package org.example.command;

import java.util.Stack;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.Factory;

public class Minus implements Command {
    private static final Logger logger = LogManager.getLogger(Minus.class);
    @Override
    public void performCommand(Stack<Double> stack, String data) throws Exception{
        Excep excep = new Excep();
        logger.info("The start of the Minus command execution");
        if (stack.size() < 2) {
            excep.NotEnoughValuesOnStack(stack.size());
        }
        double a = stack.pop();
        double b = stack.pop();
        stack.push(b-a);
        logger.info("Subtraction of the number " + a + " from among " + b);
    }
}
