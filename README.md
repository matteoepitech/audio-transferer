# Audio Transferer

Audio Transferer is a text messaging system that transmits data between computers using FSK (Frequency Shift Keying) modulation over audio. The transmitter encodes text into high-frequency audio tones, and the receiver decodes them in real-time using the Goertzel algorithm.

## How it works

- **Bit 0** → 18 kHz tone
- **Bit 1** → 19.5 kHz tone
- **Preambule** → 22.5 kHz synchronization signal
- **Bit duration** → 50 ms (~2.5 characters/second)

## Dependencies

Make sure you have these installed:

- [vcpkg](https://vcpkg.io/) – for dependency management
- [CMake](https://cmake.org/) – build system

## Build

```bash
./build.sh
```

## Usage

```bash
./build/audiotr -tx <file>
./build/audiotr -rx
```

Then choose between **transmitter** or **receiver** mode. The transmitter reads from a file and sends the content as audio. The receiver listens on the microphone and decodes the message.
