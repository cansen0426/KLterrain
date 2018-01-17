#ifndef __KL3DBASEHANDLE_H__
#define __KL3DBASEHANDLE_H__

#include <osgViewer/Viewer>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>
#include <osg/Geometry>
#include <osg/Geode>

/*!***************************************
<br>��˵���� ��ά������������
*****************************************/

class KL3DBaseHandler : public osgGA::GUIEventHandler
{
public:

	/*!Ĭ�Ϲ��캯��*/
	KL3DBaseHandler();

	/*!��д�����handle����*/
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��Ӧ���̰����¼�*/
	virtual void keydownEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��Ӧ���̵����¼�*/
	virtual void keyupEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!���push�¼�*/
	virtual void mousePushEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!���Move�¼�*/
	virtual void mouseMoveEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!���Drag�¼�*/
	virtual void mouseDragEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!���˫���¼�*/
	virtual void mouseDoubleClickEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!���Release�¼�*/
	virtual void mouseReleaseEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��Ӧ�������¼�*/
	virtual void mouseScrollEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!���Ʊ༭�Ķ����*/
	virtual void drawEditGeometry(osg::ref_ptr<osg::Geometry> pGeometry);

	/*!�õ���Ļ�����Ӧ�ľֲ�����*/
	void getLoacalPoints(float& windowX, float& windowY, float& localX, float& localY);

	/*!���ó����ı༭״̬*/
	void setEditState(bool isEdit);

protected:
	/*!��������*/
	virtual ~KL3DBaseHandler();

protected:

	/*!��ǰ��������*/
	osgViewer::Viewer* m_viewer;

	/*!���pushʱ����Ļ����*/
	float m_initWindowX, m_initWindowY;

	/*!���Move����Dragʱ����Ļ����*/
	float m_currentWindowX, m_currentWindowY;

	/*!���Releaseʱ����Ļ����*/
	float m_endWindowX, m_endWindowY;

	/*!���doubleClickʱ����Ļ����*/
	float m_doubleClickWindowX, m_doubleClickWindowY;

	/*!���pushʱ����Ļ�����һֵ*/
	float m_initWindowXnormal, m_initWindowYnormal;

	/*!���Move����Dragʱ����Ļ�����һֵ*/
	float m_currentWindowXnormal, m_currentWindowYnormal;

	/*!���Releaseʱ����Ļ�����һֵ*/
	float m_endWindowXnormal, m_endWindowYnormal;

	/*!���doubleClickʱ����Ļ�����һֵ*/
	float m_doubleClickWindowXnormal, m_doubleClickWindowYnormal;

	/*!���pushʱ���ֲ�����*/
	float m_initLocalX, m_initLoaclY, m_initLocalZ;

	/*!���Move����Dragʱ���ֲ�����*/
	float m_currentLoaclX, m_currentLocalY, m_currentLocalZ;

	/*!���releaseʱ���ֲ�����*/
	float m_endLoaclX, m_endlocalY, m_endLocalZ;

	/*!��ʶ����ǰ�����ı༭״̬*/
	bool m_isEditState;

	/*!��ʾ�༭ͼ�ε�����ڵ�*/
	osg::ref_ptr<osg::Camera> m_drawCamera;

	/*!��ű༭ͼ�εĶ�������*/
	osg::ref_ptr<osg::Vec3Array> m_drawPointArray;

	/*!��ű༭ͼ�ε���ɫ����*/
	osg::ref_ptr<osg::Vec4Array> m_drawColorArray;

	/*!��־�������Ƿ񰸼�*/
	bool m_isKeyDown;
};



#endif