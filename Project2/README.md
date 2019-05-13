# Project2
## UART and circular buffers

### Project Description 
This project uses UART0 on FRDM KL25Z board for communicating with the user through serial terminal.
Circular buffer is interfaced to UART0 which stores the data which comes through the serial terminal.
We have developed an application which processes data inside circular buffer. It counts the number of characters 
and prints a report about the same. 

Project Features:
- Circular buffer has ability to resize, add new item, delete the oldest item, operate on multiple buffers.
- We have performed randmized unit testing on circular buffers on linux platform using CUnit framework.
- UART0 can be operated in Blocking and Nonblocking mode
