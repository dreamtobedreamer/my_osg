#include "PickHandler.h"

bool PickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::PUSH:
		if (ea.getButton() == 1)
		{
			Common::Pick(ea.getX(), ea.getY(),viewer_);
		}
		break;
	}
	return false;
}