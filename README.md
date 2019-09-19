TI MSP430 User Library
=====
A namespace-oriented wrapper library for using the TI MSP430.

This library aims to provide a more straightforward approach to working with the MSP430 MCU and its modules.
Use of `#define` is avoided where possible, instead, favoring constants and inline functions.
C++ namespaces are used to logically divide functionality and modules of the MSP430.

Building
-----
Currently, the library is compiled with GCC 9.1.0 with C++17.

The included makefile in `src` does a little work in finding the correct compiler to use.
Change MSP430PATH to the directory where MSP430 files are (bin, lib, include, etc.).
Change MSP430MCU to the MCU to compile for.

License
-----
This library is licensed under the 3-clause BSD License.
See LICENSE for more information.
