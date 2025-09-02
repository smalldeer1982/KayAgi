# Snowy Mountain

## 题目描述

There are $ n $ locations on a snowy mountain range (numbered from $ 1 $ to $ n $ ), connected by $ n-1 $ trails in the shape of a tree. Each trail has length $ 1 $ . Some of the locations are base lodges. The height $ h_i $ of each location is equal to the distance to the nearest base lodge (a base lodge has height $ 0 $ ).

There is a skier at each location, each skier has initial kinetic energy $ 0 $ . Each skier wants to ski along as many trails as possible. Suppose that the skier is skiing along a trail from location $ i $ to $ j $ . Skiers are not allowed to ski uphill (i.e., if $ h_i < h_j $ ). It costs one unit of kinetic energy to ski along flat ground (i.e., if $ h_i = h_j $ ), and a skier gains one unit of kinetic energy by skiing downhill (i.e., if $ h_i > h_j $ ). For each location, compute the length of the longest sequence of trails that the skier starting at that location can ski along without their kinetic energy ever becoming negative. Skiers are allowed to visit the same location or trail multiple times.

## 说明/提示

In the first test, $ h = [0, 0, 1, 1, 2, 3] $ . The skier starting from $ 6 $ can ski along at most $ 5 $ trails, in the path $ 6 \rightarrow 5 \rightarrow 4 \rightarrow 3 \rightarrow 4 \rightarrow 2 $ (notice that a skier can ski multiple times along the same trail and can visit more than once the same location):

- at the location $ 6 $ , the kinetic energy is $ 0 $ ;
- at the location $ 5 $ , the kinetic energy increases by $ 1 $ (because $ h_5 < h_6 $ ), so it becomes $ 1 $ ;
- at the location $ 4 $ , the kinetic energy increases by $ 1 $ (because $ h_4 < h_5 $ ), so it becomes $ 2 $ ;
- at the location $ 3 $ , the kinetic energy decreases by $ 1 $ (because $ h_3 = h_4 $ ), so it becomes $ 1 $ ;
- at the location $ 4 $ , the kinetic energy decreases by $ 1 $ (because $ h_4 = h_3 $ ), so it becomes $ 0 $ ;
- at the location $ 2 $ , the kinetic energy increases by $ 1 $ (because $ h_2 < h_4 $ ), so it becomes $ 1 $ .

There isn't any sequence of trails of length greater than $ 5 $ such that the kinetic energy is always non-negative.

Moreover,

- the optimal path for the skier starting from $ 1 $ is $ 1 $ (no trails);
- the optimal path for the skier starting from $ 2 $ is $ 2 $ (no trails);
- the optimal path for the skier starting from $ 3 $ is $ 3 \rightarrow 1 $ ;
- the optimal path for the skier starting from $ 4 $ is $ 4 \rightarrow 2 $ ;
- the optimal path for the skier starting from $ 5 $ is $ 5 \rightarrow 4 \rightarrow 3 \rightarrow 1 $ .

In the second test, $ h = [3, 2, 2, 1, 1, 1, 0, 0, 0] $ . The skier starting from $ 1 $ can ski along at most $ 5 $ trails, in the path $ 1 \rightarrow 3 \rightarrow 2 \rightarrow 5 \rightarrow 4 \rightarrow 7 $ .

- at the location $ 1 $ , the kinetic energy is $ 0 $ ;
- at the location $ 3 $ , the kinetic energy increases by $ 1 $ (because $ h_3 < h_1 $ ), so it becomes $ 1 $ ;
- at the location $ 2 $ , the kinetic energy decreases by $ 1 $ (because $ h_2 = h_3 $ ), so it becomes $ 0 $ ;
- at the location $ 5 $ , the kinetic energy increases by $ 1 $ (because $ h_5 < h_2 $ ), so it becomes $ 1 $ ;
- at the location $ 4 $ , the kinetic energy decreases by $ 1 $ (because $ h_4 = h_5 $ ), so it becomes $ 0 $ ;
- at the location $ 7 $ , the kinetic energy increases by $ 1 $ (because $ h_7 < h_4 $ ), so it becomes $ 1 $ .

There isn't any sequence of trails of length greater than $ 5 $ such that the kinetic energy is always non-negative.

In the third test, for the skier starting from vertex $ 1 $ , the optimal path is $ 1 \rightarrow 2 \rightarrow 5 \rightarrow 4 \rightarrow 3 \rightarrow 6 \rightarrow 11 \rightarrow 10 \rightarrow 11 $ .

Here are pictures of the first, second, and third test, with the base lodges shown in red:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1654G/b725e7b9e427936f6b26c706b4c284b2d928bc38.png)

## 样例 #1

### 输入

```
6
1 1 0 0 0 0
1 3
2 4
3 4
4 5
5 6```

### 输出

```
0 0 1 1 3 5```

## 样例 #2

### 输入

```
9
0 0 0 0 0 0 1 1 1
1 3
2 3
2 5
3 6
4 5
4 7
5 8
6 9```

### 输出

```
5 3 2 1 1 1 0 0 0```

## 样例 #3

### 输入

```
14
0 0 0 0 0 0 0 0 0 1 1 1 1 1
1 2
2 5
3 4
4 5
3 6
4 8
5 9
7 8
6 11
7 12
8 13
9 14
10 11```

### 输出

```
8 5 4 3 2 2 1 1 1 0 0 0 0 0```

## 样例 #4

### 输入

```
20
0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 1 0 1
17 3
11 12
6 10
18 19
8 14
16 20
5 3
2 11
7 10
2 15
8 3
3 15
9 16
7 13
16 1
19 2
2 16
6 1
4 17```

### 输出

```
2 2 1 5 3 4 8 1 2 6 4 6 10 0 0 0 3 0 1 0```

# 题解

## 作者：Un1quAIoid (赞：7)

**洛谷传送门：[Snowy Mountain](https://www.luogu.com.cn/problem/CF1654G)**

--------------------

贡献一个 $O(n \log n)$ 解法。

初始可以用 BFS 求出每个点的高度 $h_u$。

接下来我们来考虑如何使得操作数最大化，这点其它题解讲的很明白，从点 $u$ 出发的答案即为 $2h_u-h_v$，其中 $v$ 是从 $u$ 出发能到达的高度最小的具有相同高度邻点的点。

考虑使用点分治计算每个点 $u$ 所对应的 $h_v$，设当前分治连通块的重心为 $x$，连通块大小为 $s$，先用 DFS $O(s)$ 计算出从 $x$ 出发到达连通块内每个点 $v$ 所需的最小初始动能，具体做法是维护变量 $sum$，高度下降则 $-1$，不变则 $+1$，到 $v$ 点时所需的最小动能即为过程中 $sum$ 的最大值。

使用同样的方法，我们也可以用第二遍 DFS 处理出从连通块内每个点 $u$ 是否可以到达 $x$，以及到达时的动能。此时在 $O(s \log s)$ 时间内处理每个连通块的方式就比较明朗了：将所有能够到达的、具有相同高度邻点的 $v$ 按照到达它所需的最小动能排序，然后按照 $h_v$ 做一个前缀min，在第二遍 DFS 到某个点 $u$ 时直接在这个有序序列上二分查找其所对应的最小的 $h_v$ 即可，因为是取min而不是求和，所以可以不用担心 $u$ 和 $v$ 来自同一棵子树的情况。

这样复杂度是 $O(n \log^2 n)$ 的，然后我们还有很好的一个性质没有用到：**每次变量 $sum$ 只会 $+1$ 或 $-1$。**

这意味着变量 $sum$ 的值是 $O(s)$ 的，这就允许我们可以不用排序，而是直接在值域上操作，这样处理单个分治连通块的复杂度就降到了 $O(s)$，总复杂度 $O(n \log n)$。

代码：
```cpp
//CF1654G Snowy Mountain
//O(nlogn)解法
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define eb emplace_back
#define pb push_back
#define mp make_pair
using namespace std;

typedef long long ll;
const int N = 2e5+5;
const int Mod = 998244353;

int n, h[N], ans[N];
int siz[N];
bool b[N], vis[N];

vector<int> T[N];
queue<int> Q;

void dfs_centre(int x, int fa, int sizz, int &c) {
    siz[x] = 1;
    int mx = 0;
    for (auto son : T[x]) {
        if (son == fa || vis[son]) continue;
        dfs_centre(son, x, sizz, c);
        siz[x] += siz[son];
        mx = max(mx, siz[son]);
    }
    if (mx <= sizz / 2 && siz[x] >= sizz / 2) c = x;
}

int L, R, mn[N * 2];

void dfs(int x, int fa, int mx, int sum, bool t) {
    mx = max(mx, t ? sum : -sum);
    if (t) {
        if (sum >= mx && sum + n >= L)
            ans[x] = min(ans[x], mn[min(R, sum + n)]);
    } else if (b[x]) {
        while (R < mx + n) mn[++R] = n;
        while (L > mx + n) mn[--L] = n;
        mn[mx + n] = min(mn[mx + n], h[x]);
    }

    for (auto son : T[x]) {
        if (son == fa || vis[son]) continue;
        if (h[son] == h[x]) dfs(son, x, mx, sum - 1, t);
        else if (t ^ (h[x] > h[son])) dfs(son, x, mx, sum + 1, t);
    }
}

inline void calc(int x) {
    L = R = mn[n] = n;
    dfs(x, x, 0, 0, 0);
    for (int i = L + 1; i <= R; i++) mn[i] = min(mn[i], mn[i - 1]);
    dfs(x, x, 0, 0, 1);
}

void solve(int x, int sizz) {
    dfs_centre(x, x, sizz, x);
    vis[x] = 1;
    calc(x);
    for (auto son : T[x]) {
        if (vis[son]) continue;
        solve(son, siz[son] > siz[x] ? sizz - siz[x] : siz[son]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
        h[i] = -1;
        if (b[i]) {
            h[i] = 0;
            Q.push(i);
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        T[u].pb(v), T[v].pb(u);
    }

    while (!Q.empty()) {
        int top = Q.front();
        Q.pop();
        for (auto v : T[top]) if (!~h[v]) {
            h[v] = h[top] + 1;
            Q.push(v);
        }
    }

    for (int i = 1; i <= n; i++) {
        ans[i] = h[i];
        b[i] = 0;
        for (auto j : T[i]) if (h[i] == h[j])
            { b[i] = 1; break; }
    }

    solve(1, n);

    for (int i = 1; i <= n; i++) printf("%d ", 2 * h[i] - ans[i]);
    return 0;
}
```

---

## 作者：Tyyyyyy (赞：6)

## CF1654G

### 题意简述
有一棵树，其中某些点是小屋。对于每个点定义高度 $h_i$ 为它到最近的小屋的距离。有一滑雪者从某一点出发，能量值初始为 $0$，若滑到一个 $h$ 小于当前点的点，则能量值 $+1$，若滑到一个 $h$ 等于当前点的点，则能量值 $-1$。不能滑到 $h$ 更大的点。

对于每个点，求以该点作为出发点最多能走多远。可以重复经过点或边。

### 题目分析
我们称一条满足 $h_u=h_v$ 的边 $(u,v)$ 为一个平台，那么这个人的最优策略一定是先滑到能到达的最低平台，然后来回滑把能量用完，再滑到小屋。

假设这个人从 $u$ 出发，在一个包含 $v$ 的平台上滑，那么总路径长度就是 $2h_u-h_v$。这是因为用尽能量后，从 $v$ 滑到小屋积累的 $h_v$ 的能量不能消耗。

如果这个人从 $u$ 出发，滑不到任何一个平台，那么总路径长度就是 $h_u$。注意到答案能被表示为 $2h_u-val$ 的形式，其中 $val$ 是最后消耗不掉的能量值。我们不妨对于每个点计算 $val_u$。

注意到 $val_u$ 要么是 $h_u$，要么是 “从 $u$ 出发能到达的最低平台的高度”。这启发我们关注平台的高度。可以发现若存在一个高度为 $k$ 的平台，那么其两端至少有 $2k$ 个点（根据高度的定义易得）。因此，所有平台的高度之和为 $O(n)$ 级别。这是一个经典的模型，我们随即可以得到，平台高度的种类数为 $O(\sqrt{n})$ 级别。

那么，$val_u$ 的种类数也是 $O(\sqrt{n})$ 级别的。我们可以尝试对于每一种 $val$，计算出有哪些点取该值。我们可以对于一种平台的高度，求出能到达该种平台的所有顶点。

具体来说，按照平台的高度将这个树分为若干层，做类似 $01$ bfs 的最短路即可。

时间复杂度为 $O(n\sqrt{n})$。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],h[N],f[N],g[N];
vector<int>g1[N],g2[N]; 
void add1(int u,int v)
{
	g1[u].push_back(v);
	g1[v].push_back(u);
}
int main()
{
	scanf("%d",&n);
	queue<int>q;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i])q.push(i),h[i]=1; 
	}
	for(int i=1,x,y;i<n;i++)
		scanf("%d%d",&x,&y),add1(x,y);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(auto v:g1[u])
			if(!h[v])h[v]=h[u]+1,q.push(v);
	}
	for(int i=1;i<=n;i++)
	{
		bool ok=0;
		for(auto j:g1[i])
			if(h[i]==h[j])ok=1;
		if(ok)g2[h[i]].push_back(i);
	}
	memset(g,-1,sizeof(g));
	deque<int>q0;
	for(int i=1;i<=n;i++)
	{
		if(g2[i].empty())continue;
		memset(f,0x3f,sizeof(f));
		for(auto v:g2[i])
			f[v]=i+1,q0.push_back(v);
		while(!q0.empty())
		{
			int u=q0.front();q0.pop_front();
			for(auto v:g1[u])
			{
				if((h[u]==h[v]||(h[u]<h[v]&&f[u]==h[u]))&&f[v]>f[u]+1)
					f[v]=f[u]+1,q0.push_back(v);
				if(h[u]<h[v]&&f[u]>h[u]&&f[v]>f[u])
					f[v]=f[u],q0.push_front(v);
			}
		}
		for(int u=1;u<=n;u++)
			if(f[u]==h[u]&&g[u]==-1)g[u]=i;
	}
	for(int i=1;i<=n;i++)
		if(g[i]==-1)printf("%d ",h[i]-1);
		else printf("%d ",2*(h[i]-1)-(g[i]-1));
	return 0;
}
```

---

## 作者：Locix_Elaina_Celome (赞：3)

# [CF1654G Snowy Mountain](https://www.luogu.com.cn/problem/CF1654G) 题解

## 题意

给出一颗树，点分黑白色。一个点的高度 $h_i$ 定义为其距离最近黑色节点的距离。初始在点 $i$，动能为 $0$。每次可以向相邻的更低点移动，动能 $+1$，或向相邻的相同高度点移动，动能 $-1$。对于 $i\in [1,n]$，求出最多能移动多少次。

$n\le 2\times 10^5$

## 题解

（下面称一些相邻的等高点组成的连通块为一个“平台”。）

容易想到，我们每次直接走得尽可能低，然后在两个相同高度的点之间 brbrbrbrbr 然后再走到最下面。

所以答案其实就很明晰了：设 $val_i$ 表示从点 $i$ 出发能到的最深的“平台”的高度（一个也到不了则 $val_i=h_i$），则答案为 $2h_i-val_i$。$h_i$ 可以用 BFS 轻松求出，所以我们现在的目标就是怎么求出 $val_i$。

首先给出一个~~一点也不好想的~~暴力做法。

一个显然的事实：一个点 $i$ 能走到一个高 $k$ 的平台，当且仅当其走到一个高 $k$ 的平台至少要 $0$ 的初始动能。所以我们直接从点 $i$ 开始 bfs，求出到每个平台要的最少初始动能，于是有了一个一点也不优秀的 $O(n^2)$ 做法。

作为一个 OI 人，秉着有分就骗有常数就卡的原则~~（虽然这是 CF）~~，我们发现平台的高度种类数再怎么说也比点数要少一些，尝试反着 bfs。

具体地，对于一个高度 $k$，我们从每个高 $k$ 的平台出发，相同高度的点之间边权为 $1$，向上边权为 $-1$。每转移一次要与 $0$ 取 $\min$（毕竟实际操作时后面获得的动能不能在前面用）。形式化地，$dp_v=\min(dp_u,\max(dp_u+c_{u,v},0))$，其中 $c$ 为边权。

这个类似于一个最短路，但要取 $\min$，所以并不能简单地用 $lca$。

可以选择用 SPFA。

当然也可以选择使用 01bfs（我并不会）。

有意思的是，这样的时间复杂度是 $O(n\sqrt{n})$ 的，因为平台的高度种类数是 $O(\sqrt{n})$ 级别的。这并不难证明，对于一个高 $k$ 平台，其两端往下走至少有 $2k$ 个点，且每个点至多在一个平台下面。设我们有 $x$ 个不同的平台高度，则有 $\sum\limits_{k=0}^{x} 2k=x(x-1)\le n$，则 $x$ 为 $O(n)$ 级别的。

于是我们就 A 了。

## 代码

（01bfs 写挂了不想调，直接 SPFA。）

```cpp
using namespace std;
#include<bits/stdc++.h>
//#include<cstdio>
//#include<cstring>
//#include<string>
//#include<iostream>
//#include<utility>
//#include<algorithm>
#define MAX(x,y) (x<y?y:x)
#define MIN(x,y) (x<y?x:y)
#define ABS(x) (x<0?-x:x)
#define lb(x) ((x)&(-(x)))
#define N 200005
#define LL long long
#define LD long double
#define int LL
//#define double LD
#define P 1000000007
#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#elif _WINDOWS_
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#else
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
constexpr double EPS=(1e-9);
#ifdef int
constexpr int INF=1211081101201201140;
#else
constexpr int INF=1145141919;
#endif
template<typename T>T Max(T x,T y){return MAX(x,y);}
template<typename T>T Min(T x,T y){return MIN(x,y);}
template<typename T>T Abs(T x){return ABS(x);}
template<typename T>void Swap(T&x,T&y){x^=y^=x^=y;}
template<typename T>T Gcd(T x,T y){while(y^=x^=y^=x%=y);return x;}
template<typename T>
T qp(T a,T b){T sum=1;
while(b){if(b&1)sum=(sum*a)%P;a=(a*a)%P;b>>=1;}return sum;}
template<typename T>
void read(T&x){
x=0;char c=getchar();/*T fl=1;*/
while(c<'0'||c>'9'){/*if(c == '-')fl=-1;*/c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}/*x*=fl;*/}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);}
int n;
int t[N<<1],las[N<<1],fir[N],num;
void add(int u,int v){
t[++num]=v;las[num]=fir[u];fir[u]=num;
t[++num]=u;las[num]=fir[v];fir[v]=num;}
int col[N];
int h[N];
void bfs(){
	queue<int> q; 
	for(int i=1;i<=n;i++){
		h[i]=INF;
		if(col[i])h[i]=0,q.push(i);
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=fir[u];i;i=las[i])
			if(h[u]+1<h[t[i]])q.push(t[i]),h[t[i]]=h[u]+1;
	}
}
vector<int> v[N];
int val[N];
int vis[N];
int stp[N];
signed main(){
	read(n);
	for(int i=1;i<=n;i++)read(col[i]);
	for(int i=1,x,y;i<n;i++)read(x),read(y),add(x,y);
	bfs();
	for(int u=1;u<=n;u++){
		int fl=0;
		for(int i=fir[u];i;i=las[i])fl|=(h[t[i]]==h[u]);
		if(fl)v[h[u]].push_back(u);
	}
	for(int i=1;i<=n;i++)val[i]=h[i];
	for(int k=n;k>=0;k--){
		if(v[k].empty())continue;
		for(int i=1;i<=n;i++)vis[i]=0,stp[i]=INF;
		queue<int> q;
		for(int u:v[k])stp[u]=0,q.push(u); 
		while(!q.empty()){
			int u=q.front();
			q.pop();
			vis[u]=0;
			for(int i=fir[u];i;i=las[i]){
				if(h[t[i]]==h[u]&&stp[u]+1<stp[t[i]]){
					stp[t[i]]=Min(stp[u]+1,stp[t[i]]);
					if(!vis[t[i]])q.push(t[i]);
					vis[t[i]]=1;
				}
				else if(h[t[i]]>h[u]&&Max(stp[u]-1,(int)0)<stp[t[i]]){
					stp[t[i]]=Min(stp[t[i]],Max(stp[u]-1,(int)0));
					if(!vis[t[i]])q.push(t[i]);
					vis[t[i]]=1;
				}
			}
		}
		for(int i=1;i<=n;i++)if(stp[i]<=0)val[i]=Min(val[i],k);
	}
	for(int i=1;i<=n;i++)write((h[i]<<1)-val[i]),putchar(' ');
	return 0;
}
```



---

## 作者：I_am_Accepted (赞：3)

~~正解 $O(n\sqrt{n})$，谁又想得到呢？~~

首先一次 BFS 求出每个节点的高度。

贪心地，一个位置上若要滑得最远，可以先不断滑，然后到达两个相邻且高度相同的节点反复横跳，将势能用尽后再滑向底部。

记 $h_i$ 表示 $i$ 点的高度，若出发节点为 $x$，反复横跳的节点为 $y$，则最终滑雪距离为
$$
Ans=2h_x-h_y
$$
所以我们对于每一个出发点，需要找到最小的反复横跳高度。

记那些可以反复横跳的节点为集合 $P$。

* * *

**结论：** $P$ 中不同的高度数量为 $O(\sqrt{n})$。

* * *

所以我们对于每种 $P$ 内出现的高度，求出哪些点可以在这个高度反复横跳，设当前考虑高度 $v$。

记 $f_i$ 表示在 $i$ 节点至少要储备多少势能才能到达 $v$ 高度横跳，转移有
$$
f_x=0\quad(h_x=v)
$$
$$
f_i=\min\{\max(0,f_j-1)\ |\ (i,j)\in E,h_i=h_j+1\}\cup\{f_j+1\ |\ (i,j)\in E,h_i=h_j\}
$$
前半部分我们按 $h$ 分层 BFS，后半部分换根树形 DP。

代码实现要达到 $O(n\sqrt n)$ 且不写假或带 $\log$ 是挺麻烦的。

[更多 STL 的代码](https://codeforces.com/contest/1654/submission/164142890) [更少 STL 的代码](https://codeforces.com/contest/1654/submission/164144640)

---

## 作者：Cry_For_theMoon (赞：3)

这是一个常数很大的 $O(n\log^2 n)$ 解法。信仰 polylog 拒绝根号谢谢喵。

经过一些归纳整理，我们的行走路径一定是 $u\rightarrow v$ 的最短路径，其中最多在一个点 $w$ 的时候，会反复来回在 $w$ 和它的一个同高度邻居间横跳，最后回到 $w$，一口气走到 $v$。且满足 $w\rightarrow v$ 这一段的高度是不断严格下降的。

设 $f(u)$ 是从 $u$ 出发，不断严格下降高度，所能走的最大步数；那么上面的路径，可以看成 $u\rightarrow w$，然后反复横跳回到 $w$，然后加上 $f(w)$。这样我们就可以用简单路径的形式描述我们的行走，把所有简单路径以外的部分用一个简单的贡献形式来描述。

我们把路径上，势能增加的边给上 $+1$ 的权，势能减少的边给上 $-1$ 的权（当然有一些边禁止通行）。那么合法的充要条件是最小前缀和非负，设最后总共的和是 $d$（也就是走到 $w$ 后余下的势能），如果我们要进行反复横跳，那么我们应该是可以走 $\lfloor \frac{d}{2} \rfloor\times 2$ 也就是 $d-[2\nmid d]$ 这么多步。

首先考虑点分。这样我们可以对每个点 $u$，处理 $u$ 上行到 $rt$ 以及从 $rt$ 下行到 $u$ 的信息。我们考虑拼接两部分，那么只需要分别维护两端的 $(premin,endv)$，分别表示最小前缀和以及最后总共的和。

然后设上行段是 $L$，下行段是 $R$，那么最小前缀和非负的话，也就是：

$$
\begin{cases}
premin_L\ge 0 \\
endv_L+premin_R\ge 0
\end{cases}
$$

看上去是一个二维数点的形式。实际上如果 $premin_L\lt 0$ 我们直接忽略这个点，这样就只剩下一个维度的限制了，可以直接 bit 上解决。（点分治为了解决相同子树问题，要正着反着遍历一遍，这个过程决定了它是一个“在线”的数点，因此这个一维数点也必须用 BIT 维护前缀 $\max$）。

贡献可以拆成 $depth_u+depth_v+f(v)$，然后我们还要分类：也就是到底是否进行反复横跳（因为不是所有的点 $w$ 都可以反复横跳的）。

如果不能横跳，那么直接 $depth_u+depth_v+f(v)$ 完事（事实上 $depth_u+depth_v$ 也是可以的）。

如果可以横跳，那么我们发现 $d=endv_L+endv_R$，暴力枚举两个 $endv$ 的奇偶性就可以确定 $d$ 的奇偶性。所以我们加入一个点的时候要加入到其 $endv$ 所属奇偶性的 bit（还要根据是否能成为反复横跳点分类，所以实质上有 $4$ 个 bit）。然后查询 bit 的时候再去暴力枚举 $4$ 种 case，此时的贡献是容易统计的。

时间复杂度确实是 $O(n\log^2 n)$ 但是常数也确实很大。

[记录](https://codeforces.com/contest/1654/submission/186411542)

---

## 作者：yyyyxh (赞：2)

感觉从这道题学到了好多套路和分析技巧，所以在这里记录一下，以下主要是对官方题解的一些理解与补充。

首先假设我们最后走的长度为 $len$ ，容易发现，我们最终终点一定是某一个盆地，多源 bfs 出高度 $d_x$ ，那么发现我们有 $d_x$ 步在增加动能，剩下的步都在减少动能，也就是说，我们最后一定会剩下 $d_x-(len-d_x)=2d_x-len$ 单位的动能。

考虑一个贪心，如果我们不是直接沿着最短路径滑向某一个盆地的，那么我们一定会经过 $d_u=d_v$ 的边，如果在经过最后的这样的边时我们还有剩余动能，我们不如在这条边上反复滑来滑去增加距离，这样子的话最后一定一点动能都不剩，再继续沿着最短路径直接滑向某一个盆地（这个过程只会增加动能），最后剩余的动能就是 $w(=d_u/d_v)$ 。那么这种情况中 $w=2d_x-len$ ，可以得到 $len=2d_x-w$ ，我们的任务就是求对每个点 $x$ 求最优 $w$。

$w$ 就是所有能够满足动能限制的前提下被 $x$ 到达且有一条 $d_u=d_v$ 的树边的 $u$ 的最小值，这个东西十分难以处理，很大的原因是这道题的出发点和需考虑的终点都有 $O(n)$ 个，这个时候找性质就很神了。

设 $S=\{u|\exists (u,v)\in E,d_u=d_v\}$ ，发现 $\sum_{u\in S} d_u$ 在 $O(n)$ 级别。

这个东西很好理解，因为两个相邻点 $d_u=d_v$ ，那么他们一定分别由两条长度为 $d_u/d_v$ 的不交路径增广而来。

一堆数的和是 $O(n)$ 级别，那么数的种类就是 $O(\sqrt n)$ 级别，那么我们真正需要考虑的终点的 $d_u$ 种类也是 $\sqrt n$ 级别的。

具体地，设 $f_{u,i}$ 表示从 $u$ 到每一个 $d_v=i$ 的点的路程中所有时刻的动能的最小值的相反数的最小值（此时先假设动能可以为负），第二维的大小就是 $O(\sqrt n)$ 的。

发现这个东西转移顺序不太好搞，首先可以发现如果 $d$ 不等那么就从 $d$ 小的转移到 $d$ 大的，但是 $d$ 相同的位置是多个连通块。

那么对每一个连通块 up and down dp 就可以解决转移顺序的问题。

```cpp
#include <cstdio>
using namespace std;
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=(x<<1)+(x<<3)+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
const int INF=0x3f3f3f3f;
const int N=200003;
int que[N],tl;
int d[N],n;
int f[N][700];
namespace tr{
	int hd[N],ver[N<<1],nxt[N<<1],tot;
	void add(int u,int v){nxt[++tot]=hd[u];hd[u]=tot;ver[tot]=v;}
}
namespace bl{
	int hd[N],ver[N<<1],nxt[N<<1],tot;
	void add(int u,int v){nxt[++tot]=hd[u];hd[u]=tot;ver[tot]=v;}
}
void chmn(int &u,int v){if(u>v) u=v;}
void chmx(int &u,int v){if(u<v) u=v;}
bool vis[N];
int p[N],pp[N],rk;
void updp(int u,int fa){
	vis[u]=1;
	for(int i=tr::hd[u],v;i;i=tr::nxt[i])
		if((v=tr::ver[i])^fa){
			if(d[v]!=d[u]) continue;
			updp(v,u);
			for(int t=1;t<=rk;++t)
				chmn(f[u][t],f[v][t]+1);
			f[u][pp[d[u]]]=1;
		}
}
void downdp(int u,int fa){
	for(int i=tr::hd[u],v;i;i=tr::nxt[i])
		if((v=tr::ver[i])^fa){
			if(d[v]!=d[u]) continue;
			for(int t=1;t<=rk;++t)
				chmn(f[v][t],f[u][t]+1);
			f[v][pp[d[v]]]=1;
			downdp(v,u);
		}
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		int a=read();
		if(a==1) vis[que[++tl]=i]=1;
		else d[i]=INF;
	}
	for(int i=1;i<n;++i){
		int u=read(),v=read();
		tr::add(u,v);tr::add(v,u);
	}
	for(int it=1;it<=tl;++it){
		int u=que[it];
		for(int i=tr::hd[u],v;i;i=tr::nxt[i])
			if(!vis[v=tr::ver[i]]){
				d[v]=d[u]+1;
				vis[que[++tl]=v]=1;
			}
	}
	for(int u=1;u<=n;++u){
		vis[u]=0;bl::add(d[u],u);
		if(pp[d[u]]) continue;
		for(int i=tr::hd[u];i;i=tr::nxt[i]){
			int v=tr::ver[i];
			if(d[u]==d[v]) p[pp[d[u]]=++rk]=d[u];
		}
	}
	for(int o=0;o<=n;++o){
		for(int i=bl::hd[o];i;i=bl::nxt[i]){
			int u=bl::ver[i];
			for(int t=1;t<=rk;++t) f[u][t]=INF;
			for(int j=tr::hd[u];j;j=tr::nxt[j]){
				int v=tr::ver[j];
				if(d[v]!=d[u]-1) continue;
   				for(int t=1;t<=rk;++t)
					if(f[v][t]) chmn(f[u][t],f[v][t]-1);else f[u][t]=0;
			}
		}
		for(int i=bl::hd[o];i;i=bl::nxt[i]){
			int u=bl::ver[i];
			if(!vis[u]) updp(u,0),downdp(u,0);
		}
	}
	for(int u=1;u<=n;++u){
		int res=d[u];
		for(int t=1;t<=rk;++t)
			if(!f[u][t]) chmx(res,d[u]+d[u]-p[t]);
		printf("%d ",res);
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：pengyule (赞：0)

[1654G Snowy Mountain](http://codeforces.com/problemset/problem/1654/G)
> 一棵 $n(n\le 2\cdot 10^5)$ 个点的树，布尔数组 $l_i$ 表示点 $i$ 是不是基地，一个点的高度 $h_i$ 为其到最近的基地的距离。从一个点出发时动能为 $0$，随后可以下滑或走平地，从 $u$ 到相邻的 $v$：若 $h_u>h_v$，则增加 $1$ 动能，若 $h_u=h_v$，则减少 $1$ 动能。问从每个点出发、全程动能非负最远可以到的距离。


滑雪下来重力势能做的功是恒定的，我们实际要最大化产生的热能，即滑更多的平地。

**结论1**（贪心）最优策略为滑到一个海拔最低的“辗转点”，再在这个平台上辗转直到动能耗尽，再由它径直滑到最近的基地。*定义“辗转点”为相邻节点中有与它等高的点的点。*  
*证明*：当人到达终点时，具有动能 $w$，$w$ 就是完全被浪费的，原因是除掉恒定的那 $h_u$ 个单位长度，没有浪费的机械能都会转化为一单位热能，即一单位长度，要最小化浪费，就要最低化目标“辗转点”。进一步量化，令 $h_u,h_v$ 为起始点和目标“辗转点”的高度，$len$ 表示路径总长度，则根据上面有 $len=h_u+(h_u-h_v)=2h_u-h_v$。

现在的任务变为求一个点能到达的最低“辗转点”。

**结论2** 所有“辗转点”的高度总和为 $O(n)$ 级别。  
*证明*：  
![image040787c149c1ff69.png](https://z4请更换图床a.net/images/2022/04/13/image040787c149c1ff69.png)  
**推论** 高度不同的“辗转点”数量不超过 $\sqrt{2n}=O(\sqrt n)$。（最坏情况下是 $\sum h=1+2+...$）

这就是说我们可以暴力枚举辗转平台高度，并看看哪些点可以到达这一高度的辗转点的任意一个，更新它们的答案。  
具体地，我们设 $c_u$ 为 $u$ 到达任何一个这一高度的辗转点的最小初始动能，则扩展 $c_u$ 的过程等价于在一个边权为 $h_u=h_v\to 1$、$h_u<h_v\to-1$ 的图上跑多源最短路；这个可以使用分层 bfs，将高度相同的点视作同一层，按高度从小到大处理每一层：在层内部做普通的 bfs（一个点可能会多次入队，但所有点的入度之和是 $O(n)$ 的），搞完后进行 $h\to h+1$ 的边的扩展。总时间复杂度 $O(n\sqrt n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5,INF=0x3f3f3f3f;
int n,l[N],h[N],u[N],v[N],c[N],mn[N];
vector<int>G[N],nd[N],land[N];
queue<int>Q;
inline int read(){
	register char ch=getchar();register int x=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
void bfs(int H){
	memset(c,0x3f,sizeof(c));
	for(int i=0;i<land[H].size();i++)c[land[H][i]]=0;
	for(int i=H;i<=n;i++){
		for(int j=0;j<nd[i].size();j++)if(c[nd[i][j]]!=INF)Q.push(nd[i][j]);
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			for(int j=0;j<G[x].size();j++){
				int y=G[x][j];
				if(h[x]!=h[y])continue;
				if(c[x]+1<c[y]){
					c[y]=c[x]+1;
					Q.push(y);
				}
			}
		}
		for(int j=0;j<nd[i].size();j++)if(c[nd[i][j]]!=INF){
			int x=nd[i][j];
			for(int k=0;k<G[x].size();k++){
				int y=G[x][k];
				if(h[x]<h[y]&&c[x]-1<c[y]){
					c[y]=max(c[x]-1,0);
				}
			}
		}
	}
	for(int i=1;i<=n;i++)if(!c[i])mn[i]=min(mn[i],H);
}
int main(){
	n=read();
	memset(h,-1,sizeof(h));
	for(int i=1;i<=n;i++){
		l[i]=read();
		if(l[i])h[i]=0,Q.push(i);
	}
	for(int i=1;i<n;i++)u[i]=read(),v[i]=read(),G[u[i]].push_back(v[i]),G[v[i]].push_back(u[i]);
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(int i=0;i<G[x].size();i++){
			int y=G[x][i];
			if(h[y]==-1)h[y]=h[x]+1,Q.push(y);
		}
	}
	for(int i=1;i<=n;i++)nd[h[i]].push_back(i); 
	for(int i=1;i<=n;i++){
		bool flag=0;
		for(int j=0;j<G[i].size();j++)if(h[G[i][j]]==h[i]){flag=1;break;}
		if(flag)land[h[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)mn[i]=h[i];
	for(int i=0;i<=n;i++)if(land[i].size())bfs(i);
	for(int i=1;i<=n;i++)cout<<(mn[i]==INF?0:2*h[i]-mn[i])<<' ';
} 
```

---

## 作者：Little09 (赞：0)

先一遍 BFS 求出 $h_i$。

考虑每个点滑雪的最优路径是什么。是先不重复经过点，滑到一个点 $x$，其中点 $x$ 满足其与一个相同高度的点相连。在 $x$ 与旁边这个点横跳，直到能量耗尽，最后滑下到底。

假设从点 $i$ 出发，能找到 $x$ 的最小高度是 $f_i$，那么 $i$ 的答案应当是 $2\times h_i-f_i$。于是题目转化为对每个点找到能到达的最小高度的 $x$ 点。

令所有符合条件的 $x$ 点构成集合 $S$，我们容易发现 $\sum_{i\in S}h_i$ 是 $O(n)$ 级别的。所以本质不同的 $h_i$ 是 $O(\sqrt{n})$ 级别的。

对每个符合的高度求出能不能到所有点就行了。可以通过分层的 BFS，对每层找到每个点需要多少能量 $d_i$ 可以到达符合的 $x$ 点就行了，每层之间传递然后到下一层，单次是线性复杂度。具体地，如果 $x$ 与 $y$ 有边：

- 在同一层：$d_x$ 可以用 $\max(d_y+1,1)$ 更新。
- 不在同一层：$d_x$ 可以用 $d_y-1$ 更新。

总时间复杂度是 $O(n\sqrt{n})$。

我的代码写得太复杂，就不放了。

---

