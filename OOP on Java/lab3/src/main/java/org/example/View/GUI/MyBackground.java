package org.example.View.GUI;

import javafx.scene.image.Image;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;

import java.util.Objects;

public class MyBackground {
    public BackgroundImage getCastomBackground() {
        Image backgroundImage = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/background.png")));
        BackgroundImage background = new BackgroundImage(
                backgroundImage,
                BackgroundRepeat.NO_REPEAT,
                BackgroundRepeat.NO_REPEAT,
                BackgroundPosition.CENTER,
                new BackgroundSize(100, 100, true, true, true, true)
        );
        return background;
    }

    public BackgroundImage getCastomBackgroundForField() {
        Image backgroundImage = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/fieldBackground.png")));
        BackgroundImage background = new BackgroundImage(
                backgroundImage,
                BackgroundRepeat.NO_REPEAT,
                BackgroundRepeat.NO_REPEAT,
                BackgroundPosition.CENTER,
                new BackgroundSize(100, 100, true, true, true, true)
        );
        return background;
    }
}
