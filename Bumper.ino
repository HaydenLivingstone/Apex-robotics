const int B1 = 2;    // Pin numbers of input buttonsv
const int B2 = 3;    
const int B3 = 4;    

int BS1;             // the current reading from the input pin
int BS2;             // the current reading from the input pin
int BS3;             // the current reading from the input pin
int LBS1 = LOW;   // the previous reading from the input pin
int LBS2 = LOW;   // the previous reading from the input pin
int LBS3 = LOW;   // the previous reading from the input pin


long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() 
{
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
}

void loop() 
{
  int R1 = digitalRead(B1);
  int R2 = digitalRead(B2);
  int R3 = digitalRead(B3);

  if ((R1 != LBS1)| (R2 != LBS2) | (R3 != LBS3))
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    if ((R1 != BS1)| (R2 != BS2) | (R3 != BS3))
    {
      BS1 = R1;
      BS2 = R2;
      BS3 = R3;

      if ((BS1 | BS2 | BS3) == HIGH) {
        return 1;
      }
    }
  }
  LBS1 = R1;
  LBS2 = R2;
  LBS3 = R3;
}
