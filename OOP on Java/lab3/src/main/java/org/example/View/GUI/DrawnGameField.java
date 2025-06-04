package org.example.View.GUI;

import javafx.beans.property.IntegerProperty;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
import javafx.scene.control.Label;

import static java.lang.Integer.parseInt;

import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;
import org.example.Model.Field;

import java.util.Objects;

import static java.lang.Math.sqrt;

public class DrawnGameField {
    private final Stage stage;
    private final CellClicker listenerForCell;
    private int cellSize;
    private final Image bomb;
    private final Image flag;
    private Label[][] cellLabels;

    public DrawnGameField(Stage stage, CellClicker listenerForCell) {
        this.stage = stage;
        this.listenerForCell = listenerForCell;
        bomb = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/mine.png")));
        flag = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/flag.png")));
    }
    public void show(Field field, IntegerProperty time) {
        Label timerLabel = new Label();
        timerLabel.textProperty().bind(time.asString("Time: %d s"));
        timerLabel.setStyle("-fx-font-size: 35px; -fx-text-fill: darkblue;");
        HBox topPanel = new HBox(timerLabel);
        topPanel.setAlignment(Pos.TOP_LEFT);
        topPanel.setPadding(new Insets(10));
        int sizeField = (int)sqrt(field.field.size());
        SetCellSize(sizeField);
        VBox window = new VBox(topPanel);
        window.setPadding(new Insets(0, 0, 0, 0));
        window.setAlignment(Pos.TOP_CENTER);
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        cellLabels = new Label[sizeField][sizeField];
        for (int row = 0; row < sizeField; row++) {
            for (int col = 0; col < sizeField; col++) {
                Label cellLabel = new Label();
                cellLabel.setPrefSize(cellSize, cellSize);
                cellLabel.setAlignment(Pos.CENTER);
                cellLabel.setFont(Font.font("Arial", FontWeight.BOLD, cellSize*0.5));
                cellLabel.setStyle("-fx-border-color: black; -fx-border-width: 1;");

                int cellIndex = row * sizeField + col;
                updateCell(cellLabel, field, cellIndex);

                cellLabel.setOnMouseClicked(e -> {
                    boolean needUpdate = false;
                    needUpdate = listenerForCell.CellClicked(cellIndex, e.getButton());
                    if (needUpdate) {
                        updateCell(cellLabel, field, cellIndex);
                    }
                });

                grid.add(cellLabel, col, row);
                cellLabels[row][col] = cellLabel;
            }
        }
        MyBackground background = new MyBackground();
        window.setBackground(new Background(background.getCastomBackgroundForField()));
        window.getChildren().add(grid);
        Scene scene = new Scene(window, sizeField * cellSize, sizeField * cellSize);
        stage.setScene(scene);
        stage.setTitle("Minesweeper");
        stage.show();
    }

    private void updateCell(Label cellLabel, Field field, int cell) {
        if (field.field.get(cell).isFlagOpen()) {
            ImageView imageView = new ImageView(flag);
            imageView.setFitWidth(cellSize - 10);
            imageView.setFitHeight(cellSize - 10);
            cellLabel.setGraphic(imageView);
            cellLabel.setText("");
        }
        else if (!field.field.get(cell).isCellOpen()) {
            cellLabel.setGraphic(null);
            cellLabel.setText("");
            cellLabel.setStyle("-fx-border-color: black; -fx-border-width: 1;");
        }
        else if (field.field.get(cell).getValue().equals("Bomb")) {
            ImageView imageView = new ImageView(bomb);
            imageView.setFitWidth(cellSize - 10);
            imageView.setFitHeight(cellSize - 10);
            cellLabel.setGraphic(imageView);
            cellLabel.setText("");
        }
        else if (field.field.get(cell).getValue().equals("0")) {
            cellLabel.setGraphic(null);
            cellLabel.setText("");
            cellLabel.setStyle("-fx-background-color: #BC8F8F; -fx-border-color: black; -fx-border-width: 1;");
        }
        else {
            cellLabel.setGraphic(null);
            int minesAround = parseInt(field.field.get(cell).getValue());
            cellLabel.setText(String.valueOf(minesAround));
            cellLabel.setTextFill(getNumberColor(minesAround));
        }
    }

    private Paint getNumberColor(int minesAround) {
        return switch (minesAround) {
            case 1 -> Color.BLUE;
            case 2 -> Color.GREEN;
            case 3 -> Color.RED;
            case 4 -> Color.DARKBLUE;
            case 5 -> Color.DARKRED;
            case 6 -> Color.TEAL;
            case 7 -> Color.BLACK;
            case 8 -> Color.GRAY;
            default -> Color.YELLOWGREEN;
        };
    }
    public void updateAllCells(Field field) {
        int sizeField = (int)sqrt(field.field.size());
        for (int row = 0; row < sizeField; row++) {
            for (int col = 0; col < sizeField; col++) {
                int cellIndex = row * sizeField + col;
                updateCell(cellLabels[row][col], field, cellIndex);
            }
        }
    }

    private void SetCellSize(int sizeField) {
        int maxWidth = (1000 / sizeField);
        int maxHeight = (700 / sizeField);
        cellSize = Math.min(maxWidth, maxHeight);
        cellSize = Math.max(cellSize, 20);
    }
}
