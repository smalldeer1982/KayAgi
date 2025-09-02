# Ivan the Fool VS Gorynych the Dragon

## 题目描述

Once upon a time in a kingdom far, far away… Okay, let’s start at the point where Ivan the Fool met Gorynych the Dragon. Ivan took out his magic sword and the battle began. First Gorynych had $ h $ heads and $ t $ tails. With each strike of the sword Ivan can either cut off several heads (from $ 1 $ to $ n $ , but not more than Gorynych has at the moment), or several tails (from $ 1 $ to $ m $ , but not more than Gorynych has at the moment). At the same time, horrible though it seems, Gorynych the Dragon can also grow new heads and tails. And the number of growing heads and tails is determined uniquely by the number of heads or tails cut by the current strike. When the total number of heads and tails exceeds $ R $ , Gorynych the Dragon strikes its final blow and destroys Ivan the Fool. That’s why Ivan aims to cut off all the dragon’s heads and tails as quickly as possible and win. The events can also develop in a third way: neither of the opponents can win over the other one and they will continue fighting forever.

The tale goes like this; easy to say, hard to do. Your task is to write a program that will determine the battle’s outcome. Consider that Ivan strikes consecutively. After each blow Gorynych grows a number of new heads and tails depending on the number of cut ones. Gorynych the Dragon is defeated if after the blow he loses all his heads and tails and can’t grow new ones. Ivan fights in the optimal way (fools are lucky), i.e.

- if Ivan can win, he wins having struck the least number of blows;
- if it is impossible to defeat Gorynych, but is possible to resist him for an infinitely long period of time, then that’s the strategy Ivan chooses;
- if Gorynych wins in any case, Ivan aims to resist him for as long as possible.

## 样例 #1

### 输入

```
2 2 4
2
1 0
0 1
3
0 1
0 1
0 0
```

### 输出

```
Ivan
2
```

## 样例 #2

### 输入

```
2 2 4
1
0 1
1
1 0
```

### 输出

```
Draw
```

## 样例 #3

### 输入

```
2 2 5
1
1 1
1
3 0
```

### 输出

```
Zmey
2
```

# 题解

## 作者：wjh2011 (赞：2)

由于这题数据范围不大，所以我们可以直接枚举状态 $(i,j)$ 至少要几步才能到达，这里可以用 bfs 或 dijkstra 解决。

如果从 $(h,t)$ 可以到 $(0,0)$，那么直接输出 `Ivan` 和 $dis_{0,0}$。

否则我们把所有 $i+j>R$ 的 $(i,j)$ 合并成一个点，然后建反图并从这个点开始跑拓扑排序。如果到 $(h,t)$ 的路径上有环，输出 `Draw`，否则输出 `Zmey` 和这个点到 $(h,t)$ 的距离。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 405
#define PII pair<int, int>
int h, t, n, m, k, ans, h_n[N], t_n[N], h_m[N], t_m[N], dis[N * N], in[N * N];
vector<int> G[N * N], E[N * N];
bool vis[N * N];
int get(int x, int y) { return x * 400 + y; }
void dijkstra() {
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	priority_queue<PII,vector<PII>,greater<PII>> q;
	dis[get(h, t)] = 0;
	q.push({0, get(h, t)});
	while (q.size()) {
		int x = q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int y : G[x]) {
			if(dis[y] > dis[x] + 1) {
				dis[y] = dis[x] + 1;
				q.push({dis[y], y});
			}
		}
	}
}
int topo_sort() {
    memset(vis, 0, sizeof(vis));
    queue<PII> q;
    for (int i = 0; i <= k; i++)
        for (int j = 0; i + j <= k; j++) {
            int x = get(i, j);
            for (int y : G[x]) {
                E[y].push_back(x);
                in[x]++;
            }
        }
    q.push({100000, 0});
	while (q.size()) {
        PII tmp = q.front();
        q.pop();
        if (vis[tmp.first]) continue;
        vis[tmp.first] = 1;
        if (tmp.first == get(h, t)) return tmp.second;
        for (int y : E[tmp.first]) {
            in[y]--;
            if (!in[y]) q.push({y, tmp.second + 1});
        }
    }
    return -1;
}
int main() {
	cin >> h >> t >> k;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> h_n[i] >> t_n[i];
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> h_m[i] >> t_m[i];
	for (int i = 0; i <= k; i++)
		for (int j = 0; i + j <= k; j++) {
			for (int l = 1; l <= min(n, i); l++) G[get(i, j)].push_back(get(i - l + h_n[l], j + t_n[l]));
			for (int l = 1; l <= min(m, j); l++) G[get(i, j)].push_back(get(i + h_m[l], j - l + t_m[l]));
		}
	for (int i = 0; i <= k; i++)
		for (int j = 0; i + j <= k; j++)
			for (int l = 0; l < G[get(i, j)].size(); l++) {
				int x = G[get(i, j)][l];
				if (x / 400 + x % 400 > k) G[get(i, j)][l] = 100000;
			}
	dijkstra();
	if (dis[0] < 1e9) {
		cout << "Ivan\n" << dis[0];
		return 0;
	}
	int x = topo_sort();
    if (x == -1) cout << "Draw";
    else cout << "Zmey\n" << x;
	return 0;
}
```

---

## 作者：DiDi123 (赞：2)

# 分析

发现这个题所有的数的范围都比较小，考虑暴力建图。

我们设龙有 $i$ 个头和 $j$ 条尾巴的状态为 $c_{i,j}$，那么我们依次考虑砍掉 $1\sim \min(n,i)$ 个头和 $1\sim \min(m,j)$ 条尾巴，并且从 $c_{i,j}$ 向这些状态连边。
 
我们令 $sw=c_{0,0}$，表示 $\text {Ivan}$ 胜利的状态；令所有的 $c_{i,j}=sl(i+j>R)$，表示 $\text {Ivan}$ 失败的状态。

那么我们判断 $\text {Ivan}$ 是否胜利就是判断在图上是否有一条从 $c_{h,t}$ 出发的路径能到达 $sw$，如果有，我们还需要找到最短的路径长度，这样跑 bfs 即可。

如果不能到达 $sw$，我们需要判断是否能平局。发现当 $\text {Ivan}$ 走到一个环中的时候就可以平局（但是我不太会判环qwq）。那就先考虑如果 $\text {Ivan}$  失败，最多需要的步数，相当于求 $c_{h,t}$ 到 $sl$ 的最长路，这个很经典，只需要在反图上跑一遍拓扑排序即可。然后我们发现，拓扑排序也能处理环！发现如果 $c_{h,t}$ 到 $sl$ 的路径上如果有环，那么拓扑排序就无法遍历到 $c_{h,t}$，这样就可以很好的处理平局的情况。

最坏情况下有 $R^2$ 个点，$R^3$ 条边，可以通过。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 210
#define pb push_back
#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pa;
int h,t,r,ct,sl,sw,n,m;
int id[MAXN][MAXN],vis[MAXN*MAXN],ind[MAXN*MAXN],h1[MAXN],t1[MAXN],h2[MAXN],t2[MAXN];
vector <int> g[MAXN*MAXN],sg[MAXN*MAXN];
queue <pa> q;
int bfs()
{
	memset(vis,0,sizeof(vis));
	q.push(mp(id[h][t],0));
	while(!q.empty())
	{
		pa x=q.front();
		q.pop();
		if(x.fi==sw) return x.se;
		if(vis[x.fi]) continue;
		vis[x.fi]=1;
		for(auto y:g[x.fi]) q.push(mp(y,x.se+1));
	}
	return -1;
}
int topo()
{
	memset(vis,0,sizeof(vis));
	while(!q.empty()) q.pop();
	for(int i=1;i<=ct;i++)
		for(auto y:g[i]) sg[y].pb(i),ind[i]++;
	q.push(mp(sl,0));
	while(!q.empty())
	{
		pa x=q.front();
		q.pop();
		if(x.fi==id[h][t]) return x.se;
		for(auto y:sg[x.fi])
		{
			ind[y]--;
			if(!ind[y]) q.push(mp(y,x.se+1));
		}
	}
	return -1;
}
int main()
{
	cin>>h>>t>>r;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>h1[i]>>t1[i];
	cin>>m;
	for(int i=1;i<=m;i++) cin>>h2[i]>>t2[i];
	sl=++ct;
	for(int i=0;i<=r;i++)
		for(int j=0;j<=r-i;j++)
			id[i][j]=++ct;
	sw=id[0][0];
	for(int i=0;i<=r;i++)
		for(int j=0;j<=r-i;j++)
		{
			for(int k=1;k<=min(n,i);k++) 
			{
				if(i-k+h1[k]+j+t1[k]>r) g[id[i][j]].pb(sl),vis[id[i][j]]=1;
				else g[id[i][j]].pb(id[i-k+h1[k]][j+t1[k]]);
			}
			for(int k=1;k<=min(m,j);k++)
			{
				if(i+h2[k]+j-k+t2[k]>r) 
				{
					if(!vis[id[i][j]]) g[id[i][j]].pb(sl);
				}
				else g[id[i][j]].pb(id[i+h2[k]][j-k+t2[k]]);
			}
		}
	int ta=bfs();
	if(ta!=-1)
	{
		puts("Ivan");
		cout<<ta;
		return 0;
	}
	ta=topo();
	if(ta!=-1)
	{
		puts("Zmey");
		cout<<ta;
	}
	else puts("Draw");
}
```


---

## 作者：2018ty43 (赞：1)

## 题意  
- 龙有 $h$ 个头与 $t$ 个尾巴，愚者想杀死了龙，他每次可以砍断龙 $i\in[1,n]$ 个头或 $i\in[1,m]$ 个尾巴。  
- 如果砍了 $i$ 个头，则龙会新长 $hn_i$ 个头与 $tn_i$ 个尾巴，如果砍了 $i$ 个尾巴，则龙会新长 $hm_i$ 个头与 $tm_i$ 个尾巴。  
- 当龙头加尾数大于 $R$ $(h+t>R)$ 时愚者失败，当无头且无尾 $(h=t=0)$ 时愚者胜。  
- 判断愚者如果能胜最快多快胜，无法胜利则是否能无限战斗，失败则最多打多久。
- 所有数字不超过 $200$.

## 思路
考虑 $R\le200$，最多有 $\frac{R}{2}\times \frac{R}{2}=10000$ 种状态，$10000\times (n+m) =4000000$ 种转移，可以枚举每种状态的后继。  
如果可以从 $(h,t)$ 到达 $(0,0)$，则广搜最快多块胜利。  
否则判断状态转移是否有环，有则可以在环上无限战斗。  
如果没有环，则在 DAG 上找从 $(h,t)$ 到 $(0,0)$ 的最长路。

## 代码
```cpp
#include<bits/stdc++.h>
int vis[209][209];
bool az[209][209];
struct T{int u,v;};
std::vector<T>ed[209][209];
int h,t,r,n,m,hn[209],tn[209],hm[209],tm[209];
void dfs(int u,int v)//找到所有可达状态 
{
	if(vis[u][v]||(u==0&&v==0))return;
	vis[u][v]=1;
	for(int i(1);i<=u&&i<=n;++i)if(u+v-i+hn[i]+tn[i]<=r)dfs(u-i+hn[i],v+tn[i]),az[u][v]|=az[u-i+hn[i]][v+tn[i]],ed[u-i+hn[i]][v+tn[i]].push_back((T){u,v});
	for(int i(1);i<=v&&i<=m;++i)if(u+v-i+hm[i]+tm[i]<=r)dfs(u+hm[i],v-i+tm[i]),az[u][v]|=az[u+hm[i]][v-i+tm[i]],ed[u+hm[i]][v-i+tm[i]].push_back((T){u,v});
}
int ans[209][209],quex[209*209],quey[209*209],ss,tt;
int bfs1()//如果可胜，找到胜利的最短路 
{
	while(ss<=tt)
	{
		int u(quex[ss]),v(quey[ss]);
		if(u==h&&v==t)return ans[u][v];
		++ss;
		for(T i:ed[u][v])
		{
			if(ans[i.u][i.v]==0&&(i.u!=0||i.v!=0))
			{
				ans[i.u][i.v]=ans[u][v]+1;
				quex[++tt]=i.u,quey[tt]=i.v;
			}
		}
	}
}
short vis2[209][209];
void dfs2(int u,int v)//查找是否有环 
{
	if(vis2[u][v]==1)
	{
		puts("Draw");
		exit(0);
	}
	if(vis2[u][v]==2)return;
	vis2[u][v]=1;
	for(int i(1);i<=u&&i<=n;++i)if(u+v-i+hn[i]+tn[i]<=r)dfs2(u-i+hn[i],v+tn[i]);
	for(int i(1);i<=v&&i<=m;++i)if(u+v-i+hm[i]+tm[i]<=r)dfs2(u+hm[i],v-i+tm[i]);
	vis2[u][v]=2;
}
int ac[209][209];
inline int max(int u,int v){return (u>v)?u:v;} 
int dfs3(int u,int v)//找失败的最长路 
{
	if(ac[u][v])return ac[u][v];
	for(int i(1);i<=u&&i<=n;++i)if(u+v-i+hn[i]+tn[i]<=r)ac[u][v]=max(ac[u][v],dfs3(u-i+hn[i],v+tn[i]));
	for(int i(1);i<=v&&i<=m;++i)if(u+v-i+hm[i]+tm[i]<=r)ac[u][v]=max(ac[u][v],dfs3(u+hm[i],v-i+tm[i]));
	return ++ac[u][v];
}
int main()
{
	scanf("%d%d%d",&h,&t,&r);
	az[0][0]=1;
	scanf("%d",&n);
	for(int i(1);i<=n;++i)scanf("%d%d",hn+i,tn+i);
	scanf("%d",&m);
	for(int i(1);i<=m;++i)scanf("%d%d",hm+i,tm+i);
	dfs(h,t);
	if(az[h][t])
	{
		printf("Ivan\n%d\n",bfs1());
		return 0;
	}
	dfs2(h,t);
	printf("Zmey\n%d",dfs3(h,t));
}
```


---

## 作者：封禁用户 (赞：0)

思路：本题数据最多就两百，因此可以使用广搜出猎人斩龙的最佳路数，如果猎人无法斩龙，那就深搜判断是否组成回路，从而形成永久的对战模式，还是不行那就更新猎人最终成为龙的食物的最大路数。
```
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int mm=250;
const int oo=1e9;
int vis[mm][mm];
bool yes;
int h,t,r,n,m;
class node
{
  public:int h,t,c;
}hh[mm],tt[mm];
queue<node >q,p;
int dfs(int x,int y)
{ int&ret=vis[x][y];
  int tx,ty;
  if(x+y>r)return 0;
  if(vis[x][y]==-2)
  {
    yes=1;return 0;
  }
  else if(vis[x][y]==-1)
  {
    ret=-2;int dd=-oo,z;
    int bbs;
    bbs=n<x?n:x;
    for(int i=0;i<bbs;i++)
      {
        tx=x+hh[i].h-i-1;ty=y+hh[i].t;
        z=dfs(tx,ty)+1;
        dd=dd>z?dd:z;
      }
      bbs=m<y?m:y;
      for(int i=0;i<bbs;i++)
      {
        tx=x+tt[i].h;ty=y+tt[i].t-i-1;
        z=dfs(tx,ty)+1;
        dd=dd>z?dd:z;
      }
      ret=dd;
  }
  return ret;
}
int main()
{
  while(cin>>h>>t>>r)
  {
    cin>>n;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++)
    {
      cin>>hh[i].h>>hh[i].t;
    }
    cin>>m;
    for(int j=0;j<m;j++)
    {
      cin>>tt[j].h>>tt[j].t;
    }
    vis[h][t]=1;
     int x,y,zz;
     while(!q.empty())q.pop();
     node z,p;yes=0;
     z.h=h;z.t=t;z.c=0;
     q.push(z);
     while(!q.empty()&&!yes)
     { z=q.front();q.pop();
      int bbs=n<z.h?n:z.h;
      for(int j=0;j<bbs;j++)
      {
        x=z.h+hh[j].h-j-1;y=z.t+hh[j].t;
        if(x+y>r)continue;
        if(!vis[x][y])
        {vis[x][y]=1;
         p.h=x;p.t=y;p.c=z.c+1;
         if(x==0&&y==0)
          { cout<<"Ivan\n"<<p.c<<"\n";yes=1;
            break;
          }
         ///if(x+y>r&&d>z.c){d=z.c;continue;}
         q.push(p);
        }
      }
      bbs=m<z.t?m:z.t;
      for(int j=0;j<bbs;j++)
      {
        x=z.h+tt[j].h;y=z.t+tt[j].t-j-1;
        if(x+y>r)continue;
        if(!vis[x][y])
        {vis[x][y]=1;
         p.h=x;p.t=y;p.c=z.c+1;
         if(x==0&&y==0)
          { cout<<"Ivan\n"<<p.c<<"\n";yes=1;
            break;
          }
         ///if(x+y>r&&d>z.c){d=z.c;continue;}
         q.push(p);
        }
      }
    }
    if(yes)continue;
    memset(vis,-1,sizeof(vis));
    int ans=dfs(h,t);
    if(yes)cout<<"Draw\n";
    else cout<<"Zmey\n"<<ans<<"\n";
  }
}
```


---

