#include <graphics/listeners.hpp>
#include <common.hpp>

/*---------------------- Object Listener -------------------------*/
ObjectListener::ObjectListener(Ogre::SceneNode* nde): objectNode(nde), engine{}
{
        ;
}

bool ObjectListener::frameStarted(const Ogre::FrameEvent& evt)
{
	float dt = evt.timeSinceLastFrame;
	engine.set_dt(dt);	
	engine.move();
	objectNode->setPosition(engine.get_X(),engine.get_Y(),engine.get_Z());
	float rad = 1./180.*3.1415; 
	
	if(engine.get_yaw())
		objectNode->yaw(Ogre::Radian(rad));
	if(engine.get_pitch())
		objectNode->pitch(Ogre::Radian(rad));
	if(engine.get_roll())
		objectNode->roll(Ogre::Radian(rad));
	return true;
}

/*------------------------------ INPUT LISteNER ----------------*/
InputListener::InputListener(Ogre::RenderWindow* wdow, Ogre::SceneNode* nde)
        :
        window_handle (0),
        node {nde},
     controller_modes(0),
     controllers_v(0)
{
        // create OIS objects
        wdow->getCustomAttribute("WINDOW",&window_handle);
}

InputListener::~InputListener()
{
        ; // static variables will be destroyed at the end of the app!
}

void InputListener::registerController(controllerType ct,
                size_t mode)
{

        switch(ct)
        {
        case GENERAL:
        {
                controllers_v.push_back(&InputListener::generalControl);
                controller_modes.push_back(mode);
                break;
        }
        case MOTION:
        {
                controllers_v.push_back(&InputListener::motionControl);
                controller_modes.push_back(mode);
                break;
        }
        case CAMERA:
        {
                //controllers_v.push_back(&InputListener::mouseControl);
                controllers_v.push_back(&InputListener::cameraControl);
                controller_modes.push_back(mode);
                break;
        }
        default:
        {
                ;
        }
        }
}

bool InputListener::motionControl(const Ogre::FrameEvent& evt,size_t mode)
{

        assert( node != nullptr);

        // W-A-S-D controls
        OIS::Keyboard* keyboard = InputListener::getKeyboard(InputListener::getInputManager(window_handle));
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

bool InputListener::cameraControl(const Ogre::FrameEvent& evt,size_t mode)
{
        assert(node != nullptr);

        // ToDo: Inprove camera control!
        OIS::Keyboard* keyboard = InputListener::getKeyboard(InputListener::getInputManager(window_handle));
        keyboard->capture();
	float rotY = 0. ; 
	float rotX = 0. ;
	float step = 1./180.*3.1415; 

	if (keyboard->isKeyDown(OIS::KC_UP))
		rotX+= step;
	if (keyboard->isKeyDown(OIS::KC_DOWN))
		rotX-=step;
	if (keyboard->isKeyDown(OIS::KC_LEFT))
		rotY+=step;
	if (keyboard->isKeyDown(OIS::KC_RIGHT))
		rotY-=step;       

	if (mode != 0)
        {
                rotX *=-1;
                rotY *=-1;
        }
        node->yaw(Ogre::Radian(rotY)); // around Y axis
        node->pitch(Ogre::Radian(rotX)); // around X axis

        return true;
}




bool InputListener::mouseControl(const Ogre::FrameEvent& evt,size_t mode)
{
        assert(node != nullptr);

        // ToDo: Inprove camera control!
        OIS::Mouse* mouse = InputListener::getMouse(InputListener::getInputManager(window_handle));
        mouse->capture();
        float rotX = mouse->getMouseState().X.rel * evt.timeSinceLastFrame*-1;
        float rotY = mouse->getMouseState().Y.rel * evt.timeSinceLastFrame*-1;

        if (mode != 0)
        {
                rotX *=-1;
                rotY *=-1;
        }
        node->yaw(Ogre::Radian(rotX)); // around Y axis
        node->pitch(Ogre::Radian(rotY)); // around X axis
        return true;
}

bool InputListener::generalControl(const Ogre::FrameEvent& evt,size_t mode)
{
        OIS::Keyboard* keyboard = InputListener::getKeyboard(InputListener::getInputManager(window_handle));
        keyboard->capture();
        if (keyboard->isKeyDown(OIS::KC_ESCAPE))
                return false;
        return true;
}

bool InputListener::frameStarted(const Ogre::FrameEvent & evt)
{
        assert( controllers_v.size() == controller_modes.size() );
        for(size_t idx =0 ; idx< controllers_v.size(); idx++)
                if( (this->*controllers_v[idx])(evt,controller_modes[idx]) == false) // calling a pointer to member of this has a funny syntax
                        return false;
        return true;
}











