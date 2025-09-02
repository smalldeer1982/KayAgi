# [SEERC 2019] Game on a Tree

## 题目描述

Alice 和 Bob 在树上玩游戏。最初的时候，树上的所有节点都是白色的。

Alice 先手，她可以任选一个节点并在该点上放置一个标记，该点变为黑色。在这之后，玩家轮流进行游戏，每一回合中玩家可以将标记从所在点移动到该点的白色祖先节点或儿子节点中，并将移动到的点变为黑色。无法进行移动的玩家即输。

谁会赢得游戏呢？

在有根树上，节点 $v$ 的*祖先节点*是指从树根到节点 $v$ 的路径上的任意点。

在有根树上，节点 $v$ 的*儿子节点*是指满足节点 $v$ 在从树根到节点 $w$ 路径上的任意点 $w$。

规定树的树根为点 $1$。

## 说明/提示

第一组样例中，树的形态是 $4$ 个点的一条链，所以 Bob 总是可以把标记移到最后的白点上。

第二组样例中，Alice 的最佳策略是先把标记放在点 $3$ 上，然后 $3$ 会变为黑色。Bob 只能移动标记到点 $1$ 上。Alice 可以选择点 $4, 5, 6$ 或 $7$ 来移动。Bob 只能选择 $2$。Alice 选择 $2$ 的任一白色子节点，Bob 就无法移动了。

## 样例 #1

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
Bob```

## 样例 #2

### 输入

```
7
2 1
2 6
1 3
2 5
7 2
2 4```

### 输出

```
Alice```

# 题解

## 作者：FjswYuzu (赞：4)

$\ \ \ \ \ \ \ $[原题解blog](https://www.cnblogs.com/st1vdy/p/11789546.html)

---

$\ \ \ \ \ \ \ $题意转化：有一棵以 1 为根的树，每个节点的初始颜色为白色。Alice 先让任意一个节点放上标记变黑作为一次操作。然后 Bob 开始，轮流移动这个标记到当前所在节点的任意一个白色的祖先或者后代节点，并且把它这个节点染成黑色。谁不能移动谁就输了。

$\ \ \ \ \ \ \ $考虑这个树上博弈问题。首先引进树的最大匹配。不会的同学，可以自查博客。

$\ \ \ \ \ \ \ $首先假设我们只能够走到相邻的节点，我们发现我们只需要判断这棵树是否满足，它的最大匹配是一个完美匹配。如果是的话，后手必胜，否则先手一定能够避免，于是先手必胜。

$\ \ \ \ \ \ \ $回到问题，我们不只是走到相邻的节点。但是思路相同，这个问题我们用树形 dp 求解。

$\ \ \ \ \ \ \ $定义 $dp_i$ 为节点 $i$ 以及该节点对应子树未匹配节点的最小数量，$cnt=\sum_{\texttt{以i为根节点的后代j}} dp_j$

$$\begin{cases}
dp_i = cnt - 1 (cnt > 0),  \\    dp_i = 1 (cnt = 0).  \\
\end{cases}$$

$\ \ \ \ \ \ \ $如果 $dp_1=0$ ，则说明先手必胜。

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
vector<int> G[100005];
int dp[100005],n;
bool vis[100005];
void dfs(int now,int pre)
{
	bool flag=false;
	for(unsigned int i=0;i<G[now].size();++i)
	{
		if(G[now][i]==pre)	continue;
		dfs(G[now][i],now);
		flag|=vis[G[now][i]];
		dp[now]+=max(dp[G[now][i]],vis[G[now][i]]?1:0);
	}
	if(!flag || dp[now]>0)	vis[now]=true;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;++i)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	memset(dp,-1,sizeof dp);
	dfs(1,0);
	puts(dp[1]?"Alice":"Bob");
	return 0;
}
```

---

## 作者：CoronaQL (赞：2)

# 题意
这题读了好多遍才看懂，大意是说有一棵根为1的树，每个节点初始都是白色，Alice 能在这棵树的某个节点放下一个棋子，并使得该节点变为黑色，然后从Bob开始，两人能轮流移动这个棋子到当前所在节点的任意一个白色的祖先或者后代节点（不需要相邻的节点），并且将移动到的节点染为黑色。谁先不能移动就输了。
# 理解
题目是一个树上的博弈问题。我们一开始读错题意，以为必须得是移动到与当前节点相邻的节点，那这道题就很容易转化为求树上最大匹配的问题。我们发现如果这棵树的最大匹配是完美匹配，那么后手必胜，反之先手必胜，原因是：不论先手选哪一个节点，后手都能将棋子移动到与当前节点匹配的某一节点。但如果不存在完美匹配，那先手必然能避免这种情况。之后才发现不需要移动到相邻节点，事实上解决方法也类似上面说的树上最大匹配，只不过这个最大匹配并不需要相邻节点，只要某两个点满足互为祖先节点和后代节点就能匹配。
# 总结
如果是完美匹配，那么后手胜；不是完美匹配，先手胜。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int f[500007];
vector<int>ex[500007];
void dfs(int x,int fa)
{
    for(auto y : ex[x])//最近书上看到，用一下，大家不用管就按平常的for打就行 
	{
        if(y==fa)
		continue;
        dfs(y,x);
        f[x]+=f[y];
    }
    if(f[x])
	f[x]--;
    else 
	f[x]=1;
}
int main()
{
	int n;
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
	{
        int x,y;
        scanf("%d%d", &x, &y);
        ex[x].push_back(y);//再退回去 
        ex[y].push_back(x);//同理 
    }
    dfs(1,0);
    if(!f[1])
	printf("Bob\n");
    else 
	printf("Alice\n");
    return 0;
}
```


---

## 作者：WorldMachine (赞：1)

Trick：树上博弈，考虑完美匹配。

以防读题读错了，这个题中的棋子可以移动到任意没走过的祖先节点，不只是父亲节点。

首先有一个类似的问题：假如棋子只能移动到相邻节点，考虑完美匹配的存在性：

- 如果存在完美匹配，先手不管选哪个点，后手都可以选它的匹配点，这样后手一直有点选，所以后手必胜；
- 否则先手可以选择一个非匹配点，显然其它点都是匹配点（不然就存在增广路，可以多一条匹配边），那么就变成了第一种情况，只不过先后手交换了，因此先手必胜。

这个题也差不多，区别在于 $u$ 不仅可以和其相邻点匹配，还可以和它的任意祖先匹配，树形 dp，设 $f_u$ 表示 $u$ 子树内最少还剩多少个未匹配的点，转移是容易的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, f[N]; vector<int> G[N];
void dfs(int u, int fa) {
	for (int v : G[u]) if (v != fa) dfs(v, u), f[u] += f[v];
	if (f[u]) f[u]--; else f[u] = 1;
}
int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
	dfs(1, 0), printf("%s", f[1] ? "Alice" : "Bob");
}
```

---

## 作者：Betrayer_of_love (赞：1)

### 题目大意：
有一棵根为 $1$ 的树，每个节点初始都是白色，Alice 能在这棵树的某个节点放下一个棋子，并使得该节点变为黑色，然后从 Bob 开始，两人能轮流移动这个棋子到当前所在节点的任意一个白色的祖先或者后代节点（不需要相邻的节点），并且将移动到的节点染为黑色。谁先不能移动就输了。
 
### 思路：

做的时候一直以为他的跳转是只能跳转到当前点的相邻结点，但其实这道题可以跳到任意祖先结点或者后代结点，其实不管是上面说的哪种情况都可以同样用判断图是否存在完美匹配解得。
  
### 两种情况：

1. 存在完美匹配：那么不管 Alice 从哪个点起步， Bob 都可以找到该点的匹配点并染色，这样下来最先无法染色的一定是 Alice。

2. 不存在完美匹配：那么 Alice 可以选择不在最大匹配中的点起步，假设起始点为 $a1$ ，Bob 走的下一步为 $b1,b1$ 其实必在最大匹配中，因为如果不在，那么 $(a,b)$ 又构成一个匹配，与最大匹配矛盾。那么接下来 Alice 就可以采取第一种情况中 Bob 的操作，因为 Bob 接下来是无法到达最大取匹配外的点的(假设 $b3$ 在最大匹配外，那么匹配 $(a1,b1)$ ， $(a2,b2),(a3,b3)$ 一直这样，这样的匹配数一定大于最大匹配 $(b1,a2),(b2,a3)$ ，后边都一样)，所以 Alice 只要走最大匹配外的点，接下来 Bob 只能走最大匹配内的点，类似于第一种情况只不过 Bob 先手，所以 Alice 必赢。

## CODE

```c
#include <bits/stdc++.h>
using namespace std;
#define ms(a, x) memset(a, x, sizeof(a))
#define fore(i, a, n) for (ll ll i = a; i < n; i++)
#define ford(i, a, n) for (ll ll i = n - 1; i >= a; i--)
#define si(a) scanf("%d", &a)
#define sl(a) scanf("%lld", &a)
#define sii(a, b) scanf("%d%d", &a, &b)
#define siii(a, b, c) scanf("%d%d%d", &a, &b, &c)
#define sll(a, b) scanf("%lld%lld", &a, &b)
#define slll(a, b, c) scanf("%lld%lld%lld", &a, &b, &c)
#define debug(a) cout << a << endl
#define pr(a) printf("%d ", a)
#define endl '\n'
#define pi acos(-1.0)
#define tr t[root]
#define IO ios::sync_with_stdio(false), cin.tie(0)
#define ull unsigned long long
#define py puts("Yes")
#define pn puts("No")
#define pY puts("YES")
#define pN puts("NO")
#define re(i, a, b) for (int i = a; i <= b; ++i)
#define de(i, a, b) for (int i = a; i >= b; --i)
#define all(x) (x).begin(), (x).end()
#define ls(x) x.resize(unique(all(x)) - x.begin())
const double eps = 1e-8;
inline int sgn(const double &x) { return x < -eps ? -1 : x > eps; }
typedef long long ll;
const ll inf = 0x3f3f3f3f;
const int MAXN = 1e5 + 5;
template <class T>
inline void cmin(T &a, T b) { ((a > b) && (a = b)); }
template <class T>
inline void cmax(T &a, T b) { ((a < b) && (a = b)); }
const ll mode = 20090126;
int f[MAXN];
vector<int> edge[MAXN];
void dfs(int x, int fa){
	for (auto to : edge[x]){
		if (to == fa)
			continue;
		dfs(to, x);
		f[x] += f[to];
	}
	if (f[x])
		f[x]--;
	else
		f[x] = 1;
}
int main(){
	int n;
	si(n);
	for (int i = 1; i < n; i++){
		int u, v;
		sii(u, v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1, 0);
	if (!f[1])
		printf("Bob\n");
	else
		printf("Alice\n");
	return 0;
}
```


### 完结撒花，谢谢！！！

---

## 作者：shuangmu (赞：1)

博弈论。

对于这种删点的题目，即走过一个点后该点不可再次经过，都可以这样考虑：如果这张图存在一个完美匹配，则后手必胜，否则先手必胜。

如果存在完美匹配，则无论先手选择哪个点，后手都可以选择该点的匹配点，这样最后的路径一定是一条交错边组成的路径，先手最后一定会无点可选；如果不存在完美匹配，找出这张图的最大匹配，先手可以选择一个未匹配的点为起点，这样后手一定会选择一个匹配上的点，这时候先手就可以去选择该点的匹配点，走一条交错边组成的路径。而且，这条路径上一定不会再有未匹配的点，否则就存在增广路，与最大匹配相矛盾。

至于树上的匹配，我们考虑贪心。如果点 $u$ 的子树内有未匹配的点，则点 $u$ 优先去匹配子树内的点；否则就上传，去匹配父节点。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+100;

int read() {
	int x = 0; char ch = getchar();
	while(ch<'0' || ch>'9') ch = getchar();
	while(ch>='0'&&ch<='9') x = x*10+(ch-48), ch = getchar();
	return x;
}
int head[N], tot;
struct node {
	int nxt, to;
} edge[N<<1];

void add(int u, int v) {
	edge[++tot].nxt = head[u];
	edge[tot].to = v;
	head[u] = tot;
}

int f[N];
void dfs(int u, int fath) {
	f[u] = 1;
	int sum = 0;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(v == fath) continue;
		dfs(v, u);
		if(f[u] && f[v]) {
			--f[u], --f[v];
		}
		sum+=f[v];
	}
	f[u]+=sum;
}

int n;

int main() {
	n = read();
	for(int i = 1; i<n; ++i) {
		int u = read(), v = read();
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	if(f[1]) puts("Alice");
	else puts("Bob");
	return 0;
}
```



---

## 作者：是个妹子啦 (赞：0)

#### 题意：

一张无向图， $Alice$选择从某处开始放一个棋子，然后 $Bob$ 和 $Alice$ 依次移动这个棋子，但是不能走到到过的地方，无法操作者败。

假如做过P1623，~~可能会联想到~~要找树的匹配

分类讨论

假如树是完美匹配的，后手只要走先手的完美匹配点即可，先手会失败

树没有完美匹配，找出树的最大匹配$(1,2),(3,4)$，假如先手从一个没在最大匹配的点开始，后手不可能再走到一个没有在最大匹配的点，先后手转换

令$f_x$表示$x$子树中多少点没有匹配即可

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
inline int read(){
	int x = 0;char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x;
}
const int N = 1e5 + 10;
struct edge{int to,next;}e[N<<1]; int head[N],tot,f[N];
inline void add(int u,int v){
	e[++tot] = (edge){v,head[u]}; head[u] = tot;
}
void dfs(int x,int fa){
	f[x] = -1;
	for(int i = head[x];i;i = e[i].next){
		int v = e[i].to;
		if(v == fa) continue;
		dfs(v,x); f[x] += f[v];
	}
	if(f[x] < 0) f[x] = -f[x];
}
int main(){
	int n;scanf("%d",&n);int u,v;
	for(int i = 1;i < n;++i){
		u = read(); v = read();
		add(v,u); add(u,v);
	} dfs(1,0);
	puts(f[1] ? "Alice" : "Bob");
}
```



---

