package org.example.command;

import java.util.Stack;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.Factory;

public class Plus implements Command {
    private static final Logger logger = LogManager.getLogger(Plus.class);
    @Override
    public void performCommand(Stack<Double> stack, String data) throws Exception {
        logger.info("The start of the Plus command execution");
        Excep excep = new Excep();
        if (stack.size() < 2) {
            excep.NotEnoughValuesOnStack(stack.size());
        }
        double a = stack.pop();
        double b = stack.pop();
        stack.push(a+b);
        logger.info("Added of the number " +  a + " by the number " +  b);
    }
}
