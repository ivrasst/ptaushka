#pragma once
#include "argviz.h"


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

    // ROW(
    //   "encLphi: %d", (int)(enc_l_get_phi() * 180.0/M_PI)
    // )
    // ROW(
    //   "encRphi: %d", (int)(enc_r_get_phi() * 180.0/M_PI)
    // )
    
    // ROW(
    //   "encRphi: %d", (int)(enc_r_get_phi() * 180.0/M_PI)
    // )

  }
)


SCREEN(servos,
  {
    CLICK_ROW(
      [](CLICK_STATE state){
        switch (state)
        {
        case CLICK_LEFT:
          goal_v_0-=0.1;
          break;
        case CLICK_RIGHT:
          goal_v_0+=0.1;
          break;
        case CLICK_DOWN:
          goal_v_0 = 0;
          break;
        default:
          break;
        }
      },
      "goal_v_0: %s", String(goal_v_0).c_str()
    )
    CLICK_ROW(
      [](CLICK_STATE state){
        switch (state)
        {
        case CLICK_LEFT:
          goal_theta_i0-=0.1;
          break;
        case CLICK_RIGHT:
          goal_theta_i0+=0.1;
          break;
        case CLICK_DOWN:
          goal_theta_i0 = 0;
          break;
        default:
          break;
        }
      },
        "goal_theta_i0: %s", String(goal_theta_i0).c_str()
    )
    ROW(
      "odom_S: %s", String(odom_get_S()).c_str()
    )
    ROW(
      "odom_theta: %s", String(odom_get_theta()).c_str()
    )
  }
)
