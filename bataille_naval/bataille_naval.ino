
#define double_buffer
#include <PxMatrix.h>

#ifdef ESP32

#define P_LAT 22
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_OE 16
#define P_CLK 14
#define P_R1 13
#define nuke 25

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

#endif

PxMATRIX display(32,32,P_LAT, P_OE,P_A,P_B,P_C,P_D, P_R1);
//PxMATRIX display(64,64,P_LAT, P_OE,P_A,P_B,P_C,P_D,P_E);

#ifdef ESP32
void IRAM_ATTR display_updater(){
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);
  display.display(70);
  portEXIT_CRITICAL_ISR(&timerMux);
}
#endif


uint16_t textColor = display.color565(0, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myCYAN = display.color565(4, 196, 255);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myPURPLE = display.color565(199, 4, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myORANGE = display.color565(255, 163, 4);
uint16_t lineColor = display.color565(255, 0, 0);
uint16_t backgroundColor = display.color565(0, 255, 0);

const int bouton = 26;
const int joystick_X = 33;
const int joystick_Y = 32;

int valeurbouton = 0;
int valeurX = 0;
int valeurY =0;
int valeurnuke = 0;
int valeurnuke2 = 0;

int pointX = 11;
int pointY = 11;

bool valider = false;

int hit[10][10];

int bateaux[5] = { 2, 3, 3, 4, 5 };


int bat[5][4] = {{ 33,33, 33,33},{ 50,50, 50,50},{ 60,60, 60,60},{ 70,70, 70,70},{ 80,80, 80,80}};
int m = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  display.begin(16);
  display.flushDisplay();

  pinMode(25, INPUT);

  #ifdef ESP32
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &display_updater, true);
    timerAlarmWrite(timer, 4000, true);
    timerAlarmEnable(timer);
  #endif

  int i = 0;
  
  Serial.print("joystick X  joystick Y  bouton");
  pinMode(bouton,INPUT_PULLUP);
  valeurX = analogRead(joystick_X); 
  valeurY = analogRead(joystick_Y);
}






void loop() {
  valeurX = analogRead(joystick_X);
  valeurY = analogRead(joystick_Y);
  valeurbouton = digitalRead(bouton);
  /*Serial.println("valeur x");
  Serial.println(valeurX);
  Serial.println("valeur y");
  Serial.println(valeurY);
  Serial.println("valeur bouton");
  Serial.println(valeurbouton);
  delay(1000);*/
//display.clearDisplay();
display.showBuffer();

ecran(); // Affichage de l'ecran
 
  for (int i = 0; i<5; i++){   //Boucle pour placement des bateaux 
    pointX =11;
    pointY =11;
    delay(500);
    //Serial.println("valeurdei");
    //Serial.println(i);
    valider = false;
    while (valider == false){
  valeurX = analogRead(joystick_X);
  valeurY = analogRead(joystick_Y);
  valeurbouton = digitalRead(bouton);
  /*Serial.println("valeur x");
  Serial.println(valeurX);
  Serial.println("valeur y");
  Serial.println(valeurY);*/
  //Serial.println(valeurbouton);
  //Serial.println("valeur bouton");
      display.showBuffer();

      if (valeurnuke == 0){
          if (valeurX>2500 && pointX+bateaux[i]<21){
                //Serial.println("coucoux");
              pointX+=1;
              delay(200);
      }   else if (valeurX<1000 && pointX>11){
              pointX-=1;
              delay(200);
      }
          if (valeurY>2500 && pointY<20){
              //erial.println("coucouy");
              pointY+=1;
              delay(200);
      }   else if (valeurY<1000 && pointY>11){
              pointY-=1;
              delay(200);
      }
      }   else {
            if (valeurX>2500 && pointX<20){
              //Serial.println("coucoux");
              pointX+=1;
              delay(200);
      }    else if (valeurX<1000 && pointX>11){
              pointX-=1;
              delay(200);
      }
           if (valeurY>2500 && pointY+bateaux[i]<21){
              //erial.println("coucouy");
              pointY+=1;
              delay(200);
      }    else if (valeurY<1000 && pointY>11){
              pointY-=1;
              delay(200);
      }
        }
      
          while (valeurX>1000 && valeurX<2500 && valeurY>1000 && valeurY<2500 && valeurbouton == 1 && valeurnuke == valeurnuke2 ){
             /*display.drawLine(pointX, pointY, pointX+bateaux[i]-1, pointY, myGREEN);*/
             display.clearDisplay();
             ecran();
             valeurX = analogRead(joystick_X);
             valeurY = analogRead(joystick_Y);
             valeurbouton = digitalRead(bouton);
             //Serial.println(valeurbouton);
             valeurnuke = digitalRead(nuke);
             Serial.print("nuke = ");
             Serial.println(valeurnuke);
             
          }
          
          ecran();
          if (valeurnuke == 0)
              {
                display.drawLine(pointX, pointY, pointX+bateaux[i]-1, pointY, myGREEN);
                valeurX = analogRead(joystick_X);
                valeurY = analogRead(joystick_Y);
                
              }
              else{
                display.drawLine(pointX, pointY, pointX, pointY+bateaux[i]-1, myGREEN);
                valeurX = analogRead(joystick_X);
                valeurY = analogRead(joystick_Y);
              }
             
              if (valeurnuke2 != valeurnuke){
                  valeurnuke2 = valeurnuke;
              };

             if (valeurbouton == 0){
              collision(i);
              if (m==5){
                valider=true;
              }else{
                m=0;
              }
             }
      }

     if (valeurnuke == 0){
       switch (i){
          case 0:
            bat[0][0]=pointX;
            bat[0][1]=pointY;
            bat[0][2]=pointX+bateaux[i]-1;
            bat[0][3]=pointY;
            break;
         
         case 1:
            bat[1][0]=pointX;
            bat[1][1]=pointY;
            bat[1][2]=pointX+bateaux[i]-1;
            bat[1][3]=pointY;
            break;
         
         case 2:
            bat[2][0]=pointX;
            bat[2][1]=pointY;
            bat[2][2]=pointX+bateaux[i]-1;
            bat[2][3]=pointY;
            break;
         
         case 3:
            bat[3][0]=pointX;
            bat[3][1]=pointY;
            bat[3][2]=pointX+bateaux[i]-1;
            bat[3][3]=pointY;
            break;
         
         case 4:
            bat[4][0]=pointX;
            bat[4][1]=pointY;
            bat[4][2]=pointX+bateaux[i]-1;
            bat[4][3]=pointY;
            break;
            }     
     }else {
      switch (i){
          case 0:
            bat[0][0]=pointX;
            bat[0][1]=pointY;
            bat[0][2]=pointX;
            bat[0][3]=pointY+bateaux[i]-1;
            break;
         
         case 1:
            bat[1][0]=pointX;
            bat[1][1]=pointY;
            bat[1][2]=pointX;
            bat[1][3]=pointY+bateaux[i]-1;
            break;
         
         case 2:
            bat[2][0]=pointX;
            bat[2][1]=pointY;
            bat[2][2]=pointX;
            bat[2][3]=pointY+bateaux[i]-1;
            break;
         
         case 3:
            bat[3][0]=pointX;
            bat[3][1]=pointY;
            bat[3][2]=pointX;
            bat[3][3]=pointY+bateaux[i]-1;
            break;
         
         case 4:
            bat[4][0]=pointX;
            bat[4][1]=pointY;
            bat[4][2]=pointX;
            bat[4][3]=pointY+bateaux[i]-1;
            break;
            }
     }
     
   } 

           pointX =11;
           pointY =11;
    int a = 0;
       while(a<100){
    
              Serial.println("orange");
              valeurX = analogRead(joystick_X);
              valeurY = analogRead(joystick_Y);
              valeurbouton = digitalRead(bouton);
    
                display.showBuffer();
            if (valeurX>2500){
                Serial.println("coucoux");
                pointX+=1;
                delay(200);
            }else if (valeurX<1000){
                pointX-=1;
                delay(200);
            }
            if (valeurY>2500){
                Serial.println("coucouy");
                pointY+=1;
                delay(200);
            }else if (valeurY<1000){
                pointY-=1;
                delay(200);
          }
    
          while (valeurX>1000 && valeurX<2500 && valeurY>1000 && valeurY<2500 && valeurbouton == 1){
                 /*display.drawLine(pointX, pointY, pointX+bateaux[i]-1, pointY, myGREEN);*/
                 display.clearDisplay();
                 ecran();
                 valeurX = analogRead(joystick_X);
                 valeurY = analogRead(joystick_Y);
                 valeurbouton = digitalRead(bouton);
                 //Serial.println(valeurbouton);
    
              }
              ecran();
              display.drawPixel(pointX, pointY, myORANGE);
            
          if (valeurbouton == 0){
                  a += 1;
                  delay(500);
                  Serial.println("target");
                  Serial.println(a);
    
                  hit[pointX-11][pointY-11]=1;
                 }


     }
     
  }

void ecran(){
  display.fillScreen(myCYAN); //Eau clair
  display.fillRect(11 , 11, 10, 10, myBLUE); //Eau
  display.drawRect(10, 10, 12, 12, myPURPLE); //Contour
  /*display.drawLine(32, 1, 32, 32, myWHITE);
  display.fillRect(15, 15, 1, 4, myWHITE); //Bateau
  display.drawPixel(15, 16, myRED);*/
  for (int i=0; i < 5; i++){
    display.drawLine(bat[i][0], bat[i][1], bat[i][2], bat[i][3], myWHITE); 
  }      
}
void collision(int a){
   for (int i = 0; i<5; i++){
    if (valeurnuke == 0){
      if (i == a){
        m++;
      }else{
        if (bat[i][0]-1 < pointX < pointX+bateaux[a] < bat[i][2]+1 || bat[i][1]-1 < pointY < bat[i][3]+1){
            Serial.print("ligma balls");
            //placement impossible  
        } else {
        Serial.print("Qu'est ce que sex ?");
        valider=true;
        m++;
        }
      }
      
    }else{
      if (i == a){
        m++;
      }else{
        if (bat[i][1] < pointY < pointY+bateaux[a] < bat[i][3] || bat[i][0] < pointX < bat[i][2]){
            //placement impossible
        } else {
          valider=true;
          m++;
        }
      }
    }
  }
} 
 /* for (int i = 0; i<4; i++){
    display.drawCircle(18, 18, 2, myRED);
    delay(1000);
    display.drawCircle(18, 18, 3, myRED);
    display.fillCircle(18, 18, 2, myORANGE);
    delay(1000);
    display.drawCircle(18, 18, 4, myRED);
    display.fillCircle(18, 18, 3, myORANGE);
    }*/

    /*Serial.println(analogRead(27));
    Serial.println(analogRead(26));
    Serial.println(analogRead(25));
    Serial.println("-------------");
    delay(1000);
};
  */
