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

	// 创建一个可以位置变换的节点
	static osg::Transform* CreateNode(osg::Node* node, Common::TRANSFORM t = Common::PAT);
	// 加载一个图片
	static osg::ref_ptr<osg::StateSet> LoadImage(const std::string& filename);
	// 加载一个模型
	static osg::ref_ptr<osg::Node> LoadModel(const std::string modelName, std::string tag = "");
	// 查找一个模型
	static osg::ref_ptr<osg::Node> FindModel(const std::string modelName);
	// 删除一个模型
	static void DelModel(const std::string modelName);
	// 添加一个模型或者节点
	static bool AddModel(osg::ref_ptr<osg::Node>& node, std::string tag);
	// 创建一个球体
	static osg::ref_ptr<osg::Geode> CreateSphere(osg::Vec3 pos, float radius = 0.2f);
	// 从viewer的(x,y)屏幕坐标发出射线
	static osgUtil::LineSegmentIntersector::Intersections* Pick(float x, float y, osgViewer::Viewer* viewer);
	// 日志信息
	static std::fstream& Log();
private:
	static std::map<std::string, osg::ref_ptr<osg::Node>> models_;
	static std::fstream log_;
};

#endif