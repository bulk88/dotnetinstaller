#include "StdAfx.h"
#include "ComponentsList.h"

CComponentsList::CComponentsList(void)
{
}

CComponentsList::~CComponentsList(void)
{
}

IMPLEMENT_DYNAMIC(CComponentsList, CCheckListBox)

BEGIN_MESSAGE_MAP(CComponentsList, CCheckListBox) 
END_MESSAGE_MAP()

void CComponentsList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{ 
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	if (((LONG)(lpDrawItemStruct->itemID) >= 0) &&
		(lpDrawItemStruct->itemAction & (ODA_DRAWENTIRE | ODA_SELECT)))
	{
		int cyItem = GetItemHeight(lpDrawItemStruct->itemID);
		BOOL fDisabled = !IsWindowEnabled() || !IsEnabled(lpDrawItemStruct->itemID);

		COLORREF newTextColor = fDisabled ?
			RGB(0, 0, 0) : GetSysColor(COLOR_WINDOWTEXT);  // light gray
		COLORREF oldTextColor = pDC->SetTextColor(newTextColor);

		COLORREF newBkColor = GetSysColor(COLOR_WINDOW);
		COLORREF oldBkColor = pDC->SetBkColor(newBkColor);

		if (newTextColor == newBkColor)
			newTextColor = RGB(0xC0, 0xC0, 0xC0);   // dark gray

		if (!fDisabled && ((lpDrawItemStruct->itemState & ODS_SELECTED) != 0))
		{
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
			pDC->SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
		}

		if (m_cyText == 0)
			VERIFY(cyItem >= CalcMinimumItemHeight());

		CString strText;
		GetText(lpDrawItemStruct->itemID, strText);

		pDC->ExtTextOut(lpDrawItemStruct->rcItem.left + 5,
			lpDrawItemStruct->rcItem.top + max(0, (cyItem - m_cyText) / 2),
			ETO_OPAQUE, &(lpDrawItemStruct->rcItem), strText, strText.GetLength(), NULL);

		int nCheck = GetCheck(lpDrawItemStruct->itemID);
		if (fDisabled && nCheck == 0)
		{
			CRect checkbox(0, lpDrawItemStruct->rcItem.top, lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.bottom);
			COLORREF newBkColor = GetSysColor(COLOR_WINDOW);
			CBrush brush(newBkColor);
			pDC->FillRect(& checkbox, & brush);
		}

		pDC->SetTextColor(oldTextColor);
		pDC->SetBkColor(oldBkColor);
	}

	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) != 0)
		pDC->DrawFocusRect(&(lpDrawItemStruct->rcItem));
}

void CComponentsList::PreDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CCheckListBox::PreDrawItem(lpDrawItemStruct);
}
