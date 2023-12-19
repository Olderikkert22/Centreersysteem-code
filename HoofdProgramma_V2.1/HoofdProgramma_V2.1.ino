#include <AccelStepper.h>

//Startknop gedefineerd
#define Start 56

//Home switches gedefineerd
#define HSLA 33 
#define HSRA 31

#define HSLB 25 
#define HSRB 23

#define HSLC 26 
#define HSRC 28

#define HSLD 34
#define HSRD 36

//Bumper switches gedefineerd
#define BSLA 37
#define BSRA 35

#define BSLB 29
#define BSRB 27

#define BSLC 22
#define BSRC 24

#define BSLD 30
#define BSRD 32

//Direction en step gedefineerd voor de Drivers links en recht van zijde A
#define DirAL 41 
#define StepAL 39
#define DirAR 45
#define StepAR 43

//Direction en step gedefineerd voor de Drivers links en recht van zijde B
#define DirBL 49  
#define StepBL 47
#define DirBR 53
#define StepBR 51

//Direction en step gedefineerd voor de Drivers links en recht van zijde C
#define DirCL 52  
#define StepCL 50
#define DirCR 48
#define StepCR 46

//Direction en step gedefineerd voor de Drivers links en recht van zijde D
#define DirDL 44   
#define StepDL 42
#define DirDR 40
#define StepDR 38

//Dit geeft aan dat het om een driver gaat
#define motorInterfaceType 1

//Enablepin gedefineerd
#define enablePin 57

//LEDjes defineren
#define Home_LED_Groen 13
#define Home_LED_Blauw 12
#define Home_LED_Rood 11

#define Centreren_LED_Groen 10
#define Centreren_LED_Blauw 9
#define Centreren_LED_Rood 8

//Deze LEDjes kunnen nog gebruiken worden voor een bepaalde functie
#define Anders_LED_Groen 7
#define Anders_LED_Blauw 6
#define Anders_LED_Rood 5

//Snelheid voor het homen en het centreren
int Speed_Homing = 2500;
//snelheid van het centreren is nog niet in te stellen
int Speed_Center = -2500;

//Het defineren van en driver met step en direction
//De driver zullen moet worden ingesteld op 1600 pulsen per rotatie voor dit programma
AccelStepper DLA(motorInterfaceType, StepAL, DirAL);
AccelStepper DRA(motorInterfaceType, StepAR, DirAR);

AccelStepper DLB(motorInterfaceType, StepBL, DirBL);
AccelStepper DRB(motorInterfaceType, StepBR, DirBR);

AccelStepper DLC(motorInterfaceType, StepCL, DirCL);
AccelStepper DRC(motorInterfaceType, StepCR, DirCR);

AccelStepper DLD(motorInterfaceType, StepDL, DirDL);
AccelStepper DRD(motorInterfaceType, StepDR, DirDR);

//Alle boolen waarden gedefineerd
//Een bool waar kan true of false zijn of te wel hoog of laag
bool Run_Homing = false;
bool Run_Center = false;
bool Start_AC = false;
bool Start_BD = false;
bool Start_home_AC = false;
bool Start_home_BD = false;
bool Foutmelding_Center = false;
bool Foutmelding_Home = false;
bool Controle_switches = false;

//Alle unsigned long waarden gedefineerd
//Unsigned long is een type waarde net zoals int maar unsigned long kan een heel groot getal zijn
unsigned long VorigeTijd = 0;
unsigned long HuidigeTijd = 0;
unsigned long Tijd_Tussen_Knopjes = 500;
unsigned long Tijd_Tussen_Knopjes_Bijzonder = 500;
unsigned long Tijd_Tussen_Knopjes_Home = 500;

int Testduur = 0;
bool testbool = false;

void setup() {
  Serial.begin(9600); 
  
  //Maximale speed en versnelling ingesteld voor de drivers links en rechts van zijde A
  DLA.setMaxSpeed(3000);
  DLA.setAcceleration(1000);
  DLA.setSpeed(2000);
  DRA.setMaxSpeed(3000);
  DRA.setAcceleration(1000);
  DRA.setSpeed(2000);

  //Maximale speed en versnelling ingesteld voor de drivers links en rechts van zijde B
  DLB.setMaxSpeed(3000);
  DLB.setAcceleration(1000);
  DRB.setMaxSpeed(3000);
  DRB.setAcceleration(1000);

  //Maximale speed en versnelling ingesteld voor de drivers links en rechts van zijde C 
  
  DLC.setMaxSpeed(3000);
  DLC.setAcceleration(1000);
  DRC.setMaxSpeed(3000);
  DRC.setAcceleration(1000);

  //Maximale speed en versnelling ingesteld voor de drivers links en rechts van zijde D
  DLD.setMaxSpeed(3000);
  DLD.setAcceleration(1000);
  DRD.setMaxSpeed(3000);
  DRD.setAcceleration(1000);

  //Start knop als input gedefineerd
  pinMode(Start, INPUT);
  
  //Home Microswitches als input gedefineerd
  pinMode(HSLA, INPUT);
  pinMode(HSRA, INPUT);

  pinMode(HSLB, INPUT);
  pinMode(HSRB, INPUT);

  pinMode(HSLC, INPUT);
  pinMode(HSRC, INPUT);

  pinMode(HSLD, INPUT);
  pinMode(HSRD, INPUT);

  //Bumper Microswitches als input gedefineerd
  pinMode(BSLA, INPUT);
  pinMode(BSRA, INPUT);

  pinMode(BSLB, INPUT);
  pinMode(BSRB, INPUT);

  pinMode(BSLC, INPUT);
  pinMode(BSRC, INPUT);

  pinMode(BSLD, INPUT);
  pinMode(BSRD, INPUT);

  //Enable gedefineerd
  DLA.setEnablePin(enablePin);
  pinMode(enablePin, OUTPUT);
  
  //LEDjes gedefineerd
  pinMode(Home_LED_Groen, OUTPUT);
  pinMode(Home_LED_Blauw, OUTPUT);
  pinMode(Home_LED_Rood, OUTPUT);
  
  pinMode(Centreren_LED_Groen, OUTPUT);
  pinMode(Centreren_LED_Blauw, OUTPUT);
  pinMode(Centreren_LED_Rood, OUTPUT);
  
  pinMode(Anders_LED_Groen, OUTPUT);
  pinMode(Anders_LED_Blauw, OUTPUT);
  pinMode(Anders_LED_Rood, OUTPUT);

}




void loop() {
  int start1 = digitalRead(Start);
  //DLA.enableOutpurs() activeer de anable pin waar door alle motor vrij komen te staan en niet kunnen gaan draaien
  //Inplaatsvan voor iedere driver een aparte enableoutputs en input heb ik er voor gekozen om dit allemaal te gelijkertijd te schakelen
  DLA.enableOutputs();
  
  
  if(start1 == HIGH /*|| testbool == true*/ ){
    //Controller of de microswitches het kunnen doen
    testbool = true;
    setSwitche_Controle();
    if(Controle_switches == true){
      //setHoming_AC start het homen van de bumpers zijde A en C
      setHoming_AC();
      //setHoming_BD start het homen van de bumpers zijde B en D
      setHoming_BD();
      // Door Start_AC true te zetten start het centreren van de AC zijde
      Start_AC = true;
    }
    
  }

  if(Start_AC == true){
    //setCentreren_AC is de functie die de zijden A en C laat centreren
    setCentreren_AC();
    Start_home_AC = true;
  }
  
  if (Start_home_AC == true){
    //setHoming_AC start het homen van de bumpers zijde A en C
    setHoming_AC();
    Start_BD = true;
  }
  
  if(Start_BD == true){
    //setCentreren_BD is de functie die de zijden B en D laat centreren
    setCentreren_BD();
    Start_home_BD = true;
  }

  if(Start_home_BD == true){
    //setHoming_BD start het homen van de bumpers zijde B en D
    setHoming_BD();
    //setEinde_AC start het laatste gedeeld van de eind positie van het systeem
    setEinde_AC();
    //setEinde_BD start het laatste gedeeld van de eind positie van het systeem
    setEinde_BD();
    Testduur = Testduur + 1;
    Serial.println(Testduur);

  }
}


