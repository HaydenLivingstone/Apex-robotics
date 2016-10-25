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
    int MAX_PWM_VOLTAGE = 100;
    int blf = 6;
    int blr = 7;
    int brf = 9;
    int brr = 8;
    int values0;
    int values1;
    int values2;
    int values3;
    int values4;
    int values5;
    int pmws;
    
void setup() {
    Serial.begin(9600);
    Serial3.begin(9600);
    Serial.println("Serial conection started, waiting for instructions...");
    Serial3.setTimeout(10);
    Serial.setTimeout(10);
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

        // Process message when new line character is recieved ONLY WHEN \n IS RECEIVED
        if (recieved == '\n')
        {
           Serial.print("Arduino Received: ");
            Serial.print(inData);

            // You can put some if and else here to process the message juste like that:

            if(inData == "+++\n"){ // DON'T forget to add "\n" at the end of the string.
              Serial.println("OK. Press h for help.");
            }   

          
            //LOAD ARRAY OF COMMAS (REQUIRED FOR NEXT FUNCTION)
            int comma[5];
            for (int i=0; i<5; i++){
              if (i == 0){
                comma[i] = inData.indexOf(',');
              }
              else{
              comma[i] = inData.indexOf(',', comma[i-1]+1);
              }
            }
            
//            Serial.println("COMMA START");
//            Serial.println(comma[0]);
//            Serial.println(comma[1]);
//            Serial.println(comma[2]);
//            Serial.println(comma[3]);
//            Serial.println("COMMA END");

            //LOAD ARRAY OF STRINGS SEPERATED BY COMMAS
            String values[5];
            for (int z=0; z<6; z++){
              if (z == 0){
                values[z] = inData.substring(comma[z-1],comma[z]);
              }
              else {
                values[z] = inData.substring((comma[z-1]+1),comma[z]);
              }
            }

            
            
//            Serial.println("Comma location");
//          //where do
            //Serial.println(comma[2]+1);
            values0 = values[0].toInt();
            values1 = values[1].toInt();
            values2 = values[2].toInt();
            values3 = values[3].toInt(); 
            values4 = values[4].toInt();
            values5 = values[5].toInt();
             

            Serial.println(values0);

            Serial.println(values1);

            Serial.println(values2);

            Serial.println(values3);

            Serial.println(values4);

            Serial.println(values5);

           
            if (values1 > 101){
                pmws = values1 - 50;
                analogWrite(frf, pmws); //front right forward
                analogWrite(flf, pmws); //front left forward
                analogWrite(frr, LOW);  //front right reverse
                analogWrite(flr, LOW);  //front left reverse
                analogWrite(blr, LOW); //back left reverse
                analogWrite(brr, LOW); // back right reverse
                analogWrite(blf, pmws);  //back left forward
                analogWrite(brf, pmws);  //back right forward
                //Serial.println(pmws);
            }
            if (values1 < 99){
                pmws = 150 - values1;
                analogWrite(frf, LOW); //front right forward
                analogWrite(flf, LOW); //front left forward
                analogWrite(frr, pmws);  //front right reverse
                analogWrite(flr, pmws);  //front left reverse
                analogWrite(blr, pmws); //back left reverse
                analogWrite(brr, pmws); // back right reverse
                analogWrite(blf, LOW);  //back left forward
                analogWrite(brf, LOW);  //back right forward
                //Serial.println(-pmws); 
            }           
            if (values1 == 100)
            {
                pmws = 0;
                analogWrite(frf, LOW);
                analogWrite(flf, LOW);
                analogWrite(frr, LOW);
                analogWrite(flr, LOW);
                analogWrite(blr, LOW);
                analogWrite(brr, LOW);
                analogWrite(blf, LOW);
                analogWrite(brf, LOW);
                //Serial.println(pmws);
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

