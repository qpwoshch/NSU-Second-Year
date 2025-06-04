package org.example.Model;

import javafx.application.Platform;
import javafx.beans.property.SimpleIntegerProperty;

public class Timer {
    private final SimpleIntegerProperty second = new SimpleIntegerProperty(0);
    private Thread timer;
    private volatile boolean isRun;

    public void startTimer() {
        isRun = true;
        timer = new Thread(() -> {
            while (isRun) {
                try {
                    Thread.sleep(1000);
                    Platform.runLater(() -> second.set(second.get() + 1));
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        });
        timer.setDaemon(true);
        timer.start();
    }

    public void stopTimer() {
        isRun = false;
        if (timer != null) {
            timer.interrupt();
        }
    }

    public void resetTimer() {
        second.set(0);
    }

    public SimpleIntegerProperty getTime() {
        return second;
    }
}
