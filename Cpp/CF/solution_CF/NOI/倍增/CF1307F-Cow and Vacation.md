# Cow and Vacation

## 题目描述

Bessie 正在准备度假。

他所在的个洲有 n 个城市，n-1 条双向道路连接。保证可以从任意一个城市到任意一个城市。

Bessie 考虑了 v 种度假方案，每种方案包括从城市 ai 开始到城市 bi 结束。

已知一共有 r 个城市拥有休息点。Bessie 容易疲倦，并且他不能在不休息的情况下穿越超过 k 条连续道路。有时，他还会因为太想休息而多次穿过同一个城市。

对于每一种旅行方案，Bessie 是否有从出发城市到结束地城市的旅行方式？

## 说明/提示

第一个例子的图表如下所示。休息站用红色表示。

对于第一个查询，Bessie 可以按以下顺序访问这些城市：1->2->3。

对于第二个查询，Bessie 可以按以下顺序访问这些城市： 3->2-> 4-> 5。

对于第三个查询，Bessie 无法前往目的地。例如，如果她试图这样旅行：3->2->4->5->6，他在2条以上的道路上旅行而没有休息。

## 样例 #1

### 输入

```
6 2 1
1 2
2 3
2 4
4 5
5 6
2
3
1 3
3 5
3 6```

### 输出

```
YES
YES
NO```

## 样例 #2

### 输入

```
8 3 3
1 2
2 3
3 4
4 5
4 6
6 7
7 8
2 5 8
2
7 1
8 1```

### 输出

```
YES
NO```

# 题解

## 作者：I_am_Accepted (赞：20)

~~良心题解，管理员求过。~~

有任何关于此篇题解的问题皆可私信[我](https://www.luogu.com.cn/user/101868)。

### 题意简述

简述不了 qwq。

### 题目分析

假设你是 Bessie，来脑中模拟一下度假过程：

1. 出发！

2. 向终点跑去。

3. 若跑着跑着饿了，找驿站吃饭（可以绕路）。

4. 步骤 2 和 3 重复。

5. 到达终点。

发现步骤 4 中 Bessie 不断从驿站到驿站。

我们马上想到**给所有驿站建立并查集**

两个驿站若**在树上有长度不大于 $m$（题中的 $k$）的路径**（此操作可从每个驿站半径为 $\frac{m}{2}$ 扩散用 BFS 在 $O(n)$ 内完成），则放入同一个并查集内。

此时同一个并查集内的驿站 **Bessie 要么都能到达，要么都不能到达**。

这就可以判断了：

- 若 $dis(x,y)\leq m$ 不用驿站直接到达。

- 设 $ans_1$ 和 $ans_2$ 分别表示 $x$ 和 $y$ 分别在 $path_{x,y}$ 上前进 $\frac{m}{2}$ 步后的点。若 $ans_1$ 和 $ans_2$ 两者皆在某驿站的扩散范围内，且两驿站在同一并查集内，则可通过驿站到达。

- Otherwise 不行（达咩）

### Details

若 $m$ 为奇数，则所有有关 $\frac{m}{2}$ 的代码部分将变得非常棘手。

此时只要双倍开点（原每条线段中间新增一个点），此时新图的问题中 $m$ 变成了 $2m$，必然是偶数，解决！

### ACcode
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define FOR(i,j,k) for(register int i=j;(j<k)?(i<=k):(i>=k);i+=(j<k)?1:(-1))
#define IO ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 233333

int n,m,k;
int f[2*N][21];//倍增father
int dep[2*N];//deep
int grf[2*N];//并查集的father
int vis[2*N];//bfs标记 （到驿站的dis）
vector<int> e[2*N];//边 
int gf(int x) {//路径压缩求祖先 
	if(grf[x]==x)return x;
	return grf[x]=gf(grf[x]);
}
int move(int x,int val) {//将x向祖先move val步后的id 
	FOR(i,20,0) {
		if((1<<i)<=val) {
			val-=(1<<i);
			x=f[x][i];
		}
	}
	return x;
}
int lca(int x,int y) {
	int xx,yy;
	if(dep[x]<dep[y])swap(x,y);
	x=move(x,dep[x]-dep[y]);
	if(x==y)return x;
	FOR(i,20,0) {
		xx=f[x][i];
		yy=f[y][i];
		if(xx!=yy) {
			x=xx;
			y=yy;
		}
	}
	return f[x][0];
}
void dfs(int rt,int fa) {
	dep[rt]=dep[fa]+1;
	f[rt][0]=fa;
	FOR(i,1,20)f[rt][i]=f[f[rt][i-1]][i-1];
	for(int i:e[rt]) {
		if(i==fa)continue;
		dfs(i,rt);
	}
}
signed main() {
	IO;
	cin>>n>>m>>k;
	int x,y,z;
	FOR(i,1,n-1) {
		cin>>x>>y;//为判断奇偶方便虚拟点n+i 
		e[x].pb(n+i);//push_back 
		e[y].pb(n+i);
		e[n+i].pb(x);
		e[n+i].pb(y);
	}
	dfs(1,0);
	FOR(i,1,n*2)grf[i]=i;//init 
	queue<int> q;
	memset(vis,-1,sizeof vis);
	FOR(i,1,k) {
		cin>>x;
		q.push(x);
		vis[x]=0; 
	}
	while(!q.empty()) {//广搜 半径m 
		int tmp=q.front();
		q.pop();
		if(vis[tmp]==m)break;
		for(int i:e[tmp]) {
			grf[gf(i)]=gf(tmp);//并查集合并（多个驿站联合 商帮） 
			if(vis[i]==-1) {
				vis[i]=vis[tmp]+1;
				q.push(i);
			}
		}
	}
	int qu,ans1,ans2;
	cin>>qu; 
	FOR(i,1,qu) {
		cin>>x>>y;
		z=lca(x,y);
		int len=dep[x]+dep[y]-2*dep[z];//dis计算 
		if(len<=2*m)cout<<"YES"<<endl;//直接走 
		else {//抽屉原理：一定有一边从出发点至LCA距离>=m 
			ans1=(m<=dep[x]-dep[z])?gf(move(x,m)):gf(move(y,len-m));//x向y走m步 
			ans2=(m<=dep[y]-dep[z])?gf(move(y,m)):gf(move(x,len-m));//y向x走m步 
			cout<<(ans1==ans2?"YES":"NO")<<endl;//康康是否在一个并查集里 
		}
	}
	return 0;
}

```

~~看完了，点个赞再走吧。~~

---

## 作者：MusicBox (赞：9)

### 题意简述

给你一棵树，其中某些节点是休息点，然后询问能否从  $l_i$ 到 $r_i$ 。

如果 $l_i$ 能到达 $r_i$ ，则路径中，每一个休息点往后走 $k$ 步必定出现至少一个新的休息点吗，请注意，$k$ 是固定的，而 $l_i$ 和 $r_i$ 每次询问给出。

注意，询问中，由于起始点和终点的特殊性，我们将 $l_i$ 和 $r_i$ 看作休息点，但是在下面的题解中，休息点不包括始终点。

 ### 思路

我们发现，如果从一个休息点 $A$ 到另一个休息点 $B$ 的距离小于等于 $k$，我们必然会有从 $A$ 向外扩散 $k$ 步之内到达 $B$。

那么，如果是多个点在一起判断呢？

我们发现，以每个休息点画一个半径为 $\frac{k}{2}$ 的圆（抽象的说，其实就是标记一下 $\frac{k}{2}$ 步内能到达的点），如果两个休息点的圆出现了交集，那么这两个圆所对应的休息点必然可以在 $k$ 步内到达。

考虑用并查集直接维护。

如果要询问从 $l_i$ 到 $r_i$ 呢，而不是从某个休息点到另一个休息点呢？

我们可以画出从 $l_i$ 到 $r_i$ 的最短路径，从 $l_i$ 和 $r_i$ 各向对方走 $\frac{k}{2}$ 步，然后判断这两个点是否在一个集合内。

这一步操作很好理解，大家可以画一下图。（我画的太抽象就不给大家看了 /qd）

### 细节

#### 1. 我们怎么维护两个休息点是否可以到达？

对于每个休息点都开始 bfs，按照搜索深度一直搜索，当某个点遇到已经搜索过的点，就不在遍历，但是要合并一下两个点。

```cpp
while(!que.empty()) {
    int u = que.front().first;
    int len = que.front().second;
    que.pop();
    if(len == k / 2) return ;
    for(auto v : p[u]) {
        merge(u, v);
        if(!go[v]) {
            go[v] = 1;
            que.push({v, len + 1});
        }
    }
}
```

讲的很抽象，看一下代码就明白了。

正确性也很好证明，每一个点被访问都是搜索深度最小的时候被访问的，那么我们每个点可以搜索的范围就是最广的，而每个点至被遍历一次，复杂度 $O(n)$



#### 2. k 如果是奇数怎么处理 $\frac{k}{2}$ ？

双倍扩点。



剩下的一些小细节其他的题解也说的很清楚了，如果感觉有问题，可以看下我的代码：

```cpp
/*
 * @Author: Linmobi
 * @Date: 2023-07-28 18:50:44
 * @LastEditTime: 2023-07-29 16:40:09
 */
#include<bits/stdc++.h>
// #define int long long
typedef long long ll;
typedef unsigned long long ull;
#define rep(i, a, b) for(int i = (a); i <= signed(b); i ++)
#define per(i, a, b) for(int i = (a); i >= signed(b); i --)

using namespace std;

const int P = 1e9 + 7;
const int L = 4e5 + 5;

inline ll qpow(ll a, ll b) { ll ans = 1, q = a; while(b) { if(b & 1) { ans *= q; ans %= P; } q *= q; q %= P; b >>= 1; } return ans; }
inline int read() {int f = 0, x = 1; char ch = getchar(); while(ch < '0' || ch > '9') { if(ch == '-') x = -1; ch = getchar(); } while(ch >= '0' && ch <= '9') { f = (f << 1) + (f << 3) + ch - '0'; ch = getchar(); } return x * f; }

int n, k, r, v, a, b, cnt, len[L], st[L][30], fa[L], fre[L], gt[L], go[L];
queue<pair<int, int> > que;
vector<int> p[L];

void debug(int fa, int u) {
    for(auto v : p[u]) {
        if(fa != v) {
            cout << u << ' ' << v << endl;
            debug(u, v);
        }
    }
}

void dfs(int fa, int u, int lenth) {
    st[u][0] = fa;
    len[u] = lenth;
    for(auto v : p[u]) {
        if(v != fa) {
            dfs(u, v, lenth + 1);
        }
    }
}

void mkstable() {
    rep(i, 1, 20) {
        rep(j, 1, n) {
            st[j][i] = st[st[j][i - 1]][i - 1];
        }
    }
}

void initdsu() {
    rep(i, 1, n) {
        fa[i] = i;
    }
}

int getfa(int u) {
    if(fa[u] != u) return fa[u] = getfa(fa[u]);
    return fa[u];
}

void merge(int u, int v) {
    fa[u] = getfa(u), fa[v] = getfa(v);
    fa[fa[u]] = fa[v];
}

void godsu() {
    while(!que.empty()) {
        int u = que.front().first;
        int len = que.front().second;
        que.pop();
        if(len == k / 2) return ;
        for(auto v : p[u]) {
            merge(u, v);
            if(!go[v]) {
                go[v] = 1;
                que.push({v, len + 1});
            }
        }
    }
}

int lca(int l, int r) {
    if(len[l] < len[r]) {
        swap(l, r);
    }
    per(i, 20, 0) {
        if(len[st[l][i]] >= len[r]) {
            l = st[l][i];
        }
    }
    if(l == r) return l;
    per(i, 20, 0) {
        if(st[l][i] != st[r][i]) {
            l = st[l][i], r = st[r][i];
        }
    }
    return st[l][0];
}

int getnode(int u, int lenth) {
    per(i, 20, 0) {
        if(lenth >= (1 << i)) {
            lenth -= (1 << i);
            u = st[u][i];
        }    
    }
    return u;
}

signed main() {
    n = read(), k = read(), r = read();
    k *= 2; 
    cnt = n;
    rep(i, 2, n) {
        a = read(), b = read(), ++ cnt;
        p[a].push_back(cnt);
        p[cnt].push_back(a);
        p[cnt].push_back(b);
        p[b].push_back(cnt);
    }
    n += (n - 1);
    dfs(1, 1, 1);
    mkstable();
    initdsu();
    rep(i, 1, r) {
        fre[i] = read();
        que.push({fre[i], 0});
        go[fre[i]] = 1;
    }
    godsu();
    v = read();
    rep(i, 1, v) {
        int l = read(), r = read();
        int LCA = lca(l, r);
        if(len[l] > len[r]) swap(l, r);
        if(len[l] + len[r] - 2 * len[LCA] <= k) goto yes;
        if(len[l] - len[LCA] < k / 2) {
            if(getfa(getnode(r, (len[r] + len[l] - 2 * len[LCA] - k / 2))) == getfa(getnode(r, k / 2))) goto yes;
            else goto no;
        } else {
            if(getfa(getnode(l, k / 2)) == getfa(getnode(r, k / 2))) goto yes;
            else goto no;
        }
        yes:;
        puts("YES");
        continue;
        no:;
        puts("NO");
    }
    return 0;
}
```



---

## 作者：KK_lang (赞：7)

难度虚高。

依题意，如果两个休息站之间的距离 $\leq k$，则这两个点是可以互相到达的。

有休息站之间是对称的，故等价于每个休息站能控制到它的距离 $\leq k/2$ 的所有点，若存在一个点能被两个休息站控制，那么这两个休息站是可以互相到达的。

考虑 $k$ 不一定为偶数，不妨在每跳边上加一个中间点，这样原先每条边的长度就变成了 $2$，故每个休息站就可以控制到它距离 $\leq k$ 的点了，十分的优雅。

对于每个休息站跑一个迭代层数为 $k$ 的 bfs，并把跑到的所有点使用并查集并到该休息站，这样互相可达的休息站就在一个集合里了。

考虑起点 $a_i$，终点 $b_i$，同理，也可以视为到 $a_i$ 距离 $\leq k$ 的是 $a_i$ 可以到达的，到 $b_i$ 距离 $\leq k$ 的是可以走到 $b_i$ 的。

故考虑 $a_i$ 和 $b_i$ 都向他们的 lca 移动 $k$ 步到达 $a_i'$ 和 $b_i'$，若 $a_i'$ 和 $b_i'$ 在同一个集合内则成立，否则失败。

注意 $a_i'$ 和 $b_i'$ 是否越过 lca。

[$\text{Submission}$](https://codeforces.com/problemset/submission/1307/276536199) $\&$ [$\text{Code}$](https://www.luogu.com.cn/paste/2yiyyup7)

---

## 作者：OMG_wc (赞：7)



题意：$n$ 个点构成树上有 $r$  个休息站。从一个点出发，如果不经过休息站，最多只能走 $k$ 步（只要走到休息站，下次又可以走 $k$ 步）。现在有 $v$ 个询问，每个询问让你判断从 $x$ 出发能否到达 $y$。

根据样例2，我们发现如果两个休息站的距离 $\le k$，那么你就可以在这些休息站之间任意走动。也就是说，每个休息站的控制范围是距离 $\frac{k}{2}$  范围内的点，然后看任意两个休息站是否重叠。

$k$ 是奇数的时候，控制半径不是整数不是很方便，一种优雅的解决方案是：在每条边中间加一个点，这样原来距离为 $1$ 就变成了 $2$，题目要求的 $k$ 变成了 $2k$，控制半径变成了 $k$。

那么只要对所有休息站放进队列里，进行一次BFS，最多扩展 $k$ 距离，用并查集维护每个点属于哪个休息站。如果一个点属于多个休息站，那这两个休息站就能合并。

对每个询问，首先判断两个点的距离是否小于 $k$（这里需要用倍增求LCA），小于 $k$ 直接就是可达的。否则让两个点各种往对方的方向走 $k$ 步（也是利用倍增来走，注意要判断是否越过LCA），最后判断这两个点是否在并查集里属于同一个集合。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 400005;

vector<int> G[N];
int f[N][20], d[N];
void dfs(int u) {
    d[u] = d[f[u][0]] + 1;
    for (auto v : G[u]) {
        if (v == f[u][0]) continue;
        f[v][0] = u;
        dfs(v);
    }
}
int LCA(int x, int y) {
    if (d[x] < d[y]) swap(x, y);
    int K = 0;
    while ((1 << (K + 1)) <= d[x]) K++;
    for (int j = K; j >= 0; j--) {
        if (d[f[x][j]] >= d[y]) x = f[x][j];
    }
    if (x == y) return x;
    for (int j = K; j >= 0; j--) {
        if (f[x][j] != f[y][j]) {
            x = f[x][j];
            y = f[y][j];
        }
    }
    return f[x][0];
}
int go(int x, int k) {
    for (int j = 19; j >= 0; j--) {
        if (1 << j <= k) {
            k -= 1 << j;
            x = f[x][j];
        }
    }
    return x;
}

int p[N];
int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}
int vis[N];
int main() {
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    int nn = n;
    for (int i = 1; i < nn; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        ++n;
        G[u].push_back(n);
        G[n].push_back(u);
        G[v].push_back(n);
        G[n].push_back(v);
    }
    dfs(1);
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }
    for (int i = 1; i <= n; i++) p[i] = i;
    queue<int> q;
    memset(vis, -1, sizeof vis);
    for (int i = 0; i < r; i++) {
        int x;
        scanf("%d", &x);
        q.push(x);
        vis[x] = 0;
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (vis[u] == m) break;
        for (auto v : G[u]) {
            int x = find(u), y = find(v);
            p[x] = y;
            if (vis[v] == -1) {
                q.push(v);
                vis[v] = vis[u] + 1;
            }
        }
    }

    int g;
    scanf("%d", &g);
    while (g--) {
        int x, y;
        scanf("%d%d", &x, &y);
        int z = LCA(x, y);
        int len = d[x] + d[y] - 2 * d[z];
        if (len <= 2 * m) {
            puts("YES");
        } else {
            int t1 = m <= d[x] - d[z] ? find(go(x, m)) : find(go(y, len - m));
            int t2 = m <= d[y] - d[z] ? find(go(y, m)) : find(go(x, len - m));
            puts(t1 == t2 ? "YES" : "NO");
        }
    }
    return 0;
}

```











---

## 作者：PCCP (赞：5)

## 背景：

调了一整天了，终于是过了，~~帮我调代码的学弟都会这题了（~~，所以必须写一篇题解来纪念一下。

## 思考过程：

不妨把休息点看成重生点，每次从不同的重生点里，走出一个野生 Bessie。

第一眼看到这题，因为和连通性相关，想到以 $ k $ 为范围去扩展，把遍历到的点全部加进并查集里面。但是很快我们发现，这样会导致一个点同时在多个并查集内，但是这些并查集不能合并，这就无法进行实现。想要不冲突，发现以 $ \frac{k}{2} $ 为范围去扩展，就可以保证：一个点被多个重生点遍历到时，这些重生点都是一定可以合并到一起去的。因为这保证了重生点之间的路径长度一定是小于 $ k $ 的。

那么如果 $ k $ 是奇数时，又该怎么办呢？我们把在网络流中学到各种奇怪小技巧想一想，发现把一条边也看成一个点就行了。这样对于边数来说，偶数乘 $ 2 $ 还是偶数，奇数乘 $ 2 $ 则变成了偶数。实现时把 $ k $ 版本更新一下就行了。

查询也好办，可以直接判出来的合法情况有两种：

- 两点已经在同一连通块内；

- 树上两点间路径长度已经小于等于 $ k $。

对于剩余的情况，由于我们是以 $ \frac{k}{2} $ 为范围去扩展的，那么就还差 $ \frac{k}{2} $ 的范围要从周围的非连通块内节点去扩展。由于是树上问题，我们可以使用倍增在 $ \log_2{k} $ 的时间复杂度内爬到**两点路径上**距离两个点距离分别为 $ \frac{k}{2} $ 的两个节点。判定他们是否在同一个连通块内即可。

为什么直接找到这两个节点去判定就是对的呢？很简单，因为树上两点间路径唯一，一个连通块的范围在路径中（当然这里要分类讨论，一种是连通块包含了一个点，一种是连通块不包含任何点，但是简单思考一下都是符合接下来的内容的，读者可自行证明，~~其实是我太懒了~~），它想扩展到路径两端的节点去，就必须经过这两个点。

保证了两点间路径长度大于 $ k $，也就是说，有以下两种子情况：

- 有一个点到最近公共祖先的距离小于 $ \frac{k}{2} $；

- 同上一个情况相反。

两种都可以用倍增实现，非常的简单，写这题的同学想必都会。

## 具体实现细节：

首先是预处理重生点扩展，这里不建议使用 DFS。第一，递归层数多，极易超时；第二，有的同学 ~~（其实是我）~~ 认为可以剪枝，即已经遍历到了的，合并后就不用继续遍历了，这样就可以保证不超时，但是请看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/x37hsbk8.png)

其中 $ k=4 $，节点 $ 1 $ 和 $ 4 $ 是重生点。

求最近公共祖先用倍增即可。查询时，注意距离别算错了。输出注意全是大写。

最后，路径压缩+按秩合并（或启发式合并）的并查集的时间复杂度才是  $ \alpha(n) $。

## 总结：

整个题目难点在于想到把范围折半和实现（因为细节多），属于并查集 + 树上倍增 + 树的遍历方法的集合。其实也就紫题的难度吧，黑题感觉确实有点虚高，~~尽管蒟蒻调了一天~~。

总体时间复杂度：$ O(n(\log_2{n}+\alpha(n))) $。

代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<set>
#include<vector>
#include<map>
using namespace std;
typedef pair<int,int> PII;
const int N=4e5+10;
const int M=8e5+10;
int n,k,r,m,fa[N],siz[N],rt;
int he[N],ne[M<<1],to[M<<1],tot=1;
int fat[30][N],dep[N],yet[N];
queue<int> q;
bool st[N];
inline void addedge(int x,int y){
	to[++tot]=y;
	ne[tot]=he[x];
	he[x]=tot;
}
inline int find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}
inline void unify(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy){
		return;
	}
	if(siz[fx]<siz[fy]){
		swap(fx,fy);
	}
	fa[fy]=fx;
	siz[fx]+=siz[fy];
}
inline void dfs(int x,int f,int deep){
	dep[x]=deep;
	for(int i=he[x];i;i=ne[i]){
		int v=to[i];
		if(v==f){
			continue;
		}
		dfs(v,x,deep+1);
		fat[0][v]=x;
	}
}
inline int lca(int x,int y){
	int l=0;
	while((1<<l)<2*n){
		l++;
	}
	if(dep[x]<dep[y]){
		swap(x,y);
	}
	for(int i=l;i>=0;i--){
		if(dep[y]<=dep[x]-(1<<i)){
			x=fat[i][x];
		}
	}
	if(x==y){
		return x;
	}
	for(int i=l;i>=0;i--){
		if(fat[i][x]!=fat[i][y]){
			x=fat[i][x];
			y=fat[i][y];
		}
	}
	return fat[0][x];
}
inline int getori(int x,int len){
	for(int i=30;i>=0;i--){
		if((1<<i)<=len){
			x=fat[i][x];
			len-=(1<<i);
		}
	}
	return x;
}
int main(){
	scanf("%d%d%d",&n,&k,&r);
	memset(yet,-1,sizeof yet);
	k*=2;
	int x,y,z;
	for(int i=1;i<2*n;i++){
		fa[i]=i;
		siz[i]=1;
	}
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		addedge(x,n+i);
		addedge(n+i,x);
		addedge(n+i,y);
		addedge(y,n+i);
	}
	dfs(1,1,1);
	for(int i=1;(1<<i)<2*n;i++){
		for(int j=1;j<2*n;j++){
			fat[i][j]=fat[i-1][fat[i-1][j]];
		}
	}
	for(int i=1;i<=r;i++){
		scanf("%d",&x);
		st[x]=true;
		q.push(x);
		yet[x]=0;
	}
	while(q.size()){
		int t=q.front();
		q.pop();
		if(yet[t]>=k/2){
			continue;
		}
		for(int i=he[t];i;i=ne[i]){
			int v=to[i];
			unify(v,t);
			if(yet[v]==-1){
				yet[v]=yet[t]+1;
				q.push(v);
			}
		}
	}
	scanf("%d",&m);
	while(m--){
		scanf("%d%d",&x,&y);
		if(dep[x]>dep[y]){
			swap(x,y);
		}
		int LCA=lca(x,y);
		if(find(x)==find(y)||dep[x]+dep[y]-2*dep[LCA]<=k){
			printf("YES\n");
			continue;
		}
		int lx,ly,len;
		if(dep[x]-dep[LCA]<k/2){
			len=dep[y]-dep[LCA]-(k/2-(dep[x]-dep[LCA]));
			lx=getori(y,len);
			ly=getori(y,k/2);
		}
		else if(dep[y]-dep[LCA]<k/2){
			len=dep[x]-dep[LCA]-(k/2-(dep[y]-dep[LCA]));
			ly=getori(x,len);
			lx=getori(x,k/2);
		}
		else{
			lx=getori(x,k/2);
			ly=getori(y,k/2);
		}
		if(find(lx)==find(ly)){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
}
```

这么良心的题解，点个赞在走吧~

（2023/7/29 更新：修改了图例解释的错误）

---

## 作者：xtx1092515503 (赞：3)

[CF1307F Cow and Vacation](https://www.luogu.com.cn/problem/CF1307F)

和现行题解不同的偏数据结构做法。

定义 $d_i$ 为节点 $i$ 到最近补给点的距离。则，$x\to y$ 的路径，可以被解释为：

- 一个 counter $c$ 自 $x$ 出发，初始为 $k$。
- 在到达一个点 $z$ 时，若 $c\geq d_z$ 则 $c\to\max(c,k-d_z)$。这对应着在 $z$ 点处可选择走到最近补给点获取补给，也可以放弃。
- 每走一步，$c$ 减一。$c$ 应在任意时刻非负。

显然，若 $x$ 可达 $y$ 则 $y$ 必可达 $x$（将路径反向即可）。考虑自 $x,y$ 同时出发到达点 $z$，此时有 counter $c_x$ 与 $c_y$。我们发现，当且仅当 $c_x+c_y\geq k$，$x,y$ 互相可达。

先考虑套一层淀粉质，在分治块内计算所有跨分治中心的对的答案。自底向上地，我们可以用数据结构维护这一流程：维护子树中所有路径端点的 $c$，向上跳一步就把减到负的 $c$ 扔掉，其对应的路径变得不合法。父亲的集合由合并所有儿子的集合得到，再插入那些自父亲开始的路径端点。在一个点合并完成后，考虑 $d$ 的影响：假如 $d\geq k-d$，则将 $[d,k-d]$ 中所有 $c$ 赋为 $k-d$。

我们发现，任意时刻若在同一点处，两个路径端点对应的 $c$ 值相同，那么接下来的所有时间中它们的 $c$ 值必保持相同。这意味着我们可以用冰茶姬来维护这一流程：我们总是合并 $c$ 值相同的点，使得结构中不存在 $c$ 值相同的元素。

于是我们可以使用 `set` 启发式合并来解决上述问题：合并父子时是简单的（父子有相同键值就合并）；向上跳可以打全局 `tag`；$[d,k-d]$ 的赋值可以暴力扫过区间中所有 counter 将它们合并。

并且，我们发现上述流程甚至不依赖于淀粉质。我们直接将路径拆为 $x\to\text{LCA}$ 与 $y\to\text{LCA}$ 两部分，然后直接运行上述算法，在 $\text{LCA}$ 处查询当前 $x,y$ 所在冰茶姬的值即可。

时间复杂度线性对数或线性对数平方，取决于你维护上述流程使用的数据结构：`set` 启发式合并是后者，线段树合并是前者。但是 `set` 启发式合并要好写很多，这也是本人代码的写法。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,K,m,q;
vector<int>v[200100];
int d[200100];
void dfsup(int x,int fa){for(auto y:v[x])if(y!=fa)dfsup(y,x),d[x]=min(d[x],d[y]+1);}
void dfsdown(int x,int fa){for(auto y:v[x])if(y!=fa)d[y]=min(d[y],d[x]+1),dfsdown(y,x);}
set<pair<int,int> >s[200100];int tag[200100];
int anc[200100][20],dep[200100];
void dfsinit(int x,int fa){
	dep[x]=dep[fa]+1,anc[x][0]=fa;for(int i=1;i<20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
	for(auto y:v[x])if(y!=fa)dfsinit(y,x);
}
int C[400100];
int c[400100],dsu[400100];
int find(int x){return dsu[x]==x?x:dsu[x]=find(dsu[x]);}
vector<int>u[200100],w[200100];
int LCA(int x,int y){
	if(dep[x]>dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[x]<=dep[y]-(1<<i))y=anc[y][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(anc[x][i]!=anc[y][i])x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}
void dfscalc(int x,int fa){
	for(auto y:v[x])if(y!=fa){
		dfscalc(y,x);
		tag[y]++;
		if(!s[y].empty()&&s[y].begin()->first<tag[y])
			C[s[y].begin()->second]=-1,s[y].erase(s[y].begin());
		if(s[y].size()>s[x].size())swap(s[x],s[y]),swap(tag[x],tag[y]);
		for(auto z:s[y]){
			z.first-=tag[y],z.first+=tag[x];
			auto it=s[x].lower_bound(make_pair(z.first,-0x3f3f3f3f));
			if(it!=s[x].end()&&it->first==z.first)dsu[z.second]=it->second;
			else s[x].insert(z),C[z.second]=z.first;
		}
		s[y].clear();
	}
	if(!u[x].empty()){
		auto it=s[x].lower_bound(make_pair(K+tag[x],-0x3f3f3f3f));
		if(it!=s[x].end()&&it->first==K+tag[x])
			for(auto z:u[x])dsu[z]=it->second;
		else{
			int y=u[x].back();u[x].pop_back();
			s[x].emplace(K+tag[x],y),C[y]=K+tag[x];
			for(auto z:u[x])dsu[z]=y;
		}
	}
	if(d[x]<K-d[x]){
		auto it=s[x].lower_bound(make_pair(d[x]+tag[x],-0x3f3f3f3f));
		int las=-1;
		while(it!=s[x].end()&&it->first-tag[x]<=K-d[x]){
			if(las!=-1)dsu[las]=it->second;
			las=it->second;
			it=s[x].erase(it);
		}
		if(las!=-1)s[x].emplace(K-d[x]+tag[x],las),C[las]=K-d[x]+tag[x];
	}
	for(auto z:w[x]){
		c[z]=C[find(z)];
		if(c[z]!=-1)c[z]-=tag[x];
		// printf("%d->%d:%d\n",z,find(z),c[z]);
	}
}
int main(){
	scanf("%d%d%d",&n,&K,&m);
	for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
	memset(d,0x3f,sizeof(d));
	for(int i=1,x;i<=m;i++)scanf("%d",&x),d[x]=0;
	dfsup(1,0),dfsdown(1,0),dfsinit(1,0);
	scanf("%d",&q);
	for(int i=1,x,y,z;i<=q;i++){
		scanf("%d%d",&x,&y),z=LCA(x,y);
		// printf("%d,%d:%d\n",x,y,z);
		u[x].push_back(i),w[z].push_back(i);
		u[y].push_back(i+q),w[z].push_back(i+q);
		dsu[i]=i,dsu[i+q]=i+q;
	}
	dfscalc(1,0);
	for(int i=1;i<=q;i++)puts(c[i]!=-1&&c[i+q]!=-1&&c[i]+c[i+q]>=K?"YES":"NO");
	return 0;
}
```



---

## 作者：UperFicial (赞：3)

感觉 CF*3300 的难度没有这么简单吧（

[题目传送门](https://www.luogu.com.cn/problem/CF1307F)。

同步发表于我的 [$\text{cnblogs}$](https://www.cnblogs.com/UperFicial/p/16718355.html)。

考虑 $\texttt{Bessie}$ 运动的过程：起点 $\to$ 休息点 $\to $ $\cdots$ $\to$ 休息点 $\to$ 终点。

考虑我们把能相互到达的点放到一个连通块，那么问题就变得简单。

我们对于每一个休息点开始 $\text{bfs}$，注意，每个休息点可控制的范围是 $\frac{k}{2}$ 而非 $k$，然后用并查集维护这个连通块。

考虑询问操作：

- 对于询问的两点 $a,b$，若 $\operatorname{dist}(a,b)\le k$，那么这是可行的。

- 若 $a,b$ 在同一个连通块里，那么也是可行的。

- 我们考虑将 $a$ 和 $b$ 分别沿着 $a\to b$ 这条路径向上走 $\frac{k}{2}$ 个点，看看能不能走到一个连通块里。

	
这个东西的实现可以考虑倍增去跳，如果跳着跳着超出了 $\texttt{LCA}$，那么往另一半跳。
    
往另一半跳的过程不好维护，因为是祖先跳到儿子,设 $\texttt{LCA}$ 为 $c$，考虑超出的距离为 $k-\operatorname{dist}(a,c)$，这个东西可以表示成 $b$ 往上跳 $\operatorname{dist}(b,c)-\left(k-\operatorname{dist}(a,c)\right)$ 步，也就是 $b$ 向上跳 $\operatorname{dist}(a,b)-k$ 步到达的点。倍增即可。

注意半径为 $\frac{k}{2}$ 不好处理，我们可以在每条边间插一个点，这样将 $k\leftarrow k\times 2$ 即可。

时间复杂度 $\Theta(n\log n)$。

[代码比较人性化](https://codeforces.com/contest/1307/submission/173011088)。

---

## 作者：无名之雾 (赞：1)

[YeahPotato](https://www.luogu.com.cn/user/94976) 图论杂题选讲里的题，真正意义上的第一道独立做出来的 *3300，虽然感觉难一般。

## solution

下文我们称这些可以休息的点为关键点。

### sol1
一个 [YeahPotato](https://www.luogu.com.cn/user/94976) 提出来的略显暴力的思路是。

考虑对路径上的点逐一求出 LCA，从一个关键点（或起点）出发到它的最少步数 $x$。

向后走时，如果遇到更近且可达的关键点，就更新 $x$，否则 $x$ 加一。这个过程可以将一段区间看作黑盒，如果进入时的 $x$ 过大就走不过去。

否则可以算出经过后的 $x$。倍增即可。具体实现起来需要再处理一下，因为走的过程可逆，所以也从 $b$ 出发倍增到 LCA，最后看两个 $x$ 之和是否 小于等于 $k$。

### sol2

考虑上面那个思路其实并未用完这题的所有性质。

对于一组询问 $(a,b)$：

对于路径上的点 $u$，如果不是 $u$ 直接到 $b$，那么它一定要能到最近的关键点。这意味着这样的点离最近关键点的距离必须 小于等于 $\frac{k}{2}$，且不能出现连续两个点都恰为 $\frac{k}{2}$。

两个驿站若在树上有长度不大于 $k$ 的路径我们就把他扔到一个并查集里。

实现上我们考虑先从 $a$ 和 $b$ 出发以一个类似于 meet-in-the-middle 的方式跳 $\frac{k}{2}$ 步。从关键点多源 BFS $\frac{k}{2}$ 步，要求 $a'$ 到 $b'$ 上的点都被 BFS 到。每条边裂出一个点以处理边界情况。

实际上就是希望 $a',b'$ 最近的关键点可以互达。

[submission](https://codeforces.com/contest/1307/submission/306531618)

---

## 作者：CmsMartin (赞：1)

[更差的阅读体验](http://www.cmsblog.top/archives/cowandvacation)

## 题目描述

有一颗 $n$ 个节点树，其中有 $k$ 个点是关键点。现在有 $m$ 次询问，每次询问是否存在一条 $u \to v$ 的路径（不一定是简单路径），使得路径上任意两个关键点并且 $u,v$ 和路径上与其最近的关键点的距离小于等于 $k$。

$n,m,k \le 2\times10^5$。

## 思路

考虑我们会怎么走，显然是：$u \to$ 关键点 $\to$ 关键点 $\to \cdots \to$ 关键点 $\to v$。

那我们可以建立并查集，把 $k$ 步之内可以互达的关键点以及可以到达他们的普通点并在一块。可以使用 BFS 计算。从每个关键点向外 BFS $\frac{k}{2}$ 步即可。当 $k$ 是奇数的时候，我们只需要对每个点建边并且使 $k$ 乘 $2$ 即可。

接下来我们套路的进行树上倍增，对于一次询问 $u \to v$，我们只需要将 $u$ 向 $v$ 跳 $\frac{k}{2}$ 步，再将 $v$ 向 $u$ 跳 $\frac{k}{2}$ 步。然后再判断跳完后的答案是否在并查集同一集合内即可。

时间复杂度 $\mathcal{O}(n \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N= 2e5 + 5;

vector<int> G[N << 1];
int fa[N << 1][23], p[N << 1], depth[N << 1];
int n, k, r, Q, vis[N << 1];

int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = 19; i >= 0; i--) 
        if (depth[fa[u][i]] >= depth[v])
            u = fa[u][i];
    if (u == v) return u;
    for (int i = 19; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

void dfs(int u, int f) {
    fa[u][0] = f;
    depth[u] = depth[f] + 1;
    for (int v : G[u])
        if (v != f)
            dfs(v, u);
};

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

int move(int u, int k) {
    for (int i = 19; i >= 0; i--) {
        if (1 << i <= k) {
            u = fa[u][i];
            k ^= 1 << i;
        }
    }
    return u;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k >> r;
    for (int i = 1; i <= n << 1; i++) p[i] = i;
    for (int i = 1; i < n; i++) {
        static int u, v;
        cin >> u >> v;
        G[u].push_back(n + i); G[n + i].push_back(u);
        G[v].push_back(n + i); G[n + i].push_back(v);
    }
    dfs(1, 0);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n << 1; j++)
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
    memset(vis, -1, sizeof vis); queue<int> q;
    for (int i = 1; i <= r; i++) {
        static int u;
        cin >> u;
        vis[u] = 0;
        q.push(u);
    }
    while (q.size()) {
        int u = q.front(); q.pop();
        if (vis[u] == k) break;
        for (int v : G[u]) {
            int x = find(u), y = find(v);
            p[x] = y;
            if (vis[v] == -1) {
                q.push(v);
                vis[v] = vis[u] + 1;
            }
        }
    }
    cin >> Q;
    while (Q--) {
        static int u, v, z;
        cin >> u >> v;
        z = LCA(u, v);
        if (depth[u] + depth[v] - 2 * depth[z] <= 2 * k) {
            cout << "YES" << endl;
        } else {
            int t1 = k <= depth[u] - depth[z] ? find(move(u, k)) : find(move(v, depth[u] + depth[v] - 2 * depth[z] - k));
            int t2 = k <= depth[v] - depth[z] ? find(move(v, k)) : find(move(u, depth[u] + depth[v] - 2 * depth[z] - k));
            cout << (t1 == t2 ? "YES" : "NO") << endl;
        }
    }
    return 0;
}

```



---

## 作者：strcmp (赞：0)

*3300！

题目翻译很易懂了。

注意到每次经过一个休息点，休息时间都会重置。

因此考虑休息点往外 $k$ 步到达的其它点，以此类推，这些点形成了一个个的联通块，这个过程可以用 bfs 和并查集做完。

怎么做？每个休息点考虑往外 $\frac{k}{2}$ 步即可，如果 $k$ 是奇数直接拆边即可。将休息点看作一个个的圆，只要这些圆不相离则在同一个联通块内。

方便起见，以下无论 $k$ 的奇偶都将原树拆边，真实的 $k$ 是 $2k$。

那么我们的联通块就是将休息点向外扩展 $k$ 步，**我们可以断言，从不同联通块的两个休息点出发，它们必定互相走不到。**

接下来考虑怎么判断一个询问 $u,\,v$。

首先 $u,\,v$ 的距离小于等于 $2k$ 直接一步完了，不用考虑。

能不能直接考虑 $u,\,v$ 在不在同一联通块？不行，$u$ 和 $v$ 可以看作两个休息站，因为从 $u$ 出发的时候体力是满的，$v$ 的话我们不需要考虑返回。

所以我们要先分别从 $u$ 和 $v$ 走一段路程。

此时从 $u$ 贪心的往 $v$ 的方向走 $k$ 步，$v$ 贪心的往 $u$ 的方向走 $k$ 格。相当于分别从 $u,\,v$ 往外伸出了半径为 $k$ 的圆。

然后考虑新的 $u,\,v$ 是否在同一个联通块内，在那么就判断 `YES` 否则就 `NO`。

时间复杂度瓶颈在于求 LCA 和走 $k$ 步的树上倍增，时间复杂度 $\Theta((n + q) \log n)$。可以使用 $\Theta(n)/\Theta(1)$ LCA 和长链剖分求 $k$ 级祖先做到 $\Theta(n + q)$ 但没有必要。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define mp make_pair
using namespace std;
using ld = double;
typedef long long int ll;
typedef unsigned long long int ull;
using pli = pair<ll, int>;
using ppi = pair<pli, int>;
using vec = vector<int>;
const int maxn = 4e5 + 10;
struct edge { int to, nxt; } nd[maxn << 1]; int h[maxn], cnt = 0, n, k, r;
inline void add(int u, int v) { nd[cnt].nxt = h[u], nd[cnt].to = v, h[u] = cnt++; }
inline void addE(int u, int v) { add(u, v), add(v, u); }
int fa[maxn][20], dep[maxn], pa[maxn], d[maxn];
int find(int x) { return !pa[x] ? x : pa[x] = find(pa[x]); }
void dfs(int u, int f) {
    dep[u] = dep[f] + 1; fa[u][0] = f;
    for (int i = 1; i < 20; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = h[u]; ~i; i = nd[i].nxt) if (nd[i].to != f) dfs(nd[i].to, u);
}
inline int mv(int x, int w) { for (int i = 19; i >= 0; i--) if (w >= 1 << i) w -= 1 << i, x = fa[x][i]; return x; }
inline int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    x = mv(x, dep[x] - dep[y]); if (x == y) return x;
    for (int i = 19; i >= 0; i--) if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
int q[maxn], hd = 1, tl = 0, Q;
int main() {
    memset(h, -1, sizeof h); memset(d, -1, sizeof(d)); scanf("%d%d%d", &n, &k, &r);
    for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), addE(u, n + i), addE(n + i, v);
    for (int i = 1, x; i <= r; i++) scanf("%d", &x), q[++tl] = x, d[x] = 0; dfs(1, 0);
    while (hd <= tl) {
        int u = q[hd++];
        if (d[u] >= k) break;
        for (int i = h[u]; ~i; i = nd[i].nxt) {
            int v = nd[i].to;
            if (find(u) != find(v)) pa[find(v)] = find(u);
            if (d[v] == -1) d[v] = d[u] + 1, q[++tl] = v;
        }
    }
    scanf("%d", &Q);
    while (Q--) {
        int x, y, z;
        scanf("%d%d", &x, &y); z = lca(x, y);
        int w = dep[x] + dep[y] - dep[z] * 2;
        if (w <= k << 1) puts("YES");
        else {
            int s1, s2, p1 = dep[x] - dep[z], p2 = dep[y] - dep[z];
            s1 = ((k <= p1) ? find(mv(x, k)) : find(mv(y, w - k)));
            s2 = ((k <= p2) ? find(mv(y, k)) : find(mv(x, w - k)));
            puts(s1 == s2 ? "YES" : "NO");
        }
    }
    return 0;
}
```

---

## 作者：Raisetsu41 (赞：0)

不难想到要把点的询问挂到对于它最优的休息点上去，于是预处理每个休息点能够辐射到的范围，发现有一些休息点能够互相覆盖，希望将他们塞到一个并查集里面去。  
那么有了第一步，从每个休息点出发走 $\frac{k}{2}$ 步，记录每个点最近的休息点，并将能够互相走到的点塞入一个并查集中。  
说得有点抽象，代码如下

```cpp
inline void spread() {
  for (int u : sp) que.push(mp(u, 0)), pre[u] = u;
  while (!que.empty()) {
    pii now = que.front(); que.pop(); int u = now.first;
    if (now.second >= k >> 1) continue;
    for (int v : G[u]) {
      if (!pre[v]) pre[v] = pre[u], que.push(mp(v, now.second + 1)), dsu.unionset(v, pre[u]);
      else dsu.unionset(pre[v], pre[u]);
    }
  }
}
```

然后考虑回答每一个询问，对于二元组 $(u, v)$，若 $\mathrm{dist}(u, v) \le k$ 那么可以直接走到，否则需要经过休息站。于是从 $u$ 往 $\mathrm{lca}(u, v)$ 跳 $\frac{k}{2}$ 步到 $x$，从 $v$ 往 $\mathrm{lca}(u, v)$ 跳 $\frac{k}{2}$ 步到 $y$。如果 $x,y$ 能够互通，那么 $u, v$ 能够互通。  
接下来论证这个方法的正确性，即是论证 $x$ 能走到的有用的休息站集合和 $u$ 能走到的有用的休息站集合等价，只需要想，如果有一个休息站 $p$，$u$ 能走到，$x$ 不能走到，这就意味着 $\mathrm{dist}(p, x) > k,\mathrm{dist}(p, u) \le k$，因为 $\mathrm{dist}(u, x) = \mathrm{dist}(p, x) = \mathrm{dist}(p, u) = \frac{k}{2} \Rightarrow \mathrm{dist}(p, u) > \frac{k}{2}$，所以先走到 $p$ 再走到 $x$ 只会更劣，同理 $v, y$ 也能得出一样的结论。  

这里有一些小细节需要注意，为了避免小数距离，可以将 $k$ 乘一倍，在边之间塞虚点；如果往上跳的时候 $\mathrm{dist}\left(u, \mathrm{lca}(u, v)\right) < \frac{k}{2}$，相当于让 $v$ 往上面跳 $\mathrm{dist}(u, v) - \frac{k}{2}$ 步。  

---

