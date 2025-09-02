# [CERC2013] Chain & Co.

## 题目描述

Chain $&$ Co. 专注于生产无限强度的链条。由于其高质量的产品，他们迅速占领了市场。这带来了新的挑战，其中一些是他们之前从未想象过的。例如，使用计算机程序自动验证链环的耐久性，而这正是你需要编写的程序。

公司生产的链环大小相同。每个链环都是三维空间中的一个无限薄的正方形框架（由四个无限薄的线段构成）。

在测试过程中，所有链环都是“轴对齐的”并且放置得没有两个框架接触。为了进行适当的强度测试，锻造了两个链环集合 A 和 $B$，使得 A 的每个链环都与 B 的每个链环不可分离（不可分离意味着它们不能在不破坏其中一个的情况下分开）。

你偶然发现了一些链环（轴对齐，成对不相交）。它们是否处于适当的测试位置？换句话说，它们能否被划分为两个非空集合 A 和 $B$，并具有所需的特性？

“轴对齐”意味着所有线段都平行于 $X, Y$ 或 $Z$ 轴。

## 说明/提示

时间限制：10 秒，内存限制：128 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3

2
0 0 0 0 10 10
-5 5 15 5 5 25

5
0 0 0 0 10 10
-5 5 6 5 5 16
-5 5 -6 5 5 4
-5 6 5 5 16 5
-5 -6 5 5 4 5

3
0 0 0 3 0 -3
1 -1 -1 1 2 -4
-1 -2 -2 2 1 -2
```

### 输出

```
NO
YES
YES
```

# 题解

## 作者：Graphcity (赞：2)

首先注意到同一维相等的矩形都是不能扣起来的，所以只用考虑 $x,y,z$ 相等的三类矩形的划分方式。

考虑 $y$ 相等的矩形 $A$ 和 $z$ 相等的矩形 $B$ 扣起来的条件：

$$
\begin{cases}
y_{B_{\min}}\le y_{A}\le y_{B_{\max}}\\
z_{A_{\min}}\le z_{B}\le z_{A_{\max}}\\
\end{cases}
$$

这两个条件都很好判断。关键在于 $x$ 坐标。分析这些矩形在 $x$ 轴上的投影，可以发现投影都是一个区间，而且有 $A$ 中矩形的投影区间与 $B$ 中矩形的投影区间相交。

正难则反，扫描线判断有无两个区间相离或者包含即可。

其它情况类似，只需将坐标变换一下。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6,inf=1e9+7;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int T,n;
struct Square{int x1,y1,z1,x2,y2,z2;};
struct Node{int l,r,op;};
inline bool operator<(Node a,Node b) {return a.l<b.l;}
vector<Square> X,Y,Z;

vector<Node> v;
inline int CheckYZ()
{
    if(Y.empty() || Z.empty()) return 0;
    int Zmn=inf,Zmx=-inf,Ymn=inf,Ymx=-inf;
    for(auto i:Z) Zmn=min(Zmn,i.z1),Zmx=max(Zmx,i.z2);
    for(auto i:Y) Ymn=min(Ymn,i.y1),Ymx=max(Ymx,i.y2);
    for(auto i:Y) if(i.z1>=Zmn || i.z2<=Zmx) return 0;
    for(auto i:Z) if(i.y1>=Ymn || i.y2<=Ymx) return 0;
    int yl=-inf,yr=inf,zl=-inf,zr=inf;
    v.clear(),v.shrink_to_fit();
    for(auto i:Y)
        yl=max(yl,i.x1),yr=min(yr,i.x2),
        v.push_back((Node){i.x1,i.x2,1});
    for(auto i:Z) 
        zl=max(zl,i.x1),zr=min(zr,i.x2),
        v.push_back((Node){i.x1,i.x2,2});
    if(yr<=zl || zr<=yl) return 0;
    sort(v.begin(),v.end()),yr=zr=-inf;
    for(auto i:v)
    {
        if(i.op==1) {if(zr>=i.r) return 0; yr=max(yr,i.r);}
        if(i.op==2) {if(yr>=i.r) return 0; zr=max(zr,i.r);}
    }
    return 1;
}
inline int CheckXY()
{
    if(X.empty() || Y.empty()) return 0;
    swap(X,Z);
    for(auto &i:X) swap(i.x1,i.z1),swap(i.x2,i.z2);
    for(auto &i:Y) swap(i.x1,i.z1),swap(i.x2,i.z2);
    for(auto &i:Z) swap(i.x1,i.z1),swap(i.x2,i.z2);
    int chk=CheckYZ();
    swap(X,Z);
    for(auto &i:X) swap(i.x1,i.z1),swap(i.x2,i.z2);
    for(auto &i:Y) swap(i.x1,i.z1),swap(i.x2,i.z2);
    for(auto &i:Z) swap(i.x1,i.z1),swap(i.x2,i.z2);
    return chk;
}
inline int CheckXZ()
{
    if(X.empty() || Z.empty()) return 0;
    swap(X,Y);
    for(auto &i:X) swap(i.x1,i.y1),swap(i.x2,i.y2);
    for(auto &i:Y) swap(i.x1,i.y1),swap(i.x2,i.y2);
    for(auto &i:Z) swap(i.x1,i.y1),swap(i.x2,i.y2);
    int chk=CheckYZ();
    swap(X,Y);
    for(auto &i:X) swap(i.x1,i.y1),swap(i.x2,i.y2);
    for(auto &i:Y) swap(i.x1,i.y1),swap(i.x2,i.y2);
    for(auto &i:Z) swap(i.x1,i.y1),swap(i.x2,i.y2);
    return chk;
}

inline void Solve()
{
    n=read(),X.clear(),Y.clear(),Z.clear();
    X.shrink_to_fit(),Y.shrink_to_fit(),Z.shrink_to_fit();
    For(i,1,n)
    {
        int x1=read(),y1=read(),z1=read(),x2=read(),y2=read(),z2=read();
        if(x1>x2) swap(x1,x2); if(y1>y2) swap(y1,y2); if(z1>z2) swap(z1,z2);
        Square k=(Square){x1,y1,z1,x2,y2,z2};
        if(x1==x2) X.push_back(k);
        if(y1==y2) Y.push_back(k);
        if(z1==z2) Z.push_back(k);
    }
    if(n==1) {printf("NO\n"); return;}
    if((!X.empty())+(!Y.empty())+(!Z.empty())==1) {printf("NO\n"); return;}
    int XY=CheckXY(),XZ=CheckXZ(),YZ=CheckYZ();
    if((!X.empty())+(!Y.empty())+(!Z.empty())==2)
    {
        if(XY || YZ || XZ) printf("YES\n");
        else printf("NO\n");
        return;
    }
    if((XY && XZ) || (XY && YZ) || (XZ && YZ)) printf("YES\n");
    else printf("NO\n");
}

int main()
{
    T=read();
    while(T--) Solve();
    return 0;
}
```

---

## 作者：Sampson_YW (赞：0)

好像没用到正方形和边长相等这两个条件？

有点卡常的单 $\log$ 做法。

由于任意两个矩形的边界不交，所以只有平行于不同坐标轴的两个矩形会出现“不可分离”。

考虑一个平行于 $x$ 轴的矩形 $i$ 和一个平行于 $y$ 轴的矩形 $j$ 要满足以下三个条件才会不可分离。

- $xl_j<x_i<xr_j$。

- $yl_i<y_j<yr_i$。

- 区间 $[zl_i, zr_i]$ 和区间 $[zl_j, zr_j]$ 有交且互不包含。

$x$ 轴和 $z$ 轴，$y$ 轴和 $z$ 轴同理。

考虑建图。将可以分离的矩形之间连边，如果最后只有一个连通块就无法分成两个集合。

直接建图是 $O(n^2)$ 的，考虑优化。

由于只要求连通块数量，所以可以用并查集优化。

因为两个矩形只要有任意一个条件不满足就会连边，并且对于每个维度是独立的。所以我们可以将三个维度单独拿出来连边。

考虑对于 $x$ 轴的连边方法。$y$ 轴和 $z$ 轴同理。

- 两个平行于 $x$ 轴的矩形，一定会有连边。

- 一个平行于 $x$ 轴的矩形和一个不平行于 $x$ 轴的矩形 $j$，当 $x_i\leq xl_j$ 或 $x_i \geq xr_j$ 的时候会和矩形 $i$ 有连边。

这种情况按照区间的结尾或开头排序，然后把单点从小到大或从大到小排序，每种情况分别扫一遍即可。

- 两个不平行于 $x$ 轴的矩形 $i,j$，当区间 $[xl_i,xr_i]$ 和区间 $[xl_j,xr_j]$ 不交或包含时会有连边。

这种情况以右端点为第一关键字，左端点为第二关键字排序，再用个栈维护一下即可。

~~不知道咋描述，代码可能更清晰。~~

复杂度 $O(n\log n)$，瓶颈在排序。

[Code](https://www.luogu.com.cn/paste/sf2iok8n)

---

