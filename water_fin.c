/*
 * 字符串图片生成
 * 作者：beast
 * 日期：2018.9.18
 * 功能：根据用户名，终端机器特征码，文件标题，当前时间等信息将字符串生成图片缓存
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
 * 备注：
 *       引用第三方库libgd 
 *       官网：https://libgd.github.io
 */
 
#include <stdio.h>
#include <string.h>
#include "gd.h"
#include "OFD_WMM_GenWaterMarkPic.h"
 
int OFD_WMM_GenWaterMarkPic(char *pcUserName, char *aucDevcode, char *pcTitle, 
							char *pcCurtime, char *pucPic, int *uiSize)
{
    /* 输入参数长度检查 */
    if(strlen(pcUserName)>MAX_USERNAME || strlen(aucDevcode)>MAX_DEVCODE ||strlen(pcTitle)>MAX_TITLE ||strlen(pcCurtime)>MAX_TIME ){
        return ERROR_PARAM;
    }
    
    gdImagePtr pstImg = NULL;            //声明图像结构体指针，结构体具体内容见gd.h文件
    int black = 0;                       //声明颜色索引
    int white = 0;
    double udFontHig = 50.0;             //字体高度
    char *pcErr = NULL;                  //gdImageStringFT()函数错误内容，若函数正常执行，函数返回NULL  
    int uiFontLen = 0;                   //存储图片生成宽度
    int uiFontwid = 0;                   //存储图片生成高度
    char cMsg[MAX_BUFFER];              //参数集和字符串
    char *pcTmp = NULL;                    //gdimg存储缓存
    //linux中文字体为文泉驿微米黑，系统路径为/usr/share/fonts/wqy-microhei.ttc
    char *pcFont = "/usr/share/fonts/wqy-zenhei/wqy-zenhei.ttc";
    
    //计算单个字体宽度，按照左上，右上，右下，左下顺序，利用（X，Y）坐标表示，因此brect共有8个值
    int brect[8];          
    
    /*  拼接输入参数，将参数整合到pcMsg中 */
   strncpy(cMsg, pcUserName, strlen(pcUserName));
   strcat(cMsg,aucDevcode);
   strcat(cMsg,pcTitle);
   strcat(cMsg,pcCurtime);  
   
    /* 获取brect用以测量图片大小 */
    pcErr = gdImageStringFT(NULL, &brect[0], 0, pcFont, 
                            udFontHig, 0.0, 0, 0, cMsg);
    if(pcErr){
    return ERROR_GET_FONT_SIZE;
    }
    
    /* 创建对字符串来讲一个足够大尺寸的图片，并且有一些留白 */
    uiFontLen = brect[2]-brect[6]+6;
    uiFontwid = brect[3]-brect[7]+6;
    
    //创建uiFontLen*uiFontwid的图像，如果需要使用真彩色，换成gdImageCreatTrueColor接口
    pstImg = gdImageCreate(uiFontLen,uiFontwid);
    
    /* 指定背景色，因为是图中首个被定义的颜色所以为背景色.颜色为红绿蓝三原色组成 */
    white = gdImageColorResolve(pstImg, 255, 255, 255);
    black = gdImageColorResolve(pstImg, 0, 0, 0);
    
    /* 设置打印字符串左下角基准点 */
    uiFontLen = 3-brect[6];
    uiFontwid = 3-brect[7];
    
    /* 将字符串打印至gd image */
    pcErr = gdImageStringFT(pstImg, &brect[0], black, pcFont, 
                            udFontHig, 0.0, uiFontLen, uiFontwid, cMsg);
     if(pcErr){
    return ERROR_RENDER_IMAGE;
    }
        
    /* 将生成的图片buffer传入参数pucPic中 */
    int uiTempSize = 0;
    pcTmp = (char*)gdImageJpegPtr(pstImg,&uiTempSize,-1); 
    memcpy(pucPic, pcTmp, uiTempSize);
    *uiSize = uiTempSize;
    
    free(pcTmp);
    gdImageDestroy(pstImg);
    
    return 0;

}
