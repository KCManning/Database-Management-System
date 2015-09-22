#include "Inclusion.h"

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	mysql_init(&queries.mysql);
	global.isAdmin = false;

	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	frmHWND = CreateWindowEx(NULL,
		"WindowClass1",    // name of the window class
		"Xanadu Invoice Management System",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		CW_USEDEFAULT,    // x-position of the window
		CW_USEDEFAULT,    // y-position of the window
		global.getWidth(),    // width of the window
		global.getHeight(),    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	// display the window on the screen
	ShowWindow(frmHWND, SW_SHOWMAXIMIZED);

	global.setRect(frmHWND);
	// enter the main loop:
	// this struct holds Windows event messages
	MSG msg;

	if (!mysql_real_connect(&queries.mysql,"localhost","root","root","mydb",global.getPort(),NULL,NULL)) 
	{ 

		short shtInterfaceX = global.getPadding();
		short shtInterfaceY = global.getPadding();

		shtInterfaceY += global.getBtnHeight() + global.getPadding() + global.getBtnHeight() + global.getPadding()
			+ global.getBtnHeight() + global.getBtnHeight() + global.getPadding() + global.getBtnHeight() + global.getPadding();

		lblInvoiceTag = CreateWindow("STATIC", " Error: Failed to connect to database.", 
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			shtInterfaceX, shtInterfaceY,
			global.getInputWidth() * 2, global.getBtnHeight(),
			frmHWND, NULL, NULL, NULL);
	}

	// wait for the next message in the queue, store the result in 'msg'
	while(GetMessage(&msg, NULL, NULL, NULL))
	{
		// translate keystroke messages into the right format
		TranslateMessage(&msg);

		// send the message to the WindowProc function
		DispatchMessage(&msg);

	}

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND frmHWND, UINT message, WPARAM wParam, LPARAM lParam)
{
	//	PAINTSTRUCT ps;
	//HDC hdc;

	// sort through and find what code to run for the message given
	switch(message)
	{
		//This message is read only when the program is started
	case WM_CREATE:
		{
			fCreatePanels(frmHWND);
			global.setScreen(Login);
			fCreateLoginScreen(frmHWND);
			break;
		}

		//this message reads in the user command.
	case WM_COMMAND:

		switch(global.getScreen())
		{
		case Admin:
			switch(LOWORD(wParam))
			{
#pragma region Divisions
			case 811:
				{
					char divisionName[20];
					GetWindowText(txtPeriodStart, divisionName, 20);

					string name;
					stringstream ss;

					ss << divisionName;
					ss >> name;

					queries.stateInsert = "INSERT INTO";
					queries.table = " divisions ";
					queries.whereStatement = " (Div_Name) VALUES ('" + name + "')";
					queries.query = queries.stateInsert + queries.table + queries.whereStatement + ";";

					const char *myQuery = queries.query.c_str();

					if(name.empty() || mysql_query(&queries.mysql, myQuery))
						::MessageBox(frmHWND, "Error in entering information.\nPlease try again.", NULL, NULL);
					else
					{
						::MessageBox(frmHWND, "New Division Successfully Added!", NULL, NULL);
						SetWindowText(txtPeriodStart, (""));
					}
					break;
				}
			case 812:
				{
					char divisionName[20];
					GetWindowText(txtPeriodStart, divisionName, 20);

					string name;
					stringstream ss;

					ss << divisionName;
					ss >> name;

					queries.stateSelect = "SELECT Div_Name";
					queries.table = " FROM divisions ";
					queries.whereStatement = " WHERE Div_Name='";
					queries.query = queries.stateSelect + queries.table + queries.whereStatement + name + "';";

					const char *myQuery = queries.query.c_str();

					if(name.empty() || mysql_query(&queries.mysql, myQuery))
						::MessageBox(frmHWND, "Error in entering information.\nPlease try again.", NULL, NULL);
					else
					{
						queries.result = mysql_store_result(&queries.mysql);
						while ((queries.row = mysql_fetch_row(queries.result)))
						{
							string results = "Division: " + name + " exists.";
							const char *divName = results.c_str();
							::MessageBox(frmHWND, divName, NULL, NULL);
						}
					}

					break;
				}
#pragma endregion

#pragma region Employees
			case 831:
				break;
			case 832:
				break;
#pragma endregion

#pragma region Units
			case 821:
				break;
			case 822:
				break;
#pragma endregion

			case 801:
				if(global.getSubScreen() != Employee)
				{
					fDestoryElements();
					global.setSubScreen(Employee);
					fCreateEmployeeScreen(frmHWND);
				}
				break;

			case 802:
				if(global.getSubScreen() != UnitNum)
				{
					fDestoryElements();
					global.setSubScreen(UnitNum);
					fCreateUnitScreen(frmHWND);
				}
				break;

			case 803:
				if(global.getSubScreen() != Division)
				{
					fDestoryElements();
					global.setSubScreen(Division);
					fCreateDivisionScreen(frmHWND);

				}
				break;

			case NULL:
			case 123:
				{
					break;
				}

			default:
				{
					global.setScreen(NoScreen);
					fDestoryElements();
				}
			}
			break;

		case Invoice:
			if(LOWORD(wParam) != 1)
			{
				fDestoryElements();
				//fDestoryInvoiceScreen();
			}
			break;

		case Vendor:
			if(LOWORD(wParam) == 202)
			{

				break;
			}
			if(LOWORD(wParam) == NULL || LOWORD(wParam) == 123)
			{
				break;
			}

			if(LOWORD(wParam) != 2)
			{
				fDestoryElements();
				//fDestoryVendorScreen();
			}
			break;

		case Contractor:
			if(LOWORD(wParam) != 4)
			{
				fDestoryElements();
				//fDestoryReportScreen();
			}
			break;

		case Contract:
			if(LOWORD(wParam) != 3)
			{
				fDestoryElements();
				//fDestoryContractScreen();
			}
			break;

		case Report:
			if(LOWORD(wParam) != 5)
			{
				fDestoryElements();
				//fDestoryReportScreen();
			}
			break;

#pragma region Login
		case Login:
			if(LOWORD(wParam) == 601)
			{
				char userName[10];
				GetWindowText(txtPeriodStart, userName, 10);
				char password[10];
				GetWindowText(txtPeriodEnd, password, 10);

				string user;
				stringstream ss;

				ss << userName;
				ss >> user;

				queries.stateSelect = "SELECT ";
				queries.table = " FROM employees";
				queries.whereStatement = " WHERE Emp_User_Name='" + user;
				queries.query = queries.stateSelect + "Emp_Password,Emp_Auth_Level"
					+ queries.table + queries.whereStatement + "';";

				const char *myQuery = queries.query.c_str();
				if(mysql_query(&queries.mysql, myQuery));

				//queries.row[0] = " ";
				queries.result = mysql_store_result(&queries.mysql);
				int validResults = 0;
				while ((queries.row = mysql_fetch_row(queries.result)))
				{
					validResults++;
					if(!strcmp(queries.row[0], password))
					{
						if(!strcmp(queries.row[1], "Admin"))
							global.isAdmin = true;

						fDestoryElements();
						fDestoryLoginScreen();
						global.setScreen(NoScreen);
						fCreateFauxTabs(frmHWND);
					}//end if
					else
					{
						SetWindowText(txtPeriodStart, (""));
						SetWindowText(txtPeriodEnd, (""));
						::MessageBox(frmHWND,
							"Invalid Username/Password Combination.\nSee manual for additional help.",
							NULL, NULL);
					}//end else
				}//end while
				if(!validResults)
				{						
					SetWindowText(txtPeriodStart, (""));
					SetWindowText(txtPeriodEnd, (""));
					::MessageBox(frmHWND,
						"Invalid Username/Password Combination.\nSee manual for additional help.",
						NULL, NULL);

				}

			}
			else if(LOWORD(wParam) == 602)
			{
				SetWindowText(txtPeriodStart, (""));
				SetWindowText(txtPeriodEnd, (""));
			}

			break;
#pragma endregion
		}

		switch (LOWORD(wParam))
		{
		case 0:
			break;

		case 1:
			if(global.getScreen() != Invoice)
			{
				global.setScreen(Invoice);
				fCreateInvoiceScreen(pnlHWND);
			}
			break;

		case 2:
			if(global.getScreen() != Vendor)
			{
				global.setScreen(Vendor);
				fCreateVendorScreen(frmHWND);
			}
			break;

		case 3:
			if(global.getScreen() != Contract)
			{
				global.setScreen(Contract);
				fCreateContractScreen(pnlHWND);
			}
			break;

		case 4:
			if(global.getScreen() != Contractor)
			{
				global.setScreen(Contractor);
				fCreateContractorScreen(pnlHWND);
			}
			break;

		case 5:
			if(global.getScreen() != Report)
			{
				global.setScreen(Report);
				fCreateReportScreen(pnlHWND);
			}
			break;

		case 6:
			global.isAdmin = false;
			fDestoryFauxTabs();
			global.setScreen(Login);
			fCreateLoginScreen(frmHWND);
			break;

		case 7:
			DestroyWindow(frmHWND);
			break;

		case 8:
			if(global.getScreen() != Admin)
			{
				global.setScreen(Admin);
				fCreateAdminScreen(frmHWND);
			}

			break;

		case 202:
			//switch(HIWORD(wParam)) // Find out what message it was
			//{
			//case CBN_DROPDOWN:

			//	cboCountries = GetDlgItem(frmHWND, 202);

			//	for(int Count = 0; Count < 12; Count++)
			//	{
			//		SendMessage(cboCountries,
			//			CB_ADDSTRING,
			//			0,
			//			reinterpret_cast<LPARAM>((LPCTSTR)Countries[Count]));
			//	}
			//	UpdateWindow(pnlHWND);
			//	break;
			//}

			break;
		}

		UpdateWindow(frmHWND);
		break;

		// this message is read when the window is closed
	case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage(NULL);
			return EXIT_SUCCESS;
		}
		break;
	}

	//UpdateWindow(pnlHWND);

	/*global.setRect(frmHWND);
	global.setButtonDefault();*/


	// Handle any messages the switch statement didn't
	return DefWindowProc (frmHWND, message, wParam, lParam);
}

#pragma region Create


void fCreateLoginScreen(HWND frmWindow)
{
	short shtInterfaceX = global.getPadding();
	short shtInterfaceY = global.getPadding();

	lblContractTag = CreateWindow("STATIC", "   Login", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblDiscription = CreateWindow("STATIC", " Welcome to the Bank of Xanadu Contract Management System\n\n"
		" Please enter your Username and Password below to continue", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() * 2 + global.getBtnWidth(), global.getBtnHeight() + global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding() + global.getBtnHeight();

	lblHourlyRate = CreateWindow("STATIC", " Username: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() / 2, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX +=  (global.getInputWidth() / 2) + global.getPadding();

	txtPeriodStart = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX,
		shtInterfaceY,
		global.getInputWidth() / 2, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX +=  global.getBtnWidth() + global.getPadding();

	lblPeriod = CreateWindow("STATIC", " Password: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() / 2, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX +=  (global.getInputWidth() / 2) + global.getPadding();

	txtPeriodEnd = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD,
		shtInterfaceX,
		shtInterfaceY,
		global.getInputWidth() / 2, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = global.getPadding();
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	btnSearch = CreateWindow("BUTTON", "&Login", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX,
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 601, NULL, NULL);

	shtInterfaceX += global.getPadding() + global.getBtnWidth();

	btnSubmit = CreateWindow("BUTTON", "&Clear", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX,
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 602, NULL, NULL);

	shtInterfaceX += global.getPadding() + global.getBtnWidth();

	btnExit = CreateWindow("BUTTON", "&Exit", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX,
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 7, NULL, NULL);
}

void fCreatePanels(HWND frmWindow)
{
	global.setRect(frmHWND);
	//short panelLength = (global.getRight() - global.getLeft());
	//short panelHeight = (global.getBottom() - global.getTop());

	pnlStyle = CreateWindow("Static", "", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		NULL, NULL,
		global.getWidth(),    // width of the window
		global.getHeight(),    // height of the window
		frmWindow, NULL, NULL, NULL);

	pnlHWND = CreateWindow("Static", "", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		NULL, NULL,
		global.getWidth(),    // width of the window
		global.getHeight() - global.getBtnWidth(),    // height of the window
		frmWindow, NULL, NULL, NULL);

	lblTeamName  = CreateWindow("STATIC", " Developed by:\n"
		"\tTeam Sidewall\n\n"
		" Jason Speaks\n\tProject Manager\n"
		" Kevin Manning\n\tLead Developer\n"
		" Eric Gabrielle\n\tTesting Coordinator\n"
		" Frank Curzi\n\tTraining Coordinator", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getWidth() + global.getPadding(),
		global.getHeight() - global.getBtnHeight() * 11 - global.getPadding(),
		global.getInputWidth(), global.getBtnHeight() * 8,
		frmWindow, NULL, NULL, NULL);

	lblVersion  = CreateWindow("STATIC", "  Version:\n\t1.3.0\n"
		"  Released:\n"
		"\t06 / 11 / 2015\n", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getWidth() + global.getPadding(),
		global.getHeight() - global.getBtnHeight() * 3,
		global.getInputWidth(), global.getBtnHeight() * 3,
		frmWindow, NULL, NULL, NULL);
}

void fCreateFauxTabs(HWND frmWindow)
{
	global.setButtonDefault();

	btnInvoice = CreateWindow("BUTTON", "&Invoice", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getButtonXPos(), global.getButtonYPos(),
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 1, NULL, NULL);

	global.setButtonXPos(global.getPadding() + global.getBtnWidth());

	btnVendor = CreateWindow("BUTTON", "&Vendor", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getButtonXPos(), global.getButtonYPos(),
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 2, NULL, NULL);

	global.setButtonXPos(global.getPadding() + global.getBtnWidth());

	btnContract = CreateWindow("BUTTON", "&Contract", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getButtonXPos(), global.getButtonYPos(),
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 3, NULL, NULL);

	global.setButtonXPos(global.getPadding() + global.getBtnWidth());

	btnContractor = CreateWindow("BUTTON", "&Contractor", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getButtonXPos(), global.getButtonYPos(),
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 4, NULL, NULL);

	global.setButtonXPos(global.getPadding() + global.getBtnWidth());

	btnReport = CreateWindow("BUTTON", "&Report", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getButtonXPos(), global.getButtonYPos(),
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 5, NULL, NULL);

	global.setButtonXPos(global.getPadding() + global.getBtnWidth());
	if(global.isAdmin)
	{
		btnAdmin = CreateWindow("BUTTON", "&Admin", 
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			global.getButtonXPos(), global.getButtonYPos(),
			global.getBtnWidth(), global.getBtnHeight(),
			frmWindow, (HMENU) 8, NULL, NULL);

		global.setButtonXPos(global.getPadding() + global.getBtnWidth());
	}

	btnLogout = CreateWindow("BUTTON", "&Logout", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getButtonXPos(), global.getButtonYPos(),
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 6, NULL, NULL);

	global.setButtonXPos(global.getPadding() + global.getBtnWidth());

	btnExit = CreateWindow("BUTTON", "E&xit", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getButtonXPos(), global.getButtonYPos(),
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 7, NULL, NULL);


}

void fCreateInvoiceScreen(HWND frmWindow)
{
	short resetDefault = global.getPadding();
	short shtInterfaceX = resetDefault;
	short shtInterfaceY = resetDefault;

	lblInvoiceTag = CreateWindow("STATIC", "   Invoices", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblContractor = CreateWindow("STATIC", " Vendor: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	cmbUnit = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	lblContractorFirst = CreateWindow("STATIC", " Contact: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	cmbContractor = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getBtnWidth();

	lblEnd = CreateWindow("STATIC", " Previous Invoices: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();
	shtInterfaceX = resetDefault;

	lblInvoiceNumber = CreateWindow("STATIC", " Invoice Number: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	txtInvoiceNumber = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();
	//shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblInvoiceDate = CreateWindow("STATIC", " Issued Date: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtInvoiceDate = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getBtnWidth();

	lstResults = CreateWindow("LISTBOX", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth() + global.getPadding(), global.getInputWidth(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblPeriod = CreateWindow("STATIC", " Period: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtPeriodStart = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX,
		shtInterfaceY,
		global.getBtnWidth() - global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth();

	txtPeriodEnd = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() - global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth();

	lblMasterNum = CreateWindow("STATIC", " Status: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	cmbStatus = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblChargeUnit = CreateWindow("STATIC", " Rate: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() / 2, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += (global.getBtnWidth() / 2) + global.getPadding();

	txtChargeUnit = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() - global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth();

	lblContractorLast = CreateWindow("STATIC", " Amount: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += (global.getInputWidth() / 3) + global.getPadding();

	txtContractorLast = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() - global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth();

	lblStart = CreateWindow("STATIC", " Unit #: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() / 2, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() / 2 + global.getPadding();

	cmbStates = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblContractNumber = CreateWindow("STATIC", " Accrual: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding() + global.getPadding();

	txtContractNumber = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding() + global.getPadding();

	lblHourlyRate = CreateWindow("STATIC", " Date Paid: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding() + global.getPadding();

	txtHourlyRate = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding() , global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblDiscription = CreateWindow("STATIC", " Notes: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtDiscription = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth() , global.getBtnWidth(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += (global.getBtnHeight() + global.getPadding()) * 4;

	btnSubmit = CreateWindow("BUTTON", "S&ubmit", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);

	btnSearch = CreateWindow("BUTTON", "Searc&h", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth() + global.getPadding() + global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);
}

void fCreateVendorScreen(HWND frmWindow)
{
	const char* states[50] = {"AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA", "HI",
		"ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS", "MO", "MT",
		"NE", "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC", "SD",
		"TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"};

	short shtInterfaceX = global.getPadding();
	short shtInterfaceY = global.getPadding();

	lblContractTag = CreateWindow("STATIC", "   Vendor", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblContractorFirst = CreateWindow("STATIC", " Vendor Name: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	txtContractorFirst = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getInputWidth() + global.getPadding();

	lblEnd = CreateWindow("STATIC", " Vendor Search: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = global.getPadding();
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblContractorLast = CreateWindow("STATIC", " Vendor Contact Number: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	txtContractorLast = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getInputWidth() + global.getPadding();

	lstResults = CreateWindow("LISTBOX", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth() + global.getPadding(), global.getInputWidth(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = global.getPadding();
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblChargeUnit = CreateWindow("STATIC", " Vendor Email: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	txtChargeUnit = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX + global.getInputWidth() + global.getPadding(), shtInterfaceY,
		global.getInputWidth() + global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblMasterNum = CreateWindow("STATIC", " Vendor Number: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	txtMasterNum = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX + global.getInputWidth() + global.getPadding(), shtInterfaceY,
		global.getInputWidth() + global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblBankManager = CreateWindow("STATIC", " Vendor Street Address: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	txtBankManager = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX + global.getInputWidth() + global.getPadding(), shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblHourlyRate = CreateWindow("STATIC", " State: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	cmbStates = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWNLIST | WS_OVERLAPPED | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX + (global.getInputWidth() / 3) + global.getPadding(),
		shtInterfaceY, global.getBtnWidth(), global.getBtnHeight(),
		frmWindow,(HMENU) 202, NULL, NULL);

	for(int i = 0; i < 50; i++)
	{
		ComboBox_AddString(cmbStates, states[i]);
	}

	//ComboBox_SetMinVisible(cmbStates, 3);
	SendMessage((cmbStates), CB_SETCURSEL, (WPARAM) 46, 0);

	lblStart = CreateWindow("STATIC", " Zip: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX + global.getInputWidth() + global.getPadding(), shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	txtStart = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX + global.getInputWidth() + (global.getPadding() * 2) + (global.getInputWidth() / 3),
		shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += (global.getBtnHeight() + global.getPadding()) * 4;

	btnSubmit = CreateWindow("BUTTON", "S&ubmit", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);

	btnSearch = CreateWindow("BUTTON", "Searc&h", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth() + global.getPadding() + global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);



}

void fCreateContractScreen(HWND frmWindow)
{
	short resetDefault = global.getPadding();
	short shtInterfaceX = resetDefault;
	short shtInterfaceY = resetDefault;

	lblContractTag = CreateWindow("STATIC", "   Contract", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblInvoiceTag = CreateWindow("STATIC", " Contact Name: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtInvoiceTag = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	lblInvoiceNumber = CreateWindow("STATIC", " Phone: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += (global.getInputWidth() / 3) + global.getPadding();

	txtInvoiceNumber = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getBtnWidth();

	lblBankManager = CreateWindow("STATIC", " Search Results: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblInvoiceDate = CreateWindow("STATIC", " Email: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtInvoiceDate	= CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		(global.getInputWidth() + global.getPadding()) * 2, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() * 3;

	lstResults = CreateWindow("LISTBOX", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth() + global.getPadding(), global.getInputWidth(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblContractorFirst = CreateWindow("STATIC", " Contract Number: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding() * 2;

	txtContractorFirst = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding() * 2;

	lblContractorLast = CreateWindow("STATIC", " Vendor: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding() * 2;

	cmbContractor = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblChargeUnit = CreateWindow("STATIC", " Decription of work: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() - global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth();

	txtChargeUnit = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth() - global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblStart = CreateWindow("STATIC", " Period: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() - global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth();

	txtStart = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtEnd = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	lblEnd = CreateWindow("STATIC", " Unit #: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() - global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth();

	cmbStates = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblHourlyRate = CreateWindow("STATIC", " Hourly Rate ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtHourlyRate = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	lblFeeMax = CreateWindow("STATIC", " Fee Maximum: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	txtFeeMax = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblDiscription = CreateWindow("STATIC", " Notes: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtDiscription = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() * 2 + global.getPadding() * 2, global.getBtnWidth(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += (global.getBtnHeight() + global.getPadding()) * 4;

	btnSubmit = CreateWindow("BUTTON", "S&ubmit", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);

	btnSearch = CreateWindow("BUTTON", "Searc&h", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth() + global.getPadding() + global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);
}

void fCreateContractorScreen(HWND frmWindow)
{

	short shtInterfaceX = global.getPadding();
	short shtInterfaceY = global.getPadding();

	lblContractTag = CreateWindow("STATIC", "   Contractor", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblContractorFirst = CreateWindow("STATIC", " Contractor Name: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	txtContractorFirst = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getInputWidth() + global.getPadding();

	lblInvoiceTag = CreateWindow("STATIC", " Search Results: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = global.getPadding();
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblContractorLast = CreateWindow("STATIC", " Phone Number: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	txtContractorLast = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getInputWidth() + global.getPadding();

	lstResults = CreateWindow("LISTBOX", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth() + global.getPadding(), global.getInputWidth(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = global.getPadding();
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblChargeUnit = CreateWindow("STATIC", " Email: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	txtChargeUnit = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX + global.getInputWidth() + global.getPadding(), shtInterfaceY,
		global.getInputWidth() + global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblMasterNum = CreateWindow("STATIC", " Vendor: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	cmbStatus = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX + (global.getInputWidth() / 3) + global.getPadding(),
		shtInterfaceY, global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblBankManager = CreateWindow("STATIC", " Street Address: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	txtBankManager = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX + global.getInputWidth() + global.getPadding(), shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblHourlyRate = CreateWindow("STATIC", " State: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	cmbStates = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX + (global.getInputWidth() / 3) + global.getPadding(),
		shtInterfaceY, global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	lblStart = CreateWindow("STATIC", " Zip: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX + global.getInputWidth() + global.getPadding(), shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	txtStart = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX + global.getInputWidth() + (global.getPadding() * 2) + (global.getInputWidth() / 3),
		shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += (global.getBtnHeight() + global.getPadding()) * 4;

	btnSubmit = CreateWindow("BUTTON", "S&ubmit", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);

	btnSearch = CreateWindow("BUTTON", "Searc&h", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth() + global.getPadding() + global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);


}

void fCreateReportScreen(HWND frmWindow)
{
	short shtInterfaceX = global.getPadding();
	short shtInterfaceY = global.getPadding();

	lblContractTag = CreateWindow("STATIC", "   Reports", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblHourlyRate = CreateWindow("STATIC", " Report Type: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() / 2, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX +=  (global.getInputWidth() / 2) + global.getPadding();

	cmbStates = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX,
		shtInterfaceY, global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX +=  global.getBtnWidth() + global.getPadding();

	lblPeriod = CreateWindow("STATIC", " Period: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX +=  (global.getInputWidth() / 3) + global.getPadding();

	txtPeriodStart = CreateWindow("EDIT", "Start Date",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX,
		shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX +=  (global.getInputWidth() / 3) + global.getPadding();

	txtPeriodEnd = CreateWindow("EDIT", "End Date",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX,
		shtInterfaceY,
		global.getInputWidth() / 3, global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = global.getPadding();
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	btnSearch = CreateWindow("BUTTON", "Searc&h", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);

	btnSubmit = CreateWindow("BUTTON", "&Print", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth() + global.getPadding() + global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();


	lstResults = CreateWindow("LISTBOX", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() * 5, global.getBtnWidth() * 5,
		frmWindow, NULL, NULL, NULL);
}

void fCreateUnitScreen(HWND frmWindow)
{
	short resetDefault = global.getPadding();
	short shtInterfaceX = resetDefault;
	short shtInterfaceY = resetDefault;

	lblContractTag =  CreateWindow("STATIC", "   Unit Entry:", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getPadding() + global.getBtnWidth();

	lblBankManager = CreateWindow("STATIC", "   Division Name:", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	cmbStates = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX,
		shtInterfaceY, global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	lblChargeUnit = CreateWindow("STATIC", "   Unit Number:", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	txtPeriodStart = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX,
		shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getPadding() + global.getBtnWidth();

	btnSubmit = CreateWindow("BUTTON", "S&ubmit", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);

	btnSearch = CreateWindow("BUTTON", "Searc&h", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth() + global.getPadding() + global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);

}

void fCreateDivisionScreen(HWND frmWindow)
{
	short resetDefault = global.getPadding();
	short shtInterfaceX = resetDefault;
	short shtInterfaceY = resetDefault;

	lblContractTag =  CreateWindow("STATIC", "   Division Entry:", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getPadding() + global.getBtnWidth();

	lblBankManager = CreateWindow("STATIC", "   Division Name:", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getInputWidth() + global.getPadding();

	txtPeriodStart = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX,
		shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getPadding() + global.getBtnWidth();

	btnSubmit = CreateWindow("BUTTON", "S&ubmit", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 811, NULL, NULL);

	btnSearch = CreateWindow("BUTTON", "Searc&h", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth() + global.getPadding() + global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 812, NULL, NULL);

}

void fCreateEmployeeScreen(HWND frmWindow)
{
	short resetDefault = global.getPadding();
	short shtInterfaceX = resetDefault;
	short shtInterfaceY = resetDefault;

	lblContractTag = CreateWindow("STATIC", "   Employee Entry", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblInvoiceTag = CreateWindow("STATIC", " First Name: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtInvoiceTag = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblInvoiceNumber = CreateWindow("STATIC", " Last Name: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtInvoiceNumber = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += (global.getInputWidth() + global.getBtnWidth()) * 2;

	lblBankManager = CreateWindow("STATIC", " Search Results: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblContractorFirst = CreateWindow("STATIC", " Contact Number: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding() * 2;

	txtContractorFirst = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	//shtInterfaceX += global.getBtnWidth() + global.getPadding();
	shtInterfaceX += global.getInputWidth() * 3 - global.getPadding();

	lstResults = CreateWindow("LISTBOX", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth() + global.getInputWidth() + global.getPadding(), global.getInputWidth(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblContractorLast = CreateWindow("STATIC", " Auth Level:", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() + global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding() * 2;

	cmbContractor = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	lblEnd = CreateWindow("STATIC", " Title:", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth() - global.getPadding(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth();

	cmbStates = CreateWindow("COMBOBOX", "", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblHourlyRate = CreateWindow("STATIC", " Username: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtHourlyRate = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	lblFeeMax = CreateWindow("STATIC", " Password: ", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX += global.getBtnWidth() + global.getPadding();

	txtFeeMax = CreateWindow("EDIT", "",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getInputWidth(), global.getBtnHeight(),
		frmWindow, NULL, NULL, NULL);

	shtInterfaceX = resetDefault;
	shtInterfaceY += global.getBtnHeight() + global.getPadding();

	btnSubmit = CreateWindow("BUTTON", "S&ubmit", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);

	btnSearch = CreateWindow("BUTTON", "Searc&h", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		global.getInputWidth() + global.getPadding() + global.getInputWidth(),
		shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 123, NULL, NULL);

}

void fCreateAdminScreen(HWND frmWindow)
{
	short shtInterfaceX = global.getInputWidth();
	short shtInterfaceY = global.getHeight() - global.getInputWidth() - global.getPadding();

	btnEmployee = CreateWindow("BUTTON", "Em&ployee", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 801, NULL, NULL);

	shtInterfaceX += global.getPadding() + global.getBtnWidth();

	btnUnit = CreateWindow("BUTTON", "&Unit", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 802, NULL, NULL);

	shtInterfaceX += global.getPadding() + global.getBtnWidth();

	btnDivision = CreateWindow("BUTTON", "&Division", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		shtInterfaceX, shtInterfaceY,
		global.getBtnWidth(), global.getBtnHeight(),
		frmWindow, (HMENU) 803, NULL, NULL);



}

#pragma endregion

#pragma region Destroy
void fDestoryFauxTabs()
{
	DestroyWindow(btnInvoice);
	DestroyWindow(btnContract);
	DestroyWindow(btnVendor);
	DestroyWindow(btnInvoice);
	DestroyWindow(btnReport);
	DestroyWindow(btnContractor);
	DestroyWindow(btnAdmin);
	DestroyWindow(btnLogout);
	DestroyWindow(btnExit);

}

void fDestoryLoginScreen()
{
	DestroyWindow(lblContractTag);
	DestroyWindow(lblPeriod);
	DestroyWindow(lblHourlyRate);

	DestroyWindow(txtPeriodStart);
	DestroyWindow(txtPeriodEnd);

	DestroyWindow(btnSubmit);
	DestroyWindow(btnSearch);
	DestroyWindow(btnExit);


	UpdateWindow(frmHWND);
}

void fDestoryElements()
{
#pragma region Labels
	DestroyWindow(lblInvoiceTag);
	DestroyWindow(lblContractor);
	DestroyWindow(lblInvoiceNumber);
	DestroyWindow(lblInvoiceDate);
	DestroyWindow(lblMasterNum);
	DestroyWindow(lblChargeUnit);
	DestroyWindow(lblPeriod);
	DestroyWindow(lblContractTag);
	DestroyWindow(lblContractorFirst);
	DestroyWindow(lblContractorLast);
	DestroyWindow(lblHourlyRate);
	DestroyWindow(lblStart);
	DestroyWindow(lblFeeMax);
	DestroyWindow(lblDiscription);
	DestroyWindow(lblBankManager);
	DestroyWindow(lblContractNumber);
	DestroyWindow(lblEnd);
#pragma endregion

#pragma region Text Boxes
	DestroyWindow(txtInvoiceTag);
	DestroyWindow(txtContractor);
	DestroyWindow(txtInvoiceNumber);
	DestroyWindow(txtInvoiceDate);
	DestroyWindow(txtMasterNum);
	DestroyWindow(txtChargeUnit);
	DestroyWindow(txtPeriodStart);
	DestroyWindow(txtPeriodEnd);
	DestroyWindow(txtContractorFirst);
	DestroyWindow(txtContractorLast);
	DestroyWindow(txtContractNumber);
	DestroyWindow(txtBankManager);
	DestroyWindow(txtHourlyRate);
	DestroyWindow(txtStart);
	DestroyWindow(txtEnd);
	DestroyWindow(txtFeeMax);
	DestroyWindow(txtDiscription);
#pragma endregion

#pragma region Buttons, Combo Boxes, and Lists
	DestroyWindow(btnSubmit);
	DestroyWindow(btnSearch);
	if(global.getScreen() == Login)
		DestroyWindow(btnExit);

	if(global.getScreen() != Admin)
	{
		DestroyWindow(btnUnit);
		DestroyWindow(btnDivision);
		DestroyWindow(btnEmployee);
	}

	DestroyWindow(cmbStates);
	DestroyWindow(cmbContractor);
	DestroyWindow(cmbStatus);
	DestroyWindow(cmbUnit);

	DestroyWindow(lstResults);

#pragma endregion

}
#pragma endregion

#pragma region Queries
void testing()
{

}
#pragma endregion