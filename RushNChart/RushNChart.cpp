//RushNChart.cpp
/*
	프로젝트명 : Rush & Chart
	파  일  명 : RushNChart.cpp
	작  성  일 : 2014년 06월 20일
	팀      명 : i5(five)
	팀      원 : 안영보 ( 팀장 ), 채형석, 김지수, 고요셉, 곽욱현 
*/
#include "RushNChart.h"
#include "resource.h"
#include <afxcmn.h>

#include "AfterRepeat.h"
#include "BeforeRepeat.h"
#include "Selection.h"
#include "Sequence.h"
#include "SwitchCase.h"
#include "Arrow.h"
#include "ColumnCountForm.h"

#include "PaperList.h"
#include "Paper.h"
#include "Chart.h"

#include "Select.h"
#include "Pen.h"

#include "CopySymbol.h"

#include "Sticker.h"
#include "Scroll.h"
#include "PreViewDlg.h"

#include <imm.h>
#pragma comment(lib, "imm32")

#include <afxdlgs.h>
#include <string>
using namespace std;

BEGIN_MESSAGE_MAP( RushNChart, CFrameWnd )
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()

	/********* 스크롤 ***********/
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	
	/********* 키보드 ***********/
	ON_WM_KEYDOWN( )

	/********* 입 력 ***********/
	ON_WM_CHAR()
	ON_MESSAGE( WM_IME_COMPOSITION, OnIMEComposition )

	/********* 마우스 ***********/
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()

	/********* 그리기 ***********/
	ON_WM_PAINT( )

	/********* 파 일 ***********/
	ON_COMMAND ( ID_NEW, OnNewPaperMenuClicked )
	ON_COMMAND ( ID_LOAD, OnLoadMenuClicked )
	ON_COMMAND ( ID_SAVE, OnSaveMenuClicked )
	ON_COMMAND ( ID_SAVE_AS,OnReNameSaveMenuClicked )
	ON_COMMAND ( ID_PRINT, OnPrintMenuClicked )
	ON_COMMAND ( ID_PRINT_PREVIEW, OnPreViewMenuClicked )
	ON_COMMAND ( ID_END, OnCloseMenuClicked )

	/********* 도 형 ***********/
	ON_COMMAND ( ID_SEQUENCE, OnSequenceMenuClicked )
	ON_COMMAND ( ID_BEFORE_REPEAT, OnBeforeRepeatMenuClicked )
	ON_COMMAND ( ID_AFTER_REPEAT, OnAfterRepeatMenuClicked )
	ON_COMMAND ( ID_SELECTION, OnSelectionMenuClicked )
	ON_COMMAND ( ID_SWITCH_CASE, OnSwitchCaseMenuClicked )
	ON_COMMAND ( ID_ARROW, OnArrowMenuClicked )

	/********* 특수문자 ***********/
	ON_COMMAND ( ID_NOT_EQUAL, OnNotEqualMenuClicked )
	ON_COMMAND ( ID_BETTER, OnBetterThanMenuClicked )
	ON_COMMAND ( ID_LESSER, OnLesserThanMenuClicked )

	/********* 도움말 ***********/
	ON_COMMAND ( ID_HELP, OnHelpInFoButtonClicked )

	/********* 우버튼 클릭 메뉴 *********/
	ON_COMMAND ( ID_CUT, OnCutMenuClicked )
	ON_COMMAND ( ID_COPY, OnCopyMenuClicked )
	ON_COMMAND ( ID_PASTE, OnPasteMenuClicked )
	ON_COMMAND ( ID_UNDO, OnUndoMenuClicked ) 
	ON_COMMAND ( ID_REDO, OnRedoMenuClicked )
	ON_COMMAND ( ID_MAKECHART, OnMakeChartButtonClicked )
	ON_COMMAND ( ID_RELEASECHART, OnReleaseChartButtonClicked )
	ON_COMMAND ( ID_SELECTALL, OnSelectAllMenuClicked )
	ON_COMMAND ( ID_DELETE, OnDeleteMenuClicked )

END_MESSAGE_MAP()


RushNChart::RushNChart(CWnd *parent)	{
	this->paper = NULL;
	this->select = NULL;
	this->pen = NULL;
	this->copySymbol = NULL;
	this->paperList = NULL;

	this->scroll = NULL ;
	this->preViewDlg = NULL;

	// 스크롤 초기화
	this->xPos =0;
	this->yPos =0;
	this->xMax = 100 ;
	this->yMax = 200 ;
}


int RushNChart::OnCreate(LPCREATESTRUCT lpCreateStruct)	{
	int ret = CFrameWnd::OnCreate(lpCreateStruct);

	//Menu Connect
	CMenu *menu = new CMenu;
	menu->LoadMenuW( IDR_MAIN_MENU );
	this->SetMenu( menu );
	/*
	//RButtonMenu
	CMenu *rButtonMenu = new CMenu ;

	// 메뉴를 교체한다. 접속되기 전의 메뉴
	rButtonMenu->LoadMenu(IDR_RBUTTONMENU);
 
	//차트,차트해제 버튼 초기 비활성화 상태
	rButtonMenu->EnableMenuItem( ID_MAKECHART,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
	rButtonMenu->EnableMenuItem( ID_RELEASECHART,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
	//*/
	//Paper Create
	this->paper = new Paper();
	this->select = new Select();
	this->copySymbol = new CopySymbol();
	this->paperList = new PaperList ( );
	this->scroll = new Scroll;
	paperList->CaptureLastPaper( paper );

	//Flag
	this->bSelectedMenu = FALSE ;			//메뉴클릭시
	this->bDragFlag = FALSE ;				//마우스 클릭 후 이동시
	this->bCompleteStructure = FALSE ;		//구조를 그리기 완성했을때
	this->bSelectedSymbolFlag = FALSE ;		//기호를 클릭했을떄
	this->bSelectedDBLClickedFlag = FALSE;	//기호를 더블클릭했을때
	this->bMovedSymbolFlag = FALSE ;			//기호를 이동했을떄
	this->TransNumber = 0;					// 기호의 크기를 변경하고자 할때
	this->saveName = _T("");					// 다른이름으로 저장하기 기능으로 인한 추가 -채형석-
	this->loadName = _T("");					// 불러오기 할때 사용 되는 이름 - 채형석
	this->bSaveFlag = FALSE;					//SAVE 할 내용이 있는지 여부를 확인할 떄 - 채형석
	
	////
	//추가
	this->bLDown =  FALSE ;
	this->bModify  =  FALSE ;
	this->bComposition = FALSE;
	this->bEmployFlag = FALSE;
	this->bWritingFlag = FALSE; 
	
	//preview
	this->dotSticker = 0 ;
	this->dotStickers = 0 ;
	this->selectedSymbolLength = 0 ;
	this->caseNumber = 0;

	//MovePreivew 
	this->moveX = 0 ;
	this->moveY = 0 ;
	this->bMovePreivew = FALSE ;

	// 디폴트 윈도우 크기를 저장
	// 비트맵 디플트 크기로 설정 사용한다
	GetClientRect(this->paperRect);	

	this->paperRect.bottom = this->paperRect.bottom + 600;
	this->paperRect.right = this->paperRect.right + 500;

	SetScrollRange(SB_HORZ, 0, this->xMax, TRUE);
	SetScrollRange(SB_VERT, 0, this->yMax, TRUE);

	return ret;
}


BOOL RushNChart::PreCreateWindow(CREATESTRUCT& cs)	{
	if ( ! CFrameWnd::PreCreateWindow( cs ) )
        return FALSE;

      cs.x  = 0;
      cs.y  = 0;
      cs.cx = 1280;
      cs.cy = 768;

	  this->windowWidth = cs.cx;
	  this->windowHeight = cs.cy;
	 
	  cs.lpszName = _T("Rush&Chart");
      
	  return TRUE;
}


RushNChart::~RushNChart(){

}


void	RushNChart::OnSequenceMenuClicked()	{
	
	this->symbol = "Sequence" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //메뉴에서 도형 선택 시, 수정점이 표시되어진 기호의 수정점 없애기용

}


void	RushNChart::OnBeforeRepeatMenuClicked()	{

	this->symbol = "BeforeRepeat" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //메뉴에서 도형 선택 시, 수정점이 표시되어진 기호의 수정점 없애기용

	
}


void	RushNChart::OnAfterRepeatMenuClicked()	{

	this->symbol = "AfterRepeat" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //메뉴에서 도형 선택 시, 수정점이 표시되어진 기호의 수정점 없애기용
}


void	RushNChart::OnSelectionMenuClicked()	{

	this->symbol = "Selection" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //메뉴에서 도형 선택 시, 수정점이 표시되어진 기호의 수정점 없애기용
	
}


void	RushNChart::OnSwitchCaseMenuClicked()	{

	this->symbol = "SwitchCase" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //메뉴에서 도형 선택 시, 수정점이 표시되어진 기호의 수정점 없애기용
	this->columnCount = 0 ;

	ColumnCountForm columnCountForm ;
	columnCountForm.DoModal() ;
	
}


void	RushNChart::OnArrowMenuClicked()	{
	
	this->symbol = "Arrow" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //메뉴에서 도형 선택 시, 수정점이 표시되어진 기호의 수정점 없애기용

}


void	RushNChart::OnNotEqualMenuClicked()	{
	if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{
		this->bWritingFlag = TRUE; //현재 식을 쓰는 중일때

		SelectPaper *selectPaper = this->select->GetSelectPaper();

		this->SetWrite( L"≠" );

		CClientDC cDC( this );

		this->SetCaret( &cDC, "right", L"≠" );

		Invalidate(FALSE) ; //메뉴에서 도형 선택 시, 수정점이 표시되어진 기호의 수정점 없애기용
	}
}


void	RushNChart::OnBetterThanMenuClicked()	{
	if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{

		if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{
			this->bWritingFlag = TRUE; //현재 식을 쓰는 중일때

			SelectPaper *selectPaper = this->select->GetSelectPaper();

			this->SetWrite( L"≤" );

			CClientDC cDC( this );

			this->SetCaret( &cDC, "right", L"≤" );

			Invalidate(FALSE) ; //메뉴에서 도형 선택 시, 수정점이 표시되어진 기호의 수정점 없애기용
		}
	}
}


void	RushNChart::OnLesserThanMenuClicked()	{
	if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{
		if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{
			this->bWritingFlag = TRUE; //현재 식을 쓰는 중일때

			SelectPaper *selectPaper = this->select->GetSelectPaper();

			this->SetWrite( L"≥" );

			CClientDC cDC( this );

			this->SetCaret( &cDC, "right", L"≥" );

			Invalidate(FALSE) ; //메뉴에서 도형 선택 시, 수정점이 표시되어진 기호의 수정점 없애기용
		}
	}
}


void	RushNChart::OnMakeChartButtonClicked( ){

	if( select->GetSelectPaper( )->GetLength( ) >= 2 ){
		paper->MakeChart( select );
		paperList->CaptureLastPaper( paper );
		select->ReleaseChart( );
		select->ReAllocateChart( );
		select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
		select->GetSelectChart( )->DrawChartField( ) ;
		select->GetSelectPaper( )->ReleaseAllSymbols( );
		Invalidate(FALSE );
	}

}


void	RushNChart::OnReleaseChartButtonClicked( ){

	select->GetSelectPaper( )->ReleaseAllSymbols( );
	paper->ReleaseChart( select );
	paperList->CaptureLastPaper( paper );
	select->ReleaseChart( );
	Invalidate(FALSE );

}


void	RushNChart::OnHelpInFoButtonClicked( ) {
	CString path = "RushNChartHelp.chm";
	//ShellExecute(::GetDesktopWindow(), L"open", path , 0, 0, SW_SHOWDEFAULT); 
	#pragma comment(lib, "Htmlhelp.Lib") 
	::HtmlHelpA(this->m_hWnd, "RushNChartHelp.chm", HH_DISPLAY_TOPIC, 0);
}


void	RushNChart::OnRButtonDown(UINT nFlag, CPoint point) {

	ClientToScreen( &point );
	GetCursorPos( &point );
	ScreenToClient( &point );

	CMenu menu;
	menu.LoadMenu(IDR_RBUTTONMENU);
	CMenu* Dmenu = menu.GetSubMenu( 0 );
	//CMenu* chartMenu = menu.GetSubMenu( 5 ); //맨 앞에 메뉴를 가져옴


	//차트,차트해제 버튼 초기 비활성화 상태
	//chartMenu->EnableMenuItem( ID_MAKECHART, MF_GRAYED );
	Dmenu->EnableMenuItem( ID_RELEASECHART,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
	
	Dmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON , point.x, point.y, this); 
	/*
	"차트"버튼과 "차트 해제"버튼은 기본 디폴트값은 diable, 회색이지만,
	오른쪽 메뉴 버튼을 클릭했는데 종이의 기호이고, 기호가 두개 이상 선택되어있는 경우 
	"차트"버튼은 활성화 된다.
	//*/
	if( select->GetSelectPaper( )->CheckSymbol( paper,point.x,point.y )>-1 &&  
		select->GetSelectPaper( )->GetLength( ) >= 2 ) {
	}

	/*
	오른쪽 메뉴 버튼을 클릭했을때 차트이고, 차트가 선택되어 있는 경우
	"차트 해제"버튼은 활성화 된다"
	//*/
	if( select->IsChartSelected( ) == true ) { 
	}


}


void	RushNChart::OnRButtonUp(UINT nFlag, CPoint point) {
}


void	RushNChart::OnLButtonDown(UINT nFlag, CPoint point) {
	
	this->bLDown = TRUE ;
	GetCursorPos( &point ) ;
	ScreenToClient( &point ) ;

	// 스크롤 한만큼 화면이 이동하니
	// 이동한 만큼의 좌표를 더한다
	point.x = point.x + this->xPos;
	point.y = point.y + this->yPos;

	// 다운했을 때의 마우스포인터의 위치를 저장
	this->startPositionX = point.x ;
	this->startPositionY = point.y ;

	this->endPositionX = point.x;		//endPoint 초기화
	this->endPositionY = point.y;		//endPoint 초기화
	
	Long	selectIndex;
	//*
	if( this->select->GetSelectPaper()->GetLength() > 0 )
	{
		this->bMovedSymbolFlag = TRUE ;
		this->bSelectedSymbolFlag = TRUE ;
	}
	//*/
	if( this->bSelectedMenu == FALSE && this->bSelectedSymbolFlag == FALSE) {

		if ( nFlag & MK_CONTROL ) {
			selectIndex = this->CtrlSelected( startPositionX, startPositionY );
		}
		else {
			selectIndex = this->SelectCheck( startPositionX, startPositionY );
		}

		if ( selectIndex > - 1 ) {
			this->bSelectedSymbolFlag = TRUE ;
		}

		if( this->bCompleteStructure == TRUE )	{
			this->bCompleteStructure = FALSE;
			DestroyCaret();
		}

		Invalidate(FALSE );
	}
	else if( this->bSelectedMenu == FALSE && this->bSelectedSymbolFlag == TRUE ) {

		this->TransNumber = this->select->GetSelectPaper()->TransNumber( paper, startPositionX, startPositionY );
 		this->bMovedSymbolFlag = FALSE;
		//

		// 수정점 클릭이 아니면 this->TransNumber == 0
		if ( this->TransNumber == 0 ) {
			if ( nFlag & MK_CONTROL ) { // 컨트롤 키를 눌렀을 때 // 추가로 선택하기 
				selectIndex = this->CtrlSelected( startPositionX, startPositionY );
				
					
			}
			else { // 컨트롤키 없이 기호 하나를 선택할 때 
				selectIndex = this->SelectCheck( startPositionX, startPositionY );
				if ( selectIndex == - 1 ) { // 바탕화면을 클릭으로 선택 다 풀 때 
					this->bCompleteStructure = FALSE;
					this->bSelectedMenu = FALSE;
					this->bSelectedDBLClickedFlag = FALSE;
					this->bSelectedSymbolFlag = FALSE;
					this->bWritingFlag = FALSE ;
					
					select->ReleaseChart( );
					select->GetSelectPaper( ) ->ReleaseAllSymbols( );
				}
				else{ // 기호 하나를 선택 했을 때
						// 최초 선택 = 수정점 표시
						// 중복 선택 = 릴리즈
					this->bCompleteStructure = FALSE;
					this->bSelectedMenu = FALSE;
					this->bSelectedDBLClickedFlag = FALSE;
					this->bSelectedSymbolFlag = TRUE;
					this->bWritingFlag = FALSE ;
					this->bMovedSymbolFlag = TRUE;
				}
					
			}
			DestroyCaret();
		}
		Invalidate(FALSE) ;
	}

	// MovePreveiw Flag 
	if( this->TransNumber == 0	 )
	{
		if (	 this->select->GetSelectPaper()->GetLength() > 0		||	  this->paper->GetChart()->GetLength() ) 
		{
				this->bMovePreivew = TRUE ; // MovePreveiw Flag 켜기
		}
	}

	//드래그 이동시 basePoint, PreviousPoint구하기
	
	if( this->bSelectedMenu == FALSE	&&		this->bSelectedSymbolFlag == FALSE) {
		this->bDragFlag = TRUE;
	}

	//*/


}


void	RushNChart::OnLButtonDblClk( UINT nFlags, CPoint point )	{

	GetCursorPos( &point ) ;
	ScreenToClient( &point ) ;

	// 스크롤 한만큼 화면이 이동하니
	// 이동한 만큼의 좌표를 더한다
	point.x = point.x + this->xPos;
	point.y = point.y + this->yPos;

	if( this->bSelectedSymbolFlag == TRUE && select->IsChartSelected( )==false )	{
		//캐럿이 생성되면 쓸수 있는 상태임
		bWritingFlag = TRUE;
		SelectPaper *selectPaper = this->select->GetSelectPaper();
		SelectChart *selectChart = this->select->GetSelectChart();

		Symbol *symbol;
		Long symbolIndex;

		if( selectPaper != NULL )	{
			SelectedSymbol selectedSymbol = selectPaper->GetAt( 0 );
			
			symbolIndex = selectedSymbol.GetSeletedSymbolIndex();

			symbol = this->paper->GetAt( symbolIndex );
		}

		Long currentPointX = -1 ;
		Long currentPointY = -1 ;
		wstring expression;


		if( dynamic_cast< SwitchCase * > ( symbol ) )	{
			this->caseNumber = selectPaper->StringCheck( this->paper, point.x, point.y );

			if( caseNumber > 0 )	{
				SwitchCase *switchCase = static_cast< SwitchCase * > ( symbol );
				Long caseStartPointX = switchCase->GetCases( this->caseNumber - 1 )->GetExpressionStartPointX();
				Long caseEndPointX = switchCase->GetCases( this->caseNumber - 1 )->GetExpressionEndPointX();
				
				currentPointX = caseStartPointX + ( caseEndPointX - caseStartPointX ) / 2 - 2 ;
				currentPointY = switchCase->GetCases( this->caseNumber - 1 )->GetExpressionStartPointY();

				expression = switchCase->GetCases( this->caseNumber - 1 )->GetExpression();
			}
			else	{
				currentPointX = symbol->GetExpressionStartPointX();
				currentPointY = symbol->GetExpressionStartPointY();
				expression = symbol->GetExpression();
			}
		}
		else {
			currentPointX = symbol->GetExpressionStartPointX();
			currentPointY = symbol->GetExpressionStartPointY();
			expression = symbol->GetExpression();
		}

		currentPointX = currentPointX - this->xPos ;
		currentPointY = currentPointY - this->yPos ;

		CClientDC cDC( this );
		CSize size;

		if( expression.size() > 0 )	{
			size = cDC.GetTextExtent( expression.c_str() );
		}
		else	{
			size.cx = 2;
			size.cy = 16;
		}

		if( this->pen != NULL )	{
			delete this->pen;
		}

		if( dynamic_cast< Sequence * > ( symbol ) || dynamic_cast< Selection * > ( symbol ) ||
			dynamic_cast< BeforeRepeat * > ( symbol ) || dynamic_cast< AfterRepeat * > ( symbol ))	{
				this->pen = new Pen( expression.size(), currentPointX + size.cx + 2, 
				currentPointY + 5,	2, size.cy );
		}

		else if( dynamic_cast< SwitchCase * > ( symbol ) )	{
			if ( caseNumber > 0 ) {
				this->pen = new Pen( expression.size(), currentPointX + (size.cx + 2)/2, 
					currentPointY + 5,	2, size.cy );
			}
			else {
				this->pen = new Pen( expression.size(), currentPointX + size.cx + 2, 
									currentPointY + 5,	2, size.cy );
			}
		}


		CreateSolidCaret( 2, size.cy );
		POINT point = { this->pen->GetCurrentPointX(), this->pen->GetCurrentPointY() };
		SetCaretPos( point );
		ShowCaret();

		this->bSelectedDBLClickedFlag = TRUE;
	}
}


void	RushNChart:: OnMouseMove(UINT nFlag, CPoint point) {

	GetCursorPos( &point ) ;
	ScreenToClient( &point ) ;
	// 스크롤 한만큼 화면이 이동하니
	// 이동한 만큼의 좌표를 더한다
	point.x = point.x + this->xPos;
	point.y = point.y + this->yPos;

	// MovePreview
	if( this->bMovePreivew == TRUE ) 
	{
		this->moveX = point.x - this->startPositionX ;
		this->moveY = point.y - this->startPositionY ;
		Invalidate(FALSE) ;
	}


	//단일 선택 후 이동 일때, 붙이기 미리보기 
	if( this->select->GetSelectPaper()->GetLength() == 1 && this->bMovePreivew == TRUE )
	{ 
		this->StickerPreview() ;
	}
	
	// 다중 선택 후 이동일 때, 붙이기 미리보기 
	else if(  this->select->GetSelectPaper()->GetLength() > 1 && this->bMovePreivew == TRUE ) 
	{
		this->StickersPreview() ;
	}//*/


	if (this->bLDown == FALSE && this->bSelectedSymbolFlag == TRUE ) {
		this->TransNumber = this->select->GetSelectPaper()->TransNumber( paper, point.x, point.y );
		if ( this->TransNumber > 0 ) {
			Long	number = this->TransNumber ;
			if( number == 1 || number == 5 ) {
				SetCursor(LoadCursor(NULL,IDC_SIZENWSE));//왼쪽위에서 오른쪽 아래 대각선
			}
			else if ( number == 2 || number == 6 ) {
				SetCursor(LoadCursor(NULL,IDC_SIZENS)); //상하
			}
			else if ( number == 3 || number == 7 ) {
				SetCursor(LoadCursor(NULL,IDC_SIZENESW)); //오른위에서 왼아래 대각선
			}
			else if ( number == 4 || number == 8 ) {
				SetCursor(LoadCursor(NULL,IDC_SIZEWE)); //좌우
			}
		}
	}

	if ( this->bLDown == FALSE	 &&		this->bSelectedMenu == TRUE ) {
		this->startPositionX = point.x ;
		this->startPositionY = point.y ;
		Invalidate(FALSE) ;
	}

	if( this->bLDown == TRUE	 &&		this->bSelectedMenu == TRUE ){ //'만들다'에서 현재 기호의 크기를 점선으로 표시위한 크기좌표 설정
		this->endPositionX = point.x ;
		this->endPositionY = point.y ;
		Invalidate(FALSE) ;
	}
	else if ( this->bLDown == TRUE	 &&		this->bSelectedMenu == FALSE ){
		this->endPositionX = point.x ;
		this->endPositionY = point.y ;
		Invalidate(FALSE) ;
	}
	// 다중선택하다 드레그 점섬 표시
	else if ( this->bLDown == TRUE	 &&		this->bSelectedMenu == FALSE && this->bSelectedSymbolFlag == FALSE && this->bDragFlag ==TRUE ) {
		this->endPositionX = point.x ;
		this->endPositionY = point.y ;
		Invalidate(FALSE) ;
	}

	SelectPaper *selectPaper = select->GetSelectPaper( );
	if( this->bLDown == TRUE	&&	bMovedSymbolFlag == TRUE &&	this->bSelectedSymbolFlag == TRUE		&&		this->TransNumber == 0 )
	{
		//종이의 기호가 선택되어있다면
		if( selectPaper->GetLength( ) > 0 ){

			//이동된 기호들을 재 선택한다.
			//this->select->GetSelectPaper()->ReNewSelected( paper );

			this->bSelectedSymbolFlag = FALSE ;
			Invalidate(FALSE );
			this->bSelectedSymbolFlag = TRUE ;
		}
		if( select->GetSelectChart( ) != 0 ){
			Invalidate(FALSE );
		}
		
		Invalidate( FALSE);
		this->bSelectedSymbolFlag = TRUE ;
		}
	
	//고치다
	if(  this->bLDown == TRUE && this->TransNumber > 0 ) { 
		Long	index = 0;
		Long	i = 0;

		Long	number = this->TransNumber ;
		if( number == 1 || number == 5 ) {
			SetCursor(LoadCursor(NULL,IDC_SIZENWSE));//왼쪽위에서 오른쪽 아래 대각선
		}
		else if ( number == 2 || number == 6 ) {
			SetCursor(LoadCursor(NULL,IDC_SIZENS)); //상하
		}
		else if ( number == 3 || number == 7 ) {
			SetCursor(LoadCursor(NULL,IDC_SIZENESW)); //오른위에서 왼아래 대각선
		}
		else if ( number == 4 || number == 8 ) {
			SetCursor(LoadCursor(NULL,IDC_SIZEWE)); //좌우
		}

		if ( this->select->GetSelectPaper()->GetLength() == 0 ) {
			//index = this->select->GetSelectChart()->GetAt( i ).GetSeletedSymbolIndex();
			this->startPositionX = this->paper->GetChart()->GetAt( index )->GetStartPointX();
			this->startPositionY = this->paper->GetChart()->GetAt( index )->GetStartPointY();
			this->endPositionX = this->paper->GetChart()->GetAt( index )->GetEndPointX();
			this->endPositionY = this->paper->GetChart()->GetAt( index )->GetEndPointY();
		}

		else {
			index = this->paper->TransForm( this->select, this->TransNumber, point.x, point.y ) ;
			this->startPositionX = this->paper->GetAt( index )->GetStartPointX();
			this->startPositionY = this->paper->GetAt( index )->GetStartPointY();
			this->endPositionX = this->paper->GetAt( index )->GetEndPointX();
			this->endPositionY = this->paper->GetAt( index )->GetEndPointY();
		}
		// Line붙이기 
		//if( this->TransNumber > 0 ){
		if( this->TransNumber > 0 && this->select->GetSelectPaper()->GetLength() == 1 ){
			Sticker sticker ;
			this->dotSticker =  sticker.StickLineForPre( this->paper, index, this->TransNumber ) ;
		}
		/*
		// 다중 선택 후 고칠 때 붙이기
		if(  this->select->GetSelectPaper()->GetLength() > 1 ) //다중선택이면
		{
			Long index = (this->select->GetSelectPaper()->GetAt(0)).GetSeletedSymbolIndex() ;
			if( index > -1 )
			{
				Sticker sticker ;
				//sticker.SelectedSymbolsSort( this->select ) ;
 				for( Long i = 0 ; i < this->select->GetSelectPaper()->GetLength() ; i++ )
				{
					Long tempIndex = (this->select->GetSelectPaper()->GetAt(i)).GetSeletedSymbolIndex() ;	
					sticker.CheckStickingFieldForModify( this->paper, this->select, tempIndex ) ;
					if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// 붙이는 상황이면
					{
						sticker.GetInfoToMove( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), tempIndex ) ;
						string type = this->paper->CheckType( tempIndex ) ;
						//기호를 붙여 그리다 //기존 기호는 지운다
						sticker.StickTo( this->paper, sticker.GetStartX(), sticker.GetStartY(), sticker.GetEndX(), sticker.GetEndY(), paper->GetAt(tempIndex)->GetExpression(), type, tempIndex ) ;
					}
				}
			}
		}				//*/
		Invalidate(FALSE) ;

	}
}


void	RushNChart:: OnLButtonUp(UINT nFlag, CPoint point)  {

	GetCursorPos( &point ) ;
	ScreenToClient( &point ) ;

	// 스크롤 한만큼 화면이 이동하니
	// 이동한 만큼의 좌표를 더한다
	point.x = point.x + this->xPos;
	point.y = point.y + this->yPos;

	Long	index;
	if( this->bSelectedMenu == TRUE )
	{ //만들다
		Long index ;
		this->endPositionX = point.x ;
		this->endPositionY = point.y ;

		if( this->symbol != "SwitchCase" )	{
			index = this->paper->Draw ( startPositionX, startPositionY, endPositionX, endPositionY, L"", this->symbol ) ;
			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
		}
		else	{
			index = this->paper->Draw ( startPositionX, startPositionY, endPositionX, endPositionY, L"", this->symbol,
				this->columnCount );
			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
		}
		
		//그리기용 붙이기능 추가
		this->StickOnPaperWhenDraw( this->startPositionX, this->startPositionY, index  ) ;		
		paperList->CaptureLastPaper( paper );

		this->bSelectedSymbolFlag = FALSE ; //만들어 지기전에, 기존에 선택되어서 수정점 있는 기호의 수정점 없애기

		//식을 만든 직후 바로 식을 입력하기 위해서 커서 깜빡이기
		Symbol *symbol = this->paper->GetAt( index ) ;

		if( this->pen != NULL )	{
			delete this->pen;
		}

		this->pen = new Pen( 0, symbol->GetExpressionStartPointX() + 2  - this->xPos , 
			symbol->GetExpressionStartPointY() + 5  - this->yPos, 2, 16 );

		CreateSolidCaret ( 2, 16 );
		POINT point = { this->pen->GetCurrentPointX(), this->pen->GetCurrentPointY() };
		SetCaretPos( point ) ;
		ShowCaret() ;

		this->bCompleteStructure = TRUE;
		
		Invalidate(FALSE) ;

		this->bSelectedMenu = FALSE ;

	}

	// 다중선택하다 드레그 선택시
	if ( bSelectedSymbolFlag == FALSE ) {

		this->endPositionX = point.x ;
		this->endPositionY = point.y ;

		if( this->startPositionX > this->endPositionX ) {
			Long tempPositionX = this->startPositionX ;
			this->startPositionX = this->endPositionX ;
			this->endPositionX = tempPositionX ;
		}
		if( this->startPositionY > this->endPositionY ) {
			Long tempPositionY = this->startPositionY ;
			this->startPositionY = this->endPositionY ;
			this->endPositionY = tempPositionY ;
		}

		//index = this->DragSelected( this->startPositionX, this->startPositionY, point.x, point.y );
		index = this->DragSelected( this->startPositionX, this->startPositionY, this->endPositionX, this->endPositionY );
	
		if ( index > - 1 ) {
			bSelectedSymbolFlag = TRUE;
		}
		else {
			bSelectedSymbolFlag = FALSE;
		}
		Invalidate(FALSE) ;
	}

	if( this->TransNumber > 0 ) { //고치다

		if ( this->select->GetSelectPaper()->GetLength() != 0 ) {
			
			index = this->paper->TransForm( this->select, this->TransNumber, point.x, point.y ) ;
			paperList->CaptureLastPaper( paper );
			this->select->GetSelectPaper()->ReNewSelected( paper );
			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
		}
		this->select->GetSelectPaper()->ReNewSelected( paper );
		//this->select->GetSelectChart()->ReNewSelected( paper->GetChart() );
		
		//Line 붙이기 로직
		Sticker sticker ;
		sticker.StickLine( this->paper, index, this->TransNumber ) ;
		
		//******************************
		//paperList->CaptureLastPaper( paper );
		//******************************

		// StickingSign
		Long i = 0 ;
		while( i < this->paper->GetLength()  )
		{
			sticker.CheckStickingSign( this->paper , i ) ;
			i ++ ;
		}//*/

		this->select->GetSelectPaper()->ReNewSelected( paper );
		this->TransNumber  = 0 ;

		Invalidate(FALSE) ;
	}

	if( bSelectedSymbolFlag == TRUE && bMovedSymbolFlag == TRUE ){
		//종이를 이동하여 버튼을 똇을때
		if( this->select->GetSelectPaper()->GetLength() > 0 ) {
			this->paper->Move( this->select, this->startPositionX, this->startPositionY, point.x, point.y );
			Invalidate(FALSE );
			bMovedSymbolFlag = FALSE;
			this->select->GetSelectPaper()->ReNewSelected( paper );
			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
		}
		//차트를 이동하여 버튼을 뗏을때 
		if( select->IsChartSelected( ) == true && paper->GetChart( )->GetLength( ) >0 ){
			this->paper->GetChart()->Move( this->startPositionX, this->startPositionY, point.x, point.y );
			Invalidate(FALSE );
			bMovedSymbolFlag = FALSE;
			select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
			select->GetSelectChart( )->DrawChartField( );
			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
		}

		// StickingSign
		Sticker sticker ;
		Long i = 0 ;
		while( i < this->paper->GetLength()  )
		{
			sticker.CheckStickingSign( this->paper , i ) ;
			i ++ ;
		}//*/

		//단일 선택 후 이동 일때만 붙이기 
		if( this->select->GetSelectPaper()->GetLength() == 1 )
		{
			Long index = (this->select->GetSelectPaper()->GetAt(0)).GetSeletedSymbolIndex() ;

			if( index > -1 )
			{
				Long startX = this->paper->GetAt( index )->GetStartPointX() ;
				Long startY = this->paper->GetAt( index )->GetStartPointY() ;
				//단일 선택기호 붙이기
				this->StickOnPaperWhenMove( startX, startY, index ) ;
				//수정점 다시 표시
				this->select->GetSelectPaper()->ReNewSelected( paper );
			}
			//******************************
			//paperList->CaptureLastPaper( paper );
			//******************************
		}
			
		//다중 선택 후 이동 일때 붙이기
		else if( this->select->GetSelectPaper()->GetLength() > 1 )
		{
			this->StickOnPaperWhenMoveBudle() ;
			//******************************
			//paperList->CaptureLastPaper( paper );
			//******************************
		}//*/
		
		paperList->CaptureLastPaper( paper );
	}



		// MovePreivew
	if( this->bMovePreivew == TRUE )
	{
		//초기화
		this->moveX = 0 ;
		this->moveY = 0 ;
		this->bMovePreivew = FALSE ;
		Invalidate(FALSE) ;
	}

	this->bDragFlag = FALSE;
	this->bLDown = FALSE ;

}


void RushNChart::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {

	switch ( nChar )	{
		case 1:	// 전체 선택

			DestroyCaret( );

			//선택 되어있는 symbol 삭제
			this->select->GetSelectPaper()->ReleaseAllSymbols();

			this->select->GetSelectPaper()->StoreSelectedSymbol( this->paper );
			//새로 할당하고
			select->ReleaseChart( );
			select->ReAllocateChart( );
			//선택한다
			if ( this->paper->GetChart()->GetLength () > 0 ) {
				select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
				select->GetSelectChart( )->DrawChartField( );
			}
			
			this->bSelectedSymbolFlag = TRUE;

			break;

		case 3:	// Ctrl + c

			this->copySymbol->CopySymbols( this->select, this->paper );

			break;

		case 7: // Ctrl + g

			if( select->GetSelectPaper( )->GetLength( ) >= 2 ){
				paper->MakeChart( select );
				paperList->CaptureLastPaper( paper );
				select->ReleaseChart( );
				select->ReAllocateChart( );
				select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
				select->GetSelectChart( )->DrawChartField( ) ;
				select->GetSelectPaper( )->ReleaseAllSymbols( );

				Invalidate( FALSE );
			}

			break;
		
		case 14: // Ctrl + n

			this->OnNewPaperMenuClicked();

			break;

		case 15: // Ctrl + o

			this->OnLoadMenuClicked();

			break;

		case 16: // Ctrl + p

			this->OnPrintMenuClicked();

			break;

		case 19: // Ctrl + s

			this->OnSaveMenuClicked();
			
			break;

		case 21: // Ctrl + u

			if( select->IsChartSelected( ) == true ){
				select->GetSelectPaper( )->ReleaseAllSymbols( );
				paper->ReleaseChart( select );
				paperList->CaptureLastPaper( paper );
				select->ReleaseChart( );

				Invalidate( FALSE );

				this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
			}

			break;

		case 22: // Ctrl + v

			this->copySymbol->PasteSymbols( this->select, this->paper );
			this->bSelectedSymbolFlag = TRUE;

			paperList->CaptureLastPaper( paper );

			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.

			break;

		case 24: // Ctrl + x

			this->copySymbol->CutSymbols( this->select, this->paper );
			paperList->CaptureLastPaper( paper );
			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.

			break;

		case 25: // Ctrl + y

			if( paperList->GetCurrent( ) + 1 <= paperList->GetLength( ) )	{
				Paper *redoPaper = this->paperList->Redo(  );
				paper = redoPaper ;
				
				Invalidate( FALSE );

				this->bSaveFlag = TRUE;
				this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
			}
			
			break;

		case 26: // Ctrl + z
			
			if( this->paperList->GetCurrent( ) - 1 > 0 ){

				Paper *undoPaper = this->paperList->Undo( );
				if( this->pen != NULL ){
					//delete this->pen;
					DestroyCaret( );
				}
				paper = undoPaper;
				select->GetSelectPaper( )->ReleaseAllSymbols( );
				select->ReleaseChart( );
				
				Invalidate( FALSE );

				this->bSaveFlag = TRUE;
				this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
			}

			break;

		case VK_RETURN:	//Enter Key

			DestroyCaret() ;

			this->bCompleteStructure = FALSE;
			this->bSelectedMenu = FALSE;
			this->bSelectedDBLClickedFlag = FALSE;

			paperList->CaptureLastPaper( paper );
			//식을 다 쓰면
			this->bWritingFlag = FALSE;

			break;

		default:

			//TRACE ( "nChar [ %d ]\n", nChar );

			if( nChar != VK_BACK && ( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE ) )	{

				this->bWritingFlag = TRUE; //현재 식을 쓰는 중일때
				CString str; 
				str.Format( _T("%c"), nChar ) ;
				wstring newExpression = wstring ( str );

				SelectPaper *selectPaper = this->select->GetSelectPaper();
				SelectChart *selectChart = this->select->GetSelectChart();

				Symbol *symbol = NULL;

				if( this->bCompleteStructure == TRUE)	{
					symbol = this->paper->GetAt( this->paper->GetLength() - 1 );
				}
				else if( this->bSelectedDBLClickedFlag == TRUE )	{
					symbol = this->paper->GetAt ( selectPaper->GetSelectedSymbolIndex() );
				}

				if( !dynamic_cast< SwitchCase * > ( symbol ) )	{
					if( ( symbol->GetExpressionEndPointX() - 8 ) > this->pen->GetCurrentPointX() )	{

						this->SetWrite( newExpression );

						CClientDC cDC( this );

						this->SetCaret( &cDC, "right", newExpression );

					}
				}
				else	{
					SwitchCase *switchCase = static_cast< SwitchCase * > ( symbol );
					if( this->caseNumber > 0 )	{
						if( ( switchCase->GetCases( this->caseNumber - 1 )->GetExpressionEndPointX() - 8 ) > this->pen->GetCurrentPointX() )	{

							this->SetWrite( newExpression );

							CClientDC cDC( this );

							this->SetCaret( &cDC, "right", newExpression );

						}
					}
					else	{
						if( ( switchCase->GetExpressionEndPointX() - 8 ) > this->pen->GetCurrentPointX() )	{

							this->SetWrite( newExpression );

							CClientDC cDC( this );

							this->SetCaret( &cDC, "right", newExpression );

						}
					}
				}

				/*
				if( this->bSelectedDBLClickedFlag == TRUE && selectPaper != NULL )	{
					SelectedSymbol selectedSymbol = selectPaper->GetAt( 0 );

					Long symbolIndex = selectedSymbol.GetSeletedSymbolIndex();

					symbol = this->paper->GetAt( symbolIndex );

					if( dynamic_cast < SwitchCase * > ( symbol ) && this->caseNumber > 0 )	{
						Long index = this->paper->WriteCase( symbolIndex, this->caseNumber, this->pen->GetCurrentIndex(), newExpression );
					 
					}
					else	{
						if( this->pen->GetCurrentIndex() >= 0 && this->pen->GetCurrentIndex() < symbol->GetExpression().size() )	{
							Long index = this->paper->Correct( symbolIndex, this->pen->GetCurrentIndex(), newExpression );
						}
						else	{
							Long index = this->paper->Write( symbolIndex, newExpression );
						 
						}
					}
				}
				else	{
					symbol = this->paper->GetAt( this->paper->GetLength() - 1 );

					if( this->pen->GetCurrentIndex() >= 0 && this->pen->GetCurrentIndex() < symbol->GetExpression().size() )	{
						Long index = this->paper->Correct( this->paper->GetLength() - 1, this->pen->GetCurrentIndex(), newExpression );
					}
					else	{
						Long index = this->paper->Write( this->paper->GetLength() - 1, newExpression );
					 
					}
				}

				CClientDC cDC( this );

				this->SetCaret( &cDC, "right", newExpression );
				//*/
			}

			break;
	}

	/*
	if( nChar != VK_RETURN && nChar != VK_BACK && !(GetKeyState ( VK_CONTROL ) & 0x8000)  )	{

		if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{
		
			this->bWritingFlag = TRUE; //현재 식을 쓰는 중일때
			CString str; 
			str.Format( _T("%c"), nChar ) ;
			wstring newExpression = wstring ( str );

			SelectPaper *selectPaper = this->select->GetSelectPaper();
			SelectChart *selectChart = this->select->GetSelectChart();

			Symbol *symbol;

			if( this->bSelectedDBLClickedFlag == TRUE && selectPaper != NULL )	{
				SelectedSymbol selectedSymbol = selectPaper->GetAt( 0 );

				Long symbolIndex = selectedSymbol.GetSeletedSymbolIndex();

				symbol = this->paper->GetAt( symbolIndex );

				if( dynamic_cast < SwitchCase * > ( symbol ) && this->caseNumber > 0 )	{
					Long index = this->paper->WriteCase( symbolIndex, this->caseNumber, this->pen->GetCurrentIndex(), newExpression );
					 
				}
				else	{
					if( this->pen->GetCurrentIndex() >= 0 && this->pen->GetCurrentIndex() < symbol->GetExpression().size() )	{
						Long index = this->paper->Correct( symbolIndex, this->pen->GetCurrentIndex(), newExpression );
					}
					else	{
						Long index = this->paper->Write( symbolIndex, newExpression );
						 
					}
				}
			}
			else	{
				symbol = this->paper->GetAt( this->paper->GetLength() - 1 );

				if( this->pen->GetCurrentIndex() >= 0 && this->pen->GetCurrentIndex() < symbol->GetExpression().size() )	{
					Long index = this->paper->Correct( this->paper->GetLength() - 1, this->pen->GetCurrentIndex(), newExpression );
				}
				else	{
					Long index = this->paper->Write( this->paper->GetLength() - 1, newExpression );
					 
				}
			}

			CClientDC cDC( this );

			this->SetCaret( &cDC, "right", newExpression );
		}
		
	}
	else if ( nChar == VK_RETURN )	{

		DestroyCaret() ;

		this->bCompleteStructure = FALSE;
		this->bSelectedMenu = FALSE;
		this->bSelectedDBLClickedFlag = FALSE;

		this->expression = "";
		paperList->CaptureLastPaper( paper );
		//식을 다 쓰면
		this->bWritingFlag = FALSE;
	}
	
	//*/

	Sticker sticker ;
	// StickingSign
	Long i = 0 ;
	while( i < this->paper->GetLength()  )
	{
		sticker.CheckStickingSign( this->paper , i ) ;
		i ++ ;
	}

	Invalidate( FALSE ) ;
}


void RushNChart::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )	{
	
	switch(nChar)	{
		case VK_DELETE :
			if( this->bSelectedSymbolFlag == TRUE && this->bWritingFlag == FALSE ){
				if( select->GetSelectPaper( )->GetLength( ) > 0 ){
					paper->DeleteSymbols( this->select->GetSelectPaper( ) );
					paperList->CaptureLastPaper( paper );
					this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
				}
				else if( this->paper->GetChart( )->GetLength( ) > 0 && bWritingFlag == FALSE){
					paper->GetChart( )->DeleteAllSymbols(  );
					paperList->CaptureLastPaper( paper );
					select->ReleaseChart( );
					this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
				}
				DestroyCaret();
			}
			break;
		
		case VK_BACK :

			if( this->bSelectedDBLClickedFlag == TRUE || this-> bCompleteStructure == TRUE )	{
				SelectPaper *selectPaper = this->select->GetSelectPaper();
				SelectChart *selectChart = this->select->GetSelectChart();

				Symbol *symbol;
				Long symbolIndex;
				wstring tempString;

				if( this->bSelectedDBLClickedFlag == TRUE && selectPaper != NULL )	{
					SelectedSymbol selectedSymbol = selectPaper->GetAt( 0 );
					symbolIndex = selectedSymbol.GetSeletedSymbolIndex();
					symbol = this->paper->GetAt( symbolIndex );

					if( dynamic_cast < SwitchCase * > ( symbol ) && this->caseNumber > 0 )	{
						SwitchCase *switchCase = static_cast< SwitchCase * > ( symbol );

						Long currentIndex = this->pen->GetCurrentIndex() - 1;

						if( currentIndex < 0 )	{
							currentIndex = 0;
						}

						tempString = switchCase->GetCases( this->caseNumber - 1 )->GetExpression().substr( currentIndex, 1 );
						Long ret = this->paper->EraseCase( symbolIndex, this->caseNumber, this->pen->GetCurrentIndex() - 1 );
						this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
					}
					else	{
						if( this->pen->GetCurrentIndex() > 0 )	{
							tempString = symbol->GetExpression().substr( this->pen->GetCurrentIndex() - 1, 1 );
							Long ret = this->paper->Erase( symbolIndex, this->pen->GetCurrentIndex() - 1 );
							this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
						}
					}
				}
				else	{
					symbol = this->paper->GetAt( this->paper->GetLength() - 1 );

					if( this->pen->GetCurrentIndex() > 0 )	{
						tempString = symbol->GetExpression().substr( this->pen->GetCurrentIndex() - 1, 1 );
						Long ret = this->paper->Erase( this->paper->GetLength() - 1, this->pen->GetCurrentIndex() - 1 );
						this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
					}
				}

				if( this->pen->GetCurrentIndex() > 0 )	{
					CClientDC cDC( this );

					this->SetCaret( &cDC, "left", tempString );

					this->Invalidate(FALSE);
				}
			}
			break;

		case VK_LEFT :
			if( this->bSelectedDBLClickedFlag == TRUE || this-> bCompleteStructure == TRUE && select->IsChartSelected( ) == false )	{
				SelectPaper *selectPaper = this->select->GetSelectPaper();
				SelectChart *selectChart = this->select->GetSelectChart();

				Symbol *symbol;
				Long symbolIndex;

				if( this->bSelectedDBLClickedFlag == TRUE && selectPaper != NULL )	{
					SelectedSymbol selectedSymbol = selectPaper->GetAt( 0 );

					symbolIndex = selectedSymbol.GetSeletedSymbolIndex();

					symbol = this->paper->GetAt( symbolIndex );
				}

				else	{
					symbol = this->paper->GetAt( this->paper->GetLength() - 1 );
				}

				string direction = "left";
				wstring expression;
				if( dynamic_cast < SwitchCase * > ( symbol ) && this->caseNumber > 0 )	{
					SwitchCase *switchCase = static_cast< SwitchCase * > ( symbol );
					expression = switchCase->GetCases( this->caseNumber - 1 )->GetExpression();

					if( this->caseNumber > 0 )	{
						direction = "leftSwitch";
					}
				}
				else	{
					expression = symbol->GetExpression();
				}

				CClientDC cDC( this );

				if( this->pen->GetCurrentIndex() > 0 )	{
					wstring tempString = expression.substr( this->pen->GetCurrentIndex() - 1, 1 );
				
					this->SetCaret( &cDC, direction, tempString );
				}
			}

			if( bSelectedSymbolFlag == TRUE && bWritingFlag == FALSE ) {
				if( this->select->GetSelectPaper( )->GetLength( ) >= 1 ){
					this->paper->MoveKey( this->select, 0 );

					this->select->GetSelectPaper( )->ReNewSelected( paper );
					this->paperList->CaptureLastPaper( paper );
					this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
				}
				if( select->IsChartSelected( ) == true && paper->GetChart( )->GetLength( ) > 0 ) {
					this->paper->GetChart()->MoveKey( this->select, 0 );

					select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
					select->GetSelectChart( )->DrawChartField( );
					this->bEmployFlag = TRUE;
				}
			}

			break;

		case VK_RIGHT :

			if( this->bSelectedDBLClickedFlag == TRUE || this-> bCompleteStructure == TRUE && select->IsChartSelected( ) == false )	{
				SelectPaper *selectPaper = this->select->GetSelectPaper();
				SelectChart *selectChart = this->select->GetSelectChart();

				Symbol *symbol;
				Long symbolIndex;

				if( this->bSelectedDBLClickedFlag == TRUE && selectPaper != NULL )	{
					SelectedSymbol selectedSymbol = selectPaper->GetAt( 0 );

					symbolIndex = selectedSymbol.GetSeletedSymbolIndex();

					symbol = this->paper->GetAt( symbolIndex );
				}
			
				else	{
					symbol = this->paper->GetAt( this->paper->GetLength() - 1 );
				}

				string direction = "right";
				wstring expression;
				if( dynamic_cast < SwitchCase * > ( symbol ) && this->caseNumber > 0 )	{
					SwitchCase *switchCase = static_cast< SwitchCase * > ( symbol );
					expression = switchCase->GetCases( this->caseNumber - 1 )->GetExpression();

					if( this->caseNumber > 0 )	{
						direction = "rightSwitch";
					}
				}
				else	{
					expression = symbol->GetExpression();
				}

				CClientDC cDC( this );

				if( expression.size() > this->pen->GetCurrentIndex() )	{
					wstring tempString = expression.substr( this->pen->GetCurrentIndex(), 1 );
				
					this->SetCaret( &cDC, direction, tempString );
				}
			}
			
			if( bSelectedSymbolFlag == TRUE && bWritingFlag == FALSE ) {
				if( select->GetSelectPaper( )->GetLength( ) >= 1 )	{
					this->paper->MoveKey( this->select, 1 );

					select->GetSelectPaper( )->ReNewSelected( paper );
					paperList->CaptureLastPaper( paper );
					this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
				}
				if( select->IsChartSelected( ) == true && paper->GetChart( )->GetLength( ) > 0 ) {
					this->paper->GetChart()->MoveKey( this->select, 1 );

					select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
					select->GetSelectChart( )->DrawChartField( );
					this->bEmployFlag = TRUE;
				}
			}


			break;

		case VK_UP :
			
			if( bSelectedSymbolFlag == TRUE && bWritingFlag == FALSE ) {
				if( select->GetSelectPaper( )->GetLength( ) >= 1 )	{
					this->paper->MoveKey( this->select, 2 );

					select->GetSelectPaper( )->ReNewSelected( paper );
					paperList->CaptureLastPaper( paper );
					this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
				}
				if( select->IsChartSelected( ) == true && paper->GetChart( )->GetLength( ) > 0 ) {
					this->paper->GetChart()->MoveKey( this->select, 2 );

					select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
					select->GetSelectChart( )->DrawChartField( );
					this->bEmployFlag = TRUE;
				}
			}

			break;

		case VK_DOWN :

			if( bSelectedSymbolFlag == TRUE && bWritingFlag == FALSE ) {
				if( select->GetSelectPaper( )->GetLength( ) >= 1 )	{
					this->paper->MoveKey( this->select, 3 );

					select->GetSelectPaper( )->ReNewSelected( paper );
					paperList->CaptureLastPaper( paper );
					this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
				}
				if( select->IsChartSelected( ) == true && paper->GetChart( )->GetLength( ) >0 ) {
					this->paper->GetChart()->MoveKey( this->select, 3 );

					select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
					select->GetSelectChart( )->DrawChartField( );
					this->bEmployFlag = TRUE;
				}
			}

			break;

		case VK_ESCAPE :
			DestroyCaret() ;

			this->bCompleteStructure = FALSE;
			this->bSelectedMenu = FALSE;
			this->bSelectedDBLClickedFlag = FALSE;

			paperList->CaptureLastPaper( paper );
			//식을 다 쓰면
			this->bWritingFlag = FALSE;
			break;

		case VK_F12 :
			this->OnReNameSaveMenuClicked() ;
			break;

		case VK_F1 :
			this->OnHelpInFoButtonClicked();
			break;

		case 49:
			if( GetKeyState( VK_CONTROL ) < 0 )	{
				this->OnSequenceMenuClicked() ;
			}
			break;

		case 50:
			if( GetKeyState( VK_CONTROL ) < 0 )	{
				this->OnBeforeRepeatMenuClicked() ;
			}
			break;

		case 51:
			if( GetKeyState( VK_CONTROL ) < 0 )	{
				this->OnAfterRepeatMenuClicked() ;
			}
			break;

		case 52:
			if( GetKeyState( VK_CONTROL ) < 0 )	{
				this->OnSelectionMenuClicked() ;
			}
			break;

		case 53:
			if( GetKeyState( VK_CONTROL ) < 0 )	{
				this->OnSwitchCaseMenuClicked() ;
			}
			break;
		case 54:
			if( GetKeyState( VK_CONTROL ) < 0 )	{
				this->OnArrowMenuClicked() ;
			}
			break;

		default:
			
			break;
	}
	/*
	if ( (GetKeyState ( VK_CONTROL ) & 0x8000) ) {
		
		if ( nChar == 'a' || nChar == 'A' ) {
			DestroyCaret( );
			this->select->GetSelectPaper()->StoreSelectedSymbol( this->paper );
			//새로 할당하고
			select->ReleaseChart( );
			select->ReAllocateChart( );
			//선택한다
			if ( this->paper->GetChart()->GetLength () > 0 ) {
				select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
				select->GetSelectChart( )->DrawChartField( );
			}
			
			this->bSelectedSymbolFlag = TRUE;

			Invalidate( );
		}

		if ( nChar == 'c' || nChar == 'C' ) {
			this->copySymbol->CopySymbols( this->select, this->paper );
		}

		if ( nChar == 'v' || nChar == 'V' ) 
		{	move->GetMovePaperSymbols( )->DeleteAllBasePoints( );
			move->GetMoveChartSymbols( )->DeleteAllBasePoints( );
			this->copySymbol->PasteSymbols( this->select, this->paper );
			this->bSelectedSymbolFlag = TRUE;
			paperList->CaptureLastPaper( paper );
			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
			
		}
		 
		if ( nChar == 'x' || nChar == 'X' ) {
			this->copySymbol->CutSymbols( this->select, this->paper );
			paperList->CaptureLastPaper( paper );
			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
		}

		if( nChar == 'z' || nChar == 'Z' ) {
			if( this->paperList->GetCurrent( ) - 1 > 0 ){

				Paper *undoPaper = this->paperList->Undo( );
				if( this->pen != NULL ){
					//delete this->pen;
					DestroyCaret( );
				}
				paper = undoPaper;
				select->GetSelectPaper( )->ReleaseAllSymbols( );
				select->ReleaseChart( );
				move->GetMovePaperSymbols( )->DeleteAllBasePoints( );
				move->GetMoveChartSymbols( )->DeleteAllBasePoints( );
				Invalidate(FALSE );
				this->bSaveFlag = TRUE;
				this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
			}
		}
		if( nChar == 'y' || nChar == 'Y' ) {
			if( paperList->GetCurrent( ) + 1 <= paperList->GetLength( ) ){
				Paper *redoPaper = this->paperList->Redo(  );
				paper = redoPaper ;
				Invalidate(FALSE );
				this->bSaveFlag = TRUE;
				this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
			}
		}

		if( nChar == 'G' || nChar == 'g' ) {
			if( select->GetSelectPaper( )->GetLength( ) >= 2 ){
			paper->MakeChart( select );
			paperList->CaptureLastPaper( paper );
			select->ReleaseChart( );
			select->ReAllocateChart( );
			select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
			select->GetSelectChart( )->DrawChartField( ) ;
			select->GetSelectPaper( )->ReleaseAllSymbols( );
			Invalidate(FALSE );
			}
		}

		if( nChar == 'u' || nChar == 'U' ) {
			
			if( select->IsChartSelected( ) == true ){
				select->GetSelectPaper( )->ReleaseAllSymbols( );
				paper->ReleaseChart( select );
				paperList->CaptureLastPaper( paper );
				select->ReleaseChart( );
				Invalidate(FALSE );
				this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
			}
		}

		if( nChar == 'n' || nChar == 'N' ) {
			this->OnNewPaperMenuClicked();
		}

		if( nChar == 'o' || nChar == 'O' ) {
			this->OnLoadMenuClicked();
		}

		if( nChar == 's' || nChar == 'S' ) {
			this->OnSaveMenuClicked();
		}

		if( nChar == 'p' || nChar == 'P' ) {
			this->OnPrintMenuClicked();
		}
		if ( nChar == '1' ) {
			this->OnSequenceMenuClicked() ;
		}
		if ( nChar == '2' ) {
			this->OnBeforeRepeatMenuClicked() ;
		}
		if ( nChar == '3' ) {
			this->OnAfterRepeatMenuClicked() ;
		}
		if ( nChar == '4' ) {
			this->OnSelectionMenuClicked() ;
		}
		if ( nChar == '5') {
			this->OnSwitchCaseMenuClicked() ;
		}
	}
	Sticker sticker ;
	// StickingSign
	Long i = 0 ;
	while( i < this->paper->GetLength()  )
	{
		sticker.CheckStickingSign( this->paper , i ) ;
		i ++ ;
	}
	//*/

	Sticker sticker ;
	// StickingSign
	Long i = 0 ;
	while( i < this->paper->GetLength()  )
	{
		sticker.CheckStickingSign( this->paper , i ) ;
		i ++ ;
	}

	Invalidate(FALSE);
}


LRESULT RushNChart::OnIMEComposition( WPARAM wParam, LPARAM lParam )	{
	
	SelectPaper *selectPaper = this->select->GetSelectPaper();
	SelectChart *selectChart = this->select->GetSelectChart();

	Long symbolIndex;

	//식을 써 넣을 위치 확인
	if( this->bSelectedDBLClickedFlag == TRUE && selectPaper != NULL )	{
		SelectedSymbol selectedSymbol = selectPaper->GetAt( 0 );

		symbolIndex = selectedSymbol.GetSeletedSymbolIndex();
	}
	else if( this->bSelectedDBLClickedFlag == FALSE && selectChart == NULL )	{

		if( this->paper->GetLength() > 0 )	{
			symbolIndex = this->paper->GetLength() - 1;
		}
		else	{
			symbolIndex = -1;
		}
	}

	Symbol *symbol = this->paper->GetAt( symbolIndex );

	if( symbolIndex > -1 && ( symbol->GetExpressionEndPointX() - 10 ) > this->pen->GetCurrentPointX() )	{

		CClientDC cDC(this);

		HIMC hImc = ::ImmGetContext( this->GetSafeHwnd() );

		Long length;
		Long currentIndex;
		wchar_t *tempBuffer;
		bool writeFlag = false;

		//조합중
		if( lParam & GCS_COMPSTR )	{

			length = ::ImmGetCompositionString( hImc, GCS_COMPSTR, 0, 0 );
			tempBuffer = new wchar_t [ length ];

			::ImmGetCompositionString( hImc, GCS_COMPSTR, tempBuffer, length );

			tempBuffer [ length - 1 ] = '\0';

			if( length > 0 ) {
				if( this->bComposition == FALSE )	{
					currentIndex = this->pen->GetCurrentIndex();

					this->SetCaret( &cDC, "right", wstring( tempBuffer ) );

				}
				else	{
					currentIndex = this->pen->GetCurrentIndex();

					if( this->caseNumber < 1 )	{
						this->paper->Erase( symbolIndex, currentIndex - 1 );
					}
					else	{
						this->paper->EraseCase( symbolIndex, this->caseNumber, currentIndex - 1 );
					}
				}

				this->bComposition = TRUE;
				writeFlag = true;
			}
			else	{

				if( this->caseNumber < 1 )	{
					this->paper->Erase( symbolIndex, this->pen->GetCurrentIndex() );
				}
				else	{
					this->paper->EraseCase( symbolIndex, this->caseNumber, this->pen->GetCurrentIndex() );
				}

				this->bComposition = FALSE;
				writeFlag = false;
			}
			
			Long index;

			if( writeFlag == true )	{
				if( this->caseNumber < 1 )	{
					index = this->paper->Correct( symbolIndex, currentIndex, wstring ( tempBuffer ) );
				}
				else	{
					index = this->paper->WriteCase( symbolIndex, this->caseNumber, currentIndex, wstring ( tempBuffer ) );
				}
			}
		}
		
		//조합 완성
		if( lParam & GCS_RESULTSTR )	{
			this->bComposition = FALSE;
			
			length = ::ImmGetCompositionString( hImc, GCS_RESULTSTR, 0, 0 );
			tempBuffer = new wchar_t [ length ];

			::ImmGetCompositionString( hImc, GCS_RESULTSTR, tempBuffer, length );

			tempBuffer [ length - 1 ] = '\0';

			//Long index;
			if( length > 0 )	{
				if( this->caseNumber < 1 )	{
					this->paper->Erase( symbolIndex, this->pen->GetCurrentIndex() - 1 );
					this->paper->Correct( symbolIndex, this->pen->GetCurrentIndex(), wstring ( tempBuffer ) );
				}
				else	{
					this->paper->EraseCase( symbolIndex, this->caseNumber, this->pen->GetCurrentIndex() - 1 );
					this->paper->WriteCase( symbolIndex, this->caseNumber, this->pen->GetCurrentIndex(), wstring( tempBuffer ) );
				}
			}
			else	{
				if( this->caseNumber < 1 )	{
					this->paper->Erase( symbolIndex, this->pen->GetCurrentIndex() );
				}
				else	{
					this->paper->EraseCase( symbolIndex, this->caseNumber, this->pen->GetCurrentIndex() );
				}
			}
		}
		

		if( tempBuffer != 0 && writeFlag == true )	{
			delete[] tempBuffer;
		}
		
		::ImmReleaseContext( this->GetSafeHwnd(), hImc );
	
	}

	return 0;
}


void RushNChart::SetWrite( wstring expression )	{
	if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{
		this->bWritingFlag = TRUE; //현재 식을 쓰는 중일때

		SelectPaper *selectPaper = this->select->GetSelectPaper();
		Symbol *symbol;

		if( this->bSelectedDBLClickedFlag == TRUE && selectPaper != NULL )	{
			SelectedSymbol selectedSymbol = selectPaper->GetAt( 0 );

			Long symbolIndex = selectedSymbol.GetSeletedSymbolIndex();

			symbol = this->paper->GetAt( symbolIndex );

			if( dynamic_cast < SwitchCase * > ( symbol ) && this->caseNumber > 0 )	{
				Long index = this->paper->WriteCase( symbolIndex, this->caseNumber, this->pen->GetCurrentIndex(), expression );
					 
			}
			else	{
				if( this->pen->GetCurrentIndex() >= 0 && this->pen->GetCurrentIndex() < symbol->GetExpression().size() )	{
					Long index = this->paper->Correct( symbolIndex, this->pen->GetCurrentIndex(), expression );
				}
				else	{
					Long index = this->paper->Write( symbolIndex, expression );
						 
				}
			}
		}
		else	{
			symbol = this->paper->GetAt( this->paper->GetLength() - 1 );

			if( this->pen->GetCurrentIndex() >= 0 && this->pen->GetCurrentIndex() < symbol->GetExpression().size() )	{
				Long index = this->paper->Correct( this->paper->GetLength() - 1, this->pen->GetCurrentIndex(), expression );
			}
			else	{
				Long index = this->paper->Write( this->paper->GetLength() - 1, expression );
					 
			}
		}
	}
}


void RushNChart::SetCaret( CClientDC *cDC, string direction, wstring expression )	{
	CSize size = cDC->GetTextExtent( expression.c_str() );
	
	Symbol *symbol = NULL;
	if( this->bCompleteStructure == TRUE)	{
		symbol = this->paper->GetAt( this->paper->GetLength() - 1 );
	}
	else if( this->bSelectedDBLClickedFlag == TRUE )	{
		symbol = this->paper->GetAt ( this->select->GetSelectPaper()->GetSelectedSymbolIndex() );
	}

	if ( dynamic_cast < SwitchCase * > ( symbol ) ) {
		if ( this->caseNumber > 0 )	{ 
			if ( direction.compare( "left" ) == 0 )	{
				this->pen->MoveLeft( (size.cx) / 2 );
			}
			else if( direction.compare( "right" ) == 0 ) {
				this->pen->MoveRight( (size.cx) / 2 );
			}
			else if( direction.compare( "leftSwitch" ) == 0 )	{
				this->pen->MoveLeft( size.cx );
			}
			else if( direction.compare( "rightSwitch" ) == 0 )	{
				this->pen->MoveRight( size.cx );
			}
		}
		else {
			if ( direction.compare( "left" ) == 0 )	{
				this->pen->MoveLeft( size.cx );
			}
			else {
				this->pen->MoveRight( size.cx );
			}
		}
	}
	else {
		if ( direction.compare( "left" ) == 0 )	{
			this->pen->MoveLeft( size.cx );
		}
		else {
			this->pen->MoveRight( size.cx );
		}
	}


/*	if( direction.compare( "left" ) == 0 )	{
		if ( dynamic_cast < SwitchCase * > ( symbol ) ) {
			if ( this->caseNumber > 0 )	{ 
				this->pen->MoveLeft( (size.cx)/2 );
			}
			else {
				this->pen->MoveLeft( size.cx );
			}
		}
		else {
			this->pen->MoveLeft( size.cx );
		}
	}
	else	{
		if ( dynamic_cast < SwitchCase * > ( symbol ) ) {
			if ( this->caseNumber > 0 )	{ 
				this->pen->MoveRight( (size.cx)/2 );
			}
			else {
				this->pen->MoveRight( size.cx );
			}
		}
		else {
			this->pen->MoveRight( size.cx );
		}
	}
*/
	POINT point = { this->pen->GetCurrentPointX(), this->pen->GetCurrentPointY() };

	CreateSolidCaret( this->pen->GetWidth(), this->pen->GetHeight() );
	SetCaretPos( point );
	ShowCaret();

}


void	RushNChart::OnPaint()	{
	CPaintDC dc( this );

	dc.SetWindowOrg(this->xPos, this->yPos);	// 스크롤 이동 위치 자동보정

	this->UpdateClient();

	/******더블 버퍼링******/

	// 더블 버퍼링을 위한 메모리DC와 BITMAP 생성
	CDC memDc ;
	CBitmap bitMap ;

	// 더블 버퍼링을 위한 메모리DC와 BITMAP을 현재 DC의 설정과 일치
	memDc.CreateCompatibleDC(&dc);
	//bitMap.CreateCompatibleBitmap( &dc, this->windowWidth, this->windowHeight );
	bitMap.CreateCompatibleBitmap(&dc,this->paperRect.Width(), this->paperRect.Height() );
	memDc.SelectObject(&bitMap);

	//memDc.PatBlt(0,0, this->windowWidth, this->windowHeight, WHITENESS);
	memDc.PatBlt(0,0, this->paperRect.Width(), this->paperRect.Height(), WHITENESS);
	/*************************************** 메모리DC에 그리기 ***************************************/

	if ( this->bLDown == FALSE && this->bSelectedMenu == TRUE 
		 && this->bDragFlag == FALSE ) { //디폴트 심볼 점선 표시용
		this->PaintSymbolDefaultSize( &memDc ) ;
	}
	if( bLDown == TRUE && bSelectedMenu == TRUE )	{// 만들다의 크기 점선표시용
		this->PaintSymbolSize( &memDc ) ;
	}
	// 다중선택하다 점섬 표시 - 채형석
	if ( this->bDragFlag == TRUE )	{ // 다중선택 하다 의 크기 점선표시용
		this->PaintFieldSize( &memDc ) ;
	}
	if ( this->TransNumber != 0 ) {
		this->PaintFieldSize( &memDc );
	}

	this->PaintSymbols( &memDc ) ;
	this->PaintChart( &memDc ) ;

	//고치기 이동시 선택 해제 수정 - this->TransNumber == 0 일떄 / 6월 23일
	if ( this->bSelectedSymbolFlag == TRUE		&&	this->bSelectedMenu == FALSE && this->bMovedSymbolFlag ==FALSE && this->TransNumber == 0 )	{
		this->SelectDisplay ( &memDc ) ;
	}
	if ( this->bSelectedDBLClickedFlag == TRUE )	{
		//Select 수정할때 수정해주세요!
		//this->SelectExpressionDisplay ( &dc );
	}
	
	
	//StickerPreView
	if ( this->dotSticker != 0 ) 
	{
		this->DisplayDotSticker(&memDc) ;
		if( this->dotSticker != 0)
		{
			delete this->dotSticker ;
			this->dotSticker = 0 ;
		}
	}
	if ( this->dotStickers != 0 ) 
	{
		this->DisplayDotStickers( &memDc ) ;
		if( this->dotStickers != 0 ) //this->dotStickers 초기화
		{
			Long j = 0 ;
			while( j < this->selectedSymbolLength ) 
			{
				if( this->dotStickers[j] != 0 )
				{
					delete this->dotStickers[ j ] ;
				}
				j++ ;
			}
			delete[] this->dotStickers ;
			this->dotStickers = 0 ;
		}
	}
	//*/

	// MovePreview
	if( this->bMovePreivew == TRUE ) 
	{
		this->MovePreview( &memDc ) ;
		//this->MovePreviewForChart( &memDc ) ;
	}

	// 메모리DC에 그려진 내용을 현재 DC에 복사 
	//dc.BitBlt(0, 0, this->windowWidth, this->windowHeight, &memDc, 0, 0, SRCCOPY);	
	dc.BitBlt(0, 0, this->paperRect.Width(), this->paperRect.Height(), &memDc, 0, 0, SRCCOPY);	

	//인쇄 미리보기
	if(this->preViewDlg != NULL){
		this->preViewDlg->DisplayPreView(&memDc);//DC넘겨주기
		Invalidate(FALSE);
	}

	// 사용된 메모리DC와 BITMAP을 삭제
	memDc.DeleteDC();
	bitMap.DeleteObject();

	this->ReleaseDC(&memDc);
	this->ReleaseDC(&dc);
}


void	RushNChart::PaintFieldSize( CDC *memDc ) {
		CPen pen;
		CPen *oldPen;

		pen.CreatePen( PS_DOT,1,RGB(0,0,0) );
		oldPen = memDc->SelectObject( &pen );

		Long startX = startPositionX ;
		Long startY = startPositionY ;
		Long endX = endPositionX ;
		Long endY = endPositionY ;
		Long tempX = startX ;
		Long tempY = startY ;

		if ( startX > endX ) {
			startX = endX ;
			endX = tempX ;
		}
		if ( startY > endY ) {
			startY = endY ;
			endY = tempY ;
		}

		memDc->MoveTo( startX , startY ); 
		memDc->LineTo( endX, startY );
		memDc->LineTo( endX, endY );
		memDc->LineTo( startX, endY );
		memDc->LineTo( startX, startY );
}


void	RushNChart::PaintSymbolDefaultSize( CDC *memDc ) {

		CPen pen;
		CPen *oldPen;

		pen.CreatePen( PS_SOLID,1,RGB(0,0,0) );
		oldPen = memDc->SelectObject( &pen );
		
		if ( this->symbol.compare("Sequence") == 0 ) {
			memDc->MoveTo( startPositionX , startPositionY );
			memDc->LineTo( startPositionX+280, startPositionY );
			memDc->LineTo( startPositionX+280, startPositionY+40 );
			memDc->LineTo( startPositionX, startPositionY+40 );
			memDc->LineTo( startPositionX, startPositionY );
		
			wstring expression = L"Sequnece" ;

			CRect expressionRect( startPositionX+110, startPositionY+8 , startPositionX+230, startPositionY+32 );
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE );

		}
		else if ( this->symbol.compare("Selection") == 0 ) {
			memDc->MoveTo( startPositionX, startPositionY );
			memDc->LineTo( startPositionX+280, startPositionY );
			memDc->LineTo( startPositionX+280, startPositionY+40 );
			memDc->LineTo( startPositionX, startPositionY+40 );
			memDc->LineTo( startPositionX, startPositionY );
			memDc->LineTo( startPositionX+140, startPositionY+40 );
			memDc->LineTo( startPositionX+280, startPositionY );

			wstring expression = L"Selection" ;
			CRect expressionRect( startPositionX+110, startPositionY+8 , startPositionX+230, startPositionY+32 );
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE );

			wstring conditionTrue = L"TRUE" ;
			CRect conditionTrueRect(startPositionX+5, startPositionY+25, startPositionX+70, startPositionY+39 );
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_VCENTER | DT_LEFT | DT_SINGLELINE );

			wstring conditionFalse = L"FALSE" ;
			CRect conditionFalseRect(startPositionX+218, startPositionY+25, startPositionX+275, startPositionY+39 );
			memDc->DrawText( conditionFalse.c_str(), conditionFalseRect, DT_VCENTER | DT_RIGHT | DT_SINGLELINE );

		}
		else if ( this->symbol.compare("BeforeRepeat") == 0 ) {
			memDc->MoveTo( startPositionX, startPositionY );
			memDc->LineTo( startPositionX+280, startPositionY );
			memDc->LineTo( startPositionX+280, startPositionY+40 );
			memDc->LineTo( startPositionX+40, startPositionY+40 );
			memDc->LineTo( startPositionX+40, startPositionY+120 );
			memDc->LineTo( startPositionX, startPositionY+120 );
			memDc->LineTo( startPositionX, startPositionY );

			wstring expression = L"BeforeRepeat" ;

			CRect expressionRect( startPositionX+110, startPositionY+8 , startPositionX+230, startPositionY+32 );
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE );

		}
		else if ( this->symbol.compare("AfterRepeat") == 0 ) {
			memDc->MoveTo( startPositionX, startPositionY );
			memDc->LineTo( startPositionX+40, startPositionY );
			memDc->LineTo( startPositionX+40, startPositionY+80 );
			memDc->LineTo( startPositionX+280, startPositionY+80 );
			memDc->LineTo( startPositionX+280, startPositionY+120 );
			memDc->LineTo( startPositionX, startPositionY+120 );
			memDc->LineTo( startPositionX, startPositionY );

			wstring expression = L"AfterRepeat" ;

			CRect expressionRect( startPositionX+110, startPositionY+88 , startPositionX+230, startPositionY+112 );
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE );

		}
		else if ( this->symbol.compare("SwitchCase") == 0 && this->columnCount > 0 ) {

			Long count = this->columnCount ;
			Long width = 280 / (count+2) ;

			memDc->MoveTo( startPositionX, startPositionY ) ;
			memDc->LineTo( startPositionX+280, startPositionY );
			memDc->LineTo( startPositionX+280, startPositionY+40 );
			memDc->LineTo( startPositionX, startPositionY+40 );
			memDc->LineTo( startPositionX, startPositionY );
			memDc->LineTo( startPositionX+280-width, startPositionY+40 );
			memDc->LineTo( startPositionX+280, startPositionY );

			memDc->MoveTo( startPositionX, startPositionY+40 ) ;
			memDc->LineTo( startPositionX, startPositionY+80 ) ;
			memDc->LineTo( startPositionX+280-width, startPositionY+80 ) ;
			memDc->LineTo( startPositionX+280-width, startPositionY+40 ) ;

			Long i = 1 ;
			while ( i <= count ) {
				memDc->MoveTo( startPositionX + (width*i), startPositionY+40 ) ;
				memDc->LineTo( startPositionX + (width*i), startPositionY+80 ) ;
				i++ ;
			}
			wstring expression = L"SwitchCase" ;
			CRect expressionRect( startPositionX+140, startPositionY+8 , startPositionX+270, startPositionY+32 );
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );

			wstring conditionTrue = L"TRUE" ;
			CRect conditionTrueRect(startPositionX+5, startPositionY+25, startPositionX+40, startPositionY+39 );
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_VCENTER | DT_LEFT | DT_SINGLELINE );

			wstring conditionFalse = L"FALSE" ;
			CRect conditionFalseRect(startPositionX+218, startPositionY+25, startPositionX+275, startPositionY+39 );
			memDc->DrawText( conditionFalse.c_str(), conditionFalseRect, DT_VCENTER | DT_RIGHT | DT_SINGLELINE );

		}
		else if ( this->symbol.compare("Arrow") == 0 ) {

		
			memDc->MoveTo( startPositionX , startPositionY );
			memDc->LineTo( startPositionX, startPositionY+40 );
			memDc->MoveTo( startPositionX-10, startPositionY+30 );
			memDc->LineTo( startPositionX, startPositionY+40 );
			memDc->LineTo( startPositionX+10, startPositionY+30 );
		
		}

		memDc->SelectObject( oldPen );;
		pen.DeleteObject( );
}


void	RushNChart::PaintSymbolSize( CDC *memDc ) {

		CPen pen;
		CPen *oldPen;

		pen.CreatePen( PS_DOT,1,RGB(0,0,0) );
		oldPen = memDc->SelectObject( &pen );

		memDc->MoveTo( startPositionX, startPositionY );
		memDc->LineTo( endPositionX, startPositionY );
		memDc->LineTo( endPositionX, endPositionY );
		memDc->LineTo( startPositionX, endPositionY );
		memDc->LineTo( startPositionX, startPositionY );

		memDc->SelectObject( oldPen );;
		pen.DeleteObject( );
		
}


void	RushNChart::PaintSymbols( CDC *memDc )	{
	Symbol *temp;

	Long startPointX;
	Long startPointY;
	Long endPointX;
	Long endPointY;
	Long middlePointX;
	Long middlePointY;
	Long expressionStartPointX;
	Long expressionStartPointY;
	Long expressionEndPointX;
	Long expressionEndPointY;
	//Long columnCount;
	

	wstring expression;

	for( Long i = 0; i < this->paper->GetLength(); i++ )
	{
		temp = this->paper->GetAt( i );
	
		startPointX = temp->GetStartPointX();
		startPointY = temp->GetStartPointY();
		endPointX = temp->GetEndPointX();
		endPointY = temp->GetEndPointY();

		expressionStartPointX = temp->GetExpressionStartPointX();
		expressionStartPointY = temp->GetExpressionStartPointY();
		expressionEndPointX = temp->GetExpressionEndPointX( );
		expressionEndPointY = temp->GetExpressionEndPointY( );

		expression = temp->GetExpression();
	
		if( dynamic_cast< Sequence * > ( temp ) )	{
			Sequence *sequence = static_cast< Sequence * > ( temp );

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY);
			memDc->LineTo( startPointX, startPointY );
		
			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			//memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_WORD_ELLIPSIS );

		}
		else if( dynamic_cast< BeforeRepeat * > ( temp ) )	{
			BeforeRepeat *symbol = static_cast< BeforeRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX();
			middlePointY = symbol->GetMiddlePointY();

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, middlePointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( middlePointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );

			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			//memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_WORD_ELLIPSIS );

		}
		else if( dynamic_cast< AfterRepeat * > ( temp ) )	{
			AfterRepeat *symbol = static_cast< AfterRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX();
			middlePointY = symbol->GetMiddlePointY();

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, middlePointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );

			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			//memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_WORD_ELLIPSIS );
		}
		else if( dynamic_cast< Selection * > ( temp ) )	{
			Selection *symbol = static_cast< Selection * > ( temp );

			middlePointX = symbol->GetMiddlePointX();
			middlePointY = symbol->GetMiddlePointY();

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, startPointY );

			CRect expressionRect(expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			//memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_WORD_ELLIPSIS );

			wstring conditionTrue = L"TRUE" ;
			CRect conditionTrueRect(startPointX+5,endPointY-15, startPointX+50, endPointY-1 );
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_LEFT | DT_SINGLELINE );

			wstring conditionFalse = L"FALSE" ;
			CRect conditionFalseRect(endPointX-60, endPointY-15, endPointX-5, endPointY-1 );
			memDc->DrawText( conditionFalse.c_str(), conditionFalseRect, DT_RIGHT | DT_SINGLELINE );

		}

		else if( dynamic_cast< SwitchCase * > ( temp ) )	
		{
			SwitchCase *symbol = static_cast< SwitchCase * > ( temp );
			Selection *selection = symbol->GetSelection ( );

			memDc->MoveTo ( selection->GetStartPointX(), selection->GetStartPointY() );
			memDc->LineTo ( selection->GetEndPointX(), selection->GetStartPointY() );
			memDc->LineTo ( selection->GetEndPointX(), selection->GetEndPointY() );
			memDc->LineTo ( selection->GetStartPointX(), selection->GetEndPointY() );
			memDc->LineTo ( selection->GetStartPointX(), selection->GetStartPointY() );
			memDc->LineTo ( selection->GetMiddlePointX(), selection->GetMiddlePointY() );
			memDc->LineTo ( selection->GetEndPointX(), selection->GetStartPointY() );

			wstring conditionTrue = L"TRUE" ;
			CRect conditionTrueRect( startPointX+5,selection->GetMiddlePointY()-15, startPointX+50, selection->GetMiddlePointY()-1 );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_LEFT | DT_SINGLELINE );

			wstring conditionFalse = L"FALSE" ;
			CRect conditionFalseRect( endPointX-60, selection->GetMiddlePointY()-15, endPointX-5, selection->GetMiddlePointY()-1 );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( conditionFalse.c_str(), conditionFalseRect, DT_RIGHT | DT_SINGLELINE );

			for ( Long j = 0; j < symbol->GetLength(); j++ )	{
				Sequence *tempCase = symbol->GetCases ( j );

				memDc->MoveTo ( tempCase->GetStartPointX(), tempCase->GetStartPointY() );
				memDc->LineTo ( tempCase->GetEndPointX(), tempCase->GetStartPointY() );
				memDc->LineTo ( tempCase->GetEndPointX(), tempCase->GetEndPointY() );
				memDc->LineTo ( tempCase->GetStartPointX(), tempCase->GetEndPointY() );
				memDc->LineTo ( tempCase->GetStartPointX(), tempCase->GetStartPointY() );

				CRect expressionRect ( tempCase->GetExpressionStartPointX(), tempCase->GetExpressionStartPointY(),
					tempCase->GetExpressionEndPointX(), tempCase->GetExpressionEndPointY() );
				memDc->SetBkMode(TRANSPARENT);
				memDc->DrawText ( tempCase->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE|DT_CENTER );

			}

			CRect expressionRect ( selection->GetExpressionStartPointX(), selection->GetExpressionStartPointY(), selection->GetExpressionEndPointX(), selection->GetExpressionEndPointY() );
			memDc->SetBkMode(TRANSPARENT);
			//memDc->DrawText ( selection->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
			memDc->DrawText( selection->GetExpression().c_str(), expressionRect, DT_VCENTER | DT_WORD_ELLIPSIS );


		}
		else if( dynamic_cast< Arrow * > ( temp ) )	{
			Arrow *symbol = static_cast< Arrow * > ( temp );

			memDc->MoveTo( startPointX , startPointY );
			memDc->LineTo( startPointX , endPointY );
			memDc->MoveTo( startPointX - 10, endPointY-10 );
			memDc->LineTo( startPointX , endPointY);
			memDc->LineTo( startPointX + 10, endPointY-10 );
		}
		
	}

}
void	RushNChart::PaintChart( CDC *memDc ) {
	Symbol *temp;

	Long startPointX;
	Long startPointY;
	Long endPointX;
	Long endPointY;
	Long middlePointX;
	Long middlePointY;
	Long expressionStartPointX;
	Long expressionStartPointY;
	Long expressionEndPointX;
	Long expressionEndPointY;
	//Long columnCount;

	wstring expression;

	CPen *oldPen ;
	CBrush *oldBrush ;
	CPen pen ;
	CBrush chartBrush ;
	CBrush sequenceBrush ;
	CBrush startOrStopBrush ;
	CBrush beforeRepeatBrush ;
	CBrush afterRepeatBrush ;
	CBrush selectionBrush ;
	CBrush switchCaseBrush ;

	pen.CreatePen( PS_INSIDEFRAME,1,RGB(0,0,0) );
	chartBrush.CreateHatchBrush(10,RGB(0,255,255));
	startOrStopBrush.CreateSolidBrush(RGB(255,234,234));
	sequenceBrush.CreateSolidBrush(RGB(255,255,228));
	beforeRepeatBrush.CreateSolidBrush(RGB(224,255,219));
	afterRepeatBrush.CreateSolidBrush(RGB(230,255,255));
	selectionBrush.CreateSolidBrush(RGB(255,235,254));
	switchCaseBrush.CreateSolidBrush(RGB(255,217,236));
	
	oldPen = memDc->SelectObject ( &pen);

	for( Long i = 0; i < this->paper->GetChart()->GetLength(); i++ )
	{
		temp = this->paper->GetChart()->GetAt( i );
	
		startPointX = temp->GetStartPointX();
		startPointY = temp->GetStartPointY();
		endPointX = temp->GetEndPointX();
		endPointY = temp->GetEndPointY();

		expressionStartPointX = temp->GetExpressionStartPointX();
		expressionStartPointY = temp->GetExpressionStartPointY();
		expressionEndPointX = temp->GetExpressionEndPointX( );
		expressionEndPointY = temp->GetExpressionEndPointY( );

		expression = temp->GetExpression();
	
		if( dynamic_cast< Sequence * > ( temp ) )	{

			if ( expression.compare(L"start")==0 || expression.compare(L"Start")==0 || expression.compare(L"START")==0 ||
				 expression.compare(L"stop")==0 || expression.compare(L"Stop")==0 || expression.compare(L"STOP")==0 ) {
				oldBrush = memDc->SelectObject( &startOrStopBrush ) ;
			}
			else {
				oldBrush = memDc->SelectObject( &sequenceBrush ) ;
			}
			memDc->Rectangle( startPointX, startPointY, endPointX, endPointY) ;

			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			if ( expression.compare(L"start")==0 || expression.compare(L"Start")==0 || expression.compare(L"START")==0 ||
				 expression.compare(L"stop")==0 || expression.compare(L"Stop")==0 || expression.compare(L"STOP")==0 ) {
				memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE | DT_CENTER );
			}
			else{
				memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE );
			}
		}
		else if( dynamic_cast< BeforeRepeat * > ( temp ) )	{
			BeforeRepeat *symbol = static_cast< BeforeRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX();
			middlePointY = symbol->GetMiddlePointY();

			oldBrush = memDc->SelectObject( &beforeRepeatBrush ) ;
			POINT before[6] = {{startPointX, startPointY}, {endPointX, startPointY}, {endPointX, middlePointY},
								{middlePointX, middlePointY}, {middlePointX, endPointY}, {startPointX, endPointY}};
			memDc->Polygon(before,6);

			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE );
		}
		else if( dynamic_cast< AfterRepeat * > ( temp ) )	{
			AfterRepeat *symbol = static_cast< AfterRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX();
			middlePointY = symbol->GetMiddlePointY();

			oldBrush = memDc->SelectObject( &afterRepeatBrush ) ;
			POINT before[6] = {{startPointX, startPointY}, {middlePointX, startPointY}, {middlePointX, middlePointY},
								{endPointX, middlePointY}, {endPointX, endPointY}, {startPointX, endPointY}};
			memDc->Polygon(before,6);

			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE );
		}
		else if( dynamic_cast< Selection * > ( temp ) )	{
			Selection *symbol = static_cast< Selection * > ( temp );

			middlePointX = symbol->GetMiddlePointX();
			middlePointY = symbol->GetMiddlePointY();

			oldBrush = memDc->SelectObject( &selectionBrush ) ;
			
			memDc->Rectangle(startPointX, startPointY, endPointX, endPointY) ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, startPointY );

			CRect expressionRect(expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE );

			wstring conditionTrue = L"TRUE" ;
			CRect conditionTrueRect(startPointX+5,endPointY-30, startPointX+40, endPointY-5 );
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_LEFT | DT_SINGLELINE );

			wstring conditionFalse = L"FALSE" ;
			CRect conditionFalseRect(endPointX-60, endPointY-30, endPointX-5, endPointY-5 );
			memDc->DrawText( conditionFalse.c_str(), conditionFalseRect, DT_RIGHT | DT_SINGLELINE );
		}

		else if( dynamic_cast< SwitchCase * > ( temp ) )	
		{
			SwitchCase *symbol = static_cast< SwitchCase * > ( temp );
			Selection *selection = symbol->GetSelection ( );

			oldBrush = memDc->SelectObject( &switchCaseBrush ) ;

			memDc->Rectangle ( selection->GetStartPointX(), selection->GetStartPointY() , selection->GetEndPointX(), selection->GetEndPointY() );

			memDc->MoveTo ( selection->GetStartPointX(), selection->GetStartPointY() );
			memDc->LineTo ( selection->GetMiddlePointX(), selection->GetMiddlePointY() );
			memDc->LineTo ( selection->GetEndPointX(), selection->GetStartPointY() );

			CRect expressionRect ( selection->GetExpressionStartPointX(), selection->GetExpressionStartPointY(), selection->GetExpressionEndPointX(), selection->GetExpressionEndPointY() );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText ( selection->GetExpression().c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE );

			wstring conditionTrue = L"TRUE" ;
			CRect conditionTrueRect(startPointX+5,selection->GetMiddlePointY()-15, startPointX+50, selection->GetMiddlePointY()-1 );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_LEFT | DT_SINGLELINE );

			wstring conditionFalse = L"FALSE" ;
			CRect conditionFalseRect(endPointX-60, selection->GetMiddlePointY()-15, endPointX-5, selection->GetMiddlePointY()-1 );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( conditionFalse.c_str(), conditionFalseRect, DT_RIGHT | DT_SINGLELINE );

			for ( Long j = 0; j < symbol->GetLength(); j++ )	{
				Sequence *tempCase = symbol->GetCases ( j );

				memDc->Rectangle ( tempCase->GetStartPointX(), tempCase->GetStartPointY() , tempCase->GetEndPointX(), tempCase->GetEndPointY() ) ;
				CRect expressionRect ( tempCase->GetExpressionStartPointX(), tempCase->GetExpressionStartPointY(),
					tempCase->GetExpressionEndPointX(), tempCase->GetExpressionEndPointY() );
				
				memDc->DrawText ( tempCase->GetExpression().c_str(), expressionRect, DT_VCENTER | DT_SINGLELINE );

			}
		}
		else if( dynamic_cast< Arrow * > ( temp ) )	{
			Arrow *symbol = static_cast< Arrow * > ( temp );

			memDc->MoveTo( startPointX , startPointY );
			memDc->LineTo( startPointX , endPointY );
			memDc->MoveTo( startPointX - 10, endPointY-10 );
			memDc->LineTo( startPointX , endPointY);
			memDc->LineTo( startPointX + 10, endPointY-10 );
		}

	}

}


void	RushNChart::SelectDisplay ( CDC *memDc )	{  // 수정 : 채 형 석 - > 곽 욱 현
	CPen pen;
	CPen chartPen ;
	CPen *oldPen;

	pen.CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	oldPen = memDc->SelectObject( &pen );

	CBrush brush ;
	brush.CreateSolidBrush(RGB(0,255,255)) ;
	CBrush *oldBrush = memDc->SelectObject( &brush ) ;


	for( Long i = 0; i < this->select->GetSelectPaper( )->GetLength( ); i++ ){

		SelectedSymbol select = this->select->GetSelectPaper()->GetAt(i);
		if ( select.GetLeftTopStartPointX() > -1 )	{
			memDc->Rectangle( select.GetLeftTopStartPointX(), select.GetLeftTopStartPointY(),
							select.GetLeftTopEndPointX(),select.GetLeftTopEndPointY());
		}
			memDc->Rectangle( select.GetMiddleTopStartPointX(), select.GetMiddleTopStartPointY(),
							select.GetMiddleTopEndPointX(), select.GetMiddleTopEndPointY() );
		if ( select.GetRightTopStartPointX() > -1 )	{
			memDc->Rectangle( select.GetRightTopStartPointX(), select.GetRightTopStartPointY(), 
							select.GetRightTopEndPointX(), select.GetRightTopEndPointY() );
		}
			memDc->Rectangle( select.GetRightMiddleStartPointX(), select.GetRightMiddleStartPointY(),
							select.GetRightMiddleEndPointX(), select.GetRightMiddleEndPointY() );
		if ( select.GetRightBottomStartPointX() > -1 )	{
			memDc->Rectangle( select.GetRightBottomStartPointX(), select.GetRightBottomStartPointY(),
							select.GetRightBottomEndPointX(), select.GetRightBottomEndPointY() );
		}
			memDc->Rectangle( select.GetMiddleBottomStartPointX(), select.GetMiddleBottomStartPointY(),
							select.GetMiddleBottomEndPointX(), select.GetMiddleBottomEndPointY() );
		if ( select.GetLeftBottomStartPointX() > -1 )	{
			memDc->Rectangle( select.GetLeftBottomStartPointX(), select.GetLeftBottomStartPointY(),
							select.GetLeftBottomEndPointX(), select.GetLeftBottomEndPointY() );
		}
		if ( select.GetLeftMiddleStartPointX() > -1 )	{
			memDc->Rectangle( select.GetLeftMiddleStartPointX(), select.GetLeftMiddleStartPointY(),
							select.GetLeftMiddleEndPointX(), select.GetLeftMiddleEndPointY() );
		}

		if ( select.GetMiddleStartPointX() > -1 )	{
			memDc->Ellipse( select.GetMiddleStartPointX(), select.GetMiddleStartPointY(),
				select.GetMiddleEndPointX(), select.GetMiddleEndPointY() );
		}
	}
		
	bool ret = select->IsChartSelected( );

	if( ret == true ){

		chartPen.CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
		oldPen = memDc->SelectObject( &chartPen );

		memDc->MoveTo( select->GetSelectChart()->GetFieldStartPointX(), select->GetSelectChart()->GetFieldStartPointY());
		memDc->LineTo( select->GetSelectChart()->GetFieldEndPointX(), select->GetSelectChart()->GetFieldStartPointY());
		memDc->LineTo( select->GetSelectChart()->GetFieldEndPointX(), select->GetSelectChart()->GetFieldEndPointY());
		memDc->LineTo( select->GetSelectChart()->GetFieldStartPointX(), select->GetSelectChart()->GetFieldEndPointY());
		memDc->LineTo( select->GetSelectChart()->GetFieldStartPointX(), select->GetSelectChart()->GetFieldStartPointY());

		memDc->Rectangle(  select->GetSelectChart( )->GetLeftTopStartPointX(),  select->GetSelectChart( )->GetLeftTopStartPointY(),
						 select->GetSelectChart( )->GetLeftTopEndPointX(), select->GetSelectChart( )->GetLeftTopEndPointY());

		memDc->Rectangle(  select->GetSelectChart( )->GetMiddleTopStartPointX(),  select->GetSelectChart( )->GetMiddleTopStartPointY(),
						 select->GetSelectChart( )->GetMiddleTopEndPointX(),  select->GetSelectChart( )->GetMiddleTopEndPointY() );

		memDc->Rectangle( select->GetSelectChart( )->GetRightTopStartPointX(), select->GetSelectChart( )->GetRightTopStartPointY(), 
						select->GetSelectChart( )->GetRightTopEndPointX(), select->GetSelectChart( )->GetRightTopEndPointY() );

		memDc->Rectangle( select->GetSelectChart( )->GetRightMiddleStartPointX(), select->GetSelectChart( )->GetRightMiddleStartPointY(),
						select->GetSelectChart( )->GetRightMiddleEndPointX(), select->GetSelectChart( )->GetRightMiddleEndPointY() );

		memDc->Rectangle( select->GetSelectChart( )->GetRightBottomStartPointX(), select->GetSelectChart( )->GetRightBottomStartPointY(),
						select->GetSelectChart( )->GetRightBottomEndPointX(), select->GetSelectChart( )->GetRightBottomEndPointY() );

		memDc->Rectangle( select->GetSelectChart( )->GetMiddleBottomStartPointX(), select->GetSelectChart( )->GetMiddleBottomStartPointY(),
						select->GetSelectChart( )->GetMiddleBottomEndPointX(), select->GetSelectChart( )->GetMiddleBottomEndPointY() );

		memDc->Rectangle( select->GetSelectChart( )->GetLeftBottomStartPointX(), select->GetSelectChart( )->GetLeftBottomStartPointY(),
						select->GetSelectChart( )->GetLeftBottomEndPointX(), select->GetSelectChart( )->GetLeftBottomEndPointY() );

		memDc->Rectangle( select->GetSelectChart( )->GetLeftMiddleStartPointX(), select->GetSelectChart( )->GetLeftMiddleStartPointY(),
						select->GetSelectChart( )->GetLeftMiddleEndPointX(), select->GetSelectChart( )->GetLeftMiddleEndPointY() );

	}


	memDc->SelectObject( oldPen );;
	pen.DeleteObject( );
	chartPen.DeleteObject() ;
	memDc->SelectObject( oldBrush) ;
	brush.DeleteObject();
}


/*
	함수이름 : CtrlSelected
	설    명 : 다중선택하다 Ctrl 키 입력시 함수
	입    력 : Ponit X, Point Y
	출    력 : index
	만 든 이 : 채 형 석 - > 곽욱현
*/
Long	RushNChart::CtrlSelected ( Long pointX, Long pointY ) {
	Long	paperIndex;
	//Long	chartIndex;
	Long	checkDuIndex;
	Long	index = -1;
	paperIndex = this->select->GetSelectPaper()->CheckSymbol( paper, pointX, pointY );
	bool checkDuChart;
	
	//차트라면
	if ( paperIndex == - 1 ) {
		
		//select->GetSelectPaper( )->ReleaseAllSymbols( );
		bool checkChart = select->GetSelectChart( )->CheckChart( paper->GetChart( ), pointX, pointY );
		//차트의 기호이면
		if ( checkChart == true ){
			//중복인지 아닌지 확인한다.
			checkDuChart = select->IsChartSelected( );
			//이미 선택이 되어있다면
			if( checkDuChart == true ) {
				//차트를 선택해제한다.
				select->ReleaseChart( );

			}
			//중복이 아니라면
			else{
				index = 0 ;
				//새로 할당하고
				select->ReleaseChart( );
				select->ReAllocateChart( );
				//선택한다
				select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
				select->GetSelectChart( )->DrawChartField( );
				Invalidate( FALSE);
			}
		}
	}
	//종이의 기호이면.
	else {
		checkDuIndex = this->select->GetSelectPaper()->CheckDuplication( paperIndex );

		if ( checkDuIndex != - 1 ) {
			//중복이면
			index = this->select->GetSelectPaper()->Release( checkDuIndex );
		}
		else {
			//중복이 아니면
			index = this->select->GetSelectPaper()->StoreSelectedSymbol( paper,paperIndex );
		}
	}

	return index;
}

/*
	함수이름 : SelectCheck
	설    명 : 단일 선택하다 함수
	입    력 : Ponit X, Point Y
	출    력 : index
	만 든 이 : 채형석 - > 곽욱현
*/
Long	RushNChart::SelectCheck ( Long pointX, Long pointY ) {
	Long	paperIndex;
	//bool isChartSelected;
	bool checkChart;
	Long	index = -1;

	SelectPaper *selectPaper = select->GetSelectPaper( );
	SelectChart *selectChart = select->GetSelectChart( );

	Long checkDuIndex;
	
	//this->select->GetSelectChart()->ReleaseAllSymbols();
	//this->select->GetSelectPaper()->ReleaseAllSymbols();

	paperIndex = this->select->GetSelectPaper()->CheckSymbol( paper, pointX, pointY );
	//종이의 기호가 아닐때 
	if ( paperIndex == - 1 ) {
		//기호가 차트의 기호인지 확인한다.
		//종이의 기호들을 모두 선택 해제하고
		select->GetSelectPaper( )->ReleaseAllSymbols( );
		//차트를 확인한다.
		checkChart = select->GetSelectChart( )->CheckChart( paper->GetChart( ), pointX, pointY );
		//차트의 기호이면
		if ( checkChart == true ){
			index = 0 ;
			//새로 할당하고
			select->ReleaseChart( );
			select->ReAllocateChart( );
		
			//선택한다
			select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
			select->GetSelectChart( )->DrawChartField( );
			Invalidate( FALSE);

			
		}
		
	
			//차트의 기호가 아니면
		else{
			//선택된 차트를 해제한다.
			select->ReleaseChart( );
			Invalidate(FALSE );
		}

	}
	else {
		//차트를 할당 해제한다...새로운 종이의기호를 선택할 경우!! 
		select->ReleaseChart( );

		checkDuIndex = selectPaper->CheckDuplication( paperIndex );
		//중복이 아니면
		if( checkDuIndex == -1 ){
			//종이의 기호들도 선택 해제시킨다.
			this->select->GetSelectPaper()->ReleaseAllSymbols();
			//새로운 기호를 저장하고
			index = select->GetSelectPaper( )->StoreSelectedSymbol( paper, paperIndex );
		}
		//중복인 경우
		else{
			index = selectPaper->GetLength( ) -1;
		}
	}

	return index;
}

/*
	함수이름 : DragSelected
	설    명 : 다중선택 함수 드레그 할 떄
	입    력 : startPonit X, startPoint Y, endPoint X, endPoint Y
	출    력 : index
	만 든 이 : 채형석
*/
Long	RushNChart::DragSelected ( Long startPointX, Long startPointY, Long endPointX, Long endPointY ) {
	Long	index;

	index = this->select->GetSelectPaper()->CheckSymbols( paper, startPointX, startPointY, endPointX, endPointY );
//	index = this->select->GetSelectChart()->CheckSymbols( paper->GetChart(), startPointX, startPointY, endPointX, endPointY );
	
	return index;
}


/*
	함수이름 : StickOnPaperWhenDraw
	설    명 : 그릴 때 붙여 그린다
	입    력 : Long startX, Long startY, Long index
	출    력 : void
	만 든 이 : i5
*/
void	RushNChart::StickOnPaperWhenDraw( Long startX, Long startY, Long index ) {

	Sticker sticker ;


	//붙일 정보를 가져온다
	sticker.CheckStickingField( this->paper, this->select, index ) ;
	
	if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// 붙이는 상황이면
	{
			
		//붙일 기호의 위치와 크기를 정하다
		sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), index ) ;
		
		//기호를 붙여 그리다 //기존 기호는 지운다
		sticker.StickTo( this->paper, sticker.GetStartX(), sticker.GetStartY(), sticker.GetEndX(), sticker.GetEndY(), paper->GetAt(index)->GetExpression(), this->symbol, index ) ;
		
	}
	
	// StickingSign
	for( Long i = 0 ; i < this->paper->GetLength() ; i++){
		sticker.CheckStickingSign( this->paper, i ) ;
	}

}
/*
	함수이름 : StickOnPaperWhenMove
	설    명 : 이동 할 때 붙인다 
	입    력 : Long startX, Long startY, Long index
	출    력 : void
	만 든 이 : i5
*/
void	RushNChart::StickOnPaperWhenMove( Long startX, Long startY, Long index ) {

	Sticker sticker ;
	sticker.CheckStickingFieldForMove( this->paper, this->select, index, 0 ,0 ) ;
	
	if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// 붙이는 상황이면
	{
			
		//붙일 기호의 위치와 크기를 정하다
		sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), index ) ;
		string type = this->paper->CheckType( index ) ;
		//기호를 붙여 그리다 //기존 기호는 지운다
		sticker.StickTo( this->paper, sticker.GetStartX(), sticker.GetStartY(), sticker.GetEndX(), sticker.GetEndY(), paper->GetAt(index)->GetExpression(), type, index ) ;
		
	}
	
	// StickingSign
	Long i = 0 ;
	for( Long i = 0 ; i < this->paper->GetLength() ; i++){
		sticker.CheckStickingSign( this->paper, i ) ;
	}

}

/*
	함수이름 : StickOnPaperWhenMoveBudle
	설    명 : 다중 선택된 기호들을 이동 할 때 붙인다 
	입    력 : void
	출    력 : void
	만 든 이 : i5
*/
void RushNChart::StickOnPaperWhenMoveBudle() {
	Sticker sticker ;
	sticker.SearchTopBottom( this->paper, this->select ) ;
	sticker.CheckStickingFieldForMove( this->paper, this->select, sticker.GetTopIndex(), 0 ,0 ) ;

	if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// 붙이는 상황이면
	{
		sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), sticker.GetTopIndex() ) ;
		sticker.GetGap( this->paper, sticker.GetTopIndex()  ) ;
		sticker.StickBundleTo( paper, select, sticker.GetStartGapX(), sticker.GetStartGapY() ) ;

		this->select->GetSelectPaper()->ReNewSelected( paper ) ;
		
	}
	else {
		sticker.CheckStickingFieldForMove( this->paper, this->select, sticker.GetBottonIndex(), 0 ,0 ) ; ;
		
		if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// 붙이는 상황이면
		{
			sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), sticker.GetBottonIndex() ) ;
			sticker.GetGap( this->paper, sticker.GetBottonIndex()  ) ;
			sticker.StickBundleTo( paper, select, sticker.GetStartGapX(), sticker.GetStartGapY() ) ;

			this->select->GetSelectPaper()->ReNewSelected( paper ) ;
			
		}
	}

	// 기호들의 stickSign을 정리한다
	for( Long i = 0 ; i < this->paper->GetLength() ; i++){
		sticker.CheckStickingSign( this->paper, i ) ;
	}
}

/*
	함수이름 : DisplayDotSticker
	설    명 : 기호를 선택하여 이동 중, 붙여지는 위치로 이동시에 붙여일 곳을 점선으로 표시해준다
	입    력 : CPaintDC *dc
	출    력 : void
	만 든 이 : i5
*/
void RushNChart::DisplayDotSticker( CDC *memDc ) 
{

	
		CPen pen;
		CPen *oldPen;

		pen.CreatePen( PS_DOT,1,RGB(0,0,0) );
		oldPen = memDc->SelectObject( &pen );


		Symbol *temp;

		Long startPointX;
		Long startPointY;
		Long endPointX;
		Long endPointY;
		Long middlePointX;
		Long middlePointY;
		Long expressionStartPointX;
		Long expressionStartPointY;
		Long expressionEndPointX;
		Long expressionEndPointY;
		//Long columnCount;

		wstring expression;
		temp = this->dotSticker ;
	
		startPointX = temp->GetStartPointX();
		startPointY = temp->GetStartPointY();
		endPointX = temp->GetEndPointX();
		endPointY = temp->GetEndPointY();

		expressionStartPointX = temp->GetExpressionStartPointX();
		expressionStartPointY = temp->GetExpressionStartPointY();
		expressionEndPointX = temp->GetExpressionEndPointX( );
		expressionEndPointY = temp->GetExpressionEndPointY( );

		expression = temp->GetExpression();
	
		if( dynamic_cast< Sequence * > ( temp ) )	{
		
			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY);
			memDc->LineTo( startPointX, startPointY );

		}
		else if( dynamic_cast< BeforeRepeat * > ( temp ) )	{
			BeforeRepeat *symbol = static_cast< BeforeRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX();
			middlePointY = symbol->GetMiddlePointY();

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, middlePointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( middlePointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );

		}
		else if( dynamic_cast< AfterRepeat * > ( temp ) )	{
			AfterRepeat *symbol = static_cast< AfterRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX();
			middlePointY = symbol->GetMiddlePointY();

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, middlePointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );

		}
		else if( dynamic_cast< Selection * > ( temp ) )	{
			Selection *symbol = static_cast< Selection * > ( temp );

			middlePointX = symbol->GetMiddlePointX();
			middlePointY = symbol->GetMiddlePointY();

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, startPointY );

		}

		else if( dynamic_cast< SwitchCase * > ( temp ) )	
		{
			SwitchCase *symbol = static_cast< SwitchCase * > ( temp );
			Selection *selection = symbol->GetSelection ( );

			memDc->MoveTo ( selection->GetStartPointX(), selection->GetStartPointY() );
			memDc->LineTo ( selection->GetEndPointX(), selection->GetStartPointY() );
			memDc->LineTo ( selection->GetEndPointX(), selection->GetEndPointY() );
			memDc->LineTo ( selection->GetStartPointX(), selection->GetEndPointY() );
			memDc->LineTo ( selection->GetStartPointX(), selection->GetStartPointY() );
			memDc->LineTo ( selection->GetMiddlePointX(), selection->GetMiddlePointY() );
			memDc->LineTo ( selection->GetEndPointX(), selection->GetStartPointY() );

			for ( Long j = 0; j < symbol->GetLength(); j++ )	{
				Sequence *tempCase = symbol->GetCases ( j );

				memDc->MoveTo ( tempCase->GetStartPointX(), tempCase->GetStartPointY() );
				memDc->LineTo ( tempCase->GetEndPointX(), tempCase->GetStartPointY() );
				memDc->LineTo ( tempCase->GetEndPointX(), tempCase->GetEndPointY() );
				memDc->LineTo ( tempCase->GetStartPointX(), tempCase->GetEndPointY() );
				memDc->LineTo ( tempCase->GetStartPointX(), tempCase->GetStartPointY() );

				
			}

			
		}

		memDc->SelectObject( oldPen );;
		pen.DeleteObject( );
}

/*
	함수이름 : DisplayDotStickers
	설    명 : 기호를 다중 선택하여 이동 중, 붙여지는 위치로 이동시에 붙여일 곳을 점선으로 표시해준다
	입    력 : CPaintDC *dc
	출    력 : void
	만 든 이 : i5
*/
void	RushNChart::DisplayDotStickers( CDC *memDc ) 
{


		CPen pen;
		CPen *oldPen;

		pen.CreatePen( PS_DOT,1,RGB(0,0,0) );
		oldPen = memDc->SelectObject( &pen );


		Symbol *temp;

		Long startPointX;
		Long startPointY;
		Long endPointX;
		Long endPointY;
		Long middlePointX;
		Long middlePointY;
		Long expressionStartPointX;
		Long expressionStartPointY;
		Long expressionEndPointX;
		Long expressionEndPointY;
		//Long columnCount;

		wstring expression;



		
		for( Long i = 0; i < this->selectedSymbolLength; i++ )
		{
			temp = this->dotStickers[i] ;
	
			startPointX = temp->GetStartPointX();
			startPointY = temp->GetStartPointY();
			endPointX = temp->GetEndPointX();
			endPointY = temp->GetEndPointY();

			expressionStartPointX = temp->GetExpressionStartPointX();
			expressionStartPointY = temp->GetExpressionStartPointY();
			expressionEndPointX = temp->GetExpressionEndPointX( );
			expressionEndPointY = temp->GetExpressionEndPointY( );

			expression = temp->GetExpression();
	
			if( dynamic_cast< Sequence * > ( temp ) )	{
		
				memDc->MoveTo( startPointX, startPointY );
				memDc->LineTo( endPointX, startPointY );
				memDc->LineTo( endPointX, endPointY );
				memDc->LineTo( startPointX, endPointY);
				memDc->LineTo( startPointX, startPointY );
		
			}
			else if( dynamic_cast< BeforeRepeat * > ( temp ) )	{
				BeforeRepeat *symbol = static_cast< BeforeRepeat * > ( temp );

				middlePointX = symbol->GetMiddlePointX();
				middlePointY = symbol->GetMiddlePointY();

				memDc->MoveTo( startPointX, startPointY );
				memDc->LineTo( endPointX, startPointY );
				memDc->LineTo( endPointX, middlePointY );
				memDc->LineTo( middlePointX, middlePointY );
				memDc->LineTo( middlePointX, endPointY );
				memDc->LineTo( startPointX, endPointY );
				memDc->LineTo( startPointX, startPointY );

				
			}
			else if( dynamic_cast< AfterRepeat * > ( temp ) )	{
				AfterRepeat *symbol = static_cast< AfterRepeat * > ( temp );

				middlePointX = symbol->GetMiddlePointX();
				middlePointY = symbol->GetMiddlePointY();

				memDc->MoveTo( startPointX, startPointY );
				memDc->LineTo( middlePointX, startPointY );
				memDc->LineTo( middlePointX, middlePointY );
				memDc->LineTo( endPointX, middlePointY );
				memDc->LineTo( endPointX, endPointY );
				memDc->LineTo( startPointX, endPointY );
				memDc->LineTo( startPointX, startPointY );

			}
			else if( dynamic_cast< Selection * > ( temp ) )	{
				Selection *symbol = static_cast< Selection * > ( temp );

				middlePointX = symbol->GetMiddlePointX();
				middlePointY = symbol->GetMiddlePointY();

				memDc->MoveTo( startPointX, startPointY );
				memDc->LineTo( endPointX, startPointY );
				memDc->LineTo( endPointX, endPointY );
				memDc->LineTo( startPointX, endPointY );
				memDc->LineTo( startPointX, startPointY );
				memDc->LineTo( middlePointX, middlePointY );
				memDc->LineTo( endPointX, startPointY );

				
			}

			else if( dynamic_cast< SwitchCase * > ( temp ) )	
			{
				SwitchCase *symbol = static_cast< SwitchCase * > ( temp );
				Selection *selection = symbol->GetSelection ( );

				memDc->MoveTo ( selection->GetStartPointX(), selection->GetStartPointY() );
				memDc->LineTo ( selection->GetEndPointX(), selection->GetStartPointY() );
				memDc->LineTo ( selection->GetEndPointX(), selection->GetEndPointY() );
				memDc->LineTo ( selection->GetStartPointX(), selection->GetEndPointY() );
				memDc->LineTo ( selection->GetStartPointX(), selection->GetStartPointY() );
				memDc->LineTo ( selection->GetMiddlePointX(), selection->GetMiddlePointY() );
				memDc->LineTo ( selection->GetEndPointX(), selection->GetStartPointY() );

				for ( Long j = 0; j < symbol->GetLength(); j++ )	{
					Sequence *tempCase = symbol->GetCases ( j );

					memDc->MoveTo ( tempCase->GetStartPointX(), tempCase->GetStartPointY() );
					memDc->LineTo ( tempCase->GetEndPointX(), tempCase->GetStartPointY() );
					memDc->LineTo ( tempCase->GetEndPointX(), tempCase->GetEndPointY() );
					memDc->LineTo ( tempCase->GetStartPointX(), tempCase->GetEndPointY() );
					memDc->LineTo ( tempCase->GetStartPointX(), tempCase->GetStartPointY() );

				}

			}
		}

		memDc->SelectObject( oldPen );;
		pen.DeleteObject( );
}


/*
	함수이름 : StickerPreview
	설    명 : 기호를 선택하여 이동 중, 붙여지는 위치로 이동시에 붙여질 기호들을 점선으로 표시하기 위해서, 필요한 데이터(기호)를 만든다
	입    력 : void
	출    력 : void
	만 든 이 : i5
*/
void	RushNChart::StickerPreview() {
	Long index = (this->select->GetSelectPaper()->GetAt(0)).GetSeletedSymbolIndex() ;
	if( index > -1 )
	{
		Sticker sticker ;

		
		if( this->dotSticker != 0 )
		{
				delete this->dotSticker ;
				this->dotSticker = 0 ;
		}
		// StickingSign
		Long i = 0 ;
		while( i < this->paper->GetLength()  )
		{
			sticker.CheckStickingSign( this->paper , i ) ;
			i ++ ;
		}//*/

		//sticker.paperSymbolsSort( this->paper ) ;
		sticker.CheckStickingFieldForMove( this->paper, this->select, index, this->moveX, this->moveY ) ;
		
		if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// 붙이는 상황이면
		{
			sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), index ) ;
			string type = this->paper->CheckType( index ) ;
			this->dotSticker = sticker.StickToForPre( this->paper, sticker.GetStartX(), sticker.GetStartY(), sticker.GetEndX(), sticker.GetEndY(), paper->GetAt(index)->GetExpression(), type, index ) ;
		}
	}
}

/*
	함수이름 : StickersPreview
	설    명 : 기호를 다중 선택하여 이동 중, 붙여지는 위치로 이동시에 붙여질 기호들을 점선으로 표시하기 위해서, 필요한 데이터(기호)를 만든다
	입    력 : void
	출    력 : void
	만 든 이 : i5
*/
void	RushNChart::StickersPreview(){

	Sticker sticker ;
	// StickingSign
	Long i = 0 ;
	while( i < this->paper->GetLength()  )
	{
		sticker.CheckStickingSign( this->paper , i ) ;
		i ++ ;
	}//*/

	Long selectPaperLength = this->select->GetSelectPaper()->GetLength() ;
	this->selectedSymbolLength = selectPaperLength ;

	if( this->dotStickers != 0 ) //this->dotStickers 초기화
	{
		Long j = 0 ;
		while( j < this->selectedSymbolLength ) 
		{
			if( this->dotStickers != 0 )
			{
				delete this->dotStickers[ j ] ;
			}
			j++ ;
		}
		delete[] this->dotStickers ;
		this->dotStickers = 0 ;
	}
	this->dotStickers = new Symbol*[ selectPaperLength ] ;
	for( Long i = 0 ; i < this->selectedSymbolLength ; i++){
		this->dotStickers[i] = 0 ;
	}
					
	sticker.SearchTopBottom( this->paper, this->select ) ;
	sticker.CheckStickingFieldForMove( this->paper, this->select, sticker.GetTopIndex(), this->moveX, this->moveY ) ;

	if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// 붙이는 상황이면
	{
		sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), sticker.GetTopIndex() ) ;
		sticker.GetGap( this->paper, sticker.GetTopIndex()  ) ;
		sticker.StickBundleToForPre( paper, select, sticker.GetStartGapX(), sticker.GetStartGapY(), this->dotStickers, this->selectedSymbolLength  ) ;

	}
	else 
	{
		sticker.CheckStickingFieldForMove( this->paper, this->select, sticker.GetBottonIndex(), this->moveX, this->moveY ) ;
		if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// 붙이는 상황이면
			{
				sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), sticker.GetBottonIndex() ) ;
				sticker.GetGap( this->paper, sticker.GetBottonIndex()  ) ;
				sticker.StickBundleToForPre( paper, select, sticker.GetStartGapX(), sticker.GetStartGapY(), this->dotStickers, this->selectedSymbolLength  ) ;
			}


	}
	if( this->dotStickers[0] == 0 ) //붙이는 상황이 아니면
	{
		if( this->dotStickers != 0 ) //this->dotStickers 초기화
		{
			Long j = 0 ;
			while( j < this->selectedSymbolLength ) 
			{
				if( this->dotStickers != 0 )
				{
					delete this->dotStickers[ j ] ;
				}
				j++ ;
			}
			delete[] this->dotStickers ;
			this->dotStickers = 0 ;
		}
	}// dotStickers 배열에 값들이 없으면, 할당해제해서 OnPaint에서 DisplayDotStickers를 부르지 않도록 한다
}

/*
	함수이름 : OnClose
	설    명 : 닫기버튼눌렀을때
	입    력 : 없음
	출    력 : 없음
	만 든 이 : 수정 - 채형석
*/
void RushNChart::OnClose()	{
	wchar_t	*save;

	if ( this->bSaveFlag == FALSE ) {

		Long ret = ::MessageBoxA(NULL, "저장하시겠습니까?", "확인", MB_YESNOCANCEL|MB_ICONINFORMATION) ;

		if( ret == IDYES )	{
		
			if ( this->bSaveFlag != TRUE ) {
				
				wchar_t *szFilter = L"DAT (*.dat)|*.dat||";
				CFileDialog dlg (FALSE, L"DAT", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  szFilter);
				CString	filePath;

				if (dlg.DoModal () == IDOK) {
				
					filePath = dlg.GetFileName();
					save = filePath.GetBuffer( filePath.GetLength() ); 
					this->paper->Save( save );
				}
			}
			else {
				save = ( wchar_t * )this->saveName.GetBuffer();
				this->paper->Save( save );
			}

			if( this->paper != 0 )	{
				delete this->paper;
			}

			if( this->select != 0 )	{
				delete this->select;
			}

			if( this->copySymbol != 0 )	{
				delete this->copySymbol;
			}

			if( this->paperList != 0 )	{
				delete this->paperList;
			}

			if( this->pen != 0 )	{
				delete this->pen;
			}

			CFrameWnd::OnClose();
		}
		else if ( ret == IDNO ) {
			if( this->paper != 0 )	{
				delete this->paper;
			}

			if( this->select != 0 )	{
				delete this->select;
			}

			if( this->copySymbol != 0 )	{
				delete this->copySymbol;
			}

			if( this->paperList != 0 )	{
				delete this->paperList;
			}

			if( this->pen != 0 )	{
				delete this->pen;
			}

			CFrameWnd::OnClose();
		}
	}
	else {
		save = ( wchar_t * )this->saveName.GetBuffer();
		this->paper->Save( save );

		if( this->paper != 0 )	{
			delete this->paper;
		}

		if( this->select != 0 )	{
			delete this->select;
		}

		if( this->copySymbol != 0 )	{
			delete this->copySymbol;
		}

		if( this->paperList != 0 )	{
			delete this->paperList;
		}

		if( this->pen != 0 )	{
			delete this->pen;
		}

		CFrameWnd::OnClose();
	}
}

/*
	함수이름 : OnNewPaperMenuClicked
	설    명 : 새 종이 메뉴버튼을 눌렀을때
	입    력 : 없음
	출    력 : 없음
	만 든 이 : 수정 - 채형석
*/
void	RushNChart::OnNewPaperMenuClicked( ) {

	if ( this->bEmployFlag == TRUE ) {
		
		Long ret = ::MessageBoxA(NULL, " 차트를 저장하시겠습니까?", "확인", MB_YESNOCANCEL|MB_ICONINFORMATION) ;

		if( ret == IDYES )	{	
			wchar_t *szFilter = L"DAT (*.dat)|*.dat||";
			CFileDialog dlg (FALSE, L"DAT", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  szFilter);
			CString	filePath;

			if (dlg.DoModal () == IDOK) {
				wchar_t	*save;
				filePath = dlg.GetPathName();
				save = filePath.GetBuffer( filePath.GetLength() ); 
				this->paper->Save( save );
				this->saveName = filePath;
			}
		}
		else if ( ret == IDNO ) {

			if ( this->paper != NULL ) {
				delete this->paper;
			}
			this->paper = new Paper;
	
			// 이전까지 저장된 Undo 데이터들을 모두 초기화 한다.
			paperList->Initialize( );
			//빈 화면을 저장한다.
			paperList->CaptureLastPaper( paper );


			Invalidate(FALSE) ;
	
			this->bSelectedMenu = FALSE ;			//메뉴클릭시
			this->bDragFlag = FALSE ;				//마우스 클릭 후 이동시
			this->bCompleteStructure = FALSE ;		//구조를 그리기 완성했을때
			this->bSelectedSymbolFlag = FALSE ;		//기호를 클릭했을떄
			this->bSelectedDBLClickedFlag = FALSE;	//기호를 더블클릭했을때
			this->bMovedSymbolFlag = FALSE ;			//기호를 이동했을떄
			this->TransNumber = 0;					// 기호의 크기를 변경하고자 할때
			this->saveName = _T("");					// 저장할때 사용 하는 이름 -채형석-
			this->loadName = _T("");					// 불러오기 할때 사용 되는 이름 - 채형석
			this->bSaveFlag = FALSE;					//SAVE 되어있는지 여부를 파악소 - 채형석
			this->bEmployFlag = FALSE;			// 저장 여부를 파악한다.
		}
	}
	else {

		if ( this->paper != NULL ) {
			delete this->paper;
		}
		this->paper = new Paper;
	
		// 이전까지 저장된 Undo 데이터들을 모두 초기화 한다.
		paperList->Initialize( );
		//빈 화면을 저장한다.
		paperList->CaptureLastPaper( paper );


		Invalidate(FALSE) ;
	
		this->bSelectedMenu = FALSE ;			//메뉴클릭시
		this->bDragFlag = FALSE ;				//마우스 클릭 후 이동시
		this->bCompleteStructure = FALSE ;		//구조를 그리기 완성했을때
		this->bSelectedSymbolFlag = FALSE ;		//기호를 클릭했을떄
		this->bSelectedDBLClickedFlag = FALSE;	//기호를 더블클릭했을때
		this->bMovedSymbolFlag = FALSE ;			//기호를 이동했을떄
		this->TransNumber = 0;					// 기호의 크기를 변경하고자 할때
		this->saveName = _T("");					// 저장할때 사용 하는 이름 -채형석-
		this->loadName = _T("");					// 불러오기 할때 사용 되는 이름 - 채형석
		this->bSaveFlag = FALSE;					//SAVE 되어있는지 여부를 파악소 - 채형석
		this->bEmployFlag = FALSE;			// 저장 여부를 파악한다.
	}
}

/*
	함수이름 : OnSaveMenuClicked
	설    명 : 저장하기 버튼을 눌렀을 때
	입    력 : 없음
	출    력 : 없음
	만 든 이 : 수정 - 채형석 ( i5 )
*/
void	RushNChart::OnSaveMenuClicked ( ) 
{
	wchar_t *szFilter = L"DAT (*.dat)|*.dat||";
	CFileDialog dlg (FALSE, L"DAT", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  szFilter);
	CString filePath;
	wchar_t	*save;

	if ( this->bSaveFlag != TRUE ) {
		if (dlg.DoModal () == IDOK) {
			
			filePath = dlg.GetPathName();
			save = filePath.GetBuffer( filePath.GetLength() ); 
			this->paper->Save( save );
			this->bSaveFlag = TRUE;
			this->saveName = filePath;
			this->bEmployFlag = FALSE;
		}
	}
	else {

		save = ( wchar_t * )this->saveName.GetBuffer();
		this->paper->Save( save );
		this->bEmployFlag = FALSE;
	}
}

/*
	함수이름 : OnReNameSaveMenuClicked
	설    명 : 다른 이름으로 저장하기 메뉴 버튼을 눌렀을 때
	입    력 : 없음
	출    력 : 없음
	만 든 이 : 수정 - 채형석 ( i 5 )
*/

void	RushNChart::OnReNameSaveMenuClicked ( ) {

	wchar_t *szFilter = L"DAT (*.dat)|*.dat||";
	CFileDialog dlg (FALSE, L"DAT", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  szFilter);
	CString filePath;
	wchar_t	*save;

	if (dlg.DoModal () == IDOK) {
		filePath = dlg.GetPathName();
		save = filePath.GetBuffer( filePath.GetLength() ); 
		this->paper->Save( save );
		this->bSaveFlag = TRUE;
		this->saveName = filePath;
		this->bEmployFlag = FALSE;
	}
}

/*
	함수이름 : OnLoadMenuClicked
	설    명 : 불러오기 메뉴 버튼을 눌렀을 때
	입    력 : 없음
	출    력 : 없음
	만 든 이 : 채형석 ( i5 )
*/
void	RushNChart::OnLoadMenuClicked( ) {
	wchar_t	*save;

	if ( this->paper != NULL ) {

		if ( this->bEmployFlag == TRUE ) {

			Long ret = ::MessageBoxA(NULL, "변경된 내용을 저장하시겠습니까?", "확인", MB_YESNOCANCEL|MB_ICONINFORMATION) ;
		
			if ( this->bSaveFlag != TRUE ) {
			
				if( ret == IDYES )	{	
					wchar_t *szFilter = L"DAT (*.dat)|*.dat||";
					CFileDialog dlg (FALSE, L"DAT", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  szFilter);
					CString filePath;
					wchar_t	*save;

					if (dlg.DoModal () == IDOK) {
						filePath = dlg.GetPathName();
						save = filePath.GetBuffer( filePath.GetLength() ); 
						this->paper->Save( save );
						this->saveName = filePath;
					}
				}
			}
			else {
				save = ( wchar_t *)this->saveName.GetBuffer();
				this->paper->Save( save );
			}
		}

		if ( this->paper != NULL ) {
			delete this->paper;
		}
		this->paper = new Paper;

		Invalidate(FALSE) ;
	
		this->bSelectedMenu = FALSE ;			//메뉴클릭시
		this->bDragFlag = FALSE ;				//마우스 클릭 후 이동시
		this->bCompleteStructure = FALSE ;		//구조를 그리기 완성했을때
		this->bSelectedSymbolFlag = FALSE ;		//기호를 클릭했을떄
		this->bSelectedDBLClickedFlag = FALSE;	//기호를 더블클릭했을때
		this->bMovedSymbolFlag = FALSE ;			//기호를 이동했을떄
		this->TransNumber = 0;					// 기호의 크기를 변경하고자 할때
		this->saveName = _T("");					// 다른이름으로 저장하기 기능으로 인한 추가 -채형석-
		this->loadName = _T("");					// 불러오기 할때 사용 되는 이름 - 채형석
		this->bSaveFlag = FALSE;					//SAVE 할 내용이 있는지 여부를 확인할 떄 - 채형석
		this->bEmployFlag = FALSE;				// 저장할 내용이 있는지 여부를 파악서
	}

	wchar_t *szFilter = L"DAT (*.dat)|*.dat||";
	CFileDialog dlg (TRUE, L"DAT", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  szFilter);
	
	if (dlg.DoModal () == IDOK) {	
		CString filePath = dlg.GetPathName();
		wchar_t *load;
		load = filePath.GetBuffer( filePath.GetLength() );
		this->paper->Load( load );
		paperList->Initialize( );
		paperList->CaptureLastPaper( paper );
		this->saveName = filePath;
		this->bSaveFlag = TRUE;
		Invalidate(FALSE) ;
	}
}
/*
	함수이름 : OnPrintMenuClicked
	설    명 : 인쇄하기 메뉴 버튼을 눌렀을 때
	입    력 : 없음
	출    력 : 없음
	만 든 이 : i5
*/
void	RushNChart::OnPrintMenuClicked(  ) {
	
	CPrintDialog dlg(TRUE);

	CDC PrintDC; // printDC로 쓸 CDC를 만든다

	int printHeight = 2000;

	if (dlg.DoModal() == IDOK &&   PrintDC.Attach(dlg.CreatePrinterDC())     )  // CDC를 print dc로 만든다
	{

		DOCINFO doc;

		memset(&doc, 0x00, sizeof(DOCINFO));
		doc.cbSize = sizeof(DOCINFO);
		doc.lpszDocName = L"RushNChart";

		PrintDC.StartDoc(&doc); // 프린트 시작
		PrintDC.StartPage();

		CDC memDC; 
		memDC.CreateCompatibleDC(&PrintDC); // print dc를 메모리dc로 만든다

		CBitmap bitMap;

		bitMap.CreateCompatibleBitmap(&PrintDC, 14040, 9924 ); // 비트맵을 초기화 한다. 너비 높이 지정 // 픽셀단위

		memDC.SelectObject(&bitMap); // memDC가 그리는 도화지를 bitMap으로 정한다?????


		// 뽑는 용지가 A4( 210mm * 297mm ) -> inch로 변환시 A4( 8.27inch * 11.7inch ) -> 대략 A4( 8 inch * 12 inch ) 
		// A4 가로로 놓고 인쇄를 한다고 가정할 때 가로 세로 인치는 아래와 같다
		Long paperWidthInch = 12 ;
		Long paperHeightInch = 8 ;

		// DucuPrint p215b 모델의 프린터 해상도가 가로 1200dpi, 세로 1200dip 일 때,
		Long printerWidthDpi = 1200 ;
		Long printerHeightDpi = 1200 ;
		
		// 위 프린터 해상도를 기준으로 A4의 픽셀 크기는 대략 아래와 같다
		Long paperWidth = paperWidthInch * printerWidthDpi ;
		Long paperHeight = paperHeightInch * printerHeightDpi ;

		memDC.PatBlt(0,0, paperWidth, paperHeight, WHITENESS ); 

		this->PaintSymbolsForPrint(&memDC); // memDC에 현재 힙의 자료를 그린다
		this->PaintChartForPrint(&memDC) ;
		//PrintDC.StretchBlt(0, 0, 14040, 9924,&memDC, 0, 0, 14040, 9924 , SRCCOPY); // memDC 에 그린 비트맵을 print dc에 확대해서 그려넣는다
		PrintDC.BitBlt( 0, 0, paperWidth, paperHeight, &memDC ,0  ,0 ,SRCCOPY ) ;

		PrintDC.EndPage();

		PrintDC.EndDoc();

		memDC.DeleteDC();
		bitMap.DeleteObject();
		PrintDC.DeleteDC();

	}
}


/*
	함수이름 : PaintSymbolsForPrint
	설    명 : 인쇄하기 메뉴 버튼을 눌렀을 때
	입    력 : CDC *memDc ( 윈도우창에 그릴 때 쓰는 dc ) 
	출    력 : 없음
	만 든 이 : i5
*/
void RushNChart::PaintSymbolsForPrint( CDC *memDc )	{
	Symbol *temp;

	Long startPointX;
	Long startPointY;
	Long endPointX;
	Long endPointY;
	Long middlePointX;
	Long middlePointY;
	Long expressionStartPointX;
	Long expressionStartPointY;
	Long expressionEndPointX;
	Long expressionEndPointY;
	//Long columnCount;

	wstring expression;

	for( Long i = 0; i < this->paper->GetLength(); i++ )
	{
		temp = this->paper->GetAt( i );
	
		startPointX = temp->GetStartPointX() * ZOOM ;
		startPointY = temp->GetStartPointY() * ZOOM  ;
		endPointX = temp->GetEndPointX() * ZOOM ;
		endPointY = temp->GetEndPointY() * ZOOM ;

		expressionStartPointX = temp->GetExpressionStartPointX() * ZOOM ;
		expressionStartPointY = temp->GetExpressionStartPointY() * ZOOM ;
		expressionEndPointX = temp->GetExpressionEndPointX( ) * ZOOM ; //* ZOOM ;
		expressionEndPointY = temp->GetExpressionEndPointY( ) * ZOOM ;

		expression = temp->GetExpression() ;
	
		if( dynamic_cast< Sequence * > ( temp ) )	{
		
			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY);
			memDc->LineTo( startPointX, startPointY );
		
			CRect expressionRect( temp->GetExpressionStartPointX() * ZOOM, temp->GetExpressionStartPointY() * ZOOM, 
				temp->GetExpressionEndPointX( ) * ZOOM, temp->GetExpressionEndPointY( ) * ZOOM );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( temp->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
		}
		else if( dynamic_cast< BeforeRepeat * > ( temp ) )	{
			BeforeRepeat *symbol = static_cast< BeforeRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX() * ZOOM ;
			middlePointY = symbol->GetMiddlePointY() * ZOOM ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, middlePointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( middlePointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );

			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( temp->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );

		}
		else if( dynamic_cast< AfterRepeat * > ( temp ) )	{
			AfterRepeat *symbol = static_cast< AfterRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX() * ZOOM ;
			middlePointY = symbol->GetMiddlePointY() * ZOOM ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, middlePointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );

			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( temp->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
		}
		else if( dynamic_cast< Selection * > ( temp ) )	
		{
			Selection *symbol = static_cast< Selection * > ( temp );

			middlePointX = symbol->GetMiddlePointX() * ZOOM ;
			middlePointY = symbol->GetMiddlePointY() * ZOOM ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, startPointY );
			// 식을 위한 CRect, DrawText
			CRect expressionRect(expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( temp->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );

			// TRUE 조건식을 위한 CRect, DrawText
			string conditionTrue = "TRUE" ;
			expressionStartPointX = startPointX + (5 * ZOOM ) ;
			expressionStartPointY = endPointY - (30 * ZOOM ) ;
			expressionEndPointX = startPointX + (70 * ZOOM ) ;
			expressionEndPointY = endPointY - (5  * ZOOM ) ;

			CRect conditionTrueRect(  expressionStartPointX,  expressionStartPointY,  expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_VCENTER|DT_SINGLELINE );

			// FALSE 조건식을 위한 CRect, DrawText
			string conditionFalse = "FALSE" ;
			expressionStartPointX = endPointX - (70 * ZOOM ) ;
			expressionStartPointY = endPointY - (30 * ZOOM ) ;
			expressionEndPointX = endPointX - (5 * ZOOM ) ;
			expressionEndPointY = endPointY - (5 * ZOOM ) ;

			CRect conditionFalseRect(  expressionStartPointX,  expressionStartPointY,  expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( conditionFalse.c_str(), conditionFalseRect, DT_VCENTER|DT_SINGLELINE );

		}

		else if( dynamic_cast< SwitchCase * > ( temp ) )	
		{
			SwitchCase *symbol = static_cast< SwitchCase * > ( temp );
			Selection *selection = symbol->GetSelection ( );

			memDc->MoveTo ( selection->GetStartPointX() * ZOOM , selection->GetStartPointY() * ZOOM  );
			memDc->LineTo ( selection->GetEndPointX() * ZOOM , selection->GetStartPointY() * ZOOM  );
			memDc->LineTo ( selection->GetEndPointX() * ZOOM , selection->GetEndPointY() * ZOOM  );
			memDc->LineTo ( selection->GetStartPointX() * ZOOM , selection->GetEndPointY() * ZOOM  );
			memDc->LineTo ( selection->GetStartPointX() * ZOOM , selection->GetStartPointY() * ZOOM  );
			memDc->LineTo ( selection->GetMiddlePointX() * ZOOM , selection->GetMiddlePointY() * ZOOM  );
			memDc->LineTo ( selection->GetEndPointX() * ZOOM , selection->GetStartPointY() * ZOOM  );

			// TRUE 조건식을 위한 CRect, DrawText
			string conditionTrue = "TRUE" ;
			expressionStartPointX = selection->GetStartPointX() * ZOOM + (5 * ZOOM ) ;
			expressionStartPointY = selection->GetMiddlePointY() * ZOOM - (30 * ZOOM ) ;
			expressionEndPointX = selection->GetStartPointX() * ZOOM + (70 * ZOOM ) ;
			expressionEndPointY = selection->GetMiddlePointY() * ZOOM - (5  * ZOOM ) ;

			CRect conditionTrueRect(  expressionStartPointX,  expressionStartPointY,  expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_VCENTER|DT_SINGLELINE );

			// FALSE 조건식을 위한 CRect, DrawText
			string conditionFalse = "FALSE" ;
			expressionStartPointX = selection->GetEndPointX() * ZOOM - (70 * ZOOM ) ;
			expressionStartPointY = selection->GetMiddlePointY() * ZOOM - (30 * ZOOM ) ;
			expressionEndPointX = selection->GetEndPointX() * ZOOM - (5 * ZOOM ) ;
			expressionEndPointY = selection->GetMiddlePointY() * ZOOM - (5 * ZOOM ) ;

			CRect conditionFalseRect(  expressionStartPointX,  expressionStartPointY,  expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( conditionFalse.c_str(), conditionFalseRect, DT_VCENTER|DT_SINGLELINE );

			for ( Long j = 0; j < symbol->GetLength(); j++ )	{
				Sequence *tempCase = symbol->GetCases ( j );

				memDc->MoveTo ( tempCase->GetStartPointX() * ZOOM , tempCase->GetStartPointY() * ZOOM  );
				memDc->LineTo ( tempCase->GetEndPointX() * ZOOM , tempCase->GetStartPointY() * ZOOM  );
				memDc->LineTo ( tempCase->GetEndPointX() * ZOOM , tempCase->GetEndPointY() * ZOOM  );
				memDc->LineTo ( tempCase->GetStartPointX() * ZOOM , tempCase->GetEndPointY() * ZOOM  );
				memDc->LineTo ( tempCase->GetStartPointX() * ZOOM , tempCase->GetStartPointY() * ZOOM  );

				CRect expressionRect ( tempCase->GetExpressionStartPointX() * ZOOM , tempCase->GetExpressionStartPointY() * ZOOM ,
					tempCase->GetExpressionEndPointX() * ZOOM , tempCase->GetExpressionEndPointY() * ZOOM  );
				memDc->SetBkMode(TRANSPARENT);
				memDc->DrawText ( tempCase->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE|DT_CENTER );

			}

			CRect expressionRect ( selection->GetExpressionStartPointX() * ZOOM , selection->GetExpressionStartPointY() * ZOOM , 
									selection->GetExpressionEndPointX() * ZOOM , selection->GetExpressionEndPointY() * ZOOM  );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText ( selection->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
		}
		else if( dynamic_cast< Arrow * > ( temp ) )	{
		
			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->MoveTo( startPointX-10*ZOOM, endPointY-10*ZOOM );
			memDc->LineTo( startPointX, endPointY);
			memDc->LineTo( startPointX+10*ZOOM, endPointY-10*ZOOM );
		
		}
		
	}
}

/*
	함수이름 : PaintChartForPrint
	설    명 : 인쇄하기 메뉴 버튼을 눌렀을 때
	입    력 : CDC *memDc ( 윈도우창에 그릴 때 쓰는 dc ) 
	출    력 : 없음
	만 든 이 : i5
*/
void RushNChart::PaintChartForPrint( CDC *memDc ) {
	Symbol *temp;

	Long startPointX;
	Long startPointY;
	Long endPointX;
	Long endPointY;
	Long middlePointX;
	Long middlePointY;
	Long expressionStartPointX;
	Long expressionStartPointY;
	Long expressionEndPointX;
	Long expressionEndPointY;
	//Long columnCount;

	wstring expression;

	CPen *oldPen ;
	CBrush *oldBrush ;
	CPen pen ;
	CBrush chartBrush ;
	CBrush sequenceBrush ;
	CBrush startOrStopBrush ;
	CBrush beforeRepeatBrush ;
	CBrush afterRepeatBrush ;
	CBrush selectionBrush ;
	CBrush switchCaseBrush ;

	pen.CreatePen( PS_INSIDEFRAME,1,RGB(0,0,0) );
	chartBrush.CreateHatchBrush(10,RGB(0,255,255));
	startOrStopBrush.CreateSolidBrush(RGB(255,234,234));
	sequenceBrush.CreateSolidBrush(RGB(255,255,228));
	beforeRepeatBrush.CreateSolidBrush(RGB(224,255,219));
	afterRepeatBrush.CreateSolidBrush(RGB(230,255,255));
	selectionBrush.CreateSolidBrush(RGB(255,235,254));
	switchCaseBrush.CreateSolidBrush(RGB(255,217,236));
	
	oldPen = memDc->SelectObject ( &pen);

	for( Long i = 0; i < this->paper->GetChart()->GetLength(); i++ )
	{
		temp = this->paper->GetChart()->GetAt( i );
	
		startPointX = temp->GetStartPointX() * ZOOM ;
		startPointY = temp->GetStartPointY() * ZOOM ;
		endPointX = temp->GetEndPointX() * ZOOM ;
		endPointY = temp->GetEndPointY() * ZOOM ;

		expressionStartPointX = temp->GetExpressionStartPointX() * ZOOM ;
		expressionStartPointY = temp->GetExpressionStartPointY() * ZOOM ;
		expressionEndPointX = temp->GetExpressionEndPointX( ) * zoom ;//* ZOOM ;
		expressionEndPointY = temp->GetExpressionEndPointY( ) * ZOOM ;

		expression = temp->GetExpression();
	
		if( dynamic_cast< Sequence * > ( temp ) )	{

			if ( expression.compare(L"start")==0 || expression.compare(L"Start")==0 || expression.compare(L"START")==0 ||
				 expression.compare(L"stop")==0 || expression.compare(L"Stop")==0 || expression.compare(L"STOP")==0 ) {
				oldBrush = memDc->SelectObject( &startOrStopBrush ) ;
			}
			else {
				oldBrush = memDc->SelectObject( &sequenceBrush ) ;
			}
			memDc->Rectangle( startPointX, startPointY, endPointX, endPointY) ;

			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			if ( expression.compare(L"start")==0 || expression.compare(L"Start")==0 || expression.compare(L"START")==0 ||
				 expression.compare(L"stop")==0 || expression.compare(L"Stop")==0 || expression.compare(L"STOP")==0 ) {
				memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE|DT_CENTER );
			}
			else{
				memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
			}
		}
		else if( dynamic_cast< BeforeRepeat * > ( temp ) )	{
			BeforeRepeat *symbol = static_cast< BeforeRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX() * ZOOM ;
			middlePointY = symbol->GetMiddlePointY() * ZOOM ;

			oldBrush = memDc->SelectObject( &beforeRepeatBrush ) ;
			POINT before[6] = {{startPointX, startPointY}, {endPointX, startPointY}, {endPointX, middlePointY},
								{middlePointX, middlePointY}, {middlePointX, endPointY}, {startPointX, endPointY}};
			memDc->Polygon(before,6);

			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
		}
		else if( dynamic_cast< AfterRepeat * > ( temp ) )	{
			AfterRepeat *symbol = static_cast< AfterRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX() * ZOOM ;
			middlePointY = symbol->GetMiddlePointY() * ZOOM ;

			oldBrush = memDc->SelectObject( &afterRepeatBrush ) ;
			POINT before[6] = {{startPointX, startPointY}, {middlePointX, startPointY}, {middlePointX, middlePointY},
								{endPointX, middlePointY}, {endPointX, endPointY}, {startPointX, endPointY}};
			memDc->Polygon(before,6);

			CRect expressionRect( expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
		}
		else if( dynamic_cast< Selection * > ( temp ) )	{
			Selection *symbol = static_cast< Selection * > ( temp );

			middlePointX = symbol->GetMiddlePointX() * ZOOM ;
			middlePointY = symbol->GetMiddlePointY() * ZOOM ;

			oldBrush = memDc->SelectObject( &selectionBrush ) ;
			
			memDc->Rectangle(startPointX, startPointY, endPointX, endPointY) ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, startPointY );

			CRect expressionRect(expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( expression.c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );

			// TRUE 조건식을 위한 CRect, DrawText
			string conditionTrue = "TRUE" ;
			expressionStartPointX = startPointX + (5 * ZOOM ) ;
			expressionStartPointY = endPointY - (30 * ZOOM ) ;
			expressionEndPointX = startPointX + (70 * ZOOM ) ;
			expressionEndPointY = endPointY - (5  * ZOOM ) ;

			CRect conditionTrueRect(  expressionStartPointX,  expressionStartPointY,  expressionEndPointX, expressionEndPointY );
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_VCENTER|DT_SINGLELINE );

			// FALSE 조건식을 위한 CRect, DrawText
			string conditionFalse = "FALSE" ;
			expressionStartPointX = endPointX - (70 * ZOOM ) ;
			expressionStartPointY = endPointY - (30 * ZOOM ) ;
			expressionEndPointX = endPointX - (5 * ZOOM ) ;
			expressionEndPointY = endPointY - (5 * ZOOM ) ;

			CRect conditionFalseRect(  expressionStartPointX,  expressionStartPointY,  expressionEndPointX, expressionEndPointY );
			memDc->DrawText( conditionFalse.c_str(), conditionFalseRect, DT_VCENTER|DT_SINGLELINE );

		}

		else if( dynamic_cast< SwitchCase * > ( temp ) )	
		{
			SwitchCase *symbol = static_cast< SwitchCase * > ( temp );
			Selection *selection = symbol->GetSelection ( );

			memDc->MoveTo ( selection->GetStartPointX() * ZOOM , selection->GetStartPointY() * ZOOM  );
			memDc->LineTo ( selection->GetEndPointX() * ZOOM , selection->GetStartPointY() * ZOOM  );
			memDc->LineTo ( selection->GetEndPointX() * ZOOM , selection->GetEndPointY() * ZOOM  );
			memDc->LineTo ( selection->GetStartPointX() * ZOOM , selection->GetEndPointY() * ZOOM  );
			memDc->LineTo ( selection->GetStartPointX() * ZOOM , selection->GetStartPointY() * ZOOM  );
			memDc->LineTo ( selection->GetMiddlePointX() * ZOOM , selection->GetMiddlePointY() * ZOOM  );
			memDc->LineTo ( selection->GetEndPointX() * ZOOM , selection->GetStartPointY() * ZOOM  );

			for ( Long j = 0; j < symbol->GetLength(); j++ )	{
				Sequence *tempCase = symbol->GetCases ( j );

				memDc->MoveTo ( tempCase->GetStartPointX() * ZOOM , tempCase->GetStartPointY() * ZOOM  );
				memDc->LineTo ( tempCase->GetEndPointX() * ZOOM , tempCase->GetStartPointY() * ZOOM  );
				memDc->LineTo ( tempCase->GetEndPointX() * ZOOM , tempCase->GetEndPointY() * ZOOM  );
				memDc->LineTo ( tempCase->GetStartPointX() * ZOOM , tempCase->GetEndPointY() * ZOOM  );
				memDc->LineTo ( tempCase->GetStartPointX() * ZOOM , tempCase->GetStartPointY() * ZOOM  );

				CRect expressionRect ( tempCase->GetExpressionStartPointX() * ZOOM , tempCase->GetExpressionStartPointY() * ZOOM ,
					tempCase->GetExpressionEndPointX() * ZOOM , tempCase->GetExpressionEndPointY() * ZOOM  );

				memDc->DrawText ( tempCase->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );

			}

			CRect expressionRect ( selection->GetExpressionStartPointX() * ZOOM , selection->GetExpressionStartPointY() * ZOOM , selection->GetExpressionEndPointX() * ZOOM , selection->GetExpressionEndPointY() * ZOOM  );

			memDc->DrawText ( selection->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );
		}
		else if( dynamic_cast< Arrow * > ( temp ) )	{
			Arrow *symbol = static_cast< Arrow * > ( temp );

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->MoveTo( startPointX-10, endPointY-10 );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX+10, endPointY-10 );

		}

	}
}


/*
	함수이름 : OnCopyMenuClicked
	설    명 : 마우스 오른쪽 버튼 복사하기 
	입    력 : 없음
	출    력 : 없음
	만 든 이 : i5
*/
void	RushNChart::OnCopyMenuClicked( ) {
	this->copySymbol->CopySymbols( this->select, this->paper );

	// StickingSign
	Sticker sticker ;
	Long i = 0 ;
	while( i < this->paper->GetLength()  )
	{
		sticker.CheckStickingSign( this->paper , i ) ;
		i ++ ;
	}//*/
}


/*
	함수이름 : OnPasteMenuClicked
	설    명 : 마우스 오른쪽 버튼 붙여넣기 
	입    력 : 없음
	출    력 : 없음
	만 든 이 : i5
*/
void	RushNChart::OnPasteMenuClicked( ) {
	this->bSelectedSymbolFlag = TRUE;
	this->copySymbol->PasteSymbols( this->select, this->paper );
	Invalidate(FALSE) ;
	this->bSaveFlag = TRUE;
	this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
	// StickingSign
	Sticker sticker ;
	Long i = 0 ;
	while( i < this->paper->GetLength()  )
	{
		sticker.CheckStickingSign( this->paper , i ) ;
		i ++ ;
	}//*/
}

/*
	함수이름 : OnCutMenuClicked
	설    명 : 마우스 오른쪽 버튼 잘라내기 
	입    력 : 없음
	출    력 : 없음
	만 든 이 : i5
*/
void	RushNChart::OnCutMenuClicked( ) {
	this->copySymbol->CutSymbols( this->select, this->paper );
	Invalidate(FALSE) ;
	this->bSaveFlag = TRUE;
	this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
	// StickingSign
	Sticker sticker ;
	Long i = 0 ;
	while( i < this->paper->GetLength()  )
	{
		sticker.CheckStickingSign( this->paper , i ) ;
		i ++ ;
	}//*/
}


void	RushNChart::OnCloseMenuClicked( ) {
	wchar_t	*save;
	Long ret = ::MessageBoxA(NULL, "저장하시겠습니까?", "확인", MB_YESNOCANCEL|MB_ICONINFORMATION) ;

	if( ret == IDYES )	{
		
		if ( this->bSaveFlag != TRUE ) {
				
			wchar_t *szFilter = L"DAT (*.dat)|*.dat||";
			CFileDialog dlg (FALSE, L"DAT", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  szFilter);
			CString	fileName;

			if (dlg.DoModal () == IDOK) {
				
				fileName = dlg.GetFileName();
				save = fileName.GetBuffer( fileName.GetLength() ); 
				this->paper->Save( save );
			}
		}
		else {
			save = ( wchar_t * )this->saveName.GetBuffer();
			this->paper->Save( save );
		}
		if( this->paper != 0 )	{
			delete this->paper;
		}

		if( this->select != 0 )	{
			delete this->select;
		}

		if( this->copySymbol != 0 )	{
			delete this->copySymbol;
		}

		if( this->paperList != 0 )	{
			delete this->paperList;
		}

		if( this->pen != 0 )	{
			delete this->pen;
		}

		CFrameWnd::OnClose();
	}
	else if ( ret == IDNO ) {
		if( this->paper != 0 )	{
			delete this->paper;
		}

		if( this->select != 0 )	{
			delete this->select;
		}

		if( this->copySymbol != 0 )	{
			delete this->copySymbol;
		}

		if( this->paperList != 0 )	{
			delete this->paperList;
		}

		if( this->pen != 0 )	{
			delete this->pen;
		}

		CFrameWnd::OnClose();
	}
}

void	RushNChart::OnUndoMenuClicked( ) {
	if( this->paperList->GetCurrent( ) - 1 > 0 ){

		Paper *undoPaper = this->paperList->Undo( );
		if( this->pen != NULL ){
			//delete this->pen;
			DestroyCaret( );
		}
		paper = undoPaper;
		select->GetSelectPaper( )->ReleaseAllSymbols( );
		select->ReleaseChart( );
		Invalidate(FALSE );
		this->bSaveFlag = TRUE;
		this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
	}

}


void	RushNChart::OnRedoMenuClicked( ) {
	if( paperList->GetCurrent( ) + 1 <= paperList->GetLength( ) ){
		Paper *redoPaper = this->paperList->Redo(  );
		paper = redoPaper ;
		Invalidate(FALSE );
		this->bSaveFlag = TRUE;
		this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
	}
}


void	RushNChart::OnSelectAllMenuClicked( ) {

	this->select->GetSelectPaper()->StoreSelectedSymbol( this->paper );
	//새로 할당하고
	select->ReleaseChart( );
	select->ReAllocateChart( );
	//선택한다
	if ( this->paper->GetChart()->GetLength () > 0 ) {
		select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
	}
	select->GetSelectChart( )->DrawChartField( );
	this->bSelectedSymbolFlag = TRUE;

	Invalidate( );
}


void	RushNChart::OnPreViewMenuClicked( ) {

	if(this->preViewDlg == NULL){
		this->preViewDlg = new PreViewDlg(this);
		this->preViewDlg->Create(IDD_PREVIEW, this);
		this->preViewDlg->ShowWindow(SW_SHOW);
		
	}
	Invalidate(FALSE);
}


void	RushNChart::OnDeleteMenuClicked( ) {
	if( bSelectedSymbolFlag == TRUE && bWritingFlag == FALSE ){
		if( select->GetSelectPaper( )->GetLength( ) > 0 ){
			paper->DeleteSymbols( this->select->GetSelectPaper( ) );
			paperList->CaptureLastPaper( paper );
			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
		}
		else if( this->paper->GetChart( )->GetLength( ) > 0 && bWritingFlag == FALSE){
			paper->GetChart( )->DeleteAllSymbols(  );
			paperList->CaptureLastPaper( paper );
			select->ReleaseChart( );
			this->bEmployFlag = TRUE;			// 저장 여부를 파악한다.
		}
		
	}
	Invalidate();
}

void RushNChart::OnSize( UINT nType, int cx, int cy )	{
	this->windowWidth = cx;
	this->windowHeight = cy;
}



/*
	함수이름 : MovePreview
	설    명 : 기호(들)를 선택해서 이동시 미리보기를 그리는 함수
	입    력 : CDC *memDc
	출    력 : 없음
	만 든 이 : i5
*/
void	RushNChart::MovePreview( CDC *memDc )	{
	
		CPen pen;
		CPen *oldPen;

		pen.CreatePen( PS_DOT,1,RGB(0,0,0) );
		oldPen = memDc->SelectObject( &pen );

	Symbol *temp;

	Long startPointX;
	Long startPointY;
	Long endPointX;
	Long endPointY;
	Long middlePointX;
	Long middlePointY;
	//Long expressionStartPointX;
	//Long expressionStartPointY;
	//Long expressionEndPointX;
	//Long expressionEndPointY;
	//Long columnCount;

	wstring expression;

	for( Long i = 0; i < this->select->GetSelectPaper()->GetLength() ; i++ )
	{
		temp = this->paper->GetAt( this->select->GetSelectPaper()->GetAt(i).GetSeletedSymbolIndex() );
	
		startPointX = temp->GetStartPointX() + this->moveX ;
		startPointY = temp->GetStartPointY() + this->moveY ;
		endPointX = temp->GetEndPointX() + this->moveX ;
		endPointY = temp->GetEndPointY() + this->moveY ;

		
	
		if( dynamic_cast< Sequence * > ( temp ) )	{
		
			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY);
			memDc->LineTo( startPointX, startPointY );
		
			
		}
		else if( dynamic_cast< BeforeRepeat * > ( temp ) )	{
			BeforeRepeat *symbol = static_cast< BeforeRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX() + this->moveX ;
			middlePointY = symbol->GetMiddlePointY() + this->moveY ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, middlePointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( middlePointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );

			

		}
		else if( dynamic_cast< AfterRepeat * > ( temp ) )	{
			AfterRepeat *symbol = static_cast< AfterRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX() + this->moveX ;
			middlePointY = symbol->GetMiddlePointY() + this->moveY ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, middlePointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );

			
		}
		else if( dynamic_cast< Selection * > ( temp ) )	{
			Selection *symbol = static_cast< Selection * > ( temp );

			middlePointX = symbol->GetMiddlePointX() + this->moveX ;
			middlePointY = symbol->GetMiddlePointY() + this->moveY ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, startPointY );

			

		}

		else if( dynamic_cast< SwitchCase * > ( temp ) )	
		{
			SwitchCase *symbol = static_cast< SwitchCase * > ( temp );
			Selection *selection = symbol->GetSelection ( );

			memDc->MoveTo ( selection->GetStartPointX() + this->moveX , selection->GetStartPointY() + this->moveY  );
			memDc->LineTo ( selection->GetEndPointX() + this->moveX , selection->GetStartPointY() + this->moveY );
			memDc->LineTo ( selection->GetEndPointX() + this->moveX , selection->GetEndPointY() + this->moveY );
			memDc->LineTo ( selection->GetStartPointX() + this->moveX , selection->GetEndPointY() + this->moveY );
			memDc->LineTo ( selection->GetStartPointX() + this->moveX , selection->GetStartPointY() + this->moveY );
			memDc->LineTo ( selection->GetMiddlePointX() + this->moveX , selection->GetMiddlePointY() + this->moveY );
			memDc->LineTo ( selection->GetEndPointX() + this->moveX , selection->GetStartPointY() + this->moveY );

			

			for ( Long j = 0; j < symbol->GetLength(); j++ )	{
				Sequence *tempCase = symbol->GetCases ( j );

				memDc->MoveTo ( tempCase->GetStartPointX() + this->moveX, tempCase->GetStartPointY() + this->moveY );
				memDc->LineTo ( tempCase->GetEndPointX() + this->moveX, tempCase->GetStartPointY() + this->moveY );
				memDc->LineTo ( tempCase->GetEndPointX() + this->moveX, tempCase->GetEndPointY() + this->moveY );
				memDc->LineTo ( tempCase->GetStartPointX() + this->moveX, tempCase->GetEndPointY() + this->moveY );
				memDc->LineTo ( tempCase->GetStartPointX() + this->moveX, tempCase->GetStartPointY() + this->moveY );

				

			}

	
		}
		else if( dynamic_cast< Arrow * > ( temp ) )	{
		
			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->MoveTo( startPointX - 10, endPointY-10 );
			memDc->LineTo( startPointX, endPointY);
			memDc->LineTo( startPointX + 10, endPointY-10 );
		}
	}

	
		memDc->SelectObject( oldPen );;
		pen.DeleteObject( );
}





/*
	함수이름 : MovePreviewForChart
	설    명 : 차트를 선택해서 이동시 미리보기를 그리는 함수
	입    력 : CDC *memDc
	출    력 : 없음
	만 든 이 : i5
*/
void	RushNChart::MovePreviewForChart( CDC *memDc )	{
	
		CPen pen;
		CPen *oldPen;

		pen.CreatePen( PS_DOT,1,RGB(0,0,0) );
		oldPen = memDc->SelectObject( &pen );





	Symbol *temp;

	Long startPointX;
	Long startPointY;
	Long endPointX;
	Long endPointY;
	Long middlePointX;
	Long middlePointY;
	//Long expressionStartPointX;
	//Long expressionStartPointY;
	//Long expressionEndPointX;
	//Long expressionEndPointY;
	//Long columnCount;

	wstring expression;
	
	for( Long i = 0; i < this->paper->GetChart( )->GetLength( )  ; i++ )
	{
		temp = this->paper->GetChart()->GetAt( i ) ;
	
		startPointX = temp->GetStartPointX() + this->moveX ;
		startPointY = temp->GetStartPointY() + this->moveY ;
		endPointX = temp->GetEndPointX() + this->moveX ;
		endPointY = temp->GetEndPointY() + this->moveY ;

		
	
		if( dynamic_cast< Sequence * > ( temp ) )	{
		
			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY);
			memDc->LineTo( startPointX, startPointY );
		
			
		}
		else if( dynamic_cast< BeforeRepeat * > ( temp ) )	{
			BeforeRepeat *symbol = static_cast< BeforeRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX() + this->moveX ;
			middlePointY = symbol->GetMiddlePointY() + this->moveY ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, middlePointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( middlePointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );

			

		}
		else if( dynamic_cast< AfterRepeat * > ( temp ) )	{
			AfterRepeat *symbol = static_cast< AfterRepeat * > ( temp );

			middlePointX = symbol->GetMiddlePointX() + this->moveX ;
			middlePointY = symbol->GetMiddlePointY() + this->moveY ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, middlePointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );

			
		}
		else if( dynamic_cast< Selection * > ( temp ) )	{
			Selection *symbol = static_cast< Selection * > ( temp );

			middlePointX = symbol->GetMiddlePointX() + this->moveX ;
			middlePointY = symbol->GetMiddlePointY() + this->moveY ;

			memDc->MoveTo( startPointX, startPointY );
			memDc->LineTo( endPointX, startPointY );
			memDc->LineTo( endPointX, endPointY );
			memDc->LineTo( startPointX, endPointY );
			memDc->LineTo( startPointX, startPointY );
			memDc->LineTo( middlePointX, middlePointY );
			memDc->LineTo( endPointX, startPointY );

			

		}

		else if( dynamic_cast< SwitchCase * > ( temp ) )	
		{
			SwitchCase *symbol = static_cast< SwitchCase * > ( temp );
			Selection *selection = symbol->GetSelection ( );

			memDc->MoveTo ( selection->GetStartPointX() + this->moveX , selection->GetStartPointY() + this->moveY  );
			memDc->LineTo ( selection->GetEndPointX() + this->moveX , selection->GetStartPointY() + this->moveY );
			memDc->LineTo ( selection->GetEndPointX() + this->moveX , selection->GetEndPointY() + this->moveY );
			memDc->LineTo ( selection->GetStartPointX() + this->moveX , selection->GetEndPointY() + this->moveY );
			memDc->LineTo ( selection->GetStartPointX() + this->moveX , selection->GetStartPointY() + this->moveY );
			memDc->LineTo ( selection->GetMiddlePointX() + this->moveX , selection->GetMiddlePointY() + this->moveY );
			memDc->LineTo ( selection->GetEndPointX() + this->moveX , selection->GetStartPointY() + this->moveY );

			

			for ( Long j = 0; j < symbol->GetLength(); j++ )	{
				Sequence *tempCase = symbol->GetCases ( j );

				memDc->MoveTo ( tempCase->GetStartPointX() + this->moveX, tempCase->GetStartPointY() + this->moveY );
				memDc->LineTo ( tempCase->GetEndPointX() + this->moveX, tempCase->GetStartPointY() + this->moveY );
				memDc->LineTo ( tempCase->GetEndPointX() + this->moveX, tempCase->GetEndPointY() + this->moveY );
				memDc->LineTo ( tempCase->GetStartPointX() + this->moveX, tempCase->GetEndPointY() + this->moveY );
				memDc->LineTo ( tempCase->GetStartPointX() + this->moveX, tempCase->GetStartPointY() + this->moveY );
			}
		}
		else if( dynamic_cast< Arrow * > ( temp ) )	{
		
			memDc->MoveTo( startPointX , startPointY );
			memDc->LineTo( startPointX , endPointY );
			memDc->MoveTo( startPointX - 10, endPointY-10 );
			memDc->LineTo( startPointX , endPointY);
			memDc->LineTo( startPointX + 10, endPointY-10 );	
		}	
	}
		memDc->SelectObject( oldPen );;
		pen.DeleteObject( );
}


// 세로 스크롤
void RushNChart::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){

	int yInc = 0 ;	// 세로 스크롤 이동한 값

	this->scroll->VScroll(nSBCode, nPos, &yInc, &this->yPos, &this->yMax);

	ScrollWindow(0, -yInc, NULL, NULL);	
	SetScrollPos(SB_VERT, this->yPos, TRUE);	// 스크롤바 위치 설정

	InvalidateRect(NULL, FALSE);

}

// 가로 스크롤
void RushNChart::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){

	int xInc = 0 ;

	this->scroll->HScroll(nSBCode, nPos, &xInc, &this->xPos, &this->xMax);

	ScrollWindow(0, -xInc, NULL, NULL);
	SetScrollPos(SB_HORZ, this->xPos, TRUE);

	InvalidateRect(NULL, FALSE);

}

//마우스 휠
BOOL RushNChart::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt){

	int yInc=0;	

	this->scroll->MouseWheel(zDelta, &yInc, &this->yPos, &this->yMax);

	ScrollWindow(0,-yInc,NULL,NULL);	
	SetScrollPos(SB_VERT,this->yPos,TRUE);	// 스크롤바 위치 설정

	InvalidateRect(NULL, FALSE);

	return TRUE;
}


void RushNChart::MoveScreen(int xPoint, int yPoint) {

	// 상단으로 자동이동
	if ( yPoint - this->yPos < 40 ) {

		this->yPos = this->yPos - 30 ;

		// 로우플로우
		if ( this->yPos < 0) {

			this->yPos = 0;

		}

		SetScrollPos(SB_VERT,this->yPos,TRUE);
	}

	CRect windowSize;

	GetClientRect(windowSize);

	// 하단으로 자동이동
	if ( yPoint - this->yPos > windowSize.Height() - 40 ) {



		this->yPos = this->yPos + 30 ;

		// 오버플로우
		if ( this->yPos > this->yMax ) {

			this->yPos = this->yMax ;

		}

		SetScrollPos(SB_VERT,this->yPos,TRUE);

	}

	// 왼쪽으로 자동이동
	if ( xPoint - this->xPos < 40 ) {

		this->xPos = this->xPos - 30 ;

		// 로우플로우
		if ( this->xPos < 0) {

			this->xPos = 0;

		}

		SetScrollPos(SB_HORZ,this->xPos,TRUE);

	}

	// 오른쪽으로 자동이동
	if ( xPoint - this->xPos > windowSize.Width() - 40 ) {

		this->xPos = this->xPos + 30 ;

		// 오버플로우
		if ( this->xPos > this->xMax ) {

			this->xPos = this->xMax ;

		}

		SetScrollPos(SB_HORZ,this->xPos,TRUE);

	}

}


void RushNChart::UpdateBitMap(){

	if ( this->xPos + 30 >= this->xMax ){

		this->paperRect.right = this->paperRect.right + 400 ;
		this->xMax = this->xMax + 400 ;
		SetScrollRange(SB_HORZ,0,this->xMax,TRUE);

	}

	if ( this->yPos + 30 >= this->yMax ){

		this->paperRect.bottom = this->paperRect.bottom + 400 ;
		this->yMax = this->yMax + 400 ;
		SetScrollRange(SB_VERT,0,this->yMax,TRUE);
	}

}

void RushNChart::UpdateClient(){

	int length = this->paper->GetLength();
	int i = 0 ;

	while( i < length ) {

		Symbol *symbol = this->paper->GetAt(i);
		int width = symbol->GetEndPointX() + symbol->GetStartPointX();
		int height = symbol->GetEndPointY() + symbol->GetStartPointY();

		if ( this->paperRect.Width() < width + 400 ) {

			this->paperRect.right = this->paperRect.right + 400 ;
			this->xMax = this->xMax + 400 ;
			SetScrollRange(SB_HORZ,0,this->xMax,TRUE);

		}

		if ( this->paperRect.Height() < height + 500 ) {

			this->paperRect.bottom = this->paperRect.bottom + 400 ;
			this->yMax = this->yMax + 400 ;
			SetScrollRange(SB_VERT,0,this->yMax,TRUE);

		}

		i++;

	}

}


//미리보기 보기 닫을때
void RushNChart::ClosePreView(){
	if(this->preViewDlg != NULL){
		delete this->preViewDlg;
		this->preViewDlg = NULL;
	}
}