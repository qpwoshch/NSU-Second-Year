package org.example.factory.storage;

import org.example.factory.details.Bodies;

import java.util.LinkedList;
import java.util.Queue;

public class StorageOfBody {
    private Integer bodiesSize;
    private Queue<Bodies> bodies = new LinkedList<>();
    private volatile boolean isRun = true;



    public void setBodySize(int data) {
        this.bodiesSize = data;
    }

    public Integer getCount() {
        return bodies.size();
    }

    public synchronized void put(Bodies body) throws InterruptedException {
        while (bodies.size() >= bodiesSize && isRun) {
            wait();
        }
        if (!isRun) {
            return;
        }
        bodies.add(body);
        notifyAll();
    }

    public synchronized Bodies get() throws InterruptedException {
        while (bodies.isEmpty() && isRun) {
            wait();
        }
        if (!isRun) {
            return null;
        }
        Bodies body = bodies.poll();
        notifyAll();
        return body;
    }

    public void stopThreads() {
        isRun = false;
        synchronized (this) {
            notifyAll();
        }
    }
}
