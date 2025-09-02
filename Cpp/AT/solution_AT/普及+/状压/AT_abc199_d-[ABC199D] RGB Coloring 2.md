# [ABC199D] RGB Coloring 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc199/tasks/abc199_d

$ N $ 頂点 $ M $ 辺の単純無向グラフがあります。頂点には $ 1 $ から $ N $ までの、辺には $ 1 $ から $ M $ までの番号がついています。  
 辺 $ i $ は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます。  
 このグラフの各頂点を赤、緑、青の $ 3 $ 色のいずれかで塗る方法であって、以下の条件を満たすものの数を求めてください。

- 辺で直接結ばれている $ 2 $ 頂点は必ず異なる色で塗られている

なお、使われない色があっても構いません。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 20 $
- $ 0\ \le\ M\ \le\ \frac{N(N\ -\ 1)}{2} $
- $ 1\ \le\ A_i\ \le\ N $
- $ 1\ \le\ B_i\ \le\ N $
- 与えられるグラフは単純 (多重辺や自己ループを含まない)

### Sample Explanation 1

頂点 $ 1,\ 2,\ 3 $ の色をそれぞれ $ c_1,\ c_2,\ c_3 $ とし、赤、緑、青をそれぞれ `R`, `G`, `B` で表すと、以下の $ 6 $ 通りが条件を満たします。 - $ c_1c_2c_3\ = $ `RGB` - $ c_1c_2c_3\ = $ `RBG` - $ c_1c_2c_3\ = $ `GRB` - $ c_1c_2c_3\ = $ `GBR` - $ c_1c_2c_3\ = $ `BRG` - $ c_1c_2c_3\ = $ `BGR`

### Sample Explanation 2

辺がないため、各頂点の色を自由に決めることができます。

### Sample Explanation 3

条件を満たす塗り方が存在しない場合もあります。

### Sample Explanation 4

答えは $ 32 $ ビット符号付き整数型に収まらないことがあります。

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1```

### 输出

```
6```

## 样例 #2

### 输入

```
3 0```

### 输出

```
27```

## 样例 #3

### 输入

```
4 6
1 2
2 3
3 4
2 4
1 3
1 4```

### 输出

```
0```

## 样例 #4

### 输入

```
20 0```

### 输出

```
3486784401```

# 题解

## 作者：suzhikz (赞：3)

## 前言：
这题是学校模拟赛出的题，开始的时候没有头绪，后来在讲评之后也是恍然大悟了。临近 noip，写篇题解希望 rp++，预祝大家考的都会。
## 思路：
这题一看数据量就知道肯定是爆搜或者状压了，但是显然不满足无后效性（还是我太蒻了？），所以直接写爆搜。将图分为几个连通互相没有边的图，分开处理，最后答案相乘即可。
## 易错
爆搜相信大家都会，我在下面写一些易错点：
1. 这个图不一定是树，当图中有环时，需要标记，否则答案就会加两遍（or 更多），样例一就是这种情况。
2. 一个点的颜色需要先与父亲判断，重复就要跳过，否则计算量过大，喜提 TLE。
3. 记得开 long long，否则样例 4 就可以卡掉。
## code
```cpp
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdio>
#include<string>
#include<deque>
#include<stack>
#include<queue>
#include<vector>
#include<stdio.h>
//#include<map>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<bitset>
using namespace std;
int n,m;
vector<int> w[25];//图
long long ans[25],tot;//答案
bool vis[25];//是否搜过
int huan[25][25];//有没有环
int c[25];
int work(int x,int fa){
	int an=0;
	vis[x]=1;
	if(c[x]){//重复搜到肯定是因为有环。
		huan[x][fa]=1;//这个环肯定包括这个点和他的两个儿子，一个儿子搜过了，只需要再特判另一个即可。
		return c[x]!=c[fa];
	}
	for(int i=1;i<=3;i++){
		if(i==c[fa])continue;//易错点2。
		c[x]=i;
		int book=1;
		memset(huan[x],0,sizeof(huan[x])); //初始化也是易错。
		for(int j=0;j<w[x].size();j++){
			int v=w[x][j];
			if(!huan[x][v])book*=work(v,x);//没有环或环还没搜。
		}
		c[x]=0;
		an+=book;
	}
	return an;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		w[u].push_back(v);
		w[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=1;
			ans[++tot]=work(i,0);
		}
	}
	for(int i=2;i<=tot;i++)ans[i]*=ans[i-1];
	cout<<ans[tot];
	return 0;
}
```

---

## 作者：_Gabriel_ (赞：1)

### 思路

因为 $n$ 很小，可以考虑 `dfs` 暴力涂色。

直接枚举的复杂度为 $O(3^n)$，不能通过。

我们可以将图拆分为多个连通分块，单独计算每个分块的方案数，最终结果即为所有分块的方案数之积。

代码便是两个 `dfs` 函数，一个用于拆分连通块，一个用于计算分块的方案数。

### 代码


```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;
const int N = 2e5 + 10;
vector<int> G[30];
int vis[N], c[N];
int cnt;
vector<int> a;

void dfs1(int u) {
    a.push_back(u);
    vis[u] = 1;
    for (int v : G[u]) {
        if (vis[v]) continue;
        dfs1(v);
    }
}

void dfs2(int u) {
    if (u == a.size()) {
        cnt++;
        return;
    }
    int x = a[u];
    int flag[4] = {0};
    for (auto v : G[x]) flag[c[v]] = 1;
    for (int i = 1; i <= 3; i++) {
        if (flag[i]) continue;
        c[x] = i;
        dfs2(u + 1);
        c[x] = 0;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        a.clear();
		dfs1(i);
        cnt = 0;
		dfs2(0);
        ans = ans * cnt;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：sherry_lover (赞：0)

# AT_abc199_d [ABC199D] RGB Coloring 2 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc199_d)

## 思路

如果直接暴力枚举，复杂度是 $O(n^3)$ 的，考虑优化。

注意到如果一条边上的一个端点已经被染过色，则另一个端点只要枚举两种状态。所以我们对每个连通块单独拎出来枚举一遍，每个连通块第一个点枚举 $3$ 种颜色，其他点枚举 $2$ 中颜色，复杂度 $O(3 \times 2^{n-1})$。

容易发现，当 $m=0$ 时，整个算法将退化到 $O(3^n)$，依旧不能通过。

可以省去第一个枚举 $3$ 种颜色，直接从第二个枚举 $2$ 种颜色，最后答案乘三即可。时间复杂度还是 $O(2^n)$ 级别的。

代码就不贴了。

---

## 作者：Claire0918 (赞：0)

容易想到暴搜染色，但容易误以为时间复杂度为 $\mathcal{O}(3^n)$，无法通过。

实际上，对于一个大小为 $k$ 的连通块，其时间复杂度为 $\mathcal{O}(3 \times 2^{k - 1})$，所以总时间复杂度近似 $\mathcal{O}(2^n)$，可以稳定通过。

搜索时将每个连通块分开后暴力即可。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 20 + 10;

struct{
    int v, nex;
} edge[maxn * maxn];

int n, m;
long long res = 1, now;
int colour[maxn];
bool vis[maxn];
int head[maxn], top = 0;
vector<int> buf;

inline void add(int u, int v){
    edge[++top].v = v;
    edge[top].nex = head[u];
    head[u] = top;
}

inline void dfs1(int u){
    buf.push_back(u);
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        if (!vis[v]){
            dfs1(v);
        }
    }
}

inline void dfs2(int pos){
    if (pos == buf.size()){
        now++;
        return;
    }
    bool flag[4] = {0};
    const int u = buf[pos];
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        flag[colour[v]] = true;
    }
    for (int i = 1; i <= 3; i++){
        if (!flag[i]){
            colour[u] = i;
            dfs2(pos + 1);
            colour[u] = 0;
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            buf.clear();
            dfs1(i);
            now = 0;
            dfs2(0);
            res *= now;
        }
    }
    printf("%lld", res);

return 0;
}
```

---

## 作者：loser_seele (赞：0)

观察到 $ n $ 很小，考虑暴力涂色。

首先如果暴力枚举 $ 3^n $ 种颜色显然是难以通过的。

但观察到如果某个点的颜色确定了，那么和这个点相连的分量的所有点都最多只有两种颜色的取值。

因此可以找出图的所有连通分量，然后分别处理所有连通块，随便选一个点作为起点，枚举这个点的颜色，然后枚举所有方案即可，对于每个连通块这么做的时间复杂度是 $ 3 \times 2^{n-1} $，可以接受。

总时间复杂度 $ \mathcal{O}(3 \times 2^{n-1}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,s,l;
int ans[30];
vector<int>q[30];
int ts[30][30];
int v[30];
int c[30];
int doing(int x,int fa)
{
    if(c[x])
    {
        ts[x][fa]=1;
        return c[x]!=c[fa];
    }
    v[x]=1;
    int ans=0,now;
    for(int i=1;i<=3;i++)
    if(i!=c[fa])
    {
        c[x]=i;
        now=1;
        memset(ts[x],0,sizeof(ts[x]));
        for(int j=0;j<q[x].size();j++)
        if(!ts[x][q[x][j]])
        now*=doing(q[x][j],x);
        ans+=now;
    }
    c[x]=0;
    return ans;
}
main()
{
    cin>>n>>m;
    while(m--)
    {
        scanf("%d %d",&s,&l);
        q[s].push_back(l);
        q[l].push_back(s);
    }
    s=0;
    for(int i=1;i<=n;i++)
    if(!v[i])
    ans[++s]=doing(i,0);
    for(int i=2;i<=n;i++)
    ans[i]*=ans[i-1];
    cout<<ans[s];
}
```


---

## 作者：StayAlone (赞：0)

## 题意

给定一个 $N$ 个点 $M$ 条边的简单无向图，要求给每个点染色，共有三种颜色，问最终满足对于任意一条边，其两端节点颜色不同的染色方案数。

## 思路

考虑 dfs 暴力染色。对于一个点数为 $x$ 的联通块，从某一个点开始，这个点以外的每个点最多两种染色方式，所以时间复杂度为 $\mathcal O(3\times 2^{x-1})$。

那如果他给你 $0$ 条边的图，总时间复杂度就炸成了 $\mathcal O(3^n)$。所以自然想到，对于每一个独立的点，无需 dfs，因为它们可以任意染色。若有 $p$ 个独立的点，答案就是其余的点的染色方案乘上 $3^p$。

因此，只需要精美地实现一下，仅枚举有必要的点和有必要的颜色，时间复杂度最劣应该是 $\mathcal O(2^{\frac{n}{2}}\times 3^{\frac{n}{2}})=\mathcal O(6^{\frac{n}{2}})$。这样的数据是 $N$ 个点 $\frac{N}{2}$ 条边，每个联通块大小均为 $2$。

[AC record](https://atcoder.jp/contests/abc199/submissions/41531632)

```cpp
int n, m, vis[MAXN], col[MAXN], ord[MAXN], wt[MAXN], idx; vector <int> lnk[MAXN];
ll ans, tms = 1;

il void add(const int &x, const int &y) {
	lnk[x].eb(y); lnk[y].eb(x);
}

il bool check() {
	rep1(i, 1, n) {
		for (auto v : lnk[i]) if (!vis[v] && !vis[i] && col[v] == col[i]) return false;
	} return true;
}

il bool clt() {
	rep1(i, 1, n) if (!col[i] && !vis[i]) return false;
	return true;
}

il void dfs(int step) {
	if (step > idx) return ans += check(), void();
	int p = ord[step];
	if (vis[p]) return dfs(step + 1);
	for (auto v : lnk[p]) if (col[v]) {
		rep1(i, 1, 3) if (i ^ col[v]) col[p] = i, dfs(step + 1), col[p] = 0;
		return;
	}
	rep1(i, 1, 3) col[p] = i, dfs(step + 1), col[p] = 0;
}

il void pre(int x) {
	wt[x] = 1; ord[++idx] = x;
	for (auto v : lnk[x]) if (!vis[v] && !wt[v]) pre(v);
}
 
int main() {
	read(n, m);
	rep1(i, 1, m) add(read(), read());
	rep1(i, 1, n) if (!lnk[i].size()) tms *= 3, vis[i] = 1;
	rep1(i, 1, n) if (!wt[i] && !vis[i]) pre(i);
	dfs(1); printf("%lld\n", tms * ans);
	rout;
}
```

---

