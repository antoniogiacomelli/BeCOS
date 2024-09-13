# BeCOS
**BeCOS - Basic Extensible Card Operating System**

This work has been presented as my final paper as a partial requirement for the Software Engineering Specialist title.

It is a proof of concept for a extensible smart card operating systems Highlights are:

* A low-coupled object-based design
* Client-server oriented
* Strict alignment with SOLID principles
* The chosen abstractions
  1. A polymorphic communication channel - the communication to the reader is transparent to the application.
  2. A "Program" (application) is a set of processes scheduled based the on the first APDU request from the reader, to load an application. (after handshake for communication is established)
  3. A "Process" (in the loose sense) is a set of co-routines aggregated to a pipe.
  4. The command-response pattern in this domain, allows a single-thread of execution (on the unprivileged level) to be used. This aligns with stringent memory constraints.
  
  *The rationale for (ii) and (iii) is because pipes-and-filters design pattern fits well smart card applications, mainly those for access control and identification.*
  *Messages are always exchanged as a stream of bytes.*
  
The HAL is written with proxy design patterns for hardware access, providing easy portability. Note that the class Transceiver is still on the application layer, the Program class is not coupled to the hardware. A transceiver is an abstract data type, dedoupled from to the HAL by dependency inversion.
    
The PoC was deployed on an Atmega328p, 2KB RAM. 
    
![uml](https://github.com/antoniogiacomelli/BeCOS/blob/main/uml2.png)
