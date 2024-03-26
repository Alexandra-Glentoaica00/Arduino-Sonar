#include <Servo.h>

//servo
int servo_control_pin = 3;
int servo_position = 0;
int position_increment = 5;
Servo myServo;

//ultrasonic sensor
int trigger_pin = 8;
int echo_pin = 9;
unsigned long ping_echo_time;
float sound_speed = 0.034;
float distance;

//buzzer
int buzzer_pin = 5;

int flag=0;

float ultrasonic_sensor_read(){
  float dist;
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  ping_echo_time=pulseIn(echo_pin, HIGH); //this time is in microseconds
  delay(200);
  dist=sound_speed*ping_echo_time/2; //this distance will be in centimenters
  return dist;
}

void setup() {
  Serial.begin(9600);
  myServo.attach(servo_control_pin);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);

}

void loop() {
  myServo.write(servo_position);
  distance=ultrasonic_sensor_read();
  if(distance < 100){
    tone(buzzer_pin, 1000);
    Serial.println("Object has been detected!");
    Serial.println(distance); 
  }

  if(distance > 100){
    noTone(buzzer_pin); 
  }

  if(flag == 0){
     servo_position += position_increment;
     if(servo_position == 180){
        flag = 1;
     }
  }else if(flag == 1){
      servo_position -= position_increment;
      if(servo_position == 0){
        flag = 0;
      }
  }

  delay(200);
  
}
