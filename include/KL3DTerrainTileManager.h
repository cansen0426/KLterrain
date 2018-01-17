#ifndef __KL3DTERRAINTILEMANAGER_H__
#define __KL3DTERRAINTILEMANAGER_H__

#include <osgTerrain/TerrainTile>
#include "KL3DGeospatialExtents.h"

#define PARALLELNUM 10

class KL3DGeospatialExtents;

/*!*****************************************************
<br>类说明：三维观测系统内存插值类，用于特定时机通过内存双线程插值算法获取炮检点对应的地形高程
*******************************************************/
class KL3DTerrainTileManager
{
public:
	/*!默认构造函数，传入地形节点*/
	KL3DTerrainTileManager(osg::Node* rootNode);

	/*!首先清除m_TileMap,然后利用节点遍历类，来遍历OSG场景树，有效的TerrainTile节点*/
	virtual void gatherCurrentOSGScenceTerrainTile();

	/*!得到z值。根据x,y值在当前视图上，通过插值得到对应的高程值*/
	virtual void getValue(float x, float y, float& z);

		/*!得到z值。根据x,y值在当前视图上，通过插值得到对应的高程值*/
	virtual void getValue(float x, float y, osg::Vec3f& value);

	/*!根据vector中的vec3f的x、y得到z*/
	virtual void getValue(std::vector<osg::Vec3f>& vecs);

	/*!根据vector中的vec3f的x,y得到z*/
	virtual void getValue(osg::Vec3Array* vecs, int size);

	/*!根据指定的顶点值，获得其周围四个顶点的数值*/
	virtual void printSroundVec(std::vector<osg::Vec3f>& vecs);

	/*!
	\brief 根据高程域，x、y坐标（实际坐标值），得到高程值
	\return float 插值结果
	\param hf 高程对象
	\param x,y二维坐标
	*/
	float getInterpolatedValue(osg::HeightField* hf, double x, double y);

	/*!获取瓦片ID*/
	std::vector<osgTerrain::TileID> getTileIDs(){return m_tileIDVect;}

	/*!得到瓦片集合*/
	std::map<osgTerrain::TileID,osgTerrain::TerrainTile*> getTileID2TerrainMap()
	{
		return m_tileMap;
	}

	/*!设置x方向的偏移量*/
	void setXOffset(const float& xOffset);

	/*!设置y方向的偏移量*/
	void setYOffset(const float& yOffset);

	/*!得到x方向的偏移量*/
	float getXOffset() const;

	/*!得到y方向的偏移量*/
	float getYOffset() const;

	/*!地形访问器*/
	friend class KL3DTerrainTileVisitor;

protected:
	
	/*!保存地形瓦片序列*/
	std::map<osgTerrain::TileID, osgTerrain::TerrainTile*> m_tileMap;

	/*!保存地形瓦片extents序列*/
	std::vector<KL3DGeospatialExtents> m_extentsVect;
	std::vector<osgTerrain::TileID> m_tileIDVect;

	/*!缓冲当前操作瓦片，为了提高速度，保存缓冲的TileID位置*/
	int m_curPos;

	/*!保存当前场景中的根节点*/
	osg::Node* m_root;

	/*!并行数*/
	int m_paralNum;

	/*!x方向偏移量*/
	float m_xOffset;

	/*!y方向偏移量*/
	float m_yOffset;


};


/*!*************************************************
<br> 类说明：遍历当前OSG场景树中，有效的TerrainTile
****************************************************/
class KL3DTerrainTileVisitor: public osg::NodeVisitor
{
public:
	KL3DTerrainTileVisitor(KL3DTerrainTileManager* map):osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ACTIVE_CHILDREN)
	{
		m_terrainTileMap = map;
	}

	//重写apply方法
	virtual void apply(osg::Node& node)
	{
		osgTerrain::TerrainTile* result = dynamic_cast<osgTerrain::TerrainTile*>(&node);
		if(result)
		{
			apply(*result);
		}

		traverse(node);
	}

	//重写apply方法，node 待处理的OSG地形瓦片节点
	virtual void apply(osgTerrain::TerrainTile& node)
	{
		//遍历当前场景的根节点，然后构造相应的数据缓存
		m_terrainTileMap->m_tileMap.insert(std::pair<osgTerrain::TileID, osgTerrain::TerrainTile*>(node.getTileID(),&node));

		osgTerrain::HeightFieldLayer* heightLayer = dynamic_cast<osgTerrain::HeightFieldLayer*>(node.getElevationLayer());
		if(heightLayer)
		{
			//构建范围
			osg::HeightField* hf = heightLayer->getHeightField();
			if(hf != NULL)
			{
				float xOffset = m_terrainTileMap->getXOffset();
				float yOffset = m_terrainTileMap->getYOffset();

				KL3DGeospatialExtents extents;
				extents.xMin() = hf->getOrigin().x();
				extents.yMin() = hf->getOrigin().y();
				extents.xMax() = extents.xMin() + (hf->getNumColumns() - 1)* hf->getXInterval();
				extents.yMax() = extents.yMin() + (hf->getNumRows() - 1)* hf->getYInterval();
				m_terrainTileMap->m_extentsVect.push_back(extents);
				m_terrainTileMap->m_tileIDVect.push_back(node.getTileID());

			}
		}
	}

private:
	//地形瓦片序列
	KL3DTerrainTileManager* m_terrainTileMap;
};

#endif