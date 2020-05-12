// edited by: Septian Madiyanto, Pakngah Projects


uint8_t buf[8] = { 0 };   //Keyboard report buffer

#define PIN_UP 4 // Pin for UP
#define PIN_DOWN 5 // Pin for DOWN
#define PIN_RIGHT 6 // Pin for RIGHT
#define PIN_LEFT 7 // Pin for LEFT
#define PIN_SPEED 8 // Pin for Speed Selector
int pulsa=0;
int myspeed=5;
int statusin=1;
int statusinlast=1;
void setup() {
  Serial.begin(9600); // Setup Serial communication

  //Set pinmode of Input pins
  pinMode(PIN_UP, INPUT);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_SPEED, INPUT_PULLUP);
}

void myDelay(int del) {
  unsigned long myPrevMillis = millis();
  while (millis()- myPrevMillis <= del);
}
void loop() {


  statusin=digitalRead(PIN_UP); 
  if (digitalRead(PIN_UP) == HIGH){
    releaseKey();
  }      
  if (statusin!=statusinlast)
  {
    if(statusin==LOW){pulsa++;}
    myDelay(100);
  }
  statusinlast=statusin;
  if (pulsa>=myspeed) {
    
    buf[2] = 82;   
    Serial.write(buf, 8); 
    //Serial.println("UP");
    pulsa=0;    
    myDelay(100);
  }                                                                                                                                                                                                        
  
  if (digitalRead(PIN_SPEED) == LOW) { 
    myspeed=2;
  }
  if (digitalRead(PIN_SPEED) == HIGH){
    myspeed=5;
  }
  
  if (digitalRead(PIN_DOWN) == LOW) {
    
    buf[2] = 81;   // Down keycode
    Serial.write(buf, 8); // Send keypress
    //Serial.println("DOWN");
    
    myDelay(300);
  } 
  
//When button representing S is pressed
  if (digitalRead(PIN_RIGHT) == LOW) {    
    
    buf[2] = 79;   // S keycode
    Serial.write(buf, 8); // Send keypress
    //Serial.println("RIGHT");
    
    myDelay(500);
  }

  
//When button representing D is pressed
  if (digitalRead(PIN_LEFT) == LOW) {
    
    buf[2] = 80;   // D keycode
    Serial.write(buf, 8); // Send keypress
    //Serial.println("LEFT");
   
    myDelay(500);
  }

} 

// Function for Key Release
void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Send Release key 

}
