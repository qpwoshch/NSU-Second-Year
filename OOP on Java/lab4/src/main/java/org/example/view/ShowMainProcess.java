package org.example.view;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.Background;
import javafx.scene.layout.VBox;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import javafx.util.Duration;
import org.example.factory.StartFactory;

import java.util.HashMap;
import java.util.Map;

public class ShowMainProcess {
    private final Stage stage;
    private Style style = new Style();
    private final SliderForDealers listenerForSlider;
    private Map<String, Integer> value = new HashMap<>();
    private Timeline timeline;




    public ShowMainProcess(Stage stage, SliderForDealers listenerForSlider) {
        this.stage = stage;
        this.listenerForSlider = listenerForSlider;
    }

    public void show(StartFactory factory) {
        MyBackground background = new MyBackground();
        value = factory.getValue();

        Label producedAccessoriesLabel = style.createStyledLabel("Produced Accessories: " + value.get("ProducedAccessories"));
        Label accessoriesStorageLabel = style.createStyledLabel("Accessories in Storage: " + value.get("AccessoriesInStorage"));

        Label producedBodiesLabel = style.createStyledLabel("Produced Bodies: " + value.get("ProducedBodies"));
        Label bodiesStorageLabel = style.createStyledLabel("Bodies in Storage: " + value.get("BodiesInStorage"));

        Label producedMotorsLabel = style.createStyledLabel("Produced Motors: " + value.get("ProducedMotors"));
        Label motorsStorageLabel = style.createStyledLabel("Motors in Storage: " + value.get("MotorsInStorage"));

        Label producedCarsLabel = style.createStyledLabel("Produced Cars: " + value.get("ProducedCars"));
        Label carsStorageLabel = style.createStyledLabel("Cars in Storage: " + value.get("CarsInStorage"));

        Slider slider = style.createStyledSlider(1000, 10000, factory.getSpeedOfDealers());
        Label speedOfRequestingLabel = style.createStyledLabel("Speed of requesting the car: " + factory.getSpeedOfDealers() + "ms");

        slider.valueProperty().addListener((obs, oldVal, newVal) -> {
            int newSpeed = newVal.intValue();
            speedOfRequestingLabel.setText("Speed of requesting the car: " + newSpeed + "ms");
            listenerForSlider.speedChange(newSpeed);
        });

        HBox accessoriesFlow = new HBox(10, producedAccessoriesLabel, accessoriesStorageLabel);
        accessoriesFlow.setAlignment(Pos.CENTER);

        HBox bodiesFlow = new HBox(10, producedBodiesLabel, bodiesStorageLabel);
        bodiesFlow.setAlignment(Pos.CENTER);

        HBox motorsFlow = new HBox(10, producedMotorsLabel, motorsStorageLabel);
        motorsFlow.setAlignment(Pos.CENTER);

        HBox carsFlow = new HBox(10, producedCarsLabel, carsStorageLabel);
        carsFlow.setAlignment(Pos.CENTER);

        VBox dealerFlow = new VBox(10, speedOfRequestingLabel, slider);
        dealerFlow.setAlignment(Pos.CENTER);

        VBox fullFlow = new VBox(30,
                accessoriesFlow,
                bodiesFlow,
                motorsFlow,
                carsFlow,
                dealerFlow
        );
        fullFlow.setAlignment(Pos.CENTER);
        fullFlow.setPadding(new Insets(50));
        fullFlow.setBackground(new Background(background.getMainBackground()));

        Scene scene = new Scene(fullFlow, 1400, 800);
        stage.setScene(scene);
        stage.setTitle("Factory");

        startAutoUpdate(factory,
                producedAccessoriesLabel, accessoriesStorageLabel,
                producedBodiesLabel, bodiesStorageLabel,
                producedMotorsLabel, motorsStorageLabel,
                producedCarsLabel, carsStorageLabel);

        stage.setOnCloseRequest(event -> {
            stopAutoUpdate();
            factory.stopThreads();
            Platform.exit();
            System.exit(0);
        });

        stage.show();
    }


    private void startAutoUpdate(StartFactory factory,
                                 Label producedAccessoriesLabel, Label accessoriesStorageLabel,
                                 Label producedBodiesLabel, Label bodiesStorageLabel,
                                 Label producedMotorsLabel, Label motorsStorageLabel,
                                 Label producedCarsLabel, Label carsStorageLabel) {
        timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> {
            value = factory.getValue();

            producedAccessoriesLabel.setText("Produced Accessories: " + value.get("ProducedAccessories"));
            accessoriesStorageLabel.setText("Accessories in Storage: " + value.get("AccessoriesInStorage"));

            producedBodiesLabel.setText("Produced Bodies: " + value.get("ProducedBodies"));
            bodiesStorageLabel.setText("Bodies in Storage: " + value.get("BodiesInStorage"));

            producedMotorsLabel.setText("Produced Motors: " + value.get("ProducedMotors"));
            motorsStorageLabel.setText("Motors in Storage: " + value.get("MotorsInStorage"));

            producedCarsLabel.setText("Produced Cars: " + value.get("ProducedCars"));
            carsStorageLabel.setText("Cars in Storage: " + value.get("CarsInStorage"));
        }));
        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();
    }

    private void stopAutoUpdate() {
        if (timeline != null) {
            timeline.stop();
        }
    }


}
