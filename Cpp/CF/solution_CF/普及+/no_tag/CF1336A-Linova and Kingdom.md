# Linova and Kingdom

## 题目描述

Writing light novels is the most important thing in Linova's life. Last night, Linova dreamed about a fantastic kingdom. She began to write a light novel for the kingdom as soon as she woke up, and of course, she is the queen of it.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/776211708d76e2738717d34c412159f730c6de15.png)There are $ n $ cities and $ n-1 $ two-way roads connecting pairs of cities in the kingdom. From any city, you can reach any other city by walking through some roads. The cities are numbered from $ 1 $ to $ n $ , and the city $ 1 $ is the capital of the kingdom. So, the kingdom has a tree structure.

As the queen, Linova plans to choose exactly $ k $ cities developing industry, while the other cities will develop tourism. The capital also can be either industrial or tourism city.

A meeting is held in the capital once a year. To attend the meeting, each industry city sends an envoy. All envoys will follow the shortest path from the departure city to the capital (which is unique).

Traveling in tourism cities is pleasant. For each envoy, his happiness is equal to the number of tourism cities on his path.

In order to be a queen loved by people, Linova wants to choose $ k $ cities which can maximize the sum of happinesses of all envoys. Can you calculate the maximum sum for her?

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/550bbb250626ee83a75f7874e99bb74967e95572.png)

In the first example, Linova can choose cities $ 2 $ , $ 5 $ , $ 6 $ , $ 7 $ to develop industry, then the happiness of the envoy from city $ 2 $ is $ 1 $ , the happiness of envoys from cities $ 5 $ , $ 6 $ , $ 7 $ is $ 2 $ . The sum of happinesses is $ 7 $ , and it can be proved to be the maximum one.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/42ded7a124702f40fc5538e5ca404a7c3df59128.png)

In the second example, choosing cities $ 3 $ , $ 4 $ developing industry can reach a sum of $ 3 $ , but remember that Linova plans to choose exactly $ k $ cities developing industry, then the maximum sum is $ 2 $ .

## 样例 #1

### 输入

```
7 4
1 2
1 3
1 4
3 5
3 6
4 7```

### 输出

```
7```

## 样例 #2

### 输入

```
4 1
1 2
1 3
2 4```

### 输出

```
2```

## 样例 #3

### 输入

```
8 5
7 5
1 7
6 1
3 7
8 3
2 1
4 5```

### 输出

```
9```

# 题解

## 作者：VenusM1nT (赞：20)

结论题。  
第一反应：草 SB 结论题，切了  
然后发现会对到根节点路径上全部点产生影响，有点烦人  
等等，路径修改，那岂不是……  
然后发现树剖还要存位置信息，麻烦死了（居然有验题人写了 Orz），想想还是找结论吧  
首先有个结论：如果有个点被选，那么所有它的后代节点都要被选，因为这样才能达到最大贡献，而这个节点又会让所有后代节点的贡献 $-1$，所以这个节点对答案的贡献为 $-\text{siz}_ u$，然后考虑正贡献，显然就是它到根节点的路径上的节点数（除去本身），即 $\text{dep}_ u-1$，综上对于节点 $u$，它的贡献是 $\text{dep}_ u-\text{siz}_ u-1$，丢到优先队列里贪心取一手即可。  
```cpp
#include<bits/stdc++.h>
#define MAXN 200005
#define reg register
#define inl inline
using namespace std;
int cnt,fst[MAXN],nxt[MAXN<<1],to[MAXN<<1];
int n,K,siz[MAXN],dep[MAXN];
long long ans;
priority_queue <int> q;
inl void AddEdge(reg int u,reg int v)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
}
void Dfs(reg int u,reg int pre)
{
	dep[u]=dep[pre]+1;
	for(reg int i=fst[u];i;i=nxt[i])
	{
		reg int v=to[i];
		if(v==pre) continue;
		Dfs(v,u);
		siz[u]+=siz[v];
	}
	q.push(dep[u]-siz[u]-1);
	siz[u]++;
}
int main()
{
	scanf("%d %d",&n,&K);
	for(reg int i=1;i<n;i++)
	{
		reg int x,y;
		scanf("%d %d",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	Dfs(1,0);
	for(reg int i=1;i<=K;i++)
	{
		ans+=q.top();
		q.pop();
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：STA_Morlin (赞：18)

[CF1336A Linova and Kingdom（丽诺娃和王国）
 の 题目传送门。](https://www.luogu.com.cn/problem/CF1336A)

> Tips：此题为 CF 的 RemoteJudge，所以需提交两次同样代码。

# 题目简化
> 给定一个共有 $n$ 个节点的有根树，根为 $1$ 号节点。  
> 你可以选择 $k$ 个节点，将其设置为**贡献点**，其余设置为**非贡献点**。  
> 对于一个贡献点，定义它的**贡献**为其自身至根的路径经过的**非贡献点**的数量。

> 求出所有贡献点的**贡献之和的最大值**。  

# 思路讲解

### 可得前置结论：
如果点 $x$ 为贡献点，那么他的子孙都为贡献点一定最优。

### 证明：
如果 $x$ 为贡献点，其子孙 $y$ 为非贡献点，$x, y$ 的贡献分别为为 $d_x, d_y$：

将 $x, y$ 的性质互换，$d_x$ 不改变，$d_y+1$；  
Q.E.D.

### 原因：
非贡献点可以创造贡献，贡献点不可以创造贡献，所以贡献点要放在非贡献点后面。


综上看出算法：贪心。  

---
---
# 代码实现

因为是从每个贡献点到根，（可以看做根到每个贡献点），所以使用 `dfs`

$dep_x$ 代表 $x$ 的深度，$siz_x$ 代表 $x$ 的子树大小，$q$ 存每个节点贡献值，因为要最大，所以大根堆。

挨个找与 $x$ 相连的点，如果不是他的**直接祖先**，就再 `dfs`，之后 $siz_x$ 更新。（因为这是树，所以不是直接祖先就一定是子孙。）

贡献计算：
- 它本身：$dep_x-1$  
是它到根的路径（不算本身）。

- 它对子孙影响：$siz_x+1$  
因为它变为贡献点，所以子孙的贡献都会减一（还是不算本身）。

加起来就是 $dep_x+siz_x$，直接扔到优先队列里。

#  _CODE_：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int man = 2e5+10;
struct Graph {
	int hed[man], len;
	int nxt[man<<1], to[man<<1];
	void Ins (int u, int v) {
		to[++len] = v;
		nxt[len] = hed[u];
		hed[u] = len;
		return ;
	}
} G;

int n, k;
ll res;
int dep[man], siz[man];
priority_queue <int, vector<int>, less<int> > q;
void dfs (int x,int fa) {
	dep[x] = dep[fa]+1;
	siz[x] = 1;
	for (int i = G.hed[x]; i; i = G.nxt[i]) {
		int t = G.to[i];
		if (t != fa) {
			dfs(t, x);
			siz[x] += siz[t];
		}
	}
	q.push(dep[x]-siz[x]);
	return ;
}
int main () {
	scanf("%d%d", &n, &k);
	for(int u, v, i = 1; i < n; ++ i) {
		scanf("%d%d", &u, &v);
		G.Ins(u, v);
		G.Ins(v, u);//注意：树是无向图
	}
	dfs(1,0);
	for(int i = 1; i <= k; ++ i) {
		res += q.top();//大根堆的堆顶就是最大的
		q.pop();
	}
	printf("%lld", res);
	return 0;
}
```
## E.N.D.

---

## 作者：wsyhb (赞：11)

## 分析 + 题解

看到一道跟树相关的题目，你想到了什么？树形 DP？dfs 序？还是树剖？

我相信，当你读完题面和样例解释后，你一定会说：“都不是，这只是个贪心罢了。”

没错，一种显然的贪心策略是（从下往上）选择深度尽量大、子树大小尽量小的节点，但这不完全正确，因为你没有求得**这两个属性在最优性中的权重**，下面将进行推导。

------------

首先给出一个显然正确的结论：将一个节点作为工业城市的**必要不充分条件**是，这个节点所在子树的其他节点均已作为工业城市。

**证明**：若存在一个工业城市 $x$ 的子孙 $y$ 为旅游城市，那么将 $x$ 和 $y$ 的类型交换后，$y$ 子树的所有节点贡献不变，且其余属于 $x$ 子树的节点贡献加 $1$。

这启发我们一件事：点 $x$ 从旅游城市变为工业城市的**贡献**为 $dep_x-sz_x$，其中 $dep_i$ 表示 $i$ 号点的深度（$dep_1=1$），$sz_i$ 表示以 $i$ 为根子树的大小。

**说明**：此时，$x$ 新增贡献 $dep_x$，且 $x$ 子树内所有节点贡献减 $1$（包括 $x$，即 $x$ 的当前贡献为 $dep_x-1$）。

因此，我们只需贪心选取 $dep_x-sz_x$ 前 $k$ 大的 $x$ 节点作为工业城市即可。

有人可能会问，需不需要考虑上文提到的必要条件。答案是否定的，因为对于任意父子关系 $x$ 和 $y$（$x$ 是 $y$ 的父亲），显然有 $dep_y=dep_x+1>dep_x$，$sz_y<sz_x$，进一步有 $dep_y-sz_y>dep_x-sz_x$。也就是说，根据这种贪心策略选取，必定满足“先选子孙，再选自己”。

## 代码实现

只需遍历一遍树，计算出 $dep$ 和 $sz$，并使用 `nth_element()` 求得 $dep-sz$ 的前 $k$ 大，将其求和即为答案。

**时间复杂度**：$O(n)$

~~轻轻松松最优解^_^~~

------------

**补充：有关 STL 中的 `nth_element()`**

**作用**：求区间第 $k$ 小，并将比这个数小的数放在它之前，将比它大的放在它之后（**无序**，但足以求区间前 $k$ 小）。

**用法**：前三个参数分别为起始位置，第 $k$ 个元素所在位置，结束位置（**左闭右开**），第四个参数为比较函数（可省略，默认为 $<$）。

**时间复杂度**：$O(len)$，$len$ 为区间长度。（类似快速排序实现）

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=2e5+5;
int End[max_n<<1],Last[max_n],Next[max_n<<1],e;
inline void add_edge(int x,int y)
{
	End[++e]=y;
	Next[e]=Last[x];
	Last[x]=e;
	End[++e]=x;
	Next[e]=Last[y];
	Last[y]=e;
}
int dep[max_n],sz[max_n],val[max_n];
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	sz[x]=1;
	for(int i=Last[x];i;i=Next[i])
	{
		int y=End[i];
		if(y!=fa)
		{
			dfs(y,x);
			sz[x]+=sz[y];
		}
	}
	val[x]=dep[x]-sz[x];
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n-1;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
	}
	dfs(1,0);
	nth_element(val+1,val+k,val+n+1,greater<int>());//看似求第 k 大，实则获得前 k 大 
	long long ans=0;
	for(int i=1;i<=k;++i)
		ans+=val[i];
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Polaris_Dane (赞：9)

没错，我就是那个拿树剖过的菜鸡验题人

一开始权值设定为深度

就随便维护一下权值最大值

然后当一个点被选为工业城市时，那么他的所有祖先的权值都必须减$1$

树剖维护一下，每次取个最大值加修改就行了

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<set>
#include<queue>
#define M 1010000
#define inf 0x3f3f3f3f
#define LL long long
#define int long long
const int mod=998244353;
using namespace std;
inline int read(){
	int f=1,x=0;char s=getchar();
	while (!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while (isdigit(s)){x=(x<<1)+(x<<3)+(s^48),s=getchar();}
	return x*f;
}
int n,k,head[M],cnt,ans;
struct edge{int to,nxt;}e[M];
inline void add_edge(int u,int v){e[++cnt].nxt=head[u],head[u]=cnt,e[cnt].to=v;}
int dep[M],fa[M],top[M],son[M],siz[M],id[M],ref[M],tot;
int maxx[M],pos[M],tag[M];
inline void update(int rt){
	maxx[rt]=max(maxx[rt<<1],maxx[rt<<1|1]);
	if (maxx[rt]==maxx[rt<<1]) pos[rt]=pos[rt<<1];
	else pos[rt]=pos[rt<<1|1];	
}
inline void push_down(int rt){
	maxx[rt<<1]+=tag[rt],maxx[rt<<1|1]+=tag[rt];
	tag[rt<<1]+=tag[rt],tag[rt<<1|1]+=tag[rt],tag[rt]=0;	
}
inline void build(int rt,int l,int r){
	int mid=(l+r)>>1;
	if (l==r){pos[rt]=l;return void(maxx[rt]=dep[ref[l]]);}
	build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
	update(rt);
}
inline void modify(int rt,int l,int r,int x,int y,int v){
	if (x<=l&&y>=r){
		maxx[rt]+=v,tag[rt]+=v;
		return;
	}
	push_down(rt);
	int mid=(l+r)>>1;
	if (x<=mid) modify(rt<<1,l,mid,x,y,v);
	if (y>mid) modify(rt<<1|1,mid+1,r,x,y,v);
	update(rt);
}
inline void dfs1(int rt,int f){
	fa[rt]=f,siz[rt]=1;
	for (int i=head[rt];i;i=e[i].nxt){
		if (e[i].to==f) continue;dep[e[i].to]=dep[rt]+1;
		dfs1(e[i].to,rt),siz[rt]+=siz[e[i].to];
		if (siz[e[i].to]>siz[son[rt]]) son[rt]=e[i].to;
	}
}
inline void dfs2(int rt,int topf){
	top[rt]=topf,id[rt]=++tot,ref[tot]=rt;
	if (!son[rt]) return;
	dfs2(son[rt],topf);
	for (int i=head[rt];i;i=e[i].nxt){
		if (e[i].to==fa[rt]||e[i].to==son[rt]) continue;
		dfs2(e[i].to,e[i].to);	
	}
}
signed main(void){
	n=read(),k=read();
	for (int i=1;i<=n-1;i++){
		int u=read(),v=read();
		add_edge(u,v),add_edge(v,u);
	}
	dfs1(1,0),dfs2(1,1),build(1,1,n);
	for (int i=1;i<=k;i++){
		ans+=maxx[1];int x=ref[pos[1]];
		modify(1,1,n,id[x],id[x],-inf);
		while (top[x]!=1){
			modify(1,1,n,id[top[x]],id[x],-1);
			x=fa[top[x]];
		}
		modify(1,1,n,id[1],id[x],-1);
	}printf("%lld",ans);
	return 0;
}
```


---

## 作者：b6e0_ (赞：6)

[CF题面传送门](https://codeforces.com/contest/1336/problem/A) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1336A) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1336A)

大家的思路都好复杂啊，都是我想不到的方法。

设点 $x$ 的深度为 $de_x$，子树大小为 $siz_x$。

发现一个性质：当一个点 $u$ 成为工业城市时，它的子树里一定所有节点都成为了工业城市。否则，在它的子树里选一个点 $v$，它的深度大于 $u$，即更优。

考虑贡献。当一个节点 $x$ 被选时，它会产生 $de_x-1$ 的贡献，但是对于它子树里所有点都会产生 $-1$ 的贡献，再根据上面的性质，它还会产生 $-siz_x+1$ 的贡献，总共会产生 $de_x-siz_x$ 的贡献。所以，处理出每一个节点的贡献，排序累加前 $k$ 个就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//记得开long long！
vector<int>g[200010];
int de[200010],siz[200010],p[200010];
bool cmp(int x,int y)
{
	return x>y;
}
void dfs(int f,int x)
{
	de[x]=de[f]+1;
	siz[x]=1;
	for(int i=0;i<g[x].size();i++)
		if(g[x][i]!=f)
		{
			dfs(x,g[x][i]);
			siz[x]+=siz[g[x][i]];
		}
}
signed main()
{
	int n,k,i,u,v,ans=0;
	cin>>n>>k;
	for(i=1;i<n;i++)
	{
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0,1);
	for(i=1;i<=n;i++)
		p[i]=de[i]-siz[i];
	sort(p+1,p+n+1,cmp);
	for(i=1;i<=k;i++)
		ans+=p[i];
	cout<<ans;
	return 0;
}
```
时间复杂度为 $\mathcal O(n\log n)$。

---

## 作者：chenzida (赞：6)

### 题意简述：
在一棵树上，标记 $k$ 个点，使得从这 $k$ 个点到 $1$ 的路径上经过的未被标记的结点数量最多。

### 思路解析：

这道题看上去十分像一个树形 $dp$，用 $dp[i][j]$ 表示以第 $i$ 个结点为根的子树中选择 $j$ 个结点标记的最大距离。但是这个算法的时间复杂度明显是 $O(n\times k)$，会 $TLE/MLE$，是不可取的。

如果是用树形 $dp$ 的话，这个方法是没有办法再优化的了，因为肯定有一个 $n$ 要用来记录结点编号，另一个 $k$ 要记录选择的点数，所以就要想一想是不是不用树形 $dp$就能解决。

如果不用树形 $dp$，而且要用 $O(n)$ 或 $O(n\times log(n))$ 的时间复杂度，同时又要取最大值，那么基本可以肯定要用贪心来做这道题，那么我们先想一下怎么贪心。

如果是贪心的话，就要有一个贪心的顺序。所以首先一定能推导出一个定理，那就是：

**定理 $1:$** 如果要标记一个结点，那么这个以这个结点为根的子树上的结点都必须被标记。

**证明**：反证法，如果这个点被标记了，并且它的子孙结点没有被标记，则一定可以放弃标记这个点。转而标记它的那个子孙结点，因为这个结点的没被标记的子孙结点到 $1$ 号结点的路径更长，并且对它的其他子孙结点的答案影响更小。注：这里的影响更小指的是如果不标记这个结点，原本这个结点其他的子孙结点到 $1$ 的答案都会增加，因为它们到 $1$ 的路径上就会少被标记一个结点。
证毕。

如果有了定理 $1$，我们可以得出一件事，那就是如果要标记一个结点，一定会标记一整个子树，所以我们要怎么排序呢？当然是按一个结点对整个答案的贡献来排序啦。

**定理 $2:$** 设一个结点的 $dep$ 表示这个结点到 $1$ 的路径经过的结点数（不包括这个点自己），一个结点的 $siz$ 表示这个以这个结点为根的子树包含的结点数量，则这个结点 $x$ 对答案的贡献就是 $dep[x]-siz[x]+1$。

**证明**：新标记一个结点 $x$ 的能够得到的就是它到 $1$ 号结点的路径中经过的结点数，即 $dep[x]$，因为有定理 $1$，所以可以肯定在考虑这个结点时这个结点的祖先结点还不会被标记。但是这个结点对答案的损失就是它的子孙数，因为原本它的子孙 $y$ 的贡献为 $dep[y]$，而现在 $y$ 结点到 $1$ 的路径中经过的结点数 $dep[y]$ 会变少一个，因为这个路径上多标记了一个点，而减少总量就是这个结点的子孙结点数，即 $siz[x]-1$，而贡献减去损失就是 $dep[x]-(siz[x]-1)$，即 $dep[x]-siz[x]+1$。

而我们的贪心的排序关键字就是每个结点对答案的贡献。特别的，就算贡献为负数也要加上，因为必须是正好 $k$ 个。

**具体步骤**

$1.$ 读入，建图

$2.$ 一遍 $dfs$ 初始化出每个结点的 $dep$ 和 $siz$。

$3.$ 用一个 $num$ 数组作为贪心排序关键字，$num[i]=dep[i]-siz[i]+1$，在定理 $2$ 中已经证明。

$4.$ 按 $num$ 从大到小排序，并让 $ans$ 加上前 $k$ 个 $num$ 值。

$5.$ 输出答案。

**总结**

这道题也做完了，那就来总结一下这道题吧。这道题的最大的难点有三个，分别是如何判别这道题是贪心而不是树形 $dp$，定理 $1$ 的证明，和定理 $2$ 的证明。其中我觉得最难的就是怎么打破树形 $dp$ 的思维定式，能想到贪心。所以我总结了一下什么时候会用贪心而什么时候要用 $dp$。

老师或教练教的肯定是“能通过局部最优做出全局最优”，但是这个东西并不通俗易懂，那么我就把这个翻译成人话吧。

就是说当要取 $k+1$ 个东西时，我们取的东西肯定包含只让我们取 $k$ 个东西时我们要取得东西（有可能还取别的但这 $k$ 个东西我们肯定还取）。比如说这一道题，在树的结构固定时，我们取 $k+1$ 个东西时肯定只用考虑第 $k+1$ 个东西怎么取，因为之前取的 $k$ 个东西我们肯定还取。其他的贪心题比如合并果子等经典贪心也会满足这个条件。再回头看一看 $dp$ 问题，就不一定了，比如说最经典的 $01$ 背包 $dp$ 问题。你的最大背包容量为 $k+1$ 时取得物品不一定包含最大背包容量为 $k$ 时取得物品。所以背包问题必须要用 $dp$ 而不能用贪心。

好了也说了不少了，下面上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int NR=2e5+10;
int n,k;
int to[NR<<1],nxt[NR<<1];
int head[NR];
int tot=1;
void add(int x,int y)
{
	to[tot]=y;
	nxt[tot]=head[x];
	head[x]=tot++;
}
int siz[NR],dep[NR];
void dfs(int x,int fa_)
{
	siz[x]=1;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==fa_) continue;
		dep[y]=dep[x]+1;
		dfs(y,x);
		siz[x]+=siz[y];
	}
}
int num[NR];
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),k=read();
	for(int i=1;i<=n-1;i++)
	{
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		num[i]=dep[i]-(siz[i]-1);
	}
	sort(num+1,num+n+1);
	ll ans=0;
	for(int i=n;i>=n-k+1;i--)
	{
		ans+=num[i];
	}
	printf("%lld",ans);
	return 0;
}
 
```

---

## 作者：Warriors_Cat (赞：6)

### $Description:$

在一棵 $n$ 个节点的以 $1$ 为根的树上选出 $k$ 个节点作为 $A$ 节点，其余节点作为 $B$ 节点。问所有 $A$ 节点与根节点的路径中经过的 $B$ 节点个数的和的最大值。

### $Solution:$

我们先一次 $dfs$ 预处理出每个节点的深度和子树大小。然后考虑贪心。（这里 $dep[1] = 1$）

由于选一个节点 $x$ 时，它的子树的深度都会大于 $x$ 的深度，那么它的子树节点对答案的贡献会更大。所以选了节点 $x$ 后它的子树肯定都选了。

那么选节点 $x$ 时，增加的答案为 $dep[x] - 1$，因为它成功变为了 $A$ 节点。同时减少的答案为 $siz[x] - 1$，因为它的子树节点都少了一个。

那么，它对答案的贡献为：$dep[x] - 1 - siz[x] + 1$，即 $dep[x] - siz[x]$。

于是排个序就行了，最后再统计一下答案即可。

下面是代码：

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
struct edge{
	int v, nxt;
}e[400010];
int head[400010], cnt, n, k, x, y, siz[200010], ans;
bool Vis[200010], vis[200010];
struct node{
	int siz, dep, idx;
}a[200010];
inline bool cmp(node a, node b){
	return a.dep - a.siz > b.dep - b.siz; 
}//排序用
inline void add(int u, int v){
	e[++cnt].v = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
inline void dfs(int u){
	a[u].siz = 1;
	a[u].idx = u;
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].v;
		if(a[v].dep) continue;//相当于遍历过
		a[v].dep = a[u].dep + 1;
		dfs(v);
		a[u].siz += a[v].siz;
	}
	return;
}
inline void dfs2(int u, int d){
	if(vis[u]){
		ans += siz[u] * (d - 1);//因为它的子树都选了，所以它们各自的答案一样，直接加
		return;
	}
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].v;
		if(Vis[v]) continue;
		Vis[v] = 1;
		dfs2(v, d + 1);
	}
	return;
}
signed main(){
	scanf("%lld%lld", &n, &k);
	for(int i = 1; i < n; ++i){
		scanf("%lld%lld", &x, &y);
		add(x, y);
		add(y, x);
	}//建树
	dfs(a[1].dep = 1);//第一次 dfs，求子树大小和深度
	for(int i = 1; i <= n; ++i) siz[i] = a[i].siz;
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= k; ++i) vis[a[i].idx] = 1;
	dfs2(Vis[1] = 1, 1);//第二次求答案
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：FZzzz (赞：4)

这里提供一个不一样的算法。

首先考虑 dp，但是 dp 的时候显然不能把 $k$ 这一维纳入状态。

答案关于 $k$ 是个凸函数，这个感性理解一下就可以了。大概可以这样解释：一开始加一个黑点会有很多的贡献，但是后面黑点多了以后再加一个黑点就会减少很多其他点的贡献。

所以我们可以 wqs 二分。大概就是二分一个偏移量，然后每把一个点涂黑就多这么多的贡献，最后根据最优解的黑点个数去调整这个偏移量。

易证一个点要是涂黑，则它子树内所有点都要涂黑。因为如果子树里面有一个白点，那把那个点涂黑然后把这个点涂白一点更优。

然后就可以 dp 了。一个点有两种决策：涂黑，不涂黑。

code：
```cpp
#include<vector>
#include<cstring>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=2e5+5;
int n,k;
vector<int> g[maxn];
int fa[maxn],dep[maxn],size[maxn];
void dfs(int u){
	dep[u]=dep[fa[u]]+1;
	size[u]=1;
	for(int i=0;i<(int)g[u].size();i++){
		int v=g[u][i];
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs(v);
		size[u]+=size[v];
	}
}
double l,r,mid;
bool c[maxn];
double dp(int u){
	double res=0;
	for(int i=0;i<(int)g[u].size();i++){
		int v=g[u][i];
		if(v==fa[u]) continue;
		res+=dp(v);
	}
	if(res<size[u]*(dep[u]-1+mid)){
		c[u]=1;
		return size[u]*(dep[u]-1+mid);
	}
	else{
		c[u]=0;
		return res;
	}
}
int count(int u){
	if(c[u]) return size[u];
	int cnt=0;
	for(int i=0;i<(int)g[u].size();i++){
		int v=g[u][i];
		if(v==fa[u]) continue;
		cnt+=count(v);
	}
	return cnt;
}
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    k=readint();
    for(int i=1;i<n;i++){
    	int u,v;
    	u=readint();
    	v=readint();
    	g[u].push_back(v);
    	g[v].push_back(u);
	}
	dfs(1);
	l=-n;
	r=n;
	while(r-l>1e-5){
		mid=l+(r-l)/2;
		memset(c,0,sizeof(c));
		dp(1);
		if(count(1)<k) l=mid;
		else r=mid;
	}
	printf("%.f\n",dp(1)-r*k);
    return 0;
}
```
要是有人把这代码交上去我也拦不住对吧。

就是因为这份代码，我 fst 了，然后下分了。

是的这里写的是实数的 wqs 二分，这题卡精度……

解决办法两个，要不然把精度改成 `1e-6`，要不然在二分后面加个 `mid=r`。

另外某个验题人跟我说他是用树剖做的？不知道怎么做。

---

## 作者：H6_6Q (赞：4)

### 题目翻译：      
有一棵 $n$ 个节点的树 ( $n \le 2 \times 10^5 $ )，现在要求选出 $k$ 个节点，使得这 $k$ 个节点到根节点的最短路径中，每个节点经过的剩余 $n-k$ 个节点的数量之和最大。
### 思路：      
**注：**     
- 这里所说的 $u$ 的子树不包含 $u$ 本身。       
- $dep$ 指深度，$siz$ 指子树大小（包含子树的根）。       

先 dfs 一遍，把树的深度和子树大小处理出来，然后贪心。   
如果直接按照深度或者子树大小排序都是错的，这是因为新选一个节点可能会导致答案减小。所以我们需要一种更优的排序策略。       
因为选 $u$ 答案增加 $dep_u-1$，而选 $u$ 子树中的节点增加的值一定大于 $dep_u-1$。而且选 $u$ 子树中的节点，减少的值一定小于等于选 $u$ 节点。所以如果要选 $u$ 节点，那么 $u$ 结点的子树一定都选完了。  
所以我们排序的时候就认为当选 $u$ 时，它的子树都已经被选完。      
所以选节点 $u$ 会增加的值就是：
- $(dep_u-1) \times siz_u$ 

选节点 $u$ 会减少的值就是：    
- $(siz_u-1)\times dep_u$     

选节点 $u$ 对整个答案的贡献就是：
- $(dep_u-1)\times siz_u-(siz_u-1) \times dep_u$ 

按照这个贡献排序，选前 $k$ 名即可。    
答案再 dfs 一遍就可以得到。
### Code:
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<bitset>
#include<cmath>
#include<queue>
#include<map>
#include<set>
#define LL long long

using namespace std;

LL read()
{
	LL ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}

const LL N=1e6+5;
LL n,k,is[N],sum[N],ans;

struct Edge
{
	LL v,ne;
}e[N];
LL head[N],tot;

struct Node
{
	LL dep,x,siz;
    // 分别代表 深度 ，编号 ，子树大小
	bool operator < (const Node &x)const
	{
		return ((x.dep-1)*x.siz-x.dep*(x.siz-1))<((dep-1)*siz-dep*(siz-1));
        // 这是上面推出的排序策略
	}
}node[N];

inline void add(LL u,LL v);
void dfs1(LL u,LL fa);
void dfs2(LL u,LL fa);

int main()
{
	n=read();k=read();
	for(LL i=1;i<=n-1;++i)
	{
		LL u=read(),v=read();
		add(u,v);
		add(v,u);
        // 注意无向边
	}
	dfs1(1,0);
	sort(node+1,node+1+n);
	for(LL i=1;i<=k;++i)
    // 选出前 k 个节点
		is[node[i].x]=1;
	dfs2(1,0);
	printf("%lld",ans);
	return 0;
}

inline void add(LL u,LL v)
{
	e[++tot]=(Edge){v,head[u]};
	head[u]=tot;
}

void dfs1(LL u,LL fa)
// 第一遍 dfs 预处理出每个节点的深度与子树大小
{
	node[u].dep=node[fa].dep+1;
	node[u].siz=1;
	node[u].x=u;
	for(LL i=head[u];i;i=e[i].ne)
	{
		LL v=e[i].v;
		if(v==fa)
			continue;
		dfs1(v,u);
		node[u].siz+=node[v].siz;
	}
}

void dfs2(LL u,LL fa)
// 第二遍 dfs 利用前缀和求答案
{
	if(!is[u])
		sum[u]++;
	else
		ans+=sum[u];
	for(LL i=head[u];i;i=e[i].ne)
	{
		LL v=e[i].v;
		if(v==fa)
			continue;
		sum[v]=sum[u];
		dfs2(v,u);
	}
}
```


---

## 作者：无尽星空 (赞：2)

## 序
1.一开始想树形DP，但是没搞成

2.蒟蒻的第一篇题解
## 前传
先引入几个定理：

1.如果是一条链且选了0个点，那么一定选另一端（显然的）

![](https://cdn.luogu.com.cn/upload/image_hosting/huj7kgh8.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

2.如果是一条链且选了1个点，那么一定选择已经选了的点的父亲（为了最优答案）

3.不会出现没有选择某个点的父亲却选择了父亲的父亲的情况（否则违背定理2）

所以，由定理1.2，我们可以推出定理4：如果选了某个点，那么它的所有儿子必定已经被选了

怎样理解呢？举个~~栗子~~例子，看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/m9lnk80x.png?x-oss-process=image/resize,m_lfit,h_170,w_225)（1号点是Root）

图中3号点没选，那么对于它的儿子4号点（or 5号点），出现了违背定理3的情况，所以定理4成立
## 正传
好了我们开始解题

设dep[i]表示i点的深度（dep[1]=1),son[i]表示i点的儿子数

假设我们选到了i号点，那么i号点对答案的贡献分两部分：

1.增量：dep[i]-1(选择了i,那么目前为止i的所有祖先都没选（否则违反定理3），祖先数为dep[i]-1）

2.减量：son[i](选择了i，那么对于它的儿子们，选择它的儿子们时没有选i，现在选了i，那么每个儿子的贡献-1，根据定理4可知儿子被全部选择，即有son[i]个儿子被选）

所以选i对答案的贡献为dep[i]-1-son[i]

那么我们就可以~~愉快地~~贪心了,我们对所有点的贡献从大到小排序，选前k大的就可以了

代码：（蒟蒻喜欢压行，不喜勿喷）
```
#include<bits/stdc++.h>
#define R register
using namespace std;
const int N=200005;
int n,h[N],nx[N*2],to[N*2],cnt,son[N],dep[N],k;
long long ans;
priority_queue<int> q;  //优先队列排序
void add(int &x,int &y) {to[++cnt]=y;nx[cnt]=h[x];h[x]=cnt;}//链式前向星加边
inline int read()    //快读
{
	int s=0;char c=getchar();
	while(!isdigit(c))  c=getchar();
	while(isdigit(c))  s=(s<<3)+(s<<1)+(c^48),c=getchar();
	return s;
}
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	for(R int i=h[x];i;i=nx[i])
		if(to[i]!=fa)  dfs(to[i],x),son[x]+=son[to[i]];
	q.push(dep[fa]-son[x]);    //dep[fa]=dep[x]-1,打dep[fa]省事
	son[x]++;    //son[x]之前表示x的儿子数，不包括自己，但返回到fa时还要用到自己，所以++
}
int main()
{
	n=read();k=read();
	for(R int i=1;i<n;i++)
	{
		int a=read(),b=read();
		add(a,b);add(b,a);
	}
	dfs(1,0);
	while(k--)  ans+=q.top(),q.pop();//选前k大的贡献
	cout<<ans;
	return 0;       //完美落幕
}
```
[评测记录](https://www.luogu.com.cn/record/33033968)，2.38s，还可以吧

---

## 作者：1saunoya (赞：2)

~~最开始看错题了，zbl~~

~~题意自行去看.jpg~~


我们发现你选一个叶子结点的贡献是 $dep_i$，如果你选一个非叶子结点，那么儿子必须都要选，所以非叶子结点的贡献是 $dep_i - sz_i + 1$。

然后排个序，选最大的 $k$ 个就完事了。

```cpp

// powered by c++11
// by Isaunoya
#include <bits/stdc++.h>

#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)

using namespace std;
using db = double;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

#define pii pair<int, int>
#define fir first
#define sec second

template <class T>

void cmax(T& x, const T& y) {
  if (x < y) x = y;
}

template <class T>

void cmin(T& x, const T& y) {
  if (x > y) x = y;
}

#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back

template <class T>

void sort(vector<T>& v) {
  sort(all(v));
}

template <class T>

void reverse(vector<T>& v) {
  reverse(all(v));
}

template <class T>

void unique(vector<T>& v) {
  sort(all(v)), v.erase(unique(all(v)), v.end());
}

void reverse(string& s) { reverse(s.begin(), s.end()); }

const int io_size = 1 << 23 | 233;
const int io_limit = 1 << 22;
struct io_in {
  char ch;
#ifndef __WIN64
  char getchar() {
    static char buf[io_size], *p1 = buf, *p2 = buf;

    return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, io_size, stdin), p1 == p2) ? EOF : *p1++;
  }
#endif
  io_in& operator>>(char& c) {
    for (c = getchar(); isspace(c); c = getchar());

    return *this;
  }
  io_in& operator>>(string& s) {
    for (s.clear(); isspace(ch = getchar());)
      ;

    if (!~ch) return *this;

    for (s = ch; !isspace(ch = getchar()) && ~ch; s += ch)
      ;

    return *this;
  }

  io_in& operator>>(char* str) {
    char* cur = str;
    while (*cur) *cur++ = 0;

    for (cur = str; isspace(ch = getchar());)
      ;
    if (!~ch) return *this;

    for (*cur = ch; !isspace(ch = getchar()) && ~ch; *++cur = ch)
      ;

    return *++cur = 0, *this;
  }

  template <class T>

  void read(T& x) {
    bool f = 0;
    while ((ch = getchar()) < 48 && ~ch) f ^= (ch == 45);

    x = ~ch ? (ch ^ 48) : 0;
    while ((ch = getchar()) > 47) x = x * 10 + (ch ^ 48);
    x = f ? -x : x;
  }

  io_in& operator>>(int& x) { return read(x), *this; }

  io_in& operator>>(ll& x) { return read(x), *this; }

  io_in& operator>>(uint& x) { return read(x), *this; }

  io_in& operator>>(ull& x) { return read(x), *this; }

  io_in& operator>>(db& x) {
    read(x);
    bool f = x < 0;
    x = f ? -x : x;
    if (ch ^ '.') return *this;

    double d = 0.1;
    while ((ch = getchar()) > 47) x += d * (ch ^ 48), d *= .1;
    return x = f ? -x : x, *this;
  }
} in;

struct io_out {
  char buf[io_size], *s = buf;
  int pw[233], st[233];

  io_out() {
    set(7);
    rep(i, pw[0] = 1, 9) pw[i] = pw[i - 1] * 10;
  }

  ~io_out() { flush(); }

  void io_chk() {
    if (s - buf > io_limit) flush();
  }

  void flush() { fwrite(buf, 1, s - buf, stdout), fflush(stdout), s = buf; }

  io_out& operator<<(char c) { return *s++ = c, *this; }

  io_out& operator<<(string str) {
    for (char c : str) *s++ = c;
    return io_chk(), *this;
  }

  io_out& operator<<(char* str) {
    char* cur = str;
    while (*cur) *s++ = *cur++;
    return io_chk(), *this;
  }

  template <class T>

  void write(T x) {
    if (x < 0) *s++ = '-', x = -x;

    do {
      st[++st[0]] = x % 10, x /= 10;
    } while (x);

    while (st[0]) *s++ = st[st[0]--] ^ 48;
  }

  io_out& operator<<(int x) { return write(x), io_chk(), *this; }

  io_out& operator<<(ll x) { return write(x), io_chk(), *this; }

  io_out& operator<<(uint x) { return write(x), io_chk(), *this; }

  io_out& operator<<(ull x) { return write(x), io_chk(), *this; }

  int len, lft, rig;

  void set(int _length) { len = _length; }

  io_out& operator<<(db x) {
    bool f = x < 0;
    x = f ? -x : x, lft = x, rig = 1. * (x - lft) * pw[len];
    return write(f ? -lft : lft), *s++ = '.', write(rig), io_chk(), *this;
  }
} out;
#define int long long

template <int sz, int mod>

struct math_t {
	math_t() {
    fac.resize(sz + 1), ifac.resize(sz + 1);
    rep(i, fac[0] = 1, sz) fac[i] = fac[i - 1] * i % mod;

    ifac[sz] = inv(fac[sz]);
    Rep(i, sz - 1, 0) ifac[i] = ifac[i + 1] * (i + 1) % mod;
  }

  vector<int> fac, ifac;

  int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = x * x % mod)
      if (y & 1) ans = ans * x % mod;
    return ans;
  }

  int inv(int x) { return qpow(x, mod - 2); }

  int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
  }
};

int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
int lcm(int x, int y) { return x * y / gcd(x, y); }


int n;
const int maxn = 2e5 + 52;
vector < int > g[maxn]; 

int a[maxn], sz[maxn];

void dfs(int u, int fa) {
	sz[u] = 1;
	for(int v : g[u]) {
		if(v ^ fa) {
			a[v] = a[u] + 1;
			dfs(v, u);
			sz[u] += sz[v];
		}
	}
	a[u] -= sz[u] - 1;
}

signed main() {
  // code begin.
  int k;
	in >> n >> k;
	rep(i , 2 , n) {
		int u ,v;
		in >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1, 0);
	sort(a + 1 , a + n + 1) ;
	int ans = 0;
	for(int i = n ; i > n - k ; i --) ans += a[i];
	out << ans << '\n';
  return 0;
  // code end.
}
```

---

## 作者：Doubeecat (赞：2)

## 题目链接：

[CF1336A/CF1337C](<https://codeforces.ml/contest/1337/problem/C>)

## 题意：
有一个有 $n$ 个点的树，以 1 为根，你可以选择 $k$ 个节点，使得这 $k$ 个节点到 1 节点的最短路径中经过的非选择的点最多。

## 思路：
先约定：  
$siz_v$ 为以 $v$ 为根的子树大小，当 $v$ 为叶子节点时，$siz_v = 1$。。  
$dep_v$ 为从根到 $v$ 的最短路径长度（即深度）。  

首先我们可以发现，这里每选择一个点是会对它的子树造成影响。  
例如这里：  
![](https://cdn.luogu.com.cn/upload/image_hosting/52wr03fh.png)  
如果我们已经选择了 4,5，那么如果再选择 2， 4,5 到根节点的权值就会各 -1。  
所以我们不止要简单的计算深度最大的，而且要计算它的子树大小最小的。  
因此，我们设一个点的贡献为 $f_v$，$f_v = dep_v - siz_v$,最后对 $f_i$ 排序求出最小的 $k$ 个值相加即可。    
显然对于 $dep_i$ 和 $siz_i$ 我们可以通过一遍 DFS 求出来   
```cpp
void dfs1(int s,int f) {
	a[s].dep = a[f].dep+1,a[s].siz = 1;
	for (int i = hd[s];i;i = nxt[i]) {
		int v = to[i];
		if (v == f) continue;
		dfs1(v,s);
		a[s].siz += a[v].siz;
	}
}
```
之后就是简单的计算 $f_i$ 的过程了，不再多说。
## 代码
```cpp
//本代码是赛时代码，可能有些变量名称不一样，但大体思路一致。
#include <bits/stdc++.h>
using namespace std;
#define int long long//答案会超出int的范围
#define ri register int

inline int read() {
	char v = getchar();int x = 0,f = 1;
	while (!isdigit(v)) {if (v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {x = x * 10 + v - 48;v = getchar();}
	return x * f;
}

const int N = 500001;
const int M = 500001;

int to[M],hd[N],nxt[M],tot;

inline void add(int u,int v) {to[++tot] = v;nxt[tot] = hd[u];hd[u] = tot;}
inline void addedge(int u,int v) {add(u,v),add(v,u);}

struct node {
	int dep,siz;
}a[N];
//a[i].dep 存的是 dep[i] a[i].siz 存的是 siz[i] 
inline bool cmp(node a,node b) {
	return (a.dep-a.siz)>(b.dep-b.siz);
}
//按照dep[i] - siz[i]（也就是f[i]）排序
void dfs1(int s,int f) {
	a[s].dep = a[f].dep+1,a[s].siz = 1;//计算dep和siz
	for (int i = hd[s];i;i = nxt[i]) {
		int v = to[i];
		if (v == f) continue;
		dfs1(v,s);
		a[s].siz += a[v].siz;
	}
}

int n,k,ans;

signed main() {
	n = read(),k = read();
	for (int i = 1;i < n;++i) {
		int x = read(),y = read();
		addedge(x,y);
	}
	a[0].dep = 0,a[0].siz = 0;
	dfs1(1,0);
	sort(a+1,a+1+n,cmp);//排序
	for (int i = 1;i <= k;++i) {
		ans += (a[i].dep - a[i].siz);
	}//选前k个
	cout << ans;
	return 0;
}
```

---

## 作者：_Revenge_ (赞：1)

### 题目简化和分析：

明确一点这是一棵树。    
为了保证每个工业城市的设置效益最大，应该设在最深的节点。   
从深到浅，可以使用**优先队列**去实现。   

设置一个的价值为 $dep_u-siz_u-1$。

关于作者一开始想反了，设置旅游城市，虽然可以做，但非常麻烦，于是看了别人大佬思路才明白。   
错误原因在于，有可能儿子先设置了，而他的祖先却没有，会导致重复计算。    
大家引以为戒。   

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=4e5+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

int n,k;
struct edge{
	int to,next;
}e[N];
int head[N],cnt;
void add_edge(int u,int v){
	++cnt;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
priority_queue<int>q;
int siz[N],dep[N];
void dfs(int u,int p){
	dep[u]=dep[p]+1;
	for(int i=head[u];i;i=e[i].next){
		int y=e[i].to;
		if(y==p) continue;
		dfs(y,u);
		siz[u]+=siz[y];
	}
	q.push(dep[u]-siz[u]-1);
	++siz[u];
}
int main()
{
	n=read(),k=read();
	for(int i=1;i<n;++i){
		int u,v;
		u=read(),v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	ll ans=0;
	while(k){
		--k;
		ans+=q.top();
		q.pop();
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：Tenshi (赞：1)

题解区似乎没有和我一样用类似于拓扑序的东西搞的 qwq。

非常直观的想法就是从叶开始向上取，这样就能让收益最大化。

但向上取的顺序如何呢？

我们采取贪心的思想，将每个当前度数为 $1$ 的节点入优先队列，优先队列存储的元素有两个属性：价值与节点编号。价值就是当前点 $u$ 的深度减去 $u$ 所在子树的大小，然后当然是价值大的优先级高。

剩下的工作就是跑一遍 bfs，类似于拓扑序一样将度数为 $1$ 的点入队然后更新其它点度数就做完了。

```cpp
// Problem: A. Linova and Kingdom
// Contest: Codeforces - Codeforces Round #635 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1336/A
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)

using pii = pair<int, int>;
using ll = long long;

inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=2e5+5, M=N<<1;

struct Edge{
	int to, next;
}e[M];

int h[N], tot;

void add(int u, int v){
	e[tot].to=v, e[tot].next=h[u], h[u]=tot++;
}

int n, k;

int deg[N], d[N], sz[N];

void dfs(int u, int fa, int dep){
	sz[u]=1, d[u]=dep;
	for(int i=h[u]; ~i; i=e[i].next){
		int go=e[i].to;
		if(go==fa) continue;
		dfs(go, u, dep+1);
		sz[u]+=sz[go];
	}
}

struct Node{
	int w, u;
	bool operator < (const Node &o)const{
		return w<o.w;
	}
};

priority_queue<Node> q; 

int main(){
	memset(h, -1, sizeof h);
	cin>>n>>k;
	rep(i,1,n-1){
		int u, v; read(u), read(v);
		add(u, v), add(v, u);
		deg[u]++, deg[v]++;
	}
	
	dfs(1, -1, 1);
	
	rep(i,2,n) if(deg[i]==1) q.push({d[i]-sz[i], i});
	
	ll res=0;
	while(q.size()){
		auto t=q.top(); q.pop();
		int u=t.u;
		if(k) res+=t.w, k--;
		for(int i=h[u]; ~i; i=e[i].next){
			int go=e[i].to;
			if(--deg[go]==1) q.push({d[go]-sz[go], go}); 
		}
	}
	
	cout<<res<<endl;
	
	return 0;
}
```

---

## 作者：nao_nao (赞：1)

#### 题意：

给定一棵树，取其中 k 个点做上标记。求这 k 个点到节点 1 的路径上未被标记的点的个数和。

#### 题解：

我们以节点 1 为根，那么各个点到节点 1 的路径就可以看为各个节点到根节点的路径。

我们首先贪心：我们发现在这棵树上，选取离根节点最远的点做上标记常常是答案（其实并不是），我们观察样例的两个图可以显然发现这个结论。但是这个结论并不是完美的。

我们发现，如果我们选取了节点 u 做上标记，那么为了得到最优解，我们一定会选取以 u 为根的子树中的所有点。

我们考虑选取每一个点对答案造成的贡献：对于选 u 节点，会使答案增加 u 到根的路径上的节点数，同时，会使以 u 为子树中除根节点外，对答案的贡献减少一 （因为u被打上标记了嘛） ，贪心可知，若选 u ，必选 u 的子树，因此可以把这部分贡献算在 u 上，即为答案减少 $(siz[u]-1)$ 其中 $siz[u]$ 为以 u 为根的子树的大小。 

所以每一个点 u 对答案造成的贡献可表示为：$ans[u] = dis[u]-siz[u]+1$,其中 dis 为点 u 的深度，可以用来算点 u 到根节点路径上的节点个数。

我们将所有的贡献排序，再次发现 u 子树中的其他节点贡献真的都比 u 大，所以上面的发现显然正确。

code：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int read() {为了便于阅读代码我把快读略掉吧}
const int N=1e6+7;
int n,k;
int t[N];
int head[N],go[N],nxt[N],cnt;
int fa[N],ans[N],siz[N];
struct node{
	int id,dis;
	friend bool operator < (node a,node b) {return a.dis < b.dis;}
}arr[N];
void dfs(int u)//预处理出每一个点的贡献
{
	arr[u] = (node){u,arr[fa[u]].dis+1};
	siz[u] = 1;
	for(int e = head[u];e;e= nxt[e]){
		int v = go[e];
		if(v == fa[u]) continue;
		fa[v] = u;
		dfs(v); 
		siz[u] += siz[v];
	}
	arr[u].dis = arr[u].dis-siz[u]+1;
}
void add(int u,int v)
{
	go[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}

int main()
{
	n = read(),k = read();
	for(int i = 1;i < n;i ++){
		int u = read(),v = read();
		add(u,v);add(v,u);
	}
	arr[0] = (node){0,-1};
	dfs(1);long long sum = 0;
	sort(arr+1,arr+1+n);
	for(int i = n-k+1;i <= n;i ++){//这个写法很难看，我发现了qwq
		sum += arr[i].dis;
	}
	printf("%lld",sum);
	return 0;
}
```

最后送给大家：十年oi一场空，不开long long……

---

## 作者：404Not_Found (赞：0)

**引理**：如果一个点被标记，则它的子树内的所有节点都要标记上。

**证明**：如果它有子孙没有被标记的话，那么只标记那个节点显然更优。

考虑标记一个点给答案带来的贡献。它本身的贡献是 $\operatorname{dep}_u$，另外减去子树带来的代价，即 $\operatorname{siz}_u$，所以每个节点给答案带来的代价为 $\operatorname{dep}_u-\operatorname{siz}_u$，选最大的 $k$ 个即可。

时间复杂度：$\mathcal{O}(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
#define LL long long
struct edge{
	int to,nxt;
} e[MAXN<<1];
int head[MAXN],cnt,n,k,siz[MAXN],dep[MAXN],a[MAXN];LL ans;
inline void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int u,int fa)
{
	siz[u]=1; dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v]; 
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v); add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) a[i]=dep[i]-siz[i];
	sort(a+1,a+n+1);
	for(int i=n;i>=n-k+1;i--) ans+=1ll*a[i];
	printf("%lld\n",ans);
	return 0; 
}
```

---

## 作者：huayucaiji (赞：0)

首先我们发现我们要找到深度尽可能大的节点，这样对答案的贡献较大，用堆维护，但是我们来看样例1：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/550bbb250626ee83a75f7874e99bb74967e95572.png)

如果我们找到了按顺序找到了 $5,6,7,4$ 四个点，那么答案就是 $6$，与样例不符，~~没有体现样例的严密性，准确性，科学性~~。所以我们发现我们找到的点，尽量要分布在不同链上，这样对答案的减少最小。

我们下面来讨论如何解决这个问题：

~~这个题珂以用树剖做，但是我懒，还是用了贪心~~

### 树剖做法

先说树剖的做法，代码不给了。上面提到了，我们发现我们找到的点，尽量要分布在不同链上，这样对答案的减少最小。自然想到维护链的工具：树剖。我们找到一个点后，对其所在的重链或长链打上标记，下次优先找其他链上的点。代码可以自己写下。

### 贪心做法

我们再来看看贪心。我们发现，一个节点对于答案的贡献是它到根节点的深度减去以它为根的子树的工业城市与它的距离之和。但是由于我们贪心，所以我们肯定在选这个节点前，它的子树全被选过了（因为它的子树里每一个节点，深度都比它大，它们的贡献也比这个节点大），那么简而言之，一个节点的**新**贡献是这样的：
$$dep_u-size_u$$

它的每一个子树成员都因为它的出现导致答案减去 $1$。所以我们在一遍 dfs 预处理完所有的基本信息后，用堆来维护即可。

这个可能太抽象，我们来模拟一下一组数据：

```plain
7 5
1 2
1 3
1 4
3 5
3 6
4 7
```

图和样例1一样：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/550bbb250626ee83a75f7874e99bb74967e95572.png)

我们前面的还是选择了 $5,6,7$。现在堆里有 $3$ 个节点：$2,3,4$ 如果我们分别选择了它们，则对答案的**新**贡献分别是 $1,-1,0$ （因为其子树里的所有节点都会的答案值都要减 $1$），那么我们就选 $2$ 号节点。然后把 $1$ 放进去。最后不难发现我们改选择 $4$ 作为下一个选择的节点，因为他的**新**贡献值最大（虽然是负的，但是不管如何，都要选满 $k$ 个）。

是不是理解了呢，应该很清晰易懂了吧~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=2e5+10;

int n,h[maxn],cnt,k,dep[maxn],ans,fa[maxn],size[maxn];
bool ind[maxn],ex[maxn];
priority_queue<pair<int,int> > q;

struct edge {
	int v,next;
}e[maxn<<1];

void addedge(int u,int v) {
	e[++cnt].v=v;
	e[cnt].next=h[u];
	h[u]=cnt;
}

void dfs(int u,int father) {
	int num=0;
	size[u]=1;
	for(int i=h[u];i;i=e[i].next) {
		int v=e[i].v;
		if(v!=father) {
			num++;
			dep[v]=dep[u]+1;
			fa[v]=u;
			dfs(v,u);
			size[u]+=size[v];
		}
	}
	if(!num) {
		q.push(make_pair(dep[u],u));
		ex[u]=1;
	}
}

void cfs(int u,int fa,int num) {
	for(int i=h[u];i;i=e[i].next) {
		int v=e[i].v;
		if(v!=fa) {
			cfs(v,u,num+1-ind[u]);
		}
	}
	if(ind[u])
		ans+=num;
}

signed main() {
	
	n=read();k=read();
	for(int i=1;i<n;i++) {
		int a=read(),b=read();
		addedge(a,b);
		addedge(b,a);
	}
	dfs(1,0);
	for(int i=1;i<=k;i++) {
		pair<int,int> pr=q.top();
		q.pop();
		ind[pr.second]=1;
		if(!ex[fa[pr.second]]) {
			q.push(make_pair(dep[fa[pr.second]]-size[fa[pr.second]]+1,fa[pr.second]));
			ex[fa[pr.second]]=1;
		}
	}
	cfs(1,0,0);
	cout<<ans<<endl;
	return 0;
}


```

---

## 作者：do_while_true (赞：0)

贪心，选深度更深的节点肯定比选深度更浅的节点更优，也就是我们选一个节点，如果想让答案更优，它的子树也一定是被选了的。

所以我们可以根据这个特点算出每一个点对答案的贡献。当一个点是叶子节点，显然选它对答案的贡献就是这个节点的深度。如果不是的话，首先它会对答案加上它的深度，然后因为它被标记成工业城市了，它的子树对答案的贡献也会-1，我们干脆把这个负的贡献强加到这个父节点身上。

所以我们设这个节点的深度为 $depth_i$，子树大小为 $siz_i$，这个节点对答案的贡献就为 $depth_i-siz_i$。我们算出所有的节点对答案的贡献，然后排序，取前 $k$ 个即可。

我用的 $bfs$ 求深度， $dfs$ 求子树大小，虽然里面实现过程有点麻烦，不过写 $bfs$ 写炸的小伙伴可以来看看我的代码。

## $\mathcal{Code}:$

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
int n,k,cnt[200001],fa[200001];
ll ans,depth[200001],fin[200001],siz[200001];
vector<int>go[200001];
bool vis[200001],vis2[200001];
struct queue{
	int head,tail,a[300001];
    void push(int x){a[++tail] = x;}
    int front(){return a[head];}
    void pop(){head++;}
    int empty(){return head>tail?1:0;}
}q;//手写队列
void add(int x,int y)
{
	go[x].push_back(y);
	go[y].push_back(x);
	cnt[x]++;
	cnt[y]++;//vector存树
}
bool cmp(ll x,ll y)
{
	return x>y;
}
void dfs(int x)
{
	siz[x]=1;//这里的siz大小是包括自身的
	for(int i=0;i<cnt[x];i++)
	{
		if(!vis2[go[x][i]])
		{
			vis2[go[x][i]]=1;
			dfs(go[x][i]);
			siz[x]+=siz[go[x][i]];
		}
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	vis2[1]=1;
	dfs(1);
	q.tail=-1;
	q.push(1);
	depth[1]=0;
	vis[1]=1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=0;i<cnt[x];i++)
			if(!vis[go[x][i]])
			{
				q.push(go[x][i]);
				vis[go[x][i]]=1;
				depth[go[x][i]]=depth[x]+1;
				fa[go[x][i]]=x;
			}
	}
	for(int i=1;i<=n;i++){
		fin[i]=depth[i];
  		//fin[i]是i对答案的贡献
		for(int j=0;j<cnt[i];j++)
			if(go[i][j]!=fa[i])
				fin[i]-=siz[go[i][j]];
	}
	sort(fin+1,fin+n+1,cmp);
	for(int i=1;i<=k;i++)
		ans+=fin[i];
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Vocalise (赞：0)

这里提供一个近乎暴力的做法。

我们考虑贪心，每次选取一个对当前状态贡献最大的点。

这里可以考虑堆维护，初始时当然是选深度最大的点。但是如果一个点的祖先被选了，它的贡献就应该 $-1$；如果一个点需要选，它的祖先也已经被选了，它的贡献也应该少一个。这里该怎么办呢？

于是我们考虑把一个负的贡献算在它的祖先（子树）身上。

然后这就成为了一个全局取最小值，一个点到它的祖先路径修改加上子树修改的问题了。

可以直接树剖。

于是147行可以解决问题。但是笔者太菜，比赛时没有A，如何呢？

第一是没有考虑到接近 $-k$ 的负贡献，因而在将一个使用过的点重置只将它赋成了 $-5$。

第二是只考虑了到根的路径上的修改，没有考虑子树内的修改。其实这里笔者也没有十分搞清楚，或者因为是个歪解，就没有卡？但是不加子树修改会在 $6$ 号点WA是确凿的。

这里就请大家多多指教了。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
	return x * f;
}

typedef long long ll;
const int MAXN = 200001;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int u;
	Edge *nxt;
};

Edge *adj[MAXN];

void ins(int v,int u) {
	Edge *e = new Edge;
	e -> u = u;
	e -> nxt = adj[v];
	adj[v] = e;
}

int n,k;
int fa[MAXN],dep[MAXN],size[MAXN],son[MAXN];
int top[MAXN],rev[MAXN],id[MAXN],tot;

#define lc(k) k << 1
#define rc(k) k << 1 | 1

struct Node
{
	int id; ll max; // id on segment_tree
	friend bool operator < (const Node &x,const Node &y) { return x.max < y.max; }
};

Node d[MAXN << 2];
int add[MAXN << 2];

void pushup(int k) { d[k] = std::max(d[lc(k)],d[rc(k)]); }

void pushdown(int k) {
	if(!add[k]) return;
	d[lc(k)].max += add[k], add[lc(k)] += add[k];
	d[rc(k)].max += add[k], add[rc(k)] += add[k];
	add[k] = 0;
}

void Build(int k,int l,int r) {
	if(l == r) {
		d[k].id = l, d[k].max = dep[rev[l]];
		return;
	}
	int mid = (l + r) >> 1;
	Build(lc(k),l,mid);
	Build(rc(k),mid + 1,r);
	pushup(k);
	return;
}

void Update(int k,int l,int r,int x,int y) {
	if(l > y || r < x) return;
	if(l >= x && r <= y) {
		d[k].max--, add[k]--;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(k);
	Update(lc(k),l,mid,x,y);
	Update(rc(k),mid + 1,r,x,y);
	pushup(k);
	return;
}

void Dfs1(int v,int f) {
	fa[v] = f, size[v] = 1;
	for(Edge *i = adj[v];i;i = i -> nxt) {
		int u = i -> u;
		if(u == f) continue;
		dep[u] = dep[v] + 1;
		Dfs1(u,v);
		size[v] += size[u];
		if(size[u] > size[son[v]]) son[v] = u;
	}
	return;
}

void Dfs2(int v,int t) {
	top[v] = t;
	id[v] = ++tot, rev[tot] = v;
	if(!son[v]) return;
	Dfs2(son[v],t);
	for(Edge *i = adj[v];i;i = i -> nxt) {
		int u = i -> u;
		if(u == fa[v] || u == son[v]) continue;
		Dfs2(u,u);
	}
	return;
}

void Reset(int k,int l,int r,int x) {
	if(l == r) {
		d[k].max = -INF;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) Reset(lc(k),l,mid,x);
	else Reset(rc(k),mid + 1,r,x);
	pushup(k);
	return;
}

int main() {
	n = read(), k = read();
	for(int i = 2,v,u;i <= n;i++) {
		v = read(), u = read();
		ins(v,u); ins(u,v);
	}
	Dfs1(1,0);
	Dfs2(1,1);
	Build(1,1,n);
	ll ans = 0; 
	while(k--) {
		Node v = d[1];
		ans += v.max;
		// std::printf("id on tree = %d weight = %d\n",rev[v.id],v.max);
		// std::printf("id on seg = %d\n",rev[v.id]);
		// std::printf("ans = %lld\n",ans);
		Reset(1,1,n,v.id);
		int u = rev[v.id];
		Update(1,1,n,id[u],id[u] + size[u] - 1);
		while(u != 0) {
			Update(1,1,n,id[top[u]],id[u]);
			u = fa[top[u]];
		}
	}
	std::printf("%lld\n",ans);
	return 0;
}

```

---

