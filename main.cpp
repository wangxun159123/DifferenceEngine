//Viewport and camera based of mad marx tutorial 3
//inlude our skeleton file
#include "OgreSkeleton.h"

//main method

int main() {
    try {
        //create our Ogre Skeleton object
        OgreSkeleton* skeleton = new OgreSkeleton("Difference Engine");
        //create a scene manager
        SceneManager* scene = skeleton->root->createSceneManager(ST_GENERIC, "Scene1");
        //get the root scene node, scene nodes are hierarchical and can contain child scene nodes or meshes. 
        //You perform transformations on scene nodes, not meshes
        SceneNode* rootSceneNode = scene->getRootSceneNode();
        //create a camera
        Camera* camera = scene->createCamera("Camera1");
        //add the camera to it's own scene node
        SceneNode* cameraNode = rootSceneNode->createChildSceneNode("CameraNode");
        cameraNode->attachObject(camera);
        //create a viewport, this is a link between a camera and a window
        //viewport will be 88% of the width and height of the window
        float viewportWidth = 0.88f;
        float viewportHeight = 0.88f;
        //centre the viewport
        float viewportLeft = (1.0f - viewportWidth) * 0.5f;
        float viewportTop = (1.0f - viewportHeight) * 0.5f;
        //create the viewport
        Viewport* viewport = skeleton->window->addViewport(camera, 100, viewportLeft, viewportTop, viewportWidth, viewportHeight);
        //draw the scene automatically when the window updates
        viewport->setAutoUpdated(true);
        //give the viewport a bright colour to see holes in the scenery
        viewport->setBackgroundColour(ColourValue(1,0,1));
        //make the camera have the same ratio as the viewport
        camera->setAspectRatio(float(viewport->getActualWidth()) / float(viewport->getActualHeight()));
        //set clip distance
        camera->setNearClipDistance(1.5f);
        camera->setFarClipDistance(3000.0f);
        //make the window active
        skeleton->window->setActive(true);
        //don't auto update the window
        skeleton->window->setAutoUpdated(false);
        //clear events so we don't have to process everything we missed while initialising
        skeleton->root->clearEventTimes();
        //while the window isn't closed
        while (!skeleton->window->isClosed()) {
            //update the window
            skeleton->window->update(false);
            //swap the buffers using vsync
            skeleton->window->swapBuffers(true);
            skeleton->root->renderOneFrame();
            //get events
            WindowEventUtilities::messagePump();
        }
        //several things could go wrong, if they do, catch them here	
    } catch (Exception &e) {
        LogManager::getSingleton().logMessage(String("Ogre Error: ") + e.what());
    } catch (std::exception &e) {
        LogManager::getSingleton().logMessage(String("Error: ") + e.what());
    }
}
