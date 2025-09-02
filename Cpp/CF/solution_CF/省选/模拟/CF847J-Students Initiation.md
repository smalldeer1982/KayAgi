# Students Initiation

## 题目描述

Soon the first year students will be initiated into students at the University of Berland. The organizers of the initiation come up with a program for this holiday. In their opinion, it would be good if the first-year students presented small souvenirs to each other. When they voiced this idea to the first-year students, they found out the following:

- some pairs of the new students already know each other;
- each new student agrees to give souvenirs only to those with whom they are already familiar;
- each new student does not want to present too many souvenirs.

The organizers have written down all the pairs of first-year friends who are familiar with each other and now want to determine for each new student, whom they should give souvenirs to. In their opinion, in each pair of familiar students exactly one student must present a souvenir to another student.

First year students already decided to call the unluckiest the one who will have to present the greatest number of souvenirs. The organizers in return promised that the unluckiest will be unlucky to the minimum possible degree: of course, they will have to present the greatest number of souvenirs compared to the other students, but this number will be as small as possible.

Organizers are very busy, and they asked you to determine for each pair of first-year friends who and to whom should present a souvenir.

## 样例 #1

### 输入

```
5 4
2 1
1 3
2 3
2 5
```

### 输出

```
1
1 2
2 3
3 1
5 2
```

## 样例 #2

### 输入

```
4 3
1 2
1 3
1 4
```

### 输出

```
1
1 4
2 1
3 1
```

## 样例 #3

### 输入

```
4 6
1 2
4 1
4 2
3 2
4 3
1 3
```

### 输出

```
2
1 3
2 1
2 4
3 2
4 1
4 3
```

# 题解

## 作者：xzggzh1 (赞：2)

题意：

有 $n$ 个人，$m$ 对关系，要求每对关系中，有且仅有一个人给另外一个人送礼物，并且使送出礼物最多的人送的礼物尽可能少。并输出送礼物的方案。

$n\leq 5000$。

---

由于瞄了一眼 cf 的原题 ，看到 `flow` 就没怎么想直接秒了，感觉可能浪费一道好题…

「最多的最少」 可以让我们想到二分答案，二分这个 「最少」 值。

那么二分出这个 「最少」 值 $x$ 后，直接从源点向所有的点连 $x$ 流量的边。表示这个点最多给出 $x$ 个礼物。

然后把每个点拆成出入两个点，每一个关系连一个双向的边，出的点连汇点。但是如果 $(a,b)$ 有边，不能出现 $a\to b $ 且 $b\to a $ 的情况，所以再搞一个限制把这个双向的边限制只有一个方向。

判断是否可行只要看是否流满即可。

----

核心代码：（网络流部分略去）

```cpp

int n,m,u[5555],v[5555],st,en;
bool pd(int now){
	mxfl::init();
	for (int i=1;i<=m;i++){
		mxfl::add(u[i],i+n,1);
		mxfl::add(v[i],i+n,1);
		mxfl::add(i+n,en,1);
	}
	for (int i=1;i<=n;i++)mxfl::add(st,i,now);
	return mxfl::Main()==m;
}	
int main(){
	scanf("%d%d",&n,&m);
	st=n+m+1;en=st+1;
	for (int i=1;i<=m;i++)scanf("%d%d",&u[i],&v[i]);
	int l=0,r=st,mid;
	for (;l<r;pd(mid)?r=mid:l=mid+1)mid=(l+r)>>1;
	printf("%d\n",l);
	pd(l);
	for (int i=1,id;i<=m;i++){
		id=6*i-4;
		if(mxfl::r[id].fl)printf("%d %d\n",v[i],u[i]);
		else printf("%d %d\n",u[i],v[i]);
	}
}
```


---

## 作者：UperFicial (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF847J)

同步发表于我的 [$\texttt{cnblog}$](https://www.cnblogs.com/UperFicial/p/16166996.html)。

### $\texttt{Description}$

有 $n$ 个人，$m$ 对关系，要求每对关系中，**有且仅有**一个人给另外一个人送礼物，并且使送出礼物最多的人送的礼物尽可能少。并输出送礼物的方案。

$1\le n,m\le 5\times 10^3$。

### $\texttt{Solution}$

~~这翻译全都贺出去了，全都贺出去了啊~~

仍然考虑构造一个二分图。

一开始想了一个非常 $\texttt{naive}$ 的做法，左边是送礼物的人 $i$，右边对应是收礼物的人 $i'$。

对于一个关系 $(u,v)$，如果建边方式为 $u\to v'$ 和 $v\to u'$，且容量都为 $1$，则【**有且仅有**一个人给另外一个人送礼物】这个条件是无法表示出来的。

考虑左边还是送礼物的人，右边变成方案。

考虑将一个方案表示成一个点，对于第 $i$ 个方案，我们连边 $u_i\to i$，$v_i\to i$，容量均为 $1$，然后对于每一个方案与 $t$ 连一条容量为 $1$ 的边，这样就保证两个送出礼物最终只有一个能流到 $t$。

那么对于每一个人 $i$，$s$ 和 $i$ 之间如何连边呢？

看到了【最大值尽可能小】限制，很容易想到二分，我们二分每一个最多送出的礼物数量 $k$，所以对于每一个 $i$，连一条 $s\to i$，容量为 $k$ 的边。

最后输出只需要找那些残余流量为 $0$ 的边就行了。

还有一个大坑点，调了好久：每一次跑 $\text{dinic}$ 都是需要重新建图的，所以就导致，找到正确答案后，还会重新建一些新的图，这就导致找残余容量为 $0$ 的边会找错。

所以只需要找完答案后，重新建一遍图跑一个 $\text{dinic}$ 即可。

代码：

```cpp
inline bool check(int k)
{
	remake();
	rep(i,1,m)
	{
		add_edge(nx[i],i+n,1);
		add_edge(ny[i],i+n,1);
	} 
	rep(i,1,n) add_edge(s,i,k);
	rep(i,1,m) add_edge(i+n,t,1);
	int ans(0);
	while(bfs()) ans+=dfs(s,INF);
	return ans==m&&ans;
}
int main()
{
	n=read(),m=read();
	rep(i,1,m) nx[i]=read(),ny[i]=read();
	int l=1,r=n,res(0);
	s=0,t=n+m+1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1,res=mid;
		else l=mid+1; 
	}
	printf("%d\n",res);
	check(res);
	rep(i,1,m)
	{
		bool flag(false);
		gra(j,nx[i]) if(edge[j].to==i+n&&!edge[j].flow)
		{
			printf("%d %d\n",nx[i],ny[i]);
			flag=true;
			break;
		}
		if(!flag) printf("%d %d\n",ny[i],nx[i]);
	}
	return 0;
}
```

$$\texttt{The End.by UF}$$

---

## 作者：SFlyer (赞：0)

考虑这个限制有点难刻画，那么我们就上网络流。因为是恰好一个人给另一个人，说明流的大小一定是 $m$。二分一下，设答案是 $k$，建图（上标是流量）：

- $i\stackrel{k}{\longrightarrow} T$。

- $i+n\stackrel{1}{\longrightarrow} u_i,v_i$。$i\in [1,m]$。

- $S\stackrel{1}{\longrightarrow} i+n$。$i\in [1,m]$。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e4+4;
const int inf = 2e9;

struct edge {
	int to,cap,rev;
};

int lvl[N],vis[N];
vector<edge> g[N];

void ae(int u,int v,int w){
	g[u].push_back({v,w,g[v].size()});
	g[v].push_back({u,0,g[u].size()-1});
}

void bfs(int s){
	memset(lvl,-1,sizeof lvl);
	queue<int> q;
	q.push(s),lvl[s]=0;
	while (!q.empty()){
		int u=q.front();
		q.pop();
		for (auto v : g[u]){
			if (v.cap>0 && lvl[v.to]<0){
				lvl[v.to]=lvl[u]+1;
				q.push(v.to);
			}
		}
	}
}

int dfs(int v,int t,int f){
	if (v==t) return f;
	for (int &i=vis[v]; i<g[v].size(); i++){
		edge &e=g[v][i];
		if (e.cap>0 && lvl[v]<lvl[e.to]){
			int d=dfs(e.to,t,min(f,e.cap));
			if (d>0){
				e.cap-=d,g[e.to][e.rev].cap+=d;
				return d;
			}
		}
	}
	return 0;
}

int mf(int s,int t){
	int ans=0;
	while (1){
		bfs(s);
		if (lvl[t]<0) return ans;
		memset(vis,0,sizeof vis);
		int f;
		while ((f=dfs(s,t,inf))>0) ans+=f;
	}
} 

int cnt;

void init(){
	cnt=0;
	for (int i=0; i<N; i++) g[i].clear();
}

int n,m,u[N],v[N],id[N];

bool chk(int mid){
	init();
	int S=0,T=n+1;
	cnt=n+1;
	for (int i=1; i<=n; i++){
		ae(i,T,mid);
	}
	for (int i=1; i<=m; i++){
		int in=(++cnt);
		id[i]=in;
		ae(in,u[i],1);
		ae(in,v[i],1);
		ae(S,in,1);
	}
	int ans=mf(S,T);
	if (ans==m) return 1;
	return 0;
}

void pr(){
	for (int i=1; i<=m; i++){
		auto e=g[id[i]][0];
		if (e.cap) cout<<v[i]<<" "<<u[i]<<"\n";
		else cout<<u[i]<<" "<<v[i]<<"\n";
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>m;
	for (int i=1; i<=m; i++){
		cin>>u[i]>>v[i];
	}
	int l=-1,r=m+1;
	while (l+1<r){
		int mid=l+r>>1;
		if (chk(mid)){
			r=mid;
		}
		else l=mid;
	}
	cout<<r<<"\n";
	chk(r);
	pr();
	return 0;
}
```

---

