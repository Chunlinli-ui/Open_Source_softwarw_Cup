#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "putin.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
 
#define CLRSCR  system("cls")
#define PRINT_TITLE "\nnum\tid\t\tname\tsex \tgrade\n"
#define PRINT_FORMAT "%d\t%s\t%s\t%s\t%s\n",i,p->stu.id,p->stu.name,p->stu.sex,p->stu.grade
#define WRITE_FORMAT "%s\t%s\t%s\t%s\n",p->stu.id,p->stu.name,p->stu.sex,p->stu.grade
#define READ_FORMAT "%s %s %s %s",&p->stu.id,&p->stu.name,&p->stu.sex,&p->stu.grade
 
typedef struct{
​int id;
​char name[10];
​char sex[10];
​int grade;
}student;
 
struct Student
{
       char    id[9];
       char    name[10];
       char    sex[3];
       char    grade[10];
 
};
//定义单链表结点
typedef struct listnode
{
        struct Student stu;
        struct listnode *next;
}node;

int chachong(int a,int b[],int n){
	int i;
	for(i=0;i<n;i++){
		if(a==b[i])return 1;
	}
	return 0;
}

void lotterying ()
{
	//int DATALEN=10;//调试完成后改用下面一行；
	int DATALEN=putin();//此处调用了putin接口，在putin函数中输入学生信息，将其储存在txt文件中，并返回一个整形值赋给DATALEN，即学生的数量；
	int i=0;
	FILE *fp;
	student std[DATALEN];
//文件打开开始
 	fp=fopen("information.txt","r");
	if(fp==NULL)
	{
		printf("Cannot open the file.\n");
	}
	while(!feof(fp))
	{
		fscanf(fp,"%d %s %s %d\n",&std[i].id,&std[i].name,&std[i].sex,&std[i].grade);
		i++;
	}
	fclose(fp);
	/*
	int j;
	for(j=0;j<i;j++){
		printf("%d %s %s %d\n",std[j].id,std[j].name,std[j].sex,std[j].grade);
	}调试程序*/
	//文件打开结束
	
	//奖项数目规定开始
	printf("请输入奖项等级数目：");
	int n;
	scanf("%d",&n);
	int k=n;//因为n在下面有更改用于其他作用，此处用k来为下面抽奖过程中作循环次数控制
	int prizenumber[n+1];
	prizenumber[0]=0;
	for(i=1;i<=n;i++){
		printf("%d等奖的数目是：",i);
		scanf("%d",&prizenumber[i]);
		prizenumber[0]+=prizenumber[i];
	}
/*调试程序
	for(i=0;i<=n;i++){
		printf("%d\n",prizenumber[i]);
	}*/
	
	//奖项数目规定结束,此时prizenumber[i]中储存着i等奖的数目，prizenumber[0]储存奖项的数目之和，用于后续抽奖；
	//此时，主程序中有std[DATALEN]的结构体数组，储存了学生的个人信息
	n=prizenumber[0];
	//抽奖开始
	int a[DATALEN],data[n],same[n];
	for(i=0;i<DATALEN;i++){
		a[i]=std[i].id;
	}//将学号存入数组a[];
	/*printf("这是a[i]的值\n");
	for(i=0;i<DATALEN;i++){
		printf("%d\n",a[i]);
	}*/
	
	int m;//用于临时储存随即选择的值；
	n=0;//用于查重计数
	Randomize();
	int j;//用于控制循环抽奖的次数
	for(j=1;j<=k;j++){
		for(i=0;i<prizenumber[j];i++){
			while(1){
				m=RandomInteger(0,DATALEN-1);
				if(chachong(m,same,n)==0){
					data[n]=a[m];
					same[n]=m;
					n+=1;
					break;
				}
			}
		}
	}

/*调试程序
	for(i=0;i<6;i++){
                printf("%d\n",same[i]);
        }printf("same\n");

	 
        for(i=0;i<6;i++){
                printf("%d\n",data[i]);
        }printf("data\n");
	*/
	
	i=0;
	int p=0;//用于和prizenumber【j】相加，控制输出次数
	for(j=1;j<=k;j++){
		printf("%d等奖获得者学号为:\n",j);
		for(i=i;i<prizenumber[j]+p;i++){
			printf("%d\n",data[i]);
		}
		p=i;
	}
	printf("抽奖结束\n");
	//抽奖结束
	//完成了抽奖的全
}


int MySelect(node * head,node *temp)   //返回查找到符合条件的项目数
{
        int equal,N;
        char CHAR[10];


        printf("----------------------------------------------\n\n");
        printf("查找模式:1是相等查找,0是不相等查找\n");
	printf("列名编号:1是学号,2是姓名,3是性别,4是获奖等级\n");
	printf("\n--------------------------------------------\n");

      	do
        {
        printf("\nselect lookup mode:");//用scanf时输入字母会错误 改用getche，不用scanf
        equal=GetInteger();
        if((equal!='1')&&(equal!='0'))
                printf("\n\twrong input\n");
        }
        while((equal!='1')&&(equal!='0'));
        equal=equal-48;
		do
        {
        printf("\n enter the column name number:");
        N=GetInteger();
        if(N!='1'&&N!='2'&&N!='3'&&N!='4')
                printf("\n\twrong input\n");
        }
        while(N!='1'&&N!='2'&&N!='3'&&N!='4');
        switch(N)
        {
        case '1':       N=0;break;
        case '2':       N=9;break;
        case '3':       N=16;break;
        case '4':       N=19;break;
        }



        printf("\ninput key words:");
        scanf("%s",CHAR);

        int  i=0,flag;
        node *p,*tp=temp;
        p=head->next;
	while (NULL!=p)
        {
                flag=strcmp((char *)p+N,CHAR);
                if((abs(flag)+equal)==1)//当equal为1时是相等查找,为0时是不相等查找
                {
                        node *end;
                        end = (node *)malloc(sizeof(node));
                        tp->next=end;
             
                        tp->next=NULL;
                        tp->stu=p->stu;

                        if(i==0)
                                printf (PRINT_TITLE);
                        i++;
                        printf(PRINT_FORMAT);




                }
                p=p->next;

        }

        if(i==0)
                printf("\n\tno qualifying information was found\n");

return i;
}

void InsertSort(node *head)//学号从小到大排序
{ 
	node *p,*q,*r,*u;
    p=head->next;  
	head->next=NULL;
    while(p!=NULL)
    {
		r=head;  
		q=head->next;
         
		while(q!=NULL&& strcmp(q->stu.id,p->stu.id)<0) //成立则基点向后移
		{
			r=q; 
			q=q->next;
		}
		u=p->next; 
		p->next=r->next;   //p->stu.num比q->stu.num小，放到q->stu.num前面
		r->next=p;  

		p=u;//下一上节点与基点进行比较
	}
}

void CheckNum(node *head)
{
	/*删除学号重复的条目*/
		node *release,*p;
		p=head->next;
		int m=0;
		while(NULL!=p->next)
		{
			node *p2=p;
			
			while(NULL!=p2->next)
			{
				if(0==strcmp(p->stu.id,p2->next->stu.id))
				{	m++;
					if(m==1)
					printf("\t\t the following entry was not imported because of a conflict between the student number and the previous information\n");

					printf ("%d\t%s\t%s\t%s\t%s\n",m,p2->next->stu.id,p2->next->stu.name,\
					p2->next->stu.sex,p2->next->stu.grade);

					release=p2->next;
					p2->next=p2->next->next; 
					free(release);				
				}
				p2=p2->next;
			}

			p=p->next;
		}


}

void FscanfFromFile(node *head)
{	
	char file[15];
	printf("输入待导入的文件名:");
	scanf("%s",file);

	FILE *fp;
	if((fp=fopen(file,"r"))==NULL)
	{
		printf("\n\t文件打开失败，按任意键退出\n");
		GetInteger();
		exit(0);
	}
	
	node *p=head;

	while(!feof(fp))
	{	
		node *end; 	
		end = (node *)malloc(sizeof(node));
		p->next=end;
		p=end;
		p->next=NULL;
	
		fscanf(fp,READ_FORMAT);
		
	}
		printf("\n\t信息导入成功\n");
		
		fclose(fp);

	void CheckNum(node *head);
	void InsertSort(node *head);
	CheckNum(head);
	InsertSort(head);

}

void ShowList(node *head)//带头结点的链表
{
        node *p=head->next;
        int i=0;
        printf (PRINT_TITLE);
        while(NULL!=p )//NULL!=p 不是NULL!=p->next
        {       i++;
                printf (PRINT_FORMAT);
                p=p->next;
        }
}

void FprintfToFile(node *head)
{
        char file[15];

        printf("\n输入要写入的文件名:");
        scanf("%s",file);

        FILE *fp;
        if((fp=fopen(file,"w+"))==NULL)
        {
                printf("\n\t文件创建失败\n");

                exit(0);
        }
        node *p=head->next;
        while(NULL!=p)
        {
                if(p->next==NULL)//不要最后一行的回车，这样的话导入该文件时就不会有末尾的乱码
                        fprintf(fp,"%s\t%s\t%s\t%s",p->stu.id,p->stu.name,p->stu.sex,p->stu.grade);
                else
                        fprintf(fp,WRITE_FORMAT);
                p=p->next;
        }
        fclose(fp);
        printf("\n\t 数据写入成功\n",file);//printf输出双引号要用转义字\"

}
node *ClearList(node *head)
{
        node *p=head->next;
        while(NULL!=p)
        {
                node *tp=p->next;
                free(p);
                p=tp;
        }
        return head->next=NULL;

}

int AddStu(node *head)
{
        node *p,*p2=head,*p3;
        p=(node *)malloc(sizeof(node));
        printf("依次输入学生的学号、姓名、性别和籍贯（用空格隔开）：\n");
        scanf("%s %s %s %s",p->stu.id,p->stu.name,p->stu.sex,p->stu.grade);

        int flag=0;
        while(NULL!=p2->next)
        {       /*找出第一个比新学生的学号大的位置，将新信息放在它前面*/
                if((flag=strcmp(p->stu.id,p2->next->stu.grade))<0)
                {
                        p3=p2->next;
                        p2->next=p;
                        p->next=p3;
                        break;
                }

                p2=p2->next;
        }

        /*如果新添加学生的学号比已有的都大，放置最末尾*/
        if(flag>0)
        {
                p2->next=p;
                p->next=NULL;
        }
        void CheckNum(node *head);
        CheckNum(head);

        printf("信息添加成功\n");
        printf("\t按任意数字键键返回\n");
        GetInteger();



        return 1;
}

int DeleteByNum(node *head)
{       char num[9];
        int flag=1;
        node *p=head,*p2;
        printf("输入要删除信息的学号：");
        scanf("%s",num);
        while(NULL!=p->next)
        {
                if((flag=strcmp(p->next->stu.id,num))==0)
                {
                        p2=p->next;
                        p->next=p->next->next;
                        free(p2);
                        printf("删除成功\n");
                        break;                 
                }
                p=p->next;
        }

        if(flag!=0)
                printf("你输入的学号不存在\n");
        printf("\t按任意数字键键返回\n");
        GetInteger();
        return 1;
}

int main()
{
	
    printf ("+---------------------------------------欢迎来到抽奖系统----------------------------------------------------+\n");
    printf ("+-----------------------------------------------------------------------------------------------------------+\n");
    printf ("|                                          抽奖信息简介                                                     |\n");
    printf ("|          为回馈大家消费，本APP开展一次面向学生的抽奖活动。只需输入个人姓名，性别，学号，                  |\n");
    printf ("|   					游戏规则如下                                                     |\n");
    printf ("|            本次抽奖设置三个奖项，一等奖电脑一台，二等奖手机一部，三等奖励100元			         |\n");
    printf ("|    本次抽奖您将会获得一个幸运数字，1到10为一等奖，11到20为二等奖，21到30为三等奖，剩下的数字为未中奖数字  |\n");
    printf ("+-----------------------------------------------------------------------------------------------------------+\n");
    printf ("+---------------------------------------------------------------------------------------------------------- +\n");
    printf ("+------------------------------------------------------------------------------------------------------------\n");
    printf ("                                           一等奖设置一人                                                    \n");
    printf ("                                           二等奖设置两人                                                    \n");
    printf ("                                           三等奖设置三人                                                    \n");
   
    lotterying();
    
        node *head;
        int i=0;
        head = (node *)malloc(sizeof(node));
        strcpy(head->stu.id," ");
        strcpy(head->stu.grade," ");
        strcpy(head->stu.name," ");
        strcpy(head->stu.sex," ");
        node *temp= (node *)malloc(sizeof(node));//保存查找结果的头结点

                FscanfFromFile(head);
        char charget;

        do
        {
                printf("\n----------------------------------------------\n");
                printf("\n[1]信息显示\n");
                printf("[2]信息查找\n");
                printf("[3]添加信息\n");
                printf("[4]删除信息\n");
                printf("[5]退出程序\n");

                do
                {
                charget=getchar();
                }

                while((charget!='1')&&(charget!='2')&&(charget!='3')&&(charget!='4')&&(charget!='5'));

                switch(charget)
                {
                case '1':       ShowList(head);
                                       printf("\n按任意数字键显示上层操作菜单\n");
                                        GetInteger();
                                        break;
                case '2':       if(0!=MySelect(head,temp))//查找结束不为空则进行下面的操作，为空则返回上层菜单
                                        {

                                                char charget2;
                                                do
                                                {
                                                        printf("\n[1]在此基础上继续查找\n");
                                                        printf("[2]将查找结果写入文件\n");
                                                        printf("[3]退出本次查找\n");


                                                        do
                                                        {
															charget2=GetInteger();
                                                        }
                                                        while((charget2!='1')&&(charget2!='2')&&(charget2!='3'));

                                                        switch(charget2)
                                                        {
                                                        case '1':       if(0==MySelect(temp,temp))
                                                                                {
                                                                                        printf("\n按任意数字键结束本次查找\n");
                                                                                        GetInteger();
                                                                                        charget2='3';
                                                                                }
                                                                                break;

                                                        case '2':       FprintfToFile(temp);
                                                                                charget2='3';//数据写入后，自动结束本次查找
                                                                                break;
                                                        case '3':       ClearList(temp);//结束查找，释放暂存查找结果的链表
																		break;


                                                        }//end switch，结束本次查找
                                                }
                                                while(charget2!='3');//如果charget2也用charget的话，在查找中按键3会直接退出程序
                                        }//end if
                                        break;
                case '3':       AddStu(head);break;
                case '4':       DeleteByNum(head);break;

                }//end switch，结束操作
        }
        while(charget!='5');
    return 0;


