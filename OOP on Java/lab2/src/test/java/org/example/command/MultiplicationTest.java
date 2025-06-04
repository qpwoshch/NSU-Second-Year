package org.example.command;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;


public class MultiplicationTest {
    @Test
    void testPerformMult() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Multiplication multiplication = new Multiplication();
        Push push = new Push(parametrsOfDefine);
        push.performCommand(stack, "PUSH 8");
        push.performCommand(stack, "PUSH 7");
        multiplication.performCommand(stack, "*");
        assertEquals(56, stack.peek());
    }

    @Test
    void testWithZeroValuesOnStack() {
        Stack<Double> stack = new Stack<>();
        Multiplication multiplication = new Multiplication();
        Exception exception = assertThrows(Exception.class, () -> {
            multiplication.performCommand(stack, "-");
        });
        String expectedMessage = "there are 0 values on the stack, you need at least 2";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
}
