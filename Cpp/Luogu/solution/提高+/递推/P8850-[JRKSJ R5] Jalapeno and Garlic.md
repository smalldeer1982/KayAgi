# [JRKSJ R5] Jalapeno and Garlic

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/peaku0fe.png)

## 题目描述

一个 $n$ 个点的环，点有点权 $a$，编号依次从 $1\sim n$。点 $1$ 与点 $n$ 相邻。

你希望只存在一个 $x\in[1,n]$ 满足 $a_x\ne 0$。为此，你需要按下面流程进行操作：

1. 选定一个 $x$，表示最终使得 $a_x\ne 0$。**此后不能更改 $x$ 的选择。**
2. 进行若干次修改操作，每次操作你可以选定一个 $y\in[1,n]$，将 $a_y\gets a_y-1$。同时在与点 $y$ 相邻的两个点中**等概率选择**一个，其点权将被 $+1$。

你希望期望的修改次数最少，所以求在最优策略下的期望操作次数（操作 1 不计入）。

## 说明/提示

### 样例 $1$ 解释

选定 $x=2$，进行 $114514$ 次操作，每次的 $y=1$。

### 数据规模

**本题采用捆绑测试。**

| $\text{Subtask}$ | $n\le$ |分值 |
| :----------: | :----------: |:----------: |
| $1$ | $2$ | $5$ |
| $2$ | $10^3$ | $20$ |
| $3$ | $10^4$ | $20$ |
| $4$ | $10^5$ | $20$ |
| $5$ | $10^6$ | $35$ |

对于 $100\%$ 的数据，$2\le n\le 10^6$，$0\le a_i<1004535809$。

## 样例 #1

### 输入

```
2
114514 1919810```

### 输出

```
114514```

## 样例 #2

### 输入

```
3
1 1 2```

### 输出

```
4```

# 题解

## 作者：NaCly_Fish (赞：9)

首先简单转化一下题意，每个位置有 $a_i$ 个棋子，每次操作选择一个棋子，将其随机向相邻位置移动。然后要选择一个目标点，使得期望操作次数最少。

设一个棋子在目标的顺时针 $i$ 格（也就是逆时针 $n-i$ 格）的位置，移到目标的期望次数为 $f_i$，则：

$$f_i=1+\frac 12 (f_{i-1}+f_{i+1}) \  \ (i\in[1,n-1])$$
这个线性方程组可以用常系数线性递推的方法来解：
$$F(x)=2xF(x)-x^2F(x)-\frac{2x}{1-x}+(f_1+2)x$$
$$f_i=i(f_1-i+1)$$
由于 $f_n=0$，解得 $f_i=i(n-i)$。

题目要我们求出期望最小的目标点，不妨直接把所有目标的情况，全都求出答案来。

$$s_d=\sum_{i=1}^n a_i |i-d|(n-|i-d|)$$
这里有个绝对值很烦，考虑拆为：
$$b_d=\sum_{i=1}^{d-1}a_i(d-i)(n-d+i) \ , \ c_d=\sum_{i=d+1}^na_i(i-d)(n-i+d)$$
再把和式中的乘积展开，可以得到（这里以 $b$ 为例，对 $c$ 也是类似的）：
$$b_d=-\left(\sum_{i=1}^{d-1}i^2a_i \right)+(2d-n)\left(\sum_{i=1}^{d-1}ia_i \right)+d(n-d)\left(\sum_{i=1}^{d-1}a_i\right)$$
这样维护三个前缀和即可，对于 $c$ 也就是三个后缀和，做法是一致的。时间复杂度 $\Theta(n)$。

注意值域较大，需要 int128。

---

## 作者：normalpcer (赞：6)

## 题意简述
在一个由 $n$ 个点组成的环上，初始时每个点上有一定数量的棋子（第 $i$ 个点有 $a_i$ 个棋子）。选择一个目标点后，每次操作可以选择一个棋子并将其随机移动到相邻的一个点（左或右，概率均等）。目标是通过合理选择目标点，最小化所有棋子移动到目标点的期望操作次数。

## 分析
### 期望计算
先想办法表示出这个“期望操作次数”。直觉上它会和与目标间的距离有关。

设 $ f_i $ 表示一个棋子距离目标点为 $ i $（逆时针距离）时，到达目标点的期望步数。

易知以下的初始条件：
$$
f_0 = 0, f_n = 0
$$

根据题意，每次操作可以选择向左或向右移动一步，因此：
$$
f_i = \frac{1}{2}(f_{i-1} + 1) + \frac{1}{2}(f_{i+1} + 1)
$$

整理得：
$$
f_{i+1} - f_i = f_i - f_{i-1} - 2
$$

令 $ g_i = f_{i+1} - f_i $，则有：
$$
\begin{aligned}
g_i     &= g_{i-1} - 2  \\
        &= g_0 - 2i
\end{aligned}
$$

累加得到：
$$
\begin{aligned}
f_{i+1} &= f_0 + \sum_{k=0}^i (g_0 - 2k) \\
        &= f_0 + \sum_{k=0}^i g_0 - \sum_{k=0}^i 2k \\
        &= f_0 + (i+1)g_0 - i(i+1)
\end{aligned}
$$

将 $f_n = 0$ 和 $f_0 = 0$ 带入上述公式可知：
$$
g_0 = n-1
$$
$$
f_i = ni - i^2
$$

### 最小化期望
考虑依次枚举所有可能的目标点，计算对于每个目标点，所有棋子的期望步数之和。

如果每次都重新求值，时间复杂度是 $O(n^2)$，无法接受。

不过显然两个目标点之间的期望之和是有一定关联的，考虑它们的变化量。

设当前选中的目标点为 $p$，下一次枚举为 $p + 1$。

这个过程中，绝大多数点到目标点的距离都会减小 $1$，而 $p$ 本身与目标点的距离会变为 $n-1$。

一个与 $p$ 点距离为 $i$ 的棋子（$i \neq 0$），期望步数从 $f_i$ 变为了 $f_{i-1}$，这个过程中的差值为：
$$
\begin{aligned}
f_{i-1} - f_i   &= (ni - i^2) - [n(i - 1) - (i - 1)^2]  \\
                &= 2i - n - 1
\end{aligned}
$$

特别地，
$$
f_{n-1} - f_0 = n - 1
$$

直接按照上个式子计算得到的值为 $-n-1$，相差了 $2n$，最后需要额外加回来。

考虑所有棋子，设有 $t_i$ 个棋子与 $p$ 的距离为 $i$。

于是答案的变化量如下：
$$
\begin{aligned}
\Delta ans  &= 2n + \sum\limits_{i = 0}^{n - 1}t_i(2i - n - 1)  \\
            &= 2n + 2\sum\limits_{i = 0}^{n - 1}i\cdot t_i - (n-1)\sum\limits_{i = 0}^{n - 1}t_i
\end{aligned}
$$

只需要维护 $c_i = i\cdot t_i$ 之和。

还是从 $p$ 到 $p+1$ 这个过程，$p$ 以外的点上的 $c_i$ 都会减小 $t_i$（因为 $i$ 减小了 $1$），总共减小的值即为棋子个数。

特别地，$c_0$ 从 $0$ 变成了 $t_0(n-1)$，再加上刚才额外减的，需要再加上 $n\cdot t_0$。

最后，对于每一个枚举到的目标点，取答案的最小值即可。每次计算答案的复杂度为 $O(1)$，整个过程的复杂度为 $O(n)$。

另外，由于涉及到比较大小，所以不能在中间过程中取模。可以使用 $128$ 位整数存储，并在最后取模和输出。

## 代码
```cpp
/**
 * @link https://www.luogu.com.cn/problem/P8850
 */

#include <bits/stdc++.h>
template <typename T> inline auto chkMin(T &base, const T &cmp) -> T & { return (base = std::min(base, cmp)); }
const char endl = '\n';

using i16 = int16_t; using i32 = int32_t; using i64 = int64_t;
using u16 = uint16_t; using u32 = uint32_t; using u64 = uint64_t; using uz = size_t;
using i128 = __int128;

namespace Solution {
    i32 constexpr mod = 1004535809;  // 1e9
    void solve() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr), std::cout.tie(nullptr);

        i32 N;  std::cin >> N;  // 1e6
        std::vector<i32> a(N);  // 1e9
        for (auto &x: a)  std::cin >> x;

        i64 sigma_ai = 0;  // sigma < 1e15
        i128 sigma_i_times_ai = 0;  // i * a[i] < 1e15, sigma < 1e21 需要 int128
        for (i32 i = 0; i < N; i++) {
            sigma_ai += a[i];
            sigma_i_times_ai += static_cast<i64>(i) * a[i];
        }

        i128 init = 0;
        for (i32 i = 0; i < N; i++) {
            init += static_cast<i128>(a[i]) * i * (N - i);
        }

        i128 cur = init;
        i128 ans = 0;  std::memset(&ans, 0x3f, sizeof(ans));  // 1e36 左右的极大值

        for (i32 p = 0; p < N; p++) {
            chkMin(ans, cur);

            cur += 2 * sigma_i_times_ai;
            cur -= static_cast<i128>(N + 1) * sigma_ai;
            cur += static_cast<i64>(N * 2) * a[p];
            sigma_i_times_ai -= sigma_ai;
            sigma_i_times_ai += static_cast<i64>(a[p]) * N;
        }

        std::cout << static_cast<i32>(ans % mod) << endl;
    }
}

int main() {
    Solution::solve();
    return 0;
}
```

---

## 作者：ღꦿ࿐ (赞：5)

题意题面陈述很清楚了。但是这个大蒜无炮真的很强（？）

---

Tag : 推式子 解方程 最优化问题

一般最优化问题要求答案取模有以下两种情况：

1.有通用的，固定的最优方案结论。

2.答案可以用能够储存的实数表示出来（分母分子不含有较大组合数或阶乘）。

对于这道题，因为没有一种显然的最优策略，所以我们猜测后者。

---

### 考虑如何计算一个点到另一个点的期望次数

（感觉这个问题莫名的典，但我好像又没做过）

令一个 长 $n$ 的环上一对相隔 $i$ 个点的点的期望操作次数为 $f(i)  ,i\in[0,n]$

显然有以下结论

$$f(0) = 0$$

$$f(i) = f(n-i) $$ 


拆开
$$f(i) = \frac{f(i-1)+f(i+1)}{2} +1$$

上式可转化为

$$f(i+1)=2f(i)-f(i-1)-2$$

$$f(i) = 2f(i-1)-f(i-2)-2   \ \ (i>1)$$

发现这是一个环形的方程组，令 $$f(1) = x$$

则 

$$f(2) = 2f(1) -f(0) - 2 = 2x - 2$$

$$f(3) = 2f(2) - f(1) - 2= 3x - 6$$

$$f(4) = 2f(3) - f(2) - 2 =4x - 12$$

$$\dots$$

$$f(k) = kx - k^2+k$$

---

如果你不想知道我是怎么发现这个规律的，请跳过这几行。

其实是这样的：

$$

\begin{bmatrix}
f(i) & f(i-1) & 1
\end{bmatrix}
=\begin{bmatrix}
f(i - 1) & f(i-2) & 1
\end{bmatrix} \times

\begin{bmatrix}
2&1&0\\
-1&0&0\\
2&0&1\\
\end{bmatrix}

$$

在脑袋中运行 Brain++ 语言，发现这个矩阵的 $k - 1$ 次方等于

$$
\begin{bmatrix}
f(k) & f(k-1) & 1
\end{bmatrix}

=
\begin{bmatrix}
f(1) & f(0) & 1
\end{bmatrix} \times


\begin{bmatrix}
k&1&0\\
-k+1&-k+2&0\\
k^2-k&k^2-3k+2&1\\
\end{bmatrix}

$$

其实有时候用矩阵打表找规律很方便。

---

代入最开始的等式

$$f(n-1)=(n-1)x-(n-1)(n-2) = f(1)=x$$

$$x = n - 1$$

$$f(i) = i (n-i)$$

于是我们就得到了这个优美的，没有分数的结论。

---

### 如何选择使得答案最优？

令 $ans(p)$ 为选 $p$ 做终点行时的答案。

$$ans(p) = \sum_{i=1}^n f(\left|p - i\right|)\times ai $$

拆开绝对值和 $f$ 得到

$$ans(p)=\sum_{i=1}^p i^2\times  a_i  +(2p-n)\sum_{i=1}^p i\times a_i +(pn -p^2)\sum_{i=1}^pa_i + \sum_{i=p+1}^n  i^2\times  a_i  +(2p+n)\sum_{i=p+1}^n  i\times a_i -(pn +p^2)\sum_{i=p+1}^n a_i $$



用 int128 维护 $a_i , a_i\times i,a_i\times i^2$ 的前缀和即可解决。


全部取 min 后再取模。



---

[code](https://www.luogu.com.cn/paste/j5oos237)


不是很理解考场上为啥做出来的人这么少。

~~虽然我并没有打~~



---

## 作者：do_while_true (赞：3)

2022.12 upd：原先代码锅了，重写了一份。

看上去是比较常规的题，应当需要更灵敏的直觉和更快的速度解决这道题。

首先考虑若已经确定一个 $x$，那么贪心修改策略就是随便找一个非 $0$ 的位置操作，因为早操作晚操作这个地方都要操作。

之后就考虑一个距离 $x$ 为 $i$ 有一个 $1$，那么这个 $1$ 对 $x$ 处的答案 $ans_x$ 的贡献系数是确定的，设其为 $E(i)$．

考虑解出这个 $E(i)$，其实际意义是有一个模 $n$ 意义下的变量 $x$，每次有 $\frac{1}{2}$ 的概率 $+1$ 或者 $-1$，求 $x$ 变为 $0$ 步数的期望。则可以列出方程 $E(i)=\frac{1}{2}(E(i-1)+E(i+1))+1$ 即 $E(i+1)=2E(i)-E(i-1)-2$，当然内部的 $i,i-1,i+1$ 都是模 $n$ 意义下的。

边界情况是 $E(0)=0$，采用主元法解这个方程，设 $E(1)=x$，则通过 $E(2)=2E(1)-E(0)-2$ 可得 $E(2)$ 是关于 $x$ 的一次多项式，类似地能继续往后解出 $E(n)$ 是关于 $x$ 的一次多项式，最终 $E(n)=E(0)=0$ 解出 $x$，再往回代入求出其他所有 $E$ 即可。

打表观察 $E(i)$，容易发现在前半部分 $E(i)$ 是关于 $i$ 的二次函数（具体地，$E(i)-E(i-1)=n-(2i-1)$），后半部分是对称的。这个时候可以发现题面中的取模实际上是假的，因为答案最大是 $\mathcal{O}(n^3a)$ 级别的，`__int128` 足够存下。

所以可以考虑计算出所有 $ans_x$，以一个 $a_y$ 考虑其对所有 $ans_x$ 的贡献，则为向左向右各一个区间二次函数加。利用三阶差分化为单点加即可。

时间复杂度线性。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
#define ll i128
using namespace std;
//typedef long long ll;
typedef __int128 i128;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
    r=0;bool w=0;char ch=getchar();
    while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
    while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
    return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=1004535809;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
    int s=1;
    while(y){
        if(y&1)s=1ll*s*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return s;
}
mt19937 rnd(time(NULL)^(ull)(new char));
inline int rd(int a,int b){
    return a+rnd()%(b-a+1);
}
#define Win do{puts("Yes");return ;}while(0)
#define Lose do{puts("No");return ;}while(0)
#define Alice do{puts("Alice");return ;}while(0)
#define Bob do{puts("Bob");return ;}while(0)
#define Fuyi do{puts("-1");return ;}while(0)
#define Line cerr << "----------\n"
char outc[201];
int outct;
void print(i128 x){
    do{
        outc[++outct]=x%10+'0';
        x/=10;
    }while(x);
    while(outct)putchar(outc[outct--]);
}
const int N=1000010;
int n;
ll f[N],w[N];
ll s[N*2];
void calc(int rev){
	for(int i=1;i<=2*n+3;i++)s[i]+=s[i-1];
	for(int i=1;i<=2*n+3;i++)s[i]+=s[i-1];
	for(int i=1;i<=2*n+3;i++)s[i]+=s[i-1];
	for(int i=1;i<=2*n+3;i++){
		int id=(i-1)%n+1;
		if(rev)id=n-id+1;
		f[id]+=s[i];
		s[i]=0;
	} 
}
signed main(){
    #ifdef do_while_true
//      assert(freopen("data.in","r",stdin));
//      assert(freopen("data.out","w",stdout));
    #endif
    read(n);
    for(int i=1;i<=n;i++)read(w[i]);
    if(n&1){
    	i128 sum=(ll)(n+1)*(n/2)/2;
    	for(int i=1;i<=n;i++){
    		s[i+1]+=(n-1)*w[i];
    		s[i+2]+=(-n-1)*w[i];
    		s[i+n/2+1]+=-sum*w[i];
    		s[i+n/2+2]+=(2*sum+2)*w[i];
    		s[i+n/2+3]+=-sum*w[i];
		}
		calc(0);
    	for(int i=1;i<=n;i++){
    		s[i+1]+=(n-1)*w[n-i+1];
    		s[i+2]+=(-n-1)*w[n-i+1];
    		s[i+n/2+1]+=-sum*w[n-i+1];
    		s[i+n/2+2]+=(2*sum+2)*w[n-i+1];
    		s[i+n/2+3]+=-sum*w[n-i+1];
		}
		calc(1);
	}
	else{
    	i128 sum=(ll)n*(n/2)/2;
    	for(int i=1;i<=n;i++){
    		s[i+1]+=(n-1)*w[i];
    		s[i+2]+=(-n-1)*w[i];
    		s[i+n/2+1]+=(-sum+1)*w[i];
    		s[i+n/2+2]+=(2*sum+1)*w[i];
    		s[i+n/2+3]+=-sum*w[i];
		}
		calc(0);
    	for(int i=1;i<=n;i++){
    		s[i+1]+=(n-1)*w[n-i+1];
    		s[i+2]+=(-n-1)*w[n-i+1];
    		s[i+n/2+1]+=(-sum+1)*w[n-i+1];
    		s[i+n/2+2]+=(2*sum+1)*w[n-i+1];
    		s[i+n/2+3]+=-sum*w[n-i+1];
		}
		calc(1);
		for(int i=1;i<=n;i++)f[(i+n/2-1)%n+1]-=w[i]*sum;
	}
    ll mx=f[1];
    for(int i=2;i<=n;i++)mx=min(mx,f[i]);
    print(mx%mod);
    #ifdef do_while_true
        cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
    #endif
    return 0;
}
```

---

## 作者：critnos (赞：3)

这个题目是数学题。因为出题人不会数学，所以题目很简单。

题目背景已经提示，操作顺序无关。所以考虑分别将每个 $1$ 移动到目标。

设 $f_i$ 为从点 $i$  移动到点 $1$ 期望操作次数。考虑求出这个。

可以列出方程：

$$f_1=0$$

$$f_i=1+\dfrac  1 2(f_{i-1}+f_{i+1})(i\in[2,n-1])$$

$$f_n=1+\dfrac  1 2(f_{1}+f_{n-1})$$

考察 $f$ 的一些性质。

$f$ 显然具有对称性，即 $f_i=f_{n-i+2}$。

设我们已经求出了 $f_{2\dots k},f_{n-k+2,n}$，考虑求出 $f_{k+1}$ 即 $f_{n-k+1}$。

有：

$$f_{k+1}=1+\dfrac  1 2(f_k+f_{k+2})$$

$$\dots$$

$$f_{n-k+1}=1+\dfrac  1 2(f_{n-k}+f_{n-k+2})$$

两边求和：

$$S=\sum_{i=k+1}^{n-k+1}  f_i$$

$$=n-2k+1+\dfrac 1 2( \sum_{i=k}^{n-k} f_i+\sum_{i=k+2}^{n-k+2} f_i)$$

$$=n-2k+1+\dfrac 1 2(S+f_k-f_{n-k+1}+S-f_{k+1}+f_{n-k+2})$$

$$=n-2k+1+S+f_k-f_{k+1}$$

所以有递推式 $f_{k+1}=f_k+n-2k+1$。

现在问题即将 $a$ 旋转，最小化 $\sum_{i=1}^n a_if_i$。

~~好了这里显然是个卷积形式，跑卷积就行了~~

~~然而虽然模数是 NTT 模数但是根本没用好吧~~

考虑旋转次数 $k$。

$$\sum_{i=1}^{n-k} a_i f_{i+k}+\sum_{i=n-k+1}^na_if_{k-n+i}$$

$k\to k+1$：

$$\sum_{i=1}^{n-k-1} a_i f_{i+k+1}+\sum_{i=n-k}^na_if_{k-n+i+1}$$

增量为：

$$\sum_{i=1}^{n-k-1} a_i (n-2(i+k)+1)+\sum_{i=n-k+1}^na_i(n-2(k-n+i)+1)-a_{n-k}(n-1)$$

拆开后容易维护。时间复杂度线性。

---

## 作者：enucai (赞：1)

## Analysis

根据期望的线性性，我们在钦定最后一个不为 $0$ 的元素后，题目需要计算的步数等于每个 $1$ 移到目标位置的期望步数之和。

考虑计算这个期望步数，假设目标位置是 $1$，由 $i$ 号位置转移到目标位置的期望步数是 $f_i$。可以列出转移方程如下：

$$
\begin{cases}
f_1=0\\
f_{i}=\frac{1}{2}(f_{i-1}+f_{i+1})+1\ (2\le i<n)\\
f_n=\frac{1}{2}f_{n-1}+1
\end{cases}
$$

我们可以高斯消元 $O(n^3)$ 求出每个 $f_i$ 的值，不难发现规律：

$$
f_i=(i-1)\cdot (n-i+1)
$$

这样就不用高斯消元了，可以直接求出。

另一种方法是发现这个矩阵是一个三对角矩阵，于是可以 $O(n)$ 求出所有的 $f_i$，具体可以参考 [CF24D Broken robot](https://www.luogu.com.cn/problem/CF24D)。

知道 $f_i$ 后，我们可以枚举最终不为 $0$ 的点，设为 $i$，然后列出答案的式子：

$$
\sum_{j=1}^{i-1}(i-j)\cdot(n-i+j)\cdot a_j+\sum_{j=i+1}^n(j-i)\cdot(n-j+i)\cdot a_j
$$

然后把括号拆开，发现只与所有 $a_j$，$a_j\cdot j$ 与 $a_j\cdot j^2$ 有关。于是预处理这三个东西的前后缀和即可。

另一个 trick 是，期望一定是整数，总的期望上限是 $O(Vn^2)$，所以直接用 `__int128` 存储即可。

## Code

```cpp
#define int long long
using i128=__int128;
const int N=1000010;
const i128 mod=1004535809;
int n,b[N];
i128 a[N],p0[N],p1[N],p2[N],s0[N],s1[N],s2[N];
signed main(){
  cin>>n;
  rep(i,1,n) cin>>b[i],a[i]=(i128)b[i];
  rep(i,1,n){
    p0[i]=p0[i-1]+a[i];
    p1[i]=p1[i-1]+a[i]*i;
    p2[i]=p2[i-1]+a[i]*i*i;
  }
  per(i,n,1){
    s0[i]=s0[i+1]+a[i];
    s1[i]=s1[i+1]+a[i]*i;
    s2[i]=s2[i+1]+a[i]*i*i;
  }
  i128 ans=(i128)3e38;
  rep(i,1,n){
    i128 pre=p0[i-1]*(n*i-i*i)+p1[i-1]*(2*i-n)-p2[i-1];
    i128 suf=-s0[i+1]*(n*i+i*i)+s1[i+1]*(2*i+n)-s2[i+1];
    ans=min(ans,pre+suf);
  }
  cout<<(int)(ans%mod);
}
```

---

## 作者：BobL (赞：0)

# P8850 题解
想了一节语文课（对不起语文老师），终于推出来了！
感觉自己解法不太一样？

upd:noip考完退役了


------------


显然，如果我们确定了起点 $x$ 的位置，就能线性算答案。我们考虑环上离起点距离为 $i$ 的点中，转移权值 $1$ 到起点的期望（注意这里  $i$ 的定义有变化），不妨设其为 $E_i$ ，考虑对其他期望的贡献及环本身的对称性，则有：

$$E_0 = 0$$

$$E_i = E_{n-i}$$

$$2E_i = E_{i-1}+E_{i+1} + 2$$

转换一下：

$$E_{i+1}-E_i =  E_i - E_{i-1}-2  $$ 

发现这是一个等差数列，对前 $n-1$ 项求和，可以由上述式子得到:

$$E_1 = n-1$$

对前 $i-1$ 项做前缀和，可以得到：

$$E_i = (n-i) i$$

这样我们就可以得到每个 $1$ 转移到起点的期望了。暴力的话就是枚举每个起点算答案。

考虑优化，发现这是个二次函数，其相邻整点函数值的差的差分为定值  $2$ 或 $-2$，而在本题中，令起点从左向右移一个单位，除起点外的所有点在函数上左移一个单位（相当于向右移动起点每个点离起点的距离 $-1$ ），原起点加到所有点最后，那么除原起点以外的点的期望值的增量必为 $-2$ .

单独考虑前起点$i$，其期望值增量由最后的 $-(n-1)$ ，变为 $(n-1)$ ，增量为 $2n-2$（以上皆为权值$1$的增量，计算时只需乘上对应的 $a_i$ ）。

这样就可以方便的维护增量。考虑移动起点，则起点从$i$到$i+1$增量的变化量为:

$$2na_i-2\sum_{j=1}^{j\leq n} a_{j}$$

初始增量为:

$$(n-1)a_1-\sum_{j=2}^{j\leq n} a_{j}(E_{j-1}-E_{j-2})$$

后者是朴素的前缀和，每个点的增量可以常数级别维护，于是做完了。唯一要注意的是数据范围会爆 long long。代码如下:
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
long long a[1000005];
__int128 ans=1e36,sum,add,p = 1004535809,b[1000005],E[1000005];
//sum表示现在的答案，add表示增量
int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%lld",&a[i]);
        b[i]=b[i-1]+a[i];//可以直接用一个变量维护，懒得改了
        E[i-1] = (__int128)1ll*(n+1-i)*(i-1);/计算初始期望
        sum+=E[i-1]*(__int128)a[i];//计算初始答案
        if(i>1)add+=(E[i-2]-E[i-1])*(__int128)a[i];//维护初始增量
	}
    add+=(n-1)*a[1];
    ans=sum;
    for(int i = 2;i <=n;i++){
        sum+=add;
        add-=b[n]*2;
        add+=2*n*a[i];//根据上述式子计算新的增量
        ans=min(ans,sum);
    }
    cout << (long long)(ans%(__int128)1004535809);
	return 0;
}
```




---

