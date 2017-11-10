#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<string>
using namespace std;
#define INF 0x3f3f3f3f
typedef long long ll;
const double eps=1e-6;
const int MAXN = 1e6+10;

struct trie
{
    string str;
    int cnum;
    int bnum;
    bool isbook;
    trie * nextc[33];
    trie * nextb[33];
    trie()
    {
        cnum=0;
        bnum=0;
        memset(nextb,0,sizeof(nextb));
        memset(nextc,0,sizeof(nextc));
        isbook=false;
    }

};

inline trie * newnode()
{
    trie*t = new trie();
//    memset(t,0,sizeof(trie));
    return t;
}
void insert(trie * s,char x[])
{
    int len=strlen(x);
    trie *t;
    string temp("");
    temp.clear();
    for(int i=0;i<len;i++)
    {
        if(x[i]=='/')
        {
            bool ok=false;
            for(int j=0;j<s->cnum;j++)
            {
                if(s->nextc[j]->str==temp)
                {
                    s=s->nextc[j];
                    ok=true;
                    break;
                }
            }
            if(!ok)
            {
                t=newnode();
                s->nextc[s->cnum++]=t;
                s=t;
                t->str=temp;
            }
            temp.clear();
        }
        else
        {
            temp.append(1,x[i]);
        }
    }
    bool ok=false;
    for(int j=0;j<s->bnum;j++)
    {
        if(s->nextb[j]->str==temp)
        {
            s=s->nextb[j];
            ok=true;
            break;
        }
    }
    if(!ok)
    {
        t=newnode();
        s->nextb[s->bnum++]=t;
        s=t;
        t->str=temp;
        t->isbook=true;
    }
}

void print(trie *s,int cnt)
{
    if(s->isbook)
    {
        for(int i=1;i<=4*cnt;i++)
            printf("%c",' ');
        cout<<s->str<<endl;
    }
    else
    {
        if(cnt!=-1)
        {
            for(int i=1;i<=4*cnt;i++)
                printf("%c",' ');
            cout<<s->str<<endl;
        }
        for(int i=0;i<s->cnum;i++)
        {
            print(s->nextc[i],cnt+1);
        }
        for(int i=0;i<s->bnum;i++)
        {
            print(s->nextb[i],cnt+1);
        }
    }
}

void deltrie(trie * s)
{
    int i;
    for(i=0; i < 33 ; i++)
    {
        if( s->nextb[i] )  deltrie(s->nextb[i]);
        if( s->nextc[i] )  deltrie(s->nextc[i]);
    }
    free(s);
    s=NULL;
}

trie *thead;

char s[110];
char ss[33][110];

int cmp(const void * a,const void *b)
{
    return strcmp((char *)a,(char *)b);
}
int main()
{
	freopen("HihoCoder1383.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
    int icase=1;
    while(gets(s))
    {
    	// cout<<s<<endl;
        int num=0;
        while(strcmp(s,"0")!=0)
        {
            num++;
            for(int i=0;i<int(strlen(s));i++)
            {
                ss[num][i]=s[i];
                if(ss[num][i]==' ')
                    ss[num][i]=']';
            }
            gets(s);
        }
        qsort(ss+1,num,sizeof(ss[0]),cmp);
        for(int i=1;i<=num;i++)
            for(int j=0;j<int(strlen(ss[i]));j++)
                if(ss[i][j]==']')
                    ss[i][j]=' ';
        thead=newnode();
        for(int i=1;i<=num;i++)
            insert(thead,ss[i]);
        printf("Case %d:\n",icase++);
        print(thead,-1);
        deltrie(thead);
    }
    return 0;
}