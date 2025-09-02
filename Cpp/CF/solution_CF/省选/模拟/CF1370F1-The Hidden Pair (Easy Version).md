# The Hidden Pair (Easy Version)

## 题目描述

Note that the only difference between the easy and hard version is the constraint on the number of queries. You can make hacks only if all versions of the problem are solved.

 This is an interactive problem.

You are given a tree consisting of $ n $ nodes numbered with integers from $ 1 $ to $ n $ . Ayush and Ashish chose two secret distinct nodes in the tree. You need to find out both the nodes. You can make the following query:

- Provide a list of nodes and you will receive a node from that list whose sum of distances to both the hidden nodes is minimal (if there are multiple such nodes in the list, you will receive any one of them). You will also get the sum of distances of that node to the hidden nodes.

Recall that a tree is a connected graph without cycles. The distance between two nodes is defined as the number of edges in the simple path between them.

More formally, let's define two hidden nodes as $ s $ and $ f $ . In one query you can provide the set of nodes $ \{a_1,       a_2, \ldots, a_c\} $ of the tree. As a result, you will get two numbers $ a_i $ and $ dist(a_i, s) + dist(a_i, f) $ . The node $ a_i $ is any node from the provided set, for which the number $ dist(a_i, s) + dist(a_i, f) $ is minimal.

 You can ask no more than $ 14 $ queries.

## 说明/提示

The tree from the first test is shown below, and the hidden nodes are $ 1 $ and $ 3 $ .

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1370F1/deea4b0040e770b1c1e50ebf95e24ae594eea667.png)

## 样例 #1

### 输入

```
1
3
1 2
1 3

1 1

2 3

3 1

3 1

Correct```

### 输出

```
? 1 1

? 1 2

? 1 3

? 2 2 3

! 1 3```

# 题解

## 作者：Loser_Syx (赞：3)

教练把这题和另外三道逆天题搞成了一个一蓝三紫的 noip 模拟赛，这下这下了。

我们记 $dis(u,v)$ 为 $u$ 到 $v$ 最短路径长度，$x,y$ 为两个标记点，则 $dis(x,y) = \text{?}\ n\  a_1,a_2,a_3,\ldots,a_n$。

我们考虑此时询问得到的顶点 $u$，它一定存在于 $x\rightarrow y$ 的最短路径上，由于是树所以此路径唯一，那么以 $u$ 为根后，$x,y$ 一定是把 $dis(x,y)$ 分成了两段：$dis(x,u)$ 与 $dis(y,u)$，我们这里默认 $dis(x,u) > dis(y,u)$ 即 $dep_x > dep_y$。

因为 $u$ 是 $x\rightarrow y$ 的一条路径，所以 $u\rightarrow x$ 一定依次经过深度为 $1 \sim dep_x$ 的，在这些点到 $x,y$ 的路径长度一定 $dis(x,y)$（到 $y$ 的路径长度增加等同于到 $x$ 路径减少的那么多），而在深度 $> dep_x$ 的点时一定包含了 $x \rightarrow y$ 的路径和一些其他乱七八槽的路径，所以一定比第一次询问的长度大。

如此可见满足单调性，可以二分深度得出 $x$，每次二分的 $mid$，因为我们不知道 $x$ 是哪一个，把同样深度的所有点一起塞进去询问即可，最后根据返回长度进行收缩区间。

因为在 $dep_i = dep_x$ 的 $i$ 的答案中，$i$ 永远是要多走一段路走到 $x \rightarrow y$ 的路径上的，所以 $x$ 是唯一的（或者当 $dep_x = dep_y$ 时为唯二的），无论如何，返回的点一定是一个答案。

接下来考虑以该点为根，查询新的深度等于 $dis(x,y)+1$ 的那些点（$+1$ 是因为点比边多一），得到的 $y$ 一定是唯一的，证明见上。

算下来次数一共是 $1 + \lceil \log_2 n \rceil + 1$ 次，共 $12$，足以通过此题。

哦对了还有一个注意点是不能查询空集，所以二分的右端点是 $\max dep_i$。

```cpp
const int N = 1010;
vector<int> g[N], all, d[N];
int dep[N], dmax;
void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	smax(dmax, dep[u]);
	d[dep[u]].emplace_back(u);
	for (const int i : g[u]) if (i != fa) dfs(i, u);
}
signed main() {
	int t; cin >> t;
	while (t--) {
		int n; dmax = 0; cin >> n;
		for (int i = 1; i <= n; ++i) g[i].clear(), d[i].clear();
		for (int i = 1, u, v; i < n; ++i) {
			cin >> u >> v;
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
		cout << "? " << n << ' ';
		for (int i = 1; i <= n; ++i) cout << i << ' ';
		cout << endl;
		int root, dis; cin >> root >> dis;
		dfs(root, 0);
		int l = 1, r = dmax, ans;
		while (l <= r) {
			int mid = (l + r) >> 1;
			cout << "? " << d[mid].size() << ' ';
			for (const int i : d[mid]) cout << i << ' ';
			cout << endl;
			int s, t; cin >> s >> t;
			if (t == dis) ans = s, l = mid + 1;
			else r = mid - 1;
		}
		for (int i = 1; i <= n; ++i) d[i].clear();
		dfs(ans, 0);
		int a, b;
		cout << "? " << d[dis + 1].size() << ' ';
		for (const int i : d[dis + 1]) cout << i << ' ';
		cout << endl;
		cin >> a >> b;
		cout << "! " << ans << ' ' << a << '\n';
		fflush(stdout);
		string s; cin >> s;
	}
	return 0;
}
```

---

## 作者：45dinо (赞：3)

从7.31~8.2，蒟蒻终于 $A$ 了这~~一~~两道题，祭之。

~~不仅是两道紫题，还是两道题解，四倍经验~~。

每一步骤都会画图实现，加深理解。

样例（测试点 #3的第三组数据）
```
5
隐藏的点为（1，2）
5 2
1 4
4 2
3 5

```

第一次询问所有的点，得到一个点 $x$ ，这个点是两个隐藏点（设为 $a,b$ )路径上的一点。同时得到了 $a,b$ 的距离 $y$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hj7amorr.png)

接下来以 $x$ 为根节点进行一次 $DFS$ ，处理出每一个点的深度，同时将深度相同的点放到同一个集合里， $d_i$ 存储的是所以深度为 $i$ 的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/ght0l0f9.png)

下面要算 $a,b$ 中深度较大的一个点（假设是 $a$），可以使用二分实现。

可以发现，如果深度 $i$ 小于等于 $a$ 的深度，那么 $d_i$ 中必有一点到 $a,b$ 的距离和为 $y$ ，反之则没有，如果 $i$ 是 $a$ 的深度，那么这个点就是 $a$。

此处就可以用二分实现。

![](https://cdn.luogu.com.cn/upload/image_hosting/6cj74l51.png)

然后就可以问出 $a$ 的值。

再以 $a$ 为根节点进行一次 $DFS$ ，仅将深度为 $y$ 的点存储起来，因为这里面必然有 $b$ ，询问这个集合即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/stv3bvad.png)

---

## 作者：sunkuangzheng (赞：1)

虽然这题我想了快 1h 才会，但还是建议降蓝。（

$\Large \textbf{1.Hints}$

$\textbf{1.1 Hint 1}$

设关键点为 $u,v$，考虑什么样的点 $x$ 满足 $\operatorname{dis}(u,x) + \operatorname{dis}(v,x)$ 取 $\min$。

$\textbf{1.2 Hint 2}$

如果知道一个端点 $u$ 和答案 $w$，你可以在 $1$ 此询问内得到 $v$。

$\textbf{1.3 Hint 3}$

先找到一个满足 $\operatorname{dis}(u,x) + \operatorname{dis}(v,x)$ 取 $\min$ 的点 $x$，二分查找端点 $u$。

$\textbf{1.4 Hint 4}$

每次询问固定深度的点。

$\Large \textbf{2.Solution}$

显然的，满足 $\operatorname{dis}(u,x) + \operatorname{dis}(v,x)$ 取 $\min$ 的点 $x$ 在 $u \to v$ 的链上。考虑不在链上的点，一定会多走若干距离到 $u,v$。

当你知道一个端点 $u$ 和答案 $w$，你可以询问以 $u$ 为根深度 $w+1$ 的所有点，显然点 $v$ 唯一存在于这个深度。

如何找到一个端点 $u$？我们先问出距离和 $dis$，寻找 $u,v$ 中深度较大的那个，这里记为 $u$。每次询问深度为 $mid$ 的所有点，若 $dep_{mid} \le dep_{u}$，那么深度为 $mid$ 的点的答案为 $dis$；否则，答案一定大于 $dis$。二分即可。

总共需要 $1+\lceil\log_2(n)\rceil+1=12$ 次，可以通过 easy version。

如何省去最后一次询问？请参考 hard version 题解。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 23.10.2023 10:47:19
**/
#include<bits/stdc++.h>
using namespace std;
int t,n,k,w,u,v,dep[1005],nk,t1,t2;vector<int> acc,g[1005],d[1005];string sb;
pair<int,int> ask(vector<int> &acc){
    cout << "? " << acc.size() << " ";
    for(int i : acc) cout << i << " ";
    cout << endl,cin >> k >> w;return {k,w};
}void dfs(int u,int fa){
    dep[u] = dep[fa] + 1,d[dep[u]].push_back(u);
    for(int v : g[u]) if(v != fa) dfs(v,u);
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t --){
        cin >> n,acc.clear();
        for(int i = 1;i <= n;i ++) g[i].clear(),acc.push_back(i),d[i].clear();
        for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
        auto [u,nk] = ask(acc);dfs(u,0);
        int l = 1,r = *max_element(dep+1,dep+n+1),ans = -1;
        while(l <= r){
            int mid = (l + r) / 2;
            if(auto [t1,t2] = ask(d[mid]);t2 == nk) ans = t1,l = mid + 1;
            else r = mid - 1;
        }for(int i = 1;i <= n;i ++) d[i].clear();
        dfs(ans,0);auto [res,fkccf] = ask(d[nk + 1]);
        cout << "! " << ans << " " << res << endl,cin >> sb;
    }
}
```

---

## 作者：lgswdn_SA (赞：1)

~~为了让hard version和easy version的题解数量一样，这道题的两篇题解我全扔这里好了~~

我们设 $x,y$ 为 hidden nodes，并且 $d(u,v)$ 代表 $u,v$ 两点的距离。

## 1 Easy Version

首先一个很简单的观察：满足 $d(u,x)+d(u,y)$ 的最小的点 $u$ 一定是 $[x,y]$ 路径上的点。所以，我们通过一次全局询问就可以得到一个 $[x,y]$ 路径上的点 $r$ 以及 $u,v$ 之间的距离。

我们以 $r$ 为根，提树。然后 $[x,y]$ 路径就成了一个跨越根节点的路径。长成这样。

![image.png](https://i.loli.net/2021/02/04/WmunQPA3r4DN6vC.png)

（绿色三角代表树，橙色曲线代表路径）

我们需要找到一个点。考虑找到更深的 $x$ 点。（我们令深度相同的点形象地组成一个层）由于对于深度不大于 $x$ 的每一层，$d(u,x)+d(u,y)=d(u,v)$ 并且对于深度大于 $x$ 的每一层，$d(u,x)+d(u,y)>d(u,v)$，我们可以二分出深度等于 $x$ 的深度的那一层。显然，那一层的查询可以告诉我们 $x$ 是什么。

然后我们以 $x$ 为根，提树。此时深度为 $d(x,y)$ 的那一层上并且在路径上的点也是唯一的，是 $y$。

我们可以通过 $2+\log(n)$ 次询问得到答案。极端形况下是 $12$ 次。

## 2 Hard Version

差一次，考虑能不能松一松。

第一步和最后一步明显没法弄掉。那二分答案的时候呢？

设 $dep_r(u)$ 为以 $r$ 为根时 $u$ 的深度。由于 $dep_r(x)+dep_r(y)=d(x,y)$ 并且 $dep_r(x)\ge dep_r(y)$，所以有 $dep_r(x)\ge \frac{d(x,y)}{2}$。所以实际上我们可以把 $\log(n)$ 松成 $\log(n/2)$，极端情况下是 $11$ 次就可以通过了。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=1009;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int T,d[N],mx;
vector<int>e[N],fl[N],tmp;
char res[N];

void print(vector<int>v) {
	printf("? %d ",v.size());
	for(auto i:v) printf("%d ",i); puts("");
	fflush(stdout);
}

void dfs(int u,int fa) {
	for(auto v:e[u]) {
		if(v==fa) continue;
		d[v]=d[u]+1, mx=max(mx,d[v]);
		dfs(v,u);
	}
}

int main() {
	T=read();
	while(T--) {
		int n=read();
		rep(i,1,n) e[i].clear();
		rep(i,2,n) {
			int u=read(), v=read();
			e[u].push_back(v), e[v].push_back(u);
		}
		tmp.clear();
		rep(i,1,n) tmp.push_back(i);
		print(tmp);
		int rt=read(), dis=read();
		d[rt]=mx=0;
		dfs(rt,0);
		rep(i,0,n) fl[i].clear();
		rep(i,1,n) fl[d[i]].push_back(i);
		int l=dis/2,r=min(mx,dis),x=0;	//优化的地方1 
		while(l<=r) {
			int mid=(l+r)/2;
			print(fl[mid]);
			int a=read(), da=read();
			if(da==dis) x=a, l=mid+1;
			else r=mid-1;
		}
		d[x]=0;
		dfs(x,0);
		tmp.clear();
		rep(i,1,n) if(d[i]==dis) tmp.push_back(i);
		print(tmp);
		int y=read(), dt=read();
		printf("! %d %d\n",x,y);
		fflush(stdout);
		scanf("%s",res+1);
		if(res[1]!='C') {
			puts("F**k you Mr. interactor.");   //优化的地方2（雾 
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：墨舞灵纯 (赞：1)

### 题意

给定一棵树，有两个点 $a,b$ 被暗中标记，每次可以询问一个集合，会返回这个集合里的某个节点 $u$ ，满足 $dis_{a,u}+dis_{b,u}$ 最小。请在 $14$ 次以内完成询问并输出被标记的点。

### 题解

考虑如何知道 $s \rightarrow t$ 的路径长度：把所有点拿去询问一遍。这样我们一定会得到路径上的任意一点 $x$ 以及路径长度 $L$ 。

然后我们把 $x$ 作为树的根 $root$ 进行 $dfs$ ，这样我们就是找两个点 $a,b$ 使得 $dis_{a,root}+dis_{b,root}=L$ ，易得知一定有一个点到 $root$ 的距离 $\geq \lceil \frac{L}{2} \rceil$ ，另一个点到 $root$ 的距离 $\leq \lfloor \frac{L}{2} \rfloor$ ，又发现$14-1=13≈log_2(1024)$ ，也就是最多进行 $log$  次询问，可以想到二分。所以我们二分其中一个点到 $root$ 的距离再通过询问找另一个点就可以了。

### 注意

每次要读入一个表示正确和错误的字符串！

### 代码

$\color{#abcdef}{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int h[N], nxt[N], adj[N], u, v, t, rot, T, L, d[N], n;
string tmp;
vector<int> vec, g[N];
inline void add() { nxt[++t] = h[u], h[u] = t, adj[t] = v, nxt[++t] = h[v], h[v] = t, adj[t] = u; }
inline void que() {
    cout << '?' << ' ' << vec.size();
    for (const int &i : vec) cout << ' ' << i;
    cout << endl, cout << flush, cin >> u >> v;
}
void dfs(int x, int fa) {
    d[x] = d[fa] + 1, g[d[x] - 1].push_back(x);
    for (int i = h[x]; i; i = nxt[i])
        if (adj[i] != fa)
            dfs(adj[i], x);
}
void dfs(int x, int fa, int dis) {
    if (!dis) return vec.push_back(x), void();
    for (int i = h[x]; i; i = nxt[i])
        if (adj[i] != fa)
            dfs(adj[i], x, dis - 1);
}
void MidSearch() {
    int l = L + 1 >> 1, r = L, mid, s = 0;
    while (l <= r) {
        mid = l + r >> 1, vec = g[mid];
        if (vec.empty()) {
            r = mid - 1;
            continue;
        }
        que(), v <= L ? s = u, l = mid + 1 : r = mid - 1;
    }
    vec.clear(), dfs(s, 0, L), que(), cout << '!' << ' ' << s << ' ' << u << endl, cout << flush;
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> T; int i;
    while (T--) {
        cin >> n, vec.clear();
        for (i = 1; i <= n; ++i) h[i] = 0, vec.push_back(i), g[i].clear(); t = 0;
        for (i = 1; i < n; ++i) cin >> u >> v, add();
        que(), rot = u, L = v, dfs(rot, 0), MidSearch(), cin >> tmp;
    }
    return 0;
}

---

## 作者：tzl_Dedicatus545 (赞：0)

$f$ 是题目里的询问。。。

两眼丁真，先问 $f([n])$，得到 $u\to v$ 路径上的一个点以及 $dis(u,v)$。

知道了这个以后，我们不妨以这个点定做根，则 $u$ 与 $v$ 必定位于不同的子树。

我们按照 $dep_x$ 分层，每次我们问所有深度为 $d$ 的点，可以知道 $\max(dep_u,dep_v)$ 是否大于 $d$。

重要的技巧是：因为 $dep_u+dep_v$ 为定值 $k$，我们只需二分 $[1,\dfrac{k}{2}]$ 即可。

可以通过 F1、F2。

---

## 作者：under_the_time (赞：0)

## 题意

> *交互题。* 给你一棵 $n$ 个点的树，需要得出树上两个点 $X,Y$ 的位置。你可以向评测机询问一个点集，评测机会回答点集中与 $X,Y$ 距离和最小的点，以及这个距离和。询问不超过 $14$ 次。 

## 思路

询问次数不能超过 $11$ 次，这个数字与 $\log n$ 的值很接近。考虑先对所有 $n$ 个点进行询问，这样就可以得到 $X,Y$ 之间的距离，和一个必定在 $X,Y$ 路径上的点。设这个点为 $rt$，$X,Y$ 之间的距离为 $dis$。如果我们以 $rt$ 为树根，那么对于树中深度为 $dep$ 的点集 $\{A\}$，且 $dep$ 大于等于 $X,Y$ 中较小的深度，我们对其进行询问：

- 如果询问得到的距离和为 $dis$，则表示询问得到的点在 $X,Y$ 的路径上，即 $X,Y$ 中较大的深度大于等于 $dep$；
- 如果询问得到的距离和大于 $dis$，则表示该深度的点中没有在 $X,Y$ 的路径上的，即 $X,Y$ 中较大深度小于 $dep$。

对于第一种情况询问到的点都可能是 $X,Y$ 中深度较大的点，不妨令 $dep_X\ge dep_Y$。考虑二分，区间下界为 $\min(dis,Dep)$，其中 $Dep$ 为最大深度。每一轮都询问一次深度为 $mid$ 的点集，按照上述两种情况二分，最终可以得到深度较大的 $X$。然后我们以 $X$ 为树根，然后询问深度为 $dis$ 的点集，得到的点即为 $Y$。

## 实现

实现没什么难点，注意每次询问/回答都要 `fflush(stdout)`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
vector<int> mp[maxn << 1];
void addEdge(int u,int v) {
    mp[u].push_back(v);
}
vector<int> a[maxn]; int Dep;
void dfs(int u,int fa,int dep) {
    a[dep].push_back(u);
    Dep = max(Dep,dep);
    for (auto v : mp[u]) {
        if (v == fa) continue;
        dfs(v,u,dep + 1);
    }
}
pair<int,int> Query(const vector<int> &ask) {
    printf("? %d",ask.size());
    for (auto x : ask) printf(" %d",x);
    puts(""); 
    fflush(stdout);
    int x,d;
    scanf("%d %d",&x,&d);
    return make_pair(x,d);
}
pair<int,int> Solve(int n,const vector<pair<int,int> > &edge) {
    for (int i = 1;i <= n;i ++)
        mp[i].clear();
    for (int i = 0;i <= Dep;i ++) a[i].clear();
    Dep = 0;
    for (auto E : edge) {
        int u = E.first, v = E.second;
        addEdge(u,v); addEdge(v,u);
    }
    vector<int> ask;
    for (int i = 1;i <= n;i ++) ask.push_back(i);
    pair<int,int> res = Query(ask);
    int rt = res.first, sum = res.second;
    dfs(rt,0,0);
    int l = 0, r = Dep;
    int X = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        res = Query(a[mid]);
        if (res.second == sum) l = mid + 1, X = res.first;
        else r = mid - 1;
    }
    for (int i = 0;i <= Dep;i ++) a[i].clear();
    Dep = 0; dfs(X,0,0);
    return make_pair(X, Query(a[sum]).first);
}
int T,n; char AC_or_WA[maxn];
vector<pair<int,int> > Edge;
int main() {
    scanf("%d",&T);
    while (T --) {
        scanf("%d",&n);
        Edge.clear();
        for (int i = 1,u,v;i < n;i ++) {
            scanf("%d%d",&u,&v);
            Edge.emplace_back(u,v);
        }
        pair<int,int> ans = Solve(n,Edge);
        printf("! %d %d\n",ans.first,ans.second);
        fflush(stdout);
        scanf("%s",AC_or_WA + 1);
    }
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

唐人做唐题。考虑 $\text{query}(\{1,2,3,\dots,n\})$，得到了两个关键点之间的距离和他们路径上的某一个节点 $u$。

以 $u$ 为根，两个关键点 $c$ 和 $d$ 在两个不同的子树内。

考虑到 $c$ 和 $d$ 之间的路径和一个水平面（深度相同的点）只有一个交点，那么就可以通过二分得到较深的那一个点，设为 $c$。

再以 $c$ 为根，按照 $c$ 和 $d$ 之间的距离画一个水平面，与路径也只有一个交点，为 $d$。

这样需要 $2+ \log(n)$ 次询问。

注意到我们是找到较深点，所以它所在的可能深度范围小于等于 $\dfrac{n}{2}$，审掉了一次询问。

可以通过 $\rm Easy \ version$ 和 $\rm Hard \ version$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10;
int n,T,dis[MAXN],dep[MAXN];
vector<int> G[MAXN];
pair<int,int> query(vector<int> vc) {
	if(vc.empty()) return {0,0};	
	cout<<"? "<<vc.size()<<' ';for(auto id:vc) cout<<id<<' ';cout<<endl;
	int x,d; cin>>x>>d;
	return {x,d};
}
void dfs(int u,int f,int *dis) {
	dis[u]=dis[f]+1;
	for(auto v:G[u]) if(v!=f) dfs(v,u,dis);
	return ;	
}
vector<int> gen(int deep) {
	vector<int> ans;
	ffor(i,1,n) if(dep[i]==deep) ans.push_back(i);
	return ans;	
}
int main() {
	cin>>T;
	while(T--) {
		cin>>n; ffor(i,1,n) G[i].clear();
		ffor(i,1,n-1) {int u,v; cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
		vector<int> vc; ffor(i,1,n) vc.push_back(i);
		auto pr=query(vc); int len=pr.second,rt=pr.first;
		dfs(rt,0,dep);
		int L=(len+1)/2,R=len,ans=0;
		while(L<=R) {
			int mid=L+R>>1;
			auto pr=query(gen(mid+1));
			if(pr.second==len) ans=pr.first,L=mid+1;
			else R=mid-1;	
		}
		dfs(ans,0,dep);
		int ot=query(gen(len+1)).first;
		cout<<"! "<<ans<<' '<<ot<<endl;
		string result; cin>>result;
	}
	return 0;
}
```

---

## 作者：N1K_J (赞：0)

写这道题的时候旁边打音游的不停肘我，RMJ 似了几次，真的难蚌。

约定标记点为 $p,q$，点 $x,y$ 之间的距离为 $dis(x,y)$，点 $x,y$ 之间的路径为 $Path_{x,y}$。

首先，考虑询问一次所有的点，这时结果 $(x_0,d_0)$ 必定满足 $x_0$ 在 $Path_{p,q}$ 上，$d_0=dis(p,q)$。

考虑以 $x_0$ 为根，考虑此时 $p,q$ 中深度较深的点。

我们考虑二分这个深度，每次将所有二分到的深度 $M$ 上所有点询问一次，设答案为 $x_M,d_M$。若 $d_M = d_0$，那么这相当于这些点中存在 $Path_{p,q}$ 上的点，也就是 $p,q$ 中较深点深度不低于 $M$，否则，说明较深点深度小于 $M$。

应当注意到，最后一次询问会得到较深点的位置（除非两个点深度相同，但是这是不会影响后面的过程的）。

接下来，以这个较深点为根，显然我们可以计算出另一点的深度，直接对该深度的所有点做一次询问就好了。

注意到这会最多有 $1+\log_2{1024}+1=12$ 次询问，只能通过 easy version。

不过由于较深点的深度肯定不小于 $\dfrac{d_0}{2}$，所以我们将二分时左端点设为 $\dfrac{d_0}{2}$ 节省 $1$ 次询问就能通过本题的 hard version。

[Code](codeforces.com/contest/1370/submission/255481610)

---

