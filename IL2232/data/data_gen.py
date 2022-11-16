import os
import math 
import numpy as np
import argparse
import csv
parser=argparse.ArgumentParser(description="Aesa input")
parser.add_argument('-o',nargs=1,type=str,metavar='PATH',default='data/Aesa_input.csv')
parser.add_argument('-n',nargs=1,type=int,metavar='NUM',default=2)
args=parser.parse_args()
AESA=dict()
AESA["fRadar"]=10e9
AESA["Wavelength"]=3e8/AESA["fRadar"]
AESA["DistanceBetweenRadarElements"]=AESA["Wavelength"]/2

AESA["NoDataChannels"]=16
AESA["NoRangeBinInEveryPulse"]=1024
AESA["NoPulsesPerFFTBatch"] = 256
AESA["DataWidthIn"] = 16
AESA["Fsampling"] = 3e6
AESA["PulseWidth"] = 1e-6
AESA["NoInCubes"] = args.n

EmptyData = list(list() for i in range(0,AESA["NoDataChannels"]))
for i in range(0,AESA["NoDataChannels"]):
    EmptyData[i] = list(list() for j in range(0,AESA["NoRangeBinInEveryPulse"]))
    for j in range(0,AESA["NoRangeBinInEveryPulse"]):
        EmptyData[i][j] = list(0 for j in range(0,AESA["NoPulsesPerFFTBatch"]))         
AESA["InputData"] = EmptyData
print(len(AESA["InputData"][1]))
def GenerateObjectReflection(AESA, Distance, Angle, RelativeSpeed, SignalPower):
    # Distance in meters
    # Relative speed i m/s, positive relative speed means approaching object
    # Angle to object, given as Theta above
    # SignalPower given as relative to the full scale power

    # wd is 2*pi*doppler frequency
    wd = 2 * math.pi * 2 * RelativeSpeed / AESA["Wavelength"]
    print(wd)
    # A is the power of the reflected signal (-5 => 1/32 of fullscale)
    A = math.pow(2,SignalPower)
   
    # Large distances will fold to lower ones, assume infinite sequences
    # Otherwise the the first X pulses would be absent
    trefl_start = math.ceil((2*Distance/3e8)*AESA["Fsampling"]) % AESA["NoRangeBinInEveryPulse"]
    trefl_stop = math.ceil((2*Distance/3e8+AESA["PulseWidth"])*AESA["Fsampling"]) % AESA["NoRangeBinInEveryPulse"]
#感觉像是开始检测到结束检测，一个发出的带宽
    print([trefl_start, trefl_stop])

    # Handling for distances at the edge of the 
    crossing_reflection = 0
    if (trefl_stop < trefl_start):
        crossing_reflection = 1
    
    # The initial phase of a full data cube will be random
    phi_start = 2*math.pi*np.random.randint(0,359)/360
    
    for PulseIt in range(0, AESA["NoPulsesPerFFTBatch"]):#256
       for RangeBinIt in range(0, AESA["NoRangeBinInEveryPulse"]):#1024
           for ChannelIt in range(0, AESA["NoDataChannels"]):#16
               ChannelDelay = -1*ChannelIt*math.pi*math.sin(Angle)
               t = (RangeBinIt + PulseIt*AESA["NoRangeBinInEveryPulse"]) / AESA["Fsampling"]
               I = A*math.cos(wd*t + phi_start)
               Q = -A*math.sin(wd*t + phi_start)
               value = (I + 1j*Q)*(math.cos(ChannelDelay) + 1j*math.sin(ChannelDelay))
              #print(A, math.sqrt(value.real*value.real + value.imag*value.imag))

                  
             
               if (RangeBinIt in range(trefl_start, trefl_stop)) and (not crossing_reflection):
                  AESA["InputData"][ChannelIt][RangeBinIt][PulseIt] = AESA["InputData"][ChannelIt][RangeBinIt][PulseIt] + value
               if not (RangeBinIt in range(trefl_start, trefl_stop)) and (crossing_reflection):
                  AESA["InputData"][ChannelIt][RangeBinIt][PulseIt] = AESA["InputData"][ChannelIt][RangeBinIt][PulseIt] + value
    print(AESA["InputData"][0][241][0])
GenerateObjectReflection(AESA, 12e3, math.pi/3 + 2*(math.pi - 2*math.pi/3)/7, 0.94, -6)
#input data的矩阵由16个数据通道，每一个数据通道由1024个range bin构成