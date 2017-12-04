#include "inputs.hpp"
#include "common.hpp"


/*------------------------------ INPUT CONTROLLER ----------------*/
InputController::InputController(Ogre::RenderWindow* wdow, Ogre::SceneNode* nde, Ogre::Camera* cam)
        :
	windowHandle (0),
	node {nde},
       camera {cam},
       controllers_v(0)
{
        // create OIS objects
        std::stringstream windowHndStr;
        wdow->getCustomAttribute("WINDOW",&windowHandle);
}

InputController::~InputController()
{
	; // static variables will be destroyed at the end of the app!
}

void InputController::registerController(controllerType ct)
{
        switch(ct)
        {
        case GENERAL:
        {
                controllers_v.push_back(&InputController::generalControl);
                break;
        }
        case MOTION:
        {
                controllers_v.push_back(&InputController::motionControl);
                break;
        }
        case CAMERA:
        {
                controllers_v.push_back(&InputController::cameraControl);
                break;
        }
        default:
        {
                ;
        }
        }
}

bool InputController::motionControl(const Ogre::FrameEvent& evt)
{
        // W-A-S-D controls
	OIS::Keyboard* keyboard = InputController::get_keyboard(InputController::get_input_manager(windowHandle)); 
	keyboard->capture();
	Ogre::Vector3 translate_v {0.0f,0.0f,0.0f};
        
	if(keyboard->isKeyDown(OIS::KC_S))
                translate_v += Ogre::Vector3 {0.,-5,0.};
        if(keyboard->isKeyDown(OIS::KC_A))
                translate_v += Ogre::Vector3 {-5,0.,0.};
        if(keyboard->isKeyDown(OIS::KC_W))
                translate_v += Ogre::Vector3 {0.,5.0f,0.};
        if(keyboard->isKeyDown(OIS::KC_D))
                translate_v += Ogre::Vector3 {5.,0.,0.};
        node->translate(translate_v);
	return true;

}

bool InputController::cameraControl(const Ogre::FrameEvent& evt)
{
        return true;
}

bool InputController::generalControl(const Ogre::FrameEvent& evt)
{
	OIS::Keyboard* keyboard = InputController::get_keyboard(InputController::get_input_manager(windowHandle)); 
	keyboard->capture();
        if (keyboard->isKeyDown(OIS::KC_ESCAPE))
                return false;
        return true;
}

bool InputController::frameStarted(const Ogre::FrameEvent & evt)
{
        for(auto c : controllers_v)
                if( (this->*c)(evt) == false) // calling a pointer to member of this has a funny syntax
                        return false;
        return true;
}




