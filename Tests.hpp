#pragma once

#include "WiFi_Util.hpp"

void test_timing(){
  log_message("Starting");
  char test[512] = {};
  send_packet(IPAddress(192, 168, 4, 255), 5001, test);
  log_message("finished");
}
