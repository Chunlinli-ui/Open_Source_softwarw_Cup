#include <stdio.h>
#include "putin.h"
typedef struct{
        int id;
        char name[10];
        char sex[10];
        int grade;
}student;

int putin(void)
{
        printf("请输入参与抽奖的人数：\n");
        int n;
        scanf("%d",&n);
        student stu[n];
        printf("请参照一下格式输入每个学生的信息（用空格来分割）：\n");
        printf("学号 姓名 性别 年级\n");
        for(int i=0;i<n;i++){
                printf("请输入第%d个学生的信息\n",i+1);
                scanf("%d %s %s %d",&stu[i].id,stu[i].name,stu[i].sex,&stu[i].grade);
        }
        int i;
        FILE *fp;
        if((fp=fopen("informatioin.txt","wb"))==NULL)
        {
                printf("cannot open file\n");
                return;
        }
        for(i=0;i<n;i++){
                if(fwrite(&stu[i],sizeof(student),1,fp)!=1)
                        printf("file write error\n");
        }
        printf("文件创建成功\n");
        fclose(fp);
        printf("数据存储完成\n");
        return n;
}
