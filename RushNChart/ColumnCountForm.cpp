#include "ColumnCountForm.h"
#include "RushNChart.h"
#include <sstream>

BEGIN_MESSAGE_MAP( ColumnCountForm, CDialog )
	ON_BN_CLICKED( IDC_BUTTON_OK, OnOkButtonClicked )
	//ON_WM_KEYDOWN( )
	ON_WM_CLOSE( )
END_MESSAGE_MAP( )

ColumnCountForm::ColumnCountForm ( CWnd *parent )
	:CDialog ( ColumnCountForm::IDD, parent )
{
}

BOOL ColumnCountForm::OnInitDialog()
{
	CDialog::OnInitDialog() ;

	GotoDlgCtrl( GetDlgItem( IDC_EDIT_COLUMNCOUNT ) );

	return FALSE;
}


void ColumnCountForm::OnOkButtonClicked( ){
	CString columnCount;

	this->GetDlgItem( IDC_EDIT_COLUMNCOUNT )->GetWindowText( columnCount );
	
	RushNChart *rushNChart = (RushNChart*)CWnd::FindWindow( NULL, TEXT("Rush&Chart") );
	
	//_ttoi´Â CString->int ·Î ¹Ù²ãÁÜ 
	rushNChart->columnCount = _ttoi( columnCount ) ;

	/*
	if ( rushNChart->columnCount >5 ) {
		rushNChart->columnCount = 5 ;
	}
	//*/

	OnOK( );
}

BOOL ColumnCountForm::PreTranslateMessage(MSG* pMsg) {
	if(pMsg->message == WM_KEYDOWN){
		 if(pMsg->wParam == VK_RETURN){
				CString columnCount;

				this->GetDlgItem( IDC_EDIT_COLUMNCOUNT )->GetWindowText( columnCount );
	
				RushNChart *rushNChart = (RushNChart*)CWnd::FindWindow( NULL, TEXT("Rush&Chart") );
	
				//_ttoi´Â CString->int ·Î ¹Ù²ãÁÜ 
				rushNChart->columnCount = _ttoi( columnCount ) ;
				OnOK( );
		 }
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void ColumnCountForm::OnClose( ){
	OnOK( );
}
