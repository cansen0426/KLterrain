#ifndef __KL3DBASEHANDLE_H__
#define __KL3DBASEHANDLE_H__

#include <osgViewer/Viewer>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>
#include <osg/Geometry>
#include <osg/Geode>

/*!***************************************
<br>类说明： 三维场景交互基类
*****************************************/

class KL3DBaseHandler : public osgGA::GUIEventHandler
{
public:

	/*!默认构造函数*/
	KL3DBaseHandler();

	/*!重写父类的handle方法*/
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!响应键盘按下事件*/
	virtual void keydownEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!响应键盘弹起事件*/
	virtual void keyupEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!鼠标push事件*/
	virtual void mousePushEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!鼠标Move事件*/
	virtual void mouseMoveEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!鼠标Drag事件*/
	virtual void mouseDragEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!鼠标双击事件*/
	virtual void mouseDoubleClickEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!鼠标Release事件*/
	virtual void mouseReleaseEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!响应鼠标滚轮事件*/
	virtual void mouseScrollEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!绘制编辑的多边形*/
	virtual void drawEditGeometry(osg::ref_ptr<osg::Geometry> pGeometry);

	/*!得到屏幕坐标对应的局部坐标*/
	void getLoacalPoints(float& windowX, float& windowY, float& localX, float& localY);

	/*!设置场景的编辑状态*/
	void setEditState(bool isEdit);

protected:
	/*!析构函数*/
	virtual ~KL3DBaseHandler();

protected:

	/*!当前场景对象*/
	osgViewer::Viewer* m_viewer;

	/*!鼠标push时的屏幕坐标*/
	float m_initWindowX, m_initWindowY;

	/*!鼠标Move或者Drag时的屏幕坐标*/
	float m_currentWindowX, m_currentWindowY;

	/*!鼠标Release时，屏幕坐标*/
	float m_endWindowX, m_endWindowY;

	/*!鼠标doubleClick时的屏幕坐标*/
	float m_doubleClickWindowX, m_doubleClickWindowY;

	/*!鼠标push时的屏幕坐标归一值*/
	float m_initWindowXnormal, m_initWindowYnormal;

	/*!鼠标Move或者Drag时的屏幕坐标归一值*/
	float m_currentWindowXnormal, m_currentWindowYnormal;

	/*!鼠标Release时，屏幕坐标归一值*/
	float m_endWindowXnormal, m_endWindowYnormal;

	/*!鼠标doubleClick时的屏幕坐标归一值*/
	float m_doubleClickWindowXnormal, m_doubleClickWindowYnormal;

	/*!鼠标push时，局部坐标*/
	float m_initLocalX, m_initLoaclY, m_initLocalZ;

	/*!鼠标Move或者Drag时，局部坐标*/
	float m_currentLoaclX, m_currentLocalY, m_currentLocalZ;

	/*!鼠标release时，局部坐标*/
	float m_endLoaclX, m_endlocalY, m_endLocalZ;

	/*!标识：当前场景的编辑状态*/
	bool m_isEditState;

	/*!显示编辑图形的相机节点*/
	osg::ref_ptr<osg::Camera> m_drawCamera;

	/*!存放编辑图形的顶点数组*/
	osg::ref_ptr<osg::Vec3Array> m_drawPointArray;

	/*!存放编辑图形的颜色数组*/
	osg::ref_ptr<osg::Vec4Array> m_drawColorArray;

	/*!标志：键盘是否案件*/
	bool m_isKeyDown;
};



#endif