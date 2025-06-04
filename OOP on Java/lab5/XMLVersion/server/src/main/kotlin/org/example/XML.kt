package org.example

import org.w3c.dom.Document
import javax.xml.parsers.DocumentBuilderFactory
import org.xml.sax.InputSource
import java.io.StringReader

class XML {
    fun makeXMLMessage(name : String, message : String, time : String) : String {
        return "<event name=\"message\">" +
                "<message>$message</message>" +
                "<name>$name</name>" +
                "<time>$time</time>" +
                "</event>"
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

    fun makeXMLNewClient(name : String) : String {
        return "<event name=\"userlogin\">" +
                "<name>$name</name>" +
                "</event>"
    }

    fun makeXMLLeaveClient(name : String) : String {
        return "<event name=\"userlogout\">" +
                "<name>$name</name>" +
                "</event>"
    }

    fun parseXMLLogin(xml : String) : Map<String, String> {
        val docBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder()
        val inputSource = InputSource(StringReader(xml))
        val document: Document = docBuilder.parse(inputSource)
        val root = document.documentElement
        val name = root.getElementsByTagName("name").item(0)?.textContent ?: ""
        return mapOf(
            "name" to name
        )
    }

    fun success() : String {
        return "<success>" +
                "</success>"
    }

    fun error(e : String) : String {
        return "<error>" +
                "<message>$e</message>" +
                "</error>"
    }

    fun addNewClient(name : String) : String {
        return "<event name=\"add client\">" +
                "<name>$name</name>" +
                "</event>"
    }
}