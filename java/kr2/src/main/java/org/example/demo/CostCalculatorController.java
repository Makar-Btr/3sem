package org.example.demo;

import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

public class CostCalculatorController {

    private static final double CONCERT_COST = 50000.0;
    private static final double DISCOUNT_RATE = 0.90;
    private static final String PRESENTERS_FILE_NAME = "Presenters.txt";

    private final Map<String, Map<String, Double>> presenterGifts = new HashMap<>();

    @FXML
    private CheckBox huaweiCheck;
    @FXML
    private CheckBox yandexCheck;
    @FXML
    private CheckBox tbankCheck;

    @FXML
    private ListView<Gift> giftList;

    @FXML
    private ToggleGroup concertGroup;
    @FXML
    private RadioButton concertYesRadio;
    @FXML
    private RadioButton concertNoRadio;

    @FXML
    private CheckBox persistentClientCheck;

    @FXML
    private Label totalCostLabel;
    @FXML
    private TextArea summaryTextArea;

    @FXML
    private Button calculateButton;

    private static class Gift {
        String name;
        double price;

        Gift(String name, double price) {
            this.name = name;
            this.price = price;
        }

        @Override
        public String toString() {
            return String.format("%s (%.2f руб.)", name, price);
        }
    }

    @FXML
    private void initialize() {
        // 1. Загружаем данные из файла
        try {
            loadPresentersFromFile(PRESENTERS_FILE_NAME);
        } catch (IOException e) {
            handleLoadError(e);
            return;
        }

        huaweiCheck.selectedProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal) {
                yandexCheck.setSelected(false);
                tbankCheck.setSelected(false);
            }
            updateGiftList();
        });

        yandexCheck.selectedProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal) {
                huaweiCheck.setSelected(false);
                tbankCheck.setSelected(false);
            }
            updateGiftList();
        });

        tbankCheck.selectedProperty().addListener((obs, oldVal, newVal) -> {
            if (newVal) {
                huaweiCheck.setSelected(false);
                yandexCheck.setSelected(false);
            }
            updateGiftList();
        });

        concertNoRadio.setSelected(true);
        huaweiCheck.setSelected(true);

        summaryTextArea.setText("Выберите опции и нажмите 'Рассчитать'.");
        totalCostLabel.setText("0.00 руб.");
    }

    @FXML
    private void onCalculateButtonClick() {
        double total = 0.0;
        StringBuilder summary = new StringBuilder();

        CheckBox selectedPresenterCheck = null;
        if (huaweiCheck.isSelected()) {
            selectedPresenterCheck = huaweiCheck;
        } else if (yandexCheck.isSelected()) {
            selectedPresenterCheck = yandexCheck;
        } else if (tbankCheck.isSelected()) {
            selectedPresenterCheck = tbankCheck;
        }

        if (selectedPresenterCheck == null) {
            summaryTextArea.setText("Ошибка: Поздравитель не выбран.");
            totalCostLabel.setText("0.00 руб.");
            return;
        }
        String presenterName = selectedPresenterCheck.getText();
        summary.append("Поздравитель: ").append(presenterName).append("\n");

        Gift selectedGift = giftList.getSelectionModel().getSelectedItem();
        double giftCost = 0.0;
        if (selectedGift != null) {
            giftCost = selectedGift.price;
            total += giftCost;
            summary.append("Подарок: ").append(selectedGift.name)
                    .append(" (").append(String.format("%.2f", giftCost)).append(" руб.)\n");
        } else {
            summary.append("Подарок: (не выбран)\n");
        }

        if (concertYesRadio.isSelected()) {
            total += CONCERT_COST;
            summary.append("Концерт: Да (").append(String.format("%.2f", CONCERT_COST)).append(" руб.)\n");
        } else {
            summary.append("Концерт: Нет\n");
        }

        if (persistentClientCheck.isSelected()) {
            total *= DISCOUNT_RATE;
            summary.append("Скидка: 10%\n");
        }
        else {
            summary.append("Скидка: 0%\n");
        }


        totalCostLabel.setText(String.format("%.2f руб.", total));
        summaryTextArea.setText(summary.toString());
    }

    private void updateGiftList() {
        CheckBox selectedCheck = null;
        if (huaweiCheck.isSelected()) {
            selectedCheck = huaweiCheck;
        } else if (yandexCheck.isSelected()) {
            selectedCheck = yandexCheck;
        } else if (tbankCheck.isSelected()) {
            selectedCheck = tbankCheck;
        }

        giftList.getItems().clear();

        if (selectedCheck == null) {
            return;
        }

        String presenterName = selectedCheck.getText();
        Map<String, Double> giftsMap = presenterGifts.get(presenterName);

        if (giftsMap != null) {
            for (Map.Entry<String, Double> entry : giftsMap.entrySet()) {
                giftList.getItems().add(new Gift(entry.getKey(), entry.getValue()));
            }
        }
    }

    private void loadPresentersFromFile(String fileName) throws IOException {
        InputStream is = getClass().getResourceAsStream(fileName);
        if (is == null) {
            throw new IOException("Файл ресурсов не найден: " + fileName);
        }

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8))) {
            String line;
            String currentPresenter = null;
            Map<String, Double> currentGifts = null;

            while ((line = reader.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) continue;

                if (line.equals("---")) {
                    if (currentPresenter != null && currentGifts != null) {
                        presenterGifts.put(currentPresenter, currentGifts);
                    }
                    currentPresenter = null;
                    currentGifts = null;
                } else if (line.contains(":")) {
                    String[] parts = line.split(":", 2);
                    if (parts.length == 2 && currentGifts != null) {
                        try {
                            String giftName = parts[0].trim();
                            double giftPrice = Double.parseDouble(parts[1].trim());
                            currentGifts.put(giftName, giftPrice);
                        } catch (NumberFormatException e) {
                            System.err.println("Неверный формат цены для: " + line);
                        }
                    }
                } else {
                    currentPresenter = line;
                    currentGifts = new HashMap<>();
                }
            }
            if (currentPresenter != null && currentGifts != null) {
                presenterGifts.put(currentPresenter, currentGifts);
            }
        }
    }

    private void handleLoadError(IOException e) {
        summaryTextArea.setText("ОШИБКА: Не удалось загрузить файл");
        e.printStackTrace();
        huaweiCheck.setDisable(true);
        yandexCheck.setDisable(true);
        tbankCheck.setDisable(true);
        giftList.setDisable(true);
        calculateButton.setDisable(true);
        concertYesRadio.setDisable(true);
        concertNoRadio.setDisable(true);
        persistentClientCheck.setDisable(true);
    }
}