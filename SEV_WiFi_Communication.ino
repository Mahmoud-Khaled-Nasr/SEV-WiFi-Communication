#include "Serial_Interface.hpp"
#include "WiFi_Util.hpp"
#include "Tests.hpp"

int clients_count_g = 0;
const int SERIAL_WIFI_DATA_BUFFER_MAX_SIZE_C = 100;
unsigned char serial_wifi_data_buffer_g[SERIAL_WIFI_DATA_BUFFER_MAX_SIZE_C];
int serial_wifi_data_buffer_current_size_g = 0;

void broadcast_data_buffer(){
  send_packet(broadcast_IP_g, BROADCAST_PORT_C, serial_wifi_data_buffer_g, serial_wifi_data_buffer_current_size_g);
}

bool add_byte_to_data_buffer (byte new_byte){
  serial_wifi_data_buffer_g[serial_wifi_data_buffer_current_size_g] = new_byte;
  serial_wifi_data_buffer_current_size_g++;
  if( serial_wifi_data_buffer_current_size_g == SERIAL_WIFI_DATA_BUFFER_MAX_SIZE_C){
    serial_wifi_data_buffer_current_size_g = 0;
    return true;
  }else{
    return false;
  }
}

void setup() {
  init_logger();
  init_serial();
  init_wifi();
}

// TODO add support for deep sleep
void loop() {
  //log_loop();
  int result = receive_handshake_packet();

  if (clients_count_g == 0 && result == 1){
    start_serial();
  }else if (clients_count_g == 1 && result == -1){
    end_serial();
  }
  clients_count_g += result;
  
  if (clients_count_g > 0){
    byte b = receive_serial_byte();
    bool is_full = add_byte_to_data_buffer(b);
    if (is_full){
      end_serial();
      broadcast_data_buffer();
      start_serial();
    }
  }
}









