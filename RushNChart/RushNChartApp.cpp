//MainFrameApp.cpp

#include "RushNChartApp.h"
#include "RushNChart.h"


RushNChartApp rushNChartApp;

BOOL RushNChartApp::InitInstance()	{
	RushNChart* rushNChart = new RushNChart ;
	rushNChart->Create( 0, 0 ) ;
	rushNChart->ShowWindow(SW_SHOW) ;
	rushNChart->UpdateWindow() ;
	m_pMainWnd = rushNChart ;
	 
	return TRUE ;
}
