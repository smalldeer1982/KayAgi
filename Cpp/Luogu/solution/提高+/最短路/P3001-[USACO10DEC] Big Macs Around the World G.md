# [USACO10DEC] Big Macs Around the World G

## 题目描述

Bessie 正在学习她最喜欢的科目宏观经济学，作为她最后一门学科，她将对世界各种货币的汇率进行研究。

为了让她的演讲更加生动，她会展示一个叫做 BM 的商品在全世界的相对价格。举个例子，Bessie 会通过其他国家的汇率去找到一件 BM 在一个国家的最小价值。

- 一件 BM 在美国值 $60$ 美元；
- 美元与加拿大元的汇率为 $1$ 美元换 $0.2$ 加拿大元（$1:0.2$）。
- 美元与英镑的汇率为 $1$ 美元换 $5$ 英镑（$1:5$）。
- 英镑与加拿大元的汇率为 $1$ 英镑换 $0.5$ 加拿大元（$1:0.5$）。
- 加拿大元与美元的汇率是 $5$ 美元换一加拿大元（$5:1$），Bessie 有两种方法通过货币兑换在加拿大这个国家找到一件 BM 的最低价值：

1. 拿着美元直接去加拿大，通过汇率得出一件 BM 只要 $12$ 加拿大元；
2. 拿着美元去英国，兑换为英镑后再去加拿大，得出一件 BM 要 $150$ 加拿大元。

Bessie 会选择前一种方案因为她更乐意为在加拿大买一件 BM 支付 $12$ 加元而不是 $150$ 加元。

Bessie 有 $N(1\leq N\leq 2000)$ 个国家的信息和 $M(1\leq M\leq25000)$ 种汇率，在 $i,j$ 国间的汇率表示为 $e_{ij}(0.1\leq e_{ij}\leq 10)$。

给你一个值 $V(1\leq V\leq 10^{12})$，$V$ 不一定是一个整数。$V$ 是 BM 在起始国家 A 的价格，帮助 Bessie 寻找到在 B 国 BM 最低的价格，如果不存在，则输出 $0$。

据保证答案小于 $10^{15}$，也保证所有国家都可以通过汇率将钱币转为别的国家的。

## 样例 #1

### 输入

```
3 4 60 1 2 
1 2 0.2 
1 3 5 
3 2 0.5 
2 1 5 
```

### 输出

```
12.00 
```

# 题解

## 作者：The_BJX (赞：4)

## 前言
~~瞎写了个 SPFA 就切掉了。~~  
其他题解都 WA 了。所以我写了个正确的。  




## 题意简述

求**有向图**上的最短路，路径的权值为经过的所有边的权值之和。  

有人因为没发现是有向图而 WA 掉了。

### 为什么要用 SPFA？

看到图上求权值最小的路径之类的问题时，可以很容易想到需要最短路算法。

此题的距离依照题意，就是边权的乘积。因此将松弛部分改一下即可。

因此这里的负环指的是一个**边权之积小于 1** 的环。如果一直沿着这个环走，价格就会越走越低,没有最小值（~~最后就可以白嫖了~~）。所以此题要判负环。~~然而我只会 SPFA。~~


AC 代码：
```cpp

#include <iostream>
#include <iomanip>
#include <cstring>
#include <queue>
#define ll long double//用 long double 不然会被卡精度去世
using namespace std;
const ll inf = 9982443500;
struct edge{
    int to;
    int next;
    ll w;
}edges[600000];
int head[30000];
int tot;
void add(int a, int b, ll w)
{
    edges[++tot].to=b;
    edges[tot].w=w;
    edges[tot].next=head[a];
    head[a]=tot;
}//前向星基操

int n,m,a,b;
ll v;
queue<int> sp;//SPFA 的主队列
bool in[30000];//某一个点是否现在在队列里
int count[30000];//各店入队的次数
ll dis[30000];//源点到各店的距离

void push(int x)
{
    if(!in[x])
    {
        sp.push(x);
        in[x]=true;
        count[x]++;
    }
}

bool spfa(int f)
{
    while(!sp.empty())sp.pop();
    push(f);
    dis[f]=1;
    while(!sp.empty())
    {
        int x=sp.front();
        sp.pop();
        in[x]=false;
        for (int i = head[x]; i; i=edges[i].next)
        {
            int y=edges[i].to;
            if(dis[y]>dis[x]*edges[i].w)
            {
                dis[y]=dis[x]*edges[i].w;//注意是乘积！ 
                if(!in[y])
                {
                    push(y);
                    if(count[y]>n)
                    {
                        return true;
                        //判断负环，如果入队次数大于点数说明有负环
                    }
                }
            }
        }
    }
    return false;
}

int main()
{
    
    
    cin >> n >> m >> v >> a >> b;
    for (int i = 1; i <= n; i++)
    {
        dis[i]=inf;
    }
    for (int i = 0; i < m; i++)
    {
        int u,v;
        ll w;
        cin >> u >> v >> w;
        add(u,v,w);
    }
    
    if(spfa(a))cout << 0;
    else cout << fixed << setprecision(6) << dis[b]*v;//记得乘原价
        
    
}

```

~~蒟蒻的第一篇题解求过 qwq 啊啊啊!~~

---

## 作者：Grharris (赞：2)

# 鸣谢 @Yushuotong_std
蒟蒻的第一篇题解。。。

我看到本题时第一反应是dp，但看到数据范围时就虚了

本题实际是乘法的spfa(卡精度，要开```long double```)，就是把
```
if(dis[u]>dis[v]+pic[i].dis)
```
改成
```
if(dis[u]>dis[v]*pic[i].dis)
```
然后就是判断“负环”，也就是存在进队列超过n次的要输出0.000000(样例实际应该是12.000000)

剩下的就是代码问题了(以下代码第一个点WA但本地AC,鄙人偏分过的)

```
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
struct edge
{
	int t,nxt;
	long double val; 
}pic[25100];
int cnt=1;
int head[2010];
long double val[2010];
int hs[2010];
int n,m,a,b,p0,p1;
long double v,p2;
queue<int> q;
void add(int f,int t,long double tra)
{
	pic[cnt].t=t;
	pic[cnt].val=tra;
	pic[cnt].nxt=head[f];
	head[f]=cnt;
	cnt++;
}
int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d%d%Lf%d%d",&n,&m,&v,&a,&b);
	for(int i=1;i<=n;i++)
	{
		val[i]=1e16;
	}
	val[a]=v;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%Lf",&p0,&p1,&p2);
		add(p0,p1,p2);//链星加边
	}
	q.push(a);//乘法spfa
	while(!q.empty())
	{
		int top=q.front();
		q.pop();
		for(int i=head[top];i!=-1;i=pic[i].nxt)
		{
			int to=pic[i].t;
			if(val[to]>=val[top]*pic[i].val)//关键处
			{
				hs[to]++;
				val[to]=val[top]*pic[i].val;
				q.push(to);
				if(hs[to]>=n)//这也许有点问题，详见下面
				{
					printf("0.000000");
					return 0;
				}
			}
		}
	}
	printf("%.6Lf",val[b]);
	return 0;
}
```
问题：

节点1、2、3、4，边1->2,1->4,2->3,3->2,其中2、3间构成负环
a=1，b=4
但本人写```if(hs[b]>=n)```时2、6点WA，而改成```if(hs[to]>=n)```之后就AC

## 重申一下：本题卡精，不开long double 3、5过不去

---

## 作者：_czy (赞：1)

## 分析
最短路板，每个汇率连条有向边跑最短路。

发现由于不断乘一个小于 $1$ 的数，会无限接近 $0$，也就是有负环，所以使用 spfa。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2003
#define db long double
int n,m,a,b,h[N],x,y,p[N];
db v,d[N],z;
struct edge{
	db val;
	int to,nxt;
}e[25003];
queue<int>q;
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>v>>a>>b;
	for(int i=1;i<=n;i++)d[i]=1e20;
	d[a]=v;
	for(int i=1;i<=m;i++){
		cin>>x>>y>>z;
		e[i]={z,y,h[x]},h[x]=i;
	}
	q.push(a);
	while(!q.empty()){
		x=q.front();
		q.pop();
		for(int i=h[x];i;i=e[i].nxt){
			y=e[i].to,z=d[x]*e[i].val;
			if(z<d[y]){
				d[y]=z,p[y]++;
				if(p[y]>n){
					cout<<"0.000000";
					return 0;
				}
				q.push(y);
			}
		}
	}
	printf("%.6Lf",d[b]);
}
```

---

## 作者：夢子電 (赞：1)

## **没有题解？**
蒟蒻第一篇题解就决定是——你了！（滑稽）        
由于之前做过【P1968】（[传送门(P1968)](https://www.luogu.org/problemnew/show/P1968)），所以见到本题第一反应:这不是~~动态规划~~吗？
看到数据范围：（1<=V<=1000000000000）后（崩溃）  
果断仔细看题  
发现本题原来是一道**最短路**问题,但需要**把和变成积**
```
if(l[to]>l[u]*indexx[i].to)
{
	l[to]=l[u]*indexx[i].val;//+indexx[i].val;
}
```
只有80分？  
在第3个点和第五个点卡了好久......  
## 此题要开long double！不然会卡在#3和#5！

附代码：
```
#include<bits/stdc++.h>
using namespace std;
#define N 200000
int n,m,a,b,x,y;
long double v,w;
struct node
{
	int to,next;
	long double val;
}indexx[N];
int cnt,head[N],hash[N];
void init(int x,int y,long double w)
{
	indexx[++cnt].to=y;
	indexx[cnt].next=head[x];
	indexx[cnt].val=w;
	head[x]=cnt;
}
long double l[N];
bool vis[N],flag;
void spfa()
{
	queue<int> q;
	for(int i=1;i<=n;i++)
	{
		l[i]=1e16;
	}
	l[a]=v;
	q.push(a);
	vis[a]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=indexx[i].next)
		{
			int to=indexx[i].to;
			if(l[to]>l[u]*indexx[i].val)
			{
				l[to]=l[u]*indexx[i].val;
				if(!vis[to])
				{
					q.push(to);
					vis[to]=1;
					hash[to]++;
					if(hash[to]>n)//此处判负环，如果有负环输出"0"
					{
						flag=1;
						break;
					}
				}
			}
		}
	}
	
}
int main()
{
	scanf("%d%d%Lf%d%d",&n,&m,&v,&a,&b);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%Lf",&x,&y,&w);
		init(x,y,w);//有向边
	}
	spfa();
	printf("%Lf\n",flag==1?0:l[b]);
}
```
第一次发题解，非喜勿喷  
**欢迎大佬hack数据  **  
[传送门(P3001)](https://www.luogu.org/problemnew/show/P3001)

---

## 作者：_wzx (赞：1)

## 思路

这题用的是 spfa，用 spfa 去判断负环，当存在负环时就输出 $0$，但注意 spfa 中用的是乘法，而且注意开 long double。

## code
```cpp
#include<bits/stdc++.h>
#define INF 0x7ffffffff
const int N = 25000;

using lb = long double;
using namespace std;
struct Node {
	int to,nxt;
	lb w;
}e[N<<1];
int head[N<<1],cnt=0;
lb d[N],v;
int sum[N];
int vis[N];
int n,m,a,b;
void add(int u,int v,lb w) {
	e[++cnt] = (Node){v,head[u],w};
	head[u] = cnt;
}
bool spfa(int u) {	//判负环 
	for(int i=1;i<=n;i++) d[i] = INF;
	memset(vis,0,sizeof(vis));
	vis[u] = 1;
	d[u] = 1;
	sum[u]++;
	queue<int> q;
	q.push(u);
	while(!q.empty()) {
		int f=q.front();
		q.pop();
		vis[f] = 0;
		for(int i=head[f];i;i=e[i].nxt) {
			int v=e[i].to	;
			if(d[v] > d[f]*e[i].w) {
				d[v]=d[f]*e[i].w;
				if(!vis[v]) {
					vis[v] = 1;
					sum[v]++;
					q.push(v);
					if(sum[v]>n)
						return true;
				}
			}
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>v>>a>>b;
	lb w;
	for(int i=1,u,v;i<=m;i++) {
		cin>>u>>v>>w;
		add(u,v,w);
	}
	if(spfa(a)) {
		cout<<0<<endl;
	}
	else cout << fixed << setprecision(6) << d[b]*v;
}
```

---

## 作者：Danny_chan (赞：0)

本题其实就是在求最短路，但是这题松弛时要把和改为乘积。由于可能会出现负环，所以我们要用 spfa 最短路算法。最后要注意精度问题。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,st,en,sum[30010];
vector< pair<int,long double> >a[30010];  
long double d[30010],v;//这个不要忘了开 long double 
queue<int>q;
bool f[30010];
signed main() {
	cin>>n>>m>>v>>st>>en;
	while(m--){
		int x,y;
		long double z; 
		cin>>x>>y>>z;
		a[x].push_back({y,z});//有向图 
	}
	for(int i=1;i<=n;i++){
		d[i]=1e10;
	}
	d[st]=1; 
	q.push(st);
	f[st]=true;
	while(!q.empty()){
		int t=q.front();
		q.pop();
		f[t]=false; 
		for(int i=0;i<a[t].size();i++){
			int u=a[t][i].first;
			if(d[u]>d[t]*a[t][i].second){//松弛 
				d[u]=d[t]*a[t][i].second;
				sum[u]=sum[t]+1;
				if(sum[u]>=n){//判断是否有负环 
					cout<<0<<endl;
					return 0;
				}
				if(f[u]==false){
					q.push(u);
					f[u]=true;
				}
			}
		}
	}
	printf("%.6Lf",d[en]*v); 
	return 0; 
}
```

---

## 作者：729hao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3001)

------------
## 思路
这道题一眼可以看出求最短路，只是从求和最小变成了积最小。

在这道题里，~~关于 dijstra，它死了~~。

为什么？因为这道题的权值可能小于 $1$，乘上之后会让权值变小，可以理解为经典最短路的负权边，所以用 spfa。

如果“没有最小值”，则一定出现了权值小于 $1$ 的环，可以理解为经典最短路的负环。

顺带一提，这道题卡精度，需要开 long double。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2000;
int n,m,a,b,cnt[N+5];
long double V,d[N+5];
//cnt 表示最短路经过边数；d 表示最小权值
struct edge{
	int to;
	long double val;
};
vector<edge>v[N+5];
bool f[N+5];
queue<int>q;
bool spfa(){
	int Top,u;
	for(int i=1;i<=n;i++){
		d[i]=LLONG_MAX/3;
	}
	d[a]=1;
	q.push(a);
	f[a]=1;
	while(!q.empty()){
		Top=q.front();
		q.pop();
		f[Top]=0;
		for(int i=0;i<v[Top].size();i++){
			u=v[Top][i].to;
			if(d[u]>d[Top]*v[Top][i].val){
				d[u]=d[Top]*v[Top][i].val;
				cnt[u]=cnt[Top]+1;
				if(cnt[u]>=n)return 0;
              	//因为最短路最长经过 n-1 条边，所以如果 cnt 大于 n，则说明有权值小于 1 的环
				if(!f[u]){
					q.push(u);
					f[u]=1;
				}
			}
		}
	}
	return 1;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>V>>a>>b;
	int x,y;
	long double z;
	for(int i=1;i<=m;i++){
		cin>>x>>y>>z;
		v[x].push_back({y,z});
	}
	if(spfa()){
		printf("%.6Lf",d[b]*V);
	}
	else{
		cout<<"0";
	}
	return 0;
}
/*
input:
4 5 1 1 4
1 4 0.1
1 2 0.2
2 3 9
3 4 0.1
2 4 0.2
output:
0.04
*/
```

---

## 作者：Night_sea_64 (赞：0)

这题就是一个乘法最短路。

很容易想到用 spfa 做。因为这题边权有小于 $1$ 的，所以在走的过程中 $dis$ 可能变小，所以不能用 dijkstra。

本题中的“负环”指边权的乘积小于 $1$ 的环，如果一直走这个环，答案就不断减少，趋近于 $0$。这里我用了一个办法就是判断出负环之后，将判断出的这个点的 $dis$ 值直接改为 $0$，这样一路下去其它点 $dis$ 都是 $0$，所以正好可以判断出不存在最小值的情况。

开 long double，不然精度会炸。

```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,s,t;
long double price;
struct edge{int x;long double w;};
vector<edge>v[2010];
long double d[2010];
int cnt[2010];
struct node{int x;long double d;};
void spfa()
{
    for(int i=1;i<=n;i++)d[i]=9e18;
    d[s]=price;
    queue<node>q;
    q.push({s,price});
    while(!q.empty())
    {
        int x=q.front().x;
        q.pop();
        cnt[x]++;
        if(cnt[x]>=n)d[x]=0;
        for(auto e:v[x])
            if(d[x]*e.w<d[e.x])
            {
                d[e.x]=d[x]*e.w;
                q.push({e.x,d[e.x]});
            }
    }
}
int main()
{
    cin>>n>>m>>price>>s>>t;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        long double w;
        cin>>x>>y>>w;
        v[x].push_back({y,w});
    }
    spfa();
    printf("%.8Lf\n",d[t]);
    return 0;
}
```

---

## 作者：xzy_caiji (赞：0)

让我来介绍一下 SPFA 的 dfs 版！

SPFA 的 bfs 版一般跑的比 dfs 版快，

但是如果是网格图或者特殊构造的数据 SPFA 的 dfs 版就快到飞起。

判负环？更加简单，开个数组判断一下是否在递归栈中就完成了（注意要回溯）。

这道题卡精度，得用 `long double`。

更离谱的是，这道题还是单向汇率……

记住，浮点数数组千万不能用 `memset()`，会疯狂 RE！我已经被坑过两遍了……


```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n,m,head[2005],vet[25005],nxt[25005],en;long double wei[25005],dis[2005],v;bool vis[2005],flag;
void addedge(int u,int v,long double w){
	vet[++en]=v,nxt[en]=head[u],head[u]=en,wei[en]=w;
}
void SPFA(int u){                 //当前搜到u
	vis[u]=1;                   //设当前节点在递归栈中（其实就是记录当前路径中有没有经过这个点）
	for(int i=head[u];i;i=nxt[i]){
		int v=vet[i];
		if(dis[v]>dis[u]*wei[i]){
			if(vis[v]){flag=1;return;} //若v点已在递归栈中，则出现负环
			dis[v]=dis[u]*wei[i];
			SPFA(v);
		}
	}
	vis[u]=0;                   //将u退栈
}
int main(){
	cin>>n>>m>>v>>a>>b;
	for(int i=0;i<m;i++){
		int s,e;long double t;
		cin>>s>>e>>t;
		addedge(s,e,t);
	}
	for(int i=0;i<=2003;i++)dis[i]=1e9;
	dis[a]=1;
	SPFA(a);
	cout<<fixed<<setprecision(6)<<(flag?0:dis[b]*v);
	return 0;
}
```
代码短跑得还快，喜提最优解第一！！！！！

upd 2024.2.1：半年后看我的第一篇题解……膜拜后来超过我的三位大佬（几乎已经比我快一倍了。。。）

---

## 作者：Lonely_NewYear (赞：0)

# 洛谷 P3001 题解

## 题目分析

最短路，只是边权和之前的意义不一样了。

现在的 $dis_i$ 表示这个物品 BM 在 $i$ 国最少花多少 $i$ 国币能买到。$w_{i,j}$ 则表示从 $i$ 国到 $j$ 国后所用钱数的变化。如何变化呢？根据样例，很容易发现如果经过边 $i,j$，则 $dis_j=dis_i\times w_{i,j}$。然后跑一遍最短路就行了。注意起始点的 $dis$ 是 $v$。

还要注意判负环和不连通的情况。（负环的意义也不一样了，现在负环指的这个环的边权的乘积小于 $1$）

注意精度，double 过不了。

```cpp
#include<cstdio>
#include<queue>
using namespace std;
struct edge
{
	int v,next;
	long double w;
}g[25001];
int head[2001],cnt,num[2001],n,m,s,t;
long double v,dis[2001];
void add(int x,int y,long double w)
{
	cnt++;
	g[cnt].v=y;
	g[cnt].w=w;
	g[cnt].next=head[x];
	head[x]=cnt;
}
bool spfa()
{
	for(int i=1;i<=2000;i++)
	{
		dis[i]=1e15;
	}
	dis[s]=v;
	bool vis[2001]={0};
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=g[i].next)
		{
			int y=g[i].v;
			long double w=g[i].w;
			if(dis[x]*w<dis[y])
			{
				dis[y]=dis[x]*w;
				num[y]++;
				if(num[y]>=n)
				{
					return true;
				}
				if(!vis[y])
				{
					q.push(y);
					vis[y]=1;
				}
			}
		}
	}
	return false;
}
int main()
{
	scanf("%d%d%Lf%d%d",&m,&n,&v,&t,&s);
	for(int i=1;i<=m;i--)
	{
		int x,y;
		long double w;
		scanf("%d%d%Lf",&x,&y,&w);
		add(x,y,w);
	}
	if(spfa()||dis[t]==1e15)
	{
		printf("0.000000");
	}
	else
	{
		printf("%.6Lf",12);
	}
	return 0;//请勿抄袭
}
```

谢谢观看！

---

