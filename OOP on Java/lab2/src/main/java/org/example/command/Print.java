package org.example.command;

import java.util.Stack;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.Factory;

public class Print implements Command {
    private static final Logger logger = LogManager.getLogger(Print.class);
    @Override
    public void performCommand(Stack<Double> stack, String data) throws Exception{
        logger.info("The start of the Print command execution");
        Excep excep = new Excep();
        if (stack.empty()) {
            excep.EmptySTack();
        }
        double a = stack.peek();
        System.out.println(a);
        logger.info("The number is printed");
    }
}
