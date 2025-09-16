#include "StdAfx.h"

namespace ui
{

PlaceHolder::PlaceHolder() :
	m_pWindow(nullptr),
	m_sName(),
	m_cxyFixed(DUI_LENGTH_STRETCH, DUI_LENGTH_STRETCH),
	m_cxyMin(-1, -1),
	m_cxyMax(9999999, 9999999),
	m_pParent(nullptr),
	m_rcItem(),
	m_horAlignType(kHorAlignLeft),
	m_verAlignType(kVerAlignTop),
	m_bInited(false),
	m_bFloat(false),
	m_bReEstimateSize(true),
	m_bVisible(true),
	m_bInternVisible(true),
	m_bIsArranged(true)
{

}

PlaceHolder::~PlaceHolder()
{
	
}

std::wstring PlaceHolder::GetName() const
{
	return m_sName;
}

std::string PlaceHolder::GetUTF8Name() const
{
	std::string strOut;
	StringHelper::UnicodeToMBCS(m_sName, strOut, CP_UTF8);
	return strOut;
}

void PlaceHolder::SetName(const std::wstring& strName)
{
	m_sName = strName;
}

void PlaceHolder::SetUTF8Name(const std::string& strName)
{
	std::wstring strOut;
	StringHelper::MBCSToUnicode(strName, strOut, CP_UTF8);
	m_sName = strOut;
}

Window* PlaceHolder::GetWindow() const
{
	return m_pWindow;
}

void PlaceHolder::SetWindow(Window* pManager, Box* pParent, bool bInit)
{
	m_pWindow = pManager;
	m_pParent = pParent;
	if (bInit && m_pParent && !IsInited())
		Init();
}

void PlaceHolder::SetWindow(Window* pManager)
{
	m_pWindow = pManager;
}

bool PlaceHolder::IsInited(void) const
{
	return m_bInited;
}

void PlaceHolder::Init()
{
	if (IsInited())
		return;

	m_bInited = true;
	DoInit();
}

void PlaceHolder::DoInit()
{

}

bool PlaceHolder::IsVisible() const
{
	return m_bVisible && m_bInternVisible;
}

bool PlaceHolder::IsInternVisible() const
{
	return m_bInternVisible;
}

bool PlaceHolder::IsFloat() const
{
	return m_bFloat;
}

void PlaceHolder::SetFloat(bool bFloat)
{
	if (m_bFloat == bFloat) return;

	m_bFloat = bFloat;
	ArrangeAncestor();
}

int PlaceHolder::GetFixedWidth() const
{
	return m_cxyFixed.cx;
}

void PlaceHolder::SetFixedWidth(int cx, bool bArrange, bool bNeedDpiScale)
{
	if (cx < 0 && cx != DUI_LENGTH_STRETCH && cx != DUI_LENGTH_AUTO) {
		ASSERT(FALSE);
		return;
	}

	if (bNeedDpiScale && cx > 0)
		DpiManager::GetInstance()->ScaleInt(cx);

	if (m_cxyFixed.cx != cx)
	{
		m_cxyFixed.cx = cx;

		if (bArrange) {
			ArrangeAncestor();
		}
		else {
			m_bReEstimateSize = true;
		}
	}
	//if( !m_bFloat ) ArrangeAncestor();
	//else Arrange();
}

int PlaceHolder::GetFixedHeight() const
{
	return m_cxyFixed.cy;
}

void PlaceHolder::SetFixedHeight(int cy, bool bNeedDpiScale)
{
	if (cy < 0 && cy != DUI_LENGTH_STRETCH && cy != DUI_LENGTH_AUTO) {
		ASSERT(FALSE);
		return;
	}

	if (bNeedDpiScale && cy > 0)
		DpiManager::GetInstance()->ScaleInt(cy);

	if (m_cxyFixed.cy != cy)
	{
		m_cxyFixed.cy = cy;

		ArrangeAncestor();
	}
	//if( !m_bFloat ) ArrangeAncestor();
	//else Arrange();
}

int PlaceHolder::GetMinWidth() const
{
	return m_cxyMin.cx;
}

void PlaceHolder::SetMinWidth(int cx)
{
	DpiManager::GetInstance()->ScaleInt(cx);
	if (m_cxyMin.cx == cx) return;

	if (cx < 0) return;
	m_cxyMin.cx = cx;
	if (!m_bFloat) ArrangeAncestor();
	else Arrange();
}

int PlaceHolder::GetMaxWidth() const
{
	return m_cxyMax.cx;
}

void PlaceHolder::SetMaxWidth(int cx)
{
	DpiManager::GetInstance()->ScaleInt(cx);
	if (m_cxyMax.cx == cx) return;

	m_cxyMax.cx = cx;
	if (!m_bFloat) ArrangeAncestor();
	else Arrange();
}

int PlaceHolder::GetMinHeight() const
{
	return m_cxyMin.cy;
}

void PlaceHolder::SetMinHeight(int cy)
{
	DpiManager::GetInstance()->ScaleInt(cy);
	if (m_cxyMin.cy == cy) return;

	if (cy < 0) return;
	m_cxyMin.cy = cy;
	if (!m_bFloat) ArrangeAncestor();
	else Arrange();
}

int PlaceHolder::GetMaxHeight() const
{
	return m_cxyMax.cy;
}

void PlaceHolder::SetMaxHeight(int cy)
{
	DpiManager::GetInstance()->ScaleInt(cy);
	if (m_cxyMax.cy == cy) return;

	m_cxyMax.cy = cy;
	if (!m_bFloat) ArrangeAncestor();
	else Arrange();
}

int PlaceHolder::GetWidth() const
{
	return m_rcItem.right - m_rcItem.left;
}

int PlaceHolder::GetHeight() const
{
	return m_rcItem.bottom - m_rcItem.top;
}

ui::HorAlignType PlaceHolder::GetHorAlignType() const
{
	return m_horAlignType;
}

void PlaceHolder::SetHorAlignType(HorAlignType horAlignType)
{
	m_horAlignType = horAlignType;
}

ui::VerAlignType PlaceHolder::GetVerAlignType() const
{
	return m_verAlignType;
}

void PlaceHolder::SetVerAlignType(VerAlignType verAlignType)
{
	m_verAlignType = verAlignType;
}

bool PlaceHolder::IsReEstimateSize() const
{
	return m_bReEstimateSize;
}

void PlaceHolder::SetReEstimateSize(bool bReEstimateSize)
{
	m_bReEstimateSize = bReEstimateSize;
}

CSize PlaceHolder::EstimateSize(CSize szAvailable)
{
	return m_cxyFixed;
}

UiRect PlaceHolder::GetPos(bool bContainShadow) const
{
	return m_rcItem;
}

void PlaceHolder::SetPos(UiRect rc)
{
	m_rcItem = rc;
}

void PlaceHolder::Arrange()
{
	if (GetFixedWidth() == DUI_LENGTH_AUTO || GetFixedHeight() == DUI_LENGTH_AUTO)
	{
		ArrangeAncestor();
	}
	else
	{
		ArrangeSelf();
	}
}

void PlaceHolder::ArrangeAncestor()
{
	m_bReEstimateSize = true;
	if (!m_pWindow || !m_pWindow->GetRoot())
	{
		if (GetParent()) {
			GetParent()->ArrangeSelf();
		}
		else {
			ArrangeSelf();
		}
	}
	else
	{
		Control* parent = GetParent();
		while (parent && (parent->GetFixedWidth() == DUI_LENGTH_AUTO || parent->GetFixedHeight() == DUI_LENGTH_AUTO))
		{
			parent->SetReEstimateSize(true);
			parent = parent->GetParent();
		}
		if (parent)
		{
			parent->ArrangeSelf();
		}
		else	//˵��root����AutoAdjustSize����
		{
			m_pWindow->GetRoot()->ArrangeSelf();
		}
	}

}

bool PlaceHolder::IsArranged() const
{
	return m_bIsArranged;
}

void PlaceHolder::ArrangeSelf()
{
	if (!IsVisible()) return;
	m_bReEstimateSize = true;
	m_bIsArranged = true;
	Invalidate();

	if (m_pWindow != NULL) m_pWindow->SetArrange(true);
}

void PlaceHolder::Invalidate() const
{
	if (!IsVisible()) return;

	UiRect rcInvalidate = GetPosWithScrollOffset();
	if (m_pWindow != NULL) m_pWindow->Invalidate(rcInvalidate);
}

UiRect PlaceHolder::GetPosWithScrollOffset() const
{
	UiRect pos = GetPos();
	CPoint offset = GetScrollOffset();
	pos.Offset(-offset.x, -offset.y);
	return pos;
}

CPoint PlaceHolder::GetScrollOffset() const
{
	CPoint scrollPos;
	Control* parent = GetParent();
	ListBox* lbParent = dynamic_cast<ListBox*>(parent);
	if (lbParent && (lbParent->IsVScrollBarValid() || lbParent->IsHScrollBarValid()) && IsFloat()) {
		return scrollPos;
	}
	while (parent && (!dynamic_cast<ListBox*>(parent) || !(dynamic_cast<ListBox*>(parent)->IsHScrollBarValid() || dynamic_cast<ListBox*>(parent)->IsVScrollBarValid())))
	{
		parent = parent->GetParent();
	}

	if (parent) {
		//˵���ؼ���Listbox�ڲ�
		ListBox* listbox = (ListBox*)parent;
		scrollPos.x = listbox->GetScrollPos().cx;
		scrollPos.y = listbox->GetScrollPos().cy;
	}

	return scrollPos;
}

bool IsChild(PlaceHolder* pAncestor, PlaceHolder* pControl)
{
	while (pControl && pControl != pAncestor)
	{
		pControl = pControl->GetParent();
	}

	return pControl != nullptr;
}


}