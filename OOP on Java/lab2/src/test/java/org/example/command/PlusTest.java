package org.example.command;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;


public class PlusTest {
    @Test
    void testPerformPlus() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Plus plus = new Plus();
        Push push = new Push(parametrsOfDefine);
        push.performCommand(stack, "PUSH 8");
        push.performCommand(stack, "PUSH 7");
        plus.performCommand(stack, "+");
        assertEquals(15, stack.peek());
    }
    @Test
    void TestWithZeroValuesOnStack() throws Exception {
        Stack<Double> stack = new Stack<>();
        Plus plus = new Plus();
        Exception exception = assertThrows(Exception.class, () -> {
            plus.performCommand(stack, "POP");
        });
        String expectedMessage = "there are 0 values on the stack, you need at least 2";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
}
