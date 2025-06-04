package org.example.View.GUI;

import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.effect.DropShadow;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

public class Style {
    public Button createStyledButton(String text) {
        Button button = new Button(text);

        button.setStyle(
                "-fx-background-color: linear-gradient(#ff5400, #be1d00);" +
                        "-fx-background-radius: 30;" +
                        "-fx-text-fill: white;" +
                        "-fx-font-weight: bold;" +
                        "-fx-padding: 15 40 15 40;" +
                        "-fx-border-radius: 30;" +
                        "-fx-border-width: 3;" +
                        "-fx-border-color: white;"
        );

        button.setFont(Font.font("Arial", 24));

        DropShadow shadow = new DropShadow();
        shadow.setColor(Color.rgb(0, 0, 0, 0.5));
        shadow.setRadius(10);
        shadow.setSpread(0.2);

        button.setEffect(shadow);

        button.setOnMouseEntered(e -> {
            button.setStyle(button.getStyle() + "-fx-background-color: linear-gradient(#ff7000, #d62800);");
            button.setTranslateY(-2);
        });

        button.setOnMouseExited(e -> {
            button.setStyle(button.getStyle().replace("-fx-background-color: linear-gradient(#ff7000, #d62800);",
                    "-fx-background-color: linear-gradient(#ff5400, #be1d00);"));
            button.setTranslateY(0);
        });



        return button;
    }
    public Slider createStyledSlider(double min, double max, double value) {
        Slider slider = new Slider(min, max, value);

        slider.setStyle(
                "-fx-control-inner-background: #ff5400;" +
                        "-fx-background-color: transparent;" +
                        "-fx-padding: 10;" +
                        "-fx-show-tick-marks: true;" +
                        "-fx-show-tick-labels: true;" +
                        "-fx-major-tick-unit: 5;" +
                        "-fx-minor-tick-count: 4;" +
                        "-fx-snap-to-ticks: true;" +
                        "-fx-tick-label-fill: #ff5400;" +
                        "-fx-tick-mark-color: #ff5400;"
        );

        slider.setMinWidth(500);
        slider.setMaxWidth(500);

        DropShadow shadow = new DropShadow();
        shadow.setColor(Color.rgb(0, 0, 0, 0.3));
        shadow.setRadius(5);
        slider.setEffect(shadow);

        return slider;
    }

    public Label createStyledLabel(String text) {
        Label label = new Label(text);
        label.setStyle(
                "-fx-text-fill: #e0e0e0;" +
                        "-fx-font-weight: bold;" +
                        "-fx-effect: dropshadow(three-pass-box, rgba(0,0,0,0.8), 6, 0.3, 0, 2);" +
                        "-fx-background-color: rgba(0,0,0,0.4);" +
                        "-fx-background-radius: 5;" +
                        "-fx-padding: 8px 12px;" +
                        "-fx-border-color: #505050;" +
                        "-fx-border-width: 1px;" +
                        "-fx-border-radius: 5px;"
        );
        label.setFont(Font.font("Arial", FontWeight.BOLD, 28));
        label.setLineSpacing(1.5);
        label.setWrapText(true);
        return label;
    }

    public Label createErrorLabel(String text) {
        Label label = new Label(text);
        label.setStyle(
                "-fx-text-fill: #ff4444;" +
                        "-fx-font-weight: bold;" +
                        "-fx-effect: dropshadow(gaussian, rgba(255,0,0,0.3), 3, 0.5, 0, 1);" +
                        "-fx-background-color: rgba(0,0,0,0.4);" +
                        "-fx-background-radius: 5;" +
                        "-fx-padding: 8px 12px;" +
                        "-fx-border-color: #505050;" +
                        "-fx-border-width: 1px;" +
                        "-fx-border-radius: 5px;"
        );
        label.setFont(Font.font("Arial", FontWeight.EXTRA_BOLD, 30));
        return label;
    }
}
