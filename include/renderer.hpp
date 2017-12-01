#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <Ogre.h>

#include <ois/OIS.h>

#include <memory>
#include <map>


class SceneRenderer
{
public:
        // constructor
        SceneRenderer(std::string appName,
                      std::string res = "resources.cfg", std::string plugin = "plugins.cfg",
                      std::string config = "ogre.cfg", std::string log  = "Ogre.log"):
                app_root {new Ogre::Root(plugin,config,log)},
        scene_graph {}, entities {}, cameras {}, light_sources {},  resources {res}, app_name {appName}, scene_created {false}
        {
                read_configs(resources);
                app_root->showConfigDialog(NULL);
        }

        void createScene();
        void renderScene();

private:

        void read_configs(Ogre::String filename);
        void create_plane(Ogre::Vector3 normal = Ogre::Vector3::UNIT_Y);

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


class InputController: public Ogre::FrameListener
{
public:
	InputController(Ogre::SceneNode* nde, Ogre::RenderWindow* win);
	// this is the method launched at framestarted! Must return ture to continue; otherwise exit  
	bool frameStarted(const Ogre::FrameEvent & evt); // evt.timeSinceLastFrame
	~InputController();

private:
	Ogre::RenderWindow* window; 
        Ogre::SceneNode* node; // listens to events at this node!
	OIS::InputManager* input_manager;
	OIS::Keyboard* keyboard;
};

#endif




