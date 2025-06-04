package org.example;

import java.util.*;

public class ReportGeneration {
    public List generator(Map<String, Counter> words) {
        List<Map.Entry<String, Counter>> list = new ArrayList<>(words.entrySet());
        list.sort((entry1, entry2) -> Integer.compare(entry2.getValue().getCounter(), entry1.getValue().getCounter()));
        return list;
    }
}
