# Game in Tree (Hard Version)

## 题目描述

这是问题的困难版本。在这一版本中，不要求 $u = v$。只有当两个版本的问题都成功解决后，你才能进行 hack。

Alice 和 Bob 在一棵树上玩一个有趣的游戏。这棵树有 $n$ 个顶点，编号从 $1$ 到 $n$。回顾一下，一棵有 $n$ 个顶点的树是一个有 $n - 1$ 条边的无向连通图。

游戏规则是 Alice 和 Bob 轮流移动，Alice 先行动，每位玩家在自己的回合中，必须从当前所在的顶点移动到一个尚未被访问过的相邻顶点。如果某个玩家无法移动，则他输掉比赛。

给定两个顶点 $u$ 和 $v$。从顶点 $u$ 到顶点 $v$ 的简单路径用数组表示为 $p_1, p_2, p_3, \ldots, p_m$，其中 $p_1 = u$，$p_m = v$，并且每对相邻的顶点 $p_i$ 和 $p_{i+1}$之间都有一条边（$1 \le i < m$）。

你的任务是，判断在 Alice 从顶点 $1$ 开始，而 Bob 从路径中的顶点 $p_j$（$1 \le j \le m$）开始的情况下，谁将获胜。

## 说明/提示

在第一个例子中，路径是（$2, 3$）。如果 Bob 开始时位于顶点 $2$，Alice 在第一回合就无法移动，只能输掉比赛。而如果 Bob 从顶点 $3$ 开始，Alice 会移动到顶点 $2$，此时 Bob 就没有顶点可动并会输掉比赛。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3
1 2
2 3
2 3
6
1 2
1 3
2 4
2 5
1 6
4 5
4
1 2
1 3
2 4
2 4```

### 输出

```
Bob
Alice
Alice
Bob
Alice
Bob
Alice```

# 题解

## 作者：Lynkcat (赞：8)

大家好，我限时返场了。为了进一步锻炼语言表达能力，同时也跟之前我写的题解做个对比，我来尝试讲述一下更强的 F2plus 版本（确信）的做法。就是把问题改为**求每个点的答案**。

Tips：时间复杂度跟 F2 能做到的最优复杂度有出入，因为做法的发展路径也不是完全一样（知道一些事情之后 F2 的 $O(n\log n)$ 很平凡，并且 $O(n)$ 似乎也是一些技巧上的东西，所以这里不提了，可以看别的题解）

首先来关注一下 F1 怎么做：

我们假设初始 Alice 在 $1$，Bob 在 $m$。

考虑将 $1$ 到 $m$ 路径上的点扣下来组成一个点序列 $p_1=1,p_2,...,p_k=m$。然后试着模拟一下两人的策略。

一开始，Alice 在 $1$ 号点，我们把她接下来走的路分为两个策略：走到 $p_2$ 与走出链。因为走出链就回不来了，所以这样分析是十分合理的。因为走出链就回不来了，所以接下来就变成两个数比大小了，也就是 Bob 接下来能走的最多步数跟 Alice 往下能走的最多步数比大小，两者互不影响了。

也就是：如果 Alice 发现走出链必胜，那么她一定会走出链。否则会走到 $p_2$。前者胜负已定，对于后者来说，可以发现 Bob 接下来要面对相同的局面。那就继续这样判断即可。

整个过程已经搞明白了，解决一些实现上的问题，比如“对方接下来能走的最多步数”该怎么算。

设 $a_i$ 为 $p_i$ 走出链之后能走多少步，具体地走不出链就是 $0$ 否则就是“链外每棵子树深度的最大值”。

设当前 Alice 在 $p_l$，Bob 在 $p_r$。对于 Alice，我们可以将情况描述成判断如下条件是否成立：

$$a_l>\max_{i=l+1}^r{a_i+(r-i)}$$ 

对于 Bob，我们可以将情况描述成判断如下条件是否成立：

$$a_r\geq\max_{i=l}^{r-1}{a_i+(i-l)}$$ 

**实现时小心第二个式子的等于号。**

是一个简单的 rmq 问题，当然 $l,r$ 的值显然也有一些性质，可以简化实现。

F1 直接这样做就可以了。对于 F2plus 版本的问题，我们要求出每个点的答案，怎么办呢？

明确一下问题，我们现在要找的是 $1$ 到 $m$ 上的这条链上第一次满足不等式成立的点的位置。**注意了**，现在的 $a_i$ 是会随着求答案的那个点而变化的，因此需要动态维护，但这里不要忽略了一个在待会儿很重要的性质：考察树上遍历的过程，发现 $a_i$ 只会在 $i-1$ 与 $i$ 处改变。

接下来有一些路显然是可以探索的，第一条路是 $l,r$ 的值存在性质。但是思考了一会儿你会发现似乎没有什么办法（思考了会儿就能解决 F2。。）

第二条路需要注意到一个经典的性质：$\sum a_i<n$。那么首先将 $a_i$ 按照根号的阈值分为大的部分跟小的部分，需要在遍历的过程中来求一下对于当前的这个点哪些 $a$ 是大的。

无论是写成不等式还是直接考察原意义都能让我们茅塞顿开：

- 当 $a_i$ 大于阈值时，最多 $O(\sqrt n)$ 个情况需要判断，每种情况相当于求一次一条直链上的最大值。

- 当 $a_i$ 小于阈值时，我们发现另一边有一个 $r-i$ 或 $l-i$ 那么，若当 $r-l-1$ 大于阈值时不等式必然不成立。那么也就是说还是只有 $O(\sqrt n)$ 种情况需要判断。也是，相当于求一次一条直链上的最大值。

那么我们只需要解决求一条直链上的最大值做到查询 $O(1)$ 即可。我们注意到类似 ST 表的，在遍历树的过程中求出 $fa_{k,i},mn_{k,i},mn1_{k,i}$ 分别表示 $k$ 点的 $2^i$ 级祖先和 $2^i$ 步后的 $a_j-j$ 与 $a_j+j$ 的最大值即可。由于 $a$ 只会在最后两位变化，所以在遍历到 $k$ 的时候再重建 $k$ 的父亲为端点的信息即可。查询跟 ST 表是一样的。

那么问题即可在 $O(n \log n+n \sqrt n)$ 的时间复杂度内解决。

可以看出这还是一道比较简单的题！其实写这个根号做法 F2 挺快的，所以数据可能不是很强。有错误可以在评论区告诉我，谢谢！

---

## 作者：XZhuRen (赞：3)

一道难度没有 *3500 的 *3500。

首先考虑暴力，即 [CF2013F1](https://codeforces.com/problemset/problem/2013/F1)：

我们设 $g_i$ 为不经过 $1-u$ 路径上点向子树外走的最大距离，一遍树上 DP 求出所有 $g_i$。

把 $1-u$ 路径拍成序列 $B$，长度为 $m$，设 $f_i=g_{b_i}$，A 当前所在位置为 $l$，B 当前所在位置为 $r$。

正常情况下，A 或 B 在某个位置跳出路径即可立即获胜，获胜的充要条件即:

$$A:l-1+f_l>\max_{x\in (l,r]}\{f_x+m-r\}$$

$$B:m-r+f_r\ge \max_{x\in [l,r)}\{f_x+x-1\}$$

若始终未跳出，则根据 $m$ 的奇偶性判断答案，奇数为 Alice，偶数为 Bob。

这样模拟下去我们就写完了 Easy。

现在回来看这道题：

首先我们分开求 $1-u$ 路径和 $1-v$ 路径答案即可。

考虑怎么求出一条到根路径答案：

我们重新观察，尝试简化这个过程：

我们跳来跳去，容易对于 A 和 B 分别求出它们最早可以跳出的位置 $p_a,p_b$，这个时候 A 胜利的充要条件即：

$$p_a\le m-p_b+1$$

考虑直接枚举每个位置 $pos$，求出以它作为跳出点，能造成什么贡献：

求 $l=pos$ 对 $A$ 的贡献，记 $r=x$，则 $m=x+pos-2$，套用刚才的式子，发现**具有单调性**。

求 $r=pos$ 对 $B$ 的个贡献，记 $l=x$，则 $m=x+pos-2$，同理具有单调性。

这样二分后使用 sgt_beats 等数据结构维护即可，没有被覆盖的部分记为 $\inf$。

最后的问题：我们对于每个 $m$ 求答案时，$f_m$ 存在变化。

这个问题是简易的，对于刚才 $x=1$ 的部分暴力枚举一下即可，这个对每个 $m$ 只要进行一次判断。

然后我们就轻松解决了一道 *3500，小编也觉得很神奇呢！

---

发现这个和 Wuyanru 大神的题解思路是一样的。

Code 还是贴一下：

```cpp

#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int M=8e5+5;
const int inf=1e9+7;
int n;
int LOG2[N];
struct edge{
	int u,v,nxt;
}g[N*2];
int head[N],tote=0;
void ae(int u,int v){g[++tote]=(edge){u,v,head[u]};head[u]=tote;}
int fa[N],d[N],f1[N];
int ST,ED;bool onr[N];
bool dfs(int u,int Fa,int D){
	d[u]=D,fa[u]=Fa;
	for(int e=head[u],v;e;e=g[e].nxt){
		v=g[e].v;if(v==Fa)continue;
		onr[u]|=dfs(v,u,D+1);
	}
	return onr[u];
}
void dfs2(int u){
	f1[u]=1;
	for(int e=head[u],v;e;e=g[e].nxt){
		v=g[e].v;if(v==fa[u])continue;
		dfs2(v);
		if(!onr[v])f1[u]=max(f1[u],f1[v]+1);
	}
}
void init(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)head[i]=0;
	tote=0;
	for(int e=1,u,v;e<n;e++){
		scanf("%d%d",&u,&v);
		ae(u,v),ae(v,u);
	}
	scanf("%d%d",&ST,&ED);
}
bool Ans[N];
int f[N],b[N];
int m=0;
const int MXK=19;
struct St_List{
	int mx[MXK][N];
	void build(bool op){
		for(int i=1;i<=m;i++)mx[0][i]=op?(f[i]-i):(f[i]+i-1);
		for(int k=1;(1<<k)<=m;k++)
			for(int i=1;i+(1<<k)-1<=m;i++)
			mx[k][i]=max(mx[k-1][i],mx[k-1][i+(1<<(k-1))]);
	}
	void modify(int pos,int x){
		mx[0][pos]=x;
		for(int k=1;(1<<k)<=pos;k++){
			int i=pos-(1<<k)+1;
			mx[k][i]=max(mx[k-1][i],mx[k-1][i+(1<<(k-1))]);
		}
	}
	int qry(int l,int r){
		if(l>r||l<1||r>m){
			cout<<"FuckYou!";
			exit(0);
		}
		int k=log2(r-l+1);
		return max(mx[k][l],mx[k][r-(1<<k)+1]);
	}
}sta,stb;
int pa[N],pb[N];
struct sgt{
	int L[M],R[M];
	int tag[M];
#define ls (o<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
	void build(int o,int l,int r){
		L[o]=l,R[o]=r,tag[o]=inf;
		if(l==r)return;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void pushdown(int o){
		tag[ls]=min(tag[ls],tag[o]);
		tag[rs]=min(tag[rs],tag[o]);
		tag[o]=inf;
	}
	void cover(int o,int lt,int rt,int x){
		int l=L[o],r=R[o];
		if(l>=lt&&r<=rt){tag[o]=min(tag[o],x);return;}
		pushdown(o);
		if(lt<=mid)cover(ls,lt,rt,x);
		if(rt>mid)cover(rs,lt,rt,x);
	}
	void get(int o,int *P){
		int l=L[o],r=R[o];
		if(l==r){P[l]=tag[o];return;}
		pushdown(o),get(ls,P),get(rs,P);
	}
#undef ls
#undef rs
#undef mid
}sa,sb;
void solve(int ed){
	for(int i=1;i<=n;i++)onr[i]=0;
	onr[ed]=1;
	dfs(1,0,1),dfs2(1);
	m=d[ed];
	while(ed){b[d[ed]]=ed;ed=fa[ed];}
	for(int i=1;i<=m;i++)f[i]=f1[b[i]];
	sta.build(0),stb.build(1);
	sa.build(1,1,m),sb.build(1,1,m);//ST 表及线段树的预处理

	for(int i=2;i<=m;i++)Ans[b[i]]=!(i&1);
	for(int pos=2;pos<=m;pos++){//计算对 A 的贡献，二分，注意这里<=2 的部分都需要暴做，否则会触碰到右边界
		int res=0;
		{
			int lt=(pos<<1),rt=m,mid=0;
			while(lt<=rt){
				mid=(lt+rt)>>1;
				int l=pos,tot=mid,r=tot-l+1;
				if(stb.qry(l+1,r)+tot<f[pos]+l-1){
					res=mid,lt=mid+1;
				}else rt=mid-1;
			}
		}
		if(res>=(pos<<1))
			sa.cover(1,(pos<<1),res,pos);
	}
	for(int pos=3;pos<=m;pos++){//计算对 B 的贡献，二分
		int res=inf;
		{
			int lt=pos+1,rt=min(m,(pos<<1)-3),mid=0;
			while(lt<=rt){
				mid=(lt+rt)>>1;
				int tot=mid,r=pos,l=tot-r+2;
				if(sta.qry(l,r-1)<=f[r]+tot-r)
					res=mid,rt=mid-1;
				else lt=mid+1;
			}
		}
		if(res<=min(m,(pos<<1)-3))
			sb.cover(1,res,min(m,(pos<<1)-3),m-pos+1);
	}
	sa.get(1,pa),sb.get(1,pb);
	for(int i=m,j=0;i>1;i--,j++)pb[i]-=j;
	for(int i=m;i>1;){//单独处理第一次
		int l=1,r=i;
		bool turn=0;
		while(l<r&&l<=2){//暴力
			if(!turn){
				if(f[l]+l-1>stb.qry(l+1,r)+i){
					pa[i]=min(pa[i],l);
				}
				l++;
			}else{
				if(f[r]+i-r>=sta.qry(l,r-1))
					pb[i]=min(pb[i],i-r+1);
				r--;
			}
			turn^=1;
		}
		--i;
		f[i]=max(f[i],f[i+1]+1);f[i+1]=-inf;
		sta.modify(i+1,-inf),stb.modify(i+1,-inf);
		sta.modify(i,f[i]+i-1),stb.modify(i,f[i]-i);
	}
	for(int i=m,u;i>1;i--){
		u=b[i];if(pa[i]>m&&pb[i]>m)continue;
		Ans[u]=pb[i]<pa[i];
	}
}
bool res[N];
void work(){
	solve(ST);
	solve(ED);
	dfs(1,0,1);
	int u=ST,v=ED,lca=0;
	while(u!=v){if(d[u]<d[v]){swap(u,v);}u=fa[u];}
	lca=u;u=ST,v=ED;
	while(u!=lca){Ans[u]?printf("Bob\n"):printf("Alice\n");u=fa[u];}
	Ans[lca]?printf("Bob\n"):printf("Alice\n");
	int tr=0;
	while(v!=lca){res[++tr]=Ans[v],v=fa[v];}
	while(tr)res[tr--]?printf("Bob\n"):printf("Alice\n");
}
int main(){
	LOG2[1]=0;
	for(int i=2;i<=200000;i++){
		LOG2[i]=LOG2[i-1];
		if((1<<(LOG2[i]+1))==i)LOG2[i]++;
	}
	int T=0;
	scanf("%d",&T);
	while(T--){init();work();}
	return 0;
}

```

---

## 作者：Wuyanru (赞：3)

不知道是算好牛还是好不牛的题。

[题目链接](https://codeforces.com/contest/2013/problem/F2)。

## 题意

现在有一棵 $n$ 个点的树，初始时 Alice 在点 $1$，Bob 在点 $x$。

两个人轮流进行操作，Alice 先手。每一个人操作的时候需要走向当前点的一个邻居，并且这个邻居之前没有被两个人访问过，不能走的人输。

给定两个点 $u,v$，对 $u\to v$ 路径链上的每一个点 $x$ 求出答案，保证 $1$ 不在 $u,v$ 的路径上。

$n\le 2\times 10^5$。

## 题解

先来考虑如何对于一个固定点 $x$ 求出答案。

首先将 $1$ 到 $x$ 路径上面所有的点拿出来，假设他们分别是 $p_1,p_2,\dots,p_m$，满足 $p_1=1$ 且 $p_m=x$。我们称这些点为关键点。

然后考虑这个游戏的过程，首先肯定是两个人都在这些关键点上，朝对面的方向走。

直到有一个人某步走在了一个非关键点上，之后两个人会往尽可能远的地方走，第一个走不了的人输。

特别的，如果两个人直到最后都没有走到非关键点上，则可以通过 $m$ 奇偶性判断谁赢。

设 $d_i$ 表示从点 $i$ 出发，不经过其他的关键点，能走出的最长简单路径有多长。

假设当前 Alice 在点 $p_l$ 上，Bob 在点 $p_r$ 上，现在该 Alice 走了，考虑什么情况下 Alice 会走到非关键点上。

此时若 Alice 下一步要往非关键点上走，那么 Alice 还最多能走 $A=d_{p_l}$ 步。

后面 Bob 会挑选尽可能远的地方走，那么 Bob 最多还能走 $B=\max_{i=l+1}^r(d_{p_i}+r-i)$ 步。

由于下一步是 Alice 走，所以当 $A>B$ 时，Alice 必胜，$A\le B$ 时，Alice 必败。

换句话说，若 $A>B$ 时，Alice 会走到非关键点上，此时 Alice 必胜，否则 Alice 会继续往前走到 $p_{l+1}$。

Bob 的策略同理。

考虑模拟这个过程，中间求区间最值的操作可以使用两个 st 表完成。

那么就可以在 $O(n\log n)$ 复杂度求出单个点的答案

其实求区间最值的过程可以看成每一次删一个数字，然后求最大值，可以直接拿一个桶存起来，然后每一次从上一次查询的答案往下扫，这样就可以做到 $O(n)$ 了，不过这不重要。

F1 的[代码](https://codeforces.com/contest/2013/submission/283495899)，复杂度是 $O(n)$ 的（这份代码我写的时候 $p$ 序列是反过来写的）。

---

然后来考虑 F2 怎么做。

考虑求出 $1\to u$ 和 $1\to v$ 这两条路径上所有答案，这两条链上的点包含了 $u\to v$ 路径上所有点。

假设当前想要求 $1\to u$ 路径上所有点答案（$v$ 同理），还是一样先把路径上点拿出来，从 $1$ 到 $u$ 分别是 $p_1,p_2,\dots,p_m$。

考虑这么一个事情，根据上面的讨论，两个人一定是能往非关键点上走就一定往非关键点上走，也就是说，如果我们能求出，两个人最早能在哪个位置往非关键点上走，问题就解决了。

设 $pa_i$ 表示当 Bob 起点为 $p_i$ 时，Alice 最早在点 $p_{pa_i}$ 上往非关键点走。$pb_i$ 同理。

那么问题在于如何求出 $pa_i$ 和 $pb_i$。以 $pa_i$ 举例。

考虑枚举一个点 $p_j$，看一下 Bob 的起点为哪些点时，Alice 从 $p_j$ 走出去会必胜。

假设当前有两个点 $p_x,p_y$，满足 $2j-1<x<y$（$2j-1<x$ 是因为需要当 Alice 走到点 $p_j$ 时 Bob 还没有撞上去）。

如果 Bob 的起点是 $p_y$，并且此时 Alice 从 $p_j$ 走出去必胜，那么可以发现，若 Bob 的起点是 $p_x$，则 Alice 从 $p_j$ 走出去一定也必胜。

为什么呢？根据上面的讨论，起点为 $p_y$ 时，Bob 还能走 $B=\max_{i=j+1}^{y-j+1}(d_{p_i}+y-i)$ 次。

而起点为 $B'$ 时，Bob 还能走 $B'=\max_{i=j+1}^{x-j+1}(d_{p_i}+x-i)$。

而因为 $y>x$，所以一定有 $B'>B$，也就是说，点 $p_j$ 能贡献到的 $pa_i$ 是一个区间 $[2j,?]$（为什么左端点是 $2j$ 呢，因为小于 $2j$ 两个人就撞了）。

而这个 $?$ 我们是可以直接二分出来的。

所以可以直接枚举每一个 $j$，二分出其贡献的区间，然后用线段树（我代码中用的一个类似 st 表的东西）做区间覆盖（或者取最大值，都可以），就能直接算出 $pa_i$ 了。

每一个点 $p_j$ 对 $pb_i$ 的贡献也是一段区间，可以自己推，不细说了。

然后是有一些细节：

1. 注意到如果 Alice 在第一步就往出走，上面的 $B$ 的式子是错的，还有 Bob 往 $p_m$ 那个方向走的贡献，所以需要特判 $pa_i=1$ 的情况。
2. 和第一条一样，Bob 也可能第一步就直接往右边走，所以 $pb_i=i$ 的情况也需要特判。
3. $pa_i$ 不存在就设为 $+\infty$，$pb_i$ 不存在设为 $0$，两个人都走不出去的时候看链长度的奇偶性。

## 代码

代码在 [这里](https://codeforces.com/contest/2013/submission/283534030)，太长了贴出来好丑。

~~我也是没想到一个博弈题怎么代码这么长。~~

---

## 作者：SukiYuri (赞：2)

## 闲话

~~纪念我模拟赛使用 $\mathcal{O}(nd)$ 的复杂度获得 96 pts 的成绩。~~

## 分析

考虑固定 Alice 和 Bob 的出发位置我们如何确定输赢。

首先我们发现操作序列一定是这样的：

Alice 的出发位置（记为 $x$）Bob 的出发位置（记为 $y$）形成了一条链，Alice 和 Bob 均会在这条链上走若干步然后跳出这条链，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/kyd96ns7.png)

我们钦定点 $x$ 为根且深度为 $1$，那么如果 Alice 在点 $u$
处跳出这条链，那么将可以走 $(dep_u+len_u-1)$ 步，$len_u$ 定义为 $u$ 在这条链外的最长路径，即图中三角形部分。而 Bob 在 $v$ 处跳出这条链，那么将可以走 $(dep_y-dep_v+len_v)$ 步。

因此，若 Alice 在 $x$，Bob 在 $y$ 且 Alice 获胜，当且仅当存在点 $u$ 满足：

$$dep_u+len_u-1 > \max_{dep_v>dep_u} \{len_v+dep_y-dep_v\}\land dep_u<\left\lceil\frac{dep_y}{2}\right\rceil$$

发现这个东西只需要维护 $u$ 到根的栈和后缀最大值，每扫到一个点暴力判断就行，时间复杂度 $\mathcal{O}(nd)$，$d$ 是树的高度。

考虑优化这个过程，我们将上式放缩一下，得到：

$$dep_u+len_u-1>dep_y-(dep_u+1)$$

因此对于 $u$，$2\cdot dep_u+len_u>dep_y$ 是 Alice 获胜的必要条件。我们对于 $len_u$ 按 $B$ 分类，

- 对于 $len_u<B$：我们有 $\left\lfloor\frac{dep_y-B}{2}\right\rfloor<dep_u<\left\lceil\frac{dep_y}{2}\right\rceil$，共有 $\mathcal O(B)$ 个符合条件的点。
- 对于 $len_u>B$：我们有 $\sum len_u=\mathcal O(n)$，共有 $\mathcal O(\frac{n}{B})$ 个符合条件的点。

因此，每次到一个点需要判断的决策点数量降低到了 $\mathcal O(B+\frac{n}{B})$ 量级。因为每次还有一个最值的查询，因此我们使用 ST 表 $\mathcal O(\log n)$ `pop_back` `push_back`，$\mathcal O(1)$ 查询即可。总时间复杂度 $\mathcal O(n\sqrt n)$。

使用放缩减少状态数量的技巧还是第一次见。果然做题太少了。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2013F2)

**题目大意**

> 给定 $n$ 个点的树，先手从 $1$ 出发，后手从 $x$ 出发，两个人轮流在树上游走，不能重复经过点，对于 $u\to v$ 上的每个 $x$，求谁有必胜策略。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

假设 $1\to x$ 路径是 $p_1\sim p_m$，两个人的策略就是在 $p$ 上运动，直到某个时刻必胜的时候离开路径。

设 $d_i$ 表示从 $p_i$ 处离开路径，最多能走多少步。

假设先手在 $p_l$ 处离开路径必胜，这就要求：$\max_{i=l+1}^{m-l+1}m-i+d_i<d_l+l-1$。

假设后手在 $p_r$ 处离开路径必胜，这就要求：$\max_{i=m-r+2}^{r-1}a_i+i-1\le a_r+m-r$。 

暴力枚举每个 $l,r$，考虑第一个合法的 $l$ 和第一个合法的 $r$，比较 $l-1,n-r$ 即可知道谁必胜，现在要优化这部分的分之道。

定义 $f_l=d_l+l-1,g_r=a_r+m-r$，表示先手 / 后手从 $p_l,p_r$ 处离开路径后最多能走多远。

我们要找 $f_l>\max g[l+1,m-l+1]$ 的第一个 $l$，我们发现随着 $l$ 的增加，$\max g$ 的范围越来越小，因此 $i<j,f_i<f_j$ 时，$i$ 必胜能推出 $j$ 必胜 。

注意到 $l$ 变化的时候 $\max g$ 实际上不太容易变化，可以找到 $g[mid+1,m]$ 中的最大值 $g_r$，只有 $l-1>n-r$ 的时候才会产生变化。

找到 $f[1,mid]$ 的最大值 $f_l$，不妨设 $l-1\le n-r$，比较 $f_l,g_r$ 的关系：

- 如果 $f_l\le g_r$，那么 $i\in [1,l]$ 的点都不可能合法。
- 否则 $i\in [n-l+1,n]$ 的点都不可能合法，我们只要判断 $i\in [1,l]$ 中有没有合法点，很显然最容易合法的就是 $f_l$，只需要判断 $f_l$ 是否合法即可。

因此我们只需要判定 $f_l$ 是否合法，然后就把问题缩小成了 $[l,n-l+1]$ 的子问题。

不断这样的递归，我们会需要判定的 $l$ 一定是 $f[1,mid]$ 的后缀最大值，需要判定的 $r$ 一定是 $g[mid+1,r]$ 的前缀最大值。

考虑 $i<j,f_i\ge f_j$ 的两个点，此时一定有 $d_i>d_j$，因此 $f[1,mid]$ 的后缀最大值的 $d$ 单调递增。

由于 $\sum d_i=\mathcal O(n)$，因此访问到的 $l,r$ 总数是 $\mathcal O(\sqrt n)$ 级别的。

在 dfs 的时候动态维护栈中节点的 $f_i,g_i$，需要一个数据结构支持修改末尾元素，快速查询区间最大值。

可以用 st 表，$s_{i,k}$ 维护 $[i-2^k+1,i]$ 范围内的最小值，修改末尾元素 $\mathcal O(\log n)$，查询最大值 $\mathcal O(1)$。

此时我们能得到后手从每个 $x$ 出发是否必胜，容易回答询问。

时间复杂度 $\mathcal O(n\sqrt n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
inline int bit(int x) { return 1<<x; }
struct ST {
	int v[MAXN],f[MAXN][18];
	int cmp(int x,int y) { return v[x]>v[y]?x:y; }
	void upd(int x,int z) {
		v[x]=z,f[x][0]=x;
		for(int k=1;bit(k)<=x;++k) f[x][k]=cmp(f[x][k-1],f[x-bit(k-1)][k-1]);
	}
	int qry(int l,int r) {
		int k=__lg(r-l+1);
		return cmp(f[l+bit(k)-1][k],f[r][k]);
	}
}	A,B;
void upd(int d,int w) { A.upd(d,w+d-1),B.upd(d,w-d); }
bool sol(int n) {
	int mid=(n+1)>>1;
	for(int l=A.qry(1,mid),r=B.qry(mid+1,n);;) {
		if(l-1<=n-r) {
			if(A.v[l]>B.v[B.qry(l+1,n-l+1)]+n) return 1;
			if(l>=mid) return 0;
			l=A.qry(l+1,mid);
		} else {
			if(B.v[r]+n>=A.v[A.qry(n-r+2,r-1)]) return 0;
			if(r<=mid+1) return 1;
			r=B.qry(mid+1,r-1);
		}
	}
}
vector <int> G[MAXN];
int n,d[MAXN],f[MAXN],fa[MAXN];
bool ans[MAXN];
void dfs1(int u,int fz) {
	d[u]=d[fz]+1,f[u]=0,fa[u]=fz;
	for(int v:G[u]) if(v^fz) dfs1(v,u),f[u]=max(f[u],f[v]+1);
}
void dfs2(int u) {
	int mx=0,sx=0;
	for(int v:G[u]) if(v^fa[u]) {
		if(f[v]+1>mx) sx=mx,mx=f[v]+1;
		else sx=max(sx,f[v]+1);
	}
	if(u>1) upd(d[u],mx),ans[u]=sol(d[u]);
	for(int v:G[u]) if(v^fa[u]) upd(d[u],f[v]+1==mx?sx:mx),dfs2(v);
}
void prt(int u) { cout<<(ans[u]?"Alice":"Bob")<<"\n"; }
void out(int u,int v) {
	if(u==v) return prt(u);
	if(d[u]>d[v]) prt(u),out(fa[u],v);
	else out(u,fa[v]),prt(v);
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;++i) G[i].clear();
	for(int i=1,u,v;i<n;++i) cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
	dfs1(1,0),dfs2(1);
	int s,t;
	cin>>s>>t,out(s,t);
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

