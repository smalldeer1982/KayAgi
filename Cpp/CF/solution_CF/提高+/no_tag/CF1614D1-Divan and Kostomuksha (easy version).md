# Divan and Kostomuksha (easy version)

## 题目描述

This is the easy version of the problem. The only difference is maximum value of $ a_i $.

Once in Kostomuksha Divan found an array $ a $ consisting of positive integers. Now he wants to reorder the elements of $ a $ to maximize the value of the following function: 
$$
\sum_{i=1}^n \operatorname{gcd}(a_1, \, a_2, \, \dots, \, a_i),
$$
where  $\operatorname{gcd}(x_1, x_2, \ldots, x_k)$  denotes the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers  $ x_1, x_2, \ldots, x_k $ , and $ \operatorname{gcd}(x) = x $  for any integer  $ x$.

Reordering elements of an array means changing the order of elements in the array arbitrary, or leaving the initial order.

Of course, Divan can solve this problem. However, he found it interesting, so he decided to share it with you.

## 说明/提示

In the first example, it's optimal to rearrange the elements of the given array in the following order: $ [6, \, 2, \, 2, \, 2, \, 3, \, 1] $ :

$$
\operatorname{gcd}(a_1) + \operatorname{gcd}(a_1, \, a_2) + \operatorname{gcd}(a_1, \, a_2, \, a_3) + \operatorname{gcd}(a_1, \, a_2, \, a_3, \, a_4)\\ + \operatorname{gcd}(a_1, \, a_2, \, a_3, \, a_4, \, a_5) + \operatorname{gcd}(a_1, \, a_2, \, a_3, \, a_4, \, a_5, \, a_6)\\= 6 + 2 + 2 + 2 + 1 + 1 = 14.
$$
It can be shown that it is impossible to get a better answer.

In the second example, it's optimal to rearrange the elements of a given array in the following order:  $[100, \, 10, \, 10, \, 5, \, 1, \, 3, \, 3, \, 7, \, 42, \, 54]$.

## 样例 #1

### 输入

```
6
2 3 1 2 6 2```

### 输出

```
14```

## 样例 #2

### 输入

```
10
5 7 10 3 1 10 100 3 42 54```

### 输出

```
131```

# 题解

## 作者：EuphoricStar (赞：15)

## 题意

给定序列 $a_1,a_2,...,a_n$，要求重排 $a$，使得

$$\sum\limits_{i=1}^n \gcd(a_1,a_2,...,a_i)$$

最大。输出这个最大值。

## 思路

考虑 dp 求解。

设 $cnt_i$ 为序列中有因数 $i$ 的数字个数，例如如果 $a = [6,2,3,4]$，那么 $cnt_2$ 为 $2$。这个可以枚举每个 $a_i$ 的因数，$O(n \sqrt{w})$（$w$ 为值域，下同）求出。

然后是 dp 部分。设 $f_i$ 为 以 含有因数 $i$ 结尾的 重排后前缀 $\operatorname{gcd}$ 和 的最大值，初值为 $f_i = cnt_i \times i$（表示把含有因数 $i$ 的数排到前面）。转移枚举每个质数，$f_i = \max\limits_{j=1}{f_{i \times pr_j} + i \times (cnt_i - cnt_{i \times pr_j})}$。这里 $i \times (cnt_i - cnt_{i \times pr_j})$ 表示的是将含有因数 $i$ 的剩余元素添加到序列产生的新贡献，$cnt_{i \times pr_j}$ 由于在计算 $f_{i \times pr_j}$ 时已经算过一遍所以要减去。这部分的时间复杂度为 $O(w \log \log w)$。

最后答案为所有满足 $cnt_i = n$ 的 $f_i$ 的最大值，$cnt_i = n$ 说明 $i$ 为序列所有数的 $\operatorname{gcd}$ 的因数。

总时间复杂度为 $O(n \sqrt{w} + w \log \log w)$。

## 代码

```cpp
void prepare() {
	for (int i = 2; i <= 20000000; ++i) {
		if (!vis[i]) {
			pr[++tot] = i;
		}
		for (int j = 1; j <= tot && i * pr[j] <= 20000000; ++j) {
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				break;
			}
		}
	}
}

void solve() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		for (int j = 1; j * j <= x; ++j) {
			if (x % j == 0) {
				++cnt[j];
				if (j * j != x) {
					++cnt[x / j];
				}
			}
		}
	}
	for (int i = 20000000; ~i; --i) {
		f[i] = cnt[i] * i;
		for (int j = 1; j <= tot && i * pr[j] <= 20000000; ++j) {
			f[i] = max(f[i], f[i * pr[j]] + 1LL * i * (cnt[i] - cnt[i * pr[j]]));
		}
	}
	ll ans = 0;
	for (int i = 1; i <= 20000000; ++i) {
		if (cnt[i] == n) {
			ans = max(ans, f[i]);
		}
	}
	printf("%lld", ans);
}
```


---

## 作者：daniEl_lElE (赞：8)

看完此篇后可以尝试一下 D2。

## 思路

考虑 $dp_{i}$ 表示目前前缀 $\gcd=i$，前缀 $\gcd$ 和的最大值。

首先计算是 $i$ 的倍数的 $a_i$ 的数量，记为 $cnt_i$。

考虑转移，假设是从 $j$ 转移，转移到 $i$，容易发现多的 $a_i$ 数量为 $cnt_i-cnt_j$。所以转移式长这样：

$$dp_{i}=\max_{i|j}(dp_{j}+(cnt_i-cnt_j)\times i)$$

（令 $m=\max a_i$）看上去是 $m^2$ 的，其实是 $\sum_{i=1}^m\frac{m}{i}=O(n\ln n)$ 的，可以通过。

你放心，四秒呢。

## 代码

```cpp
#include <bits/stdc++.h>
#define double long double
#define int long long
using namespace std;
int cnt[5000005];
int f[5000005];
signed main(){
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++;
	for(int i=1;i<=5000000;i++){
		for(int j=i*2;j<=5000000;j+=i){
			cnt[i]+=cnt[j];
		}
	}
	for(int i=5000000;i>=1;i--){
		f[i]=cnt[i]*i;
		for(int j=i*2;j<=5000000;j+=i){
			f[i]=max(f[i],(cnt[i]-cnt[j])*i+f[j]);
		}
	}
	cout<<f[1];
	return 0;
} 
```

---

## 作者：laboba (赞：7)

观察数据范围，盲猜dp状态只与值域有关。事实上同时和 $n$  及值域相关不太可能，而只跟 $n$ 有关重排这件事是非常难处理的，所以最后的状态是设 $f_i$ 表示最后一个 $\gcd$ 是 $i$ 时的最大值，其中 $n$ 个数不一定都用完。

设重排后的序列为 $q$ ，经过分析可以贪心出这样一个性质：对任意 $\gcd(q_1,q_2,...,q_i)$， $q_{i+1},q_{i+2}...,q_n$ 均不是它的倍数。感性理解下，$\gcd$ 序列显然是单调不增的，如果有一个 $j>i$ 满足 $q_j$ 是前 $i$ 个数 $\gcd$ 的倍数，把 $j$ 放到 $i+1$ 位结果只增不减。

于是根据这个性质，转移方程可以得出：$f_i=\max(f_j+(num_i - num_{j})\times i),i\mid j$ 其中 $num$ 表示 $a$ 中能被 $i$ 整除的数的个数。方程的含义是枚举上一个不同于 $i$ 的 $\gcd$ 为 $j$，设  $\gcd(q_1,q_2....,q_k)=j$，则在 $j+1$ 至 $f_i$ 所在位置全部填上 $a$ 中是 $i$ 的倍数但不是 $j$ 的倍数的数，这段的贡献是 $(num_i - num_{j})\times i$。

UPD:修改了一处笔误。

```cpp
#include<cstdio>
#include<algorithm> 
using namespace std;
const int N=100100,A=5001000;
int a[N],num[A];
long long f[A];
int n;
int main(){
	scanf("%d",&n);
	int m=0;//m是值域 
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),num[a[i]]++,f[a[i]]+=a[i],m=max(m,a[i]);
	for(int i=1;i<=m;i++){
		for(int j=i*2;j<=m;j+=i)num[i]+=num[j];
	}
	for(int i=m;i>=1;i--){
		for(int j=i*2;j<=m;j+=i){
			f[i]=max(f[i],f[j]+1ll*(num[i]-num[j])*i);
		}
	}
	long long ans=0;
	for(int i=1;i<=m;i++)ans=max(ans,f[i]);//不知道gcd(a[1],a[2]...a[n])是多少，所以要枚举 
	printf("%lld",ans);
}
```


---

## 作者：orz_z (赞：2)

## 题目大意

给定序列 $a_1,a_2,...,a_n$，要求重排 $a$，使得

$$
\sum\limits_{i=1}^n \gcd(a_1,a_2,...,a_i)
$$



最大。

输出这个最大值。

## 解题思路

显然，一道 `dp`。

设 $cnt_i$ 表示数组 $a$ 中是 $i$ 的倍数的元素个数，$dp_i$ 表示时能得到已含有因数 $i$ 结尾排列能获得的最大值。

此时有转移方程
$$
dp_i=\max_{j=1}{f_{i \times pri_j} + i \times (cnt_i - cnt_{i \times pri_j})}
$$
最后答案为满足 $cnt_i=n$ 的 $dp_i$ 的最大值。

求 $cnt$ 可先筛出所有质数，再枚举 $i$ 和质数集 $pri$，计算 $cnt_i$。

时间复杂度 $\mathcal O(w \log \log w)$，其中 $w$ 为值域。

具体实现见代码。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

const int _ = 2e7 + 1;

int n;

int ans;

int cnt[_ + 7];

int dp[_ + 7];

bool vis[_];

vector<int> primes;

void init()
{
    for (int i = 2; i < _; ++i)
    {
        if (!vis[i])
            primes.push_back(i);
        for (auto p : primes)
        {
            if (p * i > _)
                break;
            vis[p * i] = 1;
            if (i % p == 0)
                break;
        }
    }
}

signed main()
{
    init();
    n = read();
    for (int i = 1, x; i <= n; ++i)
        cnt[read()]++;
    for (auto p : primes)
        for (int j = _ / p; j >= 1; --j)
            cnt[j] += cnt[j * p];
    for (int i = _ - 1; i >= 1; --i)
    {
        dp[i] = cnt[i] * i;
        for (auto p : primes)
        {
            int j = p * i;
            if (j > _)
                break;
            dp[i] = max(dp[i], dp[j] + i * (cnt[i] - cnt[j]));
        }
        if (cnt[i] == n)
            ans = max(ans, dp[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

设 $dp_i$ 表示当前 $\gcd=i$ 时的最大值。由 $\gcd$ 的性质，要从 $j$ 转移至 $i$ 的条件为 $i$ 是 $j$ 的因子。设 $c_i$ 表示 $a$ 中元素为 $i$ 倍数的个数。那么有初始化 $dp_i=c_i\cdot i$，转移为：$dp_i\gets\displaystyle\max_{i\mid j}dp_j+(c_i-c_j)i$，就是把 $i\sim j$ 之间为 $i$ 的倍数的那些数放在中间，每一个做出 $i$ 的贡献。最后答案为 $dp_1$。

预处理 $c$ 与 dp 的转移运算量皆为 $\displaystyle\sum_{i=1}^{V}\frac{V}{i}\approx V\ln V$。

于是时间复杂度：$O(V\ln V)$。

---

## 作者：残阳如血 (赞：1)

### $\textbf{Description}$

求对序列 $\{a_n\}$ 进行重排，最大化
$$
\sum\limits_{i=1}^{n}{\gcd(a_1,a_2,\dots,a_{i})}
$$

### $\textbf{Solution}$

令 $h(x)=\gcd(a_1,a_2,\dots,a_x)$。

如果确定了第一个数 $a_1$，则 $\forall\,i\in[2,n]$，有 $h(i)\le h(i-1)$ 且 $h(i)\mid a_1$。

考虑 $\text{DP}$，设 $f(i)$ 表示第一个数为 $i$ 时的答案最大值。

> PS：初始条件：$f(1)=n$。

从小到大考虑 $i$，$i$ 可以由其一因数 $j$ 转移而来：
$$
f(i)=\max_{j\,\mid\,i}\{f(j)+\text{cnt}(i)\times(i-b)\}
$$
其中 $\text{cnt}(i)$​ 表示 $i$​ 及其倍数在 $a$​​ 数组中的数量。

预处理因数，可以做到时间复杂度 $O(n\ln n)$。

---

## 作者：WhisperingWillow (赞：0)

[D1](https://www.luogu.com.cn/problem/CF1614D1) [D2](https://www.luogu.com.cn/problem/CF1614D2)

[CF1614D1](https://codeforces.com/problemset/problem/1614/D1) [CF1614D2](https://codeforces.com/problemset/problem/1614/D2)

考虑设计 DP。

设 $f_i$ 表示目前 $\gcd$ 为 $i$ 的最大 $\gcd$ 和，记 $cnt_i$ 表示 $i$ 的倍数有多少个。

有转移 $f_i=\max_{i|j}f_j+(cnt_i-cnt_j)i$，$f_i$ 的初始值为  $icnt_i$。

直接做是 $\mathcal O(n\ln n)$ 的，可以通过 D1。

[Sumission](https://codeforces.com/problemset/submission/1614/244560459)

考虑优化。

发现 $cnt_i$ 可以用狄利克雷后缀和来解决，复杂度 $\mathcal O(n\ln \ln n)$。 

发现 $f$ 的转移太慢了。

考虑贪心，发现若 $\dfrac{j}{i} \in \text{prime}$ 转移一定是最优的。

时间复杂度为 $\mathcal O(n\ln \ln n)$，可以通过 D2。

[Sumission](https://codeforces.com/problemset/submission/1614/244630080)

---

## 作者：elbissoPtImaerD (赞：0)

前缀 $\gcd$ 的变化次数是 $\mathcal{O(\log V)}$ 的。

我们考虑对每一次极长的一段进行 dp。

可以设状态：$f_i$ 表示 $\gcd$ 的当前末尾极长不变的段值为 $i$ 的最长序列的最大价值。

每次 $\gcd$  一定会变成其因数，有转移：$f_i=\max \limits_{j=1}f_{i\times p_j} + i \times (g_i-g_{i \times p_j})$，含义时把 $\gcd$ 中的素数一个一个拔掉，相当于在序列末尾放上是 $i$ 倍数但不是 $i\times p_j$ 的倍数的那些数，每次加上对应改变的贡献。

其中 $p_j$ 表示第 $j$ 小的素数，$g_i=\sum \limits_{j=1}^n[i|a_j]$。

如何求解 $g$：

不妨初始时让 $g_i = \sum \limits_{j=1}^n[i=a_j]$。

考虑 $x|y$ 的 $g_y$ 如何对 $g_x$ 贡献，想到把 $\frac yx$ 的素数一个一个拔掉即可。

$f$ 的 dp 和 $g$ 的转移均是 $\mathcal{O(\sum\limits_{p\in P}\lfloor\frac np\rfloor)} = \mathcal{O(n\ln n)}$ 的。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1614/submission/228507210)

---

## 作者：SunnyYuan (赞：0)

## 前言

基本思路，zltqwq 大佬已经讲的很清楚了，我想补充一下怎么转移 DP。

~~被 `long long` 卡了 6 发。~~

## 思路

先说说基本思路。

首先我们计算出 $c_i$ 表示所有数字中有因数 $i$ 的数字个数，设 $f_i$ 表示以 $i$ 为**公因数**时可以贡献的和（不包括不能整除 $i$ 的）。

最开始时 $f_i = c_i \cdot i$。

转移方程为 $f_{i} = f_{i\cdot p} + i\cdot (c_i - c_{i \cdot p})$。

这表示啥呢？这个实际上是先将 $c\cdot p$ 的倍数放在前面，然后将 $c_{i} - c_{i\cdot p}$ 个数字放在后面，因为 $i$ 的倍数中包含 $i\cdot p$ 的倍数，所以要减掉，这样保证了前面的 $\gcd$ 是 $c\cdot p$，后面的是 $\gcd$ 是 $c$，目的就是让和最大化。

最后的答案就是 $ans = \max\limits_{c_i = n} f_i$。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: Divan and Kostomuksha (easy version)
| OJ:      Luogu
| URL:     https://www.luogu.com.cn/problem/CF1614D1
| When:    2023-10-20 20:25:20
| 
| Memory:  1000 MB
| Time:    4000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

const int N = 100010, M = 5000010;

int prime[M], cnt;
bool inp[M];

void getprime() {
    inp[1] = inp[0] = 1;

    for (int i = 2; i < M; i++) {
        if (!inp[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && prime[j] * i < M; j++) {
            inp[prime[j] * i ] = true;
            if (i % prime[j] == 0) break;
        }
    }
    
}

int n, a[N];
i64 f[M];
int c[M];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getprime();

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= a[i] / j; j++) {
            if (a[i] % j == 0) {
                c[j]++;
                if (a[i] / j != j) c[a[i] / j]++;
            }
        }
    }
    for (int i = 0; i < M; i++) f[i] = 1ll * c[i] * i;

    for (int i = M - 1; i >= 1; i--) {
        for (int j = 1; j <= cnt && 1ll * i * prime[j] < M; j++) {
            f[i] = max(f[i], f[i * prime[j]] + 1ll * i * (c[i] - c[i * prime[j]]));
        }
    }
    i64 ans = 0;
    for (int i = 0; i < M; i++)
        if (c[i] == n)
            ans = max(ans, f[i]);
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：intel_core (赞：0)

令 $b_i=\gcd(a_1,a_2,\cdots,a_i)$，那么有 $b_{i+1}|b_i$。

贪心的，如果存在 $i<j$ 满足 $b_i|a_j$，那么可以交换 $a_i,a_j$。

令 $f_i$ 表示把为 $i$ 的倍数的 $a$ 都排进数列中，此时已确定 $\sum b_i$ 的最大值。

考虑转移，由前面的分析，如果 $f_i$ 可以从 $f_j$ 转移过来，那么必须满足 $i|j$。

所以 $f_i=\max\{c_i\times i,\max\limits_{i|j}\{f_j+(c_i-c_j)\times i\} \}$。

这里 $c_i$ 表示 $\{a_n \}$ 中 $i$ 的倍数的个数。

求 $c_i$ 和 $f_i$ 都可以在 $O(n \sqrt{V})$ 时间内完成，可以通过 $\text{D1}$。

```cpp
#pragma GCC optimize("Ofast")
#pragma GCC comment("sse,sse2,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10;
const int MR=2e7+10;
#define ll long long
int n,a[NR],buc[MR];ll f[MR];

int prime[MR],vis[MR],tot;
void init(){
	for(int i=2;i<=2e7;i++){
		if(!vis[i])prime[++tot]=i;
		for(int j=1;j<=tot&&i*prime[j]<=2e7;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}	
}

signed main(){
	cin>>n;init();
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(int j=1;j<=sqrt(a[i])+0.5;j++)
			if(a[i]%j==0){
				if(j*j==a[i])buc[j]++;
				else buc[j]++,buc[a[i]/j]++;
			}
	}
	for(int i=2e7;i>=1;i--){
		f[i]=1ll*i*buc[i];
		for(int j=1;j<=tot&&i*prime[j]<=2e7;j++)f[i]=max(f[i],f[i*prime[j]]+1ll*(buc[i]-buc[i*prime[j]])*(1ll*i));
	}	
	ll ans=0;
	for(int i=1;i<=2e7;i++)ans=max(ans,f[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1614D1 题解

## 题目大意

给定一个有 $n$ 个数的数组 $a$，现在可以让你任意重排这个 $a$ 数组，请求出 $\sum_{i=1}^{n}\gcd(a_1,a_2,\dots,a_i)$ 的最大值。

数据范围保证：$n\le5\times10^6,a_i\le 2\times 10^7$。

## 思路分析

约定用 $x$ 表示满足 $\gcd(a_1,a_2,\dots,a_x)>1,\gcd(a_1,a_2,\dots,a_{x+1})=1$ 的 $x$。

显然本题考虑 dp，用 $dp_i$ 表示重排 $a$ 后满足 $i\mid \gcd(a_1,a_2,\dots,a_x)$ 时 $\sum_{i=1}^x \gcd(a_1,a_2,\dots,a_x)$ 的最大值。

用 $cnt_i$ 表示 $a$ 中满足 $i\mid a_i$ 数的个数。

那么 dp 的边界条件就应该是 $dp_i=i\times cnt_i$，因为最开始的时候肯定是把 $cnt_i$ 个 $i$ 的倍数放在最前面，其他的贡献还没有考虑。

然后考虑 dp 的状态转移，状态转移方程应该是：
$$
dp_i=\max_{i\mid j} (dp_j+i\times(cnt_i-cnt_j))
$$
这个方程的含义是，从每个 $i$ 的倍数 $j$ 处转移，考虑前面填的数的 $\gcd$ 是 $i$ 的某个倍数的情况（也就是 $dp_j$ ），再加上后面 $a$ 中所有满足 $i \mid x$ 且 $j\not \mid x$ 的数放在后面，这部分的数的 $\gcd$ 是 $i$，而一共有 $cnt_i-cnt_j$ 个，这就是状态转移方程的含义。

然后考虑统计答案，$dp_i$ 可能成为答案的充分必要条件是其对应的 $x=n$，也就是 $cnt_i=n$。

所以可以写出统计答案的式子。
$$
ans=\max_{i=1} (dp_i\times[cnt_i=n])
$$


这个做法的时间复杂度分为两部分 ($w=\max(a_i)\le5\times 10^6$，表示 $a$ 的值域)。

1. 读入并预处理 $cnt$ 数组，复杂度 $\Theta(n\sqrt{w})$。
2. 进行 dp 的状态转移，复杂度 $\Theta(\sum_{i=1}^w\dfrac{w}{i})=\Theta(w\ln w)$。

总的时间复杂度是 $\Theta(n\sqrt w+w\ln w)$，可以通过本题。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+1,MAXV=5e6+1;
int a[MAXN],cnt[MAXV],n,w;
long long dp[MAXV],ans; //注意开long long 
signed main() {
	scanf("%d",&n);
	for(register int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		w=max(w,a[i]);
		for(register int j=1;j*j<=a[i];++j) {
			if(a[i]%j==0) {
				//预处理a[i]的每个因数并统计进cnt里面 
				++cnt[j];
				if(j*j<a[i]) ++cnt[a[i]/j];
			}
		}
	}
	for(register int i=w;i>0;--i) {
		dp[i]=(long long)i*(long long)cnt[i]; //dp边界条件 
			if(dp[i]) {
			//剪枝，如果本身cnt[i]=0也就是没有i的倍数就不考虑 
			  	for(register int j=i;j<=w;j+=i) {
			  		//考虑i的每个倍数 
					if(dp[j]) {
						//同理，剪枝*2 
						dp[i]=max(dp[i],dp[j]+(long long)i*((long long)cnt[i]-(long long)cnt[j])); 
					}
			}
		} 
		if(cnt[i]==n) ans=max(ans,dp[i]); //统计答案 
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

