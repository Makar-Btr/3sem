package org.example.tables;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.Comparator;

public class HelloController
{

    @FXML
    private TableView<Student> studentTable;
    @FXML
    private TableColumn<Student, String> surnameColumn;
    @FXML
    private TableColumn<Student, String> nameColumn;
    @FXML
    private TableColumn<Student, String> patronymicColumn;
    @FXML
    private TableColumn<Student, String> groupColumn;
    @FXML
    private TableColumn<Student, Integer> idColumn;

    @FXML
    private ComboBox<String> sortComboBox;

    private final ObservableList<Student> studentData = FXCollections.observableArrayList();

    @FXML
    private void initialize()
    {
        sortComboBox.getItems().addAll("SNP", "Group", "ID");
        sortComboBox.setValue("SNP");

        surnameColumn.setCellValueFactory(new PropertyValueFactory<>("surname"));
        nameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        patronymicColumn.setCellValueFactory(new PropertyValueFactory<>("patronymic"));
        groupColumn.setCellValueFactory(new PropertyValueFactory<>("group"));
        idColumn.setCellValueFactory(new PropertyValueFactory<>("ID"));

        studentTable.setItems(studentData);

        // УДАЛИТЕ ЭТУ СТРОКУ: loadDataFromFile();
    }

    private void loadDataFromFile()
    {
        studentData.clear(); // Очищаем список перед загрузкой
        String fileName = "students.txt";

        try (InputStream is = getClass().getResourceAsStream(fileName))
        {

            if (is == null)
            {
                showErrorAlert("Не удалось найти файл " + fileName);
                return;
            }

            try (BufferedReader reader = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8)))
            {
                String line;
                while ((line = reader.readLine()) != null)
                {
                    if (line.trim().isEmpty())
                    {
                        continue;
                    }

                    String[] parts = line.split(",");
                    if (parts.length == 5)
                    {
                        try
                        {
                            String surname = parts[0].trim();
                            String name = parts[1].trim();
                            String patronymic = parts[2].trim();
                            String group = parts[3].trim();
                            int id = Integer.parseInt(parts[4].trim());

                            studentData.add(new Student(surname, name, patronymic, group, id));

                        } catch (NumberFormatException e)
                        {
                            System.err.println("Ошибка парсинга ID в строке: " + line);
                        }
                    } else
                    {
                        System.err.println("Неверный формат строки: " + line);
                    }
                }
            }

        } catch (IOException e)
        {
            showErrorAlert("Ошибка чтения файла");
        }
    }

    @FXML
    protected void onSortButtonClick(ActionEvent event)
    {
        String sortBy = sortComboBox.getValue();
        if (sortBy == null)
        {
            return;
        }

        switch (sortBy)
        {
            case "SNP":
                studentData.sort(Comparator.comparing(Student::getFullName));
                break;
            case "Group":
                studentData.sort(Comparator.comparing(Student::getGroup));
                break;
            case "ID":
                studentData.sort(Comparator.comparingInt(Student::getID));
                break;
        }
    }

    @FXML
    protected void onInputButtonClick(ActionEvent event)
    {
        loadDataFromFile();
    }
    // ------------------------------------------


    private void showErrorAlert(String content)
    {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setContentText(content);
        alert.showAndWait();
    }
}