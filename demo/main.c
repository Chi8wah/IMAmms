#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
//fflush(stdin);
typedef struct Info
{
    char name[50];          //��������
    char pass[20];          //��������
    char num[20];           //ѧ��
    char tel[20];           //�绰
    char qq[20];            //QQ��
    //���ź�:1 ����Ӳ����;2 �ƶ���������;3 ��Ϸ��;4 ��Ʋ�;5 ��Ʒ��;
    int bm;
    int sf;                 //���(0:��Ա;1:����)
}Info;

typedef struct LNode
{
    Info data;
    struct LNode *next;
}LNode,*LinkList;

LinkList Ima;

int GetInfo();      //ȡ��������
int Login();        //����
LNode *Search(char[50],int);      //��ѯ��Ա
char Menu();         //����˵�ҳ
int Create();       //������Ա
int Delete(LinkList);       //ɾ����Ա
int EditInfo();     //��Ա��Ϣ����
int SaveInfo();     //�汾������
void Print(LinkList);

int identity;       //Ȩ��(0:��Ա;1:����)

char loginname[50]="";
char managerid[]="guanli";      //����Աid
char managerpass[]="123456";     //����Ա����

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
            printf("\n�����뿪ϵͳ��");
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
    printf("������ѡ��ǰ����ĸ�Խ�����һ��\n");
    char Get;
    if(identity)
    {
        printf("i:��ѯ���޸ĳ�Ա��Ϣ\n");
        printf("c:���ӳ�Ա\n");
        printf("l:�˳���¼\n");
        printf("b:�뿪ϵͳ\n");
    }
    else
    {
        printf("i:��ѯ���޸ĳ�Ա��Ϣ\n");
        printf("l:�˳���¼\n");
        printf("b:�뿪ϵͳ\n");
    }
    printf("������:");
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
            printf("�����֤���������µ�½��\n");
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
            printf("�����֤���������µ�½��\n");
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
    if(g==1)                        //Ѱ������
    {
        while(p&&(strcmp(p->data.name,s)!=0))
        {
            p=p->next;
        }
    }
    else if(g==2)                   //Ѱ��ѧ��
    {
        while(p&&(strcmp(p->data.num,s)!=0))
        {
            p=p->next;
        }
    }
    else if(g==0)                   //Ѱ��ǰ׺�ڵ�
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
        printf("�밴����ʾ�����Ӧ��Ϣ(�س�����)!\n");
        LNode *s=(LNode*)malloc(sizeof(LNode));
        s->next=Ima->next;
        Ima->next=s;
        printf("����������:");fflush(stdin);scanf("%s",&s->data.name);
        printf("����������:");fflush(stdin);scanf("%s",&s->data.pass);
        printf("������ѧ��:");fflush(stdin);scanf("%s",&s->data.num);
        printf("������绰:");fflush(stdin);scanf("%s",&s->data.tel);
        printf("������QQ��:");fflush(stdin);scanf("%s",&s->data.qq);
        printf("�����벿�ź�:\n(1-����Ӳ����;2-�ƶ���������;3-��Ϸ��;4-��Ʋ�;5-��Ʒ��)\n");
        fflush(stdin);scanf("%d",&s->data.bm);
        printf("���������(0:��Ա;1:����): ");fflush(stdin);scanf("%d",&s->data.sf);getchar();
        (Ima->data.sf)++;
        printf("¼��ɹ�!\n�Ƿ����¼��?(Y/N): ");fflush(stdin);scanf("%c",&flag);getchar();
    }
    return 0;
}
int Delete(LinkList ss)
{

    LNode *p=Search(ss->data.name,0);  //Ѱ��ǰ׺�ڵ� //printf("\nP:%p\tP.next:%p",p,p->next);
    if(!(p||p->next)){return 0;}
    LNode *s=p->next;
    p->next=s->next;
    free(s);
    (Ima->data.sf)--;   //����-1
    return 1;
}
int EditInfo()
{

    int g,tempt;char ss[50]="",flag='N',temps[50]="";
EditBegin:system("cls");
    printf("��ѡ���ѯ��ʽ(����[1]/ѧ��[2]): ");fflush(stdin);scanf("%d",&g);getchar();
    if(g==1)
    {
        printf("����������ѯ����: ");fflush(stdin);scanf("%s",&ss);getchar();
    }
    else if(g==2)
    {
        printf("����������ѯѧ��: ");fflush(stdin);scanf("%s",&ss);getchar();
    }
    else
    {
        printf("Unknown Input!Press ENTER to try again!\n");
        fflush(stdin);getchar();
        goto EditBegin;
    }
    LNode *s=Search(ss,g);
    if(s==NULL){printf("���޴���!�����ص��˵�!");getchar();return 0;}
    Print(s);

    printf("�Ƿ�Գ�Ա��Ϣ�����޸�(Y/N): ");fflush(stdin);scanf("%c",&flag);getchar();
    if(flag=='N') return 0;

    if(identity==0)
    {
        if(strcmp(loginname,s->data.name)==0)
        {
            printf("������޸ĵ�������!���������������: ");
            fflush(stdin);scanf("%s",&s->data.pass);getchar();
            printf("�޸����!�����ص��˵�!");
            getchar();
            return 0;
        }
        else
        {
            printf("�޲���Ȩ��!�����ص��˵�ҳ!");
            getchar();
            return 0;
        }
    }

    flag=='N';
    printf("�Ƿ�ɾ���˳�Ա(Y/N):"); fflush(stdin);scanf("%c",&flag);getchar();
    if (flag=='Y')
    {
        if(Delete(s)==0) printf("ɾ��ʧ��!�����ص��˵�ҳ!");
        else printf("ɾ���ɹ�!�����ص��˵�ҳ!");
        getchar();
        return 0;
    }

    system("cls");
    printf("�ѽ����޸�״̬!�������ʾ�������!\n�������޸�����������9!\n");
    printf("(�����޸ĵĳ�Ա����Ϊ:%s)\n",s->data.name);
    printf("����������:"); fflush(stdin);scanf("%s",&temps); if(strcmp(temps,"9")!=0) {strcpy(s->data.name,temps);} strcpy(temps,"");getchar();
    printf("����������:"); fflush(stdin);scanf("%s",&temps); if(strcmp(temps,"9")!=0) {strcpy(s->data.pass,temps);} strcpy(temps,"");getchar();
    printf("������ѧ��:"); fflush(stdin);scanf("%s",&temps); if(strcmp(temps,"9")!=0) {strcpy(s->data.num,temps);} strcpy(temps,"");getchar();
    printf("������绰:"); fflush(stdin);scanf("%s",&temps); if(strcmp(temps,"9")!=0) {strcpy(s->data.tel,temps);} strcpy(temps,"");getchar();
    printf("������QQ��:"); fflush(stdin);scanf("%s",&temps); if(strcmp(temps,"9")!=0) {strcpy(s->data.qq,temps);} strcpy(temps,"");getchar();

    printf("�����벿�ź�:\n(1-����Ӳ����;2-�ƶ���������;3-��Ϸ��;4-��Ʋ�;5-��Ʒ��)\n");
    fflush(stdin);scanf("%d",&tempt);
    if((tempt>=1)&&(tempt<=5)) s->data.bm=tempt;
    else if(tempt!=9) printf("��������!�޸�ʧ��!");
    tempt=9;getchar();

    printf("���������(0:��Ա;1:����): ");
    fflush(stdin);scanf("%d",&tempt);
    if((tempt==0)||(tempt==1)) s->data.sf=tempt;
    else if(tempt!=9) printf("��������!�޸�ʧ��!");
    tempt=9;getchar();

    printf("�޸����!�����ص��˵�!");
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
        printf("����:\t");printf("%s\n",s->data.name);
        printf("����:\t");printf("%s\n",s->data.pass);
        printf("ѧ��:\t");printf("%s\n",s->data.num);
        printf("�绰:\t");printf("%s\n",s->data.tel);
        printf("QQ��:\t");printf("%s\n",s->data.qq);
        printf("���ź�:\t%d\n(1-����Ӳ����;2-�ƶ���������;3-��Ϸ��;4-��Ʋ�;5-��Ʒ��)\n",s->data.bm);
        printf("���:\t%d (0:��Ա;1:����)\n",s->data.sf);getchar();
}
