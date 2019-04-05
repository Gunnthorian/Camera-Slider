#include <math.h>
#define PI 3.1415926535897932384626433832795

int stepPin_0 = 5;
int dirPin_0 = 6;
int stepPin_1 = 3;
int dirPin_1 = 4;
int enblPin = 7;

const int DIR = 1;
const double TIME = 5;
const int TRAVEL_DISTANCE = 17;
const int FOCUS_DISTANCE = 12;

const int rot_dir = abs(DIR - 1);
const double steps = TRAVEL_DISTANCE * 1262;
const double focus_steps = FOCUS_DISTANCE * 1262;
const double time_micros = TIME * 60 * 1000000;
const double step_delay = time_micros / steps;
const double start_angle = ((atan(focus_steps/(steps/2)))/PI)*180;
const double angle_steps_left = abs((start_angle/90) - 1) * 400;

double steps_traveled = 0;
double current_angle = angle_steps_left;

void setup() {
  Serial.begin(9600);
  pinMode (stepPin_0, OUTPUT); 
  pinMode (dirPin_0, OUTPUT); 
  pinMode (stepPin_1, OUTPUT); 
  pinMode (dirPin_1, OUTPUT); 
  pinMode (enblPin, OUTPUT); 
  digitalWrite(stepPin_0, LOW); 
  digitalWrite(dirPin_0, DIR); 
  digitalWrite(stepPin_1, LOW); 
  digitalWrite(dirPin_1, rot_dir); 
  digitalWrite(enblPin, HIGH); 
  Serial.print(((atan(focus_steps/(steps/2)))/PI)*180);
  Serial.print(" ");
  Serial.print(angle_steps_left);
}

void loop() {
  for(double x=0; x<steps; x++){ 
    digitalWrite(stepPin_0, HIGH);
    digitalWrite(stepPin_0, LOW); 
    if(steps_traveled < steps/2 && current_angle > abs(( (((atan(focus_steps/(steps/2 - steps_traveled)))/PI)*180) /90) - 1) * 400){
      digitalWrite(stepPin_1, HIGH);  
      digitalWrite(stepPin_1, LOW); 
      current_angle--;
    }
    if(steps_traveled > steps/2 && current_angle < abs(( (((atan(focus_steps/(steps_traveled - steps/2)))/PI)*180) /90) - 1) * 400){
      digitalWrite(stepPin_1, HIGH);  
      digitalWrite(stepPin_1, LOW); 
      current_angle++;
    }
    delayMicroseconds(step_delay);
    steps_traveled++;
  }
  digitalWrite(enblPin, LOW); 
  exit(0);
}
