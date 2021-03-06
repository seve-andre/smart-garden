plugins {
    id("java")
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation("org.junit.jupiter:junit-jupiter-api:5.8.1")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine:5.8.1")


    implementation("io.vertx:vertx-core:4.2.6")
    implementation("io.vertx:vertx-web:4.2.6")
    implementation("io.vertx:vertx-web-client:4.2.6")
    implementation("io.vertx:vertx-mqtt:4.2.6")
}

tasks.getByName<Test>("test") {
    useJUnitPlatform()
}
