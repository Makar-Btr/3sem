package org.example.controller;

import org.example.model.Book;
import org.example.service.LibraryService;
import org.example.service.UserService;
import org.springframework.security.core.Authentication;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Controller
public class LibraryController {
    private final LibraryService libraryService;
    private final UserService userService;

    public LibraryController(LibraryService libraryService, UserService userService) {
        this.libraryService = libraryService;
        this.userService = userService;
    }

    @GetMapping("/books")
    public String viewBooks(@RequestParam(required = false) String search,
                            @RequestParam(required = false) String type,
                            Model model, Authentication auth) {
        List<Book> books = libraryService.searchBooks(search, type);
        model.addAttribute("books", books);
        model.addAttribute("role", auth.getAuthorities().toString());
        return "books";
    }

    @GetMapping("/librarian/add")
    public String showAddBookForm(Model model) {
        model.addAttribute("book", new Book());
        return "add-book";
    }

    @PostMapping("/librarian/add")
    public String addBook(@ModelAttribute Book book) {
        libraryService.addBook(book);
        return "redirect:/books";
    }

    @PostMapping("/librarian/issue/{id}")
    public String issueBook(@PathVariable int id,
                            @RequestParam String username,
                            Model model,
                            Authentication auth) {
        try {
            List<Book> books = libraryService.getAllBooks();
            Book bookToIssue = books.stream().filter(b -> b.getId() == id).findFirst().orElse(null);

            if (bookToIssue != null && bookToIssue.getInStock() > 0) {
                userService.issueBookToUser(username, bookToIssue.getTitle());

                bookToIssue.setInStock(bookToIssue.getInStock() - 1);
                libraryService.saveBooks(books);
            }
        } catch (RuntimeException e) {
            if (e.getMessage().equals("USER_NOT_FOUND")) {
                List<Book> books = libraryService.searchBooks(null, null);
                model.addAttribute("books", books);
                model.addAttribute("role", auth.getAuthorities().toString());

                model.addAttribute("showRegisterModal", true);
                model.addAttribute("notFoundUsername", username);
                model.addAttribute("pendingBookId", id);

                return "books";
            }
        }
        return "redirect:/books";
    }

    @PostMapping("/librarian/fast-register")
    public String fastRegisterAndIssue(@RequestParam String username,
                                       @RequestParam String password,
                                       @RequestParam int bookId) {
        try {
            userService.register(username, password);
        } catch (Exception e) {
        }

        List<Book> books = libraryService.getAllBooks();
        Book book = books.stream().filter(b -> b.getId() == bookId).findFirst().orElse(null);

        if (book != null && book.getInStock() > 0) {
            userService.issueBookToUser(username, book.getTitle());
            book.setInStock(book.getInStock() - 1);
            libraryService.saveBooks(books);
        }

        return "redirect:/books";
    }

    @GetMapping("/account")
    public String viewAccount(Model model, Authentication auth) {
        var user = userService.findByUsername(auth.getName()).get();
        model.addAttribute("user", user);
        return "account";
    }
}