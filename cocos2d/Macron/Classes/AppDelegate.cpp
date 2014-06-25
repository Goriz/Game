#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}


typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;// for iphone

static Resource smallResource = {cocos2d::Size(480,320),"iphone"};

//for ipad
static Resource mediumResource = {cocos2d::Size(1024,768),"ipad"};

//for ipad retina
static Resource largeResource = {cocos2d::Size(2048,1536),"ipadhd"};

//static display size
static Size designResolutionSize = Size(800, 480);


bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    //////////////////////////////////////
    // ** multi display scaling **
    //////////////////////////////////////
    
    //device size
    Size frameSize = glview->getFrameSize();
    
    //set design resolution  ** (800x480) boder none
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    
    /*  今のところ一セットの画像でやるので、基準の画像サイズのみ考慮する。後は拡大
    
    //add serch path (Resource/image)
    std::vector<std::string> searchPath;
    searchPath.push_back("image");
    FileUtils::getInstance()->setSearchPaths(searchPath);
    
    //both resource size setting
    std::vector<std::string> resolutionOrder;
    if(frameSize.height > largeResource.size.height)
    {
        //add Resources/image/ipadhd
        resolutionOrder.push_back(largeResource.directory);
        //set scale factor
        director->setContentScaleFactor(MIN(
                                largeResource.size.height/designResolutionSize.height,
                                largeResource.size.width/designResolutionSize.width));
    }
    else if(frameSize.height > mediumResource.size.height)
    {
        //add Resources/image/ipad
        resolutionOrder.push_back(mediumResource.directory);
        //set scale factor
        director->setContentScaleFactor(MIN(
                                            mediumResource.size.height/designResolutionSize.height,
                                            mediumResource.size.width/designResolutionSize.width));
    }
    else if(frameSize.height > smallResource.size.height)
    {
        //add Resources/image/iphone
        resolutionOrder.push_back(smallResource.directory);
        //set scale factor
        director->setContentScaleFactor(MIN(
                                            smallResource.size.height/designResolutionSize.height,
                                            smallResource.size.width/designResolutionSize.width));
    }
    FileUtils::getInstance()->setSearchResolutionsOrder(resolutionOrder);
    
    */
    //end scaling

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    //set gl depth
    //director->setDepthTest(false);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
