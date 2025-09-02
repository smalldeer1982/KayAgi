# [ABC159F] Knapsack for All Segments

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc159/tasks/abc159_f

長さ $ N $ の整数列 $ A_1 $, $ A_2 $, $ \ldots $, $ A_N $ と正の整数 $ S $ が与えられます。  
 $ 1\leq\ L\ \leq\ R\ \leq\ N $ をみたす整数 $ (L,\ R) $ の組について、$ f(L,\ R) $ を以下のように定めます。

- $ L\ \leq\ x_1\ <\ x_2\ <\ \cdots\ <\ x_k\ \leq\ R $ かつ $ A_{x_1}+A_{x_2}+\cdots\ +A_{x_k}\ =\ S $ を満たすような整数列 $ (x_1,\ x_2,\ \ldots\ ,\ x_k) $ の個数

$ 1\leq\ L\ \leq\ R\leq\ N $ を満たす整数 $ (L,\ R) $ の組すべてに対する $ f(L,\ R) $ の和を求めてください。ただし、答えは非常に大きくなることがあるので、$ 998244353 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ S\ \leq\ 3000 $
- $ 1\ \leq\ A_i\ \leq\ 3000 $

### Sample Explanation 1

それぞれ以下のように計算できて、その和は $ 5 $ です。 - $ f(1,1)\ =\ 0 $ - $ f(1,2)\ =\ 1 $ ($ (1,\ 2) $ の $ 1 $ つ) - $ f(1,3)\ =\ 2 $ ($ (1,\ 2) $ と $ (3) $ の $ 2 $ つ) - $ f(2,2)\ =\ 0 $ - $ f(2,3)\ =\ 1 $ ($ (3) $ の $ 1 $ つ) - $ f(3,3)\ =\ 1 $ ($ (3) $ の $ 1 $ つ)

## 样例 #1

### 输入

```
3 4
2 2 4```

### 输出

```
5```

## 样例 #2

### 输入

```
5 8
9 9 9 9 9```

### 输出

```
0```

## 样例 #3

### 输入

```
10 10
3 1 4 1 5 9 2 6 5 3```

### 输出

```
152```

# 题解

## 作者：hyxgg (赞：7)

[题目](https://www.luogu.com.cn/problem/AT_abc159_f)
## 思路
考虑每一个和为 $S$ 的子序列的贡献：

设子序列里最左边的位置为 $l$，右边为 $r$。显然这个序列的贡献为 $l(n-r+1)$。

也就是对于大于等于 $r$ 的每个位置都会创造 $l$ 的贡献。

容易想到一个思路，处理对于每个位置，其左边的子序列的 $l$ 的和，再加起来就行了。

那怎么处理呢？

很简单，写个背包，$dp[i]$ 为目前遍历到的位置左边的和为 $i$ 子序列的 $l$ 的和，在每个位置加上 $dp[S]$ 就行了。

## 代码
代码如下，有问题评论区见。
```
#include<iostream>
#include<cstdio>
#define ll long long
#define mod 998244353
using namespace std;
ll dp[3005],n,a[3005],s,z[3005],ans;
int main(){
	scanf("%lld%lld",&n,&s);
	for(ll i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		for(ll j=s-a[i];j>=1;j--){
			dp[j+a[i]]+=dp[j];
			dp[j+a[i]]%=mod;
		}
		dp[a[i]]+=i;
		dp[a[i]]%=mod;
		ans+=dp[s];
		ans%=mod;
	}
	printf("%lld",ans);
	return 0;
} 
```

---

## 作者：dd_d (赞：5)

## Sol:
首先考虑暴力怎么做。  
我们枚举 $l$ 和 $r$，然后在 $l$ 到 $r$ 这段区间里做一遍背包即可。  
显然这样的复杂度是 $O(n^3s)$。   
仔细一想很快就会发现枚举 $l$ 到 $r$ 这段区间的这个循环可以通过边做边枚的方式优化一层掉。  
那么时间复杂度就变为 $O(n^2s)$。  
这样做还是不够优，我们考虑更优的做法。   
我们考虑算每个数的贡献。  
我们假设已经选取了一个区间，左端点为 $l$，右端点为 $r$。  
那么这个区间对答案的贡献就是 $l*(n-r+1)$。  
记 $dp_i$ 为所有选数和为 $i$ 的方案的 $l$ 的和。 
我们可以用背包来维护这个和。  
假设当前的数为 $a_i$，那么我们对其进行分类讨论。  
1. 当 $a_i$ 是 $r$ 时，他对答案的贡献就是 
```cpp
		        dp[s-a[i]]*(n-i+1)
```
2. 当 $a_i$ 是 $l$ 时，则  
```cpp 
                 dp[a[i]]+=i 
```


## Code:  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int mod=998244353;
int n,s,a[1000001],dp[100001],ans;
signed main()
{
	n=read(); s=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	for (int i=1;i<=n;i++)
	{
		if (a[i]<s) (ans+=dp[s-a[i]]*(n-i+1))%=mod;
		if (a[i]==s) (ans+=i*(n-i+1))%=mod;  //小细节要注意。
		for (int j=s;j>=a[i];j--)
			(dp[j]+=dp[j-a[i]])%=mod;  //背包维护。
		(dp[a[i]]+=i)%=mod;
	}
	writeln(ans);
}



```


---

## 作者：ctq1999 (赞：3)

 $f[x]$ 表示目前和为x的所有左端点选择方案数。

我们现在要选择 $x_1,x_2,...x_k$ 满足 $a_{x_1}+a_{x_2}+...a_{x_k}=S$，那么左端点的范围是 $1~x_1$，右端点的范围是 $x_k~n$。

然后 $S$ 就是容量，转移即可。

更新 $ans$ 时，$f[s]$ 要乘上 $(n-i+1)$，因为终止于位置i的方案可以有 $(n-i+1)$ 个右端点可以选择

起点为i的方案左端点有i种选择,所以dp过程中 $f[a[i]]+=i$。

详情见程序。

```cpp
#include <bits/stdc++.h>

#define MAXN 3010
#define ll long long
#define mod 998244353

using namespace std;

ll n, tot, ans, s;

ll a[MAXN], f[MAXN]; 

int main() {
	int t;
	scanf("%lld%lld", &n, &s);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = s; j > a[i]; j--) {
			f[j] = (f[j] + f[j - a[i]]) % mod;
		}
		f[a[i]] = (f[a[i]] + i) % mod;
		ans = (ans + (n - i + 1) * f[s] % mod) % mod;
		f[s] = 0;
	}
	cout << (ll)ans << endl;
	return 0;
}
```

---

## 作者：Union_Find (赞：2)

题目很好理解，我们就先想暴力。

# 暴力

我们可以枚举所有区间，然后在上面跑背包，发现时间复杂度是 $O(n^3s)$ 的，离目标差很远。

```cpp
int main(){
	n = rd(), s = rd();	
	for (int i = 1; i <= n; i++) a[i] = rd();
	for (int l = 1; l <= n; l++) for (int r = l; r <= n; r++){
		for (int i = 1; i <= s; i++) f[i] = 0;
		f[0] = 1;
		for (int i = l; i <= r; i++)
			for (int j = s; j >= a[i]; j--)
				f[j] = (f[j] + f[j - a[i]]) % P;
		ans += f[s];
	}
	printf ("%lld", ans);
	return 0;
}
```

# 小优化

有认真看代码的话，可以很容易发现，$r$ 的遍历和 $i$ 的遍历是重合的，所以可以将二者合并成一个循环，时间复杂度 $O(n^2s)$。

太简单了，代码就不放了。

# 正解

其实剩下的就很简单了，我们考虑到之所以会时间复杂度那么高，就是因为我们枚举了所有区间。但实际上，我们可以算每一个区间对答案的贡献。

简单来说，就是每个区间会对答案产生 $l \times (n - r + 1)$ 的贡献，这样我们就可以把原来枚举 $[l, r]$ 改成枚举 $[1, r]$ 了，时间复杂度 $O(ns)$，可以通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 100005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, s, a[N], f[N], ans, P = 998244353;
int main(){
	n = rd(), s = rd();	
	for (int i = 1; i <= n; i++) a[i] = rd();
	for (int i = 1; i <= n; i++){
		if (a[i] < s) ans = (ans + f[s - a[i]] * (n - i + 1) % P) % P;
		if (a[i] == s) ans = (ans + i * (n - i + 1) % P) % P;
		for (int j = s; j >= a[i]; j--) f[j] = (f[j] + f[j - a[i]]) % P;
		f[a[i]] = (f[a[i]] + i) % P;
	}
	printf ("%lld", ans);
	return 0;
}

```

---

## 作者：_Gabriel_ (赞：2)

### 思路

本题要用 `DP`。

状态：$dp_{i,j}$ 表示前 $i$ 个数和为 $j$ 的总方案数。

状态转移方程 $dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-a_i}$，可以把 $dp$ 数组化成一维数组进行空间优化。

只要把每次计算完加上 $dp_m$ 即为答案。

**注意：别忘了模 $998244353$**。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll mod = 998244353;
const int N = 5e2 + 10;
int a[N], dp[N];

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		dp[0]++;
		for (int k = m; k >= a[i]; k--) {
			dp[k] = (dp[k] + dp[k - a[i]]) % mod;
		}
		ans = (ans + dp[m]) % mod;
	}
	cout << ans;
    return 0;
}
```

---

## 作者：Lskkkno1 (赞：2)

- [AT5282 [ABC159F] Knapsack for All Segments](https://www.luogu.com.cn/problem/AT5282)

### 题目描述


求 $A$ 的所有连续子段的 "子序列中元素的和等于 $S$ 个数" 的和。 

### 正解

求一个连续子段等于 $S$ 的个数，可以用背包做到 $O(n^2)$。

但要对于每一个区间做一次背包，复杂度实在过不去。

考虑一个子序列在 $A$ 中产生的贡献（所有连续子段中的出现次数）。

子序列左端点是 $l$，右端点是 $r$ 的话，那么产生的贡献就是 $l \times (n - r + 1)$。

发现这个贡献只与左右端点有关，那么就再做背包的时候魔改一下。

具体是这样实现的：

加入背包的时候，

1. 如果当前没有放元素，那么乘上一个 $l$ 的系数 （即加上 $l$ 而不是加 1）。（左端点的贡献）

2. 如果放入当前元素背包满了，那么对答案产生 $f_s \times (n - r  + 1)$ 的贡献。（右端点的贡献）

3. 否则就按普通背包做就行了。

$\color{DeepSkyBlue} Code :$

```cpp
#include <bits/stdc++.h>
#define N 3005

using namespace std;

const int mod = 998244353;

int n, S;
int a[N], f[N];

int main() {
	scanf("%d %d", &n, &S);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		if(a[i] > S) continue;
		else if(a[i] == S) {
			ans = (ans + 1LL * i * (n - i + 1)) % mod;
		} else {
			ans = (ans + 1LL * f[S - a[i]] * (n - i + 1)) % mod;
			for(int j = S; j > a[i]; --j)
				(f[j] += f[j - a[i]]) %= mod;
			f[a[i]] = (f[a[i]] + i) % mod;
		}
	}
	
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：EastPorridge (赞：1)

给一种题解区没有的做法，挺简单的吧。

一开题解区全是分析的高级 $01$ 背包，哈哈，我不会。

### 题目分析：

考虑一个最简单的问题，求 $[1,n]$ 的子序列有多少等于 $S$ 呢？

这东西显然可以生成函数，对于每一位，要么选要么不选，$a_i$ 的贡献就直接写成 $(1+x^{a_i})$，则整个函数表达出来就是：

$$f([1,n])=(1+x^{a_1})(1+x^{a_2}) \cdots (1+x^{a_n})$$

答案就是这个多项式的第 $S$ 项系数。

推广到原问题就是求 $l,r$ 满足 $1 \le l < r \le n$ 下的 $f([l,r])$ 的第 $S$ 项系数和。

直接做 $O(n^3)$ 的，有点难受，考虑点优化。

其实这个东西就是一个乘法分配律，用 $g_i$ 表示 $(1+x^{a_i})$，假如现在 $n=3$，把式子写出来：

$$g_1 + g_1 g_2 + g_1 g_2 g_3 + g_2 +g_2 g_3+g_3$$

提出来，

$$g_1(1+ g_2 +g_2 g_3)+g_2(1+g_3)+g_3$$

看明白了吗？化简后的式子第 $i$ 项的式子就是第 $i+1$ 项加 $1$ 再乘 $g_i$，第 $n$ 项就是 $g_n$。

要对它使用高级的 $\texttt{NTT}$ 吗？大可不必，大于 $S$ 的项永远不会对 $S$ 有贡献，所以我们只处理到 $S$，每次乘一个二项式，直接乘就是带两倍常数的 $O(S)$，整体复杂度 $O(nS)$。

或者直接对上面那个式子做类似 $01$ 背包的 dp，也是 $O(nS)$ 的，方法差不多，不再赘述。

---

## 作者：guozhetao (赞：0)

## 链接
[我的 AC 链接](https://atcoder.jp/contests/abc159/submissions/55362713)

[在洛谷中查看题目](https://www.luogu.com.cn/problem/AT_abc159_f)

[在 atcoder 中查看](https://atcoder.jp/contests/abc159/tasks/abc159_f)
## 题意
给定一个长度为 $N(1\leq N\leq3\times10^3)$ 的正整数序列 $A(1\leq A_i\leq3\times10^3)$。

定义 $f(L,R)$ 表示 $A$ 从 $L$ 位置到 $R$ 位置这一子串（子串无需连续），有多少子序列的和等于 $S(1\leq S\leq3\times10^3)$。

求所有 $f(L,R)$ 的和，答案对 $998244353$ 取模。

注：后文用 $p$ 代表模数 $998244353$。


## 思路
让 $dp_{i,j}$ 代表当查找到前 $i$ 个数时总和为 $j$，则转移方程易得为：

$$dp_{i,j} \gets (dp_{i-1,j} + dp_{i-1,j-a_i}) \bmod p$$

因为每次枚举 $dp_{i,j}$ 都只要用到 $dp_{i - 1,x}$，因此可以省去一维，即用 $dp_j$ 表示上文 $dp_{i,j}$。

如果只考虑 $A_i = S$ 的情况，则可得出有 $i$ 种右端点为 $i$ 的方案，所以对于每个 $i$，$dp_0 \gets i$。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int p = 998244353;
using namespace std;
int ans,n,s,a[3005],dp[3005];
signed main() {
	scanf("%lld %lld",&n,&s);
	for(int i = 1;i <= n;i++) scanf("%lld",&a[i]);
	for(int i = 1;i <= n;i++) {
		dp[0]++;
		for(int j = s;j >= a[i];j--) {
			dp[j] = (dp[j] + dp[j - a[i]]) % p;
		}
		ans += dp[s];
		ans %= p;
	}
	printf("%lld\n",ans);
	return 0;
}


```

---

## 作者：crzcqh (赞：0)

思路：

暴力会 TLE，所以考虑求贡献。

对于任意 $l,r$，如果 $\sum\limits_{i=l}^{r} A_i = S$，则有 $1\le i\le l$ 和 $r\le j  \le n$ 存在 $f(i,j)$ 贡献一次的情况，所以区间 $l,r$ 的贡献即为 $l\times (n-r+1)$。

我们遍历 $A_i$，设 $f_j$ 为所有 $\sum\limits_{i=l}^{r}=j$ 的情况下 $l$ 的和，维护若干个数的和等于一个定值很明显使用背包。进行分类讨论后，有以下情况：

1. $dp_i=dp_i+dp_{i-A_i}$。
2. $dp_{A_i}=dp_{A_i}+i$。

进行 dp 后，每次贡献即为 $f_S \times (n-r+1)$，最后累加答案即可。

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define M 3005
#define mod 998244353
using namespace std;
ll n,k,ans;
ll a[M],dp[M];
int main(){
	cin>>n>>k;
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	for(ll i=1;i<=n;i++){
		if(a[i]<k)
			ans+=dp[k-a[i]]*(n-i+1),
			ans%=mod;
		if(a[i]==k)
			ans+=i*(n-i+1),
			ans%=mod;
		for(ll j=k;j>=a[i];j--)
			dp[j]+=dp[j-a[i]],
			dp[j]%=mod;
		dp[a[i]]+=i,
		dp[a[i]]%=mod;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Not_defined (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc159_f)
### 思路
这是一个背包计数问题，令 $f_{i,j}$ 表示前 $i$ 个数凑成 $j$ 的方案数。状态转移方程：$f_{i,j}=f_{i-1,j}+f_{i-1,j-a_{i}}$。我们可以考虑用滚动数组进行优化，设选择的左边位置为 $pos_{l}$ 右边位置为  $pos_{r}$，对于每种 $f_{1,n}$ 的方案他被算了$pos_{l}\times (n-pos_{r}+1)$ 次。边界条件：$f_{i,a_{i}}=f_{i,a_{i}}+i$ (以 $a_{i}$ 为最左边选的数)。时间复杂度：$O(n^{2})$。

### My code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=101010,mod=998244353;
int n,S,a[N],dp[N],res;
signed main()
{
	cin>>n>>S;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		dp[0]=i; 
		for(int j=S;j>=a[i];j--)
			(dp[j]+=dp[j-a[i]])%=mod;
		(res+=dp[S])%=mod;
	}
	cout<<res;
	return 0;
}
```


---

## 作者：highkj (赞：0)

# 思路
我们可以发现这道题只能用动态规划来做，那么我们就来思考下如何定义状态，我们可以用 $f_{i,j}$ 定义前 $i$ 个数中合为 $j$ 的方案数但是我们可以发现其实我们只要用两维即可，所以我们可以将这个二维数组优化成一维的，就只要 $f_j$ 那么我们就可以想到一个转移方程就是 $f_j=(f_j+f_{j-a_i})$ 就是加上 $a_i$ 和不加上 $a_i$ 的，然后我们在每一次求完答案后将答案加上 $f_s$ 即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;--i)
#define fire signed
void read(int &ff) {
	char c=getchar();
	int f=1;
	int x=0;
	while(c>'9'||c<'0') {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c<='9'&&c-'0'>=0) {
		x=x*10+c-'0';
		c=getchar();
	}
	ff=x;
}
int n,s,res;
int a[101010];
int f[101010];
const int mod=998244353;
fire main() {
	read(n),read(s);
	rep(i,1,n) read(a[i]);
	rep(i,1,n) {
		f[0]=i; //初始化（其实就是一个组合数学我们左端点为1右端点为1到i一共i种）
		rep1(j,s,a[i]) (f[j]+=f[j-a[i]])%=mod; //转移
		(res+=f[s])%=mod; //累加答案
	}
	cout<<res<<endl;
	return false;
}
```

---

## 作者：CQ_Bab (赞：0)

# 思路
我们这道题就可以想到动态规划好吧。那么我们就来想一下 $f_i$ 表示什么，我们可以令 $f_i$ 为合为 $i$ 时左端点的总方案数，那么我们假设满足条件的左右端点为 $i,j$ 那么它的贡献就为 $i\times(n-j+1)$ 这个是因为我们只要取的 $x,y$ 在 $i,j$ 以外并且包含 $i,j$ 即可。那么我们只需要在每次统计完成后将答案加上 $f_s\times (n-i+1)$ 就行了。然后我们考虑一下初始化，其实就是 $l$ 和 $r$ 相等的情况那么总方案数就是 $i$ 了，切记这个初始化要在求完值后进行毕竟最大就只能遍历到 $i$ 了，还要在一次结束后将 $f_s$ 归零，然后我们来推状态转移方程其实和背包差不多，我们就将 $f_j$ 加上 $f_{j-a_i}$ 即可。
# 代码
```
#include <bits/stdc++.h>
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
using namespace std ;
int n,s,a[1010101],res,f[1010101];
const int mod=998244353;
signed main() {
	cin>>n>>s;
	rep(i,1,n) cin>>a[i];
	rep(i,1,n) {
		rep1(j,s,a[i]) {
			f[j]=(f[j]+f[j-a[i]])%mod;//求值
		}
		f[a[i]]=(f[a[i]]+i)%mod; //初始化
		res=(res+f[s]*(n-i+1)%mod)%mod;
		f[s]=0;
	}
	cout<<res<<endl;
	return false;
}

```

---

## 作者：极寒神冰 (赞：0)

先考虑最暴力做法——每次暴力枚举$L$和$R$,然后通过01背包统计当前体积为$S$的物品数量。这样的复杂度是$O(n^3)$的。

```
R(L,1,n)
R(i,1,n)
{
	L(j,1,S-a[i]) Add(dp[j+a[i]],dp[j]);
	Add(dp[a[i]],1);
	Add(res,dp[S]);
}
```

但是因为是要求出所有$f(l,r)$的和，所以事实上我们并不用枚举这个$L$

直接$Add(dp[a[i]],l)$即可

```cpp
int n,S;
int dp[N];
int res;
signed main()
{
	n=read(),S=read();
	R(i,1,n)
	{
		int x=read();
		L(j,1,S-x) Add(dp[j+x],dp[j]);
		Add(dp[x],i);
		Add(res,dp[S]);
	}
	printf("%lld\n",res);
}
```


---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT5282) & [AtCoder题目页面传送门](https://atcoder.jp/contests/abc159/tasks/abc159_f)

>给定$n$个整数，第$i$个数为$a_i$。定义$f(l,r)$表示$[l,r]$内和为$m$的集合的数量。求$\sum\limits_{i=1}^n\sum\limits_{j=i}^nf(i,j)$。答案对$998244353$取模。

>$n,m,a_i\in[1,3000]$。

考虑算贡献法。对于某个集合$\{a_{x_i}\mid i\in[1,k]\}$，其中$x_1<x_2<\cdots<x_k$，区间$[l,r]$包含它当且仅当$l\in[1,x_1],r\in[x_k,n]$，所以此集合对答案的贡献为$x_1(n-x_k+1)$。

看到“和为某数”一类的问题，不难想到类似背包的值域DP。设$dp_{i,j}$表示考虑到第$i$个数，所有和为$j$的集合最左边的位置之和。边界是$dp_{0,i}=0$，目标是$\sum\limits_{i=1}^n\begin{cases}0&m<a_i\\i(n-i+1)&m=a_i\\dp_{i-1,m-a_i}(n-i+1)&m>a_i\end{cases}$（枚举和为$m$的集合最右边的位置贡献答案），状态转移方程是$dp_{i,j}=dp_{i-1,j}+[j=a_i]i+\begin{cases}dp_{i-1,j-a_i}&j\geq a_i\\0&j<a_i\end{cases}$。时间复杂度$\mathrm O(nm)$。

另外，此状态转移方程与01背包极其相似，可以用类似01背包的方式将DP数组压成一维，并在每次用$a_i$更新$dp'$之前及时将$i$作为和为$m$的集合最右边的位置贡献答案。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int N=3000,M=3000;
int n,m;
int a[N+1];
int dp[M+1];//dp' 
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		if(m==a[i])(ans+=1ll*i*(n-i+1)%mod)%=mod;
		else if(m>a[i])(ans+=1ll*dp[m-a[i]]*(n-i+1)%mod)%=mod;//更新答案 
		for(int j=m;j>=a[i];j--)(dp[j]+=dp[j-a[i]]+(j==a[i]?i:0))%=mod;//转移 
	}
	cout<<ans;
	return 0;
}
```

---

