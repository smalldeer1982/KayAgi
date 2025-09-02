# Pictures with Kittens (easy version)

## 题目描述

The only difference between easy and hard versions is the constraints.

Vova likes pictures with kittens. The news feed in the social network he uses can be represented as an array of $ n $ consecutive pictures (with kittens, of course). Vova likes all these pictures, but some are more beautiful than the others: the $ i $ -th picture has beauty $ a_i $ .

Vova wants to repost exactly $ x $ pictures in such a way that:

- each segment of the news feed of at least $ k $ consecutive pictures has at least one picture reposted by Vova;
- the sum of beauty values of reposted pictures is maximum possible.

For example, if $ k=1 $ then Vova has to repost all the pictures in the news feed. If $ k=2 $ then Vova can skip some pictures, but between every pair of consecutive pictures Vova has to repost at least one of them.

Your task is to calculate the maximum possible sum of values of reposted pictures if Vova follows conditions described above, or say that there is no way to satisfy all conditions.

## 样例 #1

### 输入

```
5 2 3
5 1 3 10 1
```

### 输出

```
18
```

## 样例 #2

### 输入

```
6 1 5
10 30 30 70 10 10
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 3 1
1 100 1 1
```

### 输出

```
100
```

# 题解

## 作者：Pengzt (赞：5)

[CF1077F1](https://www.luogu.com.cn/problem/CF1077F1)

很板的 dp。

令 $dp_{i, j}$ 表示前 $i$ 个数中，选了第 $i$ 个数且一共选了 $j$ 个数的方案数，$sum_i$ 表示 $\sum\limits_{j = 1}^{i} a_j$。

显然 $dp_{i, j} = \max\limits_{l=\max(0, i - k)}^{i - 1} dp_{l, j - 1} + a_j$。

暴力递推的话，时间复杂度 $\mathcal{O}(n^2 k)$，可过，代码就不放了。

观察转移方程，发现只需维护 $dp_{k, j - 1}, k\in [\max(0, i - m), i - 1]$ 的最大值，可以使用单调队列维护，省去了一维。

时间复杂度：$\mathcal{O}(n^2)$

注意要先将 $\texttt{dp}$ 数组赋值为 $\texttt{-inf}$，否则可能会报错。

[评测记录](https://www.luogu.com.cn/record/99437291)

---

## 作者：wkjwkj (赞：5)

对于本题，显然用 $\mathtt{dp}$ 求解。

我们用 $\mathtt{f[i][j]}$ 表示前 $i$ 个数一共取 $j$ 个且第 $i$ 个一定取所得到的最大答案。

不难写出转移方程：

$$f[i][j]=\max\{f[p][j-1]\}+a[i](i-k\le p<i)$$

若直接根据我们的转移方程进行，复杂度是 $O(n^3)$，由于数据范围较小，可以通过。~~但读者一定会听优化的吧。~~

注意到可以转移的区间长度是不变的，我们要求的即为区间 $[i-k,i-1]$ 内的最小值。

我们有两种选择，一种是采用 $\mathtt{ST}$ 算法，复杂度为 $O(n^2\log n)$。

自然也可以采用单调队列的方法。这就是裸的单调队列，直接用滑动窗口方法求解即可。

核心代码如下：

```cpp
for(int i=1;i<=n;i++)
{
	while(le<=ri&&q[le]+k<i)le++;
	f[i][j]=f[q[le]][j-1]+a[i];
	while(le<=ri&&f[i][j-1]>=f[q[ri]][j-1])ri--;
	q[++ri]=i;
}
```

本题还有一点需要注意，虽然我们通过单调队列，第一次更新即为最优答案，如果不进行初始化，但是本题可能会存在一种情况，即非法情况可能转移至合法情况，导致答案非法，说的清楚一点，即你的转移中可能会存在同一个数被加多次的情况，我们必须排除这种情况，即开始把 $\mathtt{f}$ 数组赋为负无穷，否则得到的答案可能比正确答案大。

$\mathtt{AC}$ 代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,k,x;
ll f[5005][5005];
int q[5005];
int le=1,ri=0;
int a[5005];
int main()
{
	scanf("%d%d%d",&n,&k,&x);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	memset(f,0xcf,sizeof f);
	if(n/k>x){
		puts("-1");
		return 0;
	}
	f[0][0]=0;
	for(int j=1;j<=x;j++)
	{
		le=1,ri=0;
		q[++ri]=0;
		for(int i=1;i<=n;i++)
		{
			while(le<=ri&&q[le]+k<i)le++;
			f[i][j]=f[q[le]][j-1]+a[i];
			while(le<=ri&&f[i][j-1]>=f[q[ri]][j-1])ri--;
			q[++ri]=i;
		}
	}
	ll ans=0;
	for(int i=n-k+1;i<=n;i++)ans=max(ans,f[i][x]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Nephren_Sakura (赞：3)

题目传送门：[link](https://www.luogu.com.cn/problem/CF1077F1)

不难想到状态为 $dp_{i,j}$ 表示以 $a_i$ 结尾且选了 $j$ 个元素的最大和。

状态转移方程：$dp_{i,j}=\max(dp_{i-m,j-1},dp_{i-m+1,j-1},\dots,dp_{i-1,j-1})+a_i$。

其中 $\max(dp_{i-m,j-1},dp_{i-m+1,j-1},\dots,dp_{i-1,j-1})$ 指可以转移过来的状态中的最大值，$a_i$ 指当前选择的元素。

最后输出 $\max(dp_{n-m+1,s},dp_{n-m+2,s},\dots,dp_{n,s})$ 即可。

初始化 $dp_{0,0}=1$。

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n=read(),m=read(),s=read(),a[1000005],dp[205][205];
signed main(){
    if(n/m>s){
        cout<<-1;
        return 0;
    }
    memset(dp,0xcf,sizeof(dp));
    int maxi=-1e18;
    for(int i=1; i<=n; i++)
        a[i]=read();
    dp[0][0]=0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=s; j++){
            for(int k=1; k<=min(i,m); k++)
                dp[i][j]=max(dp[i-k][j-1],dp[i][j]);
            dp[i][j]+=a[i];
        }
    }
    int sum=-1e18;
    for(int i=n-m+1; i<=n; i++)
        sum=max(sum,dp[i][s]);
    cout<<sum;
    return 0;
}
```

时间复杂度为 $O(N^3)$

---

## 作者：lraM41 (赞：2)

应该是一道比较简单的动规题吧。

考虑以 ```dp[i][j]``` 表示选取了 ```i``` 个，而取 ```a[j]``` 时的最大值，显然 $dp[i][j]=\max \{dp[i-1][K]+a[j]\}(j-k \le K<j)(1 \le j \le n)(1 \le i \le m) $，$j=k$ 时是取第一个数的情况，既 $K=0$。

代码：


```
#include<bits/stdc++.h>
#define int long long //不开 long long 见祖宗。
using namespace std;
int k,n,m,a[205],dp[205][205],ma=-1,s;//定义。
signed main()
{
   cin>>n>>k>>m;
   if(n/k>m) puts("-1"),exit(0);//无解。
   for(int i=1;i<=n;i++) cin>>a[i];
   for(int i=0;i<=200;i++)
      for(int j=0;j<=200;j++)
         dp[i][j]=-1e15;dp[0][0]=0;//初始化。
   for(int i=1;i<=m;i++)
      for(int j=1;j<=n;j++)
         for(int _=max(0LL,j-k);_<j;_++){//如果 j<k 则为 0。
            dp[i][j]=max(dp[i][j],dp[i-1][_]+a[j]);
         }
   for(int i=n-k+1;i<=n;i++)//找最大。
      ma=max(ma,dp[m][i]);
   cout<<ma;
   return 0;
}


---

## 作者：Liu_zj (赞：2)

~~AFO前最后一发题解~~

题目大意：

第一行输入三个数$n,k,m$

之后给你一个$n$个数的数列，你需要选择$m$个元素，使得连续的$k$个元素都至少有一个被选中。

需要你最大化选出来的所有数的和，并输出这个值。

考虑DP

设$f[i][j]$表示前$i$个数，选择了$j$个的最大值。其中$a_i$一定选择。

则可以轻易推出转移式：

$f[i][j]=max \  \ from \ \ f[i-k][j-1] \ \ to \  \ f[i-1][j-1] \ + a_i$

细节还是挺多的

```
#include<bits/stdc++.h>
using namespace std;
#define in(x) cin >> x
const int MAXN=201;
long long num[MAXN];
long long f[MAXN][MAXN];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	long long n,m,kk,ans(0);
	in(n); in(kk); in(m);
	if(n/kk>m){
		printf("-1");
		return 0;
	}
	for(register int i=1;i<=n;i++)
		in(num[i]);
	memset(f,0xcf,sizeof f);
	f[0][0]=0;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			long long ma=-0x3f3f3f3f3f3f3f3fll;
			for(register long long k=max(0ll,i-kk);k<i;k++)
				ma=max(ma,f[k][j-1]);
			f[i][j]=ma+num[i];
		}
	}
	for(register int i=n-kk+1;i<=n;i++)
		ans=max(ans,f[i][m]);
	cout<<ans;
}
```


---

## 作者：BzhH (赞：1)

从困难版过来的
[CF1077F2 Pictures with Kittens (hard version)](https://www.luogu.com.cn/problem/CF1077F2)
困难版需要用单调队列优化,但这道题就不需要了

定义状态$f_{i,j}$表示当前选了$i$个数字,在第$j$个数字时的和的最大值

那么很容易可以想出转移方程
$f_{i,j}=\max\limits_{0\le u<j}\limits^{1\le i \le x,0\le j\le n}f_{i-1,u}+a_j$

直接O(n^3)转移即可

代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 5005;
typedef long long ll;

ll f[N][N], a[N];

int main()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            f[i][j] = -1e18;
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    f[0][0] = 0;//初始状态
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            for (int u = 0; u < j; u++)
            {
                if (j - u <= k)
                    f[i][j] = max(f[i][j], f[i - 1][u] + a[j]);
            }暴力转移的代码
        }
    }
    ll ans = -1;
    for (int i = n - k + 1; i <= n; i++)
        ans = max(ans, f[m][i]);
    printf("%lld", ans);
}
```

---

## 作者：wyyqwq (赞：0)

### CF1077F1


$dp[i][j]$ 表示选了 $i$ 个，必选第 $j$ 个的方案数量，转移式为
$$
dp[i][j] = \max\{dp[i - 1][u](j - u \le k) + a[j], dp[i][j]\}
$$
$O(n^3)$ 转移即可。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;

const int N = 500;

int dp[N][N];
int a[N];
signed main(){
	memset(dp, -0x3f, sizeof dp);
	int n, m, k;
	cin >> n >> k >> m;
	dp[0][0] = 0; 
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
	}
	
	for(int i = 1; i <= m; i ++){
		for(int j = 0; j <= n; j ++){
			for(int u = 0; u < j; u ++){
				if(j - u <= k){
					dp[i][j] = max(dp[i - 1][u] + a[j], dp[i][j]);
				}
			}
		}
	}
	int ans = -1;
	for(int i = n - k + 1; i <= n; i ++){
		ans = max(ans, dp[m][i]);
	}
	cout << ans << endl;
}
```


---

## 作者：xxxr_2024 (赞：0)

# CF1077F1 Pictures with Kittens (easy version) 题解
## 算法
动态规划。
## 思路
1. **确定状态**，用 $dp_{i,j}$ 来表示前 $i$ 个中选 $j$ 个所得的最大和，为了便于列出状态转移方程，我们令这个状态时 $a_i$ 是必取的。
2. **确定边界值**，初始化 $dp$ 数组为负无穷，$dp_{0,0}$ 置为 $0$。
3. **列出状态转移方程**，这一位必取且要取最大和，那就要找这一位之前的最大和，而在 $k$ 个中必须取一个，那就是找区间 $[i-k,i-1]$ 之中的最大和，而为了避免 $i-k$ 为负数，在实现时与 $0$ 取个最大值。因为 $a_i$ 必取，所以 $dp_{i,j}$ 就是找出来的最大和再加上 $a_i$。
4. **输出**，最终的最大和一定是取了 $x$ 个，但最后一位有可能是区间 $[n-k+1,n]$ 之间的一个，所以还要循环取最大值，输出即可。注意，如果没有取到正值说明没有合法方案，输出 $-1$ 即可。

复杂度 $\mathcal O(n^3)$，数据范围 $n\le200$，可过。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
namespace Raiden
{
    const int N = 205;
    int k, n, x;
    int dp[N][N], a[N];
    signed work()
    {
        cin >> n >> k >> x;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        memset(dp, -0x3f, sizeof(dp));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= min(i, x); j++)
                for (int p = max(0ll, i - k); p <= i - 1; p++)
                    dp[i][j] = max(dp[i][j], dp[p][j - 1] + a[i]);
        int ans = -0x3f3f3f3f;
        for (int i = max(0ll, n - k) + 1; i <= n; i++)
            ans = max(ans, dp[i][x]);
        if (ans < 0)
            ans = -1;
        cout << ans << endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：chengning0909 (赞：0)

# CF1077F1

## 题意

给定一个长度为 $n$ 的序列 $a$，你需要选择 $x$ 个元素，使得连续 $k$ 个元素都至少有一个被选中。

你需要最大化选出来的数之和，并输出。

$1 \le k, x \le n \le 200$

$1 \le a_i \le 10 ^ 9$

## 思路

很明显，这题是 dp。

$dp_{i, j}$ 表示前 $i$ 个数中，选择 $j$ 个的最大和。

所以就有转移：

$$dp_{i, j} = \max \limits _ {\max(0, i - k) \le l < i} \{dp_{l, j - 1} + a_i\}$$

时间复杂度为 $O(n ^ 3)$。

## 代码

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 210, MAXX = 210;
const long long INF = -1e18;

int n, k, x, a[N];
long long dp[N][MAXX], ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> k >> x;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  if (n / k > x) {  // 判断非法情况
    cout << -1;
    return 0;
  }
  for (int i = 0; i <= n; i++) { 
    for (int j = 0; j <= x; j++) {
      dp[i][j] = INF; // 初始化
    }
  }
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= x; j++) {
      for (int l = max(0, i - k); l < i; l++) {
        dp[i][j] = max(dp[i][j], dp[l][j - 1] + a[i]);  // 转移
      }
    }
  }
  for (int i = n - k + 1; i <= n; i++) {  // 统计答案
    ans = max(ans, dp[i][x]);
  }
  cout << ans;
  return 0;
}
```

---

## 作者：WeiFanbo (赞：0)

[CF1077F2](https://www.luogu.com.cn/problem/CF1077F2)的弱化版

# 题意

给你一个数列 $a$，从中选择 $m$ 个元素，使得连续的 $k$ 个元素都至少有一个被选中，并使选出来的数的总和最大。

# 思路

因为题目要我们求的是最大值，自然而然想到 dp。

我们设 $dp_{i,j}$ 表示前 $i$ 个数中选了 $j$ 个数并且一定选了 $a_i$ 后选出的数的总和的最大值。那么我们可以得到一个很显然的转移方程

$dp_{i,j}=\max\ (dp_{p,j-1}+a_i)\ (i-k≤p<i)$

最后的答案就是 $\max\ dp_{p,m}\ (n-k<p≤n)$

这样朴素转移下来可以通过本题，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 210
using namespace std;
int n,m,k,a[N];
int dp[N][N];
signed main(){
	scanf("%lld%lld%lld",&n,&k,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	memset(dp,-127,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int p=max(0ll,i-k);p<i;p++)
				dp[i][j]=max(dp[i][j],dp[p][j-1]+a[i]);	
	int ans=-1;
	for(int i=n-k+1;i<=n;i++)
		ans=max(ans,dp[i][m]);
	cout<<ans;
	return 0;
}
```


# 优化

这样做的话时间复杂度为 $O(n^3)$，可以通过本题，但是对于这道题的加强版[CF1077F2](https://www.luogu.com.cn/problem/CF1077F2)来说，这样的复杂度会 TLE，那么我们考虑优化

观察这道题的状态转移方程：

$dp_{i,j}=\max\ (dp_{p,j-1}+a_i)\ (i-k≤p<i)$

我们发现他求的是上一层连续一段区间的最大值，显然可以用单调队列来优化，均摊复杂度 $O(1)$，整个题目的时间复杂度为 $O(n^2)$，这样我们就可以愉快地AC加强版了。

# CODE

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 5010
using namespace std;
int n,m,k,a[N];
int dp[N][N];
int que[N];
signed main(){
	scanf("%lld%lld%lld",&n,&k,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	memset(dp,-127,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=m;i++){
		int p=0;
		int head=1,tail=0;
		for(int j=1;j<=n;j++){
			for(;p<j;p++){
				while(head<=tail&&dp[i-1][que[tail]]<dp[i-1][p])
					tail--;
				que[++tail]=p;
			}
			while(head<=tail&&que[head]<j-k)
				head++;
			dp[i][j]=dp[i-1][que[head]]+a[j];
		}
	}
	int ans=-1;
	for(int i=n-k+1;i<=n;i++)
		ans=max(ans,dp[m][i]);
	cout<<ans;
	return 0;
}
```


---

## 作者：shao0320 (赞：0)

#### CF1077F1 Pictures with Kittens (easy version)

常规$dp$题，这个套路也见过挺多次的了。

对于这种类似于"连续$k$个中至少有一个"的题目可以直接这样设计状态$f(x,...)$表示考虑前$x$个里边符合(...)的限制条件且必须选择第$x$个的$dp$值。

那对于这道题来说就直接$f(i,j)$表示前$i$个数中取了$j$个，且第$i$个一定取的最大值，转移的话就是
$$
f(i,j)=\max^{i}_{lst=i-k}f(lst,j-1)+a_i
$$
答案直接枚举最后一个取的位置即可。

~~以下内容是我口胡的~~

注意到这个转移式子实际上是个单点插入，区间求$\max$的形式，因此可以考虑维护$n$棵线段树，然后每次快速求答案，应该是可以做到$O(n^2\log n)$的，不过这题的数据范围显然没必要，Hard Version可能需要吧。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 205
#define int long long 
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,k,f[N][N],a[N];
signed main()
{
	memset(f,-0x3f,sizeof(f));
	n=read();k=read();m=read();
	f[0][0]=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=min(i,m);j++)
		{
			for(int lst=max(0ll,i-k);lst<i;lst++)
			{
				if(f[lst][j-1]==-1)continue;
				f[i][j]=max(f[i][j],f[lst][j-1]+a[i]);
				//cout<<i<<" "<<j<<" "<<f[i][j]<<" "<<lst<<" "<<j-1<<" "<<f[lst][j-1]<<" "<<f[lst][j-1]+a[i]<<endl;
			}
		}
	}
	int ans=-1;
	for(int i=n-k+1;i<=n;i++)ans=max(ans,f[i][m]);
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=0;j<=m;j++)
//		{
//			printf("%lld ",f[i][j]);
//		}
//		puts("");
//	}
	printf("%lld\n",ans);
}

```



---

## 作者：chufuzhe (赞：0)

考虑 $dp$ 。

设 $dp[i][j]$ 表示前 $i$ 个数中选择 $j$ 个数的最大和，且选了 $a_i$。

可以枚举一个数 $i2$，表示上一个取的是 $a_{i2}$ ， $i2$ 要满足 $i-k<=i2<i$，且 $i2$ 为非负整数。

那这样的和就是 $dp[i2][j - 1] + a_i$ 。

所以 $dp[i][j] = max(dp[i2][j - 1] + a_i)$

### 十年 $OI$ 一场空，不开 $long$ $long$ 见祖宗

代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[205], dp[205][205];
signed main() {
    int n, k, x;
    cin >> n >> k >> x; //输入
    for(int i = 1; i <= n; i++){
    	cin >> a[i];
    }
    for(int i = 0; i <= n; i++){ //初始化
	    for(int j = 0; j <= n; j++){
		    dp[i][j] = -1e16;
	    }
    }
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++){
    	int i2;
    	if(i < k) i2 = 0; //i2是非负的
    	else i2 = i - k; //保证连续的k个元素都至少有一个被选中
        for(; i2 < i; i2++){ //枚举上一个取的数的坐标
            for(int j = 1; j <= x; j++){
                dp[i][j] = max(dp[i][j], dp[i2][j - 1] + a[i]); //计算dp[i][j]
            }
        }
    }
    int ans = -1; //当最大和为负数时，输出-1
    for(int i = 0; i < k; i++)
		ans = max(ans, dp[n - i][x]);
    cout << ans << endl; //输出
    return 0;
}
```


---

