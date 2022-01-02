# IR_REMOTE_CONTROL_CAR
/* Project Name: IR Remote Control Car
 * Revision Date: 01.01.2022 
 * Author: İrem Sevdenur Doğan 
*/

#include <IRremote.h>      // IR libraries are added to the program.

const int RECV_PIN = 2;    // The pin of the infrared receiver is determined.

//L298N Motor Driver Connection
const int OUT1 = 5;    // IN1 input of L298N
const int OUT2 = 6;    // IN2 input of L298N
const int motor_control_1 = 9;   // ENA input of L298N     // Enable(9 and 10) pins provide speed control.   
const int OUT3 = 7;    // IN3 input of L298N     // Pins 9 and 10 have PWM feature.
const int OUT4 = 8;    // IN4 input of L298N
const int motor_control_2 = 10;  // ENB input of L298      // Enable pins provide speed control.

// HC-SR04 Distance Sensor connection
const int echoPin = 11;
const int trigPin = 12;

int Hiz = 50;    // The speed variable of the motor is defined.
                    // analogWrite function can take values between 0-255.  // Max speed is 255.
IRrecv irrecv(RECV_PIN);       // A new object of type IRrecv is derived.   // Specifies which pin to use.
decode_results results;        // A definition of the results is made.

#define up_arrow 16718055      // Go straight.
#define down_arrow 16730805    // Go back.
#define left_arrow 16716015    // Turn left.
#define right_arrow 16734885   // Turn right.
#define square_key 16756815    // Reduce speed.
#define star_key 16738455      // Increase speed.
#define button_0 16750695      // Stop.

void setup() 
{
  pinMode(OUT1, OUTPUT);        // to the motor driver.
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  pinMode(motor_control_1, OUTPUT);       // Pins to motor driver are defined as OUTPUT.
  pinMode(motor_control_2, OUTPUT);      // The reason why it is defined as OUTPUT is to transfer information 
 

  pinMode(echoPin, INPUT);           // For HC-SR04   // echoPin detects external signal so it is INPUT.
  pinMode(trigPin, OUTPUT);          // trigPin generates signal so it is OUTPUT.

  digitalWrite(motor_control_1, LOW);    // When the arduino is energized, we keep the pins going to the motor driver. 
  digitalWrite(motor_control_2, LOW);
  digitalWrite(OUT1, LOW);     // As soon as the Arduino energizes the card, LOW is defined so that the vehicle
  digitalWrite(OUT2, LOW);    // does not start with the previous commands and the vehicle is de-energized.
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, LOW);
  
  irrecv.enableIRIn();    // For the remote to work.
}
void loop() 
{
  int distance = distance_measurement();
if (distance > 10)
{
  if (irrecv.decode(&results))
   {
    switch(results.value)
     {
      case square_key:
      if(Hiz<255)
      Hiz = Hiz + 10;
      break;
      case star_key:
      if(Hiz>50)
      Hiz = Hiz - 10;
      break;
      case up_arrow:
      motor_movements(1,0,0,1,Hiz);
      break;
      case down_arrow:
      motor_movements(0,1,1,0,Hiz);
      break;
      case left_arrow:
      motor_movements(1,0,1,0,Hiz);
      break;
      case right_arrow:
      motor_movements(0,1,0,1,Hiz);
      break;
      case button_0:
      motor_movements(0,0,0,0,0);
      break;
     }
    irrecv.resume(); 
  }
 }
else
 {
  motor_movements(0,1,1,0,Hiz);
  delay(500);
  motor_movements(0,0,0,0,0);
 }
}

int distance_measurement()       // For HC-SR04     // Distance measurement.
{
  long duration, distance;
  digitalWrite(trigPin, LOW);   // The sensor emits an ultrasonic sound wave.
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // echopin is activated when waves hit an obstacle and bounce back.
  distance = duration / 29.1 / 2;         // When the return time of the wave is known, the distance can be calculated.
  delay(50);                          // To convert the distance in cm, the time is divided by 58.2.
  return distance;      // so it returns after 50.
}

void motor_movements(int value1, int value2, int value3, int value4, int Hiz)
{
digitalWrite(OUT1, value1);
digitalWrite(OUT2, value2);
digitalWrite(OUT3, value3);
digitalWrite(OUT4, value4);
analogWrite(motor_control_1, Hiz);
analogWrite(motor_control_2, Hiz);
}
