# Police Station

## 题目描述

The Berland road network consists of $ n $ cities and of $ m $ bidirectional roads. The cities are numbered from 1 to $ n $ , where the main capital city has number $ n $ , and the culture capital — number $ 1 $ . The road network is set up so that it is possible to reach any city from any other one by the roads. Moving on each road in any direction takes the same time.

All residents of Berland are very lazy people, and so when they want to get from city $ v $ to city $ u $ , they always choose one of the shortest paths (no matter which one).

The Berland government wants to make this country's road network safer. For that, it is going to put a police station in one city. The police station has a rather strange property: when a citizen of Berland is driving along the road with a police station at one end of it, the citizen drives more carefully, so all such roads are considered safe. The roads, both ends of which differ from the city with the police station, are dangerous.

Now the government wonders where to put the police station so that the average number of safe roads for all the shortest paths from the cultural capital to the main capital would take the maximum value.

## 说明/提示

In the first sample you can put a police station in one of the capitals, then each path will have exactly one safe road. If we place the station not in the capital, then the average number of safe roads will also make ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF208C/4f500a162714534e43b066c5f5f2d811a8bad225.png).

In the second sample we can obtain the maximum sought value if we put the station in city $ 4 $ , then $ 6 $ paths will have $ 2 $ safe roads each, and one path will have $ 0 $ safe roads, so the answer will equal ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF208C/1f07abb000fedcaa79d701679480aab65a6674db.png).

## 样例 #1

### 输入

```
4 4
1 2
2 4
1 3
3 4
```

### 输出

```
1.000000000000
```

## 样例 #2

### 输入

```
11 14
1 2
1 3
2 4
3 4
4 5
4 6
5 11
6 11
1 8
8 9
9 7
11 7
1 10
10 4
```

### 输出

```
1.714285714286
```

# 题解

## 作者：Komorebi_03 (赞：6)

## 思路：
既要求从 $1$ 点到 $n$ 点的最短路条数，又要找这些最短路经过次数最多的点以及最短路径上和这个点相邻的边数（安全边）。

乍一看非常复杂，但仔细一想并不复杂。

显然，对于任意一条最短路，至多经过两条安全边，考虑枚举所有警察局的位置。

首先，当警察局设置在 $1$ 点或 $n$ 点时易得每条最短路都会且只会经过一条安全边，所以这种情况相当于最短路计数。

其他情况下，可以将原图分成 $1$ 点到警察局，警察局到 $n$ 点两部分来看。

只有当： $1$ 点到警察局的最短路 $+$ 警察局到 $n$ 点的最短路 $=$ $1$ 点到 $n$ 点的最短路，才能保证最短路经过安全边。

同时可以根据排列组合乘法原理相关知识得出，经过的安全边条数应为： $1$ 点到警察局的最短路条数 $\times$ 警察局到 $n$ 点的最短路条数。

附：一道最短路计数问题[P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

```cpp
// Problem: CF208C Police Station
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF208C
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By:Komorebi_03
#include<bits/stdc++.h>
using namespace std;
#define clear(a) memset(a,0,sizeof a)
#define int long long
const int N = 1e6+5;
const int M = 210;
int n,m,e_cnt,cnt[N],sum[M][M],dis[M][M],head[N];
bool vis[N];
struct edge{
	int v;
	int w;
	int nxt;
}e[N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void add(int u,int v)
{
	e[++e_cnt].v=v;
	e[e_cnt].nxt=head[u];
	head[u]=e_cnt;
}

void BFS(int s)
{
	clear(vis);
	queue<int> q;
	vis[s]=true;
	q.push(s);
	sum[s][s]=1;
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		for (int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(!vis[v])
			{
				vis[v]=true;
				dis[s][v]=dis[s][u]+1;
				q.push(v);
			}
			if(dis[s][v]==dis[s][u]+1)
				sum[s][v]+=sum[s][u];
		}
	}
}

signed main()
{
	n=read();
	m=read();
	for (int i=1;i<=m;i++)
	{
		int u=read();
		int v=read();
		add(u,v);
		add(v,u);
	}
	BFS(1);
	BFS(n);
	int k=sum[1][n];
	for (int i=2;i<n;i++)
		if(dis[1][i]+dis[n][i]==dis[1][n])
			k=max(k,sum[1][i]*sum[n][i]*2);
	printf("%.12lf",k*1.0/sum[1][n]);
	return 0;
	//Amireux_35
}
```


---

## 作者：GalwayGirl (赞：5)

看题解里都是 Floyd，虽然 $O(n^3)$ 可以跑过，但我还是打算交一发~~已死的~~优秀的 SPFA，并且位于最优解               rank1。

## Solution
最段路条数很好处理，最短路经过安全边的个数是什么？

对于警局在 $1$ 或 $n$，每条最短路都会经过一条安全边，所以等同于最短路条数。
 
其他情况下，只有当 $1$ 到警局的最短路和警局到 $n$ 的最短路之和等于 $1$ 到 $n$ 的最短路，才能使最短路经过安全边，经过的条数为 $2$ 倍的 $1$ 到警局的最短路条数乘上 警局到 $n$ 的最短路条数，为什么会是这样？让我们来看下面这张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/obs5fp6b.png)

可以看出当 $3$ 号点作为警局时最优，从起点到警局的最短路条数为 $2$，从警局到终点的最短路条数为 $3$，因为可以任选一条最短路从警局上方下来，所以下方被经历的总数为 $2×3=6$，上方经历的总数也为 $6$，证毕。

最后贴上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110,M=1e4+100;
long long cnt[N][N],max_,n,m,c,head[N],dis[N][N];
struct xzh{
    int next,to;
}edge[2*M];
bool vis[N];
void add(int u,int v){
    c++;
    edge[c].next=head[u];
    edge[c].to=v;
    head[u]=c;
}
void bfs(int s){
    queue<int>q;
    for(int i=1;i<=n;i++)vis[i]=false;
    vis[s]=true;
    q.push(s);
    cnt[s][s]=1;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=head[now];i;i=edge[i].next){
            int v=edge[i].to;
            if(!vis[v]){
                vis[v]=true;
                dis[s][v]=dis[s][now]+1;
                q.push(v);
            }
            if(dis[s][v]==dis[s][now]+1){
                cnt[s][v]+=cnt[s][now];
            }
        }
    }
}
int f[N];
int main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    bfs(1);
    bfs(n);
    max_=cnt[1][n];
    for(int i=2;i<n;i++){
        if(dis[1][i]+dis[n][i]==dis[1][n]){
            max_=max(max_,cnt[1][i]*cnt[n][i]*2);
        }
    }
    printf("%.12lf",max_*1.0/cnt[1][n]);
}
```


---

## 作者：Purple_Circle (赞：3)

题目说的很明白了，需要我们在一个无向图中选取一个点，最大化从 $1$ 到 $n$ 的最短路中经过该点所连边的数量。

看到数据范围 $n \le 100$，很容易想到通过 Floyd 算法在 $O(n^3)$ 的复杂度求解。而计算 “安全边” 的条数，可以转化为点 $1,n$ 分别到该点的路径条数，将它们相乘即为“安全边”的条数。

为什么呢，看到下面这张图：

![](https://urlshare.img.ink/2022/23f9bf050117c.png)

在这张图中，$p1 \sim p5$ 为中转点，$k$ 为警局所在的点。

则 $1\sim k$ 有 $3$ 条路径，$k \sim n$ 有 $2$ 条路径。

根据乘法原理可得，$1 \sim n$ 共有 $2 \times 3 $ 共 $6$ 条路径，而为了使“安全边”最大化，要让 $k$ 的所有出边尽量都在最短路上。

因此，“安全边”的条数即为 $1 \sim k$ 的路径数与 $k \sim n$ 的路径数之积。

那么我们将两个问题都放在 Floyd 中一起处理即可在 $O(n^3)$ 的时间复杂度内通过此题。

Floyd 代码如下：

```cpp
void Floyd(){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(G[i][j]>G[i][k]+G[k][j]){
					G[i][j]=G[i][k]+G[k][j];
					M[i][j]=0;
				}
				if(G[i][j]==G[i][k]+G[k][j]){
					M[i][j]+=(M[i][k]*M[k][j]);
				}
			}
		}
	}
}
```

完整代码：
```cpp
#include<bits/stdc++.h>
#define rd read()
#define int long long
using namespace std;
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
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,m;
int G[310][310],M[310][310];
void Floyd(){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(G[i][j]>G[i][k]+G[k][j]){
					G[i][j]=G[i][k]+G[k][j];
					M[i][j]=0;
				}
				if(G[i][j]==G[i][k]+G[k][j]){
					M[i][j]+=(M[i][k]*M[k][j]);
				}
			}
		}
	}
}
double ans=1.0;
void add(int x,int y){
	G[x][y]=M[x][y]=1;
}
signed main(){
	n=rd,m=rd;
	memset(G,0x3f,sizeof(G));
	for(int i=1;i<=m;i++){
		int x=rd,y=rd;
     		add(x,y);
                add(y,x);
	}
	Floyd();
	for(int i=2;i<n;i++){
    	if(G[1][i]+G[i][n]==G[1][n]){
    		ans=max(ans,2.0*M[1][i]*M[i][n]/M[1][n]);
		}
  	}
	printf("%.12lf",ans);
	return 0;
}

```

---

## 作者：EnofTeiPeople (赞：2)

考虑从 $1$ 和 $n$ 出发广搜两次，记录他们到每一个点的最短路长度和条数。

具体地，开一个队列，初始只有起点，每次出队头，扫从队头出边连到的点，如果该点距离大于当前距离加一，则赋值为当前距离加一，并且若现在的距离等于当前距离，则更新方案数。

如果选定的点为 $1$ 或 $n$，那么每一条最短路都会恰好经过一条安全边，经过条数等同最短路条数。

否则，最短路必定是有 $1$ 到 $x$ 的最短路与 $x$ 到 $n$ 的最短路拼接而成，并且保证没有重复经过（如果那样就不是最短了）。

最后的答案照题意需除以 $n$，注意开 `long long` 和 `double`，输出格式用 `printf("%.12lf",ans);`

好，代码太短了，不到 700B：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=105;
using ll=long long;
ll g[N][N],ans;
ll d[N][2],ct[N][2];
int q[N],l,r,n,m;
inline void bfs(int s,int k){
	q[l=r=1]=s;int x,y;
	d[s][k]=ct[s][k]=1;
	while(l<=r){
		x=q[l++];
		for(y=1;y<=n;++y)
			if(g[x][y]){
				if(!d[y][k])d[q[++r]=y][k]=d[x][k]+1,ct[y][k]=ct[x][k];
				else if(d[y][k]==d[x][k]+1)ct[y][k]+=ct[x][k];
			}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	int i,x,y;
	for(i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		g[x][y]=g[y][x]=1;
	}bfs(1,0),bfs(n,1);//两次广搜
	ans=ct[n][0];
	for(x=2;x<n;++x)
		if(d[x][0]+d[x][1]==d[n][0]+1)
			ans=max(ans,ct[x][0]*ct[x][1]*2);
	double res=ans;res/=ct[n][0];
	printf("%.12lf\n",res);
	return 0;
}
```

---

## 作者：pitiless0514 (赞：2)

## 题目
有 $n$ 个点，让你选择一个点为警局，使得点 $1$ 到点 $n$ 的和谐路数与最短路径数最大。

## 题解

先吐槽垃圾翻译。

我们发现 $n$ 的范围并不是很大，一个立方的算法他是能够接受的。


我们可以先使用 floyd 算法求解出图上每个点之间的最短距离。

接下来考虑是计算的和谐道路数目。

我们发现其实我们不需要可以的去算这个东西。

我们只需要知道的是点 $1$ 到警局和点 $n$ 到警局的路径条数。

然后这两个乘起来就是我们的和谐路径数量。

那么很显然，这个东西是可以在 floyd 的过程中一起处理的，于是就可以在 $n^3$ 的复杂度里解决这个问题。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline char nc() {
  static char buf[100000], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline int read() {
  char ch = nc();
  int sum = 0;
  while (!isdigit(ch))
    ch = nc();
  while (isdigit(ch))
    sum = sum * 10 + ch - 48, ch = nc();
  return sum;
}
const int N = 300;
int n, m, a[N][N], b[N][N];
signed main() {
  n = read(), m = read();
  memset(a, 63, sizeof(a));
  for (int i = 0; i < m; i++) {
    int x = read(), y = read();
    a[x][y] = a[y][x] = 1;
    b[x][y] = b[y][x] = 1;
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (a[i][j] > a[i][k] + a[k][j]) {
          a[i][j] = a[i][k] + a[k][j];
          b[i][j] = 0;
        }
        if (a[i][j] == a[i][k] + a[k][j]) {
          b[i][j] += b[i][k] * b[k][j];
        }
      }
    }
  }
  double ans = 1.0;
  for (int i = 2; i < n; i++) {
    if (a[1][i] + a[i][n] == a[1][n])
      ans = max(ans, 2.0 * b[1][i] * b[i][n] / b[1][n]);
  }
  printf("%.10lf\n", ans);
  return 0;
}


```



---

## 作者：2huk (赞：0)

不妨枚举警察局放在哪。设为 $u$。考虑求解”所有最短路中经过的安全边个数”。

不妨枚举这条安全边 $(u, v)$，然后计算有多少条最短路经过它。对于每个 $v$ 都算一遍然后加和即为答案。

首先，如果 $dis(1,u)+1+dis(v,n)\ne dis(1,n)$ 则无解。这里 $dis(i, j)$ 表示 $i \rightsquigarrow j$ 的最短路长度。

然后做最短路计数。答案为 $cnt(1,u) \times cnt(v,n)$，其中 $cnt(i, j)$ 表示 $i \rightsquigarrow j$ 的最短路条数。

最短路计数见 [P1144](https://www.luogu.com.cn/problem/P1144)。

$cnt(i, j)$ 是否会爆掉 `long long`？不会的。一个最短路最多的例子是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/fyozvscg.png)

（虽然题目保证了没有重边，但是没有重边的最短路条数一定比上面这个少。）

此时最短路条数是 $2^{n/2}=2^{50}$。`long long` 存储是没有问题的。

代码：<https://codeforces.com/contest/208/submission/289875013>

---

## 作者：xuanxuan001 (赞：0)

终于是第 10 篇题解了，不容易。

这题可以用两个 BFS 求出每个点分别到 1 和 $n$ 号点的最短路长度和条数，分别存入数组 $dis1,disn,cnt1,cntn$。然后枚举警察局点编号 $i \in [2,n)$，那么所有经过点 $i$ 的路径都会经过 2 条安全边，其他的都是 0 条，所以此时的答案是

$$
\dfrac{cnt1_i \times cntn_i}{cnt1_n} \times 2
$$

并且要注意这时的路径要是最短路，也就是 $dis1_i+disn_i=dis1_n$。我就因为这个 WA 了一次。

求出来之后还要特判一下，如果最大值比 $cnt1_n$ 还小的话就要选 1 或 $n$ 号为警察局，输出 1。

但很容易就会发现一个问题：$cnt1$ 与 $cntn$ 两个数组的值的上限。

这个我也没有严谨证明出来，还需要更厉害的大佬来证。

我是主观地构造了一种我认为路径数最多的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/21bwqout.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

就是起点与 $r$ 个点相连，这 $r$ 个点再与另一个点 $p$ 相连，$p$ 再与另外的 $r$ 个点相连，以此类推，这样每一组里面都有 $r$ 种选择，有 $\lfloor \dfrac{100}{r+1} \rfloor$ 组，所以有 $r^{\lfloor {100 \over r+1} \rfloor}$ 条路径。

于是我写了一个程序来枚举 $r$，发现 $r=4$ 时最大，有 $2^{40}$，这开 long long 完全够，就算真正的上限比这大几十倍 long long 也绰绰有余。

代码：

```cpp
#include<cstdio>
#include<queue>
#define Ty int
#define MAXN 102
#define FOR(i,a,b) for(Ty i=a;i<=b;i++)
#define fOR(i,a,b) for(Ty i=a;i<b;i++)
#define ROF(i,a,b) for(Ty i=a;i>=b;i--)
#define rOF(i,a,b) for(Ty i=a;i>b;i--)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
Ty _abs(Ty a){return a<0?-a:a;}
ll maxn(ll a,ll b){return a>b?a:b;}
Ty qr(){
	char ch=getchar();Ty s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';
	return x*s;
}Ty n,m,u,v,head[MAXN],nxt[MAXN*MAXN],to[MAXN*MAXN],dis1[MAXN],disn[MAXN],nw;
ll cnt1[MAXN],cntn[MAXN],ans;queue<Ty>q;
void addedge(Ty u,Ty v,Ty id){nxt[id]=head[u];to[head[u]=id]=v;}
int main(){
	fOR(i,0,MAXN)dis1[i]=disn[i]=-1;
	n=qr();m=qr();
	cnt1[1]=cntn[n]=1;dis1[1]=disn[n]=0;
	FOR(i,1,m){
		u=qr();v=qr();
		addedge(u,v,i<<1);
		addedge(v,u,i<<1|1);
	}q.push(1);
	while(q.size()){
		nw=q.front();q.pop();
		for(Ty i=head[nw];i;i=nxt[i]){
			if(dis1[to[i]]==-1){
				dis1[to[i]]=dis1[nw]+1;cnt1[to[i]]=cnt1[nw];q.push(to[i]);
			}else if(dis1[to[i]]==dis1[nw]+1)cnt1[to[i]]+=cnt1[nw];
		}
	}q.push(n);
	while(q.size()){
		nw=q.front();q.pop();
		for(Ty i=head[nw];i;i=nxt[i]){
			if(disn[to[i]]==-1){
				disn[to[i]]=disn[nw]+1;cntn[to[i]]=cntn[nw];q.push(to[i]);
			}else if(disn[to[i]]==disn[nw]+1)cntn[to[i]]+=cntn[nw];
		}
	}fOR(i,2,n)if(dis1[i]+disn[i]==dis1[n])ans=maxn(ans,cnt1[i]*cntn[i]);
	ans<<=1;if(ans<cnt1[n])printf("1");//特判
	else printf("%.8lf",(double)ans/cnt1[n]);
	return 0;
}
```

---

