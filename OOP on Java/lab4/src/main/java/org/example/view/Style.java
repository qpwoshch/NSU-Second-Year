package org.example.view;

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

        String normalStyle =
                "-fx-background-color: linear-gradient(to bottom, #ffd580, #ff8c42);" +
                        "-fx-background-radius: 25;" +
                        "-fx-text-fill: #4b2e00;" +
                        "-fx-font-weight: bold;" +
                        "-fx-padding: 10 28 10 28;" +
                        "-fx-border-radius: 25;" +
                        "-fx-border-width: 1;" +
                        "-fx-border-color: rgba(255, 255, 255, 0.6);";

        String hoverStyle =
                "-fx-background-color: linear-gradient(to bottom, #ffe0a3, #ffaa5e);" +
                        "-fx-background-radius: 25;" +
                        "-fx-text-fill: #4b2e00;" +
                        "-fx-font-weight: bold;" +
                        "-fx-padding: 10 28 10 28;" +
                        "-fx-border-radius: 25;" +
                        "-fx-border-width: 1;" +
                        "-fx-border-color: rgba(255, 255, 255, 0.8);";

        button.setStyle(normalStyle);
        button.setFont(Font.font("Arial", 20));

        DropShadow shadow = new DropShadow();
        shadow.setColor(Color.rgb(255, 200, 100, 0.6));
        shadow.setRadius(10);
        shadow.setOffsetY(2);
        button.setEffect(shadow);

        button.setOnMouseEntered(e -> {
            button.setStyle(hoverStyle);
            button.setTranslateY(-2);
        });

        button.setOnMouseExited(e -> {
            button.setStyle(normalStyle);
            button.setTranslateY(0);
        });

        return button;
    }


    public Slider createStyledSlider(double min, double max, double value) {
        Slider slider = new Slider(min, max, value);

        slider.setStyle(
                "-fx-control-inner-background: transparent;" +
                        "-fx-background-color: rgba(255, 255, 255, 0.4);" +
                        "-fx-padding: 8;" +
                        "-fx-show-tick-marks: true;" +
                        "-fx-show-tick-labels: true;" +
                        "-fx-major-tick-unit: 10;" +
                        "-fx-minor-tick-count: 3;" +
                        "-fx-snap-to-ticks: true;" +
                        "-fx-tick-label-fill: #ffffff;" +
                        "-fx-tick-mark-color: #ffffff;"
        );

        slider.setMinWidth(450);
        slider.setMaxWidth(450);

        DropShadow shadow = new DropShadow();
        shadow.setColor(Color.rgb(0, 0, 0, 0.2));
        shadow.setRadius(3);
        slider.setEffect(shadow);

        return slider;
    }

    public Label createStyledLabel(String text) {
        Label label = new Label(text);
        label.setStyle(
                "-fx-text-fill: white;" +
                        "-fx-font-weight: bold;" +
                        "-fx-effect: dropshadow(three-pass-box, rgba(0,0,0,0.6), 3, 0.2, 0, 1);" +
                        "-fx-background-color: rgba(0, 0, 0, 0.3);" +
                        "-fx-background-radius: 6;" +
                        "-fx-padding: 8px 12px;" +
                        "-fx-border-color: rgba(255, 255, 255, 0.35);" +
                        "-fx-border-width: 1;" +
                        "-fx-border-radius: 6;"
        );
        label.setFont(Font.font("Arial", FontWeight.BOLD, 22));
        label.setLineSpacing(1.1);
        label.setWrapText(true);
        return label;
    }
}
