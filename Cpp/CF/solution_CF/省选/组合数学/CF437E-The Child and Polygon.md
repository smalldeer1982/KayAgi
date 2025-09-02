# The Child and Polygon

## 题目描述

This time our child has a simple polygon. He has to find the number of ways to split the polygon into non-degenerate triangles, each way must satisfy the following requirements:

- each vertex of each triangle is one of the polygon vertex;
- each side of the polygon must be the side of exactly one triangle;
- the area of intersection of every two triangles equals to zero, and the sum of all areas of triangles equals to the area of the polygon;
- each triangle must be completely inside the polygon;
- each side of each triangle must contain exactly two vertices of the polygon.

The picture below depicts an example of a correct splitting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437E/a8e2701cc66365983a77c546adbf6d2315ebb4eb.png)Please, help the child. Calculate the described number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ for him.

## 说明/提示

In the first sample, there are two possible splittings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437E/02e2009a70acb17a1ce2cf1ec7df448a4afdd92f.png)In the second sample, there are only one possible splitting:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437E/2a38e13bdc3c393812a8729aaf5a7d6b365647bf.png)

## 样例 #1

### 输入

```
4
0 0
0 1
1 1
1 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
0 0
1 0
0 1
-1 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
0 0
1 0
1 1
0 1
-2 -1
```

### 输出

```
3
```

# 题解

## 作者：丛雨 (赞：3)

考虑区间dp

$dp_{i,j}$表示$i$点到$j$点所截下来的图形的方案数，如下图中阴影部分的划分方案数

![](https://cdn.luogu.com.cn/upload/image_hosting/nmi0pddi.png)

$dp_{i,j}=\sum\limits_{x=i+1}^{j-1}dp_{i,x}dp_{x,j},$表示先以$ij$为$1$边剖出一个三角形，再按照乘法原理与加法原理得到结果,如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/v2v2gid4.png)

转移条件为$x$点在$ji$的右边，如上图,用叉乘判断

$\overrightarrow{ij} \times \overrightarrow{ix}>0$时$x$在$ji$右边

$\mathfrak{Talk\ is\ cheap,show\ you\ the\ code.}$

```cpp
#include<map>
#include<queue>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
# define ll long long
# define read read1<int>()
# define Type template<class T>
Type T read1(){
    T t=0;
    bool vis=0;
    char k;
    do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
    while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
    return vis?-t:t;
}
Type void print(T arg1){cout<<arg1;}
Type void get(T arg1){cout<<arg1;}
template<typename T,typename... Ts>
    void print(T arg1, Ts... arg_left){
        cout<<arg1<<" ";
        print(arg_left...);
    }
template<typename T,typename... Ts>
    void get(T arg1, Ts... arg_left){
        cout<<arg1<<" ";
        print(arg_left...);
    }
# define mod 1000000007
# define A pair<int,int>
A a[205];
int s,dp[205][205];
A operator -(const A &x,const A &y){return A(x.first-y.first,x.second-y.second);}
ll operator *(const A &x,const A &y){return 1ll*x.first*y.second-1ll*x.second*y.first;}
int main(){
    s=read;ll t=0;
    for(int i=1;i<=s;++i){
        a[i]=make_pair(read,read);
        if(i!=1)t+=a[i-1]*a[i];
    }
    t+=a[s]*a[1];
    for(int i=1;i<s;++i)
        dp[i][i+1]=1;
    if(t>0)reverse(a+1,a+s+1);
    for(int i=s;--i;)
        for(int j=i+2;j<=s;++j)
            for(int k=i+1;k<j;++k)
                if((a[j]-a[i])*(a[k]-a[i])>0)
                    dp[i][j]=(dp[i][j]+1ll*dp[i][k]*dp[k][j])%mod;
    printf("%d",dp[1][s]);
    return 0;
}
```

---

## 作者：Jeefy (赞：2)

# The Child and Polygon 题解

> 这世界这么大，遇到了这个奇奇怪怪的题。

这道题其实可以很自然的联想到卡特兰数。

在卡特兰数的计数中，有这么一个意义：$C_n$ 表示把有 $n+2$ 条边的凸多边形分成 $n$ 个三角形的方案数。

利用这个意义可以得到 $C_n$ 的另一个递推关系：

$$
C_n = \sum_{k = 0}^{n - 1} {C_k C_{n-1-k}}
$$

而这一道题，正可以类比这个递推关系进行求解。

## 思路

在卡特兰数递推中，$k$ 实际上枚举的是最后一次的分界点。也就是把整个多边形分成两部分，分别划分，再求最终方案数。

首先我们将已知的 $n$ 个点按照顺时针方向排好序。

类比下来，我们可以設 $f_{i, j}$ 表示由 $i \sim j$ 这 $j - i + 1$ 个点形成的多边形的划分数。

于是

$$
f_{i, j} = \sum_{k = i}^{j} {f_{i, k} f_{k, j}} [i 可以连向 k]
$$

> 这里 $i$ 可以连向 $k$ 当且仅当线段 $\vec{ij}$ 在线段 $\vec{ik}$ 的顺时针方向。

于是本题的核心思路就已经出来了。接下来考虑实现问题。

## 实现

### 逆时针，顺时针？

我们可以通过向量叉乘的方法来判断所给的点是顺时针还是逆时针。

考虑按照所给的点的顺序计算这个多边形的面积。

枚举 $i$ 利用 $\vec{1i}$ 和 $\vec{1(i+1)}$ 的叉乘，可以算出整个多边形的面积(的两倍)。

但是考虑到叉乘的正负性，如果结果为正，则所给的顺序为逆时针（因为 $\vec{1i}$ 在 $\vec{1(i+1)}$ 的顺时针方向）。

此时就可以搞定逆时针，顺时针的问题了。

### 可连？不可连？

在前面已经提到，$i$ 可以连向 $k$ 的条件，如何判断？

还是利用 $\vec{ij} \times \vec{ik}$，如果结果为正，则 $\vec{ij}$ 在 $\vec{ik}$ 的顺时针方向，可以连。

------------
于是你成功的可以 $\texttt{\colorbox{#52C41A}{\textcolor{white}{AC}}}$ 本题了。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 203, mod = 1e9 + 7;
typedef long long lint;

struct Point {
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	inline lint operator * (const Point &p) {
		return (1ll * x * p.y - 1ll * y * p.x);
	}

	inline Point operator - (const Point &p) {
		return Point(x - p.x, y - p.y);
	}
} p[N];

lint dp[N][N];

int main() {
	cin.tie(0)->sync_with_stdio(false);

	int n; cin >> n;
	for (int x, y, i = 1; i <= n; ++i) {
		cin >> x >> y;
		p[i] = Point(x, y);
	}

	lint clockwiser = 0;
	for (int i = 2; i < n; ++i) {
		clockwiser += (p[i] - p[1]) * (p[i + 1] - p[1]);
	}

	if (clockwiser > 0) // if is positive, then it is counterclockwise
		reverse(p + 1, p + 1 + n);

	for (int i = 1; i < n; ++i)
		dp[i][i + 1] = 1;

	for (int len = 2; len < n; ++len) {
		for (int l = 1, r = len + 1; r <= n; ++l, ++r) {
			for (int k = l; k <= r; ++k) {
				if ((p[r] - p[l]) * (p[k] - p[l]) > 0)
					dp[l][r] = (dp[l][r] + dp[l][k] * dp[k][r] % mod) % mod;
			}
		}
	}

	cout << dp[1][n] << '\n';
}

```


---

## 作者：foreverlasting (赞：2)

[也可以在这里看啦](https://foreverlasting1202.github.io/2019/07/02/NOIP2019%E5%89%8D%E7%9A%84%E5%81%9A%E9%A2%98%E8%AE%B0%E5%BD%95/)

动态规划。

考虑设计$dp[l][r]$表示$l$到$r$号点的方案数。如果这$n$个点在一个凸包上的话，考虑枚举一条边然后对应任意的三角形来转移，那么就是$dp[l][r]=\sum_{k=l}^{r} dp[l][k]\ast dp[k][r]$，初始化是$dp[i][i+1]=1$。如果有一块地方是凹进去的话，就构不成三角形了，无法转移。所以叉积判一下转移条件就好了。复杂度$O(n^3)$。

code:
```cpp
//2019.7.6 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f
#define eps 5.6e-8
#define RG register
#define db long double
#define pc(x) __builtin_popcount(x)
typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
#define pi acos(-1.0)
#define pb push_back
#define gc getchar
//inline char gc() {
//    static char buf[100000],*p1,*p2;
//    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
//}
//inline int read() {
//    res s=0,ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
inline int read() {
    res s=0,ch=gc(),w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s*w;
}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
inline void swap(res &x,res &y) {
    x^=y^=x^=y;
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int kcz=1e9+7;
const int N=2e2+10;
namespace MAIN{
    int n;
    struct P{
        int x,y;
        P() {}
        P(res x,res y):x(x),y(y) {}
    }a[N];
    inline LL operator * (const RG P &A,const RG P &B){
        return 1LL*A.x*B.y-1LL*A.y*B.x;
    }
    inline P operator - (const RG P &A,const RG P &B){
        return P(A.x-B.x,A.y-B.y);
    }
    inline void add(res &x,const res &y){
        x+=y,x>=kcz?x-=kcz:1;
    }
    inline int Add(const res &x,const res &y){
        return x+y>=kcz?x+y-kcz:x+y;
    }
    inline int mul(const res &x,const res &y){
        return int(1LL*x*y%kcz);
    }
    int dp[N][N];
    inline void MAIN(){
        n=read();
        for(res i=1;i<=n;i++){
            res x=read(),y=read();
            a[i]=P(x,y);
        }
        RG LL tmp=a[n]*a[1];
        for(res i=1;i<n;i++)tmp+=a[i]*a[i+1];
        if(tmp>0)reverse(a+1,a+n+1);
        for(res i=1;i<n;i++)dp[i][i+1]=1;
        for(res len=2;len<n;len++)
            for(res l=1,r=l+len;r<=n;l++,r++)
                for(res k=l;k<=r;k++)
                    if((a[r]-a[l])*(a[k]-a[l])>0)add(dp[l][r],mul(dp[l][k],dp[k][r]));
        printf("%d\n",dp[1][n]);
    }
}
int main() {
//    srand((unsigned)time(NULL));
    // freopen("zao.in","r",stdin);
    // freopen("std.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

