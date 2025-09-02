# Labyrinth

## 题目描述

Leslie and Leon entered a labyrinth. The labyrinth consists of $ n $ halls and $ m $ one-way passages between them. The halls are numbered from $ 1 $ to $ n $ .

Leslie and Leon start their journey in the hall $ s $ . Right away, they quarrel and decide to explore the labyrinth separately. However, they want to meet again at the end of their journey.

To help Leslie and Leon, your task is to find two different paths from the given hall $ s $ to some other hall $ t $ , such that these two paths do not share halls other than the staring hall $ s $ and the ending hall $ t $ . The hall $ t $ has not been determined yet, so you can choose any of the labyrinth's halls as $ t $ except $ s $ .

Leslie's and Leon's paths do not have to be the shortest ones, but their paths must be simple, visiting any hall at most once. Also, they cannot visit any common halls except $ s $ and $ t $ during their journey, even at different times.

## 样例 #1

### 输入

```
5 5 1
1 2
2 3
1 4
4 3
3 5```

### 输出

```
Possible
3
1 2 3
3
1 4 3```

## 样例 #2

### 输入

```
5 5 1
1 2
2 3
3 4
2 5
5 4```

### 输出

```
Impossible```

## 样例 #3

### 输入

```
3 3 2
1 2
2 3
3 1```

### 输出

```
Impossible```

# 题解

## 作者：jianhe (赞：7)

[CF1666L Labyrinth](https://www.luogu.com.cn/problem/CF1666L)
题解

### 算法：回溯

一道搜索的好题。

当搜到一个点已经被访问过时，就说明可能是找到了两条路径，输出答案即可。如果这个点只是重复点，说明这种方法不可行。回溯即可。

### 注意点：

1. 有向图！

2. 输出时要倒着输出，因为存储时是反着来的。

3. 输出第一行要大写。


### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+10;
ll n,m,s,u,v,v1,v2,ans,ans1[N],ans2[N],vis[N],fa[N];
vector<ll> e[N];
void Ans(ll u,ll f){
	ans2[++v2]=u;
	for(int i=u;i!=s&&fa[i]!=i;i=fa[i]) ans1[++v1]=i;
	for(int i=f;i!=s&&fa[i]!=i;i=fa[i]) ans2[++v2]=i;
	ans1[++v1]=s,ans2[++v2]=s;
}
void pr(){
	cout<<"Possible\n";
	cout<<v1<<"\n";
	for(int i=v1;i>=1;i--) cout<<ans1[i]<<" ";
	cout<<"\n"<<v2<<"\n";
	for(int i=v2;i>=1;i--) cout<<ans2[i]<<" ";
	exit(0);//结束程序 
}
void dfs(ll u,ll f){
	if(u==s) return;
	if(vis[u]){
		if(vis[u]!=ans) Ans(u,f),pr();
		return;
	}
	vis[u]=ans,fa[u]=f;
	for(auto v:e[u]) dfs(v,u);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m>>s;
    while(m--) cin>>u>>v,e[u].push_back(v);
	for(auto v:e[s]) ans=v,dfs(v,s);
	cout<<"Impossible";
	return 0;
}

```

---

## 作者：晨曦墨凝 (赞：2)

题目要求从点 $A$ 出发，是否存在另一个终点 $B$，使得 $A$ 到 $B$ 的路径不重复。

本题与路径有关，考虑可以遍历边的算法，同时注意到，题目中 $0 \leq m \leq 2 \cdot 10^{5}$，故应设计出 $O(m \log m)$ 及更快的算法。

------------

可以看一下样例一，找找灵感。

![](https://cdn.luogu.com.cn/upload/image_hosting/2ddfd4wq.png)

第一条路径：$1 \to 2 \to 3$。

第二条路径：$1 \to 4 \to 3$。

找到终点的标准，就是第一条路径与第二条路径能共同遍历到该点，这不就是搜索中的 $vis$ 标记嘛。但是，怎么回溯寻找答案呢？将没有路径压缩的并查集中的 $fa$ 魔改一下即可。好了，确定使用广搜算法。

------------

但是，出题人非常良心，样例二与样例三给了我们两种坑点。

先看样例二

![](https://cdn.luogu.com.cn/upload/image_hosting/2wdqi9cy.png)

显然，如果我们只维护一个 $fa$ 是不行的，虽然是有两条路能到达 $4$ 号节点，但是不难发现 $2$ 是重复经历的，那么维护一个数组来维护路径的特征。出发点是所有都要经过的，这个特征太普遍了，但是根据定义，出发点下一个节点是每条正确路径独一无二的特征，很好我们维护一个数组 $root$，$root_i$ 表示经过节点 $i$ 的路径的出发点的下一个节点，问题便解决了。

------------

再看样例三

![](https://cdn.luogu.com.cn/upload/image_hosting/mxth8o0u.png)

这是一个环，需要我们在原维护的数组上加点小细节。$s$ 为出发点，它不能被塞入队列，那么就把$fa_s$ 在初始时赋值为 $-1$。（若你想出来的写法与我的不同，可能不用考虑）

------------

广搜时，每条边至多被遍历一次，那么复杂度应该是 $O(m)$ 的。

```
#include <iostream>
#include <cstdio>
#include <queue>
#define MAXN 200005
using namespace std;

int n, m, s;
struct edge
{
    int v, nxt;
}G[MAXN];
int head[MAXN], cntEdge;
int fa[MAXN], root[MAXN];   // 维护父节点与根节点（搜索出发点）
int ans[MAXN], cnt;

int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

void addEdge(int u, int v)
{
    ++cntEdge;
    G[cntEdge].v = v;
    G[cntEdge].nxt = head[u];
    head[u] = cntEdge;
}

void init()
{
    n = read(), m = read(), s = read();
    for (int i = 1; i <= m; ++i)
    {
        int u = read(), v = read();
        addEdge(u, v);
    }
}

void outPut(int u, int v)
{
    printf("Possible\n");
    while (fa[v] != -1)
    {
        ans[++cnt] = v;
        v = fa[v];
    }
    ans[++cnt] = s;
    printf("%d\n", cnt);
    for (int i = cnt; i; --i)
        printf("%d ", ans[i]);
    printf("\n");

    cnt = 1;    // ans[1] 即为 v
    while (fa[u] != -1)
    {
        ans[++cnt] = u;
        u = fa[u];
    }
    ans[++cnt] = s;
    printf("%d\n", cnt);
    for (int i = cnt; i; --i)
        printf("%d ", ans[i]);
    exit(0);
}

void BFS()
{
    queue <int> q;
    fa[s] = -1;
    for (int i = head[s]; i; i = G[i].nxt)
    {
        int v = G[i].v;
        fa[v] = s;
        root[v] = v;
        q.push(v);
    }
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = G[i].nxt)
        {
            int v = G[i].v;
            if (fa[v] > 0 && root[v] != root[u])    // 若父节点为-1，则是环，若父节点是0，则表示未遍历。
                outPut(u, v);
            if (fa[v] == 0)
            {
                fa[v] = u;
                root[v] = root[u];
                q.push(v);
            }
        }
    }
}

void solve()
{
    BFS();
    printf("Impossible");
}

int main()
{
    init();
    solve();
    return 0;
}
```


---

## 作者：JCLinux (赞：2)

**题目要求：**

从给定的起点出发，尝试找到一个终点，满足以下的条件：

1. 从起点到终点有两条不同的路径。

2. 除了起点之外，这两条路径不存在任何公共的点。

3. 每条路径自身不存在重复的点。

如果存在这样的终点，输出 possible，并且分别输出这两条路径，否则输出 impossible


**思路：**

从起点的下一个点出发，这个点作为当前路径的根节点，开始 dfs。对于不同的根节点，如果到达了同一个点，说明一定存在满足条件的终点。

**特别注意的一点是**：找第一个从两个根都能到达的终点，不是第一个的话可能会导致路径重复。

因为是两条没有重复点的不同路径，因此除了终点之外**路径**上的任何一个点都只有一个父节点。

因此，总体做法：

在 dfs 的过程中只需要维护每个点的父节点就好，遇到之前已经访问过的点，看这个点的根节点是不是当前这条路径的根节点，是的话就剪掉这个点，因为路径总不能有重复的点。不是的话，这个点就是答案了。对于这个点，他有两个父节点，单独开一个变量存一下就好，其他点就只有一个父节点，用递归回溯答案就好。

还有一点强调的就是，在 dfs 找点的过程中，特判一下起点。


**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, s, another;
int flag;//终点
vector<int> edge[200005];
int R[200005];//每个节点的根节点
int fa[200005];//每个节点的父节点
vector<int>ans[2];//两条路径
void fans(int s, int i, int way)//答案回溯
{
	ans[way].push_back(i);
	if(i == s) return;
	fans(s, fa[i], way);
}
void dfs(int i, int root, int f)//dfs 找点
{
	if(i==s) return;//特判起点
	if(flag) return;//已经找到答案就不需要任何操作了
	if(R[i])//当前点已经访问过了，他就有希望成为答案节点
	{
		if(R[i] != root)//不是一条路径上的重复节点，那他就是答案了
		{
			flag = i;
			another = f;
		}
		return ;
	}
	R[i] = root;
	fa[i] = f;
	for(auto x : edge[i]) dfs(x, root, i);
}
int main()
{
	cin.sync_with_stdio(false);
	cin >> n >> m >> s;
	for(int i = 1; i <= m; i++)
	{
		int f, t;
		cin >> f >> t;
		edge[f].push_back(t);
	}
	for(int i = 0; i < (int)edge[s].size(); i++) dfs(edge[s][i], edge[s][i], s);
	if(flag)
	{
		cout << "Possible\n";
		ans[0].push_back(flag);
		ans[1].push_back(flag);
		fans(s, fa[flag], 0);
		fans(s, another, 1);
		reverse(ans[0].begin(), ans[0].end());
		reverse(ans[1].begin(), ans[1].end());
		cout << ans[0].size() << '\n';
		for(auto x : ans[0]) cout << x << ' ';
		cout << '\n' << ans[1].size() << '\n';
		for(auto x : ans[1]) cout << x << ' ';
	}
	else cout << "Impossible";
	return 0;
}

```


---

## 作者：xgyxgy111 (赞：1)

给一份比较容易理解的题解？

首先题目已经告诉你了这是一个有向无环图，也不会是基环树，那么一些奇奇怪怪的动态规划拓扑就可以不用考虑了。

我们看第一个样例，图是这样的，其中 $1$ 是起点。
![](https://cdn.luogu.com.cn/upload/image_hosting/l4ilrzci.png)

那么从 $1$ 走到 $3$ 显然有两条不同的路径，那么我们是如何确定这两条路径的呢，很简单因为这两条路径都要从起点出发，并且 **中间不能经过相同的节点** 那么我们想这个限制条件其实是不完整的，如果你从起点走，**已经有两条不同路径**了那么这个时候再经过相同的节点，我们直接**把相同的节点作为终点**不就可以了吗。

所以现在问题就变成了从起点走，你能不能找到两条或以上不同的路径最后汇合到一个点上。

那很显然的就一个 bfs，接下来的问题就是如何去判断两条路径不同，以及不同的路径如何汇合到相同的节点上，我们可以采用染色法，把起点有向边连接的若干点都染上不同的颜色，然后开始 bfs，如果有两个不同颜色相遇了，那么就代表我们找到了一个合法的终点。

最后一个问题，路径怎么存，你会发现你在图上跑 bfs 边跑边标记其实把图剖分成了若干个树，所以你每次 bfs 到新的点去记录一下他的父节点就行了。

特别的，考虑这个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/q5f530d9.png)


$1$ 是起点，你染色完直接跑 bfs 会回到起点，所以要特判一下，代码如下，时间复杂度 $O(n+m)$。

```
#include <bits/stdc++.h>

using namespace std;
using PII=pair<int,int>;

const int N=200010*4;

int n,m,s;
PII edge;
int color[N],pre[N];
int e[N],ne[N],h[N],idx;

void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

bool bfs(){
	queue<int> q;
	int c=1;
	for(int i=h[s];~i;i=ne[i]){
		int j=e[i];
		color[j]=c++;
		
		pre[j]=s;
		q.push(j);
	}
	
	bool flag=0;
	while(q.size()){
		auto t=q.front();
		q.pop();
		
		for(int i=h[t];~i;i=ne[i]){
			int j=e[i];
			if(j==s) continue;
			if(color[j]&&color[j]!=color[t]){
				flag=1;
				edge={t,j};
				continue;
			}
			if(color[j]) continue;
			
			color[j]=color[t];	
			pre[j]=t;
			q.push(j);
		}
	}
	
	return flag;
}

void solve(){
	cin>>n>>m>>s;
	for(int i=1;i<=n;i++) h[i]=-1;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
	}
	
	if(!bfs()){
		cout<<"Impossible"<<endl;
		return;
	}
	
	cout<<"Possible"<<endl;
	stack<int> sta1,sta2;
	
	int t=edge.first;
	sta1.push(edge.second);
	while(t!=s) sta1.push(t),t=pre[t];
	sta1.push(s);
	
	t=edge.second;
	while(t!=s) sta2.push(t),t=pre[t];
	sta2.push(s);
	
	cout<<sta1.size()<<endl;
	while(sta1.size()) cout<<sta1.top()<<' ',sta1.pop();
	cout<<endl;
	
	cout<<sta2.size()<<endl;
	while(sta2.size()) cout<<sta2.top()<<' ',sta2.pop();
	cout<<endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--) solve();
	return (0-0);
}

```

审核大大辛苦了，求通过~

---

## 作者：hzjnsy (赞：1)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17718396.html)**

**[题目传送门](https://www.luogu.com.cn/problem/CF1666L)**

> - 给出 $n$ 个点 $m$ 条边的有向图，以及一个起点 $s$。问是否能找到两条从 $s$ 出发的不同的路径，满足：
>
>    - 两条路径在同一个点结束。
>
>    - 两条路径除起点、终点外不相交。
>
>    - 每一条路径不经过重复的点。
>
>    称两条路径是不同的，当且仅当它们经过的点数不同，或存在 $i$ 使得第一条路径的第 $i$ 个点与第二条路径的第 $i$ 个点不同。有解时输出方案。
>
> - $n,m\le 2\times 10^5$。

先考虑什么时候一定无解，显然 $s$ 的出度小于 $2$。

否则，两条路径一定是从 $s$ 的两个后继出发，到达某个相同的点，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/f6pyubjg.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

进一步思考，这个形态即为图的一棵搜索树，而若要满足条件，则说明必须存在一条**横跨两个后继子树的横叉边**。所以先以 $s$ 为根找出一棵搜索树，然后记录每个点 $u$ 的父亲 $fa_u$。

我们对每个后继的子树用一种**独一无二的颜色染色**，若遍历当前点 $u$ 边集的过程中发现与自己颜色不同的点（记为 $v$），则说明存在一条这样的横叉边，所求路径即为 $s\rightsquigarrow v$ 和 $s\rightsquigarrow u \rightarrow v$，记录一下这两个点即可。不要像某个人一样忘记了 **$\boldsymbol{s}$ 到后继的边也可以成为横叉边**。若不存在这样的 $u,v$ 则无解。然后你发现这样包含了 $s$ 的出度小于 $2$ 的情况。  

输出方案的时候，先递归输出自己父亲的路径，再输出自己。**第二条路径不要忘记输出点 $\boldsymbol{v}$**，因为横叉边的结尾是 $v$。

时间、空间复杂度均为 $\mathcal{O}(n+m)$。

**[评测记录](https://codeforces.com/problemset/submission/1666/224164546 "评测记录")**

```cpp
#include <bits/stdc++.h>
using namespace std; const int N = 2e5 + 5;
int n, m, s, col[N], cnt, fa[N], p1, p2, tot; vector<int> g[N]; bool op, vis[N];
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - 48; x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
void init(int u) { 
    vis[u] = 1; for (int v : g[u]) if (!vis[v]) fa[v] = u, init(v);
}
void dfs(int u, int c) {
    if (col[u] != -1 && !op) p1 = u, p2 = s, op = 1; col[u] = c; 
    for (int v : g[u]) {
        if (col[v] == c || !col[v]) continue;
        if (col[v] == -1) dfs(v, c); else if (!op) p1 = v, p2 = u, op = 1; 
    }
}
void find(int u) { 
    if (u != s) ++tot, find(fa[u]); else print(tot); print(u, ' '); 
}
signed main() {
    read(n), read(m), read(s); memset(col, -1, sizeof col);
    for (int i = 1, u, v; i <= m; ++i) read(u), read(v), g[u].emplace_back(v);
    col[s] = 0; init(s); for (int v : g[s]) dfs(v, ++cnt);
    if (!p1 || !p2) return puts("Impossible"), 0; puts("Possible");
    tot = 1, find(p1); puts(""); tot = 2, find(p2), print(p1);
    return 0;
}
```

---

## 作者：Duawieh (赞：1)

看到题解池的各位写的都是CF的官方题解~~别打我，可能也有不是的~~，所以在这里提供一个基于二进制拆分的思路。

考虑对于一组 $s$、$t$，要令路径完全不同，必有从 $s$ 出发后到达的第一个点就不相同，那么根据这个前提，将与点 $s$ 直接相连的点进行二进制分组，那么必然存在某一次分组时，合法答案的路径被分入不同组。

所以每次分组后检查两组中是否各存在一条路径能够到达相同的点，则这个点就是我们要找的点 $t$，输出对应的路径即可。

至于公共点怎么找，以及路径怎么记录，染色加双端队列维护即可。

时间复杂度 $O(n\log_2n)$。

---

补充一下，二进制分组是基于不同整数的二进制表达一定不相同这个前提进行的分组方式。所以逐位判断某数的某位是`0`还是`1`，以此进行分组，那么必然不存在两个不同的整数在每一次分组时都处于同一组内（因为它们的异或结果不是零）。

---

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
//Labyrinth
const int maxn = (int)2e5 + 10;
bool vis[maxn], siv[maxn];
vector<int> ed[maxn];
vector<int> op[maxn];
deque<int> pth;
int n, m, s, t;
int cnt;

void dfs_1(int x) {
	if (vis[x] || x == s) return; vis[x] = true;
	for (int i = 0; i < ed[x].size(); i++) dfs_1(ed[x][i]);
}

bool dfs_2(int x) {
	if (x == s || siv[x]) return false;
	pth.push_back(x);
	siv[x] = true;
	if (vis[x]) {
		t = x;
		return true;
	}
	for (int i = 0; i < ed[x].size(); i++) 
		if (dfs_2(ed[x][i])) return true;
	pth.pop_back();
	return false;
}

inline bool ver_2(int x, int i) {
	if (cnt > 1) return false;
	return x == t && op[x][i] == s;
}

bool dfs_3(int x) {
	siv[x] = true;
	pth.push_back(x);
	if (x == s) return true;
	for (int i = 0; i < op[x].size(); i++) {
		if (siv[op[x][i]] || vis[op[x][i]] || ver_2(x, i)) continue;
		if (dfs_3(op[x][i])) return true;
	}
	pth.pop_back();
	return false;
}

bool check() {
	for (int k = 0; k < 32; k++) {
		for (int i = 0; i < ed[s].size(); i++) 
			if (ed[s][i] & 1 << k) dfs_1(ed[s][i]);
		for (int i = 0; i < ed[s].size(); i++) {
			if (ed[s][i] & 1 << k);
			else if (dfs_2(ed[s][i])) return true;
		}
		memset(vis, false, sizeof vis);
		memset(siv, false, sizeof siv);
	}
	return false;
}

void out_put() {
	int ans[maxn];
	
	while (pth.size()) {
		ans[++cnt] = pth.front();
		pth.pop_front();
	}
	
	memset(vis, false, sizeof vis);
	memset(siv, false, sizeof siv);
	
	printf("%d\n%d ", cnt + 1, s);
	for (int i = 1; i <= cnt; i++) printf("%d ", ans[i]);
	for (int i = 1; i < cnt; i++)  vis[ans[i]] = true;
	printf("\n");
	
	dfs_3(t);
	printf("%d\n", pth.size());
	while (pth.size()) {
		printf("%d ", pth.back());
		pth.pop_back();
	}
	
	return;
}

int main() {
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		ed[u].push_back(v);
		op[v].push_back(u);
	}
	
	if (check()) {
		printf("Possible\n");
		out_put();
	} else printf("Impossible");
	
	return 0;
}
```

---

## 作者：dreamsky (赞：1)

## 题目分析

题目要找的是从 $s$ 到 $t$ 的两条不相交路径，即两条路径中间没有重复顶点。首先考虑从 $s$ 出发的边到达的顶点，那么满足题目条件的两条路径一定会到达两个不同的顶点。我们可以先遍历以 $s$ 为起点的边，以每个终点为根分别进行 dfs，各得到一棵生成树。如果有两个生成树有重复的节点，那么我们就找到了问题一个解，否则就说明问题无解。

可以用一个 parent 数组保存每个顶点在生成树上的父节点。另外用一个 root 数组表示每个顶点所在生成树的根。在 dfs 遇到已有 parent 且 root 与当前 dfs 不同的顶点时，说明找到了一个解，此时分别输出这个顶点在两棵生成树上的路径即可。

另外，因为符合题目要求的路径不可能回到起点 $s$，dfs 构建生成树时需要排除顶点 $s$。

## 代码

```cpp
int n, m, s, par[200001], root[200001];
vector<int> g[200001];

void output(int v, int p) {
    stack<int> s1, s2;
    s2.push(v);
    while (v) {
        s1.push(v);
        v = par[v];
    }
    while (p) {
        s2.push(p);
        p = par[p];
    }
    // output s1 and s2
}

bool dfs(int v, int p, int r) {
    if (root[v] == r) {
        return false;
    }
    if (par[v]) {
        output(v, p);
        return true;
    }
    par[v] = p;
    root[v] = r;
    for (int i=0; i<g[v].size(); i++) {
        if (dfs(g[v][i], v, r)) return true; 
    }
    return false;
}

int main() {
    cin >> n >> m >> s;
    int a, b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;
        if (b == s) continue;
        g[a].push_back(b);
    }

    for (int i=0; i<g[s].size(); i++) {
        if (dfs(g[s][i], s, g[s][i])) {
            return 0;
        }
    }
    cout << "Impossible" << endl;
}
```


---

## 作者：guaidaokenan (赞：0)

#### 题目大意
题目要求从点 $A$ 出发到点 $B$ 存不存在有两种不相交的路径。
#### 算法
当一个点已经被访问过时，就说明有可能是找到了两条路径，输出答案即可。如果这个点被遍历了两次，说明这种方法不可行，回溯即可。
#### 重要细节
1. 此题目的图是有向图。
2. 输出的字符串注意大小写。
3. 注意输出顺序。
#### 给上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int s1,s2;
int ans,ans1[200005],ans2[200005];
int vis[200005],fa[200005];
vector<int> v[200005];//用动态数组存图
void check(int x,int y){
	ans2[++s2]=x;
	for(int i=x; i!=k&&fa[i]!=i; i=fa[i]){
		ans1[++s1]=i;
	} 
	for(int i=y; i!=k&&fa[i]!=i; i=fa[i]){
		ans2[++s2]=i;
	} 
	ans1[++s1]=k;
	ans2[++s2]=k;
}
void cmp(){
	printf("Possible\n");
	printf("%d\n",s1);
	for(int i=s1; i>=1; i--){
		printf("%d ",ans1[i]);
	}
	printf("\n%d\n",s2);
	for(int i=s2; i>=1; i--){
		printf("%d ",ans2[i]);
	}
	printf("\n");
	exit(0);
}
void dfs(int x,int y){
	if(x==k){
		return ;
	}
	if(vis[x]!=0){
		if(vis[x]!=ans){
			check(x,y);
			cmp();
		}
		return;
	}
	vis[x]=ans;
	fa[x]=y;
	for(int i=0; i<v[x].size(); i++){
		dfs(v[x][i],x);
	}
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	v[x].push_back(y);
	}
	for(int i=0; i<v[k].size(); i++){
		ans=v[k][i];
		dfs(v[k][i],k);
	}
	printf("Impossible\n");
	return 0;
}
```

---

## 作者：hyman00 (赞：0)

# CF1666L

~~这题很诡异。~~

这题大概是这个意思，就是我们从点出发随便找两个第一步走的是不一样的节点的路径，如果这两个路径出现了交点的话，那么我们就去这个交点为终点。可以满足题目条件。

于是我们分别没举第一步走哪些点，然后 dfs 一遍，把所有这个点能走到的目前没有染过色的点都染成这个点的标号，在这里如果某一次 dfs 到了一个染过其他颜色的点，说明我们就找到答案了。

这是只要对每一个点记录一下 dfs 是从哪儿转移到的，就能算出答案。

```c++
void dfs(int u,int ty){
	for(int i:v[u]){
		if(lst[i]!=0&&br[i]!=ty&&i!=s){
			vi path1;
			int x=i;
			while(x!=s){
				path1.pb(x);
				x=lst[x]-100;
			}
			path1.pb(x);
			reverse(all(path1));
			vi path2(1,i);
			x=u;
			while(x!=s){
				path2.pb(x);
				x=lst[x]-100;
			}
			path2.pb(x);
			reverse(all(path2));
			cout<<"Possible\n"<<sz(path1)<<"\n";
			rep(j,sz(path1))cout<<path1[j]+1<<" ";
			cout<<"\n"<<sz(path2)<<"\n";
			rep(j,sz(path2))cout<<path2[j]+1<<" ";
			exit(0);
		}
		else if(lst[i]==0){
			lst[i]=u+100;
			br[i]=ty;
			dfs(i,ty);
		}
	}
}
void run(){
	cin>>n>>m>>s;
	s--;
	rep(i,m){
		int x,y;
		cin>>x>>y;
		x--,y--;
		v[x].pb(y);
	}
	lst[s]=100+s;
	br[s]=-1;
	rep(i,sz(v[s])){
		if(lst[v[s][i]]!=0){
			cout<<"Possible\n2\n"<<s+1<<" "<<v[s][i]+1<<"\n";
			vi path(1,v[s][i]);
			int x=v[s][i];
			while(x!=s){
				x=lst[x]-100;
				path.pb(x);
			}
			reverse(all(path));
			cout<<sz(path)<<"\n";
			rep(i,sz(path))cout<<path[i]+1<<" ";
			cout<<"\n";re;
		}
		lst[v[s][i]]=s+100;
		br[v[s][i]]=i;
		dfs(v[s][i],i);
	}
	cout<<"Impossible\n";
}
```

---

