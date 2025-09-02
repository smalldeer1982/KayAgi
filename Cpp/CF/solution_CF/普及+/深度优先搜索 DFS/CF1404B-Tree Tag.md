# Tree Tag

## 题目描述

Alice and Bob are playing a fun game of tree tag.

The game is played on a tree of $ n $ vertices numbered from $ 1 $ to $ n $ . Recall that a tree on $ n $ vertices is an undirected, connected graph with $ n-1 $ edges.

Initially, Alice is located at vertex $ a $ , and Bob at vertex $ b $ . They take turns alternately, and Alice makes the first move. In a move, Alice can jump to a vertex with distance at most $ da $ from the current vertex. And in a move, Bob can jump to a vertex with distance at most $ db $ from the current vertex. The distance between two vertices is defined as the number of edges on the unique simple path between them. In particular, either player is allowed to stay at the same vertex in a move. Note that when performing a move, a player only occupies the starting and ending vertices of their move, not the vertices between them.

If after at most $ 10^{100} $ moves, Alice and Bob occupy the same vertex, then Alice is declared the winner. Otherwise, Bob wins.

Determine the winner if both players play optimally.

## 说明/提示

In the first test case, Alice can win by moving to vertex $ 1 $ . Then wherever Bob moves next, Alice will be able to move to the same vertex on the next move.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404B/49586895aed4babac3e35aba1e1c4162a3ac0674.png)In the second test case, Bob has the following strategy to win. Wherever Alice moves, Bob will always move to whichever of the two vertices $ 1 $ or $ 6 $ is farthest from Alice.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404B/514885d88075ac42c59e9da88fb4903131f99500.png)

## 样例 #1

### 输入

```
4
4 3 2 1 2
1 2
1 3
1 4
6 6 1 2 5
1 2
6 5
2 3
3 4
4 5
9 3 9 2 5
1 2
1 6
1 9
1 3
9 5
7 9
4 8
4 3
11 8 11 3 3
1 2
11 9
4 9
6 5
2 10
3 2
5 9
8 3
7 4
7 10```

### 输出

```
Alice
Bob
Alice
Alice```

# 题解

## 作者：SSerxhs (赞：8)

只有三种情况 Alice 赢

1. $\text{dis}(a,b)\le da$
2. $2\times da\ge db$ 此时只要一步步逼近即可
3. 树的直径 $\le2\times da$ 此时只要占据直径中点即可

以下证明剩下情况必定可以（设 $b$ 为根，特殊链指的是长度大于 $2\times da$ 的链）

1. 若特殊链某一端点到 $b$ 路径上（不含 $b$） 的任意节点不是 $a$ 的祖先

那么直接对着这一端点跳然后特殊链上反复横跳即可

2. 若特殊链在 $a$ 子树内

则 $a$ 往子树内最深处 $d$ 走至少能走 $da+1$ 步，加上 $a,b$ 距离至少为 $da+1$，故 $b$ 到 $d$ 的链一定为特殊链且为 1. 情况，成立

3. 若特殊链一端点到 $b$ 路径不经过 $a$ 且除 $b$ 外还有一个点 $c$ 为 $a$ 祖先

若 $\text{dis(a,c)}>da$ ，则显然存在 1. 情况链，否则直接向 $c$ 沿链（非 $a$ 方向）走显然 Alice 追不上，走到底之后就可以在这条特殊链上反复横跳了
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+2,M=2e5+2;
int lj[M],nxt[M],fir[N],dep[N],md[N],f[N];
int n,c,fh,i,t,a,b,da,db,bs,x,y;
bool ed[N];
inline void add()
{
	lj[++bs]=y;
	nxt[bs]=fir[x];
	fir[x]=bs;
	lj[++bs]=x;
	nxt[bs]=fir[y];
	fir[y]=bs;
}
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
void dfs(int x)
{
	ed[x]=1;md[x]=dep[x];
	for (int i=fir[x];i;i=nxt[i]) if (!ed[lj[i]])
	{
		dep[lj[i]]=dep[x]+1;
		dfs(lj[i]);
		md[x]=max(md[x],md[lj[i]]);
	}
}
void dfsf(int x)
{
	ed[x]=1;md[x]=dep[x];
	for (int i=fir[x];i;i=nxt[i]) if (!ed[lj[i]])
	{
		dep[lj[i]]=dep[x]+1;
		f[lj[i]]=x;
		dfsf(lj[i]);
		md[x]=max(md[x],md[lj[i]]);
	}
}
int main()
{
	read(t);
	while (t--)
	{
		memset(fir+1,bs=0,n<<2);
		memset(f+1,0,n<<2);
		memset(dep+1,0,n<<2);
		memset(md+1,0,n<<2);
		memset(ed+1,0,n*sizeof(bool));
		read(n);read(a);read(b);read(da);read(db);
		for (i=1;i<n;i++)
		{
			read(x);read(y);add();
		}
		if (da+da>=db) {puts("Alice");continue;}
		dep[b]=1;dfs(b);if (dep[a]-1<=da) {puts("Alice");continue;}
		for (i=1;i<=n;i++) if (md[b]==dep[i]) break;
		memset(ed+1,0,n*sizeof(bool));
		memset(dep+1,0,n<<2);
		memset(md+1,0,n<<2);
		dep[i]=1;
		dfs(i);if (md[i]-1<=da+da) {puts("Alice");continue;}
		puts("Bob");
	}
}
```

---

## 作者：AFOier (赞：7)

我们考虑什么情况下Alice可以获胜.

如果$dis_{a,b} \leq da$，则Alice可以一步就追上Bob.

如果Alice处在一个能覆盖整棵树的点，即$2da+1 \geq$树的直径，那么Bob也无处可走了,Alice获胜.

其它情况下，Alice会一步一步逼近Bob，并一定能把Bob逼近某棵子树.

如果当前Alice占据一个点，使Bob无论怎么走都还在Alice的控制范围内，那么Alice必胜.

此时条件即为$2da \geq db$.

除以上条件外，Bob获胜，因为他可以再Alice靠近他的时候不断反向跳走.

```
#include <bits/stdc++.h>
using namespace std;
int n, a, b, da, db, dis[100011];
vector <int> e[100011];
void dfs(int w, int fa) {
	dis[w] = dis[fa] + 1;
	for(int i = 0; i < (int)e[w].size(); i++) {
		int ver = e[w][i];
		if(ver != fa) dfs(ver, w);
	}
}
void solve() {
	scanf("%d%d%d%d%d", &n, &a, &b, &da, &db);
	for(int i = 1; i <= n; i++) e[i].clear();
	for(int i = 1; i < n; i++) {
		int u, v; scanf("%d%d", &u, &v);
		e[u].push_back(v); e[v].push_back(u);
	}
	dfs(1, 0); int maxw = 0;
	for(int i = 1; i <= n; i++) 
		if(dis[maxw] < dis[i]) maxw = i;
	dfs(maxw, 0);
	maxw = 0;
	for(int i = 1; i <= n; i++) 
		if(dis[maxw] < dis[i]) maxw = i;
	if(dis[maxw] <= da*2+1) {
		printf("Alice\n");
		return;
	}
	dfs(a, 0);
	if(dis[b] <= da+1) {
		printf("Alice\n");
		return;
	}
	if(2*da >= db) {
		printf("Alice\n");
		return;
	}
	printf("Bob\n");
}
int main() {
	int t; scanf("%d", &t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：tommymio (赞：7)

$\text{Game}$ 类题目，标准做法先手玩样例，再考虑极限情况。

显然可以发现这样的一个结论：如果 $\text{Alice}$ 无法收缩 $\text{Bob}$ 到达的点，则 $\text{Bob}$ 一定赢。换句话说，如果无论 $\text{Alice}$ 采取什么策略，$\text{Bob}$ 都总是能跳出 $\text{Alice}$ 覆盖的范围，则 $\text{Bob}$ 一定赢。反过来，就是 $\text{Bob}$ 无法跳出 $\text{Alice}$ 覆盖的范围时，$\text{Bob}$ 一定输。

有了这个结论，可以非常方便考虑极限情况。自然是 $\text{Alice}$ 再走一次就能够到达 $\text{Bob}$ 所在的点。此时 $\text{Bob}$ 无法跳出 $\text{Alice}$ 覆盖的范围，$\text{Bob}$ 就一定输。于是只需满足下面三个条件之一，$\text{Alice}$ 一定赢。

- $2\times da\geq \min(db,len)$，与直径 $\text{len}$ 取 $\text{min}$ 是因为直径是树上两点间的最远距离，所以最远 $\text{Bob}$ 一次最远只能走 $\min(db,len)$。 
- $\mathrm{dis(a,b)}\leq da$，即开始时 $\text{Alice}$ 走一步就可以到达。

```cpp
#include<cstdio>
int cnt=0,pos=0;
int dep[100005];
int h[100005],to[200005],ver[200005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void dfs(int x,int fa) {
	if(dep[pos]<dep[x]) pos=x;
	for(register int i=h[x];i;i=ver[i]) {
		int y=to[i];
		if(y==fa) continue; 
		dep[y]=dep[x]+1;
		dfs(y,x);
	}
}
int main() {
	int T=read();
	while(T--) {
		int n=read(),a=read(),b=read(),da=read(),db=read();
		for(register int i=1;i<=n;++i) h[i]=0; cnt=0;
		for(register int i=1;i<n;++i) {
			int x=read(),y=read();
			add(x,y); add(y,x);
		}
		pos=1; dep[1]=0; dfs(1,-1); dep[pos]=0; dfs(pos,-1);
		if(2*da>=db||2*da>=dep[pos]) printf("Alice\n");
		else {
			dep[a]=0; dfs(a,-1);
			if(dep[b]<=da) printf("Alice\n");
			else printf("Bob\n");
		}
	}
	return 0;
}
```

---

## 作者：CYZZ (赞：4)

# [Tree Tag](https://www.luogu.com.cn/problem/CF1404B)
## 题意
Alice 和 Bob（以下简称 A，B）分别在树的两个点上，每两个点间的距离为 1。A 和 B 一步分别能走 $da,db$ 的距离。 A 先走，求 A 能否追上 B。
## 思路
考虑 A 如何追上 B 的情况，有些情况 B 是必败的：

1. $db\le2\times da$。B 一直跑，被逼进死路后再折返，跨过 A。那么折返的时候 B 就要跨过大于 $2\times da$ 的距离，否则下一步就会被 A 追上。所以当 $db\le2\times da$ 时，B 一定能被追上。
2. $2\times da\ge d$，其中 $d$ 为树的直径。因为直径是树上最长的简单路径，所以 A 只需站在直径的中点上，就能覆盖到树上的每一个点。B 无处可逃。
3. 开始时 A 和 B 间的距离小于 $da$，这样 A 第一步就能追上 B。

可以证明除了以上 3 种情况，其它情况 A 都追不上 B， 所以只需要把 3 种情况都判断一下就可以了。

树的直径用两遍 dfs 求出，A 和 B 的初始距离一遍 dfs 求出即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,as,bs,da,db,maxx,head[100005],tot,dis[100005];
struct Edge
{
    int next,to;
}e[200005];
void add_edge(int u,int v)
{
    e[++tot].next=head[u];
    e[tot].to=v;
    head[u]=tot;
}
void dfs(int u,int fa)
{
    if(dis[u]>dis[maxx])
        maxx=u;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa)
			continue;
        dis[v]=dis[u]+1;
		dfs(v,u);
	}
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d%d",&n,&as,&bs,&da,&db);
        tot=0;
		memset(head,0,sizeof head);
        memset(dis,0,sizeof dis);
        for(int i=1;i<n;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            add_edge(x,y);
            add_edge(y,x);
        }
        dfs(as,0);
        int len=dis[bs];
        dis[maxx]=0;
        dfs(maxx,0);
        if(len<=da||db<=2*da||dis[maxx]<=2*da)//判断
            printf("Alice\n");
        else
            printf("Bob\n");
    }
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：Tarsal (赞：3)

## CF1405D 题解

### 题目大意

给定你一棵树， $Alice$ 和 $Bob$ 初始在这棵树上的节点 $a$, $b$。

他们可以在树上轮流移动一段距离不超过 $da$ 和 $db$ 的路径。

路径的定义是 $2$ 点之间简单路径的边数。

如果 $Alice$ 追到了 $Bob$ ，那么则算 $Alice$ 赢，否则算 $Bob$ 赢。

### 题解

我们考虑一下，如果是一条链，那么 $Alice$ 一定会不停的把 $Bob$ 往首尾比逼。

只有当 $Bob$ 可以跨越 $Alice$ 下一步所能覆盖的范围的时候他才可能逃出 $Alcie$ 的魔爪

如这张图

![](https://cdn.luogu.com.cn/upload/image_hosting/x8welagd.png)

蓝色的是 $Alice$ ，红色的是 $Bob$ 只有 $da > 2 * db$ 的时候他才可以逃出魔爪。

但是有另一种情况，就是如果 $2 * db > len$ 那么 $Alice$ 可以每次都到达链上任意一点。

那么我们搬回树上。

我们只需要考虑 $da$ 与 $2 * db$ 的关系。

然后最后考虑的链的长度，我们只要代入成树的直径即可。

### 代码

```
#include <iostream>
#include <string.h>
using namespace std;
const int maxn = 100010;
int T, n, a, RT, b, da, db, cnt, x, y, head[maxn];
struct node {
    int to, nxt, dep;
} e[maxn << 1];
void add(int x, int y) {
    e[++ cnt] = (node) {y, head[x], 0};
    head[x] = cnt;
}
void Dfs(int x, int fa) {
    e[x].dep = e[fa].dep + 1;
    if(e[x].dep > e[RT].dep) {
        RT = x;
    }
    for(int i = head[x]; ~i ; i = e[i].nxt) {
        int v = e[i].to;
        if(v != fa) {
            Dfs(v, x);
        }
    }
}
int main() {
    // freopen("a.in", "r", stdin);
    // freopen("a.out", "w", stdout);
    cin >> T;
    while(T --) {
        cin >> n >> a >> b >> da >> db;
        memset(head, -1, sizeof(head));
        for(int i = 1; i < n; ++ i) {
            cin >> x >> y;
            add(x, y), add(y, x);
        }
        if(db <= (da << 1)) {
            puts("Alice");
            continue;
        }
        RT = a;
        Dfs(a, 0);
        if(e[b].dep <= da + 1) {
            puts("Alice");
            continue;
        }
        Dfs(RT, 0);
        if(e[RT].dep - 1 <= (da << 1)) {
            puts("Alice");
            continue;
        }
        else {
            puts("Bob");
            continue;
        }
    }
    return 0;
}
```

---

## 作者：钓鱼王子 (赞：1)

可以发现，在一些情况 Bob 必败，先是一些很明显的：

1.初始 Alice 能一步到。

2.$da\times 2\geq db$ 也就是说逼到死角之后 Bob 无处可去。

但还有一种情况，就是 Bob 跳不到 $db$，也就是说，因为树不够大。而 Bob 此时最多能跳的长度为直径，将 $db$ 与直径取 $\min$ 即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t; 
}
int t,n,m,a,b,da,db,head[100002],cnt,vis[200002],mxd,mxp,fa[200002];
struct edge{
	int to,next;
}e[200002];
inline void add(re int x,re int y){
	e[++cnt]=(edge){y,head[x]};
	head[x]=cnt;
}
inline void dfs(re int x,re int y,re int z){
	if(z>mxd)mxd=z,mxp=x;
	fa[x]=y;
	for(re int i=head[x];i;i=e[i].next)if(e[i].to^y)dfs(e[i].to,x,z+1);
}
int main(){
	t=read();
	while(t--){
		n=read(),a=read(),b=read(),da=read(),db=read();
		for(re int i=1;i<=n;++i)head[i]=0,vis[i]=-1;
		for(re int i=1,x,y;i<n;++i)x=read(),y=read(),add(x,y),add(y,x);
		mxd=0,dfs(1,0,1);
		re int x=a,y=b,z=0,dis=0;
		while(x)vis[x]=z++,x=fa[x];
		while(vis[y]==-1)y=fa[y],++dis;
		dis+=vis[y];
		if(dis<=da||da*2>=db)puts("Alice");
		else{
			dfs(mxp,mxp,1);
			if(da*2>=mxd-1)puts("Alice");
			else puts("Bob");
		}
	}
}
```


---

## 作者：lory1608 (赞：1)

本来这一题很简单，但在打比赛的时候没想清楚，然后就没做出来。

显然，答案为 $\texttt{Alice}$ 当且仅当以下三个条件之一满足：

- $\texttt{Alice}$ 和 $\texttt{Bob}$ 的距离小于等于$da$。

- $db \leq 2\times da$ 。

- 树的直径长度 $\leq 2\times da$ 。

其余情况下，可以证明 $\texttt{Bob}$ 一定能赢。

复杂度 $\Theta(\sum n)$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#include<set>
#define IN inline
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(u) for(int i=p[u];i!=-1;i=e[i].nxt)
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
using namespace std;
inline int getint()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return (f==1)?x:-x;
}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int maxn=1e5+5;
int T,n,p[maxn],sz,a,b,da,db; 
struct edge
{
	int v,nxt;
	edge(int vv=0,int nn=0){v=vv,nxt=nn;}
}e[maxn<<1];
inline void add(int u,int v)
{
	e[++sz]=edge(v,p[u]);
	p[u]=sz;
}
int dis[maxn];
inline void dfs(int u,int fa)
{
	REP(u)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dis[v]=dis[u]+1;
		dfs(v,u);
	}
}
int main()
{
	T=getint();
	while(T--)
	{
		n=getint();
		sz=0;
		FOR(i,1,n)p[i]=-1;
		a=getint(),b=getint(),da=getint(),db=getint();
		FOR(i,1,n-1)
		{
			int u=getint(),v=getint();
			add(u,v);
			add(v,u);
		}
		FOR(i,1,n)dis[i]=0;
		dfs(a,0);
		int maxpos,maxdis=0;
		if(dis[b]<=da)
		{
			printf("Alice\n");
			continue;
		}
		FOR(i,1,n)if(dis[i]>maxdis)maxpos=i,maxdis=dis[i];
		FOR(i,1,n)dis[i]=0;
		dfs(maxpos,0);
		FOR(i,1,n)if(dis[i]>maxdis)maxpos=i,maxdis=dis[i];
		if(min(maxdis,db)<=2*da)printf("Alice\n");
		else printf("Bob\n");
	}
	return 0;
}
```

---

## 作者：ZZZZZZZF (赞：0)

### 思路
~~问就是没思路~~

先手玩数据，发现只有当 Bob 可以一步跨过 Alice 的攻击范围时才能逃脱，否则 Alice 就可以通过一步一步逼近抓住 Bob。

再考虑极限：
 
1. 如果节点数过少，Alice 站在树的中间时就可以覆盖到全部节点，那么 Bob 将无处可逃。设树直径的边数为 $D$，即 $D \le 2\times da$。


2. 如果 Alice 和 Bob 距离过近，以至于 Alice 第一步就能抓住 Bob，那么 Bob 将插翅难飞
。设两人初始距离为  $Dis$，即 $Dis \le da$。

求一下树的直径和 Alice 与 Bob 在 $0$ 时刻的距离即可。时间复杂度 $O(n)$。

关于树的直径，随便挑一个点，求其距离最远点 $a$，再求出距 $a$ 最远的点 $b$，顺便求出两点距离 $D$。$a b$ 即为直径端点，距离即为直径。

注意多组询问需要反复初始化。

### Code: 
```
#include<bits/stdc++.h>
#define M 100010
#define N 100010
using namespace std;

struct edge{
    int v,next;
}e[M*2];

int m,n,tt,a,b,da,db;
int head[N],eNum[N];

//看起来输入挺多，用了快读
inline int read() {
	int x = 0, k = 1, c = getchar();
	while (c > '9' || c < '0') { if (c == '-')k = -1; c = getchar(); }
	while (c <= '9' && c >= '0')x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return x * k;
}

void add(int u,int v){
    e[++tt].next = head[u];
    e[tt].v = v;
    head[u] = tt;
    return;
}

//双bfs获取直径
int getD(){
    queue <pair<int,int>> q;
    int vis[N],max1 = 0,n1,n2;

    for(int i = 1;i<=n;i++)
        vis[i] = 0;
    
    q.push(pair<int,int>{1,0});
    while(!q.empty()){
        int u = q.front().first,d = q.front().second;
        q.pop();
        if(d>max1){
            n1 = u;
            max1 = d;
        }
        vis[u] = 1;
        for(int i = head[u];i;i = e[i].next){
            int v = e[i].v;
            if(vis[v] == 0)
                q.push(pair<int,int>{v,d+1});
        }
    }

    for(int i = 1;i<=n;i++)
        vis[i] = 0;
    while(!q.empty())q.pop();
    max1 = 0;

    q.push(pair<int,int>{n1,0});
    while(!q.empty()){
        int u = q.front().first,d = q.front().second;
        q.pop();
        if(d>max1){
            n2 = u;
            max1 = d;
        }
        vis[u] = 1;
        for(int i = head[u];i;i = e[i].next){
            int v = e[i].v;
            if(vis[v] == 0)
                q.push(pair<int,int>{v,d+1});
        }
    }

    return max1;
}

//获取两点间距离
int dfs(int num,int d,int f){
    if(num == b) return d;
    int ans = 0;
    for(int i = head[num];i;i = e[i].next){
        int v = e[i].v;
        if(v!=f)
            ans+=dfs(v,d+1,num);
    }
    return ans;
}

int main(){
    int T = read();
    while(T--){
        n = read(),a = read(),b = read(),da = read(),db = read();
        m = n-1,tt = 0;
        for(int i = 1;i<=n;i++)
            head[i] = 0;

        for(int i = 1,u,v;i<=m;i++){
            u = read(),v = read();
            add(u,v);
            add(v,u);
            eNum[u]++;
            eNum[v]++;
        }
        
        /*邻接表检验
        printf("\n");
        for(int u = 1;u<=n;u++){
            for(int i = head[u];i;i = e[i].next){
                printf("%d %d\n",u,e[i].v);
            }
            printf("\n");
        }
        printf("\n");
        */

        int D = getD();
        int abD = dfs(a,0,-1);

        if(abD<=da)
            printf("Alice\n");	//一步抓住
        else if(2*da>=D)
            printf("Alice\n");	//Alice地图炮
        else if(db>da*2)
            printf("Bob\n");	//Bob一步逃出Alice范围
        else   
            printf("Alice\n");	//Bob腿短

    }

    return 0;
}

```

---

## 作者：神光qwq (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1404B)

## 思维历程

~~以下是蒟蒻在做题时的内心想法，可能对于您下一次做这种的类似题思考有帮助。~~

首先分析距离即 $a$ 和 $b$ 的不同对答案的影响，设距离为 $dis$，当 $dis$ 极大时显然无影响（毕竟没有威胁 Bob 再跑也不会有啥用），考虑较近情况。

- 当 $dis \le da$ 时，这里直接一步就能追到。

接下来考虑 $da$ 和 $db$ 的影响。

- 当 $db \le 2da$ 时，考虑逼近法，即 Alice 把 Bob 一步一步逼向子树，由于满足条件所以 Bob 不可能直接从 $dis>da$ 的子树里直接跳到仍旧满足 $dis>da$ 的父亲节点，即不可能从一个安全但必定会被逼迫到 $dis \le da$ 的位置跳到另一个~~有更大发展空间~~的安全位置。

此时 $da$ 较大的情况考虑过了，较小时易证更难满足情况，而且对于 $dis$ 的影响情况也考虑过了，但是对于 $db$ 我们此时只考虑了其较小的时候，并未考虑较大时。

但是 $db$ 较大的话就很难保证追上（毕竟可以用第二条说的不能满足的策略一直跑路），但是还有一个一直被忽略的东西，那就是树本身的性质。

**那么，这又会有什么影响呢？**

可以发现，这其实是对 $db$ 规定了一个上界，毕竟你不可能一下跳出这颗树，那么我们就得知了这道题的最后一块拼图，即设树的直径为 $len$，有 $truedb \le len$，这里的 $truedb$ 表示的是对于这颗树 Bob 实际上能跳跃距离的上界，此时再回望第二条性质，发现一切都串起来了。

- 当 $len \le 2da$ 时，可以通过第二条的策略来追上。

此时我们对于所有可以用上的性质都用过了，所以，完结撒花。

~~本人拙见，如有差错，请赐教。~~

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define void inline void
using namespace std;
const ll N=1e5+10;
ll T,n,a,b,da,db,root=1;
ll cnt,h[N],nxt[N<<1],to[N<<1],depth[N];
inline ll read(){
	char ch=getchar();ll res=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}
void add(ll x,ll y){
	nxt[++cnt]=h[x],to[cnt]=y,h[x]=cnt;
}
void dfs(ll x,ll fa,ll dep){
	depth[x]=dep;
	if(depth[x]>depth[root]) root=x;
	for(ll i=h[x];i;i=nxt[i]){
		ll v=to[i];
		if(v==fa) continue;
		dfs(v,x,dep+1);
	}
}
int main(){
	T=read();
	while(T--){
		n=read(),a=read(),b=read(),da=read(),db=read(),cnt=0,root=1;
		for(ll i=1;i<=n;i++) h[i]=0;
		for(ll i=1;i<n;i++){
			ll X=read(),Y=read();
			add(X,Y),add(Y,X);
		}
		dfs(1,0,1),dfs(root,0,1);//对于这种不要求复杂度的题，直接两遍 dfs 是非常方便额的
		if(2*da>=db||2*da>=depth[root]-1){printf("Alice\n");continue;}
		dfs(a,0,1);
		if(da>=depth[b]-1){printf("Alice\n");continue;}
		printf("Bob\n");
	}
	return 0;
}

```


---

## 作者：Sol1 (赞：0)

完全不会博弈论，vp 的时候想了 40min /kk

从 Alice 的角度考虑，如何把 Bob 逼到死角？

显然 Alice 不希望 Bob 直接跨过自己跑到外面，很容易得到的结论是 Alice 会尝试在尽量远的地方威胁吃掉 Bob。

那么 Alice 的策略确定了，就可以分析 Bob 什么时候能赢。

首先，如果自己翻不掉 Alice，那么一定会输。如果能翻掉 Alice：

- 如果 Alice 第一步就能吃掉自己，那么一定输；
- 如果 Alice 能够控制的半径达到树直径的一半，那么 Alice 一定有一个位置能够控制整个树，也一定输。
- 其余情况下，Bob 处在 Alice 被控制的区域内时一定可以移动到一个没有被控制的点，不在的时候不动就可以，一定能赢。

所以算法就很明显了：

- 首先判断一步能不能吃到，能则输出 Alice；
- 然后判断 Bob 能不能翻掉 Alice，不能则输出 Alice；
- 然后求直径，判断 Alice 能不能控制整个树，能则输出 Alice；
- 否则输出 Bob。

复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

struct Edge {
	int to, nxt;
	Edge() {
		nxt = -1;
	}
};
Edge e[200005];
int n, hd[100005], pnt, a, b, da, db, dep[100005], du;

inline void AddEdge(int u, int v) {
	e[++pnt].to = v;
	e[pnt].nxt = hd[u];
	hd[u] = pnt;
}

inline void Clr() {
	pnt = 0;
	for (int i = 1;i <= n;i++) hd[i] = -1;
}

inline void Read() {
	n = qread(); a = qread(); b = qread(); da = qread(); db = qread();
	Clr();
	for (int i = 1;i < n;i++) {
		int u = qread(), v = qread();
		AddEdge(u, v);
		AddEdge(v, u);
	}
}

inline void Dfs(int u, int fa) {
	if (dep[du] < dep[u]) du = u;
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa) {
			dep[e[i].to] = dep[u] + 1;
			Dfs(e[i].to, u);
		}
	}
}

inline void Solve() {
	dep[a] = 0;
	Dfs(a, -1);
	if (dep[b] <= da) {
		cout << "Alice\n";
		return;
	}
	if (db <= da * 2) {
		cout << "Alice\n";
		return;
	}
	du = 0;
	dep[1] = 0;
	Dfs(1, -1);
	dep[du] = 0;
	Dfs(du, -1);
	int len = dep[du];
	if (len <= da * 2) {
		cout << "Alice\n";
		return;
	}
	cout << "Bob\n";
}

int main() {
	std::ios::sync_with_stdio(0);
	int t = qread();
	while (t--) {
		Read();
		Solve();
	}
	cout.flush();
	#ifdef CFA_44
	while (1) getchar();
	#endif
	return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# [Tree Tag 传送门](https://www.luogu.com.cn/problem/CF1404B)

# 题目解释
有两个人 $\text{Alice}$ 和 $\text{Bob}$ 在一棵树上相互追逐，$\text{Alice}$ 先走 $da$ 步，$\text{Bob}$ 走 $db$ 步。问 $\text{Alice}$ 在 $10^{100}$ 步内能否追上 $\text{Bob}$。~~其实就是问有没有可能追上。~~
# 题目分析
如果 $\text{Alice}$ 无法收缩 $\text{Bob}$ 到达的点，则 $\text{Bob}$ 一定赢。换句话说，如果无论 $\text{Alice}$ 采取什么策略，$\text{Bob}$ 都总是能跳出 $\text{Alice}$ 覆盖的范围，则 $\text{Bob}$ 一定赢。反过来，就是 $\text{Bob}$ 无法跳出 $\text{Alice}$ 覆盖的范围时，$\text{Bob}$ 一定输。
### 先推个结论
因为走的次数是 $10^{100}$，~~接近无限大。~~ 显然如果 $\text{Alice}$ 能赢，那一定有一个状态：一步之内就能追上 $\text{Bob}$。反过来说，如果 $\text{Alice}$ 下一步追不上 $\text{Bob}$，那 $\text{Alice}$ 就一定输。
### 然后
$\text{Alice}$ 再走一次就能够到达 $\text{Bob}$ 所在的点。此时 $\text{Bob}$ 无法跳出 $\text{Alice}$ 覆盖的范围，$\text{Bob}$ 就一定输。于是只需满足三个条件，$\text{Alice}$ 一定赢。
### 三个条件
- $\text{dis}(a,b)\le da$
- $2\times da\ge db$
- 树的直径 $\le2\times da$

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int ans;
int dep[MAXN];
int head[MAXN];
int tot;
int n,a,b,da,db;
struct node{
    int nxt;
    int to;
}e[MAXN<<1];
void init(){for(int i=1;i<=n;i++)head[i]=0;tot=0;}
void edgeadd(int u,int v){
    e[++tot].to=v;
    e[tot].nxt=head[u];
    head[u]=tot;
}
void read(){
	cin>>n>>a>>b>>da>>db;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		edgeadd(u,v);
		edgeadd(v,u);
	}
}
void A(){cout<<"Alice\n";}
void B(){cout<<"Bob\n";}
void dfs(int u,int fa) {
	if(dep[ans]<dep[u])
        ans=u;
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
}
int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
	while(T--){
		init();
		read();
		ans=1;
		dep[1]=0;dfs(1,-1);
		dep[ans]=0;dfs(ans,-1);
		if(2*da>=db||2*da>=dep[ans])
			A();
		else {
			dep[a]=0;
			dfs(a,-1);
			if(dep[b]<=da)
				A();
			else
				B();
		}
	}
}

```

---

## 作者：Fairicle (赞：0)

大概可以看作一个 Alice 追击 Bob 的问题，并且 Alice 先走。

那么如果一开始 $a,b$ 的距离就小于了 $da$，Alice 必然胜利。

接下来就是对于这种 game 类型题目的通常考虑方法：构造极限情况。

这题的极限情况是什么呢？应当是 Alice 移动之后，两人相距恰好为 $da$，且 Bob 下一步必须跨过 Alice。如果跨过之后 Bob 安全了，说明 $db>2*da$ 且树的直径 $len>2*da$。如果满足，则 Alice 永远不可能追上 Bob，Bob 只需要在直径上反复横跳即可。

code：
```cpp
struct node{
	int nxt,to;
}star[N<<1];
int t,n,a,b,da,db,head[N],x,y,wl;
inline void add(int from,int to){
	wl++;
	star[wl].to=to;
	star[wl].nxt=head[from];
	head[from]=wl;
}
int mxdep,pos,depth;
inline void dfs(int x,int fa,int dep){
	if(dep>mxdep){pos=x,mxdep=dep;}
	for(ri i=head[x];i;i=star[i].nxt){
		int u=star[i].to;
		if(u==fa) continue;
		dfs(u,x,dep+1);
	}
}
inline void dfs2(int x,int fa,int dep){
	if(x==b) depth=dep;
	for(ri i=head[x];i;i=star[i].nxt){
		int u=star[i].to;
		if(u==fa) continue;
		dfs2(u,x,dep+1);
	}
}
inline int rd(){
	int x=0,flg=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flg=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*flg;
}
int main(){
	t=rd();
	while(t--){
		depth=0;
		n=rd(),a=rd(),b=rd(),da=rd(),db=rd();
		wl=0;
		for(ri i=1;i<n;++i){
			x=rd(),y=rd(),add(x,y),add(y,x);
		}
		dfs2(a,0,0);
		dfs(1,0,0);
		mxdep=0;
		dfs(pos,0,0);
		if(mxdep>2*da&&db>2*da&&depth>da) puts("Bob");
		else puts("Alice");
		for(ri i=1;i<=n;++i) head[i]=0;mxdep=0;
	}
	return 0;
}
```


---

