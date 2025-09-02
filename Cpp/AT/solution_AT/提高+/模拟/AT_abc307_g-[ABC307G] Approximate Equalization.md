# [ABC307G] Approximate Equalization

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc307/tasks/abc307_g

長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。

高橋君は次の $ 2 $ 種類の操作のうち $ 1 $ つを選んで行う事を、何回でも ($ 0 $ 回でも良い) 繰り返し行う事ができます。

- $ 1\leq\ i\leq\ N-1 $ をみたす整数 $ i $ を選び、$ A_i $ を $ 1 $ 減らし、$ A_{i+1} $ を $ 1 $ 増やす。
- $ 1\leq\ i\leq\ N-1 $ をみたす整数 $ i $ を選び、$ A_i $ を $ 1 $ 増やし、$ A_{i+1} $ を $ 1 $ 減らす。
 
数列 $ A $ が次の条件をみたすようにするために必要な操作の回数の最小値を求めてください。

- 任意の $ 1 $ 以上 $ N $ 以下の整数の組 $ (i,j) $ に対して、$ \lvert\ A_i-A_j\rvert\leq\ 1 $ が成り立つ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5000 $
- $ \lvert\ A_i\ \rvert\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

次のようにして $ 4 $ 回の操作で $ A $ が条件をみたすようにできます。 - $ i=1 $ を選び、$ A_1 $ を $ 1 $ 増やし、 $ A_2 $ を $ 1 $ 減らす。$ A=(3,6,6) $ となる。 - $ i=1 $ を選び、$ A_1 $ を $ 1 $ 増やし、 $ A_2 $ を $ 1 $ 減らす。$ A=(4,5,6) $ となる。 - $ i=2 $ を選び、$ A_2 $ を $ 1 $ 増やし、 $ A_3 $ を $ 1 $ 減らす。$ A=(4,6,5) $ となる。 - $ i=1 $ を選び、$ A_1 $ を $ 1 $ 増やし、 $ A_2 $ を $ 1 $ 減らす。$ A=(5,5,5) $ となる。 この時操作回数が最小であり、よって $ 4 $ を出力します。

### Sample Explanation 2

次のようにして $ 2 $ 回の操作で $ A $ が条件をみたすようにできます。 - $ i=1 $ を選び、$ A_1 $ を $ 1 $ 減らし、 $ A_2 $ を $ 1 $ 増やす。$ A=(-3,-4,-2) $ となる。 - $ i=2 $ を選び、$ A_2 $ を $ 1 $ 増やし、 $ A_3 $ を $ 1 $ 減らす。$ A=(-3,-3,-3) $ となる。 この時操作回数が最小であり、よって $ 2 $ を出力します。

### Sample Explanation 3

うまく操作することで、$ 13 $ 回の操作の後で、 $ A=(0,0,-1,-1,-1) $ にでき、これは問題文の条件をみたします。 $ 12 $ 回以下の操作で条件をみたすようにすることはできないため、$ 13 $ を出力します。

## 样例 #1

### 输入

```
3
2 7 6```

### 输出

```
4```

## 样例 #2

### 输入

```
3
-2 -5 -2```

### 输出

```
2```

## 样例 #3

### 输入

```
5
1 1 1 1 -7```

### 输出

```
13```

# 题解

## 作者：xht (赞：4)

先算出最后结果的结构，注意对负数的处理。

然后就是 trivial 的 $\mathcal O(n^2)$ DP，$f_{i,j}$ 表示前 $i$ 个数转换成 $j$ 个较小值的最小步数，转移就是讨论当前数转换为较小值还是较大值。转移写出来后发现 `abs` 中的内容实际上是一样的。

```cpp
int main() {
	int n;
	cin >> n;
	vector<ll> a(n + 1), s(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i], s[i] = s[i-1] + a[i];
	ll w = s[n] / n, t = s[n] % n;
	if (t < 0) w--, t += n;
	vector<vector<ll>> f(n + 1, vector<ll>(t + 1, 1e18));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= t; j++) {
			f[i][j] = f[i-1][j] + abs(a[i] + s[i-1] - w * (i - 1) - j - w);
			if (j) f[i][j] = min(f[i][j], f[i-1][j-1] + abs(a[i] + s[i-1] - w * (i - 1) - (j - 1) - (w + 1)));
		}
	cout << f[n][t] << endl;
	return 0;
}
```

---

## 作者：FReQuenter (赞：3)

观察操作发现：$\sum^{n}_{i=1}a_i$ 不会改变。

也就是说，最后的数列中的每个数一定是 $\lfloor\frac{S}{n}\rfloor$ 或者 $\lfloor\frac{S}{n}\rfloor+1$（其中$S=\sum^{n}_{i=1}a_i$）

因为序列和是确定的，所以可以得出最终值为这两类数的分别有 $n-S+n\times \lfloor\frac{S}{n}\rfloor$ 和 $S-n\times \lfloor\frac{S}{n}\rfloor$ 个。

接下来考虑 dp。

令 $f_{i,j}$ 表示前 $i$ 个数中有 $j$ 个第二类数和 $i-j$ 个第一类数的最小花费。

考虑转移：最主要的问题是它将相邻的两个数绑在一起操作。

我们现在只考虑对于前 $i+1$ 个数的操作。因为总和不变，所以我们能得到这样一个式子，其中 $P$ 为改变后的 $a_{i+1}$：

$$P=\sum^{i+1}_{k=1}a_k-j\times(\lfloor\frac{S}{n}\rfloor+1)-(i-j)\times\lfloor\frac{S}{n}\rfloor$$

应该不难懂。就是前 $i+1$ 个数的和减掉前 $i$ 个数的组成部分（可以由当前 dp 状态推导出来）。

接下来就可以转移啦：

$$f_{i+1,j}=\min\{f_{i+1,j},f_{i,j}+|P-\lfloor\frac{S}{n}\rfloor|\}$$

$$f_{i+1,j+1}=\min\{f_{i+1,j+1},f_{i,j}+|P-(\lfloor\frac{S}{n}\rfloor+1)|\}$$

复杂度 $O(n^2)$。初值 $f=\{\inf\},f_{0,0}=0$。

$S$ 为负时要注意一些细节。

```cpp
#include<bits/stdc++.h>
#define MAXN 5005
#define int long long
using namespace std;
int n,S,a[MAXN],sum[MAXN],f[MAXN][MAXN];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],S+=a[i],sum[i]=sum[i-1]+a[i];
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	int tmp=S/n;
	if(tmp*n>S) tmp--;//负数时取整有问题 
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			int P=sum[i+1]-j*(tmp+1)-(i-j)*tmp;//同上 
			f[i+1][j]=min(f[i+1][j],f[i][j]+abs(P-tmp));
			f[i+1][j+1]=min(f[i+1][j+1],f[i][j]+abs(P-(tmp+1)));
		}
	}
	cout<<f[n][S-tmp*n];
	return 0;
}
```

---

## 作者：_Flame_ (赞：1)

### $\text{solution}$

看到两种操作都是一个数加一一个数减一，容易发现数列的和是不变的。

最后任意两个数相差不超过 $1$，所以数列中的所有数在最终状态下肯定都是 $\lfloor \frac{\sum\limits_{i=1}^{n} a_i}{n}\rfloor$ 或者 $\lfloor \frac{\sum\limits_{i=1}^{n} a_i}{n}\rfloor+1$ 其中之一，这两种的个数分别为 $n-\sum\limits_{i=1}^{n} a_i+n\times \lfloor \frac{\sum\limits_{i=1}^{n} a_i}{n}\rfloor$ 和 $\sum\limits_{i=1}^{n} a_i-n\times \lfloor \frac{\sum\limits_{i=1}^{n} a_i}{n}\rfloor$ 个。

设状态 $dp_{i,j}$ 为前 $i$ 个数中最后有 $j$ 个 $\lfloor \frac{\sum\limits_{i=1}^{n} a_i}{n}\rfloor+1$ 时候的最小操作次数。

考虑转移，讨论第 $i$ 个数是取 $\lfloor \frac{\sum\limits_{i=1}^{n} a_i}{n}\rfloor$ 还是 $\lfloor \frac{\sum\limits_{i=1}^{n} a_i}{n}\rfloor+1$，$a_i$ 经过前 $i-1$ 次操作后的值为 $\sum\limits_{i=1}^{i+1} a_i-i\times \lfloor \frac{\sum\limits_{i=1}^{n} a_i}{n}\rfloor -j$ 设其为 $k$，转移即为：

$$dp_{i+1,j}=\min(dp_{i+1,j},\mid k-\lfloor \frac{\sum\limits_{i=1}^{n} a_i}{n}\rfloor \mid)$$
$$dp_{i+1,j+1}=\min(dp_{i+1,j+1},\mid k-\lfloor \frac{\sum\limits_{i=1}^{n} a_i}{n}\rfloor -1\mid)$$

### $\text{code}$


```cpp

int n;

int a[maxn];

int dp[maxn][maxn];

int sum[maxn];

void init(){
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
}

void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	int cnt=sum[n]/n;
	int kk=sum[n]-cnt*n;
	if(kk<0){
		cnt--;
		kk=sum[n]-cnt*n;
	}
	init();
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			dp[i+1][j]=min(dp[i+1][j],dp[i][j]+abs(sum[i+1]-j*(cnt+1)-(i-j)*cnt-cnt));
			dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]+abs(sum[i+1]-j*(cnt+1)-(i-j)*cnt-(cnt+1)));
		}
	}
	int ans=dp[n][kk];
	write(ans);
	puts("");
	return ;
}
```

---

## 作者：氧少Kevin (赞：1)

# Abc307G - Approximate Equalization
- DP、序列变换最小操作

## 题意

给出一个长度为 $n(2\leq n\leq 5000)$ 的序列 $a(|a_i|\leq 10^9)$，需要让序列满足对于任意的 $1\leq i<j\leq n$ 有 $|a_i-a_j|<1$。

每次操作可以进行下面的操作之一：
- 令 $a_i:=a_i-1,a_{i+1}:=a_{i+1}+1$
- 令 $a_i:=a_i+1,a_{i+1}:=a_{i+1}-1$

问最小的操作次数。

## 思路
### hint 1
先考虑下面的问题：

给出两个长度均为 $n$ 的序列 $a,b$，保证 $\sum a_i = \sum b_i$，每次可以对 $a$ 进行题目所述操作，问要让 $a=b$ 的最小操作次数。

考虑对每个元素算贡献。

假设每个元素中途可以减为负数，那么可以从 $a_1$ 开始，依次处理到 $a_n$。

对于每个元素，计算它对答案的贡献。每个元素对答案的贡献是：$|a_i-\frac{sum}{n}|$。

同时，$a_i=b_i$，$a_i$ 的变化量是：$b_i-a_i$，需要将其支配给下一个元素，即 $a_{i+1}:=a_{i+1}+b_i-a_i$。

归纳一下，对于第 $a_i$ 来说，要让前面的元素都满足 $a_i=b_i$，$a_i$ 需要变成 $\sum_{j=1}^{i}|a_j-b_j|$。

因此，$a_i$ 对答案的贡献为：$\sum_{j=1}^{i}|a_j-b_j|$。将这 $n$ 个贡献相加就是答案。

### hint 2

回到本题，设所有元素加和为 $sum$。

不难发现，每种元素只可能是 $\lfloor\frac{sum}{n}\rfloor,\lfloor\frac{sum}{n}\rfloor+1$ 中的一种。

$\lfloor\frac{sum}{n}\rfloor+1$ 恰好有 $sum\mod n$ 个。

根据 hint1，用 $f_{i,j}$ 表示当前为第 $i$ 个元素，当前已经安放了 $j$ 个 $\lfloor\frac{sum}{n}\rfloor+1$，操作次数的最小值。

维护 $a$ 和 $b$ 的前缀和，转移即可。

---

## 作者：JWRuixi (赞：1)

~~应该去看一看这题的……~~

### 题意

给定序列 $\{a_n\}$，你可以对序列进行如下操作任意顺序任意多次：
- 选定 $i < n$，令 $a_i\gets a_i+1$，$a_{i+1}\gets a_{i+1}-1$。 
- 选定 $i < n$，令 $a_i\gets a_i-1$，$a_{i+1}\gets a_{i+1}+1$。

求令序列满足 $\forall (i,j),|a^\prime_i-a^\prime_j|\le1$ 的最少操作数。

### 分析

考虑每次一个数 $+1$ 一个数 $-1$，则整个序列的和不变，有序列极差不超过 $1$，则每个数要么是 $\lfloor \frac{S}{n}\rfloor$，要么是 $\lfloor \frac{S}{n}\rfloor+1$。既然终态这么少，那就可以考虑直接 `dp`。

设 $f_{i,j}$ 表示前 $i$ 个数中，有 $j$ 个变为了 $\lfloor \frac{S}{n}\rfloor+1$ 的最小操作数。我们考虑前 $i$ 个数操作，最多影响到 $[1,i+1]$ 这个区间。若 $pre_i=\sum\limits_{j=1}^ia_j$，当前考虑到 $f_{i,j}$ 的转移，显然前 $i+1$ 个数和不变，我知道前 $i$ 个数此时的值，那就有 $a^\prime_{i+1}=pre_{i+1}-i\lfloor\frac{S}{n}\rfloor-j$，有转移：

$$f_{i,j}+|a^\prime_{i+1}-\lfloor\frac{S}{n}\rfloor| \to f_{i+1,j}$$
$$f_{i,j}+|a^\prime_{i+1}-\lfloor\frac{S}{n}\rfloor-1| \to f_{i+1,j+1}$$

复杂度 $\mathcal O(n^2)$。

### code

<https://atcoder.jp/contests/abc307/submissions/42991077>

---

## 作者：_Kenma_ (赞：0)

# AT_abc307_g 解题报告

## 前言

做题时开始读成了相邻两个差不超过 $1$，结果连样例都模不过……

## 思路分析

首先有个很重要的观察：设总和为 $s$，目标数组中只含有 $\lfloor \frac{s}{n} \rfloor$ 和 $\lfloor \frac{s}{n} \rfloor+1$ 两种取值。

然后就可以直接 DP 了。

具体地，设 $f_{i,j}$ 表示前 $i$ 项中含有 $j$ 项的取值为 $\lfloor \frac{s}{n} \rfloor$。考虑每次修改一个数时都把多余的值往后面几项移动，结果一定不劣，所以可以转移：

$$f_{i,j}=\min( f_{i-1,j}+ \left| \sum_{k=1}^{i-1} a_k-j\cdot \lfloor \frac{s}{n} \rfloor -(i-j-2)\cdot (\lfloor \frac{s}{n} \rfloor+1) \right|, f_{i-1,j-1}+\left| \sum_{k=1}^{i-1} a_k-(j-2) \cdot \lfloor \frac{s}{n} \rfloor-(i-j) \cdot (\lfloor \frac{s}{n} \rfloor+1)\right|)$$

看起来很吓人，但是其实不难理解。

复杂度 $O(n^2)$。

也许可以参变分离单调队列做到 $O(n)$？但是那就有点困难了。

## 代码实现

不难写。

注意因为负数下取整很麻烦，可以全部取反，答案不变。

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[5005],s[5005],f[5005][5005],sum;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	if(sum<0){
		for(int i=1;i<=n;i++){
			a[i]*=-1;
		} 
		sum*=-1;
	}
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+a[i];
	}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			f[i][j]=min(f[i][j],f[i-1][j]+abs(s[i]-j*(sum/n)-(i-1-j)*(sum/n+1)-sum/n-1));
			if(j) f[i][j]=min(f[i][j],f[i-1][j-1]+abs(s[i]-(j-1)*(sum/n)-(i-1-j+1)*(sum/n+1)-sum/n)); 
		}
		
	}
	cout<<f[n][n-sum%n];
	return 0;
}

```

---

## 作者：JackMerryYoung (赞：0)

# 前言

G 题，观察的结论有一丁点意思。

这是来自 [Purslane](https://atcoder.jp/users/purslane) 的解法。

# 正文

首先我们知道无论我们怎么操作都不会改变整个数组的值。

然后有个条件 $\forall i, j \in [1, N], \ \text{s.t.} |A_i - A_j| \le 1$。

这个条件给出来后就可以猜到了，最终答案只能是 $\lfloor\dfrac{sum}{N}\rfloor$ 或者 $\lfloor\dfrac{sum}{N}\rfloor + 1$。且第二种情况的数目为 $sum - N \times \lfloor \dfrac{sum}{N}\rfloor$。

这样子就直接砸个 DP 上去，设 $f_{i, j}$ 为前 $i$ 个中有 $j$ 个情况 2 的最小操作数目。显然可得转移方程：

$$
\begin{cases}
f_{i + 1, j} = \min\left\{f_{i + 1, j}, f_{i, j} + \text{情况 1 的转移花费}\right\} \\
f_{i + 1, j + 1} = \min\left\{f_{i + 1, j + 1}, f_{i, j} + \text{情况 2 的转移花费}\right\}
\end{cases}
$$

其中这个转移花费可以前缀和得到。

# 代码

使用了往后刷表的方法。

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 5005;
int N, V, arr[MAXN], pre[MAXN], sum, f[MAXN][MAXN];

signed main() 
{
	ios::sync_with_stdio(false);
	cin >> N;
    for(int i = 1; i <= N; ++ i) 
    {
        cin >> arr[i];
        sum += arr[i];
        pre[i] = pre[i - 1] + arr[i];
    }

	int V = sum / N; 
    if(V * N > sum) 
        -- V;

	int x = N - sum + V * N;
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for(int i = 0; i < N; ++ i) 
    {
        for(int j = 0; j <= i; ++ j) 
        {
            int val = j * (V + 1) + (i - j) * V;
            int A = arr[i + 1] - val + pre[i];
            f[i + 1][j] = min(f[i + 1][j], f[i][j] + abs(A - V)), f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j] + abs(A - V - 1));
        }
    }

    cout << f[N][N - x];
	return 0;
}
```

# 后言

~~感觉 xht 写的题解好抽象（），所以又自己写了一篇~~

---

## 作者：EuphoricStar (赞：0)

考虑我们如果确定了最终态 $B = (B_1, B_2, ..., B_n)$，如何计算最少操作次数。

显然从左往右依次使 $A_i = B_i$。当操作到第 $i$ 个位置时，此时 $A'_i = A_i + \sum\limits_{j = 1}^{i - 1} A_j - B_j$，所需操作次数为 $|A'_i - B_i|$。令 $C_i = \sum\limits_{j = 1}^i A_j - B_j$，最少操作次数为 $\sum\limits_{i = 1}^n |C_i|$。

设 $s = \sum\limits_{i = 1}^n A_i, r = s \bmod n$，那么最终态一定有 $r$ 个 $\left\lfloor\frac{s}{n}\right\rfloor + 1$，$n - r$ 个 $\left\lfloor\frac{s}{n}\right\rfloor$。考虑 dp，设 $f_{i, j}$ 为考虑到第 $i$ 个位置，当前有 $j$ 个 $\left\lfloor\frac{s}{n}\right\rfloor + 1$。转移讨论第 $i$ 个位置取 $\left\lfloor\frac{s}{n}\right\rfloor$ 还是 $\left\lfloor\frac{s}{n}\right\rfloor + 1$ 即可。因为知道 $j$，所以 $C_i$ 能算出来，操作次数也能知道。

时间复杂度 $O(n^2)$。

[code](https://atcoder.jp/contests/abc307/submissions/42976050)

---

## 作者：CarroT5656 (赞：0)

**题目大意**

给定一个长度为 $n$ 的序列 $A$。每次可以执行下列操作之一：

* 选取一个 $i<n$，将 $A_i$ 变为 $A_i+1$，$A_{i+1}$ 变为 $A_{i+1}-1$。

* 选取一个 $i<n$，将 $A_i$ 变为 $A_i-1$，$A_{i+1}$ 变为 $A_{i+1}+1$。

问你最少需要多少次操作，使得对于任意一个二元组 $(i,j)$，满足 $|A_i-A_j|\le1$。

**解题思路**

肯定只与 $A_i$ 的相对大小有关，可以先将 $A_i$ 变为正整数。

操作是一个加一，一个减一，显然序列总和不变。

令 $m=\lfloor \dfrac{\sum a_i}{n} \rfloor$，可以知道最终序列只会包含 $m$ 和 $m+1$。

令 $S$ 为 $A$ 的前缀和数组。

考虑 dp，设置转移方程：

* $dp_{i,j}$ 表示取到第 $i$ 位，有 $j$ 个 $m+1$。

* $l=S_i-(m\times (i-1)+j)$，表示经过前 $i-1$ 个位置的操作后 $a_i$ 的值。

* $dp_{i,j}=dp_{i-1,j}+|m-l|$

* $dp_{i,j+1}=dp_{i-1,j}+|m+1-l|$

最终会有 $m \bmod n$ 个 $m+1$，剩余的都是 $m$。

则答案为 $dp_{n,m\bmod n}$。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 5005
ll n,a[N],cnt,dp[N][N];
int main(){
	scanf("%lld",&n);
	memset(dp,0x7f,sizeof dp);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]+=a[i-1]+1e9;
	cnt=a[n]/n;
	dp[0][0]=0;
	for(ll i=1;i<=n;i++) for(ll j=0;j<=n;j++){
		ll l=a[i]-((i-1)*cnt+j);
		dp[i][j]=min(dp[i][j],dp[i-1][j]+abs(cnt-l));
		dp[i][j+1]=min(dp[i][j+1],dp[i-1][j]+abs(cnt+1-l));
	}
	printf("%lld\n",dp[n][a[n]%n]);
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：0)

## AT_abc307_g

### 大意

给定一个长度为 $n$ 的序列 $a$，你可以：

+ 选择 $1\leq i<n$，令 $a_i$ 减去 $1$、$a_{i+1}$ 加上 $1$。
+ 选择 $1\leq i<n$，令 $a_i$ 加上 $1$、$a_{i+1}$ 减去 $1$。

你要让 $a$ 中任意两个数相差不超过 $1$，输出最少步数。

### 思路

让序列里每个数加上 $1$ 答案不会改变，所以假设 $a$ 里都是正整数。

无论如何操作，整个序列的和是不会改变的，并且操作顺序无关紧要。

令 $m=\lfloor\dfrac{\sum a}n\rfloor$，最后的序列一定由 $m$ 和 $m+1$ 组成。

设 $dp_{i,j}$ 表示前 $i$ 个数里最终有 $j$ 个 $m+1$，算出现在 $a_{i+1}$ 是多少，枚举变成 $m$ 还是 $m+1$ 转移。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
const int inf=1e17+289,e=1e9+7;
int a[5050],dp[5050][5050];
inline void Min(int&x,int y){if(x>y)x=y;}
signed main(){
	cin>>n;
	f(i,1,n)scanf("%lld",&a[i]),a[i]+=a[i-1]+e;
	m=a[n]/n;
	f(i,0,n)f(j,0,n)dp[i][j]=inf;
	dp[0][0]=0;
	f(i,1,n)f(j,0,n){
		l=a[i]-((i-1)*m+j);
		Min(dp[i][j],dp[i-1][j]+abs(m-l));
		Min(dp[i][j+1],dp[i-1][j]+abs(m+1-l));
	}
	printf("%lld\n",dp[n][a[n]%n]);
    return 0;
}
```

---

