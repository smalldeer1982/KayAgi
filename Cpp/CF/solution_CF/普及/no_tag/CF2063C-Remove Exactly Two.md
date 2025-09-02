# Remove Exactly Two

## 题目描述

最近，小 John 从姑姑那里得到一棵树来装饰房屋。但显然，仅一棵树不足以装饰整个房屋。小 John 想到一个主意：或许可以通过移除树上的若干顶点，将其分割成多棵树？你有一棵包含 $n$ 个顶点的树 $^{\text{∗}}$，必须**恰好执行两次**以下操作：

- 选择一个顶点 $v$；
- 移除与 $v$ 相连的所有边，并删除该顶点 $v$。

请计算操作完成后连通分量的最大数量。

两个顶点 $x$ 和 $y$ 属于同一连通分量，当且仅当存在从 $x$ 到 $y$ 的路径。明确地，根据定义，包含 $0$ 个顶点的图有 $0$ 个连通分量 $^{\text{†}}$。

$^{\text{∗}}$ 树是一个无环的连通图。

$^{\text{†}}$ 但这样的图是否连通呢？


## 说明/提示

第一个测试用例中，两次删除顶点后图变为空。根据定义，包含 $0$ 个顶点的图的连通分量数量为 $0$，因此答案为 $0$。

第二个测试用例中，删除顶点 $1$ 和 $2$ 后，剩余 $2$ 个连通分量。由于无法得到 $3$ 个连通分量，答案为 $2$。

第三个测试用例中，删除顶点 $1$ 和 $5$ 后，得到 $4$ 个连通分量：$\{2,4\}$、$\{3\}$、$\{6\}$、$\{7\}$。可以证明无法得到 $5$ 个连通分量，因此答案为 $4$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
2
1 2
4
1 2
2 3
2 4
7
1 2
1 3
2 4
4 5
5 6
5 7```

### 输出

```
0
2
4```

# 题解

## 作者：_huangweiliang_ (赞：23)

#### 前言
提供一个不需要分讨的 $O(Tn \log n)$ 做法。

#### 解题思路
首先会想到选出度数最大和次大的两个点删除。

但是注意到，有三个度数都为最大的点连在一起的时候，你不能先删中间的点。（可以随便举个例子手玩一下。）

这时有人就开始思考 dp 或者 分类讨论 了。

~~这时候想我这种没有思维的人就开始发力了。~~

假设要删的点为 $x$ 和 $y$，并且先删 $x$ 点。

直接暴力枚举每个点作为 $x$，并更新与之有连边的点的度数，再从剩下的点中选出度数最大的点计算答案，所有情况取最大值即可。

具体实现可以使用 `std::multiset`。
#### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N];
vector<int> v[N];
void solve(){
    int n, ans = 0;
    cin >> n;
    for(int i = 1; i <= n; i++) a[i] = 0;
    for(int i = 1; i < n; i++){
        int x, y;
        cin >> x >> y;
        a[x]++, a[y]++;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    multiset<int> s;
    for(int i = 1; i <= n; i++) s.insert(a[i]);
    for(int i = 1; i <= n; i++){
        int sum = 1;
        s.erase(s.find(a[i]));
        for(int y : v[i]){
            s.erase(s.find(a[y]));
            s.insert(a[y] - 1);
        }
        sum += a[i] - 1;
        sum += *s.rbegin() - 1;
        for(int y : v[i]){
            s.erase(s.find(a[y] - 1));
            s.insert(a[y]);
        }
        s.insert(a[i]);
        ans = max(ans, sum);
    }
    cout << ans << endl;
    for(int i = 1; i <= n; i++) v[i].clear();
}
int main(){
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：cjh20090318 (赞：7)

~~好吧我承认我是来水社区贡献的。~~

一道比较简单的题，年级里竟然还有同学无法战胜。

## 题意

你有一棵 $n$ 个点的树，你需要执行以下操作刚好两次：

- 选择一个点 $v$。
- 断开和 $v$ 相连的所有边，并删除点 $v$。

求经过操作后最多会有多少个连通块。

## 分析

考虑直接枚举每一个点，只需要找到另一个点断开以后能获得最大值。

这个断开的点会对它的子结点带来影响，度数减少了 $1$。

于是直接维护一个 `std::multiset`，暴力插入删除。

每条边只会被访问两次，所以时间复杂度 $O(n \log n)$。

虽然跑的很慢，效率不高，但是避免了分类讨论，编程复杂度相对较低。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
#define MAXN 200002
using namespace std;
int n;
vector<int> G[MAXN];
multiset<int> S;
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) G[i].clear();
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	S.clear();
	for(int i=1;i<=n;i++) S.insert(G[i].size());
	int ans=0;
	for(int i=1;i<=n;i++){
		S.erase(S.find(G[i].size()));//删去当前点。
		for(const int v:G[i]) S.erase(S.find(G[v].size())),S.insert(G[v].size()-1);
		ans=max(ans,(int)G[i].size()+*S.rbegin()-1);//取最大值。
		S.insert(G[i].size());
		for(const int v:G[i]) S.erase(S.find(G[v].size()-1)),S.insert(G[v].size());//撤销更改。
	}
	printf("%d\n",ans);
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：szh_AK_all (赞：6)

首先，假设一个点的度数为 $d$，那么若选择将它删去，则会多产生 $d-1$ 个连通块，所以这告诉我们可以贪心的删两个点，使得连通块个数尽可能多。

所以应当将所有点按照度数从大到小的顺序排序，然后再取度数最大的两个点，但是这样真的是对的吗？

假设当前有三个点的度数都为 $x$，并且 $x$ 是所有度数中最大的度数，那么从三个点中要选出两个点，并不是可以随便选的。假设第一次选择了 $u$，第二次选择了 $v$，如果 $u$ 和 $v$ 在原树上是相连的话，那么 $v$ 的度数实际上还得减一。

这告诉我们在取度数最大的两个点的同时，还得考虑选取的点是否相连的问题，于是就有了我赛时的答辩分讨。

- 若有超过三个点的度数都为最大的 $x$，那么答案为 $1+x-1+x-1=2x-1$，因为在这三个点中，一定能选出两个不相连的点（否则这就是一个连通分量了）。

- 若有两个点的度数都为最大的 $x$，且这两个点不相连，那么答案也为 $2x-1$。

- 若有两个点的度数都为最大的 $x$，且这两个点相连，那么答案为 $1+x-1+x-1-1=2x-2$，因为无论是选两个最大度数的点，还是选一个度数最大的点和另一个度数次大且不与度数最大的那个点相连的点，答案都为 $2x-2$。

- 若只有一个点的度数为最大的 $x$，且在度数为次大的 $y$ 的点中，有某个点与 $x$ 不相连，那么答案为 $1+x-1+y-1=x+y-1$。

- 若只有一个点的度数为最大的 $x$，且所有度数为次大的 $y$ 的点都与 $x$ 相连，那么答案为 $1+x-1+y-1-1=x+y-2$，因为无论是选一个最大度数的点和一个度数次大的点，还是选一个度数最大的点和另一个度数第三大且不与度数最大的那个点相连的点，答案都为 $x+y-2$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[2000005];
vector<int>g[200005];
int du[200005];
int p[200005];
unordered_map<int, int>q[200005];

bool cmp(int x, int y) {
	return du[x] > du[y];
}

signed main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 1; i < n; i++) {
			int x, y;
			cin >> x >> y;
			g[x].push_back(y);
			g[y].push_back(x);
			q[x][y] = 1;
			q[y][x] = 1;
			du[x]++, du[y]++;
			p[i] = i;
		}
		p[n] = n;
		sort(p + 1, p + n + 1, cmp);
		if (n >= 3 && du[p[1]] == du[p[2]] && du[p[2]] == du[p[3]])
			cout << 1 + du[p[1]] - 1 + du[p[1]] - 1;
		else if (du[p[1]] == du[p[2]] && !q[p[1]][p[2]])
			cout << 1 + du[p[1]] - 1 + du[p[1]] - 1;
		else if (du[p[1]] == du[p[2]])
			cout << du[p[1]] - 1 + du[p[1]] - 1;
		else {
			int pp = 0;
			for (int i = 2; i <= n; i++)
				if (du[p[i]] == du[p[2]] && !q[p[1]][p[i]]) {
					pp = 1;
					break;
				}
			if (pp)
				cout << 1 + du[p[1]] - 1 + du[p[2]] - 1;
			else
				cout << du[p[1]] - 1 + du[p[2]] - 1;
		}
		cout << "\n";
		for (int i = 1; i <= n; i++)
			du[i] = 0, g[i].clear(), q[i].clear();
	}
}
```

---

## 作者：bryce (赞：5)

## 思路
显然第一想法是去掉度数最大的点，将相邻点的度数减一，再去掉度数次大的点，但这是个错误的想法。

因为如果有多个度数最大且一样的点那么，删掉不同度数最大的点后面次大的点的度数会不同。

赛时吃罚时找到了一个数据：
```
1
8
1 2
1 3
1 4
2 5
2 6
3 7
3 8
```
大家可以手模以下，发现 $1$，$2$，$3$ 号点的度数都一样，但是删掉 $2$，$3$ 号点能形成 $5$ 个连通块，而删掉 $1$，$2$ 只能形成 $4$ 个连通块。

于是我们又有一个想法，枚举最大度数一样的点，将与它相邻的点的度数全部减一，求剩下度数最大的点的度数，显然这个可以用线段树维护。

由于所有最大度数的点的度数和是 $O(n)$ 级别的，所以总时间复杂度为 $O(n\log n)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 2e5 + 10;
int T, n, ans;
int in[N];
struct edge{
    int v, nxt;
}e[N << 1];
int head[N], cnt;
void add(int u, int v){
    e[++cnt] = (edge){v, head[u]};
    head[u] = cnt;
}
int pos, maxn;
vector<int> d;
int t[N << 2];
void build(int now, int l, int r){
    if (l == r){
        t[now] = in[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(now << 1, l, mid);
    build(now << 1 | 1, mid + 1, r);
    t[now] = max(t[now << 1], t[now << 1 | 1]);
}
void modify(int now, int l, int r, int x, int k){
    if (l == r){
        t[now] += k;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) modify(now << 1, l, mid, x, k);
    else modify(now << 1 | 1, mid + 1, r, x, k);
    t[now] = max(t[now << 1], t[now << 1 | 1]);
}

signed main(){
    T = read();
    while (T--){
        n = read(), ans = 0;
        for (int i = 1; i < n; i++){
            int u = read(), v = read();
            in[u]++, in[v]++;
            add(u, v), add(v, u);
        }
        maxn = 0;
        build(1, 1, n);
        for (int i = 1; i <= n; i++)
            if (in[i] >= maxn) pos = i, maxn = in[i];
        for (int i = 1; i <= n; i++) if (in[i] == maxn) d.emplace_back(i);
        int mx = 0;
        for (auto u : d){
            for (int i = head[u]; i; i = e[i].nxt){
                int v = e[i].v;
                modify(1, 1, n, v, -1), modify(1, 1, n, u, -1);
            }
            if (t[1] >= mx) pos = u, mx = t[1];
            for (int i = head[u]; i; i = e[i].nxt){
                int v = e[i].v;
                modify(1, 1, n, v, 1), modify(1, 1, n, u, 1);
            }
        }
        cout << maxn + mx - 1 << '\n';
        d.clear();
        for (int i = 1; i <= n; i++) head[i] = in[i] = 0;
        for (int i = 1; i <= cnt; i++) e[i].v = 0, e[i].nxt = 0;
        cnt = 0;
    }
    return 0;
}
```

---

## 作者：TainityAnle (赞：3)

### 题意

给定一棵树，删掉两个节点，问最多变成几棵树。

### 思路

因为是一棵树，所以删掉的点 $x$ 度数为 $d_x$，那么 $x$ 所在的这棵树就会从 $1$ 棵树变成 $d_x$ 棵树。相当于增加了 $d_x-1$ 棵树。

所以可以想到一个很简单的贪心做法，先删度最大的点 $id$，答案加上 $d_{id}$，把与 $id$ 相连的点度数都减一。再选当前度最大的点即可。

但是这样是错误的。

有这样一棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/09nni0ms.png)

点 $1,5,8$ 的度数都为 $4$，但如果删 $5$ 和 $1$ 或 $8$，会剩下 $6$ 棵树；但若删 $1$ 和 $8$，会剩下 $7$ 棵树，要是按照上面的策略，我们无法确定删哪个。

如何避免这个问题呢，把所有度最多的点记一下，如果在与一个点相连的点中，度数最多的点的数量大于等于 $2$，那么就不行，因为这样第二次就有可能选到与它相邻的度数最多的点。如果与它相连的点中度数最多的点的数量小于等于 $1$，那么就认为可以删它。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,u,v,d[N],maxx,id,ans,vis[N];
vector<int> to[N];
int main() {
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--) {
		maxx=0,ans=0;
		for(int i=1; i<=n; i++) vis[i]=0,to[i].clear(),d[i]=0;
		cin>>n;
		for(int i=1; i<n; i++) {
			cin>>u>>v;
			to[u].push_back(v);
			to[v].push_back(u);
			d[u]++,d[v]++;
		}
		vector<int> m1;
		for(int i=1; i<=n; i++) {
			if(d[i]>maxx) {
				maxx=d[i];
			}
		}
		for(int i=1;i<=n;i++){
			if(d[i]==maxx){
				m1.push_back(i);
				vis[i]=1;
			}
		}
		for(auto x:m1){
			int tmp=0;
			for(auto y:to[x]){
				tmp+=vis[y];
			}
			if(tmp<=1){
				id=x;
				break;
			}
		}
		ans+=d[id];
		for(auto y:to[id]) d[y]--;
		d[id]=0;
		maxx=0;
		for(int i=1; i<=n; i++) if(d[i]>maxx) maxx=d[i],id=i;
		ans+=d[id];
		cout<<ans-1<<endl;
	}
	return 0;
}
```

---

## 作者：boluo2014 (赞：2)

还是一道挺有意思的题目。

### 思路

首先，我一看这一题，以为是大水题。因为好像直接记录每一个顶点的子节点个数，然后找到最大的节点和次最大的节点就可以了。

然后我模拟了样例，错了。

于是我画了图，发现这还得分类讨论！不过，我们设删去的第一个节点的子结点个数为 $a$，第二个为 $b$。

当然，$n=2$ 可以直接输出 $0$。

第一种情况：删去的两个节点毫无关系，也就是它们的层数的差的绝对值 $ \ge 2$，换句话说，就是它们并没有父子关系也没有同父亲的关系。这种情况下，最终数量就是 $(a+b)$ 个。

第二种情况：删去的两个点存在父子关系，如果存在父子关系，那么父亲的那个节点的儿子个数就会减少 $1$，故答案也减少 $1$，数量是 $(a+b-1)$。

第三种情况：存在同一个父亲的关系，也就是它们的层数相同，那么会发现，父亲节点会多“分裂”出一片东西，所以答案需要 $+1$。也就是 $(a+b+1)$。

备注：这三个情况画图就可以理解了。当然，代码模拟起来稍微有点长。

### 模拟

首先，$n=2$ 可以直接特判输出 $0$。

最好的情况肯定是 $(a+b+1)$，我们直接枚举同层的最大加次最大的和。也就是不断迭代更新，求出最大和次最大（可能相等）的和再 $+1$ 的最大值。（需要每一层都遍历），然后记录下这个数据 $t$。

假设找到的最大为 $mx$，次最大为 $smx$。

然后，就是去找最大的个数有几个。如果不止 $1$ 个，那么很简单，看看有没有不是父子关系，如果没有，直接输出 $2 \times mx -1$ 和 $t$ 中较大的即可，有不是父子关系的更好，输出 $2 \times mx$ 即可（不用和 $t$ 比较了）。如果刚好只有 $1$ 个，那就找次最大，看看是不是同层、父子或者没关系，计算出来就可以了。

代码不给了，稍微有点长，怕浪费洛谷空间。

就这样，输出完成了。比较简单。

---

## 作者：hytallenxu (赞：2)

## 前言
CF 好题。

## 正文
题意：有一个无根树，移除 $2$ 点之后联通分量的个数最大是多少。

以下皆钦定**度数**为入度和出度的和。

设节点 $u$ 的度数为 $\text{deg}_u$，我们对依次移除的 $2$ 点 $i,j$ 进行分类讨论。

1. 若 $i,j$ 不相邻：

   断开 $i$ 点，树显然会变成有 $\text{deg}_i$ 个连通分量的图。

   断开 $j$ 点，会再多出 $\text{deg}_j-1$ 个联通分量。为什么呢？因为在刚刚断开的 $\text{deg}_i$ 个分量里面必有 $1$ 个包含 $j$ （也包含其他的节点），断开 $j$ 不会影响这一个连通分量，因此会少多出来 $1$ 个连通分量。

   答案为 $\text{deg}_i+\text{deg}_j-1$。

2. 若 $i,j$ 相邻：

   与 (1) 同样的逻辑，断开 $i$ 点，树还是会变成有 $\text{deg}_i$ 个连通分量的图。

   但是，断开 $j$ 点，我们会比刚刚**再**少多出来一个连通分量，因为**移除 $i$ 点的同时 $j$ 点的度数也 $-1$ 了**。

   答案为 $\text{deg}_i+\text{deg}_j-2$。

问题来了，那怎么实现呢？

具体的，我们枚举点 $i$，然后根据上面的找出最大的满足条件的点 $j$。

注意到我们需要一个能实时排序，插入和移除的数据结构，我这里用的是 `std::set` 和 `std::multiset`。

具体实现细节看代码。

## Code
时间复杂度显然为 $\Theta(n \log n)$。
```cpp
#include <bits/stdc++.h>
#ifdef LOCAL
	#include "debug.h"
#else
	#define debug(...) 42
#endif
#define mkp make_pair
#define pb emplace_back
#define endl "\n"
using namespace std;
using ll = long long;
int n,m,t,cnt=0;
const int maxn=2e5+10;
const double eps=1e-6;

int deg[maxn];
vector<int> e[maxn];
void solve(){
	int ans=0;
	cin>>n;
	fill(deg+1,deg+1+n,0);
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1;i<=n-1;i++){
		int u,v;cin>>u>>v;
		deg[u]++,deg[v]++;
		e[u].pb(v);
		e[v].pb(u);
	}
	set<pair<int,int>> st;
	for(int i=1;i<=n;i++) st.insert(mkp(deg[i],i));
	for(int i=1;i<=n;i++){
		multiset<int> mt;
		st.erase(mkp(deg[i],i));
		for(int v:e[i]){mt.insert(deg[v]);st.erase(mkp(deg[v],v));}
		int case2=deg[i]+*prev(mt.end())-2;
		if(st.size()){
			int case1=deg[i]+(*prev(st.end())).first-1;
			ans=max({ans,case1,case2});
		}else{ans=max({ans,case2});}
		st.insert(mkp(deg[i],i));
		for(int v:e[i])	st.insert(mkp(deg[v],v));
	}
	cout<<ans<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：AtomAlpaca (赞：1)

大家好我不是很有脑子，所以我用 dp 过了这道题

## 题意

给出一棵树，求删除两个点及其相连的边后最多能产生多少个联通块

$n \le 2 \cdot 10^5$


## 题解
不妨设 $f_{u, \{1, 2\}, \{0, 1\}}$ 是 $u$ 这个节点子树内删除 $1, 2$ 个节点，其中自己不删除/删除所形成的最多的联通块数量。我们依次考虑这四种情况。下面设 $s_u$ 是 $u$ 的儿子组成的集合。

首先 $f_{u, 1, 0}$ 只能从子树内找一个删掉。注意如果删掉的是儿子节点，那么 $u$ 和其余的儿子及其子树会额外形成一个联通块。即 $f_{u, 1, 0} = \max_{v\in s_u)} \max (f_{v, 1, 0}, f_{v, 1, 1} + 1)$。

$f_{u, 1, 1} = |s_u|$，这是显然的。 

$f_{u, 2, 0}$ 略微复杂，要么是一个儿子的子树内删掉两个（如果有两个节点），要么两个子树分别删掉一个（如果有两个子树）。前者和 $f_{u, 1, 0}$ 类似地更新，后者我们维护 $\forall v \in s_u, f_{v,  1, 0} - 1, f_{v, 1, 1}$ 中前两大 $m_1, m_2$，则 $f_{u, 2, 0} = m_1 + m_2 + 1$。

$f_{u, 2, 1}$ 和 $f_{u, 1, 1}$ 类似地，只是其中一个子树也被删除了节点，我们可以想象其删掉了一个联通块又加上若干个，故 $f_{u, 2, 1} = |s_u| - 1 + \max_{v \in s_u} \max (f_{v, 1, 0}, f_{v, 1, 1})$。

总复杂度 $O(n)$，优于官方题解。

具体过程难以用语言描述，建议参考代码理解。

## 代码
```cpp
#include <bits/stdc++.h>

const int MAX = 1e6 + 5;
typedef long long ll;
const ll INF = 1e16 + 5;

inline ll max(ll a, ll b) { return a > b ? a : b; }

ll T, n, l, r, ans, tot, u, v;
ll a[MAX], h[MAX], g[MAX], s[MAX];
ll f[MAX][3][2];

struct E { ll v, x; } e[MAX];

void add(ll u, ll v)
{
    e[++tot] = { v, h[u] }; h[u] = tot;
    e[++tot] = { u, h[v] }; h[v] = tot;
}

void upd(ll & m1, ll & m2, ll a)
{
    if (a > m1) { m2 = m1; m1 = a; }
    else if (a > m2) { m2 = a; }
}

void dfs(ll u, ll fa)
{
    ll c = 0, m1 = 0, m2 = 0, mx = 0;
    for (int i = h[u]; i; i = e[i].x)
    {
        ll v = e[i].v; if (v == fa) { continue; }
        dfs(v, u); ++c;
        f[u][1][0] = max(f[u][1][0], f[v][1][0]); f[u][1][0] = max(f[u][1][0], f[v][1][1] + 1);
        if (g[v]) { f[u][2][0] = max(f[u][2][0], f[v][2][0]); f[u][2][0] = max(f[u][2][0], f[v][2][1] + 1); }
        upd(m1, m2, max(f[v][1][0] - 1, f[v][1][1]));
        mx = max(mx, f[v][1][0]); mx = max(mx, f[v][1][1]);
    }
    f[u][1][1] = c;
    if (!c) { g[u] = 0; }
    else
    {
        g[u] = 1;
        if (c >= 2) { f[u][2][0] = max(f[u][2][0], m1 + m2 + 1); }
        f[u][2][1] = c + mx - 1;
    }
}

void solve()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) { h[i] = g[i] = f[i][1][0] = f[i][1][1] = f[i][2][0] = f[i][2][1] = 0;  }
    for (int i = 1; i <  n; ++i) { scanf("%lld%lld", &u, &v); add(u, v); }
    if (n == 2) { printf("0\n"); return ; }
    dfs(1, 0);
    printf("%lld\n", max(f[1][2][0], f[1][2][1]));
}

int main() { scanf("%lld", &T); while (T--) { solve(); } }
```

## 后记
> Sure, you can do DP on tree, but that's not what we want you to use. Think easier.

---

## 作者：_anll_ (赞：1)

## 思路
刚开始想的是自己写假的贪心，上去罚了一发后突发奇想能不能用树形 dp。

我们规定 $siz_x$ 表示当前 $x$ 连接的节点个数，那么有一个很一眼的结论就是对于一个先前联通的树而言，删除 $x$ 这个节点会使本树变为 $siz_x$ 个连通块。不妨令 $dp[x][1/2]$ 表示在 $x$ 的子树内（含 $x$）选了 $1$ 或 $2$ 个点进行删除后**对当前子树的贡献**。$dp[x][1]$ 很简单，一定会从所有 $dp[l][1]$ 和 $siz_x-1$ 中取最大，其中减一的原因是我们不考虑连父亲的那一块。 

考虑 $dp[x][2]$ 怎么处理。首先，它一定能从 $dp[l][2]$ 继承过来；其次，我们可以在 $x$ 的子树内选择除了 $x$ 以外的两个儿子节点，用它们 $dp[l][1]$ 的和进行更新，这是因为它们被删除不会影响到彼此，这里我们贪心地去取最大值和次大值即可。

我们再考虑必须选择 $x$ 的情况，这里也要分两种情况讨论：如果被选中的点为儿子节点，那就会导致 $siz_x$ 减少一；反之不会有任何影响。我们可以让 dfs 函数带一个返回值，具体地，我们提前处理，即将所有 $dp[l][1]$ 和 $siz_x-2$ 取最大值返回。

最后的答案就是 $dp[rt][2]$，我一般钦定 $rt$ 为 $1$。但注意我们最后图上至多只会剩下 $n-2$ 个连通块，所以答案要和 $n-2$ 取小。

## 代码
赛时代码稍微美化了一下，将就看好了。
```cpp
#include<vector>
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n,siz[N],dp[N][3];
vector<int> edges[N];
int dfs(int x,int fa){
	int maxn=0,caxn=0,maxa=0,siz=edges[x].size();
	for(auto l:edges[x]){
		if(l==fa) continue;
		maxa=max(maxa,dfs(l,x));
		dp[x][1]=max(dp[l][1],dp[x][1]);
		dp[x][2]=max(dp[l][2],dp[x][2]);
		if(maxn<dp[l][1]) caxn=maxn,maxn=dp[l][1];
		else if(caxn<dp[l][1]) caxn=dp[l][1];
	}
	dp[x][2]=max(dp[x][2],max(maxn+caxn+1,siz+maxa));
	int an=max(dp[x][1],siz-2);
	dp[x][1]=max(dp[x][1],siz-1);
	return an;
}
void solve(){
	cin>>n;int f,l,rt=1;
	for(int i=1;i<=n;i++)
		edges[i].clear(),
		dp[i][1]=dp[i][2]=0;
	for(int i=1;i<n;i++){
		cin>>f>>l;
		edges[f].push_back(l);
		edges[l].push_back(f);
	}
	dfs(1,0);cout<<min(n-2,dp[1][2])<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
} 
```

---

## 作者：ran_qwq (赞：1)

如果是执行一次，树会被分成 $\max d_u$ 块。

枚举第一次删除的点 $u$，现在把 $u$ 相邻的 $v$ 度数减去 $1$，再转化为执行一次的情况，答案为 $d_u+d_v-1$。为什么要 $-1$ 呢？因为 $u$ 和 $v$ 中间的一段被算了两遍。

可以用 multiset 维护，删除 $d_v$，加入 $d_v-1$。操作完之后撤销回去即可。

赛时代码中实现与描述中略有不同，较为复杂，维护了相邻点和其他点的 multiset。

```cpp
int n,id,as,hd[N],d[N]; multiset<int> st;
struct EDGE {int to,ne;} e[N*2];
il void add(int u,int v) {e[++id]={v,hd[u]},hd[u]=id,d[u]++;}
void QwQ() {
	n=rd(),id=as=0;
	for(int i=1;i<=n;i++) hd[i]=d[i]=0; st.clear();
	for(int i=1,u,v;i<n;i++) u=rd(),v=rd(),add(u,v),add(v,u);
	for(int i=1;i<=n;i++) st.insert(d[i]);
	for(int u=1;u<=n;u++) {
		multiset<int> tmp; st.erase(st.find(d[u]));
//		wr(st.size(),"\n");
		for(int i=hd[u];i;i=e[i].ne) st.erase(st.find(d[e[i].to])),tmp.insert(d[e[i].to]);
		cmax(as,max(st.size()?d[u]+*st.rbegin()-1:-INF,d[u]+*tmp.rbegin()-2));
		for(int i=hd[u];i;i=e[i].ne) st.insert(d[e[i].to]);
		st.insert(d[u]);
	}
	wr(as,"\n");
}
```

---

## 作者：Rannio (赞：1)

好玩，赛时吃了六发罚时。

### 题意

给定一棵树，求删掉两个点及它们所连接的边后最多能形成多少个连通块。

### 思路

赛时先吃了四发罚时，发现随便选两个连接边数最多的点删掉是错的，随便整条链就 hack 掉了。

既然随便选两个点不行，那我们就先随便选一个连边最多的点，将与它相连的边删掉后再选择当前连边最多的点，统计完答案后再把边连回来，这样就避免了上一个策略中删掉的两个点有可能是邻接点的问题。

在这个策略中，每条边最多被删两次，所以时间复杂度为 $O(n \log n)$。

代码使用 `set` 实现，便于删边后再连回来。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m,k;
int a[500005],sum[200005];
int head[400005],cnt=1;
struct node{
    int to,next;
}edge[400005];
set<pair<int,int> > st;
void add(int x,int y){
    edge[cnt].to=y;
    edge[cnt].next=head[x];
    head[x]=cnt++;
}
int get(int x){
    st.erase({sum[x],x});
    for(int i=head[x];i;i=edge[i].next){
        int u=edge[i].to;
        st.erase(st.find({sum[u],u}));
        sum[u]--;
        st.insert({sum[u],u});
    }
    int res=sum[x]+(*(--st.end())).first-1;
    for(int i=head[x];i;i=edge[i].next){
        int u=edge[i].to;
        st.erase(st.find({sum[u],u}));
        sum[u]++;
        st.insert({sum[u],u});
    }
    st.insert({sum[x],x});
    // cout<<res<<endl;
    return res;
}
void init(){
    for(int i=1;i<=n;i++){
        sum[i]=0;
    }
    for(int i=1;i<=cnt;i++){
        head[i]=0;
        edge[i].to=edge[i].next=0;
    }
    cnt=1;
    st.clear();
}
signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        for(int i=1;i<n;i++){
            int x,y;
            scanf("%lld%lld",&x,&y);
            add(x,y);
            add(y,x);
            sum[x]++,sum[y]++;
        }
        for(int i=1;i<=n;i++) st.insert({sum[i],i});
        int res=0,mx=(*(--st.end())).first;
        // cout<<mx<<endl;
        for(int i=1;i<=n;i++){
            if(sum[i]==mx){
                res=max(res,get(i));
            }
        }
        printf("%lld\n",res);
        init();
    }
    return 0;
}
```

---

## 作者：XCDRF_ (赞：0)

# CF2063C Remove Exactly Two

[原题传送门](https://codeforces.com/problemset/problem/2063/C)

[更好的阅读体验](https://www.luogu.com.cn/article/8fu7f440)

## 题目大意

给定一颗 $n$ 个点的树，求删掉两个点以及它们所连的边后，连通分量个数的最大值。

## 解题思路

看到题目后，首先能得到一个很显然的结论。设 $i$ 号点的度数为 $d_i$，选 $i$ 号和 $j$ 号点删掉：
- 若两点不相邻，答案为 $d_i+d_j-1$。
- 若两点相邻，答案为 $d_i+d_j-2$，因为这两点之间的边只能被删掉一次。

暴力枚举两个点，时间复杂度 $O(n^2)$，无法通过此题。

从贪心的角度优化，选度数大的点肯定比选度数小的点要优。所以只需要第一次选一个度数最大的点，然后删一次边，再在删完边的图上找一次度数最大的点即可。

不过可能会遇到选的两个度数最大的点相邻，但还有不相邻的最大点的情况。例如一个五个点构成的链，如果删中间的点，必定会导致答案少 $1$，因为选的两个点只能相邻。

此时，我们可以从度数最大的点中任意找两个点，分别求一次答案，输出二者间的最大值即可。为什么？设这两个点分别为 $u$ 和 $v$，删完边后的最大值点为 $w$。$u$，$v$，$w$ 三点中至少有两个不相邻，否则就形成了环。所以任意找两个点计算答案一定能找到不相邻的情况，也就是最大值。

这样做时间复杂度为 $O(n)$，可以通过。

## 参考代码
```cpp
#include<iostream>
using namespace std;
const int N=2e5+5;
int t,n,x,y,tot,maxx,maxxx,ans,cnt;
int deg[N],head[N],maxn[N];
bool vis[N];
struct Edge{
	int nxt,to;
}edge[N<<1];
void add(int x,int y){
	edge[++tot]={head[x],y};
	head[x]=tot;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
   	cin>>t;
   	while(t--){
   		tot=0,maxx=0,cnt=0;
   		cin>>n;
   		if(n==2){
   			cout<<0<<'\n';
   			cin>>x>>y;
   			continue;
		}
   		for(int i=1;i<n;i++){
   			cin>>x>>y;
   			add(x,y);
   			add(y,x);
   			deg[x]++;
   			deg[y]++;
		}
		for(int i=1;i<=n;i++){
			if(deg[i]>maxx){
				cnt=0;
				maxx=deg[i];
				maxn[++cnt]=i;
			}
			else if(deg[i]==maxx){
				maxn[++cnt]=i;
			}
		}
		ans=0;
		for(int x=1;x<=min(2,cnt);x++){
			int cnt2=0;
			for(int i=head[maxn[x]];i;i=edge[i].nxt){
				int xx=edge[i].to;
				deg[xx]--;
			}
			deg[maxn[x]]=0;
			maxxx=0;
			for(int i=1;i<=n;i++)
				if(deg[i]>maxxx) maxxx=deg[i];
			ans=max(ans,maxx+maxxx-1);
			for(int i=head[maxn[x]];i;i=edge[i].nxt){
				int xx=edge[i].to;
				deg[xx]++;
			}
			deg[maxn[x]]=maxx;
		}
		cout<<ans<<'\n';
		for(int i=1;i<=n;i++) deg[i]=0,head[i]=0;
	}
	return 0;
}
```

[AC 记录](https://codeforces.com/contest/2063/submission/302534280)

---

## 作者：SpringFullGarden (赞：0)

## 题意

给定一棵树，求删去两个节点后连通块的最大数量。

## 思路

贪心地想，容易想到要删去度数最大和次大的两个节点。

设要删去的两节点为 $u, v$，度数为 $d_u, d_v$。

观察发现，$u, v$ 相邻，则对答案的贡献 $d_u + d_v - 2$，否则对答案的贡献为 $d_u + d_v - 1$。

接下来进行分类讨论：

1. 若度数为最大值的点只有一个，那么枚举度数为次大值的点，看两点是否相邻；
2. 若度数为最大值的点只有两个，那么看这两点是否相邻；
3. 若度数为最大值的点超过两个，那么一定存在两个点不相邻。

## 代码

```cpp
vector <int> e[200005];
ll fa[200005], s[200005], t[200005], mx, mn;

void dfs(ll x) {
    for(ll v : e[x]) {
        if(v == fa[x]) continue;
        fa[v] = x, dfs(v);
    }
    if(e[x].size() > e[mx].size()) mn = mx, mx = x;
    else if(e[x].size() > e[mn].size()) mn = x;
}
signed main() {
    for(ll T = rd(); T--; ) {
        ll n = rd(), cnt = 0, ans = 0;
        mx = mn = 0;
        for(ll i = 1; i <= n; i++) e[i].clear(), t[i] = 0;
        for(ll i = 1, u, v; i < n; i++) 
            u = rd(), v = rd(), e[u].push_back(v), e[v].push_back(u);
        dfs(1);
        for(ll i = 1; i <= n; i++) if(e[i].size() == e[mx].size())
            s[++cnt] = i;
        if(cnt == 1) {
            for(ll i = 1; i <= n; i++)
                if(e[i].size() == e[mn].size()) {
                    if(fa[i] == mx || fa[mx] == i) 
                        ans = max(ans, (ll)e[i].size() + (ll)e[mx].size() - 2ll);
                    else 
                        ans = max(ans, (ll)e[i].size() + (ll)e[mx].size() - 1ll);
                }
        } else if(cnt == 2) {
            if(fa[s[1]] == s[2] || fa[s[2]] == s[1]) 
                ans = max(ans, 2 * (ll)e[mx].size() - 2ll);
            else 
                ans = max(ans, 2 * (ll)e[mx].size() - 1ll);
        } else ans = max(ans, 2ll * (ll)e[mx].size() - 1ll);
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Colinxu2020 (赞：0)

给出一个完全不需要分讨的做法。

先考虑恰好删除一个点的情况，容易发现，因为这是一个树，当我们删除某一个点 $x$ 之后，所有和 $x$ 有连边的点都处于不同的连通块，因此可以得到 $\deg x$ 个连通块，答案为 $\max \deg x$，但对于删两次来说这是错的。

考虑枚举删去的第一个点是哪个点，记这个点为 $x$，记删去这个点后第 $i$ 个点的度数为 $\deg' i$，令原树 $G=(V,E)$，可以发现 $\forall_{(x,i) \in E},\deg' i=\deg i - 1\forall_{(x_i) \notin E},deg'_i=deg_i$，因为上面的贪心对于删除一个点是正确的，所以对于第二个点直接跑上面的贪心。不妨把所有的 $(\deg_i,i)$ 扔到一个 `set` 里，我们在 `set` 里暴力找到最小的和 $x$ 没有连边的点的度数 $a$ 和全局度数最小的点的度数 $b$，答案为 $\deg x+\max(a,b-1)-1$（$-1$ 的原因是某一个连通块会被算两次），注意特判所有点都和 $x$ 有连边的情况即可，然后不要把 $x$ 自己也算在里面（可以在最开始删掉，最后加回去）。因为每条边最多被跳过两次，复杂度为 $\Theta(n \log n)$。

参考代码：

```cpp
#include<iostream>
#include<set>
using namespace std;

const int maxn=2e5+10;
int n;
set<int> grp[maxn];
set<pair<int,int>> se;

int main(){
    int T; cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<n;i++){
            int u,v; cin>>u>>v;
            grp[u].insert(v);
            grp[v].insert(u);
        }
        for(int i=1;i<=n;i++)se.insert({-(signed)grp[i].size(),i});
        int ans=0;
        for(int i=1;i<=n;i++){
            se.erase({-(signed)grp[i].size(),i});
            auto it=se.begin();
            while(it!=se.end()&&grp[i].count(it->second))it++;
            int cur=-(se.begin()->first)-1;
            if(it!=se.end())cur=max(cur,-(it->first));
            ans=max(ans,(signed)grp[i].size()+cur-1);
            se.insert({-(signed)grp[i].size(),i});
        }
        cout<<ans<<endl;
        se.clear();
        for(int i=1;i<=n;i++)grp[i].clear();
    }
}
```

---

