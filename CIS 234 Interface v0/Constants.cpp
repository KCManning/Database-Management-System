#include "Constants.h"

Constants::Constants()
{
	m_WindowDimensions.top = NULL;
	m_WindowDimensions.bottom = NULL;
	m_WindowDimensions.right = NULL;
	m_WindowDimensions.left = NULL;
	setButtonDefault();
	m_Screen = NoScreen;
}

void Constants::setButtonDefault()
{

	//		global.getWidth(),    // width of the window
		//global.getHeight(),    // height of the window
	
	m_ButtonXPos = m_WindowDimensions.left + getPadding();
	m_ButtonYPos = getHeight() - getPadding() - getPadding();
}