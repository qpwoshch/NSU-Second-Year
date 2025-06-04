package org.example.factory.storage;

import org.example.factory.details.Accessories;

import java.util.LinkedList;
import java.util.Queue;

public class StorageOfAccessories {
    private Integer accessoriesSize;
    private Queue<Accessories> accessories = new LinkedList<>();
    private volatile boolean isRun = true;



    public void setAccessoriesSize(int data) {
        this.accessoriesSize = data;
    }

    public Integer getCount() {
        return accessories.size();
    }

    public synchronized void put(Accessories accessory) throws InterruptedException {
        while (accessories.size() >= accessoriesSize && isRun) {
            wait();
        }
        if (!isRun) {
            return;
        }
        accessories.add(accessory);
        notifyAll();
    }

    public synchronized Accessories get() throws InterruptedException {
        while (accessories.isEmpty() && isRun) {
            wait();
        }
        if (!isRun) {
            return null;
        }
        Accessories accessory = accessories.poll();
        notifyAll();
        return accessory;
    }

    public void stopThreads() {
        isRun = false;
        synchronized (this) {
            notifyAll();
        }
    }
}
