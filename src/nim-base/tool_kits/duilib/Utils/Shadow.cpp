#include "StdAfx.h"

namespace ui 
{

Shadow::Shadow() :
	m_rcShadowCorner(14, 14, 14, 14),
	m_bShadowAttached(true),
	m_bUseDefaultImage(true),
	m_strImage(L"file='../public/bk/bk_shadow.png' corner='30,30,30,30'"),
	m_pRoot(nullptr)
{
	DpiManager::GetInstance()->ScaleRect(m_rcShadowCorner);
	m_rcShadowCornerBackup = m_rcShadowCorner;
}

void Shadow::SetShadowAttached(bool bShadowAttached)
{
	m_bShadowAttached = bShadowAttached;

	UpdateShadow();
}

bool Shadow::IsShadowAttached() const
{
	return m_bShadowAttached;
}

bool Shadow::IsUserDefaultImage() const
{
	return m_bUseDefaultImage;
}

void Shadow::SetShadowImage(const std::wstring &image)
{
	m_strImage = image;
	m_bUseDefaultImage = false;

	UpdateShadow();
}

std::wstring Shadow::GetShadowImage() const
{
	return m_strImage;
}

void Shadow::SetShadowCorner(const UiRect &rect)
{
	m_rcShadowCorner = rect;
	DpiManager::GetInstance()->ScaleRect(m_rcShadowCorner);
	m_rcShadowCornerBackup = m_rcShadowCorner;
	UpdateShadow();
}

UiRect Shadow::GetShadowCorner() const
{
	if (m_bShadowAttached) {
		return m_rcShadowCorner;
	}
	else {
		return UiRect(0, 0, 0, 0);
	}
}

Box*Shadow::AttachShadow(Box* pRoot)
{
	if (!m_bShadowAttached)
		return pRoot;

	m_pRoot = new Box();
	SetPadding();

	int rootWidth = pRoot->GetFixedWidth();
	if (rootWidth > 0) {
		rootWidth += m_rcShadowCorner.left + m_rcShadowCorner.right;
	}
	m_pRoot->SetFixedWidth(rootWidth, true, false);

	int rootHeight = pRoot->GetFixedHeight();
	if (rootHeight > 0) {
		rootHeight += m_rcShadowCorner.top + m_rcShadowCorner.bottom;
	}
	m_pRoot->SetFixedHeight(rootHeight, false);

	if (m_bUseDefaultImage)
	{
		CSize size(3, 3);
		pRoot->SetBorderRound(size);
	}

	m_pRoot->Add(pRoot);
	m_pRoot->SetBkImage(m_strImage);

	return m_pRoot;
}

void Shadow::MaximizedOrRestored(bool isMaximized)
{
	if (!m_bShadowAttached)
		return;

	if (isMaximized && m_pRoot) {
		m_rcShadowCorner = UiRect(0, 0, 0, 0);
		SetPadding();

		if (m_bUseDefaultImage)
		{
			Control* control = m_pRoot->GetItemAt(0);
			CSize size(0, 0);
			control->SetBorderRound(size);
		}
	}
	else if (!isMaximized && m_pRoot) {
		m_rcShadowCorner = m_rcShadowCornerBackup;
		SetPadding();

		if (m_bUseDefaultImage)
		{
			Control* control = m_pRoot->GetItemAt(0);
			CSize size(3, 3);
			control->SetBorderRound(size);
		}
	}
}

ui::Control* Shadow::GetRoot()
{
	return m_pRoot;
}

void Shadow::ClearImageCache()
{
	m_pRoot->ClearImageCache();
}

void Shadow::SetPadding()
{
	UiRect rcPadding;
	int nScaleFactor = DpiManager::GetInstance()->GetScale();
	int width = MulDiv(m_rcShadowCorner.right - m_rcShadowCorner.left, 100, nScaleFactor);
	int height = MulDiv(m_rcShadowCorner.bottom - m_rcShadowCorner.top, 100, nScaleFactor);
	rcPadding.left = MulDiv(m_rcShadowCorner.left, 100, nScaleFactor);
	rcPadding.top = MulDiv(m_rcShadowCorner.top, 100, nScaleFactor);
	rcPadding.right = rcPadding.left + width;
	rcPadding.bottom = rcPadding.top + height;

	m_pRoot->GetLayout()->SetPadding(rcPadding);
}

void Shadow::UpdateShadow(void)
{
	if (NULL == m_pRoot)
		return;

	if (m_bShadowAttached)
	{
		m_pRoot->GetLayout()->SetPadding(m_rcShadowCorner);

		m_pRoot->SetBkImage(m_strImage);

		if (m_bUseDefaultImage)
		{
			Control* control = m_pRoot->GetItemAt(0);
			CSize size(3, 3);
			control->SetBorderRound(size);
		}
	}

#if 0
	else
	{
		
		m_pRoot->GetLayout()->SetPadding(UiRect(0, 0, 0, 0));

		Control* control = m_pRoot->GetItemAt(0);
		CSize size(0, 0);
		control->SetBorderRound(size);
	}
#endif

}

}