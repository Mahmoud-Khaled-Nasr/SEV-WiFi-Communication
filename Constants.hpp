#pragma once

const char* AP_NAME_C = "SEV_CUT";  // The name of the AP network
const char* AP_PASSWORD_C = "password";  // The password of the AP

const int LOCAL_UDP_PORT_C = 4210;

const int INPUT_BUFFER_SIZE_C = 255;

const int AT_BAUD_RATE_C = 115200;
const int LOG_BAUD_RATE_C = 115200;

const char STARTING_SEQUENCE_C = 'a';
const char ENDING_SEQUENCE_C = 'b';

const bool LOGGING_C = false;
const bool DEBUG_C = false;
const bool DEV_C = true;

char udp_input_buffer_g[INPUT_BUFFER_SIZE_C];
int current_udp_input_buffer_size_g = 0;
int clients_count_g = 0;
