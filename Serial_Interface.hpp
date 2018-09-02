#pragma once
#include <SoftwareSerial.h>

const int AT_BAUD_RATE_C = 9600;
const int LOG_BAUD_RATE_C = 9600;

const char STARTING_SEQUENCE_C = 'a';
const char ENDING_SEQUENCE_C = 'b';

const bool LOGGING_C = true;
const bool DEBUG_C = false;
const bool DEV_C = false;

#define RX D0
#define TX D1

SoftwareSerial log_serial(D0, D1);

// Logging serial functions
void init_logger(){
  if (LOGGING_C){
    log_serial.begin(LOG_BAUD_RATE_C);
    log_serial.write("start logging");
  } 
}

void log_message(String s){
  if (LOGGING_C){
    log_serial.write(s.c_str());
  } else if (DEV_C){
    Serial.write(s.c_str());
  }
}


// Data serial functions
void init_serial(){
  Serial.begin(AT_BAUD_RATE_C);
  log_message(String("Serial is up and running \n"));
}

void start_serial(){
  Serial.write(STARTING_SEQUENCE_C);
}

void end_serial(){
  Serial.write(ENDING_SEQUENCE_C);
}

void receive_serial_packet(unsigned char* data_buffer, int data_buffer_size){
  const int SERIAL_WIFI_DATA_BUFFER_MAX_SIZE_C = 100;
  int received_data_size = Serial.readBytes(data_buffer, SERIAL_WIFI_DATA_BUFFER_MAX_SIZE_C);
  if (received_data_size != SERIAL_WIFI_DATA_BUFFER_MAX_SIZE_C){
    log_message(String("ERROR in receiving serial data frame: Size mismatch \n"));
  }
  // Take the size from the last byte of the buffer
  data_buffer_size = (int)data_buffer[SERIAL_WIFI_DATA_BUFFER_MAX_SIZE_C - 1];
}

