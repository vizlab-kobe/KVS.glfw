#include <kvs/glfw/Application>
#include <kvs/glfw/Screen>
#include <kvs/HydrogenVolumeData>
#include <kvs/Isosurface>
#include <kvs/PolygonRenderer>
#include <kvs/RayCastingRenderer>


int main( int argc, char** argv )
{
    kvs::glfw::Application app( argc, argv );
    kvs::glfw::Screen screen1( &app );
    kvs::glfw::Screen screen2( &app );
    screen1.setTitle( "RayCastingRenderer" );
    screen2.setTitle( "PolygonRenderer" );

    auto* volume = new kvs::HydrogenVolumeData( kvs::Vec3u( 64, 64, 64 ) );

    // Ray-casting rendering
    {
        auto* renderer = new kvs::glsl::RayCastingRenderer();
        screen1.registerObject( volume, renderer );
        screen1.create();
    }

    // Isosurfaces
    {
        auto* object = new kvs::Isosurface( volume );
        auto* renderer = new kvs::glsl::PolygonRenderer();
        screen2.registerObject( object, renderer );
        screen2.create();
    }

    return app.run();
}
