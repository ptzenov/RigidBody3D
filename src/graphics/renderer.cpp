#include <graphics/renderer.hpp>
#include <common.hpp>
#include <iostream>

void SceneRenderer::createPlane(Ogre::Vector3 normal)
{
        Ogre::MeshManager::getSingleton().createPlane("plane",
                        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                        Ogre::Plane(normal,-50), 1500,1500,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z);
        entities["plane"] = sceneMgr->createEntity("plane","plane");

        scene_graph["planeNode"] = rootNode->createChildSceneNode();
        scene_graph["planeNode"]->attachObject(entities["plane"]);
}

void SceneRenderer::createScene()
{
        // create window and scene manager
        window = app_root->initialise(true,app_name);
        sceneMgr = app_root->createSceneManager();
        rootNode = sceneMgr->getRootSceneNode();

        /**
        * Manually add the resource group
        */
        Ogre::ResourceGroupManager::getSingleton().createResourceGroup("Blender");
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation( "../meshes/",
                        "FileSystem", "Blender");
        Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Blender");
        Ogre::ResourceGroupManager::getSingleton().loadResourceGroup("Blender");

        rootNode->setPosition(Ogre::Vector3 {0.0f,0.0f,0.0f});

        // setup the camera(s)
        cameras["MainCam"] = sceneMgr->createCamera("MainCam");
        cameras["MainCam"]->lookAt(Ogre::Vector3 {0,0,0});
        cameras["MainCam"]->setNearClipDistance(5);

        viewport = window->addViewport(cameras["MainCam"],0.0,0.0,0.0,1.0,1.0);
        viewport->setBackgroundColour(Ogre::ColourValue(.324,.1534,.1123));
        cameras["MainCam"]->setAspectRatio(
                Ogre::Real(viewport->getActualWidth()) /
                Ogre::Real(viewport->getActualHeight()));

        scene_graph["cameraNode"] = rootNode->createChildSceneNode();
        scene_graph["cameraNode"]->setPosition(Ogre::Vector3 {0.,0.,300.});
        scene_graph["cameraNode"]->attachObject(cameras["MainCam"]);

//        createPlane();
        light_sources["DirLight"] = sceneMgr->createLight("DirLigth");
        light_sources["DirLight"]->setType(Ogre::Light::LT_DIRECTIONAL);
        light_sources["DirLight"]->setDiffuseColour(1.,1.,1.0);
        light_sources["DirLight"]->setDirection(1.0f,-1.0f,0.0f);

        // create the ball
        entities["object"] = sceneMgr->createEntity("Sphere.mesh");
        entities["object"]->setCastShadows(true);

        // ball node!
        scene_graph["objectNode"] = rootNode->createChildSceneNode();
        scene_graph["objectNode"]->setPosition(0.0,0.0,0.0); // this is the position inside the parent node!
        scene_graph["objectNode"]->setScale(20,20,20); // this sets the scale of the mesh
        scene_graph["objectNode"]->attachObject(entities["object"]);

        /* control listeners */
        frame_listeners["rootListener"] = std::unique_ptr<Ogre::FrameListener>(
                        new InputListener(window,scene_graph["cameraNode"]));
        static_cast<InputListener*>(frame_listeners["rootListener"].get())
        ->registerController(GENERAL,0);
        static_cast<InputListener*>(frame_listeners["rootListener"].get())
        ->registerController(CAMERA,0);
        static_cast<InputListener*>(frame_listeners["rootListener"].get())
        ->registerController(MOTION,0);

        app_root->addFrameListener(frame_listeners["rootListener"].get());

        frame_listeners["objectListener"] = std::unique_ptr<Ogre::FrameListener>(
                        new ObjectListener(scene_graph["objectNode"]));
        app_root->addFrameListener(frame_listeners["objectListener"].get());

        // add shadows
        sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
        DBG_MSG("Scene created",__FILE__,__LINE__);
        scene_created = true;
}


void SceneRenderer::renderScene()
{
        if( !scene_created)
                std::cout<<"\nCannot render scene before actually drawing it! \n";
        else
                app_root->startRendering();
}

void SceneRenderer::readConfigs(Ogre::String filename)
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







