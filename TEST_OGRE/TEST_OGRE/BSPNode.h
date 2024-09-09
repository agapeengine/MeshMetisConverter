#pragma once
#include"Ogre.h"

class BSPNode
{
    




   std::vector<Ogre::Polygon*>behing_plane;
   std::vector<Ogre::Polygon>before_plane;
    Ogre::Plane deviding_plane;
};
