# Maze Game

A small Arduino/PlatformIO-based maze game project. This repository contains the source code, configuration, and assets used to build and run a microcontroller maze game (development and simulation done with PlatformIO and Wokwi).

## What this is

This project implements a simple maze game for embedded platforms (Arduino/PlatformIO). The main code lives in `src/` and is structured to build with PlatformIO. A `wokwi.toml` file and other project metadata are included to allow easy simulation on Wokwi.

## Features

- Simple maze logic
- PlatformIO project layout
- Wokwi simulation support

## Requirements

- PlatformIO (CLI or VS Code extension)
- A compatible Arduino board (e.g. Uno, Nano, or any board supported by the `platformio.ini` configuration)
- Optional: Wokwi (for browser-based simulation)

## Repository layout

- `game.ino` - (legacy / top-level sketch if present)
- `Maze Game/` - main PlatformIO project folder
  - `platformio.ini` - PlatformIO build configuration
  - `src/main.cpp` - main program entry
  - `include/`, `lib/` - headers and libraries
  - `wokwi.toml` - simulation config for Wokwi
- `README.md` - this file

## Build & upload (PlatformIO)

Open a terminal in the repository root and run (PowerShell / Command Prompt):

```powershell
# Build the project
pio run

# Upload to a connected board (make sure it's plugged in)
pio run -t upload

# Open the serial monitor
pio device monitor
```

If you prefer VS Code, install the PlatformIO IDE extension, open the `Maze Game` folder and use the UI buttons to build/upload/monitor.

## Run in Wokwi (simulation)

You can simulate the project in Wokwi using the included `wokwi.toml`. Open Wokwi and import the project or use the Wokwi UI to start the simulation.

## Contributing

Contributions are welcome — thanks for considering improvements! A few guidelines to make reviews faster:

- Fork the repository and create a branch for your change (feature/ or fix/ prefixes help).
- Keep PRs focused and include a short description of the problem and your solution.
- Run a local build with PlatformIO before opening a PR and include any test steps.
- For documentation or wiring changes, include images (PNG) in `Maze Game/assets/` and reference them in the README.

If you're unsure where to start, open an issue describing a bug or feature request and tag it `good first issue` if it's introductory.

## Board-specific setup (Arduino Uno example)

This section gives a minimal wiring and setup example for an Arduino Uno. Adapt pins to match `src/main.cpp` or change the constants there to match your wiring.

- Buttons: connect each momentary push-button between the chosen digital pin and GND. Use the internal INPUT_PULLUP in the sketch or add a 10k pull-up resistor.
- LEDs: connect through 220Ω resistors from digital pins to GND (or from VCC to pin if you use inverted wiring).
- Buzzer (optional): connect the positive lead to a PWM-capable digital pin through a 100Ω resistor and the negative lead to GND.

Typical example pin mapping (update `src/main.cpp` if different):

- D2: Button - Up
- D3: Button - Down
- D4: Button - Left
- D5: Button - Right
- D6: Player LED
- D7: Goal LED
- D9: Buzzer (PWM)

Wiring tips:

- Use short jumper wires for reliable button reads.
- Add small capacitors (e.g., 100nF) across noisy inputs if you see false triggers.
- If using a breadboard, keep power rails stable and use a common GND.

## Testing & debugging

- Build locally with PlatformIO: `pio run`.
- Upload and monitor serial: `pio run -t upload` then `pio device monitor`.
- If the game won't start, open the serial monitor at 115200 (or the baud rate in `src/main.cpp`) to see debug output.
- For simulation, use Wokwi: open the `Maze Game` folder in Wokwi or import the project ZIP.

## Screenshots & assets

Place images (wiring photos, screenshots) into `Maze Game/assets/` and reference them with relative links in this README or a dedicated `Maze Game/README.md` inside the PlatformIO folder.

## 📄 [License](./LICENSE.md): Proprietary – Permission Required

---

If you'd like, I can also:

- Add a `Maze Game/README.md` with board-specific diagrams and step-by-step wiring photos.
- Create a small example that maps pins to constants in `src/config.h` and adds a runtime self-test for hardware.
- Add CI (GitHub Actions) to run a simple markdown linter and PlatformIO build on PRs.
 
Tell me which of those you'd like next and I'll implement it.
