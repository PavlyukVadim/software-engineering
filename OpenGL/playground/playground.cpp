// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <common/shader.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/texture.hpp>

#include "display.h"

vec3 gPosition1(-1.5f, 0.0f, 0.0f);
vec3 gOrientation1;
 
vec3 gPosition2( 1.5f, 0.0f, 0.0f);
quat gOrientation2;

int main( void )
{
	fprintf(stderr, "Failed to initialize GLEW\n");

	// Initialise GLFW
	if( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	// Open a window and create its OpenGL context
	Display display(1024, 768, "UFO");
	window = display.window;
	
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	   // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	
	// Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    //glfwSetCursorPos(window, 1024/2, 768/2);


	// Create and compile our GLSL program from the shaders
	//GLuint programID = LoadShaders( "VertexShader.vs", "FragmentShader.fs");
    GLuint programID = LoadShaders( "TransformVertexShader.vs", "TextureFragmentShader.fs" );
    // Create and compile our GLSL program from the shaders
	GLuint programTriangleID = LoadShaders( "TransformVertexShader.vs", "TextureFragmentShader.fs" );
	// Get a handle for our "MVP" uniform
	GLuint MatrixTriangleID = glGetUniformLocation(programTriangleID, "MVP");

	static const GLfloat g_vertex_buffer_data[] = { 
	   -200, -200, 0,
	    200, -200, 0,
	   -200,  200, 0,

	    200,  200, 0,
	   -200,  200, 0,
	    200, -200, 0
	};


    const GLsizeiptr texCoordSize = 6 * 2 * sizeof(GLfloat);
    const GLfloat texCoordData[] =
    {
         -200, -200,
	    200, -200, 
	   -200,  200, 

	    200,  200, 
	   -200,  200, 
	    200, -200
    };

	GLuint vertexbuffertr;
	glGenBuffers(1, &vertexbuffertr);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffertr);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint m_texCoordBuffer;
	glGenBuffers(1, &m_texCoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, texCoordSize, texCoordData, GL_STATIC_DRAW);


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 ProjectionBackground = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	glm::mat4 ViewBackground = glm::lookAt(
								glm::vec3(0,0,100), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 ModelBackground = glm::mat4(1.0f) * scale(mat4(), vec3(10.0f, 10.0f, 10.0f));;
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVPBackground  = ProjectionBackground * ViewBackground * ModelBackground; // Remember, matrix multiplication is the other way around


	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Load the texture
	
	//GLuint Texture = loadBMP_custom("texture.bmp");
	GLuint Texture = loadDDS("uvmap.DDS");

	GLuint TextureBackground = loadBMP_custom("space.bmp");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
	GLuint TextureBackgroundID  = glGetUniformLocation(programTriangleID, "myTextureSample");
	
	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("ufo.obj", vertices, uvs, normals);

	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);



	// For speed computation
	double lastTime = glfwGetTime();
	double lastFrameTime = lastTime;
	int nbFrames = 0;
	bool reverse = false;

	do {

		// Measure speed
		double currentTime = glfwGetTime();
		float deltaTime = (float)(currentTime - lastFrameTime); 
		lastFrameTime = currentTime;
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0/double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Clear the screen
		display.Clear();




		//-------Background



		// Use our shader
		glUseProgram(programTriangleID);
		
		

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputsB();
		glm::mat4 ProjectionMatrixB = getProjectionMatrixB();
		glm::mat4 ViewMatrixB = getViewMatrixB();
		glm::mat4 ModelMatrixB = glm::mat4(1.0f) * scale(mat4(), vec3(100.0f, 100.0f, 100.0f));;
		MVPBackground = ProjectionMatrixB * ViewMatrixB * ModelMatrixB;		
		glUniformMatrix4fv(MatrixTriangleID, 1, GL_FALSE, &MVPBackground[0][0]);



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureBackground);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureBackgroundID, 0);


		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffertr);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);


		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

	



		//-------UFO



		// Use our shader
		glUseProgram(programID);

		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);


		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);


		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);



		{ // Euler
			// As an example, rotate arount the vertical axis at 180°/sec
			gOrientation1.y += 3.14159f/2.0f * deltaTime;
			
			if (!reverse) {
				gOrientation1.z += (3.14159f/2.0f * deltaTime) / 10;	
				if(gOrientation1.z >= 3.14159f/8.0f) {
					reverse = true;
				}
			}
			else {
				gOrientation1.z -= (3.14159f/2.0f * deltaTime) / 10;	
				if(gOrientation1.z <= -3.14159f/8.0f) {
					reverse = false;
				}	
			}
			
			

 
			// Build the model matrix
			glm::mat4 RotationMatrix = eulerAngleYXZ(gOrientation1.y, gOrientation1.x, gOrientation1.z);
			glm::mat4 TranslationMatrix = translate(mat4(), gPosition1); // A bit to the left
			glm::mat4 ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
 
			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
 
			// Send our transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		}


		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}