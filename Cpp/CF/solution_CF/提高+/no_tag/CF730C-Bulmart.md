# Bulmart

## 题目描述

Berland 的一股新的商业力量正在崛起。作为铲子领域的新兴贸易巨头，Bulmart 准备主宰这一市场！如今，几乎每个 Berland 城市都有 Bulmart 商店，有些城市甚至有多家。唯一的问题是，当前的销售额……远低于预期。一些人认为，铲子零售市场的规模过小，大公司难以从中获益。但公司管理层对市场的未来充满信心，正在寻找提升收入的新方法。

Berland 有 $ n $ 座城市，通过 $ m $ 条双向道路相连。所有道路的长度都相同。可能出现某些城市之间无法通过道路直接到达的情况。没有一条道路连接同一个城市，任意两个城市之间最多只有一条道路。

Berland 有 $ w $ 家 Bulmart 商店。每家商店信息包括：

- $ c_{i} $ — 第 $ i $ 家商店所在城市的编号（一个城市可能没有商店，也可能有多个），
- $ k_{i} $ — 第 $ i $ 家商店的铲子数量，
- $ p_{i} $ — 第 $ i $ 家商店中每把铲子的价格（以 burles 为单位）。

Bulmart 管理层最新的想法是开发一个程序，帮助顾客在预算内快捷地购买到铲子。具体来说，该程序需要找到在不超过 $ a_{j} $ burles 的总预算下，将 $ r_{j} $ 把铲子运送到城市 $ g_{j} $ 的顾客的手中所需的最短时间。任意两个相邻城市之间的运送时间是 $ 1 $。如果铲子是从多个城市运送来的，运送时间即为最后一批货物到达的时间。运送过程是免费的。

程序需要处理 $ q $ 个独立的查询。每个查询独立计算，一次查询不会影响后续查询中的商店库存。

## 样例 #1

### 输入

```
6 4
4 2
5 4
1 2
3 2
2
4 1 2
3 2 3
6
1 2 6
2 3 7
3 1 2
4 3 8
5 2 5
6 1 10
```

### 输出

```
2
-1
2
2
3
-1
```

# 题解

## 作者：Soul_Love (赞：3)

### 简要题意

有一个 $n$ 个点，$m$ 条边的无向图。在这个图上有 $w$ 个商店，它们分布在若干个点上，每个点上可能有多个商店，也有可能没有商店。每个商店都只卖一种商品，第 $i$ 个商店位于第 $c_i$ 个点，所拥有的商品数量为 $k_i$，单价为 $p_i$。

$q$ 次询问，对于第 $i$ 次询问，问从商店中买 $r_i$ 个商品送到第 $g_i$ 个点所需要的最少时间，并且要求花费不超过 $a_i$。

商品运输没有花费，商品每运输过一条边要一个单位的时间，商品是同时运输的。

### 暴力

容易发现，每一套运输方案的所需时间只与离 $r_i$ 最远的商店与 $r_i$ 的距离决定的，看到这经典的“最大的最小”，而且时间上限大的最优方案肯定不会比时间上限小的最优方案劣，所以直接上二分。

二分一个时间 $t$ 后，相当于在离 $r_i$ 的距离不超过 $t$ 的所有商店中选一部分，满足费用不超过 $a_i$。

考虑贪心，优先选单价低的。

于是代码就成型了。

因为是边权为 $1$ 的最短路，对于每次询问，二分完后，都对 $r_i$ 跑一遍 $\operatorname {bfs}$，把能跑到的商店存下来，然后跑一遍 $\operatorname {sort}$，检验答案就可以了。

```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,l,h[50100],q,x,y,z,num[5010],vis[5010],dis[5010];
inline int read()
{
	int k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
struct edge
{
	int v,next;
}e[100100];
struct shop
{
	int cost,num;
}sh[5010][5010],ss[5010];
inline void add(int x,int y)
{
	e[++l].v=y;
	e[l].next=h[x];
	h[x]=l;
}
inline bool cmp(shop x,shop y)
{
	return x.cost<y.cost;
}
inline bool check(int x,int y,int z,int t)//数量要求，目的地，花费上限，时间上限 
{
	memset(vis,0,sizeof(vis));
	int cnt=0;
	queue<int>q;
	while(!q.empty()) q.pop();
	q.push(y);
	vis[y]=1;
	dis[y]=0;
    for(int i=1;i<=num[y];i++) ss[++cnt]=sh[y][i];
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(dis[u]==t) continue;//限制
		for(int i=h[u];i;i=e[i].next)
		{
			if(!vis[e[i].v])
			{
				vis[e[i].v]=1;
				dis[e[i].v]=dis[u]+1;
				q.push(e[i].v);
				for(int j=1;j<=num[e[i].v];j++) ss[++cnt]=sh[e[i].v][j];
			}
		}
	}
	sort(ss+1,ss+cnt+1,cmp);
	int c=0;
	for(int i=1;i<=cnt;i++)
	{
		if(x>ss[i].num)//特判能否直接买光这个商店
		{
			x-=ss[i].num;
			c+=ss[i].cost*ss[i].num;
		}
		else
		{
			c+=ss[i].cost*x;
			x=0;
			break;
		}
	}
	if(x>0||c>z) return 0;
	return 1;
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	k=read();
	for(int i=1;i<=k;i++)
	{
		x=read(),y=read(),z=read();//所在的城市，数量，单价 
		sh[x][++num[x]].cost=z;//num[i]为点i的商店数量
		sh[x][num[x]].num=y;
	}
	q=read();
	while(q--)
	{
		y=read(),x=read(),z=read();//目的地，数量要求，花费上限 
		int l=0,r=n,s=-1;
		while(l<=r)//二分时间，等价于距离
		{
			int mid=(l+r)>>1;
			if(check(x,y,z,mid))
			{
				s=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		printf("%lld\n",s);
	}
	return 0;
}
```

时间复杂度 $O(q \operatorname {log}n(n+w \operatorname{log}w))$。

~~确实有点极限~~

T 飞了。

### 优化

[大佬](https://www.luogu.com.cn/user/522067)说暴力优化一下就能 A。

看一下复杂度瓶颈，似乎在快排。

所以考虑预处理，一开始先把所有商店都 $\operatorname {sort}$ 一遍，所有点都 $\operatorname {bfs}$ 一遍，处理出点两两之间的距离。

二分时，跑一遍所有商店，判一下距离，根据贪心，前面的合法的商店优先取。

```c
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
int n,m,k,l,h[50100],qq,x,y,z,vis[5010],dis[5010][5010];
inline int read()
{
	int k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
struct edge
{
	int v,next;
}e[100100];
struct shop
{
	int cost,num,pos;
}ss[5010];
inline void add(int x,int y)
{
	e[++l].v=y;
	e[l].next=h[x];
	h[x]=l;
}
inline bool cmp(shop x,shop y)
{
	return x.cost<y.cost;
}
inline void bfs(int y)
{
	memset(vis,0,sizeof(vis));
	queue<int>q;
	while(!q.empty()) q.pop();
	q.push(y);
	vis[y]=1;
	dis[y][y]=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=h[u];i;i=e[i].next)
		{
			if(!vis[e[i].v])
			{
				vis[e[i].v]=1;
				dis[e[i].v][y]=dis[y][e[i].v]=dis[y][u]+1;
				q.push(e[i].v);
			}
		}
	}
}
inline bool check(int x,int y,int z,int kk)//数量要求，目的地，花费上限，时间上限
{
	for(int i=1;i<=k;i++)
	{
		if(dis[y][ss[i].pos]<=kk)
		{
			if(x<ss[i].num)
			{
				z-=x*ss[i].cost;
				x=0;
				break;
			}
			else
			{
				z-=ss[i].cost*ss[i].num;
				x-=ss[i].num;
			}
			if(z<0) break;
		}
	}
	if(x==0&&z>=0) return 1;
	return 0;
}
signed main()
{
	memset(dis,inf,sizeof(dis));
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++) bfs(i);
	k=read();
	for(int i=1;i<=k;i++)
	{
		ss[i].pos=read(),ss[i].num=read(),ss[i].cost=read();//所在的城市，数量，单价 
	}
	sort(ss+1,ss+k+1,cmp);
	qq=read();
	while(qq--)
	{
		y=read(),x=read(),z=read();//目的地，数量要求，花费上限 
		int l=0,r=n,s=-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(check(x,y,z,mid))
			{
				s=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		printf("%lld\n",s);
	}
	return 0;
}
```

注释都打暴力代码里了。

时间复杂度 $O(n^2+w \operatorname {log}w+qw \operatorname {log}n)$。

---

## 作者：___QAQ__ (赞：0)

# 题意
给定一个 $N$ 个点 $M$ 条边的无向图，其中 $c_i$ 个点上有第 $i$ 个超市，总共 $w$ 个超市。每个超市有 $k_i$ 个铲子且单价为 $p_i$ 元。

给定 $q$ 次询问，每次询问给定 $r_i,g_i,a_i$，求将 $r_i$ 个铲子送到第 $g_i$ 个城市的最短时间，且花费不超过 $a_i$，若无解输出 $-1$。任何两个相邻城市之间的送货时间等于 $1$。
# 思路
1. 存在单调关系：距离越远，包含的商店越多，可以买到的铲子越多，价格越便宜。
2. 考虑二分答案，然后贪心求距离内可买到铲子的最小价格 $a$。
3. 注意事项：贪心时只需对铲子处理一次即可。

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXW = 5e3 + 1, MAXN = 5e3 + 1;

struct Node{
  int c;
  ll k, p;
  bool operator<(const Node &i) const{
    return p < i.p;
  }
}s[MAXW];

int n, m, x, y, w, q, g, r, a, v[MAXN];

vector<int> h[MAXN];

void bfs(int x, int u){
  queue<int> q;
  q.push(u);
  v[u] = 0;
  while(!q.empty()){
    int cur = q.front();
    q.pop();
    if(v[cur] == x){
      continue;
    }
    for(const auto &it : h[cur]){
      if(v[it] != -1){
        continue;
      }
      q.push(it);
      v[it] = v[cur] + 1;
    }
  }
}

bool f(int x, int g, ll c, ll a){
  fill(v + 1, v + 1 + n, -1);
  bfs(x, g);
  for(int i = 1; i <= w; i++){
    if(v[s[i].c] != -1){
      a -= min(c, s[i].k) * s[i].p;
      c -= min(c, s[i].k);
    }
    if(a < 0){
      break;
    }
  }
  if(c){
    return 0;
  }
  return a >= 0;
}

int F(int g, ll c, ll a){
  int l = 0, r = n;
  while(l < r){
    int mid = (l + r) >> 1;
    f(mid, g, c, a) ? r = mid : l = mid + 1;
  }
  return (!f(l, g, c, a) ? -1 : l);
}

void Solve(){
  cin >> g >> r >> a;
  cout << F(g, r, a) << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for(int i = 1; i <= m; i++){
    cin >> x >> y;
    h[x].push_back(y);
    h[y].push_back(x);
  }
  cin >> w;
  for(int i = 1; i <= w; i++){
    cin >> s[i].c >> s[i].k >> s[i].p;
  }
  sort(s + 1, s + 1 + w);
  cin >> q;
  while(q--){
    Solve();
  }
  return 0;
}
```
# 复杂度
时间复杂度：$O(q\log n(n +m + w))$。

时限刚好 $1.5$ 秒，可以过。

---

