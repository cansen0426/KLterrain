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
	//解决中文显示乱码问题
	//QTextCodec* code = QTextCodec::codeForName("UTF-8");
	//Qstring qstr = Qstring(Qstring::fromLocal8bit(m_showText.c_str()));
	
	std::string qstr;//此处注释掉上面两句话以下面的做注释
	//std::string str = code->fromUnicode(qstr).data();
	std::string str;//此处注释掉上面两句话以下面的做注释
	
	//设置显示文本
	text->setText(str,osgText::String::ENCODING_UTF8);
	text->setCharacterSize(osgText::TextBase::SCREEN_COORDS);
	//设置文本位置坐标
	text->setPosition(m_textPosition);
	text->setFont(m_textFont);
	//设置文本字体大小
	text->setCharacterSize(m_characterSize);
	//设置文本颜色
	text->setColor(m_color);
	
	addDrawable(text.get());
}

void KL3DEntityText::initBillBoard()
{
	osg::ref_ptr<osgText::Text> text = new osgText::Text();
	//解决中文显示乱码问题
	//QTextCodec* code = QTextCodec::codeForName("UTF-8");
	//Qstring qstr = Qstring(Qstring::fromLocal8bit(m_showText.c_str()));

	std::string qstr;//此处注释掉上面两句话以下面的做注释
	//std::string str = code->fromUnicode(qstr).data();
	std::string str;//此处注释掉上面两句话以下面的做注释

	m_pat = new osg::PositionAttitudeTransform();
	//设置文本位置坐标
	m_pat->setPosition(m_textPosition);

	//设置显示文本
	text->setText(str,osgText::String::ENCODING_UTF8);
	text->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);

	osg::ref_ptr<osgText::Font> font = new osgText::Font();
	font = osgText::readFontFile(m_textFont);

	text->setFont(font);

	//设置文本字体大小
	text->setCharacterSize(m_characterSize);
	//设置文本颜色
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





