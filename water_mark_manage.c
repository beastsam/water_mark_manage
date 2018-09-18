/*
 * 动态水印管理接口
 * 作者：高杨
 * 日期：2018.9.18
 * 功能：根据用户名，终端机器特征码，文件标题，当前时间等信息将字符串生成图片
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
#include "water_mark_manage.h"
 
int water_mark_manage(char *pcUserName, char *aucDevcode, char *pcTitle, 
							char *pcCurtime, char *pucPic, int *uisize)
{
    /* 输入参数长度检查 */
    if(strlen(pcUserName)>MAX_USERNAME || strlen(aucDevcode)>MAX_DEVCODE ||strlen(strlen)>MAX_TITLE ||strlen(pcCurtime)>MAX_TIME ){
        return ERROR_PARAM;
    }
    
    gdImagePtr pstImg = NULL;            //声明图像结构体指针，结构体具体内容见gd.h文件
    
    int black = 0;                       //声明颜色索引
    int white = 0;
    double udFontHig = 50.0;             //字体高度
    char *pcErr = NULL;                  //gdImageStringFT()函数错误内容，若函数正常执行，函数返回NULL  
    int uiFontLen = 0;                   //存储图片生成高度
    int uiFontwid = 0;                   //存储图片生成宽度
    char pcMsg[MAX_BUFFER];              //参数集和字符串
    char pcJpegName[MAX_BUFFER];         //生成图片名称
    char *pcTmp = NULL;                    //gdimg存储缓存
    //linux中文字体为文泉驿微米黑，系统路径为/usr/share/fonts/wqy-microhei.ttc
    char *pcFont = "/usr/share/fonts/wqy-zenhei/wqy-zenhei.ttc";
    
    //计算单个字体宽度，按照左上，右上，右下，左下顺序，利用（X，Y）坐标表示，因此brect共有8个值
    int brect[8];          
       
    FILE *pfJpeg = NULL;                 //声明输出文件格式  正式代码删除

    
    
    /*  拼接输入参数，将参数整合到pcMsg中 */
   strncpy(pcMsg, pcUserName, strlen(pcUserName));
   strcat(pcMsg,aucDevcode);
   strcat(pcMsg,pcTitle);
   strcat(pcMsg,pcCurtime);  
   
    /* 获取brect用以测量图片大小 */
    pcErr = gdImageStringFT(NULL, &brect[0], 0, pcFont, 
                            udFontHig, 0.0, 0, 0, pcMsg);
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
                            udFontHig, 0.0, uiFontLen, uiFontwid, pcMsg);
     if(pcErr){
    return ERROR_RENDER_IMAGE;
    }
    
    /* 测试用代码段，生成图片名称，正式代码可删  91-96 */
    strncpy(pcJpegName, pcMsg, strlen(pcMsg));
    strcat(pcJpegName,".jpg");   
    //打开一个文件作为写入，"wb"意思是写二进制，对MSDOS很重要，对Unix来说影响较小
    pfJpeg = fopen(pcJpegName, "wb");
    //将图片输出到硬盘存储以jpg格式,第三个参数为按照默认图片质量（0-95）
    gdImageJpeg(pstImg, pfJpeg, -1);
    
    /* 将生成的图片buffer传入参数pucPic中 */
    int uiTempSize;
    pcTmp = (char*)gdImageJpegPtr(pstImg,&uiTempSize,-1); 
    memcpy(pucPic, pcTmp, uiTempSize);
    *uisize = uiTempSize;

    fclose(pfJpeg);    
    free(pcTmp);
    gdImageDestroy(pstImg);
    
    return 0;

}
