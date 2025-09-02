# Shortest path

## 题目描述

在一个平面内有 $N$ 个点，其中的 $N-1$ 个点在一条直线上，另一个点不在这条直线上，现在需要从点 $K$ 出发，遍历所有的点 。每次可以选择任意两点间的直线移动，可以重复经过这些点，求最小的移动路径 。

## 样例 #1

### 输入

```
5 2
0 0
-1 1
2 -2
0 1
-2 2```

### 输出

```
7.478709```

# 题解

## 作者：EnofTaiPeople (赞：5)

既然这是一个平面几何贪心题，我们考虑分类讨论。

如果起点在直线外，那么它必须要分别到达直线端点，当它先到达直线的某一端时，直接沿直线走到另一端一定是最优策略，此时中间的点都被经过，于是只需考虑先走到那一端即可。

否则，起点在直线上。

从刚才的情况，我们发现，一旦到达直线外的点，就只有直线端点会对答案造成影响。

换言之，到达直线外的点之前，只有到达直线端点会对答案造成影响。

枚举会先到达哪个端点，但是，有可能先往中部走在到达这个端点更优。

事实上，我们需要枚举往中部走到的最远的点，也有可能先走到端点，再往中部走，在走出直线，容易发现这些计算都不复杂，除了中部点枚举之外都是 $O(1)$ 的。

走到直线外之后问题就变成了最初的问题，依旧可以 $O(1)$ 计算。

当然可能先把直线走完再走出去，但这些细节是平凡的：
```cpp
ll k2(ll x){return x*x;}
struct dat{
    ll x,y;
    dat operator-(const dat &z)
    const{return{x-z.x,y-z.y};}
    void rd(){cin>>x>>y;}
    bool operator<(const dat &z)
    const{return x==z.x?y<z.y:x<z.x;}
    ll operator*(const dat &z)
    const{return x*z.y-y*z.x;}
    ld operator/(const dat &z)
    const{return sqrtl(k2(x-z.x)+k2(y-z.y));}
}a[N];
int n,m,K,b[N],bt;
ld ans,now;
int main(){
    ios::sync_with_stdio(false);
    int i,j,k,l,r,x,y,z;
    cin>>n>>K;
    for(x=1;x<=n;++x)a[x].rd();
    if(K!=1)swap(a[1],a[K]);
    for(i=2;i<n;++i)if((a[i]-a[1])*(a[n]-a[1]))b[++bt]=i;
    if(bt){
        if(bt==1)swap(a[b[1]],a[n]);
        else{
            if((a[b[1]]-a[1])*(a[b[2]]-a[1])){
                sort(a+2,a+n+1);
                printf("%.12Lf\n",min(a[1]/a[2],a[1]/a[n])+a[2]/a[n]);
                return 0;
            }
        }
    }
    for(k=K=1;k<n;++k)if(a[k]<a[1])++K;
    sort(a+1,a+n);
    ans=min(a[1]/a[n],a[n-1]/a[n])+a[1]/a[n-1]+a[K]/a[n];
    for(k=K;k<n;++k){
        now=min(a[K]/a[1]+a[k]/a[n],a[K]/a[k]+a[1]/a[n])+a[1]/a[k];
        if(k+1<n)now+=min(a[n]/a[k+1],a[n]/a[n-1])+a[k+1]/a[n-1];
        ans=min(ans,now);
    }
    K=n-K,reverse(a+1,a+n);
    for(k=K;k<n;++k){
        now=min(a[K]/a[1]+a[k]/a[n],a[K]/a[k]+a[1]/a[n])+a[1]/a[k];
        if(k+1<n)now+=min(a[n]/a[k+1],a[n]/a[n-1])+a[k+1]/a[n-1];
        ans=min(ans,now);
    }
    printf("%.12Lf\n",ans);
    return 0;
}
```

---

## 作者：yzh_Error404 (赞：0)

题目给定有 $n-1$ 个点在同一直线上，所以第一步肯定是将这 $n-1$ 个点找出来，这个判相邻三个点的斜率即可，为了方便，我们可以将不在直线上的那个点（下面称作额外点）放在最后的位置，然后将前面的所有数按照 $x$ 排序。

简单思考，如果没有额外点，我们显然只会在这条直线上走动，在有额外点的情况下，也不会多次经过这个额外点（走额外点的长度一定会比直接走的长度要长）。

还有，当总长度最短的时候，走过的路径一定不会有无意义的往返（显然不优）。

对于 $k$ 的取值，有两种情况：

1. 点 $k$ 是额外点，那么直接走到线段一端端点，再走过整个线段即可。

2. 点 $k$ 不是额外点，这时又分两种情况：
	1. 在这个线段上的每条边都经过，也就是先走到线段一端，走过整条线段，最后走到额外点上。
    2. 枚举一条边不经过，则当前的线段分为经过额外点之前走和经过额外点之后走。
    
最后答案取所有情况的最小值即可。

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
const double eps=1e-9;
struct node
{
    double x,y;
}e[MAXN],s;
int n,k;
inline bool comp(node a,node b)
{
    return (a.x==b.x)&&(a.y==b.y);
}
inline bool cmp(node a,node b)
{
    if(a.x==b.x)return a.y<b.y;
    return a.x<b.x;
}
inline double dist(node a,node b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline bool check(node x,node y,node z)
{
	return fabs((y.x-x.x)*(z.y-x.y)-(z.x-x.x)*(y.y-x.y))<eps;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(register int i=1;i<=n;i++)
        scanf("%lf%lf",&e[i].x,&e[i].y);
    if(n==3)
    {
        double len=dist(e[1],e[2])+dist(e[2],e[3])+dist(e[1],e[3]);
        len-=max(dist(e[1],e[2]),max(dist(e[2],e[3]),dist(e[1],e[3])));
        printf("%.6lf",len);
        return 0;
    }
    s=e[k];
    if(check(e[1],e[2],e[3]))for(register int i=4;i<=n;i++)if(!check(e[1],e[2],e[i])){swap(e[i],e[n]);break;}
    else
    {
        if(check(e[1],e[2],e[4]))swap(e[3],e[n]);
        else if(check(e[1],e[3],e[4]))swap(e[2],e[n]);
        else swap(e[1],e[n]);
    }
    sort(e+1,e+n,cmp);
    for(register int i=1;i<=n;i++)
        if(comp(e[i],s))k=i;
    if(n==k){printf("%.8lf",min(dist(e[n],e[1]),dist(e[n],e[n-1]))+dist(e[1],e[n-1]));return 0;}
    double ans=1e18 ;
    for(register int i=1;i<n-1;i++)
    {
        node a,b,c,d;
        if(i>=k)a=e[i],b=e[i+1],c=e[1],d=e[n-1];
        else a=e[i+1],b=e[i],c=e[n-1],d=e[1];
        ans=min(ans,min(dist(e[k],a)+dist(a,c)+dist(c,e[n])+dist(e[n],b)+dist(b,d),\
                        dist(e[k],c)+dist(c,a)+dist(a,e[n])+dist(e[n],b)+dist(b,d)));
    }
    ans=min(ans,dist(e[k],e[1])+dist(e[1],e[n-1])+dist(e[n-1],e[n]));
    ans=min(ans,dist(e[k],e[n-1])+dist(e[n-1],e[1])+dist(e[1],e[n]));
    printf("%.8lf",ans);
    return 0;
}
```

---

## 作者：Z1qqurat (赞：0)

抽象分讨题。感觉比分讨更抽象的就是这题 cin 会 TLE 改成 scanf 就过了，而且问题是复杂度瓶颈根本不在输入输出，真是活久见。出题人还是耗子尾汁。

首先怎么把这条直线找出来？先暴力 check 前 $4$ 个点，把孤点放到 $a_n$ 的位置上，保证 $a_1,a_2$ 在直线上；剩下的点都依次和 $a_1,a_2$ check，如果不在一条直线上就说明这个点是孤点，扔到 $a_n$ 去。那么现在 $a_{1\sim n-1}$ 就是在同一条直线上的了。

然后考虑如果起点 $s$ 就是孤立点，那么恰好只有这一种情况（蓝色的路径或者红色的路径）：

![p1](https://pic.imgdb.cn/item/65d84d829f345e8d03dd40c0.jpg)

为什么一定会先从孤点 $p$ 到直线上的一个端点呢？比如像图上红色的路径，由于三角形两边之和大于第三边，肯定不优。

否则就是 $s$ 在直线上的情况。最优的肯定是尽量在直线上走，所以我们只会恰好到达孤点 $p$ 一次。假如我们现在从 $s$ 到达了直线上某一端点，然后就走向 $p$，接下来 $p$ 要走回直线以完成没有被访问的部分，可以发现这就是等价于于 $s=p$ 的一个子问题了：

![p2](https://pic.imgdb.cn/item/65d84d299f345e8d03dc3ef5.jpg)

但是不一定就得直接从 $s$ 走到某一端点啊！可能先从 $s$ 走到一个位置，然后再拐回端点仍然更优的。所以我们需要枚举一个断点 $i$，考虑直线上 $\le i$ 的节点都会在路径到达 $p$ 之前被访问，$>i$ 的节点会在路径到达 $p$ 之后被访问（当然，还要讨论 $i$ 和 $s$ 的位置关系才能确定具体的贡献）。

![p3](https://pic.imgdb.cn/item/65d84d299f345e8d03dc3f55.jpg)

举例，比如 $i>s$，那么我们相当于有两种走 $p$ 之前路径的方式：$s\to i,i\to 1,1\to p$，$s\to 1,1\to i,i\to p$，然而右边的子问题走法都是 $p\to i+1,i+1\to n-1$ 或者 $p\to n-1,n-1\to i+1$。直接分情况讨论，所有的取 $\min$ 即可。容易发现还需要特判 $i=1,n-1$ 的情况，这时候分别把 $i-1/i+1$ 涉及到的线段长度看作 $0$ 就行啦。复杂度瓶颈在于对直线上点的排序，$\mathcal{O}(n\log n)$。

[Submission.](https://codeforces.com/contest/1599/submission/247840671)

---

