package org.example.Model;

import java.util.*;

public class HighScore {
    private Map<String, Integer> tableOfHighScore = new LinkedHashMap<>(11);

    public StringBuilder getHighScore() {
        StringBuilder listOfHighScores = new StringBuilder();
        for (Map.Entry<String, Integer> pair : tableOfHighScore.entrySet()) {
            listOfHighScores.append(pair.getKey()).append(" ").append(pair.getValue()).append("\n");
        }
        listOfHighScores.deleteCharAt(listOfHighScores.length() - 1);
        return listOfHighScores;
    }

    public void sort() {
        List<Map.Entry<String, Integer>> list = new ArrayList<>(tableOfHighScore.entrySet());
        list.sort((entry1, entry2) -> Integer.compare(entry1.getValue(), entry2.getValue()));
        tableOfHighScore.clear();
        for (int i = 0; i < Math.min(list.size(), 10); i++) {
            tableOfHighScore.put(list.get(i).getKey(), list.get(i).getValue());
        }
    }

    public void setHighScore(String nameOfPerson, Integer time) {
        tableOfHighScore.put(nameOfPerson, time);
        sort();
    }
}
