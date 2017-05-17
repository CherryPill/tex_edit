#include <Windows.h>
#include <CommCtrl.h>
#ifndef TOOLBARCONTROL_H
#define TOOLBARCONTROL_H
void disableFormattingOptions(void);
void enableFormattingOptions(void);
void enableFastSaveIcon(void);
void disableFastSaveIcon(void);
void createToolbar(HWND);
void fillToolbar(HWND);
#endif
