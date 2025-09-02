# Freezing with Style

## 题目描述

This winter is so... well, you've got the idea :-) The Nvodsk road system can be represented as $ n $ junctions connected with $ n-1 $ bidirectional roads so that there is a path between any two junctions. The organizers of some event want to choose a place to accommodate the participants (junction $ v $ ), and the place to set up the contests (junction $ u $ ). Besides, at the one hand, they want the participants to walk about the city and see the neighbourhood (that's why the distance between $ v $ and $ u $ should be no less than $ l $ ). On the other hand, they don't want the participants to freeze (so the distance between $ v $ and $ u $ should be no more than $ r $ ). Besides, for every street we know its beauty — some integer from $ 0 $ to $ 10^{9} $ . Your task is to choose the path that fits in the length limits and has the largest average beauty. We shall define the average beauty as a median of sequence of the beauties of all roads along the path.

We can put it more formally like that: let there be a path with the length $ k $ . Let $ a_{i} $ be a non-decreasing sequence that contains exactly $ k $ elements. Each number occurs there exactly the number of times a road with such beauty occurs along on path. We will represent the path median as number $ a_{⌊k/2⌋} $ , assuming that indexation starting from zero is used. $ ⌊x⌋ $ — is number $ х $ , rounded down to the nearest integer.

For example, if $ a={0,5,12} $ , then the median equals to $ 5 $ , and if $ a={0,5,7,12} $ , then the median is number $ 7 $ .

It is guaranteed that there will be at least one path with the suitable quantity of roads.

## 说明/提示

In the first sample all roads have the same beauty. That means that all paths of the positive length have the same median. Thus, any path with length from $ 3 $ to $ 4 $ , inclusive will be valid for us.

In the second sample the city looks like that: 1 - 2 - 3 - 4 - 5 - 6. Two last roads are more valuable and we should choose any path that contains both of them and has the suitable length. It is either the path between $ 2 $ and $ 6 $ or the path between $ 3 $ and $ 6 $ .

## 样例 #1

### 输入

```
6 3 4
1 2 1
2 3 1
3 4 1
4 5 1
5 6 1
```

### 输出

```
4 1
```

## 样例 #2

### 输入

```
6 3 4
1 2 1
2 3 1
3 4 1
4 5 2
5 6 2
```

### 输出

```
6 3
```

## 样例 #3

### 输入

```
5 1 4
1 2 1
1 3 4
3 4 7
3 5 2
```

### 输出

```
4 3
```

## 样例 #4

### 输入

```
8 3 6
1 2 9
2 3 7
3 4 7
4 5 8
5 8 2
3 6 3
2 7 4
```

### 输出

```
5 1
```

# 题解

## 作者：shadowice1984 (赞：18)

大力点分治……

人傻常数大，两个log跑不过3个log……

(另外这题是cf老题，意味着你的运行时间要被乘2，所以时限只有3500ms)
_________________

### 前置芝士：点分治

~~不会点分治的话出门左转你站模板区，包教包会~~

## 本题题解

一句话题意:设树上一条路径的权值为路径上边的中位数，求边数在(L,R)这个区间里并且权值最大的路径，随意输出一种方案即可

那么题目已经十分简单易懂了，对于最大化中位数的题目，我们有一个通用套路叫二分答案

具体来讲，我们将最大化中位数问题转化为这样一个问题，判断是否存在一个大于mid的中位数

那么我们怎么判定呢？这又是一个经典的奇技淫巧，我们将所有小于的mid的边的边权看成-1,将所有大于等于mid的边的边权看成1，此时如果有一条路径的边权和大于等于0，那么这条路径的中位数就大于mid

为什么呢？

证明其实很简单，我们发现如果这条路径的权值和大于等于0的话，就说明这条路径中大于等于mid的数比小于mid的数多，所以这个序列的中位数自然就大于等于mid了

所以现在的问题转化成了，如何在树上找一个边数在(L,R)这个区间里并且权值和大于等于0的路径了，当然，还要输出这个路径

这个问题其实是一个经典的点分治问题，我们对整棵树进行点分治，现在考虑过中心G的所有路径，根据点分治的一般套路，我们把G到其他联通块里的点的路径全部dfs/bfs出来

现在我们需要做的事就是枚举每一条路径，找到一条和它所“匹配”的最优路径了
(这里的匹配的意思就是这条从G出发的路径可以和另一条从G出发的路径拼成一条过G的路径)

那么我们当然需要满足一些限制条件，假设这条路径的长度为$x$的话,那么和他匹配的路径的长度应该在$(L-x,R-x)$之间，同时我们应该让这条和他匹配的路径权值尽可能的大

这似乎是一个区间最大值问题，于是我们可以写出来一个愚蠢的$O(nlogn^3)$做法，那就是dfsG的每一个子树，每次d出一条路径我们就在线段树上查一下区间最大值和这个路径匹配一下，然后在dfs完整棵子树之后把这些d出来的路径全部插入到线段树当中就行了

然后我们点分治每一层的复杂度都是O(nlogn)总复杂度就是$O(nlog^3)$了

有点蠢啊，看看我们可不可以砍掉一个log呢?

这是点分治中的另一个套路，名字叫做单调队列按秩合并

### 单调队列按秩合并

刚才的做法之所以多了一个log是因为我们用线段树这个数据结构去查区间最大值了，我们考虑一下有没有一些机智点的方法

答案是有的，我们现在BFSG的每一个子树，此时我们发现找出来的路径会有一个相当优雅的性质，就是长度是严格递增的，假设现在的路径长度是x，那么之后找出来的路径长度不可能比x小，换句话说合法的匹配路径的长度需要满足的区间$[L-x,R-x]$只会一直向左移动

这好像是一个经典的滑动窗口取最大值问题啊……

所以我们似乎只需要使用单调队列维护一下区间中的最大值，然后插入路径的时候将路径插入到一个权值数组里似乎就可以了？

遗憾的是这个做法的时间复杂度是$O(n^2)$会被直接叉掉

为什么呢？单调队列的复杂度不是均摊O(1)的嘛？

的确单调队列在采用滑动窗口法处理区间最小值的时候的确不会使复杂度变为$O(n^2)$

不过这里有一个问题是，在使用单调队列解决滑动窗口问题时，单调队列的初始话也是要耗费时间的，换句话说我们可能需要把$(L,R)$这个区间里的全部元素都塞到单调队列里，而这个单调队列的初始话我们却需要做O(点度)次

于是一个扫把就可以轻松叉掉我们的算法了

那怎么办呢?

我们发现一件事情是每次初始化的时候我们可以不初始化到R而是仅仅初始化到当前权值数组中最长的路径，似乎是一个不错的剪枝

不过这并没有什么卵用，我们只需要一个扫把就可以接着叉掉这个算法

然后就是这个做法为什么叫单调队列按秩合并的原因了，我们将初始的每一个子树按照siz(或者最大深度)为关键字进行排序，然后此时依次bfs每一个子树进行遍历的初始化复杂度就是对的了

原理其实也很简单，由于每次初始化的复杂度是在这个子树之前出现的路径的最大深度，由于所有子树已经排好序，因此最大深度就是这个子树的最大深度，那么初始化的总复杂度就是$O(\sum{mxdep})=O(\sum{siz})=O(n)$的了

至此我们成功将点分治的复杂度降至$O(nlogn)$然后我们就可以以$O(nlog^2n)$的复杂度愉快的A掉本题了

需要注意的一点是请注意储存每次点分治时的中心，不要每次二分的时候现场计算，不然会炸，另一点是这道题数据过水，所有边的真实值域范围是$0-32767$(出题人windows造数据)而不是$0-10^9$所以如果莫名tle可以减少二分上界

上代码~

```C
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#define VEI vector <ed> :: iterator 
#define BG v[u].begin()
#define ED v[u].end()
using namespace std;const int N=1e5+10;int n;int L;int R;
struct data{int u;int f;int dis;int dep;};queue <data> q1,q2;
struct ed//存边的结构体 
{
	int v;int val;int siz;int ori;
	friend bool operator <(ed a,ed b){return a.siz<b.siz;}
};vector <ed> v[N];int ng[N];int tim;int nsiz[N];
int w[N];int nu[N];int siz[N];bool cut[N];int ans1;int ans2;
struct dq//双端队列 
{
	int q[3*N];int hd;int tl;
	inline void clr(){hd=1;tl=0;} 	   inline bool emp(){return hd<=tl;}
	inline void ins(int j){while(hd<=tl&&w[j]>=w[q[tl]])tl--;q[++tl]=j;}
	inline void del(int k){while(hd<=tl&&q[hd]>k)hd++;}
	inline int qmx(){return q[hd];}
}q;
inline void clear(queue <data>& q){queue <data> emp;swap(q,emp);}
inline int dfs1(int u,int f)//处理siz 
{siz[u]=1;for(VEI it=BG;it!=ED;++it)if(it->v!=f&&!cut[it->v])siz[u]+=dfs1(it->v,u);return siz[u];}
inline int find(int u,int f,const int& tot)//处理重心 
{
	for(VEI it=BG;it!=ED;++it)
		if(it->v!=f&&!cut[it->v]&&2*siz[it->v]>=tot)return find(it->v,u,tot);return u;
}
inline int dfs3(int u,int f)//处理最大深度 
{int mx=0;for(VEI it=BG;it!=ED;++it)if(it->v!=f&&!cut[it->v])mx=max(mx,dfs3(it->v,u));return mx+1;}
inline bool bfs(data st,int mxsiz)//bfs 
{
	q.clr();clear(q1);clear(q2);int j=min(R,mxsiz);for(;j>=L;j--)q.ins(j);
	for(q1.push(st);!q1.empty();)
	{
		data nw=q1.front();q2.push(nw);q1.pop();if(nw.dep>R)continue;
		int dl=max(L-nw.dep,0);int dr=min(R-nw.dep,mxsiz);for(;j>=dl;j--)q.ins(j);q.del(dr);
		if(q.emp()){int p=q.qmx();if(nw.dis+w[p]>=0){ans1=nu[p];ans2=nw.u;return true;}}
		for(VEI it=v[nw.u].begin();it!=v[nw.u].end();++it)
			if(it->v!=nw.f&&!cut[it->v])q1.push((data){it->v,nw.u,nw.dis+it->val,nw.dep+1});
	}
	for(;!q2.empty();q2.pop()){data a=q2.front();if(w[a.dep]<a.dis)w[a.dep]=a.dis,nu[a.dep]=a.u;}
	return false;
}
inline bool solve(int u)
{
	++tim;int g;
	if(ng[tim]==-1)//对点分治进行记忆化 
	{
		dfs1(u,0);g=find(u,0,siz[u]);cut[g]=true;ng[tim]=g;nsiz[tim]=siz[u];
		if(siz[u]==1)return false;
		for(int i=1;i<=siz[u];i++)w[i]=-0x3f3f3f3f,nu[i]=0;
		for(VEI it=v[g].begin();it!=v[g].end();++it)if(!cut[it->v])it->siz=dfs3(it->v,g);
		sort(v[g].begin(),v[g].end());w[0]=0;nu[0]=g;
	}
	else 
	{
		g=ng[tim];cut[g]=true;if(nsiz[tim]==1)return false;
		for(int i=1;i<=nsiz[tim];i++)w[i]=-0x3f3f3f3f,nu[i]=0;w[0]=0;nu[0]=g;
	}
	for(VEI it=v[g].begin();it!=v[g].end();++it)//bfs判断 
		if(!cut[it->v])if(bfs((data){it->v,g,it->val,1},it->siz))return true;
	for(VEI it=v[g].begin();it!=v[g].end();++it)if(!cut[it->v])if(solve(it->v))return true;
	return false;
}
inline bool jud(int mid)
{
	tim=0;
	for(int i=1;i<=n;i++)
		for(VEI it=v[i].begin();it!=v[i].end();++it)it->val=(it->ori>=mid)?1:-1;
	for(int i=1;i<=n;i++)cut[i]=false;
	return solve(1);
}
int main()
{
	scanf("%d%d%d",&n,&L,&R);int l=0;int r=0;
	for(int i=1;i<=n;i++)ng[i]=-1;
	for(int i=1,u,V,va;i<n;i++)
	{
		scanf("%d%d%d",&u,&V,&va);r=max(r,va);
		v[u].push_back((ed){V,0,0,va});v[V].push_back((ed){u,0,0,va});
	}//大力二分就行了 
	while(l!=r){int mid=(l+r+1)/2;if(jud(mid))l=mid;else r=mid-1;}
	jud(l);printf("%d %d",ans1,ans2);return 0;
}
```







---

## 作者：critnos (赞：14)

（假了骂我哈哈）

听闻有 1log 做法，大受震撼。

想了一下发现好像可行。

二分答案 $O(n)$ 后求树上链长在 $[l,r]$ 内的链的和的最大值。

考虑长链剖分。每次从下往上扫一条长链，每次把短链求答案之后合并上来。

那么需要一个数据结构，支持：

* 全局加
* 定长区间最大值
* 往前段加一个数
* 将前缀的若干个数变大，“若干个数”数量总和 $O(n)$

显然全局加没用。定长区间最大值就直接按定长分块，每次查询分成块的前缀和后缀。前面在更新的非整块显然平凡。每次将前缀的若干个数变大可以说是对某个块的前缀操作。

发现对每个块的后缀维护也平凡。实际上只剩下：

* 将前缀的若干个数变大
* 求前缀最大值

按 $\log n$ 分块。对 $2\sim k$ 块维护 ST 表。那么对 $2\sim k$ 块的维护直接重构、在 ST 表上 $O(\log n)$ 修改均摊复杂度显然是对的。

考虑第一块，维护所有前缀最大值的位置。每次修改的时候加入一些前缀最大值，删掉一些值，均摊复杂度对的。然后用一个 word 维护所有前缀最大值的位置，查询求出这个前缀最后一个前缀最大值即可。

所以时间复杂度 $O(n\log n)$。

---

## 作者：小粉兔 (赞：12)

### 2019-08-03 补档

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/CF150E.html](https://www.cnblogs.com/PinkRabbit/p/CF150E.html)。

据说这个傻逼题还有一个 $\log$ 的做法，但是我还不会。

### 题意简述：

给定一棵 $n$（$2\le n\le 10^5$）个点的树，边有边权。

定义一条路径的权值为路径经过的边的边权的中位数，若经过偶数条边则取两个中位数中较大的那个。

求长度介于 $l$ 到 $r$（$1\le l\le r<n$）之间的路径的最大权值，并输出这个路径的两端点。

### 题解：

看到中位数的定义，首先想到二分答案，假设二分的值为 $\mathrm{mid}$，将边权 $\ge\mathrm{mid}$ 的边看作 $+1$，将边权 $<\mathrm{mid}$ 的边看作 $-1$，则一条路径的权值大于等于 $\mathrm{mid}$ 当且仅当其经过的边的和大于等于 $0$。

二分了一个值后，考虑使用点分治统计路径。

合并子树时相当于查询一个滑动窗口内的最大值，用单调队列维护即可。  
对当前分治块内统计时要注意需要先处理较小的子树以保证复杂度。

下面是代码，时间复杂度 $\mathcal{O}(n\log^2 n)$。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>

const int Inf = 0x3f3f3f3f;
const int MN = 100005;

int N, L, R, Ans = -1, AnsU, AnsV;
int uv[MN], w[MN];
std::vector<int> G[MN];
int dw[MN], M;

int vis[MN], siz[MN], tsiz, rsiz, Root;
void GetRoot(int u, int fz) {
	siz[u] = 1;
	int nsiz = 0;
	for (auto i : G[u]) {
		int v = uv[i] ^ u;
		if (v == fz || vis[v]) continue;
		GetRoot(v, u), siz[u] += siz[v];
		if (nsiz < siz[v]) nsiz = siz[v];
	}
	if (nsiz < tsiz - siz[u]) nsiz = tsiz - siz[u];
	if (rsiz > nsiz) rsiz = nsiz, Root = u;
}
int stk[MN], tp, _U;
inline bool cmp(int i, int j) {
	return siz[uv[i] ^ _U] < siz[uv[j] ^ _U];
}
int seq[MN], sequ[MN], odep, tmp[MN], tmpu[MN], ndep;
void DFS(int u, int fz, int d, int x, int y) {
	if (tmp[d] < x) tmp[d] = x, tmpu[d] = u;
	if (ndep < d) ndep = d;
	for (auto i : G[u]) {
		int v = uv[i] ^ u;
		if (v == fz || vis[v]) continue;
		DFS(v, u, d + 1, x + (w[i] >= y ? 1 : -1), y);
	}
}
int ucal, vcal;
bool Calc(int u, int x) {
	static int que[MN];
	seq[odep = 0] = 0, sequ[0] = u;
	for (int i = 1; i <= tp; ++i) {
		int v = uv[stk[i]] ^ u;
		for (int j = 1; j <= siz[v]; ++j) tmp[j] = -Inf;
		ndep = 0, DFS(v, u, 1, w[stk[i]] >= x ? 1 : -1, x);
		int l = 1, r = 0, lb = odep, rb = odep + 1;
		for (int j = 1; j <= ndep; ++j) {
			while (rb > 0 && rb > L - j) {
				--rb;
				while (l <= r && seq[que[r]] < seq[rb]) --r;
				que[++r] = rb;
			}
			while (lb >= 0 && lb > R - j) {
				--lb;
				while (l <= r && que[l] > lb) ++l;
			}
			if (l <= r && seq[que[l]] + tmp[j] >= 0) {
				ucal = sequ[que[l]], vcal = tmpu[j];
				return 1;
			}
		}
		while (odep < ndep) seq[++odep] = -Inf;
		for (int j = 1; j <= ndep; ++j)
			if (seq[j] < tmp[j])
				seq[j] = tmp[j], sequ[j] = tmpu[j];
	}
	return 0;
}
void Solve(int u) {
	int nsiz = tsiz;
	tp = 0;
	for (auto i : G[u]) {
		int v = uv[i] ^ u;
		if (vis[v]) continue;
		siz[v] = siz[v] > siz[u] ? nsiz - siz[u] : siz[v];
		stk[++tp] = i;
	}
	_U = u, std::sort(stk + 1, stk + tp + 1, cmp);
	int lb = 1, rb = M, mid, ans = 0, ansu = 0, ansv = 0;
	while (lb <= rb) {
		mid = (lb + rb) >> 1;
		if (Calc(u, dw[mid])) {
			ans = mid;
			ansu = ucal, ansv = vcal;
			lb = mid + 1;
		}
		else rb = mid - 1;
	}
	if (Ans < dw[ans]) {
		Ans = dw[ans];
		AnsU = ansu, AnsV = ansv;
	}
	vis[u] = 1;
	for (auto i : G[u]) {
		int v = uv[i] ^ u;
		if (vis[v]) continue;
		rsiz = tsiz = siz[v], GetRoot(v, 0), Solve(Root);
	}
}

int main() {
	scanf("%d%d%d", &N, &L, &R);
	for (int i = 1; i < N; ++i) {
		int x, y;
		scanf("%d%d%d", &x, &y, &w[i]);
		uv[i] = x ^ y;
		G[x].push_back(i);
		G[y].push_back(i);
		dw[i] = w[i];
	}
	std::sort(dw + 1, dw + N);
	M = std::unique(dw + 1, dw + N) - dw - 1;
	rsiz = tsiz = N, GetRoot(1, 0), Solve(Root);
	printf("%d %d\n", AnsU, AnsV);
	return 0;
}
```

---

## 作者：天命之路 (赞：11)

来一篇代码好看一点的。

首先，做这个题目需要学会一个东西：**点分治**

点分治这里不多讲，只说一下大概步骤：

1. 在一棵无根树中选出一个点 $p$ 作为树根 

2. 看看有没有经过 $p$ 的合法路径

3. 将 $p$ 删除

4. 对 $p$ 的每棵子树递归执行 1~3 步

细节请去模板题，包教包会。

如果第二步的复杂度是 $O(siz)$ (此处及以后的$siz$ 都指无根树大小)，那么单次点分治的时间复杂度为 $O(n\log n)$

**正题**

遇到中位数，感觉直接统计不好算，想到二分答案

注意到这里的中位数是往大了取，所以对于二分答案$mid$，将$\ge mid$ 的边的权设为 $1$ ，否则设为 $-1$,判断树上有没有一条大于等于 $0$ 的路径即可。

这确实是可以用点分治解决的，看这个判断条件。

我们主要看看第二步怎么办。

刚开始看到时，我是想到了 CF293E 的思路，对到根结点 $p$ 深度 $dep$ 建立树状数组，然后将根结点 $p$ 的所有后代按照到根的边权和 $dis$ 排序，然后双指针扫描统计，看最后路径条数是否大于0


但是 这一步复杂度是 $O(siz\log siz)$，总时间复杂度为 $O(n\log^2 n \log w)$ ($w$ 为值域大小) ，过不了

我们的目标就是砍掉一个 $log$

注意到对于深度相同的链，我们只保留边权和最大的。

那么可以开两个数组 $f,g$ ,处理到一个子树时，令 $f[i]$ 为 **之前的所有子树**中深度为 $i$ 的链的边权和最大值， $g[i]$ 为**当前子树**中深度为 $i$ 的链的边权和最大值

那么，对于每个子树，我们要判断的东西就是
$$\max\{f[i]+g[j]|L\le i+j \le U\}\ge 0$$

是否成立

注意到，随着 $j$ 的递减，我们$f[i]$ 的可选区间 $[L-j,U-j]$ 是在以固定速度向右滑动的。

这就像滑动窗口了，可以用单调队列来做。


但是，最坏情况下，单调队列要处理的值域可以达到 $[1,n-1]$ ，对于每个子树都这么干，显然是过不了的

我们思考一下，为什么单调队列要维护这么多数据？有些子树的最大深度明明没有这么大，有很多信息显然是无用的。

设当前子树的最大深度为 $mxd$ ，前面所有子树的最大深度为 $pre$

实际上，我们只要统计在 $[1,pre]$ 之间的信息。

如果 $pre\le mxd$ 的话，我们对于单个子树的复杂度就是 $O(mxd)$ 了，不是吗?

由于子树之间的顺序是可以交换的，所以我们完全可以将所有子树按最大深度排序，然后进行统计。


这样对于一次点分治，复杂度从 $O(siz \log siz)$ 降为 $O(siz)$ ，总复杂度为 $O(n\log n \log w)$


有必要指出的是，由于新加了个排序操作，所以对其复杂度单独分析一下：

如果对于一个点分治中的根结点，他有 $p$ 个子树，则排序的复杂度为 $O(p\log p)$

而这 $p$ 个子树对应着 连向根结点的 $p$ 条边

由于总共只有 $n-1$ 条边，所以子树总个数应该是与 $n$ 同阶的。

所以排序的总时间复杂度为 $O(n\log n \log w)$


两相合并，整个程序的时间复杂度为 $O(n\log n \log w)$

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
void read(T &a)
{
 	char ch;int sign=1;
 	for(ch=getchar();!isdigit(ch);ch=getchar())
 	if(ch=='-') sign=-1;
 	a=ch&15;
 	for(ch=getchar();isdigit(ch);ch=getchar())
 	a=(a<<3)+(a<<1)+(ch&15);
 	a*=sign;
}
template<typename T>inline bool ckmax(T &x,const T &y) {    if(x<y) return x=y,true;return false;}
const int N=1e5+5,M=2e5+5;
int fir[N],nxt[M],to[M],w[M],ect=0;
inline void addedge(int u1,int v1,int w1)
{
	nxt[++ect]=fir[u1];fir[u1]=ect;to[ect]=v1;w[ect]=w1;
}
int n,L,U;
int f[N],g[N];
#define wei(z) (z>=val?1:-1)
int que[N];
int head,tail;
int dis[N],dep[N],maxd[N];
bool sgn[N];
int sz[N],maxx,pos;
#define Edge(x) for(int i=fir[x],y,z;y=to[i],z=w[i],i;i=nxt[i])
inline void getroot(int x,int S,int fa)
{
	sz[x]=1;
	int res(0);
	Edge(x)
	{
		if(y==fa||sgn[y]) continue;
		getroot(y,S,x);
		sz[x]+=sz[y];
		res=max(res,sz[y]);
	}
	res=max(res,S-sz[x]);
	if(res<maxx) maxx=res,pos=x;
}
int pf[N],pg[N];
inline void dfs(int st,int p,int dep1,int len1,int val,int fa,int rt)
{
	ckmax(maxd[st],dep[p]=dep1);
	if((dis[p]=len1)>g[dep[p]])
	{
		g[dep[p]]=dis[p],pg[dep[p]]=p;
	//	if(rt==15) printf("points:%d,%d,%d,%d\n",st,p,dep[p],dis[p]);
	}
	
	Edge(p)
	{
		if(y==fa||sgn[y]) continue;
		dfs(st,y,dep1+1,len1+wei(z),val,p,rt);
	}
}
int srt[N],weight[N],ans1,ans2;
inline bool cmp(int x,int y) { return maxd[x]<maxd[y];}
inline bool calc(int x,int val)
{
	int total=0,maxdepp=0;
	Edge(x) if(!sgn[y]) srt[++total]=y,maxd[y]=0,weight[y]=z;
	Edge(x) if(!sgn[y]) dfs(y,y,1,wei(z),val,x,x),ckmax(maxdepp,maxd[y]);
	sort(srt+1,srt+total+1,cmp);
	for(int i=0;i<=maxdepp;++i) g[i]=f[i]=-1e9,pf[i]=pg[i]=0;
//	if(x==15)
//	{
//		printf("maxdepp=%d\n",maxdepp);
//		for(int i=1;i<=total;i++) printf("srt[%d]=%d\n",i,srt[i]);
//	}
	f[0]=0;pf[0]=x;
	for(int i=1;i<=total;++i)
	{
		int y=srt[i],z=weight[y];
		if(sgn[y]) continue;
		maxd[y]=0;
		dfs(y,y,1,wei(z),val,x,x);
	
		int now=0;head=tail=1;
		for(int j=min(U,maxd[y]);j>=0;j--)
		{
			while(now<=maxd[srt[i-1]]&&now+j<=U)
			{
				while(head<tail&&f[que[tail-1]]<f[now]) tail--;
				que[tail++]=now;now++;
			
			}
			while(head<tail&&que[head]+j<L) head++;
			if(head<tail&&que[head]+j<=U&&f[que[head]]+g[j]>=0) return (ans1=pf[que[head]],ans2=pg[j]),true;
		}
		for(int j=0;j<=maxd[y];j++)
		{
			if(g[j]>f[j])
			pf[j]=pg[j],f[j]=g[j];
			g[j]=-1e9;pg[j]=0;
		}
	}
	return false;
}
int ans,minedge=1e9,maxedge;
inline bool Divide(int root,int val)
{
//	printf("root=%d\n",root);
	if(calc(root,val)) return true;
	sgn[root]=1;
	Edge(root)
	{
		if(sgn[y]) continue;
		maxx=INT_MAX;pos=0;
		getroot(y,sz[y],0);
		if(Divide(pos,val)) return true;
	}
	return false;
}
inline bool Judge(int val)
{
	for(int i=1;i<=n;i++) sgn[i]=0;
	ans1=ans2=0;
	maxx=INT_MAX;pos=0;
	getroot(1,n,0);
	return Divide(pos,val);
}
int main()
{
//	freopen("test.in","r",stdin);
	scanf("%d%d%d",&n,&L,&U);
	for(int i=1,u,v,w;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);addedge(v,u,w);
		minedge=min(minedge,w);
		maxedge=max(maxedge,w);
	}
	int lef=minedge,righ=maxedge,mid,ans=lef;
	while(lef<=righ)
	{
		mid=lef+righ>>1;
		if(Judge(mid)) ans=mid,lef=mid+1;
		else righ=mid-1;
	}
	Judge(ans);
	printf("%d %d\n",ans1,ans2);
//	cout<<Judge(832);
}

```


后期将会向代码中添加更完备的注释，现在先咕着.


---

## 作者：vectorwyx (赞：5)

> 这是一份**有代码**的单 log 做法。

二分答案 $x$，把边权大于等于 $x$ 的边的边权视为 $+1$，其余视为 $-1$。然后考虑长剖，因为处理拐点为 $i$ 的路径时，$i$ 每个儿子的子树内同样深度的链肯定和越大越好。这样就可以枚举每条短链的深度 $i$，然后去看看传上来的长链里深度介于 $[l-i,r-i]$ 的点的权值最大是多少，如果加起来大于等于 $0$ 就能判定可行。在枚举完之后还需要把当前短链的信息与长链合并，即取最大值。如果偷懒写棵线段树肯定能做，不过这样会多一个 log。仔细考量我们需要支持的操作：

* 前端插入一个元素。这是长剖要求支持的。

* 定长区间查询最大值，定长区间可能退化为前缀或后缀。这是判定要求支持的。
* 给定一个长度为 $m$ 的数组 $a$，令第 $i$ 个元素的值与 $a_i$ 取 $\max$。$\sum m\le n$。这是合并子树要求支持的。

定长区间是一个突破口，考虑**按定长分块**，那么我们只需要维护每块块内的前缀最大值和后缀最大值就能拼出任意一个定长区间（包括退化为前后缀时的情况）。我们暂时不管前端插入，先看看块内结构具体长啥样。

考虑前缀修改对于每一块的信息的影响，后缀最大值可以直接 $O(m)$ 暴力修改。前缀最大值呢？对于覆盖到的整块直接重构，问题只剩下处理探出来的那一段零散点。先把对应块单拎出来，相当于我们要写一个数据结构，支持：前缀对 $a$ 取 $\max$，查询前缀最小值。这个就底层 $\log(r-l+1)$ 分块，块间维护 st 表。修改前缀 $[1,m]$ 时，对于覆盖到的整块，直接重构以这个块为起点的 st 表，复杂度是 $O(\lfloor{\frac{m}{\log(r-l+1)}\rfloor\log (r-l+1)})=O(m)$。在重构整块对应 st 表之前先要更新零散点，考虑对每个小块维护一个**压位单调栈**，即状压所有前缀最大值的位置。某个位置变大时，先看看它自己是不是前缀最大值，然后把它后面的某些前缀最大值弹掉。每修改一个位置最多使单调栈的大小 $+1$，那么删除的总复杂度均摊 $O(1)$。查询块内前缀最大值只需要借助位运算定位到最靠右的前缀最大值的位置。

回头看看前端插入：外层分块和底层分块改为从右往左，预留出一个不完整的块放在首位，用于接收前端插入的元素。对于大块内的前两个小块，不维护 st 表，查询和修改时特殊处理，这是为了保证重构 st 表的复杂度能摊到 $m$ 里。如果随着这次前端插入这一块变完整了就 $O(\log(r-l+1))$ 建出 st 表，在前面新开一个空的块，那么这个复杂度可以摊到前端插入里，因为每插入 $\log(r-l+1)$ 次才会建一个 st 表。而如果说随着这次前端插入整个大块都变完整了，就在大块的前面新开一个大块。具体实现就是把分块所需要的所有数组按照长剖内存池那样开出来，在二分前先处理出分块结构。

代码太长了，可以去 [CF](https://codeforces.com/problemset/submission/150/187112684) 上看。底层分块的部分和[这里](https://www.cnblogs.com/vectorwyx/p/15382823.html)差不多。不知道为什么跑得这么慢，路过的卡常大手子能否指点一下QAQ。

---

## 作者：1saunoya (赞：3)

### $sol:$

给一种大常数 $n \log^2 n$ 的做法

考虑二分，由于是中位数，我们就二分这个中位数，$x>=mid$则设为 $1$，否则为 $-1$ 所以我们只需要找到一条 $sum >= 0$ 的路径，这样就有解了，易证。

长链剖分，让长链变成连续的一段区间 $[dfn_u,dfn_u+len_u-1]$，线段树的每个点是对于当前的 $u$ 

然后考虑到对于每个 $u$ 只需要找到长度在 $[L,R]$ 的边，且经过 $u$，很显然是从 $u$ 的子树里面找，显然你只需要算出来先前每层的$\max$存在线段树上面，表示 $dep_v$ 的一堆点，到 $u$ 的最大路径，然后用 $dfs$+线段树，从下到上更新，每次把 $\max$ 更新到长链相对的线段树区间 $[dfn_u,dfn_u+len_u-1]$ 上面。

考虑到更新答案什么的，直接暴力更新长链上的信息（复杂度证明在下面）
即枚举一个长度 $j$，然后你另一条边的长度区间是限定的，于是你可以线段树区间查询，所以每次查询的复杂度都是 $\log n$

每次查询完之后更新相同深度的答案，这样就可以保证不会重复了，复杂度仍然是优美的一个 $\log$。

### 复杂度分析

考虑到它的 $dfs$ 是枚举非儿子点的最深深度，而你非儿子点的一定是某个长链的 $top$，那么你保证了只会遍历一个点一遍，于是就可以证明这个复杂度是 $O(n)$ 的，但是由于你必须要用一个线段树来维护，所以单次的复杂度就到达了 $O(n \log n)$，外边还需要一个二分，复杂度是 $O(n \log^2 n)$ 


```cpp
#include <cstdio>
#include <algorithm>

int read() {
  int x = 0;
  char c = getchar();
  while (c < 48) c = getchar();
  while (c > 47) x = x * 10 + (c - 48), c = getchar();
  return x;
}

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

int n, L, R;
// edge-list
const int maxn = 2e5 + 52;
struct edge {
  int v, nxt, w;
} e[maxn << 1];
int head[maxn], cnt = 0, val[maxn];
void add(int u, int v, int w) {
  e[++cnt] = { v, head[u], w }, head[u] = cnt;
  e[++cnt] = { u, head[v], w }, head[v] = cnt;
}

// dfs
int len[maxn], son[maxn], wt[maxn];
void dfs(int u, int fa) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa) continue;
    dfs(v, u);
    if (len[v] > len[son[u]]) {
      son[u] = v, wt[u] = e[i].w;
    }
  }
  len[u] = len[son[u]] + 1;
}

int dfn[maxn], idx = 0;
void dfs(int u) {
  dfn[u] = ++idx;
  if (son[u]) dfs(son[u]);
  for (int i = head[u]; i; i = e[i].nxt)
    if (!dfn[e[i].v]) dfs(e[i].v);
}
// smt
struct node {
  int mx, t;
} sum[maxn << 2];
int tag[maxn << 2];
node merge(const node& x, const node& y) { return x.mx > y.mx ? x : y; }

void clr(int l, int r, int rt) {
  tag[rt] = sum[rt].t = 0, sum[rt].mx = -n;
  if (l == r) return;
  int mid = l + r >> 1;
  clr(l, mid, rt << 1);
  clr(mid + 1, r, rt << 1 | 1);
}

void pushtag(int rt, int v) { tag[rt] += v, sum[rt].mx += v; }
void pushd(int rt) {
  if (!tag[rt]) return;
  pushtag(rt << 1, tag[rt]);
  pushtag(rt << 1 | 1, tag[rt]);
  tag[rt] = 0;
}

node qry(int a, int b, int l, int r, int rt) {
  if (a <= l && r <= b) return sum[rt];
  pushd(rt);
  int mid = l + r >> 1;
  if (b <= mid) return qry(a, b, l, mid, rt << 1);
  if (a > mid) return qry(a, b, mid + 1, r, rt << 1 | 1);
  return merge(qry(a, b, l, mid, rt << 1), qry(a, b, mid + 1, r, rt << 1 | 1));
}

void change(int a, int b, int l, int r, int rt, int v) {
  if (a <= l && r <= b) {
    pushtag(rt, v);
    return;
  }
  pushd(rt);
  int mid = l + r >> 1;
  if (a <= mid) change(a, b, l, mid, rt << 1, v);
  if (b > mid) change(a, b, mid + 1, r, rt << 1 | 1, v);
  sum[rt] = merge(sum[rt << 1], sum[rt << 1 | 1]);
}

void modify(int l, int r, int rt, int x, node v) {
  if (l == r) {
    sum[rt] = merge(sum[rt], v);
    return;
  }
  pushd(rt);
  int mid = l + r >> 1;
  if (x <= mid)
    modify(l, mid, rt << 1, x, v);
  else
    modify(mid + 1, r, rt << 1 | 1, x, v);
  sum[rt] = merge(sum[rt << 1], sum[rt << 1 | 1]);
}

int flag = 0, xx = 0, yy = 0;
void dfs(int u, int fa, int mid) {
  if (flag) return;
  modify(1, n, 1, dfn[u], { 0, u });
  if (!son[u]) return;
  dfs(son[u], u, mid);
  change(dfn[u] + 1, dfn[u] + len[u] - 1, 1, n, 1, wt[u] >= mid ? 1 : -1);
  if (L < len[u]) {
    node ask = qry(dfn[u] + L, dfn[u] + min(len[u] - 1, R), 1, n, 1);
    if (ask.mx >= 0) {
      flag = 1;
      xx = u, yy = ask.t;
      return;
    }
  }
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || v == son[u]) continue;
    dfs(v, u, mid);
    int w = e[i].w >= mid ? 1 : -1;
    for (int j = 1; j <= len[v]; j++) {
      node c = qry(dfn[v] + j - 1, dfn[v] + j - 1, 1, n, 1);
      c.mx += w;
      if (L - j >= len[u] || j > R) continue;
      node ask = qry(dfn[u] + max(0, L - j), dfn[u] + min(len[u] - 1, R - j), 1, n, 1);
      if (c.mx + ask.mx >= 0) {
        xx = c.t, yy = ask.t;
        flag = 1;
        break;
      }
    }
    for (int j = 1; j <= len[v]; j++) {
      node c = qry(dfn[v] + j - 1, dfn[v] + j - 1, 1, n, 1);
      c.mx += w, modify(1, n, 1, dfn[u] + j, c);
    }
  }
}
bool chk(int mid) {
  clr(1, n, 1);
  flag = 0, dfs(1, 0, mid);
  return flag;
}
int main() {
  // freopen("testdata.in", "r", stdin);
  n = read(), L = read(), R = read();
  for (int i = 1; i < n; i++) {
    int u = read(), v = read(), w = read();
    add(u, v, w), val[i] = w;
  }
  dfs(1, 0), dfs(1), std ::sort(val + 1, val + n);
  int le = 1, ri = std ::unique(val + 1, val + n) - val - 1;
  int ansx = 0, ansy = 0;
  while (le <= ri) {
    int mid = le + ri >> 1;
    if (chk(val[mid])) {
      le = mid + 1;
      ansx = xx, ansy = yy;
    } else
      ri = mid - 1;
  }
  printf("%d %d\n", ansx, ansy);
  return 0;
}
```

---

## 作者：OIer_ACMer (赞：1)

~~我又是最优解？！~~

------------
## 警钟敲烂：
本题主要为**二分**与点分治，这个二分千万别写错~~不然就像我一样调试 $48$ 分钟。~~

------------
## 大致思路：
这道题细节较多，全部拿出来讲一整天也讲不完，因此作者在这里只讲大致思路。

首先，老规矩，输入这棵树的点与边的关系，并**先用结构体**存着，因为我们要先给这颗树排个序，来建一棵新树，因为我们要求最大的中位数，排序是少不的，接着，我们用循环建一颗**点与点之间是之前有多少对点权不一样的点对的数量的边**，因为我们要中位数，两个点点权不同就说明前面有多少位，最后加一就是这个点排第几位，最后通过遍历树就知道这个点是不是中位数~~怎么样，我聪不聪明~~。

之后的操作，就是——找重心，这个操作的步骤我不打算细讲，因为实在是太简单了~~如果你连这都不知道怎么做你来做这题干嘛~~，直接套模板就可以了，具体代码怎么写看我代码就知道了。

然后，就是重点，分治的操作。显然，这个中位数显然可以通过二分来确定。**检验的方法就是把边权大于等于检验值的设为** $1$，**小于的设为** $-1$，看是否有一条路径边权和大于等于 $0$。而分治能发挥作用的地方我觉得也只有将长度分治。对于节点 $x$，先把它的子节点按子树**从小到大排序**，保证复杂度，开个桶记录一下长度为d的边最大的权值 $bkt_{d}^{w}$，以及其端点 $bkt_{d}^{y}$，然后逐一合并。到子树 $y$ 时，先深度优先搜索 dfs 一下，求出子树内的不同长度下最大权值，就开个 $t1$ 数组记录一下，然后对于 $t1$ 内每个值，需要寻找一个滑动区间内的最大值，类似于单调队列的思路。若没有找到可行解则把 $t1$ 合并到桶中，再做深搜去下一个子树。

友情提示：把二分套在分治里面常数更小。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
struct edge1
{
    int u, v, w;
} d1[N];
struct zzx
{
    int y, next, w;
} edge[N << 1];
struct node
{
    int w, x;
} t1[N], bkt[N];
bool vis[N];
int n, l, r, a, b, root, s, cnt, ans, ansu, ansv, tmpu, tmpv, num, maxn1, maxn2;
int head[N], siz[N], son[N], que[N], tree[N];
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline bool cmp1(edge1 i, edge1 j)
{
    return i.w < j.w;
}
inline bool cmp3(int i, int j)
{
    return siz[edge[i].y] < siz[edge[j].y];
}
inline void addedge(int u, int v, int w)
{
    edge[++num].y = v;
    edge[num].w = w;
    edge[num].next = head[u];
    head[u] = num;
    edge[++num].y = u;
    edge[num].w = w;
    edge[num].next = head[v];
    head[v] = num;
}
void getroot(int u, int fa)
{
    siz[u] = 1, son[u] = 0;
    for (int i = head[u], v; i != -1; i = edge[i].next)
    {
        v = edge[i].y;
        if (!vis[v] && v != fa)
        {
            getroot(v, u);
            siz[u] += siz[v];
            if (son[u] < siz[v])
            {
                son[u] = siz[v];
            }
        }
    }
    if (s - siz[u] > son[u])
    {
        son[u] = n - siz[u];
    }
    if (son[u] < son[root])
    {
        root = u;
    }
}
void getdis(int u, int fa, int d, int w, int x)
{
    if (d > maxn2)
    {
        maxn2 = d;
    }
    for (int i = head[u], v; i != -1; i = edge[i].next)
    {
        v = edge[i].y;
        if (!vis[v] && fa != v)
        {
            int uw = w + (edge[i].w >= x ? 1 : -1), ud = d + 1;
            if (t1[ud].w < uw)
            {
                t1[ud].w = uw, t1[ud].x = v;
            }
            getdis(v, u, ud, uw, x);
        }
    }
}
inline bool check(int u, int x)
{
    bkt[0].w = 0, bkt[0].x = u;
    maxn1 = 0, maxn2 = 1;
    for (int i = 1, v; i <= cnt; i++)
    {
        v = edge[tree[i]].y;
        for (int j = 2; j <= siz[v]; j++)
        {
            t1[j].w = -1e9;
        }
        int tmp = edge[tree[i]].w >= x ? 1 : -1;
        t1[1].w = tmp, t1[1].x = v;
        getdis(v, u, 1, t1[1].w, x);
        int a1 = 1, b1 = 0, a2 = maxn1, b2 = maxn1;
        for (int j = 1; j <= maxn2; j++)
        {
            while (a2 >= 0 && j + a2 >= l)
            {
                while (a1 <= b1 && bkt[que[b1]].w <= bkt[a2].w)
                {
                    b1--;
                }
                que[++b1] = a2;
                a2--;
            }
            while (b2 >= -1 && j + b2 >= r)
            {
                while (a1 <= b1 && que[a1] > b2)
                {
                    a1++;
                }
                b2--;
            }
            if (a1 <= b1 && t1[j].w + bkt[que[a1]].w >= 0)
            {
                tmpu = t1[j].x, tmpv = bkt[que[a1]].x;
                return true;
            }
        }
        while (maxn1 < maxn2)
        {
            bkt[++maxn1].w = -1e9;
        }
        for (int j = 1; j <= maxn1; j++)
        {
            if (bkt[j].w < t1[j].w)
            {
                bkt[j].x = t1[j].x, bkt[j].w = t1[j].w;
            }
        }
    }
    return false;
}
void divide(int u)
{
    vis[u] = true;
    int ll = a, rr = b;
    cnt = 0;
    for (int i = head[u], v; i != -1; i = edge[i].next)
    {
        v = edge[i].y;
        if (!vis[v])
        {
            siz[v] = siz[v] > siz[u] ? s - siz[u] : siz[v];
            tree[++cnt] = i;
        }
    }
    sort(tree + 1, tree + cnt + 1, cmp3);
    while (ll <= rr)
    {
        int mid = (ll + rr) >> 1;
        if (check(u, mid))
        {
            ll = mid + 1;
        }
        else
        {
            rr = mid - 1;
        }
        if (rr <= ans)
        {
            break;
        }
    }
    if (rr > ans)
    {
        ans = rr, ansu = tmpu, ansv = tmpv;
    }
    for (int i = head[u], v; i != -1; i = edge[i].next)
    {
        v = edge[i].y;
        if (!vis[v] && siz[v] > l)
        {
            s = siz[v], root = 0;
            getroot(v, u);
            divide(root);
        }
    }
}
int main()
{
    n = read();
    l = read();
    r = read();
    num = -1;
    memset(head, -1, sizeof(head));
    a = 1e9, b = 0;
    for (int i = 1; i < n; i++)
    {
        d1[i].u = read(), d1[i].v = read(), d1[i].w = read();
    }
    sort(d1 + 1, d1 + n, cmp1);
    d1[0].w = -1;
    for (int i = 1, summm = 0; i < n; i++)
    {
        if (d1[i].w != d1[i - 1].w)
        {
            summm++;
        }
        addedge(d1[i].u, d1[i].v, summm);
        if (summm < a)
        {
            a = summm;
        }
        if (summm > b)
        {
            b = summm;
        }
    }
    memset(vis, false, sizeof vis);
    root = 0, son[0] = n, s = n, ans = -1;
    getroot(1, 0);
    divide(root);
    cout << ansu << ' ' << ansv << endl;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121795958)

---

## 作者：DaiRuiChen007 (赞：1)

# CF150E 题解

[Problem Link](https://www.luogu.com.cn/problem/CF150E)

**题目大意**

> 给定一颗带边权的树，求一条边数在 $[L,R]$ 之间的路径，并使得路径上边权的中位数最大。
>
> 数据范围：$n\le 10^5$。

**思路分析**

显然直接二分中位数是否 $\ge x$，那么把 $\ge x$ 的看成 $1$，否则是 $-1$，那路径合法当且仅当路径权值和非负。

考虑点分治求经过 $p$ 的路径，那么我们就要求 $dep_u+dep_v\in[L,R],dis_u+dis_v\ge 0$ 的路径 $(u,v)$，枚举每个子树，对于相同深度的点我们显然只保留 $dis$ 最大的一个，然后按深度枚举 $u$，我们只要求深度在 $[L-dep_u,R-dep_u]$ 中最大的 $dis$，直接单调队列扫一遍就行。

但是对于两个这样的子树 $v,x$，设他们的信息大小为 $q_v,q_x$（可以看成最大深度或子树大小），合并复杂度为 $\mathcal O(q_v+q_x)$，但合并后的信息大小会达到 $\max(q_v,q_x)$，如果第一次就找到一个很大的 $q_v$，复杂度会退化到 $\mathcal O(n^2)$，因此可以把子树按 $q$ 小到大排序，复杂度是 $\mathcal O(\sum q_u)$，即线性于子树大小的，一次点分治的复杂度就是 $\mathcal O(n\log n)$ 的。

时间复杂度 $\mathcal O(n\log ^2n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5,inf=1e9;
int n,L,R;
struct Edge { int v,w; };
vector <Edge> G[MAXN];
bool vis[MAXN];
int siz[MAXN],cur[MAXN],mq[MAXN];
vector <array<int,2>> Que[MAXN];
array<int,2> ans;
vector <int> ord;
inline void dfs(int u) {
	vis[u]=true,ord.push_back(u);
	for(auto e:G[u]) if(!vis[e.v]) {
		int rt=0,tot=siz[e.v];
		auto find=[&](auto self,int u,int fa) -> void {
			siz[u]=1,cur[u]=0;
			for(auto e:G[u]) if(!vis[e.v]&&e.v!=fa) {
				self(self,e.v,u);
				cur[u]=max(cur[u],siz[e.v]);
				siz[u]+=siz[e.v];
			}
			cur[u]=max(cur[u],tot-siz[u]);
			if(!rt||cur[u]<cur[rt]) rt=u;
		};
		find(find,e.v,u);
		dfs(rt);
	}
}
inline bool check(int lim) {
	ans={-1,-1};
	for(int i=1;i<=n;++i) Que[i].clear(),vis[i]=false;
	for(int u:ord) {
		vis[u]=true;
		vector <int> sons;
		for(auto e:G[u]) if(!vis[e.v]) {
			sons.push_back(e.v);
			auto &Info=Que[e.v]; Info.push_back({0,u});
			auto dfs=[&](auto self,int u,int fa,int dep,int dis) -> void {
				if((int)Info.size()==dep) Info.push_back({dis,u});
				else Info[dep]=max(Info[dep],{dis,u});
				if(dep==R) return ;
				for(auto e:G[u]) if(!vis[e.v]&&e.v!=fa) {
					self(self,e.v,u,dep+1,dis+(e.w>=lim?1:-1));
				}
			};
			dfs(dfs,e.v,u,1,e.w>=lim?1:-1);
		}
		sort(sons.begin(),sons.end(),[&](int vx,int vy){ return Que[vx].size()<Que[vy].size(); });
		if(sons.empty()) continue;
		for(int i=0;i<(int)Que[sons[0]].size();++i) {
			if(L<=i&&i<=R&&Que[sons[0]][i][0]>=0) ans={Que[sons[0]][i][1],u};
		}
		for(int s=1;s<(int)sons.size();++s) {
			int x=sons[s-1],v=sons[s],hd=1,tl=0; //x->v
			int sx=Que[x].size(),sv=Que[v].size();
			for(int i=min(sx-1,R);i>L;--i) {
				while(hd<=tl&&Que[x][mq[tl]]<=Que[x][i]) --tl;
				mq[++tl]=i;
			}
			for(int i=0;i<sv;++i) { //L-i~R-i
				while(hd<=tl&&mq[hd]>R-i) ++hd;
				if(0<=L-i&&L-i<sx) {
					while(hd<=tl&&Que[x][mq[tl]]<=Que[x][L-i]) --tl;
					mq[++tl]=L-i;
				}
				if(hd<=tl&&Que[x][mq[hd]][0]+Que[v][i][0]>=0) {
					ans={Que[x][mq[hd]][1],Que[v][i][1]};
					return true;
				}
			}
			for(int i=0;i<sx;++i) Que[v][i]=max(Que[v][i],Que[x][i]);
		}
		for(int v:sons) Que[v].clear();
	}
	return false;
}
signed main() {
	scanf("%d%d%d",&n,&L,&R);
	vector <int> vals;
	for(int i=1,u,v,w;i<n;++i) {
		scanf("%d%d%d",&u,&v,&w);
		vals.push_back(w);
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	int rt=0;
	auto find=[&](auto self,int u,int fa) -> void {
		siz[u]=1,cur[u]=0;
		for(auto e:G[u]) if(!vis[e.v]&&e.v!=fa) {
			self(self,e.v,u);
			cur[u]=max(cur[u],siz[e.v]);
			siz[u]+=siz[e.v];
		}
		cur[u]=max(cur[u],n-siz[u]);
		if(!rt||cur[u]<cur[rt]) rt=u;
	};
	find(find,1,0),dfs(rt);
	sort(vals.begin(),vals.end()),vals.erase(unique(vals.begin(),vals.end()),vals.end());
	int l=0,r=vals.size()-1,res=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(vals[mid])) res=mid,l=mid+1;
		else r=mid-1;
	}
	check(vals[res]);
	printf("%d %d\n",ans[0],ans[1]);
	return 0;
}
```

---

## 作者：绝顶我为峰 (赞：1)

三只 $\log$ 直接冲过去了，6。


中位数一眼二分，先考虑如果没有路径长度的限制怎么做，那么显然可以直接 dfs 一遍找出来权值最大的路径即可。

现在有长度的限制，考虑用线段树维护子树内每一个深度的路径最大值，这样启发式合并的时候每个点直接在线段树上查询一段区间的路径最值就能得到答案，合并两个子树的路径也可以简单地用线段树合并完成。

直接写时间复杂度 $O(n\log^2n\log V)$，会被卡常，你把权值离散化一下复杂度变成 $O(n\log^3 n)$ 就直接过了。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int n,L,R,w,tot,node[100001],cnt,d[100001],s[100001],son[100001],dep[100001],root[100001],ls[100001*20],rs[100001*20],tag[100001*20];
vector<pair<int,int> > v[100001];
pair<int,int> maxn[100001*20]={make_pair(-1e9,0)},ans,tmp;
inline void init()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}
inline int read()
{
    int x;
    cin>>x;
    return x;
}
inline void clear()
{
    for(int i=1;i<=n;++i)
        root[i]=0;
    for(int i=1;i<=tot;++i)
    {
        ls[i]=rs[i]=0;
        maxn[i]={-1e9,0};
    }
    tot=0;
}
inline void push_up(int k)
{
    maxn[k]=max(maxn[ls[k]],maxn[rs[k]]);
}
inline void push_down(int k)
{
    if(tag[k])
    {
        if(ls[k])
        {
            maxn[ls[k]].first+=tag[k];
            tag[ls[k]]+=tag[k];
        }
        if(rs[k])
        {
            maxn[rs[k]].first+=tag[k];
            tag[rs[k]]+=tag[k];
        }
        tag[k]=0;
    }
}
inline int merge(int l,int r,int x,int y)
{
    if(!x||!y)
        return x|y;
    if(l==r)
    {
        maxn[x]=max(maxn[x],maxn[y]);
        return x;
    }
    push_down(x);
    push_down(y);
    int mid=(l+r)>>1;
    ls[x]=merge(l,mid,ls[x],ls[y]);
    rs[x]=merge(mid+1,r,rs[x],rs[y]);
    push_up(x);
    return x;
}
inline void update(int node,int l,int r,int &k,int p)
{
    if(!k)
        k=++tot;
    if(l==r)
    {
        maxn[k]=max(maxn[k],{0,p});
        return;
    }
    push_down(k);
    int mid=(l+r)>>1;
    if(node<=mid)
        update(node,l,mid,ls[k],p);
    else
        update(node,mid+1,r,rs[k],p);
    push_up(k);
}
inline pair<int,int> query(int nl,int nr,int l,int r,int k)
{
    if(!k)
        return {-1e9,0};
    if(l>=nl&&r<=nr)
        return maxn[k];
    push_down(k);
    int mid=(l+r)>>1;
    pair<int,int> res={-1e9,0};
    if(nl<=mid)
        res=max(res,query(nl,nr,l,mid,ls[k]));
    if(nr>mid)
        res=max(res,query(nl,nr,mid+1,r,rs[k]));
    return res;
}
inline void dfs1(int k,int f,int deep)
{
    s[k]=1;
    dep[k]=deep;
    for(auto i:v[k])
    {
        if(i.first==f)
            continue;
        dfs1(i.first,k,deep+1);
        s[k]+=s[i.first];
        if(s[i.first]>s[son[k]])
            son[k]=i.first;
    }
}
inline void solve(int k,int f,int mid,int val,int rt)
{
    int l=max(1,dep[rt]+L-(dep[k]-dep[rt])),r=min(n,dep[rt]+R-(dep[k]-dep[rt]));
    if(l>r)
        return;
    pair<int,int> now=query(l,r,1,n,root[rt]);
    if(val+now.first>w)
    {
        w=val+now.first;
        tmp={k,now.second};
    }
    for(auto i:v[k])
    {
        if(i.first==f)
            continue;
        solve(i.first,k,mid,val+(i.second>=mid? 1:-1),rt);
    }
}
inline void dfs2(int k,int f,int mid)
{
    for(auto i:v[k])
        if(i.first==son[k])
        {
            dfs2(i.first,k,mid);
            maxn[root[i.first]].first+=i.second>=mid? 1:-1;
            tag[root[i.first]]+=i.second>=mid? 1:-1;
            root[k]=merge(1,n,root[k],root[i.first]);
        }
    for(auto i:v[k])
    {
        if(i.first==son[k]||i.first==f)
            continue;
        solve(i.first,k,mid,i.second>=mid? 1:-1,k);
        dfs2(i.first,k,mid);
        maxn[root[i.first]].first+=i.second>=mid? 1:-1;
        tag[root[i.first]]+=i.second>=mid? 1:-1;
        root[k]=merge(1,n,root[k],root[i.first]);
    }
    update(dep[k],1,n,root[k],k);
    int l=max(1,dep[k]+L),r=min(n,dep[k]+R);
    if(l<=r)
    {
        pair<int,int> now=query(l,r,1,n,root[k]);
        if(now.first>w)
        {
            w=now.first;
            tmp={k,now.second};
        }
    }
}
inline bool check(int mid)
{
    clear();
    w=-1e9;
    tmp={0,0};
    dfs2(1,0,mid);
    return w>=0;
}
int main()
{
    init();
    n=read(),L=read(),R=read();
    for(int i=1;i<n;++i)
    {
        int x=read(),y=read(),w=read();
        node[++cnt]=w;
        v[x].emplace_back(y,w);
        v[y].emplace_back(x,w);
    }
    dfs1(1,0,1);
    sort(node+1,node+cnt+1);
    cnt=unique(node+1,node+cnt+1)-node-1;
    int l=1,r=cnt,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(check(node[mid]))
        {
            ans=tmp;
            l=mid+1;
        }
        else
            r=mid-1;
    }
    cout<<ans.first<<" "<<ans.second<<'\n';
    cout.flush();
    return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF150E)

## 前言

~~服了，挂了一下午。~~

## 题意

给定一棵 $n$ 个节点的树，每条边有边权 $w_i$，给定 $L$ 和 $R$，找出一条简单路径满足：

1. 边数 $\in[L,R]$。
2. 边权中位数尽量大。

找出任意一条路径输出两个端点。

$1\le L\le R<n\le 10^5$，$1\le w_i\le 10^9$。

## 题解

看到统计路径，容易想到点分治；看到中位数，容易想到二分。

结合两个思路，我们可以在全局二分中位数 $middle$，边权小于 $middle$ 的赋为 $-1$，大于 $middle$ 赋为 $1$。接下来再利用点分治求出是否有满足条件 $1$ 且边权和 $\ge 0$ 的路径。

考虑后者的求法：

1. 线段树：用线段树储存边数为下标的最大边权和，然而复杂度为 $O(n\log_2^3n)$，明显过不了。
2. 单调队列：枚举每个以当前节点为起点的路径，假设边数为 $x$，则相当于要在其他子树中找到边数在 $[L-x,R-x]$ 中的最大边权和，如果 $x$ 是单调的，这个问题相当于滑动窗口，而我们可以使用 $\text{BFS}$ 使其单调。

但是单调队列的复杂度为单次均摊 $O(n)$，放在一起会被卡成 $O(n^2)$，所以这里还要加一些优化：

1. 单调队列的初始化只从当前的 $maxdep$ 开始处理，这样单次复杂度 $O(dep)$。
2. 使用按秩合并，将子树按照 $maxdep$ 从小到大排序，容易证明 $maxdep\le size$，所以单调队列复杂度为 $O(\sum maxdep)\le O(\sum size)=O(n)$，总复杂度为 $O(n\log_2^2n)$。

## 代码

~~呜呜呜我常数太大了被卡了（只有用 C++17 我才能过）。~~

```cpp
// Problem: E. Freezing with Style
// Contest: Codeforces - Codeforces Round #107 (Div. 1)
// URL: https://codeforces.com/problemset/problem/150/E
// Memory Limit: 256 MB
// Time Limit: 7000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define mem(x,y) memset(x,y,sizeof(x))
#define mk make_pair
#define pb push_back
#define ff first
#define ss second
#define _inf 0xc3c3c3c3
using namespace std;
namespace Std{
    void read(int &x){
        x=0;
        int y=1;
        char c=getchar();
        while(c<'0'||c>'9'){
            if(c=='-')y=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9'){
            x=(x<<1)+(x<<3)+(c&15);
            c=getchar();
        }
        x*=y;
    }
    int n,L,R;
    int sz[300010],dep[300010],mx[300010],dis[300010],root,rt,ans,tld,trd,ld,rd;
    vector<pair<int,int> >to[300010],re[300010];
    vector<int>son[300010];
    int ma[300010],sta[300010],top,fa[300010],q[300010],ls,rs;
    bool vis[300010];
    void findroot(int x,int y,int z){
        sz[x]=1;
        mx[x]=0;
        for(auto i:to[x]){
            if(i.ff==y||vis[i.ff])continue;
            findroot(i.ff,x,z);
            sz[x]+=sz[i.ff];
            mx[x]=max(mx[x],sz[i.ff]);
        }
        mx[x]=max(mx[x],z-sz[x]);
        if((!root)||mx[x]<mx[root])root=x;
    }
    void dfs(int x,int y){
        mx[x]=dep[x];
        sz[x]=1;
        for(auto i:to[x]){
            if(i.ff==y||vis[i.ff])continue;
            dep[i.ff]=dep[x]+1;
            dfs(i.ff,x);
            mx[x]=max(mx[x],mx[i.ff]);
            sz[x]+=sz[i.ff];
        }
    }
    void bfs(int x){
        queue<int>q;
        q.push(x);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            sta[++top]=u;
            for(auto i:re[u]){
                if(i.ff==fa[u]||vis[i.ff])continue;
                dis[i.ff]=dis[u]+i.ss;
                dep[i.ff]=dep[u]+1;
                fa[i.ff]=u;
                q.push(i.ff);
            }
        }
    }
    void init(int x){
        if(x==1){
            ++x,--x;
        }
        vis[x]=true;
        for(auto i:to[x]){
            if(vis[i.ff])continue;
            dep[i.ff]=1;
            dfs(i.ff,x);
        }
        sort(to[x].begin(),to[x].end(),[&](pair<int,int>x,pair<int,int>y){return sz[x.ff]<sz[y.ff];});
        for(auto i:to[x]){
            if(vis[i.ff])continue;
            root=0;
            findroot(i.ff,x,sz[i.ff]);
            son[x].pb(root);
            init(root);
        }
    }
    void solve(int x){
        vis[x]=true;
        ma[0]=x;
        dis[x]=0;
        int now=1,mxx=0;
        top=0;
        for(auto i:re[x]){
            if(vis[i.ff])continue;
            dep[i.ff]=1;
            dis[i.ff]=i.ss;
            fa[i.ff]=x;
            bfs(i.ff);
            int nowl=min(mxx+1,L),nowr=min(mxx,R);rs=0,ls=1;
            for(int j=nowr;j>=nowl;--j){
                while(ls<=rs&&dis[ma[j]]>=dis[ma[q[rs]]])--rs;
                q[++rs]=j;
            }
            int tmp=now;
            while(now<=top){
                int aiml=max(0,L-dep[sta[now]]),aimr=min(mxx,R-dep[sta[now]]);
                while(nowl>aiml){
                    --nowl;
                    while(ls<=rs&&dis[ma[nowl]]>=dis[ma[q[rs]]])--rs;
                    q[++rs]=nowl;
                }
                nowr=aimr;
                while(ls<=rs&&q[ls]>aimr)++ls;
                if(ls<=rs&&dis[ma[q[ls]]]+dis[sta[now]]>ans)ans=max(ans,dis[ma[q[ls]]]+dis[sta[now]]),tld=ma[q[ls]],trd=sta[now];
                ++now;
            }
            now=tmp;
            while(now<=top){
                if(dis[sta[now]]>dis[ma[dep[sta[now]]]])ma[dep[sta[now]]]=sta[now];
                mxx=max(mxx,dep[sta[now]]);
                ++now;
            }
        }
        for(int i=1;i<=top;++i)ma[dep[sta[i]]]=0;
        for(auto i:son[x])solve(i);
    }
    bool work(int x){
        dis[0]=_inf;
        for(int i=1;i<=n;++i){
            re[i].clear();
            for(auto j:to[i]){
                if(j.ss>=x)re[i].pb(mk(j.ff,1));
                else re[i].pb(mk(j.ff,-1));
            }
        }
        mem(vis,0);
        ans=_inf,tld=0,trd=0;
        solve(rt);
        return (ans>=0);
    }
    void main(){
        read(n);read(L);read(R);
        ma[0]=0;
        int u,v,w;
        for(int i=1;i<n;++i){
            read(u);read(v);read(w);
            to[u].pb(mk(v,w));
            to[v].pb(mk(u,w));
        }
        findroot(1,1,n);
        rt=root;
        init(root);
        int l=0,r=1000000;
        while(l<r){
            int mid=((l+r+1)>>1);
            if(work(mid))l=mid,ld=tld,rd=trd;
            else r=mid-1;
        }
        work(l);ld=tld,rd=trd;
        printf("%d %d\n",ld,rd);
    }
}
int main(){
    return Std::main(),0;
}
```


---

## 作者：chroneZ (赞：0)

对于中位数最大的限制，考虑二分答案后将小于 $\text{mid}$ 的边权视作 $1$，大于等于 $\text{mid}$ 的边权视作 $0$，记路径长度为 $\text{len}$，则路径可行当且仅当路径上的边权和 $\leq \frac{\text{len}}{2}$。

自然地想到点分治，考虑点分治过程中怎样对某个根 $u$ 判断有无经过 $u$ 的可行路径。记 $(l, s)$ 表示一条长为 $l$，链上边权和为 $s$ 的链，则对于一条已被合并的链 $(l_1, s_1)$ 和一条待处理的链 $(l_2, s_2)$ 而言，两条链相接是可行的，当且仅当 $s_1 + s_2 \leq \frac{l_1 + l_2}{2} \Rightarrow 2s_2 \leq l_1 + l_2 - 2s_1$。

为了尽可能保证存在这样的可行路径，应该令左式尽可能小，右式尽可能大，因此对于一棵待处理的子树，可以先对每个 $l_2$ 处理出长度为 $l_2$ 的链中最小的 $s_2$，并对每个 $l_1$ 求其最大的 $l_1 - 2s_1$。形式化地，记 $\text{rec}_i = \min \limits_{l_2 = i} s_2$，并记 $f_i = \max \limits_{l_1 = i} l_1 - 2s_1$，枚举 $i = l_2$，如果存在 $i + \max \limits_{j \in [L - i, R - i]} f_j \geq \text{rec}_i$，便说明存在合法路径。

当我们判断完有无合法路径后，可以通过以下方式将这棵新子树与已有子树的信息合并：对所有 $i$ 令 $f_i \gets \max(f_i, i - 2\text{rec}_i)$ 即可。对于求是否存在合法路径的部分，暴力线段树的复杂度是 $\mathcal{O}(n \log^3 n)$ 的，发现所求区间定长，因此可以运用单调队列求解。

要注意的是实现时的**上界**问题。如果不加任何优化，每次单调队列之前我们都会预处理一段长为 $R - L + 1$ 的区间的最大值，复杂度直接退化到 $\mathcal{O}(n ^ 2)$。发现对于 $\text{rec}$ 而言，它的最大有效下标取决于当前子树中最长的链的长度，也即子树深度。因此一个比较显而易见的优化是，可以将判断区间的上界对 $\text{rec}$ 或 $f$ 的最大有效下标取 $\min$。形式化地，对 $i + \max \limits_{j \in [L - i, R - i]} f_j \geq \text{rec}_i$ 一式，$i$ 的上界最大只需达到**当前子树的最大深度**，$j$ 的上界最大只需达到**已遍历过子树中的最大深度**。对每一棵子树而言，复杂度可以被认为是这两个上界之和。

感性上可能觉得这个优化很有道理，类似于树上背包的上下界优化，我们让它的上界和子树深度（也可以认为是子树大小）扯上了关系。事实上确实如此，但仅仅这样还不够，因为如果遍历子节点的过程中，第一棵子树的深度非常大，那么在遍历之后的子树时，每棵子树的循环上界仍然可以达到 $\mathcal{O}(n)$，最劣复杂度仍然在 $\mathcal{O}(n ^ 2)$。我们发现问题出在 $j$ 的上界上，因此考虑是否可以对所有子树先按最大深度排序后再执行上述过程呢？

这个优化类似于按秩合并，由于我们将子树按最大深度排了序，因此**已遍历过子树的最大深度**不会超过**当前子树的最大深度**，复杂度成功被优化为 $\mathcal{O}(\sum \limits_{v \in son_u} \text{dep}_v) = \mathcal{O}(n)$。

其实也可以按照子树大小排序，两种按秩合并的方式的复杂度是相同的。总体时间复杂度为 $\mathcal{O}(n\log n\log V)$。

还有一个比较有用的常数优化是，总共要进行 $\mathcal{O}(\log V)$ 次的点分治，但每次点分治时找重心的部分是重复的，因此可以在进行一次点分治后将重心按顺序离线下来，这样就不必进行 $\log$ 次的 $\mathtt{calcsiz}$ 了。

```cpp
#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int N = 1e5 + 10, inf = 2e9;

vector<pair<int, int>> G[N];
int n, L, R;
int ans, rec1, rec2;
int W;

int vis[N];
int siz[N], msiz[N], tsiz, mins, root;
void calcsiz(int u, int father) {
	msiz[u] = siz[u] = 1;
	for(auto [v, w] : G[u]) {
		if(v == father || vis[v]) continue;
		calcsiz(v, u); siz[u] += siz[v];
		msiz[u] = max(msiz[u], siz[v]);
	}
	msiz[u] = max(msiz[u], tsiz - siz[u]);
	if(msiz[u] <= mins) mins = msiz[u], root = u;
}

int dis[N], lim, rec[N], it[N];
void calcdis(int u, int father, int len) {
	lim = max(lim, len);
	if(dis[u] < rec[len]) {
		rec[len] = dis[u];
		it[len] = u;
	}
	for(auto [v, w] : G[u]) {
		if(v == father || vis[v]) continue;
		w = (w < W); dis[v] = dis[u] + w;
		calcdis(v, u, len + 1);
	}
}

int f[N], it2[N];

int q[N], head, tail;

int lis[N], curl, F;

void dfz(int u) {
	vis[u] = 1; f[0] = 0; it2[0] = u;
	if(F == 0) sort(G[u].begin(), G[u].end(), [](pair<int, int> x, pair<int, int> y) {return siz[x.first] < siz[y.first];});
	int cl = 0;
	for(auto [v, w] : G[u]) {
		if(vis[v]) continue;
		dis[v] = (w = (w < W)), lim = 0;
		calcdis(v, u, 1); 

		head = 0, tail = -1;
		for(int i = lim; i >= 1; i--) {
			int maxv = -inf, cur;
			if(i == lim) {
				int lo = max(0, L - i), hi = min(cl, R - i);
				for(int j = lo; j <= hi; j++) {
					while(head <= tail && f[q[tail]] < f[j]) tail--;
					q[++tail] = j;
				}
			} else {
				while(head <= tail && q[head] < L - i) head++;
				if(R - i >= 0 && R - i <= cl) {
					while(head <= tail && f[q[tail]] < f[R - i]) tail--;
					q[++tail] = R - i;
				}
			}
			if(head <= tail) maxv = f[q[head]], cur = it2[q[head]];
			if(rec[i] * 2 <= i + maxv) ans = 1, rec1 = it[i], rec2 = cur;
		}	
		
		for(int i = 1; i <= lim; i++) {
			if(i - 2 * rec[i] > f[i]) {
				f[i] = i - 2 * rec[i];
				it2[i] = it[i];
			}
			rec[i] = inf; it[i] = -1;
		}
		cl = max(cl, lim);
	}
	for(int i = 1; i <= cl; i++)
		f[i] = -inf, it2[i] = -1;

	for(auto [v, w] : G[u]) {
		if(vis[v]) continue;
		if(F == 0) {
			tsiz = siz[v], root = v, mins = inf;
			calcsiz(v, u); calcsiz(root, -1);
			lis[++curl] = root;
		} else root = lis[++curl];
		dfz(root);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	cin >> n >> L >> R;
	int l = inf, r = -inf;
	for(int i = 1; i < n; i++) {
		int u, v, w; cin >> u >> v >> w;
		l = min(l, w), r = max(r, w);
		G[u].emplace_back(v, w), G[v].emplace_back(u, w);
	}
	
	memset(f, -0x3f, sizeof f);
	int mid, res; pair<int, int> P;
	while(l <= r) {
		mid = (l + r + 1) >> 1; W = mid;

		fill(vis + 1, vis + n + 1, 0);
		fill(rec + 1, rec + n + 1, inf);
		fill(f + 1, f + n + 1, -inf);
		
		if(F == 0) {
			tsiz = n, root = 1, mins = inf;
			calcsiz(1, -1); calcsiz(root, -1);
			lis[++curl] = root;
		} else root = lis[curl = 1];
		
		ans = 0; dfz(root);
		if(ans) res = mid, P = {rec1, rec2}, l = mid + 1;
		else r = mid - 1;
		F = 1;
	}
	cout << P.first << " " << P.second << "\n";
}
```

---

## 作者：封禁用户 (赞：0)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF150E)

[CF](https://codeforces.com/problemset/problem/150/E)

### 写在前面

一道合格的紫题，有难度，有细节。

### 分析

点分治是平凡的。

我们取 $rt$ 为树的重心，把链分为两类。

1. 经过 $rt$ 的链。

1. 不经过 $rt$ 的链。

对于第二类可以递归处理，因此只考虑第一类。

要求中位数最大，可以二分中位数，边权大于等于二分值的令边权为 $1$，小于二分值的令边权为 $-1$，如果链的边权大于等于 $0$ 即该二分值视为满足条件。

我们在一条链，假设其链长为 $len$，就要在前面寻找链长为 $[L-len,R-len]$ 的最大值。

所以加上区间求最大值，就有一个显然的 $O(n\log^{3}{n})$ 的做法。

然而可以优化。

注意到 $[L-len,R-len]$ 可以视为一段“滑动窗口”，想到单调队列优化。

为了保证 $len$ 单调递增，我们需要使用广度优先搜索。

但当 $len = 0$ 时，初始化区间 $[L,R]$ 也许会超时。

注意到我们最多只需要初始化区间右端点到 $dep_{max}$ 即可，我们只要把 $dep$ 按从小到大排序，则初始化区间只要初始化到 $dep$ 即可，而 $\sum{dep}$ 小于等于 $size$。

那加上排序时间复杂度不还是 $O(n\log^{3}{n})$ 吗？由于 $dep$ 的范围较小，其实只要使用计数排序即可。

这样时间复杂度就只有 $O(n\log^2{n})$ 了。
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1;
	x = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
	x *= p;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 100010
int Mx[N],dep[N],leng[N],val[N],a[N],sz[N],n,L,R,now,rt,tot;
bitset<N> vis,found;
pii Ans,ans,mx[N];
pair<int,pii> tp[N];
vector<pii> g[N],Sort[N];
void get_rt(int u,int fa)
{
	sz[u] = 1,Mx[u] = 0;
	for(auto p:g[u])
	{
		int v = p.first;
		if(v == fa||vis[v]) continue;
		get_rt(v,u);
		sz[u] += sz[v];
		Mx[u] = max(Mx[u],sz[v]);	
	}	
	Mx[u] = max(Mx[u],tot - sz[u]);
	if(Mx[u] < Mx[rt]) rt = u;
}
void get_dep(int u,int fa,int deep)
{
	found[u] = 0;
	dep[u] = deep;
	for(auto p:g[u])
	{
		int v = p.first;
		if(v == fa||vis[v]) continue;
		get_dep(v,u,deep+1);
		dep[u] = max(dep[u],dep[v]);
	}
}
queue<int> q;
deque<int> Q;
void solve(int u)
{
	if(ans != (pii){0,0}) return;
	vis[u] = 1;
	get_dep(u,0,0);
	F(i,0,dep[u]) Sort[i].clear(),mx[i] = (pii){-1e9,0};
	mx[0] = (pii){0,u};
	for(auto p:g[u])
	{
		if(vis[p.first]) continue;
		Sort[dep[p.first]].push_back(p); 
	}
	F(c,0,dep[u])
		for(auto p:Sort[c])
		{
			while(Q.size()) Q.pop_back();
			int v = p.first,w = p.second,cnt = 0,nt = 0;
			if(w >= now) val[v] = 1;
			else val[v] = -1;
			leng[v] = 1;
			D(i,dep[v],L)
			{
				while(Q.size()&&mx[i].first >= mx[Q.back()].first) Q.pop_back();
				Q.push_back(i);
			}
			q.push(v);
			found[v] = 1;
			while(q.size())
			{
				int x = q.front();
				q.pop();
				while(nt < leng[x])
				{
					++nt;
					while(Q.size()&&Q.front() > R-nt) Q.pop_front();
					if(0 <= L-nt&&L-nt <= dep[v])
					{
						while(Q.size()&&mx[L-nt].first >= mx[Q.back()].first) Q.pop_back();
						Q.push_back(L-nt); 	
					}	
				}
				if(Q.size()&&mx[Q.front()].first + val[x] >= 0)
				{
					ans = (pii){mx[Q.front()].second,x};	
					while(q.size()) q.pop();
					return;	
				} 
				tp[++cnt] = (pair<int,pii>){leng[x],(pii){val[x],x}};  
				for(auto pp:g[x])
				{
					int y = pp.first,ww = pp.second;
					if(vis[y]||found[y]) continue;
					found[y] = 1;
					leng[y] = leng[x] + 1;
					if(ww >= now) val[y] = val[x] + 1;
					else val[y] = val[x] - 1;
					q.push(y);	
				}	
			}	
			F(i,1,cnt) mx[tp[i].first] = max(mx[tp[i].first],tp[i].second);
		}
	int T = tot;
	for(auto p:g[u])
	{
		int v = p.first;
		if(vis[v]) continue;
		tot = sz[v];
		if(sz[v] > sz[u]) tot = T - sz[u];
		rt = 0;
		get_rt(v,0);
		solve(rt);
	} 
}
inline bool check(int x)
{
	now = a[x];
	vis = 0;
	tot = n;
	rt = 0;
	Mx[0] = 1e9;
	ans = (pii){0,0};
	get_rt(1,0);
	solve(rt);
	if(ans == (pii){0,0}) return 0;
	Ans = ans;
	return 1;
}
int main()
{
	read(n),read(L),read(R);
	F(i,1,n-1)
	{
		int u,v;
		read(u),read(v),read(a[i]);
		g[u].push_back((pii){v,a[i]});
		g[v].push_back((pii){u,a[i]});
	}
	sort(&a[1],&a[n]);
	int m = unique(&a[1],&a[n]) - &a[1];
	int l = 1,r = m,mid;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid - 1;
	}	
	write(Ans.first),putchar(' '),write(Ans.second);
	return 0;
}
```

---

## 作者：FreeTimeLove (赞：0)

首先观察题目发现中位数难以处理，考虑二分答案，令 $w\ge mid$ 的边边权为 $1$ ，$w<mid$ 的边边权为 $-1$，如果存在一条权值不小于 $0$ 的路径满足长度（边数）在 $[L,R]$ 之间就说明答案不小于 $mid$。那么问题转化为给定一棵树，求树上长度在 $[L,R]$ 之间的最大权值路径的权值是否不小于 $0$。

树上路径问题首先考虑点分治，可以用线段树维护各个长度路径的权值 $\max$，不同子树之间直接区间查询单点修改。这样单次点分治时间复杂度 $O(n\log^2n)$，总时间复杂度 $O(n\log ^2n\log V)$，不够优秀。

注意到一棵以 $v$ 为根的子树内到点分治的根 $u$ 的路径长度一定介于 $[1,mxd_v]$ 之间，其中 $mxd_v$ 为该子树的深度。而统计子树 $v$ 和之前遍历到的子树之间的答案时，$v$ 子树内深度为 $j$ 的路径一定是在之前子树内深度为 $[L-j,R-j]$ 的路径中找匹配，为经典的滑动窗口形式，可以用单调队列优化，单次的时间复杂度是 $O(\min(mxd_v,\max\{mxd_{v'}\}))$，其中 $\max\{mxd_{v'}\}$ 为之前子树 $mxd$ 的最大值。按任意顺序合并子树的总时间复杂度是错的，但是如果我们按 $mxd$ 升序排序 $u$ 的子节点，那么合并 $u$ 的所有子树的时间复杂度就是 $O(\sum mxd_v)$，而这个复杂度在最劣情况下是 $O(siz_u)$。那么我们就实现了单次点分治时间复杂度 $O(n\log n)$，总时间复杂度 $O(n\log n\log V)$。

至于方案，在求路径权值时记录一下端点，在找到不小于 $0$ 的路径时更新方案即可。

### code

```cpp
//written_by_FTL
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#include<vector>
#include<queue>
#include<map>
#define ll long long
#define LD long double
#define i7 __int128
#define re return
#define con continue
using namespace std;
inline void ckmin(auto &a,auto b){if(a>b)a=b;}
inline void ckmax(auto &a,auto b){if(a<b)a=b;}
const int N=1e5+5;
inline int rd(){
	int ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	re f?-ans:ans;
}
int n,L,R,l,r,mid,ans,U,V,ansU,ansV;
int nd[N],tt=1;
struct edge{
	int v,w,nxt;
}e[N<<1];
void add(int u,int v,int w){
	e[++tt]={v,w,nd[u]};
	nd[u]=tt;
}
int hd,tl,w[N];
struct xxs{//记录端点和路径权值 
	int u,dis;
	bool operator <(const xxs &x)const{re dis<x.dis;}
}d[N],c[N];
int q[N];
namespace DOV{
	int S,rt,mx[N],bk[N],siz[N];
	int mxd[N],sn[N],cnt;
	bool cmp(int a,int b){re mxd[a]<mxd[b];}
	void dfs1(int u,int fa){//找重心 
		siz[u]=1,mx[u]=0;
		for(int i=nd[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==fa||bk[v])con;
			dfs1(v,u),siz[u]+=siz[v];
			ckmax(mx[u],siz[v]);
		}ckmax(mx[u],S-siz[u]);
		if(mx[u]<mx[rt])rt=u;
	}
	void dfs2(int u,int fa){//计算mxd 
		mxd[u]=0;
		for(int i=nd[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==fa||bk[v])con;
			dfs2(v,u),ckmax(mxd[u],mxd[v]);
		}mxd[u]++;
	}
	void dfs3(int u,int fa,int dep,int dis){//计算路径权值 
		if(dep>R)re;
		if(dep>=L)if(dis>ans){ans=0,U=rt,V=u;re;}
		if(dep<R)ckmax(d[dep],(xxs){u,dis});
		for(int i=nd[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==fa||bk[v])con;
			dfs3(v,u,dep+1,dis+(e[i].w>=mid?1:-1));
		}	
	}
	void sol(int u){
		rt=0,dfs1(u,0);
		bk[u=rt]=1;
		cnt=0;
		for(int i=nd[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(bk[v])con;
			dfs2(v,u);
			sn[++cnt]=v,w[v]=e[i].w>=mid?1:-1;
		}
		sort(sn+1,sn+cnt+1,cmp); 
		for(int i=1;i<=cnt;i++){
			memset(d,0xc3,(sizeof d[0])*(mxd[sn[i]]+1));
			dfs3(sn[i],u,1,w[sn[i]]);
			if(ans>=0)re;
			hd=tl=0;
			for(int j=max(1,L-mxd[sn[i]]);j<=R-mxd[sn[i]]&&j<=mxd[sn[i-1]];j++){
				while(hd<tl&&c[q[tl-1]]<c[j])tl--;
				q[tl++]=j;
			}
			for(int j=mxd[sn[i]];j;j--){//单调队列 
				while(hd<tl&&q[hd]+j<L)hd++;
				if(R-j<=mxd[sn[i-1]]){
					while(hd<tl&&c[q[tl-1]]<c[R-j])tl--;
					q[tl++]=R-j;
				}
				if((int)(hd<tl?c[q[hd]].dis:0xc3c3c3c3)+d[j].dis>ans){
					ans=d[j].dis+(hd<tl?c[q[hd]].dis:0xc3c3c3c3);
					U=d[j].u,V=c[q[hd]].u;
					memset(c,0xc3,(mxd[sn[cnt]]+1)*(sizeof d[0]));re;
				}
			}
			for(int j=mxd[sn[i]];j;j--)ckmax(c[j],d[j]);
		}
		memset(c,0xc3,(mxd[sn[cnt]]+1)*(sizeof d[0]));
		int tmp=S;
		for(int i=nd[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(!bk[v])S=siz[v]<siz[u]?siz[v]:tmp-siz[u],sol(v);
			if(ans>=0)re;
		}
	}
	void init(){
		memset(bk,0,sizeof bk);
		memset(c,0xc3,sizeof c);
		mx[0]=0x3f3f3f3f,S=n;
	}
}
int half(){
	r++;
	while(l<r){
		mid=(l+r)>>1,ans=-1;
		DOV::init();
		DOV::sol(1);
		if(ans>=0)l=mid+1,ansU=U,ansV=V;
		else r=mid;
	}
	printf("%d %d\n",ansU,ansV);
	re l-1;
}
int main(){
	n=rd(),L=rd(),R=rd();
	for(int i=1;i<n;i++){
		int u=rd(),v=rd(),w=rd();
		ckmax(r,w),ckmin(l,w);
		add(u,v,w),add(v,u,w);
	}
	half();
	re 0;
}
/*

*/
```

### $\text{The End.}$


---

## 作者：极寒神冰 (赞：0)

与[[WC2010]重建计划](https://www.luogu.com.cn/problem/P4292)挺相似的一道题目.

前者可以考虑二分答案，假设二分的值为$mid$,将每条边边权$-mid$，判断有没有长度在$\left[L,R\right]$之间且边权和$\geq 0$的路径.

而本题根据中位数的定义同样也可以使用二分答案，假设二分的值为$mid$,将边权$\geq mid$的边看作$+1$,将边权$<mid$的边看作$-1$,判断有没有长度在$\left[L,R\right]$之间且边权和$\geq 0$的路径.

考虑点分治，枚举路径的一端，然后在它前面的子树中寻找有没有符合条件的另一端,假设当前这个点的深度为$x$,在它前面的子树的另一端深度需要在$[L-x,R-x]$之间，对于每个深度保存最大值，然后维护一个单调队列.

之后枚举完一个子树将它们加入备选终点.

时间复杂度为$O(n\times log^2 n)$

```cpp
int n,_n,L,R,ansu,ansv;
int val[N];
int siz[N];
int vis[N],cxy=50;
int dis[N],dep[N],que[N],fa[N],cnt[N],rev[N],ljt[N];
int M;
int g[N],gg[N];
vector<pii>e[N];
int bfs(int G)
{
	int st=1,en=0;que[++en]=G;fa[G]=0;
	for(;st<=en;st++) 
	{
		int u=que[st];
		for(auto qwq:e[u]) 
		{
			int v=qwq.fi;
			if(vis[v]==cxy) continue;
			if(v!=fa[u]) 
				fa[v]=u,que[++en]=v,dep[v]=dep[u]+1,cnt[v]=cnt[u]+(qwq.se<val[M]?-1:1);
		}
	}
	return en;
}
int find_gra(int G)
{
	int Mn=inf,Mnpos;
	int en=bfs(G);
	L(t,1,en)
	{
		int u=que[t];
		int mx=0;siz[u]=1;
		for(auto qwq:e[u])
		{
			int v=qwq.fi;
			if(vis[v]==cxy||v==fa[u]) continue;
			siz[u]+=siz[v];
			ckmax(mx,siz[v]);
		}
		ckmax(mx,en-siz[u]);
		if(mx<Mn) Mn=mx,Mnpos=u;
	}
	return Mnpos;
}
int calc(int u) 
{
	int en=bfs(u);
	R(i,1,en) if(rev[dep[que[i]]]<cnt[que[i]]) rev[dep[que[i]]]=cnt[que[i]],gg[dep[que[i]]]=que[i];
	int ok=0,bg=1,ed=0;
	for(int i=en,j=0;i;i--) 
	{
		int ql=L-i,qr=R-i;if(ql>_n) break; 
		ckmax(j,ql);
		for(;j<=qr&&j<=_n;j++) {for(;bg<=ed&&dis[j]>dis[ljt[ed]];ed--);ljt[++ed]=j;}
		for(;bg<=ed&&ljt[bg]<ql;bg++);
		if(bg<=ed&&dis[ljt[bg]]+rev[i]>=0) {ansu=g[ljt[bg]],ansv=gg[i],ok=1;break;}
	}
	_n=max(_n,en);
	R(i,1,en) {if(rev[i]>dis[i])dis[i]=rev[i],g[i]=gg[i];rev[i]=-inf;}
	return ok;
}

int solve(int u)
{
	int G=find_gra(u);
	dep[G]=cnt[G]=0;
	int en=bfs(G);
	vis[G]=cxy;dis[0]=_n=0;g[0]=G;
	R(i,1,en) dis[i]=rev[i]=-inf;
	for(auto qwq:e[G]) 
	{
		int v=qwq.fi;
		if(vis[v]==cxy) continue; 
		if(calc(v)) return 1;
	}
	for(auto qwq:e[G]) 
	{
		int v=qwq.fi;
		if(vis[v]==cxy) continue;
		if(solve(v)) return 1;
	}
	return 0;
}
inline int check() {return solve(1);}
signed main()
{
	n=read(),L=read(),R=read();
	R(i,1,n-1) 
	{
		int u=read(),v=read();val[i]=read();
		e[u].pb(mkp(v,val[i])),e[v].pb(mkp(u,val[i]));
	}
	sort(val+1,val+n);
	int l=1,r=n-1;
	while(l<=r) 
	{
		M=(l+r)>>1;cxy--;
		if(check()) l=M+1;else r=M-1;
	}
	M=r;cxy--;check();
	printf("%lld %lld\n",ansu,ansv);
}
```


---

