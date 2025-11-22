package org.example.threads;

import javafx.fxml.FXML;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

import java.util.Arrays;

public class HelloController {

    @FXML
    private VBox barsContainer;

    private final int[] data = {15, 50, 80, 120, 45, 10, 95, 30};

    @FXML
    public void initialize() {
        int maxVal = Arrays.stream(data).max().orElse(1);

        barsContainer.getChildren().clear();

        for (int value : data) {
            Rectangle rect = new Rectangle();

            rect.setHeight(20);

            rect.setFill(Color.DODGERBLUE);

            double ratio = (double) value / maxVal;

            rect.widthProperty().bind(
                    barsContainer.widthProperty().multiply(ratio)
            );

            barsContainer.getChildren().add(rect);
        }
    }

}