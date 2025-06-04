package org.example.factory;

import javafx.stage.Stage;
import org.example.factory.storage.StorageOfAccessories;
import org.example.factory.storage.StorageOfBody;
import org.example.factory.storage.StorageOfCar;
import org.example.factory.storage.StorageOfMotor;
import org.example.factory.suppliers.AccessorySuppliers;
import org.example.factory.suppliers.BodySuppliers;
import org.example.factory.suppliers.MotorSuppliers;
import org.example.view.ShowMainProcess;
import org.example.view.SliderForDealers;
import org.example.view.SliderForOptions;
import org.example.view.StartMenu;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;



public class StartFactory implements SliderForOptions, SliderForDealers {
    private final Parser parser = new Parser();
    private final Stage primaryStage;
    private boolean isLog;
    private final StorageOfCar storageOfCar = new StorageOfCar();
    private final StorageOfBody storageOfBody = new StorageOfBody();
    private final StorageOfMotor storageOfMotor = new StorageOfMotor();
    private final StorageOfAccessories storageOfAccessories = new StorageOfAccessories();
    private Integer countOfAccessoriesSupplier;
    private int speedOfBody, speedOfAccessories, speedOfMotor, speedOfDealers;
    private int workers, dealers;
    private final List<Workers> listOfWorkers = new ArrayList<>();
    private final List<AccessorySuppliers> listOfAccessorySuppliers = new ArrayList<>();
    private BodySuppliers bodySuppliers;
    private MotorSuppliers motorSuppliers;
    private List<Dealers> listOfDealers = new ArrayList<>();
    private int speedOfWork;


    public StartFactory(Stage primaryStage) {
        this.primaryStage = primaryStage;
    }


    public void setBodySize(int data) {
        storageOfBody.setBodySize(data);
    }
    public void setMotorSize(int data) {
        storageOfMotor.setMotorSize(data);
    }
    public void setAccessoriesSize(int data) {
        storageOfAccessories.setAccessoriesSize(data);
    }
    public void setCarSize(int data) {
        storageOfCar.setCarSize(data);
    }
    public void setWorkers(int data) {
        this.workers = data;
    }
    public void setDealers(int data) {
        this.dealers = data;
    }
    public void setLog(boolean data) {
        this.isLog = data;
    }
    public void setAccessoriesSupplier(int data) {
        this.countOfAccessoriesSupplier = data;
    }



    public void setSettings() throws IOException {
        parser.parseConfigFile(this);
        new StartMenu(primaryStage, this).show();
    }

    public void Initial() {
        for (int i = 0; i < countOfAccessoriesSupplier; i++) {
            AccessorySuppliers accessorySuppliers = new AccessorySuppliers(storageOfAccessories, i, speedOfAccessories);
            listOfAccessorySuppliers.add(accessorySuppliers);
            accessorySuppliers.start();
        }
        bodySuppliers = new BodySuppliers(storageOfBody, speedOfBody);
        bodySuppliers.start();
        motorSuppliers = new MotorSuppliers(storageOfMotor, speedOfMotor);
        motorSuppliers.start();
        for (int i = 0; i < workers; i++) {
            Workers workers = new Workers(storageOfBody, storageOfMotor, storageOfAccessories, storageOfCar, i, speedOfWork);
            listOfWorkers.add(workers);
            workers.start();
        }

        for (int i = 0; i < dealers; i++) {
            Dealers dealers = new Dealers(storageOfCar, i, speedOfDealers, isLog);
            listOfDealers.add(dealers);
            dealers.start();
        }
        GUI();
    }

    @Override
    public void SizeSettingsChanged(int speedOfBody, int speedOfMotor, int speedOfAccessories, int speedOfRequestingCar, int speedOfWork) {
        this.speedOfBody = speedOfBody;
        this.speedOfMotor = speedOfMotor;
        this.speedOfAccessories = speedOfAccessories;
        this.speedOfDealers = speedOfRequestingCar;
        this.speedOfWork = speedOfWork;
        Initial();
    }



    public Map<String, Integer> getValue() {
        Map<String, Integer> value = new HashMap<>();
        value.put("AccessoriesInStorage", storageOfAccessories.getCount());
        value.put("BodiesInStorage", storageOfBody.getCount());
        value.put("MotorsInStorage", storageOfMotor.getCount());
        value.put("CarsInStorage", storageOfCar.getCount());
        if (!listOfAccessorySuppliers.isEmpty()) {
            int producedAccessories = listOfAccessorySuppliers.getFirst().getCount();
            value.put("ProducedAccessories", producedAccessories);
        } else {
            value.put("ProducedAccessories", 0);
        }
        value.put("ProducedBodies", bodySuppliers.getCount());
        value.put("ProducedMotors", motorSuppliers.getCount());
        if (!listOfWorkers.isEmpty()) {
            value.put("ProducedCars", listOfWorkers.getFirst().getCount());
        } else {
            value.put("ProducedCars", 0);
        }

        return value;
    }

    public void GUI() {
        new ShowMainProcess(primaryStage, this).show(this);
    }

    @Override
    public void speedChange(int speedOfDealers) {
        for (Dealers dealer : listOfDealers) {
            dealer.setSpeed(speedOfDealers);
        }
        this.speedOfDealers = speedOfDealers;
    }

    public int getSpeedOfDealers() {
        return speedOfDealers;
    }

    public void stopThreads() {
        bodySuppliers.stopThreads();
        motorSuppliers.stopThreads();
        for (Dealers dealers : listOfDealers) {
            dealers.stopThreads();
        }
        for (Workers workers : listOfWorkers) {
            workers.stopThreads();
        }
        for (AccessorySuppliers suppliers : listOfAccessorySuppliers) {
            suppliers.stopThreads();
        }
        storageOfBody.stopThreads();
        storageOfMotor.stopThreads();
        storageOfCar.stopThreads();
        storageOfAccessories.stopThreads();
    }
}
