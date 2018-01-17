#ifndef __KL3DLINESNODE_H__
#define __KL3DLINESNODE_H__

#include <osgSim/OverlayNode>

#include "KL3DLineGeode.h"
#include "KL3DTextureManager.h"

/*!***********************************************
<br>��˵������ά�۲�ϵͳ�ڼ�����ʾ�����ڵ�
**************************************************/
#define  KL3DLineGeodeSet std::map<double, KL3DLineGeode*>

class KL3DLinesNode: public osg::Switch
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DLinesNode();

	/*!��ʼ������*/
	virtual void init();

	/*!�ػ溯��*/
	virtual void reDraw();

	/*!��������*/
	virtual void setType(KL3DLineType type);

	/*!�õ�����*/
	virtual KL3DLineType getType() const;

	/*!ɾ���ڼ��߻��ƽڵ�*/
	bool deleteLineGeode(const double& id);

	/*!������ʾ״̬*/
	virtual void setIsDisplay(bool isDisplay);

	/*!�õ���ʾ״̬*/
	virtual bool getIsDisplay() const;

	/*!�����ڼ��߱�ע�Ƿ�ɼ�*/
	void setLinesLabelIsVisible(bool isVisible);

	/*!�õ��ڼ��߱�ע�Ƿ�ɼ�*/
	bool getLinesLabelIsVisible() const;

	/*!�����ߵĴ�С*/
	virtual void setLineSize(const float& size);

	/*!�õ��ߵĿ�ȣ���С��*/
	virtual float getLineSize() const;

	/*!�����ߵ���ɫ*/
	virtual void setLineColor(const osg::Vec4& color);

	/*!�õ��ߵ���ɫ*/
	virtual osg::Vec4 getLineColor() const;

	/*!�õ��ڼ��߻��ƽڵ�ļ���*/
	virtual KL3DLineGeodeSet* getLinesGeodes();

	/*!�õ�ָ�����ڼ��߻��ƽڵ�*/
	virtual KL3DLineGeode* getLineGeode(double id);

	/*!����ʾ�����в����ڼ�����ʾ�ڵ�*/
	virtual bool insertLineGeode(KL3DLineGeode* pLineGeode);

	/*!���õ��νڵ�*/
	virtual void setTerrainNode(osg::Node* pTerrainNode);

	/*!�õ����νڵ�*/
	virtual osg::Node* getTerrainNode();

	/*!��������������*/
	void setTextureManager(KL3DTextureManager* pTextureManager);

	/*!��Ӹ߳����������*/
	void notifyAddTextureManager(KL3DTextureManager* pTextureManager);

	/*!�õ�vertex����ֵ*/
	GLuint getVertexIndex() const;

	/*!�õ�color����ֵ*/
	GLuint getColorIndex() const;

	/*!������Դ·��*/
	virtual void setSourcePath(const std::string& sourcePath);

	/*!����x����Ļ���*/
	virtual void setXBase(const float& xBase);

	/*!�õ�x����Ļ���*/
	virtual float getXBase() const;

	/*!����y����Ļ���*/
	virtual void setYBase(const float& yBase);

	/*!�õ�y����Ļ���*/
	virtual float getYBase() const;

	/*!���õ�������ϵ��*/
	void setTerrainScale(osg::MatrixTransform* mt);

	/*!���õ�������ϵ��*/
	void setTerrainScale(const float& pScale);

protected:
	/*!��������*/
	virtual ~KL3DLinesNode();

private:
	/*!����*/
	KL3DLineType m_type;

	/*!��Ӧ��״̬��*/
	osg::ref_ptr<osg::StateSet> m_stateSet;

	/*!�ڼ��߻��ƽڵ�ļ���*/
	KL3DLineGeodeSet m_lineGeodes;

	/*!��ʶ�����ƽڵ��Ƿ���ʾ*/
	bool m_isDisplay;

	/*!�ڼ��ߵı�ע�Ƿ���ʾ*/
	bool m_isDisplayLineLabel;

	/*!�߿�*/
	float m_lineSize;

	/*!�ߵ���ɫ*/
	osg::Vec4 m_color;

	/*!���νڵ�*/
	osg::Node* m_terrainNode;

	/*!����������*/
	KL3DTextureManager* m_textureManager;

	/*!������������*/
	GLuint m_vertexIndex;

	/*!��ɫ��������*/
	GLuint m_colorIndex;

	/*!�߳���������*/
	int m_demTextureIndex;

	/*!��Դ·��*/
	std::string m_sourcePatch;

	/*!x��y������������*/
	float m_xBase, m_yBase;

	/*!��������ϵ��*/
	float m_terrainScale;
};

#endif