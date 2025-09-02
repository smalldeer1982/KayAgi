# Candies

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_m

$ N $ 人の子供たちがいます。 子供たちには $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。

子供たちは $ K $ 個の飴を分け合うことにしました。 このとき、各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について、子供 $ i $ が受け取る飴の個数は $ 0 $ 以上 $ a_i $ 以下でなければなりません。 また、飴が余ってはいけません。

子供たちが飴を分け合う方法は何通りでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。 ただし、$ 2 $ 通りの方法が異なるとは、ある子供が存在し、その子供が受け取る飴の個数が異なることを言います。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 100 $
- $ 0\ \leq\ K\ \leq\ 10^5 $
- $ 0\ \leq\ a_i\ \leq\ K $

### Sample Explanation 1

子供たちが飴を分け合う方法は、次の $ 5 $ 通りです。 各数列において、$ i $ 番目の要素は子供 $ i $ が受け取る飴の個数を表します。 - $ (0,\ 1,\ 3) $ - $ (0,\ 2,\ 2) $ - $ (1,\ 0,\ 3) $ - $ (1,\ 1,\ 2) $ - $ (1,\ 2,\ 1) $

### Sample Explanation 2

子供たちが飴を分け合う方法が存在しない場合もあります。

### Sample Explanation 3

子供たちが飴を分け合う方法は、次の $ 1 $ 通りです。 - $ (0,\ 0) $

### Sample Explanation 4

答えを $ 10^9\ +\ 7 $ で割った余りを出力することを忘れずに。

## 样例 #1

### 输入

```
3 4
1 2 3```

### 输出

```
5```

## 样例 #2

### 输入

```
1 10
9```

### 输出

```
0```

## 样例 #3

### 输入

```
2 0
0 0```

### 输出

```
1```

## 样例 #4

### 输入

```
4 100000
100000 100000 100000 100000```

### 输出

```
665683269```

# 题解

## 作者：FelFa_1414666 (赞：19)

[atcoder 题目传送门](https://atcoder.jp/contests/dp/tasks/dp_m)，经典的 **dp + 前缀和优化**。

[更好的阅读体验](https://www.luogu.com.cn/blog/xesssb10108899/solution-at4534)。

------------

### 题意

有 $n$ 个不同的小朋友和 $k$ 个相同的糖，给每个小朋友分配若干个糖且糖要分配完，每个小朋友分配糖的上限个数为 $a_i$，求分配方案总数。

- $1\le n\le 100$

- $1\le k\le 10^5$

- $1\le a_i\le k$

------------

### 思路

- 朴素的 dp 状态：$dp(i,j)$ 表示考虑到第 $i$ 个小朋友，当前已经用掉 $j$ 个糖的方案数。

- 转移方程：
$$dp(i,j)=\sum\limits_{k=\max(0,j-a_{i-1})}^jdp(i-1,k)$$

这样一来转移的复杂度是 $O(k)$，总复杂度为 $O(nk^2)$，会超时。这时候我们进行优化，就必须要观察转移方程的特点了。

- 优化：**发现公式里每个 dp 值都由上一行中一段连续的 dp 值之和转移而来**，可以**前缀和**优化转移，每次用 $sum$ 数组预处理上一行 $dp$ 的前缀和，可以 $O(1)$ 地求出连续一段 dp 值之和并转移。具体处理如下：
$$sum(i)=\sum\limits_{j=0}^idp(i-1,j)$$

时间复杂度：$O(nk)$

空间复杂度：$O(nk)$


------------

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
const ll MOD=1e9+7;
int n,m,a[105];
ll dp[105][100005],sum[100005];
ll getsum(int l,int r)//前缀和
{
	return (l==0?sum[r]:(sum[r]+MOD-sum[l-1])%MOD);
}
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>a[i];
	dp[0][0]=1ll;
	for(int i=1;i<=n;i++)
	{
		sum[0]=dp[i-1][0];//处理上一行dp的前缀和
			for(int k=1;k<=m;k++)
				sum[k]=(sum[k-1]+dp[i-1][k])%MOD;
		for(int j=0;j<=m;j++) //按公式转移
			dp[i][j]=getsum(max(0,j-a[i-1]),j);
	}
	cout<<dp[n][m]<<endl;
	return 0;
}
```
其实我的 dp 公式是**从前面的值转移到当前值**的。也有其他的选手喜欢**用当前值更新后面值**的转移方式。这样的话优化就会运用到一个**差分数组**，其实和前缀和是异曲同工的。

希望题解对你有帮助！

---

## 作者：云浅知处 (赞：14)

题目其实就是求符合以下条件的序列 $(x_1,x_2,\cdots,x_n)$ 的个数：

- $0\le x_i\le a_i$
- $\sum_{i=1}^n x_i=K$

考虑 dp。设 $F(i,j)$ 为前 $i$ 个数加起来得到 $j$ 的方案数，枚举最后一个数是多少可以得到转移方程：

$$
F(i,j)=\sum_{x=0}^{a_i}F(i-1,j-x)
$$

初始状态即为 $F(1,j)=[j\le a_1]$。

直接转移需要 $O(n)$ 的时间，时间复杂度将为 $O(n^2K)$，稳 TLE。

注意到如果做一个前缀和，记 $S(i,j)$ 为：

$$
S(i,j)=\sum_{x=0}^{j}F(i,j)
$$

那么转移方程就是

$$
F(i,j)=S(i-1,j)-S(i-1,j-a_i-1)
$$

$$
S(i,j)=S(i,j-1)+F(i,j)
$$

这样就得到了一个 $O(nK)$ 的算法。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>

#define int long long
const int mod=1e9+7;
const int MK=1e5+5;
const int MN=105;

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

int a[MN],dp[MN][MK],sum[MN][MK],n,K;

signed main(void){

    n=read(),K=read();
    for(int i=1;i<=n;i++)a[i]=read();
    dp[1][0]=sum[1][0]=1;for(int i=1;i<=K;i++)dp[1][i]=(i<=a[1]),sum[1][i]=dp[1][i]+sum[1][i-1];
    for(int i=2;i<=n;i++){
        dp[i][0]=sum[i][0]=1;
        for(int j=1;j<=K;j++){
            if(j<=a[i])dp[i][j]=sum[i-1][j]%mod;
            else dp[i][j]=(sum[i-1][j]-sum[i-1][j-a[i]-1]+mod)%mod;
            sum[i][j]=(sum[i][j-1]+dp[i][j])%mod;;
        }
    }
    cout<<dp[n][K]<<endl;

    return 0;
}
```




---

## 作者：chlchl (赞：4)

AT 的 dp 题单前一半是 J 组难度，后一半是 S 组。这题应该是 S 组最简单， ~~最 naive~~ 的 一道了。

## 题意简述
$k$ 个糖果分成 $n$ 个**不同的堆**（顺序不同算两种方案），每堆不能少于 $0$ 个、超过 $a_i$ 个。问有多少种分堆方案。结果对 $10^9+7$ 取模。

## 做法
显然考虑 dp。

设 $f_{i,j}$ 为前 $i$ 堆一共分了 $j$ 颗糖果的方案数。

转移肯定枚举第 $i$ 堆放了多少个，然后从前 $i-1$ 堆转移过来，即 $f_{i,j}=\sum_{l=1}^{a_i}f_{i-1,j-l}$。

这样，总时间复杂度 $O(n^2k)$，恭喜 TLE。

注意到求的是方案数，用到的是连续一段区间的和，显然考虑~~线段树~~前缀和。

我们记 $sum_{i,j}=\sum_{l=1}^{j}f_{i,l}$。则状态转移方程可以改写为 $f_{i,j}=sum_{i-1,j}-sum_{i-1,j-a_i-1}$。

发现可以在每一次求完整个 $f_{i,j},j\in[0,k]$ 后直接计算前缀和，所以前缀和可以把 $i$ 那一维去掉。

再发现 $f_i$ 的转移只与 $f_{i-1}$ 有关，所以同样可以把 $i$ 那一维去掉。

最终时间复杂度 $O(nk)$，空间复杂度 $O(k)$，可以顺利通过本题。

空间优化随意，优不优都能过。

前缀和记得判断是否越界，避免 RE。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll MOD = 1e9 + 7;
const int N = 1e5 + 10;
int n, k, a[110];
ll sum[N], f[N];

int main(){
	scanf("%d%d", &n, &k);
	for(int i=1;i<=n;i++)
		scanf("%d", &a[i]);
	f[0] = 1;
	for(int i=1;i<=n;i++){
		sum[0] = f[0];
		for(int j=1;j<=k;j++)
			sum[j] = (sum[j - 1] + f[j]) % MOD;
		for(int j=0;j<=k;j++)
			f[j] = ((sum[j] - (j <= a[i] ? 0 : sum[j - a[i] - 1])) % MOD + MOD) % MOD;//注意 j 与 a[i] 的大小关系
	}
	printf("%lld\n", f[k]);
	return 0;
}
```


---

## 作者：AmamiyaYuuko (赞：3)

我们可以很 naive 的写出一个朴素 DP：设 $f(i, j)$ 为前 $i$ 个人分了 $j$ 块糖的方案数，转移为 $f(i, j) = \sum \limits_{t = 0}^{a_i} f(i - 1, j - t)$。这样做的话是 $O(nk^2)$ 的。

观察这个式子，不难发现 $f(i, j)$ 只跟前一段状态的一段区间有关，可以想到用前缀和优化。设 $s_{i, j} = \sum \limits_{j = 0}^k f(i, j)$，于是状态转移方程可以写成 $f(i, j) = s(i - 1, j) - s(i - 1, j - a_i - 1)$。

注意到 $j - a_i - 1$ 可能会导致 RE，上一篇题解中也有这个问题，我们可以将 $s$ 的下标统一加 $1$ 来解决。~~没有 UB 总比有好~~

代码：

```cpp
int main() {
    read(n), read(k);
    f[0][0] = 1;
    for (int i = 1; i <= k + 1; ++i)    s[i] = 1;
    for (int i = 1, a; i <= n; ++i) {
        read(a);
        if (i == 1) {
            for (int j = 0; j <= a; ++j)    f[i][j] = 1;
        } else {
            for (int j = 0; j <= k; ++j) {
                f[i][j] = ((s[j + 1] - s[std::max(0, j - a)]) % mod + mod) % mod;
                f[i][j] %= mod;
            }    
        }
        s[1] = 1;
        for (int j = 2; j <= k + 1; ++j)    s[j] = s[j - 1] % mod + f[i][j - 1] % mod, s[j] %= mod;   
    }
    printf("%lld\n", (f[n][k] % mod + mod) % mod);
    return 0;
}
```

---

## 作者：Acerkaio (赞：2)

### [题目](https://www.luogu.com.cn/problem/AT4534)

### 思路

DP。

30 分做法（部分分做法）：

我们设 $f_{i,j}$ 为前 $i$ 个人分 $j$ 颗糖的方案数，则有：

$$f_{i,j} =  \sum_{x = 0}^{a_i}f_{i - 1,j - x} $$

正解做法：

我们最头疼的是原来状态转移方程的这个大型运算：

$$\sum_{x = 0}^{a_i}f_{i - 1,j - x}$$

我们不妨设 

$$sum_{i,j} = \sum_{x = 0}^{j}f_{i,x}$$

那么我们就可以得到 sum 的转移方程

$$sum_{i,j} = sum_{i,j - 1} + f_{i,j}$$

所以就可以优化原来的方程为

$$f_{i,j} = sum_{i - 1,j} - sum_{i - 1, j - a_{i} -  1}$$

详细看代码。
### CODE

```
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n, k, a[1000001], f[101][100001];

signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		f[i][0] = 1; //初始化
	}
	for (int j = 1; j <= n; j++) {
		f[1][j] = (j <= a[1]);
	}
	for (int i = 2; i <= n; i++) {
		for (int x = 0; x <= a[i]; x++) {
			for (int j = x; j <= k; j++) {
				if(j == 0)
					f[i][j] = f[i - 1][j - x]; //直接转移
				else
					f[i][j] += f[i - 1][j - x];
			}
		}
	}
	cout << f[n][k];
	return 0;
}
```


---

## 作者：_Kouki_ (赞：1)

## 题目解释
求出方案数 $( x_1 , x_2 , x_2 ... x_n )$  使得 $ x_i \le a_i (i\leq n) $ 并且 $\sum_{i=1}^{n} x_i \le k$。    
## 题目思路

我们可以很快想出一种暴力的方法。    
$ \mathit f_{i,j} $ 表示 前 $ i $ 个数加起来等于 $j $ 的方案数。   
$$ \mathit f_{i,j} = \sum_{x=1}^{a_i} \mathit f_{i-1,j-x} $$

但是这妥妥的 TLE ，因此我们发现了此方程进行了多次的重复运算。 

$ \mathit f_{i-1,j-x} $  被重复计算，因此使用**前缀和优化**。

$$ \mathit s_{i,j}=\mathit s_{i,j-1}+\mathit f_{i,j} $$ 

即 

$$ \mathit s_{i,j}=\sum_{j=1}^{a_i} \mathit f_{i,j} $$    


$$\mathit f_{ i , j }  = \mathit s_{ i - 1 , j }-\mathit s_{ i - 1 , j - a_i - 1 }$$   

## 题目代码

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const ll N=1e2+50;
const ll M=1e5+50;
const ll mod=1e9+7;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

ll n,k;
ll a[N],f[N][M],s[N][M];

int main()
{
	n=read(),k=read();
	for(int i=1;i<=n;++i) a[i]=read();
	f[1][0]=1; //一个人分0块 答案为1
	s[1][0]=1; // 初始化
	for(int i=1;i<=k;++i){
		f[1][i]=(i<=a[1])?1:0;
		s[1][i]=s[1][i-1]+f[1][i];
	}
	for(int i=2;i<=n;++i){
		f[i][0]=1; //同理 初始化
		s[i][0]=1; //
		for(int j=1;j<=k;++j){
			f[i][j]=(j>a[i])?((s[i-1][j]-s[i-1][j-a[i]-1]+mod)%mod):(s[i-1][j]%mod);
			s[i][j]=(s[i][j-1]+f[i][j])%mod;
		}
	}
	printf("%lld\n",f[n][k]%mod);
	return 0;
}

```

---

