#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H
#define SZ_INIT    TEXT("Initializing application...")
#define SZ_LOAD    TEXT("Loading resources...       ")
#define SZ_CLOSE   TEXT("Closing splash window...")
#define SZ_SPLASH  TEXT("Splash window")

#define ID_TIMER_CLOSE	0x1111
#define ID_TIMER_INIT	0x1112
#define ID_TIMER_LOAD	0x1113
#define ID_TIMER_DONE	0x1114

LRESULT CALLBACK splashWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void registerSplashClass(void);
void createSplashScreen(void);
void showSplashScreen(void);
#endif