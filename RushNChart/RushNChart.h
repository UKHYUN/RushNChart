//RushNChart.h
#ifndef _RUSHNCHART_H
#define _RUSHNCHART_H
#include <afxwin.h>
#include <string>
#define ZOOM 4
#define zoom 2

using namespace std;
typedef long int Long ;

class Paper;
class Select;
class Move;
class Symbol;
class Pen;
class CopySymbol;
class PaperList;
class Scroll;
class PreViewDlg;

class RushNChart: public CFrameWnd	{
	friend class PreViewDlg;

	private:
		Paper	*paper;
		Select	*select;
		Move	*move;
		Pen		*pen;
		CopySymbol	*copySymbol;
		PaperList	*paperList;
		Scroll *scroll;
		PreViewDlg *preViewDlg;//미리보기

		Long	mouseCurrentPositionX ;
		Long	mouseCurrentPositionY ;
		Long	startPositionX ;
		Long	startPositionY ;
		Long	endPositionX ;
		Long	endPositionY;
		Long	caseNumber;

		CString	saveName ;						// Save 파일 이름 저장 - 채형석
		CString	loadName ;						// Load 파일 이름 저장 - 채형석
		
		Long	TransNumber;

		BOOL	bSelectedMenu ;
		BOOL	bDragFlag ;
		BOOL	bCompleteStructure ;
		BOOL	bSelectedSymbolFlag ;
		BOOL	bSelectedDBLClickedFlag;
		BOOL	bMovedSymbolFlag;
		BOOL	bSaveFlag;					// Save 조건에 대한 Flag - 채형석
		BOOL	bEmployFlag;				// 저장 여부 파악
		
		//추가
		BOOL	bLDown ;
		BOOL	bModify ;
		BOOL	bComposition;
		BOOL	bWritingFlag ; //식을 쓰는 중일때 TRUE

		Long windowWidth;
		Long windowHeight;

		// preview
		Symbol *dotSticker ;
		Symbol *( *dotStickers ) ;
		Long selectedSymbolLength ;


		// For MovePreview
		Long moveX ;
		Long moveY ;
		BOOL		bMovePreivew ;
		
		// SCroll 에 필요한 변수들  
		int xPos;	// 현재 가로 스크롤 위치값
		int yPos;	// 현재 세로 스크롤 위치값	
		int xMax;	// 가로 스크롤 범위값
		int yMax;	// 세로 스크롤 범위값

		CRect paperRect;	// 종이 크기

	public:
		Long columnCount ;
		string symbol ;
	public:
		RushNChart ( CWnd *parent = NULL );
		~RushNChart( );

		virtual BOOL PreCreateWindow( CREATESTRUCT& cs );

	public:
		void	PaintSymbols ( CDC *memDc ) ;
		void	PaintChart ( CDC *memDc ) ;
		void	SelectDisplay ( CDC *memDc ) ;
		void	SelectExpressionDisplay ( CDC *memDc );
		void	SetCaret ( CClientDC *cDC, string direction, wstring expression ) ;
		void	MoveSymbol ( Long symbolIndex, Symbol *movedSymbol );
		Long	CtrlSelected ( Long pointX, Long pointY );				// 다중선택하다 컨트롤 선택
		Long	SelectCheck ( Long pointX, Long pointY );				// 단일 선택하다
		Long	DragSelected ( Long startPointX, Long startPointY, Long endPointX, Long endPointY ); // 드레그 선택하다
		//추가
		void	PaintFieldSize ( CDC *memDc ) ;
		void	PaintSymbolDefaultSize ( CDC *memDc ) ;
		void	PaintSymbolSize ( CDC *memDc ) ;
		
		void	StickOnPaperWhenDraw ( Long startX, Long startY, Long index ) ;
		void	StickOnPaperWhenMove ( Long startX, Long startY, Long index ) ;
		void	StickOnPaperWhenMoveBudle ( ) ;

		// single preview
		void	DisplayDotSticker ( CDC *memDc ) ;
		void	DisplayDotStickers ( CDC *memDc ) ;

		void	StickerPreview () ;
		void	StickersPreview () ;

		void	PaintSymbolsForPrint ( CDC *memDc ) ;
		void	PaintChartForPrint ( CDC *memDc ) ;

		void	SetWrite ( wstring expression );
		

			//MovePreview
		void MovePreview( CDC *memDc ) ;
		void MovePreviewForChart( CDC *memDc ) ;

		void UpdateBitMap();
		void MoveScreen(int xPoint, int yPoint);
		void UpdateClient();

		//미리보기
		void ClosePreView();

		CRect GetPaperRect() const;
		int GetxPos() const;
		int GetyPos() const;
	
	protected:
		afx_msg int	 OnCreate ( LPCREATESTRUCT lpCreateStruct ) ;
		afx_msg void OnSize( UINT nType, int cx, int cy );
		afx_msg void OnClose () ;

		/********* 키보드 ***********/
		afx_msg void OnKeyDown ( UINT nChar, UINT nRepCnt, UINT nFlags );

		/********* 입 력 ***********/		
		afx_msg void OnChar ( UINT nChar, UINT nRepCnt, UINT nFlags ) ;
		afx_msg LRESULT OnIMEComposition ( WPARAM wParam, LPARAM lParam );

		/********* 마우스 ***********/
		afx_msg void OnLButtonDown ( UINT nFlag, CPoint point ) ;
		afx_msg void OnLButtonDblClk ( UINT nFlags, CPoint point );
		afx_msg void OnLButtonUp ( UINT nFlag, CPoint point ) ;
		afx_msg void OnRButtonDown ( UINT nFlag, CPoint point ) ;  //오른쪽 마우스 버튼을 Down
		afx_msg void OnRButtonUp ( UINT nFlag, CPoint point ) ;  //오른쪽 마우스 버튼을 Up
		afx_msg void OnMouseMove ( UINT nFlag, CPoint point ) ;

		//스크롤
		afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
		afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
		afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

		/********* 그리기 ***********/
		afx_msg void OnPaint() ;
		
		/********* 파 일 ***********/
		afx_msg void	OnNewPaperMenuClicked() ;
		afx_msg void	OnLoadMenuClicked() ;
		afx_msg void	OnSaveMenuClicked() ;
		afx_msg void	OnReNameSaveMenuClicked() ;
		afx_msg void	OnPrintMenuClicked() ;
		afx_msg void	OnPreViewMenuClicked() ;
		afx_msg void	OnCloseMenuClicked() ;

		/********* 도 형 ***********/
		afx_msg void	OnSequenceMenuClicked() ;
		afx_msg void	OnBeforeRepeatMenuClicked() ;
		afx_msg void	OnAfterRepeatMenuClicked() ;
		afx_msg void	OnSelectionMenuClicked() ;
		afx_msg void	OnSwitchCaseMenuClicked() ;
		afx_msg void	OnArrowMenuClicked() ;

		/********* 특수문자 ***********/
		afx_msg void	OnNotEqualMenuClicked() ;
		afx_msg void	OnBetterThanMenuClicked() ;
		afx_msg void	OnLesserThanMenuClicked() ;

		/********* 도움말 ***********/
		afx_msg void	OnHelpInFoButtonClicked() ;

		/********* 우버튼 클릭 메뉴 *********/
		afx_msg void	OnCutMenuClicked() ;
		afx_msg void	OnCopyMenuClicked() ;
		afx_msg void	OnPasteMenuClicked() ;
		afx_msg void	OnUndoMenuClicked() ;
		afx_msg void	OnRedoMenuClicked() ;
		afx_msg void	OnMakeChartButtonClicked() ;
		afx_msg void	OnReleaseChartButtonClicked() ;
		afx_msg void	OnSelectAllMenuClicked() ;
		afx_msg void	OnDeleteMenuClicked() ;
		
		DECLARE_MESSAGE_MAP()
};

inline CRect RushNChart::GetPaperRect() const{
	return this->paperRect;
}

inline int RushNChart::GetxPos() const{
	return this->xPos;
}

inline int RushNChart::GetyPos() const{
	return this->yPos;
}

#endif 