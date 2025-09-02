# [NOISG 2022 Qualification] Tree Cutting

## 题目背景

一个国家有 $N$ 个城市，编号为 $1$ 到 $N$，以及 $N-1$ 条双向公路。通过这些公路，可以从任意一个城市到达另一个城市。

城市 $x$ 和城市 $y$ 之间的距离定义为连接两城市所需经过的公路数。

州长决定拆除一条公路，并新建另一条公路，使得任意两城市之间的最远距离最大化。

## 题目描述

请计算新建公路后，任意两城市之间的最大距离。

## 说明/提示

【样例解释】

对于样例 $1$，最远距离无法增加，仍然为 $3$。  

对于样例 $2$，可以拆除公路 $2-5$，新建公路 $3-4$，最远路径为 $1-2-3-4-5-6$，其长度为 $5$。

【数据范围】

- $2 \leq N \leq 300,000$
- $1 \leq u, v \leq N$

| 子任务编号 | 分值 | 额外限制条件                             |
| :--------: | :--: | :--------------------------------------: |
| $1$        | $5$  | $N \leq 10$                              |
| $2$        | $10$ | $N \leq 100$                             |
| $3$        | $15$ | $N \leq 3000$                            |
| $4$        | $15$ | $N \leq 300,000$，至多一个城市连接至少 $3$ 条公路 |
| $5$        | $55$ | 无额外限制                              |

## 样例 #1

### 输入

```
4
1 2
1 3
3 4```

### 输出

```
3```

## 样例 #2

### 输入

```
6
1 2
2 3
2 5
4 5
5 6```

### 输出

```
5```

# 题解

## 作者：xiezheyuan (赞：3)

感觉大家好像都写的是 $O(n)$ 或 $O(n\log n)$ 的，给大家来一个 $O(n\log^2 n)$ 的做法养养眼（bushi），成功抢下最劣解。

## 简要题意

给定一个 $n$ 个点的树，你需要断掉一条边并连接一条边，使得得到的无向图仍然构成一个树，在此基础上，最大化直径长度。输出这个最大长度。

$1\leq n\leq 3\times 10^5$。

Note：题意中没有显示要求剩下的图仍然是一棵树，但是如果不是一棵树的话“任意两城市之间的最远距离”是未定义的。

## 思路

我们考虑枚举断掉哪一条边，为了方便，我们随便钦定一个点为根，然后枚举这条边的两端点中深度较大的点。

现在的问题是接下来连哪条边更优，我们断掉这条边后实际上将原树分成了两个连通块，那么我们显然连接两个连通块的直径最优。答案就是这两个直径的长度之和加上 $1$（$1$ 表示连接的这条边的长度）。

于是我们转换成求每一个子树内 / 外的直径长度，比较好的做法是树形 dp，但是更加一般的做法是对树求一遍 dfs 序，则子树内的点位于连续区间内，用线段树维护区间直径即可。

用重链剖分求 LCA（用于求树上距离），时间复杂度 $O(n\log^2 n)$，实现精细的话换成欧拉序或 dfs 序求 LCA 可以做到 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

const int N = 3e5 + 5;
int n;
vector<int> g[N];

int top[N], dep[N], siz[N], son[N], father[N], dfn[N], rev[N];

void dfs1(int u, int fa){
    dep[u] = dep[fa] + 1, father[u] = fa, siz[u] = 1;
    dfn[u] = ++dfn[0], rev[dfn[u]] = u;
    for(int v : g[u]){
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int fa){
    if(son[u]){
        top[son[u]] = top[u];
        dfs2(son[u], u);
    }
    for(int v : g[u]){
        if(v == fa || v == son[u]) continue;
        top[v] = v;
        dfs2(v, u);
    }
}

int lca(int x, int y){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = father[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

int dis(int x, int y){
    return dep[x] + dep[y] - (dep[lca(x, y)] << 1);
}

struct node{
    int x, y, len;
} t[N << 2];

node merge(node x, node y){
    vector<node> kcr = {
        {x.x, y.x, dis(x.x, y.x)}, {x.x, y.y, dis(x.x, y.y)},
        {x.y, y.x, dis(x.y, y.x)}, {x.y, y.y, dis(x.y, y.y)},
        x, y
    };
    return *max_element(kcr.begin(), kcr.end(), [](node x, node y){
        return x.len < y.len;
    });
}

void build(int i, int l, int r){
    if(l == r) return (t[i] = {rev[l], rev[l], 0}), void();
    build(ls, l, mid), build(rs, mid + 1, r);
    t[i] = merge(t[ls], t[rs]);
}

node query(int ql, int qr, int i, int l, int r){
    if(ql <= l && r <= qr) return t[i];
    if(ql <= mid && qr > mid) return merge(query(ql, qr, ls, l, mid), query(ql, qr, rs, mid + 1, r));
    else if(ql <= mid) return query(ql, qr, ls, l, mid);
    return query(ql, qr, rs, mid + 1, r);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1,u,v;i<n;i++){
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    dfs1(1, 0), dfs2(1, 0), build(1, 1, n);
    int ans = 0;
    for(int i=2;i<=n;i++){
        int in_tree = query(dfn[i], dfn[i] + siz[i] - 1, 1, 1, n).len;
        int out_tree;
        if(dfn[i] != 1 && dfn[i] + siz[i] <= n) out_tree = merge(query(1, dfn[i] - 1, 1, 1, n), query(dfn[i] + siz[i], n, 1, 1, n)).len;
        else if(dfn[i] != 1) out_tree = query(1, dfn[i] - 1, 1, 1, n).len;
        else out_tree = query(dfn[i] + siz[i], n, 1, 1, n).len;
        ans = max(ans, in_tree + out_tree);
    }
    cout << ans + 1;
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Nasaepa (赞：1)

# Part 0 闲话

这道题是一道换根 dp，个人感觉还挺简单的，有一点思维难度。

# Part 1 题意转化

我们知道，树上的每一条边都是桥，所以在截断一条边后一定会使整棵树变为 2 颗树。此时我们只需要在这 2 颗子树上找各找直径并将其连接就能满足题目要求。

所以这题就被我们转化成了：将 1 棵树通过删除一条边变为 2 棵树。使这两棵树的直径之和最大。

此时我们需要思考一个问题：一棵树的以任意一个子节点为根的子树的直径很好求，一次深搜维护就能搞定。如果一棵树**删去**以任意一个子节点（非原树的根节点）为根的子树的部分，剩下的部分的直径应该怎么求？

# Part 2 换根 dp

假设对于这样一颗树：

![](https://cdn.luogu.com.cn/upload/image_hosting/7ia6gj2c.png)

其中绿色节点是根节点，我们对蓝色节点进行讨论。

我们要找出每个节点的所有子节点为根的子树中高度第一高、第二高和第三高的， 图中已经标注，分别用红橙黄色对应标注了根节点。

我们首先需要知道蓝色节点子树以外的点构成的树的直径，用 $up$ 表示，红色节点的高度用 $rmax$ 表示，橙色节点的高度用 $smax$ 表示，黄色节点的高度用 $tmax$ 表示。这些值都可以用 2 次 dfs 实现。与此同时，我们还需要知道以每棵树为根节点的子树内部的直径，用 $mdia$ 表示。

此时我们可以写出一段代码维护这些值：

```cpp
void init(const int &idx,const int &dad){
    for(int edg = head[idx];edg;edg = nxt[edg]){
        if(to[edg] == dad)continue;
        init(to[edg],idx);
        // 根据 rmax 判断
        if(rmax[to[edg]] + 1 > rmax[idx]){
            tmax[idx] = smax[idx];
            smax[idx] = rmax[idx];// 更新次短
            sn[idx] = rn[idx];
            rn[idx] = to[edg];
            rmax[idx] = rmax[to[edg]] + 1;
        }else if(rmax[to[edg]] + 1 > smax[idx]) {
            tmax[idx] = smax[idx];
            sn[idx] = to[edg];
            smax[idx] = rmax[to[edg]] + 1;
        }else if(rmax[to[edg]] + 1 > tmax[idx]){
            tmax[idx] = rmax[to[edg]] + 1;
        }
    }
}

void lift(const int &idx,const int &dad){
    mdia[idx] = smax[idx] + rmax[idx];
    for(int edg = head[idx];edg;edg = nxt[edg]){
        if(to[edg] == dad)continue;
        if(to[edg] == rn[idx])up[to[edg]] = max(smax[idx],up[idx]) + 1;
        else up[to[edg]] = max(rmax[idx],up[idx]) + 1;
        lift(to[edg],idx);
        mdia[idx] = max(mdia[idx],mdia[to[edg]]);
    }
}
```

这些值维护完成后，就需要回到前面提出过的问题了。假设剩下部分的直径用 $dia$ 表示。我们首先看到红色节点。红色节点在子树中被删去，因此 $rmax$ 不能使用。注意到，我们可以选择该条直径是否经过蓝色节点。因此：

$$
dia = \max(smax + tmax,smax + up,dia_2)
$$

其中 $dia_2$ 表示蓝色节点的 $dia$ 值，下文同理。

同理可得，当当前节点为橙色节点时，可以得出：

$$
dia = \max(rmax + tmax,rmax + up,dia_2)
$$

当当前节点为黄色节点或者其它蓝色节点的子节点时，可以得出：

$$
dia = \max(rmax + smax,rmax + up,dia_2)
$$

因此，对于一个点，选择其作为被截出的子树的根节点后，其对应的直径之和为：

$$
dia + mdia + 1
$$

用代码则是这样实现的：

```cpp
void push(const int &idx,const int &dad){
    for(int edg = head[idx];edg;edg = nxt[edg]){
        if(to[edg] == dad)continue;
        if(to[edg] == rn[idx]){
            dia[to[edg]] = max(smax[idx] + tmax[idx],max(smax[idx]+up[idx],dia[idx]));
        }else if(to[edg] == sn[idx]){
            dia[to[edg]] = max(rmax[idx] + tmax[idx],max(rmax[idx]+up[idx],dia[idx]));
        }else dia[to[edg]] = max(rmax[idx] + smax[idx],max(rmax[idx]+up[idx],dia[idx]));
        push(to[edg],idx);
    }
    // 注意此处的判定
    if(dia[idx])ans = max(dia[idx] + mdia[idx] + 1,ans);
}
```

为何代码里有一行特判呢？因为我们需要考虑根节点的情况。

完整代码：

```cpp
// #pragma GCC optimize(2) // 开启O2优化
#include<bits/stdc++.h>
using namespace std;
#define N 300010
#define INF 0x3f3f3f3f // 无穷大
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define func function<void()>
namespace weighted_Graph{
	int head[N],nxt[N<<1],to[N<<1];//三个数组，分别为节点的第一条边，边的下一条边，边指向的节点
	int cnt_edge = 0;//边的个数
	inline void connect_head(const int &x,const int &y){//头部插入函数O(1)
		++cnt_edge;
		nxt[cnt_edge] = head[x];
		head[x] = cnt_edge;
		to[cnt_edge] = y;
	}
}
using namespace weighted_Graph;
int n;
int rmax[N],smax[N],rn[N],sn[N],tmax[N],up[N];// 最大值，次大值，最大值来源，向上走能走多远
int dia[N];
int mdia[N];// 子树的最大直径
int a,b,ans = 1;

void init(const int &idx,const int &dad){
    for(int edg = head[idx];edg;edg = nxt[edg]){
        if(to[edg] == dad)continue;
        init(to[edg],idx);
        // 根据 rmax 判断
        if(rmax[to[edg]] + 1 > rmax[idx]){
            tmax[idx] = smax[idx];
            smax[idx] = rmax[idx];// 更新次短路
            sn[idx] = rn[idx];
            rn[idx] = to[edg];
            rmax[idx] = rmax[to[edg]] + 1;
        }else if(rmax[to[edg]] + 1 > smax[idx]) {
            tmax[idx] = smax[idx];
            sn[idx] = to[edg];
            smax[idx] = rmax[to[edg]] + 1;
        }else if(rmax[to[edg]] + 1 > tmax[idx]){
            tmax[idx] = rmax[to[edg]] + 1;
        }
    }
}

void lift(const int &idx,const int &dad){
    mdia[idx] = smax[idx] + rmax[idx];
    for(int edg = head[idx];edg;edg = nxt[edg]){
        if(to[edg] == dad)continue;
        if(to[edg] == rn[idx])up[to[edg]] = max(smax[idx],up[idx]) + 1;
        else up[to[edg]] = max(rmax[idx],up[idx]) + 1;
        lift(to[edg],idx);
        mdia[idx] = max(mdia[idx],mdia[to[edg]]);
    }
}

void push(const int &idx,const int &dad){
    for(int edg = head[idx];edg;edg = nxt[edg]){
        if(to[edg] == dad)continue;
        if(to[edg] == rn[idx]){
            dia[to[edg]] = max(smax[idx] + tmax[idx],max(smax[idx]+up[idx],dia[idx]));
        }else if(to[edg] == sn[idx]){
            dia[to[edg]] = max(rmax[idx] + tmax[idx],max(rmax[idx]+up[idx],dia[idx]));
        }else dia[to[edg]] = max(rmax[idx] + smax[idx],max(rmax[idx]+up[idx],dia[idx]));
        push(to[edg],idx);
    }
    if(dia[idx])ans = max(dia[idx] + mdia[idx] + 1,ans);

}

// 输入函数
void input(){
    scanf("%d",&n);
    for(int i = 1;i < n;++i)scanf("%d%d",&a,&b), connect_head(b,a), connect_head(a,b);
}

// 处理函数
void solve(){
    init(1,0);
    lift(1,0);
    push(1,0);

//    for(int i = 1;i <= n;++i)printf("idx:%d rmax:%d rn:%d smax:%d sn:%d tmax:%d up:%d dia:%d mdia:%d\n",i,rmax[i],rn[i],smax[i],sn[i],tmax[i],up[i],dia[i],mdia[i]);
}

// 输出函数
void output(){
    printf("%d",ans);
}

// 主函数
int main(int argc,char* argv[]){
	input();
	solve();
	output();
	return 0;
}
```

---

## 作者：破壁人罗辑 (赞：1)

题目传送门：[P11294 [NOISG2022 Qualification] Tree Cutting](https://www.luogu.com.cn/problem/P11294)

## 题目大意

在一棵树上删除一条边并增加一条边，问新生成的树的最大直径。

## 解题思路

删除一条边之后，一棵树会变成两棵树，显然此时最好情况是将两棵树的直径相连。枚举每一条边计算即可。

可以使用 dfs，对于每个节点除去和它的每个子节点，计算该节点除去这个子节点后所在的树的直径和这个子节点的子树直径，相加再加一，取最大值即为答案。

可以在第一次 dfs 中计算计算每个节点的子树直径、子树最远节点距离、子树非严格次远节点距离、子树非严格第三远节点距离，在第二次 dfs 中计算非子树最远节点距离，然后由这些值计算出直径即可。时间复杂度 $O(n)$，可通过此题。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>to[300001];
bool vis[300001];int dep[300001],maxdep[300001][4],maxlen[300001],ans;
void dfs0(int i){
	dep[i]=1;vis[i]=1;
	for(auto j:to[i])if(!vis[j]){
		dfs0(j);dep[i]=max(dep[i],dep[j]+1);
		if(dep[j]>=maxdep[i][0]){
			maxdep[i][2]=maxdep[i][1];maxdep[i][1]=maxdep[i][0];maxdep[i][0]=dep[j];
		}
		else if(dep[j]>=maxdep[i][1]){
			maxdep[i][2]=maxdep[i][1];maxdep[i][1]=dep[j];
		}
		else if(dep[j]>=maxdep[i][2])maxdep[i][2]=dep[j];
		maxlen[i]=max(maxlen[i],maxlen[j]);
	}
	vis[i]=0;maxlen[i]=max(maxlen[i],maxdep[i][0]+maxdep[i][1]);
}
void dfs1(int i){
	vis[i]=1;
	for(auto j:to[i])if(!vis[j]){
		maxdep[j][3]=max(maxdep[i][0]==dep[j]?maxdep[i][1]:maxdep[i][0],maxdep[i][3])+1;
		dfs1(j);
		ans=max(ans,
			(maxdep[i][0]==dep[j]?maxdep[i][1]+max(maxdep[i][2],maxdep[i][3]):
			maxdep[i][1]==dep[j]?maxdep[i][0]+max(maxdep[i][2],maxdep[i][3]):
			maxdep[i][0]+max(maxdep[i][1],maxdep[i][3]))
			+maxlen[j]+1);
	}
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);to[u].push_back(v);to[v].push_back(u);
	}
	dfs0(1);dfs1(1);
	printf("%d",ans);
    return 0;
}
```

---

## 作者：Rem_CandleFire (赞：1)

操作等价于断开一条边，求分开的两棵树的直径之和的最大值。显然是换根 DP。规定 $1$ 为根。

设 $f_u$ 表示以点 $u$ 为根的子树的直径长度。显然可以通过讨论直径是否经过点 $u$ 转移。这里要维护深度的前三大值。

考虑换根得到对于边 $u\rightarrow v$，断掉该边后 $u$ 那端子树的直径，记为 $dp_v$，那么本题的答案就是 $\max_u{f_u+dp_u+1}$。假设现在断的边是 $u\rightarrow v$，转移需要类似上文一样分类讨论。

- 继承其它点的直径。对于点 $u$ 和所有与 $u$ 连边的 $v$（包括祖先），需要维护 $f_v$ 的最大值和次大值。若最大值的方向是当前的 $v$ 则取次大值，否则取最大值。
- 直径经过点 $u$。考虑维护以 $u$ 为端点的链的前三大长度，从祖先到达的链需要特殊转移，否则沿用求 $f$ 时记录的值。同时记录方向，然后按求 $f$ 时类似的方程转移即可。

时间复杂度 $O(n)$。如果需要样例可以看一下讨论区的帖子。

[常数较大，又臭又长的代码](https://www.luogu.com.cn/paste/xi6ao2cg)

---

## 作者：ben090302 (赞：0)

题意简化：删一条边连一条边，使得树的直径尽可能长。

考虑到肯定是删掉一条边后形成两棵树，那么必然是把两棵树的直径接起来最优。

我们考虑用线段树维护一段连续 dfs 序的点的直径，由于结论两棵树的直径的端点一定是两条直径分别的端点中选出两个作为端点，于是就可线段树维护区间直径，非常好写，于是我们可以快速求子树内外分别的直径。

非常好写，因为用了树剖求最近公共祖先所以复杂度 $O(n\log^2n)$，可过。

```
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n;
vector<int> e[N];
int fa[N],siz[N],son[N],dep[N],top[N],dfn[N],idx;
void dfs1(int u,int ff){
	fa[u]=ff;
	siz[u]=1;
	dep[u]=dep[ff]+1;
	for(int v:e[u]){
		if(v==ff) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
int nfd[N];
void dfs2(int u,int tp){
	top[u]=tp;
	dfn[u]=++idx;
	nfd[idx]=u;
	if(son[u]) dfs2(son[u],tp);
	for(int v:e[u]){
		if(v==fa[u] or v==son[u]) continue;
		dfs2(v,v);
	}
}
int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	return (dep[u]<dep[v])?u:v;
}

int dis(int u,int v){
	return dep[u]+dep[v]-2*dep[LCA(u,v)];
}
struct node{
	int x,y,len;//直径端点和长度
	bool operator<(node y)const{
		return len<y.len;
	}
}tr[N<<2];
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
node merge(node x,node y){
	return max({{x.x,y.x,dis(x.x,y.x)},{x.x,y.y,dis(x.x,y.y)},{x.y,y.x,dis(x.y,y.x)},{x.y,y.y,dis(x.y,y.y)},x,y});
}
void build(int rt,int l,int r){
	if(l==r){
		tr[rt]={nfd[l],nfd[l],0};
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	tr[rt]=merge(tr[ls],tr[rs]);
}
node query(int rt,int l,int r,int L,int R){
	if(L<=l and r<=R){
		return tr[rt];
	}
	if(L<=mid and mid<R) return merge(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R)); 
	if(L<=mid) return query(ls,l,mid,L,R);
	return query(rs,mid+1,r,L,R);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	int ans=0;
	for(int i=2;i<=n;i++){
		int In=query(1,1,n,dfn[i],dfn[i]+siz[i]-1).len;
		int out;
		if(dfn[i]+siz[i]<=n) out=merge(query(1,1,n,1,dfn[i]-1),query(1,1,n,dfn[i]+siz[i],n)).len;
		else out=query(1,1,n,1,dfn[i]-1).len;
		ans=max(ans,In+out+1);
	}
	cout<<ans;
}
```

---

## 作者：zhuweiqi (赞：0)

考虑枚举拆除的边，答案即为被断开的两个子树的直径之和加一，证明显然，这里主要考虑怎么维护。

令节点 $1$ 为根，求这一整棵树的直径如果不会请移步 [B4016](https://www.luogu.com.cn/problem/B4016)。在树形 dp 的过程中，我们需要记录几个值：他子树中离他最远的点与他的距离，他子树的直径（显然不包括在他上面的节点）。

考虑换根 dp。

第一次 dfs，先求出上面提到的两个值。

第二次换根 dp，从上至下依次转移，求出所有在他上面的节点（即不在他子树内部）中，距离他最远的点的距离，及由所有这些节点构成的子树的直径。重点在于换根的时候，我们要记录三个值，最远，次远，和第三远（非严格），我们递归下去的这个子树，他上面的直径不能由他祖先到他子树内部那个最远节点构成，所以对不同子树来说，他上面那棵子树的直径是不一样的，如果有重复的，比如说他子树内部那个距离等于最远的，那上面的直径就在于他二级祖先与次远加第三远之和的较大值。

综上，时空复杂度均为 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+2;
int ds[N],dd[N];
int us[N],ud[N];
int ans;
vector<int> e[N];
void dg(int x,int fa){
	if(x==1){
		int ms=0,ss=0,ts=0,fd=0,sd=0;
		for(auto y:e[x]){
			dg(y,x);
			ds[x]=max(ds[x],ds[y]+1);
			if(ds[y]+1>=ms) ts=ss,ss=ms,ms=ds[y]+1;
			else if(ds[y]+1>=ss) ts=ss,ss=ds[y]+1;
			else if(ds[y]+1>ts) ts=ds[y]+1;
			dd[x]=max(dd[x],dd[y]);
			if(dd[y]>=fd) sd=fd,fd=dd[y];
			else if(dd[y]>sd) sd=dd[y];
		}
		dd[x]=max(dd[x],ms+ss);
		ds[x]=ms;
		for(auto y:e[x]){
			if(fd==dd[y]) ud[y]=sd;
			else ud[y]=fd;
			int tmp=0;
			if(ms==ds[y]+1) tmp=ss+ts;
			else if(ss==ds[y]+1) tmp=ms+ts;
			else tmp=ms+ss;
			ud[y]=max(ud[y],tmp);
			if(ds[y]==ms-1) us[y]=ss+1;
			else us[y]=ms+1;
		}
		return;
	}
	int ms=0,ss=0;
	for(auto y:e[x]){
		if(y==fa) continue;
		dg(y,x);
		ds[x]=max(ds[x],ds[y]+1);
		if(ds[y]+1>=ms) ss=ms,ms=ds[y]+1;
		else if(ds[y]+1>ss) ss=ds[y]+1;
		dd[x]=max(dd[x],dd[y]);
	}
	dd[x]=max(dd[x],ms+ss);
	ds[x]=ms;
	return;
}
void dg0(int x,int fa){
	ans=max(ans,dd[x]+ud[x]+1);
	int ms=0,ss=0,ts=0,fd=0,sd=0;
	for(auto y:e[x]){
		if(y==fa) continue;
		if(ds[y]+1>=ms) ts=ss,ss=ms,ms=ds[y]+1;
		else if(ds[y]+1>=ss) ts=ss,ss=ds[y]+1;
		else if(ds[y]+1>ts) ts=ds[y]+1;
		if(dd[y]>=fd) sd=fd,fd=dd[y];
		else if(dd[y]>sd) sd=dd[y];
	}
	if(us[x]>=ms) ts=ss,ss=ms,ms=us[x];
	else if(us[x]>=ss) ts=ss,ss=us[x];
	else if(us[x]>ts) ts=us[x];
	for(auto y:e[x]){
		if(y==fa) continue;
		if(fd==dd[y]) ud[y]=sd;
		else ud[y]=fd;
		int tmp=0;
		if(ms==ds[y]+1) tmp=ss+ts;
		else if(ss==ds[y]+1) tmp=ms+ts;
		else tmp=ms+ss;
		ud[y]=max(ud[y],tmp);
		if(ds[y]==ms-1) us[y]=ss+1;
		else us[y]=ms+1;
	}
	for(auto y:e[x]){
		if(y==fa) continue;
		dg0(y,x);
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dg(1,0);
	ans=dd[1];
	for(auto y:e[1]) dg0(y,1);
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑枚举端的边是 $u \to v$，那么整棵树被分为了 $v$ 子树内和 $v$ 子树外，要添加一条边使得树的直径最大。

显然应该添加一条连接两个部分分别的直径的边，贡献是 $a + b + 1$，其中 $a$ 是 $v$ 子树外的树的直径，$b$ 是 $u$ 子树内的树的直径。

考虑树形 dp，令 $dp_{u, 0/1/2}$ 表示最远，次远和次次远的从 $u$ 出发向 $u$ 子树走的距离。

该部分较为简单，直接给出 Code：

```cpp
inline void dfs1(int u, int f){
	for(auto v : E[u]){
		if(v == f)
		  continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs1(v, u);
		if(dp[v][0] + 1 > dp[u][0]){
			dp[u][2] = dp[u][1];
			dp[u][1] = dp[u][0];
			dp[u][0] = dp[v][0] + 1;
		}
		else if(dp[v][0] + 1 > dp[u][1]){
			dp[u][2] = dp[u][1];
			dp[u][1] = dp[v][0] + 1;
		}
		else if(dp[v][0] + 1 > dp[u][2])
		  dp[u][2] = dp[v][0] + 1;
	}
}
```

然后考虑求出 $f_u$ 表示在 $u$ 子树内经过点 $u$ 的最长链长度，易得 $f_u = dp_{u, 0} + dp_{u, 1}$：

```cpp
	for(int i = 1; i <= n; ++i)
	  f[i] = dp[i][0] + dp[i][1];
```

然后再求出 $g_{u, 0/1}$ 表示 $u$ 的儿子中 $\max(g_{v, 0}, f_v)$ 的最大和次大值；即表示 $u$ 子树内除了 $u$ 节点 $f$ 的最大值和次大值：

```cpp
inline void dfs2(int u){
	for(auto v : E[u]){
		if(v == fa[u])
		  continue;
		dfs2(v);
		int w = max(f[v], g[v][0]);
		if(w > g[u][0]){
			g[u][1] = g[u][0];
			g[u][0] = w;
		}
		else if(w > g[u][1])
		  g[u][1] = w;
	}
}
```

然后回到刚开始的问题：

- 求出 $v$ 子树内的直径 $b$。

- 求出除 $v$ 子树外的直径 $a$。

容易得到 $b = \max(f_v, g_{v, 0})$，主要是如何求 $a$。

考虑 $a$ 能取到哪些点，首先是 $u$ 子树中除了 $v$ 子树内的点的直径；若 $\max(g_{v, 0}, f_v) = g_{u, 0}$，则贡献是 $g_{u, 1}$；否则是 $g_{u, 0}$。

还有穿过 $u$ 的链：

- 若 $dp_{v, 0} + 1 = dp_{u, 0}$，则链长是 $dp_{u, 1} + dp_{u, 2}$。

- 否则若 $dp_{v, 0} + 1 = dp_{u, 1}$，则链长是 $dp_{u, 0} + dp_{u, 2}$。

- 否则链长是 $dp_{u, 1} + dp_{u, 2}$。

最后不要忽略这种链：

- 令 $t_u$ 表示不经过 $v$ 子树的话子树内的最长链。

- 则还可能存在 $u$ 到 $u$ 的祖先 $fa$ 的链，长度是 $t_u + t_{fa} + dep_u - dep_{fa}$；只需要找到 $t_{fa} - dep_{fa}$ 的最大值即可。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 3e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, u, v, ans;
int dp[N][3], g[N][2], f[N], fa[N], dep[N];
vector<int> E[N];
inline void add(int u, int v){
	E[u].push_back(v);
	E[v].push_back(u);
}
inline void dfs1(int u, int f){
	for(auto v : E[u]){
		if(v == f)
		  continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs1(v, u);
		if(dp[v][0] + 1 > dp[u][0]){
			dp[u][2] = dp[u][1];
			dp[u][1] = dp[u][0];
			dp[u][0] = dp[v][0] + 1;
		}
		else if(dp[v][0] + 1 > dp[u][1]){
			dp[u][2] = dp[u][1];
			dp[u][1] = dp[v][0] + 1;
		}
		else if(dp[v][0] + 1 > dp[u][2])
		  dp[u][2] = dp[v][0] + 1;
	}
}
inline void dfs2(int u){
	for(auto v : E[u]){
		if(v == fa[u])
		  continue;
		dfs2(v);
		int w = max(f[v], g[v][0]);
		if(w > g[u][0]){
			g[u][1] = g[u][0];
			g[u][0] = w;
		}
		else if(w > g[u][1])
		  g[u][1] = w;
	}
}
inline void dfs3(int u, int Max, int _Max = -1e9){
	for(auto v : E[u]){
		if(v == fa[u])
		  continue;
		int h = (dp[v][0] + 1 == dp[u][0] ? dp[u][1] : dp[u][0]);
		int w = max(f[v], g[v][0]);
		int _now = max(_Max, h - dep[u]);
		if(u == 1){
			int now = max((g[u][0] == w ? g[u][1] : g[u][0]), (dp[v][0] + 1 == dp[u][0] ? (dp[u][1] + dp[u][2]) : (dp[u][0] + (dp[v][0] + 1 == dp[u][1] ? dp[u][2] : dp[u][1]))));
			dfs3(v, now, _now);
			ans = max(ans, now + w);
		}
		else{
			int now = max({Max, dep[u] + h + _Max, (g[u][0] == w ? g[u][1] : g[u][0]), (dp[v][0] + 1 == dp[u][0] ? (dp[u][1] + dp[u][2]) : (dp[u][0] + (dp[v][0] + 1 == dp[u][1] ? dp[u][2] : dp[u][1])))});
			dfs3(v, now, _now);
			ans = max(ans, now + w);
		}
	}
}
bool End;
int main(){
	n = read();
	for(int i = 1; i < n; ++i){
		u = read(), v = read();
		add(u, v);
	}
	dfs1(1, 1);
	for(int i = 1; i <= n; ++i)
	  f[i] = dp[i][0] + dp[i][1];
	dfs2(1);
	dfs3(1, 0);
	write(ans + 1);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

