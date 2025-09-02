# [AGC004B] Colorful Slimes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc004/tasks/agc004_b

高橋君は異世界に住んでいます。 この世界には $ N $ 色のスライムがいます。 最初、高橋君はどの色のスライムも飼っていません。 高橋君の目標は、全色のスライムを一緒に飼うことです。

高橋君は次の $ 2 $ 種類の操作を行えます。

- 今飼っていないスライムの色 $ i $ ($ 1\ <\ =i\ <\ =N $) をひとつ選ぶ。 色 $ i $ のスライムを捕まえて飼う。 この操作には $ a_i $ 秒掛かる。
- 魔法を唱える。 すると、今飼っている各スライムについて、色 $ i $ ($ 1\ <\ =i\ <\ =N-1 $) のスライムは色 $ i+1 $ へ変色する。 ただし、色 $ N $ のスライムは色 $ 1 $ へ変色する。 この操作には $ x $ 秒掛かる。

高橋君が全色のスライムを一緒に飼うためには、最短で合計何秒掛かるかを求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =N\ <\ =2,000 $
- $ a_i $ は整数である。
- $ 1\ <\ =a_i\ <\ =10^9 $
- $ x $ は整数である。
- $ 1\ <\ =x\ <\ =10^9 $

### Sample Explanation 1

次のように操作を行えばよいです。 - 色 $ 1 $ のスライムを捕まえて飼う。 $ 1 $ 秒掛かる。 - 魔法を唱える。 スライムの色が $ 1 $ → $ 2 $ と変わる。 $ 10 $ 秒掛かる。 - 色 $ 1 $ のスライムを捕まえて飼う。 $ 1 $ 秒掛かる。

### Sample Explanation 2

次のように操作を行えばよいです。 - 色 $ 2 $ のスライムを捕まえて飼う。 $ 1 $ 秒掛かる。 - 魔法を唱える。 スライムの色が $ 2 $ → $ 3 $ と変わる。 $ 10 $ 秒掛かる。 - 色 $ 2 $ のスライムを捕まえて飼う。 $ 1 $ 秒掛かる。 - 魔法を唱える。 スライムの色が $ 3 $ → $ 1 $，$ 2 $ → $ 3 $ とそれぞれ変わる。 $ 10 $ 秒掛かる。 - 色 $ 2 $ のスライムを捕まえて飼う。 $ 1 $ 秒掛かる。

### Sample Explanation 3

次のように操作を行えばよいです。 - 色 $ 1 $ のスライムを捕まえて飼う。 $ 1 $ 秒掛かる。 - 色 $ 2 $ のスライムを捕まえて飼う。 $ 2 $ 秒掛かる。 - 色 $ 3 $ のスライムを捕まえて飼う。 $ 3 $ 秒掛かる。 - 色 $ 4 $ のスライムを捕まえて飼う。 $ 4 $ 秒掛かる。

## 样例 #1

### 输入

```
2 10
1 100```

### 输出

```
12```

## 样例 #2

### 输入

```
3 10
100 1 100```

### 输出

```
23```

## 样例 #3

### 输入

```
4 10
1 2 3 4```

### 输出

```
10```

# 题解

## 作者：LCuter (赞：6)

首先有特别显然的结论。

每个所罗门一定都是从另一个所罗门变过来的。

设 $p(x)$ 表示第 $x$ 个所罗门是从第 $p(x)$ 个所罗门变过来的，$d(i)=p(i)-i+[p(i)<i]n$，换句话说，它是环上 $i$ 到 $p(i)$ 的**顺时针**距离。

那么对于一个 $p$，它的花费是：
$$
x\max_{i}d(i)+\sum_{i}a_{p(i)}
$$
构造很简单，将所有元素按照 $d$ 降序排列，然后依次执行对应的抓捕操作，接着执行对应次数的魔法操作即可。

这时就有个简单的做法，枚举 $\max_i d(i)$，那么 $x\max_i d(i)$ 就是定值，那我们知道对于 $p(i)$ 我们只需选择在范围内且 $a$ 最小的下标。

在原题的数据范围内，直接预处理所有区间的最小值就可以做到 $O(n^2)$。

记 $D=\max_i d(i),S(D)=\sum_{i}a_{p(i)}$。

转换一下思路，设 $c(i)$ 表示在某个 $D$ 下，$i$ 作为 $p(j)$ 出现的次数，也即 $\#\{p(j)=i\}$，考虑怎么维护 $c(i)$ 的变化。

我们知道当 $D=0$ 时，所有 $c$ 都为 $1$。

我们发现，以 $D$ 为横坐标时，$c$ 在一般情况下是先增长，再不变，最后减少的样子（也有可能缺失某一部分）。

增长的话，意味着它向前扩张时没被后面的扩张。

不变的话有两种可能，一种是向前扩张时遇到一个更小的值，并且后面没有把自己扩掉，一种是向前扩张了，但是也被后面的扩张了。

减少的话，意味着没有向前扩张，但是被后面的值扩张了。

如果能预处理出 $c$，就能通过二次差分计算出 $S(D),D=0,1,\cdots,n-1$，现在问题转为对于每一个元素，计算它的 $c$ 函数，我们知道只需求出它的至多的两个拐点。

那我们直接使用单调栈预处理前后比它小的元素，就可以得出 $c$。对于相等的元素，给它定个序就好了。

声明：由于细节过多，仅实现了 $O(n^2)$ 的做法。

时间复杂度 $O(n)$。

---

## 作者：Goodenough (赞：6)

看到题解这么少，我来水一波。\
~~实际上这是我们校内比赛赛题~~  我也是受了positive1巨佬的启发\
就是用一个dp，dp[i][j]表示第i个点使用j及以下次魔法能达到的价格最小的那个点\
注意long long
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const long long inf=0x3f3f3f3f3f3f3f3f;
long long n,x,a[2005],dp[2005][2005],sum,ans=inf;
int main(){
	scanf("%lld%lld",&n,&x);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
	    dp[i][0]=a[i];
	    for(int j=1;j<n;j++){
	    	int k=i-j;
	    	if(k<=0) k+=n;
	        dp[i][j]=min(dp[i][j-1],a[k]);
	    }
	}
	for(int i=0;i<n;i++){
	    sum=x*i;
	    for(int j=1;j<=n;j++)
	        sum+=dp[j][i];
	    ans=min(ans,sum);
	}
	printf("%lld",ans);
	return 0;
}
```
这就好了，想清楚了dp的内涵就没什么问题

---

## 作者：Autream (赞：4)

#### 题意简述
有 $N$ 种颜色的史莱姆，捕获第 $i$ 只需要 $a_i$ 的能量，或者使用 $x$ 的能量把当前所捕获的史莱姆的颜色编号都 $+1$。
 
---
#### 题目分析
首先观察数据范围：$N \leq 2000$，可以支持 $O(N^2)$ 的算法，这里我们考虑使用 DP。  
设 $dp_{i,j}$ 表示获得第 $i$ 种颜色，使用 $j$ 次魔法的最小代价。  
状态转移方程：$dp_{i,j}=\min(dp_{i,j-1},a_t)$，其中 $t=(i-j+n)\%n$。  
答案 $ans=\min\{k \times\ x+\sum^n_{i=1}dp_{i,k}\}$。

---
#### 问题优化
因为 $dp_{i,j}$ 只与 $dp_{i,j-1}$ 有关，所以我们可以考虑优化一维，设 $dp_i$ 表示获得第 $i$ 种颜色的最小代价。  
所以优化后的状态转移方程：$dp_i=\min(dp_i,a_t)$。
初始状态：$dp_i=a_i$。  
答案在每次循环里面统计就行。

---
#### AC Code
```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::cin>>a[i]
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
CI N=2005;
int n,x,ans=LLONG_MAX,a[N],dp[N];
signed main() {
    std::cin>>n>>x;
    rep(i,0,n-1){
        std::cin>>a[i];
        dp[i]=a[i];
    }
    rep(j,0,n-1){//压维
        int s=0;
        rep(i,0,n-1){
            dp[i]=std::min(dp[i],a[(i-j+n)%n]);
            s+=dp[i];
        }
        ans=std::min(ans,x*j+s);//统计答案
    }
    std::cout<<ans;
    return 0;
}
```

---

## 作者：ningago (赞：2)

容易想到总变换次数一定小于 $n$，因为你可以在任意的一次变换之前插入“买”的操作。

令 $dp_{i,j}$ 表示通过 $j$ 次变换凑出颜色 $i$ 的最小代价（这里的代价指买史莱姆的代价，不包括变换的，因为两只史莱姆同时变换一次只需要一份钱，单独计算）。

转移很自然： $dp_{i,j}=\min\{dp_{last,j-1},a_i\}$。

$last$ 指环上的前驱，也就是 $i-1$，对于 $1$ 来说 $last=n$。

答案就是 $\min_{j=0}^{n-1}\{j\cdot x+\sum_{i=1}^n dp_{i,j}\}$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 2010
#define int long long

int n,X;
int dp[N][N],a[N];
int res = 0x3f3f3f3f3f3f3f3f;

signed main()
{
	scanf("%lld%lld",&n,&X);
	for(int i = 1;i <= n;i++)
	{
		scanf("%lld",&a[i]);
		dp[i][0] = a[i];
	}
	for(int j = 1;j < n;j++)
	{
		for(int i = 1;i <= n;i++)
		{
			int last = i - 1 == 0 ? n : i - 1;
			dp[i][j] = std::min(dp[last][j - 1],a[i]);
		}
	}
	for(int j = 0;j < n;j++)
	{
		int now = j * X;
		for(int i = 1;i <= n;i++)
			now += dp[i][j];
		res = std::min(now,res);
	}
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：Electrified (赞：2)

本人第二篇题解~~貌似也是这题第一篇题解~~请各位大佬多多指教。

这题原来是我们学校对新生的一次考试的题目，然后给我们出题的学长就出了这题，结果那次考试绝大多数考生都是其他三题全对，这题做不出来（包括我）。于是老师讲完正解之后恍然大悟，拖了几个月打出了这篇题解。。。

据说这题可以用动态规划（然而我们老师还没教），但是我们老师想出来了一个用贪心做的方法————枚举进化次数。如何得到每一只史莱姆的最小价钱似乎很复杂，但进化次数是可以枚举的，进化的价钱也是确定的。这样，我们就可以贪心一下，开一个二维数组来记录某个区间中最便宜的史莱姆的价钱，区间的右边界就是进化的目标史莱姆，左边界就是目标史莱姆的等级减去进化次数的史莱姆，然后将这些都加起来，再加上进化所需价钱，枚举一下，取最小值就可以了。注意开long long。

代码如下

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll a[2005],b[2005][2005],n,x,ans=9e18;
int main()
{
	scanf("%lld%lld",&n,&x);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		b[i][i]=a[i];
		for(int j=i+1;j<=n;j++)
		{
			b[i][j]=min(b[i][j-1],a[j]);
		}
	}
	for(ll i=0;i<n;i++)
	{
		ll temp=i*x;
		for(ll j=1;j<=n;j++)
		{
			int k=j-i;
			if(k<=0)
            {
            	temp+=min(b[k+n][n],b[1][j]);
            }
			else temp+=b[k][j];
		}
		ans=min(ans,temp);
	}
	printf("%lld",ans);
	return 0;
}
```

还是一道很巧的贪心题的。

---

## 作者：Zhddd_ (赞：1)

首先，可以发现一个性质，假设对于第 $i$ 个史莱姆，得到它需要施展 $k_i$ 次魔法，那么一定可以构造一种方式，使得总施展魔法次数恰好等于 $\max_{i=1}^{n}(k_i)$ 次。

又因为得到一个史莱姆，肯定不需要施展大于等于 $n$ 次魔法，所以总施展魔法次数在 $[0,n-1]$ 这个区间内。

所以，可以枚举总施法次数，若当前枚举到 $k$，则对于第 $i$ 个史莱姆，用 ST 表来查询第 $i+1$ 个史莱姆到第 $i+k$ 个史莱姆中直接抓的代价最小值（这里要把史莱姆序列头尾相接），与直接抓第 $i$ 只的代价对比。最后总代价加上这 $k$ 次施法的代价就行了。

时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 4e3 + 10;
const LL INF = 1e15;
LL n, x, res = INF, a[N], mn[N][13];
LL getMin(int l, int r) {
	if (l > r) return INF;
	int k = log2(r - l + 1);
	return min(mn[l][k], mn[r - (1 << k) + 1][k]);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> x;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) a[i + n] = a[i]; // 头尾相接。
	for (int i = 1; i <= 2 * n; i++) mn[i][0] = a[i];
	for (int j = 1; j < 12; j++) {
		for (int i = 1; i <= 2 * n; i++) {
			if (i + (1 << j) - 1 <= 2 * n) mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
		}
	} 
	for (int k = 0; k < n; k++) {
		LL sum = k * x;
		for (int i = 1; i <= n; i++) {
			sum += min(a[i], getMin(i + 1, i + k));
		}
		res = min(sum, res);
	}
	cout << res;
	return 0;
}
```

---

## 作者：Chillturtle (赞：1)

# 题意

- 首先有 $ N $ 个史莱姆，它们有不同的颜色，我们需要进行若干次操作后，需要得到一个能够包含所有颜色的花费。

- 求这个花费的最小值。

# 思路

因为 $N \le 2000$，所以根本用不着各种高大上的数据结构，直接枚举当前应该转哪一位，如果使用魔法，花费是否比原来大就可以了。

## 特别地

在循环的时候特别注意 $i$ 与 $j$ 的位置，如果 $i$（当前应转位）比 $j$ 大，那么使用魔法次数应为 $n-i+j$，否则应为 $j-i$。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10;
int a[N],n,b[N],x;
signed main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	memset(b,0x7f,sizeof(b));
	int minn=LLONG_MAX;
	for(int i=0;i<=n;i++){
		int sum=0;
		for(int j=1;j<=n;j++){
			int opt;
			if(j<=i){
				opt=n-(i-j);
			}else{
				opt=j-i;
			}
			b[j]=min(b[j],a[opt]);
			sum+=b[j];
		}
		minn=min(minn,sum+i*x);
	}
	cout<<minn<<endl;
return 0;
}
```

---

## 作者：wth2026 (赞：0)

# 题目思路
用动态规划可以轻松解决。

首先用 $f_{i,j}$ 表示选到第 $i$ 个点，最多用了 $j$ 次魔法的最小代价，就可以推出动转方程： 
$$
f_{i,j}=\min(f_{i,j-1},a_{((i-j+n-1)\mod n) +1})
$$
其中的 $((i-j+n-1)\mod n)+1$ 表示的是：
$$
\begin{cases}
  i-j & i>j\\
  i-j+n & i\leq j
\end{cases}
$$
# AC Code
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f

//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Os")
//#pragma GCC optimize("Ofast")
//
using namespace std;

//#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1 ++)
//char *p1, *p2, buf[1 << 20 + 5];
//
//inline int read() {
//	int x = 0;
//	char c = gc();
//	
//	while (!isdigit(c)) {
//		c = gc();
//	}
//	
//	while (isdigit(c)) {
//		x = (x << 3) + (x << 1) + (c ^ 48);
//		c = gc();
//	}
//	
//	return x;
//}
//
//void print(int k) {
//	if (k > 9) {
//		print(k / 10);
//	}
//	
//	putchar(k % 10 + 48);
//}
//
const int N = 2000;
int n, x, a[N + 5], f[N + 5][N + 5], sum, ans = inf;

void init() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}

signed main() {
	init();
	cin >> n >> x;
	
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	
	for (int i = 1; i <= n; ++ i) {
		f[i][0] = a[i];
		
		for (int j = 1; j < n; ++ j) {
			f[i][j] = min(f[i][j - 1], a[(i - j + n - 1) % n + 1]);
		}
	}
	
	for (int i = 0; i < n; ++ i) {
		sum = x * i;
		
		for (int j = 1; j <= n; ++ j) {
			sum += f[j][i];
		}
		
		ans = min(ans, sum);
	}
	
	cout << ans;
	return 0;
}
```

---

## 作者：Dengkaizhong (赞：0)

[题目传送](https://www.luogu.com.cn/problem/AT_agc004_b)
### 题意描述
有 $N$ 个颜色的史莱姆，直接得到 $TA$，要花费 $a_i$ 秒钟时间。

也可以通过花费 $x$ 秒钟使颜色为 $i$ 的史莱姆变成颜色为 $i+1$ 的史莱姆（特殊的：颜色为 $N$ 的史莱姆会变成颜色为 $1$ 的史莱姆。
### 做题过程
首先尝试暴搜每个点的最小（我太蒟了，没做出来)。

再次尝试往后搜最小（$A$ 了）。
### 做法分析
先考虑到运用第 $2$ 种操作是对全员的，枚举做了 $i$ 次第 $2$ 种操作，因为整体是个环，所以 $0<i<n$，再找从第 $j$ 个点后 $i$ 个点中最小的一个，整体相加，再加上第 $2$ 种操作的耗费即 $i \times x$ 再取整体最小即可。

注意：

因为 $2 \le N \le 2000$ 所以只能用 $O(N^2)$，考虑优化，记忆每个第 $j$ 个点后 $i-1$ 个点中最小的一个。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
//要用long long !!!

int n;
int x;
int ls[2005];
int mi[2005];//每个第j个点后i-1个点中最小的一个
int ans;

signed main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
		cin>>ls[i];
		mi[i]=ls[i];//初始化
		ans+=ls[i];
	}
	for(int i=1;i<n;i++)//枚举向后找的距离
	{
		int temp=0;
		for(int j=1;j<=n;j++)
		{
			mi[j]=min(mi[j],ls[(j-i>0?j-i:j-i+n)]);//在这里我懒得破环成链，直接用的三目
			temp+=mi[j];
		}
		ans=min(ans,temp+i*x);
	}
	cout<<ans;
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/153353178)
### 完成！

---

## 作者：max666dong123 (赞：0)

# 题意
现在有一群史莱姆，它们有 $N$ 种颜色，每种颜色的史莱姆有无数只。现在你需要搜集齐 $N$ 种颜色，但是只能够使用下面的方法：

1. 选择颜色 $i$，然后花费 $a_i$ 的代价抓一只颜色为 $i$ 的史莱姆。
2. 让已经抓到的所有的史莱姆的颜色都从 $i$ 变为 $i+1$，代价是 $x$（颜色为 $N$ 的史莱姆的颜色变为 $1$）。

现在要求你以最小的代价搜集齐 $N$ 种颜色，输出最小代价。
# 思路
考虑贪心。

我们可以将每种方案转成这个样子：有 $n$ 个底座，每个底座上有一些史莱姆。每次可以将每个底座最底下的史莱姆移到右边的一个柱子，当每个底座上都有史莱姆的时候，统计结果。就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/4oqy5ds6.png)

正着想这个问题，的确不好做。但是，我们可以反着想。
![](https://cdn.luogu.com.cn/upload/image_hosting/wachzlbs.png)

我们可以让史莱姆选择放在那个底座，使花费最小。
# 实现方法
先将枚举每个史莱姆跳的次数 $k\le n$，$minn_i$ 表示的是在当前能到的最小的底座。每次的答案：$\sum^{n}_{i=1}min_i+i \times x$。

最后的答案就是它们的最小值了。
# AC code
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e3+10;
int a[N];
int n,x;
int minn[N];
int calc(int x){
	if(x<=0){
		return x+n;
	}
	if(x>n){
		return x-n;
	}
	return x;
}
signed main(){
	memset(minn,0x5f,sizeof(minn));
	cin>>n>>x;
	int ans=LONG_LONG_MAX;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=0;i<=n;i++){
		int res=0;
		for(int j=1;j<=n;j++){
			minn[j]=min(minn[j],a[calc(j-i)]);
			res=res+minn[j];
		} 
//		cout<<res<<" ";
		ans=min(ans,res+i*x);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：nxd_oxm (赞：0)

# 题意
我们有 $n$ 种颜色的史莱姆，我们想要所有颜色的。

我们有 $2$ 种方法：

- 花费 $a_i$ 的代价抓一只 $i$ 颜色的史莱姆。

- 把所有抓到的所有史莱姆的颜色都从 $i$ 变成 $i+1$，颜色 $n$ 变为 $1$。

# 思路
好，我们看到这个数据范围，$n \le 2000$！好，dp 启动！

其实不用这么麻烦，考虑贪心即可。

正难则反，我们可以把问题转换成，我们有 $n$ 种颜色的史莱姆每种一个，每次移动将球向左移，求在哪种状态下花费最少。

我们枚举一共的移动次数 $y$。

那么对于第 $i$ 个史莱姆，我们可以通过第 $(i-y) \sim i$ 位置来转移，相当于，从第 $j$ 位置上转移来的，就是在第 $j-i+y+1$ 次移动前在第 $j$ 个位置上抓了一只史莱姆，那在第 $y$ 次移动后，第 $i$ 个位置上就有史莱姆了。

对于每一个位置，我们新算的能转移的就是 $a_{i-y}$ 的代价，而我们也可以用原来的。拿个数组存一下 $i$ 位置上的曾经的值，而这个值的意义就是在 $y$ 次跳动内能使第 $i$ 个位置上有史莱姆的最小代价，转移 $O(n)$。

而对于每次枚举的 $y$，我们把所有位置上的最小代价加起来，再加上 $y$ 次移动的最小代价即 $y \times x$。

从 $0$ 到 $n$ 枚举跳动次数 $y$，取最小值，输出即可。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int a[2010];
int b[2010];
int n,x;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>x;
	memset(b,0x7f,sizeof b);
	f(i,1,n){
		cin>>a[i];
	}
	int sum=LLONG_MAX;
	f(i,0,n){
		int minn=0;
		f(j,1,n){
			int jl=(j-i<=0?j-i+n:j-i);
//			cout<<i<<"-->"<<j<<" "<<jl<<" "<<jl*x+a[j]<<endl;
			b[j]=min(b[j],a[jl]); 
			minn+=b[j];
		}
		sum=min(sum,minn+i*x);
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：FBW2010 (赞：0)

# 题意

[传送门](https://www.luogu.com.cn/problem/AT_agc004_b)

有 $N$ 个数，每次你可以花 $a_i$ 的代价将第 $i$ 个数加一，或者是花 $x$ 的代价把所有的数右移一位（最右边的数移到第一个），求使所有数大于零的最小代价。

# 思路

首先，我们会发现每一个地方只能由他自己提供或从其他地方一直移过来。而由于是所有数同时移动，我们就没必要单独移动某一个值，只需要找到移动次数最多的即可。因此，我们可以设 $i$ 为最多移动次数，枚举每一个 $i$，每个数的最小代价就应该是他前 $i$ 个数中的最小值，即第 $j$ 个数变为一的最小代价就是 $\min(a_{j-k})(0 \le k < i)$。接着把每个数的代价累加，再加上移动的代价，最后求最小值即可。

对于维护最小值，我们可以使用**单调队列**，即可做到 $O(n^2)$ 的复杂度。具体详见[滑动窗口](https://www.luogu.com.cn/problem/P1886)。

但因为最后一个数会移到第一个，也就是说所有数相当于一个**环**，此时我们需要**破环为链**，再保存每个位置代价的前缀和，最后将每一个长度为 $n$ 的链的代价求最小值即可。

~~最后记得不开 long long 见祖宗！~~

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,ans=1e18,a[4005],sum[4005]/*维护节点代价的前缀和*/;
struct node{
	long long x,id; //单调队列的结构体 
};
int main(){
	scanf("%lld %lld",&n,&x);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		a[i+n]=a[i]; //破环为链 
	}
	for(int i=1;i<2*n;i++){
		deque<node> q; //单调队列 
		for(int j=1;j<2*n;j++){
			//单调队列基操 
			while(!q.empty()&&q.back().x>=a[j]){ 
				q.pop_back();
			}
			q.push_back({a[j],j});
			while(!q.empty()&&j-q.front().id+1>i){
				q.pop_front();
			}
			sum[j]=sum[j-1]+q.front().x; //计算前缀和 
		}
		for(int j=1;j<=n;j++){
			ans=min(ans,sum[n+j-1]-sum[j-1]+(i-1)*x); //枚举答案 
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：qiuzijin2026 (赞：0)

# [AGC004B] Colorful Slimes

[题面](https://www.luogu.com.cn/problem/AT_agc004_b)

## 思路

因为这道题是环，所以先破环成链。

显然使用魔法的次数一定小于 $n$，如果固定了施展魔法的次数为 $i$，那么抓第 $j$ 种史莱姆的最小代价就是：

$$
\min_{k=0}^{i}\{ a_{j-k}\}
$$

于是我们就可以枚举 $i$，然后用 `rmq` 或滑动窗口维护区间最小值累加到答案里，加上施展 $i$ 次魔法的代价，最后取最小值即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
long long x;
long long a[4005];
long long rmq[4005][25];
long long cnt;
long long ans=LONG_LONG_MAX;
long long cx(long long l,long long r){
	long long k=log(r-l+1)/log(2);
	return min(rmq[l][k],rmq[r-(1<<k)+1][k]);
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%lld%lld",&n,&x);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		a[n+i]=a[i];
		rmq[i][0]=a[i];
		rmq[i+n][0]=a[i+n];
	}
	long long k=log(2*n)/log(2);
	for(int i=1;i<=k;i++)
		for(int j=1;j<=2*n-(1<<i)+1;j++)
			rmq[j][i]=min(rmq[j][i-1],rmq[j+(1<<(i-1))][i-1]);
	for(long long i=0;i<n;i++){
		cnt=0;
		for(long long j=1;j<=n;j++) cnt+=cx(j+n-i,j+n);
		ans=min(ans,cnt+i*x);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：run_away (赞：0)

## 题意

很简单，不多说了，直接看分析。

## 分析

可以发现，直接捕捉第 $i$ 只 slime 就相当于用 0 次魔法，而用魔法的次数肯定小于 $n$。

因为 $n\le 2000$，所以可以预处理出 $f_{i,j}$ 表示捕捉到第 $i$ 个 slime 用 $j$ 次魔法所花费的最小代价。

设第 $i$ 位之前的那个 slime 编号为 $lst$，所以状态转移方程为 $f_{i,j} = \min(f_{i,j-1},a_{lst})$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
ll n,x,a[2005],f[2005][2005],sum,ans=LONG_LONG_MAX;
signed main(){
    n=read(),x=read();
    for(ll i=1;i<=n;++i)a[i]=read();
    for(ll i=1;i<=n;++i){
        f[i][0]=a[i];
        for(ll j=1;j<n;++j){
            ll lst=i>j?i-j:n+i-j;
            f[i][j]=min(f[i][j-1],a[lst]);
        }
    }
    for(ll i=0;i<n;++i){
        sum=x*i;
        for(ll j=1;j<=n;++j){
            sum+=f[j][i];
        }
        ans=min(ans,sum);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

把直接抓 $i$ 号史莱姆看作抓了第 $i$ 号史莱姆之后，施展了 $0$ 次魔法。那么所有史莱姆都可视为抓了某种史莱姆之后，施展若干次魔法得到的。

假设对于第 $i$ 个史莱姆，它是抓了第 $\left ( i-k_i \right )$ 号史莱姆后，施展 $k_i$ 次魔法得到的。那么一定可以构造方案，使得施展魔法的总次数为 $\max \left \{ k_i \right \}$。


假设有 $5$ 种颜色，魔法代价为 $10$，捕捉代价为 $ \left \{ 1,100,1,100,100 \right \}$。

那么每种史莱姆分别需要魔法 $ \left \{ 0,1,0,1,2 \right \}$ 次。

即先抓 $3$ 号史莱姆、施展魔法 $ \left \{ 4 \right \}$、抓 $1$ 号史莱姆、抓 $3$ 号史莱姆、施展魔法 $ \left \{ 2,4,5 \right \}$、抓 $1$ 号史莱姆、抓 $3$ 号史莱姆。

又因为施展 $N$ 次魔法后，一个史莱姆的颜色将变回原样，因此肯定不需要施展 $\left ( \geqslant N \right )$ 次魔法，所以总魔法次数小于 $N$。

综上，可以枚举总魔法次数 $K$，对于第 $i$ 个史莱姆，其代价为从第 $\left ( i-K \right )$ 到第 $i$ 号中直接抓某个史莱姆的最小代价，区间最小值问题可用 $\operatorname{ST}$ 表等方法维护。最后再加上 $k$ 次魔法的总代价即可。

复杂度：$O \left ( n^2 \right )$。

### AC code
```cpp
#include <bits/stdc++.h>
#define llm LONG_LONG_MAX
using namespace std;
long long a[2005],st[2005][15],x,minn=llm,ans;
int s[2005],n,m;
void check(){
	s[0]=-1;
	for(int i=1;i<=2000;i++){
		s[i]=s[i/2]+1;
	}
	memset(st,0x3f3f,sizeof(st));
	for(int i=1;i<=n;i++){
		cin>>a[i];
		st[i][0]=a[i];
	}
	int k=s[n];
	for(int j=1;j<=k;j++){
		for(int i=1;i+(1<<j)<=n+1;i++){
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}
int pri(int x,int y){
	int k=s[y-x+1];
	return min(st[x][k],st[y-(1<<k)+1][k]);
}
int main(){
	scanf("%d%lld",&n,&x);
	check();
	for(int k=0;k<n;k++){
		ans=0;
		for(int i=1;i<=k;i++){
			ans+=min(pri(1,i),pri(i+n-k,n));
		}
		for(int i=k+1;i<=n;i++){
			ans+=pri(i-k,i);
		}
		minn=min(minn,ans+k*x);
	}
	printf("%lld\n",minn);
	return 0;
}
```


---

## 作者：lijunxi1 (赞：0)

对于此题，我们不难想到对于每个点，不考虑其他时，答案为 $ans_i=\left \{ ^{x\times(i-j)+a_j(i>j)}_{x\times(n+i-j)+a_j(i<j)} \right \} $。

如何会发现移动步骤可以重合，故枚举移动次数。

令 $f(x,y)$ 为 $x$ 前 $y$ 位中，的 $a$ 的最小值：

令移动次数为 $c$，则答案为 $\sum^{i=1}_{i\le n}ans_i=c\times x+f(i,c)$。

枚举 $c$ 再暴力求才 $n^2$，而 $n\le2000$，故完结：

这里提供线段树和暴力预处理两种方法：

 线段树：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,a[2005],ans=1e18,z,xds[8005];
long long js(int l,int r,int w)
{
    if(l==r)return xds[w]=a[l];
    long long zj=(l+r)/2;
    return xds[w]=min(js(l,zj,w*2),js(zj+1,r,w*2+1));
}
long long qz(int l,int r,int cl,int cr,int w)
{
    if(cl<=l&&r<=cr)return xds[w];
    long long zj=(l+r)/2,re=1e18;
    if(zj>=cl)re=min(re,qz(l,zj,cl,cr,w*2));
    if(zj<cr)re=min(re,qz(zj+1,r,cl,cr,w*2+1));
    return re;
}
long long q(long d,long long fw)
{
    if(fw<d)return qz(1,n,d-fw,d,1);
    return min(qz(1,n,1,d,1),qz(1,n,n+d-fw,n,1));
}
int main ()
{
   
    scanf("%lld%lld",&n,&x);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    js(1,n,1);
    for(int i=0;i<=n;i++)
    {
        z=i*x;
        for(int j=1;j<=n;j++)z+=q(j,i);
        ans=min(ans,z);
    }
    printf("%lld",ans);
}
```

暴力：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,minz[2005][2005],a[2005];
long long ans=1e18,z;
int q(int d,int fw)
{
    return d>fw?minz[d-fw][d]:(minz[1][d]<minz[n+d-fw][n]?minz[1][d]:minz[n+d-fw][n]);
}
int main ()
{
  
    scanf("%d%d",&n,&x);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        minz[i][i]=a[i];
        for(int j=i+1;j<=n;j++)minz[i][j]=(minz[i][j-1]>a[j]?a[j]:minz[i][j-1]);
    }
    for(int i=0;i<=n;i++)
    {
        z=1ll*i*x;
        for(int j=1;j<=n;j++)z+=1ll*q(j,i);
        ans=min(ans,z);
    }
    printf("%lld",ans);
}
```

---

