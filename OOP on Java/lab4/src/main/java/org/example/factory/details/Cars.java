package org.example.factory.details;

import java.util.HashMap;
import java.util.Map;

public class Cars {
    private static int count = 0;
    Map<String, Integer> id = new HashMap<>();

    public Cars(int bodyID, int motorID, int accessoryID) {
        id.put("carID", count++);
        id.put("bodyID", bodyID);
        id.put("motorID", motorID);
        id.put("accessoryID", accessoryID);
    }

    public Map<String, Integer> getID() {
        return id;
    }
}
