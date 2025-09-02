# [ABC258Ex] Odd Steps

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc258/tasks/abc258_h

以下の条件を全て満たす数列 $ X $ の総数を $ 998244353 $ で割った余りを求めてください。

- $ X $ の全ての項は正の**奇数**である。
- $ X $ の各項の総和は $ S $ に等しい。
- $ X $ の累積和には $ A_1,\ \dots,\ A_N $ のいずれも現れない。厳密には、各 $ i\ \,\ (1\ \leq\ i\ \leq\ |X|) $ に対して $ Y_i\ =\ X_1\ +\ \dots\ +\ X_i $ と定めたとき、$ 1\ \leq\ i\ \leq\ |X|,\ 1\ \leq\ j\ \leq\ N $ を満たす全ての整数 $ i,\ j $ に対して $ Y_i\ \neq\ A_j $ が成り立つ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_1\ \lt\ A_2\ \lt\ \dots\ \lt\ A_N\ \lt\ S\ \leq\ 10^{18} $
- 入力は全て整数

### Sample Explanation 1

以下の $ 3 $ 通りが条件を満たします。 - $ (1,\ 5,\ 1) $ - $ (3,\ 3,\ 1) $ - $ (7) $

## 样例 #1

### 输入

```
3 7
2 4 5```

### 输出

```
3```

## 样例 #2

### 输入

```
5 60
10 20 30 40 50```

### 输出

```
37634180```

## 样例 #3

### 输入

```
10 1000000000000000000
1 2 4 8 16 32 64 128 256 512```

### 输出

```
75326268```

# 题解

## 作者：piggy123 (赞：6)

题解的矩阵大小都是 $3$，提供一个矩阵大小为 $2$ 的做法。

考虑容斥，$dp_i$ 表示总和为 $A_i$，并且不出现除了 $A_i$ 其他前缀和的方案数，将 $A_{n+1}=S$，容易发现方程：

$$
dp_i=F_i-\sum_j dp_j\times F_{A_i-A_j}
$$

其中 $F_i$ 表示仅用奇数凑出的 $i$ 的方案数，打表发现 $F_i$ 为斐波那契数列。

然后用一个矩阵维护后面那坨求和，从 $\sum_j dp_j\times F_{A_{i-1}-A_j}$ 变为 $\sum_j dp_j\times F_{A_{i}-A_j}$ 即可。

矩阵就是斐波那契数列的矩阵，大小为 $2$。

---

## 作者：Powerless233 (赞：5)

## Description
求满足以下条件的序列数量（对 998244353 取模）：

- 只由奇数构成。

- 所有数和为 $S$。

- 所有的前缀和中不能出现 $A$ 中的任意数字。

## Analysis

先把第三个限制（即前缀和限制）和数据范围忽略，考虑一个朴素的算法。

设 $f_{i}$ 表示当前和为 $i$ 的序列数量，那么有：

$$f_{i}=f_{i-1}+f_{i-3}+f_{i-5}+\dots$$

（可以取的数只有 $1,3,5,\dots$）

边界有：

$$f_{0}=1$$

这个 dp 的复杂度是 $O(S^2)$ 的，显然我们需要做一些优化。
### Optimize  1

观察到，$f_{i-1}+f_{i-3}+f_{i-5}+\dots$ 是可以在边求 $f$ 的时候边维护的，我们设 $s_{i}$ 表示 $s_{i}=f_{i}+f_{i-2}+f_{i-4}+\dots$ ，则有：

$$f_{i} = s_{i-1}$$

$$s_{i} = s_{i-2} + f_{i}$$

这样，我们就在 $O(S)$ 的时间内求出了答案。

**但这还不够！** $S$ 的级别为 $10^{18}$ ，这个数据范围似乎在提示我们使用某种优化。
### Optimize 2
观察到 $f,s$ 的递推式都是不变的，没有额外限制，且数据范围在 $10^{18}$ ，这些信息提示我们使用一种优化：

**矩阵快速幂**。

考虑我们需要维护的量：$f_{i},s_{i-1},s_{i-2}$ ，那么可以构造出矩阵：

$$\begin{bmatrix}f_{i}\\ s_{i-1} \\ s_{i-2} \end{bmatrix}$$

根据之前的递推关系，有系数矩阵：

$$\begin{bmatrix}1 & 0 & 1 \\ 1 & 0 & 1
\\ 0 & 1 & 0\end{bmatrix} \begin{bmatrix}f_{i-1}\\ s_{i-2} \\ s_{i-3} \end{bmatrix} = \begin{bmatrix}f_{i}\\ s_{i-1} \\ s_{i-2} \end{bmatrix}$$

用快速幂优化这个过程，我们就在 $O(\log_{2}n)$ 的复杂度下求出了答案。

### Back to the Origin
接下来考虑前缀和限制。

把 “前缀和不能为 $a_{i}$” 写为形式化的语言，其实就是 $f_{a_{i}} = 0$ 。那么我们只需要在快速幂的中间，将 $f_{i} = 0$ 即可。

时间复杂度 $O(n+\log_{2}S)$。

## Code
```cpp
#include <bits/stdc++.h>
#define LL long long
#define int long long
using namespace std;
inline LL read()
{
	LL res = 0, fl = 1;
	char ch = getchar();
	while (!(ch >= '0' && ch <= '9'))
	{
		if (ch == '-')
			fl = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		res = (res << 3) + (res << 1) + ch - '0', ch = getchar();
	return res * fl;
}
inline LL max(LL a, LL b) { return a > b ? a : b; }
inline LL min(LL a, LL b) { return a < b ? a : b; }
const LL inf = 0x3f3f3f3f, mod = 998244353;
const LL N = 1e5 + 5, M = 4, si = 3;
LL n, m, a[N];
struct matrix
{
	int a[M][M];
	matrix()
	{
		memset(a, 0, sizeof a);
	}
	inline void build()
	{
		for (int i = 1; i <= si; i++)
		{
			a[i][i] = 1;
		}
	}
};
matrix operator*(const matrix &x, const matrix &y)
{
	matrix res;
	for (int i = 1; i <= si; i++)
	{
		for (int j = 1; j <= si; j++)
		{
			for (int k = 1; k <= si; k++)
			{
				res.a[i][j] += x.a[i][k] * y.a[k][j] % mod;
				res.a[i][j] %= mod;
			}
		}
	}
	return res;
}
matrix operator^(const matrix x, LL y)
{
	matrix base = x, res;
	res.build();
	while (y)
	{
		if (y & 1)
			res = base * res;
		base = base * base;
		y >>= 1;
	}
	return res;
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	matrix trans, cur, tmp;
	trans.a[1][1] = 1, trans.a[1][2] = 0, trans.a[1][3] = 1;
	trans.a[2][1] = 1, trans.a[2][2] = 0, trans.a[2][3] = 1;
	trans.a[3][1] = 0, trans.a[3][2] = 1, trans.a[3][1] = 0;
	n = read(), m = read();
	cur.a[1][1] = 1, cur.a[2][1] = 0, cur.a[3][1] = 0;
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
		tmp = trans ^ (a[i] - a[i - 1]);
		cur = tmp * cur;
		cur.a[1][1] = 0;
	}
	tmp = trans ^ (m - a[n]);
	cur = tmp * cur;
	cout << cur.a[1][1] << '\n';
	return 0;
}
```


---

## 作者：_ZML_ (赞：4)

# 思路

拿到这道题，第一时间肯定想到是 $dp$ 题目。

## 朴素 DP

用 $dp_i$ 表示序列和为 $i$ 的序列个数。因为原数组由奇数组成，所以 $dp$ 只可能由 $dp_{i-1}$，$dp_{i-3}$ 等等转移过来，若 $i\in A$，$dp_i=0$。即：
$$
dp_i=\begin{cases}
 0&i\in A\\
 dp_{i-1}+dp_{i-3}+\cdots  &otherwise
\end{cases}
$$

## 优化

设 $sum_i=f_i+f_{i-2}+f_{i-4}+\cdots$。则 $f_i=sum_{i-1} $，$s_i=s_{i-2}+f_i$。

观察式子发现可以使用矩阵优化递推，我们维护 $f_i$，$sum_{i-1}$，$sum_{i-2}$ 的值。

因为 ：
$$
\left\{\begin{matrix} 

f_{i+1}=f_i+s_{i-2}\\
s_{i}=f_{i}+s_{i-2}\\
s_{i-2}=s_{i-2}
\end{matrix}\right.
$$
所以可以构造如下矩阵：
$$
\begin{bmatrix}
 f_i & s_{i-1} &s_{i-2}
\end{bmatrix}
\begin{bmatrix}
 1 & 1 &0 \\
 0 & 0 & 1\\
 1 &  1&0
\end{bmatrix}
$$
所以之后分段快速幂即可，剩下的看我代码吧。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3, mod=998244353;
int a[100010];

struct mat {
	int a[maxn+1][maxn+1];
	mat() {
		memset(a,0,sizeof(a));
	}
	mat operator*(const mat&T) const {
		mat res;
		for(int i=1;i<=maxn;i++) {
			for(int j=1;j<=maxn;j++) {
				for(int k=1;k<=maxn;k++) {
					res.a[i][j]=(res.a[i][j]+a[i][k]*T.a[k][j])%mod;
				}
			}
		}
		return res;
	}
	mat operator^(int x) const {
        mat bas,res;
        for(int i=1;i<=maxn;i++) res.a[i][i]=1;
        for(int i=1;i<=maxn;i++) {
            for(int j=1;j<=maxn;j++) {
                bas.a[i][j]=a[i][j]%mod;
            }
        }
        while(x) {
            if(x&1) {
                res=res*bas;
            }
            bas=bas*bas;
            x>>=1;
        }
        return  res;
    }
};
mat x,y,tmp;
signed main() {
	x.a[1][1]=1, x.a[1][2]=0,x.a[1][3]=0;
	int n,s;
	cin>>n>>s;
	y.a[1][1]=y.a[1][2]=y.a[2][3]=y.a[3][2]=y.a[3][1]=1;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		tmp=y^(a[i]-a[i-1]);
		x=x*tmp;
		x.a[1][1]=0;
	} 
	mat tmp=y^(s-a[n]);
	x=x*tmp;
	cout<<x.a[1][1];
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc258_h)

## 思路

难得有这么水的 $\rm Ex$。

考虑把 $S$ 拆成 $S$ 个 $1$，现在问题就转化成了：选出若干个首尾相接的区间，使得这些区间的长度都是奇数，并且区间的右端点不能等于某个 $a_i$ 的方案数。

转移可以分类：

$$f_i=\begin{cases}0,& i=a_j \\ \sum f_j \times [j \bmod 2 \neq i \bmod 2],&  \text{otherwise.}\end{cases}$$

显然的，我们可以维护两个前缀和把计算加速到 $\mathcal O(s)$，但是这显然不够。

考虑使用矩阵快速幂优化之。

不妨设 $p_{i,0/1}$ 表示已经计算到位置 $i$，$j$ 的奇偶性与 $i$ 相同/不相同的前缀和。

考虑设出转移矩阵，得到：

$$\begin{bmatrix}1&0&1\\1&0&1\\0&1&0\\\end{bmatrix} \times \begin{bmatrix}f_i \\ p_{i,0} \\ p_{i,1}\end{bmatrix}=\begin{bmatrix}f_{i+1} \\ p_{i+1,0} \\ p_{i+1,1}\end{bmatrix}$$

然后就做完了，对于每个 $f_i=0$ 的节点，分段然后快速幂即可。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const mod=998244353;
int const N=1e6+10;int a[N];
struct matrix{
	int a[3][3];
	matrix(){memset(a,0,sizeof(a));}
};
matrix operator * (matrix a,matrix b){
	matrix res;
	for (int i=0;i<3;++i)
		for (int j=0;j<3;++j)
			for (int k=0;k<3;++k)
				res.a[i][j]+=a.a[i][k]*b.a[k][j]%mod,res.a[i][j]%=mod;
	return res;
}
inline matrix qpow(matrix a,int b){
	matrix res;res.a[0][0]=res.a[1][1]=res.a[2][2]=1;
	while (b){
		if (b&1) res=res*a;
		a=a*a,b>>=1;
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,s;cin>>n>>s;
	for (int i=1;i<=n;++i) cin>>a[i];
	matrix zhuan,ans;
	zhuan.a[0][0]=zhuan.a[0][2]=
	zhuan.a[1][0]=zhuan.a[1][2]=zhuan.a[2][1]=1;
	ans.a[0][0]=ans.a[1][0]=1,a[0]=1;
	for (int i=1;i<=n;++i) ans=qpow(zhuan,a[i]-a[i-1])*ans,ans.a[0][0]=0;
	ans=qpow(zhuan,s-a[n])*ans;cout<<ans.a[0][0]<<'\n';
	return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

不错的矩阵快速幂优化 dp 练习题。

考虑一个朴素 dp，$f_i$ 为组成和为 $i$ 且用到的数都是奇数的方案数。有转移：

$$f_i = \begin{cases} \sum\limits_{j=0}^{i-1} [i \bmod 2 \ne j \bmod 2] f_j & i \notin A \\ 0 & i \in A \end{cases}$$

考虑前缀和优化，设 $g_{i, j} = \sum\limits_{i=0}^i [i \bmod 2 = j] f_i$，那么：

$$f_i = \begin{cases} g_{i, 1 - i \bmod 2} & i \notin A \\ 0 & i \in A \end{cases}$$

$$g_{i, i \bmod 2} = g_{i - 1, i \bmod 2} + f_i = g_{i - 1, i \bmod 2} + [i \notin A] g_{i - 1, 1 - i \bmod 2}$$

$$g_{i, 1 - i \bmod 2} = g_{i - 1, 1 - i \bmod 2}$$

至此得到了一个 $O(S)$ 的做法。

发现 $[0, S]$ 被 $A_i$ 分成若干段，并且每一段的转移方程重复。为了方便把 $i \bmod 2 = 1, i \bmod 2 = 0$ 的相邻两个 $i$ 放一起考虑，那么相当于 $g'_0 = 2g_0 + g_1, g'_1 = g_0 + g_1$。容易刻画成矩阵形式，然后分段转移。注意处理一些端点奇偶性不相同的情况。

时间复杂度 $O(n \log S)$。

[code](https://atcoder.jp/contests/abc258/submissions/41857223)

---

## 作者：Paper27 (赞：2)

看到这道题后我整个人都是蒙的——什么东西？？？  
也许你也跟我一样，但别慌，且听我细细道来。  
## 思路  
- 首先观察题目给组成序列的三个条件。  
>1. 仅由**正奇数**组成。  
>2. 所有数之**和为 $S$**。  
>3. 序列的**任意前缀和**均不能为 $A_i,1 \le i \le N$。

咱们一个个看。

### 2. 所有数之和为 $S$。 

这里我们先看第二条。

所有数之和为 $S$，很容易想到这里应使用隔板法，
但很明显这样做会超时。

此时，你回眸一看发现——

### 1. 仅由正奇数组成。

然后想到这两个东西能有什么关联呢？

于是\"你\"想到了神奇的打表。  
最后你暴力计算 $S=1,2,3,...$ 时满足这两个条件的方案数后发现这不是**斐波拉契数列**吗！！！ 

接下来证明这一条件。

>- 第一种方案：  
使用**数学归纳法**。  
记当 $S=x$ 时满足条件的方案数为 $f(x)$。  
此时我们仅需考虑最后一个数为多少即可求出 $f(x)$。  
即 $x$ 为偶数时 $f(x)=f(x-1)+f(x-3)+f(x-5)+...+f(1)$。  
$x$ 为奇数时 $f(x)=f(x-1)+f(x-3)+f(x-5)+...+f(2)+1$。  
当 $S=1,2$ 时 $f(1),f(2)$ 显然为斐波拉契数列。  
此时假设 $f(1),f(2),f(3),...,f(i-1)$ 时此数列为斐波拉契数列。  
接下来分类讨论。    
当 $i$ 为偶数时 $f(i)=f(i-1)+f(i-3)+...+f(1)$。  
又因为 $f(1)=f(2)$ 所以 $f(i)=f(i-1)+f(i-3)+...+f(2)$。  
又由斐波拉契数列的性质得 $f(3)+f(2)=f(4),f(5)+f(4)=f(6),...,f(i-3)+f(i-4)=f(i-2)$。  
所以有 $f(i)=f(i-1)+f(i-2)$ 满足斐波拉契数列的性质。  
当 $i$ 为奇数时 $f(i)=f(i-1)+f(i-3)+...+f(2)+1$。  
又因为 $1=f(1)$ 所以 $f(i)=f(i-1)+f(i-3)+...+f(2)+f(1)$。  
又由斐波拉契数列的性质得 $f(2)+f(1)=f(3),f(4)+f(3)=f(5),...,f(i-3)+f(i-4)=f(i-2)$。  
所以有 $f(i)=f(i-1)+f(i-2)$ 满足斐波拉契数列的性质。  
综上所述，当 $x \in \mathbb{N}^+$ 时 $f(1),f(2),f(3),...$ 为斐波拉契数列。

>- 第二种方案：  
>我们定义以下两种操作。  
1.使序列添加一个元素 $1$。  
2.使序列最后一个数增加 $2$。  
可以发现任何一个满足条件的方案都可以通过这个方式生成。  
记当 $S=x$ 时满足条件的方案数为 $f(x)$。  
则有 $f(x)=f(x-1)+f(x-2),x>2且x \in \mathbb{N}^+$。  
所以此时 $f(1),f(2),f(3),...$ 为斐波拉契数列。

那么这里直接考虑使用斐波拉契数列求 $f(x)$。  
但直接线性求会超时，考虑**矩阵乘法**加速求斐波拉契第 $x$ 项，没学过的戳 <https://www.luogu.com.cn/problem/B2105>
代码如下。  
```
void c(ll a[2][2],ll b[2][2])
{
	ll x[2][2]={0,0,0,0};
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				x[i][j]=(x[i][j]+a[i][k]*b[k][j]%mod)%mod;
	memcpy(a,x,sizeof(x));
}
ll fab(ll x)
{
	if(x<=0)return 0;
	ll fa[2][2]={1,0,0,0};
	ll ans[2][2]={1,1,1,0};
	x--;
	while(x)
	{
		if(x&1)c(fa,ans);
		c(ans,ans);
		x=(x>>1);
	}
	return fa[0][0];
}
```
那么前两条也是完美解决了(不会写就怨我吧~ 抽泣 ing...)。

我们继续。
### 3. 序列的任意前缀和均不能为 $A_i,1 \le i \le N$。

思绪回到刚开始时，发现了自己想用隔板法时真觉得自己愚蠢。  
但仔细一想，发现如果用隔板法解决这道题，那么第三点就转换成了**不能在 $A_i,1 \le i \le N$ 后面插隔板**。  
那么 $A_1,A_2,A_3,...,A_N$ 就把 $S$ 分成了 $n+1$ 个区间。  
此时设 $dp_{i,j}$ 表示前 $i$ 个区间最后一个数模以 $2$ 为 $j$ 且其它数均为奇数时的方案数；$f_i$ 为斐波拉契数列第 $i$ 位;$l_i$ 为第 $i$ 个区间的长度。  
此时\"你\"正在思考 $dp_{i,j}$ 的转移方程是什么呢？  
别急，答案其实很显然。

现在只需考虑正在求的区间如何与之前的区间合并。  
分类讨论如下。

- 当 $j=0$ 时，可以从正在求的区间末端拿出一个 $1$ 于是使区间最后一位为偶数且其它数均为奇数且其他数均为奇数就转换成了从正在求的区间末端拿出一个 $1$ 将区间分成任意个数的奇数，方案数为 $f(l_i-1)$ 此时即可将 $dp_{i,0}$ 与 $dp_{i-1,0}$ 合并。  
将 $dp_{i,0}$ 与 $dp_{i-1,1}$ 合并只需要再从正在求的区间头部拿出一个 $1$ 则可以将问题转换成从正在求的区间头部和末端分别拿出一个 $1$ 将区间分成任意个数的奇数，方案数为 $f(l_i-2)$。

$$
dp_{i,0}=dp_{i-1,0}\times f(l_i-1)+dp_{i-1,1} \times f(l_i-2)
$$

- 当 $j=1$ 时，只是不用从正在求的区间末端拿出一个 $1$ 而已。

$$
dp_{i,1}=dp_{i-1,0} \times f(l_i)+dp_{i-1,1} \times f(l_i-1)
$$

需要注意的是当 $l_i=1$ 时。

$$
dp_{i,0}=dp_{i-1,0} \times f(l_i-1)+dp_{i-1,1}
$$

综上，有

$$
dp_{i,j}=\begin{cases}
dp_{i-1,0} \times f(l_i-1-j \oplus 1)+dp_{i-1,1} \times f(l_i-j \oplus 1) & l_i \ne 1 \\
dp_{i-1,0} \times f(l_i-1)+dp_{i-1,1} \times (j \oplus 1) & l_i=1 \\
\end{cases}
$$

实现时我将 $j=0$ 与 $j=1$ 反转了。  
初始化 $dp_{0,1}=1$。

代码如下。

```
cin>>n>>s;
for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
a[n+1]=s;
dp[0][1]=1;
for(int i=1;i<=n+1;i++)
{
	ll l=a[i]-a[i-1];
	for(int j=0;j<2;j++)
	{
		dp[i][j]=(dp[i][j]+dp[i-1][1]*fab(l-j)%mod)%mod;
		dp[i][j]=(dp[i][j]+dp[i-1][0]*fab(l-1-j)%mod)%mod;
		if(j&&l==1)dp[i][j]=(dp[i][j]+dp[i-1][0])%mod;
	}
}
cout<<dp[n+1][0];
```

最后是

## 完整代码

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
void c(ll a[2][2],ll b[2][2])
{
	ll x[2][2]={0,0,0,0};
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				x[i][j]=(x[i][j]+a[i][k]*b[k][j]%mod)%mod;
	memcpy(a,x,sizeof(x));
}
ll fab(ll x)
{
	if(x<=0)return 0;
	ll fa[2][2]={1,0,0,0};
	ll ans[2][2]={1,1,1,0};
	x--;
	while(x)
	{
		if(x&1)c(fa,ans);
		c(ans,ans);
		x=(x>>1);
	}
	return fa[0][0];
}
int n;
ll dp[100003][2],a[100003],s;
int main()
{
	cin>>n>>s;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	a[n+1]=s;dp[0][1]=1;
	for(int i=1;i<=n+1;i++)
	{
		ll l=a[i]-a[i-1];
		for(int j=0;j<2;j++)
		{
			dp[i][j]=(dp[i][j]+dp[i-1][1]*fab(l-j)%mod)%mod;
			dp[i][j]=(dp[i][j]+dp[i-1][0]*fab(l-1-j)%mod)%mod;
			if(j&&l==1)dp[i][j]=(dp[i][j]+dp[i-1][0])%mod;
		}
	}
	cout<<dp[n+1][0];
	return 0;
}
```

时间复杂度 $O(N\log S)$，撒花。

---

## 作者：Coffee_zzz (赞：1)

首先考虑没有前缀和的限制时怎么做。

定义 $f_i$ 表示序列中所有数之和为 $i$ 时的方案数。

容易得到转移方程：

$$
f_i=f_{i-1}+f_{i-3}+f_{i-5}+\cdots
$$

直接转移的复杂度是 $\mathcal O(S^2)$ 的，考虑优化。

我们设：

$$
\begin{aligned}
& s_i=f_{i-1}+f_{i-3}+f_{i-5}+\cdots\\
& t_i=f_{i-2}+f_{i-4}+f_{i-6}+\cdots
\end{aligned}
$$

则：

$$
\begin{aligned}
&f_i=s_i\\
&s_{i+1}=f_i+t_i\\
&t_{i+1}=s_i
\end{aligned}
$$

直接递推的复杂度是 $\mathcal O(S)$ 的，继续优化。

我们考虑下面的矩阵：

$$
\begin{bmatrix}
s_i & t_i
\end{bmatrix}
$$

由于 $f_i=s_i$，所以每次转移相当于给该矩阵乘上了：

$$
\begin{bmatrix}
1 & 1\\
1 & 0
\end{bmatrix}
$$

注意到每次乘的矩阵是相同的，所以可以使用矩阵快速幂将复杂度优化至 $\mathcal O(\log S)$。

接下来考虑怎么处理前缀和的限制。

根据 $f$ 的定义可以知道，每个 $A_k=i$ 的限制相当于强制使 $f_i$ 的值变成了 $0$，此时：

$$
\begin{aligned}
&s_{i+1}=f_i+t_i=t_i\\
&t_{i+1}=s_i
\end{aligned}
$$

所以这时的转移相当于给原矩阵乘上了：

$$
\begin{bmatrix}
0 & 1\\
1 & 0
\end{bmatrix}
$$

于是我们分成 $n+1$ 段计算，每段之间特殊处理即可。

时间复杂度 $\mathcal O(n+\log S)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll long long
#define i128 __int128
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define vei vector<int>
#define pq priority_queue
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;
const int mod=998244353,N=1e5+5;
struct mat{
	int v[3][3]={};
};
mat mul(mat a,mat b){
	mat res;
	for(int i=1;i<=2;i++) for(int j=1;j<=2;j++) for(int k=1;k<=2;k++) res.v[i][j]=(res.v[i][j]+a.v[i][k]*b.v[k][j])%mod;
	return res;
}
mat ksm(mat a,int b){
	mat res;
	res.v[1][1]=res.v[2][2]=1;
	while(b){
		if(b&1) res=mul(res,a);
		a=mul(a,a);
		b>>=1;
	}
	return res;
}
int n,s,a[N];
void solve(){
	cin>>n>>s;
	mat m,p,q;
	m.v[1][1]=1;
	p.v[1][1]=p.v[1][2]=p.v[2][1]=1;
	q.v[1][2]=q.v[2][1]=1;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		m=mul(m,ksm(p,a[i]-a[i-1]-1));
		m=mul(m,q);
	}
	m=mul(m,ksm(p,s-a[n]-1));
	cout<<m.v[1][1]<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc258_h)

考虑刻画答案序列 $\{B_i\}$ 的前缀和，发现其前缀和必然是一奇一偶的形式，并且最后必然是 $S$。

先暂时不讨论最后一个数为 $S$。

不妨考虑 dp，设 $f_{i, 0/1}$ 表示考虑前 $i$ 个数，然后最后一个是偶数还是奇数的方案数。

- 如果选 $i$，那么肯定有 $f_{i, j} \gets f_{i - 1, j \oplus 1}$，其中 $j = i\bmod 2$。
- 而如果不选 $i$，那么只能 $f_{i, 0} \gets f_{i - 1, 0}$，$f_{i, 1} \gets f_{i - 1, 1}$。

边界条件为 $f_{0, 0} = 1$。

考虑到最终一定要选 $S$，那么答案为 $f_{S - 1, (S\bmod 2) \oplus 1}$。

这样做的时间复杂度是 $O(S)$ 的。

---

考虑到很多 $i$ 都可以选，而不可以选的 $i$ 只有 $N$ 个。

而对于可以选的 $i$ 显然是可以用矩阵加速的。

于是我们就按 $\{A_n\}$ 分段矩阵快速幂，所以时间复杂度就可以做到 $O(N\log S)$ 了。

---

注意到这样写会更麻烦一点，因为 $i$ 是奇数和 $i$ 是偶数的转移矩阵不同。

所以我们重新设计状态，$f_{i, 0/1}$ 表示考虑前 $i$ 个数，最后一个数和 $i$ 的奇偶性是否相同，这样就变成了：

- 如果选 $i$，$f_{i, 1} \gets f_{i - 1, 1}$。
- 如果不选 $i$，$f_{i, 0} \gets f_{i - 1, 1}$，$f_{i, 1} \gets f_{i - 1, 0}$。

初始化 $f_{0, 1} = 1$，然后答案为 $f_{S - 1, 1}$，并且转移矩阵不会因为 $i$ 的奇偶性变化。
$$
\mathbf{A} = 
\begin{bmatrix}
0 & 1 \\
1 & 1 \\
\end{bmatrix}
$$

> 这题启发我们，先设计出最简单的 dp，然后再去优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
#define ll long long
const ll mod = 998244353; 
ll inline read() {
	ll num = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + (ch ^ 48);
		ch = getchar();
	}
	return num * f;
}
int n; ll S, a[N]; 
struct Matrix {
	ll M[4];
	Matrix(bool isT = false) {
		if(isT) M[1] = M[2] = 0, M[0] = M[3] = 1; 
		else M[0] = M[1] = M[2] = M[3] = 0; 
	}
	ll& operator [](const int index) { return M[index]; }
	const ll& operator [](const int index) const { return M[index]; }
	Matrix operator * (const Matrix &o) const {
		Matrix res; 
		res[0] = (M[0] * o[0] + M[1] * o[2]) % mod; 
		res[1] = (M[0] * o[1] + M[1] * o[3]) % mod; 
		res[2] = (M[2] * o[0] + M[3] * o[2]) % mod; 
		res[3] = (M[2] * o[1] + M[3] * o[3]) % mod; 
		return res; 
	}
} A, ans;
Matrix qp(Matrix A, ll b) {
	Matrix res(true);
	while(b) {
		if(b & 1) res = res * A;
		A = A * A, b >>= 1;  
	}
	return res; 
}
int main() {
#ifdef file
	freopen("ABC258H.in", "r", stdin);
	freopen("ABC258H.out", "w", stdout);
#endif
	n = read(), S = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	A[1] = A[2] = A[3] = 1, A[0] = 0;
	ans[0] = ans[2] = ans[3] = 0, ans[2] = 1;
	for(int i = 1; i <= n; ++i) {
		ans = qp(A, a[i] - a[i - 1] - 1) * ans;
		swap(ans[0], ans[2]);
	}
	ans = qp(A, S - a[n] - 1) * ans;
	printf("%lld", ans[2]);
	return 0;
}
```

---

## 作者：KarmaticEnding (赞：0)

# 这是前记

可以讲一下我的心路历程。

第一想法就是用总方案数减去不合法方案数。设 $f_i$ 表示序A列总和为 $i$ 的方案数，那么合法方案数就是 $f_S-f_{A_1}-f_{A_2}-\dots-f_{A_n}$。随即我就发现，这个思路里面的 $f$ 巨大且难以维护，所以我就放弃了。

Few days later，我在某矩阵题单里面发现了这道题，我就开始思考，这道题跟矩阵有什么关系吗？众所周知矩阵乘法的作用是转加为乘，转 $O(n)$ 的递推为 $O(\log n)$ 的快速幂，我就在想是否存在一些递推关系使得我们可以快速求出总方案数？

# 这是我的解法

设 $f_i$ 表示和为 $i$ 的 __合法__ 序列数量，那么：

  - 当 $i\in A$ 的时候，$f_i=0$。
  - 其他情况下，$f_i=f_{i-1}+f_{i-3}+\dots$

其中 $f_0=1$。

现在思路出来了，怎么优化呢？这个时间复杂度明显是不行的。

观察到，对于式子 $f_i=f_{i-1}+f_{i-3}+\dots$，右式是不是有一点前缀和的形式？那么，现在我们设 $s_i=f_{i}+f_{i-2}+\dots$，则这个 $s$ 数组拥有以下的性质：

$$
\left\{\begin{matrix} 
  f_i=s_{i-1}\\
  s_i=s_{i-2}+f_{i}
\end{matrix}\right. 
$$

[错误的思路]([云剪贴板 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/paste/tw467vbs))

555这个思路我写到最后才发现它是错的，因为如果$1\in A$，那么 $s_1=s_2=0$，这就没法玩了。但是我也没发现我推导哪里有问题啊？有没有大佬可以在评论区指正一下。

现在回到正确的思路上。观察上面的性质易得以下两个关系式：
$$
\left\{\begin{matrix} 
  f_{i+1}=f_{i}+s_{i-2}\\
  s_i=f_i+s_{i-2}
  
\end{matrix}\right. 
$$
可以使用矩阵递推：
$$
\begin{bmatrix}
  f_{i+1}\\
  s_{i}\\
  s_{i-1}
\end{bmatrix}=\begin{bmatrix}
  1&0&1\\
  1&0&1\\
  0&1&0
\end{bmatrix}\times\begin{bmatrix}
  f_{i}\\
  s_{i-1}\\
  s_{i-2}
\end{bmatrix}
$$
就可以直接写代码了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
int n,s;
ll a[100010];
const ll mod=998244353;
struct MATRIX{
	ll matrix[8][8];
	int rowcount,colcount;//分别表示行数,列数
	MATRIX(){
		memset(matrix,0,sizeof(matrix));
	}
	void getvalue(){//输入
		for(int i=1;i<=rowcount;++i){
			for(int j=1;j<=colcount;++j){
				scanf("%lld",&matrix[i][j]);
			}
		}
	}
	void putvalue(){//输出
		for(int i=1;i<=rowcount;++i){
			for(int j=1;j<=colcount;++j){
				printf("%lld ",matrix[i][j]);
			}
			putchar('\n');
		}
	}
	MATRIX operator*(const MATRIX &rhs)const{
		MATRIX res;
		res.rowcount=rowcount;
		res.colcount=rhs.colcount;
		for(int i=1;i<=3;++i){
			for(int j=1;j<=3;++j){
				for(int k=1;k<=3;++k){
					res.matrix[i][j]+=(matrix[i][k]*rhs.matrix[k][j])%mod;
				}
			}
		}
		return res;
	}
	MATRIX operator^(ll x){
		MATRIX base,res;
		res.matrix[1][1]=res.matrix[2][2]=res.matrix[3][3]=1;
		for(int i=1;i<=3;++i){
			for(int j=1;j<=3;++j){
				base.matrix[i][j]=matrix[i][j]%mod;
			}
		}
		while(x){
			if(x&1){
				res=base*res;
			}
			base=base*base;
			x=x>>1;
		}
		return res;
	}
}ans,b,tmp;
int main(){
	ans.colcount=1;
	ans.rowcount=3;
	ans.matrix[1][1]=1,ans.matrix[2][1]=0,ans.matrix[3][1]=0;
	b.colcount=b.rowcount=tmp.colcount=tmp.rowcount=3;
	b.matrix[1][1]=b.matrix[1][3]=b.matrix[2][1]=b.matrix[2][3]=b.matrix[3][2]=1;
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		tmp=b^(a[i]-a[i-1]);
		ans=tmp*ans;
		ans.matrix[1][1]=0;//撞到A数组上了
	}
	tmp=b^(s-a[n]);
	ans=tmp*ans;
	printf("%lld",ans.matrix[1][1]);
	return 0;
}

```

---

