#include <kvs/glfw/Application>
#include <kvs/glfw/Screen>
#include <kvs/HydrogenVolumeData>
#include <kvs/Isosurface>
#include <kvs/PolygonRenderer>
#include <kvs/KeyPressEventListener>


class KeyPressEvent : public kvs::KeyPressEventListener
{
    void update( kvs::KeyEvent* event )
    {
        switch ( event->key() )
        {
        case kvs::Key::f:
            if ( screen()->isFullScreen() )
            {
                screen()->showNormal();
            }
            else
            {
                screen()->showFullScreen();
            }
            break;
        default: break;
        }
    }
};

int main( int argc, char** argv )
{
    kvs::glfw::Application app( argc, argv );
    kvs::glfw::Screen screen( &app );
    screen.setTitle( "Fullscreen" );

    auto* volume = new kvs::HydrogenVolumeData( kvs::Vec3u( 64, 64, 64 ) );
    auto* object = new kvs::Isosurface( volume );
    auto* renderer = new kvs::glsl::PolygonRenderer();
    screen.registerObject( object, renderer );
    screen.create();

    KeyPressEvent event;
    screen.addEvent( &event );

    delete volume;

    return app.run();
}
