#include <Arduino.h>
#include <argviz.h>

#include "Config.h"
#include "VoltageSensor.h"
#include "Motor.h"
#include "Encoder.h"
#include "FunctionSelect.h"
#include "VelEstimator.h"
#include "ServoMotor.h"
#include "Mixer.h"
#include "Odometr.h"
#include "ASMR.h"
#include "Screens.h"

void setup()
{
  Serial.begin(115200);
  
  m_init();
  vs_init();
  enc_init();
  odom_reset();
  fns_init();
  asmr_init();

  interrupts();

  argviz_init(Serial);
  argviz_registerScreen(1, volts);
  argviz_registerScreen(0, odom);
  argviz_start();  

}


void loop()
{
  // Timer
  static uint32_t timer = micros();
  while(micros() - timer < Ts_us)
    ;
  timer = micros();
  asmr_tick();
}
