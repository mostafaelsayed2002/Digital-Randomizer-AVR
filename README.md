# Digital Randomizer README

## Overview

The Digital Randomizer is a digital device designed to generate random integer numbers using an ATmega328P microcontroller. The project consists of two main components: the Human-Machine Interface (HMI) MCU and the Processing MCU. The HMI MCU is connected to various components, including 7-segments, LEDs, push buttons, servo motor, and a buzzer. The Processing MCU is connected to LEDs.

## Project Components

- **2 ATmega328P microcontrollers (Arduino UNO)**
- **5 LEDs** for displaying numbers.
- **3 LEDs** to show the state of the processing MCU.
- **Buzzer** for audible feedback.
- **Servo motor** for angular feedback.
- **3 Push buttons** for rolling the Randomizer.

## Description

1. **Generating Random Numbers:**
   - Press the "Generate" push button on the HMI MCU.
   - HMI MCU sends a request to the Processing MCU to generate a random number.
   - The 1st LED connected to the processing MCU turns ON, then the 2nd LED after one second, indicating the random number is ready.
   - After one more second, the Processing MCU responds with the random number, and the 3rd LED turns on.
   - All LEDs turn off after one second.
   - If synchronization issues occur, the 3 LEDs toggle for 5 seconds (toggle every 500 ms).

2. **Displaying Random Numbers:**
   - The HMI displays the generated number in 5 digits on 5 LEDs, one digit at a time.
   - Corresponding LEDs light up for each digit in the order of appearance.
   - The buzzer releases a sound with a duty cycle based on the digit value / 10 for 5 seconds.
   - After 5 seconds, the duty cycle becomes the random number / 65535.

3. **Servo Motor Movement:**
   - The HMI moves the servo to a position (random number % 180) over a 5-second period.

4. **User Interaction:**
   - Pressing the "Next" button skips the current task and moves to the next digit quickly.
   - Pressing the "Previous" button does the same but in reverse.
   - If "Generate" is pressed before the completion of the previous task, the current task is ignored, and the new task starts immediately.

5. **State Persistence:**
   - The system's current state, including the generated random number and the current displayed digit, is saved in EEPROM.
   - Upon system reset or power cycle, the system resumes from the last saved state.

## Project Objectives
1. **Randomizer:** Develop a digital Randomizer using ATmega328P microcontrollers.
2. **Random Number Algorithm:**  Support both pseudo and real random number generation algorithms.
3. **Display:** Utilize one 7-segment display and 5 LEDs to visually represent the generated number.
4. **Audio Feedback:** Integrate a buzzer to provide audible indications with a signal bias from the potentiometer's read value.
5. **User Interaction:** Design user-friendly controls with 3 push buttons for operating the Digital Randomizer.
6. **Low Power Consumption:** Optimize the device for low power consumption to prolong battery life.


## Prototype Schematic

![Digital Randomizer Prototype](https://i.imgur.com/lNfDxfo.png)

## How to Run the Simulation

To run the simulation, you'll need Simulide. Follow these steps:
1. Download Simulide from [Simulide's official website](https://simulide.com/p/downloads/) and install it on your machine.
2. Open Simulide and load the simulation file provided: `Project.simu.sim1`.
3. Run the simulation within Simulide to observe the behavior of the digital randomizer prototype.


## Prototype Video 

[Watch the Digital Randomizer Prototype Video](https://youtu.be/1jX2jBWo9-Y) 
