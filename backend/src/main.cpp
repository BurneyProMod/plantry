// backend/src/main.cpp
#include <crow.h>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <limits>
#include "recipe.hpp"

using json = nlohmann::json;

// Load all recipes from a JSON file at startup
std::vector<Recipe> loadRecipes(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        CROW_LOG_ERROR << "Failed to open recipes file: " << path;
        return {};
    }
    json j;
    in >> j;
    std::vector<Recipe> recipes;
    for (const auto& item : j.at("recipes")) {
        recipes.push_back(Recipe::fromJson(item));
    }
    return recipes;
}

// Given a list of recipes, build a shopping list: name → total qty
std::unordered_map<std::string, double>
buildShoppingList(const std::vector<Recipe>& plan) {
    std::unordered_map<std::string, double> agg;
    for (const auto& r : plan) {
        for (auto& [name, qty] : r.ingredients) {
            agg[name] += qty;
        }
    }
    return agg;
}

// Compute overlap score between a candidate recipe and current aggregated ingredients
double overlapScore(const Recipe& cand,
                    const std::unordered_map<std::string,double>& agg) {
    double score = 0;
    for (auto& [ing, qty] : cand.ingredients) {
        auto it = agg.find(ing);
        if (it != agg.end()) {
            score += std::min(qty, it->second);
        }
    }
    return score;
}

int main() {
    crow::SimpleApp app;

    // Load recipes once
    auto allRecipes = loadRecipes("../data/recipes.json");

    // Health check
    CROW_ROUTE(app, "/ping")([](){
        return "pong";
    });

    // GET /recipes
    CROW_ROUTE(app, "/recipes")([&](){
        crow::json::wvalue resp;
        auto& arr = resp["recipes"];
        for (const auto& r : allRecipes) {
            arr.push_back(r.toJson());
        }
        return resp;
    });

    // POST /plan
    CROW_ROUTE(app, "/plan").methods("POST"_method)
    ([&](const crow::request& req){
        auto body = json::parse(req.body);
        int desired = body.at("servings").get<int>();
        std::vector<int> selectedIds = body.at("selected").get<std::vector<int>>();

        // Build initial plan vector and aggregated ingredients
        std::vector<Recipe> plan;
        plan.reserve(desired);
        std::unordered_map<std::string,double> agg;

        // Add user‐selected first
        for (int id : selectedIds) {
            auto it = std::find_if(allRecipes.begin(), allRecipes.end(),
                                   [&](auto& r){ return r.id == id; });
            if (it != allRecipes.end()) {
                plan.push_back(*it);
                for (auto& [ing, qty] : it->ingredients)
                    agg[ing] += qty;
            }
        }

        // Fill up to desired count by max‐overlap
        while ((int)plan.size() < desired) {
            double bestScore = -1;
            size_t bestIdx = std::numeric_limits<size_t>::max();
            for (size_t i = 0; i < allRecipes.size(); ++i) {
                const auto& cand = allRecipes[i];
                // skip if already selected
                if (std::find_if(plan.begin(), plan.end(),
                                 [&](auto& r){ return r.id == cand.id; })
                    != plan.end()) continue;

                double score = overlapScore(cand, agg);
                if (score > bestScore) {
                    bestScore = score;
                    bestIdx = i;
                }
            }
            // if none found (all have zero overlap), just break
            if (bestIdx == std::numeric_limits<size_t>::max()) break;

            // add best candidate
            plan.push_back(allRecipes[bestIdx]);
            for (auto& [ing, qty] : allRecipes[bestIdx].ingredients)
                agg[ing] += qty;
        }

        // Build response
        crow::json::wvalue resp;
        auto& planArr = resp["plan"];
        for (auto& r : plan) {
            planArr.push_back(r.toJson());
        }
        auto shopping = buildShoppingList(plan);
        auto& shopObj = resp["shoppingList"];
        for (auto& [ing, qty] : shopping) {
            shopObj[ing] = qty;
        }

        return resp;
    });

    app.port(18080)
       .multithreaded()
       .run();

    return 0;
}
