#include <Windows.h>
#include <tchar.h>
#include "translationconsts.h"
#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H


//NOT CURRENTLY IMPLEMENTED WORK STILL IN PROGRESS
//English U.S.

//main menu bar
extern TCHAR *mainMenuStringFile_ENG;
extern TCHAR *mainMenuStringEdit_ENG;
extern TCHAR *mainMenuStringFormat_ENG;
extern TCHAR *mainMenuStringAbout_ENG;
//respective submenus
extern TCHAR *mainSubMenuFileString_ENG[6];
extern TCHAR *mainSubMenuEditString_ENG[6]; //add+2 reserve for find/rep
extern TCHAR *mainSubMenuFormatString_ENG[10];
extern TCHAR *mainSubMenuAboutString_ENG;

extern TCHAR *errorMessages_ENG[6];
extern TCHAR *warningMessages_ENG[6];

extern TCHAR *toolbarText_ENG[12];
//Russian

//main menu bar
extern TCHAR *mainMenuStringFile_RU;
extern TCHAR *mainMenuStringEdit_RU;
extern TCHAR *mainMenuStringFormat_RU;
extern TCHAR *mainMenuStringAbout_RU;
//respective sub menus
extern TCHAR *mainSubMenuFileString_RU[6];
extern TCHAR *mainSubMenuEditString_RU[6]; //add+2 reserve for find/rep
extern TCHAR *mainSubMenuFormatString_RU[10];
extern TCHAR *mainSubMenuAboutString_RU;

extern TCHAR *errorMessages_RU[6];
extern TCHAR *warningMessages_RU[6];

extern TCHAR *toolbarText_RU[12];


//Japanese (Standard)

extern TCHAR *mainMenuStringFile_JP;
extern TCHAR *mainMenuStringEdit_JP;
extern TCHAR *mainMenuStringFormat_JP;
extern TCHAR *mainMenuStringAbout_JP;
//respective sub menus
extern TCHAR *mainSubMenuFileString_JP[6];
extern TCHAR *mainSubMenuEditString_JP[6]; //add+2 reserve for find/rep
extern TCHAR *mainSubMenuFormatString_JP[10];
extern TCHAR *mainSubMenuAboutString_JP;

extern TCHAR *errorMessages_JP[6];
extern TCHAR *warningMessages_JP[6];

extern TCHAR *toolbarText_JP[12];



extern TCHAR *toolbarText_JP[12];


extern TCHAR *settingsTextGroupLabels_EN[10];
extern TCHAR *settingsTextGroupLabels_RU[10];
extern TCHAR *settingsTextGroupLabels_JP[10];

extern TCHAR *settingsTextActual_EN[20];
extern TCHAR *settingsTextActual_RU[20];
extern TCHAR *settingsTextActual_JP[20];

extern TCHAR *settingsTextWindowTitle_EN;
extern TCHAR *settingsTextWindowTitle_RU;
extern TCHAR *settingsTextWindowTitle_JP;

extern TCHAR *settingsBtns_EN[2];
extern TCHAR *settingsBtns_RU[2];
extern TCHAR *settingsBtns_JP[2];

extern TCHAR *statusControlMessages_EN[];

extern TCHAR *statusControlMessages_RU[];

extern TCHAR *statusControlMessages_JP[];


extern const TCHAR *commDlgMsgWarnInfo_EN[];
extern TCHAR *commDlgMsgWarnInfo_RU[];
extern TCHAR *commDlgMsgWarnInfo_JP[];


extern TCHAR *commDlgMsgWarnInfoCaptions_EN[];
extern TCHAR *commDlgMsgWarnInfoCaptions_RU[];
extern TCHAR *commDlgMsgWarnInfoCaptions_JP[];

extern TCHAR *commDlgMsgError_EN[];
extern TCHAR *commDlgMsgError_RU[];
extern TCHAR *commDlgMsgError_JP[];

extern TCHAR *commDlgMsgErrorCaptions_EN[];

extern TCHAR *timeStrings_EN[];
extern TCHAR *dateStrings_EN[];
extern const TCHAR *test[1];
#endif