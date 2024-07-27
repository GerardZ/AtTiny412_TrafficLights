#include "main.h"

volatile TrafficLights trafficlights;

void ClearAll(uint8_t column = 0)
{
  /*
  Clear light in column, or all if column == 0
  */
  if (column == 0 || column == 1)
  {
    trafficlights.r1 = false;
    trafficlights.y1 = false;
    trafficlights.g1 = false;
  }

  if (column == 0 || column == 2)
  {
    trafficlights.r2 = false;
    trafficlights.y2 = false;
    trafficlights.g2 = false;
  }
}

void DoAction(Action action)
{
  switch (action)
  {
  // on or off light in column
  case RED1_on:
    trafficlights.r1 = true;
    return;
  case RED1_off:
    trafficlights.r1 = false;
    return;
  case RED2_on:
    trafficlights.r2 = true;
    return;
  case RED2_off:
    trafficlights.r2 = false;
    return;
  case YEL1_on:
    trafficlights.y1 = true;
    return;
  case YEL1_off:
    trafficlights.y1 = false;
    return;
  case YEL2_on:
    trafficlights.y2 = true;
    return;
  case YEL2_off:
    trafficlights.y2 = false;
    return;
  case GRN1_on:
    trafficlights.g1 = true;
    return;
  case GRN1_off:
    trafficlights.g1 = false;
    return;
  case GRN2_on:
    trafficlights.g2 = true;
    return;
  case GRN2_off:
    trafficlights.g2 = false;
    return;

  // following does the same but first clears other lights in that column
  case cRED1_on:
    ClearAll(1);
    trafficlights.r1 = true;
    return;
  case cRED2_on:
    ClearAll(2);
    trafficlights.r2 = true;
    return;
  case cYEL1_on:
    ClearAll(1);
    trafficlights.y1 = true;
    return;
  case cYEL2_on:
    ClearAll(2);
    trafficlights.y2 = true;
    return;
  case cGRN1_on:
    ClearAll(1);
    trafficlights.g1 = true;
    return;
  case cGRN2_on:
    ClearAll(2);
    trafficlights.g2 = true;
    return;

  // following will turn on Led and turns off ALL others.
  case ccYEL1_on:
    ClearAll();
    trafficlights.y1 = true;
    return;
  case ccYEL2_on:
    ClearAll();
    trafficlights.y2 = true;
    return;

  // pause`s....
  case PAUSE0:
    delay(500);
    return;
  case PAUSE1:
    delay(1500);
    return;
  case PAUSE2:
    delay(10000);
    return;
  case PAUSE3:
    delay(4000);
    return;

    // misc
  case ClrAll:
    ClearAll();
    return;
  }
}

Action program1[] = {
    ccYEL2_on,
    PAUSE0,
    ccYEL1_on,
    PAUSE0,
    };

Action program[] = {
    cRED1_on,
    cGRN2_on,
    PAUSE2,
    cYEL2_on,
    PAUSE1,
    cRED2_on,
    PAUSE1,
    cGRN1_on,
    PAUSE2,
    cYEL1_on,
    PAUSE1,
    cRED1_on,
    PAUSE1};

void setupTimer()
{
  // Configure Timer B0
  TCB0.CCMP = 20000 - 1;                              // Set the compare value for 100 Hz interrupts
  TCB0.CTRLA = TCB_CLKSEL_CLKDIV2_gc | TCB_ENABLE_bm; // Use Prescaler CLK_PER/2, Enable the timer
  TCB0.CTRLB = TCB_CNTMODE_INT_gc;                    // Set timer to periodic interrupt mode

  // Enable interrupt
  TCB0.INTCTRL = TCB_CAPT_bm; // Enable the interrupt

  // Enable global interrupts
  sei();
}

ISR(TCB0_INT_vect)
{
  TCB0.INTFLAGS = TCB_CAPT_bm; // Clear the interrupt flag

  /**
   * @brief ISR, this is multiplexing lights1 & lights2
   *
   */

  pinMode(MUX, INPUT); // switch off all
  trafficlights.mux = !trafficlights.mux;
  digitalWrite(MUX, trafficlights.mux);

  // now set every led according to trafficlights
  if (!trafficlights.mux)
  { // left
    digitalWrite(RED, trafficlights.r1);
    digitalWrite(YELLOW, trafficlights.y1);
    digitalWrite(GREEN, trafficlights.g1);
  }
  else
  { // right
    digitalWrite(RED, !trafficlights.r2);
    digitalWrite(YELLOW, !trafficlights.y2);
    digitalWrite(GREEN, !trafficlights.g2);
  }

  pinMode(MUX, OUTPUT);
}

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(MUX, OUTPUT);

  setupTimer();
}

uint8_t pgmCount = 0;
void loop()
{
  DoAction(program[pgmCount++ % sizeof(program)]);

  //pgmCount++;
  //pgmCount = pgmCount % sizeof(program);
}
