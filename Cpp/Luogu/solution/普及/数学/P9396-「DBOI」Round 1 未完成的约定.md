# 「DBOI」Round 1 未完成的约定

## 题目背景

>  _生活快得停不下来_\
_璀璨的也最终衰败_\
_他感到负荷已过载_\
_车窗外_\
_天上大朵云彩_\
_追随他的速度跑得飞快_\
_不由自主比赛_\
——《笨小孩的道歉信》

不管多少个日夜，为你一直唱。

## 题目描述

$m^3$ 可以表示为 $m$ 个连续奇数的和 $(m \geqslant 1)$：  
$$
1^3 = 1\\
2^3 = 3 + 5\\
3^3 = 7 + 9 + 11\\
4^3 = 13 + 15 + 17 + 19\\
5^3 = 21 + 23 + 25 + 27 + 29\\
\cdots\cdots
$$

在左昂对奇数的狂热崇拜的影响下，苏信好写出来的歌只会是奇数长度。显然歌曲的长度不能是负数。

对于一首长度为 $x$ 的歌，它的悦耳值 $f(x)$ 满足将 $f(x)^3$ 按照上面的规律表示出来后，$x$ 是其中的一个加数。例如 $f(21) = 5, f(11) = 3,f(3) = 2$。

第二天，左昂前来参观，发现苏信好只写出来了一首歌，鄙夷不已。苏信好怒从心起，写出了以 $1\sim k$ 内所有长度为奇数的歌。

现在左昂想要知道苏信好所有歌的悦耳值之和，以预估他的狂热崇拜的效果。即：给定一个正奇数 $k(1\leqslant k< 2^{64})$，求 $s = \sum\limits_{i = 1}^{\frac{k + 1}{2}} f(2\times i - 1)$，即 $f(1) + f(3) + f(5) + \cdots +f(k)$。  

由于苏信好实在太生气，写出来的歌的悦耳值可能十分之大，你只需要输出 $s\bmod{10^9 + 7}$ 的结果。

**本题有多组数据。**

## 说明/提示


|  Subtask |  数据范围  | 分值 |
|:----:|:----:|:----:|
| Subtask 1 | $T=1$，$k< 2^{25}$ | $20$ |
| Subtask 2 | $T\leq 5$，$k< 2^{48}$ | $30$ |
| Subtask 3 | $T\leq 10^6$，$k < 2^{48}$ | $40$ |
| Subtask 4 | $T\leq 3\times 10^6$，$k < 2^{64}$ | $10$ |

**请注意常数因子对程序效率的影响。**

## 样例 #1

### 输入

```
1 114514 1919810 19950501 5```

### 输出

```
35```

## 样例 #2

### 输入

```
5 231421 523434 31243 5```

### 输出

```
50
30
40
55
35```

# 题解

## 作者：liuliucy (赞：10)

这道题目看到数据都会以为是 $O(1)$ 复杂度的吧……

所以直接数学方法暴力求解。

### 1.求解答案

首先看题目，对于任意的 $n$，其三次方都能表示成 $n$ 个连续奇数的和。

令集合 $S_{n} =\left \{ x_{n}|f(x_{n})=n \right \} $，目标：求其中最小的元素 $x_{n,1}$ 的值。

由题目可得 $S$ 内所有元素的和等于 $n^3$，根据高斯求和公式：

$$\frac{(x_{n,1}+2(n-1))n}{2}=n^3$$

易解得: $x_{n,1}=n^2-n+1$。

因此可得最大元素：$x_{n,n}=n^2+n-1$。

设 $f(k)=p$，然后考虑分区间，将原来 $[1,k]$ 区间分成 $S_{1}+S_{2}+S_{3}+...+S_{p-1}+R$，$R$ 表示分区间后的剩余元素集合。

则答案为：

$$\sum_{i=1}^{p}\sum_{j=1}^{i}  i+\sum_{i=x_{p,1}}^{k}p $$

化简一下：

$$=\sum_{i=1}^{p}i^2+\frac{k-x_{p,1}+2}{2}p$$

$$=\frac{(p-1)p(2p-1)}{6}+\frac{k-(p^2-p+1)+2}{2} p$$

再考虑求 $p$，先计算 $x_{n,1}=k$，也就是：

$$n^2-n+1=k$$

得：

$$n=\frac{\sqrt{4k-3} +1}{2}$$

显然：$x_{p,1} \le k < x_{p+1,1}$。

也就是：$x_{p,1} \le x_{n,1} < x_{p+1,1}$。

所以：$p=\left \lfloor n \right \rfloor $。

这样，我们就求出了这道题。

### 2.数据范围与取模
先注意数据范围，$k<2^{64}$，所以 $p<2^{32}$，注意我们上边的求解过程，计算出的答案最大是 $p^3$ 左右，大概为 $2^{96}$，我们可以用 ```__int128``` 储存变量，但是会因为常数过大超时，所以我们要在计算时先确定好能被除数整除的数，先对其做除法，便可以完美的求出答案。

但注意另外一个点，求 $p$ 的过程中，计算 $\sqrt{4k-3}$ 时会先计算 $4k-3$ 但是计算时电脑是使用  $64$ 位二进制储存的，但是 ```__int128``` 并不支持根号运算，所以在计算时要考虑强转 ```long double``` 再存入 $p$ 中，注意 $p$ 不能使用 ```__int128``` 储存，不然会导致常数过大导致超时。

取模也是一个问题，为了节省常数复杂度，不能暴力直接全用 ```__int128```，所以当我们除以 $2$ 时，我们得考虑乘上它的乘法逆元，再考虑取余，显然 $2$ 此时的乘法逆元是 $500000004$ 所以我们取余时就可以分开取余了。

### 3.Code

~~展示我丑陋的代码~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull md=1e9+7;
const ull ppp=500000004;
namespace Mker {
	ull SA, SB, SC, p = -1;
	int base;
	void init(){scanf("%llu%llu%llu%d", &SA, &SB, &SC, &base); p = p << (65 - base) >> (65 - base);}
	ull rand() {
		ull now = SC; now += !(now & 1);
	    SA ^= SA << 32, SA ^= SA >> 13, SA ^= SA << 1;
	    ull t = SA;
		return SA = SB, SB = SC, SC ^= t ^ SA, (now & p) + p + 1;
	}
};
void print(__int128 x){
	if(x==0)return;
	print(x/10);
	putchar(x%10+'0');
}
ull k;
int T;
int main(){
	scanf("%d",&T); Mker::init();
	while(T--){
		k = Mker::rand(); 
		ull p=(sqrt((long double)4*k-3)+1)/2;
		__int128 ans;
		ull a=p-1,b=p,c=2*p-1;		
		if(a%3==0)a/=3;
		else if(b%3==0)b/=3;
		else c/=3;
		if(a%2==0)a/=2;
		else if(b%2==0)b/=2;
		else c/=2;
		ans=(__int128)a*b%md*c%md;
		p%=md;
		ull len=(k%md*ppp%md-(((p*p%md-p%md)+md)%md+1)%md*ppp%md+md+1)%md;
		p%=md;
		(ans+=len*p%md)%=md;
		print(ans);
		putchar('\n');
	}
}
```


---

## 作者：StayAlone (赞：5)

出题人题解。

[所有部分分代码及标程均在这里。](https://www.luogu.com.cn/paste/3997j2uq)

这个题目是我们前面的月考卷子改编后的 idea，前年就出了，去年翻出来经过加强得到了这道签到题。

首先，不要畏惧输入格式……仔细阅读应该是可以理解使用方式的。

### Subtask 1

$\mathcal O(Tk)$，模拟即可。

### Subtask 2

令 $f(k) = l$，则：
$$
\begin{aligned}
\sum_{i = 1}^l i\geq\dfrac{k + 1}{2}\\
\dfrac{l(l + 1)}{2}\geq\dfrac{k + 1}{2}\\
l(l + 1)\geq k + 1\\
l(l + 1) - 1\geq k\\
\end{aligned}
$$

容易观察到，$l$ 是 $\sqrt k$ 级别的，因此可以 $\mathcal O(\sqrt k)$ 枚举到 $f(k)$ 的值。

由于 $m^3$ 被表示为 $m$ 个连续奇数的和，那么有 $1$ 个数答案为 $1$，$2$ 个数答案为 $2$，$3$ 个数答案为 $3$。所以算出 $l$ 之后，答案就是先把前 $l - 1$ 行的和累计，再单独计算第 $l$ 行的和。

$ans = \sum\limits_{i = 1}^{l - 1} {i^2} + l\times (\dfrac{k + 1}{2} - \dfrac{l(l - 1)}{2})$。

计算 $ans$ 也是 $\mathcal O(\sqrt k)$ 的。

总复杂度 $\mathcal O(T\sqrt k)$。

### Subtask 3

考虑优化 Subtask 2 的做法。

主体有两个部分，一个是计算 $l$，一个是累加平方和。我们分别优化。

1. 计算 $l$，显然可以二分，$\mathcal O(\log k)$。
2. 计算 $\sum\limits_{i = 1}^l {i^2}$。可以 $\mathcal O(\sqrt k)$ 预处理前缀和 $s_i = \sum\limits_{k = 1}^i{k^2}$，每一次 $\mathcal O(1)$ 查询。  

时间复杂度 $\mathcal O(\sqrt k+T\log n)$。其中空间复杂度较高，需要 $\mathcal O(\sqrt k)$。注意不要盲目开 `long long`，否则你会被卡空间。

### Subtask 4

略有些毒瘤，意料之外。

为了题解的简洁，证明均写在最后。

首先可以证明 $l = \operatorname{round}(\sqrt{k + 1})$，其中 $\operatorname{round}(x)$ 表示将 $x$ 四舍五入到整数的值。虽然这和二分的时间复杂度相同，但是由于 $k$ 的大小已经在 `unsigned long long` 的临界值，需要仔细思考，否则容易乘炸；若使用 `__int128`，需要注意写法的常数，若写法不优，可能会被卡常。

然而 $k + 1$ 仍然会爆 `unsigned long long`。你可以通过特判过题，也可以证明：$\forall k = 2p + 1(p\in\mathbb{N}),\operatorname{round(\sqrt{k})}=\operatorname{round(\sqrt{k + 1})}$。

至此，我们求出了 $l$。

对于平方和，有公式 $\sum\limits_{i = 1}^{p}{i^2} = \dfrac{p(p + 1)(2p + 1)}{6}$，则 $ans = \dfrac{l(l - 1)(2l - 1)}{6} + l\times (\dfrac{k + 1}{2} - \dfrac{l(l - 1)}{2})$。  

然而 $l(l - 1)(2l - 1)$ 爆 `unsigned long long` 了，所以你需要把三个数分别存下来，然后枚举哪个数含有因数 $2$，哪个数含有因数 $3$，手动除掉后再取模相乘。显然 $l(l - 1)$ 是 $2$ 的倍数且不会爆 `unsigned long long`，所以可以先除掉 $2$。

如果你会计算逆元，也可以使用逆元避免上面略显冗余的操作。

此外，还是因为 $k + 1$ 爆 `unsigned long long` 了，所以显然可以转换成 $\dfrac{k + 1}{2} = \dfrac{k - 1}{2} + 1$。

此外，由于 $k$ 太大，C++ 中的 `sqrt` 函数精度可能会被卡，所以你需要使用 `sqrtl` 函数。

注意不要乱取模，否则可能减出负数导致挂大分。

$ans = \dfrac{l(l - 1)(2l - 1)}{6} + l\times (\dfrac{k - 1}{2} + 1 - \dfrac{l(l - 1)}{2})$

时间复杂度 $\mathcal O(T\log n)$。  

--------------------
证明：$l = \operatorname{round}(\sqrt {k + 1})$。

即证明此时 $l(l + 1) - 1\geq k$。

设整数 $p$。

1. $l < p + 0.5$

$$
\begin{aligned}
(p + 0.5)^2> k + 1\\
p^2 + p + 0.25> k + 1\\
p^2 + p> k + 0.75\\
p(p + 1) - 1> k -0.25\\
\end{aligned}
$$

由于都是整数，所以 $p(p + 1 ) - 1\geq k$，则 $l$ 取 $p$，即“四舍”的值。

2. $l \geq p + 0.5$

$$
\begin{aligned}
(p + 0.5)^2\leq k + 1\\
p^2 + p + 0.25\leq k + 1\\
p^2 + p\leq k + 0.75\\
p(p + 1) - 1\leq k -0.25\\
\end{aligned}
$$

由于都是整数，所以 $p(p + 1 ) - 1\leq k - 1$，则 $l$ 不能取 $p$，而应取 $p + 1$，即“五入”的值。  


------------------

证明：$\forall k = 2p + 1(p\in\mathbb{N}),\operatorname{round(\sqrt{k})}=\operatorname{round(\sqrt{k + 1})}$。   

考虑反证法。

若要不同，只有一种情况：$\operatorname{round(\sqrt{k + 1})}$“五入”，$\operatorname{round(\sqrt{k})}$“四舍”。

设整数 $x$，因为 $(x + 0.5)^2 = x^2 + x + 0.25$，若要四舍，则 $k = x^2 + x = x(x + 1)$，必定是偶数，不符合题意。

---

## 作者：y_kx_b (赞：4)

听说 `sqrt` 被随机数据卡了/jk

首先看着题面中的三角，觉得全是奇数不太好看，于是我们全部给它除以 $2$（上取整）：

$$
1\\2, 3\\4, 5, 6\\7, 8, 9, 10\\\cdots\cdots
$$

题面可以转化成求 $\sum\limits_{x=1}^{\frac {k+1}2}f_1(x)$，其中 $f_1(x)$ 表示上图中 $x$ 所在的层数。然后很容易我们发现第 $i$ 层有 $i$ 个元素，前 $i$ 层的 $f_1$ 和即为 $\sum_{i=1}^ti^2=\frac{t(t+1)(2t+1)}6$。于是考虑把前面整层的用这个公式直接算，最后单层单独算即可。

发现第 $t$ 层最后一个元素是 $\sum_{i=1}^ti=\frac{t(t+1)}2$，解一元二次方程 $t^2+t-2x=0\Rightarrow t=\frac{-1\pm\sqrt{1+8x}}2$。按照该式算出来的 $t$ 下取整就是是最后一个完整层的层数。按照上式计算并最后加上 $(t+1)(\frac{k+1}2-\frac{t(t+1)}2)$（统计第 $t+1$ 层的元素）就是答案啦。

具体实现可能有比较多的细节（）

code：
```cpp
typedef unsigned long long ull;
const int mod = 1e9 + 7;
ull sum(ull x) {// calc x(x+1) / 2
	ull y = x + 1;
	if(x & 1) /*x*/y >>= 1; else /*y*/x >>= 1;
	return x * y;
}
ll sum2(ull x) {// calc (x(x+1)(2x+1) / 6) % mod
	ull y = x + 1, z = (x << 1) + 1;
	if(x % 3 && y % 3) z /= 3;
	else if(x % 3) y /= 3;
	else x /= 3;
	if(x & 1) y >>= 1; else x >>= 1;
	return (x % mod) * (y % mod) % mod * (z % mod) % mod;
}
bool major(int Testcase = 1) {
	scanf("%d", &T); Mker::init();
	while (T--) {
		unsigned long long k = Mker::rand();
		k = (k >> 1) + 1;// (k+1) / 2
		ull t = (sqrt/*l*/((long double)k * 8 + 1) - 1) / 2;
		ull r = sum(t);//第 t 层最后一个元素
		ll ans = sum2(t);
		if(r != k) (ans += (t + 1) * ((k - r) % mod)) %= mod;//加上第 t+1 层的元素
		writeln(ans);
	}
	return 0;
}
```

---

