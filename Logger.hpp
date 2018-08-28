#pragma once

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

