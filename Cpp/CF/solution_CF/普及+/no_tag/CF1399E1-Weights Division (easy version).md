# Weights Division (easy version)

## 题目描述

简单版本和困难版本是两个完全不同的问题，因此我们建议：两题的题面都要仔细阅读。

给定一棵以 $1$ 号点为根的带权有根树。

树是一个无环连通图。有根树有一个被称作根的特殊节点。在从根到节点 $v$ 的路径上，最后一个不同于 $v$ 的节点被称作节点 $v$ 的父亲节点。以节点 $v$ 为父亲的节点称为节点 $v$ 的儿子节点。若一个节点没有任何儿子，则称它为叶子节点。带权树上的边带有权值。

定义一条路径的权值为这条路径上所有边的权值之和。特别地，一条从某个节点到它自己的路径权值为 $0$。

你可以进行一系列的操作，操作零次或多次。对于每次操作，你可以选择任意一条边，将其权值除以 $2$（向下取整）。更正式地说，在每次操作中，你可以选择一条边 $i$，使得这条边的权值 $w_i$ 变成 $\lfloor \frac{w_i}{2} \rfloor$。

你的任务是找到最小操作数，以满足所有从根到叶子的路径的权值之和不超过 $S$。换句话说，如果设 $w(i,j)$ 为从节点 $i$ 到节点 $j$ 的路径的权值，那么你需要使得 $\sum_{v \in leaves} w(root,v) \leq S$，其中 $leaves$ 是所有叶子组成的集合。

你需要回答 $t$ 组独立的数据。

## 样例 #1

### 输入

```
3
3 20
2 1 8
3 1 7
5 50
1 3 100
1 5 10
2 3 123
5 4 55
2 100
1 2 409```

### 输出

```
0
8
3```

# 题解

## 作者：HoshizoraZ (赞：10)

印象深刻的一道题。

------------

**题意描述：**

在一棵 $n$ 个节点、根为 $1$ 号点的树上，每一条边都有边权。

每次操作可以使一条边的边权除以 $2$ 并下取整，问最少操作多少次可以让点 $1$ 到各个叶子结点的距离和不超过 $S$。

------------

首先，很容易想到一个贪心策略：哪条边当前的**边权 × 该边出现次数**最大，就优先让这条边的边权除以 $2$。

但是这个策略有漏洞，做法需要进行修改。

**第一步：求出点 $1$ 到各个叶子结点的路径中，每条边出现的次数。**

有一个显而易见的结论：一个点的出现次数，等于这个点到达它的父亲，经过的边的出现次数。

而题目一开始就说了 $1$ 号点是根，所以从 $1$ 号点开始 dfs，把每条边的边权信息存到较深的节点就可以了（边权也需要传）。

**第二步：每次操作时，找到当前影响最大的边，并将其边权除以 $2$ 下取整，直到距离总和小于 $S$。**

这步也不难，我们可以拿一个堆（或 **set** 什么的都可以），每次只需要 $\log$ 级别的复杂度就可以添加、删除节点。

为了判断距离总和是否小于 $S$，需要做：

- 操作前算出所有的**边权 × 该边出现次数**之和，命名为 $S_0$。

- 假设当前优先级最大边的边权为 $w$，出现次数为 $c$，那么做一次操作之后，$S_0\leftarrow S_0 - \left(w - \lfloor \frac{w}{2}\rfloor\right) \times c$。

如果使用的是堆，我们就需要设计它的优先级，为此我曾设计过两种做法：

- 第一种（**非正确做法**）：把当前**边权 × 该边出现次数**最大的边找出来，边权变为 $\frac{\text{边权 * 该边出现次数}}{2}$ 

**这个做法的反例如下**：

```cpp
边权      出现次数
 53          2
 15          7
```
虽然 $53 \times 2 > 15 \times 7$，但是 $\left(53-\lfloor\frac{53}{2}\rfloor\right) \times 2 < \left(15-\lfloor\frac{15}{2}\rfloor\right) \times 7$，明显后者可以减小的数更大，即操作后作用越大，所以这个做法是错误的。

- 第二种做法（**正确做法**）：**优先级判定应该是，选出当前最大的**

$$\left(\text{边权}-\lfloor\frac{\text{边权}}{2}\rfloor\right)\times \text{出现次数}$$

然后，将 **边权**（注意除法和出现次数无关，不要拿乘积作除法） 除以 $2$ 下取整。

然后程序的主体内容就结束了，剩下的就没什么难度了。

------------

**复杂度分析**

对于每组数据（因为 $\sum n \le 10^5$，所以没有影响），我们有 $n$ 个数塞进堆里。

因为每次操作都是将数字除以 $2$ 下取整，所以把数 $a$ 变为 0 的操作次数只有 $\log$ 级别。

当所有数字变为 $0$，距离和就一定不超过 $S$（$S$ 是正整数）。

所以最多在堆内操作 $n \log w$ 次。

故复杂度就是 $O((n \log w) \log \ (n \log w))$，在 $3$ 秒时间限制下是可以通过的。

------------

**代码**

```cpp
#include <cstdio>
#include <queue>
#define N 100010
typedef long long ll;
using namespace std;
 
struct Edge{
    int to, nxt;
    ll val;
}e[N << 1];
int t, n, fir[N], ans, cnt;
ll S, s[N], sum[N], W[N], l, r, SS;
 
struct P{
    int id;                             // 这里设 id 是为了方便查找边的出现次数 
    ll val;
};
priority_queue <P> q;                   // 优先队列 

bool operator < (P a, P b){             // 判断优先级 
    return (a.val - a.val / 2) * s[a.id] < (b.val - b.val / 2) * s[b.id];
}
 
inline void add(int x, int y, ll z){    // 建边 
    e[++cnt].to = y;
    e[cnt].nxt = fir[x];
    e[cnt].val = z;
    fir[x] = cnt;
}
 
ll dfs(int x, int fa){                  // 统计每条边出现次数、以及和边权的乘积 
    ll ss = 0;
    bool bb = 0;
    for(int i = fir[x], y; i; i = e[i].nxt){
        y = e[i].to;
        if(y == fa) continue;           // 对于每次搜索不要返回去搜索父亲，不然死循环 
        bb = 1;                         // 确定这不是叶子节点 
        ss += dfs(y, x);
        W[y] = e[i].val;                // 把边的信息化成点的信息，方便之后统计 
        sum[y] = s[y] * e[i].val;		
    }
    if(!bb) return s[x] = 1;            // 是叶子节点就要把自己信息带上去 
    else return s[x] = ss;              // 不然只需搬运下面的节点的信息 
}

void CLEAR(){
    for(int i = 1; i <= n; i++)
        fir[i] = s[i] = sum[i] = W[i] = 0;
    while(!q.empty())                   // 优先队列清空 
        q.pop();
}
 
int main(){
 
    scanf("%d", &t);
    while(t--){
        scanf("%d %lld", &n, &S);
        cnt = ans = 0, SS = 0;
        for(int i = 1, u, v; i < n; i++){
            ll w;
            scanf("%d %d %lld", &u, &v, &w);
            add(u, v, w), add(v, u, w);
        }
        dfs(1, 0);
        for(int i = 2; i <= n; i++)                 // 从 2 开始，因为 1 没有通往父亲的边 
            q.push((P){i, W[i]}), SS += sum[i];
        int xx;
        ll yy;
        while(SS > S){                              // 一直操作直到结束 
            xx = q.top().id, yy = q.top().val;
            q.pop(), ++ans;                         // 答案累加 
            SS -= yy * s[xx] - (yy / 2) * s[xx];    // 减小的量 
            q.push((P){xx, yy / 2});
        }
        CLEAR();                                    // 初始化 
        printf("%d\n", ans);
    }
 
    return 0;
}
```

---

## 作者：AbsMatt (赞：2)

### [题目传送器](https://www.luogu.com.cn/problem/CF1399E1)

### [Hard Version](https://www.luogu.com.cn/problem/CF1399E2)

### [更爽的阅读体验](https://www.luogu.com.cn/blog/yaohaoyou/solution-cf1399e1)

### [Hard Version solution](https://www.luogu.com.cn/blog/yaohaoyou/solution-cf1399e2)

### CF 2000

## 题意
翻译讲的很清楚了，这里就不多展开了。

## 做法
首先可以用**树形 DP** 求出每条边的代价系数，设 $dp_i$ 表示 $i$ 的子树中有多少个叶子节点，不难得出
$dp_u = \begin{cases}\sum dp_{son} & u \ne leaf \\ 1 & u=leaf \end{cases}$。

设一条边的代价系数为 $s_i$，当这棵树以 $1$ 为根时的儿子为 $v$，则 $s_i=dp_v$。

由于每条边的代价相同，则理所应当考虑贪心，每次选择当前能产生最大贡献的边进行操作。使用大根堆，每次按贡献排序即可。

时间复杂度为 $O(n\times \log_2n)$，开 long long。
### [AC Code](https://codeforces.com/contest/1399/submission/239955281)

---

## 作者：do_while_true (赞：1)

dfs 预处理出每条边下的子树的叶子节点个数，就能算出如果修改这条边会对总和产生的影响大小。把修改当前边对总和的贡献为优先级放进优先队列中，贪心修改即可。

代码有些长，不过实现方法和思路还是很简单的。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#define ll long long
#define int long long
inline ll read() {
	int r=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		r=(r<<3)+(r<<1)+(ch^48);
		ch=getchar();
	}
	return r*w;
}
const int N=200010;
struct node {
	int to,next;
	ll val;
} e[N<<1];//原始的边
struct Node {
	ll va,si;
	bool f;
	bool operator < (const Node & x) const {
		return va*si-(va/2*si)<x.va*x.si-(x.va/2*x.si);
	}
} E[N<<1],xx;//要放入优先队列的边
std::priority_queue<Node>que;
int n,cnt,size[N],head[N];
ll S,sum,ans;
void dfs(int x,int fa) {
	int son=0;
	for(int i=head[x]; i; i=e[i].next) {
		if(e[i].to==fa) {
			E[i].f=1;
			continue ;
		}
		son++;
		dfs(e[i].to,x);
		size[x]+=size[e[i].to];
	}
	for(int i=head[x]; i; i=e[i].next) {
		if(e[i].to==fa) continue;
		E[i].si=size[e[i].to];//该边下有几个叶子节点
	}
	if(son==0) size[x]=1;//标记为叶子节点
}
void add() {
	int x=read(),y=read();
	ll z=read();
	e[++cnt].next=head[x];
	e[cnt].to=y;
	E[cnt].va=e[cnt].val=z;
	head[x]=cnt;
	e[++cnt].next=head[y];
	e[cnt].to=x;
	E[cnt].va=e[cnt].val=z;
	head[y]=cnt;
}
signed main() {
	int T;
	T=read();
	while(T--) {
		n=read();
		S=read();
		ans=0;
		sum=0;
		cnt=0;
		while(!que.empty())
			que.pop();
		for(int i=1; i<=n; i++)
			size[i]=head[i]=0;
		for(int i=1; i<n; i++)
			add();
		dfs(1,-1);
		for(int i=1; i<=cnt; i++) {
			if(E[i].f) continue;
			sum+=E[i].va*E[i].si;
			que.push(E[i]);
		}
		while(sum>S) {
			xx=que.top();
			que.pop();
			sum-=xx.si*xx.va;
			xx.va=xx.va/2;
			sum+=xx.si*xx.va;
			que.push(xx);
			ans++;
		}
		for(int i=1; i<=cnt; i++)
			E[i].f=E[i].si=E[i].va=e[i].to=e[i].next=e[i].val=0;
		printf("%lld\n",ans);
	}
}
```


---

## 作者：dead_X (赞：1)

## 题意 
给定一棵树，边带权，每一次可以将一条边的权值除以 $2$ 并向下取整，问要使所有叶子到根的距离和不超过 $S$ 的最小操作次数。
## 思路
注意到操作次数不会超过 $nlogw$ 次，即每条边最多 $logw$ 次后就会变成 $0$ 。

所以我们可以暴力用 $set$ 维护最优决策。

先 $dfs$ 出每条边经过了几遍，然后全部放入 $set$ 里，$set$ 根据将这条边除以 $2$ 后距离和减小的值排序，每次取出最优解，执行操作后再放回 $set$ 中，当满足要求时退出并输出答案。

~~恭喜你，喜提 $\red{\text{Wrong answer on pretest 2}}$~~

记得开 $multiset$ 避免两个优先级相同的解被吞了一个。
## 代码
```cpp
#include<bits/stdc++.h>
#define qwq int T=read(); while(T--)
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline long long readll(){
   long long s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int to[1000003],nxt[1000003],head[1000003],val[1000003],t[1000003],cnt=0;
int d[1000003];
struct cmp  
{  
    bool operator ()(const pair<int,int> &a, const pair<int,int> &b)  
    {  
        if(1LL*(a.first-(a.first/2))*a.second!=1LL*(b.first-(b.first/2))*b.second) return 1LL*(a.first-(a.first/2))*a.second>1LL*(b.first-(b.first/2))*b.second; 
		return a.first>b.first; 
    }  
};  
void dfs(int x,int fa,int from)
{
	if(d[x]==1 && x!=1) 
	{
		t[from]=1;
		return ;
	}
	for(int i=head[x]; i; i=nxt[i]) if(to[i]!=fa)
	{
		dfs(to[i],x,i);
		t[from]+=t[i];
	}
	return ;
}
multiset<pair<int,int>,cmp> s;
int main()
{
	qwq
	{
		s.clear(),cnt=0;
		int n=read(),ans=0;
		int m=(n-1)<<1;
		for(int i=1; i<=n; i++) head[i]=0,d[i]=0;
		for(int i=1; i<=m; i++) t[i]=0;
		long long S=-readll(); 
		for(int i=1; i<n; i++) 
		{
			int u=read(),v=read(),w=read();
			to[++cnt]=v,val[cnt]=w,nxt[cnt]=head[u],head[u]=cnt;
			to[++cnt]=u,val[cnt]=w,nxt[cnt]=head[v],head[v]=cnt;
			d[u]++,d[v]++;
		}
		dfs(1,1,0);
		for(int i=1; i<=m; i++) if(t[i]) S+=1LL*val[i]*t[i],s.insert(make_pair(val[i],t[i]));
		while(S>0)
		{
			if(s.empty()) break;
			pair<int,int> tmp=*s.begin();
			s.erase(s.begin());
			S-=1LL*(tmp.first-(tmp.first/2))*tmp.second;
			tmp.first/=2;
			if(tmp.first) s.insert(tmp);
			++ans;
		}
		printf("%d\n",ans);
	}
    return 0;
}
//By dead_X
```

---

## 作者：45dino (赞：1)

这一题比 hard version 简单了不止一点啊喂，为什么 hard version 还是蓝QAQ。

发现边与边是**独立**的，即改变这一条边对答案的影响只和这一条边有关，是 $(v-\lfloor \frac v 2\rfloor)\times p$ （v 指当前的边权，p 指有多少条从根到叶子的路径经过这一条边）

先用一遍 dfs 预处理出 p，再利用**优先队列**算操作那些边收益最大。

复杂度大概是 $\Theta(n \log n)$ 。~~其实我也不确定，能过就是了~~

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int to,next,val,popu;
} edge[199999];
struct que{
	int val,popu;
	bool operator<(const que &x)const
	{
		return (val-val/2)*popu<(x.val-x.val/2)*x.popu;
	}
};
int t,n,s,ans,cnt,sum,head[100001];
priority_queue<que> q;
void add(int x,int y,int z)
{
	edge[++cnt].to=y;
	edge[cnt].val=z;
	edge[cnt].next=head[x];
	edge[cnt].popu=0;
	head[x]=cnt;
}
int dfs(int x,int fa)
{
	int tot=0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
		{
			edge[i].popu=dfs(edge[i].to,x);
			q.push((que){edge[i].val,edge[i].popu});
			sum+=edge[i].val*edge[i].popu;
			tot+=edge[i].popu;
		}
	tot=max(tot,1ll);
	return tot;
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld %lld",&n,&s);
		ans=cnt=sum=0;
		while(!q.empty())
			q.pop();
		memset(head,0,sizeof(head));
		for(int i=1;i<n;i++)
		{
			int a,b,c;
			scanf("%lld %lld %lld",&a,&b,&c);
			add(a,b,c);
			add(b,a,c);
		}
		dfs(1,0);
		while(sum>s)
		{
			que f=q.top();
			q.pop();
			sum-=(f.val-f.val/2)*f.popu;
			f.val/=2;
			q.push(f);
			ans++;
		}
		cout<<ans<<endl;
	}
}
```


---

## 作者：JOKER_chu (赞：0)

### 题意

以下 $dis_{i,j}$ 表示点 $i$ 与点 $j$ 的距离，$leaves$ 表示这棵树的叶子节点。

给定一棵以 $1$ 为根的有根树，你可以进行任意次操作，每次操作都可以选择一条边并将这条边的权值 $w$ 变为 $\lfloor \frac{w}{2} \rfloor$，可以对一条边操作多次。

请你求出最少的操作次数使得 $\sum_{u \in leaves} dis_{1,u} \leq S$。

### 解法

先求出 $\sum_{u \in leaves} dis_{1,u}$，然后将对答案贡献最大的边操作，直到满足答案限制。

每条边对答案的贡献为该点子树内**叶子**的数量 $\times w$，$w$ 表示这条边的边权。显然的 `priority_queue` 维护边的贡献，大根堆维护即可。

### 代码

```cpp
#include <iostream>

#include <vector>

#include <climits>

#include <queue>

#include <algorithm>

#define endl '\n'

#define int long long

using namespace std;

const int N = 2e5 + 5;

struct Node{
  int x, c;
  bool operator<(const Node &i) const {
    return c > i.c;
  }
};

struct Edge{
  int x, c;
};

int t, n, s, dis[N], dp[N];
bool v[N];

struct edge{
  int x, y, c;
  bool operator<(const edge &i) const {
    return (c - ( c >> 1 )) * min(dp[x], dp[y]) < (i.c - ( i.c >> 1 )) * min(dp[i.x], dp[i.y]);
  }
}a[N];

priority_queue<edge>e;
vector<Edge>g[N];

void Dijkstra(int s){
  priority_queue<Node>que;
  dis[s] = 0;
  que.push({s, 0});
  while(!que.empty()){
    Node u = que.top();
    que.pop();
    if(v[u.x] == 1) continue;
    v[u.x] = 1;
    for(auto to : g[u.x]){
      if(dis[u.x] + to.c < dis[to.x]){
        dis[to.x] = dis[u.x] + to.c;
        que.push({to.x, dis[to.x]});
      }
    }
  }
}

void dfs(int x, int fa){
  if(g[x].size() == 1) dp[x] = 1;
  for(auto to : g[x]){
    if(to.x == fa) continue;
    dfs(to.x, x);
    dp[x] += dp[to.x];
  }
}

void solve(){
  cin >> n >> s;
  while(!e.empty()) e.pop();
  for(int i = 1; i <= n; ++i) g[i].clear(), dis[i] = LLONG_MAX >> 1, v[i] = dp[i] = 0;
  for(int i = 1, x, y, c; i < n; ++i){
    cin >> x >> y >> c;
    g[x].push_back({y, c}), g[y].push_back({x, c});
    a[i] = {x, y, c};
  }
  Dijkstra(1), dfs(1, 0);
  for(int i = 1; i < n; ++i) e.push(a[i]);
  int ans = 0, tans = 0;
  for(int i = 1; i <= n; ++i){
    if(g[i].size() == 1){
      ans += dis[i];
    }
  }
  while(ans > s){
    edge u = e.top();
    e.pop();
    int i = u.c;
    u.c /= 2;
    ans -= (i - u.c) * min(dp[u.x], dp[u.y]);
    tans++;
    e.push(u);
  }
  cout << tans << endl;
}

signed main(){
  cin >> t;
  while(t--) solve();
  return 0;
}

```

代码内的小丑行为：

**树上两点距离使用 `dijkstra`**。

~~完~~

---

