#ifndef __NodeMove_H__
#define __NodeMove_H__
#include "Common.h"

class NodeMove : public osgGA::GUIEventHandler
{
public:
	NodeMove(osg::Node* node)
	{
		node_ = dynamic_cast<osg::MatrixTransform*>(node);
		pos_[0] = 0;
		pos_[1] = 0;
		pos_[2] = 0;
		angle_ = 0;
	}
	~NodeMove(){}

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		switch (ea.getKey())
		{
		case osgGA::GUIEventAdapter::KEY_Up:
			++pos_[2];
			std::cout << angle_ << std::endl;
			rot_.makeRotate(osg::Quat(angle_+=0.1f,osg::Vec3(1,0,0)));
			// rot*pos 先平移后旋转
			// pos*rot 先旋转后(根据旋转后的坐标进行平移)
			node_->setMatrix(osg::Matrix::translate(pos_)*rot_);
			break;
		case osgGA::GUIEventAdapter::KEY_Down:
			--pos_[2];
			node_->setMatrix(osg::Matrix::translate(pos_));
			break;
		case osgGA::GUIEventAdapter::KEY_Left:
			--pos_[0];
			node_->setMatrix(osg::Matrix::translate(pos_));
			break;
		case osgGA::GUIEventAdapter::KEY_Right:
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