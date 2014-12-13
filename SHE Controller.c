//==============================================================================
//
// Title:       SHE Controller
// Purpose:     A short description of the application.
//
// Created on:  6/26/2012 at 3:08:59 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include <NIDAQmx.h>
#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
//#include "YOKO.h"
#include <utility.h> 
//#include "KEITHLEY_2000.h"
#include <math.h>
#include <string.h>
#include "SHE Controller.h"
#include "toolbox.h"
#include "SHE_Globals.h"
#include "2400_Mag_Control.h"
#include "lockins.h"
#include "AligentSweeper.h"
#include "Yoko.h"
#include "CNS_angle.h"
#include "BigMag.h"
#include "Keithley2k.h"

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

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
    int error = 0;
    
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (mainH = LoadPanel (0, "SHE Controller.uir", MAIN));
    
    /* display the panel and run the user interface */
    errChk (DisplayPanel (mainH));
	SetUp();
    errChk (RunUserInterface ());

Error:
    /* clean up */
    DiscardPanel (mainH);
    return 0;
}

void Debug(void)
{
	//mag_2400_init();
	//mag_2400_setv(3.14159); 
	//lockin_init(0);
	//SetCtrlVal(mainH, MAIN_DOUBLED, lockin_xvolts(0));
	
}

void SetUp(void) {
	CONFIG_CB (mainH, 0, EVENT_COMMIT,0, 0, 0); 
	MAG_SYSTEM_CB (mainH, 0, EVENT_COMMIT,0, 0, 0);
	USE_YOKO_CB (mainH, 0, EVENT_COMMIT,0, 0, 0);
	mag_2400_init(); 
	rf_init();
	GetCtrlVal(mainH, MAIN_RF_POWER, &rf.power);
	rf_set_power(rf.power);
	GetCtrlVal(mainH, MAIN_RF_FREQ, &rf.freq);
	rf_set_freq(rf.freq);
	lockin_init(0); 
	current.active=0;

	//YOKO_mA();
	YOKO_10V();
	
	
	data.collected=0;
	AllocateMemForData();
	strcpy(data.filename, "");
}

void RFFreqSweep(void)
{
	for(rf.freq = rf.freq_start; rf.freq<=rf.freq_end; rf.freq+=rf.freq_delta){
		rf_set_freq(rf.freq);
		Sweep();
		//sprintf(buff, ":SOURce:FREQuency:FIXed %fGHZ", freq);
		MakeAutoFilename();
		SaveData();
	}
}

void MakeAutoFilename(void)
{
	//Save space in the filename, use short versions of numbers if they are set to zero
	//May need to modify this by hand if doing dispersion scans with more than 0.1 GHz resolution
	if (current.now==0.0) {
		sprintf(data.filename, "%s_%.1fGHz_%.2fdBm_0mA_%.0fdeg%s", data.prefix, rf.freq/pow(10,9), rf.power, angle.set  ,".dat");		
	} else {
		sprintf(data.filename, "%s_%.1fGHz_%.2fdBm_%.2fmA_%.0fdeg%s", data.prefix, rf.freq/pow(10,9), rf.power, current.now*pow(10,3), angle.set, ".dat");	
	}
}

void RFPowerSweep(void)
{
	for(rf.power = rf.power_start; rf.power<=rf.power_end; rf.power+=rf.power_delta){
		rf_set_power(rf.power);
		Sweep();
		//sprintf(buff, ":SOURce:FREQuency:FIXed %fGHZ", freq);
		MakeAutoFilename();
		SaveData();
	}
}

void CurrentSweep(void)
{
	//for(current.now = current.start; current.now<=current.end; current.now+=current.delta){
		//rf_set_power(rf.power);
	current.now = current.start;
	YOKO_set(current.now);
	while (fabs(current.now	-current.end)>=current.delta) {
		YOKO_set(current.now); 
		Sweep();
		//sprintf(buff, ":SOURce:FREQuency:FIXed %fGHZ", freq);
		MakeAutoFilename();
		SaveData();
		current.now+=current.delta;
		//YOKO_set(current.now);	
	}
	YOKO_set(current.now); 
	Sweep();
	MakeAutoFilename();
	SaveData();
}
void AngleSweep(void)
{
	//for(current.now = current.start; current.now<=current.end; current.now+=current.delta){
		//rf_set_power(rf.power);
	angle.set = angle.start;
	CNS_set_angle();
	while (fabs(angle.set-angle.end)>=angle.delta) {
		CNS_set_angle(); 
		Sweep();
		//sprintf(buff, ":SOURce:FREQuency:FIXed %fGHZ", freq);
		MakeAutoFilename();
		SaveData();
		angle.set+=angle.delta;
		//YOKO_set(current.now);	
	}
	//angle.set=angle.end;
	CNS_set_angle();
	Sweep();
	MakeAutoFilename();
	SaveData();
}
	
	

void AllocateMemForData(void)
{
	if( ((data.tesla=malloc((NUM_POINTS)*sizeof(float/*64*/)))==NULL)		//allocate space for archive  
		||((data.volts=malloc((NUM_POINTS)*sizeof(float/*64*/)))==NULL)
		/*||((data.current=malloc((NUM_POINTS)*sizeof(float64)))==NULL)
		||((data.frequency=malloc((NUM_POINTS)*sizeof(float64)))==NULL)*/) 
	MessagePopup("Error","Not enough memory for archive of all points");	
	
}

void TakeSingle(void) 
{ //Records what's going on and adds it to the data archive
	data.tesla[data.collected] = mag.now;  
	if (experiment.whichv ==0) {
		data.volts[data.collected] = lockin_xvolts_n(0, experiment.num_samps);
		//data.current[data.collected] = 0;  //Currently saved in headers only
		//data.frequency[data.collected] = 0;  //Currently recorded in headers only
		if (experiment.use_ref==1) {
			data.volts[data.collected] /= (experiment.reference_r+experiment.device_r)/experiment.reference_r;
		}
	} else {
		data.volts[data.collected] = keithley2k_read();		
	}
	data.collected++;
	UpdateGraph();
}

void UpdateGraph(void) 
{
	if (data.collected > 1) {
	DeleteGraphPlot (mainH, MAIN_GRAPH, -1, VAL_IMMEDIATE_DRAW);
	PlotXY (mainH, MAIN_GRAPH, data.tesla, data.volts, data.collected, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_SIMPLE_DOT, VAL_SOLID, 1, VAL_BLACK);
	}
}

void ClearData(void)
{
	data.collected=0;
	DeleteGraphPlot (mainH, MAIN_GRAPH, -1, VAL_IMMEDIATE_DRAW);;
}

void Sweep(void) 	  //Now always measures while sweeping toward zero
{

	ClearData();
	mag.set=mag.start;
	SetMag();
	
	if (experiment.fancy_sweep==1) {   //Sweep from both sides to zero
		while ((fabs(mag.set)>mag.delta)&&(experiment.interrupt==0)) {
			Delay(mag.delay);
			TakeSingle();
			mag.set+=mag.delta;
			SetMag();
		}
		Delay(mag.delay);
		TakeSingle();
	
		mag.set = mag.end;
		SetMag();
	
		while ((fabs(mag.set)>mag.delta)&&(experiment.interrupt==0)) {
			Delay(mag.delay);
			TakeSingle();
			mag.set-=mag.delta;
			SetMag();
		}
	}
		
	else { //Simple sweep from start to end, mostly for big magnet
		while ((fabs(mag.end-mag.set)>mag.delta)&&(experiment.interrupt==0)) {
		Delay(mag.delay);
		TakeSingle();
		mag.set+=mag.delta;
		SetMag();
		}

	}
	Delay(mag.delay);
	TakeSingle();
	mag.set = 0;
	SetMag();
	
	if (experiment.sweep_pause==1) {
		Delay(SCAN_DELAY);
	} 
}


void SetMag(void) {
	if (mag.system==4) {
		if (experiment.interrupt==1) {
			BigMagSetTesla(0.0);
			mag.set=0;
			mag.now = 0;	
		} else {
			BigMagSetTesla(mag.set);
			mag.now = mag.set;
			SetCtrlVal(mainH, MAIN_MAG_SET, mag.now);
		}
	} 
	else {
	if (experiment.interrupt==1){
			mag.set=0;
		}
	while (fabs(mag.set-mag.now)>MAX_MAG_STEP) {
		mag.now += sign(mag.set-mag.now)*MAX_MAG_STEP;
		SetCtrlVal(mainH, MAIN_MAG_SET, mag.now);
		//YOKO_set(ProjTeslaToVolts(mag.now), mag.handle);
		mag_2400_sett(mag.now);
		
		Delay(MAG_DELAY);
		ProcessSystemEvents();
		if (experiment.interrupt==1){
			mag.set=0;
		}
	}
	ProcessSystemEvents();
	mag.now = mag.set;
	SetCtrlVal(mainH, MAIN_MAG_SET, mag.now);
	mag_2400_sett(mag.now);
	}
}

double sign(double val) {
	if (val>0) {
		return 1;
	}
	if (val<0) {
		return -1;
	}
	return 0;
}

void SaveData(void) 
{		//Needs to be changed to voltage
	int i;
	FILE *out;
	int brag;
	brag = 1;
	if (strcmp(data.filename,"")==1) {
		brag = 0;
	} else {
		FileSelectPopup (data.filename,"*.dat", "*.dat","Save data", VAL_SAVE_BUTTON, 0, 0, 1, 1, data.filename);
	}
		
	
	//if ((strcmp(data.filename,""))||(FileSelectPopup (data.filename,"*.dat", "*.dat","Save data", VAL_SAVE_BUTTON, 0, 0, 1, 1, data.filename)))
	//{
		
		
		out=fopen(data.filename,"w");
		//Print a standardized header of info
		/*fprintf(out, "%s", "---Begin Header---");
		fprintf(out, "%s%f", "\nReference resistance (Ohm) :", experiment.ref_r);
		fprintf(out, "%s%E", "\nFull scale reference sensitivity (V) :", lockins.ref_sens);		
		fprintf(out, "%s%E", "\nFull scale Vxx sensitivity (V) :", lockins.vxx_sens);
		fprintf(out, "%s%E", "\nFull scale Vxy sensitivity (V) :", lockins.vxy_sens);
		fprintf(out, "%s%i", "\nSamples per point :", experiment.num_samps);
		fprintf(out, "%s%i", "\nSample frequency (Hz) :", experiment.freq_samps);
		fprintf(out, "%s", "\n---End Header---\n\n"); */
		
		fprintf( out , "%s", "Vmix\tField\n");  // Units are volts, ohms, oersted, kelvin, amps
		for(i=1;i<data.collected;i++) 
		{
			fprintf( out , "%E%s%E%s", data.volts[i], "\t",data.tesla[i], "\n");				
		}
		fclose(out);
		if (brag==1){
		   MessagePopup ("Victory!", "Data has been saved");
		}
		strcpy(data.filename, "");
	//}
}

void RunScanFile(void)   // Reads power in DB, freq in GHz and current in mA
{
	char scanfilename[MAX_PATHNAME_LEN];
	double freq;
	double power;
	double current;
	FILE *infile;
	
	if (FileSelectPopup ("", "*.dat", "*.dat", "Choose scan file", VAL_LOAD_BUTTON, 0,0, 1,1, scanfilename)==1) {
		infile = fopen(scanfilename, "r");
		while ((fscanf(infile, "%lf %lf %lf", &freq, &power, &current)==3)&&(experiment.interrupt==0)) {
			current = current*0.001;
			freq = freq*pow(10,9); 
			SetCtrlVal(mainH, MAIN_RF_FREQ, freq);
			SetCtrlVal(mainH, MAIN_RF_POWER, power);
			SetCtrlVal(mainH, MAIN_CURRENT, current);
			//int CallCtrlCallback (int panel, int ctrl, int event, int eventData1, int eventData2, int **returnValue);
			CallCtrlCallback (mainH, MAIN_RF_POWER, EVENT_COMMIT, 0, 0, 0);
			CallCtrlCallback (mainH, MAIN_RF_FREQ, EVENT_COMMIT, 0, 0, 0);
			CallCtrlCallback (mainH, MAIN_CURRENT, EVENT_COMMIT, 0, 0, 0);
			ProcessSystemEvents();
			Delay(10);  //Let things settle
			Sweep();
			MakeAutoFilename();
			SaveData();
		}
		fclose(infile);
	}
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
        int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}
