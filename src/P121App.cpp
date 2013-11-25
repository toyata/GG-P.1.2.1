#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class P121App : public AppNative {
  public:
	void prepareSettings(Settings *settings);
	void setup();
	void mouseDown(MouseEvent event);
	void mouseMove(MouseEvent event);
    void keyDown(KeyEvent event);
	void update();
	void draw();
    
	void shakeColors();
    
    Vec2i mMouseLoc;
    int tileCountX = 2;
    int tileCountY = 10;
    
    vector<ci::Color> colorsLeft;
    vector<ci::Color> colorsRight;
    
    bool interpolateShortest = true;
};

void P121App::prepareSettings( Settings *settings ){
	settings->setWindowSize(800, 800);
	settings->setFrameRate(10.0f);
    
    colorsLeft.reserve(tileCountY);
    colorsRight.reserve(tileCountY);
    
    mMouseLoc = Vec2i(800, 800);
    shakeColors();
}

void P121App::setup()
{
}

void P121App::mouseMove(MouseEvent event) {
    mMouseLoc = event.getPos();
}

void P121App::keyDown( KeyEvent event ) {
    switch (event.getChar()) {
        case '1':
            //segmentCount = 360;
            break;
        case '2':
            //segmentCount = 45;
            break;
        case '3':
            //segmentCount = 24;
            break;
        case '4':
            //segmentCount = 12;
            break;
        case '5':
            //segmentCount = 6;
            break;
    }
}


void P121App::mouseDown( MouseEvent event )
{
    shakeColors();
}

void P121App::update()
{
}

void P121App::draw()
{
	// clear out the window with black
	gl::clear(Color(0, 0, 0));
    
    int width = getWindowWidth();
    int height = getWindowHeight();
    
    tileCountX = (int) lmap((float)mMouseLoc.x, 0.0f, (float)width, 2.0f, 100.0f);
    tileCountY = (int) lmap((float)mMouseLoc.y, 0.0f, (float)height, 2.0f, 10.0f);

    float tileWidth = width / (float)tileCountX;
    float tileHeight = height / (float)tileCountY;
    ci:Color interCol;
    
    int i = 0;
    
    for (int gridY=0; gridY < tileCountY; gridY++) {
        ci::Color col1 = colorsLeft[gridY];
        ci::Color col2 = colorsRight[gridY];
     
        for (int gridX=0; gridX < tileCountX ; gridX++) {
            float amount = lmap((float)gridX, 0.0f, (float)(tileCountX - 1), 0.0f, 1.0f);
            
            Color cc = col1.lerp(amount, col2);
            gl::color(cc);
        
            float posX = (float) tileWidth*gridX;
            float posY = (float) tileHeight*gridY;
            
            gl::drawSolidRect(Rectf(posX, posY, posX + tileWidth, posY + tileHeight));
            i++;
        }
    }

}

void P121App::shakeColors() {
    for (int i=0; i < tileCountY; i++) {
        colorsLeft[i] = Color(CM_HSV, randFloat(60/(float)360), randFloat(1.0f), 1.0f);//color(random(0,60), random(0,100), 100);
        colorsRight[i] = Color(CM_HSV, randFloat(160/(float)360, 190/(float)360), 1.0f, randFloat(1.0f));//color(random(0,60), random(0,100), 100);
        
        //console() << float(160/360) << std::endl;
        //console() << Color(CM_HSV, randFloat(60), randFloat(100), 100) << std::endl;
    }
}

CINDER_APP_NATIVE( P121App, RendererGl )
