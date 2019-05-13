# Project3
## ADC DMA DSP
### Project Description: 

We configure DMA to transfer samples from ADC to a buffer in memory. ADC continuously converts voltage levels into digital values. DMA is configured to transfer 256bytes of data into buffer of size 256. We have developed an application which process data simaltaneously. 

ADC: Channel0 of ADC has 16bit resolution, continuous conversion mode with hardware averaging.
DMA: Channel0 is configured to have matching source and destination size of 2bytes and it transfers 128 in one iteration of the program.
Application : It compares all the samples in buffer and finds the highest value which is called as peak. This peak value is decayed with a constant factor alpha of 0.5 until a new peak emerges. Application continuously prints out the value along with corresponding DBFS value. 


