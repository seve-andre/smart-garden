
<div align="center">
  <img src="https://github.com/seve-andre/smart-garden/blob/main/schema.jpg" alt="subsystems schema" height="300" />
</div>

# Smart Garden
IoT smart garden, i.e. a smart system monitoring and controlling the state of a garden

The system is composed of **5 subsystems**:
- [Sensorboard]:
  - monitors the state of the garden by using a set of sensors:
    - [LM35](https://www.google.com/search?q=lm35+temperature+sensor): to retrieve temperature
    - [LDR-VT90](https://www.google.com/search?q=photoresistor): photoresistor to measure brightness of the ambient light
  - interacts via HTTP with the [Service] to send sensors data

- [Service]:
  - main control unit that manages the garden
  - interacts:
    - via the serial line with the [Controller]
    - via HTTP with the [SensorBoard]
    - via HTTP with the [Dashboard]

- [Controller]:
  - controls the irrigation system and lighting
  - interacts:
    - via serial line with the [Service]
    - via Bluetooth with the [Android app]

- [Android app]:
  - makes it possible to manually control the irrigation system and lighting
  - interacts:
    - via Bluetooth with the [Controller]
    - via HTTP with the [Service]

- [Dashboard]:
  - frontend to visualise and track the state of the garden
  - interacts with the [Service] to get the data

## Hardware components
- [Sensorboard]:
  - [esp32-s3-devkitc-1](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/hw-reference/esp32s3/user-guide-devkitc-1.html) board, including:
    - a green led
    - [LM35](https://www.google.com/search?q=lm35+temperature+sensor) temperature sensor
    - [LDR-VT90](https://www.google.com/search?q=photoresistor) photoresistor
    
- [Controller]:
  - [Arduino uno](https://store.arduino.cc/products/arduino-uno-rev3) board, including:
    - 4 green leds
    - servo motor CONTINUE
    - HC05 Bluetooth module
## Behaviour


---
Assignment #3 [Embedded Systems and IoT](https://www.unibo.it/en/teaching/course-unit-catalogue/course-unit/2021/470158) - [Computer Science and Engineering](https://corsi.unibo.it/1cycle/ComputerScienceEngineering) 2021/22 UniBo
- [more detailed version](https://docs.google.com/document/d/1oD8VSHPsmvpfgtXeALszZn8Bt9sD60pmsZQmUkinLm0/edit)
- [demo](https://liveunibo-my.sharepoint.com/:v:/g/personal/andrea_severi12_studio_unibo_it/Ebr-YQ9bWPhForXCmn0dCDIBFiw2Ak20UQRDlxhNdCWyyQ?e=LvFZex)

<!-- Links -->
[Sensorboard]: https://github.com/seve-andre/smart-garden/tree/main/garden-sensorboard
[Service]: https://github.com/seve-andre/smart-garden/tree/main/garden-service
[Controller]: https://github.com/seve-andre/smart-garden/tree/main/garden-controller
[Android app]: https://github.com/seve-andre/smart-garden/tree/main/garden-app
[Dashboard]: https://github.com/seve-andre/smart-garden/tree/main/garden-dashboard
