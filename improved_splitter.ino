/*
  Multple Serial test

 Receives from the main serial port, sends to the others.
 Receives from serial port 1, sends to the main serial (Serial 0).

 This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc

 The circuit:
 * Any serial device attached to Serial port 1
 * Serial monitor open on Serial port 0:

 created 30 Dec. 2008
 modified 20 May 2012
 by Tom Igoe & Jed Roach
 modified 27 Nov 2015
 by Arturo Guadalupi

 This example code is in the public domain.

 */
 

String inData;
//String[] values;
void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  
}

void loop() {
  // read from port 1, send to port 0:
  if (Serial.available()) {
   char recieved = Serial.read();
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

            //counts number of blocks
            int numberBlocks = 0;
            //Serial.println(inData.length());
            for (int i=0; i<inData.length(); i++){
              if (inData[i] == ','){
                numberBlocks++;
               }
            }

            //do stuff
            String *values = new String[numberBlocks];
            BlockBreaker(inData, numberBlocks, &values);
            Serial.println(values[1]); //example - access values[1]
            delete[] values;
            inData = "";    
    }
  }
}



//function that takes a comma-seperated string of any length as input and returns an array of strings of that size
 void BlockBreaker(String inData, int numberBlocks, String **values){

            //LOAD ARRAY OF COMMAS (REQUIRED FOR NEXT FUNCTION)
            int comma[numberBlocks];
 
            for (int i=0; i<numberBlocks; i++){
              if (i == 0){
                comma[i] = ((inData.indexOf(',')));
              }
              else{
                comma[i] = (inData.indexOf(',', (comma[i-1])+1));
              }
            }
            //LOAD ARRAY OF STRINGS SEPERATED BY COMMAS
            //String values[numberBlocks];
            for (int z=0; z<numberBlocks; z++){ 
              if (z == 0){
                (* values)[z] = inData.substring(0,comma[z]);
              }
              else {
                (* values)[z] = inData.substring(comma[z-1]+1,comma[z]);
              }
            }

            inData = "";
            return;
        }
