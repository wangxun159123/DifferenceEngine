//Loading materials based off mad marx tutorial 7
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
            light->setDiffuseColour(1.0f, 1.0f, 1.0f);
            //colour of reflection (white)
            light->setSpecularColour(1.0f, 1.0f, 1.0f);
            //attach light to scene node
            lightNode->attachObject(light);
            //set the ambient lighting for the scene (dull grey)
            scene->setAmbientLight(ColourValue(0.2f, 0.2f, 0.2f, 1.0f));
        }
        //create a resource group called entities
        String resourceGroupName = "entities";
        {
            //Get the singleton for the resource group manager class
            ResourceGroupManager& rgMgr = ResourceGroupManager::getSingleton();
            //create the resource group
            rgMgr.createResourceGroup(resourceGroupName);
            //tell the resource group which directories to look in
            rgMgr.addResourceLocation("./media/textures", "FileSystem", resourceGroupName, false);
            rgMgr.addResourceLocation("./media/meshes", "FileSystem", resourceGroupName, false);
            //parse any scripts in the resource group
            rgMgr.initialiseResourceGroup(resourceGroupName);
            //load all the files
            rgMgr.loadResourceGroup(resourceGroupName);
        }
        //Get the singleton for the material manager class
        MaterialManager& materialManager = MaterialManager::getSingleton();
        {
            //create a material
            MaterialPtr material = materialManager.create("M_NoLighting", resourceGroupName);
            //get the first technique (rendering method) in the material
            Technique* firstTechnique = material->getTechnique(0);
            //get the first pass (layer) in the technique
            Pass* firstPass = firstTechnique->getPass(0);
            //disable lighting
            firstPass->setLightingEnabled(false);
        }
        {
            //create a material
            MaterialPtr material = materialManager.create("M_NoLighting+OneTexture", resourceGroupName);
            //get the first technique (rendering method) in the material
            Technique* firstTechnique = material->getTechnique(0);
            //get the first pass (layer) in the technique
            Pass* firstPass = firstTechnique->getPass(0);
            //disable lighting
            firstPass->setLightingEnabled(false);
            //create a texture unit
            TextureUnitState* textureUnit = firstPass->createTextureUnitState();
            //set the file to use for the texture
            textureUnit->setTextureName("Fur.png", TEX_TYPE_2D);
            textureUnit->setTextureCoordSet(0);
        }
        {
            //create a material
            MaterialPtr material = materialManager.create("M_LightingColour", resourceGroupName);
            //get the first technique (rendering method) in the material
            Technique* firstTechnique = material->getTechnique(0);
            //get the first pass (layer) in the technique
            Pass* firstPass = firstTechnique->getPass(0);
            //enable lighting
            firstPass->setLightingEnabled(true);
            //emit a faint red light
            firstPass->setSelfIllumination(ColourValue(0.1f, 0.0f, 0.0f));
            //set colour of object
            firstPass->setDiffuse(ColourValue(1.0f, 0.4f, 0.4f, 1.0f));
            //set ambient colour
            firstPass->setAmbient(ColourValue(0.4f, 0.1f, 0.1f, 1.0f));
            //reflect the sun
            firstPass->setSpecular(ColourValue(1.0f, 1.0f, 1.0f, 1.0f));
            //set the shininess
            firstPass->setShininess(Real(64.0f));
        }
        {
            //create a material
            MaterialPtr material = materialManager.create("M_Lighting+OneTexture", resourceGroupName);
            //get the first technique (rendering method) in the material
            Technique* firstTechnique = material->getTechnique(0);
            //get the first pass (layer) in the technique
            Pass* firstPass = firstTechnique->getPass(0);
            //set lighting options
            firstPass->setDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
            firstPass->setAmbient(0.3f, 0.3f, 0.3f);
            firstPass->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
            firstPass->setShininess(64.0f);
            firstPass->setSelfIllumination(0.1f, 0.1f, 0.1f);
            //create a texture unit
            TextureUnitState* textureUnit = firstPass->createTextureUnitState();
            //set the file to use for the texture
            textureUnit->setTextureName("Iron-rusted.png", TEX_TYPE_2D);
            textureUnit->setTextureCoordSet(0);
        }
        {
            //create a material
            MaterialPtr material = materialManager.create("M_Lighting+DiffuseMap+LightMap", resourceGroupName);
            //get the first technique (rendering method) in the material
            Technique* firstTechnique = material->getTechnique(0);
            //get the first pass (layer) in the technique
            Pass* firstPass = firstTechnique->getPass(0);
            //set lighting options
            firstPass->setDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
            firstPass->setAmbient(0.3f, 0.3f, 0.3f);
            firstPass->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
            firstPass->setShininess(64.0f);
            firstPass->setSelfIllumination(0.1f, 0.1f, 0.1f);
            //create a texture unit
            TextureUnitState* textureUnit = firstPass->createTextureUnitState();
            //set the file to use for the texture
            textureUnit->setTextureName("Iron-rusted.png", TEX_TYPE_2D);
            textureUnit->setTextureCoordSet(0);
            //create a lightmap texture
            TextureUnitState* textureUnitLightMap = firstPass->createTextureUnitState();
            textureUnitLightMap->setTextureName("Fur.png", TEX_TYPE_2D);
            textureUnitLightMap->setTextureCoordSet(1);
        }
        //create a vector with all out different materials
        std::vector< Ogre::String > materialNames;
        materialNames.push_back("M_NoLighting");
        materialNames.push_back("M_NoLighting+OneTexture");
        materialNames.push_back("M_LightingColour");
        materialNames.push_back("M_Lighting+OneTexture");
        materialNames.push_back("M_Lighting+DiffuseMap+LightMap");
        //amount of entities to display
        const int entityNumber = materialNames.size();
        SceneNode * nodes[entityNumber];
        for (int iter = 0; iter < entityNumber; iter++) {
            //the entity loaded from the Cube.mesh file
            Entity* entity = scene->createEntity("Cube.mesh");
            //get the material name
            const String& materialName = materialNames[iter];
            //set the material
            entity->setMaterialName(materialName);
            //create a scene node for the entity
            nodes[iter] = rootSceneNode->createChildSceneNode();
            //attach the entity
            nodes[iter]->attachObject(entity);
            //scale up node
            nodes[iter]->scale(Vector3(10, 10, 10));
            //move nodes so they don't overlap
            float offset = (float(1 + iter * 2) - (float(entityNumber)))*15;
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
