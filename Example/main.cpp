#include "Common.h"
//#include "MyHandler.h" // main1
//#include "SphereCallback.h" // main1
//#include "PickHandler.h" // main2
#include "Roam.h" // main
#include "NodeMove.h" // main
#include "LocalNodeMove.h" // main

int main()
{
	osgViewer::Viewer viewer;
	osg::Group *root = new osg::Group;

	osg::Node* cessna = Common::CreateNode(osgDB::readNodeFile("Resources/cessna.ive"), Common::MT);
	cessna->setEventCallback(new NodeMove(cessna));

	osg::Node* avatar = Common::CreateNode(osgDB::readNodeFile("Resources/avatar.ive"), Common::MT);
	avatar->setEventCallback(new LocalNodeMove(avatar));
	
	root->addChild(cessna);
	root->addChild(avatar);
	viewer.setSceneData(root);
	
	//viewer.setCameraManipulator(new Roam());
	//osgGA::EventHandler;
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	return viewer.run();
}

// pick demo
//int main2()
//{
//	osgViewer::Viewer viewer;
//	osg::Group* root = new osg::Group();
//
//	osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("Resources/cessna.osg");
//
//	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile("Resources/cow.osg");
//	osg::ref_ptr<osgFX::Scribe> sc = new osgFX::Scribe();
//	sc->addChild(cow.get());
//
//	root->addChild(cow.get());
//	root->addChild(cessna.get());
//	root->addChild(sc.get());
//
//	viewer.setSceneData(root);
//	viewer.addEventHandler(new PickHandler(&viewer));
//	viewer.addEventHandler(new osgViewer::StatsHandler);
//	viewer.addEventHandler(new osgGA::StateSetManipulator);
//	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
//	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
//	return viewer.run();
//}
//
//
//int main1(int argc, char** argv)
//{
//	osg::ArgumentParser args(&argc, argv);
//	args.getApplicationUsage()->setApplicationName(args.getApplicationName());
//	args.getApplicationUsage()->setDescription(
//		args.getApplicationName() + " is the standard OpenSceneGraph example");
//	args.getApplicationUsage()->setCommandLineUsage("no usage haha...");
//	args.getApplicationUsage()->addCommandLineOption("--image <filename>","load image");
//	
//	if (args.read("--image"))
//	{
//		std::cout << "image option" << std::endl;
//	}
//
//
//
//	osgViewer::Viewer viewer;
//	osg::Group* root = new osg::Group();
//	
//	// 模型
//	osg::ref_ptr<osg::Node> model = Common::LoadModel("Resources/glider.osg");//osgDB::readNodeFile("Resources/glider.osg");
//
//	osg::ref_ptr<osg::PositionAttitudeTransform> mtx =
//		dynamic_cast<osg::PositionAttitudeTransform*>(Common::CreateNode(Common::LoadModel("Resources/glider.osg"), Common::PAT));
//	mtx->setPosition(osg::Vec3d(2, 2, 2));
//	if (!model)
//	{
//		std::cout << "error load model..." << std::endl;
//	}
//	root->addChild(model);
//	root->addChild(mtx);
//	// 圆球模型
//	osg::ref_ptr<osg::Node> sphere = Common::CreateSphere(osg::Vec3(0, 2, 0));
//	osg::ref_ptr<osg::MatrixTransform> mt = 
//		dynamic_cast<osg::MatrixTransform*>(Common::CreateNode(sphere, Common::MT));
//	/*osg::ref_ptr<osg::PositionAttitudeTransform> mt =
//		dynamic_cast<osg::PositionAttitudeTransform*>(Common::CreateNode(sphere, Common::PAT));*/
//	//mt->setUpdateCallback(new SphereCallback());
//	root->addChild(mt.get());
//	// 圆球模型2
//	osg::ref_ptr<osg::Node> sphere2 = Common::CreateSphere(osg::Vec3(0, 1, 0));
//	osg::ref_ptr<osg::MatrixTransform> mt2 =
//		dynamic_cast<osg::MatrixTransform*>(Common::CreateNode(sphere2, Common::MT));
//	/*osg::ref_ptr<osg::PositionAttitudeTransform> mt =
//	dynamic_cast<osg::PositionAttitudeTransform*>(Common::CreateNode(sphere, Common::PAT));*/
//	mt2->setUpdateCallback(new SphereCallback());
//	mt->addChild(mt2.get());
//	{
//		osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitch = new osgGA::KeySwitchMatrixManipulator;
//		keyswitch->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator());
//		keyswitch->addMatrixManipulator('2', "Trackball", new osgGA::FlightManipulator());
//		keyswitch->addMatrixManipulator('3', "Trackball", new osgGA::DriveManipulator);
//		keyswitch->addMatrixManipulator('4', "Trackball", new osgGA::TerrainManipulator());
//
//		new osgGA::CameraManipulator;
//		viewer.setCameraManipulator(keyswitch.get());
//	}
//	viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);
//	viewer.setSceneData(root);
//	viewer.addEventHandler(new MyHandler(model));
//	viewer.addEventHandler(new MyHandler(sphere));
//	viewer.addEventHandler(new osgViewer::StatsHandler);
//	viewer.addEventHandler(new osgGA::StateSetManipulator);
//	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
//	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
//	return viewer.run();
//}