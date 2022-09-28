//Importiert die Benötigte Bibliothek
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

SoftwareSerial nextion(6, 5); //Ersetzt RX und TX Pins im Nextion Display

int LEDPIN  = 10; //Pin Eingang zum Neopixel
int NUMPIXELS = 80; //Anzahl der Menge an Neopixels
bool mode = true;
int counter;
const byte interruptPin = 2;


//Sagt die Anzahl der Neopixel und der Pineingang für das Signal
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_RGB + NEO_KHZ800);

String daten_display = ""; //String wird Definiert (Zeichenkette)


void setup() {
  Serial.begin(9600); //Startet die Serielle Kommunikation
  nextion.begin(9600);
  pixels.begin(); //Initialisiert die NeoPixel Library

  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt_call, FALLING);
}

void loop() {
//--------------------------------------------------------------------
//Wird Abgefragt welches Signal(Zeichen) der jeweilige Button sendet
  if (nextion.available() > 0){
    daten_display += char (nextion.read());
  }
//--------------------------------------------------------------------
//Wenn Button "jeweiliges Zeichen" entspricht dann Code ausführen
  if(daten_display == "rot"){
    Serial.println("ROT");
    Rot(); //Ruft die Methode auf
    daten_display=""; //Setzt die Zeichenkette wieder zurück
  }
  if(daten_display == "blau"){
    Serial.println("BLAU");
    Blau();
    daten_display="";
  }
  if(daten_display == "gruen"){
    Serial.println("GRÜN");
    Gruen();
    daten_display="";
  }
  if(daten_display == "weis"){
    Serial.println("WEIß");
    Weis();
    daten_display="";
  }
  if(daten_display == "orange"){
    Serial.println("ORANGE");
    Orange();
    daten_display="";
  }
  if(daten_display == "gelb"){
    Serial.println("GELB");
    Gelb();
    daten_display="";
  }
  if(daten_display == "rainbow"){
    Serial.println("REGENBOGEN");
    rainbow();
    daten_display="";
  }
  if(daten_display == "zirkus"){
    Serial.println("ZIRKUS");
    ZirkusEffekt(0xff,0,0,50);
    daten_display="";
  }
  if(daten_display == "fade"){
    Serial.println("ColorWipe");
    ColorWipe(0x00,0xff,0x00, 50);
    ColorWipe(0x00,0x00,0x00, 50);
    ColorWipe(0x00,0xff,0x00, 50);
    ColorWipe(0x00,0x00,0x00, 50);
    ColorWipe(0x00,0xff,0x00, 50);
    ColorWipe(0x00,0x00,0x00, 50);        
    daten_display="";
  }
  if(daten_display == "clear"){
    Serial.println("LED STRIPES GELÖSCHT");
    Leschen();
    daten_display="";
  }
}
//-----------------------------------------------------------------------------------
//pixel.Color RGB werte von 0 - 255
//-----------------------------------------------------------------------------------
void Rot(){
  for(int i=0; i<NUMPIXELS; i++) {//Färbt alle Neopixels der Entsprechenden Farbe
    pixels.setPixelColor(i, pixels.Color(0,150,0)); //Setzt die Farbe der Neopixel zu Rot
    pixels.show(); //Sendet die Neue Farbe zur Hardware
  }
}
void Gruen(){
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150,0,0)); //Grün
    pixels.show();
  }
}
void Blau(){
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,150)); //blau
    pixels.show();
  }
}
void Gelb(){
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150,150,0)); //Gelb
    pixels.show();
  }
}
void Orange(){
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(50,150,0)); //Orange
    pixels.show();
  }
}
void Weis(){
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150,150,150)); //Weiß
    pixels.show();
  }
}
void Leschen(){
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0)); //Keine Farbe
    pixels.clear();
    pixels.begin();
    pixels.show();
  }
}
//--------------------------------------------------------------------------------------
void rainbow() {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<pixels.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show();
    delay(5);
  } pixels.clear();
}
//--------------------------------------------------------------------------------------
void ZirkusEffekt(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j=0; j<10; j++) { //Anzahl der Wiederholungen
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUMPIXELS; i=i+3) {
        pixels.setPixelColor(i+q, red, green, blue);    //jeden dritten anschalten
      }
      pixels.show();
     
      delay(SpeedDelay);
     
      for (int i=0; i < NUMPIXELS; i=i+3) {
        pixels.setPixelColor(i+q, 0,150,0);        //jeden dritten ausschalten
      } 
  }
 } pixels.clear();
}
//--------------------------------------------------------------------------------------
void ColorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i, red, green, blue);
      pixels.show();
      delay(SpeedDelay);
  }
}
//--------------------------------------------------------------------------------------
void interrupt_call(){ //Code hat keine Funktion
  Serial.println("Interrupt");
}
