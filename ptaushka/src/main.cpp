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
#include "Screens.h"


void setup()
{
  Serial.begin(115200);
  
  m_init();
  vs_init();
  enc_init();
  odom_reset();
  fns_init();

  argviz_init(Serial);
  argviz_registerScreen(0, volts);
  argviz_registerScreen(1, servos);
  argviz_start();


  
}

void loop()
{
  // Timer
  static uint32_t timer = micros();
  while(micros() - timer < Ts_us)
    ;
  timer = micros();
  odom_tick();
  static float ph = 0;
  ph += 0.004;


  // mixer_tick(goal_v_0, goal_theta_i0);
  mixer_tick(0.02, sin(ph)*1.5);
}
