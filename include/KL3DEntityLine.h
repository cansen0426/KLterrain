#ifndef __KL3DENTITYLINE_H__
#define __KL3DENTITYLINE_H__

#include "KL3DTerrainTileManager.h"
#include "KL3DBaseEntity.h"

/*!***************************************
<br>类说明： 三维线状图元
*****************************************/

class KL3DEntityLine: public KL3DBaseEntity
{
public:
	/*!默认构造函数*/
	KL3DEntityLine();

	/*!默认析构函数*/
	~KL3DEntityLine();

	/*!初始化函数*/
	virtual void init();

	/*!设置拐点序列*/
	void setPointArray(osg::Vec3Array* pPointArray);
	
	/*!设置线宽*/
	void setLineWidth(const float& pLineWidth);

	/*!设置线样式*/
	/*!线样式pLineStyle：LineSolid/LineDash/LineDot/LineDashDot*/
	void setLineStyle(const std::string& pLineStyle);

	/*!设置地形管理对象*/
	void setTerrainTileManager(KL3DTerrainTileManager* terrainTileManager);
private:
	/*!拐点序列*/
	osg::ref_ptr<osg::Vec3Array> m_pointArray;

	/*!点的个数*/
	int m_nPointCount;

	/*!线宽*/
	float m_lineWidth;

	/*!线样式*/
	GLushort m_lineStyle;

	/*!地形管理器(线图元需要插值)*/
	KL3DTerrainTileManager* m_terrainTileManager;
};
#endif