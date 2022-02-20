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



/*
// GUItool: begin automatically generated code
AudioInputI2S            linein;         //xy=103.33332824707031,114.99995422363281
AudioSynthWaveform       testwave;       //xy=103.33332824707031,205.99993896484375
AudioSynthWaveformSine   sine1; //xy=108.33332824707031,317.9999542236328
AudioSynthWaveformSine   sine2; //xy=108.33332824707031,404.9999542236328
AudioMixer4              inmixer;        //xy=293.3333282470703,101.99995422363281
AudioMixer4              testoutmixer;   //xy=365.3333740234375,563.9999389648438
AudioPlayQueue           outqueue;       //xy=414.33331298828125,451.9999084472656
AudioEffectMultiply      multiply1; //xy=494.3333282470703,278.9999542236328
AudioEffectMultiply      multiply2; //xy=495.3333282470703,162.9999542236328
AudioAmplifier           amptest;        //xy=537.3333129882812,605.9999389648438
AudioAmplifier           ampout;         //xy=573.3333129882812,496.9999084472656
AudioFilterBiquad        biquad1; //xy=667.3333282470703,165.9999542236328
AudioFilterBiquad        biquad2; //xy=662.3333282470703,311.9999542236328
AudioOutputI2S           lineout;        //xy=730.3333129882812,635.9999389648438
AudioRecordQueue         inqueue1;       //xy=828.3333282470703,166.9999542236328
AudioRecordQueue         inqueue2;       //xy=835.3333282470703,312.9999542236328
AudioConnection          patchCord1(linein, 0, inmixer, 0);
AudioConnection          patchCord2(sine1, 0, multiply1, 1);
AudioConnection          patchCord3(sine2, 0, multiply2, 1);
AudioConnection          patchCord4(inmixer, 0, multiply1, 0);
AudioConnection          patchCord5(inmixer, 0, multiply2, 0);
AudioConnection          patchCord6(multiply1, biquad1);
AudioConnection          patchCord7(multiply2, biquad2);
AudioConnection          patchCord8(biquad1, inqueue1);
AudioConnection          patchCord9(biquad2, inqueue2);
AudioConnection          patchCord10(outqueue, ampout);
AudioConnection          patchCord12(sine1, 0, testoutmixer, 1);
AudioConnection          patchCord13(testoutmixer, amptest);
AudioConnection          patchCord14(testwave, 0, testoutmixer, 0);
AudioConnection          patchCord15(testwave, 0, inmixer, 1);
AudioConnection          patchCord16(amptest, 0, lineout, 1);
AudioConnection          patchCord17(ampout, 0, lineout, 0);
// GUItool: end automatically generated code
*/


/*
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
AudioConnection          patchCord6(refoutmixer, 0, lineout, 1);
AudioConnection          patchCord7(ampout, 0, lineout, 0);
// GUItool: end automatically generated code
*/


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

}

void draw_buffer_state() {
  
  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.setCursor(86,53);
  u8g2.print("Buffers");
  u8g2.setCursor(82,64);
  u8g2.printf("%d %d %d",inqueue.available(),outqueue.available(),refoutqueue.available());

}


const int NUM_TAPS = 47;
const int state_length = NUM_TAPS + AUDIO_BLOCK_SAMPLES - 1;

// http://t-filter.engineerjs.com/, 400 Hz cutoff
float32_t firCoeffs32[NUM_TAPS] = { 
  0.003077507292576588,
  0.0011117297486932997,
  -0.00533016875949713,
  -0.00006652407404843488,
  0.004749400263903654,
  0.0038093295305040922,
  -0.006830703219073057,
  -0.006674121666725155,
  0.006546680681076068,
  0.011799819859228443,
  -0.005261470914162357,
  -0.017560496951289646,
  0.0010399076331204155,
  0.024290370336453506,
  0.006812935620559314,
  -0.031093222851880542,
  -0.02042762411930543,
  0.03745058299050936,
  0.044055234306168936,
  -0.042591300656463105,
  -0.09360562569928207,
  0.04595801878847091,
  0.31401362942163463,
  0.4528747467752534,
  0.31401362942163463,
  0.04595801878847091,
  -0.09360562569928207,
  -0.042591300656463105,
  0.044055234306168936,
  0.03745058299050936,
  -0.02042762411930543,
  -0.031093222851880542,
  0.006812935620559314,
  0.024290370336453506,
  0.0010399076331204155,
  -0.017560496951289646,
  -0.005261470914162357,
  0.011799819859228443,
  0.006546680681076068,
  -0.006674121666725155,
  -0.006830703219073057,
  0.0038093295305040922,
  0.004749400263903654,
  -0.00006652407404843488,
  -0.00533016875949713,
  0.0011117297486932997,
  0.003077507292576588
};


arm_fir_instance_f32  fir1;
float fir1_state[state_length];
arm_fir_instance_f32  fir2;
float fir2_state[state_length];


void setup(void) {
  //float coeffs[NUM_TAPS] = {1.0,0.8,0.5,0.2,0.1};

  arm_fir_init_f32(&fir1, NUM_TAPS, firCoeffs32, fir1_state, AUDIO_BLOCK_SAMPLES);
  arm_fir_init_f32(&fir2, NUM_TAPS, firCoeffs32, fir2_state, AUDIO_BLOCK_SAMPLES);

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
  testwave.amplitude(0.25);
  testwave.begin(WAVEFORM_TRIANGLE);
  //testwave.begin(WAVEFORM_SINE);

  refoutmixer.gain(0,1.0);
  refoutmixer.gain(1,0.0);
  testmode = false;


  AudioInterrupts();

  ui->runbutton->set_callback(&toggleOnOff);
  ui->testbutton->set_callback(&toggletest);
  ui->main->draw_callback = &draw_buffer_state;

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
        
        /*for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          outbuf[i] = (int16_t) round(buf1[i]*lockingain*1.0);
        }*/

        //arm_fir_f32(&fir1,buf1,filt1,AUDIO_BLOCK_SAMPLES);
        //arm_fir_f32(&fir2,buf2,filt2,AUDIO_BLOCK_SAMPLES);
        /*for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          outbuf[i] = (int16_t) round(filt1[i]*lockingain*1.0);
        }*/


        for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          filt1[i] = filter1.filter(buf1[i]);
          filt2[i] = filter2.filter(buf2[i]);
        }
        /*for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          outbuf[i] = (int16_t) round(filt1[i]*lockingain*1.0);
          //outbuf[i] = filter1.filter(buf1[i]);
        }*/

        /*for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          filt1[i] = (buf[i] - last1)*filtcoef + last1; 
          last1 = filt1[i];
          filt1[i] = (buf[i] - last1)*filtcoef + last2; 
          last1 = filt1[i];
        }*/

        /*for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          filt1[i] = (last1 - buf1[i])*0.1 + last1; 
          last1 = filt1[i];
          outbuf[i] = (int16_t) round(filt1[i]*lockingain);
        }*/
        
        
        // buf1 = buf1^2
        arm_mult_f32(filt1,filt1,buf1,AUDIO_BLOCK_SAMPLES);
        // buf2 = buf2^2
        arm_mult_f32(filt2,filt2,buf2,AUDIO_BLOCK_SAMPLES);

        arm_add_f32(buf1,buf2,sum,AUDIO_BLOCK_SAMPLES);
        

        for (int i = 0;i<AUDIO_BLOCK_SAMPLES;i++) {
          //arm_sqrt_f32(sq(filt1[i]) + sq(filt2[i]), &res);
          arm_sqrt_f32(sum[i], &res);
          //res = filt2[i];
          outbuf[i] = (int16_t) round(res*lockingain*16384.0);
        }
        inqueue.freeBuffer();
      }
    }
  }
  outqueue.playBuffer();
  refoutqueue.playBuffer();

  timer_ui.run(20);

}