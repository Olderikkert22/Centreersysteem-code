bool helemaal_rechts = false;
void setCentreren_AC(){
  Run_Center = true;
  //DLA.disableOutputs activeer de anable pin waar door alle motor kunnen gaan draaien
  DLA.disableOutputs(); 

  digitalWrite(Home_LED_Groen, LOW);
  digitalWrite(Centreren_LED_Groen, LOW);

  while(Run_Center == true){
    //Dit leest de waarden van de microswitches uit
    int state_BSLA = digitalRead(BSLA);
    int state_BSRA = digitalRead(BSRA);
    int state_BSLC = digitalRead(BSLC);
    int state_BSRC = digitalRead(BSRC);

    digitalWrite(Centreren_LED_Blauw, HIGH);

    //Deze functie set de aantal pulsen die worden uitgevoerd
    //51200 staat gelijk aan 256mm verplaatsing als de huidige spindel nog wordt gebruikt met de juiste in stelling van de driver
    DLA.setSpeed(Speed_Center);
    DLA.runSpeed();
    DRA.setSpeed(Speed_Center);
    DRA.runSpeed();

    DLC.setSpeed(Speed_Center);
    DLC.runSpeed();
    DRC.setSpeed(Speed_Center);
    DRC.runSpeed();

    //Foutmelding_Centreren_AC();

    if ( state_BSLA + state_BSRA + state_BSLC + state_BSRC == 1 && Foutmelding_Center == false){
      VorigeTijd = millis();
      Foutmelding_Center = true;
    }
    /*if ( state_BSLA + state_BSRA + state_BSLC + state_BSRC == 1 && Foutmelding_Center == false){
      VorigeTijd = millis();
      Foutmelding_Center = true;
    }*/
    //Als er 3 microswitches worden bediend en het te lang duurt voor dat de vierde wordt bediend stopt het programma en zal het programma gereset moeten worden
    while (millis() - VorigeTijd > Tijd_Tussen_Knopjes && Foutmelding_Center == true && helemaal_rechts == false){
      digitalWrite(Centreren_LED_Blauw, LOW);
      digitalWrite(Centreren_LED_Rood, HIGH);    
      DLA.enableOutputs();
    }
    //Als alle microswitches bediend zijn stopt het centreren of als de afstand die afgelegt mocht worden behaald is
    if (state_BSLA == LOW && state_BSRA == LOW && state_BSLC == LOW && state_BSRC == LOW || DLA.currentPosition() == -52000 || DLC.currentPosition() == -52000){
      digitalWrite(Centreren_LED_Blauw, LOW);
      Run_Center = false;
      Start_AC = false;
      Foutmelding_Center = false;
      delay(500);
    }

    if (state_BSLA == LOW && state_BSRC == LOW && state_BSRA == HIGH && state_BSLC == HIGH && Foutmelding_Center == false){
      VorigeTijd = millis();
      Foutmelding_Center = true;
      helemaal_rechts = true;
    }
    if (state_BSLA == HIGH && state_BSRC == HIGH && state_BSRA == LOW && state_BSLC == LOW && Foutmelding_Center == false){
      VorigeTijd = millis();
      Foutmelding_Center = true;
      helemaal_rechts = true;
    }

    if (millis() - VorigeTijd > Tijd_Tussen_Knopjes_Bijzonder && Foutmelding_Center == true && helemaal_rechts == true){
      digitalWrite(Centreren_LED_Blauw, LOW);
      Run_Center = false;
      Start_AC = false;
      Foutmelding_Center = false;
      helemaal_rechts = false;
      digitalWrite(Centreren_LED_Groen, HIGH);
      delay(500);

    }
  }
}

void setCentreren_BD(){
  Run_Center = true;
  DLA.disableOutputs(); 
  digitalWrite(Home_LED_Groen, LOW);
  Foutmelding_Center = false;
  while(Run_Center == true){
    //Dit leest de waarden van de microswitches uit
    int state_BSLB = digitalRead(BSLB);
    int state_BSRB = digitalRead(BSRB);
    int state_BSLD = digitalRead(BSLD);
    int state_BSRD = digitalRead(BSRD);

    digitalWrite(Centreren_LED_Blauw, HIGH);
    
    //Deze functie set de aantal pulsen die worden uitgevoerd
    //51200 staat gelijk aan 256mm verplaatsing als de huidige spindel nog wordt gebruikt met de juiste in stelling van de driver
    DLB.setSpeed(Speed_Center);
    DLB.runSpeed();
    DRB.setSpeed(Speed_Center);
    DRB.runSpeed();

    DLD.setSpeed(Speed_Center);
    DLD.runSpeed();
    DRD.setSpeed(Speed_Center);
    DRD.runSpeed();
    
    if ( state_BSLB + state_BSRB + state_BSLD + state_BSRD == 1 && Foutmelding_Center == false){
      VorigeTijd = millis();
      Foutmelding_Center = true;
    }
    //Als er 3 microswitches worden bediend en het te lang duurt voor dat de vierde wordt bediend stopt het programma en zal het programma gereset moeten worden
    
    while (millis() - VorigeTijd > Tijd_Tussen_Knopjes && Foutmelding_Center == true){
      digitalWrite(Centreren_LED_Blauw, LOW);
      digitalWrite(Centreren_LED_Rood, HIGH);    
      DLA.enableOutputs();
      Serial.println("test");
    }
    //Als alle microswitches bediend zijn stopt het centreren of als de afstand die afgelegt mocht worden behaald is
    if (state_BSLB == LOW && state_BSRB == LOW && state_BSLD == LOW && state_BSRD == LOW || DLB.currentPosition() == -52000 || DLD.currentPosition() == -52000){
      digitalWrite(Centreren_LED_Blauw, LOW);
      digitalWrite(Centreren_LED_Groen, HIGH);
      delay(500);
      Start_BD = false;
      Run_Center = false;
      Foutmelding_Center = false;
    }
  }
}