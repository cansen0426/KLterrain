
/*
#include <QString>
#include <QDir>
#include <QtGUi/QMessageBox>

#include <Qpainter>*/

#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>

#include <osg/ComputeBoundsVisitor>
#include <osg/CullingSet>

#include <osgDB/ReadFile>

#include <iostream>

//#include "KL3DTerrainTileManager"
#include "KL3DDesignShape.h"

KL3DDesignShape::KL3DDesignShape() :
	m_viewer(NULL),
	m_root(NULL),
	m_mapManager(NULL),
	m_designSourcePath(""),
	m_terrainScaleTranform(NULL),
	m_3DDesignHandle(NULL),
	m_3DDesignPolygonHandle(NULL)
{

}


KL3DDesignShape::~KL3DDesignShape()
{

}


void KL3DDesignShape::init()
{

}


void KL3DDesignShape::setRootNode(osg::Node* rootNode)
{
	m_root = rootNode;
}


void KL3DDesignShape::setSourcePath(const std::string sourcePath)
{
	m_designSourcePath = sourcePath;
}


bool KL3DDesignShape::generate3DDesignData(osgViewer::Viewer* pViewer,osgTerrain::Terrain* pTerrain, std::string dataFileName)
{
	m_viewer = pViewer;

	osg::CullStack::CullingMode cullingMode = m_viewer->getCamera()->getCullingMode();
	cullingMode &= ~(osg::CullStack::SMALL_FEATURE_CULLING);
	m_viewer->getCamera()->setCullingMode(cullingMode);

	//创建KL3DMapCache对象
	KL3DMapCache* pCache = new KL3DMapCache();
	pCache->setID(dataFileName);

	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO" );
	OGRRegisterAll();

	OGRDataSource* poDS = (OGRDataSource*)OGRSFDriverRegistrar::Open(dataFileName.c_str(),FALSE);
	if(poDS == NULL)
	{
		std::cout<<"文件无法打开"<<std::endl;
		return false;
	}

	OGRLayer* poLayer = poDS->GetLayer(0);
	poLayer->ResetReading();
	OGRFeature *poFeature;

	double id = 0.0;
	unsigned int num = 0;

	while((poFeature = poLayer->GetNextFeature()) != NULL)
	{
		OGRGeometry *poGeometry=poFeature->GetGeometryRef();
		if (poGeometry!=NULL)
		{
			switch (wkbFlatten(poGeometry->getGeometryType()))
			{
			case wkbLineString:
				num++;
				id++;
				OGRLineString *poLine = (OGRLineString*)poGeometry;
				KL3DLine* p3DLine = new KL3DLine();
				p3DLine->setID(id);
				KL3DLineType type;
				if(num%2 == 1)
					type = KL3D_SHOTLINE;
				else
					type = KL3D_SHOTLINE;
				p3DLine->setType(type);
					
				osg::Vec3Array* pVertexArray = p3DLine->getVertexArray();
				osg::Vec3Array* pColorArray = p3DLine->getColorArray();
				osg::FloatArray* pFlagArray = p3DLine->getFlagArray();
				for(unsigned int i = 0;i<poLine->getNumPoints();i++)
				{
					KL3DPoint* p3DPoint = new KL3DPoint();
					p3DPoint->setID((double)i);
					p3DPoint->setSameStakeID(i%9);

					float x = poLine->getX(i);
					float y = poLine->getY(i);
					float z = KL3DDEFAULTVALUE;//= poLine->getZ(i);

					osg::Vec3 coord(x, y, z);

					p3DPoint->setCoord(coord);

					p3DPoint->setIndex(i);
					pVertexArray->push_back(coord);
					if(type == KL3D_SHOTLINE)
					{
						pColorArray->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
					}
					else if(type == KL3D_RCVLINE)
					{
						pColorArray->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
					}

					pFlagArray->push_back(1.0);

					p3DLine->insertPoint(p3DPoint);
				}

				pCache->insertLine(p3DLine);
				OGRFeature::DestroyFeature( poFeature );
				break;
			}
		}
	}


	//insert the cache to mapManager
	KL3DMapManager* pMapManager = new KL3DMapManager(m_viewer, dynamic_cast<osg::Group*>(m_root));
	pMapManager->setTerrainScale(m_terrainScaleTranform);
	
	pMapManager->setSourcePath(m_designSourcePath);
	osg::ref_ptr<osg::Image> pShotPointImage = createPointImage(KL3D_SHOTLINE);
	osg::ref_ptr<osg::Image> pRcvPointImage = createPointImage(KL3D_RCVLINE);
	pMapManager->initPointImage(pShotPointImage.get(), pRcvPointImage.get());

	pMapManager->insertCache(pCache, pTerrain);
	pMapManager->updatePointsDemByCPU(true);
	m_mapManager = pMapManager;

	//add event handle to the viewer
	m_3DDesignHandle = new KL3DDesignHandle(pMapManager,pTerrain);
	m_3DDesignHandle->setEditState(m_mapManager->getEditState());
	m_viewer->getCamera()->setEventCallback(m_3DDesignHandle);

	//add polyonhandle to the viewer
	/*m_3DDesignPolygonHandle = new KL3DDesignPolygonHandle(pMapManager);
	m_3DDesignPolygonHandle->setEditState(m_mapManager->getEditState());
	m_viewer->getCamera()->setEventCallback(m_3DDesignPolygonHandle);*/

	return true;
}


bool KL3DDesignShape::generate3DDesignData(osgViewer::Viewer* pViewer,osgTerrain::Terrain* pTerrain)
{
	m_viewer = pViewer;

	osg::CullStack::CullingMode cullingMode = m_viewer->getCamera()->getCullingMode();
	cullingMode &= ~(osg::CullStack::SMALL_FEATURE_CULLING);
	m_viewer->getCamera()->setCullingMode(cullingMode);

	//创建KL3DMapCache对象
	KL3DMapCache* pCache = new KL3DMapCache();
	std::string designID = "myDesign";
	pCache->setID(designID);

	//计算地形包围盒
	osg::ComputeBoundsVisitor cbVisitor;
	pTerrain->accept(cbVisitor);
	osg::BoundingBox terrainBoundingBox = cbVisitor.getBoundingBox();

	double xMin = terrainBoundingBox.xMin() + (terrainBoundingBox.xMax() - terrainBoundingBox.xMin())*0.2;
	double yMin = terrainBoundingBox.yMin() + (terrainBoundingBox.yMax() - terrainBoundingBox.yMin())*0.2;
	double xMax = terrainBoundingBox.xMax() - (terrainBoundingBox.xMax() - terrainBoundingBox.xMin())*0.2;
	double yMax = terrainBoundingBox.yMax() - (terrainBoundingBox.yMax() - terrainBoundingBox.yMin())*0.2;

	double xMin2 = terrainBoundingBox.xMin() + (terrainBoundingBox.xMax() - terrainBoundingBox.xMin())*0.1;
	double yMin2 = terrainBoundingBox.yMin() + (terrainBoundingBox.yMax() - terrainBoundingBox.yMin())*0.1;
	double xMax2 = terrainBoundingBox.xMax() - (terrainBoundingBox.xMax() - terrainBoundingBox.xMin())*0.1;
	double yMax2 = terrainBoundingBox.yMax() - (terrainBoundingBox.yMax() - terrainBoundingBox.yMin())*0.1;

	long pointNum = 0;
	double shotPointInterval = 1200.0;
	double rcvPointInterVal = 900.0;
	//设置炮检
	for(unsigned int i = 0; i < unsigned int((xMax - xMin)/shotPointInterval); i++)
	{
		KL3DLine* p3DLine = new KL3DLine();
		p3DLine->setID(double(i+1));
		p3DLine->setType(KL3D_SHOTLINE);

		osg::Vec3Array* pVertexArray = p3DLine->getVertexArray();
		osg::Vec3Array* pColorArray = p3DLine->getColorArray();
		osg::FloatArray* pFlagArray = p3DLine->getFlagArray();
		for(unsigned int j = 0;j < unsigned int((yMax - yMin)/shotPointInterval);j++)
		{
			KL3DPoint* p3DPoint = new KL3DPoint();
			p3DPoint->setID((double)j);
			p3DPoint->setSameStakeID(j%9);

			float x = float(xMin + i*shotPointInterval);
			float y = float(yMin + j*shotPointInterval);
			float z = 0.0f;//= poLine->getZ(i);

			osg::Vec3 coord(x, y, z);

			p3DPoint->setCoord(coord);

			p3DPoint->setIndex(j);
			pVertexArray->push_back(coord);

			pColorArray->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));

			pFlagArray->push_back(1.0);

			p3DLine->insertPoint(p3DPoint);

			pointNum++;
		}

		pCache->insertLine(p3DLine);
	}

	//设置检点
	for(unsigned int i = 0; i < unsigned int((yMax2 - yMin2)/rcvPointInterVal); i++)
	{
		KL3DLine* p3DLine = new KL3DLine();
		p3DLine->setID(double(i+1));
		p3DLine->setType(KL3D_RCVLINE);

		osg::Vec3Array* pVertexArray = p3DLine->getVertexArray();
		osg::Vec3Array* pColorArray = p3DLine->getColorArray();
		osg::FloatArray* pFlagArray = p3DLine->getFlagArray();
		for(unsigned int j = 0;j < unsigned int ((xMax2 - xMin2)/rcvPointInterVal);j++)
		{
			KL3DPoint* p3DPoint = new KL3DPoint();
			p3DPoint->setID((double)j);
			p3DPoint->setSameStakeID(j%9);

			float x = float(xMin2 + j*rcvPointInterVal);
			float y = float(yMin2 + i*rcvPointInterVal);
			float z = 0.0f;//= poLine->getZ(i);

			osg::Vec3 coord(x, y, z);

			p3DPoint->setCoord(coord);

			p3DPoint->setIndex(j);
			pVertexArray->push_back(coord);

			pColorArray->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

			pFlagArray->push_back(1.0);

			p3DLine->insertPoint(p3DPoint);

			pointNum++;
		}

		pCache->insertLine(p3DLine);
	}

	std::cout<<"The sum number of Point is:"<<pointNum<<std::endl;

	//insert the cache to mapManager
	KL3DMapManager* pMapManager = new KL3DMapManager(m_viewer, dynamic_cast<osg::Group*>(m_root));
	pMapManager->setTerrainScale(m_terrainScaleTranform);

	pMapManager->setSourcePath(m_designSourcePath);
	osg::ref_ptr<osg::Image> pShotPointImage = createPointImage(KL3D_SHOTLINE);
	osg::ref_ptr<osg::Image> pRcvPointImage = createPointImage(KL3D_RCVLINE);
	pMapManager->initPointImage(pShotPointImage.get(), pRcvPointImage.get());

	pMapManager->setMainDesignPointsNum(pointNum);
	pMapManager->insertCache(pCache, pTerrain);
	pMapManager->updatePointsDemByCPU(true);
	m_mapManager = pMapManager;

	//add event handle to the viewer
	m_3DDesignHandle = new KL3DDesignHandle(pMapManager, pTerrain);
	m_3DDesignHandle->setEditState(m_mapManager->getEditState());
	m_viewer->getCamera()->setEventCallback(m_3DDesignHandle);

	//add polyonhandle to the viewer
	/*m_3DDesignPolygonHandle = new KL3DDesignPolygonHandle(pMapManager);
	m_3DDesignPolygonHandle->setEditState(m_mapManager->getEditState());
	m_viewer->getCamera()->setEventCallback(m_3DDesignPolygonHandle);*/

	return true;
}


void KL3DDesignShape::setDesignNodeVisible(bool isVisible)
{

}


void KL3DDesignShape::setPointsVisible(bool isVisible, KL3DLineType type)
{

}


void KL3DDesignShape::setLabelIsVisible(bool isVisible, KL3DLineType type)
{

}


void KL3DDesignShape::setLabelInterval(const unsigned int& interval, KL3DLineType type)
{

}


void KL3DDesignShape::setLinesVisible(bool isVisible, KL3DLineType)
{

}


void KL3DDesignShape::setLinesLabelIsVisible(bool isVisible, KL3DLineType type)
{

}


osg::ref_ptr<osg::Image> KL3DDesignShape::createPointImage(KL3DLineType type)
{
	osg::ref_ptr<osg::Image> pointImage;
	if(type == KL3D_SHOTLINE)
		pointImage = osgDB::readImageFile("../KL3DDisplay/images/shotPointImage.bmp");
	else
		pointImage = osgDB::readImageFile("../KL3DDisplay/images/rcvPointImage.bmp");

	return pointImage;
}


void KL3DDesignShape::setPointSize(const float& PointSize, KL3DLineType type)
{

}


bool KL3DDesignShape::isTerrainExist()
{
	return true;
}


void KL3DDesignShape::setTerrainScale(osg::MatrixTransform* mt)
{

}


void KL3DDesignShape::setCurrentEventHandle(osg::ref_ptr<KL3DBaseHandler> pHandle)
{
	
}


void KL3DDesignShape::generate3DLines(KL3DMapCache* pCache)
{

}