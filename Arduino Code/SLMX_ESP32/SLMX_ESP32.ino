#include <WiFi.h>                                                // esp32 library

#include <IOXhop_FirebaseESP32.h>                                             // firebase library

#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial ESP_BT; //Object for Bluetooth

#define FIREBASE_HOST "slockmx.firebaseio.com"                         // the project name address from firebase id

#define FIREBASE_AUTH "5pOxXbZBJkpWBFOIeDjsvxMTJtzqrFkF9tvqYAZO"                    // the secret key generated from firebase

#define WIFI_SSID "SLOCK"                                          // input your home or public wifi name

#define WIFI_PASSWORD "SLOCK123456"                                    //password of wifi ssid

String fireStatus = "";                                                     // led status received from firebase

int cerradura = 2;
String incoming = "";
void setup() {

  Serial.begin(9600);

  delay(1000);

  pinMode(2, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi

  delay(10000);
  Serial.print("Connecting to ");

  Serial.print(WIFI_SSID);

  if (WiFi.status() != WL_CONNECTED) {          //If it isn't possible to connect, activates the bluetooth

    Serial.print("CREATING BT CONNECTION");

    delay(500);

    WiFi.disconnect(true);

    ESP_BT.begin("SecureLockMX"); //Name of your Bluetooth Signal

    Serial.println("Bluetooth Device is Ready to Pair");


  } else {                                            // if the wifi is aviable...

    Serial.println();

    Serial.print("Connected to ");

    Serial.println(WIFI_SSID);

    Serial.print("IP Address is : ");

    Serial.println(WiFi.localIP());                                                      //print local IP address

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase

    Firebase.setString("LOCK_STATUS", "CLOSE");                                          //send initial string of led status
  }
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    fireStatus = Firebase.getString("LOCK_STATUS");                     // get led status input from firebase

    if (fireStatus == "OPEN") {                         // compare the input of led status received from firebase

      Serial.println("LA CERRADURA ESTA ABIERTA");

      digitalWrite(2, HIGH);                                                         // make output led ON

    }

    else if (fireStatus == "CLOSE") {              // compare the input of led status received from firebase

      Serial.println("CERRADO");

      digitalWrite(2, LOW);                                                         // make output led OFF

    }

    else {

      Serial.println("Wrong Credential!");

    }
  }
  else {
  char chr;
    if (ESP_BT.available()) //Check if we receive anything from Bluetooth
    {
      chr = ESP_BT.read(); //Read what we recevive
      if(chr == 13){
        if(incoming=="d975205d410502c5d490b74f58704a1d6f4ffeb11ff3140b561deea721ee3bb7")
        {
        Serial.println(incoming);
        digitalWrite(2, HIGH);
        delay(3000);
        digitalWrite(2, LOW);
        
        ESP.restart();
        }
      }
      else
      {
               digitalWrite(13, HIGH);
               delay(1500);
               digitalWrite(13, LOW);
               delay(1500);
               digitalWrite(13, HIGH);
               delay(3000);
               digitalWrite(13, LOW);
      }
      incoming = incoming + chr;    
    }
  }

  // Implement color and sound codes like 1 beep and 1 flash is OK, it will be developed as functions in order to callem anywhere in the code

}
