# Timber

## 题目描述

There is a beautiful alley with trees in front of a shopping mall. Unfortunately, it has to go to make space for the parking lot.

The trees on the alley all grow in a single line. There are $ n $ spots for trees, index $ 0 $ is the shopping mall, index $ n+1 $ is the road and indices from $ 1 $ to $ n $ are the spots for trees. Some of them are taken — there grow trees of the same height $ k $ . No more than one tree grows in each spot.

When you chop down a tree in the spot $ x $ , you can make it fall either left or right. If it falls to the left, it takes up spots from $ x-k $ to $ x $ , inclusive. If it falls to the right, it takes up spots from $ x $ to $ x+k $ , inclusive.

Let $ m $ trees on the alley grow in some spots $ x_1, x_2, \dots, x_m $ . Let an alley be called unfortunate if all $ m $ trees can be chopped down in such a way that:

- no tree falls on the shopping mall or the road;
- each spot is taken up by no more than one fallen tree.

Calculate the number of different unfortunate alleys with $ m $ trees of height $ k $ . Two alleys are considered different if there is a spot $ y $ such that a tree grows in $ y $ on the first alley and doesn't grow in $ y $ on the second alley.

Output the number modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
6 1 4```

### 输出

```
4```

## 样例 #2

### 输入

```
5 2 2```

### 输出

```
0```

## 样例 #3

### 输入

```
6 2 2```

### 输出

```
4```

## 样例 #4

### 输入

```
15 3 2```

### 输出

```
311```

# 题解

## 作者：Gypsophila (赞：16)

## 解法1：

对于一个状态考虑贪心，能往左就往左倒，否则往右倒。
设 $f_{i,j}$ 表示考虑了前 $i$ 颗树最后倒在 $j$ 的方案数。

考虑往一个位置 $j$ 后面加一颗新的树转移：

- $2 f_{i,j} \to f_{i+1,l}$ 当 $l\in{[j+k+1,j+2k]}$
- $f_{i,j} \to f_{i+1,l}$ 当 $l\in{[j+2k+1,\inf]}$ 

写成生成函数的形式后，答案可以表示为 $\sum\limits_{t=0}^{n}([x^t](\sum\limits_{i=k+1}^{2k}2x^i+\sum\limits_{i=2k+1}^{\inf} x^i)^m$)。

直接使用多项式快速幂可以做到 $O(n \log n)$ 的时间复杂度。

考虑继续推导：
$$
\begin{aligned}
[x^t](\sum\limits_{i=k+1}^{2k}2x^i+\sum\limits_{i=2k+1}^{\inf} x^i)^m 
&=[x^{t-m(k+1)}](\sum\limits_{i=0}^{k-1}2x^i+\sum\limits_{i=k}^{\inf} x^i)^m \\
&=[x^{t-m(k+1)}](\frac{2-x^k}{1-x})^m
\end{aligned} 
$$

设：

- $f(t)=[x^{tk}](2-x^k)^m=(-1)^t2^{m-t}\binom{m}{t}$

- $g(t)=[x^t](\frac{1}{1-x})^{m}=\binom{t+m-1}{m-1}$

设 $h(n)=\sum\limits_{i=0}^{n} g(i)$，那么答案为 $\sum\limits_{ki+j\leq n-m(k+1)}f(i)g(j)=\sum\limits_{0 \leq i \leq m} f(i) h(n-m(k+1)-ki)$。代入计算即可。时间复杂度 $O(n)$。

## 解法2：

我们考虑设 $p_i$ 为考虑前 $i$ 颗树都倒下后最后一个位置（也就是 $dp$ 中的转移点）。那么根据上述 $dp$ 转移，对于任意的 $i$，都有 $p_i-p_{i-1} \ge k+1$ 。并且如果同时满足 $p_i-p_{i-1} \leq 2k$，那么会对答案造成一个 $2$ 的贡献。

考虑把前 $m$ 段中都去掉必须有的 $k+1$ 个位置，那么我们把问题转化为：在一个长度为 $n-m(k+1)$ 序列里放 $m$ 个不降的 $p_i$ 并将序列划分成 $m+1$ 个区间 $(p_{i-1},p_i](1\leq i \leq m+1,0=p_0\leq p_1 \cdots \leq p_{m+1}=n)$。

在前 $m$ 个区间中（不算第 $m+1$ 个区间），每当有一个长度 $\leq k-1$ 的区间，贡献就会乘以 $2$。我们要求出所有方案的贡献之和。

设 $f_x$ 表示前 $m$ 个区间中恰好有 $x$ 个区间长度 $\ge k$，$g_x$ 表示钦定其中 $x$ 个区间长度 $\ge k$。

我们可以得到：
- $g_x=\binom{m}{x}\binom{n-m(k+1)-xk+m}{m}$ 
- $g_x=\sum\limits_{i=x}^{m} \binom{i}{x}f_i$
- 答案为 $\sum\limits_{i=0}^{m} 2^{m-i} f_i$

由二项式反演可以得到 $f_x=\sum\limits_{i=x}^{m} (-1)^{i-x}\binom{i}{x} g_i $。

于是有：
$$
\begin{aligned}
\sum\limits_{i=0}^{m} 2^{m-i} f_i
&= \sum\limits_{i=0}^{m} 2^{m-i} \sum\limits_{j=i}^{m} (-1)^{j-i} \binom{j}{i} g_j \\
&= \sum\limits_{j=0}^{m} g_j \sum\limits_{i=0}^{j} 2^{m-i} (-1)^{j-i} \binom{j}{i} \\ 
&= \sum\limits_{j=0}^{m} g_j 2^m (-\frac{1}{2})^j
\\ 
&= \sum\limits_{j=0}^{m} \binom{m}{j} \binom{n-m(k+1)-jk+m}{m}2^{m-j} (-1)^j
\end{aligned}
$$

直接 $O(n)$ 计算即可。

## 解法3：

事实上，这个 $dp$ 有另一种转移方式：考虑一个一个位置的枚举：
- $f_{i,j-1} \to f_{i,j}$ 表示当前位置是空； 
- $(2f_{i-1,j-(k+1)}-f_{i-1,j-(2k+1)}) \to f_{i,j}$ 表示当前 $[i-k,i]$ 被覆盖了一颗新树，如果当前树初始在位置 $i-k$ 我们还需要容斥掉 $i-k$ 可以往前倒的情况。

此时我们可以考虑这个 $dp$ 的组合意义，相当于最初在 $(0,0)$，我们要走到 $(m,n)$，每次可以选择加上向量 $(0,1)$，贡献为 $1$；选择 $(1,k+1)$，贡献为 $2$；选择 $(1,2k+1)$，贡献为 $-1$。

可以发现，第二种转移和第三种转移的总数为 $m$，我们直接枚举走了 $t$ 个第三种转移，可以计算出此时有 $m-t$ 个第二种转移以及 $n-(m-t)(k+1)-t(2k+1)$ 个第一种转移。

将第二和第三种转移排列好有 $\binom{m}{t}$ 种方案，使用插板法计算出把第一种转移插入到第二三种转移的空隙中的方案数，最后可以得到答案为：

$$
\sum\limits_{t=0}^{m} 2^{m-t}(-1)^{t} \binom{m}{t}\binom{n-(m-t)(k+1)-t(2k+1)+m}{m}
$$

可以发现三种做法殊途同归，同样 $O(n)$ 计算即可。

代码：https://www.luogu.com.cn/paste/8vgbd3uy



---

## 作者：Eznibuil (赞：11)

简单容斥板题被评 2600，怎么会是呢？

考虑倒下后的形态。容易得知答案是 $\binom{n-mk}m$。

每棵树有两种倒法，所以是 $2^m\binom{n-mk}m$。

然而显而易见会算重，考虑容斥。首先是一棵树可以两侧倒的情况，应该是 $2^{m-1}\binom m1\binom{n-(m+1)k}m$。为什么？首先两侧都倒下的树（呃，假装它同时倒向两侧并占据 $2k+1$ 个点）不要需要倒下的方向，而还需要在 $m$ 棵中选一棵两边倒。

然后就是两棵树两边倒，是 $2^{m-2}\binom m2\binom{n-(m+2)k}m$。依此类推。

容斥系数呢？其实稍作观察发现这和用集合交算集合并的容斥结构一样，因此容斥系数是 $(-1)^i$（或者也可以理解为二项式反演）。

于是就有最后的柿子：
$$\sum_{i=0}^{\mathclap{\lfloor\frac{n-m}k\rfloor-m}}(-1)^i2^{m-i}\binom mi\binom{n-(m+i)k}m$$
```cpp
#include<stdio.h>
typedef long long ll;
const ll mod=998244353;
ll fac[1000001],inf[1000001],ans;
ll Inv(ll a)
{
	ll s=1,b=mod-2;
	for(a%=mod;b;a=a*a%mod,b>>=1)
		if(b&1)
			s=s*a%mod;
	return s;
}
ll C(ll n,ll k){return fac[n]*inf[k]%mod*inf[n-k]%mod;}
int main()
{
	fac[0]=inf[0]=1;
	for(int i=1;i<1000001;i++)
		fac[i]=fac[i-1]*i%mod;
	inf[1000000]=Inv(fac[1000000]);
	for(int i=1000000;i>1;i--)
		inf[i-1]=inf[i]*i%mod;
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(ll i=m,j=(m&1?-1:1);~i;i--,j=j*-2%mod)
		if(n-(i+m)*k>=m)
			ans=(ans+j*C(m,i)%mod*C(n-(i+m)*k,m))%mod;
	printf("%lld",(ans+mod)%mod);
	return 0;
}
```

---

## 作者：Reanap (赞：5)

首先考虑如何判断是否合法，容易发现，从左往右考虑，能往左边倒就往左边倒。

能全部倒掉就赢了。

有一个最最暴力的想法是定义 $f_{i,j}$ 表示最靠右的一个被占据的位置是 $j$ ，并且决策了 $i$ 棵树的方案数。转移是平凡的，很容易就可以写出从 $f_{i} \rightarrow f_{i+1}$ 的转移式。

发现这个转移是规整的，转移可以用生成函数来描述，每一次转移等价于乘上了：
$$
2 (x^{k+1} + x^{k+2} + \dots + x^{2k+1}) + x^{2k+2} + x^{2k+3} + \dots
$$
改写成封闭形式，则可以得到：
$$
\frac{x^{k+1}(2 - x^k)}{1-x}
$$
于是由初始状态 $f_{0,0} = 1$ 得到答案：
$$
f_n = \frac{x^{mk + m}(2 - x^k)^m}{(1-x)^m}
$$
我们再改写一步：
$$
f_n = x^{mk + m}(2 - x^k)^m\frac{1}{(1-x)^m}
$$
于是，我们可以枚举 $(2 - x^k)^m$ 贡献的项的次数。

在计算中，我们可能会用到这样的一个变换：
$$
\sum_{q=0}^p [x^q] \frac{1}{(1-x)^m} = [x^p]\frac{1}{(1-x)^{m+1}} = \binom{p + n}{m}
$$
因为 $\frac{1}{1-x}$ 的组合意义是滚一次前缀和，然后就做完了。

---

## 作者：BreakPlus (赞：3)

脑瘫推柿子推了 1h。基础不牢，地动山摇（doge

这次尝试一下先放 Hint 再放 Sol 的形式。

---

**先令 $k$ 为 $k+1$**，因为原题可以理解为覆盖 $k+1$ 个点。

# Hint 1

考虑给你每棵树的位置，怎么贪心地让树倒下去。

# Hint 2

考虑倒下去的形态，共 $n$ 个点被覆盖了 $m$ 段长度为 $k$ 的区间。每个区间会有向左和向右两种情况。另外要符合 Hint1 的倒下去的方式。

# Hint 3


解决这样一个问题：非负整数 $x_1,x_2,...,x_n$，满足 $\sum x = m$，其中有 $k$ 个 $i$ 要满足 $x_i \ge T$。


# Sol 1

将树按横坐标排序，从左到右依次考虑：能往左倒往左倒，否则向右。

# Sol 2

不难发现如果这个区间是向右倒的，那么它和上一个区间的间隙最多有 $k$ 个点。

我们把一个区间“绑”在一起，相当于先确定了 $m$ 个区间，然后把剩余的 $n-mk$ 个点插进 $m+1$ 个空隙里。

不难发现一个向右倒的区间与前一个区间之间的间隙小于 $k-1$ 个点。问题转化为 Hint 3。

# Sol 3

大力容斥即可。

# Final Solution

结合 Sol 2 和 Sol 3 可得（$i$ 是向右倒的数量，$j$ 是容斥过程）

$$ \sum \limits_{i=0}^m {m \choose i}\sum \limits_{j=0}^i (-1)^j{i \choose j}{n-mk-j(k-1) \choose m}$$

我们发现 ${m \choose i}{i \choose j}={m \choose j}{m-j \choose i-j}$，可以变化求和顺序，把 $j$ 提上来。

$$\sum \limits_{i=0}^m \sum \limits_{j=0}^i (-1)^j{m \choose j}{m-j \choose i-j}{n-mk-j(k-1) \choose m}$$

$$ \sum \limits_{j=0}^m (-1)^j{m \choose j}{n-mk-j(k-1) \choose m}\sum \limits_{i=j}^m {m-j \choose i-j}$$

后面那坨明显是 $2^{m-j}$。

$$ \sum \limits_{j=0}^m (-1)^j{m \choose j}{n-mk-j(k-1) \choose m}2^{m-j}$$


硬算就完了。

```cpp
ll n,m,k;
void solve2(){
	n=read(), m=read(), k=read()+1;
	ll ans = 0;
	for(ll j=0;j<=m;j++){
		ll w1 = comb.C(m,j) * comb.C(n-m*k-j*(k-1)+m,m) % mod * ((j&1)? mod-1: 1) % mod;
		ans = (ans + w1 * qpow(2, m-j))% mod;
	}
	printf("%lld\n", ans);
}
```

---

## 作者：_SeeleVollerei_ (赞：3)

很适合做 GF 的入门题。

考虑怎么判断一个条件合法，从左往右扫一遍，能往左倒就往左倒即可。

按照这个东西可以设计 dp 状态，设 $f_{i,j}$ 表示前 $i$ 棵树在最优方案下铺到位置 $j$ 的方案数。

考虑转移，分别考虑什么情况往左倒，什么情况从左边往右倒过来即可，有 $f_{i,j}=\sum_{l=0}^{j-k-1}f_{i-1,l}+\sum_{l=j-2k}^{j-k-1}f_{i-1,l}$。

因为每个 $f_i$ 都是从 $f_{i-1}$ 转移，且形式都很优美，考虑 GF。

令 $F_i(x)=\sum_{i\ge 0}f_{i,j}x^j$，则所求为 $F_m(x)$ 每一项的系数和，分别考虑两个转移对应的多项式。

左边是 $A(x)=\sum_{i\ge k+1}x^i=\frac{x^{k+1}}{1-x}$，右边为 $B(x)=\sum_{i=k+1}^{2k}x^i=\frac{2^{k+1}-x^{2k+1}}{1-x}$。

因为 $F_0(x)=1$，所以有 $F_m(x)=(A(x)+B(x))^m=\frac{(2x^{k+1}-x^{2k+1})^m}{(1-x)^m}$。

拆成两个多项式乘起来后，分子可以二项式展开，分母是典中典，那么两个多项式都可以 $O(n)$ 求出。

因为我们不需要知道 $F_m(x)$ 的每一项是多少，只需要知道每一项的和，所以这个也是可以 $O(n)$ 求出的。

总复杂度 $O(n)$。

https://codeforces.com/contest/1821/submission/202915394

---

## 作者：daniEl_lElE (赞：2)

考虑先选出 $m$ 个长度为 $k+1$ 的段作为树倒下的地方。每种倒下方法可以选开头和结尾，理应有 $2^m$ 个位置可以放树。然而，不难发现如果两段之间距离大于等于 $k$ 时后一段选择起点及前面 $k$ 个点会有重复计算。考虑当且仅当两段之间距离小于 $k$ 时后一段乘 $2$，否则乘 $1$（只计算最右端的点向前面倒）。

不难发现我们要求的就是对于每个 $i$，有 $i$ 段距离大于等于 $k$ 的方案数，记为 $f_i$。很难计算，考虑容斥，钦定某 $i$ 段距离大于等于 $k$ 的方案数，记为 $g_i$。$g_i$ 是容易计算的，易知为 $\binom{n-m\times k-i\times k}{m}\times\binom{m}{i}$。不难发现对 $g$ 做二项式反演即可得到 $f_i$。$n\log n$ 多项式处理即可。

问题不大，我不会多项式。

考虑用 $g_i$ 表示 $f_i$：$f_i=\sum_{j=i}^mg_j(-1)^{j-i}\binom{i}{j}$。

考虑用 $f_i$ 表示答案：$ans=\sum_{i=0}^mf_i2^{m-i}$。

考虑用 $g_i$ 表示答案：$ans=\sum_{i=0}^m(\sum_{j=i}^mg_j(-1)^{j-i}\binom{j}{i})2^{m-i}$。

交换顺序：$ans=\sum_{j=0}^mg_j2^{m-j}(\sum_{i=0}^j(-1)^{j-i}2^{j-i}\binom{j}{i})$。

将后面改成二项式展开形式：$ans=\sum_{j=0}^mg_j2^{m-j}(-1)^j(\sum_{i=0}^j(-1)^{i}2^{j-i}\binom{j}{i})$。

将二项式展开形式变成二项式幂形式：$ans=\sum_{j=0}^mg_j2^{m-j}(-1)^j(-1+2)^j$。

最终得到：$ans=\sum_{i=0}^m\binom{n-m\times k-i\times k}{m}\binom{m}{i}2^{m-i}(-1)^i$。

---

## 作者：xiezheyuan (赞：1)

## 简要题意

你需要在数轴上的区间 $[1,n]$ 放 $m$ 棵高度为 $k$ 的树，使得你可以为每一个树钦定一个倾倒方向（左或右），使得所有树均倾倒后，每个数轴上的点至多被一个树覆盖，且不在区间 $[1,n]$ 的点不会被树覆盖。

求方案数，答案对 $998,244,353$ 取模。

$1\leq n,m,k\leq 3\times 10^5$。

## 思路

考虑到我们本质上相当于将数轴分成 $m$ 段，钦定每一段的后缀被树覆盖，其余部分未被树覆盖。求方案数。

对于一个大小 $\leq k$ 的段，显然是没有方案的。但是对于其余的段可能很复杂，可能会算重。由于方案之和我们选择的树的位置有关，所以不妨假设每个树尽量往左倒。则对于大小 $\geq 2k+1$ 的段，只能让树放在段的末尾，然后钦定往左倒。至于介于 $[k+1,2k]$ 的段，可以在中间往右倒（左侧空间不够），也可以在末尾往左倒，有两种方案。

于是可以列出生成函数：

$$
\begin{aligned}
&\left(\sum_{j=k+1}^{2k}2z^j+\sum_{j\geq 2k+1} z^j\right)^m\\
&=\left(2z^{k+1}\frac{1-z^{k}}{1-z}+\frac{z^{2k+1}}{1-z}\right)^m\\
&=\left(z^{k+1}\frac{2-z^k}{1-z}\right)^m
\end{aligned}
$$

所以其实我们就是要求：

$$
\left(z^{k+1}\frac{2-z^{k}}{1-z}\right)^{m}
$$

多项式乘法（这个 $1-z$ 可以手算逆） & 多项式求 $\ln$ & 多项式求 $\exp$ 应该可以做到 $O(n\log n)$，不过常数过大。

稍微整理一下：

$$
z^{(k+1)m}\left(\frac{2-z^{k}}{1-z}\right)^{m}
$$

考虑分子分母。

对于分子，有：

$$
(2-z^{k})^m=\sum_{i\geq 0}\binom{m}{i}(-1)^{i}z^{ik}2^{m-i}
$$

对于分母，有：

$$
(1-z)^{-m}=\sum_{i\geq 0}\binom{-m}{i}(-1)^{i}z^{i}=\sum_{i\geq 0}\binom{m+i-1}{i}z^i
$$

由于我们只需要取上两式卷积取一个区间的次数，直接对一个多项式的系数取前缀和，然后暴力卷积求一项即可。时间复杂度 $O(n)$。

[Submission](https://codeforces.com/contest/1821/submission/307413950)。

PS：请注意数组大小和一些 corner case，否则可能会收到 RE 大礼包：

![](https://cdn.luogu.com.cn/upload/image_hosting/tv9bz9tv.png)

---

## 作者：Mars_Dingdang (赞：1)

推式子题。

## 题目大意
在 $[1, n]$ 的区间里放 $m$ 棵树，每棵树的高度为 $k$。求有多少种放置树的方法，满足：

1. 每个树都在整点上，且每个点最多只能放一棵树。
2. 存在一种砍倒树的方案，使得树倒了之后不会越界，也不会有某个点被超过一棵树占据。你可以自由选择树向左倒（也就是占据区间 $[x - k, x]$）或者向右倒（也就是占据区间 $[x, x + k]$）。

$1\leq n, m, k\leq 3\times 10 ^ 5$。答案取模 $998244353$。

## 大体思路
很显然，我们考虑将所有树砍到之后的状态。这相当于有 $m$ 条长度为 $k+1$ 的线段（指覆盖 $k+1$ 个整点）要放置在长度为 $n$ 个整点的数轴上。

因此，我们得到的空位数 $s=n-m(k+1)$，而这 $s$ 个空位要插入 $m$ 条线段形成的 $m+1$ 个空隙中。

根据组合数学知识，$n$ 个元素可重复地选出 $r$ 个的方案数为 $\binom {n+r-1}{r}$，故此时放置线段的方案数为

$$\binom{m+1+s-1}{s}=\binom{n-mk}{n-mk-m}=\binom{n-mk}{m}$$

然后考虑将树竖起来，可以往左竖或者往右树，方案数为

$$2^m\binom{n-mk}{m}$$

然而，根据题目难度评分，很显然这是错的。观察样例 $4$ 便可以发现答案 $311$ 根本不是 $2$ 的幂。

其原因在于，考虑一棵树往左倒和往右倒，对应两种线段放置的方案，如果这两种方案均合法，那么种树的方案会被重复计算一次。所以我们使用容斥，考虑有 $i$ 棵树满足这种条件，即往左倒和往右倒均合法，那么这棵树倒下需要预留的线段长度就是 $2k+1$。因此，此时 $s(i)=n-(m-i)(k+1)-i(2k+1)=n-m(k+1)-ik$。带入原式可得此时方案数为

$$2^{m-i}\binom m i\binom{n-(m+i)k}{m}$$

其容斥的贡献系数为 $(-1)^i$，乘起来求和即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 3e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
const ll mod = 998244353;
inline ll Pow(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res % mod;
}
ll n, m, k, fac[maxn], inv[maxn];
inline void init(int N) {
	fac[0] = fac[1] = inv[0] = inv[1] = 1;
	rep(i, 2, N) fac[i] = 1ll * i * fac[i - 1] % mod;
	inv[N] = Pow(fac[N], mod - 2);
	Rep(i, N - 1, 1) inv[i] = 1ll * (i + 1) * inv[i + 1] % mod;
}
inline ll C(ll n, ll m) {
	if(m > n || m < 0) return 0;
	if(m == 0 || m == n) return 1;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int main () {
	read(n); read(m); read(k);
	init(300000);
	ll res = 0;
	rep(i, 0, m) {
		ll dlt = Pow(2, m - i) * C(m, i) % mod * C(n - (m + i) * 1ll * k, m) % mod;
		(res += (i & 1 ? -1 : 1) * dlt) %= mod;
	}
	writeln((res % mod + mod) % mod);
	
	return 0;
}
```

## 后记
CSP-S2023 考完了，笔者大概获得 300+ 的分数，然而 T4 在场上来不及思考。做题的时候希望大家都不会陷入思维盲区而卡住，比如本题想不到重复情况。

---

## 作者：xiaoliebao1115 (赞：0)

有几篇题解最后一步说的不是很严谨啊，这边写一下严谨的过程。

一棵树相当于占据一个 $k+1$ 的长条，剩下 $n-(k+1)\times m$ 个空位，把这些空位插到长条当中去，根据插板法方案数是 $C(n-mk,m)$，每棵树有两种倒法，所以是乘上 $2^{m}$。

但是这样会算重复，考虑对于实际树的位置如果一棵树既可以往左倒也可以往右，那么他会被长条在左边右边各算到一次，这个是不对的。

令 $a_i$ 表示 $i$ 随便选这个限制，$b_i$ 表示 $i$ 左右都可以倒下这个限制，$a_i-b_i$ 就是你实际的限制，因为 $b$ 的在 $a$ 中被算到了两次减掉一次。

那么我们要求的答案就是 $\prod(a_i-b_i)$，乘起来就表示同时满足这些限制，展开这个东西的话就可以很好的计数了，拆开来的多项式枚举其中有几个 $-b_i$ 假设是 $j$ 个，那么答案就是 $2^{m-j}\times C(n-(m+j)k,m)$，这个就是因为剩下的其他 $m-j$ 个随便选，两边都可以倒下的增加 $k$ 的占地面积，在原本的式子上增加 $kj$。有 $C(m,j)$ 个这样的集合，容斥系数取决于选了多少个 $-b_i$ 所以是 $(-1)^j$，答案就是 $\sum 2^{m-j}\times C(n-(m+j)k,m)\times C(m,j)\times (-1)^j$。

---

## 作者：Tx_Lcy (赞：0)

属于是和题比谁更唐了。

多项式快速幂贺了半天卡不过去，最后发现直接来就是线性的，what can i say？

## 思路

考虑一个双射，让放树的方案和字典序最小的砍树方案（能向左倒就向左倒）双射。

然后射回来，考虑先放若干个区间，然后决策占据这些区间的树放在左端点还是右端点。

显然一棵树放在右端点一定是合法的，如果放在左端点合法那一定要满足这棵树不能向左倒，也就是这个区间跟上一个区间的距离 $\le k$。

然后直接容斥，钦定一些树放的是不合法的，组合数算一下贡献就好了。

## 代码

我这里好像写的是 $\Theta(n \log n)$ 的，不过容易优化成线性。

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
int const N=3e5+10,mod=998244353;
int n,m,k,fac[N],inv[N];
inline int qpow(int a,int b){int res=1;while (b){if (b&1) res*=a,res%=mod;a*=a,a%=mod,b>>=1;}return res;}
inline int C(int n,int m){if (n<m || m<0) return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
inline void solve(){
	cin>>n>>m>>k,++k;
	if (m*k>n) return cout<<"0\n",void();
	int tot=qpow(2,m)*C(n-m*(k-1),m)%mod;
	rep(i,1,m){
		int an=qpow(2,m-i)*C(n-m*(k-1)-i*(k-1),m)%mod*C(m,i)%mod;
		if (i&1) tot+=mod-an,tot%=mod;
		else tot+=an,tot%=mod;
	}
	cout<<tot<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	fac[0]=1;
	rep(i,1,N-1) fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	per(i,N-2,0) inv[i]=inv[i+1]*(i+1)%mod;
	int t=1;
	// cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

无脑 $\rm GF$ 保平安。

设 $dp_{i,j}$ 表示前 $i$ 棵树，且第 $i$ 棵树倒下的位置最小能是 $j$ 的方案数。

当下一棵树放在 $[j+1,j+k]$ 之间时，树只能往右倒，也即转移到 $[j+k+1,j+2k]$；

当下一棵树放在 $[j+k+1,n]$ 之间时，我们选择往左倒，也就是转移到 $[j+k+1,+ \infty)$。

相当于乘二倍贡献到 $[j+k+1,j+2k]$，以及直接贡献倒 $[j+2k+1,+ \infty)$。

求出 $dp_{i,*}$ 的生成函数 $\mathcal F_i$，则

$$
\mathcal F_{i+1} = \mathcal F_i (\sum_{i=k+1}^{2k} x^i + \sum_{i=k+1}^{+ \infty} x^i)  = x^{k+1}F_i(\dfrac{2-x^k}{1-x})
$$

而 $\mathcal F_0=1$，得

$$
\mathcal F_m = x^{m(k+1)}(\dfrac{2-x^k}{1-x})^m 
$$

只要最后一棵树倒下的位置 $\le n$ 即可。

那么 $(\dfrac{2-x^k}{1-x})^m$ 每一项分别是多少？

$[x^t](\dfrac{1}{1-x})^m = \dbinom{t+m-1}{m-1}$，$[x^{tk}](2-x^k)^m = (-1)^t 2^{m-t} \dbinom{m}{t}$。

那么枚举后者的次数，前者预处理关于 $t$ 的前缀和即可。

-----

花絮：我尝试使用最朴素的二项式反演 + 二阶线性递推，得到了一个需要巨大多多项式开根的复杂做法，显然没有去实现。。。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10,MOD=998244353;
int n,m,k,u=1000000,frac[MAXN],inv[MAXN],pre[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;	
	}
	return ans;
}
int C(int u,int d) {
	if(u<0||u>d) return 0;
	return frac[d]*inv[u]%MOD*inv[d-u]%MOD;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	frac[0]=1;
	ffor(i,1,u) frac[i]=frac[i-1]*i%MOD;
	inv[u]=qpow(frac[u],MOD-2);
	roff(i,u-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	cin>>n>>m>>k;
	ffor(t,0,n) pre[t]=C(m-1,t+m-1);	
	ffor(t,1,n) pre[t]=(pre[t-1]+pre[t])%MOD;
	int pw=((m&1)?1:-1)*(MOD+1)/2,ans=0;
	roff(t,m,0) {
		pw=-2*pw%MOD;
		if(t*k+m*(k+1)<=n) ans=(ans+pw*C(t,m)%MOD*pre[n-(t*k+m*(k+1))])%MOD;
	}
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：hcywoi (赞：0)

## 题意

- 在 $[1, n]$ 的区间里放 $m$ 棵树，每棵树的高度为 $k$。求有多少种放置树的方法，满足：

	- 每个树都在整点上，且每个点最多只能放一棵树。

	- 存在一种砍倒树的方案，使得树倒了之后不会越界，也不会有某个点被超过一棵树占据。你可以自由选择树向左倒（也就是占据区间 $[x-k, x]$）或者向右倒（也就是占据区间 $[x,x+k]$）。

- 答案对 $998244353$ 取模。

- $1\le n, m, k\le 3\times 10^5$。

### 题解

对于一种方案，贪心地能往左倒就往左倒，否则往右倒，如果存在一种能砍倒树的方案，则这种方案合法。

考虑 dp，设 $f_{i,j}$ 表示当前考虑到第 $i$ 棵树，且目前最靠右的被占据的位置为 $j$。

对于每个 $f_{i, j}$，其贡献到的状态为：

$$2f_{i, j}\to f_{i+1, k}(\forall k\in [j+k+1, j+2k])$$
$$f_{i, j}\to f_{i+1, k}(\forall k\in [j+2k+1, \infty])$$

考虑用生成函数来转移，记
$$F_i(x)=\sum_{j\ge 0}f_{i, j}x^j$$

则，
$$F_{i+1}(x)=F_i(x)\frac{2x^{k+1}-x^{2k+1}}{1-x}=F_i(x)\frac{x^{k+1}(2-x^k)}{1-x}$$

因此，
$$F_{m}(x)=\frac{x^{m(k+1)}(2-x^k)^m}{(1-x)^m}$$

我们需要求 $\sum_{i=0}^{n}[x^i]F_m(x)$，可以转换为求 $[x^n]\frac{F_m(x)}{1-x}$。

推导一下，
$$
\begin{aligned}
[x^n]\frac{F_m(x)}{1-x}
&=[x^n]\frac{x^{m(k+1)}(2-x^k)^m}{(1-x)^{m+1}}\\
&=[x^{n-m(k+1)}]\frac{(2-x^k)^m}{(1-x)^{m+1}}\\
&=[x^{n-m(k+1)}]\sum_{i=0}^{m}\binom{m}{i}2^i(-1)^{m-i}x^{k(m-i)}\sum_{j\ge 0}\binom{j+m}{m}x^j
\end{aligned}
$$

当 $i$ 固定时，$j$ 唯一确定，直接暴力枚举 $i$ 即可，时间复杂度：$O(m)$。

---

## 作者：Arghariza (赞：0)

考虑如何判断一个方案是合法的，很容易想到贪心，从左到右考虑第 $i$ 棵树：

- 如果这棵树能向左倒即 $[x_i-k,x_i]$ 没有被占据，就向左倒。
- 否则向右倒。

显然向左倒对之前已经倒下的树没有影响，而对后面的树来讲，这棵树向左倒能留下尽量多的空间，所以优先向左倒一定不劣。

所以考虑一个 dp，设 $f_{i,j}$ 为第 $i$ 棵树倒下后最右覆盖到 $j$ 点的方案树，考虑新增一棵树：

- 对于 $p\in [j+k+1,j+2k]$ 的位置，它有两种方式被覆盖到（把树放到 $p$ 然后向左倒、把树放到 $p-k$ 然后向右倒），于是 $2f_{i,j}\to f_{i+1,p}$。
- 对于 $p\in [j+2k+1,+∞)$ 的位置，它只有一种方式被覆盖到（时刻保证贪心方案的性质），$f_{i,j}\to f_{i+1,p}$。

最后枚举 $j$ 的位置对 $f_{n,j}$ 求和即可。那么就可以写成 GF 的形式：

$$\sum\limits_{i=1}^n[x^i]\left(\sum\limits_{j=k+1}^{2k}2x^j+\sum\limits_{j=2k+1}x^j\right)^m$$

这是多项式快速幂，但我不会。

考虑写成封闭形式：

$$\begin{aligned}&\sum\limits_{j=k+1}^{2k}2x^j+\sum\limits_{j=2k+1}x^j\\=&\sum\limits_{j=k+1}x^j+\sum\limits_{j=k+1}^{2k}x^j\\=&\frac{x^{k+1}}{1-x}+\frac{x^{k+1}(1-x^k)}{1-x}\\=&x^{k+1}\cdot\frac{2-x^k}{1-x}\end{aligned}$$

所以：

$$\begin{aligned}&\sum\limits_{i=1}^n[x^i]\left(\sum\limits_{j=k+1}^{2k}2x^j+\sum\limits_{j=2k+1}x^j\right)^m\\=&\sum\limits_{i=0}^{n-m(k+1)}[x^i]\left(\frac{2-x^k}{1-x}\right)^m\end{aligned}$$

考虑到 $(2-x^i)^m$ 中 $x$ 的次数始终为 $k$ 的倍数，令 $f(i)=[x^{ik}](2-x^k)^m$，令 $g(i)=[x^i](1-x)^{-m}$：

$$\begin{aligned}f(i)=&[x^{ik}](2-x^k)^m\\=&[x^i](2-x)^m\\=&2^{m-i}(-1)^i\dbinom{m}{i}\\g(i)=&[x^i](1-x)^{-m}\\=&\dbinom{m+i-1}{i}\end{aligned}$$

那么即求 $\sum\limits_{ik+j\le n-m(k+1)}f(i)g(j)$，预处理 $g$ 的前缀和，然后求 $\sum\limits_{ik+j= n-m(k+1)}f(i)S_g(j)$ 即可。

很好写。

---

## 作者：Raisetsu41 (赞：0)

挺好一道题，可惜我是暴力二项式反演丑陋做法。

贪心的判定很显然，能往左边倒就往左边倒。先按计数 `dp` 方法写个式子， $dp_{i, j}$ 表示前 $i$ 棵树最后一棵倒下来放到了 $j$ 的方案数。

$$
dp_{i, j} = \sum_{l = 0}^{j - k - 1} dp_{i - 1, l} + \sum_{l = j - 2k}^{j - k - 1} dp_{i - 1, l}
$$

然后我对 GF 不怎么熟，就观察了一下这个式子，发现可以改写为

$$
dp_{i, j} = 2 \sum_{l = j - 2k}^{j - k - 1} dp_{i, l} + \sum_{l = 0}^{j - 2k} dp_{i, l}
$$

继续观察，发现可以转化这个问题，对于一个长度为 $n$ 的序列分成 $m$ 段，使得每一段的长度都大于等于 $k$，当一段的长度大于 $2k$ 时，该段的贡献为 $2$。

于是定义 $f_i$ 表示恰好有 $i$ 段的长度大于 $2k$ 的方案数，则答案为 $\sum_{i = 0}^m 2^{m - i} f_i$，然后开始吟唱，定义 $g_i$ 表示至少 $i$ 段的长度大于 $2k$，那么有下面的等式。

$$
\begin{aligned}
  g_i &= \sum_{j = i}^{m} \binom{m}{j} f_j \\
      &= \binom{m}{i} \binom{n - (i + m)k}{m}
\end{aligned}
$$

继续化简答案

$$
\begin{aligned}
  res &= \sum_{i = 0}^{m}\sum_{j = i}^{m} (-1)^j \binom{j}{i} g_j \\
      &= \sum_{j = 0}^{m} g_j \sum_{i = 0}^{j} 2^{m - j} (-1)^{i - j} \binom{j}{i} \\
      &= \sum_{j = 0}^{m} (-1)^{j} 2^{m - j} g_j
\end{aligned}
$$

于是可以 $\Theta(m)$ 直接计算了。

其实这个玩意没有这么复杂。可以有一个非常优美的 GF 做法，可惜我不会 /kk

---

## 作者：chroneZ (赞：0)

给出一种不用 GF 的解法。

首先可以想到在原序列上选择 $m$ 个长为 $k + 1$ 的区间，使得区间两两不交，最后将方案数乘以 $2 ^ m$ 以计算树放在区间的左端 / 右端的方案数。

容易发现，这样计算的问题在于，我们最后计数的对象是**序列上树的位置**，而不关心树是往哪边倒的。举个反例，可能会有两种安放 $m$ 个区间的方式，使得第一种方案中某个区间的左端点和第二种方案中某个区间的右端点相同，其余区间完全相同，此时乘 $2^m$ 会产生重复方案。

考虑对区间安放方式与树的位置建立一一映射。一种可能的方式是利用贪心的思想，如果一棵树在序列上能向左倒就向左倒，否则向右。这样一来，记安放区间时两个相邻区间分别为 $[l_1, r_1], [l_2, r_2]$，如果 $l_2 \in [r_1 + 1, r_1 + k]$，则区间 $[l_2, r_2]$ 存在 $2$ 种方案，既可以放在左端点向右倒，也可以放在右端点向左倒；否则若 $l_2 \geq r_1 + k + 1$，仅 $1$ 种方案，即放在右端点向左倒，因为按我们定义的映射方案，即使放在左端点它也应该向左倒，不符合这个区间的覆盖范围。

此即，记两个区间的“距离”为 $l_2 - r_1$，如果距离小于等于 $k$，会带来 $2$ 的贡献；否则贡献为 $1$。记 $f(x)$ 表示恰好有 $x$ 对相邻区间的距离大于 $k$ 的方案数（注意第一段区间，此处钦定 $r_0 = 0$），答案可以写作 $\sum \limits_{i = 0} ^ m 2^{m - i}f(i)$。

$f(i)$ 的计算就是经典的容斥了。记 $f'(S)$ 表示相邻区间距离大于 $k$ 的位置**恰好**为集合 $S$ 的方案数，$g(S)$ 表示钦定集合 $S$ 中的位置的相邻区间的距离大于 $k$ 的方案数。

两个区间的距离减一即需向两区间之间插入的空格数，因此 $g(S) = \binom{N - m(k + 1) - |S|(k + 1 - 1) + m}{m} = \binom{N - mk - |S|k}{m}$。

枚举一下贡献得 $g(S) = \sum \limits_{T \supseteq S} f'(T)$，子集反演得 $f'(S) = \sum \limits_{T \supseteq S} (-1) ^ {|T| - |S|}g(T)$。

转为枚举集合大小得 $f(n) = \binom{m}{n} f'(S), |S| = n$，进而 $f(n) = \binom{m}{n} \sum \limits_{i = n} ^ m \binom{m - n}{i - n} (-1) ^ {i - n} \binom{N - mk - ik}{m}$。由于 $\binom{m}{n}\binom{m - n}{i - n} = \binom{m}{i}\binom{i}{n}$，这个式子可以进一步化为 $f(n) = \sum \limits_{i = n} ^ m \binom{m}{i}\binom{i}{n} (-1) ^ {i - n} \binom{N - mk - ik}{m}$。
$$
\begin{aligned}
\text{ans} &= \sum_{i = 0} ^ m 2 ^ {m - i} \sum_{j = i} ^ m \binom{m}{j} \binom{j}{i} (-1) ^ {j - i} \binom{N - mk - jk}{m}	\\
&= \sum \limits_{j = 0} ^ m \binom{m}{j} \binom{N - mk - jk}{m} \sum \limits_{i = 0} ^ j 2 ^ {m - i} \binom{j}{i} (-1) ^ {j - i} \\
&= \sum \limits_{j = 0} ^ m \binom{m}{j} \binom{N - mk - jk}{m} 2^{m - j} (-1) ^ j\sum \limits_{i = 0} ^ j \binom{j}{i} 2^{j - i} (-1) ^ {i} \\
&= \sum \limits_{j = 0} ^ m \binom{m}{j} \binom{N - mk - jk}{m} 2^{m - j} (-1) ^ j
\end{aligned}
$$

直接计算即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int N = 3e5 + 10, mod = 998244353;

inline i64 ksm(i64 a, i64 b){
	i64 r = 1;
	while(b){
		if(b & 1) r = r * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return r;
}

inline i64 inv(i64 x) {return ksm(x, mod - 2);}

i64 fact[N], ifact[N];

inline i64 binom(i64 n, i64 m) {
	if(n < m) return 0;
	return fact[n] * ifact[m] % mod * ifact[n - m] % mod;
}

i64 p2[N];

int main(){
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); cout.tie(nullptr);
	
	fact[0] = ifact[0] = 1;
	for(int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % mod;
	ifact[N - 1] = inv(fact[N - 1]);
	for(int i = N - 2; i > 0; i--)
		ifact[i] = ifact[i + 1] * (i + 1) % mod;
	p2[0] = 1;
	for(int i = 1; i < N; i++)
		p2[i] = p2[i - 1] * 2 % mod;

	i64 n, m, k; cin >> n >> m >> k;
	i64 ans = 0;
	for(int j = 0; j <= m; j++){
		ans += binom(m, j) * binom(n - m * k - j * k, m) % mod * p2[m - j] % mod * (j % 2 == 0 ? 1 : -1);
		ans %= mod;
	}
	ans = (ans % mod + mod) % mod;
	cout << ans << "\n";
}
```

---

