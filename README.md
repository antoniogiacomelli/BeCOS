# BeCOS
**BeCOS - Basic Extensible Card Operating System**

This work has been presented as my final paper as a partial requirement for the Software Engineering Specialist title.

It is a proof of concept for smart card operating systems. Highlights are:

* A low-coupled object-based design
* Client-server oriented
* Strict alignment with SOLID principles
* The chosen abstractions
  * A polymorphic communication channel
  * A "Program" is a set of processes scheduled based the first APDU request, that loads an application.
  * A "Process" (in the loose sense) is a co-routine aggregated to a queue.
    This is done because the filter-pipes design pattern fits well smart card applications.

The HAL is written with proxy design patterns for hardware access.
    
    
    
