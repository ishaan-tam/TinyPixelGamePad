# TinyPixelGamePad

A tiny RP2040-powered handheld gamepad built around a custom SMD Neopixel matrix display. Designed to fit on a keychain and play simple retro-style games like Snake.

## Features
- Ultra-compact 5×5 (or 6×6) Neopixel display using 1x1mm SMD LEDs
- RP2040 microcontroller
- Custom PCB designed in KiCad
- Programmed in Arduino
- USB-C power and programming
- Built-in games: Snake, with more to come

## Preview

<img src="Images/front_assembled.jpg" width="400"/>
<img src="Images/pcb_closeup.png" width="400"/>
<img src="Images/on_keychain.jpg" width="400"/>

## Repo Structure
- `Firmware/` – Game logic and display code (Arduino)
- `Hardware/` – KiCad schematics and PCB layout
- `Images/` – Rendered images and assembly photos
- `Docs/` – Build notes, game dev instructions

## Getting Started
1. Open `Firmware/snake.ino` in the Arduino IDE
2. Select the RP2040 board and upload via USB
3. Power on and start playing 

## Pin Mapping


## Roadmap
- Add menu for game selection
- Add buzzer for sound feedback
- Add charging support for LiPo battery
- Open-source arcade game template
