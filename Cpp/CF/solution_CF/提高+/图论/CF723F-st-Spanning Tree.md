# st-Spanning Tree

## 题目描述

You are given an undirected connected graph consisting of $ n $ vertices and $ m $ edges. There are no loops and no multiple edges in the graph.

You are also given two distinct vertices $ s $ and $ t $ , and two values $ d_{s} $ and $ d_{t} $ . Your task is to build any spanning tree of the given graph (note that the graph is not weighted), such that the degree of the vertex $ s $ doesn't exceed $ d_{s} $ , and the degree of the vertex $ t $ doesn't exceed $ d_{t} $ , or determine, that there is no such spanning tree.

The spanning tree of the graph $ G $ is a subgraph which is a tree and contains all vertices of the graph $ G $ . In other words, it is a connected graph which contains $ n-1 $ edges and can be obtained by removing some of the edges from $ G $ .

The degree of a vertex is the number of edges incident to this vertex.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
1 2 1 1
```

### 输出

```
Yes
3 2
1 3
```

## 样例 #2

### 输入

```
7 8
7 4
1 3
5 4
5 7
3 2
2 4
6 1
1 2
6 4 1 4
```

### 输出

```
Yes
1 3
5 7
3 2
7 4
2 4
6 1
```

# 题解

## 作者：cyh_toby (赞：5)

题目链接：[CF723F 【st-Spanning Tree】](https://www.luogu.com.cn/problem/CF723F)

# 分析

考虑先把 $s$ 和 $t$ 点隔离开，找一遍连通块。

找的时候分别记录一下这个连通块是否能到达 $s$ 和 $t$ 。

由于原图联通，不存在既不与 $s$ 联通，也不与 $t$ 联通的连通块。那么连通块有两种：

- 只与 $s$ 和 $t$ 中一个相连。对于这种连通块，这条连接的边是必须选入生成树的。（如果有多条边，选一条即可，下同。）

- 与 $s$ 和 $t$ 都相连。如果当前 $s$ 和 $t$ 还不连通，那么把这两条边都选入生成树；否则，只选择一条。

需要注意到，我们应该先处理第一种连通块，然后再做第二种。否则可能会把有解误判为无解。

如果处理完上述两种连通块，$s$ 和 $t$ 都仍然没有连通，根据**原图是联通的**，它们之间必定存在至少一条边，那么加入这条边即可。

在过程中，只要有必须加边而度数不满足的时候，则判定无解。

# 源码

代码有亿点乱，有亿点长。

```cpp
const int N = 2e5+5, M = 4e5+5;

int n, m, s, t;
int ds, dt, b = 0;
int g[N], v[2*M], nxt[2*M], tot = 1;
int vis[N], es1[M], et1[M], idx1, es2[M], et2[M], idx2;
int e[M], cnt, flag = 1;

inline void add(int x, int y) {
	v[++tot] = y, nxt[tot] = g[x], g[x] = tot;
}

void dfs(int u, int &e1, int &e2) {
	vis[u] = 1;
	for (int i = g[u]; i; i = nxt[i]) {
		int y = v[i];
		if (vis[y]) continue;
		if (y == s) {
			e1 = i;
			continue;
		}
		if (y == t) {
			e2 = i;
			continue;
		}
		e[++cnt] = i;
		dfs(y, e1, e2);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	scanf("%d%d%d%d", &s, &t, &ds, &dt);
	
	for (int i = 1; i <= n; i++) {
		if (vis[i] || i == s || i == t) continue;
		int e1 = 0, e2 = 0;
		dfs(i, e1, e2);
		if (e1 && e2) {
			idx2++;
			es2[idx2] = e1, et2[idx2] = e2;
		}
		else {
			idx1++;
			es1[idx1] = e1, et1[idx1] = e2;
		}
	}
	
	for (int i = 1; i <= idx1; i++) {
		if (es1[i]) {
			if (!ds) {
				flag = 0;
				break;
			}
			ds--;
			e[++cnt] = es1[i];
		}
		else {
			if (!dt) {
				flag = 0;
				break;
			}
			dt--;
			e[++cnt] = et1[i];
		}
	}
	
	if (!flag) {
		printf("No\n");
		return 0;
	}
	
	for (int i = 1; i <= idx2; i++) {
		if (!b) {
			if (!ds || !dt) {
				flag = 0;
				break;
			}
			ds--, dt--, b = 1;
			e[++cnt] = es2[i];
			e[++cnt] = et2[i];
			continue;
		}
		
		if (ds) {
			ds--;
			e[++cnt] = es2[i];
		}
		else {
			if (!dt) {
				flag = 0;
				break;
			}
			dt--;
			e[++cnt] = et2[i];
		}
	}
	
	if (!b) {
		if (!ds || !dt) {
			flag = 0;
		}
		else {
			ds--, dt--, b = 1;
			e[++cnt] = -1;
		}
	}
	
	if (!flag) {
		printf("No\n");
	}
	else {
		printf("Yes\n");
		for (int i = 1; i <= cnt; i++)
			if (e[i] == -1)
				printf("%d %d\n", s, t);
			else
				printf("%d %d\n", v[e[i]], v[e[i]^1]);
	}
	
	return 0;
}

```

---

## 作者：YCE__22 (赞：4)

1、首先我们可以将边分成两类：

①有s或者t作为一点的边：这类边的加入要有一定的条件。

②没有s或者t作为一点的边：这类边的加入不会影响结果，没有限定的条件，所以我们可以将其权值设定为0.

所以问题我们可以转化为给边设定权值的问题。剩余部分只要跑最小生成树贪心算法维护结果是否合法即可。



2、那么我们的问题关键点就在于如何设定类型①的边的权值。

接下来我们引入贪心思维，然后将问题再分成三类：

①ds>dt.那么我们肯定优先加入只有s点的边，然后次优先加入只有t的边，最后再加入既有s又有t的边。

过程 kruskal算法贪心加并查集维护即可。如果最终s点的度和t点的度都满足要求即为结果。

②ds<dt.那么我们肯定优先加入只有t点的边，然后次优先加入只有s的边，最后再加入既有s又有t的边。

③ds==dt.那么我们跑两遍即可，第一遍优先加入只有s点的边，然后次优先加入只有t的边，最后再加入既有s又有t的边。第二遍反过去，优先加入只有t点的边，然后次优先加入只有s的边，最后再加入既有s又有t的边。
```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
struct node
{
    int x,y,w,use;
}a[550000];
int f[550000];
int cmp(node a,node b)
{
    return a.w<b.w;
}
int find(int a)
{
    int r=a;
    while(f[r]!=r)
    r=f[r];
    int i=a;
    int j;
    while(i!=r)
    {
        j=f[i];
        f[i]=r;
        i=j;
    }
    return r;
}
void merge(int a,int b)
{
    int A,B;
    A=find(a);
    B=find(b);
    if(A!=B)
    f[B]=A;
}
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int s,t,ds,dt;
        for(int i=1;i<=n;i++)f[i]=i;
        for(int i=0;i<m;i++)scanf("%d%d",&a[i].x,&a[i].y);
        scanf("%d%d%d%d",&s,&t,&ds,&dt);
        int vals,valt;
        if(ds>dt)vals=1,valt=2;
        else vals=2,valt=1;
        for(int i=0;i<m;i++)
        {
            a[i].use=0;
            if(a[i].x==s||a[i].y==s)a[i].w=vals;
            if(a[i].x==t||a[i].y==t)a[i].w=valt;
        }
        int cnt=0;
        sort(a,a+m,cmp);
        int dds=0,ddt=0;
        for(int i=0;i<m;i++)
        {
            if(a[i].w==0)
            {
                if(find(a[i].x)!=find(a[i].y))
                {
                    cnt++;
                    a[i].use=1;
                    merge(a[i].x,a[i].y);
                }
            }
            else
            {
                if(find(a[i].x)!=find(a[i].y))
                {
                    if(a[i].x==s||a[i].y==s)
                    {
                        if(dds==ds)continue;
                        dds++;
                    }
                    if(a[i].x==t||a[i].y==t)
                    {
                        if(ddt==dt)continue;
                        ddt++;
                    }
                    cnt++;
                    a[i].use=1;
                    merge(a[i].x,a[i].y);
                }
            }
        }
        if(dds<=ds&&ddt<=dt&&cnt==n-1)
        {
            printf("Yes\n");
            for(int i=0;i<m;i++)
            {
                if(a[i].use==1)
                printf("%d %d\n",a[i].x,a[i].y);
            }
        }
        else //如果不行再反向跑一遍。
        {
            for(int i=1;i<=n;i++)f[i]=i;
            int vals,valt;
            if(ds>=dt)vals=1,valt=2;
            else vals=2,valt=1;
            for(int i=0;i<m;i++)
            {
                a[i].use=0;
                if(a[i].x==s||a[i].y==s)a[i].w=vals;
                if(a[i].x==t||a[i].y==t)a[i].w=valt;
            }
            int cnt=0;
            sort(a,a+m,cmp);
            int dds=0,ddt=0;
            for(int i=0;i<m;i++)
            {
                if(a[i].w==0)
                {
                    if(find(a[i].x)!=find(a[i].y))
                    {
                        cnt++;
                        a[i].use=1;
                        merge(a[i].x,a[i].y);
                    }
                }
                else
                {
                    if(find(a[i].x)!=find(a[i].y))
                    {
                        if(a[i].x==s||a[i].y==s)
                        {
                            if(dds==ds)continue;
                            dds++;
                        }
                        if(a[i].x==t||a[i].y==t)
                        {
                            if(ddt==dt)continue;
                            ddt++;
                        }
                        cnt++;
                        a[i].use=1;
                        merge(a[i].x,a[i].y);
                    }
                }
            }
            if(dds<=ds&&ddt<=dt&&cnt==n-1)
            {
                printf("Yes\n");
                for(int i=0;i<m;i++)
                {
                    if(a[i].use==1)
                    printf("%d %d\n",a[i].x,a[i].y);
                }
            }
            else
            {
                printf("No\n");
            }
        }
    }
}

```


---

## 作者：LKY928261 (赞：2)

将边分为三类：

1. 不与 $s$ 和 $t$ 相连；
2. 只与 $s$ 和 $t$ 中的任意一个相连；
3. 连接 $s$ 和 $t$。

对于第一类边，加入时不会对结果产生影响，可以任意加入，且越多越好。

对于第二和第三类边，加入时均会占用 $d_s$ 和/或 $d_t$ 的剩余容量，且第三类边会同时占用。

考虑对边加权，使每条边的边权等于其连接的两个点中的 $s$ 和 $t$ 的数量（即，第一类边边权为 $0$，第二类边为 $1$，第三类边为 $2$）。

接下来再跑 Kruskal，就可以做到优先加入第一类边，然后第二类，再是第三类。加边过程中同时维护 $d_s$ 和 $d_t$，若加入后无法满足则跳过这条边。最后再判定加入边数是否为 $n-1$。

[代码](https://codeforces.com/problemset/submission/723/190987337)

然而这样贪心会 WA on 68。

以下是第 68 组数据：

```
5 5
1 3
1 4
1 5
2 3
2 4
1 2 2 2
```

上述代码错判了无解。

观察数据，因为每条边都属于第二类边，上述代码会直接按读入顺序进行加边，导致结点 3,4 被占用，结点 2 只连出一条边，结点 1 却连出了 3 条。

但是，不难发现，只需要换一个读入顺序就不会出错。

于是，在加上 ``random_shuffle`` 之后，我们通过了此题。

[代码](https://codeforces.com/problemset/submission/723/190988287)

~~（这就是这道简单题能评 2300 的原因？）~~

咳咳，上面的只是一种基于随机化的乱搞而已，请勿模仿。下面来说说正解。

一开始的错误代码错在了加边的顺序。我们对加边权的策略进行一点调整：对于所有与点 $s$ 直接相连的边，将其边权加上 1；对于所有与点 $t$ 直接相连的边，将其边权加上 2。这样就保证了只与点 $s$ 相连的边会比所有只与 $t$ 相连的边更早尝试加入。

将加边策略反过来，就可以保证只与点 $t$ 相连的边会比所有只与 $s$ 相连的边更早尝试加入。

跑两遍 Kruskal 即可。

代码不难，在原来的基础上改改就行，此处不作展示。~~（因为我懒得写了）~~

---

## 作者：Locix_Elaina_Celome (赞：1)

# [CF723F st-Spanning Tree](https://www.luogu.com.cn/problem/CF723F) 题解
## 题意
给定一个 $n$ 个点 $m$ 条边的无向简单联通图。给定 $s$ 和 $t$，求一棵生成树，使得 $s$ 和 $t$ 的度数不超过 $ds$ 和 $dt$。若有解，输出“Yes”和方案，若无解，输出“No”。
## 题解

这个题可以用神奇的最小生成树做，但是我自己胡了一个神秘的线性做法。跑得很快，直接拿下最优解。

我们这里成 $s$ 和 $t$ 两个点为“关键点”。

发现不和关键点相邻的边都是可以乱选的，所以我们把整张图在不经过关键点的情况下分割成若干个连通块。连通块内部 dfs 树乱跑。因为每一个连通块是极大的，所以这时连通块之间肯定没有连边。

我们发现每个连通块要么只和一个关键点相邻，要么连接了两个关键点。

大概就是这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/l7jcy2ib.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

因为要构成一棵联通的生成树，所以只和一个点相邻的点（图中的 1267）强制和关键点连一条边。

对于剩下的点，选一个和关键点连接。注意要保证关键点的出度。

这时候发现整张图被分成了 $S$、$T$ 两个部分，我们要想办法连接起来。

使用 $S-T$ 这条边？明显是不优的，因为这样会在左右各花费一个度。如果我们选择一个关键点，向其没有连边的一个中间的点连一条边，就联通了，且只花费了一个出度。注意一种特殊情况，当中间没有点，只能用 $S$ 和 $T$ 直接连边。

如果发现无法在保证关键点的出度的情况下构造解，则无解。

## 代码

细节很多，容易写挂。

```cpp
using namespace std;
#include<bits/stdc++.h>
//#include<cstdio>
//#include<cstring>
//#include<string>
//#include<iostream>
//#include<utility>
//#include<algorithm>
#define MAX(x,y) (x<y?y:x)
#define MIN(x,y) (x<y?x:y)
#define ABS(x) (x<0?-x:x)
#define lb(x) ((x)&(-(x)))
#define N 1000005
#define LL long long
#define LD long double
//#define int LL
//#define double LD
#define P 1000000007
#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#elif _WINDOWS_
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#else
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
constexpr double EPS=(1e-9);
#ifdef int
constexpr int INF=1211081101201201140;
#else
constexpr int INF=1145141919;
#endif
template<typename T>T Max(T x,T y){return MAX(x,y);}
template<typename T>T Min(T x,T y){return MIN(x,y);}
template<typename T>T Abs(T x){return ABS(x);}
template<typename T>void Swap(T&x,T&y){x^=y^=x^=y;}
template<typename T>T Gcd(T x,T y){while(y^=x^=y^=x%=y);return x;}
template<typename T>
T qp(T a,T b){T sum=1;
while(b){if(b&1)sum=(sum*a)%P;a=(a*a)%P;b>>=1;}return sum;}
template<typename T>
void read(T&x){
x=0;char c=getchar();/*T fl=1;*/
while(c<'0'||c>'9'){/*if(c == '-')fl=-1;*/c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}/*x*=fl;*/}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);}
int t[N],las[N],fir[N],num;
void add(int u,int v){
t[++num]=v;las[num]=fir[u];fir[u]=num;
t[++num]=u;las[num]=fir[v];fir[v]=num;}
int fx,fy;
int dx,dy;
int n,m;
int col[N];
int cid;
queue<pair<int,int> > q;
void dfs(int u){
	col[u]=cid;
	for(int i=fir[u];i;i=las[i]){
		if(col[t[i]])continue;
		q.push({u,t[i]});
		dfs(t[i]);
	}
}
int fl[N][2];
int vis[N][2];
int vvis[N];
#undef int
int main(){
//#define int LL
	read(n);
	read(m);
	for(int i=1,x,y;i<=m;i++)
		read(x),read(y),add(x,y);
	read(fx),read(fy);
	read(dx),read(dy);
	col[fx]=++cid;
	col[fy]=++cid;
	for(int i=1;i<=n;i++)if(i!=fx&&i!=fy&&!col[i])++cid,dfs(i);
	for(int u=1;u<=n;u++){
		if(u==fx||u==fy)continue;
		for(int i=fir[u];i;i=las[i]){
			if(t[i]==fx)fl[col[u]][0]=1;
			if(t[i]==fy)fl[col[u]][1]=1;
		}
	}
	int cnt=cid-2;
	for(int u=3;u<=cid;u++){
		if(fl[u][0]==1&&fl[u][1]==0)dx--,cnt--,vis[u][0]=vis[u][1]=-1;
		if(fl[u][0]==0&&fl[u][1]==1)dy--,cnt--,vis[u][0]=vis[u][1]=-1;
	}
	if(cnt==0&&dx>=1&&dy>=1){
		for(int i=fir[fx];i;i=las[i]){
			if(t[i]==fx||t[i]==fy)continue;
			if(vis[col[t[i]]][0]<0){
				if(!vvis[col[t[i]]])q.push({fx,t[i]});
				vvis[col[t[i]]]=1;
				continue;
			}
		}
		for(int i=fir[fy];i;i=las[i]){
			if(t[i]==fx||t[i]==fy)continue;
			if(vis[col[t[i]]][0]<0){
				if(!vvis[col[t[i]]])q.push({fy,t[i]});
				vvis[col[t[i]]]=1;
				continue;
			}
		}
		puts("Yes");
		while(!q.empty()){
			write(q.front().first);
			putchar(' ');
			write(q.front().second);
			puts("");
			q.pop();
		}
		write(fx);
		putchar(' ');
		write(fy);
		return 0;
	}
	for(int i=fir[fx];i&&dx;i=las[i]){
		if(t[i]==fx||t[i]==fy)continue;
		if(vis[col[t[i]]][0]<0){
			if(!vvis[col[t[i]]])q.push({fx,t[i]});
			vvis[col[t[i]]]=1;
		}
	}
	for(int i=fir[fy];i&&dy;i=las[i]){
		if(t[i]==fx||t[i]==fy)continue;
		if(vis[col[t[i]]][0]<0){
			if(!vvis[col[t[i]]])q.push({fy,t[i]});
			vvis[col[t[i]]]=1;
		}
	}
	for(int i=fir[fx];i&&dx;i=las[i]){
		if(t[i]==fx||t[i]==fy)continue;
		if(vis[col[t[i]]][0]<0){
			if(!vvis[col[t[i]]])q.push({fx,t[i]});
			vvis[col[t[i]]]=1;
			continue;
		}
		if(vis[col[t[i]]][0]==1||vis[col[t[i]]][1]==1)continue;
		dx--;
		q.push({fx,t[i]});
		vis[col[t[i]]][0]=1;
	}
	for(int i=fir[fy];i&&dy;i=las[i]){
		if(t[i]==fx||t[i]==fy)continue;
		if(vis[col[t[i]]][0]<0){
			if(!vvis[col[t[i]]])q.push({fy,t[i]});
			vvis[col[t[i]]]=1;
			continue;
		}
		if(vis[col[t[i]]][0]==1||vis[col[t[i]]][1]==1)continue;
		dy--;
		q.push({fy,t[i]});
		vis[col[t[i]]][1]=1;
	}
	int fl=0;
	for(int i=fir[fx];i&&dx;i=las[i]){
		if(fl)break;
		if(t[i]==fx||t[i]==fy)continue;
		if(vis[col[t[i]]][0]<0)continue;
		if(vis[col[t[i]]][1])q.push({fx,t[i]}),fl=1,dx--;
	}
	for(int i=fir[fy];i&&dy;i=las[i]){
		if(fl)break;
		if(t[i]==fx||t[i]==fy)continue;
		if(vis[col[t[i]]][0]<0)continue;
		if(vis[col[t[i]]][0])q.push({fy,t[i]}),fl=1,dy--;
	}
	if((int)q.size()==n-1&&dx>=0&&dy>=0){
		puts("Yes");
		while(!q.empty()){
			write(q.front().first);
			putchar(' ');
			write(q.front().second);
			puts("");
			q.pop();
		} 
		return 0;
	}
	puts("No");
	return 0;
}
```

---

## 作者：Starlight_Glimmer (赞：1)

首先，可以把边分成两类：
一类是端点含s或t的，另一类是和s,t没有任何关系的。
第二类边可以随便乱连，而第一类边不可以。


所以，就先把第二类边乱连，随便连，反正没有边权连就是了，用一个并查集，相当于搞一个生成树森林出来，这样我们就有了很多很多块集合（相当于被缩成一个点，要注意细节）和s,t两个点。


集合中只与s,t的其中一个点有边的，只能连那个边，否则就不联通了。一边连一边判断s,t的度数，如果超过了就判定无解。


集合中和s,t都有边相连的，选一个和s,t都连一条边，这样可以使s,t联通的同时尽量最小化度数。（s,t直接相连，度数各增加1，某一个集合再和s,t中的一个相连，s,t中的一个度数会增加1）


剩下的和s,t都有边相连的集合，随便连s,t都可以。（如果一个点的度数被连完了，就连另外那个）


最后，如果没有和s,t都有边相连的集合，那么此时s,t还没有被连起来，那么还要在s,t之间直接连一条边。


注意还要判断它是不是一棵生成树的形态（边数为n-1）


```cpp
#include<cstdio>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define ll long long
#define N 200005
int n,m,s,t,ds,dt;
vector<int>G[N];
vector<pair<int,int> >ans;
int f[N];//并查集
int ls[N],lt[N];//编号为i的集合通过ls[i]/lt[i]和s/t相连 
inline int rd()
{
	int f=1,x=0;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-f;c=getchar();}
	while('0'<=c&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f*x;
}
int Find(int x)
{
	if(f[x]==x) return x;
	return f[x]=Find(f[x]);
}
bool Union(int u,int v)
{
	int x=Find(u),y=Find(v);
	if(x==y) return false;
	if(x<y) f[y]=x;
	else f[x]=y;
	return true; 
}
void Init()
{
	for(int i=1;i<=n;i++)
		f[i]=i;
} 
int main()
{
	n=rd(),m=rd();
	for(int i=1;i<=m;i++)
	{
		int u=rd(),v=rd();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	s=rd(),t=rd(),ds=rd(),dt=rd();
	Init();
	//乱连不含s,t的边 
	for(int u=1;u<=n;u++)
	{
		if(u==s||u==t) continue;
		for(int i=0;i<G[u].size();i++)
		{
			int v=G[u][i];
			if(v==s||v==t) continue;
			if(Union(u,v)) ans.push_back(make_pair(u,v));
		}
	}
	//处理集合的哪些边和s,t相连的情况 
	for(int i=0;i<G[s].size();i++)
		if(G[s][i]!=t)
		{
			int x=Find(G[s][i]);
			ls[x]=G[s][i];
		}
	for(int i=0;i<G[t].size();i++)
		if(G[t][i]!=s)
		{
			int x=Find(G[t][i]);
			lt[x]=G[t][i];
		}
	//处理只和s,t中的一个相连的集合 
	for(int i=1;i<=n;i++)
	{
		if(ls[i]&&!lt[i])
		{
			ds--;
			Union(s,i);
			ans.push_back(make_pair(s,ls[i]));
		}
		else if(!ls[i]&&lt[i])
		{
			dt--;
			Union(t,i);
			ans.push_back(make_pair(t,lt[i]));
		}
		if(ds<0||dt<0)
		{
			puts("No");
			return 0;
		}
	}
	//处理和s,t都相连的集合 第一个会和s,t都连 s,t连通之后就只会连一个 
	for(int i=1;i<=n;i++)
		if(ls[i]&&lt[i])
		{
			if(ds&&Union(s,i))
			{/*短路运算符 Union不能写在前面 或者也可以用find()判断 Union写在里面*/
				ds--;
				ans.push_back(make_pair(s,ls[i]));
			}
			if(dt&&Union(t,i))
			{
				dt--;
				ans.push_back(make_pair(t,lt[i]));
			}
			if(Find(s)!=Find(i)||Find(t)!=Find(i)) //说明前面没有办法连 度数都用完了 
			{
				puts("No");
				return 0;
			}
		}
	if(Find(s)!=Find(t))//s,t还没有连通
	{
		bool f=0;
		for(int i=0;i<G[s].size();i++)
			if(G[s][i]==t)
			{
				f=1;
				break;
			}
		if(ds&&dt&&f)
			ans.push_back(make_pair(s,t));
		if(!f)
		{
			puts("No");
			return 0;
		}
	}
	if(ans.size()!=n-1)
	{//满足是一棵生成树 
		puts("No");
		return 0;
	}
	puts("Yes");
	for(int i=0;i<ans.size();i++)
		printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
}

```


---

## 作者：Na2PtCl6 (赞：0)

看到题目和 Spanning Tree 有关，就觉得应该往并查集、连通块的方向想，然后再往下推就是考虑因为一个端点是 $s$ 或 $t$ 的边会受到限制，所以先禁用这些边跑一遍，把目前的极大连通块求出来，并找到这些连通块中能与 $s$，能与 $t$ 连边的节点，分别记为该连通块关于 $s$ 的代表性节点，关于 $t$ 的代表性节点。这个时候，我们就已经得到了一部分的答案，即极大连通块内部的边。

第二步，我们考虑把只能到达 $s$ 和 $t$ 二者之一的连通块优先与 $s$ 或 $t$ 连上，原因显然。答案就是那些代表性节点到 $s$ 或 $t$ 的边。

第三步，如果没有 $s$ 和 $t$ 都能到达的连通块，那么 $s$ 和 $t$ 之间就必须连一条边；如果存在 $s$ 和 $t$ 都能到达的连通块，那么先就用一个连通块来连接 $s$ 和 $t$ 所在连通块（因为这样做是比绝对不会比直接连接 $s$ 和 $t$ 更差的），然后就用 $s$ 和 $t$ 随便连向剩余的连通块，反正都是等价的。 

怎么判无解呢？第一步中，我们可以在处理代表性节点的时候顺便判一下联通性；第三步中，我们可以知道数据中的 $ds$ 和 $dt$ 够不够我们连。根据这两个判无解就足够了

CODE:（放在题解区应该算短的）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=400004;
char t_nei[maxn],s_nei[maxn];
int n,m,s,t,ds,dt,cntcon,u[maxn],v[maxn],fir[maxn],rep1[maxn],rep2[maxn],dsu[maxn];
bitset < maxn > to_s,to_t,inter;
deque< int > con,blk[maxn];
vector< pair<int,int> > ans;

int find(int k){ return dsu[k]==k?k:dsu[k]=find(dsu[k]);}

void output(){
	for(pair<int,int> i:ans)
		printf("%d %d\n",i.first,i.second);
}

int main(){
	scanf("%d %d",&n,&m);
	cntcon=n;
	for(int i=1;i<=n;i++)
		dsu[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d %d",&u[i],&v[i]);
	scanf("%d %d %d %d",&s,&t,&ds,&dt);
	for(int i=1;i<=m;i++){
		if(u[i]==s||v[i]==s||u[i]==t||v[i]==t)
			continue;
		fir[i]=1;
		int fu=find(u[i]),fv=find(v[i]);
		dsu[fu]=fv;
		if(fu!=fv)
		ans.push_back(make_pair(u[i],v[i]));
	}
	for(int i=1;i<=m;i++){
		if(fir[i])
			continue;
		if(u[i]==s||v[i]==s){
			if(u[i]!=s)
				swap(u[i],v[i]);
			s_nei[v[i]]=1;
			to_s[find(v[i])]=1;
		}
		if(u[i]==t||v[i]==t){
			if(u[i]!=t)
				swap(u[i],v[i]);
			t_nei[v[i]]=1;
			to_t[find(v[i])]=1;
		}
	}
	inter=to_s&to_t;
	for(int i=1;i<=m;i++){
		if(fir[i])
			continue;
		int fv=find(v[i]);
		if(u[i]==s&&!inter[fv]&&fv!=s&&v[i]!=t){
			dsu[fv]=s;
			ans.push_back(make_pair(s,v[i]));
			--ds;
		}
		if(u[i]==t&&!inter[fv]&&fv!=t&&v[i]!=s){
			dsu[fv]=t;
			ans.push_back(make_pair(t,v[i]));
			--dt;
		}
	}
	for(int i=1;i<=n;i++){
		int fi=find(i);
		if(fi!=s&&fi!=t){
			blk[fi].push_back(i);
			con.push_back(fi);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j:blk[i]){
			if(t_nei[j])
				rep1[i]=j;
			if(s_nei[j])
				rep2[i]=j;
		}
		if((rep1[i]==0||rep2[i]==0)&&blk[i].size()){
			puts("No");
			return 0;
		}
	}
	sort(con.begin(),con.end());
	int sz=unique(con.begin(),con.end())-con.begin();
	while(con.size()>sz)
		con.pop_back();
	if(sz==0&&ds&&dt&&to_t[s]==1){
		puts("Yes");
		ans.push_back(make_pair(s,t));
		output();
		return 0;
	}
	if(sz<ds+dt&&ds&&dt){
		char fresh=1;
		puts("Yes");
		while(!con.empty()){
			int rc1=rep1[con.front()],rc2=rep2[con.front()];
			if(fresh){
				--ds,--dt;
				ans.push_back(make_pair(s,rc2));
				ans.push_back(make_pair(t,rc1));
				fresh=0;
				con.pop_front();
				continue;	
			}
			if(ds){
				--ds;
				ans.push_back(make_pair(s,rc2));
				con.pop_front();
				continue;
			}
			if(dt){
				--dt;
				ans.push_back(make_pair(t,rc1));
				con.pop_front();
			}
		}
		output();
		return 0;
	}
	puts("No");
	return 0;
}
```

---

