# SDES Implementation

This project contains a simple implementation of the Simplified DES (SDES) encryption algorithm.
**Note:** Padding is not yet implemented.

## Usage

To run the program, use one of the following flags to choose the operation mode:

- `--ecb` for Electronic Code Book mode
- `--cbc` for Cipher Block Chaining mode

You can also add the `--debug` flag to display debug messages during execution.

## Input Files

Before running, make sure to provide the required inputs inside the `data` folder:

- `key`: the encryption key
- `iv`: the initialization vector (used only in CBC mode)
- `plaintext`: the message to be encrypted