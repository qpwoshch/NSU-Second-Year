package org.example;

import javafx.application.Application;
import javafx.stage.Stage;
import org.example.Controller.Controller;


public class Main extends Application {
    public static void main(String[] args) {
        if (args[0].equals("-t")) {
            new Controller().startTextGame();
        } else if (args[0].equals("-g")) {
            launch(args);
        }
    }

    @Override
    public void start(Stage primaryStage) {
        Controller controller = new Controller();
        controller.startGUI(primaryStage);
    }
}
