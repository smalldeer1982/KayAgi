# [ARC032C] 仕事計画

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc032/tasks/arc032_3

大工のチョーさん(Daiku Cho)は $ N $ 個の仕事を頼まれています。$ i $ 番目の仕事は時刻 $ a_i $ に始まり、$ b_i $ に終わります。

チョーさんは一度に複数の仕事をこなすことはできないので、これらの仕事のうち、仕事を行う時刻が重ならないようになるべく多くの仕事を選びたいです。ただし、終了と同時に別の仕事に取り掛かることはできます。

最も多く選ぶ方法が複数あるときは、選んだ仕事の番号を開始時刻の順に並べた列が辞書順最小となるように選ぼうと思っています。

大工のチョーさんは仕事上手ですが、スケジュールを管理するのは上手くないようです。チョーさんが引き受ける最適な仕事の組み合わせを求めてください。

ただし、長さ $ L $ の列 $ A=\{a_1,a_2,…,a_L\} $ と $ B=\{b_1,b_2,…,b_L\} $ に対し、辞書順で $ A $ が $ B $ より小さいとは、

- $ i\ <\ k $ で $ a_i $=$ b_i $
- $ i=k $ で $ a_i $&lt;$ b_i $

となるような $ k(1≦k≦L) $ が存在するということです。

## 说明/提示

### Sample Explanation 1

チョーさんは最大で $ 2 $ つの仕事を選ぶことができます。その選び方は $ 3 $ 通りあり、チョーさんは仕事 $ 1 $ と $ 4 $、または仕事 $ 2 $ と $ 3 $、または仕事 $ 2 $ と $ 4 $ を選ぶことができます。 この内、辞書順で小さくなる選び方は仕事 $ 1 $ と $ 4 $ を選んだときです。なぜならば、それらの仕事番号を \*\*仕事の開始時刻順\*\* に並べたときに $ \{1,4\} $ となり、それが辞書順最小となるからです(21:12修正)。 !\[\](http://arc032.contest.atcoder.jp/img/arc/032/C1.png)

## 样例 #1

### 输入

```
4
0 5
0 3
3 7
5 10```

### 输出

```
2
1 4```

## 样例 #2

### 输入

```
5
0 5
0 3
3 7
5 10
7 12```

### 输出

```
3
2 3 5```

## 样例 #3

### 输入

```
8
1 5
3 9
2 5
1 2
8 10
9 11
7 15
10 14```

### 输出

```
4
4 3 5 8```

# 题解

## 作者：iiiiiyang (赞：1)

[无聊的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17682415.html)

[题目链接](https://www.luogu.com.cn/problem/AT_arc032_3)

只和区间相对位置有关，先离散化。时间点上倒序贪心，设 $f_i$ 表示第 $i$ 个时间点最多能选几个区间，$g_i$ 表示在最大 $f_i$ 的前提下转移过来最小的字典序标号，可以顺便记录前驱。区间右端点可以转移到左端点，将右端点的决策存在左端点上即可。转移只有两种，继承上一个时间点的答案，选择一个区间从右端点转移过来。于是做到 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
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
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=200010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int n,l[MAX],r[MAX],d[MAX],cnt,now;
    int f[MAX],g[MAX],from[MAX];
    vector<pii> dec[MAX];
    
    inline void lmy_forever()
    {
    	read(n),memset(g,-1,sizeof g);
    	for(int i=1;i<=n;++i) read(l[i],r[i]),d[++cnt]=l[i],d[++cnt]=r[i];
    	sort(d+1,d+cnt+1),cnt=unique(d+1,d+cnt+1)-d-1;
    	for(int i=1;i<=n;++i) l[i]=lower_bound(d+1,d+cnt+1,l[i])-d,r[i]=lower_bound(d+1,d+cnt+1,r[i])-d,dec[l[i]].eb(mp(r[i],i));
    	for(int i=cnt;i;--i)
    	{
			for(auto [j,id]:dec[i])
			{
				if(f[i]<f[j]+1) f[i]=f[j]+1,g[i]=INF;
	    		if(f[i]==f[j]+1&&g[i]>id) g[i]=id,from[i]=j;
			}
	    	if(i!=cnt&&f[i]<f[i+1]) f[i]=f[i+1],g[i]=INF;
			if(i!=cnt&&f[i]==f[i+1]&&g[i]>g[i+1]) g[i]=g[i+1],from[i]=from[i+1];
		}
		write(f[1],'\n'),now=1,write(g[now],'~'),now=from[now];
		while(g[now]!=-1) putchar(' '),write(g[now],'~'),now=from[now];
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

