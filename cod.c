char valoare_uss[7];
char valoare_usj[7];
char valoare_uds[7];
char valoare_udj[7];
char lock_status[10]="LOCKED"; //LOCKED/UNLOCKED
char light_status[10]="OFF"; //AUTO
char ignition_status[10]; //ON/OFF/ACC
char valoare_PIR[11]; //ACTIV/DEZACTIVAT
char valoare_alarma[15]; //ACTIVA/DEZACTIVATA

void setup()
{
  pinMode(A5,INPUT); //fotorezistenta faruri
  pinMode(A4,INPUT); //potentiometru
  Serial.begin(9600);
  pinMode(9, OUTPUT); //far stanga
  pinMode(10, OUTPUT); //far dreapta
  pinMode(11,OUTPUT); //led status
  
  //fotorezistente usi
  pinMode(A0,INPUT);//usa stanga sus
  pinMode(A1,INPUT);//usa stanga jos
  pinMode(A2,INPUT);//usa dreapta sus
  pinMode(A3,INPUT);//usa dreapta jos
  
  pinMode(2, INPUT);//senzor PIR
  
  pinMode(8, OUTPUT);//buzzer
}

void loop()
{
  int light = analogRead(A5); //fotorezistor lumina
  int potVal  = analogRead(A4); //potentiometru
  
  int light_uss = analogRead(A0);
  int light_usj = analogRead(A1);
  int light_uds = analogRead(A2);
  int light_udj = analogRead(A3);
  
  int senzor_PIR = digitalRead(2);
  
  			     	//G,I,J,K,L,R
  
  if(Serial.available() == 0){
   Serial.println("No data was written to the serial monitor"); 
  }
  else if (Serial.available() > 0){
    char val = Serial.read();
    switch (val){
      case 'L':
      if( (strcmp(ignition_status,"OFF")==0) && //r
         (strcmp(valoare_uss,"CLOSED") == 0) &&
         (strcmp(valoare_uds,"CLOSED") == 0)){
        strcpy(lock_status,"LOCKED");
      }
      else{
       Serial.println("Nu au fost indeplinite toate cerintele pentru ca masina sa isi dea lock"); 
       strcpy(lock_status,"UNLOCKED");
      }
      break;
      
      case 'U':
      strcpy(lock_status,"UNLOCKED");
      break;
      
      case 'A':
      strcpy(light_status,"AUTO");
      break;
      
      case 'O':
      strcpy(light_status,"OFF");
      break;
      
      case 'P':
      strcpy(light_status,"ONN");
      break;
      
      default:
      Serial.println("Introduceti unul dintre caracterele L,U,A,O,P");
    }
  }
  
  Serial.println("Lock status: " + String(lock_status));
  Serial.println("Light Status: " +String(light_status));
  
  
  						//H,M
 bool x;
 int a;
 if (strcmp(lock_status, "LOCKED") == 0) {
    digitalWrite(11, HIGH); // Aprindem ledul rosu
   if(x == false){
     a=millis();
     x=true;
   }
   if(millis() -a >= 1000){
    //delay(1000);
    digitalWrite(11, LOW);
    //delay(1000);
     x=false;
   }
    if ((senzor_PIR == HIGH) && strcmp(valoare_uss, "CLOSED") == 0 && //R
          strcmp(valoare_usj, "CLOSED") == 0 && 
          strcmp(valoare_uds, "CLOSED") == 0 && 
          strcmp(valoare_udj, "CLOSED") == 0) {
        strcpy(valoare_PIR, "ACTIV"); // Se activeaza senzorul PIR
    }else {
        strcpy(valoare_PIR, "DEZACTIVAT");
    }
 }else {
    strcpy(valoare_PIR, "DEZACTIVAT");
 }
  
  if(strcmp(lock_status,"UNLOCKED") == 0){
   digitalWrite(11,LOW); 
  }

  Serial.print("Lumina: ");  
  Serial.println(light); // print current  light value
  Serial.print("Masina: ");
  Serial.println(potVal);
  //valorea aleasa in stadiul de testare este 200
  //cand lumina > 200 =>farurile se aprind
  
  							//E,F
  
 	//folosim functia x = map(x, pMin, pMax, 0, 100) 
	//take the value of x, compared it to the scale of the 
  	//potentiometer pMin to pMax,
	//and translate that value to the scale of 0 to 100

  
  //Am vazut ca maximul potentiometrului este 1023
  int percentage = map(potVal,0,1023,0,100);
  if ((percentage >= 0) && (percentage <= 30)){
    // Mașina este oprită
    strcpy(ignition_status,"OFF");
    
  } else if ((percentage >= 31) && (percentage <= 60)){
    
    // Mașina este în modul accesoriu
    strcpy(ignition_status,"ACC");
    
  } else {
    
    // Mașina este pornită
    strcpy(ignition_status,"ON");
    
  }
  Serial.println("Ignition Status: " + String(ignition_status));
  
   if ((strcmp(ignition_status, "ACC") == 0) || (strcmp(ignition_status, "ON") == 0) || (strcmp(ignition_status, "OFF") == 0)) {
    if (strcmp(light_status, "OFF") == 0) {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    }
   }
  
  if ((strcmp(ignition_status, "ACC") == 0) || (strcmp(ignition_status, "ON") == 0)) {
    if ((strcmp(light_status, "AUTO") == 0) || (strcmp(light_status, "ONN") == 0)){
       digitalWrite(9, HIGH);
       digitalWrite(10, HIGH);  
    }
}
  
 						//A,B,C

 if ((strcmp(ignition_status, "ACC") == 0) || (strcmp(ignition_status, "ON") == 0)) {
    if ((strcmp(light_status, "AUTO") == 0)){
        if (light > 200) { // testare (c)
            digitalWrite(9, HIGH);
            digitalWrite(10, HIGH);
        } else {
            digitalWrite(9, LOW);
            digitalWrite(10, LOW);
        }
    }
} else {
    if ((strcmp(ignition_status, "OFF") == 0) && (strcmp(light_status, "AUTO") == 0)) {
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        Serial.println("Light status : AUTO");
        strcpy(light_status, "AUTO");
    } else {
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
    }
}

  
  							//D
  
  //maximul pentru toate fotorezistentelor usilor este de 974
  //valoarea aleasa in stadiul de testare este 900
  //cand valoare >=900, usa deschisa
  //cand valoare < 900, usa inchisa
  //_______________________________________________
  if(light_uss >= 900){
    strcpy(valoare_uss,"OPEN");
  }
  else if(light_uss <900){
    strcpy(valoare_uss,"CLOSED");
  }
  Serial.println("Door status usa stanga sus: " + String(valoare_uss));
  //____________________________________________________
  
  if(light_usj >= 900){
    strcpy(valoare_usj,"OPEN");
  }
  else if(light_usj < 900){
    strcpy(valoare_usj,"CLOSED");
  }
  Serial.println("Door status usa stanga jos: " + String(valoare_usj));
  //____________________________________________________
  
  if(light_uds >= 900){
    strcpy(valoare_uds,"OPEN");
  }
  else if(light_uds < 900){
    strcpy(valoare_uds,"CLOSED");
  }
  Serial.println("Door status usa dreapta sus: " + String(valoare_uds));
  //_________________________________________________________
  
  if(light_udj >= 900){
    strcpy(valoare_udj,"OPEN");
  }
  else if(light_udj < 900){
    strcpy(valoare_udj,"CLOSED");
  }
  
  if((strcmp(lock_status,"LOCKED")) == 0){
   	 if((strcmp(valoare_uss,"OPEN") == 0) ||
         (strcmp(valoare_usj,"OPEN") == 0) || 
         (strcmp(valoare_uds,"OPEN") == 0) ||
         (strcmp(valoare_udj,"OPEN") == 0)){
       
       strcpy(lock_status,"UNLOCKED");
     }
    
  }
  Serial.println("Door status usa dreapta jos: " + String(valoare_udj));
  
  //____________________________________________________

  
  						//N
 
  if(strcmp(valoare_PIR,"ACTIV") == 0){ //inseamna ca avem miscare in masina 
    int timp_initial = millis();
    int timp_scurs = 0;
    int frequency = 100;
    while(timp_scurs < 10000){
    		tone(8, frequency, 500);
      		strcpy(valoare_alarma,"ACTIVATA");
            digitalWrite(9,HIGH); 
    		digitalWrite(10,HIGH);
    		delay(1000);
    		digitalWrite(9,LOW); 
    		digitalWrite(10,LOW);
    		delay(1000);
      		timp_scurs = millis() - timp_initial;
      		frequency = frequency + 100;
  	
    }
  }

  					   //P
  
  if((strcmp(lock_status,"LOCKED")) == 0){
   	 if((strcmp(valoare_uss,"OPEN") == 0) ||
         (strcmp(valoare_usj,"OPEN") == 0) || 
         (strcmp(valoare_uds,"OPEN") == 0) ||
         (strcmp(valoare_udj,"OPEN") == 0)){
       
       strcpy(lock_status,"UNLOCKED");
       strcpy(valoare_PIR,"DEZACTIVAT");
       strcpy(valoare_alarma,"DEZACTIVATA");
     }
    
  }
  
  //Serial.println("PIR sensor status:" + String(valoare_PIR));
  
  
  						//Q
  
  if(strcmp(ignition_status, "OFF") == 0 && strcmp(light_status, "ONN") == 0){
    if(strcmp(valoare_uss, "OPEN") == 0 || 
          strcmp(valoare_usj, "OPEN") == 0 || 
          strcmp(valoare_uds, "OPEN") == 0 || 
          strcmp(valoare_udj, "OPEN") == 0){
        tone(8, 500); 
        delay(100); 
        strcpy(valoare_alarma,"ACTIVATA");
    }else{
    	noTone(8); // Oprirea sunetului când toate ușile sunt închise
      	strcpy(valoare_alarma,"DEZACTIVATA");
    }
  }
  
  //Serial.println("Alarm status:" + String(valoare_alarma));

  
  Serial.println("_____________________________________________");
  delay(1000); //O
}


