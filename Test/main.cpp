/*#include <iostream>
#include <GL/glew.h>

#include "Display.h"
#include "Mesh.h"
#include "Shader.h"

using namespace std;

int main()
{
    Display display(800, 600, "Hello World!");


    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5, 0)),
        Vertex(glm::vec3(0, 0.5, 0)),
        Vertex(glm::vec3(0.5, -0.5, 0)),
    };

    Mesh mesh(vertices, 3);

    Shader shader("./res/basicShader");

    while(!display.IsClosed()) {

        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        shader.Bind();
        mesh.Draw();

        display.Update();
    }

    return 0;
}
*/

/*
 * (c) Copyright 1995-1999, Igor Tarasov
 * FidoNet: 2:5020/370.2 620.20 1103.5
 * Inet: itarasov@rtuis.miem.edu.ru
 * Phone: (095)942-50-97
 */

