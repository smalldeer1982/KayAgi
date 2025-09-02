# Bertown roads

## 题目描述

Bertown 有 $n$ 个路口和 $m$ 条双向道路。已知通过现有的道路，可以从任意一个路口到达任意其他路口。

随着城市中汽车数量的增加，交通拥堵问题日益严重。为了解决这个问题，政府决定将所有道路改为单向通行，以缓解交通压力。你的任务是判断是否存在一种方式，将所有道路定向为单向，使得从任意一个路口仍然可以到达任意其他路口。如果存在这样的方案，你还需要给出其中一种可能的道路定向方式。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 8
1 2
2 3
1 3
4 5
4 6
5 6
2 4
3 5
```

### 输出

```
1 2
2 3
3 1
4 5
5 6
6 4
4 2
3 5
```

## 样例 #2

### 输入

```
6 7
1 2
2 3
1 3
4 5
4 6
5 6
2 4
```

### 输出

```
0
```

# 题解

## 作者：NatsumeHikaru (赞：7)

ad: [博客食用效果更佳](https://hikaru.com.cn/hikaru/212/)
#### Description

[here](https://codeforces.com/contest/118/problem/E)

#### Solution

> 桥：给定一张无向连通图 $G$ .若对于 $x\in V$ ，从图中删去边 $e$ 之后，$G$ 分裂成两个不相连的子图，则 $e$ 称 为 $G$ 的桥或割边。

那么本题就转化为判断是否存在桥，如果有桥存在即是无解，可以使用 tarjan 算法解决。

在进行 tarjan 时，顺便记录下路径。

#### Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=100010,M=600010;

int n,m;
int h[N],to[M],ne[M],idx;
int dfn[N],low[N],timestamp;
int ans[M][2],tot;
bool vis[M];

inline void read(int &x){
	x=0;int f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	x*=f;
}

inline void add(int u,int v){
	to[idx]=v,ne[idx]=h[u],h[u]=idx++;
}

void tarjan(int u,int fa){
	low[u]=dfn[u]=++timestamp;
	for(int i=h[u];~i;i=ne[i]){
		int j=to[i];
		if(j == fa) continue;
		if(!dfn[j]){
			tarjan(j,u);
			ans[++tot][0]=u,ans[tot][1]=j;
			if(low[j] > dfn[u]){
				puts("0");
				exit(0);
			}
			low[u]=min(low[u],low[j]);
		}
		else{
			low[u]=min(low[u],dfn[j]);
			if(dfn[j] < dfn[u]) ans[++tot][0]=u,ans[tot][1]=j;
		} 
	}
}

int main(){
	memset(h,-1,sizeof h);
	read(n),read(m);
	while(m--){
		int a,b;
		read(a),read(b);
		add(a,b),add(b,a);
	}

	tarjan(1,-1);
	for(int i=1;i<=tot;++i)
		printf("%d %d\n",ans[i][0],ans[i][1]);
	return 0;
}
```



---

## 作者：RainFestival (赞：5)

首先把图读进来

然后我们先进行 tarjan

如果有桥，那么一定无解

不然我们就进行 dfs

按照访问顺序输出

注意这是双向边，所以边已访问的标记要打双向的

但是这样会超时

有一种情况：

```
7 11
1 2
2 3
3 1
1 4
4 2
1 5
5 2
1 6
6 2
1 7
7 2
```
这样1,2两个点会重复访问，而且他们的出边又很多

所以访问过的点也要标记，不能重复访问（但边不能标记）

代码：

```cpp
#include<cstdio>
#include<vector>
#include<queue>
std::vector<int> a[100005],b[100005],f[100005];
int n,m,flag,cnt,dfn[100005],low[100005],vis[100005],p[100005]; 
void add(int x,int y)
{
	a[x].push_back(y),a[y].push_back(x);
	b[x].push_back(0),b[y].push_back(0);
	f[x].push_back(a[y].size()-1),f[y].push_back(a[x].size()-1);
}
void tarjan(int v,int fa)
{
	low[v]=dfn[v]=++cnt;vis[v]=1;
	for (int i=0;i<a[v].size();i++)
	{
	    int u=a[v][i];
	    if (u==fa) continue;
	    if (!dfn[u]) tarjan(u,v),low[v]=std::min(low[v],low[u]);
	    else if (vis[u]) low[v]=std::min(low[v],dfn[u]);
	    if (dfn[v]<low[u]) flag=1;
	}
}
void dfs(int v)
{
	if (p[v]) return;p[v]=1;
	for (int i=0;i<a[v].size();i++)
	{
		int u=a[v][i];
		if (b[v][i]) continue;
		b[v][i]=1;b[u][f[v][i]]=1;
		printf("%d %d\n",v,u);
		dfs(u);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	tarjan(1,-1);
	if (flag) {puts("0");return 0;}
	dfs(1);
	return 0;
}
```


---

## 作者：Galex (赞：3)

考虑 dfs 树。

当且仅当一条树边没有被返祖边（即非树边）覆盖过时，无解。

所以我们可以直接把 dfs 树建出来，对返祖边的覆盖范围在 dfs 树上进行树上差分。

最后若有解，直接按照 dfs 树上的方向输出即可。

```cpp

#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n, m;
vector<int> e[100005];
vector<int> t[100005];
bool vis[100005] = {0};
int d[100005] = {0};

void dfs(int x, int fa) {
	vis[x] = true;
	for (int y : e[x])
		if (y != fa && vis[y])
			d[x]++, d[y]--;
	for (int y : e[x])
		if (!vis[y])
			t[x].push_back(y), dfs(y, x);
}

bool intot(int x) {
	bool ans = true;
	for (int y : t[x])
		ans &= intot(y), d[x] += d[y];
	return ans && (d[x] || x == 1); 
}

void print(int x, int fa) {
	vis[x] = true;
	for (int y : e[x])
		if (y != fa && vis[y])
			printf("%lld %lld\n", x, y);
	for (int y : e[x])
		if (!vis[y])
			printf("%lld %lld\n", x, y), print(y, x);
}

signed main() {
	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read();
		e[u].push_back(v), e[v].push_back(u);
	}
	dfs(1, 0);
	if (!intot(1)) {
		printf("0");
		return 0;
	}
	memset(vis, 0, sizeof vis);
	print(1, 0);
	return 0;
}
```

---

## 作者：wxzzzz (赞：3)

### 题意

给定 $m$ 条无向边，把它们转换成有向边，使得这张图变成一个[强连通分量](https://baike.baidu.com/item/%E5%BC%BA%E8%BF%9E%E9%80%9A%E5%88%86%E9%87%8F/7448759)。

### 思路

前置：[tarjan](https://www.cnblogs.com/wangxuzhou-blog/p/advanced-graph-theory.html#%E5%89%B2%E7%82%B9%E4%B8%8E%E6%A1%A5)。

我们都知道割边是一张图中所有强连通分量的分界，一个强连通分量是不能存在割边的。

因此，如果存在割边，无解。

那么如何求出一组解？

这是样例 $1$ 的一组解：

![](https://cdn.luogu.com.cn/upload/image_hosting/eq65xjmp.png)

可以发现每个点向**没有向它连过有向边**并且**在原图中有无向边与其直接相连**的点连有向边，这也和 tarjan 的遍历规则相同。

因此，在 tarjan 求割边时顺便记录顺序即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, t, idx, cnt, v[1000005], h[1000005], ne[1000005], dfn[1000005], low[1000005];
bool flag, vis[1000005];
pair<int, int> ans[1000005];
void add(int a, int b) {
    v[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void tarjan(int x, int F) {
    vis[x] = 1;
    low[x] = dfn[x] = ++t;

    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (!vis[y]) {
            tarjan(y, x);
            ans[++cnt] = {x, y};
            low[x] = min(low[x], low[y]);

            if (low[y] > dfn[x]) {
                flag = 1;
                return;
            }
        } else if (y != F && dfn[y] < dfn[x]) {
            low[x] = min(low[x], dfn[y]);
            ans[++cnt] = {x, y};
        }
    }
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;

    while (m--) {
        int x, y;
        cin >> x >> y;
        add(x, y), add(y, x);
    }

    tarjan(1, 0);

    if (flag) {
        cout << "0";
        return 0;
    }
    //注意这里不能写成 if (tarjan(1, 0))，不然返回值会出错

    for (int i = 1; i <= cnt; i++) {
        cout << ans[i].first << ' ';
        cout << ans[i].second << '\n';
    }

    return 0;
}
```

---

## 作者：Fiendish (赞：2)

不难发现，如果一个图中有桥的话，那么将其改为单向边后就会出现一种情况，即其连接的两个子图只能从其中一个走到另一个，但走过去就回不来了。所以，问题就转化成了求图中有没有桥，如果有就不符合要求。

为了最后输出答案，我们可以一边跑 tarjan 一边记录路径，最后输出即可（tarjan 算法在此不再赘述，有兴趣者自行了解）。

贴上丑陋的代码：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=100010,M=600010;
int n,m;
int h[N],to[M],ne[M],idx;
int dfn[N],low[N],timestamp;
int ans[M][2],tot;
bool vis[M];
void read(int &x){
	x=0;int f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	x*=f;
}
void add(int u,int v){
	to[idx]=v,ne[idx]=h[u],h[u]=idx++;
}
void tarjan(int u,int fa){//tarjan求桥
	low[u]=dfn[u]=++timestamp;
	for(int i=h[u];~i;i=ne[i]){
		int j=to[i];
		if(j==fa) continue;
		if(!dfn[j]){
			tarjan(j,u);
			ans[++tot][0]=u,ans[tot][1]=j;//记录路径
			if(low[j]>dfn[u]){//有桥
				puts("0");//输出0
				exit(0);//结束程序
			}
			low[u]=min(low[u],low[j]);
		}
		else{
			low[u]=min(low[u],dfn[j]);
			if(dfn[j]<dfn[u]) ans[++tot][0]=u,ans[tot][1]=j;//记录路径
		} 
	}
}
int main(){
	memset(h,-1,sizeof h);
	read(n),read(m);
	while(m--){
		int a,b;
		read(a),read(b);
		add(a,b),add(b,a);
	}
	tarjan(1,-1);
	for(int i=1;i<=tot;++i)
		printf("%d %d\n",ans[i][0],ans[i][1]);
	return 0;
}
```
若有疏漏、不详之处，恳请各位大佬指出。

---

## 作者：EuphoricStar (赞：2)

## 思路

[dfs tree](https://codeforces.com/blog/entry/68138)。

首先显然如果原图中有桥则答案为 $0$。因为无论这条边的方向朝哪边都会有一个连通块的结点不能到达它连接的另一个连通块。找桥可以 tarjan。

然后直接给出结论：求出 dfs tree，则树边的方向是由父到子，非树边（返祖边）的方向是由子到父。

证明也很简单。根存在路径到达任意一个子结点（因为建出了 dfs tree），而任意一个子结点也存在路径到达根（因为子结点的子树中肯定会存在一个结点，使得它连出一条返祖边）。

于是这题就做完了。

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 100100;
const int maxm = 600100;

int n, m, head[maxn], len, dfn[maxn], low[maxn], times;
bool vis[maxm];
struct edge {
	int to, id, next;
} edges[maxm];

struct node {
	int u, v;
	node() {}
	node(int a, int b) : u(a), v(b) {}
};
vector<node> ans;

void add_edge(int u, int v, int id) {
	edges[++len].to = v;
	edges[len].id = id;
	edges[len].next = head[u];
	head[u] = len;
}

void dfs(int u) {
	dfn[u] = low[u] = ++times;
	for (int i = head[u]; i; i = edges[i].next) {
		int v = edges[i].to;
		if (vis[edges[i].id]) {
			continue;
		}
		vis[edges[i].id] = 1;
		ans.pb(node(u, v));
		if (!dfn[v]) {
			dfs(v);
			// vis[edges[i].id] = 1;
			low[u] = min(low[u], low[v]);
		} else {
			low[u] = min(low[u], dfn[v]);
		}
		if (low[v] > dfn[u]) {
			puts("0");
			exit(0);
		}
	}
}

void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v, i);
		add_edge(v, u, i);
	}
	dfs(1);
	for (int i = 0; i < (int)ans.size(); ++i) {
		printf("%d %d\n", ans[i].u, ans[i].v);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：一只小咕咕 (赞：1)

[更好的阅读体验](https://www.cnblogs.com/yzxgg/p/solution-cf118e.html)

**Tarjan**

### 思路

先来看一下题目给出的无解的这个样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/raklgm56.png)

不难发现，导致无解的两条边就是 $6 - 7$ 和 $2 - 4$ 这两个桥。所以这个题就转换成了求桥，如果存在桥就是无解。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=3e5+5;
inline int read();
int n,m,cnt=1,head[N],idx,dfn[N],low[N],anscnt;
bool flag,vis[M<<1];
struct E{
	int to,nex,u;
}edge[M<<1];
struct A{
	int x,y;
}ans[M<<1];
void add(int u,int v)
{
	edge[++cnt].to=v;
	edge[cnt].u=u;
	edge[cnt].nex=head[u];
	head[u]=cnt;
}
void tarjan(int x,int fa)
{
	dfn[x]=low[x]=++idx;
	for(int i=head[x];i;i=edge[i].nex)
	{
		int to=edge[i].to;
		if(!dfn[to])
		{
			tarjan(to,x);
			low[x]=min(low[to],low[x]);
			ans[++anscnt]=(A({x,to}));
			if(low[to]>dfn[x])
			{
				flag=1;
				return ;
			}
		}
		else if(to!=fa&&dfn[to]<dfn[x])
		{
			low[x]=min(low[x],dfn[to]);
			ans[++anscnt]=(A({x,to}));//记录一下答案
		}
	}
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		int x,y;
		x=read();y=read();
		ans[i].x=x;ans[i].y=y;
		add(x,y);
		add(y,x);
	}
	tarjan(1,0);
	if(flag)
	{
		puts("0");
		return 0;
	}
	for(int i=1;i<=anscnt;i++)
	{
		printf("%d %d\n",ans[i].x,ans[i].y);
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

## 作者：Little09 (赞：1)

DFS 树。

首先我们要知道，在求割点或桥的时候有一种不用 Tarjan 的算法：DFS 树。如果不了解，我推荐神仙的博客 [link](https://blog.csdn.net/weixin_43848437/article/details/105133155)（其实是翻译）。

我们考虑证明，如果存在桥一定不满足，否则一定可以构造。

- 如果存在桥：假设我们把这条边定向为 $u\to v$，那么显然 $v$ 走不到 $u$ 了。
- 如果不存在桥：我们考虑把 DFS 树上所有边定向为父亲到儿子，其他非树边定向为返祖边。首先显然根能到达所有节点。由于没有桥，在每个点 $x$ 经过几个树边和一个返祖边，一定能到达一个 $x$ 的长辈。这样一直走一定能到达根。

于是这题做完了。当然 Tarjan 也可以做，具体可以看其他神仙的做法。

```cpp
// By: Little09
// Problem: CF118E Bertown roads
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF118E
// Memory Limit: 250 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
const int N=500005;
int n,m;
vector<int>t[N],g[N],id[N];
bool vis[N],cut[N],used[N];
int rt[N],cnt,w[N],dis[N],s[N];
int X[N],Y[N];
inline int read()
{
    int F=1,ANS=0;
	char C=getchar();
    while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
    while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
    return F*ANS;
}
void dfs1(int x,int fa)
{
	vis[x]=1;
	dis[x]=dis[fa]+1;
	for (int i=0;i<t[x].size();i++)
	{
		if (t[x][i]==fa) continue;
		if (vis[t[x][i]]==0) 
		{
			dfs1(t[x][i],x);
			used[id[x][i]]=1;
			g[x].push_back(t[x][i]);
			g[t[x][i]].push_back(x);
		}
		else if (dis[x]>dis[t[x][i]])
		{
			s[x]=min(s[x],dis[t[x][i]]);
		}
	}
}
void dfs2(int x,int fa)
{
	for (int i=0;i<g[x].size();i++)
	{
		if (g[x][i]!=fa) 
		{
			dfs2(g[x][i],x);
			s[x]=min(s[x],s[g[x][i]]);
		}
	}
	if (fa!=0&&s[x]>=dis[x]) cut[x]=1;
}
int main()
{
	n=read(),m=read();
	for (int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		t[x].push_back(y),t[y].push_back(x);
		id[x].push_back(i),id[y].push_back(i);
		X[i]=x,Y[i]=y;
	}
	for (int i=1;i<=n;i++) s[i]=N;
	for (int i=1;i<=n;i++)
	{
		if (vis[i]==0)
		{
			dfs1(i,0),dfs2(i,0);
		}
	}
	for (int i=1;i<=n;i++) 
	{
		if (cut[i]==1)
		{
			puts("0");
			return 0;
		}
	}
	for (int i=1;i<=m;i++)
	{
		int x=X[i],y=Y[i];
		if (dis[x]>dis[y]) swap(x,y); 
		if (used[i]==0) swap(x,y);
		printf("%d %d\n",x,y);
	}
	return 0;
}

```


---

## 作者：npqenqpve (赞：1)

### 题意：
判断是否能把一个无向图的所有无向边改成有向边，使得改完后两两点可达，并给出方案。

### 思路：

不在深度优先生成树上的边必然连到它的祖先或者直接儿子。

然后可以发现，不存在方案等价于任意一种深度优先遍历的方式都存在一个点和它的子树内都没有返祖边。

也就是说，存在桥。

当然，如果知道了结论是桥的话，证明是很简单的，因为删了桥后图不再连通，那么定向后两块一定有一块总到不了另一块。

Tarjan 判一发桥。

然后怎么改，由于已经保证没有桥，所以每个点的子树内都有返祖边，当然就是树上的边指向儿子，剩余的边指向祖先。

为啥这是对的呢，假设根是 $root$。

那么很明显 $root$ 能到达所有点，那么只需要证明所有点都能到 $root$ 即可：

首先，必然存在一个 $root$ 的度大于等于 $2$，选他为正式的 $root$。
那么，肯定是一个边是 $root$ 指向生成树树上的儿子，另一些是 $u$ 指向 $root$ 的（注意方向）。
所以 $root$ 和 $u$ 之间的所有点都能走到 $root$ 了
由于所有在 $u$ 的子树内一定存在 $v$ 满足 $v$ 和 $u$ 的某个祖先有连边，否则就存在桥了。

然后能走到 $root$ 就有传递性了。

感性理解，不能走时就往下走到第一个有返祖边的点再往上跳。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,p[(int)(2e5+10)];
vector<int>e[(int)(2e5+10)];
int fa[(int)(2e5+10)];
int dfn[(int)(2e5+10)],low[(int)(2e5+10)],id=0,num=0;
bool f=0;
struct node
{
    int u,v;
}a[(int)(3e5+10)],b[(int)(3e5+10)];
int top1;
map<pair<int,int>,int>is;
void dfs(int u)
{
    dfn[u]=low[u]=++num;
    for(int i=0;i<e[u].size();i++)
    {
        int v=e[u][i];
        bool fl=0;
        if(!dfn[v])
        {
            b[++top1]=(node){u,v};
            is[make_pair(u,v)]=is[make_pair(u,v)]=1;
            fa[v]=u;dfs(v);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u])
            {
                f=1;
            }
        }
        else 
        {
            if(fa[u]!=v)
            {
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
}
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;cin>>u>>v;
        e[u].push_back(v);e[v].push_back(u);
        a[i]=(node){u,v};
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            dfs(i);
        }
    }
    // for(int i=1;i<=n;i++)
    // {
    //     cout<<dfn[i]<<"\n";
    // }
    // puts("");
    if(f==1) puts("0");
    else 
    {
        for(int i=1;i<=top1;i++)
        {
            cout<<b[i].u<<" "<<b[i].v<<"\n";
        }
        for(int i=1;i<=m;i++)
        {
            if(is[make_pair(a[i].v,a[i].u)]||is[make_pair(a[i].u,a[i].v)]) continue;
            if(dfn[a[i].v]<dfn[a[i].u]) cout<<a[i].u<<" "<<a[i].v<<"\n";
            else cout<<a[i].v<<" "<<a[i].u<<"\n";
        }
    }
    system("pause > null");
}
```

---

## 作者：Underage_potato (赞：0)

## Solution

~~tarjan 判桥板子题。~~

不知道什么是桥的点 **[这里](https://oi-wiki.org/graph/cut/)**。

通过桥的定义可以将本题转化为判断图内是否存在桥，若桥存在便是无解。

那么此题就可以用 tarjan 算法解决了！

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{
	int to,next;
};edge e[600060];
int n,m;
int cnt,head[100010];
int dfn[100010],low[100010],ttg;
int ans[600060][2],tot;
bool vis[600060];
void add_edge(int u,int v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void tarjan(int u,int fa){
	low[u]=dfn[u]=++ttg;
	for(int i=head[u];i;i=e[i].next){
		int j=e[i].to;
		if(j==fa){
			continue;
		}
		if(!dfn[j]){
			tarjan(j,u);
			ans[++tot][0]=u;
			ans[tot][1]=j;
			if(low[j]>dfn[u]){
				cout<<0;
				exit(0);
			}
			low[u]=min(low[u],low[j]);
		}
		else{
			low[u]=min(low[u],dfn[j]);
			if(dfn[j]<dfn[u]){
				ans[++tot][0]=u;
				ans[tot][1]=j;
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add_edge(u,v);
		add_edge(v,u);
	}
	tarjan(1,-1);
	for(int i=1;i<=tot;i++){
		cout<<ans[i][0]<<" "<<ans[i][1]<<endl;
	}
	return 0;
}
```


---

## 作者：马桶战神 (赞：0)

### 一道 Tarjan 好题

**思路**

首先，一个图论题肯定先建图。在体会到 vector 存图的好处之后，我已经放弃了链式前向星（虽然常数小）。

然后，题目说要判断图的连通性，还是无向图改有向图，立刻想到 Tarjan（不清楚 Tarjan 的请看[洛谷官方题单](https://www.luogu.com.cn/training/210#information)）。如果图上有桥（桥的定义请看楼上大佬详细解释），那么一定不行，便输出 $\operatorname{0}$。

如果没有桥便考虑如何将无向改为有向。本来考虑暴力 dfs 找路径，结果发现会 TLE，而本蒟蒻又不会打标记或剪枝。后来突然想到之前在书上看到过直接在 Tarjan 过程中记录路径的操作，便果断使用了。Tarjia 过程中直接记录当前的边，这样跑完 Tarjan 后记录的路径就是答案。

详细请看代码。

**代码**

码风略丑，见谅。

```cpp
#include<bits/stdc++.h>   //万能头
using namespace std;
int read()            //快读
{
	int x=0; bool f=true; char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-') f=false;
		c=getchar();
	}
	while(isdigit(c))
		x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return (f?(x):(-x));
}
void write(int x)      //快写
{
	if(!x)
	{
		putchar('0');
		return ;
	}
	char F[130];
	int tmp=x>0?x:-x ,cnt=0;
	if(x<0) putchar('-');
	while(tmp>0)
	{
		F[cnt++]=tmp%10+'0';
		tmp/=10;
	}
	while(cnt>0) putchar(F[--cnt]);
	return ;
}
int n,m,u,v,cnt=0,low[100005],dfn[100005];   //cnt，dfn数组和low数为tarjan使用
vector<int> e[100005];      //vector存图
vector<pair<int,int> > a;   //用来记录答案的，pair的first是有向边起点，second是终点
bool fl;   //记录有没有桥
void add(int x,int y)     //建图，存边
{
	e[x].push_back(y),e[y].push_back(x);
	return ;
}
void go(int x,int fa)     //tarjan模板+记录路径
{
   	if(fl)
        return ;     //如果找到桥了就返回
	low[x]=dfn[x]=++cnt;
	for(int i=0;i<e[x].size();++i)
	{
		int vv=e[x][i];
		if(vv==fa)
			continue;
		if(!dfn[vv])
		{
			go(vv,x);
			if(fl)
                return ;   //如果找到桥了就直接返回
			a.push_back(make_pair(x,vv));   //记录当前路径
			if(low[vv]>dfn[x])   //找到桥了就记录
			{
			    fl=true;
			    return ;
			}
			low[x]=min(low[x],low[vv]);
		}
		else
		{
			low[x]=min(low[x],dfn[vv]);
			if(dfn[x]>dfn[vv])
				a.push_back(make_pair(x,vv));   //记录当前路径
		}
	}
	return ;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;++i)   //建图
	{
		u=read(),v=read();
		add(u,v);
	}
	go(1,0);
	if(fl)   //如果有桥直接输出0
	{
		putchar('0');
		return 0;
	}
	for(int i=0;i<a.size();++i)
	{
		write(a[i].first);
		putchar(' ');
		write(a[i].second);
		putchar('\n');
	}
	return 0;   //结束程序
}
```


---

