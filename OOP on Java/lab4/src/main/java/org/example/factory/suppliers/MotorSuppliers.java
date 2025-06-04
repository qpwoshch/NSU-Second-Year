package org.example.factory.suppliers;

import org.example.factory.details.Motors;
import org.example.factory.storage.StorageOfMotor;

public class MotorSuppliers extends Thread {
    private int speed;
    private StorageOfMotor storage;
    private static int countOfAllMotors = 0;
    private volatile boolean isRun = true;


    public MotorSuppliers(StorageOfMotor storage, int speed) {
        this.storage = storage;
        this.speed = speed;
    }

    public Integer getCount() {
        return countOfAllMotors;
    }

    @Override
    public void run() {
        try {
            while (isRun) {
                Motors motor = new Motors();
                storage.put(motor);
                countOfAllMotors++;
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
