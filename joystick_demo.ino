`

#include <SoftwareSerial.h>
String cor; 
String xcor;
String ycor;
String rcor;
int baseHealth = 15;
int robotSpeed = 50; 
int baseSpeed = 50;
int baseDamageSide = 1;
int baseDamageCorner = 2;
int baseDamageBack = 3;
int damage = 1; 
int baseAmmo = 10;
int baseShotPower = 5;
int shotPower = 5;
int noHealthVar = 0;
int stunned = 0;
int magnetPin = 5;
//read input from bluetooth (on tx1 and rx1) and send to PC serial (tx0 and rx0)
//note that TX must be connected to RX and vice versa
//also note ports 18 and 19 (rx1 and tx1) on the Mega clone appear to be switched around!! caused big headaches





void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial1.setTimeout(10);
  Serial.setTimeout(10);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(22, INPUT);
}
void loop() {
  // read from port 1, send to port 0:
  
  int i = 1;
  while (Serial1.available()>0) {
    cor = Serial1.readString(); // Read a character
     if (cor[0]=='N'){
      xcor="100";
      ycor="100";
      rcor="100";
     }
    if (cor[0]== 'X'){
       while (cor[i]!=','){
        char temp=cor[i];
        xcor += temp;
        i++;
       }
       i++;
      while (cor[i]!=','){
        char temp=cor[i];
        ycor += temp;
        i++;
       }
       i++;
       while (cor[i]!=','){
          char temp=cor[i];
          rcor += temp;
          i++;
        } 
        /*Serial.write('X');
        Serial.print(xcor);
        Serial.write('\n');
        Serial.write('Y');
        Serial.print(ycor);
        Serial.write('\n');
        Serial.write('R');
        Serial.print(rcor);
        Serial.write('\n');
        */
     }
    
    if (cor[0]=='N'){
      xcor= "100";
      ycor="100";
      rcor ="100";
      /*Serial.write('X');
      Serial.print(xcor);
      Serial.write('\n');
      Serial.write('Y');
      Serial.print(ycor);
      Serial.write('\n');
      Serial.write('R');
      Serial.print(rcor);
      Serial.write('\n');
    */
    }
    if (cor[0] == 'W'){     //shoot
      //IR transmitter  code for shooting 
      Serial.write("W");
      Serial1.write("w");
      Serial.write("w");
      analogWrite(7, 255);
      delay(1000);
      analogWrite(7, 0);
    }
    if (cor[0]== 'Y'){      //ability
      Serial1.write("l");
      analogWrite(4, 255);
      delay(60000);
      analogWrite(4, 0);
    }
    if (cor[0]== 'A'){      //speedboost reset
      Serial.write("A");
    }
    if (cor[0]== 'B'){      //powershot reset
      Serial.write("B");
    }
    if (cor[0]== 'C'){      //ability normal
      Serial.write("C");
    }
    if (cor[0]== 'D'){      //not invinciable
      Serial.write("D");
    }
    if (cor[0]== 'E'){      
      Serial.write("E");
      robotClassGunner();
    }
    if (cor[0]== 'F'){      
      Serial.write("F");
      robotClassTank();
    }
    if (cor[0]== 'G'){      
      Serial.write("G");
      robotClassSniper();
    }
    if (cor[0]== 'H'){      //healing shot reset
      Serial.write("H");
    }
    if (cor[0]== 'I'){      //Sheild reset
      Serial.write("I");
    }
    if (cor[0]== 'J'){      //not stunned anymore
      Serial.write("J");
    }
    if (cor[0]== 'K'){      //stun shot reset
      Serial.write("K");
    }
    if (cor[0]== 'L'){      //powerup reset
      Serial.write("L");
    }
    if (cor[0]== 'O'){      //magnet
      Serial1.write("O");
      Serial.write("O");
      analogWrite(5, 255);
      //toggle Magnit on or offcode
    }
    if (cor[0]== 'P'){      //magnet
      Serial1.write("P");
      Serial.write("P");
      analogWrite(5, 0);
      //toggle Magnit on or offcode
    }
    //information recived from IR
    if (stunned != 1){
      //controls for movement
    }                                   //Bumper code segment
    cor="";
    xcor="";
    ycor="";
    rcor="";
    i=1;
    
  }
  /*int val = digitalRead(22);
    if (val== LOW){
      analogWrite(6,0);
      Serial.write("u");
      delay(10);
    }
    else if(val == HIGH){
      analogWrite(6,255);
      Serial.write("s");
      delay(10);
    }*/
}

void robotClassGunner(){
  baseHealth = 15;
  baseSpeed = 50;
  baseDamageSide = 1;
  baseDamageCorner = 2;
  baseDamageBack = 3;
  baseAmmo = 16;
  baseShotPower = 3;
  Serial1.write('e');     //will tell the phone that it has the gunner class
  return;
 
}

void robotClassTank(){
  baseHealth = 20;
  baseSpeed = 20;
  baseDamageSide = 1;
  baseDamageCorner = 1;
  baseDamageBack = 2;
  baseAmmo = 8;
  baseShotPower = 5;  
  Serial1.write('f');      //will tell the phone that it has the tank class
  return;
}

void robotClassSniper(){
  baseHealth = 10;
  baseSpeed = 30;
  baseDamageSide = 2;
  baseDamageCorner = 2;
  baseDamageBack = 3;
  baseAmmo = 4;
  baseShotPower = 8;  
  Serial1.write('g');      //will tell the phone that it has the sniper class
  return;
} 

void robotAbilitySheild(){
  
} 

void robotAbilityStunShot(){
  
} 

void robotAbilityHealingShot(){
  
} 

int takeDamageBumper(int damage){
  baseHealth = baseHealth - damage;
  //LED health code
  return baseHealth;
}

int takeDamageShot( int damage){
  baseHealth = baseHealth - damage;
  //LED health code
  return baseHealth;
}

void takeArmourDamage(){
  
}

int getPowerUp(float powerUpSpeed, float powerUpShot){
  int randomPower = random(3);
  if (randomPower == 0){    //speed boost
    float powerUpSpeed = baseSpeed * 1.75;
    Serial1.write('a');      //will tell the phone to count down from 15 with speed increased by 75% then return to normal
  }
  if (randomPower == 1){    //shot power boost
    float powerUpShot = baseShotPower * 1.5;
    Serial1.write('b');      //will tell the phone to count down from 30 with 50% more shot power then return to normal
  }
  if (randomPower == 2){    //buff
    Serial1.write('c');      //will tell the phone to count down from 30 with doubling active abilities then return to normal
  }
  if (randomPower == 3){    //invincible
    Serial1.write('d');      //will tell the phone to count down from 7 with no damage taken then return to normal
  }
  return powerUpSpeed,powerUpShot;
}
