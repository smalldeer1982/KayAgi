# Pokémon Arena

## 题目描述

You are at a dueling arena. You also possess $ n $ Pokémons. Initially, only the $ 1 $ -st Pokémon is standing in the arena.

Each Pokémon has $ m $ attributes. The $ j $ -th attribute of the $ i $ -th Pokémon is $ a_{i,j} $ . Each Pokémon also has a cost to be hired: the $ i $ -th Pokémon's cost is $ c_i $ .

You want to have the $ n $ -th Pokémon stand in the arena. To do that, you can perform the following two types of operations any number of times in any order:

- Choose three integers $ i $ , $ j $ , $ k $ ( $ 1 \le i \le n $ , $ 1 \le j \le m $ , $ k > 0 $ ), increase $ a_{i,j} $ by $ k $ permanently. The cost of this operation is $ k $ .
- Choose two integers $ i $ , $ j $ ( $ 1 \le i \le n $ , $ 1 \le j \le m $ ) and hire the $ i $ -th Pokémon to duel with the current Pokémon in the arena based on the $ j $ -th attribute. The $ i $ -th Pokémon will win if $ a_{i,j} $ is greater than or equal to the $ j $ -th attribute of the current Pokémon in the arena (otherwise, it will lose). After the duel, only the winner will stand in the arena. The cost of this operation is $ c_i $ .

Find the minimum cost you need to pay to have the $ n $ -th Pokémon stand in the arena.

## 说明/提示

In the first test case, the attribute array of the $ 1 $ -st Pokémon (which is standing in the arena initially) is $ [2,9,9] $ .

In the first operation, you can choose $ i=3 $ , $ j=1 $ , $ k=1 $ , and increase $ a_{3,1} $ by $ 1 $ permanently. Now the attribute array of the $ 3 $ -rd Pokémon is $ [2,2,1] $ . The cost of this operation is $ k = 1 $ .

In the second operation, you can choose $ i=3 $ , $ j=1 $ , and hire the $ 3 $ -rd Pokémon to duel with the current Pokémon in the arena based on the $ 1 $ -st attribute. Since $ a_{i,j}=a_{3,1}=2 \ge 2=a_{1,1} $ , the $ 3 $ -rd Pokémon will win. The cost of this operation is $ c_3 = 1 $ .

Thus, we have made the $ 3 $ -rd Pokémon stand in the arena within the cost of $ 2 $ . It can be proven that $ 2 $ is minimum possible.

In the second test case, the attribute array of the $ 1 $ -st Pokémon in the arena is $ [9,9,9] $ .

In the first operation, you can choose $ i=2 $ , $ j=3 $ , $ k=2 $ , and increase $ a_{2,3} $ by $ 2 $ permanently. Now the attribute array of the $ 2 $ -nd Pokémon is $ [6,1,9] $ . The cost of this operation is $ k = 2 $ .

In the second operation, you can choose $ i=2 $ , $ j=3 $ , and hire the $ 2 $ -nd Pokémon to duel with the current Pokémon in the arena based on the $ 3 $ -rd attribute. Since $ a_{i,j}=a_{2,3}=9 \ge 9=a_{1,3} $ , the $ 2 $ -nd Pokémon will win. The cost of this operation is $ c_2 = 3 $ .

In the third operation, you can choose $ i=3 $ , $ j=2 $ , and hire the $ 3 $ -rd Pokémon to duel with the current Pokémon in the arena based on the $ 2 $ -nd attribute. Since $ a_{i,j}=a_{1,2}=2 \ge 1=a_{2,2} $ , the $ 3 $ -rd Pokémon can win. The cost of this operation is $ c_3 = 1 $ .

Thus, we have made the $ 3 $ -rd Pokémon stand in the arena within the cost of $ 6 $ . It can be proven that $ 6 $ is minimum possible.

## 样例 #1

### 输入

```
4
3 3
2 3 1
2 9 9
6 1 7
1 2 1
3 3
2 3 1
9 9 9
6 1 7
1 2 1
4 2
2 8 3 5
18 24
17 10
1 10
1 1
6 3
21412674 3212925 172015806 250849370 306960171 333018900
950000001 950000001 950000001
821757276 783362401 760000001
570000001 700246226 600757652
380000001 423513575 474035234
315201473 300580025 287023445
1 1 1```

### 输出

```
2
6
17
1224474550```

# 题解

## 作者：LKY928261 (赞：14)

有个较为显然的结论：

- 任意最优方案中，相邻两次 2 操作中的 $j$ 不同。

> 证明：假设相邻两次操作中，先用 $y$ 的 $i$ 属性打败了 $x$，再用 $z$ 的 $i$ 属性打败了 $y$，那么直接用 $z$ 的 $i$ 属性打败 $x$ 可以节省 $c_y$ 的雇佣费，并且后者所需要提升的能力值不多于前者，即后者一定更优。

于是用 $y$ 的 $i$ 属性打败 $x$ 所需提升的能力值永远是 $\max(0,a_{y,i}-a_{x,i})$，因为根据结论 $a_{x,i}$ 不会在前面的操作中被修改。

先直接建出图。图上点 $x$ 的权值为雇佣费 $c_x$。从点 $x$ 向点 $y$ 连 $m$ 条有向边，其中第 $i$ 条的边权为 $\max(0,a_{y,i}-a_{x,i})$。一条 $1$ 到 $n$ 的路径长度为路径上边权与除 $c_1$ 外所有点权的总和。于是原题就转化成了一个最短路问题。

带着点权做并不方便。可以考虑将一个点拆成入点和出点，从入点向出点连权值为 $c_x$ 的边。这样就把点权转成了边权。

直接这样做有 $\Theta(n^2m)$ 条边，不可接受，需要优化。

将 $m$ 个属性值分开考虑。由于 $x$ 到 $y$ 的边权为两者对应属性值的差，显然可以按属性值对 $n$ 个点排序，每个点只向相邻的点连边。这样单层的边数就变成 了 $\Theta(n)$，一共 $m$ 层。

简单总结一下：

- 一共有 $n$ 个出点，以及 $m$ 层入点，每层 $n$ 个；
- 每层的入点之间，从小点向大点连边权为两者之差的边，从大点往小点连边权为 $0$ 的边，只对 rank 相邻的点加边即可；
- 点 $x$ 对应的 $m$ 个入点均向出点连一条权值 $c_x$ 的边；
- 每个出点向其对应的所有入点连一条边权为 $0$ 的边，这是因为优化建图后可以直接走入点间的连边。

点数与边数均为 $\Theta(nm)$ 级别。

建完图直接跑最短路即可。

[完整赛时 AC 代码](https://codeforces.com/problemset/submission/1936/248969388)。

---

## 作者：tyr_04 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1936C)

场上没切掉，场下发现思路没问题，代码没调出来，该反思一下了。（（（

### 题意

$n$ 个人在竞技场，每个人有 $m$ 个属性，第 $i$ 个人的第 $j$ 个属性记为 $a_{i,j}$，每次决斗赢的人留在擂台上，输的人下场，$x$ 能打败 $y$ 当且仅当存在某个 $k$ 使得 $a_{x,k} \ge a_{y,k}$。第 $i$ 个人出场需花费 $c_i$，可以花费 $p$ 将某个人的某个属性永久提升 $p$，一开始第 $1$ 个人在擂台上，问要使第 $n$ 个人在擂台上的最小花费。

### 思路

考虑建图，边 $p$ 到 $q$ 的定义是 $q$ 将 $p$ 打败的花费，固定属性 $u$，若第 $x$ 个人能被 $y$ 打败（只看属性 $u$），则 $x$ 向 $y$ 连边，边权为 $c_y$；如果 $x$ 通过属性 $u$ 可以打败 $z$，$x$ 仍向 $z$ 连边，边权为 $c_z + a_{x,u} - a_{z,u}$，从 $1$ 到 $n$ 跑一遍最短路就是答案。

第一种连边正确性显然，思考第二种连边为什么不会影响答案。

假设现在在 $x$，通过第二种边去往 $y$。如果 $y$ 是终点，正确性显然（先将 $y$ 的属性增加再打败 $x$，符合题意），如果再下次从 $y$ 去往 $z$：

* 如果 $y$ 未通过 $u$ 属性去往 $z$，明显不影响。

* 如果 $y$ 通过 $u$ 属性去往 $z$，那么从 $x$ 直接去往 $z$ 花费一定更少（首先出场花费少了 $y$，其次从 $x$ 去往 $z$ 增加的属性少于 $x$ 先去 $y$ 再去 $z$），所以更劣，也不影响。

按照上述方式直接连边复杂度高达 $O(nm^2)$，使用前缀优化建图和分治优化建图可以做到点数 $O(nm)$，边数 $O(nm)$，总复杂度 $O(nm\log(nm))$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,dist[800005],c[800005];
bool z[800005];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
vector<int> a[800005];
vector<pair<int,int> > v[800005];
struct node
{
	int u,id;
}s[800005];
bool cmp(node x,node y)
{
	return x.u>y.u;
}
void dij()
{
	for(int i=1;i<=2*n*m;i++)
	{
		dist[i]=1e18;
		z[i]=0;
	}
	dist[1]=0;
	q.push({0,1});
	while(!q.empty())
	{
		pair<int,int> u=q.top();
		q.pop();
		int lc=u.first,x=u.second;
		if(z[x]==1)
		{
			continue;
		}
		z[x]=1;
		for(int i=0;i<v[x].size();i++)
		{
			int y=v[x][i].first,bq=v[x][i].second;
			if(dist[y]>lc+bq)
			{
				dist[y]=lc+bq;
				q.push({dist[y],y});
			}
		}
	}
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>c[i];
		}
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
			{
				v[j+i*n].push_back({j,c[j]});
			}
		}
		for(int i=1;i<=n;i++)
		{
			a[i].push_back(0);
			for(int j=1;j<=m;j++)
			{
				int x;
				cin>>x;
				a[i].push_back(x);
			}
		}
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
			{
				s[j].id=j;
				s[j].u=a[j][i];
			}
			sort(s+1,s+n+1,cmp);
			for(int j=1;j<=n;j++)
			{
				if(j<n)
				{
					v[s[j+1].id+i*n].push_back({s[j].id+i*n,0});
					v[s[j].id+i*n].push_back({s[j+1].id+i*n,s[j].u-s[j+1].u});
				}
				v[s[j].id].push_back({s[j].id+i*n,0});
			}
		}
		dij();
		cout<<dist[n]<<'\n';
		for(int i=1;i<=2*n*m;i++)
		{
			a[i].clear();
			v[i].clear();
		}
	}
	return 0;
}
```

---

## 作者：TLE_AK (赞：0)

### 题意
有 $n$ 只宝可梦，每只宝可梦有 $m$ 个属性值 $a_{i,j}$，现在有两个操作。
- 选择 $3$ 个整数 $i,j,k$，将第 $i$ 个宝可梦的第 $j$ 属性增加 $k$，同时增加k的代价。
- 选择 $2$ 个整数 $i,j$，设场上为第 $x$ 只宝可梦，若 $a_{i,j}\ge a{x,j}$，则场上变为第 $i$ 只宝可梦。
## 思路
先考虑暴力建图，对于每个 $i$ 向其他所有的 $j$ 连 $m$ 条边,每条边的边权为 $\max{0,a_{i,x}-a_{j,x}}$，跑最短路即可（一个属性最多提升一次，$i$ 用 $x$ 属性打败 $j$ 的代价固定，所以可以直接建图），这样做边是 $O(n^2m)$ 的。

考虑优化,我们注意到我们可以叠加小的来达到大的（等价于赢了 $a$ 后提升再赢 $b$ 这样，我们只要对每个属性排序，分层后相邻的连接。这样做边数是 $O(nm)$ 的。

对于每个点权拆成入点出点，然后直接建图跑最短路即可。
## 代码
注意因为我们的松弛代表场上宝可梦变更，所以对于小到大的点设为 $0$，大到小的点设为两者差值。  
其余有关建图问题可看代码。
```
#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace acac
{
	struct edge
	{
		int to,ne,v;
	}e[2000100];
	int cnt,tot;
	
	//dij手写堆 
	struct node
	{
		int v,w;
	}sreap[2000100];
	int dis[1000010],H[1000010],T[1000010];
	void up(int u)
	{
		while(u>1)
		{
			if(sreap[u].v<sreap[u>>1].v)
			{
				swap(sreap[u].v,sreap[u>>1].v);
				swap(sreap[u].w,sreap[u>>1].w);
				u>>=1;
			}
			else break;
		}
	}
	void down(int u)
	{
		while(2*u<=tot)
		{
			//cout<<u<<endl;
			int tmp;
			if(2*u==tot)tmp=2*u;
			else if(sreap[2*u].v<sreap[2*u+1].v)tmp=2*u;
			else tmp=2*u+1;
			if(sreap[u].v>sreap[tmp].v)
			{
				swap(sreap[u].v,sreap[tmp].v);
				swap(sreap[u].w,sreap[tmp].w);
				u=tmp;
			}
			else break;
		}
	}
	void ins(int v,int w)
	{
		sreap[++tot].v=v;
		sreap[tot].w=w;
		up(tot);
	}
	void del()
	{
		swap(sreap[1].v,sreap[tot].v);
		swap(sreap[1].w,sreap[tot].w);
		//cout<<sreap[1].v<<endl;
		tot--;
		if(!tot)sreap[1].v=0;
		down(1);
		//	cout<<sreap[1].v<<endl<<endl;
		
	}
	void add(int a,int b,int c)
	{
	//	cout<<a<<' '<<b<<' '<<c<<endl;
		e[++cnt].to=b;
		e[cnt].ne=H[a];
		H[a]=cnt;
		e[cnt].v=c;
	}
	//最短路 
	void dij()
	{
		
		dis[1]=0;
		ins(0,1);
		while(tot)
		{
			int u=sreap[1].w;
			del();
			if(T[u])continue;
			T[u]=1;
			for(int i=H[u];i;i=e[i].ne)
			{
				int v=e[i].to;
				if(dis[u]+e[i].v<dis[v])
				{
					dis[v]=dis[u]+e[i].v;
					if(!T[v])ins(dis[v],v);
				}
			}
		}
	}

	struct node2
	{
		int id,v;
	}B[400010];
	
	bool cmp(node2 a,node2 b)
	{
		return a.v<b.v;
	}
	
	vector<int>A[400010];
	int C[400010];

	int main()
	{
		int t;
		scanf("%lld",&t);
		while(t--)
		{
			int n,m;
			scanf("%lld%lld",&n,&m);
			//初始化
			//应该不会有人memset吧qwq 
			for(int i=1;i<=(m+1)*n;i++)
			{
				T[i]=H[i]=0;
				dis[i]=1e18;
				if(i<=n)A[i].clear();
			}
			cnt=0;
			for(int i=1;i<=n;i++)
			{
				scanf("%lld",&C[i]);
			}
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=m;j++)
				{
					//这里的i为出点，i+j*n为入点，表经过一个点 
					add(i,i+j*n,0);
					add(i+j*n,i,C[i]);
					int a;
					scanf("%lld",&a);
					A[i].push_back(a);
				}
			}
	//		cout<<endl;
			for(int j=1;j<=m;j++)
			{
				//对每个j分层 
				for(int i=1;i<=n;i++)
				{
					B[i]={i+j*n,A[i][j-1]};
				}
				sort(B+1,B+1+n,cmp);
				for(int i=1;i<n;i++)
				{
					//上面提的细节 
					add(B[i].id,B[i+1].id,0);
					add(B[i+1].id,B[i].id,B[i+1].v-B[i].v);
				}
			}
		
			dij();
			cout<<dis[n]<<'\n';
			
		}
		return 0;
	}
}
#undef int
int main()
{
//	freopen("out.out","w",stdout);
	acac::main();
	return 0;
}

```

---

## 作者：XYQ_102 (赞：0)

# E. Pokémon Arena

> You are at a dueling arena. You also possess $n$ Pokémons. Initially, only the $1$-st Pokémon is standing in the arena.
> 
> Each Pokémon has $m$ attributes. The $j$-th attribute of the $i$-th Pokémon is $a\_{i,j}$. Each Pokémon also has a cost to be hired: the $i$-th Pokémon's cost is $c\_i$.
> 
> You want to have the $n$-th Pokémon stand in the arena. To do that, you can perform the following two types of operations any number of times in any order:
> 
> +   Choose three integers $i$, $j$, $k$ ($1 \le i \le n$, $1 \le j \le m$, $k \gt 0$), increase $a\_{i,j}$ by $k$ permanently. The cost of this operation is $k$.
> +   Choose two integers $i$, $j$ ($1 \le i \le n$, $1 \le j \le m$) and hire the $i$-th Pokémon to duel with the current Pokémon in the arena based on the $j$-th attribute. The $i$-th Pokémon will win if $a\_{i,j}$ is **greater than or equal to** the $j$-th attribute of the current Pokémon in the arena (otherwise, it will lose). After the duel, only the winner will stand in the arena. The cost of this operation is $c\_i$.
> 
> Find the minimum cost you need to pay to have the $n$-th Pokémon stand in the arena.
> 
> $1 \le n \times m \le 4 \times 10^5$。

图论好题。

首先，$O(n^2m)$ 的建图方法是简单的，现在我们考虑如何优化。

分析一下，考虑这样一种建图方式，对于每一个属性，我们都建立出 $2n$ 个点，还有 $n$ 个点为那 $n$ 个点本身。

![](https://cdn.luogu.com.cn/upload/image_hosting/281fc0qw.png)

我们的两列点都是按照从大到小的顺序做的。

可以模拟一下，发现这样就变成了求 $1 \sim n$ 的最短路了。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second

const int N=2e6+5;
const ll inf=1e18;
int n,m,c[N],idx=0,T;
ll dis[N];
vector<pair<int,ll>> G[N];
bool vis[N];

struct node{
  int id,v;
  bool operator <(const node &rhs) const{return v<rhs.v;}
};
vector<node> a[N];

ll dij(){
  for(int i=1;i<=idx;i++) dis[i]=inf,vis[i]=false;
  dis[1]=0;
  priority_queue<pair<ll,int> > Q;
  Q.push({0,1});
  while(!Q.empty()){
    int u=Q.top().se;Q.pop();
    if(vis[u]) continue;
    vis[u]=true;
    for(auto i:G[u]){
      ll w=i.se,v=i.fi;
      if(dis[v]>dis[u]+w){
      	dis[v]=dis[u]+w;
      	Q.push({-dis[v],v});
      }
    }
  }
  return dis[n];
}

void sol(){
  cin>>n>>m;idx=n;
  for(int i=1;i<=n;i++) cin>>c[i];
  for(int i=1;i<=n;i++) for(int j=1,x;j<=m;j++) cin>>x,a[j].pb((node){i,x});
  for(int i=1;i<=m;i++){
  	sort(a[i].begin(),a[i].end());
  	for(int j=1;j<=n;j++) G[j].pb({idx+j,0}),G[idx+n+j].pb({j,c[j]}),G[idx+j].pb({idx+n+j,0});
  	for(int j=1;j<n;j++) G[idx+a[i][j].id].pb({idx+a[i][j-1].id,a[i][j].v-a[i][j-1].v});
  	for(int j=0;j+1<n;j++) G[idx+n+a[i][j].id].pb({idx+n+a[i][j+1].id,0});
  	idx+=2*n;a[i].clear();
  }
  cout<<dij()<<'\n';
  for(int i=1;i<=idx;i++) G[i].clear();
}

int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>T;
  while(T--) sol();
  return 0;
}
```

---

