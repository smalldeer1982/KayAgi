# [ABC407G] Domino Covering SUM

## 题目描述

给你一个 $H$ 行 $W$ 列的网格，第 $i$ 行第 $j$ 列的格子上写有数字 $A_{i,j}$。

你要在网格上摆放若干个多米诺骨牌，每个骨牌盖住相邻的两个格子。你要保证没有任何一个格子被多于一个骨牌盖住。

求摆放完骨牌之后，所有**没有**被骨牌盖住的格子上的数字之和的最大值。

## 说明/提示

**样例解释 1**

网格如下所示：

![](https://img.atcoder.jp/abc407/5381f1b744f7aeb5255628f8154a70be.png)

以下的摆放方式中未被盖住的数字之和为 $23$。

![](https://img.atcoder.jp/abc407/138df0fb001c8e55e88f41af1ca61d63.png)

可以证明此值无法达到 $24$ 或更大，故输出 $23$。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
3 4
3 -1 -4 1
-5 9 -2 -6
-5 3 -5 8```

### 输出

```
23```

## 样例 #2

### 输入

```
5 5
-70 11 -45 -54 -30
-99 39 -83 -69 -77
-48 -21 -43 -96 -24
-54 -65 21 -88 -44
-90 -33 -67 -29 -62```

### 输出

```
39```

## 样例 #3

### 输入

```
8 9
-74832 16944 58683 32965 97236 -52995 43262 -51959 40883
-58715 13846 24919 65627 -11492 -63264 29966 -98452 -75577
40415 77202 15542 -50602 83295 85415 -35304 46520 -38742
37482 56721 -38521 63127 55608 95115 42893 10484 70510
53019 40623 25885 -10246 70973 32528 -33423 19322 52097
79880 74931 -58277 -33783 91022 -53003 11085 -65924 -63548
78622 -77307 81181 46875 -81091 63881 11160 -82217 -55492
62770 39530 -95923 92440 -69899 77737 89392 -14281 84899```

### 输出

```
2232232```

# 题解

## 作者：Milthm (赞：7)

### 思路

如果把相邻两个格子连边，则可以将摆放多米诺骨牌看成选择两点之间连的一条边。然后我们发现如果把 $i+j$ 为奇数和 $i+j$ 的偶数的格子分为两个集合，则两个格子内部不会有连边，所以这个图是二分图。

如果一条边的边权为两点的点权和，那么问题就转化为求二分图最小权匹配，用总和减去它就可以得到答案。

考虑再转化为费用流模型，设原点为 $s$ 汇点为 $t$，将 $s$ 向左部连流量为 $1$ 费用为 $0$ 的边，所有点都向 $t$ 连流量为 $1$ 费用为 $0$ 的边。然后如果原图有边 $(u,v)$，则将 $u$ 向 $v$ 连流量为 $1$ 费用为对应边权的边。求这个图的最小费用最大流即可得到原图的二分图最小权匹配。

（为什么所有点都要向 $t$ 连边？因为虽然朴素的二分图最大匹配只需要把右部点连向 $t$，但是最小权匹配并不一定是最大匹配，所以需要给左部点一个不选的机会。）

如果采用 Dinic 实现可能是 $O((hw)^3)$ ，但它通过了这道题目（因为特殊图跑不满的）。不放心的话可以通过 Primal-Dual 原始对偶算法获得 $O((hw)^2 \log (hw))$ 的时间复杂度，这个复杂度就比较对了。


### 闲话

你注意到我这次只通过了 ABCD，因为我不会 E 写挂 F 然后将希望寄托在 G。

我在比赛结束前十分钟的时候写完了 G，但是样例怎么都过不去，最后遗憾离场。

调了半个小时终于发现了，是这样的，如果你和我一样喜欢粘贴模板，一定会记得有个模板叫【模板】最小费用最大流，那题要输出最大流和最小费用，然后我忘记了我的变量 `mf` 是什么意思，误以为字母 F 指的是费用。

于是你就可以看到，在这题的二分图最小权匹配中，我输出了总和减**最大流**。

---

## 作者：EricWan (赞：2)

题意：格图上放 $1\times2$ 大小的牌子，问不被盖住的格子最大权值和。

不被盖住的最大等价于被盖住的最小，观察到当且仅当两个格子相邻，才可能放一个牌子，那么我们把这个东西建图出来，就是一个二分图最小权匹配（不需要完美），然后跑费用流板子，重复找增广路直到增广权值大于等于 $0$。

具体来说，建立源和汇，将格子黑白间隔染色。

+ 源向黑连容量为 $1$，费用是 $0$ 的边，代表一个黑最多被用一次；
+ 白向汇连容量为 $1$，费用是 $0$ 的边，代表一个白最多被用一次；
+ 每一对相邻的黑和白，链接一个容量为 $1$（当然这个并不重要，因为黑和白的限制已经卡紧了），费用是格权和的边。

每一次增广，形如多放一个骨牌（可能调整之前的放置方案），直到再多放骨牌不优（也就是增广权值大于等于 $0$，当然大于 $0$ 也可以），就可以跳出来。想到这里我们就可以粘过来自己喜欢的流子板子了。

代码就不粘在题解里了（有点长，我用的是自己的库），想看我表演建图的可以在[提交记录](https://atcoder.jp/contests/abc407/submissions/66136914)里看。

用 atlib 做应该很容易（我看过 atlib 源码，没有记错的话使用 `mcf_graph<>::slope()` 然后扫前面小于零的增广即可）。

然后大概是不难写的。

---

闲话：我的流子板子是以函数封装的，需要在外面传入指针，换句话说，我的初始化需要再外面做，然后我的 $edge\_cnt$ 没有初始化，边是从 $1$ 开始编号的，使用异或 $1$ 的网络流写法，自然全都乱套了，调到距离考试结束还有负十六分钟才调出来，喜提差一点就 1 Dan。然后下一天 ARC 被 CornerCase 状丝了。

---

## 作者：lao_wang (赞：1)

## 题意

给你一个 $n \times m$ 的矩阵，你能执行多次操作：同时覆盖 $(i,j)$、$(i,j+1)$ 或 $(i,j)$、$(i+1,j)$ 的数字（不能有交集，且两点均在矩阵内）。求剩余数字和的最大值。

## 正文

因为操作不能有交集，所以我们可以先把他看作匹配问题。

又因为是矩阵，所以我们要求的是带权二分图匹配权值最小。

如何使得匹配的权值最小？

注意到费用流的每一次增广后 $dis_{t}$ 单调不降。

所以我们就可以找到增广路后判断一下 $dis_{t}$ 是否是负数，不是则输出答案。（$t$ 为汇点。）

复杂度 $O(n^2m)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define N 112345
#define int long long
#define root(i,j) ((i-1)*m+j)
using namespace std ;
int n , m , a[2123] , dis[N] , head[N] , s , t , fa[N] , cost=0 , cnt=0 ;
bool vis[N] ;
struct node {
	int to , next , w , c ;
} e[N<<1];
void use(int u,int v,int w,int c) {
	e[cnt].to = v ;
	e[cnt].w = w ;
	e[cnt].c = c ;
	e[cnt].next = head[u] ;
	head[u] = cnt++ ;
}
void newnet(int u,int v,int w,int c) {
	use(u,v,w,c) ;
	use(v,u,0,-c) ;
}
bool spfa() {
	for(int i=1; i<=t; i++) dis[i] = (1ll<<60) , vis[i]=0 ;
	queue<int> q ;
	q.push(s) ;
	dis[s] = 0 ;
	while(!q.empty()) {
		int u=q.front() ;
		q.pop() ;
		vis[u] = 0 ;
		for(int i=head[u]; ~i; i=e[i].next) {
			int x=e[i].to ;
			if(dis[u]+e[i].c<dis[x]&&e[i].w) {
				fa[x] = i ;
				dis[x] = dis[u]+e[i].c ;
				if(!vis[x]) q.push(x) , vis[x]=1 ;
			}
		}
	}
	return dis[t]!=(1ll<<60);
}
void flows() {
	while(spfa()) {
		int now=t ;
		while(now!=s) {
			e[fa[now]].w = 0 ;
			e[fa[now]^1].w = 1 ;
			now = e[fa[now]^1].to ;
		}
		if(dis[t]>0) return ;
		cost -= dis[t] ;
	}
}
signed main() {
	memset(head,-1,sizeof head) ;
	cin >> n >> m ;
	s = n*m+1 ; t = s+1 ;
	for(int i=1; i<=m*n; i++) scanf("%lld",a+i) , cost += a[i] ;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(((j&1)&&i&1)||(!(j&1)&&!(i&1))) {
				newnet(s,root(i,j),1,0) ;
				if(i!=1) newnet(root(i,j),root(i-1,j),1,a[root(i,j)]+a[root(i-1,j)]) ;
				if(j!=1) newnet(root(i,j),root(i,j-1),1,a[root(i,j)]+a[root(i,j-1)]) ;
				if(j!=m) newnet(root(i,j),root(i,j+1),1,a[root(i,j)]+a[root(i,j+1)]) ;
				if(i!=n) newnet(root(i,j),root(i+1,j),1,a[root(i,j)]+a[root(i+1,j)]) ;
			}else newnet(root(i,j),t,1,0) ;
		}
	}
	flows() ;
	cout << cost ;
	return 0 ;
}
```

---

## 作者：qqqaaazzz_qwq (赞：1)

没有场切，怎么会逝呢（（（

网格图上放 Domino 骨牌是很经典的套路了，考虑点有点权，然后相邻的两个点之间连一条边，问题转化为我们要找到这个图的最小带权匹配，然后再用 $\sum a_{i,j}$ 减掉最小带权匹配就是答案。

按照 $i+j$ 的奇偶性将图黑白染色，这个图会变成二分图。左边加一个超级源点，右边加一个超级汇点，然后跑最小费用最大流，这道题就做完了。吗？？？

这样做没有正确性，因为 Dinic 可能会为了最大化流量而将费用变高，这不是我们所希望的。这里我想到一种解决方法，就是新建一个点 $w$，所有左部点向 $w$ 连容量 $1$，费用 $0$ 的边，$w$ 向所有右部点连容量 $1$，费用 $0$ 的边，然后再跑最小费用最大流就是对的啦~~

```
2 2
-3 4
5 -6
```

画出来的图长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/xsbd4v9c.png)

My Code :

```cpp
#include <bits/stdc++.h>
#define int long long
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
int n,m,s,t;
int h[10000010],w[10000010],e[10000010],c[10000010],ne[10000010],now[10000010],idx;
const int inf = 1e14;
bool vis[10000010];

void add(int x,int y,int z,int v){
	e[idx] = y;
	w[idx] = z;
	c[idx] = v;
	ne[idx] = h[x];
	h[x] = idx;
	++idx;
	return;
}
bool in[10000010];
int dis[10000010];
bool dead(){
	for (int i=1;i<=n;i++){
		in[i] = false;
		dis[i] = inf;
	}
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	in[s] = true;
	while(!q.empty()){
		int f = q.front();
		now[f] = h[f];
		q.pop();
		in[f] = false;
		for (int i=h[f];~i;i=ne[i]){
			if(w[i]>0&&dis[f]+c[i]<dis[e[i]]){
				dis[e[i]] = dis[f]+c[i];
				if(!in[e[i]]){
					q.push(e[i]);
					in[e[i]] = true;
				}
			}
		}
	}
	if(dis[t]==inf) return false;
	return true;
}
int final,ans;
int dfs(int d,int mi){
	if(d==t){
		return mi;
	}
	vis[d] = true;
	int sum = 0;
	for (int i=now[d];~i && mi;i=ne[i]){
		now[d] = i;
		if(!vis[e[i]]&&w[i]>0&&dis[e[i]]==dis[d]+c[i]){
			int k = dfs(e[i],min(mi,w[i]));
			sum += k;
			final += k*c[i];
			w[i^1] += k;
			w[i] -= k;
			mi -= k; 
		}
	}
	if(sum==0) dis[d] = inf;
	vis[d] = false;
	return sum;
}
int sum = 0;
void Get_ans(){
	while(dead()){
		ans += dfs(s,inf);
	}
	cout << sum-final << "\n";
	return;
}
int A,B;
int a[2010][2010];
int k[2010][2010];
void RADD(int x,int y,int w,int c){
	add(x,y,w,c);
	add(y,x,0,-c);
}

int to(int x,int y){
	return (x-1)*B+y;
}

signed main()
{
	memset(h,-1,sizeof(h));
	cin >> A >> B;
	for (int i=1;i<=A;i++){
		for (int j=1;j<=B;j++){
			cin >> a[i][j];
			sum += a[i][j];
		}
	}
	s = A*B+1,t = A*B+2;
	for (int i=1;i<=A;i++){
		for (int j=1;j<=B;j++){
			if(i+1<=A){
				if((i+j)&1){
					RADD(to(i,j),to(i+1,j),1,a[i][j]+a[i+1][j]);
				}
				else{
					RADD(to(i+1,j),to(i,j),1,a[i][j]+a[i+1][j]);
				}
			}
			if(j+1<=B){
				if((i+j)&1){
					RADD(to(i,j),to(i,j+1),1,a[i][j]+a[i][j+1]);
				}
				else{
					RADD(to(i,j+1),to(i,j),1,a[i][j]+a[i][j+1]);
				}
			}
			if((i+j)&1) RADD(s,to(i,j),1,0);
			else RADD(to(i,j),t,1,0);
		}
	}
	int wow = A*B+3;
	for (int i=1;i<=A;i++){
		for (int j=1;j<=B;j++){
			if((i+j)%2==1){
				RADD(to(i,j),wow,1,0);
			}
			else{
				RADD(wow,to(i,j),1,0);
			}
		}
	}
	n = wow;
	Get_ans();
	return 0;
}
```

---

## 作者：Engulf (赞：0)

网格图上放多米诺骨牌好像是常见套路？

如果相邻节点之间两两连边，且边权为两点权值和，问题就转化为，在这个图上找到一个权值最小的匹配。

又因为网格图是二分图，二分图最小权匹配问题用最小费用最大流解决。

建模如下：
- 首先将网格图黑白染色；
- 建立源点 $s$，对于每个黑点 $u$，连一条 $s \to u$，流量为 $1$，费用为 $0$ 的边；
- 每个黑点 $u$ 向相邻的白点 $v$ 连一条 $u\to v$，流量为 $1$，费用为 $a_u + a_v$ 的边；
- 建立汇点 $t$，每个点 $v$ 向汇点 $t$ 连一条 $v\to t$，流量为 $1$，费用为 $0$ 的边；
- 由于最小权匹配的匹配边的数量（流量）不一定与最大匹配的匹配边数量（流量）相等，因此对于每个黑点 $u$，还需向汇点 $t$ 连一条 $u\to t$ 流量为 $1$，费用为 $0$ 的边。

求上述网络的最小费用最大流即可得到二分图的最小权匹配 $c$。

记原网格中的权值之和为 $s$，答案为 $s-c$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2005, M = 3 * N;

int n, m, s, t;
int maxflow; ll mincost;

struct edge {
    int to, nxt, w;
    ll c;
} e[M << 1];
int cur[N], head[N], ecnt = 1;
void add(int u, int v, int w, ll c) {
    e[++ecnt] = {v, head[u], w, c}, head[u] = ecnt;
    e[++ecnt] = {u, head[v], 0, -c}, head[v] = ecnt;
}

inline int id(int i, int j) {return (i - 1) * m + j;}

ll dis[N];
bool vis[N];

bool spfa() {
    memset(dis, 0x3f, sizeof dis);
    memcpy(cur, head, sizeof head);
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (e[i].w && dis[v] > dis[u] + e[i].c) {
                dis[v] = dis[u] + e[i].c;
                if (!vis[v])
                    vis[v] = 1, q.push(v);
            }
        }
    }
    return dis[t] != 0x3f3f3f3f3f3f3f3f;
}

int dfs(int u, int in) {
    if (u == t) return in;
    vis[u] = 1;
    int out = 0;
    for (int i = cur[u]; i && in; i = e[i].nxt) {
        cur[u] = i;
        int v = e[i].to;
        if (!vis[v] && e[i].w && dis[v] == dis[u] + e[i].c) {
            int fl = dfs(v, min(in, e[i].w));
            mincost += fl * e[i].c;
            in -= fl, out += fl;
            e[i].w -= fl, e[i ^ 1].w += fl;
        }
    }
    vis[u] = 0;
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<vector<ll>> a(n + 1, vector<ll>(m + 1));
    ll sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j], sum += a[i][j];

    s = 0, t = n * m + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            add(id(i, j), t, 1, 0);
            if (i + j & 1) continue;
            add(s, id(i, j), 1, 0);
            static int dir[][2] = {1, 0, 0, 1, -1, 0, 0, -1};
            for (int k = 0; k < 4; k++) {
                int x = i + dir[k][0], y = j + dir[k][1];
                if (x < 1 || x > n || y < 1 || y > m) continue;
                add(id(i, j), id(x, y), 1, a[i][j] + a[x][y]);
            }
        }

    while (spfa()) maxflow += dfs(s, 0x3f3f3f3f);

    cout << sum - mincost << "\n";
    return 0;
}
```

---

## 作者：2012_Zhang_ (赞：0)

本蒟蒻自己想出的第一道 G，写篇题解纪念一下，望管理员大大通过。
## 思路解析
很经典的题。  
先考虑连边，先将图染为黑白两色，  
将 $$S$$ 向白点连一条容量为 $$1$$，费用为 $$0$$ 的边，再将黑点向 $$T$$ 连一条容量为 $$1$$，费用为 $$0$$ 的边。  
接着从白点向相邻的黑点连一条容量为 $$1$$，费用为两点权之和的边，割去相当于覆盖。  
这样整个图就转化为了二分图，跑费用流，用总和减费用就行了。  
但各位神犇眉头一皱，发现事情没那么简单。  
如果只是如此，费用流会为了流量将正点权覆盖了。  
所以在跑费用流时，如果费用为正，就直接退出即可。  
## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e5+5,inf=1e18;
int s,t,head[maxn],to[maxn*2],nxt[maxn*2],val[maxn*2],tot=1,pre[maxn];
int vis[maxn],n,m,a[5005][5005],dist[maxn],flow[maxn*2],dis[maxn];
int dx[]={1,0,-1,0},dy[]={0,1,0,-1},ans,sum,cnt;
queue<int>q;
void add(int a,int b,int v,int w){
	nxt[++tot]=head[a];
	to[tot]=b;
	flow[tot]=v;
	val[tot]=w;
	head[a]=tot;
	nxt[++tot]=head[b];
	to[tot]=a;
	val[tot]=-w;
	head[b]=tot;
}
int id(int x,int y){return x*(m+1)+y;}
bool spfa(){
	for(int i=0;i<=id(n,m)+3;i++) dis[i]=inf;
	memset(vis,0,sizeof vis);
	q.push(s);
	dis[s]=0;
	vis[s]=1;
	dist[s]=inf;
	while(!q.empty()) {
		int x=q.front();
		vis[x]=0;
		q.pop();
		for(int i=head[x];i;i=nxt[i]) {
			int y=to[i];
			if(!flow[i]) continue;
			if(dis[y]>dis[x]+val[i]) {
				dis[y]=dis[x]+val[i];
				dist[y]=min(dist[x],flow[i]);
				pre[y]=i;
				if(!vis[y]) vis[y]=1,q.push(y);
			}
		}
	}
	if(dis[t]==inf) return 0;
	return 1;
}
bool update(){
    if(dis[t]>=0) return 0;
	int x=t;
	while(x!=s){
		int id=pre[x];
		flow[id]-=dist[t];
		flow[id^1]+=dist[t];
		x=to[id^1];
	}
	ans+=dist[t];
	sum+=dis[t];
	return 1;
}
signed main(){
	int num=0;
	cin>>n>>m;
	s=id(n,m)+1,t=id(n,m)+2; 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j],num+=a[i][j];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if((i+j)%2==0) {
                add(s,id(i,j),1,0);
                for(int k=0;k<4;k++){
                    int nx=i+dx[k],ny=j+dy[k];
                    if (nx<1||nx>n||ny<1||ny>m) continue;
                    add(id(i,j),id(nx,ny),1,a[i][j]+a[nx][ny]);
                }
            }
			else add(id(i,j),t,1,0);
        }
    }
	while(spfa()){if(!update()) break;}
	cout<<num-sum;
	return 0;
}

---

