// Description: BMFLC filter
// Author: Yan Naing Aye
// http://coolemerald.blogspot.sg/
// Date: 2016 April 15

#include "InputSignal.h"
#include "BMFLC.h"
//--------------------------------------------------------
//Constants
#define MAXK 30   // Maximum sampling instant to count 
#define T 0.01    // Sampling time period in second
//--------------------------------------------------------
//External variables
float k=MAXK;//sampling instant
float s=0;//input signal
float y=0;//filtered signal
//--------------------------------------------------------
//define timer
unsigned long cm=0; //current time in milliseconds
unsigned long lm=0; //store last updated time
//--------------------------------------------------------
void setup() {
  // initialize serial communications 
  Serial.begin(115200);

  InitBMFLC();//initialize BMFLC
}
void loop() {
  cm=millis(); //get current time
  if((cm-lm)>=(1000*T)) {//if timeout
    lm=cm;   //store the updated time
    //----------------------------------------------------
    //Tasks at each sampling instant

    //update time
    k+=T; if(k>=MAXK)k=0;

    //get input signal
    s=GenerateInput(k);
    
    //filter
    y=BMFLC(k,s);
    
    //plot to serial
    PlotSerial(s,y);
    //----------------------------------------------------
  }        
}
void PlotSerial(float x, float y)
{
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print("\n");
}


