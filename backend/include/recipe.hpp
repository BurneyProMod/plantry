#ifndef PLANTRY_RECIPE_HPP
#define PLANTRY_RECIPE_HPP

#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

// A single recipe: has an ID, a human-readable name,
// and a map of ingredient name → quantity (for one serving).
struct Recipe {
    int                                        id;
    std::string                                name;
    std::unordered_map<std::string, double>    ingredients;

    // Deserialize from JSON:
    // {
    //   "id": 1,
    //   "name": "Pancakes",
    //   "ingredients": {
    //      "flour": 100.0,
    //      "egg": 1.0,
    //      "milk": 200.0
    //   }
    // }
    static Recipe fromJson(const nlohmann::json& j) {
        Recipe r;
        r.id = j.at("id").get<int>();
        r.name = j.at("name").get<std::string>();
        for (auto& [key, val] : j.at("ingredients").items()) {
            r.ingredients[key] = val.get<double>();
        }
        return r;
    }

    // Serialize back to JSON (same shape as above):
    nlohmann::json toJson() const {
        nlohmann::json j;
        j["id"] = id;
        j["name"] = name;
        nlohmann::json ing = nlohmann::json::object();
        for (auto& [key, val] : ingredients) {
            ing[key] = val;
        }
        j["ingredients"] = ing;
        return j;
    }
};

#endif // PLANTRY_RECIPE_HPP
