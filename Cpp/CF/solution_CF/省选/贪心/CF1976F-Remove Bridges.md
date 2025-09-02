# Remove Bridges

## 题目描述

You are given a rooted tree, consisting of $ n $ vertices, numbered from $ 1 $ to $ n $ . Vertex $ 1 $ is the root. Additionally, the root only has one child.

You are asked to add exactly $ k $ edges to the tree (possibly, multiple edges and/or edges already existing in the tree).

Recall that a bridge is such an edge that, after you remove it, the number of connected components in the graph increases. So, initially, all edges of the tree are bridges.

After $ k $ edges are added, some original edges of the tree are still bridges and some are not anymore. You want to satisfy two conditions:

- for every bridge, all tree edges in the subtree of the lower vertex of that bridge should also be bridges;
- the number of bridges is as small as possible.

Solve the task for all values of $ k $ from $ 1 $ to $ n - 1 $ and output the smallest number of bridges.

## 样例 #1

### 输入

```
4
2
1 2
12
4 10
5 12
12 11
3 6
9 6
1 6
12 7
11 6
2 11
10 9
10 8
8
1 2
2 3
2 4
3 5
3 6
4 7
4 8
5
1 2
2 3
3 4
4 5```

### 输出

```
0 
7 3 1 0 0 0 0 0 0 0 0 
4 1 0 0 0 0 0 
0 0 0 0```

# 题解

## 作者：yshpdyt (赞：7)

## 题意
一棵根节点为 $1$ 的树，节点 $1$ 只有一个儿子，你可以加 $k$ 条边，且满足以下条件：
 - 对于每一条割边，该割边的下顶点的子树上的所有树边也应该是割边。
 - 使割边数量尽可能小。
 
 输出对于每个 $k\in[1,n-1]$ 的答案。
## Sol
~~这 F 怎么比 D 还水。~~

注意到节点 $1$ 只有一个儿子，所以其一定是割边的一端，先考虑第一条边如何加。

由于第一条限制，加的边的一端必须是 $1$。

由于第二条限制，加的边的另一端深度越大答案越优。

所以第一条边，两端分别是 $1$ 和深度最大点。

接着考虑连成环后如何处理。

注意到第一次选择的链将整棵树分成若干部分，如图。
![](https://cdn.luogu.com.cn/upload/image_hosting/3v1l71po.png)

根据刚才的思想，我们要选择**不在环上的部分**长度最长的链。对于一条链的情况，和刚才类似处理即可。对于分成多个部分，我们发现可以选择两个被红链分开的链，在两个链的叶子节点处加边，一次性可以减少两个部分的割边。

这样做一定合法，因为选中的两条链的顶端的 lca 在红链上。

这样做一定最优，如果能选一条链让答案最大，那么让这条链与另一个链结合，答案会更大。

选完第二条链后，红色部分扩大，仍然是分成若干蓝色部分，重复刚才的操作即可。

~~乱猜结论贪心题证明总是能写一大堆。~~

如何统计答案？每次的答案是选择两条满足叶子节点到红链最长的链，特别的第一次答案是选择深度最大的叶子节点。



注意到分成若干条链的情况和树链剖分很相似，到红链可以变成到链顶。由于每次选择的点和最大深度有关，考虑长链剖分的思想。

具体来说，优先去找深度最大的链，每次走到叶子节点，就把 $dep_x-dep_{top}+1$ 放入优先队列，最后每次选择长度最大的两个元素进行合并即可，特别的，第一次加边只应选择一个，且要答案减一，原因是 $1$ 没有父亲，也就没有到红链的距离这一说，就是深度最大点到 $1$ 的距离。

感觉说起来很抽象，还是看看代码吧。

时间复杂度 $O(n\log n)$。

##  Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 300005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
priority_queue<ll>q;
namespace sp{
    ll fa[N],dep[N],son[N],siz[N],len[N],top[N];
    vector<ll>v[N];
    void dfs(ll x,ll fat){
        len[x]=x;//子树内深度最大点的编号，如果是自己说明是叶子节点
        fa[x]=fat;
        dep[x]=dep[fa[x]]+1;
        for(auto y:v[x]){
            if(y==fa[x])continue;
            dfs(y,x);
            if(dep[len[x]]<dep[len[y]]){
                len[x]=len[y];
                son[x]=y;//类似重链剖分，为长儿子
            }
        }
    }
    void dfs2(ll x,ll tp){
        top[x]=tp;
        if(son[x])dfs2(son[x],tp);//先找长的链
        for(auto y:v[x]){
            if(y==fa[x]||y==son[x])continue;
            dfs2(y,y);
        }
        if(len[x]==x)q.push(dep[x]-dep[top[x]]+1);
    }

}using namespace sp;
ll n;
void sol(){
    cin>>n;
    while (!q.empty())q.pop();
    for(int i=1;i<=n;i++){
        fa[i]=dep[i]=son[i]=siz[i]=len[i]=top[i]=0;
        v[i].clear();
    }
    for(int i=1;i<n;i++){
        ll x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1,0);
    dfs2(1,1);
    ll res=n;//应该是n-1，但第一次要+1。
    auto t=q.top();
    q.pop();
    res-=t;
    cout<<res<<" ";
    for(int i=1;i<n-1;i++){
        if(q.size()>=1){
            t=q.top();
            q.pop();
            res-=t;
        }
        if(q.size()>=1){
            t=q.top();
            q.pop();
            res-=t;
        }
        cout<<res<<" ";
    }
    cout<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

### [CF1976F Remove Bridges](https://www.luogu.com.cn/problem/CF1976F)

由边双连通理论，若 $u, v$ 连通，则加入 $(u, v)$ 会导致任何 $u, v$ 之间的割边变成非割边。因此，题目转化为：在树上选择 $k$ 条链，满足

1. 若一条边没有被覆盖，则其子树内所有边没有被覆盖。
2. 被至少一条链覆盖的边尽可能多。

首先考虑 $k = 1$。因为题目保证根节点 $1$ 只有一个儿子 $x$，所以链的一端一定是 $1$，否则 $x$ 子树内有边被覆盖，但 $(1, x)$ 没有被覆盖，不合法。另一端选择任意深度最大的点。

- 当 $k$ 增大时，考虑所有被覆盖的边形成的结构。这个结构一定包含 $1$，且除了 $1$ 以外至多有 $2k - 1$ 个叶子，因为只有链的两端可能作为叶子，且 $1$ 一定是某条链的一段。对于除了 $1$ 以外的叶子，如果它在原树上不是叶子，那么一定可以将以它为一端的链向下延伸，覆盖更多边。

- 有经典结论：给定树上的不超过 $2k$ 个点，一定存在 $k$ 条链，这些链的并集恰好是这些点形成的虚树。[证明](https://www.luogu.com.cn/article/86z5823v)。

- 选定 $2k - 1$ 个叶子，它们到根的路径并集符合题目限制一。

结合上述三条观察，题目转化为：在树上选 $2k - 1$ 个叶子，使得它们到根的路径并所覆盖的边（等价于覆盖的点）尽可能多。这是经典问题，长链剖分后贪心即可。

时间复杂度 $\mathcal{O}(n\log n)$。换成桶排即可线性。[代码](https://codeforces.com/contest/1976/submission/265627549)。

---

## 作者：Rosabel (赞：5)

应该会比 yshpdyt 的实现略微简单。

考虑直接贪心。每次选取两个叶子连边。因为若连的是非叶子节点那么选取某该节点所在子树的叶子结点绝对不劣（可以多覆盖几条边）。

每次选取叶子连边的时候一定是选择之前没连过边的叶子，若是选已经连过边的叶子，那么总是存在至少一个另外的没连过边的叶子使得其覆盖原路径上的所有边。

很容易发现选取的叶子 $u,v$ 到 $lca$ 的两条路径都为这种形式 ```lca - X - X - ... - X - O - O - ... - O - u/v```，其中 ```X``` 和 ```O``` 表示每条边已经被覆盖（即非桥边）和尚未被覆盖（即桥边）。很容易发现此时 $lca$ 的位置已经不重要。我们只关心 ```X``` 和 ```O``` 交界的点所可以通过全为 ```O``` 路径到达的节点的深度。

考虑贪心。选择当前最长深度的叶子即可。那么通过观察很容易发现深度单调递减。这是因为若出现比上一个覆盖的叶子深度更深的叶子那么交换顺序更优。

一个很经典的 trick 是自底向上贪心，每次选取最大的点向上更新，其他的就留在该子树中存进预选数组中。根节点特殊处理。树遍历完把预选数组（此时存的是删除叶节点的最大深度和）的所有元素降序排序，除了第一次从数组拿出最大元素（根节点特殊处理）每次拿出最大值和次大值作为当前答案即可。

可以保证若预选数组元素个数 $\ge 2$ 那么必可以选出 $2$ 个值使得所有被选叶子到根的路径上的所有边都被覆盖过。若出现剩余一棵完整的子树（这是特殊情况，即该子树的所有边都没被覆盖，包括子树根到父亲的边）那么选出两个叶节点会导致子树根到父亲的边未被覆盖不满足刚才的保证。其实只需要交换一下涉及到父亲的路径所在端点二元组的其中一个元素和两个叶节点其中一个叶节点就能保证路径在子树根和父亲的边上交叉，即该边被覆盖到。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
vector<int>E[N];
int n,m,a[N],f[N],tmp[N];
bool cmp(int A,int B){
    return A>B;
}
void dfs(int u,int fa){
    for(int i=0;i<E[u].size();i++){
        int v=E[u][i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
    }
    int p=0;
    for(int i=0;i<E[u].size();i++){
        int v=E[u][i];
        if(v==fa){
            continue;
        }
        tmp[++p]=f[v]+1;
        // printf("u=%d v=%d %d\n",u,v,tmp[p]);
    }
    sort(tmp+1,tmp+p+1,cmp);
    if(u==1){
        a[++m]=tmp[1];
        return;
    }
    if(!p){
        f[u]=0;
        return;
    }
    f[u]=tmp[1];
    for(int i=2;i<=p;i++){
        a[++m]=tmp[i];
    }
}
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        E[i].clear();
    }
    m=0;
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1,0);
    sort(a+1,a+m+1,cmp);
    int res=n-1;
    for(int i=1;i<=2*n-3;i++){
        if(i<=m){
            res=res-a[i];
        }
        if(i&1){
            printf("%d ",res);
        }
    }
    printf("\n");
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：hegm (赞：4)

首先我们不妨转化一下题意，首先树上每个边都是割边，一旦我们连接了两节点 $x,y$，那么对应的树上路径 $x\to y$ 的所有边都会变化为非割边。

所以我们每次操作本质上是选定树上一条路径覆盖。

考虑合法状态本质，也就是说对于一条边，如果他没被覆盖，那么他的子树内也不能有覆盖边。

因此我们的状态本质是一个连通块，并且这个连通块一定包含根。

现在考虑如何用 $k$ 次覆盖路径达到一个合法且最大的状态。

路径覆盖过于麻烦，所以我们不妨转化为形成一个连通块，其有 $x$ 个叶子（度数为 $1$ 的节点）。显然 $x$ 个叶子的连通块可以用 $\left\lceil\dfrac{x}{2}\right\rceil$ 次路径覆盖形成。

现在问题转化为对于每一个 $x$ 求出恰好有 $x$ 个叶子并且包含 $1$ 的连通块最大是多少。

这玩意看着就像可以贪心的搞，这里我们不妨证明一下。

考虑 $k=i$ 的情况，我们已经得到了一个最大的连通块。

![](https://cdn.luogu.com.cn/upload/image_hosting/r1nzl673.png)

如图，假定 $k=1$，显然我们 $k=1$ 的最大连通块为 $\text{\color{red}红色}$ 路径。

考虑对于每一个节点  $i$，我们维护出其子树内部最深（之一）的叶子是谁称之为 $son_i$。

每次，我们将和当前连通块相邻的节点 $i$ 放进集合 $S$ 中。

我们将 $S$ 集合按照 $\text{dep}_i-\text{dep}_{son_i}$ 从大到小排序。每次将权值最大的 $i$ 提取出来，将 $son_i\sim i$ 这条路径上的节点加入到连通块里，并且更新 $S$ 集合。

考虑证明其为什么是对的，首先，对于一个已经加入集合的节点，在没有选择它的时候，不管外界作何选择，绝对不会影响其答案。

对于一次选择 $i\to son_i$，我们的贡献理论上应该是 $w_i$，对于因为这次选择而更新出的节点 $x$，显然 $w_x<w_i$ 如若不然，那么就违背了 $son_i$ 是 $i$ 子树内最深的节点。

因此我们纵观整个流程，每次取出契合中最大的权值，然后会新形成一些比其小的权值塞入集合中。因此无需策略，只需要无脑的选择最大即可更新出答案。

代码直接模拟这个过程就行。

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define make make_pair
#define pii pair<int,int> 
#define N 600005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,dep[N],ans,son[N],f[N],p[N],cnt;
bool vis[N];
vector<int> v[N];
priority_queue<pii> q;
void dfs(int now,int fa)
{
	son[now]=now;
	f[now]=fa;dep[now]=dep[fa]+1;
	for(int x:v[now])
	{
		if(x==fa)continue; 
		dfs(x,now);
		if(dep[son[x]]>dep[son[now]])
		son[now]=son[x];
	}
}
void add(int x)
{
	q.push(make(dep[son[x]]-dep[x],son[x]));
}
void sol(int x)
{
	while(!vis[x])
	{
		vis[x]=1;
		for(int y:v[x])if(!vis[y]&&y!=f[x])add(y);
		x=f[x];ans--;
	}
}
signed main()
{
	int T=read();
	while(T--)
	{
		n=read();ans=n;cnt=0;
		for(int i=0;i<=n;i++)v[i].clear(),vis[i]=0;vis[0]=1;
		for(int i=1,a,b;i<n;i++)
		{
			a=read();b=read();
			v[a].push_back(b);
			v[b].push_back(a);
		}
		dfs(1,0);
		sol(son[1]);
		p[++cnt]=ans;
		while(q.size())
		{
			sol(q.top().se);
			p[++cnt]=ans;
			q.pop();
		}
		for(int i=1;i<n;i++)cout<<p[2*i-1]<<" ";cout<<"\n";
		for(int i=1;i<=cnt;i++)p[i]=0;
	}
	return 0;
}

```

---

## 作者：_Cheems (赞：2)

upd：差不多一年后重新看这题，发现完全是套路啊。

题意：$n$ 个点的树，以 $1$ 为根，且 $1$ 只有一个儿子。可以加 $k$ 条边，要满足割边下端的子树内不存在非割边，对 $k\in [1,n)$，求最少割边数量。

考虑加入边 $(u,v)$，等价于让树上 $u\to v$ 路径的所有边变成非割边。那么这就变成了染色问题，选择 $k$ 条路径染色，满足未被染色的边下面的所有边也未被染色，并且染色边尽量多。

可以发现，选取路径的两端必然是叶子节点或 $1$，否则可以不断向下伸长路径，显然这不会影响合法性。因为从完整的子树中抽出一条顶端到叶子的链，剩下的也是完整子树。

注意到 $1$ 只有一个儿子，所以 $k=1$ 的答案是 $1$ 到叶子的一条最长链。


#### 原思路
对于一般情况，可以发现原树被已染色的边，划分为多个完整的、未被染色的子树，不难想到贪心：从中选取两条最长链拼接，最长是指未被染色的边尽量多。

假如选取的两条链来自不同子树，那么其构成的路径一定合法。但是来自同一棵子树怎么办？假设之前操作了 $(u,v)$，现在想操作 $(x,y)$，可以发现，更改操作为 $(u,x),(v,y)$ 后，就变得合法了。

所以可以拿个优先队列存剩下所有子树的最长链，除第一次以外，均选 $2$ 条最长链即可。由于每个点只被遍历一次、加入一次，所以复杂度 $O(n\log n)$。

不难感性理解，口胡下正确性：交换（时间上）相邻两条链的选取顺序，不会影响合法性，所以可以交换使得选取的链长递减，即每次选最长链。
#### 新思路
无论怎么操作，操作端点集合一定是至多 $2k$ 个叶子。有经典结论：可以用不超过 $k$ 条链，恰好覆盖 $2k$ 个叶子的虚树。这是覆盖点数的上界了，同时一定满足题意（以虚树的视角看待，就是链上挂着一些完整子树），所以这么干。

这题甚至傻乎乎地告诉你 $1$ 一定被操作，那就更容易了，经典长剖贪心即可。$O(n\log n)$ 或 $O(n)$。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define pir pair<int, int>
const int N = 3e5 + 5;
int T, n, k, u, v, fa[N], ans;
int f[N], leaf[N]; 
vector<int> to[N];
struct node{int u, leaf, w;};
inline bool operator < (const node& A, const node& B) {return A.w < B.w;}
priority_queue<node> s; 

inline void init(int u){
	f[u] = 0, leaf[u] = u;
	for(auto v : to[u])
		if(v ^ fa[u]){
			fa[v] = u, init(v);
			if(f[v] + 1 > f[u]) f[u] = f[v] + 1, leaf[u] = leaf[v]; 
		} 
}
inline void upd(node p){
	int u = p.u, pos = p.leaf, lst = -1; ans -= p.w;
	while(lst != u){
		for(auto v : to[pos])
			if(v != lst && v != fa[pos]) s.push({v, leaf[v], f[v] + 1});
		lst = pos, pos = fa[pos];
	}
}
inline void doit(){
	if(!s.empty()){
		node A = s.top(); s.pop();
		upd(A);
	}
}
signed main(){
	cin >> T;
	while(T--){
		while(!s.empty()) s.pop();
		scanf("%d", &n), ans = n - 1;
		for(int i = 1; i <= n; ++i) to[i].clear();
		for(int i = 1; i < n; ++i) scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
		init(1), s.push({1, leaf[1], f[1]});
		for(int i = 1; i < n; ++i){
			doit();
			if(i != 1) doit();
			printf("%d ", ans);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：紊莫 (赞：1)

标签：贪心

给出一种代码略长但是无脑的做法。

首先发现第一次一定要连接 $1$ 号点和另一个点，那么一定是连接深度最大的点，我们定义 $val_i$ 表示 $i$ 到根的路径上桥边的个数，也就是说选出 $val$ 最大的位置，然后我们暴力去更新它到根上的所有边，直到遇到非桥边或者到根。

这样的话复杂度是均摊 $O(n)$ 的，因为每条边只会被遍历一次。

然后对于剩下的操作，我们显然每次取出两个 $val$ 最大的值，然后将这条路径上的点暴力更新，证明其他题解已有，不再赘述。

此处我们可以直接用线段树来维护 $val$ 值，首先按照 dfs 序拍平序列，然后每一次标记一条边，就会把下面子树的 $val$ 全都减一，这样就好了。

时间复杂度 $O(n \log n)$，[代码](https://codeforces.com/contest/1976/submission/268253391)是 VP 的时候写的，比较混乱。

---

## 作者：RainWetPeopleStart (赞：0)

做的时候对假贪心调了 0.5h，然后意识到可以直接长链剖分。

首先，如果你想使桥边数为 $0$，那么每一次配对两个一度点一定最优，记一度点个数为 $c$，最小的 $k$ 就是 $\lceil\frac{c}{2}\rceil$。

接下来，考虑增加桥边以减少一度点数。

你发现你不能直接删叶子，因为可能会产生新的一度点。

但是你可以修这一个做法，把树剖成若干条链，每次选长度最小的链（增加的桥边最小）即可。

由于链长总和一定，你需要尽可能的把短的链变得更短，长的链变得更长，容易发现这等价于长链剖分，做完了。


```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define bi __int128_t
using namespace std;
const int N=3e5+10,B=300;
int n;
vector<int> E[N];
int du[N];int fa[N];
int ans[N],h[N],son[N];
int c[N],top=0;
void dfs(int u,int pr){
    fa[u]=pr;
    for(auto v:E[u]){
        if(v==pr) continue;
        dfs(v,u);
        h[u]=max(h[u],h[v]);
    }h[u]++;
    for(auto v:E[u]){
        if(v==pr) continue;
        if(h[v]+1==h[u]){
            son[u]=v;break;
        }
    }
}void dfs2(int u,int pr,int len){
    for(auto v:E[u]){
        if(v==pr) continue;
        if(v==son[u]) dfs2(v,u,len+1);
        else dfs2(v,u,1);
    }
    if(u!=1&&du[u]==1) c[++top]=len;
}
void slv(){
    cin>>n;
    for(int i=1;i<=n;i++) du[i]=0,h[i]=0,E[i].clear();top=0;
    for(int i=1;i<n;i++){
        ans[i]=0;
        int u,v;cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
        du[u]++;du[v]++;
    }dfs(1,0);dfs2(1,0,1);
    int leaf=0;
    for(int i=1;i<=n;i++) if(du[i]==1) leaf++;
    int now=(leaf+1)/2,res=0;sort(c+1,c+top+1);
    //for(int i=1;i<=n;i++) cout<<son[i]<<' ';cout<<endl;
    for(int i=1;i<=top;i++){
        leaf--;res+=c[i];
        if((leaf+1)/2<now){
            now--;ans[now]=res;
        }
    }
    for(int i=1;i<n;i++) cout<<ans[i]<<' ';cout<<endl;
}
int main(){
    int t;cin>>t;while(t--) slv();
    return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有一个 $n$ 个点的树，根节点为 $1$，且根节点的度数也为 $1$。

你需要在图上任意两点连接 $k$ 条边（允许重边），使得对于每一条割边，在树上深度较大的端点的子树内的所有边都是割边。在此限制下，要求整个图的割边数量最少。

对于所有 $k\in[1,n]$，输出此时图中的割边数量最小值。

$T$ 组数据。$2\leq n,\sum n\leq 3\times 10^5$。

## 思路

先来转化题意，当我们在 $u,v$ 间连接一条边时，路径 $(u,v)$ 时都不再是割边了，所以问题可以转换为对 $k$​ 条路径上的所有边进行覆盖，使得若一条边被覆盖，则这条边上的一端点到根的路径上的所有边均被覆盖。我们要求覆盖的边尽可能多。

接着，我们考虑 $k=1$ 的情况，由于根节点度数为 $1$，故我们只能选择根节点为端点的一条最长链。

然后考虑 $k=2$，此时我们还需要选择一条链进行覆盖，不同的是此时我们不一定需要让路径端点为根节点了，只需要端点的 LCA 在第一条链上即可。对于一般的情况，我们只需要选择两条链，并且这两条链的 LCA 到根的路径上的所有边都被覆盖即可。这个性质很像长链剖分，于是可以将树长链剖分一下（其实如果你做题足够多的话，已经可以看出一个正确且经典的贪心了）。下面是将样例的第二组数据的树进行长链剖分后得到的结果：

![](https://cdn.luogu.com.cn/upload/image_hosting/203phgui.png?x-oss-process=image/resize,p_75)

对于第一个路径，我们显然选择最长链，对于第二个路径我们可以选择次长链和次次长链。可以得到一个规律：对于 $k$，我们只需要选前 $2k-1$ 长链即可。

至于这样的正确性证明，最优性是显然的，至于合法性，由于链剖分的性质，当我们选择一条链时，顶端的父亲一定选过了（因为包含它的链比这条链更长）。

于是可以用一个大根堆维护长链信息，时间复杂度 $O(Tn\log n)$。

注意一个小细节，除了顶端为根的链之外，其余链的贡献应该是链的底端减去**顶端的父节点**的深度。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, dep[N], hgt[N], son[N], top[N], len[N];
vector<int> g[N];

void dfs1(int u, int fa){
    dep[u] = dep[fa] + 1;
    for(int v : g[u]){
        if(v == fa) continue;
        dfs1(v, u);
        if(hgt[u] < hgt[v] + 1) hgt[u] = hgt[v] + 1, son[u] = v;
    }
}

void dfs2(int u, int fa){
    len[top[u]] = max(len[top[u]], dep[u] - dep[top[u]] + (top[u] != 1));
    if(son[u]) top[son[u]] = top[u], dfs2(son[u], u);
    for(int v : g[u]){
        if(v == fa || v == son[u]) continue;
        top[v] = v, dfs2(v, u);
    }
}

void solve(){
    cin >> n;
    for(int i=1,x,y;i<n;i++){
        cin >> x >> y;
        g[x].push_back(y), g[y].push_back(x);
    }
    top[1] = 1;
    dfs1(1, 0), dfs2(1, 0);
    priority_queue<int> q;
    for(int i=1;i<=n;i++) q.push(len[i]);
    int cnt = n - 1;
    cout << (cnt -= q.top()) << ' ';
    q.pop();
    for(int i=2;i<n;i++){
        int x = 0, y = 0;
        if(!q.empty()) x = q.top(), q.pop();
        if(!q.empty()) y = q.top(), q.pop();
        cout << (cnt -= x + y) << ' ';
    }
    cout << '\n';
}

void clear(){
    for(int i=1;i<=n;i++){
        g[i].clear();
        dep[i] = hgt[i] = son[i] = top[i] = len[i] = 0;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t; cin >> t;
    while(t--) solve(), clear();
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：daniEl_lElE (赞：0)

容易发现第一次显然会选深度最深的链的两端连接。

在每一个后一次操作中，不再需要选一条从上到下的链，于是，我们可以选择两条链并拼接他们，得到新加入的路径。

于是，大致的思路就是，对树进行长链剖分，每次加入一条链将这条链上的所有点开始的向下的链加入 priority_queue，每次取出 priority_queue 中最长的两条链两端连接起来并作为这一次的加入。

然而，还有一种特殊情况：每一次加入的两条边可能满足：

* $u$ 为已经覆盖过的点。
* $(u,v)$ 为一条路径，上面有一个不为 $u$ 的点 $w$；
* $(w,z)$ 为另一条路径。

考虑这样为何合法，注意到至少从上到下经过 $u$ 的路径。将这条路径断开并连接 $v$ 和 $z$，即可添加长度为 $(u,v)$ 和 $(w,z)$ 的两条链。

这种情况的本质是需要先将一条链对应的向下的链加入 priority_queue 再去选下一条链。稍作修改即可。

总复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> vc[1000005];
int maxdep[1000005];
int son[1000005],cnt;
vector<int> bc[1000005];
vector<int> lc[1000005];
void dfs0(int now,int fa){
	son[now]=0;
	maxdep[now]=1;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs0(v,now);
		if(maxdep[v]>=maxdep[now]){
			son[now]=v;
			maxdep[now]=maxdep[v]+1;
		}
	}
}
int dfs1(int now,int fa,int bel){
	if(!bel) bel=++cnt;
	bc[bel].push_back(now);
	if(son[now]) dfs1(son[now],now,bel);
	for(auto v:vc[now]){
		if(v==fa||v==son[now]) continue;
		lc[now].push_back(dfs1(v,now,0));
	}
	return bel;
}
void solve(){
	cnt=0;
	int n; cin>>n;
	for(int i=1;i<=n;i++) vc[i].clear(),bc[i].clear(),lc[i].clear();
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs0(1,0);
	int st=dfs1(1,0,0);
	priority_queue<pair<int,int>> pq;
	int tot=n-1,tr=0;
	pq.push(make_pair(bc[st].size(),st));
	while(!pq.empty()){
			int f=pq.top().second; pq.pop();
			tot-=bc[f].size()-(st==f);
			for(auto x:bc[f]){
				for(auto v:lc[x]){
					pq.push(make_pair(bc[v].size(),v));
				}
			}
			if(pq.size()!=0&&tr!=0){
				int f=pq.top().second; pq.pop();
				tot-=bc[f].size()-(st==f);
				for(auto x:bc[f]){
					for(auto v:lc[x]){
						pq.push(make_pair(bc[v].size(),v));
					}
				}
			} 
			cout<<tot<<" ";
			tr++;
	}
	while(tr!=n-1){
		cout<<tot<<" ";
		tr++;
	}
	cout<<"\n";
}
signed main(){
	int t; cin>>t; while(t--) solve();
	return 0;
}
```

---

## 作者：MiniLong (赞：0)

经典题。考虑根度数是 $1$，所以第一次肯定是选从根开始的一条路径，那肯定就是最深的那个叶子。然后第二次就可以选两个到根的链，也一定是两个叶子（选两个原因：有个经典结论是在树上选 $2k$ 个点一定存在 $k$ 条链并集是它们的虚树），这个就是 BZOJ3252，长剖之后每个叶子的权值就是它到链头的长度，排个序就好了。复杂度 $\Theta(n\log n)$，瓶颈在排序。

---

