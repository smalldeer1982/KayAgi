# Reunion

## 题目描述

据悉，2050 大会将于4月23日至25日在杭州云栖小镇举行，包括主题论坛、晨跑、露营等活动。

大会有 $n$ 个志愿者 , 他们之间的关系可以用一棵 $n$ 的点的树描述 . 第 $i$ 个结点代表第 $i$ 个志愿者 . 定义树上两点间距离 $\mathrm{dis}(u,v)$ 为为他们之间的最短路径所经过的边数 .

现在他们想进行一场聚会 , 一些志愿者有空参加 , 而其它的正忙 . 在这种情况下 , 对于某个志愿者 $x$ 和非负整数 $r$ , 如果所有与 $x$ 的距离不超过 $r$ 的志愿者**全部**有空参加 , 那么可以召开一场以 $x$ 为中心 , 半径为 $r$ 的聚会 . 这场聚会的等级定义为所有可能的半径 $r$ 中的**最大值** . 

每一个志愿者都有 $\frac12$ 的概率有空参加或者正忙 . 现在请你求出所有情况下聚会等级的**期望**对 $998\ 244\ 353$ 取模的结果 . 特别的 , 当所有志愿者都正忙时 , 该聚会的等级为 $-1$ ; 当所有志愿者都有空参加时 , 该聚会的等级为 $n$ .

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
499122177```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
3 5```

### 输出

```
249561089```

## 样例 #3

### 输入

```
10
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10```

### 输出

```
821796866```

# 题解

## 作者：pigstd (赞：15)

#### [CF1517F Reunion](https://www.luogu.com.cn/problem/CF1517F)

下文中，令有空的志愿者为白点，反之为黑点。 

遇到这种期望必然转换成所有情况的和除以方案数。

然后肯定要转换成对于每个 $i\ (1 \le i < n)$，求 $r \ge i$ 的方案数，然后全部加起来即可。

对于每个 $i$，若 $dis(u,v) \le i$，那么称 $u,v$ 互相控制。那么如果一个方案的 $r\ge i$，那么相当于存在一个点 $u$，他所有的控制的点都是白点。

这个玩意很难搞，需要再一步的转化。正难则反，不难发现，如果一个方案的 $r< i$，就意味着每一个点都会被至少一个黑点控制，即被黑点控制的集合就是全集。

然后就不难设计出一个树形 dp：$dp_{u,i}$ 表示点 $u$ 的子树中，若 $i\ge 0$ 表示 $u$ 的子树（包括 $u$ 本身）都全部被覆盖并且与 $u$ 相距为 $i$ 的点也都被覆盖，$i < 0$ 则表示在 $u$ 的子树中，深度最深的没有被覆盖的节点的深度为 $-i$（$u$ 的深度为 $1$），转移的时候，对于 $u \to v$ 的边，那么对于 $dp_{u,x}$ 和 $dp_{v,y}$，如果 $x+y-1 \ge 0$，那么相当于是第一种情况，就转移到 $tmp_{\max(x,y-1)}$ 上。否则就是第二种情况，转移到 $tmp_{\min(x,y-1)}$ 上。初始化的时候令 $dp_{u,-1}=dp_{u,i}=1$ 即可（分别对应是否是黑点）。

然而这样做是 $\mathcal{O}(n^4)$ 的，考虑优化这个树上背包的过程。实际上不难注意到，对于一个点 $u$，使得 $dp_{u,i} \ne 0$ 的 $i$ 是 $sz_u$ 级别的（实际上是 $u$ 中深度最大的点的深度级别的，但是这个东西上界是 $sz_u$），那么用一个 `set` 维护不为 $0$ 的 $i$，树上背包的复杂度就可以变为 $\mathcal{O}(n^2)$，总复杂度 $\mathcal{O}(n^3)$。

注意到全白是 $n$ 全黑是 $-1$，但是我们算出来全白的贡献会是 $n-1$ 全黑是 $0$，所以总和是不变的不用管就行了。

[code](https://codeforces.com/contest/1517/submission/128314249)。

---

## 作者：zyc2003 (赞：15)

#### 写在前面

这道题花了我一个上午+一个下午一共 $9h$ 的时间 , 已经要被抬走了 ; 官方题解没有代码还没有转移方程 , 这让我这种理解能力差的蒟蒻如何是好 ... 

本篇题解思路来源于官方题解 , 但是大部分内容都是自己想的 (因为题解太简略了)

但是应该和出题人思路不一致 , 因为我这个做法怎么想都优化不到 $\mathcal O(n^2\log n)$ , 而题解提了一嘴 : "It is possible to optimize it to $\mathcal O(n^2\log n)$ further" . 

#### 题意简述

在一棵 $n$ 个点的树上 , 每个结点有一个志愿者 ; 现在要召开一场会议 , 每一个志愿者有 $1/2$ 的可能参加 , 也有 $1/2$ 的可能不参加 , 不难看出有 $2^n$ 种情况 ; 对于每一种情况下的会议 , 我们可以有多种方案展开会议 , 即任意选定一个志愿者 $x$ 所在结点为会议中心 , 如果与 $x$ 的树上距离 $\leq r$ 的结点内的志愿者**都**参加了该会议 , 那么该方案 $(x,r)$ 合法 ; 该情况下的会议的会议半径定义为所有合法的 $(x,r)$ 的**最大的** $r$ . 

请求出会议半径的期望值 , 对 $998\ 244 \ 353$ 取模 . 

#### 解题策略

我们发现对于每一种情况 , 我们很难确定令这场会议的会议半径最大的 $x$ . 这就意味着我们几乎无法通过枚举会议中心 $x$ 来求得总情况数 .

于是我们转变策略 , 既然确定 $x$ 很困难 , 那么通过确定每一个 $r$ 来求总情况数呢 ?  

对于一种情况 , 正向考虑的话 , 即**存在**一个结点 $x$ , 与它距离为 $r$ 以内的点上的志愿者都参加会议 . "存在"有点难整 , 那么逆向考虑呢 ? 我们定义 : 没有参加的志愿者的结点**被染成黑色** . 那么对于被染色的结点 , 与它距离 $\leq r$ 的其它未被染色结点是不可能成为半径为 $r$ 的会议中心的 ; 于是我们定义 $B_{u,r}=\{v|dis(u,v)\leq r\}$ , 那么对于所有被染色的 $u$ , $B_{u,r}$ 内的点不能成为会议中心 ; 

好戏来了 ! 那么 , 如果所有被染色的 $u$ 的 $B_{u,r}$ 的**并集**包括了所有点 , 这就意味着该情况的半径一定不为 $r$ . 确切的说 , 是一定 $< r$ . 我们没有达成求出单独的 $r$ 的目的 , 但是通过这种方法却能求出 $<r$ 的所有情况 , 在通过差分 , 就能求出每一个 $r$ 对应的情况数了 . 

于是问题转变为 : 对于一个 $r$ , 有多少的方案 , 使得 $B_{u,r}$ 之并包括所有点 ? 换句话说 , 一个**被染色**结点能覆盖与其距离 $\leq r$ 的所有点 , 请求出所有点都被覆盖的方案数 . 

方案数嘛 , 那肯定是要 dp 的 . 问题在于如何设计 dp 方程 . 我们需要的方程 , 应该拥有以下信息 : 

$1.$ 从 $u$ 的子树向 $u$ 转移时 , $u$ 是否染色会对子树的方案造成什么影响 ;

$2.$ $u$ 的不同子树之间 , 已染色的结点是否会覆盖其它子树的未覆盖结点 . 

而我们发现 , 这个影响其实只和**深度**有关 . 覆盖到未覆盖的结点 , 只会是一个子树内**最浅的**已染色结点对另一个子树造成影响 ; 而一个子树内只有**最深的**未覆盖结点被覆盖 , 这个子树的所有结点才会被**全部覆盖** , 所以 :

我们设 $u$ 的深度为 $\mathrm{dep}_u$ , $u$ 子树内所有结点的最大深度为 $\mathrm{maxdep}_u$ . 

设 $f_{u,d}$ 表示 $u$ 为根的子树中 , 有一些点未被覆盖 , 且**最深的**未被覆盖的点的深度为 $d$ 时的方案数 ; 

设 $pre_{u,d}$ 表示 $u$ 为根的子树中 , 有一些点未被覆盖 , 且未被覆盖的点的深度为 $\leq d$ 时的方案数 ; 它是 $f$ 的前缀和 ;

设 $g_{u,d}$ 表示 $u$ 为根的子树中 , 所有结点均被覆盖 , 且**最浅的**染成黑色的点的深度为 $d$ 时的方案数 ;

设 $suf_{u,d}$ 表示 $u$ 为根的子树中 , 所有结点均被覆盖 , 且染成黑色的点的深度为 $\geq d$ 时的方案数 ; 它是 $g$ 的后缀和 ;

(前排提示 , 在求 $pre$ 和 $suf$ 时 , 推荐求出 $pre_{u,1\sim 2n}$ 和 $suf_{u,1\sim 2n}$ , 详情见下文"细节处理")

#### 方程推导

首先我们考虑 $u$ 为根的子树内 , 对于两个点不属于同一棵子树的 $x,y$ , $x$ 未被覆盖 , $y$ 被染成黑色 , 那么它们深度关系为何时 , $y$ 能/不能覆盖 $x$ . 

若 $\mathrm{dep}_x-\mathrm{dep}_u+\mathrm{dep}_y-\mathrm{dep}_u\geq r+1$ : 

此时 $y$ 无法覆盖 $x$ , 即 : 

$$\mathrm{dep}_y \geq 2\mathrm{dep}_u-\mathrm{dep}_x+r+1$$

若 $\mathrm{dep}_x-\mathrm{dep}_u+\mathrm{dep}_y-\mathrm{dep}_u\leq r$ : 

此时 $y$ 可以覆盖 $x$ , 即 : 

$$\mathrm{dep}_x \leq 2\mathrm{dep}_u-\mathrm{dep}_x+r$$

那么下面进行推导 : 


$1.$ 对于 $d=\mathrm{dep}_u$ : 

$$f_{u,d}=\prod_{v\in \mathrm{son}_u} suf_{v,\mathrm{dep}_u+r+1}$$

此时 , 最深的未覆盖的结点为 $u$ , 那么 $u$ 一定不被染色 , 且子树中最浅的被染色的结点与其距离 $\geq r+1$ . 

而对于 $g_{u,d}$ 而言 :

$$g_{u,d}=\prod_{v\in \mathrm{son}_u} (pre_{v,\mathrm{dep}_u+r}+suf_{v,\mathrm{dep}_v})$$

此时 , 最浅的被染色的结点为 $u$ , 那么 $u$ 一定被染色 , 且子树中最深的未被覆盖的结点与其距离 $\leq r$ , 或者是不存在未被覆盖的结点 . 

$2.$ 对于 $\mathrm{dep}_u < d \leq \mathrm{dep}_u+r$

在这个区域内 , 如果对 $u$ 染色 , 则 $u$ 可以**覆盖所有结点** ;

如果 $u$ **被染色** : 

那么 $f_{u,d}$ 没有值 , 而 $g_{u,d}$ 也没有值 . 

如果 $u$ **不被染色** : 根据上面的讨论设 $d'=2*\mathrm{dep}_u-d+r+1$

$$f_{u,d}=\prod_{v\in \mathrm{son}_u}(pre_{v,d}+suf_{v,d'})-\prod_{v\in \mathrm{son}_u}(pre_{v,d-1}+suf_{v,d'})$$

我们使用容斥 . $u$ 的每一个子树 $v$ 内任选最深的未覆盖结点 $\leq d$ 或者是最浅的染色点 $\geq d'$ , 这样 $u$ 的最深未覆盖结点深度在 $\mathrm{dep_u}\sim d$ 内 , 或者是没有未被覆盖的结点 ; 那么我们减去多余情况 , 使得只剩下 $u$ 的最深未覆盖结点深度为 $d$ 的情况 . 

根据上面的讨论 , 重新设 $d'=2*\mathrm{dep}_u-d+r$ . 这里要注意 , $u$ 一定被覆盖了吗 ? 由于 $d-\mathrm{dep}_u\leq r$ , 所以 $u$ 一定会被覆盖 , 无需担心 .

$$g_{u,d}=\prod_{v\in \mathrm{son}_u}(suf_{v,d}+pre_{v,d'})-\prod_{v\in \mathrm{son}_u}(suf_{v,d+1}+pre_{v,d'})$$

仍然是容斥 . $u$ 的每一个子树 $v$ 内任选最浅的染色点 $\geq d$ 或者是最深的未覆盖结点 $\leq d'$ , 这样 $u$ 的最浅染色结点深度在 $d\sim\mathrm{maxdep}_u$ 内 , 或是仍有没有被覆盖的结点 ; 那么我们减去多余情况 , 使得只剩下 $u$ 的最浅已染色结点深度为 $d$ 的情况 . 

$3.$ 对于 $\mathrm{dep}_u +r< d \leq \mathrm{maxdep}_u$

现在 $u$ 是否染色对 $f_{u,d}$ 已经没有了影响 . 所以仍然设 $d'=2*\mathrm{dep}_u-d+r+1$ :

$$f_{u,d}=2\Big(\prod_{v\in \mathrm{son}_u}(pre_{v,d}+suf_{v,d'})-\prod_{v\in \mathrm{son}_u}(pre_{v,d-1}+suf_{v,d'})\Big)$$

那么 $g_{u,d}$ 呢 ? 那肯定还是不能染色的 , 所以最浅的染色结点必须满足 $d-\mathrm{dep}_u\leq r$ , 即 $\mathrm{dep}_u+r\geq d$ , 和 $\mathrm{dep}_u +r< d$ 矛盾 , 故 $g_{u,d}$ 无值 . 如果染色 ? 那么最浅的染色结点肯定是 $u$ 嘛 , 亦不合法 . 


至此讨论完毕 . 

至于复杂度 ? 枚举 $r$ 是 $\mathcal O(n)$ 的 , 转移是 $\mathcal O(n^2)$ 的 , 总复杂度为 $\mathcal O(n^3)$ . 

#### 细节处理

$1.$ 前缀和和后缀和都要求到 $2*n$ , 是因为方程中的 $d'$ 可能会越界超过 $n$ . 这样做事保险起见(其实是懒得分析) , 当然从实际意义上来说这样求也没有错 . 

$2.$ 叶子结点直接赋值就好 (边界情况)

$3.$ 转移虽然复杂 , 但是严格按照方程来肯定没问题(大概

$4.$ 其它细节 ? 貌似没了 

#### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned int ui;

ll read() {
	ll x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
void write(ll x) {
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+48);
}
void writes(ll x) {write(x),putchar(' ');}
void Writes(ll x) {write(x),putchar('\n');}

#define N 605
#define M 1220
#define mod 998244353

int Qpow(int x,int p) {int res=1;for(;p;p>>=1,x=1ll*x*x%mod)if(p&1)res=1ll*res*x%mod;return res;}
int Inv(int x) {return Qpow(x,mod-2);}

int n;
int head[N],nxt[M],ver[M],tot=1;
void add(int x,int y) {ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;}
int f[N][N],pre[N][N];
int g[N][N],suf[N][N];
int mulf[2],mulg[2];
int dep[N],maxdep[N];
bool isleaf[N];
int ans[N];
int tans;

void Reset() {
	for(int i=1;i<=n;++i)
		for(int j=dep[i];j<=maxdep[i];++j)
			f[i][j]=g[i][j]=0,pre[i][j]=suf[i][j]=0;
}

void dfs(int x,int fa) {
	maxdep[x]=dep[x]=dep[fa]+1;
	for(int i=head[x];i;i=nxt[i]) {
		int y=ver[i];
		if(y == fa)	continue;
		dfs(y,x);
		maxdep[x]=max(maxdep[x],maxdep[y]);
	}
	if(maxdep[x] == dep[x])
		isleaf[x]=1;
}

void treedp(int x,int fa,int r) {
	int d=dep[x];
	if(isleaf[x] == 1) {
		f[x][d]=1,g[x][d]=1;
		for(int d=1;d<=2*n;++d) 
			pre[x][d]=(1ll*pre[x][d-1]+1ll*f[x][d])%mod;
		for(int d=2*n;d>=1;--d) 
			suf[x][d]=(1ll*suf[x][d+1]+1ll*g[x][d])%mod;
		return ;
	}
	for(int i=head[x];i;i=nxt[i]) {
		int y=ver[i];
		if(y == fa)	continue;
		treedp(y,x,r);
	}
	//d == dep[x]
	f[x][d]=1,g[x][d]=1;
	for(int i=head[x];i;i=nxt[i]) {
		int y=ver[i];
		if(y == fa)	continue;
		int D;
		D=dep[x]+r+1;
		f[x][d]=1ll*f[x][d]*suf[y][D]%mod;
		D=dep[x]+r;
		g[x][d]=1ll*g[x][d]*(1ll*pre[y][D]+1ll*suf[y][dep[y]])%mod;
	}
	//dep[x] < d <= dep[x]+r
	for(d=dep[x]+1;d<=dep[x]+r;++d) {
		mulf[0]=1,mulg[0]=1;
		mulf[1]=1,mulg[1]=1;
		for(int i=head[x];i;i=nxt[i]) {
			int y=ver[i];
			if(y == fa)	continue;
			int D;
			D=2*dep[x]-d+r+1;
			mulf[0]=1ll*mulf[0]*(1ll*pre[y][d]+1ll*suf[y][D])%mod;
			mulf[1]=1ll*mulf[1]*(1ll*pre[y][d-1]+1ll*suf[y][D])%mod;
			D=2*dep[x]-d+r;
			mulg[0]=1ll*mulg[0]*(1ll*suf[y][d]+1ll*pre[y][D])%mod;
			mulg[1]=1ll*mulg[1]*(1ll*suf[y][d+1]+1ll*pre[y][D])%mod;
		}
		f[x][d]=(mulf[0]-mulf[1])%mod;
		g[x][d]=(mulg[0]-mulg[1])%mod;
	}
	//dep[x]+r < d <= maxdep[x]
	for(d=dep[x]+r+1;d<=maxdep[x];++d) {
		mulf[0]=1,mulf[1]=1;
		for(int i=head[x];i;i=nxt[i]) {
			int y=ver[i];
			if(y == fa)	continue;
			int D;
			D=2*dep[x]-d+r+1;
			mulf[0]=1ll*mulf[0]*(1ll*pre[y][d]+1ll*suf[y][D])%mod;
			mulf[1]=1ll*mulf[1]*(1ll*pre[y][d-1]+1ll*suf[y][D])%mod;
		}
		f[x][d]=2ll*(mulf[0]-mulf[1])%mod;
	}
	//pre and suf
	pre[x][0]=f[x][0];
	for(int d=1;d<=2*n;++d) 
		pre[x][d]=(1ll*pre[x][d-1]+1ll*f[x][d])%mod;
	suf[x][2*n+1]=g[x][2*n+1];
	for(int d=2*n;d>=1;--d) 
		suf[x][d]=(1ll*suf[x][d+1]+1ll*g[x][d])%mod;
}

int solve(int r) {
	Reset();
	treedp(1,0,r);
	return suf[1][1];
}

int main() {
	n=read();
	for(int i=1;i<n;++i) {
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs(1,0);
	for(int i=0;i<=n+1;++i) 
		ans[i]=solve(i);
	tans=1ll*ans[0]*(-1); 
	for(int i=1;i<=n+1;++i) 
		tans=(1ll*tans+1ll*(1ll*ans[i]-1ll*ans[i-1])*(i-1)%mod)%mod;
	tans=(1ll*tans+1ll*1*n)%mod;
	tans=1ll*tans*Qpow(Inv(2),n)%mod;
	Writes((tans%mod+mod)%mod);
	return 0;
}
```

---

## 作者：syksykCCC (赞：9)

用黑点表示这个志愿者没有来，白点表示这个志愿者来了。

定义 $B(u, r) = \{ v \mid \text{dis}(u, v) \le r \}$，也就是距离 $u$ 不超过 $r$ 的结点集合。

首先，我们枚举 $r$，计算有多少种方法满足 $ans \ge r$。 

考虑 $ans$ 的实际意义是什么？存在某一个结点 $u$，对于任意一个黑点 $v$，都有 $\text{dis}(u, v) > ans$。

于是可以想到一种判定方法：如果 $\left(\bigcup\limits_{u\text{ is black}} B(u, r) \right) = \{1, 2, \cdots, n\}$，那么 $ans < r$，反之 $ans \ge r$。

所以现在就是要找出不满足上面这个式子的方案数。可以想到一种 DP，用 $f(u, depth, height)$ 表示 $u$ 的子树，当前未被覆盖的结点最深为 $depth$，以及这棵子树中最浅的黑点可以往上覆盖到的高度是 $height$。直接做的话是 $O(n^3)$ 的。

可以发现一个优化：

1. 如果当前子树中**存在**未被覆盖的结点 $x$，那么 $height$ 是不重要的。

> 这是因为，为了保证所有的点都被覆盖到，$u$ 子树外必然存在另一个黑点 $y$ 满足 $\text{dis}(x, y) \le r$，那么就可以得知，「$u$ 子树中最浅的黑点所能**往上**覆盖到的点集」是「$y$ 所能覆盖到的点集」的子集，自然就不必考虑。

2. 如果当前子树中**不存在**未被覆盖的结点 $x$，那么 $depth$ 是不重要的。

> $depth$ 的含义就是未被覆盖的结点的最大深度，既然没有这样的点，那自然不重要。

于是，我们得出了一个结论：$depth / height$ **只会有一者是有意义的**。

于是更改我们的状态，用 $f(u, i)$ 表示在 $u$ 的子树中：

* $i \ge 0$，表示最浅的黑点能往上额外延伸 $i$ 的距离。
* $i < 0$，表示最深的没被覆盖的点离 $u$ 的距离为 $-i-1$。

每个点 $u$ 的 $f(u, i) \ne 0$ 的 $i$ 是 $O(\text{size}(u))$ 的，所以单次 DP 时间复杂度为 $O(n^2)$。转移的写法和树形背包类似，注意复杂度不要写假掉。

总时间复杂度 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define delta (n + 1)
using namespace std;
typedef long long ll;
const int N = 305, M = 605, MOD = 998244353, INV2 = 499122177;
int n, m, r, f[N][M], ans;
void Add(int &x, int y) { if((x += y) > MOD) x -= MOD; }
vector<int> G[N];
vector<pair<int, int>> tmp1, tmp2;
void Dp(int u, int fa)
{
	fill(f[u], f[u] + m, 0);
	int son = 0;
	for(int v : G[u])
	{
		if(v == fa) continue;
		Dp(v, u); son++;
	}
	f[u][r + delta] = f[u][-1 + delta] = 1;
	if(!son) return;
	for(int v : G[u])
	{
		if(v == fa) continue;
		tmp1.clear(); tmp2.clear();
		for(int i = 0; i < m; i++) if(f[u][i]) { tmp1.pb(mp(i - delta, f[u][i])); f[u][i] = 0; }
		for(int i = 0; i < m; i++) if(f[v][i]) tmp2.pb(mp(i - delta, f[v][i]));
		for(pair<int, int> t1 : tmp1) for(pair<int, int> t2 : tmp2)
		{
			int i = t1.first, j = t2.first, w = (ll)t1.second * t2.second % MOD;
			if(i < 0 && j < 0) Add(f[u][min(i, j - 1) + delta], w);
			if(i < 0 && j >= 0) Add(f[u][(i + j >= 0 ? j - 1 : i) + delta], w);
			if(i >= 0 && j < 0) Add(f[u][(i + j >= 0 ? i : j - 1) + delta], w);
			if(i >= 0 && j >= 0) Add(f[u][max(i, j - 1) + delta], w);
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n; m = n * 2 + 5;
	for(int i = 1; i < n; i++)
	{
		int u, v; cin >> u >> v;
		G[u].pb(v); G[v].pb(u);
	}
	for(r = 1; r < n; r++)
	{
		Dp(1, 0);
		for(int i = 0; i < delta; i++) Add(ans, f[1][i]);
	}
	for(int i = 1; i <= n; i++) ans = (ll)ans * INV2 % MOD;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Little09 (赞：7)

提供一种形式上不大一样的思路。

称“有空”的位置为白点，“正忙”的位置为黑点。首先转化为对每个 $k$ 满足 $1\le k<n$，求 $r\ge k$ 的方案数。这个条件等价于对每个初始的黑点，将其距离 $\le k$ 的点染黑，要求最后至少存在一个白点。容斥一下变成计算不存在白点的方案。

定义数组 $d_i$ 表示 $i$ 到最近的黑点的距离。我们发现一个染色方案唯一对应一组 $d$，同时一组合法的 $d$ 也唯一对应一个染色方案。因此我们只需要计算合法 $d$ 的方案数。容易发现以下条件是一组 $d$ 合法的充要条件：

- 对于边 $(u,v)$，有 $|d_u-d_v|\le 1$；
- 对于点 $u$，要么 $d_u=0$，要么存在一条边 $(u,v)$ 使得 $d_v=d_u-1$。

那么不存在白点，就是需要对于所有 $u$，满足 $d_u\le k$。

直接对 $d$ 做暴力 DP 即可做到 $O(n^3)$。

---

## 作者：Alex_Wei (赞：7)

> H. [CF1517F Reunion](https://www.luogu.com.cn/problem/CF1517F) *3200

一道计数好题。

首先对题目进行第一步转化，设一种方案 $S$（$S$ 表示有空的志愿者的点集）的半径为 $f(S)$，将 $n - 1 + \sum\limits_{r = 1} ^ {n - 1} r \sum\limits_{S \neq \varnothing \land S \neq U} [f(S) = i]$ 改写为 $\sum\limits_{r = 1} ^ {n - 1} \sum\limits_S [f(S)\geq r]$，因为对于一般 DP 限制，大于等于比恰好等于更容易满足。

从差分容斥算半径恰好等于某个值的方案数也可以推得上式，因此问题转化为对每个 $r$ 求解 $\sum\limits_{S} [f(S) \geq r]$。

设有空的点为白点，没有空的点为黑点。

容易发现，一个方案的半径大于等于 $r$ 当且仅当存在一个点使得距离它最近的黑点与它的距离大于 $r$。接下来的一切分析都围绕这个结论展开。

设 $f_{i, j}$ 表示以 $i$ 为根的子树内部距离 $i$ 最近的黑点的距离为 $j$ 的方案数，自然的想法是当 $j = r + 1$ 时就满足了条件。但实际上并非这样，因为 $i$ 只满足了子树内的限制，还没有满足子树外的限制（即 $i$ 子树外距离 $i$ 最近的黑点并不一定距离 $i$ 大于 $r$）。我们记这样的点为 **预备点**，即已经满足子树内距离其最近的黑点与其距离大于 $r$ 的限制，可能成为聚会中心的点。

为此，我们再设 $g_{i, j}$ 表示 $i$ 的子树内最深的预备点与 $i$ 的距离为 $j$ 时的方案数（如果最深的都不满足子树外要求，那么更浅的一定不满足，所以只关心最深的预备点），这样就可以封闭转移了。

注意，$f, g$ 两者是 **互斥** 的，即若子树内已经存在预备点，那么没有必要再考虑距离 $i$ 最近的黑点与 $i$ 的距离。如果不存在时，我们才要记录距离 $i$ 最近的黑点与 $i$ 的距离。这保证计数不重不漏。

我一开始想同时考虑到一个节点的所有儿子，发现根本不可做就弃疗了。实际上，如果从 **合并两棵子树** 的角度分析，问题就变得相当好做。这也说明 **树形 DP 不方便同时考虑所有子节点时，单独考虑合并两棵子树** 是很有用的策略。

初始化很容易，$f_{i, 0} = g_{i, 0} = 1$，分别代表当前点涂成黑点和白点两种选择。

设当前合并节点 $i$ 与其子节点 $u$。

- 合并 $f_{i, j}$ 和 $f_{u, k}$。据定义，距离 $i$ 最近的黑点距离为 $\min(j, k + 1)$，转移到 $f_{i, \min(j, k + 1)}$。
- 合并 $f_{i, j}$ 和 $g_{u, k}$。若 $j + (k + 1) > r$，那么 $u$ 子树内的预备点不会被干扰，转移到 $g_{i, k + 1}$。否则该预备点由于不满足子树外限制被舍弃，转移到 $f_{i, j}$。
- 合并 $g_{i, j}$ 和 $f_{u, k}$。同理，若 $j + (k + 1) > r$ 则转移到 $g_{i, j}$，否则转移到 $f_{i, k + 1}$。
- 合并 $g_{i, j}$ 和 $g_{u, k}$。转移到 $g_{i, \max(j, k + 1)}$。

答案即 $\sum\limits_{i = 0} ^ n g_{root, i}$。

根据转移式，我们发现一个节点的 $f, g$ 有值的部分大小为 $\mathcal{O}(\mathrm{maxdep}(i)) \leq \mathcal{O}(\mathrm{size}(i))$，所以根据树形背包的复杂度分析，一次 DP 的复杂度为 $\mathcal{O}(n ^ 2)$。

综上，总复杂度为 $\mathcal{O}(n ^ 3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 300 + 5;
const int mod = 998244353;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
int n, r, ans, sz[N], f[N][N], g[N][N];
vector <int> e[N];
void dfs(int id, int fa) {
	f[id][0] = g[id][0] = sz[id] = 1; // id 是黑点或白点.
	for(int it : e[id]) {
		if(it == fa) continue;
		dfs(it, id);
		static int ff[N], gg[N];
		memset(ff, 0, sizeof(ff)), memset(gg, 0, sizeof(gg));
		for(int j = 0; j < sz[id]; j++)
			for(int k = 0; k < sz[it]; k++) {
				add(ff[min(j, k + 1)], 1ll * f[id][j] * f[it][k] % mod);
				add(gg[max(j, k + 1)], 1ll * g[id][j] * g[it][k] % mod);
				add(j + k + 1 > r ? gg[k + 1] : ff[j], 1ll * f[id][j] * g[it][k] % mod);
				add(j + k + 1 > r ? gg[j] : ff[k + 1], 1ll * g[id][j] * f[it][k] % mod);
			}
		sz[id] += sz[it];
		memcpy(f[id], ff, sizeof(ff)), memcpy(g[id], gg, sizeof(gg));
	}
}
int main() {
	cin >> n;
	for(int i = 1, u, v; i < n; i++) cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
	for(r = 1; r < n; r++) {
		memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g)), dfs(1, 0);
		for(int j = 0; j < n; j++) add(ans, g[1][j]);
	}
	for(int i = 1; i <= n; i++) ans = 1ll * ans * (mod + 1 >> 1) % mod;
	cout << ans << endl;
	return 0;
}

/*
2022/4/30
start thinking at 16:31

考虑直接求半径 = r 的方案数.
半径 = r 的方案限制考虑点 - 边容斥.
我们希望在数方案数的时候, 任何半径 > r 的方案都不会被数进来, 且包含了所有半径等于 r 的方案.
哦这玩意可以差分容斥掉.

所以我们只要数至少出现一次半径 >= r 的方案数.
设 f_{i, j} 表示以 i 为根的子树, 最近的距离 i 的坏点距离是 j 的方案数.
设 g_{i, j} 表示要满足 i 以外最近的距离 i 的坏点距离 > j 才能使得存在半径 r 的方案数.
似乎可以搞.
再设 h_i 表示以 i 为根的子树已经符合要求的方案数.

看起来很麻烦，有点寄.

看了一下题解.
发现其实扎不多.
不过是容斥了一下.
好像没有容斥, 就是我的定义.
不对就是取了个反.
那我为什么不会转移呢?
因为我没想到直接树形背包做.
我想直接用子树答案直接计算而不是特殊合并.
我是傻逼.

>= 0 表示最深的一个黑点还能向上延伸多远.
< 0 表示距离当前点最深的好点的距离的相反数 (还要减去 1).
树形背包合并, 时间复杂度 n ^ 2.

start coding at 20:21
finish debugging at 20:43

2022/5/3
换了一种自己的理解方式写.
*/
```

---

## 作者：wangsiyuanZP (赞：4)

NOI 前来篇题解积德。貌似是不同的做法，虽然复杂度都是 $n^3$ 的。

这种对最大值求和题肯定要转换成：对 $ans<x$ 的方案数计数。现在要求变为了每个点距离 $k$ 以内的点至少有一个是无法参加的（后文称作 $0$ 点）。这不容易计数，我们**容斥**，钦定一个集合 $S$ 非法，即到 $S$ 中任意一个点的距离 $\le k$ 的点均为 $1$ 点，称这些点被**标记**。对答案的贡献即为：

$$-1^{|S|}\times 2^{-标记点数}$$

我考虑过对 $S$ dp，不过标记的点数难以计算。考虑我们如何标记这些点：设 $S$ 中的点能量为 $k+1$，其他点的能量为周围点的能量的 $\max-1$（下限为 $0$）。~~大概就是红石粉~~。注意到一个合法的能量序列一定和一个 $S$ 成为双射，因为有且只有 $S$ 中的点能量为 $k+1$。同时，能量还可以记录一个点是否标记，将上文式子中的两个指数信息都涵盖了！我们对点的能量 $dp$，同时记录相关系数即可，对于每个能量不为 $0$ 或 $k+1$ 的点，要求旁边至少有一个点能量恰为其能量 $+1$，需要记录一下，具体的转移式可以看代码，并不难推导。

```cpp
// Calm down.
// Think TWICE, code ONCE.
#include<bits/stdc++.h>
#define pb push_back
#define popcnt __builtin_popcountll
#define debug printf("Passed line %d\n", __LINE__)

using namespace std;
typedef long long ll;
typedef vector<int> vint;
typedef pair<int, int> PII;

template<typename T> inline void read(T &x){
	x = 0; bool F = 0; char c = getchar();
	for (;!isdigit(c);c = getchar()) if (c == '-') F = 1;
	for (;isdigit(c);c = getchar()) x = x*10+(c^48);
	if (F) x = -x;
}

template<typename T1, typename... T2> inline void read(T1 &x, T2 &...y){read(x); read(y...);}

template<typename T> inline void checkmax(T &a, const T &b){if (a<b) a = b;}

template<typename T> inline void checkmin(T &a, const T &b){if (a>b) a = b;}

const int N = 305;
const ll MOD = 998244353;
ll dp[N][N][2], pre[N][2];
vector<int> to[N];
int n, k;

void dfs(int u, int fa){
	memset(dp[u], 0, sizeof(dp[u]));
	for (int i = 0;i<k;i++){
		dp[u][i][!i] = 1+!i;
	}
	dp[u][k][1] = MOD-1;
	for (int v: to[u]){
		if (v == fa) continue;
		dfs(v, u);
		swap(dp[u], pre), memset(dp[u], 0, sizeof(dp[u]));
		for (int i = 0;i<=k;i++){
			if (i){
				(dp[u][i][0] += pre[i][0]*(dp[v][i-1][0]+dp[v][i-1][1])) %= MOD;
				(dp[u][i][1] += pre[i][1]*(dp[v][i-1][0]+dp[v][i-1][1])) %= MOD;
			}
			(dp[u][i][0] += pre[i][0]*dp[v][i][1]) %= MOD;
			(dp[u][i][1] += pre[i][1]*dp[v][i][1]) %= MOD;

			(dp[u][i][1] += (pre[i][0]+pre[i][1])*dp[v][i+1][1]) %= MOD;
		}
	}
}

int main(){
	freopen("input.txt", "r", stdin); cerr << "\n\n--------------------------------- Program output ---------------------------------\n";
	read(n); int u, v;
	for (int i = 1;i<n;i++) read(u, v), to[u].pb(v), to[v].pb(u);
	ll ans = 0, mul = 1;
	for (int i = 1;i<=n;i++) (mul *= 2) %= MOD;
	for (k = 2;k<=n+1;k++){
		dfs(1, 0);
		for (int i = 0;i<=k;i++) ans += MOD-dp[1][i][1];
		ans += mul;
	}
	(ans += MOD-1) %= MOD;
	for (int i = 1;i<=n;i++) (ans *= (MOD+1)>>1) %= MOD;
	printf("%lld\n", ans%MOD);
	return cerr << "\n\n\n", 0;
}
/*
self check:
1. long long
2. size of array
3. code for testing
4. initializing
 */
```

---

## 作者：PTqwq (赞：1)

感谢 KingPowers 老师给我讲了这个题。

首先把问题转化成，求答案小于 $r$ 的方案数（最后除以 $2^n$ 就行了，后面说的都是方案数），这样只需要差分一下乘上系数加到贡献里面就行，特判一下答案为 $n$ 的情况，这里只考虑 $0 \leq r \leq n$ 的情况：

记号：把能来的节点叫做白点，不能来的叫做黑点。

显然对于任意一个黑点，假设我们有一个白点使得其方圆距离 $\leq r$ 的点都是白点，那么我们可以考虑一件事情，就是对于一个黑点，那么与这个点距离小于等于 $r$ 的点都不可以作为合法的中心，那么问题转化为：**选一些点，所有被选中的点的方圆距离 $\leq r$ 的点的并集为全集的方案数。我们将已经在并集中的点称为已经被覆盖的点。**

考虑一个 DP，设 $f_{0/1, u, d}$ 表示：

- 第一维为 $0$：$u$ 没有被覆盖，$u$ 子树内存在一个点 $d$ 使得其没有被覆盖。
- 第一维为 $1$：$u$ 被覆盖了，$u$ 还可以往外面覆盖距离 $\leq d$ 的点。

这里有另一种情况：如果 $u$ 被覆盖了但是 $u$ 子树内还有一个点 $p$ 没有被覆盖怎么办？此时我们直接将 $u$ 视为没有被覆盖，因为最终被我们统计进入答案的方案一定是全部被覆盖的方案，那一定在 $u$ 的子树外存在一个点 $v$ 可以覆盖掉 $p$，此时 $v$ 覆盖的点集一定严格包含所有 **已经被 $u$ 子树内的点覆盖但是还没有被考虑的点**，所以我们将 $u$ 视为没有被覆盖也是可以的。

然后考虑转移，其实就是分讨一下 $u$ 有没有被覆盖，如果没有，那么就把最深的没有被覆盖的点的深度取个 max，如果被覆盖了，那么把还能覆盖的距离取个 max，这个容易用前缀和优化做到单次 $O(n^2)$，$r$ 的个数是 $O(n)$ 量级的，所以总时间复杂度 $O(n^3)$，可以通过。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

namespace PTqwq {

int readqwq() {
    int x = 0;
    bool f = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) f |= (c == '-');
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
    if (f) {
        x = -x;
    }
    return x;
}

ll readllqwq() {
    ll x = 0;
    bool f = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) f |= (c == '-');
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
    if (f) {
        x = -x;
    }
    return x;
}

const ll mod = 998244353;
const ll Inv2 = 499122177;

ll PowerQ(ll a, ll b) {
    ll x = 1;
    for (; b > 0; b /= 2, a = a * a % mod) {
        if (b % 2 == 1) {
            x = x * a % mod;
        }
    }
    return x;
}

int n, curd;
vector<int> g[340];
ll f[2][340][340], dp[2][340];

void dfs(int u, int fa) {
    f[0][u][0] = 1;
    f[1][u][curd] = 1;
    for (auto v : g[u]) {
        if (v != fa) {
            dfs(v, u);
            for (int U = 0; U <= n + 1; ++ U) {
                dp[0][U] = 0;
                dp[1][U] = 0;
            }
            ll sumx = 0, sumy = 0;
            for (int U = 0; U <= n; ++ U) {
                sumx = (sumx + f[0][u][U]) % mod;
                if (U >= 1) {
                    sumy = (sumy + f[0][v][U - 1]) % mod;
                }
                dp[0][U] = sumx * sumy % mod;
            }
            for (int U = n; U >= 1; -- U) {
                dp[0][U] = (dp[0][U] + mod - dp[0][U - 1] % mod) % mod;
            }
            sumx = 0, sumy = f[1][v][0];
            for (int U = 0; U <= n; ++ U) {
                sumx = (sumx + f[1][u][U]) % mod;
                if (U + 1 <= n) {
                    sumy = (sumy + f[1][v][U + 1]) % mod;
                }
                dp[1][U] = sumx * sumy % mod;
            }
            for (int U = n; U >= 1; -- U) {
                dp[1][U] = (dp[1][U] + mod - dp[1][U - 1] % mod) % mod;
            }
            sumx = 0;
            for (int U = 0; U <= n; ++ U) {
                sumx = (sumx + f[1][v][U]) % mod;
                dp[0][U] = (dp[0][U] + f[0][u][U] * sumx % mod) % mod;
            }
            sumx = 0;
            for (int V = 1; V <= n; ++ V) {
                sumx = (sumx + f[0][u][V - 1]) % mod;
                dp[1][V - 1] = (dp[1][V - 1] + sumx * f[1][v][V] % mod) % mod;
            }
            sumx = 0;
            for (int U = 0; U <= n; ++ U) {
                if (U - 1 >= 0) {
                    sumx = (sumx + f[0][v][U - 1]) % mod;
                }
                dp[1][U] = (dp[1][U] + f[1][u][U] * sumx % mod) % mod;
            }
            sumx = 0;    
            for (int V = 0; V < n; ++ V) {
                sumx = (sumx + f[1][u][V]) % mod;
                dp[0][V + 1] = (dp[0][V + 1] + sumx * f[0][v][V] % mod) % mod;
            }
            for (int U = 0; U <= n; ++ U) {
                f[0][u][U] = dp[0][U];
                f[1][u][U] = dp[1][U];
            } 
        }
    }
}

void Solve() {
    n = readqwq();
    for (int i = 1; i < n; ++ i) {
        int u = readqwq();
        int v = readqwq();
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ll ans = 0, val = 0;
    for (ll i = 0; i <= n; ++ i) {
        curd = i;
        for (int j = 0; j <= n; ++ j) {
            for (int k = 0; k <= n + 1; ++ k) {
                f[0][j][k] = 0;
                f[1][j][k] = 0;
            }
        }
        dfs(1, 0);
        ll cur = 0;
        for (int j = 0; j <= i; ++ j) {
            cur = (cur + f[1][1][j]) % mod;
        }
        ans = (ans + (cur + mod - val % mod) % mod * ((i + mod - 1) % mod) % mod) % mod;
        val = cur;
    }
    ans = (ans + 1ll * n) % mod;
    for (int i = 1; i <= n; ++ i) {
        ans = ans * Inv2 % mod;
    }

    printf("%lld\n", ans);
}

}

int main() {
    PTqwq::Solve();

    return 0;
}
```

---

## 作者：xzCyanBrad (赞：1)

[Video editorial](https://www.bilibili.com/video/BV1uK4ZeuEU5/)

下面设 $l(S)$ 为当 $S$ 集合里的人有空时的 Level。答案的 $2^n$ 倍为
$$
\begin{aligned}
&n+(-1)+\sum_{r=1}^{n-1}r\sum_S[l(S)=r]\\
=&\sum_{r=1}^{n-1}\sum_S[l(S)\ge r]
\end{aligned}
$$
枚举 $r$，那么后面的求和式即有下面的组合意义：将树黑白染色，存在一个黑点，其最近的白点与其距离至少为 $r$。发现这个“最近”，不仅有孩子，还有祖先，甚至还有祖先开叉的边，怎么处理呢？

考虑树形 dp。$f(u,i)$ 表示，以 $u$ 点为根的子树内，离 $u$ 点最近的白点，距离 $u$ 为 $i$，答案的期望；$g(u,i)$ 类似，只是变成离 $u$ 点最远的可以用的黑点。注意 $g$ 严格 Override $f$，即如果有活着的黑点必然先要那个黑点。

转移时先设 $f(u,0)=f(v,0)=\frac12$。然后考虑每次合并入一个 $u$ 的儿子 $v$：

- $f(u,\min(i,j))\leftarrow f(u,\min(i,j))+f(u,i)f(v,j-1)$
- $g(u,\max(i,j))\leftarrow g(u,\max(i,j))+g(u,i)g(v,j-1)$
- $\begin{cases}g(u,j)\leftarrow g(u,j)+f(u,i)g(v,j-1),&i+j>r\\f(u,i)\leftarrow f(u,i)+f(u,i)g(v,j-1),&i+j\le r\end{cases}$
- $\begin{cases}g(u,i)\leftarrow g(u,i)+g(u,i)f(v,j-1),&i+j>r\\f(u,j)\leftarrow f(u,j)+g(u,i)f(v,j-1),&i+j\le r\end{cases}$

注意每次转移前要用一个空数组拷贝，因为概率每次都要减半。这四个转移其实都很好理解，但是需要画图，所以就录了视频题解。

最后答案就是 $\sum_i g(u,i)$，因为到了根上面没有祖先了。复杂度为 $\Theta(n\times (\sum_u\text{len}_u)^2)$，其中 $\text{len}_u$ 为以 $u$ 为根的子树内最大深度。显然 $\text{len}_u\le \text{sz}_u$，所以复杂度是稳稳的 $\Theta(n^3)$，$n\le 300$ 已经足够。

**Bonus**（$n\le 1000$）：注意到这个是一个关于深度有关的东西，所以可以考虑前缀和优化并长剖，可以做到 $\Theta(n^2\log n)$。

---

## 作者：dAniel_lele (赞：1)

考虑将问题转化为对于每个 $r$，求出不存在一个点使得与其距离小于等于 $r$ 的所有点都有志愿者。

对于每个子问题（即，每个 $r$），考虑 $dp_{i,j,0/1}$。

* 第三维为 $0$ 时，表示考虑到 $i$ 子树，距离该点最近的一个没被选的点距离为 $j$ 的概率；
* 第三维为 $1$ 时，表示考虑到 $i$ 子树，要求在上方有一个距离该点小于等于 $j$ 的没被选的点的概率。

考虑转移，合并 $dp_{a,x,i}$ 和 $dp_{b,y,j}$。

* $x<y$ 时：$dp_{a,x,i}\times dp_{b,y,j}\to dp_{c,y,j}$；
* $x>y$ 时：$dp_{a,x,i}\times dp_{b,y,j}\to dp_{c,x,i}$；
* $x=y$ 时：$dp_{a,x,i}\times dp_{b,y,j}\to dp_{c,x,i\operatorname{and}j}$。

注意到可以使用前缀和优化，单次复杂度 $O(n^2)$，总复杂度 $O(n^3)$，可以通过。

为了方便转移，可以在 dfs 结尾将目前的状态适配直接上一层与子树合并。初始状态 $dp_{now,0,0}=dp_{now,r,1}=\frac{1}{2}$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
const int mod=998244353,inv2=(mod+1)/2;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1; 
	}
	return ans;
}
int dp[305][305][2];
vector<int> vc[305];
int r;
void dfs(int now,int fa){
	dp[now][0][0]=inv2;
	dp[now][r][1]=inv2;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
		int sufnow[305][2],sufv[305][2],tmp[305][2];
		memset(sufnow,0,sizeof(sufnow));
		memset(sufv,0,sizeof(sufv));
		memset(tmp,0,sizeof(tmp));
		for(int i=0;i<=r;i++) sufnow[i][0]=dp[now][i][0],sufnow[i][1]=dp[now][i][1],sufv[i][0]=dp[v][i][0],sufv[i][1]=dp[v][i][1];
		for(int i=r-1;i>=0;i--){
			sufnow[i][0]=add(sufnow[i][0],sufnow[i+1][0]);
			sufnow[i][1]=add(sufnow[i][1],sufnow[i+1][1]);
			sufv[i][0]=add(sufv[i][0],sufv[i+1][0]);
			sufv[i][1]=add(sufv[i][1],sufv[i+1][1]);
		}
		for(int i=0;i<=r;i++){
			tmp[i][0]=add(tmp[i][0],dp[now][i][0]*(sufv[i][1]+sufv[i][0])%mod);
			tmp[i][1]=add(tmp[i][1],dp[now][i][1]*(sufv[i][1]+sufv[i+1][0])%mod);
			tmp[i][0]=add(tmp[i][0],dp[v][i][0]*(sufnow[i][1]+sufnow[i+1][0])%mod);
			tmp[i][1]=add(tmp[i][1],dp[v][i][1]*(sufnow[i+1][1]+sufnow[i+1][0])%mod);
		}
		for(int i=0;i<=r;i++) dp[now][i][0]=tmp[i][0],dp[now][i][1]=tmp[i][1];
	}
	if(now!=1){
		for(int i=1;i<=r;i++) dp[now][i-1][1]=dp[now][i][1];
		dp[now][r][1]=dp[now][r][0];
		for(int i=r-1;i>=0;i--) dp[now][i+1][0]=dp[now][i][0];
		dp[now][0][0]=0;
	}
}
signed main(){
	int n; cin>>n;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	int ans=(mod-1+n*qp(inv2,n)%mod)%mod,lst=0;
	for(int i=1;i<=n;i++){
		r=i;
		memset(dp,0,sizeof(dp));
		dfs(1,0);
		int tot=0; for(int j=0;j<=r;j++) (tot+=dp[1][j][0])%=mod;
		(ans+=(tot+mod-lst)*i)%=mod;
		lst=tot;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：baoba (赞：0)

设 $\operatorname{B}(u,r)={v|dis(u,v)≤r}$。如果志愿者不参加，则顶点为黑色。

首先，我们枚举 $r$，并计算答案不大于 $r$ 的情况。

这相当于对于所有黑色顶点 $u$，$\operatorname{B}(u,r)$ 的联合将覆盖所有顶点。

因此，一个典型的树 $dp$ 是考虑一个子树，最深的未覆盖顶点的深度，以及它能延伸多长(其邻居能从这个子树延伸出去的最浅的黑色顶点)。

这里有一个观察结果，如果子树上有一个未覆盖顶点，那么它能延伸多长并不重要。原因是这个顶点需要被其他子树上的顶点 $(v)$ 覆盖，而 $v$ 可以比这个子树上的顶点延伸得更远。

因此，如果子树上有未覆盖顶点，我们只关心最深的未覆盖顶点的深度。否则，我们只关心最浅的黑色顶点的深度。这棵子树的状态是 $O(Size_a)$(实际上是  $O(dep_a)$)。

每个 $r$ 的时间复杂度为 $O(n^2)$，总体复杂度为 $O(n^3)$。

有可能进一步优化为 $O(n^2 \log n)$。

附上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
enum{N=309,M=N*2,P=998244353};
int F[N][M],G[M],*f[N],*g=G+N,n,o;
basic_string<int>e[N];
unordered_set<int>s[N],t;
int qp(int a,int b){int r=1;for(;b;b>>=1,a=a*1ll*a%P)if(b&1)r=r*1ll*a%P;return r;}
void dfs(int x,int y){
	memset(F[x],0,M*4),f[x][-1]=f[x][o]=1,s[x]={-1,o};
	for(int i:e[x])if(i^y){
		dfs(i,x),memset(G,0,M*4),t={};
		int l;
		for(int j:s[x])for(int k:s[i])if(j+k>=0)t.insert(l=max(j,k-1)),g[l]=(g[l]+f[x][j]*1ll*f[i][k])%P;
		else if((l=min(j,k-1))>=-o)t.insert(l),g[l]=(g[l]+f[x][j]*1ll*f[i][k])%P;
		memcpy(F[x],G,M*4),s[x]=t;
	}
}
int main(){ios::sync_with_stdio(0),cin.tie(0);
	int i,j,k;
	for(i=0;i<N;++i)f[i]=F[i]+N;
	for(cin>>n,i=1;i<n;++i)cin>>j>>k,e[j]+=k,e[k]+=j;
	for(o=1,j=0;o<n;++o)for(dfs(1,0),k=0;k<n;++k)j=(j-f[1][k])%P;
	cout<<((j+qp(2,n)*(n-1ll))%P*qp(qp(2,P-2),n)%P+P)%P;
	return 0;
}
```

---

## 作者：o51gHaboTei1 (赞：0)

**sol of CF1517F**

其实不是很难的一道题。

很考察基础 dp 状态设定的 trick 与套路的好题。

思考的过程连续性比较长。

参考了 aw 的题解。

------------------------------------------------------

这是该题个人的解题步骤：

- 发现性质，确定性质；

- 状态设定（被卡了/ll）

- 转移方程

期望是水的，本质还是求和。

定义白点是有空的，黑点是没空的。

我们发现这道题相当于就是问树上每个点等概率保留的情况下可能产生的所有连通块直径长和。

一个初步的想法是：在 dp 的时候对于每一个连通块的贡献尝试记在一个节点上以达到去重的目的。最初你可能想的是枚举每个直径的端点。

我们不妨先保留一个初步想法：将 dp 设定成二维 $dp_{x}$ 表示点 $x$ 作为连通块的贡献记录点时的贡献之和。但是你发现这样去重的状态也难以继续添加并设定。

然后重新推性质。先对于全没空和全有空的贡献当成全有空的贡献是 $n - 1$，设 $s(U)$ 表示的是联通块 $U$ 的直径长，我们想要算的就是：$\sum_{r = 1} ^ {n - 1} r\sum[s(U) == r]$。

观察一下，这个好像我们做期望题的时候 $\sum_{x} xP(x)$ 之类的形式啊，我们也尝试做成容斥的形式，即求 $\sum_{r = 1} ^ {n - 1} \sum[s(U) \geq r]$。


这一步不用容斥理解其实也不困难，就是把前面系数 $r$ 的贡献重新分配了一下。


继续做，先枚举 $r$。


我们先只考虑子树，假设 $f_{x,i}$ 表示 $x$ 子树内，半径 $\geq i$ 的方案数。很恶心的定义，我们不妨直接换成，$f_{x,i}$ 表示子树内距离 $x$ 最近的黑色节点距离 $> i$ 时的方案数，两者显然是等价的。

这个东西确实很好转移，但是我们发现这个状态下子树外的信息啥也不知道啊，那难道做个换根吗？显然不是的。

我们定义满足子树内/外限制的贡献记录点为完全合法点，只满足子树内的为子树合法点（即上文中的 $f$）。

我们知道 $f$ 数组算的是子树合法的方案数，我们称这些满足子树限制的点是子树合法的，定义 $g_{x,i}$ 表示 $x$ 子树内距离 $x$ 为 $i$ 的**最远**子树合法，且**仅考虑在 $x$ 子树内是完全合法**的贡献记录点贡献的联通块方案数。

同时最重要的是，$f,g$ 数组**是两个完全独立的状态**，即任意一种连通块方案要么记在 $f$ 数组里面要么记在 $g$ 数组里面。

这是高度压缩的划分状态，请没完全理解的读者仔细理解。

定义 $g$ 数组的目的是将子树 $x$ 内的子树合法点都从下往上转移上来，在这个过程中检查子树合法点是否在子树外合法，这个暂时没看懂没关系，你看完下面的状态转移在上来看看，这是帮助理解的。

我们写出转移方程并逐一解释，以下的转移方程的形式都是将一棵儿子子树 $v$ 合并到 $u$ 上去：

- $f_{u,i},f_{v,j}$ 的合并。这个简单，根据定义我们直接向 $f_{u,\min(i,j+1)}$ 转移即可；

- $g_{u,i},g_{v,j}$ 的合并。根据定义，我们知道我们记的是距离最远的子树合法点，所以向 $g_{u,\max(i,j + 1)}$ 转移即可；

- $f_{u,i},g_{v,j}$ 的合并。这个稍微困难一些，我们发现若 $i + j + 1 > r$ 就得向 $g_{u,j+1}$ 转移，否则就得向 $f_{u,i}$ 转移。前一个好理解，合法就转移，并且由于划分是独立的所以只能向 $g$ 转；对于后一个，我们发现此时出现了不合法的情况，那么这个子树合法点就寄了，由于在 $g_{v,j}$ 内部满足任意的链长 $m$，$m + j > r$，而又由于 $i + j + 1 \leq r$，所以显然 $i < m$，则在向 $f$ 转移时还是应该取距离为 $i$ 的那个距离最近的黑色节点；

- $g_{u,i},f_{v,j}$ 的合并。类似上面的，如果 $i + j + 1 > r$ 就得向 $g_{u,i}$ 转移；否则就得向 $f_{i,j + 1}$ 转移。原理和上面差不多。

看完这里你再返回上面设定 $g$ 数组的目的那里去看一下应该也能理解了。

最后对于每一个 $r$ 的答案是 $\sum_{i=0}^{n-1}g_{1,i}$。

关于不算重其实还好说，因为可能最后对于每个 $r$ 算出来的连通块可能记录了多个子树合法点，但是每次都是在子树之间做方案乘积时候计入的，所以不会算重。

这样的转移总是能让 $f,g$ 封闭独立转移，我们可以理解成 $g$ 其实相较于 $f$ 是应被优先统计的，即若一个连通块满足 $g$ 与 $f$ 两者的限制那么我们优先算在 $g$ 上面，这样所有的连通块方案就被划分为了两种情况：记在 $g$ 上的所有满足 $g$ 的连通块方案以及不满足 $g$ 但满足 $f$ 限制的联通块方案。

时间复杂度 $O(n ^ 3)$。

```cpp
/*
考虑一次贡献是记在 x 连通块直径端点上的。 
不懂。不懂啊。
计数题还是做不来，乐死了。计数题还是做不来，乐死了。计数题还是做不来，乐死了。 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 305 , mod = 998244353;
int n,m,head[Len],cnt,f[Len][Len],g[Len][Len],siz[Len],as;
struct node
{
	int next,to;
}edge[Len << 1];
inline void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
int recf[Len],recg[Len],r;
inline void Mod(int &x){if(x < 0) x += mod;if(x >= mod) x -= mod;}
inline void Add(int &x,int y){x += y;Mod(x);}
inline void Sub(int &x,int y){x -= y;Mod(x);}
void dfs(int x,int fa)
{
	for(int i = 0 ; i <= n ; i ++) f[x][i] = g[x][i] = 0;
	f[x][0] = g[x][0] = 1;siz[x] = 1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == fa) continue;
		dfs(to , x);
		for(int i = 0 ; i <= siz[x] + siz[to] ; i ++) recf[i] = recg[i] = 0;
		for(int i = 0 ; i < siz[x] ; i ++) 
		{
			for(int j = 0 ; j < siz[to] ; j ++)
			{
				//f_{x,i} + f_{to,j}
				Add(recf[min(i , j + 1)] , 1ll * f[x][i] * f[to][j] % mod);
				//g_{x,i} + g_{to,j}
				Add(recg[max(i , j + 1)] , 1ll * g[x][i] * g[to][j] % mod);
				//f_{x,i} + g_{to,j}
				Add((i + j + 1 > r) ? recg[j + 1] : recf[i] , 1ll * f[x][i] * g[to][j] % mod);
				//g_{x,i} + f_{to,j}
				Add((i + j + 1 > r) ? recg[i] : recf[j + 1] , 1ll * g[x][i] * f[to][j] % mod);
			}
		}
		siz[x] += siz[to];
		for(int i = 0 ; i <= siz[x] ; i ++) f[x][i] = recf[i] , g[x][i] = recg[i];
	}
}
inline int qpow(int a,int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		b = b >> 1;
	}
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);
	}
	r = 1;
	while(r < n)
	{
		dfs(1 , 0);
		for(int i = 0 ; i < n ; i ++) as += g[1][i] , Mod(as);
		r ++;
	}
	//printf("%d\n",as);
	printf("%lld\n",1ll * as * qpow(qpow(2 , n) , mod - 2) % mod);
	return 0;
}
```

---

