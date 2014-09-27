#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Shader.h"

using namespace ci;
using namespace ci::app;
using namespace std;


enum LightingModel{
    
    FLAT,
    PHONG,
    CELL
    
};

class Lighting_TestApp : public AppNative {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyUp( KeyEvent event ) override;
	void update() override;
	void draw() override;
    
    vec4 mLightPos;
    
    gl::GlslProgRef mFlatShading;
    gl::GlslProgRef mPhongShading;
    gl::GlslProgRef mCellShading;

    gl::BatchRef mTorus, mTeapot, mLightBulb;

    LightingModel mCurrentModel;
    
    CameraPersp mCamera;
    
    vec3 mCellColors[3];
    
};

void Lighting_TestApp::setup()
{
    
    mFlatShading = gl::GlslProg::create(loadAsset("Flat.vert"), loadAsset("Flat.frag"));
    mPhongShading = gl::GlslProg::create(loadAsset("Phong.vert"), loadAsset("Phong.frag"));
    mCellShading = gl::GlslProg::create(loadAsset("Cell.vert"), loadAsset("Cell.frag"));
    
    mTorus = gl::Batch::create(geom::Torus().enable(geom::Attrib::NORMAL), mFlatShading);
    mTeapot = gl::Batch::create(geom::Teapot().enable(geom::Attrib::NORMAL), mFlatShading);

    mLightBulb = gl::Batch::create(geom::Sphere().radius(.1), gl::getStockShader(gl::ShaderDef().color()));
    
    mLightPos = vec4( 5,5,5, 1);
    
    mCamera.setPerspective(60, getWindowAspectRatio(), .1, 10000);
    mCamera.lookAt(vec3(0,0,5),vec3(0,0,0));
    
    mCellColors[0] = vec3( .25,.0,1. );
    mCellColors[1] = vec3( .5,.25,1. );
    mCellColors[2] = vec3( 1.,.75,1. );
    
    gl::enableDepthWrite();
    gl::enableDepthRead();
    
}

void Lighting_TestApp::keyUp( KeyEvent event )
{
    
    if( event.getChar() == '1' ){
        mCurrentModel = FLAT;
        
        mTorus->setGlslProg(mFlatShading);
        mTeapot->setGlslProg(mFlatShading);
        
    }else if( event.getChar() == '2' ){
        mCurrentModel = PHONG;
        
        mTorus->setGlslProg(mPhongShading);
        mTeapot->setGlslProg(mPhongShading);
        
    }else if( event.getChar() == '3' ){
        mCurrentModel = CELL;
        
        mTorus->setGlslProg(mCellShading);
        mTeapot->setGlslProg(mCellShading);
        
    }
    
}

void Lighting_TestApp::mouseDown( MouseEvent event )
{
}

void Lighting_TestApp::update()
{
    
    mLightPos = vec4( vec3(cos(getElapsedSeconds())*3, sin(getElapsedSeconds()*2)*3, sin(getElapsedSeconds())*3)*.5f, 1.);
    
}

void Lighting_TestApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::setMatrices(mCamera);
    
    mTorus->getGlslProg()->uniform("lightPosition",  vec3( gl::getModelView() * mLightPos ) );
    
    if(mCurrentModel == CELL )
        mTorus->getGlslProg()->uniform("cells", mCellColors, 3 );
    
    {
        gl::ScopedMatrices push;
        gl::translate(vec3(2,0,0));
        gl::rotate((float)getElapsedSeconds()*7. , vec3(1,1,1) );
        mTorus->draw();
    }
    
    
    {
        gl::ScopedMatrices push;
        gl::translate(vec3(-2,0,0));
        gl::rotate( (float)getElapsedSeconds()*7., vec3(-1,-1,-1) );
        mTeapot->draw();
    }
    
    {
        gl::ScopedMatrices push;
        gl::translate(mLightPos.x, mLightPos.y, mLightPos.z);
        mLightBulb->draw();
    }
    
}

CINDER_APP_NATIVE( Lighting_TestApp, RendererGl )
