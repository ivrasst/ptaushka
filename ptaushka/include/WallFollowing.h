#pragma once

#include "ASMR.h"

float wf_kp_l = 0.08;
float wf_kp_r = -wf_kp_l;
float wf_kp_angle = 7;

// 6 = k*10 => k = 6/10

float wf_straight_tick(SensorData data)
{

    float theta_i0 = 0;
    int count = 0;

    float left = data.dist_left;
    float right = data.dist_right;

    float err_l = WF_LEFT_REFERENCE - left;
    float err_r = WF_RIGHT_REFERENCE - right;
    float err_angle = 0 - data.odom_theta;
    
    float theta_i0_left = err_l * wf_kp_l;
    float theta_i0_right = err_r * wf_kp_r;
    float theta_i0_angle = err_angle * wf_kp_angle;
    // if (data.is_wall_left)
    // {
        theta_i0 = theta_i0_left;
    //     count++;
    // }

    // if (data.is_wall_right)
    // {
    //     theta_i0 += theta_i0_right;
    //     count++;
    // }

    // theta_i0 += theta_i0_angle;
    // count++;
    if (count > 0)
    {
        theta_i0 /= count;
    }

    return theta_i0;
}
