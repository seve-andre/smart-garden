#include "HttpService.h"

#include "HTTPClient.h"

HttpService::HttpService() {}

int HttpService::post() {
    HTTPClient http;
    http.begin("localhost:8080/api/data");
    http.addHeader("Content-Type", "application/json");

    String msg = String("{ \"value\": ") + "value" + "\" }";

    int retCode = http.POST(msg);
    http.end();

    return retCode;
}