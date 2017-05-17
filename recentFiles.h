#include <Windows.h>
#include <vector>
#ifndef RECENTFILES_H
#define RECENTFILES_H



//functions affecting the main structure
void recentDocsList_clear(void);
void recentDocsList_push(LPCTSTR, WPARAM); //gets invoked when uses chooses to open/create/close file
//backend
void recentDocsList_clear_backend(void);
void recentDocsList_push_backend(LPCTSTR);
//front-end functions affecting the main menu appearance
void recentDocsList_clear_gui(void);
void recentDocsList_fill_gui(void); //gets invoked only at startup
void recentDocsList_push_gui(LPCTSTR);
void recentDocsList_insert_gui(LPCTSTR);
void recentDocsList_delete_gui(void);
void recentDocsList_delete_backend(void);
void recentDocsList_delete(LPCTSTR);
bool askForDeletion(void);
//dummy
void recentDocsList_pop(void);
//sys
void disableRecentMenuItem(void);
void enableRecentMenuItem(void);
//fileio
bool chkIfRecentFilesExists(void);
void loadRecentFiles(void);
void writeRecentFiles(void);
void setDefaultRecentFiles(void);
bool initClearRecProc(void);
extern std::vector<std::string> recentDocsList;
#endif