#ifndef _INPUTS_HPP_
#define _INPUTS_HPP_

#include <Ogre.h>
#include <ois/OIS.h>

#include <vector>

enum controllerType {GENERAL,MOTION,CAMERA};
/**
 * Input controller class!
 * Keyboard and mouse control for the object. Uses the OIS library. Caveat-> OIS allows only one listener
 * per mouse keyboard or joystick!
 *
 */
class InputController: public Ogre::FrameListener
{
public:
        InputController(Ogre::RenderWindow* win, Ogre::SceneNode* nde = nullptr, Ogre::Camera* cam = nullptr);

        // this is the method launched at framestarted! Must return ture to continue; otherwise exit
        bool frameStarted(const Ogre::FrameEvent & evt); //
        void registerController(controllerType ct);
        ~InputController();
private:

        bool motionControl(const Ogre::FrameEvent & evt);
        bool cameraControl(const Ogre::FrameEvent & evt);
        bool generalControl(const Ogre::FrameEvent& evt);

	size_t windowHandle;
        Ogre::SceneNode* node;
        Ogre::Camera* camera;
       
	// singleton input manager --> due to OIS limitations
	static OIS::InputManager* get_input_manager(size_t win_handle)
	{
		static OIS::InputManager* input_manager = OIS::InputManager::createInputSystem(win_handle);
		return input_manager;
	}
	// singleton keyboard --> due to OIS limitations 
	static OIS::Keyboard* get_keyboard(OIS::InputManager* input_manager)
	{
		static OIS::Keyboard* keyboard = static_cast<OIS::Keyboard*> (input_manager->createInputObject(OIS::OISKeyboard,false));	
		return keyboard;
	}
        
	// singleton mouse --> due to OIS limitations
	static OIS::Mouse* get_mouse(OIS::InputManager* input_manager)
	{
		static OIS::Mouse* mouse = static_cast<OIS::Mouse*> (input_manager->createInputObject(OIS::OISMouse,false));	
		return mouse;
	}

        using controller = bool (InputController::*)(const Ogre::FrameEvent& evt);
        std::vector<controller> controllers_v;
};




#endif



