#define USE_ARDUINO_INTERRUPTS true    // bpm i doru lmek icin kesintiler
#include <PulseSensorPlayground.h>     // PulseSensorPlayground ktpanesi eklendi   
#include <Wire.h> //LCD Ekranmz kullanabilmek iin ktphane tanmlamas yapyoruz
#include <LiquidCrystal_I2C.h> //LCD Ekranmz kullanabilmek iin ktphane tanmlamas yapyoruz

const int PulseWire = 0; 
int Threshold = 515;           // sensrde alglanacak vuru eik deeri

LiquidCrystal_I2C lcd(0x27, 16, 2);//LCD Ekranmzn I2C adresinin "0x27" olduunu ve 2 satr 16 stundan olutuunu tanmlyoruz
                               
PulseSensorPlayground pulseSensor;  // instance aldk

void setup() {   
  lcd.begin(); //LCD Ekranmzn 2 satr ve 16 stundan olutuunu tanmlyoruz
  Serial.begin(9600);          // seri iletiim balatld

  // pulsesensr deiken atamalar
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   

  // pulsesensr nesnesinin olutuunu ve sinyal gndermeye baladn yazdrdk
   if (pulseSensor.begin()) {
    Serial.println("Nabz Olcer Nesnesi Olustu!");   
  }
}



void loop() {

 int myBPM = pulseSensor.getBeatsPerMinute();  // pulsesensrden gelen bpm i dng iinde myBPM e atadk
                                               // her atmda MyBPM deiiyor.

if (pulseSensor.sawStartOfBeat()) {            // pulsesensrde atm olup olmadn kontrol ediyoruz
 Serial.println("  Kalp At Algland!"); // eer atm okunuyorsa "kalp at algland !" yazacak
 Serial.print("BPM: ");                        // "BPM" ifadesi ekrana yazdr.
 Serial.println(myBPM);                        // BPM deerini ekrana yazdr.
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("BPM: ");                        // "BPM" ifadesi ekrana yazdr.
 lcd.print(myBPM);                        // BPM deerini ekrana yazdr.
}

  delay(20);                    // tm bu ilemlerden sonra 20 milisaniye beklet

}
