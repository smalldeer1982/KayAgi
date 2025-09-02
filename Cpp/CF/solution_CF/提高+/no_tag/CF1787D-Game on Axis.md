# Game on Axis

## 题目描述

There are $ n $ points $ 1,2,\ldots,n $ , each point $ i $ has a number $ a_i $ on it. You're playing a game on them. Initially, you are at point $ 1 $ . When you are at point $ i $ , take following steps:

- If $ 1\le i\le n $ , go to $ i+a_i $ ,
- Otherwise, the game ends.

Before the game begins, you can choose two integers $ x $ and $ y $ satisfying $ 1\le x\le n $ , $ -n \le y \le n $ and replace $ a_x $ with $ y $ (set $ a_x := y $ ). Find the number of distinct pairs $ (x,y) $ such that the game that you start after making the change ends in a finite number of steps.

Notice that you do not have to satisfy $ a_x\not=y $ .

## 说明/提示

In the first test case, the pairs $ (x,y) $ with which the game ends are $ (1,-1) $ and $ (1,1) $ , corresponding to the routes $ 1\rightarrow 0 $ and $ 1\rightarrow 2 $ . Note that $ (1,2) $ is invalid since when $ n=1 $ , $ y=2 $ violates $ -n\le y\le n $ . $ (1,0) $ is also invalid since you will go from $ 1 $ to $ 1 $ forever.

In the second test case, the pairs are $ (1,-2),(1,-1),(1,2),(2,-2),(2,-1),(2,0),(2,1),(2,2) $ .

In the fourth test case, the pairs are $ (1,-2),(1,-1),(1,1),(1,2),(2,-2),(2,1),(2,2) $ .

## 样例 #1

### 输入

```
9
1
0
2
-1 0
2
1 -1
2
1 1
3
-1 -2 -1
3
1 -2 -1
4
-1 4 -2 1
5
1 1 1 1 -4
5
1 1 1 1 1```

### 输出

```
2
8
6
7
20
17
34
30
40```

# 题解

## 作者：ningago (赞：9)

题意简述：

$n$ 个点中，每个点初始有至多一条出边。

现在你可以修改任意**一个**点 $i$ 的出点为 $i+y\ (y\in [-n,n]\cap \mathbb{Z})$。

求有多少种修改方式，使得从 $1$ 出发，一直沿着出边走，不会走向环。

$n\leq 2\times 10^5$，不必保证修改后是否与原来相同。

---

通过分析图像可以得知，初始的图（修改后的图也是）可以概况成这样一个森林：

![](https://cdn.luogu.com.cn/upload/image_hosting/rg30f2tn.png)

每个连通块的中心是**一个环（包括自环），或一个点**，环上每一个点都是**一棵有向树的根**，这些树的有向边都指向根的方向（我也不知道叫这种森林什么名字，姑且称之为红太阳森林罢 qwq）。

> update：@lyc_qwq 大佬指出，这玩意叫基环内向森林。我才疏学浅QAQ。

对此我们可以把红太阳划分为两类：**环太阳**（包括自环），**点太阳**。

对于 $1$ 号点所在的红太阳，也可以把点分为两类：路径上的点和路径外的点。（图中认定蓝色点为 $1$ 号点）

![](https://cdn.luogu.com.cn/upload/image_hosting/j8k2vsh6.png)

对于路径上的点进行答案统计：

- 就此停止，将出点修改为不属于 $[1,n]$ 中的点，有 $2n+1-n=n+1$ 种方案。
- 连向一个点太阳的任意一个点。
- 若现在的点 $p$ 属于一个点太阳，则可以连向当前太阳不在 $p$ 子树内的点。

对路径外的点：

- 如果 $1$ 号点属于一个点太阳，则路径外的点都不影响，任意修改即可，有 $2n+1$ 种贡献。

Code：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define int long long
#define N 200010

int T,n;
int nx[N];
int ru[N];
std::vector <int> g[N];
bool check(int x)
{
	return 1 <= x && x <= n;
}
int dep[N],idx,id[N],cnt[N],sum;
bool vis[N];
int siz[N];

void dfs(int k,int deep)
{
	siz[k] = 1;
	vis[k] = 1;
	dep[k] = deep;
	id[k] = idx;
	cnt[idx]++;
	sum++;
	int sz = g[k].size();
	for(int i = 0;i < sz;i++)
	{
		int p = g[k][i];
		dfs(p,deep + 1);
		siz[k] += siz[p];
	}
}

signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		for(int i = 1;i <= n;i++)
		{
			scanf("%lld",&nx[i]);
			nx[i] += i;
			if(check(nx[i]))
			{
				ru[i]++;
				g[nx[i]].push_back(i);
			}
		}
		for(int i = 1;i <= n;i++)
		{
			if(!ru[i])
			{
				idx++;
				dfs(i,1);
			}
		}
		for(int i = 1;i <= n;i++)
			vis[i] = 0;
		if(id[1])
			sum -= cnt[id[1]];
		int p = 1,ans = 0;
		while(check(p) && !vis[p])
		{
			vis[p] = 1;
			ans += n + 1;
			if(id[p])
				ans += cnt[id[p]] - siz[p];
			ans += sum;
			p = nx[p];
		}
		for(int i = 1;i <= n;i++)
			if(id[1] && !vis[i])
				ans += 2 * n + 1;
		printf("%lld\n",ans);
		for(int i = 1;i <= n;i++)
		{
			vis[i] = 0;
			id[i] = 0;
			cnt[i] = 0;
			dep[i] = 0;
			ru[i] = 0;
			g[i].clear();
		}
		idx = sum = 0;
	}
}
```

---

## 作者：qzhwlzy (赞：4)

### 题目大意

有 $1\sim n$ 共 $n$ 个点和长度为 $n$ 的序列 $a$。初始你在点 $1$，你会不断从点 $i$ 走向点 $i+a_i$，走出范围结束。问多少对 $(x,y)$ 满足将 $a_x$ 赋值为 $y$ 后能结束游戏。

### 思路

按照路线将 $i$ 和 $a_i$ 连有向边，那么得到的图应该由若干链和环组成。当且仅当按照有向边走时不会走入环内才能够结束游戏，下文统一将这种情况叫做“链”；否则叫做“环”。如下图，最左边的在本文中称作 $1$ 在链上，其余的称作 $1$ 在环内。

![](https://cdn.luogu.com.cn/upload/image_hosting/czua7ypy.png)

考虑两种情况：若 $1$ 在一个环内，那么初始情况下是不能结束游戏的。所以能够结束游戏的唯一方法就是将 $1$ 能走到的点连向其它链内或直接可以结束的节点。所以统计出 $1\sim n$ 中在链上的点的个数 $\text{tot}$ 以及 $1$ 能到达的点数 $\text{tot2}$，答案即为 $\text{tot2}\times (\text{tot1} + n + 1)$。后面加的 $n+1$ 表示直接连向 $[1,n]$ 范围外的点。

否则若 $1$ 在链上，初始情况下就能结束游戏，所以除了 $1$ 能到的点外，其余点可以随便连，对答案有 $(n-\text{tot2})\times(2n+1)$ 的贡献。例如下图中的点 $2,3,4$ 都可以随便连。那么对于 $1$ 能到的点可以连哪些点呢？发现 $1$ 所在的连通块一定是一棵树（环只有入度没有出度，所以这棵树上不会有环），以结束的节点为根，如下图中的点 $6$，而节点不能连向自己子树内的点。故统计出节点子树大小 $\text{son}$，对答案就有 $\text{tot} - \text{son} + n + 1$ 的贡献（连链上的 $\text{tot}-\text{son}$ 以及连结束的 $n + 1$ 个点）。

![](https://cdn.luogu.com.cn/upload/image_hosting/vbtg3y0x.png)

关于 $\text{tot}$ 与 $\text{tot2}$ 的计算，前者只需要记录所有结束节点，DFS 一遍即可（同时顺便处理子树的问题）；后者从 $1$ 暴力跑即可。

```cpp
#include<iostream>
#include<cstdio>
#define maxn 200005
#define ll long long
using namespace std;
int T,n,tot=0,tot2=0,son[maxn],a[maxn],s[maxn],ttop=0; bool vis[maxn*3]; ll ans=0;
struct edge{int to,nex;}g[maxn]; int head[maxn*3],cnt=0;
void add(int from,int to){g[++cnt].to=to; g[cnt].nex=head[from]; head[from]=cnt;}
void set(){for(int i=1;i<=3*n;i++){head[i]=vis[i]=0;} tot=ttop=cnt=0; tot2=1; ans=0LL;}
void dfs(int top){
    top+=n; if(top<0) return; if(top-n>=1&&top-n<=n) son[top-n]=1;
    for(int i=head[top];i;i=g[i].nex) if(g[i].to-n>=1&&g[i].to-n<=n)
        {vis[g[i].to-n]=1; tot++; dfs(g[i].to-n); if(top-n>=1&&top-n<=n) son[top-n]+=son[g[i].to-n];}
}
int main(){
    scanf("%d",&T); while(T--){
        scanf("%d",&n); set(); for(int i=1;i<=n;i++){
            scanf("%d",&a[i]); add(a[i]+i+n,i+n); // 因为会走到负数所以 +n 的偏移量
            if((a[i]+i>n||a[i]+i<1)&&!vis[a[i]+i+n]){s[++ttop]=a[i]+i; vis[a[i]+i+n]=1;}
        } for(int i=1;i<=n;i++) vis[i]=0; vis[1]=1;
        for(int i=1+a[1];i>1&&i<=n&&!vis[i];i+=a[i],tot2++) vis[i]=1; // 暴力跑 tot2
        for(int i=1;i<=n;i++) vis[i]=0; while(ttop) dfs(s[ttop--]); // 处理 tot 及 son
        if(!vis[1]){printf("%lld\n",1LL*tot2*(tot+n+1)); continue; /*环*/ } ans=1LL*(n-tot2)*(2*n+1);
        for(int i=1,p=1;i<=tot2;i++,p+=a[p]) ans+=1LL*(tot-son[p]+n+1); printf("%lld\n",ans); // 链
    }
    return 0;
}
// 如果 1 在链上，链外随便连，链上不能连环及之前；如果 1 在环上，环内不能连环
// 统计 1 所在链/环上节点个数 tot2 及 1~n 中在链上的节点个数 tot
```

---

## 作者：yimuhua (赞：4)

## 题意：

有 $n$ 个点，一开始你在点 $1$，每次从点 $i$ 走到点 $i+a_i$，如果走之后不在 $1$ 到 $n$ 以内则游戏结束。在开始之前，你可以选一个 $(x,y)$，并将 $a_x$ 变为 $y$，求有多少个 $(x,y)$ 可以使游戏介绍。

## 思路：

将 $i$ 与 $i+a_i$ 连边，分类讨论：

首先，对于每一个点，都有 $n+1$ 种方法直接连出边界外。

以下使用 $cnt$ 表示可以结束的点的数量，$siz_i$ 表示原本路径中在点 $i$ 之前被到达的点

#### 若一开始点 $1$ 就能结束游戏：

对于点 $i$，若 $i$ 不在从点 $1$ 开始的路径上，则可任意连边，有 $2\times n+1$ 种方法；

若 $i$ 在点 $1$ 路径上，则不能连向原本路径中在点 $i$ 之前被到达的点和不能结束的点，有 $cnt-siz_i+n+1$ 种。

#### 若一开始点 $1$ 不能结束游戏：

对于点 $1$ 路径上的每一个点，都只能直接连出去或连向原本能结束的点，有 $cnt+n+1$ 种。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool f[200005];
vector<int> v[200005];
long long t, n, cnt, ans, a[200005], vis[200005], siz[200005];
void dfs(int x, int y) {
    if(vis[x])
        return;
    vis[x] = y;
    if(x + a[x] < 1 || x + a[x] > n) {
        f[x] = 1;
        return;
    }
    dfs(x + a[x], y), f[x] = f[x + a[x]];
    return;
}
void dfs2(int x) {
    siz[x] = 1;
    for(int i : v[x])
        dfs2(i), siz[x] += siz[i];
    return;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--) {
        cin >> n, cnt = ans = 0;
        for(int i = 1; i <= n; i++)
            cin >> a[i], vis[i] = f[i] = siz[i] = 0;
        for(int i = 1; i <= n; i++)
            if(!vis[i])
                dfs(i, i);
        for(int i = 1; i <= n; i++)
            if(f[i])
                cnt++;
        if(f[1]) {
            for(int i = 1; i <= n; i++)
                v[i].clear();
            for(int i = 1; i <= n; i++)
                if(i + a[i] > 0 && i + a[i] <= n)
                    v[i + a[i]].push_back(i);
            for(int i = 1; i <= n; i++)
                if(vis[i] == 1 && (i + a[i] < 1 || i + a[i] > n))
                    dfs2(i);
            for(int i = 1; i <= n; i++)
                if(vis[i] == 1)
                    ans += cnt - siz[i] + n + 1;
                else
                    ans += n * 2 + 1;
        }
        else
            for(int i = 1; i <= n; i++)
                if(vis[i] == 1)
                    ans += cnt + n + 1;
        cout << ans << '\n';
    }
    return 0;
}
```


---

## 作者：ttq012 (赞：1)

考虑按照套路，对于每一个 $i\in [1,n]$，有一条边 $i\to i+a_i$。

如果把走到出口看作 $0$ 号节点，那么有以下的性质：

+ 对于一个节点 $i$，如果这个点可以到达节点 $0$，那么这个节点一定在 $0$ 为根节点的树上。
+ 否则，从这个节点出发，一定会走到一个环 $g_1,g_2,g_3,\ldots,g_t,g_1,\ldots$，也就是说，这个节点一定在一个基环树上。

然后需要考虑初始节点 $1$ 是否可以到达出口 $0$。

如果初始节点可以到达出口 $0$，那么记录一个数组 $val$，表示 $1$ 号节点 $\to 0$ 号节点的简单路径上的点。那么除了这些点以外，其他点都可以通过将自己修改成 $1$ 号节点，这样到达终点。

于是考虑正难则反。容易发现一共有 $n\times (2\times n+1)$ 种情况，那么对于 $val$ 中的每一个节点编号 $p$，计算出不符合要求（出现了“反自己和儿子边”或者连接到了其他的不可以到达终点的基环树上）的即可。

否则，对于每一个 $1$ 号点能够到达的点（包括她自己），只需要计算这个点 $v$ 连到 $0$ 号节点所在的树上的任意的一个点即可。

时间复杂度是 $O(n)$ 的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n;
vector<int>z[N];
int a[N],fa[N];
bool vis[N];
int sz[N];
void dfs(int u) {
	sz[u]=1;
	for (auto &j:z[u]) {
		dfs(j);
		sz[u]+=sz[j];
	}
}
bool check(int p) {
	if(p<0||p>n)return false;
	return true;
}
void check(int u,int v) {
	if(check(u)&&check(v))z[v].push_back(u),fa[u]=v; else z[0].push_back(u),fa[u]=0;
}
signed main() {
	int T;
	cin>>T;
	while(T--) {
		cin>>n;
		for (int i=0;i<=n;i++)z[i].clear();
		for (int i=0;i<=n;i++)sz[i]=0;
		for (int i=0;i<=n;i++)vis[i]=false;
		for (int i=1;i<=n;i++)cin>>a[i];
		for (int i=1;i<=n;i++) {
			int u=i,v=i+a[i];
			check(u,v);
		}
		dfs(0);
		if(sz[1]) {
			int r=n*(2*n+1),p=1;
			while(p) {
				r-=sz[p]+n-sz[0]+1;
				p=fa[p];
			}
			cout<<r<<'\n';
		} else {
			int r=0,p=1;
			while(!vis[p]) {
				//找环
				vis[p]=true;
				p=fa[p];
				r+=n+sz[0];
			}
			//cout<<"114: ";
			cout<<r<<'\n';
		}
	}
}
```



---

## 作者：Engulf (赞：1)

对于跳出去的这一种，我们统一连到 $n+1$ 这个点（方便统计）。

对于每一个点 $u$ 可以跳到的点 $v$，我们都连一条 $v \rightarrow u$ 的边，此时显然形成了一个森林。

然后我们通过 dfs 计算出每个节点 $u$ 的子树大小，就代表了有多少个节点能够到达 $u$。

我们分两种情况考虑一下：

### 1. 从 1 开始可以结束游戏

所有合法对的数量是 $n \times (2n + 1)$，减去不合法的即为答案。

假设当前从 1 已经来到了节点 $u$，

### 2. 从 1 开始不能结束游戏

显然此时出现了环，此时我们只能处理环上的节点，只有两种情况：

1. 直接跳出去
2. 跳到一个可以跳出去的节点

对于第一种，对于每个位置 $i$，都只有 $n + 1$ 种方案能够直接跳出去（可以自己算算）。

对于第二种，可以跳出去的节点就是节点 $n + 1$ 的子树大小 $-1$（减去 $n - 1$ 本身）。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;

const int N = 2e5 + 5;

int n;

int a[N], st[N], siz[N];

vector<int> g[N];

void dfs(int u) {
	siz[u] = st[u] = 1;
	for (auto v: g[u])
		dfs(v), siz[u] += siz[v];
}

void init() {
	for (int i = 1; i <= n + 1; i++) {
		g[i].clear();
		siz[i] = st[i] = 0;
	}
}

void so1ve() {
	init();
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] += i;
		if (a[i] < 1 || a[i] > n) a[i] = n + 1;
		g[a[i]].push_back(i);
	}
	dfs(n + 1);
	LL ans = 0;
	if (st[1] == 1) {
		ans = (LL)n * (2LL * n + 1);
		int u = 1;
		while (1 <= u && u <= n) {
			ans -= siz[u] + (n + 1 - siz[n + 1]);
			u = a[u];
		}
	} else {
		int u = 1;
		while (st[u] != 2) {
			ans += n + siz[n + 1];
			st[u] = 2;
			u = a[u];
		}
	}
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int tt;
	cin >> tt;
	while (tt--)
		so1ve();
	return 0;
}
```

---

## 作者：小木虫 (赞：0)

### Problem  
给你一个长度为 $n$，从 1 开始的数轴，每个点 $i$ 上都有一个数 $a_i$。  
现在你要从点 1 开始，在这个数轴上走路，其具体过程为：  

$\space \space \space \space$ 目前在点 $u$：  
$\space \space \space \space$ 若点 $u$ 不在这个数轴上，退出。  
$\space \space \space \space$ 否则去往 $u+a_u$。   

现在允许你自定义任意一个点上的数字，问你有多少种定义方案使得走路不会陷入循环。  
### Solution  
这个问题看上去非常的图论，于是我们将 $i$ 与 $a_i+i$ 用一条单向边连接起来。  
然后你发现，若将 $a_i+i$ 看作 $i$ 的父亲，那么这是一个包含树的基环树森林。  
对于 $a_i+i$ 超出数轴的点，其一定为一棵树的根。  

然后你发现，由于每个点最多有一条出边，所以若一个连通块是基环树，那么从其任意点出发，一定能到达那个环。  

分析到这里，问题就十分清晰了。  

若从 1 开始的连通块是一棵树，那么你可以随意更改任何不属于这个连通块的点的值，而在这个连通块里的点则不可以连到其子孙，不可以连到基环树连通块。  

若从 1 开始的连通块是一棵基环树，那么你只能更改这个连通块内的点的值，不可以连到其它基环树连通块。  

code：  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int T,n,a[N],vis[N];
void init(){
	
}
queue <int> Q;
bool to[N];
vector <int> root;
vector <int> edge[N];
int sz,no[N],cnt[N];
void dfs(int u){
	sz++;no[u]=1;cnt[u]=1;
	for(int i=0;i<edge[u].size();i++)
		dfs(edge[u][i]),cnt[u]+=cnt[edge[u][i]];
}
void solve(){
	cin>>n;root.clear();sz=0;
	for(int i=1;i<=n;i++)
		to[i]=cnt[i]=no[i]=0,edge[i].clear();
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i+a[i]>=1&&i+a[i]<=n){
			edge[i+a[i]].push_back(i);
		}else{
			root.push_back(i);
		}
		vis[i]=0;
	}
	for(int i=0;i<root.size();i++)
		dfs(root[i]);
	int now=1;bool flag=0;
	while(now>=1&&now<=n){
		if(to[now])break;
		to[now]=1;
		now=now+a[now];
	}
	if(now<1||now>n)flag=1;
	int res=0;
	for(int i=1;i<=n;i++){
		if(!to[i]){
			if(flag){
				res+=2*n+1;
			}
			continue;
		}
		if(no[i])res+=sz-cnt[i];
		else res+=sz;
		res+=n+1;
	}
	cout<<res<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)init(),solve();
	return 0;
}
```



---

## 作者：Spouter_27 (赞：0)

第一遍 dfs 处理出 $1$ 号点能到达的节点和能逃出数轴的节点。   
设 $1$ 号点能到达 $cnt$ 个节点，有 $cnt2$ 个节点能逃出数轴。

分类讨论。

- $1$ 号点不能逃出数轴，则需要修改 $1$ 号节点能到达的节点的值。可以将其中任意一个点指向数轴外或者能逃出数轴的点。答案为 $cnt\times(cnt2+n+1)$.

- $1$ 号点可以逃出数轴，则可以任意修改 $1$号点到达不了的节点。

	对原图建反图。按照 $1$ 号节点逃出数轴的节点顺序枚举节点 $i$，以 $i$ 为起点在反图上不断跑 dfs。
    
    设遍历到节点 $j$，则 $i$不能连向 $j$。因为 $j$ 按照自己原来的顺序走会到达 $i$，这样会陷入循环。如果 $j$ 没有被标记，那么 $cnt2$ 减 $1$，然后标记上 $j$；过程中遇到已经标记的点或者原本就无法逃出的点就返回。dfs 结束后，剩下的 $cnt2$ 个点都能逃出数轴，答案加上 $cnt2+n+1$。
    
    当然最后答案需要加上 $(n-cnt)\times(2\times n-1)$.

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
const ll N=2e5+10;
ll T,n,a[N],ans,cnt;
bool vis[N],rc[N],rc1[N],pk[N];
vector<ll> q;
bool dfs(ll st,ll nw){
	if(nw>n||nw<=0)	return true;
	if(rc[nw])	return true;
	if(vis[nw])	return false;
	if(st==1)	rc1[nw]=true,q.push_back(nw);
	vis[nw]=true;
	ll tor=nw+a[nw];
	rc[nw]=dfs(st,tor);
	return rc[nw];
}
ll tt,to[N],hd[N],nt[N];
void push(ll u,ll v){
	to[++tt]=v;
	nt[tt]=hd[u];
	hd[u]=tt;
}
void dfs2(ll nw){
	if(pk[nw]){
		return;
	}
	if(!rc[nw])	return;
	pk[nw]=true;
	cnt--;
	for(int i=hd[nw];i;i=nt[i]){
		dfs2(to[i]);
	}
}
void work(){
	scanf("%lld",&n);
	cnt=ans=tt=0;
	q.clear();
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		ll tor=a[i]+i;
		if(tor>n||tor<1)	tor=n+1;
		push(tor,i);
		vis[i]=rc[i]=rc1[i]=pk[i]=false;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i])	rc[i]=dfs(i,i);
	}
	for(int i=1;i<=n;i++)	cnt+=rc[i];
	if(rc[1]){
		ans+=(n-q.size())*(2*n+1);
		for(int i=0;i<q.size();i++){
			dfs2(q[i]);
			ans+=cnt+n+1;
		}
	}
	else{
		ans=q.size()*(cnt+n+1);
	}
	for(int i=1;i<=n+1;i++){
		hd[i]=to[i]=nt[i]=0;
	}
		printf("%lld\n",ans);
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		work();
	}
	return 0;
}
/*
exSample:

*/

```


---

