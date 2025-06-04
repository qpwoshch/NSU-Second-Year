package org.example.command;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;

public class PopTest {
    @Test
    void TestPerformPop() throws Exception {
        Stack<Double> stack = new Stack<>();
        Map<String, Double> parametrsOfDefine = new HashMap<>();
        Pop pop = new Pop();
        Push push = new Push(parametrsOfDefine);
        push.performCommand(stack, "PUSH 8");
        push.performCommand(stack, "PUSH 9");
        pop.performCommand(stack, "POP");
        assertEquals(8.0, stack.peek());
    }
    @Test
    void testWithEmptyStack() throws Exception {
        Stack<Double> stack = new Stack<>();
        Pop pop = new Pop();
        Exception exception = assertThrows(Exception.class, () -> {
            pop.performCommand(stack, "POP");
        });
        String expectedMessage = "Stack is empty";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
}
