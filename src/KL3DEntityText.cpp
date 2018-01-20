#include "KL3DEntityText.h"
#include <osgText/Text>
#include <osgText/Font>

KL3DEntityText::KL3DEntityText():
	m_showText(""),
	m_textPosition(osg::Vec3(0.0f,0.0f,0.0f)),
	m_textFont(""),
	m_characterSize(30.0),
	m_pat(NULL)
{

}

KL3DEntityText::~KL3DEntityText()
{
	
}

void KL3DEntityText::init()
{
	osg::ref_ptr<osgText::Text> text = new osgText::Text();
	//���������ʾ��������
	//QTextCodec* code = QTextCodec::codeForName("UTF-8");
	//Qstring qstr = Qstring(Qstring::fromLocal8bit(m_showText.c_str()));
	
	std::string qstr;//�˴�ע�͵��������仰���������ע��
	//std::string str = code->fromUnicode(qstr).data();
	std::string str;//�˴�ע�͵��������仰���������ע��
	
	//������ʾ�ı�
	text->setText(str,osgText::String::ENCODING_UTF8);
	text->setCharacterSize(osgText::TextBase::SCREEN_COORDS);
	//�����ı�λ������
	text->setPosition(m_textPosition);
	text->setFont(m_textFont);
	//�����ı������С
	text->setCharacterSize(m_characterSize);
	//�����ı���ɫ
	text->setColor(m_color);
	
	addDrawable(text.get());
}

void KL3DEntityText::initBillBoard()
{
	osg::ref_ptr<osgText::Text> text = new osgText::Text();
	//���������ʾ��������
	//QTextCodec* code = QTextCodec::codeForName("UTF-8");
	//Qstring qstr = Qstring(Qstring::fromLocal8bit(m_showText.c_str()));

	std::string qstr;//�˴�ע�͵��������仰���������ע��
	//std::string str = code->fromUnicode(qstr).data();
	std::string str;//�˴�ע�͵��������仰���������ע��

	m_pat = new osg::PositionAttitudeTransform();
	//�����ı�λ������
	m_pat->setPosition(m_textPosition);

	//������ʾ�ı�
	text->setText(str,osgText::String::ENCODING_UTF8);
	text->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);

	osg::ref_ptr<osgText::Font> font = new osgText::Font();
	font = osgText::readFontFile(m_textFont);

	text->setFont(font);

	//�����ı������С
	text->setCharacterSize(m_characterSize);
	//�����ı���ɫ
	text->setColor(m_color);
	text->setAlignment(osgText::Text::CENTER_BOTTOM);
	text->setAutoRotateToScreen(true);

	osg::ref_ptr<osg::Billboard> billboard = new osg::Billboard();
	billboard->setMode(osg::Billboard::POINT_ROT_WORLD);

	billboard->addDrawable(text.get());
	m_pat->addChild(billboard.get());
}

void KL3DEntityText::setShowText(const std::string& showText)
{
	m_showText = showText;
}

void KL3DEntityText::setTextPosition(const osg::Vec3& textPosition)
{
	m_textPosition = textPosition;
}

void KL3DEntityText::setTextFont(const std::string& textFont)
{
	m_textFont = textFont;
}

void KL3DEntityText::setCharacterSize(const float& characterSize)
{
	m_characterSize = characterSize;
}

osg::ref_ptr<osg::PositionAttitudeTransform> KL3DEntityText::getPAT()
{
	return m_pat;
}





