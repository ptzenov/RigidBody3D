#ifndef _LISTENERS_HPP_
#define _LISTENERS_HPP_

#include <Ogre.h>
#include <ois/OIS.h>
#include <vector>

#include <sim/simulationEngine.hpp>


class ObjectListener:public Ogre::FrameListener
{
	private:
		Ogre::SceneNode* objectNode;
		Engine engine;
	public:
	        ObjectListener(Ogre::SceneNode* nde);	
		bool frameStarted(const Ogre::FrameEvent & evt);
};


enum controllerType {GENERAL,MOTION,CAMERA};

/**
 * Input controller class!
 * Keyboard and mouse control for the object. Uses the OIS library. Caveat-> OIS allows only one listener
 * per mouse keyboard or joystick!
 *
 */
class InputListener: public Ogre::FrameListener
{
public:
        InputListener(Ogre::RenderWindow* win, Ogre::SceneNode* nde = nullptr);
        // this is the method launched at framestarted! Must return ture to continue; otherwise exit
        bool frameStarted(const Ogre::FrameEvent & evt); //
	// select which controller to attach to the current node
	// and at which mode
        void registerController(controllerType ct,size_t mode = 0);
        ~InputListener();
private:
        
	bool motionControl(const Ogre::FrameEvent & evt,size_t mode);
        bool mouseControl(const Ogre::FrameEvent & evt,size_t mode);
        bool cameraControl(const Ogre::FrameEvent & evt,size_t mode);
        bool generalControl(const Ogre::FrameEvent& evt,size_t mode);
	
	// singleton input manager --> due to OIS limitations
	static OIS::InputManager* getInputManager(size_t win_handle)
	{
		static OIS::InputManager* input_manager = OIS::InputManager::createInputSystem(win_handle);
		return input_manager;
	}
	// singleton keyboard --> due to OIS limitations 
	static OIS::Keyboard* getKeyboard(OIS::InputManager* input_manager)
	{
		static OIS::Keyboard* keyboard = static_cast<OIS::Keyboard*> (input_manager->createInputObject(OIS::OISKeyboard,false));	
		return keyboard;
	}
        
	// singleton mouse --> due to OIS limitations
	static OIS::Mouse* getMouse(OIS::InputManager* input_manager)
	{
		static OIS::Mouse* mouse = static_cast<OIS::Mouse*> (input_manager->createInputObject(OIS::OISMouse,false));	
		return mouse;
	}

	size_t window_handle;
        Ogre::SceneNode* node;
	std::vector<size_t> controller_modes;
	
        using controllerFunc = bool (InputListener::*)(const Ogre::FrameEvent& evt, size_t);
        std::vector<controllerFunc> controllers_v;

};

#endif



