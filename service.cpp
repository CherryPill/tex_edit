#define OEMRESOURCE
#include <Windows.h>
#include "resource.h"
#include "appconst.h"
#include "globalVars.h"
#include "service.h"

void loadAppSmIcon(void)
{
	mainAppIcon = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON155), IMAGE_ICON, 0, 0, NULL);
}
void initWaitCursor(void)
{
	SetSystemCursor(plainCursor,OCR_WAIT);
}
void resetCursor(void)
{
	SystemParametersInfo(SPI_SETCURSORS,0,NULL,0);
}
//returns the calculated groupbox width based on how many elements there are
//CHECKBOXONLY
INT32 getGroupBoxWidth(INT32 numOfElements)
{
	return 
		{
			PREF_BLOCK_FIRSTITEM_OFFSET + 
				(PREF_BLOCK_CHKBOX_HEIGHT + PREF_BLOCK_CHKBOX_MARGIN_TOP)*numOfElements + 
			PREF_BLOCK_FIRSTITEM_OFFSET - 10
		};
}