#include <Windows.h>
#include  "mainEditUtils.h"
void enableDragAndDrop(void)
{
	DragAcceptFiles(hwnd,true);
}
void disableDragAndDrop(void)
{
	DragAcceptFiles(hwnd,false);
}