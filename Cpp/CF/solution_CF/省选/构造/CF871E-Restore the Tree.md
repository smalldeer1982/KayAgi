# Restore the Tree

## 题目描述

Petya had a tree consisting of $ n $ vertices numbered with integers from $ 1 $ to $ n $ . Accidentally he lost his tree.

Petya remembers information about $ k $ vertices: distances from each of them to each of the $ n $ tree vertices.

Your task is to restore any tree that satisfies the information that Petya remembers or report that such tree doesn't exist.

## 说明/提示

Picture for the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF871E/6f212029526e4d77c3a6bc5fe4ad25b3afc1824a.png)

## 样例 #1

### 输入

```
5 2
0 1 2 3 2
2 1 0 1 2
```

### 输出

```
2 1
3 2
4 3
5 2
```

## 样例 #2

### 输入

```
3 1
1 2 1
```

### 输出

```
-1
```

# 题解

## 作者：hegm (赞：1)

一道有点意思的构造。

考虑先将 $k$ 个关键点的关系建出来。

考虑如果找出 $u\leftrightarrow v$ 的两个关键点，并且两关键点之间的路径上没有其他的关键点，如何构造出两点间的普通节点路径。

定义 $S_{u,k}$ 表示距离 $u$ 距离为 $k$ 的点的集合，$p_i$ 表示第 $i$ 个关键点。

假设 $u\leftrightarrow v$ 的路径长度为 $w$。

那么在路径上距离 $u$ 为 $i$ 的节点为 $S_{u,i}\cap S_{v,w-i}$。

求集合并可以分别枚举一遍，然后看每个点被枚举的次数即可，枚举过两边的节点就是所求。连接一次复杂度为 $O(n)$。

考虑如何找出 $u\leftrightarrow v$ 满足路径上没有其他节点。

不妨设当前已经建立出关系的关键点集为 $T$ （我们保证过程中 $T$ 是联通的，起始时，$T=\{p_1\}$）

考虑找出距离 $T$ 中任何一个点 $u$ 最近的关键节点 $v,v\notin T$。

那么 $u\leftrightarrow v$ 路径上一定没有其他关键点，因为若是有，最近关键节点就不会是 $v$ 了。

因为每次会加入 $T$ 一个关键点，所以会连接 $O(k)$ 次，总复杂度为 $O(nk)$。

找到最近关键点可以通过优先队列实现，每次加入一个关键点的时候就将其距离其他关键点距离信息加入优先队列，复杂度为 $O(k^2\log k^2)$。

如此一来，我们就建立出了一棵基本的树，但是还有一些节点没有出现在树上，如果一个节点其不再任何一对关键点的路径上，那么其目前还未加入。

我们不妨让 $p_1$ 作为根，方便描述。

考虑一个未出现的节点 $i$，其父亲距离关键节点的距离，比他距离关键节点的距离都少 $1$。

那么不妨用 `hash` 来维护和直接查询，我们将每个节点距离 $k$ 个节点的距离视为一个序列，将其哈希即可，查询其父亲的序列也很简单，只需要再暴力的跑一下序列上每个数 $-1$ 的哈希，然后用 `map` 查询即可。

为了保证每个节点加入时其父亲也已经加入，我们将未加入的节点按照距离关键点的最近距离排序，按顺序加入即可。

此复杂度为 $O(nk+n\log n)$。

总复杂度为 $O(nk+n\log n +k^2\log k^2)$

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ll unsigned long long
#define make make_pair
#define pii pair<int,int>
#define N 30004
#define M 205
#define B 23
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,k,ans=1,id[N],p[M][N],vis[N],rt;
vector<int> v[M][N];
map<ll,int> ch;
int dis(int x,int y)
{
	if(!id[x])swap(x,y);
	return p[id[x]][y];
}
struct node
{
	int w,x,y;
	bool friend operator <(node a,node b)
	{
		return a.w>b.w;
	}
};
priority_queue<node> q;
map<int,bool> mp[N];
struct edge
{
	int a,b;
}e[N];int ct;
int h[N];
void lk(int a,int b)
{
	if(mp[a][b])return ;
	mp[a][b]=1;
	mp[b][a]=1;
	e[++ct]={a,b};
}
void solve(int x,int y,int w)
{
	int lst=x;
	for(int l=1;l<w;l++)
	{
		int pos=0;
		for(int a:v[id[x]][l])h[a]++;
		for(int b:v[id[y]][w-l])h[b]++;
		for(int a:v[id[x]][l])
		{
			if(h[a]==2)
			{
				lk(lst,a);
				lst=a;
				vis[a]=1;
				pos++;
			}
			h[a]=0;
		}
		for(int b:v[id[y]][w-l])h[b]=0;
		if(pos!=1)ans=0;
	}
	lk(lst,y);
}
void out()
{
	for(int i=1;i<=ct;i++)
	{
		cout<<e[i].a<<" "<<e[i].b<<"\n";
	}
}
signed main()
{
	n=read();k=read();
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++)
		{
			int w=read();
			p[i][j]=w;
			v[i][w].push_back(j);
		}
		if(v[i][0].size()==1)
		{
			id[v[i][0][0]]=i;
			if(i==1)rt=v[i][0][0];
		}
		else ans=0;
	}
	vis[rt]=1;
	for(int i=1;i<=n;i++)if(id[i])q.push({dis(rt,i),rt,i});
	while(q.size())
	{
		int x=q.top().x,y=q.top().y,w=q.top().w;
		q.pop();
		if(vis[y])continue;
		vis[y]=1;
		solve(x,y,w);
		for(int i=1;i<=n;i++)if(id[i])q.push({dis(x,i),x,i});
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			int w=1e9;
			for(int j=1;j<=k;j++)w=min(w,p[j][i]);
			q.push({w,i,0});
		}
		else
		{
			ll w=0;
			for(int j=1;j<=k;j++)w=w*B+p[j][i];
			ch[w]=i;
		}
	}
	while(q.size())
	{
		int x=q.top().x;q.pop();
		ll pw=0,nw=0;
		for(int j=1;j<=k;j++)
		{
			pw=pw*B+p[j][x]-1;
			nw=nw*B+p[j][x];
		}
		if(ch[pw])lk(ch[pw],x);
		ch[nw]=x;
	}
	if(!ans||ct!=n-1)cout<<"-1\n";
	else out();
	return 0;
}

```

---

## 作者：EmptyAlien (赞：1)

[CodeForces 871E](https://codeforces.com/problemset/problem/871/E)

很好的一道构造题。

# 一个性质

我们记这 $k$ 个点分别为 $p_1\sim p_k$。

首先，题目并没有指定树的根，比较难受，为了方便，我们取 $p_1$ 为根。

于是我们就意外得到了每个点的深度，也就是到 $p_1$ 的距离 $\left\{d_1\right\}$，我们另外记 $i$ 的深度为 $dep_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/xm0c8ypz.png)

因此，我们得到：
$$
dep_{lca(u,v)}=\cfrac{dep_u+dep_v-dis_{u, v}}{2}
$$
其中 $dis_{x,y}$ 为 $x$ 与 $y$ 间的距离。

有了这个结论我们就能求一个关键点与其他任意一点的 lca 深度了。

除此之外我们还可以判断一点是不是另一点祖先。（需要满足其中一点为关键点）

# 构造过程

## Step 0

捣鼓了半天我们连 $p_i$ 是啥都不知道。

但是每个点到自己的距离为 $0$。

所以只需要看对应的距离上哪个是 $0$ 就行了。

如果没有就直接无解。

时间复杂度 $\Theta(nk)$。

## Step 1

由于关键点之间信息最多，先建立关键点的联系。

我们建一棵稍微小那么一点的树，其上的节点只有关键点，两点连边当且仅当其中一点为另一点在关键点中最近的祖先。

显然这是一棵以 $p_1$ 为根的树，且拥有原树的基本形态。

要构建这棵树我们考虑枚举每个不是根的点，尝试寻找她的父亲。

只要对于每个点再枚举关键点找出深度最深且为其祖先的即可。

但是如果搞出来的不是一个树，直接无解。

时间复杂度 $\Theta(k^2)$。

## Step 2

光有这棵树显然是没有什么用的，我们要把她还原成原树。（至少是一部分）

怎么办？

对于这棵乞丐版的树，要是两点间有连边，那她们一定有一条直上直下的链连接她们。（因为成祖先关系）

我们可以试着把这些链找出来。

考虑枚举原树上每个非关键点和小树上的每条边，看看这个点在不在这条边对应的链上。

如果这个点在链上，那她到链两端的距离和就等于链的长度。

我们把每条边上的链全部算出来，于是乎按照深度排个序就把小树的影子映射到了大树上。

如果一条链上的深度有重叠或者漏一个直接无解。

时间复杂度 $\Theta(n\log n + nk)$。

？

嘻嘻……你被坑了。

有没有想过一个问题，在小树下 $u,v$ 是 $w$ 的两个儿子，但是在大树中 $u,v$ 的 lca 并不是 $w$ 而是另一个点 $p$？

![](https://cdn.luogu.com.cn/upload/image_hosting/q7wgse0v.png)

这个时候，$w$ 到 $p$ 之间的点会被算两次。

于是我们还要给整张图去重边！

Tip: 相较于对存图的 `vector` 进行 `unique`，更好的方法是直接覆盖每个点的父亲。

## Step 3

树的形状是出来了，但明显少了一堆点没加上去。

由于我们已经把主干画出来了，而且根一定是关键点，所以剩下的一定是挂在主干上某些节点的枝条。

先不管她枝条什么个形状，先搞清楚这些点挂在哪里。

同样枚举每个还没挂上去的点。再枚举每个关键点，她与每个关键点的 lca 中最深的那个一定是她所在枝条挂在主干上的点。

我们知道这个点深度之后，再枚举每条小树边看这个点在不在对应的链上，如果在就把这个点塞进到链上对应深度的点的 todo list 里去。

如果这个点无法挂到任何的点上去，则直接无解。

时间复杂度：$\Theta(nk)$。

## Step 4

终于到打 boss 的阶段了！

我们现在要考虑的是，对于每个枝条，确定她的形状。

而我们唯一的限制就是每个点的深度。

直接将这些点按照深度排序，把下一深度的所有点全部接到上一深度的任意一个点上即可。

如果存在相邻深度差 $2$ 或以上的则直接无解。

时间复杂度：$\Theta(n\log n)$。

总时间复杂度：$\Theta(k^2+nk+n\log n)$。

# 代码细节

看到这么多无解情况一定很头疼吧，其实，其他无解情况是无效的。

~~别问，问就是面向数据编程。~~

建议给每个小树边对应的链建 `vector` 这样可以在 Step 3 省很多事。

还有就是不要用 `vector` 或链式前向星存图，在遍历边时较为零乱，不方便去重，而且数据里的输出都是枚举每个点输出它与其父亲的边。在稍微大一点的数据进行查错时较为轻松。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define debug(x) cerr << #x << " = " << x << endl
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define gn(u, v) for (int v : G.G[u])
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define vi vector<int>
#define vpii vector<pii>
#define vvi vector<vi>
#define no cout << "NO" << endl
#define yes cout << "YES" << endl
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define tomin(x, y) ((x) = min((x), (y)))
#define tomax(x, y) ((x) = max((x), (y)))
#define ck(mask, i) (((mask) >> (i)) & 1)
#define pq priority_queue
#define FLG (cerr << "Alive!" << endl);

constexpr int MAXN = 3e4 + 5;
constexpr int MAXK = 205;
int n, k;
int d[MAXK][MAXN], p[MAXK];

vi G[MAXK];
int fa[MAXK];
vpii con[MAXK];
bool mark[MAXN];
vpii hanging[MAXN];
int f[MAXN];

int dep(int x) {
    return d[1][x];
}

int lcadep(int x, int y) {
    return (dep(p[x]) + dep(p[y]) - d[x][p[y]]) / 2;
}

int lca(int x, int y) {
    return (dep(p[x]) + dep(y) - d[x][y]) / 2;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    rep (i, 1, k) {
        bool flag = false;
        rep (j, 1, n) {
            cin >> d[i][j];
            if (d[i][j] == 0) {
                p[i] = j;
                mark[p[i]] = true;
                flag = true;
            }
        }
        if (!flag) {
            cout << -1 << endl;
            return 0;
        }
        // cerr << p[i] << " ";
    }
    // cerr << endl;

    rep (i, 1, k) {
        rep (j, 1, k) {
            if (i == j)
                continue;
            if (lcadep(i, j) == dep(p[i])) {
                if (dep(p[i]) > dep(p[fa[j]]) || !fa[j]) {
                    fa[j] = i;
                }
            }
        }
    }

    // rep (i, 2, k) {
    //     cerr << p[i] << " " << p[fa[i]] << endl;
    // }

    rep (i, 1, n) {
        rep (j, 2, k) {
            if (p[j] != i && p[fa[j]] != i) {
                if (d[j][i] + d[fa[j]][i] == d[j][p[fa[j]]] && dep(i) > dep(p[fa[j]]) && dep(i) < dep(p[j])) {
                    // cerr << p[j] << "." << dep(p[j]) - dep(p[fa[j]]) << " ";
                    con[j].pb(mp(dep(i), i));
                    mark[i] = true;
                }
            }
        }
        // cerr << endl;
    }

    rep (i, 2, k) {
        sort(all(con[i]));
        int last = p[fa[i]];
        for (auto [ord, u] : con[i]) {
            f[u] = last;
            last = u;
        }
        f[p[i]] = last;
        // cerr << endl;
    }

    // rep (i, 1, n) {
    //     if (mark[i]) {
    //         cerr << i << " ";
    //     }
    // }
    // cerr << endl;

    rep (i, 1, n) {
        if (mark[i])
            continue;
        int mxdep = -1, point;
        // cerr << endl;
        rep (j, 1, k) {
            if (lca(j, i) > mxdep) {
                mxdep = lca(j, i);
                point = j;
                // cerr << j << " ";
            } else if (lca(j, i) == mxdep) {
                // cerr << j << " ";
                if (dep(p[point]) > dep(p[j]))
                    point = j;
            }
        }
        // if (i == 8) {
        //     cerr << point << " " << mxdep << endl;
        // }
        // cerr << i << ":" << point << " " << mxdep << endl;
        if (lca(point, i) == dep(p[point])) {
            hanging[p[point]].pb(mp(dep(i), i));
            continue;
        }
        bool flag = true;
        mxdep = 0;
        rep (j, 2, k) {
            if (lca(j, i) > dep(p[fa[j]]) && lca(j, i) < dep(p[j])) {
                int cur = con[j][lca(j, i) - dep(p[fa[j]]) - 1].se;
                if (dep(cur) > dep(mxdep)) {
                    mxdep = cur;
                }
            // cerr << lca(j, i) << endl;
                // cerr << con[j][lca(j, i) - dep(p[fa[j]]) - 1].fi 
            }
        }
        hanging[mxdep].pb(mp(dep(i), i));
        // if (flag) {
        //     cerr << i << endl;
        // }
    }

    rep (i, 1, n) {
        if (mark[i]) {
            sort(all(hanging[i]));
            // if (hanging[i].size()) {
            //     cerr << i << ":" << endl;
            //     for (auto [ord, u] : hanging[i]) {
            //         cerr << u << " ";
            //     }
            //     cerr << endl;
            // }
            int cur = i, last = i;
            for (auto [ord, u] : hanging[i]) {
                if (dep(u) != dep(last)) {
                    cur = last;
                }
                f[u] = cur;
                mark[u] = true;
                // cerr << cur << " " << u << endl;
                last = u;
            }
        }
    }

    rep (i, 1, n)
        if (f[i])
            cout << i << " " << f[i] << endl;

    return 0;
}
```

---

## 作者：tzc_wk (赞：0)

首先非常明显的一点是，根据每个点到关键点的距离我们可以确定每个关键点具体是什么——因为它就是到该关键点距离为 $0$ 的点。当然如果这样的点不唯一咱就直接输出 $-1$ 即可。在下文中为了方便起见我们称这些关键点为 $p_1,p_2,\cdots,p_k$。

我们不妨将树根定在以 $p_1$，这样我们只要确定了每个点的父亲，就可以确定整棵树。下面我们的任务就是找到每个点的父亲，一个 trivial 的 observation 是，对于 $p_1,p_2,\cdots,p_k$ **构成的虚树上的所有点**，它们的父亲是很容易确定的，因为对于一个 $p_i$，$p_1\to p_i$ 路径上所有点组成的集合等于 $\{x|d_{1,x}+d_{i,x}=d_{1,p_i}\}$，这个遍历一遍即可求得，又显然这些点的 $d_{1,x}$ 互不相同，因此我们可以轻松获取这些节点的父子关系——当然，如果这其中的父子关系出现冲突，我们需输出 $-1$。

接下来考虑如何钦定剩余的点，显然对于每个不在虚树上的点 $x$，我们可以找到这个点到根路径上深度最深的且在虚树上的点 $pt_x$，这个就枚举所有关键点 $i$，然后根据 $d_{1,x}+d_{1,p_i}-2d_{1,\text{LCA}(p_i,x)}=d_{i,x}$ 得到它们 LCA 的深度，进而知道它们的 LCA 是谁，那么我们要求的 $pt_x$ 就是所有 LCA 中深度最深的。

我们考虑把所有不在虚树上的点 $x$ 都存在 $pt_x$ 的 `vector` 里，然后遍历虚树上的每一个点，将其 `vector` 中的点按深度从小到大排序，然后考虑这些点的深度的每一个连续段，如果相邻两个连续段中点的深度相差超过 $1$ 那么答案是 $-1$，否则我们把这一连续段中的点挂在上一连续段中任意一个点下面即可。

时间复杂度 $nk\log n$。

~~不过 u1s1 这道题的数据好像除了 test2 没有 $-1$ 的点，所以 $-1$ 的情况你想咋判就咋判反正 test2 那么弱也不太可能 WA（大雾，/xyx~~

```cpp
using namespace fastio;
const int MAXK=200;
const int MAXN=3e4;
int n,k,d[MAXK+5][MAXN+5],p[MAXK+5],fa[MAXN+5],anc[MAXK+5][MAXN+5];
void setfa(int x,int f){if(fa[x]&&fa[x]!=f) puts("-1"),exit(0);fa[x]=f;}
bool vis[MAXN+5];vector<pii> bel[MAXN+5];int f[MAXN+5];
int find(int x){return (!f[x])?x:f[x]=find(f[x]);}
bool merge(int x,int y){x=find(x);y=find(y);return (x==y)?0:(f[x]=y,1);}
int hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int dep[MAXN+5];
void dfs(int x,int f,int *dep){
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		dep[y]=dep[x]+1;dfs(y,x,dep);
	}
}
int main(){
	read(n);read(k);
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++) read(d[i][j]);
		vector<int> pt;
		for(int j=1;j<=n;j++) if(!d[i][j]) pt.pb(j);
		if(pt.size()!=1) return puts("-1"),0;
		p[i]=pt[0];
	} anc[1][0]=p[1];
	for(int i=2;i<=k;i++){
		vector<pii> vec;
		for(int j=1;j<=n;j++) if(d[i][j]+d[1][j]==d[1][p[i]])
			vec.pb(mp(d[1][j],j));
		sort(vec.begin(),vec.end());
		for(int j=0;j<vec.size();j++) if(vec[j].fi!=j) return puts("-1"),0;
		for(int j=1;j<vec.size();j++) setfa(vec[j].se,vec[j-1].se);
		for(int j=0;j<vec.size();j++) anc[i][j]=vec[j].se,vis[vec[j].se]=1;
	} vis[p[1]]=1;
	for(int i=1;i<=n;i++) if(!vis[i]){
		vector<pii> lca_s;
		for(int j=1;j<=k;j++){
			int dis=d[1][p[j]]+d[1][i]-d[j][i];
			if(dis&1) return puts("-1"),0;
			dis>>=1;lca_s.pb(mp(dis,anc[j][dis]));
		} sort(lca_s.begin(),lca_s.end());
		for(int j=1;j<lca_s.size();j++){
			if(lca_s[j].fi==lca_s[j-1].fi&&lca_s[j].se!=lca_s[j-1].se)
				return puts("-1"),0;
		} //printf("%d %d\n",i,lca_s.back().se);
		bel[lca_s.back().se].pb(mp(d[1][i],i));
	}
	for(int i=1;i<=n;i++) if(!bel[i].empty()){
		sort(bel[i].begin(),bel[i].end());
		int pre=d[1][i],prep=i;
		for(int l=0,r=0;l<bel[i].size();l=r){
			r=l;while(r<bel[i].size()&&bel[i][r].fi==bel[i][l].fi) ++r;
			if(bel[i][l].fi!=pre+1) return puts("-1"),0;
			for(int j=l;j<r;j++) setfa(bel[i][j].se,prep);
			pre=bel[i][l].fi;prep=bel[i][l].se;
		}
	}
//	for(int i=1;i<=n;i++) if(i!=p[1]) printf("%d %d\n",i,fa[i]);
	for(int i=1;i<=n;i++) if(i!=p[1]){
		if(!merge(i,fa[i])) return puts("-1"),0;
		adde(i,fa[i]);adde(fa[i],i);
	}
	for(int i=1;i<=k;i++){ 
		memset(dep,0,sizeof(dep));dfs(p[i],0,dep);
		for(int j=1;j<=n;j++) if(d[i][j]!=dep[j])
			return puts("-1"),0;
	}
	for(int i=1;i<=n;i++) if(i!=p[1]) printf("%d %d\n",fa[i],i);
	return 0;
}
/*
10 3
0 1 1 2 2 2 2 3 3 3
2 1 3 2 0 4 4 5 5 1
3 4 2 5 5 3 1 0 2 6
*/
```

---

