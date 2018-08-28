#pragma once

#include "Constants.hpp"
#include "WiFi_Util.hpp"

void test_timing(){
  log_message("Starting");
  char test[1512] = {};
  send_packet(IPAddress(192, 168, 4, 255), 5001, test);
  log_message("finished");
}
