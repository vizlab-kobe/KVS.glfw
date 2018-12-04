#include <iostream>
#include <kvs/StructuredVolumeObject>
#include <kvs/StructuredVolumeImporter>
#include <kvs/PolygonObject>
#include <kvs/Isosurface>
#include <kvs/HydrogenVolumeData>
#include <KVS.glfw/Lib/Application.h>
#include <KVS.glfw/Lib/Screen.h>

void Register( kvs::StructuredVolumeObject* volume, kvs::glfw::Screen& screen )
{
    const double i = ( volume->maxValue() + volume->minValue() ) * 0.5;
    const kvs::PolygonObject::NormalType n = kvs::PolygonObject::VertexNormal;
    const bool d = false;
    const kvs::TransferFunction t( 256 );
    kvs::PolygonObject* object = new kvs::Isosurface( volume, i, n, d, t );
    screen.registerObject( object );
}


int main( int argc, char** argv )
{
    kvs::glfw::Application app( argc, argv );

    kvs::glfw::Screen screen1( &app );
    kvs::glfw::Screen screen2( &app );

    screen1.setTitle("A");
    screen2.setTitle("B");

    kvs::StructuredVolumeObject* volume = new kvs::HydrogenVolumeData( kvs::Vec3u( 64, 64, 64 ) );
    volume->updateMinMaxValues();

    Register( volume, screen1 );
    Register( volume, screen2 );

    screen1.show();
    screen2.show();

    return app.run();
}
