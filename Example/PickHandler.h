#ifndef __PickHandler_H__
#define __PickHandler_H__

#include "Common.h"

class PickHandler : public osgGA::GUIEventHandler
{
public:
	PickHandler(osgViewer::Viewer* viewer)
		: viewer_(viewer){}
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
private:
	osgViewer::Viewer* viewer_;
};


#endif