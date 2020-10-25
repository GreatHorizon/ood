#pragma once
#include "AbstractCommand.h"
class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(int& width, int& height, int newWidth, int newHeight);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	int& m_width;
	int& m_height;
	int m_newHeight;
	int m_newWidth;
};

