# Turtles

## 题目描述

一张$n$行$m$列的网格图，图中的有些格子上面有障碍物，但保证$(1,1)$和$(n,m)$上面都没有障碍物。在$(1,1)$处有两只乌龟，都想要去$(n,m)$。乌龟每次都可以向下或者向右走一格，前提是格子上没有任何障碍物。要求两只乌龟在前往$(n,m)$的路途中不可以相遇，即除了起点和终点，他们的路径没有其他公共点。求出从起点到终点的不同路径对数。答案对$10^9+7$取模。

注：$(route_a,route_b)$和$(route_b,route_a)$被视为同一对路径。

## 样例 #1

### 输入

```
4 5
.....
.###.
.###.
.....
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3
...
...
```

### 输出

```
1
```

# 题解

## 作者：pigstd (赞：19)

同步更新于 [题目总结](https://www.luogu.com.cn/blog/pigstd/ti-mu-zong-jie)。

[CF348D Turtles](https://www.luogu.com.cn/problem/CF348D) 容斥 dp，经典题。

首先考虑只有一只乌龟的时候怎么做，

这就是一个经典的 dp 问题，设 $f_{i,j}$ 表示点 $(1,1)$ 到 $(i,j)$ 的方案数，$a_{i,j}$ 表示 $(i,j)$ 是否可走，那么有不难有：

$f_{i,j}=\begin{cases} 0\ (a_{i,j}=0) \\ f_{i,j}+f_{i-1,j}+f_{i,j-1}\  (a_{i,j}=1)\end{cases}$。

然而题目让我们求的是两条不相交的路径，这个怎么求呢？

我们不难注意到，不相交的路径必然是一条 $(1,2) \to (n-1,m)$ 的路径和一条 $(2,1) \to (n,m-1)$ 的路径，而一条 $(1,2) \to (n,m-1)$ 和一条 $(2,1) \to (n-1,m)$ 必然是相交的。那么我们因为我们能求助所有 $(1,2) \to (n-1,m)$ 的路径和 $(2,1) \to (n,m-1)$ 的路径，那么我们只要减去满足上述条件，并且相交的路径总数就可以了。

对于两条有交点的路径，不妨在最后一个交点处，交换剩下的两个路径。那么这就转换成了一条 $(1,2) \to (n,m-1)$ 和一条 $(2,1) \to (n-1,m)$ 的路径。并且不难发现，这些路径是一一对应的。所以相交的路径总数就是一条 $(1,2) \to (n,m-1)$ 和一条 $(2,1) \to (n-1,m)$ 的路径总数。

画几幅图可能更容易理解：如果原来的两条相交的路径是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/lbaow946.png)

其中黄线和绿线分别表示两条路径，红圈表示最后一个交点处。那么可以讲此图转换成：

![](https://cdn.luogu.com.cn/upload/image_hosting/grft41s6.png)

这样就是满足第二个条件的路径了。同理，每个满足第二个条件的两条路径也能够转化回来。

然后就转换成上述的经典问题了。设 $F(x1,y1,x2,y2)$ 表示 $(x1,y1) \to (x2,y2)$ 的路径总数，那么有 $ans=F(1,2,n-1,m)\times F(2,1,n,m-1)-F(1,2,n,m-1)\times F(2,1,n-1,m)$。时间复杂度 $O(n^2)$。

（吐槽：用 `string` 和 `cin` 读入字符串会被卡常）。

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

const int Mod=1e9+7;
const int M=3010;
int f[M][M][4],n,m;
bool a[M][M];

int F(int x1,int y1,int x2,int y2,int tt)
{
//	for (int i=1;i<=n;i++)for (int j=1;j<=m;j++)f[i][j]=0;
	f[x1][y1][tt]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (a[i][j]==0)f[i][j][tt]=0;
			else f[i][j][tt]=((f[i][j][tt]+f[i-1][j][tt])%Mod+f[i][j-1][tt])%Mod;
	return f[x2][y2][tt];
}

char s[M];

signed main()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			a[i][j]=(getchar()=='#'?0:1);
		getchar();
	}
	long long ans=1ll*F(1,2,n-1,m,0)*F(2,1,n,m-1,1)-1ll*F(1,2,n,m-1,2)*F(2,1,n-1,m,3);
	ans%=Mod,ans+=Mod,ans%=Mod;cout<<ans<<endl;
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：8)

考虑 LGV 引理的定义：对于 $n$ 个源点以及 $m$ 个终点进行相应匹配，得到不交路径方案数之和。            

那么对于这道题只要转化一下就好了，由于起点与终点也不能相交，所以我们把源点 $(1,1)$ 变为 $(1 , 2) , (2 , 1)$，终点 $(n,m)$ 变为 $(n - 1,m) , (n , m - 1)$。               

显然如果让 $(2,1)$ 和 $(n - 1,m)$ 匹配必然会让所有路径方案数都产生交，所以让 $(1,2)$ 匹配 $(n - 1 , m)$，$(2 , 1)$ 匹配 $(n , m - 1)$ 即可，用 dp 跑出系数矩阵然后直接上 LGV 的板子即可。            

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 3e3 + 5 , MOD = 1e9 + 7;
int n,m,mp[Len][Len],SonA[2],SonB[2],dp[Len][Len];
char s[Len];
void Work(int c)
{
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 1 ; j <= m ; j ++) 
		{
			if(!mp[i][j])
			{
				dp[i][j] = 0;
				continue;
			}
			if(i - 1 >= 1) dp[i][j] += dp[i - 1][j];
			if(j - 1 >= 1) dp[i][j] += dp[i][j - 1];
			dp[i][j] %= MOD;
		}
	}
	SonA[c] = dp[n - 1][m];
	SonB[c] = dp[n][m - 1];
}
long long Iabs(long long x){return x > 0 ? x : -x;}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%s",s + 1);
		for(int j = 1 ; j <= m ; j ++) mp[i][j] = (s[j] == '.');
	}
	memset(dp , 0 , sizeof dp);
	dp[1][2] = 1;
	Work(0);
	memset(dp , 0 , sizeof dp);
	dp[2][1] = 1;
	Work(1);
	printf("%lld\n",((1ll * SonA[0] * SonB[1] % MOD - 1ll * SonB[0] * SonA[1] % MOD) + MOD) % MOD);
	return 0;
}
```

---

## 作者：MYJ_aiie (赞：3)

### [CF348D Turtles](https://www.luogu.com.cn/problem/CF348D)
**题意**：$n\times m$ 网格图，图中有些格子上有障碍物，两只乌龟从 $(1,1)$ 走到 $(n,m)$，可以向下或向右，求两只乌龟不交路径对数，答案对 $1e9+7$ 取模。$n,m\leq3000$。  
**思路**：一只乌龟的很简单，设 $f_{i,j}$ 表示走到 $(i,j)$ 的路径数，那么当 $a_{i,j}$ 为可走时， $f_{i,j}=(f_{i,j}+f_{i-1,j}+f_{i,j-1})$。  
怎么判断不交呢？我们可以先看有哪些是一定相交的。首先，两只乌龟一定分别经过 $(1,2)$ 和 $(n-1,m)$，$(2,1)$ 和 $(n,m-1)$。若两条路径同时走了 $(1,2)$ 和 $(n,m-1)$，$(2,1)$ 和 $(n-1,m)$，那就是有交。  
**code**:
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=3002;
const int mod=1e9+7;
ll f[N][N];
int a[N][N];
int n,m;
ll a1,a2,a3,a4;
ll solve(int bx,int by,int ex,int ey){
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++) f[i][j]=0;
	}
	f[bx][by]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==0) f[i][j]=0;
			else f[i][j]=((f[i][j]+f[i-1][j])%mod+f[i][j-1])%mod;
		}
	}
	return f[ex][ey];
}
int main(){
	char s;
	scanf("%d%d",&n,&m);
	s=getchar();
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			s=getchar();
			if(s=='.') a[i][j+1]=1;
			else a[i][j+1]=0;
		}
		s=getchar();
	}
	a1=solve(1,2,n-1,m);
	a2=solve(2,1,n,m-1);
	a3=solve(1,2,n,m-1);
	a4=solve(2,1,n-1,m);
	printf("%lld\n",((a1*a2%mod-a3*a4%mod)%mod+mod)%mod);
	return 0;
}
```

**提示**：
1. cin被卡的时候可以换成getchar，注意输入换行。
2. lgv引理。对于路径不相交问题，试着对它们的起点终点进行匹配。

---

## 作者：potatoler (赞：2)

由于两条路径在中间不相交，我们可以把题意变为：在有坏点的，n*m 的网格图上，从 (2, 1) 到 (n-1, m) 的路径与从 (1, 2) 到 (n, m-1) 的路径有多少种情况不相交。很容易可以递推求网格图上两点之间路径条数，现在我们将路径抽象成一根线，考虑下面的情况：

![](https://i.loli.net/2020/07/16/eFU7HdOcPrQM9Ni.png)

也就是说最终的答案就是用集合1方案数减去集合2方案数。还可以根据[LGV引理](https://oi-wiki.org/graph/lgv/)转化为一个 2*2 的行列式进行计算，列出来的式子是一样的。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long 
using namespace std;
const int MaxN = 3005, Mod = 1e9+7;
int n, m, ans, f[MaxN][MaxN];
char map[MaxN][MaxN];

inline int numberofWays(int x1, int y1, int x2, int y2){
	memset(f, 0, sizeof(f));
	for(int i = x1; i <= x2; i++)
		for(int j = y1; j <= y2; j++){
			if(map[i][j] == '.'){
				if(i == x1 && j == y1) f[i][j] = 1;
				else f[i][j] = (f[i-1][j] + f[i][j-1]) % Mod;
			}
		}
	return f[x2][y2] % Mod;
}

signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i=1;i<=n;i++)
		scanf("%s", map[i] + 1);
	ans = ((numberofWays(1, 2, n-1, m) * numberofWays(2, 1, n, m-1) % Mod) - (numberofWays(1, 2, n, m-1) * numberofWays(2, 1, n-1, m) % Mod) + Mod) % Mod;
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：yanmingqian (赞：1)

考虑怎么求从一个点到另一个点的方案数。这不就是我们的 [Grid 1](https://www.luogu.com.cn/problem/AT_dp_h) 吗！把代码稍微一改，可以得到下面一个函数：

```cpp
long long f[3010][3010];
long long g(int sx,int sy,int ex,int ey){
    memset(f,0,sizeof f);
    f[sx][sy-1]=(a[sx][sy]=='.');
    for(int i=sx;i<=ex;i++){
        for(int j=sy;j<=ey;j++){
            if(a[i][j]=='.'){
                f[i][j]=(f[i-1][j]+f[i][j-1])%mod;
            }
        }
    }
    return f[ex][ey];
}
```

这份代码可以求解从 $(sx,sy)$ 到 $(ex,ey)$ 的方案数。

考虑这题怎么做。显然，要想让路径没有交，两条路径必然一条是从 $(1,2)$ 到 $(n-1,m)$，另一条是从 $(2,1)$ 到 $(n,m-1)$。乘法原理可得，这样的路径对数就是这两种路径数的乘积。

容斥一下，刚刚求出了总方案数，考虑不合法的方案数是多少。我们将不合法的路径对从最后一个交点处交换，这样不合法的路径就变成了从 $(1,2)$ 到 $(n,m-1)$ 和从 $(2,1)$ 到 $(n-1,m)$。显然每一条不合法路径都可以转换为这样，因此和上面总方案数类似地可以求出不合法方案数，也就是从 $(1,2)$ 到 $(n,m-1)$ 和从 $(2,1)$ 到 $(n-1,m)$ 两种路径的乘积。用总方案减掉不合法方案数就是答案。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const long long mod=1e9+7;
char a[3010][3010];
long long f[3010][3010];
long long g(int sx,int sy,int ex,int ey){
    memset(f,0,sizeof f);
    f[sx][sy-1]=(a[sx][sy]=='.');
    for(int i=sx;i<=ex;i++){
        for(int j=sy;j<=ey;j++){
            if(a[i][j]=='.'){
                f[i][j]=(f[i-1][j]+f[i][j-1])%mod;
            }
        }
    }
    return f[ex][ey];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    cout<<((g(1,2,n-1,m)*g(2,1,n,m-1)%mod-g(1,2,n,m-1)*g(2,1,n-1,m)%mod)%mod+mod)%mod;
    return 0;
}
```

---

## 作者：ChickyHas (赞：1)

好久没写题解了，反正之前的都没过审。

题意挺简单，就不多赘述了。

求出从一个点到另一个点的方案就是 dp，那么要求两个不相交的怎么办呢？

首先我们发现两只乌龟一开始肯定是往两边走的，然后回来的时候一定是从终点。

我们钦定一只乌龟从起点下侧走到终点左侧，另一只乌龟从起点右侧走到终点上侧。

在这个情况下我们仍然考虑删除路径的交。

像是做卡特兰数那个翻转一样，我们考虑在两者的第一个交点交换两条路径，那么就直接一一对应了，就可以求出路径的交了。

然后就做完了，复杂度 $O(nm)$。

---

## 作者：Emplace (赞：1)

# 思路
  这道题目是一道容斥原理的题目，也就是 LGV 引领。
  
  LGV 引领：对多个起点与多个重点进行匹配，求不相交路劲的数量之和。

  而由于题目中说两只乌龟在路程中不能相遇，那我们可以理解为有两终点和两起点，分别是起点 $ (1,2) $，$ (2,1) $。与终点 $ (n,m-1) $，$ (n-1,m) $。

  而如果我们把 $ (1,2) $ 和 $ (n-1,m) $ 配对。那么这条路与 $ (2,1) $ 和 $ (n,m-1) $ 一定会相交。
  
  所以我们因该把 $ (1,2) $ 和 $ (n,m-1) $ 配对。把 $ (2,1) $ 和 $ (n-1,m) $ 配对。

  然后我们在两只乌龟相交后让它们交换路径，最后将两种方案的乘积相减就是答案了。

  ~~接下来就是正片了~~

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a[3001][3001],dp[3001][3001],mod=1000000007,a11,a12,a21,a22,t,t1,t2;
void js(int x1,int y1,int x2,int y2){
//	cout<<endl<<1145141919810<<endl;
	memset(dp,0,sizeof(dp));
	if(a[x1][y1]==1||a[x2][y2]==1){
		return ;
	}
	dp[x1][y1]=1;
	for(int i=1;i<=x2;i++){
		for(int j=1;j<=y2;j++){
			if(a[i][j]==1){
				continue;
			}
			dp[i][j]+=(dp[i-1][j]+dp[i][j-1]+mod)%mod;
			dp[i][j]%=mod;
		}
	}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;
			cin>>c;
			if(c=='.'){
				a[i][j]=0;
			}
			else if(c=='#'){
				a[i][j]=1;
			}
		} 
	} 
	js(1,2,n-1,m);
	a11=dp[n-1][m];
  	js(1,2,n,m-1);
  	a12=dp[n][m-1];
  	js(2,1,n-1,m);
  	a21=dp[n-1][m];
   	js(2,1,n,m-1);                    
   	a22=dp[n][m-1];
   	t=(a11*a22+mod)%mod;
   	t1=(a12*a21+mod)%mod;
   	t2=(t-t1+mod)%mod;
   	cout<<t2;
	return 0;
}

```

---

## 作者：violin_wyl (赞：1)

## CodeForces348D


### 解析：

#### 题目大意：

给你一张 $ n \times m$ 的图，让你选择两条从 $(1,1)$ 到 $(n,m)$ 的路径 $(1 \leq n \leq 3000)$ ，使得这两条路径不相交


------------

#### 思路：

当看到数据范围是 $n \leq 3000$ ，很明显的 $O(n^2)$ 吧（~~把输入码出来就差不多了~~），直接dp肯定是不行的，我们先考虑 $O(n^2)$ 我们能够求出什么，如果题目没有限制两条路径不能相交，那就是一个 $O(n^2)$ 的路径数量问题，令 $dp_{i,j}$ 代表从 $(1,1)$ 到达 $(i,j)$ 的不同路径数量，那么可得：
$$
dp_{i,j} = \begin{cases}
0 (a_{i,j}=0)\\
dp_{i-1,j}+dp_{i,j-1}(a_{i,j}=1)
\end{cases}
$$


会求路径数量后，我们在考虑两条路径不能相交这个限制条件。


很明显，选择两条从 $(1,1)$ 到 $(n,m)$ 的不相交的路径的充分条件是一条路径选择 $(1,2)$ 到 $(n-1,m)$ ，而第二条则选择 $(2,1)$ 到 $(n,m-1)$ （我们称为情况一），如图：

![图1](https://cdn.luogu.com.cn/upload/image_hosting/eu1s6714.png)

而显然选择 $(1,2)$ 到 $(n,m-1)$ 和 $(1,2)$ 到 $(n-1,m)$ （我们称为情况二），必定会有至少 1 个交点，如图：

![图2](https://cdn.luogu.com.cn/upload/image_hosting/vbfr20ta.png)

但是我们发现，情况一中的路径仍然会有个别情况会相交，如图

![图3](https://cdn.luogu.com.cn/upload/image_hosting/zag649aj.png)

那我们怎么删掉这种情况呢？其实只要减到情况二就行了。

不难发现，对于每一种 $(1,2)$ 到 $(n,m-1)$ 和 $(1,2)$ 到 $(n-1,m)$ 的路径，如果把他们第一次相交的点称作 $(x,y)$ ，那么将两条路径在 $(x,y)$ 后面的部分交换，通俗的说，我们让两只乌龟在相遇后交换他们的行进路线，则这种情况必定是情况一中的一种会相交的路线，于是我们得到了结论，即情况一中相交的路线必定与情况二一一对应，如图：

![图4](https://cdn.luogu.com.cn/upload/image_hosting/463v3hin.png)

这里只考虑了相交一次的个数，而相交 $k$ 次的以此类推即可。

综上：设 $f(sx,sy,tx,ty)$ 表示 $(sx,sy) \to (tx,ty)$ 的路径数量，那么答案就是情况一减去情况二的数量（至于情况二不一定是情况一的子集，所以最后减出来可能是负数……注意取余）

即 $(f(1, 2, n - 1, m)\times f(2, 1, n, m - 1)) - (f(1, 2, n, m - 1) \times f(2, 1, n - 1, m))$

最后膜一波kewth大佬


------------



### code：


```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e3 + 10;
const int mods = 1e9 + 7;
inline int read ( )
{
	int x = 0, f = 1;
	char ch = getchar ( );
	while (ch < '0' || ch > '9') {if (ch == '-') f = - 1; ch = getchar ( );}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
	return x * f;
}
int n, m;
int a[N][N];
int dp[N][N];
int f(int sx, int sy, int tx, int ty)
{
	memset (dp, 0, sizeof(dp));
	dp[sx][sy] = 1;
	for (int i = sx; i <= tx; i++)
		for (int j = sy; j <= ty; j++)
			dp[i][j] += (a[i][j] ? (dp[i - 1][j] +  dp[i][j - 1]) % mods : 0);
	return dp[tx][ty];
}
signed main ( )
{
	n = read ( ), m = read ( );
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
        {
            char ch = getchar ();
            a[i][j] = (ch == '.' ? 1 : 0);
        }
        getchar ();
	}
	if (!a[1][2] || !a[2][1] || !a[n][m - 1] || !a[n - 1][m]) {printf("0\n"); return 0;}//注意特判
	printf("%lld\n", ((f(1, 2, n - 1, m) * f(2, 1, n, m - 1)) % mods - (f(1, 2, n, m - 1) * f(2, 1, n - 1, m)) % mods + mods) % mods);//减法可能有负数
    return 0;
} //The Dark Emperor
```





---

## 作者：Purslane (赞：0)

# Solution

首先，我们可以很简单的求出单点到单点的方案数。但是如果通过这个求出合法的两条不相交的方案的总数呢？

低情商：LGV 引理。

高情商：容斥原理。

很显然，问题转化为两只小海龟，分别从 $(1,2)$ 和 $(2,1)$ 出发，到达 $(n,m-1)$ 和 $(n-1,m)$。想要不相交，必定是 $(1,2)$ 到 $(n-1,m)$，$(2,1)$ 到 $(n,m-1)$。我们可以把两种情况不考虑其他条件的方案数乘在一起，但也可能有交。那么考虑把这些交给删掉。

考虑在两个小海龟第一次相遇之后，两个人交换路径：这样实际上是把相交的方案一一映射到 $(1,2)$ 到 $(n,m-1)$ 且 $(2,1)$ 到 $(n-1,m)$ 的两条必定相交的路径上。减去两种方案的乘积即可。

这种方法可以给大家提供理解 LGV 引理的最简单形式，而真正的 LGV 引理只需要引入行列式即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10,MOD=1e9+7;
int n,m,flg[MAXN][MAXN],dp[MAXN][MAXN];
int solve(int sx,int sy,int tx,int ty) {
	memset(dp,0,sizeof(dp));
	if(flg[sx][sy]||flg[tx][ty]) return 0;
	dp[sx][sy]=1;
	ffor(i,1,n) ffor(j,1,m) {
		dp[i][j]+=dp[i-1][j]+dp[i][j-1];
		dp[i][j]%=MOD;
		if(flg[i][j]) dp[i][j]=0;
	}
	return dp[tx][ty];
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) {
		string S; cin>>S;
		ffor(j,1,m) if(S[j-1]=='#') flg[i][j]=1;
	}
	cout<<((solve(1,2,n-1,m)*solve(2,1,n,m-1)%MOD-solve(1,2,n,m-1)*solve(2,1,n-1,m)%MOD)%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：Vidoliga (赞：0)

这题是道 $LGV$ 引理板子题。

我们考虑将起点，终点分别分成两个，使问题等价、简洁。

我们不难发现对于第一部操作，一定是走到 $(1,2)$ 或 $(2,1)$。

对于终点，一定是走到 $(n-1,m)$ 或 $(n,m-1)$。

于是问题转化成为了 $(1,2)$ 或 $(2,1)$ 走到 $(n-1,m)$ 或 $(n,m-1)$ 不相交路径个数。

但是，对于 $(1,2)$ 走到 $(n,m-1)$ 与 $(2,1)$ 走到 $(n-1,m)$ 必定相交。

故起点终点一一对应，此时便想到 $LGV$ 引理。

对于答案，我们分别算出 $\omega (P_1),\omega (P_2),\omega (P_3),\omega (P_4)$ 。

分别表示为 $(1,2)$ 走到 $(n-1,m)$ 的方案数，$(2,1)$ 走到 $(n,m-1)$ 的方案数，$(1,2)$ 走到 $(n,m-1)$ 的方案数，$(2,1)$ 走到 $(n-1,m)$ 的方案数。

答案即为 $\omega (P_1)\times \omega (P_2)-\omega (P_3)\times \omega (P_4)$ 。

对于 $\omega$，我们可以用 $dp$ 求解，设 $f_{i,j}$ 表示从 $(1,2)$ 到 $(i,j)$ 的方案数，$g_{i,j}$ 表示从 $(2,1)$ 到 $(i,j)$ 的方案数。

转移只写 $f$，$g$ 同类：

$$f_{i,j}=f_{i-1,j}[c_{i,j-1}='.']+f_{i,j-1}[c_{i,j-1}='.']$$

复杂度 $O(n^2)$。

```cpp
#include<cstdio> 
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define int ll
using namespace std;
const int N=3e3+10,mod=1e9+7;
inline int read(){
	int d=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){d=(d<<1)+(d<<3)+(ch^48);ch=getchar();}
	return d*f;
}
int n,m,ans1,ans2,ans3,ans4,f[N][N],g[N][N];
char ch[N][N];
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",ch[i]+1);
	}
	f[1][2]=(ch[1][2]!='#')?1:0;
	for(int i=1;i<=n;i++){
		for(int j=2;j<=m;j++){
			if(ch[i+1][j]!='#') f[i+1][j]=(f[i+1][j]+f[i][j])%mod;
			if(ch[i][j+1]!='#') f[i][j+1]=(f[i][j+1]+f[i][j])%mod;
		}
	}
	ans1=f[n-1][m];ans3=f[n][m-1];
	g[2][1]=(ch[2][1]!='#')?1:0;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ch[i+1][j]!='#') g[i+1][j]=(g[i+1][j]+g[i][j])%mod;
			if(ch[i][j+1]!='#') g[i][j+1]=(g[i][j+1]+g[i][j])%mod;
		}
	}
	ans2=g[n][m-1];ans4=g[n-1][m];
	printf("%lld\n",(ans1*ans2%mod-ans3*ans4%mod+mod)%mod);
	return 0;
}
```


---

## 作者：OceanLiu (赞：0)

这么好的思维题竟然没人写题解？那蒟蒻就来写一篇总结一下吧。

这是我们模拟赛题，完全不会，只打了个暴力骗了40分。听了前辈讲课后大呼其神，幸甚至哉，歌以咏志。

$n^4$的暴力很好想：

设$f[i][j][k][l]$表示第一个人走到$(i,j)$，第二个人走到$(k,l)$的方案数。然后转移注意要同步转移。代码参考传纸条（[传送门](https://www.luogu.com.cn/problem/P1006)）。貌似也可以优化成$n^3$(同机房大佬说的)，但我没试过。

正解：

1.LGV定理。会这个定理的大佬可以秒切此题，而且这一类不相交路径问题都可以切掉。但本蒟蒻实在不会QAQ。定理请自行百度。

2.递推（思维题）。我从这个相对简单的角度来分析解法。

题意可以简化为从$(1,2)$到$(n-1,m)$和从$(2,1)$到$(n,m-1)$的路径不相交的方案数。然后，本题的精髓来了：

**如果两条路径有相交，那么可以理解为这种情况是从$(1,2)$到$(n,m-1)$和从$(2,1)$到$(n-1,m)$的路径**。这种情况是不合法的。所以我们只需要一步容斥一下，那么答案就是：

$calc(1,2,n-1,m)*calc(2,1,n,m-1)-calc(1,2,n,m-1)*clac(2,1,n-1,m)$

代码难度普及-，思维难度提高+

代码：

```cpp
//calc(1,2,n-1,m)*calc(2,1,n,m-1)-calc(2,1,n-1,m)*calc(1,2,n,m-1)
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
long long n,m,f[3005][3005];
char vis[3005][3005];
inline int calc(int a,int b,int c,int d)
{
	memset(f,0,sizeof(f));
	for (int i=a;i<=c;i++)
		for (int j=b;j<=d;j++)
		{
			if (vis[i][j]=='.'){
				if (i==a&&j==b) f[i][j]=1;
				else f[i][j]=(f[i-1][j]+f[i][j-1])%mod;
			}
		}
	return f[c][d];
}
signed main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++) scanf("%s",vis[i]+1);
	int t1=calc(1,2,n-1,m),t2=calc(2,1,n,m-1);
	int t3=calc(1,2,n,m-1),t4=calc(2,1,n-1,m);
	cout<<((t1*t2%mod-t3*t4%mod)+mod)%mod;
	return 0;
} 
```

---

