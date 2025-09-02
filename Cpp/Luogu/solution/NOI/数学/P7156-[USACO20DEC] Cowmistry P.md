# [USACO20DEC] Cowmistry P

## 题目描述

Bessie 的化学作业已经拖了很久，现在需要你的帮助！她需要用三种不同的化学品制造一种混合物。所有聪明的奶牛都知道，某些化学品之间不能进行混合，否则会产生爆炸。具体地说，两种标号为 $a$ 和 $b$ 的化学品当 $a⊕b≤K$ （$1≤K≤10^9$） 时可以出现在同一种混合物中。

注：这里，$a⊕b$ 表示非负整数 $a$ 与 $b$ 的「异或」。这一运算等价于在二进制下将每一对应位相加并且舍弃进位。例如， 
$$0⊕0=1⊕1=0$$
，
$$1⊕0=0⊕1=1$$
，
$$5⊕7=101_2⊕111_2=010_2=2$$
。

Bessie 有 $N$ 盒化学品，第 $i$ 个盒子内有标号从 $l_i$ 到 $r_i$ 的化学品（$0≤l_i≤r_i≤10^9$）。没有两个盒子中含有同一种化学品。她想要知道她可以得到多少种由三种不同的化学品混合而成的混合物。如果至少一种化学品出现在一种混合物中而没有出现在另一种中，则认为这两种混合物是不同的。由于答案可能非常大，输出对 $10^9+7$ 取模的结果。 

## 说明/提示

我们可以将所有化学品分为不能交叉混合的 $13$ 组：$(0 \ldots 15)$，$(16 \ldots 31)$，… $(192 \ldots 199)$。前 $12$ 组每组贡献了 $352$ 种混合物，最后一组贡献了 $56$ 种（因为所有 $\binom{8}{3}$ 种 $(192 \ldots 199)$ 中三种不同化学品的组合均可行），总共为 $352 \cdot 12 + 56 = 4280$。 

 - 测试点 3-4 满足 $\max(K, r_N) \le {10}^4$。
 - 测试点 5-6 对某个 $k \ge 1$ 满足 $K = 2^k - 1$。
 - 测试点 7-11 满足 $\max(K, r_N) \le {10}^6$。
 - 测试点 12-16 满足 $N \le 20$。
 - 测试点 17-21 没有额外限制。

对于所有测试点，满足 $1 \le N \le 2 \times {10}^4$。

供题：Benjamin Qi 

## 样例 #1

### 输入

```
1 13
0 199```

### 输出

```
4280```

## 样例 #2

### 输入

```
6 147
1 35
48 103
125 127
154 190
195 235
240 250```

### 输出

```
267188```

# 题解

## 作者：tzc_wk (赞：30)

[题面传送门](https://www.luogu.com.cn/problem/P7156)

题意：

> 给出集合 $S=[l_1,r_1]\cup[l_2,r_2]\cup[l_3,r_3]\cup\dots\cup[l_n,r_n]$ 和整数 $k$，求有多少个三元组 $(a,b,c)$ 满足：
>
> - $a,b,c\in S$，$a<b<c$
>
> - $a,b,c$ 两两异或得到的值均 $\leq k$
>
> 答案对 $10^9+7$ 取模。
>
> $1\leq n\leq 2\times 10^4$，$0\leq l_1\leq r_1\lt l_2\leq r_2\lt\dots\lt l_n\leq r_n\leq 10^9$

Yet another 1e9+7

Yet another 计数 dp

Yet another 我做不出来的题

阿巴细节题。

首先考虑优雅的暴力，也就是 $\max(k,r_n)\leq 10^6$ 那一档部分分。

建一棵包含 $S$ 所有元素的 trie 树。

设 $dp1_i$ 表示选择的三个数均在 $i$ 的子树中的方案数。假设我们当前考虑到从高到低的第 $x$ 位。

可以分为四种情况转移：

1. 选择的三个数均在 $i$ 的左子树内。这种情况又可分为两种情况：如果 $k$ 的从高到低的第 $x$ 位为 $1$，那么不论选哪三个点，它们两两异或起来从高到低第 $x$ 位都为 $0$。故不论选哪三个点都满足条件，贡献为 $\dbinom{siz_{ch_{i,0}}}{3}$ ；如果 $k$ 从高到低的第 $x$ 位为 $0$，那么贡献就是 $dp1_{ch_{i,0}}$。
2. 选择的三个数均在 $i$ 的右子树内，与第一种情况几乎一样。
3. 选择的三个数中，其中两个数 $a,b$ 在 $i$ 的左子树内，一个数 $c$ 在 $i$ 的右子树内。由于 $b\oplus c$ 从高到低的第 $x$ 位为 $1$，故这种情况只有当 $k$ 的从高到低的第 $x$ 位为 $1$ 的情况下才能发生。
4. 选择的三个数中，其中一个数 $a$ 在 $i$ 的左子树内，一个数 $b,c$ 在 $i$ 的右子树内，与第三种情况几乎一样。

不难发现，在这四种情况中前两种情况都是可以直接转移的，而后两种无法直接表示出来，需要引入另一个状态。

再设 $dp2_{i,j}$ 表示选择的三个数中两个数在 $i$ 的子树中，一个在 $j$ 的子树中的方案数。

继续分情况讨论，可以分为六种情况：

1. 在 $i$ 子树中的两个数都在 $i$ 的左子树中，在 $j$ 子树中的数在 $j$ 的左子树中。这种情况又可分为两种情况：如果 $k$ 的从高到低的第 $x$ 位为 $1$，那么不论选哪三个点，它们两两异或起来从高到低第 $x$ 位都为 $0$。故不论选哪三个点都满足条件，贡献为 $\dbinom{siz_{ch_{i,0}}}{2}\times siz_{ch_{j,0}}$。 如果 $k$ 从高到低的第 $x$ 位为 $0$，那么贡献就是 $dp2_{ch_{i,0},ch_{j,0}}$。

2. 在 $i$ 子树中的两个数 $a,b$ 都在 $i$ 的左子树中，在 $j$ 子树中的数 $c$ 在 $j$ 的右子树中。由于 $a\oplus c$ 从高到低的第 $x$ 位为 $1$，所以这种情况只有在当 $k$ 的从高到低的第 $x$ 位为 $1$ 的情况下才能发生。这种情况产生的贡献为 $dp2_{ch_{i,0},ch_{j,1}}$

3. 在 $i$ 子树中的两个数 $a,b$ 中 $a$ 在 $i$ 的左子树中，$b$ 在 $i$ 的右子树中，在 $j$ 子树中的数 $c$ 在 $j$ 的左子树中。由于 $b\oplus c$ 从高到低的第 $x$ 位为 $1$，所以这种情况只有在当 $k$ 的从高到低的第 $x$ 位为 $1$ 的情况下才能发生。我们还注意到，不论 $a$ 为何值都有 $a\oplus b<a\oplus c<b\oplus c$， 也就是说，不论 $a$ 取何值，只要 $b,c$ 满足条件，$a$ 一定满足条件。求出满足条件的 $b,c$ 个数后乘一个 $siz_{ch_{i,0}}$ 就行了。
4. 在 $i$ 子树中的两个数 $a,b$ 中 $a$ 在 $i$ 的左子树中，$b$ 在 $i$ 的右子树中，在 $j$ 子树中的数 $c$ 在 $j$ 的右子树中，与第三种情况几乎一样，只不过变成了求出满足条件的 $a,c$ 的个数 。
5. 在 $i$ 子树中的两个数 $a,b$ 都在 $i$ 的右子树中，在 $j$ 子树中的数 $c$ 在 $j$ 的左子树中，与第二种情况几乎一样。
6. 在 $i$ 子树中的两个数都在 $i$ 的右子树中，在 $j$ 子树中的数在 $j$ 的右子树中，与第一种情况几乎一样。

但是碰到这里我们又犯难了，情况 1,2,5,6 可以直接转移，但是情况 3,4 无法通过已有状态求出满足条件的 $b,c$ 的个数，这是我们又需要引入一个新状态。

再设 $dp3_{i,j}$ 表示两个数 $a,b$ 中一个数在 $i$ 的子树中，一个在 $j$ 的子树中的方案数。

又可以分四种情况：

1. $a$ 在 $i$ 的左子树中，$b$ 在 $j$ 的左子树中，这种情况又可分为两种情况：如果 $k$ 的从高到低的第 $x$ 位为 $1$，那么不论选哪两个点，它们两两异或起来从高到低第 $x$ 位都为 $0$。故不论选哪三个点都满足条件，贡献为 $siz_{ch_{i,0}}\times siz_{ch_{j,0}}$。 如果 $k$ 从高到低的第 $x$ 位为 $0$，那么贡献就是 $dp3_{ch_{i,0},ch_{j,0}}$。

2. $a$ 在 $i$ 的左子树中，$b$ 在 $j$ 的右子树中。由于 $a\oplus b$ 从高到低的第 $x$ 位为 $1$，所以这种情况只有在当 $k$ 的从高到低的第 $x$ 位为 $1$ 的情况下才能发生。
3. $a$ 在 $i$ 的右子树中，$b$ 在 $j$ 的左子树中，与第二种情况几乎一样。
4. $a$ 在 $i$ 的右子树中，$b$ 在 $j$ 的右子树中，与第一种情况几乎一样。

算下时间复杂度：$dp1$ 的时间复杂度肯定是没问题的，加个记忆化每个 $dp1_i$ 最多被计算一次。关键是 $dp2$ 和 $dp3$，$dp2$ 和 $dp3$ 状态是二维的。可合法的状态数真的是 $n^2$ 吗？非也。拿 $dp2$ 举例，只有当 $k$ 的第 $x$ 位为 $0$ 的时候才会调用 $dp2_{ch_{i,0},ch_{j,0}}$ 和 $dp2_{ch_{i,1},ch_{j,1}}$，当 $k$ 的第 $x$ 位为 $1$ 的时候才会调用 $dp2_{ch_{i,0},ch_{j,1}}$ 和 $dp2_{ch_{i,1},ch_{j,0}}$。稍微观察下即可发现，$i$ 与 $j$ 表示的数异或起来肯定是 $k$ 的一个前缀。这意味着对于每个 $i$ 有唯一的 $j$ 与之对应，故合法状态数只有 $\mathcal O(m)$，其中 $m$ 为 trie 数上的点数。故这个“优雅的暴力”是没问题的~~（真 nm 优雅）~~。

最后考虑 $k,r_n\leq 10^9$ 的情况。其实想到这一步本题就已经做完了 $80\%$ 了，虽然到这一步只包含了本题 $40\%$ 的部分分。

我们发现待插入的数很多，高达 $10^9$，但是这些数都是一段一段区间，区间个数只有 $2\times 10^4$。于是我们可以想到一个东西叫做线段树，可以通过线段树的思想将每个区间拆分成 $\log 10^9$ 个长度为 $2$ 的整数次幂的区间插入 trie 树。这样一来我们可以得到这样的 trie 树：trie 树上每个叶子节点代表一个大小为 $2^m$ 的满二叉树。

这样说有些抽象，举个例子，譬如我们要插入区间 $[0,6]$，如果按照之前的暴力我们会这样插：

![](https://cdn.luogu.com.cn/upload/image_hosting/2cw1c0tl.png)

但我们发现，黄色部分和绿色部分都是满二叉树，根本不用把它们建出来，所以我们索性把它们缩成一个“大点”：

![](https://cdn.luogu.com.cn/upload/image_hosting/joyvvjnt.png)

但是这样还是不太行啊？如果你 $dfs$ 到一个“大点”，对应到 $dp$ 值怎么计算呢？

可以考虑额外建 $31$ 个节点，编号为 $0,1,2,\dots,30$，节点 $i$ 的左右儿子都是节点 $i-1$，这样大小为 $2^m$ 的子树就等价于节点 $m$，$dfs$ 的时候直接在这 $31$ 个节点上记录 $dp$ 值就可以了。

代码不长，也就 100 行而已，不过细节实在是太太太太太太多了，这篇题解也写了整整 1 个小时。。。

 ```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=2e4;
const int LOG_N=30;
const int MAXT=1e6;
const int MAX=(1<<LOG_N)-1;
const int MOD=1e9+7;
const int TWO=5e8+4;
const int SIX=166666668;
int n,k,siz[MAXT+5],ch[MAXT+5][2],ncnt=LOG_N+1,rt=LOG_N+1,dep[MAXT+5];
bool isend[MAXT+5];
void update(int &k,int l,int r,int nl,int nr,int d){
	if(l==nl&&nr==r){k=LOG_N-d;return;}
	if(!~k) k=++ncnt,dep[k]=d;int mid=(l+r)>>1;
//	printf("%d %d %d %d %d %d\n",k,l,r,nl,nr,d);
	if(nr<=mid) update(ch[k][0],l,mid,nl,nr,d+1);
	else if(nl>mid) update(ch[k][1],mid+1,r,nl,nr,d+1);
	else update(ch[k][0],l,mid,nl,mid,d+1),update(ch[k][1],mid+1,r,mid+1,nr,d+1);
	siz[k]=siz[ch[k][0]]+siz[ch[k][1]];
}
int dp1[MAXT+5];
map<int,int> dp2[MAXT+5],dp3[MAXT+5];
int calc1(int x);
int calc2(int x,int y);
int calc3(int x,int y);
//calc1: 3 nodes in subtree of x
//calc2: 2 nodes in subtree of x and 1 node in subtree of y
//calc3: 1 nodes in subtree of x and 1 node in subtree of y
int calc1(int x){
//	if(x==0||x==1) return 0;
	if(~dp1[x]) return dp1[x];
	dp1[x]=0;
	if(~ch[x][0]){
		if(k>>(LOG_N-dep[x]-1)&1) dp1[x]=(dp1[x]+1ll*siz[ch[x][0]]*(siz[ch[x][0]]-1)%MOD*(siz[ch[x][0]]-2)%MOD*SIX%MOD)%MOD;
		else dp1[x]=(dp1[x]+calc1(ch[x][0]))%MOD;
	}
	if(~ch[x][1]){
		if(k>>(LOG_N-dep[x]-1)&1) dp1[x]=(dp1[x]+1ll*siz[ch[x][1]]*(siz[ch[x][1]]-1)%MOD*(siz[ch[x][1]]-2)%MOD*SIX%MOD)%MOD;
		else dp1[x]=(dp1[x]+calc1(ch[x][1]))%MOD;
	}
	if(~ch[x][0]&&~ch[x][1]) if(k>>(LOG_N-dep[x]-1)&1){
		dp1[x]=(dp1[x]+calc2(ch[x][0],ch[x][1]))%MOD;
		dp1[x]=(dp1[x]+calc2(ch[x][1],ch[x][0]))%MOD;
	}
//	printf("%d %d\n",x,dp1[x]);
	return dp1[x];
}
int calc2(int x,int y){
//	if(!x) return 0;
	if(dp2[x].find(y)!=dp2[x].end()) return dp2[x][y];
	dp2[x][y]=0;
	if(~ch[x][0]&&~ch[y][0]){
		if(k>>(LOG_N-dep[x]-1)&1)
			dp2[x][y]=(dp2[x][y]+1ll*siz[ch[x][0]]*(siz[ch[x][0]]-1)%MOD*TWO%MOD*siz[ch[y][0]]%MOD)%MOD;
		else dp2[x][y]=(dp2[x][y]+calc2(ch[x][0],ch[y][0]))%MOD;
	}
	if(~ch[x][0]&&~ch[y][1]) if(k>>(LOG_N-dep[x]-1)&1) dp2[x][y]=(dp2[x][y]+calc2(ch[x][0],ch[y][1]))%MOD;
	if(~ch[x][0]&&~ch[x][1]&&~ch[y][0]) if(k>>(LOG_N-dep[x]-1)&1) dp2[x][y]=(dp2[x][y]+1ll*calc3(ch[x][1],ch[y][0])*siz[ch[x][0]]%MOD)%MOD;
	if(~ch[x][0]&&~ch[x][1]&&~ch[y][1]) if(k>>(LOG_N-dep[x]-1)&1) dp2[x][y]=(dp2[x][y]+1ll*calc3(ch[x][0],ch[y][1])*siz[ch[x][1]]%MOD)%MOD;
	if(~ch[x][1]&&~ch[y][0]) if(k>>(LOG_N-dep[x]-1)&1) dp2[x][y]=(dp2[x][y]+calc2(ch[x][1],ch[y][0]))%MOD;
	if(~ch[x][1]&&~ch[y][1]){
		if(k>>(LOG_N-dep[x]-1)&1)
			dp2[x][y]=(dp2[x][y]+1ll*siz[ch[x][1]]*(siz[ch[x][1]]-1)%MOD*TWO%MOD*siz[ch[y][1]]%MOD)%MOD;
		else dp2[x][y]=(dp2[x][y]+calc2(ch[x][1],ch[y][1]))%MOD;
	}
//	printf("c2 %d %d %d\n",x,y,dp2[x][y]);
	return dp2[x][y];
}
int calc3(int x,int y){
	if(!x) return 1;
	if(dp3[x].find(y)!=dp3[x].end()) return dp3[x][y];
	dp3[x][y]=0;
	if(~ch[x][0]&&~ch[y][0]){
		if(k>>(LOG_N-dep[x]-1)&1) dp3[x][y]=(dp3[x][y]+1ll*siz[ch[x][0]]*siz[ch[y][0]]%MOD)%MOD;
		else dp3[x][y]=(dp3[x][y]+calc3(ch[x][0],ch[y][0]))%MOD;
	}
	if(~ch[x][0]&&~ch[y][1]) if(k>>(LOG_N-dep[x]-1)&1) dp3[x][y]=(dp3[x][y]+calc3(ch[x][0],ch[y][1]))%MOD;
	if(~ch[x][1]&&~ch[y][0]) if(k>>(LOG_N-dep[x]-1)&1) dp3[x][y]=(dp3[x][y]+calc3(ch[x][1],ch[y][0]))%MOD;
	if(~ch[x][1]&&~ch[y][1]){
		if(k>>(LOG_N-dep[x]-1)&1) dp3[x][y]=(dp3[x][y]+1ll*siz[ch[x][1]]*siz[ch[y][1]]%MOD)%MOD;
		else dp3[x][y]=(dp3[x][y]+calc3(ch[x][1],ch[y][1]))%MOD;
	}
//	printf("c3 %d %d %d\n",x,y,dp3[x][y]);
	return dp3[x][y];
}
int main(){
	fill1(ch);
	siz[0]=1;for(int i=1;i<=LOG_N;i++) ch[i][0]=ch[i][1]=i-1,siz[i]=(1<<i),dep[i]=LOG_N-i;
	memset(dp1,-1,sizeof(dp1));scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){int l,r;scanf("%d%d",&l,&r);update(rt,0,MAX,l,r,0);}
//	for(int i=0;i<=ncnt;i++) printf("%d %d %d %d\n",ch[i][0],ch[i][1],dep[i],siz[i]);
	printf("%d\n",calc1(rt));
	return 0;
}
/*
1 3
0 3

1 6
0 5

1 15
0 10
*/
 ```



---

## 作者：orangejuice (赞：13)

# 「USACO 2020.12 Platinum」Cowmistry 

[cnblogs界面](https://www.cnblogs.com/chasedeath/p/14429363.html)

令$m=\min\{2^t|2^t>k\}$，也就是$k$最高位+1

对于数轴，按照$[im,(i+1)m)$分组，显然跨过分组的数之间异或$\ge m>k$，不合法，扔掉

对于每组，直接看做是$[0,m-1]$，此时令$d=\frac{m}{2}$

将$[0,m-1]$分为$[0,d-1],[d,m-1]$，显然两段之内的数相互异或的结果$<d$，一定合法

也就是说，长度为$d$的段内随意选3个都合法

下面考虑跨过$d$的贡献，显然是一边选一个，一边选两个，此时这些数之间的异或和$\ge d$

以左边选一个为例，令$k'=k-d$

### $O(k\log k)$

考虑异或和中一定有$d$这一位，下面只需要对于$i\in[0,d-1]$暴力统计出$[d,m]$中有多少个数$j$满足$i\oplus j\leq k'$

可以前缀和之后$\log k$做到，从高到低依次考虑$k$每一个为1的二进制位$i$，如果查询的数这一位和$x$相同，那么下面可以任意选择

否则将$x\rightarrow x\oplus 2^i$

实现如下

```cpp
int Que(int x,int *A,int k){
	int ans=0;
	drep(i,19,0) if(k&(1<<i)) {
		int l=x&(~((1<<i)-1)),r=l+(1<<i)-1;
		ans+=A[r]-A[l-1];
		x^=1<<i;
	}
	return ans+A[x]-A[x-1];
}
```

得到个数$c$之后，接下来就是为$x$在$c$里选择两个匹配，就是$\sum \frac{c(c-1)}{2}$

由此得到一个$O(k\log k)$做法，可以通过前三档数据

```cpp
namespace part_klogk{
	const int N=1<<20|10;
	int m,A[N],B[N],ans;
	int Que(int x,int *A,int k){
		int ans=0;
		drep(i,19,0) if(k&(1<<i)) {
			int l=x&(~((1<<i)-1)),r=l+(1<<i)-1;
			ans+=A[r]-A[l-1];
			x^=1<<i;
		}
		return ans+A[x]-A[x-1];
	}
	void Solve(int l,int r) {
		int mid=(l+r)>>1;
		int c1=0,c2=0;
		rep(i,l,mid) c1+=A[i];
		rep(i,mid+1,r) c2+=A[i];
		ans=(ans+D3(c1))%P,ans=(ans+D3(c2))%P;
		rep(i,l,mid) if(A[i]) {
			int c=Que(i-l,B+mid+2,k-(m/2));
			ans=(ans+1ll*c*(c-1)/2)%P;
		}
		rep(i,mid+1,r) if(A[i]) {
			int c=Que(i-mid-1,B+l+1,k-(m/2));
			ans=(ans+1ll*c*(c-1)/2)%P;
		}
	}
	void Solve() {
		for(m=1;m<=k;) m<<=1;
		rep(i,1,n) rep(j,L[i],R[i]) A[j]++;
		rep(i,1,N-1) B[i]=B[i-1]+A[i-1];
		rep(i,0,R[n]/m) Solve(i*m,(i+1)*m-1);
		printf("%d\n",ans);
	}
}
```





$$\ $$

### $O(n\log k-n\log ^2 k)$

考虑对于$k'$，问题降阶为求区间$a$中的每一个数 ， 在区间$b$中查询合法的个数$cnt_a$

其中$a,b$区间可以认为对应相同的$[0,L-1]$，但是出现元素不同

此时，继续采用上面的方法进行分组，分组对象变为两组区间

令$m'=\min\{2^t|2^t>k'\},d'=\frac{m}{2}$，分组之后

对于$[0,d'-1],[d',m-1]$，显然两段之内异或$\leq d$，一定合法，加入答案$cnt_a$中

对于跨过区间的贡献，用下面的方法处理

左边区间对于右边区间继续递归进行查询，将得到的结果加上左边区间中数的个数

右边区间继续对于左边区间递归进行查询，将得到的结果加上右边区间中数的个数

问题不断降阶为子问题，会有$\log k$层子问题

每层子问题所有的区间可以分为$O(n)$段 **特殊** 的段

其他的部分要么完全覆盖要么为空，这些部分可以快速求出

发现答案如果用$(num,cnt)$表示当前查询结果为$num$的个数为$cnt$

每层可以用$O(n)$个不同的二元对表示结果

如此求得后，再自底向上合并得到答案

$$ \ $$

$$ \ $$

### 关于实现

如果真的按照上面的方法，一层层向下分裂区间，会面临着常数大，难以实现的问题

考虑将每个区间$[L_i,R_i]$插入线段树$[0,2^{30}-1]$

显然得到$O(n\log n)$个节点，在递增完全覆盖的节点打上标记

先递归进行第一层的分裂区间操作，对于打上标记的节点可以分成$\frac{r-l+1}{m}$个完全覆盖区间

这些完全覆盖区间的答案可以$O(1)$求出

$$ \ $$

分裂完成后，每次查询的区间用$(a,b,L,k,f1,f2)$表示

其中$a$表示查询区间对应节点，$b$表示被查询区间对应节点

$L$表示区间长度，$f1,f2$表示$a,b$是否继承到上层的完全覆盖标记

如此每次合并$(ls_a,rs_b),(rs_a,ls_b)$的查询结果即可

当$b$为空或者为完全覆盖时，答案可以$O(1)$得到

当$a$为空时，可以得到空答案

从这样的底层向上合并，每个元素被合并次数$O(\log k)$

$$ \ $$

没有仔细分析复杂度，应该就是$O(n\log k-n\log ^2 k)$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int,int> Pii;
#define mp make_pair
#define pb push_back
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
char IO;
int rd(){
    int s=0;
    while(!isdigit(IO=getchar()));
    do s=(s<<1)+(s<<3)+(IO^'0');
    while(isdigit(IO=getchar()));
    return s;
}

const int N=2e4+10,P=1e9+7,I2=(P+1)/2,I3=(P+1)/3,U=1<<30;

int n,m,k;
int L[N],R[N];
int Check(){
    for(int i=k;i;i>>=1) if(~i&1) return 0;
    return 1;
}
int D3(int n){ return 1ll*n*(n-1)/2%P*(n-2)%P*I3%P; }
int D2(int n){ return 1ll*n*(n-1)/2%P; }

const int M=N*60;
int s[M],ls[M],rs[M],t[M],cnt,rt;
//在线段树上插入节点，打上标记，同时处理出size便于下面计算
void Ins(int &p,int l,int r,int ql,int qr){
    if(!p) p=++cnt;
    s[p]+=min(qr,r)-max(ql,l)+1;
    if(ql<=l && r<=qr) { t[p]=1; return; }
    int mid=(l+r)>>1;
    if(ql<=mid) Ins(ls[p],l,mid,ql,qr);
    if(qr>mid) Ins(rs[p],mid+1,r,ql,qr);
}

int ans;
int Up(int k){ return 1<<(32-__builtin_clz(k)); }
typedef vector <Pii> V;
V Union(const V &A,const V &B){
    int p1=0,p2=0,s1=A.size(),s2=B.size();
    V R;
    // 这里是否归并并不影响复杂度
    while(p1<s1 || p2<s2) {
        if(p1<s1 && (p2==s2||A[p1]<B[p2])) {
            if(R.size() && R.back().first==A[p1].first) R.back().second+=A[p1].second;
            else R.pb(A[p1]);
            p1++;
        } else {
            if(R.size() && R.back().first==B[p2].first) R.back().second+=B[p2].second;
            else R.pb(B[p2]);
            p2++;
        }
    }
    return R;
}
V Calc(int a,int b,int L,int k,int f1,int f2){
    f1|=t[a],f2|=t[b];
    V Res;
    // 底层情况O(1)解决
    if(!f1 && !a) return Res;
    if(f2) return Res.pb(mp(k+1,f1?L:s[a])),Res;
    if(!b) return Res.pb(mp(0,f1?L:s[a])),Res;
    int m=Up(k);
    // L>m说明还要继续进行分裂
    if(L>m) return Union(Calc(ls[a],ls[b],L/2,k,f1,f2),Calc(rs[a],rs[b],L/2,k,f1,f2));
    // 进入降阶子问题，左查右，右查左
    k-=m/2;
    V A=Calc(ls[a],rs[b],L/2,k,f1,f2);
    for(auto &i:A) i.first+=f2?L/2:s[ls[b]];
    V B=Calc(rs[a],ls[b],L/2,k,f1,f2);
    for(auto &i:B) i.first+=f2?L/2:s[rs[b]];
    return Union(A,B);
}

int cm;
void Solve(int p,int L){
    if(!p) return;
    // 完全覆盖的部分答案可以快速求出
    if(t[p]) { cm+=L/m; return; }
    // 已经完成分裂，此时进入第一层子问题
    if(L==m) {
        // 贡献分为 
        // 左选3 ， 右选 3
        ans=(ans+D3(s[ls[p]]))%P,ans=(ans+D3(s[rs[p]]))%P;
        // 左1，右2
        V A=Calc(ls[p],rs[p],m/2,k-m/2,0,0);
        // 左2，右1
        V B=Calc(rs[p],ls[p],m/2,k-m/2,0,0);
        for(auto i:A) ans=(ans+1ll*D2(i.first)*i.second)%P;
        for(auto i:B) ans=(ans+1ll*D2(i.first)*i.second)%P;
        return;
    }
    Solve(ls[p],L/2),Solve(rs[p],L/2);
}
int main(){
    n=rd(),k=rd();
    rep(i,1,n) { int l=rd(),r=rd(); Ins(rt,0,U-1,l,r); }
    m=Up(k),Solve(rt,U);
    // O(1)求得完全覆盖部分的答案
    int t=(2ll*D3(m/2)+1ll*D2(k-m/2+1)*m)%P;
    ans=(ans+1ll*cm*t)%P;
    printf("%d\n",ans);
}


```



































































































---

## 作者：ETHANK (赞：10)

**题目大意：**

给 $N$ 个区间 $[l_i,r_i]$ ，问在所有区间的并中有多少个三元组 $(a,b,c)$ ，满足：

- $a,b,c$ 互不相同 .
- $a\oplus b,a\oplus c,b\oplus c\le K$ .

输出对 $10^9+7$ 取模。

数据范围：$1\le N\le 2\times 10^4,1\le K\le 10^9$ .

> 题目难度：NOI/NOI+/CTSC

**解析：**

~~没人写官方题解思路啊，那我写一手~~

首先对 $K+1$ 这样就把 $\le$ 转化成了 $<K$ 。定义 $P$ 为最小的 $2$ 的次幂使得 $P>K$ ，那么显然 $(a,b,c)$ 必须满足（否则会有 $>K$ 且不为 0 的位出现）：
$$
\lfloor\frac{a}{P}\rfloor=\lfloor\frac{b}{P}\rfloor=\lfloor\frac{c}{P}\rfloor
$$
 接下来分类讨论：

1. $\lfloor\frac{a}{P/2}\rfloor=\lfloor\frac{b}{P/2}\rfloor=\lfloor\frac{c}{P/2}\rfloor$

此时 $a\oplus b$ 在 $P/2$ 以上的位均为 $0$ ，显然满足要求，统计相等的数量并对答案加上 $\binom{cnt}{3}$ 即可。

2. 其他情况

由于 $P$ 以上的二进制位值都一样，抽屉原理得出必有两项 $a,b$ 满足 $\lfloor\frac{a}{P/2}\rfloor=\lfloor\frac{b}{P/2}\rfloor$ 。不妨考虑 $\lfloor\frac{a}{P/2}\rfloor=\lfloor\frac{b}{P/2}\rfloor>\lfloor\frac{c}{P/2}\rfloor$ 时的情况，由于显然有 $a\oplus b<P/2<K$ ，只用考虑对每个 $c$ 求所有满足 $c\oplus a<K$ 的 $a$ 。

具体地，有 $c\in[Pt+P/2,Pt+P)$ ，集合 $S$ 为 所有 $x\in[Pt,Pt+P/2)$ 且 $x\oplus c<K$ 的 $x$ ，对于该 $c$ 的答案就是 $\binom{|S|}{2}$ 。

下面考虑如何实现，首先我们将每个原区间按上述讨论拆为长度为 $P$ 的整块和不到 $P$ 的散块。对于长度为 $P$ 的块，答案为
$$
2\times\binom{P/2}{3}+P\times\binom{K-P/2}{2}
$$
接下来把散块离线处理，

```cpp
void solve(vector <pii> v){
    int p2=p/2;
    vector<pii>tot[2];
    for(auto& t:v){
        if(t.fi/p2<t.se/p2){
            tot[0].push_back({t.fi,p2-1});
            tot[1].push_back({0,t.se-p2});
        }else
            tot[t.fi/p2].push_back({t.fi%p2,t.se%p2});
    }
    rep(i,0,1){
        add(ans,c3(totlen(tot[i])));//第一类
        solve2(tot[i],tot[i^1],p2,0);//第二类
    }
}
```

第一类的答案很好统计，考虑如何处理第二类。可以将第二类划分为更小的两个区间进行计算，这样的分治最多进行 $O(\log K)$ 层，可以通过。

时间复杂度：$O(N\log K)$ .

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int M=1e9+7,i6=166666668;
int n,k,p=1;
ll ans;
ll c2(ll x){return 1ll*x*(x-1)/2%M;}
ll c3(ll x){return 1ll*x*(x-1)%M*(x-2)%M*i6%M;}
inline void add(ll &a,const ll b){a=(a+b)%M;}
inline ll totlen(const vector<pii>&v){
    ll len=0;for(auto &t:v)len+=t.se-t.fi+1;
    return len;
}
void solve2(const vector<pii>&a,const vector<pii>&b,int block,int cur){
    //基本情况
    if(!(int)a.size())return;
    if(!(int)b.size()){
        ans=(ans+c2(cur)*totlen(a)%M)%M;
        return;
    }
    vector<pii> des{{0,block-1}};
    if (b == des) { // b = [0,block)
		cur =(cur+((block-1)&k))%M;
		ans=(ans+c2(cur)*totlen(a)%M)%M;
		return;
	}
	//继续往下分治
	vector<pii> A[2], B[2];
	auto ad = [&](vector<pii>& v,pii p) {
		p.fi=max(p.fi,0),p.se=min(p.se,block/2-1);
		if (p.fi > p.se) return;
		v.push_back(p);
	};
	for (auto& t: a) ad(A[0],t), ad(A[1],{t.fi-block/2,t.se-block/2});
	for (auto& t: b) ad(B[0],t), ad(B[1],{t.fi-block/2,t.se-block/2});
	if (k&(block/2)) {
		for(int i=0; i<2; ++i) solve2(A[i],B[i^1],block/2,(cur+totlen(B[i]))%M);
	} else {
		for(int i=0; i<2; ++i) solve2(A[i],B[i],block/2,cur);
	}
}
//处理a/P相等的散块
void solve(vector <pii> v){
    int p2=p/2;
    vector<pii>tot[2];
    for(auto& t:v){
        if(t.fi/p2<t.se/p2){
            tot[0].push_back({t.fi,p2-1});
            tot[1].push_back({0,t.se-p2});
        }else
            tot[t.fi/p2].push_back({t.fi%p2,t.se%p2});
    }
    rep(i,0,1){
        add(ans,c3(totlen(tot[i])));//第一类
        solve2(tot[i],tot[i^1],p2,0);//第二类
    }
}
int main(){
    n=read(),k=read();
    ++k;while(p<=k)p<<=1;
    k=k-p/2;
    ll sum=(p*c2(k)%M+2*c3(p/2)%M)%M;//整块答案直接统计
    map<int,vector<pii>>todo;
    rep(i,1,n){
        int l=read(),r=read();
        int LL=l/p,RR=r/p;
        if(LL!=RR){
            add(ans,sum*(RR-LL-1)%M);
            todo[LL].push_back({l%p,p-1});
            todo[RR].push_back({0,r%p});
        }else todo[LL].push_back({l%p,r%p});
    }
    for(auto& t:todo)solve(t.se);
    printf("%lld\n",ans%M);
    return 0;
}
```



---

## 作者：monstersqwq (赞：5)

大恶心题，不知道出题人手机里有没有一款开放世界冒险游戏。

先把所有区间都扔到 trie 上，容易发现将形成 $O(n\log V)$ 个互不包含的子树，后面只考虑这些子树。

设 $m$ 为 $k$ 在二进制下的位数。

首先考虑 $(a,b,c)$ 合法的条件是什么，$m$ 位以上的必定要全相等，如果第 $m$ 位也全相等就直接合法了。否则不妨设 $b,c$ 在第 $m$ 位相等，且 $a$ 在第 $m$ 位与它们不同，那么只需要满足 $a\oplus c\le k,a\oplus b\le k$ 即可，也就是说，如果我们枚举所有被包含的化学品，就可以在 $O(k\log k)$ 的时间复杂度内解决这一部分。

如果有一个子树代表的前缀最低位比 $m$ 位还高，那么如果选了这棵子树内的一个点，其它两个点也必定在这棵子树内，并且可以发现每棵子树的贡献仅与其代表前缀最低位有关，这一部分易于统计。下面认为剩余子树都不满足这个条件。

先考虑第 $m$ 位全相等的情况，考虑枚举所有的代表前缀最低位为第 $m$ 位的子树，这一子树内任取三个点均满足这种情况，且不会漏数，由于上一段解决了更高位的问题，这里的复杂度为 $O(n\log V)$。

在解决下一部分之前，先观察一下对于某个 $x$，满足 $x\oplus y\le k$ 的 $y$ 的形态，其可以表示为，在 trie 上从根到 $x\oplus k$ 的路径上，如果 $k$ 的某位是 $1$，那么在路径上对应位置伸出一棵子树，这些子树内的点就是所有的 $y$。

那么对于一棵子树内的所有 $x$（设这棵子树代表的前缀为 $s$，最低位为 $d$），$y$ 的形态大致为首先先从根到 $s\oplus k$ 的第 $d$ 位并进行统计，后面每次从左右儿子中随机选择一个向下走，由 $k$ 的当前位决定是否将另一个儿子包含的子树大小加入。

对于不全相等的情况，我们枚举所有区间形成的那 $O(n\log V)$ 个子树 $s$。对于 $s$ 中的所有数 $x$，满足 $x\oplus y\le k$ 且 $x,y$ 的 $m$ 位不同的 $y$ 个数设为 $cnt$，要求的即为 $\sum\binom{cnt}{2}$，只需要维护 $\sum cnt^2,\sum cnt$ 即可。

考虑 dp，对于某个 trie 上的点 $x$，设 $dp_{x,i(0/1/2)}$ 表示在 $x$ 子树内，随机选择左右儿子向下走，并仅加入位数比 $x$ 代表前缀最低位还低且 $k$ 对应位为 $1$ 的那些子树，得到的值的 $i$ 次方和，这个 dp 是可以展开平方式转移的。

对于枚举到的每个 $s$，在其 $\oplus k$ 后得到的对应子树 $t$ 上用其 dp 值进行计算，可以在 $O(n\log^2 V)$ 或 $O(n\log V)$ 的时间复杂度内做完整个问题。

不太好写。

---

## 作者：dengchengyu (赞：1)

## USACO 20Dec P Cowmistry 题解

这里把官方题解写得详细一点。

首先把 $K$ 加一，于是 $\le$ 转化为 $<$。我们找到最小的大于 $K$ 的 2 的幂 $P$。那么如果三种化学品 $a,b,c$ 能被算入答案，一定满足：
$$
\lfloor\frac {a}{P}\rfloor=\lfloor\frac {b}{P}\rfloor=\lfloor\frac {c}{P}\rfloor
$$
那么我们一开始把 $\lfloor\frac {a}{P}\rfloor$ 相等的数放在一起，接下来分类：

### 第一类

记 $Q=\frac P2$，若
$$
\lfloor\frac {a}{Q}\rfloor=\lfloor\frac {b}{Q}\rfloor=\lfloor\frac {c}{Q}\rfloor
$$
则 $a,b,c$ 显然满足条件，所以如果一种 $\lfloor\frac {a}{Q}\rfloor$ 相等的数有 $cnt$ 个，它对答案的贡献为 $\binom {cnt}3$。

### 第二类

否则，先假设
$$
\lfloor\frac {a}{Q}\rfloor=\lfloor\frac {b}{Q}\rfloor>\lfloor\frac {c}{Q}\rfloor
$$
对于被 $[kP,(k+1)P)$ 包含的区间，我们计算一个数在 $[kP,kP+Q)$，另外两个数在 $[kP+Q,(k+1)P)$ 中的方案数。

那么对于左边的每个数 $x$，求出右边使得 $x\oplus y<K$ 的 $y$ 的个数 $cnt$，对答案的贡献为 $\binom{cnt}2$。

### 实现

我们将给定的区间按照 $P$ 分块，分为整块和散块。

我们先考虑整块的答案，即 $[0,P)$ 的答案。对于第一类就是 $2\binom Q3$；对于第二类，对于左边的每一个数，右边是全集分别与其异或，那么异或出来的值也是全集，所以即 $K-Q$ 种满足条件，贡献为 $2\times Q\times \binom{K-Q}2=P\binom{K-Q}2$。所以整块的答案为：
$$
2\times \binom Q3+P\times \binom {K-Q} 2
$$
对于散块，我们对两边的区间同时分治，直到两边都拆分成 $2$ 的次幂的区间时用上面的公式算。

例如把 $[0,3][5,7],[8,11][14,15]$ 拆成 $[0,1][2,2][5,5][6,7],[8,11][14,15]$。

对于每一层，若 $K$ 在这一位为 $0$，则两边这一位必须取相同值。

当 $K$ 在这一位为 $1$ 时，可以选择两边取不同值然后递归，也可以在其中一边选一个传参，也可以当前选三个数计入答案。

复杂度为 $O(n\log K)$。代码：

```cpp
const int mod=1e9+7;
int pow1(int x,int y) {
	int res=1;
	for(;y;y>>=1,x=(ll)x*x%mod) if(y&1) res=(ll)res*x%mod;
	return res;
}
void inc(int &x,int y) {x+=y; if(x>=mod) x-=mod;}
int inv6=pow1(6,mod-2),inv2=pow1(2,mod-2);
int cho2(int x) {
	return (ll)x*(x-1)%mod*inv2%mod;
}
int cho3(int x) {
	return (ll)x*(x-1)%mod*(x-2)%mod*inv6%mod;
}
int cnt(vp &x) {
	int res=0;
	for(auto i:x) res+=i.se-i.fi+1;
	return res;
}
int ans=0;
int n,K;
void solve2(vp &L,vp &R,int p,int c,int s) {
	if(L.empty()||R.empty()||c<0) return;
	if(cnt(L)==p&&cnt(R)==p) {
		inc(ans,(ll)2*p*cho2(K%p)%mod);
		inc(ans,(ll)p*(K%p)%mod*s%mod);
		return;
	}
	vp a[2],b[2];
	for(auto i:L) {	
		if(i.fi<p/2&&i.se>=p/2) a[0].pb({i.fi,p/2-1}),a[1].pb({0,i.se-p/2});
		else if(i.se<p/2) a[0].pb(i);
		else a[1].pb({i.fi-p/2,i.se-p/2});
	}
	for(auto i:R) {	
		if(i.fi<p/2&&i.se>=p/2) b[0].pb({i.fi,p/2-1}),b[1].pb({0,i.se-p/2});
		else if(i.se<p/2) b[0].pb(i);
		else b[1].pb({i.fi-p/2,i.se-p/2});
	}
	if(K>>c&1) {
		solve2(a[0],b[1],p/2,c-1,s+cnt(a[1])+cnt(b[0]));
		solve2(a[1],b[0],p/2,c-1,s+cnt(a[0])+cnt(b[1]));
		inc(ans,(ll)cnt(a[0])*cnt(b[0])%mod*s%mod);
		inc(ans,(ll)cnt(a[1])*cnt(b[1])%mod*s%mod);
		inc(ans,(ll)cnt(a[0])*cho2(cnt(b[0]))%mod);
		inc(ans,(ll)cnt(b[0])*cho2(cnt(a[0]))%mod);
		inc(ans,(ll)cnt(a[1])*cho2(cnt(b[1]))%mod);
		inc(ans,(ll)cnt(b[1])*cho2(cnt(a[1]))%mod);
	}
	else {
		solve2(a[0],b[0],p/2,c-1,s);
		solve2(a[1],b[1],p/2,c-1,s);
	}
}
int P,ct=0;
void solve1(vp &x) {
	vp L,R;
	for(auto i:x) {
		if(i.fi<P/2&&i.se>=P/2) L.pb({i.fi,P/2-1}),R.pb({0,i.se-P/2});
		else if(i.se<P/2) L.pb(i);
		else R.pb({i.fi-P/2,i.se-P/2});
	}
	inc(ans,cho3(cnt(L)));
	inc(ans,cho3(cnt(R)));
	solve2(L,R,P/2,ct-1,0);
}
map<int,vp> mp;
signed main(){
	frein("1");
	read(n,K);
	++K,P=1,ct=-1; while(P<=K) P<<=1,++ct;
	int res1=(2ll*cho3(P/2)+(ll)P*cho2(K-P/2))%mod;
	fo(i,1,n) {
		int l,r; read(l,r);
		if(l/P!=r/P) {
			inc(ans,(ll)res1*(r/P-l/P-1)%mod);
			mp[l/P].pb({l%P,P-1});
			mp[r/P].pb({0,r%P});
		}
		else mp[l/P].pb({l%P,r%P});
	}
	for(auto &i:mp) solve1(i.se);
	write(ans);
	return 0;
}
```

---

## 作者：Sky_Maths (赞：1)

# 前言
**基本**上是自己做的（0.5 道黑题）！

虽然做之前还参考了一下 tzc_wk 的题解，但式子是自己推的，所以算一半 QWQ。

建议各位先做一下 [Keep XOR Low(From CF)](https://www.luogu.com.cn/problem/CF1616H) 和这道题差不多，甚至不能称为弱化版，因为那道题的转移状态更多，~~我错了好久~~。

# 正文
这是一道 Trie 树上数位 DP 的练习题，首先设 $f_u$ 为以 $u$ 为根的子树内选 3 个，且存在限制（对于之后的数位都要考虑 $\le k$ 的限制），即二进制前缀为 $u'$ 的中选三个。

因为存在 $\le k$ 的限制，考虑对 $k$ 在该位的值分类讨论。

以下 $ul,ur$ 分别代表 $u$ 的左儿子和右儿子，$F_u$ 代表在 $u$ 的子树内不考虑限制选 $3$ 个的数量。

若 $k$ 在 $i$ 位上为 $0$，$f_u=f_{ul}+f_{ur}$。

若 $k$ 在 $i$ 位上为 $1$，发现可能会“分裂”，故加入另一种状态设计（就是多写一个函数），$g(u,v)$ 代表在 $u,v$ 中分别选 $1,2/2,1$ 个的种类数（考虑限制）。得到$f_u=F_{ul}+F_{ur}+g(ul,ur)$。

容易得到 $F_u=C_{size_u}^{3}$，接下来考虑 $g(u,v)$ 同样分类讨论。

若 $k$ 在 $i$ 位上为 $0$，$g(u,v)=g(ul,vl)+g(ur,vr)$。

若 $k$ 在 $i$ 位上为 $1$，这个真的很麻烦，我直接采取画图法。

```
左边/代表ul，ur/vl/vr同理
// \
// /
/\ \
/\ /
\\ \
\\ /
\ //
/ //
\ /\
/ /\
\ \\
/ \\
```

多吧，有 $12$ 种，请先尝试自己推一下公式，但是有一个坑。

下面给出公式，其中 $h(u,v)$ 表示在 $u,v$ 中各找出 $1$ 个且考虑限制的种类数，$size$ 用 $S$ 简写。

$g(u,v)=g(ul,vr)+g(ur,vl)+h(ul,vr)\cdot (S_{ur}+S_{vl})+h(ur,vl)\cdot (S_{ul}+S_{vr})+
C_{S_{ul}}^2\cdot S_{vl}+
C_{S_{ur}}^2\cdot S_{vr}+
C_{S_{vl}}^2\cdot S_{ul}+
C_{S_{vr}}^2\cdot S_{ur}$

还有 $h(u,v)$，同样分类讨论。

若 $k$ 在 $i$ 位上为 $0$，$h(u,v)=h(ul,vl)+h(ur,vr)$。

若 $k$ 在 $i$ 位上为 $1$，$h(u,v)=h(ur,vl)+h(ul,vr)+S_{ul}\cdot S_{vl}+S_{ur}\cdot S_{vr}$。

发现若有一棵大小为 $n$ 的树

$$h(u,v):hT(n)=2hT(\frac{n}{2})+1=n$$

$$g(u,v):gT(n)\le 2gT(\frac{n}{2})+(2hT(\frac{n}{2})+1=n)=n\log n$$

$$f(u):fT(u)\le\max(2fT(\frac{n}{2}),2gT(\frac{n}{2})=n \log n)=n \log n$$

而只要我们采用懒标记，树的大小 $m\approx n\log n$，代入上式（即令 $n$ 变成 $n\log n$），得到时间复杂度为 $O(n\log n \log(n\log n))$

但是 $fT,gT$ 都是 $\le$ 所以不一定能跑满，而且 $n\le 2\cdot 10^4$，其实就是 $m\le 3\cdot 10^5$ 时的 $O(m\log m)$。

所以是没问题的。

当然，还有一个细节，就是“懒节点”的设置，具体看代码。

# 代码
```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(register int i(l),i##end(r);i<=i##end;++i)
#define per(i,r,l) for(register int i(r),i##end(l);i>=i##end;--i)
using namespace std;
#define ci const int
#define pt printf
#define gc getchar
#define pc putchar
typedef long long ll;
inline void rd(int &x) {
	x=0; char ch=gc(); bool f=0;
	while((ch<'0'||ch>'9')&&ch!='-') ch=gc();
	if(ch=='-') f=true,ch=gc();
	while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
	if(f) x=-x;
}
inline void wt(ll x) {
	if(x<10) return pc(x+'0'),void();
	wt(x/10);
	pc(x%10+'0');
}

ci mod = 1e9 + 7;
ci X2 = 5e8 + 4;
ci X3 = 333333336;
ci X6 = 166666668;
ci LOG_V = 29;
ci V = (1LL<<(LOG_V+1))-1;
ci N = 1e6 + 9;
int n,x,rt,cnt;
int siz[N],id[N];
int ch[N][2];
#define ls ch[u][0]
#define rs ch[u][1]
void insert(int &u,int l,int r,int a,int b,int i) {
	if(r<a||b<l) return;
	if(a<=l&&r<=b) {
		u=id[i+1];
		return;
	}
	if(!u) u=++cnt;
	int mid=(1LL*l+r)/2;
	insert(ls,l,mid,a,b,i-1);
	insert(rs,mid+1,r,a,b,i-1);
	siz[u]=siz[ls]+siz[rs];
}
#define ul ch[u][0]
#define ur ch[u][1]
#define vl ch[v][0]
#define vr ch[v][1]
#define mp make_pair
typedef pair<int,int> pii;
map<pii,int> H; int h(int u,int v,int i) {
	if(!u||!v) return 0;
	if(i<0) return 1;
	if(H.find(mp(u,v))!=H.end()) return H[mp(u,v)];
	if((x>>i)&1) {
		return H[mp(u,v)]=(h(ur,vl,i-1)+h(ul,vr,i-1)+1LL*siz[ul]*siz[vl]%mod+1LL*siz[ur]*siz[vr]%mod)%mod;
	}
	else return H[mp(u,v)]=(h(ul,vl,i-1)+h(ur,vr,i-1))%mod;
}
ll tw(int u) {return 1LL*siz[u]*(siz[u]-1)%mod*X2%mod;}
map<pii,int> G; int g(int u,int v,int i) {
	// return 0;
	if(i<0||!u||!v) return 0;
	if(G.find(mp(u,v))!=G.end()) return G[mp(u,v)];
	if((x>>i)&1) {
		int res1=(g(ul,vr,i-1)+g(ur,vl,i-1))%mod;
		int res2=(tw(ul)*siz[vl]+tw(ur)*siz[vr]+tw(vl)*siz[ul]+tw(vr)*siz[ur])%mod;
		int res3=(1LL*h(ul,vr,i-1)*(siz[ur]+siz[vl])+1LL*h(ur,vl,i-1)*(siz[ul]+siz[vr]))%mod;
		return G[mp(u,v)]=((res1+res2)%mod+res3)%mod;
	}
	else {
		return G[mp(u,v)]=(g(ul,vl,i-1)+g(ur,vr,i-1))%mod;
	}
}
int th(int u) {return 1LL*siz[u]*(siz[u]-1)%mod*(siz[u]-2)%mod*X6%mod;}
map<int,int> F; int f(int u,int i) {
	if(!u||i<0) return 0;
	if(F.find(u)!=F.end()) return F[u];
	if((x>>i)&1) return F[u]=(1LL*th(ls)+th(rs)+g(ls,rs,i-1))%mod;
	else return F[u]=(f(ls,i-1)+f(rs,i-1))%mod;
}
main() {
	rd(n);
	rd(x);
	rep(i,0,LOG_V-1) {
		siz[id[i]=(++cnt)]=1<<i;
		if(i) ch[id[i]][0]=ch[id[i]][1]=id[i-1];//之前忘写了
	}
	int l,r; rep(i,1,n) {
		rd(l);
		rd(r);
		insert(rt,0,V,l,r,LOG_V);
	}
	printf("%d\n",f(rt,LOG_V));
	return 0;
}
```

---

## 作者：gary2005 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7156)

这题是一个非常恶心的分类讨论题。
首先可以将所有的二进制建在一个trie树上，然后进行dp。

设$dp[i]$表示三个二进制的LCA是属于i的子树。

然后一个显然的转移：$dp[i]=dp[l[i]]+dp[r[i]]$，也就是LCA分别属于两个儿子的子树，或者三个数的LCA正好是$i$。也就是有一个走到了一边，两个到了另一边。

可以发现难以用这个dp状态算分叉的情况。

所以我们引入$dp2[i][j]$表示两个属于i的子树，一个属于j的子树，需要哪个落单的必须和那两个xor起来<=k，$i\neq j$。可以发现，到了这一步前面的所有数$xor$起来正好是k的前缀。

所以我们可以通过$i$推出$j$。也就是说，我们只需要记录$dp2[i]$就好了。

$dp2[i]$的转移:$dp2[l[i]]+dp2[r[i]]$+那两个在i处再次分叉+已经可以保证 $\leq k$。

然后再次分叉的又不好算了，我们再引入$dp1[i][j]$。

表示一个在i的子树，一个在j的子树，的方案数，可以用上面的观察，优化到一维$dp1[i]$。转移也比较简单。
```cpp
/*
{
######################
#       Author       #
#        Gary        #
#        2020        #
######################
*/
#include<bits/stdc++.h>
#define rb(a,b,c) for(int a=b;a<=c;++a)
#define rl(a,b,c) for(int a=b;a>=c;--a)
#define LL long long
#define IT iterator
#define PB push_back
#define II(a,b) make_pair(a,b)
#define FIR first
#define SEC second
#define FREO freopen("check.out","w",stdout)
#define rep(a,b) for(int a=0;a<b;++a)
#define SRAND mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define random(a) rng()%a
#define ALL(a) a.begin(),a.end()
#define POB pop_back
#define ff fflush(stdout)
#define fastio ios::sync_with_stdio(false)
#define check_min(a,b) a=min(a,b)
#define check_max(a,b) a=max(a,b)
using namespace std;
//inline int read(){
//    int x=0;
//    char ch=getchar();
//    while(ch<'0'||ch>'9'){
//        ch=getchar();
//    }
//    while(ch>='0'&&ch<='9'){
//        x=(x<<1)+(x<<3)+(ch^48);
//        ch=getchar();
//    }
//    return x;
//}
const int INF=0x3f3f3f3f;
typedef pair<int,int> mp;
/*}
*/
const int MOD=1e9+7;
int n,k;
vector<int> cover;
vector<int> ls,rs;
vector<int> depth;
vector<int> match;
int get(int num,int pos){
	return (num>>(30-pos))&1;
}
int getval(int num,int pos){
	return num&((1<<pos)-1);
}
void extand(int idx,bool flag=false){
	if(ls[idx]) return;
	ls[idx]=cover.size();
	rs[idx]=cover.size()+1;
	cover.PB(0);
	cover.PB(0);
	ls.PB(0),ls.PB(0);
	rs.PB(0),rs.PB(0);
	depth.PB(depth[idx]+1);
	depth.PB(depth[idx]+1);
	match.PB(0);
	match.PB(0);
	if(flag){
		cover[ls[idx]]=cover[rs[idx]]=1<<(30-depth[ls[idx]]);
	}
	extand(match[idx],(cover[match[idx]]!=0));
	if(get(k,depth[idx]+1)){
		match[ls[idx]]=(rs[match[idx]]);
		match[rs[idx]]=(ls[match[idx]]);
	}
	else{
		match[ls[idx]]=(ls[match[idx]]);
		match[rs[idx]]=(rs[match[idx]]);
	}
}
void insert(int root,int l,int r,int is=0){
	if(l>r) return;
	cover[root]+=(r-l+1);
	if(r-l+1==(1<<(30-depth[root]))){
		queue<int> q;
		q.push(root);
		while(!q.empty()){
			int now=q.front();
			q.pop();
			if(now!=root){
				cover[now]+=1<<(30-depth[now]);
			}
			if(ls[now]){
				q.push(ls[now]);
				q.push(rs[now]);
				assert(rs[now]);
			}
		}
//		cout<<root<<' '<<match[root]<<" "<<l<<' '<<r<<' '<<depth[root]<<' '<<cover[root]<<endl;
		return;
	}
	extand(root);
	int mid=is;
	mid+=1<<(30-depth[root]-1);
	insert(ls[root],l,min(r,mid-1),is);
	insert(rs[root],max(l,mid),r,mid);
}
vector<int> dp1,dp2,dp3,g1,g2,g3;
/*
dp1[i]:一个选在i为根的子树，另一个选在match[i]为根的子树 
dp2[i]:两个选在i为根的子树，另一个选在match[i]为根的子树
dp3[i]: i为根的子树的方案 
*/
const int SIX=166666668;
void calc1(int rt){
	if(!cover[rt]) return;
	if(ls[rt]==0){
		if(cover[rt]&&cover[match[rt]]){
			dp1[rt]=1<<(30-depth[rt]);
			dp1[rt]=1ll*dp1[rt]*(getval(k,30-depth[rt])+1)%MOD;
		} 
		return;
	}
	calc1(ls[rt]);
	calc1(rs[rt]);
	dp1[rt]=dp1[ls[rt]]+dp1[rs[rt]];
	dp1[rt]%=MOD;
	if(get(k,depth[rt]+1)){
		(dp1[rt]+=1ll*cover[ls[rt]]*(cover[ls[match[rt]]])%MOD)%=MOD;
		(dp1[rt]+=1ll*cover[rs[rt]]*(cover[rs[match[rt]]])%MOD)%=MOD;
	}
}
void calc2(int rt){
	if(!cover[rt]) return;
	if(ls[rt]==0){
		if(cover[rt]&&cover[match[rt]]){
			dp2[rt]=g2[30-depth[rt]];
		}
		return;
	}
	calc2(ls[rt]);
	calc2(rs[rt]);
	dp2[rt]=dp2[ls[rt]]+dp2[rs[rt]];
	dp2[rt]%=MOD;
	if(get(k,depth[rt]+1)){
		(dp2[rt]+=(1ll*dp1[ls[rt]]*cover[rs[rt]]%MOD+1ll*dp1[rs[rt]]*cover[ls[rt]]%MOD)%MOD)%=MOD;
		(dp2[rt]+=1ll*cover[ls[rt]]*(cover[ls[rt]]-1)/2%MOD*(cover[ls[match[rt]]])%MOD)%=MOD;
		(dp2[rt]+=1ll*cover[rs[rt]]*(cover[rs[rt]]-1)/2%MOD*(cover[rs[match[rt]]])%MOD)%=MOD;
	}
}
void calc3(int rt){
	if(!cover[rt]) return;
	if(ls[rt]==0){
		if(cover[rt])
			dp3[rt]=g3[30-depth[rt]];
		return;
	}
	calc3(ls[rt]);
	calc3(rs[rt]);
	if(get(k,depth[rt]+1)){
		(dp3[rt]+=dp2[ls[rt]])%=MOD;
		(dp3[rt]+=dp2[rs[rt]])%=MOD;
		dp3[rt]+=1ll*(cover[ls[rt]])*(cover[ls[rt]]-1)%MOD*(cover[ls[rt]]-2)%MOD*SIX%MOD;
		dp3[rt]%=MOD;
		dp3[rt]+=1ll*(cover[rs[rt]])*(cover[rs[rt]]-1)%MOD*(cover[rs[rt]]-2)%MOD*SIX%MOD;
		dp3[rt]%=MOD;
	}
	else{
		dp3[rt]=dp3[ls[rt]]+dp3[rs[rt]];
		dp3[rt]%=MOD;
	}
}
int main(){
	scanf("%d%d",&n,&k);
	cover.PB(0);
	ls.PB(0);
	rs.PB(0);
	depth.PB(0);
	match.PB(0);
	rb(i,1,n){
		int l,r;
		scanf("%d%d",&l,&r);
		insert(0,l,r);
	}
	int n=cover.size()-1;
	g1.resize(n+1);
	g2.resize(n+1);
	g3.resize(n+1);
	dp1.resize(n+1);
	calc1(0);
	rb(i,0,30){
		g2[i]=1<<i;
		g2[i]=1ll*(getval(k,i)+1)*(getval(k,i))/2%MOD*g2[i]%MOD;
	}
	dp2.resize(n+1);
	calc2(0);
	dp3.resize(n+1);
	rb(i,2,30){
		if((k>>(i-1))&1){
			g3[i]+=2ll*g2[i-1]%MOD;
			g3[i]%=MOD;
			int tmp=1<<(i-1);
			tmp=2ll*tmp*(tmp-1)%MOD*(tmp-2)%MOD*SIX%MOD;
			(g3[i]+=tmp)%=MOD;
		}
		else{
			g3[i]=g3[i-1]<<1;
			g3[i]%=MOD;
		}
	}
	calc3(0);
	printf("%d\n",dp3[0]);
	return 0;
}
/*
5 147
1 35
48 103
125 127
154 190
195 235

2 147
154 190
1 35


2 147
1 35
154 190
16603
*/
```

---

## 作者：Anonymely (赞：0)

超级大粪。

首先这个题和 [Keep XOR Low](https://www.luogu.com.cn/problem/CF1616H) 很像，非常像。

给定了强制选 3 个的限制，所以套用一样的方法，设 $f_u$ 表示在节点 $u$ 里面选三个的方案数，转移考虑限制数 $K$ 这一位是 $0$ 还是 $1$，若为 $1$ 则考虑要分叉，再记录 $g(u,v)$ 表示在节点 $u$ 和节点 $v$ 子树内选 $1,2/2,1$ 的方案数，同理还要 $h(u,v)$ 表示在节点 $u$ 和节点 $v$ 子树内选 $1,1$ 的方案数。

$f(x,y)=f(ls(x),ls(y))+f(rs(x),rs(y)),[k=0]$

$f(x,y)=g(ls(x),rs(y))+g(rs(x),ls(y))+C_3(s(x))+C_3(s(y)),[k=1]$

$g(x,y)=g(ls(x),ls(y))+g(rs(x),rs(y)),[k=0]$

$g(x,y)=g(ls(x),rs(y))+g(rs(x),ls(y))\\+h(ls(x),rs(y))\times (s(rs(x))+s(ls(y)))+h(rs(x),ls(y))\times(s(ls(x))+s(rs(y)))\\+C_2(s(ls(x)))\times s(ls(y))+C_2(s(rs(x)))\times s(rs(y))\\+C_2(s(ls(y)))\times s(ls(x))+C_2(s(rs(y)))\times s(rs(x)),[k=1]$

$h(x,y)=h(ls(x),ls(y))+h(rs(x),rs(y)),[k=0]$

$h(x,y)=h(ls(x),rs(y))+h(rs(x),ls(y))+s(ls(x))\times s(ls(y))+s(rs(x))*s(rs(y))$

$s$ 为子树大小。

不难发现对于 $f,g,h$ 都满足每个点恰好走过一遍，所以复杂度是可以接受的。

现在的问题是如何进行区间插入，考虑 Trie 树本身就是一颗线段树，将区间分成 $\log V$ 个长度为 $2^t$ 区间依次插入即可，这个可能会对复杂度分析有一点影响，但是增加量也是在 $\log V$ 内，可以接受。

---

