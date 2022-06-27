#include "HttpService.h"

#include <ArduinoJson.h>

#include "HTTPClient.h"

DynamicJsonDocument jsonPost(1024);
char msg[100];

HttpService::HttpService() {
}

int HttpService::post(int intensity) {
    HTTPClient http;
    http.begin("https://d3e0-80-182-124-4.eu.ngrok.io/api/data");
    http.addHeader("Content-Type", "application/json");

    jsonPost["intensity"] = intensity;

    serializeJson(jsonPost, msg);

    int retCode = http.POST(msg);
    http.end();

    return retCode;
}
