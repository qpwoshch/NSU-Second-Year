package org.example;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.*;

class ReportGenerationTest {

    @Test
    void testGenerator() {
        Map<String, Counter> words = new HashMap<>();
        words.put("word1", new Counter());
        words.put("word2", new Counter());
        words.get("word1").increment();
        words.get("word2").increment();
        words.get("word2").increment();

        ReportGeneration reportGen = new ReportGeneration();
        List<Map.Entry<String, Counter>> sortedList = reportGen.generator(words);

        assertEquals("word2", sortedList.get(0).getKey());
        assertEquals("word1", sortedList.get(1).getKey());
    }
}
