package com.plantry.core;

import java.util.List;

public class Recipe {
    private String dishName;
    private int servingSize;
    private int caloriesPerServing;
    private List<Ingredient> ingredients;
    private String description;
    private String picPath;
    private List<String> cookingSteps;
    private List<String> tags;

    public Recipe(
        String dishName,
        int servingSize,
        int caloriesPerServing,
        List<Ingredient> ingredients,
        String description,
        String picPath,
        List<String> cookingSteps,
        List<String> tags
    ) {
        this.dishName = dishName;
        this.servingSize = servingSize;
        this.caloriesPerServing = caloriesPerServing;
        this.ingredients = ingredients;
        this.description = description;
        this.picPath = picPath;
        this.cookingSteps = cookingSteps;
        this.tags = tags;
    }

    public String getDishName() { 
        return dishName; 
    
    }

    public int getServingSize() { 
        return servingSize; 
    }

    public int getCaloriesPerServing() { 
        return caloriesPerServing; 
    }

    public List<Ingredient> getIngredients() { 
        return ingredients; 
    }

    public String getDescription() { 
        return description; 
    }

    public String getPicPath() { 
        return picPath; 
    }

    public List<String> getCookingSteps() { 
        return cookingSteps; 
    }

    public List<String> getTags() { 
        return tags;
    }

}
