/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2014. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  MAIN                             1       /* callback function: panelCB */
#define  MAIN_MAG_SET                     2       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_MAG_RAMP                    3       /* control type: command, callback function: MAG_RAMP_CB */
#define  MAIN_MAG_DELTA                   4       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_MAG_START                   5       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_MAG_END                     6       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_MAG_DELAY                   7       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_MAG_SWEEP                   8       /* control type: command, callback function: MAG_SWEEP_CB */
#define  MAIN_NUM_SAMPS                   9       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_INTERRUPT                   10      /* control type: textButton, callback function: INTERRUPT_CB */
#define  MAIN_GRAPH                       11      /* control type: graph, callback function: (none) */
#define  MAIN_CLEAR_DATA                  12      /* control type: command, callback function: CLEAR_DATA_CB */
#define  MAIN_SAVE                        13      /* control type: command, callback function: SAVE_CB */
#define  MAIN_RF_FREQ                     14      /* control type: numeric, callback function: RF_FREQ_CB */
#define  MAIN_RF_FREQ_START               15      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_RF_FREQ_END                 16      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_RF_FREQ_DELTA               17      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_RF_SWEEP                    18      /* control type: command, callback function: RF_SWEEP_CB */
#define  MAIN_RF_POWER                    19      /* control type: numeric, callback function: RF_POWER_CB */
#define  MAIN_RF_POWER_DELTA              20      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_RF_POWER_START              21      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_RF_POWER_END                22      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_RF_POWER_SWEEP              23      /* control type: command, callback function: RF_POWER_SWEEP_CB */
#define  MAIN_FILE_PREFIX                 24      /* control type: string, callback function: CONFIG_CB */
#define  MAIN_CURRENT                     25      /* control type: numeric, callback function: CURRENT_CB */
#define  MAIN_CURRENT_START               26      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_CURRENT_DELTA               27      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_CURRENT_END                 28      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_CURRENT_SWEEP               29      /* control type: command, callback function: CURRENT_SWEEP_CB */
#define  MAIN_AUTO_SAVE                   30      /* control type: command, callback function: AUTO_SAVE_CB */
#define  MAIN_LOOP_FROM_FILE              31      /* control type: command, callback function: LOOP_FROM_FILE_CB */
#define  MAIN_MAG_SYSTEM                  32      /* control type: ring, callback function: MAG_SYSTEM_CB */
#define  MAIN_DEVICE_R                    33      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_REFERENCE_R                 34      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_USE_REF                     35      /* control type: radioButton, callback function: CONFIG_CB */
#define  MAIN_SWEEP_PAUSE                 36      /* control type: radioButton, callback function: CONFIG_CB */
#define  MAIN_MANUAL_VOLT                 37      /* control type: numeric, callback function: MANUAL_VOLT_CB */
#define  MAIN_ANGLE_SET                   38      /* control type: numeric, callback function: ANGLE_SET_CB */
#define  MAIN_ANGLE_DELTA                 39      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_ANGLE_START                 40      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_ANGLE_END                   41      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_USE_ANGLE                   42      /* control type: radioButton, callback function: USE_ANGLE_CB */
#define  MAIN_ANGLE_SWEEP                 43      /* control type: command, callback function: ANGLE_SWEEP_CB */
#define  MAIN_MAN_USB_SET                 44      /* control type: numeric, callback function: MAN_USB_SET_CB */
#define  MAIN_READ_S1H                    45      /* control type: command, callback function: READ_S1H_CB */
#define  MAIN_USB_LAST_READ               46      /* control type: textMsg, callback function: (none) */
#define  MAIN_TEXTMSG                     47      /* control type: textMsg, callback function: (none) */
#define  MAIN_TEXTMSG_3                   48      /* control type: textMsg, callback function: (none) */
#define  MAIN_DECORATION                  49      /* control type: deco, callback function: (none) */
#define  MAIN_FANCY_SWEEP                 50      /* control type: radioButton, callback function: CONFIG_CB */
#define  MAIN_TEXTMSG_7                   51      /* control type: textMsg, callback function: (none) */
#define  MAIN_TEXTMSG_6                   52      /* control type: textMsg, callback function: (none) */
#define  MAIN_DECORATION_2                53      /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_3                54      /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_4                55      /* control type: deco, callback function: (none) */
#define  MAIN_WHICHV                      56      /* control type: ring, callback function: WHICHV_CB */
#define  MAIN_DAQ_DEBUG                   57      /* control type: numeric, callback function: (none) */
#define  MAIN_USE_YOKO                    58      /* control type: radioButton, callback function: USE_YOKO_CB */
#define  MAIN_DECORATION_5                59      /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_6                60      /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_7                61      /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_8                62      /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ANGLE_SET_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ANGLE_SWEEP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AUTO_SAVE_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CLEAR_DATA_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CONFIG_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CURRENT_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CURRENT_SWEEP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK INTERRUPT_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LOOP_FROM_FILE_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MAG_RAMP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MAG_SWEEP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MAG_SYSTEM_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MAN_USB_SET_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MANUAL_VOLT_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK READ_S1H_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RF_FREQ_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RF_POWER_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RF_POWER_SWEEP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RF_SWEEP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SAVE_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK USE_ANGLE_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK USE_YOKO_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WHICHV_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
