#ifndef __KL3DLINEGEODE_H__
#define __KL3DLINEGEODE_H__

#include <osg/Geode>
#include <osg/Geometry>

#include "KL3DCommonStruct.h"

/*!****************************************************
<br>��˵�����ڼ��߻��Ƶ�Ҷ�ڵ�
*******************************************************/
class KL3DLineGeode : public osg::Geode
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DLineGeode();

	/*!��������*/
	~KL3DLineGeode();

	/*!��ʼ������*/
	virtual void init();

	/*!�ػ溯��*/
	virtual void reDraw();

	/*!��������ʾ�ڵ��ID*/
	virtual void setID(const double& id);

	/*!�õ�����ʾ�ڵ��ID*/
	virtual double getID() const;

	/*!��������ʾ�ڵ������*/
	virtual void setType(KL3DLineType type);

	/*!�õ�����ʾ�ڵ������*/
	virtual KL3DLineType getType() const;

	/*!������ʾ״̬*/
	virtual void setIsDisplay(bool isDisplay);

	/*!�õ���ʾ״̬*/
	virtual bool getIsDisplay() const;

	/*!�����Ƿ���ʾ�ڼ��߱�ע*/
	void setLineLabelIsVisible(bool isVisible);

	/*!���ö�������*/
	virtual void setVertexArray(osg::Vec3Array* pVertexArray);

	/*!�õ���������*/
	virtual osg::Vec3Array* getVertexArray();

	/*!�����ߵ���ɫ*/
	virtual void setColor(const osg::Vec4& color);

	/*!�õ��ߵ���ɫ*/
	virtual osg::Vec4 getColor() const;

	/*!������ɫ����*/
	virtual void setColorArray(osg::Vec3Array* pColorArray);

	/*!�õ���ɫ����*/
	virtual osg::Vec3Array* getColorArray();

	/*!���ö�����������*/
	virtual void setVertexIndex(const GLuint& vertexIndex);

	/*!���ö�����ɫ������*/
	virtual void setColorIndex(const GLuint& colorIndex);

	/*!����x�����������*/
	virtual void setXCoordBase(const float& xCoordBase);

	/*!����y�����������*/
	virtual void setYCoordBase(const float& yCoordBase);

	/*!���°󶨶�������*/
	void reBindingArray();

	/*!ɾ���ߺű�ע*/
	void deleteLineLabel();

private:
	/*!Ҷ�ڵ�Ψһ��ʶ*/
	double m_id;

	/*!����Ҷ�ڵ������*/
	KL3DLineType m_type;

	/*!��Ҷ�ڵ��״̬��*/
	osg::ref_ptr<osg::StateSet> m_stateSet;

	/*!��ʶ�����ƽڵ��Ƿ���ʾ*/
	bool m_isDisplay;

	/*!Ҷ�ڵ�Ļ��Ƽ��νڵ�*/
	osg::ref_ptr<osg::Geometry> m_geometry;

	/*!��������*/
	osg::Vec3Array* m_vertexArray;

	/*!�ߵ���ɫ*/
	osg::Vec4 m_color;

	/*!��ɫ����*/
	osg::ref_ptr<osg::Vec3Array> m_colorArray;

	/*!�߿�*/
	float m_size;

	/*!������������*/
	GLuint m_vertexIndex;

	/*!��ɫ��������*/
	GLuint m_colorIndex;

	/*!x���귽�����*/
	float m_xCoordBase;

	/*!y���귽�����*/
	float m_yCoordBase;

	/*!�ڼ��߱����ʾ�ڵ�*/
	osg::ref_ptr<osg::Group> m_lineLabelRoot;

	/*!�ڼ��߱���Ƿ���ʾ*/
	bool m_isLineLabelVisible;
};
#endif