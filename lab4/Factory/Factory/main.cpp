#include "Designer.h"
#include "ShapeFactory.h"
#include "Painter.h"

void ShowHint()
{
	std::cout << "Commands:\n"
		<< "ellipse <center point X> <center point Y> <vertical radius> <horizontal radius> <fill color>\n"
		<< "rectangle <left top point X> <left top point Y> <width> <height> <color>\n"
		<< "triangle <vertex1 X> <vertex1 Y> <vertex2 X> <vertex2 Y> <vertex3 X> <vertex3 Y> <color>\n"
		<< "regularPolygon <center point X> <center poing Y> <radius> <color>\n"
		<< "<color> could be: green, red, blue, yellow, black, pink\n\n";
}

int main()
{
	ShowHint();
	CShapeFactory factory;
	CDesigner designer(factory);
	CPainter painter;
	CPictureDraft draft = designer.CreateDraft(std::cin);


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
		painter.DrawPicture(draft, canvas);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}