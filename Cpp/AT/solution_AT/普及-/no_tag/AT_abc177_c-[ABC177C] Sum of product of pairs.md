# [ABC177C] Sum of product of pairs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc177/tasks/abc177_c

$ N $ 個の整数 $ A_1,\ldots,A_N $ が与えられます。

$ 1\leq\ i\ <\ j\ \leq\ N $ を満たす全ての組 $ (i,j) $ についての $ A_i\ \times\ A_j $ の和を $ \bmod\ (10^9+7) $ で求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

$ 1\ \times\ 2\ +\ 1\ \times\ 3\ +\ 2\ \times\ 3\ =\ 11 $ です。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
11```

## 样例 #2

### 输入

```
4
141421356 17320508 22360679 244949```

### 输出

```
437235829```

# 题解

## 作者：GreenMelon (赞：2)

既然有了翻译，就不过多讲述了。

可以将式子拆分开来：

$$\sum^{n-1}_{i=1}\sum^{n}_{j=i+1}A_i\times A_j = A_1\times A_2+A_1\times A_3+\cdots+A_1\times A_n+A_2\times A_1+\cdots+A_i\times A_j+\cdots+A_{n-1}\times A_n \\
=A_1\times (A_2+A_3+\cdots+A_n)+A_2\times(A_3+\cdots+A_n)+\cdots+A_{n-1}\times A_n$$

用一个数组 $B$ 存储 $A$ 的前缀和，也就是说，$B_i=A_1+A_2+\cdots+A_i$，最后式子将变为：

$$A_1\times (B_n-B_1)+A_2\times(B_n-B_2)+\cdots+A_i\times(B_n-B_i)+\cdots+A_{n-1}\times A_n$$

注意最后要 $\bmod$ $(10^9+7)$。

---

## 作者：yinbe (赞：2)

## 题面描述

给定 $N$ 个整数 $A_1,...,A_n$，求出所有满足 $1 \le i <j \le n$ 的 $A_{i} \times A_{j}$ 的和。

答案对 $10^9+7$ 取模。

### 数据范围

- $2\ \leq\ N\ \leq\ 2\times\ 10^5$
- $0\ \leq\ A_i\ \leq\ 10^9$

## 暴力思路

枚举 $i$ 和 $j$，直接计算和，时间复杂度 $O(n^2)$ 显然会 TLE。

## 暴力代码

```cpp
#include<iostream>
using namespace std;
int n;
long long a[200005],ans;
long long mod=1e9+7;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			ans+=a[i]*a[j];
			ans%=mod;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

## 正解思路

先观察一下要求的答案：

$A_{1} \times A_{2} + A_{1} \times A_{3} + \cdots + A_{i} \times A_{j} + \cdots A_{n-1} \times A_{n}$

用乘法分配律将每个 $A_{i}$ 提出来，原式就变成了：

$A_{1} \times (A_{2} + A_{3} + \cdots + A_{n}) + \cdots +A_{i} \times (A_{i+1} +A_{i+2} + \cdots A_{n}) + \cdots A_{n-1}\times A_{n}$

我们发现：

$A_{i} +A_{i+1} + \cdots A_{n}$

这个式子可以利用前缀和 $O(1)$ 的求出来，所以我们只需要枚举 $i$ 就好了，时间复杂度降为 $O(n)$。

## 正解代码

```cpp
#include<iostream>
using namespace std;
int n;
long long a[200005],sum[200005],ans;
long long mod=1e9+7;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=n;i++)
	{
		ans+=a[i]*((sum[n]-sum[i])%mod);
		ans%=mod;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：3_14 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc177_c)

# 思路

这个问题要求我们计算给定数组中所有可能的两两元素乘积之和，并对结果取模。具体来说，我们需要计算以下表达式的值：

$$\sum_{i=1}^{n-1} \sum_{j=i+1}^{n} a_{i} \times a_{j}$$

其中 $a_{i}$ 是数组中的元素，$n$ 是数组的长度。

1. 暴力解法：方法是使用两层循环来计算所有可能的 $a_{i} \times a_{j}$ 的和。这种方法的时间复杂度是 $O \left ( n^{2} \right ) $，对于较大的 $n$ 会超时。

2. 优化解法：我们可以通过数学推导来优化这个过程。作出以下等式：

$$\sum_{i=1}^{n-1} \sum_{j=i+1}^{n} a_{i} \times a_{j} = \frac{\left ( \sum_{i=1}^{n} a_{i}  \right )^{2} + \sum_{i=1}^{n} a^{2}_{i} }{2} $$

这个公式可以通过以下步骤推导出来：

1. 首先计算所有元素的平方和。

$$\sum_{i=1}^{n} a_{i}^{2}$$

2. 然后计算所有元素的和的平方。

$$\left ( \sum_{i=1}^{n} a_{i} \right ) ^{2}$$

3. 通过公式计算结果。

$$\frac{\left ( \sum_{i=1}^{n} a_{i}  \right )^{2} + \sum_{i=1}^{n} a^{2}_{i} }{2}$$

# 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i)cin >> a[i];
    long long sum = 0;
    long long sum_sq = 0;
    for (int i = 0; i < n; ++i) {
        sum = (sum + a[i]) % MOD;
        sum_sq = (sum_sq + a[i] * a[i]) % MOD;
    }
    long long result = (sum * sum % MOD - sum_sq + MOD) % MOD;
    result = (result * 500000004) % MOD;
    cout << result << endl;
    return 0;
}

```

这个方法的时间复杂度是 $O \left ( n \right ) $ 包过的。

---

## 作者：ICE__LX (赞：1)

这道题第一眼就是暴力，但数据明显超过了 $O(n^2)$ 的能力范围，因此我们需要对代码进行优化。  
根据伟大的乘法分配率，我们可以得出 $\sum_{i=1}^{n-1}{\sum_{j=i+1}^{n}{a_i\times a_j}}$ 实际上就是 $\sum_{i=1}^{n-1}{a_i\times \sum_{j=i+1}^{n}{a_j}}$。因此，我们可以把求 $\sum_{j=i+1}^{n}{a_j}$ 的过程优化成 $O(1)$ 级别，这一过程可以通过前缀和实现，优化后的时间复杂度为 $O(n)$，可以通过。  
那就没什么好说的了，上代码吧。  

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
signed main() {
	int n;
	int ans=0;
	cin>>n;
	int *a=new int[n+1],*c=new int[n+1];//动态数组
	c[0]=0;
	for(int i=1; i<=n; i++)cin>>a[i],c[i]=c[i-1]+a[i];//输入、前缀和初始化
	for(int i=1; i<=n; i++)
		ans=((ans+((a[i]*((c[n]-c[i])%mod))%mod))%mod);//计算过程
	cout<<ans;
	delete[]a;//释放空间
	delete[]c;
	return 0;
}

```

---

## 作者：hjhAKIOI (赞：1)

# [ABC177C] Sum of product of pairs题解

## 题目描述

给定 $N$ 个整数 $A_1,A_2\cdots A_n$，求出 $(\sum_{i=1}^{n-1} \sum_{j=i+1}^{n} A_i\times A_j)\bmod 10^9+7$ 的值。

数据范围：$1\le N \le 2\times 10^5,0\le A_i\le 10^9$

## 题意分析

这题的题意比较清楚，如果看不懂大型运算符可以看下面的解释：

给定 $N$ 个整数 $A_1,A_2\cdots A_n$，对于所有满足 $1\le i<j \le N$ 的整数数对 $(i,j)$，求出 $A_i\times A_j$ 的总和。答案对 $10^9+7$ 取模。

## 做题思路

我们可以先想暴力的做法。

这题暴力的做法比较显然，枚举所有满足条件的整数数对，并把结果加到答案中。但是这样的做法时间复杂度为 $O(N^2)$ ，不能通过本题。

我们可以考虑每个数对答案的贡献。

把上面的式子展开：

$\sum_{i=1}^{n-1} \sum_{j=i+1}^{n} A_i\times A_j=A_1\times A_2+A_1\times A_3+\cdots+A_1\times A_n+A_2\times A_3+A_2\times A_4+\cdots+A_{n-1}\times A_{n}$.

可能这样看不出什么，我们对这个式子再整理一下：

$A_1\times A_2+A_1\times A_3+\cdots+A_1\times A_n+A_2\times A_3+A_2\times A_4+\cdots+A_{n-1}\times A_{n}$

$=A_1\times A_2+A_1\times A_3+A_2\times A_3+A_1\times A_4+A_2\times A_4+A_3\times A_4+A_1\times A_5+\cdots +A_{n-1}\times A_n$

$=A_1\times A_2+(A_1+A_2)\times A_3+(A_1+A_2+A_3)\times A_4+\cdots+(A_1+A_2+\cdots+A_{n-1})\times A_n$.

到这里就非常明显了：每个数的贡献是**数列中这个数前面所有数的和，也就是这个数前面的前缀和！**

那么我们就可以想到线性的做法：先预处理数列的前缀和，然后只要遍历一遍整个数列就可以得到答案了。

于是，问题愉快的解决了。

## 时间\空间复杂度分析

### 时间复杂度

预处理前缀和需要 $O(N)$ 的时间复杂度，遍历整个数列需要 $O(N)$ 的时间复杂度，遍历时的计算是 $O(1)$ 的，所以整个算法的时间复杂度为 $O(N)$，可以通过本题。

### 空间复杂度

前缀和需要 $O(N)$ 的数组来存储，再加上数列 $A$ 的 $O(N)$ 空间复杂度，一共是 $O(N)$ 的空间复杂度，可以通过本题。

## 实现细节

由于数列 $A$ 中的数比较大，需要开 `long long`。另外，在计算的过程中甚至可能会爆 `long long`，所以要写一个~~龟速~~快速乘。

---

至此，所有的问题都得到了解决。

下面给出 AC 代码：

```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5,Mod=1e9+7;
int n,ans;
int a[200005],s[200005];

int mul(int a,int b,int p){  //快速乘
	a%=p;
	b%=p;
	int c=(long double)a*b/p;
	int x=a*b,y=c*p;
	int ans=(long long)(x%p)-(long long)(y%p);
	if(ans<0){
		ans+=p;
	}
	return ans;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+a[i];    //预处理前缀和
	}
	for(int i=1;i<=n;i++){
		ans=(ans+mul(a[i],s[i-1],Mod))%Mod; //记得取模
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：dangerous_DZR (赞：0)

# AT_abc177_c [ABC177C] Sum of product of pairs 题解
## 分析
看到题目后首先对一长串式子进行分解：  
原式 $= a_1 \times a_2 + a_1 \times a_3 + ... + a_1 \times a_n + a_2 \times a_3 + a_2 \times a_4 + ... + a_2 \times a_n + ... + a_{n - 1} \times a_n$  
${\color{white}{kon}} = a_1 \times (a_2 + a_3 + ... + a_n) + a_2 \times (a_3 + a_4 + ... + a_n) + ... + a_{n - 1} \times a_n$

于是我们双眼一瞪——这不是前缀和吗？  
——$O(n ^ 2)$ 变成了 $O(n)$！
### 注意
不开 long long 见祖宗！
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, a[200010], sum[200010], ans, mod = 1e9 + 7;//注意取模
int main(){
	cin >> n;
	for (int i = 1; i <= n; i ++){
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];//正常前缀和
	}
	for (int i = 1; i < n; i ++)ans += (a[i] * ((sum[n] - sum[i]) % mod)) % mod;//化简后的式子
	cout << ans % mod;
	return 0;
}
```
Goodbye！

---

## 作者：huanglihuan (赞：0)

### 题目大意

给定 $n$ 和长度为 $n$ 的序列 $a$，求 $\sum_{i=1}^{n-1}{\sum_{j=i+1}^{n}{a_i\times a_j}}\bmod10^9+7$ 的值。

### 思路

拆解式子得

$$a_1\times a_2+a_1\times a_2+a_1\times a_3+a_1\times a_4+\ldots+a_1\times a_n+a_2\times a_3+a_2\times a_4\ldots+a_{n-2}\times a_n+a_{n-1}\times a_n\bmod10^9+7$$

因为对于下标 $i$，它的贡献值为 $a_i\times (a_{i+1}+a_{i+2}+\ldots+a_n)$，这个式子中的 $a_{i+1}+a_{i+2}+\ldots+a_n$ 可以变成 $a_1$ 到 $a_n$ 的和减去 $a_1$ 到 $a_i$ 的和，可以用前缀和计算。

### 答案

令 $pre_i$ 为 $a_1+a_2+\ldots+a_i$ 的值即前缀和。

最终答案为

$$\sum_{i=1}^{n-1}a_i\times(pre_n-pre_i)\bmod10^9+7$$

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a [200005],pre [200005];
const int mod = 1e9 + 7;
signed main ()
{
	int n;
	cin >> n;
	for (int i = 1;i <= n;i ++)
	{
		cin >> a [i];
		pre [i] = pre [i - 1] + a [i];
	}
	int ans = 0;
	for (int i = 1;i <= n;i ++)
	{
		ans += a [i] * ((pre [n] - pre [i]) % mod) % mod;
		ans %= mod;
	}
	cout << ans;
	return 0;
}
```

---

