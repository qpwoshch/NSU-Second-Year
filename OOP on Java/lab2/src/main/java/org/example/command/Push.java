package org.example.command;

import java.util.Map;
import java.util.Stack;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.Factory;

public class Push implements Command {
    private static final Logger logger = LogManager.getLogger(Push.class);
    private final Map<String, Double> parametrsOfDefine;
    public Push(Map<String, Double> parametrsOfDefine) {
        this.parametrsOfDefine = parametrsOfDefine;
    }
    @Override
    public void performCommand(Stack<Double> stack, String data) throws Exception{
        logger.info("The start of the Push command execution");
        String a = data.split(" ")[1];
        if (parametrsOfDefine.containsKey(a)) {
            stack.push(parametrsOfDefine.get(a));
            logger.info("Number " + parametrsOfDefine.get(a) + " added to stack");
        }
        else {
            try {
                stack.push(Double.parseDouble(a));
                logger.info("Number " + Double.parseDouble(a) + " added to stack");
            } catch(NumberFormatException e) {
                String error = "Enter the number with the parameter";
                logger.error("Error: " + error);
                throw new Exception(error);
            }
        }
    }
}
