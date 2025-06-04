package org.example.factory.storage;

import org.example.factory.details.Motors;

import java.util.LinkedList;
import java.util.Queue;

public class StorageOfMotor {
    private Integer motorsSize;
    private Queue<Motors> motors = new LinkedList<>();
    private volatile boolean isRun = true;



    public void setMotorSize(int data) {
        this.motorsSize = data;
    }

    public Integer getCount() {
        return motors.size();
    }

    public synchronized void put(Motors motor) throws InterruptedException {
        while (motors.size() >= motorsSize && isRun) {
            wait();
        }
        if (!isRun) {
            return;
        }
        motors.add(motor);
        notifyAll();
    }

    public synchronized Motors get() throws InterruptedException {
        while (motors.isEmpty() && isRun) {
            wait();
        }
        if (!isRun) {
            return null;
        }
        Motors motor = motors.poll();
        notifyAll();
        return motor;
    }


    public void stopThreads() {
        isRun = false;
        synchronized (this) {
            notifyAll();
        }
    }
}
