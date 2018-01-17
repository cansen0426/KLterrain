
#include <osg/Camera>
#include <osg/PolygonMode>
#include <osg/MatrixTransform>

#include "KL3DOperationSel.h"
#include "KL3DOperationUnsel.h"
#include "KL3DOperationForbid.h"
#include "KL3DOPerationActive.h"
#include "KL3DOperationMove.h"
#include "KL3DOperationDelete.h"

#include "KL3DDesignHandle.h"

#define		KL3D_SINGLESEL_OFFSET	6.0f

KL3DDesignHandle::KL3DDesignHandle(KL3DMapManager* pMapManager,osgTerrain::Terrain* pTerrain) :
	m_mapManager(pMapManager),
	m_isShotPointEdit(false),
	m_isShotLineEdit(false),
	m_isRcvPointEdit(false),
	m_isRcvLineEdit(false),
	m_isMoveOperation(false),
	m_selExtent(new KL3DSelExtent()),
	m_isRightPush(false),
	m_pushZ(1),
	m_pushX(1),
	m_pushC(0),
	m_pushV(0),
	m_pushAlt(0),
	m_isAddPoint(false),
	m_terrain(pTerrain)
{

}


KL3DDesignHandle::~KL3DDesignHandle()
{

}


void KL3DDesignHandle::keydownEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if(ea.getKey() == 't')
	{
		osg::Camera* pRttCamnera = m_mapManager->getMainTextureManager();
		if(pRttCamnera)
		{
			unsigned int nodeMask = pRttCamnera->getNodeMask();
			pRttCamnera->setNodeMask(!nodeMask);
		}
	}

	//判断左右ctrl键是否按下来对多选进行操作
	if(ea.getKey() == 0xFFE3 || ea.getKey() == 0xFFE4)
	{
		m_isKeyDown = true;
	}

	//按O键进行炮点编辑操作
	if(ea.getKey() == 'o' || ea.getKey() == 'O')
	{
		m_isEditState = true;

		m_mapManager->editShotPoint();

	}

	//按P键进行检点编辑操作
	if(ea.getKey() == 'p' || ea.getKey() == 'P')
	{
		m_isEditState = true;

		m_mapManager->editRcvPoint();

	}

	//按K键进行炮线编辑操作
	if(ea.getKey() == 'k' || ea.getKey() == 'K')
	{
		m_isEditState = true;

		m_mapManager->editShotLine();

	}

	//按L键进行检线编辑操作
	if(ea.getKey() == 'l' || ea.getKey() == 'L')
	{
		m_isEditState = true;

		m_mapManager->editRcvLine();

	}

	//按Q键进行操作
	if(ea.getKey() == 'q' || ea.getKey() == 'Q')
	{
		clearEditPoints();
		m_isEditState = false;

		m_mapManager->cancelEditShotPoint();
		m_mapManager->cancelEditRcvPoint();
		m_mapManager->cancelEditShotLine();
		m_mapManager->cancelEditRcvLine();
	}


	//按F键进行禁止操作
	if(ea.getKey() == 'f' || ea.getKey() == 'F')
	{
		forbidEditObject();
	}

	//按F键进行删除操作
	if(ea.getKey() == 'd' || ea.getKey() == 'D')
	{
		deleteEditObject();
	}

	//按A键进行激活操作
	if(ea.getKey() == 'a' || ea.getKey() == 'A')
	{
		activeEditObject();
	}

	//按V键进行炮检线显示
	if(ea.getKey() == 'v' || ea.getKey() == 'V')
	{
		m_pushV++;
		if(m_pushV%2 == 0)
		{
			m_mapManager->set3DLinesVisible(true,KL3D_SHOTLINE);
			m_mapManager->set3DLinesVisible(true,KL3D_RCVLINE);
			m_mapManager->designPointsRarefying();
		}
		else if(m_pushV%2 == 1)
		{
			m_mapManager->set3DLinesVisible(false,KL3D_SHOTLINE);
			m_mapManager->set3DLinesVisible(false,KL3D_RCVLINE);
		}

	}

	//按Z键对炮点大小进行设置
	if(ea.getKey() == 'z' || ea.getKey() == 'Z')
	{
		m_pushZ++;
		float pointSize = 0.0f;

		if(m_pushZ % 6 == 0)
			pointSize = 1.0f;
		else if(m_pushZ % 6 == 1)
			pointSize = 2.0f;
		else if(m_pushZ % 6 == 2)
			pointSize = 3.0f;
		else if(m_pushZ % 6 == 3)
			pointSize = 4.0f;
		else if(m_pushZ % 6 == 4)
			pointSize = 5.0f;
		else if(m_pushZ % 6 == 5)
			pointSize = 6.0f;

		KL3DDesignNode* p3DDesignNode = m_mapManager->getMainDesignNode();
		p3DDesignNode->setPointSize(pointSize,KL3D_SHOTLINE);
	}

	//按X键对检点大小进行设置
	if(ea.getKey() == 'x' || ea.getKey() == 'X')
	{
		m_pushX++;
		float pointSize = 0.0f;

		if(m_pushX % 6 == 0)
			pointSize = 1.0f;
		else if(m_pushX % 6 == 1)
			pointSize = 2.0f;
		else if(m_pushX % 6 == 2)
			pointSize = 3.0f;
		else if(m_pushX % 6 == 3)
			pointSize = 4.0f;
		else if(m_pushX % 6 == 4)
			pointSize = 5.0f;
		else if(m_pushX % 6 == 5)
			pointSize = 6.0f;

		KL3DDesignNode* p3DDesignNode = m_mapManager->getMainDesignNode();
		p3DDesignNode->setPointSize(pointSize,KL3D_RCVLINE);
	}

	//按N键对地形拉伸系数进行设置(增大)
	if(ea.getKey() == 'n' || ea.getKey() == 'N')
	{
		m_terrain->setVerticalScale(m_terrain->getVerticalScale()*2.0);
		osg::notify(osg::NOTICE)<<"Vertical scale "<<m_terrain->getVerticalScale()<<std::endl;

		float inverseVerticalSacle = m_terrain->getVerticalScale();
		m_mapManager->setTerrainScaleZ(inverseVerticalSacle);
		float verticalScale = 1.0/m_terrain->getVerticalScale();
		m_mapManager->getMainDesignNode()->getPointsNode(KL3D_SHOTLINE)->setTerrainScale(verticalScale);
		m_mapManager->getMainDesignNode()->getPointsNode(KL3D_RCVLINE)->setTerrainScale(verticalScale);
		m_mapManager->getMainDesignNode()->getLinesNode(KL3D_SHOTLINE)->setTerrainScale(verticalScale);
		m_mapManager->getMainDesignNode()->getLinesNode(KL3D_RCVLINE)->setTerrainScale(verticalScale);
	}

	//按M键对地形拉伸系数进行设置（减小）
	if(ea.getKey() == 'm' || ea.getKey() == 'M')
	{
		m_terrain->setVerticalScale(m_terrain->getVerticalScale()/2.0);
		osg::notify(osg::NOTICE)<<"Vertical scale "<<m_terrain->getVerticalScale()<<std::endl;

		float inverseVerticalSacle = m_terrain->getVerticalScale();
		m_mapManager->setTerrainScaleZ(inverseVerticalSacle);
		float verticalScale = 1.0/m_terrain->getVerticalScale();
		m_mapManager->getMainDesignNode()->getPointsNode(KL3D_SHOTLINE)->setTerrainScale(verticalScale);
		m_mapManager->getMainDesignNode()->getPointsNode(KL3D_RCVLINE)->setTerrainScale(verticalScale);
		m_mapManager->getMainDesignNode()->getLinesNode(KL3D_SHOTLINE)->setTerrainScale(verticalScale);
		m_mapManager->getMainDesignNode()->getLinesNode(KL3D_RCVLINE)->setTerrainScale(verticalScale);
	}

	//按C键对地形显示进行设置
	if(ea.getKey() == 'c' || ea.getKey() == 'C')
	{
		m_pushC++;
		if(m_pushC%2 == 0)
			m_terrain->setNodeMask(true);
		else if(m_pushC%2 == 1)
			m_terrain->setNodeMask(false);
	}

	//按Alt键是否进行增加点操作
	if(ea.getKey() == 0xFFE9 || ea.getKey() == 0xFFEA)
	{
		m_pushAlt++;
		if(m_pushC%2 == 0)
			m_isAddPoint = false;
		else if(m_pushC%2 == 1)
			m_isAddPoint = true;
	}
}


void KL3DDesignHandle::keyupEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	//判断左右ctrl键是否弹起来取消多选进行操作
	if(ea.getKey() == 0xFFE3 || ea.getKey() == 0xFFE4)
	{
		m_isKeyDown = false;
	}
}


void KL3DDesignHandle::mousePushEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	//如果当前不处于编辑状态，那么直接返回
	if(!m_isEditState)
	{
		return;
	}

	//如果点击右键或中间键，则直接返回
	if(ea.getButton() == 4 || ea.getButton() == 2)
	{
		m_isRightPush = true;
		return;
	}

	m_isRightPush = false;

	//获取鼠标Push时屏幕坐标对应的局部坐标
	osg::Vec3 localCoord = getTerrainCoord(m_initWindowX, m_initWindowY);

	//对m_selExtent设置点击时屏幕坐标对应得局部坐标
	m_selExtent->setPushToLocalCoor(localCoord);

	if(m_selExtent->isInExtent(localCoord))
	{
		m_isMoveOperation = true;
	}
	else
	{
		KL3DEditObject editObject = m_mapManager->getEditObject();
		if(editObject == KL3D_SHOTLINE_EDIT || editObject == KL3D_RCVLINE_EDIT || editObject == KL3D_LINE_EDIT)
		{
			if(isLoactAtEditLines(m_initWindowX, m_initWindowY))
			{
				m_isMoveOperation = true;
			}
			else
			{
				m_isMoveOperation = false;
			}

		}
	}

	//判断进行移动操作KL3DOperationMove还是进行清除操作KL3DOperationClear
	if(!m_isMoveOperation)
	{
		if(m_isKeyDown == false)
		{
			//多边形框选结束之后，在选中区域之外点击清楚上次（或多次）屏幕框选对应的局部（地形)范围
			m_selExtent->clearLocalExtent();

			KL3DOperationBase* pOperation = new KL3DOperationUnsel(m_mapManager);
			pOperation->build();
			delete pOperation;
		}
	}
}


void KL3DDesignHandle::mouseMoveEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	osg::Vec3 position = getTerrainCoord(m_currentWindowX, m_currentWindowY);
	position = position * (m_mapManager->getScaleMatrix());
	if(position.z() < 0.0001)
	{
		position.z() = 0;
	}
}


void KL3DDesignHandle::mouseDragEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	//如果当前不处于编辑状态操作，那么直接返回
	if(!m_isEditState)
	{
		return;
	}

	//如果点击鼠标中间键或者右键，那么拖拉不做任何工作
	if(m_isRightPush == true)
	{
		return;
	}

	//判断是否为移动选中点
	osg::Vec3 initLoaclCoord = getTerrainCoord(m_initWindowX, m_initWindowY);

	if(!m_isMoveOperation)
	{
		m_drawPointArray->clear();
		m_drawColorArray->clear();
		m_drawPointArray->push_back(osg::Vec3(m_initWindowXnormal, 0.0f, m_initWindowYnormal));
		m_drawPointArray->push_back(osg::Vec3(m_currentWindowXnormal, 0.0f, m_initWindowYnormal));
		m_drawPointArray->push_back(osg::Vec3(m_currentWindowXnormal, 0.0f, m_currentWindowYnormal));
		m_drawPointArray->push_back(osg::Vec3(m_initWindowXnormal, 0.0f, m_currentWindowYnormal));
		m_drawColorArray->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));

		osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry();
		pGeometry->setDataVariance(osg::Object::DYNAMIC);
		pGeometry->setUseDisplayList(false);
		pGeometry->setVertexArray(m_drawPointArray);
		pGeometry->setColorArray(m_drawColorArray);
		pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, m_drawPointArray->size()));
		drawEditGeometry(pGeometry);
	}
}


void KL3DDesignHandle::mouseReleaseEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	//如果当前不处于编辑操作， 那么直接返回
	if(!m_isEditState)
	{
		return;
	}

	//判断是否为移动选中点
	osg::Vec3 initLocalCoord = getTerrainCoord(m_initWindowX, m_initWindowY);

	if(!m_isMoveOperation)
	{
		//清除选择框
		if(m_drawCamera.valid())
		{
			osg::Group* pRoot = dynamic_cast<osg::Group*>(m_viewer->getSceneData());
			pRoot->removeChild(m_drawCamera);
			m_drawCamera = NULL;
		}

		float xWindowMin = m_initWindowX < m_endWindowX ? m_initWindowX : m_endWindowX;
		float xWindowMax = m_initWindowX >= m_endWindowX ? m_initWindowX : m_endWindowX;
		float yWindowMin = m_initWindowY < m_endWindowY ? m_initWindowY : m_endWindowY;
		float yWindowMax = m_initWindowY >= m_endWindowY ? m_initWindowY : m_endWindowY;

		//先设置非点选
		m_selExtent->setIsPtSel(false);

		//如果xWindowMin 和 xWindowMax相同，yWindowMin与yWindowMax相同，则说明是点选，那么把选择框设置为下
		if((xWindowMin == xWindowMax) && (yWindowMin == yWindowMax))
		{
			xWindowMin -= KL3D_SINGLESEL_OFFSET;
			xWindowMax += KL3D_SINGLESEL_OFFSET;
			yWindowMin -= KL3D_SINGLESEL_OFFSET;
			yWindowMax += KL3D_SINGLESEL_OFFSET;

			//如果鼠标push和release的坐标相同，判断为点选
			m_selExtent->setIsPtSel(true);
		}

		osg::Vec3 downLeftLoaclCoord = getTerrainCoord(xWindowMin, yWindowMin);
		osg::Vec3 upLeftLocalCoord = getTerrainCoord(xWindowMin, yWindowMax);
		osg::Vec3 downRightLoaclCoord = getTerrainCoord(xWindowMax, yWindowMin);
		osg::Vec3 upRightLoaclCoord = getTerrainCoord(xWindowMax, yWindowMax);

		m_selExtent->setExtentWindow(xWindowMin, yWindowMin, xWindowMax, yWindowMax);
		m_selExtent->setSelectType(SEL_REC);

		osg::ref_ptr<osg::Vec3Array> pLocalArray = new osg::Vec3Array();
		pLocalArray->push_back(upLeftLocalCoord);
		pLocalArray->push_back(upRightLoaclCoord);
		pLocalArray->push_back(downRightLoaclCoord);
		pLocalArray->push_back(downLeftLoaclCoord);
		m_selExtent->setLocalExtent(pLocalArray);

		KL3DOperationBase* pOperation = new KL3DOperationSel(m_mapManager,m_selExtent);
		pOperation->build();
		delete pOperation;

	}
	else //move operation
	{
		osg::Vec3 endLocalCoord = getTerrainCoord(m_endWindowX, m_endWindowY);
		osg::Vec3 offset = endLocalCoord - initLocalCoord;
		m_selExtent->changeSelExtent(offset);

		KL3DOperationBase* pOperation = new KL3DOperationMove(m_mapManager, offset);
		pOperation->build();
		delete pOperation;

		m_isMoveOperation = false;
	}
}

void KL3DDesignHandle::mouseScrollEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	m_mapManager->resetPointSize();

	m_mapManager->designPointsRarefying();
}


osg::Vec3 KL3DDesignHandle::getTerrainCoord(const float& x, const float& y)
{
	osg::Vec3 realVec;
	osgUtil::LineSegmentIntersector::Intersections intersections; //创建一个线段交集检测对象
	if(m_viewer->computeIntersections(x, y, intersections))
	{
		osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
		//hitr++;
		realVec = hitr->getWorldIntersectPoint();
		//realVec = getTerrainCoordFine(*hitr);
	}

	return realVec;
}


void KL3DDesignHandle::forbidEditObject()
{
	KL3DOperationBase* pOperation = new KL3DOperationForbid(m_mapManager);
	pOperation->build();
	delete pOperation;

	clearEditPoints();
}


void KL3DDesignHandle::activeEditObject()
{
	KL3DOperationBase* pOperation = new KL3DOperationActive(m_mapManager);
	pOperation->build();
	delete pOperation;

	clearEditPoints();
}


void KL3DDesignHandle::deleteEditObject()
{
	KL3DOperationBase* pOperation = new KL3DOperationDelete(m_mapManager);
	pOperation->build();
	delete pOperation;

	clearEditPoints();
}


KL3DEditObject KL3DDesignHandle::getEditObject()
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


void KL3DDesignHandle::clearEditPoints()
{
	KL3DOperationBase* pOperation = new KL3DOperationUnsel(m_mapManager);
	pOperation->build();
	delete pOperation;

	delete m_selExtent;
	m_selExtent = new KL3DSelExtent();
}


bool KL3DDesignHandle::isLoactAtEditLines(const float& xWindow, const float& yWindow)
{
	KL3DMapCache* pCache = m_mapManager->getMainCache();
	KL3DEditLineSet* pEditLines = pCache->getEditLines();
	if(pEditLines->empty())
	{
		return false;
	}

	KL3DSelExtent pSelExtent;
	pSelExtent.setExtentWindow(xWindow - KL3D_SINGLESEL_OFFSET, yWindow - KL3D_SINGLESEL_OFFSET, xWindow + KL3D_SINGLESEL_OFFSET, yWindow + KL3D_SINGLESEL_OFFSET);

	for(unsigned int i = 0; i < pEditLines->size(); ++i)
	{
		KL3DLine* pLine = (*pEditLines)[i];
		KL3DPointVector* p3DPoints = pLine->getPointVector();

		for(unsigned int j = 0; j < p3DPoints->size(); ++j)
		{
			//获取点的坐标，然后记性判断
			KL3DPoint* pPoint = (*p3DPoints)[j];
			osg::Vec3f coord = pPoint->getCoord();
			osg::Vec3 windowCoord = localToScreen(coord);

			if(pSelExtent.isInExtentWindow(windowCoord))
			{
				return true;
			}
		}
	}

	return false;
}


osg::Vec3 KL3DDesignHandle::localToScreen(const osg::Vec3& worldpoint)
{
	//修改世界坐标向屏幕坐标转换
	osg::Vec3 windowPoint;

	osgViewer::Viewer* pViewer = m_mapManager->getID();
	osg::Camera* camera = pViewer->getCamera();
	osg::Matrix modelViewMatrix = camera->getViewMatrix();
	osg::Matrix projectionMatrix = camera->getProjectionMatrix();
	osg::Matrix windowMatrix = camera->getViewport()->computeWindowMatrix();

	osg::Matrix MPW = modelViewMatrix * projectionMatrix * windowMatrix;

	windowPoint = worldpoint * MPW;

	return windowPoint;
}


bool KL3DDesignHandle::notifyUpdateView()
{
	int size = m_mapManager->getMainCache()->getEditPoints()->size() + m_mapManager->getMainCache()->getEditLines()->size();
	return (size > 0) ? true : false;
}


bool KL3DDesignHandle::notifyShotUpdateView()
{
	KL3DDesignNode* pDesignNode = m_mapManager->getMainDesignNode();
	if(pDesignNode == NULL)
	{
		return false;
	}

	KL3DPointsNode* pPointsNode = pDesignNode->getPointsNode(KL3D_SHOTLINE);
	if(pDesignNode == NULL)
	{
		return false;
	}

	bool isUpdate = pPointsNode->getIsVisible();

	if(!m_mapManager->getMainDesignNode()->getIsVisble())
	{
		isUpdate = false;
	}

	return isUpdate;
}


bool KL3DDesignHandle::notifyRcvUpdateView()
{
	KL3DDesignNode* pDesignNode = m_mapManager->getMainDesignNode();
	if(pDesignNode == NULL)
	{
		return false;
	}

	KL3DPointsNode* pPointsNode = pDesignNode->getPointsNode(KL3D_RCVLINE);
	if(pDesignNode == NULL)
	{
		return false;
	}

	bool isUpdate = pPointsNode->getIsVisible();

	if(!m_mapManager->getMainDesignNode()->getIsVisble())
	{
		isUpdate = false;
	}

	return isUpdate;
}