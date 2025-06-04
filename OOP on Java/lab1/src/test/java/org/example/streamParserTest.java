package org.example;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.*;

import java.io.*;

class StreamParserTest {

    @Test
    void testNextWord() throws IOException {
        StringReader reader = new StringReader("word1 word2 word3");
        StreamParser parser = new StreamParser();
        assertEquals("word1", parser.NextWord(reader).toString());
        assertEquals("word2", parser.NextWord(reader).toString());
        assertEquals("word3", parser.NextWord(reader).toString());
    }

    @Test
    void testWordsCount() {
        StreamParser parser = new StreamParser();
        Map<String, Counter> words = parser.words();
        assertNotNull(words);
        assertTrue(words.size() > 0);
    }
}
