#ifndef CAMERA_H
#define CAMERA_H

#include <stdbool.h>

// Initializes the OV2640 camera on the ESP32-S3-EYE, per Espressif's
// official schematic (SCH_ESP32-S3-EYE-MB_20211201_V2.2.pdf) cross-checked
// against the widely-used CAMERA_MODEL_ESP32S3_EYE board definition.
// Control signals (XCLK/PCLK/VSYNC/HREF) confirmed from two independent
// sources; Y2-Y9 data-line bit order not independently re-verified, but
// doesn't block Milestone 1's bring-up acceptance criteria (init + single
// frame capture) -- only matters once real pixel data is being read.
bool camera_init(void);

// Captures a single frame and immediately releases it. Returns true if a
// frame was successfully captured (proving the driver + wiring work),
// regardless of pixel content correctness.
bool camera_capture_test_frame(void);

#endif