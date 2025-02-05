Directory guide: FTDI_Library
--------------------------
Brief description

Directory contains files which are needed for FTDI 232H
to work properly in telemetry system.

--------------------------
File details

File structure (on abstract level) is like this:

ftd2xx.h -- WinTypes (lower layer)
    |
    |
libMPSSE
    |
    |
libMPSSE_spi         (higher layer)



- libMPSSE_spi.h

This file contains SPI library for FTDI device.

- libMPSSE.a, libMPSSE.dll, libMPSSE.lib

These files are necessary to use 
libMPSSE_spi.h . The libMPSSE_spi.h to work, use functions declared in 3
above mentioned files.

The .a file is compiled library.
The .lib file is static part of library.
The .dll file is dynamic part of library.

- ftd2xx.h

Is a header file of FTDI low-level driver

- WinTypes.h

This header file contain all data types declarations for ftd2xx library.

