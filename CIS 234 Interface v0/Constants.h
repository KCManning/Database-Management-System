// include the basic windows header file
#include <my_global.h>
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <objidl.h>
#include <stdio.h> 
#include <mysql.h>
#include <sstream>
//#include "mysql.h"


#pragma comment(lib, "libmysql")
#pragma comment(lib, "mysqlclient")



//#pragma comment(lib, "mysqlclient.lib")
//
//#include <driver.h>
//#include <connection.h>
//#include <statement.h>
//#include <prepared_statement.h>
//#include <resultset.h>
//#include <metadata.h>
//#include <resultset_metadata.h>
//#include <exception.h>
//#include <warning.h>

#pragma warning (disable: 4244)
//#pragma comment(lib, "gdiplus.lib")


using namespace std;
//using namespace Gdiplus;

enum Screen
{
	NoScreen,
	Invoice,
	Contractor,
	Contract,
	Vendor,
	Report,
	Login,
	Admin
};

enum SubScreen
{
	BlankScreen,
	Employee,
	UnitNum,
	Division
};

class Constants
{
public:
	Constants();

	short getHeight() const {return m_WINDOW_HEIGHT;}
	short getWidth() const {return m_WINDOW_WIDTH;}
	short getXPos() const {return m_WINDOW_X_POSITION;}
	short getYPos() const {return m_WINDOW_Y_POSITION;}
	short getPadding() const {return m_WINDOW_PADDING;}
	short getBtnHeight() const {return m_BUTTON_HEIGHT;}
	short getBtnWidth() const {return m_BUTTON_WIDTH;}
	short getInputWidth() const {return m_INPUT_WIDTH;}

	void setRect(HWND frmHWND){GetWindowRect(frmHWND, &m_WindowDimensions);}
	short getBottom() const {return m_WindowDimensions.bottom;}
	short getTop() const {return m_WindowDimensions.top;}
	short getRight() const {return m_WindowDimensions.right;}
	short getLeft() const {return m_WindowDimensions.left;}
	short getPort() const {return m_PORT;}

	void setButtonDefault();
	void setButtonXPos(short x){m_ButtonXPos += x;}
	void setButtonYPos(short y){m_ButtonYPos += y;}
	short getButtonXPos() const {return m_ButtonXPos;}
	short getButtonYPos() const {return m_ButtonYPos;}

	void setScreen(Screen screenName){m_Screen = screenName;}
	Screen getScreen() const {return m_Screen;}
	void setSubScreen(SubScreen screenName){m_SubScreen = screenName;}
	SubScreen getSubScreen() const {return m_SubScreen;}

	bool isAdmin;

private:
	static const short m_WINDOW_HEIGHT = 725;
	static const short m_WINDOW_WIDTH = 1200;
	static const short m_WINDOW_X_POSITION = NULL;
	static const short m_WINDOW_Y_POSITION = NULL;
	static const short m_WINDOW_PADDING = 25;
	static const short m_BUTTON_HEIGHT = 25;
	static const short m_BUTTON_WIDTH = 100;
	static const short m_INPUT_WIDTH = 200;
	static const short m_PORT = 3306;
	RECT m_WindowDimensions;

	short m_ButtonXPos;
	short m_ButtonYPos;

	Screen m_Screen;
	SubScreen m_SubScreen;


};