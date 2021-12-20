#include <FastLED.h>
#include <IRremote.h>

#define IR_PIN 2
#define nump 100
#define PIN 3
#define LED_PIN 12
#define MAX_B 160
#define MIN_B 0
#define MIN_TO_CHANGE 1 
#define COLPAL 4

#define BUTT_UP     0xFF629D
#define BUTT_DOWN   0xFFA857
#define BUTT_LEFT   0xFF22DD
#define BUTT_RIGHT  0xFFC23D
#define BUTT_OK     0xFF02FD
#define BUTT_1      0xFF6897
#define BUTT_2      0xFF9867
#define BUTT_3      0xFFB04F
#define BUTT_4      0xFF30CF
#define BUTT_5      0xFF18E7
#define BUTT_6      0xFF7A85
#define BUTT_7      0xFF10EF
#define BUTT_8      0xFF38C7
#define BUTT_9      0xFF5AA5
#define BUTT_0      0xFF4AB5
#define BUTT_STAR   0xFF42BD
#define BUTT_HASH   0xFF52AD
#define PUSHED      0xFFFFFF
//*******************************************************************
CRGB leds[nump];
IRrecv irrecv(IR_PIN);
decode_results res;
//*******************************************************************
volatile byte type = 1;
volatile bool ok = false;//not ok
volatile byte slujeb = NULL;
byte currentPal = 2;

byte t1 = 0;
uint32_t t = 0;
uint8_t b = 80;
byte colorIndex[nump];
//************************-PALETTES-********************************
CRGBPalette16 purplePalette = CRGBPalette16 (
CRGB::DarkViolet,
CRGB::DarkViolet,
CRGB::DarkViolet,
CRGB::DarkViolet,
CRGB::Magenta,
CRGB::Magenta,
CRGB::Linen,
CRGB::Linen,
CRGB::Magenta,
CRGB::Magenta,
CRGB::DarkViolet,
CRGB::DarkViolet,
CRGB::DarkViolet,
CRGB::DarkViolet,
CRGB::Linen,
CRGB::Linen
);
DEFINE_GRADIENT_PALETTE(greenmap_p) {
  0, 0, 255, 0,
  80, 26, 175, 50,
  141, 16, 200, 100,
  160, 10, 255, 0,
  255, 0, 255, 0
};
DEFINE_GRADIENT_PALETTE(burn_p) {
  0, 255, 0, 0,
  80, 240, 30, 0,
  81, 230, 30, 10,
  131, 240, 200, 0,
  141, 200, 200, 0,
  148, 240, 30, 30,
  161, 240, 200, 0,
  255, 255, 0, 0
};
CHSVPalette16 special = CHSVPalette16(
  CHSV(1, 0, 0),
  CHSV(1, 255, 255),
  CHSV(0, 255, 100),
  CHSV(0, 0, 0),
  CHSV(0, 0, 0),
  CHSV(96, 255, 255),
  CHSV(96, 255, 100),
  CHSV(0, 0, 0),
  CHSV(0, 0, 0),
  CHSV(160, 255, 255),
  CHSV(160, 255, 100),
  CHSV(0, 0, 0),
  CHSV(0, 0, 0),
  CHSV(40, 255, 255),
  CHSV(40, 255, 100),
  CHSV(0, 0, 0)
);
CRGBPalette16 myPal = burn_p;
//*******************************************************************
void setup() {
  irrecv.enableIRIn();
  attachInterrupt(0, IRcheck, CHANGE);
  FastLED.addLeds<WS2811, PIN, RGB>(leds, nump);
  FastLED.setBrightness(b);
  FastLED.clear();
  pinMode(LED_PIN, OUTPUT);
  for (int i = 0; i < nump; i++) {
    colorIndex[i] = random8();
  }
}
//*******************************************************************
volatile byte kod;
void IRcheck(){ 
  
  if(irrecv.decode(&res)){
    
    if(res.value == PUSHED || res.value == 0){
      switch(kod){
        case 1:   slujeb = 1;  break;
        case 2:   slujeb = 2;  break;
        case 3:   slujeb = 3;  break;
        case 4:   slujeb = 4;  break;
        case 5:   ok = !ok;    break;
        case 6:   type = 1;    break;
        case 7:   type = 2;    break;
        case 8:   type = 3;    break;
        case 9:   type = 4;    break;
        case 10:  type = 5;    break;
        case 11:  type = 6;    break;
        case 12:  type = 7;    break;
        case 13:  type = 8;    break;
        case 14:  type = 9;    break;
        case 15:  type = 0;    break;
        case 16:               break;//#
        case 17:               break;//*
        };
        return 0;
        
    };
    
    switch(res.value){
      
      case BUTT_UP:     slujeb = 1; kod = 1; break;
      case BUTT_RIGHT:  slujeb = 2; kod = 2; break;
      case BUTT_DOWN:   slujeb = 3; kod = 3; break;
      case BUTT_LEFT:   slujeb = 4; kod = 4; break;
      case BUTT_OK:     ok = !ok;   kod = 5; break;
      case BUTT_1:      type = 1;   kod = 6; break;
      case BUTT_2:      type = 2;   kod = 7; break;
      case BUTT_3:      type = 3;   kod = 8; break;
      case BUTT_4:      type = 4;   kod = 9; break;
      case BUTT_5:      type = 5;   kod = 10; break;
      case BUTT_6:      type = 6;   kod = 11; break;
      case BUTT_7:      type = 7;   kod = 12; break;
      case BUTT_8:      type = 8;   kod = 13; break;
      case BUTT_9:      type = 9;   kod = 14; break;
      case BUTT_0:      type = 0;   kod = 15; break;
      case BUTT_HASH:               kod = 16; break;//#
      case BUTT_STAR:               kod = 17; break;//*
      
    };
    irrecv.resume();
  }
}
//****************************LOOP**********************************
void loop(){
  t = millis() / 5;
  leds[nump - 1] = CRGB(255, 0, 0);
  if(irrecv.isIdle()){
    changeType();
    switcher();
    if(slujeb != NULL){
      changePalTo();
      options();
    }
  }
}
//******************************************************************
void changeType(){
  switch(type){
    case 1: type1(); break;
    case 2: type2(); break;
    case 3: type3(); break;
    case 4: type4(); break;
    //case 5: type5(); break;
    //case 6: type6(); break;
    //case 7: type7(); break;
    //case 8: type8(); break;
    //case 9: type9(); break;
    case 0: off();   break;
  }
}
void switcher(){
  if(ok == true){
    digitalWrite(LED_PIN, HIGH);
    if(millis() / 60000 - t1 >= MIN_TO_CHANGE){
      t1 = millis() / 60000;
      type = type <= 9 ? type ++ : type = 1;
    }
  }else{
    digitalWrite(LED_PIN, LOW);
  }
}
void options(){
  switch(slujeb){
    case 1: b = b < MAX_B ? b += 5 : b = MAX_B; FastLED.setBrightness(b); break;
    case 3: b = b > MIN_B ? b -= 5 : b = MIN_B; FastLED.setBrightness(b); break;
    case 2: currentPal++;break;//change pal
    case 4: currentPal--;break;
  }
  FastLED.show();
  slujeb = NULL;
}
void changePalTo(){
  if(currentPal > COLPAL - 1){
    currentPal = 0;
  }else if(currentPal < 0){
    currentPal = COLPAL - 1;
  }
  switch(currentPal){
    case 0: myPal = purplePalette; break;
    case 1: myPal = greenmap_p; break;
    case 2: myPal = burn_p; break;
    case 3: myPal = special; break;
  }
}
//****************************************************************
void off(){
  FastLED.clear();
  FastLED.show();
}
void type1() {
    static int scale = beatsin8(0, 10, 30);
    for (byte i = 0; i < nump - 1; i++) {
      byte noise = inoise8(i * scale, t);
      byte h = map(noise, 50, 190, 0, 255);
      leds[i] = CHSV(h, 199, 135);
    }
    FastLED.show();
}
void type2() {
  EVERY_N_MILLISECONDS(40) {
    leds[random8(0, nump - 1)] = ColorFromPalette(myPal, random8(), b, LINEARBLEND);
  };
  fadeToBlackBy(leds, nump, 1);
  FastLED.show();
}
void type3() {
  static byte palIndex = 0;
  fill_palette(leds, nump - 1, palIndex, 100 / nump, myPal, b, LINEARBLEND);

  EVERY_N_MILLISECONDS(15) {
    palIndex++;
  }
  FastLED.show();
}

void type4() {
  for (byte i = 0; i < nump - 1; i++) {
    leds[i] = ColorFromPalette(myPal, colorIndex[i]);
  }
  EVERY_N_MILLISECONDS(5){
    for (int i = 0; i < nump; i++) {
      colorIndex[i]++;
    }
  }
  FastLED.show();
}
