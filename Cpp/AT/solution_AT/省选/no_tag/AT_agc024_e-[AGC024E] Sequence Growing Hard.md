# [AGC024E] Sequence Growing Hard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc024/tasks/agc024_e

次の条件を満たす数列の組 $ (A_0,A_1,...,A_N) $ としてありうるものの個数を $ M $ で割ったあまりを求めてください。

- 全ての $ i(0\leq\ i\leq\ N) $ に対し、$ A_i $ は $ 1 $ 以上 $ K $ 以下の整数からなる長さ $ i $ の数列である
- 全ての $ i(1\leq\ i\leq\ N) $ に対し、$ A_{i-1} $ は $ A_i $ の部分列である。すなわち、ある $ 1\leq\ x_i\leq\ i $ が存在し、$ A_i $ の $ x_i $ 文字目を取り除いてできる数列が $ A_{i-1} $ に一致する
- 全ての $ i(1\leq\ i\leq\ N) $ に対し、$ A_i $ は辞書順で $ A_{i-1} $ より大きい

## 说明/提示

### 制約

- $ 1\ \leq\ N,K\ \leq\ 300 $
- $ 2\ \leq\ M\ \leq\ 10^9 $
- $ N,K,M $ は整数である

### Sample Explanation 1

以下の $ 5 $ つの組が条件を満たします。 - $ (),(1),(1,1) $ - $ (),(1),(1,2) $ - $ (),(1),(2,1) $ - $ (),(2),(2,1) $ - $ (),(2),(2,2) $

## 样例 #1

### 输入

```
2 2 100```

### 输出

```
5```

## 样例 #2

### 输入

```
4 3 999999999```

### 输出

```
358```

## 样例 #3

### 输入

```
150 150 998244353```

### 输出

```
186248260```

# 题解

## 作者：zhylj (赞：36)

[阅读体验，博客](http://zhylj.cc/index.php/archives/37/)

## 题目

求有多少个序列组 $A_0,A_1,\cdots,A_n$ 满足：

- $A_i$ 的长度为 $i$，且其中元素均为属于 $[1,K]$ 的整数。
- $A_{i-1}$ 为 $A_i$ 的子序列。
- $A_i$ 的字典序大于 $A_i$.

对 $M$ 取模。

$1\le n,K\le 300$，$2\le M\le 10^9$.

## 分析

大概是一个比较不同的二维 dp 的切入方法。

先考虑一个弱化版的问题：给定 $A_n$，求有多少种可能的序列组 $A_0,\cdots,A_{n-1}$.

我们发现，由 $A_n$ 得到 $A_0$ 的过程相当于每次从 $A_n$ 中删一个数，并要求字典序递减。

「字典序递减」看上去不是很好处理，于是考虑其是否存在等价条件：假如我们删了 $s$ 的第 $i$ 个位置得到了 $s'$，可以发现，$s$ 的前 $i - 1$ 个位置构成的前缀和 $s'$ 的前 $i - 1$ 个位置构成的前缀完全相同，我们实际上需要比较的是这两个串从 $i$ 开始的后缀的字典序。

注意到我们有 $s_{j+1}=s'_{j}(j\ge i)$，想象一下比较字典序的过程：

- 若 $s_i = s'_i = s_{i+1}$，则比较位置 $s_{i + 1}$ 和 $s'_{i+1}$.
- 若 $s_{i+1} = s_i =  s'_{i+1} = s_{i+2}$，则比较位置 $s_{i+2}$ 和 $s_{i+2}'$.
- ...

故「$s$ 删去第 $i$ 个元素后字典序变小」的条件实际上等价于：「$s_i$ 大于 $i$ 之后第一个不等于 $s_i$ 的元素」。

但是，我们注意到，如果 $s$ 存在一段相同的元素，那么删除这段元素中的任何一个所得到的结果完全相同，它们不应该被重复统计，所以我们不妨给这段元素人为地定一个顺序：直觉告诉我们，定义每次只能删除一段连续元素中最右边的元素是最为方便的。

然后，我们再重新审视一下我们的条件，发现它惊人的简洁：「$s_i > s_{i+1}$」（当然，最后一个元素是一定能删的）.

于是我们考虑 dp，设 $f_{i,j}$ 表示长度为 $i$ 的 $A_i$，只用了 $[1,j]$ 中的整数的方案数。

转移的时候，为了避免重复，我们枚举**第一个** $1$ 出现的位置 $k$，以及这个 $1$ 被删除的时刻 $p$。那么就意味着：$1$ 后面的 $i - k$ 个数必须在前 $p - 1$ 个时刻中全部被删除。

于是有：

$$
f_{i,j} = \sum_{k=1}^i \sum_{p=i-k+1}^i f_{k-1,j-1}f_{i-k,j}{p-1\choose i-k}
$$

注意到 $\sum {p-1\choose i-k}$ 只和 $i,k$ 有关，而与 $j$ 无关，所以可以预处理，时间复杂度就做到了 $\mathcal O(n^3)$.

然后这题就做完了。

## 代码

```cpp
const int kN = 3e2 + 5;

int N, K; ll M;

ll C[kN][kN], t[kN][kN];
void Init() {
	for(int i = 0; i <= N; ++i) {
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % M;
	}
	for(int i = 1; i <= N; ++i)
		for(int k = 1; k <= i; ++k) 
			for(int p = i - k + 1; p <= i; ++p)
				t[i][k] = (t[i][k] + C[p - 1][i - k]) % M;
}

ll f[kN][kN];
void Calc() {
	f[0][0] = 1;
	for(int j = 1; j <= K; ++j) {
		f[0][j] = 1;
		for(int i = 1; i <= N; ++i) {
			for(int k = 1; k <= i; ++k) {
				ll tmp = f[k - 1][j - 1] * f[i - k][j] % M;
				f[i][j] = (f[i][j] + tmp * t[i][k]) % M;
			}
			f[i][j] = (f[i][j] + f[i][j - 1]) % M;
		}
	}
}

int main() { 
	rd(N, K, M);
	Init(); Calc();
	printf("%lld\n", f[N][K]);
	return 0;
}
```

---

## 作者：tzc_wk (赞：19)

UPD 2021.3.20：修复了式子中的一个小 typ

[题目传送门](https://atcoder.jp/contests/agc024/tasks/agc024_e)


楼下大佬用的是三维 $dp$，这里介绍一个二维 $dp$ 的方法。

题目可以转化为每次在序列中插入一个 $[1,k]$ 的数，共操作 $n$ 次，满足后一个序列的字典序严格大于前一个序列，问有多少种操作序列。

显然相同的数可以合并，因为在由相同的数 $x$ 组成的数段中，在任何位置插入 $x$，得到的序列都是相同的。

再考虑字典序的问题。你只能序列末尾或者一个 $<x$ 的数前面插入 $x$，否则得到的序列的字典序就会 $\geq$ 原序列的字典序。

但这样问题还是比较棘手，我们还需进一步转化。

我们把操作序列转化为一棵有根树，树上每个节点都是一个二元组 $(val,dfn)$，表示第 $dfn$ 次操作插入了值为 $val$ 的数。如果第 $i$ 次操作将 $v$ 插在第 $j$ 次操作插入的数 $w$ 前面，那么我们就将节点 $(v,i)$ 挂在 $(w,j)$ 下面。新建一个虚拟节点 $(0,0)$，如果在序列末尾插入 $v$，那么就把 $(v,i)$ 挂在 $(0,0)$ 下面。

由于我们只能在 $<x$ 的数前面插入 $x$，因此若 $y$ 为 $x$ 的父亲，那么 $val_y>val_x$，$dfn_y<dfn_x$。

不妨举个例子，假设有如下的操作序列：

1. 向序列中插入数 $1$，得到序列 $[1]$。这可看成将点 $(1,1)$ 挂在点 $(0,0)$ 下面。
2. 在 $1$ 前插入 $3$，得到序列 $[3,1]$。这可看成将点 $(3,2)$ 挂在点 $(1,1)$ 下面。
3. 在序列末尾插入 $2$，得到序列 $[3,1,2]$。这可看成将点 $(2,3)$ 挂在点 $(0,0)$ 下面。
4. 在 $1$ 再插入一个 $3$，得到序列 $[3,3,1,2]$。这可看成将点 $(3,4)$ 挂在点 $(1,1)$ 下面。
5. 在 $1$ 前插入一个 $2$，得到序列 $[3,3,2,1,2]$。这可看成将点 $(2,5)$ 挂在点 $(1,1)$ 下面。
6. 在第二个 $3$ 前插入一个 $4$，得到序列 $[3,4,3,2,1,2]$。这可看成将点 $(4,6)$ 挂在点 $(3,4)$ 下面。

这样 $6$ 次操作下来，我们得到了一棵 $7$ 个节点的树，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/r3ezeq4v.png)

一种操作序列恰对应一棵树，一棵满足条件的树也对应一种操作序列。因此问题转化为有多少个满足条件的树。

这就可以直接 $dp$ 了。我们设 $dp_{i,j}$ 表示有多少个以 $i$ 为节点的树，根节点的 $val$ 为 $j$。

考虑转移，对于 $i>1$，假设根节点的 $dfn$ 为 $1$，那么根节点必定有个儿子，其 $dfn$ 为 $2$。我们就枚举这棵子树的大小 $l$ 和根节点的 $val$ —— $v$。确定这棵子树的形态的方案数为 $dp_{l,v}$，将这棵子树中所有节点的 $dfn$ 值定好的方案数为 $C_{n-2}^{k-1}$（从 $3$ 到 $n$ 这 $n-2$ 个数中中选择 $k-1$ 个数），填好剩余部分的方案数为 $dp_{i-l,j}$。因此有转移方程：

$$dp_{i,j}=\sum\limits_{l=1}^{i-1}C_{n-2}^{k-1} \times dp_{i-l,j} \times \sum\limits_{v=j+1}^k dp_{l,v}$$

后面那个 $\sum$ 可以用前缀和优化掉。时间复杂度也是 $\mathcal O(n^2k)$

```cpp
/*
Contest: -
Problem: Atcoder Grand Contest 024 E
Author: tzc_wk
Time: 2020.7.22
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define y1			y1010101010101
#define y0			y0101010101010
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
int n=read(),k=read(),m=read();
int C[305][305],s[305][305],dp[305][305];
signed main(){
	fz(i,0,300){
		C[i][0]=1;
		fz(j,1,i)	C[i][j]=(C[i-1][j]+C[i-1][j-1])%m;
	}
//	printf("%d\n",C[5][3]);
	fz(i,0,k)	dp[1][i]=1;
	fd(i,k,0)	s[1][i]=(s[1][i+1]+dp[1][i])%m;
	fz(i,2,n+1){
		fz(j,0,k)
			fz(l,1,i-1)
				dp[i][j]=(dp[i][j]+C[i-2][l-1]*dp[i-l][j]%m*s[l][j+1]%m)%m;
		fd(j,k,0)	s[i][j]=(s[i][j+1]+dp[i][j])%m;
	}
	printf("%lld\n",dp[n+1][0]);
	return 0;
}
```

---

## 作者：Yansuan_HCl (赞：6)

**UPD 24/12/13 修正笔误：$\binom{i+j-2}{j}$ 应为 $\binom{i+j-2}{j - 1}$。**

即每次插入一个数，使得每次操作后序列的字典序大于操作前的数组。观察发现，一个数只有插入在**小于**它的数前面，或插入在序列尾，才**一定**能使字典序变大。可以在序列尾放一个无穷小的虚点，方便实现。

考虑怎样计数操作，不会做。试想更简单的问题：对于一个确定的序列，怎样刻画“插入”操作并对其计数？根据性质，一个数会插入在另一个数前。因此，可以考虑向位置靠后的数连边。这样，每个位置都有一个出边，只有虚点没有出边。所以这是一棵树，树上每个节点的父亲的权值都**严格小于**它。

这样，对于确定的序列，一个插入方案可以被写成一棵树，一棵确定的树也就可以对应一个插入方案。不交子树之间，贡献互不影响。于是转化为计树。

计树题就可以比较方便地做。设 $f_k(i)$ 表示根节点填 $k$，树的大小为 $i$ 的方案数。每次**在最前面**加入一棵子树以规避算重——这样加入的子树的根必须紧接着原树的根之后插入——值得注意的是，根据定义，这样加入子树即是“有序”的。可以得到：

$$f_k(i+j) \gets \binom{i+j-2}{j - 1}f_k(i)f_{k'>k}(j)$$

。其中组合数表示：钦点完根和*加入子树*的根，剩下的时刻选一些时刻放入操作。

于是就可以 DP. 进行后缀和优化之后复杂度为 $O(n^2k)$。

```cpp
const int N = 305;
int n, m; ll P;
ll C[N][N];
ll f[N][N], s[N][N];

int main() {
	rd(n, m, P);
	U (i, 0, N - 1) {
		C[i][0] = 1;
		U (j, 1, i)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
	}
	
	U (k, 0, m) f[k][1] = 1;
	D (k, m, 0) s[k][1] = (s[k + 1][1] + f[k][1]) % P;
	// f_k(i+j) <- f_k(i)f_{k' > k}(j) * C_{i-2+j}^{j}
	// f_k(i) = \sum_{x+y=i, x,y>=1} f_k(x) * s_{k+1}(y) * C_{i-2}^y
	U (i, 2, n + 1) {
		U (k, 0, m)
			U (x, 1, i - 1)
				(f[k][i] += C[i - 2][x - 1] * f[k][x] % P * s[k + 1][i - x]) %= P;
		D (k, m, 0) (s[k][i] = s[k + 1][i] + f[k][i]) %= P;
	}
	printf("%lld", (f[0][n + 1] % P + P) % P);
}
```

---

## 作者：rong_nian (赞：4)

[题目链接](https://www.luogu.com.cn/problem/AT3962)  
孩子太菜了自己改不出看了别人题解才AC。/kk
### 题目大意 :
给定 $n, k, m$，求满足一下条件的 $(n + 1)$ 元序列组 $(A_0, A_1, \cdots, A_n)$ 的数量 对 $m$ 取模。  

- 对于任意的 $i$，序列 $A_i$ 由 $1 \text{~} K$ 之间的整数构成，长度为 $i$ 。
- 对于任意 $i > 1$，序列 $A_{i-1}$ 是 $A_i$ 的子序列。
- 对于任意 $i> 1$，序列 $A_{i-1}$ 在字典序意义下严格小于 $A_i$。  

$1 \le n,k \le 300$，$2 \le m \le 10^9$ , $n, m, k$ 都是整数。不保证 $m$ 是质数( 参考自 [@CHHC](https://www.luogu.com.cn/user/82472)）。

### Solution : 

我们考虑什么时候字典序会变小。

如果在一串 xxxxxb 中再插入一个 x 形成的 xxxxxxxb， x < b 这样就会减小。

而且如果我们每次都把 x 放在 $A_i$ 的最后，我们的答案就不会算重。  

所以在将 $A_i$ 变为 $A_{i + 1}$ 的过程中，x 要满足 **大于** 它后面的那个数，或在序列的末尾（不能大于等于, 那样会重复）。

我们令 $dp[i][j][k]$ 表示当前进行到第 $i$ 个操作，现在放到了数字 $j$ ，前面有 $k + 1$ 个位置可以放（也就是前面有 $k$ 段连续数字，剩下的那个 $+1$ 是因为开头也是能放的）。

当前数不放 ：

- $dp[i][j][k-1] += dp[i][j][k] (k > 0)$
- $dp[i][j + 1][i] += dp[i][j][k] (k=0)$ 这是因为我们现在已经没位置能放了，我们就要跳到下一个数了。

当前数放了 ： 

$dp[i+1][j][k] += dp[i][j][k] \times (k + 1)$ 

表示我们多进行了一次操作而且这个操作有 $(k + 1)$ 种选择。

最后输出 $dp[n][k][0]$ 即可。（这个 $k$ 是题目里给的那个）

### Code : 

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, mod, dp[305][305][305];

int main() {
    cin >> n >> m >> mod;
    dp[0][1][0] = 1;
    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = i; k >= 0; --k) {
                if (dp[i][j][k] == 0) continue;
                if (!k) dp[i][j + 1][i] = (dp[i][j + 1][i] + dp[i][j][k]) % mod;
                else dp[i][j][k - 1] = (dp[i][j][k - 1] + dp[i][j][k]) % mod;
                if (i <= n - 1) 
                dp[i + 1][j][k] = (dp[i + 1][j][k] + 1ll * (k + 1) * dp[i][j][k] % mod) % mod;
            }
        }
    }
    cout << dp[n][m][0] << endl;
    return 0;
}
```
参考文章 ：  
- http://blog.leanote.com/post/rockdu/0227
- https://www.luogu.com.cn/blog/CHHC/Solution-AT3962

别人的神奇做法 ：
- [洛谷题解](https://www.luogu.com.cn/problem/solution/AT3962)
- [Froggy yyds](https://www.luogu.com.cn/blog/froggy/agc024-solution)

---

## 作者：pengyule (赞：3)

https://atcoder.jp/contests/agc024/tasks/agc024_e

模拟这个过程。

![image.png](https://s2.loli.net/2022/01/05/f47GVtKoO8LZDR6.png)

其中 `#` 代表其他的数，不重要，我们关键看 `x` 的动作。

为了不重复统计，我们规定 **$x$ 是一个连续相同数字段的起头**。

在左边能插入数的充要条件是，插入的数**大于** $x$。

为什么？有归纳法：
1. 第一次（第一行到第二行）显然需要大于；
2. 后面只需要以现在左边 `#` 全大于 $x$ 为前提，这种情况下由于我们规定了 $x$ 是起头的因此很容易意会。

我们设 `x` 位置值为 $x$，其左侧（不含）有 $k$ 个 `#`，这是在考虑 $A_i$，$A_i$ 里只能用 $[j,m]$ 中的数，为 $f(i,j)$。

那么
$$
f(i,j)=\sum_{x=j}^{m}\sum_{k=0}^{i-1}f(k,x+1)f(i-1-k,j){{i-1}\choose{k}}
$$
第一个 $f(k,x+1)$ 是左边一坨 `#` 的方案，同理…是右边的，而为什么要乘组合数？

因为上面绿色的 `+`，虽然左边和右边所加的数的**集合**是确定的，但操作序列的顺序是有区别的，我们可以任意决定这些 `+` 号在竖直方向的相对位置！

$O(n^5)$。接着发现组合数只跟 $i,k$ 相关便可以预处理。$O(n^4)$。

最后便是前缀和优化。$O(n^3)$。

由于 $x$ 只出现了一次，而且每次都是查 $j+1\sim m+1$ 这个后缀，因此通过结合律可以知道
$$
f(i,j)=\sum_{k=0}^{i-1}t(k,j)f(i-1-k,j){{i-1}\choose{k}},\text{where }t(i,j)=f(i,j+1)+f(i,j+2)+...+f(i,m+1)
$$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=305;
int n,m,mod,f[N][N],t[N][N],C[N][N];
int main(){
	cin>>n>>m>>mod;
	C[0][0]=1;
	for(int i=1;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int i=1;i<=m+1;i++)f[0][i]=1;for(int i=m;i;i--)t[0][i]=t[0][i+1]+f[0][i+1];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			for(int k=0;k<i;k++)
				(f[i][j]+=1ll*t[k][j]*f[i-1-k][j]%mod*C[i-1][k]%mod)%=mod;
		for(int j=m;j;j--)t[i][j]=(t[i][j+1]+f[i][j+1])%mod;
	}
	cout<<f[n][1];
}
```



---

## 作者：chenxia25 (赞：3)

tzc：“AtC风格的计数DP。”我就想问了，AtC的题怎么可能不是AtC风格的呢？

> ### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT3962) & [AtC题目页面传送门](https://atcoder.jp/contests/agc024/tasks/agc024_e)

>给定$n,m,p$，求有多少个值域为$[1,m]\cap\mathbb Z$的序列$n+1$元组$(a_0,a_1,\cdots,a_n)$，满足：

>1. $\forall i\in[0,n],|a_i|=i$；
>1. $\forall i\in[0,n)$，$a_i$是$a_{i+1}$的子序列；
>1. $\forall i\in[0,n),a_i<a_{i+1}$。

>答案对$p$取模。

>$n,m\in[1,300],p\in\left[2,10^9\right]$。

显然，原问题等价于，一个序列$a$一开始为空，$n$次每次往里任意位置塞一个$[1,m]$内的数，使得字典序大于原来的序列，求$n$次组成的序列组的个数（注意这里不能说操作的数量，因为在不同位置插入相同数可能得到的序列一样）。

考虑在位置$x$插入$y$合法的充要条件。若$x=|a|+1$显然合法。剩下的显然要满足$[y]+a_{x,|a|}>a_{x,|a|}$。若$y\neq a_x$，那么字典序相对大小决定在它们身上，所以$y>a_x$。否则的话，，，注意到若把$y$插入到往右数第一个满足$y\neq a_{x'}$的位置$x'$，那么得到的序列是一样的，为了去重，我们可以直接不考虑这种情况，反而更方便了。于是充要条件就是$x=|a+1|$或$y>a_x$。

分析完之后还是不会做。这是一个动态的插入问题，每次的$a$都会变。不妨将时间定格在最后一刻，所有数都各就各位了，再来考虑每个位置$i$上的值$v_i$与被插入的时间（时间戳）$dfn_i$。

稍微转化一下，此时一个$(v,dfn)$序列合法当且仅当，$\forall i\in[1,n],v_i>v_{\min\limits_{j>i,dfn_j<dfn_i}\{j\}}$（为了方便，设$v_{n+1}=dfn_{n+1}=0$，合理性显然）。考虑$v_i$要$>$的那个东西固定的一个，就是使得$dfn_x=1$的$x$。它的条件是$v_x>v_{n+1}=0$。然后不难发现，$\forall i\in[1,x),\min\limits_{j>i,dfn_j<dfn_i}\{j\}\in[1,x]$，对应的，$\forall i\in(x,n],\min\limits_{j>i,dfn_j<dfn_i}\{j\}\in[x+1,n+1]$。这样就可以把问题分解成$x$左右两半相似的问题，其中左边的值域变成$(v_x,m]$，右边值域不变。问题就迎刃而解了。

考虑DP。设$dp_{i,j}$表示$(v,dfn)$序列的大小为$i$，值域为$[j,m]$的方案数。边界$dp_{0,j}=1$，目标$dp_{n,1}$。枚举$dfn_x=1$的$x$和$v_x$两个东西，就可以转移了，注意到若左右各找一个方案，那么左右两半内部的$dfn$相对大小固定，而跨越左右两半的$dfn$相对大小無·所·謂，将它们的$dfn$值域共同扩展，还要乘上一个组合数。

状态转移方程：

$$dp_{i,j}=\sum_{k=1}^i\sum_{o=j}^mdp_{k-1,o+1}dp_{i-k,j}\binom{i-1}{k-1}$$

不过这样时间复杂度是$\mathrm O\!\left(n^4\right)$的（视$n,m$同阶），然鹅很好优化，移一下$\sum$得到

$$dp_{i,j}=\sum_{k=1}^idp_{i-k,j}\binom{i-1}{k-1}\sum_{o=j}^mdp_{k-1,o+1}$$

则实时维护$\forall i\in[0,n],dp_i$的前缀和，后面那个$\sum$调用一下前缀和复杂度就少一个$n$了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300,M=300;
int n,m,mod;
int comb[N+1][N+1];
int dp[N+1][M+2];
int Sum[N+1][M+2];
int main(){
	cin>>n>>m>>mod;
	comb[0][0]=1;
	for(int i=1;i<=n;i++)for(int j=0;j<=i;j++)comb[i][j]=((j?comb[i-1][j-1]:0)+(j<i?comb[i-1][j]:0))%mod;//预处理组合数 
	for(int i=1;i<=m+1;i++)Sum[0][i]=(Sum[0][i-1]+(dp[0][i]=1))%mod;//边界 
	for(int i=1;i<=n;i++){//转移 
		for(int j=1;j<=m;j++){
			for(int k=1;k<=i;k++)(dp[i][j]+=1ll*dp[i-k][j]*comb[i-1][k-1]%mod*(Sum[k-1][m+1]-Sum[k-1][j])%mod)%=mod;//转移方程 
			Sum[i][j]=(Sum[i][j-1]+dp[i][j])%mod;//维护前缀和 
//			printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
		}
		Sum[i][m+1]=Sum[i][m];//维护前缀和 
	}
	cout<<(dp[n][1]+mod)%mod;//目标 
	return 0;
}
```

---

## 作者：FZzzz (赞：2)

下文中的 $m$ 就是原题面中的 $k$~~，因为不然循环变量就不够用了~~。

$A_i$ 可以看成是由 $A_{i-1}$ 插入一个字符得到的。考虑插入时需要满足什么条件，发现这次插入会使后面整体右移一位，第一个不同的位置则是后面第一个与插入的字符不同的位置，那么限制就是插入的字符比这个字符大。

在连续的一段相等的字符中的任意一个位置插入一个这种字符，得到的结果是相同的。出于去除重复计数和简化限制两方面的考虑，我们将限制改为：后一个字符比插入的字符小。那么我们可以直接对每次插入的位置和插入的字符计数，就能够统计到所有不同的方案。

这样还是不易于统计，再做一步转化，把每个字符的位置用它被插入的时间表示。那么我们需要做的即是对每次操作，选择之前的一次操作表示这次插在之前插的位置前面。特别地，选择 $0$ 操作表示这次插在最后面。

这样形成了一个树形结构，$0$ 是根节点。那么问题转化为对一个有标号的树计数，每个点有一个 $[0,m]$ 的权值，根的权值和编号都为 $0$，要满足儿子的编号和权值都比父亲大。

设计一个 dp，$f_{i,j}$ 表示根的权值为 $j$ 的 $i$ 个点的树的数量。转移时枚举编号最小的儿子的编号和数量，相当于把这个子树的编号插到其他子树去。有转移方程：
$$f_{i,j}=\sum_{k=1}^{i-1}\sum_{h=j+1}^m\binom{i-2}{k-1}f_{k,h}f_{i-k,j}$$
预处理组合数，后缀和优化即可。时间复杂度 $O(n^2m)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=300+5;
int n,m;
ll p,C[maxn][maxn],f[maxn][maxn],s[maxn][maxn];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	m=readint();
	p=readint();
	for(int i=0;i<=n+1;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
	}
	for(int i=0;i<=m;i++){
		f[1][i]=1;
		s[1][i]=m-i+1;
	}
	for(int i=2;i<=n+1;i++) for(int j=m;j>=0;j--){
		for(int k=1;k<i;k++)
			f[i][j]=(f[i][j]+s[k][j+1]*f[i-k][j]%p*C[i-2][k-1]%p)%p;
		s[i][j]=(s[i][j+1]+f[i][j])%p;
	}
	printf("%lld\n",f[n+1][0]);
	#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
	#endif
	return 0;
}
```
这是这题现在的主流做法，但是其实还有更简洁巧妙的 dp 方式。设 $f_{i,j}$ 为 $j$ 个节点权值不大于 $i$ 的树的个数。

每次枚举权值小于 $i$ 的节点的个数 $k$，那么另外 $j-k$ 节点一定全是叶子。考虑从 $f_{i-1,k}$ 转移时的转移系数，我们需要的是给这 $j-k$ 个点找到父亲，再给所有点重新分配编号。我断言，这样做的方案数相当于把 $j$ 个有区别元素分配进 $k$ 个无区别非空集合里。

建立这两件事之间的双射。把这些集合按照各自的最小元排序，然后按照 $k$ 个点原来的标号顺序对应到这 $k$ 个点。令剩下这些元素对应到新加进来的 $j-k$ 个点，每个点的父亲为它集合内的最小元对应的点。这样可以证明两个方案数是相等的。

举个例子，假如我本身有一棵两个节点的树，现在新加入一个节点，那么：
- 集合分配是 $\{\{0\},\{1,2\}\}$，那么原来的点编号是 $0$ 和 $1$，新加入的点编号是 $2$，父亲是 $1$；
- 集合分配 $\{\{0,1\},\{2\}\}$，那么原来的点编号是 $0$ 和 $2$，新加入的点编号是 $1$，父亲是 $0$；
- 集合分配是 $\{\{0,2\},\{1\}\}$，那么原来的点编号是 $0$ 和 $1$，新加入的点编号是 $2$，父亲是 $0$。

这样就把两个问题的方案一一对应。

那么转移方程就是：
$$f_{i,j}=\sum_{k=1}^{j-1}\begin{Bmatrix}j\\k\end{Bmatrix}f_{i-1,k}$$
预处理第二类斯特林数，时间复杂度仍为 $O(n^2m)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=300+5;
int n,m;
ll p,S[maxn][maxn],f[maxn][maxn];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	m=readint();
	p=readint();
	S[0][0]=1;
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<=i;j++)
			S[i][j]=(S[i-1][j]*j%p+S[i-1][j-1])%p;
	}
	f[0][1]=1;
	for(int i=1;i<=m;i++) for(int j=1;j<=n+1;j++)
		for(int k=1;k<=j;k++)
			f[i][j]=(f[i][j]+f[i-1][k]*S[j][k]%p)%p;
	printf("%lld\n",f[m][n+1]);
	#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
	#endif
	return 0;
}
```
遗留问题：
1. 能否对第一个递推式，通过代数推导得到第二个递推式？
2. 在 $m$ 较大时我们显然可以矩阵快速幂 $O(n^3\log m)$（可能可以通过 BM 和特征多项式做到 $O(n^2+n\log n\log m)$？），但能否在 $o(n^2)$ 时间内解决？

~~有没有老哥教教我啊。~~

---

## 作者：kkio (赞：2)

如果在一个位置插入一个数，那么之后的字典序更大的要求，是插入位置之后第一个 $ s_i \neq s_{i+1} $ 的位置满足 $ s_i > s_{i+1} $ 。将连续的一段相同去重，那么每次插入的条件应该是 $ s_i > s_{i+1} $ ，当然，你放开头也可以。只要我们从小到大放，那就一定能满足条件。

设置 $ dp_{i,j,k} $ 表示长度为 $ i $ ，现在考虑放 $ j $ ，后面还有 $ k $ 个位置(不包括开头)没被决定放的方案数。

那么有转移：

1. $ dp_{i,j,k} \rightarrow dp_{i+1,j,k} \times (k+1) $ 。这个转移的意思是当前考虑的位置（包括开头也要算）上放一个 $ j $ ，但是由于你还能往这个 $ j $ 的后面再放，所以你的 $ k $  不变。
2. $ dp_{i,j,k} \rightarrow dp_{i,j,k-1}) $ 。你不打算往这个位置上再放 $ j $了，所以你可决定的位置再减少。
3. $ dp_{i,j,0} \rightarrow dp_{i,j+1,i} $ 。已经没有可放的位置了，考虑下一个 $ j $ ，这个 $ j $ 可以放在所有的已有的数后面和开头。

初始状态 $ dp_{1,0,1} = 1 $ 。答案就是 $ dp_{n,k,0} $ 。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=305;
int n,k,mod;
int dp[maxn][maxn][maxn];
int main()
{
	scanf("%d%d%d",&n,&k,&mod);
	dp[0][1][0]=1;
	for(int i=0;i<=n;i++)
		for(int j=1;j<=k;j++)
			for(int l=n;l>=0;l--)
				if(dp[i][j][l])
				{
					if(l==0)
						dp[i][j+1][i]=(dp[i][j+1][i]+dp[i][j][l])%mod;
					else 
						dp[i][j][l-1]=(dp[i][j][l-1]+dp[i][j][l])%mod;
					dp[i+1][j][l]=(dp[i+1][j][l]+1ll*dp[i][j][l]*(l+1)%mod)%mod;
				}
	printf("%d",dp[n][k][0]);
}
```


---

## 作者：xht (赞：2)

## [Sequence Growing Hard](https://atcoder.jp/contests/agc024/tasks/agc024_e)

### 题意

- 求以序列为元素的满足下列条件的 $n+1$ 元组 $a_{0\dots n}$ 的组数：
  - 对于 $i \in [0,n]$，$a_i$ 长度为 $i$，其包含的元素为 $[1,k]$ 中的整数。
  - 对于 $i \in [1,n]$，$a_{i-1}$ 为 $a_i$ 的子序列。
  - 对于 $i \in [1,n]$，$a_i$ 的字典序 $>a_{i-1}$。
- $n,k \le 300$，答案对 $P$ 取模。

### 题解

考虑从小到大插入数，这样当插入 $i$ 时，插在所有位置都是合法的。

但是这样会算重复，规定相同数只能插在最后即可。

考虑 DP，设 $f_{i,j,k}$ 表示当前插入到第 $i$ 个数，插入的数为 $j$，有 $k$ 个数之后可以放（即有 $k+1$ 个位置可以放）。

转移是 $\mathcal O(1)$ 的，时间复杂度 $\mathcal O(n^3)$。

### 代码

```cpp
const int N = 307;
int n, m;
modint f[N][N][N];

int main() {
	rd(n, m, P);
	f[0][1][0] = 1;
	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = i; ~k; k--)
				if (!!f[i][j][k]) {
					if (k) f[i][j][k-1] += f[i][j][k];
					else f[i][j+1][i] += f[i][j][k];
					f[i+1][j][k] += f[i][j][k] * (k + 1);
				}
	print(f[n][m][0]);
	return 0;
}
```

---

## 作者：RainsAFO (赞：2)

题意：

给定$n,k,mod$，求有多少个序列组$A$，满足：

$1. |A_i| = i$

$2.$所有数在$[1,k]$中，$∀i∈[0,n)$

$3.A_i∈A_i + 1$且$A_i < A_i + 1$

答案对$mod$取模。

思维题。

观察数据范围，应该需要一个$n^3$的算法（这里视$n,k$同阶）

我们无法得知序列组具体的数，于是考虑把$n$个数一个个加进状态中，由于加入一个非严格极大值不影响状态，**所以从小到大加是无后效性的**。

这里出现了一个问题，如何判重？

**我们强制让相同的数挨在一起**，乘上连续段的贡献即可。

转移有三种：

$1.dp[i][j][k - 1] += dp[i][j][k] $  $(k != 0)$

表示不加入这个数

$2.dp[i][j + 1][i] += dp[i][j][k] $ $(k = 0)$

同上，不过已经没有位置可加了

$3.dp[i + 1][j][k] += dp[i][j][k] * (k + 1)$

加入这个数。

代码很好写。

code:

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

#define int long long 

int n , m , mod;

const int N = 305;

int f[N][N][N];
 
void add(int &x , int y){
	x = (x + y >= mod ? x + y - mod : x + y);
}

main() {
	cin >> n >> m >> mod;
	f[0][1][0] = 1;
	for (int i = 0; i <= n; i++)//注意从零开始
		for (int j = 1; j <= m; j++)
			for (int k = i; k >= 0; k--) {
				if (k) 
					add(f[i][j][k - 1] , f[i][j][k]);
				else 
					add(f[i][j + 1][i] , f[i][j][k]);
				add(f[i + 1][j][k] , (f[i][j][k] * (k + 1)) % mod);
	}
	cout << f[n][m][0];
	return 0;
}
```







---

## 作者：CHHC (赞：2)

## 题意
给定$N,K,M$，求满足以下条件的$(N+1)$元序列组$(A_0,A_1,…,A_N)$的数量，$mod M$。
-	对于任意$i$，序列$A_i$由$1$~$K$之间的整数构成，长度为$i$。
-	对于任意$i>1$，序列$A_{i-1}$是序列$A_i$的子序列。
-	对于任意$i>1$，序列$A_{i-1}$在字典序意义下严格小于序列$A_i$。
## 思路
考虑每次向第$i$个序列 “插入”元素时的情况。

因为要满足条件3，所以新插入的元素需要比上一个序列的插入位置的元素要大。可以发现，直接从小往大放是可以覆盖所有情况的。那么考虑去重，钦定当序列中有相同元素时在后面插入即可。

那么自然（……）有了dp状态：$DP(i,j,k)$表示考虑到第i个序列，放到数字j，在第k个数后面可以插入新的数字。

考虑转移：
-	当前状态下加入数字：$DP(i+1,j,k)+=DP(i,j,k)*(k+1)$。（注意可以放在末端，所以是$k+1$）
-	当前状态不加数字：$DP(i,j,k-1)+=DP(i,j,k)$。
-	考虑下一个数字：$DP(i,j+1,k)+=DP(i,j,k)$。

又是一道题面简单代码简单但是思维难度比较大的Atcoder（。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int inf = 1000000007ll;
int mod;

inline void add(int &x, int y)
{
    x += y;
    if (x > mod)
        x -= mod;
}

int N, M;
int dp[333][333][333];

signed main()
{
    ios::sync_with_stdio(false);

    cin >> N >> M >> mod;
    dp[0][1][0] = 1;
    for (int i = 0; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            for (int k = i; k >= 0; k--)
            {
                int &cur = dp[i][j][k];
                if (!cur)
                    continue;
                if (!k)
                    add(dp[i][j + 1][i], cur); // 转移3
                else
                    add(dp[i][j][k - 1], cur); // 转移2
                if (i + 1 <= N)
                    add(dp[i + 1][j][k], cur * (k + 1) % mod); // 转移1
            }
        }
    }
    cout << dp[N][M][0] << endl;
    return 0;
}
```

---

