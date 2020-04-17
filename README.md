# Compress Image
[![Build Status](https://travis-ci.com/djusten/compress.svg?branch=master)](https://travis-ci.com/djusten/compress)

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
- build-essential
- cmake
- git

### Installing
1. Install Linux packages dependencies (requires sudo).
  ```bash
  sudo apt-get update && sudo apt-get install -y build-essential cmake git
  ```

### Building
1. Clone the compress repository:
  ```bash
  git clone --recursive https://github.com/djusten/compress.git
  cd ./compress
  ```

1. Create a build folder and compile:
  ```bash
  mkdir build && cd build/
  cmake ..
  make
  make test #To run unit tests
  ```

### Running
1. To run the application:
  ```bash
  ./src/compress_service
  ```
