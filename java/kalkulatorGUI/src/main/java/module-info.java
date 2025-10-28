module org.example.kalkulatorgui {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;

    opens org.example.kalkulatorgui to javafx.fxml;
    exports org.example.kalkulatorgui;
}