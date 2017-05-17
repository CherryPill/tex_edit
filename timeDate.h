#include <Windows.h>
#include <tchar.h>
#ifndef TIMEDATE_H
#define TIMEDATE_H
//10K in hex
#define IDT_TIME_US 0x2710
#define IDT_TIME_MILITARY 0x2711

#define IDT_DATE_US 0x2712
#define IDT_DATE_EUR 0x2713
#define IDT_DATE_ISO 0x2714


void getCurrentTime(int mode);
void getCurrentDate(int mode);
void formatDateStr(WORD,WORD,WORD,int mode);
void formatTimeStr(WORD,WORD,WORD, int mode);	
void sendTimeDate2RE(TCHAR[]);
#endif