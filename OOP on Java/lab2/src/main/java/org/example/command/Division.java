package org.example.command;

import java.util.Stack;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.Factory;

public class Division implements Command {
    private static final Logger logger = LogManager.getLogger(Division.class);
    @Override
    public void performCommand(Stack<Double> stack, String data) throws Exception{
        Excep excep = new Excep();
        logger.info("The start of the Division command execution");
        if (stack.size() < 2) {
            excep.NotEnoughValuesOnStack(stack.size());
        }
        double a = stack.pop();
        double b = stack.pop();
        if (a == 0.0) {
            String error = "It cannot be divided by 0";
            logger.error("Error: " + error);
            throw new Exception(error);
        }
        stack.push(b/a);
        logger.info("The division of the numbers " +  b + " by the number " + a);
    }
}
