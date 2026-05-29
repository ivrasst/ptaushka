#include <Arduino.h>
#include <argviz.h>

#include "VoltageSensor.h"
#include "Motor.h"
#include "Encoder.h"
#include "Config.h"
#include "VelEstimator.h"
#include "ServoMotor.h"
#include "Mixer.h"
#include "Screens.h"
#include "Odometer.h"
#include "ASMR.h"
#include "DistSensors.h"
#include "Maze.h"
#include "MazeDrawer.h"
#include "Solver.h"
#include "Navigator.h"
#include "Tests.h" 

void setup()
{
  Serial.begin(115200);

  m_init();
  vs_init();
  enc_l_init(); 
  enc_r_init();
  asmr_init();
  dist_init();
  maze_init();
  nav_init();
  pinMode(6, OUTPUT);
  
  interrupts();

  argviz_init(Serial);
  argviz_registerScreen(0, volts);
  argviz_registerScreen(1, encoders);
  argviz_registerScreen(2, servos);
  argviz_registerScreen(0, mixer);
  argviz_registerScreen(4, asmr);
  argviz_registerScreen(5, dist);
  argviz_registerScreen(7, wf);
  // argviz_start();
  
  digitalWrite(6, 0);
  
  while (true)
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
      ;
    timer = micros();
    
    asmr_tick();

    if(asmr_is_finished())
    {
      // digitalWrite(6, 1);
      break;
    }
  }
  Serial.println("=======  RESOLVE  =======");
  nav_init();
  asmr_init();
  static uint32_t timerStop = millis();
  while (millis() - timerStop < 8000)
    m_drive(0, 0);
  

  odom_reset();
  solver_init();
  solver_set_start_goal(Vec2{0, 0}, Vec2{GOAL_X, GOAL_Y});

  while(!solver_solve())
    digitalWrite(6, 1);
  digitalWrite(6, 0);
  router_init();
  router_tick();
  
  router_path_to_cyc(router_path_buffer);
  
  for(int i  = 0; i < router_cyc_index; i++)
  {
      asmr_prog_buffer[i].raw = router_cyc_buffer[i].raw;
  }
  asmr_prog_buffer[router_cyc_index+1] = asmr_prog_buffer[router_cyc_index];
  asmr_prog_buffer[router_cyc_index].raw = SWD05;
  asmr_prog_counter = 0;

  while(true)
  {
    static uint32_t timer = micros();
    while (micros() - timer < Ts_us)
      ;
    timer = micros();
    
    asmr_tick();

    if(asmr_is_finished())
    {
      break;
    } 
  }
  //*/


  
  // test_navigator();
  // test_router();
  // maze_init();
  // test_maze();
  // draw_maze(MAZE_WIDTH, MAZE_HEIGHT);
}

// 1. Переписать весь решенный лабиринт в циклограммах а asmr_prog_buffer
// 2. перезапускать решение лабиринта, если увидели новые стенки и не на финише


void loop()
{
  // Timer
  static uint32_t timer = micros();
  while (micros() - timer < Ts_us)
    ;
    timer = micros();
    

  // Sense
  // odom_tick();

  // enc_l_tick();
  // enc_r_tick();
  // ve_l_tick(enc_l_get_phi());
  // ve_r_tick(enc_r_get_phi());

  // Plan

  // Act
  // servo_tick(left_w0, right_w0);
  // mixer_tick(v_0, theta_i0);
  asmr_tick();
}
