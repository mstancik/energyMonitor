
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "MST";
const char* password = "";

void setup()
{
  delay(1000);
  Serial.begin(9600);
//  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
//  delay(1000);
 // WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  HTTPClient http;    //Declare object of class HTTPClient
  bool StringReady = false;
  String json;
  String Link,Link2;

  //ACCEPT DATA FROM THE ARDUINO
  while (Serial.available()){ // listen for serial data from the Arduino Atmega328
    json=Serial.readString();
    json = json.substring(0,json.length()-2);
    //json.replace("\"","%22");
    StringReady = true;
    }

  if (StringReady){
    delay(1);
    Serial.println("ESP STRING");
    Serial.println(json+"012345");

    //GET Data
    //json = "{\"power1\":3.592164,\"power2\":226.0527,\"power3\":210.8689}";
    Link = "http://192.168.254.3/input/post?node=mst_emon&fulljson=" + json + "&apikey=e9ba303b131f33322ff6dd9e69ca751f";
    //{\"power1\":200,\"power2\":100,\"power3\":300}
    //Link = "http://192.168.254.3/input/post?node=mst_emon&fulljson={\"power1\":3.592164,\"power2\":226.0527,\"power3\":210.8689}&apikey=e9ba303b131f33322ff6dd9e69ca751f";
    Serial.println(Link);
    Serial.println(Link2);
    http.begin(Link);     //Specify request destination
    
    int httpCode = http.GET();            //Send the request
    String payload = http.getString();    //Get the response payload
  
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
  
    http.end();  //Close connection
    
    //delay(500);  //GET Data at every 5 seconds
    
    StringReady = false;
    }
}
