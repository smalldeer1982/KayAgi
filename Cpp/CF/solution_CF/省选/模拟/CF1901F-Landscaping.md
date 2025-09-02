# Landscaping

## 题目描述

You are appointed to a very important task: you are in charge of flattening one specific road.

The road can be represented as a polygonal line starting at $ (0, 0) $ , ending at $ (n - 1, 0) $ and consisting of $ n $ vertices (including starting and ending points). The coordinates of the $ i $ -th vertex of the polyline are $ (i, a_i) $ .

"Flattening" road is equivalent to choosing some line segment from $ (0, y_0) $ to $ (n - 1, y_1) $ such that all points of the polyline are below the chosen segment (or on the same height). Values $ y_0 $ and $ y_1 $ may be real.

You can imagine that the road has some dips and pits, and you start pouring pavement onto it until you make the road flat. Points $ 0 $ and $ n - 1 $ have infinitely high walls, so pavement doesn't fall out of segment $ [0, n - 1] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1901F/8839610379cc44772317fd4bbd1b705c5e309085.png)The cost of flattening the road is equal to the area between the chosen segment and the polyline. You want to minimize the cost, that's why the flattened road is not necessary horizontal.

But there is a problem: your data may be too old, so you sent a person to measure new heights. The person goes from $ 0 $ to $ n - 1 $ and sends you new heights $ b_i $ of each vertex $ i $ of the polyline.

Since measuring new heights may take a while, and you don't know when you'll be asked, calculate the minimum cost (and corresponding $ y_0 $ and $ y_1 $ ) to flatten the road after each new height $ b_i $ you get.

## 说明/提示

The first answer in the first example is shown on the picture above.

You can achieve the second answer with the following "best segment":

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1901F/da2ddd3dbe1ecc31494d5c6683d2fcb299f41685.png)You can achieve the third answer using the following "best segment":

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1901F/e8054cd29668ffb627496e6942c60799596229a1.png)You can achieve the fourth answer with the "best segment" shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1901F/af61ec48154d7b6613f3e5ddb4a7228c4cf5dd30.png)

## 样例 #1

### 输入

```
5
0 5 1 3 0
0 1 3 2 0```

### 输出

```
8.000000000000 4.000000000000 6.000000000000 6.000000000000 6.000000000000```

## 样例 #2

### 输入

```
6
0 4 1 3 3 0
0 1 4 0 1 0```

### 输出

```
7.000000000000 5.000000000000 7.500000000000 7.500000000000 6.666666666667 6.666666666667```

# 题解

## 作者：EnofTaiPeople (赞：12)

首先题意中的 $y_0+y_1$ 提示了我们当 $y_0+y_1$ 最小时，花费最小。

而 $y_0+y_1$ 最小又等价于该直线在 $m=\dfrac{n-1}2$ 处最小。

容易发现直线一定经过两个点（否则可以通过旋转使答案更优）且一定不会经过下凸的点（否则不符合题意），所以可以建出上凸壳，答案就是凸壳的所有边中在 $m$ 处最小的那一条。

画一下图会发现这条边所对应的**线段**一定会经过 $m$，而这样的边最多有两条，而有两条时它们同为最优解。

事实上，如果默认取靠左的边，那么两个端点的横坐标 $l,r(l<r)$ 满足 $l<m\le r$。

而因为我们把下凸点弹掉了，所以最后剩下的 $(l,r)$ 会在 $m$ 中取到最大值。

于是问题就转化为对于所有线段 $(l,r),l<m\le r$，求其在 $m$ 处的最大值。

同样，对左右两边分别建上凸壳，下凸的点可以弹掉。

但是两个前缀凸包不好合并，甚至前缀凸包也不好建。

于是我们可以对于 $[0,m)$ 的询问，对 $a$ 数组 $[m,n-1]$ 的点建上凸壳，通过凸包上二分求出 $a,b$ 数组中 $[0,m)$ 的点与该凸包产生的最大贡献，并分别求后缀，前缀最大值。

查询直接合并后缀 $a$ 最值和前缀 $b$ 最值。

同理，对于 $[m,n-1]$ 的询问，对 $b$ 数组中 $[0,m)$ 的点建上凸壳。

时间复杂度瓶颈在于凸包上二分，$O(n\log n)$：
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,fast-math",3)
using namespace std;
const int N=(1<<21)+10,M=998244353;
using ll=long long;
using ul=unsigned long long;
using ld=double;
string s;
int T,n=1e6+5,m,a[N],b[N];
ld nc;
struct dat{
    ld x,y;
    dat operator-(const dat &z)
    const{return{x-z.x,y-z.y};}
    ll operator*(const dat &z)
    const{return x*z.y-y*z.x;}
    ld operator()(const ld &p,const ld &q){
        return ld(y*p+x*q)/(x+p);
    }
}d[N];
int stk[N],tp;
ld sol(ld p,ld u){
    int L=1,R=tp,md;
    while(L<R){
        md=L+R>>1;
        if(d[stk[md+1]](p,u)>d[stk[md]](p,u))L=md+1;
        else R=md;
    }
    return d[stk[L]](p,u)*2;
}
ld pr[N],to[N];
int main(){
    ios::sync_with_stdio(false);
    int i,j,k,l,r,x,y,z;
    cin>>n;
    for(i=1;i<=n;++i)cin>>a[i];
    for(i=1;i<=n;++i)cin>>b[i];
    m=n+1>>1,nc=(1.+n)/2;
    for(x=m+1;x<=n;++x){
        d[x]={x-nc,a[x]};
        while(tp>1&&(d[stk[tp]]-d[stk[tp-1]])*(d[x]-d[stk[tp-1]])>=0)--tp;
        stk[++tp]=x;
    }
    pr[0]=to[m+1]=-1e18;
    for(x=1;x<=m;++x)
        pr[x]=max(pr[x-1],sol(nc-x,b[x]));
    for(x=m;x;--x)
        to[x]=max(to[x+1],sol(nc-x,a[x]));
    for(x=1;x<=m;++x)
        printf("%.12lf ",max(pr[x],to[x+1]));
    for(x=m,tp=0;x;--x){
        d[x]={nc-x,b[x]};
        while(tp>1&&(d[stk[tp]]-d[stk[tp-1]])*(d[x]-d[stk[tp-1]])>=0)--tp;
        stk[++tp]=x;
    }
    pr[m]=to[n+1]=-1e18;
    for(x=m+1;x<=n;++x)pr[x]=max(pr[x-1],sol(x-nc,b[x]));
    for(x=n;x>m;--x)to[x]=max(to[x+1],sol(x-nc,a[x]));
    for(x=m+1;x<=n;++x)
        printf("%.12lf ",max(pr[x],to[x+1]));
    return 0;
}
```

---

## 作者：Terac (赞：0)

使梯形面积最小，即保证答案合法同时，直线在 $x=\frac {n-1}2$ 处的 $y$ 尽量小。记 $mid=\frac{n-1}2$。

容易发现直线一定至少过两个折点，否则一定可以通过顺时针或逆时针旋转减小 $y_c$，直到碰到另一个点。又因为所有点都在这条直线下方，所以答案直线一定是凸包某条线段的所在直线。因为让 $y_{mid}$ 最小，更进一步地，是凸包过 $mid$ 的线段所在的直线。于是我们解决了没有修改的问题。

加上修改，似乎要支持一个合并凸包的操作。但我们只关注跨越 $mid$ 的那条线段，先看如何处理左半边的答案。

设当前时刻为 $i,i\in[0,\left\lfloor\frac  n 2\right\rfloor)$。暴力想法是枚举左半边的点和右半边的点共 $O(n^2)$ 条线段，算出 $y_{mid}$ 最大值，对应的线段一定在凸包上。发现有效的线段很少，对于左边的某点 $P$，它最优的匹配点一定在右半边的凸包上，换句话说，是 $P$ 与右半边凸包的切点，于是可以二分求得。

记 $g(x,y)$ 为过 $(x,y)$ 点的切线，$f(L)$ 为直线 $L$ 在 $mid$ 处的值，则 $ans_i=\max(\max\limits_{j=0}^ i f(g(j,b_j)),\max\limits_{j=i+1}^{\left\lfloor\frac  n 2\right\rfloor}f(g(j,a_j)))$，预处理前缀后缀 $\max$ 即可。

右半边的做法类似，时间复杂度 $O(n\log n)$。

---

