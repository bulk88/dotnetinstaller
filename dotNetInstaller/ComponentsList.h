#pragma once

class CComponentsList :
	public CCheckListBox
{
	DECLARE_DYNAMIC(CComponentsList);
protected: 
	void PreDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct); 
	DECLARE_MESSAGE_MAP();
public:
	CComponentsList(void);
	~CComponentsList(void);
};
