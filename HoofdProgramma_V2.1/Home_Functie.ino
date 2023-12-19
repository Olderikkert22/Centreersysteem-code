void setHoming_AC(){
  Run_Homing = true;
  //Deactiveerd de outputs om de moter te kunnen laten draaien
  DLA.disableOutputs();

  while(Run_Homing == true){
    //Dit leest de waarden van de microswitches uit
    int state_HSLA = digitalRead(HSLA);
    int state_HSRA = digitalRead(HSRA);
    int state_HSLC = digitalRead(HSLC);
    int state_HSRC = digitalRead(HSRC);

    digitalWrite(Home_LED_Blauw, HIGH);
    
    if (state_HSLA == HIGH){
      DLA.setSpeed(Speed_Homing);
      DLA.runSpeed();
    }
    if (state_HSRA == HIGH){
      DRA.setSpeed(Speed_Homing);
      DRA.runSpeed();
    }
    if (state_HSLC == HIGH){
      DLC.setSpeed(Speed_Homing);
      DLC.runSpeed();
    }
    if (state_HSRC == HIGH){
      DRC.setSpeed(Speed_Homing);
      DRC.runSpeed();
    }
    
    if ( state_HSLA + state_HSRA == 1 && Foutmelding_Home == false){
      VorigeTijd = millis();
      Foutmelding_Home = true;
    }
    //Als er 1 microswitch wordt bediend en het te lang duurt voor dat de tweede wordt bediend stopt het programma en zal het programma gereset moeten worden
    while (millis() - VorigeTijd > Tijd_Tussen_Knopjes_Home && Foutmelding_Home == true && state_HSLA + state_HSRA == 1){
      digitalWrite(Home_LED_Blauw, LOW);
      digitalWrite(Home_LED_Rood, HIGH);    
      DLA.enableOutputs();
      //Serial.println("A");
    }

    if ( state_HSLC + state_HSRC == 1 && Foutmelding_Home == false){
      VorigeTijd = millis();
      Foutmelding_Home = true;
    }
    //Als er 1 microswitch wordt bediend en het te lang duurt voor dat de tweede wordt bediend stopt het programma en zal het programma gereset moeten worden
    while (millis() - VorigeTijd > Tijd_Tussen_Knopjes_Home && Foutmelding_Home == true && state_HSLC + state_HSRC == 1){
      digitalWrite(Home_LED_Blauw, LOW);
      digitalWrite(Home_LED_Rood, HIGH);    
      DLA.enableOutputs();
      //Serial.println("C");
    }
    //Als alle microswitches zijn bediend stop het homen
    if (state_HSLA == LOW && state_HSRA == LOW && state_HSLC == LOW && state_HSRC == LOW){
      Run_Homing = false;
      Start_home_AC = false;
      Foutmelding_Home = false;
      // setCurrentPosition set de huidige posistie weer op nul om het nulpunt te bepalen
      DLA.setCurrentPosition(0);
      DRA.setCurrentPosition(0);
      DLC.setCurrentPosition(0);
      DRC.setCurrentPosition(0);
      
      digitalWrite(Home_LED_Blauw, LOW);
      digitalWrite(Home_LED_Groen, HIGH);
    }
  }
}

void setHoming_BD(){
  Run_Homing = true;
  //Deactiveerd de outputs om de moter te kunnen laten draaien
  DLA.disableOutputs();

  while(Run_Homing == true){
    //Dit leest de waarden van de microswitches uit
    int state_HSLB = digitalRead(HSLB);
    int state_HSRB = digitalRead(HSRB);
    int state_HSLD = digitalRead(HSLD);
    int state_HSRD = digitalRead(HSRD);

    digitalWrite(Home_LED_Blauw, HIGH);
    
    if (state_HSLB == HIGH){
      DLB.setSpeed(Speed_Homing);
      DLB.runSpeed();
    }
    if (state_HSRB == HIGH){
      DRB.setSpeed(Speed_Homing);
      DRB.runSpeed();
    }
    if (state_HSLD == HIGH){
      DLD.setSpeed(Speed_Homing);
      DLD.runSpeed();
    }
    if (state_HSRD == HIGH){
      DRD.setSpeed(Speed_Homing);
      DRD.runSpeed();
    }

    if ( state_HSLB + state_HSRB == 1 && Foutmelding_Home == false){
      VorigeTijd = millis();
      Foutmelding_Home = true;
    }
    //Als er 1 microswitch wordt bediend en het te lang duurt voor dat de tweede wordt bediend stopt het programma en zal het programma gereset moeten worden
    while (millis() - VorigeTijd > Tijd_Tussen_Knopjes_Home && Foutmelding_Home == true && state_HSLB + state_HSRB == 1){
      digitalWrite(Home_LED_Blauw, LOW);
      digitalWrite(Home_LED_Rood, HIGH);    
      DLA.enableOutputs();
      //Serial.println("B");
    }

    if ( state_HSLD + state_HSRD == 1 && Foutmelding_Home == false){
      VorigeTijd = millis();
      Foutmelding_Home = true;
    }
    //Als er 1 microswitch wordt bediend en het te lang duurt voor dat de tweede wordt bediend stopt het programma en zal het programma gereset moeten worden
    while (millis() - VorigeTijd > Tijd_Tussen_Knopjes_Home && Foutmelding_Home == true && state_HSLD + state_HSRD == 1){
      digitalWrite(Home_LED_Blauw, LOW);
      digitalWrite(Home_LED_Rood, HIGH);    
      DLA.enableOutputs();
      //Serial.println("D");
    }
    //Als alle microswitches zijn bediend stop het homen
    if (state_HSLB == LOW && state_HSRB == LOW && state_HSLD == LOW && state_HSRD == LOW){
      Run_Homing = false;
      Start_home_BD = false;
      Foutmelding_Home = false;
      // setCurrentPosition set de huidige posistie weer op nul om het nulpunt te bepalen
      DLB.setCurrentPosition(0);
      DRB.setCurrentPosition(0);
      DLD.setCurrentPosition(0);
      DRD.setCurrentPosition(0);

      digitalWrite(Home_LED_Blauw, LOW);
      digitalWrite(Home_LED_Groen, HIGH);
    }
  }
}