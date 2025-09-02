# [COTS 2025] 砍树 / Stablo

## 题目描述


**这是一道交互题。本题中，交互库是非自适应的。**

有一棵 $N$ 个节点的树。这棵树中，每个节点度数至多为 $3$。

你可以提问至多 $K=2.5\times 10^5$ 次。每次给定三个两两不同的节点 $a,b,c$，交互库会回答：

- $\text{0}$，如果 $\operatorname{dist}(a,b)=\operatorname{dist}(a,c)$;
- $\text{1}$，如果 $\operatorname{dist}(a,b)\lt\operatorname{dist}(a,c)$;
- $\text{2}$，如果 $\operatorname{dist}(a,b)\gt\operatorname{dist}(a,c)$。  

定义 $\operatorname{dist}(u,v)$ 表示 $u,v$ 最短路上边的数量。

试通过询问还原这棵树。

虽然你可以提问 $K=2.5\times 10^5$ 次，但是想要获得更高的分数，需要更少的询问次数。见「计分方式」。

### 实现细节

首先读入正整数 $N$。读入后发起询问：

- $\texttt{?}$ $a$ $b$ $c$：发起一次询问。
    - 你需要保证 $1 \leq a, b, c \leq N$ 且 $a \neq b$，$b \neq c$，$c \neq a$。
    - **最多可以询问 $2.5\times 10^5$ 次。**
    - 从标准输入流读入一个整数表示答案，具体见「题目描述」。
- $\texttt{!}$：报告答案。
    - 输出 $\texttt{!}$ 后，接下来再输出 $(N-1)$ 行，每行两个正整数，描述一条树边。
    - 你可以以任意顺序输出这 $(N-1)$ 条边。
    - 报告答案后，你的程序必须终止运行。
     

**每次提问后，都需要换行并刷新缓冲区。**

**交互库是非自适应的**。也就是说，树的形态在交互开始前已经固定。

## 说明/提示


### 样例解释

样例中，树边有 $\{(1,2),(2,3),(3,4)\}$。

### 数据范围

- $N\lt 512$；
- 每个节点度数至多为 $3$。


### 子任务

- $\text{Subtask 0 (0 pts)}$：样例。
- $\text{Subtask 1 (10 pts)}$：每个节点度数至多为 $2$。
- $\text{Subtask 2 (20 pts)}$：树是满二叉树。
    - 换句话说，树是完全二叉树，且存在正整数 $k$ 使得 $N=2^k-1$。
- $\text{Subtask 3 (70 pts)}$：无额外限制。

### 计分方式

答案错误，询问次数超限，或者出现了任何未能成功运行结束的情况，得 $0$ 分。

假设你在某个分值为 $B$ 的子任务中至多用了 $K$ 次查询，则子任务得分为

$$\min\left(1, \left(\frac{14000}{K}\right)^{0.7}\right) \cdot B$$

**交互库是非自适应的**。也就是说，树的形态在交互开始前已经固定。


## 样例 #1

### 输入

```
4

1

2

0



```

### 输出

```

? 1 2 3

? 1 4 3

? 2 1 3

!
1 2
2 3
3 4```

# 题解

## 作者：EuphoricStar (赞：7)

有点意思的题。

考虑逐个加点。假设已经维护出来原树的一个连通块，我们现在要加入一个新点，即挂一个叶子到这个连通块上。

考虑边分治去找新点应该挂到哪个点上。每次找到一条边 $(u, v)$ 使得它连接的两棵子树大小最大值最小。设新点为 $x$，询问一次 $(x, u, v)$ 即可知道 $x$ 在 $u$ 子树内还是 $v$ 子树内，扔掉另一棵子树然后继续做直到只剩一个点即可。由于树是二叉树所以对于一个 $x$ 至多问 $O(\log n)$ 次，加入 $n$ 个点总共问 $O(n \log n)$ 次。

问题还剩下如何保证新点一定是连通块的叶子。考虑将所有点按照与 $1$ 的距离从小到大排序，依次加入即可。排序需要 $O(n \log n)$ 次询问。

所以我们就以 $O(n \log n)$ 的询问次数做完了。询问次数实际表现差不多是 $2n \log n$。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 520;

int n, p[maxn];
bool vis[maxn];
pii e[maxn];
vector<int> G[maxn];
map< pair< pair<int, int>, int >, int > mp;

inline int ask(int a, int b, int c) {
	if (mp.find(mkp(mkp(a, b), c)) != mp.end()) {
		return mp[mkp(mkp(a, b), c)];
	}
	printf("? %d %d %d\n", a, b, c);
	fflush(stdout);
	int x;
	scanf("%d", &x);
	return mp[mkp(mkp(a, b), c)] = x;
}

int sz[maxn], fa[maxn];

void dfs(int u, int t) {
	sz[u] = 1;
	fa[u] = t;
	for (int v : G[u]) {
		if (v == t || !vis[v]) {
			continue;
		}
		dfs(v, u);
		sz[u] += sz[v];
	}
}

void dfs2(int u, int fa) {
	vis[u] = 0;
	for (int v : G[u]) {
		if (v == fa || !vis[v]) {
			continue;
		}
		dfs2(v, u);
	}
}

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		p[i] = i;
	}
	stable_sort(p + 2, p + n + 1, [&](const int &x, const int &y) {
		return ask(1, x, y) == 1;
	});
	G[1].pb(p[2]);
	G[p[2]].pb(1);
	e[1] = mkp(1, p[2]);
	for (int i = 3; i <= n; ++i) {
		mems(vis, 0);
		for (int j = 1; j < i; ++j) {
			vis[p[j]] = 1;
		}
		while (1) {
			int cnt = 0, u = 0;
			for (int j = 1; j < i; ++j) {
				if (vis[p[j]]) {
					++cnt;
					u = p[j];
				}
			}
			if (cnt == 1) {
				e[i - 1] = mkp(u, p[i]);
				G[u].pb(p[i]);
				G[p[i]].pb(u);
				break;
			}
			dfs(u, -1);
			int mn = 1e9, w = -1;
			for (int j = 1; j < i; ++j) {
				int v = p[j];
				if (u != v && vis[v] && max(sz[v], cnt - sz[v]) < mn) {
					mn = max(sz[v], cnt - sz[v]);
					w = v;
				}
			}
			if (ask(p[i], w, fa[w]) == 1) {
				dfs2(fa[w], w);
			} else {
				dfs2(w, fa[w]);
			}
		}
	}
	puts("!");
	for (int i = 1; i < n; ++i) {
		printf("%d %d\n", e[i].fst, e[i].scd);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Mirasycle (赞：1)

经典构建一颗树的交互，这种题我们一般是要求出每个点的深度，然后按照深度分层加入。

本题中，我们先以 $1$ 为根，然后剩下所有点按照深度排序。依次加入，这样子保证新加入的点一定是当前联通块的一个叶子节点。于是我们需要找到这个点 $x$ 连向哪个点，可以使用边分治，找到一条边 $(u,v)$ 使得其两侧联通块大小尽量接近，然后 $(u,v,x)$ 即可得到 $x$ 是在哪个联通块之中，递归下去即可。这是一个边分治的过程，由于这是一颗二叉树，所以边分治的复杂度是对的。

第一次排序需要花费 $O(n\log n)$ 次，第二次单点加入是 $O(\log n)$，加入 $n-1$ 个点是 $O(n\log n)$ 次。

所以总的次数是 $O(n\log n)$ 次。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef vector<int> vi;
const int maxn=600;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int n,fa[maxn],vis[maxn],p[maxn],sz[maxn],core,siz; 
vi G[maxn],nS,vec; int deta;
int query(int x,int y,int z){
	cout<<"? "<<x<<" "<<y<<" "<<z<<endl;
	fflush(stdout); int X; cin>>X; return X;
} 
bool cmp(int x,int y){ return (query(1,x,y)==1); }
void dfs(int u){
	vis[u]=1; sz[u]=1;
	for(auto v:G[u]){
		if(vis[v]) continue;
		fa[v]=u; dfs(v); sz[u]+=sz[v];
	}
	if(abs(2*sz[u]-siz)<deta) core=u,deta=abs(2*sz[u]-siz);
}
void find(int u){
	vis[u]=2;
	for(auto v:G[u]){
		if(vis[v]||v==fa[u]) continue;
		find(v);
	}
}
void ins(int u,vi S){
	if(S.size()==1){ G[S.back()].pb(u); G[u].pb(S.back()); return ; }
	for(auto z:S) vis[z]=sz[z]=fa[z]=0; 
	siz=S.size(); deta=600; core=0;
	dfs(S.front()); assert(core);
	for(auto z:S) vis[z]=0;
	find(core); int z=query(u,core,fa[core]);
	nS.clear();
	if(z==1){
		for(auto v:S) 
			if(vis[v]==2) nS.pb(v);
	}else{
		for(auto v:S) 
			if(vis[v]!=2) nS.pb(v);
	}
	ins(u,nS);
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n;
	if(n==2){
		cout<<"!"<<endl;
		cout<<1<<" "<<2<<endl;
		return 0;
	}
	for(int i=1;i<=n-1;i++) p[i]=i+1;
	sort(p+1,p+n,cmp); vec.pb(1);
	for(int i=1;i<=n-1;i++) ins(p[i],vec),vec.pb(p[i]);
	cout<<"!"<<endl;
	for(int u=1;u<=n;u++)
		for(auto v:G[u])
			if(u<v) cout<<u<<" "<<v<<endl;
	return 0;
}
```

---

## 作者：2019yyy (赞：1)

来点乱搞。

思路很简单，对于现在已经做好的一棵树，你要往上面新放一个点，只需要从根开始二叉搜索。

总共只会遇到三种情况：

1. 这个点只有一个儿子，直接向下跑。
2. 这个点有两个儿子，比较一下它们，取离要添加的点较近的向下搜索。
3. 这个点有三个儿子，任取两个儿子比较，如果它们距离相等，则取第三个，否则取较近的。

由于这么做还需要知道我们到没到因该向上挂点的那一层，所以我们需要跑出深度来。

具体做法就是利用排序，用 $O(n \log n)$ 次操作，把 $dep$ 的先后顺序跑出，再依次前后比较一遍，得到 $dep$ 大小。

有些点它没有儿子在你要放的点的上一层，它们根本不用考虑，这样我们可以减少比较次数。

不知道为什么比较次数是对的，但感性的想确实比较优，跳过了所有单个儿子的链，使在树的真正有用的深度在大约 $O(\log)$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110000],cnt,dep[110000],lowdep[110000];
int query(int x,int y,int z){
    cout<<"? "<<x<<" "<<y<<" "<<z<<endl;
    int res;cin>>res;
    return res;
}
bool cmp(int x,int y){ return query(1,x,y)==1; }
vector<int> g[110000];
vector<pair<int,int> > ans;
int dfs(int now,int x){
    lowdep[x]=dep[now];
    if(dep[x]+1==dep[now]) return x;
    vector<int> f;
    for(auto to:g[x]) if(lowdep[to]>=dep[x]-1) f.push_back(to);
    if(f.size()==1) return dfs(now,f[0]);
    if(f.size()==2){
        int t=query(now,f[0],f[1]);
        if(t==1) return dfs(now,f[0]);
        else return dfs(now,f[1]);
    }
    if(f.size()==3){
        int t=query(now,f[0],f[1]);
        if(t==0) return dfs(now,f[2]);
        else if(t==1) return dfs(now,f[0]);
        else return dfs(now,f[1]);
    }
    return -0721;
}
int main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++) a[i]=i;
    sort(a+2,a+n+1,cmp);lowdep[a[2]]=dep[a[2]]=++cnt;
    for(int i=3;i<=n;i++){
        if(query(1,a[i-1],a[i])==1) cnt++;
        lowdep[a[i]]=dep[a[i]]=cnt;
    }
    for(int i=2;i<=n;i++){
        int fa=dfs(a[i],1);
        g[fa].push_back(a[i]),ans.push_back({fa,a[i]});
    }
    cout<<"!"<<endl;
    for(auto now:ans) cout<<now.first<<" "<<now.second<<endl;
    return 0;
}
```

---

## 作者：Undead2008 (赞：1)

[COTS 2025 题解合集](https://www.luogu.com.cn/article/dupadkce)

考虑硬点 $1$ 作为根，这时候 $\text{cmp}(1,i,j)$ 相当于比较 $i$ 和 $j$ 在树上的深度，可以将所有节点按照深度先排序再分层，一层一层加入。

加入新一层的某个节点 $x$ 时需要求出他挂在了上一层哪个叶子上，可以对原树进行树剖维护往下跳的过程，然后在每条重链上二分一个点 $p$，表示 $x$ 在 $p$ 的轻子树中或者 $x$ 就是 $p$（此时 $p$ 为重链链底，是叶子）。

二分到 $M$，check 就是问 $\text{cmp}(x,M,\text{son}_M)$，如果返回 $2$，则说明 $p$ 在 $\text{son}_M$ 的子树内，反之同理。

因为是二叉树，找到 $p$ 直接往轻儿子跳就行了，如果有两个轻儿子得特判。

这个询问次数是两个 $\log$，但是他直接过了，信仰树剖神教，易写作，小常数，卡不满！

使用全局平衡二叉树的技巧可以一个 $\log$。

---

## 作者：Sliarae (赞：1)

乱搞做法，我也不知道为啥对。

任意选取树上的一个点作为根，设结点 $i$ 的深度为 $\text{dep}_i$，用 $O(n \log n)$ 次操作可以将所有点按 $\text{dep}_i$ 排序，从而求出所有 $\text{dep}_i$。

考虑每次扩展一层，从 $1 \sim n$ 枚举 $d$，将 $\text{dep} = d$ 的点加入到树上，这个时候我们有两个直观的想法：

- 对于每个 $\text{dep} = d$ 的点 $u$，通过询问比较出它到所有 $\text{dep} = d - 1$ 的点中距离最小者为 $v$，则 $v$ 是 $u$ 的父亲。但是如果 $\text{dep} = d - 1$ 的点特别多的时候会炸。

- 对于每个 $\text{dep} = d$ 的点 $u$，由 $\text{deg} \le 3$ 是二叉树（特别地，根可能有 $3$ 个儿子，不过影响不大），于是可以在上面二叉搜索。但是树特别高的时候会炸。

所以我们这样做，对所有 $\text{dep} = d - 1$ 的点建虚树，然后在虚树上二叉搜索，这样好像就不太好卡了。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
using Pii = pair<int, int>;

const int kN = 515;

int n, m; 
vector<int> st[kN], son[kN];
int fa[kN], dep[kN];
int dfn[kN], now;
vector<int> vt[kN];

int Query (int a, int b, int c) {
  cout << "? " << a << ' ' << b << ' ' << c << endl;
  int ret;
  cin >> ret; 
  return ret;
}

vector<int> Sort (int p, vector<int> v) {
  stable_sort(v.begin(), v.end(), [&](int a, int b) -> bool {
    return Query(p, a, b) == 1; 
  });
  return v;
}

void Dfs (int u) {
  dfn[u] = ++now;
  for (auto v : son[u]) Dfs(v);
}

int Lca (int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  while (dep[u] > dep[v]) u = fa[u];
  while (u != v) u = fa[u], v = fa[v];
  return u;
}

int main () {
  cin >> n;
  vector<int> all(n - 1);
  iota(all.begin(), all.end(), 2);
  all = Sort(1, all);
  st[0].push_back(1);
  for (int i = 0; i < n - 1; ++i) {
    if (!i || Query(1, all[i - 1], all[i]) == 1) {
      ++m;
    }
    st[m].push_back(all[i]), dep[all[i]] = m;
  }
  vector<Pii> ans;
  for (int i = 1; i <= m; ++i) {
    // cout << "start i = " << i << '\n'; 
    now = 0, Dfs(1);
    vector<int> vec = st[i - 1];
    sort(vec.begin(), vec.end(), [&](int i, int j) -> bool {
      return dfn[i] < dfn[j];
    });
    for (int i = 0, tmp = vec.size(); i < tmp - 1; ++i) vec.push_back(Lca(vec[i], vec[i + 1]));
    sort(vec.begin(), vec.end(), [&](int i, int j) -> bool {
      return dfn[i] < dfn[j];
    });
    for (int i = 1; i <= n; ++i) vector<int>().swap(vt[i]);
    // cout << "d = " << i << '\n';
    for (int i = 0; i < vec.size() - 1; ++i) {
      int u = Lca(vec[i], vec[i + 1]), v = vec[i + 1];
      vt[u].push_back(v); 
      // cout << "vt " << u << ' ' << v << '\n';
    }
    int rt = vec[0];
    for (auto x : st[i]) {
      int cur = rt;
      while (true) {
        if (vt[cur].empty()) {
          // cout << "get " << cur << ' ' << x << '\n';
          fa[x] = cur;
          son[cur].push_back(x);
          ans.emplace_back(cur, x);
          break;
        }
        vector<int> lis = Sort(x, vt[cur]);
        cur = lis[0];
      }
    }
  }
  cout << "! " << endl;
  for (auto i : ans) cout << i.first << ' ' << i.second << endl;
  return 0; 
}
```

---

