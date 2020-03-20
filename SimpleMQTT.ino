#include <ESP8266WiFi.h>
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson (use v6.xx)
#include <ESP8266AWSIoTMQTTWS.h>  //https://github.com/debsahu/esp8266-arduino-aws-iot-ws
                                  //https://github.com/Links2004/arduinoWebSockets
                                  //https://projects.eclipse.org/projects/technology.paho/downloads (download Arduino version)

const char *ssid = "Nobelium";
const char *password = "pointblank";

// See `src/aws_iot_config.h` for formatting
char *region = (char *) "us-east-1";
char *endpoint = (char *) "ag74md295t9zg-ats";
char *mqttHost = (char *) "ag74md295t9zg-ats.iot.us-east-1.amazonaws.com";
int mqttPort = 443;
char *iamKeyId = (char *) "AKIAJKTNKGV5DQXH3L7A";
char *iamSecretKey = (char *) "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";
const char* aws_topic  = "$aws/things/YouTubeTest/shadow/update";

ESP8266DateTimeProvider dtp;
AwsIotSigv4 sigv4(&dtp, region, endpoint, mqttHost, mqttPort, iamKeyId, iamSecretKey);
AWSConnectionParams cp(sigv4);
AWSWebSocketClientAdapter adapter(cp);
AWSMqttClient client(adapter, cp);

void setup() {

    Serial.begin(115200);
    while(!Serial) {
        yield();
    }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    int res = client.connect();
    Serial.printf("mqtt connect=%d\n", res);

    if (res == 0) {
      client.subscribe(aws_topic, 1,
        [](const char* topic, const char* msg)
        { Serial.printf("Got msg '%s' on topic %s\n", msg, topic); }
      );
    }
}

void loop() {
  if (client.isConnected()) {
    DynamicJsonDocument jsonBuffer;
    JsonObject& root = jsonBuffer.to<JsonObject>();
    JsonObject& state = root.createNestedObject("state");
    JsonObject& state_reported = state.createNestedObject("reported");
    state_reported["value"] = random(100);
    serializeJson(root, Serial);
    Serial.println();
    String shadow;
    serializeJson(root, shadow);

    client.publish(aws_topic, shadow.c_str(), 0, false);
    client.yield();

  } else {
    Serial.println("Not connected...");
    delay(2000);
  }

  delay(30000);
}
