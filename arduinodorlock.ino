/*Note from Ben: I set one of the LEDs to pin 13 to see changes
 but the led is always on.  It goes between a lower brightness 
 to a higher brightness when activated.
 Will check this out later

*/
#include <Password.h> //http://playground.arduino.cc/uploads/Code/Password.zip //tells to use password library
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip  //tells to use keypad library
#include <Servo.h> //tells to use servo library


Servo myservo; //declares servo
Password password = Password( "7538" ); //password to unlock, can be changed

const int unlock = 2;
int unlockState = 0;

const byte ROWS = 4; // Four rows
const byte COLS = 4; // columns
// Define the Keymap
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9, 8, 7, 6 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3 };


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  Serial.write(254);
  Serial.write(0x01);
  delay(200); 
  pinMode(13, OUTPUT);  //green light
  pinMode(12, OUTPUT);  //red light
  pinMode(unlock, INPUT); //unlock button 
  myservo.attach(13); //servo on digital pin 9 //servo
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  }

void loop(){
  if (unlockState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      myservo.write(150);  //unlock
    } 
    // Delay a little bit to avoid bouncing
    delay(40);
  myservo.write(0);  //lock after delay of 10 second
  keypad.getKey();
  myservo.write(0);
  }
  //take care of some special events
  void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
  case PRESSED:
  
  Serial.print("Enter:");
  Serial.println(eKey);
  delay(10);
  
  Serial.write(254);
  
  switch (eKey){
    case '*': checkPassword(); delay(1); break;
    
    case '#': password.reset(); delay(1); break;
    
     default: password.append(eKey); delay(1);
}
}
}
void checkPassword(){
  
if (password.evaluate()){  //if password is right open
    
    Serial.println("Accepted");
    Serial.write(254);delay(10);
    //Add code to run if it works
    myservo.write(150); //deg
    
        digitalWrite(13, HIGH);//turn on
    delay(5000); //wait 5 seconds
    digitalWrite(13, LOW);// turn off
    
    
}else{
    Serial.println("Denied"); //if passwords wrong keep locked
    Serial.write(254);delay(10);
    //add code to run if it did not work
    myservo.write(0);
    digitalWrite(12, HIGH); //turn on
    delay(500); //wait 5 seconds
    digitalWrite(12, LOW);//turn off
    
}
}
