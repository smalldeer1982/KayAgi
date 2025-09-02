# Bounding Box

## 题目描述

在平面直角坐标系中有 $N$ 个点，第 $i$ 个点在 $(x_i,y_i)$ 处，价值为 $c_i$。

你需要选择 $K$ 个点，令：

- $X_{\max}$ $\coloneqq$ 选择的点的 $x$ 坐标的最大值
- $X_{\min}$ $\coloneqq$ 选择的点的 $x$ 坐标的最小值
- $Y_{\max}$ $\coloneqq$ 选择的点的 $y$ 坐标的最大值
- $Y_{\min}$ $\coloneqq$ 选择的点的 $y$ 坐标的最小值
- $S$ $\coloneqq$ 选择的点的价值之和

要求最大化 $(X_{\max}-X_{\min})+(Y_{\max}-Y_{\min})+S$，请输出其最大值。

## 说明/提示

- $1\le K\le\ N\le 2\times10^5$
- $1\le x_i,y_i\le 10^9$
- $1\le c_i\le 10^9$

## 样例 #1

### 输入

```
3 2
1 3 1
3 1 1
3 3 2```

### 输出

```
6```

## 样例 #2

### 输入

```
12 5
79 29 4
47 96 11
31 100 13
89 67 13
28 45 9
66 70 12
18 12 9
21 57 14
67 17 6
91 12 9
79 11 8
67 50 6```

### 输出

```
220```

# 题解

## 作者：Richard_Whr (赞：5)

题意：平面上 $n$ 个点，坐标为 $(x_i,y_i)$，有权值 $c_i$。


你要选 $k$ 个点，使得 这些点的权值和 加上 这些点 $x$ 坐标最大值与最小值的差 加上 这些点 $y$ 坐标最大值与最小值的差 尽量大。

经典套路就是你发现最大化的是 $\max-\min$，显然是越大越好。

可以弱化这个问题：选 $k$ 个点，选某个点的 $-x_i$，某个点的 $x_j$，某个点的 $-y_k$，某个点的 $y_l$，以及所有点的权值和。

可以发现不优的情况你一定不会选，最优决策一定是自动选择了最大值和最小值做差。

因此就有了一个 $O(n^2)$ 的 dp。

设 $f_{i,j,s}$ 表示前 $i$ 个物品，选了 $j$ 个，当前上述四种特殊权值有没有使用，的最大价值。

预处理一个点的 $val_{i,s}$ 表示这个点四种特殊权值使用情况为 $s$ 的时候对答案的贡献。

转移就是 $f_{i,j,s}=\max(f_{i-1,j-1,t}+val_{i,s \oplus t})$。

考虑我们如何优化这个东西。

其实这 $j$ 个中只有最多 $4$ 个有特殊权值，其余的都是“平等”的，体积为 $1$，价值为 $val_{i,0}$。

当我们确定了含有特殊权值的选了的点的集合 $S$，我们一定会从剩下的 $n-|S|$ 个中挑权值最大的 $k-|S|$ 个。

这部分是可以贪心的。

当我们固定了 $k$ 的时候，最大值前 $k-4$ 的元素一定会选，同时他们还有可能贡献一些特殊权值。

而不在前 $k-4$ 大的元素最多只会选 $4$ 个，且他们一定贡献特殊权值。

我们按权值从大到小对点排序，分别做前缀后缀的背包。

前缀背包忽略体积，后缀背包体积最大为 $4$。

这样复杂度优化为 $n \times 4\times 3^4$。

对于查询，我们枚举选了 $t$ 个特殊点不在前 $k-t$ 大的集合中，然后再枚举一下前面特殊权值的贡献状态，将两个背包合并即可。

$$ans=\max\limits_{t=0}^{\min(4,k)}\{f_{k-t,s}+g_{k-t+1,t,s \oplus 2^4}\}$$

总复杂度 $O(n\times3^4+n\times 4\times 3^4+q\times 4\times 2^4)$。

虽然复杂度不应该含有常数，但这个题常数的计算还是比较必要的，因此还是放进去了。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,M=16,K=5;
int f[N][M],g[N][K][M];
struct Data
{
	int x,y,c;
	bool operator<(const Data &t)const
	{
		return c>t.c;
	}
}q[N];
int val[N][M];
int n,m;

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>q[i].x>>q[i].y>>q[i].c;
	}
	
	sort(q+1,q+1+n);
	
	memset(f,-0x3f,sizeof f);
	f[0][0]=0;
	
	for(int i=1;i<=n;i++)
	{
		for(int s=0;s<M;s++)
		{
			val[i][s]=q[i].c;
			if(s&1) val[i][s]-=q[i].x;
			if(s&2) val[i][s]+=q[i].x;
			if(s&4) val[i][s]-=q[i].y;
			if(s&8) val[i][s]+=q[i].y;
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int s=0;s<M;s++)
		{
			f[i][s]=f[i-1][s]+val[i][0];
			for(int t=s;t;t=(t-1)&s) 
			{
				f[i][s]=max(f[i][s],f[i-1][s^t]+val[i][t]);
			}
		}
	}
	
	memset(g,-0x3f,sizeof g);
	g[n+1][0][0]=0;
	
	//必须选某个1，2，4，8 
	
	for(int i=n;i>=1;i--)
	{
		for(int j=0;j<K;j++)
		{
			for(int s=0;s<M;s++)
			{
				g[i][j][s]=g[i+1][j][s];
				if(!j) continue;
				for(int t=s;t;t=(t-1)&s) g[i][j][s]=max(g[i][j][s],g[i+1][j-1][s^t]+val[i][t]);
			}	
		}
	}
	
	
	int ans=f[m][M-1];
	for(int t=1;t<=4;t++)//后面选了几个 
		for(int s=0;s<M;s++)
			ans=max(ans,f[m-t][s]+g[m-t+1][t][15-s]);
	cout<<ans<<"\n";
	
	return 0;
}
```

---

## 作者：HomuraAkemi (赞：1)

场切了。

考虑“不合法不优”。随便钦定一个点作为最大值计入答案。如果它实际上并不是最大的，那么一定不优，会在取 $\max$ 的时候被排除掉。对最小值同理。

那么不难设计一个 $\Theta(n^2\cdot 3^k)$ 的 DP：令 $f(i,j,s)$ 为当前考虑 $1\sim i$，选了 $j$ 个点，其中我们计入了哪些贡献（你显然不能重复加减）的最大权值。转移显然。这里 $k=4$，当然等于 $2$ 也可以。

这个时候你就考虑降复杂度。对于背包来说这已经是最优复杂度了，但是如果我们当成背包来做，无形中就是将问题一般化了，我们需要考虑这道题的性质。

一种想法是，考虑到只有 $4$ 个特殊物品，其他的物品都是平凡的，然后贪心的选择。但是我赛场上不是很知道这个东西怎么写。

但是感性理解一下认为这个东西是凸的，写一个 wqs 二分可以通过。严谨证明不会，若有证明/证伪请联系。

时间复杂度是 $\Theta(n\log V\cdot 3^k)$ 的，代码很好写。

---

## 作者：int_R (赞：1)

PNR#8 T2，感觉还是有些许趣味的。

首先如果没有那些关于坐标的贡献，肯定是选出来前 $k$ 个最优。而关于坐标的贡献最多出现在 $4$ 个点上，所以答案一定是形如选出来前 $k-s$ 个点，再在后 $n-(k-s)$ 个点中选出来 $s$ 个点，其中 $s\in[0,\min(4,k)]$。

于是我们考虑钦定一些点的坐标给答案贡献。比方说我们钦定选出来了点 $i$ 并且给答案一个 $X_i$ 的贡献，但其实我们不需要保证 $X_i=X_{\max}$，因为对于同一种选择方案，当你钦定 $X_{\max}$ 给正贡献，$X_{\min}$ 给负贡献的时候答案一定是最大的。

于是可以设计 DP，$g_{i,s,j}$ 表示在 $i\sim n$ 这些点中，选出来了 $s$ 个点，$j$ 是状压了四种特殊贡献有没有被钦定过。转移的时候枚举 $16$ 种状态，即钦定当前点 $i$ 给某些特殊贡献。

然后对前缀同样做一遍，不过不用记选出来过多少个点了，然后就做完了。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#define ll long long
using namespace std;
const int MAXN=2e5+10;
int n,k;struct node{int x,y,c;}t[MAXN];
ll f[MAXN][16],g[MAXN][5][16],s[MAXN],ans;
inline bool cmp(node x,node y){return x.c>y.c;}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i)
        cin>>t[i].x>>t[i].y>>t[i].c;
    sort(t+1,t+1+n,cmp);
    if(k==1){cout<<t[1].c<<'\n';return 0;}
    memset(f,-0x3f,sizeof(f)),f[0][0]=0;
    memset(g,-0x3f,sizeof(g)),g[n+1][0][0]=0;
    for(int i=1;i<=k;++i) s[i]=s[i-1]+t[i].c;
    for(int i=1;i<=k;++i) for(int j=0;j<16;++j)
    {
        if((j&3)==3||(j&12)==12) continue;ll cur=0;
        if(j&1) cur-=t[i].x;if(j&2) cur+=t[i].x;
        if(j&4) cur-=t[i].y;if(j&8) cur+=t[i].y;
        for(int k=0;k<16;++k) if(!(j&k))
            f[i][j|k]=max(f[i][j|k],f[i-1][k]+cur);
    }
    for(int i=n;i>=min(1,k-4);--i) 
    {
        memcpy(g[i],g[i+1],sizeof(g[i]));
        for(int j=0;j<16;++j)
        {
            if((j&3)==3||(j&12)==12) continue;ll cur=t[i].c;
            if(j&1) cur-=t[i].x;if(j&2) cur+=t[i].x;
            if(j&4) cur-=t[i].y;if(j&8) cur+=t[i].y;
            for(int o=0;o<4;++o)
            {
                for(int k=0;k<16;++k) if(!(j&k))
                    g[i][o+1][j|k]=max(g[i][o+1][j|k],g[i+1][o][k]+cur);
            }
        }
    }
    for(int o=0;o<=4&&k-o>=0;++o) for(int i=0;i<16;++i)
        ans=max(ans,f[k-o][i]+g[k-o+1][o][15^i]+s[k-o]);
    cout<<ans<<'\n';return 0;
}
```

---

