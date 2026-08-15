# ADR 0001: Why I chose esp32-s3-eye

## Status
Accepted

## Context
The project needs a microcontroller platform capable of running on-device
face detection and recognition, actuating a physical door lock, and later
adding networking (Wi-Fi), an I2C environmental sensor, and I2C liveness/
tailgating sensors — all with a fail-safe, offline-first design (the unlock
decision must never depend on a network call).

## Options considered

**ESP32 (original)** — the chip the project's earlier environment-monitor
plan was built around. Sufficient for I2C sensor work, but lacks the RAM/
PSRAM headroom and official AI tooling needed for on-device face recognition.

**STM32** — excellent for pure real-time/deterministic firmware work, but
has no built-in Wi-Fi/Bluetooth and no first-party on-device face-recognition
framework; would require sourcing and integrating a third-party ML pipeline
from scratch.

**Raspberry Pi Zero / Pi-class board** — plenty of compute for face
recognition, but runs full Linux rather than an RTOS, has a much slower
boot time, and shifts the project away from firmware engineering toward
embedded Linux systems work, which isn't the skill this project is built to
practice.

**ESP32-S3 (bare chip/module) + separate camera module** — technically
viable, but means sourcing and wiring a camera breakout independently and
building the ESP-WHO/ESP-DL integration without a reference board's proven
pin mapping and power design.

**ESP32-S3-EYE (chosen)** — Espressif's own purpose-built dev board for
exactly this use case: ESP32-S3 SoC, 2MP OV2640 camera, 8MB PSRAM, 8MB
flash, LCD, mic, all pre-wired and validated by the chip vendor.

## Decision
Use the ESP32-S3-EYE. It runs Espressif's own ESP-WHO/ESP-DL framework for
on-device face detection and recognition with no cloud dependency, sits on
the same ESP-IDF toolchain already validated in Milestone 0 (no environment
rework needed), and its 8MB PSRAM is load-bearing for camera frame buffers
and model weights in a way the original ESP32 could not support.

## Consequences
- **Positive:** No environment/toolchain changes needed from Milestone 0;
  camera + AI pipeline has a proven reference design instead of being wired
  from scratch; PSRAM headroom supports the recognition pipeline comfortably.
- **Negative:** Locks the project to Espressif's ESP-DL model format and
  toolchain rather than a more portable ML framework; the EYE board's fixed
  form factor and pre-wired camera position constrain physical mounting
  options for the final door-lock enclosure more than a custom camera
  placement would.
- **Revisit if:** recognition accuracy or latency (NFR-003) can't be met on
  this hardware even after optimization — at that point, a more powerful
  ESP32-S3 variant with more PSRAM, or a different platform entirely, would
  need to be re-evaluated against this same decision record.