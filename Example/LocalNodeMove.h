#ifndef __LocalNodeMove_H__
#define __LocalNodeMove_H__
#include "Common.h"

class LocalNodeMove : public osgGA::GUIEventHandler
{
public:
	LocalNodeMove(osg::Node* node)
	{
		node_ = dynamic_cast<osg::MatrixTransform*>(node);
		pos_[0] = 0;
		pos_[1] = 0;
		pos_[2] = 0;
		angle_ = 0;
	}
	~LocalNodeMove(){}

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		switch (ea.getKey())
		{
		case osgGA::GUIEventAdapter::KEY_W:
			++pos_[2];
			node_->setMatrix(osg::Matrix::translate(pos_)*rot_);
			break;
		case osgGA::GUIEventAdapter::KEY_S:
			--pos_[2];
			node_->setMatrix(osg::Matrix::translate(pos_));
			break;
		case osgGA::GUIEventAdapter::KEY_A:
			--pos_[0];
			node_->setMatrix(osg::Matrix::translate(pos_));
			break;
		case osgGA::GUIEventAdapter::KEY_D:
			++pos_[0];
			node_->setMatrix(osg::Matrix::translate(pos_));
			break;
		default:
			break;
		}
		return false;
	}
private:
	osg::MatrixTransform* node_;
	osg::Vec3f pos_;
	osg::Matrix rot_;
	float angle_;
};

#endif