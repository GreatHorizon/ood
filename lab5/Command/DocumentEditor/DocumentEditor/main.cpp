#include "stdafx.h"
#include "Editor.h"
#include "Document.h"

int main()
{
	CEditor editor(std::cin, std::cout);
	editor.Start();
	return 0;
}
