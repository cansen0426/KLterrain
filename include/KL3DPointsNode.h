#ifndef __KL3DPOINTSHODE_H__
#define __KL3DPOINTSHODE_H__

#include <osg/Switch>

#include "KL3DPointGeode.h"
#include "KL3DTextureManager.h"

/*!*********************************************
<br>��˵������ά�۲�ϵͳ�ڼ����ʾ�ڵ�ĸ��ڵ�
***********************************************/
/*!�������Ҷ�ڵ�ļ���*/
#define KL3DPointGeodeSet std::map<double, KL3DPointGeode*>

class KL3DPointsNode : public osg::Switch
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DPointsNode();

	/*!��ʼ������*/
	virtual void init();

	/*!���ƺ���*/
	virtual void reDraw();

	/*!��������*/
	void setType(KL3DLineType type);

	/*!�õ�����*/
	KL3DLineType getType() const;

	/*!�õ���ļ���*/
	KL3DPointGeodeSet* getPointGeodes();

	/*!����ID�õ��㼯���еĻ��ƽڵ�*/
	KL3DPointGeode* getPointGeode(double id);

	/*!����ʾ�б��в����ڼ����ƽڵ�*/
	bool insertPointGeode(KL3DPointGeode* pPointGeode);

	/*!����IDɾ���ڼ����ƽڵ�*/
	bool deletePointGeode(const double& id);

	/*!���õ��νڵ�*/
	void setTerrainNode(osg::Node* pTerrainNode);

	/*!���õ�������ϵ��*/
	void setTerrainScale(osg::MatrixTransform* mt);

	/*!���õ�������ϵ��*/
	void setTerrainScale(const float& pScale);

	/*!���õ�������ϵ��*/
	float getTerrainScale();

	/*!�õ����νڵ�*/
	osg::Node* getTerrainNode();

	/*!��������������*/
	void setTextureManager(KL3DTextureManager* pTextureManager);

	/*!��Ӹ߳����������*/
	void notifyAddTextureManager(KL3DTextureManager* pTextureManager);

	/*!�õ�Vertex����ֵ*/
	GLuint getVertexIndex() const;

	/*!�õ�color����ֵ*/
	GLuint getColorIndex() const;

	/*!�õ�flag����ֵ*/
	GLuint getFlagIndex() const;

	/*!���ó�ʼ�ڼ����ͼ*/
	void initPointImage(osg::Image* pointImage);

	/*!���õ����ͼ*/
	void setPointImage(osg::Image* pointImage);

	/*!���õ�Ĵ�С*/
	void setPointSize(const float& size);

	/*!�����ڼ���Ƿ�ɵ�����С*/
	void setPointSizeChange(const bool& isChange, const bool& isScroll);

	/*!�õ��ڼ��Ĵ�С*/
	float getPointSize() const;

	/*!������Դ·��*/
	void setSourcePath(const std::string& sourcePath);

	/*!����x����Ļ���*/
	void setXBase(float xBase);

	/*!�õ�x����Ļ���*/
	float getXBase() const;

	/*!����y����Ļ���*/
	void setYBase(float yBase);

	/*!�õ�y����Ļ���*/
	float getYBase() const;

	/*!���õ�ǰ����ʾ״̬*/
	void setIsVisible(bool isVisible);

	/*!�õ���ǰ����ʾ״̬*/
	bool getIsVisible();

	/*!���ñ�ע�Ƿ�ɼ�*/
	void setLabelIsVisible(bool isVisible);

	/*!���ñ�ע���*/
	void setLabelInterval(const unsigned int& interval);

protected:
	/*!��������*/
	virtual ~KL3DPointsNode();

private:
	/*!����*/
	KL3DLineType m_type;

	/*!��Ӧ��״̬��*/
	osg::ref_ptr<osg::StateSet> m_stateSet;

	/*!�ڼ���Ӧ�Ļ���Ҷ�ڵ�ļ���*/
	KL3DPointGeodeSet m_pointGeodes;

	/*!���νڵ�*/
	osg::Node* m_terrainNode;

	/*!��������ϵ��*/
	float m_terrainScale;

	/*!����۲����*/
	KL3DTextureManager* m_textureManager;

	/*!������������*/
	GLuint m_vertexIndex;

	/*!������ɫ��������*/
	GLuint m_colorIndex;

	/*!�����Ƿ���ʾ����ı�ʶ����*/
	GLuint m_flagIndex;

	/*!�߳���������*/
	int m_demTextureIndex;

	/*!�ڼ����������*/
	int m_pointTextureIndex;

	/*!���С*/
	float m_pointSize;

	/*!��Ĵ�С�Ƿ�ɸı�*/
	bool m_isPointSizeChange;

	/*!�Ƿ�Ϊ�����ֲ���*/
	bool m_isScroll;

	/*!��Դ·��*/
	std::string m_sourcePath;

	/*!x,y������������*/
	float m_xBase, m_YBase;

	/*!�ڼ����ͼ*/
	osg::Image* m_pointImage;



};


#endif