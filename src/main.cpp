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


// GUItool: begin automatically generated code
AudioSynthWaveform       testwave;      //xy=75.33332824707031,157.33334350585938
AudioInputI2S            linein;           //xy=78.33332824707031,82.33333587646484
AudioSynthWaveformSine   sine1;          //xy=83.33332824707031,285.33331298828125
AudioSynthWaveformSine   sine2;          //xy=83.33332824707031,372.33331298828125
AudioAmplifier           ampsine1;           //xy=257.33331298828125,282.3333435058594
AudioAmplifier           ampsine2;           //xy=264.33331298828125,371.33331298828125
AudioMixer4              inmixer;         //xy=268.33331298828125,69.33333587646484
AudioMixer4              testoutmixer;         //xy=281.33331298828125,598.3333129882812
AudioPlayQueue           outqueue;         //xy=409.33331298828125,460.3333435058594
AudioAmplifier           amptest;           //xy=457.33331298828125,609.3333129882812
AudioEffectMultiply      multiply2;      //xy=469.33331298828125,246.33334350585938
AudioEffectMultiply      multiply1;      //xy=470.33331298828125,130.33334350585938
AudioAmplifier           amp1;           //xy=566.3333282470703,53.33332824707031
AudioAmplifier           ampout;           //xy=566.3333129882812,501.3333435058594
AudioAmplifier           amp2;           //xy=572.3333282470703,363.3333282470703
AudioFilterBiquad        biquad2;        //xy=637.3333129882812,279.33331298828125
AudioFilterBiquad        biquad1;        //xy=642.3333129882812,133.33334350585938
AudioOutputI2S           lineout;           //xy=647.3333129882812,649.3333129882812
AudioRecordQueue         inqueue1;         //xy=803.3333129882812,134.33334350585938
AudioRecordQueue         inqueue2;         //xy=810.3333129882812,280.33331298828125
AudioConnection          patchCord1(testwave, 0, testoutmixer, 0);
AudioConnection          patchCord2(linein, 0, inmixer, 0);
AudioConnection          patchCord3(sine1, ampsine1);
AudioConnection          patchCord4(sine1, 0, testoutmixer, 1);
AudioConnection          patchCord5(sine2, ampsine2);
AudioConnection          patchCord6(ampsine1, 0, multiply1, 1);
AudioConnection          patchCord7(ampsine2, 0, multiply2, 1);
AudioConnection          patchCord8(inmixer, 0, multiply1, 0);
AudioConnection          patchCord9(inmixer, 0, multiply2, 0);
AudioConnection          patchCord10(testoutmixer, amptest);
AudioConnection          patchCord11(outqueue, ampout);
AudioConnection          patchCord12(amptest, 0, lineout, 1);
AudioConnection          patchCord13(multiply2, amp2);
AudioConnection          patchCord14(multiply1, amp1);
AudioConnection          patchCord15(amp1, biquad1);
AudioConnection          patchCord16(ampout, 0, lineout, 0);
AudioConnection          patchCord17(amp2, biquad2);
AudioConnection          patchCord18(biquad2, inqueue2);
AudioConnection          patchCord19(biquad1, inqueue1);
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
      AudioNoInterrupts();
      inqueue1.clear();
      inqueue1.begin();
      inqueue2.clear();
      inqueue2.begin();
      AudioInterrupts();
      state = RUNNING;
      break;
    case RUNNING:
      AudioNoInterrupts();
      inqueue1.end();
      inqueue2.end();
      //buffer1.clear();
      //buffer2.clear();
      AudioInterrupts();
      state = IDLE;
      break;
  }
}

void toggletest() {
    AudioNoInterrupts();
    if (testmode){
      testoutmixer.gain(0,0.0);
      testoutmixer.gain(1,1.0);
      testmode = false;
    } else {
      testoutmixer.gain(0,1.0);
      testoutmixer.gain(1,0.0);
      testmode = true;
    }
    AudioInterrupts();
}

Simpletimer timer_ui;

void ui_callback() {
  buttons->update();
  ui->input();
  ui->draw();
}

void setup(void) {

  AudioMemory(10);

  AudioNoInterrupts();
  //Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);
  //sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);

  inmixer.gain(1,0.0);
  testwave.frequency(120);
  testwave.amplitude(0.5);
  testwave.begin(WAVEFORM_TRIANGLE);

  sine1.frequency(2000);
  sine1.amplitude(0.5);
  sine1.phase(0.0);
  sine2.frequency(2000);
  sine2.amplitude(0.5);
  sine2.phase(90.0);
  
  inmixer.gain(0,1.0);
  
  ampsine1.gain(1.0);
  ampsine2.gain(1.0);
  testoutmixer.gain(0,0.0);
  testoutmixer.gain(1,1.0);

  amp1.gain(2.0);
  amp2.gain(2.0);
  ampout.gain(5.0);

  biquad1.setLowpass(0, 500, 0.707);
  biquad2.setLowpass(0, 500, 0.707);

  delay(100);
  
  AudioInterrupts();

  u8g2.begin();

  timer_ui.register_callback(ui_callback);
}

elapsedMillis drawtime=0;
int blink = 0;



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
      }
      outqueue.playBuffer();
      inqueue1.freeBuffer();
      inqueue2.freeBuffer();
    }
  }
  
  timer_ui.run(10);



  /*
  inmixer.gain(0, ingain);
  ampsine1.gain(sinegain);
  ampsine2.gain(sinegain);
  amp1.gain(multgain);
  amp2.gain(multgain);
  amptest.gain(outgain);
  ampout.gain(outgain);
  */

}