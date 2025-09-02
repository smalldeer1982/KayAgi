# [USACO12DEC] Milk Routing S

## 题目描述

Farmer John's farm has an outdated network of M pipes (1 <= M <= 500) for pumping milk from the barn to his milk storage tank.  He wants to remove and update most of these over the next year, but he wants to leave exactly one path worth of pipes intact, so that he can still pump milk from the barn to the storage tank.

The pipe network is described by N junction points (1 <= N <= 500), each of which can serve as the endpoint of a set of pipes.  Junction point 1 is the barn, and junction point N is the storage tank.  Each of the M bi-directional pipes runs between a pair of junction points, and has an associated latency (the amount of time it takes milk to reach one end of the pipe from the other) and capacity (the amount of milk per unit time that can be pumped through the pipe in steady state).  Multiple pipes can connect between the same pair of junction points.

For a path of pipes connecting from the barn to the tank, the latency of the path is the sum of the latencies of the pipes along the path, and the capacity of the path is the minimum of the capacities of the pipes along the path (since this is the "bottleneck" constraining the overall rate at which milk can be pumped through the path).  If FJ wants to send a total of X units of milk through a path of pipes with latency L and capacity C, the time this takes is therefore L + X/C.

Given the structure of FJ's pipe network, please help him select a single path from the barn to the storage tank that will allow him to pump X units of milk in a minimum amount of total time.




## 说明/提示

FJ wants to send 15 units of milk through his pipe network.  Pipe #1 connects junction point 1 (the barn) to junction point 2, and has a latency of 10 and a capacity of 3.  Pipes #2 and #3 are similarly defined.


The path 1->3 takes 14 + 15/1 = 29 units of time.  The path 1->2->3 takes 20 + 15/2 = 27.5 units of time, and is therefore optimal.


约翰想要通过管网运送15个单位的牛奶。管道1连接节点1（谷仓）和节点2，延迟为10，容量为3。管道2和管道3也以相似的方式来定义。


路径1->3花费14+15/1=29个单位的时间。路径1->2->3花费20+15/2=27.5个单位的时间，用时最少。


## 样例 #1

### 输入

```
3 3 15 
1 2 10 3 
3 2 10 2 
1 3 14 1 
```

### 输出

```
27 
```

# 题解

## 作者：Clare613 (赞：24)

# 建议降黄或橙 or 加强数据
## 题目大意:
就是让 $L+X/C$ 小就行了。
## 思路：
最容易想到的是 SPFA ，但因数据较小，所以 DFS 也能过，而我们的 DFS 是来找容量和延迟最小的最大值。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int v,w,fj;
};
vector<node> a[505];
int cnt[505],sum,l[505],ctn,minn=1e9;
int n,m,qwe;
bool f[505][505];
void dfs(int sum,int maxn,int now){//dfs
	if(sum+maxn>minn) return ;//剪枝
	if(now==n){
		minn=min(minn,sum+maxn);//求最小值
		return ;
	}
	for(int i=0;i<a[now].size();i++){
		if(f[now][a[now][i].v]) continue;//走过就不能走
		f[now][a[now][i].v]=1;//标记
		dfs(sum+a[now][i].w,max(maxn,a[now][i].fj),a[now][i].v);//转移
		f[now][a[now][i].v]=0;//取消标记
	}
}
int main(){
	cin>>n>>m>>qwe;
	for(int i=1;i<=m;i++){
		int x,y,z,q;
		cin>>x>>y>>z>>q;
		//建边
		a[x].push_back({y,z,floor(qwe/q)});
		a[y].push_back({x,z,floor(qwe/q)});
	}
	dfs(0,0,1);
	cout<<minn;//输出
	return 0;
}
```

---

## 作者：Eleven谦 (赞：23)

# Milk Routing S

#### 双倍经验时间

[洛谷P5837  [USACO19DEC]Milk Pumping G](https://www.luogu.com.cn/problem/P5837)

[洛谷P3063  [USACO12DEC]Milk Routing S](https://www.luogu.com.cn/problem/P3063)

#### 题目模型

给定$N$个点和$M$条边，对于每条边，给定连接的两个端点以及这条边的花费和“流量”

1. 设这条路径上所有边的花费总和为$L$

2. 设这条路径上所有边中“流量”值最小的为$C$

要求找出一条$1$到$N$的路径满足：**$L$尽可能小的同时$C$尽可能大（注意是一条路径上的L和C）**

------------
#### 解题思路

如果是单独求$L$或者$C$中的一个，那么我们很容易便能解决

但是如果要求同时维护$L$和$C$两个值，而且这两个值还是**矛盾**的，那我们怎么做呢？

（这里的矛盾指：$L$要尽量小，而同一条道路的$C$又要尽量大）

- First

首先我们先来考虑用一个最短路同时维护这两个值，但经过一番思索，我们会发现无法做到

为什么？因为这两个值矛盾啊！相矛盾的两个值怎么能在同一个最短路中解决呢？

- Second

否定了同时维护的想法，我们只能考虑分开维护，分开维护？多个最短路？

肯定也不行，为什么？维护出来的$L$、$C$**分别对应的最短路径不一定是同一条**啊！最短路径都不是同一条那$L$、$C$怎么会相对应呢？

- Third

同时维护和分开维护都不行，那怎么做？

**枚举**

什么意思？

我们要维护对应的两个值，那我们可以**枚举其中一个值，然后再在枚举的这个值的基础上去寻找对应的另一个值**呀！

怎么实现呢？

假设我们枚举$Ci$，然后跑最短路去求解对应的$Li$，在跑最短路时判断当前点$v$的$Cv$值是否小于$Ci$，如果小于那么就不管这个点（因为我们枚举的$Ci$已经是假定的最小流量值，那么所有小于$Ci$肯定没有用）

**为什么$Ci$是假定的最小流量值？不是求最大的$C$吗？**

我们不断枚举$Ci$，找到所有对应的$Li$，然后用一个$ans$来记录最终的答案，**最终找到的一定是最大的$C$和最小的$L$**


------------
#### 代码Code

- [洛谷P3063  [USACO12DEC]Milk Routing S](https://www.luogu.com.cn/problem/P3063) 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,x,u,v,w,c,tot,ans=20050206;
int dis[510005],vis[510005],head[510005],flag[510005];
priority_queue<pair<int,int> > shan;

struct node {
	int to,net,val,liu;
} e[510005];

inline void add(int u,int v,int w,int l) {
	e[++tot].to=v;
	e[tot].val=w;
	e[tot].liu=l;
	e[tot].net=head[u];
	head[u]=tot;
}

inline void dijkstra(int li) {
	for(register int i=1;i<=n;i++) {
		vis[i]=0;
		dis[i]=20050206;
	}
	dis[1]=0;
	shan.push(make_pair(0,1));
	while(!shan.empty()) {
		int xx=shan.top().second;
		shan.pop();
		if(vis[xx]) continue;
		vis[xx]=1;
		for(register int i=head[xx];i;i=e[i].net) {
			int v=e[i].to;
			if(e[i].liu<li) continue;
			if(dis[v]>dis[xx]+e[i].val) {
				dis[v]=dis[xx]+e[i].val;
				shan.push(make_pair(-dis[v],v));
			}
		}
	}
}

int main() {
	scanf("%d%d%d",&n,&m,&x);
	for(register int i=1;i<=m;i++) {
		scanf("%d%d%d%d",&u,&v,&w,&c);
		flag[i]=c;
		add(u,v,w,c);
		add(v,u,w,c);
	}
	for(register int i=1;i<=m;i++) {
		dijkstra(flag[i]);
		if(dis[n]!=20050206) ans=min(ans,dis[n]+x/flag[i]);
	}
	printf("%d",ans);
	return 0;
}
```

- [洛谷P5837  [USACO19DEC]Milk Pumping G](https://www.luogu.com.cn/problem/P5837) 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a,b,c,f,tot,ans;
int dis[100010],vis[100010],head[100010];
priority_queue<pair<int,int> > shan;

struct node {
	int to,net,liu,val;
} e[100010];

inline void add(int u,int v,int w,int l) {
	e[++tot].to=v;
	e[tot].net=head[u];
	e[tot].liu=l;
	e[tot].val=w;
	head[u]=tot;
}

inline void dijkstra(int l) {
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[1]=0;
	shan.push(make_pair(0,1));
	while(!shan.empty()) {
		int x=shan.top().second;
		shan.pop();
		if(vis[x]==1) continue;
		vis[x]=1;
		for(register int i=head[x];i;i=e[i].net) {
			int v=e[i].to;
			if(e[i].liu<l) continue;
			if(dis[v]>dis[x]+e[i].val) {
				dis[v]=dis[x]+e[i].val;
				shan.push(make_pair(-dis[v],v));
			}
		}
	}
}

int main() {
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=m;i++) {
		scanf("%d%d%d%d",&a,&b,&c,&f);
		add(a,b,c,f);
		add(b,a,c,f);
	}
	for(register int li=1;li<=1000;li++) {
		dijkstra(li);
		if(dis[n]!=0x3f) ans=max(ans,li*1000000/dis[n]);
	}
	printf("%d",ans);
	return 0;
}
```

------------

自认为讲得还是很详细的，如果还有什么不懂的欢迎留言qwq

最后，感谢一下**RHL大佬**对我的指导

------------


---

## 作者：Victorique (赞：11)

总是要有人写第一篇题解的。

首先，声明一点，这个题和最大流没有任何关系。。。就是一个最短路罢了。讨论里的那些很让人误会的，这题想最大流的思路注定毒死自己。

正解最短路了。。和-->通往奥格瑞玛的道路很像。
只不过那个题还要二分，我们这题直接枚举所有可行的流量跑spfa即可。

注释略少，因为确实没啥好说的。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define ll long long
#define rp (i-1)*n+j 
#define cp (i-1)*n+j+n*n 
#define inf 50000000
#define re register
using namespace std;
struct po{
	int nxt,to,w,dis;
};
po edge[20001];
int head[20001],dis[20001],n,m,c[20001],b[20001],minn=909909090,k,num,s,t;
inline void add_edge(int from,int to,int w,int dis)
{
	edge[++num].nxt=head[from];
	edge[num].to=to;
	edge[num].w=w;
	edge[num].dis=dis;
	head[from]=num;
}
inline void add(int from,int to,int w,int dis)
{
	add_edge(from,to,w,dis);
	add_edge(to,from,w,dis);
}
inline void spfa(int x)
{
	queue<int> q;
	memset(dis,50,sizeof(dis));
	memset(b,0,sizeof(b));
	q.push(s);
	dis[s]=0;
	b[s]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		b[u]=0;
		for(re int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].dis&&edge[i].w>=x){
				dis[v]=dis[u]+edge[i].dis;
				if(!b[v]){
					q.push(v);
					b[v]=1;
				}
			}
		}
	}
}
int main()
{
	cin>>n>>m>>k;
	for(re int i=1;i<=m;i++)
	{
		int x,y,d,l;
		cin>>x>>y>>d>>l;
		add(x,y,l,d);
		c[i]=l;
	}
	sort(c+1,c+m+1);
	s=1,t=n;
	for(re int i=1;i<=m;i++)
	{
		spfa(c[i]);
		minn=min(minn,dis[t]+k/c[i]);
	}
	cout<<minn;
}
```

---

## 作者：lzpclxf (赞：6)

[题面](https://www.luogu.org/problem/P3063)
不写篇题解对不起我那逝去的时光啊！

首先我考虑的是贪心，把每条边的权值定义为通过这条路的时间（时间算法题目中已给出），跑一边最短路即可结果样例就把我哈克了。$233$，忍住眼泪继续思考，我们可以枚举每一个容量，在该容量的制约下找最小的延迟值，很显然跑$m$ 遍$SPFA$即可。

### 细节$1$:

这题要存双向边，因为管道之间是没有方向的，如果您只存了单向边，那么恭喜您能拿到20分的好成绩!存图实现方式全靠个人喜好，我比较喜欢下边这样，当然，在$add$函数里写的长一点也完全可以。

```cpp
add(x, y, l, d), add(y, x, l, d);
```
跑$m$遍$SPFA$提一句，这个$C$数组完全可以省掉的，它存储的信息就是每条边的容量
```cpp
	for(int i = 1; i <= m; i++) {
		spfa(C[i]);
		minn = min(minn, (dis[n] + x / C[i]));
	}
```
题解中有的文章对C数组排了序，其实没有什么必要因为我们枚举了所有的容量值，排序也是找$m$遍，不排序也是找$m$遍，我们完全可以不用排序。
### 细节$2$:
要注意清空$dis$数组和$vis$ 数组

```cpp
    memset(dis, 50, sizeof(dis));
    memset(vis, 0, sizeof(vis));
```
The Last:
```cpp#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 5005;
int cnt, head[N << 1], n, m, x, minn = 0x3f3f3f3f, C[N], t, s, dis[N];
bool vis[N];
struct node{
	int nxt, to, d, w;
}e[N << 1];
int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') w = -1; ch = getchar();}
	while(isdigit(ch)) {s = s * 10 + ch - '0'; ch = getchar();}
	return s * w;
}
void add(int x, int y, int w, int d) {
	e[++cnt].nxt = head[x];
	e[cnt].to = y;
	e[cnt].w = w;
	e[cnt].d = d;
	head[x] = cnt;
}
void spfa (int ww) {
    queue<int> q;
    memset(dis, 50, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    vis[1] = 1;
    q.push(1);
    dis[1] = 0;
    while (!q.empty()) {
        int he = q.front();
        q.pop();
        vis[he] = 0;
        for (int i = head[he]; i ;i = e[i].nxt) {
            if (dis[e[i].to] > dis[he] + e[i].d && e[i].w >= ww) {
                dis[e[i].to] = dis[he] + e[i].d;
                if (!vis[e[i].to]) 
                    vis[e[i].to] = 1, q.push(e[i].to);
            }
        }
    }
}
int main() {
	n = read(), m = read(), x = read();
	for(int i = 1; i <= m; i++) {
		int x, y, d, l;
		x = read(), y = read(), d = read(), l = read();
		add(x, y, l, d), add(y, x, l, d);
		C[i] = l;
	}
	for(int i = 1; i <= m; i++) {
		spfa(C[i]);
		minn = min(minn, (dis[n] + x / C[i]));
	}
	printf("%d\n", minn);
	return 0;
}
```
谢谢收看，祝身体健康！

---

## 作者：zhengrunzhe (赞：5)

提供一个Dijkstra+Heap

很多题解都不是正解

应该枚举最小容量然后求最短路更新答案

求最短路的时候不走<最小容量的边

O(mnlog n)
```cpp
#include<queue>
#include<cstdio>
#include<utility>
#include<algorithm>
using namespace std;
typedef pair<int,int>pii;
typedef priority_queue<pii,vector<pii>,greater<pii> >heap;
const int N=510,M=510,INF=2147483647;
int n,m,cap[M],x,ans=INF;
int head[N],cnt;
struct edge
{
	int to,next,delay,capacity;
	inline edge(const int &a=0,const int &b=0,const int &c=0,const int &d=0):
		to(a),next(b),delay(c),capacity(d){}
}e[M<<1];
inline const void connect(int u,int v,int d,int c)
{
	e[++cnt]=edge(v,head[u],d,c);head[u]=cnt;
	e[++cnt]=edge(u,head[v],d,c);head[v]=cnt;
}
bool vis[N];
int dis[N];
inline const int dijkstra(int s,int t,int limit)
{
	for (int i=1;i<=n;i++)dis[i]=INF,vis[i]=0;
	heap q;q.push(make_pair(dis[s]=0,s));
	while (!q.empty())
	{
		int u=q.top().second;q.pop();
		if (vis[u])continue;vis[u]=1;
		for (int v,i=head[u];i;i=e[i].next)
			if (e[i].capacity>=limit&&dis[v=e[i].to]>dis[u]+e[i].delay)
				q.push(make_pair(dis[v]=dis[u]+e[i].delay,v));
	}
	return dis[t];
}
int main()
{
	scanf("%d%d%d",&n,&m,&x);
	for (int a,b,c,i=1;i<=m;i++)scanf("%d%d%d%d",&a,&b,&c,&cap[i]),connect(a,b,c,cap[i]);
	sort(cap+1,cap+m+1);int tot=unique(cap+1,cap+m+1)-cap-1;
	/*int l=1,r=tot;  本来想来个二分 发现不能二分
	while (l<r)
	{
		int mid=l+r>>1,d=dijkstra(1,n,cap[mid]);
		if (d^INF)l=mid+1,ans=d+x/cap[mid];
		else r=mid;
	}*/
	for (int d,i=1;i<=tot;i++)
		d=dijkstra(1,n,cap[i]),
		ans=min(ans,d^INF?d+x/cap[i]:ans);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：zhangyuhan (赞：3)

最短路的变形题。

乍一看这道题，似乎有两种权值，仿佛不可做的样子。

但是仔细观察，其中的容量只需要知道路径上的最小容量，所以我们可以考虑进行特殊处理。

枚举$m$种容量，在随之跑$m$遍$SPFA$，设定其枚举的容量为下限，这$m$遍的最短路径的每条路径的最小容量一定要$>=$这个下限，再取每一次的$L+\frac{X}{C}$的最小值即可。

**注意，因为是多次跑SPFA，所以每次都一定要记得初始化**

没了。

$AC$ $Code$

```cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 1e9;

struct edge {
	int to, cost, c;
};
std::vector<edge> G[10010];

int n, m, a[10010], d[10010], x, ans = INF;
queue<int> q;
bool exist[10010];

int spfa(int Min) {
	fill(d+1, d+1+n, INF);
	memset(exist, false, sizeof(exist));//初始化莫忘掉！
	d[1] = 0;
	q.push(1);
	exist[1] = true;
	while(!q.empty()) {
		int v = q.front();
		q.pop();
		exist[v] = false;
		for (int i=0; i<G[v].size(); i++) {
			edge e = G[v][i];
			if (d[e.to] > d[v] + e.cost && e.c >= Min) {//注意，这里一定要有e.c>=Min,因为要满足大于下限的要求
				d[e.to] = d[v] + e.cost;
				if (!exist[e.to]) {
					q.push(e.to);
					exist[e.to] = true;
				}
			}
		}
	}
	return d[n] + x / Min;//返回值要是那个式子的值，不能是最短路长度
}

int main() {
	cin >> n >> m >> x;
	for (int i=1; i<=m; i++) {
		int u, v, c;
		cin >> u >> v >> c >> a[i];
		G[u].push_back((edge){v, c, a[i]});
		G[v].push_back((edge){u, c, a[i]});
	}//读入+建图
	for (int i=1; i<=m; i++) 
		ans = min(ans, spfa(a[i]));//跑m次SPFA，并更新答案
	cout << ans << endl;//输出答案
	return 0;//完结撒花！
}
```

---

## 作者：那一条变阻器 (赞：3)

这道题可以暴力哒~

------------

我们枚举每一个出现过的容量，然后跑一次最短路，求延迟，在跑最短路的时候，如果遇到的某一个点，比我们当前枚举的那个点小，那么就直接不走这一个点，然后枚举完后，就能得到最大值了。

代码~
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int w , v;
};
int n , m , need , ans = 0x3fffffff;
int h[510] , vis[510] , dis[510];
vector<pair<int , node> > e[510];
void work(int minn){
	priority_queue<pair<int , int> > q;
	dis[1] = 0;
	q.push(make_pair(0 , 1));
	while(!q.empty()){
		int x = q.top().second;
		q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(int i = 0; i < e[x].size(); i++){
			int nx = e[x][i].first , nw = e[x][i].second.w , nv = e[x][i].second.v;
			if(nv < minn) continue;	//不满足的话就下一个 
			if(dis[nx] > dis[x] + nw){
				dis[nx] = dis[x] + nw;
				q.push(make_pair(-dis[nx] , nx));
			}
		}
	}
}
int main(){
	cin >> n >> m >> need;
	for(int i = 1; i <= m; i++){
		int a , b , c , d;
		cin >> a >> b >> c >> d;
		h[i] = d;	//记录下出现过的流量 
		e[a].push_back(make_pair(b , (node){c , d}));
		e[b].push_back(make_pair(a , (node){c , d}));
	}
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++) vis[j] = 0 , dis[j] = 0x3fffffff;	//初始化一下 
		work(h[i]);	//一个个枚举 
		ans = min(ans , dis[n] + need / h[i]);	//记得加上流量 
	}
	cout << ans;
	return 0;
}
```

三倍经验：

[P5837](https://www.luogu.com.cn/problem/P5837)

[P1462](https://www.luogu.com.cn/problem/P1462) 这道题要加个二分，其他的都差不多啦


---

## 作者：george0929 (赞：1)

按流量从大到小加边，每加一条边跑一遍单源最短路，设最短路为 $L$，新加入边流量为 $C$，则用 $L + \frac{X}{C}$ 更新答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define db double
struct edge{
	int u,v,w,lim;
}e[505];
bool cmp(edge a,edge b){
	return a.lim>b.lim;
}
vector<pair<int,int>> V[505];
queue<int> Q;
int inq[505],dis[505];
void spfa(){
	memset(dis,0x3f,sizeof(dis));
	memset(inq,0,sizeof(inq));
	dis[1]=0;
	Q.push(1);
	inq[1]=1;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		inq[u]=0;
		for(auto nx:V[u]){
			int v=nx.first,w=nx.second;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!inq[v]){
					inq[v]=1;
					Q.push(v);
				}
			}
		}
	}
} 
int main(){
	int n,m,x;
	cin>>n>>m>>x;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w>>e[i].lim;
	}
	sort(e+1,e+1+m,cmp);//排序
	db ans=1e8;
	for(int i=1;i<=m;i++){//从大到小加边
		V[e[i].u].push_back({e[i].v,e[i].w});
		V[e[i].v].push_back({e[i].u,e[i].w});
		spfa();//每次跑一遍最短路
		ans=min(ans,dis[n]+(db)x/(db)e[i].lim);//更新答案
	}
	cout<<(int)ans;
}
```

---

## 作者：zong15632539rongjuan (赞：0)

- ### 读题
给一个有 $N$ 个点和 $M$ 条边的图，约翰在图上运送 $X$ 个单位的牛奶，每条边有 $I$ 和 $J$ 两个顶点和 $L$ 和 $C$ 两个权值。求约翰沿着一条路径送牛奶花费的最少的时间，使 $L+X \div C$ 最小，向下取整到最近的整数。
- ### 算法
图论、最短路。
- ### 数据结构
这道题要使用图这个数据结构。图是一种数据结构，定义是 $graph=(V,E)$，$V$ 是顶点，$E$ 是边的集合。图有两种存储方式：邻接矩阵和邻接表。邻接矩阵是表示顶点之间相邻关系的矩阵。邻接表是把从同一个顶点发出的边连接在同一个称为边链表的单链表中。因为每条边有两个权值，所以图用邻接表存储。
#### 最短路
我们可以用 Dijstra 求最短路，这个算法的条件是权值非负。因为这道题中的权值 $L$ 和 $C$ 代表延迟值和容量值，所以不可能是负数，可以使用 Dijstra。建立两个顶点集合，一个代表已确定最短路径的顶点，一个代表未确定最短路径的顶点。已确定最短路径的顶点全部设置成 $0x3f3f3f3f$，相当于整型变量的中间值，然后选出距离源点最短的点，并把权值放在已确定最短路径的顶点集合里。然后用这个点不断松弛其他点。然后找到最短点继续重复松弛，直到找到全部最短路为止。
- ### 过程分析
	1. 用邻接表存储图。
    1. 求出约翰沿着一条路径送牛奶花费的最少的时间。
- ### 代码
```
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int max_N = 550, max_2M = 1100;
int N, M, X, I, J, L, C, head[max_N];
int e[max_2M], nxt[max_2M], val[max_2M];
int ll[max_2M], idx, temp[max_N], dist[max_N];
int vis[max_N], temp_h, ans = 0x3f3f3f3f;
void add(int x, int y, int z, int lili) {
	e[++idx] = y;
	val[idx] = z;
	ll[idx] = lili;
	nxt[idx] = head[x];
	head[x] = idx;
}
priority_queue<pair<int, int>
	, vector<pair<int, int>>
	, greater<pair<int, int>>> h;
int main() {
    scanf("%d%d%d", &N, &M, &X);
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d%d%d", &I, &J, &L, &C);
        add(I, J, L, C);
        add(J, I, L, C);
        temp[i] = C;
    }
    for (int i = 1; i <= M; ++i) {
		memset(vis, 0, sizeof(vis));
        memset(dist, 0x3f, sizeof(dist));
		dist[1] = 0;
		h.push({0, 1});
		for (int j = 1; !h.empty(); ++j) {
			temp_h = h.top().second;
			h.pop();
			if (vis[temp_h])
				continue;
			vis[temp_h] = 1;
			for(int k = head[temp_h]; k; 
				k = nxt[k]) {
				if (ll[k] < temp[i])
					continue;
				if(dist[e[k]] 
					> dist[temp_h]+val[k]) {
					dist[e[k]] = dist[temp_h]
						+val[k];
					h.push(make_pair(dist[e[k]]
						, e[k]));
				}
			}
		}
		if (dist[N] != 0x3f3f3f3f)
			ans = min(ans, dist[N] + X / temp[i]);
    }
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Weekoder (赞：0)

### 思路

和 [P5837](https://www.luogu.com.cn/problem/P5837) 很像，只不过这题要求的是最少总时间。

考虑枚举 $m$ 条边的容量作为路径上的最小容量，即“瓶颈”。跑 $m$ 遍 Dijkstra，跳过容量小于“瓶颈”的边，获取到 $dis_n$，也就是路径的延迟之和。若 $dis_n\ne+\infty$，也就是可以顺利到达终点，就记录最小值 $dis_n+\frac{X}{C}$。

注意事项：

- 需要建**双向边**。

- 在 Dij 模板的基础上，加入跳过容量小于“瓶颈”的代码。

- 注意判断 $dis_n$ 是否为 $+\infty$ 再取最小值，否则会出现错误。

# $\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 505;

struct Edge {
	int to, w, f;
};
struct node {
	int to, w;
	bool operator<(const node &x)const {
		return w > x.w;
	}
};

int n, m, dis[N], x, W[N];
bool vis[N];

vector<Edge> nbr[N];

priority_queue<node> pq;

void dijkstra(int s, int f) {
	memset(dis, 0x3f, sizeof dis);
	memset(vis, 0, sizeof vis);
	dis[s] = 0;
	pq.push((node){s, 0});
	while (!pq.empty()) {
		node now = pq.top(); pq.pop();
		int cur = now.to;
		if (vis[cur]) continue;
		vis[cur] = 1;
		for (auto nxt : nbr[cur]) {
			int to = nxt.to, w = nxt.w;
			if (nxt.f >= f && dis[to] > dis[cur] + w) {
				dis[to] = dis[cur] + w;
				pq.push((node){to, dis[to]}); 
			}
		}
	}
}

int main() {	
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 
	cin >> n >> m >> x;
	for (int i = 1, a, b, c, f; i <= m; i++) {
		cin >> a >> b >> c >> f;
		W[i] = f;
		nbr[a].emplace_back((Edge){b, c, f});
		nbr[b].emplace_back((Edge){a, c, f});
	}
	int minx = 1e9;
	for (int i = 1; i <= m; i++) {
		dijkstra(1, W[i]);
		if (dis[n] != 0x3f3f3f3f) minx = min(minx, dis[n] + x / W[i]);
	}
	cout << minx;	
	return 0;
}
```

---

## 作者：x_miracle (赞：0)


### 核心算法 Dijkstra


------------

这道题要求维护两个量，一个是容量，一个是延迟。而在Dijkstra的模板题，维护的是一个量，就是路程（此题中延迟）。

这道题中，流量，与花费的联系并不是必然的。也就是说，**不可以想当然的认为，最短路上的流量与花费的比就是所求的答案。**

那么，如何解决呢？

### 枚举，控制变量

------------

我们要维护两个值，则我们可以枚举其中一个值，然后再在去寻找对应的另一个值。

在这道题中，明显是控制容量好一些。（因为延迟不好控制）

不断枚举容量，跑出其对应的延迟，然后与先前的比较。最后得出最小的。

------------


代码如下：
```cpp
#include <bits/stdc++.h>
#define MAXN 2000005
#define INF 0x3f3f3f3f
struct EDGE{int to,nxt,late,can;}	e[MAXN];
//存图 
struct node 
{
	int pos,dis;
	bool operator < (const node & x) const	{ return x.dis < dis; }
	//重定向 
};
int adj[MAXN],cnt=0,vis[MAXN],dis[MAXN],contain[MAXN];
int n,m,x,ans=INF;
std::priority_queue < node > q;
//堆优化Dijkstra 
void addedge(int u,int v,int l,int c)
{
	e[++cnt].to=v;	e[cnt].nxt=adj[u];	e[cnt].late=l;	e[cnt].can=c;	adj[u]=cnt;
}
//链式前向星 
void Dijkstra(int mincan)
{
	//记得先清空 ，初始化 
	std::memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;++i)	dis[i]=INF;
	while(!q.empty())	q.pop(); 
	//Dijkstra
	dis[1]=0;	q.push((node) {1,0});
	while(!q.empty())
	{
		node temp=q.top();	q.pop();
		int u=temp.pos;
		if(vis[u])	continue;	vis[u]=1;
		for(int i=adj[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(mincan>e[i].can) continue;	//控制最小的容量 
			//如果下一个边的容量比最小的还小，就舍掉。 
			if(dis[v]>dis[u]+e[i].late)
			{
				dis[v]=dis[u]+e[i].late;
				if(!vis[v])
					q.push((node) {v,dis[v]});
			}
		}
	}
}
int main()
{
	std::scanf("%d%d%d",&n,&m,&x);
	for(int i=1;i<=m;++i)
	{
		int u,v,c,l;
		std::scanf("%d%d%d%d",&u,&v,&l,&c);
		addedge(u,v,l,c);	addedge(v,u,l,c);
		contain[i]=c;
	}
	for(int mincan=1;mincan<=m;++mincan)
	{
		Dijkstra(contain[mincan]);
		if(dis[n]!=INF) ans=std::min(ans,dis[n]+x/contain[mincan]);
	}
	std::printf("%d",ans);
	return 0;
}
```


---

## 作者：sunxiaofan (赞：0)

~~似乎这将是本题第一篇目前可以AC的题解~~

自从这个题被hack了之后，本题似乎变难了。那些原本的题解**好像**（我也不确定）都过不了了。

首先，这个题是一个最短路的题，可以跑spfa，与以往不同的区别就是原来的dis现在要变一变了，我用的结构体，l存延时，c存容量，dist其实没什么用，存的是走到该点已知的最短距离。判断是否更新的语句就是

```
if(dis[已知].dist>((dis[本节点].l +这条道路.l )+(x/min(dis[本节点].c,道路.c ))))
```
相信很多同学跟我一样，在第十一的点的位置上wa了。第十一点的数据如下：

```
3 3 15
1 2 4 3
1 2 1 1
2 3 1 1
```

[hack！！！](https://www.luogu.org/discuss/show/74002)见于讨论

这个数据其实是这样的：
本来跑spfa，先看1 2 4 3 ，将dis[2].dist更新为9；
然后看1 2 1 1 ，发现值为16，没有更新；
然后，看2 3 1 1 ，这时问题就出现了，因为这时路线的容量变了，如果还选第一条路，那ans就变为20了；可如果选第一条路，ans就为17，显然比第一条路更优。这其实也就是讨论中所说的 **"后效性"** 。~~（瞬间这道题变为了蓝题，因为一般人一次AC不了了）~~

于是，我们可以跑多边spfa，介于时间复杂度，我只跑了两次，一次是从1到n，一次是从n到1.

代码如下：
```
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<stack>
using namespace std;
inline int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,m,x,ans1,ans2;
int ai,bi,cur2,v1;
struct road
{
	int to,l,c;
}cur;
vector<road> v[550];
struct distance
{
	int dist,l,c;
}dis[550],cur1;
bool book[550];
queue<int> q;
void spfa(int k1)
{
	for(int i=1;i<=n;i++)//初始化
	{
		dis[i].dist =99999999;
		dis[i].c =9999999;
		dis[i].l =0;//这个必须有（为什么？这个问题留给读者思考。蒟蒻问题）
	}
	dis[k1].dist =0;
	book[k1]=1;
	q.push(k1);
	while(!q.empty() ) 
	{
		cur2=q.front() ;
		q.pop() ;
		for(int i=0;i<v[cur2].size() ;i++)
		{
			cur=v[cur2][i];
			if(dis[cur.to ].dist>((dis[cur2].l +cur.l )+(x/min(dis[cur2].c,cur.c ))))//这里是核心
			{
				
				dis[cur.to ].dist =dis[cur2].l +cur.l+(x/min(dis[cur2].c,cur.c ));
				dis[cur.to ].c =min(dis[cur2].c,cur.c );
				dis[cur.to ].l =dis[cur2].l +cur.l;
				if(!book[cur.to ])
				{
					book[cur.to ]=1;
					q.push(cur.to ); 
				}
			}
			
		}
		book[cur2]=0;
	}
}
int main()
{   
    n=read();
    m=read();
    x=read();
    for(int i=1;i<=m;i++)
    {
    	ai=read();
    	bi=read();
    	cur.l =read();
    	cur.c =read();
    	cur.to =bi;
    	v[ai].push_back(cur);
		cur.to =ai;
		v[bi].push_back(cur);  
	}
	spfa(1);
	double aaa1,aaa2;
	aaa1=dis[n].l +(x/double(dis[n].c ));
	ans1=floor(aaa1);
	spfa(n);
	aaa2=dis[1].l +(x/double(dis[1].c ));
	ans2=floor(aaa2);
	printf("%d",min(ans1,ans2));
	return 0;
}
```

好吧，说实在的，这道题的正解究竟是不是我这样做我也不知道。或许还有别的方法，但毕竟第11个数据还是很水的，这样就能过。

if（dalao还有更好的方法）
{
   请您在回复我，谢谢；
   return 0；
}


--------------------------------
Process exited after 0.000001 seconds with return value 0

请按任意键继续. . .

---

## 作者：CHGM (赞：0)

蒟蒻的第一篇题解，凑合看吧。

首先，这很明显是一个**单源最短路问题**，花费为 $l$，难点只有一个：$c$。怎么办呢？

如果样例给我们一个最小的 $c$，让我们只用管最短路的话，那么，这道题就会非常简单（废话）。但它不给（题目：怪我咯？），那我自己设一个最小的 $c$ 不就行了吗？

**最终做法：枚举 $c$，跑 dijkstra，取最小值。**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{
    int v,w,l;
};
struct node{
    int v,d;
};
int n,m,s,t,dis[100005],e[100005],d=100000000;
vector<edge> g[100005]; 
bool vis[100005];
bool cmp(node a,node b){
    return a.d>b.d;
}
void dijkstra(int x){//板子，稍微改了一下
    memset(dis,0x3f,sizeof dis);//初始化
    memset(vis,0,sizeof vis);
    priority_queue<node,vector<node>,decltype(cmp)* > q(cmp);
    dis[1]=0;
    q.push((node){1,0});
    while(q.size()){
        node t=q.top();
        q.pop();
        if(vis[t.v]==1)continue;
        vis[t.v]=1;
        for(int j=0;j<g[t.v].size();j++){
            int v=g[t.v][j].v,w=g[t.v][j].w,l=g[t.v][j].l;
            if(dis[v]>dis[t.v]+w&&l>=x){//c小于我们枚举的c才用
                dis[v]=dis[t.v]+w;
                q.push((node){v,dis[v]});
            }
        }
    }
    if(dis[n]==0x3f3f3f3f)return;
    else d=min(d,dis[n]+s/x);//取最小值
    return;
}
int main(){
    cin>>n>>m>>s;
    for(int i=1;i<=m;i++){//存图
        int x,y,z,l;
        cin>>x>>y>>z>>l;
        e[i]=l;//单独保存c
        g[x].push_back((edge){y,z,l});
        g[y].push_back((edge){x,z,l});//反向存图
    }
    for(int i=1;i<=m;i++)dijkstra(e[i]);//枚举C，跑dijkstra
    cout<<d;//输出
    return 0;
}
```
[买一送一](https://www.luogu.com.cn/problem/P5837)

---

