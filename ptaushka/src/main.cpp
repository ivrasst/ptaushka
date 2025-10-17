#include <Arduino.h>
#include <argviz.h>

#include "VoltageSensor.h"
#include "Motor.h"
#include "Encoder.h"

int left_u = 0;
int right_u = 0;

SCREEN(volts,
  {
    ROW("Vbatt [mV]: %d", int(vs_get_v_batt() * 1000));
    CLICK_ROW(
      [](CLICK_STATE state){
        switch (state)
        {
        case CLICK_LEFT:
          left_u--;
          break;
        case CLICK_RIGHT:
          left_u++;
          break;
        case CLICK_DOWN:
          left_u = 0;
          break;
        default:
          break;
        }
      },
      "left u [V]: %d", left_u
    )
    CLICK_ROW(
      [](CLICK_STATE state){
        switch (state)
        {
        case CLICK_LEFT:
          right_u--;
          break;
        case CLICK_RIGHT:
          right_u++;
          break;
        case CLICK_DOWN:
          right_u = 0;
          break;
        default:
          break;
        }
      },
      "right u [V]: %d", right_u
    )

    ROW(
      "encLphi: %d", (int)(enc_l_get_phi() * 180.0/M_PI)
    )
    ROW(
      "encRphi: %d", (int)(enc_r _get_phi() * 180.0/M_PI)
    )
  }
)

void setup()
{
  Serial.begin(115200);
  
  m_init();
  vs_init();
  enc_init();

  argviz_init(Serial);
  argviz_registerScreen(0, volts);
  argviz_start();


  
}

void loop()
{
  enc_l_tick();
  enc_r_tick();
  m_drive(left_u, right_u);

  delay(1);
}
