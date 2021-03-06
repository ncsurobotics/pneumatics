//Seawolf Pneumatics

#define DEBUG //uncomment this line while testing w/ Arduino serial monitor


////////////////////////////////////////////////////////////
// you should wire it so that p6 relates to firing 6 etc etc 
//6 = white
//5 = green
//4 = yeller
//3 = blue
// 2 = black
// 1 = orange


///////////////////////////////////////////////////////////

//byte code definitions, bytes corresponding numbered Pneumatics item, P1-P6
const byte OPEN_GRABBER   =1 ;
const byte CLOSE_GRABBER  =2 ;
const byte TORPEDO_2      =3 ;
const byte TORPEDO_1      =4 ;
const byte DROPPER_2      =5 ;
const byte DROPPER_1      =6 ;
const byte RESET          ='r';
// if there is a problem with comparing it may be because of how the above variables are initialized.
// consider making a counter to not let the things fire more than once 
const byte EXTRA          = 7; //reserved for future use for something else

//callback function declarations
void openGrabber();
void closeGrabber();
void dropper1();
void dropper2();
void torpedo1();
void torpedo2();

//pins
const int grabberPin1=8;
const int grabberPin2=9;
const int torpedoPin2=10;
const int torpedoPin1=11;
const int dropperPin2=12;
const int dropperPin1=7;
const int LED=13;



void firePin(int pin, unsigned long ms)
{
  digitalWrite(pin, HIGH);
  delay(ms);
  digitalWrite(pin, LOW); 
}

int handshakeSerial(){
    Serial.println("Waiting for handshake");
    //Show handshake LED
    digitalWrite(LED, HIGH);
    
    int incomingByte;
    int i = 0;
    char incomingString[64];

    /* Wait for handshake signal */
    while(1){
      //blocking
      while(Serial.available()==0){}
      
      //Treat 0xFE as a signal for Identity
      incomingByte = Serial.read();
      if(incomingByte == 0xFE) {
          Serial.println("{ID|Pneumatics}");
          delay(250);
          break;
      }
    }
    Serial.println("Handshake ");

    //turn off handshake LED
    digitalWrite(LED, LOW);
    
    return 1;
}

void setup() 
{
  Serial.begin(9600);
  
  pinMode(dropperPin1,OUTPUT);
  pinMode(dropperPin2,OUTPUT);
  pinMode(torpedoPin1,OUTPUT);
  pinMode(torpedoPin2,OUTPUT);
  pinMode(grabberPin1,OUTPUT);
  pinMode(grabberPin2,OUTPUT);
  pinMode(LED,        OUTPUT);
  
  //#ifndef DEBUG
    handshakeSerial();
  //#endif
}

void loop() 
{
  if(Serial.available()>0)
  {
    byte code;

    //only use this method when manually debugging with arduino serial monitor
    #ifdef DEBUG
      code=Serial.parseInt();
    #else
      code=Serial.read();
    #endif

    switch(code)
    {
      case OPEN_GRABBER:
        openGrabber();
        break;
      case CLOSE_GRABBER:
        closeGrabber();
        break;
      case DROPPER_1:
        dropper1();
        break;
      case DROPPER_2:
        dropper2();
        break;
      case TORPEDO_1:
        torpedo1();
        break;
      case TORPEDO_2:
        torpedo2();
        break;
      case RESET:
        setup();
      default:
        Serial.print("Unknown Code: ");
        Serial.println(code);
    }
  }
}

//function definitions

void openGrabber()
{
  #ifdef DEBUG
  Serial.println("Open Grabber");
  #endif
  
  //firePin(grabberPin1, 1000);
  digitalWrite(grabberPin1, HIGH);
}

void closeGrabber()
{
  #ifdef DEBUG
  Serial.println("Close Grabber");
  #endif
  
  //firePin(grabberPin2, 1000);
  digitalWrite(grabberPin1, LOW);
  delay(100);
  digitalWrite(grabberPin2, HIGH);
  delay(1000);
  digitalWrite(grabberPin2, LOW);
}

void dropper1()
{
  #ifdef DEBUG
  Serial.println("Dropper 1");
  #endif
  firePin(dropperPin1, 1000);
}

void dropper2()
{
  #ifdef DEBUG
  Serial.println("Dropper 2");
  #endif
  firePin(dropperPin2, 1000);
}

void torpedo1()
{
  #ifdef DEBUG
  Serial.println("Torpedo 1");
  #endif
  firePin(torpedoPin1, 1000);
}

void torpedo2()
{
  #ifdef DEBUG
  Serial.println("Torpedo 2");
  #endif
  firePin(torpedoPin2, 1000);
}
