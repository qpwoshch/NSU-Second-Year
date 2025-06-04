package org.example.command;

import java.util.Stack;

public interface Command {
    void performCommand(Stack<Double> stack, String data) throws Exception;
}
