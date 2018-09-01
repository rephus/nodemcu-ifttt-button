#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

static const uint8_t D2   = 4;
const int buttonPin = D2;     // the number of the pushbutton pin
const int ledPin =  LED_BUILTIN;      // the number of the LED pin
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

const int ON = LOW; 
const int OFF = HIGH; 

void setup() {
 
 
  Serial.begin(115200);                                  //Serial connection

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, OFF);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
    //digitalWrite(buttonPin, LOW);


  Serial.println("Connecting to Wifi...");
  
  WiFi.begin("SSID", "xxxxx");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
 
  }
  Serial.println("Connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  
  digitalWrite(ledPin, ON);
  delay(1000); 
  digitalWrite(ledPin, OFF);
}
 
void loop() {
  
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
  
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
      Serial.println("Button pressed");
      // turn LED on:
      digitalWrite(ledPin, ON);
      delay(1000); 

         HTTPClient http;    //Declare object of class HTTPClient
       
         http.begin("http://maker.ifttt.com/trigger/esp_button_1/with/key/cEZ5IEFRNAbytl2-vzsB5y");      //Specify request destination
         //http.addHeader("Content-Type", "text/plain");  //Specify content-type header
       
         //int httpCode = http.POST("Message from ESP8266");   //Send the request
         int httpCode = http.GET();
         String payload = http.getString();                  //Get the response payload
       
         Serial.println(httpCode);   //Print HTTP return code
         if (httpCode > 0) { //Check the returning code
 
           String payload = http.getString();   //Get the request response payload
            Serial.println(payload);                     //Print the response payload
 
         } else {
            digitalWrite(ledPin, ON);
            delay(100); 
            digitalWrite(ledPin, OFF);
            delay(100); 
            digitalWrite(ledPin, ON);

         }

         http.end();  //Close connection

      
       digitalWrite(ledPin, OFF);
       //TODO Send HTTP request
    }
    /*

  */
 }else{
    Serial.println("Error in WiFi connection");   
 }
 
  delay(100);  //Send a request every 30 seconds
 
}
