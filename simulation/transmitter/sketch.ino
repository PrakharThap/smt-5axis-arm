#include <esp_now.h>
#include <WiFi.h>

// Receiver MAC address
uint8_t broadcastAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


const int numJoysticks = 5;
int joystickADC[numJoysticks] = {2, 3, 0, 1, 4};

typedef struct struct_message {
  int8_t joystickVals[numJoysticks]; 
} struct_message;

struct_message joystickData;
esp_now_peer_info_t peerInfo;

// Callback when data is sent
void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
      Serial.println("Error initializing ESP-NOW");
      return;
  }

  // Register send callback to get status of transmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
      Serial.println("Failed to add peer");
      return;
  }

  // Set all pins to INPUT
  for (int i = 0; i < numJoysticks; i++) {
    pinMode(joystickADC[i], INPUT);
  }
}

void loop() {
  delay(10);

  for (int i = 0; i < numJoysticks; i++) {
    // Map joystick values to signed 8 bit range
    int8_t horz = map(analogRead(joystickADC[i]), 0, 4095, 127, -128);
    joystickData.joystickVals[i] = horz;
    Serial.println(horz);
  }  

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&joystickData, sizeof(joystickData));
}
