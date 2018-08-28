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
}

void log_loop(){
  log_message(
    String("number of clients ") + 
    String(clients_count_g) + 
    String("\n"));
}

void receive_handshake_packet(){
  IPAddress remote_IP;
  int len, remote_port;
  receive_packet(remote_IP, remote_port, len);
  if (len > 2){
    log_message(String("ERROR in the reveived packet\n"));
  }else if (udp_input_buffer_g[0] == STARTING_SEQUENCE_C){
    clients_count_g++;
  }else if (udp_input_buffer_g[0] == ENDING_SEQUENCE_C){
    clients_count_g--;
  }else {
    log_message(String("ERROR in the parsing the packet\n"));
  }
  // send back a reply, to the IP address and port we got the packet from
  char reply_packet[] = "received";
  send_packet(remote_IP, remote_port, reply_packet);
}

void loop() {
  //log_loop();
  receive_handshake_packet();
  if(clients_count_g > 0){
    
  }
}
