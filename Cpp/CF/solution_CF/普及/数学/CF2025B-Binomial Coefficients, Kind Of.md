# Binomial Coefficients, Kind Of

## 题目描述

Recently, akshiM met a task that needed binomial coefficients to solve. He wrote a code he usually does that looked like this:

```
<pre class="verbatim">    for (int n = 0; n < N; n++) { // loop over n from 0 to N-1 (inclusive)<br></br>        C[n][0] = 1;<br></br>        C[n][n] = 1;<br></br>        for (int k = 1; k < n; k++) // loop over k from 1 to n-1 (inclusive)<br></br>            C[n][k] = C[n][k - 1] + C[n - 1][k - 1];<br></br>    }<br></br>
```

Unfortunately, he made an error, since the right formula is the following:

```
<pre class="verbatim">            C[n][k] = C[n - 1][k] + C[n - 1][k - 1]<br></br>
```

But his team member keblidA is interested in values that were produced using the wrong formula. Please help him to calculate these coefficients for $ t $ various pairs $ (n_i, k_i) $ . Note that they should be calculated according to the first (wrong) formula.

Since values $ C[n_i][k_i] $ may be too large, print them modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
7
2 5 5 100000 100000 100000 100000
1 2 3 1 33333 66666 99999```

### 输出

```
2
4
8
2
326186014
984426998
303861760```

# 题解

## 作者：Chenyanxi0829 (赞：3)

由于 $C_{n,0}=1$，所以当 $k=0$ 时，$C_{n,k}$ 的值相等。而之后的 $C_{n,k}=C_{n,k-1}+C_{n-1,k-1}$，于是可以依次推出 $C_{n,k}$ 当 $k$ 一定时是一样的，所以可以直接把 $n$ 那一位去掉，于是 $C_k$ 的递推式就是 $C_k=2C_{k-1}$，那么 $C_k$ 就是 $2^k$，一开始预处理出 $2^i\bmod (10^9+7)$ 就做完了。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e5, mod = 1e9 + 7;

int a[kMaxN], t;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  a[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    a[i] = a[i - 1] * 2 % mod;
  }
  cin >> t;
  for (int i = 1, x; i <= t; i++, cin >> x) {
  }
  for (int i = 1, x; i <= t; i++) {
    cin >> x, cout << a[x] << '\n';
  }
  return 0;
}
```

---

## 作者：sherry_lover (赞：1)

# CF2025B Binomial Coefficients, Kind Of 题解

[题目传送门](https://www.luogu.com.cn/problem/CF2025B)

## 思路

考虑打表找规律：

|n/k|0|1|2|3|4|
|:-:|:-:|:-:|:-:|:-:|:-:|
|0|1|||||
|1|1|1||||
|2|1|2|1|||
|3|1|2|4|1||
|4|1|2|4|8|1|

容易发现，当 $n = k$ 或 $k = 0$ 时，$C_{n,k} = 1$。否则 $C_{n,k} = 2^k$。再观察数据范围，$1 \le k_i < n$，就不需要考虑前面的情况了。

可以用数学归纳法证明。~~读者自证不难。~~

已知 $C_{0,0}$ 到 $C_{i,j-1}$ 的每一项都符合上面的规律，要证 $C_{i,j}$ 也符合上面的规律。

1. 当 $j = 0$ 或 $j = i$ 时，由 `C[n][0] = 1;C[n][n] = 1;` 可得命题成立。
2. 否则由 `C[n][k] = C[n][k - 1] + C[n - 1][k - 1];` 可以得出，$C_{i,j} = C_{i-1,j-1} + C_{i,j-1} = 2^{j-1} + 2^{j-1} = 2^j$，即命题对 $C_{i,j}$ 成立。

所以命题成立。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
int T,k;
long long Pow[100005];
void init()
{
	Pow[0] = 1;
	for(int i = 1;i < 100000;i++) Pow[i] = (Pow[i-1] << 1)%mod;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	init();
	for(int i = 1;i <= T;i++) cin >> k;
	for(int i = 1;i <= T;i++)
	{
		cin >> k;
		cout << Pow[k] << "\n";
	}
	return 0;
}
```

---

## 作者：DragonForge (赞：1)

## 题解：CF2025B Binomial Coefficients, Kind Of

其实这道题不难，它的关键便是观察与推导公式。其他的题解已经讲的很精确了，在这里我再详细的完善和说明一下过程。

### Part.1 观察样例

这是一道有多测的题，观察样例会发现，**好像每一组输出的数都是 2 的幂次方**。这是一个非常重要的发现，我们可以凭借这一点进行合理的猜想与推断。

### Part.2 推导公式

发现题解区里大家推导的方式都大同小异，于是我决定整合一下大家的思路。

---

#### 当 $k=1$ 时，
$C_{n,k}=C_{n,k-1}+C_{n-1,k-1}$ 可以简写为 $C_{n,1}=C_{n,0}+C_{n-1,0}$。因为我们知道 $C_{n,0}=1$，所以 $C_{n,1}=1+1=2$。将 $k=2$ 代入又可以得到有关 $C_{n,2}$ 的值。整理后可以得到：


||0|1|2|3|4|
|:-:|:-:|:-:|:-:|:-:|:-:|
|**0**|1|||||
|**1**|1|1||||
|**2**|1|2|1|||
|**3**|1|2|4|1||
|**4**|1|2|4|8|1|
|**5**|1|2|4|8|16|

因此我们发现，其实 $C_{n,k}$ 的值和 `n` 没有什么必要的联系，只需要分两种情况讨论：
1. $n=k$，直接输出 1；
2. $n \ne k$，输出 $2^k$ 即可。
### Part.3 重要细节

其实这一点是很多选手在比赛时最容易忘记的点，但是多多对拍就能很容易的避开它——`long long`。尽管这道题可能并不需要这一点，但是见到 $10^9+7$ 这么大的数字我还是保险的开了 `long long`。

### 总结
综上所述，这道题是需要严谨的推理才能得到正确的公式的，这道题的陷阱就在于 `n` 与 `k` 的关系上，如果忽略了这一点就很容易失分。

---

## 作者：xyin (赞：1)

这种给出了一段代码的题，最好先手模样例，看不出来什么性质就打表。

手模样例，我们就能找到一个很显然的规律：如图为一个 $n$ 行 $k$ 列的答案矩阵，发现对于每一个 $n$，当 $k=n$ 的时候，$C_{n,k}=1$；否则 $C_{n,k}=2^{k}$。

||0|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|0|1||||||
|1|1|1|||||
|2|1|2|1||||
|3|1|2|4|1|||
|4|1|2|4|4|1||
|5|1|2|4|4|4|1|

$1\le t\le 2\times 10^5$，我们甚至都不用预处理 $2^k$，就能通过这道题了，时间复杂度 $O(t\log k)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define pb push_back
#define pp pop_back
#define pai pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
const int maxn=1e5+5;
const int INF=1e18;
const int mod=1e9+7;
int read(int x=0,bool f=1,char c=0){
    while (!isdigit(c=getchar())) f=c^45;
    while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return f?x:-x;
}
int T,a[maxn],b[maxn];
int qpow(int a,int b){
    int res=1;
    while (b){
        if (b&1) res=res*a%mod;
        a=a*a%mod;b>>=1;
    }
    return res;
}
signed main(){
    T=read();
    for (int i=1;i<=T;i++)
        a[i]=read();
    for (int i=1;i<=T;i++)
        b[i]=read();
    for (int i=1;i<=T;i++)
        if (a[i]==b[i]) printf("1\n");
        else printf("%lld\n",qpow(2,b[i]));
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

$$f(n,0)=1,f(n,k)=1+\sum_{i=0}^{k-1}f(n-1,i)=2^k$$

我感觉这东西能直接看出来。

当然选手注意力不太集中没能看出来，可以靠样例或者打表猜出结论。

想证明直接上数学归纳法，相当容易。

---

## 作者：wuyouawa (赞：1)

### 题目大意

有 $t$ 组数据，每组数据给定 $n,k$，有递推式 $C_{n,\ k}=C_{n,\ k-1}+C_{n-1,\ k-1}$，以及 $C_{n,\ 0}=1,C_{n,\ n}=1$，求 $C_{n,\ k}$。

### 思路

很明显，这题如果我们暴力去求 $C_{n, \ k}$ ，在 $n,k \le 10^5$ 的情况下是会超时的。那么我们考虑找规律优化，那么可以先把 $k=1$ 的情况带入看看。

当 $k=1$ 时，可得如下算式

 $$C_{n,\ 1}=C_{n,\ 0}+C_{n-1,\ 0}$$

 $C_{n,\ 0}$ 我们已经算好了是 $1$，$C_{n-1,\ 0}$ 之前也算过是 $1$。那么 $C_{n,\ 1}$ 就等于 $1+1=2$，那么 $C_{n,\ 2}$ 也同理，最后我们得出 $C_{n,\ k}=2^k$，然后就可以直接算了。

注意 $2^{10^5}$ 会非常大，题目中说了要对 $10^9+7$ 取模。而且我们要用一个数组 $f$ 预处理 $2^k \bmod 10^9+7$，因为 $O(tk)$ 的时间复杂度还是无法通过。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod = 1e9+7; //初始化模数
long long n[100005], k[100005], t, f[100005];
int main() {
	cin >> t;
	f[0] = 1; //2的0次方为1
	for (int i = 1; i <= 100000; i++) {
		f[i] = f[i - 1] * 2 % mod; //根据余数的可乘性，可以乘一次模一次
	}
	for (int i = 1; i <= t; i++) { //t组数据
		scanf("%lld", &n[i]);
	}
	for (int i = 1; i <= t; i++) {
		scanf("%lld", &k[i]);
	}
	for (int i = 1; i <= t; i++) {
		printf("%lld\n", f[k[i]]); //scanf和printf快点
	}
	return 0;
}
```

---

## 作者：A_R_O_N_A (赞：1)

## 题意

有一个人写了一段代码用于解决一个需要二项式系数的问题：


```cpp
for (int n = 0; n < N; n++) { // loop over n from 0 to N-1 (inclusive)
    C[n][0] = 1;
    C[n][n] = 1;
    for (int k = 1; k < n; k++) // loop over k from 1 to n-1 (inclusive)
        C[n][k] = C[n][k - 1] + C[n - 1][k - 1];
}
```

但很遗憾，他写错了，正确的公式应该是下面这个：

$$C_{n,k}=C_{n-1,k}+C_{n-1.k-1}$$

```cpp
C[n][k] = C[n - 1][k] + C[n - 1][k - 1]
```

但是他的一群同志们对这一段错误的代码输出的结果十分感兴趣，他们想知道对于一对整数 $(n,k)$，上面给出的错误代码的结果会是多少？

多测，$t$ 组数据，$1\le t\le 10^5$，对于每一个 $n_i,k_i$ 满足：$2\le n_i\le 10^5$，$1\le k_i< n_i$。

由于结果太大，你需要对 $10^9+7$ 取模。

## 分析

首先我们可以知道这代码本来是拿来求杨辉三角的。由于 $\sum n$ 可能达到 $10^{10}$ 的规模，所以单次的查询复杂度需要在 $\log$ 级及以下。所以要么 $O(n)$ 或 $O(n\log n)$ 预处理，$O(1)$ 查询，要么就不预处理，$O(\log n)$ 或 $O(\log k)$ 查询。

我考虑的是 $O(\log n)$ 或 $O(\log k)$ 查询的思路。这时候就可以选择代入小样例观察结果规律入手。这里提供一下打表程序：

```cpp
	n=read();k=read();
	for(int i=0;i<n;i++){
		dp[i][0]=1;
		dp[i][i]=1;
		for(int j=1;j<i;j++){
			dp[i][j]=dp[i][j-1]+dp[i-1][j-1];
		}
	}
	freopen("text.txt","w",stdout);
	for(int i=0;i<n;i++){
		for(int j=1;j<i;j++){
			printf("(%d,%d)=%lld ",i,j,dp[i][j]);
		}
		puts("");
	}
```

$n=k=10$ 的情况下得到输出：


```
(2,1)=2 
(3,1)=2 (3,2)=4 
(4,1)=2 (4,2)=4 (4,3)=8 
(5,1)=2 (5,2)=4 (5,3)=8 (5,4)=16 
(6,1)=2 (6,2)=4 (6,3)=8 (6,4)=16 (6,5)=32 
(7,1)=2 (7,2)=4 (7,3)=8 (7,4)=16 (7,5)=32 (7,6)=64 
(8,1)=2 (8,2)=4 (8,3)=8 (8,4)=16 (8,5)=32 (8,6)=64 (8,7)=128 
(9,1)=2 (9,2)=4 (9,3)=8 (9,4)=16 (9,5)=32 (9,6)=64 (9,7)=128 (9,8)=256 
```

注意到 $n$ 对于答案无影响，$(n,k)$ 所对应的答案为 $2^k$。

这里结果已经很显然了，不过为了严谨我们可以尝试证明一波：

设 $C$ 为答案数组，且 $\forall i\in [0,n-1]$，有 $C_{i,0}=C_{i,i}=1$，同时有转移方程：

$$C_{i,j}=C_{i,j-1}+C_{i-1,j-1}(1\le j < i)$$

因为 $1\le j<i$，所以当 $i\ge 2$ 时才会进行转移，又因为 $C$ 数组拥有边界，所以当 $j=1$ 时，原方程变为：

$$C_{i,1}=C_{i,0}+C_{i-1,0}$$

因为 $C_{i,0}=C_{i-1,0}$，所以可以继续转化成为：

$$C_{i,1}=C_{i,0}\times 2=C_{i-1,0}\times 2$$

显然有：

$$C_{i-1,1}=C_{i-1,0}\times 2$$

所以我们便证明出来了：$\forall i\in [2,n-1]$，有 $C_{i,1}=C_{i-1,1}$，同理一直证下去，可得出结论：$i$ 对 $C_{i,j}$ 的值**无影响**。于是我们回到上面去，把 $C$ 省掉一维：

$$C_j=C_{j-1}\times 2$$

得出结论：$C_{i,j}=2^j$，即 $C_{n,k}=2^k$。

那么这题就变成了多测快速幂板子题，代码就不给了。

---

## 作者：xiaobeng_0912 (赞：0)

## $\mathbf{Knowledge}$

1. 找规律

## $\mathbf{Solution}$

乍一看似乎没什么思路，所以我们可以找规律（题目规定 $k<n$，所以有一些部分可以省略）：

|$C_{n,k}=$|$k=0$|$k=1$|$k=2$|$k=3$|$k=4$|$k=5$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$n=0$|||||||
|$n=1$|$1$||||||
|$n=2$|$1$|$2$|||||
|$n=3$|$1$|$2$|$4$||||
|$n=4$|$1$|$2$|$4$|$8$|||
|$n=5$|$1$|$2$|$4$|$8$|$16$||

我们发现，对于任意一个符合题目规定的 $C_{n,k}$，结果为 $2^k$。然后，如果不想用快速幂，就直接先预处理所有情况（因为它只跟 $k$ 有关，所以时间复杂度是线性的，不用考虑 $n$ 到底是几）。

**最后，答案不要忘了对 $10^9+7$ 取模！**

## $\mathbf{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD=1e9+7;
int t,n[100001],k[100001];
long long a[100001]={1};//由于乘的过程中（还没有取模的时候）有可能爆 int，所以开 long long 保险
int main(){
	for(int i=1;i<=100000;i++){//预处理
		a[i]=a[i-1]*2%MOD;//可以边乘边取模
	}
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%d",&n[i]);
	}
	for(int i=1;i<=t;i++){
		scanf("%d",&k[i]);
		printf("%lld\n",a[k[i]]);//输出答案
	}
	return 0;
}
```

---

## 作者：huanglihuan (赞：0)

### Solution
很明显，当计算到程序第四行的时候，$C_{n,k-1}$ 和 $C_{n-1,k-1}$ 都被定义，而 $C_{0,0}=1$ 则 $C_{n,k}=C_{n,k-1}\times2$，舍弃前一项，则 $S_k=S_{k－1}\times2$，又因为 $S_0=1$，则 $S_k=2^k$，最后 $n=k$ 的情况要特判。
### Code
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 988444333
#define MOD 1000000007
using namespace std;
const int N = 2e6 + 5;
int a [N],b [N],s [N];
inline int read ()
{
	int x = 0;
	char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return x;
}
inline void write (int x)
{
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
signed main ()
{
	s [0] = 1;
	for (int i = 1;i < N;i ++) s [i] = s [i - 1] * 2 % MOD; 
	int n;
	cin >> n;
	for (int i = 1;i <= n;i ++) cin >> a [i];
	for (int i = 1;i <= n;i ++) cin >> b [i];
	for (int i = 1;i <= n;i ++)
	{
		if (a [i] == b [i]) cout << 1;
		else cout << s [b [i]];
		cout << endl;
	}
	return 0;
}
```

---

## 作者：lhc0707 (赞：0)

考点：求解递推式

为了与正常的 $C_{i}^j$ 区分，这里我们把题目中的 $C_{i}^j$ 记作 $f_{j}(i)$。

给的代码相当于递推式：

$$
f_{k}(n)=f_{k-1}(n)+f_{k-1}(n-1)
$$

问题让我们解这个式子。考虑爆拆，得：

$$
f_{k}(n)=f_{k-1}(n)+f_{k-1}(n-1)
\\=(f_{k-2}(n)+f_{k-2}(n-1))+(f_{k-2}(n-1)+f_{k-2}(n-2))
\\=f_{k-2}(n)+2f_{k-2}(n-1)+f_{k-2}(n-2
)
\\=f_{k-3}(n)+f_{k-3}(n-1)+2(f_{k-3}(n-1)+f_{k-3}(n-2)+f_{k-3}(n-2)+f_{k-3}(n-3))
\\=f_{k-3}(n)+3f_{k-3}(n-1)+3f_{k-3}(n-2)+f_{k-3}(n-3)
$$

注意到推到最后一行时系数是杨辉三角，并且考虑到对于每一个不在边上的项，前一层式子对这一项的贡献是两个相邻的系数相加，所以我们知道他的系数就是杨辉三角，也就是正派组合数。于是可以继续推关于 $f_{k}(n)$ 的式子：

$$f_{k}(n)=\sum_{i=0}^t f_{k-t}(n-i)\cdot C_{t}^i
\\=\sum_{i=0}^k f_{0}(n-i)\cdot C_{k}^i
$$

其中 $t$ 是一个整数，而第二行相当于 $t=k$ 时的情况。由题意我们知道 $f_{0}(x)=1$，故：

$$
f_{k}(n)=\sum_{i=0}^k C_{k}^i
$$

由二项式定理，得

$$
f_{k}(n)=2^k
$$

然后预处理 $2$ 的次幂就可以通过本题。

---

## 作者：coderJerry (赞：0)

大胆假设，小心求证！

|$k$ \ $n$|0|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|**0**|1|1|1|1|1|1|
|**1**|/|2|2|2|2|2|
|**2**|/|/|4|4|4|4|
|**3**|/|/|/|8|8|8|
|**4**|/|/|/|/|16|16|
|**5**|/|/|/|/|/|32|


通过观察样例和打表可知，$C[n][k]=2^k$。（推荐一道观察样例得出结论的题：[here](https://www.luogu.com.cn/problem/P9183)）

证明一下猜出的结论：

$$C[n][k]=C[n][k-1]+C[n-1][k-1]$$

$$=C[n][k-2]+C[n-1][k-2]+C[n-1][k-2]+C[n-2][k-2]$$

$$= C[n][k - 2] + 2 \cdot C[n - 1][k - 2] + C[n - 2][k - 2] =
$$

$$
= C[n][k - 3] + 3 \cdot C[n - 1][k - 3] + 3 \cdot C[n - 2][k - 3] + C[n - 3][k - 3] $$

系数是杨辉三角，且 $C[n][0]=C[n][n]=1$，所以根据杨辉三角的性质即得 $C[n][k]=2^k$。

---

## 作者：cly312 (赞：0)

根据题意，错误的递推公式是 $C_{n,k} = C_{n,k-1} + C_{n-1,k-1}$，而错误的 $C_{n,k} = C_{n-1,k} + C_{n-1,k-1}$ 。通过观察，可以发现对于 $k < n$ 的情况，$C_{n,k} = 2^k$。因此，我们只需预先计算 $2^k$，然后对于每个查询直接输出对应的结果。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD=1e9+7;
int main(){
	int t;
	cin>>t;
	vector<int> n(t);
	for(auto &x:n) cin>>x;
	vector<int> k(t);
	for(auto &x:k) cin>>x;
	int maxk=0;
	for(auto &x:k) maxk=max(maxk,x);
	vector<long long> pow2(maxk+1,1);
	for(int i=1;i<=maxk;i++) pow2[i]=(pow2[i-1]*2)%MOD;
	for(int i=0;i<t;i++) cout<<pow2[k[i]]<<"\n";
	return 0;
}
```

---

