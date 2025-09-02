# MloVtry的idea

## 题目背景

点击～


## 题目描述

MloVtry是一个脑洞很大的人，它总会想出一些奇奇怪怪的idea。

可问题是，MloVtry作为一个蒟蒻，很多时候都没办法解决自己提出的问题，所以MloVtry想出一套题的梦想一直被搁置。

不过好在MloVtry有一些神犇朋友，他们强的没边，所以MloVtry一有机会就会向这些dalao们请教。

现在MloVtry有n个idea，这n个idea在MloVtry二维的大脑里排成一列，每一个idea都有一个难度值，用a[i]表示，当然难度值越大越困难。

MloVtry准备与q个神犇进行交♂易，但是MloVtry不想问一些过于简单的idea来降自己的B格，又不好意思用太难的、无法解决的idea来伤害自己与神犇之间的感情，所以它每次都会挑idea序列中的第k简单的idea来向神犇询问（也就是难度值第k小的那个idea）。

MloVtry的脑子有坑，但是没关系，这个坑会反而会帮助MloVtry思考，不过这样数列的a[i]就会更新，具体的，设坑在第j个idea上，那么a[i]=a[i]-zz(i<=j);a[i]=i+a[i]-j(i>j)。

如果仅仅如此MloVtry也不会感到迷茫，但关键的是这个坑还会不定时的跳跃，这就让MloVtry手足无措了---它不知道这个时候要问哪个问题了。

现在MloVtry会给出你---它最好的朋友一些询问---一些二元组（at，k），表示脑洞位于at，且它想询问第k简单的idea，请你告诉MloVtry这个idea难度是多少。


## 说明/提示

各个值保证在int范围内。

对于100%的数据，n,q<=6w。

对于40%的数据，n,q<=1000。

PS.可能有重复，例如

1 1 1 1 1 0

此时第1大、第2大....第5大的值都是1，第6大的值是0


## 样例 #1

### 输入

```
13 12 56
10100 12208 11766 11872 11336 10815 10710 11872 11536 11988 10100 10908 10815 
11 13
1 3
3 10
1 7
8 4
7 11
11 4
5 2
13 11
13 6
3 11
11 10```

### 输出

```
10044
11932
10918
11280
10044
10759
10827
11874
12152
10759
10044
10713```

# 题解

## 作者：wangif424 (赞：1)

# P4855题解

## 思路

这道题乍一看非常不可做，要实现区间加一个数，区间加等差数列和区间第 $k$ 小。

不过手玩样例后可以发现每次查询中对 $a$ 产生的变化仅在当次查询中生效。

而且因为 $zz$ 给定，所以对于所有查询中 $i\le j$ 的部分变化后的量都相同，于是可以维护一个数组 $a_i-zz$。

因此，不难想到分两部分处理。

再思考 $i\gt j$ 的部分如何处理，尝试找通性，$a_i+i-j_1$ 和 $a_i+i-j_2$ 中，仅有每次的 $j$ 不同，但在单个询问中固定，于是可以再维护一个数组 $a_i+i$。

## 做法

由于要区间第 $k$ 小，且题面中未明确值域，所以使用主席树解决此题。

用两棵主席树分别维护 $a_i-zz$ 和 $a_i+i$。

对于每次查询，由于不便于（或者我太蒟）直接查询第 $k$ 小，于是改为二分查找。

二分一个最小在当前的 $a$ 中小于等于自己的数的个数大于等于 $k$ 的数就是答案。

小于等于 $x$ 的数的个数可以分两部分求，为 $x$ 在 $a_i-zz,i\le j$ 中的最大排名，和 $x+j$ 在 $a_i+i,i\gt j$ 中的最大排名的和。

## AC代码
```cpp
#include<bits/stdc++.h>
#define R(x) x=read()
using namespace std;
char pbuf[1<<20], *pp=pbuf;
void swap(int &a,int &b){a^=b^=a^=b;}
inline void push(const char &c){if(pp - pbuf == 1<<20)fwrite(pbuf, 1, 1<<20, stdout),pp = pbuf;*pp++ = c;}
class io{public:~io(){fwrite(pbuf, 1, pp - pbuf, stdout);}}_;
inline void write(int x) {
    if (x<0)x=-x,push('-');
    int sta[35],top=0;
    do{sta[top++]=x%10,x/=10;}while (x);
    while(top)push(sta[--top]^'0');
}
#ifndef LOCAL
    char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
    #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
int n,q,zz;
#define N 60010
int a[N];
struct node{
    int ls,rs,s;
}t[N<<6];
int siz;
int rt[N],r2[N];
void update(int u,int v,int l,int r,int pos){
    t[v].s=t[u].s+1;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(!t[u].ls)t[u].ls=++siz;
    if(!t[u].ls)t[u].rs=++siz;
    t[v].ls=t[u].ls;
    t[v].rs=t[u].rs;
    if(pos<=mid){
        t[v].ls=++siz;
        update(t[u].ls,t[v].ls,l,mid,pos);
    }
    else{
        t[v].rs=++siz;
        update(t[u].rs,t[v].rs,mid+1,r,pos);
    }
}
int query(int u,int v,int l,int r,int x){
    if(l==r)return t[v].s-t[u].s;
    int mid=(l+r)>>1;
    if(x<=mid)return query(t[u].ls,t[v].ls,l,mid,x);
    else return t[t[v].ls].s-t[t[u].ls].s+query(t[u].rs,t[v].rs,mid+1,r,x);
}
int ls;
signed main(){
    R(n);R(q);R(zz);
    for(int i=1;i<=n;i++)R(a[i]);
    rt[0]=++siz;
    r2[0]=++siz;
    for(int i=1;i<=n;i++){
        rt[i]=++siz;
        r2[i]=++siz;
        update(rt[i-1],rt[i],-1e9,1e9,a[i]-zz);
        update(r2[i-1],r2[i],-1e9,1e9,a[i]+i);
    }
    while(q--){
        int R(j),R(k);
        j=(j^ls)%n+1;
        k=(k^ls)%n+1;
        int l=-1e9,r=1e9;
        while(l<r){
            int mid=(l+r)>>1;
            if(query(rt[0],rt[j],-1e9,1e9,mid)+query(r2[j],r2[n],-1e9,1e9,mid+j)>=k)r=mid;
            else l=mid+1;
        }
        // for(int i=1;i<=n;i++){
        //     if(i<=j)write(a[i]-zz);
        //     else write(a[i]-j+i);
        //     push(' ');
        // }
        // push('\n');
        // int x=11932;
        // write(query(rt[0],rt[j],-1e9,1e9,x));write(query(r2[j],r2[n],-1e9,1e9,x+j));push('\n');
        // write(j);push(' ');
        // write(k);push('|');
        write(l);
        // push(' ');
        // write(query(rt[0],rt[j],-1e9,1e9,l));write(query(r2[j],r2[n],-1e9,1e9,l+j));
        push('\n');
        ls=l>0?l:-l;
    }
    return 0;
}
```

---

