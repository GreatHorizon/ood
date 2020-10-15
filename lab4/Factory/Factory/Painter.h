#pragma once
#include "PictureDraft.h"
#include "ICanvas.h"

class CPainter
{
public:
	void DrawPicture(CPictureDraft& draft, ICanvas& canvas) const;
};