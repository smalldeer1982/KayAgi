# [ABC340D] Super Takahashi Bros.

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc340/tasks/abc340_d

高橋君はゲームをプレイしています。

ゲームは $ 1,2,\ldots,N $ の番号がついた $ N $ 個のステージからなり、現在はステージ $ 1 $ のみを遊ぶことができます。

各ステージ $ i $ ( $ 1\leq\ i\ \leq\ N-1 $ )が遊べるとき、ステージ $ i $ では以下の $ 2 $ つのどちらかの行動を行えます。

- $ A_i $ 秒掛けてステージ $ i $ をクリアする。ステージ $ i+1 $ を遊べるようになる。
- $ B_i $ 秒掛けてステージ $ i $ をクリアする。ステージ $ X_i $ を遊べるようになる。
 
各ステージをクリアするためにかかる時間以外は無視できるとき、ステージ $ N $ を遊べるようになるのは最短で何秒後ですか？

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ 10^9 $
- $ 1\ \leq\ X_i\ \leq\ N $
- 入力は全て整数
 
### Sample Explanation 1

次のように行動することで、$ 350 $ 秒でステージ $ 5 $ を遊べるようになります。 - $ 100 $ 秒掛けてステージ $ 1 $ をクリアし、ステージ $ 2 $ を遊べるようになる。 - $ 50 $ 秒掛けてステージ $ 2 $ をクリアし、ステージ $ 3 $ を遊べるようになる。 - $ 200 $ 秒掛けてステージ $ 3 $ をクリアし、ステージ $ 5 $ を遊べるようになる。

## 样例 #1

### 输入

```
5
100 200 3
50 10 1
100 200 5
150 1 2```

### 输出

```
350```

## 样例 #2

### 输入

```
10
1000 10 9
1000 10 10
1000 10 2
1000 10 3
1000 10 4
1000 10 5
1000 10 6
1000 10 7
1000 10 8```

### 输出

```
90```

## 样例 #3

### 输入

```
6
1000000000 1000000000 1
1000000000 1000000000 1
1000000000 1000000000 1
1000000000 1000000000 1
1000000000 1000000000 1```

### 输出

```
5000000000```

# 题解

## 作者：xiaoshumiao (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc340_d)

纪念第一次 ABC。

看了题目，相信大家肯定会想到 dp。

设 $dp_i$ 为能在 $i$ 号台上表演的最少时间，$k$ 为所有 $x_j=i$ 的 $j$，则

$$dp_i=\min(dp_{i-1}+a_{i-1},dp_k+b_k)$$

可是如果直接 dp，会有状态转移顺序的问题。

而且由于 $x_i$ 的关系可能成环，也没有明确的拓扑序。

所以我们考虑把它转换成最短路的形式。我们每读入 $a_i,b_i,x_i$ 就向 $i$ 到 $i+1$ 连一条边权为 $a_i$ 的边，向 $i$ 到 $x_i$ 连一条边权为 $b_i$ 的边，答案就是 $1$ 到 $N$ 的最短路。

[code](https://atcoder.jp/contests/abc340/submissions/50173173)

---

## 作者：Genius_Star (赞：3)

### 思路：

因为没有保证 $x_i>i$ 故可能有环，需要建图。

对于 $i$ 点，建一条 $i \to i+1$ 且边权为 $a_i$ 的边和一条 $i \to x_i$ 且边权为 $b_i$ 的点。

我们需要知道从 $1$ 号点到达 $n$ 号点的最短路，考虑堆优化 dijkstra。

时间复杂度为 $O((n+m) \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200,INF=1e17;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll y,x;
	bool operator<(const Node&rhs)const{
		return rhs.y<y;
	}
};
ll n;
ll a[N],b[N],dis[N];
bool f[N];
vector<pair<ll,ll>> E[N];
priority_queue<Node> q;
void add(ll u,ll v,ll w){
	E[u].push_back({v,w});
}
void dijkstra(ll s){
    dis[s]=0;
    q.push({0,s});
    while(!q.empty()){
        Node t=q.top();
        q.pop();
        ll x=t.x;
        if(f[x])
          continue;
        f[x]=1;
        for(auto i:E[x]){
        	ll y=i.first;
            if(dis[y]>dis[x]+i.second){
                dis[y]=dis[x]+i.second;
                if(!f[y])
                  q.push({dis[y],y});
            }
        }
    }
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		a[i]=read(),b[i]=read();
		add(i,i+1,a[i]);
		add(i,read(),b[i]);
	}
	for(int i=1;i<=n;i++)
	  dis[i]=INF;
	dijkstra(1);
	write(dis[n]);
	return 0;
}

```


---

## 作者：Hughpig (赞：2)

考虑把每个关卡看作节点，通关时间看作边权，就可以建图了。问题转化为从节点 $1$ 到节点 $n$ 的最短路径。

这个问题用 $\text{dijkstra}$ 算法解决。时间复杂度 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

ll n,dis[200007];
bool vis[200007];
vector<ll> G[200007],val[200007];

struct node{
	ll dis,p;
	friend bool operator <(node a,node b){
		return a.dis>b.dis;
	}
};

priority_queue<node> pq;

void dijkstra(int s){
	dis[s]=0;
	pq.push((node){0,s});
	while(pq.size()){
		node tmp=pq.top();
		pq.pop();
		int u=tmp.p;
		if(vis[u])continue;
		vis[u]=1;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i],w=val[u][i];
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!vis[v]){
					pq.push((node){dis[v],v});
				}
			}
		}
	}
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)dis[i]=1e18;
	for(ll i=1,a,b,x;i<n;i++){
		cin>>a>>b>>x;
		G[i].pb(i+1);
		val[i].pb(a);
		G[i].pb(x);
		val[i].pb(b);
	}
	dijkstra(1);
	cout<<dis[n];
}
```

---

## 作者：spire001 (赞：2)

## 思路
考虑搜索即可，使用 `bfs` 配合优先队列搜索解决这道题，记得每次搜索时对堆顶标记免得重复状态太多，详情见代码。
## CODE
```cpp
# include <climits>
# include <iostream>
# include <cstring>
# include <algorithm>
# include <cstdlib>
# include <stack>
# include <queue>
# include <vector>
# include <bitset>
# include <iomanip>
# include <cctype>
# define dbg(x) cerr << #x" = " << x << '\n'
using namespace std;

void rc(char &__c)
{
	while(!isalpha((__c = getchar())));
	return;
}
template <typename T>
void Read_base(T & num)
{
	char ch;int f = 1;num = 0;
	for(ch = getchar(); ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -f;
	for(;ch <= '9' && ch >= '0'; ch = getchar()) num = (num << 1) + (num << 3) + (ch ^ 48);
	num *= f; return;
}
void Read() {}
void Write() {}
template <typename T , typename ... args>
void Read(T & num , args &...  _num)
{
	Read_base(num);
	Read(_num...);
	return;
}
template <typename T>
void Write_base(const T num)
{
	if(num > 9) Write_base(num / 10);
	putchar(num % 10 ^ 48);
	return;
}
template <char __c = ' ' , typename T , typename ... args>
void Write(const T num , const args ...  _num)
{
	if(num < 0) {putchar('-');Write_base(-num);}
	else Write_base(num);
	putchar(__c);Write(_num...);
	return;
}
int n;
struct node1{
	int a , b , x;
}c[200002];
struct node{
	int place ;
	long long t;
	bool operator < (const node &Q) const
	{
		return t > Q.t;
	}//记得自己写一个比较函数
};
priority_queue <node> q;//STL优先队列
bool box[200002];//标记数组
int main()
{
	Read(n);
	for(int i = 1; i < n; i++) Read(c[i].a , c[i].b , c[i].x);//不定项读入函数比较方便
	node beg = {1 , 0};//初始状态
	q.push(beg);long long ans = LONG_LONG_MAX;
	box[1] = true;//标记
	while(!q.empty())
	{
		node nows = q.top();
		q.pop();//堆顶
		box[nows.place] = true;//标记
		if(nows.place == n)
		{
			ans = nows.t;
			break;//满足条件了
		}
		if(!box[c[nows.place].x])
		{
			//box[c[nows.place].x] = true;
			q.push({c[nows.place].x , nows.t + c[nows.place].b});
		}
		if(!box[nows.place + 1])
		{
			//box[nows.place + 1] = true;
			q.push({nows.place + 1 , nows.t + c[nows.place].a});//按题目要求继续搜索
		}
	}
	Write(ans);
	return 0;
}

---

## 作者：Pink_Cut_Tree (赞：1)

# AT_abc340_c [ABC340C] Divide and Divide 题解

### 解析

自然而然的想到了最短路。

对于一个 $1\leq i<n$，在 $i$ 和 $i+1$ 间连一条长为 $a_i$ 的边，在 $i$ 和 $x_i$ 之间连一条长为 $b_i$ 的边，跑最短路即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
#define inf 2010080820100808
#define ll long long
int n;
struct stage{
	int x,a,b;
}stg[N];
#define pii pair<ll,ll>
priority_queue<pii,vector<pii>,greater<pii> >Q; //维护一个小根堆
ll ans[N];
bool vis[N];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>stg[i].a>>stg[i].b>>stg[i].x;
	}
	Q.push({ans[1],1ll});
	for(int i=2;i<=n;i++){
		ans[i]=inf;
	}
	while(!Q.empty()){
		ll u=Q.top().second;
		Q.pop();
//		cout<<u<<" "<<ans[u]<<" "<<vis[u]<<"\n";
		if(u==n){ //如果到答案了直接输出
			cout<<ans[u]; return 0;
		}
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		if(ans[u+1]>ans[u]+stg[u].a){
			ans[u+1]=ans[u]+stg[u].a;
			Q.push({ans[u+1],u+1});
//			cout<<u+1<<"\n";
		}
		if(ans[stg[u].x]>ans[u]+stg[u].b){
			ans[stg[u].x]=ans[u]+stg[u].b;
			Q.push({ans[stg[u].x],stg[u].x});
//			cout<<stg[u].x<<"\n";
		}
	}
return 0;
}
```


---

## 作者：Otue (赞：1)

我们可以抽象成最短路问题。

对于第 $i$ 个频道，可以花费 $A_i$ 到第 $i+1$ 个频道，等价于第 $i$ 个点向第 $i+1$ 个点连一条权值为 $A_i$ 的边。

同时，可以花费 $B_i$ 到第 $X_i$ 个频道，等价于第 $i$ 个点向第 $X_i$ 个点连一条权值为 $B_i$ 的边。

答案就是 $1\sim n$ 的最短路。

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>
const int N = 2e5 + 5;
int n, dist[N], st[N];
vector<PII> G[N];

void dijstra(int s) {
	priority_queue<PII, vector<PII>, greater<PII> > q;
	fill(dist + 1, dist + n + 1, 2e18);
	dist[s] = 0; q.push({0, 1});
	while (q.size()) {
		auto t = q.top();
		q.pop();
		int u = t.second;
		if (st[u]) continue;
		st[u] = 1;
		for (auto e : G[u]) {
			auto v = e.first, d = e.second;
			if (dist[v] > dist[u] + d) {
				dist[v] = dist[u] + d;
				q.push({dist[v], v});
			}
		}
	}
}

signed main() {
	cin >> n;
	for (int i = 1; i <= n - 1; i++) {
		int a, b, x;
		cin >> a >> b >> x;
		G[i].push_back({i + 1, a});
		G[i].push_back({x, b}); 
	}
	dijstra(1);
	if (dist[n] == 2e9) puts("-1");
	else cout << dist[n] << endl;
}
```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc340_d)

## 思路

可以把这道题想象成一个有向图。第 $i$ 个点指向 $i+1$ 与 $X_i$，边权分别为 $A_i,B_i\space (1\le i<N)$。

于是思路就很快出来：计算从 $1$ 号点到 $N$ 号点的最短路长度。我们选择用 spfa 算法进行最短路长度计算。

- 最短路长度最长可能为 $2\times 10^5\times 10^9=2\times 10^{14}$，记得**开 long long。**

## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define pli pair<ll,int>
#define fi first
#define se second
using namespace std;
inline ll read(){
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
const int N=2e5+10;
int n;
ll dis[N];
bool vis[N];
vector<pli>g[N];
priority_queue<pli,vector<pli>,greater<pli>>q;//堆优化。
void spfa(){
	memset(dis,0x7f,sizeof dis);
	dis[1]=0;
	q.push({0,1});
	while(q.size()){
		auto k=q.top().se;
		q.pop();
		vis[k]=1;
		for(auto i:g[k]){
			if(dis[i.se]>dis[k]+i.fi){
				dis[i.se]=dis[k]+i.fi;
				if(!vis[i.se])q.push({dis[i.se],i.se});
			}
		}
	}
	return ;
}
int main(){
	cin>>n;
	for(int i=1;i<n;++i){
		ll a=read(),b=read();
		int x=read();
		g[i].pb({a,i+1});//建图。
		g[i].pb({b,x});
	}
	spfa();
	cout<<dis[n];
	return 0;
}
```

[已 AC](https://www.luogu.com.cn/record/146664837)

---

## 作者：SJZ2010 (赞：1)

### 题意

对于 $1 \le i \le N - 1$，我们可以用 $A_i$ 的代价到达 $i+1$，$B_i$ 的代价到达 $X_i$。求到达 $N$ 的最小代价。

### 做法

根据题意，不难想到建图跑最短路。我们从 $i$ 向点 $i+1$ 和 $X_i$ 分别连边权为 $A$ 和 $B$ 的边。在 $1$ 号节点跑一遍 Dijkstra，最后可以求出 $1$ 到 $N$ 的距离。

注意要开 `long long`。

代码：

```cpp
#include <bits/stdc++.h>

using ll = long long;
using qi = std::queue < int >;
using vi = std::vector < int >;
#define pq std::priority_queue
#define ve std::vector < edge >
#define VE std::vector < EDGE >
#define me(a, b) std::memset(a, b, sizeof(a))

const int N = 2e5 + 5; // This need you to adjust
const double TLS = 1;
const double eps = 1e-9;
const int inf = 0x3f3f3f3f;
const int CPS = CLOCKS_PER_SEC;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const double TLC = TLS * 0.97 * CPS;

struct edge
{
	int v;
	ll w;
	inline bool operator < (const edge& x) const {
		return w > x.w;
	}
};

int n;
ll dis[N]; // 三年 OI 一场梦，不开 long long 见祖宗
bool vis[N];
ve G[N];

void Dijkstra() // 单源最短路
{
	pq < edge > Q;
	me(dis, 0x3f);
	dis[1] = 0;
	Q.push({1, 0});
	int u;
	while (!Q.empty())
	{
		u = Q.top().v;
		Q.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		for (edge e : G[u])
			if (dis[u] + e.w < dis[e.v])
			{
				dis[e.v] = dis[u] + e.w;
				Q.push({e.v, dis[e.v]});
			}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, a, b, x; i < n; i++)
	{
		scanf("%d %d %d", &a, &b, &x);
		G[i].push_back({i + 1, a}); // 建图
		G[i].push_back({x, b});
	}
	Dijkstra(); // 跑最短路
	printf("%lld\n", dis[n]);
	return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

## Problem
高桥正在玩一个游戏。

游戏由编号为 $1,2,3\dots,n$ 的 $n$ 个阶段组成。最初，只有阶段 $1$ 可以玩。

对于每个阶段 $i$，可执行两种操作之一：

- 花费 $A_i$ 秒清除阶段 $i$。这样就可以进入 $i+1$ 阶段。
- 花费 $B_i$ 秒清除阶段 $i$。这样就可以进入 $X_i$ 阶段。

至少需要多少秒才能通关 $n$？

## Solve
对于每个阶段的操作，都有两种转移状态：

- 花费 $A_i$ 秒清除阶段 $i$。这样就可以进入 $i+1$ 阶段。
- 花费 $B_i$ 秒清除阶段 $i$。这样就可以进入 $X_i$ 阶段。

显然，阶段与阶段之间构成图论关系。因此建图。

考虑到求最小时间。所以建图后跑最短路即可。

时间复杂度 $O(n\log n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 2e5 + 10;

struct Node {
  int v, w, nx;
  bool operator < (const Node &x) const {
    return x.w < w;
  }
} e[N << 1];

int n, h[N], tot, dis[N];

bool vis[N];

void add(int u, int v, int w) {
  e[++tot] = (Node){v, w, h[u]};
  h[u] = tot;
}

void dijkstra() {
  memset(dis, 0x3f, sizeof dis);
  dis[1] = 0;
  priority_queue<Node> q; 
  q.push((Node){1, 0});
  while(!q.empty()) {
    int x = q.top().v;
    q.pop();
    if(vis[x]) continue;
    for (int i = h[x]; i; i = e[i].nx) {
      int y = e[i].v, w = e[i].w;
      if(dis[y] > dis[x] + w) {
        dis[y] = dis[x] + w;
        q.push((Node){y, dis[y]});
      }
    }
  }
}

signed main() {
  read(n);
  For(i,1,n-1) {
    int a, b, x;
    read(a, b, x);
    add(i, i + 1, a);
    add(i, x, b);
  }
  dijkstra();
  cout << dis[n] << '\n'; 
  return 0;
}
```

---

## 作者：aCssen (赞：0)

### Solution

如果把题目中的关卡变为点,那么相当于有两种边:

+ 连接点 $i$ 与点 $i+1$ 的边,边权为 $A_i$。

+ 连结点 $i$ 与点 $X_i$ 的边,边权为 $B_i$。

那么问题就转化为了求点 $1$ 到点 $n$ 的最短路,使用 dijkstra 即可。

记得开 `long long`。

### Code
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
const int maxm=4e5+5;
int head[maxn],ver[maxm],edge[maxm],nxt[maxm],tot,n;
ll dis[maxn];
priority_queue<pair<ll,int> >q;
bool vis[maxn];
void add_edge(int u,int v,int w){
	ver[++tot]=v;
	edge[tot]=w;
	nxt[tot]=head[u];
	head[u]=tot;
}
void dijkstra(int s){
	memset(dis,0x3f,sizeof(dis));
	q.push(make_pair(0,s));
	dis[s]=0;
	while(!q.empty()){
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i],z=edge[i];
			if(dis[x]+z<dis[y]){
				dis[y]=dis[x]+z;
				q.push(make_pair(-dis[y],y));
			}
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int a,b,x;
		scanf("%d%d%d",&a,&b,&x);
		add_edge(i,i+1,a);
		add_edge(i,x,b);
	}
	dijkstra(1);
	printf("%lld",dis[n]);
	return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

题目给出的关系显然有两种，一种是循规蹈矩直接花费 $a_{i}$ 的代价从 $ i $ 走到 $ i+1 $，一种是花费 $b_{i}$ 的代价从 $ i $ 跳到 $x_{i}$ 。

也就是说对于一个点有两种转移方式。

把这 $n$ 个点和他们转移方式看做一张有向图，按照上述转移方式对点 $i$ 和 $i+1$ 连一条权值为 $a_{i}$ 的边，再链接一条到 $b_{i}$ 权值为 $x_{i}$ 的边。

在这个有向图里进行最短路算法，可以发现到第 $i$ 的点的最短距离就是高桥最小花费，故到第 $n$ 点的最短路即为所求。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct Point{
	int v;
	long long val;
};
struct cmp{
	bool operator()(Point x,Point y){
		return x.val>y.val;
	}
};
vector <Point> e[N];
priority_queue<Point,vector<Point>,cmp> q;
int n;
long long u,v,w,dis[N];
bool vis[N];
void add(int u,int v,int w){
	e[u].push_back((Point){v,w});
}
void dij(){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[1]=0;
	q.push((Point){1,0});
	while(!q.empty()){
		Point head=q.top();
		q.pop();
		if(vis[head.v])continue;
		vis[head.v]=1;
		for(int i = 0;i < e[head.v].size();i++){
			int v=e[head.v][i].v;
			if(dis[v]>dis[head.v]+e[head.v][i].val){
				dis[v]=dis[head.v]+e[head.v][i].val;
				q.push((Point){v,dis[v]});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i=  1;i < n;i++){
		cin >> u >> w >> v;
		add(i,i+1,u);
		add(i,v,w);
	}
	dij();
	cout << dis[n];
	return 0;
}
```


---

## 作者：Elysian_Realme (赞：0)

# AtCoder_abc340 D

## 题意简述

有 $N$ 个节点，每次你可以从 $i$ 节点花 $A_i$ 的代价走到 $i+1$ 节点，或花费 $B_i$ 的代价走到 $X_i$ 节点，问走到节点 $N$ 的最小代价。

## 解题思路

很明显的最短路模板了。

我们可以直接把 $i$ 和 $i+1$ 连一条长度为 $A_i$ 的边，$i$ 和 $X_i$ 之间连一条长度为 $B_i$ 的边，然后跑一遍 dijkstra 模板，如果懒得建图也可以稍微改变一下松弛的过程。

小细节，输入是从 $1\sim N-1$。~~估计也只有我会犯这种低级错误。~~

最后还有一点：**十年 OI 一场空，不开 long long 见祖宗。**

时间复杂度 $O(N\log N)$。

## Code

```cpp
// Problem: D - Super Takahashi Bros.
// Contest: AtCoder - KAJIMA CORPORATION CONTEST 2024（AtCoder Beginner Contest 340）
// URL: https://atcoder.jp/contests/abc340/tasks/abc340_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int id,dis;
	bool operator < (node a)const{
		return dis>a.dis;
	}
};
int n,a[200005],b[200005],x[200005];
int dis[200005];bool vis[200005];
void dij(){
	priority_queue<node>que;
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	que.push((node){1,0});
	while(!que.empty()){
		int u=que.top().id;
		que.pop();
		if(vis[u])continue;
		vis[u]=1;
		if(dis[u+1]>dis[u]+a[u]){
			dis[u+1]=dis[u]+a[u];
			que.push((node){u+1,dis[u+1]});
		}if(dis[x[u]]>dis[u]+b[u]){
			dis[x[u]]=dis[u]+b[u];
			que.push((node){x[u],dis[x[u]]});
		}
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++)
		cin>>a[i]>>b[i]>>x[i];
	dij();
	cout<<dis[n];
	return 0;
}
```



---

## 作者：Link_Cut_Y (赞：0)

考虑建立图论模型。

$\forall i < n$，连接边 $i \rightarrow i + 1$，边权为 $a_i$，表示表演完 $i$ 之后，花费 $a_i$ 的代价才能表演第 $i + 1$ 出戏；连接边 $i \rightarrow x_i$，边权为 $b_i$，表示表演完 $i$ 之后，需要花费 $b_i$ 的时间才能表演第 $x_i$ 场。

所求即为 $1$ 号点到 $n$ 号点的最短路。由于每个点的出度最多为 $2$，边数严格小于 $2n$，使用 `dijkstra` 算法求解即可。时间复杂度 $O(n \log n)$。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define int long long

using namespace std;

typedef pair<int, int> PII;
const int INF = 1e16;
const int N = 200010;
const int M = N << 1;
int n, a[N], b[N], x[N], d[N];
int h[N], e[M], ne[M], w[M], idx;
bool vis[N];
void add(int a, int b, int c) {
	e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx, w[idx] = c;
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i < n; i ++ )
		scanf("%lld%lld%lld", &a[i], &b[i], &x[i]);
	for (int i = 1; i < n; i ++ )
		add(i, i + 1, a[i]),
		add(i, x[i], b[i]);
	priority_queue<PII, vector<PII>, greater<PII>> q;
	fill(d, d + n + 1, INF); d[1] = 0; q.push({0, 1});
	while (q.size()) {
		int u = q.top().second; q.pop();
		if (vis[u]) continue; vis[u] = 1;
		for (int i = h[u]; i; i = ne[i]) {
			int v = e[i];
			if (d[v] > d[u] + w[i]) {
				d[v] = d[u] + w[i];
				q.push({d[v], v});
			}
		}
	} cout << d[n] << endl; return 0;
}

```

---

## 作者：Luxingguang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc340_d)

## 一、思路分析
------------
一道最短路的模板题。每次输入，就相当于建立两条边。因为 $N$ 很大，所以我们需要用 $O(n\times \log(n))$ 的 Dijkstra。

## 二、构造代码
------------
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,a,b,x; 
int dis[N];
bool vis[N];
struct z{
	int v,d;
	bool operator < (const z&rhs)const{
		return d>rhs.d;
	}
}vex;
vector<z> G[N];
void djs(int u){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[u]=0;
	priority_queue<z> pq;
	vex.v=u,vex.d=0;
	pq.push(vex);
	while(!pq.empty()){
		vex=pq.top();
		pq.pop();
		int v=vex.v;
		if(vis[vex.v])
			continue;
		vis[v]=true;
		for(int i=0;i<G[v].size();i++){
			int j=G[v][i].v;
			if(!vis[j]&&dis[v]+G[v][i].d<dis[j]){
				dis[j]=dis[v]+G[v][i].d;
				vex.v=j;vex.d=dis[j];
				pq.push(vex);
			}
		}
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		scanf("%lld%lld%lld",&a,&b,&x);
		vex.v=i+1,vex.d=a;
		G[i].push_back(vex);
		vex.v=x,vex.d=b;
		G[i].push_back(vex);
	}djs(1);
	printf("%lld",dis[n]);
	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[AT_abc340_d [ABC340D] Super Takahashi Bros.](https://www.luogu.com.cn/problem/AT_abc340_d)

### 思路

我们把游戏抽象成节点，题目变成了这样：你现在在第一个节点，要到第 $n$ 个节点，从 $i$ 到 $i+1$ 路径的长度为 $A_i$，从 $i$ 到 $X_i$ 路径的长度为 $B_i$，求 $1$ 到 $n$ 的最短路。然后你就会发现这是一道最短路的模板题，直接上 Dijkstra 即可。时间复杂度 $O(n\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using std::cin;using std::cout;
constexpr int N=200005;
constexpr long long inf=1e18;
int n,a,b,x;
long long dis[N];
bool vis[N];
struct A{int v,w;};
std::vector<A>edge[N];
struct B{
	int u;long long dis;
	inline bool operator<(const B &a)const{return dis>a.dis;}
};
std::priority_queue<B>q;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;for(int i=2;i<=n;++i) dis[i]=inf;
	for(int i=1;i<n;++i){
		cin>>a>>b>>x;
		edge[i].push_back(A{i+1,a});
		edge[i].push_back(A{x,b});
	}
	q.push(B{1,0});
	while(!q.empty()){
		B k=q.top();q.pop();
		if(vis[k.u]) continue;
		vis[k.u]=1;
		for(A i:edge[k.u]){
			if(dis[k.u]+i.w<dis[i.v]){
				dis[i.v]=dis[k.u]+i.w;
				q.push(B{i.v,dis[i.v]});
			}
		}
	}
	cout<<dis[n];
	return 0;
}
```

---

## 作者：Bpds1110 (赞：0)

对于每个阶段 $i$，有两种选择，分别是花 $a_i$ 的代价到 $i + 1$，和花 $b_i$ 的代价到 $x_i$。

我们可以考虑把 $n$ 个阶段看做**有向图**中的 $n$ 个点。对于每个点 $i < n$，连两条边。第一条连向 $i + 1$，边权为 $a_i$，表示通过 $i$ 花费 $a_i$ 的代价到达 $i + 1$。第二条连向 $x_i$，表示通过 $i$ 花费 $b_i$ 的代价到达 $x_i$。

题目求从 $1$ 到 $n$ 的最少代价，用 Dijkstra 跑一遍最短路即可。

```cpp
#include <bits/stdc++.h>
#define int long long

const int N = 2e5 + 100;
struct node {
	int id, dis;
	bool operator < (const node &b) const {
		return b.dis < dis;
	}
}; std::priority_queue <node> q;
struct nde {
	int to, w;
}; std::vector <nde> G[N];
int dis[N], n;
bool vis[N];

void Dijkstra(int s) {
	for (int i = 1; i <= n; ++ i) dis[i] = 1e18, vis[i] = 0; 
	dis[s] = 0; q.push((node) {s, 0});
	while (! q.empty()) {
		int u = q.top().id; q.pop();
		if (vis[u]) continue ; vis[u] = 1;
		for (int i = 0; i < G[u].size(); ++ i) {
			int v = G[u][i].to, w = G[u][i].w;
			if (dis[u] + w >= dis[v]) continue ;
			dis[v] = dis[u] + w;
			q.push((node) {v, dis[v]});
		}
	} return void();
}

signed main() {

//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	std::cin >> n;
	for (int i = 1, a, b, c; i < n; ++ i) {
		std::cin >> a >> b >> c;
		G[i].push_back((nde) {i + 1, a});
		G[i].push_back((nde) {c, b});
	}
	Dijkstra(1);
	std::cout << dis[n];

	return 0;
}

```


---

## 作者：yyrwlj (赞：0)

## 思路

考虑将原问题转化成图论问题。

对于形如花费 $c$ 时间通过第 $a$ 关达到第 $b$ 关这样的关系，就相当于 $a$ 到 $b$ 连一条边权为 $c$ 的边。

然后跑一遍堆优化 dijkstra 求点 $1$ 到 $n$ 的最短路即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
typedef long long LL;
typedef pair<LL, int> PII;
struct Edge{
    int e, to, nxt;
}g[N << 1];
int h[N], idx;
LL dis[N];
bool st[N];
void add(int a,int b,int c)
{
    g[++idx] = {c, b, h[a]}, h[a] = idx;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i=1;i<=n;i++)
    {
        int a, b, x;
        scanf("%d%d%d", &a, &b, &x);
        add(i, i + 1, a);
        add(i, x, b);
    }
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII> > q;
    q.push({0, 1});
    while (!q.empty())
    {
        PII now = q.top();
        q.pop();
        int u = now.second;
        LL d = now.first;
        if (st[u])
            continue;
        st[u] = true;
        for (int i = h[u]; i; i = g[i].nxt)
        {
            int j = g[i].to, w = g[i].e;
            if (dis[j] > d + w)
            {
                dis[j] = d + w;
                q.push({dis[j], j});
            }
        }
    }
    printf("%lld", dis[n]);
    return 0;
}
```

---

## 作者：Double_Light (赞：0)

因为 $i$ 阶段的最小花费可能并不是从 $1\sim i-1$ 阶段转移而来的（反例如样例 $2$），所以不可以动态规划、递推等。同时这个数据范围搜索会超时，所以将问题转化为图上问题。

若从 $u$ 阶段可以花费 $w$ 秒直接到达 $v$ 阶段，就从 $u$ 向 $v$ 连一条权值为 $w$ 的有向边。对于 $i$ 阶段，就向 $i+1$ 阶段连一条长度为 $a_i$ 的边，同时向 $x_i$ 阶段连一条长度为 $b_i$ 的边。

问题就是从 $1$ 到 $N$ 的最短路。

于是只需要跑一个 dijkstra 即可。

```cpp
#include<iostream>
#include<queue>
#define pi pair<int,int>
#define int long long
using namespace std;
int n,a[200005],b[200005],x[200005],ans[200005];
struct Edge{
	int u,v,nxt,w;
}e[400005];
int tot,head[200005];
void add_edge(int u,int v,int w){
	e[++tot]={u,v,head[u],w};
	head[u]=tot;
}priority_queue<pi,vector<pi>,greater<pi> >q;
bool f[200005];
int dijkstra(int x){
	while(f[x]==0){
		int u=q.top().second;
		q.pop();
		if(f[u])continue;
		f[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			if(!f[e[i].v]&&ans[u]+e[i].w<ans[e[i].v]){
				ans[e[i].v]=ans[u]+e[i].w;
				q.push({ans[e[i].v],e[i].v});
			}
		}
	}
	return ans[x];
}
signed main(){
	cin>>n;
	q.push({0,1});
	for(int i=1;i<n;i++){
		cin>>a[i]>>b[i]>>x[i];
		add_edge(i,i+1,a[i]);
		add_edge(i,x[i],b[i]);
	}
	for(int i=2;i<=n;i++)ans[i]=1e18;
	cout<<dijkstra(n);
	return 0;
}
```


---

## 作者：gongziwen (赞：0)

这道 D 题想起来还是挺简单的。

我就不放正解之外的解法了，这道题一开始可能想到贪心，但是不对，因为 $x_i<i$ 是有可能的。那么就会有环，再考虑是稀疏图，所以一眼堆优 Dijkstra。

建图 $G=(V,E)$，$V=[1..n]$，$E=(u,u+1)\forall u\in [1..n-1]\bigcup(u,x_u)\forall u\in [1..n-1]$，$w(u,u+1)=a_u\forall (u,u+1)\in E$，$w(u,x_u)=b_u\forall (u,x_u)\in E$。

然后跑堆优 Dijkstra。起点为 $1$，终点为 $n$。

因为可以通过 $a_i$ 爬上去，所以一定有解。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#define int long long
struct EDGE{
	int ver,w;
};
struct NODE{
	int point,dist;
};
const int N=2e5+6,M=5e5+6;
int n,m,dist[M],nowdist[M],a[N],b[N],x[N];
std::vector<EDGE>edge[N];
bool cmp(NODE x,NODE y){return x.dist>y.dist;}
struct priority_queue{
	NODE a[M];
	int size;
	void push(NODE x)
	{
		a[++size]=x;
		std::push_heap(a+1,a+size+1,cmp);
	}
	void pop()
	{
		std::pop_heap(a+1,a+size+1,cmp);
		size--;
	}
	NODE top(){return a[1];}
	bool empty(){return !size;}
}q;
int heap_dijkstra(int s,int t)//板子不熟悉建议复习
{
	for(int i=1;i<=n;i++)
		if(i!=s) q.push({i,(int)1e15}),dist[i]=1e15;
	q.push({s,0}),dist[s]=0;
	while(!q.empty())
	{
		while(!q.empty()&&q.top().dist!=dist[q.top().point]) q.pop();
		if(q.empty()) break;
		NODE vp=q.top();
		int v=vp.point;
		q.pop();
		for(int j=0;j<edge[v].size();j++)
		{
			int u=edge[v][j].ver;
			if(dist[u]>vp.dist+edge[v][j].w)
			{
				dist[u]=vp.dist+edge[v][j].w;
				q.push({u,dist[u]});
			}
		}
	}
	return dist[t];
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%lld%lld%lld",a+i,b+i,x+i);
		edge[i].push_back({i+1,a[i]});
		edge[i].push_back({x[i],b[i]});
	}//建边
	printf("%lld",heap_dijkstra(1,n));
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

注意到这就是很典型的图论建模，直接把 $i$ 与 $i+1,x_i$ 连边，边权分别是 $a_i,b_i$，跑最短路即可。由于 $a_i,b_i>0$，所以可以跑 dijkstra。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=500010;
struct node
{
	int u,dist;
	bool operator >(const node& x)const
	{
		return x.dist<dist;
	}
};
struct edge
{
	int v,w;
};
vector<edge> G[N];
int dist[N],vis[N],n;
priority_queue<node,vector<node>,greater<node>> q;
void dijkstra(int s)
{
	memset(dist,0x3f,sizeof dist);
	dist[s]=0;
	q.push({s,0});
	while(!q.empty())
	{
		int u=q.top().u;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto e:G[u])
		{
			int v=e.v,w=e.w;
			if(dist[v]>dist[u]+w)
			{
				dist[v]=dist[u]+w;
				q.push({v,dist[v]});
			} 
		}
	}
}
signed main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int a,b,x;
		cin>>a>>b>>x;
		G[i].push_back({i+1,a});
		G[i].push_back({x,b});
	}
	dijkstra(1);
	cout<<dist[n];
	return 0;
}

---

## 作者：fls233666 (赞：0)

直接做好像没有什么好的入手思路，考虑进一步转化。

不妨把每个关卡看作一个点，把两种通关方式分别看作边。更准确来说，是一条从点 $i$ 连到点 $i+1$ 的权重为 $A_i$ 的有向边和一条从点 $i$ 连到点 $X_i$ 的权重为 $B_i$ 的有向边。至此，我们把原题的背景转化为了一张**有向图**。而求到达第 $N$ 关的最短用时，就转化为**求这个有向图的从点 $1$ 到点 $N$ 的最短路。**

完成转化后，这题就做完一大半了。接下来就是选一种方法求解最短路即可。注意到 $A_i,B_i$ 均为正数，因此本人采用堆优化的 Dijkstra 算法实现，代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define ll long long
using namespace std;

const int mxn = 2e5+5;

bool deal[mxn];
int tot,n,lst[mxn];
ll w[mxn<<1],dis[mxn];
int to[mxn<<1],nxt[mxn<<1];

priority_queue < pair<ll,int>,vector< pair<ll,int> >,greater< pair<ll,int> > >que;

inline void add(int a,int b,ll abw){
    tot++;
    to[tot]=b;
    w[tot]=abw;
    nxt[tot]=lst[a];
    lst[a]=tot;
}  //边链表连边

int main(){
    int p;
    ll wa,wb;
    scanf("%d",&n);
    for(int h,i=1;i<n;i++){
        scanf("%lld%lld%d",&wa,&wb,&h);
        add(i,i+1,wa);
        add(i,h,wb);
    }  //建图
    
    memset(dis,127,sizeof(dis));
    dis[1]=0;
    que.push(make_pair(0,1));  //初始化
    
    while(!que.empty()){
        p=que.top().second;
        que.pop();
        if(deal[p])
            continue;
        deal[p]=true;
        for(int i=lst[p];i;i=nxt[i]){
            if(dis[to[i]]>dis[p]+w[i]){
                dis[to[i]]=dis[p]+w[i];
                que.push(make_pair(dis[to[i]],to[i]));
            }
        }
    }  //最短路求解
    
    printf("%lld",dis[n]);
    return 0;
}
```


---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/AT_abc340_d)

考虑把这题转换为图论模型。

按照题意，就是 $i$ 和 $i+1$ 有一条长度为 $a_i$ 的边，$i$ 和 $X_i$ 有一条长度为 $b_i$ 的边。

然后跑最短路即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
#define int long long 
int n,dis[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
struct node{
	int v,w;
};
vector<node> g[N<<1];
void Dijkstra(int s){
	memset(dis,0x7f,sizeof(dis));
	q.push({0,s}),dis[s]=0;
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i].v,w=g[u][i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({dis[v],v});
			}
		}
	}
	cout<<dis[n]<<endl;
}
signed main(){
	cin>>n;
	for(int i=1,x,y,z;i<n;i++){
		cin>>x>>y>>z;
		g[i].push_back({z,y}),g[i].push_back({i+1,x});
	}
	Dijkstra(1);
}
```


---

## 作者：_O_v_O_ (赞：0)

考场上一眼秒掉了。

首先，题目可以这样转换：

> 给定一个有 $n$ 个点的图（每一关可抽象成一个个点）：
>
> - 对于每个 $\forall1\le i<n$ 的 $i$，在 $i\Rightarrow i+1$ 有一条边，边权为 $a_i$。
> - 对于每个 $\forall1\le i<n$ 的 $i$，在 $i\Rightarrow x_i$ 有一条边，边权为 $b_i$。
>
> 问 $1\Rightarrow n$ 的最短路是多少。

这样就把这道题变成板子了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=1e6+5;
int head[maxn],edgenum;
int n,m,s;
struct edge{
	int to,w,nxt;
}e[maxn];

void addedge(int u,int v,int w){
	e[++edgenum].nxt=head[u];
	e[edgenum].to=v;
	e[edgenum].w=w;
	head[u]=edgenum;
}

bool vis[maxn];
int dis[maxn];
int INF=LONG_LONG_MAX;
priority_queue<pair<int,int> > q;
void dij(){
	for(int i=1;i<=n;i++){
		dis[i]=INF;
		vis[i]=0;
	}
	dis[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()){
		int now=q.top().second;
		q.pop();
		if(vis[now]) continue;
		vis[now]=1;
		for(int i=head[now];i;i=e[i].nxt){
			int nxt=e[i].to;
			if(dis[now]+e[i].w<dis[nxt]){
				dis[nxt]=dis[now]+e[i].w;
				q.push(make_pair(-dis[nxt],nxt));
			}
		}
	}
}

signed main(){
	cin>>n;
	s=1;
	for(int i=1;i<n;i++){
		int a,b,x;
		cin>>a>>b>>x;
		addedge(i,i+1,a);
		addedge(i,x,b);
	}
	dij();
	cout<<dis[n];
	return 0;
}
```


---

## 作者：apiad (赞：0)

这道题，他说，可以从 $i$ 到 $i+1$ 贡献为 $a_i$，然后，$i$ 到 $x_i$ 贡献为 $b_i$，一开始还想着将 $x$ 反着映射一下，然后 Dp，但是我们发现样例中有 $x_i \le i$ 的，Dp 无法做到有后效性。

所以我们可以连边 $(u,v,w)$，对于 $i$ 可以连 $(i,i+1,a_i)$ 和 $(i,x_i,b_i)$。这样，边有 $2\times n$，直接跑最短路即可，用的 Dij，所以时间复杂度是 $O(n\log n)$。 

[code](https://atcoder.jp/contests/abc340/submissions/50173386)。

---

## 作者：xixisuper (赞：0)

# [ABC340D] Super Takahashi Bros.题解

长着 DP 脸的最短路径题。

## 思路

~~刚看题以为是个一维 DP，准备秒，结果发现不满足无后效性。~~

正解：最短路径。

把每一个游戏阶段想象成一个节点，对于节点 $i$ 来说，就有从它到节点 $i+1$ 边权为 $A_i$ 的一条边，以及从它到节点 $X_i$ 边权为 $B_i$ 的一条边。

跑一个最短路径，最后输出从节点 $1$ 到节点 $n$ 的最短路径就行了。

我用的是堆优化的 dijkstra 算法，时间复杂度 $O(n \log n)$（因为最多有不超过 $2n$ 条边）。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <queue> 
#define ll long long
using namespace std;
const ll N=1e6+10;
struct node{
	ll from,to,w,nxt;
	friend bool operator >(const node a,const node b){
		return a.w > b.w;
	}
}edge[N];
priority_queue<node,vector<node>,greater<node> > q;
ll tot,head[N],n,dis[N];
bool vis[N];
void add_edge(ll u,ll v,ll len){
	edge[++tot].from = u;
	edge[tot].to = v;
	edge[tot].w = len;
	edge[tot].nxt = head[u];
	head[u] = tot;
}
void dijkstra(ll stt){
	dis[stt]=0;
	vis[stt]=1;
	for(ll i=head[stt];i;i=edge[i].nxt)
		q.push(edge[i]);
	while(!q.empty()){
		node now=q.top();
		q.pop();
		if(vis[now.to]) continue;
		dis[now.to]=now.w;
		vis[now.to]=1;
		for(ll i=head[now.to];i;i=edge[i].nxt){
			node in=edge[i];
			in.w+=dis[in.from];
			q.push(in);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	ll x,y,z;
	for(ll i=1;i<n;++i){
		cin>>x>>y>>z;
		add_edge(i,i+1,x);
		add_edge(i,z,y);
	}
	dijkstra(1);
	cout<<dis[n];
	return 0;
}
```


---

