#ifndef __Common_H__
#define __Common_H__
// osg
#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/TexGen>
#include <osg/TexEnv>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/LineSegment>
#include <osg/NodeCallback> 
#include <osg/ShapeDrawable>
#include <osg/Transform>
#include <osg/AutoTransform>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
// osgviewer
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
// osgDB
#include <osgDB/ReadFile>
// osgUtil
#include <osgUtil/Optimizer>
#include <osgUtil/IntersectVisitor>
#include <osgUtil/LineSegmentIntersector>
// osgGA
#include <osgGA/GUIEventHandler>
#include <osgGA/CameraManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/TerrainManipulator>
// osgFX
#include <osgFX/Scribe>

// std include
#include <iostream>
#include <fstream>
#include <string>
#include <map>

// macro define
#define log() Common::Log() \
			 << " file: " << __FILE__ << \
				" line: " << __LINE__ << "] "

class Common
{
public:
	enum TRANSFORM{
		T,//Transform,
		AT,//AutoTransform,
		MT,//MatrixTransform,
		PAT//PositionAttitudeTransform
	};

	// ����һ������λ�ñ任�Ľڵ�
	static osg::Transform* CreateNode(osg::Node* node, Common::TRANSFORM t = Common::PAT);
	// ����һ��ͼƬ
	static osg::ref_ptr<osg::StateSet> LoadImage(const std::string& filename);
	// ����һ��ģ��
	static osg::ref_ptr<osg::Node> LoadModel(const std::string modelName, std::string tag = "");
	// ����һ��ģ��
	static osg::ref_ptr<osg::Node> FindModel(const std::string modelName);
	// ɾ��һ��ģ��
	static void DelModel(const std::string modelName);
	// ���һ��ģ�ͻ��߽ڵ�
	static bool AddModel(osg::ref_ptr<osg::Node>& node, std::string tag);
	// ����һ������
	static osg::ref_ptr<osg::Geode> CreateSphere(osg::Vec3 pos, float radius = 0.2f);
	// ��viewer��(x,y)��Ļ���귢������
	static osgUtil::LineSegmentIntersector::Intersections* Pick(float x, float y, osgViewer::Viewer* viewer);
	// ��־��Ϣ
	static std::fstream& Log();
private:
	static std::map<std::string, osg::ref_ptr<osg::Node>> models_;
	static std::fstream log_;
};

#endif