#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

int main()
{
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    cout << "Hello world!" << endl;
    return 0;
}
