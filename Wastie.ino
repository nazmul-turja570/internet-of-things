#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "wastie-9b3e2.firebaseio.com"
//#define FIREBASE_HOST "hawkbit-9eefb.firebaseio.com"
#define FIREBASE_AUTH "kCOStqKEGyV559ndYPne2FEdVu04TMmeTO5bG7AK"
//#define FIREBASE_AUTH "B6vj9ipfFz5Oj4WhyVaYll4S0bhMzE6GSOhiQg2k"
#define WIFI_SSID "Nobelium"
#define WIFI_PASSWORD "pointblank"

#define ADDRESS "dustbin1"

#define trigPin D0
#define echoPin D1

#define LED_25 D2
#define LED_50 D3
#define LED_75 D4
#define LED_100 D5

#define multi (0.034/2)
#define level1  50
#define level2  45
#define level3  40
#define level4  35
#define level5  30
#define level6  25
#define level7  20
#define level8  15
#define level9  10
#define level10 5
//level10 < level1

long duration;
int distance;
int state;
int state_buffer[3] = {1,1,1};
int sonar_data;
//String chipId = " Chip/Hawkbit2";

void setup() {
  Serial.begin(9600);
  //Set pins
 // pinMode(D0, INPUT);
  // for LED
  pinMode(LED_25, OUTPUT);
  pinMode(LED_50, OUTPUT);
  pinMode(LED_75, OUTPUT);
  pinMode(LED_100, OUTPUT);
  //for Sonar
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void set_Data(){

  // set value
  Firebase.setFloat(ADDRESS, sonar_data);
}

int get_data_from_sonar(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration* multi;
 
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
 
  //Figuring Out State
  state_buffer[0] = state_buffer[1];
  state_buffer[1] = state_buffer[2];
 
  if (distance <= level10)
    state_buffer[2] = 10;
  else if (distance <= level9)
    state_buffer[2] = 9;
  else if (distance <= level8)
    state_buffer[2] = 8;
  else if (distance <= level7)
    state_buffer[2] = 7;
  else if (distance <= level6)
    state_buffer[2] = 6;
  else if (distance <= level5)
    state_buffer[2] = 5;
  else if (distance <= level4)
    state_buffer[2] = 4;
  else if (distance <= level3)
    state_buffer[2] = 3;
  else if (distance <= level2)
    state_buffer[2] = 2;
  else if (distance <= level1)
    state_buffer[2] = 1;
  else
    state_buffer[2] = 0; //JITTER
 
//Change state if the state value stays consistent for 3 readings
  if (state_buffer[0] == state_buffer[1] && state_buffer[1] == state_buffer[2])
    state = state_buffer[1];

  delay(50);
  return state;
}

void led_driver(){
  digitalWrite(LED_25, LOW);
  digitalWrite(LED_50, LOW);
  digitalWrite(LED_75, LOW);
  digitalWrite(LED_100, LOW);

  if(sonar_data == 1 || sonar_data == 2 || sonar_data == 3 || sonar_data == 0){
    digitalWrite(LED_25, HIGH);
  }
  else if(sonar_data == 4 || sonar_data == 5){
    digitalWrite(LED_50, HIGH);
  }
  else if(sonar_data == 6 || sonar_data == 7){
    digitalWrite(LED_75, HIGH);
  }
  else{
    digitalWrite(LED_100, HIGH);
  }
}

void loop(){
  sonar_data = get_data_from_sonar();
  led_driver();
  set_Data();
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(50);
}
