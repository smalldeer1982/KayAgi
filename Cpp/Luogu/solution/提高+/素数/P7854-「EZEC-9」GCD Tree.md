# 「EZEC-9」GCD Tree

## 题目背景

规定 $\gcd(x,y)$ 表示 $x,y$ 的最大公约数，$\operatorname{lca}(x,y)$ 表示 $x$ 号节点和 $y$ 号节点的最近公共祖先。

## 题目描述

给你 $n$ 个点，编号分别为 $1,2,\ldots,n$，点权分别为 $a_1,a_2,\ldots,a_n$。

请你用这 $n$ 个点构造一棵树，使得 $\forall 1 \le i < j \le n$，$\gcd(a_i, a_j) = a_{\operatorname{lca}(i, j)}$。

若无解，报告之，否则输出树的形态。

## 说明/提示

**【数据规模与约定】**

**本题采用捆绑测试。**

-  Subtask 1（5 points）：$n = 2$。
-  Subtask 2（5 points）：所有 $a_i$ 均相等。
-  Subtask 3（5 points）：$n \le 5$。
-  Subtask 4（10 points）：保证有解。
-  Subtask 5（15 points）：$n \le 100$。
-  Subtask 6（15 points）：$n \le 10^3$。
-  Subtask 7（15 points）：$n \le 3 \times 10^3$。
-  Subtask 8（30 points）：无特殊限制。

对于 $100 \%$ 的数据，$2 \le n \le 10^5$，$1 \le a_i \le 10^6$。

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
0 1 1 2 1
```

## 样例 #2

### 输入

```
5
1 2 3 4 6
```

### 输出

```
-1
```

# 题解

## 作者：littleKtian (赞：10)

首先点权相同的点显然可以缩在一起，这样剩下的点点权都是互不相同的。

因为当 $a_i\mid a_j$ 时 $\gcd(a_i,a_j)=a_i$，显然此时 $i$ 应该是 $j$ 的祖先。所以我们考虑按点权从大到小枚举 $i$，对于所有点权为其倍数的**还未设置父亲**的点 $j$，将 $j$ 的父亲设置为 $i$，全部设置完后再次枚举倍数检查是否成祖先关系（在这步之前要先检查是否连通）。

考虑如何处理类似 `1 4 6` 这种 $\gcd$ 未出现的情况。

我们可以枚举 $\gcd$ 的值，然后将点权为其倍数的点全部标记出来。可以发现如果所有被标记出来的点如果正好构成原树的一棵子树，那么这个 $\gcd$ 的值是不会出现的；如果为多棵，那么就必然会有点对使得点权的 $\gcd$ 的值为枚举到的值，也就是无解。

然后可以发现这步的判断可以和上面的判断合成一种判断。

复杂度 $O(n\log n)$（调和级数的复杂度）。

```cpp
#include<bits/stdc++.h>
#define N 1000000
using namespace std;
int lw[100005],bi[100005][2],bs;
int n,a[100005],fa[100005],tt,rt;
int si[100005],hx[100005],dfn;
int xh[1000005];
int dr()
{
	int xx=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')xx=xx*10+ch-'0',ch=getchar();
	return xx;
}
void tj(int u,int v){bi[++bs][0]=lw[u],bi[lw[u]=bs][1]=v;}
void dfs(int w)
{
	si[w]=1,hx[w]=++dfn;
	for(int o_o=lw[w];o_o;o_o=bi[o_o][0])
	{
		int v=bi[o_o][1];
		dfs(v),si[w]+=si[v];
	}
}
bool gra(const int &x,const int &y){return hx[x]<=hx[y]&&hx[y]<hx[x]+si[x];}
int main()
{
	n=dr();
	for(int i=1;i<=n;i++)
	{
		a[i]=dr();
		if(xh[a[i]])fa[xh[a[i]]]=i,tj(i,xh[a[i]]),++tt;
		xh[a[i]]=i;
	}
	for(int i=N;i;i--)if(xh[i])
	{
		rt=xh[i];
		for(int j=i*2;j<=N;j+=i)if(xh[j]&&(!fa[xh[j]]))fa[xh[j]]=xh[i],tj(xh[i],xh[j]),++tt;
	}
	if(tt!=n-1){printf("-1");return 0;}
	dfs(rt);
	for(int i=1;i<=N;i++)
	{
		int tt=0;
		for(int j=i;j<=N;j+=i)if(xh[j]&&(fa[xh[j]]==0||a[fa[xh[j]]]%i!=0))++tt;
		if(tt>1){printf("-1");return 0;}
	}
	for(int i=1;i<=n;i++)printf("%d ",fa[i]);
}
```

---

## 作者：chager (赞：9)

这道题好像解法真的很多呢……

前置芝士：

我们设 $d_i$ 表示 $i$ 的约数个数，则：

$\sum\limits_{i=1}^n d(i)$ 是 $O(nlogn)$ 级别的。

$\sum\limits_{i=1}^n \lfloor\frac{n}{i}\rfloor$ 也是 $O(nlogn)$ 级别的。

---

我们不妨先考虑一些引理：

1.重复的点可以缩点（其他点直接全连一个点上）；

2.如果序列中 $\exists y \le z \le x$ 使得 $y \mid x,z \mid x$ 但 $y \nmid z$，则一定无解；

证明：因为 $y \mid x,z \mid x$，所以 $y,z$ 一定都在 $x$ 到根的路径上；然而 $y \nmid z$，所以 $y,z$ 不应在一条链上；矛盾，证毕；

3.我们将所有出现了的数的所有因数 $f$ 值 $+1$，对于一个数，如果他的倍数中有2个及以上 $f$ 值 $>1$ 且这个数没有出现，则无解；

证明：相当于它是一个gcd；

其余的情况均有解；

于是我们考虑从小到大对于每个点求其父亲，可以用线性筛做到 $O(nlogn)$；

然后做的时候判断是否满足2条件；

做完之后判断是否满足3条件；

代码：

```cpp
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <algorithm>
int mip[1000010],isp[1000010],totp,p[1000010],f[1000010],fa[1000010];
int totr,r[100010],bj[1000010],mp[1000010];
int tots,s[1000010];
struct node
{
	int pos,val;
}a[100010];
int cmp(node x,node y)
{
	return (x.val<y.val || x.val==y.val && x.pos<y.pos);
}
void init()
{
	int i,j;
	isp[1]=1;
	mip[1]=1;
	for(i=2;i<=1000000;i++)
	{
		if(!isp[i])
		{
			totp++;
			p[totp]=i;
			mip[i]=i;
		}
		for(j=1;j<=totp;j++)
		{
			if(i*p[j]>1000000)
				break;
			isp[i*p[j]]=1;
			mip[i*p[j]]=p[j];
			if(!i%p[j])
				break;
		}
	}
	return;
}
void get1(int x)
{
	if(x==1)
		return;
	if(r[totr]!=mip[x])
	{
		totr++;
		r[totr]=mip[x];
	}
	f[mip[x]]++;
	get1(x/mip[x]);
	return;
}
void dfs1(int x,int now)
{
	int i;
	if(x>totr)
	{
		bj[now]++;
		tots++;
		s[tots]=now;
		return;
	}
	dfs1(x+1,now);
	for(i=1;i<=f[r[x]];i++)
	{
		now*=r[x];
		dfs1(x+1,now);
	}
	return;
}
void done1(int x)
{
	int i,j;
	for(i=1;i<=totr;i++)
		f[r[i]]=0;
	totr=0;
	for(i=1;i<=tots;i++)
		f[s[i]]=0;
	tots=0;
	get1(x);
	dfs1(1,1);
	std::sort(s+1,s+tots+1);
	j=x;
	tots--;
	for(i=tots;i>=1;i--)
	{
		if(mp[s[i]])
		{
			if(!fa[mp[x]])
			{
				fa[mp[x]]=mp[s[i]];
				j=s[i];
			}
			else
			{
				if(j%s[i])
				{
					printf("-1");
					exit(0);
				}
				else
					j=s[i];
			}
		}
	}
	return;
}
void chec(int x)
{
	int i;
	if(bj[x]<1 || mp[x])
		return;
	for(i=2*x;i<=1000000;i+=x)
	{
		if(bj[i]>=bj[x])
			return;
	}
	printf("-1");
	exit(0);
	return;
}
int main()
{
	init();
	int i,j,n,m;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i].val);
		a[i].pos=i;
	}
	std::sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++)
	{
		if(!mp[a[i].val])
			mp[a[i].val]=a[i].pos;
		else
			fa[a[i].pos]=mp[a[i].val];
	}
	for(i=1;i<=1000000;i++)
	{
		if(mp[i])
			done1(i);
	}
	for(i=1;i<=1000000;i++)
		chec(i);
	for(i=1;i<=n;i++)
		printf("%d ",fa[i]);
	return 0;
}
```

---

## 作者：LZDQ (赞：6)

显然树上存在祖先关系的点一定有倍数关系。对于权值相同的点，我们连成一条链之后只处理链顶那个点即可。

将第一句话反过来，有倍数关系的两个点一定要有祖先关系。考虑一个点的权值的所有存在的因子（存在指有一个点的权值为这个因子），沿着树往上跳必须经过所有存在的因子。显然我们找到最大的存在的因子连一条边是唯一可行解。之后只需要判断这棵树是否合法（这题相当于让你写一个 SPJ）。~~我们也不需要考虑利用这棵树的性质，因为 SPJ 用不到任何性质。~~

考虑对于每个 $\operatorname{lca}$ 处，需要满足每棵子树的 $\operatorname{lcm}$ 的两两 $\gcd$ 均为 $a_{lca}$。同时除以 $a_{lca}$，相当于每棵子树构成的质因数集合两两不交。处理完 $a_{lca}$ 后将这些质因数集合的不重并集并上 $a_{lca}/a_{fa_{lca}}$ 的质因数集合加入到父亲。可能可以过吧，但是非常麻烦。

考虑对于每个质因数分开处理。对于 $p | (a_i/a_{fa_i})$ 的点将权值设置为 $1$，其他为 $0$。当两个没有祖先关系的点权值都为 $1$ 时，显然会在 $\operatorname{lca}$ 处发生错误。所以相当于判断权值为 $1$ 的点是不是在一条从根出发的链上。

考虑将所有 $a_i/a_{fa_i}$ 打上标记 $\text{cnt++}$ ，并记录深度最大的那个点。对于每个权值 $p$，把倍数全部弄出来算有多少个标记和深度最大的那个点，然后从那个点暴力往上跳计数有多少个 $1$，如果两个计数器不相等就不合法。

复杂度 $\Theta(m \ln m)$，其中 $m=10^6$。还有一定的常数优化空间比如只需要枚举质数。

本以为自己代码写得挺复杂，看了几页发现很短，不知道各位神仙都是怎么做的。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long ll;
using namespace std;
const int MAXN=1e6+5;
int n,m,tot,p[MAXN],fa[MAXN],fw[MAXN],cnt[MAXN],mx[MAXN],dep[MAXN];
// fw 记录权值 i 的父亲的权值，dep 记录权值为 i 的深度
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int a; scanf("%d",&a);
		if(p[a]) fa[i]=p[a],tot++;
		else p[a]=i,fw[a]=1;
	}
	m=1e6;
	for(int i=m; i; i--){
		if(!p[i]) continue;
		for(int j=i<<1; j<=m; j+=i)
			if(p[j]&&!fa[p[j]])
				fa[p[j]]=p[i],fw[j]=i,tot++;
	}
	if(tot<n-1) return puts("-1"),0;
	for(int i=1; i<=m; i++)
		if(p[i]){
			dep[i]=dep[fw[i]]+1;
			cnt[i/fw[i]]++;
			if(dep[i]>dep[mx[i/fw[i]]]) mx[i/fw[i]]=i;
		}
	for(int i=2; i<=m; i++){
		int s=0,t=0;
		for(int j=i; j<=m; j+=i){
			s+=cnt[j];
			if(dep[t]<dep[mx[j]]) t=mx[j];
		}
		while(t>1){
			if(t/fw[t]%i==0) s--;
			t=fw[t];
		}
		if(s) return puts("-1"),0;
	}
	for(int i=1; i<=n; i++)
		printf("%d ",fa[i]);
	puts("");
	return 0;
}
```

---

## 作者：Ecrade_ (赞：5)

### 题外话

这题原本的数据范围是 $1\le n\le 3\times 10^3$，值域 $V$ 开到了 $10^{18}$，由于当时的解法无法避免使用 $\gcd$ 函数，时间复杂度为 $O(n^2\log V)$。

不过 @[小粉兔](https://www.luogu.com.cn/user/10703) 审题时一直在研究，当 $V$ 较小时是否存在 $O(n^2)$ 或 $O(n^{2-\text{eps}})$ 的解法。

这启发了我，于是经过一番思考，我便口胡出了一种 $O(n\log n\log V+n\sqrt V)$ 的奇怪解法。

后经 @[小粉兔](https://www.luogu.com.cn/user/10703) 点拨，我们成功将复杂度降至 $O((n+V)\log n+V)$，本题也随之诞生。

本题解法颇多，但由于数据极其难造，故不能保证可以卡掉所有错解，还请大家谅解。

感谢 @[小粉兔](https://www.luogu.com.cn/user/10703) 对加强本题~~以及让我体会到重写一份 5KB 数据生成器的快感~~做出的所有贡献！

---
### 题解

相同权值的节点必定只能形成一个连通块，故只需考虑去重后的节点即可。

**先申明一下：下文中的推理均是在节点去重后的基础上进行的。**

一个**可能不是那么重要**的结论：

- 树的形态是唯一的。

两个**显然**的结论：

- $a_u$ 必为 $u$ 子树中所有节点权值的因数。

- $u$ 子树中不能出现两个节点 $v_1,v_2$，使得 $\gcd(v_1,v_2)>a_u$ 且它们出现在 $u$ 某两个不同子节点的子树中。

**我们可以先建树，再判断是否合法。**

若 $a_{p_1},a_{p_2},\dots,a_{p_k}\ (a_{p_1}<a_{p_2}<\dots<a_{p_k})$ 均为 $a_i$ 的因数，那么能够作为 $i$ 父亲的只可能是 $p_k$。

故可以按照权值从大到小遍历 $a$ 数组，若当前遍历到了 $i$，那么再找到权值为 $a_i$ 倍数、且还未有父节点的所有节点，并将它们的父节点设置为 $i$。

实现过程中，可以记录一个权值所对应的节点编号，接着枚举 $a_i$ 的倍数，看对应的节点是否存在，若存在就看其当前是否有父节点。

排序 + 建树过程的时间复杂度为 $O(n\log n+V\log n)$。

接下来考虑如何判断建出来的树是否合法。

一种朴素的想法是直接枚举 $\text{lca}$ 暴力判断，但这是 $O(n^2\log V)$ 的，显然不能接受。

换个思路，假设建出的树不合法，那么这棵树会有什么性质呢？

为了方便表述，我们称满足题目条件的点对是**友好的**，否则是**不友好的**，同时定义 $l_{i,j}$ 表示 $\text{lca}(i,j)$，$fa_u$ 表示 $u$ 的父节点。

若树**不合法**，那我们必定能找到一个**不为祖孙关系**的点对 $(i,j)$，使得 $i$ 到 $l_{i,j}$ 上的所有点，与 $j$ 到 $l_{i,j}$ 上的所有点两两之间都是友好的，而只有 $(i,j)$ 不友好。

不妨设 $r_1$ 为 $i$ 到 $l_{i,j}$ 这条路径上的某一点，$r_2$ 为 $j$ 到 $l_{i,j}$ 这条路径上的某一点。当然，$(r_1,r_2)\neq (i,j)$。

由于 $(r_1,r_2)$ 是友好的，那么可推得 $\gcd(\dfrac{a_{r_1}}{a_{l_{i,j}}},\dfrac{a_{r_2}}{a_{l_{i,j}}})=1$，记为 ① 式。

又 $(fa_{r_1},fa_{r_2})$ 是友好的，故 $\gcd(\dfrac{a_{fa_{r_1}}}{a_{l_{i,j}}},\dfrac{a_{fa_{r_2}}}{a_{l_{i,j}}})=1$，记为 ② 式。

将 ① 式与 ② 式相除，得到 $\gcd(\dfrac{a_{r_1}}{a_{fa_{r1}}},\dfrac{a_{r_2}}{a_{fa_{r2}}})=1$（注意到这里参与 $\gcd$ 运算的所有分式的值均为整数，故能够保证其正确性）。

相类似地，由于 $(i,j)$ 是不友好的，而 $(fa_i,fa_j)$ 是友好的，那么可推得 $\gcd(\dfrac{a_i}{a_{fa_i}},\dfrac{a_j}{a_{fa_j}})>1$。

说人话，就是如果出现了一个**不为祖孙关系**的点对 $(i,j)$，满足 $\gcd(\dfrac{a_i}{a_{fa_i}},\dfrac{a_j}{a_{fa_j}})>1$，那么这棵树就是**不合法的**。

再稍微转化下。

具体地，对于每个非根节点 $u$，定义 $c_u=\dfrac{a_u}{a_{fa_u}}$。

对于一个质数 $p$，定义 $S_p$ 表示满足 $p\mid c_u$ 的所有结点 $u$ 构成的集合。

那么，建出来的树是**合法的**，当且仅当对于所有质数 $p$，$S_p$ 中的所有节点两两均为祖孙关系。

由于树的深度最多为 $\log V$，故每枚举一个质数 $p$，直接从最深的节点往上遍历，看能否遍历到 $S_p$ 中的所有节点即可。

质数个数为 $O(\frac{V}{\log V})$ 个，遍历一次 $O(\log V)$，则判断部分的时间复杂度为 $O(V)$。

综上，我们便用 $O((n+V)\log n+V)$ 的时间复杂度解决了本题。

代码可读性不高，就不放了。

---

## 作者：Y_B_X (赞：4)

[原题链接](https://www.luogu.com.cn/problem/P7854)

题意：给定 $n$ 个点，点有点权，求一棵树满足对所有点对  $(i,j)$ 有 $\gcd(a_i,a_j)=a_{\operatorname{lca}(i,j)}$

首先，如果一些点的点权相同那它们就能缩成一个点，内部形成一条链。

所以只需看去重后的点如何构造，以下分析都是基于**去重后的序列**。

先求出所有点的 $\gcd$ ，如果序列中没有这个值，就一定不合法，

否则就是整棵树的根 $root$ 且点权最小。

由于每个点 $x$ 作为 $(i,j)$ 的 $\operatorname{lca}$ 时有 $a_x|a_i$ 且 $a_x|a_j$

所以点权为 $a_x$ 的倍数的点一定在 $x$ 的子树内。

而如果存在两个点 $(u,v)$ 使 $a_u|a_i$ 且 $a_v|a_i$ 但 $a_u$ 与 $a_v$ 不互为倍数。

这个时候 $i$ 必须在 $u$ 的子树内又在 $v$ 的子树内，
但 $u$ 不在 $v$ 的子树内，$v$ 不在 $u$ 的子树内。

矛盾！此时就说明序列就不合法。

换句话说，每个点出现在原序列中的因子必须相互整除。

所以对于一个合法的序列，每个点在树上的父亲的必须是**序列中除它外的，能整除它且权值最大的点**。

这可以以 $O(\sqrt V)$ 的时间找出。

这样就能初步构造出如果序列合法时其树的形态。

这棵树能保证对任意 $(i,j)$ 有 $a_{\operatorname{lca}(i,j)}|\gcd(a_i,a_j)$

赋给每个点另外一个值 $w_i=a_i/a_{fa_i}$ 也即与他父亲做商，特别的，$w_{root}=1$。

记 $path(i,j)$ 为 $i$ 到 $j$ 的路径组成的集合。

那么每个点 $i$ 有 $a_i=\prod\limits_{j\in path(i,root)}w_j$

由于 $a_{\operatorname{lca}(i,j)}=\gcd(a_i,a_j)$

所以 $\prod\limits_{k\in path(i,\operatorname{lca}(i,j))}w_k$ 与 $\prod\limits_{k\in path(j,\operatorname{lca}(i,j))}w_k$ 互素。

也即 $i$ 到 $\operatorname{lca}(i,j)$ 路径 $w$ 积与 $j$ 到 $\operatorname{lca}(i,j)$ 路劲 $w$ 积互素。

所以不满足这个条件时，存在一个 $d$ 使在两条路径上各有一 $w$ 是其倍数。

换句话说，树合法时，对每个 $d$ 是它倍数的 $w$ 值所对应的点都在树上的一条链上。

记录下每个 $w$ 值对应树上那些点，可用动态数组或 $\text{vecotor}$ 实现。

然后枚举 $d$ ，找出所有它的倍数的 $w$ 值所对应的点并按深度从小到大排序。

这些点的总个数是 $O(n\log V)$ 的，因为每个值的因子有 $O(\log V)$ 个。（为了不影响阅读体验，证明在后面）

对每个点先查询在它之前它到根路径上共有多少点，判断其是否等于之前点的个数。

如不等，则说明其不在一条链上，树就不合法。

查询直接暴力跳就好了，因为由于每个点的父亲权值是其因子，树高至多是 $\log(V)$ 的。

这样的时间复杂度是 $O(n\sqrt V+n\log^2 V)$

对每个值因子个数为 $O(\log V)$ 的证明：

设 $d(n)$ 为 $n$ 的因子个数，$n=p_1^{\alpha_1}p_2^{\alpha_2}\dots p_k^{\alpha_k}$

由于 $d$ 为积性函数，只需证明对任意的素数 $p$ 有 $p^m$ 的因数个数是 $O(\log p^m)$。

而 $d(p^m)=m+1=1+\log_{p} p^m\leq 1+\log p^m$ , 证毕。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int n,m,x,y,nn,d,tot,res,tmp,sum;char ch;
int a[N+10],f[N+10],dep[N+10],fr[N+10],bk[N+10],size[N+10],t[N+10];
int rev[N+10],f_[N+10],w[N+10],cnt[N+10],*id[N+10];
inline void read(int &x){x=0;ch=getchar();while(ch<48||ch>57)ch=getchar();
	while(ch>47&&ch<58)x=x*10+ch-48,ch=getchar();}
void write(int x){if(x>=10)write(x/10);putchar(48+x%10);}
void dispose(int x){tmp=0;for(y=x;y;y=f_[y])tmp+=size[y];++size[x],++tot;}
bool cmp(int a,int b){return dep[a]<dep[b];}
main(){
	read(n);register int i,j,k;
	for(i=1;i<=n;++i){
		read(a[i]);
		if(!d)d=a[i];
		if(!fr[a[i]])fr[a[i]]=bk[a[i]]=i;
		else f[i]=bk[a[i]],bk[a[i]]=i;
		d=__gcd(d,a[i]);
	}
	for(i=1;i<=N;++i)if(bk[i])a[++nn]=i,rev[i]=nn;
	if(a[1]^d){puts("-1");return 0;}
	dep[1]=1;
	for(i=2;i<=nn;++i){
		m=sqrt(a[i]);
		for(j=2;j<=m;++j)if(a[i]%j==0&&bk[k=a[i]/j]){
			f_[i]=rev[k];dep[i]=dep[rev[k]]+1;f[fr[a[i]]]=bk[k];++cnt[w[i]=j];break;
		}
		if(!f_[i])for(j=m;j;--j)if(a[i]%j==0&&bk[j]){
			f_[i]=rev[j];dep[i]=dep[rev[j]]+1;f[fr[a[i]]]=bk[j];++cnt[w[i]=a[i]/j];break;
		}
	}
	for(i=1;i<=N;++i)if(cnt[i])id[i]=new int [cnt[i]+1],cnt[i]=0;
	for(i=2;i<=nn;++i)id[w[i]][++cnt[w[i]]]=i;
	for(i=2;i<=N;++i){
		for(j=i;j<=N;j+=i)if(cnt[j])for(k=1;k<=cnt[j];++k)t[++sum]=id[j][k];
		sort(t+1,t+sum+1,cmp);
		for(j=1;j<=sum;++j){res=tot;dispose(t[j]);if(tmp^res){puts("-1");return 0;}}
		for(j=1;j<=sum;++j)--size[t[j]];tot=0;
		sum=0;
	}
	for(i=1;i<=n;++i)write(f[i]),putchar(' ');
}
```

事实上这还能优化不少。

对于一开始 $O(\sqrt V)$ 的找父亲，可以变成从小到大枚举序列中的每个数的倍数。

这样之前的 $O(n\sqrt V)$ 处理就优化成 $O(V\log n)$

如果这个数的某个倍数存在就更新其父亲，

而后面枚举 $d$ 时只需枚举素数就足够了。

这部分的粗略的近似应该是 $O(n\times \dfrac{\ln^2 V}{\ln\ln V})$

[证明有点复杂，放这里](https://www.luogu.com.cn/blog/Y-B-X/yi-ge-shuo-di-zhi-yin-zi-ge-shuo-di-cu-lve-jin-si)

然后就能顺利跑进第一页~

---

## 作者：chenxinyang2006 (赞：3)

对于满足限制的树，其必然满足以下性质

- 任意节点的权值，是其所有祖先权值的倍数

- 最小值对应的节点必然是根

由 1 我们可以知道，这棵树的树高是 $\log v$ 级别的，暂时看不出有什么用，由 2 我们可以直接确定根，并判掉一类无解情况，即存在数无法整除最小值

然后我们可以考虑能不能简化问题，比如转化为所有数互不相同的情况，这会给我们枚举倍数之类的操作提供便利，不难发现，我们对于所有数去重后，建出一颗树，然后对于所有值为 $x$ 但被删除的节点，我们把它挂在原树上值为 $x$ 的节点下面，得到的树仍然合法

接下来我们考虑，对于有一个确定的权值为 $u$ 的根，和一些节点的树（显然这些节点的权值都是根权值倍数），能否确定根的所有儿子，以及其他非儿子节点属于哪个儿子的子树

我们取出最小值 $v$，显然其是根的一个儿子，否则违反了 1，然后我们考虑哪些节点会在 $v$ 的子树内

不难发现，$v$ 的所有倍数对应的节点，必然在 $v$ 子树内，否则那个节点与 $v$ 的 LCA 是 $u$，但他们的 GCD 为 $v$，不符合条件

而其他节点在挂在 $v$ 的下面，会违反 1

然后我们删除 $v$ 和所有 $v$ 的倍数，再次循环上述过程，直到不存在其他节点

接下来递归求解所有子树即可

于是我们发现，我们唯一确定了一棵树

使用 set 维护子树内的所有节点即可支持以上所有操作，因为所有数互不相同，并且树高 $\log v$，这部分是 $O(n \log n \log v + v \log v)$ 的

接下来就是要判定这棵树是否合法了

可以观察发现，我们建出来的树可能存在的问题在于，两个点的 GCD 是他们 LCA 权值的倍数

我们考虑枚举这个 GCD 为 $d$，取出所有权值为 $d$ 倍数的节点，接下来我们就是要找，这些点中有没有两个点，$d$ 是他们的 LCA 权值的倍数

（这样可能选出两个点，他们的 GCD 实际上比 $d$ 大，但可以发现无影响）

换句话说，我们要找一个权值最小的 LCA

考虑性质 1，实际上我们要找所有 LCA 中最浅的一个，所有这些点的 LCA 是符合条件的

因为树高是 $\log v$ 级别的，于是我们用倍增 LCA 即可做到 $O(n \log \log v)$ 预处理，$O(\log \log v)$ 查询 

这部分复杂度为 $O(v \log v \log \log v)$，完全可过，实际上由于树高 $\log v$ 的性质，也容易利用 dfs 序去掉 $\log \log v$

```cpp
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <set>
using namespace std;

#define maxv 1000000
int n;
int a[100005],id[1000005];
int f[1000005],to[5][1000005],dep[1000005];

set <int> S[1000005];
set<int>::iterator it;

void dfs(int u){
	while(S[u].size()){
		it = S[u].begin();
		int v = *it;
		for(int i = 2 * v;i <= maxv;i += v){
			if(id[i]){
				S[u].erase(i);
				S[v].insert(i);
			}
		}
		S[u].erase(v);
		f[v] = u;
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}

int LCA(int u,int v){
	if(dep[u] < dep[v]) swap(u,v);
	for(int i = 4;i >= 0;i--) if(dep[to[i][u]] >= dep[v]) u = to[i][u];
	if(u == v) return u;
	for(int i = 4;i >= 0;i--){
		if(to[i][u] != to[i][v]){
			u = to[i][u];
			v = to[i][v];
		}
	}
	return to[0][u];
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		if(!id[a[i]]) id[a[i]] = i;
	}
	int rt = 0;
	for(int i = 1;i <= maxv;i++) if(id[i] && !rt) rt = i;
	for(int i = 1;i <= maxv;i++){
		if(id[i] && i % rt != 0){
			printf("-1\n");
			exit(0);
		}
	}
	for(int i = rt + 1;i <= maxv;i++) if(id[i]) S[rt].insert(i);
	dep[rt] = 1;
	dfs(rt);
	for(int i = 1;i <= maxv;i++) to[0][i] = f[i];
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= maxv;j++){
			if(!id[j]) continue;
			to[i][j] = to[i - 1][to[i - 1][j]];
		}
	}
	for(int d = 1;d <= maxv;d++){
		int cur = 0;
		for(int i = d;i <= maxv;i += d){
			if(!id[i]) continue;
			if(!cur) cur = i;
			else cur = LCA(cur,i);
		}
		if(cur % d != 0){
			printf("-1\n");
		    exit(0);
		}
	}
	for(int i = 1;i <= n;i++){
		if(id[a[i]] == i) printf("%d ",id[f[a[i]]]);
		else printf("%d ",id[a[i]]);
	}
	return 0;
}
```


---

## 作者：_SeeleVollerei_ (赞：1)

首先是同机房某个大佬告诉的结论，每个点的父亲的值是可选值中能整除这个点值的最大值，对于相同值的若干点搞成一条链直接取最上面那个点来用即可，然后就相当于判断这棵树是否符合题意即可。

有关这个结论的证明可以去看看其他大佬的题解，我只是想分享一下我的另一种判断的方式——点分治。

对于每个点$\ u\ $，对于$\ u\ $的任意两个不同的儿子 $\ a\ $ 和 $\ b\ $ ，在 $a$ 和 $\ b\ $ 的子树中各自任意选一个点$\ x\ $ 和 $\ y\ $ ，这两个点的 $\ lca\ $ 一定是 $\ u\ $。

也就是对于$\ u\ $的子树来讲要满足所有的 $\  \gcd (val_x,val_y)=val_u\ $ ，也就是 $\ val_x/val_u\ $ 与 $\ val_y/val_u\ $ 互质。

互质该怎么处理，我们只需要考虑质因数是否有重复的即可，而且不需要记录每种质因数的个数，只需要记录质因数有哪几种即可。

同时因为每个点的父亲都是他的因数，所以我们只用记录叶子结点的质因数。

我们发现， $\ val_i \le 10^6\ $。

而 $\ 2 \times 3 \times 5 \times 7\times 11 \times 13 \times 17=510510\ $ 。

所以每个数最多只有7种质因数，所以期望复杂度应该是 $\ O(nk\log n)\ $ 其中$\ k\ $是质因数种数造成的极小的常数。

然后可能有人会问：如果数据是条链呢？

因为父子都是倍数关系，相同的都弄成条链了对于父子相同值特判一下就好了，那么对于倍数关系，层数最多也只有 $\ \log10^6\ $ ，所以是不会被卡的。

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
const int M=1e6+5;
const int N=1e5+5;
bool Prime[M],flg=1;
int Headnum[M],Nxtnum[M<<2],Vernum[M<<2],cnt_num;
int Head[N],Nxt[N],Ver[N],cnt_edge;
int Num[N],fa[N],pos[M],n,ss,root;
int c[M];
inline int Read(){
	char ch;
	while((ch=getchar())<'0'||ch>'9');
	int x=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+(ch^48);
	return x;
}
inline int Max(const int x,const int y){
	return x>y?x:y;
}
inline void Add_Num(const int u,const int v){  //用邻接表存质因数
	++cnt_num;
	Vernum[cnt_num]=v;
	Nxtnum[cnt_num]=Headnum[u];
	Headnum[u]=cnt_num;
	return ;
}
inline void Add_Edge(const int u,const int v){
	++cnt_edge;
	Ver[cnt_edge]=v;
	Nxt[cnt_edge]=Head[u];
	Head[u]=cnt_edge;
	return ;
}
inline void Init(){
	memset(Headnum,-1,sizeof(Headnum));
	memset(Head,-1,sizeof(Head));
	n=Read();
	for(register int i=1;i<=n;i++){
		Num[i]=Read();
		if(!pos[Num[i]]) pos[Num[i]]=i;
		else fa[i]=pos[Num[i]];
	}
	for(register int i=1;i<=n;i++){  //给每个点找父亲
		if(fa[i]) continue ;
		for(register int j=2;j*j<=Num[i];j++){
			if(Num[i]%j) continue ;
			if(pos[Num[i]/j]){
				fa[i]=pos[Num[i]/j];
				break ;
			}
			if(pos[j]&&j>Num[fa[i]]) fa[i]=pos[j];
		}
		if(!fa[i]&&pos[1]&&i!=pos[1]) fa[i]=pos[1];
		if(!fa[i]) ss++,root=i;
		Add_Edge(fa[i],i);
	}
	for(register int i=2;i<=M-5;i++){
		if(Prime[i]) continue ;
		for(register int j=i;j<=M-5;j+=i){  //埃氏筛弄出每个数质因数
			Prime[j]=1;
			Add_Num(j,i);
		}
	}
	return ;
}
inline void Dfs1(const int u,const int value,const int fa){  //判断
	if(Head[u]==-1){
		for(register int i=Headnum[Num[u]/value];i!=-1;i=Nxtnum[i]){
			int v=Vernum[i];
			if(c[v]==fa){puts("-1");exit(0);}
		}
	}
	for(register int i=Head[u];i!=-1;i=Nxt[i]){
		int v=Ver[i];
		Dfs1(v,value,fa);
	}
	return ;
}
inline void Dfs2(const int u,const int value,const int fa){  //记录
	if(Head[u]==-1){
		for(register int i=Headnum[Num[u]/value];i!=-1;i=Nxtnum[i]){
			int v=Vernum[i];
			c[v]=fa;
		}
	}
	for(register int i=Head[u];i!=-1;i=Nxt[i]){
		int v=Ver[i];
		Dfs2(v,value,fa);
	}
	return ;
}
inline void Dfs(const int u){
	for(register int i=Head[u];i!=-1;i=Nxt[i]){
		int v=Ver[i];
		if(Num[v]==Num[u]) continue ;  //特判链
		Dfs1(v,Num[u],u);
		Dfs2(v,Num[u],u);
	}
	for(register int i=Head[u];i!=-1;i=Nxt[i]){
		int v=Ver[i];
		if(Num[v]==Num[u]) continue ;  //特判链
		Dfs(v);
	}
	return ;
}
inline void Solve(){
	if(ss>1){puts("-1");return ;}
	Dfs(root);
	for(register int i=1;i<=n;i++)
		printf("%d ",fa[i]);
	putchar('\n');
	return ;
}
int main(){
	Init();
	Solve();
	return 0;
}
```

---

## 作者：cmll02 (赞：0)

毒瘤题。

容易发现这棵树合法的必要条件是 $a_{fa_x}|a_x$。

那么我们考虑先构造出一棵树满足这个条件，然后再判断是否合法。

先把重复的数处理掉，直接往和他相同的数上连就行了。

将数组 $a$ 从小到大排序，最小的为根，然后剩下的一个一个加入树中。

记录下每个 $a_i$ 的因数，然后找到 $a$ 中出现的最大的那个因数（不能是他自己，找不到就是无解），然后连上去。

为什么连最大的呢？

考虑两种情况。

1. 存在 $j,k~(a_j<a_k)$ 且 $a_j\not|~a_k$，这种情况一定无解，因为你不管连 $j$ 还是 $k$ 都会矛盾，比如连 $j$，那么 $\operatorname{lca}(i,k)=\operatorname{lca}(j,k)$，$a_{\operatorname{lca}(j,k)}|\gcd(a_j,a_k)$，$\gcd(a_i,a_k)=a_{\operatorname{lca}(i,k)}\neq a_k$。

2. 存在 $j,k~(a_j|a_k)$，那么直接连 $k$ 不会有问题。

得到这个东西不一定是合法的，要进行判断。

判断的方法是，如果存在互不相同的 $u,v,w$ 使得 $v$ 在 $u$ 子树内，$w$ 不在 $u$ 子树内则不合法。

考虑这玩意咋维护。

其实很好维护，直接树上启发式合并就可以了。

复杂度是 $nD\log n$，$D\le \max(d(a_i))$。

[Code](https://paste.ubuntu.com/p/cPDXq3yW3x/)

---

