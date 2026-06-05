#include <iostream>
#include <cstring>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const int MAXN = 100000 + 5;
const int BUF  = 1 << 20;

unsigned int a[MAXN];

char ibuf[BUF];
char obuf[BUF];

int ip=0, il=0;
int op=0;

streambuf* IN;
streambuf* OUT;

inline char gc()
{
    if(ip>=il)
    {
        il=IN->sgetn(ibuf,BUF);
        ip=0;

        if(!il)
            return EOF;
    }

    return ibuf[ip++];
}

inline bool readInt(int &x)
{
    char c=gc();

    while(c<=' '&&c!=EOF)
        c=gc();

    if(c==EOF)
        return false;

    bool neg=false;

    if(c=='-')
    {
        neg=true;
        c=gc();
    }

    x=0;

    while((unsigned)(c-'0')<10u)
    {
        x=x*10+(c-'0');
        c=gc();
    }

    if(neg)
        x=-x;

    return true;
}

inline void pc(char c)
{
    obuf[op++]=c;

    if(op==BUF)
    {
        OUT->sputn(obuf,BUF);
        op=0;
    }
}

inline void writeInt(int x)
{
    unsigned int y;

    if(x<0)
    {
        pc('-');
        y=-(unsigned int)x;
    }
    else
        y=(unsigned int)x;

    char s[12];
    int p=0;

    do
    {
        s[p++]=char(y%10+'0');
        y/=10;
    }
    while(y);

    while(p)
        pc(s[--p]);
}

inline void flush()
{
    if(op)
        OUT->sputn(obuf,op);
}

inline void insertion(unsigned int* arr,int l,int r)
{
    for(int i=l+1;i<r;i++)
    {
        unsigned int key=arr[i];
        int j=i-1;

        while(j>=l&&arr[j]>key)
        {
            arr[j+1]=arr[j];
            --j;
        }

        arr[j+1]=key;
    }
}

void afs(unsigned int* arr,int l,int r,int shift)
{
    if(r-l<=64)
    {
        insertion(arr,l,r);
        return;
    }

    if(shift<0)
        return;

    int cnt[256]={0};

    int i=l;

    for(;i+3<r;i+=4)
    {
        cnt[(arr[i]>>shift)&255]++;
        cnt[(arr[i+1]>>shift)&255]++;
        cnt[(arr[i+2]>>shift)&255]++;
        cnt[(arr[i+3]>>shift)&255]++;
    }

    for(;i<r;i++)
        cnt[(arr[i]>>shift)&255]++;

    int begin[256];
    int next[256];

    begin[0]=l;

    for(int k=1;k<256;k++)
        begin[k]=begin[k-1]+cnt[k-1];

    for(int k=0;k<256;k++)
        next[k]=begin[k];

    for(int b=0;b<256;b++)
    {
        int end=begin[b]+cnt[b];

        while(next[b]<end)
        {
            unsigned int v=arr[next[b]];

            int d=(v>>shift)&255;

            while(d!=b)
            {
                unsigned int tmp=arr[next[d]];

                arr[next[d]]=v;

                next[d]++;

                v=tmp;

                d=(v>>shift)&255;
            }

            arr[next[b]]=v;

            next[b]++;
        }
    }

    if(shift==0)
        return;

    for(int b=0;b<256;b++)
    {
        if(cnt[b]>1)
        {
            afs(
                arr,
                begin[b],
                begin[b]+cnt[b],
                shift-8
            );
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    IN=cin.rdbuf();
    OUT=cout.rdbuf();

    int n;

    if(!readInt(n))
        return 0;

    for(int i=0;i<n;i++)
    {
        int x;

        readInt(x);

        a[i]=((unsigned)x)^0x80000000u;
    }

    afs(a,0,n,24);

    writeInt(n);
    pc('\n');

    for(int i=0;i<n;i++)
    {
        writeInt((int)(a[i]^0x80000000u));
        pc('\n');
    }

    flush();
}
