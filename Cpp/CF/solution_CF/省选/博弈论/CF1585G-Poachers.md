# Poachers

## 题目描述

Alice and Bob are two poachers who cut trees in a forest.

A forest is a set of zero or more trees. A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. The parent of a node $ v $ is the next vertex on the shortest path from $ v $ to the root. Children of vertex $ v $ are all nodes for which $ v $ is the parent. A vertex is a leaf if it has no children.

In this problem we define the depth of vertex as number of vertices on the simple path from this vertex to the root. The rank of a tree is the minimum depth among its leaves.

Initially there is a forest of rooted trees. Alice and Bob play a game on this forest. They play alternating turns with Alice going first. At the beginning of their turn, the player chooses a tree from the forest. Then the player chooses a positive cutting depth, which should not exceed the rank of the chosen tree. Then the player removes all vertices of that tree whose depth is less that or equal to the cutting depth. All other vertices of the tree form a set of rooted trees with root being the vertex with the smallest depth before the cut. All these trees are included in the game forest and the game continues.

A player loses if the forest is empty at the beginning of his move.

You are to determine whether Alice wins the game if both players play optimally.

## 说明/提示

In the first test case Bob has a symmetric strategy, so Alice cannot win.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/504019013a3bfbf8eb56c8730800a342f1394e57.png)

In the second test case Alice can choose the second tree and cutting depth $ 1 $ to get a forest on which she has a symmetric strategy.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/8fe2d012fa7f86edd6ce3b0992b73d46bc9c4b34.png)

In third test case the rank of the only tree is $ 2 $ and both possible moves for Alice result in a loss. Bob either can make the forest with a symmetric strategy for himself, or clear the forest.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/eed2cbe70e21303a782188eb3bbbd7989634e2f0.png)

In the fourth test case all leafs have the same depth, so Alice can clear the forest in one move.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/095a24a5876a4e208466c20d0a9b949b0c7e2ff3.png)

## 样例 #1

### 输入

```
4
4
0 1 0 3
7
0 1 2 0 4 5 6
4
0 1 1 2
7
0 1 1 2 2 3 3```

### 输出

```
NO
YES
NO
YES```

# 题解

## 作者：Qiaoqia (赞：5)

~~话说怎么全网都没有这题的中文题解啊。~~  
想不到官方题解里一只 $\log$ 的神奇做法，所以我用树上启发式合并（dsu on tree）和线段树以 $\mathcal O(n \log^2 n)$ 的时间复杂度通过了此题 ~~同时喜提最优解最后一名~~。  

首先复习一下博弈论相关知识：
1. 一个公平游戏的一个状态的 $\operatorname {SG}$ 函数值为它能到达的所有状态的 $\operatorname {SG}$ 函数值中没出现过的最小非负整数（即 $\operatorname {mex}$ 值）。
2. 多个公平游戏组合在一起的 $\operatorname {SG}$ 函数值是其中所有游戏状态的 $\operatorname {SG}$ 函数值异或和。
3. 一个公平组合游戏先手必败当且仅当其初始状态 $\operatorname{SG}$ 函数值为 $0$。

那么这题就有了一个基本思路，即对每棵子树求出它删去一个深度以下的点剩下的子树的 $\operatorname {SG}$ 函数值的异或和的 $\operatorname {mex}$，最后再将森林中的所有树根的 $\operatorname {SG}$ 函数值异或在一起。

这个计算的过程要对子树询问，看上去很可以 dsu on tree，但是和 dsu on tree 的板子又有这些不同：

1. 需要维护的 $\operatorname {mex}$ 值不像和之类的那么好维护。
3. 询问一个点为根的子树不把根计入答案。
1. 空状态并不是树上的节点，但它的 $\operatorname {SG}$ 函数值（也就是 $0$）会对计算过程有影响。
2. 每次并不是要询问整棵子树，而只是对一个深度以上求解。


对于第一个问题，可以开一棵线段树来维护每个非负整数出现的次数，修改的时候先把原来的值删去，插入时加上，询问时线段树上二分。  
对于第二个问题和第三个问题，每次维护当前点以下的答案即可（不重新计算重儿子子树改为只计算重儿子上的值，而不进入子树中的其它点），同时每次加入一个 $0$ 表示新出现的一层的答案。  
对于最后一个问题，因为最小深度肯定是不断递减的，每次删除重儿子的深度限制和当前点的限制之间深度的答案就行了，注意 dsu on tree 加和清空的时候不要再 加/清空 这些点了。

这样这题就做完了。

cf 提交记录：[#153349274](https://codeforces.com/contest/1585/submission/153349274)


---

## 作者：Grisses (赞：3)

考虑对每棵树算 $sg$ 值，容易发现有 $\begin{cases}dp_{x,0}&=&\operatorname{mex}\limits_{i=1}^{lim_x}dp_{x,i}&\\dp_{x,i}&=&\bigoplus\limits_{v}dp_v{i-1}&(i>0)\end{cases}$。

其中 $dp_{x,i}$ 表示以 $x$ 子树中距 $x$ 距离为 $i$ 的所有点为根的子树的 $sg$ 的异或和，$lim_x$ 表示 $x$ 子树中离 $x$ 最近的叶子的距离。

考虑先给所有叶子挂一个虚点，这样就避免了特判一步删空。

发现这玩意和深度有关，于是我们可以得到一个基于长剖的线性做法。

- 如果 $x$ 是叶子，$sg_x=dp_{x,0}=0$。
- 如果 $x$ 只有一个儿子 $v$，考虑其所有后代的 $sg$ 值组成的集合 $S_x$，可以发现有 $S_x=S_v\cup\{sg_v\}$。同时有 $sg_x=\operatorname{mex}S_x$，发现 $sg_x$ 可以从 $sg_v$ 暴力往上枚举，对于一整条长链，最多跳 $\Theta(len)$ 次。
- 如果 $x$ 有多个儿子，考虑将所有 $dp_{x,i}$ 求出后直接暴力算出 $sg_x$，复杂度 $\Theta(lim_x)$。

也就是说我们总的复杂度为所有长链的长度之和，即 $n$。

[代码](https://codeforces.com/contest/1585/submission/298957875)。

---

## 作者：I_am_Accepted (赞：3)

目标是求出每个树根的 sg 函数。

长剖，每个点维护其为根的子树的 sg 值，以及该 sg 值是由哪个集合的值求 $\text{mex}$ 得到的。

对于叶子，sg 值 $=1$，集合为 $\{0\}$。

对于只有一个儿子的节点，其集合为儿子集合加上儿子的 sg（直接换过来，复杂度 $O(1)$），该节点的 sg 若出现在集合中则不断 $+1$。

否则，先执行长剖合并过程，每个位置存该深度子树的 sg 值的 $\text{xor}$ 和。求 sg 时直接暴力存集合求 $\text{mex}$ 。该步复杂度基于最浅叶子深度，由长剖合并复杂度分析，复杂度正确。

用优先队列实现集合的各种操作，总复杂度 $O(n\log n)$。

长剖容易写挂不好调，开内存池的做法很难找出越界错误。

---

## 作者：绝顶我为峰 (赞：1)

这显然是个公平博弈，森林中每一棵树完全独立，分别算 SG 函数异或起来即可，下面尝试算一下 SG 函数。

毫无疑问，空树的 SG 函数是 $0$，考虑非空树的 SG 函数怎么计算。

首先维护一下最浅的叶子深度，这样我们选定一个 $d$ 之后，把所有深度 $\leq d$ 的点删掉，会剩下若干个（可以是 $0$ 个）森林，两棵子树之间是完全独立的，那么 SG 值就是所有子树的 SG 值的异或。

枚举所有合法的 $d$ 然后暴力求 $\mathrm{mex}$ 就是 $O(n^2)$ 的暴力，尝试优化。

首先考虑怎样快速维护所有 $d$ 的答案，发现这个东西只和深度有关，可以直接套一个长链剖分。

然后是怎样快速求 $\mathrm{mex}$，可以对所有 $d$ 对应的 SG 函数维护一棵平衡树，查询的时候在平衡树上二分，如果左子树是满的就进右子树，否则进左子树。

理论上时间复杂度 $O(n\log n)$，但是手写平衡树实在是太麻烦了，我偷懒直接用了 pbds 的平衡树，但这样就会让平衡树二分变成二分套平衡树，多一个 $\log$。

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/trie_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> val[500001];
int t,ans,n,fa[500001],minn[500001],p[500001],tmp[2000001],*id=tmp,*sg[500001],len[500001],son[500001];
vector<int> v[500001];
map<int,int> cnt[500001];
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
inline void dfs1(int k)
{
    minn[k]=n;
    for(int i:v[k])
    {
        dfs1(i);
        if(len[i]>len[son[k]])
            son[k]=i;
        minn[k]=min(minn[k],minn[i]+1);
    }
    len[k]=len[son[k]]+1;
    if(v[k].empty())
    {
        len[k]=2;
        minn[k]=1;
    }
}
inline int mex(int l,int r,int k)
{
    if(l==r)
        return l;
    int mid=(l+r)>>1;
    if(val[k].order_of_key(mid+1)==mid+1)
        return mex(mid+1,r,k);
    return mex(l,mid,k);
}
inline void dfs2(int k)
{
    if(son[k])
    {
        sg[son[k]]=sg[k]+1;
        dfs2(son[k]);
        p[k]=p[son[k]];
        for(int i=minn[son[k]]+1;i>minn[k];--i)
            if(!--cnt[p[k]][sg[k][i]])
            {
                val[p[k]].erase(sg[k][i]);
                cnt[p[k]].erase(sg[k][i]);
            }
    }
    else
    {
        p[k]=k;
        cnt[p[k]][0]=1;
        val[p[k]].insert(0);
    }
    for(int i:v[k])
    {
        if(i==son[k])
            continue;
        sg[i]=id;
        id+=len[i];
        dfs2(i);
        for(int j=1;j<=minn[k];++j)
        {
            if(!--cnt[p[k]][sg[k][j]])
            {
                val[p[k]].erase(sg[k][j]);
                cnt[p[k]].erase(sg[k][j]);
            }
            sg[k][j]^=sg[i][j-1];
            if(!cnt[p[k]][sg[k][j]]++)
                val[p[k]].insert(sg[k][j]);
        }
    }
    sg[k][0]=mex(0,n,p[k]);
    if(!cnt[p[k]][sg[k][0]]++)
        val[p[k]].insert(sg[k][0]);
}
int main()
{
    t=read();
    while(t--)
    {
        n=read();
        for(int i=1;i<=n;++i)
        {
            fa[i]=read();
            if(fa[i])
                v[fa[i]].emplace_back(i);
        }
        for(int i=1;i<=n;++i)
            if(!fa[i])
            {
                dfs1(i);
                sg[i]=id;
                id+=len[i];
                dfs2(i);
                ans^=sg[i][0];
            }
        cout<<(ans? "YES":"NO")<<'\n';
        for(int i=0;i<=n;++i)
        {
            fa[i]=minn[i]=p[i]=len[i]=son[i]=0;
            sg[i]=NULL;
            v[i].clear();
            val[i].clear();
            cnt[i].clear();
        }
        for(int i=0;i<=n+n;++i)
            tmp[i]=0;
        id=tmp;
        ans=0;
    }
    return 0;
}
```

---

## 作者：xfrvq (赞：0)

$\tt^*2500$。

套路。公平博弈考虑 $\tt SG$ 函数。$\mathtt{SG}=0$ 代表先手必败，$>0$ 表示先手必胜。终止状态（必败）的 $\tt SG$ 值为 $0$，一个状态的 $\tt SG$ 值是它所有后继状态的 $\rm mex$，多个状态的 $\tt SG$ 值是每个子状态值的异或和。

这题中，终止状态是“树为空”，一个子树是一个状态，其后继状态是分别删去 $1,\cdots,$ 它的秩层后的情况，涉及到多个子树的时候，把每个子树的 $\tt SG$ 值异或起来。考虑 dp 模拟这个过程。

套路，dp 涉及子树深度，考虑长剖优化。设 $f_{u,i}$ 代表 $u$ 子树距离 $u$ 为 $i$ 的 $\tt SG$ 值异或和。转移为：

$$\begin{cases}f_{u,i+1}&=\bigoplus _{v}f_{v,i}\\f_{u,0}&=\mathrm{mex}_kf_{u,k}\end{cases}$$

（第二条式子中 $k$ 是 $u$ 所有能转移到的高度，设 $d$ 为深度，$d_0$ 为子树内最浅叶子深度，$d_1$ 为子树内最深叶子深度，这里 $1\le k\le\min\{d_{0,u}+1,d_{1,u}\}-d_u$）

此时唯一问题是求 $\rm mex$，考虑用 `set` 类似 $\tt ODT$ 维护所有值域连续段，`map` 维护每个数的出现次数，适时在 `set` 中添加或删除。询问要么是 $0$ 要么是 `set` 的第一个值域连续段右端点 $+1$。

长剖从长儿子转移过来直接把 `set`，`map` 弄过来。这时需要删去“在长儿子子树中合法，父亲子树中不合法”的情况，分讨边界即可。

注意“树为空”状态并不存在，但确实要把 $0$ 统计入 $\tt SG$ 函数求 $\rm mex$ 里面。考虑什么情况下能到达空树的状态（也就是一步能删完的状态），此时应当有 $d_{0,u}=d_{1,u}$，特判即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

int T,n,dep[N],mxd[N],mnd[N],son[N],dfn[N],cnt,sg[N];
bool rt[N];
vector<int> G_[N]; 
map<int,int> M[N];
set<pair<int,int>> S[N];

void ins(int u,int x){
	if(!M[u][x]++){
		auto i = S[u].lower_bound(make_pair(x,0));
		int l = x,r = x;
		if(i != S[u].begin() && prev(i)->second == x - 1) l = prev(i)->first,S[u].erase(prev(i));
		i = S[u].lower_bound(make_pair(x,0));
		if(i != S[u].end() && i->first == x + 1) r = i->second,S[u].erase(i);
		S[u].emplace(l,r);
	}
}

void ers(int u,int x){
	if(!--M[u][x]){
		auto i = prev(S[u].lower_bound(make_pair(x + 1,0)));
		auto[l,r] = *i; S[u].erase(i);
		if(x != l) S[u].emplace(l,x - 1);
		if(x != r) S[u].emplace(x + 1,r);
	}
}

int qry(int u){
	if(S[u].empty() || S[u].begin()->first != 0) return 0;
	return S[u].begin()->second + 1;
} 

void dfs(int u,int ft){
	mxd[u] = dep[u] = dep[ft] + 1,son[u] = 0;
	mnd[u] = (!G_[u].size()) ? dep[u] : (n + 1);
	for(int v : G_[u]){
		dfs(v,u);
		mnd[u] = min(mnd[u],mnd[v]);
		if(mxd[v] > mxd[u]) mxd[u] = mxd[v],son[u] = v;
	}
}

void sol(int u,int ft){
	dfn[u] = ++cnt;
	if(son[u]){
		sol(son[u],u);
		M[u].swap(M[son[u]]),S[u].swap(S[son[u]]);
		for(int i = min(mnd[u] + 1,mxd[u]) - dep[u] + 1;i <= min(mnd[son[u]] + 1,mxd[son[u]]) - dep[u];++i) ers(u,sg[dfn[u] + i]);
		if(mnd[son[u]] == mxd[son[u]] && mnd[u] != mxd[u]) ers(u,0);
	} else ins(u,0);
	for(int v : G_[u]) if(v != son[u]){
		sol(v,u);
		for(int i = 0;i <= mxd[v] - dep[v];++i){
			if(i + 1 <= min(mnd[u] + 1,mxd[u]) - dep[u]) ers(u,sg[dfn[u] + i + 1]);
			sg[dfn[u] + i + 1] ^= sg[dfn[v] + i];
			if(i + 1 <= min(mnd[u] + 1,mxd[u]) - dep[u]) ins(u,sg[dfn[u] + i + 1]);
		}
	}
	sg[dfn[u]] = qry(u),ins(u,sg[dfn[u]]);
}

int main(){
	for(scanf("%d",&T);T--;){
		scanf("%d",&n),cnt = 0;
		for(int i = 0;i <= n;++i) G_[i].clear(),M[i].clear(),S[i].clear();
		for(int i = 1,f;i <= n;++i)
			scanf("%d",&f),G_[f].push_back(i),rt[i] = !f;
		for(int i = 1;i <= n;++i) if(rt[i]) dfs(i,0);
		for(int i = 1;i <= n;++i) if(rt[i]) sol(i,0);
		int s = 0;
		for(int i = 1;i <= n;++i) if(rt[i]) s ^= sg[dfn[i]];
		puts(s ? "YES" : "NO");
	}
	return 0;
}
```

---

