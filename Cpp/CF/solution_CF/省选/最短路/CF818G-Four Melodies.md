# Four Melodies

## 题目描述

Author note: I think some of you might remember the problem "Two Melodies" from Eductational Codeforces Round 22. Now it's time to make it a bit more difficult!

Alice is a composer, and recently she had recorded two tracks that became very popular. Now she has got a lot of fans who are waiting for new tracks.

This time Alice wants to form four melodies for her tracks.

Alice has a sheet with $ n $ notes written on it. She wants to take four such non-empty non-intersecting subsequences that all of them form a melody and sum of their lengths is maximal.

Subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

Subsequence forms a melody when each two adjacent notes either differ by 1 or are congruent modulo 7.

You should write a program which will calculate maximum sum of lengths of such four non-empty non-intersecting subsequences that all of them form a melody.

## 说明/提示

In the first example it is possible to compose $ 4 $ melodies by choosing any $ 4 $ notes (and each melody will consist of only one note).

In the second example it is possible to compose one melody with $ 2 $ notes — $ {1,2} $ . Remaining notes are used in other three melodies (one note per each melody).

## 样例 #1

### 输入

```
5
1 3 5 7 9
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 3 5 7 2
```

### 输出

```
5
```

# 题解

## 作者：xtx1092515503 (赞：6)

update on 2021-1-21：

重制了全文，感谢 @George1123 帮助我发现算法的锅。（一年前的算法是有大量坑的）

现在使用的是正确算法。

同时修改为正确的 $\LaTeX$ 格式。

### 翻译

给你 $n$ 个数 $a_1 \dots a_n$，要你从这 $n$ 个数中选出 $4$ 个**互不相交**的**非空子序列**，并且要求：这些子序列中任意相邻的两个数 $a_{x_i},a_{x_{i+1}}$，都必须有 $|a_{x_i}-a_{x_{i+1}}|=1$ **或 **$a_{x_i}\equiv a_{x_{i+1}}\pmod7$。求这些子序列的长度之和的最大值。

数据范围：$4\leq n\leq 3000,1\leq a_i\leq 10^5$。

### 做法

我们考虑暴力的网络流做法：将每个位置拆点以限制只能被一条路径访问，然后在两个可以成为子序列中相邻元素的位置间连边，同时建立**伪源点**以限制只有四条路径，然后直接上最大费用最大流即可。

该做法点数是 $2n$，边数是 $n^2$，亲测过不去。考虑消减边数。

我们发现，若我们考虑“同余”的情形，则会发现每一个 $\bmod7$ 的同余类内所有东西间都是两两有单向边的。于是我们新建 $n$ 个节点表示此种类型，每个新建节点连向其后方第一个与其同余的新节点。我们发现，这样连边后，各个同余系中的元素所连成的东西互不干涉，可以被看作是形成了 $7$ 条“高速公路”。$i$ 位置的出点在此处“上高速公路”，然后在其后的任意位置都可以“下高速公路”。为了实现此功能，只需让位置 $i$ 的出点连向其之后第一个同余节点的高速公路节点，并且从位置 $i$ 的高速公路节点连向其入点即可。

我们再来看向第二个“差为一”的情形——$a_i$ 连向所有其之后值为 $a_i+1$ 和 $a_i-1$ 的位置，本质上不是还是上述的高速公路问题嘛！我们对于每个不同的值，建一条高速公路，然后 $a_i$ 在其之后第一个 $a_i+1$ 的位置上 $a_i+1$ 的高速公路，在其之后第一个 $a_i-1$ 的位置上 $a_i-1$ 的高速公路，在之后的位置随时可以下高速公路，就是这样。

于是此时就共需要 $4n$ 个节点，边数被消减到 $O(n)$。可以通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,num[3010],s;
namespace MCMF{
	const int N=15000,M=2000000;
	int head[N],cnt,dis[N],fr[N],id[N],S,T,cost;
	struct node{
		int to,next,val,cost;
	}edge[M];
	void ae(int u,int v,int w,int c){
//		printf("%d %d (%d,%d)\n",u,v,w,c);
		edge[cnt].cost=c,edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=w,head[u]=cnt++;
		edge[cnt].cost=-c,edge[cnt].next=head[v],edge[cnt].to=u,edge[cnt].val=0,head[v]=cnt++;
	}
	queue<int>q;
	bool in[N];
	bool SPFA(){
		memset(dis,-1,sizeof(dis)),dis[S]=0,q.push(S),in[S]=true;
		while(!q.empty()){
			int x=q.front();q.pop(),in[x]=false;
	//		printf("%d\n",x);
			for(int i=head[x];i!=-1;i=edge[i].next){
				if(!edge[i].val)continue;
				if(dis[edge[i].to]<dis[x]+edge[i].cost){
					dis[edge[i].to]=dis[x]+edge[i].cost,fr[edge[i].to]=x,id[edge[i].to]=i;
					if(!in[edge[i].to])in[edge[i].to]=true,q.push(edge[i].to);
				}
			}
		}
		if(dis[T]==-1)return false;
		int x=T,mn=0x3f3f3f3f;
		while(x!=S)mn=min(mn,edge[id[x]].val),x=fr[x];
		cost+=dis[T]*mn,x=T;
		while(x!=S)edge[id[x]].val-=mn,edge[id[x]^1].val+=mn,x=fr[x];
		return true;
	}
}
using namespace MCMF;
int main(){
	scanf("%d",&n),memset(head,-1,sizeof(head)),S=4*n+1,T=4*n+2,s=4*n+3,ae(S,s,4,0);
	for(int i=1;i<=n;i++)scanf("%d",&num[i]);
	for(int i=1;i<=n;i++){
//0:of the same reminder  1:of the same value  2,3: assistive nodes for a particular position
		ae(s,i+2*n,0x3f3f3f3f,0);
		ae(i+0*n,i+2*n,0x3f3f3f3f,0);
		ae(i+1*n,i+2*n,0x3f3f3f3f,0);
		ae(i+2*n,i+3*n,1,1);
		ae(i+3*n,T,0x3f3f3f3f,0);
		
		for(int j=i+1;j<=n;j++)if(num[i]-num[j]==1){ae(i+3*n,j+1*n,0x3f3f3f3f,0);break;}
		for(int j=i+1;j<=n;j++)if(num[j]-num[i]==1){ae(i+3*n,j+1*n,0x3f3f3f3f,0);break;}
		for(int j=i+1;j<=n;j++)if(num[i]%7==num[j]%7){ae(i+3*n,j+0*n,0x3f3f3f3f,0);break;}
		
		for(int j=i+1;j<=n;j++)if(num[i]%7==num[j]%7){ae(i+0*n,j+0*n,0x3f3f3f3f,0);break;}
		for(int j=i+1;j<=n;j++)if(num[i]==num[j]){ae(i+1*n,j+1*n,0x3f3f3f3f,0);break;}
	}
	while(SPFA());
	printf("%d\n",cost);
	return 0;
}
```



---

## 作者：LinkyChristian (赞：6)

审核求过

在[我的博客](https://lookcatbox.github.io/post/ti-jie-cf818g-four-melodies/)食用更佳

~~这是在咕了一周的每日总结以及一次每周总结的情况下写的题解~~

其实蛮简单的....就是没有有图的题解。

考虑每个$a_i$只能选一次的限制，这个太典了，直接拆点$in_i,out_i$，连一条容量 $1$ ,费用 $1$ 的边，走了这条边意味着选了 $a_i$ , 并且产生 $1$ 的贡献。

然后思考两个限制，相邻元素绝对值差为 $1$ ,或模 $7$ 同余。

显然有这么一种思路，从 $out_i$ 向之后所有的与它差为 $1$ 或模 $7$ 同余的点的 $in_i$ 连边，但这样边数是 $O(n^2)$ 的，显然过不了。

考虑从 $a_i$ 到 $a_j$ ，如果中间有一个一样可以到达 $a_i$ ，$a_j$ 的点 $a_k$ , 那么从 $a_i$ 到 $a_k$ ，再从 $a_k$ 到 $a_j$ 是完全可以替代 $a_i,a_j$ 的。   

因此继续拆点，将$a_i$再拆成$sub_i,mod_i$ ，用于与绝对值差为 $1$ ，以及膜 $7$ 同余的 **最近点** 连边。

具体连边像这样（容量、费用）

![](https://cdn.luogu.com.cn/upload/image_hosting/i4rq50jd.png)

然后在相邻的模 $7$ 同余的点的 $mod_i$ 之间连 $(INF，0)$ 的边（不选），在相邻的 $a_i$ 相同的点的 $sub_i$ 之间连 $(INF，0)$ 的边（这些是表示不用选自己就可以选到自己后面的）。从每个点的 $out_i$ 向之后最近的 $a_i-a_j==1$ 的点和 $a_j-a_i==1$ 的点的 $sub_i$ 连 $(INF，0)$ 的边，向之后最近的模 $7$ 同余的节点的 $mod_i$ 连 $(INF，0)$ 的边。（表示选了自己后能选后面的）

然后从源点向每个点的 $in_i$ 连 $(INF，0)$ 的边，从每个点的 $out_i$ 向汇点连 $(INF，0)$。

最后有一个子序列数量的限制，我们建一个超级源点，向源点连容量为需要的子序列数，费用为 $0$ 的边。（所以其实 $k-Melodies$ 都是能做的）

附上样例二的建图

![](https://cdn.luogu.com.cn/upload/image_hosting/t4b9w0zl.png)

~~很丑陋吧?画图画的~~

附上代码

```cpp
// Problem: CF818G Four Melodies
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF818G
// Memory Limit: 1000 MB
// Time Limit: 5000 ms
#include<bits/stdc++.h>
#define N 20010
#define M 1000010
using namespace std;
namespace MCMF{
	int cnt=1,head[N],to[M],nxt[M],val[M],flow[M];
	const int INF=0x3f3f3f3f;
	void insert(int u,int v,int f,int w){
		cnt++;
		to[cnt]=v;
		val[cnt]=w;
		flow[cnt]=f;
		nxt[cnt]=head[u];
		head[u]=cnt;
	}
	void ins(int u,int v,int f,int w) {
		insert(u,v,f,w);
		insert(v,u,0,-w);
	}
	int wat[N],dis[N],vis[N],fr[N];
	int SPFA(int ss,int tt) {
		memset(dis,-1,sizeof(dis));
		queue<int> q;
		q.push(ss),dis[ss]=0,wat[ss]=INF,vis[ss]=1;
		while(!q.empty()) {
		    int now=q.front();q.pop();
		    vis[now]=0;
		    for(int i=head[now]; i; i=nxt[i]) 
		        if(flow[i]&&dis[to[i]]<dis[now]+val[i]) {
		        	dis[to[i]]=dis[now]+val[i];
		        	fr[to[i]]=i;
		        	wat[to[i]]=min(wat[now],flow[i]);
		        	if(!vis[to[i]]) q.push(to[i]),vis[to[i]]=1;
		        }
		}
		return dis[tt]!=-1;
	}
	pair<int,int> Dinic(int ss,int tt) {
		int rf=0,rv=0;
		while(SPFA(ss,tt)) {
			rf+=wat[tt],rv+=wat[tt]*dis[tt];
			int now=tt;
			while(now!=ss) {
				flow[fr[now]]-=wat[tt];
				flow[fr[now]^1]+=wat[tt];
				now=to[fr[now]^1];
			}
		}
		return make_pair(rf,rv);
	}
}
using namespace MCMF;
int read() {
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)) f=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch)) res=res*10+ch-'0',ch=getchar();
	return f*res;
}
int S,s,T,n,num[N];
int main()
{
	n=read();s=4*n+1,T=4*n+2;
    for(int i=1; i<=n; i++) num[i]=read();
    ins(S,s,4,0);
    for(int i=1; i<=n; i++) {
    	ins(s,2*n+i,INF,0),ins(i,2*n+i,INF,0),ins(n+i,2*n+i,INF,0);
    	ins(2*n+i,3*n+i,1,1),ins(3*n+i,T,INF,0);
    	for(int j=i+1;j<=n;j++)if(num[i]-num[j]==1){ins(n*3+i,n+j,INF,0);break;}
		for(int j=i+1;j<=n;j++)if(num[j]-num[i]==1){ins(n*3+i,n+j,INF,0);break;}
		for(int j=i+1;j<=n;j++)if(num[i]%7==num[j]%7){ins(n*3+i,j,INF,0),ins(i,j,INF,0);break;}
		for(int j=i+1;j<=n;j++)if(num[i]==num[j]){ins(n+i,n+j,INF,0);break;}
    }
    cout<<Dinic(S,T).second;
    return 0;
}
```


---

## 作者：xxr___ (赞：2)

楼上都是正经的，来点不正经的，~~逃~~。

首先网络流是显然的，考虑建边如下：

建立超级源点 $s$ 超级汇点 $t$。

建立超级超级源点 $S$ 和超级超级汇点 $T$。

由于每个点只能选一次，所以把每个点拆点，拆成入点和出点，这都是套路。我们记 $i$ 的入点是 $i$ 出点是 $i + n$。

连边的时候：
1. $s→u,u\in [1,n]$ 流量是 $1$ 权值是 $0$。
2. $i→i+n,i\in [1,n]$ 流量是 $1$ 代表只能选一次，权值是 $1$ 选了有 $1$ 的贡献。
3. $i+n→t,i\in [1,n]$ 流量是 $1$ 权值是 $0$。
4. 对于每个 $i$ 找出所有满足条件的 $j$ 连 $i + n→j$ 流量是 $1$ 权值是 $0$。

这样建完会发现不对劲啊，这样直接跑最大流显然都走 $s→i→i+n→t$ 了，都走没了，题目要求只能走 $4$ 条路径，所以这个时候就可以让超级超级源点连向超级源点了，相当于把源点也拆成两个。让超级汇点连向超级超级汇点。

然后这样边数是 $O(n^2)$ 级别的，能过？

考虑优化它，其实满足条件的是一条链一样的东西，我们只需要找到它后面的几个就可以了，然后就开始考虑~~乱搞~~每次把 $i$ 连向后面前多少个分别满足绝对值等于 $1$ 的和同余的，我这里分别连了前 $5$ 个就轻松跑过去了，连少了能不能过没有测试并不知道，过了的可以在评论中踢踢我哈。

然后这样边数就降至 $O(n)$ 级别，使用 `Dinic` 总复杂度 $O(n^3)$ 但是跑不满就是了。

代码：
```cpp
#include<iostream>
#include<queue>
const int N = 8005,inf = 1e9;
#define int long long
struct edge{
	int flow,cost,to,nxt;
}e[N<<5];

int s = 0,n,cur[N],ds[N],a[N],head[N],tot = 1,sum = 0,t = N - 3,ss = N - 2,tt = N - 1;
void add(int u,int v,int w,int c){
	e[++tot].cost = c;
	e[tot].to = v;
	e[tot].flow = w;
	e[tot].nxt = head[u];
	head[u] = tot;
	e[++tot].cost = -c;
	e[tot].to = u;
	e[tot].flow = 0;
	e[tot].nxt = head[v];
	head[v] = tot;
}
bool vs[N];
bool spfa(){
	for(int i = 0;i <= tt; ++i) vs[i] = 0,cur[i] = head[i],ds[i] = -inf;
	std::queue<int> q;
	q.push(ss);ds[ss] = 0;
	while(q.size()){
		int u = q.front();q.pop();
		vs[u] = 0;
		for(int i = head[u];i;i = e[i].nxt){
			int v = e[i].to;
			if(e[i].flow > 0 && ds[v] < ds[u] + e[i].cost){
				ds[v] = ds[u] + e[i].cost;
				if(!vs[v]){
					q.push(v);
					vs[v] = 1;
				}
			}
		}
	}
	for(int i = 0;i <= tt; ++i) vs[i] = 0;
	if(ds[tt] == -inf) return false;
	return true;
}
int dfs(int x,int flow){
	if(x == tt || !flow) return flow;
//	std :: cout << x << ' ' << flow << '\n';
	vs[x] = 1;
	int used = 0;
	for(int i = cur[x];i && flow;i = e[i].nxt){
		int v = e[i].to;
		cur[x] = i;
		if(!vs[v] && (ds[v] == ds[x] + e[i].cost) && e[i].flow > 0){
			int k = dfs(v,std::min(flow,e[i].flow));
			if(!k){
				ds[v] = 0;
			}
			used += k;sum += k * e[i].cost;
			flow -= k;
			e[i].flow -= k;
			e[i^1].flow += k;
		}
	}
	vs[x] = 0;
	if(!used) vs[x] = 1;
	return used;
}
int32_t main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cin >> n;
	for(int i = 1;i <= n; ++i){
		std::cin >> a[i];
	}
	for(int i = 1;i <= n; ++i){
		add(s,i,1,0);
		add(i,i + n,1,1);
		add(i + n,t,1,0);
	}
	add(ss,s,4,0);
	add(t,tt,4,0);
	for(int i = 1;i <= n; ++i){
		int f = 0,g = 0,l = 0;
		for(int j = i + 1;j <= n; ++j){
			if(f > 5 && g > 5 && l > 5) break;
			if(a[i] == a[j] + 1 && f < 5){
				++ f;
				add(i + n,j,1,0); 
			}
			if(a[i] == a[j] - 1 && l < 5){
				++ l;
				add(i + n,j,1,0);
			}
			if((a[i] % 7 == a[j] % 7) && g < 5){
				++ g;
				add(i + n,j,1,0);
			}
		}
	}
	int ans = 0;
	while(spfa()){
		ans += dfs(ss,inf);
	}
	std::cout << sum << '\n';
	return 0;
}
```

---

## 作者：Tachibana_Kimika (赞：1)

### 题目解析

这道题要让我们求四个不相交的 melody 串的最大长度和。

首先我们可以想到一个很 naive 的思路就是把每个点先拆成入点和出点，中间连接流量和费用为 1 的边意味着一个点只能走一次，然后每个点枚举后面有哪个点可以走过去，就直接把出点连到他的入点去。这样的边数是 $O(n^2)$，结合一下本题 $n\le 3000$ 和流算法逆天的复杂度，肉眼可得不能过。

我们考虑优化建图方式，我们可以采取一个类似于电路并联的方式，对于点 $i$ ，我们先把他的出点连到下一个可扩展的点 $j$ 的入点上，这时有两条路选择，一个是走到点 $j$ 的出点去，选中这个点，另一个就是不选这个点，直接从入点走到另一个可以从点 $i$ 扩展的点去。

因为题目里 melody 串有两种扩展方式，我们分类讨论。

当同余时，先把所有同余的点的入点连到一起，意味着这些点是等价的，如果不选上一个可以选下一个那种。然后把一个点的出点连向离他最近的下一个同余点，意味着选完他可以选下一个。

当差 1 时，把所有权值相同的点的入点连到一起，意味着这些点是等价的，如果不选上一个可以选下一个那种。然后把一个点的出点连向离他最近的下一个和他差 1 的点，意味着选完他可以选下一个。注意大 1 和小 1 要连两条边。

因为两种扩展方式，所以需要三个入点，两个是扩展方式的入点，一个是有费用的边的入点。

因为要求四个 melody 串，所以建立临时源点，从源点到临时源点连一条权值为 4 的边意味着有四个流量进入图中。跑最大费用最大流即可。

省略费用流板子如下，注意要最大费用，所以把所有费用取反。

```cpp
int a[N];

inline void fake_main(){
	memset(head,-1,sizeof head);
	int n; cin>>n; s=N-1,t=N-2; int S=t-1;
	for(int i=1;i<=n;i++) cin>>a[i]; adde(s,S,2,0);
	for(int i=1;i<=n;i++){//4i是出点，4i-1是连接费用边的入点，4i-2是同余入点，4i-3是差 1 入点。
		adde(S,i*4-1,inf,0);
		adde(i*4,t,inf,0);
		adde(i*4-1,i*4,1,-1);
		adde(i*4-3,i*4-1,inf,0);
		adde(i*4-2,i*4-1,inf,0);
		for(int j=i+1;j<=n;j++)	if(a[i]==a[j]) {adde(i*4-3,j*4-3,inf,0); break;}
		for(int j=i+1;j<=n;j++)	if(a[i]-a[j]==1) {adde(i*4,j*4-3,inf,0); break;}
		for(int j=i+1;j<=n;j++) if(a[j]-a[i]==1) {adde(i*4,j*4-3,inf,0); break;}
		for(int j=i+1;j<=n;j++) if(a[i]%7==a[j]%7) {adde(i*4,j*4-2,inf,0); adde(i*4-2,j*4-2,inf,0); break;}
	}
	mcmf(); cout<<-mncos<<"\n";
}
```

---

