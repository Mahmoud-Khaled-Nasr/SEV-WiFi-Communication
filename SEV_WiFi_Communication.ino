#include "Serial_Interface.hpp"
#include "WiFi_Util.hpp"
#include "Tests.hpp"

int clients_count_g = 0;

void broadcast_data_buffer(unsigned char* data_buffer, int data_buffer_size){
  send_packet(broadcast_IP_g, BROADCAST_PORT_C, data_buffer, data_buffer_size);
}

void setup() {
  init_logger();
  init_serial();
  init_wifi();
}

// TODO add support for deep sleep
void loop() {  
  int result = receive_handshake_packet();

  if (clients_count_g == 0 && result == 1){
    start_serial();
  }else if (clients_count_g == 1 && result == -1){
    end_serial();
  }
  clients_count_g += result;
  
  if (clients_count_g > 0){
    unsigned char* data_buffer;
    int data_buffer_size;
    receive_serial_packet(data_buffer, data_buffer_size);
    // TODO check if u need to stop the serial here
    broadcast_data_buffer(data_buffer, data_buffer_size);
  }
}









