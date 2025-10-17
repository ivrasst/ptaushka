#include <Arduino.h>
#include <argviz.h>

#include "Config.h"
#include "VoltageSensor.h"
#include "Motor.h"
#include "Encoder.h"
#include "FunctionSelect.h"
#include "VelEstimator.h"

int left_u = 0;
int right_u = 0;

SCREEN(volts,
  {
    // ROW("Vbatt [mV]: %d", int(vs_get_v_batt() * 1000));
    // CLICK_ROW(
    //   [](CLICK_STATE state){
    //     switch (state)
    //     {
    //     case CLICK_LEFT:
    //       left_u--;
    //       break;
    //     case CLICK_RIGHT:
    //       left_u++;
    //       break;
    //     case CLICK_DOWN:
    //       left_u = 0;
    //       break;
    //     default:
    //       break;
    //     }
    //   },
    //   "left u [V]: %d", left_u
    // )
    // CLICK_ROW(
    //   [](CLICK_STATE state){
    //     switch (state)
    //     {
    //     case CLICK_LEFT:
    //       right_u--;
    //       break;
    //     case CLICK_RIGHT:
    //       right_u++;
    //       break;
    //     case CLICK_DOWN:
    //       right_u = 0;
    //       break;
    //     default:
    //       break;
    //     }
    //   },
    //   "right u [V]: %d", right_u
    // )

    ROW(
      "encLphi: %d", (int)(enc_l_get_phi() * 180.0/M_PI)
    )
    ROW(
      "encRphi: %d", (int)(enc_r_get_phi() * 180.0/M_PI)
    )
    ROW(
      "ve_l_w: %d", (int)(ve_l_get_w_est_f() * 180.0/M_PI)
    )
    ROW(
      "ve_r_w: %d", (int)(ve_r_get_w_est_f() * 180.0/M_PI)
    )
    // ROW(
    //   "encRphi: %d", (int)(enc_r_get_phi() * 180.0/M_PI)
    // )
  }
)

void setup()
{
  Serial.begin(115200);
  
  m_init();
  vs_init();
  enc_init();
  fns_init();

  argviz_init(Serial);
  argviz_registerScreen(0, volts);
  argviz_start();


  
}

void loop()
{
  // Timer
  static uint32_t timer = micros();
  while(micros() - timer < Ts_us)
    ;
  timer = micros();
  // Sense
  // Plan
  // Act
  enc_l_tick();
  enc_r_tick();
  ve_l_tick(enc_l_get_phi());
  ve_r_tick(enc_r_get_phi());
  fns_tick();
  // m_drive(left_u, right_u);

}
