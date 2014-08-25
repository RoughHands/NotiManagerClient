#include "AppDelegate.h"
#include "NotiManagerScene.h"

#include "SpriteBuilderTester.h"

#include <spritebuilder/SpriteBuilder.h>
#define PHYSIC_FACTOR 32

const char* CCSetupPixelFormat = "CCSetupPixelFormat";
const char* CCSetupScreenMode = "CCSetupScreenMode";
const char* CCSetupScreenOrientation = "CCSetupScreenOrientation";
const char* CCSetupAnimationInterval = "CCSetupAnimationInterval";
const char* CCSetupFixedUpdateInterval = "CCSetupFixedUpdateInterval";
const char* CCSetupShowDebugStats = "CCSetupShowDebugStats";
const char* CCSetupTabletScale2X = "CCSetupTabletScale2X";

const char* CCSetupDepthFormat = "CCSetupDepthFormat";
const char* CCSetupPreserveBackbuffer = "CCSetupPreserveBackbuffer";
const char* CCSetupMultiSampling = "CCSetupMultiSampling";
const char* CCSetupNumberOfSamples = "CCSetupNumberOfSamples";

const char* CCScreenOrientationLandscape = "CCScreenOrientationLandscape";
const char* CCScreenOrientationPortrait = "CCScreenOrientationPortrait";

const char* CCScreenModeFlexible = "CCScreenModeFlexible";
const char* CCScreenModeFixed = "CCScreenModeFixed";




USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    Size size = director->getWinSize();
    float scaleFactor = size.width / 640.0f;
    glview->setDesignResolutionSize(size.width / scaleFactor, 1136, ResolutionPolicy::SHOW_ALL);


    //director->setContentScaleFactor(scaleFactor);
    director->setContentScaleFactor(scaleFactor / (size.height / 1136)); //because the current resource is phonehd's

    spritebuilder::CCBReader::setupSpriteBuilder("resources-phonehd", PHYSIC_FACTOR);


    // turn on display FPS
//    director->setDisplayStats(true);
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    
    NotiManagerScene* notiManagerScene = NotiManagerScene::create();
    director->runWithScene(notiManagerScene);

//    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();
//    ccNodeLoaderLibrary->registerNodeLoader("MainScene", MainSceneContent::loader());
//    ccNodeLoaderLibrary->registerNodeLoader("Level", LevelLoader::loader());
//    spritebuilder::CCBReader * ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
//    
//    //std::string str = CCBLocalizationManager::sharedManager()->localizedStringForKey("this_is_a_game");
//    
//    Scene* scene = ccbReader->createSceneWithNodeGraphFromFile("MainScene.ccbi");
//    director->runWithScene(scene);




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
