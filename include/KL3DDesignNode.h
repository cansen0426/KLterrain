#ifndef __KL3DDESIGNNODE_H__
#define __KL3DDESIGNNODE_H__

#include <osg/MatrixTransform>
//#include<boost//function.hpp>

#include "KL3DPointsNode.h"
#include "KL3DLinesNode.h"
#include "KL3DMapCache.h"
#include "KL3DTextureManager.h"

/*!****************************************************
<br>��˵������ά�۲�ϵͳ��ʾ�ڵ�
******************************************************/
/*!����ɫ���ɫ�꺯��ָ��*/
//typedef boost::function<osg::Vec4(const double& lineID, const float& pointID, const short& sameStakeID, bool isShotLine)> multiAttributeColorFunc;

class KL3DDesignNode : public osg::Group
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DDesignNode(KL3DMapCache* pCache, KL3DTextureManager* pTextureManager);

	/*!��ʼ������*/
	virtual void init();

	/*!�ػ溯��*/
	virtual void reDraw();

	/*!����ID*/
	void setID(const std::string& id);

	/*!�õ�ID*/
	std::string getID();

	/*!���õ��νڵ�*/
	void setTerrainNode(osg::Node* pTerrainNode);

	/*!�õ����νڵ�*/
	osg::Node* getTerrainNode();

	/*!���õ�������ϵ��*/
	void setTerrainScale(osg::MatrixTransform* mt);

	/*!���ù۲�ϵͳ�ڵ��Ƿ���ʾ*/
	void setIsVisible(bool isVisible);

	/*!�õ��۲�ϵͳ�ڵ��Ƿ���ʾ*/
	bool getIsVisble();

	/*!�����ڼ��׮���Ƿ���ʾ*/
	void setLabelIsVisible(bool isVisible, KL3DLineType type);

	/*!���ñ�ע��ʾ���*/
	void setLabelInterval(const unsigned int& interval, KL3DLineType type);

	/*!�����ڼ����ߺ��Ƿ���ʾ*/
	void setLinesLabelIsVisible(bool isVisible, KL3DLineType type);

	/*!���ó�ʼ�ڼ����ͼ*/
	void initPointImage(osg::Image* shotPointImage, osg::Image* rcvPointImage);

	/*!�����ڼ����ͼ*/
	void setPointImage(osg::Image* image, KL3DLineType type);

	/*!�����ڼ���С*/
	void setPointSize(const float& pointsize, KL3DLineType type);

	/*!�����ڼ���Ƿ�ɵ�����С*/
	void setPointSizeChange(const bool& isChange, const bool& isScroll);

	/*!ɾ����ʾ�ڵ�*/
	bool deleteGeode(KL3DLineType type, const double& id);

	/*!�õ��ڼ����ʾ�ڵ�*/
	KL3DPointsNode* getPointsNode(KL3DLineType type);

	/*!�õ��ڼ�����ʾ�ڵ�*/
	KL3DLinesNode* getLinesNode(KL3DLineType type);

	/*!��������������*/
	void setTextureManager(KL3DTextureManager* pTextureManager);

	/*!��Ӹ߳����������*/
	void notifyAddTextureManager(KL3DTextureManager* pTextureManager);

	/*!����Z����ƫ����*/
	void setDepature(const double& depature);

	/*!�õ�Z����ƫ����*/
	double getDepature() const;

	/*!������Դ·��*/
	void setSourcePath(const std::string& sourcePath);

	/*!���ú���ָ��*/
	//void setColorFunc(multiAttributeColorFunc pfn);

	/*!�õ�����ָ��*/
	//multiAttributeColorFunc getColorFunc();

	/*!�����ڵ��������ʾ*/
	void setShotPointsMultiAttribute(bool isMultiAttribute);

	/*!���ü첨���������ʾ*/
	void setRcvPointsMultiAttribute(bool isMultiAttribute);

	/*!�õ��ڵ��������ʾ*/
	bool getShotPointsMultiAttribute() const;

	/*!�õ��첨���������ʾ*/
	bool getRcvPointsMultiAttribute() const;

protected:
	/*!��������*/
	virtual ~KL3DDesignNode();

	/*!�����ڼ����ʾ�ڵ�*/
	KL3DPointsNode* creatPointsNode(KL3DLineType type);

	/*!�����ڼ�����ʾ�ڵ�*/
	KL3DLinesNode* createLinesNode(KL3DLineType type);

private:
	/*!��ά�۲�ϵͳ��ʾ�ڵ��Ψһ��ʶ�����Ӧ�����ݹ�����KL3DMapCache*/
	std::string m_id;

	/*!�ڵ���ʾ�ڵ�*/
	osg::ref_ptr<KL3DPointsNode> m_shotPointsNode;

	/*!�첨����ʾ�ڵ�*/
	osg::ref_ptr<KL3DPointsNode> m_rcvPointsNode;

	/*!������ʾ�ڵ�*/
	osg::ref_ptr<KL3DLinesNode> m_shotLinesNode;

	/*!�첨����ʾ�ڵ�*/
	osg::ref_ptr<KL3DLinesNode> m_rcvLinesNode;

	/*!�ڼ�㡢�ڼ��߽ڵ��Ƿ񱻴���*/
	bool m_isPointsNodeCreated, m_isLinesNodeCreated;

	/*!��ʾ�ڵ��Ӧ�ĵ��νڵ�*/
	osg::Node* m_terrainNode;

	/*!�Ƿ��ڵ��νڵ�����ʾ*/
	bool m_isExistTerrain;

	/*!����۲����*/
	KL3DTextureManager* m_textureManager;

	/*!��ʾ�ڵ��Ӧ�����ݹ�������*/
	KL3DMapCache* m_cache;

	/*!��Դ·��*/
	std::string m_sourcePath;

	/*!����x�������*/
	float m_xBase;

	/*!����y�������*/
	float m_yBase;

	/*!����Z�����ƫ����:���ھ������*/
	double m_depature;

	/*!����ɫ��ĺ���ָ��*/
	//multiAttributeColorFunc m_pfn;

	/*!�����ڵ��Ƿ��������ʾ*/
	bool m_isShotPointsMultiAttribute;

	/*!���ü첨���Ƿ��������ʾ*/
	bool m_isRcvPointsMultiAttribute;

	/*!��������ϵ������*/
	osg::MatrixTransform* m_terrainScaleTransform;

	/*!�ڵ���ͼ*/
	osg::Image* m_shotPointImage;

	/*!�첨����ͼ*/
	osg::Image* m_rcvPointImage;

};
#endif