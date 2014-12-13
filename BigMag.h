//==============================================================================
//
// Title:       BigMag.h
// Purpose:     A short description of the interface.
//
// Created on:  9/9/2013 at 11:22:10 AM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

#ifndef __BigMag_H__
#define __BigMag_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

void InitBigMagnet(void);
void BigMagSetAmps(double amps);
void BigMagSetTesla(double tesla);
void BigMagReadS1H(void);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __BigMag_H__ */
