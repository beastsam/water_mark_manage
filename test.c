#include <stdio.h>
#include <string.h>
#include "gd.h"

int main(int argc, char **argv)
{
    gdImagePtr stImg;             //声明图像结构体，具体内容gd.h文件
    FILE *pfJpeg = NULL;          //声明输出文件格式
    int black;                    //声明颜色索引
    int white;
    char *pcMsg = "hello, 你好";    //转换字符串内容
    double sz = 100.0;            //字体高度
    char *err = NULL;
    int x;                        //存储图片生成高度
    int y;                        //存储图片生成宽度
    //linux中文字体为文泉驿微米黑，系统路径为/usr/share/fonts/wqy-microhei.ttc
    char *pcFont = "/usr/share/fonts/wqy-zenhei/wqy-zenhei.ttc";
    
    //计算单个字体宽度，按照左下，右下，右上，左上顺序，利用（X，Y）坐标表示，因此brect共有8个值
    int brect[8];            
         
        
    //获取brect用以测量图片大小
    err = gdImageStringFT(NULL, &brect[0], 0, pcFont, sz, 0.0, 0, 0, pcMsg);
    if(err){
    fprintf(stderr, "%s", err);
    return 1;
    }
    
    
    //创建对字符串来讲一个足够大尺寸的图片，并且有一些留白
    x = brect[2]-brect[6]+6;
    y = brect[3]-brect[7]+6;
    
    //创建x*y的图像，如果需要使用真彩色，换成gdImageCreatTrueColor接口
    stImg = gdImageCreate(x,y);
    
    //指定背景色，因为是图中首个被定义的颜色所以为背景色.颜色为红绿蓝三原色组成
    white = gdImageColorResolve(stImg, 255, 255, 255);
    
    black = gdImageColorResolve(stImg, 0, 0, 0);
    
    x = 3-brect[6];
    y = 3-brect[7];
    err = gdImageStringFT(stImg, &brect[0], black, pcFont, sz,0.0, x, y, pcMsg);
     if(err){
    fprintf(stderr, "%s", err);
    return 1;
    }
    
    //打开一个文件作为写入，"wb"意思是写二进制，对MSDOS很重要，对Unix来说影响较小
    pfJpeg = fopen("test.jpg", "wb");
    
    //将图片输出到硬盘存储以jpg格式,第三个参数为按照默认图片质量（0-95）
    gdImageJpeg(stImg, pfJpeg, -1);
    
    fclose(pfJpeg);
    gdImageDestroy(stImg);
    return 0;
   
}
