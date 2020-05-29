#if 1
#include <iostream>
#include <kvs/StructuredVolumeObject>
#include <kvs/StructuredVolumeImporter>
#include <kvs/PolygonObject>
#include <kvs/PolygonRenderer>
#include <kvs/Isosurface>
#include <kvs/HydrogenVolumeData>
#include <kvs/RayCastingRenderer>
#include <kvs/TimerEventListener>
#include <KVS.glfw/Lib/Application.h>
#include <KVS.glfw/Lib/Screen.h>
#include <KVS.glfw/Lib/Timer.h>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>

#include <kvs/KeyPressEventListener>
class KeyPressEvent : public kvs::KeyPressEventListener
{
    void update( kvs::KeyEvent* event )
    {
        switch ( event->key() )
        {
        case kvs::Key::One:
            screen()->showFullScreen();
            break;
        case kvs::Key::Two:
            screen()->showNormal();
            break;
        default:
            break;
        }
    }
};

class TimerEvent : public kvs::TimerEventListener
{
    void update( kvs::TimeEvent* event )
    {
        std::cout << "TimerEvent::update()" << std::endl;
    }
};

int main( int argc, char** argv )
{
#if 1
    kvs::glfw::Application app( argc, argv );
    kvs::glfw::Screen screen1( &app );
    kvs::glfw::Screen screen2( &app );
#else
    kvs::glut::Application app( argc, argv );
    kvs::glut::Screen screen1( &app );
    kvs::glut::Screen screen2( &app );
#endif
    screen1.setTitle("A");
    screen2.setTitle("B");

    kvs::StructuredVolumeObject* volume = new kvs::HydrogenVolumeData( kvs::Vec3u( 64, 64, 64 ) );
    volume->updateMinMaxValues();

    {
        screen1.registerObject( volume, new kvs::glsl::RayCastingRenderer );
///        screen1.registerObject( volume, new kvs::RayCastingRenderer );
    }

    {
        const double i = ( volume->maxValue() + volume->minValue() ) * 0.5;
        const kvs::PolygonObject::NormalType n = kvs::PolygonObject::VertexNormal;
        const bool d = false;
        const kvs::TransferFunction t( 256 );
        kvs::PolygonObject* object = new kvs::Isosurface( volume, i, n, d, t );
        kvs::glsl::PolygonRenderer* renderer = new kvs::glsl::PolygonRenderer();
        screen2.registerObject( object, renderer );
//        screen2.registerObject( object );
    }

    // Timer.
//    TimerEvent timer_event;
//    int msec = 1000;
//    kvs::glfw::Timer timer( msec );
//    screen1.addTimerEvent( &timer_event, &timer );

    KeyPressEvent key_event1;
    KeyPressEvent key_event2;
    screen1.addEvent( &key_event1 );
    screen2.addEvent( &key_event2 );

    screen1.show();
    screen2.show();

    return app.run();
}

#else
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
#endif
