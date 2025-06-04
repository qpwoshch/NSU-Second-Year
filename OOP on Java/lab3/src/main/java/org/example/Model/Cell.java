package org.example.Model;

public class Cell {
    private String value;
    private boolean isOpen;
    private boolean isFlag;

    public Cell() {
        isOpen = false;
        this.value = "";
        isFlag = false;
    }

    public void openForcibly() {
        isFlag = false;
        isOpen = true;
    }

    public void makeTheCellOpen() {
        if (isOpen) {
            throw new IllegalStateException("This cell already open");
        }
        if (isFlag) {
            throw new IllegalStateException("Cannot open this cell, because it has a flag");
        }
        else {
            isOpen = true;
        }
    }

    public void setValue(String data) {
        this.value = data;
    }

    public String getValue() {
        if (isOpen) {
            return value;
        }
        return ".";
    }

    public String getValueForModel() {
        return value;
    }

    public void putTheFlag() {
        if (isOpen) {
            throw new IllegalStateException("Cannot put flag on opened cell");
        }
        if (isFlag) {
            isFlag = false;
        }
        else {
            isFlag = true;
        }
    }

    public boolean isFlagOpen() {
        return isFlag;
    }

    public boolean isCellOpen() {
        return isOpen;
    }
}
