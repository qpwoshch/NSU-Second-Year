package org.example.factory;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;


public class Parser {
    private static final String config = "/config.properties";

    public void parseConfigFile(StartFactory factory) throws IOException {
        try (InputStream inputStream = Parser.class.getResourceAsStream(config)) {
            Properties properties = new Properties();
            properties.load(inputStream);
            factory.setBodySize(Integer.parseInt(properties.getProperty("bodySize")));
            factory.setMotorSize(Integer.parseInt(properties.getProperty("motorSize")));
            factory.setAccessoriesSize(Integer.parseInt(properties.getProperty("accessoriesSize")));
            factory.setCarSize(Integer.parseInt(properties.getProperty("carSize")));
            factory.setAccessoriesSupplier(Integer.parseInt(properties.getProperty("accessorySuppliers")));
            factory.setWorkers(Integer.parseInt(properties.getProperty("workers")));
            factory.setDealers(Integer.parseInt(properties.getProperty("dealers")));
            factory.setLog(Boolean.parseBoolean(properties.getProperty("isLog")));
        }
    }
}
