package org.example.command;

import java.util.Stack;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.Factory;

public class Pop implements Command {
    private static final Logger logger = LogManager.getLogger(Pop.class);
    @Override
    public void performCommand(Stack<Double> stack, String data) throws Exception{
        logger.info("The start of the Pop command execution");
        Excep excep = new Excep();
        if (stack.empty()) {
            excep.EmptySTack();
        }
        stack.pop();
        logger.info("The number is removed from the stack");
    }
}
