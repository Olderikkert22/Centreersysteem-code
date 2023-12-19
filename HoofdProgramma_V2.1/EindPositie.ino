//Deze functie zorgt dat op het eind van het programma de bumpers 4 mm weer naar voren draaid
//Dit geeft in combinatie met de home functie een controle om de motoren te testen
//Als de volgende keer er opnieuwe het programma wordt gestart zal er eerst gehomed moeten worden
void setEinde_AC(){
  Run_Center = true;
  DLA.disableOutputs(); 

  while(Run_Center == true){
    //Deze functie set de aantal pulsen die worden uitgevoerd
    //800 staat gelijk aan 256mm verplaatsing als de huidige spindel nog wordt gebruikt met de juiste in stelling van de driver
    DLA.moveTo(-800);
    DLA.run();
    DRA.moveTo(-800);
    DRA.run();

    DLC.moveTo(-800);
    DLC.run();
    DRC.moveTo(-800);
    DRC.run();
    //Als de afgelegde weg is behaald stopt deze functie
    if (DLA.distanceToGo() == 0 || DLC.distanceToGo() == 0){
      Run_Center = false;
    }
  }
}

void setEinde_BD(){
  Run_Center = true;
  DLA.disableOutputs(); 
  
  while(Run_Center == true){
    //Deze functie set de aantal pulsen die worden uitgevoerd
    //800 staat gelijk aan 256mm verplaatsing als de huidige spindel nog wordt gebruikt met de juiste in stelling van de driver
    DLB.moveTo(-800);
    DLB.run();
    DRB.moveTo(-800);
    DRB.run();

    DLD.moveTo(-800);
    DLD.run();
    DRD.moveTo(-800);
    DRD.run();
    //Als de afgelegde weg is behaald stopt deze functie
    if (DLB.distanceToGo() == 0 || DLD.distanceToGo() == 0){
      Run_Center = false;
      digitalWrite(Anders_LED_Groen, LOW);
    }
  }
}