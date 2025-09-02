# Comb

## 题目描述

### 题面描述

克服所有困难以后，劳拉发现她在一间有宝藏的屋子里。令她惊讶的是，那里没有堆积成山的金子。环顾四周，她注意到在地面上有一个大小为 $n\times m$ 个格子的桌子，桌子的每个格子上有一个数字。墙边有无数石头。桌边的柱子上有一条告示。告示上说，为了拿到宝藏，对桌子的每一行都必须选择从第一个格子开始连续的几个格子（不能为0）并且将石头放在上面，将这些格子压下去。那之后她会得到很多金币，数目等同于所有压下去的格子上的数字之和。劳拉很快决定了如何放置石头，但在她开始之前她注意到了告示下面的一行小字。根据这行字，为了不让天花板掉下来并砸死探险者，探险者选择的格子要形成一个`Comb`。如果令 $c_i$ 表示第 $i$ 行选择的格子数量，那么选择的格子能形成一个`Comb`当且仅当 $c_1>c_2<c_3>c_4\ldots$ ，就是相邻的不等号方向不同。现在劳拉很迷惑，停止了思考，不知道要怎么做。帮她判断她最多能获得多少金币，同时活下来。

### 简要题意

有 $n\times m$ 个数组成一个矩阵，第 $i$ 行选择前 $c_i>0$ 个数 $a_{i,1},a_{i,2},\ldots,a_{i,c_i}$ ，问满足 $c_1>c_2<c_3>c_4\ldots$ 的前提下 $\sum_{i=1}^n\sum_{j=1}^{c_i}a_{i,j}$ 的最大值是多少。

## 样例 #1

### 输入

```
2 2
-1 2
1 3
```

### 输出

```
2
```

# 题解

## 作者：E1_de5truct0r (赞：6)

我调了 50 分钟才做出来的题，很练习代码能力。建议评为蓝题。

首先看到这道题，就自然而然的想到了状态：$dp_{i,j}$ 表示选了前 $i$ 行，第 $i$ 行选了 $j$ 个时题目要求的最大值。

状态转移方程很自然地想到了：

如果 $i$ 为奇数，那么 $dp_{i,j} = \max_{k=1}^{j-1}(dp_{i-1,k} + \sum_{l=1}^{k}a_{i,l})$ （只能选 $k$ 比 $j$ 小的状态，原因见题目）

否则 $i$ 为偶数，那么 $dp_{i,j} = \max_{k=1}^{j-1}(dp_{i-1,k} + \sum_{l=1}^{k}a_{i,l})$ （只能选 $k$ 比 $j$ 大的状态。）

这个复杂度是 $O(n^4)$ 显然会 T 飞。

## 优化一

那个 $l$ 的循环显然可以在 $k$ 循环的时候顺便求出来。这样时间复杂度降到了 $O(n^3)$。交上去，发现第 18 个点 T 飞了。

## 优化二

我们先把优化一之后的转移的核心代码写出来：

```cpp
if(i&1)
{
	int sum=0; //前缀和
	for(int j=1;j<=m;j++)
	{
		sum+=a[i][j]; //优化
		for(int k=1;k<j;k++)
			dp[i][j]=max(dp[i][j],dp[i-1][k]+sum); //转移
	}
}
else
{
	int sum=0;
	for(int j=1;j<=m;j++)
	{
		sum+=a[i][j];
		for(int k=j+1;k<=m;k++)
			dp[i][j]=max(dp[i][j],dp[i-1][k]+sum);
	}
}
```

我们发现，在 $i$ 为奇数的时候，$dp_{i,j}$ 能取到的 $k$ 的范围随着 $j$ 的增加而增加，且每次 $j$ 增加 1，$k$ 的取值范围也增加 1.。因此我们可以每次取得 $\max$ 要么是上次所有取值已经求出的 $\max$ 值得来的，要么是当前能取到的 $dp_{i-1,j-1}$。$i$ 为偶数的时候，我们更改循环顺序为倒序就可以了。

你也许看蒙了，给你们放上转移代码结合一个例子再理解一下：

```
3 3
-1 2 5
-3 6 -1
2 1 -4
```

第一行显然：

$dp_{1,1} = -1,dp_{1,2} = 1,dp_{1,3} = 6$

第二行的推导： 因为是偶数所以倒序推。

$dp_{2,3}$ 会用到第一行第四个往后这些状态（因为只能取 $j>3$ 的上一行状态。）然后发现没法转移，所以赋成 ```INF```。

$dp_{2,2}$ 会用到第一行第三个及往后的这些状态（理由同上）那么这次相当于上一次取得所有 $\max$ 和现在新增的取值 $dp_{1,3}$ 取 $\max$。加上预处理的和，得出这个等于 $6 + 3 = 9$。

$dp_{2,1}$ 会用到第一行第二个及往后的状态（理由略）那么这次相当于上一次取得所有的 $\max$ 和现在新增的取值 $dp_{1,2}$ 取 $\max$。因为 $dp_{1,2}$ 太逊了没有 $dp_{1,3}$ 大，因此 $\max$ 还是 $dp_{1,3}$。加上预处理的和，得出这个等于 $6 + (-1) = 5$。

第三行是奇数行，方法和第二行同理，只不过顺序是从 $1$ 到 $m$ 逐个处理。

### 希望您听懂了。如果没听懂，麻烦您请画个图（我画的太烂了）模拟一下。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[1505][1505],dp[1505][1505];
signed main()
{
	ios_base::sync_with_stdio(false);
	memset(dp,-0x3f,sizeof(dp)); //一定要记得！！！会有负数情况！！！
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=m;i++) dp[0][i]=0;
	for(int i=1;i<=n;i++)
	{
		if(i&1)
		{
			int sum=0; //前缀和
			for(int j=1;j<=m;j++)
			{
				sum+=a[i][j];
				dp[i][j]=max(dp[i][j-1]-sum+a[i][j]/*因为这里每次转移之后加上了 sum 所以还原的时候要减掉 sum*/,dp[i-1][j-1])+sum; //转移
			}
		}
		else
		{
			int sum=0;
			for(int j=1;j<=m;j++) sum+=a[i][j]; //由于是倒序需要先预处理
			for(int j=m;j>=1;j--)
			{
				dp[i][j]=max(dp[i][j+1]-sum-a[i][j+1],dp[i-1][j+1])+sum;
				sum-=a[i][j]; //每次减掉已经用完的
			}
		}
	}
	int ans=-1e9; //一定要记得！！！会有负数情况！！！
	for(int i=1;i<=m;i++)
		ans=max(ans,dp[n][i]); //最后对答案取 max
	cout<<ans; //实而不华的输出！
	return 0;
}
```

完结撒花！~~~

---

## 作者：pikabi (赞：4)

### 前置芝士：
~~简单的~~前缀和。

### 简要题意 
有 $ n\times m$个数组成一个矩阵，第 $i$ 行选择前 $c_i>0$ 个数$a_{i,1} ,a_{i,2},…,a_{i,c_i}$，问满足 $c_1 > c_2 < c_3 >c_4 …$的前提下$\sum_{i=1}^n \sum_{j = 1}^{c_i}a_{i, j}$的最大值是多少。

### Solution

读入时，预处理前缀和--->

```
sum[i][j] = sum[i][j - 1] + a[i][j];
```
令 $f_{i,j}$ 表示第 $i$ 行第 $j$ 列最大值， $g_{i,j}$ 表示第 $i$ 行前 $j$ 个$f_{i,j}$的最大值，$t_{i,j}$ 表示其后 $m - j + 1$ 个的最大值。每次更新即可。最后输出最后一行中最大的值。（别忘了使 $g_{i,0}$ 和 $t_{i,m+1}$ 设为 -inf，是为了应付全为负的情况）--->

```cpp
for(int i = 1; i <= n; i++){
	g[i][0] = -inf;
	t[i][m + 1] = -inf;
	for(int j = 1; j <= m; j++){
		if(i % 2){
			f[i][j] = g[i - 1][j - 1] + sum[i][j];
		}
		else {
			f[i][j] = t[i - 1][j + 1] + sum[i][j];
		}
			g[i][j] = max(g[i][j - 1], f[i][j]);
		}
	for(int j = m; j >= 1; j--){
		t[i][j] = max(t[i][j + 1], f[i][j]);
		}
}
```

献上完整代码--->

```cpp
#include <cstdio>
#include <algorithm>
#define PT 520
#define inf 1023456789
#define ll long long

using namespace std;

ll n, m, a[1505][1505], sum[1505][1505];
ll f[1505][1505], g[1505][1505], t[1505][1505], maxn = -inf;

int main(){
	scanf("%lld%lld",&n,&m);
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++)
	scanf("%lld",&a[i][j]), sum[i][j] = sum[i][j - 1] + a[i][j];
	for(int i = 1; i <= n; i++){
		g[i][0] = -inf;
		t[i][m + 1] = -inf;
		for(int j = 1; j <= m; j++){
			if(i % 2){
				f[i][j] = g[i - 1][j - 1] + sum[i][j];
			}
			else {
				f[i][j] = t[i - 1][j + 1] + sum[i][j];
			}
			g[i][j] = max(g[i][j - 1], f[i][j]);
			
		}
		for(int j = m; j >= 1; j--){
			t[i][j] = max(t[i][j + 1], f[i][j]);
		}
	}
	for(int j = 1; j <= m; j++)
	maxn = max(maxn, f[n][j]);
	printf("%lld\n",maxn);
} 
```
完结撒花✿✿ヽ(°▽°)ノ✿


---

## 作者：lgx57 (赞：1)

简单前缀和优化 dp 题，写了 $20$ 分钟就过了。

首先肯定要预处理出每一行的前缀和。用 $sum_{i,j}$ 表示  $\displaystyle\sum_{i=1}^j a_{i,j}$。

接下来可以设计 dp。设 $dp_{i,j}$ 为当前在第 $i$ 行选了 $j$ 个数的最大值。那么

$$dp_{i,j}=\begin{cases} sum_{i,j}+\displaystyle\max_{k=1}^{j-1} dp_{i-1,k} & i \bmod 2 = 1 \\ sum_{i,j}+\displaystyle\max_{k=j+1}^{m} dp_{i-1,k} & i \bmod 2 = 0\end{cases}$$

这样就可以前缀和优化了。每一轮计算预处理出上一次的 $dp$ 的前缀 $\max$ 与后缀 $\max$，可以把复杂度优化到 $O(nm)$。

---

## 作者：RE_Prince (赞：1)

# CF46E Solution

算法：DP+优先队列

调了一上午，终于过了……

### 思路 1

我们用 $dp_{i,j,k}$ 表示现在处理到第 $i$ 行，上一行取了 $j$ 个数字，这一行取 $k$ 个数字的数字最大和。但是，$n,m\leq 1500$，空间复杂度不允许，需要优化。

### 思路 2

优化 DP 空间通常都是降低维度或者滚动数组，这里我们用降维的方法。

题目问的是最大和，既然它没问方案，我们求一行取多少数就只需要知道上一行取了多少数，并不需要具体到这行取了多少数。这样求一下这行的最大前缀和就好了。因此，现在我们的状态设计是 $dp_{i,j}$ 表示现在处理到第 $i$ 行，上一行取了 $j$ 个数的最大数字和。

那状态转移呢？

很显然，我们要分类讨论 $i$ 的奇偶性。如果 $i$ 为奇数的话，$dp_{i,j}=d_{i-1,j}+\max(q_{i,j+1},q_{i,j+2}\dots q_{i,m})$，其中 $d_{i,j}$ 表示现在处理到第 $i$ 行，**这行**取了 $j$ 个数的最大和。$q_{i,j}$ 表示第 $i$ 行前 $j$ 个数的和。取 $j+1\sim m$ 是为了保证满足“梳子”的要求。

同理，当 $i$ 为偶数，$dp_{i,j}=d_{i-1,j}+\max(q_{i,1},q_{i,2}\dots q_{i,j-1})$。

这两个状态转移方程里的前缀和最大值用两个数组 $f,b$ 来分别从前后维护前缀和的前缀/后缀最大值，这样可以 $O(1)$ 查询最大值。

我们除了更新 $dp$ 数组，还要每次更新 $d$。

显然，当 $i$ 为奇数时，$d_{i,j}=\max(d_{i-1,1},d_{i-1,2},\dots d_{i-1,j-1})$。考虑到 $d$ 数组是实时变化的，不能用前缀和维护，必须每次重新更新，但要注意时间复杂度的问题。

为了避免超时，每次循环找 $\max$ 肯定不行。但是，我们注意到循环会有很多重复统计的 $d_{i,j}$，只有最新加入的 $d_{i-1,j-1}$ 是被实际统计的。因此，我们只需将新来的那个元素放入到整个序列中就好了。我用了 `priority_queue` 来维护这个动态最大值。

找到了最大值，这道题也就结束了，最后答案为 $\max(dp_{n,1},dp_{n,2},\dots dp_{n,m})$。

附代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,i,j,k,ans=-1e18;
int a[1509][1509];
int f[1509][1509],b[1509][1509];
int qzh[1509][1509];
int dp[1509][1509],d[1509][1509];
void fmax(int p)
{
	for(int i=1;i<=m;i++) f[p][i]=max(f[p][i-1],qzh[p][i]);
	for(int i=m;i>=1;i--) b[p][i]=max(b[p][i+1],qzh[p][i]);
}
signed main()
{
	memset(f,-0x7f,sizeof(f));
	memset(b,-0x7f,sizeof(b));
	cin>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++) scanf("%lld",&a[i][j]),qzh[i][j]=qzh[i][j-1]+a[i][j];//一定用scanf，会T
	for(i=1;i<=n;i++) fmax(i);//统计前缀和的最大前缀/后缀
	for(i=1;i<=n;i++)
	{
		int st,ed;
		if(i&1) st=1,ed=m-1;
		else st=2,ed=m;//注意下边界
		for(j=st;j<=ed;j++) 
		{
			if(i==1) dp[i][j]=b[1][2];
			else if(i&1) dp[i][j]=b[i][j+1]+d[i-1][j];
			else dp[i][j]=f[i][j-1]+d[i-1][j];
		}//状态转移
		if(!(i&1)) st=1,ed=m-1;
		else st=2,ed=m;
		priority_queue<int> q;
		if(i&1)//更新d
		{
			q.push(d[i-1][1]);
			for(j=st;j<=ed;j++) 
			{
				d[i][j]=q.top()+qzh[i][j];
				q.push(d[i-1][j]);
			}
		}
		else
		{
			q.push(d[i-1][m]);
			for(j=ed;j>=st;j--) 
			{
				d[i][j]=q.top()+qzh[i][j];
				q.push(d[i-1][j]);
			}
		}
	}
	int st,ed;
	if(!(n&1)) st=2,ed=m;
	else st=1,ed=m-1;
	for(i=st;i<=ed;i++) ans=max(ans,dp[n][i]);//统计答案
	cout<<ans;
	return 0;
}
```

---

## 作者：yifu_chen (赞：0)

#### 题意

有一个 $n\times m$  的矩阵，要在每行选择前几个元素（必须选），使选择的元素的和最大。设第 $i$ 行选择了 $c_i$ 个元素，则还需要满足 $c_1>c_2<c_3>c_4<...$ 

#### 思路

设 $f_{i,j}$ 表示前 $i$ 行在第 $i$ 行选择了 $j$ 个元素的前提下最大的元素和。

犹豫每行不能选择 $0$ 个，所以可以初始时将 $f_{0,1}$ 设为 $0$。

$   f_{i,j}= \left\{ \begin{array}{rcl} \max _{k=1}^{j-1}f_{i-1,k}+w_{i,j}(i\mod 2=1)\\ \max_{k=j+1}^{m} f_{i-1,k}+w_{i,j}(i\mod 2=0)\end{array}\right.$

这里的 $w_{i,j}=\sum_{k=1}^ja_{i,k}$，即输入的矩阵每一行的前缀和。

最后求 $\max _{i=1}^m f_{n,i}$。

但是此时的时间复杂度是 $O(nm^2)$，所以要在枚举状态 $j$ 的同时更新所有 $f_{i-1,k}$ 的最大值。以 $i\mod 2=1$ 的情况为例，用一个变量存储对于当前的 $i$ 和 $j$ 的$\max_{k=1}^{j-1}f_{i-1,k}$。从小到大枚举 $j$ ，在计算完当前的 $f_{i,j}$ 之后，用 $f_{i-1,j}$ 更新这个变量。这样时间复杂度变为 $O(nm)$ 。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1505;
int n,m,a[N][N];
long long w[N][N],f[N][N],maxn;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie();
	cout.tie(); 
	cin>>n>>m;
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
        	cin>>a[i][j];
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
        	w[i][j]=w[i][j-1]+a[i][j];
    for(int i=0;i<=n;i++)
    	for(int j=1;j<=m;j++)
        	f[i][j]=-1e18;
    f[0][1]=0;
    for(int i=1;i<=n;i++)
    {
    	maxn=-1e18;
    	if(i%2==1)
        {
        	for(int j=1;j<=m;j++)
            {
            	if(maxn!=-1e18)f[i][j]=maxn+w[i][j];
            	else           f[i][j]=-1e18;
            	maxn=max(maxn,f[i-1][j]);
            }
        }
        else
        {
        	for(int j=m;j>=1;j--)
            {
            	if(maxn!=-1e18)f[i][j]=maxn+w[i][j];
            	else           f[i][j]=-1e18;
                maxn=max(maxn,f[i-1][j]);
            }
        }
    }
    long long ans=-1e18;
    for(int i=1;i<=m;i++)ans=max(ans,f[n][i]);
    cout<<ans;
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

裸 DP。

令 $dp_{i,j}$ 为第 $i$ 行取了 $j$ 个数的最大值。

当 $i$ 是偶数时，$dp_{i,j} = max_{k = j + 1}^m dp_{i - 1,k} + \sum_{k = 1}^j a_{i,k}$。

当 $i$ 是奇数时，$dp_{i,j} = max_{k = 1}^{j - 1} dp_{i - 1,k} + \sum_{k = 1}^j a_{i,k}$。

显然我们可以用前缀和、前缀最大值和后缀最大值做到 $O(n^2)$。

**DP 不初始化见祖宗。**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1510;
const int inf = 1e16;
int T,n,m;
int a[N][N],sum[N][N],dp[N][N];
int mx1[N][N],mx2[N][N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> n >> m;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= m ; j++)
			cin >> a[i][j];
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= m ; j++)
			sum[i][j] = sum[i][j - 1] + a[i][j];
	for (int i = 1 ; i <= n ; i++){
		for (int j = 1 ; j <= m ; j++){
			if (i & 1) dp[i][j] = mx1[i - 1][j - 1] + sum[i][j];
			else dp[i][j] = mx2[i - 1][j + 1] + sum[i][j];
		}
		mx1[i][0] = mx2[i][m + 1] = -inf;
		for (int j = 1 ; j <= m ; j++) mx1[i][j] = max(mx1[i][j - 1],dp[i][j]);
		for (int j = m ; j >= 1 ; j--) mx2[i][j] = max(mx2[i][j + 1],dp[i][j]);
	}
	int ans = 0;
	cout << mx1[n][m] << endl;
}
signed main(){
	close();
	T = 1;
	//cin >> T;
	while (T--) solve();
	return 0;
}
```

---

