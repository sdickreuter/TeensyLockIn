#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <U8g2lib.h>
#include <UI.h>
#include <Simpletimer.h>

const int SH1106_DC_pin = 5;
const int SH1106_CS_pin = 14;
const int SH1106_RES_pin = 9;
const int SH1106_CLK_pin = 17;
const int SH1106_DATA_pin = 3;


U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, SH1106_CS_pin, SH1106_DC_pin, SH1106_RES_pin);
//U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, SH1106_CLK_pin, SH1106_DATA_pin, SH1106_CS_pin, SH1106_DC_pin, SH1106_RES_pin);


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            linein;         //xy=103.33332824707031,114.99995422363281
AudioSynthWaveform       testwave;       //xy=103.33332824707031,205.99993896484375
AudioSynthWaveformSine   sine1; //xy=108.33332824707031,317.9999542236328
AudioSynthWaveformSine   sine2; //xy=108.33332824707031,404.9999542236328
AudioMixer4              inmixer;        //xy=293.3333282470703,101.99995422363281
AudioMixer4              testoutmixer;   //xy=365.3333740234375,563.9999389648438
AudioPlayQueue           outqueue;       //xy=414.33331298828125,451.9999084472656
AudioEffectMultiply      multiply3; //xy=494.3333282470703,278.9999542236328
AudioEffectMultiply      multiply4; //xy=495.3333282470703,162.9999542236328
AudioAmplifier           amptest;        //xy=537.3333129882812,605.9999389648438
AudioAmplifier           ampout;         //xy=573.3333129882812,496.9999084472656
AudioFilterBiquad        biquad2; //xy=662.3333282470703,311.9999542236328
AudioFilterBiquad        biquad1; //xy=667.3333282470703,165.9999542236328
AudioOutputI2S           lineout;        //xy=730.3333129882812,635.9999389648438
AudioRecordQueue         inqueue1;       //xy=828.3333282470703,166.9999542236328
AudioRecordQueue         inqueue2;       //xy=835.3333282470703,312.9999542236328
AudioConnection          patchCord1(linein, 0, inmixer, 0);
AudioConnection          patchCord2(testwave, 0, testoutmixer, 0);
AudioConnection          patchCord3(testwave, 0, inmixer, 1);
AudioConnection          patchCord4(sine1, 0, multiply4, 1);
AudioConnection          patchCord5(sine1, 0, testoutmixer, 1);
AudioConnection          patchCord6(sine2, 0, multiply3, 1);
AudioConnection          patchCord7(inmixer, 0, multiply4, 0);
AudioConnection          patchCord8(inmixer, 0, multiply3, 0);
AudioConnection          patchCord9(testoutmixer, amptest);
AudioConnection          patchCord10(outqueue, ampout);
AudioConnection          patchCord11(multiply3, biquad2);
AudioConnection          patchCord12(multiply4, biquad1);
AudioConnection          patchCord13(amptest, 0, lineout, 1);
AudioConnection          patchCord14(ampout, 0, lineout, 0);
AudioConnection          patchCord15(biquad2, inqueue2);
AudioConnection          patchCord16(biquad1, inqueue1);
// GUItool: end automatically generated code




AudioControlSGTL5000     sgtl5000_1;

NavButtons *buttons = new NavButtons();
UI *ui = new UI(buttons, &u8g2);


const int IDLE = 0;
const int RUNNING = 1;
int state = 0;
bool testmode = false;
float lockingain = 1.0;

void toggleOnOff() {
    switch(state) {
    case IDLE:
      inqueue1.clear();
      inqueue1.begin();
      inqueue2.clear();
      inqueue2.begin();
      state = RUNNING;
      break;
    case RUNNING:
      inqueue1.end();
      inqueue2.end();
      //buffer1.clear();
      //buffer2.clear();
      state = IDLE;
      break;
  }
}

void toggletest() {
    if (testmode){
      testoutmixer.gain(0,0.0);
      testoutmixer.gain(1,1.0);
      inmixer.gain(1,0.0);
      testmode = false;
    } else {
      testoutmixer.gain(0,1.0);
      testoutmixer.gain(1,0.0);
      inmixer.gain(1,1.0);
      testmode = true;
    }
}

Simpletimer timer_ui;
Simpletimer timer_blink;
Simpletimer timer_blinkfast;


void ui_callback() {
  buttons->update();
  ui->input();
  ui->draw();


  inmixer.gain(0, ui->gains_menu->ingain);
  //ampsine1.gain(ui->ref_menu->amp);
  //ampsine2.gain(ui->ref_menu->amp);
  sine1.amplitude(ui->ref_menu->amp);
  sine2.amplitude(ui->ref_menu->amp);
  sine1.frequency(ui->ref_menu->freq);
  sine2.frequency(ui->ref_menu->freq);
  //amp1.gain(multgain);
  //amp2.gain(multgain);
  amptest.gain(ui->gains_menu->outgain);
  ampout.gain(ui->gains_menu->outgain);
  lockingain = ui->gains_menu->lockingain;
}

void setup(void) {

  AudioMemory(10);

  AudioNoInterrupts();
  //Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);
  //sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);

  inmixer.gain(1,0.0);
  testwave.frequency(60);
  testwave.amplitude(0.5);
  testwave.begin(WAVEFORM_TRIANGLE);

  sine1.frequency(2000);
  sine1.amplitude(0.5);
  sine1.phase(0.0);
  sine2.frequency(2000);
  sine2.amplitude(0.5);
  sine2.phase(90.0);
  
  inmixer.gain(0,1.0);
  
  //ampsine1.gain(1.0);
  //ampsine2.gain(1.0);
  testoutmixer.gain(0,0.0);
  testoutmixer.gain(1,1.0);

  //amp1.gain(1.0);
  //amp2.gain(1.0);
  ampout.gain(1.0);

  biquad1.setLowpass(0, 500, 0.707);
  biquad2.setLowpass(0, 500, 0.707);

  delay(100);
  
  AudioInterrupts();

  ui->runbutton->set_callback(&toggleOnOff);
  ui->testbutton->set_callback(&toggletest);

  u8g2.begin();

  timer_ui.register_callback(ui_callback);
  timer_blink.register_callback(Widget::switch_blink);
  timer_blinkfast.register_callback(Widget::switch_blinkfast);

}

elapsedMillis drawtime=0;


void loop(void) {


  float lockval = 0.0;
  if ((inqueue1.available() > 1) && (inqueue2.available() > 1)) {
    int16_t* outbuf = outqueue.getBuffer();
    if (outbuf != NULL) {
      int16_t* buf1 = inqueue1.readBuffer();
      int16_t* buf2 = inqueue2.readBuffer();
      for (int i = 0;i<128;i++) {
        lockval = lockingain*sqrt(sq((float32_t)buf1[i]) + sq((float32_t)buf2[i]));
        outbuf[i] = round(lockval);
        outbuf[i] = buf1[i];
      }
      outqueue.playBuffer();
      inqueue1.freeBuffer();
      inqueue2.freeBuffer();
    }
  }
  
  timer_blink.run(500);
  timer_blinkfast.run(50);
  timer_ui.run(10);

}