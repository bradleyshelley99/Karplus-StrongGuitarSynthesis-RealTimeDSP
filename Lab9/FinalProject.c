#include "driverlib.h"
#include "device.h"
#include <F28x_Project.h>
#include <F2837xD_Device.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include <OneToOneI2CDriver.h>
#include <LCD_Headers.h>
#include "mcbsp.h"
#include "AIC23.h"



void GPIO_INIT();
void InitSPIA();
void InitAIC23(void);
void InitMcBSPb();
void SpiTransmit(uint16_t data);
void InitUSBSCI();

Uint16 SPI_TRANSMIT(Uint16 Sdata);

interrupt void McBSPb_isr(void);
#define PI M_PI
#define SR8 0xC
#define srt 38000.0
#define freqA 196.0
#define AKey 110
#define DKey 147
#define GKey 196
#define BKey 247
#define EKey 330
#define Sr48 48000.0

#define NOTE_E2   82.41
#define NOTE_F2   87.31
#define NOTE_Fs2  92.50
#define NOTE_G2   98.00
#define NOTE_Gs2 103.82
#define NOTE_A2  110.00
#define NOTE_As2 116.54
#define NOTE_B2  123.47
#define NOTE_C3  130.81
#define NOTE_Cs3 138.59
#define NOTE_D3  146.83
#define NOTE_Ds3 155.56
#define NOTE_E3  164.81
#define NOTE_F3  174.61
#define NOTE_Fs3 185.00
#define NOTE_G3  196.00
#define NOTE_Gs3 207.65
#define NOTE_A3  220.00
#define NOTE_As3 233.08
#define NOTE_B3  246.94
#define NOTE_C4  261.63
#define NOTE_Cs4 277.18
#define NOTE_D4  293.66
#define NOTE_Ds4 311.13
#define NOTE_E4  329.63
#define NOTE_F4  349.23
#define NOTE_Fs4 369.99
#define NOTE_G4  392.00
#define NOTE_Gs4 415.30
#define NOTE_A4  440.00
#define NOTE_As4 466.16
#define NOTE_B4  493.88

int16 HAudio = 0, LAudio = 0;
int Ng = 0;

bool gucci =1, Modeling = 1, ModelRecord = 0;

// Long int for time * SR
// 5 seconds for Guitar , 2 Seconds for Audio at 8kHz
long Samples = Sr48*3.0, ModelSamples = 16000;
int pSample =0, GuitString = 0;


float Guitbuf[1024];
#pragma DATA_SECTION(Guitbuf, "ramgs0")


#define delay_5ms() for(long t =0; t<1000000;t++)



// Main Program
int main(void) {

    InitSysCtrl();      // Set SYSCLK to 200 MHz, disables watchdog timer, turns on peripheral clocks
    EALLOW;
    DINT;               // Disable CPU interrupts globally on startup
    EALLOW;
    PieVectTable.MCBSPB_RX_INT = &McBSPb_isr;
    PieCtrlRegs.PIEIER6.bit.INTx7 = 1;

    IER |= M_INT6 ;                             // Enable INT6.7 in CPU
    EnableInterrupts();                         // Enable PIE and CPU interrupts
    InitUSBSCI();

    GPIO_INIT();
    InitSPIA();
    EDIS;

    GpioDataRegs.GPASET.all= 0x0FF0;
    unsigned char receivedChar;
    volatile float x1, x2 = 0.0;





    I2C_O2O_Master_Init(0x27,200,100);
    delay_5ms();
    delay_5ms();
    LCD_Command_Clear();
    GpioDataRegs.GPATOGGLE.bit.GPIO4;
    LCD_Command_Home();
    LCD_Write("DSP ready for");
    LCD_Command_Next_Line();
    LCD_Write("Python to Start");
    receivedChar = SCI_readCharBlockingFIFO(SCIA_BASE);
    // Defaults to 48kHz on startup
    InitAIC23();
    InitMcBSPb();
    LCD_Command_Clear();
    LCD_Command_Home();
    LCD_Write("Ready for Inputs");
while (1){

    receivedChar = SCI_readCharBlockingFIFO(SCIA_BASE);

    switch(receivedChar){

        case 'A':
        case 'a':
            Ng = Sr48/NOTE_A2;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing A2 Note");
            break;
        case 'B':
        case 'b':
            Ng = Sr48/NOTE_B3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing B3 Note");
            break;
        case 'D':
        case 'd':
            Ng = Sr48/NOTE_D3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing D3 Note");
            break;
        case 'G':
        case 'g':
            Ng = Sr48/NOTE_G3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing G3 Note");
            break;
        case 'E':
        case 'e':
            Ng = Sr48/NOTE_E4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing E4 Note");
            break;
        case 'q':
            Ng = Sr48/NOTE_E2;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing E2 Note");
            break;
        case 'w':
            Ng = Sr48/NOTE_F2;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing F2 Note");
            break;
        case 'r':
            Ng = Sr48/NOTE_Fs2;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing Fs2 Note");
            break;
        case 't':
            Ng = Sr48/NOTE_G2;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing G2 Note");
            break;
        case 'y':
            Ng = Sr48/NOTE_Gs2;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing Gs2 Note");
            break;
        case 'u':
            Ng = Sr48/NOTE_As2;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing As2 Note");
            break;
        case 'i':
            Ng = Sr48/NOTE_B2;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing B2 Note");
            break;
        case 'o':
            Ng = Sr48/NOTE_C3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing C3 Note");
            break;
        case 'p':
            Ng = Sr48/NOTE_Cs3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing Cs3 Note");
            break;
        case 's':
            Ng = Sr48/NOTE_Ds3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing Ds3 Note");
            break;
        case 'f':
            Ng = Sr48/NOTE_E3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing E3 Note");
            break;
        case '1':
            Ng = Sr48/NOTE_F3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing F3 Note");
            break;
        case 'h':
            Ng = Sr48/NOTE_Fs3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing Fs3 Note");
            break;
        case 'j':
            Ng = Sr48/NOTE_Gs3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing Gs3 Note");
            break;
        case 'k':
            Ng = Sr48/NOTE_A3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing A3 Note");
            break;
        case 'l':
            Ng = Sr48/NOTE_As3;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing As3 Note");
            break;
        case 'z':
            Ng = Sr48/NOTE_C4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing C4 Note");
            break;
        case 'x':
            Ng = Sr48/NOTE_Cs4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing Cs4 Note");
            break;
        case 'c':
            Ng = Sr48/NOTE_D4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing D4 Note");
            break;
        case 'v':
            Ng = Sr48/NOTE_Ds4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing Ds4 Note");
            break;
        case 'n':
            Ng = Sr48/NOTE_F4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing F4 Note");
            break;
        case 'm':
            Ng = Sr48/NOTE_Fs4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing Fs4 Note");
            break;
        case',':
            Ng = Sr48/NOTE_G4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing G4 Note");
            break;
        case'.':
            Ng = Sr48/NOTE_Gs4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing Gs4 Note");
            break;
        case'/':
            Ng = Sr48/NOTE_A4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing A4 Note");
            break;
        case'[':
            Ng = Sr48/NOTE_As4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing As4 Note");
            break;
        case']':
            Ng = Sr48/NOTE_B4;
            Samples = Sr48*3.0;
            gucci = 1;
            Modeling = 0;
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Playing B4 Note");
            break;
        default:
            LCD_Command_Clear();
            LCD_Command_Home();
            LCD_Write("Bad Key");
              break;

        }


    }
for(;;){

}
}

interrupt void McBSPb_isr(void){
        /* Read DDR2 to get high word of channel
         * Read DDR1 to get low word of channel
         * Output High Word to DXR2
         * Output Low Word to DXR1
         *  Allow the PIE ctrl to fire again.
         *  */

        HAudio = McbspbRegs.DRR2.all;
        LAudio = McbspbRegs.DRR1.all;

     if(Modeling == 0){
// Karplus Strong Synthesis
//////////////////////////////////////////////////////////////////////
        if(gucci == 1){
            gucci = 0;
            // Long int for time * SR

          Samples = Sr48 * 3.0;
          pSample =0;
          GuitString = 0;

//       Fill in buffer to create random white noise
//       Needed for making the guitar sound.
         for (int i=Ng-1; i>=0; i--){
          volatile int rad = rand();
          Guitbuf[i] = rad * (1/(float)32767);
             }

        }

        // Decay on the component GuitString to act as a guitar should
        GuitString = Guitbuf[pSample] * (1<<(8*sizeof GuitString));
        // Because its a circular buffer need to check for previous and current sample spots
        volatile int cSample;
        if(pSample != Ng-1){
            cSample = pSample + 1;
        }
        else{
            cSample = 0;
        }

        volatile float avg = .999 * .5 * (Guitbuf[pSample] + Guitbuf[cSample]);

        Guitbuf[pSample] = avg;
        pSample = cSample;
        Samples -= 1;
        if(Samples <= 0){
            Modeling = 1;
            gucci = 1;
        }
//////////////////////////////////////////////////////////////////////
     }

        McbspbRegs.DXR1.all =  (int16) (GuitString * 30.0);
        McbspbRegs.DXR2.all =  (int16) (GuitString * 30.0);

       // end:
        // Acknowledging the interrupt so that it can fire again
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;


}

void SpiTransmit(uint16_t data)
{
    /* Transmit 16 bit data */
    SpiaRegs.SPIDAT = data; //send data to SPI register
    while(SpiaRegs.SPISTS.bit.INT_FLAG == 0); //wait until the data has been sent
    Uint16 dummyLoad = SpiaRegs.SPIRXBUF; //reset flag
}


void InitAIC23(void) {
    SmallDelay();
    uint16_t command;
    command = reset();
    SpiTransmit(command);
    SmallDelay();
    command = softpowerdown();       // Power down everything except device and clocks
    SpiTransmit(command);
    SmallDelay();
    command = linput_volctl(LIV);    // Unmute left line input and maintain default volume
    SpiTransmit(command);
    SmallDelay();
    command = rinput_volctl(RIV);    // Unmute right line input and maintain default volume
    SpiTransmit(command);
    SmallDelay();
    command = lhp_volctl(LHV);       // Left headphone volume control
    SpiTransmit(command);
    SmallDelay();
    command = rhp_volctl(RHV);       // Right headphone volume control
    SpiTransmit(command);
    SmallDelay();
    command = nomicaaudpath();      // Turn on DAC, mute mic
    SpiTransmit(command);
    SmallDelay();
    command = digaudiopath();       // Disable DAC mute, add de-emph
    SpiTransmit(command);
    SmallDelay();

    // I2S
    command = DSPdigaudinterface(); // AIC23 master mode, I2S mode,32-bit data, LRP=1 to match with XDATADLY=1
    SpiTransmit(command);
    SmallDelay();
    command = CLKsampleratecontrol (SR48);
    SpiTransmit(command);
    SmallDelay();

    command = digact();             // Activate digital interface
    SpiTransmit(command);
    SmallDelay();
    command = nomicpowerup();      // Turn everything on except Mic.
    SpiTransmit(command);
}

void InitMcBSPb()
{
    /* Init McBSPb GPIO Pins */

    //modify the GPxMUX, GPxGMUX, GPxQSEL
    //all pins should be set to asynch qualification

    /*
     * MDXB -> GPIO24
     * MDRB -> GPIO25
     * MCLKRB -> GPIO60
     * MCLKXB -> GPIO26
     * MFSRB -> GPIO61
     * MFSXB -> GPIO27
     */
    EALLOW;

    // MDXB -> GPIO24 (GPIOA)

    GpioCtrlRegs.GPAGMUX2.bit.GPIO24 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3;

    // MDRB -> GPIO25 (GPIOA)

    GpioCtrlRegs.GPAGMUX2.bit.GPIO25 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 3;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 3;

    // MFSRB -> GPIO61 (GPIOB)

    GpioCtrlRegs.GPBGMUX2.bit.GPIO61 = 0;
    GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 1;
    GpioCtrlRegs.GPBQSEL2.bit.GPIO61 = 3;

    // MFSXB -> GPIO27 (GPIOA)

    GpioCtrlRegs.GPAGMUX2.bit.GPIO27 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 3;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 3;

    // MCLKRB -> GPIO60 (GPIOB)

    GpioCtrlRegs.GPBGMUX2.bit.GPIO60 = 0;
    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 1;
    GpioCtrlRegs.GPBQSEL2.bit.GPIO60 = 3;

    // MCLKXB -> GPIO26 (GPIOA)

    GpioCtrlRegs.GPAGMUX2.bit.GPIO26 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 3;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3;
    EDIS;

    /* Init McBSPb for I2S mode */
    EALLOW;
    McbspbRegs.SPCR2.all = 0; // Reset FS generator, sample rate generator & transmitter
    McbspbRegs.SPCR1.all = 0; // Reset Receiver, Right justify word
    McbspbRegs.SPCR1.bit.RJUST = 2; // left-justify word in DRR and zero-fill LSBs
    McbspbRegs.MFFINT.all=0x0; // Disable all interrupts
    McbspbRegs.SPCR1.bit.RINTM = 0; // McBSP interrupt flag - RRDY
    McbspbRegs.SPCR2.bit.XINTM = 0; // McBSP interrupt flag - XRDY
    // Clear Receive Control Registers
    McbspbRegs.RCR2.all = 0x0;
    McbspbRegs.RCR1.all = 0x0;
    // Clear Transmit Control Registers
    McbspbRegs.XCR2.all = 0x0;
    McbspbRegs.XCR1.all = 0x0;
    // Set Receive/Transmit to 32-bit operation
    McbspbRegs.RCR2.bit.RWDLEN2 = 0;
    McbspbRegs.RCR1.bit.RWDLEN1 = 5;
    McbspbRegs.XCR2.bit.XWDLEN2 = 0;
    McbspbRegs.XCR1.bit.XWDLEN1 = 5;
    McbspbRegs.RCR2.bit.RPHASE = 0; // Dual-phase frame for receive
    McbspbRegs.RCR1.bit.RFRLEN1 = 0; // Receive frame length = 1 word in phase 1
    McbspbRegs.RCR2.bit.RFRLEN2 = 0; // Receive frame length = 1 word in phase 2
    McbspbRegs.XCR2.bit.XPHASE = 0; // Dual-phase frame for transmit
    McbspbRegs.XCR1.bit.XFRLEN1 = 0; // Transmit frame length = 1 word in phase 1
    McbspbRegs.XCR2.bit.XFRLEN2 = 0; // Transmit frame length = 1 word in phase 2
    // I2S mode: R/XDATDLY = 1 always
    McbspbRegs.RCR2.bit.RDATDLY = 0;
    McbspbRegs.XCR2.bit.XDATDLY = 0;
    // Frame Width = 1 CLKG period, CLKGDV must be 1 as slave
    McbspbRegs.SRGR1.all = 0x0001;
    McbspbRegs.PCR.all=0x0000;
    // Transmit frame synchronization is supplied by an external source via the FSX pin
    McbspbRegs.PCR.bit.FSXM = 0;
    // Receive frame synchronization is supplied by an external source via the FSR pin
    McbspbRegs.PCR.bit.FSRM = 0;
    // Select sample rate generator to be signal on MCLKR pin
    McbspbRegs.PCR.bit.SCLKME = 1;
    McbspbRegs.SRGR2.bit.CLKSM = 0;
    // Receive frame-synchronization pulses are active low - (L-channel first)
    McbspbRegs.PCR.bit.FSRP = 1;
    // Transmit frame-synchronization pulses are active low - (L-channel first)
    McbspbRegs.PCR.bit.FSXP = 1;
    // Receive data is sampled on the rising edge of MCLKR
    McbspbRegs.PCR.bit.CLKRP = 1;



    // Transmit data is sampled on the rising edge of CLKX
    McbspbRegs.PCR.bit.CLKXP = 1;



    // The transmitter gets its clock signal from MCLKX
    McbspbRegs.PCR.bit.CLKXM = 0;
    // The receiver gets its clock signal from MCLKR
    McbspbRegs.PCR.bit.CLKRM = 0;
    // Enable Receive Interrupt
    McbspbRegs.MFFINT.bit.RINT = 1;
    // Ignore unexpected frame sync
    //McbspbRegs.XCR2.bit.XFIG = 1;
    McbspbRegs.SPCR2.all |=0x00C0; // Frame sync & sample rate generators pulled out of reset
    delay_loop();
    McbspbRegs.SPCR2.bit.XRST=1; // Enable Transmitter
    McbspbRegs.SPCR1.bit.RRST=1; // Enable Receiver
    EDIS;
}




void GPIO_INIT()
        {
    // Setup for checking Test
    // If either switch is up determines the test

    // Set each DIP SW as an input and allow PUD
    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;

    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;

    GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;

}
void InitSPIA()
{
    /* Init GPIO pins for SPIA */

    //enable pullups for each pin
    //set to asynch qualification
    //configure each mux

    //SPISTEA -> GPIO19
    //SPISIMOA -> GPIO58
    //SPICLKA -> GPIO18

    EALLOW;

    //enable pullups
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;

    GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 0;
    GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 0;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO58 = 3;

    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 3;

    //asynch qual
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3;
    GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3;

    EDIS;

    /* Init SPI peripheral */
    SpiaRegs.SPICCR.all = 0x5F; //CLKPOL = 0, SOMI = SIMO (loopback), 16 bit characters
    SpiaRegs.SPICTL.all = 0x06; //master mode, enable transmissions
    SpiaRegs.SPIBRR.all = 50; //gives baud rate of approx 850 kHz

    SpiaRegs.SPICCR.bit.SPISWRESET = 1;
    SpiaRegs.SPIPRI.bit.FREE = 1;

}


void InitUSBSCI(){
    //
    // Configure PLL, disable WD, enable peripheral clocks.
    //
    //Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
   // Device_initGPIO();

    //
    // Configuration for the SCI Rx pin.
    //
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCIRXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    //
    // Configuration for the SCI Tx pin.
    //
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCITXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

    //
    // Initialize interrupt controller and vector table.
    //
    //Interrupt_initModule();
   // Interrupt_initVectorTable();

    //
    // Initialize SCIA and its FIFO.
    //
    SCI_performSoftwareReset(SCIA_BASE);

    //
    // Configure SCIA for echoback.
    //
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 9600, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));
    SCI_resetChannels(SCIA_BASE);
    SCI_resetRxFIFO(SCIA_BASE);
    SCI_resetTxFIFO(SCIA_BASE);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF | SCI_INT_RXFF);
    SCI_enableFIFO(SCIA_BASE);
    SCI_enableModule(SCIA_BASE);
    SCI_performSoftwareReset(SCIA_BASE);
}


