# OHD-AR
this project is a replacment to an exam in a university course (Automanous robots).  
the aim of this project is to improve the OHD project and contribute to it.

## what happened
### the problem
from the first time of using openHD, a blurry and distorted image is all that appeared.  
the first thought was "it's probably a bug", let's aim to fix it.  
after learning the project's code and trying to find the source of the bug with not success.  
the proposed method was: using a arduino nano as a breakout board to read the packets from the ground and air units and compare the results.  
the conclusions from the debuging with a breakout board was: the hardware (probably the wifi modules) were defective.

### the solution
without the ability of getting new hardware, the suggested solution was: adding redundancy to the packets, and using basic hamming codes for error corection code.  
cons: 
* increaing the transmitted data by at least 2
* not very effective beyond a few meters
in small distances (up to 5 meter) it worked good, and the received image was mostly clear from errors
