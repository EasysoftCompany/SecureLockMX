#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "slockmx.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "5pOxXbZBJkpWBFOIeDjsvxMTJtzqrFkF9tvqYAZO"                    // the secret key generated from firebase
#define WIFI_SSID "INFINITUM802D6B"                                          // input your home or public wifi name
#define WIFI_PASSWORD "075369D316"                                    //password of wifi ssid

String FIRESTATUS = "";
int CERRADURA = 3;


void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(12, LOW);
  

  Serial.println("iniciando Wifi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
  delay(10000);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("RECONECTANDO Wifi");
    digitalWrite(2, LOW);
    delay(500);   
    digitalWrite(2, HIGH);
    delay(500);   
    digitalWrite(2, LOW);
    delay(500);   
    digitalWrite(2, HIGH);
  } else {
    
    Serial.println("CONEXION EXITOSA!");                                                
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
    Firebase.setString("LOCK_STATUS","CLOSE");
    
    Serial.println("Enviando estatus close a Firebase");
    delay(1000);   
    digitalWrite(2, LOW);    
    delay(1000);   
    digitalWrite(2, HIGH);
    delay(1000);   
    digitalWrite(2, LOW);
    delay(1000);   
    digitalWrite(2, HIGH);

                                      
  }
}

void loop() {

  
  delay(700);
  FIRESTATUS = Firebase.getString("LOCK_STATUS");

  
  if (FIRESTATUS == "CLOSE") {
    
    Serial.println("CERRADO");
    digitalWrite(12, LOW);
  }
  if (FIRESTATUS == "OPEN") {
    
    Serial.println("ABIERTO");
    digitalWrite(12, HIGH);
  }
}
