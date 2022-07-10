/* 
 *  Sketch to aid monitoring the the status of ZF test-benchs
 *  The LED indicators are taken in the order of importance.
 *  RED -> HIGH Priority
 *  YELLOW -> MEDIUM Priority
 *  GREEN -> MEDIUM Priority
 *  
 *  Implemented by: Chima Ochiagha
 *  Role: Test Engineering Intern
 *  Data Started: 6/3/2022 
 */
#include <SPI.h>
#include  <Ethernet.h>

                                        //GLobal Variables
/* ---------------------------------------------------------------------------------------------------*/
/*LED pins | Note: Can be re-set by the programmer */
/* LED order:{Red, Yellow, Green}*/
int C1TBLED[3] = {22,23,24}; 
int C2TBLED[3] = {25,26,27}; 
int C3TBLED[3] = {28,29,30}; 
int C4TBLED[3] = {31,32,33}; 
int C5TBLED[3] = {34,35,36};
int ED1TBLED[3] = {37,38,39};  
int ED2TBLED[3] = {40,41,42};  
char color1 = 'G';     //Combustion engine Test bench 1
char color2 = 'G';     //Combustion engine Test bench 2
char color3 = 'G';     //Combustion engine Test bench 3
char color4 = 'G';     //Combustion engine Test bench 4
char color5 = 'G';     //Combustion engine Test bench 5
char color6 = 'G';     //Electrical engine Test bench 1
char color7 = 'G';     //Electrical engine Test bench 2

/* ---------------------------------------------------------------------------------------------------*/

       /* Global function declarations */

/*
 * Function to check the Status for the LED devices
 */
char CET1();      //Combustion engine Test bench 1
char CET2();      //Combustion engine Test bench 2
char CET3();      //Combustion engine Test bench 3
char CET4();      //Combustion engine Test bench 4
char CET5();      //Combustion engine Test bench 5
char EET1();      //Electrical engine Test bench 1
char EET2();      //Electrical engine Test bench 2

/* Functions: check the LED status for the test benches
 *  Params: None
 *  Return: Boolean values */
/* Functions to check the Red LED pins for all the combustion benches */
bool checkRed_Comb1();
bool checkRed_Comb2();
bool checkRed_Comb3();
bool checkRed_Comb4();
bool checkRed_Comb5();
bool checkRed_ED1();
bool checkRed_ED2();
/* Function to check the yellow LED pins for all the combustion benches */
bool checkYellow_Comb1();
bool checkYellow_Comb2();
bool checkYellow_Comb3();
bool checkYellow_Comb4();
bool checkYellow_Comb5();
bool checkYellow_ED1();
bool checkYellow_ED2();
/* Function to check the Green LED pins for all the combustion Pins*/
bool checkGreen_Comb1();
bool checkGreen_Comb2();
bool checkGreen_Comb3();
bool checkGreen_Comb4();
bool checkGreen_Comb5();
bool checkGreen_ED1();
bool checkGreen_ED2();
  
/* ---------------------------------------------------------------------------------------------------*/
/* Ethernet Config */
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xEF, 0xED};   //Hard ware mac address (arbitrarily selected)
IPAddress ip(192,168, 1, 20);

EthernetServer server(80);                          //TCP server port
  
/* ---------------------------------------------------------------------------------------------------*/
/* Program  setup */
void setup() {
  //INnstantiate Serial Comms
  Serial.begin(9600);
  Serial.println("Program begins");
  Serial.println("Configuring the server IP address");

  //Get the IP config from the DHCP server
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("The server is at: ");
  Serial.println(Ethernet.localIP());

  //Instantiate the LED pins value holders
  for(int i = 0; i < 3; i++) {
    pinMode(C1TBLED[i], INPUT);      //Instantiate the LED pins to be read as inputs
  }

  
}

/* ---------------------------------------------------------------------------------------------------*/

void loop() {
    checkClient();
}


/* Ethernet Funtions */
void checkClient() {
   //Instantiate the Ethernet client
   EthernetClient client = server.available();
   
   if(client) {                     //Check if the server's available for the client
    Serial.print("new Client");
      while(client.connected()){    //Check if the server's connected to the port
        if(client.available()){     //Check if the client's connected to the server
           char c = client.read();   //Read a char from the client
           Serial.write(c);   //Print the char on the serial Monitor

          //Publishing to the client server
          if(c == '\n'){
            client.println("HTTP/1.1 200 OK"); //Sever request quote
            client.println("Connection-Type: text/html");
            client.println("Connection: close");
            client.println("Refresh: 2");  // refresh the page automatically every 5 sec
            client.println(); 

           /* Publish HTML page initialization */
            client.println(" <!DOCTYPE html>");
            client.println(" <html lang='en' dir='ltr'> ");
            client.println(" <head> ");
            client.println(" <meta charset='utf-8'> ");
            client.println(" <meta name='viewport' content='width=device-width, initial-scale =1'> ");
            client.println(" <title>Status Monitor</title> ");
 
            client.println(" </head> ");
            client.println(" <style> ");
            
           /*------------------------------------------------------------BEGN OF CSS SEG -------------------------------------------------------------------*/ 
            client.println(" title{ text-align: center; pos} ");
            client.println(" h1 {text-align: center;} ");
            client.println(" h2 {overflow-wrap: break-word;} ");
            client.println(" p{ font-weight:bold; font-size: 30;} ");
            client.println(" .Comb_Dyno_4{ position: absolute; right:0; top:47px;} ");
            client.println(" .Comb_Dyno_5{ position: absolute; right:0px; top:295px; word-wrap: break-word;}  ");
            client.println(" .E-Dyno_1{ position: absolute; right:0; top:550px;} ");
            client.println(" .E-Dyno_2{ text-align: center; left:50%; top:50%; } ");
            
            //Comb1 frame segment
            client.println(" .CB1{  width: 100px; height:100px; padding-top:30px; padding-bottom:50px; padding-left: 30px; padding-right: 30px; text-align: center; border: 3px solid #000000; ");
            //Check for status here
            CET1();        //Call the checking function
            switch(color1) {
              case 'R': client.println(" background-color: #FF5733; }"); break;
              case 'Y': client.println(" background-color: #F8FF33; }"); break;
              case 'G': client.println(" background-color: #4CAF50; }"); break;
            }
            //Comb2 frame segment
            client.println(" .CB2{ width: 100px; height:100px; padding-top:30px; padding-bottom:50px; padding-left: 30px; padding-right: 30px; text-align: center; border: 3px solid #000000; ");
            //Check for status here
             CET2();        //Call the checking function
            switch(color2) {
              case 'R': client.println(" background-color: #FF5733; }"); break;
              case 'Y': client.println(" background-color: #F8FF33; }"); break;
              case 'G': client.println(" background-color: #4CAF50; }"); break;
            }

            //Comb3 frame segment
            client.println(" .CB3{ width: 100px; height:100px; padding-top:30px; padding-bottom:50px; padding-left: 30px; padding-right: 30px; text-align: center; border: 3px solid #000000; ");
            //Check for status here
            CET3();        //Call the checking function
            switch(color3) {
              case 'R': client.println(" background-color: #FF5733; }"); break;
              case 'Y': client.println(" background-color: #F8FF33; }"); break;
              case 'G': client.println(" background-color: #4CAF50; }"); break;
            }

            //Comb4 frame segment
            client.println(" .CB4{ width: 100px; height:100px; position: absolute; right: 0; top:100px; padding-top:30px; padding-bottom:50px; padding-left: 30px; padding-right: 30px; text-align: center; border: 3px solid #000000; ");
            //Check for status here
             CET4();        //Call the checking function
            switch(color4) {
              case 'R': client.println(" background-color: #FF5733; }"); break;
              case 'Y': client.println(" background-color: #F8FF33; }"); break;
              case 'G': client.println(" background-color: #4CAF50; }"); break;
            }

            //Comb5 frame segment
            client.println(" .CB5{ width: 100px; height:100px; position: absolute; right: 0; top:350px; padding-top:30px; padding-bottom:50px; padding-left: 30px; padding-right: 30px; text-align: center; border: 3px solid #000000; ");
            //Check for status here
             CET5();        //Call the checking function
            switch(color5) {
              case 'R': client.println(" background-color: #FF5733; }");  break;
              case 'Y': client.println(" background-color: #F8FF33; }"); break;
              case 'G': client.println(" background-color: #4CAF50; }"); break;
            }

            //ED1 frame Segment
            client.println(" .ED1{ width: 100px; height:100px; position: absolute; right: 0; top:600px; padding-top:30px; padding-bottom:50px; padding-left: 30px; padding-right: 30px; text-align: center; border: 3px solid #000000; ");
            //Check for status here
            EET1();        //Call the checking function
            switch(color6) {
              case 'R': client.println(" background-color: #FF5733; }"); break;
              case 'Y': client.println(" background-color: #F8FF33; }"); break;
              case 'G': client.println(" background-color: #4CAF50; }"); break;
            }

            //ED2 Frame Segment
            client.println(" .ED2{ top:25%; right:50%; padding-top:30px; padding-bottom:50px; padding-left: 30px; padding-right: 30px; text-align: center; border: 3px solid #000000; ");
            //Check for status here
            EET2();        //Call the checking function
            switch(color7) {
              case 'R': client.println(" background-color: #FF5733; }"); break;
              case 'Y': client.println(" background-color: #F8FF33; }"); break;
              case 'G': client.println(" background-color: #4CAF50; }"); break;
            }

            /*------------------------------------------------------------END OF CSS SEG -------------------------------------------------------------------*/ 
            
            client.println(" .button { background-color: #4CAF50; border: none; position: absolute; right: 0; color: white; padding: 20px 50px; text-align: center; text-decoration: none; display: inline-block; font-size: 20px; margin: 4px 2px; cursor: pointer;" );
            client.println(" </style> ");
            client.println("<body><h1 >Test Bench Operation Monitor</h1> ");
            //Test Bench 1
            client.println(" <h2 id='Comb_Dyno 1'> Com. Dyno Test Bench 1 </h2> ");
            client.println(" <div class='CB1'> ");
            client.println(" <p id=CB1_stat>Status Signal</p> ");
            client.println(" </div> ");
            //Check for status change

            //Combustion Test Bench 2
            client.println(" <h2 id='Comb_Dyno 2'> Comb. Dyno T.B 2  </h2> ");
            client.println(" <div class='CB2'> ");
            client.println(" <p id=CB2_stat>Status Signal</p> ");
            client.println(" </div> ");
            //Check for status change
            
            //Combustion Test Bench 3
            client.println(" <h2 id='Comb_Dyno 3'> Comb. Dyno T.B 3  </h2> ");
            client.println(" <div class='CB3'> ");
            client.println(" <p id=CB3_stat>Status Signal</p> ");
            client.println(" </div> ");
            //Check for status change

            //Combustion Test Bench 4 
            client.println(" <h2 class='Comb_Dyno_4'> Comb. Dyno T.B 4  </h2> ");
            client.println(" <div class='CB4'> ");
            client.println(" <p id=CB4_stat>Status Signal</p> ");
            client.println(" </div> ");
            //Check for status change

            //Combustion Test Bench 5 (Proposed)
            client.println(" <h2 class='Comb_Dyno_5'> Comb. Dyno T.B 5 </h2> ");
            client.println(" <div class='CB5'> ");
            client.println(" <p id=CB5_stat>Status Signal</p> ");
            client.println(" </div> ");
            //Check for status change

            //E-Dyno Test Bench 1 (Proposed)
            client.println(" <h2 class='E-Dyno_1'>E-Dyno T.B 1 </h2> ");
            client.println(" <div class='ED1'> ");
            client.println(" <p id=ED1_stat>Status Signal</p> ");
            client.println(" </div> ");
            //Check for status change

            //E-Dyno Test Bench 2 (Proposed)
            client.println(" <h2 class='E-Dyno_2'>E-Dyno T B 2 </h2> ");
            client.println(" <div class='ED2'> ");
            client.println(" <p id=ED2_stat>Status Signal</p> ");
            client.println(" </div> ");
            //Check for status change

            client.println(" </body> ");
            client.println(" </html> ");
            
           //Terminate the client server
            delay(1);
            client.stop();
          }
        }
      }
   }
}

char CET1() {
  if(checkRed_Comb1()){
    color1 = 'R';
  }
  else if(checkYellow_Comb1()){
    color1 = 'Y';
  }
  else{
    color1 = 'G';
  }
}

char CET2(){
  if(checkRed_Comb2()){
    color2 = 'R';
  }
  else if(checkYellow_Comb2()){
    color2 = 'Y';
  }
  else{
    color2 = 'G';
  }
}

char CET3() {
  if(checkRed_Comb3()){
    color3 = 'R';
  }
  else if(checkYellow_Comb3()){
    color3 = 'Y';
  }
  else{
    color3 = 'G';
  }
}
char CET4() {
  if(checkRed_Comb4()){
    color4 = 'R';
  }
  else if(checkYellow_Comb4()){
    color4 = 'Y';
  }
  else{
    color4 = 'G';
  }
}
char CET5() {
  if(checkRed_Comb5()){
    color5 = 'R';
  }
  else if(checkYellow_Comb5()){
    color5 = 'Y';
  }
  else{
    color5 = 'G';
  }
}
char EET1() {
  if(checkRed_ED1()){
    color6 = 'R';
  }
  else if(checkYellow_ED1()){
    color6 = 'Y';
  }
  else{
    color6 = 'G';
  }
}

char EET2() {
  if(checkRed_ED2()){
    color7 = 'R';
  }
  else if(checkYellow_ED2()){
    color7 = 'Y';
  }
  else{
    color7 = 'G';
  }
}

bool checkRed_Comb1() {
  //Check for Red light
        if(digitalRead(C1TBLED[0])) {
          //Indicate color red color
          return true;
        }
        return false;
}
bool checkRed_Comb2() {
   //Check for yellow light
  if(digitalRead(C2TBLED[0])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkRed_Comb3() {
   //Check for yellow light
  if(digitalRead(C3TBLED[0])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkRed_Comb4() {
   //Check for yellow light
  if(digitalRead(C4TBLED[0])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkRed_Comb5() {
   //Check for yellow light
  if(digitalRead(C5TBLED[0])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkRed_ED1() {
   //Check for yellow light
  if(digitalRead(ED1TBLED[0])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkRed_ED2() {
   //Check for yellow light
  if(digitalRead(ED2TBLED[0])) {
    //Indicate high value
    return true;
   }
   return false;
}

/* Function to check the yellow LED pins for all the combustion benches */
bool checkYellow_Comb1() {
  //Check for yellow light
  if(digitalRead(C1TBLED[1])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkYellow_Comb2() {
  //Check for yellow light
  if(digitalRead(C2TBLED[1])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkYellow_Comb3(){
  //Check for yellow light
  if(digitalRead(C3TBLED[1])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkYellow_Comb4() {
  //Check for yellow light
  if(digitalRead(C4TBLED[1])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkYellow_Comb5() {
  //Check for yellow light
  if(digitalRead(C5TBLED[1])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkYellow_ED1() {
  //Check for yellow light
  if(digitalRead(ED1TBLED[1])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkYellow_ED2() {
  //Check for yellow light
  if(digitalRead(ED2TBLED[1])) {
    //Indicate high value
    return true;
   }
   return false;
}

/* Function to check the Green LED pins for all the combustion Pins*/
bool checkGreen_Comb1() {
  //Check for yellow light
  if(digitalRead(C1TBLED[2])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkGreen_Comb2() {
  //Check for yellow light
  if(digitalRead(C2TBLED[2])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkGreen_Comb3() {
  //Check for yellow light
  if(digitalRead(C3TBLED[2])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkGreen_Comb4() {
  //Check for yellow light
  if(digitalRead(C4TBLED[2])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkGreen_Comb5() {
  //Check for yellow light
  if(digitalRead(C5TBLED[2])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkGreen_ED1() {
  //Check for yellow light
  if(digitalRead(ED1TBLED[2])) {
    //Indicate high value
    return true;
   }
   return false;
}
bool checkGreen_ED2() {
  //Check for yellow light
  if(digitalRead(ED2TBLED[2])) {
    //Indicate high value
    return true;
   }
   return false;
}