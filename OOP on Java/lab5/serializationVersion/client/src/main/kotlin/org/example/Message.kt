package org.example

import java.io.Serializable

data class Message (
    val name : String,
    val message: String,
    val time : String,
    val key : String
) : Serializable {
    companion object {
        private const val serialVersionUID: Long = 1L
    }
}