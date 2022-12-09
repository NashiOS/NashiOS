# Build instructions

## Prerequisites

We need some dependencies installed to be able to generate the cross compiler and emulate the system.

### Debian family

```bash
# GCC dependencies
sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo 
# Build system
sudo apt install cmake ninja-build 
# Emulator
sudo apt install qemu-system-x86
```

## Compile

### Configure build system

First we need to configure the project and generate the build system, run at the project root folder:

```bash
cmake --preset {architecture}
```

We use [CMake](https://cmake.org/) to build and configure our build system and [ninja-build](https://ninja-build.org/)
as the build system.

### Build the project

To compile NashiOS, you first need to build the toolchain by running the following command:

```bash
cmake --build --preset {architecture} --target toolchain
```

This step is only done the first time and when there are changes in critical parts of the system.

Now it's time to compile the entire system:

```bash
cmake --build --preset {architecture} --target install
```

This will compile the entire system and install the built files into the `Sysroot` directory.

## Running

With the system compiled without errors, let's run it in the [QEMU](https://www.qemu.org/) emulator:

```bash
cmake --build --preset {architecture} --target run
```

Later, when you use git pull to get the latest changes, you will again use the above commands to verify the changes.
