// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>

#include <glfw3.h>
#include <string>

class Display
{
public:
	Display();
	Display(int width, int height, std::string title);
	~Display() {};

	void Setting();
	bool CheckCreateWindow();
	bool CheckCGlewInit();

	void Clear();


	GLFWwindow* window;
};