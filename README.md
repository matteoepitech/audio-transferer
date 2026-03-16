# Audio Transferer

Audio Transferer is a text messaging system that sends data between computers using sound. The transmitter turns text into sound tones, and the receiver decodes them in real time with the Goertzel algorithm.
You will probably never manage to make it work, since these sound tones are also used in the natural world.

## How it works

- **Bit 0** → 1000 kHz sound tone
- **Bit 1** → 2000 kHz sound tone
- **Preambule** → 3000 kHz synchronization sound
- **Bit duration** → 50 ms (~2.5 characters/second)

## Dependencies

Make sure you have these installed:

- [vcpkg](https://vcpkg.io/) – for dependency management
- [CMake](https://cmake.org/) – build system

## Build

```bash
vcpkg install
./build.sh
```

## Usage

```bash
./build/soundtr -tx <file>
./build/soundtr -rx
```

Then choose between **transmitter** or **receiver** mode. The transmitter reads from a file and sends the content as sound. The receiver listens on the microphone and decodes the message.
