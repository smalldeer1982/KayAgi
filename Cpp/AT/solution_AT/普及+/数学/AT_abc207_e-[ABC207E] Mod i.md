# [ABC207E] Mod i

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc207/tasks/abc207_e

長さ $ N $ の数列 $ A $ が与えられます。$ A $ をいくつかの連続した空でない部分列 $ B_1,B_2,\ldots,B_k $ に切り分ける方法であって、以下の条件を満たすものの個数を求めてください。

- 全ての $ i\ (1\ \leq\ i\ \leq\ k) $ について、$ B_i $ に含まれる要素の総和が $ i $ で割り切れる。

答えは非常に大きくなることがあるので、$ (10^9+7) $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ A_i\ \leq\ 10^{15} $
- 入力は全て整数

### Sample Explanation 1

以下の $ 3 $ 通りの切り分け方があります。 - $ (1),(2),(3),(4) $ - $ (1,2,3),(4) $ - $ (1,2,3,4) $

### Sample Explanation 3

入力が $ 32 $ bit 整数型に収まりきらない場合があります。

## 样例 #1

### 输入

```
4
1 2 3 4```

### 输出

```
3```

## 样例 #2

### 输入

```
5
8 6 3 3 3```

### 输出

```
5```

## 样例 #3

### 输入

```
10
791754273866483 706434917156797 714489398264550 918142301070506 559125109706263 694445720452148 648739025948445 869006293795825 718343486637033 934236559762733```

### 输出

```
15```

# 题解

## 作者：COsm0s (赞：4)

## $\mathcal{Solution}$

考虑 DP。

+ 先考虑朴素 DP。

  设 $f_{i,j}$ 为 前 $i$ 个数分成 $j$ 段的方案数。
	
  很容易得出以下转移方程：
  
  $f_{i,j} = \sum\limits_{k=j-1}^{i-1} f_{k,j-1}(\sum\limits_{l=k+1}^i a_i\mod j=0)$
  
  复杂度 $\Theta{(n^3)}$。
  
  对于本题 $n \leq 3000$ 的数据下，显然超时。
  
+ 考虑对此方程进行优化。

   进行前缀和优化。
  
  设 $sum_i = \sum\limits_{k=1}^{i} a_i$。
        
   则 $\sum\limits_{l=k+1}^i a_i\mod j=0$ 一式可以转变为 $sum_i \equiv sum_{k}( \bmod \ j)$
   
+ 设 $g_{k,j}$ 为当 $sum_i \bmod  j=k$ 时，分成 $j$ 段的方案数。

  则原式转化为 $f_{i,j}=g_{sum_i\bmod j,j-1}$，$g_{sum_i\bmod j,j-1}$ 每次需要加上 $f_{i,j-1}$。
  
  注意先做 $f$ 数组，通过朴素 DP 式可知，$k\leq j-1$，则 $g$ 数组不需要当前的 $f$。
  
+ $g$ 数组边界为 $g_{0,0}=1$。最终的答案即为 $\sum\limits_{i=1}^n f_{n,i}$。

+ 最终复杂度 $\Theta{(n^2)}$。
        
## $\mathcal{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define up(a, b, c) for(register int a = b; a <= c; a ++)
#define down(a, b, c) for(register int a = b; i >= c; a --)
#define L first
#define R second
const int mod = 1e9 + 7;
const int N = 3e3 + 5;
inline int min(int x, int y) {
	return x < y ? x : y;
}
inline int max(int x, int y) {
	return x > y ? x : y;
}
inline int read() {
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x) {
	if(x < 0) {
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
int a[N], f[N][N], b[N], modsum[N][N];
signed main() {
	int n = read();
	up(i, 1, n) a[i] = read(), b[i] = b[i - 1] + a[i];
	modsum[0][0] = 1;
	up(j, 1, n)
	up(i, 1, n) {
		f[i][j] = modsum[b[i] % j][j - 1];
		modsum[b[i] % j][j - 1] += f[i][j - 1];
		modsum[b[i] % j][j - 1] %= mod;
	}
	int ans = 0;
	up(i, 1, n) ans = (ans + f[n][i]) % mod;
	write(ans);
	return 0;
}
```

  
  

---

## 作者：_Ponder_ (赞：4)

[Mod i](https://www.luogu.com.cn/problem/AT_abc207_e)

### 题目大意

给定一个序列 $a$，问将其划分成若干段，满足第 $i$ 段的和是 $i$ 的倍数的划分方案的个数。

### 思路分析

考虑 DP，设 $f_{i,j}$ 表示将序列中前 $i$ 个数划分成 $j$ 段，且满足条件的划分方案的个数，容易得出状态转移方程：

$$f_{i,j}=\sum f_{k,j-1}(\sum_{h=k+1}^i a_i\bmod j=0)$$

直接转移的复杂度是 $O(n^3)$ 的，无法接受，考虑优化。

设 $s_i$ 为 $a$ 的前 $i$ 项和，那么约束条件等价于 $(s_i-s_k) \bmod j=0$，当条件成立时有 $s_i\equiv s_k \pmod j$。

可以设 $g_{i,j}=\sum f_{k,i}(s_k\bmod (i+1)=j)$，那么容易发现 

$$g_{j-1,s_i\bmod j}=\sum f_{k,j-1}(s_k\bmod j=s_i\bmod j)= f_{i,j}$$

这样转移就优化到了 $O(n^2)$，这是因为 $g$ 可以在转移时累加，即 

$$g_{j,s_i\bmod (j+1)}=\sum f_{k,j}(s_k\bmod (j+1)=s_i\bmod(j+1))$$ 
其中包含 $f_{i,j}$。

### 代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N=3200,mod=1000000007;
#define int long long

int f[N][N],g[N][N];
int sum[N],a[N];
int ans,n;

signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        sum[i]=sum[i-1]+a[i];
    }
    f[0][0]=g[0][0]=1;//初始条件
    for(int i=1;i<=n;i++)
        for(int j=n;j>=1;j--){
            f[i][j]=g[j-1][sum[i]%j];
            g[j][sum[i]%(j+1)]=(g[j][sum[i]%(j+1)]+f[i][j])%mod;
        }
    for(int i=1;i<=n;i++) ans=(ans+f[n][i])%mod;//累加答案
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：菲斯斯夫斯基 (赞：4)

## AT_abc207_e [ABC207E] Mod i 题解

AtCoder 真的很会出 dp。

CSP 崩了，只好回来训练基础了。

**思路**

一眼 dp。很容易想到 $dp$ 数组的含义。定义 $dp_{i,j}$ 为前 $i$ 个数，分为 $j$ 段的合法方案数为多少。

先考虑朴素的 dp。显然，$dp_{i,1}$ 均为 $1$。对于 $j\ne1$ 的情况考虑怎样转移：多枚举一层 $k$，表示现在要将 $[k+1,i]$ 作为新的一段，若合法则为新的方案数。

动态转移方程：

$$dp_{i,j}=\sum\limits_{k=1}^{i-1}[j\mid(a_i-a_k)]dp_{k,j-1}$$

其中 $a_i$ 表示前缀和。

这样的复杂度是 $O(n^3)$ 的，无法通过本题。

考虑前缀和优化。

注意到要求某一段数的和模 $i$ 为 $0$，其实就是要求这两段的前缀和余数相同。

（设 $s_{i,j}$ 为 $[i,j]$ 的和，那么 $s_{i,j}\equiv 0\pmod k$ 就是 $s_{1,i-1} \equiv s_{1,j} \pmod k$）

想到这个就很简单了，$dp$ 数组含义不变。再定义一个 $sum_{i,j}$ 数组，意思为当前满足前缀和模 $i$ 为 $j$ 的合法方案数和。转移时一步转移即可：$dp_{i,j}=sum_{j,a[i]\%j}$。这里的 $\%$ 表示取余。

时间复杂度为 $O(n^2)$，可以通过本题。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3010,mod=1e9+7;
int n,ans;
int a[N],dp[N][N],sum[N][N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],a[i]+=a[i-1];//前缀和
	for(int i=1;i<=n;i++)
	{
		dp[i][1]=1;
		for(int j=2;j<=i;j++)
			dp[i][j]=sum[j][a[i]%j],dp[i][j]%=mod;
		for(int j=1;j<=n;j++)
			sum[j][a[i]%j]+=dp[i][j-1];//转移
	}
	for(int i=1;i<=n;i++)
		ans+=dp[n][i],ans%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：Melo_DDD (赞：1)

~~这个人直接想到了平方做法但是为了回归原始我们强行从立方做法开始搞。~~
## 题目大意
注意第 $i$ 段是 $i$ 的倍数。
## 题目实现
首先对于这种余数的问题，一般尝试去使用前缀和。

注意到 $\sum_{i=l}^{r}a_i\equiv0\pmod x\iff sum_r\equiv sum_{l-1}\pmod x$，其中 $sum$ 是前缀和数组，简而言之就是去寻找两个余数相同的前缀和，这样一减就消掉整除了。

好现在我们尝试退化，去想一个朴素的 $\mathcal {O}(n^3)$ 的做法。

很直观的，设 $dp_{i,j}$ 表示把前 $i$ 个数分成 $j$ 段且**符合条件**的方案数。

显然初始化 $dp_{i,1}=1$，下面设计状态转移方程，不难想到应该去枚举断点。
$$
dp_{i,j} = \sum_{k=1}^{i-1}[sum_i\equiv sum_k\pmod j]dp_{k,j-1}
$$
那么我们就设计出了一个复杂度爆炸的算法，下面尝试优化，我们会发现大部分时间浪费在了枚举 $k$ 上，而绝大多数的 $k$ 都是不合法的，相当于我们白做了很多事情，我们考虑反过来，就是计算每个 $k$ 时去计算它的贡献。

所以我们设计一个数组 $tot$，其中：
$$
tot_{i,j}=\sum_{k}^{}[sum_k\equiv j\pmod i]dp_{k,j-1}
$$
变成人话就是统计满足模 $i$ 等于 $j$ 的所有合法方案。

那么我们的状态转移方程变成了：
$$
dp_{i,j}=tot_{j,sum_i\bmod j}
$$
但是尽管这样仍然没有实质性的优化，我们考虑如何在不大于 $\mathcal {O}(n)$ 时间内求出 $tot$。

然后注意到（观察那个式子），对于当前的 $dp_{i,j}$，它只会影响到 $tot_{j+1,sum_k\bmod (j+1)}$。

代码：

```cpp
f (i ,1 ,n ,1) {
	int a ;
	read (a) ;
	sum += a ;
	dp[i][1] = 1 ;
	f (j ,2 ,i ,1) {
		dp[i][j] = tot[j][sum % j] % mod ;
	}
	f (j ,2 ,i + 1 ,1) {
		(tot[j][sum % j] += dp[i][j - 1]) %= mod ;
	}
} 
int ans = 0 ;
f (i ,1 ,n ,1) {
	(ans += dp[n][i]) %= mod ;
}
```

---

## 作者：__HHX__ (赞：1)

# 思路
我们很容易知道，我们在转移过程中只用关心 $(l, r, i, sum)$ 即左右端点和位于第 $i$ 段和 $sum$ 方案数。

我们很容易推出转移为 $(l, i, sum_{l, i}) \rightarrow (r, i + 1, sum_{r, i + 1} + sum_{l, i})$。

看下面的**关于证明**，我们可以知道若 $s_r \equiv s_{l - 1}\pmod i$ 则可以转移。

我们稍微变形下转移 $(r, i + 1, 0) \rightarrow (r, i + 1, \sum sum_{l, i})$，其中 $s_r \equiv s_{l - 1}\pmod i$ 且 $l < r$。

我们可以用 $p_k$ 来记录满足 $k = l \bmod i$ 的 $l$ 的 $\sum sum_{l,i}$。

那转移为 $(r, i + 1, 0) \rightarrow (r, i + 1, p_{r \bmod i})$，$p_{r \bmod i} \rightarrow p_{r \bmod i} + sum_{r, i}$。

先执行 $(r, i + 1, 0) \rightarrow (r, i + 1, p_{r \bmod i})$，因为在此时 $p_{r \bmod i}$ 正好等于 $\sum sum_{l,i}$。

# 关于证明
设：第 $i$ 段的左右端点为 $l, r$。

则 $i$ 满足 $i \mid \sum_{u = l} ^ r a_u$。

简化 $\sum_{u = l} ^ r a_u$ 得 $\sum_{u = 1} ^ r a_u - \sum_{u = 1} ^ r a_u$。

我们令 $s_k = \sum_{u = 1} ^ k a_u$。

则上式等于 $s_r - s_{l - 1}$。

则 $i$ 满足 $i \mid s_r - s_{l - 1}$。

我们令 $s_r = a_{l - 1} \cdot i + b_{l - 1}, s_{l - 1} = a_r \cdot i + b_r$，其中 $0 \leq b < i$。

则 $i$ 满足 $i \mid a_{l - 1} \cdot i + b_{l - 1} - a_r \cdot i - b_r$，即 $i \mid b_{l - 1} - b_r$。

因为 $0 \leq b < i$ 所以 $(b_{l - 1} - b_r) \in (-i, i)$。

其中仅 $b_{l - 1} - b_r = 0$ 满足 $i \mid b_{l - 1} - b_r$。

即 $b_{l - 1} = b_r$。

则 $i$ 满足 $s_r \equiv s_{l - 1}\pmod i$。

---

## 作者：yqr123YQR (赞：1)

### 题意
原题意挺简省的，不再复述。

### 分析
令 $dp_{i,j}$ 表示前 $i$ 位分成 $j$ 段，且每段均符合要求的方案数；令 $sum_i$ 表示前 $i$ 位的和。显然有如下转移方程：
$$
dp_{i,j}=\sum_{i'=0}^{i-1}dp_{i',j-1}[sum_i-sum_{i'}\equiv 0\pmod j]
$$
由此，$O(n^3)$ 的方法就出炉了。现在考虑优化。

注意到，式子里的 $sum_i-sum_{i'}\equiv 0\pmod j$ 即等价于 $sum_i\equiv sum_{i'}\pmod j$，所以可以另外引入 $g_{i,j}=\sum dp_{i',j-1}[s_{i'}\equiv j\pmod i]$，此时状态转移方程化为：
$$
\begin{matrix}
dp_{i,j}=g_{j,r} & (r=sum_i\bmod j)
\end{matrix}
$$
瓶颈即转到“如何快速维护 $g$”上。可以发现，求出 $dp_{i,j}$ 后，其只会对 $g_{j+1,i\bmod (j+1)}$ 有贡献，加上即可。

### 代码
```cpp
#include<stdio.h>
typedef long long ll;
const int maxn = 3000, bufsize = 220005, mod = 1e9 + 7;
char gtchar()
{
	static char buf[bufsize], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsize, stdin)) == buf? EOF: *p1++;
}
ll read()
{
	ll ret = 0;
	char ch = gtchar();
	while(ch < '0' || ch > '9') ch = gtchar();
	while(ch >= '0' && ch <= '9') ret = (ret << 3) + (ret << 1) + (ch ^ 48), ch = gtchar();
	return ret;
}
int n = read(), ans, sum[maxn + 5][maxn + 5]/*即文中的 g*/, dp[maxn + 5][maxn + 5];
ll s;
int Add(int a, int b) {return (a += b) >= mod? a -= mod: a;}
int main()
{
	sum[1][0] = 1;
	for(int i = 1; i <= n; i++)
	{
		s += read();//前缀和。由于 sum_i 对其他 i 的转移没有任何影响，用变量记录即可。
		for(int j = 1; j <= i; j++) dp[i][j] = sum[j][s % j];
		for(int j = 1; j <= i; j++) sum[j + 1][s % (j + 1)] = Add(sum[j + 1][s % (j + 1)], dp[i][j]);
	}
	for(int i = 1; i <= n; i++) ans = Add(ans, dp[n][i]);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

## 思路

考虑 $dp_{i,j}$ 表示看到第 $i$ 位选了 $j$ 段的方案数。

转移枚举从 $k$ 位转移，若 $k+1\sim i$ 位和为 $j$ 的倍数我们可以将他们分成一段，故可以转移。

复杂度 $O(n^3)$ 无法通过题目。

考虑优化，考虑定义一个 $sum_{i,j}$ 表示在 $\bmod\ i$ 的情况下 $pre_x$（前缀和）$=j$ 的所有 $dp_{x,j}$ 的和，转移时只需要查找对应的 $sum_{j,pre_i\bmod j}$ 即可。此时复杂度 $O(n^2)$ 可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int dp[3005][3005],tot[3005][3005];
signed main(){
	int n;
	cin>>n;
	int a[n+1],sum[n+1]; sum[0]=0;
	for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i];
	dp[0][0]=1;
	tot[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=n;j>=1;j--){
			dp[i][j]=tot[j-1][sum[i]%j];
			(tot[j][sum[i]%(j+1)]+=dp[i][j])%=mod;
//			cout<<dp[i][j]<<" ";
		}
//		cout<<endl;
	}
	int ans=0;
	for(int i=1;i<=n;i++) (ans+=dp[n][i])%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：xiaoPanda (赞：1)

## ABC207E - Mod i(*1820)
### Problem
给出 $n$ 个数 $A_i$，可以将它分成连续的许多段，满足第 $i$ 段所有数之和是 $i$ 的倍数，问方案数。

### Solution
考虑 DP，设 $f_{i,j}$ 表示将前 $i$ 个数分成 $j$ 段的方案数，易得 $f_{i,j}+=f_{k,j-1}(\sum_{w=k+1}^i A_w\bmod j=0)$，注意到 $j$ 每次增加 $1$ ，应该先枚举 $j$ ，再枚举 $i$。

这样时间复杂度是 $O(n^3)$ 的，将那个区间和写成前缀和就是 $(sum_i-sum_k)\bmod j=0$，所以 $sum_i\bmod j=sum_k\bmod j$。

再设 $g_{t,j}$ 表示当 $sum_i\bmod j=t$ 时，分成 $j$ 段的方案数，
那么原方程变为 $f_{i,j}+=g_{sum_i\bmod j,j-1}$，同理 $g_{sum_i\bmod j,j-1}+=f_{i,j-1}$，注意到应该先更新 $f$，再更新 $g$ ，因为每一段至少有 $1$ 个数，所以最开始的暴力 DP 中 $j-1\le k\le i-1$，更新 $f$ 时不要加上 $f_{i,j-1}$，但下一次计算 $f_{i+1,j}$ 就要加上 $f_{i,j-1}$了，所以后更新 $g$。

注意一下初始化 $g_{0,0}=1$，答案为 $\sum f_{n,i}$，时间复杂度为 $O(n^2)$。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3007;
const int M=1e9+7;
int f[N][N],g[N][N],a[N],sum[N];
main() 
{
	int n,ans=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]),sum[i]=sum[i-1]+a[i];
	g[0][0]=1;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++)/*此处i，j与题解中的相反*/
			f[j][i]=g[sum[j]%i][i-1],g[sum[j]%i][i-1]+=f[j][i-1],g[sum[j]%i][i-1]%=M;
	for(int i=1;i<=n;i++)
        ans=(ans+f[n][i])%M;
    printf("%lld",ans);
	return 0;
}
```

---

## 作者：AlicX (赞：1)

## Solution 

很经典的 `dp`，定义 $f_{i,j}$ 表示前 $i$ 个数分成 $j$ 段的方案数。

考虑 $O(n^3)$ 的暴力：当 $(s_i-s_k) \bmod j$ 为零时，$f_{i,j}=f_{i,j}+f_{k,j-1}$。

接下来考虑优化，发现判断条件等效于 $s_i \bmod j= s_k \bmod j$，于是用 $g_{j,p}$ 记录 $\sum \limits_{i=1}^{n} f_{i,j-1}(s_i \bmod j=p)$，转移令 $p=s_i \bmod j$，即为 $f_{i,j}=f_{i,j}+g_{j,p}$，$g_{j,p}=g_{j,p}+f_{i,j-1}$。

注意初始化为 $f_{0,0}=1,g_{1,0}=1$，时间复杂度为 $O(n^2)$。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=3010,Mod=1e9+7; 
int n; 
int a[N],s[N]; 
int f[N][N],g[N][N]; 
signed main(){ 
//	freopen("div.in","r",stdin); 
//	freopen("div.out","w",stdout); 
	scanf("%lld",&n); f[0][0]=1; int ans=0; g[1][0]=1;  
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),s[i]=s[i-1]+a[i]; 
	for(int i=1;i<=n;i++){ 
		for(int j=1;j<=n;j++){ 
			int p=s[i]%j; 
			f[i][j]=(f[i][j]+g[j][p])%Mod; 
			g[j][p]=(g[j][p]+f[i][j-1])%Mod; 
			if(i==n) ans=(ans+f[n][j])%Mod; 
		} 
	} printf("%lld\n",ans); return 0; 
} 
```


---

## 作者：Swirl (赞：0)

考虑 dp。

记 $dp(i, j, k)$ 为第 $i$ 组的状态，$k \in \{0, 1\}$。

- 当 $k = 0$，$dp(i, j, k)$ 为第 $i$ 组的开头是第 $j$ 个元素的方案数。
- 当 $k = 1$，$dp(i, j, k)$ 为第 $j$ 个元素第 $i$ 组结尾的状态。

首先，我们可以知道：

$$
dp(i, j, 0) = dp(i - 1, j - 1, 1)
$$

因为第 $i$ 组的开头是 $j$，那么第 $i - 1$ 组的结尾就一定是 $j - 1$。

而 $dp(i, j, 1)$ 的情况就是其实就是所有满足 $\sum_{l = k} ^ {j} a_l$ 为 $i$ 的倍数的 $dp(i, k, 0)$ 的和。

正常情况下枚举是 $\mathcal O(n)$ 的，但是可以开一个前缀和优化，再用 map 维护一下。

时间复杂度：$\mathcal O(n^2\log n)$，稍微有点小常数。

---

```cpp
namespace zqh {
	const int N = 3005;
	
	int n, a[N], sum[N], dp[N][N][2];
	
	void init() {
		cin >> n;
		rep (i, 1, n) {
			cin >> a[i];
			sum[i] = (sum[i - 1] + a[i]);
		}
	}
	
	void solve() {
		dp[0][0][0] = dp[0][0][1] = 1;
		rep (i, 1, n) {
			dp[1][i][1] = 1;
		}
		dp[1][1][0] = 1;
		rep (i, 2, n) {
			map<int, int> mp;
			rep (j, i, n) {
				dp[i][j][0] = dp[i - 1][j - 1][1] % mod;
				mp[sum[j - 1] % i] = (mp[sum[j - 1] % i] + dp[i][j][0]) % mod;
				dp[i][j][1] = (dp[i][j][1] + mp[sum[j] % i]) % mod;
			}
		}
		int ans = 0;
		rep (i, 1, n) ans = (ans + dp[i][n][1]) % mod;
		cout << ans; 
	}
	
	void main() {
		init();
		solve();
	}
}  // namespace zqh
```

其实 $k$ 的一维可以省掉，但我不想。

---

