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
// #include "Screens.h"

void fw();
void left();
void stop();
void setup()
{
  Serial.begin(115200);
  
  m_init();
  vs_init();
  enc_init();
  odom_reset();
  fns_init();

  argviz_init(Serial);
  // argviz_registerScreen(0, volts);
  // argviz_registerScreen(1, servos);
  // argviz_start();  

  fw();
  left();
  fw();
  left();
  fw();
  left();
  fw();
  left();
  stop();
}

float v_0 = 0;
float theta_i0 = 0;
// bool m = false;

void stop()
{
  odom_reset();
  while(true){
    //Timer
    static uint32_t timer = micros();
    while(micros() - timer < Ts_us)
      ;
    timer = micros();

    //Sens
    odom_tick();

    //Plan
    v_0 = 0;
    theta_i0 = 0;

    //Act
    mixer_tick(v_0, theta_i0);
  }
}

void fw()
{
  odom_reset();
  while(true){
    //Timer
    static uint32_t timer = micros();
    while(micros() - timer < Ts_us)
      ;
    timer = micros();

    //Sens
    odom_tick();

    //Plan
    v_0 = MAX_VEL;
    theta_i0 = 0;

    if(odom_get_S() > CELL_WIDTH)
      return;

    //Act
    mixer_tick(v_0, theta_i0);
  }
}

void left()
{
  odom_reset();
  while(true){
    //Timer
    static uint32_t timer = micros();
    while(micros() - timer < Ts_us)
      ;
    timer = micros();

    //Sens
    odom_tick();

    //Plan
    v_0 = 0;
    theta_i0 = MAX_THETA;

    if(abs(odom_get_theta()) > M_PI / 2)
      return;

    //Act
    mixer_tick(v_0, theta_i0);
  }
}

void loop()
{
  // Timer
  static uint32_t timer = micros();
  while(micros() - timer < Ts_us)
    ;
  timer = micros();
  // odom_tick();

  // mixer_tick(0,0);
}
