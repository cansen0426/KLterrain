#ifndef __KL3DPERATIONBASE_H__
#define __KL3DPERATIONBASE_H__

#include "KL3DMapManager.h"

/*!**********************************************************
<br> 类说明：三维观测系统操作的基类
***********************************************************/

class KL3DOperationBase
{
public:
	/*!默认构造函数*/
	KL3DOperationBase();

	/*!构造函数*/
	KL3DOperationBase(KL3DMapManager* pMapManager);

	/*!默认析构函数*/
	virtual ~KL3DOperationBase();

	/*!初始化函数*/
	virtual void init();

	/*!创建操作函数*/
	virtual void build();

protected:
	/*!单窗口多方案管理对象*/
	KL3DMapManager* m_mapManager;
};

/*!框选的类型*/
typedef enum
{
	SEL_REC,
	SEL_POLOYGON
}KL3DSelectType;


/*!*************************************************************
<br>类说明：框选范围类
****************************************************************/

class KL3DSelExtent
{
public:
	/*!默认构造函数*/
	KL3DSelExtent();

	/*!重载构造函数*/
	KL3DSelExtent(osg::Vec3& upLeft, osg::Vec3& upRight, osg::Vec3& downRight, osg::Vec3& downLeft);

	/*!默认析构函数*/
	virtual ~KL3DSelExtent();

	/*!设置selExtent的范围*/
	void setExtent(osg::Vec3& upLeft, osg::Vec3& upRight, osg::Vec3& downRight, osg::Vec3& downLeft);

	/*!设置setExtentWindow的范围*/
	void setExtentWindow(const float& xmin, const float& ymin, const float& xmax, const float& ymax);

	/*!设置多边形框选的范围*/
	void setPolygonExtentWindow(osg::Vec2Array* pscreenArray);

	/*!设置屏幕选择对应的局部范围*/
	void setLocalExtent(osg::Vec3Array* plocalArray);

	/*!清楚屏幕选择对应的局部范围*/
	void clearLocalExtent();

	/*!判断是否在选框（有一个或多个）范围内（屏幕坐标转局部坐标）*/
	bool isInExtent(const osg::Vec3& coord);

	/*!判断是否在某个框选范围内（屏幕坐标转局部坐标）*/
	bool isInOnePolygonExtent(const osg::Vec3& coord, osg::Vec3Array* pLocalArray);

	/*!判断是否在多选框内*/
	bool isInExtentWindow(const osg::Vec3& coord);

	/*!选择区域屏幕坐标数组对应的局部左边数组添加一个偏移量，即为局部选框添加一个偏移量*/
	void changeSelExtent(const osg::Vec3& offset);

	/*!设置框选类型*/
	void setSelectType(const KL3DSelectType pType);

	/*!设置是否点选*/
	void setIsPtSel(bool pIsPtSel){m_isPtSel = pIsPtSel;};

	/*!得到是否点选*/
	bool getIsPtSel(){return m_isPtSel;};

	/*!设置push时屏幕点对应的局部点坐标*/
	void setPushToLocalCoor(const osg::Vec3& pPustTocal){m_pushToLocalCoor = pPustTocal;};

	/*!push时屏幕点对应的局部点*/
	osg::Vec3 getPushToLocalCoor(){return m_pushToLocalCoor;};

protected:
	/*!判断是否在矩形多选框内（局部坐标转换为屏幕坐标）*/
	bool isInRecExtentWindow(const osg::Vec3& coord);

	/*!判断是否在多边形多选框内（局部坐标转换为屏幕坐标）*/
	bool isInPolygonExtentWindow(const osg::Vec3& coord);

private:
	/*!选择区域左上角映射到地形的坐标*/
	osg::Vec3 m_upLeftCoord;

	/*!选择区域右上角映射到地形的坐标*/
	osg::Vec3 m_upRightCoord;

	/*!选择区域右下角映射到地形的坐标*/
	osg::Vec3 m_downRightCoord;

	/*!选择区域左下角映射到地形的坐标*/
	osg::Vec3 m_downLefeCoord;

	/*!选择区域屏幕坐标x*/
	float m_windowXmin, m_windowXmax;

	/*!选择区域屏幕坐标y*/
	float m_windowYmin, m_windowYmax;

	/*!选择区域屏幕坐标数组*/
	osg::ref_ptr<osg::Vec2Array> m_screenArray;

	/*!选择区域屏幕坐标数组对应的局部坐标数组(多次选择的存储)*/
	std::vector<osg::ref_ptr<osg::Vec3Array>> m_localArrayVector;

	/*!框选的类型*/
	KL3DSelectType m_selectType;

	/*！是否为点选*/
	bool m_isPtSel;

	/*!负责记录屏幕push点对应的局部坐标点*/
	osg::Vec3 m_pushToLocalCoor;
};
#endif