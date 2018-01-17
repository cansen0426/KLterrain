#ifndef __KL3DLINE_H__
#define __KL3DLINE_H__

#include <osg/Array>

#include "KL3DCommonStruct.h"
#include "KL3DPoint.h"

class KL3DLine;

/*!*******************************************
<br>结构体说明： 存储线及起始点号、终止点号（索引）的结构
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

	KL3DLine* m_3DLine; //线指针
	int m_startIndex; //起始点号索引
	int m_endIndex; //终止点号索引

};

/*!存储线及起始终止点号结构指针的数组*/
typedef std::vector<KL3DLinePointStruct*> KL3DLinePointStructArray;

/*!**********************************************************
<br>类说明：三维线的数据类
*************************************************************/

/*!定义点集*/
#define     KL3DPointVector   std::vector<KL3DPoint*>

class KL3DLine
{
public:
	/*!默认构造函数*/
	KL3DLine();

	/*!默认析构函数*/
	virtual ~KL3DLine();

	/*!设置线号：唯一的ID*/
	void setID(const double& id);

	/*!得到线号*/
	double getID() const;

	/*!设置线的类型*/
	void setType(KL3DLineType type);

	/*!得到线的类型*/
	KL3DLineType getType() const;

	/*!设置线是否被选中*/
	void setIsSelected(bool isSelected);

	/*!得到线是否被选中*/
	bool getIsSelected() const;

	/*!设置线是否被禁止*/
	void setIsForbidden(bool isForbidden);

	/*!得到线是否被选中*/
	bool getIsForbidden() const;

	/*!向线中插入点*/
	bool insertPoint(KL3DPoint* pPoint);

	/*!根据点号、线号获取线中的三维点*/
	KL3DPoint* getPoint(const double& pointID, const short& samestakeID);

	/*!得到点的集合*/
	KL3DPointVector* getPointVector();

	/*!设置顶点数组*/
	void setVertexArray(osg::ref_ptr<osg::Vec3Array> pVertexArray);

	/*!得到顶点数组*/
	osg::Vec3Array* getVertexArray();

	/*!设置颜色数组*/
	void setColorArray(osg::ref_ptr<osg::Vec3Array> pColorArray);

	/*!得到颜色数组*/
	osg::Vec3Array* getColorArray();

	/*!设置标识数组*/
	void setFlagArray(osg::ref_ptr<osg::FloatArray> pFlagArray);

	/*!得到标识数组*/
	osg::FloatArray* getFlagArray();

private:

	/*!线号：线的唯一标识*/
	double m_id;

	/*!类型：分为激发线和接收线两大类*/
	KL3DLineType m_type;

	/*!标识：线是否被选中*/
	bool m_isSelected;

	/*!标识：线是否被禁止*/
	bool m_isForbidden;

	/*!保存点的集合*/
	KL3DPointVector* m_pointsVector;

	/*!保存点的坐标数组*/
	osg::ref_ptr<osg::Vec3Array> m_vertexArray;

	/*!保存点的颜色数组*/
	osg::ref_ptr<osg::Vec3Array> m_colorArray;

	/*!保存显示颜色还是显示图片的标识*/
	osg::ref_ptr<osg::FloatArray> m_flagArray;

	
};

#endif