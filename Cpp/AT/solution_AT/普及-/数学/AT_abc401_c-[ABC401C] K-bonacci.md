# [ABC401C] K-bonacci

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc401/tasks/abc401_c

给定正整数 $N$ 和 $K$。我们按照以下方式定义长度为 $N+1$ 的数列 $A=(A_0,A_1,\ldots,A_N)$ 的每个元素值：

- 当 $0 \leq i < K$ 时，$A_i = 1$
- 当 $K \leq i$ 时，$A_i = A_{i-K} + A_{i-K+1} + \ldots + A_{i-1}$

请计算 $A_N$ 对 $10^9$ 取模后的结果。

## 说明/提示

### 约束条件

- $1 \leq N, K \leq 10^6$
- 输入的所有数值均为整数

### 样例解释 1

$A_0 = A_1 = 1$，而 $A_2 = A_0 + A_1 = 2$，$A_3 = A_1 + A_2 = 3$，$A_4 = A_2 + A_3 = 5$。

### 样例解释 3

请注意需要输出 $A_N$ 对 $10^9$ 取模后的结果。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4 2```

### 输出

```
5```

## 样例 #2

### 输入

```
10 20```

### 输出

```
1```

## 样例 #3

### 输入

```
1000000 500000```

### 输出

```
420890625```

# 题解

## 作者：Gilbert1206 (赞：1)

## AT_abc401_c [ABC401C] K-bonacci 题解

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc401_c)

## 题意和做法
这道题的相当于斐波拉契数列的进阶版，就是把前 $K$ 个设为 $1$。后面的第 $i$ 个数为前 $i-K$ 个至 $i-1$ 个的和。让你求出第 $N$ 项。

思路其实是前缀和把每次算出的答案记录在前缀和里。每次记录的答案应该是前 $i-K$ 个至 $i-1$ 个的和，每次算出答案后还要模 $10^9$。

## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=1e9;
long long a[1400000];
int main(){	
	long long n,k;
	cin>>n>>k;
	if(n<k){
		cout<<1;
		return 0;
	}
	for(int i=1;i<=k;i++){
		a[i]=a[i-1]+1;
	}
	for(int i=k+1;i<=n+1;i++){
		a[i]=a[i-1]+(a[i-1]-a[i-k-1]);
		if(a[i]<0){
			a[i]+=N;
		}
			a[i]%=N;
	}
	cout<<(a[n+1]-a[n]+N)%N;
	return 0;
}

```

---

## 作者：lizhixun (赞：1)

使用前缀和解决，下文中的 $s$ 为序列 $A$ 前缀和数组。

- 当 $0 \le i < K$ 时：$A_i=1$。
- 当 $K \le i \le n$ 时：$A_i=(\sum_{j=i-K}^{i-1}a_j)\bmod10^9=(s_{i-1}-s_{i-K-1})\bmod10^9$。

无论何时对于 $i\le1$ 有 $s_i=(s_{i-1}+a_i)\bmod10^9$，且 $s_0=1$。根据上述式子计算即可，每次先计算 $a_i$ 再 $s_i$，不要搞反了。

[Code.](https://atcoder.jp/contests/abc401/submissions/65208779)

---

## 作者：天使宝贝 (赞：1)

### 题目大意

给你正整数 $n$ 和 $k$ .定义长度为 $n + 1$ 的序列 $a = (a_0, a_1, \ldots, a_n)$ 如下：

- $a_i = 1$ 为 $0 \le i < k$；
- $a_i = a_{i - k} + a_{i - k + 1} + \ldots + a_{i - 1}$ 代表 $k \le i$。

求 $A_n \pmod{ 10^{9} }$。

### 思路&分析
首先，我们可以先求出 $a_0, a_1, \ldots , a_{k - 1}$，然后对于这段区间，求出对应的前缀和，将前缀和数组记为 $sum$，然后我们可以从 $k$ 一直遍历到 $n$，对于每一个 $a_i$，我们可以通过前缀和 $O(1)$ 求出从 $a_{i - k}$ 一直加到 $a_{i - 1}$ 的区间和了，即：

$$a_i = sum_{i - 1} - sum_{i - k - 1}$$

不过需要注意的是，当 $i = k$ 是需要特判，因为 $i - k -1$ 的值为 $-1$，因此会产生越界。

由于我们已经求得了 $a_i$，因此我们只需要用 $a_i$ 更新当前的 $sum_i$ 即可。

### CODE
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define IOS ios::sync_with_stdio(0), ios_base::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define dep(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
constexpr int MAXN = 1e6 + 5, MOD = 1e9;
int n, k, a[MAXN], sum[MAXN];
signed main() {
	IOS;
	cin >> n >> k;
	rep(i, 0, k - 1) {
		a[i] = 1;
	}
	sum[0] = a[0];
	rep(i, 1, k - 1) {
		sum[i] = (sum[i - 1] + a[i]) % MOD;
	}
	rep(i, k, n) {
		if (i == k) a[i] = sum[i - 1] % MOD;
		else a[i] = (sum[i - 1] - sum[i - k - 1] + MOD) % MOD;
		sum[i] = sum[i - 1] + a[i];
	}
	cout << a[n] << endl;
	return 0;
}
```
时间复杂度：$O(n)$。

---

## 作者：hjyowl (赞：0)

### 思路

先用一个 $f$ 数组初始化前 $k$ 个。

再用 $s$ 数组维护 $f$ 的前缀。

我们可以得到一个式子：

对于 $m + 1 \le i$，$f_i=(s_{i-1}-s_{i-m-1})$

否则 $f_i=s_{i-1}$。

然后统计 $f$ 的前缀。

做完了。

### 代码

```cpp
//f(3,5)=4 f(4,5)=5 f(5,5)=1
//既然我求不出来答案，那么为什么我们不能回退？
//首先，最后一项等于1,然后推回去，能等于1的只有f(m,m)
//然后，我们对于f(m,m)，就意思说有东西退出来了f(m,m),那只有f(m-1,m)和f(m^2,m)
//然后，这里出了两条分叉，直接按照是+1或者说/m来搜出来，对于每个子树，只要搜到了n层就推出
//时间复杂度O(2^n)，一眼超时，现在问题变成了这样，我可以进行n次，每次可以考虑-1或者*m，求出总方案
//不过，我们可以枚举进行了多少次*m,-1的次数也知道了
//C(3,1)+C(3,0),3+1=4(因为只有t个*m,所以说n-t<=t) 
//ans:sigma(0~n/2)C(n,i)
#include <bits/stdc++.h>
using namespace std;
long long mod = 1e9;
long long qmi(long long a,long long k){
	long long res = 1;
	while (k){
		if (k & 1){
			res = (res * a) % mod;
		}
		a = (a * a) % mod;
		k >>= 1;
	}
	return res;
}
const long long N = 1000010;
long long f[N]; 
long long s[N];
int main(){
//	freopen("change.in","r",stdin);
//	freopen("change.out","w",stdout);
	memset(s,0,sizeof s);
	memset(f,0,sizeof f);
	long long n,m;
	cin >> n >> m;
	if (n < m){
		cout << 1;
		return 0;
	}
	for (long long i = 0; i < m; i ++ ){
		f[i] = 1;
	}
	s[0] = f[0];
	for (long long i = 1; i < m; i ++ ){
		s[i] = s[i - 1] + f[i];
		s[i] %= mod;
	}
	for (long long i = m; i <= n; i ++ ){
		if (i - m - 1 >= 0){
			f[i] = (s[i - 1] - s[i - m - 1]) % mod;
			if (f[i] < 0){
				f[i] += mod;
			}
		}
		else{
			f[i] = s[i - 1] % mod;
		}
		s[i] = (s[i - 1] + f[i]) % mod;
	}
	cout << f[n] % mod;
	return 0;
} 
```

---

## 作者：liruizhou_lihui (赞：0)

题目大意：

给你两个数 $n$ 和 $k$，你要根据 $k$ 求出序列 $a$，求 $a_n$。

$a_i$ 的计算方式：

$$
a_i = \begin{cases}
  1 & 0\le i < k \\
  \sum_{j=i-k}^{i-1} a_j& k\le i \\
  
\end{cases}

$$
---

考虑递推加前缀和优化，$s_{i}$ 表示 $a$ 前 $i$ 项和，处理 $0\le i < k$的时候每次把 $s_i$ 赋值成 $s_{i-1}+1$。

处理到 $k\le i$ 时：先把 $s_i$ 赋值成 $s_{i-1}$，如果 $i=k$ 就代表 $a_i$ 就是前面所有数的和，直接加上 $s_{i-1}$。$i \ne k$ 就是 $s_{i-1}-s_{i-k-1}$。

最后 $s_n-s_{n-1}$ 就是 $a_i$。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int MOD=1e9;
int n,k;
int s[1000005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>k;
	for(int i=0;i<k;i++)
	{
		s[i]=s[i-1]+1;
		s[i]%=MOD;
	}
	if(k>n)
	{
		cout<<1;
		return 0;
	}
	for(int i=k;i<=n;i++)
	{
		s[i]+=s[i-1]+s[i-1];
		if(i!=k)
		{
			s[i]-=s[i-k-1];
		}
		s[i]%=MOD;
	}
	cout<<(s[n]-s[n-1]+MOD)%MOD;
	return 0;
}
```

---

## 作者：jiangyunuo (赞：0)

### 题目意思：
[题面翻译](https://www.luogu.com.cn/paste/kdvek72o)。  
给出 $N$ 和 $K$，构造一个数列，初始时 $A_0 = A_1 = A_2 = \ldots = A_{K-1}$，同时 $A_i = A_{i-K} + A_{i-K+1} + \ldots + A_{i-1}$（此时 $i \ge K$），问：$A_N$ 的值是多少。  
### 大体思路：
观察题目，我们可以发现本题是一道递推，我们可以从 $A_1$ 一直推到 $A_N$。  
接下来我们要进行分类讨论：

1. 当 $i < K$ 时，$A_i = 1$。
2. 当 $i \ge K$ 时，$A_i = A_{i-K} + A_{i-K+1} + \ldots + A_{i-1}$。

注：以上两种情况在题目中都给出了。  
于是，我们就得到了核心代码：

```
for(int i=0;i<=n;i++){
		if(i<k)ans[i]=1;
		else{
        for(int j=1;j<=k;j++){
            ans[i]+=ans[i-j];
        }
    }
		ans[i]%=1000000000;   //题目要取模，别忘了。
}
```

这就好了吗？  
显然，本题没这么简单，你看，这双重循环的时间复杂度为 $O(NK)$（注，代码中 $N$ 和 $K$ 其实是小写的形式，即 $n$ 和 $k$，且数组 $ans$ 表示数列 $A$），但本题的数据范围：$1 \le N, K \le 10^6$。  
那该咋办？  
别急，接着看。  
已知 $A_{i-1} = A_{i-K-1} + A_{i-K} + \ldots + A_{i-2}$，而 $A_i = A_{i-K} + A_{i-K+1} + \ldots + A_{i-1}$。  
可以发现，$A_i - A_{i-1} = A_{i-K} + A_{i-K+1} + \ldots + A_{i-2}$。  
对比 $A_{i-1} = A_{i-K-1} + A_{i-K} + \ldots + A_{i-2}$，我们可以得出 $A_i - A_{i-1} = A_{i-1} - A_{i-K-1}$。  
再移项，得 $A_i = 2 \times A_{i-1} - A_{i-K-1}$。  
于是，我们又得到：

```
for(int i=0;i<=n;i++){
		if(i<k)ans[i]=1;
    else if(i==k)ans[i]=k;   //注意，如果没这一行，一定会错，毕竟在这种情况下 i-k-1 为 -1，数组就越界了。
		else ans[i]=ans[i-1]*2-ans[i-k-1];
		ans[i]%=1000000000;
}
```

不过，这依旧是错的，为啥？  
注意这个取模，本来 $A_{i-1} \times 2 - A_{i-k-1}$ 的结果应该是个正数，但是，取模的缘故可能会导致 $A_{i-1} \times 2 < A_{i-K-1}$。  
为了解决这个问题，我们可以让 $A_{i-1} \times 2 + 10^9$。  
为什么可以这样？  

1. 若 $A_{i-1} \times 2 < A_{i-K-1}$，那么 $A_{i-1} \times 2 + 10^9$ 就相当于向前借一位数，和列竖式向前借一位的原理类似。注意，在不取模的情况下 $A_{i-1} \times 2 \ge A_{i-K-1}$ 一定成立，也就是说，不管怎样，$A_{i-1} \times 2 < A_{i-K-1}$ 时一定能向前借一位。  
2. 如果 $A_{i-1} \times 2 \ge A_{i-K-1}$，那么借不借都无所谓，借了也没影响，那借的一位不会被用到，到了取模的时候就直接消掉了。

于是，我们得到了：

```
for(int i=0;i<=n;i++){
		if(i<k)ans[i]=1;
    else if(i==k)ans[i]=k;
		else ans[i]=ans[i-1]*2+1000000000-ans[i-k-1];
		ans[i]%=1000000000;
}
```

这回就没问题了，这是正确的。
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	long long ans[n+1]={};   //本题数据量大，有取模也需要 longlong。
	for(int i=0;i<=n;i++){
		if(i<k)ans[i]=1;
    else if(i==k)ans[i]=k;
		else ans[i]=ans[i-1]*2+1000000000-ans[i-k-1];
		ans[i]%=1000000000;
	}
	cout<<ans[n]<<endl;
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc401/submissions/64783113)。

---

