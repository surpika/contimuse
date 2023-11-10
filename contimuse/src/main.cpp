#include <GLFW/glfw3.h>
#include "Graph.h"
#include "Waveform.h"
#include "PointArray.h"
#include "globals.h"
#include <iostream>

//declare and initialize a Graph object
Graph graph;
//declare and initialize a Waveform object
Waveform w;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        xpos = convertMousePositionX(xpos);
        ypos = convertMousePositionY(ypos);
        graph.addPoint(xpos, ypos);
        std::cout << xpos << ", " << ypos << std::endl << std::endl;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        graph.dump();
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {
        w.computeWaveform(graph.pointArray());
        w.writeToWav();
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
    {
        w.dump();
    }
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Contimuse Pre-Alpha v1.0", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //set the background color to dark gray
    glClearColor(GLclampf(0.1), GLclampf(0.1), GLclampf(0.1), 1);
    //set a mouse callback
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    //set a keyboard callback
    glfwSetKeyCallback(window, key_callback);

    glEnableClientState(GL_VERTEX_ARRAY);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        graph.repaint();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glDisableClientState(GL_VERTEX_ARRAY);

    glfwTerminate();
    return 0;
}