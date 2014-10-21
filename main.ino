#include <Servo.h>

#define  sensorx1  0
#define  sensorx2  1
#define  sensory1  2
#define  sensory2  3

#define  motorx  5
#define  motory  6

//  calibration for sensor values
const float sensx1cal = 1;
const float sensx2cal = 1.5;
const float sensy1cal = 1.15;
const float sensy2cal = 1;

//  calibration for PI controller
const float kpx = 1;
const float kix = 1;
const float kpy = 1;
const float kiy = 1;

//  initial variable setup
Servo  servox, servoy;

float motorxpos, motorypos;  //position in degrees of motor x, y

float sensorx1val, sensorx2val, sensory1val, sensory2val;

float xint, yint, xerr, yerr;

void setup()
{  
  servox.attach(motorx);
  servoy.attach(motory);
  
  servox.write(motorxpos);
  servoy.write(motorypos);
  
  xerr = 0;
  yerr = 0;
  xint = 0;
  yint = 0;
  
  delay(2000);
}

void loop()
{
//  read sensor values__________________________________

  sensorx1val=sensx1cal*analogRead(sensorx1);
  sensorx2val=sensx2cal*analogRead(sensorx2);
  sensory1val=sensy1cal*analogRead(sensory1);
  sensory2val=sensy2cal*analogRead(sensory2);
  
//  PI controller_______________________________________
//  Comment out and uncomment next section if PI is not used
  
  xerr = sensorx1val-sensorx2val;//set point is for sensorx1val-sensorx2val = 0
  yerr = sensory1val-sensory2val;
  
  xint = xint + xerr;//Integral
  yint = yint + yerr;
  
  motorxpos = kix*xint + kpx*xerr;
  motorypos = kiy*yint + kpy*yerr;
  
// This section of code is the simple heuristic part that executes tracking
// to use this, comment out the pid code
// some changes are also required in setting the servo position in the 'rotate motor accordingly' section
  
//  if(sensorx1val-sensorx2val>5){
//    motorxpos=motorxpos+1;//_speed*(sensorx1val-sensorx2val);
//  }
//  if(sensorx1val-sensorx2val<-5){
//    motorxpos=motorxpos-1;//_speed*(sensorx1val-sensorx2val);
//  }
//    
//  if(sensory1val-sensory2val>5){
//    motorypos=motorypos+1;//_speed*(sensory1val-sensory2val);
//  }
//  
//  if(sensory1val-sensory2val<-5){
//    motorypos=motorypos-1;//_speed*(sensory1val-sensory2val);
//  }
  
  //rotate motors accordingly___________________________
  
  if(servox.read()-motorxpos>0&&servox.read()+motorxpos<180){//update servo position if it is within its limits (0 to 180 deg)
//if(servox.read()-motorxpos<2&&servox.read()-motorxpos>-2){//update servo position if it is within its limits (0 to 180 deg) //use this if pid is not used
    servox.write(motorxpos);
  }
  else{
    servox.write(servox.read());
  }
    
  if(servoy.read()-motorypos>0&&servoy.read()+motorypos<180){//similarly update motor y
//  use a different line as mentioned above if PI is not being used
    servoy.write(motorypos);
  }
  else{
    servoy.write(servoy.read());
  }
  
  //delay until next refresh cycle______________________
  delay(200);
}
