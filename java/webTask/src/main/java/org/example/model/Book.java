package org.example.model;

public class Book {
    private int id;
    private String title;
    private String author;
    private int year;
    private double price;
    private String category;
    private int total;
    private int inStock;

    public Book() {}

    public Book(int id, String title, String author, int year, double price, String category, int total, int inStock) {
        this.id = id;
        this.title = title;
        this.author = author;
        this.year = year;
        this.price = price;
        this.category = category;
        this.total = total;
        this.inStock = inStock;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }
    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }
    public String getAuthor() { return author; }
    public void setAuthor(String author) { this.author = author; }
    public int getYear() { return year; }
    public void setYear(int year) { this.year = year; }
    public double getPrice() { return price; }
    public void setPrice(double price) { this.price = price; }
    public String getCategory() { return category; }
    public void setCategory(String category) { this.category = category; }
    public int getTotal() { return total; }
    public void setTotal(int total) { this.total = total; }
    public int getInStock() { return inStock; }
    public void setInStock(int inStock) { this.inStock = inStock; }
}