#pragma once
#include <iosfwd>
#include <iostream>

class CPictureDraft;
class IShapeFactory;

class CDesigner
{
public:
	CDesigner(IShapeFactory& factory);
	~CDesigner();
	CPictureDraft CreateDraft(std::istream& inputData);
private:
	IShapeFactory& m_factory;
};