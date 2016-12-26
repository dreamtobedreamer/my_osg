#ifndef __GameObject_H__
#define __GameObject_H__
#include "Common.h"

class GameObject : public osg::MatrixTransform, osg::PositionAttitudeTransform
{
public:
	GameObject();
	~GameObject();

	void AddChild(osg::Transform* tran)
	{
		//tran->computeLocalToWorldMatrix();
		//osg::Matrixd
	}
	void SetParent(osg::Transform*);
private:
};


#endif