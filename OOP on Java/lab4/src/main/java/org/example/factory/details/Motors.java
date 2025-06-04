package org.example.factory.details;

public class Motors {
    private static int count = 0;
    private int id = 0;

    public Motors() {
        this.id = count++;
    }

    public int getID() {
        return id;
    }
}
