package org.example.demo;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class OlympiadCostApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(OlympiadCostApplication.class.
                getResource("cost-calculator-view.fxml"));

        Scene scene = new Scene(fxmlLoader.load(), 1000, 800);
        stage.setTitle("Калькулятор затрат на олимпиаду");
        stage.setScene(scene);
        stage.setResizable(false);
        stage.show();
    }

    public static void main(String[] args) {
        Application.launch(OlympiadCostApplication.class, args);
    }
}