#include "MyHandler.h"

bool MyHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (ea.getKey() == osgGA::GUIEventAdapter::KEY_J)
	{
		std::cout << "key j down..." << std::endl;
		if (model_)
			model_->setStateSet(Common::LoadImage(filenames[getIndex()]));
	}
	return false;
}

