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
		PreViewDlg *preViewDlg;//�̸�����

		Long	mouseCurrentPositionX ;
		Long	mouseCurrentPositionY ;
		Long	startPositionX ;
		Long	startPositionY ;
		Long	endPositionX ;
		Long	endPositionY;
		Long	caseNumber;

		CString	saveName ;						// Save ���� �̸� ���� - ä����
		CString	loadName ;						// Load ���� �̸� ���� - ä����
		
		Long	TransNumber;

		BOOL	bSelectedMenu ;
		BOOL	bDragFlag ;
		BOOL	bCompleteStructure ;
		BOOL	bSelectedSymbolFlag ;
		BOOL	bSelectedDBLClickedFlag;
		BOOL	bMovedSymbolFlag;
		BOOL	bSaveFlag;					// Save ���ǿ� ���� Flag - ä����
		BOOL	bEmployFlag;				// ���� ���� �ľ�
		
		//�߰�
		BOOL	bLDown ;
		BOOL	bModify ;
		BOOL	bComposition;
		BOOL	bWritingFlag ; //���� ���� ���϶� TRUE

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
		
		// SCroll �� �ʿ��� ������  
		int xPos;	// ���� ���� ��ũ�� ��ġ��
		int yPos;	// ���� ���� ��ũ�� ��ġ��	
		int xMax;	// ���� ��ũ�� ������
		int yMax;	// ���� ��ũ�� ������

		CRect paperRect;	// ���� ũ��

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
		Long	CtrlSelected ( Long pointX, Long pointY );				// ���߼����ϴ� ��Ʈ�� ����
		Long	SelectCheck ( Long pointX, Long pointY );				// ���� �����ϴ�
		Long	DragSelected ( Long startPointX, Long startPointY, Long endPointX, Long endPointY ); // �巹�� �����ϴ�
		//�߰�
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

		//�̸�����
		void ClosePreView();

		CRect GetPaperRect() const;
		int GetxPos() const;
		int GetyPos() const;
	
	protected:
		afx_msg int	 OnCreate ( LPCREATESTRUCT lpCreateStruct ) ;
		afx_msg void OnSize( UINT nType, int cx, int cy );
		afx_msg void OnClose () ;

		/********* Ű���� ***********/
		afx_msg void OnKeyDown ( UINT nChar, UINT nRepCnt, UINT nFlags );

		/********* �� �� ***********/		
		afx_msg void OnChar ( UINT nChar, UINT nRepCnt, UINT nFlags ) ;
		afx_msg LRESULT OnIMEComposition ( WPARAM wParam, LPARAM lParam );

		/********* ���콺 ***********/
		afx_msg void OnLButtonDown ( UINT nFlag, CPoint point ) ;
		afx_msg void OnLButtonDblClk ( UINT nFlags, CPoint point );
		afx_msg void OnLButtonUp ( UINT nFlag, CPoint point ) ;
		afx_msg void OnRButtonDown ( UINT nFlag, CPoint point ) ;  //������ ���콺 ��ư�� Down
		afx_msg void OnRButtonUp ( UINT nFlag, CPoint point ) ;  //������ ���콺 ��ư�� Up
		afx_msg void OnMouseMove ( UINT nFlag, CPoint point ) ;

		//��ũ��
		afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
		afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
		afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

		/********* �׸��� ***********/
		afx_msg void OnPaint() ;
		
		/********* �� �� ***********/
		afx_msg void	OnNewPaperMenuClicked() ;
		afx_msg void	OnLoadMenuClicked() ;
		afx_msg void	OnSaveMenuClicked() ;
		afx_msg void	OnReNameSaveMenuClicked() ;
		afx_msg void	OnPrintMenuClicked() ;
		afx_msg void	OnPreViewMenuClicked() ;
		afx_msg void	OnCloseMenuClicked() ;

		/********* �� �� ***********/
		afx_msg void	OnSequenceMenuClicked() ;
		afx_msg void	OnBeforeRepeatMenuClicked() ;
		afx_msg void	OnAfterRepeatMenuClicked() ;
		afx_msg void	OnSelectionMenuClicked() ;
		afx_msg void	OnSwitchCaseMenuClicked() ;
		afx_msg void	OnArrowMenuClicked() ;

		/********* Ư������ ***********/
		afx_msg void	OnNotEqualMenuClicked() ;
		afx_msg void	OnBetterThanMenuClicked() ;
		afx_msg void	OnLesserThanMenuClicked() ;

		/********* ���� ***********/
		afx_msg void	OnHelpInFoButtonClicked() ;

		/********* ���ư Ŭ�� �޴� *********/
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