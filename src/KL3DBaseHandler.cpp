#include <osg/PolygonMode>
#include <osg/lineWidth>

#include "KL3DBaseHandler.h"

KL3DBaseHandler::KL3DBaseHandler():
	m_initWindowX(FLT_MAX),
	m_initWindowY(FLT_MAX),
	m_initWindowXnormal(FLT_MAX),
	m_initWindowYnormal(FLT_MAX),
	m_initLocalX(FLT_MAX),
	m_initLoaclY(FLT_MAX),
	m_currentWindowX(FLT_MAX),
	m_currentWindowY(FLT_MAX),
	m_currentWindowXnormal(FLT_MAX),
	m_currentWindowYnormal(FLT_MAX),
	m_currentLoaclX(FLT_MAX),
	m_currentLocalY(FLT_MAX),
	m_endWindowX(FLT_MAX),
	m_endWindowY(FLT_MAX),
	m_endWindowXnormal(FLT_MAX),
	m_endWindowYnormal(FLT_MAX),
	m_endLoaclX(FLT_MAX),
	m_endlocalY(FLT_MAX),
	m_drawColorArray(new osg::Vec4Array()),
	m_drawPointArray(new osg::Vec3Array()),
	m_drawCamera(NULL),
	m_viewer(NULL),
	m_isEditState(false),
	m_isKeyDown(false)
{

}


KL3DBaseHandler::~KL3DBaseHandler()
{

}


bool KL3DBaseHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	//得到场景的视景器对象
	m_viewer = dynamic_cast<osgViewer::Viewer*>(&aa);

	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			keydownEvent(ea, aa);
			return m_isEditState;
		}

	case(osgGA::GUIEventAdapter::KEYUP):
		{
			keyupEvent(ea, aa);
			return m_isEditState;
		}
	case(osgGA::GUIEventAdapter::PUSH):
		{
			if(ea.getButton() == 1)
			{
				m_initWindowX = ea.getX();
				m_initWindowY = ea.getY();
				m_initWindowXnormal = ea.getXnormalized();
				m_initWindowYnormal = ea.getYnormalized();
			}
			mousePushEvent(ea, aa);
			return m_isEditState;
		}

	case(osgGA::GUIEventAdapter::MOVE):
		{
			m_currentWindowX = ea.getX();
			m_currentWindowY = ea.getY();
			m_currentWindowXnormal = ea.getXnormalized();
			m_currentWindowYnormal = ea.getYnormalized();

			mouseMoveEvent(ea, aa);
			return m_isEditState;
		}

	case(osgGA::GUIEventAdapter::DRAG):
		{
			m_currentWindowX = ea.getX();
			m_currentWindowY = ea.getY();
			m_currentWindowXnormal = ea.getXnormalized();
			m_currentWindowYnormal = ea.getYnormalized();

			mouseDragEvent(ea, aa);
			return m_isEditState;
		}

	case(osgGA::GUIEventAdapter::DOUBLECLICK):
		{
			if(ea.getButton() == 1)
			{
				m_doubleClickWindowX = ea.getX();
				m_doubleClickWindowY = ea.getY();
				m_doubleClickWindowXnormal = ea.getXnormalized();
				m_doubleClickWindowYnormal = ea.getYnormalized();	

				mouseDoubleClickEvent(ea, aa);
			}
	
			return m_isEditState;
		}

	case(osgGA::GUIEventAdapter::RELEASE):
		{
			if(ea.getButton() == 1)
			{
				m_endWindowX = ea.getX();
				m_endWindowY = ea.getY();
				m_endWindowXnormal = ea.getXnormalized();
				m_endWindowYnormal = ea.getYnormalized();

				mouseReleaseEvent(ea, aa);
			}

			return m_isEditState;
		}

	case(osgGA::GUIEventAdapter::SCROLL):
		{
			mouseScrollEvent(ea, aa);
			return false;
		}
	}

	return false;
}



void KL3DBaseHandler::keydownEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{

}


void KL3DBaseHandler::keyupEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{

}


void KL3DBaseHandler::mousePushEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{

}


void KL3DBaseHandler::mouseMoveEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{

}


void KL3DBaseHandler::mouseDragEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{

}


void KL3DBaseHandler::mouseDoubleClickEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{

}


void KL3DBaseHandler::mouseReleaseEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{

}


void KL3DBaseHandler::mouseScrollEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{

}


void KL3DBaseHandler::setEditState(bool isEdit)
{
	m_isEditState = isEdit;
}


void KL3DBaseHandler::getLoacalPoints(float& windowX, float& windowY, float& localX, float& localY)
{

}


void KL3DBaseHandler::drawEditGeometry(osg::ref_ptr<osg::Geometry> pGeometry)
{
	//将Geometry对象加载到叶节点
	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode();
	pGeode->addDrawable(pGeometry);

	osg::ref_ptr<osg::PolygonMode> pPolyMode = new osg::PolygonMode();
	pPolyMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	pGeometry->getOrCreateStateSet()->setAttributeAndModes(pPolyMode.get());
	pGeometry->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);

	osg::ref_ptr<osg::LineWidth> pLineWidth = new osg::LineWidth(2.0f);
	pGeometry->getOrCreateStateSet()->setAttribute(pLineWidth, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);

	//创建绘制相机，将相机挂载在场景节点下
	osg::ref_ptr<osg::Camera> pCamera = new osg::Camera();
	pCamera->setProjectionMatrix(osg::Matrix::ortho2D(-1.0f, 1.0f, -1.0f, 1.0f));
	pCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	pCamera->setViewMatrixAsLookAt(osg::Vec3d(0, -1, 0), osg::Vec3d(0, 0, 0), osg::Vec3d(0, 0, 1));
	pCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
	pCamera->setRenderOrder(osg::Camera::POST_RENDER);
	pCamera->setAllowEventFocus(false);
	pCamera->addChild(pGeode.get());

	//将绘制编辑框的相机节点添加到场景节点下
	osg::Node* pRoot = m_viewer->getSceneData();
	if(m_drawCamera.valid())
	{
		pRoot->asGroup()->replaceChild(m_drawCamera, pCamera);	
	}
	else
	{
		pRoot->asGroup()->addChild(pCamera);
	}
	m_drawCamera = pCamera;

}