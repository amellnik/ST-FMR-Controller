//==============================================================================
//
// Title:       BigMag.c
// Purpose:     A short description of the implementation.
//
// Created on:  9/9/2013 at 11:22:10 AM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <utility.h>
#include <ansi_c.h>
#include <userint.h>
#include "BigMag.h"
#include <rs232.h>
#include "SHE Controller.h"
#include "SHE_Globals.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static int COMPORT = 4;
//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions



void InitBigMagnet(void) {		        //2? 
	OpenComConfig (COMPORT, "COM4", 9600, 0, 8, 1, 0, 0);	   //Last two are default values
	SetComTime (COMPORT, 0.5);
	FlushInQ (COMPORT);
	
	//test write
	BigMagReadS1H();
	
	BigMagSetAmps(0.0);
	
	//Turn on supply
	char buf[100];
	char retbuf[100];
	sprintf(buf, "%s%s", "N", "\r");
	ComWrt (COMPORT, buf, strlen(buf));
	ComRdTerm (COMPORT, retbuf, 100, 13);		//13=CR
	SetCtrlVal(mainH, MAIN_USB_LAST_READ, retbuf);
	sprintf(buf, "%s%s", "NASW", "\r");	   
	ComWrt (COMPORT, buf, strlen(buf));   
	FlushInQ (COMPORT);
}

void BigMagSetAmps(double amps) {
	//self.setCurrentPPM(int((1e6/160)*amps))
	//self.write("DA 0,%d" % int(ppm))
	if (amps<=0.0) {
		amps = 0.0;	
	}
	SetCtrlVal(mainH, MAIN_MAN_USB_SET, amps); 
	char retbuf[100];  
	char buf[100]; 
	int status = 400003;
	SetCtrlVal(mainH, MAIN_DAQ_DEBUG, amps);
	amps *= 1000000/160;
	int val = (int) amps;
	//Write value
	
	sprintf(buf, "%s%u%s", "DA 0,",val, "\r");
	ComWrt (COMPORT, buf, strlen(buf));
	FlushInQ (COMPORT); 
	//Clear results
	ProcessSystemEvents(); 
	FlushInQ (COMPORT);
	
	//Ask for status and read result
	while (status==400003) {
		sprintf(buf, "%s%s", "S1H", "\r");
		FlushInQ (COMPORT); 
		ComWrt (COMPORT, buf, strlen(buf)); 	
		ComRdTerm (COMPORT, retbuf, 100, 13);		//13=CR
		//status = atoi(retbuf);  // its possible atoi is the problem I have 
		sscanf(retbuf, "%d",  &status);
		SetCtrlVal(mainH, MAIN_USB_LAST_READ, retbuf);
		Delay (0.2);
		ProcessSystemEvents();
	}
	
	
	
}

void BigMagSetTesla(double tesla) {
  //old W_coef={-0.056003,85.245,2.1904,-4.6395,3.6965}	
 // new W_coef={0.31412,74.011,51.734,-72.812,32.749}
	double k0 = 0.31412;
	double k1 = 74.011;
	double k2 = 51.734;
	double k3 = -72.812;
	double k4 = 32.749;
	double amps = k0 + k1*tesla + k2*pow(tesla,2) + k3*pow(tesla,3) + k4*pow(tesla,4);
	amps = fabs(amps);
	BigMagSetAmps(amps);
}


void BigMagReadS1H(void) {
	char buf[100]; 
	sprintf(buf, "%s%s", "S1H", "\r");
	ComWrt (COMPORT, buf, strlen(buf)); 	
	char retbuf[100];
	ComRdTerm (COMPORT, retbuf, 100, 13);		//13=CR
	SetCtrlVal(mainH, MAIN_USB_LAST_READ, retbuf);
}
