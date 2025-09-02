# Reachability and Tree

## 题目描述

考虑一个有向图，我们称有序数对 $(u,v)$ 是好的当且仅当 $u\ne v$ 且图中存在一条 $u$ 到 $v$ 的路径。

给你一棵 $n$ 个结点的树，问有没有一种把这棵树的所有 $n-1$ 条边确定方向的方案，使得形成的有向图中恰有 $n$ 个好的数对。如果存在，给出任意一种方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2112D/5e96780aa4a833603401ce38c95583d3dff310ba.png)

对于第一组数据，这是一种可能的定向方案。

## 说明/提示

**样例解释**

对于第一组数据，一种可能的定向方案如上图所示。在此方案中五个好的数对为 $(3,5),(3,1),(3,2),(1,2),(4,2)$。

对于第二组数据，一种可能的定向方案如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2112D/a9d7677ec7ba1046004aa29fc6e4a4dca863d6eb.png)

在此方案中五个好的数对为 $(2,1),(3,1),(4,1),(5,4),(5,1)$。

对于第三组数据，只有两个有序数对，无论这条唯一的边指向哪个方向，都只有一个数对会是好的。

## 样例 #1

### 输入

```
4
5
1 2
2 4
1 3
3 5
5
1 2
1 3
1 4
4 5
2
2 1
4
3 1
1 2
2 4```

### 输出

```
YES
1 2
3 1
3 5
4 2
YES
2 1
3 1
4 1
5 4
NO
YES
1 3
2 1
2 4```

# 题解

## 作者：sSkYy (赞：3)

# [CF2112D Reachability and Tree](https://www.luogu.com.cn/problem/CF2112D)

## 题意

设 $u$ 和 $v$ 是有向图中的两个不同顶点。如果存在一条从顶点 $u$ 到顶点 $v$ 的路径，我们称有序对 $(u, v)$ 是好的。

给一棵树定向，使得好点对数量刚好为 $n$。如果可能，输出任意一种满足条件的边定向方案。

## 题解

注意到不管如何定向一条边总会产生 $1$ 的贡献，那么答案至少为 $n-1$。 

如图，我们只需要沿着 $\text{DFS}$ 给边一正一反的定向就可以产生 $n-1$ 的贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/jzoehz6k.png)
---

现在要做的是如何多产生 $1$ 的贡献，注意到如果一个点的度数为 $2$ 时，改变其子树上所有边的方向，就可以刚好增加 $1$ 的贡献。

如图，只要把以顶点 $5$ 为根节点的子树上的边的方向全部取反即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/78p6agdr.png)
---

具体的，先找出一个入度为 $2$ 的点，标记一下，当遍历到该点时将当前方向取反，再正常 $\text{DFS}$ 即可。 

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,id;
vector<int> e[N];
vector<pair<int,int>> ans;
void dfs(int u,int fa,bool op){
    if(u==id) op^=1;
    for(int v:e[u]){
        if(v==fa) continue;
        if(op) ans.emplace_back(u,v);
        else ans.emplace_back(v,u);
        dfs(v,u,op^1);
    }
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) e[i].clear();
    ans.clear();
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    bool flag=false;
    for(int i=1;i<=n;i++)
        if(e[i].size()==2){
            flag=true;
            id=i; //标记入度为 2 的点。
            break;
        }
    if(!flag) return cout<<"NO\n",void();
    if(id==1) dfs(2,2,1);//注意不能从标记的点开始 DFS ，否则方向取反就没用了。
    else dfs(1,1,1);
    cout<<"YES\n";
    for(auto it:ans) cout<<it.first<<" "<<it.second<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int T; cin>>T;
    while(T--) solve();
	return 0;
}
```

---

## 作者：ZHR100102 (赞：1)

[Blog](https://www.cnblogs.com/zhr0102/p/18943906)

注意到 $n$ 个数对对于整棵树来说是很小的，因此先考虑**最小化数对**。又因为一条边必定会贡献一个数对，为了让一条有向边不与其他有向边一起对答案造成贡献，所以我们使**所有相邻的边指的方向都不同**。因为树是特殊的**二分图**，所以这是可以实现的。

此时我们的构造方案是 $n-1$ 个数对，要补齐最后的那一个，考虑**调整法**，只要让**恰好两条**相邻的边是同一个指向的就好了。画成图可以发现，这个点一定满足**度数为 $2$** 的限制，否则一定会多贡献。于是把度数为 $2$ 的点的某条边反转，然后把该点子树中的所有边再反转一次即可。


依据上文构造，时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=200005,inf=0x3f3f3f3f,V=200005;
vector<int>g[N];
int n,rd[N];
void dfs(int u,int fa,int pre)
{
    for(auto v:g[u])
    {
        if(v==fa)continue;
        if(fa==0)
        {
            cout<<u<<" "<<g[u][0]<<'\n';
            cout<<g[u][1]<<" "<<u<<'\n';
            dfs(g[u][0],u,0);
            dfs(g[u][1],u,1);
            return;
        }
        if(pre==0)cout<<v<<" "<<u<<'\n';
        else cout<<u<<" "<<v<<'\n';
        dfs(v,u,pre^1);
    }
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        rd[i]=0;
        g[i].clear();
    }
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
        rd[u]++;rd[v]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(rd[i]==2)
        {
            cout<<"YES\n";
            dfs(i,0,0);
            return;
        }
    }
    cout<<"NO\n";
}

int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：zhanglh (赞：1)

容易发现，对于每条边定向后，就形成了 $n - 1$ 对有序对。题目要求定向后图中存在恰好存 $n$ 对有序对，因此，还需要构造恰好一对。

发现，此有序对之间的路径长度应该恰为 $2$。考虑选取一个度数为 $2$ 的节点作为 root 开始 DFS。此有序对就是从 root 的一个孩子走到另一个孩子。

考虑其余的边，对于 $x$ 的孩子 $y$ 和父节点 $z$，应使得边 $\{x, y\}$ 的方向和边 $\{x, z\}$ 的方向相反。

```
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int N = 200010;

int n, root, d[N];
vector<int> e[N];
vector<pii> adj;

void dfs(int u, int parent, int dir) {
    if (u == root) {
        dfs(e[u][0], u, 1);
        adj.push_back({e[u][0], root});
        dfs(e[u][1], u, 0);
        adj.push_back({root, e[u][1]});
    } else {
        for (int v : e[u]) {
            if (v == parent) continue;
            dfs(v, u, dir ^ 1);
            if (dir == 0) adj.push_back({v, u});
            else adj.push_back({u, v});
        }
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        d[i] = 0;
        e[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
        d[u]++;
        d[v]++;
    }
    root = 0;
    for (int i = 1; i <= n; i++) {
        if (d[i] == 2) {
            root = i;
            break;
        }
    }
    if (root == 0) {
        cout << "NO\n";
        return;
    }
    adj.clear();
    dfs(root, 0, -1);
    cout << "YES\n";
    for (pii i : adj) cout << i.first << " " << i.second << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    while(T--) solve();
    
    return 0;
}

```

---

## 作者：Mason123456 (赞：1)

~~感觉比 C 题好想。~~

多测不清空，亲人两行泪。

***

观察样例，发现如果「两条边相对」（如：$u \to v, w \to v$）或者「两条边相反」（如：$u \to v, u \to w$），那么每条边的贡献就是 $1$。

**此时，每个节点要么只是出边，要么只是入边。**

此时构造出来的图的答案就是 $n-1$。

观察样例，发现如果存在「只有两条边的路」（如：$u \to v, v \to w$），那么贡献就会多 $1$ 个（$u \to v \to w$）。

需要注意：**上述的点 $v$ 只能有两条边相连**。因为但凡多一条就多了贡献。可以自己画图验算一下。

***

所以我们需要找到度数为 $2$ 的节点（令它为 $rt$）为根结点，假如 $rt$ 的两个儿子 $u, v$，那么构造一个 $u \to rt \to v$。用「深度优先搜索」保证 $u$ 和 $v$ 的子树的答案都是「子树大小 $-1$」即可。

***

因为存在性质 $u, v$ 的子树的每个节点**要么只是出边，要么只是入边**，所以只用打节点的标记即可。

对于根 $rt$，在代码中用「第一个儿子」反转一下边，即将第一个儿子的标记和 $rt$ 一样。

代码中的 `cnt` 的作用是判断是不是第一个儿子。`tag[i] == 0` 表示全是出边，反之亦然。

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 5;
int tag[N];
vector<int> g[N];

void dfs(int u, int fa, int rt){
    int cnt = 0;
    for(auto v : g[u]){
        if(v == fa) continue;
        if(u == rt && !cnt)
            cnt = 1, tag[v] = tag[u];
        else    tag[v] = 1 - tag[u];
        dfs(v, u, rt);
    }
}

void sol(){
    int n;  cin>>n;
    vector<int> in(n + 1);
    for(int i = 1;i < n;i++){
        int u, v;   cin>>u>>v;
        g[u].push_back(v), g[v].push_back(u);
        in[u]++, in[v]++;
    }
    int rt = -1;
    for(int i = 1;i <= n;i++){
        if(in[i] == 2){
            rt = i;
            dfs(i, 0, i);
            break;
        }
    }
    if(rt == -1){
        cout<<"NO\n";
    }
    else{
        cout<<"YES\n";
        for(int i = 1;i <= n;i++){
            if(tag[i])  continue;
            int cnt = 0;
            for(auto v : g[i]){
                if(i == rt && !cnt){
                    cnt = 1;
                    continue;
                }
                cout<<i<<" "<<v<<'\n';
            }
        }
    }
    for(int i = 1;i <= n;i++){
        g[i].clear();   tag[i] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;  cin>>t;
    while(t--)  sol();
    return 0;
}
```

---

## 作者：lilong (赞：1)

注意到一条边无论方向如何，都能使两端的某一个点到达另一个点，即至少有 $n-1$ 对。如果只需要 $n-1$ 对，那么只需要在每一条链上相邻的边方向相反即可。对于剩下的一对，我们可以找到一个度数为 $2$ 的点，并把连接的两条边由反向改为同向，那么附近的三个点产生的对数由 $2$ 变成了 $3$，达到要求（如果度数不为 $2$，那么增加的对数一定不止 $1$，不能达到要求）。如果找不到则无解。时间复杂度 $O(\sum n)$。


```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define N 200010
using namespace std;
vector<int> G[N];
int n,rt;
void dfs(int u,int fa,int op){
    for(auto v:G[u]){
        if(v==fa)continue;
        if(op)cout<<u<<' '<<v<<'\n';
        else cout<<v<<' '<<u<<'\n';
        dfs(v,u,op^1);
    }
    return;
}
void solve(){
    int u,v;
    rt=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        G[i].clear();
    for(int i=1;i<n;i++){
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
        if(G[i].size()==2){
            rt=i;
            break;
        }
    if(!rt){
        cout<<"NO\n";
        return;
    }
    cout<<"YES\n";
    cout<<G[rt][0]<<' '<<rt<<'\n';
    cout<<rt<<' '<<G[rt][1]<<'\n';
    dfs(G[rt][0],rt,1);
    dfs(G[rt][1],rt,0);
}
int main(){
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：Halberd_Cease (赞：0)

首先观察到无论如何，图上至少有 $n-1$ 对符合要求的数对，因为从一条边的一边前往另外一条边是合法的。

我们容易想到一种构造方法，即同一个点只有入度或者出度，这样的话树上就有 $n-1$ 个合法数对，因为是树，没有环所以一定可以构造出来。

考虑在此之上调整。考虑两条相邻的边什么时候有大于 $2$ 的贡献，即这两条边同向，此时贡献为 $3$，刚好多 $1$。如果有 $3$ 条及以上的边连接同一个节点，那么无论怎么改变边的方向，增加的贡献一定大于 $1$ 因此不合法。

所以我们只能找到一个度数为 $2$ 的节点，给相邻的两条边方向设置相同（一进一出），剩下的点根据已经确定边的方向确定，均为全部进或者全部出。

若一个图无 $2$ 度点，那么无解。

[submission](https://codeforces.com/contest/2112/submission/325941265)

---

## 作者：kczw (赞：0)

# 题意
给定一棵 $n$ 个节点的无向树，如果有两个节点 $u,v$ 使得 $u$ 可到达 $v$ 则称这是一对好节点。试给 $n-1$ 条边定向，使得恰好有 $n$ 对好节点，有则输出 `YES` 以及每条边的方向，无则输出 `NO`。

多测，$t\le10^4,\sum n\le2\times10^5$。
# 思路
如果是 $n-1$ 对好节点就简单了，注意到好节点意味着一条路径，而树本身就具有 $n-1$ 条边，所以最少都具有 $n-1$ 路径，如果是求恰有 $n-1$ 对好节点，就要保证从每个点出发只能走一步，我们把所有偶数深度的节点当做出点，奇数深度的节点当做入点即可。

但是我们现在要求恰恰有 $n$ 对号节点，那么就意味着恰多出一条路径，这一路径只能是两条边 $(u,v),(v,w)$ 组成路径 $(u,v,w)$ 这样多出一对好节点 $u,w$。同时，$v$ 作为中间节点，无论是出点还是入点只有它还有除了 $(u,v),(v,w)$ 外的其他边例如 $(v,x)$，如果是 $v$ 作出点则多了一对好节点 $u,x$，否则也会多一对好节点 $w,x$。所以作为中间节点的 $v$ 只能有 $(u,v),(v,w)$ 两条边，也就是它的度为 $2$。不妨将 $v$ 作根，那么它有两个子树，子树内部同上段按照深度处理即可。

同理，若该树不存在度为 $2$ 的节点，则无解。

时间复杂度 $O(n)$。
# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,vis[N],dep[N];
vector<int>e[N];
queue<int>q;
inline void solve(){
	m=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)e[i].clear(),vis[i]=0;
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	for(int i=1;i<=n;i++)if(e[i].size()==2)m=i;
	if(!m)return puts("NO"),void();
	puts("YES");
	printf("%d %d\n",e[m][0],m);
	printf("%d %d\n",m,e[m][1]);
	vis[m]=1;dep[m]=0;
	q.push(e[m][0]);
	dep[e[m][0]]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=1;
		for(auto v:e[u])if(!vis[v]){
			q.push(v);
			dep[v]=dep[u]+1;
			if(dep[u]&1)printf("%d %d\n",u,v);
			else printf("%d %d\n",v,u);
		}
	}
	q.push(e[m][1]);
	dep[e[m][1]]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=1;
		for(auto v:e[u])if(!vis[v]){
			q.push(v);
			vis[v]=1;
			dep[v]=dep[u]+1;
			if(dep[u]&1)printf("%d %d\n",v,u);
			else printf("%d %d\n",u,v);
		}
	}
	return;
}
int main(){
	int t;scanf("%d",&t);
	while(t--)solve();
	return 0;
}
```

---

## 作者：He_XY (赞：0)

## [D. Reachability and Tree](https://codeforces.com/contest/2112/problem/D)

### 题意

一棵树有 $n$ 个节点，你要给出一种方案，给每条边加上方向，要存在恰好 $n$ 个数对 $(u,v)$，使得 $u$ 和 $v$ 之间有路径；或者说明这是不可能的。

### 思路

首先，不管怎么加方向，一定存在至少 $n-1$ 个这样的数对，就是每条边的两个点都可以组成一个数对，所以，只要再加上一对即可。

如果只要 $n-1$ 对，若 $1$ 为根节点，我们可以想到这样子加边：第一层全朝上，第二层全朝下，以此类推。

![](https://cdn.luogu.com.cn/upload/image_hosting/ciptikv2.png)

要想再加上一条边，应该找一个 $2$ 度点，它连接的两条边的方向设为相同的，比如上图中，$8$ 是唯一一个 $2$ 度点，所以把 $9\rightarrow 8$ 改为 $8\rightarrow 9$。

若没有两度点，就是不可以。

### C++ 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mpr make_pair
using namespace std;
const int maxn=200005;
int n;
vector<int> g[maxn];
bool flag=false;
int cg;
vector<pair<int,int> > ans;
void find(int v,int fa,int col){
	for(int x:g[v]){
		if(x!=fa){
			if(col) ans.pb(mpr(x,v));
			else ans.pb(mpr(v,x));
			find(x,v,col^1);
		}
	}
}
void solve(){
	flag=false; cg=0;
    for(int i=1;i<=n;i++){
		g[i].clear();
	}
    
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		g[u].pb(v);
		g[v].pb(u);
	}
    for(int i=1;i<=n;i++){
        if(g[i].size()==2){
            cg=i;
            flag=true;
            break;
        }
    }
    
	if(!flag){
		cout<<"NO\n";
		return;
	}
    
	cout<<"YES\n";
	int prv=g[cg][0],nxt=g[cg][1];
	ans.clear();
	ans.pb(mpr(prv,cg));
	ans.pb(mpr(cg,nxt));
	find(prv,cg,0);
	find(nxt,cg,1);
	for(pair<int,int> x:ans){
		cout<<x.first<<" "<<x.second<<endl;
	}
}

int main(){
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

## Statement

给定一棵无向树，我们定义有向图上两个点 $(u,v)$ 是一对好点仅当其满足存在一条从 $u \to v$ 的路径或者 $v \to u$ 的路径，现在你需要求如何树上的边定向使得其正好有 $n$ 对好点。

## Solution

因为这是一棵树，所以一开始我们有几种方案：

- 设所有边向叶子或者向根，则只需要改变可能一条边。

- 按深度奇偶性指向。

你注意到所有边指向叶子或指向根的方案一定不优，因为会出现链导致产生冗余的贡献，所以采取第二种方案，这样构造出来正好是 $n - 1$ 对好点，只需要更改只有一个子节点的子树的那条边，不存在这种子树则无解。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
constexpr int N = 2e5 + 10;

int n, idx, root;
int head[N], fa[N], son[N], depth[N], tag[N], deg[N], u[N], v[N];

struct graph {
	int v, nxt, id;
} e[N << 1];

void addedge (int u, int v, int id) {
	deg[u] ++;
	e[idx].v = v;
	e[idx].nxt = head[u];
	e[idx].id = id;
	head[u] = idx ++;
}

void init() {
	memset (fa, 0, sizeof(int) * (n + 5));
	memset (tag, 0, sizeof(int) * (n + 5));
	memset (son, 0, sizeof(int) * (n + 5));
	memset (deg, 0, sizeof(int) * (n + 5));
	memset (head, -1, sizeof(int) * (n + 5));
	memset (depth, 0, sizeof(int) * (n + 5));
	for (int i = 0; i < idx; i ++)
		e[i].id = e[i].nxt = e[i].v = 0;
	idx = 0;
}

void dfs (int u, int fth) {
	fa[u] = fth;
	depth[u] = depth[fth] + 1;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].v, id = e[i].id;
		if (v != fth) {
			tag[id] = depth[u] % 2; // 按深度奇偶性定向（奇上偶下）
			dfs(v, u), son[u] ++;
		}
	}
}

void change (int u) {
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].v, id = e[i].id;
		if (v != fa[u]) {
			tag[id] ^= 1, change(v); // 只需要改叶子（仅有一个）
		}
	}
}

void solve() {
	cin >> n, init();
	for (int i = 1; i < n; i ++) {
		cin >> u[i] >> v[i];
		addedge (u[i], v[i], i), addedge (v[i], u[i], i);
	}
	
	root = 1;
	for (int i = 1; i <= n; i ++) {
		if (deg[i] != 2) {
			root = i; break;
		}
	}
	dfs(root, 0);
	
	bool flag = false;
	for (int i = 1; i <= n; i ++) {
		if (fa[i] && son[i] == 1) {
			change(i);
			flag = true;
			break;
		}
	}
	
	if (!flag) {
		cout << "NO\n";
		return;
	}
	
	cout << "YES\n";
	for (int i = 1; i < n; i ++) {
		if (depth[u[i]] > depth[v[i]]) {
			swap(u[i], v[i]);
		}
		if (tag[i]) {
			swap(u[i], v[i]);
		}
		cout << u[i] << ' ' << v[i] << '\n';
	}
	return;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int test; cin >> test;
	while (test--) {
		solve();
	}
	return 0;
}
```

---

## 作者：yanjiadong (赞：0)

## 题目描述
在有向树上，如果点 $u$ 可以到达点 $v$，则称有序点对 $(u,v)$ 是好的。

给一棵大小为 $n$ 的无向树的边定方向，使其定向后恰有 $n$ 个好的点对。

## 转换题意
每个好的点对其实就对应有向树上的一条路径。

很显然，长度为 $1$ 的树上路径有且仅有 $n-1$ 条。所以我们构造出来的树必须恰有一条长度不为 $1$ 的路径。

更进一步地，如果存在一条长度大于 $2$ 的路径，那么显然它一定包含至少一条长度等于 $2$ 的路径，不符合要求。

所以题目其实是让我们给无根树的边定方向，使其恰有一条长度为 $2$ 的路径，且不包含长度大于 $2$ 的路径。
## 解题思路
统计一棵有向树上长度为 $2$ 的路径数量是简单的。

我们对于每个节点统计它的入度和出度，那么以它为中心的长度为 $2$ 的路径数就是入度乘以出度。

既然我们只希望有一条长度为 $2$ 的路径，构造出的树需要满足以下两条限制：
1. 存在一个点，它的入度和出度均为 $1$。
2. 对于剩余的所有点，它的出度和入度之一为 $0$。

考虑给把树上的每个节点染成黑色、白色或红色，**满足相邻两点颜色互不相同，同时有且仅有一个红点**，按照如下规则给树边定方向：
- 黑点向白点连边
- 黑点向红点连边
- 红点向白点连边

这样构造出的树有以下性质：

黑点的入度为 $0$，白点的出度为 $0$，这样就满足了限制 2。

为了满足限制 1，只需要保证红点恰好被一个黑点连边，同时恰好向一个白点连边即可。

所以我们可以记录无向树每个点的度数，如果存在一个点度为 $2$，就把它染成红色，并递归地给其它点染色，因为树是二分图，所以这样的染色方案一定存在。

如果不存在度数为 $2$ 的点，直接输出 `NO` 即可。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
vector<int>e[N];
int d[N];bool vis[N];
void dfs(int x,bool t) {
	vis[x]=1;
	for(auto j:e[x]) {
		if(vis[j]) continue;
		if(t) cout<<x<<' '<<j<<'\n'; //黑->白
		else cout<<j<<' '<<x<<'\n';  //白<-黑
		dfs(j,!t);
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int T;cin>>T;
	while(T--) {
		int n;cin>>n;
		for(int i=1;i<n;i++) {
			int u,v;cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
			++d[u],++d[v];//记录每个点的度数
		}
		for(int i=1;i<=n;i++) {
			if(d[i]==2) {
				puts("YES");
				int x=e[i][0],y=e[i][1];
				cout<<x<<' '<<i<<'\n';//红<-黑
				cout<<i<<' '<<y<<'\n';//红->白
				vis[i]=1;
				dfs(x,1),dfs(y,0);
				goto qwq;
			}
		}
		puts("NO");
		qwq:;
		for(int i=1;i<=n;i++) e[i].clear(),d[i]=vis[i]=0;
	}
	return 0;
}
```

---

