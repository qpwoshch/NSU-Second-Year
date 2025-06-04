package org.example.factory;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.factory.details.Cars;
import org.example.factory.storage.StorageOfCar;

import java.util.Map;

public class Dealers extends Thread {
    private int speed;
    private int dealerID;
    private StorageOfCar storage;
    private volatile boolean isRun = true;
    private static final Logger logger = LogManager.getLogger(Dealers.class);
    private boolean isLog;


    public Dealers(StorageOfCar storage, int id, int speed, boolean isLog) {
        this.dealerID = id;
        this.storage = storage;
        this.speed = speed;
        this.isLog = isLog;
    }

    public void setSpeed(int speed) {
        this.speed = speed;
    }


    @Override
    public void run() {
        try {
            while (isRun) {
                Cars car = storage.get();
                if (isLog) {
                    writeLog(car.getID());
                }
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

    private void writeLog(Map<String, Integer> id) {
        logger.info("Dealer Number: " + (dealerID+1) + " Auto: " + (id.get("carID")+1) + " (Body: " + (id.get("bodyID")+1) + " Motor: " + (id.get("motorID")+1) + " Accessory: " + (id.get("accessoryID")+1) + ")");
    }
}
