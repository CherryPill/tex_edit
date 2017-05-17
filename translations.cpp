#include <windows.h>
#include <tchar.h>
#include "translations.h"


//NOT WORKING

/* ########################################################################
							MAIN MENU STRINGS BEGIN
########################################################################*/
/* ########################################################################
							ENGLISH (UNITED STATES) BEGIN
########################################################################*/

//main menu bar
 TCHAR *mainMenuStringFile_ENG = _T("File");
 TCHAR *mainMenuStringEdit_ENG = _T("Edit");
 TCHAR *mainMenuStringFormat_ENG = _T("Format");
 TCHAR *mainMenuStringAbout_ENG = _T("About");
//respective submenus
 TCHAR *mainSubMenuFileString_ENG[6] = 
 {
							 _T("Open...\tCtrl+O"),
							 _T("New..."),
							 _T("Save\tCtrl+S"),
							 _T("Save as..."),
							 _T("Print...\tCtrl+P"),
							 _T("Exit")
 };
 TCHAR *mainSubMenuEditString_ENG[6] = 
 {
							 _T("Undo...\tCtrl+Z"),
							 _T("Redo...\tCtrl+R"),
							 _T("Copy...\tCtrl+C"),
							 _T("Paste...\Ctrl+V"),
							 _T("Cut\tCtrl+X"),
							 _T("Preferences...\tCtrl+J")
 }; //add+2 reserve for find/rep (later)
 TCHAR *mainSubMenuFormatString_ENG[10] = 
 {
							 _T("Alignment"),
							 _T("Left"),
							 _T("Center"),
							 _T("Right"),
							 _T("Style"),
							 _T("Bold\tCtrl+B"),
							 _T("Italic\tCtrl+I"),
							 _T("Underline\tCtrl+U"),
							 _T("Color"),
							 _T("Font"),
 };
 TCHAR *mainSubMenuAboutString_ENG;

TCHAR *errorMessages_ENG[6] = 
{
	_T("FATAL ERROR: this program requires comctl32.dll of version >=6"),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T("")

};
TCHAR *warningMessages_ENG[6];

TCHAR *toolbarText_ENG[12] = { 
								_T("New"),
								_T("Open"), 
								_T("Save"),
								_T("Print"),
								_T("Left"),
								_T("Center"),
								_T("Right"),
								_T("Bold"),
								_T("Italic"),
								_T("Underline"),
								_T("Color"), 
								_T("Font"), 
   
   };
TCHAR *settingsTextActual_EN[20]
{
													_T("Remember last window position and size"),
													_T("Splash Screen"),
													_T("Always confirm exit"),
													_T("Show complete path in title bar"),
													_T("Detect URLs and email links (.RTF only)"),
													_T("Toolbar Active"),
													_T("Show Text"),
													_T(""),
													_T(""),
													_T(""),
													_T(""),
													_T(""),
													_T(""),
													_T(""),
													_T(""),
													_T(""),
													_T(""),
													_T(""),
													_T(""),
													_T(""),
};
TCHAR *settingsTextGroupLabels_EN[10] =
{
											_T("Startup"),
											_T("Shutdown"),
											_T("Editor"),
											_T("Toolbar"),
											_T(""),
											_T(""),
											_T(""),
											_T(""),
											_T(""),
											_T(""),
};
TCHAR *settingsBtns_EN[2]
{
	_T("OK"),
		_T("Cancel"),

};
TCHAR *settingsTextWindowTitle_EN = _T("TexEdit - Settings");
/* ########################################################################
								ENGLISH (UNITED STATES) END
########################################################################*/

/* ########################################################################
								RUSSIAN SECTION BEGIN
########################################################################*/
//main menu bar
 TCHAR *mainMenuStringFile_RU = _T("Файл");
 TCHAR *mainMenuStringEdit_RU = _T("Редактирование");
 TCHAR *mainMenuStringFormat_RU = _T("Форматирование");
 TCHAR *mainMenuStringAbout_RU = _T("О Программе");




//respective sub menus
 TCHAR *mainSubMenuFileString_RU[6] = 
 {
							 _T("Открыть...\tCtrl+O"),
							 _T("Новый документ..."),
							 _T("Сохранить\tCtrl+S"),
							 _T("Сохранить как..."),
							 _T("Печать...\tCtrl+P"),
							 _T("Выход")
 };
 TCHAR *mainSubMenuEditString_RU[6] =
 {
							 _T("Отменить действие...\tCtrl+Z"),
							 _T("Повторить действие...\tCtrl+R"),
							 _T("Копировать...\tCtrl+C"),
							 _T("Вставить...\Ctrl+V"),
							 _T("Вырезать\tCtrl+X"),
							 _T("Настройки...\tCtrl+J")
 }; //add+2 reserve for find/rep
 TCHAR *mainSubMenuFormatString_RU[10] = 
 {
								 _T("Выравнивание"),
								 _T("Слева"),
								 _T("По центру"),
								 _T("Справа"),
								 _T("Стиль"),
								 _T("Жирный\tCtrl+B"),
								 _T("Курсив\tCtrl+I"),
								 _T("Подчеркнутый\tCtrl+U"),
								 _T("Цвет"),
								 _T("Шрифт"),
 };
 TCHAR *mainSubMenuAboutString_RU;
TCHAR *errorMessages_RU[6] = {
														_T("Файл конфигурации не найден, он будет воссоздан"),
														_T(""),
														_T(""),
														_T(""),
														_T(""),
														_T(""),

};
TCHAR *warningMessages_RU[6];

TCHAR *toolbarText_RU[12] = {
									_T("Новый"),
									_T("Открыть"),
									_T("Сохранить"),
									_T("Печать"),
									_T("Слева"),
									_T("Центр"),
									_T("Справа"),
									_T("Жирный"),
									_T("Курсив"),
									_T("Подчеркнутый"),
									_T("Цвет"),
									_T("Шрифт"),
};

TCHAR *settingsTextActual_RU[20]
{
	_T("Запоминать последнюю позицию и размеры окна"),
		_T("Экран приветствия"),
		_T("Всегда подтверждать вых из программы"),
		_T("Показывать полный путь к файлу в заголовку"),
		_T("Выделять гиперссылки (только .RTF)"),
		_T("Панель инструментов"),
		_T("Показывать текст на панели инструментов"),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
};
TCHAR *settingsTextWindowTitle_RU = _T("TexEdit - Настройки");
TCHAR *settingsTextGroupLabels_RU[10] =
{

	_T("Запуск программы"),
	_T("Выход из программы"),
	_T("Редактор"),
	_T("Панель инструментов"),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
};
TCHAR *settingsBtns_RU[2]
{
	settingsBtns_EN[0],
		_T("Отмена"),
};
/* ########################################################################
								RUSSIAN SECTION END
   ########################################################################*/


/* ########################################################################
							JAPANESE (JAPAN) BEGIN
########################################################################*/

//main menu bar
TCHAR *mainMenuStringFile_JP = _T("ファイル");
TCHAR *mainMenuStringEdit_JP = _T("編集");
TCHAR *mainMenuStringFormat_JP = _T("Format");
TCHAR *mainMenuStringAbout_JP = _T("このプログラムについて");
//respective submenus
TCHAR *mainSubMenuFileString_JP[6] =
{
	_T("Open...\tCtrl+O"),
	_T("制作する..."),
	_T("保存する\tCtrl+S"),
	_T("名前をつけて保存する..."),
	_T("印刷...\tCtrl+P"),
	_T("プログラムをやめる")
};
TCHAR *mainSubMenuEditString_JP[6] =
{
	_T("Undo...\tCtrl+Z"),
	_T("Redo...\tCtrl+R"),
	_T("Copy...\tCtrl+C"),
	_T("Paste...\Ctrl+V"),
	_T("Cut\tCtrl+X"),
	_T("設定...\tCtrl+J")
}; //add+2 reserve for find/rep (later)
TCHAR *mainSubMenuFormatString_JP[10] =
{
	_T("配置"),
	_T("左"),
	_T("中"),
	_T("右"),
	_T("Style"),
	_T("Bold\tCtrl+B"),
	_T("イタリック\tCtrl+I"),
	_T("下線部\tCtrl+U"),
	_T("字色"),
	_T("フォント"),
};
TCHAR *mainSubMenuAboutString_JP;
TCHAR *errorMessages_JP[6];
TCHAR *warningMessages_JP[6];

TCHAR *toolbarText_JP[12] = {
	_T("New"),
	_T("オープンファイル"),
	_T("保存"),
	_T("印刷"),
	_T("左"),
	_T("中"),
	_T("右"),
	_T("ボールド"),
	_T("イタリック"),
	_T("下線部"),
	_T("字色"),
	_T("フォント"),
};
TCHAR *settingsTextActual_JP[20]
{
		_T("Remember last window position and size"),
		_T("ようこそ画像を表示する"),
		_T("終了確認"),
		_T("Show complete path in title bar"),
		_T("Detect URLs and email links (.RTF only)"),
		_T("Toolbar Active"),
		_T("テキストを表示する"),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
};
TCHAR *settingsTextGroupLabels_JP[10] =
{
	_T("起動"),
	_T("終了"),
	_T("編集"),
	_T("ツールバー"),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
	_T(""),
};
TCHAR *settingsBtns_JP[2]
{
	settingsBtns_EN[0],
		_T("キャンセル"),

};
TCHAR *settingsTextWindowTitle_JP = _T("TexEdit - 設定");
/* ########################################################################
							JAPANESE (JAPAN) END
########################################################################*/

/* ########################################################################
							  MAIN MENU STRINGS END
########################################################################*/
/* ########################################################################
							STATUS CONTROL MESSAGES BEGIN
########################################################################*/



TCHAR *statusControlMessages_EN[] =
{
	_T("Ready"),
	_T("File loaded"),
	_T("File saved"),
	_T("File quick saved"),
	_T("File not saved"),
	_T("Standing by...")
};
TCHAR *statusControlMessages_RU[] =
{
	_T("Готово"),
	_T("Документ загружен"),
	_T("Документ сохранен"),
	_T("Документ сохранен"),
	_T("Документ не сохранен"),
	_T("Ожидание...")
};
TCHAR *statusControlMessages_JP[] =
{
	_T("準備はいい"),
	_T("文書ロードしました"),
	_T("文書保存しましたた"),
	_T("文書早保存"),
	_T("文書無保存"),
	_T("待機...")
};
/* ########################################################################
						STATUS CONTROL MESSAGES END
########################################################################*/


/* ########################################################################
							COMMON DIALOG MESSAGES BEGIN
########################################################################*/








/* ########################################################################
							ENGLISH (UNITED STATES) BEGIN
########################################################################*/



const TCHAR *commDlgMsgWarnInfo_EN[] = 
{
				_T("You have unsaved changes\nIf you leave now, all changes will be lost\nQuit anyway ?"),
				_T("Are you sure you want to quit?"),
				_T("Changes have been saved and will take effect on next startup"),
				_T("You have unsaved changes\nSave them now?"),
				_T("Configuration file is missing\nIt will be recreated"),
				_T("Are you sure you want to delete the recent files list?"),
				_T("Do you want to share anonymous statistics about your system?\nThe data gathered ONLY includes your Windows version."),
				_T("Do you want to delete it from the list?")
};
TCHAR *commDlgMsgError_EN[] = 
{
	_T("Unable to write to file"),
	_T("File not found")
};
TCHAR *commDlgMsgWarnInfoCaptions_EN[] = 
{
	_T("TexEdit - Warning")
};
TCHAR *commDlgMsgErrorCaptions_EN[] = 
{
	_T("TexEdit - Error")
};
/* ########################################################################
							ENGLISH (UNITED STATES) END
########################################################################*/

/* ########################################################################
						RUSSIAN BEGIN
########################################################################*/
TCHAR *commDlgMsgWarnInfo_RU[] =
{
	_T("Имеются несохраненные изменения\nЕсли вы покинете программу сейчас, все изменения будут утеряны\nВыйти?"),
	_T("Вы действительно хотите выйти?"),
	_T("Изменения были сохранены и вступят в силу при следующем запуске программы"),
	_T("Имеются несохраненные изменения\nСохранить документ?"),
	_T("Файл конфигурации не найдет\nОн будет воссоздан со значениями по умолчанию")

};
TCHAR *commDlgMsgError_RU[] =
{
	_T("")

};

/* ########################################################################
								RUSSIAN END
########################################################################*/

/* ########################################################################
									JAPANESE BEGIN
########################################################################*/


TCHAR *commDlgMsgWarnInfo_JP[] =
{
	_T("You have unsaved changes\nIf you leave now, all changes will be lost\nQuit anyway?"),
	_T("本当に終了しますか"),
	_T("Changes have been saved and will take effect on next startup"),
	_T("You have unsaved changes\nSave them now?"),
	_T("設定ファイルがいませんですが、再作成します")

};
TCHAR *commDlgMsgError_JP[] =
{
	_T("")

};

/* ########################################################################
									JAPANESE END
########################################################################*/



/* ########################################################################
								COMMON DIALOG MESSAGES END
########################################################################*/
/* ########################################################################
							MENU TIME & DATE STRING BEGIN
########################################################################*/

TCHAR *timeStrings_EN[] = 
{
	_T("AM/PM"),
	_T("Military")
};
TCHAR *dateStrings_EN[] = 
{
	_T("m/d/yyyy"),
	_T("d/m/yyyy"),
	_T("yyyy/m/d")
};
const TCHAR *test[1] =
{
	_T("test")
};