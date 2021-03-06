#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <Ogre.h>

#include <memory>
#include <map>

#include <graphics/listeners.hpp>
#include <sim/simulationEngine.hpp>
#include <string>



class SceneRenderer
{
public:
        // constructor
        SceneRenderer(std::string appName,
                      std::string res = "resources.cfg", std::string plugin = "plugins.cfg",
                      std::string config = "ogre.cfg", std::string log  = "Ogre.log"):
        app_root {new Ogre::Root(plugin,config,log)},
        scene_graph {}, entities {}, cameras {}, light_sources {},  resources {res}, app_name {appName}
        {
                readConfigs(resources);
                app_root->showConfigDialog(NULL);
		scene_created = false;
        }

        void createScene();
        void renderScene();

private:

        void readConfigs(Ogre::String filename);
        void createPlane(Ogre::Vector3 normal = Ogre::Vector3::UNIT_Y);

        std::unique_ptr<Ogre::Root> app_root;

        Ogre::RenderWindow* window;
        Ogre::SceneManager* sceneMgr;
        Ogre::Viewport* viewport;
        Ogre::SceneNode* rootNode;

        std::map<std::string,Ogre::SceneNode*> scene_graph;
        std::map<std::string,Ogre::Entity*> entities;
        std::map<std::string,Ogre::Camera*> cameras;
        std::map<std::string,Ogre::Light*> light_sources;

        std::map<std::string,std::unique_ptr<Ogre::FrameListener>> frame_listeners;

        Ogre::String resources;
        Ogre::String app_name;
	bool scene_created; 


};


#endif





