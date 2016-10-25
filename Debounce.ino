const int buttonPin = 2;    // the number of the pushbutton pin

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() 
{
  pinMode(buttonPin, INPUT);
}

void loop() 
{
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) 
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        return 1;
      }
    }
  }
  lastButtonState = reading;
}
