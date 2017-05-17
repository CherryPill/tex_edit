#include <windows.h>
#include <tchar.h>
#include <string>
#ifndef APPCONST_H
#define APPCONST_H

//app name
extern HICON mainAppIcon;
extern HICON appSetsIcon;
extern TCHAR *szConfigPath;
extern TCHAR *szRecentFilesPath;
extern TCHAR *szConfigManualPath;
extern TCHAR *szAppName;
extern TCHAR *szAppClass;
extern TCHAR *rtfExt;
extern TCHAR *txtExt;
extern TCHAR *settingsDialogCaption;
//initial window size
extern WPARAM screenWidth;
extern WPARAM screenHeight;
extern WPARAM wpInitWidth;
extern WPARAM wpInitHeight;
//default centering using default coords for height and width
extern WPARAM wpInitPosX;
extern WPARAM wpInitPosY;

extern WPARAM currentWidth;
extern WPARAM currentHeight;

extern WPARAM currentPosX;
extern WPARAM currentPosY;

extern WPARAM splashScreenWidth;
extern WPARAM splashScreenHeight;

//semi consts

extern int toolbarOffset;
extern const int mainPrefsMax;

//settings
extern WPARAM settingsDialogBoxWidth;
extern WPARAM settingsDialogBoxHeight;

extern int recentDocsListMax;

extern WPARAM zoomRatio_e;
extern WPARAM zoomRatio_d;
#define mainPrefsMax 14
//important geometry constants
#define PREF_BLOCKS_OFFSET 50
#define PREF_BLOCK_WIDTH 400 //wrap according to current width
#define PREF_BLOCK_WIDTH_TEXT 420 //blzitfgt
#define PREF_BLOCK_HEIGHT 80
#define PREF_BLOCK_CHKBOX_HEIGHT 20
#define PREF_BLOCK_CHKBOX_MARGIN_TOP 5
#define PREF_BLOCK_FIRSTITEM_OFFSET 20
#define PREF_BLOCK_SUBITEM_OFFSET 20
#define PREF_BLOCK_POSINIT_Y 30
#define PREF_BLOCK_MARGIN 5
#define PREF_BLOCK_MARGIN_LEFT 20
#define PREF_BLOCK_PADDING_LEFT 15
#define PREF_BLOCK_MARGIN_TOP 1
#define NEWLINE_CHAR '\n'
#define STD_BTN_WIDTH 48
#define STD_BTN_HEIGHT 48
#define STD_BTN_POS_Y 400
#endif