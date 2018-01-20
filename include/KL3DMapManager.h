#ifndef __KL3DMAPMANAGER_H__
#define __KL3DMAPMANAGER_H__

#include <osgViewer/Viewer>

#include "KL3DTextureManager.h"
#include "KL3DTerrainTileManager.h"
#include "KL3DMapCache.h"
#include "KL3DDesignNode.h"

/*!********************************************************
<br> 类说明：单窗口多方案管理类
***********************************************************/

#define		KL3DMapCacheSet		std::map<std::string, KL3DMapCache*>
#define		KL3DDesignNodeSet	std::map<std::string, osg::ref_ptr<KL3DDesignNode>>
#define		KL3DTextureManagerSet	std::map<osg::Node*, osg::ref_ptr<KL3DTextureManager>>
#define		KL3DTerrainSet          std::vector<osg::Node*>

class KL3DMapManager
{
public:
	/*!默认构造函数*/
	KL3DMapManager(osgViewer::Viewer* pID, osg::Group* pRoot);

	/*!析构函数*/
	~KL3DMapManager();

	/*!得到ID*/
	osgViewer::Viewer* getID();

	/*!设置资源路径*/
	void setSourcePath(const std::string& sourcePath);

	/*!重新设置主方案*/
	void resetMainDesign();

	/*!判断是否存在观测系统对象*/
	bool isCacheExist(const std::string& fileName);

	/*!向多方案管理器中添加一个cache,并传入与之相关的地形节点*/
	void insertCache(KL3DMapCache* pCache, osg::Node* pTerrain = NULL);

	/*!删除某方案*/
	void deleteCache(const std::string& fileName);

	/*!获取KL3DMaoCache对象*/
	KL3DMapCache* getCache(const std::string& path);

	/*!设置观测系统方案是否可见*/
	void set3DDesignVisible(bool isVisible);

	/*!设置炮检点是否可见*/
	void set3DPointsVisible(bool isVisible, KL3DLineType type);

	/*!设置炮检线是否可见*/
	void set3DLinesVisible(bool isVisible, KL3DLineType type);

	/*!得到炮检线是否可见*/
	bool get3DLinesVisible(KL3DLineType type);

	/*!设置炮检线颜色*/
	void set3DLinesColor(const osg::Vec4& color, KL3DLineType type);

	/*!设置炮检线线宽*/
	void set3DLineSize(const float& size, KL3DLineType type);

	/*!得到当前纹理管理器对象*/
	KL3DTextureManager* getMainTextureManager();

	/*!得到当前主方案对应的显示节点*/
	KL3DDesignNode* getMainDesignNode();

	/*!得到当前主方案对应的Cache*/
	KL3DMapCache* getMainCache();

	/*!根据标识获取KL3DDesignNode对象*/
	KL3DDesignNode* getDesignNode(const std::string& designNdoePath);

	/*!设置地形*/
	void setTerrainNode(osg::Node* pTerrainNode);

	/*!设置地形拉伸系数*/
	void setTerrainScale(osg::MatrixTransform* mt);

	/*!得到地形拉伸系数*/
	osg::Matrix getScaleMatrix() const;

	/*!得到地形拉伸的Z值*/
	float getTerrainScaleZ();

	/*!得到地形拉伸的X值*/
	float getTerrainScaleX();

	/*!得到地形拉伸的Y值*/
	float getTerrainScaleY();

	/*!利用CPU双线性插值的方法重新更新方案内所用炮检点的坐标（Z值）*/
	void updatePointsDemByCPU(bool isUpdate, const double depature = 0);

	/*!是否存在地形*/
	bool isTerrainExist();

	/*!向KL3DMapManager中添加地形纹理*/
	void addTerrainTexture(osg::Node* pTerrainNode);

	/*!根据viewer计算当前场景下炮检点的大小*/
	float computePointSize();

	/*!根据滚轮缩放重设炮检点的大小*/
	void resetPointSize();

	/*!设置初始炮检点贴图*/
	void initPointImage(osg::Image* shotPointImage, osg::Image* rcvPointImage);

	/*!设置炮检点数量规模*/
	void setMainDesignPointsNum(long& pPointNum);

	/*!观测系统抽稀处理*/
	void designPointsRarefying();

	/*!设置地形Z值拉伸系数*/
	void setTerrainScaleZ(float& pTerrainScaleZ);

	/*!网格归位*/
	void gridHoming();
	/*!坐标归位*/
	void ProjectToGrid_3D(double &x,double &y,
		double &hInterval,double &halfHInterval,
		double &vInterval,double &halfVInterval,
		double &x0,double &y0,
		double &sinValue,double &cosValue);
	/*!偏移函数*/
	void SDRound_3D(double &value,double &gridLength,double &halfGridLength);

	//*********炮检点编辑状态控制函数*********//
	/*!获取当前编辑对象*/
	KL3DEditObject getEditObject();

	/*!获取编辑状态*/
	bool getEditState();

	/*!设置编辑炮点*/
	virtual void editShotPoint();

	/*!设置编辑炮线*/
	virtual void editShotLine();

	/*!设置编辑检波点*/
	virtual void editRcvPoint();

	/*!设置编辑检波线*/
	virtual void editRcvLine();

	/*!取消编辑炮点*/
	virtual void cancelEditShotPoint();

	/*!取消编辑炮线*/
	virtual void cancelEditShotLine();

	/*!取消编辑检波点*/
	virtual void cancelEditRcvPoint();

	/*!取消编辑检波线*/
	virtual void cancelEditRcvLine();

	/*!炮点的编辑状态*/
	virtual bool isShotPointEdit() const;

	/*!炮线的编辑状态*/
	virtual bool isShotLineEdit() const;

	/*!检波点的编辑状态*/
	virtual bool isRcvPointEdit() const;

	/*!检波线的编辑状态*/
	virtual bool isRcvLineEdit() const;


private:
	/*!ID:KL3DMapManager的唯一标识*/
	osgViewer::Viewer* m_id;

	/*!OSG场景根节点：用于观测系统显示的根节点*/
	osg::Group* m_root;

	/*!保存KL3DMapCache的队列*/
	KL3DMapCacheSet m_caches;

	/*!保存KL3DDesignNode的队列*/
	KL3DDesignNodeSet m_surveyNodes;

	/*!保存KL3DTextureManager的队列*/
	KL3DTextureManagerSet m_textureManagers;

	/*!保存地形的集合*/
	KL3DTerrainSet m_terrains;

	/*!地形变换矩阵*/
	osg::MatrixTransform* m_matrixTransform;

	/*!当前窗口先的主方案*/
	KL3DMapCache* m_mainCache;

	/*!当前窗口下主方案对应主显示节点*/
	KL3DDesignNode* m_mainSurveyNode;

	/*!当前窗口下主方案所在的地形*/
	osg::Node* m_mainTerrain;

	/*!当前窗口下主方案对应的地形纹理管理器*/
	KL3DTextureManager* m_mainTextureManager;

	/*!需要设置主方案*/
	bool m_isNeedSetMainCache;

	/*!设置资源路径*/
	std::string m_sourcePath;

	/*!是否存在地形*/
	bool m_isTerrainExist;

	/*!炮检点大小*/
	float m_pointSize;

	/*!炮点贴图*/
	osg::Image* m_shotPointImage;

	/*!检点贴图*/
	osg::Image* m_rcvPointImage;

	/*!主方案炮检点数量*/
	long m_mainDesingPointsNum;

	/*!根据鼠标滚轮缩放得到的一个缩放参数*/
	unsigned int m_scrollNum;

	/*!地形Z值拉伸系数*/
	float m_terrainScaleZ;

	//***********炮检点编辑操作对应的相关状态量***********//
	/*!标识：炮检点观测系统是否处于编辑状态*/
	bool m_isEditState;

	/*!标识：炮点是否处于编辑状态*/
	bool m_isShotPointEdit;

	/*!标识：炮线是否处于编辑状态*/
	bool m_isShotLineEdit;

	/*!标识：检波点是否处于编辑状态*/
	bool m_isRcvPointEdit;

	/*!标识：炮线是否处于编辑状态*/
	bool m_isRcvLineEdit;

};

#endif