//USAGE NOTES
//make sure you change the array size AND for-loop conditional for both the COMMAS and VALUES functions to the number of datas you are sending (currently 6)
//code must execute before the received buffer is cleared (last line of this program)
//String[i].toInt() function can be used to convert a string to an integer

// Buffer to store incoming commands from serial port
String inData;
    int frr = 10;
    int frf = 11;
    int flr = 13;
    int flf = 12;
    int MAX_PWM_VOLTAGE = 240;
    int blf = 6;
    int blr = 7;
    int brf = 9;
    int brr = 8;
    
void setup() {
    Serial.begin(9600);
    Serial3.begin(9600);
    Serial.println("Serial conection started, waiting for instructions...");

    pinMode(frr,OUTPUT);  //fri=ont right reverse
    pinMode(frf, OUTPUT); //front right forward
    pinMode(flr,OUTPUT);  //front left reverse
    pinMode(flf, OUTPUT); //front left forward
    pinMode(blf,OUTPUT);  //back left forward
    pinMode(blr, OUTPUT); //back left reverse
    pinMode(brf,OUTPUT);  //back right forward
    pinMode(brr, OUTPUT); //back right reverse
}

void loop() {
    //loop that runs every time that serial data is sent
    while (Serial3.available() > 0)
    {

        char recieved = Serial3.read();
        inData += recieved; 

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            Serial.print("Arduino Received: ");
            Serial.print(inData);

            // You can put some if and else here to process the message juste like that:

            if(inData == "+++\n"){ // DON'T forget to add "\n" at the end of the string.
              Serial.println("OK. Press h for help.");
            }   


            //LOAD ARRAY OF COMMAS (REQUIRED FOR NEXT FUNCTION)
            int comma[6];
            for (int i=0; i<6; i++){
              comma[i] = inData.indexOf(',', comma[i-1]+1);
            }

            //LOAD ARRAY OF STRINGS SEPERATED BY COMMAS
            String values[6];
            for (int z=0; z<6; z++){
              if (z == 0){
                values[z] = inData.substring(comma[z-1],comma[z]);
              }
              else {
                values[z] = inData.substring((comma[z-1]+1),comma[z]);
              }
            }

            
            
//            Serial.println("Comma location");
//
//            Serial.println(comma[2]+1);

            Serial.println("Text block");
            Serial.println("values 0");
            Serial.println(values[0].toInt());
            Serial.println("values 1");
            Serial.println(values[1].toInt());
            Serial.println("values 2");
            Serial.println(values[2].toInt());
            Serial.println("values 3");
            Serial.println(values[3].toInt());
            Serial.println("values 4");
            Serial.println(values[4].toInt());
            Serial.println("values 5");
            Serial.println(values[5].toInt());

            if ((values[0].toInt()) > 101){
                digitalWrite(frf, MAX_PWM_VOLTAGE); //front right forward
                digitalWrite(flf, MAX_PWM_VOLTAGE); //front left forward
                analogWrite(frr, LOW);  //front right reverse
                analogWrite(flr, LOW);  //front left reverse
                digitalWrite(blr, LOW); //back left reverse
                digitalWrite(brr, LOW); // back right reverse
                analogWrite(blf, MAX_PWM_VOLTAGE);  //back left forward
                analogWrite(brf, MAX_PWM_VOLTAGE);  //back right forward
            }
            else
            {
                Serial.write("Z");
                digitalWrite(frf, LOW);
                digitalWrite(flf, LOW);
                analogWrite(frr, LOW);
                analogWrite(flr, LOW);
                digitalWrite(blr, LOW);
                digitalWrite(brr, LOW);
                analogWrite(blf, LOW);
                analogWrite(brf, LOW);
            }
//              
//            int firstComma = inData.indexOf(',');
//            int secondComma = inData.indexOf(',',firstComma+1);

//            Serial.println("X Coordinates");
//            Serial.println(inData.substring(0, firstComma));
//            Serial.println("Y Coordinates");
//            Serial.println(inData.substring(firstComma+1, secondComma));
            
            
            inData = ""; // Clear recieved buffer
            
            
            
        }
    }
}
