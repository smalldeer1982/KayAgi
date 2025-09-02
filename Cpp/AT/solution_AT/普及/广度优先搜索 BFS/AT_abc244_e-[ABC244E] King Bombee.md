# [ABC244E] King Bombee

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc244/tasks/abc244_e

$ N $ 頂点 $ M $ 辺の単純無向グラフが与えられます。このグラフの頂点には $ 1 $ から $ N $ の番号が付けられており、辺には $ 1 $ から $ M $ の番号が付けられています。辺 $ i $ は頂点 $ U_i $ と頂点 $ V_i $ の間を結んでいます。

整数 $ K,\ S,\ T,\ X $ が与えられます。以下の条件を満たす数列 $ A\ =\ (A_0,\ A_1,\ \dots,\ A_K) $ は何通りありますか？

- $ A_i $ は $ 1 $ 以上 $ N $ 以下の整数
- $ A_0\ =\ S $
- $ A_K\ =\ T $
- 頂点 $ A_i $ と頂点 $ A_{i\ +\ 1} $ の間を直接結ぶ辺が存在する
- 数列 $ A $ の中に整数 $ X\ (X≠S,X≠T) $ は偶数回出現する ( $ 0 $ 回でも良い)

ただし、答えは非常に大きくなることがあるので、答えを $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ <\ =N\ <\ =2000 $
- $ 1\ <\ =M\ <\ =2000 $
- $ 1\ <\ =K\ <\ =2000 $
- $ 1\ <\ =S,T,X\ <\ =N $
- $ X≠S $
- $ X≠T $
- $ 1\ <\ =U_i\ <\ V_i\ <\ =N $
- $ i≠j $ ならば $ (U_i,\ V_i)≠(U_j,\ V_j) $

### Sample Explanation 1

\- $ (1,\ 2,\ 1,\ 2,\ 3) $ - $ (1,\ 2,\ 3,\ 2,\ 3) $ - $ (1,\ 4,\ 1,\ 4,\ 3) $ - $ (1,\ 4,\ 3,\ 4,\ 3) $ の $ 4 $ 個が条件を満たします。$ (1,\ 2,\ 3,\ 4,\ 3) $ や $ (1,\ 4,\ 1,\ 2,\ 3) $ は $ 2 $ が奇数回出現するため、条件を満たしません。

### Sample Explanation 2

グラフは連結であるとは限りません。

### Sample Explanation 3

$ 998244353 $ で割ったあまりを求めてください。

## 样例 #1

### 输入

```
4 4 4 1 3 2
1 2
2 3
3 4
1 4```

### 输出

```
4```

## 样例 #2

### 输入

```
6 5 10 1 2 3
2 3
2 4
4 6
3 6
1 5```

### 输出

```
0```

## 样例 #3

### 输入

```
10 15 20 4 4 6
2 6
2 7
5 7
4 5
2 4
3 7
1 7
1 4
2 9
5 10
1 3
7 8
7 9
1 6
1 2```

### 输出

```
952504739```

# 题解

## 作者：SunnyYuan (赞：6)

[更好的阅读体验](https://www.cnblogs.com/PlayWithCPP/p/17047027.html)

### 原题：

[Atcoder ABC244E - King Bombee](https://atcoder.jp/contests/abc244/tasks/abc244_e)

### 题意

给你一张图，从 $S$ 到 $T$，经过 $k$ 条边， 经过 $X$ 号点偶数次的方案数。

### 做法

设 $f_{i, j, k}$ 表示经过 $i$ 条边，现在在 $j$，经过 $X$ 的次数的奇偶。

初始状态：

$f_{0, S, 0} = 1$

状态转移：

$f_{i, u, k} = \sum_{(u, v) \in E}f_{i - 1, v, k}(u \ne X)$

$f_{i, u, k} = \sum_{(u, v) \in E}f_{i - 1, v, 1 - k}(u = X)$

即如果当前节点为 $X$，那么从上一个节点到这个节点需要改变奇偶（因为到达 $X$ 的点数会 $+ 1$ 所以会改变奇偶性。

对应：

$f_{i, u, k} = \sum_{(u, v) \in E}f_{i - 1, v, 1 - k}(u = X)$

如果当前节点不为 $X$，那么奇偶性不会变。

对应：

$f_{i, u, k} = \sum_{(u, v) \in E}f_{i - 1, v, k}(u \ne X)$

### C++ 代码

记录：[戳这里](https://atcoder.jp/contests/abc244/submissions/37958012)

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2010, M = 4010, mod = 998244353;

struct Edge {
    int to;
    int next;
}e[M];

int head[N], idx;

void add(int a, int b) {
    idx++;
    e[idx].to = b;
    e[idx].next = head[a];
    head[a] = idx;
}

int f[N][N][2];

int n, m, k, s, t, x;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> s >> t >> x;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    f[0][s][0] = 1;
    
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            for (int l = head[j]; l; l = e[l].next) {
                int to = e[l].to;
                for (int r = 0; r <= 1; r++) {
                    if (j == x) f[i][j][r] = (f[i][j][r] + f[i - 1][to][1 - r]) % mod;
                    else f[i][j][r] = (f[i][j][r] + f[i - 1][to][r]) % mod;
                }
            }
        }
    }
    cout << f[k][t][0] << '\n';
    return 0;
}
```

---

## 作者：appear_hope (赞：2)

考虑状态设计：

状态：$(i, u, op)$ 表示已选序列长度为 $i$，当前在点 $u$，已经走了点 $x$ 奇数次（$op = 1$）或偶数次（$op = 0$）

转移：$(i, u, op) \rightarrow (i + 1, v, (op + (v == x)) \mod 2)$，其中 $v$ 和 $u$ 之间有一条连边。

初始状态：$(0, s, 0)$。

目标状态：$(k, t, 0)$。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;
const int mod = 998244353;

vector<int> g[N];
int n, m, k, s, t, x, dp[N][N];

int main(){
	cin >> n >> m >> k >> s >> t >> x;
	for(int i = 1, u, v; i <= m; i++){
		cin >> u >> v;
		g[u].push_back(v), g[v].push_back(u);
	}
	dp[0][s][0] = 1;
	for(int i = 1; i <= k; i++){
		for(int j = 1; j <= n; j++){
			for(int v : g[j]){
				dp[i][j][0] = (dp[i][j][0] + dp[i - 1][v][v == x]) % mod;
				dp[i][j][1] = (dp[i][j][1] + dp[i - 1][v][(v == x ? 0 : 1)]) % mod;
			}
		}
	}
	cout << dp[k][t][0];
	return 0;
}
```

---

## 作者：cwxcplh (赞：1)

一道图上 DP 的好题。

（题目自己看，我就不说了。）

首先一看到求方案数，首先就要反应的是 DP 或者排列组合，反正考试的时候我写半天排列组合没写出来，所以就只能是 DP 了。~~（好牵强的理由啊……）~~

既然是 DP，那我们看看 DP 表示什么。自然是求啥设啥，那应该开几维呢？怎么写状态转移方程呢？

首先我们来解决第一个问题：我们看看题目中有几个不定量。不难发现，最主要的一共有三个：当前所在的点、总长度和经过 $X$ 的次数。所以 DP 一共就有三维。（正好开下数据范围。）

接着我们来写状态转移方程，其实我们把 DP 设出来之后就很好写状态转移方程了，具体如下：

$$\begin{cases} dp_{i,j,0}=dp_{i,j,0}+dp_{i-1,to,0},dp_{i,j,1}=dp_{i,j,1}+dp_{i-1,to,1}&j\not=t\\dp_{i,j,0}=dp_{i,j,0}+dp_{i-1,to,1},dp_{i,j,1}=dp_{i,j,1}+dp_{i-1,to,0}&j=t\end{cases}$$

其中 $to$ 表示从 $j$ 能到的点。

AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,m,k,s,t,x,dp[2006][2006][2];
vector<int>v[2006];
signed main()
{
    cin>>n>>m>>k>>s>>t>>x;
    for(int i=1,y,z;i<=m;i++)
    {
        cin>>y>>z;
        v[y].emplace_back(z);
        v[z].emplace_back(y);
    }
    dp[0][s][0]=1;
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=n;j++)
        {
            for(auto l:v[j])
            {
                if(j==x)
                {
                    dp[i][j][0]+=dp[i-1][l][1],dp[i][j][0]%=mod;
                    dp[i][j][1]+=dp[i-1][l][0],dp[i][j][1]%=mod;
                }
                else
                {
                    dp[i][j][0]+=dp[i-1][l][0],dp[i][j][0]%=mod;
                    dp[i][j][1]+=dp[i-1][l][1],dp[i][j][1]%=mod;
                }
            }
        }
    }
    cout<<dp[k][t][0]%mod;
    return 0;
}
```

---

## 作者：tsh_qwq (赞：1)

此题难处理之处就在**出现次数为偶数次**。  
经过长时间的思考后，我想到可以采用类似于状拆的思路，设计状态 $f_{i,j,k}$，表示从某点开始经过 $i$ 条边到节点 $j$，$k$ 为 $x$ 出现次数模 $2$ 的余数。  
可以得出动态转移方程：

#### 当 $(j=x)$ 时:

$dp_{i,j,1}=dp_{i,j,1}+dp_{i-1,u,0}$

$dp_{i,j,0}=dp_{i,j,0}+dp_{i-1,u,1}$

#### 当 $(j\not=x)$ 时:

$dp_{i,j,1}=dp_{i,j,1}+dp_{i-1,u,1}$

$dp_{i,j,0}=dp_{i,j,0}+dp_{i-1,u,0}$

至于建图方面就很简单了，记住是**无向图**就行了，~~尽管考试时忘了这一点调了好久~~。

给出代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,m,k,s,t,x,sum;
int f[2003][2003][10];
vector<int>e[10000];
void add(int u,int v)
{
	e[v].push_back(u); 
	e[u].push_back(v);
}
int main()
{
	cin>>n>>m>>k>>s>>t>>x;
	int a,b;
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		add(a,b);
	}
	f[0][s][0]=1;
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=0;k<e[j].size();k++)//遍历图 
			{
				int r=e[j][k];
				if(j==x)
				{
					f[i][j][0]+=f[i-1][r][1];
					f[i][j][1]+=f[i-1][r][0];
					f[i][j][0]%=mod;//mod
					f[i][j][1]%=mod;
				}
				else
				{
					f[i][j][0]+=f[i-1][r][0];
					f[i][j][1]+=f[i-1][r][1];
					f[i][j][0]%=mod;
					f[i][j][1]%=mod;
				}
			}
		}
	}
	cout<<f[k][t][0];
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/192603521)

---

## 作者：ghx0052 (赞：1)

# 思路

发现若相同的位置有 $3$ 个或 $0$ 个时为 Yes，否则为 No，下面给出简要说明。

为 $3$ 个的时候就把两个反复横跳即可，为 $0$ 个的话可以构造方案在操作两次后转化为 $3$ 个一样的情况。

否则相同的位置只可能有 $1$ 个，做任意一次交换后都会变成上面两种情况，所以寄了。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define pb(z,a,i) z[a].push_back(i)
#define fr(i,j,k) for(int i=j;i<=k;i++)
#define rp(i,j,k) for(int i=j;i>=k;i--)
using namespace std;
const int N=2e5+10;
signed main(){
	char a[3],b[3];
	fr(i,0,2)cin>>a[i];
	fr(i,0,2)cin>>b[i];
	int cnt=0;
	fr(i,0,2) if(a[i]!=b[i]) cnt++;
	if(cnt==0||cnt==3)cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
}
```


---

## 作者：IGpig (赞：0)

## abc244e
### Problem
给定整数 $K$，$S$，$T$，$X$。满足以下条件的序列 $A=(A_0,A_1,\dots, A_K)$ 有多少个？
- $A_i$ 是一个介于 $1$ 和 $N$ 之间的整数（包括两端）。
- $A_0=S$。
- $A_K=T$。
- 存在一条边直接连接顶点 $A_i$ 和顶点 $A_{i+1}$。
- 整数 $X$ 在序列 $A$ 中出现偶数次（可能为零）。

### Solution
考虑图上动态规划，可以很快发现有 $dp_{k,v,cnt}$ 表示走了 $k$ 步到了 $v$ 已经出现了 $x$ 次。\
但是这样的 $n^3$ 复杂度无法通过。我们发现最后一维是没有实际意义的，只需要看是否为偶数。所以有：
~~~cpp
    LL nk=k+1,nv=to,ni=i;
    if(to==x) ni^=1;
    dp[nk][nv][ni]+=dp[k][j][i];
~~~
答案为 $dp_{K,T,0}$。

### Code
~~~cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
const LL mod = 998244353;
LL dp[2005][2005][2],n,m,K,s,t,x;
vector<LL> g[2005];
int main(){
    cin>>n>>m>>K>>s>>t>>x;
	dp[0][s][0]=1;
    for(int u,v,i=1;i<=m;i++){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int k=0;k<K;k++)
		for(int j=1;j<=n;j++)
			for(int i=0;i<=1;i++) {
        	for (auto to : g[j]) {
            	LL nk=k+1,nv=to,ni=i;
            	if(to==x) ni^=1;
            	dp[nk][nv][ni]+=dp[k][j][i];//多一个，下一个位置，出现。
				dp[nk][nv][ni]%=mod;
        	}
    }
    cout<<dp[K][t][0];
    return 0;
}

~~~

---

## 作者：Grace2022 (赞：0)

这里提供一个记忆化搜索的方法。
## 题意
给定一个无向图，求经过边数为 $K$、起点为 $S$、终点为 $T$、经过偶数次节点 $X$ 的路径条数。  
## 赛时心路历程
由于在我理解错的情况下记得教练说过类似“dp 不能解决有环的问题”，我刻意避开了 dp 解法，从并查集想到汇点再想到奇偶性分类讨论，因为受数位 dp 中记忆化搜索的佘毒，最后决定暴搜再优化。 

当时竟然没想到这只是一道黄题 dp……
## 思路分析
按照题意用 dfs 模拟一遍，再对参数记忆化，大概长这样：
```cpp
int dfs(int s,int t,int k,int step,int flag,int cnt,int x){
	if(step==k){
		return (cnt%2==0)&&(flag==t);
	}
	if(dp[step][flag].find(cnt)!=dp[step][flag].end()) return dp[step][flag][cnt]%Mod;
	int ans=0;
	for(auto i:e[flag]){
		ans+=dfs(s,t,k,step+1,i,cnt+(i==x),x)%Mod;
		ans%=Mod;
	}
	return dp[step][flag][cnt]=ans%Mod;
}
```
$\mathcal{O}(K^2 \times N)$ 的复杂度铁超时了。于是我开启了漫长的剪枝优化的之旅……
### 优化 1：并查集判断起点终点是否连通
我们在最开始的时候，每输入一条边，就把这条边的起点和终点加入一个集合，在 dfs 前就判断存不存在路径，时间复杂度 $\mathcal{O}(\alpha(M))$。
### 优化 2：最短路判断是否有递归下去的必要
由于是无向图，$\text{dij}(u,v) = \text{dij}(v,u)$，所以我们可以通过求出从点 $T$ 到任意点的最短路，如果当前剩余步数小于最短路，就不再可能走到了，没有必要再走下去。  

即：```if(dis[flag]>k-step) return 0;```。
### 优化 3：参数 $cnt$ 只需用来判断奇偶性
当你做了前一个或两个的优化时，你就能得到 21 比 38 的 TLE 成绩，我在赛时的思考也止步于此了。然而实际上，对于参数 $cnt$，我们从头到尾只用到了它的奇偶性，也就是题目中说的：

> 整数 $X$ 在序列 $A$ 中出现偶数次（可能为零）。

我们只需要保留 $cnt$ 的奇偶性即可。  

优化到这里你就能发现，现在的代码已经和普通 dp 大差不差了，优化 1 和优化 2 似乎也没什么必要了。
## AC 代码
本人的代码不是简约风格，且赛时为了优化使尽浑身解数，所以代码量较大且略显冗长。如果读者自己写一遍就能发现，实际上的代码和普通 dp 差不多，而且不用动脑子（*~毕竟是无脑暴搜，虽然普通 dp 也不需要动脑子~*）。
``` cpp
#include<bits/stdc++.h>
using namespace std;
#define PII pair<int,int> 
const int Mod=998244353;
inline int read(){
	int st=1,s=0;
	char c=getchar();
	while(c<'0' || c>'9'){
		(c=='-') && (st=-1);
		c=getchar();
	}
	while(c>='0' && c<='9'){
		s=(s<<3)+(s<<1)+(c^48);
		c=getchar();
	}
	return (st==1?s:-s);
}
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+48);
}
vector<int> e[2005];
int pre[2005],vis[2005],dis[2005],dp[2005][2005][2];
int fi(int x){
	if(x==pre[x]) return x;
	else return pre[x]=fi(pre[x]);
}
inline void merge(int x,int y){
	int fx=fi(x),fy=fi(y);
	if(fx!=fy){
		pre[fx]=fy;
	}
}
inline void dij(int ss){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	priority_queue<PII,vector<PII>,greater<PII> > q;
	q.push(make_pair(dis[ss]=0,ss));
	while(!q.empty()){
		PII t=q.top();
		q.pop();
		if(vis[t.second]) continue;
		vis[t.second]=1;
		for(auto i:e[t.second]){
			if(t.first+1<dis[i]){
				dis[i]=t.first+1;
				q.push(make_pair(dis[i],i)); 
			}
		} 
	}
}
int dfs(int s,int t,int k,int step,int flag,int cnt,int x){
	if(step==k){
		return cnt&&(flag==t);
	}
	if(dp[step][flag][cnt]%2!=-1) return dp[step][flag][cnt%2]%Mod;
	if(dis[flag]>k-step){
		//cout<<flag<<' '<<dis[flag]<<' '<<step<<endl;
		return 0;
	}
	int ans=0;
	for(auto i:e[flag]){
		ans+=dfs(s,t,k,step+1,i,(cnt+(i==x))%2,x)%Mod;
		ans%=Mod;
	}
	dp[step][flag][cnt%2]=ans%Mod;
	return dp[step][flag][cnt%2];
}
int main(){
	memset(dp,-1,sizeof(dp)); 
	int n=read(),m=read(),k=read(),s=read(),t=read(),x=read();
	for(int i=1;i<=n;++i){
		pre[i]=i;
	}
	for(int i=1;i<=m;++i){
		int u=read(),v=read();
		e[u].emplace_back(v);
		e[v].emplace_back(u);
		merge(u,v);
	}
	if(fi(s)!=fi(t)){
		cout<<0;
		return 0;
	}
	dij(t);
	cout<<dfs(s,t,k,0,s,1,x);
	return 0;
}
```

---

## 作者：z_yq (赞：0)

# 题意
给出一个图，求出有多少个数列满足条件。\
题面很清晰了，无法简化了，直接去看思路。
# 思路
计数问题，一眼就是 DP，于是我们设计状态。\
发现我们要判定 $X$ 是否出现了偶数次，我们找到数列的第几位来了，当前这一位是多少，所以状态就是 $dp_{i,j,0/1}$ 表示枚举到了 $i$ 这一位，而且当前是 $j$，满足 $X$ 是否出现了偶数次，最后的答案就是 $dp_{n,T,1}$。\
思考转移式，我们可以枚举上一个的点，设为 $k$，那么如果 $k,j$ 直接有边，那么 $dp_{i,j,0/1} = dp_{i,j,0/1} + dp_{i-1,k,0/1}$ 其中需要判定 $j,k$ 都是否为 $X$。\
然后这样的转移是会超时的，因为是三次方的复杂度，发现转移中还需要判定是否有边，那么不如直接枚举边，这样就是 $n^2$ 的复杂度了，可过。\
注意：需要取模，而且初始化也需要考虑考虑。
# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define Inf 0x7f7f7f7f
#define Mod 998244353
#define P pair<ll,ll>
#define fi first
#define se second
using namespace std;
const int N=2e3+9;
int n,m,len,s,t,num;
P book[N];
ll dp[N][N][2];
int main()
{
	cin>>n>>m>>len>>s>>t>>num;
	for(int i=1,x,y;i<=m;i++)
		cin>>book[i].fi>>book[i].se;
	if(s==num)dp[0][s][0]=1;
	else dp[0][s][1]=1;
	for(int i=1;i<=len;i++)
		for(int num1=1;num1<=m;num1++)
		{
			int j=book[num1].fi,k=book[num1].se;
			if(k==num)
				dp[i][k][0]+=dp[i-1][j][1],
				dp[i][k][1]+=dp[i-1][j][0];
			else
				dp[i][k][0]+=dp[i-1][j][0],
				dp[i][k][1]+=dp[i-1][j][1];
			dp[i][k][0]%=Mod;
			dp[i][k][1]%=Mod;
			swap(j,k);
			if(k==num)
				dp[i][k][0]+=dp[i-1][j][1],
				dp[i][k][1]+=dp[i-1][j][0];
			else
				dp[i][k][0]+=dp[i-1][j][0],
				dp[i][k][1]+=dp[i-1][j][1];
			dp[i][k][0]%=Mod;
			dp[i][k][1]%=Mod;
		}
	cout<<dp[len][t][1];
	return 0;
}
/*
dp[i][j][0/1]:考虑到Ai，结尾为j，出现是否为偶数次
*/
```
# 后言
题目简单，一遍过，如果有不详细或者错误，请指出，谢谢。

---

## 作者：_qingshu_ (赞：0)

感觉上位黄？有点难想。

# 思路：

看到方案数~~与答案可能很大~~，想到动态规划，首先考虑状态：

我们定义 $f_{i,j,k}$ 来表示数列中第 $j$ 个位置填 $i$ 且路径上 $X$ 的个数 $Xn\bmod 2=k$ 的方案数。

考虑转移方式，直接循环转移我太彩了推不出来qwq，所以考虑类似 bfs 的逐位递推写法，每一次记录下一位可以填的数，再分类讨论转移。这个写法的可行性在于 $1\le M \le 2000$，因为我们转移目标一定是一条边的一端也就是说我们每一次转移最多考虑 $2\times M$ 次，再加上遍历位置，时间复杂度为 $\mathcal{O}(kM)$。

转移方程非常好推，设当前点为 $x$，遍历点为 $v$，位置为 $now$：

- 若 $v=X$：

$$f_{v,now+1,1}=f_{v,now+1,1}+f_{x,now,0}$$
$$f_{v,now+1,0}=f_{v,now+1,0}+f_{x,now,1}$$

- 若 $v\neq X$：

$$f_{v,now+1,1}=f_{v,now+1,1}+f_{x,now,1}$$
$$f_{v,now+1,0}=f_{v,now+1,0}+f_{x,now,0}$$

不要忘记取模和我们是从 $0$ 开始递推的。


# Code：

```cpp
#include<bits/stdc++.h>
#define Mark using
#define _ namespace
#define liang std;
Mark _ liang
#define mod 998244353
int n,m,k,s,t,x;
vector<int>e[5200010];
long long f[2001][2001][2];//在序列中第 j 个位置为 i 且 x 出现次数为奇/偶的次数
set<int>q,qq;
inline void bfs(int whe){
    if(whe==k)return;
    for(int d : q){
        for(int v : e[d]){
            qq.insert(v);
            f[v][whe+1][1]+=f[d][whe][1^(v==x)];
            f[v][whe+1][1]%=mod;
            f[v][whe+1][0]+=f[d][whe][0^(v==x)];
            f[v][whe+1][0]%=mod;
            // cout<<d<<" "<<v<<endl;
            // cout<<v<<" "<<whe+1<<" "<<1<<" : "<<f[v][whe+1][1]<<" / "<<0<<" : "<<f[v][whe+1][0]<<endl;
        }
    }
    q=qq;
    qq.clear();
    bfs(whe+1);
}
int main(){
    cin>>n>>m>>k>>s>>t>>x;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    f[s][0][s==x]=1;
    q.insert(s);
    bfs(0);
    cout<<f[t][k][0]%mod<<endl;
}
```

update：

- 修改了标点符号。

---

## 作者：Mingrui_Yang (赞：0)

[luogu 传送门](https://www.luogu.com.cn/problem/AT_abc244_e)

## 题意

有一张无向图，求从 $S$ 到 $T$ 经过 $K$ 条边且经过 $X$ 号点偶数次的方案数，答案对 $998244353$ 取模。

## 思路

考虑 DP。

令 $f_{i, j, k}$ 表示状态为经过 $i$ 条边，目前在 $j$ 号点，经过 $X$ 号点的次数的奇偶性的方案数。

考虑 $f_{i, u, k}$ 的状态转移。   
点 $u$ 一定是由它的邻接点转移而来。       
如果 $u = X$，则经过 $X$ 号点的奇偶性将发生改变。   
否则奇偶性不会发生改变。

状态转移方程如下：

$$
\begin{cases}
  f_{i, u, k} = {\textstyle \sum_{\{u, v \} \in E}^{}} f_{i - 1, v, k} & \text{ if } u \neq X \\
  f_{i, u, k} = {\textstyle \sum_{\{u, v \} \in E}^{}} f_{i - 1, v, 1 - k} & \text{ if } u = X \\
\end{cases}
$$
$E$ 为边集，$1 - k$ 表示扭转奇偶性。

初始状态为 $f_{0, S, 0} = 1$。

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long 
#define ADD(x, y) (((x) += (y)) %= Mod)
using namespace std;
const int N = 2010;
const int Mod = 998244353;
int n, m, k, s, t, x;
int h[N], ne[N << 1], e[N << 1], idx; // 邻接表，无向图，开双倍 
int f[N][N][2];
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ; }
signed main() {
	memset(h, -1, sizeof h);
	cin >> n >> m >> k >> s >> t >> x;
	for (int i = 0; i < m; i ++ ) {
		int u, v;
		cin >> u >> v;
		add(u, v), add(v, u);
	}
	f[0][s][0] = 1;
	for (int i = 1; i <= k; i ++ )
		for (int j = 1; j <= n; j ++ ) 
			for (int k = 0; k < 2; k ++ ) 
				for (int l = h[j]; ~l; l = ne[l])
					if (j == x) ADD(f[i][j][k], f[i - 1][e[l]][1 - k]);
					else ADD(f[i][j][k], f[i - 1][e[l]][k]);
	cout << f[k][t][0] << endl;
	return 0;
}
```

---

## 作者：highkj (赞：0)

# 思路
一眼 Dp，我们首先定义 $f_{i,j,0/1}$ 代表现在填到了第 $i$ 个且第 $i$ 个为 $j$ 并且 $x$ 的出现次数为奇数或偶数的方案数，最后答案即为 $f_{k+1,t,0}$。然后我们就可以来想转移了，我们可以从一个点转移到他能到达的点所以我们可以先分类讨论一下。

- $f_{i+1,to,0}=f_{i+1,to,0}+f_{i,j,(0+to=x)\mod 2}$。
- $f_{i+1,to,1}=f_{i+1,to,1}+f_{i,j,(1+to=x)\mod 2}$。

这里主要是看它能到的点是否是 $x$ 因为若是的话就要进位，最后输出答案即可。
# 代码
这里为了能更好地理解，我吧是否等于 $x$ 的情况拆开来算了。
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n,m,s,t,x;
const int N=2e3+10;
vector<int>v[N];
int f[N][N][2];//现在是确定了i个第i个填j，x的出现次数为偶数或奇数
int vis[N],k;
const int mod=998244353;
fire main() {
	cin>>n>>m>>k>>s>>t>>x;
	rep(i,1,m) {
		int a,b;
		cin>>a>>b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	f[1][s][0]=1;
	rep(i,2,k+1) {
		rep(j,1,n) {
			for(auto y:v[j]) {
				if(y==x) (f[i][y][1]+=f[i-1][j][0])%=mod,(f[i][y][0]+=f[i-1][j][1])%=mod;//分类讨论
				else (f[i][y][1]+=f[i-1][j][1])%=mod,(f[i][y][0]+=f[i-1][j][0])%=mod;
			}
		}
	}
	cout<<f[k+1][t][0]<<endl;//输出
	return 0;
}
```

---

## 作者：Rosent (赞：0)

[Link](https://www.luogu.com.cn/problem/AT_abc244_e)

[at 原题link](https://atcoder.jp/contests/abc244/tasks/abc244_e)

~~这题建议升绿~~

题意简述：

一个 $n$ 个点 $m$ 条边的有向图，要求求出点 $s$ 和点 $t$ 经过点 $x$ 偶数次的路径总数。

观察数据范围 $2 \le n \le 2000$ 不难发现可以使用图上 dp 算法。

设 dp 数组 $f_{i,j,k}$ 表示走了 $i$ 步，到达 $j$ 点，经过点 $x$ 次数的奇偶。

dp 转移方程如下：

设 $to$ 表示 $j$ 点的所有出边。

若 $j \ne x$，则 $f_{i,j,k}=f_{i,j,k}+f_{i-1,to,k}$

若 $j=x$，则 $f_{i,j,k}=f_{i,j,k}+f_{i-1,to,k \operatorname{xor} 1}$

特别的，$f_{0,s,0}=1$

PS：不开long long 见祖宗。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mod 998244353
#define maxn 2010
using namespace std;
int n,m,k,s,t,x,cnt=0;
int first[maxn],f[maxn][maxn][3];
struct ed
{
	int next,to;
}edge[maxn*2];
void add(int u,int v)
{
	edge[++cnt].next=first[u];
	edge[cnt].to=v;
	first[u]=cnt;
}
signed main()
{
	cin>>n>>m>>k>>s>>t>>x;
	int a,b;
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	f[0][s][0]=1;
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int l=first[j];l;l=edge[l].next)
			{
				int r=edge[l].to;//上一个点 
				if(j==x)//该点为偶数点而非r
				{
					f[i][j][0]=(f[i][j][0]+f[i-1][r][1])%mod;
					f[i][j][1]=(f[i][j][1]+f[i-1][r][0])%mod;
				}
				else
				{
					f[i][j][0]=(f[i][j][0]+f[i-1][r][0])%mod;
					f[i][j][1]=(f[i][j][1]+f[i-1][r][1])%mod;
				}
				
			}
		}
	}
	cout<<f[k][t][0];
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

出现次数是偶数这个条件不好处理，想办法转化。

不难发现可以直接把这个出现次数写进状态里，于是设计 dp 状态 $ dp_{i,j,x} $，表示从 $ S $ 开始到节点 $ j $ 经过 $ i $ 条边，$ x $ 的出现次数模 $ 2 $ 的余数。

于是不难发现可以枚举当前点的邻接点 $ u $，则不难有：

` dp[i][j][x]=dp[i][j][x]+dp[i+1][u][x^1] (u==x),dp[i][j][x]=dp[i][j][x]+dp[i+1][u][x](u!=x) `

最后答案为 $ dp_{k+1,T,0} $。因为需要转移 $ i $ 次，每次转移都要枚举所有边，所以总时间复杂度 $ \mathcal{O}(km) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int N = 2e3+10,M = N * 2,INF = 0x3f3f3f3f,mod = 998244353;
int dp[N][N][2];
int h[N],e[M],ne[M],idx;
void add(int a,int b)
{
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
int main()
{
    memset(h,-1,sizeof h);
    int n,m,k,S,T,x;
    cin>>n>>m>>k>>S>>T>>x;
    while(m--)
    {
        int a,b;
        cin>>a>>b;
        add(a,b),add(b,a);
    }
    dp[1][S][0] = 1;
    for(int i = 2 ; i <= k + 1 ; i++)
        for(int j = 1 ; j <= n ; j++)
            if(dp[i-1][j][0]||dp[i-1][j][1])
                for(int o = h[j] ; ~o ; o = ne[o])
                {
                    int u = e[o];
                    if(u==x)
                    {
                        dp[i][u][0] = (dp[i][u][0] + dp[i-1][j][1]) % mod;
                        dp[i][u][1] = (dp[i][u][1] + dp[i-1][j][0]) % mod;
                    }
                    else
                    {
                        dp[i][u][0] = (dp[i][u][0] + dp[i-1][j][0]) % mod;
                        dp[i][u][1] = (dp[i][u][1] + dp[i-1][j][1]) % mod;
                    }
                }
    cout<<dp[k+1][T][0];
}
```


---

