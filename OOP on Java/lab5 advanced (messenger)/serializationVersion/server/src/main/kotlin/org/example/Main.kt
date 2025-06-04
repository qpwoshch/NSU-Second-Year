package org.example

import org.apache.logging.log4j.LogManager
import org.apache.logging.log4j.Logger


val logger: Logger = LogManager.getLogger("Main")

fun main() {
    logger.info("The beginning of the program")
    val server = Server()
    server.startServer()
}
