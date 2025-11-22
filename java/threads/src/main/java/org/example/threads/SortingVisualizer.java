package org.example.threads;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class SortingVisualizer extends Application {

    private static final long DELAY_MS = 50;
    private static final Color PRIMARY_COLOR = Color.DEEPSKYBLUE;
    private static final Color ACTIVE_COLOR = Color.DARKBLUE;
    private static final DateTimeFormatter TIME_FORMATTER = DateTimeFormatter.ofPattern("HH:mm:ss");

    private int[] originalData;

    private SortPanel bubblePanel;
    private SortPanel quickPanel;
    private SortPanel heapPanel;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        BorderPane root = new BorderPane();

        HBox controls = new HBox(10);
        Button loadBtn = new Button("Загрузить файл");
        Button startBtn = new Button("Начать сортировку");
        startBtn.setDisable(true);

        controls.getChildren().addAll(loadBtn, startBtn);
        controls.setStyle("-fx-padding: 10; -fx-background-color: #eee;");
        controls.setAlignment(Pos.CENTER);

        HBox visualArea = new HBox(20);
        visualArea.setStyle("-fx-padding: 20;");
        visualArea.setAlignment(Pos.CENTER);

        bubblePanel = new SortPanel("Bubble Sort");
        quickPanel = new SortPanel("Quick Sort");
        heapPanel = new SortPanel("Heap Sort");

        visualArea.getChildren().addAll(bubblePanel, quickPanel, heapPanel);

        loadBtn.setOnAction(e -> {
            FileChooser fileChooser = new FileChooser();
            File file = fileChooser.showOpenDialog(primaryStage);
            if (file != null) {
                loadData(file);
                startBtn.setDisable(false);
                bubblePanel.reset();
                quickPanel.reset();
                heapPanel.reset();
            }
        });

        startBtn.setOnAction(e -> startSorting());

        root.setTop(controls);
        root.setCenter(visualArea);

        Scene scene = new Scene(root, 1000, 700);
        primaryStage.setTitle("Sorting Visualizer");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void loadData(File file) {
        try {
            Scanner scanner = new Scanner(file);
            List<Integer> list = new java.util.ArrayList<>();
            while (scanner.hasNext()) {
                if (scanner.hasNextInt()) {
                    list.add(scanner.nextInt());
                } else {
                    scanner.next();
                }
            }
            originalData = list.stream().mapToInt(i -> i).toArray();

            bubblePanel.setData(originalData);
            quickPanel.setData(originalData);
            heapPanel.setData(originalData);

        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void startSorting() {
        new Thread(() -> bubbleSort(bubblePanel)).start();
        new Thread(() -> startQuickSortThread(quickPanel)).start();
        new Thread(() -> heapSort(heapPanel)).start();
    }

    private void bubbleSort(SortPanel panel) {
        long startTime = System.currentTimeMillis();
        panel.setStartTime(LocalTime.now().format(TIME_FORMATTER));

        int[] arr = panel.getData();
        int n = arr.length;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    panel.redraw(j + 1);
                    sleep();
                }
            }
        }

        long endTime = System.currentTimeMillis();
        panel.setEndTime(LocalTime.now().format(TIME_FORMATTER));
        panel.setDuration(endTime - startTime);
        panel.redraw(-1);
    }

    private void startQuickSortThread(SortPanel panel) {
        long startTime = System.currentTimeMillis();
        panel.setStartTime(LocalTime.now().format(TIME_FORMATTER));

        int[] arr = panel.getData();
        quickSort(panel, arr, 0, arr.length - 1);

        long endTime = System.currentTimeMillis();
        panel.setEndTime(LocalTime.now().format(TIME_FORMATTER));
        panel.setDuration(endTime - startTime);
        panel.redraw(-1);
    }

    private void quickSort(SortPanel panel, int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(panel, arr, low, high);
            quickSort(panel, arr, low, pi - 1);
            quickSort(panel, arr, pi + 1, high);
        }
    }

    private int partition(SortPanel panel, int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                panel.redraw(i);
                sleep();
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        panel.redraw(i + 1);
        sleep();

        return i + 1;
    }

    private void heapSort(SortPanel panel) {
        long startTime = System.currentTimeMillis();
        panel.setStartTime(LocalTime.now().format(TIME_FORMATTER));

        int[] arr = panel.getData();
        int n = arr.length;

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(panel, arr, n, i);

        for (int i = n - 1; i > 0; i--) {
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            panel.redraw(0);
            sleep();
            heapify(panel, arr, i, 0);
        }

        long endTime = System.currentTimeMillis();
        panel.setEndTime(LocalTime.now().format(TIME_FORMATTER));
        panel.setDuration(endTime - startTime);
        panel.redraw(-1);
    }

    private void heapify(SortPanel panel, int[] arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && arr[l] > arr[largest]) largest = l;
        if (r < n && arr[r] > arr[largest]) largest = r;

        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;
            panel.redraw(largest);
            sleep();
            heapify(panel, arr, n, largest);
        }
    }

    private void sleep() {
        try {
            Thread.sleep(DELAY_MS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    static class SortPanel extends VBox {
        private Canvas canvas;
        private int[] data;
        private Text startTimeText;
        private Text endTimeText;
        private Text durationText;

        public SortPanel(String title) {
            Text titleNode = new Text(title);
            titleNode.setFont(Font.font("Arial", FontWeight.BOLD, 16));

            canvas = new Canvas(300, 450);

            startTimeText = new Text("Start: --");
            startTimeText.setFill(Color.DARKBLUE);
            startTimeText.setFont(Font.font("Monospaced", FontWeight.BOLD, 12));

            endTimeText = new Text("End: --");
            endTimeText.setFill(Color.RED);
            endTimeText.setFont(Font.font("Monospaced", FontWeight.BOLD, 12));

            durationText = new Text("Time: -- ms");
            durationText.setFill(Color.FORESTGREEN);
            durationText.setFont(Font.font("Monospaced", FontWeight.BOLD, 12));

            VBox statsBox = new VBox(5, startTimeText, endTimeText, durationText);
            statsBox.setAlignment(Pos.CENTER_LEFT);
            statsBox.setStyle("-fx-padding: 10; -fx-background-color: #f4f4f4; -fx-background-radius: 5;");

            this.getChildren().addAll(titleNode, canvas, statsBox);
            this.setSpacing(10);
            this.setAlignment(Pos.TOP_CENTER);
            this.setStyle("-fx-border-color: #ccc; -fx-border-width: 1; -fx-padding: 10; -fx-background-color: white;");
        }

        public void setData(int[] originalData) {
            this.data = Arrays.copyOf(originalData, originalData.length);
            redraw(-1);
        }

        public int[] getData() {
            return data;
        }

        public void reset() {
            Platform.runLater(() -> {
                startTimeText.setText("Start: --");
                endTimeText.setText("End: --");
                durationText.setText("Time: -- ms");
            });
        }

        public void setStartTime(String time) {
            Platform.runLater(() -> startTimeText.setText("Start: " + time));
        }

        public void setEndTime(String time) {
            Platform.runLater(() -> endTimeText.setText("End:   " + time));
        }

        public void setDuration(long ms) {
            Platform.runLater(() -> durationText.setText("Time:  " + ms + " ms"));
        }

        public void redraw(int activeIndex) {
            Platform.runLater(() -> {
                GraphicsContext gc = canvas.getGraphicsContext2D();
                double width = canvas.getWidth();
                double height = canvas.getHeight();

                gc.clearRect(0, 0, width, height);

                if (data == null || data.length == 0) return;

                int maxVal = Arrays.stream(data).max().orElse(1);
                double barHeight = height / data.length;

                for (int i = 0; i < data.length; i++) {
                    if (i == activeIndex) {
                        gc.setFill(ACTIVE_COLOR);
                    } else {
                        gc.setFill(PRIMARY_COLOR);
                    }

                    double barWidth = ((double) data[i] / maxVal) * width;
                    gc.fillRect(0, i * barHeight, barWidth, barHeight);

                    if (barHeight > 3) {
                        gc.setStroke(Color.WHITE);
                        gc.strokeLine(0, i * barHeight + barHeight, width, i * barHeight + barHeight);
                    }
                }
            });
        }
    }
}