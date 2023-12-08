# Qt_mqtt
Приложение считывает файл построчно и отправляет в MQTT брокер

## MQTT Module install
Чтобы добавить mqtt в Qt необходимо:
    - перейти в папку ~/Qt/{version_qt}/Src (cd ~/Qt/{version_qt}/Src)
    - клонировать репозиторий git clone https://github.com/qt/qtmqtt.git
    - выполнить след команды 
        * cd qtmqtt
        * mkdir build && cd build
        * ~/Qt/{version_qt}/gcc_64/bin/qmake -r .. 
        * make install

## MQTT Module usage
Чтобы добавить модуль mqtt необходимо в pro файле вашего проекта добавить 
    - QT += mqtt
В вашем классе добавить следующие заголовки
    #include <QtMqtt/QMqttClient>
    #include <QtMqtt/QMqttMessage>
    #include <QtMqtt/QMqttSubscription>
