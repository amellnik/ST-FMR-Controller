
#include <gpib.h>
#include <ansi_c.h>
#include "2400_Mag_Control.h"
#include "SHE_Globals.h"
#include "SHE Controller.h"
//==============================================================================
//
// Title:       2400_Mag_Control.c
// Purpose:     A short description of the implementation.
//
// Created on:  6/26/2012 at 3:33:14 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include "2400_Mag_Control.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions



void mag_2400_init(void)	   
{
	//double initial_volts;
	mag_2400.handle = ibdev (0, KEITHLEY_ADDRESS, NO_SAD, T10s, 1, 0); 
	//char buf[30];
	
	mag.set = 0.0;
	mag.now = 0.0;
	//SetMag();
	
	ibwrt (mag_2400.handle, "*RST", strlen("*RST"));
	ibwrt (mag_2400.handle, ":SENSe:CURRent:PROTection:LEVel 1", strlen(":SENSe:CURRent:PROTection:LEVel 1"));   //set current limit to 1 A
	ibwrt (mag_2400.handle, ":SENSe:CURRent:RANGe .01", strlen(":SENSe:CURRent:RANGe .01")); 
	ibwrt (mag_2400.handle, ":OUTPut:STATe ON", strlen(":OUTPut:STATe ON"));
	ibwrt (mag_2400.handle, ":SOURce:VOLTage:LEVel:IMMediate 0", strlen(":SOURce:VOLTage:LEVel:IMMediate 0"));
	//mag.volts=0;
}

void mag_2400_setv(double volts)	 //Works
{
	char buff[255];
	sprintf(buff, ":SOURce:VOLTage:LEVel:IMMediate %f", volts);
	ibwrt (mag_2400.handle, buff, strlen(buff));	
}

void mag_2400_sett(double tesla)
{
	double volts;
	volts = mag_tesla_to_volts(tesla);
	mag_2400_setv(volts);
}

double mag_tesla_to_volts(double tesla)
{
	double k0 = 1.1;
	double k1 = 1.1;
	double k2 = 1.1;
	double k3 = 1.1;
	double k4 = 1.1;
	double k5 = 0;   // Only used for some fits, usually up to four is enough
	switch (mag.system)  {
		case 0:	   //This is for the copper or al stages with both power supplies
			//Cal on 21 June 2013

			// 12-23-13    W_coef={0.016685,28.552,-71.706,250.61,-4091.3}
  	k0	=0.058535;
  	k1	=30.167;
  	k2	=-79.392;
  	k3	=486.45;
  	k4	=-2752;
			if (tesla>0) {  //{,,,,}
			//{-0.12324,23.449,260.63,-1374.7,9139.4}
			// 12-23-13 W_coef={-0.028518,9.2201,487.06,-3266.8,14080}
k0	=-0.23783;
  	k1	=24.256;
  	k2	=217.9;
  	k3	=-782.33;
  	k4	=6652.3;
			} 
		break;
		case 1: //This is for the projected field at 45 degrees out of plane
			//{0.057656,27.008,127.07,750.06,681.1}
			k0 = 0.057656;
	 		k1 = 27.008;
	  		k2 = 127.07;
	  		k3 = 750.06;
	  		k4 = 681.1;
			if (tesla>0) {
				//{-0.039495,26.633,-120.35,708.73,-597.46}
				k0 = -0.039495;
				k1 = 26.633;
				k2 = -120.35;
				k3 = 708.73;
				k4 = -597.46;	
			}
		break;
		case 2: //This is for either the copper of al stages with only one power supply
			
			
			// Updated 16 May with rubber shims in
			// W_coef={0.28111,52.044,-275.9,-3273,-17333}
			// Updated 22 Dec .11 to 0.0 NDR:
			//   W_coef={0.029479,46.461,-402.78,-5704,-34011}
			k0	=0.029479;
  			k1	=46.461;
  			k2	=-402.78;
  			k3	=-5704;
  			k4	=-34011;
			if (tesla>0) {  
		
			//	k0	=-0.26107;
  			//	k1	=51.317;
  			//	k2	=294.14;
  			//	k3	=-3473.7;
  			//	k4	=18007;
			//	W_coef={-0.022543,13.169,1325.7,-15398,67893}   
				k0	=-0.022543;
  				k1	=13.169;
  				k2	=1325.7;
  				k3	=-15398;
  				k4	=67893;
			}
			break;
		case 3:
			// This is for the projected field with the field in-plane
			// Updated 20 May 
		
	k0	=0.028303;
  	k1	=21.947;
  	k2	=-19.75;
  	k3	=-683.41;
  	k4	=-5157.3;
  	k5	=-8295.4;
			if (tesla>0) {  
				k0	=-0.015566;
  				k1	=21.992;
  				k2	=16.435;
  				k3	=-628.42;
  				k4	=4843.2;
  				k5	=-7762.3;	
			}
			
	}
	
	if (tesla==0.0) {
		return 0;
	}
	
	double volts;
	volts = k0 + k1*tesla + k2*pow(tesla,2) + k3*pow(tesla,3) + k4*pow(tesla,4) + k5*pow(tesla,5);
	return volts;
}

double mag_2400_read_volts(void) {
	char buff[255];
	char *trash;
	ibwrt (mag_2400.handle, ":SOURce:VOLTage?", strlen(":SOURce:VOLTage?"));
	ibrd (mag_2400.handle, &buff, 255);
	return strtod(buff, &trash); 
}
