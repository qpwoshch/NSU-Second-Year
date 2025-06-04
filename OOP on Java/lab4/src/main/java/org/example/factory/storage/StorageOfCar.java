package org.example.factory.storage;

import org.example.factory.details.Cars;

import java.util.LinkedList;
import java.util.Queue;

public class StorageOfCar {
    private Integer carSize;
    private Queue<Cars> cars = new LinkedList<>();
    private volatile boolean isRun = true;



    public void setCarSize(int data) {
        this.carSize = data;
    }

    public Integer getCount() {
        return cars.size();
    }


    public synchronized void put(Cars car) throws InterruptedException {
        while (cars.size() >= carSize && isRun) {
            wait();
        }
        if (!isRun) {
            return;
        }
        cars.add(car);
        notifyAll();
    }

    public synchronized Cars get() throws InterruptedException {
        while (cars.isEmpty() && isRun) {
            wait();
        }
        if (!isRun) {
            return null;
        }
        Cars car = cars.poll();
        notifyAll();
        return car;
    }

    public void stopThreads() {
        isRun = false;
        synchronized (this) {
            notifyAll();
        }
    }
}
