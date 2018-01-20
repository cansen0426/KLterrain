#ifndef __KL3DENTITYTEXT_H__
#define __KL3DENTITYTEXT_H__

//#include <QtCore/QTextCodec>
#include <osg/PositionAttitudeTransform>
#include "KL3DBaseEntity.h"

/*!***************************************
<br>类说明： 三维文本图元
*****************************************/

class KL3DEntityText : public KL3DBaseEntity
{
public:
	/*!默认构造函数*/
	KL3DEntityText();

	/*!默认析构函数*/
	~KL3DEntityText();

	/*!初始化函数（普通方式）*/
	virtual void init();

	/*!初始化函数（BillBoard方式）*/
	virtual void initBillBoard();

	/*!设置要显示的文本*/
	void setShowText(const std::string& showText);

	/*!设置文本位置坐标*/
	void setTextPosition(const osg::Vec3& textPosition);

	/*!设置文本字体*/
	void setTextFont(const std::string& textFont);

	/*!设置文本大小*/
	void setCharacterSize(const float& characterSize);
	
	/*!获取PAT对象*/
	osg::ref_ptr<osg::PositionAttitudeTransform> getPAT();
	
private:
	/*!显示文本*/
	std::string m_showText;

	/*!位置坐标*/
	osg::Vec3 m_textPosition;

	/*!字体*/
	std::string m_textFont;

	/*!字体大小*/
	float m_characterSize;

	/*!PositionAttitudeTransform*/
	osg::ref_ptr<osg::PositionAttitudeTransform> m_pat;
};


#endif