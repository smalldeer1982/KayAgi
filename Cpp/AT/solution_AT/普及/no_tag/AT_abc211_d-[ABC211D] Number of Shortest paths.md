# [ABC211D] Number of Shortest paths

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc211/tasks/abc211_d

AtCoder 国には $ 1 $ から $ N $ の番号がついた $ N $ 個の都市と、$ 1 $ から $ M $ の番号がついた $ M $ 個の道路があります。

道路 $ i $ を通ると都市 $ A_i $ と都市 $ B_i $ の間を双方向に $ 1 $ 時間で移動することができます。

都市 $ 1 $ から都市 $ N $ へ最も早く移動することができる経路は何通りありますか？  
 答えは非常に大きくなる可能性があるので $ (10^9+7) $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,B_i) $ は相異なる
- 入力に含まれる値は全て整数である

### Sample Explanation 1

都市 $ 1 $ から都市 $ 4 $ へは最短 $ 2 $ 時間で移動することができ、それを実現する経路は $ 1\ \to\ 2\ \to\ 4 $ と $ 1\ \to\ 3\ \to\ 4 $ の $ 2 $ つです。

### Sample Explanation 2

都市 $ 1 $ から都市 $ 4 $ へは最短 $ 3 $ 時間で移動することができ、それを実現する経路は $ 1\ \to\ 3\ \to\ 2\ \to\ 4 $ の $ 1 $ つです。

### Sample Explanation 3

都市 $ 1 $ から都市 $ 2 $ に移動することはできません。この場合 $ 0 $ を出力してください。

## 样例 #1

### 输入

```
4 5
2 4
1 2
2 3
1 3
3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3
1 3
2 3
2 4```

### 输出

```
1```

## 样例 #3

### 输入

```
2 0```

### 输出

```
0```

## 样例 #4

### 输入

```
7 8
1 3
1 4
2 3
2 4
2 5
2 6
5 7
6 7```

### 输出

```
4```

# 题解

## 作者：2020luke (赞：2)

# [[ABC211D] Number of Shortest paths](https://www.luogu.com.cn/problem/AT_abc211_d) 题解

## 思路解析

题目其实说得很明白了，就是最短路计数。我们可以用一个 $s_i$ 表示从起点到 $i$ 的最短路计数，然后进行 bfs，由于边权为 $1$，所以可以使用 bfs 求最短路。如果 $u \to v$ 是 $v$ 的最短路的其中一段，就把 $s_u \to s_v$ 转移即可。

注意要记得取模。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7;
int n, m, d[N], s[N];
vector<int> g[N];
void bfs() {
	memset(d, 0x3f, sizeof(d));
	d[1] = 0; s[1] = 1;
	queue<int> q;
	q.push(1);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(auto it : g[u]) {
			if(d[it] >= d[u] + 1) {
				if(d[it] > 1e8) q.push(it);
				d[it] = d[u] + 1;
				s[it] = (s[it] + s[u]) % mod;
			}
		}
	}
}
int main() {
	cin >> n >> m;
	for(int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	bfs();
	cout << s[n];
	return 0;
}
```

---

## 作者：Jasonshan10 (赞：1)

## 题意
- 一张图，求从 $1$ 到 $n$ 的最短路的条数，答案对 $10^9+7$ 取模。

## 分析
- 最短路，显然可以用 BFS 解决。
- 接着考虑如何求条数。
	- 如果遍历到的这个点（设为 $x$ ）是最短路上的点，并且是 $y$ 这个点遍历过来的。则 ```cnt[x]=cnt[x]+cnt[y];```
   - 如果不是最短路，则跳过。
   
  
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5,mod=1e9+7;
vector<int> G[MAXN];
int step[MAXN],cnt[MAXN],push[MAXN];
void bfs(){
	queue<int> q;
	q.push(1);
	while (!q.empty()){
		int temp=q.front();
		q.pop();
		for(int i=0;i<G[temp].size();++i){
			if (step[temp]+1<=step[G[temp][i]]){
				step[G[temp][i]]=step[temp]+1;
				cnt[G[temp][i]]=(cnt[G[temp][i]]+cnt[temp])%mod;
				if (push[G[temp][i]]==0){
					push[G[temp][i]]=1;
					q.push(G[temp][i]);
				}
			}
		}
	}
}
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	memset(step,0x3f,sizeof(step));
	for(int i=1,u,v;i<=m;++i){
		scanf("%d %d",&u,&v);
		G[u].push_back(v),G[v].push_back(u);
	}
	step[1]=0;
	cnt[1]=1;
	push[1]=1;
	bfs();
	printf("%d\n",cnt[n]);
	return 0;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

给定一张 $n$ 个点 $m$ 条边的无向无权图，问从 $1$ 到 $n$ 的最短路有多少条。

## 题目分析

设 $cnt_i$ 表示从 $1$ 到 $i$ 的最短路条数，$dis_i$ 表示最短路。

这道题可以考虑使用 BFS 做，对于一个点 $v$，设第一次更新它的点为 $u$，则它的转移应为 $cnt_v \leftarrow cnt_u$ 并且 $dis_v \leftarrow dis_u+1$，表示 $v$ 的最短路是由 $u$ 转移过来的。由于 BFS 的算法流程，此时 $v$ 的最短路已经被确定下来了，所以之后再有点 $x$ 更新 $v$ 时，仅当 $dis_v=dis_x+1$ 时，才有转移 $cnt_v \leftarrow cnt_v+cnt_x$，表示 $1 \rightarrow x \rightarrow v$ 是 $1 \rightarrow v$ 的另一条最短路。

最后输出 $cnt_n$ 即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define random(a,b) (rand()%(b-a+1)+a)
const int N=2e5+10,mod=1e9+7;
int n,m,x,y,dis[N],cnt[N],vis[N];
vector<int> G[N]; 
queue<int> q;
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
    	cin>>x>>y;
    	G[x].push_back(y);
    	G[y].push_back(x);
	}
	memset(dis,0x3f,sizeof dis);
	dis[1]=0;
	cnt[1]=1;
	q.push(1);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=1;
		for(int v:G[u])
		{
			if(!vis[v])
			{
				dis[v]=dis[u]+1;
				cnt[v]+=cnt[u];
				q.push(v);
				vis[v]=1;
			}
			else if(dis[u]+1==dis[v])
			{
				cnt[v]=(cnt[v]+cnt[u])%mod;
			}
		}
	}
	cout<<cnt[n];
	return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

这是一个很经典的问题，就是最短路计数。正常的最短路 dij 我们是开一个 $dis_x$ 代表到达 $x$ 的最短步数，那么怎么做到计数呢？我们只需要给 $dis$ 开成一个 pair，在计算第一个数的最小值的时候，给另一个数记录这个出现了多少次即可，只用在模板单源最短路上添加对次数的记录即可通过本题。dij 的具体过程就是每次选择最小的距离的点，然后加入队列，相当于 BFS 加上权值，注意，这是优先队列。[link](https://atcoder.jp/contests/abc211/submissions/51773460)。

---

## 作者：highkj (赞：0)

# 前言
~~水一篇题解~~。
# 思路
我们可以很明显的发现这是一个最短路模板，那么我们就可以想一下如何从 $cnt_x$ 转移到 $cnt_{to}$ 这里的 $cnt_i$ 表示从 $1$ 到 $i$ 的最短路径数量而 $to$ 为 $x$ 能到达的点。通过 Dijkstra，我们可以得到以下判断。

- 如果 $dis_x+1<dis_{to}$ 那么我们可以得到既然从 $x\to to$ 这条边最短那么我们就可以得到到 $x$ 的条数就等于到 $to$ 的最短路条数。
- 如果 $dis_x+1=dis_{to}$ 那么我们就可以将原来的条数加上到 $x$ 的条数即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define pb push_back
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define pa pair<int,int>
const int N=2e5+10,mod=1e9+7;
priority_queue<pa,vector<pa>,greater<pa>>q;
int dis[N],vis[N],cnt[N],n,m;
vector<int>v[N];
void dij(int s)  {
	q.push({0,s});
	memset(dis,0x3f,sizeof dis);
	dis[s]=0;
	cnt[s]=1;
	while(q.size()) {
		int x=q.top().second;
		q.pop();
		for(auto to:v[x]) {
			if(dis[to]>1+dis[x]) {
				cnt[to]=cnt[x];
				dis[to]=dis[x]+1;
				q.push({dis[to],to});
			}else if(dis[to]==1+dis[x]) {
				cnt[to]+=cnt[x];
				cnt[to]%=mod;
			}
		}
	}
}
fire main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	in(n),in(m);
	rep(i,1,m) {
		int x,y;
		in(x),in(y);
		v[x].pb(y);
		v[y].pb(x);
	}dij(1);
	cout<<cnt[n]<<endl;
	return false;
}


```

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$
模板最短路计数啊。

堆优化的 dijkstra 大家应该都会，只需要稍微思考一下就能做出来了，先来思考到达一个点时，有两种花费相同的方法时的情况，很显然，直接将两种情况的方案数相加就可以了，而当当前枚举的这种方案比之前的优的时候，则可以直接覆盖。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e6+10;
const int mod=1e9+7;
using namespace std;
int n,m,a,b,e[N],ne[N],h[N],idx=1,dist[N],ans[N];
priority_queue<pii> q;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
void add(int x,int y)
{
	e[idx]=y;
	ne[idx]=h[x];
	h[x]=idx++;
}
void dijkstra()
{
	dist[1]=0;
	ans[1]=1;
	q.push(make_pair(0,1));
	while(!q.empty())
	{
		int t=q.top().y;
		q.pop();
		for(int i=h[t];~i;i=ne[i])
		{
			int to=e[i];
			if(dist[to]>dist[t]+1)//更优
			{
				dist[to]=dist[t]+1;//更新
				ans[to]=ans[t];//覆盖
				q.push(make_pair(-dist[to],to));
			}
			else if(dist[to]==dist[t]+1)//相同的情况
			{
				ans[to]+=ans[t];//直接加上
				ans[to]%=mod;
			}
		}
	}
}
signed main()
{
	memset(h,-1,sizeof h);
	memset(dist,0x3f,sizeof dist);
	n=read();
	m=read();
	rep1(i,1,m)
	{
		a=read();
		b=read();
		add(a,b);
		add(b,a);
	}
	dijkstra();
	cout<<ans[n]<<endl;
	return 0;
}
```

---

## 作者：Slient_QwQ (赞：0)

## 分析
一道显然的最短路，用 dijkstra 算法。

计算最短路的同时，保存最短路个数，如果与当前最短路相同，最短路个数相加，否则到这个节点的最短路个数为上一个节点的最短路个数。

## Accepted Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
const int mod = 1e9 + 7;
struct Edge{
	int v, nxt;
}edge[N * 2];
int head[N], vis[N], cnt;
long long num[N], dis[N];
void add_edge(int u, int v){edge[++cnt] = (Edge){v, head[u]}; head[u] = cnt;}
void dijkstra(int s)
{
    memset(dis, 0x3f3f3f3f, sizeof(dis));
    priority_queue<pair<int, int> > q;
    dis[s] = 0; num[s] = 1;
    q.push(make_pair(0, s));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = edge[i].nxt)
        {
            int v = edge[i].v;
            if (dis[v] < dis[u] + 1)continue;
            if (dis[v] == dis[u] + 1)num[v] += num[u];
            else dis[v] = dis[u] + 1, num[v] = num[u];
            num[v] %= mod;
            q.push(make_pair(-dis[v], v));
        }
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        add_edge(u, v); add_edge(v, u);
    }
    dijkstra(1);
    cout << num[n];
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 题意：

给定一个图，求点 $1$ 到点 $N$ 的最短路径条数。

### 思路：

这道题可以用各种算法踩掉，我选择的是 SPFA 算法。

因为题目要求计数，所以我们开一个 $ans$ 数组表示数量。

分两种情况讨论：

1. 若是 $dis_v>dis_u+1$。

- 最短路被更新了，可以直接 $ans_v=ans_u$ 覆盖。

2. 若是 $dis_v=dis_u+1$。

- 又找到一条最短路，将条数相加即可。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define mod 100003
using namespace std;struct Edge {
    int to,next;
}e[];
int head[],cnt;
inline void adde(int u,int v){
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
} int n,m;
//ans表示最短路条数
int dis[],vis[],ans[];
queue<int>q;//稍加改动的SPFA
inline void SPFA(){
    memset(dis,0x3f,sizeof(dis));
    q.push();
    dis[]=;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=;
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].to;
            if(dis[v]>dis[u]+){
                dis[v]=dis[u]+;
                //最短路转移
                ans[v]=ans[u];
                if(!vis[v]){
                    vis[v]=;
                    q.push(v);
                }
            }else if(dis[v]==dis[u]+){
                //最短路统计
                ans[v]=(ans[v]+ans[u])%mod;
            }
        }
    }
}int main()
{
    cin>>n>>m;
    for(int i=;i<=m;i++){
        int a,b;
        cin>>a>>b;
        adde(a,b);
        adde(b,a);
    }    ans[]=;//记得初始化
    SPFA();    for(int i=;i<=n;i++){
        cout<<ans[i]<<endl;
    }    return ;
}
```


---

## 作者：loser_seele (赞：0)

这题重了，原题是 [P1144](https://www.luogu.com.cn/problem/P1144)。详细的解答可以看这题的题解，这里只提供较简略的思路。

类似 dijkstra 的思路，在每次更新最短路长度的时候对每个节点记录一个当前方案数，记录每个节点的前缀，如果当前距离长度和最短路相等则累加答案，否则用它的前缀的方案数替换它即可，这样即可统计出所有最短路的个数。

时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。注意判断重边和自环，以及模数不同，如果直接套用原题的代码可能会超过 int 能表示的数据范围，所以需要用 long long 来解决。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2000005;
int h[N],e[N],ne[N],idx;
int n,m;
int dist[N],dis[N];
int st[N];
typedef pair <int,int> PII;
void add(int a,int b)
{
    e[idx]=b;
    ne[idx]=h[a];
    h[a]=idx++;
}
void dijkstra()
{
    memset(dist,0x3f,sizeof dist);
    priority_queue<PII , vector<PII>, greater<PII>> heap;
    heap.push({0,1});
    dist[1]=0;
    dis[1]=1;
    while(heap.size())
    {
        auto t=heap.top();
        int ver=t.second;
        heap.pop(); 
        if(st[ver]) continue;
        st[ver]=true;
        for(int i=h[ver];i!=-1;i=ne[i])
        {
            int j=e[i];
            if(dist[j]>dist[ver]+1)
            {
                dist[j]=dist[ver]+1;
                heap.push({dist[j],j});
                dis[j]=dis[ver];
                dis[j]=dis[j]%100003;
            }
            else if(dist[j]==dist[ver]+1)
            {
                dis[j]+=dis[ver];
                dis[j]=dis[j]%100003;
            }
        }

    }
}
int main()
{
    cin>>n>>m;
    memset(h,-1,sizeof h);
    while(m--)
    {
        int a,b;
        cin>>a>>b;
        add(a,b);
        add(b,a);
    }
    dijkstra();
    for(int i=1;i<=n;i++)
    printf("%d\n",dis[i]);
}
```


---

