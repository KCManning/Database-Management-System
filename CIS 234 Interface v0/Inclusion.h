#include "Queries.h"


#pragma region Window Definitions
//Initializing global variables.
Constants global;
Queries queries;

// the handle for the window, filled by a function
HWND frmHWND, pnlHWND, pnlStyle;

//Initalizes all of the buttons for the Invoice Interface
HWND btnSubmit, btnSearch, btnUnit, btnDivision, btnEmployee;

//Initalizes all of the buttons needed for the faux tabs
HWND btnContract, btnInvoice, btnVendor, btnReport, btnContractor, btnAdmin, btnLogout, btnExit;

//Initalizes all of the labels for the Invoice Interface
HWND lblInvoiceTag, lblContractor, lblInvoiceNumber, lblInvoiceDate, lblMasterNum, lblChargeUnit, lblPeriod, lblTeamName, lblVersion;

//Initalizes all of the txt boxes for the Invoice Interface
HWND txtInvoiceTag, txtContractor, txtInvoiceNumber, txtInvoiceDate, txtMasterNum, txtChargeUnit, txtPeriodStart, txtPeriodEnd;

//Initalizes all of the labels for the Contracts Interface
HWND lblContractTag, lblContractorFirst, lblContractorLast, lblContractNumber, lblHourlyRate, lblStart, lblEnd, lblFeeMax, lblDiscription, lblBankManager;

//Initalizes all of the txt boxes for the Contracts Interface
HWND txtContractTag, txtContractorFirst, txtContractorLast, txtContractNumber, txtHourlyRate, txtStart, txtEnd, txtFeeMax, txtDiscription, txtBankManager;

HWND cmbStates, cmbContractor, cmbStatus, cmbUnit, lstResults;

////Initalizes all of the labels for the Vendor Interface
//HWND lblInvoiceTag, lblContractor, lblInvoiceNumber, lblInvoiceDate, lblMasterNum, lblChargeUnit, lblPeriod;
//
////Initalizes all of the txt boxes for the Vendor Interface
//HWND txtInvoiceTag, txtContractor, txtInvoiceNumber, txtInvoiceDate, txtMasterNum, txtChargeUnit, txtPeriodStart, txtPeriodEnd;


//Prototyping
// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#pragma endregion

#pragma region Prototypes
void fCreatePanels(HWND frmWindow);
void fCreateFauxTabs(HWND frmWindow);
void fCreateInvoiceScreen(HWND frmWindow);
void fCreateContractScreen(HWND frmWindow);
void fCreateVendorScreen(HWND frmWindow);
void fCreateReportScreen(HWND frmWindow);
void fCreateLoginScreen(HWND frmWindow);
void fCreateUnitScreen(HWND frmWindow);
void fCreateDivisionScreen(HWND frmWindow);
void fCreateEmployeeScreen(HWND frmWindow);
void fCreateContractorScreen(HWND frmWindow);
void fCreateAdminScreen(HWND frmWindow);


void fDestoryFauxTabs();
void fDestoryInvoiceScreen();
void fDestoryContractScreen();
void fDestoryVendorScreen();
void fDestoryReportScreen();
void fDestoryLoginScreen();
void fDestoryElements();

void testing();
#pragma endregion