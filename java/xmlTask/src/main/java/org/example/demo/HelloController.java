package org.example.demo;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.FilteredList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import org.w3c.dom.*;
import org.xml.sax.SAXException;

import javax.xml.XMLConstants;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import java.io.File;
import java.util.Optional;

public class HelloController {

    @FXML private TableView<Book> bookTable;
    @FXML private TableColumn<Book, Integer> colId;
    @FXML private TableColumn<Book, String> colTitle;
    @FXML private TableColumn<Book, String> colAuthor;
    @FXML private TableColumn<Book, Integer> colYear;
    @FXML private TableColumn<Book, Double> colPrice;
    @FXML private TableColumn<Book, String> colCategory;
    @FXML private TableColumn<Book, Integer> colTotal;
    @FXML private TableColumn<Book, Integer> colStock;

    @FXML private ComboBox<String> searchTypeBox;
    @FXML private TextField searchField;
    @FXML private Label statusLabel;

    @FXML private TextField addTitle, addAuthor, addYear, addPrice, addCategory, addTotal;

    private final ObservableList<Book> masterData = FXCollections.observableArrayList();
    private final File xmlFile = new File("library.xml");

    @FXML
    public void initialize() {
        colId.setCellValueFactory(new PropertyValueFactory<>("id"));
        colTitle.setCellValueFactory(new PropertyValueFactory<>("title"));
        colAuthor.setCellValueFactory(new PropertyValueFactory<>("author"));
        colYear.setCellValueFactory(new PropertyValueFactory<>("year"));
        colPrice.setCellValueFactory(new PropertyValueFactory<>("price"));
        colCategory.setCellValueFactory(new PropertyValueFactory<>("category"));
        colTotal.setCellValueFactory(new PropertyValueFactory<>("total"));
        colStock.setCellValueFactory(new PropertyValueFactory<>("inStock"));

        searchTypeBox.getItems().addAll("Автор", "Год", "Категория");
        searchTypeBox.setValue("Автор");

        loadXmlData();
    }

    private void showErrorDialog(String title, String content) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        alert.showAndWait();
    }

    // --- Чтение XML через DOM ---
    private void loadXmlData() {
        try {
            // 1. Валидация XSD
            SchemaFactory schemaFactory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
            Schema schema = schemaFactory.newSchema(new File("library.xsd"));
            Validator validator = schema.newValidator();
            validator.validate(new StreamSource(xmlFile));
            statusLabel.setText("✅ Статус: XML валиден (XSD проверен).");

            // 2. Парсинг DOM
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            dbFactory.setIgnoringElementContentWhitespace(true);
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(xmlFile);
            doc.getDocumentElement().normalize();

            masterData.clear();
            NodeList nList = doc.getElementsByTagName("book");

            for (int i = 0; i < nList.getLength(); i++) {
                Node nNode = nList.item(i);
                if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) nNode;

                    // Чтение атрибутов и элементов (с преобразованием типов)
                    int id = Integer.parseInt(element.getAttribute("id"));
                    int total = Integer.parseInt(element.getAttribute("total"));
                    int inStock = Integer.parseInt(element.getAttribute("inStock"));

                    String title = getTagValue("title", element);
                    String author = getTagValue("author", element);
                    int year = Integer.parseInt(getTagValue("year", element));
                    double price = Double.parseDouble(getTagValue("price", element));
                    String category = getTagValue("category", element);

                    masterData.add(new Book(id, title, author, year, price, category, total, inStock));
                }
            }
            bookTable.setItems(masterData);

        } catch (SAXException e) {
            showErrorDialog("Ошибка валидации XSD", "Файл library.xml не соответствует схеме library.xsd: " + e.getMessage());
            statusLabel.setText("❌ Ошибка: XML не загружен из-за проблем со схемой.");
        } catch (Exception e) {
            showErrorDialog("Ошибка загрузки XML", "Произошла критическая ошибка при чтении файла. Проверьте его структуру.");
            statusLabel.setText("❌ Ошибка: Критическая ошибка загрузки.");
            e.printStackTrace();
        }
    }

    private String getTagValue(String tag, Element element) {
        NodeList nodeList = element.getElementsByTagName(tag).item(0).getChildNodes();
        Node node = (Node) nodeList.item(0);
        return node.getNodeValue();
    }

    // --- Сохранение XML через DOM ---
    @FXML
    protected void onSaveClick() {
        try {
            DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
            Document doc = docBuilder.newDocument();
            Element rootElement = doc.createElement("library");
            doc.appendChild(rootElement);

            for (Book book : masterData) {
                Element bookElement = doc.createElement("book");

                // Установка атрибутов
                bookElement.setAttribute("id", String.valueOf(book.getId()));
                bookElement.setAttribute("total", String.valueOf(book.getTotal()));
                bookElement.setAttribute("inStock", String.valueOf(book.getInStock()));

                // Создание дочерних элементов
                appendChildElement(doc, bookElement, "title", book.getTitle());
                appendChildElement(doc, bookElement, "author", book.getAuthor());
                appendChildElement(doc, bookElement, "year", String.valueOf(book.getYear()));
                // Цена должна иметь формат с точкой, а не запятой, для XML
                appendChildElement(doc, bookElement, "price", String.valueOf(book.getPrice()));
                appendChildElement(doc, bookElement, "category", book.getCategory());

                rootElement.appendChild(bookElement);
            }

            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();

            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");

            DOMSource source = new DOMSource(doc);
            StreamResult result = new StreamResult(xmlFile);

            transformer.transform(source, result);

            statusLabel.setText("✅ Данные успешно сохранены в library.xml!");

        } catch (Exception e) {
            showErrorDialog("Ошибка сохранения", "Не удалось сохранить файл! " + e.getMessage());
            statusLabel.setText("❌ Ошибка: Сохранение не выполнено.");
            e.printStackTrace();
        }
    }

    private void appendChildElement(Document doc, Element parent, String tagName, String textValue) {
        Element el = doc.createElement(tagName);
        el.appendChild(doc.createTextNode(textValue));
        parent.appendChild(el);
    }

    // --- Поиск ---
    @FXML
    protected void onSearchClick() {
        String searchText = searchField.getText().toLowerCase();
        String type = searchTypeBox.getValue();

        FilteredList<Book> filteredData = new FilteredList<>(masterData, p -> true);

        filteredData.setPredicate(book -> {
            if (searchText == null || searchText.isEmpty()) return true;

            String lowerVal = "";
            if ("Автор".equals(type)) lowerVal = book.getAuthor().toLowerCase();
            else if ("Год".equals(type)) lowerVal = String.valueOf(book.getYear());
            else if ("Категория".equals(type)) lowerVal = book.getCategory().toLowerCase();

            return lowerVal.contains(searchText);
        });

        bookTable.setItems(filteredData);
        statusLabel.setText("🔍 Поиск завершен.");
    }

    @FXML
    protected void onResetSearchClick() {
        searchField.setText("");
        bookTable.setItems(masterData);
        statusLabel.setText("🔎 Поиск сброшен.");
    }

    // --- Добавление новой книги (с валидацией) ---
    @FXML
    protected void onAddBookClick() {
        try {
            int maxId = masterData.stream().mapToInt(Book::getId).max().orElse(0);

            // Валидация числовых полей
            int year = Integer.parseInt(addYear.getText());
            double price = Double.parseDouble(addPrice.getText());
            int total = Integer.parseInt(addTotal.getText());

            // Запрет отрицательных чисел
            if (year <= 0 || price <= 0 || total <= 0) {
                showErrorDialog("Ошибка ввода", "Год, Цена и Количество экземпляров должны быть положительными числами.");
                return;
            }

            Book newBook = new Book(
                    maxId + 1,
                    addTitle.getText(),
                    addAuthor.getText(),
                    year,
                    price,
                    addCategory.getText(),
                    total,
                    total
            );

            masterData.add(newBook);
            statusLabel.setText("➕ Книга добавлена (не забудьте сохранить!).");

            addTitle.clear(); addAuthor.clear(); addYear.clear();
            addPrice.clear(); addCategory.clear(); addTotal.clear();

        } catch (NumberFormatException e) {
            showErrorDialog("Ошибка ввода", "Год, Цена и Количество должны содержать только положительные числа.");
        } catch (Exception e) {
            showErrorDialog("Ошибка добавления", "Произошла ошибка при добавлении книги: " + e.getMessage());
        }
    }

    // --- Эмуляция выдачи ---
    @FXML
    protected void onIssueBookClick() {
        Book selected = bookTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            if (selected.getInStock() > 0) {
                selected.setInStock(selected.getInStock() - 1);
                statusLabel.setText("📚 Выдана книга: " + selected.getTitle() + ". Осталось: " + selected.getInStock());
                bookTable.refresh();
            } else {
                showErrorDialog("Нет в наличии", "Эта книга закончилась. Количество экземпляров в наличии равно 0.");
            }
        } else {
            statusLabel.setText("⚠️ Выберите книгу!");
        }
    }

    // --- Изменение цены (с валидацией) ---
    @FXML
    protected void onChangePriceClick() {
        Book selected = bookTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            TextInputDialog dialog = new TextInputDialog(String.valueOf(selected.getPrice()));
            dialog.setTitle("Переоценка");
            dialog.setHeaderText("Изменение цены для: " + selected.getTitle());
            dialog.setContentText("Новая цена:");

            Optional<String> result = dialog.showAndWait();
            result.ifPresent(priceStr -> {
                try {
                    double newPrice = Double.parseDouble(priceStr);

                    // Запрет отрицательных чисел
                    if (newPrice <= 0) {
                        showErrorDialog("Ошибка ввода", "Цена должна быть положительным числом.");
                        return;
                    }

                    selected.setPrice(newPrice);
                    bookTable.refresh();
                    statusLabel.setText("💰 Цена изменена на: " + newPrice);
                } catch (NumberFormatException e) {
                    showErrorDialog("Ошибка ввода", "Неверный формат цены. Введите число (используйте точку).");
                }
            });
        } else {
            statusLabel.setText("⚠️ Выберите книгу для переоценки!");
        }
    }

    @FXML
    protected void onExitClick() {
        System.exit(0);
    }
}