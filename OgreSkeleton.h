/* 
 * File:   OgreSkeleton.h
 * Author: samuel
 *
 * Created on 04 March 2013, 18:50
 */

#ifndef OGRESKELETON_H
#define	OGRESKELETON_H
#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include <memory>
#include <exception>
using namespace Ogre;
class OgreSkeleton{
public:
    //Ogre::root object, lots of things used in OGRE are in this class
    std::auto_ptr<Root> root;
    //The window object
    Ogre::RenderWindow* window;
    //constructor
    OgreSkeleton(String title);
    //dimensions of window
    unsigned int width;
    unsigned int height;
};


#endif	/* OGRESKELETON_H */