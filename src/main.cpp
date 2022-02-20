#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <U8g2lib.h>
#include <UI.h>
#include <Simpletimer.h>
#include <arm_math.h>
#include <Ewma.h>

Ewma filter1(0.05);
Ewma filter2(0.05);

const int SH1106_DC_pin = 5;
const int SH1106_CS_pin = 14;
const int SH1106_RES_pin = 9;
const int SH1106_CLK_pin = 17;
const int SH1106_DATA_pin = 3;


U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, SH1106_CS_pin, SH1106_DC_pin, SH1106_RES_pin);
//U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, SH1106_CLK_pin, SH1106_DATA_pin, SH1106_CS_pin, SH1106_DC_pin, SH1106_RES_pin);


// GUItool: begin automatically generated code
AudioInputI2S            linein;           //xy=121.16667175292969,121.16667175292969
AudioPlayQueue           refoutqueue;         //xy=203.1666717529297,500.1666564941406
AudioSynthWaveform       testwave;      //xy=216.1666717529297,573.1666870117188
AudioAmplifier           ampin;           //xy=289.16668701171875,120.16666412353516
AudioRecordQueue         inqueue;         //xy=477.1666717529297,126.16667175292969
AudioPlayQueue           outqueue;         //xy=492.1666717529297,405.1666717529297
AudioMixer4              refoutmixer;         //xy=534.1666870117188,560.1666870117188
AudioAmplifier           ampout;           //xy=697.1666870117188,451.1666564941406
AudioOutputI2S           lineout;           //xy=855.1666717529297,535.1666717529297
AudioConnection          patchCord1(linein, 0, ampin, 0);
AudioConnection          patchCord2(refoutqueue, 0, refoutmixer, 0);
AudioConnection          patchCord3(testwave, 0, refoutmixer, 1);
AudioConnection          patchCord4(ampin, inqueue);
AudioConnection          patchCord5(outqueue, ampout);
AudioConnection          patchCord7(ampout, 0, lineout, 0);
AudioConnection          patchCord8(refoutmixer, 0, lineout, 1);
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
      inqueue.begin();
      state = RUNNING;
      AudioInterrupts();
      break;
    case RUNNING:
      AudioNoInterrupts();
      inqueue.end();
      inqueue.clear();
      state = IDLE;
      AudioInterrupts();
      break;
  }
}

void toggletest() {
    if (testmode){
      AudioNoInterrupts();
      refoutmixer.gain(0,1.0);
      refoutmixer.gain(1,0.0);
      testmode = false;
      AudioInterrupts();
    } else {
      AudioNoInterrupts();
      refoutmixer.gain(0,0.0);
      refoutmixer.gain(1,1.0);
      testmode = true;
      AudioInterrupts();
    }
}

Simpletimer timer_ui;
Simpletimer timer_blink;
Simpletimer timer_blinkfast;

void ui_callback() {
  timer_blink.run(500);
  timer_blinkfast.run(50);

  buttons->update();
  ui->input();
  ui->draw();

  //AudioNoInterrupts();
  ampin.gain(ui->gains_menu->ingain);
  ampout.gain(ui->gains_menu->outgain);
  lockingain = ui->gains_menu->lockingain;
  //AudioInterrupts();
  filter1.alpha = ui->filterinputbox->get_value();
  filter2.alpha = ui->filterinputbox->get_value();
}

void draw_buffer_state() {
  
  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.setCursor(86,53);
  u8g2.print("Buffers");
  u8g2.setCursor(82,64);
  u8g2.printf("%d %d %d",inqueue.available(),outqueue.available(),refoutqueue.available());

}

float randvals[AUDIO_BLOCK_SAMPLES];

void setup(void) {
  AudioMemory(10);

  AudioNoInterrupts();
  //Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);
  // https://openaudio.blogspot.com/2017/03/teensy-audio-board-self-noise.html
  sgtl5000_1.adcHighPassFilterDisable();

  ampin.gain(1.0);
  ampout.gain(1.0);

  delay(100);

  testwave.frequency(60);
  testwave.amplitude(0.1);
  testwave.begin(WAVEFORM_TRIANGLE);
  //testwave.begin(WAVEFORM_SINE);

  refoutmixer.gain(0,1.0);
  refoutmixer.gain(1,0.0);
  testmode = false;


  AudioInterrupts();

  ui->runbutton->set_callback(&toggleOnOff);
  ui->testbutton->set_callback(&toggletest);
  //ui->main->draw_callback = &draw_buffer_state;

  u8g2.begin();

  timer_ui.register_callback(ui_callback);
  timer_blink.register_callback(Widget::switch_blink);
  timer_blinkfast.register_callback(Widget::switch_blinkfast);

}

float32_t calc_sinus(float32_t* buffer, float32_t freq, float32_t phase) {
    float32_t x = phase;
    for (int i=0;i<AUDIO_BLOCK_SAMPLES;i++)
    {
      x += freq/AUDIO_SAMPLE_RATE_EXACT*TWO_PI;
      if (x > TWO_PI)
        x -= TWO_PI;
      buffer[i] = arm_sin_f32(x);
    }
    return x;
}

float32_t last_x1 = 0.0;
float32_t last_x2 = 0.0;
float32_t sin1[AUDIO_BLOCK_SAMPLES];
float32_t sin2[AUDIO_BLOCK_SAMPLES];
float32_t finput[AUDIO_BLOCK_SAMPLES];
float32_t buf1[AUDIO_BLOCK_SAMPLES];
float32_t buf2[AUDIO_BLOCK_SAMPLES];
float32_t sq1[AUDIO_BLOCK_SAMPLES];
float32_t sq2[AUDIO_BLOCK_SAMPLES];
float32_t filt1[AUDIO_BLOCK_SAMPLES];
float32_t filt2[AUDIO_BLOCK_SAMPLES];
float32_t sum[AUDIO_BLOCK_SAMPLES];
float32_t res;



void loop(void) {

  while (inqueue.available() > 0) {
    int16_t* outbuf = outqueue.getBuffer();
    if (outbuf != NULL) {
      int16_t* inbuf = inqueue.readBuffer();
      if (inbuf != NULL) {
        for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          finput[i] = ((float32_t)(inbuf[i])/32767.0)+1.0;
        }
        
        arm_scale_f32(finput,lockingain,finput,AUDIO_BLOCK_SAMPLES);

        last_x1 = calc_sinus(sin1, ui->ref_menu->freq, last_x1);
        last_x2 = calc_sinus(sin2, ui->ref_menu->freq, last_x2+(PI/2.0));
        
        arm_scale_f32(sin1,ui->ref_menu->amp,sin1,AUDIO_BLOCK_SAMPLES);
        arm_scale_f32(sin2,ui->ref_menu->amp,sin2,AUDIO_BLOCK_SAMPLES);

        int16_t* refoutbuf = refoutqueue.getBuffer();
        for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          refoutbuf[i] = (int16_t) round(sin1[i]*16384.0);
        }
        
        // mult1 = sin1 * finput
        arm_mult_f32(sin1,finput,buf1,AUDIO_BLOCK_SAMPLES);
        // mult2 = sin2 * finput
        arm_mult_f32(sin2,finput,buf2,AUDIO_BLOCK_SAMPLES);

        if (testmode) {
          
          arm_mult_f32(buf1,sin1,buf1,AUDIO_BLOCK_SAMPLES);
          arm_mult_f32(buf2,sin2,buf2,AUDIO_BLOCK_SAMPLES);
        }

        for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          filt1[i] = filter1.filter(buf1[i]);
          filt2[i] = filter2.filter(buf2[i]);
        }
        
        // buf1 = buf1^2
        arm_mult_f32(filt1,filt1,buf1,AUDIO_BLOCK_SAMPLES);
        // buf2 = buf2^2
        arm_mult_f32(filt2,filt2,buf2,AUDIO_BLOCK_SAMPLES);

        arm_add_f32(buf1,buf2,sum,AUDIO_BLOCK_SAMPLES);
        

        for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          arm_sqrt_f32(sum[i], &res);
          outbuf[i] = (int16_t) round((res-0.5)*16384.0);
        }
        inqueue.freeBuffer();
      }
    }
  }
  outqueue.playBuffer();
  refoutqueue.playBuffer();

  timer_ui.run(20);

}