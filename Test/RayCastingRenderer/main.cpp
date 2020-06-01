#include <kvs/glfw/Application>
#include <kvs/glfw/Screen>
#include <kvs/HydrogenVolumeData>
#include <kvs/RayCastingRenderer>


int main( int argc, char** argv )
{
    kvs::glfw::Application app( argc, argv );
    kvs::glfw::Screen screen( &app );
    screen.setTitle( "RayCastingRenderer" );

    auto* object = new kvs::HydrogenVolumeData( kvs::Vec3u( 64, 64, 64 ) );
//    auto* renderer = new kvs::RayCastingRenderer();
    auto* renderer = new kvs::glsl::RayCastingRenderer();
    screen.registerObject( object, renderer );
    screen.create();

    return app.run();
}
