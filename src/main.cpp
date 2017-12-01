#include <Ogre.h>

#include "renderer.hpp"

#include <iostream>

#include  <memory>
#include <algorithm>


//! [main]
int main()
{

	SceneRenderer app{"RigidBody"}; 
	app.createScene();
	app.renderScene();
        return 0;
}



















