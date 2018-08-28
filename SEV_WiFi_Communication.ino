#include "Constants.hpp"
#include "Logger.hpp"
#include "WiFi_Util.hpp"
#include "Tests.hpp"

void init_serial(){
  Serial.begin(AT_BAUD_RATE_C);
  log_message(String("Serial is up and running \n"));
}

void setup() {
  init_logger();
  init_serial();
  init_wifi();
  test_timing();
}

void log_loop(){
  log_message(
    String("number of clients ") + 
    String(clients_count_g) + 
    String("\n"));
}

void loop() {
  //log_loop();
  receive_packet();
  if(clients_count_g > 0){
    
  }
}
