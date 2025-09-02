# [BalticOI 1996] A FAST JOURNEY (Day 2)

## 题目描述

一侧的交通道路连接了许多城市。城市从 $1$ 到 $n$ 编号，其中 $n$ 是城市的数量。在奇数天，车辆按照交通指示的方向行驶，在偶数天，则沿相反的方向行驶。两个城市之间的道路长度用一个整数值来衡量——从一个城市到另一个城市的旅程的持续时间（以小时为单位），它与方向无关。  

编写一个程序来查找从城市 A 到城市 B 的路线，以便尽可能快地到达城市 B。  

旅程的第一天是奇数天。一天之内的旅程不能超过十二个小时。晚上必须在一个城市度过。行程可能会在第二天继续。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 < n \le 100$，$1 \le k \le 1000$。
#### 样例说明  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/onmlfj8f.png)
#### 分值说明  
本题分值按 BOI 原题设置，**满分** $35$ 。
#### 题目说明  
来源于 Baltic Olympiad in Informatics 1996 的 [Day 2:A FAST JOURNEY](https://boi.cses.fi/files/boi1996_day2.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
1 3
6 7
1 2 9
1 6 2
1 5 10
5 4 1
4 6 2
4 3 4
2 3 5```

### 输出

```
1 5 1 10
5 4 1 1
4 3 3 4```

# 题解

## 作者：logfk (赞：11)

## 题意

题意可直接转化为：

每天共有 $12$ 个小时，每走一条路会消耗一定小时，用尽后或大于剩余时间当天将不能再走。

以及，奇数天走路的正方向，偶数天走路的反方向，求从起点到终点所用最短时间（优先天数，天数相同比较当天剩余时间）时的路径。

样例为：

第一天：$1\to5\to4$。

第二天：留在 $4$。

第三天：$4\to3$。

## 分析

如果想要保证走的时间最短，就应该使用最短路，我们从一个点出发到一个点时，以天数为第一关键字，当前天数所剩时间为第二关键字进行优先队列的标准进行 Dij，如果当前天的时间加上走这条的时间小于等于 $12$ 则可以转移，如果大于则无法转移。

但是这并不能覆盖样例的等候情况，因此我们需要判断是否能够在一个地点等一天，所以我们直接在判断之后进行一次下一天的过渡，在转移过程中记录相关信息，最后到终点时直接输出即可。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
struct node{
	int da,ti,np;
	friend bool operator < (node x,node y)
	{
		if(x.da==y.da) return x.ti>y.ti;
		return x.da>y.da;
	}
};//天数，天数相同比较时间
priority_queue<node> q;
int hpla[110],st,to[2010],nxt[2010],head[2010],val[2010],fl[2010],cnt,vis[110][2][20],pre[110],hpt[110],hpti[110];
int ansp[110],ansx[110],anst[110],ansti[110];
void addedge(int x,int y,int z,int ff)
{
	to[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
	val[cnt]=z;
	fl[cnt]=ff;//正图还是反图
}
void out(int x,int &nc)
{
//	cout<<x<<nc<<endl;
//	if(x==0) return;
	ansp[nc]=pre[x];
	ansx[nc]=x;
	anst[nc]=hpt[x];
	ansti[nc]=hpti[x];//取出路径
	nc++;
	if(pre[x]==st) return;
	out(pre[x],nc);
}
int main()
{
	int x,y,z;st=read();
	int ed=read(),n=read(),m=read();
	memset(hpt,0x3f,sizeof(hpt));
	memset(hpti,0x3f,sizeof(hpti));
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read(),z=read();
		addedge(x,y,z,1);
		addedge(y,x,z,0);
	}
	vis[st][1][0]=1;
	q.push((node){1,0,st});
	while(!q.empty())
	{
		node nq=q.top();
		q.pop();
//		cout<<nq.np<<" "<<nq.da<<" "<<nq.ti<<endl;
		if(nq.np==ed)//到了直接输出
		{
			int cc=0;
			out(nq.np,cc);
			for(int i=cc-1;i>=0;i--)
			{
				cout<<ansp[i]<<" "<<ansx[i]<<" "<<anst[i]<<" "<<ansti[i]<<endl;
			}
			return 0;
		}
		x=nq.np;
		int d=nq.da,tt=nq.ti;
		for(int i=head[x];i;i=nxt[i])
		{
			int ft=to[i],ro=val[i];
			if(tt+ro<=12)//如果一天还未结束
			{
//				cout<<ft<<" "<<ro<<endl;
				if(!vis[ft][d%2][tt+ro]&&d%2==fl[i])//当前时间没有走过
				{
					if(d<hpt[ft]||(d==hpt[ft]&&tt+ro<hpla[ft]))//剩余时间更优
					{
						pre[ft]=x;
						hpt[ft]=d;
						hpti[ft]=ro;
						hpla[ft]=ro+tt;
					}
					vis[ft][d%2][tt+ro]=1;
					q.push((node){d,tt+ro,ft});
				}
			}
		}
		if(!vis[x][(d+1)%2][0])//注意！可以选择在某个地方停留一天
		{
			q.push((node){d+1,0,x});
		}
	}
}
```


---

## 作者：caoruiqi (赞：6)

看着楼上 dalao 的最短路，本蒟蒻直接~~不会~~了，本蒟蒻只会~~爆搜~~。

# 题目简述
给定一个有向图，它的边有二特殊性质，及可在奇数天通过或在偶数天通过，以及一边只得在同一天通过。要求给出一条一天之中边权和不超过 $ 12 $ 且最短的路径。

------------

# 分析
观察数据范围，我们发现 $ n \le 100 $，直接~~暴力~~搜索。

------------

# 具体做法
对于每一条路径，记 $ tot $ 为总小时数 $ day $ 为总天数，$ time $ 为当天小时数。

那么，简单分析可得，对于一条路径上的一个点，只有两种选择：

1. 枚举与他相邻的每一条边，当 $ time + \text{边权} \le 12 $ 且当天可过，则直接继续 dfs。

2. 等待一天，继续 dfs。

存图时建议使用链式前向星，在枚举邻边时较快。

特别强调，要建 **双向边** 。

最后就是~~无脑~~ dfs 了。

------------

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int max(int a,int b){
	return a>b?a:b;
}
int min(int a,int b){
	return a<b?a:b;
}//自带min,max太慢了，小优化
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-'){
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^'0');
		c=getchar();
	}
	return x*f;
}//快读
void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return;
}//快写
int a,b,n,m,u,v,x,head[101],sum,i,cnt,ans=0x3f3f3f3f,tot,sda;//a为出发点，b为目标点，n为城市数，m为节点数，u为出发城市，v为到达城市，x为走过道路花费的时间，cnt为每一次dfs时经过的城市数，ans为最小花费小时数，tot为每一次dfs时花费的小时数，sda为最小花费时经过的城市数
bool vis[101];//标记城市是否被访问过
struct node{
	int to,nxt,num,flag;//链式前向星结构体，flag为奇偶标志
};
node e[2001];
void add(int a,int b,int c,int d){
	e[++sum].num=c;
	e[sum].to=b;
	e[sum].nxt=head[a];
	e[sum].flag=d;
	head[a]=sum;
}//链式前向星建图
struct dot{
	int fr,to,num,day;
};
dot cit[101],well[101];//按输出要求，fr为出发编号，to为到达编号，num为道路长度，day为日期
void dfs(int x,int day,int t,int skiped){//x为当前到达城市，day为日期，t为时间（当天的第几小时），skiped为停留次数
	int i;
	if(tot>ans){//一个小优化，如果当前花费时间大于当前最优解，直接return
		return ;
	}
	if(x==b){
		if(ans>tot){//更新最优解
			sda=cnt;
			ans=tot;
			for(i=1;i<=cnt;i++){
				well[i].day=cit[i].day,well[i].fr=cit[i].fr,well[i].to=cit[i].to,well[i].num=cit[i].num;
			}
		}
		return;
	}
	//当天不停留继续旅行
	for(i=head[x];i!=0;i=e[i].nxt){//遍历每一条相邻的边
		if(!vis[e[i].to]&&day%2==e[i].flag&&t+e[i].num<=12){//如果边连接的点没访问过&&当天可通行&&加上这条边后当天旅行时间<=12就访问该点
			tot+=e[i].num;//加上花费时间
			vis[e[i].to]=true;//标记访问过
			cit[++cnt].fr=x;//记录答案
			cit[cnt].to=e[i].to,cit[cnt].num=e[i].num,cit[cnt].day=day;
			dfs(e[i].to,day,t+e[i].num,0);//继续dfs
			cnt--;//回溯
			vis[e[i].to]=false;
			tot-=e[i].num;
		}
	}
	//停留一天
	tot+=24-t;//+24-t与当天时间t相加，得24小时，等于第二天0:00出发
	if(skiped<2){//若停留次数大于等于2，就不如不停
		dfs(x,day+1,0,skiped+1);//停留一天继续走
	}
	tot-=24-t;//回溯
	return ;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	a=read();
	b=read();
	n=read();
	m=read();
	for(i=1;i<=m;i++){
		u=read();
		v=read();
		x=read();
		add(u,v,x,1);//正向建一条u到v边权为x，奇数天可以通过的边
		add(v,u,x,0);//反向建一条偶数天可以通过的边
	}
	dfs(a,1,0,0);//无脑dfs
	for(i=1;i<=sda;i++){//输出
		write(well[i].fr);
		putchar(' ');
		write(well[i].to);
		putchar(' ');
		write(well[i].day);
		putchar(' ');
		write(well[i].num);
		putchar('\n');
	}
	return 0;
}
```
本蒟蒻第一篇题解，管理员大大求过！！！

最后祝大家NOIP2024 rp++！！！

---

## 作者：信息向阳花木 (赞：5)

竟然没人写 SPFA，吃我一篇！

关于 SPFA ——它死了。

我偏不信！

### 	SPFA
* 由 bellman-ford 算法优化而来。
* 只有自己被更新过的，才会去更新别的点。
* 网格图不行，容易被卡。

### 这道题

难点有两个:

1. 城市可以停留

2. 需打印路径

可以用结构体来存储每条边的信息，当走这条边的时间加上之前在本天所消耗的时间时小于 $12$ 小时，就求一下最短路。

注意可以停留，因为道路会变向，但只能停留 $1$ 天，不然又变回去了。

再用一个结构体存储路径，最后递归输出。

### 后记
（2021.12.25 手贱，把已经通过的题解不小心又提交了一遍~）

两位大佬给出了代码，把 Dijkstra 换成 SPFA 就行。

---

## 作者：_adil_ (赞：3)

这题可以很好地加深对最短路的理解。

相比板子，它有以下几点不同：

-  边的方向会改变

-  移动的时间有限制

- 要考虑停留的情况

-  需要输出方案

对此，相比传统的 $dis$ 数组，此题中需要两个维度，分别记录走到每个点最短时间的日期和小时，并且在更新时记录路径，最后递归输出即可。其中，每条边只要多加一个布尔参数，通过日期的奇偶性即可判断这个方向在这天能不能走了。

具体细节见注释！

```
#include<bits/stdc++.h>
#define N 109
#define M 1009
#define INF 0x3f3f3f3f
#define mod 998244353
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef pair<int,int> pii;
int n,m,cnt,st,en;
int head[2*M],to[2*M],nxt[2*M],val[2*M],dir[2*M],vis[N][2][59];
void add(int u,int v,int w,int d){
  to[++cnt]=v,nxt[cnt]=head[u],head[u]=cnt,val[cnt]=w,dir[cnt]=d;
}
struct node1{
  int dt,ti,id;//天数，小时数，节点编号
  friend bool operator < (const node1 &a,const node1 &b){
    if(a.dt!=b.dt)return a.dt>b.dt;
    else return a.ti>b.ti;
  }
}dis[N];
struct node2{
  int st,en,dt,len;//答案边的头，尾，天数，长度
}ans[2*M];
vector<node2> fin;
void print(int x){
  if(!ans[x].st)return;//递归输出，ans[x]表示答案路径中结尾为x的边，找它的头即可
  fin.push_back(ans[x]);
  print(ans[x].st);
}
void dij(){
  for(int i=0;i<N;i++)dis[i].dt=dis[i].ti=INF;
  priority_queue<node1> q;
  dis[st].dt=0,dis[st].ti=0;
  q.push({1,0,st});//日期从1开始
  while(!q.empty()){
    node1 now=q.top();q.pop();
    if(now.id==en){return;}//已经算到过终点，结束
    int u=now.id,nt=now.ti,nd=now.dt;
    if(vis[u][nd%2][nt])continue;
    vis[u][nd%2][nt]=1;//只关心天数奇偶性，因为第i天和第i+2天的路是一样的
    for(int i=head[u];i;i=nxt[i]){
      int v=to[i],w=val[i];
      if(nt+w<=12){//这一天能走
        if(!vis[v][nd%2][nt+w]&&nd%2==dir[i]){//这个方向能走，并且可以更新
          if(nd<dis[v].dt||(nd==dis[v].dt&&nt+w<dis[v].ti)){//时间更优
            ans[v].st=u,ans[v].en=v,ans[v].dt=nd,ans[v].len=w;
            dis[v].dt=nd,dis[v].ti=nt+w;
            q.push({nd,nt+w,v});
          }
        }
      }
    }
    if(!vis[u][(nd+1)%2][0]){//停留一天
      q.push({nd+1,0,u});
    }
  }
}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin>>st>>en;
  cin>>n>>m;
  for(int i=1;i<=m;i++){
    int u,v,w;
    cin>>u>>v>>w;
    add(u,v,w,1),add(v,u,w,0);//别连反了
  }
  dij();
  print(en);//从结尾开始找
  for(int i=fin.size()-1;i>=0;i--){
    cout<<fin[i].st<<" "<<fin[i].en<<" "<<fin[i].dt<<" "<<fin[i].len<<endl;
  }
  return 0;
}
```


---

## 作者：Kalium (赞：3)

# P7655 [BalticOI 1996 Day 2] A FAST JOURNEY题解

## 前言：

本题是一道最短路好题，想训练的可以做做，但是本蒟蒻由于太菜了，做了好久才做出来。

## 题意：

有 n 个城市 k 条道路，在奇数天的时候道路按给定的方向，在偶数天反着来，每天最多行驶 12 小时，可以在一个城市停留，求 A 到 B 的最短路径，打印出最短路径。

## 思路：

以下是堆优化的 dijktra。

既然有天和小时，必然是以天为第一关键字，小时为第二关键字建其小根堆，如果说当天走这条路的时间加上之前在本天所消耗的时间时小于 12 小时，即不满一天，那么我们再来选取最短路。

很明显，最短路肯定是先比较日期，在日期的相同时比较时间即可。

那么现在要注意一点，我们可以在一个城市停留。

既然停留，肯定只能选择停留 1 天，因为一旦停留 2 天，就又回到没停留的时候了，那么停留就没意义了。

说说打印路径。

其实吧，打印路径可以看看[这题](https://www.luogu.com.cn/problem/P1144)。

还是具体说说吧（~~就是为了凑文字~~）。

我们可以用一个结构体储存，在每次入堆的时候，将所有信息储存下来，当到达终点时，我们在递归输出即可。

本人由于手写堆，代码会比楼上长，还请多多包涵。

## 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

#define inf 0x3f3f3f3f

const int N = 1e3 + 7;

using namespace std;

int s, t;

int n, m;

bool flag[107][3][17];

struct distance {
	int ti, da;
} dis[107];

struct Remember {
	int u, v, da, w;
} mem[107];

struct Edge {
	int to, next, w, op;
} edge[N << 1];

struct node {
	int da, ti, id;
};

struct HEAP {
	int sz;
	node heap[N << 2 | 1];
	
	inline int empty() {
		return sz == 0;
	}
	
	inline node top() {
		return heap[1];
	}
	
	inline void push(node a) {
		int now = ++ sz;
		
		heap[now] = (node) {a.da, a.ti, a.id};
		
		while (now != 1) {
			int fa = now >> 1;
			
			if (heap[fa].da > heap[now].da)
				swap(heap[fa], heap[now]);
			else if (heap[fa].da == heap[now].da && heap[fa].ti > heap[now].ti)
				swap(heap[fa], heap[now]);
			else break;
			
			now = fa;
		} 
		
		return ;
	}
	
	inline void pop() {
		swap(heap[1], heap[sz]);
		sz --;
		
		int now = 1;
		
		while (now << 1 <= sz) {
			int son = now << 1;
			
			if (son + 1 <= sz) {
				if (heap[son + 1].da < heap[son].da) son ++;
				else if (heap[son + 1].da == heap[son].da && heap[son + 1].ti < heap[son].ti) son ++;
			}
			
			if (heap[son].da < heap[now].da)
				swap(heap[son], heap[now]);
			else if (heap[son].da == heap[now].da && heap[son].ti < heap[now].ti)
				swap(heap[son], heap[now]);
			else break;
		
			now = son;
		}
		
		return ;
	}
} Heap;
 
int head[107], cnt;

inline void addedge(int u, int v, int w, int op) {
	edge[++ cnt] = (Edge) {v, head[u], w, op};
	head[u] = cnt;
}

inline void print(int u, int st) {
	if (mem[u].u == st) {
		printf("%d %d %d %d\n", mem[u].u, mem[u].v, mem[u].da, mem[u].w);
		
		return ; 
	}	
	
	print(mem[u].u, st);
	
	printf("%d %d %d %d\n", mem[u].u, mem[u].v, mem[u].da, mem[u].w);
}

inline void dijkstra(int st, int fi) {
	memset(dis, inf, sizeof(dis));
	dis[st].ti = 0, dis[st].da = 0;
	
	Heap.push((node) {1, 0, st});
	
	while (! Heap.empty()) {
		node k = Heap.top();
		
		Heap.pop();
		
		//printf("%d ", k.id); 
		
		if (k.id == fi) {
			print(fi, st);
			
			return ;
		}
		
		if (flag[k.id][k.da & 1][k.ti]) continue;
		
		flag[k.id][k.da & 1][k.ti] = 1;
		
		for (int i = head[k.id]; ~i; i = edge[i].next) {
			int v = edge[i].to;
			
			if (k.ti + edge[i].w <= 12) {
				int w = k.ti + edge[i].w;
				
				if (! flag[v][k.da & 1][w] && (k.da & 1) == edge[i].op) {
					if ((k.da < dis[v].da) || (k.da == dis[v].da && w < dis[v].ti)) {
						dis[v].da = k.da;
						dis[v].ti = w;
						
						mem[v].u = k.id;
						mem[v].v = v;
						mem[v].da = dis[v].da;
						mem[v].w = edge[i].w;
                        
						Heap.push((node) {k.da, w, v});
					}
				}
			}
		}
		
		if (! flag[k.id][k.da + 1 & 1][0])
			Heap.push((node) {k.da + 1, 0, k.id});
	}
}

int main() {
	memset(head, -1, sizeof(head));
	
	scanf("%d %d", &s, &t);
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= m; i ++) {
		int u, v, w;
		
		scanf("%d %d %d", &u, &v, &w);
		
		addedge(u, v, w, 1);
		addedge(v, u, w, 0);
	}
	
	dijkstra(s, t);
	
	return 0;
} 
```

## 后记：

感谢 [flysnow](https://www.luogu.com.cn/user/238445) 大佬的教导。

$Atlantis.$

---

## 作者：Charles_with_wkc (赞：2)

# 样例：
第一天：$1 → 5 → 4$。  
第二天：$4$。  
第三天：$4 → 3$。

# 题意：
每天共有 $12$ 个小时，每走一条路会消耗一定小时，用尽后或大于剩余时间当天将不能再走。

以及，奇数天走路的正方向，偶数天走路的反方向，求从起点到终点所用最短时间（优先天数，天数相同比较当天剩余时间）时的路径。

# 分析：
如果想要保证走的时间最短，就应该使用最短路，我们从一个点出发到一个点时，以天数为第一关键字，当前天数所剩时间为第二关键字进行优先队列的标准进行 Dijkstra，如果当前天的时间加上走这条的时间小于等于 $12$ 则可以转移，如果大于则无法转移。

# Dijkstra
```cpp
void dijkstra(int sta){//sta 是天 1 
	priority_queue<node>q;
	memset(hpt,0x7f,sizeof(hpt));
	memset(hpti,0x7f,sizeof(hpti));
	q.push(node{sta,0,st});
	//初始化 
	while(!q.empty()){
		node nq=q.top();
		q.pop();
		if(nq.np==ed){
			out(nq.np);//打印 
			return ;
		}
		if(vis[nq.np][nq.day%2][nq.hour]) continue;
		vis[nq.np][nq.day%2][nq.hour]=1;
		int d=nq.day,tt=nq.hour,tmpu=nq.np;
		for(int i=head[tmpu];i;i=nxt[i]){
			int ft=to[i],ro=val[i];
			if(!vis[ft][d%2][tt+ro]&&d%2==fl[i]&&tt+ro<=12&&(d<hpt[ft]||(d==hpt[ft]&&tt+ro<hpla[ft]))){
				pre[ft]=tmpu;
				hpt[ft]=d;
				hpti[ft]=ro;
				hpla[ft]=ro+tt;
				q.push(node{d,tt+ro,ft});
			}
		}
		//模板 
		if(!vis[tmpu][(d+1)%2][0]) q.push(node{d+1,0,tmpu});
	}
	return ;
}
```
# 打印 out
两种方法。
```cpp
void out(int x){
	if(x==st) return ;
	out(pre[x]);
	cout<<pre[x]<<" "<<x<<" "<<hpt[x]<<" "<<hpti[x]<<endl;
	return ;
}
```


```cpp
void out2(int x){
	if(pre[x]==st){
		cout<<pre[x]<<" "<<x<<" "<<hpt[x]<<" "<<hpti[x]<<endl;
		return ;
	}
	out(pre[x]);
	cout<<pre[x]<<" "<<x<<" "<<hpt[x]<<" "<<hpti[x]<<endl;
	return ;
}
```

# 定义：
```cpp
const int N=2005;
struct node{
	int day,hour,np;
	friend bool operator<(node x,node y){
		return (x.day==y.day?x.hour>y.hour:x.day>y.day);
	}
};
int st,cnt,ed,n,m,u,v,k;
int hpla[N],to[N],nxt[N],head[N],val[N],fl[N],vis[N][2][25],pre[N],hpt[N],hpti[N];
void addedge(int u,int v,int w,int zf){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
	val[cnt]=w;
	fl[cnt]=zf;
	return ;
}
```

---

## 作者：Y_ATM_K (赞：2)

## 题意
- 给你一个 $n$ 个点，$m$ 条边的有向图，每隔一天所有边会反向。
- 一天只能走 12 小时。
- 求 $A$ 到 $B$ 的最短路。
- $n \le 100,m \le 1000$

## 分析
一看 $n,m$ 这么小，随便乱搞都可以过。考虑 DP。

设 $f_{i,j,k}$ 表示**能否**在第 $i$ 天走 $j$ 小时到达编号为 $k$ 的结点。

显然有 $f_{i,j,k} \Rightarrow f_{i,j+w,v},f_{i,j,k} \Rightarrow f_{i+1,0,k},f_{1,0,A}=1$，其中 $v$ 为 $k$ 在第 $i$ 天的出边，$w$ 为边权。

然后找到 $i$ 最小的 $f_{i,j,B}$ 使得 $f_{i,j,B}=1$。如果 $i$ 相同就找 $j$ 最小的。

然而题目要求输出方案，其实 DP 输出方案很简单，只需要新开一个数组 $g$，存一下当前状态的 $f$ 是由哪个状态转移过来的。递归，从末状态反推到初状态，即可输出方案。

本题 $f$ 有 3 个状态，$g$ 存 3 个值就行。

然后注意一下，由于本题没有 spj，所以(应该)是输出字典序最小的方案，解决方案是让 $g$ 存当前状态被推到的第一个状态，因为第一个推到的时间肯定最早。(我因为这个 WA 了两发)

因为最坏情况下每个点都走一天，再停一天，所以天数不超过 $2n$。

时间复杂度 $O(nm)$，空间复杂度 $O(n^2)$，实际上要乘上一个 12 的常数。~~跑得飞快~~

然后空间上 $f$ 其实可以压掉第一维，但是没有必要。(因为 $g$ 压不掉)

细节见代码。

## 代码
```cpp
#include <bits/stdc++.h>
#define N 105
using namespace std;
int n,m,S,T;
struct node {
	int v,w;
	node(int x,int y) {v=x,w=y;}
};
vector<node> head1[N],head2[N];//head1存奇数天的边，head2存偶数天的边
void init() {
	for(int i=1;i<=m;++i) {
		int s,e,w;
		scanf("%d%d%d",&s,&e,&w);
		head1[s].push_back(node(e,w));
		head2[e].push_back(node(s,w));
	}
}
bool f[N<<1][13][N];
int g[N<<1][13][N][3];
void out(int date,int tim,int now) {
	int *p=g[date][tim][now];
	if(p[0]>1||p[1]||p[2]!=S) out(p[0],p[1],p[2]);
	if(now!=p[2]) printf("%d %d %d %d\n",p[2],now,date,tim-p[1]);
	//注意如果停在原处不要输出
}
int main() {
	scanf("%d%d%d%d",&S,&T,&n,&m);
	init();
	f[1][0][S]=1;
	int ansd=0,anst=0;
	for(int i=1;i<=n<<1&&!ansd;++i) {
		for(int j=0;j<=12;++j) {
			if(f[i][j][T]) {
				ansd=i,anst=j;//如果找到答案，直接退出
				break;
			}
			for(int k=1;k<=n;++k) {
				if(!f[i][j][k]) continue;
				if(i&1) {
					int sz=head1[k].size();
					for(int l=0;l<sz;++l) {
						int v=head1[k][l].v,w=head1[k][l].w;
						if(j+w<=12&&!f[i][j+w][v]) {
							f[i][j+w][v]=1;
							g[i][j+w][v][0]=i,g[i][j+w][v][1]=j,g[i][j+w][v][2]=k;
						}
					}
				} else {
					int sz=head2[k].size();
					for(int l=0;l<sz;++l) {
						int v=head2[k][l].v,w=head2[k][l].w;
						if(j+w<=12&&!f[i][j+w][v]) {
							f[i][j+w][v]=1;
							g[i][j+w][v][0]=i,g[i][j+w][v][1]=j,g[i][j+w][v][2]=k;
						}
					}
				}
				if(!f[i+1][0][k]) {
					f[i+1][0][k]=1;
					g[i+1][0][k][0]=i,g[i+1][0][k][1]=j,g[i+1][0][k][2]=k;
					//别忘了可以不走
				}
			}
		}
	}
	out(ansd,anst,T);
	return 0;
}
```

---

## 作者：jinfanhao (赞：0)

这道题是道很好的最短路练习题。\
这题我们可以用迪杰斯特拉，把他其中的标记数组改为三维的，第一维是点的编号，第二维是当天的时间，第三维是看他是奇数天还是偶数天。\
其他的也是这样加一维或两维。\
还要记得记录路径，但要记得倒着输出，不然会全错的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+1;
struct edge{
	int v,w,dir;
};
struct node{
	int id,day,time;
	bool operator<(const node &x) const{
		if(day==x.day)return time>x.time;
		return day>x.day;
	}
};
struct point{
	int day,time;
}dist[N];
struct stu{
	int u,day,w;
}pre[N];
int n,m,st,en;
vector<edge> g[N];
bool ok[N][N][2];
void dijkstra(){
	priority_queue<node> pq;
	memset(ok,false,sizeof(ok));
	for(int i=1; i<=n; ++i){
		dist[i].day=1e18;
		dist[i].time=1e18;
	}
	dist[st].day=0;
	dist[st].time=0;
	pq.push({st,1,0});
	while(pq.size()){
		node now=pq.top();
		pq.pop();
		int u=now.id,day=now.day,time=now.time;
		if(u==en)return;  
		if(ok[u][time][day&1])continue;
		ok[u][time][day&1]=true;
		for(auto it:g[u]){
			int v=it.v,w=it.w,dir=it.dir;
			if(time+w<=12 && dir==(day&1) && !ok[v][time+w][dir] && (day<dist[v].day || day==dist[v].day && time+w<dist[v].time)){
				pre[v].day=day;
				pre[v].w=w;
				pre[v].u=u;
				dist[v].day=day;
				dist[v].time=time+w;
				pq.push({v,day,time+w});
			}
		}
		if(!ok[u][0][day+1&1])pq.push({u,day+1,0});
	}
}
void print(int op){
	if(!pre[op].u)return;
	print(pre[op].u);
	printf("%lld %lld %lld %lld\n",pre[op].u,op,pre[op].day,pre[op].w);
}
signed main(){
	scanf("%lld%lld%lld%lld",&st,&en,&n,&m);
	for(int i=1; i<=m; ++i){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		g[u].push_back({v,w,1});
		g[v].push_back({u,w,0});
	}
	dijkstra();
	print(en);
	return 0;
}
```

---

## 作者：WhiteNight__ (赞：0)

## [P7655](https://www.luogu.com.cn/problem/P7655)

### 题目大意
有很多条路，选择某一条路走都会消耗这一天中一定的时间，走一条路的充要条件是**当天已走的时间与这条路消耗时间之和小于等于 $12$ 小时**。当然，你也可以选择留在一个城市。

此外还有一条规则，奇数天时走正常的道路，偶数天时走相反的道路。

要求尽可能用短的时间从起点 $S$ 走到终点 $T$。

### 思路
要想让时间最短，首先想到最短路，时间最短时应该让天数首先最短，其次是小时数最少，那么就可以设计优先队列进行 Dijkstra 算法。
```cpp
struct Queue {
	int to , day , hour;
  
	Queue (int to_ , int day_ , int hour_):
	to(to_) , day(day_) , hour(hour_) {}
  
	bool operator < (const Queue t) const {
		if(t.day == this -> day) 
			return t.hour < this -> day;
		return t.day < this -> day;
	}
};
```
接下来思考如何进行转移。由题目可得，只有当前天数消耗时间与路径耗时之和小于等于 $12$ 小时时才可以进行转移。同时还要考虑停留城市的情况，主动停留时只停留一天，因为停留两天道路又变了，相当于没有停留（当然了消耗的时间会重置）。

最后打印路径，只需要用一个结构体记录每一个节点的前驱、当天时间、走的道路长度。在最短路跑完后用递归打印路径。

### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define MAXN 105

int s , t , n , k , cnt , head_re[MAXN] , head_un[MAXN]; // 分别记录正图和反图
struct Edge {
	int to , next , dis;
}real[MAXN<<4] , unre[MAXN<<4]; // 分别记录正图和反图

struct Queue { // 优先队列
	int to , day , hour;
	
	Queue (int to_ , int day_ , int hour_):
	to(to_) , day(day_) , hour(hour_) {}
	
	bool operator < (const Queue t) const {
		if(t.day == this -> day) 
			return t.hour < this -> day;
		return t.day < this -> day;
	}
};

struct Road { // 记录路径
	int fa , day , len;
}r[MAXN];

struct Time {
	int day , hour;
}dis[MAXN];

void add (int u , int v , int dis)
{
	if(dis > 12) // 如果这条路本身就消耗时间过长，就不必记录
		return;
	++ cnt;
	real[cnt] = {v , head_re[u] , dis};
	head_re[u] = cnt;
	// 记录正图
	unre[cnt] = {u , head_un[v] , dis};
	head_un[v] = cnt;
	// 记录反图
}

void Dijk ()
{
	bool vis[MAXN][2][14]; // 判断每个状态是否访问过
	memset (vis , false , sizeof vis);
	for(int i = 0 ; i < MAXN; i ++)
		dis[i] = {0x3f , 13};
	priority_queue <Queue> q;
	q.push(Queue(s , 1 , 0)) , dis[s] = {1 , 0};
	while (!q.empty())
	{
		const Queue t = q.top(); 
		q.pop();
		if(vis[t.to][t.day&1][t.hour])
			continue;
		vis[t.to][t.day&1][t.hour] = true;
		Edge *edge = NULL;
		int *head = NULL;
		if(t.day&1) // 单数就用正图跑
			head = head_re , edge = real;
		else head = head_un , edge = unre; // 否则就用反图
      
		for(int i = head[t.to] ; i ; i = edge[i].next)
		{
			const int to = edge[i].to , disw = edge[i].dis;
			Time &ne = dis[to];
			if(t.hour + disw <= 12) // 判断是否可以转移
				if((ne.hour > t.hour + disw && ne.day >= t.day) || ne.day > t.day)
				{ // 判断时间是否更优
					ne.hour = t.hour + disw;
					ne.day = t.day;
					if(!vis[to][ne.day&1][ne.hour])
					{
						r[to] = {t.to , ne.day , disw}; // 记录路径
						q.push(Queue(to , ne.day , ne.hour));
					}
				}
		}
		
		if(!vis[t.to][(t.day+1)&1][0]) // 判断停留的情况
			q.push(Queue(t.to , t.day+1 , 0));
	}
}

void print (int k) // 用递归打印路径
{
	if(r[k].fa != s) print (r[k].fa);
	printf("%d %d %d %d\n",r[k].fa , k , r[k].day , r[k].len);
}

int main()
{
	scanf("%d%d%d%d",&s,&t,&n,&k);
	
	for(int i = 1 ; i <= k ; i ++)
	{
		int u , v , w;
		scanf("%d%d%d",&u,&v,&w);
		add (u , v , w);
	}
	
	Dijk();
	
	print(t);
	
	return 0;
}
```

---

