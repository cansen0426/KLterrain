#ifndef __KL3DTERRAINTILEMANAGER_H__
#define __KL3DTERRAINTILEMANAGER_H__

#include <osgTerrain/TerrainTile>
#include "KL3DGeospatialExtents.h"

#define PARALLELNUM 10

class KL3DGeospatialExtents;

/*!*****************************************************
<br>��˵������ά�۲�ϵͳ�ڴ��ֵ�࣬�����ض�ʱ��ͨ���ڴ�˫�̲߳�ֵ�㷨��ȡ�ڼ���Ӧ�ĵ��θ߳�
*******************************************************/
class KL3DTerrainTileManager
{
public:
	/*!Ĭ�Ϲ��캯����������νڵ�*/
	KL3DTerrainTileManager(osg::Node* rootNode);

	/*!�������m_TileMap,Ȼ�����ýڵ�����࣬������OSG����������Ч��TerrainTile�ڵ�*/
	virtual void gatherCurrentOSGScenceTerrainTile();

	/*!�õ�zֵ������x,yֵ�ڵ�ǰ��ͼ�ϣ�ͨ����ֵ�õ���Ӧ�ĸ߳�ֵ*/
	virtual void getValue(float x, float y, float& z);

		/*!�õ�zֵ������x,yֵ�ڵ�ǰ��ͼ�ϣ�ͨ����ֵ�õ���Ӧ�ĸ߳�ֵ*/
	virtual void getValue(float x, float y, osg::Vec3f& value);

	/*!����vector�е�vec3f��x��y�õ�z*/
	virtual void getValue(std::vector<osg::Vec3f>& vecs);

	/*!����vector�е�vec3f��x,y�õ�z*/
	virtual void getValue(osg::Vec3Array* vecs, int size);

	/*!����ָ���Ķ���ֵ���������Χ�ĸ��������ֵ*/
	virtual void printSroundVec(std::vector<osg::Vec3f>& vecs);

	/*!
	\brief ���ݸ߳���x��y���꣨ʵ������ֵ�����õ��߳�ֵ
	\return float ��ֵ���
	\param hf �̶߳���
	\param x,y��ά����
	*/
	float getInterpolatedValue(osg::HeightField* hf, double x, double y);

	/*!��ȡ��ƬID*/
	std::vector<osgTerrain::TileID> getTileIDs(){return m_tileIDVect;}

	/*!�õ���Ƭ����*/
	std::map<osgTerrain::TileID,osgTerrain::TerrainTile*> getTileID2TerrainMap()
	{
		return m_tileMap;
	}

	/*!����x�����ƫ����*/
	void setXOffset(const float& xOffset);

	/*!����y�����ƫ����*/
	void setYOffset(const float& yOffset);

	/*!�õ�x�����ƫ����*/
	float getXOffset() const;

	/*!�õ�y�����ƫ����*/
	float getYOffset() const;

	/*!���η�����*/
	friend class KL3DTerrainTileVisitor;

protected:
	
	/*!���������Ƭ����*/
	std::map<osgTerrain::TileID, osgTerrain::TerrainTile*> m_tileMap;

	/*!���������Ƭextents����*/
	std::vector<KL3DGeospatialExtents> m_extentsVect;
	std::vector<osgTerrain::TileID> m_tileIDVect;

	/*!���嵱ǰ������Ƭ��Ϊ������ٶȣ����滺���TileIDλ��*/
	int m_curPos;

	/*!���浱ǰ�����еĸ��ڵ�*/
	osg::Node* m_root;

	/*!������*/
	int m_paralNum;

	/*!x����ƫ����*/
	float m_xOffset;

	/*!y����ƫ����*/
	float m_yOffset;


};


/*!*************************************************
<br> ��˵����������ǰOSG�������У���Ч��TerrainTile
****************************************************/
class KL3DTerrainTileVisitor: public osg::NodeVisitor
{
public:
	KL3DTerrainTileVisitor(KL3DTerrainTileManager* map):osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ACTIVE_CHILDREN)
	{
		m_terrainTileMap = map;
	}

	//��дapply����
	virtual void apply(osg::Node& node)
	{
		osgTerrain::TerrainTile* result = dynamic_cast<osgTerrain::TerrainTile*>(&node);
		if(result)
		{
			apply(*result);
		}

		traverse(node);
	}

	//��дapply������node �������OSG������Ƭ�ڵ�
	virtual void apply(osgTerrain::TerrainTile& node)
	{
		//������ǰ�����ĸ��ڵ㣬Ȼ������Ӧ�����ݻ���
		m_terrainTileMap->m_tileMap.insert(std::pair<osgTerrain::TileID, osgTerrain::TerrainTile*>(node.getTileID(),&node));

		osgTerrain::HeightFieldLayer* heightLayer = dynamic_cast<osgTerrain::HeightFieldLayer*>(node.getElevationLayer());
		if(heightLayer)
		{
			//������Χ
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
	//������Ƭ����
	KL3DTerrainTileManager* m_terrainTileMap;
};

#endif