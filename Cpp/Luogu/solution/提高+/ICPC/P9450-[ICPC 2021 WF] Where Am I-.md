# [ICPC 2021 WF] Where Am I?

## 题目描述

我是谁？我是什么？我为什么存在？这些都是让哲学家们在过去的千年里一直忙碌的问题。但是当谈到“我在哪里”时，现代智能手机和 GPS 卫星几乎已经让这个问题失去了吸引力。

为了给那些曾经思考“我在哪里”问题的空间哲学家们再添一层伤害，“即时制图定位公司”（ICPC）决定进行一次演示，以展示 GPS 比传统地图强大得多。他们的论点是，地图只有在你已经知道自己在哪里时才有用，但如果你从一个未知位置开始，地图的用处就小得多了。

在这次演示中，ICPC 创建了一个测试区域，该区域被布置成一个无限的笛卡尔网格。大多数网格单元是空的，但有限数量的单元在其中心有一个标记（参见图 L.1(a) 中的五个标记单元的示例）。所有空网格单元看起来都一样，所有带标记的单元也看起来都一样。假设你得到了测试区域的地图（即所有标记的位置），并且你被放置在一个（你不知道的）网格单元上。你需要多长时间才能找到你实际所在的位置？ICPC 的答案很明确：可能需要很长很长的时间，而 GPS 会立即给你答案。但究竟需要多长时间呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/ydxjurja.png)

在试验中，测试对象将通过遵循一个顺时针扩展的螺旋形来探索他们的环境，其前几步如图 L.1(b) 所示。起始单元标记为“0”，数字显示了访问其他单元的顺序。测试对象只有在其网格单元上才能看到标记，并且一旦他们根据迄今为止看到的网格单元知道自己在哪里，他们就会停止探索。这意味着观察到的空和标记网格单元的序列只能从一个可能的起始位置开始。网格是无限的，但探索将是有限的，因为一旦测试对象看到了网格上的所有标记，他们就一定知道自己在哪里。

让数百名测试对象字面意义上地绕圈跑可能会很昂贵，所以 ICPC 认为编写一个模拟程序会更便宜更快。也许你可以帮忙？

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 5
....X
.X...
.....
X..X.
..X..
```

### 输出

```
9.960000000
18
(1,4) (4,5)
```

## 样例 #2

### 输入

```
5 1
..XX.
```

### 输出

```
4.600000000
7
(1,1) (5,1)
```

# 题解

## 作者：iyaang (赞：1)

[纯享的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17582188.html)

[题目链接](https://www.luogu.com.cn/problem/P9450)

这年 WF 较为简单的一道了，直接模拟即可。首先可以预处理出它顺时针螺旋轨迹的移动步数，方便过会算距离直接查表。我偷懒直接用 map 记录的距离表，这样不用处理复数下标的问题。注意到 $X$ 的数量不会超过 $100$ 个，所以我们可以反过来从标记点上入手。找出所有的标记点，记录下每个位置到每个标记点的距离并将这些距离从小到大排序，然后将每个位置按照“到每个 $X$ 的距离构成的序列”的字典序排序，这样无法区分所在位置的一定是在排序后序列中相邻的两项，因为它们有最长的公共前缀，可以直接暴力遍历算。最后统计答案即可。如果视查询 map 复杂度为 $\mathcal O(1)$ 的话，记 $T$ 为 $X$ 标记的数量，复杂度 $\mathcal O(d_x d_y T \log T)$。

闲话：

![](https://dl3.img.timecdn.cn/2023/07/26/AJMXOCQ9XM5_TVYXV3.png)

[另一篇题解](https://www.luogu.com.cn/blog/894838/solution-p9450)有点逆天啊，感觉[在哪见过](https://zhuanlan.zhihu.com/p/583573316)。

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
    static const int Mod=1e9+9;
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
    static const int MAX=100010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
	
	int n,m;
	char c;
	vector<pii> X,ans; int Xcnt;
	map<pii,int> dis;
	int dissum,dismix;
	
	struct lmy
	{
		int x,y,dis;
		vector<int> tox;
		lmy(int X=0,int Y=0,int Dis=0):x(X),y(Y),dis(Dis) {}
	};
	vector<lmy> all;
	
    inline void lmy_forever()
    {
    	read(n,m);
    	for(int x=0,y=0,step=0,stepn=1,cur=0,dx=0,dy=1;cur<=40400;++cur)
    	{
    		dis[mp(x,y)]=cur,x+=dx,y+=dy;
    		if(++step==stepn) Swp(dx,dy),dy=-dy,step=0,stepn+=(dy!=0);
		}
    	for(int j=m;j>=1;--j) for(int i=1;i<=n;++i)
    	{
    		do c=getchar(); while(c!='X'&&c!='.');
    		if(c=='X') X.eb(mp(i,j));
		}
		Xcnt=X.size();
		for(int i=1;i<=n;++i) for(int j=1;j<=m;++j)
		{
			lmy now; now.x=i,now.y=j;
			for(auto it:X) now.tox.eb(dis[mp(it.fi-i,it.se-j)]);
			sort(now.tox.begin(),now.tox.end()),all.eb(now);
		}
		sort(all.begin(),all.end(),[&](lmy a,lmy b){for(int i=0;i<Xcnt;++i) if(a.tox[i]!=b.tox[i]) return a.tox[i]<b.tox[i];});
		for(int i=1;i<((int)all.size());++i) for(int j=0;j<Xcnt;++j) if(all[i].tox[j]!=all[i-1].tox[j])
		{
			cmax(all[i].dis,min(all[i].tox[j],all[i-1].tox[j])),
			cmax(all[i-1].dis,min(all[i].tox[j],all[i-1].tox[j]));
			break;
		}
		for(auto it:all) cmax(dismix,it.dis),dissum+=it.dis;
		cout<<fixed<<setprecision(9)<<1.0*dissum/((int)all.size())<<'\n'<<dismix<<'\n';
		for(auto it:all) if(it.dis==dismix) ans.eb(mp(it.y,it.x));
		sort(ans.begin(),ans.end());
		for(auto it:ans) putchar('('),write(it.se,','),write(it.fi,')'),putchar(' ');
    	return puts(""),void();
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

