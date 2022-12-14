//======================================================================
/**
*  @file      Protechny.h
*
*  项目描述： 粒子系统
*  文件描述:  喷泉类 
*  适用平台： Windows98/2000/NT/XP
*  
*  作者：     WWBOSS
*  电子邮件:  wwboss123@gmail.com
*  创建日期： 2006-12-18	
*  修改日期： 2006-12-19
*	
*/																			
//======================================================================

#ifndef  __PROTECHNY_H__
#define  __PROTECHNY_H__


#include "CBMPLoader.h"
#include "Particle.h"


/** 喷泉类 */
class CProtechny : public CParticle
{

public:
	CProtechny()  {};
	~CProtechny() {};
	
	bool		Init(int num );  /**< 初始化过程 */
	void		Render();        /**< 渲染过程 */
	void		Update();        /**< 更新过程 */

private:
	CBMPLoader  m_texture;       /**< 粒子的纹理 */

}; 

#endif //__PROTECHNY_H__
