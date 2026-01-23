#include <Arduino.h>

const int EMITTER_1 = 12;
const int EMITTER_2 = 11;

/****/

/***
 * Global variables
 */

uint32_t updateTime;
uint32_t updateInterval = 40;  // (ms) do not make this smaller than 25ms for performance reasons

// the default values for the front sensor when the robot is backed up to a wall
const int FRONT_REFERENCE_R = 44;
const int FRONT_REFERENCE_L = 44;
// the default values for the side sensors when the robot is centred in a cell
const int LEFT_REFERENCE = 38;
const int RIGHT_REFERENCE = 49;

// the values above which, a wall is seen
const int FRONT_WALL_THRESHOLD_L = FRONT_REFERENCE_L / 20;  // minimum value to register a wall
const int FRONT_WALL_THRESHOLD_R = FRONT_REFERENCE_R / 20;  // minimum value to register a wall
const int LEFT_WALL_THRESHOLD = LEFT_REFERENCE / 2;     // minimum value to register a wall
const int RIGHT_WALL_THRESHOLD = RIGHT_REFERENCE / 2;   // minimum value to register a wall

// working copies of the reference values
int gFrontReference_L = FRONT_REFERENCE_L;
int gFrontReference_R = FRONT_REFERENCE_R;
int gLeftReference = LEFT_REFERENCE;
int gRightReference = RIGHT_REFERENCE;
// the current value of the sensors
volatile int gSensorFront_L;
volatile int gSensorFront_R;
volatile int gSensorLeft;
volatile int gSensorRight;
// true f a wall is present
volatile bool gFrontWall_L;
volatile bool gFrontWall_R;
volatile bool gLeftWall;
volatile bool gRightWall;
// steering and turn position errors
volatile int gSensorFrontError_L;   // zero when robot in cell centre
volatile int gSensorFrontError_R;   // zero when robot in cell centre
volatile float gSensorCTE;  // zero when robot in cell centre



void analogueSetup() {
  // increase speed of ADC conversions to 28us each
  // by changing the clock prescaler from 128 to 16
  bitClear(ADCSRA, ADPS0);
  bitClear(ADCSRA, ADPS1);
  bitSet(ADCSRA, ADPS2);
}

/***
 * If you are interested in what all this does, the ATMega328P datasheet
 * has all the answers but it is not easy to follow until you have some
 * experience. For now just use the code as it is.
 */
void setupSystick() {
  // set the mode for timer 2
  bitClear(TCCR2A, WGM20);
  bitSet(TCCR2A, WGM21);
  bitClear(TCCR2B, WGM22);
  // set divisor to 128 => timer clock = 125kHz
  bitSet(TCCR2B, CS22);
  bitClear(TCCR2B, CS21);
  bitSet(TCCR2B, CS20);
  // set the timer frequency
  OCR2A = 249;  // (16000000/128/500)-1 = 249
  // enable the timer interrupt
  bitSet(TIMSK2, OCIE2A);
}


void updateWallSensor_Side() {
  // first read them dark
  int right = analogRead(A0);
  int left = analogRead(A3);
  // light them up
  digitalWrite(EMITTER_1, 1);
  // wait until all the detectors are stable
  delayMicroseconds(50);
  // now find the differences
  right = analogRead(A0) - right;
  left = analogRead(A3) - left;
  // and go dark again.
  digitalWrite(EMITTER_1, 0);

  gLeftWall = left > gLeftReference / 2;
  gRightWall = right > gRightReference / 2;

  // make the results available to the rest of the program
  gSensorLeft= left;
  gSensorRight = right;
}

void updateWallSensor_Front() {
  // first read them dark
  int front_l = analogRead(A2);
  int front_r = analogRead(A1);
  // light them up
  digitalWrite(EMITTER_2, 1);
  // wait until all the detectors are stable
  delayMicroseconds(50);
  // now find the differences
  front_l = analogRead(A1) - front_l;
  front_r = analogRead(A2) - front_r;
  // and go dark again.
  digitalWrite(EMITTER_2, 0);

  gFrontWall_L = front_l > gFrontReference_L / 2;//4;
  gFrontWall_R = front_r > gFrontReference_R / 2;//4;

  // make the results available to the rest of the program
  gSensorFront_L = front_l;
  gSensorFront_R = front_r;
}


// the systick event is an ISR attached to Timer 2
bool sensUpdSwitch = 0;
ISR(TIMER2_COMPA_vect) {
  if (sensUpdSwitch) {
    updateWallSensor_Side();
    sensUpdSwitch = 0;
  }
  else {
    updateWallSensor_Front();
    sensUpdSwitch = 1;
  }
}

void ws_init() {
  pinMode(EMITTER_1, OUTPUT);
  pinMode(EMITTER_2, OUTPUT);
  digitalWrite(EMITTER_1, 0);  // be sure the emitter is off
  digitalWrite(EMITTER_2, 0);  // be sure the emitter is off
  analogueSetup();           // increase the ADC conversion speed
  setupSystick();
//   updateTime = millis() + updateInterval;
}

uint16_t ws_left()
{
    return gSensorLeft;
}
uint16_t ws_right()
{
    return gSensorRight;
}
uint16_t ws_front_l()
{
    return gSensorFront_L;
}
uint16_t ws_front_r()
{
    return gSensorFront_R;
}


uint16_t ws_left_wall()
{
    return gLeftWall;
}
uint16_t ws_right_wall()
{
    return gRightWall;
}
uint16_t ws_front_l_wall()
{
    return gFrontWall_L;
}
uint16_t ws_front_r_wall()
{
    return gFrontWall_R;
}
