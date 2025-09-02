# Computer

## 题目描述

某学校在一段时间前购买了第一台计算机（因此这台计算机的编号是 1）。在最近几年中，学校又购买了 $N-1$ 台新计算机。每台新计算机都连接到之前已经安装的计算机之一。学校的管理人员对网络运行缓慢感到担忧，想知道每台计算机需要发送信号的最大距离 $S_i$（即到最远计算机的电缆长度）。你需要提供这些信息。

![](https://cdn.luogu.com.cn/upload/image_hosting/2dycu3sg.png)

提示：示例输入对应于此图。从图中可以看到，计算机 4 是距离计算机 1 最远的，因此 $S_1 = 3$。计算机 4 和 5 是距离计算机 2 最远的，因此 $S_2 = 2$。计算机 5 是距离计算机 3 最远的，因此 $S_3 = 3$。我们还得到 $S_4 = 4$，$S_5 = 4$。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5
1 1
2 1
3 1
1 1```

### 输出

```
3
2
3
4
4```

# 题解

## 作者：yingxi (赞：12)

## [题目传送门](https://www.luogu.com.cn/problem/P10962)

### 题意

给定一棵有 $n$ 个节点的树，对于每个节点，都求出离他最远的节点离他的距离。

### 思路

- 暴力：以每个点为起点依次进行 `dfs(i, 0)`，查看从 $i$ 出发最多走多少步。

- 二次 dfs 法：第一次 dfs 从下往上搜，第二次 dfs 从上往下搜，具体见代码。

### ACcode：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e4 + 5;
vector<pair<int, int> > g[N];
int dis1[N], dis2[N]; //dis1表示子树的最长路, dis2表示子树的次长路 
int f[N], son[N]; //son表示子树的最长路的节点编号, f表示子树外的最长路 
int n;
void dfs1(int u, int fa)
{
	for (auto x : g[u])
	{
		int v = x.first, w = x.second;
		if (v == fa)
			continue;
		dfs1(v, u);
		//回溯过程将子树的信息带回来更新u
		if (dis1[u] < dis1[v] + w)
		{
			dis2[u] = dis1[u]; //先更新次长路
			dis1[u] = dis1[v] + w;
			son[u] = v; // 最长路先经过v
		}
		else if (dis2[u] < dis1[v] + w)
			dis2[u] = dis1[v] + w; 
	}
	return ;
}
void dfs2(int u, int fa)
{
	for (auto x : g[u])
	{
		int v = x.first, w = x.second;
		if (v == fa)
			continue;
		//在递的过程中更新数据，父亲更新儿子
		if (son[u] != v) //u的最长路不包含v, 可以直接用 
			f[v] = max(dis1[u], f[u]) + w;
		else
			f[v] = max(dis2[u], f[u]) + w;
		dfs2(v, u);
	}
	return ;
}
void solve()
{
	for (int i = 1; i <= n; i++)
		g[i].clear();
	//多测注意清空 
	memset(dis1, 0, sizeof dis1);
	memset(dis2, 0, sizeof dis2);
	memset(f, 0, sizeof f);
	for (int i = 2; i <= n; i++) 
	{
		int u, v;
		cin >> u >> v;
		g[i].push_back({u, v});
		g[u].push_back({i, v});
	}
	dfs1(1, 0); //从下往上dfs
	dfs2(1, 0); //从上往下dfs
	for (int i = 1; i <= n; i++)
		cout << max(dis1[i], f[i]) << "\n";
	return ;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
    return 0;
}
```

---

## 作者：MLE_Automaton (赞：9)

机构留的作业是 hdu 上的这题，所以闻着味就过来了。顺便水一发题解。我的思路与老师不同，还是挺独特，简单的。

废话少说，正片马上开始！
# 题目分析
给你一个节点个数为 $n(n\le10^4)$ 的树，让你求每个点与其它所有点的最长路的最大值。

注：此处数据量写了 $10^4$ 是为了遵循[原题](https://acm.hdu.edu.cn/showproblem.php?pid=2196)，此题数据量虽为 $10^3$，但是暴力枚举还是会[超时](https://www.luogu.com.cn/record/178268525)。

最容易想到的是每个点 dfs 遍历一个 $dis$ 出来求最大值。可是这题有多组数据，会 TLE 掉。

等会，遍历一个 $dis$ 出来？这道题其实就是一道树的直径模板题！

我们可以先遍历出来从根节点出来到每个节点的距离，把最长的点记录下来为 $mn_1$， 再跑一遍 $dis$，还是将最长的点记录下来为 $mn$，这样我们就得到了以根为源的最短路（根至 $mn_1$）和次短路（根至 $mn$）。因为一个点要么在最短路的路径上（此时与 $mn$ 距离最大），要么在其它地方（此时与 $mn_1$ 距离最大），所以最后我们把每个点到 $mn1$ 和 $mn$ 的距离取最大值即可。

值得注意的是，统计与 $mn$ 的距离时应使用第二次的 $dis$，不然会多算两遍根至此点的距离。而统计与 $mn_1$ 的距离时就不需要了，因为 $dis_{mn_1}$ 总是小于等于 $dis_{mn}$。

Upd on 24-11-13：

感谢 @[ycyxh1](https://www.luogu.com.cn/user/1287433) 提供的一组 hack，现已修正。

还需要注意，因为树的直径不一定会经过 $1$ 号节点，但是一定会在一次遍历后的 $mn$ 上，所以我们先从 $1$ 遍历一遍，将根设为 $mn$ 就行了。
# Talk is cheap,show me the code!
请忽略我臃肿的模板。
```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i=(a);i<=(b);i++)
#define pre(i, a, b) for(int i=(a);i>=(b);i--)
#define INF 0x3f3f3f3f
#define llINF 0x3f3f3f3f3f3f3f3f
#define bigpq(type) priority_queue<type>
#define smpq(type) priority_queue<type,vector<type>,greater<type>>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
/**********************************************************************
    test06.cpp created by Dennis2013 on 22-09-2024 周日 at 18:49:21
**********************************************************************/
int n, dis1[10005], dis2[10005], mx, mn = 1, mn1;
vector<pii> g[10005]; //使用邻接表存树
void dfs(int *dis, int u, int fa)
{
    if (dis[u] > mx) mx = dis[u], mn = u;
    for (auto k : g[u])
    {
        int v = k.first, w = k.second;
        if (v == fa) continue;
        dis[v] = dis[u] + w;
        dfs(dis, v, u);
    }
}
int main()
{
    while (~scanf("%d", &n))
    {
        rep(i, 1, n) g[i].clear();
        memset(dis1, 0, sizeof dis1);
        memset(dis2, 0, sizeof dis2);
        mx = 0; mn = 1;
        rep(i, 2, n)
        {
            int v, w; scanf("%d%d", &v, &w);
            g[i].push_back({v, w});
            g[v].push_back({i, w});
        }
        dfs(dis1, 1, 0);
        int rt = mn;
        dis1[rt] = 0;
        dfs(dis1, rt, 0);
        mn1 = mn;
        mx = 0; mn = rt;
        dfs(dis2, mn1, 0);
        rep(i, 1, n) printf("%d\n", max(dis1[i] + dis1[mn], dis2[i]));
    }
    return 0;
}
```

---

## 作者：skcks (赞：7)

不难看出本题为换根 dp 板子题。  
# 算法实现
由于题目中固定了 $1$ 为根节点，所以考虑先求出 $1$ 作为根的答案，再 dfs 进行转移。

其中 $1$ 的答案为以根作为端点的最长路。

考虑转移时，对于 $y$ 的一个儿子 $x$，它由
1.  $y$ 的其他儿子到 $y$ 的最长路加上 $x$ 到 $y$ 这条边的长度，转移而来。
2.  $y$ 的祖先到 $y$ 的最长路加上 $x$ 到 $y$ 这条边的长度，转移而来。
3.  $x$ 为根的子树上作为端点的最长路。

三者取最大值，即为转移答案。

### 注意 
若 $x$ 在 $y$ 作为端点的最长路上，答案 $1$ 只能从 $y$ 的其他儿子转移而来，因此要维护每个点作为端点的最长路和次长路。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,x;
long long d[10003][5],r[10003];
long long z,w[20003];
int head[10003],from[20003],to[20003],num=0;
void init() {
	for(int i=1; i<=10000; i++) {
		head[i]=d[i][0]=d[i][1]=r[i]=0;
	}
	num=0;
	return ;
}
void add(int x,int y,long long z) {
	from[++num]=head[x];
	to[num]=y;
	w[num]=z;
	head[x]=num;
	return ;
}
void dfs(int nw,int fa) {
	for(int i=head[nw]; i; i=from[i]) {
		int v=to[i];
		if(v==fa)continue;
		dfs(v,nw);
		if(d[v][1]+w[i]>=d[nw][1]) {
			d[nw][2]=d[nw][1];
			d[nw][1]=d[v][1]+w[i];
		} else if(d[v][1]+w[i]>=d[nw][2]) {
			d[nw][2]=d[v][1]+w[i];
		}
	}
	return ;
}
void dfs2(int nw,int fa) {
	for(int i=head[nw]; i; i=from[i]) {
		int v=to[i];
		if(v==fa)continue;
		if(d[v][1]+w[i]==d[nw][1]) {
			r[v]=max(r[nw],d[nw][2])+w[i];
		} else {
			r[v]=max(r[nw],d[nw][1])+w[i];
		}
		dfs2(v,nw);
	}
	return ;
}
signed main() {
	while(scanf("%lld",&n)==1) {
		init();
		for(int i=2; i<=n; i++) {
			scanf("%lld%lld",&x,&z);
			add(i,x,z);
			add(x,i,z);
		}
		dfs(1,0);
		dfs2(1,0);
		for(int i=1; i<=n; i++) {
			printf("%lld\n",max(d[i][1],r[i]));
		}
	}
	return 0;
}
```

---

## 作者：ycy1124 (赞：6)

### 题意
对于一颗有 $n$ 个节点，$m$ 条边的树，求出树上每个点距离其它任意一点的最大距离。
### 分析
看到这道题首先很容易就想到树的直径，我们不妨回忆一下树的直径的求法。首先选择树上任意一点，然后找这个点距离树上其他点的距离最远的那个点，然后再对于新找出来的这个点，再找一遍树上其他点距离这个点最远的那个点。最后找出来的那两个点的距离就是树的直径（此处不做证明）。

回到题目，对于每一个点距离最远的那一个点集，我们可以发现其中**一定包含**树的直径两端的**至少**一点。因为我们可以用这个点反求树的直径，求出来的其中一条直径与这条直径相同且两端中的至少一个点是距这个点最远的，否则就会有另一条比这条直径更长的直径。（绕晕了）
### 写法
跑两遍 Dijkstra 求出树的直径，然后在求树的直径的过程中记录一个端点距树上所有点的距离，然后再跑一遍 Dijkstra 求出另一个端点距树上所有点的距离，然后输出时每个点的答案就是距两个端点的距离的最大值。
### 代码
```cpp
#include<bits/stdc++.h>
#define hy for(int i=1;i<=n;i++){bj[i]=0;}
#define int long long
using namespace std;
struct Node{
	int to,w;
};
vector <Node> a[10001];
int js[10001][2];
struct qaq{
	int w,p;
}b[40001];
int tot=0;
bool bj[10001];
void work(int x){
	if(x*2+1<=tot&&b[x*2].w>b[x*2+1].w&&b[x*2+1].w<b[x].w){//堆优化
		swap(b[x],b[x*2+1]);
		work(x*2+1);
	}
	else if(x*2<=tot&&b[x*2].w<b[x].w){
		swap(b[x*2],b[x]);
		work(x*2);
	}
}
void work1(int x){
	if(b[x].w<b[x/2].w&&x!=1){
		swap(b[x],b[x/2]);
		work1(x/2);
	}
}
void dij(int p,int w,int qwq){//跑dij
	bj[p]=1;
	js[p][qwq]=w;
	for(auto it:a[p]){
		if(!bj[it.to]){
			b[++tot]={w+it.w,it.to};
			work1(tot);
		}
	}
}
signed main(){
	int n;
	while(scanf("%lld",&n)==1){
		hy
		for(int i=1;i<n;i++){
			int w,u;
			scanf("%lld%lld",&u,&w);//存图
			a[i+1].push_back({u,w});
			a[u].push_back({i+1,w});
		}
		tot=0;
		b[++tot]={0,1};
		while(tot){
			dij(b[1].p,b[1].w,0);
			swap(b[1],b[tot]);
			tot--;
			work(1);
		}
		hy
		int s=0;
		for(int i=1;i<=n;i++){
			if(js[i][0]>js[s][0]){
				s=i;
			}
		}
		tot=0;
		b[++tot]={0,s};
		while(tot){
			dij(b[1].p,b[1].w,0);
			swap(b[1],b[tot]);
			tot--;
			work(1);
		}
		hy
		int t=0;
		for(int i=1;i<=n;i++){
			if(js[i][0]>js[t][0]){
				t=i;
			}
		}
		tot=0;
		b[++tot]={0,t};
		while(tot){
			dij(b[1].p,b[1].w,1);
			swap(b[1],b[tot]);
			tot--;
			work(1);
		}
		for(int i=1;i<=n;i++){
			printf("%lld\n",max(js[i][0],js[i][1]));//取距端点最大
		}
		for(int i=1;i<=n;i++){
			a[i].clear();//多测清空
		}
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/178613374)。

最后提醒一下，该题的 $n$ 的范围是小于等于 $10^4$ 的，不要被题面诈骗了（别问我怎么知道）。

---

## 作者：Lysea (赞：3)

### [P10962 Computer](https://www.luogu.com.cn/problem/P10962)

本题状态设计较为难想。

首先不变地，令 $f_x$ 表示 $x$ 子树中的点到达 $x$ 的最长链。

假若我们仍然设 $g_x$ 表示所有节点到达 $x$ 中的最长链，会发现不太好转移，思考到最后会牵扯到次大值，以及次次大值。

而正解为 $g_x$ 表示非 $x$ 子树内节点到达 $x$ 的最长链，这样设状态，转移会轻松不少，只需最大值与次大值即可。

令 $f2_x$ 表示次长链。 

若 $f_y+v\ne f_x$：

$$g_y=\max\{g_y,f_y\}+v$$

否则：

$$g_y=\max\{g_y,f2_y\}+v$$

不过要注意一下，最后的答案不是 $g_x$，而是 $\min\{f_x,g_x\}$，可以看出这二者已经涵盖了答案取值集合。

代码：


```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1e18
#define N 1000005
using namespace std;
struct star{
    int next,to,val;
}e[N];
int T,n,head[N],cnt,siz[N],f[N],f2[N],g[N],ans;
void add(int u,int v,int w){
    e[++cnt].next=head[u];
    head[u]=cnt;
    e[cnt].to=v;
    e[cnt].val=w;
}
void dfs1(int x,int fa){
    for(int i=head[x];i;i=e[i].next){
        int y=e[i].to,d=e[i].val;
        if(y==fa) continue;
        dfs1(y,x);
        if(f[y]+d>f[x]){
            f2[x]=f[x];
            f[x]=f[y]+d;
        }else if(f[y]+d>f2[x]){
            f2[x]=f[y]+d;
        }
    }
}
void dfs2(int x,int fa){
    for(int i=head[x];i;i=e[i].next){
        int y=e[i].to,d=e[i].val;
        if(y==fa) continue;
        if(f[y]+d==f[x]) g[y]=max(f2[x],g[x])+d;
        else g[y]=max(f[x],g[x])+d;
        dfs2(y,x);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    while(cin>>n){
    	for(int i=1;i<=n;i++) f[i]=f2[i]=g[i]=head[i]=0;
    	cnt=0;
    	for(int i=2,v,w;i<=n;i++){
	        cin>>v>>w;
	        add(i,v,w),add(v,i,w);
	    }
	    dfs1(1,0),dfs2(1,0);
	    for(int i=1;i<=n;i++) cout<<max(g[i],f[i])<<endl;
	}
    return 0;
}
```

---

## 作者：P2441M (赞：2)

经典题，来写写题解。

[原题链接](https://www.luogu.com.cn/problem/P10962)

## 题意简述
给定一棵树，对于每个节点，输出它能到达的最远的距离。

## 题解
显然是换根 DP，但并不是那么好想。

钦定 $1$ 号节点为根。一个节点 $u$ 走到最远的距离只有两种情况：
1. 一直**向下**走，即路径在 $\operatorname{subtree}(u)$ 内；
2. 先**向上**走，再向下走到 $\operatorname{subtree}(u)$ 之外的地方（下面直接称为**向上走**）。

对于第一种情况，我们容易通过一次 DFS 树形 DP 求出。

对于第二种情况，考虑使用换根 DP 求出每个节点向上走的最远距离。当从 $u$ 转移到它的某个子节点 $v$ 时，设它们间的边权为 $w$，我们对 $v$ 向上向下走的拐点进行讨论：

1. 若拐点为 $u$ 的祖先，则这种情况已经在计算 $u$ 时被覆盖了，直接从 $v$ 走到 $u$，再累加上 $u$ 的向上走的最远距离；
2. 若拐点就是 $u$，考虑令 $u$ 取到向下的最远距离的是哪个子树。
   - 如果不是 $v$ 所在的子树，那么最长的路径必然是从 $v$ 走到 $u$ 后，在从 $u$ 向下走最长路；
   - 如果恰好是 $v$ 所在的子树，那么走次长路即可。次长路可以在第一次树形 DP 时被求出。

根据上述讨论，我们可以设计出这样的状态：设 $f_{u,0/1}$ 表示从节点 $u$ 向下走能达到的最长路/次长路的长度。$g_{u}$ 表示令 $u$ 取到向下的最远距离的子节点编号。$f_{u,2}$ 表示节点 $u$ 向上走能达到的最长路的长度。

对于第一次 DFS，转移是简单的：
$$
\forall v\in\operatorname{son}(u),\ 
\begin{cases}
f_{u,1}\leftarrow f_{u,0},\ 
f_{u,0}\leftarrow f_{v,0}+w,\ 
g_{u}=v
&{\text{if}}\ f_{u,0}<f_{v,0}+w \\
f_{u,1}\leftarrow \max(f_{u,1},f_{v,0}+w)
&{\text{otherwise}}
\end{cases}
$$

对于第二次 DFS，我们按照上述讨论进行转移即可：
$$
\forall v\in\operatorname{son}(u),\ f_{v,2}\leftarrow \max(f_{u,2},f_{u,[g_u=v]})+w
$$

统计答案时，显然有 $ans_u=\max(f_{u,0},f_{u,2})$。

于是我们就轻松解决了本题，时间复杂度为 $O(n+m)$。

## 代码
```cpp
// Problem: Computer
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/showproblem.php?pid=2196
// Memory Limit: 32 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstring>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define add_mod(x, v) (x) = ((ll)(x) + (v)) % MOD
#define mul_mod(x, v) (x) = (1ll * (x) * (v)) % MOD
#define sub_mod(x, v) (x) = (((ll)(x) - (v)) % MOD + MOD) % MOD
typedef long long ll;
typedef pair<int, int> pii;
const int MAX_N = 1e4 + 5, MAX_M = 1e4 + 5;

int n, f[MAX_N][3], g[MAX_N];

struct AdjList {
    int tot, head[MAX_N], nxt[MAX_M << 1], to[MAX_M << 1], edge[MAX_M << 1];
    
    void init() {
        tot = 0;
        for (int i = 1; i <= n; ++i) head[i] = -1;
    }
    
    void insert(int x, int y, int z) {
        to[++tot] = y;
        edge[tot] = z;
        nxt[tot] = head[x];
        head[x] = tot;
    }
} t;

void dfs1(int x, int fx) {
    for (int i = t.head[x]; ~i; i = t.nxt[i]) {
        int y = t.to[i], z = t.edge[i];
        if (y == fx) continue;
        dfs1(y, x);
        if (f[x][0] < f[y][0] + z) {
            f[x][1] = f[x][0];
            f[x][0] = f[y][0] + z;
            g[x] = y;
        } else f[x][1] = max(f[x][1], f[y][0] + z);
    }
}

void dfs2(int x, int fx) {
    for (int i = t.head[x]; ~i; i = t.nxt[i]) {
        int y = t.to[i], z = t.edge[i];
        if (y == fx) continue;
        f[y][2] = max(f[x][2], f[x][y == g[x]]) + z;
        dfs2(y, x);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    while (cin >> n) {
        t.init();
        for (int i = 2; i <= n; ++i) {
            int j, w;
            cin >> j >> w;
            t.insert(i, j, w); t.insert(j, i, w);
        }
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        dfs1(1, 0);
        dfs2(1, 0);
        for (int i = 1; i <= n; ++i) cout << max(f[i][0], f[i][2]) << '\n';
    }
    return 0;
}
```

---

## 作者：Farmer_Nhoj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10962)。
## Part 1 闲话
刷[动态规划](https://www.luogu.com.cn/training/505327#problems)的时候，遇到了这道换根 DP，觉得是道很好的练习题。

## Part 2 题目大意
对于树上的每一个点，寻找距离它最远的那个点距离它的距离。

## Part 3 思路
首先想到暴力。  
对于每一个点跑一遍，求出最长路。  
对于每次求解，时间复杂度为 $O(n^{2})$。  
因为会有多组测试用例，所以虽然 $n$ 最大仅有 $10^{4}$，但仍会获得 $70$ 分的好成绩。  
如果在比赛，这个分数对本蒟蒻来说已经很满意了。

但是我们需要写出此题的正解。  
于是我们发现可以先求出 $1$ 号点的答案，然后通过 $1$ 号点的答案转移至其他点。   
这不就是经典的换根 DP 的套路吗？！

首先我们需要求出 $1$ 号点的答案。  
想来还是比较简单的。  
请看代码：
```
void dfs(int u,int fa){
    for(int i=head[u];i;i=edge[i].nxt){
        int v=edge[i].to;
        int w=edge[i].wei;//链式前向星存图。
        if(v!=fa){//因为是无向图，所以需要判断子节点是否与父节点相同。
            dfs(v,u);//dfs求出v节点的状态。
            if(dp[v][1]+w>=dp[u][1]){
                dp[u][2]=dp[u][1];
                dp[u][1]=dp[v][1]+w;
            }
            else if(dp[v][1]+w>=dp[u][2]){
                dp[u][2]=dp[v][1]+w;
            }//维护次短路与最短路。
            //dp[u][1]是最长路。
            //dp[u][2]是次长路。
        }
    }
}
```

于是，我们得出了 $1$ 号节点的答案——$dp[1][1]$。

随后，思考如何转移。   
我们令该节点为 $u$，它的父节点为 $fa$，$u$ 到 $fa$ 距离是 $w$。   
一个节点的答案可能有三种情况，分别是：  
1. $fa$ 的某个儿子至 $fa$ 的最长路加上 $w$。  
2. $fa$ 的祖先至 $fa$ 的最长路加上 $w$。  
3. 以 $u$ 为根的子树上的某节点至 $u$ 的最长路。  

为什么要维护最长路和次长路？  
如果 $u$ 在以 $fa$ 为根节点的最长路上，则答案 $1$ 无法通过 $fa$ 的最长路转移，只能使用次长路。  
同时，一个显然的性质：若节点 $x$ 存在于 节点 $y$ 的最长路上，则 $x$ 必然不存在节点 $y$ 的次长路上。

转移代码：
```
void Dfs(int u,int fa){
    for(int i=head[u];i;i=edge[i].nxt){
        int v=edge[i].to;
        int w=edge[i].wei;
        if(v!=fa){
            if(dp[v][1]+w==dp[u][1]) f[v]=max(f[u],dp[u][2])+w;
            else f[v]=max(f[u],dp[u][1])+w;
            Dfs(v,u);
        }
    }
}
```
转移时间复杂度为 $O(n)$。  
本题其余坑点如下：  
| 坑点 | 解决方案 |
| :-: | :-: |
| 没有明确结束标识。 | 使用 `while` 进行输入。 |
| 答案不是 $f[i]$。 | 其实是 $\max(dp[i][1],f[i])$。

## Part 4 完整代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int cnt;
int head[200005];
int dp[20005][15];
int f[20005];
struct Edge{
    int nxt;
    int to;
    int wei;
}edge[200005];
void add(int u,int v,int w){
    edge[++cnt].nxt=head[u];
    edge[cnt].to=v;
    edge[cnt].wei=w;
    head[u]=cnt;
}
void dfs(int u,int fa){
    for(int i=head[u];i;i=edge[i].nxt){
        int v=edge[i].to;
        int w=edge[i].wei;
        if(v!=fa){
            dfs(v,u);
            if(dp[v][1]+w>=dp[u][1]){
                dp[u][2]=dp[u][1];
                dp[u][1]=dp[v][1]+w;
            }
            else if(dp[v][1]+w>=dp[u][2]){
                dp[u][2]=dp[v][1]+w;
            }
        }
    }
}
void Dfs(int u,int fa){
    for(int i=head[u];i;i=edge[i].nxt){
        int v=edge[i].to;
        int w=edge[i].wei;
        if(v!=fa){
            if(dp[v][1]+w==dp[u][1]) f[v]=max(f[u],dp[u][2])+w;
            else f[v]=max(f[u],dp[u][1])+w;
            Dfs(v,u);
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while(cin>>n){
        memset(dp,0,sizeof(dp));
        memset(edge,0,sizeof(edge));
        memset(f,0,sizeof(f));
        memset(head,0,sizeof(head));
        cnt=0;
        for(int u=2;u<=n;u++){
            int v,w;
            cin>>v>>w;
            add(u,v,w);
            add(v,u,w);
        }
        dfs(1,0);
        Dfs(1,0);
        for(int i=1;i<=n;i++){
            cout<<max(dp[i][1],f[i])<<"\n";
        }
    }
    return 0;
}
```
## Part 5 完结撒花
[AC 记录](https://www.luogu.com.cn/record/216164035)。

---

## 作者：GY程袁浩 (赞：0)

建议评绿。

> 原因：此题属于换根 DP，并且需要记录最大值和次大值，比较麻烦。

另外，本题的数据范围错误，应为 $n\le 10^4$，而不是 $n\le 10^3$，望请管理员修改。

## Sol

此类题容易想到我们需要做换根 DP。

考虑换根的具体进行过程：

可以假设父节点已经计算了答案。

那么我们就希望当前节点从父结点转移，由于父节点的答案有可能包含目前节点的影响。所以我们记录父节点**从他所有儿子节点的最大值转移过来**的最大值和次大值。

因为我们实际上是排除当前的节点对父节点的影响，所以是从他所有儿子节点的**最大值**转移过来。

这样我们通过父节点的转移和儿子节点的转移就成功计算出了当前节点的答案，再计算子节点的值即可。

做两次 DP，一次计算根的答案，一次进行换根，转移是显然的，详见代码。

```cpp
// Problem: P10962 Computer
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10962
// Memory Limit: 512 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define upp(a, x, y) for (int a = x; a <= y; a++)
#define dww(a, x, y) for (int a = x; a >= y; a--)
#define pb(x) push_back(x)
#define endl '\n'
#define x first
#define y second
#define PII pair<int, int>
using namespace std;
const int N = 2e4 + 10;//2e3 + 10 会 RE
int h[N], e[N], w[N], ne[N], idx;
int f1[N], f2[N], g1[N], g2[N];
int n;
void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}
void dfs1(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs1(j, u);
        if (f1[j] + w[i] >= f1[u]) {
            f2[u] = f1[u];
            f1[u] = f1[j] + w[i];
        } else if (f1[j] + w[i] > f2[u])
            f2[u] = f1[j] + w[i];
    }
}
void dfs2(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) {
            int now;
            if (g1[j] == f1[u] + w[i])
                now = g2[j] + w[i];
            else
                now = g1[j] + w[i];

            if (now >= g1[u]) {
                g2[u] = g1[u];
                g1[u] = now;
            } else if (f1[j] + w[i] > g2[u])
                g2[u] = now;
            continue;
        }
        if (f1[j] + w[i] >= g1[u]) {
            g2[u] = g1[u];
            g1[u] = f1[j] + w[i];
        } else if (f1[j] + w[i] > g2[u])
            g2[u] = f1[j] + w[i];
    }
    for (int i = h[u]; i != -1; i = ne[i])
        if (e[i] != fa) dfs2(e[i], u);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n) {
        memset(h, -1, sizeof h);
        memset(f1, 0, sizeof f1);
        memset(f2, 0, sizeof f2);
        memset(g1, 0, sizeof g1);
        memset(g2, 0, sizeof g2);
        idx = 0;
        upp(i, 2, n) {
            int y, z;
            cin >> y >> z;
            add(i, y, z);
            add(y, i, z);
        }
        dfs1(1, -1);
        dfs2(1, -1);
        upp(i, 1, n) cout << g1[i] << endl;
    }
    return 0;
}
```

---

## 作者：_zuoqingyuan (赞：0)

这题换根做法只有黄卧持。

# 思路分析

看完题面不难想到换根 dp。

设 $f_u$ 表示 $u$ 的子树内到 $u$ 的最远距离，记 $son(u)$ 为节点 $u$ 的子节点集合，则：

$$f_u=\max_{v\in son(u)}\{f_v+1\}$$

思考换根怎么做，如果把路径的范围从子树内换到整颗树，还需考虑从 $u$ 的父亲节点出发，不经过 $u$ 的最长路。

因为 $\max$ 具有区间可加性，但不具备区间可减性，所以我们很难直接换根，但 $\max$ 的性质和乘积比较像，所以可以沿用 [Subtree](https://www.luogu.com.cn/problem/AT_dp_v) 的做法。

记 $g_u$ 表示从 $u$ 的父亲出发，不考虑经过点 $u$ 的最长路径，路径可分为两类：

1. 从 $u$ 的父亲出发，经过 $u$ 的兄弟节点

2. 从 $u$ 的父亲出发，走到 $u$ 父亲的父亲，再往外走的最短路径。

后半部分，$g_u=g_{Fa(u)}+w_{u,Fa(u)}$，前半部分，维护 $$\max\{f_v+w_{v,Fa(u)}\}$$ 的前缀最大值 $suf$ 和后缀最大值 $pre$，此时 $g_u=\max\{suf,pre\}+w_{u,Fa(u)}$。

令 $g_1=0$，直接换根即可，时间复杂度 $O(n)$。


```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int N=10005,inf=1e9;
struct node{int to,v;};
vector<node>G[N];
int f[N],g[N],n;
void clear(){
	for(int i=0;i<=n;i++)G[i].clear();
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	n=0;
}
void dfs1(int x,int fa){
	f[x]=0;
	for(auto y:G[x]){
		dfs1(y.to,x);
		f[x]=max(f[x],f[y.to]+y.v);
	}
	return;
}
void dfs2(int x,int fa){
	if(!G[x].size())return;
	int suf=-inf,pre=-inf;node y;
	for(int i=0;i<G[x].size();i++){
		y=G[x][i];
		g[y.to]=max(g[y.to],suf);
		suf=max(suf,f[y.to]+y.v);
	}
	for(int i=G[x].size()-1;i>=0;i--){
		y=G[x][i];
		g[y.to]=max(g[y.to],pre);
		pre=max(pre,f[y.to]+y.v);
	}
	for(auto y:G[x]){
		g[y.to]=max(g[y.to],g[x])+y.v;
		dfs2(y.to,x);
	}
	return;
}
void work(){
	for(int i=2,u,v;i<=n;i++){
		scanf("%d %d",&u,&v);
		G[u].push_back(node{i,v});
	}
	dfs1(1,0);
	g[1]=0;
	dfs2(1,0);
	for(int i=1;i<=n;i++){
		printf("%d\n",max(f[i],g[i]));
	}
}
int main(){
	while(~scanf("%d",&n))work(),clear();
	return 0;
}
```

如有错误，请指出。

---

## 作者：Epitome (赞：0)

## 题意

一棵包含 $n$ 个点的树，对于每个满足 $1 \leq i \leq n$ 的点 $i$，求出一个 $j$ 使得对于任意 $k \land k \not = i \land k \not = j$，满足树上 $i \to j$ 的距离 $> i \to k$ 的距离。

## 解法

我们先树 `dp` 求出树中每个点以一为根的最长链 `dp[x][0]`，次长链 `dp[x][1]`。

然后换根/二次扫描，设 $ans_x$ 表示 $x$ 的**子树外**的答案，有：

如果 $son$ 是以 $x$ 为根的子树内的最长链上的节点，设 $e$ 为连接 $son$ 和 $x$ 的边的边权，那么 $ans_{son} = \max \{ ans_{x}, dp_{x, 1} \} + e$，否则 $ans_{son} = \max \{ ans_{x}, dp_{x, 0} \} + e$。

注意输出时应输出 $\max \{ ans_i, dp_{i, 0} \}$，一个子树内，一个子树外，很好理解。

## 代码

```cpp
#include <iostream>

#include <vector>

using namespace std;

const int N = 1e4 + 5;

struct Edge {
  int x, c;
};

int n, dp[N][2], ans[N];

vector<Edge> g[N];

void s( int x, int fa ) {
  for (auto to : g[x]) {
    if (!(to.x ^ fa)) continue;
    s(to.x, x);
    if (dp[to.x][0] + to.c > dp[x][0]) {
      dp[x][1] = dp[x][0], dp[x][0] = dp[to.x][0] + to.c;
    } else if (dp[to.x][0] + to.c > dp[x][1]) {
      dp[x][1] = dp[to.x][0] + to.c;
    }
  }
}

void dfs( int x, int fa ) {
  for (auto to : g[x]) {
    if (!(to.x ^ fa)) continue;
    if (dp[to.x][0] + to.c == dp[x][0]) {
      ans[to.x] = max(ans[x], dp[x][1]) + to.c;
    } else {
      ans[to.x] = max(ans[x], dp[x][0]) + to.c;
    }
    dfs(to.x, x);
  }
}

void solve() {
  for (int i = 1; i <= n; ++i) {
    g[i].clear(), dp[i][0] = dp[i][1] = 0;
  }
  for (int i = 2, x, c; i <= n; ++i) {
    cin >> x >> c;
    g[i].push_back({x, c});
    g[x].push_back({i, c});
  }
  s(1, 0);
  dfs(1, 0);
  for (int i = 1; i <= n; ++i) {
    cout << max(ans[i], dp[i][0]) << '\n';
  }
}

int main() {
  ios :: sync_with_stdio(0), cin.tie(0);
  while (cin >> n) {
    solve();
  }
  return 0;
}
```

---

## 作者：Statax (赞：0)

## P10962 Computer Solution

### 前言

此题解是建立在电缆长度为非负数的情况。

### 题义分析

给定一棵带权树，求分别从各点出发的最长链的长度。

### 题目解析

当看到求树的直径的时候，我们首先应该想到的是树形 DP 或贪心（两遍 dfs）。

而树形 DP 题解里已经有了，这里我用 dfs 来求解。

先说结论，任意节点的答案一定为该点到树的直径的两个端点的长度取较大值。

利用反证法证明，若某一点的答案不是到树的直径的两个端点的较大值，那么它无非有两种改变答案方式：

1. 该答案路径可以继续延伸。
2. 该答案换成另外的路径能使答案更大。

但这两点都会被树的直径考虑，所以结论正确。

### 题目代码

随后便可以写出代码：

```cpp
#include <iostream>
#include <cstdio>
#include <string.h>
#include <vector>

#define endl '\n'
#define int long long
#define lowbit(x) x & (-x)

using namespace std;
const int N = 1e4 + 5;

int n, d1[N], d2[N];
int res, ans;
vector<pair<int, int> > G[N];

void dfs(int u, int fa) {
	for(const auto &it : G[u]) {
		int v = it.first, w = it.second;
		if(v != fa) {
			d1[v] = d1[u] + w;
			if(d1[v] > res) res = d1[v], ans = v; 
			dfs(v, u);
		}
	}	
}

void dfss(int u, int fa) {
	for(const auto &it : G[u]) {
		int v = it.first, w = it.second;
		if(v != fa) 
			d2[v] = d2[u] + w,
			dfss(v, u);
	}	
}

// 初始化函数
void init() {
	
}

// 输入函数
void input() {
	for(int i = 0;i < N; ++i) G[i].clear();
	for(int u = 2, v, w;u <= n; ++u)
		cin >> v >> w, 
		G[u].emplace_back(make_pair(v, w)), 
		G[v].emplace_back(make_pair(u, w));
}

// 处理函数
void solve() {
	int st, ed;
	d1[1] = 0; ans = 1; res = 0; dfs(1, 0); st = ans;
    d1[st] = 0; ans = 1; res = 0; dfs(st, 0); ed = ans;
    d2[ed] = 0; ans = 1; res = 0; dfss(ed, 0);
}

// 输出函数
void output() {
	for(int i = 1;i <= n; ++i)
		cout << max(d1[i], d2[i]) << endl;
}

// 任务函数
void task() {
	input();
	solve();
	output();	
}

// 主函数
signed main() {
	int ___ = 1; 
	init(); while(cin >> n) task();
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 我的博客

本文知识点参考发于：[oi-beats/换根dp](https://ntsc-yrx.github.io/oi-beats/site/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/%E6%A0%91%E5%BD%A2DP/#dp_1)，[个人博客/](https://ntsc.flowus.cn/)。

## 大意

多次询问。给你一棵有边权的树，问你每个点到其他点的最远距离。

## 换根DP

有些时候，题目要求最优化一个值，但是它和选择哪个节点作为根节点，或者是从那个节点开始扩散有关，时间复杂度有要求我们不能采用 $n$ 次 dfs（树形 dp），这时我们就需要使用换根 dp 了。

换根 dp 是树形 dp 的一种，它通过第一遍 dfs 得到的数据（如将 $1$ 作为根节点跑出的各个节点的 dp 值），在第二次 dfs 中加以利用，通过转移式快速根据已有信息求出将邻接点作为根节点时的答案。

## 做法

换根 dp。先定义 $f_i$ 为以 $1$ 为根时，$i$ 子树内的点到 $i$ 的距离的最大值。这很好维护。

然后就是换根了。定义 $g_i$ 为以 $i$ 为根时，所有点到 $i$ 的距离的最大值，也就是题目要求的。

我们考虑如何求出 $g_i$。

我们考虑当前到了点 $x$，$v$ 是 $x$ 的一个子节点，并且我们要使用 $f$ 数组的信息求出 $g_v$。考虑 $g_v$ 的来源：

- $v$ 下方的点。直接使用 $f_v$ 即可。

- $v$ 上方的点。那么我们可以枚举 $x$ 的其他子节点 $u$，然后使用 $f_u$，加上 $u$ 到 $v$ 的路径。还有一类是来自 $x$ 上方的，这个我们接下来会用 $t$ 数组维护。这里调用 $t_x$ 即可。

那么如何维护 $t_x$ 呢？我们发现 $t_x$ 就是 $g_x$ 排除了上述第一种情况的答案后的值。所以我们在求 $g_v$ 时，先用上述的第二种情况更新它，然后用它更新 $t_v$，最后用第一种情况更新 $g_v$。



```C++
/*                                                                                
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+G then MOD : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this and dump to the next
      - ctrl+Shift+L : choose all like this
      - ctrl+K then ctrl+W: close all
      - Alt+la/ra : move mouse to pre/nxt pos'
	  
*/
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define rep(i, l, r) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(i, r, l) for (int i = r, END##i = l; i >= END##i; --i)
#define pb push_back
#define mp make_pair
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first

// #define innt int
#define itn int
// #define inr intw
// #define mian main
// #define iont int

#define rd read()
int read(){
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
		if (ch == '-')
			ff = -1;
		ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
      xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
void write(int out) {
	if (out < 0)
		putchar('-'), out = -out;
	if (out > 9)
		write(out / 10);
	putchar(out % 10 + '0');
}

#define ell dbg('\n')
const char el='\n';
const bool enable_dbg = 1;
template <typename T,typename... Args>
void dbg(T s,Args... args) {
	if constexpr (enable_dbg){
    cerr << s;
    if(1)cerr<<' ';
		if constexpr (sizeof...(Args))
			dbg(args...);
	}
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }
#else
#define dbg(...)
#endif


const int N = 1e5 + 5;
const int INF = 1e18;
const int M = 1e7;

struct node{
    int v,w;
};

vector<node> e[N];

void add(int a,int b,int c)
{
    e[a].pb({b,c});
    e[b].pb({a,c});
}


itn f[N],g[N];//i子树中到i的最大距离，以i为根时i的答案
int t[N];

void dfs(int x,int fa){
    // cdbg(x);
    for(auto v:e[x]){
        if(v.v==fa)continue;
        dfs(v.v,x);
        f[x]=max(f[x],f[v.v]+v.w);
    }
}


void dfs2(int x,int fa){
    for(auto v:e[x]){
        if(v.v==fa)continue;
        for(auto u:e[x]){
            if(u.v==fa||u.v==v.v)continue;
            g[v.v]=max(g[v.v],v.w+u.w+f[u.v]);
        }
        g[v.v]=max(g[v.v],t[x]+v.w);
        t[v.v]=g[v.v];
        g[v.v]=max(g[v.v],f[v.v]);

        dfs2(v.v,x);
    }
}

int n;

void init(){
    for(int i=1;i<=n;i++){
        while(e[i].size())e[i].pop_back();
    }
    memset(g,0,sizeof g);
    memset(f,0,sizeof f);
}

void solve(){
    init();
    if(cin>>n);
    else exit(0);

    for(int i=1;i<n;i++){
        itn b=rd,c=rd;
        add(i+1,b,c);
    }


    dfs(1,0);
    g[1]=f[1];
    dfs2(1,0);

    // for(int i=1;i<=n;i++)cdbg(f[i]);

    for(int i=1;i<=n;i++){
        cout<<g[i]<<endl;
    }
}
signed main() {
    // freopen("suffix.in","r",stdin);
    // freopen("suffix.out","w",stdout);

    int T=1;
    while(T){
    	solve();
    }
    return 0;
}
```

---

## 作者：kkkfc0114514 (赞：0)

# 题目分析
换根 dp 。

首先用 dfs 求出以 $1$ 号节点作为根节点在 $y$ 号节点的子树下离 $y$ 号节点最远的那个节点离 $y$ 号节点多远。

求出这个值后，设 $x$ 为 $y$ 号节点的父节点，则换根 dp 由这三种情况转移：

1. $x$ 的其他孩子到 $x$ 的距离加上 $y$ 到 $x$ 的距离。
2. $x$ 的祖先或 $x$ 的兄弟到 $x$ 的距离加上  $y$ 到 $x$ 的距离。
3. $y$ 号节点的子树下离 $y$ 号节点最远的那个节点到 $y$ 号节点的距离。

三者取最大值，即为答案。

画个图方便理解：

![](https://s21.ax1x.com/2024/11/23/pAf4ZRS.png)

# Code
```cpp
#include <bits/stdc++.h>
namespace SXL {
	using std::vector;
	using std::array;
	using std::max;
	constexpr int MAXN = 100005;
	vector<array<int,2>> edge[MAXN];
	int dp[MAXN],f[MAXN];
	int t[MAXN];
	void dfs(int x,int fa) {
		for(auto i : edge[x]) {
			if(i[0] == fa) continue;
			dfs(i[0],x);
			f[x] = max(f[x],f[i[0]] + i[1]);
		}
	}
	void dfs2(int x,int fa) {
		for(auto i : edge[x]) {
			if(i[0] == fa) continue;
			for(auto j : edge[x]) {
				if(j[0] == fa || i[0] == j[0]) continue;
				dp[i[0]] = max(dp[i[0]],i[1] + j[1] + f[j[0]]);
			}
			dp[i[0]] = max(dp[i[0]],t[x] + i[1]);
			t[i[0]] = dp[i[0]];
			dp[i[0]] = max(dp[i[0]],f[i[0]]);
			dfs2(i[0],x);
		}
	}
	void solve(int n) {
		for(int i = 1;i <= n;i++) {
			t[i] = 0;
			dp[i] = 0;
			f[i] = 0;
			edge[i].clear();
		}
		for(int i = 1,x,y;i < n;i++) {
			scanf("%d%d",&x,&y);
			edge[i + 1].push_back({x,y});
			edge[x].push_back({i + 1,y});
		}
		dfs(1,0);
		dp[1] = f[1];
		dfs2(1,0);
		for(int i = 1;i <= n;i++) {
			printf("%d\n",dp[i]);
		}
	}
	void main() {
		int n;
		while(scanf("%d",&n) != EOF) {
			solve(n);
		}
	}
}
int main() {
	SXL::main();
	return 0;
}
```

---

