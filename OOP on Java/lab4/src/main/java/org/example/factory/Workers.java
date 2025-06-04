package org.example.factory;

import org.example.factory.details.Accessories;
import org.example.factory.details.Bodies;
import org.example.factory.details.Cars;
import org.example.factory.details.Motors;
import org.example.factory.storage.StorageOfAccessories;
import org.example.factory.storage.StorageOfBody;
import org.example.factory.storage.StorageOfCar;
import org.example.factory.storage.StorageOfMotor;

public class Workers extends Thread{
    private final StorageOfBody bodyStorage;
    private final StorageOfMotor motorStorage;
    private final StorageOfAccessories accessoryStorage;
    private final StorageOfCar carStorage;
    private final int speedOfWork;
    private static int countOfAllCars = 0;
    private final int id;
    private volatile boolean isRun = true;

    public Workers(StorageOfBody bodyStorage, StorageOfMotor motorStorage, StorageOfAccessories accessoryStorage, StorageOfCar carStorage, int id, int speedOfWork) {
        this.bodyStorage = bodyStorage;
        this.motorStorage = motorStorage;
        this.accessoryStorage = accessoryStorage;
        this.carStorage = carStorage;
        this.speedOfWork = speedOfWork;
        this.id = id;
    }

    @Override
    public void run() {
        try {
            while (isRun) {
                Bodies body = bodyStorage.get();
                Motors motor = motorStorage.get();
                Accessories accessory = accessoryStorage.get();
                if (body == null || motor == null || accessory == null) {
                    continue;
                }
                Cars car = new Cars(body.getID(), motor.getID(), accessory.getID());
                carStorage.put(car);
                countOfAllCars++;
                Thread.sleep(speedOfWork);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public int getCount() {
        return countOfAllCars;
    }

    public void stopThreads() {
        isRun = false;
        this.interrupt();
    }

}
