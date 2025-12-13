package org.example.model;

import java.util.ArrayList;
import java.util.List;

public class User {
    private String username;
    private String password;
    private String role;
    private List<String> issuedBooks = new ArrayList<>();

    public User(String username, String password, String role) {
        this.username = username;
        this.password = password;
        this.role = role;
    }

    public String getUsername() { return username; }
    public String getPassword() { return password; }
    public String getRole() { return role; }
    public List<String> getIssuedBooks() { return issuedBooks; }
}