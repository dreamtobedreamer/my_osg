#ifndef __Roam_H__
#define __Roam_H__
#include "Common.h"

class Roam : public osgGA::CameraManipulator
{
public:
	Roam();
	~Roam(){}
public:
	void SetCollision(bool bCollision);           // 是否开启碰撞
	bool GetCollision();                          // 获得碰撞的状态
	void SwitchCollision();                       // 转换碰撞状态
	void setNode(osg::Node*) override;             // 设置检测的节点
	void setByMatrix(const osg::Matrix& matrix) override{}
	void setByInverseMatrix(const osg::Matrixd& matrix) override{}
	osg::Matrixd getMatrix() const override;
	osg::Matrixd getInverseMatrix() const override;
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override;

public:
	float angle_;                          // 屏幕角度
	void ChangePosition(osg::Vec3& delta); // 位置变换函数
	//float GetSpeed();                      // 获得当前速度
	//void SetSpeed(float);                  // 设置当前速度
	void SetPosition(osg::Vec3& pos);      // 设置试点位置
	void SetPosition(double*);
	osg::Vec3 GetPosition();               // 获得当前视点的位置
	void ComputeHomePosition();            // 计算家的位置
	
private:
	osg::ref_ptr<osg::Node> node_;         // 节点值，用来测试碰撞检测
	unsigned int camID_;                   // 相机操作器
	float speed_;                          // 速度
	osg::Vec3 pos_;                        // 位置
	osg::Vec3 rotation_;                   // 旋转
	bool bLeftButtonDown_;                 // 左键是否按下
	bool bIsCollision;                     // 碰撞检测开启状态查询
	float pushX_;                          // 左键按下时的屏幕坐标
	float pushY_;                          // 屏幕坐标
};

#endif