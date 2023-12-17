#include "painlessMesh.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define MESH_PREFIX     "BestMesh"
#define MESH_PASSWORD   "ReallyDoNotCare"
#define MESH_PORT       5555

painlessMesh mesh;




void sendMessage() { mesh.sendBroadcast("Ping: Startup complete, connected to mesh"); }

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("New Connection, nodeId = %u\n", nodeId);
}

void setup() {
  Serial.begin(115200);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  
  sendMessage();
}

void loop() {
  
  mesh.update();
}