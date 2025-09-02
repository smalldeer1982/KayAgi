# [蓝桥杯 2025 省 Python B] A · B Problem

## 题目描述

设有两个二维向量 $\overrightarrow{A}(X_A, Y_A), \overrightarrow{B}(X_B, Y_B)$。给定 $L$，求 $(X_A, Y_A), (X_B, Y_B)$ 有多少种不同的取值，使得：

1. $X_A, Y_A, X_B, Y_B$ 均为正整数；
2. $\overrightarrow{A} \cdot \overrightarrow{B} \leq L$，其中 $\overrightarrow{A} \cdot \overrightarrow{B}$ 表示 $\overrightarrow{A}, \overrightarrow{B}$ 的内积，即 $X_A \cdot X_B + Y_A \cdot Y_B$。

## 说明/提示

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$L \leq 50$；
- 对于 $80\%$ 的评测用例，$L \leq 5000$；
- 对于所有评测用例，$1 \leq L \leq 2^{20}$。

## 样例 #1

### 输入

```
2```

### 输出

```
1```

## 样例 #2

### 输入

```
3```

### 输出

```
5```

# 题解

## 作者：CSP_S_2023_T2 (赞：32)

### 思路

**Step 1：**

对于 $1$ 到 $L$ 之间的每一个满足条件的整数 $i$：

先枚举所有可能的 $X_A \cdot X_B$ 以及 $Y_A \cdot Y_B$，再枚举所有可能的 $X_A,X_B,Y_A,Y_B$。

时间复杂度 $O(L^2 \sqrt L)$，会超时。

**Step 2：**

我们定义 $f(x)$ 为 $x$ 能表示为不同的两个正整数的乘积的种类数（即 $x$ 的因数个数）。

如 $f(6)=4$（$6=1\times6=2\times3=3\times2=6\times1$）。

显然答案为

$$\sum_{i=1}^{L-1} \sum_{j=1}^{L-i} f(i) \times f(j)$$

也就是

$$\sum_{i=1}^{L-1} \big( f(i) \times \sum_{j=1}^{L-i} f(j) \big)$$

不懂的可以自己手推一下。

所以，我们可以预处理出所有的 $f(x)$，再用一次前缀和，时间复杂度就来到了 $O(L \sqrt L)$。

此时 C++ 已经能过了，但是 Python 还不能。

**Step 3：**

考虑对预处理进行优化。

我们发现，在预处理的过程中，寻找 $x$ 的因数需要枚举 $\sqrt x$ 次，远大于 $x$ 的因数个数。

所以，我们不妨枚举所有因数，即先从 $1$ 到 $L$ 枚举所有整数 $i$，然后枚举 $i$ 的所有倍数，将计数数组的这一项 $+1$ 即可。

容易发现时间复杂度即为调和级数（不懂的自己百度），也就是 $O(L \log L)$。

此时 Python 也能过了。

于是这道题就做完了。

### 代码


```python
n=int(input())
ans=0
a=[0]*1048577     #1048577=2^20+1
b=[0]*1048577
for i in range(1,n+1):
    for j in range(i,n+1,i):
        a[j]=a[j]+1          #计数器 +1
for i in range(1,n+1):
    b[i]=b[i-1]+a[i]         #前缀和数组
for i in range(1,n+1):
    ans=ans+a[i]*b[n-i]      #统计答案
print(ans)
```
（疯狂暗示）

---

## 作者：LimityZetta (赞：5)

_交一篇 c++ 题解_ 

## 题意
寻找所有不同的正整数对 $
(X_A	,Y_A)$，$(X_B,Y_B)$ 使得：对于给定的正整数 $L$，满足 $X_A \times Y_A+X_B \times Y_B \le L$。
## 题解
首先考虑暴力。

可将 $L$ 拆成所有可能的两个正整数之和，这一点利用代码很容易做到。

然后将每对可能的正整数中每一个又拆成两个正整数之积，显然，方案数为 $d(n)$，即这个正整数的正因子个数。再利用乘法原理，相乘再求和即可。

$80pts$：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mxn=1.05e6+2;//2^20
int f[mxn],n;//f[i]=d(i)
inline void pre(int x){
	bool fl=0;
	for(int i=1;i*i<=x;i++){
		f[x]+=!(x%i);
		if(i*i==x) fl=1;
	}
	f[x]<<=1;
	f[x]-=(fl);
}
unsigned long long ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) pre(i);
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			ans+=f[j]*f[i-j];
		}
	}
	cout<<ans<<endl;
}
```
时间复杂度：$O(L^{2})$。

如何优化？

注意到：我们计算答案时，使用以下公式，从而产生 $O(L^{2})$ 的时间开销：

$$
ans = \sum_{i=1}^L \sum_{j=1}^{i-1} f(i) \times f(i-j)
$$

利用乘法分配律，得到以下简化：

$$
ans = \sum_{i=1}^L ({f(i)} \times \sum_{j=1}^{i-1} f(i-j))
$$

又注意到：右半部分中是一个区间求和，可以维护一个前缀和数组，时间复杂度优化成 $O(L)$，是这样吗？

其实，现在的时间瓶颈已经转移到计算 $f$ 数组，上面代码暴力计算，复杂度达到 $O(L \sqrt{L})$，$L=10^{6}$ 一般不给过，不过这题时限 $5s$，能过。

事实上，$d(n)$ 还可以通过以下代码计算，时间复杂度更优：

```cpp
inline void pre(int x){//通过枚举每个数的倍数实现
	for(int j = x; j <= n; j += x) f[j]++;
}
```
上述为一个[调和级数求和](https://baike.baidu.com/item/%E8%B0%83%E5%92%8C%E7%BA%A7%E6%95%B0/8019971)，时间复杂度为 $O(L \log
{L})$。

AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mxn = 1.05e6 + 2;
int f[mxn], s[mxn], n;
#define reg register int

inline int fastread() {
	reg res = 0;
	bool sign = 1;
	register char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') {
		ch = getchar();
	}
	if (ch == '-')
		sign = 0, ch = getchar();
	while (ch <= '9' && ch >= '0') {
		res = (res << 3) + (res << 1) + (ch ^ 48);
		ch = getchar();
	}
	return sign ? res : -res;
}

inline void write(long long s) {
	if (s < 0) {
		putchar('-');
		s = -s;
	}
	if (s >= 10) {
		write(s / 10);
	}
	putchar(s % 10 + '0');
}

inline void pre(int x){
	for(int j = x; j <= n; j += x) f[j]++;
}

long long ans;
int main(){
	n = fastread();
	for(int i = 1; i <= n; i++) pre(i);
	for(int i = 1; i <= n; i++) s[i] = s[i - 1] + f[i];//前缀和
	for(int i = 1; i < n; i++) ans += f[i] * s[n - i];
	write(ans);
}
```

---

## 作者：Lysea (赞：3)

### 题目大意

给定 $n$，求四元组 $(a,b,c,d)$ 个数，满足 $a\times b+c\times d\le n$，且 $a,b,c,d$ 都是正整数。

### 解法

考虑先预处理出每个数的因数个数 $t_i$，这是个比较套路的线性筛，可以做到 $O(n\log n)$。

这样对于满足 $x+y=k$ 的四元组个数就是 $t_x\times t_y$。

接下来考虑 $x+y\le n$ 中 $x$ 的贡献，很明显 $y\le n-x$，因此我们可以做一个 $t_i$ 的前缀和数组 $s_i$，$t_x\times s_{n-x}$ 就是 $x$ 的贡献，那么这部分的时间复杂度为 $O(n)$。

总体时间复杂度 $O(n\log n)$。

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1e18
#define N 1000005
using namespace std;
int n,p[N],pri[N],ans[N],cnt,len,a[N],fnt,fans;
void OLS(int x){
	for(int i=2;i<=x;i++) p[i]=1;
	for(int i=2;i<=x;i++){
		if(p[i]==1) pri[++cnt]=i,p[i]=i;
		for(int j=1;j<=cnt&&i*pri[j]<=x;j++){
			p[i*pri[j]]=pri[j];
			if(i%pri[j]==0) break;
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n,OLS(N-1);
	for(int i=1,k;i<=n;i++){
		k=i,fnt=len=0,ans[i]=1;
		while(k!=1){
			a[++fnt]=p[k];
			k/=p[k];
		}
		for(int j=1;j<=fnt;j++){
			if(j!=1&&a[j]!=a[j-1]){
				ans[i]*=(len+1);
				len=1;
			}
			else len++;
		}
		ans[i]*=(len+1);
	}
	for(int i=1;i<=n;i++){
		ans[i]+=ans[i-1];
	}
	for(int i=1;i<n;i++){
		fans+=ans[n-i]*(ans[i]-ans[i-1]);
	}
	cout<<fans;
	return 0;
}
```

---

## 作者：liuhaodong886 (赞：3)

对于 $X_A$ $X_B$ ，其乘积也为正整数，因此可以把每一个数的乘积和预处理出来, 预处理每一个数的乘积可以用欧拉筛，设 $X_A$ $X_B$ 乘积为 $k$ ,那么对于 $Y_A$   $Y_B$，其乘
积可以为 $1$ 到 $n-k$ ,于是可以用前缀和处理乘积的值，然后加起来。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6 + 5;
int n,prime[N],ans,a[N];
void prep(){
	for(int i=1;i<=n;++i){
		prime[i]=1;
	}
	for(int i=2;i<=n;++i){
		if(prime[i]==1){
			prime[i]=2;
			for(int j=i*2;j<=n;j+=i){
				int k=j,cnt=0;
				while(k%i==0){
					k/=i;
					cnt++;
				}
				prime[j]*=(cnt+1);
			}
		}
	}
}
signed main(){
	cin>>n;
	prep();
	for(int i=1;i<=n;++i){
		a[i]=prime[i]+a[i-1];
	}
	for(int i=1;i<n;++i){
		ans+=prime[i]*a[n-i];
	}
	
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：ryderyang (赞：0)

# 解题思路
题目其实就是让我们找出 $A$，$B$，$C$，$D$，使得：

$$
A \times C + B \times D \le n
$$

所以我们可以想到枚举 $A \times C$，然后计算 $A$ 和 $C$ 有多少种可能的取值，记作 $x1$。然后再计算不等式 $B \times D \le n - A \times C$ 中 $B$ 和 $D$ 有多少种可能的取值，记作 $x2$。我们最终的答案加上 $x1 \times x2$ 即可。更多细节可以看下面的分析。
### 用线性筛预处理约数个数
我们需要：
1. $vis_i$ 记录 $i$ 是不是质数。
2. $primes$ 记录所有的质数。
3. $d_i$ 表示 $i$ 的因数个数。
4. $minp_i$ 表示 $i$ 的最小质因数的幂次。




```cpp
void init(int maxn)
{
	d[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			primes.push_back(i);
			d[i]=2;//质数有2个因数，1和它自己
			minp[i]=1;
		}
		for(auto p:primes)
		{
			if(i*p>maxn)
			break;//超出范围了
			vis[i*p]=true;
			if(i%p==0)
			{
				minp[i*p]=minp[i]+1;
				d[i*p]=d[i]/(minp[i]+1)*(minp[i*p]+1);
				break;
			}
			else
			{
			    minp[i* p]=1;
               	d[i*p]=d[i]*2;	
			}
		}
	}
}
```
对于每一个 $2$ 跟 $maxn$ 之间的数字 $i$：
如果 $i$ 是一个质数：

  - 将数字 $i$ 加入质数列表。
  - $d_i$ 就是 $2$，因为它的因数只有 $1$ 和它本身。
  - $minp_i$ 就是 $1$，因为 $i^1=i$。

对于质数列表中的每一个质数 $p$：

  - 如果 $i \times p \ge maxn$，也就是超出范围了，结束循环。
  - 标记 $i \times p$ 为合数。

如果 $i$ 是 $p$ 的倍数（$p$ 是 $i$ 的最小质因数）：

  - $minp_{i \times p}$ 就是 $minp_i + 1$，因为它是在 $i$ 的基础上又乘以一次 $p$ 的。
  - $d_{i \times p}$ 就是 $d_i \times \frac{minp_{i \times p}+1}{minp_i+1}$。因为：

    - $d_i$ 可以表示为 $p ^ {minp_i+1} \times d_x$。
    - $d_{i \times p}$ 就可以表示为 $p ^ {minp_i+2} \times d_x$。而 $minp_i + 2$ 就是 $minp_{i \times p} + 1$。
  - 退出循环。
如果 $i$ 不是 $p$ 的倍数：

  - $minp_{i \times p}$ 就是 $1$。
  - $d_{i \times p}$ 就是 $d_i \times 2$，因为 $d_{i \times p} = d_i \times d_p = d_i \times 2$。
### 枚举
枚举 $1$ 到 $n-1$ 的数字，记作 $i$。我们只需计算 $i$ 的因数个数，再计算每一个小于等于 $n-i$ 的因数个数之和，让答案 $ans$ 加上他们的积。我们可以用前缀和。

# 上代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=(1<<20)+5;
vector<int> primes;
int vis[N],d[N],minp[N],n,ans,f[N];
void init(int maxn)
{
	d[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			primes.push_back(i);
			d[i]=2;//质数有2个因数，1和它自己
			minp[i]=1;
		}
		for(auto p:primes)
		{
			if(i*p>maxn)
			break;//超出范围了
			vis[i*p]=true;
			if(i%p==0)
			{
				minp[i*p]=minp[i]+1;
				d[i*p]=d[i]/(minp[i]+1)*(minp[i*p]+1);
				break;
			}
			else
			{
			    minp[i* p]=1;
               	d[i*p]=d[i]*2;	
			}
		}
	}
}
signed main()
{
	scanf("%lld",&n);
	init(n);
	for(int i=1;i<=n;i++)
	f[i]=f[i-1]+d[i];
	for(int i=1;i<=n-1;i++)
	ans+=d[i]*f[n-i];
	printf("%lld",ans);
	return 0;
}
```

---

