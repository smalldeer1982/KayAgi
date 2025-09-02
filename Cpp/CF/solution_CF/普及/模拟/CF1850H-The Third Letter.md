# The Third Letter

## 题目描述

In order to win his toughest battle, Mircea came up with a great strategy for his army. He has $ n $ soldiers and decided to arrange them in a certain way in camps. Each soldier has to belong to exactly one camp, and there is one camp at each integer point on the $ x $ -axis (at points $ \cdots, -2, -1, 0, 1, 2, \cdots $ ).

The strategy consists of $ m $ conditions. Condition $ i $ tells that soldier $ a_i $ should belong to a camp that is situated $ d_i $ meters in front of the camp that person $ b_i $ belongs to. (If $ d_i < 0 $ , then $ a_i $ 's camp should be $ -d_i $ meters behind $ b_i $ 's camp.)

Now, Mircea wonders if there exists a partition of soldiers that respects the condition and he asks for your help! Answer "YES" if there is a partition of the $ n $ soldiers that satisfies all of the $ m $ conditions and "NO" otherwise.

Note that two different soldiers may be placed in the same camp.

## 说明/提示

For the first test case, we can partition the soldiers into camps in the following way: soldier:

- Soldier $ 1 $ in the camp with the coordinate $ x = 3 $ .
- Soldier $ 2 $ in the camp with the coordinate $ x = 5 $ .
- Soldier $ 3 $ in the camp with the coordinate $ x = 9 $ .
- Soldier $ 4 $ in the camp with the coordinate $ x = 11 $ .

For the second test case, there is no partition that can satisfy all the constraints at the same time.

For the third test case, there is no partition that satisfies all the constraints since we get contradictory information about the same pair.

For the fourth test case, in order to satisfy the only condition, a possible partition is:

- Soldier $ 1 $ in the camp with the coordinate $ x = 10 $ .
- Soldier $ 2 $ in the camp with the coordinate $ x = 13 $ .
- Soldier $ 3 $ in the camp with the coordinate $ x = -2023 $ .
- Soldier $ 4 $ in the camp with the coordinate $ x = -2023 $ .

## 样例 #1

### 输入

```
4
5 3
1 2 2
2 3 4
4 2 -6
6 5
1 2 2
2 3 4
4 2 -6
5 4 4
3 5 100
2 2
1 2 5
1 2 4
4 1
1 2 3```

### 输出

```
YES
NO
NO
YES```

# 题解

## 作者：buaa_czx (赞：10)

### 题目大意

有 $n$ 个军队部署在一条直线上，有 $m$ 个要求，每个要求为军队 $a$ 要在军队 $b$ 的前面 $d$ 格位置处，问是否能有一种放置方案满足所有要求。

### 题解

带权并查集模板题，用带权并查集维护每个点在它的祖先前面多少格即可，$i,j$ 两点间距离可用 ``dist[i]-dist[j]`` 表示。维护带权并查集的普遍方法：由于并查集在合并的时候只更改祖先，只需要先对祖先进行维护，集合里的其它点在路径压缩的时候可以通过递归完成维护。

### 代码

```cpp
int fa[maxN + 5], dist[maxN + 5];
int find(int x) {
    if (x == fa[x])
        return x;
    else {
        int fx = find(fa[x]);
        dist[x] += dist[fa[x]];
        fa[x] = fx;
        return fa[x];
    }
}
void join(int x, int y, int val) {
    int fx = find(x), fy = find(y);
    fa[fx] = fy;
    dist[fx] = val + dist[y] - dist[x];
}
void solve() {
    int n, m, ok = 1;
    cin >> n >> m;
    rep(i, 1, n) fa[i] = i, dist[i] = 0;
    rep(i, 0, m - 1) {
        int a, b, d;
        cin >> a >> b >> d;
        if (!ok)
            continue;
        if (find(a) != find(b)) {
            join(a, b, d);
        } else {
            if (dist[a] - dist[b] != d) {
                ok = 0;
                cerr << i << endl;
            }
        }
    }
    if (ok)
        cout << "YES\n";
    else
        cout << "NO\n";
}
```

---

## 作者：sto_5k_orz (赞：6)

# H

考虑 dfs。当一个点没有搜到时，给这个点赋点权，然后 dfs 一趟，求出能够求到的点权，如果算出来的点权与现有点权不同则无解，否则有解。

当然本题存在带权并查集、差分约束之类的其他做法，欢迎评论。

本人赛时写了半个小时的带权并查集，然后喜提五发罚时，换成 dfs 瞬间解决战斗。

注意的是 $a_i$ 到 $b_i$ 连的边权为 $d$，而 $b_i$ 到 $a_i$ 的边权为 $-d_i$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define I inline
#define gc getchar
#define W while
#define fi first
#define se second
namespace IO{
	I int read() {
		int x = 0, f = 1; char ch = gc();
		W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void Read(int &x) {x = read();}
	I void Read(int &x, int &y) {Read(x), Read(y);}
} using namespace IO;
const int N = 200010;
vector<pair<int, int> > e[N]; bool flag; int dis[N];
void dfs(int u, int now) {
	if(dis[u]) return ; dis[u] = now;
	for(auto it: e[u]) {
		if(flag) return ;
		int v = it.fi, w = it.se;
		if(!dis[v]) dfs(v, dis[u] + w);
		else {
			if(dis[v] != dis[u] + w) {
				cout << "NO\n";
				flag = 1;
				return ;
			}
		}
		if(flag) return ;
	}
}
signed main() {
    int t; Read(t);
    W(t--) {
    	int n, m; Read(n, m);
    	for(int i = 1; i <= n; i++) dis[i] = 0, e[i].clear();
    	W(m--) {
    		int a, b, d; cin >> a >> b >> d;
    		e[a].push_back(make_pair(b, d));
    		e[b].push_back(make_pair(a, -d));
		}
		flag = 0;
		for(int i = 1; i <= n; i++) {
			if(!dis[i]) dfs(i, 1e15);
			if(flag) break;
		}
		if(!flag) puts("YES");
    }
	return 0;
}

/*
1
3 2
1 2 1
3 2 1

*/
```

---

## 作者：封禁用户 (赞：3)

## 分析

~~有约束条件，判断有无解不就是差分约束模板吗~~

利用反证法的思想。

我们假设现在这些点的值是满足所有约束的。对于一个在之前没有遍历过的点 $i$，对其设一个值。然后把和 $i$ 有相互约束且未遍历的点都以这个值为基准进行计算，再对这些点进行拓展。可以证明，这个方法只会通过所有点的最多一个约束进行求值。而在有解的情况下，一旦某个点满足某个约束，则一定有其它约束也满足。

将这些值带进每一个约束条件，如果全部满足，假设成立，存在解；有一个不满足，假设不成立，不存在解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+10;
int t;
int n,m;
int ne[N],e[N],h[N],w[N],idx;
void add(int a,int b,int c){
	e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}
int where[N];
int a[N],b[N],c[N];
void dfs(int now){
	for(int i=h[now];~i;i=ne[i]){
		int j=e[i];
		if(!vis[j]){
			vis[j]=1;
			where[j]=where[now]+w[i];
			dfs(j);
		}
	}
}
void check(){
	memset(h,-1,sizeof(h));
	memset(vis,0,sizeof(vis));
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i]>>b[i]>>c[i];
		add(a[i],b[i],c[i]),add(b[i],a[i],-c[i]);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=1,where[i]=1e5;
			dfs(i);
		}
	}
	for(int i=1;i<=m;i++){
		if(where[a[i]]+c[i]!=where[b[i]]){
			cout<<"NO\n";
			return ;
		}
	}
	cout<<"YES\n";
}
signed main(){
	cin>>t;
	while(t--){
		check();
	}
	return 0;
}

```


---

## 作者：Leaper_lyc (赞：2)

### $\tt date:2023.07.25$
### $\tt upd:2023.07.26$
感谢 oyyfcy 指出错误。

------------
## 题目大意
有 $n$ 个士兵站队。要求士兵 $b$ 站在士兵 $a$ 的后 $d$ 格处（可以多个士兵站同一个位置）。问是否能满足要求。

## 分析
我们可以把 $m$ 个关系抽象成一张图，即 $a_i$ 向 $b_i$ 连一条长度为 $d_i$ 的边，$b_i$ 向 $a_i$ 连一条长度为 $-d_i$ 的边，类似的跑一遍 dfs，每次遍历到一个新的节点时就更新该节点的 $dis$，假如另一个点与该节点有连边，则判断 $dis$ 是否一致，如不一致，那一定存在冲突。

## 代码
一个小技巧，由于会有负边权，我们让初始的 $dis$ 设为很大的数，这样就不会有负数了。
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define maxn 200005
#define int long long
vector < pair <int, int> > mp[maxn];
int n, m;
int dis[maxn];
bool flag;
void dfs(int u, int dist) {
    dis[u] = dist;
    for (int i = 0, v, w; i < mp[u].size(); i++) {
        if (flag) return;
        v = mp[u][i].first;
        w = mp[u][i].second;
        if (!dis[v]) dfs(v, dist + w);
        else if (dis[v] != dis[u] + w) {
            flag = true;
            return;
        }
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        flag = false;
        for (int i = 1; i <= n; i++) dis[i] = 0, mp[i].clear();
        for (int i = 0, x, y, z; i < m; i++) {
            cin >> x >> y >> z;
            mp[x].push_back(make_pair(y, z));
            mp[y].push_back(make_pair(x, -z));
        }
        for (int i = 1; i <= n; i++) {
            if (dis[i] == 0) dfs(i, 1e16);
            if (flag) break;
        }
        if (flag) puts("NO");
        else puts("YES");
    }
}
```

---

## 作者：tZEROちゃん (赞：2)

Div. 4 的 H 题。赛时写了 `memset` 疯狂 TLE。

题目告诉了你一堆形如 $b_i-a_i=d_i$ 的约束条件，不难想到差分约束。

考虑转化成差分约束的形式，恰好等于 $d_i$ 就是 $b_i-a_i\le d_i$ 且 $b_i-a_i\ge d_i$。

前一个式子已经是这个形式了，对后面的式子进行变形。两边同时乘以 $-1$ 可以得到：$a_i-b_i\le -d_i$。

对这些约束条件做差分约束即可。

然后你就 TLE 了。

注意到这个很难跑满，我们当 $cnt_i\ge200$ 的时候就直接 `return` 掉，这玩意是可以过的。

欢迎 hack 我（

```cpp
const int N = 1e6 + 10;
vector<pair<int, int>> G[N];
int d[N]; bool v[N];
int cnt[N];
 
bool spfa(int x) {
  queue<int> q;
  q.push(x); d[x] = 0, v[x] = 1;
  while (q.size()) {
    auto x = q.front(); v[x] = 0;
    q.pop();
    for (auto i : G[x]) {
      int t = i.first; ++cnt[t];
      if (cnt[t] == 200) {
        return 0;
      }
      if (d[t] > d[x] + i.second) {
        d[t] = d[x] + i.second;
        if (!v[t]) {
          q.push(t); v[t] = 1;
        }
      }
    }
  }
  return 1;
}
 
void solve() {
  int n, m; cin >> n >> m;
  rep (i, 0, n) G[i].clear();
  rep (i, 0, n) cnt[i] = 0, d[i] = 5e17, v[i] = 0;
  rep (i, 1, n) G[0].pb({i, 0});
  rep (i, 1, m) {
    int x, y, z; cin >> x >> y >> z;
    G[x].pb({y, z}); G[y].pb({x, -z});
  }
  cout << (spfa(0) ? "YES" : "NO") << '\n';
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int q; cin >> q;
  while (q--) solve();
  return ~~(0 ^ 0);
}
```

---

## 作者：Aewrxuk (赞：1)

题目链接：[The Third Letter](https://www.luogu.com.cn/problem/CF1850H)。

这是带权并查集的模板题，但是我不会。你可以让在前面的是在后面的祖先，也可以反过来，这都无所谓，主要是并查集的权值传递，我们用一个 `d[i]` 来存 $i$ 到其祖先的距离，这个距离我们可以在查找祖先时递归更新实现，主要需要注意的就是两个连通块合并的时候，更新两个连通块祖先的距离（自己思考一下其实很简单）。对于出现环的情况，就需要判断存不存在重边不同权值，如果存在，记录一下，最后输出 `NO`；否则，输出 `YES` 即可。记得开 `long long`。

代码实现：
```cpp
int n, m, x, y, z, p, T;
int d[300010], f[300010];
int Find(int x) {
    if (x == f[x])
        return x;
    else {
        int fx = Find(f[x]);
        d[x] += d[f[x]];
        f[x] = fx;
        return f[x];
    }
}
signed main() {
    cin >> T;
    while (T--) {
        p = 0;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            d[i] = 0, f[i] = i;
        for (int i = 1; i <= m; i++) {
            cin >> x >> y >> z;
            if (p == 1)
                continue;
            int fx = Find(x), fy = Find(y);
            if (fx != fy) {
                f[fy] = fx;
                d[fy] = d[x] + z - d[y];
            } else {
                if (d[y] - d[x] != z) {
                    p = 1;
                }
            }
        }
        if (!p)
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
    }
    return 0;
}
```


---

## 作者：MrPython (赞：0)

这是一个并查集的题目。

题目要求我们维护多个人之间关系的传递（譬如说已知 A 在 B 前面 $1\text{m}$，B 在 C 前面 $1\text{m}$，则应该能计算出 $A$ 在 $C$ 前面 $2\text{m}$）。

考虑并查集：已知 $A$ 和 $B$ 处于一个集合，$B$ 和 $C$ 处于一个集合，则 $A$ 和 $C$ 处于一个集合。这是不是很像题目要求我们维护的关系？因此。我想到使用并查集解决这个问题。

题目要维护人们之间的距离，因此原先的 `fa` 数组应当作修改。`fa` 数组的定义如下：
```cpp
struct node{size_t p;long long int dis;};
vector<node> fa;
```
其中，`p` 仍然表示父节点，而 `dis` 表示**子结点在父节点前面的距离**（若在后面则为负数）。

`find` 函数除了要找到树根，还要计算**当前节点在树根前面的距离**。
```cpp
node find(size_t x){
    if (x==fa[x].p) return {x,0}; //自己就是树根，与树根的距离就是0
    else{
        node res=find(fa[x].p);
        return fa[x]={res.p,res.dis+fa[x].dis}; 
        /*树根就是 res.p；
          当前节点到树根的距离 = 父节点与根的距离 res.dis + 当前节点与父节点的距离 fa[x].dis。
          同时路径压缩，fa[x] 接记录与根的距离。*/
    }
}
```
最后，就是最重要的合并函数了。我选择将查询函数与合并函数放到一块写。若 `x` 和 `y` 不在一个集合内（关系无法判断），则合并然后返回 `true`；否则，根据并查集维护的两点之间的距离与给定条件比对。
```cpp
bool merge(size_t x,size_t y,long long int dis){
    node fax=find(x),fay=find(y);
    if (fax.p!=fay.p){
        fa[fax.p]={fay.p,-fax.dis+fay.dis+dis};
        return true;
    }else return fax.dis==fay.dis+dis;
}
```
最后，**不开 long long 见祖宗**（某人因此被 hack 了）

### 完整代码：
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
class dsds{
    struct node{size_t p;long long int dis;};
    vector<node> fa;
    node find(size_t x){
        if (x==fa[x].p) return {x,0};
        else{
            node res=find(fa[x].p);
            return fa[x]={res.p,res.dis+fa[x].dis};
        }
    }
public:
	//构造函数，将数组大小初始化为 n ，循环赋值父节点为自己，dis 初始化为 0
    dsds(size_t n):fa(n){for (size_t i=0;i<n;i++) fa[i].p=i,fa[i].dis=0;}
    bool merge(size_t x,size_t y,long long int dis){
        node fax=find(x),fay=find(y);
        if (fax.p!=fay.p){
            fa[fax.p]={fay.p,-fax.dis+fay.dis+dis};
            return true;
        }else return fax.dis==fay.dis+dis;
    }
};
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        size_t n,m;bool flag=true;  //是否全部符合的标记
        cin>>n>>m;
        dsds ds(n);
        while (m--){
            size_t a,b;long long int d;
            cin>>a>>b>>d;
            if (!ds.merge(--a,--b,d)) flag=false; //个人习惯从 0 存储因此 -1；当不符合（返回 false）时才标记 flag，因此要作非运算
        }
        cout<<(flag?"YES":"NO")<<'\n';
    }
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

若限制 $u$ 站在 $v$ 前方第 $w$ 个位置，则对 $u,v$ 的位置，知道一个就可以推出另一个，称此时 $u,v$ 连通，

则对每个连通块，钦定一个点的位置（可以任意选定），就可以推出剩下所有点。

用这种方式确定每个点的位置后，检查每个限制条件是否被满足即可。

```cpp
#include <cstdio>
#define int long long
struct E
{
    int v, w, t;
} e[400050];
bool b[400050];
int T, n, m, c, d[400050], h[400050];
void A(int u, int v, int w)
{
    e[++c] = {v, w, h[u]};
    h[u] = c;
}
void D(int u)
{
    b[u] = 1;
    for (int i = h[u], v; i; i = e[i].t)
        if (!b[v = e[i].v])
            d[v] = d[u] + e[i].w, D(v);
}
signed main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld", &n, &m);
        for (int i = 0, u, v, w; i < m; ++i)
            scanf("%lld%lld%lld", &u, &v, &w), A(u, v, w), A(v, u, -w);
        for (int i = 1; i <= n; ++i)
            if (!b[i])
                D(i);
        bool F = 1;
        for (int u = 1; u <= n; ++u)
        {
            for (int i = h[u], v; i; i = e[i].t)
                if (d[v = e[i].v] - d[u] != e[i].w)
                {
                    puts("NO");
                    F = 0;
                    break;
                }
            if (!F)
                break;
        }
        if (F)
            puts("YES");
        for (int i = 1; i <= n; ++i)
            b[i] = d[i] = h[i] = c = 0;
    }
    return 0;
}
```


---

## 作者：白简 (赞：0)

### 题目大意
$n$ 个士兵站队，给出 $m$ 个限制，要求士兵 $b$ 站在士兵 $a$ 前面距离为 $d$ 的位置，可以有多个士兵站在同一个位置。询问给定限制下是否存在合法的列队方案。
### 思路
我们考虑把互相有直接或间接限制的点看作一棵树，加入到树中的结点是受到限制的。

最开始的状况没有限制，我们考虑逐个加入限制。最开始是一片森林，每棵树中只有一个结点，感觉很像并查集。

对于每个结点，我们维护它与自己祖先之间的相对距离，记录一个 `pos`。并查集合并时，我们只需要更改它祖先的 `pos`。

关于判无解，只需要考虑两个结点是否在同一个集合中以及距离是否与集合中的限制相等。

其他的就是普通的带权并查集操作。

记得开 `long long`。
### Code
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
 
const int N = 200500;
 
int n,m;
 
struct Limits{
    int a,b;
    long long d;
}t[N];
 
long long pos[N];
int fa[N],size[N];
 
class DSU{
public:
    int Find(int x) {
        if(fa[x] == x)
            return x;
        int tmp = Find(fa[x]);
        pos[x] += pos[fa[x]];
        fa[x] = tmp;
        return Find(fa[x]);
    }
 
    void Union(int x,int y,long long dis) {
        int fx = Find(x);
        int fy = Find(y);
 
        if(fx == fy)
            return ;
        
        fa[fy] = fx;
 
        pos[fy] = pos[x] - dis - pos[y];
    }
 
    bool Check(int x,int y,long long dis) {
        if(Find(x) == Find(y)) 
            return pos[x] - pos[y] != dis;
        
        return 0;
    }
}dsu;
 
signed main() {
    int T;
    cin >> T;
    while(T--) {
        cin >> n >> m;
        for(int i = 1;i <= n; i++)
            fa[i] = i;
 
        for(int i = 1,u,v,w;i <= m; i++) {
            cin >> u >> v >> w;
 
            t[i].a = u;
            t[i].b = v;
            t[i].d = w;
        }
 
        bool flag = 0;
        for(int i = 1;i <= m; i++) {
            if(dsu.Check(t[i].a,t[i].b,t[i].d)) {
                cout << "NO\n";
                flag = 1;
                break;
            }
 
            dsu.Union(t[i].a,t[i].b,t[i].d);
        }
        if(!flag)
            cout << "YES\n";
        for(int i = 1;i <= n; i++)
            pos[i] = 0;
    }
    return 0;
}
```

---

## 作者：liangjindong0504 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1850H)

本蒟蒻赛时写挂了，特地来写一篇纪念。
### 题意简述
有 $t$ 组数据。

每组数据中，会给出士兵人数 $n$ 以及条件数 $m$。

接下来 $m$ 行，每行三个整数 $a_i,b_i,d_i$，表示士兵 $b_i$ 要在士兵 $a_i$ 后 $d_i$ 的位置上。如果所有条件都能满足，输出 ```yes```，否则输出 ```no```。

注意可以有几个士兵在同一位置。
### 题目分析

首先我们可以设 $dp_i$ 为第 $i$ 个士兵的位置（可以将士兵的位置看成点权）。

其次，我们把几个士兵看作几个节点，将题目中的 $d_i$ 看作边权就可以把他变成一棵树了。

这样，只需要 ```dfs``` 一遍，看看是否会发生矛盾就可以了。具体见实现。
### 实现
提醒两句话，第一句：**有多组数据**。第二句：不开 ```long long``` 见祖宗（我就因为这没进前 1000，太弱了）。

基本要讲的都在注释中了。

定义：

```cpp
//node 为边的结构体，本人用了 vector 存边。v 表示一个子节点，w 表示边权。
struct node{
	long long v,w;
};
vector<node>vec[200010];
//t 为数据组数。 
int t;
//n，m，a，b，d 都在题目中出现，这里不一一解释。 
long long n,m;
long long a,b,d;
//dp 数组用于存士兵的坐标。 
long long dp[200010];
//flag 数组用于判断是否访问过，作用在后面会讲。 
bool flag[200010];
//no 用于判断是否矛盾。 
bool no;
```

大部分人能看懂吧。

接下来，是最重要的搜索（查是否矛盾）。

在搜索当中，考虑遍历当前节点的每一个子节点，如果被标记过了，说明该士兵的位置已经确定了，若当前节点权值加上边权不等于子节点权值就可以直接输出 ```no```。如果未被标记，直接标记子节点并确定子节点权值，然后继续搜。最后一直没出现矛盾，输出 ```yes```。详见代码。

```cpp
void dfs(int u){//u 表示父节点 
	//如果已经矛盾了，就没必要搜下去了。 
	if(!no){
		return;
	}
	//遍历所有子节点。 
	for(int i=0;i<vec[u].size();i++){
		//如果矛盾了，打断，因为有可能会输出冗余的 no。 
		if(!no){
			return;
		}
		//y 为子节点编号。 
		int y=vec[u][i].v;
		//w 为边权。 
		long long wei=vec[u][i].w;
		//如果访问过了，看看有没有发生矛盾。 
		if(flag[y]){
			//如果发生矛盾了！ 
			if(dp[u]+wei!=dp[y]){
				//将 no 改成 0。 
				no=0;
				//输出 NO。 
				cout<<"NO"<<endl;
				return;
			}
			//访问过，无需继续搜。 
			continue;
		}
		//否则将该子节点标记为访问过，并更新 dp 数组。 
		dp[y]=dp[u]+wei;
		flag[y]=1;
		//继续搜。 
		dfs(y);
	}
}
```

既然搜索都成功写出来了，那主函数也肯定没问题了吧！

只需要注意清零基本就没问题了。

```cpp
//输入数据组数。 
cin>>t;
while(t--){
	//注意清零！！！ 
	for(int i=1;i<=n;i++){
		vec[i].clear();
	}
	memset(dp,0,sizeof(dp));
	memset(flag,0,sizeof(flag));
	//其实把 no 赋值为 0 也是可以的，赋成 1 是本人习惯这样。 
	no=1;
	//输入。 
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a>>b>>d;
		//存边。为什么第二个是 -d 呢？
		//因为若 b 在 a 的前 d 米处，则 a 在 b 的后 d 米处，即在 b 的前 -d 米处。 
		//注意存双向边（感觉存单向边也行，但没试过）。 
		vec[a].push_back((node){b,d});
		vec[b].push_back((node){a,-d});
	}
	//一个一个 dfs 未被访问过的士兵。 
	for(int i=1;i<=n;i++){
		//没被访问过。 
		if(!flag[i]){
			//标记为已访问。 
			flag[i]=1;
			//默认 dp[i] 为 1。 
			dp[i]=1;
			//开搜！ 
			dfs(i);
			//如果已经不行了就没必要搜下去了。 
			if(!no){
				break;
			}
		}
	}
	//如果依然未查出矛盾的地方，输出 yes。 
	if(no){
		cout<<"YES"<<endl;
	}
}	
```

### 完整代码和评测记录
[代码](https://www.luogu.com.cn/paste/7wm1gmj3)

[提交记录](https://www.luogu.com.cn/record/117123345)

---

## 作者：_sunkuangzheng_ (赞：0)

**【简要题意】**

长度为 $n$ 的序列，$m$ 个限制条件形如 $a_i = a_j +c$，问是否存在一个序列 $a$，序列 $a$ 的值域不限，满足全部 $m$ 条限制，多测。$1 \le m \le n \le 2 \times 10^5$。

**【题目分析】**

一开始可能会想到差分约束系统，如果有负环那么无解。

但是，这题，它卡 SPFA，如果你写了会获得 TLE。

注意到所有的条件都是相等，我们可以直接 dfs，每次钦定一个节点去遍历，如果有一个点遍历两次且值不同，那么就说明无解。由于每条边只会遍历一次，所以时间复杂度为 $\Theta(n+m \log m)$，其中 $\log m$ 是使用 `map` 判断重边的复杂度。

代码实现上，用 $vis_i$ 表示**边** $i$ 是否被遍历过，$ct_i$ 表示**点** $i$ 的权值，深搜即可。

**注意 $vis$ 存边，所以清空时要清空到 $2m$ 而不是 $n$**。还要注意对重边的处理。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 200005;
int t,n,m,ans,head[MAXN],cnt,vis[MAXN*4],dis[MAXN],s,ct[MAXN],flag;
map<pair<int,int>,int> mp1,mp2;
struct edge{
	int to,nxt,w;
}e[1000005];
void add(int u,int v,int w){
	e[++cnt].w = w;
	e[cnt].to = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
queue<int> q;
void dfs(int u,int k){
    ct[u] = k;if(flag) return;
    for(int i = head[u];i;i = e[i].nxt){
        if(vis[i]) continue;int v = e[i].to;
        if(ct[v] != ct[u] + e[i].w && ct[v] != -1e18) {flag = 1;return;}
        vis[i] ++, vis[i^1] ++,dfs(v,k+e[i].w);
    }
}
signed main(){
    cin >> t;
    while(t --){
        cin >> n >> m,mp1.clear(),mp2.clear();
        cnt = 1,flag = 0;for(int i = 0;i <= n;i ++) head[i] = vis[i] = 0,ct[i] = -1e18;
        for(int i = 1;i <= m*2+1;i ++) vis[i] = 0;
        for(int i = 1;i <= m;i ++){
            int x,y,c;
            cin >> x >> y >> c;
            if(mp2[make_pair(x,y)] && mp1[make_pair(x,y)] != c) flag = 1;
            mp1[make_pair(x,y)] = c,mp1[make_pair(y,x)] = -c;
            if(!mp2[make_pair(x,y)]) add(x,y,c),add(y,x,-c);
            mp2[make_pair(x,y)] = 1,mp2[make_pair(y,x)] = 1;
            
        }
        if(flag) {cout << "NO\n";continue;}
        for(int i = 1;i <= n;i ++) if(ct[i] == -1e18) dfs(i,0);
        if(flag) cout << "NO\n";
        else cout << "YES\n";
    }
	return 0;
}
```

---

## 作者：Light_az (赞：0)

根据题意我们发现士兵会形成一张无向图，因此考虑我们采用搜索解决本问题。

首先定义数组来记录每个士兵的距离，建无向图，再枚举 $n$ 个士兵。

当一个士兵没有被搜索过时，我们将这个士兵的距离定义为 $1$，然后以它为父亲节点接着向下搜，我们定义儿子节点的距离就是父亲节点的距离加上儿子与父亲之间的距离。

当我们发现一个儿子节点已经被搜索过但是父亲的距离加上儿子与父亲的距离却不等于儿子的距离时，说明数据存在冲突，因此我们退出搜索输出无解即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define D double
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,cnt,ans,t,l,r,len,T,a[N];
ll mn=INT_MAX,mx=0,p,opt;
struct Node{
	ll to,nxt,dis;
}tr[N];
ll head[N],vis[N];
void add(ll u,ll v,ll w){
	t++;
	tr[t].to=v;
	tr[t].dis=w;
	tr[t].nxt=head[u];
	head[u]=t;
}
void dfs(ll u){
	if(k) return ;//无解不需要继续搜索 
	for(ll i=head[u];i;i=tr[i].nxt){
		ll v=tr[i].to;
		if(vis[v]){//儿子被访问 
			if(a[u]+tr[i].dis!=a[v]){//距离有冲突 
				k=1;
				return ;
			}
		} 
		else{//访问儿子，定义儿子的距离 
			vis[v]=1;
			a[v]=a[u]+tr[i].dis;
			dfs(v);
		}
		
	}
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		t=k=0;
		F(i,1,n) a[i]=head[i]=vis[i]=0;//多组数据清空 
		F(i,1,m){//无向图 
			cin>>u>>v>>w;
			add(v,u,-w);
			add(u,v,w);
		}
		F(i,1,n){
			if(!vis[i]){//没有遍历 
				vis[i]=1;
				a[i]=1;
				dfs(i);
			}
			if(k) break;
		}
		if(k) cout<<"NO\n";//无解 
		else cout<<"YES\n";
	} 
	
	return 0;
}


```


---

