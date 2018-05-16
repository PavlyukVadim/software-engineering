package com.example.amadev.select;

public class Dish {
    private String name;
    private String price;
    private String category;

    public Dish(String name, String price, String category) {
        this.price = price;
        this.name = name;
        this.category = category;
    }

    public String getPrice() {
        return price;
    }

    public void setPrice(String birthday) {
        this.price = price;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }
}