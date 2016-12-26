#ifndef __SphereCallback_H__
#define __SphereCallback_H__
#include "Common.h"

class SphereCallback : public osg::NodeCallback
{
public:
	void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		//��������ת���ڵ�
		osg::ref_ptr<osg::MatrixTransform> mt = dynamic_cast<osg::MatrixTransform*>(node);
		//��������
		osg::Matrixd mx;
		//����Z����ת
		//osg::; node->getParent();
		mx.makeRotate(angle_, osg::Vec3(1.0, 1.0, 1.0));
		//���þ���
		mt->setMatrix(mx);
		angle_ += 0.05;

		/*osg::ref_ptr<osg::PositionAttitudeTransform> pat = dynamic_cast<osg::PositionAttitudeTransform*>(node);
		pat->setPosition(osg::Vec3d(0,dis_,0));
		dis_ += 0.05;
		pat->getPosition();*/

		//��������
		traverse(node, nv);
	}
private:
	float angle_ = 0;
	double dis_ = 0;
};

#endif