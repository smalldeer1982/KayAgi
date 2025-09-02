# [ABC132E] Hopscotch Addict

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc132/tasks/abc132_e

ケンくんはけんけんぱが大好きです。今日は有向グラフ $ G $ の上でけんけんぱをすることにしました。 $ G $ は $ 1 $ から $ N $ で番号付けされた $ N $ 頂点および $ M $ 辺からなり、 $ i $ 番目の辺は頂点 $ u_i $ から頂点 $ v_i $ に接続しています。

ケンくんははじめ頂点 $ S $ にいて、頂点 $ T $ までけんけんぱで移動したいです。 $ 1 $ 回のけんけんぱでは、「自分の今いる頂点から出ている辺を $ 1 $ つ選んで、その辺が接続する頂点に移動する」という操作をちょうど $ 3 $ 回連続で行います。

ケンくんが頂点 $ T $ に移動することができるか、また移動できるなら最小何回のけんけんぱで頂点 $ T $ まで移動することができるかを答えてください。 けんけんぱの操作の途中で頂点 $ T $ に訪れても、「頂点 $ T $ に移動できた」とは見なさないことに注意してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min(10^5,\ N\ (N-1)) $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N(1\ \leq\ i\ \leq\ M) $
- $ u_i\ \neq\ v_i\ (1\ \leq\ i\ \leq\ M) $
- $ i\ \neq\ j $ ならば $ (u_i,\ v_i)\ \neq\ (u_j,\ v_j) $
- $ 1\ \leq\ S,\ T\ \leq\ N $
- $ S\ \neq\ T $

### Sample Explanation 1

$ 1 $ 回目のけんけんぱでは $ 1\ \rightarrow\ 2\ \rightarrow\ 3\ \rightarrow\ 4 $、$ 2 $ 回目のけんけんぱでは $ 4\ \rightarrow\ 1\ \rightarrow\ 2\ \rightarrow\ 3 $ と移動することで頂点 $ 3 $ に辿り着くことができ、これが最小回数です。

### Sample Explanation 2

何回けんけんぱを繰り返しても頂点 $ 1 $ に辿り着くため、頂点 $ 2 $ に移動することは不可能です。 けんけんぱの途中で頂点 $ 2 $ を通過することはできますが、これは移動できたとは見なしません。

### Sample Explanation 3

頂点 $ S $ と頂点 $ T $ は非連結である場合があります。

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 4
4 1
1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1
1 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
2 0
1 2```

### 输出

```
-1```

## 样例 #4

### 输入

```
6 8
1 2
2 3
3 4
4 5
5 1
1 4
1 5
4 6
1 6```

### 输出

```
2```

# 题解

## 作者：RainFestival (赞：8)

因为每次只能走 $3$ 步

我们这么做

将每一个点拆成三个点，每个点表示走 $3k,3k+1,3k+2$ 步, $k$ 是整数

用 bfs 跑一边最短路

时间复杂度 $O(n+m)$

代码：

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#define f(x,k) 3*(x-1)+k+1
std::vector<int> a[300005];
int n,m,s,t,dis[300005];
void add(int x,int y){a[x].push_back(y);}
void bfs(int s)
{
	std::queue<int> q;
	for (int i=1;i<=3*n;i++) dis[i]=1000000000;
	dis[s]=0;q.push(s);
	while (!q.empty())
	{
		int v=q.front();q.pop();
		for (int i=0;i<a[v].size();i++)
		{
			int u=a[v][i];
			if (dis[v]+1<dis[u]) dis[u]=dis[v]+1,q.push(u);
	    }
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(f(x,0),f(y,1));
		add(f(x,1),f(y,2));
		add(f(x,2),f(y,0));
	}
	scanf("%d%d",&s,&t);
	bfs(f(s,0));
	printf("%d\n",dis[f(t,0)]!=1000000000?dis[f(t,0)]/3:-1);
}
```
然后就 AC 了

QAQ

---

## 作者：chu_K (赞：7)

很容易想到，对于原图，每个点三次以后能到达的点重新建图，然后在新的图上跑最短路。

我一交，发现超时了。

为什么超时？？？哦！原来是重复连边了，在完全图之类的图中，两个点之间走三步的方案可能有很多种，于是重边会有很多很多，造成了超时，其实就算不超时，空间也开不下。

所以，我们想办法优化这个问题。

怎么优化呢？由于建图会重复，可以不要建新的图，就在原图上做。

现在考虑如何在原图上做，我们可以使用 Saber-Xuhf 算法，避免掉重复，核心思想是把一个点拆成三个，记一下到这个点的步数膜三后的值，答案就是膜零后拆成的那个点。

细节就自己完善吧。

核心代码:

```cpp
void Saber-Xuhf(){
    memset(d,0x3f,sizeof(d));
    memset(v,0,sizeof(v));
    d[s]=0;
    q.push(make_pair(0,s));
    while(q.size()){
        ll x=q.top().second; q.pop();
        if(v[x]) continue;
        v[x]=1;
        for(ll i=head[x]; i; i=Next[i]){
            ll y=ver[i],z=edge[i];
            if(d[y]>d[x]+z){
                d[y]=d[x]+z;
                q.push(make_pair(-d[y],y));
            }
        }
    }
}

```

---

## 作者：lkjzyd20 (赞：6)

### [题目传送门](https://www.luogu.com.cn/problem/AT4733)
___
### 思路

分层图跑最短路。

___

$∵$ 题目中说每次只能走 $3$ 步， $∴$ 我们可以把一条边拆成三条边，
拆成 $1$ 到 $2$，$2$ 到 $3$，$3$ 到 $2$ 的三条边权为 $1$ 的边。

连边时，可以把边建在所有边的后面：

```cpp
add (x, y + n) ;
add (x + n, y + n * 2) ;
add (x + n * 2, y) ;
```

然后跑一遍从 $S$ 开始的最短路。

$∵$ 因为每个点都跑了三遍，$∴$ 最终答案 $val_t \div 3$。
 
其他题解跑最短路大多数用的是 `Dijkstra `，我就用 `SPFA` 写吧。

代码如下：

```cpp
#include <stdio.h>
#include <cstring>
#include <queue>

using namespace std;

const int N = 3e5 + 10; // 这里数组要开三倍，因为要连三条边。
const int INF = 0x3f3f3f3f;

void add (int, int) ;
void SPFA (int) ;

bool f[N];

int n, m;
int s, t;
int tot;
int val[N];
int now[N], pre[N], son[N];

queue <int> q;

main () {
    scanf ("%d %d", &n, &m) ;
    
    for (int x, y; m; -- m) {
        scanf ("%d %d", &x, &y) ;
        
        // 连三条边。
        add (x, y + n) ;
        add (x + n, y + n * 2) ;
        add (x + n * 2, y) ;
    }
        
    scanf ("%d %d", &s, &t) ;
    
    SPFA (s) ;
    
    if (val[t] == INF)
        puts ("-1") ;
    else
        printf ("%d", val[t] / 3) ; // 最终答案除以三。
}

void add (int x, int y) { // 建图。
    pre[++ tot] = now[x];
    son[tot] = y;
    now[x] = tot;
}

void SPFA (int s) { // SPFA 求最短路。
    memset (val, 0x3f, sizeof val) ;
    val[s] = 0;
    q.push (s) ;
    
    for (; !q.empty () ;) {
        int x = q.front () ;
        q.pop () ;
        f[x] = 1;
        
        for (int i = now[x]; i; i = pre[i]) {
            int y = son[i];
            
            if (val[y] > val[x] + 1) {
                val[y] = val[x] + 1;
                   
                if (!f[y]) {
                    f[y] = 1;
                    q.push (y) ;
                }
            }
        }
    }
}
```

### 完结撒花 $\sim\sim\sim$


---

## 作者：蒟酱 (赞：3)

看了一下题解，发现全是把一个点拆成三个点然后跑分层图最短路的，但是我一看感觉就是普通的 bfs。

题意是在图内询问从 $s$ 到 $t$ 是否存在长度为 $3$ 的路径。不妨开一个数组，$vis_{i,j}$ 表示是否存在从点 $s$ 出发，是否存在长度模 $3$ 是 $j$ 的路线。那么每次更新就是 $vis_{v,(x+1)\bmod3}=vis_{u,x}$，这样复杂度是 $\mathcal O(n+m)$ 的。

很短而且很快的 code：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<queue>
#define siz(x) (int)(x).size()
using std::cin;using std::cout;
constexpr int kN=1e5+1;
std::basic_string<int>g[kN];
using pii=std::pair<int,int>;
bool vis[kN][3];
int n,m,s,t;
signed main(){
//	freopen("checkers.in","r",stdin);
//	freopen("checkers.out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++)cin>>u>>v,g[u]+=v;
	cin>>s>>t;vis[s][0]=true;
	std::queue<pii>q({{s,0}});
	while(!q.empty()){
		auto[u,x]=q.front();x++;q.pop();
		for(int v:g[u])if(!vis[v][x%3]){
			if(v==t&&x%3==0)return cout<<x/3,0;
			vis[v][x%3]=true;
			q.emplace(v,x);
		}
	}
	cout<<"-1";
//	std::cerr<<"\033[33;40muse "<<clock()<<" ms\033[37;40m";
	return 0;
}
```
用 `basic_string` 存图，比 `vector` 快但是略慢于链式前向星，还有语法糖，插入可以使用 `+=` 运算符，多好！

---

## 作者：panyanppyy (赞：3)

## Solution
分层图最短路。

考虑每次只能走三步，那么把每条边拆开，拆为第一步到第二步，第二步到第三步，第三步到第一步三条边权为一的边，就可以避免到达终点但没有走到三的倍数步的情况了。
## Do it
~~英语不好勿喷。~~

具体可以把点建在所有点的序号之后：
```cpp
add(u,v+n),add(u+n,v+n+n),add(u+n+n,v);
```
然后从 $s\longrightarrow t$ 跑一遍最短路，$\dfrac{dis_t}{3}$ 就是最后答案了。

注意点和边都要开**三倍**（为此我 $\color{red}\text{WA}$ 了一发）。

时间复杂度：$O(m+n\log{n})$。

还不懂可以看注释：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=3e5+1233,N=3e5+1233;//开三倍
int n,m,nxt[M],go[M],head[M],s,t,l,g[N];
bool vis[N];
inline void add(int u,int v){
	nxt[++l]=head[u];
	head[u]=l;
	go[l]=v;
}//建图
struct qjc{
	int dis,pos;
	inline bool operator<(const qjc&b)const{
		return dis>b.dis;
	}
};
priority_queue<qjc>q;
inline void dj(int u){int v;
	memset(g,0x3f,sizeof(g));
	q.push({0,u}),g[u]=0;
	while(!q.empty()){
		u=q.top().pos;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int j=head[u];j;j=nxt[j])
			if(g[v=go[j]]>g[u]+1){
		    	g[v]=g[u]+1;
		    	if(!vis[v])q.push({g[v],v});
			}
	}
}//Dijkstra堆优化
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		add(x,y+n),add(x+n,y+(n<<1)),add(x+(n<<1),y);
	}//建三条边
	scanf("%d%d",&s,&t);
	dj(s);//最短路
	printf("%d",g[t]==0x3f3f3f3f?-1:g[t]/3);
   	//因为每个点都走了三遍所以答案除以三
	return 0;
}
```

---

## 作者：让风忽悠你 (赞：1)

分层图最短路。

考虑到 $s$ 到 $t$ 的最短路长度可能 $\nmid$ 3，所以将一个点分为三个点 $3k,3k+1,3k+2$ (k 为正整数)，分别表示到这个点刚好走完三步、多出 1 步、多出 2 步。

然后从 $s$ 开始跑最短路，$dis_t \div 3$，除以三是因为分成了三个点。

```cpp
#include<cstdio>
#include<algorithm>
#include<queue> 
#define N 300005
#define inf 0x7ffffff

using namespace std;

int n,m,s,t,tot;
int head[N],dis[N];
bool vis[N];

struct edge{
	int nxt,to;
}e[N];

struct node{
	int dis,id;
	bool operator <(const node &x) const {return x.dis<dis;}
};

void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}

void dij(int s){
	queue <node> q;
	for(int i=1;i<=3*n;i++)
		dis[i]=inf; 
	q.push((node){0,s});
	dis[s]=0;
	while(!q.empty()){
		int u=q.front().id;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				if(!vis[v]) q.push((node){dis[v],v});
			}
		}
	}
} // 最短路基本操作 

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v+n);
		add(u+n,v+2*n);
		add(u+2*n,v);
	} // 建图 
	scanf("%d%d",&s,&t);
	dij(s);
	printf("%d",dis[t]==inf?-1:dis[t]/3);// 判断是否有解 
	return 0;
}
```


---

## 作者：yinpeichu2021 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT4733)

## sol

分层图最短路。

考虑到每次只能走 $3$ 步，所以把每条边拆开，拆为第 $1$ 步到第 $2$ 步，第 $2$ 步到第 $3$ 步，第 $3$ 步到第 $1$ 步三条边，就可以避免到达终点但没有走到 $3$ 的倍数步的情况了。

具体点，建 $x$ 与 $y+n$、$x+n$ 与 $y+2\times n$ 、$x+2\times n$ 与 $y$ 三条边。

最终算出来的答案 $step$ 要除以 $3$。

**正解代码:**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,st,en,ans=INT_MAX;
int nextt[2000005],head[2000005],to[2000005],tot;//链式前向星
//数组一定要开大点，因为要拆成三个点
bool vis[2000005];
struct node{
    int x,step;
};
void add(int x,int y){//加边
    nextt[++tot]=head[x];
    to[tot]=y;
    head[x]=tot;
}
queue<node>q;
void bfs(int st,int en){
    q.push({st,0});
    while(!q.empty()){
        node top=q.front();
        q.pop();
        for(int i=head[top.x];i;i=nextt[i]){
            int v=to[i];
            if(v==en&&top.step%3==2)
//现在走一步后就走到结束点且刚好差一步，可以直接输出，算是一个小剪枝。
                cout<<(top.step+1)/3,exit(0);
            if(!vis[v]){
                q.push({v,top.step+1});
                vis[v]=1;
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y+n);
        add(x+n,y+2*n);
        add(x+2*n,y);
    }
    scanf("%d%d",&st,&en);
    bfs(st,en);
    cout<<-1;//无解
    return 0;
}
```

---

