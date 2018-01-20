#ifndef __KL3DENTITYLINE_H__
#define __KL3DENTITYLINE_H__

#include "KL3DTerrainTileManager.h"
#include "KL3DBaseEntity.h"

/*!***************************************
<br>��˵���� ��ά��״ͼԪ
*****************************************/

class KL3DEntityLine: public KL3DBaseEntity
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DEntityLine();

	/*!Ĭ����������*/
	~KL3DEntityLine();

	/*!��ʼ������*/
	virtual void init();

	/*!���ùյ�����*/
	void setPointArray(osg::Vec3Array* pPointArray);
	
	/*!�����߿�*/
	void setLineWidth(const float& pLineWidth);

	/*!��������ʽ*/
	/*!����ʽpLineStyle��LineSolid/LineDash/LineDot/LineDashDot*/
	void setLineStyle(const std::string& pLineStyle);

	/*!���õ��ι������*/
	void setTerrainTileManager(KL3DTerrainTileManager* terrainTileManager);
private:
	/*!�յ�����*/
	osg::ref_ptr<osg::Vec3Array> m_pointArray;

	/*!��ĸ���*/
	int m_nPointCount;

	/*!�߿�*/
	float m_lineWidth;

	/*!����ʽ*/
	GLushort m_lineStyle;

	/*!���ι�����(��ͼԪ��Ҫ��ֵ)*/
	KL3DTerrainTileManager* m_terrainTileManager;
};
#endif