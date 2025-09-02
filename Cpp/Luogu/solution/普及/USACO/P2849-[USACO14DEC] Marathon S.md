# [USACO14DEC] Marathon S

## 题目描述

由于对他的奶牛的健康状况不佳而感到不满，牧场主约翰让它们参加各种各样的体育健身活动。最让他感到自豪的奶牛是 Bessie，她将参加约翰牧场附近城市里的马拉松比赛！

马拉松比赛有 $N$ 个检查点 $(3\leq N\leq 500)$ ，需要按顺序访问。检查点 $1$ 是起点，检查点 $N$ 是终点。Bessie 应该按顺序一一访问所有的这些检查点，但由于她是一头懒惰的牛（懒惰竟然还选择跑马拉松！），于是她决定跳过 $K(K<N)$ 个检查点以缩小她的赛程。但她不能跳过第 $1$ 个和第 $N$ 个检查点，因为这样太明显了。

请你帮助 Bessie 计算出跳过中间的 $K$ 个检查点后她最少要跑多少距离。

注意：由于街道是网格状的，我们用坐标来表示点的位置。但是 $(x_1,y_1),(x_2,y_2)$ 两点间的距离应为 $|x_1-x_2|+|y_1-y_2|$，这种测量距离的方法被称为“曼哈顿”距离，这是因为在市中心的网格路中，你可以沿平行于 $x$ 轴或 $y$ 轴的方向走，但不能沿直线到达。

## 样例 #1

### 输入

```
5 2
0 0
8 3
1 1
10 -5
2 2```

### 输出

```
4```

# 题解

## 作者：ezоixx130 (赞：15)

这道题目是一道动规的题目。

令f[i][j]代表到了第i个检查点，跳过了j个的最短距离。

那么很容易写出转移方程：

f[i][j]=min(f[i-l-1][j-l]+dis(i,i-l-1))

~~（其实很暴力）~~

时间复杂度：O(n^3)但是常数很小。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,k,x[501],y[501],f[501][501],a[501][501];

inline int dis(int a,int b){
    return abs(x[a]-x[b])+abs(y[a]-y[b]);
}

int main()
{
    memset(f,0x7f,sizeof(f));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&x[i],&y[i]);
    }
    f[1][0]=0;
    for(int i=0;i<=n;++i)
        f[i][i]=0;
    for(int i=2;i<=n;++i)
        for(int j=0;j<=min(i-1,k);++j)
            for(int l=0;l<=j;++l)f[i][j]=min(f[i][j],f[i-l-1][j-l]+dis(i,i-l-1));
    printf("%d\n",f[n][k]);
}
```

---

## 作者：Del_Your_Heart (赞：6)

## 题目大意：
------------
### 给你$n$个点，除起点和终点外任选$(n-k)$个点组成的路径的曼哈顿距离最短。

### 还有一件事，非常重要：按题目给出的顺序形成路径。（开始我没看到这一点，以为这题很难，实际还挺简单。）

------------

**今天模拟赛难度榜$rank3$，还算比较简单的题了，但我却花了$1h$切这道题（我$tcl$）。**

**这里提供三种本蒟蒻在考场上想出来的思路（只有最后一种是正解）:**

### $1^o$ 我会暴力！：
枚举略过的点，时间复杂度$O(n*n!)$(?)

期望得分：~~想得分？做梦去吧！~~
### $2^o$ 我会$rand()$！

没错，你没看错，是$rand()$！~~用一个量子的状态~~随机决定每个检查点去不去，时间复杂度$O(n)$——计算每种状态的路径长度，再乘上一个次数$T$。我选的次数$T=150000$。

期望得分：$100pts*\frac{T+your RP}{2^n}$

我的得分：$18pts$(~~我$RP$还挺高嘛~~) 

**给出这种方法的代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,dis[505][505],ans=0x3f3f3f3f;
struct c_p{
	int x,y;bool b;
	int operator+ (const c_p a) const{
		return abs(a.x-x)+abs(a.y-y);
	}//计算距离
}p[505];
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
int main(){
	n=read();k=read();
	for(register int i=1;i<=n;++i)
		p[i].x=read()+1000,p[i].y=read()+1000;//变为正，不变也可
	int times=150000,sum=0;
	while(times--){
		sum=0;
		for(register int i=2;i<=n-1;++i)
			p[i].b=0;
		for(register int i=1;i<=k;++i){
			int op=rand()%(n-2)+2;//考验RP的时候到了
			if(p[op].b)
				i--;
			else 
				p[op].b=1;
		}
		for(register int i=2,last=1;i<=n;++i)
			if(!p[i].b){
				sum+=p[last]+p[i];//计算距离
				last=i;
			}
		ans=min(ans,sum);//取min值
	}
	cout<<ans;
}
```
**$3^o$ 我会$DP$!**

状态：$f[i][j]$表示略过$j$个检查点，到达第$i$个检查点所需的路径长度。

状态转移方程：$f[i][j]=\max{f[i][j-p]+w[i][i-p]},i,i-p\in[1,n]$

$ans=f[n][k].$

最优性证明：（~~显然~~）略过肯定比不略过更优，所以直接输出$f[n][k]$。

时间复杂度：$O(n^3)$ 

期望得分：$100pts$

**代码如下：(模拟赛上想出状态转移方程后$10min$就切掉了，连之前那个$rand()$的方法都花了$30min$)**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,f[505][505],ans=0x3f3f3f3f;
struct c_p{
	int x,y;
	int operator* (const c_p a) const{return abs(a.x-x)+abs(a.y-y);}
}p[505];
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
int main(){
	n=read();k=read();
	for(register int i=1;i<=n;++i)
		p[i].x=read()+1000,p[i].y=read()+1000;
	memset(f,0x3f,sizeof f);
	f[1][0]=0;
	for(register int i=1;i<=n;++i)
		for(register int c=0;c<=k;++c)
			for(register int s=0;s<=k&&i+s+1<=n;++s)
				f[i+s+1][c+s]=min(f[i+s+1][c+s],f[i][c]+p[i]*p[i+s+1]);
	cout<<f[n][k];
}
```







---

## 作者：linyinuo2008 (赞：4)

[原题链接](https://www.luogu.com.cn/problem/P2849)

这是一道非常不错的动归题，所以我写一篇题解来纪念一下。

这题如果不是按顺序来，将会是一道类似于[吃奶酪](https://www.luogu.com.cn/problem/P1433)与[砝码称重](https://www.luogu.com.cn/problem/P1441)合体版的蓝题。但是由于这只奶牛必须按给出的点顺序跑，所以我们就可以推出一个~~显而易见的~~动态转移方程：

设$f(i,j)$表示当前到第$i$个点，并且已经跳过$j$个点的最小路程，其中$1 \leq j \leq i \leq n$。

初始化：$f(i,i)$ $=$ $0$，$f(1,0)=0$

则$f(i,j)$ $=$ $min(f(i-p-1,j-p)+dis(i-p-1,i))$  （$1 \leq p \leq j \leq i \leq n$）,其中$dis(m,n)$表示第$m$个点与第$n$个点之间的曼哈顿距离。

而其中的意思也非常好理解，就是枚举每个点，然后枚举它最多跳过几个点，然后最小距离就是所有点这个点之前中去掉一些点取最小值，自己理解一下也应该很容易，复杂度$O(n \times k^2)$。

------------
上代码（有注释欧）：
```cpp
#include <iostream>
#include <cstring>
#include <cmath>//需要求绝对值函数 
using namespace std;
const int INF=0x7f7f7f;
const int N=505;
struct node//结构体存每个点 
{
	int x,y;
}a[N];
int n,k;
int f[N][N];
int dis(int i,int j)//楼梯状的曼哈顿距离 
{
	return abs(a[j].x-a[i].x)+abs(a[j].y-a[i].y);
}
int min(int l,int r)//手写min函数更快 
{
	return l<r?l:r;
}
int main()
{
	memset(f,INF,sizeof(f));
	int i,j,p;
	cin>>n>>k;
	for(i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
	}
	f[1][0]=0;
	for(i=0;i<=n;i++) f[i][i]=0;//初始化 
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=k&&j<i;j++)//j不能比k大（或者说我们不需要比k大的那一部分） 
		{
			for(p=0;p<=j;p++)//枚举上一步可能跳过几个点 
			{
				f[i][j]=min(f[i][j],f[i-p-1][j-p]+dis(i-p-1,i));//动归转移 
			}
		}
	}
	cout<<f[n][k];
	return 0;
}
```
撰写不易，管理员大大求通过！

**若有错误，欢迎指出！**

---

## 作者：NewErA (赞：3)

######写这篇题解主要是要告知这道题的测试数据其实是银组的啊！！！！

######不要被题面和样例所误导


一道比较普通的dp,设dp[i][j]表示前i个站中跳过j个站的最短路径

###可以比较轻松的写出状态转移方程：dp[i][j]=min(dp[i][j],dp[i-x-1][j-x]+distance(i-x-1,i))     (x<=i-1)

从而大致得到一个O(n\*k^2)的算法


面对此类问题时，一定要仔细考虑循环范围和各种边界的初始化处理！！！


附上代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
int n,k,dp[505][505];

struct marathon
{
    int x,y;
}a[505];

int dis(int p,int q)
{
    return abs(a[p].x-a[q].x)+abs(a[p].y-a[q].y);
}

int main()
{
    cin >> n >> k;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i].x >> a[i].y;
    }
    
    for(int i=1;i<=n;i++)
        for(int j=0;j<=k;j++)
            dp[i][j]=1<<27;
    
    dp[1][0]=0;
    for(int i=1;i<=n;i++) dp[i][i]=0;
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<=min(i-1,k);j++)
        {
            for(int m=0;m<=j;m++)
            {
                dp[i][j]=min(dp[i][j],dp[i-m-1][j-m]+dis(i-m-1,i));
            }
        }
    }
    
    cout << dp[n][k];
    return 0;
}
```


---

## 作者：pocafup (赞：2)

这题其实 dp 的方法显然，但是作为一个图论爱好者，dp 什么的都不存在的。

有人讲了分层图最短路，我这里提供一种更加普及的建图方法。

连边方法就是暴力连接每个点和后面的 $k$ 个点，但是我struct 了一个结构体记录（这样就不需要分层）。

```cpp
struct Edge{
  int t,dis,skip;
};
for (int i=1;i<=n;i++){
    for (int j=i+1;j<=min(n,i+k+1);j++){
      adj[i].push_back((Edge){j,distance(pos[i],pos[j]),j-i-1});
    }
  }
```
令 $dist[i][j]$ 表示现在在第 $i$ 个点，已经跳了 $j$ 个点。

之后对着图跑一遍 dij，最后答案就是在终点跳过 $k$ 个点的答案。

```cpp
inline void solve(){
  priority_queue<pair<int,pp> > q;q.push(make_pair(0,make_pair(1,0)));
  while(!q.empty()){
    int qf = q.top().s.f,qs = q.top().s.s; q.pop();
    if (qf==n && qs==k) break;
    for (Edge v : adj[qf]){
      if (qs+v.skip>k) continue;
      if (dist[v.t][qs+v.skip]>dist[qf][qs]+v.dis){
        dist[v.t][qs+v.skip] = dist[qf][qs]+v.dis;
        q.push(make_pair(-dist[v.t][qs+v.skip],make_pair(v.t,qs+v.skip)));
      }
    }
  }
  cout << dist[n][k];
}
```



---

## 作者：YangXiaopei (赞：1)

本蒟蒻真的很不理解各位大佬为什么都将 `DP` 的第二维设为跳过了几个检查点。

直接设为通过几个检查点不方便吗？

把 $k$ 变成 $n - k$ 不就可以了。

剩下的就和其他题解差不多了。

`DP` 定义：$dp_{i, j}$ 表示走到第 $i$ 个点，通过了 $j$ 个检查点的最小路程。

转移方程：$dp_{i, j} = \min\limits_{l = 1} ^ {i - 1}dp_{l, j - 1} + \left\vert x_i - x_l \right\vert + \left\vert y_i - y_l \right\vert$

答案：$dp_{n, k}$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, k, x[505], y[505], dp[505][505];
signed main(){
	cin >> n >> k;
    k = n - k;
	for(int i = 1; i <= n; i++){
		cin >> x[i] >> y[i];
	}
    memset(dp, 0x3f, sizeof(dp));
    dp[1][1] = 0;
    for(int i = 2; i <= n; i++){
		dp[i][2] = abs(x[i] - x[1]) + abs(y[i] - y[1]);
	}
	for(int i = 2; i <= n; i++){
		for(int j = 3; j <= min(i, k); j++){
			for(int l = 1; l < i; l++){
				dp[i][j] = min(dp[i][j], dp[l][j - 1] + abs(x[i] - x[l]) + abs(y[i] - y[l]));
			}
		}
	}
	cout << dp[n][k];
	return 0;
}
```

---

## 作者：IcyFoxer_XZY (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P2849)

这道题可以用 $DP$ 做，还是挺简单的。

首先题目要求我们求最短距离，那么我们可以用 $dp[i][j]$ 来表示走到第 $i$ 个检查点跳过 $j$ 个检查点时的最短距离。于是状态转移方程就不难得出：$dp[i][j]=min(dp[i][j],dp[i-l-1][j-l]+dist(i,i-l-1)$。其中 $dist$ 是求曼哈顿距离的函数。

### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register int
const int N=505;
int n,k,x[N],y[N],dp[N][N];
inline int dist(int a,int b){return abs(x[a]-x[b])+abs(y[a]-y[b]);}//曼哈顿距离 
int main(){
    memset(dp,0x7f,sizeof dp);
    scanf("%d%d",&n,&k);
    for(re i=1;i<=n;++i)scanf("%d%d",&x[i],&y[i]);//输入坐标 
    dp[1][0]=0;
    for(re i=0;i<=n;++i)dp[i][i]=0;
    for(re i=2;i<=n;++i)
        for(re j=0;j<=std::min(i-1,k);++j)
            for(re l=0;l<=j;++l)
				dp[i][j]=std::min(dp[i][j],dp[i-l-1][j-l]+dist(i,i-l-1));//状态转移方程 
    printf("%d",dp[n][k]);
    return 0;
}
```
Bye！

---

## 作者：jiang_cheng (赞：1)

## 解题思路：
首先分析题目：Bessie$\ $ 需要按顺序访问$\ N\ $个检查点。所以这道题有拓扑序，自然而然就想到了$\ $DP。

令$\ f(i,\ j)\ $表示前$\ i\ $个点已经跳过$\ j\ $个点的最小路程。

那么就可以得到状态转移方程：
$$f(i,\ j)=\min(f(p,\ j - (i - p - 1) + dis(p,\ i)).$$
其中，$p\ $表示上个经过的检查点。

预处理：
$$f(1,\ 0)=0.$$ 
答案为：
$$f(n,\ k).$$
## 附上代码：
```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int kMaxN = 5e2 + 1;

int n, k, f[kMaxN][kMaxN];
struct E {
  int x, y;
} e[kMaxN];

int dis(int a, int b) {
  return abs(e[a].x - e[b].x) + abs(e[a].y - e[b].y);  //求曼哈顿距离
}

int main() {
  //freopen("marathon.in", "r", stdin);
  //freopen("marathon.out", "w", stdout);
  cin >> n >> k;
  fill(&f[0][0], &f[0][0] + kMaxN * kMaxN, 1e9);  //初始化
  for (int i = 1; i <= n; i++) {
    cin >> e[i].x >> e[i].y;
  }
  f[1][0] = 0;                                                      //预处理
  for (int i = 1; i <= n; i++) {                                    //枚举前i个点
    for (int j = 0; j <= k; j++) {                                  //枚举当前略过多少检查站
      for (int p = 1; p < i; p++) {                                 //枚举经过的上个检查站
        f[i][j] = min(f[i][j], f[p][j - (i - p - 1)] + dis(p, i));  //动规转移
      }
    }
  }
  cout << f[n][k];  //输出答案
  return 0;
}


```


---

## 作者：俺是小程 (赞：1)

这里提供一种分层图最短路的方法.   
暴力的向**_跨点以后所到达的点_**连边, 顺便记录下跨过的点数.  
然后就是普通的分层图最短路板子了.   
注意这里的转移除了要满足最短路的松弛条件以外, 还要满足总转移次数不超过$K$.   
理论复杂度好像比dp好一些, 但是常数大得多.

```cpp
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;
const int MAXN = 5e2 + 10;
inline int read()
{
    int x = 0; char ch = getchar(); bool flag = false;
    while(!isdigit(ch)) flag |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return flag ? -x : x;
}

struct edge
{
    int to, cost, cnt;
};vector<edge> g[MAXN];

inline int calc(P &a, P &b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int N, K;
P a[MAXN];

struct Node
{
    int val, pos, cnt;
    bool operator <(const Node &rhs) const{
        return val > rhs.val;
    }   
};
int dis[MAXN][MAXN];
void dijkstra(){
    priority_queue<Node> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[0][1] = 0; q.push((Node){0, 1, 0});

    while(!q.empty()){
        Node u = q.top(); q.pop();

        if(dis[u.cnt][u.pos] < u.val) continue;

        for(int i = 0; i < (int) g[u.pos].size(); i++){
            edge &e = g[u.pos][i];

            if(u.cnt + e.cnt > K) break;
            if(dis[u.cnt + e.cnt][e.to] > u.val + e.cost) {
                dis[u.cnt + e.cnt][e.to] = u.val + e.cost;
                q.push((Node){dis[u.cnt + e.cnt][e.to], e.to, u.cnt + e.cnt});
            }
        }
    }
}

int main()
{
    // freopen("p2849.in", "r", stdin);
    cin>>N>>K;
    for(int i = 1; i <= N; i++)
        a[i].first = read(), a[i].second = read();
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= min(N - i, K); j++)
            g[i].push_back((edge){i + j, calc(a[i], a[i + j]), j - 1});
    }
    dijkstra();
    cout<<dis[K][N]<<endl;
    return 0;
}
```

---

## 作者：曹老师 (赞：1)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco14dec-marathon.html)

DP题。

设$f_{i,j}$表示前$i$个检查站跳过了$j$个检查站的距离

状态转移方程：$f_{i,j} = min( f_{i-x-1,j-x} + dis_{i,i-x-1} ) , x \in [0 , i-1]$

预处理：$f_{1,0} = 0 , f_{i,i} = 0$

答案：$f_{n,k}$

## Code ##

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;

struct Node {
	int x , y;
};
Node node[505];
int n , k , dp[505][505];

int dis(int x,int y){
 	return abs(node[x].x - node[y].x) + abs(node[x].y- node[y].y);
}

int main() {
	memset(dp , 0x3f , sizeof(dp));
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++)
		scanf("%d%d",&node[i].x,&node[i].y);
	dp[1][0] = 0;
	for(int i=0; i<=n; i++)
		dp[i][i] = 0;
	for(int i=2; i<=n; i++)
		for(int j=0; j<=min(i-1,k); j++)
			for(int l=0; l<=j; l++)
				dp[i][j] = min(dp[i][j] , dp[i-l-1][j-l] + dis(i,i-l-1));
	printf("%d",dp[n][k]);
	return 0;
}
```


  [1]: http://usaco.org/index.php?page=viewproblem2&cpid=492
  [2]: https://www.luogu.org/problemnew/show/P2849

---

## 作者：ysj1173886760 (赞：1)

考前发个题解加一下RP。


其实这道题分层图和dp是一个做法，只是不同的实现形式而已。

毕竟用最短路来做dp的貌似也不少。

（最短路不就是dp么）

貌似我的转移和其他的不太一样。


dp[i][j]表示第i个检查点，已经跳过了j次的最小值。

这种线性的递推一般都是满足最优子结构的，其实我也不会证明。

那么这个状态可能由之前的某个状态转移而来。

因为可能一下跳很多次，所以需要枚举是从哪个检查点跳过来的。

然后计算一下之间的差值，转移就行了。

具体来说：
如果i由l转移而来，他们之间间隔的检查点就是i-l-1个。

也就是说跳过了i-l-1个检查点。

dp[i][j]就可以由dp[l][j-(i-l-1)]转移而来。

因为j是已经跳过了几个。

减去就是在l的时候跳过了几个检查点。

由于第一个和第n个不能跳过。

我们的转移方程不会跳过当前的点，而是选择之前的一段区间来跳过。

所以n必定不会被跳过，因为最多到n。

对于1来说，我们直接令dp[1][0]=0,从2开始递推即可。

同样的，枚举之前状态的时候从1开始枚举，不从0。

那么这个问题就解决啦。

上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn=5e2+10;

int n,k; 
int dp[maxn][maxn],xx[maxn],yy[maxn];

int jdz(int x)			//绝对值 
{
	return x>=0?x:-x;
}
int main()
{
	memset(dp,0x3f,sizeof(dp));
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d %d",&xx[i],&yy[i]);
	dp[1][0]=0;//初始化 
	for(int i=2;i<=n;i++)
	{
		dp[i][0]=dp[i-1][0]+jdz(xx[i]-xx[i-1])+jdz(yy[i]-yy[i-1]);//单独处理一次都不跳的。 
		for(int j=1;j<=k;j++)
			for(int l=1;l<i;l++)
				if(j>=i-l-1)dp[i][j]=min(dp[i][j],dp[l][j-i+l+1]+jdz(xx[i]-xx[l])+jdz(yy[i]-yy[l]));//这里要防止下标溢出。 
	}
	cout<<dp[n][k];
	return 0;
}
```

---

## 作者：ruanwentao666 (赞：0)

~~说实话，第一次看到这题还以为是 Dijkstra。~~

题目意思很简单，就是从 $n$ 个点中删去 $k$ 个，使得剩下的点的距离最小。

算法：类 FLoyd 动规

既然是动规，那么就要有动规四部曲：

- 定义状态：定义 $f_{i,j}$ 为删除了 $j$ 个节点到达第 $i$ 个节点所经过的最短路程
- 转移方程：$f_{i,j} = \min(f_{i,j},f_{i-l-1,j-k}+dis_{i,i-l-1})$
- 边界：$f_{1,0} = f_{i,i} = 0$
- 答案：$f_{n,k}$

下面展现 AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=505;
int n,k,x[N],y[N],f[N][N];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	memset(f,0x3f,sizeof(f));
	f[1][0]=0;
    for(int i=1;i<=n;i++)f[i][i]=0;
	for(int i=2;i<=n;i++){
		int b=min(i-1,k);
		for(int j=0;j<=b;j++){
			for(int l=0;l<=j;l++){
				f[i][j]=min(f[i][j],f[i-l-1][j-l]+abs(x[i]-x[i-l-1])+abs(y[i]-y[i-l-1]));
			}
		}
	}
	cout<<f[n][k];
	return 0;
}

```


---

