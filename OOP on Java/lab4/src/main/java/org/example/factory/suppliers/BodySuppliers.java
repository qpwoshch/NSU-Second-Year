package org.example.factory.suppliers;

import org.example.factory.details.Bodies;
import org.example.factory.storage.StorageOfBody;

public class BodySuppliers extends Thread {
    private int speed;
    private StorageOfBody storage;
    private static int countOfAllBodies = 0;
    private volatile boolean isRun = true;


    public BodySuppliers(StorageOfBody storage, int speed) {
        this.storage = storage;
        this.speed = speed;
    }

    public Integer getCount() {
        return countOfAllBodies;
    }

    @Override
    public void run() {
        try {
            while (isRun) {
                Bodies body = new Bodies();
                storage.put(body);
                countOfAllBodies++;
                Thread.sleep(speed);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public void stopThreads() {
        isRun = false;
        this.interrupt();
    }

}
