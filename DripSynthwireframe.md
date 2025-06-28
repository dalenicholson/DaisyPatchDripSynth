```mermaid
---
title: A Physical Modeling Synth to make Drip sounds for daisy patch
config:
  theme: default
---
graph TD
   subgraph Drip [DripSynth Physical Modeling Voice]
       subgraph Dripin [Ocsillator]
         insig(Trigger)
      end
     subgraph ADSR [ADSR Envelope]
         Attack(Attack ADSR)
         Decay(Decay ADSR)
         Sustain(Sustain ADSR)
         Release(Release ADSR)
      end
      subgraph SVF [SVF Filter]
         Cutoff(Cutoff SVF)
         Resonance(Resonance SVF)
      end
      subgraph Wavefolder
         gain(Wavefolder Gain)
         offset(Wavefolder Offset)
      end
      subgraph PitchShifter
         transpose(Pitchshifter Transpose)
         fun(Pitchshifter Fun)    
      end
   end

    subgraph SM [Daisy Patch SM]
        GATE_IN_1[GATE IN 1]
        CV_1(CV 1)
        CV_2(CV 2)
        CV_3(CV 3)
        CV_4(CV 4)
        CV_5(CV 5)
        CV_6(CV 6)
        CV_7(CV 7)
        CV_8(CV 8)
        ADC_9(KNOB 1)
        ADC_10(KNOB 2)
        AUDIO_OUT_L[AUDIO OUT L]
        AUDIO_OUT_R[AUDIO OUT R]
    end



    GATE_IN_1 -->|trig in| Dripin;
    GATE_IN_1 -->|trig in| ADSR;



    CV_1 --> Attack;
    CV_2 --> Decay;
    CV_3 --> Sustain;
    CV_4 --> Release;

    CV_5 --> Cutoff;
    CV_6 --> Resonance;

    CV_7 --> gain;
    CV_8 --> offset;

    ADC_9 --> transpose;
    ADC_10 --> fun;

    Dripin -->|signal to filter| SVF;
    ADSR --> Dripin;
    SVF --> Wavefolder;
    Wavefolder --> PitchShifter;
    PitchShifter --> AUDIO_OUT_L;
    PitchShifter --> AUDIO_OUT_R;