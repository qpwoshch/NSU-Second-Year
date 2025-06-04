package org.example.View.GUI;

import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.Background;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.InputStream;
import java.util.Scanner;

public class ShowAbout {
    private final Stage stage;
    private String text = "";
    private final ButtonForExitToMenu listenerForButton;


    public ShowAbout(Stage stage, ButtonForExitToMenu listenerForButton) {
        this.stage = stage;
        this.listenerForButton = listenerForButton;
    }
    public void show() {
        Style style = new Style();
        Button btnBack = style.createStyledButton("Main Menu");
        try (InputStream inputStream = getClass().getResourceAsStream("/about");
            Scanner about = new Scanner(inputStream)) {
            while (about.hasNextLine()) {
                text += about.nextLine() + "\n";
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
        Label message = style.createStyledLabel(text);
        VBox root = new VBox(50, message, btnBack);
        root.setAlignment(Pos.CENTER);
        MyBackground background = new MyBackground();
        root.setBackground(new Background(background.getCastomBackground()));
        btnBack.setOnAction(e->listenerForButton.MenuSelected());
        Scene scene = new Scene(root, 1100, 800);
        stage.setScene(scene);
        stage.setTitle("About");
        stage.show();
    }
}
