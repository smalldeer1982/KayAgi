# Road Construction

## 题目描述

There are $ N $ cities in the country of Numbata, numbered from $ 1 $ to $ N $ . Currently, there is no road connecting them. Therefore, each of these $ N $ cities proposes a road candidate to be constructed.

City $ i $ likes to connect with city $ A_i $ , so city $ i $ proposes to add a direct bidirectional road connecting city $ i $ and city $ A_i $ . It is guaranteed that no two cities like to connect with each other. In other words, there is no pair of integers $ i $ and $ j $ where $ A_i = j $ and $ A_j = i $ . It is also guaranteed that any pair of cities are connected by a sequence of road proposals. In other words, if all proposed roads are constructed, then any pair of cities are connected by a sequence of constructed road.

City $ i $ also prefers the road to be constructed using a specific material. Each material can be represented by an integer (for example, $ 0 $ for asphalt, $ 1 $ for wood, etc.). The material that can be used for the road connecting city $ i $ and city $ A_i $ is represented by an array $ B_i $ containing $ M_i $ integers: $ [(B_i)_1, (B_i)_2, \dots, (B_i)_{M_i}] $ . This means that the road connecting city $ i $ and city $ A_i $ can be constructed with either of the material in $ B_i $ .

There are $ K $ workers to construct the roads. Each worker is only familiar with one material, thus can only construct a road with a specific material. In particular, the $ i^{th} $ worker can only construct a road with material $ C_i $ . Each worker can only construct at most one road. You want to assign each worker to construct a road such that any pair of cities are connected by a sequence of constructed road.

## 说明/提示

Explanation for the sample input/output #1

We can assign the workers to construct the following roads:

- The first worker constructs a road connecting city $ 1 $ and city $ 2 $ .
- The second worker constructs a road connecting city $ 2 $ and city $ 3 $ .
- The third worker constructs a road connecting city $ 3 $ and city $ 4 $ .
- The fourth worker does not construct any road.
- The fifth worker constructs a road connecting city $ 4 $ and city $ 2 $ .

 Therefore, any pair of cities are now connected by a sequence of constructed road.Explanation for the sample input/output #2

There is no worker that can construct a road connecting city $ 1 $ , thus city $ 1 $ is certainly isolated.

## 样例 #1

### 输入

```
4 5
2 2 1 2
3 2 2 3
4 2 3 4
2 2 4 5
1 2 3 4 5
```

### 输出

```
1 2
2 3
3 4
0 0
4 2
```

## 样例 #2

### 输入

```
4 5
2 2 10 20
3 2 2 3
4 2 3 4
2 2 4 5
1 2 3 4 5
```

### 输出

```
-1
```

# 题解

## 作者：xiayuyang (赞：2)

(这个题好像在luogu上交不上去？可以直接去cf上交[题目链接](https://codeforces.ml/contest/1252/problem/L))

[csdn食用地址](https://blog.csdn.net/wmhtxdy/article/details/104171990)

解法
有源汇上下界最大流

考虑如果需要连所有边的建图，每个工人向可以建的路连边，直接跑就好了。现在只需要图联通，考虑原图是一个基环树，所以树边一定要连，环边不一定要连，就跑有源汇上下界可行流,判断能否满足树边的要求，然后再跑出最大流，看最大流是否>=n-1，这样图才能联通，因为只跑可行流，环上的不一定能联通。输出方案的时候bfs满流的边。

然后直接建图会T，考虑优化建图，将材料编号离散化以后，每个工人向对应材料连边，路也向对应材料连边，注意处理好没有匹配上的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=1e5+5;
inline int read(){
	char c=getchar();int t=0,f=1;
	while((!isdigit(c))&&(c!=EOF)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)&&(c!=EOF)){t=(t<<3)+(t<<1)+(c^48);c=getchar();}
	return t*f;
}
int n,k;
vector<int> g[maxn];
vector<int> col[maxn];
int alfa[maxn];
int vis[maxn<<2],st[maxn],top,flag[maxn],bt,s,t,ss,tt;
void dfs(int u,int fa){
	st[++top]=u;vis[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		if(vis[v]){
			int tmp=st[top];
			while(tmp!=v&&top){
				flag[tmp]=1;
				top--;
				tmp=st[top];
			}
			top--;
			flag[v]=1;
			bt=1;
			return ;
		}
		dfs(v,u);
		if(bt)return ;
	}
	top--;
}
struct edge{
	int v,p,w;
}e[maxn<<2];
int h[maxn<<1],cnt=1,tot,val[maxn<<2];
inline void add(int a,int b,int c){
	e[++cnt].p=h[a];
	e[cnt].v=b;
	e[cnt].w=c;
	val[cnt]=c;
	h[a]=cnt;
}
int dis[maxn<<2],out[maxn],a[maxn];
bool bfs(){
	queue<int> q;
	memset(dis,0,sizeof(dis));
	while(!q.empty())q.pop();
	q.push(ss);
	dis[ss]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		//printf("%d\n",u);
		for(int i=h[u];i;i=e[i].p){
			int v=e[i].v;
			if(e[i].w&&(!dis[v])){
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return dis[tt]!=0;
}
int ht[maxn<<2];
int df(int u,int rest){
	if(rest==0||u==tt){
		return rest;
	}
	int tot=0;
	for(int &i=ht[u];i;i=e[i].p){
		int v=e[i].v;
		if(dis[v]==dis[u]+1&&e[i].w){
			int di=df(v,min(rest,e[i].w));
			e[i].w-=di;e[i^1].w+=di;
			tot+=di;rest-=di;
			if(rest==0)break;
		}
	}
	return tot;
}
int dinic(){
	int ans=0;
	while(bfs()){
		//puts("!");
		for(int i=0;i<=tt;i++)ht[i]=h[i];
		int di=0;
		while(di=df(ss,inf))ans+=di;
	}
	return ans;
}
int in[maxn];
int ls[maxn<<2],num;
void get(){
	queue<int> q;
	memset(vis,0,sizeof(vis));
	while(!q.empty())q.pop();
	q.push(ss);
	vis[ss]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=1;
		//printf("%d\n",u);
		for(int i=h[u];i;i=e[i].p){
			int v=e[i].v;
			if(vis[v])continue;
			if((!e[i].w)){
				if(u<=k&&v>n+k&&v<=n+k+num){
					if(!out[u])
					out[u]=v-n-k;
				}
				if(u>n+k&&u<=n+k+num&&v>k&&v<=n+k){
					if(!in[v-k])in[v-k]=u-n-k;
				}
				q.push(v);
			}
		}
	}
}
void find(){
	h[ss]=0;h[tt]=0;
	ss=s;tt=t;
	int ans=dinic();
	//printf("%d\n",ans+tot);
	get();
}
int alf[maxn],bet[maxn];
int main(){
	//freopen("1252L.in","r",stdin);
	//freopen("1252L.out","w",stdout);
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		g[a[i]].push_back(i);
		g[i].push_back(a[i]);
		int m=read();
		for(int j=1;j<=m;j++){
			int c=read();
			ls[++num]=c;
			col[i].push_back(c);
		}
	}
	for(int i=1;i<=k;i++){
		alfa[i]=read();
		ls[++num]=alfa[i];
	}
	sort(ls+1,ls+1+num);
	num=unique(ls+1,ls+1+num)-ls-1;
	dfs(1,0);
	s=0,t=n+k+num+1,ss=t+1,tt=ss+1;
	for(int i=1;i<=k;i++){
		add(s,i,1);
		add(i,s,0);
	}
	for(int i=1;i<=n;i++){
		if(flag[i]){
			//printf("%d\n",i);
			add(i+k,t,1);
			add(t,i+k,0);
		}
		if(!flag[i]){
			tot++;
		//	printf("%d\n",i);
			add(ss,t,1);
			add(t,ss,0);
			add(i+k,tt,1);
			add(tt,i+k,0);
		}
	}
	for(int i=1;i<=n;i++){
		int l=col[i].size();
		for(int j=0;j<l;j++){
			col[i][j]=lower_bound(ls+1,ls+1+num,col[i][j])-ls;
			add(n+k+col[i][j],i+k,1);
			add(i+k,n+k+col[i][j],0);
		} 
	}
	for(int i=1;i<=k;i++){
		alfa[i]=lower_bound(ls+1,ls+1+num,alfa[i])-ls;
		add(i,n+k+alfa[i],1);
		add(n+k+alfa[i],i,0);
	}
	add(t,s,inf);add(s,t,0);
	int tmp=dinic();
	//printf("%d\n",tmp);
	if(tmp==tot){
		find();
		memset(vis,0,sizeof(vis));
		int ans=0;
		for(int i=1;i<=k;i++){
			int flag=0;
			if(out[i]==0)continue;
			for(int j=1;j<=n;j++){
				if((out[i]==in[j])&&(!vis[j])){
					flag=1;ans++;
					alf[i]=j;bet[i]=a[j];
					vis[j]=1;break;
				}
			}
		}
		if(ans<n-1){puts("-1");return 0;}
		for(int i=1;i<=k;i++){
			printf("%d %d\n",alf[i],bet[i]);
		}
		return 0;
	}
	else{
		puts("-1");
	}
	return 0;
}
```


---

## 作者：幻影星坚强 (赞：0)

因为原图给出了一个基环树，而要让图联通则在环上至多有一条边不选，所有树边必须选择，而如果全部边都选择有解那么环上有一条边不选也一定有解（任意去环上的一条边都可以将其变成一棵树），那么我们直接让环上必须要有一条边不选，于是就有个建图方法：

- 从原点向将所有工人连流量为 $1$ 的边，代表他只能建一条边。

- 从所有工人向他能建造的边连流量为 $1$ 的边，代表他能建造这些边。

- 所有树边向汇点连流量为 $1$ 的边，代表这条边必须选。

- 所有环边向一个新节点连流量为 $1$ 的边，这个新节点向汇点连环长 $-1$的边，代表这些边要有一条不选。

最后得到的最大流假如结果是 $n-1$ 则有一组环上必须有一条边不选的解，否则肯定无解。

点数 $O(n)$，因为差不多像个二分图所以跑的飞快。

方案直接根据残余网络构造。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
using namespace std;
const int N = 2010;
struct bian
{
	int from, to, w;
}eg[N * N * 2 + N * 10];
int front[N << 2], num;
vector<int>cir;
map<int, int>metal[N];
struct tree
{
	bian eg[N << 1];
	int front[N], num;
	void add(int x, int y)
	{
		eg[++ num].to = y;
		eg[num].from = front[x];
		front[x] = num;
	}
	int fa[N], vis[N], dep[N];
	void dfs(int o, int from)
	{
		vis[o] = 1;
		fa[o] = from;
		dep[o] = dep[from] + 1;
		for (int i = front[o]; i; i = eg[i].from)
		{
			int to = eg[i].to;
			if(to == from)continue;
			if(vis[to] && dep[to] < dep[o])
			{
				int now = o;
				cir.push_back(now);
				while(now != to)
				{
					now = fa[now];
					cir.push_back(now);
				}
				continue;
			}
			if(vis[to])continue;
			dfs(to, o);
		}
	}
}T;
void add(int x, int y, int w)
{
	eg[++ num].to = y;
	eg[num].from = front[x];
	front[x] = num;
	eg[num].w = w;
	swap(x, y);
	eg[++ num].to = y;
	eg[num].from = front[x];
	front[x] = num;
}
int _front[N << 1], dis[N << 1];
int sf[N];
int n, m, s, t;
bool bfs()
{
	memset(dis, 0, sizeof(dis));
	queue<int>q;
	q.push(s);
	dis[s] = 1;
	while(!q.empty())
	{
		int o = q.front();
		q.pop();
		for (int i = front[o]; i; i = eg[i].from)
		{
			int to = eg[i].to;
			if(eg[i].w && dis[to] == 0)
			{
				dis[to] = dis[o] + 1;
				q.push(to);
			}
		}
	}
	return dis[t] != 0;
}
int dfs(int o, int lim)
{
	if(o == t)return lim;
	int now = 0;
	for (int &i = _front[o]; i; i = eg[i].from)
	{
		int to = eg[i].to;
		if(eg[i].w == 0 || dis[to] != dis[o] + 1)continue;
		int del = dfs(to, min(lim, eg[i].w));
		eg[i].w -= del;
		eg[((i - 1) ^ 1) + 1].w += del;
		now += del;
		if(now == lim)break;	
	}
	return now;
}
int dinic()
{
	int re = 0;
	while(bfs())
	{
		memcpy(_front, front, sizeof(front));
		re += dfs(s, 1e9);
	}
	return re;
}
int x[N];
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i)
	{
		int m;
		scanf("%d%d", &x[i], &m);
		T.add(i, x[i]);
		T.add(x[i], i);
		while(m --)
		{
			int x;
			scanf("%d", &x);
			metal[i][x] = 1;
		}
	}
	T.dfs(1, 0);
	s = n + m + 2;
	t = s + 1;
	for (int i = 1; i <= m; ++ i)
	{
		int has;
		scanf("%d", &has);
		add(s, i, 1);
		for (int j = 1; j <= n; ++ j)
		{
			if(metal[j][has])
			add(i, j + m, 1);
		}
	}
	for (int i = 0; i < cir.size(); ++ i)
	sf[cir[i]] = 1;
	for (int i = 1; i <= n; ++ i)
	{
		if(sf[i])
		add(i + m, n + m + 1, 1);
		else
		add(i + m, t, 1);
	}
	add(n + m + 1, t, cir.size() - 1);
	if(dinic() != n - 1)return printf("-1"), 0;
	for (int i = 1; i <= m; ++ i)
	{
		for (int j = front[i]; j; j = eg[j].from)
		{
			int to = eg[j].to;
			if(to == s && eg[j].w == 0)
			{
				printf("0 0\n");
				continue;
			}
			if(to > m && to <= n + m && eg[j].w == 0)
			printf("%d %d\n", to - m, x[to - m]);
		}
	}
}
```


---

