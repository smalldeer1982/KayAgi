# George and Job

## 题目描述

新款手机 iTone6 近期上市，George 很想买一只。不幸地，George 没有足够的钱，所以 George 打算当一名程序猿去打工。现在George遇到了一个问题。
给出一组有 $n$ 个整数的数列 $p_1,p_2,...,p_n$ ,你需要挑出 $k$ 组长度为 $m$ 的数，要求这些数互不重叠
即$ [l_{1},r_{1}],[l_{2},r_{2}],...,[l_{k},r_{k}] (1<=l_{1}<=r_{1}<l_{2}<=r_{2}<...<l_{k}<=r_{k}<=n; r_{i}-l_{i}+1=m)$
使选出的数的和值最大，请你帮助George码出这份代码

## 样例 #1

### 输入

```
5 2 1
1 2 3 4 5
```

### 输出

```
9
```

## 样例 #2

### 输入

```
7 1 3
2 10 7 18 5 33 0
```

### 输出

```
61
```

# 题解

## 作者：VenusM1nT (赞：8)

这道DP比较有难度（对本蒟蒻来说） 
蒟蒻表示DP很是伤不起啊
做这题需要用到前缀和的思想，以便更好地DP
我们用$f[i][j]$表示前$i$个数中选了$j$个区间可以取得的最大值
同时我们用$s[i]$表示到$i$为止的$m$个数的和
状态转移方程就很明了了:$f[i][j]=f[i-i][j],f[i][j]=max(f[i][j],f[i-m][j-1]+s[i])$
答案在$f[n][k]$的位置
具体见代码 

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long n,m,k,a[5005],s[5005],f[5005][5005];//注意用longlong 
int main()
{
    scanf("%lld %lld %lld",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    long long tot=0;
    for(int i=1;i<=n;i++)
    {
        tot+=a[i];
        if(i>=m)
        {
            s[i]=tot;//前缀和部分，个人认为这样做比较方便
			//用tot表示现在位置的前缀和，存值之后减掉该段的首个数（越界的数） 
			//有点像优先队列【大雾 
            tot-=a[i-m+1];
        }
    }
    memset(f,-1,sizeof(f));
    for(int i=0;i<=n;i++) f[i][0]=0;//初值 
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=k;j++)
        {
            f[i][j]=f[i-1][j];
            if(i>=m && f[i-m][j-1]>-1) f[i][j]=max(f[i][j],f[i-m][j-1]+s[i]);
            //状态转移方程，别忘记判断 
        }
    }
    printf("%lld",f[n][k]);//输出 
    return 0;
}
```

---

## 作者：_JF_ (赞：7)

## CF467C George and Job

[题目传送门](https://www.luogu.com.cn/problem/CF467C)

一道比较简单的 dp 题目。

设 $dp[i][j]$ 表示前 $i$ 个数，选了 $j$ 组，所可以获得的最大值。

答案就显而易见了，是 $dp[n][k]$。

设 $sum[i]$ 表示前 $i$ 个数的和。

首先，$dp[1][1]=sum[1]$。


对于我当前枚举的 $i$ 而言，相对于 $i-1$ 而言，会产生 $[i-m+1,i]$ 的一个区间。

所以我们就要分类讨论，选不选择这个区间。

对于当前的 $dp[i][j]$ 而言，如果我不选当前的 $[i-m+1,i]$ 的这个区间的话，答案就是 $dp[i-1][j]$。

如果我选当前的区间的话，就是 

$dp[i-m][j-1]+sum[i]-sum[i-m]$。


综合一下，就是：

$$ dp[i][j]=\max(dp[i-1][j],dp[i-m][j-1]+sum[i]-sum[i-m])$$

由于需要选择 $m$ 个数，所以枚举应该从 $m$ 开始。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =5010;
#define int long long
int dp[N][N],a[N],sum[N];
signed main()
{
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	dp[1][1]=sum[1];
	for(int i=m;i<=n;i++)
	{
		for(int j=1;j<=k;j++)
			dp[i][j]=max(dp[i-1][j],dp[i-m][j-1]+sum[i]-sum[i-m]);
	}
	cout<<dp[n][k]<<endl;
}
```


---

## 作者：BriMon (赞：4)

更好的阅读体验[戳这里](https://www.cnblogs.com/BriMon/p/9693210.html)

题目要求在$n$个数中选择$m$组长度为$k$的子序列使得和最大。

很容易想到，设 $f[i][j]$ 表示选择了i组，并且最后一组以j结尾的最大值。

那么 $\large f[i][j]= max_{p\leq j-k+1} \left ( f[i-1][p] + sum[i]-sum[i-k] \right )$。

这显然是$O(N^3)$的过不了。

所以用$g[p]$表示$f[i-1][1\rightarrow p]$的最大值。

这样就可以$O(1)$转移了。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define reg register 
inline char gc() {
	static const int BS = 1 << 22;
	static unsigned char Buf[BS], *st, *ed;
	if (st == ed) ed = Buf + fread(st = Buf, 1, BS, stdin);
	return st == ed ? EOF : *st++;
}
#define gc getchar
inline int read() {
	int res=0;char ch=getchar();bool fu=0;
	while(!isdigit(ch)) {if(ch=='-')fu=1;ch=getchar();}
	while(isdigit(ch))res=(res<<3)+(res<<1)+(ch^48), ch=getchar();
	return fu?-res:res;
}
#define ll long long 

int n, m, k;
ll f[5005][5005], g[5005];
ll sum[5005];
ll ans;

int main()
{
	n = read(), k = read(), m = read();
	for (reg int i = 1 ; i <= n ; i ++) sum[i] = sum[i-1] + read();
	for (reg int i = k ; i <= n ; i ++) f[1][i] = sum[i] - sum[i-k], g[i] = max(g[i-1], f[1][i]);
	for (reg int i = 2 ; i <= m ; i ++)
	{
		for (reg int j = k ; j <= n ; j ++)
			f[i][j] = g[j-k] + sum[j] - sum[j-k];
		memset(g, 0, sizeof g);
		for (reg int j = 1 ; j <= n ; j ++) 
			g[j] = max(g[j-1], f[i][j]);
	}
	for (reg int i = k ; i <= n ; i ++) ans = max(ans, f[m][i]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：RockyYue (赞：3)

感谢管理大大审核~

# 解题思路

很明显的 dp 题。

- 状态定义：令 $dp[i][j]$ 为 $n=i,k=j$ 时选出最后一个数的答案。

- 状态转移方程：
因为第 $i$ 个数必须选出，且为数组中最后一个数，则必须是一个子序列的结尾。我们再枚举一下上一个子序列的结尾，取最优即可。

- 优化：单调队列优化，前缀和预处理所有子序列的和。

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5005;
int a[N], s[N], q[N], dp[N][N];
signed main() {
    ios :: sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    int res = 0;
    for (int j = 1; j <= k; ++j) {
        memset(q, 0, sizeof q);
        int head = 1, tail = 1;
        for (int i = m; i <= n; ++i) {
            if (head <= tail) {
                dp[i][j] = max(dp[i][j], dp[q[head]][j - 1] + s[i] - s[i - m]);
            }
            while (head <= tail && dp[i - m + 1][j - 1] > dp[q[tail]][j - 1]) {
                --tail;
            }
            q[++tail] = i - m + 1;
            res = max(res, dp[i][k]);
        }
    }
    cout << res << '\n';
    return 0;
}
```


---

## 作者：Supor__Shoep (赞：2)

很明显这是一道 dp，但是它绝对不是区间 dp（也许是因为我打不出来）。

首先观察一下数据范围 $1\leq n\leq 5000$ 我们就可以想到定义一个二维的 dp 数组。定义 $dp_{i,j}$ 表示在前面 $i$ 个数中选择 $j$ 组长度为 $m$ 的不重叠子段。因此可以得到最终答案为 $dp_{n,k}$。

我们希望求得 $dp_{n,k}$ 的时间复杂度为 $O(n^2)$ 以内。所以我们可以枚举 $m$ 到 $n$ 的 $i$，并且分解 $j$ 个子段，此时的最优解可以是 $i-1$ 时的最优解（dp 的顺延），或者以 $i$ 为末尾重新取一个子段。根据这个思路，我们就可以列出方程：

$$dp_{i,j}=\text{max}(dp_{i-1,j},~dp_{i-m,j-1})$$

其中对于 $dp_{i-m,j-1}$ 的理解，就是将空间缩小至 $i-m$ 可以腾出建造以 $i$ 结尾的子段的空间，又因为答案存在了 $dp_{i,j}$ 当中，减去刚才建造的一组，就是 $j-1$。

接着代码就可以轻轻松松打出来了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long//不开 long long 见祖宗
using namespace std;
const int MAXN=5005;
int n,m,k;
long long dp[MAXN][MAXN];
long long a[MAXN],sum[MAXN];
signed main()
{
	cin>>n>>m>>k;
	for(register int i=1;i<=n;i++)	cin>>a[i];
	for(register int i=1;i<=n;i++)	sum[i]=sum[i-1]+a[i];//前缀和
	for(register int i=m;i<=n;i++)
	{
		for(register int j=1;j<=k;j++)
		{
			dp[i][j]=max(dp[i-1][j],dp[i-m][j-1]+sum[i]-sum[i-m]);//用前缀和快速求出区间和
		}
	}
	cout<<dp[n][k];
	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：2)

### 分析
我们设$f[i][j]$为前$i$个数选出了$j$组，其中第$i$个数必须选的最大值

那么我们就可以写出如下的状态转移方程
``` cpp
f[i][k]=max(f[i][k],f[j][k-1]+sum[i]-sum[i-m]);
```
时间复杂度为$O(n^3)$

实际上，我们可以用单调队列对于每一个$i$维护$f[j][k-1]$的最大值

这样时间复杂度就降到了$O(n^2)$
### 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+5;
#define int long long
int sum[maxn],a[maxn],f[maxn][maxn],q[maxn],head,tail;
signed main(){
    int n,m,p;
    scanf("%lld%lld%lld",&n,&m,&p);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        sum[i]=sum[i-1]+a[i];
    }
    int ans=0;
    for(int j=1;j<=p;j++){
        head=1,tail=1;
        memset(q,0,sizeof(q));
        for(int i=m;i<=n;i++){
            if(head<=tail)f[i][j]=max(f[i][j],f[q[head]][j-1]+sum[i]-sum[i-m]);
            while(head<=tail && f[i-m+1][j-1]>f[q[tail]][j-1]) tail--;
            q[++tail]=i-m+1;
            ans=max(ans,f[i][p]);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Fading (赞：1)

简单$dp$

设$f[i][j]$为前$i$个区间，选$1$~$j$之间的数的和最大值。

$$f[i][j]=max\left\{\begin{aligned}f[i-1][j]\ \ \text{(这个由于没有负数没用)}\\f[i-1][k]+\sum_{q=j-m+1}^{j}p[i]\ \ (k\leq j-m)\\f[i][j-1]\ \ \text{(可以不要这堆数)}\\\end{aligned}\right.$$

这个$\sum$很好用前缀和优化。至于这个$f[i-1][k]$，可以用一个变量记录前缀最大值。然后这道题就做完了。

不过你想要写单调队列单调栈什么的也可以。。。

为了优化空间，我们使用滚动数组。

```cpp
#include<bits/stdc++.h>
#define maxn 500002
#define int long long
using namespace std;
int s[5002],m,k,n,f[2][5002];
bool cur;
inline int read(){
    int x=0;char ch=getchar();int f=1;
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
signed main(){
	n=read(),m=read(),k=read();
	for (int i=1;i<=n;i++) s[i]=s[i-1]+read();
	for (int i=1;i<=k;i++){
		cur^=1;
		int MAX=0;
		for (int j=m;j<=n;j++){
			f[cur][j]=max(f[cur][j],f[cur][j-1]);
			MAX=max(MAX,f[cur^1][j-m]);
			f[cur][j]=max(f[cur][j],MAX+s[j]-s[j-m]);
		}
	}
	cout<<f[cur][n];
	return 0;
}
```


---

## 作者：芜奕丶 (赞：1)

## ~~趁着没有人赶快来水一发Pascal题解~~
#### 本题，前缀和+dp，~~难度还行~~
题意要算到第i项到第i+k项的和的和的最大值，很容易想到前缀和。

```pascal
for i:=1 to n do
    begin
        read(x);
        a[i]:=a[i-1]+x;//前i项的和
    end;
```

我们以f[a,b]来表示在前i个数中选了j个长k的区间的最大值，那么就有点像最大子序列和了，~~根据dp尿性等，很容易可以~~写出
#### 状·态·转·移·方·程
#### f[i,j]:=max(f[i,j-1], (f[i-1,j-m] +a[j]-a[j-m]));
这么一想，就很容易了。

最后放上Pascal的代码：丑爆勿喷
```pascal
uses math;
var a:array[0..5001] of int64;
	f:array[0..5001,0..5001] of int64;
	i,j,k,n,x,m:longint;
begin
	readln(n,m,k);
	for i:=1 to n do
    begin
        read(x);
        a[i]:=a[i-1]+x;
    end;
	for i:=1 to k do
		for j:=1 to n do
			if i*m>j then f[i,j]:=0
			else f[i,j]:=max(f[i,j-1], (f[i-1,j-m] +a[j]-a[j-m]));
	writeln(f[k,n]);
end.
```

---

## 作者：CANTORSORT (赞：1)

这一题的关键其实是在于 $n$ 个数选 $k$ 个长度为 $m$ 的子串，反而求和这一部分可以直接用前缀和来优化掉复杂度。

事实上，我感觉这一题倒是有一点背包的味道，至于为什么，继续讲下去就知道了。

我们设 $dp_{i,j}$ 为从前面 $i$ 个数中已经选出了 $j$ 个区间的情况，其中 $m\le i\le n,1\le j\le k$。

这里要对 $p_{i-m},p_{i-m+1},\cdots,p_i$ 这段序列是否选择进行分类讨论：

1. 如果不选择这段序列，则 $dp_{i,j}=dp_{i-1,j}$；

2. 如果选择这段序列，则 $dp_{i,j}=dp_{i-m,j-1}+sum_{i}-sum_{i-m}$。

这两种情况只能选择其中一个，那么状态转移方程就出来了：

$$dp_{i,j}=\max(dp_{i-1,j},dp_{i-m,j-1}+sum_i-sum_{i-m})$$

是不是很像背包问题？

那么最终的答案显然是 $dp_{n,k}$。

代码（部分）：

```cpp
const int N=5e3+5;
int n=read<int>(),m=read<int>(),k=read<int>(),p[N],sum[N],dp[N][N];
// 这里用 C++ 的 template 功能定义 IO
signed main()
{
	rep(i,1,n)
		p[i]=read<int>(),sum[i]=sum[i-1]+p[i];
	rep(i,m,n)
	{
		rep(j,1,k)
			dp[i][j]=max(dp[i-1][j],dp[i-m][j-1]+(sum[i]-sum[i-m]));
	}
	write(dp[n][k]);
	return 0;
}
```

---

## 作者：I_have_been_here (赞：0)

# 题目分析

简单看一下题面，已经解释得很清楚了，明显的 DP，但是不要看到区间就想区间，这是一道线性 DP，我们可以加一点前缀和处理。

# 思路解析

定义状态 $dp_{i,j}$ 表示在前 $i$ 个数中选出 $j$ 个长度为 $m$ 的子段且子段之间互不重合的最大值，注意这里题目中已经保证了 $ (1 \le (m \times k) \le n \le 5000) $，所以说我们不用担心我们选择了多个子段后大于原区间长度的问题。

考虑对于 $dp_{i,j}$ 进行转移，首先我们可以直接又 $dp_{i - 1,j}$ 继承过来，那么第二种情况，我们需要对于第 $i$ 个数我们考虑取子段，即我们往前取 $m$ 长度的子段，这里就可以直接把前缀和套过来就行了。大概就长这个样子

$$ dp_{i,j} = \max(dp_{i - 1, j},dp_{i - m, j - 1} + pre_{i} - pre_{i - m}) $$

答案显然在 $dp_{n,k}$ 中。

# AC CODE

```cpp
#include <bits/stdc++.h> // KKK 666
#define int long long
using namespace std;
const int maxn = 5005;
int dp[maxn][maxn], n, m, k, a[maxn];
int pre[maxn];
signed main() {
	scanf("%lld %lld %lld", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		pre[i] = pre[i - 1] + a[i];
	}
	for (int i = m; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			dp[i][j] = max(dp[i - 1][j], dp[i - m][j - 1] + pre[i] - pre[i - m]);
		}
	}
	cout << dp[n][k] << endl;
	return 0;
} 
```


---

