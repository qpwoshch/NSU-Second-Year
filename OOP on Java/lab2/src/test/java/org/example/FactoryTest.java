package org.example;

import org.example.command.Excep;
import org.junit.jupiter.api.Test;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.*;

public class FactoryTest {
    @Test

    void factoryTestCommand() throws Exception {
        Factory factory = new Factory();
        Stack<Double> stack = new Stack<>();
        factory.factory("PUSH 9", stack);
        assertEquals(1, stack.size());
    }
    @Test
    void factoryTestException() throws Exception {
        Factory factory = new Factory();
        Stack<Double> stack = new Stack<>();
        Exception exception = assertThrows(Exception.class, () -> {
            factory.factory("+", stack);
        });
        String expectedMessage = "there are 0 values on the stack, you need at least 2";
        assertTrue(exception.getMessage().contains(expectedMessage));
    }
}
