#pragma once

// Time
#define Ts_us 2000
#define Ts_s (Ts_us / 1000000.0)

// Vel estimator
#define VE_LPF_T 0.005

// Servo
#define SERVO_KP 3.0
#define SERVO_KI 20.0

// Robot parameters

#define ROBOT_WIDTH (0.075*380/360)//(0.075*180.0/174.0)         // [m]
#define ROBOT_WHEEL_RADIUS (0.0165*745.0/720.0) // [m]

// a / y * x
// a * x / y
// a * (x/y)

/*
16mm
16.5
17
16.5
*/

// Movement parameters
#define MAX_VEL 0.20    // [m/s]
#define MAX_ANG_VEL 1.8 // [rad/s]

#define TURN_RADIUS_SHORTEST 0.09 // [m]
#define TURN_RADIUS_EXPLORE 0.05  // [m]

// Maze parameters
#define CELL_WIDTH 0.18 // [m]

// ASMR parameters
#define ASMR_PROG_BUFFER_SIZE 64

// Wall parameters
#define WF_LEFT_REFERENCE  148//124//160//141//50
#define WF_RIGHT_REFERENCE 172//170//130//154//50
#define WF_LEFT_THRESHOLD  54//64//52//45//20
#define WF_RIGHT_THRESHOLD 70//62//62//40//20

#define WF_FRIGHT_THRESHOLD 12
#define WF_FLEFT_THRESHOLD  17

/*===MAZE===*/
#define MAZE_WIDTH 6//6
#define MAZE_HEIGHT 6//4

// Solver parameters
#define MAX_SOLVE_TIME 500 // [us]

#define GOAL_X 2
#define GOAL_Y 2

// Navigator parameters

#define NAV_X_START 1
#define NAV_Y_START 1
#define NAV_SIGMA_START 0 // стартуем вправо