# Inverse Coloring

## 题目描述

您有一个由 $n×n$ 的正方形板。 其中的每个图块的颜色为白色或黑色。

如果一个正方形板符合一下条件：

1. 对于第 $i (1\le i <n)$ 行，第 $i$ 行的第 $j(1 \le j \le n)$ 个图块颜色与第 $i+1$  行的第 $j$ 个图块颜色**都相同**，**或者**第 $i$ 行的第 $j(1 \le j \le n)$ 个图块颜色与第 $i+1$  行的第 $j$ 个图块颜色**都不同**
2. 对于第 $i (1\le i <n)$ 列，第 $i$ 列的第 $j(1 \le j \le n)$ 个图块颜色与第 $i+1$  列的第 $j$ 个图块颜色**都相同**，**或者**第 $i$ 列的第 $j(1 \le j \le n)$ 个图块颜色与第 $i+1$  列的第 $j$ 个图块颜色**都不同**

那么我们称这个正方形版为**漂亮着色**

如果它是**漂亮着色**并且**不存在**有一个单色矩形内的图块数大于等于 $k$，我们就称其为**完美着色**。

您的任务是计算给定大小的正方形板的**完美着色**方案数。

请输出答案对 $998244353$ 取模后的结果 。

## 说明/提示

样例解释 $1$：

$1×1$ 大小的正方形板是单个黑色图块或单个白色图块。 它们都包括一个由 $1$ 个图块组成的单色矩形。

样例解释 $2$：

这是 $2×2$ 大小的正方形板的**漂亮着色**，并且**不存在**有一个单色矩形内的图块数大于等于 $3$，（即**完美着色**）

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1027E/80de90a3415b68f83bd6bbf9ac9bd0269a52b223.png)

 $2×2$ 大小的正方形板的其余**漂亮着色**如下：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1027E/2cef71b669c5dbcffdc8761cbbdbcf9459086d31.png)

## 样例 #1

### 输入

```
1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 3
```

### 输出

```
6
```

## 样例 #3

### 输入

```
49 1808
```

### 输出

```
359087121
```

# 题解

## 作者：YellowBean_Elsa (赞：7)

这题的关键在于注意到**由第一行和第一列可以确定一个漂亮正方形**，且最大的同色子矩形面积为**首行和首列中最长同色子串长度之积**（手玩得证）。

于是我们考虑 dp 算一个 $1\,\times\,n$ 的情况数。

令 $dp[i][j]$ 表示前 $i$ 个最长同色子串长度 $\le j$ 个的情况数（当然，也可以设状态为恰好等于 j 个的情况数，只是转移方程会不同）

```cpp
for(k=i-j -> i-1)
dp[i][j]+=dp[k][min(j,k)];
```
$min(j,k)$ 保证 $k$ 之前没有更长的子串，从 $i-j$ 到 $i-1$ 枚举使 $k+1$ 到 $i$ 这段随便选都不会产生 $>j$ 的子串。

#### 然后就是统计答案了。

我们先把 $dp[n][i]$ 减去 $dp[n][i-1]$ 使之成为 $1\,\times\,n$ 中最长同色子串刚好为 $i$ 的情况数。（如果状态一开始就这么设的话不用这个操作）

然后枚举 $i$, $j$，如果乘积 $<k$ 就把 $dp[n][i] \times dp[n][j]$ 加入答案。

#### done

```cpp
//coder: Feliks*GM-YB
#include<bits/stdc++.h>
#define fu(i,a,b) for(int i = a, I = (b) + 1; i < I; ++i)
#define fd(i,a,b) for(int i = a, I = (b) - 1; i > I; --i)
const int N=517;
const int mod=998244353;
typedef long long ll;
using namespace std;
inline int read(){
    int x=0;char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return x;
}int n,k;
ll dp[N][N],ans;

int main(){
	n=read(),k=read();
	fu(i,1,n)dp[i][i]=1;//初始化（先不考虑到底涂那种颜色，只关注哪些颜色一样） 
	fu(i,2,n){
		fu(j,1,i-1)
			fu(k,i-j,i-1)dp[i][j]=(dp[i][j]+dp[k][min(j,k)])%mod;
		dp[i][i]+=dp[i][i-1];//notice this
	}
	//以上预处理出dp[i][j]表示前i个有<=j个连续的方案数
	fd(i,n,1)dp[n][i]=(dp[n][i]-dp[n][i-1]+mod)%mod;
	//变为dp[n][i]表示全部n个有 ==i 个连续的方案数（注意枚举次序） 
	fu(i,1,n)fu(j,1,n)
		if(i*j<k)ans=(ans+dp[n][i]*dp[n][j])%mod;
	printf("%lld\n",(ans<<1)%mod);//注意对于每一种情况(1,1)位置有两种选择，故要*2
	return 0;
}
```


---

## 作者：joe19025 (赞：5)

## [题目链接(点一下可以进去鸭)](https://www.luogu.org/problemnew/show/CF1027E)


------------

## 题解
### 前置结论
-  由于相邻行和相邻列必须完全相同或者完全不同，所以可以知道，只要确定了第一行和第一列就可以确定整个涂色的状态了。
- 题目要求其中涂色相同的最大矩形面积小于k,所以对于第一行连续相同最长的涂色个数乘上第一列连续相同最长的涂色个数必须要小于k。

### 那怎么求最长连续涂色个数的方案数呢。
设$dp[i][j][k]$为长度为i，最长连续涂色数为k，尾部最长连续涂色数为j的方案数。
##### 分两种情况
- 新的结尾的颜色和老的结尾颜色相同
	
    $dp[i+1][j+1][max(j+1,k)]+=dp[i][j][k]$
    
- 新的结尾的颜色和老的结尾的颜色不同

	$dp[i+1][1][max(1,k)]+=dp[i][j][k]$
    
### 统计答案
	就是计算所有长度乘在一起小于k的方案数即可即可。

### One More Thing
不要忘了答案除二，因为两边最长的相同时，不代表连续最长的涂色相同，可能一个是白的，一个是黑的。
### ~~剩下的我也不会了~~


------------

## Code
```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


int mod=998244353;

void add(int &a,int b)
{
    a=(a+b)%mod;
}

int main()
{
    int dp[2][505][505];
    int now=1;
    int pre=0;
    dp[0][0][0]=1;
    int n,K;
    scanf("%d%d",&n,&K);
    
    for(int i=0;i<n;i++)
    {
        pre=i&1;
        now=pre^1;
        memset(dp[now],0,sizeof(dp[now]));
        for(int j=0;j<=n;j++)
        {
            for(int k=0;k<=n;k++)
            {
                add(dp[now][j+1][max(j+1,k)],dp[pre][j][k]);
                add(dp[now][1][max(1,k)],dp[pre][j][k]);
            }
        }
    }
    int cnt[505];
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
        {
            add(cnt[i],dp[n&1][j][i]);
        }
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i*j<K)
            {
                ans+=(long long)cnt[i]*cnt[j];
                ans%=mod;
            }
        }
    }
    ans = (ans * (long long)((mod + 1) / 2)) % mod;
    printf("%lld",ans);
    return 0;
}
```


------------

#### 最后声明：本题解思路来源于codeforces官方tutorial，代码也借鉴了官方写法。

---

## 作者：pikiuk (赞：3)

分享一个 $n\ln n$ 的做法。

注意到当我们确定第一行后，接下来每一行只能和第一行完全同色或完全反色。

记 $f_k(n)$ 表示有多少个长度为 $n$ 的 $01$ 序列，使得其中最长同色连续段小于等于 $k$。

那么答案就是：
$$
\sum\limits_{i=1}^n (f_i(n)-f_{i-1}(n))\times f_{\lfloor \frac{n}{k}\rfloor}(n)
$$
那么问题可以转化为快速求 $f_k(n)$。

考虑容斥，那么有：
$$
f_k(n)=\sum\limits_{i=1}^n\sum\limits_{j=0}^i \binom{i}{j}(-1)^j \binom{n-jk-1}{i-1}
$$
注意到：
$$
\binom {n}{k}=\frac{n}{k}\binom {n-1}{k-1}
$$
那么有：
$$
\sum\limits_{i=1}^n\sum\limits_{j=0}^i \binom{i}{j}(-1)^j \frac{i}{n-jk}\binom{n-jk}{i}
$$
又有：
$$
\binom{n}{r}\binom{r}{k}=\binom{n}{k}\binom{n-k}{r-k}
$$
原式可以变为：
$$
\sum\limits_{i=1}^n\sum\limits_{j=0}^i \binom{n-j(k+1)}{i-j}\binom{n-jk}{j}(-1)^j \frac{i}{n-jk}
$$
交换求和号有：
$$
\sum\limits_{j=0}^n\binom {n-jk}{j}(-1)^j\frac{1}{n-jk}\sum\limits_{i=j}^n\binom{n-j(k+1)}{i-j}i
$$
记 $c=n-j(k+1)$，考察如下式子：
$$
\sum\limits_{i=j}^n\binom{c}{i-j}i
$$
令 $i=i+j$，有：
$$
\sum\limits_{i=0}^{n-j}\binom {c}{i}(i+j)
$$
也就是 ：
$$
j\sum\limits_{i=0}^{n-j}\binom{c}{i}+c\sum\limits_{i=0}^{n-j}\binom{c-1}{i-1}
$$
注意到 $n-j\geq c$，那么有：
$$
j\times 2^c+ c\times 2^{c-1}
$$
带回原式，则有：
$$
f_k(n)=\sum\limits_{j=0}^n\binom {n-jk}{j}(-1)^j\frac{1}{n-jk}(j\times 2^c+c\times 2^{c-1})
$$
注意到当 $jk> n$ 时，这个式子没有意义，因此 $j$ 只枚举到 $\lfloor\frac{n}{k}\rfloor$。

然后求全部 $n$ 个点的点值就是 $\sum\frac{n}{i}$，时间复杂度 $\mathcal{O}(n\ln n)$。

---

## 作者：UperFicial (赞：3)

> [**CF1027E Inverse Coloring**](https://www.luogu.com.cn/problem/CF1027E) 解题报告。

手玩几组样例发现，确定矩阵第一行和第一列后，即可确定整个正方形。

注意到，对于第一列连续的相同元素，这些位置对应的一行也都应该是相同的。这个结论放第一行上也同理。

所以对于第一行连续相同的元素和第一列连续相同的元素一定会有交，也就构成了一个子矩阵满足全部都是相同元素。

所以我们又可以得到第二个结论：最大全 `0` 或全 `1` 子矩阵的大小为，第一行最长连续元素的长度，与第一列最长连续元素的长度之积。

这样我们只需要关注第一行和第一列，但是第一行和第一列本质是相同的，所以只需要考虑第一行。

设 $f_{i,j}$ 表示考虑了前 $i$ 个元素，最长连续元素长度不大于 $j$ 的方案数，另设 $g_i$ 表示第第一行中，最长连续元素长度恰好为 $i$ 的方案数，那么显然 $g_i=f_{n,i}-f_{n,i-1}$。

考虑对于任意 $i,j$ 满足 $i\times j<K$ 我们都可以将它们对应的 $g$ 计入答案里。

$f_{i,j}$ 的转移也就很简单了， $f_{i,j}=\sum_{k=i-j}^{i-1} f_{k,j}$。使用前缀和优化就可以做到 $O(n^2)$ 了，当然在这道题中没有什么必要。

---

## 作者：MortisM (赞：2)

## Preface

[题目链接](https://codeforces.com/problemset/problem/1027/E)

**本题解提供了 $O(n^2)$ 的做法。**

校赛里碰到的，一道不错的 dp 题，原题数据范围可以再加强卡掉 $O(n^3)$ 的做法。

## Statement

现有一个 $n\times n$ 的 01 矩阵，该矩阵满足以下条件：
+ 对于该矩阵的第 $i$ 行,此行第 $j$ 个元素与第 $i+1$ 行第 $j$ 个元素都相同，或都不相同。
+ 对于该矩阵的第 $i$ 列,此列第 $j$ 个元素与第 $i+1$ 列第 $j$ 个元素都相同，或都不相同。
+ 阵内最大的全 0 和全 1 子矩阵的大小都严格小于 $k$ 。

求这样的矩阵个数对 $998244353$ 取模的结果。

## Solution

首先，通过模拟数据可以发现如果确定了矩阵的第一行和第一列就可以确定整个矩阵（容易证明，因为第一行确定基准，后面每一列确定是相同或不相同），并且最大的全 0 和全 1 子矩阵的大小等于第一行最长连续全 0 和全 1 乘上第一列全 0 和全 1 的长度。

这启发我们去分别计算两者的方案数，考虑 dp。设 $f(i,j)$ 表示 $i$ 个 0/1，最长为 $j$ 的方案。发现这并不容易转移，但是可以通过容斥状态，将状态改为 $f(i,j)$ 表示前 $i$ 个 0/1，最长 $\leq j$ 的方案数。这样一来，就可以转移了：

$$
f(i,j)=\sum_{k=i-j}^{i-1}f(k,\min(j,k))
$$

下面考虑统计答案，我们先把状态给容斥回去，即 $g(i)=f(n,i)-f(n,i-1)$，然后统计 $i\times j<k$ 的 $g(i)\cdot g(j)$ 的和即可，最后需要 $\times 2$。

至此我们就得到了一个时间复杂度为 $O(n^3)$ 的做法，[代码](https://codeforces.com/contest/1027/submission/180708661)。

当然，看到这个 $\sum$ 的形式我们似乎还可以用前缀和优化转移，实际上确实如此，我们可以分别记录 $f(i,i)$ 的前缀和 $S_1(i)$ 以及 $f(j,i)$ 的前缀和 $S_2(j,i)$，这样就可以将时间复杂度优化为 $O(n^2)$，[代码](https://codeforces.com/contest/1027/submission/180708690)。

## Summary

手动模拟数据 + 变换状态 + 前缀和优化，小清新 dp 好题~

---

## 作者：听取MLE声一片 (赞：2)

不难看出，一行加一列就能确定出整个正方形。

以下用“最长连续长度”来表示“连续相同的数最长长度”。

假定先确定出第一行，设最长连续长度为 $x$，则其他行都是由第一行传递或取反得到的，所以每一行连续相同的数最长都为 $x$。

然后确定第一列，设最长连续长度为 $y$，不难看出同色最大矩阵的大小为 $x\times y$。

问题就转化为求出每一个最长连续长度方案数的问题了，之后再枚举就行。

不难想到 dp 求解。设 $f_{i,j}$ 表示处理了前 $i$ 个元素，最长连续长度不大于 $j$ 的方案数。

转移的方式就为在之前已经处理过的长度上在加上一定长度的串，以下是转移代码。


```
for(int i=2;i<=n;i++){
	for(int j=1;j<i;j++)
		for(int k=i-j;k<i;k++)
			f[i][j]=(f[i][j]+f[k][min(j,k)])%mod;
	f[i][i]+=f[i][i-1];
}
 ```
 
注意这里处理出来的是不大于 $j$ 的方案数，循环减一下就行了。

还可以进行前缀和优化，不过我懒得写了。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=3010;
const int mod=998244353;
int n,k,f[N][N],ans;
signed main()
{
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	n=read(),k=read();
	for(int i=1;i<=n;i++)
		f[i][i]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++)
			for(int k=i-j;k<i;k++)
				f[i][j]=(f[i][j]+f[k][min(j,k)])%mod;
		f[i][i]+=f[i][i-1];
	}
	for(int i=n;i>=1;i--)
		f[n][i]=(f[n][i]-f[n][i-1]+mod)%mod;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i*j<k)ans=(ans+f[n][i]*f[n][j])%mod;
	printf("%lld",(ans<<1)%mod);
	return 0;
}
```

---

## 作者：Lilyisashit (赞：2)

一种n^2做法

其实只是优化？  :(

之前的是用dp[i][j]表示长度为i，最长连续相同颜色长度为j的序列个数

然后转移方程是

dp[i][j]=dp[i-1][j]+dp[i-2][j]+...+dp[i-j][j] (j<i)

dp[i][j]=2^(i-1) (j>=i)

此时枚举i,j,k是n^3的

我们可以把j<i时的方程拆开

dp[i][j]=dp[i-1][j]+dp[i-2][j]+...+dp[i-j][j]
   
=dp[i-1][j]+(dp[i-1][j]-dp[i-j-1][j]

=2*dp[i-1][j]-dp[i-j-1][j]

此时枚举i,j即可

~~~
%:pragma GCC optimize "-O3"
#include<bits/stdc++.h>
#define LLI long long int
#define heap priority_queue
using namespace std;
const LLI MAXN=500+5;
const LLI INF=(LLI)(9e18);
const LLI MOD=998244353;
LLI ans;
LLI dp[MAXN][MAXN];
LLI sum[MAXN],pw2[MAXN];
LLI N,K;
int main()
{
	scanf("%lld%lld",&N,&K);
    for(int i=1;i<=N;i++)
	    dp[0][i]=1;
	pw2[0]=1;
	for(int i=1;i<N;i++)
		pw2[i]=pw2[i-1]*2%MOD;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        	if(j<i)
        		dp[i][j]=(2*dp[i-1][j]%MOD-dp[i-j-1][j]+MOD)%MOD;
        	else
        		dp[i][j]=pw2[i-1];
	for(int i=1;i<=N;i++)
		sum[i]=(dp[N][i]-dp[N][i-1]+MOD)%MOD;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			if(i*j<K)
				ans=(ans+sum[i]*sum[j]%MOD)%MOD;
	printf("%lld\n",2*ans%MOD);
    return 0;
}
~~~

---

## 作者：大菜鸡fks (赞：2)

注意到满足条件其实就是要求行和列的最大连续的乘积小于k。

行列同质，只要dp一个就可以了

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int N=505,mod=998244353;
int n,K;
inline void init(){
	scanf("%I64d%I64d",&n,&K);
}
int sum,dp[N][N],ans[N];
inline void upd(int &x,int w){
	x=(x+w+mod)%mod;
}
inline void solve(){
	for (int i=1;i<=n;i++){
		dp[i][0]=1;
		for (int j=1;j<=n;j++){
			for (int k=1;k<=min(j,i);k++){
				upd(dp[i][j],dp[i][j-k]);
			}
		}
	}
	for (int i=1;i<=n;i++) upd(ans[i],dp[i][n]-dp[i-1][n]);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if (i*j<K) upd(sum,ans[i]*ans[j]);
		}
	}
	printf("%I64d\n",sum*2%mod);
}
signed main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：luogu_gza (赞：0)

翻译是狗屎。

一限制是每一对相邻的行在每个位置上要么相同，要么不同。

二限制是最大同色矩形面积 $<k$。

我们先来尝试探查一限制的本质，当我们确定了第一行以后，每一行都只有两种状态，我们只要知道了一个字符就可以确定整行，那么我们其实只要知道第一行和第一列即可。

我们再来考虑如果知道了第一行和第一列怎么对于最大同色矩形面积进行计算，我们把矩形投影到第一行和第一列上，不难注意到这两个投影上去的段都是同色的。

那么局势就很明了了，最大同色矩形面积等价于第一行和第一列的最大同色段长度之积。问题转化为了求序列上的钦定最大同色段长度的方案数。

我们尝试 dp，记 $f_{i,j}$ 表示前 $i$ 个点中，所有同色段长度都 $\leq j$ 的方案数，转移只需要枚举上一个同色段长度即可。

转移如下：

```
fo(i,2,n)
{
  fo(j,1,i-1) fo(k,i-j,i-1) (f[i][j]+=f[k][min(j,k)])%=mod;
  (f[i][i]+=f[i][i-1])%=mod;
}
```

答案即为：$2\sum_{i=1}^{n}\sum_{j=1}^{n}[ij<k](f_{n,i}-f_{n,i-1})(f_{n,j}-f_{n,j-1})$。

为什么要乘二？因为每一种同色段方案有黑同色段和白同色段两种。

代码不难。

---

## 作者：Annihilation_y (赞：0)

康复训练。

### 题目大意
给你 $n \times n$ 个方格，每个方格可以填黑或白两种颜色。

对于每一行，要么与上一行完全相等，要么完全相反。对于每一列也是如此。

求总方案数，使得满足条件，且颜色相同的最大矩形面积不超过 $k$。

### 题目理解
因为题目要求，所以这个图形一定是由多个小矩形构成的。所以可以对于行和列分开枚举，求总情况数。然后因为行和列的本质是相同的，要么相等要么不等，其实可以一起处理。

### 思路
定义 $f_{i,j}$，表示当前 $i$ 数中，最长相等个数小于等于 $j$ 的总情况数。

即可以将此理解为，$f_{i,j}$ 表示的是一个前缀和数组。

那么因为 $f_{i,j}$ 的定义，所以我们将所有 $\max(i-j,0) \sim i-1$ 的所有满足情况的结果加起来即可。因为我们可以在以上的基础上，钦定后面的所有的数字都相等，且与前一个不相等。经过一系列简单的枚举，可以证明此方案的不重复。

所以状态转移方程为 $f_{i,j} = \sum_{k = \max(0,i-j)}^{i-1} f_{k,min(j,k)}$。

之所以要写 $f_{k,min(j,k)}$ 是因为存在 $j > k$ 的情况，但这种情况肯定是要计算在总方案数里面的。因为 $f$ 是一个前缀和数组。所以在这样的情况下，就会将 $f_{i,j}$ 加上 $f_{k,k}$。

### 代码
~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=505;
#define int long long
const int Mod=998244353;
int f[MAXN][MAXN]; //f[i][j] 表示当前 i 个数中，最长相等个数小于等于 j 的总情况数
//f[i][j] 就像等于一个前缀和数组 
int n,k;
int ans=0;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) f[i][1]=1;
	for(int i=2;i<=n;i++) {
		for(int j=2;j<=i;j++) {//i 和 j都必须从 2 开始，避免重复计算 
			for(int k=i-1;k>=max(0ll,i-j);k--) {
				 	
				f[i][j]%=Mod;
			}
		}
		f[i][i]++;
		f[i][i]%=Mod;
	}
//	for(int i=1;i<=n;i++) {
//		for(int j=1;j<=i;j++) {
//			cout<<i<<" "<<j<<" "<<f[i][j]<<endl;
//		}
//	}
//	cout<<"---------\n";
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			if(i*j<k) {
				ans+=(f[n][i]-f[n][i-1])%Mod*(f[n][j]-f[n][j-1])%Mod;
				ans%=Mod; 
			}
		}
	}
	ans*=2;
	ans=(ans+Mod)%Mod;
	cout<<ans;
	return 0;
}
~~~

---

## 作者：FBW2010 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1027E)

# 思路

我们先不管 $k$ 的限制，把一列提出来，单独考虑它，那么这一列有 $2^n$ 种情况。由于要使正方形版为完美着色，不难发现其他列要么和它一样，要么完全相反。此时其它 $n-1$ 列都有两种情况，所以有 $2^{n-1}$ 种情况，总共便是**行的情况乘列的情况**，即 $2^{2n-1}$ 种。

但加入 $k$ 后怎么做呢？我们注意到一种情况中最大单色矩形的面积应该是**最长连续单色行**的长度乘上**最长连续相同列**的长度。

![](https://cdn.luogu.com.cn/upload/image_hosting/2fx8yxoi.png)

由于每行每列的情况都只有两种，可以看作 `0` 和 `1`。于是我们可以**预处理**出**长度为 $n$ 的 `01` 串中最长连续相同的长度为 $i$ 时的情况数**，然后枚举每行每列最长的连续长度，如果乘积小于 $k$ 就计入答案。

对于那个预处理，可以用 **dp** 以 $n^3$ 复杂度实现，我是定义 $dp_{i,j,k}$ 为长度为 $i$，最长连续相同的长度为 $j$，并且 $i$ 前面有连续 $k$ 个和 $i$ 一样的情况数，滚动一下简单转移一下就可以了。具体详见代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505,mod=998244353/*记得取模*/;
int n,k,ans,f[N]/*表示长度为n,最长连续长度为i时的情况数*/,dp[2][N][N]/*dp数组*/;
int main(){
	scanf("%d %d",&n,&k);
	dp[1][1][1]=2; //初始化 
	for(int i=2;i<=n;i++){
		int f=i&1;
		for(int j=1;j<=i;j++){
			//简单转移 
			for(int k=1;k<=j;k++){
				dp[f][j][k]=dp[f^1][j][k-1];
				dp[f][j][1]+=dp[f^1][j][k];
				dp[f][j][1]%=mod;
			}
			dp[f][j][j]+=dp[f^1][j-1][j-1];
			dp[f][j][j]%=mod;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			f[i]+=dp[n&1][i][j]; //丢进f中方便之后计算 
			f[i]%=mod;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i*j<k){ //判断是否合法 
				ans+=f[i]*1ll*f[j]%mod; //统计答案 
				ans%=mod;
			}
		}
	}
	printf("%lld",ans*499122177ll%mod); //相当于除以的模意义下的2,好像直接除也行,这里就不过多赘述 
	return 0;
}
```

---

## 作者：irris (赞：0)

## Preface

简单题。

## Solution

不同于其他题解，我有另一个侧面的观察：

+ 如果一矩阵仅满足行上的限制条件，它依旧永远满足列上的限制条件。
> + 证明可以手玩一下。
> + 其实就是 $a \oplus b = (a \oplus 1) \oplus (b\oplus 1)$ 啦。
    

所以发现，矩阵一定是由一堆网格拼成的。

那么矩阵的最大连通块大小就是行的最长连续段长度乘以列的最长连续段长度。这两个的形式是一致的。

考虑 dp 求解：设 $f_{i,j}$ 表示行最长连续段长度 $\leq i$ 的，长度为 $j$ 的一行网格的黑白方案数，则 $f_{i,j} = \displaystyle\sum_{k=\max(j-i,0)}^{j-1} f_{i,k}$。

维护前缀和，即可以 $\mathcal O(n^2)$ 求出 $f_{1,n}\dots f_{n,n}$。

然后发现答案其实就是 $\displaystyle\sum_{i=1}^n\sum_{j=1}^n[i\times j \lt k]f_i\times f_j$，可以整除分块 $\mathcal O(\sqrt{k})$。不过反正不在瓶颈上，所以怎么都随意咯。

时间复杂度 $\mathcal O(n^2)$。

## Code

```cpp
#include <bits/stdc++.h>

namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar(); while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return w ? ((~x) + 1) : x; }
	template <typename T> inline void write(T x) { x && (write<T>(x / 10), putchar(x % 10 ^ '0')); }
	template <typename T> inline void print(T x) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x); }
	template <typename T> inline void print(T x, char end) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x), putchar(end); }
}; using namespace FastIO;

constexpr int MOD = 998244353;
inline void add(int& x, int y) { (x += y) >= MOD && (x -= MOD); }
inline void del(int& x, int y) { (x -= y) < 0 && (x += MOD); }
inline int sum(int x, int y) { return (x += y) < MOD ? x : x - MOD; }
inline int minu(int x, int y) { return (x -= y) > 0 ? x : x + MOD; }

#define MAXN 501
int dp[MAXN], f[MAXN];

int main() {
	int N = read<int>(), K = read<int>() - 1;
	if (K == 0) return puts("0"), 0;
	for (int i = 1; i <= N; ++i) {
		dp[0] = 1;
		for (int j = 1; j <= N; ++j) {
			dp[j] = sum(dp[j - 1], dp[j - 1]);
			if (j > i) del(dp[j], dp[j - i - 1]);
		}
		f[i] = minu(dp[N], dp[N - 1]);
	}
	int ans = 0;
	for (int l = 1, r; l <= K && l <= N; l = r + 1) {
		r = std::min({K / (K / l), N, K});
		add(ans, 1ll * minu(f[r], f[l - 1]) * f[std::min(K / l, N)] % MOD);
	}
	return print<int>(sum(ans, ans)), 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 思路
显然是 $\text{DP}$。

注意到矩阵的填法和位置 $(1,1)$ 有关，所以想到考虑数组 $f[i][j]$ 的含义为前 $i$ 个同色子串小于等于 $j$ 的情况数，则显然转移方程为 $f[k][\max(j,k-i+1)]=f[k][\max(j,k-i+1)]+f[i-1][j]$

考虑统计答案，根据 $\text{dp}$ 数组的含义易知第一维肯定是 $n$，这样就只需枚举 $i,j$，当 $i \times j \le k$ 时就把 $f[n][i] \times f[n][j]$ 加入答案。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗
const int N=550;
int f[N][N]; 
const int MOD=998244353;
int n,k;
signed main(){
	cin>>n>>k;
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=i;k<=n;k++){
				f[k][max(j,k-i+1)]=(f[k][max(j,k-i+1)]+f[i-1][j])%MOD;//转移
			}
		}
	}
	k--;
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i*j<=k){
				ans=(ans+(f[n][i]*f[n][j])%MOD)%MOD;//统计答案
			}
		}
	}
	cout<<(ans<<1)%MOD<<endl;//(1,1) 有两种选择
	return 0;
} 
```


---

## 作者：轻绘 (赞：0)

# 算法

~~简单的~~DP

虽然是 $O(n^3)$ ，但是**比较直观**，好想。

写的也详细一些，将几个大佬的“易证”稍微解释一下。

[题目传送门](https://www.luogu.com.cn/problem/CF1027E)

[博客传送门](https://www.luogu.com.cn/blog/yanhangyn/)

# 思路

首先将令人烦躁的题意进行一个转换

~~根本看不懂~~

### 题意：

在一个 $n*n$ 的矩阵中，用黑白两种颜色进行染色，求满足下列条件的方案数：

1. 任意相邻的两列颜色排列要么完全相同，要么完全相反。

2. 任意相邻的两行颜色排列要么完全相同，要么完全相反。

	**注意：完全相反指的是黑变白，白变黑。**
    
3. 相同颜色组成的矩形面积小于 $k$ 。 （题目中给出 $k$ 大小）

### 可以得到的几个结论：

 1. 在确定第一行和第一列的颜色排列后，就可以得到有且仅有一种的“漂亮着色”。（及满足题意中 1,2 条的矩阵方案）
 
 2. 一种“漂亮着色”方案中，最大的相同颜色矩阵面积，是第一行中相同颜色组成的最长连续子串长度乘上第一列中相同颜色组成的最长连续子串长度。
 
 3. 第一行与第二行情况完全相同。（排列种类）
 
 **（注意：两个子串颜色不同也没有影响）**

#### 	证明：

1. 若第一行中第 $i$ 和第 $i+1$ 颜色相同，那么第 $i$ 列和 $i+1$ 列必定完全相同，反之则是完全不同。因此在确定第一行颜色排列后，可以得到任意相邻两列之间的关系。

	此时再得知第一列的全部颜色排列后，即可推出仅有一种满足“漂亮着色”的方案。（当然将列和行反过来想也一样）
    
2.	对于第一行 $i$ 与 $i+1$ 颜色相同，那么第 $i$ 列与 $i+1$ 列就是完全相同。所以第一列中相同颜色组成的最长连续子串长度就是该同色矩形的宽，第一行中相同颜色组成的最长连续子串长度就是该同色矩形的长。

3. 因为是正方形嘛，嗯嗯嗯。

### 因此

将第一行的所有状态求出，枚举所有情况，将其中符合“完美着色”的累加即可。（行列完全相同）

### 状态定义

$f(i,j,k)$ 表示

处理第 $i$ 个，最长相同颜色连续子串长为 $j$ ，结尾相同颜色连续长度为 $k$ 。

### 状态转移    

当 $i+1$ 与 $i$ 颜色不同时：$f(i+1,j,1)+=f(i,j,k)$ 

当 $i+1$ 与 $i$ 颜色相同时：$f(i+1,\max(j,k+1),k+1)+=f(i,j,k)$

### 一些细节

1. 由于直接开 $O(600^3)$ 的空间会炸，而且我们观察到状态转移只与前一个状态有关，所以用一个滚动数组。

2. 由于在处理时白色与黑色没有区别，所以任何一种方案都有两个情况，所以最后答案乘二。

3. 最后枚举可行答案时，有四个变量，即行和列的 $f(i,j,k)$ 的后两维。于是我们用一个新数组 $o(j,k)$ 表示第 $j$ 个位置最长相同颜色连续子串长为 $k$ 的数量。最后只需枚举行和列的 $k$ 即可。（都是 $n$ 的情况）

4. **不要忘记取余！**

# 代码

```
#include<bits/stdc++.h>
#define int long long
const int p=998244353;
using namespace std;
int n,k,x=1,y;
long long ans;
int f[2][600][600];
int o[600][600];
signed main(){
	cin>>n>>k;
	f[1][1][1]=1;
	for(int i=1;i<n;++i){
		for(int j=1;j<=i;++j){
			for(int v=1;v<=j;++v){
				f[!x][j][1]=f[!x][j][1]%p+f[x][j][v]%p;
				if(v+1>j)	f[!x][v+1][v+1]=f[!x][v+1][v+1]%p+f[x][j][v]%p;
				else f[!x][j][v+1]=f[!x][j][v+1]%p+f[x][j][v]%p;
			}
		}
		memset(f[x],0,sizeof(f[x]));
		x=!x;//滚动数组
		y=x;//记录n在滚动数组中哪个
	}
	for(int j=1;j<=n;++j)
		for(int v=1;v<=n;++v)
			o[y][j]=o[y][j]%p+f[y][j][v]%p;
	for(int i=1;i<=n;++i){//行的最长相同颜色子串长度
		for(int j=1;j<=n;++j){//列的最长相同颜色子串长度
			if(i*j<k)
				ans+=o[y][i]%p*o[y][j]%p; 
				ans=ans%p;	
		}
	}
	printf("%lld",ans*2%p);
	return 0;
}
```

    
	


---

