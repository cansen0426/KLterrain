#ifndef __KL3DCOMMONSTRUCT_H__
#define __KL3DCOMMONSTRUCT_H__

/*!****************************************************
<br>类说明：三维观测系统公用数据结构申明类
******************************************************/
/*!三位点无效值*/
#define KL3DDEFAULTVALUE -99999.0f

/*!圆周率*/
#define KL3DPI 3.14159f

/*!三维观测系统各缺省颜色*/
#define KL3D_SHOTPOINT_DEFAULTCOLOR osg::Vec3(1.0f, 0.0f, 0.0f)
#define KL3D_RCVPOINT_DEFAULTCOLOR  osg::Vec3(0.0f, 0.0f, 1.0f)
#define KL3D_POINT_SELCOLOR         osg::Vec3(1.0f, 1.0f, 1.0f)
#define KL3D_POINT_FORBIDCOLOR      osg::Vec3(0.0f, 0.0f, 0.0f)
#define KL3D_CONTOUR_DEFAULTCOLOR   osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)


/*!三维线的类型*/
typedef enum
{
	KL3D_SHOTLINE,
	KL3D_RCVLINE
}KL3DLineType;

/*!三维观测系统编辑的类型*/
typedef enum
{
	KL3D_SHOTPOINT_EDIT, //炮点的编辑
	KL3D_RCVPOINT_EDIT, //检波点的编辑
	KL3D_SHOTLINE_EDIT, //炮线编辑
	KL3D_RCVLINE_EDIT, //检波线的编辑
	KL3D_POINT_EDIT, //炮点、检波点编辑
	KL3D_LINE_EDIT //炮线、检波线编辑
}KL3DEditObject;


/*!三维观测系统编辑对象*/
typedef enum
{
	KL3D_SEL,

	KL3D_UNSEL,

	KL3D_MOVE,

	KL3D_FORBID,

	KL3D_ACTIVE,

	KL3D_DELETE
}KL3DEditType;


/*!三维障碍物类型*/
typedef enum
{
	KL3D_OBSTACLE_NONE,

	KL3D_OBSTACLE_AREA,

	KL3D_OBSTACLE_LINE,

	KL3D_OBSTACLE_POINT
}KL3DObstacleType;


/*!三维观测系统编辑的点的类型*/
class KL3DPoint;

typedef struct 
{
	double m_lineID;

	KL3DLineType m_type;

	KL3DPoint* m_editPoint;
}KL3DEditPoint;


/*!二三维同步操作类型*/
typedef enum
{
	KL3D_SYNCHRO_ACTIVE,
	KL3D_SYNCHRO_RORBID,
	KL3D_SYNCHRO_MOVE,
	KL3D_SYNCHRO_DELETE,
	KL3D_SYNCHRO_ADD
}KL3DSynchroType;

#endif