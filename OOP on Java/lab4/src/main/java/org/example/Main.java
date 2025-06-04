package org.example;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.factory.StartFactory;
import javafx.application.Application;
import javafx.stage.Stage;
import java.io.IOException;


public class Main extends Application {
    private static final Logger logger = LogManager.getLogger(Main.class);
    public static void main(String[] args) throws IOException {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        StartFactory startFactory = new StartFactory(primaryStage);
        startFactory.setSettings();
    }
}