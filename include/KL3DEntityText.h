#ifndef __KL3DENTITYTEXT_H__
#define __KL3DENTITYTEXT_H__

//#include <QtCore/QTextCodec>
#include <osg/PositionAttitudeTransform>
#include "KL3DBaseEntity.h"

/*!***************************************
<br>��˵���� ��ά�ı�ͼԪ
*****************************************/

class KL3DEntityText : public KL3DBaseEntity
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DEntityText();

	/*!Ĭ����������*/
	~KL3DEntityText();

	/*!��ʼ����������ͨ��ʽ��*/
	virtual void init();

	/*!��ʼ��������BillBoard��ʽ��*/
	virtual void initBillBoard();

	/*!����Ҫ��ʾ���ı�*/
	void setShowText(const std::string& showText);

	/*!�����ı�λ������*/
	void setTextPosition(const osg::Vec3& textPosition);

	/*!�����ı�����*/
	void setTextFont(const std::string& textFont);

	/*!�����ı���С*/
	void setCharacterSize(const float& characterSize);
	
	/*!��ȡPAT����*/
	osg::ref_ptr<osg::PositionAttitudeTransform> getPAT();
	
private:
	/*!��ʾ�ı�*/
	std::string m_showText;

	/*!λ������*/
	osg::Vec3 m_textPosition;

	/*!����*/
	std::string m_textFont;

	/*!�����С*/
	float m_characterSize;

	/*!PositionAttitudeTransform*/
	osg::ref_ptr<osg::PositionAttitudeTransform> m_pat;
};


#endif