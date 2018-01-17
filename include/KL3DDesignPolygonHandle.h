#ifndef __KL3DDESIGNPOLYGONHANDLE_H__
#define __KL3DDESIGNPOLYGONHANDLE_H__

#include <OpenThreads/Thread>
#include <osgTerrain/Terrain>

#include "KL3DOperationBase.h"
#include "KL3DBaseHandler.h"
#include "KL3DMapManager.h"

/*!*****************************************************
<br>类说明：三维观测系统多边形框选交互类
*******************************************************/

class KL3DDesignPolygonHandle : public KL3DBaseHandler
{
public:
	/*!默认构造函数*/
	KL3DDesignPolygonHandle(KL3DMapManager* pMapManager,osgTerrain::Terrain* pTerrain = NULL);

	/*!重写键盘按键事件*/
	virtual void keydownEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!重写键盘弹起事件*/
	virtual void keyupEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!重写鼠标push事件*/
	virtual void mousePushEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!重写鼠标Move事件*/
	virtual void mouseMoveEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!重写鼠标drag事件*/
	virtual void mouseDragEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!重写鼠标Release事件*/
	virtual void mouseReleaseEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!重写鼠标Release事件*/
	virtual void mouseDoubleClickEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!重写鼠标Scroll事件*/
	virtual void mouseScrollEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!重写得到地形坐标的函数*/
	virtual osg::Vec3 getTerrainCoord(const float& x, const float& y);

	/*!禁止操作*/
	virtual void forbidEditObject();

	/*!激活操作*/
	virtual void activeEditObject();

	/*!删除操作*/
	virtual void deleteEditObject();

	/*!清除观测系统所选对象*/
	void clearEditPoints();

	/*!清除观测系统的多边形框*/
	void clearPolygonGeometry();

	/*!选中后通知视图刷新*/
	bool notifyUpdateView();

	/*!通知视图是否显示炮点编辑按钮*/
	bool notifyShotUpdateView();

	/*!通知视图是否显示检波点编辑按钮*/
	bool notifyRcvUpdateView();

protected:
	/*!析构函数*/
	virtual ~KL3DDesignPolygonHandle();

	/*!获取当前编辑对象*/
	KL3DEditObject getEditObject();

	/*!线选时，判断鼠标按下的位置是否落在已经选择的线上*/
	bool isLoactAtEditLines(const float& xWindow, const float& yWindow);

	/*!根据单独的线程根据cpu插值算法获取高程*/
	void updateDemByCPU(bool isUpdate);

	/*!局部坐标转换成屏幕坐标*/
	osg::Vec3 localToScreen(const osg::Vec3& worldpoint);

	/*!得到屏幕坐标转换为局部坐标的精确值*/
	osg::Vec3 getTerrainCoordFine(const osgUtil::LineSegmentIntersector::Intersection* result);

	/*!根据屏幕坐标获取到与模型的局部坐标*/
	int getLocalInsectionCoord(osg::Vec3& upLeftLoaclCoord, osg::Vec3& upRightLoaclCoord, osg::Vec3& downLeftLocalCoord, osg::Vec3& downRightLoaclCoord,
		const float& xWindowMin, const float& xWindowMax, const float& yWindowMin, const float& yWindowMax );

protected:

	/*!单窗口多方案管理器对象*/
	KL3DMapManager* m_mapManager;

	/*!标识:炮点是否处于编辑状态*/
	bool m_isShotPointEdit;

	/*!标识：炮线是否处于编辑状态*/
	bool m_isShotLineEdit;

	/*!标识：检波点是否处于编辑状态*/
	bool m_isRcvPointEdit;

	/*!标识：检波线是否处于编辑状态*/
	bool m_isRcvLineEdit;

	/*!判断当前是否进行移动操作*/
	bool m_isMoveOperation;

	/*!框选区域*/
	KL3DSelExtent* m_selExtent;

	/*!记录屏幕框选区域的数组*/
	osg::ref_ptr<osg::Vec2Array> m_recordScrArray;

	/*!记录Z键按键次数，用于炮点大小的变化*/
	unsigned int m_pushZ;

	/*!记录X键按键次数，用于检点大小的变化*/
	unsigned int m_pushX;

	/*!记录C键按键次数，用于地形的显示*/
	unsigned int m_pushC;

	/*!记录V键按键次数，用于炮检线的显示*/
	unsigned int m_pushV;

	/*!交互的地形数据*/
	osgTerrain::Terrain* m_terrain;
};

#endif