//Lighting based off mad marx tutorial 6
//include our skeleton file
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
        //create a scene node for the camera
        SceneNode* cameraNode = rootSceneNode->createChildSceneNode("CameraNode");
        {
            //attach the camera to the node
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
            viewport->setBackgroundColour(ColourValue(1, 0, 1));
            //make the camera have the same ratio as the viewport
            camera->setAspectRatio(float(viewport->getActualWidth()) / float(viewport->getActualHeight()));
            //set clip distance
            camera->setNearClipDistance(1.5f);
            camera->setFarClipDistance(3000.0f);
        }
        {
            //make the window active
            skeleton->window->setActive(true);
            //don't auto update the window
            skeleton->window->setAutoUpdated(false);
            //clear events so we don't have to process everything we missed while initialising
            skeleton->root->clearEventTimes();
        }
        //create a scene node for our light
        SceneNode* lightNode = rootSceneNode->createChildSceneNode("lightNode");
        {
            //create the light
            Light* light = scene->createLight();
            //directional light
            light->setType(Light::LT_DIRECTIONAL);
            //red light
            light->setDiffuseColour(0.8f, 0.3f, 0.3f);
            //colour of reflection (white)
            light->setSpecularColour(1.0f, 1.0f, 1.0f);
            //attach light to scene node
            lightNode->attachObject(light);
            //set the ambient lighting for the scene (dull grey)
            scene->setAmbientLight(ColourValue(0.2f, 0.2f, 0.2f, 1.0f));
        }
        {
            //Get the singleton for the resource group manager class
            ResourceGroupManager& rgMgr = ResourceGroupManager::getSingleton();
            //create a resource group called meshes
            String resourceGroupName = "meshes";
            rgMgr.createResourceGroup(resourceGroupName);
            //tell the resource group which directory to look in
            rgMgr.addResourceLocation("./media/meshes", "FileSystem", resourceGroupName, false);
            //parse any scripts in the resource group
            rgMgr.initialiseResourceGroup(resourceGroupName);
            //load all the files
            rgMgr.loadResourceGroup(resourceGroupName);
        }
        //amount of entities to display
        const int entityNumber = 5;
        SceneNode * nodes[entityNumber];
        for (int iter = 0; iter < entityNumber; iter++) {
            //the entity loaded from the Cube.mesh file
            Entity* entity = scene->createEntity("Cube.mesh");
            //create a scene node for the entity
            nodes[iter] = rootSceneNode->createChildSceneNode();
            //attach the entity
            nodes[iter]->attachObject(entity);
            //scale up node
            nodes[iter]->scale(Vector3(15, 15, 15));
            //move nodes so they don't overlap
            float offset = (float(1 + iter * 2) - (float(entityNumber)))*20;
            nodes[iter]->translate(offset, offset, -200.0f);
        }
        //while the window hasn't been closed
        while (!skeleton->window->isClosed()) {
            //rotate the light
            lightNode->yaw(Degree(2.5));
            //update the window but don't swap buffers
            skeleton->window->update(false);
            //swap the buffers using vsync
            skeleton->window->swapBuffers(true);
            skeleton->root->renderOneFrame();
            //get events
            WindowEventUtilities::messagePump();
            for (int iter = 0; iter < entityNumber; iter++) {
                nodes[iter]->yaw(Radian(0.01f));
                nodes[iter]->pitch(Radian(0.01f));
            }
        }
        //several things could go wrong, if they do, catch them here	
    } catch (Exception &e) {
        LogManager::getSingleton().logMessage(String("Ogre Error: ") + e.what());
    } catch (std::exception &e) {
        LogManager::getSingleton().logMessage(String("Error: ") + e.what());
    }
}
