#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "OFD_WMM_GenWaterMarkPic.h"


int test();
							
int main()
{
    pthread_t thread[1000];
    int tstart[100];
    int tjoin[100];
    int rvalue[100];
    int num;
    int i;
    
    while(1){
        printf("输入线程数：");
        scanf("%d",&num);
        if(num<1001 && num>0){
            break;
            }
        printf("put of range\n");
    }
    
    
    
    for(i = 0;i<num;i++){
        tstart[i] = pthread_create(&thread[i],NULL,(void*)&test,NULL);
        if(tstart[i] == 0){
            printf("thread[%d] 创建成功\n",i);
        } else{
            printf("thread[%d] 创建失败\n",i);
        }
    }
    
    
    for(i = 0;i<num;i++){
        tjoin[i] = pthread_join(thread[i],(void*)&(rvalue[i]));
        if(tjoin[i] == 0){
            printf("thread[%d] 结束成功\n",i);
               if(rvalue[i] == 1){
                printf("pic suc\n");
               }else {
                printf("pic err\n");
               }
               
               
               
        } else{
            printf("thread[%d] 结束失败\n",i);
        }
    }
    return 0;
}

int test()
{
    char *pucPic = NULL;
	 int uiSize =0;
	 FILE *out;
	 	
    char *pcUserName = "张三";
    char *aucDevcode = "123";
    char *pcTitle = "防泄露";
	 char *pcCurtime;
	 char filename[10];
    time_t timep;
    time(&timep);
    pcCurtime = ctime(&timep);
    sprintf(filename,"%lu.jpg",pthread_self());
	 out = fopen(filename,"wb");
	 pucPic = malloc(50 * 1024);
	 int y;
	 
	 y = OFD_WMM_GenWaterMarkPic(pcUserName, aucDevcode, pcTitle, pcCurtime,pucPic,&uiSize);
	 if(y!=0){
	    printf("error\n");
	    return 1;
	 }
	
	 fwrite(pucPic,1,uiSize,out);
	 free(pucPic);
	 fclose(out);

	 return 1;
}
