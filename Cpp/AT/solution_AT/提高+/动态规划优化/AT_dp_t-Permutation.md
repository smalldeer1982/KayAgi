# Permutation

## 题目描述

给定一个正整数 $N$ 和一个由小于号 `<` 和大于号 `>` 组成的长度为 $N-1$ 的字符串 $s$。

你需要找到一个排列 $(p_1,\ p_2,\ p_3,\ ...,\ p_N)$，满足对于任意 $i\ (1 \leq i \leq N-1)$，如果 $s_i$ 为 `<` 则 $p_i < p_{i+1}$，如果 $s_i$ 为 `>` 则 $p_i > p_{i+1}$。求满足性质的排列 $p$ 的方案数**对 ${10}^{9}+7$ 取模**后的值。

## 说明/提示

### 数据范围与约定

- $N$ 是正整数
- $2 \leq N \leq 3000$
- $s$ 是一个长度为 $N-1$ 的字符串
- 字符串 $s$ 包含字符 `<` 和 `>`

### 样例解释 1

有 $5$ 个满足条件的排列，分别是：

- $(1,\ 3,\ 2,\ 4)$
- $(1,\ 4,\ 2,\ 3)$
- $(2,\ 3,\ 1,\ 4)$
- $(2,\ 4,\ 1,\ 3)$
- $(3,\ 4,\ 1,\ 2)$

### 样例解释 2

有 $1$ 个满足条件的排列 $(1,\ 2,\ 3,\ 4,\ 5)$。

### 样例解释 3

**注意输出结果要对 ${10}^{9}+7$ 取模。**

## 样例 #1

### 输入

```
4
<><```

### 输出

```
5```

## 样例 #2

### 输入

```
5
<<<<```

### 输出

```
1```

## 样例 #3

### 输入

```
20
>>>><>>><>><>>><<>>```

### 输出

```
217136290```

# 题解

## 作者：云浅知处 (赞：46)

考虑 dp：用 $F(i,j)$ 表示在前 $i$ 个位置上填入 $1\sim i$，且最后一位填 $j$ 的方案数。显然 $F(1,1)=1$。

转移 $F(i,j)$ 时，我们可以将前 $i-1$ 个数中 $\ge j$ 的数全部加 $1$ 以保证填入的是排列。

这样一来，枚举第 $i-1$ 个数具体是多少，我们得到了转移方程：

$$
F(i,j)=\begin{cases}\sum_{k=1}^{j-1} F(i-1,k)&,S_i=\texttt{"<"}\\\sum_{k=j}^{i-1}F(i-1,k)&,S_i=\texttt{">"}\end{cases}
$$

记录一下前缀和优化转移，就做到了 $O(n^2)$ 的时间复杂度。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>

#define int long long
const int mod=1e9+7;
const int MN=3005;

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

int n,dp[MN][MN],sum[MN][MN];
char s[MN];

signed main(void){

    cin>>n;
    cin>>(s+1);
    dp[1][1]=1;
    for(int i=1;i<=n;i++)sum[1][i]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i;j++){
            if(s[i-1]=='<')dp[i][j]=sum[i-1][j-1]%mod;
            if(s[i-1]=='>')dp[i][j]=(sum[i-1][i-1]-sum[i-1][j-1]+mod)%mod;
            sum[i][j]=(sum[i][j-1]+dp[i][j])%mod;
        }
    }
    cout<<sum[n][n]%mod<<endl;

    return 0;
}
```

---

## 作者：FelFa_1414666 (赞：22)

一道需要一定分析的 dp 题目。

[atcoder 题目传送门](https://atcoder.jp/contests/dp/tasks/dp_t) & [洛谷题目传送门](https://www.luogu.com.cn/problem/AT4541)

[更好的阅读体验](https://www.luogu.com.cn/blog/xesssb10108899/solution-at4541)

---

## Description

给定 $n$ 和一个长度为 $n-1$ 的字符串（由 '<' 和 '>' 组成），求数列 $1,2,...,n$ 有多少种排列，使得相邻数之间的大小关系与字符串中大于号小于号相符合，答案对 $10^9+7$ 取模。

- $1\le n\le 3000$

---

## Solution1

### analysis

先给出本题的一个**重要结论**：

> 对于这一序列的任何一个子序列，在其内部排列时我们只需要关心每个数的大小关系，而不是每个数具体的值。

举例：

序列`6,9,11`在进行内部排列时，我们可以将其视为`1,2,3`。

所以：

**我们只要考虑上一个数是什么，保证满足大小关系放数就行。**

这样我们得到了一个显然的 dp 状态：

- $dp_{i,j}$ 表示考虑到第 $i$ 个位置，前面一个数是前面排列中**第 $j$ 大**（上面已经得出结论，第 $j$ 大的数就视为 $j$ 参与排列）的可能数。

转移：

分为两种情况：**当前的数 > 上一个数** & **当前的数 < 上一个数**。

- 枚举上一个数在之前序列中大小排名 $k$，通过相对大小关系得到转移方程：

$$dp_{i,j}=\begin{cases}\sum\limits_{k=1}^{j-1}dp_{i-1,k}&s_{i-1}='<'\\\sum\limits_{k=j}^{i-1}dp_{i-1,k}&s_{i-1}='>'\end{cases}$$

这样转移是 $O(n)$ 的，需要优化。观察转移方程不难发现，可以对 $dp_{i-1}$ 记录前缀和，然后用前缀和进行转移。这当然是可以的，但是有代码量更少更好写的做法：

以 $s_{i-1}='<'$ 举例，我们比较 $dp_{i,j-1}$ 和 $dp_{i,j}$ 发现可以用他们的差递推，从 $dp_{i,j-1}$ 向 $dp_{i,j}$ 转移 。$s_{i-1}='>'$ 同理，从 $dp_{i,j+1}$ 向 $dp_{i,j}$ 转移。

- 这样，我们就有了新的转移方程：

$$dp_{i,j}=\begin{cases}dp_{i,j-1}+dp_{i-1,j-1}&s_{i-1}='<'\\dp_{i,j+1}+dp_{i-1,j}&s_{i-1}='>'\end{cases}$$

这样的转移是 $O(1)$ 的。

时间复杂度：$O(n^2)$。

空间复杂度：$O(n^2)$（如果用滚动数组可以降到 $O(n)$，但这一题空间足够了）。

### code

```c++
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
const ll MOD=1e9+7;//取模
int n;
string s;
ll dp[3005][3005],ans;
int main()
{
	cin>>n>>s; 
	dp[1][1]=1ll;//这里数组下标从1开始
	for(int i=2;i<=n;i++)
	{//按上面公式进行递推转移
		if (s[i-2]=='<')
			for(int j=1;j<=i;j++)
				dp[i][j]=(dp[i][j-1]+dp[i-1][j-1])%MOD;
		else
			for(int j=i-1;j>=1;j--)
				dp[i][j]=(dp[i][j+1]+dp[i-1][j])%MOD;
	}
	for(int j=1;j<=n;j++)
		ans=(ans+dp[n][j])%MOD;//答案为dp[n]总和
	cout<<ans<<endl;
	return 0;
}
```

---

## Solution2

emmm，这个方法是在 atcoder 现场排行榜上看大神写的，思维难度比较大，代码也不是很好写。~~大概是常人的思维想不到罢。~~

记录下序列中每一个**递增序列**的长度，通过**排列组合**做。

- 状态：$dp_{i,j}$ 表示考虑到第 $i$ 个递增序列，上一个序列长度为 $j$ 的可能数。

- 转移：预处理阶乘及阶乘逆元，当前递增序列长度为 $x$。

$$dp_{i+1,j+x}\leftarrow dp_{i+1,j+x}-dp_{i,j}$$

$$dp_{i+1,x}\leftarrow dp_{i+1,x}+\frac {dp_{i,j}}{j!}$$

最后答案为 $\sum\limits_{j=0}^n(dp_{n,j}\div A_n^j)\times n!$。

时间复杂度：$O(n^2)$。

空间复杂度：滚动数组 $O(n)$。

### code

```cpp
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const int mod = 1000000007;

int N; char S[3030];
vector<int> z;//记录每个递增序列长度
//inv为逆元，fact为阶乘，ifact为阶乘逆元
long long inv[3030] = {0,1}, fact[3030] = {1,1}, ifact[3030] = {1,1};
long long prv[3030],nxt[3030];//滚动的dp数组

int main()
{
	scanf ("%d",&N);
	scanf ("%s",S);
	int s = 1;
	for (int i=0;i<N-1;i++){//储存递增序列
		if (S[i] == '<') s++;
		else{
			z.push_back(s);
			s = 1;
		}
	}
	z.push_back(s);
	for (int i=2;i<=N;i++){
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		fact[i] = fact[i-1] * i % mod;
		ifact[i] = ifact[i-1] * inv[i] % mod;
	}//递推预处理阶乘和逆元
	prv[z.back()] = 1;
	z.pop_back();
	reverse(z.begin(),z.end());
	for (int x : z){
		for (int j=0;j<=N;j++) nxt[j] = 0;
		for (int j=0;j<=N;j++) if (prv[j]){//转移
			nxt[j+x] = (nxt[j+x] + mod - prv[j]) % mod;
			nxt[x] = (nxt[x] + prv[j] * ifact[j]) % mod;
		}
		for (int j=0;j<=N;j++) prv[j] = nxt[j];
	}
	long long sum = 0;
	for (int j=0;j<=N;j++) sum = (sum + prv[j] * ifact[j]) % mod;//求答案
	printf ("%lld\n",sum*fact[N]%mod);
	return 0;
}
```

~~好吧其实对这个解法我也是似懂非懂。~~ 这个解法代码量大了一些，其实是走了弯路。还是建议大家用上面那个方法。

---

## 作者：_GaP (赞：16)

## 题目大意
求出满足给定大小关系的**排列**数。

## 题目分析
令 $F_{i,j}$ 表示第 $i$ 个位置填的数字在前 $1$ 到 $i$ 个位置填的数为第 $j$ 小。因为该序列为一个排列，所以各个数**互不相同**。  

大于小于号对当前状态的贡献是不同的，所以我们分类讨论。  
1. 当第 $i$ 个数应小于第 $i-1$ 个数时，也就是这个位置填大于号。只要第 $i-1$ 个数是第 $j$ 到 $i-1$小的，就可以满足在当前状态下第 $i$ 个数为第 $j$ 小。  
所以方程如下： 
$$F_{i,j}=\sum\limits_{k=j}^{k < i}  F_{i-1,k}$$  

**注意**:这里的 $k$ 可以取到 $j$，因为 $i-1$ 位置上的数字在前 $i-1$ 个数中第 $j$ 小，加之第 $i$ 个数大于第 $i-1$ 个数，到了前 $i$ 个数就是第 $j+1$ 小了，满足要求。  

2. 当第 $i$ 个数大于第 $i-1$ 个数，也就是当前位置填小于号，就可以同理推出：
$$F_{i,j}=\sum_{k=1}^{k<j}  F_{i-1,k}$$
同样的，这里 $k$ 是无法取到 $j$ 的。

最终答案就是 $\sum\limits_{i=1}^{n-1}F_{n,i}$。  

但是此时时间复杂度是悲伤的 $O(n^3)$，在 $n\leq 3000$ 的数据范围下会时间超时。  
只需要**前缀和优化**就能将时间复杂度打到 $O(n^2)$。
## 代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 3010
#define mod 1000000007
long long n,f[N][N],s[N][N],ans;
char a[N];
int main ()
{
	scanf("%lld",&n);
	scanf("%s",a+2);//向后移一位，避免对应问题 
	f[1][1]=s[1][1]=1;
	for(long long i=2;i<=n;i++)
	{
		for(long long j=1;j<=i;j++)
		{
			if(a[i]=='<')
			{
				f[i][j]=s[i-1][j-1]%mod;
				s[i][j]=(s[i][j-1]+f[i][j])%mod;
			}
			else
			{
				f[i][j]=(f[i][j]+s[i-1][i-1]-s[i-1][j-1]+mod)%mod;
				s[i][j]=(s[i][j-1]+f[i][j])%mod;
			}
		}
	}
	for(long long i=1;i<n;i++)ans=(ans+f[n][i])%mod;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：ZillionX (赞：13)

> 给定长度为 $n-1$ 的字符串 $s$，若 $s_i='>'$ 则 $p_i<p_{i+1}$，否则 $p_i>p_{i+1}$，求满足条件的排列 $p$ 个数。

> $n \le 3000$，2s。

看见题解区清一色的二维 DP（虽然说滚动一下可以变成一维），发一个 DP 状态只需要一维的容斥做法。

约定下文中的 $s$ 为原定义的 $s$ 整体右移一位后的结果。

我们考虑忽略掉排列中的全部大于号，则此时我们要求的就是满足可以划分为若干个单调上升连续段的排列数，但是很显然原来的大于号此时不一定仍然满足大于条件，所以这比原答案要大。

我们考虑减去什么才能得到原答案，容易想到大力容斥，钦定一些大于号变为小于号，然后带上容斥系数把方案数加进答案里面。不难发现容斥系数即为被钦定的大于号个数，下面讲怎么快速处理这个。

很显然划分单调上升连续段的方案数是多重排列 $\dfrac{n!}{\prod x_i!}$ 的形式，我们把它写成 ${n \choose x_n}{n-x_n \choose x_{n-1}}\cdots {n - \sum_{i=2}^n x_i \choose x_1}$ 方便后文转移。

设 $f_i$ 为处理到 $i$ 且 $i$ 为单调上升连续段末尾的容斥答案。

有

$$f_i=\sum_{j=0}^{i-1}[s_{j+1}='>'](-1)^{s_i-s_{j+1}}{i \choose i-j} f_j$$

把组合数拆开后，容易发现这是一个半在线卷积的形式，容易用多项式求逆做到 $\mathcal O(n \log n)$，用分治 FFT 做到 $\mathcal O(n \log^2 n)$。下面给出的是 $\mathcal O(n^2)$ 的朴素实现。

```cpp
const int N=3e3+5,mo=1e9+7;
int n,f[N],a[N],fc[N],ifc[N];
char s[N];
int qpow(int x,int y=mo-2) {
	int mul=1;
	for (;y;y>>=1,x=1ll*x*x%mo)
		if (y&1) mul=1ll*mul*x%mo;
	return mul;
}
void init() {
	fc[0]=1;
	for (int i=1;i<=n;i++) fc[i]=fc[i-1]*i%mo;
	ifc[n]=qpow(fc[n]);
	for (int i=n-1;i>=0;i--) ifc[i]=ifc[i+1]*(i+1)%mo;
}
signed main(){
	scanf("%lld%s",&n,s+2);
	s[1]='>';
	init();
	for(int i=2;i<=n;i++)a[i]=a[i-1]+(s[i]=='>');
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++){
			if(s[j+1]!='>')continue;
			int bf=f[j]*ifc[i-j]%mo;
			if((a[i]-a[j+1])&1)mde(f[i],bf);
			else mad(f[i],bf);
		}
	printf("%lld",f[n]*fc[n]%mo);
	return 0;
}
```


---

## 作者：SoyTony (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT4541)

属于比较典型的排列 dp，看到数据范围可以 $O(n^2)$ 做，第一维定然是考虑到第 $i$ 个位置。

发现如果将第二维设置成具体的数，不能保证这是一个排列，发现我们只关心相对大小关系，可以设置为排名。

即令 $dp_{i,j}$ 表示考虑到前 $i$ 个位置且第 $i$ 个数目前的排名为 $j$ 的方案数（排名是从小到大），分类讨论得出转移方程。

对于 `<` 的情况，第 $i-1$ 个数原先的排名一定低于 $j$，于是有：
$$dp_{i,j}=\sum_{k=1}^{j-1} dp_{i-1,k}$$
同理，对于 `>` 的情况，第 $i-1$ 个数原先的排名一定不高于 $j$，原因是加入一个比 $i-1$ 上小的数，其排名上升了，于是有：
$$dp_{i,j}=\sum_{k=j}^{i-1} dp_{i-1,k}$$

这样复杂度是 $O(n^3)$ 的，不难想到前缀和优化，可以降到 $O(n^2)$

**代码**
```cpp
int n;
char s[3005];
int dp[3005][3005];
int sum[3005];
int main(){
    n=read();
    scanf("%s",s+2);
    dp[1][1]=1;
    for(int i=1;i<=n;++i) sum[i]=1;
    for(int i=2;i<=n;++i){
        for(int j=1;j<=i;++j){
            if(j==1&&s[i]=='<') continue;
            if(j==i&&s[i]=='>') continue;
            if(s[i]=='<'){
                dp[i][j]=(dp[i][j]+sum[j-1])%mod;
            }
            else{
                dp[i][j]=(dp[i][j]+sum[i-1]-sum[j-1]+mod)%mod;
            }
        }
        for(int j=1;j<=n;++j) sum[j]=(sum[j-1]+dp[i][j])%mod;
    }
    printf("%d\n",sum[n]);
    return 0;
}
```


---

## 作者：youyou2007 (赞：9)

## Description
给定一个数字 $n$，表示有一个长度为 $n$ 的序列，又给定一个长度为 $n-1$ 字符串 $s$，里面仅包含 $<$ 和 $>$。

当 $1 ≤ i ≤ n - 1$ 时，`s[i]` 表示数列中第 $i$ 个元素与第 $i + 1$ 个元素的关系。

求满足字符串 $s$ 关系的 $1$ ~ $n$ 的排列一共有多少种，方案数对 $10^9+7$ 取模。

## constraints
$2 ≤ n ≤ 3000$
## Solution 1 TLE

考虑DP。

设 `f[i][j]` 表示已经考虑了前 $i$ 个位置，且第 $i$ 位上，填的数字是第 $j$ 小的总方案数。

不难想到初始状态即用 $1$ 填了 $1$ 位，即 `f[1][1] = 1` 。

由于每一位必由前一个位置转移过来，所以可以分两种情况：

+ 这个位置是 `<`，根据状态定义，前一位要比这个小，即 `f[i][j] += f[i - 1][k] (k < j)`；

+ 这个位置是 `>`，前一位要比这个大，但是，在 $i-1$ 时的第 $j$ 小，由于现在加入了一个第 $j$ 小的数，将上次的第 $j$ 小变成了现在的 $j+1$ 小，所以需要加上 `f[i - 1][k]`。即 `f[i][j] += f[i - 1][k] (j ≤ k < i)`；

由于这个复杂度是 $O(n^3)$，因此还是会超时。



## Solution 2 AC
上面的算法复杂度较高，考虑优化，但状态已经优化到了二维，考虑优化转移。

发现最内层循环时，由于要统计上一个数的所有可能转移的位置，耗费了较多时间。

由于可能转移的位置肯定都是一个连续的段，且是它们之和，可以前缀和优化。设 `sum[j]` 表示从 `f[i-1][1]` 到 `f[i-1][j]` 的数值之和，转移时直接计算即可。

时间复杂度为 $O(n^2)$。

核心代码：

```cpp
	f[1][1] = 1;//初始值
	for(int i = 2; i <= n; i++)
	{
		memset(sum, 0, sizeof sum);//每一次sum要清空
		for(int j = 1; j <= i - 1; j++)
		{
			sum[j] = sum[j - 1] + f[i - 1][j];//sum记录前缀和
		}
		for(int j = 1; j <= i; j++)
		{
			if(s[i] == '<')//处理小于号
			{
				f[i][j] = (f[i][j] + sum[j - 1] - sum[0]) % MOD;
			}
			else//处理大于号
			{
				f[i][j] = (f[i][j] + sum[i - 1] - sum[j - 1]) % MOD;
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)//最后答案是f[n][i]的总和
	{
		ans = (ans + f[n][i]) % MOD;
	}
```
## Code
[Solution 1 代码](https://atcoder.jp/contests/dp/submissions/25550216)

[Solution 2 有注释代码](https://www.luogu.com.cn/paste/6d97e0ap)


---

## 作者：ttttalk (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_dp_t)

## Description

给定 $n$ 个空位之间的 `<` 和 `>`，将 $1$ 到 $n$ 的整数填入，求方案个数。$N=3e3$。

## Solution

定义 $f_{i,j}$ 意为第 $i$ 位上填的是前 $i$ 位第 $j$ 小的数的方案数，则有 $f_{1,1}=1$ 的初值，答案是填了 $n$ 个的所有情况之和，也就是 $\sum\limits_{i=1}^nf_{n,i}$。

- 当第 $i$ 和 $i-1$ 之间的符号为 `<` 时，新来的数字是更大的，不会改变第 $i-1$ 位的地位，所以选择比 $j$ 小的来转移就行了，也就是 $f_{i,j}=\sum \limits_{k=1}^{k<j}f_{i-1,k}$。

- 当第 $i$ 和 $i-1$ 之间的符号为 `>` 时，新来的数字是更小的，会使第 $i-1$ 位的地位改变，变得必须比 $j$ 大，但是不能超过 $i$，也不能取到 $i$（因为新来的是更小的），所以是 $f_{i,j}=\sum\limits_{k=j}^{k<i}f_{i-1,k}$。

时间复杂度 $O(n^3)$，$TLE$。

## Optimization

发现第三层循环的 $k$ 可以用前缀和优化掉，于是边填表边更新前缀和。

## Ac Code

```cpp
#include<cstdio>
#include<iostream>
#define int long long
using namespace std;
const int N=3e3+10,mod=1e9+7;
int n,f[N][N],s[N][N],ans;
char t[N];
signed main()
{
	scanf("%lld %s",&n,t+2);
	f[1][1]=s[1][1]=1;
	for (int i=2;i<=n;i++)
	{
		if (t[i]=='<')
			for (int j=1;j<=i;j++)
			{
				f[i][j]=s[i-1][j-1]%mod;
				s[i][j]=(f[i][j]+s[i][j-1])%mod;
			}
//				for (int k=1;k<j;k++) f[i][j]=(f[i][j]+f[i-1][k])%mod;
		else
			for (int j=1;j<=i;j++)
			{
				f[i][j]=(f[i][j]+s[i-1][i-1]-s[i-1][j-1]+mod)%mod;
				s[i][j]=(f[i][j]+s[i][j-1])%mod;
			}
//				for (int k=j;k<i;k++) f[i][j]=(f[i][j]+f[i-1][k])%mod;
	}
	for (int i=1;i<=n;i++) ans=(ans+f[n][i])%mod;
	printf("%lld\n",ans%mod);
}
```

---

## 作者：novax (赞：1)

[题面](https://www.luogu.com.cn/problem/AT4541)

### 题意

给你一个长度为 $N-1$ 由大于号和小于号组成的串，求一个长度为 $N$ 的排列插入符号之间，使整个不等式成立。

### 思路

一种特殊的dp，姑且称之为插入dp。

设 $F_{i,j}$ 表示当前做到了第 $i$ 个空位，当前空位插入了当前序列中从小到大第 $j$ 大的数的方案数。有 $N-1$ 个符号，所以是 $N$ 个空位。这里的“从小到大第j大”指的是当前已经插入的数字的大小关系，并不是其真实数值。

在当前空位之前的符号为小于号时，有 $F_{i,j} = \sum_{k=1}^{j-1} F_{i-1,k}$，因为当前插入的是第 $j$ 大的数字，所以所有在上一位插入的数字位次小于 $j$ 的方案都能满足这个小于号；当前空位之前的符号为大于号时，则有 $F_{i,j} = \sum_{k=j}^{i} F_{i-1,k}$，道理同上，所有此前位次大于等于 $j$ 的方案都是合法的，这种情况下的 $F_{i-1,k}$ 也应该转移到当前状态，因为上一次的第 $j$ 位次在当前钦定的第 $j$ 位次插入后就变成了第 $j+1$ 位次。

由此的转移是 $n^3$ 的。在转移的同时维护一个 $F_{i-1}$ 行的前缀和，即可将转移复杂度降为 $O(n^2)$，可以通过本题。

### 代码

```cpp
#include <cstdio>
const int mod=1e9+7;
int N;
long long sum[3010],F[3010][3010],ans;//表示前i个数字 当前插入为从小到大第j大的数的方案数
char s[3010];
int main()
{
	scanf("%d%s",&N,s+1);
	int i,j,k;
	F[1][1]=1;sum[1]=1;
	for(i=2;i<=N;i++)
	{
		for(j=1;j<=i;j++)
		{
			if(s[i-1]=='<')
				F[i][j]=(F[i][j]+sum[j-1])%mod;
			if(s[i-1]=='>')
				F[i][j]=(F[i][j]+sum[i-1]-sum[j-1]+mod)%mod;
		}
		sum[1]=F[i][1];
		for(j=2;j<=i;j++)
			sum[j]=(sum[j-1]+F[i][j])%mod;
	}
	for(i=1;i<=N;i++)
		ans=(ans+F[N][i])%mod;
	printf("%lld\n",ans);
}
```


---

## 作者：MortisM (赞：1)

题意：给你一个长度为 $n-1$ 的只有 `<` 或者 `>` 两种字符的字符串 $s$，分别代表 $p_i<p_{i+1}$ 或 $p_i>p_{i+1}$，求有多少个 $1$ 到 $n$ 的排列 $p$ 满足这个要求。

数据范围：$n\leq 3000$。

一开始容易想到一个错误的状态 $f(i,j)$ 表示第 $i$ 个数为 $j$ 的情况数。

这个状态错误的原因就是我们不应该关心 $p_i$ 的值，而是应该关心 $p_i$ 在前 $i$ 个数中的排名。

这样就不难设计出 DP 状态 $f(i,j)$ 表示第 $i$ 个数在 $1$ 到 $i$ 中排名为 $j$ 的情况。

转移:

+ 若 $s_{i-1}$ 为 `<`，则 $f(i,j)\leftarrow \sum_{k=1}^{j-1}f(i-1,k)$。
+ 否则 $f(i,j)\leftarrow \sum_{k=j}^nf(i-1,k)$。

用前缀和优化一下即可，时间复杂度 $O(N^2)$。

**[代码](https://atcoder.jp/contests/dp/submissions/33728523)**

---

## 作者：MortisM (赞：1)

# 前言

怎么说呢？这个题看起来也不太难，但是感觉要想到这个状态还是有一定难度的。（至少对于我来说是这样）

设计这个题的状态要求清晰地认识需要什么和不需要什么。

# 题目大意

这个题题意还是很清楚的。

你有一个长度为 $n-1$ 的字符串 $s$，其中每个字符为 `<` 或者 `>`，表示 $p_i<p_{i+1}$ 或者 $p_i>p_{i+1}$。

求有多少个 $1$ 到 $n$ 的排列满足要求，输出结果模 $10^9+7$。

# 做法

首先，~~因为这是 DP Contest 里的题~~，发现这道题是一个 DP。

考虑怎样设计 DP 状态，很容易就可以得到一个二维的 DP 状态。设 $f(i,j)$ 表示前 $i$ 个数，第 $i$ 个填的是 $j$ 的方案数。

然后你仔细想一想就知道这个状态是不对的，因为它可能会有重复的情况。比如说 `<>` 会将 $(1,2,1)$ 也算入答案。

那么考虑怎样修改这个状态。我们需要认清需要什么，**其实，我们不用知道每个数是啥，只要知道排名即可。**

认识到这点之后，这个题就不困难了。设 DP 状态 $f(i,j)$ 表示前 $i$ 个数中，第 $i$ 个从小到大排名为 $j$ 的方案数。

这个的转移是容易的：

若 $s_{i-1}$ 为 `<`，则 $f(i,j)=\sum_{k=1}^{j-1}f(i-1,k)$。

若 $s_{i-1}$ 为 `>`，则 $f(i,j)=\sum_{k=j}^nf(i-1,k)$

这个用前缀和优化即可。

时间复杂度 $O(N^2)$。

## 程序

```cpp
const int maxn=3005,mod=1e9+7;
int n,dp[maxn][maxn],presum[maxn][maxn];
string s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>s;s=' '+s;
	dp[1][1]=1;
	for(int i=1;i<=n;i++)presum[1][i]=1;
	for(int i=2;i<=n;i++){
		if(s[i-1]=='<'){
			for(int j=1;j<=i;j++)dp[i][j]=presum[i-1][j-1];
		}
		else{
			for(int j=1;j<=i;j++)dp[i][j]=(presum[i-1][n]-presum[i-1][j-1]+mod)%mod;
		}
		for(int j=1;j<=n;j++)presum[i][j]=(presum[i][j-1]+dp[i][j])%mod;
	}
	cout<<presum[n][n]<<endl;
	return 0;
}
```

---

