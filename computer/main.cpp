#define _CRT_SECURE_NO_WARNINGS
#include <string> 

/*!
 \file      Example1.cpp

 \brief     Example code source for class serialib.
			This example open the device on ttyACM0.
			(USB to RS232 converter under linux).
			If the opening is successful, it sends the AT command
			and waits for a string being received from the device.
			After 5 seconds, if no valid data are received from the
			device, reception is giving up.

 \author    Philippe Lucidarme (University of Angers) <serialib@googlegroups.com>
 \version   1.2
 \date      05/01/2011
 */

#include <stdio.h>
#include "serialib.h"
#include <iostream>


#if defined (_WIN32) || defined( _WIN64)
#define         DEVICE_PORT             "COM4"                               // COM1 for windows
#define _CRT_SECURE_NO_WARNINGS

#endif

#ifdef __linux__
#define         DEVICE_PORT             "/dev/ttyS0"                         // ttyS0 for linux

#endif


int main()
{
	serialib LS;                                                            // Object of the serialib class
	int Ret; // Used for return values
	char Buffer[32];
	char in[32];
	// Open serial port

	Ret = LS.Open(DEVICE_PORT, 9600);                                        // Open serial link at 9600 bauds
	if (Ret != 1) {                                                           // If an error occured...
		printf("Error while opening port. Permission problem ?\n");        // ... display a message ...
		return Ret;                                                         // ... quit the application
	}
	printf("Serial port opened successfully !\n");
	// Write the AT command on the serial port
	printf("Sending data!\n");
	float test = -1;
	while (test <= 1) {
		sprintf(Buffer, "%f", test);
		printf("Data sent: %s         ", Buffer);
		Ret = LS.WriteString(Buffer);
		Ret = LS.ReadString(in, '>', 1000);                                // Read a maximum of 128 characters with a timeout of 5 seconds
																		   // The final character of the string must be a line feed ('\n')
		if (Ret > 0) {                                                             // If a string has been read from, print the string
			float received = atof(in);
			printf("Error In  : %f \n", received);
		}
		else {
			printf("TimeOut reached. No data received !\n");
		}
		Sleep(500);
		test += 0.05;
		
	}
	
	/*if (Ret != 1) {                                                           // If the writting operation failed ...
		printf("Error while writing data\n");                              // ... display a message ...
	                                           // Send the command on the serial port
		return Ret;                                                         // ... quit the application.
	}
	printf("Write operation 1 is successful \n"); */
	
	 /*
	 //Read a string from the serial device
	  Ret = LS.ReadString(Buffer,'>',1000);                                // Read a maximum of 128 characters with a timeout of 5 seconds
																			// The final character of the string must be a line feed ('\n')
	if (Ret > 0) {                                                             // If a string has been read from, print the string
		float received = atof(Buffer);
		printf("\nMotor speed right : %f", received);
	}
	else {
		printf("TimeOut reached. No data received !\n");
	}              
	*/
	// Close the connection with the device
	LS.Close();

	return 0;
}


