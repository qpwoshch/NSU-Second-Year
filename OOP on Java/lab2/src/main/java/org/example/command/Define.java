package org.example.command;



import java.util.Map;
import java.util.Stack;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.Factory;

public class Define implements Command {
    private final Map<String, Double> parametrsOfDefine;
    private static final Logger logger = LogManager.getLogger(Define.class);
    public Define(Map<String, Double> parametrsOfDefine) {
        this.parametrsOfDefine = parametrsOfDefine;
    }
    @Override
    public void performCommand(Stack<Double> stack, String data) throws Exception {
        logger.info("The start of the Define command execution");
        Double value = 0.0;
        String parametrs = data.split(" ")[1];
        try {
            value = Double.parseDouble(data.split(" ")[2]);
        } catch (NumberFormatException e) {
            String error = "Enter the number with the second parameter";
            logger.error("Error: " + error);
            throw new Exception(error);
        }
        parametrsOfDefine.put(parametrs, value);
        logger.info("Added parameter value " + parametrs);
    }
}
