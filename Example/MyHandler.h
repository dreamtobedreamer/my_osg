#ifndef __MyHandler_H__
#define __MyHandler_H__

#include "Common.h"

class MyHandler : public osgGA::GUIEventHandler
{
public:
	MyHandler(osg::ref_ptr<osg::Node>& model)
	{
		filenames[0] = "Resources/Images/dark_grey.tga";
		filenames[1] = "Resources/Images/red.tga";
		filenames[2] = "Resources/Images/skin.tga";
		index_ = 0;
		model_ = model;
	}
	bool handle(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&);
private:
	osg::ref_ptr<osg::Node> model_;
	std::string filenames[3];
	int getIndex() { return index_++% 3; }
	unsigned int index_;
};

#endif