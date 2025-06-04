package org.example.View.GUI;

import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.Background;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;


public class Message {
    private final Stage stage;
    private final MyBackground background = new MyBackground();
    private final Style style = new Style();
    private final Button btnMen = style.createStyledButton("Main Menu");
    private Label message;
    private VBox root = new VBox();
    private final ButtonForExitToMenu listenerForButton;


    public Message(Stage stage, ButtonForExitToMenu listenerForButton) {
        this.stage = stage;
        this.listenerForButton = listenerForButton;

    }

    public void showMessage() {
        root.setAlignment(Pos.CENTER);
        root.setBackground(new Background(background.getCastomBackground()));
        btnMen.setOnAction(e->listenerForButton.MenuSelected());
        Scene scene = new Scene(root, 1100, 800);
        stage.setScene(scene);
        stage.setTitle("Game");
        stage.show();
    }

    public void showWinMessage() {
        root.getChildren().clear();
        message = style.createStyledLabel("You Win");
        Label nameOfWinner = style.createStyledLabel("Enter your name");
        Button save = style.createStyledButton("Save");
        TextField nameField = new TextField();
        save.setOnAction(e -> {
            String name;
            name = nameField.getText();
            if (name != null && !name.isEmpty()) {
                listenerForButton.onNameEntered(name);
            }
        });
        nameField.setMaxWidth(200);
        btnMen.setOnAction(e -> listenerForButton.MenuSelected());
        root.getChildren().addAll(message, nameOfWinner, nameField, save, btnMen);
        root.setSpacing(20);
        showMessage();
    }

    public void showLoseMessage() {
        root.getChildren().clear();
        message = style.createStyledLabel("You Lose");
        root.getChildren().addAll(message, btnMen);
        root.setSpacing(20);
        showMessage();
    }

    public void showHighScore(StringBuilder listOfHighScore) {
        root.getChildren().clear();
        message = style.createStyledLabel(String.valueOf(listOfHighScore));
        root.getChildren().addAll(message, btnMen);
        root.setSpacing(20);
        showMessage();
    }
}
