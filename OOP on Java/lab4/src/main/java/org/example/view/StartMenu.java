package org.example.view;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Stage;

public class StartMenu {
    private final Stage stage;
    private final SliderForOptions listenerForSlider;
    private Style style = new Style();


    public StartMenu(Stage stage, SliderForOptions listenerForSlider) {
        this.stage = stage;
        this.listenerForSlider = listenerForSlider;
    }

    public void show() {
        MyBackground background = new MyBackground();
        Slider speedOfWorkSlider = style.createStyledSlider(1000, 10000, 1000);
        Slider speedOfAccessoriesSlider = style.createStyledSlider(1000, 10000, 1000);
        Slider speedOfMotorSlider = style.createStyledSlider(1000, 10000, 1000);
        Slider speedOfBodySlider = style.createStyledSlider(1000, 10000, 1000);
        Slider speedOfRequestingCarSlider = style.createStyledSlider(1000, 10000, 1000);
        Label speedOfWorkLabel = style.createStyledLabel("Speed of work: 1000ms");
        Label speedOfRequestingLabel = style.createStyledLabel("Speed of requesting the car: 1000ms");
        Label speedBodyLabel = style.createStyledLabel("Speed of body supplier: 1000ms");
        Label speedMotorLabel = style.createStyledLabel("Speed of motor supplier: 1000ms");
        Label speedAccessoriesLabel = style.createStyledLabel("Speed of accessories supplier: 1000ms");
        Button btnStart = style.createStyledButton("Start Factory");
        speedOfMotorSlider.valueProperty().addListener((obs, oldVal, newVal) ->
                speedMotorLabel.setText("Speed of motor supplier: " + newVal.intValue()));
        speedOfWorkSlider.valueProperty().addListener((obs, oldVal, newVal) ->
                speedOfWorkLabel.setText("Speed of work supplier: " + newVal.intValue()));
        speedOfBodySlider.valueProperty().addListener((obs, oldVal, newVal) ->
                speedBodyLabel.setText("Speed of body supplier: " + newVal.intValue()));
        speedOfAccessoriesSlider.valueProperty().addListener((obs, oldVal, newVal) ->
                speedAccessoriesLabel.setText("Speed of accessories supplier: " + newVal.intValue()));
        speedOfRequestingCarSlider.valueProperty().addListener((obs, oldVal, newVal) ->
                speedOfRequestingLabel.setText("Speed of requesting the car: " + newVal.intValue()));
        btnStart.setOnAction(e -> {
                listenerForSlider.SizeSettingsChanged((int)speedOfBodySlider.getValue(), (int)speedOfMotorSlider.getValue(), (int)speedOfAccessoriesSlider.getValue(), (int)speedOfRequestingCarSlider.getValue(), (int)speedOfWorkSlider.getValue());

        });
        VBox root = new VBox(20, speedBodyLabel, speedOfBodySlider, speedMotorLabel, speedOfMotorSlider, speedAccessoriesLabel, speedOfAccessoriesSlider, speedOfRequestingLabel, speedOfRequestingCarSlider, speedOfWorkLabel, speedOfWorkSlider, btnStart);
        root.setBackground(new Background(background.getMainBackground()));
        root.setAlignment(Pos.CENTER);
        root.setPadding(new Insets(50));
        Scene scene = new Scene(root, 1400, 800);
        stage.setScene(scene);
        stage.setTitle("Game Settings");
        stage.show();
    }
}
