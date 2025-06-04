package org.example.Model;

import java.util.*;

import static java.lang.Integer.parseInt;
import static java.lang.Math.*;

public class Field {
    public List<Cell> field;
    public Integer countOfBomb;

    public void setField(int data) {
        int size = (int) pow(data, 2.0);
        field = new ArrayList<>(size);
        for (int i = 0; i < size; i++) {
            field.add(new Cell());
        }
    }

    public boolean boundary(int i) {
        return (i % (int)sqrt(field.size()) == 0);
    }

    public void fillingField(int data) {
        countOfBomb = data;
        Random random = new Random();
        int bomb;
        for (int i = 0; i < countOfBomb; i++) {
            bomb = random.nextInt(field.size());
            if (field.get(bomb).getValueForModel().equals("Bomb")) {
                i--;
                continue;
            }
            field.get(bomb).setValue("Bomb");
        }
        for (int i = 0; i < field.size(); i++) {
            if (field.get(i).getValueForModel().equals("Bomb")) {
                continue;
            }
            int neighbor = 0;
            int shiftUp = i + (int) sqrt(field.size());
            int shiftDown = i - (int) sqrt(field.size());
            if (i + 1 < field.size() && field.get(i + 1).getValueForModel().equals("Bomb") && !boundary(i + 1)) {
                neighbor++;
            }
            if (i - 1 >= 0 && field.get(i - 1).getValueForModel().equals("Bomb") && !boundary(i)) {
                neighbor++;
            }
            if (shiftUp < field.size() && field.get(shiftUp).getValueForModel().equals("Bomb")) {
                neighbor++;
            }
            if (shiftDown >= 0 && field.get(shiftDown).getValueForModel().equals("Bomb")) {
                neighbor++;
            }
            if (shiftUp + 1 < field.size() && field.get(shiftUp + 1).getValueForModel().equals("Bomb") && !boundary(i + 1)) {
                neighbor++;
            }
            if (shiftUp - 1 < field.size() && field.get(shiftUp - 1).getValueForModel().equals("Bomb") && !boundary(i)) {
                neighbor++;
            }
            if (shiftDown + 1 >= 0 && field.get(shiftDown + 1).getValueForModel().equals("Bomb") && !boundary(i + 1)) {
                neighbor++;
            }
            if (shiftDown - 1 >= 0 && field.get(shiftDown - 1).getValueForModel().equals("Bomb") && !boundary(i)) {
                neighbor++;
            }
            field.get(i).setValue(Integer.toString(neighbor));
        }

    }



    public void OpenAndCheckingForZero(int cell) {
        field.get(cell).makeTheCellOpen();
        if (field.get(cell).getValue().equals("0")) {
            OpenAround(cell);
        }
    }

    public void OpenAround(int cell) {
        int shiftUp = cell + (int) sqrt(field.size());
        int shiftDown = cell - (int) sqrt(field.size());
        if (cell - 1 >= 0 && !boundary(cell) && !field.get(cell-1).isFlagOpen() && !field.get(cell-1).isCellOpen()) {
            OpenAndCheckingForZero(cell-1);
        }
        if (cell+1 < field.size() && !boundary(cell+1) && !field.get(cell+1).isCellOpen() && !field.get(cell+1).isFlagOpen()) {
            OpenAndCheckingForZero(cell+1);
        }
        if (shiftUp < field.size() && !field.get(shiftUp).isFlagOpen() && !field.get(shiftUp).isCellOpen()) {
            OpenAndCheckingForZero(shiftUp);
        }
        if (shiftDown >= 0 && !field.get(shiftDown).isCellOpen() && !field.get(shiftDown).isFlagOpen()) {
            OpenAndCheckingForZero(shiftDown);
        }
    }

    public boolean openTheCell(String data) {
        try {
            String[] command = data.split(" ");
            if (command.length < 2) {
                throw new IllegalArgumentException("Invalid input. Please enter a 2 parameters");
            }
            if (!command[0].equals("Open") && !command[0].equals("Flag")) {
                throw new IllegalArgumentException("Invalid input. First argument must be a \"Flag\" or \"Open\"");
            }
            int cell = parseInt(command[1]);
            if (cell < 0 || cell >= field.size()) {
                throw new IndexOutOfBoundsException("Invalid input. Cell index must be between 0 and " + (field.size() - 1));
            }
            if (command[0].equals("Open")) {
                try {
                    field.get(cell).makeTheCellOpen();
                } catch (Exception e) {
                    throw e;
                }
                if (field.get(cell).getValue().equals("0")) {
                    OpenAround(cell);
                }
                return !field.get(cell).getValue().equals("Bomb");
            }
            else {
                try {
                    field.get(cell).putTheFlag();
                } catch (Exception e) {
                    throw e;
                }
                return true;
            }
        } catch (NumberFormatException e) {
            System.err.println("Invalid input. Please enter a number with second parameter");
            return true;
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            return true;
        } catch (Exception e) {
            System.err.println(e.getMessage());
            return true;
        }
    }

    public void openAllCell() {
        for (int i = 0; i < field.size(); i++) {
            field.get(i).openForcibly();
        }
    }

    public boolean isWin() {
        for (int i = 0; i < field.size(); i++) {
            if (!field.get(i).getValueForModel().equals("Bomb") && !field.get(i).isCellOpen()) {
                return false;
            }
        }
        return true;
    }


}
