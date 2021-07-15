/*
  Autonomous movement file for robot snake with 6 servos
*/

#include <Servo.h> 

// Define servo objects for the snake segments
Servo s1; 
Servo s2;
Servo s3;
Servo s4; 
Servo s5;
Servo s6;

Servo panServo;
  
// Define variables
const int IRpin = A1;
const int NUM_reading = 100; //number of readings taken from ir sensor
int readDelay = 10;
int a[NUM_reading];
int Tolerance = 450;
int distanceReading;
int distanceReadingLeft;
int distanceReadingRight;
int panDelay = 1000;

int forwardVal = 0;  // Remote control variables
int reverseVal = 0;
int rightVal = 0;
int leftVal = 0;

int counter = 0; // Loop counter variable
float lag = 22.0/21; // Phase lag between segments
int frequency = 2; // Oscillation frequency of segments.
int amplitude = 40; // Amplitude of the serpentine motion of the snake
int rightOffset = 8; // Right turn offset
int leftOffset = -8; // Left turn offset
int offset = 0; // Variable to correct servos that are not exactly centered
int delayTime = 5; // Delay between limb movements
int startPause = 5000;  // Delay time to position robot
int test = -3; // Test varialble takes values from -6 to +5

int get_avg_reading(int *a,int n){
  float mean = 0,absolute_error = 0;
  for(int i = 0;i<n;i++){
    mean += a[i];
  }
  mean = mean/n;
  for(int i = 0;i<n;i++)absolute_error += abs(mean - a[i]);
  absolute_error /= n;
  return (mean+absolute_error);
}

void setup() 
{ 
  
  
  // Attach segments to pins  
  s1.attach(3);
  s2.attach(4);
  s3.attach(6);
  s4.attach(7);
  s5.attach(8);
  s6.attach(12);
  
  panServo.attach(11);
 
  // Put snake in starting position
  s1.write(75+offset+amplitude*cos(3*lag));
  delay(1000);
  s2.write(90+amplitude*cos(2*lag)); 
  delay(1000);
  s3.write(90+amplitude*cos(1*lag));
  delay(1000);
  s4.write(90+amplitude*cos(0*lag));
  delay(1000);
  s5.write(90+amplitude*cos(-1*lag));
  delay(1000);
  s6.write(90+amplitude*cos(-2*lag));
  delay(1000);
  
} 
  
void loop() {
  // Point distance sensor straight ahead
  panServo.write(90);
  delay(panDelay);
  //take readings
  for(int i =0;i<NUM_reading;i++){
    a[i] = analogRead(IRpin);
    delay(readDelay);
  }
  distanceReading = get_avg_reading(a,NUM_reading);
  
  //if distanceReding <= 450 move forward
  if (distanceReading <= 450 ){  
    for(counter = 0; counter < 360; counter += 1)  {
      s1.write(75+amplitude*cos(frequency*counter*3.14159/180+3*lag));
      delay(delayTime);
      s2.write(90+amplitude*cos(frequency*counter*3.14159/180+2*lag));
      delay(delayTime);
      s3.write(90+amplitude*cos(frequency*counter*3.14159/180+1*lag));
      delay(delayTime);
      s4.write(90+amplitude*cos(frequency*counter*3.14159/180+0*lag));
      delay(delayTime);
      s5.write(90+amplitude*cos(frequency*counter*3.14159/180-1*lag));
      delay(delayTime);
      s6.write(90+amplitude*cos(frequency*counter*3.14159/180-2*lag));
      delay(delayTime);
         
    }
  }

  
  // distance measurements to the left and right
  else  {
    panServo.write(10);
    delay(panDelay);
    for(int i =0;i<NUM_reading;i++){
    a[i] = analogRead(IRpin);
    delay(readDelay);
  }
  distanceReadingRight = get_avg_reading(a,NUM_reading);
    
    
    
    
    panServo.write(170);
    delay(panDelay);
    for(int i =0;i<NUM_reading;i++){
    a[i] = analogRead(IRpin);
    delay(readDelay);
  }
  distanceReadingLeft = get_avg_reading(a,NUM_reading);
  
    panServo.write(90);
    delay(panDelay);

    if (distanceReadingRight> distanceReadingLeft) {
      // Reverse and then turn left
      // Reverse
      for(counter = 360; counter > 0; counter -= 1) {
	s1.write(75+offset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
	delay(delayTime);
	s2.write(90+amplitude*cos(frequency*counter*3.14159/180+2*lag));
	delay(delayTime);
	s3.write(90+amplitude*cos(frequency*counter*3.14159/180+1*lag));
	delay(delayTime);
	s4.write(90+amplitude*cos(frequency*counter*3.14159/180+0*lag));
	delay(delayTime);
	s5.write(90+amplitude*cos(frequency*counter*3.14159/180-1*lag));
	delay(delayTime);
	s6.write(90+amplitude*cos(frequency*counter*3.14159/180-2*lag));
	delay(delayTime);
          
      }    
  
      // Left turn
      // Ramp up turn offset
      for(counter = 0; counter < 10; counter += 1)  {
      
	s1.write(75+offset+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
	delay(delayTime);
	s2.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
	delay(delayTime);
	s3.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
	delay(delayTime);
	s4.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
	delay(delayTime);
	s5.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
	delay(delayTime);
	s6.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
	delay(delayTime);
          
      }  
      // Continue left turn
      for(counter = 11; counter < 350; counter += 1)  {
      
	s1.write(75+offset+leftOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
	delay(delayTime);
	s2.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
	delay(delayTime);
	s3.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
	delay(delayTime);
	s4.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
	delay(delayTime);
	s5.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
	delay(delayTime);
	s6.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
	delay(delayTime);
        
      }    
      // Ramp down turn offset
      for(counter = 350; counter < 360; counter += 1)  {
	delay(delayTime);
	s1.write(75+offset+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
	delay(delayTime);
	s2.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
	delay(delayTime);
	s3.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
	delay(delayTime);
	s4.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
	delay(delayTime);
	s5.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
	delay(delayTime);
	s6.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
	delay(delayTime);
          
      } 
    }


    if (distanceReadingLeft >= distanceReadingRight) {
  
      // Reverse and turn right
      // Reverse
      for(counter = 360; counter > 0; counter -= 1)  {
      
	s1.write(75+offset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
	delay(delayTime);
	s2.write(90+amplitude*cos(frequency*counter*3.14159/180+2*lag));
	delay(delayTime);
	s3.write(90+amplitude*cos(frequency*counter*3.14159/180+1*lag));
	delay(delayTime);
	s4.write(90+amplitude*cos(frequency*counter*3.14159/180+0*lag));
	delay(delayTime);
	s5.write(90+amplitude*cos(frequency*counter*3.14159/180-1*lag));
	delay(delayTime);
	s6.write(90+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
	delay(delayTime);
      
      }    
      // Turn right
      // Ramp up turn offset
      for(counter = 0; counter < 10; counter += 1)  {
      
	s1.write(75+offset+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
	delay(delayTime);
	s2.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
	delay(delayTime);
	s3.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
	delay(delayTime);
	s4.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
	delay(delayTime);
	s5.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
	delay(delayTime);
	s6.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
	delay(delayTime);
          
      }  
      // Continue right turn
      for(counter = 11; counter < 350; counter += 1)  {
    
	s1.write(75+offset+rightOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
	delay(delayTime);
	s2.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
	delay(delayTime);
	s3.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
	delay(delayTime);
	s4.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
	delay(delayTime);
	s5.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
	delay(delayTime);
	s6.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
	delay(delayTime);
        
      }    
      // Ramp down turn offset
      for(counter = 350; counter < 360; counter += 1)  {
      
	s1.write(75+offset+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
	delay(delayTime);
	s2.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
	delay(delayTime);
	s3.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
	delay(delayTime);
	s4.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
	delay(delayTime);
	s5.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
	delay(delayTime);
	s6.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
	delay(delayTime);
      
      } 
    }   
  
  }
   
}