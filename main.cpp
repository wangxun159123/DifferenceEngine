//Opens a window, based off mad marx tutorial 2
//inlude our skeleton file
#include "OgreSkeleton.h"

//main method

int main() {
	try {
		OgreSkeleton* skeleton = new OgreSkeleton("Difference Engine");
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
