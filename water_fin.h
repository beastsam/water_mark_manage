/*
 * 字符串图片生成
 * 作者：beast
 * 日期：2018.9.18
 * 功能：根据用户名，终端机器特征码，文件标题，当前时间等信息生成图片形式的水印
 * 参数：
 *     pcUserName[in]    用户名
 *     aucDevcode[in]    终端机器特征码
 *     pcTitle[in]       文件标题
 *     pcCurtime[in]     当前时间
 *     pucPic[out]       图片形式水印缓冲区
 *     uisize[out]       记录图片形式水印缓冲区大小
 * 返回值：
 *       如成功执行返回0
 *       若执行失败返回错误代码  
 * 备注
 */
 
#ifndef OFD_WMM_GENWATERMARKPIC_H_
#define OFD_WMM_GENWATERMARKPIC_H_

#define _CRT_SECURE_NO_WARNINGS

#define ERROR_PARAM 11               
#define ERROR_GET_FONT_SIZE 12
#define ERROR_RENDER_IMAGE 13

#define MAX_USERNAME 256+1
#define MAX_DEVCODE 16+1
#define MAX_TITLE 256+1
#define MAX_TIME 32+1
#define MAX_BUFFER 564
 
int OFD_WMM_GenWaterMarkPic(char *pcUserName, char *aucDevcode, char *pcTitle, 
							char *pcCurtime, char *pucPic, int *uiSize);
							
 
#endif
