#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
//fflush(stdin);
typedef struct Info
{
    char name[50];          //登入姓名
    char pass[20];          //登入密码
    char num[20];           //学号
    char tel[20];           //电话
    char qq[20];            //QQ号
    //部门号:1 智能硬件部;2 移动互联网部;3 游戏部;4 设计部;5 产品部;
    int bm;
    int sf;                 //身份(0:部员;1:部长)
}Info;

typedef struct LNode
{
    Info data;
    struct LNode *next;
}LNode,*LinkList;

LinkList Ima;

int GetInfo();      //取本地数据
int Login();        //登入
LNode *Search(char[50],int);      //查询成员
char Menu();         //管理菜单页
int Create();       //创建成员
int Delete(LinkList);       //删除成员
int EditInfo();     //成员信息管理
int SaveInfo();     //存本地数据
void Print(LinkList);

int identity;       //权限(0:部员;1:部长)

char loginname[50]="";
char managerid[]="guanli";      //管理员id
char managerpass[]="123456";     //管理员密码

int main()
{
    Ima=(LinkList)malloc(sizeof(LNode));
    GetInfo();
    char choose;
logIn:system("cls");
    identity=Login();
Begin:system("cls");
    choose=Menu();
    switch(choose)
    {
        case 'c':
            if(identity==0)
            {
                printf("Unknown Input!Press ENTER to try again!\n");
                fflush(stdin);getchar();
                goto Begin;
                break;
            }
            Create();
            goto Begin;
            break;
        case 'i':
            EditInfo();
            goto Begin;
            break;
        case 'l':
            SaveInfo();
            goto logIn;
            break;
        case 'b':
            SaveInfo();
            printf("\n你已离开系统！");
            break;
        default:
            printf("Unknown Input!Press ENTER to try again!\n");
            fflush(stdin);getchar();
            goto Begin;
            break;
    }



    return 0;
}

char Menu()
{
    system("cls");
    printf("请输入选项前的字母以进入下一步\n");
    char Get;
    if(identity)
    {
        printf("i:查询或修改成员信息\n");
        printf("c:增加成员\n");
        printf("l:退出登录\n");
        printf("b:离开系统\n");
    }
    else
    {
        printf("i:查询或修改成员信息\n");
        printf("l:退出登录\n");
        printf("b:离开系统\n");
    }
    printf("请输入:");
    fflush(stdin);scanf("%c",&Get);
    getchar();
    return Get;
}

int Login()
{
    system("cls");
    LNode *p_l=(LinkList)malloc(sizeof(LNode));
    char id_l[50]="",pass_l[20]="";
    printf("Input your name here:");
    fflush(stdin);scanf("%s",&id_l);
    getchar();
    printf("Input your password here:");
    fflush(stdin);scanf("%s",&pass_l);
    getchar();p_l=NULL;
    if (strcmp(id_l,managerid) != 0)
    {
        p_l=Search(id_l,1);
        if ((p_l==NULL)||(strcmp(pass_l,p_l->data.pass) != 0))
        {
            printf("身份认证错误！请重新登陆！\n");
            getchar();
            return Login();
        }
        else
        {
            strcpy(loginname,p_l->data.name);
            return p_l->data.sf;
        }
    }
    else if (strcmp(pass_l,managerpass) == 0)
    {
        return 1;
    }
         else
         {
            printf("身份认证错误！请重新登陆！\n");
            getchar();
            return Login();
         }
    return Login();
}
int GetInfo()
{
    FILE *fp;

    if ((fp=fopen("imadata.txt","r"))==NULL)
    {fp=fopen("imadata.txt","w");}
/*
        fclose(fp);
        Ima=(LinkList)malloc(sizeof(LNode));
        Ima->next=NULL;
        Ima->data.sf=0;
        return 0;
    }
    else
    {
*/
        Ima=(LinkList)malloc(sizeof(LNode));
        strcpy(Ima->data.name,"Ima");
        Ima->data.sf=0;
        Ima->next=NULL;
        int len=0;
        fscanf(fp,"%d",&len);
        LNode *r=Ima;
        //printf("name:%s\tadress:%p\n",Ima->data.name,Ima);
        while((Ima->data.sf)<len)
        {
            LNode *s=(LNode*)malloc(sizeof(LNode));
            fscanf(fp,"%s %s %s %s %s %d %d",&s->data.name,&s->data.pass,&s->data.num,&s->data.tel,&s->data.qq,&s->data.bm,&s->data.sf);
            s->next=NULL;
            r->next=s;
            r=r->next;
            (Ima->data.sf)++;
            //printf("name:%s\tadress:%p\n",s->data.name,s);
        };
    //}
    fclose(fp);
    return 0;
}


LNode *Search(char s[50],int g)
{
    LNode* p=Ima;
    if(g==1)                        //寻找姓名
    {
        while(p&&(strcmp(p->data.name,s)!=0))
        {
            p=p->next;
        }
    }
    else if(g==2)                   //寻找学号
    {
        while(p&&(strcmp(p->data.num,s)!=0))
        {
            p=p->next;
        }
    }
    else if(g==0)                   //寻找前缀节点
    {
        while((p->next)&&(strcmp(p->next->data.name,s)!=0))
        {
            p=p->next;
        }
    }
    return p;
}

int Create()
{
    system("cls");

    char flag='Y';
    while(flag=='Y')
    {
        system("cls");
        printf("请按照提示输入对应信息(回车结束)!\n");
        LNode *s=(LNode*)malloc(sizeof(LNode));
        s->next=Ima->next;
        Ima->next=s;
        printf("请输入姓名:");fflush(stdin);scanf("%s",&s->data.name);
        printf("请输入密码:");fflush(stdin);scanf("%s",&s->data.pass);
        printf("请输入学号:");fflush(stdin);scanf("%s",&s->data.num);
        printf("请输入电话:");fflush(stdin);scanf("%s",&s->data.tel);
        printf("请输入QQ号:");fflush(stdin);scanf("%s",&s->data.qq);
        printf("请输入部门号:\n(1-智能硬件部;2-移动互联网部;3-游戏部;4-设计部;5-产品部)\n");
        fflush(stdin);scanf("%d",&s->data.bm);
        printf("请输入身份(0:部员;1:部长): ");fflush(stdin);scanf("%d",&s->data.sf);getchar();
        (Ima->data.sf)++;
        printf("录入成功!\n是否继续录入?(Y/N): ");fflush(stdin);scanf("%c",&flag);getchar();
    }
    return 0;
}
int Delete(LinkList ss)
{

    LNode *p=Search(ss->data.name,0);  //寻找前缀节点 //printf("\nP:%p\tP.next:%p",p,p->next);
    if(!(p||p->next)){return 0;}
    LNode *s=p->next;
    p->next=s->next;
    free(s);
    (Ima->data.sf)--;   //总数-1
    return 1;
}
int EditInfo()
{

    int g,tempt;char ss[50]="",flag='N',temps[50]="";
EditBegin:system("cls");
    printf("请选择查询方式(姓名[1]/学号[2]): ");fflush(stdin);scanf("%d",&g);getchar();
    if(g==1)
    {
        printf("请输入所查询姓名: ");fflush(stdin);scanf("%s",&ss);getchar();
    }
    else if(g==2)
    {
        printf("请输入所查询学号: ");fflush(stdin);scanf("%s",&ss);getchar();
    }
    else
    {
        printf("Unknown Input!Press ENTER to try again!\n");
        fflush(stdin);getchar();
        goto EditBegin;
    }
    LNode *s=Search(ss,g);
    if(s==NULL){printf("查无此人!即将回到菜单!");getchar();return 0;}
    Print(s);

    printf("是否对成员信息进行修改(Y/N): ");fflush(stdin);scanf("%c",&flag);getchar();
    if(flag=='N') return 0;

    if(identity==0)
    {
        if(strcmp(loginname,s->data.name)==0)
        {
            printf("你仅可修改登入密码!请输入你的新密码: ");
            fflush(stdin);scanf("%s",&s->data.pass);getchar();
            printf("修改完成!即将回到菜单!");
            getchar();
            return 0;
        }
        else
        {
            printf("无操作权限!即将回到菜单页!");
            getchar();
            return 0;
        }
    }

    flag=='N';
    printf("是否删除此成员(Y/N):"); fflush(stdin);scanf("%c",&flag);getchar();
    if (flag=='Y')
    {
        if(Delete(s)==0) printf("删除失败!即将回到菜单页!");
        else printf("删除成功!即将回到菜单页!");
        getchar();
        return 0;
    }

    system("cls");
    printf("已进入修改状态!请根据提示完成输入!\n若不作修改请输入数字9!\n");
    printf("(正在修改的成员姓名为:%s)\n",s->data.name);
    printf("请输入姓名:"); fflush(stdin);scanf("%s",&temps); if(strcmp(temps,"9")!=0) {strcpy(s->data.name,temps);} strcpy(temps,"");getchar();
    printf("请输入密码:"); fflush(stdin);scanf("%s",&temps); if(strcmp(temps,"9")!=0) {strcpy(s->data.pass,temps);} strcpy(temps,"");getchar();
    printf("请输入学号:"); fflush(stdin);scanf("%s",&temps); if(strcmp(temps,"9")!=0) {strcpy(s->data.num,temps);} strcpy(temps,"");getchar();
    printf("请输入电话:"); fflush(stdin);scanf("%s",&temps); if(strcmp(temps,"9")!=0) {strcpy(s->data.tel,temps);} strcpy(temps,"");getchar();
    printf("请输入QQ号:"); fflush(stdin);scanf("%s",&temps); if(strcmp(temps,"9")!=0) {strcpy(s->data.qq,temps);} strcpy(temps,"");getchar();

    printf("请输入部门号:\n(1-智能硬件部;2-移动互联网部;3-游戏部;4-设计部;5-产品部)\n");
    fflush(stdin);scanf("%d",&tempt);
    if((tempt>=1)&&(tempt<=5)) s->data.bm=tempt;
    else if(tempt!=9) printf("输入有误!修改失败!");
    tempt=9;getchar();

    printf("请输入身份(0:部员;1:部长): ");
    fflush(stdin);scanf("%d",&tempt);
    if((tempt==0)||(tempt==1)) s->data.sf=tempt;
    else if(tempt!=9) printf("输入有误!修改失败!");
    tempt=9;getchar();

    printf("修改完成!即将回到菜单!");
    getchar();
    return 0;
}
int SaveInfo()
{
    int len;
    FILE *fp=fopen("imadata.txt","w");
    LNode *s=Ima;
    len=Ima->data.sf;
    fprintf(fp,"%d\n",len);
    while((s->next)!=NULL)
    {
        s=s->next;
        fprintf(fp,"%s %s %s %s %s %d %d\n",s->data.name,s->data.pass,s->data.num,s->data.tel,s->data.qq,s->data.bm,s->data.sf);
    }
    fclose(fp);
    return 0;
}

void Print(LinkList s)
{
        printf("姓名:\t");printf("%s\n",s->data.name);
        printf("密码:\t");printf("%s\n",s->data.pass);
        printf("学号:\t");printf("%s\n",s->data.num);
        printf("电话:\t");printf("%s\n",s->data.tel);
        printf("QQ号:\t");printf("%s\n",s->data.qq);
        printf("部门号:\t%d\n(1-智能硬件部;2-移动互联网部;3-游戏部;4-设计部;5-产品部)\n",s->data.bm);
        printf("身份:\t%d (0:部员;1:部长)\n",s->data.sf);getchar();
}
