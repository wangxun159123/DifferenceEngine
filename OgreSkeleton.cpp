#include "OgreSkeleton.h"

OgreSkeleton::OgreSkeleton(const String title) {
    //init root
    LogManager * logManager = new LogManager();
    logManager->createLog("DifferenceEngine.log", true, false, false);
    root.reset((new Root("", "", "")));
    //load plugins, if in debug mode append _d to each plugin name before loading
    {
        std::vector<String> pluginNames;
        pluginNames.push_back("RenderSystem_GL");
        pluginNames.push_back("Plugin_ParticleFX");
        pluginNames.push_back("Plugin_CgProgramManager");
        pluginNames.push_back("Plugin_OctreeSceneManager");
        std::vector<String>::iterator iter = pluginNames.begin();
        std::vector<String>::iterator iterEnd = pluginNames.end();
        for (; iter != iterEnd; iter++) {
            String pluginName = *iter;
            bool debugMode = OGRE_DEBUG_MODE;
            if (debugMode) {
                pluginName.append("_d");
            }
            root->loadPlugin(pluginName);
        }
    }
    //Get available render systems and set the first one to be our render system
    {
        const RenderSystemList& renderSystemList = root->getAvailableRenderers();
        if (renderSystemList.size() == 0) {
            throw new Exception(29, "Failed to find any render systems", "OgreSkeleton.cpp");
        }
        RenderSystem* renderSystem = renderSystemList[0];
        //fix for nvidia drivers on linux
        renderSystem->setConfigOption("RTT Preferred Mode", "PBuffer");
        ConfigOptionMap& currentRendererOptions = renderSystem->getConfigOptions();
        ConfigOptionMap::iterator configItr = currentRendererOptions.begin();
        String resolution;
        while (configItr != currentRendererOptions.end()) {
            if ((configItr)->first == "Video Mode") {
                // Store Available Resolutions
                //foundResolutions = ((configItr)->second.possibleValues);
                resolution = ((configItr)->second.currentValue);
            }
            configItr++;
        }
        String::iterator it;
        String x;
        String y;
        for (it = resolution.begin(); it < resolution.end(); it++) {
            if (*it == ' ') {
                break;
            }
            char cr = *it;
            x += cr;
        }
        it += 3;
        for (; it < resolution.end(); it++) {
            char cr = *it;
            y += cr;
        }
        width = atoi(x.c_str());
        height = atoi(y.c_str());
        root->setRenderSystem(renderSystem);
    }
    //open the window
    window = NULL;
    {
        root->initialise(false, "", "");
        NameValuePairList params;
        params ["FSAA"] = "0";
        params ["vsync"] = true;
        window = root->createRenderWindow(title, width, height, true, &params);
    }
}