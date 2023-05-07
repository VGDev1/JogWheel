volatile unsigned int temp, counter = 0; // This variable will increase or decrease depending on the rotation of encoder

#include <Keyboard.h>

#define encoderPinA 3
#define encoderPinB 0
#define x_button 15
#define y_button 14
#define z_button 16
#define z_out A2
#define y_out 9
#define x_out A0


int lastButtonPushed = 0;

void setup()
{
      Serial.begin(9600);

      pinMode(encoderPinA, INPUT_PULLUP); // internal pullup input pin 2

      pinMode(encoderPinB, INPUT_PULLUP); // internalเป็น pullup input pin 3
                                          // Setting up interrupt

      // setup the x,y z button input
      pinMode(x_button, INPUT_PULLUP);
      pinMode(y_button, INPUT_PULLUP);
      pinMode(z_button, INPUT_PULLUP);

      pinMode(z_out, OUTPUT);
      pinMode(y_out, OUTPUT);
      pinMode(x_out, OUTPUT);

      // A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
      attachInterrupt(digitalPinToInterrupt(encoderPinA), ai0, RISING);

      // B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
      attachInterrupt(digitalPinToInterrupt(encoderPinB), ai1, RISING);

      // attach the interrupt to the x button it will go LOW when pressed
      //attachInterrupt(digitalPinToInterrupt(x_button), x_button_pressed, FALLING);

      // attach the interrupt to the y button it will go LOW when pressed
      //attachInterrupt(digitalPinToInterrupt(y_button), y_button_pressed, FALLING);

      // attach the interrupt to the z button it will go LOW when pressed
      //attachInterrupt(digitalPinToInterrupt(z_button), z_button_pressed, FALLING);

}
void loop()
{
      //Serial.println(lastButtonPushed);
      // check if the x button is pressed

      if(digitalRead(x_button) == LOW) {
        x_button_pressed();
      }

            if(digitalRead(y_button) == LOW) {
        y_button_pressed();
      }

            if(digitalRead(z_button) == LOW) {
        z_button_pressed();
      }

      
      // Send the value of counter
      if (counter != temp)
      {
            Serial.println(counter);
            temp = counter;
      }
}

void x_button_pressed()
{
      Serial.println(1);
      lastButtonPushed = 1;
      analogWrite(x_out, 255);
      digitalWrite(y_out, LOW);
      analogWrite(z_out, 0);

}

void y_button_pressed()
{
      Serial.println(2);
      analogWrite(x_out, 0);
      digitalWrite(y_out, HIGH);
      analogWrite(z_out, 0);
      lastButtonPushed = 2;
}

void z_button_pressed()
{
      Serial.println(3);
      analogWrite(x_out, 0);
      digitalWrite(y_out, LOW);
      analogWrite(z_out, 255);
      lastButtonPushed = 3;
}

void move1() {
            switch (lastButtonPushed)
            {
            case 1:
                  Keyboard.press(KEY_LEFT_ARROW); // move left
                  Keyboard.release(KEY_LEFT_ARROW);
                  break;
            case 2:
                  Keyboard.press(KEY_UP_ARROW); // move up
                  Keyboard.release(KEY_UP_ARROW);
                  break;
            case 3:
                  Keyboard.press(KEY_PAGE_DOWN); // page up
                  Keyboard.release(KEY_PAGE_DOWN);
                  break;
            }
}

void move2() {
            switch (lastButtonPushed)
            {
            case 1:
                  Keyboard.press(KEY_RIGHT_ARROW); // move right
                  Keyboard.release(KEY_RIGHT_ARROW);
                  break;
            case 2:
                  Keyboard.press(KEY_DOWN_ARROW); // move down
                  Keyboard.release(KEY_DOWN_ARROW);
                  break;
            case 3:
                  Keyboard.press(KEY_PAGE_UP); // page down
                  Keyboard.release(KEY_PAGE_UP);
                  break;
            }
}


void ai0()
{
      // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
      // Check pin 3 to determine the direction
      if (digitalRead(encoderPinB) == LOW)
      {
            // move left, up, page up
            //move2();
      }
      else
      {
            // move right, down, page down
            //move1();            
      }
}

void ai1()
{
      // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
      // Check with pin 2 to determine the direction
      if (digitalRead(encoderPinA) == LOW)
      {
            move1();
      }
      else
      {
            move2();
      }
}
