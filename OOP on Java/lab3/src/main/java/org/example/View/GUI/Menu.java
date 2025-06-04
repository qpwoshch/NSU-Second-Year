package org.example.View.GUI;

import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.*;
import javafx.stage.Stage;

public class Menu {
    private final Stage stage;
    private final ButtonFromMenu listenerForButton;

    public Menu(Stage stage, ButtonFromMenu listenerForButton) {
        this.stage = stage;
        this.listenerForButton = listenerForButton;
    }

    public void show() {
        Style styleOfButton = new Style();
        MyBackground background = new MyBackground();
        Button NewGame = styleOfButton.createStyledButton("New Game");
        Button Exit = styleOfButton.createStyledButton("Exit");
        Button About = styleOfButton.createStyledButton("About");
        Button HighScore = styleOfButton.createStyledButton("High Score");
        NewGame.setOnAction(e -> listenerForButton.NewGameSelected());
        Exit.setOnAction(e -> listenerForButton.ExitSelected());
        About.setOnAction(e->listenerForButton.AboutSelected());
        HighScore.setOnAction(e->listenerForButton.HighScoreSelected());
        VBox root = new VBox(50, NewGame, About, HighScore, Exit);
        root.setAlignment(Pos.CENTER);
        root.setBackground(new Background(background.getCastomBackground()));
        Scene scene = new Scene(root, 1100, 800);

        stage.setScene(scene);
        stage.setTitle("Minesweeper - Main Menu");
        stage.show();
    }

}