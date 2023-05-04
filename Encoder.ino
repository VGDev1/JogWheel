volatile unsigned int temp, counter = 0; // This variable will increase or decrease depending on the rotation of encoder

#include <Keyboard.h>

#define encoderPinA 0
#define encoderPinB 3
#define x_button 4
#define y_button 5
#define z_button 6


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

      // A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
      attachInterrupt(digitalPinToInterrupt(0), ai0, RISING);

      // B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
      attachInterrupt(digitalPinToInterrupt(3), ai1, RISING);

      // attach the interrupt to the x button it will go LOW when pressed
      attachInterrupt(digitalPinToInterrupt(4), x_button_pressed, LOW);

      // attach the interrupt to the y button it will go LOW when pressed
      attachInterrupt(digitalPinToInterrupt(5), y_button_pressed, LOW);

      // attach the interrupt to the z button it will go LOW when pressed
      attachInterrupt(digitalPinToInterrupt(6), z_button_pressed, LOW);

}
void loop()
{

      // check if the x button is pressed


      // Send the value of counter
      if (counter != temp)
      {
            Serial.println(counter);
            temp = counter;
      }
}

void x_button_pressed()
{
      lastButtonPushed = 1;
}

void y_button_pressed()
{
      lastButtonPushed = 2;
}

void z_button_pressed()
{
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
                  Keyboard.press(KEY_PAGE_UP); // page up
                  Keyboard.release(KEY_PAGE_UP);
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
                  Keyboard.press(KEY_PAGE_DOWN); // page down
                  Keyboard.release(KEY_PAGE_DOWN);
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
            move1();
      }
      else
      {
            // move right, down, page down
            move2();            
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
