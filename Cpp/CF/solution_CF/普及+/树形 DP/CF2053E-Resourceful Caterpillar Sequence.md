# Resourceful Caterpillar Sequence

## 题目描述

无尽的七日轮回

— r-906, [Panopticon](https://www.youtube.com/watch?v=_-Vd0ZGB-lo)

在一个由 $n$ 个顶点组成的树中，定义了一种“毛毛虫”。一个毛毛虫用整数对 $(p, q)$（$1 \leq p, q \leq n$，且 $p \neq q$）表示，它的头在顶点 $p$，尾在顶点 $q$，并且该毛毛虫支配从 $p$ 到 $q$ 的简单路径上的所有顶点（包括 $p$ 和 $q$）。$(p, q)$ 的毛毛虫序列是按到 $p$ 的距离递增排序后的路径上的顶点序列。

Nora 和 Aron 轮流移动这条毛毛虫，Nora 先手。两个人都采用各自的最优策略来进行游戏：

- 他们会尽全力争取胜利；
- 如果无法赢得胜利，他们将努力阻止对方获胜（这样，游戏就会以平局收场）。

在 Nora 的回合中，她需要从与顶点 $p$ 相邻且未被毛毛虫支配的顶点中选择一个 $u$，然后将毛毛虫向顶点 $u$ 移动一个边。同样，在 Aron 的回合中，他需要从与顶点 $q$ 相邻且未被毛毛虫支配的顶点中选择一个 $v$，并将毛毛虫向顶点 $v$ 移动一个边。注意，两位玩家的移动方式是不同的。

若 $p$ 是叶子节点时，Nora 赢得胜利。而当 $q$ 是叶子节点时，Aron 赢得胜利。如果初始时 $p$ 和 $q$ 都是叶子，或经过 $10^{100}$ 回合游戏仍未结束，最终结果为平局。

请统计能让 Aron 赢得游戏的整数对 $(p, q)$ 的数量：$1 \leq p, q \leq n$ 且 $p \neq q$。

*用简单的话来说：当前的毛毛虫序列是 $c_1, c_2, \ldots, c_k$，移动后，新序列变为 $d(u, c_1), d(u, c_2), \ldots, d(u, c_k)$。这里，$d(x, y)$ 表示从 $y$ 到 $x$ 的简单路径上的下一个顶点。

*在树中，一个顶点的度数为1时，该顶点称为叶子节点。

*因此，只要游戏未结束，Nora 总能找到一个顶点 $u$ 来进行移动。Aron 也是一样。

## 说明/提示

在第一个测试例中，所有可能的毛毛虫是 $(1, 2)$ 和 $(2, 1)$。由于初始时 $p$ 和 $q$ 都是叶子，因此结果为平局。

在第二个测试例中，满足 Aron 赢得游戏的毛毛虫包括：$(1, 3)$、$(1, 4)$、$(1, 5)$、$(2, 3)$、$(2, 4)$、$(2, 5)$。下面我们来具体分析一些毛毛虫的情况：

- 对于毛毛虫 $(1, 5)$：顶点 $p = 1$ 不是叶子，而 $q = 5$ 是叶子，因此 Aron 在一开始就胜利。
- 对于毛毛虫 $(2, 1)$：顶点 $p = 2$ 不是叶子，$q = 1$ 也不是叶子。在 Nora 的第一次移动中，她可以选择将毛毛虫移向顶点 $5$，此时毛毛虫变为 $(5, 2)$，顶点 $p = 5$ 是叶子，因此 Nora 在下一步中胜利。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
1 2
5
1 2
1 3
2 4
2 5
12
1 6
11 2
4 8
12 3
2 7
6 12
8 1
2 3
5 12
9 2
10 3
10
1 2
2 3
3 4
4 5
5 6
4 7
6 8
4 9
4 10
25
1 16
11 22
6 14
3 1
20 14
23 17
25 19
10 11
3 18
10 6
2 21
4 5
11 12
4 9
9 13
8 6
6 1
3 7
8 19
10 24
15 13
1 2
3 4
17 8```

### 输出

```
0
6
40
27
171```

# 题解

## 作者：I_will_AKIOI (赞：12)

首先考虑一条怎样的毛毛虫，二者能分出胜负。先考虑第一种情况，开局就可以分出胜负：

+ 当 $p,q$ 都是叶子，平局。

+ 否则如果 $p$ 为叶子，Nora 获胜。

+ 否则如果 $q$ 为叶子，Aron 获胜。

接着就是二者需要移动毛毛虫的情况。

+ 如果 $p$ 相邻的节点有叶子，Nora 获胜。

+ 否则 Nora 只能移动到非叶子的点上，那么 $q$ 就会移动到当前毛毛虫的倒数第二个节点，如果这个点相邻的点有叶子，那么 Aron 就能获胜。

+ 否则二人就会把毛毛虫来回扯皮，无法分出胜负，平局。

接着考虑统计 Aron 获胜的方案数。对于第一种情况，设叶子个数为 $cnt$，Aron 获胜当且仅当那么 $p$ 是叶子，$q$ 不是叶子，乘法原理得答案为 $cnt\cdot(n-cnt)$。

对于第二种情况，考虑枚举毛毛虫尾巴 $q$，再枚举 $q$ 相邻的节点 $k$，这里要求 $k$ 相邻的点有叶子，Aron 才能获胜。接下来就需要确定毛毛虫的头 $p$，显然 $p$ 只能在以 $k$ 为根的子树内，并且 $p$ 相邻的点不能是叶子，否则 Nora 就获胜了，所以 $k$ 对答案的贡献就是以 $k$ 为根的子树内不和叶子相邻节点的个数。

现在我们需要维护 $k$ 为根的子树内不和叶子相邻节点的个数。设 $vis_i\in\{0,1\}$ 表示 $i$ 相邻的点是否有叶子，接着就可以给树做一遍后缀和，求得 $sum_i$，表示以 $i$ 为根的子树内的节点 $j$ 的 $vis_j$ 之和。那么子树内不和叶子相邻节点的个数就等于子树大小 $sz_i$ 减去 $sum_i$。

但是和 $i$ 相邻的节点不仅有自己的孩子，还有自己的父亲，这种情况可以换根，用整棵树减去子树，就可以得到以父亲为根的贡献。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
#pragma GCC optimize("O3")
using namespace std;
int n,res,cnt,sum[N],f[N],sz[N];
bool vis[N];
vector<int>v[N];
void dfs(int k,int fa)
{
  f[k]=fa;
  sz[k]=1;
  sum[k]=vis[k];
  for(int now:v[k])
  {
    if(now==fa) continue;
    dfs(now,k);
    sum[k]+=sum[now];
    sz[k]+=sz[now];
  }
  return;
}
void solve()
{
  cin>>n;
  cnt=0;
  for(int i=1;i<=n;i++) v[i].clear(),vis[i]=0;
  for(int i=1;i<n;i++)
  {
    int x,y;
    cin>>x>>y;
    v[x].push_back(y);
    v[y].push_back(x);
  }
  for(int i=1;i<=n;i++)
  {
    if(v[i].size()>1) continue;
    cnt++;
    vis[i]=1;
    for(int j:v[i]) vis[j]=1;
  }
  res=cnt*(n-cnt);//情况1
  dfs(1,0);
  for(int i=1;i<=n;i++)
  {
    int tot1=0,tot2=0;
    if(v[i].size()==1) continue;
    for(int j:v[i])//子节点的贡献
    {
      if(j==f[i]||vis[j]==0||v[j].size()==1) continue;
      tot1+=sz[j]-sum[j];
    }
    if(i!=1&&vis[f[i]]&&v[f[i]].size()>1) tot2+=(n-sz[i])-(sum[1]-sum[i]);//父亲节点的贡献
    res+=tot1+tot2;
  }
  cout<<res<<"\n";
  return;
}
signed main()
{
  ios::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：ARIS2_0 (赞：3)

### 前言

可惜没有参赛，不然 5A 涨大分。

### 结论

对于点对 $(p,q)$，它是符合条件的，当且仅当满足以下两个条件之一：

1. $q$ 为叶子节点且 $p$ 不为叶子节点

2. $q$ 往 $p$ 的方向移动一格后，与一个叶子节点相邻，且 $p$ 距离任意叶子节点的距离不小于 $2$。

### 证明

第一点是显然的。

第二点中，$p$ 距离任意叶子节点的距离不小于 $2$ 也是显然的，不然先手走一步或不走就赢了。

因为每位玩家必须动，所以先手动后，**$q$ 必然会往 $p$ 的方向移动一格**。若此时 $q$ 不与叶子节点相邻，则后手的这次操作无论向哪，**一定不会获胜**。

而后手动后，$q$ 向远离 $p$ 的方向动一格，**而 $p$ 又会被拉回原来的位置**。

而先手继续动的话，$q$ 又会回到**先手第一次动后的位置**。

就这样来回循环，最后**必然平局**。

而若 $q$ 往 $p$ 的方向移动一格后，与一个叶子节点相邻，那么在先手进行第一步后，后手能**直接进入叶子节点**从而获胜。

证毕。

### 代码实现

考虑对于每个 $q$ 计算有多少合法的 $p$。

首先用 BFS 计算每个节点离距离最近的叶子节点的距离 $dist_i$。

然后进行第一遍 DFS，求出每个子树的大小 $size_i$，每个子树中满足 $dist_i=0$ 的节点的个数 $lf_i$，每个子树中满足 $dist_i=1$ 的节点的个数 $pf_i$。

然后进行第二次 DFS。

对于节点 $x$ 的每条出边的点 $y$（包括 $x$ 的祖先），若 $dist_y=1$，则钦定 $p$ 为子树 $y$ 中的节点，$q$ 为 $x$ 的情况下，有以下这么多情况是合法的：

$$\begin{cases}size_y-lf_y,dist_x=0\\size_y-lf_y-pf_y,dist_x\not=0\end{cases}$$

其中，$dist_x=0$ 对应结论中的点 $1$，$dist_x\not=0$ 对应结论中的点 $2$。

若 $dist_y\not=1$，对应 $q$ 不与叶子节点相邻的情况，对答案没有贡献。

对于 $x$ 的祖先 $fa$，可以用换根法求出以 $x$ 为根时的 $size_{fa},lf_{fa},pf_{fa}$，然后带入计算。

一组测试样例时间复杂度 $O(n)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e16,maxn=2e5+10;
vector<int>v[maxn];
int deg[maxn],dist[maxn];
queue<int>q;
void bfs(int n){
    while(q.size())q.pop();
    for(int i=1;i<=n;i++){
        dist[i]=(deg[i]==1?0:inf);
        if(!dist[i])q.push(i);
    }
    while(q.size()){
        int x=q.front();q.pop();
        for(int y:v[x]){
            if(dist[y]==inf)dist[y]=dist[x]+1,q.push(y);
        }
    }
}
int ans=0,sizes[maxn],fa[maxn],lf[maxn],pf[maxn];
void dfs1(int x,int fat){
    sizes[x]=1;
    fa[x]=fat;
    if(dist[x]==0){
        lf[x]=1;
    }
    else lf[x]=0;
    if(dist[x]==1){
        pf[x]=1;
    }
    else pf[x]=0;
    for(int y:v[x]){
        if(y!=fa[x]){
            dfs1(y,x);
            sizes[x]+=sizes[y];
            lf[x]+=lf[y];
            pf[x]+=pf[y];
        }
    }
}
int n;
void dfs(int x){
    for(int y:v[x]){
        if(y!=fa[x]){
            dfs(y);
            if(dist[y]==1){
                if(dist[x]==0){
                    ans+=sizes[y]-lf[y];   
                    // cout<<"debug "<<x<<" "<<y<<" "<<size[y]-lf[y]<<"\n";
                }
                else ans+=sizes[y]-lf[y]-pf[y];
                // cout<<"debug "<<x<<" "<<y<<" "<<size[y]-lf[y]-pf[y]+1<<"\n";
            }
        }
    }
    if(fa[x] and dist[fa[x]]==1){
        if(dist[x]==0){
            ans+=(sizes[1]-sizes[x])-(lf[1]-lf[x]);
            // cout<<"debug "<<x<<" "<<fa[x]<<" "<<(size[1]-size[x])-(lf[1]-lf[x])<<"\n";
        }
        else ans+=(sizes[1]-sizes[x])-(lf[1]-lf[x])-(pf[1]-pf[x]);
        // cout<<"debug "<<x<<" "<<fa[x]<<" "<<(size[1]-size[x])-(lf[1]-lf[x])-(pf[1]-pf[x])+1<<"\n";
    }
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)deg[i]=0,v[i].clear(),sizes[i]=0;
        for(int i=1,p,q;i<n;i++){
            cin>>p>>q;
            deg[p]++;deg[q]++;
            v[p].push_back(q);
            v[q].push_back(p);
        }
        bfs(n);
        ans=0;
        dfs1(1,0);
        dfs(1);
        cout<<ans<<"\n";
    }
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

博弈论可爱！永远爱博弈论姐姐！

## Solution

先把 $q$ 为叶子的情况统计上，然后我们注意力惊人可以发现，无论怎么着，$p,q$ 活动的范围都很小，因为一方一往前走就会被另一方拉回去（无论另一方往哪走），具体地，$q$ 的活动范围只有与 $d(q,p)$（与题目中的不同，这里表示的是将 $q$ 向 $p$ 移动一步，因为这样更好理解）相邻的结点（$p$ 也一样，但不重要）。又因为不能选择不移动，于是只要与 $d(q,p)$ 相邻的节点中有叶子节点就可以了。

不妨设有与其相邻的叶子节点的节点为 $stic$（木棍，感性理解一下）；整个图中叶子数为 $c_l$，$stic$ 数为 $c_s$。则毛毛虫 $(p,q)$ 合法当且仅当满足下列条件中的一个：

- $q$ 为叶子。
- $q$ 不为叶子，$d(q,p)$ 为 $stic$，$p$ 不为 $stic$。

于是可以枚举每个 $stic$（即所有可能的 $d(q,p)$），统计答案。

注意到虽然确定一个 $d(q,p)$ 时没法直接算，但是如果将一个 $d(q,p)$ 对应的所有 $q$ 的答案情况加起来，就会发现不处理 $p,q$ 在同一个子树内的情况时，答案恰好会多算 $c_s$ 个，于是减掉就行了。

然后式子就很显然了，不过还是给一下吧，设 $s_u$ 为与点 $u$ 相邻的非叶子个数，则答案为：

$$\sum _{u \notin leaf,u \in stic} c_s \times (s_u - 1)$$

## Code

```cpp
int n;
vector <int> p[MAXN]; // 存图
bitset <MAXN> leaf,stic; // 分别表示第 i 个点是(1)否(0)为叶子 / stic
int d[MAXN],s[MAXN]; // d[i] 为点 i 的度数；s[i] 为与点 i 相邻的非叶子个数

il void solve(int __Ti)
{
    read(n);
    rep(i,0,n+1) clr(p[i]),d[i]=0,s[i]=0; leaf=stic=0;
    _::r(p,n-1,0);

    int ans=0;

    int tot=0,oto=0; // tot 为叶子数，oto 为 stic 数
    rep(i,1,n) d[i]=p[i].size(),d[i]==1 && (leaf[i]=1,++tot);
    ans+=tot*(n-tot);
    
    rep(i,1,n) if(d[i]>1)
    {
        for(auto j:p[i]) s[i]+=d[j]>1;
        s[i]==d[i] ? (++oto) : (stic[i]=1);
    }
    
    rep(i,1,n) d[i]>1 && stic[i] && (ans+=oto*(s[i]-1));

    write(ans,'\n');
}
```

---

## 作者：WaterM (赞：2)

显然两步之内决胜负。否则两个人会来回拉扯，平局。  
考虑何时 Aron 会赢。  
称与叶子结点边距离小于等于 $1$ 的结点为【制胜点】。

- 开局 $q$ 在叶子，$p$ 不在叶子，直接赢。方案数 $c(n-c)$，其中 $c$ 为叶子数量。
- $q$ 在一个连着【制胜点】的点，$p$ 不在【制胜点】。Nora 被迫把 $q$ 移到【制胜点】，随后 Aron 赢。

针对第二种情况，我们考虑树形 DP。对于可能的 $q$：

- $p$ 在子树内：我们枚举 $q$ 的儿子 $v$，如果其为【制胜点】，则答案加上 $v$ 子树内的非【制胜点】个数（安放 $p$）。
- $p$ 在子树外：此时 $q$ 的父亲必须为【制胜点】。答案加上 $q$ 子树外的非【制胜点】个数即可。

做完了，时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 2e5+2;
	
	int n;
	vector<int> g[N];
	
	int leaf[N], sp[N], par[N];
	int sum[N], sz[N];
	void DFS(int u, int fa) {
		par[u] = fa;
		sum[u] = sp[u];
		sz[u] = 1;
		for(auto v : g[u]) {
			if(v == fa) continue;
			DFS(v, u);
			sum[u] += sum[v];
			sz[u] += sz[v];
		}
	}
	
	bool check(int u) {
		if(leaf[u]) return false;
		for(auto v : g[u])
			if(!sp[v]) return false;
		return true;
	}
	
	void main() {
		cin >> n;
		for(int i = 1; i <= n; ++i) vector<int>().swap(g[i]);
		for(int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			g[u].push_back(v), g[v].push_back(u);
		}
		if(n == 2) {
			puts("0");
			return;
		}
		
		int cnt = 0;
		for(int i = 1; i <= n; ++i)
			if((int)g[i].size() == 1) ++cnt;
		long long ans = 1ll * cnt * (n - cnt);
		
		int root = 1;
		for(int i = 1; i <= n; ++i)
			if((int)g[i].size() > 1) {
				root = i;
				break;
			}
		memset(sum, 0, sizeof(int) * (n+1));
		memset(sz, 0, sizeof(int) * (n+1));
		memset(leaf, 0, sizeof(int) * (n+1));
		memset(sp, 0, sizeof(int) * (n+1));
		for(int i = 1; i <= n; ++i) 
			if((int)g[i].size() == 1) {
				leaf[i] = sp[i] = 1;
				for(auto v : g[i]) sp[v] = 1;
			}
		DFS(root, 0);
		
		for(int i = 1; i <= n; ++i) {
			if(leaf[i]) continue;
			if(i != root && sp[par[i]] && !leaf[par[i]]) ans += (n - sz[i]) - (sum[root] - sum[i]);
			for(auto v : g[i]) {
				if(v == par[i]) continue;
				if(sp[v] && !leaf[v]) ans += sz[v] - sum[v];
			}
		}
		printf("%lld\n", ans);
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}
 
```

---

## 作者：yvbf (赞：2)

![](bilibili:BV1WN6VYEEGs)

---

## 作者：anotherobject (赞：1)

## 题意
给一棵树和一个毛毛虫 $(p,q)$（一条路径），每次 N 和 A 交替移动（N 先），N 把毛毛虫的 $p$ 端移动一步（身体也跟着动），A 把毛毛虫的 $q$ 端移动一步同上，$p$ 到叶子则 N 赢，$q$ 到叶子则 A 赢。对满足 A 有必胜策略的初始毛毛虫计数。


### 题解
$p$ 初始不为叶子 $q$ 为叶子 A 必胜，方案数好算。

如果 N 移动一步可以达到叶子 A 必败，所以 $p$ 不为一步到叶子点。

如果 N 如何移动都能导致 $q$ 成为一步到叶子点则 A 必胜。

否则游戏将平局。

也就是选择一个一步到叶子点作为 $q$ 前面第二个点，迫使 N 开局走一步把 $q$ 移到这个位置。设这个一步到叶子点为 $u$，那么可以选择的 $p$ 为以 $q$ 为根时 $u$ 子树内非一步到叶子点数量，可以随机选定一个根，算出每个点子树内信息，然后容斥得出。

场上代码写的很仓促，将就看看？
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
struct node{int to,nxt;}edge[N*2]; int head[N],cnt;
void add(int u,int v){edge[++cnt].to=v;edge[cnt].nxt=head[u];head[u]=cnt;}
void adde(int u,int v){	add(u,v); add(v,u);}
int deg[N],isl[N],iss[N],ans,cnts,g[N];
void dfs(int u,int f){
	if(iss[u]==1) g[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){int v=edge[i].to; if(v==f) continue;dfs(v,u);g[u]+=g[v];}
}//g就是子树内非一步到叶子点数量
void dfs2(int u,int f){
	if(f&&iss[f]==0&&iss[u]!=-1)ans+=cnts-g[u];
	if(f&&iss[u]==0&&iss[f]!=-1)ans+=g[u];
	for(int i=head[u];i;i=edge[i].nxt){int v=edge[i].to; if(v==f) continue;dfs2(v,u);}
}
signed main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--){
		int n; cin>>n;
		for(int i=1;i<n;i++){int u,v; cin>>u>>v;adde(u,v);deg[u]++; deg[v]++;} int cntl=0; cnts=0;
		for(int i=1;i<=n;i++){if(deg[i]==1) isl[i]=1,cntl++;else isl[i]=0; deg[i]=0;}
		for(int u=1;u<=n;u++){//iss=-1：叶子 iss=0：一步到叶子 iss=1 非一步到叶子
			if(isl[u]){iss[u]=-1;continue;}iss[u]=1;
			for(int i=head[u];i;i=edge[i].nxt){int v=edge[i].to; if(isl[v]){iss[u]=0; break;}}
			cnts+=iss[u];
		}
		ans=cntl*(n-cntl);dfs(1,0); dfs2(1,0);cout<<ans<<"\n"; ans=0;
		for(int i=0;i<=cnt;i++) head[i]=0; cnt=0; for(int i=1;i<=n;i++ )g[i]=0;
	}
}
```

---

## 作者：冷却心 (赞：0)

神秘博弈论。

首先可以注意到，如果游戏不平局，则两个人移动的轮数不会超过 $1$。原因是如果一方走两步获胜，那么另一方可以在上一轮相反方向动，阻止他获胜，导致互相拉扯然后平局。然后开始分讨。

我们给结点分为三类，记 $c_0$ 表示的是叶子结点数（包括你假定的根，也就是所有度为 $1$ 的结点），$c_1$ 表示非叶结点并且走一步可以到达叶结点的结点数，其他是平凡的结点。

那么开始讨论。

- 一开始 $q$ 就在叶结点，而 $p$ 非叶结点，游戏一开始就结束了。则显然 $(p,q)$ 的对数是 $c_0 \times (n-c_0)$。
- $p,q$ 都不是叶子结点，但是 $p$ 先手移动一步之后不能到达叶结点，并且 $q$ 到达了一个上文第二种结点，也就是移动一步可到达叶结点的结点，那么这种方案可行。考虑怎么计数：我们分别以每个结点为根来考虑，设当前根为 $r$，$q$ 最初处于 $r$，如果 $r$ 是原树叶子，那么显然不符合这种方案，贡献为 $0$；那么考虑它的每个子结点，考虑 $p$ 落在这棵子树内的情况，首先 $p$ 不能是叶子，也不能是能一步到叶子的结点，那么这时候 $p$ 不能往上走，因为父结点在毛毛虫内，那么他只能往下走，导致 $q$ 变成了 $r$ 的这个子结点，根据我们的讨论，这时候 $q$ 应该是能到达叶子的结点，所以这个儿子应该满足能到达叶子。所以 $r$ 对答案的贡献为（其中 $f_u$ 表示 $u$ 子树内非叶子也不能一步到叶子的结点数）：
  $$\text{Contribution}=\sum_{u\in \text{son}(r) \wedge u \text{ can reach a leaf by one step}} f_u.$$
  注意到这步也要统计父亲方向的答案，可以用类似换根 DP 的方式做到。
  
然后就做完了。


```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL MOD = 998244353;
const int N = 5e5 + 10;
int n, f[N], tot; vector<int> G[N]; LL Ans = 0;
int sz[N];
void DFS1(int u, int fa) {
	sz[u] = (f[u] == 0);
	for (int v : G[u]) if (v != fa) { DFS1(v, u); sz[u] += sz[v]; }
	return ;
}
void DFS2(int u, int fa) {
	if (fa && f[fa] == 1 && f[u] != 2) Ans += tot - sz[u];
	for (int v : G[u]) if (v != fa) {
		DFS2(v, u); if (f[v] == 1 && f[u] != 2) Ans += sz[v];
	} return ;
}

int main(){
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	while (_ --) {
		cin >> n; Ans = 0; tot = 0;
		for (int i = 1, u, v; i < n; i ++) {
			cin >> u >> v; G[u].emplace_back(v); G[v].emplace_back(u);
		} int cnt = 0;
		for (int i = 1; i <= n; i ++) if (G[i].size() == 1) f[i] = 2, ++ cnt;
		for (int i = 1; i <= n; i ++) if (!f[i]) {
			for (int v : G[i]) if (f[v] == 2) f[i] = 1;
		} Ans = 1ll * cnt * (n - cnt);
		for (int i = 1; i <= n; i ++) tot += (!f[i]);
		DFS1(1, 0); DFS2(1, 0); cout << Ans << "\n";
		for (int i = 1; i <= n; i ++) G[i].clear(), f[i] = 0;
	}
	return 0;
}
```

---

## 作者：_lmh_ (赞：0)

下文假定 $p,q$ 都不是叶子。否则，只有 $q$ 是叶子的情况满足条件，这个计数是简单的。

如果 $p$ 能一步走到叶子，那么先手必胜；否则，考虑 $q$ 移动一格之后到达的位置，发现它是唯一确定的。如果这个位置能一步到达叶子，那么后手必胜。

否则，不管后手怎么走，先手都会回到原来的位置；再下一步，后手也会回到刚才那个位置，无法获胜；然后发现它们上不去下不来卡在这了。

所以我们只要算一步到不了叶子的数量，作为 $p$；对于每个能一步到达叶子的点，计算它所有非叶子的邻居，作为第二个点 $q$。注意到 $p$ 和 $q$ 可能来自同一边，所以这个邻居数量要 $-1$ 之后再累加进去。

具体细节可以参考代码，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007;
ll T,n,ans,cnt0,deg[N],ok[N],cnt1,cnt2;
vector<ll> to[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;ans=cnt0=cnt1=cnt2=0;
		for (int i=1,u,v;i<n;++i){
			cin>>u>>v;
			to[u].emplace_back(v);to[v].emplace_back(u);++deg[u];++deg[v];
		}
		for (int u=1;u<=n;++u) if (deg[u]==1){
			++cnt0;ok[to[u][0]]=1;
		}
		for (int u=1;u<=n;++u) if (deg[u]>1){
			if (ok[u]){
				--cnt1;
				for (auto v:to[u]) if (deg[v]>1) ++cnt1;
			}
			else ++cnt2;
		}
		cout<<(n-cnt0)*cnt0+cnt1*cnt2<<'\n';
		for (int i=1;i<=n;++i){
			to[i].clear();deg[i]=ok[i]=0;
		}
	}
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

由题易得后手必胜仅有两种可能：后手起始点在叶子上且先手起始点不在叶子上；先手无法在一步内走到叶子上且后手在先手操作后一定能在一步内走到叶子上。

对于第一种情况，仅需统计叶子数量即可；

对于第二种情况，对所有的点进行两次扫描，第一次扫描每个点是否与至少一个叶子相邻，第二次扫描每个点的所有邻接节点是否**全部**与至少一个叶子相邻。

在第二种情况下，先手起始节点不能放在叶子或与叶子相邻的节点上，后手起始节点必须放在所有邻接节点都与至少一个叶子相邻的节点上且自己不能是叶子。

时间复杂度 $O(n)$。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <chrono>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n, deg[N], siz[N], tot;
bool adj[N], adj2[N];
using ll = long long;
ll res, cds;
vector<int> road[N];
void init_global()
{
}
void dfs(int x, int f)
{
	siz[x] = !adj[x];
	for (auto &i : road[x])
	{
		if (i == f)
			continue;
		dfs(i, x);
		siz[x] += siz[i];
		if (adj[i] and deg[x] != 1)
			res += siz[i];
	}
	if (adj[f] and deg[x] != 1)
		res += tot - siz[x];
}
void init_local()
{
	scanf("%d", &n);
	memset(deg + 1, 0, n << 2);
	for (int i = 1; i <= n; i++)
		road[i].clear();
	for (int i = 1, x, y; i < n; i++)
	{
		scanf("%d%d", &x, &y);
		road[x].emplace_back(y);
		road[y].emplace_back(x);
		deg[x]++, deg[y]++;
	}
}
void run()
{
	res = 0;
	for (int i = 1; i <= n; i++)
		res += (deg[i] == 1);
	cds = n - res;
	res *= n - res;
	for (int i = 1; i <= n; i++)
	{
		adj[i] = true;
		if (deg[i] == 1)
			continue;
		adj[i] = false;
		for (auto &j : road[i])
		{
			adj[i] |= (deg[j] == 1);
			if (adj[i])
				break;
		}
	}
	tot = 0;
	for (int i = 1; i <= n; i++)
	{
		tot += adj[i];
	}
	tot = n - tot;
	dfs(1, 0);
	printf("%lld\n", res);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	int T = 1;
	scanf("%d", &T);
	init_global();
	while (T--)
	{
		init_local();
		run();
	}
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

