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

enum { NORMAL,
       ALARM } state;

void setup() {
    // hardware
    tempSensor = new TempSensorLM35(TEMP_SENSOR_PIN);
    lightSensor = new LightSensorImpl(PHOTORESISTOR_PIN);
    led = new Led(LED_PIN);

    // http
    wifiConnector = new WifiConnector(WIFI_SSID, PASSWORD);
    wifiConnector->connect();
    httpService = new HttpService();

    state = NORMAL;
}

void loop() {
    if (wifiConnector->isConnected()) {
        switch (state) {
            case NORMAL: {
                int lightIntensity = lightSensor->getLightIntensity();
                int temperatureMapped = map(tempSensor->getTemperature(), 0, 30, 1, 5);

                // post lightIntensity, temperatureMapped, state
                int postCode = httpService->post(lightIntensity, temperatureMapped, "auto");

                if (postCode == 200) {
                    Serial.println("ok");
                } else {
                    Serial.println(String("error: ") + postCode);
                }

                // add check for irrigation system pause
                if (temperatureMapped == 5) {
                    // ALARM
                    state = ALARM;
                }
                led->switchOn();
                break;
            }

            case ALARM: {
                led->switchOff();
                if (httpService->getState() == "auto") {
                    state = NORMAL;
                }
                break;
            }
        }
        delay(5000);
    } else {
        Serial.println("WiFi Disconnected... Reconnect.");
        wifiConnector->connect();
    }
}
