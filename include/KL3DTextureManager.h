#ifndef __KL3DTEXTUREMANAGER_H__
#define __KL3DTEXTUREMANAGER_H__

#include <osg/Camera>
#include <osg/Texture2D>
#include <osgTerrain/TerrainTile>

#define TEXTURESIZE 2048

/*!**********************************************************
<br>类说明：地形纹理管理类，纹理对象保存地形的高程
*************************************************************/

class KL3DTextureManager: public osg::Camera
{
public:
	/*!默认构造函数*/
	KL3DTextureManager(osg::Node*pTerrainNode);

	/*!初始化函数*/
	virtual void init();

	/*!设置ID*/
	void setID(osg::Node* id);

	/*!得到ID*/
	osg::Node* getID();

	/*!得到地形节点*/
	osg::Node* getTerrainNode();

	/*!得到地形节点包围盒*/
	osg::BoundingBox getTerrainBoundingBox() const;

	/*!得到或者创建高程纹理*/
	osg::ref_ptr<osg::Texture2D> getOrCreateDemTexture();

	/*!设置资源路径*/
	void setSourcePath(const std::string& sourcePath);

protected:
	/*!析构函数*/
	virtual ~KL3DTextureManager();

private:
	/*!标识，纹理管理器对象，对应每一个观测系统*/
	osg::Node* m_id;

	/*!状态集对象*/
	osg::StateSet* m_stateSet;

	/*!二维纹理对象*/
	osg::ref_ptr<osg::Texture2D> m_demTexture;

	/*!地形节点*/
	osg::Node* m_terrainNode;

	/*!地形包围盒大小*/
	osg::BoundingBox m_terrainBounding;

	/*!资源路径*/
	std::string m_sourcePath;

};

/*!*************************************************
<br>类说明：添加一个更新回调，使得三维观测系统场景出现后一段时间，rtt相机不再做渲染，从而避免影响渲染效率
****************************************************/
//计数临界值
#define  RTTCOUNT 10
class KL3DRttCallback: public osg::NodeCallback
{
public:
	/*!默认构造函数*/
	KL3DRttCallback(osg::Node* pRttCamera);

	/*!重写()操作*/
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

protected:
	/*!默认析构函数*/
	virtual ~KL3DRttCallback();

private:
	/*!计数器*/
	unsigned int m_count;

	/*!渲染到纹理节点*/
	osg::Node* m_rttCamera;
};

#endif