package org.example.factory.details;

public class Accessories {
    private static int count = 0;
    private int id = 0;

    public Accessories() {
        this.id = count++;
    }

    public int getID() {
        return id;
    }
}
