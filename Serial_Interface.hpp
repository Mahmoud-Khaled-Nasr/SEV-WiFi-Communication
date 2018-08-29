#pragma once

const int AT_BAUD_RATE_C = 115200;
const int LOG_BAUD_RATE_C = 115200;

const char STARTING_SEQUENCE_C = 'a';
const char ENDING_SEQUENCE_C = 'b';

const bool LOGGING_C = false;
const bool DEBUG_C = false;
const bool DEV_C = true;

// Logging serial functions
void init_logger(){
  if (LOGGING_C){
    Serial1.begin(LOG_BAUD_RATE_C);
    Serial1.write("start loggin");
  } 
}

void log_message(String s){
  if (LOGGING_C){
    Serial1.write(s.c_str());
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

unsigned char receive_serial_byte(){
  // TODO is this right i don't wait for anything here ????
  return Serial.read();
}

