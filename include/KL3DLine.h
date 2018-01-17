#ifndef __KL3DLINE_H__
#define __KL3DLINE_H__

#include <osg/Array>

#include "KL3DCommonStruct.h"
#include "KL3DPoint.h"

class KL3DLine;

/*!*******************************************
<br>�ṹ��˵���� �洢�߼���ʼ��š���ֹ��ţ��������Ľṹ
**********************************************/
struct KL3DLinePointStruct
{
	KL3DLinePointStruct& operator= (const KL3DLinePointStruct& obj)
	{
		if(this != &obj)
		{
			m_3DLine = obj.m_3DLine;
			m_startIndex = obj.m_startIndex;
			m_endIndex = obj.m_endIndex;
		}
		return *this;
	}

	KL3DLine* m_3DLine; //��ָ��
	int m_startIndex; //��ʼ�������
	int m_endIndex; //��ֹ�������

};

/*!�洢�߼���ʼ��ֹ��Žṹָ�������*/
typedef std::vector<KL3DLinePointStruct*> KL3DLinePointStructArray;

/*!**********************************************************
<br>��˵������ά�ߵ�������
*************************************************************/

/*!����㼯*/
#define     KL3DPointVector   std::vector<KL3DPoint*>

class KL3DLine
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DLine();

	/*!Ĭ����������*/
	virtual ~KL3DLine();

	/*!�����ߺţ�Ψһ��ID*/
	void setID(const double& id);

	/*!�õ��ߺ�*/
	double getID() const;

	/*!�����ߵ�����*/
	void setType(KL3DLineType type);

	/*!�õ��ߵ�����*/
	KL3DLineType getType() const;

	/*!�������Ƿ�ѡ��*/
	void setIsSelected(bool isSelected);

	/*!�õ����Ƿ�ѡ��*/
	bool getIsSelected() const;

	/*!�������Ƿ񱻽�ֹ*/
	void setIsForbidden(bool isForbidden);

	/*!�õ����Ƿ�ѡ��*/
	bool getIsForbidden() const;

	/*!�����в����*/
	bool insertPoint(KL3DPoint* pPoint);

	/*!���ݵ�š��ߺŻ�ȡ���е���ά��*/
	KL3DPoint* getPoint(const double& pointID, const short& samestakeID);

	/*!�õ���ļ���*/
	KL3DPointVector* getPointVector();

	/*!���ö�������*/
	void setVertexArray(osg::ref_ptr<osg::Vec3Array> pVertexArray);

	/*!�õ���������*/
	osg::Vec3Array* getVertexArray();

	/*!������ɫ����*/
	void setColorArray(osg::ref_ptr<osg::Vec3Array> pColorArray);

	/*!�õ���ɫ����*/
	osg::Vec3Array* getColorArray();

	/*!���ñ�ʶ����*/
	void setFlagArray(osg::ref_ptr<osg::FloatArray> pFlagArray);

	/*!�õ���ʶ����*/
	osg::FloatArray* getFlagArray();

private:

	/*!�ߺţ��ߵ�Ψһ��ʶ*/
	double m_id;

	/*!���ͣ���Ϊ�����ߺͽ�����������*/
	KL3DLineType m_type;

	/*!��ʶ�����Ƿ�ѡ��*/
	bool m_isSelected;

	/*!��ʶ�����Ƿ񱻽�ֹ*/
	bool m_isForbidden;

	/*!�����ļ���*/
	KL3DPointVector* m_pointsVector;

	/*!��������������*/
	osg::ref_ptr<osg::Vec3Array> m_vertexArray;

	/*!��������ɫ����*/
	osg::ref_ptr<osg::Vec3Array> m_colorArray;

	/*!������ʾ��ɫ������ʾͼƬ�ı�ʶ*/
	osg::ref_ptr<osg::FloatArray> m_flagArray;

	
};

#endif