#include "HttpService.h"

#include <ArduinoJson.h>

#include "HTTPClient.h"

DynamicJsonDocument jsonPost(1024);
char msg[100];

HttpService::HttpService() {
}

int HttpService::post(int lightIntensity, int temperatureMapped, String state) {
    HTTPClient http;
    http.begin("https://3e3b-95-244-50-244.eu.ngrok.io/api/data");
    http.addHeader("Content-Type", "application/json");

    jsonPost["intensity"] = lightIntensity;
    jsonPost["temperature"] = temperatureMapped;
    jsonPost["state"] = state;

    serializeJson(jsonPost, msg);

    int retCode = http.POST(msg);
    http.end();

    return retCode;
}
