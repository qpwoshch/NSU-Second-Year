package org.example

class History {
    private val history : MutableList<Message> = mutableListOf()

    fun addMessage(message : Message) {
        if (history.size == 14) {
            history.removeAt(0)
        }
        history.add(message)
    }

    fun getHistory() : MutableList<Message> {
        return history
    }
}