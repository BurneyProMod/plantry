package com.plantry.core;

import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        Recipe pancakes = new Recipe(
            "Pancakes",
            4,
            200,
            Arrays.asList(
                new Ingredient("Flour", "2", "cups"),
                new Ingredient("Milk", "1.5", "cups"),
                new Ingredient("Eggs", "2", "pcs"),
                new Ingredient("Sugar", "2", "tbsp"),
                new Ingredient("Baking Powder", "1", "tbsp"),
                new Ingredient("Salt", "0.5", "tsp")
            ),
            "Pancakes, for when waffle house is closed.",
            "ui/thumbnails/pancakes.jpg",
            Arrays.asList(
                "In a bowl, mix the dry ingredients.",
                "In another bowl, whisk the wet ingredients.",
                "Combine both mixtures and stir until smooth.",
                "Cook on a hot griddle until golden brown."
            ),
            Arrays.asList("breakfast", "sweet", "easy")
        );

        System.out.println("Dish Name: " + pancakes.getDishName());
        System.out.println("Serving Size: " + pancakes.getServingSize());
        System.out.println("Calories: " + pancakes.getCaloriesPerServing());
        System.out.println("Description: " + pancakes.getDescription());
        System.out.println("Picture Path: " + pancakes.getPicPath());
        System.out.println("Steps:");
        pancakes.getCookingSteps().forEach(s -> System.out.println(" - " + s));
        System.out.println("Tags:");
        pancakes.getTags().forEach(t -> System.out.println(" - " + t));
    }
}
