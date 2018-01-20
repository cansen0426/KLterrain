#ifndef __KL3DMAPMANAGER_H__
#define __KL3DMAPMANAGER_H__

#include <osgViewer/Viewer>

#include "KL3DTextureManager.h"
#include "KL3DTerrainTileManager.h"
#include "KL3DMapCache.h"
#include "KL3DDesignNode.h"

/*!********************************************************
<br> ��˵���������ڶ෽��������
***********************************************************/

#define		KL3DMapCacheSet		std::map<std::string, KL3DMapCache*>
#define		KL3DDesignNodeSet	std::map<std::string, osg::ref_ptr<KL3DDesignNode>>
#define		KL3DTextureManagerSet	std::map<osg::Node*, osg::ref_ptr<KL3DTextureManager>>
#define		KL3DTerrainSet          std::vector<osg::Node*>

class KL3DMapManager
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DMapManager(osgViewer::Viewer* pID, osg::Group* pRoot);

	/*!��������*/
	~KL3DMapManager();

	/*!�õ�ID*/
	osgViewer::Viewer* getID();

	/*!������Դ·��*/
	void setSourcePath(const std::string& sourcePath);

	/*!��������������*/
	void resetMainDesign();

	/*!�ж��Ƿ���ڹ۲�ϵͳ����*/
	bool isCacheExist(const std::string& fileName);

	/*!��෽�������������һ��cache,��������֮��صĵ��νڵ�*/
	void insertCache(KL3DMapCache* pCache, osg::Node* pTerrain = NULL);

	/*!ɾ��ĳ����*/
	void deleteCache(const std::string& fileName);

	/*!��ȡKL3DMaoCache����*/
	KL3DMapCache* getCache(const std::string& path);

	/*!���ù۲�ϵͳ�����Ƿ�ɼ�*/
	void set3DDesignVisible(bool isVisible);

	/*!�����ڼ���Ƿ�ɼ�*/
	void set3DPointsVisible(bool isVisible, KL3DLineType type);

	/*!�����ڼ����Ƿ�ɼ�*/
	void set3DLinesVisible(bool isVisible, KL3DLineType type);

	/*!�õ��ڼ����Ƿ�ɼ�*/
	bool get3DLinesVisible(KL3DLineType type);

	/*!�����ڼ�����ɫ*/
	void set3DLinesColor(const osg::Vec4& color, KL3DLineType type);

	/*!�����ڼ����߿�*/
	void set3DLineSize(const float& size, KL3DLineType type);

	/*!�õ���ǰ�������������*/
	KL3DTextureManager* getMainTextureManager();

	/*!�õ���ǰ��������Ӧ����ʾ�ڵ�*/
	KL3DDesignNode* getMainDesignNode();

	/*!�õ���ǰ��������Ӧ��Cache*/
	KL3DMapCache* getMainCache();

	/*!���ݱ�ʶ��ȡKL3DDesignNode����*/
	KL3DDesignNode* getDesignNode(const std::string& designNdoePath);

	/*!���õ���*/
	void setTerrainNode(osg::Node* pTerrainNode);

	/*!���õ�������ϵ��*/
	void setTerrainScale(osg::MatrixTransform* mt);

	/*!�õ���������ϵ��*/
	osg::Matrix getScaleMatrix() const;

	/*!�õ����������Zֵ*/
	float getTerrainScaleZ();

	/*!�õ����������Xֵ*/
	float getTerrainScaleX();

	/*!�õ����������Yֵ*/
	float getTerrainScaleY();

	/*!����CPU˫���Բ�ֵ�ķ������¸��·����������ڼ������꣨Zֵ��*/
	void updatePointsDemByCPU(bool isUpdate, const double depature = 0);

	/*!�Ƿ���ڵ���*/
	bool isTerrainExist();

	/*!��KL3DMapManager����ӵ�������*/
	void addTerrainTexture(osg::Node* pTerrainNode);

	/*!����viewer���㵱ǰ�������ڼ��Ĵ�С*/
	float computePointSize();

	/*!���ݹ������������ڼ��Ĵ�С*/
	void resetPointSize();

	/*!���ó�ʼ�ڼ����ͼ*/
	void initPointImage(osg::Image* shotPointImage, osg::Image* rcvPointImage);

	/*!�����ڼ��������ģ*/
	void setMainDesignPointsNum(long& pPointNum);

	/*!�۲�ϵͳ��ϡ����*/
	void designPointsRarefying();

	/*!���õ���Zֵ����ϵ��*/
	void setTerrainScaleZ(float& pTerrainScaleZ);

	/*!�����λ*/
	void gridHoming();
	/*!�����λ*/
	void ProjectToGrid_3D(double &x,double &y,
		double &hInterval,double &halfHInterval,
		double &vInterval,double &halfVInterval,
		double &x0,double &y0,
		double &sinValue,double &cosValue);
	/*!ƫ�ƺ���*/
	void SDRound_3D(double &value,double &gridLength,double &halfGridLength);

	//*********�ڼ��༭״̬���ƺ���*********//
	/*!��ȡ��ǰ�༭����*/
	KL3DEditObject getEditObject();

	/*!��ȡ�༭״̬*/
	bool getEditState();

	/*!���ñ༭�ڵ�*/
	virtual void editShotPoint();

	/*!���ñ༭����*/
	virtual void editShotLine();

	/*!���ñ༭�첨��*/
	virtual void editRcvPoint();

	/*!���ñ༭�첨��*/
	virtual void editRcvLine();

	/*!ȡ���༭�ڵ�*/
	virtual void cancelEditShotPoint();

	/*!ȡ���༭����*/
	virtual void cancelEditShotLine();

	/*!ȡ���༭�첨��*/
	virtual void cancelEditRcvPoint();

	/*!ȡ���༭�첨��*/
	virtual void cancelEditRcvLine();

	/*!�ڵ�ı༭״̬*/
	virtual bool isShotPointEdit() const;

	/*!���ߵı༭״̬*/
	virtual bool isShotLineEdit() const;

	/*!�첨��ı༭״̬*/
	virtual bool isRcvPointEdit() const;

	/*!�첨�ߵı༭״̬*/
	virtual bool isRcvLineEdit() const;


private:
	/*!ID:KL3DMapManager��Ψһ��ʶ*/
	osgViewer::Viewer* m_id;

	/*!OSG�������ڵ㣺���ڹ۲�ϵͳ��ʾ�ĸ��ڵ�*/
	osg::Group* m_root;

	/*!����KL3DMapCache�Ķ���*/
	KL3DMapCacheSet m_caches;

	/*!����KL3DDesignNode�Ķ���*/
	KL3DDesignNodeSet m_surveyNodes;

	/*!����KL3DTextureManager�Ķ���*/
	KL3DTextureManagerSet m_textureManagers;

	/*!������εļ���*/
	KL3DTerrainSet m_terrains;

	/*!���α任����*/
	osg::MatrixTransform* m_matrixTransform;

	/*!��ǰ�����ȵ�������*/
	KL3DMapCache* m_mainCache;

	/*!��ǰ��������������Ӧ����ʾ�ڵ�*/
	KL3DDesignNode* m_mainSurveyNode;

	/*!��ǰ���������������ڵĵ���*/
	osg::Node* m_mainTerrain;

	/*!��ǰ��������������Ӧ�ĵ������������*/
	KL3DTextureManager* m_mainTextureManager;

	/*!��Ҫ����������*/
	bool m_isNeedSetMainCache;

	/*!������Դ·��*/
	std::string m_sourcePath;

	/*!�Ƿ���ڵ���*/
	bool m_isTerrainExist;

	/*!�ڼ���С*/
	float m_pointSize;

	/*!�ڵ���ͼ*/
	osg::Image* m_shotPointImage;

	/*!�����ͼ*/
	osg::Image* m_rcvPointImage;

	/*!�������ڼ������*/
	long m_mainDesingPointsNum;

	/*!�������������ŵõ���һ�����Ų���*/
	unsigned int m_scrollNum;

	/*!����Zֵ����ϵ��*/
	float m_terrainScaleZ;

	//***********�ڼ��༭������Ӧ�����״̬��***********//
	/*!��ʶ���ڼ��۲�ϵͳ�Ƿ��ڱ༭״̬*/
	bool m_isEditState;

	/*!��ʶ���ڵ��Ƿ��ڱ༭״̬*/
	bool m_isShotPointEdit;

	/*!��ʶ�������Ƿ��ڱ༭״̬*/
	bool m_isShotLineEdit;

	/*!��ʶ���첨���Ƿ��ڱ༭״̬*/
	bool m_isRcvPointEdit;

	/*!��ʶ�������Ƿ��ڱ༭״̬*/
	bool m_isRcvLineEdit;

};

#endif