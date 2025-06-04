package org.example.factory.details;

public class Bodies {
    private static int count = 0;
    private int id = 0;


    public Bodies() {
        this.id = count++;
    }

    public int getID() {
        return id;
    }
}
