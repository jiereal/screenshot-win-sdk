#ifndef UI_UTILS_SHADOW_H_
#define UI_UTILS_SHADOW_H_

#pragma once

namespace ui 
{

class Box;
class Shadow
{
public:
	Shadow();

	void SetShadowAttached(bool bShadowAttached);
	bool IsShadowAttached() const;

	bool IsUserDefaultImage() const;

	void SetShadowCorner(const UiRect &rect);
	UiRect GetShadowCorner() const;

	void SetShadowImage(const std::wstring &image);
	std::wstring GetShadowImage() const;

	Box* AttachShadow(Box* pRoot);
	void MaximizedOrRestored(bool isMaximized);

	Control* GetRoot();
	void ClearImageCache();
private:
	void SetPadding();

	void UpdateShadow(void);
private:
	bool m_bShadowAttached;
	bool m_bUseDefaultImage;
	std::wstring m_strImage;
	UiRect m_rcShadowCorner;
	UiRect m_rcShadowCornerBackup;

	Box* m_pRoot;
};

}

#endif // UI_UTILS_SHADOW_H_