#include "Application.h"
#include "GLFW.h"
#include "ScreenBase.h"
#include <kvs/Message>
#include <cstdlib>

#if defined( KVS_GL_HAS_LAYER_BACKED_VIEW )
#include <objc/message.h>
#define GLFW_EXPOSE_NATIVE_NSGL
#include <GLFW/glfw3native.h>
#endif


namespace
{

void ErrorCallback( int error, const char* message )
{
    kvsMessageError() << "GLFW error: " << std::string( message ) << std::endl;
}

}

namespace kvs
{

namespace glfw
{

Application::Application( int argc, char** argv ):
    kvs::ApplicationBase( argc, argv )
{
    static bool flag = true;
    if ( flag )
    {
        if ( !glfwInit() )
        {
            kvsMessageError() << "GLFW initialization failed." << std::endl;
            exit( EXIT_FAILURE );
        }
        flag = false;
        atexit( glfwTerminate );
    }
}

Application::~Application()
{
}

int Application::run()
{
    static bool flag = true;
    if ( flag )
    {
        glfwSetErrorCallback( ::ErrorCallback );

        // Call initialize event function for each screen.
        std::list<kvs::ScreenBase*>::iterator screen = screens().begin();
        std::list<kvs::ScreenBase*>::iterator end = screens().end();
        while ( screen != end )
        {
#if defined( KVS_GL_HAS_LAYER_BACKED_VIEW )
            glfwPollEvents();
            GLFWwindow* window = static_cast<kvs::glfw::ScreenBase*>(*screen)->handler();
            glfwMakeContextCurrent( window );
            objc_msgSend( glfwGetNSGLContext( window ), sel_registerName( "update" ) );
#endif
            static_cast<kvs::glfw::ScreenBase*>(*screen)->initializeEvent();
            static_cast<kvs::glfw::ScreenBase*>(*screen)->paintEvent();

            screen++;
        }
        this->main_loop();
        flag = false;
    }

    return true;
}

void Application::quit()
{
    exit( EXIT_SUCCESS );
}

void Application::main_loop()
{
    while ( !this->should_close() )
    {
        bool focused = false;

        std::list<kvs::ScreenBase*>::iterator screen = screens().begin();
        std::list<kvs::ScreenBase*>::iterator end = screens().end();
        while ( screen != end )
        {
            kvs::glfw::ScreenBase* s = static_cast<kvs::glfw::ScreenBase*>(*screen);
            GLFWwindow* window = s->handler();
            glfwMakeContextCurrent( window );

            std::list<kvs::glfw::Timer*>::iterator timer = s->timerEventHandler().begin();
            while ( timer != s->timerEventHandler().end() )
            {
                (*timer)->timerEvent();
                timer++;
            }

            if ( glfwGetWindowAttrib( window, GLFW_FOCUSED ) )
            {
                glfwPollEvents();
                focused = true;
            }

            screen++;
        }

        if ( !focused ) { glfwPollEvents(); }
    }
}

bool Application::should_close()
{
    if ( screens().empty() ) { return true; }

    std::list<kvs::ScreenBase*> screen_list;
    {
        std::list<kvs::ScreenBase*>::iterator screen = screens().begin();
        std::list<kvs::ScreenBase*>::iterator end = screens().end();
        while ( screen != end )
        {
            GLFWwindow* window = static_cast<kvs::glfw::ScreenBase*>(*screen)->handler();
            if ( glfwWindowShouldClose( window ) )
            {
                screen_list.push_back( *screen );
            }
            screen++;
        }
    }

    if ( !screen_list.empty() )
    {
        std::list<kvs::ScreenBase*>::iterator screen = screen_list.begin();
        std::list<kvs::ScreenBase*>::iterator end = screen_list.end();
        while ( screen != end )
        {
            screens().remove( *screen );
            screen++;
        }
    }

    if ( screens().empty() ) { return true; }

    return false;
}

} // end of namespace glfw

} // end of namespace kvs
