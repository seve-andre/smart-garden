#include <Arduino.h>

#include "Config.h"
#include "components/http/HttpService.h"
#include "components/http/WifiConnector.h"
#include "components/led/Led.h"
#include "components/photoresistor/LightSensor.h"
#include "components/photoresistor/LightSensorImpl.h"
#include "components/temperature/TempSensor.h"
#include "components/temperature/TempSensorLM35.h"

// hardware components
TempSensor* tempSensor;
LightSensor* lightSensor;
Led* led;

// http
HttpService* httpService;
WifiConnector* wifiConnector;

void setup() {
    // hardware
    tempSensor = new TempSensorLM35(TEMP_SENSOR_PIN);
    lightSensor = new LightSensorImpl(PHOTORESISTOR_PIN);
    led = new Led(LED_PIN);

    // http
    wifiConnector = new WifiConnector("", "");
    wifiConnector->connect();
    httpService = new HttpService();
}

void loop() {
    if (wifiConnector->isConnected()) {
        int lightIntensity = lightSensor->getLightIntensity();

        if (lightIntensity < 5) {
            // turn led1 and led2 on, set intensity for the other 2
            // httpService->post();

            if (lightIntensity < 2) {
                // activate irrigation system (servo)
                // httpService->post();
            }
        }

        float temperature = tempSensor->getTemperature();
        int temperatureMapped = map(temperature, 0, 30, 1, 5);

        if (temperatureMapped == 5 /* && pause */) {
            // ALARM
            // httpService->post();
            led->switchOff();
        } else {
            // send temperature mapped
            // httpService->post();
        }
    } else {
        Serial.println("WiFi Disconnected... Reconnect.");
        wifiConnector->connect();
    }
}
