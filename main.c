#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "water_mark_manage.h"
int main()
{
    char *pcUserName = "张三";
    char *aucDevcode = "101";
    char *pcTitle = "好的话";
	 char *pcCurtime = "201809172102";
	 char *pucPic = NULL;
	 int uisize =0;
	 FILE *out;
	 out = fopen("33.jpg","wb");
	 pucPic = malloc(128 * 1024);
	 water_mark_manage(pcUserName, aucDevcode, pcTitle, pcCurtime, pucPic,&uisize);

	 fwrite(pucPic,1,uisize,out);
	 
	 free(pucPic);
	 fclose(out);
	 
	 return 0;
	 
}

