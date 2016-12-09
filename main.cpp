#include <iostream>
#include <GL/glew.h>

#include "Display.h"
#include "Mesh.h"
#include "Shader.h"

using namespace std;

int main()
{
    Display display(800, 600, "Hello World!");

    Shader shader("./res/basicShader");
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5, 0)),
        Vertex(glm::vec3(0, 0.5, 0)),
        Vertex(glm::vec3(0.5, -0.5, 0))
    };

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]) );

    while(!display.IsClosed()) {
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();

        mesh.Draw();

        display.Update();
    }

    return 0;
}
