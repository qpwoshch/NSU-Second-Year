package org.example.command;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class Excep {
    private static final Logger logger = LogManager.getLogger(Division.class);

    public void NotEnoughValuesOnStack(Integer size) throws Exception {
        String error = "there are " + size +  " values on the stack, you need at least 2";
        logger.error("Error: " + error);
        throw new Exception(error);
    }

    public void EmptySTack() throws Exception {
        String error = "Stack is empty";
        logger.error("Error: " + error);
        throw new Exception(error);
    }
}
