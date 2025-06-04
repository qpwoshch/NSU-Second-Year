package org.example;

import java.util.*;

public class Controller {
    public void start() {
        StreamParser parser = new StreamParser();
        Map<String, Counter> words = parser.words();
        ReportGeneration generation = new ReportGeneration();
        List<Map.Entry<String, Counter>> list = generation.generator(words);
        parser.writer(list);
    }
}
