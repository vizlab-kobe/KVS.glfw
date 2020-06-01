#include <kvs/glfw/Application>
#include <kvs/glfw/Screen>
#include <kvs/HydrogenVolumeData>
#include <kvs/Isosurface>
#include <kvs/PolygonRenderer>


int main( int argc, char** argv )
{
    kvs::glfw::Application app( argc, argv );
    kvs::glfw::Screen screen( &app );
    screen.setTitle("PolygonRenderer");

    auto* volume = new kvs::HydrogenVolumeData( kvs::Vec3u( 64, 64, 64 ) );
    auto* object = new kvs::Isosurface( volume );
    auto* renderer = new kvs::PolygonRenderer();
    screen.registerObject( object, renderer );
    screen.create();

    delete volume;

    return app.run();
}
