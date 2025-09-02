# Vlad and Trouble at MIT

## 题目描述

Vladislav 有一个儿子，非常想去 MIT。MIT（摩尔多瓦理工学院）的学生宿舍可以用一棵有 $n$ 个顶点的树来表示，每个顶点代表一个房间，且每个房间里正好有一名学生。一棵树是一个有 $n$ 个顶点和 $n-1$ 条边的连通无向图。

今晚有三类学生：

- 想要开派对并播放音乐的学生（用 $\texttt{P}$ 标记）；
- 想要睡觉并享受安静的学生（用 $\texttt{S}$ 标记）；
- 不在乎的学生（用 $\texttt{C}$ 标记）。

最初，所有的边都是薄墙，音乐可以穿透薄墙传播，所以当某个开派对的学生播放音乐时，所有房间都能听到。然而，我们可以在任意边上安装厚墙——厚墙可以阻挡音乐的传播。

学校希望安装一些厚墙，使得每个开派对的学生都能播放音乐，但没有任何想睡觉的学生能听到音乐。

由于学校在冠名权诉讼中损失了大量资金，他们希望你帮忙计算需要使用的最少厚墙数量。

## 说明/提示

在第一个样例中，我们可以在房间 $1$ 和 $2$ 之间安装一堵厚墙，如下图所示。不能不安装墙，否则房间 $3$ 的音乐会传到房间 $2$，而房间 $2$ 的学生想要睡觉，所以答案是 $1$。当然，也存在其他可行方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1926G/db6834436606f869a9404c7ce68aa100c7fe544a.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3
1 1
CSP
4
1 2 2
PCSS
4
1 2 2
PPSS```

### 输出

```
1
1
2```

# 题解

## 作者：yyrwlj (赞：9)

## 思路

树形 dp 板子题。

定义状态 $f_{u,0/1}$ 表示把点 $u$ 看作 P 或 S 的最小花费。

这个状态是针对 C 类型定义的，因为 P 和 S 只能看作它们本身，如果当前点是 P 或 S，那就把这个点对应的另外一种类型的 dp 值设为正无穷。

然后对于每个节点的直接相连的点（除父节点），要么跟当前节点看作的类型相同，或者不同，但是代价要加一，两者取较小值即可。

以任意节点为根节点开始 dp，最后的答案就是选定的根节点的两种可能类型的较小值。

## Code

```cpp
#include <iostream>
using namespace std;
const int N = 100005;
struct Edge{
    int to, nxt;
}g[N << 1];
int h[N], idx;
int f[N][2];
char s[N];
void add(int a,int b)
{
    g[++idx].to = b, g[idx].nxt = h[a], h[a] = idx;
}
void dfs(int u,int fa)
{
    f[u][0] = f[u][1] = 0;
    for (int i = h[u]; i; i = g[i].nxt)
    {
        int j = g[i].to;
        if (j == fa)
            continue;
        dfs(j, u);
        f[u][0] += min(f[j][0], f[j][1] + 1);
        f[u][1] += min(f[j][1], f[j][0] + 1);
    }
    if (s[u] == 'P')
        f[u][1] = 1e9;
    else if (s[u] == 'S')
        f[u][0] = 1e9;
}
void work()
{
    int n;
    scanf("%d", &n);
    for (int i=1;i<=n;i++)
        h[i] = 0;
    idx = 0;
    for (int i=2;i<=n;i++)
    {
        int a;
        scanf("%d", &a);
        add(i, a);
        add(a, i);
    }
    scanf("%s", s + 1);
    dfs(1, 1);
    printf("%d\n", min(f[1][0], f[1][1]));
}
int main()
{
    int T;
    cin >> T;
    while (T--)
        work();
    return 0;
}
```

---

## 作者：ydc66 (赞：3)

[题目链接](https://codeforces.com/problemset/problem/1926/G)  

### 题目描述  
给定一棵包含 $n$ 个节点的树结构，每个节点标记为 $\text{C}$（普通）、$\text{S}$（需要安静）或 $\text{P}$（播放音乐）。要求删除最少的边，使得任意连通块中不同时存在 $\text{S}$ 和 $\text{P}$ 类型节点。求最少需要删除的边数。  

### 思路  
将树分割为若干子树，最终每个连通块只能是以下三种情况之一：  
  • 仅含 $\text{S}$ 和 $\text{C}$ 节点。  
  • 仅含 $\text{P}$ 和 $\text{C}$ 节点。  
  • 仅含 $\text{C}$ 节点。  
  • 等价于将树分割为两个超集：$\text{S}$-集合 和 $\text{P}$-集合。  

需要找到某种划分方式使得需要删除的边最少，考虑最小割。  

### 建图方法  
定义虚拟源点 $S$ 和汇点 $T$：  
   • $\text{S}$ 节点必须与源点连通。  
     → $S$ 向所有 $\text{S}$ 节点连容量 $\infty$ 的边。  
   • $\text{P}$ 节点必须与汇点连通。  
     → 所有 $\text{P}$ 节点向 $T$ 连容量 $\infty$ 的边。  
   • 原树边建立双向容量 $1$ 的边（割断代价为 $1$）。  

最小割值即为使 $\text{S}$ 集合与 $\text{P}$ 集合完全隔离的最小删除边数。  

### 复杂度分析  
• **时间复杂度**：$O(n\sqrt{n})$。  
  Dinic 算法在单位容量网络中的优异表现。  
• **空间复杂度**：$O(n)$。  

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct MaxFlow {        // 基于Dinic
	const int inf = 1e9;// 常量
	// 链式前向星
	struct edge {
		int ne, to;
		T cap;// 容量
	};
	vector<int> h;
	int idx = 1;// 注意idx一定得从1开始
	MaxFlow() {}
	MaxFlow(int _n) {
		set_size(_n);
	}
	int s, t;           // 源点 汇点
	int n;              // 点数
	vector<edge> e;     // 存图
	vector<int> de, cur;// 深度 当前弧优化
	void _add(int u, int v, T cap) {
		++idx;
		e.push_back({h[u], v, cap});
		h[u] = idx;
	}
	void add(int u, int v, T cap) {
		_add(u, v, cap);
		_add(v, u, 0);// 建反边
	}
	void set_size(int _n) {
		n = _n;
		h.assign(n + 50, 0);
		idx = 1;
		e.resize(2);// 初始化为2，因为idx从1开始
		de.assign(n + 50, inf);
		cur.assign(n + 50, 0);
	}
	//
	bool bfs() {// 构建分层图
		//每个节点层次初始化
		for (int i = 1; i <= n; i++) de[i] = inf;
		queue<int> q;
		q.push(s);
		de[s] = 0;//源点初始化为1
		cur[s] = h[s];

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int i = h[u]; i; i = e[i].ne) {
				int v = e[i].to;
				//找有剩余流量且未被访问过的边
				if (e[i].cap > 0 && de[v] == inf) {
					q.push(v);
					cur[v] = h[v];
					de[v] = de[u] + 1;//分层
					//如果到达汇点，进行dfs
					if (v == t) return true;
				}
			}
		}
		return false;
	}
	T dfs(int u, T sum) {
		if (u == t) return sum;
		//sum是流入这个点的流量
		T flow = 0;// flow是流出的流量
		//注意流量不能为负数
		for (int i = cur[u]; i && sum > 0; i = e[i].ne) {
			cur[u] = i;
			int v = e[i].to;
			if (e[i].cap > 0 && (de[v] == de[u] + 1)) {
				T k = dfs(v, min(sum, e[i].cap));//增广
				if (k == 0) de[v] = inf;
				e[i].cap -= k;    //正边减
				e[i ^ 1].cap += k;//反边加
				flow += k;
				sum -= k;
			}
		}
		return flow;
	}
	T Dinic() {
		T flow = 0;
		while (bfs()) {
			flow += dfs(s, inf);
		}
		return flow;
	}
};
void _solve() {
	const int inf = 1e9;
	int n;
	cin >> n;
	MaxFlow<int> f(n + 2);
  // n+2为源点，n+1为汇点
	int s = n + 2, t = s - 1;
	f.s = s, f.t = t;
  // 连树边（注意是双向边）
	for (int i = 2; i <= n; i++) {
		int x;
		cin >> x;
		f.add(i, x, 1);
		f.add(x, i, 1);
	}
	for (int i = 1; i <= n; i++) {
		char x;
		cin >> x;
		if (x == 'S') f.add(s, i, inf);
		if (x == 'P') f.add(i, t, inf);
	}
	cout << f.Dinic() << endl;
}

int main() {
	int T = 1;
	cin >> T;

	while (T--) _solve();
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：3)

## 题目大意

给定一个带点权的树，点权为 `C`、`S`、`P` 的任意一个。请你删掉最小数量的边，使得 `S` 和 `P` 不连通。输出最小数量。

- 题外话

同学们不要误会，点权不是在引用某个比赛的简称，而是分别代表：

1. `C`：don't **C**are.
2. `S`：enjoy **S**ilence.
3. `P`：**P**arty and **P**lay music.

## 题目分析

显然是要树形 dp。考虑 $f_{i,0/1,0/1}$ 表示 $i$ 的子树已经满足条件，是否有 `S` 与 $i$ 父亲依旧连通，是否有 `P` 与 $i$ 的父亲依旧连通的最小删边数。

转移很简单，处理到 $x$ 时，枚举 $x$ 的儿子 $y$ 与两者的状态，如果两者状态矛盾，则断掉边 $(x,y)$ ，即转移时加上 $1$，否则直接转移。

初始化就根据节点的点权而定。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N =1e5+5;
int n,h[N],to[N],nxt[N],cnt;
void add_(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
int f[N][2][2]; 
string s;
void dp(int x){
	memset(f[x],0,sizeof(f[x]));
	if(s[x]=='S')f[x][0][1]=f[x][0][0]=n+1;
	if(s[x]=='P')f[x][1][0]=f[x][0][0]=n+1;
	e(x){
		dp(y);
		if(s[x]=='P'){
			f[x][0][1]+=min({f[y][1][0]+1,f[y][0][1],f[y][0][0]});
		}
		if(s[x]=='S'){
			f[x][1][0]+=min({f[y][1][0],f[y][0][1]+1,f[y][0][0]});
		}
		if(s[x]=='C'){
			f[x][0][0]+=min({f[y][1][0]+1,f[y][0][1]+1,f[y][0][0]});
			f[x][1][0]+=min({f[y][0][0],f[y][1][0],f[y][0][1]+1});
			f[x][0][1]+=min({f[y][0][0],f[y][1][0]+1,f[y][0][1]});
		}
	}
}
void clear(){
	repn(i)h[i]=0;
	cnt=0;
}
void Main(){
	n=read();
	rep(i,2,n)add_(read(),i);
	cin >>s,s='#'+s;
	dp(1);
	cout <<min({f[1][1][0],f[1][0][0],f[1][0][1]})<<'\n';
	clear();
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}
```


---

## 作者：kaikatandy (赞：1)

# CF1926G
- 树形 DP。S 和 P 都只有一种状态，C 有两种状态。状态对应的值是这个子树最少需要放多少堵墙。
- 枚举当前节点的状态，从儿子转移过来（求和），如果当前的状态与儿子的状态不一样，就要在这条边上放一堵墙（当前状态对应的值再加一）。
# 代码
- 对于 S、P 不存在的状态，赋一个极大值即可。
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
/*
Face the Fear, Make the Future.
FILE OPERATION IF NEEDED!!!
Problem: G. Vlad and Trouble at MIT
*/

const int N = 1e5 + 7;
vector<int> g[N];
int dp[N][2];
char sta[N];

void dfs(int u, int fa){
    if(sta[u] == 'P') dp[u][1] = 0;
    else if(sta[u] == 'S') dp[u][0] = 0;
    else dp[u][0] = dp[u][1] = 0;
    for(int v: g[u]) if(v != fa){
        dfs(v, u);
        if(sta[u] != 'S') dp[u][1] += min(dp[v][0] + 1, dp[v][1]);
        if(sta[u] != 'P') dp[u][0] += min(dp[v][1] + 1, dp[v][0]);
    }
}

void solve(){
    int n;
    cin >> n;
    memset(dp, 0x3f, sizeof dp);
    for(int i = 1; i <= n; i ++){
        g[i].clear();
    }
    for(int i = 2; i <= n; i ++){
        int a;
        cin >> a;
        g[i].push_back(a);
        g[a].push_back(i);
    }
    for(int i = 1; i <= n; i ++) cin >> sta[i];
    dfs(1, 0);
    cout << min(dp[1][0], dp[1][1]) << "\n";
}

int main(){
    int t;
    cin >> t;
    while(t --){
        solve();
    }
    return 0;
}
```

---

## 作者：一只小咕咕 (赞：1)

[题目传送门](https://codeforces.com/contest/1926/problem/G)

#### 思路
发现权值为 `C` 的点可以选择看做是权值为 `S` 或为 `P` 的点，所以问题转换为怎么给 `C` 点赋值可以使答案最小，考虑树形 dp。

$f_{i,0/i,1}$ 表示 $i$ 点赋值为 `S` 或 `P` 时最少要删除几条边。但如果当前点权值不为 `C` 的话，那显然他的父亲节点应该选择和他权值相同的点才最优，所以可以把权值相反时的 $f_i$ 赋值为一个很大的数，这样就不会被选择了。

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int inf=0x3f3f3f3f;
inline int read();
int T,n,a[N],cnt,head[N],f[N][2];
bool vis[N]; 
struct E{
	int to,next;
}edge[N<<1];
void add(int u,int v)
{
	edge[++cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
void dfs(int x)
{
	vis[x]=1;
	for(int i=head[x];i;i=edge[i].next)
	{
		int to=edge[i].to;
		if(vis[to]) continue;
		dfs(to);
		f[x][0]+=min(f[to][0],f[to][1]+1);
		f[x][1]+=min(f[to][1],f[to][0]+1);
	}
	if(a[x]==1) f[x][0]=inf;
	else if(a[x]==-1) f[x][1]=inf;
}
int main()
{
	T=read();
	for(int d=1;d<=T;d++)
	{
		cnt=0;
		memset(head,0,sizeof head);
		memset(a,0,sizeof a);
		memset(vis,0,sizeof vis);
		for(int i=1;i<=n;i++) f[i][0]=f[i][1]=0;
		n=read();
		for(int i=2;i<=n;i++)
		{
			int x;
			x=read();
			add(i,x);
			add(x,i);
		}
		for(int i=1;i<=n;i++)
		{
			char ch;
			cin>>ch;
			if(ch=='S') a[i]=1;
			else if(ch=='P') a[i]=-1;
		}
		dfs(1);
		printf("%d\n",min(f[1][0],f[1][1]));
	}
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')
	{
		x=(x<<1)+(x<<3)+(ch&15);
		ch=getchar();
	}
    return x*f;
}
```

---

## 作者：Yharimium (赞：1)

题目链接：[CF1926G](https://www.luogu.com.cn/problem/CF1926G)

## 题目大意

给定一棵 $n$ 个节点 $n-1$ 条边的树。树上的节点有 S,P,C 三种类型。现要求 S 和 P 之间不能联通，问最少删除几条边。

## 方法

容易发现每个 C 都可以看作 S 或 P。在此基础上使用树形 DP。

设计状态：
- $f[x][0]$：把节点 $x$ 视作 S 时，在以 $x$ 为根的子树中最少要删的边数
- $f[x][1]$：把节点 $x$ 视作 P 时，在以 $x$ 为根的子树中最少要删的边数

如果节点 $x$ 本就是 S（或 P），与状态的描述不符，此时令 $f[x][1]$（或 $f[x][0]$）等于一个很大的数即可。

若父节点和子节点类型不同，则其之间的边必须删除；若相同则没必要删。据此写出状态转移方程：

$$f[x][t]=\sum_{v\in \text{Son}(x)}\min(f[v][t],f[v][!t]+1)$$

任取一节点作为根节点，采用记忆化搜索。

## 代码

``` cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5 + 1;
char type[N];
int n;
vector<int> g[N];
 
int F[N][2];
 
int f(int x, bool t, int fa = 0) {
	if (F[x][t])
		return F[x][t];
	
	if (t && type[x] == 'P' || !t && type[x] == 'S')
		return 1e9;
	
	for (const auto& i : g[x]) {
		if (i == fa) continue;
		
		F[x][t] += min(f(i, t, x), f(i, !t, x) + 1);
	}
	
	return F[x][t];
}
 
int main() {
	
	int t;
	scanf("%d", &t);
	
	for (; t --; ) {
		scanf("%d", &n);
		
		for (int i = 2; i <= n; i ++) {
			static int x;
			scanf("%d", &x);
			g[i].push_back(x);
			g[x].push_back(i);
		}
		
		scanf("%s", type + 1);
		
		memset(F, 0, sizeof F);
		
		int result = min(f(1, false), f(1, true));
		
		printf("%d\n", result);
		
		for (int i = 1; i <= n; i ++)
			g[i].clear();
	}
	
	return 0;
}
```

---

