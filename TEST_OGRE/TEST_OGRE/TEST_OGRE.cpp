// TEST_OGRE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Ogre.h"
#include"include/OgreApplicationContext.h"


#include"include/OgreOctreeSceneManager.h"
#include"include/OgreOctree.h"
#include"include/OgreOctreeNode.h"
#include"include/OgreOctreeSceneQuery.h"


class KeyHandler : public OgreBites::InputListener
{
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override
	{
		if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
		{
			Ogre::Root::getSingleton().queueEndRendering();
		}
		return true;
	}
};
//! [key_handler]

int main(int argc, char* argv[])
{
	//! [constructor]
	OgreBites::ApplicationContext ctx("OgreTutorialApp");
	ctx.initApp();
	//! [constructor]

	//! [setup]
		// get a pointer to the already created root
	Ogre::Root* root = ctx.getRoot();
	
	Ogre::OctreeSceneManager* scnMgr=dynamic_cast<Ogre::OctreeSceneManager*>(root->createSceneManager("OctreeSceneManager"));
    

	Ogre::AxisAlignedBox box(Ogre::Vector3(-2000, -2000, -2000), Ogre::Vector3(2000, 2000,2000));


	scnMgr->init(box, 3000);

	Ogre::OctreeNode* root_oct_tree=dynamic_cast<Ogre::OctreeNode*>(scnMgr->getRootSceneNode());
	
	root_oct_tree=dynamic_cast<Ogre::OctreeNode*>(root_oct_tree);
	
	
	
	// register our scene with the RTSS
	Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// without light we would just get a black screen    
	Ogre::Light* light = scnMgr->createLight("MainLight",Ogre::Light::LightTypes::LT_DIRECTIONAL);

	
	
	scnMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	/*light->setDiffuseColour(Ogre::ColourValue(0.4, 0, 0,0));
	light->setSpecularColour(Ogre::ColourValue(0.4, 0, 0.0));*/

	scnMgr=dynamic_cast<Ogre::OctreeSceneManager*>(scnMgr);
	
	Ogre::SceneNode* lightNode = root_oct_tree->createChildSceneNode("FirstNode");
	   
	lightNode->setDirection(-1, -1, 0);
	lightNode->setPosition(200,200,0);
	lightNode->attachObject(light);
        	
	
	// also need to tell where we are
	Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(200, 300, 300);
	camNode->lookAt(Ogre::Vector3(-1, 0, 1), Ogre::Node::TS_PARENT);

	// create the camera
	Ogre::Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);

	// and tell it to render into the main window
	ctx.getRenderWindow()->addViewport(cam);

	// finally something to render
	Ogre::Entity* ent = scnMgr->createEntity("ninja.mesh");
	Ogre::Entity* ent_2 = scnMgr->createEntity("ninja.mesh");
	Ogre::Entity*ent_3=scnMgr->createEntity("ninja.mesh");
	//Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
	//node->attachObject(ent);

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshPtr plane_ptr=Ogre::MeshManager::getSingleton().createPlane(
		"ground", Ogre::RGN_DEFAULT,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);


	Ogre::Entity* groundEntity = scnMgr->createEntity("ground");

	groundEntity->setMaterialName("Examples/Rockwall");

	groundEntity->setCastShadows(false);
	
	Ogre::SceneNode*first_ent_node=root_oct_tree->createChildSceneNode("Second Node");

	root_oct_tree->attachObject(groundEntity);

	auto root_oct_tree_downcasted=static_cast<Ogre::SceneNode*>(root_oct_tree);
	
	root_oct_tree_downcasted->_updateBounds();
		
			
	scnMgr->_updateOctreeNode(static_cast<Ogre::OctreeNode*>(root_oct_tree_downcasted));

	
	auto ent_node_1=(first_ent_node)->createChildSceneNode("second");

	first_ent_node->attachObject(ent);

	first_ent_node->setPosition(Ogre::Vector3(0,4,1));
	
	

	first_ent_node->_updateBounds();

	Ogre::SceneNode*node_ent_2=ent_node_1->createChildSceneNode();

	node_ent_2->attachObject(ent_2);
	node_ent_2->setPosition(15,0,20);

	node_ent_2->_updateBounds();


	auto ent_node_3=node_ent_2->createChildSceneNode();
			
	ent_node_3->attachObject(ent_3);
	ent_node_3->setPosition(15,0,20);

    node_ent_2->_updateBounds();

	

	Ogre::MeshManager* ptr_mesh=Ogre::MeshManager::getSingletonPtr();

	auto mesh_loaded=ptr_mesh->load("ninja.mesh",Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME);
	
	auto buff_mg=Ogre::HardwareBufferManager::getSingletonPtr();
	


	auto buffer_vertex=mesh_loaded->getHardwareBufferManager();

	auto skel_mesh=mesh_loaded->getSkeleton();
			
	auto sub_mesh=mesh_loaded->getSubMeshes();

	

	auto &vertex_subdata=sub_mesh.at(0)->vertexData;

	vertex_subdata->vertexBufferBinding->getBuffer(0);

	auto buffer_mesh_temp=vertex_subdata->vertexBufferBinding->getBuffer(0);
	auto mesh_manager_vertex_num=buffer_mesh_temp->getNumVertices();
	
	for (uint16_t count = 0; count < mesh_manager_vertex_num; count++)
	{
		vertex_subdata->

		vertex_subdata->vertexBufferBinding->getBuffer(0)->readData(vertex_subdata->,)

	}
	
	Ogre::StaticGeometry *geom=scnMgr->createStaticGeometry("ninja.mesh");
	
	scnMgr->injectMovableObject(ent_3);
     
	 Ogre::Ray ray(Ogre::Vector3(0,0,0),Ogre::Vector3(100,-200,145));

	auto scene_visible_objects=scnMgr->getVisibleObjectsBoundsInfo(cam);

	Ogre::VisibleObjectsBoundsInfo info;

	scnMgr->_findVisibleObjects(cam,&info,true);

	auto ray_query= scnMgr->createRayQuery(ray,1);

	ray_query->execute();
	 

   
	
	
	
	
	

	/*auto ent_node=scnMgr->getRootSceneNode()->createChildSceneNode();
	ent_node->attachObject(ent);*/
	
	/*Ogre::SceneNode*node_ent=firts->createChildSceneNode("ent child");

	node_ent->setPosition(Ogre::Vector3{0.5,0.1,10});

	node_ent->attachObject(ent);

	Ogre::SceneNode *node_ent_second=node_ent->createChildSceneNode();

	node_ent_second->setPosition(Ogre::Vector3{ 0.5,0.1,1 });*/

	/*node_ent->attachObject(ent_2);*/

	
	//! [setup]

	//! [main]
		// register for input events
	KeyHandler keyHandler;
	ctx.addInputListener(&keyHandler);

	ctx.getRoot()->startRendering();
	ctx.closeApp();
	//! [main]
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
