#ifndef UI_CORE_CHILDBOX_H_
#define UI_CORE_CHILDBOX_H_

#pragma once

namespace ui
{

class UILIB_API ChildBox : public Box
{
public:
	ChildBox();

	void Init();
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	void SetChildLayoutXML(std::wstring strXML);
	std::wstring GetChildLayoutXML();

	void SetCreateControlCallback(const CreateControlCallback& fnCallback);

private:
	std::wstring m_strXMLFile;

	CreateControlCallback m_createControlCallback;
};

} // namespace ui
#endif // UI_CORE_CHILDBOX_H_
