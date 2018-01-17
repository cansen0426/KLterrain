#ifndef __KL3DCOMMONSTRUCT_H__
#define __KL3DCOMMONSTRUCT_H__

/*!****************************************************
<br>��˵������ά�۲�ϵͳ�������ݽṹ������
******************************************************/
/*!��λ����Чֵ*/
#define KL3DDEFAULTVALUE -99999.0f

/*!Բ����*/
#define KL3DPI 3.14159f

/*!��ά�۲�ϵͳ��ȱʡ��ɫ*/
#define KL3D_SHOTPOINT_DEFAULTCOLOR osg::Vec3(1.0f, 0.0f, 0.0f)
#define KL3D_RCVPOINT_DEFAULTCOLOR  osg::Vec3(0.0f, 0.0f, 1.0f)
#define KL3D_POINT_SELCOLOR         osg::Vec3(1.0f, 1.0f, 1.0f)
#define KL3D_POINT_FORBIDCOLOR      osg::Vec3(0.0f, 0.0f, 0.0f)
#define KL3D_CONTOUR_DEFAULTCOLOR   osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)


/*!��ά�ߵ�����*/
typedef enum
{
	KL3D_SHOTLINE,
	KL3D_RCVLINE
}KL3DLineType;

/*!��ά�۲�ϵͳ�༭������*/
typedef enum
{
	KL3D_SHOTPOINT_EDIT, //�ڵ�ı༭
	KL3D_RCVPOINT_EDIT, //�첨��ı༭
	KL3D_SHOTLINE_EDIT, //���߱༭
	KL3D_RCVLINE_EDIT, //�첨�ߵı༭
	KL3D_POINT_EDIT, //�ڵ㡢�첨��༭
	KL3D_LINE_EDIT //���ߡ��첨�߱༭
}KL3DEditObject;


/*!��ά�۲�ϵͳ�༭����*/
typedef enum
{
	KL3D_SEL,

	KL3D_UNSEL,

	KL3D_MOVE,

	KL3D_FORBID,

	KL3D_ACTIVE,

	KL3D_DELETE
}KL3DEditType;


/*!��ά�ϰ�������*/
typedef enum
{
	KL3D_OBSTACLE_NONE,

	KL3D_OBSTACLE_AREA,

	KL3D_OBSTACLE_LINE,

	KL3D_OBSTACLE_POINT
}KL3DObstacleType;


/*!��ά�۲�ϵͳ�༭�ĵ������*/
class KL3DPoint;

typedef struct 
{
	double m_lineID;

	KL3DLineType m_type;

	KL3DPoint* m_editPoint;
}KL3DEditPoint;


/*!����άͬ����������*/
typedef enum
{
	KL3D_SYNCHRO_ACTIVE,
	KL3D_SYNCHRO_RORBID,
	KL3D_SYNCHRO_MOVE,
	KL3D_SYNCHRO_DELETE,
	KL3D_SYNCHRO_ADD
}KL3DSynchroType;

#endif