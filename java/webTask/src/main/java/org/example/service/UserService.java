package org.example.service;

import org.example.model.User;
import org.springframework.stereotype.Service;
import org.w3c.dom.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class UserService {

    private final File xmlFile = new File("src/main/resources/users.xml");

    public Optional<User> findByUsername(String username) {
        return getAllUsers().stream()
                .filter(u -> u.getUsername().equalsIgnoreCase(username))
                .findFirst();
    }

    public void register(String username, String password) {
        List<User> users = getAllUsers();

        if (users.stream().anyMatch(u -> u.getUsername().equalsIgnoreCase(username))) {
            throw new RuntimeException("Пользователь с таким именем уже существует!");
        }

        users.add(new User(username, "{noop}" + password, "ROLE_READER"));
        saveUsers(users);
    }

    public void issueBookToUser(String username, String bookTitle) {
        List<User> users = getAllUsers();

        Optional<User> userOpt = users.stream()
                .filter(u -> u.getUsername().equalsIgnoreCase(username))
                .findFirst();

        if (userOpt.isEmpty()) {
            throw new RuntimeException("USER_NOT_FOUND");
        }

        userOpt.get().getIssuedBooks().add(bookTitle);
        saveUsers(users);
    }


    private List<User> getAllUsers() {
        List<User> userList = new ArrayList<>();
        if (!xmlFile.exists()) return userList;

        try {
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(xmlFile);
            doc.getDocumentElement().normalize();

            NodeList nList = doc.getElementsByTagName("user");
            for (int i = 0; i < nList.getLength(); i++) {
                Element element = (Element) nList.item(i);
                String username = getTagValue("username", element);
                String password = getTagValue("password", element);
                String role = getTagValue("role", element);

                User user = new User(username, password, role);

                NodeList booksNode = element.getElementsByTagName("issuedBooks");
                if (booksNode.getLength() > 0) {
                    NodeList bookTitles = ((Element) booksNode.item(0)).getElementsByTagName("bookTitle");
                    for (int j = 0; j < bookTitles.getLength(); j++) {
                        user.getIssuedBooks().add(bookTitles.item(j).getTextContent());
                    }
                }
                userList.add(user);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return userList;
    }

    private void saveUsers(List<User> users) {
        try {
            DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
            Document doc = docBuilder.newDocument();
            Element rootElement = doc.createElement("users");
            doc.appendChild(rootElement);

            for (User user : users) {
                Element userElement = doc.createElement("user");
                appendChild(doc, userElement, "username", user.getUsername());
                appendChild(doc, userElement, "password", user.getPassword());
                appendChild(doc, userElement, "role", user.getRole());

                Element issuedBooks = doc.createElement("issuedBooks");
                for (String title : user.getIssuedBooks()) {
                    appendChild(doc, issuedBooks, "bookTitle", title);
                }
                userElement.appendChild(issuedBooks);
                rootElement.appendChild(userElement);
            }

            Transformer transformer = TransformerFactory.newInstance().newTransformer();
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            transformer.transform(new DOMSource(doc), new StreamResult(xmlFile));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private String getTagValue(String tag, Element element) {
        NodeList nl = element.getElementsByTagName(tag);
        return (nl.getLength() > 0) ? nl.item(0).getTextContent() : "";
    }

    private void appendChild(Document doc, Element parent, String tag, String val) {
        Element el = doc.createElement(tag);
        el.setTextContent(val);
        parent.appendChild(el);
    }
}