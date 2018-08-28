#pragma once

#include<ESP8266WiFi.h>
#include<WiFiUdp.h>

#include "Constants.hpp"

WiFiUDP udp_g;
IPAddress broadcast_IP_g;

void init_wifi(){
  WiFi.softAP(AP_NAME_C, AP_PASSWORD_C);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    log_message(".");
  }
  log_message(" connected\n");
  
  udp_g.begin(LOCAL_UDP_PORT_C);
  log_message(
     String("Now listening at IP ") + 
     WiFi.softAPIP().toString() + 
     String(" UDP port ") + 
     String(LOCAL_UDP_PORT_C) + 
     "\n");
  IPAddress AP_IP = WiFi.softAPIP();
  broadcast_IP_g = IPAddress(AP_IP[0], AP_IP[1], AP_IP[2], 255);
  log_message(
    String("Broadcasting at ") + 
    broadcast_IP_g.toString() + 
    String("\n"));
}

void send_packet(IPAddress receiving_address, int receiving_port, char* packet){
    udp_g.beginPacket(receiving_address, receiving_port);
    udp_g.write(packet);
    udp_g.endPacket();
}

char receive_packet(){
  int packet_size = udp_g.parsePacket();
  if (packet_size)
  {
    // receive incoming UDP packets
    log_message(
      String("Received ") + 
      String(packet_size) + 
      String("bytes from ") + 
      udp_g.remoteIP().toString() + 
      String(" port ") + 
      String(udp_g.remotePort()) + 
      String("\n"));
    int len = udp_g.read(udp_input_buffer_g, INPUT_BUFFER_SIZE_C);
    if (len > 0)
    {
      udp_input_buffer_g[len] = 0;
    }
    log_message(
      String("UDP packet contents: ") + 
      String(udp_input_buffer_g) + 
      String("\n") );

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
    send_packet(udp_g.remoteIP(),  udp_g.remotePort(), reply_packet);
  }
}

