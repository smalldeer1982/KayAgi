# 草莓 Strawberry

## 题目背景

小 M 很喜欢草莓。

草莓可以抽象为一棵树 $T$。我也不知道为什么可以，但草莓甚至可以飞，抽象成一棵树想必问题也不大吧。

## 题目描述

给定一棵树 $T$，点和边均有权值。

一条简单路径是一条不重复经过任意一个点的路径。可以证明，两个节点 $u$ 和 $v$ 之间的简单路径是唯一的，我们将其记为 $P(u,v)$。一条路径的长度是它所包含的所有边的权值和。

你有两个集合 $S$ 和 $G$。

在一开始，你必须选择一个点作为 **当前点** 并且将其加入集合 $S$。接下来可以进行任意次操作，一次操作的形式如下：

假设你的 **当前点** 为 $u$，你可以选择一个节点 $v$，使得 $v \neq u$，然后将你的 **当前点** 更新为 $v$，并且将点 $v$ 加入集合 $S$，将路径 $P(u,v)$ 加入集合 $G$。

在你进行完所有操作之后，你得到的收益为 $S$ 中所有点的点权和 $\times$ $G$ 中所有路径的长度的最小值。如果 $G$ 为空，我们认为第二项的值为 $0$。

注意 $S$ 和 $G$ 都是 **不可重集**，这意味着，即使你多次将某个点加入集合 $S$，最终在计算点权时，也只会被计算一次。

求得到的收益的最大值。

## 说明/提示

本题采用 **捆绑测试**。

| 子任务编号 |      $n$      |     特殊性质     | 分值 |
| :--------: | :-----------: | :--------------: | :--: |
|     1      |   $\leq 10$   |                  |  5   |
|     2      |  $\leq 100$   |                  |  13  |
|     3      |  $\leq 900$   |                  |  8   |
|     4      | $\leq 214748$ | 树的形态是一条链 |  13  |
|     5      | $\leq 214748$ |     $a_i=0$      |  1   |
|     6      | $\leq 214748$ |                  |  60  |


对于所有数据，保证 $1 \leq n \leq 214748, 0 \leq a_i \leq 10000$，$1 \leq w \leq 10000$。

---

#### 样例 #1 解释

第一组样例给定的图如下。  

[![EWyWjg.png](https://s2.ax1x.com/2019/05/11/EWyWjg.png)](https://imgchr.com/i/EWyWjg)  


## 样例 #1

### 输入

```
6
1 4 2 8 5 7
1 2 3
4 1 2
1 5 1
2 3 4
3 6 1```

### 输出

```
198```

# 题解

## 作者：szhlg (赞：11)

### 怎么是黄题啊zbl，看来我已经弱到连黄题都不会了。。

感觉是一道比较好的构造题。

我们先分析一下题意吧。有两个集合，一个存着你选过的点，另一个存着你选点过程中的两点间路径的最小值。让你最大化所有选的点权 + 最小值的乘积。

值得注意的是，选过的点不论你选多少次都算一次，不代表你不可以选多个点。

好了，看了这个题，我一点思路都没有，于是开始看subtask。

直接输出0就可以得到1分。这就是我比赛的分数。

首先看链的部分分。先说一个结论：一定选的是这个链的一段前缀和一段后缀。![](https://cdn.luogu.com.cn/upload/image_hosting/8692qh2f.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们从左到右编号，从1~5。

首先考虑路径最小值怎么算。那显然是1~4的长度和2~5的长度的最小值。

这个可以这样想：我可以按照1、5、1、4、1、5、2这样的顺序去选。这样就保证了最大化距离的最小值。

然后如果选的不是一段前缀和一段后缀，那显然不如选上。因为这样最小距离是不变的，而点权变大了。

好了，链的部分就这些。

如果是树的话，类比链的情况，可以把直径找出来。像这样的图：
![](https://cdn.luogu.com.cn/upload/image_hosting/16dqav1m.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

找到直径之后，假设那个红色的是直径，我们可以类比链的方法，每次构造选点的顺序，都是考虑走到距离你想选的点最远的那个点，然后再选那个点，然后再跳回距离你选的点最远的点。

这样每个点对于路径最小值的贡献，就是离这个点最远的点与这个点的距离。所以我们可以按照原来的思路，把每个点和距离他距离最远的点之间的距离算出来排序，最终统计答案。

显然距离每个点最远的点是直径两个端点中的一个。

这样就可以直接统计答案了，具体看代码82~91行。

复杂度是O（n log n），瓶颈在于排序。
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
using std::max;
using std::min;
using std::sort;
const int maxn = 300005;
struct stu{
	int to,nxt,w;
}sexy[600005];
long long ans;
int n,hd[maxn],cnt,a[maxn];
void add(int x,int y,int z)
{
	sexy[++cnt].to = y;
	sexy[cnt].nxt = hd[x];
	hd[x] = cnt;
	sexy[cnt].w = z;
}
int dep1[maxn],dep2[maxn],rt1,rt2,dep[maxn];
void dfs1(int x,int fa){
	for(int i=hd[x];i;i=sexy[i].nxt){
		int v = sexy[i].to;
		if(v == fa) continue;
		dep[v] = dep[x] + sexy[i].w;
		dfs1(v,x);
	}
}
struct akk{
	int as,bs;
}chz[maxn];
bool xtt(akk a,akk b){
	return a.as > b.as;
}
void dfs2(int x,int fa){
	for(int i=hd[x];i;i=sexy[i].nxt){
		int v = sexy[i].to;
		if(v == fa) continue;
		dep1[v] = dep1[x] + sexy[i].w;
		dfs2(v,x);
	}
}
int zhijing; 
void dfs3(int x,int fa){
	for(int i=hd[x];i;i=sexy[i].nxt){
		int v = sexy[i].to;
		if(v == fa) continue;
		dep2[v] = dep2[x] + sexy[i].w;
		dfs3(v,x);
	}
}
long long sum1[maxn],sum2[maxn]; 
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<n;i++){
		int x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	} 
	dfs1(1,0);
	int maxx = 0; 
	for(int i=1;i<=n;i++){
		if(maxx < dep[i]){
			maxx = dep[i];
			rt1 = i;
		}
	}
	dfs2(rt1,0);
	maxx = 0;
	for(int i=1;i<=n;i++){
		if(maxx < dep1[i]){
			maxx = dep1[i];
			rt2 = i;
		}
	}
	dfs3(rt2,0); 
	for(int i=1;i<=n;i++){
		chz[i].as = max(dep1[i],dep2[i]);
		chz[i].bs = a[i];
	}
	sort(chz + 1,chz + n + 1,xtt);
	maxx = 0;
	for(int i=1;i<=n;i++){
		maxx += chz[i].bs;
		ans = max(ans,maxx * chz[i].as);
	}
	printf("%lld\n",ans);
}
```


---

## 作者：⚡current⚡ (赞：2)

一开始做不来，看了眼题解，发现和直径有关就有思路了，然后，又不开**long long**见祖宗。这竟是黄题，zbl，写篇题解整理一下思路。

**前置知识:** 最大生成树的求法及性质&直径的求法及性质

我们把树上任意两点见的距离作边权，把树变成一个图，那么对于任意一个点集，点权和是确定的，所以使答案最大的一定是这些点的最大生成树（注意一个点是可以重复选的，只是点权不重复统计而已，所以一定是可以构造任意一棵生成树的）

但枚举点集的复杂度是十分高的，所以我们考虑枚举边集。进行类似**kruskal**的过程，对于每个连通块而言，最小边权递减而点权和递增，且在每一个时刻，点权和一定是当前边集能取到的最大值，所以只要完成这个**kruskal**的过程就一定能求出答案

但复杂度还是太高了，因为完全图有$\frac{n(n-1)}{2}$条边，虽然求答案的过程只需要$n-1$条边，但排序的复杂度无法承受，我们用直径的一些性质进一步优化。

**直径的性质：**对于树上每个点，离它最远的的点一定是直径的两个端点之一，证明不难，而且想必大家都掌握了这个**前置知识**，这里就不写证明了

那么用反证法易证，我们这个类**kruskal**过程中所用边一定**可以**是直径加上其他$n-2$个点到最远的点的路径。所以我们也就不用再求出所有的路径长，只用3次**dfs**求出所需即可。此外由于每次是把一个孤立的点加入直径所在集合中，所以每时每刻都只有一个集合，并查集也不需要了。

至此，时间复杂度$O(nlongn)$，其中排序$O(nlogn)$，求解过程只有$O(n)$，算法的核心思想还是**kruskal**，但代码已经长得一点也不像了

$\text{ugly CODE}\downarrow$

```c++
#include<stdio.h>
#include<algorithm>
using namespace std;

const int MAXN = 500000;
int last[MAXN], ver[MAXN], nxt[MAXN], w[MAXN], dis[MAXN][3], cnt, sm, mn, n;
//dis用来存3次dfs的结果，sm是点权和，mn是最小边权
struct node
{
	int v, p;
	friend bool operator < (const node& a, const node& b) {return a.p > b.p;}
}c[MAXN];
//v是点权，p是最远路径长，运算符重载用于排序，你写cmp也是一样的

int T, far;
//T代表dfs的次数，用来指导dis的储存，far里存的是最远点，用来找直径
void dfs(int x, int from)
{
	int to;
	if(dis[x][T] > dis[far][T]) far = x;
	for(int i = last[x]; i; i = nxt[i])
	{
		to = ver[i];
		if(to == from) continue;
		dis[to][T] = dis[x][T] + w[i];
		dfs(to, x);
	}
}

inline int read()
{
	int x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		x = x*10 + ch - 48;
		ch = getchar();
	}
	return x;
}

inline void add(int& x, int &y, int& z)
{
	nxt[++cnt] = last[x];
	last[x] = cnt;
	ver[cnt] = y;
	w[cnt] = z;
}

int main()
{
	//part.1 读入数据
	n = read();
	int x, y, z;
	for(int i = 1; i <= n; ++i)
	{
		c[i].v = read();
	}
	for(int i = 1; i < n; ++i)
	{
		x = read();
		y = read();
		z = read();
		add(x, y, z);
		add(y, x, z);
	}
	//part.2 3次dfs
    //这段写得比较丑，T和far的含义前面有讲，x，y用来临时存一下直径端点
	T = 0;
	far = 0;
	dfs(1, 0);
	x = far;
	far = 0;
	T = 1;
	dfs(x, 0);
	y = far;
	far = 0;
	T = 2;
	dfs(y, 0);
	for(int i = 1; i <= n; ++i)
	{
		c[i].p = max(dis[i][1], dis[i][2]);
	}
	sort(c+1, c+n+1);//记得排序
	//求答案
	sm = c[1].v;
	long long ans = 0;
	for(int i = 2; i <= n; ++i)
	{
		sm += c[i].v;
		mn = c[i].p;
		ans = max(ans, (long long)sm*mn);//记得long long
	}
	printf("%lld\n", ans);
	return 0;
}
```



---

## 作者：Coffins (赞：1)

~~EA老师本人讲树**基础**讲的题。~~

~~不涉及困难的算法，但是。。。烧 CPU 啊~~

首先易知把直径放到 $G$ 里一定不会让答案变小（毕竟它最大），然后考虑把每个点放入 $S$ 的代价。

可知点权和会加上 $val_i$，但是 $G$ 中最短路径的长度，可能会被更新。

那么当加入一个点时，我们就要尽量让路径变长，根据直径的性质，一个点在树中能到达的最远的点就是直径之一，而直径的端点早早就被扔到 $S$ 中，所以可以记录一个 $dis_i$，表示那条最远路径的长度。

然后考虑如何更新答案。

只需要将 $dis_i$ 降序排列，然后扫一遍即可。

至于 $dis$ 数组，可以在直径两个端点各 dfs 一次。

## Code

只放核心更新答案部分。

```cpp
   priority_queue<pair<int,int> > q;//降序
	for(int i=1;i<=n;i++)
	{
		if(i==l||i==r)//l,r 表示直径的两个端点
		{
			continue;
		}
		q.push(make_pair(dis[i],val[i]));
	}
	int ans=(val[l]+val[r])*dis[l];
	int d=dis[l];
	int s=val[l]+val[r];
	while(!q.empty()) 
	{
		d=q.top().first;//更新最短的路径
		s+=q.top().second;//更新总点权
		ans=max(ans,s*d);//更新答案
		q.pop();
	}
	cout<<ans;
```

---

## 作者：chroneZ (赞：1)

考虑通过原树建立一张完全图 $G$，两点 $u, v$ 间的距离为其在原树上的距离 $\mathop{\mathrm{dis}}(u, v)$。假设我们知道最终要选的点集为 $S$，则最优策略下边集 $E$ 中最小的边权等于**点集 $S$ 导出的子图的最大生成树中的最小边权**。

可以发现如果最大生成树中存在该完全图中最大的边（等价于树的直径），答案一定不劣。那么我们可以先将这条边及这两个直径端点加入最大生成树。

考虑向这个最大生成树加入更多的点。每加入一个点，应同时加入该点与生成树内已有顶点的所有连边中最大的那一条。由于**对于树上每个点，直径的端点一定是与之相距最远的点之一**，因此存在一种最大生成树的方案，使得每新加入一个点时，该点只需向直径端点连边。

因此可以按每个点到两个直径端点的距离中的较大值排序，按顺序加点，维护答案即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	vector<vector<pair<int, int>>> G(n);
	for(int i = 1; i < n; i++) {
		int u, v, w; cin >> u >> v >> w; u--, v--;
		G[u].emplace_back(v, w), G[v].emplace_back(u, w);
	}
	if(n == 1) return cout << 0, 0;
    
	vector<int> dis(n, 0); int it = -1, maxd = 0;
	function<void(int, int)> dfs = [&](int u, int fa) {
		if(dis[u] > maxd) maxd = dis[u], it = u;
		for(auto [v, w] : G[u]) {
			if(v == fa) continue;
			dis[v] = dis[u] + w;
			dfs(v, u);
		}
	};
	vector<int> val(n, 0);
	maxd = 0; dis[1] = 0; dfs(1, -1); int p1 = it;
	maxd = 0; dis[p1] = 0; dfs(p1, -1); int p2 = it;
	for(int i = 0; i < n; i++) val[i] = max(val[i], dis[i]);
	maxd = 0; dis[p2] = 0; dfs(p2, -1);
	
    vector<pair<int, int>> dic;
	for(int i = 0; i < n; i++) {
		val[i] = max(val[i], dis[i]);
		if(i != p1 && i != p2) dic.emplace_back(val[i], i);
	}
	i64 V = a[p1] + a[p2], E = maxd, ans = V * E;
	sort(dic.begin(), dic.end(), greater<pair<int, int>>());
	for(auto [x, y] : dic) {
		V += a[y]; E = min(E, 1ll * x);
		ans = max(ans, V * E);
	}
	cout << ans;
}
```

---

## 作者：Stevehim (赞：0)

# 洛谷 P6615 草莓 Strawberry

[原题链接](https://www.luogu.com.cn/problem/P6615)

## 题意简述

&emsp;&emsp;给你两个**不可重集** $S$ 和 $G$，一个放点权，一个放边权，你在一开始需要选择一个点作为当前点，然后任意选一个点放入点集，将选择点和当前点的简单路径放入边权。

&emsp;&emsp;经过所有操作后定义收益为 $S$ 的点权和以及 $G$ 中最短的那条路径之积，请最大化收益（为甚么感觉跟没说一样QAQ）。

## 题目分析


&emsp;&emsp;感觉比较容易懂，~~也就听了六七遍回放罢~~。

&emsp;&emsp;这道题就是贪心来做。

&emsp;&emsp;可以发现我们一开始就必须放直径，因为直径最长，这样以后放任何边都不会出现“这个边大一点为什么不先加，万一答案更大呢”的情况。

&emsp;&emsp;然后考虑放其它点产生的影响。

&emsp;&emsp;首先加点到点集 $S$ 产生的贡献是非负的（为什么这么说因为你万一加了个重合的点那就是 $0$），所以我们将重点放在如何加边上。

&emsp;&emsp;从贪心的角度来讲，既然最小边的缩小无法避免，我们就要尽可能去缩小这个最小值。

&emsp;&emsp;此时注意直径的一个性质：对于树上任意一点，距离其最远的端点**一定**是**直径端点**之一（解释这里就不解释了，这是两遍 dfs 求树上直径的关键，如果有点迷糊建议重新复习）。

&emsp;&emsp;所以我们就将每个点到树上其它点的最远距离给求出来，然后根据距离降序排序，这样我们每次加边必然加的是当前最长的边，就能尽量的减小边权带来的总收益减小。

&emsp;&emsp;再之后枚举所有点（直径端点除外），一个一个加然后统计最大值就行。

&emsp;&emsp;因为题目给的时限、空间限制都很大，所以我就写了种看起来比较复杂的写法焯过去了（三遍 dfs）。

&emsp;&emsp;附注：我在码代码的时候出现了一些问题，后来自己解决了，不知道看到此题解的各位有没有相同的问题，在此一并写一下。

1. Q：这么讲的话那这道题的当前点有什么用处呢？

   A：其实按照这种做法的话确实没有用处，因为每条加的边里都肯定会有两个直径端点的一部分，我们就可以通过不断的加重点来切换到我们想要的那个直径端点（当然这个操作肯定是直接省略了）（**提示：这道题是可以一个点加多次的，只不过不会重复计算贡献罢了）**。

2. Q：其实好像还有一个但我忘了....想起来再随缘补充吧！

   A：

以下是详细注释的代码：

```cpp
#include <bits/stdc++.h>
#define maxn 300010
#define reg register
using namespace std;
int n, m;
struct EDGE {
	int to, nxt, w;
} a[maxn * 2]; //注意要双向建边
int head[maxn * 2];
struct node{
	long long first;
	int second,num; //权值，距离最远的端点，自己的编号
	friend bool operator < (node a,node b){
		return a.first < b.first;
	}
}dis[maxn],tmp;
int dis2[maxn]; //tmp数组;
int tot; //tot指加边总数
int ans, pos[3]; //pos 记录一个断电，ans记录距离
int pon = 1;
int dw[maxn]; //记录点权
bool dian[maxn]; //记录是否访问
inline int read() { //快读函数
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
inline void add(int x, int y, int z) { //链式前向星
	a[++tot].to = y;
	a[tot].nxt = head[x];
	a[tot].w = z;
	head[x] = tot;
}

inline void dfs(int u, int fa) { //u:当前节点 fa:父亲节点
	if (ans < dis[u].first) { //更新直径端点
		ans = dis[u].first;
		pos[pon] = u;
	}
	for (reg int i = head[u]; i; i = a[i].nxt) { 
		int v = a[i].to, w = a[i].w;
		if (v == fa) continue; //防止出现环
		dis[v].first = dis[u].first + w;
		dfs(v, u);
	}
}

inline void dfs2(int u, int fa) { //为了求出第二个端点，不需要找pos的操作了
	for (reg int i = head[u]; i; i = a[i].nxt) {
		int v = a[i].to, w = a[i].w;
		if (v == fa) continue; //防止出现环
		dis2[v] = dis2[u] + w; //dis2
		dfs2(v, u); //警钟敲烂：第一次写的时候这块没改（直接复制粘贴的），导致我多调了15分钟
	}
}
priority_queue<node> q;
int u, v, w;
int main() {
	n = read();
	for(reg int i = 1; i <= n; i++) dw[i] = read();
	for (reg int i = 1; i <= n - 1; i ++) {
		u = read(), v = read(), w = read();
		add(u, v, w); //双向建边
		add(v, u, w);
	}
	dfs(1,0); //首先要求出pos[1]
	pon++; //这里预备求pos[2]
	ans = 0; //ans清空
	dis[pos[1]].first = 0; //这里清空第一个端点的dis
	dfs(pos[1],0); //求第二个端点，这里可以看作以pos为源点求每个点到它的距离
	dis2[pos[2]] = 0;
	dfs2(pos[2],0); //以第二个端点为源点开始求每个点到它的距离，此时ans不用清零
	for (int i = 1; i <= n; i++) { //更新最远的端点
		if(dis[i].first > dis2[i]) dis[i].second = pos[1];
		else dis[i].first = dis2[i],dis[i].second = pos[2];
		dis[i].num = i;
		if(i == pos[1] || i == pos[2]) continue; //直径端点直接跳过，已经加完了
		q.push(dis[i]);
	}
	long long Ssum = dw[pos[1]] + dw[pos[2]]; //点集的初始值
	long long Gsum = dis[pos[1]].first; //边集的初始值，一定为直径
	long long sum = Ssum * Gsum; //总的答案
	dian[pos[1]] = dian[pos[2]] = true;
	while(!q.empty()){ //开始根据距离枚举，因为最远的点必然有一个直径端点，所以不用担心
		tmp = q.top(),q.pop();
		if(!dian[tmp.num]){ //这个点没有被加入
			dian[tmp.num] = true; //标记
			Ssum += dw[tmp.num];
			Gsum = min(Gsum,tmp.first);
			sum = max(Ssum * Gsum,sum); //计算
		}
	}
	printf("%lld", sum);
	return 0;
}
```
另：好像一不小心跑到最优解了AWA。


---

