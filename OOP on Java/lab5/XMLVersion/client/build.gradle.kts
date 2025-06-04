plugins {
    kotlin("jvm") version "2.1.0"
    application
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

application {
    mainClass.set("org.example.MainKt")
}

dependencies {
    implementation(kotlin("stdlib"))
    implementation("org.apache.logging.log4j:log4j-api:2.20.0")
    implementation("org.apache.logging.log4j:log4j-core:2.20.0")

    implementation(fileTree("C:/Users/User/all_projects/java/javafx-sdk-24/lib") {
        include("*.jar")
    })

    testImplementation(platform("org.junit:junit-bom:5.10.0"))
    testImplementation("org.junit.jupiter:junit-jupiter")
}

tasks.test {
    useJUnitPlatform()
}

kotlin {
    jvmToolchain(23)
}

tasks.named<JavaExec>("run") {
    jvmArgs = listOf(
        "--module-path", "C:/Users/User/all_projects/java/javafx-sdk-24/lib",
        "--add-modules", "javafx.controls,javafx.fxml"
    )
}