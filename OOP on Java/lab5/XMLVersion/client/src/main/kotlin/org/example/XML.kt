package org.example

import org.w3c.dom.Document
import javax.xml.parsers.DocumentBuilderFactory
import org.xml.sax.InputSource
import java.io.StringReader

class XML {
    fun login(name : String) : String {
        return "<command name=\"login\">" +
                "<name>$name</name>" +
                "</command>"
    }

    fun parseAnswer(xml : String) : Map<String, String> {
        val docBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder()
        val inputSource = InputSource(StringReader(xml))
        val document: Document = docBuilder.parse(inputSource)
        val root = document.documentElement
        if (root.nodeName == "success") {
            return mapOf(
                "answer" to "true",
                "error" to ""
            )
        }
        val errorMessage = root.getElementsByTagName("message").item(0)?.textContent ?: "Unknown error"
        return mapOf(
            "answer" to "false",
            "error" to errorMessage
        )
    }

    fun makeXMLMessage(name : String, message : String, time : String) : String {
        return "<event name=\"message\">" +
                "<message>$message</message>" +
                "<name>$name</name>" +
                "<time>$time</time>" +
                "</event>"
    }

    fun getCommand(xml : String) : String {
        val docBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder()
        val inputSource = InputSource(StringReader(xml))
        val document: Document = docBuilder.parse(inputSource)
        val root = document.documentElement
        return root.getAttribute("name")
    }

    fun parseXMLMessage(xml : String) : Map<String, String> {
        val docBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder()
        val inputSource = InputSource(StringReader(xml))
        val document: Document = docBuilder.parse(inputSource)
        val root = document.documentElement
        val eventType = root.getAttribute("name")
        val message = root.getElementsByTagName("message").item(0)?.textContent ?: ""
        val name = root.getElementsByTagName("name").item(0)?.textContent ?: ""
        val time = root.getElementsByTagName("time").item(0)?.textContent ?: ""
        return mapOf(
            "type" to eventType,
            "message" to message,
            "name" to name,
            "time" to time
        )
    }

    fun parseXMLLoginOrLogout(xml : String) : Map<String, String> {
        val docBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder()
        val inputSource = InputSource(StringReader(xml))
        val document: Document = docBuilder.parse(inputSource)
        val root = document.documentElement
        val eventType = root.getAttribute("name")
        val name = root.getElementsByTagName("name").item(0)?.textContent ?: ""
        return mapOf(
            "type" to eventType,
            "name" to name
        )
    }
}