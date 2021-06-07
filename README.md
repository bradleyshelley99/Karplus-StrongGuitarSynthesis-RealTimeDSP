# Karplus Strong Guitar Synthesis 

The Karplus Strong Algorithim
![image](https://github.com/bradleyshelley99/Karplus-StrongGuitarSynthesis-RealTimeDSP/KarplusStrong.png)

- The Karplus Strong Algorithim is a theoretical model to produce precise guitar string chords. A short burst of sound is pushed through a filter system that is randomly filled with white noise to achieve a precise guitar key frequency.

- A TI TMS320F2837xD Dual-Core Delfino Microcontroller C2000 Series was used for this sound generation. The audio is created syntehtically and does not require any sort of guitar sound be stored within the memory on the microcontroller to function.


The speech recognition portion of this project communicates through USART to the microcontroller.The microcontroller takes in a voice input that will play out the distinct Major Guitar Strings “C,D,E,G or A”. A 1-Dimensional Convolution is applied to determine the best correlation between the template voice inputs. The template voice inputs are created by the user as a model for the microcontroller to compare against. The best correlation will then be selected to play that chord. The microcontroller will then play said Major Guitar Chord through Karplus Strong Synthesis through the microcontroller and output said chord that will be playing to the LCD. There is an additional manual mode that plays all other Guitar string frequencies through terminal inputs.

