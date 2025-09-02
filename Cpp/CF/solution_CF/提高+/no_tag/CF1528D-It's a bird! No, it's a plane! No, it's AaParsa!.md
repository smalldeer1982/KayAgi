# It's a bird! No, it's a plane! No, it's AaParsa!

## 题目描述

There are $ n $ cities in Shaazzzland, numbered from $ 0 $ to $ n-1 $ . Ghaazzzland, the immortal enemy of Shaazzzland, is ruled by AaParsa.

As the head of the Ghaazzzland's intelligence agency, AaParsa is carrying out the most important spying mission in Ghaazzzland's history on Shaazzzland.

AaParsa has planted $ m $ transport cannons in the cities of Shaazzzland. The $ i $ -th cannon is planted in the city $ a_i $ and is initially pointing at city $ b_i $ .

It is guaranteed that each of the $ n $ cities has at least one transport cannon planted inside it, and that no two cannons from the same city are initially pointing at the same city (that is, all pairs $ (a_i, b_i) $ are distinct).

AaParsa used very advanced technology to build the cannons, the cannons rotate every second. In other words, if the $ i $ -th cannon is pointing towards the city $ x $ at some second, it will target the city $ (x + 1) \mod n $ at the next second.

As their name suggests, transport cannons are for transportation, specifically for human transport. If you use the $ i $ -th cannon to launch yourself towards the city that it's currently pointing at, you'll be airborne for $ c_i $ seconds before reaching your target destination.

If you still don't get it, using the $ i $ -th cannon at the $ s $ -th second (using which is only possible if you are currently in the city $ a_i $ ) will shoot you to the city $ (b_i + s) \mod n $ and you'll land in there after $ c_i $ seconds (so you'll be there in the $ (s + c_i) $ -th second). Also note the cannon that you initially launched from will rotate every second but you obviously won't change direction while you are airborne.

AaParsa wants to use the cannons for travelling between Shaazzzland's cities in his grand plan, and he can start travelling at second $ 0 $ . For him to fully utilize them, he needs to know the minimum number of seconds required to reach city $ u $ from city $ v $ using the cannons for every pair of cities $ (u, v) $ .

Note that AaParsa can stay in a city for as long as he wants.

## 说明/提示

In the first example one possible path for going from $ 0 $ to $ 2 $ would be:

1. Stay inside $ 0 $ and do nothing for $ 1 $ second.
2. Use the first cannon and land at $ 2 $ after $ 1 $ second.

Note that: we could have used the second cannon in $ 0 $ -th second but it would have taken us $ 3 $ seconds to reach city $ 2 $ in that case.

## 样例 #1

### 输入

```
3 4
0 1 1
0 2 3
1 0 1
2 0 1```

### 输出

```
0 1 2 
1 0 2 
1 2 0```

## 样例 #2

### 输入

```
6 6
0 0 1
1 1 1
2 2 1
3 3 1
4 4 1
5 5 1```

### 输出

```
0 2 3 3 4 4 
4 0 2 3 3 4 
4 4 0 2 3 3 
3 4 4 0 2 3 
3 3 4 4 0 2 
2 3 3 4 4 0```

## 样例 #3

### 输入

```
4 5
0 1 1
1 3 2
2 2 10
3 0 1
0 0 2```

### 输出

```
0 1 2 3 
3 0 3 2 
12 13 0 11 
1 2 2 0```

# 题解

## 作者：nao_nao (赞：8)

> 非常奇妙的一道题呢

思考一下这个神奇的道路，我们多等一秒就将 $u\to v$ 的路变成 $u\to v+1$ 。某种意义上来讲有 $v\to v+1$ 的一条路，它花费的时间是一秒，代价为 $1$ 。

也许我们到达一个点之后需要等待才是最优的，但是无论如何，尽早到达总是好的，所以可以使用最短路求解。

我们对于每一个节点都求一遍最短路。对于每一次求取最短路的时候。我们再建出来一个点作为起点（假装有）。对于这个起点，我们肯定没有办法将它向编号下一个的点以 $1$ 的代价转移。除去起点，其他点都可以这样做，因此将起点特殊处理。

每次转移可以看做有两种，一种是直接沿着出边当前指向的地方直接转移，另一种是等待一段时间。如何处理等待，前文已经提到过了。

首先将起点连向的出边指向的地方都更新答案为边权，然后开始跑木得优化的 $\text{dijkstra}$ 。毕竟边实在是太多了。

$\text{dijkstra}$ 中每次枚举到的当前点，我们将它向下一个编号转移一下。略加思考可以发现这样是正确的。毕竟枚举的点按照顺序答案不降。

就这样即可在 $O(n^3+nm)$ 的复杂度下解决这道题。

```cpp
const int N=1e6+7;
const ll inf = 1e18+7;
int n,m;
int head[N],go[N],nxt[N],cnt,val[N],vis[N];
ll dis[N],d[N];
void add(int u,int v,int w)
{
	go[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
	val[cnt] = w;
}
void print(ll s)
{
	if(s >= 10) print(s/10);
	putchar('0'+s%10);
}
#define mymin(a,b) ((a)>(b)?(b):(a))
#define mod(x) ((x-1)%n+1)
void dij(int pos)
{
	for(int i = 1;i <= n;i ++) dis[i] = inf,vis[i] = 0;
	vis[pos] = 0;
	for(int e = head[pos];e;e = nxt[e]) {
		int v = go[e];
		dis[v] = mymin(dis[v],val[e]);
	}
	for(int o = 1;o <= n;o ++) {
		int x = 0;
		for(int i = 1;i <= n;i ++) if(!vis[i] && (!x || dis[x] > dis[i])) x = i;
		vis[x] = 1;int u = x;
		dis[u%n+1] = mymin(dis[u]+1,dis[u%n+1]);
		for(int e = head[u];e;e = nxt[e]) {
			int v = mod(dis[u]+go[e]);
			dis[v] = mymin(dis[v],dis[u] + val[e]);
		}
	}
	for(int i = 1;i <= n;i ++) print((i!=pos)*dis[i]),putchar(' ');
	puts("");
}

int main()
{
	n = read(),m = read();
	for(int i = 1;i <= m;i ++) {
		int u = read()+1,v = read()+1,w = read();
		add(u,v,w);
	}
	for(int i = 1;i <= n;i ++) dij(i);
	return 0;
}
```
至少在我提交的时候可以过qwq。


---

## 作者：7KByte (赞：7)

$n\le 600$ 的最短路，考虑 dijkstra 或 floyd 。

对于这道题来说，我们一定是先考虑尽早到达当前点，然后考虑从当前点出发到其他节点，其中可以在当前点停留一下。

这和 dij 的思路非常类似。

考虑目前还没有扩展的距离最近的点为 $x$。记录 $w$ 数组，$w_i$ 表示从目前的 $x$ 出发的最短距离。

计算在第 $d_x$ 时刻各条边指向的节点，先不等待，直接更新 $w$ 数组。

然后令 $w_i=\max\{w_i,w_{i-1}+1\}$ 进行松弛，表示进行一秒钟的等待。

总共跑 $n$ 次 dij ，堆优化时间复杂度为 $\rm O(N(M\log M))$，事实上边数非常大，所以不使用堆反而更优，时间复杂度 $\rm O(N(N^2+M))$ 。

被卡常的赛时代码 ，不影响阅读。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 605
#define int long long 
using namespace std;
int n,m,h[N],tot;
struct edge{int to,nxt,val;}e[N*N];
void add(int x,int y,int z){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;e[tot].val=z;}
int d[N],v[N],w[N];
int g(int x){
	return (x-1)%n+1;
}
void dij(int s){
	memset(d,0x3f,sizeof(d));
	memset(v,0,sizeof(v));d[s]=0;
	rep(t,1,n){
		int x=0;
		rep(j,1,n)if(!v[j]&&(!x||d[j]<d[x]))x=j;
		v[x]=1;
		memset(w,0x3f,sizeof(w));
		for(int i=h[x];i;i=e[i].nxt){
			int ed=g(e[i].to+d[x]);
			w[ed]=min(w[ed],d[x]+e[i].val);
		}
		rep(i,1,n*2)w[g(i+1)]=min(w[g(i+1)],w[g(i)]+1);
		rep(i,1,n)d[i]=min(d[i],w[i]);
	}
	rep(i,1,n)printf("%lld ",d[i]);putchar('\n');
}
signed main(){
	scanf("%lld%lld",&n,&m);
	rep(i,1,m){
		int x,y,z;scanf("%lld%lld%lld",&x,&y,&z);
		add(x+1,y+1,z);
	}
	rep(i,1,n)dij(i);
	return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：3)

提供一个比较奇怪的思路，并不确定和其他题解的本质是否相同。

首先考虑固定一个起点 $s$，显然我们对于 $1\sim n$ 的每个点都要算一次。

考虑从 $s\to x$ 的所有路径中最短的那一条，一定是从 $s\to y$ 再从 $y$ 可能等待一会然后一步走到 $x$ 的。

思索一下有什么性质，发现 $s\to y$ 使用所有路径中最短的那一条路径一定是不劣的，因为到 $y$ 的时间越早越好，大不了多等一会也能取到最优情况。

于是我们自然的想到一个做法是在确定 $s\to a$ 不会被其他路径更新的时候去更新所有的 $s\to b$，此时 $s\to a$ 的长度一定是最短的了。

而确定 $s\to a$ 这条路径最短的办法就是其他路径要么比 $s\to a$ 大就不可能更新我了，要么已经更新过了，发现就是个 Dij 的过程，但是转移好像还比较麻烦。

考虑走到了一个点 $x$ 时刻是最小的 $t$ 要去更新其他所有点的过程。

以下均对编号取模。

一条边 $x\to y$ 代价是 $v$ 被用到了，一定是用来走 $x\to (y+t)\sim(y+t+k)$ 这样一段连续的区间。

那么就设计这样一个更新的过程：

- 先随便选一条边 $x\to(y+t)$

- 然后更新 $(y+t),(y+t+1),(y+t+2),\cdots$，显然代价就分别是 $v,v+1,v+2,\cdots$

- 直到更新到某个 $x\to(y+t+k)$ 发现有一条 $x\to(y'+t)$ 的边代价为 $v'$ 比 $v+k$ 优，就换成用它继续往后更新，也即回到第二步。

- 最后发现 $x\to (y''+t)$ 代价为 $v''$ 比 $v+k$ 优而且**已经更新过**的时候停止。

不难发现这样最多转两圈，第一圈找这条边，第二圈更新，那么仍然是 $O(n)$ 的。

对于每个点都做一次就是 $O(n^2)$ 的，而且所有边都可能用到，总共是 $O(m)$ 的。

最后乘个起点的 $n$ 总共 $O(n^3+nm)$。

---

## 作者：COsm0s (赞：2)

`Dijkstra.`

题目中给出 $s$ 可以为任意值，但是简单思考就会发现，由于指向点是在 $\bmod\ n$ 的情况下，所以 $s$ 最大为 $n - 1$。

我们每次钦定一个起点，从此点开始求最短路。

显然因为有等待这个条件，所以相当于 $x$ 点必定可以指向 $x+1$ 点，且路径长度为 $1$。

即 $u\to x$ 时多等一秒，使得 $u\to x+1$。

那么转移的方法就出来了。

+ 直接沿着出边当前指向的地方直接转移。

+ 等待一段时间。

对于第二种转移，只需要转移 $x+1$ 即可，这是因为枚举点的顺序在路径长度意义上是单调不降的（即 dijkstra 性质）。

复杂度 $\Theta(n^3+nm)$，注意常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define REP(i, a, b) for(int i = a; i <= b; ++ i)
namespace Cosmos {
	const int N = 1e6 + 5, MAXN = LLONG_MAX;
	int n, m;
	int head[N], cnt, flag[N];
	int dis[N], d[N];
	struct node {
		int to, val, next;
	} E[N << 1];
	void add(int x, int y, int z) {
		E[++ cnt].to = y;
		E[cnt].val = z;
		E[cnt].next = head[x];
		head[x] = cnt;
	}
	int main() {
		cin >> n >> m;
		REP(i, 1, m) {
			int x, y, z;
			cin >> x >> y >> z;
			++ x, ++ y;
			add(x, y, z);
		}
		REP(point, 1, n) {
			REP(i, 1, n) {
				dis[i] = MAXN, flag[i] = 0;
			}
			flag[point] = 0;
			for (int i = head[point]; i; i = E[i].next) {
				int v = E[i].to;
				int val = E[i].val;
				dis[v] = min(dis[v], val);
			}
			REP(i, 1, n) {
				int x = 0;
				REP(j, 1, n) if (!flag[j] && (!x || dis[x] > dis[j])) x = j;
				flag[x] = 1;
				int u = x;
				dis[u % n + 1] = min(dis[u] + 1, dis[u % n + 1]);
				for (int j = head[u]; j; j = E[j].next) {
					int v = (E[j].to + dis[u] - 1) % n + 1;
					int val = E[j].val;
					dis[v] = min(dis[v], dis[u] + val);
				}
			}
			REP(i, 1, n)
				if (i != point) cout << dis[i] << ' ';
				else cout << 0 << ' ';
			cout << '\n';
		}
		return 0;
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	int T = 1;
	while (T --) Cosmos::main();
	return 0;
}
```


---

## 作者：OIer_ACMer (赞：1)

这道题比较难，但是想一想也不是大问题。


1. **题面解析**：说白了就是在每个**时间刻度**各条边的终点会发生变化，然后让你通过**矩阵**输出最短路。但是，真的就这么简单吗？（~~做好头脑风暴的准备~~）

2. **大致思路**：既然终点会变化，同时要走最短路，那么我们注意这句话：“具体地，在第 $s$ 秒，第 $i$ 条边将指向节点 $(b_i+s)\bmod n$”。这说明我们可以在一个点上站**无限长时间**，来等待边转到自己的目标点。当然这**很费时间**，因此，我们就需要将时间作为**权值**赋值在每一个节点上，然后，在通过最短路，依次查找，进行转移，转移分为两种：一种是直接在当前时刻往已经搭好的路前行（~~急不可待~~）；另外一种是耐心等待。

3. **注意事项**（~~警钟敲烂~~）：一开始的起点不能按照上述思路进行转移，因此在写的时候，我们要**手动进行一次松弛操作**；转移的时候要加上之前已经有的答案（~~不再重复~~）。

4. 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 7;
const int MAXN = 0x3f3f3f3f3f3f;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, m;
int head[N], cnt, vis[N];
int dist[N], d[N];
struct node
{
    int to, val, next;
} edge[N << 1];
void add(int x, int y, int z)
{
    edge[++cnt].to = y;
    edge[cnt].val = z;
    edge[cnt].next = head[x];
    head[x] = cnt;
}
signed main()
{
    n = read();
    m = read();
    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        x = read() + 1;
        y = read() + 1;
        z = read();
        add(x, y, z);
    }
    for (int pos = 1; pos <= n; pos++)
    {
        //每次从pos开始dij
        for (int i = 1; i <= n; i++)
        {
            dist[i] = MAXN, vis[i] = 0;
        }
        vis[pos] = 0;
        for (int i = head[pos]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            int val = edge[i].val;
            dist[v] = min(dist[v], val);
        }//起点预处理
        for (int i = 1; i <= n; i++)
        {
            int x = 0;
            for (int j = 1; j <= n; j++)
            {
                if (!vis[j] && (!x || dist[x] > dist[j]))
                {
                    x = j;
                }
            }
            vis[x] = 1;
            int u = x;
            dist[u % n + 1] = min(dist[u] + 1, dist[u % n + 1]);
            for (int j = head[u]; j; j = edge[j].next)
            {
                int v = (edge[j].to + dist[u] - 1) % n + 1;
                int val = edge[j].val;
                dist[v] = min(dist[v], dist[u] + val);
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (i != pos)
            {
                cout << dist[i] << ' ';
            }
            else
            {
                cout << 0 << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}

```

---

## 作者：Leap_Frog (赞：0)

### P.S.
看到题目就觉得应该是个很有趣的题  

### Description.
略

### Solution.
首先，这题一看就很像最短路，首先考虑 Floyd。  
结果发现 Floyd 并不能较好地解决这题。  
那么我们只能一步一步考虑了。  

首先，困扰我们的显然是就地等待的问题。  
发现假设不等待会到 $x$，那等 1s 就到 $\text{next}(x)$，2s 就到 $\text{next}(\text{next}(x))$。  
我们可以考虑把这个过程拆开，拆成两个过程。  
第一个是跳到 $x$，第二个就是从 $x$ 不断往后跳。  
然后我们成功处理了这个问题。  

其他基本都迎刃而解了。  

需要注意的是，出发点是不能向后跳的，必须要特殊处理。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}/*}}}*/
struct edge{int to,w,nxt;}e[360005];int et,head[605],n,m,d[605];char v[605];
inline void adde(int x,int y,int w) {e[++et]=(edge){y,w,head[x]},head[x]=et;}
inline void dijk(int s)
{//因为边是 n^2 条，dijkstra 还不如不优化
	memset(d,0x3f,sizeof(d)),memset(v,0,sizeof(v));
	for(int i=head[s];i;i=e[i].nxt) d[e[i].to]=e[i].w;
	for(int g=1;g<n;g++)
	{
		int x=0;for(int i=1;i<=n;i++) if(!v[i]&&d[x]>=d[i]) x=i;
		v[x]=1,d[x%n+1]=min(d[x]+1,d[x%n+1]);
		for(int i=head[x],y;i;i=e[i].nxt) y=(e[i].to+d[x]-1)%n+1,d[y]=min(d[x]+e[i].w,d[y]);
	}
	for(int i=1;i<=n;i++) printf("%d%c",s==i?0:d[i],i==n?'\n':' ');
}
int main()
{
	read(n),read(m);
	for(int i=1,x,y,w;i<=m;i++) read(x),read(y),read(w),adde(++x,++y,w);
	for(int i=1;i<=n;i++) dijk(i);
	int _=0;return (0^_^0);// >_<
}
```

---

