package org.example;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class CounterTest {

    @Test
    void testIncrement() {
        Counter counter = new Counter();
        assertEquals(0, counter.getCounter());
        counter.increment();
        assertEquals(1, counter.getCounter());

        counter.increment();
        assertEquals(2, counter.getCounter());
    }

    @Test
    void testGetCounter() {
        Counter counter = new Counter();
        assertEquals(0, counter.getCounter());

        counter.increment();
        assertEquals(1, counter.getCounter());
    }
}
