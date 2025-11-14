#pragma once

// Time
#define Ts_us 2000
#define Ts_s (Ts_us / 1000000.0f)
#define VE_LPF_T 0.005

//Servo
#define SERVO_KP 1.33
#define SERVO_KI 20.0

// Robot parameters
#define ROBOT_WIDTH 0.075 // [m]
#define ROBOT_WHEEL_RADIUS 0.0165 // [m]

// Movement parameters
#define MAX_VEL 0.3 // [m/s]
#define MAX_THETA 1.0 // [m/s]

// Maze parameters
#define CELL_WIDTH 0.18 // [m]