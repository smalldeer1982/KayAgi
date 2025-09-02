# Flights

## 题目描述

LiLand 是一个由 $n$ 个城市组成的国家。城市从 $1$ 到 $n$ 编号。LiLan奇特的交通系统闻名天下。它的城市由许多单向航线连接，但是航线特殊的安排的方案导致：一旦离开某个城市，你就不可能再回来了。

从前，每条航线的航程一小时。但最近 Lily 成为了该国交通系统的新经理。她想把一些航线的航程改为 $2$ 小时，使得所有从城市 $1$ 到城市 $n$ 的路线的总航程都相同。

你的任务是帮助 Lily 改变航线的航程。

## 样例 #1

### 输入

```
3 3
1 2
2 3
1 3
```

### 输出

```
Yes
1
1
2
```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
1 4
```

### 输出

```
No
```

## 样例 #3

### 输入

```
5 6
1 2
2 3
3 5
1 4
4 5
1 3
```

### 输出

```
Yes
1
1
1
2
1
2
```

# 题解

## 作者：itisover (赞：29)

关于此题有一种精简的写法。

首先我们分析题面，可以发现如果最后可以达到使 $1$ 到 $n$ 的路径距离都相等，那么从 $1$ 到任意一个 $1$ 到 $n$ 的路径上的节点的路径也都相等。所以我们设 $dis[u]$ 为 $1$ 到 点 $u$ 的路径长度，$dis[v]$ 为 $1$ 到 $u$ 点连向的那个点的路径长度。因为边权要么为 $1$ 要么为 $2$，所以我们可以得到：$1 \leq dis[v]-dis[u] \leq 2$，即 $\begin{cases}dis[v]\leq dis[u]+2 \\ dis[u] \leq dis[v]-1 \end{cases}$ 。

所以我们就建一条 $u$ 到 $v$ 的边权为 $2$ 的边，建一条 $v$ 到 $u$ 的边权为 $-1$ 的边，然后就可以跑最短路求解出答案了（注意要判负环无解的情况）。

这里其实没必要去跑 $spfa$，因为 $n,m$ 都很小，且 $spfa$ 找负环的时间复杂度是 $O(nm)$ 的，所以我用了只有五行的 $Bellman-Ford$ 算法，时间复杂度为 $O(nm+m)$。

但是对于不在 $1$ 到 $n$ 路径上的点，我们需要找出来并不管他们，我就用了一遍 $dfs$ 解决了，没必要建反图跑两遍 $dfs$ 再来找打了两次标记的点。

代码精简，运行也快，因为 $spfa$ 在随机数据下的 $O(km)$ 复杂度，所以还是略慢于跑了两遍 $dfs$ 的 $spfa$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
  int ans=0,f=1;char ch=getchar();
  while(!isdigit(ch)){if(ch=='-') f=-f;ch=getchar();}
  while(isdigit(ch)){ans=(ans<<1)+(ans<<3)+ch-48;ch=getchar();}
  return ans*f;
}
const int N=5005;
int n,m;
int tag[N],vis[N];
int hd[N],nx[N],to[N],from[N],tot;
void adde(int u,int v){
  nx[++tot]=hd[u];to[tot]=v;hd[u]=tot,from[tot]=u;
}
int hd2[N],nx2[N<<1],to2[N<<1],tot2,val[N<<1],from2[N<<1];
void adde2(int u,int v,int w){
  nx2[++tot2]=hd2[u];to2[tot2]=v;hd2[u]=tot2,val[tot2]=w,from2[tot2]=u;
}
void dfs(int u){
  if(u==n) return;
  for(int i=hd[u];i;i=nx[i]){
    int v=to[i];
    if(!vis[v]) vis[v]=1,dfs(v);
    if(tag[v]) tag[u]=1;
  }
}
int dis[N];
int main(){
  n=read(),m=read();
  for(int i=1;i<=m;i++){
    int x=read(),y=read();
    adde(x,y);
  }
  tag[n]=1;
  dfs(1);
  for(int i=1;i<=m;i++){
    if(tag[from[i]]&&tag[to[i]]){
      adde2(from[i],to[i],2);
      adde2(to[i],from[i],-1);
    }
  }
  memset(dis,0x7f,sizeof(dis));
  dis[1]=0;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=tot2;j++)
      dis[to2[j]]=min(dis[to2[j]],dis[from2[j]]+val[j]);
  for(int i=1;i<=tot2;i++)
    if(dis[from2[i]]+val[i]<dis[to2[i]]) return printf("No\n"),0;
  printf("Yes\n");
  for(int i=1;i<=m;i++){
    if(tag[from[i]]&&tag[to[i]]) printf("%d\n",dis[to[i]]-dis[from[i]]);
    else printf("1\n");
  }
  return 0;
}
```



---

## 作者：Kendrick_Z (赞：7)

### (upd:更新了图片!!!)

好题啊！

这题一开始难住了我

想了好久

一开始以为是二分一下 判断

但是check想了半天没想出来怎么写

看了dalao的博客才发现这是一道差分约束题！！！！

首先我们发现 这个题的m==5000而n==1000

那么一定会有环和不必要的边

不必要的边指的是在1-n的路径上一定不会经过的边（DAG）

考虑删除这些无用的建一张新图

所以从1号节点一遍dfs再从n号节点dfs

这题有一个小性质

从1号节点到任意一个节点 的路径一定相同：

简单口胡一下：

![](https://cdn.luogu.com.cn/upload/pic/69864.png)

很显然 如果1-2-4-6的长度与1-3-5-6长度不等

那么一定不满足



对于这种情况也是一样
![](https://cdn.luogu.com.cn/upload/pic/69865.png)

会存在不满足的情况

所以有了这个性质，再结合条件

我们可以列出差分约束的条件

1<=dis[u]-dis[v]<=2

然后移项

跑差分约束

[想学差分约束？](https://www.luogu.org/blog/Kenrick/ci-fen-yue-shu-ji-tong)

由于我们可以确定路径长度唯一，所以正确性就可以保证了

关于为什么要去掉不经过的点？

不经过的点的父亲节点会和他组成一个约束关系 而这个约束关系对于题目是不必要的 就会GG

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){ 
		   f=-1;			 
	   }
	   ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct edge{
	int nxt,to,w;
}e1[N<<1],e2[N<<1],e[N<<1];
int n,m,cnt1,head2[N],from[N],to[N],dis[N],num[N],head1[N],cnt2,cnt,head[N];
inline void add1(int x,int y){
	e1[++cnt1].nxt=head1[x];
	e1[cnt1].to=y;
	head1[x]=cnt1;
} 
inline void add2(int x,int y){
	e2[++cnt2].nxt=head2[x];
	e2[cnt2].to=y;
	head2[x]=cnt2;
}
inline void add3(int x,int y,int w){
	e[++cnt].nxt=head[x];
	e[cnt].w=w;
	e[cnt].to=y;
	head[x]=cnt;
} 
bool vis[N],mar[N],sign[N];
inline void dfs1(int x){
	for(int i=head1[x];i;i=e1[i].nxt){
		int y=e1[i].to;
		if(vis[y]) continue;
		vis[y]=1;
		dfs1(y); 
	}
}
inline void dfs2(int x){
	for(int i=head2[x];i;i=e2[i].nxt){
		int y=e2[i].to;
		if(mar[y]) continue;
 		mar[y]=1;
 		dfs2(y);
	}
}
inline void spfa(){
	queue<int>q;
	memset(vis,0,sizeof(vis));
	memset(dis,-0x3f3f3f3f,sizeof(dis));
	q.push(1);
	vis[1]=1;
	dis[1]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]<dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w; 
				if(!vis[v]){
					q.push(v);
					num[v]++;
				}			
				if(num[v]>n){
					puts("No");
					exit(0);
				}		 
			}
		}
	} 
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read(),v=read();
		add1(u,v); 
		add2(v,u);
		from[i]=u;
		to[i]=v;
	} 
	dfs1(1);
	dfs2(n);
	for(int i=1;i<=n;i++){
		if(vis[i]&&mar[i]){
			sign[i]=1;
		}
	}
	sign[1]=1,sign[n]=1; 
	for(int i=1;i<=m;i++){
		if(sign[from[i]]&&sign[to[i]]){
			add3(from[i],to[i],1);
			add3(to[i],from[i],-2);
		}	
	}
	spfa();
	puts("Yes");
 	for(int i=1;i<=m;i++){
		if(sign[from[i]]&&sign[to[i]]){
			printf("%d\n",dis[to[i]]-dis[from[i]]);
		}else puts("1");
 	}
	return 0;	
} 
```



---

## 作者：RPChe_ (赞：4)

刚开始一看到这题，只想到了暴力，然后经一神人指点，发现这原来是一道差分约束。 [~~你不会差分约束？~~](https://www.luogu.org/blog/Darth-Che/solution-uva1723)

------------

首先我们可以发现，题目要求每条边的边权 w[i] 满足 w[i] ∈ {1,2}，并且所有从 1 到 n 的路径拥有相同的长度。那么我们就可以发现所有在从 1 到 n 的路径上的节点都满足 1 到它的路径的长度一定相同，为什么？

因为如果 1 到这个节点的路径的长度不一定相同，那么从 1 经过这个节点到 n 的路径的长度也就不一定相同，不满足题目。

我们令从 1 到其他节点的路径的长度为 dis[i] ，假设有一条从 u 到 v 的有向边，我们就可以得到两个约束条件：

1. dis[v]-dis[u]>=1，即dis[u]<=dis[v]-1。

2. dis[v]-dis[u]<=2，即dis[v]<=dis[u]+2。

然后我们对读入数据建立差分约束系统，就可以愉快的跑spfa了，~~然而却爆0了。~~

这是因为某些从 1 出发，然而到不了 n 的路径无论怎么设置边权，都无法满足约束条件，即出现了负权回路，然而这时题目是有解的。

所以我们要先做一次预处理，找出在从 1 到 n 的路径上的节点，只对它们建立差分约束系统，顺便还可以判断 1 到 n 是否联通，代码如下：

```cpp
//dfs两次，第一次从 1 出发，vis1==1表示访问过。
//第二次从 n 出发，建反向边，vis1==2表示在从 1 到 n 的路径上。
void dfs(int x,int t) {//t表示第几次dfs 
	vis1[x]++;
	if(t==1&&x==n) return;//第一次dfs到 n 就返回。 
	if(t==2&&x==1) return;//第二次dfs到 1 就返回。 
	for(int i=head[x];i!=-1;i=e[i].next) {
		if(!vis1[e[i].b]&&t==1||vis1[e[i].b]==1&&t==2) {
			dfs(e[i].b,t); 
		}
	}
}
```

而对于那些无关紧要的边，用rand函数随便赋个值就行。

这样我们就得到了完整的代码，时间复杂度O(2n+km)，如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<ctime>
#include<stdlib.h>
using namespace std;

inline int read() {
	int f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=f;ch=getchar();}
	while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return f*x;
}

inline void write(int x) {
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

struct node{
	int v,a,b,next;
}e[10000];
int head[10000],n,m,cnt,dis[10000],vis[10000];
int vis1[10000],x[10000],y[10000],sig[10000];

void add(int a,int b,int v) {
	cnt++;
	e[cnt].a=a;
	e[cnt].b=b;
	e[cnt].v=v;
	e[cnt].next=head[a];
	head[a]=cnt;
}

int spfa(int sta) {
	queue<int> q;
	dis[sta]=0;
	vis[sta]=1;
	q.push(sta);
	while(!q.empty()) {
		int tem=q.front();
		sig[tem]++;
		if(sig[tem]>m) return 0;
		q.pop();
		vis[tem]=0;
		for(int i=head[tem];i!=-1;i=e[i].next) {
			if(dis[e[i].b]>dis[tem]+e[i].v) {
				dis[e[i].b]=dis[tem]+e[i].v;
				if(!vis[e[i].b]) {
					vis[e[i].b]=1;
					q.push(e[i].b);
				}
			}
		}
	}
	return 1;
}

void dfs(int x,int t) {
	vis1[x]++;
	if(t==1&&x==n) return;
	if(t==2&&x==1) return;
	for(int i=head[x];i!=-1;i=e[i].next) {
		if(!vis1[e[i].b]&&t==1||vis1[e[i].b]==1&&t==2) {
			dfs(e[i].b,t); 
		}
	}
}

int main() {
	srand(time(0));
	memset(head,-1,sizeof(head));
	memset(dis,1e6,sizeof(dis));
	n=read(),m=read();
	for(int i=1;i<=m;i++) {
		x[i]=read(),y[i]=read();
		add(x[i],y[i],1);
	}
	dfs(1,1);
	cnt=0,memset(head,-1,sizeof(head));
	for(int i=1;i<=m;i++) add(y[i],x[i],1);
	dfs(n,2);
	if(vis1[n]<2) {
		putchar('N'),putchar('o');
		return 0;
	}
	cnt=0,memset(head,-1,sizeof(head));
	for(int i=1;i<=m;i++) {
		if(vis1[x[i]]==2&&vis1[y[i]]==2)
		add(x[i],y[i],2),add(y[i],x[i],-1);
	}
	if(spfa(1)) {
		putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
		for(int i=1;i<=m;i++) {
			if(vis1[x[i]]==2&&vis1[y[i]]==2) {
				write(dis[y[i]]-dis[x[i]]),putchar('\n');
			} else {
				write(rand()%2+1),putchar('\n');
			}
		}
	} else putchar('N'),putchar('o');
	return 0;
} 
```


---

## 作者：IGpig (赞：3)

# CF241E 

### 题意
给你一张图，单向边且边权为 1，现在需要修改一些边的边权为 2 且保证 1 到 $n$ 的所有路径的长度相同。

### Solution
观察条件，可以发现要满足 1 到 $n$ 的所有路径的长度相同，就要使 1 到 $n$ 的路径上所有的点的距离相同。

所以对于一条边，有差分约束的条件:
$$1\leq dis[v]-dis[u] \leq 2$$
当然，对于不在 1 到 $n$ 的路径的点，我们不需要考虑。

先预处理一下从 $1\leftarrow n$ 和 $n\rightarrow1$ 的边，标记后重新建图，最后答案就为 $dis[v]-dis[u]$，否则在输出时可以直接输出 1。

关于 spfa 的差分约束具体操作，就是我们在建图的时候正着建一条边权为 2 的，反着建一条边权为 -1 的，最后就是判断一下负环（详见代码）。
### Code
~~~cpp
#include<bits/stdc++.h>
#define pi pair<LL,LL>
#define val first
#define id second
using namespace std;
using LL=long long;
LL n,m,U[5005],V[5005],dis[5005],tmp[5005],cnt[5005];
bool vis[5005];
vector<pi> g[5005];
inline void add(LL u,LL v,LL w){
    g[u].push_back({w,v});
}
void dfs1(LL x){
    tmp[x]++;
    if(x==n) return ;
    for(auto i : g[x]){
        if(!tmp[i.id]){
            dfs1(i.id);
        }
    }
}
void dfs2(LL x){
    tmp[x]++;
    if(x==1) return ;
    for(auto i : g[x]){
        if(tmp[i.id]==1){
            dfs2(i.id);
        }
    }
}
queue<LL> q;
bool spfa(LL s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0,vis[s]=1;
    q.push(s);
    while(!q.empty()){
        LL to=q.front();q.pop();
        if(++cnt[to]>m) return 0;
        vis[to]=0;
        for(auto i : g[to]){
            if(dis[i.id]>dis[to]+i.val){
                dis[i.id]=dis[to]+i.val;
                if(!vis[i.id]){
                    vis[i.id]=1;
                    q.push(i.id);
                }
            }
        }
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>U[i]>>V[i];
        add(U[i],V[i],1);
    }
    dfs1(1);
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=1;i<=m;i++) add(V[i],U[i],1);
    dfs2(n);
    if(tmp[n]<2){
        cout<<"No";return 0;//n不联通
    }
    //建新图
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=1;i<=m;i++){
        if(tmp[U[i]]==2&&tmp[V[i]]==2){
            add(U[i],V[i],2);
            add(V[i],U[i],-1);
        }
    }
    if(spfa(1)){
        cout<<"Yes\n";
        for(int i=1;i<=m;i++){
            if(tmp[U[i]]==2&&tmp[V[i]]==2){
                cout<<abs(dis[V[i]]-dis[U[i]])<<endl;
            }else cout<<"1\n";
        }
        return 0;
    }
    cout<<"No";
    return 0;
}
~~~

---

## 作者：chenxia25 (赞：3)

呐，???? ycx 来补差分约束了？

我们考虑如果已知所有边的边权，那么如何判是否合法。考虑搞个 DP，$dp_i$ 表示 $1\to i$ 的所有路径的长度集合大小为 $1$ 的情况下的最短路。注意 DP 过程中如果遇到不为 $1$ 的直接输出不合法。然后这个地方有个坑点：题目只要求 $1\to n$ 的路径长度唯一，并不要求其他的长度为一，也就是对于那些不在任何一条 $1\to n$ 路径上的点，我们 dark 当他不存在。

那么我们能够通过一个合法的 DP 数组还原出每条边的权。于是我们只需要找出一组合法的 DP 数组。它显然要满足，对于所有边 $(x,y)$，都有 $dp_y-dp_x\in\{1,2\}$。那么可以列出不等式，然后差分约束。（注意这里似乎还要满足 $dp_1=0$，不过无伤大雅，我们只研究 DP 值与 DP 值的差）

时间复杂度 $\mathrm O(nm)$。

**_[code](https://www.luogu.com.cn/paste/hhggn836)_**

---

## 作者：raincity (赞：3)

## 分析

设所有点 1 到 $n$ 的路径（不一定最短）经过的所有点的集合为 $En$，改变路径长度后 1 到点 $i$ 的最短路长度是 $dis_i$。

有一个性质：**对于点 $i \in En$，满足点 1 到 $i$ 的路径长度在改变后都相等。**（理由：因为存在一条 1 到 $n$ 的路径经过 $i$ ，那么一定会有从 $i$ 到 $n$ 的路径和 $1$ 到 $i$ 的路径，在 $i$ 到 $n$ 的路径中任意一条，和所有 $1$ 到 $i$ 的路径拼起来，会得到 1 到 $n$ 的路径，而它们长度不同，与题意矛盾）。

所以，对于边 $u,v$ 满足 $u \in En, v \in En$，都有:

$\left\{\begin{array}{l}dis_v-dis_u \le 2\\dis_v-dis_u \ge 1\end{array}\right.$

第一个式子容易理解：$dis_u+2$ 是一条 1 到 $v$ 的路径长度，而 $dis_v$ 是 1 到 $v$ 的路径中长度最短的路径长度，所以 $dis_v-dis_u \le 2$。

第二个式子稍微难一些，因为 $v \in En$，所以所有 1 到 $v$ 的路径长度都一样，而改变一条边的长度只能改大，所以 $dis_v$ 要大于等于所有到 $v$ 的路径，故 $dis_v-dis_u \ge 1$。

我们只需要对这些式子跑一边差分约束即可，那么需要先求出 $En$。

方法比较简单：先从点 1 开始 bfs，求出点 $1$ 在改变前到其他点的距离，然后从点 $n$ 开始 bfs，遇到能从点 1 到的点就打上标记，最后所有打上标记的点属于 $En$。**注意要给点 n 打标记。**

具体实现见代码。

## 解决
**update:** 更新了代码，删掉了一些不必要的头文件（尽管我觉得没有人会去看头文件），这份代码比较慢（但也能过），因为不想放 rk1 代码

$\texttt{Code:}$

```cpp
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1005, M = 5005;

int _head[N], _ver[M], _nxt[M], _tot, _dis[N];
int __head[N], __ver[M], __nxt[M], __tot, __dis[N];
int head[N], ver[M << 1], nxt[M << 1], edge[M << 1], tot;
int val[N], cnt[N], dis[N], u[M], v[M], m, n;
queue <int> Q;
char vis[N], pd[N];

char SPFA() {
    Q.push(1);
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        vis[cur] = 0;
        for (register int i = head[cur]; i; i = nxt[i]) {
            int to = ver[i], w = edge[i];
            if (dis[to] > dis[cur] + w) {
                dis[to] = dis[cur] + w, val[to] = val[cur] + 1;
                if (val[to] > n)
                    return 1;
                if (!vis[to]) {
                    ++cnt[to];
                    if (cnt[to] > n)
                        return 1;
                    Q.push(to);
                }
            }
        }
    }
    return 0;
}

inline void addedge(int x, int y, int z) { ver[++tot] = y, nxt[tot] = head[x], head[x] = tot, edge[tot] = z; }
inline void _addedge(int _x, int _y) { _ver[++_tot] = _y, _nxt[_tot] = _head[_x], _head[_x] = _tot; }
inline void __addedge(int __x, int __y) { __ver[++__tot] = __y, __nxt[__tot] = __head[__x], __head[__x] = __tot; }

inline void read(int &ret) {
    ret = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = getchar();
}

void BFS() {
    Q.push(1);
    memset(_dis, 0x3f, sizeof(_dis));
    _dis[1] = 0;
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        for (register int i = _head[cur]; i; i = _nxt[i]) {
            int to = _ver[i];
            if (_dis[to] != 0x3f3f3f3f)
                continue;
            _dis[to] = _dis[cur] + 1;
            Q.push(to);
        }
    }
    memcpy(__dis, _dis, sizeof(__dis));
    Q.push(n), pd[n] = 1;
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        for (register int i = __head[cur]; i; i = __nxt[i]) {
            int to = __ver[i];
            if (__dis[to] == 0x3f3f3f3f)
                continue;
            __dis[to] = 0x3f3f3f3f, pd[to] = 1;
            Q.push(to);
        }
    }
}

void build() {
    read(n), read(m);
    for (register int i = 1; i <= m; i++) {
        read(u[i]), read(v[i]);
        _addedge(u[i], v[i]), __addedge(v[i], u[i]);
    }
    BFS();
    for (register int i = 1; i <= m; i++) {
        if (!pd[u[i]] || !pd[v[i]])
            continue;
        addedge(u[i], v[i], 2), addedge(v[i], u[i], -1);
    }
}

int main() {
    build();
    if (SPFA()) {
        puts("No");
        return 0;
    }
    puts("Yes");
    for (register int i = 1; i <= m; i++) {
        if (!pd[u[i]] || !pd[v[i]]) {
            puts("1");
            continue;
        }
        if (dis[v[i]] == dis[u[i]] + 2)
            puts("2");
        else
            puts("1");
    }
    return 0;
}
```



#### THE END

---

## 作者：1saunoya (赞：2)

差分约束。

若干条限制。

$1\leq dis_v -dis_u \leq 2$

考虑找出在 $1$ ~ $n$ 所有路径上的点。

$dis_v -2 \leq dis_u$。

$dis_u +1 \leq dis_v$。

差分约束即可。

---

## 作者：Takato_ (赞：0)

### [Flights](https://www.luogu.com.cn/problem/CF241E)

#### 思路：

题目大概是说，有一个 $n$ 个点 $m$ 条边的图，其中每条边的边权都是 $1$。现在需要改变其中若干条边的边权使得其变为 $2$，问该如何改变才能使得从 $1$ 出发到 $n$ 的所有路径边权总和相同（即所有路都是最短路）。

因为一条边的边权不是 $1$ 就是 $2$，所以有差分约束条件：

$$1 \le ans_i \le 2 $$

当然，题目已经告诉了。

由于我们只需要考虑从 $1$ 到 $n$ 路径上的点，我们不需要考虑其他路径上的点。

先分别建正图反图跑一遍 dfs，用来标记所有能跑到的点，用一个数组来统计每个点的出现次数（建反图是以防万一）。如果终点出现次数不为 $2$，说明起点走不到终点，输出 ```No```。

遍历每个点，如果点出现的次数等于 $2$，说明它出现在了路径上，将它加入一个新的图（在删去所有没用的点后重新建图），用上面的差分约束条件。

最后跑一遍最短路，如果一条路径两个点都出现在了新图上，就输出两点间的最短距离。否则不更改，直接输出 $1$。

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define x first
#define y second
int n,m,a[5010],b[5010],dis[5010],tim[5010],cnt[5010];
bool st[5010];
vector<pair<int, int> > e[5010];
void dfs(int x, int en){
    ++ tim[x];
    if(x == en) return ;
    for(auto i : e[x]){
        if((en == n && !tim[i.y]) || (en == 1 && tim[i.y] == 1)){
            dfs(i.y, en);
        }
    }
}queue<int> q;
bool spfa(){
    memset(dis, 0x3f, sizeof dis);
    dis[1]=0,st[1]=1;
    q.push(1);
    while(q.size()){
        int to=q.front();
		q.pop();
        if(++cnt[to]>m) return 0;
        st[to]=0;
        for(auto i : e[to]){
            if(dis[i.y] > dis[to] + i.x){
                dis[i.y] = dis[to] + i.x;
                if(!st[i.y]){
                    st[i.y] = 1;
                    q.push(i.y);
                }
            }
        }
    }return 1;
}signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i];
        e[a[i]].push_back({1, b[i]});
    }dfs(1, n);
    for(int i=1;i<=n;i++) e[i].clear();
    for(int i=1;i<=m;i++) e[b[i]].push_back({1, a[i]});
    dfs(n, 1);
    if(tim[n] < 2) cout << "No";
    else{
    	for(int i=1;i<=n;i++) e[i].clear();
	    for(int i=1;i<=m;i++){
	        if(tim[a[i]] == 2 && tim[b[i]] == 2){
	            e[a[i]].push_back({2, b[i]});
	            e[b[i]].push_back({-1, a[i]});
	        }
	    }if(spfa()){
	        cout << "Yes" << endl;
	        for(int i=1; i<=m; i++){
	            if(tim[a[i]] == 2 && tim[b[i]] == 2){
	                cout<<abs(dis[a[i]] - dis[b[i]]) << endl;
	            }else cout << "1" << endl;
	        }
	    }else cout << "No";
	}
}
```

---

## 作者：zyc418 (赞：0)

# 题目
[题目传送门](https://codeforces.com/problemset/problem/241/E)
# 大意
有一个 $n$ 个结点且每条边权值均为 $1$ 的有向图，要你把一些边权改成 $2$ 使得任意一条从 $1$ 到 $n$ 的路径长度都相等。
# 分析
由题意可以看出，本题相当于给定了一个有向图，现在让你给每条边确定一个权值。

并且权值的范围在 $1$ 和 $2$ 之间，每条在 $1$ 到 $n$ 之间的路径都为最短路。

那么我们可以令 $dis_{x}$ 为 $x$ 到 $n$ 的最短路，对于每一条边 $a_{u,v}$ 都有

$$
dis_{v+1} \le dis_{u} \le dis_{v+2}
$$

我们~~不难~~看出，这很像一道**差分约束**，那么我们就可以用此方程建立**不等式组**。

因为数据很小 

$$
2 \le n \le 1000
$$ 

$$
1 \le m \le 5000
$$

所以我用的是 `Bellman_Ford` ，~~主要是不想写太多~~。
# Code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=5e3+5;
ll n,m,dis[N],a[N][2],vis[N],num[N][2];
void dfs(ll u,ll t) {
	num[u][t]=1;
	for (ll i=1;i<=m;i++) {
        if (a[i][t]==u&&!num[a[i][t^1]][t]) {
            dfs(a[i][t^1],t);
        }
    }
}
void bellman_ford() {
    for(ll i=1;i<=n;i++) {
		for(ll i=1;i<=m;i++) {
            if (vis[a[i][0]]&&vis[a[i][1]]) {
				ll u=a[i][0],v=a[i][1];
				dis[u]=min(dis[v]+2,dis[u]);
				dis[v]=min(dis[u]-1,dis[v]);
			}
        }
    }
}
int main() {
	cin>>n>>m;
	for(ll i=1;i<=m;i++) {
        ll x,y;
        cin>>x>>y;
        a[i][0]=x;
        a[i][1]=y;
    }
	dfs(1,0);
    dfs(n,1);
	for(ll i=1;i<=n;i++) {
        vis[i]=(num[i][0]&&num[i][1]?1:0);
    }
	bellman_ford();
	for(ll i=1;i<=m;i++) {
        if(vis[a[i][0]]&&vis[a[i][1]]) {
			ll x=dis[a[i][0]]-dis[a[i][1]];
			if(x!=1&&x!=2) {
                cout<<"No";
                return 0;
            }
		}
    }
	cout<<"Yes"<<endl;
	for(ll i=1;i<=m;i++) {
        cout<<max(min(dis[a[i][0]]-dis[a[i][1]],2ll),1ll)<<endl;
    }
	return 0;
}
```

---

## 作者：Targanzqq (赞：0)

## 一道比较板的紫题

>主要思路：dfs+差分约束

我在刚学差分约束不久后做了这道题，~~当时以为是二分~~，结果后来发现是差分约束。

### Part 1：题目大意
有一个边权都是 $1$ 的有向无环图，我们要修改一些边使得 $1$ 到 $n$ 的所有路径相同。

### Part 2：主要思路
我们考虑从结果倒推回去：如果我们通过修改一些边使得 $1$ 到 $n$ 的所有路径相同，那么对于从第 $i$ 点到 $n$ 的点，假设我们从一条路径到达了 $i$ 点，那么当我们走完这条路径后到达 $n$ 走的路径长度一定相同，然后我们用总路径长度减掉这个路径长度，能得到从 $1$ 到 $i$ 的路径长度也是相同的。
因此，我们可以用 $dis_i$ 来表示从 $1$ 到 $i$ 的路径长度。假设 $j$ 是任意一个从 $i$ 可以通过一条边连向的点，那么我们得出一个式子：$1\le dis_j-dis_i \le 2$。

转化一下，就变成了
$\begin{cases}
  dis_j-dis_i\le 2\\
 dis_i-dis_j\ge -1
\end{cases}$，可以用差分约束解决此类问题。

[不会差分约束？](https://www.luogu.com.cn/problem/P5960)

### Part 3 代码 
```
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define int long long
using namespace std;

struct node{
	int now;
	int to;
	int val;
}edge[20001],edge2[20001];

int n,m,dis[20001],top=0,top2=0,vis[20001],fg[20001]; 

vector<int> t[20001];

void dfs(int now){
	if(now==n){
		fg[now]=1;
		return;
	}
	for(int i=0;i<t[now].size();i++){
		if(!vis[t[now][i]]){
			vis[t[now][i]]=1;
			dfs(t[now][i]);
		}
		if(fg[t[now][i]])fg[now]=1;
	}
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		t[a].push_back(b); 
		edge2[++top2]={a,b,1};
	}
	dis[1]=0;
	vis[1]=1;
	dfs(1);
	for(int i=1;i<=top2;i++){
		if(fg[edge2[i].now]&&fg[edge2[i].to]){
			edge[++top]={edge2[i].now,edge2[i].to,2};
			edge[++top]={edge2[i].to,edge2[i].now,-1};
		}
	}
	bool flag=0;
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<=top;j++){
			if(dis[edge[j].now]+edge[j].val<dis[edge[j].to]){
				flag=1;
				dis[edge[j].to]=dis[edge[j].now]+edge[j].val; 
			}
		}
		if(flag==0){
			break;
		}
	}
	for(int i=1;i<=top;i++){
		if(dis[edge[i].now]+edge[i].val<dis[edge[i].to]){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	for(int i=1;i<=top2;i++){
		if(fg[edge2[i].now]&&fg[edge2[i].to]){
			cout<<dis[edge2[i].to]-dis[edge2[i].now]<<endl;
		}
		else cout<<1<<endl;
	}
} 
```

---

## 作者：Hisaishi_Kanade (赞：0)

首先，不在 $1\to n$ 任意路径上的边随便点，毕竟无论怎么点都是无所谓的。可以通过两次搜索找到这些点。

对于在 $1\to n$ 某条路径上的点，我们设 $d_i$ 表示 $1\to i$ 最短路的值，则会对于 $\forall (u,v)$，有 $1 \le d_v-d_u\le2$，证明则显然。我们由此可以得到关于 $d_u$ 和 $d_v$ 的两个不等式。

那么，对于 $d$ 我们可以建出一个差分约束系统得到 $d$ 的一组解。如何确定边权呢，不难想到对于 $(u,v)$ 就是 $d_v-d_u$。根据差分约束系统，有负环则无解。

对于跑出来的解我们只是关心其差值，所以只要有解，则其作差后就必然得到一组合法的解。

---

## 作者：FutaRimeWoawaSete (赞：0)

尴尬了，推到正解了都还没发现推到正解了（（（             

考虑差分约束。              

我们知道如果所有 $1 \sim n$ 的路径长度相同，那么在中间选择一个点 $u$ 满足 $1 \sim u$ 的路径长度相同，$u \sim n$ 的路径长度相同，可以证明如果不相同必然导致 $1 \sim n$ 的路径长度不相同。             

一个小 trick，我们同时发现 $1 \sim n$ 的路径长度相同，被包含在了任意 $1 \sim u$ 的路径长度相同这个条件下，同时我们可以利用上述的两个条件推得 $u \sim n$ 的路径长度都相同，所以我们只需要满足任意 $1 \sim u$ 的路径长度相同即可，其中 $u$ 可以被一条 $1 \sim n$ 的路径经过。        

记 $dis_u$ 表示当前 $1 \sim u$ 的距离，那么对于任意一条边 $(u,v)$，其中 $u,v$ 都必须至少存在一条 $1 \sim n$ 的路径上，可得：           

$1 \leq dis_v - dis_u \leq 2$。                  

然后拆出另外两个不等式建立差分约束即可，时间复杂度 $O(nm)$。        

空间开小，处理了无用边两个问题均会被卡掉，实现时请注意这两个问题。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 5e3 + 5 , Inf = 1e9 + 1;
int n,m,head[Len],cnt,s,in[Len],dis[Len];bool vis[Len],flag[Len],flaw[Len];
struct NNode
{
	int x,y,w;
}Edge[5005];
struct node
{
	int next,to,id;
}edge[5005 << 1];
void add(int from,int to,int id)
{
	edge[++ cnt].to = to;
	edge[cnt].id = id;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
bool dfs(int x)
{
	if(x == n) return flag[x] = 1;
	vis[x] |= 1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(vis[to]) 
		{	
			flag[x] |= flag[to];
			continue;	
		}
		flag[x] |= dfs(to);
	}
	return flag[x];
}
struct Node
{
	int to,w;
	Node(){to = w = 0;}
	Node(int TO,int W){to = TO , w = W;}
};
vector<Node> v[Len];
void SPFA()
{
	queue<int> q;
	for(int i = 1 ; i <= n + 1 ; i ++) dis[i] = Inf , flaw[i] = 0;
	q.push(s);flaw[s] = 1;dis[s] = 0;
	while(!q.empty())
	{
		int p = q.front();q.pop();
		flaw[p] = 0;
		for(int i = 0 ; i < v[p].size() ; i ++)
		{
			int to = v[p][i].to;
			if(dis[to] > dis[p] + v[p][i].w)
			{
				dis[to] = dis[p] + v[p][i].w;
				if(!flaw[to])
				{
					in[to] ++;
					if(in[to] == n + 1) 
					{
						puts("No");
						exit(0);
					}
					flaw[to] = 1;
					q.push(to);
				}
			}
		}
	}
	for(int i = 1 ; i <= n ; i ++) 
	{
		//printf("%d %d\n",i,dis[i]);
		for(int e = head[i] ; e ; e = edge[e].next)
		{
			int to = edge[e].to;
			if(flag[i] && flag[to]) 
			{
			//	printf("%d %d %d %d\n",i,to,dis[to],dis[i]);
				Edge[edge[e].id].w = dis[to] - dis[i];
			}
			else Edge[edge[e].id].w = 1;
		}
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		Edge[i].x = x , Edge[i].y = y;
		add(x , y , i);
	}
	flag[1] = dfs(1);
	for(int i = 1 ; i <= n ; i ++)
	{
		if(!flag[i]) continue; 
		for(int e = head[i] ; e ; e = edge[e].next)
		{
			int to = edge[e].to;
			if(!flag[to]) continue;
			v[i].push_back(Node(to , 2));
			v[to].push_back(Node(i , -1));
		}
	}
	s = n + 1;
	for(int i = 1 ; i <= n ; i ++)
	{
		if(!flag[i]) continue;
		v[s].push_back(Node(i , 0));
	}
	SPFA();
	puts("Yes");
	for(int i = 1 ; i <= m ; i ++) printf("%d\n",Edge[i].w);
	return 0;
}
```

---

## 作者：Acerkaio (赞：0)

算法：差分约束。

## 思路：
我们把城市看成节点，时长看作边权。我们设 $d_i$ 为编号 $1$ 的节点到编号 $i$ 的节点需要的权。

对于节点 $u$ 与其可以到达的节点 $v$ 我们可以得出如下关系：
 
$1 \le d_u - d_v \le 2$
 
进一步得出 
$\left\{\begin{matrix} 
d_u - 1 \ge d_v\\
d_v + 2 \ge d_u
\end{matrix}\right. $
 
连边跑最短路即可。

### 正确性：

首先，此题因为需要使得所有从城市 $1$ 到城市 $n$ 的路线的总航程都相同。所以对于所有从城市 $1$ 到城市 $n$ 的路线上节点 $i$，$d_i$ 唯一。所以满足差分约束条件的答案即为解，反之则会出现负环而无解（可以自己试着构造一下）。

### 剪枝：

我们发现所有从城市 $1$ 到城市 $n$ 的路线上的节点之外的节点是对答案没有贡献的，是 $1$ 是 $2$ 都无所谓。我们便可以 DFS 寻找所有从城市 $1$ 到城市 $n$ 的路线上的节点再建边。

## CODE:

```
#include <bits/stdc++.h>
using namespace std;
const int _ = 1e5 + 7;
int tot = 0, head[_], head2[_], thoth = 0, d[_];
struct S11EDG {
  int x, y, next;
} edge[_];
struct itisover {
  int x, y, w, next;
} node[_];
int n, m;
void add(int x, int y) {
  ++tot;
  edge[tot].x = x;
  edge[tot].y = y;
  edge[tot].next = head[x];
  head[x] = tot;
}
void add2(int x, int y, int w) {
  ++thoth;
  node[thoth].x = x;
  node[thoth].y = y;
  node[thoth].w = w;
  node[thoth].next = head2[x];
  head2[x] = thoth;
}
int flag[_], vis[_];
void dfs(int u) {
  vis[u] = 1;
  //cout << "DFS DEBUG" << u << '\n';
  for (int i = head[u]; i; i = edge[i].next) {
    int v = edge[i].y;
    if (!vis[v]) dfs(v);
    if (flag[v]) flag[u] = 1;
  }
  return ;
}
signed main() {
  memset(d, 0x3f, sizeof d);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int x, y;
    cin >> x >> y;
    add(x, y);
  }
  flag[n] = 1;
  
  dfs(1);
  //cout << flag[1] << ' ' << flag[2] << ' ' << flag[3];
  for (int i = 1; i <= tot; i++) {
    if (flag[edge[i].x] && flag[edge[i].y]) {
    	//cout << i << '\n';
      add2(edge[i].x, edge[i].y, 2);
      add2(edge[i].y, edge[i].x, -1);
    }
  }
  /*-ford-*/
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= thoth; j++) {
      d[node[j].y] = min(d[node[j].y], d[node[j].x] + node[j].w);
    }
  }
  for (int j = 1; j <= thoth; j++) {
    if (d[node[j].y] > d[node[j].x] + node[j].w) {
    	cout << "No\n";
    	return 0;
		}
  }
  cout << "Yes\n";
  for (int i = 1; i <= m; i++) {
  	if (flag[edge[i].x] && flag[edge[i].y]) {
  		cout << d[edge[i].y] - d[edge[i].x] << '\n';
		} else {
			cout << "1\n";
		}
	}
  return 0;
}
```


---

## 作者：_lxy_ (赞：0)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF241E-Solution.html)
#### 简要题意

$n$ 个点，$m$ 条有向边，每条边初始边权是 $1$，让将一些边的边权变为 $2$，使所有从点 $1$ 到 $n$ 的路径长度相等。

#### 分析

首先发现如果一条边不在 $1$ 到 $n$ 的任意一条路径上，可以给它任意赋边权，因此只需考虑在 $1$ 到 $n$ 路径上的边。设 $1$ 到 $i$ 的最短路径长为 $d_i$，由于所有 $1$ 到 $n$ 的路径都等长，于是有 $\forall (u,v),d_u=d_v+w$，其中 $w$ 为 $(u,v)$ 的边权。于是题目中对边权的限制可以转换为对 $d$ 的限制，即：
$$
\begin{cases}
d_u-d_v\leq2 \\
1\leq d_u-d_v
\end{cases} 
\Longrightarrow 
\begin{cases}
d_u\leq d_v+2\\
d_v\leq d_u+1
\end{cases}
$$
，发现这是个典型的差分约束的形式，于是跑个 SPFA 就行了。最后 $(u,v)$ 的边权就是 $d_v-d_u$。

#### 核心代码

```cpp
int n,m,head[MAXN];vector<Pair>e;bitset<MAXN>v1,v2;
struct Edge{
    int to,dis,nxt;
    Edge(){;}Edge(int _to,int _dis,int _nxt):to(_to),dis(_dis),nxt(_nxt){}
};vector<Edge>edge;
void add_edge(int u,int v,int w){edge.push_back(Edge{v,w,head[u]});head[u]=edge.size()-1;}
int dis[MAXN],cnt[MAXN];bitset<MAXN>vis;queue<int>q;
bool spfa(int s){
    vis.reset();mem(dis,0x3f);mem(cnt,0);vis[s]=true;cnt[s]=1;dis[s]=0;q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i!=-1;i=edge[i].nxt){
            int v=edge[i].to,w=edge[i].dis;vis[u]=false;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!vis[v]) vis[v]=true,cnt[v]++,q.push(v);
                if(cnt[v]>=n) return false;
            }
        }
    }return true;
}vector<int>ed[MAXN];
void dfs(int u){
    for(auto v:ed[u]) if(!v1[v]) v1[v]=true,dfs(v);
}void dfs1(int u){
    for(auto v:ed[u]) if(!v2[v]) v2[v]=true,dfs1(v);
}
signed main(){
    qread(n,m);int i,j;mem(head,-1);
    for(i=1;i<=m;i++){
        int u,v;qread(u,v);e.push_back(Pair(u,v));
    }for(auto i:e) ed[i.first].push_back(i.second);
    dfs(1);for(i=1;i<=n;i++) ed[i].clear();
    for(auto i:e) ed[i.second].push_back(i.first);dfs1(n);
    if(!v1[n]) return printf("No\n"),0;v1[1]=v1[n]=v2[1]=v2[n]=true;
    for(auto i:e){
        if(v1[i.first]&&v1[i.second]&&v2[i.first]&&v2[i.second])
            add_edge(i.first,i.second,2),add_edge(i.second,i.first,-1);
    }
    if(!spfa(1)) return printf("No\n"),0;puts("Yes");
    for(auto i:e){
        if(v1[i.first]&&v1[i.second]&&v2[i.first]&&v2[i.second])
            printf("%lld\n",dis[i.second]-dis[i.first]);
        else printf("1\n",i.first,i.second);
    }
    #ifndef ONLINE_JUDGE
    system("pause > null");
    #endif
    return 0;
}
```

[record](https://codeforc.es/contest/241/submission/172240370)



---

## 作者：MSavannah (赞：0)

# Description
给你一个 $n$ 个点，$m$ 条边的有向图，起初所有边的边权都是 $1$，你可以将一些边权改为 $2$，使得 $1$ 到 $n$ 的所有路径长度都相等。

# Solution
有趣的差分约束！

首先，我们知道边权的范围是 $[1,2]$。由于我们要 $1$ 到 $n$ 的所有路径长度都相等，那么 $1$ 到任何一个在路径上的点的长度也一定都相等。设 $dis_i$ 表示从 $1$ 到 $i$ 的路径长度。

容易得到 $1\leq dis_v-dis_v \leq 2$。

把它拆开

$$\begin{cases}dis_v-dis_u\leq 2\\dis_u-dis_v\leq -1\end{cases}$$

一眼差分约束。

具体实现：我们 DFS 出在 $1$ 到 $n$ 路径上的边，把这些边按照上面式子连边，即 $u\xrightarrow{2}v$，$v\xrightarrow{-1}u$。SPFA 跑一下即可。那些不在路径上的边直接默认它是 $1$ 就好了。

注：这里解释一下为什么只对在路径上的边建立差分约束系统？
![](https://pic.imgdb.cn/item/6620b1420ea9cb1403e99dac.png)

就比如说这张图，对所有边建差分约束系统是无解的，但是它显然有解。为了避免误判，我们只对路径上的边建。

[code](https://www.luogu.com.cn/record/156184682)

顺便提一下 [P5590](https://www.luogu.com.cn/problem/P5590) 本质相同的一道题，只有边权范围改变了。

---

