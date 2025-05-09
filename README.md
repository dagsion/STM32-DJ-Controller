# STM32-DJ-Controller

## Overview

video: ([https://www.youtube.com/watch?v=qGgl6kaOK0E](https://www.youtube.com/watch?v=qGgl6kaOK0E&list=PLx5INWGhzRJpzNSY4e9aSTyx2a7EL0ueM))

![IMG_3986](https://github.com/user-attachments/assets/5103f83d-ee09-452d-bb15-227b1aa6ac76)
An STM32-based DJ controller for real-time audio playback and effects. Designed for smooth performance with responsive controls.

# 🎶 Audio Playback via DAC on MCU

This project demonstrates how to convert a song into raw digital data and play it back using a DAC on a microcontroller. It includes audio conversion with Python, playback using timer interrupts, and streaming via UART with DMA for memory efficiency.

---

## 📁 Song File to C Array

To play a song on the DAC, the audio must first be digitized and embedded into the firmware.

- A **Python script** is used to convert a raw PCM audio file into a C array.
- The raw audio file is prepared in **Audacity** by trimming, resampling to **8kHz**, and exporting as **raw (unsigned 8-bit PCM)**.
- The script reads the raw binary data and outputs a `.c` file containing an `unsigned char` array of samples.

🎯 **Sample rate:** 8000 samples per second  
📦 **Bit depth:** 8-bit unsigned integers

> 🔧 This step allows the song to be compiled directly into the firmware for playback.

---

## ⏱️ DAC Playback with Timer Interrupts

Accurate timing is crucial for clean audio playback. If samples are sent to the DAC at inconsistent intervals or incorrect frequencies, the pitch and tempo will be off.

To maintain proper timing:

- A hardware **timer interrupt** is configured to trigger exactly every **125 microseconds** (8kHz).
- On each interrupt, the next sample is written to the DAC.
- Changing the **timer prescaler** adjusts the playback tempo.

This ensures the song is played back at the correct pitch and speed.

---

## 📡 UART + DMA Streaming for Large Files

Flash memory on most microcontrollers is limited, which restricts the size of audio files that can be embedded.

To overcome this:

- Audio data is **streamed over UART** from a PC in small chunks.
- A **DMA controller** buffers the incoming data.
- Playback continues smoothly while new data is received.

This allows for songs of **unlimited length**, stored on the host computer and streamed in real time.

🎥 **Demo Video:**  
[![UART DAC Streaming Demo](https://img.youtube.com/vi/2LecshdJQbs/0.jpg)]([https://www.youtube.com/watch?v=2LecshdJQbs&list=PLx5INWGhzRJpzNSY4e9aSTyx2a7EL0ueM&index=2](https://www.youtube.com/watch?v=2LecshdJQbs&list=PLx5INWGhzRJpzNSY4e9aSTyx2a7EL0ueM&index=2))

---

## Hardware & Software
- **Microcontroller:** STM32 Nucleo F446ZE
- **Audio Codec:** RAW DAC
- **Firmware:** STM32 HAL/CubeMX
- **Development Tools:** STM32CubeIDE

## Getting Started
1. Clone the repo:
   ```bash
   git clone https://github.com/dagsion/STM32-DJ-Controller.git
   ```
2. Open in STM32CubeIDE and flash firmware.
3. Connect hardware components.

## Contributions
David Xu and Osiris Xiao
