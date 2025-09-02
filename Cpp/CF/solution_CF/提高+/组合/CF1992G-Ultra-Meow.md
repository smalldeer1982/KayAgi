# Ultra-Meow

## 题目描述

K1o0n gave you an array $ a $ of length $ n $ , consisting of numbers $ 1, 2, \ldots, n $ . Accept it? Of course! But what to do with it? Of course, calculate $ \text{MEOW}(a) $ .

Let $ \text{MEX}(S, k) $ be the $ k $ -th positive (strictly greater than zero) integer in ascending order that is not present in the set $ S $ . Denote $ \text{MEOW}(a) $ as the sum of $ \text{MEX}(b, |b| + 1) $ , over all distinct subsets $ b $ of the array $ a $ .

Examples of $ \text{MEX}(S, k) $ values for sets:

- $ \text{MEX}(\{3,2\}, 1) = 1 $ , because $ 1 $ is the first positive integer not present in the set;
- $ \text{MEX}(\{4,2,1\}, 2) = 5 $ , because the first two positive integers not present in the set are $ 3 $ and $ 5 $ ;
- $ \text{MEX}(\{\}, 4) = 4 $ , because there are no numbers in the empty set, so the first $ 4 $ positive integers not present in it are $ 1, 2, 3, 4 $ .

## 样例 #1

### 输入

```
5
2
3
4999
5
1```

### 输出

```
12
31
354226409
184
4```

# 题解

## 作者：绿化三 (赞：14)

## CF1992G 题解

个人认为不错的一道组合数题。

题意简介：记 $\operatorname{MEX}(S, k)$ 为集合 $S$ 中未出现的第 $k$ 个**正整数**，集合 $a$ 为排列 $1 \sim n$，对于集合 $a$ 的所有子集 $b$，求 $\operatorname{MEX}(b, \left| b\right| + 1)$ 的和。

第一步，对于一个子集 $b$，先不考虑集合 $b$ 中元素的影响，$\operatorname{MEX}(b, \left| b \right| + 1)$（下称 $\operatorname{MEX}$ 值）的初始值为 $\left| b\right| + 1$，故对于所有大小为 $\left| b\right|$，总共的初始值为 $(\left| b\right| + 1)\operatorname{C}_n^{\left| b\right|}$。

第二步，集合 $b$ 中元素对 $\operatorname{MEX}$ 值的影响可以看作在初始值基础上的额外贡献。贡献取决于元素的分布，若是在 $1\sim (\left| b\right| + 1)$ 中分布有 $1$ 个值，就会对结果产生 $1$ 的贡献，若是在 $1\sim (\left| b\right| + 2)$ 中分布有 $2$ 个值，就会产生 $2$ 的贡献（较小值会先使得 $\operatorname{MEX}$ 值加 $1$ 变为，此时 $\left| b \right| + 2$ 一定大于较大值；依次类推，若是在 $1\sim \left| b\right| + m$ 中分布有 $m$ 个值，就会产生 $m$ 的贡献（第 $k$ 小一定小于等于 $\left| b \right| + k$）。接下来我们只要求出所有相同大小，相同贡献的不用子集个数即可。

对于集合大小为 $\left| b \right|$ 的子集，贡献为 $1$ 的有    $\operatorname{C}_{\left| b \right| + 1}^{1} \operatorname{C}_{n-(\left| b \right| + 2)}^{\left| b \right| -1}$ 种（从 $1\sim \left| b \right| + 1$ 中选一个，此时 $\operatorname{MEX}$ 值为 $\left| b \right| + 2$，还得从 $(\left| b \right| + 3)\sim n$ 中取 $\left| b \right| -1$ 个数），贡献为 $2$ 的有 $\operatorname{C}_{\left| b \right| + 2}^{2} \operatorname{C}_{n-(\left| b \right| + 3)}^{\left| b \right| -2}$，贡献为 $m$ 的有 $\operatorname{C}_{\left| b \right| + m}^{m} \operatorname{C}_{n-(\left| b \right| + m + 1)}^{\left| b \right| - m}$。

数据保证 $O(n^2)$ 不会超时，组合数可用预处理的阶乘逆元计算。



一些细节：
1. $\operatorname{MEX}$ 值会超过 $n$，即 $\left| b \right| + m$ 超过 $n$。这时就应该只在前 $n$ 项中选取，即 $\operatorname{C}_{\min(\left| b \right| + m,n)}^{m} \operatorname{C}_{n - \min(\left| b \right| + m + 1,n)}^{\left| b \right| - m}$。
2. 在前 $\min(\left| b \right| + m,n)$ 项选完后，要保证后续项能放下剩余的元素个数。具体见代码。
3. 空集也是子集。
```cpp
#include<bits/stdc++.h>
#define YES cout << "Yes" << endl
#define NO cout << "No" << endl
#define int long long
using namespace std;
int T;
int n;
int mod = 1e9 + 7;
int fact[20003] = {1};  
int inv[20003];
int ans;
int min(int a, int b){return a < b ? a : b;}
int max(int a, int b){return a > b ? a : b;}
int ksm(int x, int y)
{
	int ans = 1;
	while(y)
	{
		if(y & 1)
			ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}
int C(int n, int m)
{
	return fact[n] * inv[m] % mod * inv[n - m] % mod;
}
signed main()
{
	for(int i = 1; i <= 5000; i ++)
	{
        fact[i] = fact[i - 1] * i % mod;
    }
    inv[5000] = ksm(fact[5000], mod - 2) % mod;
    for(int i = 4999; i >= 0; i --)
    {
        inv[i] = inv[i + 1] * (i + 1) % mod;
    }

	cin >> T;
	while(T --)
	{
		cin >> n;
		ans = 0;
		for(int i = 0; i <= n; i ++)
		{
			ans = (ans + (i + 1) * C(n, i) % mod) % mod;
			for(int j = 1; j <= i; j ++)
			{
				if(j + (n - min(i + j, n)) < i) 
				continue;
				ans = (ans + j * C(min(i + j, n), j) % mod * C(n - min(i + j + 1, n), i - j) % mod) % mod;
			}
		}
		cout << ans << endl;
	}
}
```

---

## 作者：Alex_Wei (赞：12)

### [CF1992G Ultra-Meow](https://www.luogu.com.cn/problem/CF1992G)

枚举长度 $L$ 和 $\mathrm{MEX}(b, L + 1)$ 的值 $v$，则共有 $L$ 个小于 $v$ 的数没有出现在 $b$ 中。可知序列 $b$ 共有 $v - L - 1$ 个数小于 $v$，$2L + 1 - v$ 个数大于 $v$。因此答案为
$$
\sum_{L = 0} ^ n \sum_{v = L + 1} ^ {2L + 1} v \binom {\min(n, v - 1)} {v - L - 1} \binom {\max(0, n - v)} {2L + 1 - v}
$$
算法的时间复杂度 $\mathcal{O}(n ^ 2)$。[代码](https://codeforces.com/contest/1992/submission/270567131)。

*本题解将同步发表于清华大学学生算法协会微信公众号「酒井算协」。

---

## 作者：nb_jzy (赞：4)

~~AK Div3 了~~
# 题意
定义 $\text{MEX}(S,k)$ 表示子集 $S$ 中第 $k$ 个未出现过的数字。

求一个 $1\sim n$ 的排列中，共 $2^n$ 的子集，$\text{MEX}(b,|b|+1)$ 的和。
# 思路
注意到，$2^n$ 级别的子集肯定不能枚举，但是我们讨论其 $\text{MEX}$ 的值，可以发现，其值域在 $1\sim2\times n+1$ 的。（考虑空集和全集可得）

那么，我们就可以把问题转换为，枚举一个 $x$，看**有多少个子集的结果为 $x$**。

根据题面可知，这道题目的时间复杂度是 $\mathcal{O}(n^2)$ 级别的，那么我们还可以再枚举一个 $n$。

我们考虑当前 $x$ **前面有多少个数 $i$**，假设**子集的 $max$ 小于 $x$**，那么我们需要使得 $2\times i+1=x$，这种情况才成立。而对应的方案数即为 $C_{x}^{i}$。

另一种情况则是**子集的 $max$ 大于 $x$**，那么我们可以将该子集的**长度**求出来，是 $x-i-1$，那么对应的，我们还有 $x-2
\times i-1$ 个数是**大于 $x$ 的**。

综上，我们可以将其合并为一个式子：

$$\sum_{x=1}^{2\times n+1}\sum_{i=1}^{x}C_{x}^{i}\times C_{n-x}^{x-2\times i-1}\times x$$

注意**判断一下边界条件**即可。

---

## 作者：wth2026 (赞：3)

# 题目大意
K1o0n 给了你一个长度为 $n$ 的数组 $a$，由数字 $1, 2, \ldots, n$ 组成。他要求你计算 $\text{MEOW}(a)$。

设 $\text{MEX}(S, k)$ 是集合 $S$ 中第 $k$ 个**正整数**（严格大于零）的升序排列中不在集合 $S$ 中的数字。将 $\text{MEOW}(a)$ 定义为对数组 $a$ 所有**不同**子集 $b$ 的 $\text{MEX}(b, |b| + 1)$ 进行求和。

例如，对于集合的 $\text{MEX}(S, k)$ 值：

- $\text{MEX}(\{3,2\}, 1) = 1$，因为 $1$ 是集合中缺失的第一个正整数；
- $\text{MEX}(\{4,2,1\}, 2) = 5$，因为集合中缺失的前两个正整数是 $3$ 和 $5$；
- $\text{MEX}(\{\}, 4) = 4$，因为空集合中没有数字，所以缺失的前四个正整数是 $1, 2, 3, 4$。

**数据保证 $n^2$ 之和不超过 $2.5 \times 10^7$。**
# 题目思路
枚举长度为 $i+1$ 的 $\text{MEX}(b, i+1)$ 值 $j$，则一共有 $i$ 个小于 $j$ 的数没有出现在 $b$ 中。

所以 $b$ 序列中有 $j-i-1$ 个数小于 $j$，$i \times 2 - j + 1$ 个数大于 $j$。

所以答案为：

$$
\sum_{i=0}^{n}\sum_{j=i+1}^{i \times 2 + 1} j \times C_{\min(n, j-1)}^{j-i-1} \times C_{\max(0, n-j)}^{i \times 2 + 1 - j}
$$

其中 $C^m_n$ 为组合数学中的无顺序选择，表示在 $n$ 个不同的物品中 **无顺序** 的选出 $m$ 个物品的方案数。

关于时间复杂度：

- 如果你使用公式 $C_i^j = C_{i-1}^j+C_{i-1}^{j-1}$ 预处理出所有 $i\leq n,j\leq i$ 的组合数，可以获得一份 $O(n^2)$ 的代码。

- 如果你事先预处理出阶乘并且会费马小定理和快速幂，就可以获得一份 $O(n^2 \times \log Mod)$（$Mod$ 指的是模数的大小）的代码。

- 如果你不预处理阶乘，就可以获得一份 $O(n^3 \times \log Mod)$（$Mod$ 指的是模数的大小）的代码。

- 如果你使用第一条给出的公式，但是每次询问每次现算，可以获得一份 $O(n^4)$ 的代码。

# [AC Code](https://codeforces.com/contest/1992/submission/280538330)
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 1000000007
#define lnf 0x3f3f3f3f3f3f3f3f

#pragma GCC optimize (1)
#pragma GCC optimize (2)
#pragma GCC optimize (3)
#pragma GCC optimize (4)
#pragma GCC optimize (5)
#pragma GCC optimize ("Os")
#pragma GCC optimize ("Ofast")

const bool Debug = false;

//#define Debug true

using namespace std;

const int N = 5000 + 5;

int C[N][N];

void Init () {
	for (register int i = 0; i < N; ++ i) {
		C[i][0] = 1;
		C[i][1] = i;
		C[i][i] = 1;
		
		for (register int j = 2; j < i; ++ j) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % inf;
		}
	}
	
	if (Debug) {
		cout << C[5][2] << endl;
	}
}

int T;
int n;
int _Ans;

signed main () {
	ios :: sync_with_stdio (Debug);
	cin.tie (0);
	cout.tie (0);
	Init ();
	
	cin >> T;
	
	while (T --) {
		_Ans = 0;
		cin >> n;
		
		for (register int i = 0; i <= n; ++ i) {
			for (register int j = i + 1; j <= (i << 1) + 1; ++ j) {
				_Ans += ((j * C[min (n, j - 1)][j - i - 1] % inf) * C[max (0ll, n - j)][(i << 1) + 1 - j]) % inf;
				_Ans %= inf;
				
				if (Debug) {
					cout << _Ans << endl;
				}
			}
		}
		
		cout << _Ans << endl;
	}
}

```

---

## 作者：Louis_lxy (赞：3)

一个简单的组合数学。

先算出没有考虑 $b$ 集合内的数的影响的值，此时答案为 $(|b|+1)\times C_n^{|b|}$。

显然我们有一个结论，如果在 $|b|+1$ 中有一个数，此时对答案造成的贡献就会加 $1$，因为如果区间内有一个数，显然会使得多一个属于 $b$ 的数，在 $[1,|b+1|]$ 不属于 $b$ 的数会减少一个。考虑计算此时的答案，显然我们先从 $[1,|b|+1]$ 选一个数，有 $C_{|b|+1}^1$ 种方案。接着需要在剩下的数中选择 $|b|-1$ 个，有 $C_{n-|b|-2}^{|b|-1}$ 种方案，而每个方案提供 $1$ 的贡献。此时的贡献就是 $1\times C_{|b|+1}^1\times C_{n-|b|-2}^{|b|-1}$。考虑将这个式子推广。我们发现，集合中没有重复数字，也就是说，在增加了 $1$ 的贡献后，还可以继续通过增加数字来增加贡献。我们用 $x$ 表示 $[1,|b|+x]$ 区间内有多少个数属于 $b$。那么答案就是 $x\times C_{|b|+x}^x\times C_{n-|b|-x-1}^{|b|-x}$。然后直接枚举 $|b|$ 和 $x$ 统计答案即可。注意可能会出现 $|b|+x>n$ 的情况，显然此时没有如此多的数，只需要对 $n$ 取较小值即可。

AC 记录：https://www.luogu.com.cn/record/168592610

---

## 作者：Meickol (赞：2)

**组合计数问题**。

我们先枚举集合所选的数的个数 $|S|$，然后再枚举 $\operatorname{MEX}(S,|S|+1)$ 的函数值（即结果是哪个数）。



对于 $\operatorname{MEX}({S},|S|+1)$，其可能取到的范围为 $[|S|+1,2×|S|+1] $。

> 对于此范围的解释：

因为 $\operatorname{MEX}({S},|S|+1)$ 要从 $1 \sim n$ 这些数中选择不在集合 $S$ 内的第 $|S|+1$ 小的数。

​	如果说 $1 \sim |S|+1$ 这些数都不在集合里，那么这时结果就能取到左边界 $|S|+1$；

​	如果说 $1 \sim |S|$ 都是集合 $S$ 内的数，那么这时结果就取到右边界 $|S|+|S|+1$，即 $2 \times |S|+1$。





于是有 $i=|S|$，$j=\operatorname{MEX}(S,|S|+1)$，且已知 $j \notin S$ 恒成立。

这时我们就能以 $j$ 作为分界线，分为 前半部分 $1 \sim j-1$ 和 后半部分 $j+1 \sim n$。

 - 当 $j$ 取到左边界 $i+1$ 时：
   - 即 $1 \sim |S|+1$ 这些数都不在集合里，即前半部分 $1 \sim j-1$ 中均不含有集合 $S$ 中的数。
     - 换句话说，集合 $S$ 中的 $|S|$ 个数均不在前半部分，即集合 $S$ 中的数均在后半部分。

- 当 $j$ 取到右边界 $2i+1$ 时：
  - 即 $1 \sim j-1$ 这些数都是 $S$ 中的数，即集合 $S$ 中的 $|S|$ 个数均在前半部分。
  - 注意，上面这句话只是说集合 $S$ 中的数都在前半部分，并不是说前半部分的数均为集合 $S$ 中的数。





因为 $j$ 的范围是由 $i$ 的值确定的，即 $i$ 是自变量。所以当 $i$ 固定时，$j$ 在其范围内逐渐增大的过程其实就对应了 $j$ 区域向右扩大的过程。

所以实际上，集合 $S$ 中的这 $|S|$ 个数始终是连续分布存放在 $|S|+1 \sim 2|S|+1$ 这段位置。

只是当 $j$ 不断增大时，即 $j$ 的区域向右扩大了，故集合 $S$ 中的数就逐渐开始进入前半部分即 $1 \sim j-1$ 了。

​	当 $j$ 取到范围内最小值，即集合 $S$ 中的数均不在前半部分中；

​	当 $j$ 取到范围内最大值，即集合 $S$ 中的数均在前半部分中。





其中 $S$ 中的数落在前半部分 $1 \sim j-1$ 中共有 $j-1-|S|$ 个。

$S$ 中的数落在后半部分 $j+1 \sim n$ 中共有 $n-(j-1-|S|)$ 个。



即 $\Large C_{j-1}^{j-1-i} \times C_{n-j}^{i-(j-1-i)} \times j$



即前半部分乘上后半部分再乘上 $j$ 的值。

为什么要乘上 $j$ 的值呢？结合其意义分析，因为有 $C_{j-1}^{j-1-i} \times C_{n-j}^{i-(j-1-i)}$ 种选法能对应 $\operatorname{MEX}({S},|S|+1)=j$ 的情况。

而我们要求的 $\operatorname{MEOW}(a)$ 的定义就是把数组 $a$ 的所有**不同**子集 $b$ 中的 $\operatorname{MEX}(b,|b|+1)$ 求和。

自然就是这样做。



最终答案：$\Large ans=\sum_{i=0}^{n} \sum{_{j=i+1}^{2i+1}} \ \Large C_{j-1}^{j-1-i} \times C_{n-j}^{i-(j-1-i)} \times j$



最后注意因为 $j$ 的值可能超过 $n$，所以 $\min{(n,j-1)}$、$\max{(0,n-j)}$。



```c++
#include<bits/stdc++.h>
using namespace std;
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define IOS std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define endl '\n'
typedef long long LL;
const int N=5e3+5,MOD=1e9+7;
int n;
LL C[N][N];
void init(){
	rep(i,0,N-1){
		rep(j,0,i){
			if(!j) C[i][j]=1;
			else C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
		}
	}
}
void solve(){
	cin>>n;
	LL res=0;
	rep(i,0,n){
		rep(j,i+1,2*i+1){
			res=((res+C[min(j-1,n)][j-1-i]*C[max(n-j,0)][i-(j-1-i)]%MOD*j%MOD)%MOD+MOD)%MOD;
		}
	}
	cout<<res;
}
int main(){
	IOS;
	int T;
	//cin>>T;
	T=1;
	while(T--){
		solve();
		//cout<<endl;
	}
	return 0;
}
```

---

## 作者：Jordan_Pan (赞：1)

手玩几组样例后发现如果选同样多的数，仍有大量的重复答案。进一步发现以这些答案作为分界线，集合的前后是互不相关的。

什么意思呢，考虑枚举选择的集合大小 $i$ 和选在答案之前的数量 $j$，那么 $i$、$j$ 均相同的集合的答案一定都是 $i+j+1$。例如选了 `14` 这 2 个数，发现答案是 3，并且 `24`、`25` 等等集合的答案也都是 3。

这是为什么呢，因为答案是没出现过的从小到大的第 $i+1$ 个数，那么遇到小于 $i+j+1$ 的 $j$ 个数的时候，就会跳过它。亵玩几组美味的数字后，这个结论还是相当显然的。

那么我们把一个集合分成两个部分：小于 $i+j+1$ 的，我们在里面任意选 $j$ 个数；大于 $i+j+1$ 的，我们在里面选任意 $i-j$ 个数，注意边界 $0$ 和 $n$。令 $k=i+j+1$，于是答案就呼之欲出了：

$$
\sum_{i=0}^{n} \sum_{j=0}^{i}k \binom{\min(k-1,n)}{j} \binom{\max(n-k,0)}{i-j}
$$

由于 $n \le 5000$，组合数 $O(n^2)$ 预处理即可。

代码：

~~~cpp
ans=0;
for(int i=0;i<=n;i++)
  for(int j=0;j<=i;j++){
    int k=i+j+1;
    ans=(ans+1ll*k*C[min(k-1,n)][j]%mod*C[max(n-k,0)][i-j]%mod)%mod;
  }
~~~

---

## 作者：Linge_Zzzz (赞：1)

~~纪念一下独立做出来的 *2000。~~

# 题意简述

给你一个集合 $A$，其中的元素为 $1,2,3,\cdots,n$，定义 $\operatorname{mex}\{B,k\}$ 为集合 $B$ 中从小到大不存在的第 $k$ 个**正整数**。

求 $\sum_{S\in A}\operatorname{mex}\{S,|S|+1\}$。

# 解法

考虑枚举 $a$，再计算有多少个 $S$ 符合 $\operatorname{mex}\{S,|S|+1\}=a$。

我们分为两种情况：

1. $a\leq n$，此时 $S$ 中的元素可能小于 $a$，也可能大于 $a$。

2. $n+1\leq a\leq 2n+1$，此时 $S$ 中的元素小于 $n$。

先考虑第一种情况。

既然是明摆着让 $O(n^2)$ 过，不如往 $O(n^2)$ 方面想想。

我们枚举 $a$ 的同时枚举 $S$ 中小于 $a$ 的数的个数，记为 $x$，设 $S$ 中大于 $a$ 的数的个数为 $y$，则根据定义可以推导出 $y=a-1-2x$。

相当于在小于 $a$ 的 $a-1$ 个数中选择 $x$ 个，在大于 $a$ 的 $n-a$ 个数中选择 $y$ 个，显然有 $\binom{a-1}{x}\binom{n-a}{y}$ 种情况，对应到答案的贡献就是 $\binom{a-1}{x}\binom{n-a}{y}\times a$。

再考虑第二种情况。

也是枚举 $a$。设 $x$ 为选择了多少个数（因为 $x>n$，所有的数小于等于 $n$，所以讨论 $a$ 与 $x$ 的大小关系没意义），则容易发现，当且仅当 $a=2x+1$ 时满足条件。

于是预处理组合数就可以在 $O(n^2)$ 的时间内回答一个测试点。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const int N=5e3+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int jc[N],jcinv[N];
int qpow(int a,int p){
	int ans=1;
	while(p){
		if(p&1)ans=ans*a%mod;
		a=a*a%mod;
		p>>=1;
	}
	return ans;
}
void init(){
	jc[0]=jcinv[0]=1;
	for(int i=1;i<N;i++){
		jc[i]=jc[i-1]*i%mod;
		jcinv[i]=qpow(jc[i],mod-2);
	}
}
int C(int n,int m){return jc[n]*jcinv[n-m]%mod*jcinv[m]%mod;}
void solve(){
	int n,ans=0;
	cin>>n;
	for(int a=1;a<=n;a++){
		for(int x=0;x<=a-1;x++){
			int y=a-1-2*x;
			if(y<0)break;
			if(n-a>=y)ans=(ans+C(a-1,x)*C(n-a,y)%mod*a%mod)%mod;
		}
	}
	for(int a=n+1;a<=n+n+1;a++){
		if(a%2==1)ans=(ans+C(n,a/2)*a%mod)%mod;
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	init();
	int t;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

比较好的计数题。

考虑枚举子序列大小与子序列贡献，假定这两个值分别为 $sz$ 与 $k$，不难发现，因为贡献为 $k$，所以 $[1,k]$ 一定出现了 $k-sz-1$ 个子序列中的数，而且第 $k$ 个一定不是，又因为子序列值域是 $[1,n]$，所以方案数为 ${\min(n,k-1)} \choose k-sz-1$，剩下的数再从 $[k+1,n]$ 中选择即可，预处理组合数即可 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e4+114;
const int mod = 1e9+7;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
int fac[maxn],inv[maxn];
int C(int n,int m){
    if(m==0) return 1;
    if(m>n) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int n;
void work(){
    int ans=0;
    cin>>n;
    for(int k=1;k<=2*n+1;k++){
        for(int sz=0;sz<=n;sz++){
            //[1,k] 中集合内出现了 k-sz-1 个
            if(sz+1<=k&&2*sz+1>=k){
                int res=C(min(k-1,n),k-sz-1)*C(n-k,sz-(k-sz-1))%mod;
                //cout<<k<<' '<<sz<<' '<<res<<'\n';
                ans=(ans+res*k%mod)%mod;
            }
        }
    }
    cout<<ans<<'\n';
}
signed main(){
    fac[0]=inv[0]=1;
    for(int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
2
*/

```

---

