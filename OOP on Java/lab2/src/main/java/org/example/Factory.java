package org.example;

import org.example.command.*;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;
import java.util.Stack;

public class Factory {
    private static final Logger logger = LogManager.getLogger(Factory.class);
    private final Map<String, Command> commandsCache = new HashMap<>();
    private final Map<String, Double> parametrsOfDefine = new HashMap<>();
    private static final String CONFIG = "/config.properties";


    private void loadCommands() throws Exception {
        try (InputStream inputStream = Factory.class.getResourceAsStream(CONFIG)) {
            Properties properties = new Properties();
            properties.load(inputStream);
            for (String key : properties.stringPropertyNames()) {
                String className = properties.getProperty(key);
                Class<?> clazz = Class.forName(className);
                Command command;
                if (className.equals("org.example.command.Define") || className.equals("org.example.command.Push")) {
                    command = (Command) clazz.getDeclaredConstructor(Map.class)
                            .newInstance(parametrsOfDefine);
                } else {
                    command = (Command) clazz.getDeclaredConstructor().newInstance();
                }
                commandsCache.put(key, command);
            }
        }
    }


    void factory(String str, Stack<Double> stack) throws Exception {
        logger.info("Received command: " + str);
        String commandName = str.split(" ")[0];
        if (!commandsCache.containsKey(commandName)) {
            loadCommands();
        }

        Command cmd = commandsCache.get(commandName);

        try {
            logger.info("Executing command: " + str);
            cmd.performCommand(stack, str);
        } catch (Exception e) {
            logger.error("Error executing command: " + e.getMessage());
            throw e;
        }
    }
}
