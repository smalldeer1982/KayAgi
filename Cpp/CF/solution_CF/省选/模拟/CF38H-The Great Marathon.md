# The Great Marathon

## 题目描述

- 在一个 $n$ 个点，$m$ 条边的无向连通图（有边权）上，有 $n$ 个运动员参加马拉松。
- 第 $i$ 个运动员起点为 $i$ 号点，每个运动员有自己的终点，终点可以为起点外的任何一点，多个运动员可以对应同一个终点。
- 每个运动员走最短路径抵达终点，用时为途径边权和。计算排名时，用时短的靠前；用时一样则起点编号小的靠前。
- 选择两个数 $g\in [g_1,g_2]，s\in [s_1,s_2]$。取第 $1$ 到第 $g$ 名为金牌，第 $g+1$ 到第 $g+s$ 名为银牌，其余为铜牌。
- 求一共有多少种不同的奖牌分配方案。两个方案不同当且仅当至少有一人获得的奖牌不同。保证答案在 $64$ 位有符号整数的范围内。

## 样例 #1

### 输入

```
3 2
1 2 1
2 3 1
1 1 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 5
1 2 2
2 3 1
3 4 2
4 1 2
1 3 3
1 2 1 1
```

### 输出

```
19
```

## 样例 #3

### 输入

```
3 3
1 2 2
2 3 1
3 1 2
1 1 1 1
```

### 输出

```
4
```

# 题解

## 作者：liangbowen (赞：4)

[problem](https://www.luogu.com.cn/problem/CF38H) & [blog](https://www.cnblogs.com/liangbowen/p/17722018.html)。

远古场翻到的一个不错的题，提供一个好想很多的做法。

---

求出任意两点的路径**在全部路径中是第几个**。然后随便找两个人，钦定他们是 Au 吊车尾与 Cu Rank1。这样子就可以直接求出全部人可以是否可以拿 Au Ag Cu 了。

然后就是傻子 DP 了，往状态里塞 Au 与 Ag 的人数，转移随便转移，方案数即 $\sum\limits_{g1\le i\le g2, s1 \le j\le s2} dp_{n,i,j}$。答案即全部方案数的和。

[code](https://codeforces.com/contest/38/submission/224554197)，时间复杂度 $O(n^5)$ 但常数比较小的。


---

## 作者：mzgwty (赞：3)

题目挺有趣的

首先我们跑一遍 Floyd，求出任意两点间最短路，然后我们记 $l_i=\min\limits_{j\ne i} dis_{i,j}$,$r_i=\max\limits_{j\ne i}dis_{i,j}$

我们可以知道，一个人如果拿了 Au，那么我们可以强制让他的耗时变成 $l_i$，如果他拿了 Cu，那么我们可以强制让他的耗时变成 $r_i$

这样一来，我们就可以 $O(n^2)$ 枚举 Au 线的下界和 Cu 线的上界了

接着我们跑一遍 DP，记 $f_{i,j,k}$ 为前 $i$ 个人中已经有 $j$ 个人拿 Au， $k$ 个人拿 Ag 的方案数，转移时看看这个人能否拿 Au,Ag,Cu，进行转移即可

但这样还不够，这样计算的时候会出现没人刚好是 Au 线或者 Cu 线，所以我们还需要容斥一下，形式上就像二维前缀和转移那样，结果为 $calc(a,c)-calc(a-1,c)-calc(a,c+1)+calc(a-1,c+1)$

另外，题目中说如果时间相同按编号排，我们把 $dis_{i,j}$ 赋成 $dis_{i,j}\times n+i$ 即可

```cpp
inline ll C(ll G,ll B,ll L,ll R) {
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	for(int i=1;i<=n;++i) {
		bool g=0,s=0,b=0;
		for(int j=1;j<=n;++j)
			if(i!=j&&dis[i][j]!=INF) {
				if(dis[i][j]<=G) g=1;
				if(dis[i][j]>=B) b=1;
				if(dis[i][j]>L&&dis[i][j]<R) s=1;
			}
		for(int j=0;j<=n;++j)
			for(int k=0;j+k<=n;++k)
				if(f[i-1][j][k]) {
					if(g) f[i][j+1][k]+=f[i-1][j][k];
					if(s) f[i][j][k+1]+=f[i-1][j][k];
					if(b) f[i][j][k]+=f[i-1][j][k];
				}
	}
	ll ans=0;
	for(int i=g1;i<=g2;++i)
		for(int j=s1;j<=s2;++j)
			ans+=f[n][i][j];
	return ans;
}

inline ll calc(ll G,ll B) {
	return C(G,B,G,B)-C(G-1,B,G,B)-C(G,B+1,G,B)+C(G-1,B+1,G,B);
}
```

---

## 作者：Hoks (赞：2)

## 前言
CF 远古好题。

摘自 [杂题选做](https://www.luogu.com.cn/training/597433)。
## 思路分析
$n$ 这么小，不妨想的暴力一点。

既然跑步走的是最短路，那么我们直接给最短路搞出来就行了。

接着我们发现计算方案时运动员跑到哪个点是**不重要**的。

**这并不会区分方案。**

也就是最短路的长度的具体值是不重要的，我们只关心一个**偏序**的问题。

那如果说我们要**尝试**给一个运动员金牌，直接拉到极限让他跑他**可能的最短的路程**就行了。

也就是对于运动员 $i$，他可能跑的路程最小/大值若是 $l_i,r_i$ 的话，如果我们要尝试给他金牌，那么就直接让他跑 $l_i$ 的距离即可，如果这都不行就说明他不可能拿金牌了。

类似的铜牌我们可以这样处理。

通过这样的思考，我们考虑直接钦定金牌线和银牌线来做。

这样的话我们就限定住了左右的两个端点，设这两个端点为 $L,R$，那么对于 $l_i<L$ 的人就能拿金牌，$r_i>R$ 的人就能拿铜牌。

这个时候我们还要判断一下一个人能不能拿银牌，也就是他能不能跑的距离 $x\in(L,R)$。

这个也是好处理的，我们找到这个人能跑的 $\min(x),x>L$ 即可。

如果 $x<R$，那么就是他可以拿银牌。

这个时候记得特判一下，我们钦定的两个人是只能拿固定的牌的。

然后注意到题目里说两个人如果距离相同，比起始点。

这个也是好处理的，我们直接给距离乘 $n$ 再加上起始点编号就可以对比了，本质而言，这种 trick 就是在状压。

最后考虑怎么数数，$f_{i,j,k}$ 表示前 $i$ 个人 $j$ 个金牌，$k$ 的银牌的方案数，根据上面的是否能转移转一下，最后直接遍历可能的金牌/银牌数量加就行了。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=50+10,V=1e6,M=35,INF=1e9+10,mod=1e9+7;
int n,m,ans,l1,l2,r1,r2,mx[N],mn[N],md[N],d[N][N],f[N][N][N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline void calc(int l,int r)
{
	memset(f,0,sizeof f);f[0][0][0]=1;
	for(int i=1;i<=n;i++)
	{
		int g=0,s=0,b=0;
		if(mn[i]==l) g=1;
		else if(md[i]==r) s=1;
		else
		{
			if(mn[i]<l) g=1;
			if(md[i]<r) s=1;
			if(mx[i]>r) b=1;
		}
		for(int j=0;j<=i;j++)
			for(int k=0;j+k<=i;k++)
			{
				if(j&&g) f[i][j][k]+=f[i-1][j-1][k];
				if(k&&s) f[i][j][k]+=f[i-1][j][k-1];
				if(b) f[i][j][k]+=f[i-1][j][k];
			}
	}for(int i=l1;i<=r1;i++) for(int j=l2;j<=r2;j++) ans+=f[n][i][j];
}
inline void solve()
{
	n=read();m=read(),memset(d,0x3f,sizeof d);for(int k=1;k<=n;k++) d[k][k]=0;
	for(int i=1,u,v,w;i<=m;i++) u=read(),v=read(),w=read(),d[v][u]=d[u][v]=min(d[u][v],w);
	l1=read();r1=read(),l2=read(),r2=read();
	for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
		d[i][j]=min(d[i][j],d[i][k]+d[k][j]);memset(mn,0x3f,sizeof mn);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) d[i][j]=d[i][j]*n+i-1;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(i!=j) mn[i]=min(mn[i],d[i][j]),mx[i]=max(mx[i],d[i][j]);
	for(int i=1;i<=n;i++)
	{
		memset(md,0x3f,sizeof md);
		for(int j=1;j<=n;j++) if(i!=j)
			for(int k=1;k<=n;k++) if(k!=j&&d[j][k]>mn[i])
				md[j]=min(md[j],d[j][k]);
		for(int j=1;j<=n;j++) if(j!=i) calc(mn[i],md[j]);
	}print(ans);
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：Reunite (赞：1)

怎么说呢，还是一下子对 $n=50$ 这种范围不够敏感。

## 一
---

注意到我们只在乎金银铜的获得情况，而不关心具体的路径长度，因此我们可以考虑钦定两个人，使其为金牌最低线和铜牌最高线。我们**钦定**这两个人的用时为：

$$mn\_time_{u}=\min_{w \neq u}dis_{u,w}$$

$$mx\_time_{v}=\min_{w \neq v}dis_{v,w}$$

考虑为什么这样是对的。我们纵观所有的得牌情况，以金牌线为例，如果有一个人能取得的 $mn\_time$ 要比钦定的大，但他拿了金牌，看似不合法，但我们只是在这种情况下没有计入，在钦定他自己作为金牌线时则能够计入，因此是不重不漏的。

---
## 二
---

剩下的就简单了，钦定完分数线后，预处理每个人是否能获得金牌、银牌、铜牌。暴力设 $f_{i,j,k}$ 表示前 $i$ 个人，获得了 $j$ 枚金牌，$k$ 枚银牌，转移是朴素的。

总时间复杂度为 $O(n^5)$，带上 $\frac{1}{8}$ 的常数，所以很稳。代码就不放了。

---

