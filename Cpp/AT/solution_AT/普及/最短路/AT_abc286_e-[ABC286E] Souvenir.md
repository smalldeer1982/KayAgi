# [ABC286E] Souvenir

## 题目描述

从前有 $n$ 座岛，每个岛上有 $a_i$ 个金币，各个岛间有若干条单向航线相连。

你从某个岛开始旅行，经过一个岛（包括最开始所在的岛）就会拿走上面的金币。

现在问你 $q$ 个问题：从岛 $u_i$ 旅行到岛 $v_i$，最少要走几条航线，以及恰好走这么多条航线最多能获得多少金币。如果根本无法到达 $v_i$，输出 `Impossible`。

询问之间相互独立。

## 样例 #1

### 输入

```
5
30 50 70 20 60
NYYNN
NNYNN
NNNYY
YNNNN
YNNNN
3
1 3
3 1
4 5```

### 输出

```
1 100
2 160
3 180```

## 样例 #2

### 输入

```
2
100 100
NN
NN
1
1 2```

### 输出

```
Impossible```

# 题解

## 作者：liujy_ (赞：4)

 首先题目要求最少航线，那说明可以直接先跑最短路。  
 每组询问会给定起点和终点，在加上 $n$ 的范围很小，所以用 Floyd。在代码中用了 $dd_{i,j}$ 来表示从 $i$ 到 $j$ 的最少航线数量。  
 然后我们来考虑金币数。在设一个数组 $d_{i,j}$ 表示从 $i$ 到 $j$ 走最少航线所能拿到的金币数。然后我们在枚举 $k$ 寻找 $i$ 到 $j$ 的最短路时同时更新最多的金币数。  
 假设找到了一条更短的路线，那直接用这条路线的所获金币数即为答案，假设找到了一条和原先最短路相同长度的路线，再来比较两条路线所能得到的金币数的差值。  
 然后看代码吧！
 ```cpp
#include<iostream> 
#include<cstring>
#include<cstdio>
#include<string>
using namespace std;
const int N=305;
int n,q,s,t,a[N],dd[N][N];char ch[N][N];
long long d[N][N];
int main(){
	cin>>n;memset(dd,0x3f,sizeof(dd));
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>(ch[i]+1);
	for(int i=1;i<=n;i++){
		d[i][i]=a[i];dd[i][i]=0;
		for(int j=1;j<=n;j++)
			if(ch[i][j]=='Y')d[i][j]=a[i]+a[j],dd[i][j]=1;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(dd[i][k]+dd[k][j]<dd[i][j]){
					dd[i][j]=dd[i][k]+dd[k][j];
					d[i][j]=d[i][k]+d[k][j]-a[k];
				}else if(dd[i][k]+dd[k][j]==dd[i][j])
					d[i][j]=max(d[i][k]+d[k][j]-a[k],d[i][j]);
			}
	cin>>q;
	while(q--){
		cin>>s>>t;
		if(dd[s][t]>n)printf("Impossible\n");
		else printf("%d %lld\n",dd[s][t],d[s][t]);
	}
	return 0;
}
```


---

## 作者：Hell0_W0rld (赞：2)

# [E](https://atcoder.jp/contests/abc286/tasks/abc286_e)
*1128。

## 题目大意
给定 $n$ 点 $m$ 边无向图，$u$ 号点有点权 $a_u$，一个人希望 $u\to v$ 的路上经过边数最少，在此前提下点权和最大。$Q$ 个询问，每个询问 $u\to v$ 的路上经过的边数和点权和。
## 解题思路
纯纯的 Floyd 题。

### 第一步：点权转边权

$u$ 到 $v$ 的路上可以取 $a_v$ 作为边权。答案最后记得加上 $a_u$。
### 第二步：解题
发现可以类比为最短路问题。我们需要定义一个结构体包含 $l$ 和 $s$，$l$ 表示航班数，$s$ 表示边权和。小于号定义为 $l$ 小或者 $l$ 相等且 $s$ 更大。然后套模板 Floyd 即可。
## 细节
+ 最后输出时记得判定无解。
+ 记得赋值 $\mathrm{dst}$ 数组为 $\infty$。
+ 输出答案时，第二个应为 `dst[u][v].s+a[u]`，切记要加上起点点权。

## 代码
复杂度 $O(N^3)$，可以承受。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define repD(i,u,E) for(register ll i=hd[u];i;i=E[i].nxt)
#define all(x) x.begin(),x.end()
/*
If there're more than one test case, you must remember to clear the arrays.
If you debug for a long time, you can rewrite the code.
Remember code modularity.
Please keep the code clear, so that you can debug easily.
*/
using namespace std;
void upd_s(ll&x,ll v){x=min(x,v);}
void upd_b(ll&x,ll v){x=max(x,v);}
struct Node{
	ll l,s;
	bool operator<(const Node&b)const{
		if(l!=b.l)return l<b.l;
		return s>b.s;
	}
	Node operator+(const Node&b)const{
		return (Node){l+b.l,s+b.s};
	}
	Node operator+(const ll&b){
		return (Node){l+1,s+b};
	}
};
const ll N=309,IINF=1e18;
Node INF=(Node){IINF,IINF};
Node dst[N][N];
ll a[N],n;
bool to[N][N];
int main(){
	cin>>n;
	rep(i,1,n)cin>>a[i];
	rep(i,1,n)rep(j,1,n){
		if(i==j)dst[i][j]=(Node){0,0};
		else dst[i][j]=INF;
	}
	rep(i,1,n)rep(j,1,n){
		char c;cin>>c;
		if(c=='Y')dst[i][j]=(Node){1,a[j]};
	}
	rep(k,1,n)rep(i,1,n)rep(j,1,n)dst[i][j]=min(dst[i][j],dst[i][k]+dst[k][j]);
	ll q;cin>>q;
	while(q--){
		ll u,v;cin>>u>>v; 
		if(dst[u][v].s==IINF&&dst[u][v].l==IINF)cout<<"Impossible"<<endl;
		else cout<<dst[u][v].l<<" "<<dst[u][v].s+a[u]<<endl;
	}
	return 0;
}


```

---

## 作者：tZEROちゃん (赞：2)

我们先不考虑这个「纪念品」的问题，如果是单纯的最短路，注意到 $N \le 300$，只要跑一遍 floyd，就可以快速求出任意两点 $u,v$ 之间的距离。

请注意，不需要每次询问都跑一遍 floyd，在询问开始之前跑即可。

我们考虑「纪念品」，模仿一下 floyd，我们设 $val_{i, j}$ 表示当前算出最短路上 $i$ 到 $j$ 能获得的最大纪念品价值，然后在 floyd 更新最短路径的时候顺便更新一下 $val$ 就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 310;

#define int long long
int a[N];
int f[N][N];
int value[N][N];

signed main() {
  int n; cin >> n;
  memset(f, 0x3f, sizeof f); 
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) f[i][i] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      char ch; cin >> ch;
      if (ch == 'Y') f[i][j] = 1, value[i][j] = a[j]; 
    }
  }
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (f[i][k] + f[k][j] < f[i][j]) {
          f[i][j] = f[i][k] + f[k][j];
          value[i][j] = value[i][k] + value[k][j];
        }
        else if (f[i][k] + f[k][j] == f[i][j]) {
          value[i][j] = max(value[i][j], value[i][k] + value[k][j]);
        }
      }
    }
  }
  int q; cin >> q;
  while (q--) {
    int u, v; cin >> u >> v;
    if (f[u][v] >= 0x3f3f3f3f) cout << "Impossible\n"; else 
    cout << f[u][v] << ' ' << value[u][v] + a[u] << endl;
  }
}
```


---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc286_e)

突然梦回纪念品的 DP 题（逃

## $\mathtt{Solution}$

这道题比较模板，很显然是一个最短路，本题解使用 SPFA 的做法（用 dijk 我也不拦你）。

跑广搜的过程中如果起点到当前点的最短路小于当前方案的步数，就要更新步数和金币数；如果相等就只更新金币数；否则啥也不干。

猛然发现 $a_i\le 10^9$，**要开 long long！！！**

时间复杂度 $O(qn^2)$

参见代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 3005, MR = 5e5 + 5, INF = 1145141919810;
int n, q, cnt, head[MAXN], a[MAXN], dis[MAXN], num[MAXN];
struct edge{
	int from, to, nxt;
}e[MR];
void add_edge(int u, int v){
	e[++ cnt] = {u, v, head[u]};
	head[u] = cnt;
}
struct step{
	int x, y, z;
};
void SPFA(int s){
	for(int i = 1;i <= n;i ++)dis[i] = INF, num[i] = 0;
	dis[s] = 0, num[s] = a[s];
	queue<step>q;
	q.push({0, a[s], s});
	while(!q.empty()){
		int tx = q.front().x, ty = q.front().y, tz = q.front().z;
		q.pop();
		for(int i = head[tz];i;i = e[i].nxt){
			int v = e[i].to;
			if(tx + 1 < dis[v]){
				dis[v] = tx + 1;
				num[v] = ty + a[v];
				q.push({dis[v], num[v], v});
			}
			else if(tx + 1 == dis[v]){
				if(num[v] < ty + a[v]){
					num[v] = ty + a[v];
					q.push({dis[v], num[v], v});
				}
			}
		}
	}
}
signed main(){
	scanf("%lld", &n);
	for(int i = 1;i <= n;i ++)scanf("%lld", &a[i]);
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= n;j ++){
			char x;cin>>x;
			if(x == 'Y')add_edge(i, j);
		}
	}
	scanf("%lld", &q);
	while(q --){
		int s, t;
		scanf("%lld%lld", &s, &t);
		SPFA(s);
		if(dis[t] == INF)puts("Impossible");
		else printf("%lld %lld\n", dis[t], num[t]);
	}
	return 0;
}

```


~~交上去以后，哇，二十多个时间超限，爽！~~

**本题很坑，要用离线做法，因为 $Q\le n(n-1)\le 44850$，怎么都得炸！**

于是就要用 $O(n^3)$ 的时间预处理，$O(q)$ 的时间询问。

正确代码：

```cpp
#include<bits/stdc++.h>//不要忘记开long long
#define int long long
using namespace std;
const int MAXN = 3005, MR = 5e5 + 5, INF = 1145141919810;//这个数字不过分吧
int n, q, cnt, head[MAXN], a[MAXN], dis[MAXN], num[MAXN];
int ans[MAXN][MAXN], ans2[MAXN][MAXN];//离线存储答案
struct edge{
	int from, to, nxt;
}e[MR];
void add_edge(int u, int v){
	e[++ cnt] = {u, v, head[u]};//偷懒式前向星
	head[u] = cnt;
}
struct step{
	int x, y, z;//x是步数，y是金币数，z是上一个点的编号
};
void SPFA(int s){
	for(int i = 1;i <= n;i ++)dis[i] = INF, num[i] = 0;
	dis[s] = 0, num[s] = a[s];
	queue<step>q;
	q.push({0, a[s], s});
	while(!q.empty()){
		int tx = q.front().x, ty = q.front().y, tz = q.front().z;
		q.pop();
		for(int i = head[tz];i;i = e[i].nxt){
			int v = e[i].to;
			if(tx + 1 < dis[v]){//第一种情况，当前方案步数更少，金币数和步数都要更新
				dis[v] = tx + 1;
				num[v] = ty + a[v];
				q.push({dis[v], num[v], v});
			}
			else if(tx + 1 == dis[v]){//第二种情况，当前方案步数相等，金币数更新
				if(num[v] < ty + a[v]){
					num[v] = ty + a[v];//有更优的方案，更新金币数
					q.push({dis[v], num[v], v});
				}
			}
		}
	}
}
signed main(){
	scanf("%lld", &n);
	for(int i = 1;i <= n;i ++)scanf("%lld", &a[i]);
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= n;j ++){
			char x;cin>>x;
			if(x == 'Y')add_edge(i, j);
		}
	}
	for(int i = 1;i <= n;i ++){
		SPFA(i);
		for(int j = 1;j <= n;j ++){
			ans[i][j] = dis[j];//存储答案
			ans2[i][j] = num[j];
		}
	}
	scanf("%lld", &q);
	while(q --){
		int s, t;
		scanf("%lld%lld", &s, &t);
		if(ans[s][t] == INF)puts("Impossible");//不连通，输出不可能
		else printf("%lld %lld\n", ans[s][t], ans2[s][t]);
	}
	return 0;
}

```


---

## 作者：yemuzhe (赞：1)

### 简化题意

- 有一个 $n$ 个点组成的有向图。给你一个矩阵 $S$，若 $S _ {i, j} = \text Y$ 则从 $i$ 到 $j$ 有一条长度为 $1$ 的有向边，若 $S _ {i, j} = \text N$ 则没有。
- 现在第 $i$ 个点的权值为 $A _ i$。
- 有 $Q$ 次询问，每次询问给定一对整数 $U _ i, V _ i$，问是否能从 $U _ i$ 经过若干条有向边到达 $V _ i$？如果能，输出最少要经过多少条有向边和在经过最少点的基础上经过的点（包括起点、终点）的权值和的最大值；如果不能，输出 `Impossible`。
- $2 \le N \le 300, 1 \le A _ i \le 10 ^ 9, 1 \le Q \le N(N - 1), 1 \le U _ i, V _ i \le N$。
- $S _ {i, j} \in \{\text Y, \text N\}; U _ i \neq V _ i; \forall i \neq j, (U _ i, V _ i) \neq (U _ j, V _ j)$。

### 解题思路

注意到 $N \le 300$，我们可以考虑用 floyd 算法预处理。

设 $dis _ {i, j}$ 为节点 $i$ 到 $j$ 的最短距离。起初，若 $S _ {i, j} = \text Y$，则 $dis _ {i, j} = 1$；否则 $dis _ {i, j} = +\infty$。

然后从 $1$ 到 $N$ 枚举 $k$，再枚举 $i$ 和 $j$。若 $dis _ {i, k} + dis _ {k, j} < dis _ {i, j}$，则令 $dis _ {i, j} = dis _ {i, k} + dis _ {k, j}$（松弛操作）。

设 $c _ {i, j}$ 为从节点 $i$ 到 $j$ 在经过最少点的基础上经过的点的权值和的最大值。刚开始若 $S _ {i, j} = \text Y$，则 $c _ {i, j} = A _ i + A _ j$；否则 $c _ {i, j} = 0$。

然后在 floyd 的过程中，若 $dis _ {i, k} + dis _ {k, j} < dis _ {i, j}$，则 $c _ {i, j} = c _ {i, k} + c _ {k, j} - A _ k$（因为中间点权值 $A _ k$ 被计算了两遍）；否则如果 $dis _ {i, k} + dis _ {k, j} = dis _ {i, j}$，那么 $c _ {i, j} = \max \{c _ {i, j}, c _ {i, k} + c _ {k, j} - A _ k\}$。

最后若 $dis _ {U _ i, V _ i} = +\infty$，那么输出 `Impossible`；否则依次输出 $dis _ {U _ i, V _ i}$ 和 $c _ {U _ i, V _ i}$。

### AC Code

```cpp
#include <cstdio>
#include <cstring>
#define N 305
#define inf 0x3f3f3f3f // 正无穷大
using namespace std;

int n, q, x, y, a[N], dis[N][N];
long long c[N][N];
char s[N];

void floyd ()
{
    for (int k = 1; k <= n; k ++)
    {
        for (int i = 1; i <= n; i ++)
        {
            for (int j = 1; j <= n; j ++)
            {
                if (dis[i][k] + dis[k][j] < dis[i][j])
                {
                    // 更新 dis[i][j] 和 c[i][j]
                    dis[i][j] = dis[i][k] + dis[k][j];
                    c[i][j] = c[i][k] + c[k][j] - a[k];
                }
                else if (dis[i][k] + dis[k][j] == dis[i][j] && c[i][k] + c[k][j] - a[k] > c[i][j])
                {
                    // 更新 c[i][j]
                    c[i][j] = c[i][k] + c[k][j] - a[k];
                }
            }
        }
    }
    return ;
}

int main ()
{
    scanf ("%d", &n), memset (dis, inf, sizeof (dis)); // 初值设为正无穷大
    for (int i = 1; i <= n; i ++)
    {
        scanf ("%d", &a[i]);
    }
    for (int i = 1; i <= n; i ++)
    {
        scanf ("%s", s + 1);
        for (int j = 1; j <= n; j ++)
        {
            if (s[j] == 'Y') // 有一条有向边
            {
                dis[i][j] = 1;
                c[i][j] = a[i] + a[j];
            }
        }
    }
    floyd (), scanf ("%d", &q);
    while (q --)
    {
        scanf ("%d%d", &x, &y);
        if (dis[x][y] < inf)
        {
            printf ("%d %lld\n", dis[x][y], c[x][y]);
        }
        else
        {
            puts ("Impossible");
        }
    }
    return 0;
}
```

---

## 作者：CarroT1212 (赞：0)

### 题目大意

给定一个 $N$ 个点的以邻接矩阵形式给出的有向图，第 $i$ 个点的权值为 $A_i$。给定 $Q$ 次询问，每次询问给定 $S,T$。在从 $S$ 到 $T$ 的所有路径中，你需要找到经过边数最少的一条路径，如果有多条路径长度相等且都为最小值，选择路径上所有点的权值之和最大的一条。若存在路径则输出路径长度和点权之和，否则输出 `Impossible`。

数据范围：$1 \le N \le 300$，$1 \le A_i \le 10^9$，$1 \le Q \le N(N-1)$。

------------

### 解法分析

全源最短路径，但是有两个排序关键字。应该随便魔改一下某种最短路算法即可。

如果想到把点权看成边权的话显然 Floyd 是首选，不过赛时我没想清楚做法所以没写 Floyd，码了个 $N$ 次 Dijkstra。

主要改三点：

+ 改存最短路的数组，设 $dis_{i,j,0}$ 为从 $i$ 到 $j$ 的最短路径长度，$dis_{i,j,1}$ 为从 $i$ 到 $j$ 的最短路径中点权之和的最大值。

+ 优先队列的排序机制设为先按最短路径长度从小到大排序，若相等则按权值之和从大到小排序。就是把 Dijkstra 的贪心思想和双关键字排序对上。

+ 从第 $x$ 个点尝试更新 $y$ 的 $dis$ 值时，若从 $x$ 到 $y$ 的路径长度小于 $dis$ 数组中存储的最小值，则不管点权之和多大，直接根据 $x$ 更新 $y$ 的 $dis$ 值；若两路径长度相等，则看从 $x$ 到 $y$ 的点权之和是否大于 $dis$ 中的最大值，若大于，则更新点权和，否则无法进行任何更新。也是根据双关键字排序修改更新机制。

最后注意 $A_i \le 10^9$，记得开 long long，赛时痛吃一发罚时。

------------

### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int N=307;
struct node {
	int p,v1;
	ll v2;
	bool operator < (const node &x) const { return x.v1==v1?x.v2>v2:x.v1<v1; }
};
int n,q,vis[N][N];
ll dis[N][N][2],a[N];
char str[N][N];
vector <int> v[N];
void dij(int s) {
	priority_queue <node> q;
	for (int i=1;i<=n;i++) dis[s][i][0]=1e18;
	dis[s][s][0]=0,dis[s][s][1]=a[s],q.push({s,0,a[s]});
	while (q.size()) {
		int x=q.top().p,y=q.top().v1;
		ll z=q.top().v2;
		if (vis[s][x]) continue;
		q.pop(),vis[s][x]=1;
		for (int i:v[x]) {
			if (dis[s][i][0]>y+1)
				dis[s][i][0]=y+1,dis[s][i][1]=z+a[i],q.push({i,y+1,z+a[i]});
			else if (dis[s][i][0]==y+1&&dis[s][i][1]<z+a[i])
				dis[s][i][1]=z+a[i],q.push({i,y+1,z+a[i]});
		}
	}
}
int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for (int i=1;i<=n;i++) scanf("%s",str[i]+1);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++)
		if (str[i][j]=='Y') v[i].pb(j);
	for (int i=1;i<=n;i++) dij(i);
	scanf("%d",&q);
	for (int x,y;q--;) {
		scanf("%d%d",&x,&y);
		if (dis[x][y][0]!=1e18) printf("%lld %lld\n",dis[x][y][0],dis[x][y][1]);
		else printf("Impossible\n");
	}
	return 0;
}
```

---

## 作者：12345678hzx (赞：0)

## 题目大意
有一个 $N\times N$ 的邻接矩阵，每个点有一个权值，$Q$ 次询问，每次询问有两个数 $x$ 和 $y$，要你求出在 $x$ 到 $y$ 的所有最短路径中点权和最大是多少。
## 思路
由于本题 $n\le 300$，所以考虑使用时间复杂度为 $O(n^3)$ 的 Floyd 算法，先求出最短路，再求出最大点权和，但是 Floyd 适合求解边权最最值，所以考虑将点权转成边权，然后用 Floyd 算法求出最值就好了。

关于 Floyd 算法，作者这里有一种优化 Floyd 算法的方法，具体可以看我的[这篇博客](https://www.luogu.com.cn/blog/hzx12345678/guan-yu-floyd-di-you-hua)。
## 代码
考虑到一些读者可能不理解优化后的 Floyd 算法，所以在这里放不加优化的代码。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

long long n,m,a[305],f[305][305],sum[305][305];
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) {
		char c;
		cin>>c;
		if(c=='Y') f[i][j]=1,sum[i][j]=a[i]+a[j];
		else f[i][j]=1e18;
	}
	for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	for(int i=1;i<=n;i++) sum[i][i]=a[i];
	for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(f[i][k]+f[k][j]==f[i][j]) sum[i][j]=max(sum[i][j],sum[i][k]+sum[k][j]-a[k]);//这里由于中转点会计入答案两次，所以要减去一次。
	cin>>m;
	while(m--) {
		int x,y;
		cin>>x>>y;
		if(f[x][y]==1e18) cout<<"Impossible\n";
		else cout<<f[x][y]<<" "<<sum[x][y]<<"\n";
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# ABC286E 题解



## 思路分析

对每条路径按长度为第一关键字，权值和为第二关键字升序排序，Floyd 全源最短路维护即可。

注意到对于所有 $u\to v$ 的边，我们可以把点权 $a_u,a_v$ 变成边权 $a_v$，这样求出 $x\to y$ 最短的最大权路径后，把权值加上 $a_x$ 即可。

时间复杂度 $\Theta(n^3)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=301,INF=1e18;
struct node {
	int dist,val;
	node() { dist=val=0; }
	node(int _dist,int _val) { dist=_dist,val=_val; }
	inline friend bool operator <(const node &A,const node &B) {
		if(A.dist==B.dist) return A.val>B.val;
		return A.dist<B.dist;
	}
	inline friend node operator +(const node &A,const node &B) {
		return node(A.dist+B.dist,A.val+B.val);
	}
}	f[MAXN][MAXN];
inline node better(const node &A,const node &B) {
	return A<B?A:B;
}
int a[MAXN];
char ch[MAXN][MAXN];
signed main() {
	int n;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(int i=1;i<=n;++i) {
		scanf("%s",ch[i]+1);
		for(int j=1;j<=n;++j) {
			if(i==j) f[i][j]=node(0,0);
			else if(ch[i][j]=='Y') f[i][j]=node(1,a[j]);
			else f[i][j]=node(INF,0);
		}
	}
	for(int k=1;k<=n;++k) {
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=n;++j) {
				f[i][j]=better(f[i][j],f[i][k]+f[k][j]);
			}
		}
	}
	int q;
	scanf("%lld",&q);
	while(q--) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		if(f[u][v].dist==INF) puts("Impossible");
		else printf("%lld %lld\n",f[u][v].dist,a[u]+f[u][v].val);
	}
	return 0;
}
```

---

## 作者：weizhiyonghu (赞：0)

# AT #286 E
## Explanation:
为叙述方便，规定以下内容：

$(1)$ 直连边指仅有一条边的路径。源点为 $u$，终点为 $v$ 的直连边用 $(u,v)$ 表示。该边边权用 $w(u,v)$ 表示。

$(2)$ 若有路径 $p$ 表示 $u \to \cdots \to  v$，则规定此路径的权值 $w(u,v) = \sum_{(u_i,v_i) \in p} w(u_i,v_i)$。

$(3)$ 对于一个点 $u$，$next(u)$ 表示在当前讨论的路径中点 $u$ 的后继点。$pre(u)$ 表示其前驱。

## Description:
给出一张 $n(1 \le n \le 300)$ 个点的有向连通图，再给出一个 $n \times n$ 的字符矩阵 $S$ 表示连边关系。若 $S_{i,j} = \texttt{'Y'}$ 则表示从 $i$ 到 $j$ 有直连边，否则有 $S_{i,j} = \texttt{'N'}$。每条直连边的长度相等，每个点有一个点权 $A_i$。现有 $q(1\le q \le n(n-1))$ 组询问，每组询问给出源点 $u_i$ 和终点 $v_i$，求 $u_i,v_i$ 之间以路径作为第一关键字，以路径上点权和为第二关键字，第一关键字最小，第二关键字最大的路径。
## Solution:
显而易见，本题是一道多源双关键字最长/短路题目。第一关键字直接就是边权，无需考虑太多。但是第二关键字是点权，故需要考虑建边方式。

对于每一条直连边 $u \to v$，我们考虑以下建边方式：
$w(u,v) = A_u + A_v$：此时，对于一条源点为 $s$，终点为 $t$ 的复杂路径 $p$，会发现其总权值为 $\sum_{(u,v) \in p} A_u + A_v$，即 $A_s + 2 \times A_{next(s)}\cdots + A_t$，即每个中间点都算了两次。此时，主要问题是中间的边权算了两次，则在比较的时候，源点和终点的值对于最终答案的贡献会被影响，最优性质不被保证。

考虑以下建边方式：对于 $u \to v$，使 $w(u,v) = A_u$，则可以得到对于上面的路径 $p$，有总权值为 $A_s + A_{next(s)} + \cdots + A_{pre(t)}$。此时仅少了最后一个点的点权 $A_t$。那么在比较的时候，所有需要比较的路径都仅仅少了一个相同的点权 $A_t$，前面的大小不被影响。那么可以直接进行比较，最优性质得到了保证。此时可以使用Floyd解决，时间复杂度 $O(n^3 + q)$，空间复杂度 $O(n^2)$，可以通过本题。
## Code:
```cpp
/*
author : CTR_WU
time : 2023-01-21 21:24:18
*/
#include <bits/stdc++.h>
#define int long long
#define check1 dist1[i][j]==dist1[i][k]+dist1[k][j]
#define check2 dist2[i][j]<dist2[i][k]+dist2[k][j]

using namespace std;
const int N = 330;
int n,a[N],q,l,r;
bool g[N][N];
int dist1[N][N],dist2[N][N];

inline void floyd()
{
    memset(dist1,0x3f,sizeof(dist1));
    memset(dist2,-0x3f,sizeof(dist2));
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            if(g[i][j]) dist1[i][j] = 1;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            if(g[i][j]) dist2[i][j] = a[i];
    for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                if(dist1[i][j] > dist1[i][k] + dist1[k][j])
                    dist1[i][j] = dist1[i][k] + dist1[k][j],
                    dist2[i][j] = dist2[i][k] + dist2[k][j];
                else if(check1&&check2)
                    dist2[i][j] = dist2[i][k] + dist2[k][j];
    return ;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i = 1;i <= n;i++)
        cin >> a[i];
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
        {
            char s;cin >> s;
            if(s == 'N') g[i][j] = false;
            else g[i][j] = true;
        }
    floyd();
    cin >> q;
    while(q--)
    {
        cin >> l >> r;
        if(dist1[l][r] == 0x3f3f3f3f3f3f3f3f)
        {cout << "Impossible\n";continue;}
        cout << dist1[l][r] << " ";
        cout << dist2[l][r] + a[r] << "\n";
    }
    return 0;
}
```

---

## 作者：FReQuenter (赞：0)

## 思路

我们考虑预处理任意两个点之间的答案。由于首要判断两点距离，所以考虑 BFS。队列中记录一个三元组，包括当前位置，走过的边数和纪念品数。搜索过程中顺便记录下是否可达就可以回答所有询问了。

## 代码

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define int long long
using namespace std;
string ga[305];
int n,q,a[305],f[305][305];
int vis[305][305];
vector<int> gv[305];
struct que{
  int now,step,sum;
};
signed main(){
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i];
  for(int i=1;i<=n;i++){
    cin>>ga[i],ga[i]='#'+ga[i];
    for(int j=1;j<=n;j++){
      if(i!=j){
        if(ga[i][j]=='Y'){
          gv[i].push_back(j);
        }
      }
    }
  }
  for(int i=1;i<=n;i++){
    memset(vis[i],0x3f,sizeof(vis[i]));
    memset(f[i],-0x3f,sizeof(f[i]));
    queue<que> q;
    q.push((que){i,0,a[i]});
    while(!q.empty()){
      que fr=q.front();
      q.pop();
      if(vis[i][fr.now]<fr.step) continue;
      vis[i][fr.now]=fr.step;
      if(f[i][fr.now]>fr.sum&&vis[i][fr.now]==fr.step) continue;
      f[i][fr.now]=fr.sum;
      int now=fr.now;
      for(int i=0;i<gv[now].size();i++){
        q.push((que){gv[now][i],fr.step+1,fr.sum+a[gv[now][i]]});
      }
   }
  }
  cin>>q;
  while(q--){
    int x,y;
    cin>>x>>y;
    if(f[x][y]<0) cout<<"Impossible\n";
    else cout<<vis[x][y]<<' '<<f[x][y]<<'\n';
  }
}
```

---

## 作者：lfxxx (赞：0)

首先观察到 $n \leq 300$ 加上全源“最短路”便可以自然而然的想到 `floyd`。

注意到 `floyd` 算法的可行性**只依赖统计的东西具有优先级**。

这里我们定义优先级为最短路最短且价值和最高。也就是在最短路相同的情况下比较价值和。

然后跑一遍 `floyd` 板子即可，复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 1e18
using namespace std;
const int maxn =301;
pair<int,int> dp[maxn][maxn];
int a[maxn];
int n;
signed main(){
cin>>n;
for(int i=1;i<=n;i++) cin>>a[i];
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
        char c;
        cin>>c;
        dp[i][j]=make_pair(c=='Y'?1:inf,c=='Y'?a[i]+a[j]:0);
        if(i==j) dp[i][j]=make_pair(0,a[i]);
    }
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i!=j&&i!=k&&j!=k)
            {
                pair<int,int> New=make_pair(dp[i][k].first+dp[k][j].first,dp[i][k].second+dp[k][j].second-a[k]);
                if(New.first<dp[i][j].first||(New.first==dp[i][j].first&&New.second>dp[i][j].second))
                    dp[i][j]=New;
            }

int t;
cin>>t;
while(t--)
{
    int u,v;
    cin>>u>>v;
    if(dp[u][v].first!=inf) cout<<dp[u][v].first<<' '<<dp[u][v].second<<'\n';
    else cout<<"Impossible\n";
}
}
```


---

