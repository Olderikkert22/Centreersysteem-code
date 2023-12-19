//Een functie om eventuele kabelbreuk te detecteren van de switches
void setSwitche_Controle(){
  int state_BSLA = digitalRead(BSLA);
  int state_BSRA = digitalRead(BSRA);
  int state_BSLC = digitalRead(BSLC);
  int state_BSRC = digitalRead(BSRC);

  int state_BSLB = digitalRead(BSLB);
  int state_BSRB = digitalRead(BSRB);
  int state_BSLD = digitalRead(BSLD);
  int state_BSRD = digitalRead(BSRD);

  int state_HSLA = digitalRead(HSLA);
  int state_HSRA = digitalRead(HSRA);
  int state_HSLC = digitalRead(HSLC);
  int state_HSRC = digitalRead(HSRC);

  int state_HSLB = digitalRead(HSLB);
  int state_HSRB = digitalRead(HSRB);
  int state_HSLD = digitalRead(HSLD);
  int state_HSRD = digitalRead(HSRD);

  if (state_BSLA == LOW ||  state_BSRA == LOW ||  state_BSLC == LOW ||  state_BSRC == LOW ||  state_BSLB == LOW ||  state_BSRB == LOW ||  state_BSLD == LOW ||  state_BSRD == LOW ||  state_HSLA == LOW ||  state_HSRA == LOW ||  state_HSLC == LOW ||  state_HSRC == LOW ||  state_HSLB == LOW ||  state_HSRB == LOW ||  state_HSLD == LOW ||  state_HSRD == LOW ){
    digitalWrite(Anders_LED_Groen, LOW);
    digitalWrite(Anders_LED_Rood, HIGH);
    Serial.println("Een van de switches doet het niet");
    Controle_switches = false;
  }

  else{\
    digitalWrite(Anders_LED_Rood, LOW);
    digitalWrite(Anders_LED_Groen, HIGH);
    Controle_switches = true;
  }

}
