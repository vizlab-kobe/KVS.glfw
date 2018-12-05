#include "ScreenBase.h"
#include "Application.h"
#include "KVSMouseButton.h"
#include "KVSKey.h"
#include <kvs/Message>
#include <kvs/TimerEventListener>


namespace
{

kvs::glfw::ScreenBase* ThisScreen( GLFWwindow* handler )
{
    return static_cast<kvs::glfw::ScreenBase*>( glfwGetWindowUserPointer( handler ) );
}

}

namespace kvs
{

namespace glfw
{

void WindowSizeCallback( GLFWwindow* handler, int width, int height )
{
//    std::cout << "WindowSizeCallback( " << width << ", " << height << " )" << std::endl;

    kvs::glfw::ScreenBase* this_screen = ::ThisScreen( handler );
    this_screen->resizeEvent( width, height );
//    kvs::OpenGL::SetViewport( 0, 0, width * 2, height * 2 );
    this_screen->redraw();
//    this_screen->setSize( width, height );
}

void FramebufferSizeCallback( GLFWwindow* handler, int width, int height )
{
//    std::cout << "FramebufferSizeCallback( " << width << ", " << height << " )" << std::endl;

//    kvs::glfw::ScreenBase* this_screen = ::ThisScreen( handler );
//    this_screen->resizeEvent( width, height );
//    kvs::OpenGL::SetViewport( 0, 0, width, height );
//    this_screen->redraw();
//    int width, height;
//    glfwGetFramebufferSize(this_screen->handler(), &width, &height);
//    this_screen->setSize( width, height );
//    glViewport(0, 0, width, height);
}

void MouseButtonCallback( GLFWwindow* handler, int button, int action, int mods )
{
    double x = 0.0;
    double y = 0.0;
    glfwGetCursorPos( handler, &x, &y );

    kvs::glfw::ScreenBase* this_screen = ::ThisScreen( handler );
    this_screen->m_mouse_event->setPosition( int( x ), int( y ) );
    this_screen->m_mouse_event->setButton( kvs::glfw::KVSMouseButton::Button( button ) );
    this_screen->m_mouse_event->setState( kvs::glfw::KVSMouseButton::State( action ) );
    this_screen->m_mouse_event->setModifiers( kvs::glfw::KVSKey::Modifier( mods ) );

    switch ( action )
    {
    case GLFW_PRESS:
    {
        this_screen->m_elapse_time_counter.stop();
        if ( this_screen->m_elapse_time_counter.sec() < 0.2f )
        {
            this_screen->m_mouse_event->setAction( kvs::MouseButton::DoubleClicked );
            this_screen->mouseDoubleClickEvent( this_screen->m_mouse_event );
        }
        else
        {
            this_screen->m_mouse_event->setAction( kvs::MouseButton::Pressed );
            this_screen->mousePressEvent( this_screen->m_mouse_event );
        }
        this_screen->m_elapse_time_counter.start();
        break;
    }
    case GLFW_RELEASE:
    {
        this_screen->m_mouse_event->setAction( kvs::MouseButton::Released );
        this_screen->mouseReleaseEvent( this_screen->m_mouse_event );
        break;
    }
    default: break;
    }
}

void CursorPosCallback( GLFWwindow* handler, double x, double y )
{
    kvs::glfw::ScreenBase* this_screen = ::ThisScreen( handler );
    if ( this_screen->m_mouse_event->state() == kvs::MouseButton::Down )
    {
        this_screen->m_mouse_event->setPosition( x, y );
        this_screen->m_mouse_event->setAction( kvs::MouseButton::Moved );
        this_screen->mouseMoveEvent( this_screen->m_mouse_event );
    }
}

void ScrollCallback( GLFWwindow* handler, double x, double y )
{
    kvs::glfw::ScreenBase* this_screen = ::ThisScreen( handler );
    this_screen->m_wheel_event->setPosition( x, y );
    this_screen->m_wheel_event->setDirection( y > 0.0 ? 1 : -1 );
    this_screen->wheelEvent( this_screen->m_wheel_event );
}

void KeyCallback( GLFWwindow* handler, int key, int scancode, int action, int mods )
{
    double x = 0.0;
    double y = 0.0;
    glfwGetCursorPos( handler, &x, &y );

    kvs::glfw::ScreenBase* this_screen = ::ThisScreen( handler );
    this_screen->m_key_event->setPosition( int( x ), int( y ) );
    this_screen->m_key_event->setKey( kvs::glfw::KVSKey::Code( key ) );
    this_screen->keyPressEvent( this_screen->m_key_event );
}

ScreenBase::ScreenBase( kvs::glfw::Application* application ):
    m_handler( 0 ),
    m_id( -1 ),
    m_mouse_event( 0 ),
    m_key_event( 0 ),
    m_wheel_event( 0 ),
    m_is_fullscreen( false )
{
    if ( application ) application->attach( this );

    m_mouse_event = new kvs::MouseEvent();
    m_key_event = new kvs::KeyEvent();
    m_wheel_event = new kvs::WheelEvent();

    m_elapse_time_counter.start();
}

ScreenBase::~ScreenBase()
{
    if ( m_mouse_event ) { delete m_mouse_event; }
    if ( m_key_event ) { delete m_key_event; }
    if ( m_wheel_event ) { delete m_wheel_event; }
    if ( m_handler ) { glfwDestroyWindow( m_handler ); }
}

void ScreenBase::create()
{
    KVS_ASSERT( m_id == -1 );

    // Create window.
    m_handler = glfwCreateWindow(
        BaseClass::width(),
        BaseClass::height(),
        BaseClass::title().c_str(),
        NULL, NULL );
    if ( !m_handler )
    {
        kvsMessageError() << "Cannot create GLFW screen." << std::endl;
        return;
    }

    glfwMakeContextCurrent( m_handler );
    glfwSwapInterval(1);

    // Set callback functions.
    glfwSetWindowUserPointer( m_handler, this );
    glfwSetWindowSizeCallback( m_handler, WindowSizeCallback );
    glfwSetFramebufferSizeCallback( m_handler, FramebufferSizeCallback );
    glfwSetMouseButtonCallback( m_handler, MouseButtonCallback );
    glfwSetCursorPosCallback( m_handler, CursorPosCallback );
    glfwSetScrollCallback( m_handler, ScrollCallback );
    glfwSetKeyCallback( m_handler, KeyCallback );

    // Initialize GLEW. (Before glfwMakeContextCurrent)
#if defined( KVS_ENABLE_GLEW )
    GLenum result = glewInit();
    if ( result != GLEW_OK )
    {
        kvsMessageError() << "GLEW initialization failed: " << glewGetErrorString( result ) << "." << std::endl;
    }
#endif

    // Create paint device.
    BaseClass::paintDevice()->create();

    // Generate window ID.
    static int counter = 0;
    m_id = counter++;
}

void ScreenBase::show()
{
#if 1 // KVS_ENABLE_DEPRECATED
    if ( m_id == -1 ) { this->create(); }
#endif
    glfwShowWindow( m_handler );
}

void ScreenBase::hide()
{
    glfwHideWindow( m_handler );
}

void ScreenBase::showFullScreen()
{
    if ( m_is_fullscreen ) return;
    m_is_fullscreen = true;

    // To-Do
}

void ScreenBase::showNormal()
{
    if ( !m_is_fullscreen ) return;
    m_is_fullscreen = false;

    // To-Do
}

void ScreenBase::popUp()
{
    glfwFocusWindow( m_handler );
}

void ScreenBase::pushDown()
{
    // To-Do
}

void ScreenBase::redraw()
{
    this->paintEvent();
//    glfwPostEmptyEvent();
}

void ScreenBase::resize( int width, int height )
{
    glfwSetWindowSize( m_handler, width, height );
}

bool ScreenBase::isFullScreen() const
{
    return m_is_fullscreen;
}

void ScreenBase::enable() {}
void ScreenBase::disable() {}
void ScreenBase::reset() {}

void ScreenBase::initializeEvent(){}
void ScreenBase::paintEvent(){}
void ScreenBase::resizeEvent( int, int ){}
void ScreenBase::mousePressEvent( kvs::MouseEvent* ){}
void ScreenBase::mouseMoveEvent( kvs::MouseEvent* ){}
void ScreenBase::mouseReleaseEvent( kvs::MouseEvent* ){}
void ScreenBase::mouseDoubleClickEvent( kvs::MouseEvent* ){}
void ScreenBase::wheelEvent( kvs::WheelEvent* ){}
void ScreenBase::keyPressEvent( kvs::KeyEvent* ){}

std::list<kvs::glfw::Timer*>& ScreenBase::timerEventHandler()
{
    return m_timer_event_handler;
}

void ScreenBase::addTimerEvent( kvs::TimerEventListener* event, kvs::glfw::Timer* timer )
{
    event->setScreen( this );
    timer->setEventListener( event );
    m_timer_event_handler.push_back( timer );
}

} // end of namespace glfw

} // end of namespace kvs
