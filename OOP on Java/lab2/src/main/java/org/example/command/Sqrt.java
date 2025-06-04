package org.example.command;

import java.util.Stack;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.Factory;

public class Sqrt implements Command {
    private static final Logger logger = LogManager.getLogger(Sqrt.class);
    @Override
    public void performCommand(Stack<Double> stack, String data) throws Exception{
        logger.info("The start of the Sqrt command execution");
        Excep excep = new Excep();
        if (stack.empty()) {
            excep.EmptySTack();
        }
        double a = stack.pop();
        if (a < 0) {
            String error = "Number " + a + "<0, but the number must be non-negative";
            logger.error("Error: " + error);
            throw new Exception(error);
        }
        logger.info("Take the root from number " + a);
        a = Math.sqrt(a);
        stack.push(a);
    }
}
