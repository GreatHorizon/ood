#include "Slide.h"
#include "Canvas.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Group.h"
#include "../lib/include/GLFW/glfw3.h"


int DrawSlide(std::shared_ptr<ISlide> slide)
{
	if (!glfwInit()) {
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(940, 780, "Shapes", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return 1;
	}

	CCanvas canvas(window);

	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);
		slide->Draw(canvas);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

std::shared_ptr<ISlide> CreateSlideWithPicture()
{
	auto slide = std::make_shared<CSlide>(940, 780);
	auto truck = std::make_shared<CGroup>();

	auto body = std::make_shared<CRectangle>(CPoint(0.2, 0.3), 0.4, 0.15);
	auto frame = std::make_shared<CRectangle>(CPoint(0.2, 0.15), 0.6, 0.1);
	auto cabin = std::make_shared<CRectangle>(CPoint(0.61, 0.32), 0.19, 0.17);
	auto firstWheel = std::make_shared<CEllipse>(CPoint(0.33, 0.061), 0.06, 0.06);
	auto secondWheel = std::make_shared<CEllipse>(CPoint(0.68, 0.061), 0.06, 0.06);

	cabin->GetFillStyle()->SetColor(0x4b4b4bFF);
	firstWheel->GetFillStyle()->SetColor(0x000000FF);
	secondWheel->GetFillStyle()->SetColor(0x000000FF);

	firstWheel->GetOutlineStyle()->Enable(true);
	firstWheel->GetOutlineStyle()->SetColor(0x7e5429ff);

	secondWheel->GetOutlineStyle()->Enable(true);
	secondWheel->GetOutlineStyle()->SetColor(0x7e5429ff);

	body->GetFillStyle()->SetColor(0xFF0000FF);
	frame->GetFillStyle()->SetColor(0x9abcdeFF);

	truck->InsertShape(body);
	truck->InsertShape(frame);
	truck->InsertShape(cabin);
	truck->InsertShape(firstWheel);
	truck->InsertShape(secondWheel);

	auto ground = std::make_shared<CRectangle>(CPoint(-1, 0), 2, 1);
	ground->GetFillStyle()->SetColor(0x4b4b4bFF);

	auto sandHeap = std::make_shared<CTriangle>(CPoint(0.1, 0), CPoint(-0.3, 0), CPoint(-0.1, 0.2));
	sandHeap->GetFillStyle()->SetColor(0xdebd1379);
	auto sun = std::make_shared<CEllipse>(CPoint(-0.7, 0.5), 0.1, 0.12);
	sun->GetFillStyle()->SetColor(0xeadf18ff);

	slide->InsertShape(truck);
	slide->InsertShape(ground);
	slide->InsertShape(sandHeap);
	slide->InsertShape(sun);

	return slide;
}

int main()
{
	auto slide = CreateSlideWithPicture();
	DrawSlide(slide);
	return 0;
}