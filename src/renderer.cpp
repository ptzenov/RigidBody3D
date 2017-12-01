#include "renderer.hpp"
#include <iostream>

void SceneRenderer::create_plane(Ogre::Vector3 normal)
{
        Ogre::MeshManager::getSingleton().createPlane("plane",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                        Ogre::Plane(normal,-50), 1500,1500,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z);
	entities["plane"] = sceneMgr->createEntity("plane","plane");
	
	
	scene_graph["planeNode"] = rootNode->createChildSceneNode();
	scene_graph["planeNode"]->attachObject(entities["plane"]);
	entities["plane"]->setMaterialName("Examples/BeachStones"); // jpeg
}



void SceneRenderer::createScene()
{
        // create window and scene manager
        window = app_root->initialise(true,"testapp");
        sceneMgr = app_root->createSceneManager();
	rootNode = sceneMgr->getRootSceneNode();
        
	// manually add the resource group !!!
        Ogre::ResourceGroupManager::getSingleton().createResourceGroup("Blender");
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation( "/home/kenny/Documents/BlenderModels/", "FileSystem", "Blender");
        Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Blender");
        Ogre::ResourceGroupManager::getSingleton().loadResourceGroup("Blender");

        // setup the cameras["MainCam"]!
        cameras["MainCam"] = sceneMgr->createCamera("MainCam");
        cameras["MainCam"]->setPosition(Ogre::Vector3 {-100,100,300});
        cameras["MainCam"]->lookAt(Ogre::Vector3 {0,0,0});
        cameras["MainCam"]->setNearClipDistance(5);
        
        
	viewport = window->addViewport(cameras["MainCam"],0.0,0.0,0.0,1.0,1.0);
       
       	viewport->setBackgroundColour(Ogre::ColourValue(1,0,0));
        cameras["MainCam"]->setAspectRatio(
                Ogre::Real(viewport->getActualWidth()) /
                Ogre::Real(viewport->getActualHeight()));
	
	Ogre::Vector3 lightpos{0.0f,20.0f,0.0f};
	
	light_sources["PointLight"] =  sceneMgr->createLight("PointLight");
	light_sources["PointLight"]->setType(Ogre::Light::LT_POINT);
	light_sources["PointLight"]->setDiffuseColour(1.0,1.0,1.0); 
	light_sources["PointLight"]->setPosition(lightpos);

        // Create Scene
	create_plane();

	entities["ball"] = sceneMgr->createEntity("sphere.mesh");
	entities["ball"]->setCastShadows(true);
        
	scene_graph["ballNode"] = rootNode->createChildSceneNode();
	scene_graph["ballNode"]->setPosition(lightpos);
	scene_graph["ballNode"]->scale(0.1,0.1,0.1);
        scene_graph["ballNode"]->attachObject(entities["ball"]);

	// add shadows
	sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);	
	scene_created = true;
}

void SceneRenderer::renderScene()
{
        if( !scene_created)
                std::cout<<"\nCannot render scene before actually drawing it! \n";
        else
        {
                app_root->startRendering();
        }
}

void SceneRenderer::read_configs(Ogre::String filename)
{
        // load cfg file and add to resource manager!
        Ogre::ConfigFile cf;
        cf.load(filename);

        Ogre::String name, locType;
        Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

        while (secIt.hasMoreElements())
        {
                Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
                Ogre::ConfigFile::SettingsMultiMap::iterator it;

                for (it = settings->begin(); it != settings->end(); ++it)
                {
                        locType = it->first;
                        name = it->second;

                        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
                }
        }
        // change GPU?
        // Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
        // Initialise materials -> ogre fails here?
}








