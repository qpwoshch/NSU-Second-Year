package org.example

class History {
    private val history : MutableList<String> = mutableListOf()

    fun addMessage(message : String) {
        if (history.size == 14) {
            history.removeAt(0)
        }
        history.add(message)
    }

    fun getHistory() : MutableList<String> {
        return history
    }
}