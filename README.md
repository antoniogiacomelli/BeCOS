# BeCOS
**BeCOS - Basic Extensible Card Operating System**

This work has been presented as my final paper as a partial requirement for the Software Engineering Specialist title.

It is a proof of concept for smart card operating systems. Highlights are:

* A low-coupled object-based design
* Client-server oriented
* Strict alignment with SOLID principles
* The chosen abstractions
  1. A polymorphic communication channel - the communication to the reader is transparent to the application.
  2. A "Program" (application) is a set of processes scheduled based the on the first APDU request from the reader, to load an application.
  3. A "Process" (in the loose sense) is a co-routine aggregated to a queue.
  
  *The rationale for (ii) and (iii) is because pipes-and-filters design pattern fits well smart card applications, mainly those for access control and identification.*
  
The HAL is written with proxy design patterns for hardware access, providing easy portability. 
    
    
    
