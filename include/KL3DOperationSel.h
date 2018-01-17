#ifndef __KL3DOPERATION_H__
#define __KL3DOPERATION_H__

#include "KL3DOperationBase.h"

/*!************************************************
<br> 类说明： 三维观测系统选择操作类
***************************************************/

class KL3DOperationSel : public KL3DOperationBase
{
public:
	/*!默认构造函数*/
	KL3DOperationSel(KL3DMapManager* pMapManager, KL3DSelExtent* pSelExtent);

	/*!默认析构函数*/
	virtual ~KL3DOperationSel();

	/*!初始化函数*/
	virtual void init();

	/*!build函数*/
	virtual void build();

protected:
	/*!编辑对象为点*/
	void selPoint(KL3DMapCache* pCache, KL3DLineSet* pLines);

	/*!编辑对象为点（利用omp并行选择）*/
	void selPointByOmp(KL3DMapCache* pCache, KL3DLineSet* pLines);

	/*!编辑对象为点（利用omp并行选择,选择方式为点选，点选和框选所用的方法相同，点选时只能选择一个最合适的;
	对于炮点和检点单独点选的时候，另一方默认为空）*/
	void selPointByOmpForPtClick(KL3DMapCache* pCache, KL3DLineSet* pLines, KL3DLineSet* pLines2 = NULL);

	/*!编辑对象为线*/
	void selLine(KL3DMapCache* pCache, KL3DLineSet* pLines);

	/*!编辑对象为线(利用omp并行选择)*/
	void selLineByOmp(KL3DMapCache* pCache, KL3DLineSet* pLines);

	/*!编辑对象为线(利用omp并行选择,选择方式为点选，先根据点击点获取周围所有的点，找到最近的点后
	根据此点找到最合适的线;对于炮线和检线单独点选的时候，另一方默认为空)*/
	void selLineByOmpForPtClick(KL3DMapCache* pCache, KL3DLineSet* pLines, KL3DLineSet* pLines2 = NULL);

	/*!点选时得到点击点周围的所有点*/
	KL3DEditPointSet getAllEditPointByPtClick(KL3DMapCache* pCache, KL3DLineSet* pLines);

	/*!计算得到离pushToLocalCoor最近的一个点*/
	KL3DEditPoint getEditPointByCoor(const osg::Vec3& pushToLocalCoor, KL3DEditPointSet& pAllSelPoint);

	/*!局部坐标转换为屏幕坐标*/
	osg::Vec3 localToScreen(const osg::Vec3& worldPoint);

protected:
	/*!三维观测系统选择区域*/
	KL3DSelExtent* m_selExtents;

	/*!三维观测系统选择编辑对象*/
	KL3DEditObject m_editObject;
};


#endif