#include <Windows.h>
#include "globalVars.h"
#include "timeDate.h"
/*
time formats:
	AM/PM - h:m:s(AM),h:m:s(PM)
	Military - hh:mm:ss
*/
/*
date formats:
	US -> m/d/yyyy
	European -> d/m/yyyy
	ISO -> yyyy/m/d
*/
TCHAR *amStr = _T(" (AM)");
TCHAR *pmStr = _T(" (PM)");
void getCurrentTime(int mode)
{
	SYSTEMTIME currTime;
	GetLocalTime(&currTime);
	formatTimeStr(currTime.wHour,currTime.wMinute,currTime.wSecond, mode);
}
void getCurrentDate(int mode)
{
	SYSTEMTIME currDate;
	GetLocalTime(&currDate);
	formatDateStr(currDate.wMonth,currDate.wDay,currDate.wYear, mode);
}
void formatTimeStr(WORD h,WORD m,WORD s, int mode)
{
	TCHAR timeStr[256];
	TCHAR *dayNight;
	if (mode == IDT_TIME_US)
	{
		if (h > 12)
		{
			dayNight = pmStr;
		}
		else
		{
			dayNight = amStr;
		}
		h-=12;
		_stprintf(timeStr, _T("%d:%d:%d"), h, m, s);
		_tcscat(timeStr,dayNight);
	}
	else if (mode == IDT_TIME_MILITARY)
	{
		_stprintf(timeStr, _T("%d:%d:%d"), h, m, s);
	}
	sendTimeDate2RE(timeStr);
}

void formatDateStr(WORD m,WORD d,WORD y, int mode)
{
	TCHAR dateStr[256];
	if (mode==IDT_DATE_US)
	{
		_stprintf(dateStr, _T("%d/%d/%d"), m, d, y);
	}
	else if (mode==IDT_DATE_EUR)
	{
		_stprintf(dateStr, _T("%d/%d/%d"), d, m, y);
	}
	else if (mode == IDT_DATE_ISO)
	{
		_stprintf(dateStr, _T("%d/%d/%d"), y, m, d);
	}
	sendTimeDate2RE(dateStr);
}
void sendTimeDate2RE(TCHAR formattedStr[])
{
	CHARRANGE cr;
	cr.cpMin = -1;
	cr.cpMax = -1;
	SendMessage(richEditControl,EM_EXSETSEL,0,(LPARAM)&cr);
	SendMessage(richEditControl, EM_REPLACESEL, 0, (LPARAM)formattedStr);
}
