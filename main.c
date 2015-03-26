#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    int inf,bal;
    struct nod *left,*right;
};

//void stanga(struct nod **p)
#define min(x,y) (((x) < (y)) ? (x) : (y))
#define max(x,y) (((x)>(y)) ? (x) : (y))

void dreaptadreapta(struct nod **p)
{
    struct nod *p2=*p;
    struct nod *aux;
    aux=p2->left;
    p2->left=aux->right;
    aux->right=p2;
    p2->bal=p2->bal+(1-min(aux->bal,0));
    aux->bal=aux->bal+(1+min(p2->bal,0));
    *p=aux;
}

void stangastanga(struct nod **p)
{
    struct nod *p2=*p;
    struct nod *aux;
    aux=p2->right;
    p2->right=aux->left;
    aux->left=p2;
    p2->bal=p2->bal-(1+max(aux->bal,0));
    aux->bal=aux->bal-(1-min(p2->bal,0));
    *p=aux;
}

void stangadreapta(struct nod **p)
{
    struct nod *p2=*p;
    stangastanga(&p2->left);
    dreaptadreapta(p);
}

void dreaptastanga(struct nod **p)
{
    struct nod *p2=*p;
    dreaptadreapta(&p2->right);
    stangastanga(p);
}

void echilibreaza(struct nod **p)
{
    struct nod *q=*p;
    if (q->bal==-2) {
        if (q->left!=NULL && q->left->bal==1) stangadreapta(p);
            else dreaptadreapta(p);
    }
        else if (q->bal==2) {
            if (q->right!=NULL && q->right->bal==-1) {
                dreaptastanga(p);
            }
            else stangastanga(p);
        }
}

int inserare(int a,struct nod **p)
{
    struct nod *q=*p;
    if (q==NULL) {
        struct nod *t=(struct nod*)malloc(sizeof(struct nod));
        t->inf=a;
        t->left=NULL;
        t->right=NULL;
        t->bal=0;
        *p=t;
        return 0;
    }
    if (q->inf==a) return 1;
    if (q->inf>a) {
        if (inserare(a,&q->left)==0) q->bal=q->bal-1;
            else return 1;
    }
        else {
            if (inserare(a,&q->right)==0) q->bal=q->bal+1;
                else return 1;
        }
    if (q->bal==0) return 1;
        else if ((q->bal==1) || (q->bal==-1)) return 0;
            else {
                echilibreaza(p);
                return 1;
            }
}

int cautare(int a,struct nod *p)
{
    if (a==p->inf) return 1;
        else
        {
            if (a>p->inf) {
                    if (p->right!=NULL) cautare(a,p->right);
                        else return 0;
            }
                else {
                        if (p->left!=NULL) cautare(a,p->left);
                            else return 0;
                }
        }

}

void rsd(struct nod *p)
{
    if (p!=NULL) {
        printf("[%d %d] ",p->inf,p->bal);
        rsd(p->left);
        rsd(p->right);
    }
}

void srd(struct nod *p)
{
    if (p!=NULL) {
        srd(p->left);
        printf("%d ",p->inf);
        srd(p->right);
    }
}

int maxim(struct nod *p)
{
    while (p->right!=NULL) p=p->right;
    return p->inf;
}

struct nod *minim(struct nod *p)
{
    while (p->left!=NULL) p=p->left;
    return p;
}

int sterg(int a,struct nod **p)
{
    struct nod *y,*p2=*p;
    if (p2==NULL) return 1;
    if (p2->inf>a) {
        if (sterg(a,&p2->left)==0) p2->bal=p2->bal+1;
            else return 1;
    }
        else if (p2->inf<a) {
            if (sterg(a,&p2->right)==0) p2->bal=p2->bal-1;
                else return 1;
        }
            else {
                if (p2->left==NULL || p2->right==NULL) {
                if (p2->left != NULL) {
                    p2->inf=p2->left->inf;
                    p2->left=NULL;
                    p2->bal=p2->bal+1;
                    return 0;
                }
                    else if (p2->right !=NULL) {
                        p2->inf=p2->right->inf;
                        p2->right=NULL;
                        p2->bal=p2->bal-1;
                        return 0;
                    }
                    else {
                    *p=NULL;
                    return 0;
                    }
                }
                else {
                    y=minim(p2->right);
                    p2->inf=y->inf;
                    if (sterg(y->inf,&p2->right)==0) p2->bal=p2->bal-1;
                    else return 1;
                }
            }
        if (p2->bal==2 ||p2->bal==-2) echilibreaza(p);
        if (p2->bal==0) return 0;
            else return 1;
}

int main()
{
    struct nod *p=NULL;
    int opt,x;
    do {
        printf("1.Inserare nod\n2.Cautare\n3.Maxim\n4.Sterge\n5.Afisare\n6.Afisare RSD");scanf("%d",&opt);
        switch (opt) {
        case 1:
            printf("x=");scanf("%d",&x);
            inserare(x,&p);
            break;
        case 2:
            printf("x=");scanf("%d",&x);
            printf("%d\n",cautare(x,p));
            break;
        case 3:
            printf("%d\n",maxim(p));
            break;
        case 4:
            printf("x=");scanf("%d",&x);
            sterg(x,&p);
            break;
        case 5:
            srd(p);
            printf("\n");
            break;
        case 6:
            rsd(p);
            printf("\n");
            break;
        default:break;
        }
    }while (opt>0 && opt<7);
    return 0;
}
