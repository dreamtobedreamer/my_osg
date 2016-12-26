#include "Common.h"

std::map<std::string, osg::ref_ptr<osg::Node>> Common::models_;
std::fstream Common::log_("mylog.txt",std::ios::app|std::ios::out);

std::fstream& Common::Log()
{ 
	log_ << std::endl; 
	log_ << "[" << __DATE__ << " " << __TIME__;
	return log_; 
}

osgUtil::LineSegmentIntersector::Intersections* Common::Pick(float x, float y, osgViewer::Viewer* viewer)
{
	// 创建一个存储线段相交集合的容器
	osgUtil::LineSegmentIntersector::Intersections* intersections = new osgUtil::LineSegmentIntersector::Intersections;
	// 判断是否有相交的点
	if (viewer->computeIntersections(x, y, *intersections))
	{
		for (osgUtil::LineSegmentIntersector::Intersections::iterator hiter = intersections->begin();
			hiter != intersections->end();
			++hiter)
		{
			if (!hiter->nodePath.empty() && !(hiter->nodePath.back()->getName().empty()))
			{
				//std::cout << hiter->nodePath.back()->getName() << std::endl;;
				// 获得vector<Node*>
				osg::NodePath np = hiter->nodePath;
				for (int i = np.size() - 1; i > 0; --i)
				{
					osgFX::Scribe* sc = dynamic_cast<osgFX::Scribe*>(np[i]);
					if (sc != NULL)
					{
						if (sc->getNodeMask() != 0)
						{
							sc->setNodeMask(0);
						}
							
					}
				}
			}
		}
		return intersections;
	}
	return NULL;
}

osg::ref_ptr<osg::Node> Common::LoadModel(const std::string modelName, std::string tag)
{
	tag = (tag == "") ? modelName : tag;
	std::map<std::string, osg::ref_ptr<osg::Node>>::iterator iter;
	if ((iter = models_.find(modelName)) == models_.end())
	{
		osgUtil::Optimizer optimizer; //模型优化
		osg::Node* model = osgDB::readNodeFile(modelName);
		optimizer.optimize(model);
		models_.insert(std::pair<std::string, osg::ref_ptr<osg::Node>>(tag, model));
		return model;
	}
	else
	{
		return iter->second.get();
	}
}

osg::ref_ptr<osg::Node> Common::FindModel(const std::string modelName)
{
	std::map<std::string, osg::ref_ptr<osg::Node>>::iterator iter;
	if ((iter = models_.find(modelName)) == models_.end())
	{
		return nullptr;
	}
	else
	{
		return iter->second.get();
	}
}

void Common::DelModel(const std::string modelName)
{
	auto iter = models_.find(modelName);
	if (iter == models_.end())
		models_.erase(iter);
}

bool Common::AddModel(osg::ref_ptr<osg::Node>& node, std::string tag)
{
	if (models_.find(tag) == models_.end())
	{
		models_.insert(std::pair<std::string, osg::ref_ptr<osg::Node>>(tag, node));
		return true;
	}
	return false;
}

osg::Transform* Common::CreateNode(osg::Node* node, Common::TRANSFORM t)
{
	osg::Transform* tt;
	switch (t)
	{
	case Common::T:
		tt = new osg::Transform();
		tt->addChild(node);
		break;
	case Common::AT:
		tt = new osg::AutoTransform();
		tt->addChild(node);
		break;
	case Common::MT:
		tt = new osg::MatrixTransform();
		tt->addChild(node);
		break;
	case Common::PAT:
		tt = new osg::PositionAttitudeTransform();
		tt->addChild(node);
		break;
	default:
		return nullptr;
		break;
	}
	return tt;
}

osg::ref_ptr<osg::StateSet> Common::LoadImage(const std::string& filename)
{
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile(filename);
	if (!image)
	{
		std::cout << "load  :  " << filename << "..." << std::endl;
		std::cout << "error load image" << std::endl;
		return nullptr;
	}
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
	texture->setImage(image.get());
	// 设置自动生成纹理坐标
	osg::ref_ptr<osg::TexGen> texgen = new osg::TexGen();
	texgen->setMode(osg::TexGen::SPHERE_MAP);
	// 设置纹理环境，模式为DECAL
	osg::ref_ptr<osg::TexEnv> texenv = new osg::TexEnv();
	texenv->setMode(osg::TexEnv::Mode::DECAL);
	texenv->setColor(osg::Vec4(.6, .6, .6, 1));
	// 启动单元一自动生成纹理坐标，并使用纹理
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;
	stateset->setTextureAttributeAndModes(1, texture.get(), osg::StateAttribute::ON);
	stateset->setTextureAttributeAndModes(1, texgen.get(), osg::StateAttribute::ON);
	stateset->setTextureAttribute(1, texenv.get());

	return stateset.get();
}

osg::ref_ptr<osg::Geode> Common::CreateSphere(osg::Vec3 pos, float radius)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(pos, radius);
	osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(sphere.get());
	geode->addDrawable(sd.get());
	return geode.get();
}