// PreViewDlg.h
#ifndef _PREVIEWDLG_H
#define _PREVIEWDLG_H

#include <afxwin.h>

#include "resource.h"

#define PREVIEW_WIDTH 595
#define PREVIEW_HEIGHT 842
class CDC;

class PreViewDlg : public CDialog {
public:
	enum { IDD = IDD_PREVIEW };

public:
	PreViewDlg(CWnd *parent = NULL);
	~PreViewDlg();
	void DisplayPreView(CDC *memdc);
	
protected:
	//����Ű (Ȯ��+ ���-)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//��ũ��
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	
	afx_msg void OnPrint();
	afx_msg void OnClose();
	afx_msg void OnEnd();

	afx_msg void OnUpSize();
	afx_msg void OnDownSize();

	afx_msg void OnPreView200();
	afx_msg void OnPreView150();
	afx_msg void OnPreView100();
	afx_msg void OnPreView75();
	afx_msg void OnPreView50();
	afx_msg void OnPreView25();
	
	DECLARE_MESSAGE_MAP()

private:
	//����ũ��
	int preViewWidth;	
	int preViewHeight;	

	//������ Ŭ���̾�Ʈ ���� ũ��
	CRect preViewWindow;	
	
	//��ũ�ѿ� ���� ��� ����
	int xPos;	
	int yPos;
	int xMax;
	int yMax;
};

#endif // _PREVIEWDLG_H