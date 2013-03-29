//Viewport and camera based of mad marx tutorial 4
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
        viewport->setBackgroundColour(ColourValue(1, 0, 1));
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
        //our object object :D
        ManualObject* manualObject = NULL;
        {
            //create the object
            manualObject = scene->createManualObject("CubeWithAxes");
            //don't update 2d vertex/index later
            manualObject->setDynamic(false);
            //size
            float size = 0.7f;
            //create the cube
            //begin declaring vertices and faces for the shape, first parameter is the material
            manualObject->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_LIST);
            {
                float cp = 1.0f * size;
                float cm = -1.0f * size;
                //vertices
                manualObject->position(cm, cp, cm); //a vertex
                manualObject->colour(ColourValue(0.0f, 1.0f, 0.0f, 1.0f));
                manualObject->position(cp, cp, cm); //a vertex
                manualObject->colour(ColourValue(1.0f, 1.0f, 0.0f, 1.0f));
                manualObject->position(cp, cm, cm); //a vertex
                manualObject->colour(ColourValue(0.0f, 1.0f, 0.0f, 1.0f));
                manualObject->position(cm, cm, cm); //a vertex
                manualObject->colour(ColourValue(1.0f, 0.0f, 0.0f, 1.0f));
                manualObject->position(cm, cp, cp); //a vertex
                manualObject->colour(ColourValue(0.0f, 0.0f, 0.0f, 1.0f));
                manualObject->position(cp, cp, cp); //a vertex
                manualObject->colour(ColourValue(0.0f, 1.0f, 1.0f, 1.0f));
                manualObject->position(cp, cm, cp); //a vertex
                manualObject->colour(ColourValue(1.0f, 1.0f, 1.0f, 1.0f));
                manualObject->position(cm, cm, cp); //a vertex
                manualObject->colour(ColourValue(0.0f, 0.0f, 1.0f, 1.0f));
                //faces
                manualObject->triangle(0, 1, 2);
                manualObject->triangle(2, 3, 0);
                manualObject->triangle(4, 6, 5);
                manualObject->triangle(6, 4, 7);

                manualObject->triangle(0, 4, 5);
                manualObject->triangle(5, 1, 0);
                manualObject->triangle(2, 6, 7);
                manualObject->triangle(7, 3, 2);

                manualObject->triangle(0, 7, 4);
                manualObject->triangle(7, 0, 3);
                manualObject->triangle(1, 5, 6);
                manualObject->triangle(6, 2, 1);
            }
            manualObject->end();
            //create the axis
            manualObject->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_LIST);
            {
                float axeSize = 2.0f * size;
                manualObject->position(0.0f, 0.0f, 0.0f);
                manualObject->colour(Ogre::ColourValue::Red);
                manualObject->position(axeSize, 0.0f, 0.0f);
                manualObject->colour(Ogre::ColourValue::Red);
                manualObject->position(0.0f, 0.0f, 0.0f);
                manualObject->colour(Ogre::ColourValue::Green);
                manualObject->position(0.0, axeSize, 0.0);
                manualObject->colour(Ogre::ColourValue::Green);
                manualObject->position(0.0f, 0.0f, 0.0f);
                manualObject->colour(Ogre::ColourValue::Blue);
                manualObject->position(0.0, 0.0, axeSize);
                manualObject->colour(Ogre::ColourValue::Blue);

                manualObject->index(0);
                manualObject->index(1);
                manualObject->index(2);
                manualObject->index(3);
                manualObject->index(4);
                manualObject->index(5);
            }
            manualObject->end();
        }
        //create a mesh from the object
        String meshName = "MeshCubeAndAxe";
        manualObject->convertToMesh(meshName);
        //create 5 entities from the mesh
        const int entityNumber = 5;
        SceneNode * nodes[entityNumber];
        for (int iter = 0; iter < entityNumber; ++iter) {
            Entity* entity = scene->createEntity(meshName);
            nodes[iter] = rootSceneNode->createChildSceneNode();
            nodes[iter]->attachObject(entity);
            //move the entity away from the others
            float positionOffset = float(1 + iter * 2)-(float(entityNumber));
            nodes[iter]->translate(positionOffset, positionOffset, -10.0f);
        }
        //while the window isn't closed
        while (!skeleton->window->isClosed()) {
            //update the window
            skeleton->window->update(false);
            //swap the buffers using vsync
            skeleton->window->swapBuffers(true);
            skeleton->root->renderOneFrame();
            //rotate entities
            for(int iter = 0; iter < entityNumber; iter++){
                nodes[iter]->yaw(Radian(0.01f));
                nodes[iter]->roll(Radian(0.01f));
            }
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
