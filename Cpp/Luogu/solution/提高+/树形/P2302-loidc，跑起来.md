# loidc，跑起来

## 题目背景

loidc 在路上诱拐了一个幼女。（他不是哲学家么！？）


## 题目描述

现在他已经被 cony 追杀。loidc 逃到一个迷宫中，cony 也追到了这儿。迷宫由编号由 $1$ 到 $n$ 的方块组成。每两个不同的方块将被得知它们是否与另一个相邻。现在已知 loidc 和 cony 所处迷宫的位置。在迷宫中的人可以选择留在原地不动，还是移到相邻的方格中。

迷宫具有如下性质：

它不包括三角形，也就是没有任意三个不同的方块，它们两两相邻，

每一个人到达都能到达任意一个方块。

一次追杀由许多回合组成。在一个回合内，每一个人移一步。每一个回合由 loidc 开始。如果 loidc 与 cony 在同一个方格中相遇，那么我们就可能永远见不到 loidc 了。

loidc 非常害怕，他请求你告诉他是否会被 cony 抓住，多少回合 cony 赶上他。(假设两个人都足够聪明)


## 样例 #1

### 输入

```
9 11 9 4
1 2
3 2
1 4
4 7
7 5
5 1
6 9
8 5
9 8
5 3
4 8
```

### 输出

```
3```

# 题解

## 作者：BFSBFSBFSBFS (赞：9)

~~迷宫入口去哪了..~~

题意.给出1个图.图上有2人.每个人每个回合.可以选择移动到相邻点.或者原地不动.

当2个人相遇就会被....

其中loidc会尽可能延长回合数(就是尽量不相遇.).或者干脆让cony追不上..

而cony会尽力追赶loidc.

由loidc先手.2人均使用最佳策略..求cony能否追上.以及能追上时.至少的回合数.

由于loidc用的最佳策略.显然不会去送..那么对于loidc来讲.就是要求**最多的回合数.**


------------


明确题意后.来看看双方的行动策略.

cony是要追赶loidc的.仔细想想就能明白.cony不会**停留**在1个点上.

为什么.?

若cony选择在1个点停留.接下来loidc可以继续逃跑.给予了**跑掉**的可能性.

如果loidc发现逃跑是不行的.Ta依然可以选择停留在原来的点上.相当于先手权仍然在cony这里.但**白白浪费了1回合**.

不管怎样.停留在1处都不是好方法.所以每回合cony必定**移动**.


------------


这个结论先放在1边.再看看loidc的策略.

如果说要cony追不上的话.loidc唯1的办法是.**在被cony抓到之前跑进环**.

环至少是3个点吧..2个点的明显是送....

这个好理解吧..在环上1跑1追.速度相同.是追不上的...?

这里有反例了.3角形.

 ![](https://cdn.luogu.com.cn/upload/pic/13179.png) 

(黑色的是点..红色的是边..丑..).

可以看到,如果loidc在1号点.cony在3号点.即使跑进2号点也无济于事.cony可以马上到达2号点.loidc只能被迫退出3元环..

可是.题目告诉你了没有3角形...那这条就不用管了..

也就是.只要loidc跑进**至少4个点组成的环**.loidc就不会被抓到.


------------


好了.策略分析完毕.那么loidc要怎样跑呢.?

显然.我们要尽快到达环.当然是走**最短路**了..

但是还有cony啊.不能被捉到.

我们已经知道,cony不会不动.那么让cony也跑**最短路**.比较1下就行了..

cony难道不能放弃最短路.去拦截在半路loidc.?

既然都能拦截了.那去拦截的这条路+lodic剩下的最短路.又可以组成新的最短路..

也就是不管怎样.cony1定跑在**最短路**上.

问题就变成了求2点的单元最短路.

设loidc到第i个点的最短路为$d[i]$.cony到第i个点的最短路为$e[i]$.

如果有$d[i] < e[i]$,并且$i$点在有4个点以上组成的环上面.的话.输出**NO**.

那么跑不进环怎么办.?

只能找个地方躲起来等....

就是说.对于每个$d[i] < e[i]$.输出$max(e[i])$.

就是cony最慢要跑的时间了..

Diu代码..

```cpp
program P2302;
 uses math;
 type
  wb=array[0..3001] of longint;
  wa=record
   n,t:longint;
  end;
 var
  a:array[0..30001] of wa;
  b,c,h,f,stl,instl,DFS,DFN,t:wb;
  i,m,n,p,dsum,sumstl,ac,bc,upass,smax,x,y:longint;
 procedure hahainc(x,y:longint);    //前向星遍历边..
  begin
   inc(p);
   a[p].n:=h[x];
   a[p].t:=y;
   h[x]:=p;
  end;
 procedure hahaDFS(k,lp:longint);  //用tarjan求环..
  var
   j,p,upass:longint;
  procedure hahaapps;        //初始化工作..
   begin
    inc(dsum);
    DFS[k]:=dsum;           //DFS序.
    DFN[k]:=dsum;           //最靠前访问过的点的DFS序.
    inc(sumstl);            //进栈.
    stl[sumstl]:=k;           //.
    instl[k]:=1;            //是否在栈内的判断..
    f[k]:=1;                //是否访问过的判断..
   end;
  begin
   hahaapps;
   j:=h[k];
   while a[j].n<>-1 do      //遍历边.
    begin
     p:=a[j].t;
     j:=a[j].n;
     if p=lp then continue; //这个是过滤2点环.因为这是无向边..
     if f[p]=0 then
      begin
       hahaDFS(p,k);
       DFN[k]:=min(DFN[k],DFN[p]); //环标记传递.
      end
               else if instl[p]=1 then DFN[k]:=min(DFN[k],DFS[p]); //栈内形成环.
    end;
   if stl[sumstl]=k then upass:=1 //这个是过滤单点环(..)..
                    else upass:=0;
   if DFN[k]=DFS[k] then
    repeat
     p:=stl[sumstl];
     if upass=0 then t[p]:=1;     //t是环标记.
     instl[p]:=0;
     dec(sumstl);
    until p=k;
  end;
 procedure hahadij(var b:wb;k:longint); //做2遍dij..
  var
   i,j,p:longint;
  begin
   filldword(b,length(b),1008208820);
   filldword(f,length(f),0);
   b[k]:=0;
   for i:=1 to n do
    begin
     p:=0;
     for j:=1 to n do
      if (f[j]=0) and (b[j]<b[p]) then p:=j;
     f[p]:=1;
     j:=h[p];
     while a[j].n<>-1 do
      begin
       if b[p]+1<b[a[j].t] then b[a[j].t]:=b[p]+1; //权值是1了..
       j:=a[j].n;
      end;
    end;
  end;
 begin
  readln(n,m,ac,bc);
  filldword(h,length(h),0);
  p:=0;
  for i:=1 to m do
   begin
    readln(x,y);
    hahainc(x,y);
    hahainc(y,x);
   end;
  a[0].n:=-1;
  filldword(f,length(f),0);
  filldword(t,length(t),0);
  filldword(instl,length(instl),0);
  sumstl:=0;
  dsum:=0;
  for i:=1 to n do
   if f[i]=0 then hahaDFS(i,0);
  {for i:=1 to n do
   writeln(DFS[i],' ',DFN[i],' ',t[i]);}
  hahadij(b,ac);
  hahadij(c,bc);
  upass:=0;
  smax:=0;
  for i:=1 to n do
   begin
    if (c[i]>b[i]) and (t[i]=1) then upass:=1;    //能否跑进环的标记.
    if (c[i]>b[i]) then smax:=max(smax,c[i]);     //最长的回合数..
   end;
  if upass=0 then writeln(smax)
             else writeln('NO');
 end.
```
欢迎Hack.

(ಡωಡ).


---

## 作者：MuYC (赞：4)

[这里看体验更好](https://www.cnblogs.com/MYCui/p/13916652.html)
#### 扯淡
这个游戏让我想起了小学和同学玩"抓人"，有过游戏经验的同学都知道，我们要找一个地方，可以和"追捕者"一直转圈圈，比如有东西两个楼道的教学楼就是不错的地方。
### 题意简化

现在有两个人小$L$(loidc)和小$C$(cony)，都处于一张无向联通图上的某个节点(给出他们所在的节点)而且这张图不存在三元环，每次一个人每回合可以走一步，小$L$尽量避免与小$C$相遇，而小$C$则尽量想让两个人相遇(有没有一点点像狗血的某种故事.......)两个人都选择最佳策略，问最终会不会相遇，如果相遇，那么最少用几回合？。

### 解题思路
你会说，我一开头说的是废话，但是事实则不然.......这道题和上面的抓人游戏类似。

抽象到题目里面，什么地方是可以和"追捕者"一直转圈圈的？不难想，是环上面。一开始我很费解，为什么给出这张图不含三元环，后来我思考了一下，三元环其实并不能满足一直转圈圈的性质，题解中的第一篇就讲到了这一点。

那最优策略就是小$L$就要赶紧跑到环上面，小$C$要赶紧堵住小$L$，阻止小$C$到环上面。

小$L$为了尽快跑到环上面，他选择跑到一个环上面的点(但是并非是距离自己最近的，想一想为什么)，假设这个点为$P$，那么小$L$怎么办？显然小$L$被迫的也要跑到$P$点，不然怎么阻止小$L$上到环上面去？所以解法逐渐浮现在我们眼前。

#### ——————————————————————分割线——————————————————————

#### 上面的是对于题目的分析，要是你已经分析过了可以直接看下面的做法

首先我们要找环啊，于是$tarjan$是首选，然后我们要确定“尽快跑到环上的距离小$L$最近的一点所用的时间”，于是我们需要$Dijkstra$最短路算法，计算一下小$L$到所有点的最短距离，然后还需要计算小$C$到每一个点的最短距离，然后枚举每一个点，先判断其是否在一个环上面，然后判断一下小$L$到达它的时间是否小于小$C$到达它的时间，如果存在任意一个这样的点，输出"No"。

如果不存在这个点怎么办？

可以把小$L$和小$C$的行走过程分为$x$个回合，先让小$L$走$x$个回合，那么他最终会在一个点停下来。无论这个点是哪个点，实际上只需要计算小$C$到这个点的最短路径即可，同时请想，假若小$L$到达这个点所用的时间大于小$C$到这个点的时间，那小$L$显然无法到达这个点，所以最后的答案会是满足距离小$C$最远的且满足小$L$到这个点的距离小于小$C$到这个点的距离的点。

### ————————————————————end————————————————————
以上就是关于这道题的做法！

贴出代码
```
#include <bits/stdc++.h>
using namespace std;
#define INF 100000000
const int MAXN = 6000, MAXM = 30005;
int n,m,s,t,tot = 0,cnt = 0,now = 0,z = 0;
int dfn[MAXN],low[MAXN],siz[MAXN],color[MAXN];
int tack[MAXN],vis[MAXN],book[MAXN];//tarjan算法缩点常用数组
int start[MAXN],tag[MAXN],dis[MAXN],D1[MAXN],D2[MAXN];
//D1为小L到各点的距离，D2为小C到各点的距离,tag表示是否在环上

struct Edge {
	int next,to;
} edge[MAXM];

struct data {
	int sum,id;
	bool operator <(const data& fz) const {
		return fz.sum < sum;
	}
};

priority_queue <data> q;//上面是Dijkstra要用到的东西

void add(int from,int to);
void tarjan(int x,int fa);
void Dijkstra(int S);

int main()
{
	cin >> n >> m >> s >> t;
	for(int i = 1 ; i <= m ; i ++)
	{
		int u, v;
		cin >> u >> v;
		add(u,v);
		add(v,u);	
	}
	for(int i = 1 ; i <= n ; i ++)
		if(!dfn[i])tarjan(i,i);//tarjan
	
	for(int i = 1 ; i <= n ; i ++)
		if(siz[color[i]] > 1)tag[i] = 1;//一个点单独成环没用...
	Dijkstra(s);
	for(int i = 1 ; i <= n ; i ++)D1[i] = dis[i];
	Dijkstra(t);//跑两遍Dijkstra
	int M = -1000000;
	for(int i = 1 ; i <= n ; i ++)D2[i] = dis[i];
	int flag = 0;
	for(int i = 1 ; i <= n ; i ++)
		if(D1[i] < D2[i])
		{
			M = max(M,D2[i]);
			if(tag[i] )flag = 1;
		}
	if(flag == 1)cout <<"NO\n";
	else cout << M << endl;
	return 0;
}

void add(int from,int to)
{
	cnt ++;
	edge[cnt].to = to;
	edge[cnt].next = start[from];
	start[from] = cnt;
	return ;//前向星加边
}

void tarjan(int x,int fa)//标准的tarjan即可
{
	dfn[x] = low[x] = ++now;
	tot ++ , vis[tot] = x;
	book[x] = 1;
	for(int i = start[x] ; i ; i = edge[i].next)
	{
		int to = edge[i].to;
		if(to == fa)continue;//无向边，防止反复横跳
		if(!dfn[to])
		{
			tarjan(to,x);
			low[x] = min(low[x],low[to]);
		}
		else if(book[to]) low[x] = min(low[x],dfn[to]);
	}
	if(dfn[x] == low[x])
	{
		z ++;
		while(vis[tot + 1] != x && tot > 0)
		{
			color[vis[tot]] = z;
			siz[z] ++;
			book[tot] = 0;
			tot --;
		}
	}
	return ;
}

void Dijkstra(int S)//Dijkstra求最短路即可
{
	
	for(int i = 1 ; i <= n ; i ++)dis[i] = INF;
	dis[S] = 0;
	q.push(data {dis[S],S});
	memset(book,0,sizeof(book));
	book[S] = 1;
	while(!q.empty())
	{
		data X = q.top();
		q.pop();
		if(X.sum != dis[X.id])continue;
		book[X.id] = 1;
		int x = X.id;
		for(int i = start[x] ; i ; i = edge[i].next)
		{
			int to = edge[i].to;
			if(dis[to] > dis[x] + 1)
			{
				dis[to] = dis[x] + 1;
				if(!book[to])q.push(data {dis[to],to});
			}
		}
	}
	return ;
}
```

#### 这个题目没有很多的细节，但是注意写对基础算法！

---

## 作者：happybob (赞：1)

比较容易发现的是，由于图上不存在三元环，所以如果逃犯进了一个环，那么无论如何都抓不到了。

从 $a$ 和 $b$ 跑广搜，处理出到每个点的距离。接着找所有环即可。

不需要 Tarjan，平凡的，无向图 DFS 树上不存在横叉边，每一条返祖边对应一个简单环，全都搜出来就好了。

如果存在环上的点 $i$ 满足 $a$ 到 $i$ 距离严格小于 $b$ 到 $i$ 距离，那就抓不到。否则，输出所有 $d1_i < d2_i$ 的最大 $d2_i$ 即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cstring>
#include <queue>
#include <string>
using namespace std;

const int N = 1e5 + 5;
int n, m, a, b;
bool incircle[N];
vector<int> G[N];
int d1[N], d2[N];

void bfs(int* d, int s)
{
	queue<int> q;
	q.push(s);
	d[s] = 0;
	while (q.size())
	{
		auto u = q.front();
		q.pop();
		for (auto& j : G[u])
		{
			if (d[j] == -1)
			{
				d[j] = d[u] + 1;
				q.push(j);
			}
		}
	}
}

bool vis[N];
int dep[N];
int f[N];
void dfs(int u, int fa)
{
	vis[u] = 1;
	dep[u] = dep[fa] + 1;
	f[u] = fa;
	for (auto& j : G[u])
	{
		if (j == fa) continue;
		if (vis[j])
		{
			if (dep[j] > dep[u]) continue;
			int p = u;
			do
			{
				incircle[p] = 1;
				p = f[p];
			} while (p != j);
			incircle[j] = 1;
		}
		else dfs(j, u);
	}
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &a, &b);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	memset(d1, -1, sizeof d1);
	memset(d2, -1, sizeof d2);
	bfs(d1, a);
	bfs(d2, b);
	dfs(1, 0);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		//printf("%d %d\n", i, incircle[i]);
		if (incircle[i] && d1[i] < d2[i])
		{
			//printf("!!: %d %d\n", d1[i], d2[i]);
			printf("NO\n");
			return 0;
		}
		if (d1[i] < d2[i])
		{
			ans = max(ans, d2[i]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：A_Bit_Cold (赞：1)

这是一道图论题。

观察题目，可以发现，只要 loidc 跑到环上，那 cony 就再也抓不到他了，因为 loidc 可以一直沿着环跑。

tarjan 判环是一个很好的选择，接着用 loidc 和 cony 的位置跑单元最短路，求出他们和环的最小距离 $Dis$ 和 $Dis2$。

对于节点 $i$ 来讲，如果 $Dis_i<Dis2_i$ 并且这个点在环上的话那 loidc 就可以率先到达环上的点 $i$，cony 就抓不到他了，输出 NO。

否则，如果 $Dis_i<Dis2_i$ 且 $i$ 点不在环上的话，更新最大轮数，即在  $Dis2_i$ 轮的时候 cony 就把 loidc 抓住了，因为 loidc 即使到达了 $i$ 点，但是因为其不在环上，所以没有用，就会被 cony 抓住。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int n,m,s,t,u,v;
int dist[N],Dis[N],Dis2[N],maxn;
bool vis[N],f[N];
struct Edge{
    int next,to,c;
} edge[N];
int head[N],sumedge=0;
void add_edge(int from,int to,int c) {
	sumedge++;
    edge[sumedge].next=head[from];
    edge[sumedge].to=to;
    edge[sumedge].c=c;
    head[from]=sumedge;
}//链式前向星
struct pnode {
	int dis,obj;
	bool operator >(const pnode &x) const {
		return x.dis<dis;
	}
};
priority_queue <pnode,vector<pnode>,greater<pnode> >q;
int DFN[N],Low[N],cnt,ans,a[N],color[N],ru[N],chu[N];
vector <int> next_node[N];
stack <int> S;
bool visit[N];
bool in_stack[N];
void Dijkstra(int s,int a[]) {
	while(!q.empty()) q.pop();
	memset(dist,0x3f,sizeof(dist));
	memset(vis,0,sizeof(vis));
	dist[s]=0;
	pnode n1;
	n1.dis=0;
	n1.obj=s;
    q.push(n1);
	while(!q.empty()) {
		pnode n1=q.top();
		q.pop();
		int id=n1.obj;
		if(vis[id])
		    continue;
		vis[id]=1;
		for(int j=head[id];j;j=edge[j].next) {
		    int tmp=edge[j].to;
		    if(dist[id]+edge[j].c<dist[tmp]&&vis[tmp]==0) {
			    dist[tmp]=dist[id]+edge[j].c;
			    pnode n2;
			    n2.dis=dist[tmp];
			    n2.obj=tmp;
			    q.push(n2);
			}	
        }
	}
	for(int i=1;i<=n;i++) a[i]=dist[i];
	return;
}//最短路
void tarjan(int node,int father) {
    DFN[node]=Low[node]=++cnt;
    visit[node]=1;
    S.push(node);
    in_stack[node]=1;
    for(int i=0;i<next_node[node].size();i++) {
	    int tmp=next_node[node][i];
	    if(tmp==father) continue; 
	    if(!visit[tmp]) {
	    	visit[tmp]=1;
		    tarjan(tmp,node);
		    Low[node]=min(Low[node],Low[tmp]);
		}
		else if(in_stack[tmp]) {
		    Low[node]=min(Low[node],DFN[tmp]);
		}
	}
	if(DFN[node]==Low[node]) {
		ans++;
	    int last=S.top();
	    while(last!=node) {
	    	a[ans]++;
	    	color[last]=ans;
		    in_stack[last]=0;
		    S.pop();
		    last=S.top();
		}
		a[ans]++;
		color[S.top()]=ans;
		in_stack[S.top()]=0;
		S.pop();
	}
	return;
}//tarjan 判环
int main() {
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++) {
		cin>>u>>v;
		next_node[u].push_back(v);
		next_node[v].push_back(u);
		add_edge(u,v,1),add_edge(v,u,1);
	}
	for(int i=1;i<=n;i++) {
	    if(!visit[i]) tarjan(i,-1);//tarjan
	}
	for(int i=1;i<=n;i++) {
		if(a[color[i]]<=1) continue;//<=1 的不是环
		f[i]=1;
	}
	Dijkstra(s,Dis),Dijkstra(t,Dis2);//求最短路
	for(int i=1;i<=n;i++) {
		if(Dis[i]<Dis2[i]) {//loidc 先到
			maxn=max(maxn,Dis2[i]);//更新最大轮数
			if(f[i]) {//i 在环上
				cout<<"NO";
				return 0;
			}
		}
	}
	cout<<maxn;
	return 0;
}
```


---

## 作者：Shokuhou_Misaki (赞：1)

考虑loidc什么时候能逃脱。

当loidc在一个环上时，由于这张图里没有长度为3的环，同时无向简单图不存在长度为0或1的环，那么cony永远抓不到他，所以loidc的策略就应该是尽快跑到一个环上，如果loidc到达一个环比cony快，那么他就逃脱了。

考虑loidc无法逃脱的情况，此时他只能找一个离cony最远的地方站着等死。

如何处理在环上的点？注意到在环上的点就是双联通分量上的点，所以只需跑tarjan处理即可。

之后需要判定loidc能否比cony快的到达一个环，只需要对于每个环上的点，看loidc到它的最短路是否比cony到它的最短路更短即可，如果存在这样的点就输出NO。

同时，如果loidc跑不掉，那么也只需要找到任意一个点，且loidc到它的最短路是否比cony到它的最短路更短，此时cony到它的最短路即为答案。

至于如何处理cony和loidc的最短路，图的边权为1，只需要bfs即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename tn> void read(tn &a){
	tn f=1,x=0;char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
#define int long long
const int N=3005;
const int M=15005;
int m,n,a,b;
struct edge{
	int nex,to;
	bool b;
}e[M*2];
int cnt=1,head[N],dfn[N],low[N],num;
void add(int x,int y){
	e[++cnt].nex=head[x];
	e[cnt].to=y;
	head[x]=cnt;
}
void tarjan(int x,int in_edge){
	dfn[x]=low[x]=++num;
	for(int i=head[x];i;i=e[i].nex){
		int y=e[i].to;
		if(!dfn[y]){
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x])
			    e[i].b=e[i^1].b=1;
		}
		else if(i!=(in_edge^1))
		    low[x]=min(low[x],dfn[y]);
	}
}
int c[N],dcc,cntp[N];
void dfsdcc(int x){
	c[x]=dcc;
	cntp[dcc]++;
	for(int i=head[x];i;i=e[i].nex){
		int y=e[i].to;
		if(c[y]||e[i].b) continue;
		dfsdcc(y);
	}
}
int d[3][N];
bool v[N];
void bfs(int s,int type){
	memset(d[type],0x3f,sizeof(d[type]));
	memset(v,0,sizeof(v));
	queue<int> q;
	q.push(s);
	d[type][s]=0;
	v[s]=1;
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=e[i].nex){
			int y=e[i].to;
			if(v[y]) continue;
			v[y]=1;
			d[type][y]=d[type][x]+1;
			q.push(y);
		}
	}
}
int ans;
signed main(){
	read(n);
	read(m);
	read(a);
	read(b);
	for(int i=1;i<=m;i++){
		int x,y;
		read(x);
		read(y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++)
	    if(!dfn[i]) tarjan(i,0);
	for(int i=1;i<=n;i++)
	    if(!c[i]){
	    	++dcc;
	    	dfsdcc(i);
		}
	bfs(a,0);
	bfs(b,1);
	for(int i=1;i<=n;i++)
		if(d[0][i]<d[1][i]){
			if(cntp[c[i]]>1){
				printf("NO");
				return 0;
			}
			if(d[1][i]>ans) ans=d[1][i];
		}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：JohnChan (赞：1)

## 先跑一遍**tarjan**判环 
## 再跑两遍**最短路**  
### 为什么跑最短路呢（题目中(**假设两个人都足够聪明**)） 
#### 最后枚举每个点  
### 如果loidc到这点的距离小于cony到这点的距离  
#### 那么lodic是可以跑到这点的 
### 如果这点在环上说明lodic就可以溜cony了 
#### 否则就更新答案
```cpp
#include<bits/stdc++.h>
#define ll long long
#define maxn 3010
#define maxm 15010
using namespace std;
int n,m,a,b;
vector<int>G[maxn];
void input()
{
	scanf("%d%d%d%d",&n,&m,&a,&b);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}
stack<int>stk;
bool vis[maxn],tag[maxn];
int dfn[maxn],low[maxn],cnt;
void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++cnt;
	vis[u]=1;
	stk.push(u);
	int l=G[u].size(); 
	for(int i=0;i<l;i++)
	{
		int v=G[u][i];
		if(v==fa)continue;
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else
		if(vis[v])
		low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		int w,num=0;
		do
		{
			w=stk.top();
			stk.pop();
			vis[w]=0;
			tag[w]=1;
			num++;
		}while(w!=u);
		if(num==1)tag[w]=0;
	}
}
queue<int>q;
int dist1[maxn],dist2[maxn];
bool b1[maxn];
void spfa1(int u)
{
	memset(dist1,0x3f,sizeof(dist1));
	dist1[u]=0;
	q.push(u);
	b1[u]=1;
	while(!q.empty())
	{
		int f=q.front();
		q.pop();
		b1[f]=0;
		int l=G[f].size();
		for(int i=0;i<l;i++)
		{
			int v=G[f][i];
			if(dist1[v]>dist1[f]+1)
			{
				dist1[v]=dist1[f]+1;
				if(!b1[v])
				{
					b1[v]=1;
					q.push(v);
				}
			}
		}
	}
}
bool b2[maxn];
void spfa2(int u)
{
	memset(dist2,0x3f,sizeof(dist2));
	dist2[u]=0;
	q.push(u);
	b2[u]=1;
	while(!q.empty())
	{
		int f=q.front();
		q.pop();
		b2[f]=0;
		int l=G[f].size();
		for(int i=0;i<l;i++)
		{
			int v=G[f][i];
			if(dist2[v]>dist2[f]+1)
			{
				dist2[v]=dist2[f]+1;
				if(!b2[v])
				{
					b2[v]=1;
					q.push(v);
				}
			}
		}
	}
}
int ans;
int main()
{
	input();
	for(int i=1;i<=n;i++)
	if(!dfn[i])tarjan(i,0);
	spfa1(a);
	spfa2(b);
	for(register int i=1;i<=n;i++)
	{
		if(dist1[i]<dist2[i])
		{
			ans=max(ans,dist2[i]);
			if(tag[i])
			{
				printf("NO");
				return 0;
			}
		}
	}
	printf("%d",ans);
} 
```


---

