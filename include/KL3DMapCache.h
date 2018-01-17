#ifndef __KL3DMAPCACHE_H__
#define __KL3DMAPCACHE_H__

#include <map>
#include <vector>

#include "KL3DLine.h"
#include "KL3DCommonStruct.h"

/*!****************************************************
<br>类说明：三维观测系统数据类（对应单窗口单方案观测系统）
*******************************************************/
/*!线的集合*/
#define KL3DLineSet std::map<double, KL3DLine*>
#define KL3DEditPointSet std::vector<KL3DEditPoint>
#define KL3DEditLineSet std::vector<KL3DLine*>

class KL3DMapCache
{
public:
	/*!默认构造函数*/
	KL3DMapCache();

	/*!默认析构函数*/
	~KL3DMapCache();

	/*!设置ID,观测系统的标识*/
	void setID(const std::string& id);

	/*!得到观测系统的标识*/
	std::string getID() const;

	/*!得到炮线的集合*/
	KL3DLineSet* getShotLineSet();

	/*!得到检波线的集合*/
	KL3DLineSet* getRcvLineSet();

	/*!得到编辑点的集合*/
	KL3DEditPointSet* getEditPoints();

	/*!得到编辑线集合*/
	KL3DEditLineSet* getEditLines();

	/*!查询得到炮检点对象*/
	KL3DPoint* get3DPoint(const double& lineID, const double& pointID, const short& samestakeID, KL3DLineType lineType);

	/*!向观测系统中插入炮线*/
	bool insertLine(KL3DLine* pLine);

	/*!删除三维数据线*/
	bool deleteLine(KL3DLine* pLine);

	/*!根据线号和类型得到三维线对象*/
	KL3DLine* getLine(double id, KL3DLineType type);

	/*!向观测系统中插入编辑点*/
	bool insertEditPoint(KL3DEditPoint pEditPoint);

	/*!向观测系统中插入编辑线*/
	bool insertEditLine(KL3DLine* pLine);

	/*!向观测系统中插入关系片炮点*/
	bool insertPatchSelPoint(KL3DEditPoint pPatchSelPoint);

	/*!得到观测系统中关系片炮点集合*/
	KL3DEditPointSet* getPatchSelPoints();

	/*!得到观测系统中关系片检波点集合*/
	KL3DEditPointSet* getPatchDstPoints();

	/*!清空选择区域*/
	void clearEditData();

	/*!清空关系片数据*/
	void clearPatchPoints();

	/*!设置x坐标偏移量*/
	void setXOffset(const float& xOffset);

	/*!设置y坐标偏移量*/
	void setYOffset(const float& yOffset);

	/*!获取x坐标偏移量*/
	float getXOffset() const;

	/*!获取y坐标偏移量*/
	float getYOffset() const;

	/*!设置编辑区域移动的距离：x方向*/
	void setXMoveOffset(double& offset);

	/*!设置编辑区域移动的距离：y方向*/
	void setYMoveOffset(double& offset);

	/*!得到编辑区域移动的距离：x方向*/
	double getXMoveOffset() const;

	/*!得到编辑区域移动的距离：y方向*/
	double getYMoveOffset() const;

	/*!设置与地表偏移量*/
	void setDePature(const double& depature);

	/*!得到与地表的偏移量*/
	double getDepature() const;

private:
	/*!ID:string类型，观测系统唯一标识*/
	std::string m_id;

	/*!炮线集合*/
	KL3DLineSet* m_shotLines;

	/*!检波线集合*/
	KL3DLineSet* m_rcvLines;

	/*!编辑点集合*/
	KL3DEditPointSet m_editPoints;

	/*!编辑线集合*/
	KL3DEditLineSet m_editLines;

	/*!关系片炮点集合*/
	KL3DEditPointSet m_patchSelPoints;

	/*!关系片检波点集合*/
	KL3DEditPointSet m_patchDstPoints;

	/*!编辑点移动偏移距离：x方向*/
	double m_xMoveOffset;

	/*!编辑点移动偏移距离：y方向*/
	double m_yMoveOffset;

	/*!坐标x方向偏移量*/
	float m_xOffset;

	/*!坐标y方向偏移量*/
	float m_yOffset;

	/*!与地表的偏移量：用于井深设计*/
	double m_depature;



};

#endif