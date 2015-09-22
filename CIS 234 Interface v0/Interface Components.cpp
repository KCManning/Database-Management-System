//#include <windows.h>
//
//LPCTSTR WndClassName = "firstwindow";
//HWND hwnd = NULL;
//
//const int Width  = 800;
//const int Height = 600;
//
//bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);
//
//int messageloop();
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
//{
//	if(!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
//	{
//		MessageBox(NULL, "Window Initialization - Failed", "Error", MB_OK);
//
//		return EXIT_SUCCESS;
//	}
//
//	messageloop();
//
//	return EXIT_SUCCESS;
//}
//
//bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed)
//{
//	typedef struct _WNDCLASS
//	{
//		UINT cbSize;
//		UINT style;
//		WNDPROC lpfnWndProc;
//		int cbClsExtra;
//		int cbWndExtra;
//		HANDLE hInstance;
//		HICON hIcon;
//		HCURSOR hCursor;
//		HBRUSH hbrBackground;
//		LPCTSTR lpszMenuName;
//		LPCTSTR lpszClassName;
//	} WNDCLASS;
//
//	WNDCLASSEX wc;
//
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = WndProc;
//	wc.cbClsExtra = NULL;
//	wc.cbWndExtra = NULL;
//	wc.hInstance = hInstance;
//	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = WndClassName;
//	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//	if (!RegisterClassEx(&wc))
//	{
//		MessageBox(NULL, "Error registering class", "Error", MB_OK | MB_ICONERROR);
//
//		return EXIT_FAILURE;
//	}
//
//	hwnd = CreateWindowEx(
//		NULL, WndClassName,"Window Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);
//
//	if (!hwnd)
//	{
//		MessageBox(NULL, "Error creating window", "Error", MB_OK | MB_ICONERROR);
//
//		return EXIT_FAILURE;
//	}
//
//	ShowWindow(hwnd, ShowWnd);
//	UpdateWindow(hwnd);
//
//	return true;
//}
//
//int messageloop()
//{
//	MSG msg;
//
//	ZeroMemory(&msg, sizeof(MSG));
//
//	while(true)
//	{
//		BOOL PeekMessageL(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
//
//		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
//		{
//			if (msg.message == WM_QUIT)
//				break;
//			TranslateMessage(&msg);	
//			DispatchMessage(&msg);
//		}
//		else
//		{
//			// run game code
//		}
//	}
//
//	return msg.wParam;
//}
//
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch( msg )
//	{
//	case WM_KEYDOWN:
//		if( wParam == VK_ESCAPE )
//		{
//			if(MessageBox(NULL, "Are you sure you want to exit?", "Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
//				DestroyWindow(hwnd);
//		}
//		return EXIT_SUCCESS;
//
//	case WM_DESTROY:
//		PostQuitMessage(NULL);
//		return EXIT_SUCCESS;
//
//	default:
//		break;
//	}
//
//	return DefWindowProc(hwnd, msg, wParam, lParam);
//}

//HWND frmHWND, btnRandomDots, btnShape, btnPicture, btnGradient, btnConnect, btnReset, btnExit, btnAcceptPopup,
//	pnlDrawingArea, lblInformation, frmUserInput, txtUserInput, lblInstructions, lblMessages;
//
//lblInstructions = CreateWindow("STATIC", "Enter the number of dots to draw:", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				intButtonYCord, intXCord, cintBUTTON_LENGTH, (cintBUTTON_HEIGHT * 2) + cintPADDING,
//				frmHWND, NULL, NULL, NULL);
//
//			intXCord += cintPADDING + (cintBUTTON_HEIGHT * 2);
//
//			txtUserInput = CreateWindow("EDIT", "1000",
//			WS_VISIBLE | WS_CHILD | WS_BORDER,
//			intButtonYCord, intXCord, cintBUTTON_LENGTH, cintBUTTON_HEIGHT,
//			frmHWND, (HMENU) 123, NULL, NULL);
//
//			intXCord += cintPADDING + cintBUTTON_HEIGHT;
//
//			btnRandomDots = CreateWindow("BUTTON", "&Random Dots", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				intButtonYCord, intXCord, cintBUTTON_LENGTH, cintBUTTON_HEIGHT,
//				frmHWND, (HMENU) 1 , NULL, NULL);
//
//			intXCord += cintPADDING + cintBUTTON_HEIGHT;
//
//			btnShape = CreateWindow("BUTTON", "&Draw Shapes", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				intButtonYCord, intXCord, cintBUTTON_LENGTH, cintBUTTON_HEIGHT,
//				frmHWND, (HMENU) 2, NULL, NULL);
//
//			intXCord += cintPADDING + cintBUTTON_HEIGHT;
//
//			btnPicture = CreateWindow("BUTTON", "Show &Picture", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				intButtonYCord, intXCord, cintBUTTON_LENGTH, cintBUTTON_HEIGHT,
//				frmHWND, (HMENU) 3, NULL, NULL);
//
//			pnlDrawingArea = CreateWindow("STATIC", "", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				cintPADDING, cintPADDING,
//				intButtonYCord - (cintPADDING * 2), intXCord + cintBUTTON_HEIGHT - cintPADDING,
//				frmHWND, NULL, NULL, NULL);
//
//			rect.left = cintPADDING;
//			rect.top = cintPADDING;
//			rect.right = intButtonYCord - cintPADDING;
//			rect.bottom = intXCord + cintBUTTON_HEIGHT;
//
//			intXCord += cintPADDING + cintBUTTON_HEIGHT;
//			
//			btnGradient = CreateWindow("BUTTON", "&Make Gradient", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				intButtonYCord, intXCord, cintBUTTON_LENGTH, cintBUTTON_HEIGHT,
//				frmHWND, (HMENU) 4, NULL, NULL);
//
//				lblMessages = CreateWindow("STATIC", "Well Hello There!", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				cintPADDING, intXCord,
//				intButtonYCord - (cintPADDING * 2), cintBUTTON_HEIGHT,
//				frmHWND, NULL, NULL, NULL);
//
//			intXCord += cintPADDING + cintBUTTON_HEIGHT;
//
//				btnConnect = CreateWindow("BUTTON", "&Connect", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				intButtonYCord, intXCord, cintBUTTON_LENGTH, cintBUTTON_HEIGHT,
//				frmHWND, (HMENU) 5, NULL, NULL);
//		
//				lblInformation = CreateWindow("STATIC", "What would YOU do for a Klondike bar?", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				cintPADDING, intXCord,
//				intButtonYCord - (cintPADDING * 2), cintBUTTON_LENGTH,
//				frmHWND, NULL, NULL, NULL);
//			
//			intXCord += cintPADDING + cintBUTTON_HEIGHT;
//
//				btnReset = CreateWindow("BUTTON", "Re&set", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				intButtonYCord, intXCord, cintBUTTON_LENGTH, cintBUTTON_HEIGHT,
//				frmHWND, (HMENU) 6, NULL, NULL);
//
//				intXCord += cintPADDING + cintBUTTON_HEIGHT;
//			
//			btnExit = CreateWindow("BUTTON", "&Exit", 
//				WS_VISIBLE | WS_CHILD | WS_BORDER,
//				intButtonYCord, intXCord, cintBUTTON_LENGTH, cintBUTTON_HEIGHT,
//				frmHWND, (HMENU) 7, NULL, NULL);
//
//
//			intXCord += cintPADDING + cintBUTTON_HEIGHT;
//			break;
//
//			cmbStates = CreateWindow("WX_COMBOBOX", "", 
//				CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_BORDER,
//				intButtonYCord, intXCord, cintBUTTON_LENGTH, cintBUTTON_HEIGHT,
//				frmHWND, (HMENU) 123, NULL, NULL);
//
//

//case 1:
//	GetWindowText(txtUserInput, charUserInput, 10);
//	intNumberOfDots = strtol(charUserInput, NULL, 10);
//	SetWindowText(lblInformation, ("Original System:\n"
//		"Operating System: Windows 8.1 64-bit (6.3, Build 9600) (9600.winblue_r3.140827-1500)\n"
//		"System Model: HP 15 Notebook PC\n"
//		"Processor: AMD A8-6410 APU with AMD Radeon R5 Graphics(4 CPUs), ~2.0GHz\n"
//		"Memory: 8192MB RAM"));
//	if (intNumberOfDots < 100 || intNumberOfDots > 1000000)
//	{
//		::MessageBox(frmHWND, "Please enter a number between 100 and 1,000,000!",
//			NULL, NULL);
//		break;
//	}

//void fCreateFauxTabs(HWND frmWindow)
//{
//        global.setButtonDefault();
// 
//        struct Button {HWND hwnd, const char  name};
//        Button buttons[] = {{&btnInvoice, "&Invoice"},
//                            {&btnContract, "&Contract"},
//                            {&btnVendor, "&Vendor"},
//                            {&btnReport, "&Report"},
//                            {&btnExit, "E&xit"}};
//
//        int buttonCount = sizeof(buttons)/sizeof(buttons[0]);
//        int buttonNum = 0;
//        for (auto&& button : buttons)
//        {
//           *button.hwnd = CreateWindow("BUTTON", button.name,
//                WS_VISIBLE | WS_CHILD | WS_BORDER,
//                global.getButtonXPos(), global.getButtonYPos(),
//                global.getBtnWidth(), global.getBtnHeight(),
//                frmWindow, (HMENU) buttonNum++, NULL, NULL);
// 
//           if (buttonNum != buttonCount)
//           {
//              global.setButtonXPos(global.getPadding() + global.getBtnWidth());          
//           }
//        }
//}

//struct WindowDestroy
//{
//  void operator()(HWND wnd) const
//  {
//      DestroyWindow(wnd);
//  }
//};
//
//typedef std::unique_ptr<void, WindowDestroy> WindowHandle;
//
//WindowHandle handle;
//
//handle.reset(CreateWindow(...)); //automatically destroys in its destructor!