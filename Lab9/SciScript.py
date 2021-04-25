import serial
import time
import tkinter as tk
import numpy as np
import sounddevice as sd
from scipy import signal
from scipy.io.wavfile import write
import soundfile as sf
import matplotlib.pyplot as plt
import msvcrt
fs = 44100  # Sample rate
seconds = 3  # Duration of recording
sos = signal.butter(11, 6000, 'lp', fs=fs, output='sos') #Butterworth Filter for noise
def whileTrue():
    while True:
        char = msvcrt.getch()
        DSP.write(char)


DSP = serial.Serial('COM4', 9600)

# Turn Project On
DSP.write(b'a')


window = tk.Tk()
window.configure(background="gray14")
window.title("Real-Time-DSP Final Project GUI")
terminal = tk.Label(window,font = 'ariel 12',bg = 'black',fg='white',text = " Please watch terminal for instructions after buttton press")
def ModelTraining():
    print("Please prepare to model sounds for the DSP")
    print("///////////////////////////////////////////")
    def Amodel():
        terminal.configure(text ="When ready press enter to begin a countdown to record for model note 'A2' ")
        input()
        print("In 3")
        time.sleep(1)
        print("In 2")
        time.sleep(1)
        print("In 1")
        time.sleep(1)
        print("Go")
        myrecording = sd.rec(int(seconds * fs), samplerate=fs, channels=1)
        sd.wait()  # Wait until recording is finished
        myrecording = signal.sosfilt(sos, myrecording)
        myrecording = myrecording  / np.sqrt(np.sum(myrecording **2))
        write('A2model.wav', fs, myrecording)  # Save as WAV file normalized = utility.pcm2float(sig, 'float32')
        print("DONE")
        terminal.configure(text ="Ready for next button press please watch terminal after pushing button")
    def Dmodel():
        terminal.configure(text ="When ready press enter to begin a countdown to record for model note 'D3' ")
        input()
        print("In 3")
        time.sleep(1)
        print("In 2")
        time.sleep(1)
        print("In 1")
        time.sleep(1)
        print("Go")
        myrecording = sd.rec(int(seconds * fs), samplerate=fs, channels=1)
        sd.wait()  # Wait until recording is finished
        myrecording = signal.sosfilt(sos, myrecording)
        myrecording = myrecording  / np.sqrt(np.sum(myrecording **2))
        write('D3model.wav', fs, myrecording)  # Save as WAV file normalized = utility.pcm2float(sig, 'float32')
        print("DONE")
        terminal.configure(text ="Ready for next button press please watch terminal after pushing button")
    def Gmodel():
        terminal.configure(text ="When ready press enter to begin a countdown to record for model note 'G3' ")
        input()
        print("In 3")
        time.sleep(1)
        print("In 2")
        time.sleep(1)
        print("In 1")
        time.sleep(1)
        print("Go")
        myrecording = sd.rec(int(seconds * fs), samplerate=fs, channels=1)
        sd.wait()  # Wait until recording is finished
        myrecording = signal.sosfilt(sos, myrecording)
        myrecording = myrecording  / np.sqrt(np.sum(myrecording **2))
        write('G3model.wav', fs, myrecording)  # Save as WAV file normalized = utility.pcm2float(sig, 'float32')
        print("DONE")
        terminal.configure(text ="Ready for next button press please watch terminal after pushing button")
    def Bmodel():
        terminal.configure(text ="When ready press enter to begin a countdown to record for model note 'B3' ")
        input()
        print("In 3")
        time.sleep(1)
        print("In 2")
        time.sleep(1)
        print("In 1")
        time.sleep(1)
        print("Go")
        myrecording = sd.rec(int(seconds * fs), samplerate=fs, channels=1)
        sd.wait()  # Wait until recording is finished
        myrecording = signal.sosfilt(sos, myrecording)
        myrecording = myrecording  / np.sqrt(np.sum(myrecording **2))
        write('B3model.wav', fs, myrecording)  # Save as WAV file normalized = utility.pcm2float(sig, 'float32')
        print("DONE")
        terminal.configure(text ="Ready for button press")
    def Emodel():
        terminal.configure(text ="When ready press enter to begin a countdown to record for model note 'E4' ")
        input()
        print("In 3")
        time.sleep(1)
        print("In 2")
        time.sleep(1)
        print("In 1")
        time.sleep(1)
        print("Go")
        myrecording = sd.rec(int(seconds * fs), samplerate=fs, channels=1)
        sd.wait()  # Wait until recording is finished
        myrecording = signal.sosfilt(sos, myrecording)
        myrecording = myrecording  / np.sqrt(np.sum(myrecording **2))
        write('E4model.wav', fs, myrecording)  # Save as WAV file normalized = utility.pcm2float(sig, 'float32')
        print("DONE")
        terminal.configure(text ="Ready for next button press please watch terminal after pushing button")  
    def Inputmodel():
        terminal.configure(text ="When ready press enter to begin a countdown to record for guitar sound ")
        input()
        print("In 3")
        time.sleep(1)
        print("In 2")
        time.sleep(1)
        print("In 1")
        time.sleep(1)
        print("Go")
        myrecording = sd.rec(int(seconds * fs), samplerate=fs, channels=1)
        sd.wait()  # Wait until recording is finished
        myrecording = signal.sosfilt(sos, myrecording)
        myrecording = myrecording  / np.sqrt(np.sum(myrecording **2))
        write('Input.wav', fs, myrecording)  # Save as WAV file normalized = utility.pcm2float(sig, 'float32')
        print("DONE")
        terminal.configure(text ="Ready for button press")
    def ComputeInput():
        print("Reading Model Files and Input /\/\/\/\/\ ")      
        filename = 'A2model.wav'
        Amodel, fs = sf.read(filename, dtype='float32')  
        filename = 'E4model.wav'
        Emodel, fs = sf.read(filename, dtype='float32')  
        filename = 'D3model.wav'
        Dmodel, fs = sf.read(filename, dtype='float32')  
        filename = 'G3model.wav'
        Gmodel, fs = sf.read(filename, dtype='float32')  
        filename = 'B3model.wav'
        Bmodel, fs = sf.read(filename, dtype='float32')  
        filename = 'Input.wav'
        Input, fs = sf.read(filename, dtype='float32')

        print("Beginning Zero Padded Convolution")          
        ############################################
        Acorr = np.max(np.absolute(np.convolve(Amodel,Input)))
        Ecorr = np.max(np.absolute(np.convolve(Emodel,Input)))
        Dcorr = np.max(np.absolute(np.convolve(Dmodel,Input)))
        Gcorr = np.max(np.absolute(np.convolve(Gmodel,Input)))
        Bcorr = np.max(np.absolute(np.convolve(Bmodel,Input)))
        x = Acorr
        t = 'A'
        if(x < Dcorr):
            x = Dcorr
            t = 'D'
        if(x < Gcorr):
            x = Gcorr
            t = 'G'
        if(x < Bcorr):
            x = Bcorr
            t = 'B'
        if(x < Ecorr):
            x = Ecorr
            t = 'E'
        print(Acorr,Dcorr,Gcorr,Bcorr,Ecorr)
        print(f"Highest Correlation is " + t +" with a correlation of %s" % x)
        DSP.write(t.encode())
        print("DONE")
        terminal.configure(text ="Ready for next button press please watch terminal after pushing button")
        #print(DSP.read(50))
    def ManualMode():
        window.destroy()
        whileTrue()
    def quit():
            print("\n** END OF PROGRAM **")
            DSP.write(b'q')
            DSP.close()
            window.destroy()
    b1 = tk.Button(window, text="A2 model String", command=Amodel, bg="spring green", fg="gray7", font=("ariel", 20))
    b2 = tk.Button(window, text="D3 Model Guitar", command=Dmodel, bg="firebrick2", fg="gray7", font=("ariel", 20))
    b3 = tk.Button(window, text="G3 Model Program", command=Gmodel, bg="dodger blue", fg="gray7", font=("ariel", 20))
    b4 = tk.Button(window, text="B3 model Filter", command=Bmodel, bg="PaleTurquoise1", fg="gray7", font=("ariel", 20))
    b5 = tk.Button(window, text="E4 Model Quick", command=Emodel, bg="rosy brown", fg="gray7", font=("ariel", 20))
    b6 = tk.Button(window, text="Input", command=Inputmodel, bg="mint cream", fg="gray7", font=("ariel", 20))   
    b7 = tk.Button(window, text="Quit", command=quit, bg="gold", fg="gray7", font=("ariel", 20))
    b8 = tk.Button(window, text="Manual Mode", command=ManualMode, bg="light blue", fg="gray7", font=("ariel", 20))
    b9 = tk.Button(window, text="Detect Speech", command=ComputeInput, bg="salmon", fg="gray7", font=("ariel", 20))

    b1.grid(row=1, column=2, padx=5, pady=10)
    b2.grid(row=1, column=3, padx=5, pady=10)
    b3.grid(row=1, column=4, padx=5, pady=10)
    b4.grid(row=1, column=5, padx=5, pady=10)
    b5.grid(row=1, column=6, padx=5, pady=10)
    b6.grid(row=1, column=7, padx=5, pady=10)
    b7.grid(row=1, column=8, padx=5, pady=10)
    b8.grid(row=2, column=2, padx=5, pady=10)
    b9.grid(row=2, column=3, padx=5, pady=10)

    terminal.grid(row =1,column =1 , padx = 1 ,pady = 50)

    window.mainloop()
    

time.sleep(2)
ModelTraining()

