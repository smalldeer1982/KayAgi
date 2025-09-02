# Sushi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_j

$ N $ 枚の皿があります。 皿には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。 最初、各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について、皿 $ i $ には $ a_i $ ($ 1\ \leq\ a_i\ \leq\ 3) $ 個の寿司が置かれています。

すべての寿司が無くなるまで、太郎君は次の操作を繰り返し行います。

- $ 1,\ 2,\ \ldots,\ N $ の目が等確率で出るサイコロを振り、出目を $ i $ とする。 皿 $ i $ に寿司がある場合、皿 $ i $ の寿司を $ 1 $ 個食べる。 皿 $ i $ に寿司が無い場合、何も行わない。

すべての寿司が無くなるまでの操作回数の期待値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 300 $
- $ 1\ \leq\ a_i\ \leq\ 3 $

### Sample Explanation 1

$ 1 $ 個目の寿司を食べるまでの操作回数の期待値は $ 1 $ です。 その後、$ 2 $ 個目の寿司を食べるまでの操作回数の期待値は $ 1.5 $ です。 その後、$ 3 $ 個目の寿司を食べるまでの操作回数の期待値は $ 3 $ です。 よって、全体の操作回数の期待値は $ 1\ +\ 1.5\ +\ 3\ =\ 5.5 $ です。

### Sample Explanation 2

例えば、`3.00`, `3.000000003`, `2.999999997` などを出力しても正解となります。

## 样例 #1

### 输入

```
3
1 1 1```

### 输出

```
5.5```

## 样例 #2

### 输入

```
1
3```

### 输出

```
3```

## 样例 #3

### 输入

```
2
1 2```

### 输出

```
4.5```

## 样例 #4

### 输入

```
10
1 3 2 3 3 2 3 2 1 3```

### 输出

```
54.48064457488221```

# 题解

## 作者：Haphyxlos (赞：63)

# AT4531 Sushi
[题目传送门](https://www.luogu.com.cn/problem/AT4531)

[更好的阅读体验](https://www.luogu.com.cn/blog/haphyxlos/solution-at4531)

## 暴力dp

首先我们考虑最暴力的做法，用$dp[a_1][a_2]···[a_n]$表示第$i$盘还剩$a_i$个寿司的期望次数。那么枚举随机到的数$i$就可以得到方程：

$dp[a_1][a_2]···[a_n]=1+\sum_{i=1}^{n} \frac{1}{n}dp[a_1][a_2]···[\max(a_i-1,0)]···[a_n] $


## 合并状态

（注意该方程并不能构成转移方程，因为当第$i$盘已经为空的时候，状态不变）我们现在考虑**合并等价状态**（题外话：动态规划优化的初等方法无非就那么几种，合并状态就是最重要的思想之一）。

注意到由于随机数是均匀选取的，那么盘子的位置是无关紧要的，而只有剩 余数量有影响。于是相同数值的不同排列的期望次数必然是相同的。例如$dp[1][2][3]=dp[3][2][1]$。 

所以只需要考虑每种数值出现的次数。因为$a_i \le 3$，所以至多有四种不同数值：${0,1,2,3}$。我们重新定义状态$dp[a][b][c][d]$表示当前还剩下 $a/b/c/d$盘有$0/1/2/3$个寿司。

有了状态，我们通过枚举当前随机到的盘子里还剩几只寿司得到如下方程： 

$$ dp[a][b][c][d]=1+\frac{a}{n}dp[a][b][c][d]+\frac{b}{n}dp[a+1][b-1][c][d]+\frac{c}{n}dp[a][b+1][c-1][d]+\frac{d}{n}dp[a][b][c+1][d-1]$$

移项整理得到转移方程： 

$$ dp[a][b][c][d]=\frac{n}{b+c+d}+\frac{b}{b+c+d}dp[a+1][b-1][c][d]+\frac{c}{b+c+d}dp[a][b+1][c-1][d]+\frac{d}{b+c+d}dp[a][b][c+1][d-1] $$

## 消除无用状态

但由于$n \le 300$，总状态数高达$300^{4} \approx 8×10^{9}$无法通过。我们需要进一步优化。 

注意到任意时刻下，$a + b + c + d$的值都应该等于$n$：因为不管进行多少次操作，盘子总数总是$n$。所以其实只需要知道$b,c,d$就可以反推出$a$的值：$a = n−(b + c + d)$。那么现在只保留后面三维，得到转移方程： 

$$ dp[b][c][d]=\frac{n}{b+c+d}+\frac{b}{b+c+d}dp[b-1][c][d]+\frac{c}{b+c+d}dp[b+1][c-1][d]+\frac{d}{b+c+d}dp[b][c+1][d-1] $$

本题参考程序如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
double f[305][305][305];
int a[5],n; 
int main(int argc,char const *argv[]){
	scanf("%d",&n);
	for(int i=1,x;i<=n;++i){
		scanf("%d",&x);
		a[x]++;
	}	
	for(int k=0;k<=n;++k){
		for(int j=0;j<=n;++j){
			for(int i=0;i<=n;++i){
				if(i||j||k){
					if(i)f[i][j][k]+=f[i-1][j][k]*i/(i+j+k);
        			if(j)f[i][j][k]+=f[i+1][j-1][k]*j/(i+j+k);
    	    		if(k)f[i][j][k]+=f[i][j+1][k-1]*k/(i+j+k);
	        		f[i][j][k]+=(double)n/(i+j+k);
         		}
			}
		}
	}
	printf("%.15lf\n",f[a[1]][a[2]][a[3]]);
	return 0;
}
```

本篇题解就到此结束了，如果喜欢，还请点个赞吧。



---

## 作者：FelFa_1414666 (赞：19)

这是一道很好的期望 dp 题。[atcoder 题目传送门](https://atcoder.jp/contests/dp/tasks/dp_j)

[更好的阅读体验](https://www.luogu.com.cn/blog/xesssb10108899/solution-at4531)。

------------

### 题意

有 $n$ 个盘子，每个盘子有 $a_i$ 个寿司，每次等概率选择一个盘子吃掉其中一个寿司，选到空盘子不变化，求吃完所有寿司的期望步数。

- $1\le n\le 300$

- $1\le a_i\le 3$

------------

### 分析

有同学可能没有做过**期望 dp** ，这道题能很好地诠释所谓 **"期望步数"** 的意义，加深你的理解。**所谓期望值是概率与其对应答案值的积的总和**。
有了这个公式我们可以开始考虑 dp 状态了。我们发现数据弱点在于每个盘子寿司个数只有可能为 0、1、2 或 3，且 $n$ 只有 300 。完全可以用一个 3 维的数组。

我们关心的是什么？如果有两个盘子都是 2 个寿司，那么他们在策略上就没有区别，以此类推，我们只需要关心**不同寿司个数的盘子的数量**。

- 状态：$dp(i,j,k)$ 表示当前寿司数为 1 的盘子有 $i$ 个，寿司数为 2 的盘子有 $j$ 个，寿司数为 3 的步数为 $k$ 个，吃完全部所需的期望步数。

- 根据公式推出转移方程：
$$dp(i,j,k)=\frac{n}{i+j+k}+dp(i-1,j,k)\times \frac{i}{i+j+k}+dp(i+1,j-1,k)\times \frac{j}{i+j+k}+dp(i,j+1,k-1)\times\frac{k}{i+j+k}$$

其中，$\frac{n}{i+j+k}$ 是等概率选择下排除的选了空盘子的步数（即我们平均做出一次选择需要花费 $\frac{n}{i+j+k}$ 个步数，可以自己理解一下选取空盘子消耗的步数），后面三个乘积式分别讨论了当前这一步吃掉的寿司是在 1 个寿司的盘子、2 个寿司的盘子还是 3 个寿司的盘子的情况。转移过程可以按 $k$、$j$、$i$ 三重循环，也可以记忆化搜索。最后答案为 $dp(cnt_1,cnt_2,cnt_3)$。

时间复杂度： $O(n^3)$

空间复杂度： $O(n^3)$

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
int n,cnt[5];//计数
double mem[305][305][305];//dp 数组
double dfs(int i,int j,int k)//记忆化搜索
{//dfs(i,j,k）表示当前情况需要的期望步数
	if (i==0&&j==0&&k==0)
		return 0.0;
	if (mem[i][j][k]!=0.0)
		return mem[i][j][k];
	double res=(n*1.0)/((i+j+k)*1.0);//下面是转移
	if (i>0)res+=(dfs(i-1,j,k))*(i*1.0/((i+j+k)*1.0));//吃1个寿司的盘
	if (j>0)res+=(dfs(i+1,j-1,k))*(j*1.0/((i+j+k)*1.0));//吃2个寿司的盘
	if (k>0)res+=(dfs(i,j+1,k-1))*(k*1.0/((i+j+k)*1.0));////吃3个寿司的盘
	return mem[i][j][k]=res;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		int a;
		cin>>a;
		cnt[a]++;
	}
	double ans=dfs(cnt[1],cnt[2],cnt[3]);
	printf("%.10f\n",ans);
	return 0;
}
```
希望题解对你有帮助。

---

## 作者：cmk666 (赞：17)

[题目链接](/problem/AT4531)

题目大意：给 $n$ 个 $[1,3]$ 内的整数，每次随机选一个减 $1$，减到 $0$ 则不减，求所有数变成 $0$ 的期望次数。

发现值域 $[1,3]$，考虑以值作为状态 dp。

设 $f_{i,j,k}$ 表示 $1$ 有 $i$ 个，$2$ 有 $j$ 个，$3$ 有 $k$ 个，显然 $0$ 有 $(n-i-j-k)$ 个。

转移的话枚举随机到哪个数。那么 $f_{i,j,k}$ 为下面四项之和：

随机到 $0$：$\dfrac{n-i-j-k}n(f_{i,j,k}+1)$；

随机到 $1$：$\dfrac in(f_{i-1,j,k}+1)$；

随机到 $2$：$\dfrac jn(f_{i+1,j-1,k}+1)$；

随机到 $3$：$\dfrac kn(f_{i,j+1,k-1}+1)$。

合并一下，$f_{i,j,k}=\dfrac{(n-i-j-k)f_{i,j,k}+if_{i-1,j,k}+jf_{i+1,j-1,k}+kf_{i,j+1,k-1}+n}n$。

移项并再次化简，那么 $f_{i,j,k}=\dfrac{if_{i-1,j,k}+jf_{i+1,j-1,k}+kf_{i,j+1,k-1}+n}{i+j+k}$。

为满足无后效性，注意枚举的顺序是 $k,j,i$。

时间复杂度 $O(n^3)$。核心代码如下：
```cpp
int n, x, cnt[4] = { 0 }; double f[309][309][309] = { { { 0 } } };
int main()
{
	read(n); For(i, 1, n) read(x), cnt[x]++;
	For(k, 0, n) For(j, 0, n) For(i, 0, n)
	{
		if ( !i && !j && !k ) continue;
		f[i][j][k] = n;
		if ( i ) f[i][j][k] += i * f[i - 1][j][k];
		if ( j ) f[i][j][k] += j * f[i + 1][j - 1][k];
		if ( k ) f[i][j][k] += k * f[i][j + 1][k - 1];
		f[i][j][k] /= i + j + k;
	}
	return printf("%.9lf\n", f[cnt[1]][cnt[2]][cnt[3]]), 0;
}
```

---

## 作者：kimidonatsu (赞：7)

# AT_dp_j Sushi 题解

这篇题解希望能对那些对于数论完全 0 基础的同学有所启发。希望了解有关数学期望的同学可以看一看 [OI Wiki](https://oi-wiki.org/math/probability/exp-var/) 上的权威解答或者我个人 [粗浅的学习笔记](https://www.luogu.com.cn/paste/1mnc8wd7)。

这里我们引入（期望 $E$、 $X$ 是随机变量、 $x$ 为 $X$ 的多个随机变量、 $p$ 为对应的出现概率）：

$$
E(X) = \sum_{k = 1}^{\infty} x_k p_k
$$

## 思路分析

看到此题的突破点：

* $1 \leq N \leq 300$
* $1 \leq a_i \leq 3$

数据范围都很小，考虑建立三维数组 $f_{i, j, k}$ 来表示将 $i$ 个有一个寿司的盘子、 $j$ 个有两个寿司的盘子、 $k$ 个有三个寿司的盘子（易得有 $n - i - j - k$ 个没有寿司的盘子）的情况下吃完所有寿司所需的数学期望值。

由于题目中要求，我们每次只能吃 $1$ 个寿司，所以我们可以得出 $f_{i,j,k}$ 为以下四种情况之和：

1. 选择吃 $0$ 个寿司，此时期望值为 $\dfrac{n - i - j - k}{n} \times f_{i, j, k}$ （没有动过寿司，不用改变盘子的数量）
2. 选择吃 $1$ 个寿司，此时期望值为 $\dfrac{i}{n} \times f_{i - 1, j, k}$ （吃一个寿司，将有一个寿司的盘子数量 - 1）
3. 选择吃 $2$ 个寿司，此时期望值为 $\dfrac{j}{n} \times f_{i + 1, j - 1, k}$ （吃一个寿司，多了一个有一个寿司的盘子，少了一个有两个寿司的盘子）
4. 选择吃 $3$ 个寿司，此时期望值为 $\dfrac{k}{n} \times f_{i, j + 1, k - 1}$ （吃一个寿司，多了一个有两个寿司的盘子，少了一个有三个寿司的盘子）

综上所述，可得：

$$
f_{i, j, k} = \dfrac{n - i - j - k}{n} \times f_{i, j, k} + \dfrac{i}{n} \times f_{i - 1, j, k} + \dfrac{j}{n} \times f_{i + 1, j - 1, k} + \dfrac{k}{n} \times f_{i, j + 1, k - 1}
$$

所以我们只需要统计分别有几个有 1、2、3 个寿司的盘子，记录为 $\text{sushi}_1$、$\text{sushi}_2$ 和 $\text{sushi}_3$，答案就是 $f_{\text{sushi}_1, \text{sushi}_2, \text{sushi}_3}$。

使用记忆化搜索，足以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 350;

int n;
int sushi[5];

double f[N][N][N];

double sol(int i, int j, int k) {
	if (i == 0 && j == 0 && k == 0) return 0.0;		// 处理边界
	if (f[i][j][k]) return f[i][j][k];		// 返回记录的值
	
	// 状态转移
	double p = n * 1.0 / (i + j + k) * 1.0;
	
	if (i) p += sol(i - 1, j, k) * 1.0 * (i * 1.0 / (i + j + k) * 1.0);
	if (j) p += sol(i + 1, j - 1, k) * 1.0 * (j * 1.0 / (i + j + k) * 1.0);
	if (k) p += sol(i, j + 1, k - 1) * 1.0 * (k * 1.0 / (i + j + k) * 1.0);
	
	return f[i][j][k] = p;	// 返回答案
}

int main() {
	scanf("%d", &n);
	for (int i = 1, in; i <= n; i++) {
		scanf("%d", &in);
		sushi[in]++;	// 统计寿司个数
	}
	
	printf("%.15lf\n", sol(sushi[1], sushi[2], sushi[3]));
	return 0;
}

```


---

## 作者：H2ptimize (赞：5)

### 前置知识

**什么是数学期望？**

类似于加权平均，离散型随机变量的一切可能的取值 $x_i$ 与对应的概率 $p(x_i)$ 乘积之和称为该离散型随机变量的数学期望 $E(x)$。

因此，$E(x)$ 可表示为：
$$E(x)=\sum^n_{i=1}x_ip(x_i)$$

### 分析

本题最大的特点是**每个盘子中至多有 $3$ 个寿司**。

如果有两个盘子都有 $x$ 个寿司，那么它们就没有区别。

也就是说，无论这两个盘子排在哪里，最终输出的答案是一致的。~~无端联想排列组合。~~

因此，我们只需要关心不同寿司个数的盘子的数量，**这些盘子的顺序对最终答案没有任何影响**。

### 实现

$dp_{i,j,k}$ 表示当**当前寿司数为 $1$ 的盘子有 $i$ 个，寿司数为 $2$ 的盘子有 $j$ 个，寿司数为 $3$ 的步数为 $k$ 个**时，吃完全部所需的期望。

dp 方程如下：
$$dp_{i,j,k}=\frac{n}{i+j+k}+dp_{i-1,j,k}\times\frac{i}{i+j+k}+dp_{i+1,j-1,k}\times\frac{j}{i+j+k}+dp_{i,j+1,k-1}\times\frac{k}{i+j+k}$$

显然，维度 $k$ 具有单调性，因此 $k$ 需要放在循环外层。

### Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=310;

int n,a[5];
double dp[MAXN][MAXN][MAXN];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int tmp;
		cin>>tmp;
		a[tmp]++;
	}
	for(int k=0;k<=n;k++)
	{
		for(int j=0;j<=n;j++)
		{
			for(int i=0;i<=n;i++)
			{
            	double s=i+j+k;
				if(s!=0)//防止 i,j,k 同时为零
				{
					if(i)dp[i][j][k]+=dp[i-1][j][k]*i/s;
        			if(j)dp[i][j][k]+=dp[i+1][j-1][k]*j/s;
    	    		if(k)dp[i][j][k]+=dp[i][j+1][k-1]*k/s;
	        		dp[i][j][k]+=(double)n/s;
         		}
			}
		}
	}
	printf("%.10lf\n",dp[a[1]][a[2]][a[3]]);
	return 0;
}
```

---

## 作者：xvl_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_dp_j)

一道 dp 题。

发现以前课上讲的题能水题解。

在 `dp` 之前，我们需要明确以下几个东西：

**状态的表示**，**状态转移方程**，**边界条件**跟**答案的表示**。

### 状态的表示

$dp_{i,j,k}$ 表示当有 $3$ 个寿司的盘子还剩 $i$ 个，有 $2$ 个寿司的盘子还剩 $j$ 个，有 $1$ 个寿司的盘子还剩 $k$ 个时，吃完所有寿司操作次数的期望。

### 状态转移方程

当 $i>0$ 时：
$$dp_{i,j,k}=dp_{i,j,k}+dp_{i-1,j+1,k}\times i\div (i+j+k)$$
当 $j>0$ 时：
$$dp_{i,j,k}=dp_{i,j,k}+dp_{i,j-1,k+1}\times j\div (i+j+k)$$
当 $k>0$ 时：
$$dp_{i,j,k}=dp_{i,j,k}+dp_{i,j,k-1}\times k\div (i+j+k)$$
当 $(i+j+k)>0$  时：
$$dp_{i,j,k}=dp_{i,j,k}+n\div (i+j+k)$$

### 边界条件

$$dp_{0,0,0}=0$$
### 答案的表示
$$dp_{cnt_3,cnt_2,cnt_1}$$
其中，$cnt_i$ 表示有 $i$ 个寿司的盘子数量。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n;
int cnt[4];
double dp[305][305][305];
int main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    for (int i = 0; i <= cnt[3]; i++) {
        for (int j = 0; j <= cnt[2] + cnt[3]; j++) {
            for (int k = 0; k <= cnt[1] + cnt[2] + cnt[3]; k++) {
                if (i == 0 and j == 0 and k == 0) continue;
                if (i > 0) dp[i][j][k] += dp[i - 1][j + 1][k] * i / (i + j + k);
                if (j > 0) dp[i][j][k] += dp[i][j - 1][k + 1] * j / (i + j + k);
                if (k > 0) dp[i][j][k] += dp[i][j][k - 1] * k / (i + j + k);
                dp[i][j][k] += 1.0 * n / (i + j + k);
            }
        }
    }
    printf("%.10lf", dp[cnt[3]][cnt[2]][cnt[1]]);
    return 0;
}
```


---

## 作者：gdf_yhm (赞：3)

[AT_dp_j](https://www.luogu.com.cn/problem/AT_dp_j)

[Sushi](https://atcoder.jp/contests/dp/tasks/dp_j)

### 思路

期望 dp。

设 $dp_{i,j,k,l}$ 表示当前有 $0,1,2,3$ 个寿司的盘子数有 $i,j,k,l$ 个时的期望次数。

显然 MLE。但可以发现 $i+j+k+l=n$，所以可以去掉一维。

设 $dp_{i,j,k}$ 表示当前有 $1,2,3$ 个寿司的盘子数有 $i,j,k$ 个时的期望次数。

首先有 $dp_{0,0,0}=0$。

对于一个状态 $dp_{i,j,k}$ 可以有四个状态得到。可以选装了 $1,2,3$ 个寿司的盘子，或者选空盘子，即浪费一步。

所以有：

$dp_{i,j,k}=\frac {i}{n}\times dp_{i-1,j,k}+\frac {j}{n}\times dp_{i+1,j-1,k}+\frac {k}{n}\times dp_{i,j+1,k-1}+\frac {n-i-j-k}{n}\times (dp_{i,j,k}+1)$

左右两边都有 $dp_{i,j,k}$，进行移项。得到：

$\frac {i+j+k}{n}\times dp_{i,j,k}=\frac {i}{n}\times dp_{i-1,j,k}+\frac {j}{n}\times dp_{i+1,j-1,k}+\frac {k}{n}\times dp_{i,j+1,k-1}+\frac {n-i-j-k}{n}$

$dp_{i,j,k}=(\frac {i}{n}\times dp_{i-1,j,k}+\frac {j}{n}\times dp_{i+1,j-1,k}+\frac {k}{n}\times dp_{i,j+1,k-1}+\frac {n-i-j-k}{n}) \times \frac {n}{i+j+k}$

$dp_{i,j,k}=\frac {i}{i+j+k}\times dp_{i-1,j,k}+\frac {j}{i+j+k}\times dp_{i+1,j-1,k}+\frac {k}{i+j+k}\times dp_{i,j+1,k-1}+\frac {n-i-j-k}{i+j+k}$

但是 $dp_{i,j,k}$ 需要由 $dp_{i-1,j,k},dp_{i+1,j-1,k},dp_{i,j+1,k-1}$ 计算，不符合正常理解里的 dp。所以设 $dp_{k,j,i}$ 表示当前有 $3,2,1$ 个寿司的盘子数有 $k,j,i$ 个时的期望次数。改变枚举次序，先枚举 $k$，再枚举 $j$，最后再枚举 $i$。

代码不长。

### code

```cpp
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),cnt[a[i]]++;
	dp[0][0][0]=0;
//	cout<<cnt[1]<<" "<<cnt[2]<<" "<<cnt[3]<<"\n";
	for(int k=0;k<=n;k++){
		for(int j=0;j<=n;j++){
			for(int i=0;i<=n;i++){
				if(i||j||k){
					dp[k][j][i]=1.0*(n-i-j-k)/(i+j+k);
					if(i)dp[k][j][i]+=1.0*i/(i+j+k)*(dp[k][j][i-1]+1);
					if(j)dp[k][j][i]+=1.0*j/(i+j+k)*(dp[k][j-1][i+1]+1);
					if(k)dp[k][j][i]+=1.0*k/(i+j+k)*(dp[k-1][j+1][i]+1);
//					cout<<i<<" "<<j<<" "<<k<<" ";
//					printf("%10lf\n",dp[k][j][i]);
				}
			}
		}
	}
	printf("%.10lf",dp[cnt[3]][cnt[2]][cnt[1]]);
}
```



---

## 作者：TianTian2008 (赞：3)

需要掌握期望的基本性质。

注意到寿司数量相同的盘子之间本质没有区别且 $a_i$ 值域极小，考虑 $\operatorname{DP}$ 时暴力记录每种寿司数量的盘子个数。具体地，定义 $dp_{i,j,k}$ 表示寿司数量为 $1,2,3$ 的盘子数量分别为 $i,j,k$ 的期望操作次数（隐含的条件是寿司数量为 $0$ 的盘子数为 $n-i-j-k$）。

根据期望的线性法则，容易得出

$\begin{aligned}
dp_{i,j,k}&=\frac in(dp_{i-1,j,k}+1)+\frac jn(dp_{i+1,j-1,k}+1)+\frac kn(dp_{i,j+1,k-1}+1)+\frac{n-i-j-k}n(dp_{i,j,k}+1)\\
dp_{i,j,k}&=\frac indp_{i-1,j,k}+\frac jndp_{i+1,j-1,k}+\frac kndp_{i,j+1,k-1}+\frac{n-i-j-k}ndp_{i,j,k}+1\\
\frac{i+j+k}ndp_{i,j,k}&=\frac indp_{i-1,j,k}+\frac jndp_{i+1,j-1,k}+\frac kndp_{i,j+1,k-1}+1\\
dp_{i,j,k}&=\frac{i\cdot dp_{i-1,j,k}+j\cdot dp_{i+1,j-1,k}+k\cdot dp_{i,j+1,k-1}+n}{i+j+k}
\end{aligned}$

为了保证无后效性，应先枚举 $k$，其后 $j$，最后 $i$。

到此，得出了此题的思路。

```
#include <iostream>
#include <cstdio>
using namespace std;
typedef double db;
int n;
db f[302][302][302];
int main()
{
	scanf("%d",&n);
	int c1=0,c2=0,c3=0,a;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a);
		if(a==1) ++c1;
		if(a==2) ++c2;
		if(a==3) ++c3;
	}
	for(int k=0;k<=n;++k)
		for(int j=0;j<=n;++j)
			for(int i=0;i<=n;++i)
			{
				if(!i&&!j&&!k) continue;//dp[0][0][0]特殊处理，否则会出现除以0的错误
				if(i) f[i][j][k]+=i*f[i-1][j][k];
				if(j) f[i][j][k]+=j*f[i+1][j-1][k];
				if(k) f[i][j][k]+=k*f[i][j+1][k-1];
				f[i][j][k]=(f[i][j][k]+n)/(db)(i+j+k);
			}
	printf("%.20lf",f[c1][c2][c3]);
	return 0;
}
```

---

## 作者：__yun__ (赞：1)

此篇题解补了充[这篇](https://www.luogu.com.cn/blog/CMK/solution-at4531)题解省略的推式子部分并规范了部分语言。

设 $f_{i,j,k}$表示有 $1$ 寿司的盘子有 $i$ 个，有 $2$ 寿司的盘子有 $j$ 个，有 $3$ 寿司的盘子有 $k$ 个，那么没有寿司的盘子有 $(n-i-j-k)$ 个。

分类讨论转移：

1. 随机到没有寿司的盘子：$\frac{n-i-j-k}{n}(f_{i,j,k}+1)$；

2. 随机到有 $1$ 寿司的盘子：$\frac{i}{n}(f_{i-1,j,k}+1)$；

3. 随机到有 $2$ 寿司的盘子：$\frac{j}{n}(f_{i+1,j-1,k}+1)$；

4. 随机到有 $3$ 寿司的盘子：$\frac{k}{n}(f_{i,j+1,k-1}+1)$。

合并一下，$f_{i,j,k}=\frac{(n-i-j-k)(f_{i,j,k}+1)+i  (f_{i-1,j,k}+1)+j (f_{i+1,j-1,k}+1)+k (f_{i,j+1,k-1}+1)}{n}$。

### 开始推式子！

$$f_{i,j,k}=\frac{(n-i-j-k)(f_{i,j,k}+1)+i  (f_{i-1,j,k}+1)+j (f_{i+1,j-1,k}+1)+k (f_{i,j+1,k-1}+1)}{n}$$

$$f_{i,j,k}=\frac{(n-i-j-k)f_{i,j,k}+i  f_{i-1,j,k}+j f_{i+1,j-1,k}+k f_{i,j+1,k-1}+n}{n}$$

$$n f_{i,j,k}=(n-i-j-k)f_{i,j,k}+i f_{i-1,j,k}+j f_{i+1,j-1,k}+k f_{i,j+1,k-1}+n$$

$$n f_{i,j,k}-(n-i-j-k)f_{i,j,k}=i f_{i-1,j,k}+j f_{i+1,j-1,k}+k f_{i,j+1,k-1}+n$$

$$(i+j+k)f_{i,j,k}=i f_{i-1,j,k}+j f_{i+1,j-1,k}+k f_{i,j+1,k-1}+n$$

$$f_{i,j,k}=\frac{i f_{i-1,j,k}+j f_{i+1,j-1,k}+k f_{i,j+1,k-1}+n}{i+j+k}$$

最终结果：$f_{i,j,k}=\frac{i f_{i-1,j,k}+j f_{i+1,j-1,k}+k f_{i,j+1,k-1}+n}{i+j+k}$。

### $Code$：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=310;
int n;
int a[5];
double f[M][M][M];
int main(){
	cin>>n;
	int x;
	for(int i=1;i<=n;i++){
		cin>>x;
		a[x]++;
	}
	f[0][0][0]=0;
	for(int k=0;k<=n;k++){
		for(int j=0;j<=n;j++){
			for(int i=0;i<=n;i++){
				if(!i&&!j&&!k) continue;
				if(i) f[i][j][k]+=f[i-1][j][k]*i/(i+j+k);
        		if(j) f[i][j][k]+=f[i+1][j-1][k]*j/(i+j+k);
    	    	if(k) f[i][j][k]+=f[i][j+1][k-1]*k/(i+j+k);
	        	f[i][j][k]+=1.0*n/(i+j+k);
			}
		}
	}
	printf("%.100f",f[a[1]][a[2]][a[3]]);
	return 0;
}
```

---

## 作者：Nicrobot (赞：1)


期望 DP，好题。

我们发现有很多的盘子，但盘子里的寿司数量 $1 \le a_i \le 3$，而第几个盘子并不会影响它选到的概率！我们完全可以用多维数组，表示每种个数的寿司的盘子的数量。

但是这里有吃完的即 $0$ ，我们需要表示 $0,1,2,3$ 个寿司的盘子数量，四维是开不下的。根据套路，$4$ 种的数量和为 $n$，我们可以省去一维，省去 $0$ 这一维，就可以开得下了。

这样我们确定了状态：$f(i,j,k)$ 表示要使得有 $i,j,k$ 个 $1,2,3$ 个寿司的盘子和 $(n-i-j-k)$ 个没寿司的盘子，操作次数的期望值是多少。

接下来考虑怎么转移。我们知道根据期望的定义 $E(X)=\sum_{i \in \Omega} P(i) R(i)$，即期望值等于每种可能的结果乘以其概率之和，我们就要根据它来转移，对于 $f(i,j,k)$：

- 如果这个位置选了个 $0$，啥也不动，其概率为 $\dfrac{n-i-j-k}{n}$。
- 如果这个位置选了个 $1$，即从 $f(i-1,j,k)$ 转移，概率为 $\dfrac{i}{n}$。
- 如果这个位置选了个 $2$，即从 $f(i+1,j-1,k)$ 转移，概率为 $\dfrac{j}{n}$。
- 如果这个位置选了个 $3$，即从 $f(i,j+1,k-1)$ 转移，概率为 $\dfrac{k}{n}$。


最后，注意操作次数要 $+1$。

因此，我们得到了一个初步的式子：
$$
f(i,j,k)=\dfrac{n-i-j-k}{n} \times f(i,j,k)+\dfrac{i}{n} \times f(i-1,j,k)

$$
$$
+\ \dfrac{j}{n} \times f(i+1,j-1,k)+\dfrac{k}{n} \times f(i,j+1,k-1) \color{red}+1
$$
式子两边都有 $f(i,j,k)$ 不行，但是我们整理移项，拿草稿纸算算就能得到：
$$
f(i,j,k)=\dfrac{1}{i+j+k} \times(i \times f(i-1,j,k)+ \ j \times f(i+1,j-i,k) + k\times f(i,j+1,k-1) \color {red}{+ n} \color{black})
$$
这样就能转移了。由于顺序比较复杂，我选择了记忆化搜索，当然先后顺序弄对直接 DP 就行。

时间复杂度 $O(n^3)$，但是跑得有点慢 qwq。

[提交记录](https://www.luogu.com.cn/record/98182781)

---

## 作者：Phanstom_Peng (赞：1)

## AT4531

### 题意：

$n$ 个数，$1\leq a_i\leq3$ ，每次随机选一个减一，如果是 $0$ 就不管，问全部减成 $0$ 的期望操作次数。

### 思路：

发现 $a_i$ 的范围仅仅是 $3$ ，而每个数又是等效的，所以考虑一个三维 $\text{DP}$

**计算期望，考虑从后向前计算**，设 $dp[0][0][0]$ 表示末状态的答案，每一维表示 $1,2,3$ 的数量，转移式：

定义：
$$
t0=dp[i][j][k]
$$

$$
t1=dp[i-1][j][k]
$$

$$
t2=dp[i+1][j-1][k]
$$

$$
t3=dp[i][j+1][k-1]
$$


$$
dp[i][j][k]=(1+t0 * (n-i-j-k)+t1 * i +t2 * j +t3 * k)/n;
$$
看上去好像有环，但是移项搞定，最后的式子：
$$
dp[i][j][k]=(1+t1 * i +t2 * j +t3 * k) * n / (n-i-j-k);
$$
顺序有点不好弄，所以记忆化搜索。

其实发现 $k$ 单调，所以 $k$ 为阶段，状态上，顺序枚举 $j,i$，这样就可以用循环转移了。

~~排版好像有点丑。。。~~

### 参考代码：

```cpp
#include<bits/stdc++.h>
#define y1 y3647
#define earse erase
#define INF 1000000000
#define LL long long
#define pii pair<int,int>
using namespace std;
inline void read(int &x)
{
	x=0;int f=1;
	char ch=getchar();
	while(ch!=45&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
const int N=305;
int i,j,k,n,s,t,m,s1,s2,s3;
double dp[N][N][N];
double solve(int x1,int x2,int x3)
{
	if(x1==0&&x2==0&&x3==0)return 0;
	if(dp[x1][x2][x3]>0) return dp[x1][x2][x3];
	if(x1)dp[x1][x2][x3]+=1.0*x1/n*solve(x1-1,x2,x3);
	if(x2)dp[x1][x2][x3]+=1.0*x2/n*solve(x1+1,x2-1,x3);
	if(x3)dp[x1][x2][x3]+=1.0*x3/n*solve(x1,x2+1,x3-1);
	dp[x1][x2][x3]+=1;
	dp[x1][x2][x3]*=1.0*n/(x1+x2+x3);
	return dp[x1][x2][x3];
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",sdtout);
	read(n);
	dp[0][0][0]=0;
	for(i=1;i<=n;i++)
	{
		int x;
		read(x);
		if(x==1)s1++;
		if(x==2)s2++;
		if(x==3)s3++;
	}
	printf("%0.9lf",solve(s1,s2,s3));
	return 0;
}


```



---

## 作者：紊莫 (赞：0)

本文主要讲解题解区没有详细解释的方程部分（~~其实是一开始自己没理解的~~）。  
## Part 1 题意分析

有 $n$ 个盘子，每次**随机**选择一个盘子，吃掉其中的一个寿司。若没有寿司则不吃。  

求最后吃掉所有寿司的期望步数。  

题意告诉我们非常重要的一点，可以选择空盘子，也就是说这些浪费的步数也会算入期望里。  

## Part 2 状态转移方程

定义：$f_{i,j,k}$ 表示有 $i$ 个盘子里有一个寿司，$j$ 个盘子里有两个寿司，$k$ 个盘子里有三个寿司时吃完所有寿司的期望。  

初始化：$f_{0,0,0}=0$。  

接下来，列出最初的方程：  

$$f_{i,j,k}=\dfrac{n-i-j-k}{n}\times f_{i,j,k}+\dfrac{i}{n}\times f_{i-1,j,k}+\dfrac{j}{n}\times f_{i+1,j-1,k}+\dfrac{k}{n}\times f_{i,j+1,k-1}+1$$  

首先看第一项，$\dfrac{n-i-j-k}{n}\times f_{i,j,k}$ 表示有 $\dfrac{n-i-j-k}{n}$ 的概率选到空盘子，**吃完**空盘子之后，会发现局面没有任何变化，现在想吃完所有寿司仍然需要 $f_{i,j,k}$ 的期望步数。  

第二项，这次选择吃有一个寿司的盘子，**吃完**后下一步里有一个寿司的盘子就少了一个，到达了 $f_{i-1,j,k}$ 的局面，选中这个盘子的概率同上，不再解释。  

第三项，这次选择吃有两个寿司的盘子，**吃完**后发现，两个寿司的盘子少了一个，可是剩下的那个寿司就成为了一个寿司的盘子了，所以到达了 $f_{i+1,j-1,k}$ 的局面。  

最后解释一下最后一个加一的含义，注意到我前面特别标粗了**吃完**两个字，意思就是我们目前加的都是吃完后的期望，难道当前吃的这一步不需要步数吗？所以这个一表示的就是当前吃的这一步！  

理解了初代方程之后，我们就可以合并同类项来化简了。  

$$\dfrac{i+j+k}{n}\times f_{i,j,k}=\dfrac{i}{n}\times f_{i-1,j,k}+\dfrac{j}{n}\times f_{i+1,j-1,k}+\dfrac{k}{n}\times f_{i,j+1,k-1}+1$$   

$$(i+j+k)\times f_{i,j,k}=i\times f_{i-1,j,k}+j\times f_{i+1,j-1,k}+k\times f_{i,j+1,k-1}+n$$

$$f_{i,j,k}=\dfrac{i}{i+j+k}\times f_{i-1,j,k}+\dfrac{j}{i+j+k}\times f_{i+1,j-1,k}+\dfrac{k}{i+j+k}\times f_{i,j+1,k-1}+\dfrac{n}{i+j+k}$$  

## Part 3 代码

这题如果需要循环转移的话需要按照 $k,j,i$ 的顺序，相较之下记忆化搜索不用多想。  

```cpp
const int N=305,M=(N<<1),inf=0x3f3f3f3f;
double f[N][N][N];
double dp(int i,int j,int k){
	if(i==0&&j==0&&k==0) return 0;
	if(f[i][j][k]) return f[i][j][k];
	double p=n*1.0/(i+j+k);
	if(i) p+=i*1.0/(i+j+k)*dp(i-1,j,k);
	if(j) p+=j*1.0/(i+j+k)*dp(i+1,j-1,k);
	if(k) p+=k*1.0/(i+j+k)*dp(i,j+1,k-1);
	return f[i][j][k]=p;
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,x,c[4]={0};cin>>n;
	F(i,1,n){
		cin>>x;
		c[x]++;
	}
	cout<<fixed<<setprecision(10)<<dp(c[1],c[2],c[3]);
    return 0;
}
```


---

## 作者：novax (赞：0)

[题面](https://www.luogu.com.cn/problem/AT4531)

### 题意

有 $N$ 盘寿司，每盘有 $1 \sim 3$ 个。每次随机选择一个盘子并从中拿走一个寿司吃掉，若没有则不拿。求吃完所有寿司的期望次数。

### 思路

**期望dp**。设 $F_{i,j,k}$ 表示吃到当前有 $i$ 盘剩一个，$j$ 盘剩两个，$k$ 盘剩三个的期望次数。则有转移：

$F_{i,j,k}= (1-\frac{i+j+k}{N}) \times F_{i,j,k} + \frac{i}{N} \times F_{i-1,j,k} + \frac{j}{N}F_{i+1,j-1,k} + \frac{k}{N} \times F_{i,j+1,k-1}$.

方程的四项分别对应从空盘子、有一个寿司、有两个寿司、有三个寿司的盘子中取走寿司到当前状态。

发现等式两端都有 $F_{i,j,k}$，于是考虑化简：

$\frac{i+j+k}{N}F_{i,j,k}=\frac{1}{N}(i \times F_{i-1,j,k} + j \times F_{i+1,j-1,k} + k \times F_{i,j+1,k-1})$.

$F_{i,j,k}=\frac{1}{i+j+k}(i \times F_{i-1,j,k} + j \times F_{i+1,j-1,k} + k \times F_{i,j+1,k-1})$.

由此本题做到了 $O(n^3)$ 的转移复杂度。

因为状态中 $k$ 不会用到当前行的状态，所以可用循环先枚举 $k$ 转移。或使用记忆化搜索亦可。

### 代码

```cpp
#include <cstdio>
int N,n1,n2,n3;
double F[303][303][303],ans;
double solve(int i,int j,int k)
{
	if(i==0&&j==0&&k==0)
		return 0;
	if(F[i][j][k]>0)
		return F[i][j][k];
	F[i][j][k]=N;
	if(i>0)
		F[i][j][k]+=(1.0*i)*solve(i-1,j,k);
	if(j>0)
		F[i][j][k]+=(1.0*j)*solve(i+1,j-1,k);
	if(k>0)
		F[i][j][k]+=(1.0*k)*solve(i,j+1,k-1);
	F[i][j][k]/=(1.0*(i+j+k));
	return F[i][j][k];
}
int main()
{
	scanf("%d",&N);
	int i,j,k;
	for(i=1;i<=N;i++)
	{
		scanf("%d",&k);
		if(k==1) n1++;
		else if(k==2) n2++;
		else if(k==3) n3++;
	}
	ans=solve(n1,n2,n3);
	printf("%.10f\n",ans);
}
```



---

