# [ICPC 2021 WF] Take On Meme

## 题目描述

众所周知，互联网的走红规律总是难以捉摸。你就职于一家名为 Mimi's Mammoth Memes 的小型广告公司。你们的广告策略非常经济实惠，全靠碰运气，使得下一个爆红的病毒式梗图诞生。然而，尽管你们精心设计过，最近的四百多个梗图却无一火爆。你对问题的具体原因并不十分清楚，但决定尝试一种全新的方法：众包创意！

根据你的梗图科学理论，所有梗图都可以在两个维度上被评分，分别是鲜艳度和泛黄程度，简称为 $(x, y)$ 值。显然（你这样认为），最出众的梗图要么特别鲜艳，要么特别不鲜艳，要么特别泛黄，要么特别不泛黄。你认为，一个梗图的“质量”可以直接通过它和基础梗图 $(0, 0)$ 的欧几里得距离平方来衡量，即计算 $(x^2 + y^2)$。

为了创造出终极病毒式梗图，你将把公司最近几个不成功的梗图放入一个通过在线投票来决胜负的锦标赛中。这个锦标赛可以用一棵有根树来表示。输入梗图位于叶子节点，在每个内部节点，针对其 $k$ 个子梗图 $(x_1, y_1),\cdots, (x_k, y_k)$ 进行投票。投票后，梗图将经历恐怖的扭曲并合并成一个新梗图，特别突出了胜者并削弱了所有的败者：得到的 $x$ 值为 

$$ \sum_{i=1}^{k} w_i \cdot x_i, $$ 

其中当第 $i$ 个梗图获胜时，$w_i$ 为 $1$，否则为 $-1$。$y$ 值的计算方式相同。该新梗图将进入锦标赛下一轮的投票——如果它没有父节点，则会被宣布为冠军，也就是最终的完美梗图！

你已经设计好了锦标赛的结构，包括所有输入的梗图和内部的投票节点。那么，该锦标赛可能产生的梗图质量的最大值是多少？

## 样例 #1

### 输入

```
4
3 2 3 4
0 10 1
0 3 6
0 2 7
```

### 输出

```
169```

## 样例 #2

### 输入

```
8
3 4 2 5
2 3 8
0 -3 9
0 -5 -7
2 6 7
0 1 4
0 -3 -1
0 1 4
```

### 输出

```
314```

# 题解

## 作者：iyaang (赞：4)

[心碎的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17579415.html)

[题目链接](https://www.luogu.com.cn/problem/P9449)

可以直接求闵可夫斯基和，这里介绍一种官解。

按照题面的两个评分尺度构建坐标系，将所有可能的 $1$ 号节点分值放在平面上，那么最后的答案一定在凸包上。如果我们知道答案的最终方向，那么问题就比较简单了：就是直接寻找特定方向上最远的点（那么就是找一个点使其与选定点的点积最大），只需要让和这个方向点积的贡献最短就行了。虽然我们并不知道方向是什么，不过可以随便钦定一个方向，求点积最大和最小的点，这样一定可以找到凸包上的两个点，这个可以直接树形 DP 做。再以这两个点的连线的垂线为方向，如果凸包上还有点那么一定可以找到新的凸包上的点。反复重复这个过程，知道找出的点积最大和最小的点重合，这时候找齐了凸包上的所有点。找点的时候顺便直接统计答案即可。

这样复杂度是凸包上的点数乘 $n$ 的，因为做一遍树形 DP 是 $\mathcal O(n)$，一次只能找到凸包上两个点。不过这样就留下了一个问题：凸包上到底有多少个点，复杂度是否正确？注意到给定的点的坐标都是整数，整点凸包上的点的数量级是[我们已经解决的问题](https://www.cnblogs.com/LittleTwoawa/p/17353949.html)。于是总复杂度为 $\mathcal O(T^{\frac{2}{3}} n)$，其中 $T \leq 10^7$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
using namespace std;

namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        putchar(ch);
        return;
    }
}
using namespace FastIO;

namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=a>b?a:b;}
    TT inline void cmin(T &a,T b) {a=a<b?a:b;}
    TT inline void Madd(T &a,T b) {a=a+b>Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=10010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
	
	namespace Geometry
	{
		struct Point
		{
			int x,y;
			Point(int X=0,int Y=0):x(X),y(Y) {}
			inline friend Point operator + (Point a,Point b) {return Point(a.x+b.x,a.y+b.y);}
			inline friend Point operator - (Point a,Point b) {return Point(a.x-b.x,a.y-b.y);}
			template<typename T> inline friend Point operator * (Point a,T b) {return Point(a.x*b,a.y*b);}
			template<typename T> inline friend Point operator / (Point a,T b) {return Point(a.x/b,a.y/b);}
			inline friend Point operator * (Point a,Point b) {return Point(a.x*b.x-a.y*b.y,a.y*b.x+a.x*b.y);}
			inline Point operator += (Point &T) {*this=*this+T; return *this;}
			inline Point operator -= (Point &T) {*this=*this-T; return *this;}
			template<typename T> inline Point operator *= (T &x) {*this=*this*x; return *this;}
			template<typename T> inline Point operator /= (T &x) {*this=*this/x; return *this;}
			inline Point operator *= (Point &T) {*this=*this*T; return *this;}
			inline friend bool operator == (Point a,Point b) {return a.x==b.x&&a.y==b.y;}
		};
		inline int Dot(Point a,Point b) {return a.x*b.x+a.y*b.y;}
		inline int Cross(Point a,Point b) {return a.x*b.y-a.y*b.x;}
		inline int Norm(Point a) {return sqrt(Dot(a,a));}
	}
	using namespace Geometry;
	
	int n,k,ans;
	Point p[MAX];
	vector<int> G[MAX];
	
    inline void lmy_forever()
    {
    	auto Hull=[&](Point P)->pair<Point,Point>
    	{
    		auto comp=[&](Point A,Point B)->bool
    		{
    			return Dot(P,A)<Dot(P,B);
			};
    		auto dfs=[&](auto dfs,int now)->pair<Point,Point>
    		{
    			if(G[now].empty()) return mp(p[now],p[now]);
    			auto [sl,sr]=dfs(dfs,G[now][0]);
    			Point vl,vr; vl=vr=sl+sr;
    			for(int i=1;i<((int)G[now].size());++i)
    			{
    				auto [l,r]=dfs(dfs,G[now][i]);
    				sl+=l,sr+=r;
    				if(comp(l+r,vl)) vl=l+r;
    				if(comp(vr,l+r)) vr=l+r;
				}
				return mp(vl-sr,vr-sl);
			};
			auto [l,r]=dfs(dfs,1);
			cmax(ans,Dot(l,l)),cmax(ans,Dot(r,r));
			return mp(l,r);
		};
		
		auto solve=[&](auto solve,Point a,Point b)->void
		{
			if(a==b) return;
			int x=(b-a).x,y=(b-a).y;
			Point c={-y,x};
			auto [_,d]=Hull(c);
			if(Dot(d,c)>max(Dot(a,c),Dot(b,c))) solve(solve,a,d),solve(solve,d,b);
		};
    	
    	read(n);
    	for(int i=1;i<=n;++i)
    	{
    		read(k);
    		if(!k) read(p[i].x,p[i].y);
    		else for(int j=1;j<=k;++j) G[i].eb(read());
		}
		auto [a,b]=Hull((Point){1,0});
		solve(solve,a,b);
		write(ans,'\n');
        return;
    }
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

