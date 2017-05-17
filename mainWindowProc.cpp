#include <Richedit.h>
#include <atlstr.h>
#include <cassert>
#include "translations.h"
#include "resource1.h"
#include "splashScreen.h"
#include "hotkeys.h"
#include "mainPrefs.h"
#include "appconst.h"
#include "globalVars.h"
#include "menuids.h"
#include "editcontrol.h"
#include "mainEditControl.h"
#include "mainWindowProc.h"
#include "recentFiles.h"
#include "mainMenu.h"
#include "statusControl.h"
#include "fileIO.h"
#include "settingsDialog.h"
#include "stdDialogBoxes.h"
#include "toolbarControl.h"
#include "clipboardOps.h"
#include "menuUtils.h"
#include "aboutDialog.h"
#include "timeDate.h"
LRESULT CALLBACK mainWindowProcedure(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	LPFINDREPLACE lpfr;
	if (message == WM_CLOSE || message == WM_QUIT) //bug is here
	{
		if (settings.bRememberLastSizeByUser)
		{
			getCurrentDims();
			binary::saveMainPrefs();
		}
	}
	switch (message)
	{
						
						case WM_NOTIFY:
						{
										  switch (((LPNMHDR)lParam)->code)
										  {
												  case EN_SELCHANGE:
												  {
														//MessageBox(0, _T("Key Down"), _T("Info"), MB_OK);
												  break;
												  }
												
										  }
										  changeLinePartText();
										  //TCHAR coords[20];
										  //_stprintf(coords,_T("%d %d"),curX,curY);
										  //MessageBox(NULL,coords, _T("Triggered"),MB_OK);
						break;
						}
					 case WM_KEYDOWN:
								{
									
										/*if (HIWORD(GetKeyState(VK_CONTROL)))
										{
											switch (wParam)
											{
											case O_KEY:
											{
														  MessageBox(0, _T("Key Down"), _T("Info"), MB_OK);
												break;
											}
											case J_KEY:
											{

														  MessageBox(0, _T("Key Down"), _T("Info"), MB_OK);
											break;
											}
											}
										}*/
									

										switch (wParam)
										{
										case  O_KEY:
										{
													
													   if (HIWORD(GetKeyState(VK_CONTROL)))
														  					{
																				  normal::initOpeningSequence();
																			}
														
													  //MessageBox(0, _T("Key Down"), _T("Info"), MB_OK);
													  break;
										}
										case P_KEY:
										{
													  //init print dlg

													  if (HIWORD(GetKeyState(VK_CONTROL)))
													  {
														  createPrintDialog();
													  }


													  break;
										}
										case J_KEY:
										{


													  if (HIWORD(GetKeyState(VK_CONTROL)))
													  {
														  createSettingsDialog(hwnd);
													  }
													  break;
													  //init prefs
										}
										case S_KEY:
										{
													  if (HIWORD(GetKeyState(VK_CONTROL)))
													  {

														  if (fileLoaded)
														  {
															  initSilentSavingSequence();

														  }
														  else
														  {
															  initSavingAsSequence();
														  }
													  }
													  break;
										}
									}
							//MessageBox(0, _T("Key Down"), _T("Info"), MB_OK);
							break;
						  }
	case WM_CREATE:
	{
					  //if (settings.bSplashScreen) //DO NOT UNCOMMENT
					  //{
						//  showbSplashScreen();
					  //}

					  

					
					  SetWindowText(hwnd,titleBarStatus[OPENMODE-1]);
					  createMainMenu(hwnd);
					 
					  if (settings.bToolbarActive)
					  {
						  createToolbar(hwnd);
						  fillToolbar(hwnd);
						  RECT tbDims;
						  GetWindowRect(toolBar, &tbDims);
						  toolbarOffset = tbDims.bottom - tbDims.top;
					  }
					  createMainRichEditControl(hwnd,ghInstance);
					  SendMessage(richEditControl, EM_SETZOOM, zoomRatio_e, zoomRatio_d);
					  //if set here
					  if (settings.bDetectLinks)
					  {
						  SendMessage(richEditControl,
							  EM_AUTOURLDETECT, AURL_ENABLEURL | AURL_ENABLEEMAILADDR, NULL);
					  }
					  updateChildSize(hwnd,toolbarOffset); //richedit rename
					  createStatusControl(hwnd);
					  registerSettingsDialogClass(hwnd);
					  if (OPENMODE == 1)
					  {
						  disableFormattingOptions();
					  }
					  menuState.cbSize = sizeof(MENUITEMINFO);
					  SetFocus(richEditControl);

					  //styleMenuItems();
					  //registerPrefsDialogClass(hwnd);
					  break;
	}
	case WM_SIZE:
	{
		//send new coords to child windows
					//change dims
					currentWidth = LOWORD(lParam);
					currentHeight = HIWORD(lParam);
					updateChildSize(hwnd, toolbarOffset);
					resizeStatusControl();
		break;
	}
	case WM_COMMAND:
	{
						//changeLinePartText();
					   //SendMessage(toolBar, TB_SETHOTITEM, 0, NULL);
					   switch (LOWORD(wParam))
					   {
							  
							   case IDC_EDIT_MAIN:
							   {
									break;
							   }
							   case IDM_FILE_NEW_TXT:
							   {
														initNewSequence(1);
												
											
								break;
							   }
							   case IDM_FILE_NEW_RTF:
							   {
														initNewSequence(2);
												
									break;

							   }
							   case IDM_REC_CLEAR:
							   {
													 if (initClearRecProc())
													 {
														 recentDocsList_clear();
													 }
													 else
													 {
														return 1;
													 }
													break;
							   }
							   case IDM_FILE_OPEN:
							   {
											
													 normal::initOpeningSequence();
													 break;
							   }
							   case IDM_FILE_SAVE: //ctrl+s
							   {
													   initSilentSavingSequence();
											
											break;
							   }
							   case IDM_FILE_SAVE_AS:
							   {
														initSavingAsSequence();
											
											
													 break;
							   }
								   //PRINTDLG printDialogStruct;
							   case IDM_FILE_PRINT:
							   {
													  createPrintDialog();
											  
										break;
							   }
							   case IDM_FILE_RECENT:
							   {
													  //show next to it
													   break;
							   }
							   case IDM_FILE_EXIT:
							   {
													 SendMessage(hwnd, WM_CLOSE, NULL, NULL);
													 break;
							   }
							   case IDM_EDIT_UNDO:
							   {
													 initUndoProcedure();
													 break;
							   }
							   case IDM_EDIT_COPY:
							   {
													 initCopyProcedure();
											  
								break;
							   }
							   case IDM_EDIT_PASTE:
							   {
													  initPasteProcedure();
								break;
							   }
							   case IDM_EDIT_DELETE:
							   {
													   initDelProcedure();
								break;
							   }
							   case IDM_EDIT_FIND:
							   {
													 initializeFindDlgBox(hwnd);
							   break;
							   }
							   case IDM_EDIT_REPLACE:
							   {

								break;
							   }
							   case IDM_EDIT_PREFERENCES:
							   {
								   createSettingsDialog(hwnd);
								   break;
							   }
					   
							   case IDM_JUSTIFY_LEFT:
							   {
												
														GetMenuItemInfo(menuBar, IDM_JUSTIFY_LEFT, TRUE, (LPMENUITEMINFO)&menuState);
														formatStruct.cbSize = sizeof(PARAFORMAT);
														formatStruct.dwMask = PFM_ALIGNMENT;
														if (justifyLeftEnabled)
														{
															tempStyle = PFA_LEFT;
													
															menuState.fState = MFS_UNCHECKED;
															ModifyMenu(menuBar, IDM_JUSTIFY_LEFT, MF_BYCOMMAND | MF_UNCHECKED, IDM_JUSTIFY_LEFT, _T("&Left"));
															justifyLeftEnabled = false;

														}
														else
														{

															tempStyle = PFA_LEFT;
															//ModifyMenu(menuBar, IDM_JUSTIFY_LEFT, MF_BYCOMMAND | MF_CHECKED, IDM_JUSTIFY_LEFT, _T("&Left"));
															enableMenuEditAlign_left();
															justifyLeftEnabled = true;
															justifyCenterEnabled = false;
															justifyRightEnabled = false;
														}
														formatStruct.wAlignment = tempStyle;
														setCheckButtonStyle(1,IDM_JUSTIFY_LEFT);

												

														SendMessage(richEditControl, EM_SETPARAFORMAT, formatStruct.wAlignment, (LPARAM)&formatStruct);
														break;
							   }
					
							   case IDM_JUSTIFY_CENTER:
							   {
														  GetMenuItemInfo(menuBar, IDM_JUSTIFY_CENTER, TRUE, (LPMENUITEMINFO)&menuState);
														  formatStruct.cbSize = sizeof(PARAFORMAT);
														  formatStruct.dwMask = PFM_ALIGNMENT;

														  if (justifyCenterEnabled)
														  {
															tempStyle = PFA_LEFT;
															menuState.fState = MFS_UNCHECKED;
															ModifyMenu(menuBar, IDM_JUSTIFY_CENTER, MF_BYCOMMAND | MF_UNCHECKED, IDM_JUSTIFY_CENTER, _T("&Center"));
															justifyCenterEnabled = false;
														  }
														  else
														  {
															tempStyle = PFA_CENTER;
															//ModifyMenu(menuBar, IDM_JUSTIFY_CENTER, MF_BYCOMMAND | MF_CHECKED, IDM_JUSTIFY_CENTER, _T("&Center"));
															enableMenuEditAlign_center();
															justifyCenterEnabled = true;
															justifyLeftEnabled = false;
															justifyRightEnabled = false;

														  }
														  formatStruct.wAlignment = tempStyle;
														  setCheckButtonStyle(1, IDM_JUSTIFY_CENTER);
														  SendMessage(richEditControl, EM_SETPARAFORMAT, formatStruct.wAlignment, (LPARAM)&formatStruct);
														 break;
							   }
							   case IDM_JUSTIFY_RIGHT:
							   {
														 menuState.fMask = MIIM_STATE;
														 GetMenuItemInfo(menuBar, IDM_JUSTIFY_RIGHT, false, (LPMENUITEMINFO)&menuState);

														 formatStruct.cbSize = sizeof(PARAFORMAT);
														 formatStruct.dwMask = PFM_ALIGNMENT;

														 if (justifyRightEnabled)
														 {
															 tempStyle = PFA_LEFT;
															 menuState.fState = MFS_UNCHECKED;
															 ModifyMenu(menuBar, IDM_JUSTIFY_RIGHT, MF_BYCOMMAND | MF_UNCHECKED, IDM_JUSTIFY_RIGHT, _T("&Right"));
															 justifyRightEnabled = false;
														 }
														 else
														 {
															 tempStyle = PFA_RIGHT;
															// ModifyMenu(menuBar, IDM_JUSTIFY_RIGHT, MF_BYCOMMAND | MF_CHECKED, IDM_JUSTIFY_RIGHT, _T("&Right"));
															 enableMenuEditAlign_right();
															 justifyRightEnabled = true;
															 justifyCenterEnabled = false;
															 justifyLeftEnabled = false;
														 }
														 formatStruct.wAlignment = tempStyle;
														 setCheckButtonStyle(1, IDM_JUSTIFY_RIGHT);
														 SendMessage(richEditControl, EM_SETPARAFORMAT, formatStruct.wAlignment, (LPARAM)&formatStruct);
														 break;
							   }





					 
							 CHARFORMAT textFormatStruct;
					



							   case IDM_STYLE_BOLD:
							   {
													  menuState.cbSize = sizeof(MENUITEMINFO);
													  ZeroMemory(&textFormatStruct, sizeof(textFormatStruct));
													  textFormatStruct.cbSize = sizeof(CHARFORMAT);
													  //textFormatStruct.cbSize = sizeof(CHARFORMAT);
													  //textFormatStruct.dwMask = CFM_BOLD;
													  menuState.fMask = MIIM_STATE;
													  GetMenuItemInfo(menuBar,IDM_STYLE_BOLD,TRUE,(LPMENUITEMINFO)&menuState);

													  if (styleBoldEnabled)
													  {
									
														  menuState.fState = MFS_UNCHECKED;
												 
														  textFormatStruct.dwMask = CFM_BOLD;
												
														  ModifyMenu(menuBar, IDM_STYLE_BOLD, MF_BYCOMMAND | MF_UNCHECKED, IDM_STYLE_BOLD, _T("&Bold"));
														  styleBoldEnabled = false;
													  }
													  else
													  {
												  
												  
														  ModifyMenu(menuBar, IDM_STYLE_BOLD, MF_BYCOMMAND | MF_CHECKED, IDM_STYLE_BOLD, _T("&Bold"));
												 
														  textFormatStruct.dwMask = CFM_BOLD;
														  textFormatStruct.dwEffects = CFE_BOLD;
														  styleBoldEnabled = true;
													  }

										
											   
											   
													   SendMessage(richEditControl, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&textFormatStruct);

														 break;
							   }
							   case IDM_STYLE_ITALIC:
							   {
											
												
														menuState.cbSize = sizeof(MENUITEMINFO);
														ZeroMemory(&textFormatStruct,sizeof(textFormatStruct));
														textFormatStruct.cbSize = sizeof(CHARFORMAT);
														GetMenuItemInfo(menuBar, IDM_STYLE_ITALIC, TRUE, (LPMENUITEMINFO)&menuState);
														if (styleItalicEnabled)
														{
															menuState.fState = MFS_UNCHECKED;
															ModifyMenu(menuBar, IDM_STYLE_ITALIC, MF_BYCOMMAND | MF_UNCHECKED, IDM_STYLE_ITALIC, _T("&Italic"));
															textFormatStruct.dwMask = CFM_ITALIC;
															styleItalicEnabled = false;
														}
														else
														{							
															ModifyMenu(menuBar, IDM_STYLE_ITALIC, MF_BYCOMMAND | MF_CHECKED, IDM_STYLE_ITALIC, _T("&Italic"));
															textFormatStruct.dwMask = CFM_ITALIC;
															textFormatStruct.dwEffects = CFE_ITALIC;
															styleItalicEnabled = true;
														}
														SendMessage(richEditControl, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&textFormatStruct);
														 break;
							   }
							   case IDM_STYLE_UNDERLINED:
							   {
															menuState.cbSize = sizeof(MENUITEMINFO);
															ZeroMemory(&textFormatStruct, sizeof(textFormatStruct));
															textFormatStruct.cbSize = sizeof(CHARFORMAT);
															GetMenuItemInfo(menuBar, IDM_STYLE_UNDERLINED, TRUE, (LPMENUITEMINFO)&menuState);
															if (styleUnderlinedEnabled)
															{

																menuState.fState = MFS_UNCHECKED;
																ModifyMenu(menuBar, IDM_STYLE_UNDERLINED, MF_BYCOMMAND | MF_UNCHECKED, IDM_STYLE_UNDERLINED, _T("&Underlined"));
																textFormatStruct.dwMask = CFM_UNDERLINE;
																styleUnderlinedEnabled = false;
															}
															else
															{

																ModifyMenu(menuBar, IDM_STYLE_UNDERLINED, MF_BYCOMMAND | MF_CHECKED, IDM_STYLE_UNDERLINED, _T("&Underlined"));
																textFormatStruct.dwMask = CFM_UNDERLINE;
																textFormatStruct.dwEffects = CFE_UNDERLINE;
																styleUnderlinedEnabled = true;
															}
													
												
															SendMessage(richEditControl, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&textFormatStruct);
														 break;
							   }

							   case IDM_STYLE_COLOR:
							   {
													   textFormatStruct.cbSize = sizeof(CHARFORMAT);
											   
													   textFormatStruct.dwEffects = 0;
													   textFormatStruct.dwMask = CFM_COLOR;
													   textFormatStruct.crTextColor = initializeColorDlgBox(hwnd);
											   
													   SendMessage(richEditControl, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&textFormatStruct);

								break;
							   }
							   case IDM_STYLE_FONT:
							   {
													  TCHAR fontFace[32];
													  CHOOSEFONT fontFormatStruct;
													  textFormatStruct.cbSize = sizeof(CHARFORMAT);
													  textFormatStruct.dwMask = CFM_SIZE | CFM_FACE | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE;
													  fontFormatStruct = initializeFontDlgBox(hwnd);
											  
													  //font size conversion
													  textFormatStruct.yHeight = (1440*fontFormatStruct.lpLogFont->lfHeight)/72;
											 
											 
											 
													  //font family
													  _tcscpy(fontFace, fontFormatStruct.lpLogFont->lfFaceName);
													  _tcscpy(textFormatStruct.szFaceName, fontFace);
											  
													  //style [b],[i],[u]
													  //textFormatStruct.dwEffects
													  SendMessage(richEditControl, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&textFormatStruct);			
							   break;

							   }
							   case IDT_TIME_US:
							   case IDT_TIME_MILITARY:
							   {
													getCurrentTime(LOWORD(wParam));
													break;
							   }
							   case IDT_DATE_US:
							   case IDT_DATE_EUR:
							   case IDT_DATE_ISO:
							   {
													getCurrentDate(LOWORD(wParam));
													break;
							   }
							  
							   case IDM_ABOUT_ABOUT:
								   {
										DialogBox(ghInstance,MAKEINTRESOURCE(IDD_DIALOGBAR),hwnd,aboutDlgProc);
					
										break;
								   }
							   default:
							   {
										//clicking on recent files list

										  if (LOWORD(wParam)>IDM_REC_CLEAR)
										  {
											  assert(LOWORD(wParam)>0);
											  uiMenuIndex_recents = (WPARAM)LOWORD(wParam);
											  TCHAR temp[256];
											  memset(temp, 0, sizeof(temp));
											  
											  uiVecIndex_recents = convertMenu2VecIndex((WPARAM)LOWORD(wParam));
											  std::string usrRecFilePath = getRecentlyOpenedFileName(uiVecIndex_recents); //should return the name in LPCTSTR
											  int fileType = detectFileType(usrRecFilePath);
											  _tcscpy(temp, CA2T(usrRecFilePath.c_str()));
											  fromRecent::initOpeningSequence((LPCTSTR)temp, fileType);//for saving dialog

										  }
								break;
							   }



					}
							   break;
	}
	/*case WM_KEYDOWN:
	{
					   switch (wParam)
					   {
					   case 0x4F:
					   {
									if (HIWORD(GetKeyState(VK_CONTROL)))
									{
										openFileDiag(hwnd,0);
									}
					   }
						   //TO DO USE DELETE KEY FOR ENTRY DELETION
					   }
			break;
	}*/
	case WM_CLOSE:
	{
					
					 if (fileChanged)
					 {
						 if (!fileSaved)
						 {
							 if (!settings.bConfirmExit)
							 {
								 DestroyWindow(hwnd);
								
							 }
							 else
							 {
								 if (MessageBox(hwnd, commDlgMsgWarnInfo_EN[0],
									 szAppName, MB_YESNO | MB_ICONQUESTION) == IDYES)
								 {
									 DestroyWindow(hwnd);
								 }
								 else
								 {
									 return 1;
								 }
							 }
									
						 }
						 else
						 {

							 if (!settings.bConfirmExit)
							 {
										
								 DestroyWindow(hwnd);
							 }

							 else
							 {
								 if (
								 MessageBox(hwnd, 
								 commDlgMsgWarnInfo_EN[1],
												szAppName, 
												MB_YESNO | MB_ICONQUESTION) == IDYES)
													 {
														 DestroyWindow(hwnd);
													 }
													 else
													 {
														 return 1;
													 }

							 }
			
						 }
					 }
					 else
					 {

						 if (!settings.bConfirmExit)
						 {

							 DestroyWindow(hwnd);
						 }

						 else
						 {
							 if (MessageBox(hwnd, commDlgMsgWarnInfo_EN[1],
								 szAppName, MB_YESNO | MB_ICONQUESTION) == IDYES)
							 {
								 DestroyWindow(hwnd);
							 }
							 else
							 {
								 return 1;
							 }


						 }
					 }
					 break;

	}
	case WM_DESTROY:
	{
					
					
					   PostQuitMessage(WM_QUIT);
					   return 0;
	}
	default:
	{
				//Processing messages for the find and replace dialog box
		
				
			   if (message == uFindReplaceMsg)
			   {
				   // Get pointer to FINDREPLACE structure from lParam.
				   lpfr = (LPFINDREPLACE)lParam;

				   // If the FR_DIALOGTERM flag is set, 
				   // invalidate the handle that identifies the dialog box. 
				   if (lpfr->Flags & FR_DIALOGTERM)
				   {
					   findDlg = NULL;
					   return 0;
				   }

				   // If the FR_FINDNEXT flag is set, 
				   // call the application-defined search routine
				   // to search for the requested string.
				   //user pressed the 'Find next' button in the find dialog box
				  
				   if (lpfr->Flags & FR_FINDNEXT)
				   {
					   if (!findFunc(lpfr))
					   {
							MessageBox(NULL,_T("The specified string wasn't found"), _T("Error"), MB_OK|MB_ICONWARNING);
					   }
					   //S//earchFile(lpfr->lpstrFindWhat,
						  // (BOOL)(lpfr->Flags & FR_DOWN),
						 //  (BOOL)(lpfr->Flags & FR_MATCHCASE));
				   }

				   return 0;
			   }
	break;
	}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
void updateChildSize(HWND mainWindow, int toolbarOffset)
{
	SetWindowPos(richEditControl,NULL,0,toolbarOffset,currentWidth,currentHeight,NULL);
}
void getCurrentDims(void)
{	
	RECT currentDimensions;

	unsigned int width, height, xPos, yPos;
	GetWindowRect(hwnd, &currentDimensions);
	
	width = currentDimensions.right - currentDimensions.left;
	height = currentDimensions.bottom - currentDimensions.top;
	xPos = currentDimensions.left;
	yPos = currentDimensions.top;

	settings.iUsrLastHeight = height;
	settings.iUsrLastWidth = width;
	settings.iUsrLastXPos = xPos;
	settings.iUsrLastYPos = yPos;
}
//TO -NEVER- DO: JOIN INTO ONE FUNCTION
void activateNewTXTMode(void)
{
	OPENMODE = 1;
	SetWindowText(hwnd, titleBarStatus[OPENMODE - 1]);
	SetWindowText(richEditControl, _T(""));
	disableFormattingOptions();
}
void activateNewRTFMode(void)
{
	OPENMODE = 2;
	SetWindowText(hwnd, titleBarStatus[OPENMODE - 1]);
	SetWindowText(richEditControl, _T(""));
	enableFormattingOptions();
}
