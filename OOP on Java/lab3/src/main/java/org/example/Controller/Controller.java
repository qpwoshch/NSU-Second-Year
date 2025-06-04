package org.example.Controller;

import javafx.scene.control.Label;
import javafx.scene.input.MouseButton;
import javafx.stage.Stage;
import org.example.Model.Field;
import org.example.Model.HighScore;
import org.example.Model.Parser;
import org.example.Model.Timer;
import org.example.View.GUI.*;
import static java.lang.Integer.parseInt;

import org.example.View.TextVersion.PrintAbout;
import org.example.View.TextVersion.PrintHighScore;
import org.example.View.TextVersion.PrintTextField;

import java.util.Scanner;


public class Controller implements ButtonFromMenu, SliderForOptions, ButtonForExitToMenu {
    private String data;
    private final Parser parser = new Parser();
    private final Field field = new Field();
    private final Scanner in = new Scanner(System.in);
    private Stage primaryStage;
    private final PrintAbout printAbout = new PrintAbout();
    private final PrintHighScore printHighScore = new PrintHighScore();
    private final Timer timer = new Timer();
    private final HighScore tableOfScore = new HighScore();

    public boolean textGame()  {
        PrintTextField print = new PrintTextField();
        boolean continuesGame = true;
        while (continuesGame) {
            continuesGame = field.isWin();
            if (continuesGame) {
                System.out.println("Congratulations, you win!");
                print.printField(field);
                return true;
            }
            print.printField(field);
            System.out.println("Enter a cell, which you want to open or put the flag");
            data = parser.parsing(in);
            continuesGame = field.openTheCell(data);
        }
        System.out.println("You lose");
        field.openAllCell();
        print.printField(field);
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        return false;
    }

    public void startTextGame()  throws NumberFormatException {
        System.out.println("Please enter a command: " +
                "\n\"New Game\" for new game" +
                "\n\"Exit\" for quit" +
                "\n\"About\" for information about this game" +
                "\n\"High Score\" for viewing the table of leaders");
        while (true) {
            data = parser.parsing(in);
            if (data.equals("New Game")) {
                timer.startTimer();
                int setSize = 0;
                while (true) {
                    try {
                        System.out.println("Enter size of field");
                        setSize = parseInt(parser.parsing(in));
                        break;
                    } catch (NumberFormatException e) {
                        System.err.println(e.getMessage());
                    }
                }
                field.setField(setSize);
                int setBomb = 0;
                while (true) {
                    try {
                        System.out.println("Enter count of bomb");
                        setBomb = parseInt(parser.parsing(in));
                        if (setBomb > setSize * setSize) {
                            System.err.println("Count of Bomb should be fewer than Size of field. Please enter count of bomb again");
                            continue;
                        }
                        break;
                    } catch (NumberFormatException e) {
                        System.err.println(e.getMessage());
                    }
                }
                field.fillingField(setBomb);
                boolean isWin = textGame();
                timer.stopTimer();
                if (isWin) {
                    System.out.println("Enter your name");
                    tableOfScore.setHighScore(parser.parsing(in), timer.getTime().get());
                }
                timer.resetTimer();
            } else if (data.equals("Exit")) {
                System.exit(0);
            } else if (data.equals("High Score")) {
                printHighScore.print(tableOfScore.getHighScore());
            } else if (data.equals("About")) {
                printAbout.print();
            } else {
                System.err.println("Unrecognized command, please enter: " +
                        "\n\"New Game\" for new game" +
                        "\n\"Exit\" for quit" +
                        "\n\"About\" for information about this game" +
                        "\n\"High Score\" for viewing the table of leaders");
            }
            System.out.print("Please enter a command: ");
        }
    }

    public void startGUI(Stage primaryStage) {
        this.primaryStage = primaryStage;
        showMainMenu();
    }
    private void showMainMenu() {
        new Menu(primaryStage, this).show();
    }

    @Override
    public void NewGameSelected() {
        new SizeFieldAndBomb(primaryStage, this, this).show(false);
    }

    @Override
    public void AboutSelected() {
        new ShowAbout(primaryStage, this).show();
    }

    @Override
    public void ExitSelected() {
        primaryStage.close();
    }

    @Override
    public void SizeSettingsChanged(int fieldSize, int bombCount) {
        field.setField(fieldSize);
        field.fillingField(bombCount);
        startGameGUI();
    }

    @Override
    public void MenuSelected() {
        showMainMenu();
    }



    @Override
    public void onNameEntered(String name) {
        int finalTime = timer.getTime().get();
        tableOfScore.setHighScore(name, finalTime);
    }

    @Override
    public void HighScoreSelected() {
        new Message(primaryStage, this).showHighScore(tableOfScore.getHighScore());
    }

    private void startGameGUI() {
        timer.resetTimer();
        timer.startTimer();
        Label timerLabel = new Label();
        timerLabel.textProperty().bind(timer.getTime().asString("Time: %d s"));
        final DrawnGameField[] gameFieldHolder = new DrawnGameField[1];
        DrawnGameField gameField = new DrawnGameField(primaryStage, (cellIndex, button) -> {
            boolean isContinue;
            if (button == MouseButton.PRIMARY) {
                data = "Open " + cellIndex;
            } else if (button == MouseButton.SECONDARY) {
                data = "Flag " + cellIndex;
            }
            isContinue =  field.openTheCell(data);
            if (data.contains("Open")) {
                gameFieldHolder[0].updateAllCells(field);
            }
            if (field.isWin()) {
                gameFieldHolder[0].show(field, timer.getTime());
                timer.stopTimer();
                new Message(primaryStage, this).showWinMessage();
                return false;
            }
            else if (!isContinue) {
                gameFieldHolder[0].show(field, timer.getTime());
                field.openAllCell();
                gameFieldHolder[0].show(field, timer.getTime());
                try {
                    Thread.sleep(3000);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
                new Message(primaryStage, this).showLoseMessage();
                return false;
            }
            return true;
        });
        gameFieldHolder[0] = gameField;
        gameField.show(field, timer.getTime());
    }
}
