#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>


#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN            9
#define NUMPIXELS      4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t color;

#define Select_pin 5
#define Up_pin 6
#define Down_pin 7

#define BACKLIGHT_PIN     13
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define Lcd_power 10

int metai=2018;
int menuo=12;
int diena=22;

int valanda=8;
int minutes=10;
int suma=0;
int suma_nust=100;

int RELAY1 = A0;

byte customChar[] = {
  B00000,
  B00111,
  B01000,
  B11110,
  B01000,
  B11110,
  B01000,
  B00111
};


const int coinInt = 0;  
float coinsValue = 0.0;///turi buti 0.0
int coinsChange = 0;                  

int select_btn_state = 0;
int up_btn_state = 0;
int down_btn_state = 0;


int nustatytas=0;
int openBoxas=0;
int count=0;
int mode=0;
int menu1=0;
int pradinisMeniu=0;
int autas=0;
int moneyNUST=0;
int timeNUST=0;

int adr_nustatytas=0;
int adr_openBoxas=2;
int adr_count=4;
int adr_mode=6;
int adr_menu1=8;
int adr_pradinisMeniu=10;
int adr_autas=12;
int adr_moneyNUST=14;
int adr_timeNUST=16;

int adr_suma_nust=36;
int adr_suma=42;
int adr_coinsValue=22;

int adr_metai=28;
int adr_menuo=32;
int adr_diena=34;




void setup() {
  // put your setup code here, to run once:
  pinMode(Lcd_power, OUTPUT);
  digitalWrite(Lcd_power, HIGH);
   Serial.begin(9600);
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, LOW);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(0, customChar);
  
// /*
  //EEPROM.put(adr_metai,metai);
  //EEPROM.put(adr_menuo,menuo);
  //EEPROM.put(adr_diena,diena);

  EEPROM.get(adr_nustatytas,nustatytas);
  EEPROM.get(adr_openBoxas,openBoxas);
  EEPROM.get(adr_count,count);
  EEPROM.get(adr_mode,mode);
  EEPROM.get(adr_menu1,menu1);
  EEPROM.get(adr_pradinisMeniu,pradinisMeniu);
  EEPROM.get(adr_autas,autas);
  EEPROM.get(adr_moneyNUST,moneyNUST);
  EEPROM.get(adr_timeNUST,timeNUST);
  EEPROM.get(adr_suma_nust,suma_nust);
  EEPROM.get(adr_coinsValue,coinsValue);
  
  EEPROM.get(adr_metai,metai);
  EEPROM.get(adr_menuo,menuo);
  EEPROM.get(adr_diena,diena);
  EEPROM.get(adr_suma,suma);

//-------Metai
for (int i = 29; i < 32; i++) {
    EEPROM.get(adr_metai, metai);
    adr_metai = adr_metai + sizeof(metai);  
  }

for (int i = 28; i < 32; i++) {
    EEPROM.get(i * sizeof(metai), metai);
  }
//------CoinsValue
for (int i = 23; i < 28; i++) {
    EEPROM.get(adr_coinsValue, coinsValue);
    adr_coinsValue = adr_coinsValue + sizeof(coinsValue);  
  }

for (int i = 22; i < 28; i++) {
    EEPROM.get(i * sizeof(coinsValue), coinsValue);
  }
 //-------Suma
for (int i = 43; i < 47; i++) {
    EEPROM.get(adr_suma, suma);
    adr_suma = adr_suma + sizeof(suma);  
  }

for (int i = 42; i < 47; i++) {
    EEPROM.get(i * sizeof(suma), suma);
  }

 //-------Suma_nust
for (int i = 37; i < 42; i++) {
    EEPROM.get(adr_suma_nust, suma_nust);
    adr_suma_nust = adr_suma_nust + sizeof(suma_nust);  
  }

for (int i = 36; i < 42; i++) {
    EEPROM.get(i * sizeof(suma_nust), suma_nust);
  }


  
 attachInterrupt(coinInt, coinInserted, RISING); 
   pinMode(Select_pin, INPUT);
   pinMode(Up_pin, INPUT);
   pinMode(Down_pin, INPUT);

   
  
   setTime(22,34,0,20,12,17);
  //RTC.set(now());
  while (!Serial) ; 
  setSyncProvider(RTC.get);   
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else{
     Serial.println(" ");}

 #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
pixels.begin();

      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.setPixelColor(1, pixels.Color(0,0,0));
      pixels.setPixelColor(2, pixels.Color(0,0,0));
      pixels.setPixelColor(3, pixels.Color(0,0,0));
      pixels.show();
}

void coinInserted()    
{
  coinsValue = coinsValue +0.10;  
  coinsChange = 1;                           
}

void loop() {
  // put your main code here, to run repeatedly:
select_btn_state = digitalRead(Select_pin);
up_btn_state = digitalRead(Up_pin);
down_btn_state = digitalRead(Down_pin);



while(nustatytas==1 && openBoxas==0){

  
  EEPROM.update(adr_nustatytas,nustatytas);
  EEPROM.update(adr_openBoxas,openBoxas);
  EEPROM.update(adr_count,count);
  EEPROM.update(adr_mode,mode);
  EEPROM.update(adr_menu1,menu1);
  EEPROM.update(adr_pradinisMeniu,pradinisMeniu);
  EEPROM.update(adr_autas,autas);
  EEPROM.update(adr_moneyNUST,moneyNUST);
  EEPROM.update(adr_timeNUST,timeNUST);
  //EEPROM.update(adr_suma_nust,suma_nust);
  //EEPROM.update(adr_suma,suma);
  for (int i = 43; i < 47; i++) {
    EEPROM.put(i * sizeof(suma), suma);
  }
  for (int i = 37; i < 42; i++) {
    EEPROM.put(i * sizeof(suma_nust), suma_nust);
  }
  delay(100);
  
  
  
   if(coinsChange == 1)          
  {
   
    coinsChange = 0;              
    Serial.print("Credit: ");
    Serial.println(coinsValue);
    //lcd.setCursor(9,1);
    //lcd.print(coinsValue);
    //lcd.write((uint8_t)0);

    for (int i = 23; i < 28; i++) {

    EEPROM.put(i * sizeof(coinsValue), coinsValue);
 
  }
    
   
       
  }
 
 if(coinsValue>=suma_nust && openBoxas==0){
  
  lcd.clear();
  lcd.print("sutaupyta");
  delay(1000);
  openBoxas++;
  nustatytas=3;
  autas=1;
  count=1;
  }else if (openBoxas==0){
    lcd.setCursor(9,1);
    lcd.print(coinsValue);
    lcd.write((uint8_t)0);
    lcd_pinigai();
    digitalWrite(RELAY1, LOW);//solenoidas
    lcd.setCursor(0,0);
      lcd.print("Tikslas ->");
      lcd.setCursor(0,1);
      lcd.print("Yra ->");
 
 }
}
//----------------------------- TIME
while(nustatytas==2 && openBoxas==5){
  
   EEPROM.update(adr_nustatytas,nustatytas);
  EEPROM.update(adr_openBoxas,openBoxas);
 /* EEPROM.update(adr_count,count);
  EEPROM.update(adr_mode,mode);
  EEPROM.update(adr_menu1,menu1);
  EEPROM.update(adr_pradinisMeniu,pradinisMeniu);
  EEPROM.update(adr_autas,autas);
  EEPROM.update(adr_moneyNUST,moneyNUST);
  EEPROM.update(adr_timeNUST,timeNUST);
 */ 
 //EEPROM.update(adr_metai,metai);
 for (int i = 29; i < 32; i++) {
    EEPROM.put(i * sizeof(metai), metai);
  }
  EEPROM.update(adr_menuo,menuo);
  EEPROM.update(adr_diena,diena);
  delay(100);

  
   if(coinsChange == 1)          
  {
    
    coinsChange = 0;              
    Serial.print("Credit: ");
    Serial.println(coinsValue);
    //lcd.setCursor(9,1);
    //lcd.print(coinsValue);
    //lcd.write((uint8_t)0);

    for (int i = 23; i < 28; i++) {

    EEPROM.put(i * sizeof(coinsValue), coinsValue);
 
  } 
     
  }
 
 if(year()>=metai && month()>=menuo && day()>=diena && hour()>=valanda  && openBoxas==5){
  
  lcd.clear();
  lcd.print("sutaupyta");
  delay(1000);
  openBoxas=1;
  nustatytas=3;
  autas=1;
  count=1;
  }else if (openBoxas==5){

    
    lcd.setCursor(9,1);
    lcd.print(coinsValue);
    lcd.write((uint8_t)0);
    
    lcd.setCursor(0,0);
    
    if(metai<10){
      lcd.print("0");
      lcd.print(metai);
      }else{
        lcd.print(metai);
        }
    
    lcd.print("/");
    if(menuo<10){
      lcd.print("0");
      lcd.print(menuo);
    }else{
      lcd.print(menuo);
      }
    lcd.print("/");
    if(diena<10){
      lcd.print("0");
      lcd.print(diena);
    }else{
      lcd.print(diena);
      }
    digitalWrite(RELAY1, LOW);//solenoidas
    
 
 }
}

//OPEN------------------------------------------------------------------------
if(openBoxas==1 && nustatytas==3 && autas==1){
  
  
  
  
  lcd_on();
 lcd.clear();
 lcd.print("Open");
 openBoxas++;
}
  if(select_btn_state==HIGH && count==1 && openBoxas==2 && autas==1){
    
    lcd.clear();
    lcd.print("Open");
      count++;
      openBoxas++;
      digitalWrite(RELAY1, HIGH);
//------------------------------------------------------------
      
      pixels.setPixelColor(0, pixels.Color(176,44,44));
      pixels.setPixelColor(1, pixels.Color(176,44,44));
      pixels.setPixelColor(2, pixels.Color(176,44,44));
      pixels.setPixelColor(3, pixels.Color(176,44,44));
      pixels.show();
//------------------------------------------------------------      
      delay(10000);//solenoidas
      digitalWrite(RELAY1, LOW);
      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.setPixelColor(1, pixels.Color(0,0,0));
      pixels.setPixelColor(2, pixels.Color(0,0,0));
      pixels.setPixelColor(3, pixels.Color(0,0,0));
      pixels.show();
      delay(1000);//solenoidas
      pixels.setPixelColor(0, pixels.Color(255,0,0));
      pixels.setPixelColor(1, pixels.Color(255,0,0));
      pixels.setPixelColor(2, pixels.Color(255,0,0));
      pixels.setPixelColor(3, pixels.Color(255,0,0));
      pixels.show();
      select_btn_state=LOW;
      lcd.clear();
      lcd.print("Go To Menu");
          
  }
  else if(select_btn_state==HIGH && count==2 && openBoxas==3 && autas==1){
      digitalWrite(RELAY1, LOW);
      delay(1000);//solenoidas 
      coinsValue=0.0;
      suma_nust=100;
      suma=0;
      autas=0;
      openBoxas=0;
      count=0;
      menu1=0;
      mode=0;
      nustatytas=0;
      moneyNUST=1;
      timeNUST=5;
      lcd.clear();
      select_btn_state=LOW;
      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.setPixelColor(1, pixels.Color(0,0,0));
      pixels.setPixelColor(2, pixels.Color(0,0,0));
      pixels.setPixelColor(3, pixels.Color(0,0,0));
      pixels.show();

      EEPROM.update(adr_nustatytas,nustatytas);
  EEPROM.update(adr_openBoxas,openBoxas);
  EEPROM.update(adr_count,count);
  EEPROM.update(adr_mode,mode);
  EEPROM.update(adr_menu1,menu1);
  EEPROM.update(adr_pradinisMeniu,pradinisMeniu);
  EEPROM.update(adr_autas,autas);
  EEPROM.update(adr_moneyNUST,moneyNUST);
  EEPROM.update(adr_timeNUST,timeNUST);
  EEPROM.update(adr_suma_nust,suma_nust);
  EEPROM.update(adr_suma,suma);
  for (int i = 15; i < 19; i++) {

    EEPROM.update(i * sizeof(coinsValue), coinsValue);
 
  } 
  delay(100);  
      
      }

  //---------------------------------------------------------------------  


  

if(nustatytas==0 && openBoxas==0 || nustatytas==0 && openBoxas==5){
  
  
  if(pradinisMeniu==0 && openBoxas==0){
    lcd.setCursor(0,0);
    lcd.print("Mode:");
    lcd.setCursor(12,0);
    lcd.print("Time");
    lcd.setCursor(11,1);
    lcd.print("Money");
   /* if(mode==0){
      lcd.setCursor(6,1);
      lcd.print("   ");
      lcd.setCursor(6,0);
      lcd.print("-->");
      }
    */
   if(up_btn_state==HIGH && count==0 && mode==0 && menu1==0 && autas==0 && openBoxas==0){
      lcd.setCursor(6,1);
      lcd.print("   ");
      lcd.setCursor(6,0);
      lcd.print("-->");
      mode++;
      timeNUST=5;
      delay(500);
      
    }else if(down_btn_state==HIGH && count==0 && mode==1 && menu1==0 && autas==0 && openBoxas==0){
      lcd.setCursor(6,0);
      lcd.print("   ");
      lcd.setCursor(6,1);
      lcd.print("-->");
      mode--;
      moneyNUST=0;
      timeNUST=0;
      delay(500);
      
      }
  }

    if(select_btn_state==HIGH && count==0 && mode ==0 && menu1==0 && autas==0 && moneyNUST==0 && openBoxas==0){
      //Money nustatymai
      menu1=1;
      pradinisMeniu=1;
      lcd.clear();
       delay(1000);
       
      }else if(menu1==1 && openBoxas==0){
      
      lcd.setCursor(7,0);
      lcd.print(suma);
      lcd.write((uint8_t)0);
     
    if(up_btn_state==HIGH && count==0 && mode==0 && menu1==1 && autas==0 && openBoxas==0){
          suma=suma+10;
          delay(500);
          }else if(down_btn_state==HIGH && count==0 && mode==0 && menu1==1 && autas==0 && openBoxas==0){
            if(suma>0){
            suma=suma-10;
            delay(500);
            }
            }else if(select_btn_state==HIGH && count==0 && mode==0 && menu1==1 && autas==0 && openBoxas==0 ){
              suma_nust=suma;
             // mode++;
              menu1--;
              pradinisMeniu=0;
              nustatytas++;
              lcd.clear();
              autas=1;
              moneyNUST=1;
              delay(1000);

              EEPROM.update(adr_suma_nust,suma_nust);
              EEPROM.update(adr_suma,suma);
              }
              }

//-------------------------------------------------------------------------------//

if(select_btn_state==HIGH && timeNUST==5){
  timeNUST=6;
  count=5;
  mode=5;
  menu1=5;
  autas=5;
  //-----------------
  metai=year();
  menuo=month();
  diena=day();
  //-----------------
  openBoxas=5;
  delay(1000);
  timeNUST=6;
  lcd.clear();
  select_btn_state=LOW;
  
  
  }
  
 if(timeNUST==6 && count==5 && menu1==5 && mode==5 && autas==5 && openBoxas==5){
  if(timeNUST==6 && menu1==5 && mode==5){
    
    lcd.clear();
    
    if(metai<10){
      lcd.print("0");
      lcd.print(metai);
      }else{
        lcd.print(metai);
        }
    lcd.print(">");
    lcd.print("<");
    if(menuo<10){
      lcd.print("0");
      lcd.print(menuo);
      }else{
      lcd.print(menuo);
      }
    lcd.print(">");
    lcd.print("<");
    if(diena<10){
      lcd.print("0");
      lcd.print(diena);
      }else{
    lcd.print(diena);
      }
    lcd.print(">");
    lcd.setCursor(0,1);
    lcd.print("||||");
    menu1=6;
    
    
  }
 } 
    
 if(up_btn_state==HIGH && timeNUST==6 && mode==5 && menu1==6 && autas==5 && count==5 && openBoxas==5){
    metai++;
    delay(500);
    menu1=5; 
    }else if (down_btn_state==HIGH && timeNUST==6 && mode==5 && menu1==6 && autas==5 && count==5 && openBoxas==5){
      if(metai<=year()){
        }else{
      metai--;
      delay(500);
      menu1=5;
        }
      }else if (select_btn_state==HIGH && timeNUST==6 && mode==5 && menu1==6 && autas==5 && count==5 && openBoxas==5){
        mode=6;
        delay(1000);
        lcd.clear();
        select_btn_state=LOW;
        }
      
//------------------------Nustatytas menuo

if(timeNUST==6 && count==5 && menu1==6 && mode==6 && autas==5 && openBoxas==5){
  if(timeNUST==6 && menu1==6 && mode==6){
    lcd.clear();
    
    if(metai<10){
      lcd.print("0");
      lcd.print(metai);
      }else{
        lcd.print(metai);
        }
    lcd.print(">");
    lcd.print("<");
    if(menuo<10){
      lcd.print("0");
      lcd.print(menuo);
      }else{
      lcd.print(menuo);
      }
    lcd.print(">");
    lcd.print("<");
    if(diena<10){
      lcd.print("0");
      lcd.print(diena);
      }else{
    lcd.print(diena);
      }
    lcd.print(">");
    lcd.setCursor(6,1);
    lcd.print("||");
    menu1=7;
    
  }
 } 
    
 if(up_btn_state==HIGH && down_btn_state==LOW && timeNUST==6 && mode==6 && menu1==7 && autas==5 && count==5 && openBoxas==5){
  if(menuo<12){
    menuo++;
    delay(500);
    menu1=6;
  }else{
    if(menuo>1){
        if(metai==year() && menuo>=month()){
            menuo=month();
            menuo--;
          }else{
    menuo=1;
    menu1=6;
    delay(1000); 
          }
    }
  }
  up_btn_state=LOW;
    }else if (down_btn_state==HIGH && up_btn_state==LOW && timeNUST==6 && mode==6 && menu1==7 && autas==5 && count==5 && openBoxas==5){
      if(menuo>1){
        if(metai==year() && menuo<=month()){
          }else{
      menuo--;
      delay(500);
      menu1=6;
          }
      }else{
        menuo=12;
        menu1=6;
        delay(1000);
      }
      down_btn_state=LOW;
      }else if(select_btn_state==HIGH && timeNUST==6 && mode==6 && menu1==7 && autas==5 && count==5 && openBoxas==5){
       mode=7;
       delay(500);
       lcd.clear();
       select_btn_state=LOW;
        }
        
        if (down_btn_state==HIGH && up_btn_state==HIGH && timeNUST==6 && mode==6 && menu1==7 && autas==5 && count==5 && openBoxas==5 ){
          delay(1000);
          menu1=5;
          mode=5;
        }

//-----------------diena
if(timeNUST==6 && count==5 && menu1==7 && mode==7 && autas==5 && openBoxas==5){
  if(timeNUST==6 && menu1==7 && mode==7){
    lcd.clear();
    
    if(metai<10){
      lcd.print("0");
      lcd.print(metai);
      }else{
        lcd.print(metai);
        }
    lcd.print(">");
    lcd.print("<");
    if(menuo<10){
      lcd.print("0");
      lcd.print(menuo);
      }else{
      lcd.print(menuo);
      }
    lcd.print(">");
    lcd.print("<");
    if(diena<10){
      lcd.print("0");
      lcd.print(diena);
      }else{
    lcd.print(diena);
      }
    lcd.print(">");
    lcd.setCursor(10,1);
    lcd.print("||");
    menu1=8;
    
  }
 } 
    
 if(up_btn_state==HIGH && down_btn_state==LOW && timeNUST==6 && mode==7 && menu1==8 && autas==5 && count==5 && openBoxas==5){
  //-------------------------Sausis---Kovas---Geguze---Liepa---Rugpjutis---Spalis---Gruodis
  if(menuo==1 || menuo==3 || menuo==5 || menuo==7 || menuo==8 || menuo==10 || menuo==12){ 
    if(diena<31){
      diena++;
      delay(500);
      menu1=7;
      }else{
        if(metai==year() && menuo == month() && diena>=day()){
            diena=day();
            diena--;
            }else{
        diena=1;
        menu1=7;
        delay(1000);
        }
      }
    //---------------------vasaris  
   }else if(menuo==2){
      if(diena<28){
        diena++;
        delay(500);
        menu1=7;
        }else{
          if(metai==year() && menuo == month() && diena>=day()){
            diena=day();
            diena--;
            }else{
          diena=1;
          menu1=7;
          delay(1000);
            }
        }
   //----------------------Balandis---Birzelis---Rugsejis---Lapkritis
   }else if(menuo==4 || menuo==6 || menuo==9 || menuo==11){
      if(diena<30){
        diena++;
        delay(500);
        menu1=7;
        }else{
          if(metai==year() && menuo == month() && diena>=day()){
            diena=day();
            diena--;
            }else{
          diena=1;
          menu1=7;
          delay(1000);
            }
        }
   }  
    up_btn_state=LOW;
    }else if(down_btn_state==HIGH && up_btn_state==LOW && timeNUST==6 && mode==7 && menu1==8 && autas==5 && count==5 && openBoxas==5){
      //-------------------------Sausis---Kovas---Geguze---Liepa---Rugpjutis---Spalis---Gruodis
      if(menuo==1 || menuo==3 || menuo==5 || menuo==7 || menuo==8 || menuo==10 || menuo==12){
        if(diena>1){
          if(metai==year() && menuo == month() && diena<=day()){
            }else{
        diena--;
        delay(500);
        menu1=7;
            }
        }else{
          diena=31;
          menu1=7;
          delay(1000);
          }
     //---------------------vasaris 
      }else if(menuo==2){
        if(diena>1){
          if(metai==year() && menuo == month() && diena<=day()){
            }else{
        diena--;
        delay(500);
        menu1=7;
            }
        }else{
          diena=28;
          menu1=7;
          delay(1000);
          }
        //----------------------Balandis---Birzelis---Rugsejis---Lapkritis  
      }else if(menuo==4 || menuo==6 || menuo==9 || menuo==11){
        if(diena>1){
          if(metai==year() && menuo == month() && diena<=day()){
            }else{
        diena--;
        delay(500);
        menu1=7;
            }
        }else{
          diena=30;
          menu1=7;
          delay(1000);
          }
      }
        down_btn_state=LOW;
      }else if(select_btn_state==HIGH && timeNUST==6 && mode==7 && menu1==8 && autas==5 && count==5 && openBoxas==5){
       
       delay(500);
       lcd.clear();
       nustatytas=2;
       //
       mode=0;
       menu1=0;
       autas=0;
       count=0;
       
       //
        }else if(down_btn_state==HIGH && up_btn_state==HIGH && timeNUST==6 && mode==7 && menu1==8 && autas==5 && count==5 && openBoxas==5){
          delay(500);
          menu1=6;
          mode=6;
          }


  }
}


void lcd_pinigai(){
  lcd.setCursor(11,0);
  lcd.print(suma);
lcd.write((uint8_t)0);
  lcd.print(" ");
  
  }

void lcd_real_time(){
  
  lcd.setCursor(0,0);
 lcd.print(year());
 lcd.print("/");
 if(month()<10){
  lcd.print("0");
  lcd.print(month());
  }else{
    lcd.print(month());
    }
 lcd.print("/");
 if(day()<10){
  lcd.print("0");
  lcd.print(day());
  }else{
    lcd.print(day());
    }
 lcd.setCursor(0,1);
  if (hour()<10){
      lcd.print("0");
      lcd.print(hour());
  }else{
      lcd.print(hour());
    }
 lcd.print(":");
 if (minute()<10){
      lcd.print("0");
      lcd.print(minute());
  }else{
      lcd.print(minute());
    } 
 lcd.print(":");
 if (second()<10){
      lcd.print("0");
      lcd.print(second());
  }else{
      lcd.print(second());
    }
 lcd.print(" ");
  }

  

void lcd_on_money(){
  digitalWrite(Lcd_power,HIGH);
  lcd.begin(16,2);
  lcd.createChar(0, customChar);
  lcd_pinigai();
    digitalWrite(RELAY1, LOW);//solenoidas
    lcd.setCursor(0,0);
      lcd.print("Tikslas ->");
      lcd.setCursor(0,1);
      lcd.print("Yra ->");
  }

void lcd_on_time(){
  digitalWrite(Lcd_power,HIGH);
  lcd.begin(16,2);
  lcd.createChar(0, customChar);
  lcd.setCursor(0,0);
    lcd.print(metai);
    lcd.print("/");
    if(menuo<10){
      lcd.print("0");
      lcd.print(menuo);
    }else{
      lcd.print(menuo);
      }
    lcd.print("/");
    if(diena<10){
      lcd.print("0");
      lcd.print(diena);
    }else{
      lcd.print(diena);
      }
    digitalWrite(RELAY1, LOW);
  }

void lcd_on(){
  digitalWrite(Lcd_power,HIGH);
  lcd.begin(16,2);
  lcd.createChar(0, customChar);
  }

void lcd_off(){
  digitalWrite(Lcd_power,LOW);
  }

  
