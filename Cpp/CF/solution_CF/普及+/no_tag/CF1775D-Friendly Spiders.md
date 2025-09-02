# Friendly Spiders

## 题目描述

Mars is home to an unusual species of spiders — Binary spiders.

Right now, Martian scientists are observing a colony of $ n $ spiders, the $ i $ -th of which has $ a_i $ legs.

Some of the spiders are friends with each other. Namely, the $ i $ -th and $ j $ -th spiders are friends if $ \gcd(a_i, a_j) \ne 1 $ , i. e., there is some integer $ k \ge 2 $ such that $ a_i $ and $ a_j $ are simultaneously divided by $ k $ without a remainder. Here $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

Scientists have discovered that spiders can send messages. If two spiders are friends, then they can transmit a message directly in one second. Otherwise, the spider must pass the message to his friend, who in turn must pass the message to his friend, and so on until the message reaches the recipient.

Let's look at an example.

Suppose a spider with eight legs wants to send a message to a spider with $ 15 $ legs. He can't do it directly, because $ \gcd(8, 15) = 1 $ . But he can send a message through the spider with six legs because $ \gcd(8, 6) = 2 $ and $ \gcd(6, 15) = 3 $ . Thus, the message will arrive in two seconds.

Right now, scientists are observing how the $ s $ -th spider wants to send a message to the $ t $ -th spider. The researchers have a hypothesis that spiders always transmit messages optimally. For this reason, scientists would need a program that could calculate the minimum time to send a message and also deduce one of the optimal routes.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775D/cbd40cc2068feef6a151db4f398da64f76e37f80.png)

## 说明/提示

The first example is shown above. It shows that the message from the $ 5 $ -th spider (with eight legs) to the $ 6 $ -th spider (with $ 15 $ legs) is optimal to pass through the $ 4 $ -th spider (with six legs).

In the second example, the spider number $ 7 $ (with $ 11 $ legs) is not friends with anyone, so it is impossible to send him a message.

## 样例 #1

### 输入

```
7
2 14 9 6 8 15 11
5 6```

### 输出

```
3
5 4 6```

## 样例 #2

### 输入

```
7
2 14 9 6 8 15 11
5 7```

### 输出

```
-1```

## 样例 #3

### 输入

```
7
2 14 9 6 8 15 11
5 5```

### 输出

```
1
5```

# 题解

## 作者：Ray1 (赞：30)

考虑建图跑 bfs，在每个蜘蛛之间建边的时间复杂度是 $O(n^2\log a)$ 的，直接 TLE。

注意到 $\gcd(a,b)≠1$ 的前提是 $a,b$ 有共同的质因数，于是考虑在每个质因数之间建边。

筛出在 $a_i$ 范围内的所有质因数，将每个 $a_i$ 分解质因数，这里的时间复杂度是 $O(n\times f(\sqrt a))$（$f(x)$ 表示 $≤x$ 的质数个数）。若 $a_i$ 有两个不同的质因数，就在这两个质因数之间建一条边，由于 $a_i$ 最多有 $\log a_i$ 个质因数，这里的时间复杂度是 $O(n\log^2a)$。

为了方便判断起点和重点，我们构建虚点 $x$ 与起点 $a_s$ 的所有质因数建边，虚点 $y$ 与终点 $a_t$ 的所有质因数建边。从 $x$ 向 $y$ 跑 bfs 即可求出答案，bfs 的时间复杂度是 $O(f(a))$。

**一条边的实质是一只蜘蛛**，为了统计路径，边需要记录搭这条边的蜘蛛编号。bfs 时每个到达的质因数节点需要记录路径的上一个质因数节点（即从哪个来的），和转移通过的蜘蛛。最后从终点倒序输出路径即可。

---

## 作者：xiaruize (赞：9)

~~p.s.严厉谴责出题人在题目页面放蜘蛛啊，很难受qwq~~

**思路**

暴力建图显然需要 $O(n^2)$ , 无法通过本题

考虑是否可以优化, 发现同样的公因子可能被建多条边, 导致边数达到 $n^2$ 级别

如何解决这个问题? 可以对于每个公因子建一个点, 将所有有这个因子的数全部与这个点连边, 入边边权为 $1$ , 出边为 $0$

进一步优化, 可以发现, 只需要对质因子建点

对于这张图跑 `Dijkstra` 即可

**Code**

```cpp
/*
    Name:
    Author: xiaruize
    Date:
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define ALL(a) (a).begin(), (a).end()
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define pis pair<int, string>
#define sec second
#define fir first
#define sz(a) int((a).size())
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define repp(i, x, y) for (int i = x; i >= y; i--)
#define Yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define No cout << "No" << endl
#define NO cout << "NO" << endl
#define debug(x) cerr << #x << ": " << x << endl
#define double long double
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const int N = 3e5 + 10;

// bool st;
int n;
int a[N];
vector<pii> g[N * 2];
int fa[N * 2];
int siz = 0;
int dis[N * 2];
int st, en;
vector<int> res;
// bool en;

void dfs(int x)//找路径
{
    res.pb(x);
    if (x < N)
        siz++;
    if (x == st)
        return;
    dfs(fa[x]);
}

signed main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // cerr<<(&en-&st)/1024.0/1024.0<<endl;
    // auto t_1=chrono::high_resolution_clock::now();
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        int x = a[i];
        for (int j = 2; j * j <= x; j++)
        {
            if (x % j == 0)
            {
                while (x % j == 0)
                    x /= j;
                g[i].pb({j + N, 1});
                g[j + N].pb({i, 0});
            }
        }
        if (x != 1)
        {
            g[i].pb({x + N, 1});
            g[x + N].pb({i, 0});
        }
    }
    cin >> st >> en;
    //Dijkstra
    priority_queue<pii, vector<pii>, greater<pii>> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[st] = 0;
    q.push({0, st});
    while (!q.empty())
    {
        int x = q.top().sec, d = q.top().fir;
        q.pop();
        if (dis[x] < d)
            continue;
        if (x == en)
            break;
        for (auto v : g[x])
        {
            if (dis[v.fir] > dis[x] + v.sec)
            {
                dis[v.fir] = dis[x] + v.sec;
                fa[v.fir] = x;
                q.push({dis[v.fir], v.fir});
            }
        }
    }
    if (dis[en] >= INF)
    {
        cout << "-1" << endl;
        return 0;
    }
    dfs(en);
    reverse(ALL(res));
    cout << siz << endl;
    for (auto v : res)
        if (v < N)
            cout << v << ' ';
    // auto t_2=chrono::high_resolution_clock::now();
    // cout <<". Elapsed (ms): " << chrono::duration_cast<chrono::milliseconds>(t_2 - t_1).count() << endl;
    return 0;
}
```

---

## 作者：ningago (赞：7)

用 $m$ 表示图的边数

对每个 $a_i$ 分解只因数。

每个只因数在原图上建成虚点，每个 $a_i$ 向只因数的点连边，边权为 $1$。

这样原来 $m=O(n^2)$ 的图上每一条边都在新图上形成了一条边权为 $2$ 的路径。

此时 $m=O(kn)$，由于 $2\times3\times5\times7\times11\times13\times17=510510\geq 3\times 10^5$，所以 $k \leq 7$。

然后跑最短路算法即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define N 1200010

int n;
int a[N];
int S,T;
bool vis[N];

int h[N * 2],e[N * 20],ne[N * 20],iidx;
void add_edge(int x,int y)
{
	ne[++iidx] = h[x];
	h[x] = iidx;
	e[iidx] = y;
}

void add(int x,int y)
{
	add_edge(x,y);
	add_edge(y,x);
}
bool flag;
int dis[N * 2];
struct node
{
	int id,dis;
	bool operator < (const node &B)const
	{
		return dis > B.dis;
	}
};

std::priority_queue <node> q;

void dijstra()
{
	memset(dis,0x3f,sizeof(dis));
	q.push((node){S,0});
	dis[S] = 0;
	while(!q.empty())
	{
		int k = q.top().id;
		q.pop();
		if(vis[k])
			continue;
		vis[k] = 1;
		for(int i = h[k];~i;i = ne[i])
		{
			int nx = e[i];
			if(dis[nx] > dis[k] + 1)
			{
				dis[nx] = dis[k] + 1;
				q.push((node){nx,dis[nx]});
			}
		}
	}
}

int sta[N * 2],top;

void dfs(int k)
{
	if(k <= n)
		sta[++top] = k;
	if(k == S)
		return;
	for(int i = h[k];~i;i = ne[i])
	{
		int nx = e[i];
		if(dis[nx] == dis[k] - 1)
		{
			dfs(nx);
			return;
		}
	}
}

signed main()
{
	memset(h,-1,sizeof(h));
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d",&a[i]);
		int x = a[i];
		for(int j = 2;j * j <= a[i];j++)
		{
			if(x % j == 0)
			{
				while(x % j == 0)
					x /= j;
				add(i,j + n);
			}
		}
		if(x != 1)
			add(i,x + n);
	}
	scanf("%d%d",&S,&T);
	dijstra();
	if(dis[T] == 0x3f3f3f3f)
	{
		printf("-1\n");
		return 0;
	}
	printf("%d\n",dis[T] / 2 + 1);
	memset(vis,0,sizeof(vis));
	dfs(T);
	for(int i = top;i >= 1;i--)
		printf("%d ",sta[i]);
	return 0;
}
```

---

## 作者：Neil_Qian (赞：4)

# CF1775D Friendly Spiders 题解
给你 $n$ 个数 $a_i$，对于任意两个数 $a_i$ 和 $a_j$，如果它们不互质，则它们之间有一条无向无权边。求给定的 $s$ 到 $t$ 的最短路。

对于一个无向无权边，很容易发现建好图以后一个广搜即可轻松解决。问题在于，如果任意两个点来判断的话，先要 $O(n^2)$ 来枚举 $i,j$，然后求最大公因数 $O(\log a)$，总复杂度 $O(n^2\log a)$，肯定会超时。路已经走到了尽头。

这时候，我们观察样例，发现有一个质因数的所有点都会连一条边，非常耗时。我们可以建一些虚点，对于虚点 $n+i$，将所有有 $i$ 这个质因子的所有点与这个虚点相连。这样，枚举每个 $a_i$ 的质因子即可。建图时间复杂度 $O(n\sqrt{a_i})$。

这样做的原理是什么呢？对于所有有一个质因子 $i$ 的数，任意两个点之间都有边，也就是说这个子图是一个完全图，一步就可以到达这个子图的任意点。我们用类似并查集的思路，将这个子图找一个可以代表它的虚点。在广搜中，我们假设从 $x$ 出发，先可以到 $x$ 的所有虚点，然后能到 $x$ 所在的完全图的任意点。依此类推。

但是，求解并没有结束，因为在广搜的时候会把虚点也算上，因此输出的时候要把虚点去掉。其实相对简单。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;const int N=6e5+2;//注意，因为有虚点，所以至少开n的两倍
int n,a,s,t,d[N],x;vector<int> v[N],g;queue<int> q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		for(int j=2;j*j<=a;j++)if(a%j==0){//分解质因数
			v[i].push_back(n+j),v[n+j].push_back(i);//连边
			while(a%j==0)a/=j;
		}
		if(a>1)v[i].push_back(n+a),v[n+a].push_back(i);//还剩一个质因数
	}
	scanf("%d%d",&s,&t);
	q.push(s),d[s]=1;//广搜
	while(!q.empty()){
		x=q.front(),q.pop();
		for(int k:v[x])if(!d[k])d[k]=d[x]+1,q.push(k);//计算距离
	}
	if(!d[t]){printf("-1\n");return 0;}//无法到达，即无解
	g.push_back(t);//这个vector是倒叙存储的，因为最短路找路径时只能倒退
	for(int i=t;i!=s;)for(int k:v[i])if(d[k]+1==d[i])//找到前一个点
	{i=k,g.push_back(k);break;}
	reverse(g.begin(),g.end());//翻转vector
	printf("%d\n",(g.size()+1)/2);//把虚点去掉
	for(int k:g)if(k<=n)printf("%d ",k);//输出路径
	return printf("\n"),0;
}
```


---

## 作者：honglan0301 (赞：3)

## 题意简述

给定长度为 $n\ (n\leq3\times 10^5)$ 的数列 $a\ (a_i\leq3\times 10^5)$, 给定起点 $s$ 和终点 $t$, 求最短的一条路径 $b_1,b_2,...,b_k$ 满足 $b_1=s,b_k=t$, 且对于 $\forall i∈[1,k-1], \gcd(a_{bi},a_{b(i+1)})>1$ 或报告无解。

## 题目分析

考虑最短路，直接建图显然复杂度爆炸，那么我们考虑对值域内的每一个质数建图。我们首先预处理出每个数的所有质因数，那么对于每个 $a_i$, 我们将它所有的质因数互相连边，表示这些个质因数可以通过 $a_i$ 互相转化。再从起点向 $a_s$ 的所有质因数连边，终点向 $a_t$ 的所有质因数连边，表示从起/终点开始可以直接到达含这些质因数的数。最后跑一遍 bfs 即可，记得记录下回溯时需要的信息，具体见代码。

点数 $≈26000$, 边数最多 $300000\times5\times 6+2\times5≈9000000$, 可以通过本题。

## 代码
代码应该比较清楚。
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
using namespace std;

int n,a[300005],s,t,cnt,head[26005],num[300005],cntp,dis[26005];
bool ishs[300005];
vector <int> ys[300005],lj;

struct edge
{
	int son;
	int next;
	int nnum;
}edge[9000055];

void adde(int x,int y,int z)
{
	cnt++;
	edge[cnt].son=y;
	edge[cnt].next=head[x];
	edge[cnt].nnum=z;
	head[x]=cnt;
}

void init()
{
	ishs[1]=1;
	for(int i=2;i<=300000;i++)
	{
		if(!ishs[i])
		{
			ys[i].push_back(i); num[i]=++cntp;
			for(int j=2;i*j<=300000;j++)
			{
				ishs[i*j]=1;
				ys[i*j].push_back(i);
			}
		}
	}
}

queue <int> Q;

void bfs()
{
	memset(dis,127,sizeof(dis));
	Q.push(cntp+1); dis[cntp+1]=0;
	while(!Q.empty())
	{
		int nr=Q.front();
		Q.pop();
		for(int i=head[nr];i>0;i=edge[i].next)
		{
			if(dis[nr]+1<dis[edge[i].son])
			{
				dis[edge[i].son]=dis[nr]+1;
				Q.push(edge[i].son);
			}
		}
	}
}

void hs()
{
	int nowd=0;
	while(nowd!=cntp+1)
	{
		for(int i=head[nowd];i>0;i=edge[i].next)
		{
			if(dis[nowd]==dis[edge[i].son]+1)
			{
				lj.push_back(edge[i].nnum);
				nowd=edge[i].son;
				break;
			}
		}
	}
}

int main()
{
	cin>>n; for(int i=1;i<=n;i++) cin>>a[i];
	cin>>s>>t;
	if(s==t) {cout<<1<<endl<<s<<endl; return 0;}
	init();
	for(auto i:ys[a[s]])
	{
		adde(num[i],0,s);
		adde(0,num[i],s);
	}
	for(auto i:ys[a[t]])
	{
		adde(cntp+1,num[i],t);
		adde(num[i],cntp+1,t);
	}
	for(int i=1;i<=n;i++)
	{
		for(auto j:ys[a[i]])
		{
			for(auto k:ys[a[i]])
			{
				if(j!=k) adde(num[j],num[k],i);
			}
		}
	}
	bfs();
	if(dis[0]>2000000000) {cout<<-1<<endl; return 0;}
	hs();
	cout<<dis[0]<<endl;
	for(auto i:lj)
	{
		cout<<i<<" ";
	}
}
```


---

## 作者：happybob (赞：3)

套路最短路。

考虑两数 $a,b$，若 $\gcd(a,b) \neq 1$，那么 $a,b$ 一定有公共质因数。

于是可以考虑对于每一个点 $i$，向 $a_i$ 的所有质因数连边，然后广搜即可。

```cpp
// LUOGU_RID: 99311626
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 6e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, idx, a[N];
int id[N];
vector<int> G[N];

int s, t;
int dis[N], from[N];

void bfs()
{
	queue<int> q;
	memset(dis, 0x7f, sizeof dis);
	dis[s]=0;
	q.push(s);
	while(q.size())
	{
		int u =q.front();
		q.pop();
		for(int j:G[u])
		{
			if (dis[j]==dis[0])
			{
				dis[j]=dis[u]+1;
				q.push(j);
				from[j]=u;
			}
		}
	}
}

int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	scanf("%d", &n);
	idx = n;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		int rr = a[i], p = a[i];
		for (int j = 2; j * j <= rr; j++)
		{
			int c = 0;
			while (p % j == 0)
			{
				c++;
				p /= j;
			}
			if (c)
			{
				int nx = id[j] == 0 ? (id[j] = ++idx) : id[j];
				G[i].emplace_back(nx);
				G[nx].emplace_back(i);
			}
		}
		if (p > 1)
		{
			int c = p;
			int nx = id[c] == 0 ? (id[c] = ++idx) : id[c];
			G[i].emplace_back(nx);
			G[nx].emplace_back(i);
		}
	}
	scanf("%d%d", &s, &t);
	bfs();
	if (dis[t] == dis[0]) printf("-1\n");
	else 
	{
		printf("%d\n", dis[t] / 2 + 1);
		vector<int> ans;
		do
		{ // 1
			ans.emplace_back(t);
			t = from[t];
		} while (t);
		reverse(ans.begin(), ans.end());
		for (int i : ans) 
		{
			if (i <= n) printf("%d ", i);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Mine_King (赞：2)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/17042849.html)

# D. Friendly Spiders

## Problem

[CF1775D Friendly Spiders](https://codeforces.com/contest/1775/problem/D)

**题目大意：**

给你 $n$ 个数 $a_i$，若 $\gcd(a_i, a_j) \neq 1$ 则在 $i,j$ 之间连一条无向变，求从 $s$ 到 $t$ 的最短路。

## Solution

这是一个经典的 Trick：对于每个因子建立一个虚点，每个点与自己的因子连边。

这样做显然是对的，但是边数到了 $O(n \sqrt{n})$。不过容易发现只需要考虑质因子即可，这样边数就是 $O(n \log n)$ 了。

## Code

```cpp
// Think twice, code once.
#include <stack>
#include <queue>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n,s,t,dis[600005],pre[600005];
int cnt,prime[300005],f[300005];
struct graph {
	int tot,hd[600005];
	int nxt[10000005],to[10000005];
	void add(int u,int v) {
		nxt[++tot]=hd[u];
		hd[u]=tot;
		to[tot]=v;
		return ;
	}
}g;
queue<int> q;
stack<int> ans;

int main() {
	for (int i=2;i<=300000;i++)
		if (!f[i]) {
			prime[++cnt]=i;
			for (int j=2*i;j<=300000;j+=i) f[j]=1;
		}
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		int x;
		scanf("%d",&x);
		for (int j=1;j<=cnt&&prime[j]*prime[j]<=x;j++)
			if (x%prime[j]==0) {
				g.add(i,n+j);
				g.add(n+j,i);
				while (x%prime[j]==0) x/=prime[j];
			}
		if (x!=1) {
			int pos=lower_bound(prime+1,prime+cnt+1,x)-prime;
			g.add(i,n+pos);
			g.add(n+pos,i);
		}
	}
	scanf("%d%d",&s,&t);
	memset(dis,-1,sizeof(dis));
	q.push(s);
	dis[s]=0;
	while (!q.empty()) {
		int now=q.front();q.pop();
		for (int i=g.hd[now];i;i=g.nxt[i])
			if (dis[g.to[i]]==-1) {
				dis[g.to[i]]=dis[now]+1;
				pre[g.to[i]]=now;
				q.push(g.to[i]);
			}
	}
	if (dis[t]==-1) {puts("-1");return 0;}
	for (int now=t;now;now=pre[now])
		if (now<=n) ans.push(now);
	printf("%d\n",(int)ans.size());
	while (!ans.empty()) printf("%d ",ans.top()),ans.pop();
	puts("");
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：0)

赛场没调出来，寄。

**trick：对于每个点，向其质因数连边。**

对于每个 $\leq 3\times 10^5$ 的质数，我们都对每一个质数建立一个虚点，注意编号不能和 $n$ 冲突。

我们考虑第 $i$ 个点向 $a_i$ 的所有质因数的虚点连无向边。

容易发现，这张新图是一个**二分图**，我们将 $1\sim n$ 的点记为 $A$ 类点，对于所有质数而建立的虚点，记为 $B$ 类点。

显然，如果在新图上联通的两个点，在原图上也一定联通。在这张新图上是 $A\rightarrow B\rightarrow A$，在原图中应该是 $A\rightarrow A$。

我们直接对原来给出的起点 $s$ 和终点 $t$ 在这张新图上进行求最短路。在跑最短路的时候记录下前驱，即它从哪里过来。因为 $s$ 和 $t$ 都是 $A$ 类点，所以路径一定长成这样：

$A\rightarrow B \rightarrow A \rightarrow B \rightarrow A$，在这张新图上是 $A\rightarrow B\rightarrow A$，在原图中应该是 $A\rightarrow A$。显然 虚点，即 $B$ 类点不能被计入路径中。

直接输出路径即可，具体的可以看代码。注意无解（无法抵达，在新图中不连通）输出 $-1$。

AC Code：
```cpp
int id[maxn],nid;
namespace number_theory{
	vector<int> p11;
	bool vis11[maxn];
	void init(){
		for(int i=2;i<maxn;i++){
			if(!vis11[i]){
				p11.push_back(i);
				id[i]=++nid;
			} 
			for(int j=0;j<p11.size()&&i*p11[j]<maxn;j++){
				vis11[i*p11[j]]=1;
				if(i%p11[j]==0) break;
			}
		}
	}
}
using namespace number_theory;
int a[maxn],vis[maxn];
int d[maxn],id1[maxn],lst[maxn];
struct edge{
	int u,v;
	bool operator <(const edge &a)const{
		return v>a.v;
	}
};
vector<edge>g[maxn];
priority_queue<edge>q;
vector<int>ans;
void dijkstra(int p){
	mem(vis,0);
	mem(d,inf);
	d[p]=0;
	q.push((edge){p,0});
	while(!q.empty()){
		int x=q.top().u;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=0;i<g[x].size();i++){
			int u=g[x][i].u,v=g[x][i].v;
			if(d[x]+v<d[u]){
				d[u]=d[x]+v;
                lst[u]=x;
				q.push((edge){u,d[u]});
			}
		}
	}
}
void solve(){
    int n=read(),cnt=n;
    F(i,1,n) a[i]=read();
    F(i,1,n){
        int x=a[i],y=a[i];
        for(int j=2;j*j<=x;j++){
            if(x%j) continue; 
            while(x%j==0) x/=j;
            g[n+id[j]].pb((edge){i,1});
            g[i].pb((edge){n+id[j],1});
        }
        if(x>=2){
            g[n+id[x]].pb((edge){i,1});
            g[i].pb((edge){n+id[x],1});
        }
    }
    int s=read(),t=read();
    dijkstra(s);
    if(d[t]>=inf) return puts("-1"),void();
    int u=t;
	vector<int>v;
	v.pb(u);
    while(u!=s){
        u=lst[lst[u]];//虚点不能被记入，所以要双重前驱
		v.pb(u);
    }
    printf("%lld\n",d[t]/2+1);//在新图中边权都是 1，但是 B 类点不能被算进去，所以要除以 2，题目还要求把起点加进去，所以要 +1
	int len=v.size();
	if(!len) return;
	dF(i,len-1,0) printf("%lld ",v[i]);
}
signed main(){
	number_theory::init();
	int lzm=1;
	wh(lzm) solve();
}
```


---

