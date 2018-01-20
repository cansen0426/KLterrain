#include <osg/Matrix>
#include <osg/MatrixTransform>
#include <iostream>

#include "KL3DMapManager.h"

KL3DMapManager::KL3DMapManager(osgViewer::Viewer* pID, osg::Group* pRoot) :
	m_id(pID),
	m_root(pRoot),
	m_mainCache(NULL),
	m_mainSurveyNode(NULL),
	m_mainTerrain(NULL),
	m_matrixTransform(NULL),
	m_mainTextureManager(NULL),
	m_isNeedSetMainCache(true),
	m_sourcePath(""),
	m_isTerrainExist(false),
	m_pointSize(0.0f),
	m_shotPointImage(NULL),
	m_rcvPointImage(NULL),
	m_mainDesingPointsNum(0),
	m_scrollNum(0),
	m_terrainScaleZ(1.0f),
	m_isEditState(false),
	m_isShotPointEdit(false),
	m_isShotLineEdit(false),
	m_isRcvPointEdit(false),
	m_isRcvLineEdit(false)
{

}


KL3DMapManager::~KL3DMapManager()
{
	//delete all the caches
	KL3DMapCache* pDel = NULL;
	KL3DMapCacheSet::iterator cacheIter = m_caches.begin();
	while(cacheIter != m_caches.end())
	{
		pDel = cacheIter->second;
		delete pDel;
		pDel = NULL;

		m_caches.erase(cacheIter);

		cacheIter = m_caches.begin();
	}
}


osgViewer::Viewer* KL3DMapManager::getID()
{
	return m_id;
}


void KL3DMapManager::setSourcePath(const std::string& sourcePath)
{
	m_sourcePath = sourcePath;
}


void KL3DMapManager::resetMainDesign()
{
	m_isNeedSetMainCache = true;
}


KL3DTextureManager* KL3DMapManager::getMainTextureManager()
{
	return m_mainTextureManager;
}


KL3DDesignNode* KL3DMapManager::getMainDesignNode()
{
	return m_mainSurveyNode;
}


KL3DMapCache* KL3DMapManager::getMainCache()
{
	return m_mainCache;
}


KL3DDesignNode* KL3DMapManager::getDesignNode(const std::string& designNdoePath)
{
	KL3DDesignNodeSet::iterator designNodeIter = m_surveyNodes.find(designNdoePath);
	if(designNodeIter == m_surveyNodes.end())
	{
		return NULL;
	}
	else
	{
		KL3DDesignNode* pNode = designNodeIter->second;
		return pNode;
	}
}


void KL3DMapManager::set3DDesignVisible(bool isVisible)
{
	m_mainSurveyNode->setNodeMask(isVisible);
}


void KL3DMapManager::set3DPointsVisible(bool isVisible, KL3DLineType type)
{
	osg::Switch* pDisplayNode = m_mainSurveyNode->getPointsNode(type);
	pDisplayNode->setNodeMask(isVisible);
}


void KL3DMapManager::set3DLinesVisible(bool isVisible, KL3DLineType type)
{
	m_mainSurveyNode->getLinesNode(type)->setIsDisplay(isVisible);
}


bool KL3DMapManager::get3DLinesVisible(KL3DLineType type)
{
	return m_mainSurveyNode->getLinesNode(type)->getIsDisplay();
}


void KL3DMapManager::set3DLinesColor(const osg::Vec4& color, KL3DLineType type)
{
	KL3DLinesNode* pLinesNode = m_mainSurveyNode->getLinesNode(type);
	pLinesNode->setLineColor(color);
}


void KL3DMapManager::set3DLineSize(const float& size, KL3DLineType type)
{
	KL3DLinesNode* pLinesNode = m_mainSurveyNode->getLinesNode(type);
	pLinesNode->setLineSize(size);
}


void KL3DMapManager::setTerrainNode(osg::Node* pTerrainNode)
{
	m_mainTerrain = pTerrainNode;
}


void KL3DMapManager::setTerrainScale(osg::MatrixTransform* mt)
{
	m_matrixTransform = mt;
}


osg::Matrix KL3DMapManager::getScaleMatrix() const
{
	osg::Matrix scaleMatrix;
	if(m_matrixTransform != NULL)
	{
		scaleMatrix = m_matrixTransform->getInverseMatrix();
	}

	return scaleMatrix;
}


float KL3DMapManager::getTerrainScaleZ()
{
	if(m_matrixTransform == NULL)
	{
		return 1.0f;
	}
	
	osg::Matrix matrix = m_matrixTransform->getMatrix();
	float scaleZ = matrix.getScale().z();
	return scaleZ;
}


float KL3DMapManager::getTerrainScaleX()
{
	if(m_matrixTransform == NULL)
	{
		return 1.0f;
	}

	osg::Matrix matrix = m_matrixTransform->getMatrix();
	float scaleX = matrix.getScale().x();
	return scaleX;
}


float KL3DMapManager::getTerrainScaleY()
{
	if(m_matrixTransform == NULL)
	{
		return 1.0f;
	}

	osg::Matrix matrix = m_matrixTransform->getMatrix();
	float scaleY = matrix.getScale().y();
	return scaleY;
}


bool KL3DMapManager::isCacheExist(const std::string& fileName)
{
	KL3DMapCacheSet::iterator iterCache = m_caches.find(fileName);
	if(iterCache == m_caches.end())
	{
		return false;
	}
	return true;
}


void KL3DMapManager::insertCache(KL3DMapCache* pCache, osg::Node* pTerrain /* = NULL */)
{
	//insert cache into mapCacheSet
	std::string cacheID = pCache->getID();
	KL3DMapCacheSet::iterator cacheIter = m_caches.find(cacheID);
	if(cacheIter != m_caches.end())
	{
		return;
	}

	m_caches.insert(std::make_pair(cacheID, pCache));

	//create textureManager : judge is exist terrain node
	osg::ref_ptr<KL3DTextureManager> pTextureManager = NULL;
	if(pTerrain)
	{
		m_isTerrainExist = true;
		pTextureManager = new KL3DTextureManager(pTerrain);
		pTextureManager->setSourcePath(m_sourcePath);
		pTextureManager->init();
		KL3DTextureManagerSet::iterator textureIter = m_textureManagers.find(pTerrain);
		if(textureIter == m_textureManagers.end())
		{
			m_textureManagers.insert(std::make_pair(pTerrain, pTextureManager));
		}

		m_root->addChild(pTextureManager);
	}

	//create surveyNode
	osg::ref_ptr<KL3DDesignNode> pSurveyNode = new KL3DDesignNode(pCache, pTextureManager);
	pSurveyNode->setSourcePath(m_sourcePath);
	pSurveyNode->initPointImage(m_shotPointImage,m_rcvPointImage);
	//初始化时设置地形拉伸系数
	pSurveyNode->setTerrainScale(m_matrixTransform);
	pSurveyNode->init();
	m_surveyNodes.insert(std::make_pair(cacheID, pSurveyNode));
	m_root->addChild(pSurveyNode);

	float pointSize = computePointSize();
	if(pointSize >= 0.3 && pointSize < 2.0f)
	{
		pSurveyNode->setPointSizeChange(true, false);
		pSurveyNode->setPointSize(pointSize, KL3D_SHOTLINE);
		pSurveyNode->setPointSize(pointSize,KL3D_RCVLINE);
	}
	else
	{
		pSurveyNode->setPointSizeChange(true, false);
		pSurveyNode->setPointSize(0.5f, KL3D_SHOTLINE);
		pSurveyNode->setPointSize(0.5f, KL3D_RCVLINE);
	}

	//set main cache& surveyNode& textureManager
	if(m_isNeedSetMainCache)
	{
		m_mainCache = pCache;
		m_mainTextureManager = pTextureManager;
		m_mainTerrain = pTerrain;
		m_mainSurveyNode = pSurveyNode;

		m_isNeedSetMainCache = false;
	}

	designPointsRarefying();
}


void KL3DMapManager::deleteCache(const std::string& fileName)
{
	//找到显示节点，将其从根节点删除
	KL3DDesignNodeSet::iterator iterDesignNode = m_surveyNodes.find(fileName);
	osg::ref_ptr<KL3DDesignNode> pDesignNode = iterDesignNode->second;
	m_surveyNodes.erase(iterDesignNode);
	m_root->removeChild(pDesignNode);

	//找到显示节点对应的观测系统方案对象，将其从内存中删除
	KL3DMapCacheSet::iterator iterCache = m_caches.find(fileName);
	KL3DMapCache* pDelCache = iterCache->second;
	delete pDelCache;
	m_caches.erase(iterCache);
}


KL3DMapCache* KL3DMapManager::getCache(const std::string& path)
{
	KL3DMapCache* pCache = NULL;
	KL3DMapCacheSet::iterator mapCacheIter = m_caches.find(path);

	if(mapCacheIter != m_caches.end())
	{
		pCache = mapCacheIter->second;
		return pCache;
	}
	else
	{
		pCache;
	}
}


void KL3DMapManager::updatePointsDemByCPU(bool isUpdate, const double depature /* = 0 */)
{
	if(!isUpdate)
	{
		return ;
	}

	if(!m_mainTerrain)
	{
		return;
	}
	long beginTime = clock();

	//创建KL3DTerrainTileManager对象
	KL3DTerrainTileManager* pTerrainTileManager = new KL3DTerrainTileManager(m_mainTerrain);
	pTerrainTileManager->setXOffset(m_mainCache->getXOffset());
	pTerrainTileManager->setYOffset(m_mainCache->getYOffset());
	pTerrainTileManager->gatherCurrentOSGScenceTerrainTile();

	KL3DLineSet* p3DShotLines = m_mainCache->getShotLineSet();
	KL3DLineSet* p3DRcvLines = m_mainCache->getRcvLineSet();

	KL3DLineSet::iterator lineIter; 
	if(p3DShotLines->size() > 0)
	{
		lineIter = p3DShotLines->begin();
		while(lineIter != p3DShotLines->end())
		{
			KL3DLine* p3DLine = lineIter->second;
			osg::Vec3Array* pVertexArray = p3DLine->getVertexArray();

			KL3DPointVector* p3DPoints = p3DLine->getPointVector();
			for(unsigned int i = 0; i < p3DPoints->size(); i++)
			{
				KL3DPoint* p3DPoint = (*p3DPoints)[i];
				float zInter = p3DPoint->getCoord().z();
				pTerrainTileManager->getValue(p3DPoint->getCoord().x(), p3DPoint->getCoord().y(),zInter);
				p3DPoint->setCoord(osg::Vec3f(p3DPoint->getCoord().x(),p3DPoint->getCoord().y(),zInter + depature));
				(*pVertexArray)[p3DPoint->getIndex()].z() = p3DPoint->getCoord().z();
			}
			lineIter++;
		}
	}
	

	if(p3DRcvLines->size() >0)
	{
		lineIter = p3DRcvLines->begin();
		while(lineIter != p3DRcvLines->end())
		{
			KL3DLine* p3DLine = lineIter->second;
			osg::Vec3Array* pVertexArray = p3DLine->getVertexArray();

			KL3DPointVector* p3DPoints = p3DLine->getPointVector();
			for(unsigned int i = 0; i < p3DPoints->size(); i++)
			{
				KL3DPoint* p3DPoint = (*p3DPoints)[i];
				float zInter = p3DPoint->getCoord().z();
				pTerrainTileManager->getValue(p3DPoint->getCoord().x(), p3DPoint->getCoord().y(),zInter);
				p3DPoint->setCoord(osg::Vec3f(p3DPoint->getCoord().x(),p3DPoint->getCoord().y(),zInter + depature));
				(*pVertexArray)[p3DPoint->getIndex()].z() = p3DPoint->getCoord().z();
			}
			lineIter++;
		}
	}
	

	//删除KL3DTerrainTileManager对象
	delete pTerrainTileManager;
	pTerrainTileManager = NULL;

	long cpuTime = clock() - beginTime;
	std::cout<<"update all points dem time is:"<<cpuTime<<"ms"<<std::endl;
}


bool KL3DMapManager::isTerrainExist()
{
	return m_isTerrainExist;
}


void KL3DMapManager::addTerrainTexture(osg::Node* pTerrainNode)
{
	if(pTerrainNode == NULL)
	{
		return;
	}

	osg::ref_ptr<KL3DTextureManager> pTextureManager = NULL;
	m_isTerrainExist = true;
	pTextureManager = new KL3DTextureManager(pTerrainNode);
	pTextureManager->setSourcePath(m_sourcePath);
	pTextureManager->init();
	KL3DTextureManagerSet::iterator textureIter = m_textureManagers.find(pTerrainNode);
	if(textureIter == m_textureManagers.end())
	{
		m_textureManagers.insert(std::make_pair(pTerrainNode, pTextureManager));
	}

	m_root->addChild(pTextureManager);
	m_mainTextureManager = pTextureManager;

	//向显示节点KL3DDesignNode中添加新的高程纹理管理器
	m_mainSurveyNode->notifyAddTextureManager(m_mainTextureManager);
}


float KL3DMapManager::computePointSize()
{
	osg::Camera* camera = m_id->getCamera();
	osg::Vec3d eye;
	osg::Vec3d center;
	osg::Vec3d up;

	camera->getViewMatrixAsLookAt(eye, center, up);
	double distance = fabs(eye.z());
	float imageSize = 0.0f;

	/*double terrainScale = 1.0;
	if(m_matrixTransform)
	{
		osg::Matrix matrix = m_matrixTransform->getMatrix();
		terrainScale = matrix.getScale().z();
	}*/
	
	double separationDis = 0.0;
	if(m_terrainScaleZ >= 1)
		separationDis = (m_terrainScaleZ - 1) * 2000.0;

	if(distance <= 2000.0+separationDis)
	{imageSize = 2.1f;}
	else if(distance > 2000.0 + separationDis && distance <= 2500+separationDis)
	{imageSize = 2.0f;}
	else if(distance > 2500.0 + separationDis && distance <= 3000+separationDis)
	{imageSize = 1.9f;}
	else if(distance > 3000.0 + separationDis && distance <= 4000+separationDis)
	{imageSize = 1.8f;}
	else if(distance > 4000.0 + separationDis && distance <= 5000+separationDis)
	{imageSize = 1.6f;}
	else if(distance > 5000.0 + separationDis && distance <= 6000+separationDis)
	{imageSize = 1.4f;}
	else if(distance > 6000.0 + separationDis && distance <= 7000+separationDis)
	{imageSize = 1.2f;}
	else if(distance > 7000.0 + separationDis && distance <= 8000+separationDis)
	{imageSize = 1.1f;}
	else if(distance > 8000.0 + separationDis && distance <= 9000+separationDis)
	{imageSize = 1.0f;}
	else if(distance > 9000.0 + separationDis && distance <= 10000+separationDis)
	{imageSize = 1.0f;}
	else if(distance > 10000.0 + separationDis && distance <= 20000+separationDis)
	{imageSize = 0.9f;}
	else if(distance > 20000.0 + separationDis && distance <= 30000+separationDis)
	{imageSize = 0.8f;}
	else if(distance > 30000.0 + separationDis && distance <= 40000+separationDis)
	{imageSize = 0.8f;}
	else if(distance > 40000.0 + separationDis && distance <= 50000+separationDis)
	{imageSize = 0.7f;}
	else if(distance > 50000.0 + separationDis && distance <= 60000+separationDis)
	{imageSize = 0.6f;}
	else if(distance > 60000.0 + separationDis && distance <= 70000+separationDis)
	{imageSize = 0.6f;}
	else if(distance > 70000.0 + separationDis && distance <= 80000+separationDis)
	{imageSize = 0.5f;}
	else if(distance > 80000.0 + separationDis && distance <= 90000+separationDis)
	{imageSize = 0.4f;}
	else if(distance > 90000.0 + separationDis && distance <= 100000+separationDis)
	{imageSize = 0.3f;}
	else
	{
		imageSize = 0.2f;
	}
	return imageSize;
}


void KL3DMapManager::resetPointSize()
{
	float pointSize;
	pointSize = computePointSize();
	if(m_pointSize == pointSize)
	{
		return;
	}
	else
	{
		m_pointSize = pointSize;
		KL3DDesignNodeSet::iterator Iter;
		for(Iter = m_surveyNodes.begin(); Iter != m_surveyNodes.end(); Iter++)
		{
			KL3DDesignNode* pdesignNode = (Iter->second).get();
			if(pdesignNode)
			{
				pdesignNode->setPointSizeChange(true, true);
				pdesignNode->setPointSize(m_pointSize, KL3D_SHOTLINE);
				pdesignNode->setPointSize(m_pointSize, KL3D_RCVLINE);
			}
		}

	}
}


void KL3DMapManager::initPointImage(osg::Image* shotPointImage, osg::Image* rcvPointImage)
{
	m_shotPointImage = shotPointImage;
	m_rcvPointImage = rcvPointImage;
}


void KL3DMapManager::setMainDesignPointsNum(long& pPointNum)
{
	m_mainDesingPointsNum = pPointNum;
}


void KL3DMapManager::designPointsRarefying()
{
	//当等值线所有的控制点的数量低于1000000的时候，不再做抽稀处理
	if(m_mainDesingPointsNum <= 1000000)
	{
		return;
	}
	//当rarefyMultiple=3的时候，炮检点总量已经超过1千万
	unsigned int rarefyMultiple = m_mainDesingPointsNum/5000000 + 1;

	osg::Camera* pCamera = m_id->getCamera();

	osg::Vec3d eye;
	osg::Vec3d center;
	osg::Vec3d up;

	pCamera->getViewMatrixAsLookAt(eye, center, up);
	double distance = fabs(eye.z());

	unsigned int Num = floor(distance/10000.0f);

	if(distance == 0 || distance > 1000000.0f)
	{
		Num = 40;
	}

	if(m_scrollNum == Num)
	{
		return;
	}

	m_scrollNum = Num;
	unsigned int pStep = rarefyMultiple * Num;

	KL3DPointsNode* p3DShotPointsNode = m_mainSurveyNode->getPointsNode(KL3D_SHOTLINE);
	KL3DPointsNode* p3DRcvPointsNode = m_mainSurveyNode->getPointsNode(KL3D_RCVLINE);
	KL3DLinesNode* p3DShotLinesNode = m_mainSurveyNode->getLinesNode(KL3D_SHOTLINE);
	KL3DLinesNode* p3DRcvLinesNode = m_mainSurveyNode->getLinesNode(KL3D_RCVLINE);

	bool isShotPointDisplay = p3DShotPointsNode->getIsVisible();
	bool isRcvPointDisplay = p3DRcvPointsNode->getIsVisible();
	bool isShotLineDisplay = p3DShotLinesNode->getIsDisplay();
	bool isRcvLineDisplay = p3DRcvLinesNode->getIsDisplay();


	//炮点集
	KL3DPointGeodeSet* p3DShotPointsGeodeSet = p3DShotPointsNode->getPointGeodes();
	KL3DPointGeodeSet::iterator iterShotPointGeode = p3DShotPointsGeodeSet->begin();

	//检点集
	KL3DPointGeodeSet* p3DRcvPointsGeodeSet = p3DRcvPointsNode->getPointGeodes();
	KL3DPointGeodeSet::iterator iterRcvPointGeode = p3DRcvPointsGeodeSet->begin();

	//炮线集
	KL3DLineGeodeSet* p3DShotLinesGeodeSet = p3DShotLinesNode->getLinesGeodes();
	KL3DLineGeodeSet::iterator iterShotLineGeode = p3DShotLinesGeodeSet->begin();

	//检线集
	KL3DLineGeodeSet* p3DRcvLinesGeodeSet = p3DRcvLinesNode->getLinesGeodes();
	KL3DLineGeodeSet::iterator iterRcvLineGeode = p3DRcvLinesGeodeSet->begin();
	//unsigned int pStep = Num;

	unsigned int shotLinesNum = p3DShotPointsGeodeSet->size();
	unsigned int rcvLinesNum =  p3DRcvPointsGeodeSet->size();

	/*unsigned int shotRarefyByLine = p3DShotPointsGeodeSet->size()/256 + 1;
	unsigned int rcvRarefyByLine = p3DRcvPointsGeodeSet->size()/256 + 1;*/

	unsigned int stepOfShot = 0;
	unsigned int stepOfRcv = 0;

	//对炮点抽稀的策略
	if(shotLinesNum < 64)
	{
		stepOfShot = 1;
	}
	else if(shotLinesNum < 128 && shotLinesNum >= 64)
	{
		if(Num < 4)
			stepOfShot = 1;
		else
			stepOfShot = rarefyMultiple * (Num - 3);
	}
	else if(shotLinesNum < 256 && shotLinesNum >= 128)
	{
		if(Num < 3)
			stepOfShot = 1;
		else
			stepOfShot = rarefyMultiple * (Num - 2);
	}
	else if(shotLinesNum < 512 && shotLinesNum >= 256)
	{
		if(Num<2)
			stepOfShot = 1;
		else
			stepOfShot = rarefyMultiple * (Num - 1);
	}
	else
	{
		stepOfShot = pStep;
	}

	//对检点抽稀的策略
	if(rcvLinesNum < 64)
	{
		stepOfRcv = 1;
	}
	else if(rcvLinesNum < 128 && rcvLinesNum >= 64)
	{
		if(Num < 4)
			stepOfRcv = 1;
		else
			stepOfRcv = rarefyMultiple * (Num - 3);
	}
	else if(rcvLinesNum < 256 && rcvLinesNum >= 128)
	{
		if(Num < 3)
			stepOfRcv = 1;
		else
			stepOfRcv = rarefyMultiple * (Num - 2);
	}
	else if(rcvLinesNum < 512 && rcvLinesNum >= 256)
	{
		if(Num<2)
			stepOfRcv = 1;
		else
			stepOfRcv = rarefyMultiple * (Num - 1);
	}
	else
	{
		stepOfRcv = pStep;
	}

	//抽稀开始
	if(Num == 0)
	{
		if(isShotPointDisplay)
		{
			for(; iterShotPointGeode != p3DShotPointsGeodeSet->end(); iterShotPointGeode++)
			{
				KL3DPointGeode* p3DShotPointGeode = iterShotPointGeode->second;
				p3DShotPointGeode->setNodeMask(true);
			}
		}

		if(isRcvPointDisplay)
		{
			for(; iterRcvPointGeode != p3DRcvPointsGeodeSet->end(); iterRcvPointGeode++)
			{
				KL3DPointGeode* p3DRcvPointGeode = iterRcvPointGeode->second;
				p3DRcvPointGeode->setNodeMask(true);
			}
		}

		if(isShotLineDisplay)
		{
			for(; iterShotLineGeode != p3DShotLinesGeodeSet->end(); iterShotLineGeode++)
			{
				KL3DLineGeode* p3DShotLineGeode = iterShotLineGeode->second;
				p3DShotLineGeode->setNodeMask(true);
			}
		}

		if(isRcvLineDisplay)
		{
			for(; iterRcvLineGeode != p3DRcvLinesGeodeSet->end(); iterRcvLineGeode++)
			{
				KL3DLineGeode* p3DRcvLineGeode = iterRcvLineGeode->second;
				p3DRcvLineGeode->setNodeMask(true);
			}
		}


	}
	else
	{
		//首先将节点先隐藏再按判断做处理
		if(isShotPointDisplay)
		{
			for(unsigned int i = 0; i < p3DShotPointsGeodeSet->size(); i++,iterShotPointGeode++)
			{
				KL3DPointGeode* p3DShotPointGeode = iterShotPointGeode->second;
				p3DShotPointGeode->setNodeMask(false);
				if(i%stepOfShot == 0)
				{
					p3DShotPointGeode->setNodeMask(true);
				}
			}
		}

		if(isRcvPointDisplay)
		{
			for(unsigned int i = 0; i < p3DRcvPointsGeodeSet->size(); i++,iterRcvPointGeode++)
			{
				KL3DPointGeode* p3DRcvPointGeode = iterRcvPointGeode->second;
				p3DRcvPointGeode->setNodeMask(false);
				if(i%stepOfRcv == 0)
				{
					p3DRcvPointGeode->setNodeMask(true);
				}
			}
		}

		if(isShotLineDisplay)
		{
			for(unsigned int i = 0; i < p3DShotLinesGeodeSet->size(); i++,iterShotLineGeode++)
			{
				KL3DLineGeode* p3DShotLineGeode = iterShotLineGeode->second;
				p3DShotLineGeode->setNodeMask(false);
				if(i%stepOfShot == 0)
				{
					p3DShotLineGeode->setNodeMask(true);
				}
			}
		}

		if(isRcvLineDisplay)
		{
			for(unsigned int i = 0; i < p3DRcvLinesGeodeSet->size(); i++,iterRcvLineGeode++)
			{
				KL3DLineGeode* p3DRcvLineGeode = iterRcvLineGeode->second;
				p3DRcvLineGeode->setNodeMask(false);
				if(i%stepOfRcv == 0)
				{
					p3DRcvLineGeode->setNodeMask(true);
				}

			}
		}
	} 
}


void KL3DMapManager::setTerrainScaleZ(float& pTerrainScaleZ)
{
	m_terrainScaleZ = pTerrainScaleZ;
}

//***************炮检点（线）编辑状态控制函数*************//

KL3DEditObject KL3DMapManager::getEditObject()
{
	KL3DEditObject editObject;

	if(m_isShotPointEdit && !m_isRcvPointEdit)
	{
		editObject = KL3D_SHOTPOINT_EDIT;
	}
	if(m_isRcvPointEdit && !m_isShotPointEdit)
	{
		editObject = KL3D_RCVPOINT_EDIT;
	}
	if(m_isShotPointEdit && m_isRcvPointEdit)
	{
		editObject = KL3D_POINT_EDIT;
	}
	if(m_isShotLineEdit && !m_isRcvLineEdit)
	{
		editObject = KL3D_SHOTLINE_EDIT;
	}
	if(m_isRcvLineEdit && !m_isShotLineEdit)
	{
		editObject = KL3D_RCVLINE_EDIT;
	}
	if(m_isShotLineEdit && m_isRcvLineEdit)
	{
		editObject = KL3D_LINE_EDIT;
	}

	return editObject;
}


bool KL3DMapManager::getEditState()
{
	return m_isEditState;
}


void KL3DMapManager::editShotPoint()
{
	m_isEditState = true;
	m_isShotPointEdit = true;

	m_isShotLineEdit = false;
	m_isRcvLineEdit = false;

	updatePointsDemByCPU(m_isEditState);
}


void KL3DMapManager::editShotLine()
{
	m_isEditState = true;
	m_isShotLineEdit = true;

	m_isShotPointEdit = false;
	m_isRcvPointEdit = false;

	updatePointsDemByCPU(m_isEditState);
}


void KL3DMapManager::editRcvPoint()
{
	m_isEditState = true;
	m_isRcvPointEdit = true;

	m_isShotLineEdit =false;
	m_isRcvLineEdit = false;

	updatePointsDemByCPU(m_isEditState);
}


void KL3DMapManager::editRcvLine()
{
	m_isEditState = true;
	m_isRcvLineEdit = true;

	m_isShotPointEdit = false;
	m_isRcvPointEdit = false;

	updatePointsDemByCPU(m_isEditState);
}


void KL3DMapManager::cancelEditShotPoint()
{
	m_isShotPointEdit = false;
	
	if(m_isRcvPointEdit == false)
	{
		m_isEditState = false;
	}

}


void KL3DMapManager::cancelEditShotLine()
{
	m_isShotLineEdit = false;

	if(m_isRcvLineEdit == false)
	{
		m_isEditState = false;
	}
}


void KL3DMapManager::cancelEditRcvPoint()
{
	m_isRcvPointEdit = false;

	if(m_isShotPointEdit == false)
	{
		m_isEditState = false;
	}
}


void KL3DMapManager::cancelEditRcvLine()
{
	m_isRcvLineEdit = false;

	if(m_isShotLineEdit == false)
	{
		m_isEditState = false;
	}
}


bool KL3DMapManager::isShotPointEdit() const
{
	return m_isShotPointEdit;
}


bool KL3DMapManager::isShotLineEdit() const
{
	return m_isShotLineEdit;
}


bool KL3DMapManager::isRcvPointEdit() const
{
	return m_isRcvPointEdit;
}


bool KL3DMapManager::isRcvLineEdit() const
{
	return m_isRcvLineEdit;
}

void KL3DMapManager::gridHoming()
{
	KL3DEditPointSet* pEditPointSet = m_mainCache->getEditPoints();
	KL3DDesignNode* pDesignNode = getMainDesignNode();
	if(pEditPointSet->size() != 0)
	{
		KL3DEditPointSet::iterator iterEditPoint = pEditPointSet->begin();
		for(; iterEditPoint != pEditPointSet->end(); ++iterEditPoint)
		{
			KL3DEditPoint editPoint = *iterEditPoint;
			double id = editPoint.m_lineID;
			KL3DLineType type = editPoint.m_type;
			KL3DPoint* p3DPoint = editPoint.m_editPoint;
			double moveX = p3DPoint->getCoord().x()+100;
			double moveY = p3DPoint->getCoord().y()+100;
			double moveZ = p3DPoint->getCoord().z();
			//double moveX = p3DPoint->getCoord().x();
			//double moveY = p3DPoint->getCoord().y();
			//double moveZ = p3DPoint->getCoord().z();


			p3DPoint->setCoord(osg::Vec3f(moveX,moveY,moveZ));

			KL3DLine* pLine = m_mainCache->getLine(id,type);
			osg::Vec3Array* pVertexArray = pLine->getVertexArray();
			(*pVertexArray)[p3DPoint->getIndex()] += osg::Vec3(100.0,100.0,0.0);
		}
	}
	pDesignNode->reDraw();
}

void KL3DMapManager::ProjectToGrid_3D(double &x,double &y, double &hInterval,double &halfHInterval, double &vInterval,double &halfVInterval, double &x0,double &y0, double &sinValue,double &cosValue)
{
	double x1,y1,x2,y2;
	//步骤1：平移
	x1 = x - x0;
	y1 = y - y0;
	//步骤2：旋转
	x2 = x1*sinValue - y1*cosValue;
	y2 = y1*sinValue + x1*cosValue;
	//步骤3：网格归位
	SDRound_3D(x2,vInterval,halfVInterval);
	SDRound_3D(y2,hInterval,halfHInterval);
	//步骤4：反旋转
	x1 = x2*sinValue + y2*cosValue;
	y1 = y2*sinValue - x2*cosValue;
	//步骤5：反平移
	x = x1 + x0;
	y = y1 + y0;

}

void KL3DMapManager::SDRound_3D(double &value,double &gridLength,double &halfGridLength)
{
	int timer;

	if (value >= 0)
	{
		value += halfGridLength;
	}
	else
	{
		value -= halfGridLength;
	}
	timer = (int) (value/gridLength);
	value = timer*gridLength;
}
