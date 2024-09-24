#include <WiFi.h>
#include <esp_now.h>
 #include <Adafruit_SSD1306.h>
 Adafruit_SSD1306 display(-1);
// Define data structure
typedef struct struct_message {
    float a;
    float b;
    int c;
} struct_message;
 
// Create structured data object
struct_message myData;
 
// Callback function
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  // Get incoming data
  memcpy(&myData, incomingData, sizeof(myData));
  
  // Print to Serial Monitor
  
  
    
    
    
    Serial.print("Temp Sensor ");
  Serial.print(myData.c);
  Serial.print(": ");
  Serial.println(myData.a);
 
    
  Serial.print("Humidity Sensor ");
  Serial.print(myData.c);
  Serial.print(": ");
  Serial.println(myData.b); 
  
 
  Serial.println("");
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  
 
    // Clear the buffer.
    
 
  // Start ESP32 in Station mode
  WiFi.mode(WIFI_STA);
 
  // Initalize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
   
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Sensor:");
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(58,0);
    display.println("NO.1");
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(98,0);
    display.println("NO.2");
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,10);
    display.println("Temp:");
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,23);
    display.println("Humidity:");
    display.display();

  if(myData.c==1){
  
  display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(58,10);
    display.println(myData.a);
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(58,23);
    display.println(myData.b);
    display.display();
    
  
    
  }
   else{
  
  display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(96,10);
    display.println(myData.a);
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(96,23);
    display.println(myData.b);
    display.display();
    
    delay(500);
  display.clearDisplay();
  
  }
  
  
  
    
  }