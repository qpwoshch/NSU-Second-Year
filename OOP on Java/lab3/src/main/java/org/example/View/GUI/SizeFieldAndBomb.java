package org.example.View.GUI;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Stage;

public class SizeFieldAndBomb {
    private final Stage stage;
    private final SliderForOptions listenerForSlider;
    private final ButtonForExitToMenu listenerForButton;


    public SizeFieldAndBomb(Stage stage, SliderForOptions listenerForSlider, ButtonForExitToMenu listenerForButton) {
        this.stage = stage;
        this.listenerForSlider = listenerForSlider;
        this.listenerForButton = listenerForButton;
    }

    public void show(boolean isError) {
        Style style = new Style();
        MyBackground background = new MyBackground();
        Slider sizeSlider = style.createStyledSlider(1, 30, 10);
        Label error = style.createErrorLabel("Counts of bomb must be more then counts of cell");
        Label sizeLabel = style.createStyledLabel("Field size: 10");
        Label bombLabel = style.createStyledLabel("Count of bomb: 9");
        Slider bombSlider = style.createStyledSlider(1, 50, 9);
        Button btnBack = style.createStyledButton("Main Menu");
        Button btnStart = style.createStyledButton("Start Game");
        sizeSlider.valueProperty().addListener((obs, oldVal, newVal) ->
                sizeLabel.setText("FIELD SIZE: " + newVal.intValue()));

        bombSlider.valueProperty().addListener((obs, oldVal, newVal) ->
                bombLabel.setText("BOMB COUNT: " + newVal.intValue()));
        btnStart.setOnAction(e -> {
            int size = (int)sizeSlider.getValue();
            int bombs = (int)bombSlider.getValue();
            if (bombs > size * size) {
                show(true);
            }
            else {
                listenerForSlider.SizeSettingsChanged(size, bombs);
            }
        });
        btnBack.setOnAction(e->listenerForButton.MenuSelected());
        VBox root = new VBox(30, sizeLabel, sizeSlider, bombLabel, bombSlider, btnStart, btnBack);
        if (isError) {
            root = new VBox(30, sizeLabel, sizeSlider, bombLabel, bombSlider, error,btnStart);
        }
        root.setAlignment(Pos.CENTER);
        root.setPadding(new Insets(50));
        root.setBackground(new Background(background.getCastomBackground()));

        Scene scene = new Scene(root, 1100, 800);
        stage.setScene(scene);
        stage.setTitle("Game Settings");
        stage.show();
    }
}