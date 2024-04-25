#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define RED     PIN_PA1
#define YELLOW  PIN_PA2
#define GREEN   PIN_PA3
#define MUX     PIN_PA6

struct TrafficLights
{
  bool r1;
  bool y1;
  bool g1;
  bool r2;
  bool y2;
  bool g2;
  bool mux;
};

enum Action : uint8_t
{
  RED1_on,    // RED column 1 on
  RED1_off,   // RED column 1 off
  RED2_on,    // ... etc.
  RED2_off,
  YEL1_on,    
  YEL1_off,
  YEL2_on,
  YEL2_off,
  GRN1_on,
  GRN1_off,
  GRN2_on,
  GRN2_off,
  cRED1_on,   // clear all in column 1 & RED column 1 on
  cRED2_on,   // ... etc.
  cYEL1_on,
  cYEL2_on,
  cGRN1_on,
  cGRN2_on,
  PAUSE0,     // pause 0
  PAUSE1,
  PAUSE2,
  PAUSE3,
  ClrAll      // clear all
};
