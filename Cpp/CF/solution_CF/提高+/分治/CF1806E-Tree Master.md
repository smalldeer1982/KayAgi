# Tree Master

## 题目描述

You are given a tree with $ n $ weighted vertices labeled from $ 1 $ to $ n $ rooted at vertex $ 1 $ . The parent of vertex $ i $ is $ p_i $ and the weight of vertex $ i $ is $ a_i $ . For convenience, define $ p_1=0 $ .

For two vertices $ x $ and $ y $ of the same depth $ ^\dagger $ , define $ f(x,y) $ as follows:

- Initialize $ \mathrm{ans}=0 $ .
- While both $ x $ and $ y $ are not $ 0 $ : 
  - $ \mathrm{ans}\leftarrow \mathrm{ans}+a_x\cdot a_y $ ;
  - $ x\leftarrow p_x $ ;
  - $ y\leftarrow p_y $ .
- $ f(x,y) $ is the value of $ \mathrm{ans} $ .

You will process $ q $ queries. In the $ i $ -th query, you are given two integers $ x_i $ and $ y_i $ and you need to calculate $ f(x_i,y_i) $ .

 $ ^\dagger $ The depth of vertex $ v $ is the number of edges on the unique simple path from the root of the tree to vertex $ v $ .

## 说明/提示

Consider the first example:

In the first query, the answer is $ a_4\cdot a_5+a_3\cdot a_3+a_2\cdot a_2+a_1\cdot a_1=3+4+25+1=33 $ .

In the second query, the answer is $ a_6\cdot a_6+a_2\cdot a_2+a_1\cdot a_1=1+25+1=27 $ .

## 样例 #1

### 输入

```
6 2
1 5 2 3 1 1
1 2 3 3 2
4 5
6 6```

### 输出

```
33
27```

## 样例 #2

### 输入

```
14 8
3 2 5 3 1 4 2 2 2 5 5 5 2 4
1 2 3 1 1 4 7 3 3 1 5 3 8
4 4
4 10
13 10
3 12
13 9
3 12
9 10
11 5```

### 输出

```
47
53
48
36
42
36
48
14```

# 题解

## 作者：zifanwang (赞：29)

直接记忆化搜索即可。

复杂度分析：

下面的被调用是指搜索函数被调用。

* 对于节点数 $\le\sqrt n$ 的层，我们假设每一层有 $x$ 个节点，那么最坏情况下会被调用 $x\choose 2$ 次，是 $x^2$ 级别的。因为最多有 $\frac{n}{x}$ 个这样的层，所以总共被调用的次数是 $\frac{n}{x}\times x^2=nx$ ，因为 $x\le\sqrt n$，一次调用的时间复杂度是 $O(1)$，所以总时间复杂度是 $O(n\sqrt n)$

* 对于节点数 $>\sqrt n$ 的层，这样的层小于 $\sqrt n$ 个，每一层最多被调用 $q$ 次，所以总共被调用的次数是 $q\sqrt n$，时间复杂度 $O(q\sqrt n)$

综上，总时间复杂度为 $O(n\sqrt n+q\sqrt n)$，可以通过此题。

一些注意事项：

对于节点数 $>\sqrt n$ 的层不用记搜反而会更优，因为 `unordered_map` 的常数巨大，上面分析这一部分的时间复杂度时也跟记搜没有关系，时间复杂度仍然正确。

对于节点数 $\le\sqrt n$ 的层，直接用数组存储而不用 `unordered_map`，`unordered_map` 常数巨大。

代码（有优化）：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 100003
#define md 1000000007
#define pb push_back
#define mkp make_pair
#define ld long double
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int n,q,a[mxn],d[mxn],c[mxn],p[mxn],fa[mxn];
ll f[mxn][500];
ll s[mxn];
ll dfs(int x,int y){
	if(x==y)return s[x];
	if(c[d[x]]<500){
		if(f[x][p[y]])return f[x][p[y]];
		return f[x][p[y]]=dfs(fa[x],fa[y])+(ll)a[x]*a[y];
	}else return dfs(fa[x],fa[y])+(ll)a[x]*a[y];
}
signed main(){
	scanf("%d%d",&n,&q);
	rep(i,1,n)scanf("%d",&a[i]);
	rep(i,2,n)scanf("%d",&fa[i]);
	rep(i,1,n){
		s[i]=s[fa[i]]+(ll)a[i]*a[i];
		d[i]=d[fa[i]]+1;
		p[i]=++c[d[i]];
	}
	int x,y;
	while(q--){
		scanf("%d%d",&x,&y);
		printf("%lld\n",dfs(x,y));
	}
	return 0;
}
```

---

## 作者：Mikefeng (赞：16)

## 题意

给定一棵树，点有点权，每次查询时给出两个同深度的点，要你求出这两个点到根的路径上深度相同的点的点权之积的和。

$n,q\le 10^5$

## 做法

提供一个树分块的解法，比 $mashduihca$ 的大常数正解跑得快。

考虑在树上随机撒 $\sqrt n$ 个关键点，每个点向上调到关键点的期望步数是 $O(\sqrt n)$ 的，当然你也可以根据自己喜好选择合适的树分块方法，比如按到叶子的距离分块。

查询前可以预处理出关键点与同深度节点之间的答案，时间复杂度 $O(n\sqrt n)$。

查询时可以暴力跳，期望每次跳 $O(\sqrt n)$ 步，时间复杂度 $O(n\sqrt n)$，总时间复杂度 $O(n\sqrt n)$。

## 代码

```cpp
int n,m,len;
int a[N],id[N];
bool vis[N];
vector<int> e[N],tmp;
int fa[N],dep[N];
inline void dfs(int u,int fath){
	fa[u]=fath;
	dep[u]=dep[fath]+1;
	for(int v:e[u]) dfs(v,u);
}
vector<int> b;
inline void init(int x){
	b.clear();
	while(x){
		b.emplace_back(a[x]);
		x=fa[x];
	}
	reverse(b.begin(),b.end());
}
ll val[N][B];
inline void pre_solve(int u,int pos){
	if(dep[u]>dep[pos]) return;
	val[u][id[pos]]=val[fa[u]][id[pos]]+1ll*a[u]*b[dep[u]-1];
	for(int v:e[u]) pre_solve(v,pos);
}
inline ll query(int x,int y){
	ll ans=0;
	while(!vis[x]&&!vis[y]){
		ans+=1ll*a[x]*a[y];
		x=fa[x];y=fa[y];
	}
	if(vis[x]) ans+=val[y][id[x]];
	else ans+=val[x][id[y]];
	return ans;
}
int main(){
	ios::sync_with_stdio(0);
	cout.tie(0);
	n=read();m=read();
	len=400;
	vis[1]=1;
	tmp.emplace_back(1);
	F(i,2,min(len,n)){
		int x=rd()%n+1;
		while(vis[x]) x=rd()%n+1;
		vis[x]=1;
		tmp.emplace_back(x);
	}
	F(i,1,n) a[i]=read();
	F(i,2,n) e[read()].emplace_back(i);
	dfs(1,0);
	F(i,0,(int)tmp.size()-1){
		id[tmp[i]]=i+1;
		init(tmp[i]);
		pre_solve(1,tmp[i]);
	}
	F(i,1,m){
		int x=read(),y=read();
		cout<<query(x,y)<<'\n';
	}
	return 0;
}
```


---

## 作者：_cyle_King (赞：5)

提供一个比较好想的**离线**做法。赛场上调出来时比赛已经结束了 4 分钟没来得及交（B 题降智卡了一个小时，好在 C 题只用了 20 分钟，不然连见到 E 的机会都没有）。

## 题意
给定一棵以 $1$ 为根的 $n$ 个结点有根树，第 $i$ 个点祖先为 $p_i$，每一个结点有点权 $val$。有 $q$ 次询问，每次询问给定树上两个深度相同的结点 $x,y$，设其深度为 $t$，设 $a,b$ 分别是 $1$ 到 $x,y$ 路径上经过的结点按照先后顺序组成的序列，求 $\sum\limits_{i=1}^tval_{a_i}\times val_{b_i}$。
### 数据范围
$1\leq n\leq 2\times10^5,1\leq q\leq 10^5,1\leq val_i\leq 2\times 10^5,1\leq p_i< i$
## 分析
考虑询问 $x,y$，设 $l=\operatorname{lca}(x,y)$，路径上 $1\to l$ 的一段的贡献就是路径上点权的平方和，可以预处理，我们只需要求出 $x\to y$ 的简单路径去掉 $l$ 的贡献即可。

直接用树上的数据结构维护似乎不可做，考虑将树拍扁到序列上。将树用类似括号序列的方式拍扁，在 dfs 入栈和出栈时都将当前结点加入序列中（其实就是欧拉序），设结点 $i$ 出栈和入栈时对应序列下标分别为 $st_i,ed_i$。假定 $ed_x<st_y$，发现 $x\to y$ 路径上去掉 $l$ 的结点就是序列上 $[ed_x,st_y]
$ 上出现次数为 $1$ 的结点。

为了形象说明，这里给出一个例子，下图是 $n=8$ 时的一种情况

![图炸了](https://cdn.luogu.com.cn/upload/image_hosting/4uzfvs0g.png)

$\color{White}\text{\tiny{神 TM 对称。}}$

对应拍扁的序列 $d=[1,2,5,5,6,6,2,3,3,4,7,7,8,8,4,1]$。

询问 $x=6,y=7$，按照上述方法对应的连续子序列是 $d[6..11]=[6,2,3,3,4,7]$，发现结点 $6,2,4,7$ 只被经过一次，而这些结点再加上 $l(l=1)$ 就是路径 $x\to y$ 上的结点。

很好理解，同一个结点最多出现了两次，而当出现了两次时代表经过这个结点又出来了，自然不可能在路径 $x\to y$ 上，可以看成括号序列的匹配消除。

所以每次只用计算一段区间的贡献即可。线段树/平衡树/分块直接维护有些困难，但是使用莫队可以很简单地维护。具体的，设 $dep_i$ 为 $i$ 的深度，维护 $s_i$ 表示对于现在在维护的区间中所有满足 $dep_x=i$ 的有效的 $x$ 的总贡献，即 $\sum_{x<y}val_x\times val_y$，其中 $x,y$ 满足 $x,y$ 在当前维护的区间中出现次数为 $1$ 且 $dep_x=dep_y=i$。在加入一个数时判断这个数是否出现过来动态维护 $s$ 即可。

时间复杂度 $O(m\sqrt{n})$，注意细节，比如要考虑 $x=y$ 时的特判

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
template <class T1, class T2> inline bool cmax(T1 &a, T2 b) {return a < b ? a = b, 1 : 0;}
template <class T1, class T2> inline bool cmin(T1 &a, T2 b) {return b < a ? a = b, 1 : 0;}
typedef pair <int, int> pii;
typedef long long ll;
const int N = 4e5 + 10;
char buf[1 << 13 | 1], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 13, stdin), p1 == p2) ? EOF : *p1 ++)
template <class T> inline void read(T &x) {
  x = 0; char ch = getchar();
  for(; !isdigit(ch); ch = getchar());
  for(; isdigit(ch); ch = getchar()) x = x * 10 + (ch & 15);
}
template <class T, class ...Args> inline void read(T &x, Args &... args) {
  read(x), read(args ...);
}
int n, m, Sz, a[N], bel[N], eu[N], realeu[N], tt, pos[N], st[N], ed[N], t, dep[N]; struct Qry {int l, r, id;} q[N];
vector <int> e[N]; ll dis[N], ans[N], sum[N], res; bool cnt[N];
inline void dfs(int u) {
  st[u] = ++ t, eu[t] = u, realeu[++ tt] = u, pos[u] = tt;
  //到底哪个才是真正定义上的欧拉序我也不清楚，我能接触的资料中这两种说法都有。
  for(auto v : e[u]) {
    dis[v] = dis[u] + 1ll * a[v] * a[v], dep[v] = dep[u] + 1, dfs(v);
    realeu[++ tt] = u;
  }
  ed[u] = ++ t, eu[t] = u;
}
int lg[N], mn[N][19];
inline void _init() {
  lg[1] = 0; for(int i = 2; i <= tt; i ++) lg[i] = lg[i >> 1] + 1;
  for(int i = 1; i <= tt; i ++) mn[i][0] = realeu[i];
  for(int j = 1; j <= 18; j ++) for(int i = 1; i + (1 << j) - 1 <= tt; i ++) {
    int a = i, b = i + (1 << (j - 1));
    mn[i][j] = dep[mn[a][j - 1]] < dep[mn[b][j - 1]] ? mn[a][j - 1] : mn[b][j - 1];
  }
  while(1) cout << "Never gonna give you up. Never gonna let you down." << endl;
}
inline int lca(int x, int y) {//求 lca
  x = pos[x], y = pos[y];
  if(x > y) swap(x, y);
  int k = lg[y - x + 1], a = x, b = y - (1 << k) + 1;
  return dep[mn[a][k]] < dep[mn[b][k]] ? mn[a][k] : mn[b][k];
}
inline void add(int x) {
  if(cnt[x]) sum[dep[x]] -= a[x], res -= sum[dep[x]] * a[x];
  else res += sum[dep[x]] * a[x], sum[dep[x]] += a[x];
  cnt[x] ^= 1;
}
inline void del(int x) {
  if(cnt[x]) sum[dep[x]] -= a[x], res -= sum[dep[x]] * a[x];
  else res += sum[dep[x]] * a[x], sum[dep[x]] += a[x];
  cnt[x] ^= 1;
}
//没错， add 和 del 是一样的！
int main() {
#ifndef ONLINE_JUDGE
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#endif
  ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
  read(n, m); for(int i = 1; i <= n; i ++) read(a[i]);
  for(int i = 2; i <= n; i ++) {
    int fa; read(fa), e[fa].emplace_back(i);
  }
  dis[1] = 1ll * a[1] * a[1], dfs(1), _init();
  for(int i = 1; i <= m; i ++) {
    int x, y; read(x, y);
    q[i] = {ed[x], st[y], i};
    if(q[i].l > q[i].r) q[i].l = ed[y], q[i].r = st[x];
    if(x == y) q[i].l = st[x], q[i].r = ed[x];
    ans[i] = dis[lca(x, y)];
  }
  Sz = sqrtl(1ll * t * t / m);
  for(int i = 1; i <= t; i ++) bel[i] = (i - 1) / Sz + 1;
  sort(q + 1, q + m + 1, [&](const Qry &a, const Qry &b) {
    if(bel[a.l] != bel[b.l]) return bel[a.l] < bel[b.l];
    return bel[a.l] % 2 == 1 ? a.r < b.r : a.r > b.r;
  });
  int l = 1, r = 0;
  for(int i = 1; i <= m; i ++) {
    while(r < q[i].r) add(eu[++ r]);
    while(l > q[i].l) add(eu[-- l]);
    while(r > q[i].r) del(eu[r --]);
    while(l < q[i].l) del(eu[l ++]);
    ans[q[i].id] += res;
  }
  for(int i = 1; i <= m; i ++) cout << ans[i] << '\n';
  // cerr << ti << endl;
  return 0;
}
```

$\color{White}\text{\tiny{Never gonna give you up. Never gonna let you down.}}$

不要抄题解，你会后悔的。$\color{White}\text{\tiny{不信你试试，卡爆你。}}$

## 后话

好像这玩意儿叫树上莫队，但是我没学过不太清楚。


---

## 作者：LHQing (赞：5)

#### 思路分析

数据范围 $10^5$，时限 $3s$，考虑根号分治。

对于结点个数 $\lt \sqrt s$ 的深度，直接枚举该层点对，然后暴力计算，跳到深度较小的位置碰到之前算过的点对可以通过记忆化得到。最后记录这层上一个不满足条件的深度，即结点个数 $\ge \sqrt s$。

询问处理如下：其中若当前所在深度结点个数 $\ge \sqrt s$ 直接暴力跳父亲，否则通过上一个不满足条件的深度跳祖先。具体实现见代码。

#### 题解代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e5 + 10;

int n, q, s, ans, a[maxn], p[maxn], typ[maxn], grf[maxn], dep[maxn], scp[maxn];
vector<int> g[maxn], ndd[maxn];
vector<vector<int>> val[maxn];

void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1, ++scp[dep[u]], ndd[dep[u]].push_back(u);
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v != fa) dfs1(v, u);
    }
}

signed main() {
    cin >> n >> q;
    s = sqrt(n) + 0.5;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) cin >> p[i], g[p[i]].push_back(i), g[i].push_back(p[i]);
    dfs1(1, 0);
    val[0].resize(n);
    for (int i = 0; i < n; i++) val[0][i].resize(1);
    for (int i = 1; i <= n; i++) {
        if (scp[i] == 0) break;
        if (scp[i] < s) {
            val[i].resize(scp[i]);
            for (int j = 0; j < scp[i]; j++) val[i][j].resize(scp[i]), typ[ndd[i][j]] = j;
            for (int x = 0; x < ndd[i].size(); x++) {
                for (int y = 0; y < ndd[i].size(); y++) {
                    int u = ndd[i][x], v = ndd[i][y];
                    val[i][typ[u]][typ[v]] = a[u] * a[v];
                    if (ndd[i - 1].size() < s) val[i][typ[u]][typ[v]] += val[i - 1][typ[p[u]]][typ[p[v]]];
                }
            }
            for (int x = 0; x < ndd[i].size(); x++) {
                int u = ndd[i][x];
                grf[u] = grf[p[u]];
            }
        } else {
            for (int x = 0; x < ndd[i].size(); x++) {
                int u = ndd[i][x];
                grf[u] = u;
            }
        }
    }
    while (q--) {
        int u, v, d;
        cin >> u >> v;
        d = dep[u];
        ans = 0;
        while (u != 0) {
            if (grf[u] != u) ans += val[dep[u]][typ[u]][typ[v]], u = grf[u], v = grf[v];
            ans += a[u] * a[v];
            u = p[u], v = p[v];
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：EnofTaiPeople (赞：5)

首先题目不需要支持修改，所以我们能够对信息进行预处理。

由于询问不能暴力跳，我们希望让它们能够“搭便车”，所以对于每一个深度，我们都**随机选取**两个节点作为**关键点对**，预处理往上跳 $O(\sqrt n)$ 步的答案。

然后就可以通过了，这个算法应当是卡不掉的，目测时间复杂度为期望 $O((n+q)\sqrt n)$，空间 $O(n)$，支持 $O(\sqrt n)$ 单点修改，因为每次修改最多会对 $O(\sqrt n)$ 个关键点对造成影响。

代码太好写了，几分钟就能写完，甚至不需要调试，可以一遍过。

很遗憾，这种做法并不能支持 Link-Cut 和链或子树修改。

看到别人的做法大多是莫队或记忆化，似乎莫队在线会变慢，记忆化不能修改？

不过我为什么赛时想不到记忆化啊！虽然也是 $O((n+q)\sqrt n)$ 的。

当然强制在线并且修改以上两种做法就不适用了吧。

[赛时 AC 记录](https://codeforc.es/contest/1806/submission/197943303)。

---

## 作者：Unnamed114514 (赞：4)

[题目传送门](https://codeforces.com/contest/1806/problem/E)

难度：\*2200

注意到这是个递归函数，所以说可以用 `dfs` 来实现，然后因为没有后效性，容易想到记忆化：

设 $dp_{x,y}$ 表示 $f(x,y)$ 的答案，但是这是个二元组，所以用 `map/unordered_map` 存储，此时会 TLE on #10。

容易想到一个优化：当深度比较小时，直接向上搜是不会超时的，甚至会减小记忆化的时间。加上这个优化后，运行效率大大提高，但是，很遗憾，`unordered_map` 包括 `gp_hash_table` 都会 MLE on #70，`map` 会 TLE on #70：

从头开始，回到 dp。此时我们必须得考虑时空复杂度均 $O(1)$ 的直接得到 dp 值，并且不能常数太大，显然 STL 是不行的，所以考虑数组存储。

但是，直接开数组是存不下的，所以我们减少状态的定义。考虑到 $dep_x=dep_y$，那么我们在 $dp_{x,y}$ 的时候其实我们从第一维 $x$ 就已经知道深度了。那么我们可以把 $y$ 映射到同一深度上的一个点 $f_y$ 表示 $y$ 是在 $dep_y$ 中的第几个元素，这样，我们就把 $dp_{x,y}$ 转化为 $dp_{x,dep_y}$ 了。

此时我们仍然无法直接调用数组：假如说这个树是一个菊花图，那么此时 dp 数组的消耗仍然是 $O(n^2)$ 的。

此时我们采用第二个优化：增加暴搜数量。类似于上方关于 `dfs` 中 `dep` 的判断，我们仍然要压缩状态。对于 dp：第一维 $x$ 带来了是当前查询的层数，第二位 $y$ 和层数的数量有关。那么我们只有得到 $x$，才能推出 $y$，所以说 $x$ 这一维是必不可少的，所以考虑在 $y$ 这里动手脚。

首先，我们肯定不能存储所有的状态，但是我们可以考虑一个阈值 $B$，当 $cnt_{dep_y}$ 即当前深度的节点数小于等于 $B$ 时，我们可以进行记忆化，那么空间复杂度就是 $O(nB)$。

对于时间复杂度：dp 状态数为 $O(nB)$，所以 dp 的复杂度就是 $O(nB)$。接下来我们考虑其它的层数，容易发现：此时这样的层其实最多就只有 $\dfrac{n}{B}$ 层，每层中间进行暴力匹配，一共只有 $O(B^2)$ 种查询，但是大于 $B$ 的时候，$B^2$ 是有可能超越 $q$ 的，$n,q$ 同阶，所以本质上只有 $n$ 种查询。一共 $\dfrac{n}{B}$ 层，每层 $O(n)$，时间复杂度就是 $O(\dfrac{n}{B}\times n)=O(\dfrac{n^2}{B})$。 

均摊复杂度，取 $B=\sqrt{n}$，时空复杂度 $O(n\sqrt{n})$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5,B=400;
int n,q,x,y,a[maxn],p[maxn],cnt[maxn],dep[maxn],mp[maxn],dp[maxn][B];
vector<int> G[maxn];
void dfs(int u,int d){
	mp[u]=++cnt[d],dep[u]=d;
	for(auto v:G[u])
		dfs(v,d+1);
}
int f(int x,int y){
	if(!x&&!y)
		return 0;
	if(cnt[dep[y]]<=B&&dp[x][mp[y]])
		return dp[x][mp[y]];
	int res=f(p[x],p[y])+1ll*a[x]*a[y];
	if(cnt[dep[y]]<=B)
		dp[x][mp[y]]=res;
	return res;
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	for(int i=2;i<=n;++i){
		scanf("%lld",&p[i]);
		G[p[i]].push_back(i);
	}
	dfs(1,0);
	while(q--){
		scanf("%lld%lld",&x,&y);
		printf("%lld\n",f(x,y));
	}
	return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：2)

一个常数很小的根号分治做法。

令 $B=\sqrt{n}$，定义 $cnt_i$ 表示深度为 $i$ 的节点个数，并令 $cnt_i\ge B$ 的层为关键层（不难发现只有 $\sqrt{n}$ 层）。

首先，对于所有非关键层 $i$ 预处理出第 $i$ 层的点两两之间的点权乘积，设点 $i,j$ 之间的乘积为 $c_{j,k}$，关键层的点之间 $c_{j,k}=0$（这一部分不需要开数组记录，没有空间开销）。并且对于所有的非关键层，$c_{j,k}\leftarrow c_{j,k}+c_{fa_j,fa_k}$。这一部分的复杂度为 $\sum\limits_{cnt_i\le B}\binom{cnt_i}{2}\le n\sqrt{n}$，即上限为 $\mathcal{O}(n\sqrt{n})$。

之后考虑处理询问，利用类似倍增的思路，每次跳到最近的关键层，路径上的答案已经预处理好了，再爆算关键层的答案，由于关键层数量最多只有 $\sqrt{n}$ 层，所以这部分复杂度上限为 $\mathcal{O}(m\sqrt{n})$。

两部分结合起来，复杂度上限为 $\mathcal{O}((n+m)\sqrt{n})$，实际上根本跑步满，常数也很小。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace Wilson_Inversion {
void gi(int &x) {
	x = 0;
	int y = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') y = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + (c & 15);
		c = getchar();
	}
	x *= y;
}
int n, q, kc, a[100010], fa[100010], bh[100010], dep[100010], ffa[100010], mx;
vector<vector<int> > sum[100010];
vector<int> e[100010], c[100010];
bool mark[100010];
void dfs(int x) {
	c[dep[x]].push_back(x);
	mx = max(mx, dep[x]);
	for (int i : e[x]) {
		dep[i] = dep[x] + 1;
		dfs(i);
	}
}
void main() {
	gi(n), gi(q);
	kc = sqrt(n);
	for (int i = 1; i <= n; ++i) {
		gi(a[i]);
	}
	for (int i = 2; i <= n; ++i) gi(fa[i]), e[fa[i]].push_back(i);
	dep[1] = 1;
	sum[0].resize(1);
	sum[0][0].resize(1);
	sum[0][0][0] = 0;
	dfs(1);
	for (int i = 1; i <= mx; ++i) {
		if (c[i].size() < kc) {
			for (int j = 0; j < c[i].size(); ++j) bh[c[i][j]] = j;
			sum[i].resize(c[i].size());
			int sz = c[i].size();
			for (int j = 0; j < c[i].size(); ++j) sum[i][j].resize(c[i].size());
			for (auto j : c[i]) {
				for (auto k : c[i]) {
					sum[i][bh[j]][bh[k]] = a[j] * a[k];
					if (c[i - 1].size() < kc)
						sum[i][bh[j]][bh[k]] += sum[i - 1][bh[fa[j]]][bh[fa[k]]];
				}
			}
			for (auto j : c[i]) ffa[j] = ffa[fa[j]];
		} else {
			for (auto j : c[i]) ffa[j] = j;
		}
	}
	while (q--) {
		int x, y;
		gi(x), gi(y);
		int ans = 0;
		while (x) {
			if (ffa[x] != x) ans += sum[dep[x]][bh[x]][bh[y]], x = ffa[x], y = ffa[y];
			ans += a[x] * a[y], x = fa[x], y = fa[y];
		}
		printf("%lld\n", ans);
	}
}
}
#undef int
int main() {
	Wilson_Inversion::main();
	return 0;
}
```

---

## 作者：NATURAL6 (赞：2)

## 题意

给定一颗以 $1$ 为根的树，每个节点有一个权值，每次询问给出两个深度相同的点，求他们到根的这条路径上所有深度相同的点权值的积的和。

## Sol

容易发现这就相当于他们到最近公共祖先前的这条路径上所有深度相同的点权值的积的和，加上最近公共祖先到根的路径上所有点权值的平方和。

于是可以预处理每个点到根路径上所有点的权值和，

剩下的部分可以看到就是跑括号序树上莫队时所选中的点集，

即 $u$ 到最近公共祖先路径上点加上 $v$ 到最近公共祖先路径上点除去最近公共祖先的点集。

于是考虑树上莫队，要求能维护所有深度相同点的乘积的和。

考虑对于每个深度记录其总和，

加入一个该深度点时将该点乘上总和后加入答案，

删除一个点时将总和减去其权值再乘上其权值从答案中减掉。

这样就完成了，时间复杂度 $O(n\sqrt{m})$，空间复杂度 $O(n)$。

代码中实现为倍增求最近公共祖先，所以空间为 $O(n\log n)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int qread()
{
	int a=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){(a*=10)+=(ch^48);ch=getchar();}
	return a*f;
}
int n,m,cx,a[100010],qs,l=1,r,vis[100010];
long long val[100010],ans[100010],dep[100010],an;
int cl,c[200010];
int tot,head[100010],fa[20][100010],de[100010];
int dfn[200010],cnt,L[100010],R[100010];
struct node
{
	int l,r,id;
}q[100010];
inline bool cmp(node x,node y){return c[x.l]==c[y.l]?(c[x.l]&1?x.r<y.r:x.r>y.r):x.l<y.l;}
struct qxx
{
	int nex,t;
}e[200010];
inline void adde(int x,int y)
{
	e[++tot].t=y;
	e[tot].nex=head[x];
	head[x]=tot;
	return ;
}
inline void dfs(int rt,int da)
{
	dep[rt]=dep[da]+1;
	fa[0][rt]=da;
	for(int i=1;i<=17;++i)fa[i][rt]=fa[i-1][fa[i-1][rt]];
	dfn[++cnt]=rt;L[rt]=cnt;
	val[rt]=val[da]+1ll*a[rt]*a[rt];
	for(int i=head[rt];i;i=e[i].nex)
	{
		if(e[i].t==da)continue;
		dfs(e[i].t,rt);
	}
	dfn[++cnt]=rt;
	R[rt]=cnt;
	return ;
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i=17;~i;--i)while(dep[fa[i][x]]>=dep[y])x=fa[i][x];
	if(x==y)return x;
	for(int i=17;~i;--i)while(fa[i][x]!=fa[i][y])x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
inline void U(int x)
{
	an+=1ll*a[x]*de[dep[x]];
	de[dep[x]]+=a[x];
	return ;
}
inline void M(int x)
{
	an-=1ll*a[x]*(de[dep[x]]-a[x]);
	de[dep[x]]-=a[x];
	return ;
}
inline void F(int x)
{
	cx=dfn[x];
	if(!vis[cx])U(cx);
	else M(cx);
	vis[cx]^=1;
	return ;
}
signed main()
{
	n=qread();
	m=qread();
	for(int i=1;i<=n;++i)a[i]=qread();
	for(int i=2,p;i<=n;++i)
	{
		p=qread();
		adde(i,p);
		adde(p,i); 
	}
	dfs(1,0);
	for(int i=1,x,y;i<=m;++i)
	{
		x=qread();
		y=qread();
		if(x==y)
		{
			ans[i]=val[x];
			continue;
		}
		q[++qs].id=i;
		q[qs].l=R[x];
		q[qs].r=L[y];
		if(q[qs].l>q[qs].r)
		{
			q[qs].l=R[y];
			q[qs].r=L[x];
		}
		ans[i]=val[LCA(x,y)];
	}
	cl=n*2/(sqrt(qs)+1); 
	for(int i=1;i<=cnt;++i)c[i]=(i-1)/cl+1;
	sort(q+1,q+1+qs,cmp);
	for(int i=1;i<=qs;++i)
	{
		while(r<q[i].r)F(++r);
		while(l>q[i].l)F(--l);
		while(r>q[i].r)F(r--);
		while(l<q[i].l)F(l++);
		ans[q[i].id]+=an;
	}
	for(int i=1;i<=m;++i)printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：XKJie (赞：2)

考虑根号分治。

约定：$dep_i$ 为 $i$ 的深度，$cnt_i$ 为深度为 $i$ 的节点个数，$B=\sqrt n$。

- 对于 $cnt_i$ 大于 $B$ 的询问，我们可以直接暴力处理。
- 对于 $cnt_i$ 小于 $B$ 的询问，我们则可以在暴力的基础之上加入一个记忆化的数组记录其中递归到的任意一层的结果。

那么这样为什么复杂度是对的呢？

- 对于时间复杂度

  节点个数大于 $B$ 的层数最多只有 $\frac{B}{n}$ 即 $\sqrt n$ 层，所以这一部分的时间复杂度为 $O(q\sqrt n)$。

  对于在小于 $B$ 的深度层中的节点询问，由于我们进行了记忆化搜索，所以对于每个点对的询问只会访问到一次。点对数为 $\Sigma_{cnt_i<B}C_{cnt_i}^2$，即为 $O(n\sqrt n)$ 数量级的。

- 对于空间复杂度 

  由于我们没有记忆 $cnt_i$ 大于 $B$ 的询问，因此空间复杂度是 $O(n\sqrt n)$ 的。

注意不要使用 unordered_map，虽然看上去是 $O(1)$ 但是常数巨大，用了的话似乎会在第 24 个点就 TLE。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define N 100010
#define MP make_pair
#define eb emplace_back
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
int n,q,B;
int a[N],f[N],dep[N],cnt[N];
ll dis[N][400],vis[N];
ll get_ans(int x,int y)
{
    ll ans=0;
    if (f[x]!=0 && f[y]!=0)
    {
        if (cnt[dep[f[y]]]<B && dis[f[x]][vis[f[y]]])
            ans=dis[f[x]][vis[f[y]]];
        else ans=get_ans(f[x],f[y]);
    }
    ans+=1ll*a[x]*a[y];
    if (cnt[dep[x]]<B)
    {
        dis[x][vis[y]]=ans;
        dis[y][vis[x]]=ans;
    }
    return ans;
}
int main()
{
    scanf("%d %d",&n,&q);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for (int i=2;i<=n;i++)
    {
        scanf("%d",&f[i]);
        dep[i]=dep[f[i]]+1;
        cnt[dep[i]]++;
        vis[i]=cnt[dep[i]];
    }
    B=(int)sqrt(N);
    for (int i=1;i<=q;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        printf("%lld\n", get_ans(x,y));
    }
    return 0;
}
```





---

## 作者：L0vely_NaiL0ng (赞：1)

除了记忆化搜索或者随机撒点，还可以树上莫队，但是别的莫队题解都要分讨，很复杂，事实上维护一个数组记录当前每个深度的点权之积即可。

如果加点之后当前深度的有恰好两个点，就加入答案，如果删除之后只有一个点，就把删除之前的答案去掉。记得把最近公共祖先到根的贡献加上即可。

正确性比较好理解：拍扁之后的序列如果出现了两次，要么不会对答案影响，要么第一次加入贡献，第二次去掉了相同的贡献。

可能有点讲不明白，但你看代码之后就会发现就是个莫队板子，改一下两个核心函数就可以了，赛时拉个板子写很快的：

```
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m, len, st[N], ed[N], num, id[N], pos[N];
int fa[N], siz[N], d[N], son[N], top[N];
int head[N], ver[N], nex[N], tot;
long long ans[N], cnt[N], res, a[N], sum[N], v[N];
bool flag[N];
void add(int x, int y) {
	ver[++tot] = y; nex[tot] = head[x]; head[x] = tot;
}
struct node {
	int l, r, id, z, LCA;
} q[N];
bool cmp(node i, node j) {
	if (pos[i.l] == pos[j.l]) {
		if (pos[i.l] & 1) return i.r < j.r;
		return i.r > j.r;
	}
	return i.l < j.l;
}
void dfs1(int x) {
	d[x] = d[fa[x]] + 1; siz[x] = 1;
	st[x] = ++num; id[num] = x; sum[x] = sum[fa[x]] + a[x] * a[x];
	for (int i = head[x]; i; i = nex[i]) {
		int y = ver[i];
		if (y == fa[x]) continue;
		fa[y] = x; dfs1(y);
		siz[x] += siz[y];
		if (siz[y] > siz[son[x]]) son[x] = y;
	}
	ed[x] = ++num; id[num] = x;
}
void dfs2(int x, int f) {
	top[x] = f;
	if (son[x]) dfs2(son[x], f);
	for (int i = head[x]; i; i = nex[i]) {
		int y = ver[i];
		if (y == fa[x] || y == son[x]) continue;
		dfs2(y, y);
	}
}
int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (d[top[x]] < d[top[y]]) swap(x, y);
		x = fa[top[x]]; 
	}
	if (d[x] > d[y]) swap(x, y);
	return x;
}
void add(int x) {
	cnt[d[x]]++;
	v[d[x]] *= a[x];
	if (cnt[d[x]] == 2) res += v[d[x]];
}
void del(int x) {
	cnt[d[x]]--;
	v[d[x]] /= a[x];
	if (cnt[d[x]] == 1) res -= v[d[x]] * a[x];
}
void work(int x) {
	if (!flag[x]) add(x);
	else del(x);
	flag[x] ^= 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	for (int i = 2; i <= n; i++) {
		int x; scanf("%d", &x);
		add(x, i);
	} 
	dfs1(1); dfs2(1, 1);
	len = sqrt(n);
	for (int i = 1; i <= 2 * n; i++) pos[i] = (i - 1) / len + 1;
	for (int i = 1; i <= m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		if (st[x] < st[y]) swap(x, y);
		q[i].id = i; q[i].z = q[i].LCA = lca(x, y);
		if (q[i].z == x) {
			q[i].l = st[x]; q[i].r = st[y]; q[i].z = 0;
		} else {
			q[i].l = ed[x]; q[i].r = st[y];
		}
	}
	for (int i = 1; i <= n; i++) v[i] = 1;
	sort(q + 1, q + m + 1, cmp);
	for (int i = 1, l = 1, r = 0; i <= m; i++) {
		while (l > q[i].l) work(id[--l]);
		while (r < q[i].r) work(id[++r]);
		while (l < q[i].l) work(id[l++]);
		while (r > q[i].r) work(id[r--]);
		if (q[i].z) work(q[i].z);
		ans[q[i].id] = res + sum[q[i].LCA];
		if (q[i].z) work(q[i].z);
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：Demeanor_Roy (赞：1)

- [摘自此](https://www.luogu.com.cn/blog/261213wrh/cf-r857-div2-ti-xie)。

------------

考虑暴力的同时记搜。不难发现这样做的复杂度即为本质不同点对数。

视 $n$ 和 $q$ 同级，若第 $i$ 层有 $a_i$ 个点，显然其对复杂度的贡献为 $\min({a_i}^2,n)$。于是总复杂度为 $\sum_{i=1}^{n}\min({a_i}^2,n)$，由于 $\sum a_i = n$，可用不等式推出复杂度最大值为 $n \sqrt n$。

于是可以暴力记搜做到大常数 $n \sqrt n$。

考虑优化掉哈希表，不难发现同一层只用记录 $\sqrt n$ 个点即可，于是可以用数组直接记录每一层前 $\sqrt n$ 个点，剩余暴力。此时复杂度小常数  $n \sqrt n$。


---

## 作者：zjrdmd (赞：1)

提供一个树上莫队做法。

考虑求出来原树的 DFS 序，那么我们可以把询问 $(x,y)$ 看做从 $1\sim x$，$1\sim y$ 两条 DFS 序路径上最后经过的深度为 $i$ 的点的乘积和。

于是我们以 $(x,y)$ 关键字跑莫队即可，转移到时候需要简单分讨，时间复杂度是一个根号。

---

## 作者：hbhz_zcy (赞：1)

![](https://cdn.luogu.com.cn/upload/image_hosting/kr1ivgqz.png "是故意的还是不小心的？CF：卡掉一切错误算法！")  

题意：给你一棵树，多组询问，每次询问从根节点出发到两个点 $u,v$ 的逐项乘积和，即 $\sum\limits_{i,j=root}^{u,v} a_i\cdot a_j$，数据 $1 \le N,Q \le 10^5,depth_u=depth_v$。  

考虑暴力做，发现每个询问都会有重复的部分。于是记忆化。  
为了方便分析复杂度，假设先使用了 $\Theta(N)$ 的复杂度记录下所有 $u=v$ 的答案，则所有询问只贡献不重合的部分。  
显然的，当树由 $\frac N K$ 条长 $K$ 的链组成的时候会达到复杂度上界。又因为对询问记忆化，所以复杂度为 $\min(Q,(\frac N K)^2) K$，上界为 $\Theta(N^{\frac 3 2})$。  

赛时使用的是暴力记忆化，即对于每个点对 `unordered_map` 或 `map` 记录下来，结果 TLE \#10。  
分析可得，当询问的深度比较小的时候暴力，可能会比使用记忆化快一些。于是出现了一大串的 TLE \#60~\#70。（可能有人常数比较小可以用这个过）  
于是我们考虑直接减小常数，用数组记录下每一个答案。对点按深度分层，每层的点编号。可以得出点数大于 $\sqrt N$ 的层不超过 $\sqrt N$ 个。因此可以使用 $f_{i,j}$ 表示点 $i$ 和同层编号 $j$ 的点的答案，而对于编号大于 $j$ 的，不进行记录。这样至多额外跳 $\sqrt N$ 层，但是常数极小。  

时空复杂度均为 $\Theta(\sqrt N)$。  

```cpp
//g++ d.cpp -o d -g -std=c++14 -O0 -Wall -fsanitize=undefined
#include<cstdio>
#include<vector>
#define LL long long
using namespace std;
namespace rdin{
	const int maxr=1e6+10;char buf[maxr],*l,*r;
	inline char gtc(){if(l==r){r=(l=buf)+fread(buf,1,maxr,stdin);}return l==r?EOF:*l++;}
	inline int qd(){int rt=0,ng=0;char c=gtc();while(c<'0'||c>'9'){ng^=c=='-',c=gtc();}while('0'<=c&&c<='9'){rt=(rt<<3)+(rt<<1)+(c^48),c=gtc();}return ng?-rt:rt;}
}
using rdin::qd;
const int maxn=1e5+10,maxsqn=256;
int N,Q,head[maxn],nume=0,a[maxn],fa[maxn],d[maxn],id[maxn],stop=0;LL f[maxn][maxsqn];
struct node{int to,nxt;}e[maxn<<1];
void edgen(int from,int to){e[++nume]={to,head[from]},head[from]=nume;}
vector<int>vec[maxn];
struct nodest{int x,y;}st[maxn];
void dfs(int u){
	id[u]=vec[d[u]=d[fa[u]]+1].size(),vec[d[u]].push_back(u);
	for(int i=head[u];i;i=e[i].nxt)  dfs(e[i].to);
}
int main(){
//	freopen("in.txt","r",stdin);
	N=qd(),Q=qd();
	for(int i=1;i<=N;i++)  a[i]=qd();
	for(int i=2;i<=N;i++)  edgen(fa[i]=qd(),i);
	dfs(1);f[1][0]=(LL)a[1]*a[1];
	for(int i=1;i<=Q;i++){
		int x=qd(),y=qd();if(id[x]>id[y])  swap(x,y);
		stop=0;while(id[y]>=maxsqn||!f[x][id[y]])  st[++stop]={x,y},x=fa[x],y=fa[y];
		LL ans=f[x][id[y]];
		for(;stop;stop--){
			x=st[stop].x,y=st[stop].y;ans+=(LL)a[x]*a[y];
			if(id[y]<maxsqn)  f[x][id[y]]=ans;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```  


---

## 作者：henrytb (赞：1)

本题的正解是记忆化搜索，通过根号分治证明复杂度正确，但是赛时没有想到。

于是考虑使用欧拉序“树上莫队”，考虑询问形如 $1 \to x, 1 \to y$ 这两条树上的链，且起点均为 $1$，那么可以写成询问 $(f_x, f_y)$（其中 $f_i$ 表示 $i$ 在欧拉序上第一次出现的位置）。考虑移动指针的时候如何 $O(1)$ 处理，考虑维护两个栈，表示第一条链的各深度点权和第二条链的各深度点权，再分别维护当前深度，即可计算答案的变化量。

时间复杂度 $O(n\sqrt{q})$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 1e5 + 5;
int n, q, a[N];
int target[N << 1], pre[N << 1], last[N], tot = 0;
void add(int u, int v) {
    target[++tot] = v;
    pre[tot] = last[u];
    last[u] = tot;
}
int bok1[N], bok2[N], dep1, dep2, res = 0;
int eul[N << 1], dfn_cl = 0, fi[N], la[N], typ[N << 1];
void dfs(int u, int fa) {
    eul[++dfn_cl] = u; fi[u] = dfn_cl; typ[dfn_cl] = 0;
    for (int ptr = last[u]; ptr; ptr = pre[ptr]) {
        int v = target[ptr];
        if (v != fa) {
            dfs(v, u);
        }
    }
    eul[++dfn_cl] = u; la[u] = dfn_cl; typ[dfn_cl] = 1;
}
struct queries {
    int l, r, id;
} Q[N];
int t = 0;
int ans[N];
signed main() {
    scanf("%lld%lld", &n, &q);
    rep(i, 1, n) scanf("%lld", &a[i]);
    rep(i, 2, n) {
        int x; scanf("%lld", &x);
        add(i, x); add(x, i);
    }
    dfs(1, 0);
    rep(i, 1, q) {
        int x, y;
        scanf("%lld%lld", &x, &y);
        Q[i].l = fi[x]; Q[i].r = fi[y];
        Q[i].id = i;
    }
    t = sqrt(q);
    sort(Q + 1, Q + q + 1, [] (const queries &a, const queries &b) {
        return a.l / t != b.l / t ? a.l < b.l : a.r < b.r;
    });
    int nl = 0, nr = 0;
    rep(i, 1, q) {
        int ql = Q[i].l, qr = Q[i].r;
        while (nr < qr) {
            ++nr;
            if (!typ[nr]) {
                bok2[++dep2] = a[eul[nr]];
                if (dep1 >= dep2) res += bok2[dep2] * bok1[dep2];
            } else {
                if (dep1 >= dep2) res -= bok2[dep2] * bok1[dep2];
                --dep2;
            }
        }
        while (nr > qr) {
            if (typ[nr]) {
                bok2[++dep2] = a[eul[nr]];
                if (dep1 >= dep2) res += bok2[dep2] * bok1[dep2];
            } else {
                if (dep1 >= dep2) res -= bok2[dep2] * bok1[dep2];
                --dep2;
            }
            --nr;
        }
        while (nl < ql) {
            ++nl;
            if (!typ[nl]) {
                bok1[++dep1] = a[eul[nl]];
                if (dep1 <= dep2) res += bok2[dep1] * bok1[dep1];
            } else {
                if (dep1 <= dep2) res -= bok2[dep1] * bok1[dep1];
                --dep1;
            }
        }
        while (nl > ql) {
            if (typ[nl]) {
                bok1[++dep1] = a[eul[nl]];
                if (dep1 <= dep2) res += bok2[dep1] * bok1[dep1];
            } else {
                if (dep1 <= dep2) res -= bok2[dep1] * bok1[dep1];
                --dep1;
            }
            --nl;
        }
        ans[Q[i].id] = res;
    }
    rep(i, 1, q) printf("%lld\n", ans[i]);
    return 0;
}
```

---

## 作者：bmatrix (赞：1)

[题面](https://www.luogu.com.cn/problem/CF1806E)

看起来是个 DS 题，事实上是个乱搞题，做法挺多的。由于它给的这个结构看起来就不好优化，所以考虑随机化。

由于两个点到达 LCA 后剩下的贡献就是 LCA 到根的每个点权值的平方，这部分可以 $O(n)$ 预处理，所以只需要考虑两个点之间的路径所产生的贡献。

在树上随机撒 $\sqrt n$ 个点，称这些点为关键点，那么两个关键点之间的期望距离应 $\sqrt n$。预处理任意两个关键点之间的贡献，时间复杂度 $O(n\sqrt n)$。

对于一个询问 $x,y$，从这两个点分别暴力向上跳，直到碰到关键点，然后用关键点间的贡献加上跳的时候计算的贡献即可。由于一个点到最近的关键点的期望距离为 $\sqrt n$，所以这部分时间复杂度 $O(q\sqrt n)$，总时间复杂度 $O((n+q)\sqrt n)$。实测常数略大，最大点用时约 2.6s。

代码：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define rep(i, s, e) for(int i = s, i##E = e; i <= i##E; ++i)
#define per(i, s, e) for(int i = s, i##E = e; i >= i##E; --i)
#define F first
#define S second
#define int ll
#define gmin(x, y) ((x > y) && (x = y))
#define gmax(x, y) ((x < y) && (x = y))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
constexpr int N = 1e5 + 5, B = 350;
int n, q, a[N], s[N], f[N], dep[N], id[N], st[B], dis[B][B];
vector<int> to[N];
mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
void dfs1(int p) {
    dep[p] = dep[f[p]] + 1;
    s[p] = a[p] * a[p] + s[f[p]];
    for(auto i : to[p]) dfs1(i);
}
signed main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    cin >> n >> q;
    rep(i, 1, n) cin >> a[i];
    rep(i, 2, n) {
        cin >> f[i];
        to[f[i]].push_back(i);
    }
    dfs1(1);
    uniform_int_distribution<> rnd(1, n);
    int num = sqrt(n);
    rep(i, 1, num) {
        int t = rnd(gen);
        st[i] = t;
        id[t] = i;
    }
    rep(i, 1, num) {
        dis[i][i] = s[i];
        rep(j, i + 1, num) {
            int u = st[i], v = st[j], res = 0;
            if(dep[u] < dep[v]) swap(u, v);
            while(dep[u] > dep[v]) u = f[u];
            while(u != v) {
                res += a[u] * a[v];
                u = f[u], v = f[v];
            }
            dis[i][j] = dis[j][i] = res + s[u];
        }
    }
    while(q--) {
        int u, v; cin >> u >> v;
        int fu = 0, fv = 0, res = 0;
        while((!fu || !fv) && u != v) {
            if(id[u]) fu = id[u];
            if(id[v]) fv = id[v];
            if(!fu || !fv) res += a[u] * a[v];
            u = f[u], v = f[v];
        }
        if(fu && fv) {
            cout << res + dis[fu][fv] << endl;
        }
        else cout << res + s[u] << endl;
    }
    return 0;
}
```

---

