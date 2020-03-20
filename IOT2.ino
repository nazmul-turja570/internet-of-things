#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

int leds[5]={D0,D1,D2,D3,D4};
int fans[5]={D5,D6,D7,D8,D9};
String idx[20]={"00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19"};
int tot=18;
// Set these to run example.
//#define FIREBASE_HOST "billis-bc8c2.firebaseio.com"
#define FIREBASE_HOST "hawkbit-9eefb.firebaseio.com"
//#define FIREBASE_AUTH "yzV7U7rijVvqXPK4YbCIl2v43cRvMtDWRz4C2IEP"
#define FIREBASE_AUTH "B6vj9ipfFz5Oj4WhyVaYll4S0bhMzE6GSOhiQg2k"
#define WIFI_SSID "Nobelium"
#define WIFI_PASSWORD "pointblank"
#define LED_NO 5
#define FAN_NO 5
#define Multiplier .8
#define Offset 100

String chipId = " Chip/Hawkbit2";

void setup() {
  Serial.begin(9600);
  //Set pins
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);

  // connect to wifi.
//  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }
//  Serial.println();
//  Serial.print("connected: ");
//  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void getData(){

  String path1 = chipId + "/L/001";
  FirebaseObject object1 = Firebase.get(path1);
  idx[0]=object1.getString("State");
  idx[1]=object1.getString("Value");
//  Serial.println(idx[0]);
//  Serial.println(idx[1]);
  //
  String path2 = chipId + "/L/002";
  FirebaseObject object2 = Firebase.get(path2);
  idx[2]=object2.getString("State");
  idx[3]=object2.getString("Value");
//  Serial.println(idx[2]);
//  Serial.println(idx[3]);
  //
  String path3 = chipId+"/L/003";
  FirebaseObject object3= Firebase.get(path3);
  idx[4]=object3.getString("State");
  idx[5]=object3.getString("Value");
//  Serial.println(idx[4]);
//  Serial.println(idx[5]);
//  //
  String path4 = chipId+"/L/004";
  FirebaseObject object4 = Firebase.get(path4);
  idx[6]=object4.getString("State");
  idx[7]=object4.getString("Value");
//  Serial.println(idx[6]);
//  Serial.println(idx[7]);
//  //
  String path5 = chipId+"/L/005";
  FirebaseObject object5 = Firebase.get(path5);
  idx[8]=object5.getString("State");
  idx[9]=object5.getString("Value");
//  Serial.println(idx[8]);
//  Serial.println(idx[9]);
//  //
  String path11 = chipId+"/F/001";
  FirebaseObject object11 = Firebase.get(path11);
  idx[10]=object11.getString("State");
  idx[11]=object11.getString("Value");
//  Serial.println(idx[10]);
//  Serial.println(idx[11]);
//  //
  String path12 = chipId+"/F/002";
  FirebaseObject object12 = Firebase.get(path12);
  idx[12]=object12.getString("State");
  idx[13]=object12.getString("Value");
//  Serial.println(idx[12]);
//  Serial.println(idx[13]);
//  //
  String path13 = chipId+"/F/003";
  FirebaseObject object13 = Firebase.get(path13);
  idx[14]=object13.getString("State");
  idx[15]=object13.getString("Value");
//  Serial.println(idx[14]);
//  Serial.println(idx[15]);
//  //
  String path14 = chipId+"/F/004";
  FirebaseObject object14 = Firebase.get(path14);
  idx[16]=object14.getString("State");
  idx[17]=object14.getString("Value");
//  Serial.println(idx[16]);
//  Serial.println(idx[17]);
    String path15 = chipId+"/F/005";
  FirebaseObject object15 = Firebase.get(path15);
  idx[18]=object15.getString("State");
  idx[19]=object15.getString("Value");
  

  //String inString = object.getString("State");
  //Serial.println("2");
  //Serial.println(object.getString("State"));
  //Serial.println("1");
  for (int i=0;i<LED_NO;i++){
    //if(object.getString(idx[2*i]).toInt())
     if(idx[2*i].toInt())
    {
      //analogWrite(leds[i],object.getString(idx[2*i+1]).toInt());
      analogWrite(leds[i],idx[2*i+1].toInt());
    }
    else
    {
      analogWrite(leds[i],0);
    }
    
      
  }
  for (int i=0;i<FAN_NO;i++){
    //if(object.getString(idx[2*i+10]).toInt())
    if(idx[2*i+10].toInt())
    {
      //analogWrite(fans[i],object.getString(idx[2*i+11]).toInt());
      analogWrite(fans[i],(Offset+idx[2*i+11].toInt()/Multiplier));
    }
    else
    {
      analogWrite(fans[i],0);
    }
      
  }
  
  //int led1= inString.toInt();
  //bool led2 = object.getBool("002");
  //bool led3 = object.getBool("003");
  //bool led4 = object.getBool("004");
  //bool led5 = object.getBool("005");

//  Serial.println("led 1: ");
//  Serial.println(led1);
//
//  //
//  Serial.println();
//  Serial.println("led 2: ");
//  Serial.println(led2);
//
//  //
//  Serial.println();
//  Serial.println("led 3: ");
//  Serial.println(led3);
//  //
//  Serial.println();
//  Serial.println("led 4: ");
//  Serial.println(led4);
//  //
//  Serial.println();
//  Serial.println("led 5: ");
//  Serial.println(led5);
  //
//  digitalWrite(leds[0],led1);
//  digitalWrite(leds[1],led2);
  //digitalWrite(leds[2],led3);
  //digitalWrite(leds[3],led4);
  //digitalWrite(leds[4],led5);
}

void loop(){
  getData();
//  if (Firebase.failed()){
//    Serial.println("Failed");
//  }
  delay(1500);
}
//void loop() {
//  int value=Firebase.getInt("F1");
//  analogWrite(D0,value);
//  
//  if (Firebase.failed()){
//    Serial.println("Failed");
//  }
//  delay(1000);
//}
