#ifndef __Roam_H__
#define __Roam_H__
#include "Common.h"

class Roam : public osgGA::CameraManipulator
{
public:
	Roam();
	~Roam(){}
public:
	void SetCollision(bool bCollision);           // �Ƿ�����ײ
	bool GetCollision();                          // �����ײ��״̬
	void SwitchCollision();                       // ת����ײ״̬
	void setNode(osg::Node*) override;             // ���ü��Ľڵ�
	void setByMatrix(const osg::Matrix& matrix) override{}
	void setByInverseMatrix(const osg::Matrixd& matrix) override{}
	osg::Matrixd getMatrix() const override;
	osg::Matrixd getInverseMatrix() const override;
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override;

public:
	float angle_;                          // ��Ļ�Ƕ�
	void ChangePosition(osg::Vec3& delta); // λ�ñ任����
	//float GetSpeed();                      // ��õ�ǰ�ٶ�
	//void SetSpeed(float);                  // ���õ�ǰ�ٶ�
	void SetPosition(osg::Vec3& pos);      // �����Ե�λ��
	void SetPosition(double*);
	osg::Vec3 GetPosition();               // ��õ�ǰ�ӵ��λ��
	void ComputeHomePosition();            // ����ҵ�λ��
	
private:
	osg::ref_ptr<osg::Node> node_;         // �ڵ�ֵ������������ײ���
	unsigned int camID_;                   // ���������
	float speed_;                          // �ٶ�
	osg::Vec3 pos_;                        // λ��
	osg::Vec3 rotation_;                   // ��ת
	bool bLeftButtonDown_;                 // ����Ƿ���
	bool bIsCollision;                     // ��ײ��⿪��״̬��ѯ
	float pushX_;                          // �������ʱ����Ļ����
	float pushY_;                          // ��Ļ����
};

#endif