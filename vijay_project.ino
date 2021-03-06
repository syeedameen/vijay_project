/*********************************************************************************************************/
/*                                                                                                       */
/* Author: SYEED MOHD AMEEN                                                   Date: 14-09-2021           */
/* Email:   ameensyeed2@gmail.com                                                                        */
/*                                                                                                       */
/*********************************************************************************************************/

/*********************************************************************************************************/
/*                                      THE MIT LICENSE (MIT)                                            */
/*-------------------------------------------------------------------------------------------------------*/
/* Permission is hereby granted, free of charge, to any person obtaining a copy of this software         */
/* and associated documentation files (the "Software"), to deal in the Software without restriction,     */
/* including without limitation the rights to use, copy, modify, merge, publish, distribute,             */
/* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software            */
/* is furnished to do so, subject to the following conditions:                                           */
/*                                                                                                       */
/* The above copyright notice and this permission notice shall be included in all copies                 */
/* or substantial portions of the Software.                                                              */
/*                                                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,                   */
/* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE      */
/* AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,      */
/* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF */
/* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                      */
/*********************************************************************************************************/





/* HC-SR04 Sensor range 4-Meters (actually 2-Meter but 4-Meter is safe side) */
#define MAX_DISTANCE  400 
#define MIN_DISTANCE  2 

/* Led pins statically declare in EEPROM  (make sure your pins are active high)*/
static byte green[] = {3,4};
static byte red[]   = {5,6};

/* sensor pins statically declare in EEPROM */
static byte trigger[] = {7,8};
static byte echo[]    = {9,10};
  
float distance[2];
float duration[2];

/* setup all the Input/Output */
void setup() {
  Serial.begin(9600);
  /* led output pin declaration */
  for (byte i=0; i<2; i++){
    pinMode(red[i], OUTPUT);
    pinMode(green[i], OUTPUT);
  }

  /* set initial states of leds (green led is high) */
  for (byte i=0; i<2; i++){
    digitalWrite(red[i], LOW);
    digitalWrite(green[i], LOW);
  }

  /* set trigger & Echo pin modes */
  for (byte i=0; i<2; i++){
    pinMode(trigger[i], OUTPUT);
    pinMode(echo[i], INPUT);
  }
}

void loop() {
  digitalWrite(trigger[0], LOW);
  delayMicroseconds(2);
  digitalWrite(trigger[0], HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigger[0], LOW);

  /* Measure the response from sensor pins ECHO */
  duration[0] = pulseIn(echo[0], HIGH);

  /* Determine distance from duration */
  /* Use 343 meters/sec as speed of sound (if humidity is constant) */
  distance[0] = (duration[0] / 2) * (0.0343);


  /* Read data from second Sensor */
  digitalWrite(trigger[1], LOW);
  delayMicroseconds(2);
  digitalWrite(trigger[1], HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigger[1], LOW);

  /* Measure the response from sensor pins ECHO */
  duration[1] = pulseIn(echo[1], HIGH);

  /* Determine distance from duration */
  /* Use 343 meters/sec as speed of sound (if humidity is constant) */
  distance[1] = (duration[1] / 2) * (0.0343);

  Serial.print(" Distance = ");
  if (distance[0] >= MAX_DISTANCE || distance[0] < MIN_DISTANCE){
    Serial.println(" sensor 1 <-----Out of range----->");
      
      digitalWrite(red[0], HIGH);
      digitalWrite(green[0], LOW);
  }
  else {
    Serial.println("Sensor 1 ");
    Serial.print(distance[0]);
    Serial.println(" CM ");

      digitalWrite(red[0], LOW);
      digitalWrite(green[0], HIGH);
  }

  if (distance[1] >= MAX_DISTANCE || distance[1] < MIN_DISTANCE){
    Serial.println(" sensor 2 <-----Out of range----->");

      digitalWrite(red[1], HIGH);
      digitalWrite(green[1], LOW);
  }
  else { 
    Serial.println("Sensor 2 ");
    Serial.print(distance[1]);
    Serial.println(" CM ");

      digitalWrite(red[1], LOW);
      digitalWrite(green[1], HIGH);
  }
  delay(500);           /* set delay according to your requirment */
}
