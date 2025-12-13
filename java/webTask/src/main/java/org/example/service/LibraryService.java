package org.example.service;

import org.example.model.Book;
import org.springframework.stereotype.Service;
import org.w3c.dom.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.XMLConstants;

@Service
public class LibraryService {
    private final File xmlFile = new File("src/main/resources/library.xml");

    public List<Book> getAllBooks() {
        List<Book> books = new ArrayList<>();
        try {
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            try {
                SchemaFactory schemaFactory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
                File xsdFile = new File("src/main/resources/library.xsd");
                Schema schema = schemaFactory.newSchema(xsdFile);

                dbFactory.setSchema(schema);
                dbFactory.setNamespaceAware(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(xmlFile);
            doc.getDocumentElement().normalize();
            NodeList nList = doc.getElementsByTagName("book");

            for (int i = 0; i < nList.getLength(); i++) {
                Element element = (Element) nList.item(i);
                books.add(new Book(
                        Integer.parseInt(element.getAttribute("id")),
                        getTagValue("title", element),
                        getTagValue("author", element),
                        Integer.parseInt(getTagValue("year", element)),
                        Double.parseDouble(getTagValue("price", element)),
                        getTagValue("category", element),
                        Integer.parseInt(element.getAttribute("total")),
                        Integer.parseInt(element.getAttribute("inStock"))
                ));
            }
        } catch (Exception e) { e.printStackTrace(); }
        return books;
    }

    public void saveBooks(List<Book> books) {
        try {
            DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
            Document doc = docBuilder.newDocument();
            Element rootElement = doc.createElement("library");
            doc.appendChild(rootElement);

            for (Book book : books) {
                Element bookElement = doc.createElement("book");
                bookElement.setAttribute("id", String.valueOf(book.getId()));
                bookElement.setAttribute("total", String.valueOf(book.getTotal()));
                bookElement.setAttribute("inStock", String.valueOf(book.getInStock()));

                appendChild(doc, bookElement, "title", book.getTitle());
                appendChild(doc, bookElement, "author", book.getAuthor());
                appendChild(doc, bookElement, "year", String.valueOf(book.getYear()));
                appendChild(doc, bookElement, "price", String.valueOf(book.getPrice()));
                appendChild(doc, bookElement, "category", book.getCategory());
                rootElement.appendChild(bookElement);
            }

            Transformer transformer = TransformerFactory.newInstance().newTransformer();
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            transformer.transform(new DOMSource(doc), new StreamResult(xmlFile));
        } catch (Exception e) { e.printStackTrace(); }
    }

    public List<Book> searchBooks(String query, String type) {
        List<Book> all = getAllBooks();
        if (query == null || query.isEmpty()) return all;
        String q = query.toLowerCase();

        return all.stream().filter(b -> {
            if ("author".equals(type)) return b.getAuthor().toLowerCase().contains(q);
            if ("year".equals(type)) return String.valueOf(b.getYear()).contains(q);
            if ("category".equals(type)) return b.getCategory().toLowerCase().contains(q);
            return false;
        }).collect(Collectors.toList());
    }

    public void addBook(Book book) {
        List<Book> books = getAllBooks();
        int maxId = books.stream().mapToInt(Book::getId).max().orElse(0);
        book.setId(maxId + 1);
        books.add(book);
        saveBooks(books);
    }

    private String getTagValue(String tag, Element element) {
        return element.getElementsByTagName(tag).item(0).getTextContent();
    }
    private void appendChild(Document doc, Element parent, String tag, String val) {
        Element el = doc.createElement(tag);
        el.setTextContent(val);
        parent.appendChild(el);
    }
}