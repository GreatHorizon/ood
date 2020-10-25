#include "stdafx.h"
#include "Editor.h"
#include "Document.h"

int main()
{
	auto document = std::make_shared<CDocument>();
	CEditor editor(std::cin, std::cout);
	editor.Start();
	return 0;
}
