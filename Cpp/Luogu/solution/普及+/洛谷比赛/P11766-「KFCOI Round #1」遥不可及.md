# 「KFCOI Round #1」遥不可及

## 题目背景

你未曾料到，烟火散尽，余烬渐冷，那一转身的轻易告别，却成了永远的诀别。

但是，你决意追寻她的身影，哪怕在这永无止境的重逢梦中。

## 题目描述

 $n$ 个地点构成了复杂的关系网。

但是现在这些地点复杂的路线关系被简化成为了**一棵树**。


你从每个点均出发一次，当你从点 $u$ 出发时，你会找到这个点能到达的所有最远点 $v_1,v_2,\cdots v_k$，并对每个 $v_i$，将 $u$ 到 $v_i$ 简单路径上的点权值加 $1$。


询问最终所有地点的权值总和。

## 说明/提示

样例一解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/6viyvcu1.png)

从 $1$ 出发，最远距离为 $3$，故到达 $5$ 和 $6$，各点权为 $[2,2,0,2,1,1]$；

从 $2$ 出发，最远距离为 $2$，故到达 $5$ 和 $6$，各点权为 $[2,4,0,4,2,2]$；

从 $3$ 出发，最远距离为 $3$，故到达 $5$ 和 $6$，各点权为 $[2,6,2,6,3,3]$；

从 $4$ 出发，最远距离为 $2$，故到达 $1$ 和 $3$，各点权为 $[3,8,3,8,3,3]$；

从 $5$ 出发，最远距离为 $3$，故到达 $1$ 和 $3$，各点权为 $[4,10,4,10,5,3]$；

从 $6$ 出发，最远距离为 $3$，故到达 $1$ 和 $3$，各点权为 $[5,12,5,12,5,5]$。

所以最终各点权和为 $44$。

（黄色为 $1$ 出发的路径；红色为 $2$；蓝色为 $3$；绿色为 $4$；青色为 $5$；紫色为 $6$。）

***

**本题采用捆绑测试**。

- Subtask 1（20 points，1 s）：$1\le n \le 5000$。
- Subtask 2（40 points，1 s）：$1\le n \le 5\times 10^5$。
- Subtask 3（10 points，1 s）：树的形态为链。
- Subtask 4（10 points，2 s）：树的形态为菊花。
- Subtask 5（20 points，2 s）：无特殊限制。

对于所有测试数据，$1\le n\le 10^6$，$1\le w_i \le 10^9$，$1\le a_i \le n$，$1 \le b_i\le n$。


本题输入数据较大，请使用较快的读入方式和实现方式。请注意本题的栈空间。

## 样例 #1

### 输入

```
6
1 2 1
2 3 1
2 4 1
4 5 1
4 6 1```

### 输出

```
44```

## 样例 #2

### 输入

```
10
6 10 3
9 5 4
6 7 10
6 5 9
10 4 8
5 1 9
8 10 10
2 7 1
3 1 3```

### 输出

```
52```

# 题解

## 作者：koukilee (赞：3)

> 是啊，你是小怪兽，可小怪兽也有小怪兽的好朋友，孤独的小怪兽们害怕得靠在一起，但如果正义的奥特曼要来杀你，我就帮你把正义的奥特曼杀死。可是我答应了，却没有做到。

这里是出题人的题解。

## 题目大意

给定一颗 $n$ 个节点的树，边有边权 $w_i$。

每一个点往**所有**距离自己最远的点的简单路径上的点的权值加 $1$。

求最后所有点的点权和。

$1\le n\le10^6,0\le w_i\le10^9$。


## 题目解析

### **对于前 $30\%$ 的数据**：
$1\le n \le 5000$；


注意这里数据范围较小，属于签到的部分分。

对于每个点跑一次搜索，找到最远的点，给对应路径上的权值加 $1$即可。

注意开 `long long`。

时间复杂度：$O(n^2)$。


### **对于另外 $10\%$ 的数据**：
$n\le 10^6$，且满足树的形态为**一条链**；


如果是一条链的情况，我们考虑先遍历遍这条链，做一个前缀的长度和。

对于每一个点，明显一定会取到链的两头长度才能达到最长，我们比较这个点到两头的长度即可。

注意可能两头长度一样。

时间复杂度：$O(n)$。

[Code](https://www.luogu.com.cn/article/xke1lfn5)

### **对于另外 $10\%$ 的数据**：
$n\le 5\times 10^5$，且满足树的形态为**菊花**；


此处主要是提醒大家，**菊花**在这道题是需要特殊注意的点，容易导致复杂度爆炸。

求出中心点距离其他点的最大值和次大值，及其数量。

对于菊花中心点，明显是选择最大值，加上最大值数量 $\times 2$ 即可。

对于周围的点，它到中心点的距离是确定的，那么我们就是选择除了此点以外距离最远的点。

如果中心点到此点就是最大值，并且最大值只有一个，那么加上 次大值的数量 $\times$ 3 。否则加上 (最大值数量 $- 1$) $\times$ 3 即可。此处 $\times$ 3 的原因是，从当前点走到中心点每次都还有 $2$ 的贡献，千万不要忘了。

如果中心点到此点不是最大值，直接加上 最大值数量 $\times$ 3 即可。

时间复杂度：$O(n)$。

[Code](https://www.luogu.com.cn/article/s1s6rpbq)

### **对于 $100\%$ 的数据**：
$1\le n\le 10^6$，$0\le w_i \le 10^9$。


使用了换根的做法，以下皆用样例一作为解释。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/v8zh2w86.png)

此时我们钦定红点 $1$ 为根，每条边的边权为这个点到 $1$ 节点的距离。

明显对最终答案的贡献是 $8$，最远距离是 $3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/rgacc8rn.png)

此时我们将根转移到 $2$ 上，答案变成了 $6$，最远距离为 $2$。

我们可以总结出一个规律：当一个点 $u$ 换根到他的子节点 $v$ 时，只需要将在 $u$ 子树内的节点到 $u$ 的距离全部减去 $w_{u, v}$，非子树以外的节点全部加上 $w_{u, v}$，即可实现边权的动态变化。

这里暴力实现还是 $O(n)$ 的，我们可以使用线段树维护 dfs 序，同时可以 $O(\log n)$ 修改和查询。

****

紧接着思考怎么用线段树来合并答案。

我们线段树维护了 $3$ 个值 $count,dis,res$。

$dis$ 表示当前节点到根节点的最大深度。

$count$ 表示当前为最大深度 $dis$ 的情况下，一共有多少条不同的路径。

$res$ 用于存储答案。

****

push_up 我们需要分类讨论：

当 $ls$ 和 $rs$ 的 $dis$ 相同时，总路径数要合并到一起，答案相加：

```c++
tree[k].count = tree[k << 1].count + tree[k << 1 | 1].count;
tree[k].res = tree[k << 1].res + tree[k << 1 | 1].res;
tree[k].dis = tree[k << 1].dis;
```

否则就直接继承 $dis$ 最大的那个儿子：

```c++
if (tree[k << 1].dis > tree[k << 1 | 1].dis)
		tree[k] = tree[k << 1];
else tree[k] = tree[k << 1 | 1];
```

同时需要区间修改，再维护一个 lazy tag 即可。

****

到此为止这道题已经差不多了，但是还有点小细节：

注意这个换根的转移顺序，必须从自己的父亲节点转移过来，意味着我们以 dfs 的顺序换根，回溯的时候不能忘记对线段树进行回溯。

题解里使用的是手写的树遍历（需要使用**当前弧优化**，也就是模拟 dfs），为的是减少 dfs 的栈空间和常数，本题轻微卡常。

否则只能拿到 **对于 $40\%$ 的数据**：
$n\le 5\times 10^{5},w_i\le 10^9$。

时间复杂度：$O(n \log n)$。

另有 $O(n)$ 的 DP 做法，在此不再阐述。

## STD

```c++
/* The code is from koukilee*/

struct edge{i32 u, v, d, nex;}g[MAXN << 1];
struct Tree{i32 count; i64 dis, res;}tree[MAXN << 2];

i32 n, first[MAXN], cnt, dfn[MAXN], id, size[MAXN], fdep[MAXN], dfa[MAXN], rev[MAXN], cur[MAXN], stack[MAXN], sta;
i64 ans, fw[MAXN], lazy[MAXN << 2], tazy[MAXN << 2];
bool vis[MAXN];

inline void update(i32 u, i32 v, i32 d) noexcept{g[++cnt] = (edge){u, v, d, first[u]}, first[u] = cnt;} 

void dfs (i32 u, i32 fa) noexcept{
	dfn[u] = ++id, rev[id] = u, size[u] = 1;
	for (i32 i = first[u]; i; i = g[i].nex){
		if (g[i].v != fa){
			fdep[g[i].v] = fdep[u] + 1, fw[g[i].v] = fw[u] + g[i].d;
			dfs(g[i].v, u), size[u] += size[g[i].v];
			dfa[g[i].v] = g[i].d;
		}
	}
}

inline void push_up (i32 k) noexcept{
	if (tree[k << 1].dis == tree[k << 1 | 1].dis){
		tree[k].count = tree[k << 1].count + tree[k << 1 | 1].count, tree[k].res = tree[k << 1].res + tree[k << 1 | 1].res;
		tree[k].dis = tree[k << 1].dis;
	}
	else if (tree[k << 1].dis > tree[k << 1 | 1].dis)
		tree[k] = tree[k << 1];
	else tree[k] = tree[k << 1 | 1];
}

inline void push_down (i32 k) noexcept{
	tree[k << 1].res += tree[k << 1].count * tazy[k], tree[k << 1].dis += lazy[k];
	tree[k << 1 | 1].res += tree[k << 1 | 1].count * tazy[k], tree[k << 1 | 1].dis += lazy[k];
	lazy[k << 1] += lazy[k], lazy[k << 1 | 1] += lazy[k];
	tazy[k << 1] += tazy[k], tazy[k << 1 | 1] += tazy[k];
		
	lazy[k] = tazy[k] = 0;
}

void build (i32 k, i32 l, i32 r) noexcept{
	if (l == r){
		tree[k].count = 1, tree[k].res = fdep[rev[l]], tree[k].dis = fw[rev[l]];
		return;
	}
	
	i32 mid = (l + r) >> 1;
	build(k << 1, l, mid), build(k << 1 | 1, mid + 1, r);
	push_up(k);
}

void change (i32 k, i32 l, i32 r, i32 x, i32 y, i32 v, i32 cw) noexcept{
	if (x <= l && r <= y){
		tree[k].res += tree[k].count * v, tree[k].dis += v * cw;
		lazy[k] += v * cw, tazy[k] += v ;
		return;
	}
	
	i32 mid = (l + r) >> 1; push_down(k);
	if (x <= mid) change(k << 1, l, mid, x, y, v, cw);
	if (y > mid) change(k << 1 | 1, mid + 1, r, x, y, v, cw);
	
	push_up(k);
}

int main() noexcept{
	read(n);
	for (i32 i = 1, x, y, d; i < n; i++){
		read(x, y, d); update(x, y, d), update(y, x, d);
	}
	
	for (i32 i = 1; i <= n; i++)
		cur[i] = first[i];
	
	fdep[1] = 1;
	dfs(1, 0);
	
	build(1, 1, n); 
	
	stack[++sta] = 1, ans += tree[1].res, vis[1] = 1;
	
	while (sta > 0){
		i32 nex = stack[sta], f = 0;
		
		for (i32 i = cur[nex]; i; i = g[i].nex){
			cur[nex] = i;
			if (g[i].v != nex && !vis[g[i].v]){
				stack[++sta] = g[i].v, f = 1, vis[g[i].v] = 1;
				change(1, 1, n, 1, n, 1, dfa[g[i].v]), change(1, 1, n, dfn[g[i].v], dfn[g[i].v] + size[g[i].v] - 1, -2, dfa[g[i].v]);
				ans += tree[1].res;
				break;
			}
		}
		
		if (!f)
			change(1, 1, n, 1, n, -1, dfa[nex]), change(1, 1, n, dfn[nex], dfn[nex] + size[nex] - 1, 2, dfa[nex]), sta--;
	}
	put(ans);
    return 0;
}
```

---

## 作者：_lmh_ (赞：3)

找出树的直径的中点，可以证明从任意一个点出发的任意一条最长路径都经过这个中点，否则可以在树上找出一条比直径更长的路径。

把路径分成到中点之前和到中点之后两部分计算，需要记录一个节点子树的最大深度，最大深度的节点数量和子树大小。

容易做到 $O(n)$。细节参见代码。

（upd：修复了代码中的问题。感谢 @[FRZ_29](https://www.luogu.com.cn/user/1134636) 的 hack 数据。）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1000007;
struct edge{ll to,w,nxt;}e[N<<1];
ll n,root,p1,p2,x1,x2,ans,dep[N],hd[N],nE=1,sz[N],mxd[N],p[N],cnt[N];
void add(ll u,ll v,ll w){e[++nE]=(edge){v,w,hd[u]};hd[u]=nE;}
void dfs(int u,int in){
	mxd[u]=dep[u]=dep[p[u]=e[in].to]+e[in].w;cnt[u]=1;
	if (dep[u]>dep[p1]) p1=u;
	sz[u]=1;
	for (int v,i=hd[u];i;i=e[i].nxt) if (i!=in){
		v=e[i].to;
		dfs(v,i^1);
		sz[u]+=sz[v];
		if (mxd[v]>mxd[u]){
			mxd[u]=mxd[v];cnt[u]=cnt[v];
		}
		else if (mxd[v]==mxd[u]) cnt[u]+=cnt[v];
	}
}
void add(int u,ll w){
	ans+=w*cnt[u];
	for (int v,i=hd[u];i;i=e[i].nxt) if ((v=e[i].to)!=p[u]&&mxd[v]==mxd[u]) add(v,w);
}
void add2(int u,ll w){
	ans+=w*sz[u];
	for (int v,i=hd[u];i;i=e[i].nxt) if ((v=e[i].to)!=p[u]) add2(v,w);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for (ll u,v,w,i=1;i<n;++i){
		cin>>u>>v>>w;
		add(u,v,w);add(v,u,w);
	}
	dfs(1,0);root=p2=p1;p1=0;
	dfs(root,0);
	ll d=dep[p1],w=0,u=p1;
	while(1){
		w+=dep[u]-dep[p[u]];
		if (w*2==d){x1=p[u];break;}
		else if (w*2>d){x1=u;x2=p[u];break;}
		u=p[u];
	}
	if (x2){
		dfs(x1,0);
		add(x2,n-sz[x2]);
		ll m=cnt[x2];
		dfs(x2,0);
		add(x1,n-sz[x1]);
		add2(x1,m);
		m=cnt[x1];
		dfs(x1,0);
		add2(x2,m);
	}
	else{
		dfs(x1,0);add(x1,1);
		for (int u,i=hd[x1];i;i=e[i].nxt){
			if (mxd[u=e[i].to]==mxd[x1]){
				ans+=n-sz[u]-1;
				add(u,n-sz[u]-1);
			}
			add2(u,cnt[x1]-(mxd[u]==mxd[x1]?cnt[u]:0));
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

