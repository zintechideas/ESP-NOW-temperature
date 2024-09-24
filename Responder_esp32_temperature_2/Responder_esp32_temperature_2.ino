#include <WiFi.h>
#include <esp_now.h>
#include <DHT.h>
 
// Define DHT22 parameters
#define DHTPin 12
#define DHTType DHT21
 
// Create DHT Object
DHT dht(DHTPin, DHTType);
 
// Variables for temperature and humidity
float temp;
float humid;
 
// Integer for identification (make unique for each transmitter)
int ident = 1;
 
// Responder MAC Address (Replace with your responders MAC Address)
uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0xD5, 0x72, 0x94};

// Define data structure
typedef struct struct_message {
  float a;
  float b;
  int c;
} struct_message;
 
// Create structured data object
struct_message myData;
 
// Register peer
esp_now_peer_info_t peerInfo;
 
// Sent data callback function
void OnDataSent(const uint8_t *macAddr, esp_now_send_status_t status)
{
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
 
  // Setup Serial monitor
  Serial.begin(115200);
  delay(100);
 
  // Initiate DHT22
  dht.begin();
 
  // Set ESP32 WiFi mode to Station temporarly
  WiFi.mode(WIFI_STA);
 
  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  // Define callback
  esp_now_register_send_cb(OnDataSent);
 
 
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
 
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
 
}
 
void loop() {
 
  // Read DHT22 module values
  temp = dht.readTemperature();
  delay(10);
  humid = dht.readHumidity();
  delay(10);
 
  Serial.print("Temp: ");
  Serial.println(temp);
  Serial.print("Humid: ");
  Serial.println(humid);
 
  // Add to structured data object
  myData.a = temp;
  myData.b = humid;
  myData.c = ident;
 
  // Send data
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
 
  // Delay for DHT22 sensor
  delay(2000);
}