#include "Roam.h"

Roam::Roam()
	: speed_(1.5f),
	bLeftButtonDown_(false),
	pushX_(0),
	angle_(2.5f),
	bIsCollision(false),
	pushY_(false)
{
	pos_ = osg::Vec3(0, 0, 5.0f);
	rotation_ = osg::Vec3(osg::PI_2, 0, 0);
}

osg::Matrixd Roam::getMatrix() const
{
	// 获得旋转后的矩阵(视口矩阵)
	/*osg::Matrixd mat;
	mat.makeRotate(
		rotation_[0], osg::Vec3(1,0,0),
		rotation_[1], osg::Vec3(0,1,0),
		rotation_[2], osg::Vec3(0, 0, 1)
		);
	return mat * osg::Matrixd::translate(pos_);*/
	return osg::Matrixd::identity();
}

osg::Matrixd Roam::getInverseMatrix(void) const
{
	osg::Matrixd mat;
	mat.makeRotate(rotation_[0], osg::Vec3(1, 0, 0),
		rotation_[1], osg::Vec3(0,1,0),
		rotation_[2], osg::Vec3(0,0,1));
	//mat.identity();
	return osg::Matrixd::inverse(osg::Matrixd::translate(pos_) * mat);
	//return osg::Matrixd::inverse(mat*osg::Matrixd::translate(pos_));
}

bool Roam::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa)
{
	float screenX = ea.getX();
	float sceeenY = ea.getY();
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::KEYDOWN:
		if (ea.getKey() == ' ')
		{
			aa.requestRedraw();
			aa.requestContinuousUpdate(false);
			return true;
		}
		if (ea.getKey() == 0xff50)// home
		{
			ChangePosition(osg::Vec3(0, 0, speed_));
			return true;
		}
		if (ea.getKey() == 0xff57)// end
		{
			ChangePosition(osg::Vec3(0, 0, -speed_));
			return true;
		}
		if (ea.getKey() == 0x2b)// +
		{
			speed_ += 1.0f;
			return true;
		}
		if (ea.getKey() == 0x2d)// -
		{
			speed_ -= 1.0f;
			if (speed_ < 1.0f)
				speed_ = 1.0f;
			return true;
		}
		if (ea.getKey() == 0xff52 || ea.getKey() == 0x57 || ea.getKey() == 0x77) // up
		{
			ChangePosition(osg::Vec3(0, speed_*sinf(osg::PI_2 + rotation_[2]),0));
			ChangePosition(osg::Vec3(speed_ * cosf(osg::PI_2 + rotation_[2]), 0,0));
			return true;
		}
	}
	return true;
}

void Roam::ChangePosition(osg::Vec3& delta)
{
	if (bIsCollision)
	{
		osg::Vec3 newPos = pos_ + delta;
		osgUtil::IntersectVisitor iv;
		// 前后的线段
		osg::ref_ptr<osg::LineSegment> line = new osg::LineSegment(newPos, pos_);
		// 上下移动的线段
		osg::ref_ptr<osg::LineSegment> lineZ = new osg::LineSegment(newPos + osg::Vec3(0, 0, speed_),
			newPos - osg::Vec3(0,0,speed_));
		iv.addLineSegment(line.get());
		iv.addLineSegment(lineZ.get());
		// 接受碰撞检测
		node_->accept(iv);
		if (!iv.hits())
		{
			// 如果没有碰撞，则移动就位置到新位置
			pos_ += delta;
		}

	}
	else
	{// 没开检测碰撞则直接过去
		pos_ += delta;
	}
}

void Roam::SetPosition(osg::Vec3& pos)
{
	pos_ = pos;
}

void Roam::SetPosition(double* pos)
{
	pos_[0] = pos[0];
	pos_[1] = pos[1];
	pos_[2] = pos[2];
}

osg::Vec3 Roam::GetPosition()
{
	return pos_;
}

void Roam::setNode(osg::Node* node)
{
	node_ = node;
}

void Roam::ComputeHomePosition()
{
	if (node_.get())
	{
		const osg::BoundingSphere & boundindSphere = node_->getBound();
		osg::Vec3 bp = boundindSphere._center;
		SetPosition(bp);
	}
}

void Roam::SetCollision(bool bCollision)
{
	bIsCollision = bCollision;
}

bool Roam::GetCollision()
{
	return bIsCollision;
}

void Roam::SwitchCollision()
{
	bIsCollision = !bIsCollision;
}

