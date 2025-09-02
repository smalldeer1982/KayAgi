# [NERC 2021] Fancy Stack

## 题目描述

小 Fiona 有 $n$ 个大小各异的积木 $a_1, a_2, \ldots, a_n$，其中 $n$ 为偶数。有些积木的大小可能相同。她想把这些积木一块一块地堆叠起来，形成一个**花式**堆叠。

设 $b_1, b_2, \ldots, b_n$ 为从顶部到底部的积木大小序列。由于 Fiona 要使用所有积木，$b_1, b_2, \ldots, b_n$ 必须是 $a_1, a_2, \ldots, a_n$ 的一个排列。Fiona 认为堆叠是**花式**的，当且仅当满足以下两个条件：
1. 第二块积木严格大于第一块，之后每块积木交替严格小于或严格大于前一块。形式化地说，$b_1 < b_2 > b_3 < b_4 > \ldots > b_{n-1} < b_n$。
2. 位于偶数位置的积木大小严格递增。形式化地说，$b_2 < b_4 < b_6 < \ldots < b_n$（记住 $n$ 是偶数）。

![](https://cdn.luogu.com.cn/upload/image_hosting/16lldnv3.png)

如果两个堆叠对应的序列 $b_1, b_2, \ldots, b_n$ 在至少一个位置上不同，则认为它们是不同的堆叠。

Fiona 想知道她能用所有积木堆出多少种不同的花式堆叠。由于大数字会让 Fiona 害怕，请将结果对 $998\,244\,353$ 取模后输出。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
4
1 2 3 4
8
1 1 2 3 4 4 6 7```

### 输出

```
2
4```

# 题解

## 作者：CYZZ (赞：0)

简单题。

将 $a$ 排序。记 $t_i$ 为值 $i$ 的出现次数。

直接统计 $b$ 比较困难。 我们统计 $a$ 有多少种排列方式能得到合法的 $b$。最终答案为 $\frac{ans}{\prod t_i}$。

把 $a$ 去重得到 $a'$。记 $a'$ 长度为 $cnt$ ，$pos_i$ 表示 $a'_i$ 在 $a$ 中第一次出现的位置。

发现每层的限制与奇偶性有关，于是我们两层两层 dp。

设 $f_{i,j}$ 表示考虑了前 $2i$ 层，$b_{2i}=a'_j$ 的方案数。考虑怎么向后转移。

- 对于第 $2i+1$ 层。有 $pos_j-1$ 个可以填进去的数，以前用掉了 $2i-1$ 个。故方案数为 $pos_j-2i$。
- 对于第 $2i+2$ 层。可以填任意 $k>j$，方案数为 $t_{a'_k}$。

由乘法原理得到转移：
$$
f_{i+1,k} \larr (pos_j-2i)\cdot t_{a'_k} \cdot f_{i,j}
$$
前缀和优化。复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define eb emplace_back
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
#define per(i,y,x) for(int i=(y);i>=(x);i--)
bool Memst;
namespace cyzz
{
	#define N 5005
	#define mod 998244353
	inline void Add(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
	int n,a[N],inv[N];
	int t[N],nxt[N];
	int cnt,pos[N];
	int f[N][N],pre[N][N];
	void init()
	{
		inv[0]=inv[1]=1;
		rep(i,2,n) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		rep(i,2,n) inv[i]=1ll*inv[i-1]*inv[i]%mod;
	}
	void clr()
	{
		memset(t,0,n+1<<2);
		rep(i,0,n/2+1) rep(j,0,cnt+1) f[i][j]=pre[i][j]=0;
		cnt=0;
	}
	void solve()
	{
		scanf("%d",&n);init();
		rep(i,1,n) scanf("%d",&a[i]),t[a[i]]++;
		sort(a+1,a+n+1);
		int u=1;
		while(u<=n)
		{
			pos[++cnt]=u;
			while(a[u]==a[pos[cnt]]) u++;
		}
		rep(i,1,cnt)
			f[1][i]=1ll*t[a[pos[i]]]*(pos[i]-1)%mod;
		rep(i,1,n/2)
		{
			if(i>1)
			{
				rep(j,1,cnt)
				{
					Add(pre[i][j],pre[i][j-1]);
					f[i][j]=1ll*t[a[pos[j]]]*pre[i][j]%mod;
				}
			}
			if(i<n/2)
			{
				rep(j,1,cnt)
					Add(pre[i+1][j+1],1ll*(pos[j]-2*i)%mod*f[i][j]%mod);
			}
		}
		int ans=f[n/2][cnt];
		rep(i,1,cnt) ans=1ll*ans*inv[t[a[pos[i]]]]%mod;
		printf("%d\n",ans);
		clr();
	}
	void MAIN()
	{
		int T;scanf("%d",&T);
		while(T--) 	solve();
	}
}bool Memed;
int main()
{
	// freopen("in.in","r",stdin);
	// freopen("out.out","w",stdout);
	cyzz::MAIN();
	debug("%.2lfms %.2lfMB",1.0*clock()/CLOCKS_PER_SEC*1000,
		1.0*abs(&Memed-&Memst)/1024/1024);
}
```

数组定义的有些混乱，将就着看吧。

---

