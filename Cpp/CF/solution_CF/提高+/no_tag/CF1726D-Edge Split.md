# Edge Split

## 题目描述

### 题目大意

给定一个含有 $n$ 个点 $m$ 条边的无向简单图。

对这张简单图的所有边进行红蓝染色。其中**仅由红边**组成的无向图连通块数为 $c_1$，**仅由蓝边**组成的无向图连通块数为 $c_2$。

请构造一种染色方案使得 $c_1 + c_2$ 最小。如果有多种构造方案，任意输出一种即可。

## 说明/提示

请注意 $m \leqslant n + 2$ 意味着什么。

$Translated \; by \; Zigh$

## 样例 #1

### 输入

```
4
5 7
1 2
2 3
3 4
4 5
5 1
1 3
3 5
4 4
1 2
2 3
1 4
3 4
6 7
1 2
1 3
3 4
4 5
1 4
5 6
6 2
2 1
1 2```

### 输出

```
0111010
1001
0001111
0```

# 题解

## 作者：hcywoi (赞：7)

[Edge Split](https://www.luogu.com.cn/problem/CF1726D)。

一开始 nt 了，以为红边为一颗树，蓝边为剩余边，蓝边就不会有环了。

---

假设有 $n$ 个点，$m$ 条边，且这些边**没有**出现环，那么连通块的数量为 $n - m$，因为不存在环，所以**依次**增加 $m$ 条边，每条边都是连接**两个**连通块，也就是每条边都会使连通块数量减 $1$。

那么**理论**最小值就是 $n\times 2-m$。

本题这个**理论**最小值是可以取到的。

证明：

让这个理论最小值取到，那么必定蓝边和红边都没有构成环。

红边为这些边的生成树，蓝边为剩余边。

那么当 $m = n + 2$ 时，蓝边的边数为 $3$，有可能构成环。

假设构成了环。

- 我们随便选一条环上的边，并将其归为红边。
- 将红边环上的一边且不是上述的边归为蓝边。

这样就没有环。

因为一个环上**至少**有 $3$ 条边。

### 【实现】

生成树可以用并查集实现，即判断一条边的两个端点是否在一个集合，如果在一个集合就是蓝边，否则是红边。

断环也可以并查集，即先将选得第一条边加入并查集，然后枚举红边，如果一条边的两个端点在一个集合，那么这条边就是可选边。

时间复杂度：$\mathcal O(n\alpha(n))$。

具体实现见[代码](https://codeforces.com/contest/1726/submission/189093766)。

---

## 作者：Zigh_Wang (赞：3)

# 分析

由于要求的是连通块数量最小，那么我们首先可以想到生成树，如果将生成树染成一个颜色，那么这个颜色的连通块就只有一个了，~~那就做完了~~。

为什么染成生成树一定最优呢？

我们令红边的连通块数记为 $c_1$，记蓝边连通块数记为 $c_2$。

 首先，我们观察到一点，假设红边组成的子图中存在一个**环**，我们将环上的其中一条边染成蓝色，$c_1$ **不会发生变化**，而 $c_2$ 最多会**减少** $1$，因此最终答案中一定不能存在任何一个环。
![在这里插入图片描述](https://img-blog.csdnimg.cn/38dacc6cee2c4a8e992d24d656e6e31f.png)


而如果不存在这样的一个环，则如果将一条红边染成蓝色，$c_1$ **最多增加** $1$，$c_2$ **最少减少** $1$。

![在这里插入图片描述](https://img-blog.csdnimg.cn/fbcbc119994b479a9652330fa9d24304.png)


因此我们让任何一个颜色组成一棵生成树一定是**不亏**的。

我们假定组成生成树的是红边。由于树的性质，我们知道他一共包含了 $n - 1$ 条边，而题目保证 $m \leqslant n + 2$，这就说明了蓝边**最多**只有 $3$ 条边，也就是蓝边**最多**只可能形成一个环（因为要形成两个环至少需要 $5$ 条边）。因此，我们就只需要考虑怎么把这个环断开就行了（至于为什么，看上面）。

实际上这个问题非常简单，因为我们的红色边已经构成了一棵生成树了，因此我们只需要找到这换上三个点当中最深的那个，将他原本连接的任意一条蓝色边染成红色，再将他与他原本生成树上的**父亲**的红色边染成蓝色即可。这样做既可以保证红色边仍然形成一棵生成树，也可以把环断开，具体方法如图。
![在这里插入图片描述](https://img-blog.csdnimg.cn/e21eeff0fb8c4067965cfc7d2d3a5e5d.png)
至于为什么随便断环会错我也不知道，希望有大佬能证出来Qwq。

那么这样就很简单了，我们只需要 DFS 求出生成树，再断环即可。

# 注意
**千万别用memset！！！**

**千万别用memset！！！**

**千万别用memset！！！**

# 代码
小心哦~ 
代码里是有坑的哦~ 
放心~
不是算法上的坑~
```cpp
//省略快读和头文件
int n, m;
struct Edge {
	int hd[MAXN];
	int nxt[MAXN << 1], to[MAXN << 1];
	int pre[MAXN << 1];
	int col[MAXN << 1];//1R0B
	int tot = 1;
	
	void Add(int x, int y) {
		nxt[++tot] = hd[x];
		hd[x] = tot;
		to[tot] = y;
		pre[tot] = x;
	}
}e;

bool vis[MAXN];
vector<int> B;
int deg[MAXN];
int pa[MAXN], dpt[MAXN];
void dfs(int x, int fa) {//构建生成树
	vis[x] = true;
	pa[x] = fa;
	dpt[x] = dpt[fa] + 1;
	for(int i = e.hd[x]; i; i = e.nxt[i]) {
		int y = e.to[i];
		if(vis[y])
			continue;
		e.col[i] = e.col[i ^ 1] = 1;
		dfs(y, x);
	}
}

void Check() {
	for(int i = 2; i <= m * 2; i += 2)
		if(!e.col[i]) {
			B.push_back(e.pre[i]);
			B.push_back(e.to[i]);
			deg[e.pre[i]]++, deg[e.to[i]]++;
		}
	
	if(B.size() < 6)
		return ;
	for(auto it : B)//用于检查是否成环
		if(deg[it] < 2)
			return ;
	
	priority_queue<pair<int, int>> q;//用于找深度最大
	for(auto it : B)
		q.push(make_pair(dpt[it], it));
		
	int x = q.top().second;//取出这三个点中深度最深的 
	int l, r;//交换 l 和 r 的颜色 
	for(int i = e.hd[x]; i; i = e.nxt[i]) {
		int y = e.to[i];
		
		if(e.col[i] == 0)
			l = i;
		if(y == pa[x])
			r = i;
	}
	e.col[l] = e.col[l ^ 1] = 1;
	e.col[r] = e.col[r ^ 1] = 0;
}

int T;

int main()
{
	T = inpt();
	while(T--) {
//		memset(e.hd, 0, sizeof(e.hd));
//		memset(e.col, 0, sizeof(e.col));
//		memset(pa, 0, sizeof(pa));
//		memset(dpt, 0, sizeof(dpt));
//		e.tot = 1;
		
		n = inpt(), m = inpt();
		for(int i = 1; i <= m; ++i) {
			int x = inpt(), y = inpt();
			
			e.Add(x, y);
			e.Add(y, x);
		}
		
		memset(deg, 0, sizeof(deg));
		B.clear();
		memset(vis, false, sizeof(vis));
		dfs(1, 0);
		
		Check();
		
		for(int i = 2; i <= 2 * m; i += 2)
			printf("%d", e.col[i]);
		puts("");
		
		for(int i = 1; i <= n; ++i) {
			e.hd[i] = 0;
			pa[i] = 0;
			dpt[i] = 0;
			vis[i] = false;
			deg[i] = 0;
		}
		for(int i = 2; i <= e.tot; ++i) {
			e.col[i] = 0;
		}
		e.tot = 1;
	}
	

 	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# CF1726D 题解



## 思路分析

定义 $\mathbf G_R=(\mathbf V,\mathbf E_R)$，即所有红边构成的图，$\mathbf G_B=(\mathbf V,\mathbf E_B)$，即所有蓝边构成的图。

注意到有如下观察：

> 理论上 $c_1+c_2$ 的最小值应该是 $2\times n-m$，当且仅当 $\mathbf G_R$ 和 $\mathbf G_B$ 都是森林。
>
> 考虑一个逐个加边的过程，最开始答案应该是 $2\times n$，当我们加入一条边 $(u,v)$，加入后 $c_1+c_2$ 会减少 $1$ 当且仅当在与其同色的图中 $(u,v)$ 连接了两个不同的连通块，这是根据 $c_1+c_2$ 的定义得来的。
>
> 但我们又知道在一个森林中的每条边都是连接两个不同连通块的，因此每条边都对答案有 $1$ 的贡献，故当且仅当 $\mathbf G_R$ 和 $\mathbf G_B$ 中都是森林（即无环）时 $c_1+c_2$ 取得最小值 $2\times n-m$。

注意到 $m\le n+2$，这是一个非常好的性质，考虑如何利用。

在得到这个观察之后，我们有一个非常显然的想法：由于原图联通，所以让 $\mathbf G_R$ 为原图的一棵生成树，而此时 $\mathbf G_B$ 中至多只有 $3$ 条边。

那么选择怎样的 $\mathbf G_R$ 才能保证 $\mathbf G_B$ 也是森林呢？由于原图中没有重边，因此当且仅当 $\mathbf G_B$ 为一个三元环的时候 $\mathbf G_R$ 不合法。

注意到这样的 $\mathbf G_B$ 实际上不多，因此我们可以先随便确定一棵 $\mathbf G_R$，如果 $\mathbf G_B$ 是一个三元环，我们把 $\mathbf G_B$ 中的任意一条边放进 $\mathbf G_R$，然后在生成的环上随意断掉一条原来的树边即可。

不妨设我们向 $\mathbf G_R$ 中加入一条边 $(u,v)$，我们只需要找到一条在路径 $u\to v$ 上的边即可。

对于这个问题，我们有如下的观察：

> 在一条路径 $u\to v$ 中，假设 $u$ 为深度较大的点，那么 $u$ 到其父亲的边一定在路径 $u\to v$ 中。
>
> 证明很简单，假设 $u$ 是一个任意的点，考虑什么时候 $u$ 到其父亲的边不在路径 $u\to v$ 中，显然，如果 $u\ne \operatorname{lca}(u,v)$，那么 $u$ 到其父亲的边一定在路径中，而如果 $u=\operatorname{lca}(u,v)$，那么显然深度较大的点会变成 $v$，即此时我们必然不可能选择 $u$ 到其父亲的边，而是选择了 $v$ 到其父亲的边。

所以我们只需要随便取一棵 $\mathbf G_R$ 然后 dfs 预处理一下就可以了。

时间复杂度 $\Theta(m\alpha(n))$，$\alpha(n)$ 为反阿克曼函数。

### 代码呈现

```cpp
#include<bits/stdc++.h> 
#define pii pair<int,int>
using namespace std;
const int MAXN=2e5+5;
int dsu[MAXN],dep[MAXN],fa[MAXN];
bool col[MAXN];
vector <pii> G[MAXN];
inline void dfs(int p,int f) {
	for(auto e:G[p]) {
		int v=e.first;
		if(v==f) continue;
		dep[v]=dep[p]+1;
		fa[v]=e.second;
		dfs(v,p);
	}
}
inline int find(int x) {
	if(dsu[x]==x) return x;
	return dsu[x]=find(dsu[x]);
}
inline void solve() {
	int n,m,x=0,y=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) dsu[i]=i,G[i].clear();
	set <int> ver;
	vector <int> id;
	for(int i=1;i<=m;++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		int a=find(u),b=find(v);
		if(a==b) {
			ver.insert(u),ver.insert(v);
			if(!id.size()) x=u,y=v;
			col[i]=0,id.push_back(i);
		} else {
			col[i]=1,dsu[a]=b;
			G[u].push_back(make_pair(v,i));
			G[v].push_back(make_pair(u,i));
		}
	}
	dfs(1,0);
	if((int)id.size()==3&&(int)ver.size()==3) {
		col[id[0]]=1;
		if(dep[x]<dep[y]) swap(x,y);
		col[fa[x]]=0;
	}
	for(int i=1;i<=m;++i) printf("%d",col[i]);
	puts("");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：2020kanade (赞：0)

注意到本题的限制为 $m\le n+2$ 且为无重边自环的连通图，我们先考虑一些特殊情况：

首先，如果原图是树，那么边的颜色并不会影响答案：把图复制，选一个边集加到其中一个图，剩下的边加到另一个图，显然两者都是加一条边少一个连通块，至于是谁无所谓，答案显然是 $2\times n-m$。

由于继续加边可能成环，我们考虑这样几个性质：

一张无向图的 DFS 生成树的非树边都是返祖边；

无重边无自环的无向图，最小的含环的边双连通分量大小为 $3$；结合上一条，可得一条返祖边至少跨过两条树边；

如果图是树，任意划分红蓝边集不会影响答案。

我们在此基础上充分发扬人类智慧，求出任意 DFS 生成树后将树边按照深度奇偶性染色，对于最多 $3$ 条非树边，我们维护红边和蓝边的连通块，直接尝试加边即可。

这样做一定是对的，考虑此时单个颜色的连通块最大深度为 $2$，且原图没有重边，分类讨论所有情况即可证明。

时间复杂度 $\Theta(n\alpha(n))$，这里的冰茶姬是严格反阿克曼函数复杂度实现。


```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll mod1=998244353;
const ll mod2=1e9+7;
const ll mod3=1e9+9;
int t,n,k,m,q;
vector<pair<int,int > > G[N],T[N];
int dfn[N],dfc;int ans[N];
vector<pair<pair<int,int>,int>> bes;
bool det[N];
struct ufs
{
	int _n;vector<int> fas,szs;
	ufs(int sz=0):_n(sz)
	{
	    fas=szs=(vector<int>(_n+3,0));
		for(int i=1;i<=_n;++i) fas[i]=i,szs[i]=1;
	}
	int ask(int u)
	{
		if(fas[u]==u) return u;
		else return fas[u]=ask(fas[u]);
	}
	void aws(int u,int v)
	{
		u=ask(u),v=ask(v);
		if(u==v) return;
		if(szs[u]<szs[v]) swap(u,v);
		fas[v]=u;szs[u]+=szs[v];
	}
};
ufs qaq[2];
void dfs(int u,int ff)
{
	dfn[u]=++dfc;
	for(auto [v,id]:G[u])
	{
		if(v==ff) continue;
		if(!dfn[v])
		{
			dfs(v,u);
			T[u].push_back({v,id});
			T[v].push_back({u,id});
		}
		else if(!det[id])
		{
			det[id]=1;
			bes.push_back({{u,v},id});
		}
	}
}
void getans(int u,int ff,int col)
{
	for(auto [v,val]:T[u])
	{
		if(v==ff) continue;
		ans[val]=col;
		qaq[col].aws(u,v);
		getans(v,u,1-col);
	}
}
void clr()
{
	for(int i=1;i<=n;++i) G[i].clear(),T[i].clear(),dfn[i]=0;
	for(int i=1;i<=m;++i) ans[i]=det[i]=0;
	dfc=0;bes.clear();
}
void solve()
{
	cin>>n>>m;qaq[0]=qaq[1]=ufs(n+1);
	for(int i=1,iu,iv;i<=m;++i)
	{
		cin>>iu>>iv;
		G[iu].push_back({iv,i});
		G[iv].push_back({iu,i});
	}
	dfs(1,0);getans(1,0,1);
	for(auto[x,y]:bes)
	{
		int u=x.first,v=x.second;
		int col=1;
		if(qaq[col].ask(u)==qaq[col].ask(v)) col=1-col;
		//cout<<u<<' '<<v<<' '<<y<<' '<<col<<endl;
		ans[y]=col;qaq[col].aws(u,v);
	}
	for(int i=1;i<=m;++i) cout<<ans[i];cout<<endl;
	return clr();
}
int main()
{
    syncoff();
 	t=1;
    cin>>t;
    while(t--) solve();
    return 0;
}

```

---

## 作者：Priestess_SLG (赞：0)

很厉害就是了。

发现十分逆天的性质：$n-1\le m\le n+2$，因此推测对 $m$ 的值分类讨论。

1. $m=n-1$，此时图中无环，可以随便染色。
2. $m=n$，此时图中有一个环，因此考虑把这个环中任意一条边染为蓝色，其余所有边都染为红色。
3. $m=n+1$，此时考虑找出图的任意一个生成树，将生成树上所有边染为红色，其余边染为蓝色。此时蓝色边共计有 $2$ 条，不会形成新的环。
4. $m=n+2$，此时上面的操作可能不成功，即蓝色边共计有 $3$ 条且恰好形成了一个新的环。于是考虑~~SJH~~随机化
，每一次随机一个生成树，若此时生成了环则继续打乱，否则输出答案。

然后就过了。

代码（跑的极慢，有可能一遍过不去）：

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define eb emplace_back
// #define int long long
using namespace std;
const int N = 1000100;
int fa[N], res[N], id[N];
pair<int, int> ed[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0));
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; ++i) {
            cin >> ed[i].first >> ed[i].second;
            res[i] = 0;
            id[i] = i;
        }
        iota(fa + 1, fa + n + 1, 1ll);
        if (m < n + 2) {
            for (int i = 0; i < m; ++i) {
                int a = find(ed[i].first), b = find(ed[i].second);
                if (a != b) {
                    fa[a] = b;
                    res[i] = 1;
                }
            }
            for (int i = 0; i < m; ++i) {
                cout << res[i];
            }
            cout << '\n';
        } else {
            do {
                random_shuffle(id, id + m);
                fill(res, res + m, 0ll);
                iota(fa + 1, fa + n + 1, 1ll);
                vector<int> buc;
                for (int i = 0; i < m; ++i) {
                    int a = find(ed[id[i]].first), b = find(ed[id[i]].second);
                    if (a != b) {
                        fa[a] = b;
                        res[id[i]] = 1;
                    } else {
                        buc.emplace_back(i);
                    }
                }
                assert(buc.size() == 3);
                iota(fa + 1, fa + n + 1, 1ll);
                int ok = 1;
                for (auto &i : buc) {
                    int a = find(ed[id[i]].first), b = find(ed[id[i]].second);
                    if (a == b) {
                        ok = 0;
                        break;
                    }
                    fa[a] = b;
                }
                if (ok) {
                    for (int i = 0; i < m; ++i) {
                        cout << res[i];
                    }
                    cout << '\n';
                    break;
                }
            } while (1);
        }
    }
    return 0;
}

/*



*/
```

---

## 作者：lingying (赞：0)

# 题意

给定 $n$ 个点 $m$ 条边的连通图，对每条边进行红蓝染色，计 $R$ 为红色边组成的图的连通块个数，$B$ 为蓝色边组成的图的连通块个数，请你输出任意一种满足 $R+B$ 最小的方案。

注意算连通块个数时不要忘了孤立点。

$n\le 2\times 10^5,(n-1)\le m\le \min(n+2,\dfrac{n(n-1)}{2})$。

# 解法

怎么都是正经做法，提供一个随机化做法...

发现答案下界为 $2n-m$，考虑能否达到。

~~然后发现可以达到。~~

能否达到这个下界的关键在于红蓝边各自组成的图里没有环。

可以考虑让红边组成一颗生成树，蓝边为剩下的 $0/1/2/3$ 条边。只要蓝边之间没有环即可。

发现蓝边之间有环只有可能是 $3$ 条边的时候（因为没有重边），并且当它成环的时候，一定有方法调整。

什么办法呢，我们随机化（

每次搜索就把返祖边染蓝，搜索过后进行一次 check，如果成环就把边打乱重搜。

很无脑，这个随机化也很好想，并且这个东西是卡不掉的（$m$ 太小了），感觉在 CF 赛时是不错的选择。


# 代码

```
#include<bits/stdc++.h>
using namespace std;
 
const int N=2e5+5;
 
int _,n,m,idx;
int head[N],col[N];
bool vis[N];
struct edge
{
	int fr,to,id,ne;
}e[2*N];
struct node
{
	int x,y,id;
}a[N],b[N];
 
void add(int x,int y,int z)
{
	e[++idx].fr=x;
	e[idx].to=y;
	e[idx].id=z;
	e[idx].ne=head[x];
	head[x]=idx;
}
 
void dfs(int u,int fa)
{
	vis[u]=1;
	for(int i=head[u];i;i=e[i].ne)
	{
		int v=e[i].to;
		if(v!=fa)
		{
			if(vis[v])col[e[i].id]=1;
			else col[e[i].id]=0,dfs(v,u);
		}
	}
}
 
bool check()
{
	int p1=-1,p2=-1,p3=-1;
	for(int i=1;i<=m;i++)
		if(col[i])
			if(p1==-1)p1=i;
			else if(p2==-1)p2=i;
			else p3=i;
	if(p3==-1)return 1;
	int u1,v1,u2,v2,u3,v3;
	u1=b[p1].x;
	v1=b[p1].y;
	u2=b[p2].x;
	v2=b[p2].y;
	u3=b[p3].x;
	v3=b[p3].y;
	for(int i=1;i<=n;i++)vis[i]=0;
	vis[u1]=vis[v1]=vis[u2]=vis[v2]=vis[u3]=vis[v3]=1;
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(vis[i])
			cnt++;
	for(int i=1;i<=n;i++)vis[i]=0;
	return cnt!=3;
}
 
int main()
{
	mt19937 rnd(time(0));
	scanf("%d",&_);
	while(_--)
	{
		scanf("%d%d",&n,&m);
		idx=0;
		for(int i=1;i<=n;i++)head[i]=0;
		for(int i=1;i<=n;i++)vis[i]=0;
		for(int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);a[i]=node{u,v,i},b[i]=node{u,v,i};
			add(u,v,i),add(v,u,i);
		}
		int root=rnd()%n+1;
		dfs(root,0);
		while(!check())
		{
			idx=0;
			for(int i=1;i<=n;i++)head[i]=0;
			for(int i=1;i<=n;i++)vis[i]=0;
			shuffle(a+1,a+m+1,rnd);
			for(int i=1;i<=m;i++)add(a[i].x,a[i].y,a[i].id),add(a[i].y,a[i].x,a[i].id);
			root=rnd()%n+1;
			dfs(root,0);
		}
		for(int i=1;i<=m;i++)putchar(col[i]+'0');
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：yingkeqian9217 (赞：0)

## 题目描述

给定一个含有 $n$ 个点 $m$ 条边的无向简单图。

对这张简单图的所有边进行红蓝染色。其中**仅由红边**组成的无向图连通块数为 $c_1$，**仅由蓝边**组成的无向图连通块数为 $c_2$。

请构造一种染色方案使得 $c_1 + c_2$ 最小。如果有多种构造方案，任意输出一种即可。

请注意 $m \leqslant n + 2$ 意味着什么。

## 分析

本题中要求的是连通块个数，因为总边数限制，可以想到环对连通块的影响。也就是说，要尽量保证红蓝都没有环，即尽量为树状。

若一种颜色为某个子图的生成树，那么另一种颜色将无法保证。考虑使红色为整个图的生成树，那么蓝色的边数 $eb=m-n+1\le 3$，相对更加好处理一些。

此时，红色的连通块个数为 $1$，蓝色的连通块个数最优为 $n-eb$。所谓最优，就是再没有环的条件下。因为原图是简单图，所以此时的环，长度必定 $\ge 3$。结合 $eb\le 3$，得到只有在 $eb=3$ 使才会有环，我们特判即可。

具体来说，我们可以用类似 `kruskal` 求最小生成树的方法，即使用并查集统计此边是否有作用。判断蓝色是否为环时，我们统计度数即可，最后将环的其中一边换掉，也就是将原红色中与此边起相同作用的边从红色中删去即可。

## AC CODE
```
#include<bits/stdc++.h>
#define maxn 2900001
using namespace std;
int T,n,m,fa[maxn],u[maxn],v[maxn],d[maxn];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void init(){
	for(int i=1;i<=n;i++) fa[i]=i,d[i]=0;
}
void solve(){
	int flag=0,lst=0;
	vector<int>ans;
	scanf("%d%d",&n,&m);
	init();
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u[i],&v[i]);
		if(find(u[i])!=find(v[i]))
		 fa[find(u[i])]=find(v[i]),ans.push_back(1);
		else{
			flag+=(++d[u[i]]==2);
			flag+=(++d[v[i]]==2);
			ans.push_back(0);
			lst=i;
		}
	}
	if(flag==3){
		init();
		fa[find(u[lst])]=find(v[lst]);
		for(int i=0;i<m;i++)
		 if(ans[i]){
		 	if(find(u[i+1])==find(v[i+1])){
		 		ans[i]=0;
		 		break;
			 }
			fa[find(u[i+1])]=find(v[i+1]);
		 }
		ans[lst-1]=1;
	}
	for(int i:ans)
	 printf("%d",i);
	puts("");
}
signed main(){
	scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}
```

---

