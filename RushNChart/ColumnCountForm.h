#ifndef _COLUMNCOUNTFORM_H
#define _COLUMNCOUNTFORM_H

#include "resource.h"
#include <afxwin.h>

class ColumnCountForm : public CDialog {
public :
	enum { IDD = IDM_SWITCH_CASE } ;
public : 
	ColumnCountForm ( CWnd *parent = NULL ) ;
	virtual BOOL OnInitDialog ( ) ;
	virtual BOOL PreTranslateMessage(MSG* pMsg) ;
protected :
	afx_msg void OnOkButtonClicked () ;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags ) ;
	afx_msg void OnClose( ) ;
	DECLARE_MESSAGE_MAP()
};
#endif //_MULTIPLESELECTIONFORM_H