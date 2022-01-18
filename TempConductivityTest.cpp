//TempConductivityTest.cpp
//this program reads temperature and conductivity data from an AML-1 temperature / conductivity sensor

#include <stdio.h>
#include <wiringPi.h>
#include "../RemoteControlTest/AMLTempConductivity.h"


#define NUM_TC_SAMPLES 50 //NOTE: default sample rate of instrument is 25 Hz
#define SAMPLE_DELAY 500 //length of time (in ms) to pause between samples


void ShowUsage() {
	int nNumTCSamples = NUM_TC_SAMPLES;
	printf("TempConductivityTest\n");
	printf("Usage:\n");
	printf("TempConductivityTest     --> without any arguments, displays this message about how to use the program.\n");
	printf("TempConductivityTest <serial port>       --> collect %d samples of temperature and conductivity data from a sensor connected on the specified serial port. For example: TempConductivityTest /dev/ttyUSBPort3   \n",nNumTCSamples);
	printf("TempConductivityTest -h --> displays this help message.\n");
}


int main(int argc, char** argv)
{
    const int NUM_SAMPLES = NUM_TC_SAMPLES;
	if (argc < 2) {
		ShowUsage();
		return -1;
	}
	else if (strncmp(argv[1], "-h", 2) == 0 || strncmp(argv[1], "-H", 2) == 0) {//help command flag
		ShowUsage();
		return 0;
	}
	char* szSerialPort = argv[1];
	AMLTempConductivity tcSensor(szSerialPort);

	// GPIO Initialization
	if (wiringPiSetupGpio() == -1)
	{
		printf("[x_x] GPIO Initialization FAILED.\n");
		return -2;
	}
	for (int i = 0; i < NUM_SAMPLES; i++) {
		delay(SAMPLE_DELAY);
		double dTempDegC = tcSensor.GetTemperature();
		double dConductivity = tcSensor.GetConductivity();
		printf("Temp = %.3f deg C, Conductivity = %.4f mS/cm\n", dTempDegC, dConductivity);
	}
	return 0;
}