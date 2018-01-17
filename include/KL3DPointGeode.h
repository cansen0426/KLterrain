#ifndef __KL3DPOINTGEODE_H__
#define __KL3DPOINTGEODE_H__

#include <osg/Geode>
#include <osg/Geometry>

#include "KL3DCommonStruct.h"
#include "KL3DLine.h"

/*!************************************************************
<br>��˵������ά�۲�ϵͳ�У�һ���������е���ɵ�osgҶ�ڵ�
**************************************************************/

class KL3DPointGeode: public osg::Geode
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DPointGeode();

	/*!Ĭ�ϳ�ʼ������*/
	virtual void init();

	/*!���»���������*/
	virtual void reBindingArray();

	/*!�ػ溯��*/
	virtual void reDraw();

	/*!����ID:Ψһ��ʶ*/
	void setID(const double& id);

	/*!�õ�ID*/
	double getID() const;

	/*!��������*/
	void setType(KL3DLineType type);

	/*!�õ�����*/
	virtual KL3DLineType getType() const;

	/*!������ʾ�ڵ��Ӧ������*/
	void setLineData(KL3DLine* p3DLine);

	/*!���ö�������*/
	void setVertexArray(osg::Vec3Array* pVertexArray);

	/*!�õ���������*/
	osg::Vec3Array* getVertexArray();

	/*!������ɫ����*/
	void setColorArray(osg::Vec3Array* pColorArray);

	/*!�õ���ɫ����*/
	osg::Vec3Array* getColorArray();

	/*!���ñ�ʶ����*/
	void setFlagArray(osg::FloatArray* pFlagArray);

	/*!���õ�Ĵ�С*/
	void setSize(const float& size);

	/*!�õ���Ĵ�С*/
	float getSize() const;

	/*!���ö�����������*/
	void setVertexIndex(const GLuint& index);

	/*!�õ�������������*/
	GLuint getVertexIndex() const;

	/*!������ɫ��������*/
	void setColorIndex(const GLuint& index);

	/*!�õ���ɫ��������*/
	GLuint getColorIndex() const;

	/*!���ñ�ʶ����*/
	void setFlagIndex(const GLuint& index);

	/*!�õ���ʶ����*/
	GLuint getFlagIndex() const;

	/*!�����Ƿ���ʾ�ڼ���ע*/
	void setLabelIsVisible(bool isVisible);

	/*!���ñ�ע���*/
	void setLabelInterval(const unsigned int& interval);

protected:
	/*!Ĭ����������*/
	virtual ~KL3DPointGeode();

private:
	/*!ID:Ҷ�ڵ��Ψһ��ʶ*/
	double m_id;

	/*!���ƽڵ�����*/
	KL3DLineType m_type;

	/*!�ýڵ��״̬��*/
	osg::ref_ptr<osg::StateSet> m_stateSet;

	/*!��Ӧ�Ļ��ƽڵ�Geometry*/
	osg::ref_ptr<osg::Geometry> m_geometry;

	/*!��������*/
	osg::Vec3Array* m_vertexArray;

	/*!��ɫ����*/
	osg::Vec3Array* m_colorArray;

	/*!��ʾ����*/
	osg::FloatArray* m_flagArray;

	/*!���ƽڵ�Ĵ�С*/
	float m_size;

	/*������������*/
	GLuint m_vertexIndex;

	/*!��ɫ��������*/
	GLuint m_colorIndex;

	/*!��ʶ��������*/
	GLuint m_flagIndex;

	/*!�ڼ���ע��ʾ�ڵ�*/
	osg::ref_ptr<osg::Group> m_labelRoot;

	/*!��ǰ��ע�ļ��*/
	unsigned int m_currentLabelInterval;

	/*!��ά������*/
	KL3DLine* m_line;

	/*!��ע�Ƿ���ʾ��Ĭ�Ϸ�*/
	bool m_isLabelVisible;

public:
	/*!x��������ƫ����*/
	float m_xCoordBase;

	/*!y��������ƫ����*/
	float m_yCoordBase;

};

#endif