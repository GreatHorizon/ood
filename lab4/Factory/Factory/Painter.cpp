#include "Painter.h"

void CPainter::DrawPicture(CPictureDraft& draft, ICanvas& canvas) const
{
	for (auto it = draft.begin(); it < draft.end(); it++)
	{
		it->Draw(canvas);
	}
}
