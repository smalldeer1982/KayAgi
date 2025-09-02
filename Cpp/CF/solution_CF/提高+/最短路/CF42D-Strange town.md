# Strange town

## 题目描述

Volodya最近到了一个很奇怪的小镇。这个小镇里有N个景点，并且每两个景点之间都有一条双向边连接。每条边都有一定的旅行费用（保证为自然数），保证每条路的费用都不同。但是最令人吃~~鸡~~惊的是每条遍历这个小镇里所有景点的路线都有相同的总费用！也就是说，任意一条包括所有景点的成环路线，它的总费用与这条路线无关。Volodya想要学OI的你编写一个程序来帮助他找出是否能够构建一张双向联通图符合上述要求且所有道路的旅行费用都不超过1000。

## 样例 #1

### 输入

```
3
```

### 输出

```
0 3 4 
3 0 5 
4 5 0 
```

# 题解

## 作者：MyukiyoMekya (赞：4)

考虑给第 $i$ 个点一个权值 $a_i$ ，那么 $(i,j)$ 之间的边权值就为 $a_i+a_j$ 就可以很妙的让所有哈密顿回路边权和相同，然后考虑增量法：一个一个加点。

假设新加入的点为 $i$ ，那么我们要保证每一组 $u,v,k(u\ne v,1\le u,v,k<i)$ 都有 $a_u+a_v\ne a_k+a_i$

也就是 $a_u+a_v-a_k\ne a_i$ ，为了让 $a_i\le 1000$ ，我们肯定贪心取最小的，也就是所有 $a_u+a_v-a_k$ 的 $\operatorname{mex}$ 。

分析一下正确性，对于一个 $i$ ，$(u,v,k)$ 是 $\mathcal O(n^3)$ 级别的，所以正确性得以保证。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define ALL(x) (x).begin(),(x).end()
#define mem(x,y) memset(x,y,sizeof x)
#define sz(x) (int)(x).size()
#define ln std::puts("")
#define lsp std::putchar(32)
#define pb push_back
#define MP std::make_pair
#define dbg(x) std::cerr<<__func__<<"\tLine:"<<__LINE__<<' '<<#x<<": "<<x<<"\n"
#define dprintf(x...) std::fprintf(stderr,x)
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,b,a) for(int i=(b);i>=(a);--i)
const int MaxN=25;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
int a[25];
signed main(void)
{
	int n;read(n);
	a[1]=1,a[2]=2;
	for(int i=3;i<=n;++i)
	{
		std::set<int> S;
		for(int u=1;u<i;++u)
			for(int v=1;v<i;++v)
				if(u!=v)
					for(int j=1;j<i;++j)
						S.insert(a[u]+a[v]-a[j]);
		a[i]=1;
		while(S.find(a[i])!=S.end())++a[i];
	}
	for(int i=1;i<=n;++i,ln)
		for(int j=1;j<=n;++j,lsp)
			if(i!=j)
				write(a[i]+a[j]);
			else
				std::putchar('0');
	return 0;
}
```

 



---

