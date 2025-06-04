package org.example.factory.suppliers;

import org.example.factory.details.Accessories;
import org.example.factory.storage.StorageOfAccessories;

public class AccessorySuppliers extends Thread {
    private int speed;
    private StorageOfAccessories storage;
    private final int supplierId;
    private static int countOfAllAccessories = 0;
    private volatile boolean isRun = true;


    public AccessorySuppliers(StorageOfAccessories storage, int supplierId, int speed) {
        this.storage = storage;
        this.supplierId = supplierId;
        this.speed = speed;
    }

    public Integer getCount() {
        return countOfAllAccessories;
    }



    @Override
    public void run() {
        try {
            while (isRun) {
                Accessories accessory = new Accessories();
                storage.put(accessory);
                countOfAllAccessories++;
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
