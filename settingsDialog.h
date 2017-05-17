#include <Windows.h>
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

void registerSettingsDialogClass(HWND);
void createSettingsDialog(HWND);
void showSettingsDialog(void);


void createSettingsPages(HWND, RECT);
void createSettings_Pg_0(HWND, RECT);
void createSettings_Pg_1(HWND, RECT);
void createSettings_Pg_2(HWND, RECT);
void createSettings_Pg_3(HWND, RECT);
void createSettings_Pg_4(HWND, RECT);
void createSettings_Pg_5(HWND, RECT);

//page 0
void createStartUpBlock(HWND, RECT);
void createShutDownBlock(HWND, RECT);
//page 1
void createToolbarBlock(HWND, RECT);
void createRecentsBlock(HWND, RECT);
void createStatusbarBlock(HWND,RECT);
void createMiscBlock_p1(HWND,RECT);
//page 2
void createEditorBlock(HWND, RECT);
//page 3
void createKBindsBlock(HWND, RECT);
//page 4
void createBoilerBlock(HWND,RECT);
//page 5

void createPathBlock(HWND,RECT);


//void createLanguageBlock(HWND,RECT); not used
void createOKButton(HWND, RECT);
void createCancelButton(HWND, RECT);
bool readChkBoxesState(HWND);
void writeChkBoxesState(HWND);
void fillChkBoxBlocks(HWND);


void createMainTabArea(HWND);
void toggleShowHidePage_0(bool);
void toggleShowHidePage_1(bool);
void toggleShowHidePage_2(bool);
void toggleShowHidePage_3(bool);
void toggleShowHidePage_4(bool);
void toggleShowHidePage_5(bool);

void redrawControls(INT32);
void hideAllSettingsControls(void);
bool CALLBACK SetFont(HWND, LPARAM);
void loadFlags(void);
LRESULT CALLBACK settingsDialogProcedure(HWND,UINT,WPARAM,LPARAM);
#endif