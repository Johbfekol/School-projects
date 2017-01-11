This is a requirements specification for an effects pedal looper/switcher that has the capabilities
to switch between presets. 

* Requirement 1:
Multiple loops.
  - The system has to have multiple loops which can be switched on/off depending on the situation. The loops must be 
true bypassed when not engaged, meaning that the pedal input and output signals must be grounded. This then creates additional 
requirement for DPDT relays to be used.

* Requirement 2: Two separate loop sections.
  - This requirement comes from the need for a discrete loop for front-of-the-amp FX's as well as FX-loop FX's. This enables us to put 
  drive/distortion and boosts/modulations in front of the amp and insert time-based pedals in to the loop of the amp. 
  
* Requirement 3: Saveable presets and multiple banks. 
  - The system needs a way to store presets and have multiple banks in order to be practical. Otherwise the system would just be a simple 
  looper. This requires then a programmable logic with some sort of real-time memory. There are many SoC options to choose from for this 
  application. General requirements for those are: 
    * Easily programmable
    * Multiple I/O ports
    * Fast switching
  
  From these, we can deduce a best option for this usecase. If a discrete solution was to be made, a PIC microcontroller could be used. 
  But since easy programming is one of the requirements then Arduino is a great option. 
