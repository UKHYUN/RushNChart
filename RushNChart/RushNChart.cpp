//RushNChart.cpp
/*
	������Ʈ�� : Rush & Chart
	��  ��  �� : RushNChart.cpp
	��  ��  �� : 2014�� 06�� 20��
	��      �� : i5(five)
	��      �� : �ȿ��� ( ���� ), ä����, ������, ����, ������ 
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

	/********* ��ũ�� ***********/
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	
	/********* Ű���� ***********/
	ON_WM_KEYDOWN( )

	/********* �� �� ***********/
	ON_WM_CHAR()
	ON_MESSAGE( WM_IME_COMPOSITION, OnIMEComposition )

	/********* ���콺 ***********/
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()

	/********* �׸��� ***********/
	ON_WM_PAINT( )

	/********* �� �� ***********/
	ON_COMMAND ( ID_NEW, OnNewPaperMenuClicked )
	ON_COMMAND ( ID_LOAD, OnLoadMenuClicked )
	ON_COMMAND ( ID_SAVE, OnSaveMenuClicked )
	ON_COMMAND ( ID_SAVE_AS,OnReNameSaveMenuClicked )
	ON_COMMAND ( ID_PRINT, OnPrintMenuClicked )
	ON_COMMAND ( ID_PRINT_PREVIEW, OnPreViewMenuClicked )
	ON_COMMAND ( ID_END, OnCloseMenuClicked )

	/********* �� �� ***********/
	ON_COMMAND ( ID_SEQUENCE, OnSequenceMenuClicked )
	ON_COMMAND ( ID_BEFORE_REPEAT, OnBeforeRepeatMenuClicked )
	ON_COMMAND ( ID_AFTER_REPEAT, OnAfterRepeatMenuClicked )
	ON_COMMAND ( ID_SELECTION, OnSelectionMenuClicked )
	ON_COMMAND ( ID_SWITCH_CASE, OnSwitchCaseMenuClicked )
	ON_COMMAND ( ID_ARROW, OnArrowMenuClicked )

	/********* Ư������ ***********/
	ON_COMMAND ( ID_NOT_EQUAL, OnNotEqualMenuClicked )
	ON_COMMAND ( ID_BETTER, OnBetterThanMenuClicked )
	ON_COMMAND ( ID_LESSER, OnLesserThanMenuClicked )

	/********* ���� ***********/
	ON_COMMAND ( ID_HELP, OnHelpInFoButtonClicked )

	/********* ���ư Ŭ�� �޴� *********/
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

	// ��ũ�� �ʱ�ȭ
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

	// �޴��� ��ü�Ѵ�. ���ӵǱ� ���� �޴�
	rButtonMenu->LoadMenu(IDR_RBUTTONMENU);
 
	//��Ʈ,��Ʈ���� ��ư �ʱ� ��Ȱ��ȭ ����
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
	this->bSelectedMenu = FALSE ;			//�޴�Ŭ����
	this->bDragFlag = FALSE ;				//���콺 Ŭ�� �� �̵���
	this->bCompleteStructure = FALSE ;		//������ �׸��� �ϼ�������
	this->bSelectedSymbolFlag = FALSE ;		//��ȣ�� Ŭ��������
	this->bSelectedDBLClickedFlag = FALSE;	//��ȣ�� ����Ŭ��������
	this->bMovedSymbolFlag = FALSE ;			//��ȣ�� �̵�������
	this->TransNumber = 0;					// ��ȣ�� ũ�⸦ �����ϰ��� �Ҷ�
	this->saveName = _T("");					// �ٸ��̸����� �����ϱ� ������� ���� �߰� -ä����-
	this->loadName = _T("");					// �ҷ����� �Ҷ� ��� �Ǵ� �̸� - ä����
	this->bSaveFlag = FALSE;					//SAVE �� ������ �ִ��� ���θ� Ȯ���� �� - ä����
	
	////
	//�߰�
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

	// ����Ʈ ������ ũ�⸦ ����
	// ��Ʈ�� ����Ʈ ũ��� ���� ����Ѵ�
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
	Invalidate(FALSE) ; //�޴����� ���� ���� ��, �������� ǥ�õǾ��� ��ȣ�� ������ ���ֱ��

}


void	RushNChart::OnBeforeRepeatMenuClicked()	{

	this->symbol = "BeforeRepeat" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //�޴����� ���� ���� ��, �������� ǥ�õǾ��� ��ȣ�� ������ ���ֱ��

	
}


void	RushNChart::OnAfterRepeatMenuClicked()	{

	this->symbol = "AfterRepeat" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //�޴����� ���� ���� ��, �������� ǥ�õǾ��� ��ȣ�� ������ ���ֱ��
}


void	RushNChart::OnSelectionMenuClicked()	{

	this->symbol = "Selection" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //�޴����� ���� ���� ��, �������� ǥ�õǾ��� ��ȣ�� ������ ���ֱ��
	
}


void	RushNChart::OnSwitchCaseMenuClicked()	{

	this->symbol = "SwitchCase" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //�޴����� ���� ���� ��, �������� ǥ�õǾ��� ��ȣ�� ������ ���ֱ��
	this->columnCount = 0 ;

	ColumnCountForm columnCountForm ;
	columnCountForm.DoModal() ;
	
}


void	RushNChart::OnArrowMenuClicked()	{
	
	this->symbol = "Arrow" ;
	this->bSelectedMenu = TRUE;
	this->bSelectedDBLClickedFlag = FALSE;
	Invalidate(FALSE) ; //�޴����� ���� ���� ��, �������� ǥ�õǾ��� ��ȣ�� ������ ���ֱ��

}


void	RushNChart::OnNotEqualMenuClicked()	{
	if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{
		this->bWritingFlag = TRUE; //���� ���� ���� ���϶�

		SelectPaper *selectPaper = this->select->GetSelectPaper();

		this->SetWrite( L"��" );

		CClientDC cDC( this );

		this->SetCaret( &cDC, "right", L"��" );

		Invalidate(FALSE) ; //�޴����� ���� ���� ��, �������� ǥ�õǾ��� ��ȣ�� ������ ���ֱ��
	}
}


void	RushNChart::OnBetterThanMenuClicked()	{
	if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{

		if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{
			this->bWritingFlag = TRUE; //���� ���� ���� ���϶�

			SelectPaper *selectPaper = this->select->GetSelectPaper();

			this->SetWrite( L"��" );

			CClientDC cDC( this );

			this->SetCaret( &cDC, "right", L"��" );

			Invalidate(FALSE) ; //�޴����� ���� ���� ��, �������� ǥ�õǾ��� ��ȣ�� ������ ���ֱ��
		}
	}
}


void	RushNChart::OnLesserThanMenuClicked()	{
	if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{
		if( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE )	{
			this->bWritingFlag = TRUE; //���� ���� ���� ���϶�

			SelectPaper *selectPaper = this->select->GetSelectPaper();

			this->SetWrite( L"��" );

			CClientDC cDC( this );

			this->SetCaret( &cDC, "right", L"��" );

			Invalidate(FALSE) ; //�޴����� ���� ���� ��, �������� ǥ�õǾ��� ��ȣ�� ������ ���ֱ��
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
	//CMenu* chartMenu = menu.GetSubMenu( 5 ); //�� �տ� �޴��� ������


	//��Ʈ,��Ʈ���� ��ư �ʱ� ��Ȱ��ȭ ����
	//chartMenu->EnableMenuItem( ID_MAKECHART, MF_GRAYED );
	Dmenu->EnableMenuItem( ID_RELEASECHART,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
	
	Dmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON , point.x, point.y, this); 
	/*
	"��Ʈ"��ư�� "��Ʈ ����"��ư�� �⺻ ����Ʈ���� diable, ȸ��������,
	������ �޴� ��ư�� Ŭ���ߴµ� ������ ��ȣ�̰�, ��ȣ�� �ΰ� �̻� ���õǾ��ִ� ��� 
	"��Ʈ"��ư�� Ȱ��ȭ �ȴ�.
	//*/
	if( select->GetSelectPaper( )->CheckSymbol( paper,point.x,point.y )>-1 &&  
		select->GetSelectPaper( )->GetLength( ) >= 2 ) {
	}

	/*
	������ �޴� ��ư�� Ŭ�������� ��Ʈ�̰�, ��Ʈ�� ���õǾ� �ִ� ���
	"��Ʈ ����"��ư�� Ȱ��ȭ �ȴ�"
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

	// ��ũ�� �Ѹ�ŭ ȭ���� �̵��ϴ�
	// �̵��� ��ŭ�� ��ǥ�� ���Ѵ�
	point.x = point.x + this->xPos;
	point.y = point.y + this->yPos;

	// �ٿ����� ���� ���콺�������� ��ġ�� ����
	this->startPositionX = point.x ;
	this->startPositionY = point.y ;

	this->endPositionX = point.x;		//endPoint �ʱ�ȭ
	this->endPositionY = point.y;		//endPoint �ʱ�ȭ
	
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

		// ������ Ŭ���� �ƴϸ� this->TransNumber == 0
		if ( this->TransNumber == 0 ) {
			if ( nFlag & MK_CONTROL ) { // ��Ʈ�� Ű�� ������ �� // �߰��� �����ϱ� 
				selectIndex = this->CtrlSelected( startPositionX, startPositionY );
				
					
			}
			else { // ��Ʈ��Ű ���� ��ȣ �ϳ��� ������ �� 
				selectIndex = this->SelectCheck( startPositionX, startPositionY );
				if ( selectIndex == - 1 ) { // ����ȭ���� Ŭ������ ���� �� Ǯ �� 
					this->bCompleteStructure = FALSE;
					this->bSelectedMenu = FALSE;
					this->bSelectedDBLClickedFlag = FALSE;
					this->bSelectedSymbolFlag = FALSE;
					this->bWritingFlag = FALSE ;
					
					select->ReleaseChart( );
					select->GetSelectPaper( ) ->ReleaseAllSymbols( );
				}
				else{ // ��ȣ �ϳ��� ���� ���� ��
						// ���� ���� = ������ ǥ��
						// �ߺ� ���� = ������
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
				this->bMovePreivew = TRUE ; // MovePreveiw Flag �ѱ�
		}
	}

	//�巡�� �̵��� basePoint, PreviousPoint���ϱ�
	
	if( this->bSelectedMenu == FALSE	&&		this->bSelectedSymbolFlag == FALSE) {
		this->bDragFlag = TRUE;
	}

	//*/


}


void	RushNChart::OnLButtonDblClk( UINT nFlags, CPoint point )	{

	GetCursorPos( &point ) ;
	ScreenToClient( &point ) ;

	// ��ũ�� �Ѹ�ŭ ȭ���� �̵��ϴ�
	// �̵��� ��ŭ�� ��ǥ�� ���Ѵ�
	point.x = point.x + this->xPos;
	point.y = point.y + this->yPos;

	if( this->bSelectedSymbolFlag == TRUE && select->IsChartSelected( )==false )	{
		//ĳ���� �����Ǹ� ���� �ִ� ������
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
	// ��ũ�� �Ѹ�ŭ ȭ���� �̵��ϴ�
	// �̵��� ��ŭ�� ��ǥ�� ���Ѵ�
	point.x = point.x + this->xPos;
	point.y = point.y + this->yPos;

	// MovePreview
	if( this->bMovePreivew == TRUE ) 
	{
		this->moveX = point.x - this->startPositionX ;
		this->moveY = point.y - this->startPositionY ;
		Invalidate(FALSE) ;
	}


	//���� ���� �� �̵� �϶�, ���̱� �̸����� 
	if( this->select->GetSelectPaper()->GetLength() == 1 && this->bMovePreivew == TRUE )
	{ 
		this->StickerPreview() ;
	}
	
	// ���� ���� �� �̵��� ��, ���̱� �̸����� 
	else if(  this->select->GetSelectPaper()->GetLength() > 1 && this->bMovePreivew == TRUE ) 
	{
		this->StickersPreview() ;
	}//*/


	if (this->bLDown == FALSE && this->bSelectedSymbolFlag == TRUE ) {
		this->TransNumber = this->select->GetSelectPaper()->TransNumber( paper, point.x, point.y );
		if ( this->TransNumber > 0 ) {
			Long	number = this->TransNumber ;
			if( number == 1 || number == 5 ) {
				SetCursor(LoadCursor(NULL,IDC_SIZENWSE));//���������� ������ �Ʒ� �밢��
			}
			else if ( number == 2 || number == 6 ) {
				SetCursor(LoadCursor(NULL,IDC_SIZENS)); //����
			}
			else if ( number == 3 || number == 7 ) {
				SetCursor(LoadCursor(NULL,IDC_SIZENESW)); //���������� �޾Ʒ� �밢��
			}
			else if ( number == 4 || number == 8 ) {
				SetCursor(LoadCursor(NULL,IDC_SIZEWE)); //�¿�
			}
		}
	}

	if ( this->bLDown == FALSE	 &&		this->bSelectedMenu == TRUE ) {
		this->startPositionX = point.x ;
		this->startPositionY = point.y ;
		Invalidate(FALSE) ;
	}

	if( this->bLDown == TRUE	 &&		this->bSelectedMenu == TRUE ){ //'�����'���� ���� ��ȣ�� ũ�⸦ �������� ǥ������ ũ����ǥ ����
		this->endPositionX = point.x ;
		this->endPositionY = point.y ;
		Invalidate(FALSE) ;
	}
	else if ( this->bLDown == TRUE	 &&		this->bSelectedMenu == FALSE ){
		this->endPositionX = point.x ;
		this->endPositionY = point.y ;
		Invalidate(FALSE) ;
	}
	// ���߼����ϴ� �巹�� ���� ǥ��
	else if ( this->bLDown == TRUE	 &&		this->bSelectedMenu == FALSE && this->bSelectedSymbolFlag == FALSE && this->bDragFlag ==TRUE ) {
		this->endPositionX = point.x ;
		this->endPositionY = point.y ;
		Invalidate(FALSE) ;
	}

	SelectPaper *selectPaper = select->GetSelectPaper( );
	if( this->bLDown == TRUE	&&	bMovedSymbolFlag == TRUE &&	this->bSelectedSymbolFlag == TRUE		&&		this->TransNumber == 0 )
	{
		//������ ��ȣ�� ���õǾ��ִٸ�
		if( selectPaper->GetLength( ) > 0 ){

			//�̵��� ��ȣ���� �� �����Ѵ�.
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
	
	//��ġ��
	if(  this->bLDown == TRUE && this->TransNumber > 0 ) { 
		Long	index = 0;
		Long	i = 0;

		Long	number = this->TransNumber ;
		if( number == 1 || number == 5 ) {
			SetCursor(LoadCursor(NULL,IDC_SIZENWSE));//���������� ������ �Ʒ� �밢��
		}
		else if ( number == 2 || number == 6 ) {
			SetCursor(LoadCursor(NULL,IDC_SIZENS)); //����
		}
		else if ( number == 3 || number == 7 ) {
			SetCursor(LoadCursor(NULL,IDC_SIZENESW)); //���������� �޾Ʒ� �밢��
		}
		else if ( number == 4 || number == 8 ) {
			SetCursor(LoadCursor(NULL,IDC_SIZEWE)); //�¿�
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
		// Line���̱� 
		//if( this->TransNumber > 0 ){
		if( this->TransNumber > 0 && this->select->GetSelectPaper()->GetLength() == 1 ){
			Sticker sticker ;
			this->dotSticker =  sticker.StickLineForPre( this->paper, index, this->TransNumber ) ;
		}
		/*
		// ���� ���� �� ��ĥ �� ���̱�
		if(  this->select->GetSelectPaper()->GetLength() > 1 ) //���߼����̸�
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
					if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// ���̴� ��Ȳ�̸�
					{
						sticker.GetInfoToMove( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), tempIndex ) ;
						string type = this->paper->CheckType( tempIndex ) ;
						//��ȣ�� �ٿ� �׸��� //���� ��ȣ�� �����
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

	// ��ũ�� �Ѹ�ŭ ȭ���� �̵��ϴ�
	// �̵��� ��ŭ�� ��ǥ�� ���Ѵ�
	point.x = point.x + this->xPos;
	point.y = point.y + this->yPos;

	Long	index;
	if( this->bSelectedMenu == TRUE )
	{ //�����
		Long index ;
		this->endPositionX = point.x ;
		this->endPositionY = point.y ;

		if( this->symbol != "SwitchCase" )	{
			index = this->paper->Draw ( startPositionX, startPositionY, endPositionX, endPositionY, L"", this->symbol ) ;
			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
		}
		else	{
			index = this->paper->Draw ( startPositionX, startPositionY, endPositionX, endPositionY, L"", this->symbol,
				this->columnCount );
			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
		}
		
		//�׸���� ���̱�� �߰�
		this->StickOnPaperWhenDraw( this->startPositionX, this->startPositionY, index  ) ;		
		paperList->CaptureLastPaper( paper );

		this->bSelectedSymbolFlag = FALSE ; //����� ��������, ������ ���õǾ ������ �ִ� ��ȣ�� ������ ���ֱ�

		//���� ���� ���� �ٷ� ���� �Է��ϱ� ���ؼ� Ŀ�� �����̱�
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

	// ���߼����ϴ� �巹�� ���ý�
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

	if( this->TransNumber > 0 ) { //��ġ��

		if ( this->select->GetSelectPaper()->GetLength() != 0 ) {
			
			index = this->paper->TransForm( this->select, this->TransNumber, point.x, point.y ) ;
			paperList->CaptureLastPaper( paper );
			this->select->GetSelectPaper()->ReNewSelected( paper );
			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
		}
		this->select->GetSelectPaper()->ReNewSelected( paper );
		//this->select->GetSelectChart()->ReNewSelected( paper->GetChart() );
		
		//Line ���̱� ����
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
		//���̸� �̵��Ͽ� ��ư�� �H����
		if( this->select->GetSelectPaper()->GetLength() > 0 ) {
			this->paper->Move( this->select, this->startPositionX, this->startPositionY, point.x, point.y );
			Invalidate(FALSE );
			bMovedSymbolFlag = FALSE;
			this->select->GetSelectPaper()->ReNewSelected( paper );
			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
		}
		//��Ʈ�� �̵��Ͽ� ��ư�� ������ 
		if( select->IsChartSelected( ) == true && paper->GetChart( )->GetLength( ) >0 ){
			this->paper->GetChart()->Move( this->startPositionX, this->startPositionY, point.x, point.y );
			Invalidate(FALSE );
			bMovedSymbolFlag = FALSE;
			select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
			select->GetSelectChart( )->DrawChartField( );
			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
		}

		// StickingSign
		Sticker sticker ;
		Long i = 0 ;
		while( i < this->paper->GetLength()  )
		{
			sticker.CheckStickingSign( this->paper , i ) ;
			i ++ ;
		}//*/

		//���� ���� �� �̵� �϶��� ���̱� 
		if( this->select->GetSelectPaper()->GetLength() == 1 )
		{
			Long index = (this->select->GetSelectPaper()->GetAt(0)).GetSeletedSymbolIndex() ;

			if( index > -1 )
			{
				Long startX = this->paper->GetAt( index )->GetStartPointX() ;
				Long startY = this->paper->GetAt( index )->GetStartPointY() ;
				//���� ���ñ�ȣ ���̱�
				this->StickOnPaperWhenMove( startX, startY, index ) ;
				//������ �ٽ� ǥ��
				this->select->GetSelectPaper()->ReNewSelected( paper );
			}
			//******************************
			//paperList->CaptureLastPaper( paper );
			//******************************
		}
			
		//���� ���� �� �̵� �϶� ���̱�
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
		//�ʱ�ȭ
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
		case 1:	// ��ü ����

			DestroyCaret( );

			//���� �Ǿ��ִ� symbol ����
			this->select->GetSelectPaper()->ReleaseAllSymbols();

			this->select->GetSelectPaper()->StoreSelectedSymbol( this->paper );
			//���� �Ҵ��ϰ�
			select->ReleaseChart( );
			select->ReAllocateChart( );
			//�����Ѵ�
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

				this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
			}

			break;

		case 22: // Ctrl + v

			this->copySymbol->PasteSymbols( this->select, this->paper );
			this->bSelectedSymbolFlag = TRUE;

			paperList->CaptureLastPaper( paper );

			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.

			break;

		case 24: // Ctrl + x

			this->copySymbol->CutSymbols( this->select, this->paper );
			paperList->CaptureLastPaper( paper );
			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.

			break;

		case 25: // Ctrl + y

			if( paperList->GetCurrent( ) + 1 <= paperList->GetLength( ) )	{
				Paper *redoPaper = this->paperList->Redo(  );
				paper = redoPaper ;
				
				Invalidate( FALSE );

				this->bSaveFlag = TRUE;
				this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
				this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
			}

			break;

		case VK_RETURN:	//Enter Key

			DestroyCaret() ;

			this->bCompleteStructure = FALSE;
			this->bSelectedMenu = FALSE;
			this->bSelectedDBLClickedFlag = FALSE;

			paperList->CaptureLastPaper( paper );
			//���� �� ����
			this->bWritingFlag = FALSE;

			break;

		default:

			//TRACE ( "nChar [ %d ]\n", nChar );

			if( nChar != VK_BACK && ( this->bCompleteStructure == TRUE || this->bSelectedDBLClickedFlag == TRUE ) )	{

				this->bWritingFlag = TRUE; //���� ���� ���� ���϶�
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
		
			this->bWritingFlag = TRUE; //���� ���� ���� ���϶�
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
		//���� �� ����
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
					this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
				}
				else if( this->paper->GetChart( )->GetLength( ) > 0 && bWritingFlag == FALSE){
					paper->GetChart( )->DeleteAllSymbols(  );
					paperList->CaptureLastPaper( paper );
					select->ReleaseChart( );
					this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
						this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
					}
					else	{
						if( this->pen->GetCurrentIndex() > 0 )	{
							tempString = symbol->GetExpression().substr( this->pen->GetCurrentIndex() - 1, 1 );
							Long ret = this->paper->Erase( symbolIndex, this->pen->GetCurrentIndex() - 1 );
							this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
						}
					}
				}
				else	{
					symbol = this->paper->GetAt( this->paper->GetLength() - 1 );

					if( this->pen->GetCurrentIndex() > 0 )	{
						tempString = symbol->GetExpression().substr( this->pen->GetCurrentIndex() - 1, 1 );
						Long ret = this->paper->Erase( this->paper->GetLength() - 1, this->pen->GetCurrentIndex() - 1 );
						this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
					this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
					this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
					this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
					this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
			//���� �� ����
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
			//���� �Ҵ��ϰ�
			select->ReleaseChart( );
			select->ReAllocateChart( );
			//�����Ѵ�
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
			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
			
		}
		 
		if ( nChar == 'x' || nChar == 'X' ) {
			this->copySymbol->CutSymbols( this->select, this->paper );
			paperList->CaptureLastPaper( paper );
			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
				this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
			}
		}
		if( nChar == 'y' || nChar == 'Y' ) {
			if( paperList->GetCurrent( ) + 1 <= paperList->GetLength( ) ){
				Paper *redoPaper = this->paperList->Redo(  );
				paper = redoPaper ;
				Invalidate(FALSE );
				this->bSaveFlag = TRUE;
				this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
				this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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

	//���� �� ���� ��ġ Ȯ��
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

		//������
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
		
		//���� �ϼ�
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
		this->bWritingFlag = TRUE; //���� ���� ���� ���϶�

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

	dc.SetWindowOrg(this->xPos, this->yPos);	// ��ũ�� �̵� ��ġ �ڵ�����

	this->UpdateClient();

	/******���� ���۸�******/

	// ���� ���۸��� ���� �޸�DC�� BITMAP ����
	CDC memDc ;
	CBitmap bitMap ;

	// ���� ���۸��� ���� �޸�DC�� BITMAP�� ���� DC�� ������ ��ġ
	memDc.CreateCompatibleDC(&dc);
	//bitMap.CreateCompatibleBitmap( &dc, this->windowWidth, this->windowHeight );
	bitMap.CreateCompatibleBitmap(&dc,this->paperRect.Width(), this->paperRect.Height() );
	memDc.SelectObject(&bitMap);

	//memDc.PatBlt(0,0, this->windowWidth, this->windowHeight, WHITENESS);
	memDc.PatBlt(0,0, this->paperRect.Width(), this->paperRect.Height(), WHITENESS);
	/*************************************** �޸�DC�� �׸��� ***************************************/

	if ( this->bLDown == FALSE && this->bSelectedMenu == TRUE 
		 && this->bDragFlag == FALSE ) { //����Ʈ �ɺ� ���� ǥ�ÿ�
		this->PaintSymbolDefaultSize( &memDc ) ;
	}
	if( bLDown == TRUE && bSelectedMenu == TRUE )	{// ������� ũ�� ����ǥ�ÿ�
		this->PaintSymbolSize( &memDc ) ;
	}
	// ���߼����ϴ� ���� ǥ�� - ä����
	if ( this->bDragFlag == TRUE )	{ // ���߼��� �ϴ� �� ũ�� ����ǥ�ÿ�
		this->PaintFieldSize( &memDc ) ;
	}
	if ( this->TransNumber != 0 ) {
		this->PaintFieldSize( &memDc );
	}

	this->PaintSymbols( &memDc ) ;
	this->PaintChart( &memDc ) ;

	//��ġ�� �̵��� ���� ���� ���� - this->TransNumber == 0 �ϋ� / 6�� 23��
	if ( this->bSelectedSymbolFlag == TRUE		&&	this->bSelectedMenu == FALSE && this->bMovedSymbolFlag ==FALSE && this->TransNumber == 0 )	{
		this->SelectDisplay ( &memDc ) ;
	}
	if ( this->bSelectedDBLClickedFlag == TRUE )	{
		//Select �����Ҷ� �������ּ���!
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
		if( this->dotStickers != 0 ) //this->dotStickers �ʱ�ȭ
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

	// �޸�DC�� �׷��� ������ ���� DC�� ���� 
	//dc.BitBlt(0, 0, this->windowWidth, this->windowHeight, &memDc, 0, 0, SRCCOPY);	
	dc.BitBlt(0, 0, this->paperRect.Width(), this->paperRect.Height(), &memDc, 0, 0, SRCCOPY);	

	//�μ� �̸�����
	if(this->preViewDlg != NULL){
		this->preViewDlg->DisplayPreView(&memDc);//DC�Ѱ��ֱ�
		Invalidate(FALSE);
	}

	// ���� �޸�DC�� BITMAP�� ����
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


void	RushNChart::SelectDisplay ( CDC *memDc )	{  // ���� : ä �� �� - > �� �� ��
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
	�Լ��̸� : CtrlSelected
	��    �� : ���߼����ϴ� Ctrl Ű �Է½� �Լ�
	��    �� : Ponit X, Point Y
	��    �� : index
	�� �� �� : ä �� �� - > ������
*/
Long	RushNChart::CtrlSelected ( Long pointX, Long pointY ) {
	Long	paperIndex;
	//Long	chartIndex;
	Long	checkDuIndex;
	Long	index = -1;
	paperIndex = this->select->GetSelectPaper()->CheckSymbol( paper, pointX, pointY );
	bool checkDuChart;
	
	//��Ʈ���
	if ( paperIndex == - 1 ) {
		
		//select->GetSelectPaper( )->ReleaseAllSymbols( );
		bool checkChart = select->GetSelectChart( )->CheckChart( paper->GetChart( ), pointX, pointY );
		//��Ʈ�� ��ȣ�̸�
		if ( checkChart == true ){
			//�ߺ����� �ƴ��� Ȯ���Ѵ�.
			checkDuChart = select->IsChartSelected( );
			//�̹� ������ �Ǿ��ִٸ�
			if( checkDuChart == true ) {
				//��Ʈ�� ���������Ѵ�.
				select->ReleaseChart( );

			}
			//�ߺ��� �ƴ϶��
			else{
				index = 0 ;
				//���� �Ҵ��ϰ�
				select->ReleaseChart( );
				select->ReAllocateChart( );
				//�����Ѵ�
				select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
				select->GetSelectChart( )->DrawChartField( );
				Invalidate( FALSE);
			}
		}
	}
	//������ ��ȣ�̸�.
	else {
		checkDuIndex = this->select->GetSelectPaper()->CheckDuplication( paperIndex );

		if ( checkDuIndex != - 1 ) {
			//�ߺ��̸�
			index = this->select->GetSelectPaper()->Release( checkDuIndex );
		}
		else {
			//�ߺ��� �ƴϸ�
			index = this->select->GetSelectPaper()->StoreSelectedSymbol( paper,paperIndex );
		}
	}

	return index;
}

/*
	�Լ��̸� : SelectCheck
	��    �� : ���� �����ϴ� �Լ�
	��    �� : Ponit X, Point Y
	��    �� : index
	�� �� �� : ä���� - > ������
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
	//������ ��ȣ�� �ƴҶ� 
	if ( paperIndex == - 1 ) {
		//��ȣ�� ��Ʈ�� ��ȣ���� Ȯ���Ѵ�.
		//������ ��ȣ���� ��� ���� �����ϰ�
		select->GetSelectPaper( )->ReleaseAllSymbols( );
		//��Ʈ�� Ȯ���Ѵ�.
		checkChart = select->GetSelectChart( )->CheckChart( paper->GetChart( ), pointX, pointY );
		//��Ʈ�� ��ȣ�̸�
		if ( checkChart == true ){
			index = 0 ;
			//���� �Ҵ��ϰ�
			select->ReleaseChart( );
			select->ReAllocateChart( );
		
			//�����Ѵ�
			select->GetSelectChart( )->GetFieldPoint( paper->GetChart( ) );
			select->GetSelectChart( )->DrawChartField( );
			Invalidate( FALSE);

			
		}
		
	
			//��Ʈ�� ��ȣ�� �ƴϸ�
		else{
			//���õ� ��Ʈ�� �����Ѵ�.
			select->ReleaseChart( );
			Invalidate(FALSE );
		}

	}
	else {
		//��Ʈ�� �Ҵ� �����Ѵ�...���ο� �����Ǳ�ȣ�� ������ ���!! 
		select->ReleaseChart( );

		checkDuIndex = selectPaper->CheckDuplication( paperIndex );
		//�ߺ��� �ƴϸ�
		if( checkDuIndex == -1 ){
			//������ ��ȣ�鵵 ���� ������Ų��.
			this->select->GetSelectPaper()->ReleaseAllSymbols();
			//���ο� ��ȣ�� �����ϰ�
			index = select->GetSelectPaper( )->StoreSelectedSymbol( paper, paperIndex );
		}
		//�ߺ��� ���
		else{
			index = selectPaper->GetLength( ) -1;
		}
	}

	return index;
}

/*
	�Լ��̸� : DragSelected
	��    �� : ���߼��� �Լ� �巹�� �� ��
	��    �� : startPonit X, startPoint Y, endPoint X, endPoint Y
	��    �� : index
	�� �� �� : ä����
*/
Long	RushNChart::DragSelected ( Long startPointX, Long startPointY, Long endPointX, Long endPointY ) {
	Long	index;

	index = this->select->GetSelectPaper()->CheckSymbols( paper, startPointX, startPointY, endPointX, endPointY );
//	index = this->select->GetSelectChart()->CheckSymbols( paper->GetChart(), startPointX, startPointY, endPointX, endPointY );
	
	return index;
}


/*
	�Լ��̸� : StickOnPaperWhenDraw
	��    �� : �׸� �� �ٿ� �׸���
	��    �� : Long startX, Long startY, Long index
	��    �� : void
	�� �� �� : i5
*/
void	RushNChart::StickOnPaperWhenDraw( Long startX, Long startY, Long index ) {

	Sticker sticker ;


	//���� ������ �����´�
	sticker.CheckStickingField( this->paper, this->select, index ) ;
	
	if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// ���̴� ��Ȳ�̸�
	{
			
		//���� ��ȣ�� ��ġ�� ũ�⸦ ���ϴ�
		sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), index ) ;
		
		//��ȣ�� �ٿ� �׸��� //���� ��ȣ�� �����
		sticker.StickTo( this->paper, sticker.GetStartX(), sticker.GetStartY(), sticker.GetEndX(), sticker.GetEndY(), paper->GetAt(index)->GetExpression(), this->symbol, index ) ;
		
	}
	
	// StickingSign
	for( Long i = 0 ; i < this->paper->GetLength() ; i++){
		sticker.CheckStickingSign( this->paper, i ) ;
	}

}
/*
	�Լ��̸� : StickOnPaperWhenMove
	��    �� : �̵� �� �� ���δ� 
	��    �� : Long startX, Long startY, Long index
	��    �� : void
	�� �� �� : i5
*/
void	RushNChart::StickOnPaperWhenMove( Long startX, Long startY, Long index ) {

	Sticker sticker ;
	sticker.CheckStickingFieldForMove( this->paper, this->select, index, 0 ,0 ) ;
	
	if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// ���̴� ��Ȳ�̸�
	{
			
		//���� ��ȣ�� ��ġ�� ũ�⸦ ���ϴ�
		sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), index ) ;
		string type = this->paper->CheckType( index ) ;
		//��ȣ�� �ٿ� �׸��� //���� ��ȣ�� �����
		sticker.StickTo( this->paper, sticker.GetStartX(), sticker.GetStartY(), sticker.GetEndX(), sticker.GetEndY(), paper->GetAt(index)->GetExpression(), type, index ) ;
		
	}
	
	// StickingSign
	Long i = 0 ;
	for( Long i = 0 ; i < this->paper->GetLength() ; i++){
		sticker.CheckStickingSign( this->paper, i ) ;
	}

}

/*
	�Լ��̸� : StickOnPaperWhenMoveBudle
	��    �� : ���� ���õ� ��ȣ���� �̵� �� �� ���δ� 
	��    �� : void
	��    �� : void
	�� �� �� : i5
*/
void RushNChart::StickOnPaperWhenMoveBudle() {
	Sticker sticker ;
	sticker.SearchTopBottom( this->paper, this->select ) ;
	sticker.CheckStickingFieldForMove( this->paper, this->select, sticker.GetTopIndex(), 0 ,0 ) ;

	if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// ���̴� ��Ȳ�̸�
	{
		sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), sticker.GetTopIndex() ) ;
		sticker.GetGap( this->paper, sticker.GetTopIndex()  ) ;
		sticker.StickBundleTo( paper, select, sticker.GetStartGapX(), sticker.GetStartGapY() ) ;

		this->select->GetSelectPaper()->ReNewSelected( paper ) ;
		
	}
	else {
		sticker.CheckStickingFieldForMove( this->paper, this->select, sticker.GetBottonIndex(), 0 ,0 ) ; ;
		
		if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// ���̴� ��Ȳ�̸�
		{
			sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), sticker.GetBottonIndex() ) ;
			sticker.GetGap( this->paper, sticker.GetBottonIndex()  ) ;
			sticker.StickBundleTo( paper, select, sticker.GetStartGapX(), sticker.GetStartGapY() ) ;

			this->select->GetSelectPaper()->ReNewSelected( paper ) ;
			
		}
	}

	// ��ȣ���� stickSign�� �����Ѵ�
	for( Long i = 0 ; i < this->paper->GetLength() ; i++){
		sticker.CheckStickingSign( this->paper, i ) ;
	}
}

/*
	�Լ��̸� : DisplayDotSticker
	��    �� : ��ȣ�� �����Ͽ� �̵� ��, �ٿ����� ��ġ�� �̵��ÿ� �ٿ��� ���� �������� ǥ�����ش�
	��    �� : CPaintDC *dc
	��    �� : void
	�� �� �� : i5
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
	�Լ��̸� : DisplayDotStickers
	��    �� : ��ȣ�� ���� �����Ͽ� �̵� ��, �ٿ����� ��ġ�� �̵��ÿ� �ٿ��� ���� �������� ǥ�����ش�
	��    �� : CPaintDC *dc
	��    �� : void
	�� �� �� : i5
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
	�Լ��̸� : StickerPreview
	��    �� : ��ȣ�� �����Ͽ� �̵� ��, �ٿ����� ��ġ�� �̵��ÿ� �ٿ��� ��ȣ���� �������� ǥ���ϱ� ���ؼ�, �ʿ��� ������(��ȣ)�� �����
	��    �� : void
	��    �� : void
	�� �� �� : i5
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
		
		if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// ���̴� ��Ȳ�̸�
		{
			sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), index ) ;
			string type = this->paper->CheckType( index ) ;
			this->dotSticker = sticker.StickToForPre( this->paper, sticker.GetStartX(), sticker.GetStartY(), sticker.GetEndX(), sticker.GetEndY(), paper->GetAt(index)->GetExpression(), type, index ) ;
		}
	}
}

/*
	�Լ��̸� : StickersPreview
	��    �� : ��ȣ�� ���� �����Ͽ� �̵� ��, �ٿ����� ��ġ�� �̵��ÿ� �ٿ��� ��ȣ���� �������� ǥ���ϱ� ���ؼ�, �ʿ��� ������(��ȣ)�� �����
	��    �� : void
	��    �� : void
	�� �� �� : i5
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

	if( this->dotStickers != 0 ) //this->dotStickers �ʱ�ȭ
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

	if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// ���̴� ��Ȳ�̸�
	{
		sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), sticker.GetTopIndex() ) ;
		sticker.GetGap( this->paper, sticker.GetTopIndex()  ) ;
		sticker.StickBundleToForPre( paper, select, sticker.GetStartGapX(), sticker.GetStartGapY(), this->dotStickers, this->selectedSymbolLength  ) ;

	}
	else 
	{
		sticker.CheckStickingFieldForMove( this->paper, this->select, sticker.GetBottonIndex(), this->moveX, this->moveY ) ;
		if( sticker.GetStickedIndex() != -1 && sticker.GetStickingField() != -1 )// ���̴� ��Ȳ�̸�
			{
				sticker.GetInfo( this->paper, sticker.GetStickedIndex(), sticker.GetStickingField(), sticker.GetBottonIndex() ) ;
				sticker.GetGap( this->paper, sticker.GetBottonIndex()  ) ;
				sticker.StickBundleToForPre( paper, select, sticker.GetStartGapX(), sticker.GetStartGapY(), this->dotStickers, this->selectedSymbolLength  ) ;
			}


	}
	if( this->dotStickers[0] == 0 ) //���̴� ��Ȳ�� �ƴϸ�
	{
		if( this->dotStickers != 0 ) //this->dotStickers �ʱ�ȭ
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
	}// dotStickers �迭�� ������ ������, �Ҵ������ؼ� OnPaint���� DisplayDotStickers�� �θ��� �ʵ��� �Ѵ�
}

/*
	�Լ��̸� : OnClose
	��    �� : �ݱ��ư��������
	��    �� : ����
	��    �� : ����
	�� �� �� : ���� - ä����
*/
void RushNChart::OnClose()	{
	wchar_t	*save;

	if ( this->bSaveFlag == FALSE ) {

		Long ret = ::MessageBoxA(NULL, "�����Ͻðڽ��ϱ�?", "Ȯ��", MB_YESNOCANCEL|MB_ICONINFORMATION) ;

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
	�Լ��̸� : OnNewPaperMenuClicked
	��    �� : �� ���� �޴���ư�� ��������
	��    �� : ����
	��    �� : ����
	�� �� �� : ���� - ä����
*/
void	RushNChart::OnNewPaperMenuClicked( ) {

	if ( this->bEmployFlag == TRUE ) {
		
		Long ret = ::MessageBoxA(NULL, " ��Ʈ�� �����Ͻðڽ��ϱ�?", "Ȯ��", MB_YESNOCANCEL|MB_ICONINFORMATION) ;

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
	
			// �������� ����� Undo �����͵��� ��� �ʱ�ȭ �Ѵ�.
			paperList->Initialize( );
			//�� ȭ���� �����Ѵ�.
			paperList->CaptureLastPaper( paper );


			Invalidate(FALSE) ;
	
			this->bSelectedMenu = FALSE ;			//�޴�Ŭ����
			this->bDragFlag = FALSE ;				//���콺 Ŭ�� �� �̵���
			this->bCompleteStructure = FALSE ;		//������ �׸��� �ϼ�������
			this->bSelectedSymbolFlag = FALSE ;		//��ȣ�� Ŭ��������
			this->bSelectedDBLClickedFlag = FALSE;	//��ȣ�� ����Ŭ��������
			this->bMovedSymbolFlag = FALSE ;			//��ȣ�� �̵�������
			this->TransNumber = 0;					// ��ȣ�� ũ�⸦ �����ϰ��� �Ҷ�
			this->saveName = _T("");					// �����Ҷ� ��� �ϴ� �̸� -ä����-
			this->loadName = _T("");					// �ҷ����� �Ҷ� ��� �Ǵ� �̸� - ä����
			this->bSaveFlag = FALSE;					//SAVE �Ǿ��ִ��� ���θ� �ľǼ� - ä����
			this->bEmployFlag = FALSE;			// ���� ���θ� �ľ��Ѵ�.
		}
	}
	else {

		if ( this->paper != NULL ) {
			delete this->paper;
		}
		this->paper = new Paper;
	
		// �������� ����� Undo �����͵��� ��� �ʱ�ȭ �Ѵ�.
		paperList->Initialize( );
		//�� ȭ���� �����Ѵ�.
		paperList->CaptureLastPaper( paper );


		Invalidate(FALSE) ;
	
		this->bSelectedMenu = FALSE ;			//�޴�Ŭ����
		this->bDragFlag = FALSE ;				//���콺 Ŭ�� �� �̵���
		this->bCompleteStructure = FALSE ;		//������ �׸��� �ϼ�������
		this->bSelectedSymbolFlag = FALSE ;		//��ȣ�� Ŭ��������
		this->bSelectedDBLClickedFlag = FALSE;	//��ȣ�� ����Ŭ��������
		this->bMovedSymbolFlag = FALSE ;			//��ȣ�� �̵�������
		this->TransNumber = 0;					// ��ȣ�� ũ�⸦ �����ϰ��� �Ҷ�
		this->saveName = _T("");					// �����Ҷ� ��� �ϴ� �̸� -ä����-
		this->loadName = _T("");					// �ҷ����� �Ҷ� ��� �Ǵ� �̸� - ä����
		this->bSaveFlag = FALSE;					//SAVE �Ǿ��ִ��� ���θ� �ľǼ� - ä����
		this->bEmployFlag = FALSE;			// ���� ���θ� �ľ��Ѵ�.
	}
}

/*
	�Լ��̸� : OnSaveMenuClicked
	��    �� : �����ϱ� ��ư�� ������ ��
	��    �� : ����
	��    �� : ����
	�� �� �� : ���� - ä���� ( i5 )
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
	�Լ��̸� : OnReNameSaveMenuClicked
	��    �� : �ٸ� �̸����� �����ϱ� �޴� ��ư�� ������ ��
	��    �� : ����
	��    �� : ����
	�� �� �� : ���� - ä���� ( i 5 )
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
	�Լ��̸� : OnLoadMenuClicked
	��    �� : �ҷ����� �޴� ��ư�� ������ ��
	��    �� : ����
	��    �� : ����
	�� �� �� : ä���� ( i5 )
*/
void	RushNChart::OnLoadMenuClicked( ) {
	wchar_t	*save;

	if ( this->paper != NULL ) {

		if ( this->bEmployFlag == TRUE ) {

			Long ret = ::MessageBoxA(NULL, "����� ������ �����Ͻðڽ��ϱ�?", "Ȯ��", MB_YESNOCANCEL|MB_ICONINFORMATION) ;
		
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
	
		this->bSelectedMenu = FALSE ;			//�޴�Ŭ����
		this->bDragFlag = FALSE ;				//���콺 Ŭ�� �� �̵���
		this->bCompleteStructure = FALSE ;		//������ �׸��� �ϼ�������
		this->bSelectedSymbolFlag = FALSE ;		//��ȣ�� Ŭ��������
		this->bSelectedDBLClickedFlag = FALSE;	//��ȣ�� ����Ŭ��������
		this->bMovedSymbolFlag = FALSE ;			//��ȣ�� �̵�������
		this->TransNumber = 0;					// ��ȣ�� ũ�⸦ �����ϰ��� �Ҷ�
		this->saveName = _T("");					// �ٸ��̸����� �����ϱ� ������� ���� �߰� -ä����-
		this->loadName = _T("");					// �ҷ����� �Ҷ� ��� �Ǵ� �̸� - ä����
		this->bSaveFlag = FALSE;					//SAVE �� ������ �ִ��� ���θ� Ȯ���� �� - ä����
		this->bEmployFlag = FALSE;				// ������ ������ �ִ��� ���θ� �ľǼ�
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
	�Լ��̸� : OnPrintMenuClicked
	��    �� : �μ��ϱ� �޴� ��ư�� ������ ��
	��    �� : ����
	��    �� : ����
	�� �� �� : i5
*/
void	RushNChart::OnPrintMenuClicked(  ) {
	
	CPrintDialog dlg(TRUE);

	CDC PrintDC; // printDC�� �� CDC�� �����

	int printHeight = 2000;

	if (dlg.DoModal() == IDOK &&   PrintDC.Attach(dlg.CreatePrinterDC())     )  // CDC�� print dc�� �����
	{

		DOCINFO doc;

		memset(&doc, 0x00, sizeof(DOCINFO));
		doc.cbSize = sizeof(DOCINFO);
		doc.lpszDocName = L"RushNChart";

		PrintDC.StartDoc(&doc); // ����Ʈ ����
		PrintDC.StartPage();

		CDC memDC; 
		memDC.CreateCompatibleDC(&PrintDC); // print dc�� �޸�dc�� �����

		CBitmap bitMap;

		bitMap.CreateCompatibleBitmap(&PrintDC, 14040, 9924 ); // ��Ʈ���� �ʱ�ȭ �Ѵ�. �ʺ� ���� ���� // �ȼ�����

		memDC.SelectObject(&bitMap); // memDC�� �׸��� ��ȭ���� bitMap���� ���Ѵ�?????


		// �̴� ������ A4( 210mm * 297mm ) -> inch�� ��ȯ�� A4( 8.27inch * 11.7inch ) -> �뷫 A4( 8 inch * 12 inch ) 
		// A4 ���η� ���� �μ⸦ �Ѵٰ� ������ �� ���� ���� ��ġ�� �Ʒ��� ����
		Long paperWidthInch = 12 ;
		Long paperHeightInch = 8 ;

		// DucuPrint p215b ���� ������ �ػ󵵰� ���� 1200dpi, ���� 1200dip �� ��,
		Long printerWidthDpi = 1200 ;
		Long printerHeightDpi = 1200 ;
		
		// �� ������ �ػ󵵸� �������� A4�� �ȼ� ũ��� �뷫 �Ʒ��� ����
		Long paperWidth = paperWidthInch * printerWidthDpi ;
		Long paperHeight = paperHeightInch * printerHeightDpi ;

		memDC.PatBlt(0,0, paperWidth, paperHeight, WHITENESS ); 

		this->PaintSymbolsForPrint(&memDC); // memDC�� ���� ���� �ڷḦ �׸���
		this->PaintChartForPrint(&memDC) ;
		//PrintDC.StretchBlt(0, 0, 14040, 9924,&memDC, 0, 0, 14040, 9924 , SRCCOPY); // memDC �� �׸� ��Ʈ���� print dc�� Ȯ���ؼ� �׷��ִ´�
		PrintDC.BitBlt( 0, 0, paperWidth, paperHeight, &memDC ,0  ,0 ,SRCCOPY ) ;

		PrintDC.EndPage();

		PrintDC.EndDoc();

		memDC.DeleteDC();
		bitMap.DeleteObject();
		PrintDC.DeleteDC();

	}
}


/*
	�Լ��̸� : PaintSymbolsForPrint
	��    �� : �μ��ϱ� �޴� ��ư�� ������ ��
	��    �� : CDC *memDc ( ������â�� �׸� �� ���� dc ) 
	��    �� : ����
	�� �� �� : i5
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
			// ���� ���� CRect, DrawText
			CRect expressionRect(expressionStartPointX, expressionStartPointY, 
				expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( temp->GetExpression().c_str(), expressionRect, DT_VCENTER|DT_SINGLELINE );

			// TRUE ���ǽ��� ���� CRect, DrawText
			string conditionTrue = "TRUE" ;
			expressionStartPointX = startPointX + (5 * ZOOM ) ;
			expressionStartPointY = endPointY - (30 * ZOOM ) ;
			expressionEndPointX = startPointX + (70 * ZOOM ) ;
			expressionEndPointY = endPointY - (5  * ZOOM ) ;

			CRect conditionTrueRect(  expressionStartPointX,  expressionStartPointY,  expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_VCENTER|DT_SINGLELINE );

			// FALSE ���ǽ��� ���� CRect, DrawText
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

			// TRUE ���ǽ��� ���� CRect, DrawText
			string conditionTrue = "TRUE" ;
			expressionStartPointX = selection->GetStartPointX() * ZOOM + (5 * ZOOM ) ;
			expressionStartPointY = selection->GetMiddlePointY() * ZOOM - (30 * ZOOM ) ;
			expressionEndPointX = selection->GetStartPointX() * ZOOM + (70 * ZOOM ) ;
			expressionEndPointY = selection->GetMiddlePointY() * ZOOM - (5  * ZOOM ) ;

			CRect conditionTrueRect(  expressionStartPointX,  expressionStartPointY,  expressionEndPointX, expressionEndPointY );
			memDc->SetBkMode(TRANSPARENT);
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_VCENTER|DT_SINGLELINE );

			// FALSE ���ǽ��� ���� CRect, DrawText
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
	�Լ��̸� : PaintChartForPrint
	��    �� : �μ��ϱ� �޴� ��ư�� ������ ��
	��    �� : CDC *memDc ( ������â�� �׸� �� ���� dc ) 
	��    �� : ����
	�� �� �� : i5
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

			// TRUE ���ǽ��� ���� CRect, DrawText
			string conditionTrue = "TRUE" ;
			expressionStartPointX = startPointX + (5 * ZOOM ) ;
			expressionStartPointY = endPointY - (30 * ZOOM ) ;
			expressionEndPointX = startPointX + (70 * ZOOM ) ;
			expressionEndPointY = endPointY - (5  * ZOOM ) ;

			CRect conditionTrueRect(  expressionStartPointX,  expressionStartPointY,  expressionEndPointX, expressionEndPointY );
			memDc->DrawText( conditionTrue.c_str(), conditionTrueRect, DT_VCENTER|DT_SINGLELINE );

			// FALSE ���ǽ��� ���� CRect, DrawText
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
	�Լ��̸� : OnCopyMenuClicked
	��    �� : ���콺 ������ ��ư �����ϱ� 
	��    �� : ����
	��    �� : ����
	�� �� �� : i5
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
	�Լ��̸� : OnPasteMenuClicked
	��    �� : ���콺 ������ ��ư �ٿ��ֱ� 
	��    �� : ����
	��    �� : ����
	�� �� �� : i5
*/
void	RushNChart::OnPasteMenuClicked( ) {
	this->bSelectedSymbolFlag = TRUE;
	this->copySymbol->PasteSymbols( this->select, this->paper );
	Invalidate(FALSE) ;
	this->bSaveFlag = TRUE;
	this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
	�Լ��̸� : OnCutMenuClicked
	��    �� : ���콺 ������ ��ư �߶󳻱� 
	��    �� : ����
	��    �� : ����
	�� �� �� : i5
*/
void	RushNChart::OnCutMenuClicked( ) {
	this->copySymbol->CutSymbols( this->select, this->paper );
	Invalidate(FALSE) ;
	this->bSaveFlag = TRUE;
	this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
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
	Long ret = ::MessageBoxA(NULL, "�����Ͻðڽ��ϱ�?", "Ȯ��", MB_YESNOCANCEL|MB_ICONINFORMATION) ;

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
		this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
	}

}


void	RushNChart::OnRedoMenuClicked( ) {
	if( paperList->GetCurrent( ) + 1 <= paperList->GetLength( ) ){
		Paper *redoPaper = this->paperList->Redo(  );
		paper = redoPaper ;
		Invalidate(FALSE );
		this->bSaveFlag = TRUE;
		this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
	}
}


void	RushNChart::OnSelectAllMenuClicked( ) {

	this->select->GetSelectPaper()->StoreSelectedSymbol( this->paper );
	//���� �Ҵ��ϰ�
	select->ReleaseChart( );
	select->ReAllocateChart( );
	//�����Ѵ�
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
			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
		}
		else if( this->paper->GetChart( )->GetLength( ) > 0 && bWritingFlag == FALSE){
			paper->GetChart( )->DeleteAllSymbols(  );
			paperList->CaptureLastPaper( paper );
			select->ReleaseChart( );
			this->bEmployFlag = TRUE;			// ���� ���θ� �ľ��Ѵ�.
		}
		
	}
	Invalidate();
}

void RushNChart::OnSize( UINT nType, int cx, int cy )	{
	this->windowWidth = cx;
	this->windowHeight = cy;
}



/*
	�Լ��̸� : MovePreview
	��    �� : ��ȣ(��)�� �����ؼ� �̵��� �̸����⸦ �׸��� �Լ�
	��    �� : CDC *memDc
	��    �� : ����
	�� �� �� : i5
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
	�Լ��̸� : MovePreviewForChart
	��    �� : ��Ʈ�� �����ؼ� �̵��� �̸����⸦ �׸��� �Լ�
	��    �� : CDC *memDc
	��    �� : ����
	�� �� �� : i5
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


// ���� ��ũ��
void RushNChart::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){

	int yInc = 0 ;	// ���� ��ũ�� �̵��� ��

	this->scroll->VScroll(nSBCode, nPos, &yInc, &this->yPos, &this->yMax);

	ScrollWindow(0, -yInc, NULL, NULL);	
	SetScrollPos(SB_VERT, this->yPos, TRUE);	// ��ũ�ѹ� ��ġ ����

	InvalidateRect(NULL, FALSE);

}

// ���� ��ũ��
void RushNChart::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){

	int xInc = 0 ;

	this->scroll->HScroll(nSBCode, nPos, &xInc, &this->xPos, &this->xMax);

	ScrollWindow(0, -xInc, NULL, NULL);
	SetScrollPos(SB_HORZ, this->xPos, TRUE);

	InvalidateRect(NULL, FALSE);

}

//���콺 ��
BOOL RushNChart::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt){

	int yInc=0;	

	this->scroll->MouseWheel(zDelta, &yInc, &this->yPos, &this->yMax);

	ScrollWindow(0,-yInc,NULL,NULL);	
	SetScrollPos(SB_VERT,this->yPos,TRUE);	// ��ũ�ѹ� ��ġ ����

	InvalidateRect(NULL, FALSE);

	return TRUE;
}


void RushNChart::MoveScreen(int xPoint, int yPoint) {

	// ������� �ڵ��̵�
	if ( yPoint - this->yPos < 40 ) {

		this->yPos = this->yPos - 30 ;

		// �ο��÷ο�
		if ( this->yPos < 0) {

			this->yPos = 0;

		}

		SetScrollPos(SB_VERT,this->yPos,TRUE);
	}

	CRect windowSize;

	GetClientRect(windowSize);

	// �ϴ����� �ڵ��̵�
	if ( yPoint - this->yPos > windowSize.Height() - 40 ) {



		this->yPos = this->yPos + 30 ;

		// �����÷ο�
		if ( this->yPos > this->yMax ) {

			this->yPos = this->yMax ;

		}

		SetScrollPos(SB_VERT,this->yPos,TRUE);

	}

	// �������� �ڵ��̵�
	if ( xPoint - this->xPos < 40 ) {

		this->xPos = this->xPos - 30 ;

		// �ο��÷ο�
		if ( this->xPos < 0) {

			this->xPos = 0;

		}

		SetScrollPos(SB_HORZ,this->xPos,TRUE);

	}

	// ���������� �ڵ��̵�
	if ( xPoint - this->xPos > windowSize.Width() - 40 ) {

		this->xPos = this->xPos + 30 ;

		// �����÷ο�
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


//�̸����� ���� ������
void RushNChart::ClosePreView(){
	if(this->preViewDlg != NULL){
		delete this->preViewDlg;
		this->preViewDlg = NULL;
	}
}