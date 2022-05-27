#define USE_ARDUINO_INTERRUPTS true    // bpm i doğru ölçmek için kesintiler
#include <PulseSensorPlayground.h>     // PulseSensorPlayground kütüpanesi eklendi   
#include <Wire.h> //LCD Ekranımızı kullanabilmek için kütüphane tanımlaması yapıyoruz
#include <LiquidCrystal_I2C.h> //LCD Ekranımızı kullanabilmek için kütüphane tanımlaması yapıyoruz

const int PulseWire = 0; 
int Threshold = 515;           // sensörde algılanacak vuruş eşik değeri

LiquidCrystal_I2C lcd(0x27, 16, 2);//LCD Ekranımızın I2C adresinin "0x27" olduğunu ve 2 satır 16 sütundan oluştuğunu tanımlıyoruz
                               
PulseSensorPlayground pulseSensor;  // instance aldık

void setup() {   
  lcd.begin(); //LCD Ekranımızın 2 satır ve 16 sütundan oluştuğunu tanımlıyoruz
  Serial.begin(9600);          // seri iletişim başlatıldı

  // pulsesensör değişken atamaları
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   

  // pulsesensör nesnesinin oluştuğunu ve sinyal göndermeye başladığını yazdırdık
   if (pulseSensor.begin()) {
    Serial.println("Nabız Olcer Nesnesi Olustu!");   
  }
}



void loop() {

 int myBPM = pulseSensor.getBeatsPerMinute();  // pulsesensörden gelen bpm i döngü içinde myBPM e atadık
                                               // her atımda MyBPM değişiyor.

if (pulseSensor.sawStartOfBeat()) {            // pulsesensörde atım olup olmadığını kontrol ediyoruz
 Serial.println("♥  Kalp Atışı Algılandı!"); // eğer atım okunuyorsa "kalp atışı algılandı !" yazacak
 Serial.print("BPM: ");                        // "BPM" ifadesi ekrana yazdır.
 Serial.println(myBPM);                        // BPM değerini ekrana yazdır.
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("BPM: ");                        // "BPM" ifadesi ekrana yazdır.
 lcd.print(myBPM);                        // BPM değerini ekrana yazdır.
}

  delay(20);                    // tüm bu işlemlerden sonra 20 milisaniye beklet

}
