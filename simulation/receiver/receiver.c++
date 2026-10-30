#include <Wifi.h>
#include <esp.now.h>

//Receiving ESP-NOW Data

//Determine the MAC address for transmitter
void setup(){
    Seral.begin(115200);
    Wifi.mode(WIFI_STA);
    Serial.print(WiFi.macAddress());
}
const int numJoysticks = 5;

typedef struct struct_message {
  int8_t joystickVals[numJoysticks]; 
} struct_message;
//security; encrypt LMK of the paired device with the CCMP method.
//not needed

//initialize where the data is being sent(OnDataSet)
//Receiving ESP-NOW Data
void onDataRecv(const esp_now_recv_info_t *info,const uint8_t *data,int len){
  if(len != sizeof(receivedData)) return;
  memcpy(&receivedData, data, sizeof(receivedData));

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if(esp_now_init()!=ESP_OK){
    Serial.println("ESP-NOW failed");
    return;
  }
  //call for receiver
  esp_now_register_recv_cb(onDataRecv);
  Serial.print("Ready!")
}
voidloop(){

}

