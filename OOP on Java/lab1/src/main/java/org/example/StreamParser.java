package org.example;


import java.io.*;
import java.util.*;

public class StreamParser {
    public int quantityOfWords = 0;

    public StringBuilder NextWord(Reader reader) {
        StringBuilder word = new StringBuilder();
        int symbol;
        try {
            while ((symbol = reader.read()) != -1) {
                char ch = (char) symbol;
                if (Character.isLetterOrDigit(ch)) {
                    word.append(ch);
                } else if (word.length() > 0) {
                    break;
                }
            }

        } catch (IOException e) {
            System.err.println("Error while reading file" + e.getMessage());
        }
        return word;
    }

    public void reader(Map<String, Counter> words) {
        StringBuilder word = new StringBuilder();
        try (Reader reader = new InputStreamReader(new FileInputStream("input.txt"))) {
            while (reader.ready()) {
                word.setLength(0);
                word = NextWord(reader);
                if (word.length() > 0) {
                    String key = word.toString();
                    Counter counter = words.getOrDefault(key, new Counter());
                    counter.increment();
                    words.put(key, counter);
                    quantityOfWords++;
                }
            }
        } catch (IOException e) {
            System.err.println("Error while reading file" + e.getMessage());
        }
    }

    public Map<String, Counter> words() {
        Map<String, Counter> words = new HashMap<String, Counter>();
        reader(words);
        return words;
    }

    public void writer(List<Map.Entry<String, Counter>> list) {
        try (Writer writer = new OutputStreamWriter(new FileOutputStream("output.csv"))) {
            writer.write("word;count;%\n");
            for (Map.Entry<String, Counter> entry : list) {
                double percent = (double) entry.getValue().getCounter() / ((double) quantityOfWords / 100);
                writer.write(entry.getKey() + ";" + entry.getValue().getCounter() + ";" + String.format("%.3f", percent) + "\n");
            }
        } catch (IOException e) {
            System.err.println("Error while writing file" + e.getMessage());
        }
    }

}
