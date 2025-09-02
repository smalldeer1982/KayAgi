# 【模板】Pólya 定理

## 题目描述

给定一个 $n$ 个点，$n$ 条边的环，有 $n$ 种颜色，给每个顶点染色，问有多少种**本质不同**的染色方案，答案对 $10^9+7$ 取模。

注意本题的本质不同，定义为：**只需要不能通过旋转与别的染色方案相同**。

## 说明/提示

$$n \leq 10^9$$
$$t \leq 10^3$$

## 样例 #1

### 输入

```
5
1 
2 
3 
4 
5 ```

### 输出

```
1
3
11
70
629```

# 题解

## 作者：Soulist (赞：374)

长文警告。

本文对于 $\rm Polya$ 定理中使用到的绝大部分引理都进行了~~伪证~~ 较为成分的证明。

在阅读这篇文章的时候，您可以选择性的跳过您所知道的知识，下面将从 "群" 这一个充满魔法的东西开始谈起。

## 群

### 群的定义

定义集合 $\rm G$ 和作用与集合 $\rm G$ 的二元运算 $\times$ 

若其满足以下 $4$ 个性质，则称其为一个群$(\sf Group)$，记为 $(~G,\times~)$：

$1.$  封闭性 $(\sf Closure)$

> 若存在 $a$ 和 $b$ 满足 $a\in G,b\in G$ ，则有 $a\times b\in G$

$2.$  结合律 $(\sf Associativity )$

> 对于任意 $a,b,c$ 有 $(a\times b)\times c = a\times (b\times c)$

$3.$  单位元 $(\sf Identity)$

>存在 $e\in G$，满足对于任意 $a\in G$ 有： $a\times e = e\times a = a$
>
> 这样的 $e$ 被称为单位元。容易证明单位元唯一（你假设有多个可以马上推出矛盾）
>
> $\rm e.g:$ 实数的乘法运算就是一个群，模意义下的乘法运算（不包括$0$）同样是一个群。这些例子中的单位元均为 $1$

$4.$  逆元 $(\sf Inverse)$

>对于任意 $a\in G$ 存在 $a'\in G$ 满足 $a\times a' = a'\times a = e$
>
>值得注意的是这个 $a'$ 是唯一的。读者可以尝试自行证明。


**性质的实际应用：**

$\sf 1- question:$  为什么不能使用传统的树状数组实现区间最值查询。

$\sf 1-answer:$ 树状数组在于运算上存在一个差分的过程，换而言之需要"逆元"的存在，然而最值函数与数集$\rm S$不构成群。~~（好像在扯淡）~~

### 子群：

如果 $H$ 为 $G$ 的一个子集，且有 $(~H,\times ~)$ 构成一个群，那么称 $(H,\times )$ 为 $(G,\times)$ 的一个子群。简记为 $H\le G$。

如果 $G$ 是一个群，$H$ 为其一个子群，且有 $g\in G$，那么：

> $gH={g\times h,h\in H}$，称其为 $H$ 在 $G$ 内的关于 $g$ 的左陪集。

> $Hg={h\times g,h\in H}$，称其为 $H$ 在 $G$ 内的关于 $g$ 的右陪集。

陪集的一些性质：

下面只讨论右陪集：（左陪集同理）


> $1.$ $\forall g\in G$，$|H|=|Hg|$

证明：注意到 "群的性质" ： 逆元唯一，所以有对于任意的 $g\times h_1$ 与 $g\times h_2$ 其必然不同。

> $2.$ $\forall g\in G$，$g\in Hg$

证明：注意到 $H$ 是一个群，所以 $H$ 必然包括了单位元$e$，所以 $e\times g\in Hg\iff g\in Hg$

> $3.$ $Hg = H\iff g\in H$

证明显然，由于封闭性可以得到。

> $4.$ $H a=Hb\iff a\times b^{-1}\in H$

证明：

首先你发现陪集像极了运算，所以有：$Ha=Hb \implies Ha\times b^{-1}=H$ 由于性质$3$ 得到： $a\times b^{-1}\in H$

由于 $a\times b^{-1}\in H$ 所以 $Ha = Hb$ ...这个显然，配合性质 $3$ 食用。

> $5.$ $Ha\cap Hb\ne \varnothing \to Ha=Hb$ 

这个性质非常有用，其意味着一个子群 $H$ 的陪集的交集要么是空要么两个相等。

证明：假设 $c\in Ha,c\in Hb$ ，于是有 $\exists ~h_1,h_2\in H$，$h_1\times a=c,h_2\times b=c$ 所以我们得到：$ab^{-1}=h_2 h_1^{-1}\in H$ 由于 性质$4$ 得到 $Ha=Hb$。

> $6.$ $H$ 的全体右陪集的并为 $G$

证明：因为 $H$ 存在单位元，$g$ 取遍 $G$ 中每一个元素。

#### 较为常见的表述：

若 $H\le G$，则 $G/H$ 代表 $G$ 中所有的 $H$ 的左陪集即$\{gH,g\in G\}$

若 $H\le G$，则 $[G:H]$ 表示 $G$ 中 $H$ 的不同的陪集的数量。


#### **拉格朗日定理：**

对于有限群 $G$ 与有限群 $H$ ，若 $H$ 为 $G$ 的子群，那么有：

$$|H| \text{整除} |G|$$

即 $H$ 的阶整除 $G$ 的阶。

更具体点：

$$|H|\times [G:H]=|G|$$

证明：

由于陪集的性质$1,5,6$，所有本质不同的陪集互不相交且大小均为 $|H|$ 且并的大小为$|G|$，可以得到不同的陪集数量乘以陪集大小$(|H|)$为 $G$ 。你会发现有了陪集的性质之后这些都特别自然了。

## 置换

> 备注：一个充满魔法的科技。

### 一些定义：

-----

#### **$\sf Two-line notation$**

双行表示法，大概就是用两个括号括起来，然后令 "元素/置换" 表示一个从【上列】 到 【下列】 的置换。

比如：

$\sigma=\begin{pmatrix}1&2&3&4&5\\2&5&4&3&1\end{pmatrix}$

其表示的置换为将排列 $1~2~3~4~5$ 变为 $2~5~4~3~1$ 的一个置换，可以理解为用原本第二个元素代替第一个元素，用原本的第 $5$ 个元素代替第 $2$ 个元素...依次类推。


不过我更喜欢强行规定第一列是 $(1,2,...n)$

然后第二列就是：

$\sigma =(a_1,a_2...a_n)$ 表示一个置换。

每个置换都是一个这样的排列，一个长度为 $n$ 的不同的置换的数量为 $n!$ 


#### 运算：

可以写为 $\sigma \times a$ 不过更习惯被表示为 $\sigma(a)$ 

其运算规则为：$\sigma(a)= (a_{\sigma_1},a_{\sigma_2}...a_{\sigma_n})$

没错，这是一个运算，通常可以称呼其为置换的「魔法」/「乘法」，如上例可以用文字描述为：$\sigma$ 和 $a$「魔法」起来。（这里是我个人认为它非常神奇而称呼其为「魔法」诸位笑笑便好）

更正式的，我们称呼其为置换的「合成」

### 置换群：

不妨令集合 $N = \{1,2,3...n\}$ ，令集合 $M$ 为 $N$ 的若干个排列构成的集合，我们令群 $G=(M,\times )$，其中 $\times$ 这个运算为「魔法」/「合成」，若再此基础上，其满足群的性质。则我们称 $G$ 是一个置换群。

我们现在来验证一个例子，$N$ 的所有可能的排列与运算「魔法」构成的 "二元组?"（这里不太清楚如何称呼） 是一个合法的置换群：


$1.$ 封闭性，显然，注意上面定义的是所有可能的排列。

$2.$ 单位元$~:e=(1,2,...n)$

> 容易发现 $\sigma$「魔法」$e= e$「魔法」$\sigma=\sigma$

$3.$ 结合律：容易验证「魔法」满足结合律。

$4.$ 逆元：容易验证「魔法」运算存在逆元。


### 「群作用」

分为 左群作用 和 右群作用。具体不太记得了...下面描述的是左群作用的定义，下文出于方便，将同一称为「群作用」，并使用此处的定义。

定义：

对于一个集合 $M$ 和群 $G$ 。

若给定了一个二元函数 $\varphi(v,k)$ 其中 $v$ 为群中的元素，$k$ 为集合元素，且有：

$$\varphi(e,k)=k\quad (e~\text{是单位元})$$

$$\varphi(g,\varphi(s,k))=\varphi(g\times s,k)$$

则称呼群 $G$ 作用于集合 $M$。


### 轨道-稳定子定理：

----

#### 轨道

考虑一个作用在 $X$ 上的群 $G$ 。 $X$ 中的一个元素 $x$ 的「轨道」则是 $x$ 通过 $G$ 中的元素可以转移到的元素的集合。$x$ 的轨道被记为 $G(x)$，方便起见，我们用 $g(x)$ 表示群 $G$ 元素 $g$ 作用于 $x$ 的群作用的返回值，即 $g(x)=\varphi(g,x)$。

#### 稳定子

稳定子被定义为：$G^x = \{g|g\in G,g(x)=x\}$

使用语言描述，便是群 $G$ 中满足 $g(x)=x$ 的所有元素 $g$ 所构成的集合。

$\rm e.g:$

给定一个 $2\times 2$ 的矩形，每个点可以使用黑白染色，这样得到的所有矩形构成的集合为 $M$

给定一个群 $G$ ，其成员为 $1.$ 顺时针旋转$90$°，$2.$ 顺时针旋转$180$°，$3.$ 顺时针旋转$270$°，$4.$ 顺时针旋转$0$°。其运算为模$360$意义下的加法（大概，想必诸位理解我的意思）

那么对于一个 $M$ 内的一个元素（$0$表示白，$1$表示黑）

$\begin{pmatrix}1&1\\0&0\end{pmatrix}$

而言，其稳定子 $G^x$ 为 $\{$顺时针旋转$0$°$\}$

其轨道为：


$\begin{pmatrix}1&1\\0&0\end{pmatrix},\begin{pmatrix}0&1\\0&1\end{pmatrix},\begin{pmatrix}0&0\\1&1\end{pmatrix},\begin{pmatrix}1&0\\1&0\end{pmatrix}$

似乎有一个巧合，轨道大小与稳定子的大小乘积为 $4$ 刚好是群 $G$ 的大小！

* 诸位可以去举其他例子来类比，总是可以发现这个规律。

这个东西有一个名字，叫做轨道-稳定子定理：


#### 轨道-稳定子定理：

$$|G^x|\times |G(x)|=|G|$$

首先可以证明：$G^x$ 是 $G$ 的一个子群。

首先根据群作用的定义，我们得知：$e\in G^x$

结合律显然满足，我们接下来考虑证明逆元和封闭性。

封闭性：$f\in G^x, g\in G^x$ 则 $f(x)=x,g(x)=x$ 根据群作用的定义，此时有：$(f\times g)(x)=x$，所以 $f\times g\in G^x$

逆元：若 $g\in G^x$ 则 $g(x)=x$ 又因为 $(g\times g^{-1})(x)=e(x)=x$ 所以 $g^{-1}(x)=x$ 所以 $g^{-1}\in G^x$

所以按照拉格朗日定理有： $|G^x|\times [G:G^x] = |G|$

于是只需要证明 $[G:G^x]=|G(x)|$

然后这个东西直观感受挺对的...但是还是丢一个严谨的证明：

我们只需要证明，每一个 $g(x)$ 都能对应 $[G:G^x]$ 中的一个左陪集/右陪集即可。

不妨这样构造一个一一对应的关系：

若 $f(x)=g(x)$ 则可得：$f\times g^{-1}=x=e(x)\in G^x$，由于陪集的性质$f\times G^x=g\times G^x$ ，这意味着我们证明了相同的 $f(x)$ 都可以对应相同的陪集。

反之亦然 $fG^x=gG^x\iff f(x)=g(x)$

于是每一个 $g(x)$ 我们令 $gG^x$ 表示它对应的陪集即可，正确性由上述性质保证不会重复，相同的 $g(x)$ 总是对应着相同的陪集。


## **Burnside** 定理

公式：

定义 $G$ 为一个置换群，定义其作用于 $X$，如果 $x,y\in X$ 在 $G$ 作用下可以相等即存在 $f\in G$ 使得 $f(x)=y$ 则定义$x,y$ 属于一个等价类，则不同的等价类的数量为：

$$|X/G|=\dfrac{1}{|G|}\sum_{g\in G} X^g$$

其中， $X^g$ 为 $X$ 在 $g$ 作用下的不动点的数量。即满足 $g(x)=x$ 这样的 $x$ 的数量。

文字描述：$X$ 在群 $G$ 作用下的等价类总数等于每一个 $g$ 作用于 $X$ 的不动点的算数平均值。

证明：

由于每个元素属于仅属于一个轨道，轨道内部在群 $G$ 作用下互达，(陪集性质) 所以我们可以得到：

$$|X/G|=\sum_{x\in X} \dfrac{1}{[G:G^x]}$$

根据轨道-稳定子定理，得到：

$$[G:G^x]=\dfrac{G}{|G^x|}$$

$$|X/G|=\sum_{x\in X}\dfrac{G^x}{G}$$

$$|X/G|=\dfrac{1}{|G|}\sum_{x\in X} G^x$$

后面那一坨，反过来，就是对于每一个群作用 $g$ ，其作用下不动点的数量。

综上，我们得到 $\sf Burnside$ 定理。

--------

### 回到本题，下面的关于本题的做法在一定程度上算对于 $\rm P\acute{o}lya$ 定理的推导。

首先观察本题与 $\sf Burnside$ 定理的关系。

容易发现，本质不同的 $n$ 个点的环可以看作，在群 $G$ 为$\{$ 旋转$0$ 个，旋转 $1$ 个...旋转$n-1$个 $\}$ 这些置换作用下得到的等价类的数量。

同时我们定义集合 $M$ 为 $\{1\to n\}$ 的所有可能排列表示初始的环。

于是由于 $\sf Burnside$ 定理，得到：

$$Ans=\dfrac{1}{|G|}\sum_{g\in G}M^g$$
  
我们依次考虑每个置换对于答案的贡献，显然旋转 $0$ 个的不动点的数量为：$n^n$ 即所有集合都合法。

对于旋转 $k$ 个而言，我们知道一个元素是不动点等价于其存在一个长度为 $a$ 的循环节满足 $a|k$ ，又因为对于循环节 $a$ 而言，必然存在 $a|n$ ，所以我们可以改写判定条件为存在一个长度为 $\gcd(k,n)$ 的循环节。

于是对于旋转 $k$ 个而言，每个子串的前 $\gcd(k,n)$ 都是任意取的，所以得到其贡献为 $n^{\gcd(k,n)}$

于是答案为：

$$\dfrac{1}{n}\sum_{k=1}^n n^{\gcd(k,n)}$$

剩下的就是莫比乌斯反演那一套的套路工作了，下面简单推导：

枚举 $\rm gcd$ 变为：

$$\dfrac{1}{n}\sum_{d|n} n^d \times \sum_{k=1}^{\frac{n}{d}} [\gcd(k,\dfrac{n}{d})==1]$$

后面那个式子是欧拉函数，直接带入即可：

$$\dfrac{1}{n}\sum_{d|n}n^d \varphi(\frac{n}{d})$$

然后本题暴力计算欧拉函数是可以通过的，复杂度为$O(Tn^{\frac{3}{4}})$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 1e9 + 7 ; 
int T, n ; 
int fpow( int x, int k ) {
	int ans = 1, base = x ; 
	while( k ) {
		if( k & 1 ) ans = 1ll * ans * base % P ; 
		base = base * base % P, k >>= 1 ; 
	} return ans ; 
}
int phi( int x ) {
	int ans = x ; 
	for( re int i = 2; i <= sqrt(x); ++ i ) {
		if( x % i ) continue ;
		ans = ans - ans / i ;
		while( x % i == 0 ) x /= i ;
	}
	if( x != 1 ) ans = ans - ans / x ;
	return ans ; 
}
void inc( int &x, int y ) {
	( ( x += y ) >= P ) && ( x -= P ) ;
}
signed main()
{
	int T = gi() ; 
	while( T-- ) {
		int n = gi(), cnt = sqrt(n), Ans = 0 ; 
		for( re int i = 1; i <= cnt; ++ i ) {
			if( n % i ) continue ;
			int p1 = phi(i), f1 = fpow( n, n / i ) ; 
			f1 = f1 * p1 % P, inc( Ans, f1 ) ;
			if( i * i != n ) {
				int p2 = phi( n / i ), f2 = fpow( n, i ) ;
				f2 = f2 * p2 % P, inc( Ans, f2 ) ;
			}
		}
		cout << Ans * fpow( n, P - 2 ) % P << endl ; 
	}
	return 0 ;
}
```

这样，这道题做完了，但是这篇文章还没完，接下来要介绍 $\rm P\acute{o}lya$ 定理。（其实也差不多）

## $\rm P\acute{o}lya$ 定理

考虑如何快速的使用 $\sf Burnside$ 定理进行计算。

我们可以注意到在一般的染色问题/类似的问题求本质不同的xxx的问题当中（即 $\sf Burnside$ 派上用场的时候）我们一般都是要求不动点的数量。

对于一个置换 $(a_1,a_2...a_n)$ 按照前文，我们规定上列为 $(1,2...n)$ 则其描述的是第一个位置变成 $a_1$...诸如此类的轮换。

在使用 $\sf Burnside$ 解决染色问题的时候，我们需要求的是不动点的数量，而对于上述的置换，假设我们令每个 $i$ 向 $a_i$ 连一条边容易发现会得到若干个环，仔细思考，每个环的颜色应当相同。

我们定义这个环的数量为 $c(g)$ 即置换 $g$ 的轮换(环)数。

那么我们现在可以改写 $\sf Burnside$ 定理为：

$$\dfrac{1}{|G|}\sum_{g\in G}m^{c(g)}$$

$m$ 表示可用的颜色数。

这就是 $\rm P\acute{o}lya$ 定理辣！

* 如果你认真的读完了前文的内容，那么这一步应该是相当显然的（

完结撒花！

-------

## 参考资料：

https://www.cnblogs.com/cyx0406/p/burnside_and_polya.html

https://www.cnblogs.com/yyf0309/p/Burnside.html

https://en.wikipedia.org/wiki/Burnside%27s_lemma

https://en.wikipedia.org/wiki/Group_action

https://en.wikipedia.org/wiki/Coset

https://en.wikipedia.org/wiki/Lagrange%27s_theorem_(group_theory)

感谢 tiger 对于本文的改正意见以及指导。

---

## 作者：rEdWhitE_uMbrElla (赞：39)

好题呢，不仅是单纯的Polya定理欸

0. 题目理解

	可能是人弱的原因，一开始我把```本质不同的染色方案```理解成不仅要不能通过旋转与别的染色方案相同，还要不能通过翻转与别的染色方案相同，然后样例看不懂。实际上，```本质不同的染色方案```就**只需要不能通过旋转与别的染色方案相同。**
    
1. 在Polya定理之前——Burnside引理

	burnside引理是polya定理的基础。
    
    burnside引理大概是长这样的：
    
    ---
    
    对于每个置换f，我们定义C(f)为在置换f下保持不变的方案数。
    
	则有： 本质不同的方案数为C(f)的平均数。
    
    $ans=\frac{1}{\left | G \right |} \sum _{f \in G} C(f)$
    
    ---
    
    并不是重点，就不细讲了。
    
    然而Burnside引理需要枚举每个方案，会TLE。
    
2. Polya定理

	我们知道对于每个置换f，我们一定能把它表示成循环的形式。那么我们定义L(f)为f的循环节数，k为颜色数(其实k=n)。根据该定理，则有$k^{L(f)}=C(f)$。那么问题就转化为了求L(f)。
    
    这题很良心，置换只有旋转，于是可以简单解决，否则光是求L(f)就要O(n)了。同时，```|G|=n```首先我们设这是第i次旋转(初始状态算第一次旋转)，则有每个循环节长度为```lcm(n,i)/i```，那么```L(f)=n/(lcm(n,i)/i)```，即```L(f)=gcd(n,i)```。所以，$ans=\frac{1}{n} \sum _{f \in G} k^{gcd(n,i)}$
    
3. 优化
	
    然而我们发现，现在我们求每一个ans就已经是O(n)了，还有一个常数巨大的乘方，，，可能仅仅是每个测试点里的一组数据就超时，，然而我们还有一个t。。。
    
    - 优化1：快速幂
    
    	应该都会吧，，不讲了。。。
        
    - 优化2： 欧拉函数
    	
    	我们可以从gcd优化。设$d_i=gcd(n,i)$。明显，所有d都是n约数。设有x个d是相等的，那么可以枚举n的约数。设枚举到了第j个约数$p_j$，那么$d=n/p_j$。我们也很容易发现$x=\varphi (n/d)$。所以$ans=\frac{1}{n} \sum _{p|n} \varphi (p)\times k^{\frac {n}{p}}$ 于是求ans只要$O(\sqrt n)$了
        
    - 优化3：充分利用```k=n```
    
        其实这是一个主要目的为防止溢出的优化，但同时也对常数有一定优化。
        
        在之前的算法中，我们因为要在算完$k^{L(f)}$的和后除以n，然而对于除法我们无法使用同余，所以不能在求和时取模，那么有很大的溢出风险。然而因为```n=k```，我们完全可以将k的指数减1，同时还解决了要处以n的尴尬，那么求和时完全是可以防止溢出的(为了稳妥起见，我用了```__int128```)。过程如下：
        
        $\because k=n$
        
        $\therefore ans= \sum_{p|n}\frac{\varphi (p)\times k^{\frac {n}{p}}}{n}=\sum_{p|n}\frac{\varphi (p)\times n^{\frac {n}{p}}}{n}=\sum_{p|n}\varphi (p)\times n^{\frac {n}{p}-1}$
        
好了，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace FastIO{ //IO优化
    char gc(){
        static char buf[100000],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
    }
    template<typename __Type_of__scan>
    void scan(__Type_of__scan &x){
        __Type_of__scan f=1;x=0;char s=gc();
        while(s<'0'||s>'9'){if(s=='-')f=-1;s=gc();}
        while(s>='0'&&s<='9'){x=x*10+s-'0';s=gc();}
        x*=f;
    }
    char buf[100000],*pp=buf;
    void pc(const char c){
        if(pp-buf==100000)fwrite(buf,1,100000,stdout),pp=buf;
        *pp++=c;
    }
    template<typename __Type_of__preprint>
    void fsh(__Type_of__preprint x){
        if(x<0){pc('-');x=-x;}
        if(x>9)fsh(x/10);
        pc(x%10+'0');
    }
    template<typename __Type_of__print>
    void print(__Type_of__print x){fsh(x);fwrite(buf,1,pp-buf,stdout);pp=buf;}
}
using namespace FastIO;

typedef __int128 LL;
const LL mod=1e9+7;

LL qpow(LL x,LL y){ //快速幂
    LL res = 1;
    while(y){
        if(y&1) res = res*x%mod;
        x = x*x%mod;
        y >>= 1;
    }
    return res;
}

LL euler_phi(LL n) { //欧拉函数
	LL res=1;
	for(LL i=2; i*i<=n; i++)
		if(n%i==0) {
			n/=i,res=res*(i-1);
			while(n%i==0) n/=i,res=res*i;
		}
	if(n>1) res=res*(n-1);
	return res;
}

LL polya(LL m,LL n) { //polya定理主体
	LL tot=0;
	for(LL i=1; i*i<=n; i++) {
		if(n%i) continue;
		tot+=euler_phi(i)*qpow(m,n/i-1);
		if(i*i!=n) tot+=euler_phi(n/i)*qpow(m,i-1);
	}
	return tot%mod;
}

int main(){
	int t;
	scan(t);
	for(;t;--t){
		LL n;
		scan(n),print(polya(n,n)),pc('\n');
	}
}
```

---

## 作者：Lskkkno1 (赞：26)

## $\text{Polya}$ 计数原理

### 先规定一些东西

 下面所说的**方案**指的是一种染色方案，或者说是一种状态

 用 $D(g_i)$ 表示  $g_i$ 这种**置换**下不动的**方案**的总数

 用 $Z_i$ 表示 $i$ 这种**方案**下置换后不变的**置换集合**

 用 $E_i$ 表示与 $i$ 这种**方案**本质相同的方案的**方案集合**

### 然后就有下面这些定理

#### 定理一 :

 $|E_k| \times |Z_k| = |G|$ 

其中 $|G|$ 表示置换集合大小

翻译过来就是 : 一类本质相同的**方案个数**乘上这类方案下置换不变的**置换个数**等于**置换总数**

这个窝不会证, 求哪位教教我qwq, 不过我们老师给我举例了很多都是对的, 就先假定它是正确的吧

#### 定理二 :

 $N = \sum_{i = 1}^{L}|E_i|$ 

其中 $N$ 为所有的方案个数(可相同), $L$ 为本质不同的集合大小

这个比较显然, 总方案数等于所有**本质不同**的方案乘上这种方案的**重复次数**

#### 定理三 :

 $\sum_{k = 1}^{N}|Z_k| = \sum_{i = 1}^{|G|}D(g_i)$

所有方案下置换不变的**置换个数**, 等于所有置换下方案不变的**方案个数**

想一下, 这个好像真的是对哒

想象方案和置换连边, 构成一个二分图, 而式子左右其实都是边的个数, 当然相等啊

### 开始推一些东西

$$
\sum_{k = 1}^{N}|Z_i| = \sum_{i = 1}^{L}\sum_{j \in i}|Z_i|
$$

$$
\sum_{k = 1}^{N}|Z_i| = \sum_{i = 1}^{L}|E_i||Z_i|
$$

$$
\sum_{k = 1}^{N}|Z_i| = L \cdot |G|
$$

即 :

$$
L = \frac 1 {|G|} \sum_{k = 1}^{N}|Zi|
$$

又 :
$$
\because \sum_{k = 1}^{N}|Z_k| = \sum_{i = 1}^{|G|}D(g_i)
$$

$$
\therefore L = \frac 1 {|G|} \sum_{i = 1}^{|G|}D(g_i)
$$

### 结论

  $L = \frac 1 {|G|} \sum_{i = 1}^{|G|}D(g_i)$, 这就是 $\text{Burnside}$ 定理了

 也就是说, 我们知道了所有**置换下不动的方案**(这种置换的不动点)总数, 将它除以置换集合的大小, 就可以得到**本质不同**的方案数了

  而对于一类计数问题 :

  在长度为 $N$ 的环上染色, 有 $M$ 种颜色, 我们就有

  $L = \frac 1 {|G|} \sum_{i = 1}^{|G|}M^{C(g_i)}$

  其中 $C(g_i)$ 为置换 $g_i$ 的循环总数, 且$C(g_i) = \frac {N} {gcd(i, N)}$ ($gcd(i, N)$ 为一个循环的长度)

  解释 : 一种置换不变, 那么一个循环上的点颜色都必须相同, 而每一个循环的染色操作互不影响, 用乘法原理可得 $D(g_i) = M^{C(g_i)}$

  考虑枚举循环总数, 用**欧拉定理**就可以快速求出上式

  $L = \frac 1 {|G|} \sum_{i | N} \phi(N / i) \cdot M^i$

  对于 [P4980](https://www.luogu.org/problemnew/show/P4980)

  最后答案 $res = \frac 1 {|N|} \sum_{i | N} \phi(N / i) \cdot N^i$

#### [$\color {Deepskyblue} {Code}$](https://www.luogu.org/paste/up33qogs)

---

## 作者：GKxx (赞：17)

### 题意

$n$个点的环，用$m$种颜色给点染色，求本质不同的方案数。

两个方案本质相同，当且仅当其中一个方案可以通过旋转得到另一个。

### 题解

一种染色方案可以看做先染了前$d$个位置，然后将这一段复制$n/d$次拼接而成，其中$d$是$n$的约数。我们称这个$d$为一种染色方案的*周期*（这里默认是最小正周期）。

对于一个周期为$d$的染色方案，将它旋转$d$次会得到$d$个看起来不同但本质相同的染色方案。

设$f(x)$表示周期为$x$的看上去不同的方案数。枚举周期$d$，那么每一种周期的方案就多算了$d$次，因此

$$ans=\sum\limits_{d|n}\frac{f(d)}{d}$$

$f(x)$不容易计算，但是我们知道：对于$n$的所有约数$d$，将$f(d)$求和就会得到总方案数$m^n$，即

$$m^n=\sum\limits_{d|n}f(d)$$

莫比乌斯反演得

$$f(x)=\sum\limits_{d|x}\mu(x/d)m^d$$

代入第一个式子得到

$$ans=\sum\limits_{d|n}\frac{1}{d}\sum\limits_{k|d}\mu(d/k)m^k$$

$$=\sum\limits_{d|n}\frac{d}{n}\sum\limits_{k|\frac{n}{d}}\mu(n/dk)m^k$$

$$=\frac{1}{n}\sum\limits_{d|n}d\sum\limits_{k|\frac{n}{d}}\mu(n/dk)m^k$$

$$=\frac{1}{n}\sum\limits_{k|n}m^k\sum\limits_{d|\frac{n}{k}}d\mu(n/dk)$$

$$=\frac{1}{n}\sum\limits_{k|n}m^k\varphi(n/k)$$

上面设颜色的数量为$m$是为了避免混淆，本题中$m=n$。

本题对于等价类的定义是相当简单的，因此可以用莫比乌斯反演轻松解决。如果遇到更加复杂的等价类定义就要老老实实使用polya计数了。

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T& x) {
    int f = 0, c = getchar(); x = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    if (f) x = -x;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) { write(x); puts(""); }
template <typename T> inline bool chkmin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkmax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

typedef long long LL;

const LL mod = 1e9 + 7;

inline LL qpow(LL x, LL k) {
    LL s = 1;
    for (; k; x = x * x % mod, k >>= 1)
        if (k & 1) s = s * x % mod;
    return s;
}

inline LL phi(LL x) {
    LL ans = x;
    for (LL i = 2; i * i <= x; ++i)
        if (!(x % i)) {
            ans = ans / i * (i - 1);
            while (!(x % i)) x /= i;
        }
    if (x > 1) ans = ans / x * (x - 1);
    return ans;
}

int main() {
    int T; read(T);
    while (T--) {
        LL n; read(n);
        LL ans = 0;
        for (LL k = 1; k * k <= n; ++k)
            if (!(n % k)) {
                if (k * k == n)
                    ans = (ans + qpow(n, k) * phi(n / k) % mod) % mod;
                else {
                    ans = (ans + qpow(n, k) * phi(n / k) % mod) % mod;
                    ans = (ans + qpow(n, n / k) * phi(k) % mod) % mod;
                }
            }
        writeln(ans * qpow(n, mod - 2) % mod);
    }
    return 0;
}
```

---

## 作者：Memory_of_winter (赞：15)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10202117.html)

**题目大意：**给一个$n$个点的环染色，有$n$中颜色，问有多少种涂色方案是的旋转后本质不同

**题解：**$burnside \,$引理：$ans=\dfrac1{|G|}\sum\limits_{g\in G}A_g$

对于环，有$Polya$定理：$ans=\dfrac1{|G|}\sum\limits_{g\in G}m^{c(g)}$（$m$为颜色数，在这道题中$m=n$，$c(g)$为置换$g$中循环个数）

因为是循环相同，所以$|G|=n$，当
$$g=\left(\begin{aligned}&1&2&&\cdots&&n-k&&n-k+1&&\cdots&&n \\ &k+1&k+2&&\cdots&&n&&1&&\cdots&&k\end{aligned}\right)$$

时，$c(g)=\gcd(k,n)$

$$\begin{aligned}ans&=\dfrac1{|G|}\sum\limits_{g\in G}m^{c(g)} \\ &=\dfrac1n\sum\limits_{i=1}^nn^{(i,n)} \\ &=\dfrac1n\sum\limits_{d|n}n^d\sum\limits_{i=1}^n[(i,n)=d] \\ &=\dfrac1n\sum\limits_{d|n}n^d\sum\limits_{i=1}^{\lfloor\frac nd\rfloor}[(i\cdot d,n)=d] \\ &=\dfrac1n\sum\limits_{d|n}n^d\sum\limits_{i=1}^{\lfloor\frac nd\rfloor}[(i,\dfrac nd)=1] \\ &=\dfrac1n\sum\limits_{d|n}n^d\varphi(\dfrac nd)\end{aligned}$$

虽然是多组询问，但是依然可以$O(\sqrt n)$求$\varphi$，复杂度$O(Tn^{\frac34})$，当然，正确的方法是求出质因数后递归求出每个因数的$\varphi$，复杂度$O(T\sqrt n)$

**卡点：**无



**C++ Code：**

```cpp
#include <cstdio>
const int mod = 1e9 + 7;

namespace Math {
	inline int getphi(int x) {
		int res = x;
		for (register int i = 2; i * i <= x; ++i) if (x % i == 0) {
			res = res / i * (i - 1);
			while (x % i == 0) x /= i;
		}
		if (x > 1) res = res / x * (x - 1);
		return res;
	}

	inline int pw(int base, int p) {
		static int res;
		for (res = 1; p; p >>= 1, base = static_cast<long long> (base) * base % mod) if (p & 1) res = static_cast<long long> (res) * base % mod;
		return res;
	}
	inline int inv(int x) { return pw(x, mod - 2); }
}

inline void reduce(int &x) { x += x >> 31 & mod; }

int Tim, n, ans;
inline int get(int d) {
	return static_cast<long long> (Math::pw(n, d)) * Math::getphi(n / d) % mod;
}

int main() {
	scanf("%d", &Tim);
	while (Tim --> 0) {
		scanf("%d", &n);
		ans = 0;
		for (int i = 1; i * i <= n; ++i) if (n % i == 0) {
			reduce(ans += get(i) - mod);
			if (i != n / i) reduce(ans += get(n / i) - mod);
		}
		printf("%lld\n", static_cast<long long> (ans) * Math::inv(n) % mod);
	}
	return 0;
}

```



---

## 作者：Vocalise (赞：11)

Pólya 定理在计数方面可以统计「本质不同」的方案个数。

下面从群论的基础开始讲起。

感谢 @Soulist

## 群

定义一个集合与作用在其上的二元运算 $(G,\times)$，若其具有：

1. 封闭性：对于 $a,b\in G$，$a\times b\in G$。
2. 结合律：对于 $a,b,c\in G$，$(a\times b)\times c = a\times(b\times c)$。
3. 单位元：记为 $e$，对于 $a\in G$，$a\times e = e\times a = a$。
4. 逆元：对于 $a\in G$，存在唯一的逆元记为 $a^{-1}\in G$，使 $a\times a^{-1} = a^{-1}\times a = e$。

下文中「群的运算」都记为通常的乘法标记 $\times$。

## 一些性质/定义

群的**阶**: 群中元素的个数。记作 $|T|$.

### 子群

$G$ 和 $T$ 是两个群，它们的运算相同，且 $T$ 的集合被 $G$ 的集合包含。记作 $T\le G$。

下文中沿用 $T$ 是 $G$ 的子群讨论一些性质/定理。

### 陪集

对于任意 $g\in G$，记 $gT$ 为 $G$ 的一个左陪集，表示 $\forall h\in T$ 变为 $g\times h$。$Tg$ 称为右陪集，表示 $\forall h$ 变为 $h\times g$。

下文只讨论左陪集。

$G/T$ 表示 $G$ 中所有 $T$ 的左陪集；

$[G:T]$ 表示 $G$ 中所有 $T$ 的左陪集数量，即 $\left|G/T\right|$。

有重要的性质：$g\in T$ 与 $gT = T$ 等价。由封闭性易得。

### 群作用

分为左群作用和右群作用，下面讨论左群。

对于集合 $S$ 的任意元素 $a$，若对于群 $G$ 的元素 $v,u$ 和单位元 $e$ 有映射 $G\times S\to S$ 记作二元运算 $\circ$，使得

$$ e\circ a = a $$

$$ (v\times u)\circ a = v\circ (u\circ a) $$

则称 $G$ 作用在 $S$ 上。下文沿用 $\circ$ 记号。

一般的理解就是群的作用效果可以以一定方式推广到一个集合上，虽然该集合不一定具备群的性质。

下文中会有例子，如：一个有标号环从某个点开始的标号序列与旋转该环操作构成的群，作用在每个点的颜色构成的序列上。

### 置换群

**置换**是「映射」的一种，是指非空集到它本身的**双射**。

经常讨论的是集合 $S = \{a_1,a_2,\cdots,a_n\}$ 上的置换群。

对于该集合，最大的置换群是 $n$ **元对称群**，其阶为 $n!$，可理解为全排列。所有 $n$ 元置换群都是它的子群。

一个置换一般写作：

$$g = \begin{pmatrix}a_1,a_2,\cdots,a_n\\a_{p1},a_{p2},\cdots,a_{pn}\end{pmatrix}$$

如默认上一行是 $(a_1,a_2,\cdots,a_n)$，则也许会省略掉。

有定理：一个 $n$ 元置换可以表示为若干循环循环置换的置换的乘积。顺序选取若干元素 $(a_{p1},a_{p2},\cdots,a_{pn})$，它们的循环置换是：

$$\begin{pmatrix}
a_{p1},a_{p2},\cdots,a_{pn}\\
a_{p2},a_{p3},\cdots,a_{p1}
\end{pmatrix}$$

该定理也比较显然。把每个置换看作一条有向边，$n$ 个点的图中每个点都有一条出边，形成的图由多个环组成。一个置换的**轮换**就是图上环的集合。

## 拉格朗日定理

若 $T$ 是 $G$ 的子群，则

$$ |T|\times [G:T] = |G| $$

证明：首先有 $g\in G$，则 $|gT| = |T|$。

比较显然：已知 $T$ 的元素到 $gT$ 的元素有一个映射，则 $|gT|\le |T|$；如果 $|gT| < |T|$，则一定会有 $v,u\in T,v\not=u$，$g\times v = g\times u$，发现 $g$ 是可乘上 $g^{-1}$ 消去的，则不存在这样的 $v,u$。

然后有 $\forall g_1,g_2\in G$，$g_1T\cap g_2T=\varnothing$ 或 $g_1T = g_2T$。

设 $g_1T\cap g_2T$ 中有元素 $v$，则 $g_1^{-1}\times v,g_2^{-1}\times v\in T$，$g_1^{-1}\times v\times(g_2^{-1}\times v)^{-1}=g_1^{-1}\times v\times v^{-1}\times g_2 = g_1^{-1}\times g_2\in T$。

结合陪集性质，$(g_1^{-1}\times g_2)T = T$，两边同时左乘 $g_1$ 变换，得到 $g_1T = g_2T$。

如果不存在 $v$，则无上述过程。

因此可知：$T$ 在 $G$ 中每个本质不同的陪集阶都为 $|T|$，且互不相交。显然这些陪集的并就是 $G$（因为仅单位元 $e$ 左乘所有元素就可以得到 $G$ 的所有元素），所以拉格朗日定理得证。

## 轨道-稳定子定理

下文中讨论的群 $T$ 作用在集合 $S$ 上，$x\in S$。

记 $T^x$ 为 $T$ 中作用于 $x$ 上使它没有变化的元素集合。该集合称为 $x$ 的**稳定子**。

记 $T(x)$ 为 $T$ 中所有元素作用在 $x$ 上得到的集合。该集合称为 $x$ 的**轨道**。

轨道-稳定子定理指出：

$$|T^x|\times |T(x)| = |T|$$

对任意 $x\in S$ 都成立。

证明：首先证明 $T^x$ 是 $T$ 的子群，然后运用拉格朗日定理。

$T^x$ 的元素显然都属于 $T$，下面指出它具有群的性质。

1. 封闭性：对于 $a,b\in T^x$，$a\circ x = b\circ x = x$，则群作用的性质 $(a\times b)\circ x = x$，得到 $a\times b\in T^x$，得证。
2. 结合律：显然。
3. 单位元：显然 $T$ 的单位元 $e$ 有 $e\circ x = x$，$e\in T^x$。
4. 逆元：由于 $e\in T^x$，对于 $a\in T^x$ 有 $e\circ x = (a^{-1}\times a)\circ x = a^{-1}\circ(a\circ x) = x$，取 $T$ 中的逆元即可。

于是得证。

运用拉格朗日定理 $|T^x|\times[T:T^x] = |T|$，我们只需要证明 $[T:T^x] = |T(x)|$。

即：$x$ 的稳定子群陪集的个数等于其轨道的大小。

尝试建立双射关系。对于 $g\in T$，我们用 $gT^x$ 对应一个稳定子群的陪集。

对于 $f\circ x = g\circ x$，它们是轨道中的相同元素。则同时左乘 $g^{-1}$ 得到 $(g^{-1}\times f)\circ x = e\circ x$，$g^{-1}\times f\in T^x$，$(g^{-1}\times f)T^x = T^x$，$fT^x = gT^x$。

另外对于 $fT^x = gT^x$ 也有 $g^{-1}\times f\in T^x$，$f\circ x = g\circ x$。于是得证。

## Burnside 引理

定义：若 $x,y\in S$，且存在 $g\in T$ 使 $g\circ x = y$，则同样有 $g^{-1}\circ y = x$，称 $x,y$ 是本质相同的。

有记号：$S/T$ 表示在 $T$ 的作用下本质不同的每种种类元素集合的集合，即按颜色划分为若干块。

上文有记号 $T^x$ 是 $x$ 在 $T$ 作用下的稳定集合，这里类似地引入 $S^g$ 表示 $g$ 作用下 $S$ 中不改变的元素集合。

Burnside 引理指出

$$ |S/T| = \frac 1{|T|}\sum_{g\in T}|S^g| $$

发现后求和式本质和枚举 $T^x$ 是一样的，~~但是定理就是这样。~~

则

$$ |S/T| = \frac 1{|T|}\sum_{x\in S}|T^x| $$

运用轨道-稳定子定理：

$$ \begin{aligned}
&\quad\frac 1{|T|}\sum_{x\in S}T^x = \sum_{x\in S}\frac{|T^x|}{|T|} = \sum_{x\in S}\frac 1{|T(x)|} \\
&= \sum_{G\in S/T}\sum_{x\in G}\frac 1{|T(x)|}
= \sum_{G\in S/T}\sum_{x\in G}\frac 1{|G|} \\
&= \sum_{G\in S/T}1 = |S/T|
\end{aligned} $$

其核心在于每种颜色不相交，以及同种颜色中每个元素的轨道都为该颜色集合。

## Pólya 定理

Pólya 定理和 Burnside 引理类似。但我们的问题细化一些：

我们给 $S$ 中每一个元素染色，统计 $T$ 作用下本质不同的染色方案数。

已经介绍轮换的概念，记 $c(g)$ 为 $g$ 中的轮换个数，$N$ 为颜色集合。

$$ |S/T| = \frac 1{|T|}\sum_{g\in T}|N|^{c(g)} $$

对于它，我们只考虑证明 $|N|^{c(g)} = |S^g|$。

发现每个轮换等价于一个连通块（$n$ 个点 $n$ 条出边），$S^g$ 中必然是每个轮换染相同的颜色即可，每个轮换自然有 $|N|$ 种方案，也就是 $|N|^{c(g)}$ 了。

---

## [P4980 【模板】Pólya 定理](https://www.luogu.com.cn/problem/P4980)

比较单纯的问题，循环置换群作用在长度为 $n$，$n$ 种颜色的颜色序列集合上，求本质不同的方案数。

循环置换按长度有 $0\sim n-1$ 有 $n$ 个分别为 $p_0\sim p_{n-1}$。则：

$$ |S/T| = \frac 1n\sum_{i=0}^{n-1}n^{c(p_i)} $$

考虑 $c(p_i)$。

一个轮换经过了若干次全长 $n$，同时又由若干个 $i$ 步长组成，因此一个轮换的长度是 $\operatorname{lcm}(i,n)$。每个元素在且仅在一个轮换中，因此若干个轮换的总长是 $i\times n$。

得到结论：旋转 $i$ 次的轮换有 $\dfrac{i\times n}{\operatorname{lcm}(i,n)} = \gcd(i,n)$ 个。

但是 $\gcd(0,n)$ 不好处理，我们认为旋转 $0$ 次是旋转 $n$ 次，原式为：

$$ |S/T| = \frac 1n\sum_{i=1}^nn^{\gcd(n,i)} $$

求这个式子是容易的，不展开来讲。

$$ \begin{aligned}
|S/T| &= \frac 1n\sum_{d|n}n^d\sum_{i=1}^n[\gcd(n,i) = d] \\
&= \frac 1n\sum_{d|n}n^d\sum_{i=1}^{n/d}[\gcd(\frac nd,i)=1] \\
&= \frac 1n\sum_{d|n}n^d\varphi(\frac nd)
\end{aligned} $$

暴力枚举约数，$O(\sqrt n)$ 求 $\varphi$，$O(\log n)$ 求快速幂可以过。	

但是显然可以筛素因子做到 $O(Td(n)\log n)\approx O(Tn^{\frac{1.066}{\ln\ln n}}\log n)$，$10^9$ 中大约是 $O(Tn^{\frac 13}\log n)$。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

const int p = 1000000007;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
	return x * f;
}

int fastpow(int a,int b) {
	int res = 1;
	while(b) {
		if(b & 1) res = 1ll * res * a % p;
		a = 1ll * a * a % p;
		b >>= 1;
	}
	return res;
}

int n;

int phi(int n) {
	int res = n;
	for(int i = 2;i * i <= n;i++) {
		if(n % i) continue;
		res -= res / i;
		while(!(n % i)) n /= i;
	}
	if(n > 1) res -= res / n;
	return res;
}

int f(int d) {
	return 1ll * fastpow(n,d) * phi(n / d) % p;
}

void Solve() {
	n = read(); int ans = 0,d;
	for(d = 1;d * d < n;d++)
		if(!(n % d)) {
			ans = (ans + f(d)) % p;
			ans = (ans + f(n / d)) % p;
		}
	if(d * d == n) ans = (ans + f(d)) % p;
	std::printf("%lld\n",1ll * ans * fastpow(n,p - 2) % p);
	return;
}

int main() {
	int t = read();
	while(t--) Solve();
	return 0;
}

```

---

## 作者：周道_Althen (赞：7)

~~先放个广告，感觉讲得海星吧233   [我的博客——群论初步](https://www.luogu.org/blog/Althen-Way-Satan/chao-di-neng-xie-du-qun-lun)~~



------------


### 先甩Pólya定理定义：

![](http://wx4.sinaimg.cn/mw690/0060lm7Tly1furjcufjasj311x053qa6.jpg)

即：

**设置大小为$|G|$，由$g$组成的群$G$，作用于$k$组合成的有限集合$X$上面，那么$X$在$G$内映射的作用下，$X$的变换结果种类有这么多：**

$$\frac {\sum_{g\in G}^{} {k^{m(g)}}} {|G|}$$

------------

我们先来看一下这个本题这个群的映射方式：


## 旋转

画一下草图仔细观察一下，我们可以发现具体群内的映射有如下规律：

## 旋转一共有$n$个角度

顺时针旋转$i$格的置换中，每个循环的长度为$\frac{n}{{\rm gcd}(i,n)}$，个数为${\rm gcd}(i,n)$；

直接套入公式中，我们要的答案就是：

$$ans(n)=\frac{\sum_{i=1}^{n}n^{{\rm gcd}(i,n)}}{n}$$

复杂度为${\rm O}(Tn{\rm log}n)$，过不去很尴尬，于是我们尝试将它化简：

$$\begin{aligned}\frac{\sum_{i=1}^{n}n^{{\rm gcd}(i,n)}}{n}&=\frac{\sum_{e=1}^{n}n^e \sum_{i=1}^{n}\left[{\rm gcd}(i,n)=e\right]}{n} \\ &=\frac{\sum_{e|n}n^e \sum_{i=1}^{\frac{n}{e}}\left[{\rm gcd}(i,\frac{n}{e})=1\right]}{n} \\ &=\frac{\sum_{e|n}n^e \varphi\left(\frac{n}{e}\right)}{n}\end{aligned}$$

因为n比较大，我们选择在线处理$\varphi$，那么总体复杂度是$O(Tn^{\frac{3}{4}}logn)$，就差不多卡过了，跑得比较慢。

- 附上标程代码：

```cpp#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<cmath>
#include<map>
#include<set>
using namespace std;
const int inf=0x7fffffff;
const double eps=1e-10;
const double pi=acos(-1.0);
//char buf[1<<15],*S=buf,*T=buf;
//char getch(){return S==T&&(T=(S=buf)+fread(buf,1,1<<15,stdin),S==T)?0:*S++;}
inline int read(){
	int x=0,f=1;char ch;ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch&15);ch=getchar();}
	if(f)return x;else return -x;
}
const long long mod=1e9+7;
int n;
long long rak,k;
map<long long,long long> mp;
long long phi(long long a){
  if(mp.count(a))return mp[a];
  long long t=a,tmp=a;
  for(long long j=2;j*j<=tmp;j++)
	{if(t%j==0){a=a/j*(j-1);while(t%j==0) t/=j;}}
    if(t>1)a=a/t*(t-1);mp[tmp]=a;
  return a;
}
long long power(long long a,long long b){
  long long ans=1;
  for(;b;b>>=1,a=(a*a)%mod)if(b&1)ans=(ans*a)%mod;
  return ans;
}
long long calc(long long e){return phi(n/e)*power(k,e)%mod;}
long long getans(long long n,long long k){
  long long ans=0;
  for(long long i=1;i*i<=n;i++){
    if(n%i) continue;
    long long a=i,b=n/i;
    ans=(ans+calc(a))%mod;
    if(a!=b)ans=(ans+calc(b))%mod;
  }
  return ans;
}
int op;
long long ans;
int main(){
  op=read();
  while(op--){
  	k=n=read();
    ans=getans(n,k);
    ans=(ans*power(n,mod-2))%mod;
  	printf("%lld\n",ans);
  };
  return 0;
}

```

最后建议改成$n$个点，$m$种颜色来涂好一点，身为模板的通用性更好，还有对于翻转应该也加一个部分分什么的。~~个人意见~~

[~~我出的加强模板题~~](https://www.luogu.org/problemnew/show/T47779)

---

## 作者：Liuxizai (赞：6)

[$\color{red}\LARGE{My\ Blog}$](https://liuxizai.ac.cn/post/solution-p4980-mo-ban-polya-ding-li/)

## $Description$

给定一个$n$个点，$n$条边的环，有$n$种颜色，给每个顶点染色，问有多少种**本质不同**的染色方案。

## $Solution$

$$
\begin{aligned}
|S/T|&=\frac1n\sum\limits_{i-0}^{n-1}n^{c(p_i)}\\
&=\frac1n\sum\limits_{i=1}^nn^{gcd(i,n)}\\
&=\frac1n\sum\limits_{k|n}n^k\sum\limits^n_{i=1}[gcd(i,n)=k]\\
&=\frac1n\sum\limits_{k|n}n^k\sum\limits_{i=1}^{n/k}[gcd(i,\frac nk)=1]\\
&=\frac1n\sum\limits_{k|n}n^k\varphi(\frac kn)
\end{aligned}
$$

- $(1)$ 由$Pólya$定理可得，$c$是循环节数。
- $(2)$ 可以发现$p_i$中，对于环上的点$m$，其会旋转到$(m+i)\mod n$这个点上，于是可以得到$p_i$中每个循环的长度都是$lcm(i,n)$，于是易得$c(p_i)=\frac{in}{lcm(i,n)}=gcd(i,n)$。
- $(3)$ 考虑枚举$gcd$的取值。
- $(4)$ 整体除$k$。
- $(5)$ 可以发现$\sum\limits_{i=1}^{n/k}[gcd(i,\frac nk)=1]$实际上就是$\varphi(\frac kn)$。

拿到$(5)$式后，就可以$O(\log n)$的复杂度快速幂，然后$O(\sqrt{n})$的复杂度算欧拉函数，$O(\sqrt{n})$的复杂度枚举$k$。

这样直接暴力打就能够过掉本题。

## $AC\ Code$

```cpp
#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
const int MOD = 1e9+7;
int t, n;
LL read(){
	ll n = 0; int f = 1; char ch = getchar();
	while('0' > ch || ch > '9'){
		if(ch == '-') f *= -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9'){
		n = (n << 1) + (n << 3) + ch-'0';
		ch = getchar();
	}
	return f * n;
}
Void write(ll x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
    arg = read();
    input(args...);
}
Int phi(int x){
    int rt = x, yx = x;
    for(ri i = 2; i * i <= yx; i++){
        if(x % i == 0){
            rt = rt * (i-1) / i % MOD;
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) rt = rt * (x-1) / x;
    return rt;
}
LL qpow(int a, int k){
    ll rt = 1, t = a;
    while(k > 0){
        if(k & 1) rt = (ll)rt * t % MOD;
        t = t * t % MOD;
        k >>= 1;
    }
    return rt;
}
signed main(){
    input(t);
    while(t--){
        input(n);
        int ans = 0;
        for(ri i = 1; i * i <= n; i++){
            if(n % i != 0) continue;
            ans = (ans + qpow(n, i) * phi(n/i) % MOD) % MOD;
            if(i * i != n) ans = (ans + qpow(n, n/i) * phi(i) % MOD) % MOD;
        }
        write(ans*qpow(n, MOD-2)%MOD), puts("");
    }
	return 0;
}
```

---

## 作者：MakiseVon (赞：6)

更好的阅读体验： [Pólya Theorem & Burnside Lemma](//makisevon.net/algorithm/math/pólya-theorem)

洛谷的公式好像有 *`BUG`* ，部分公式怎么调都炸了 orz  
最后没办法换成图片了 qwq  
嘛~ 将就着看嘛 233

---

#### Tutorial

*`Pólya`* 定理，常用于处理组合数学中求本质不同方案数的问题。  
而 *`Burnside`* 引理则是 *`Pólya`* 定理的基础。  
下面将给出一些前置知识，然后证明这两个小可爱 ~

---

#### Propaedeutics

给定一些状态的全体集合 $S$ 和 $S$ 上的一个置换群 $\left(G,\cdot\right)$ .  
对 $\forall k\in S$ ，记 $Z_k=\left\{f\big|f\in G,f\left(k\right)=k\right\}$ .  
显然，对 $\forall k\in S$ 有恒等置换 $e\in Z_k$ ，故 $\left|Z_k\right|\neq0$ .  
对 $\forall a,b\in S$ ，若 $\exists f\in G,f\left(a\right)=b$ ，则称 $a,b$ 是 $G$ 等价的。  
显然，对 $\forall a,b,c\in S$ 有：

- $e\left(a\right)=a$ .
- 若 $\exists f\in G,f\left(a\right)=b$ ，则 $\exists f^{-1}\in G,f^{-1}\left(b\right)=a$ .
- 若 $\exists f,g\in G,f\left(a\right)=b,g\left(b\right)=c$ ，则 $\exists gf\in G,gf\left(a\right)=g\left(f\left(a\right)\right)=c$ .

即 $G$ 等价关系满足自反性、对称性和传递性，则 $G$ 等价关系是 $S$ 上的等价关系。  
故 $G$ 等价关系可将 $S$ 划分为若干等价类，称为 $G$ 诱导的 $S$ 的等价类。  
对 $\forall k\in S$ ，记 $k$ 所在的等价类为 $E_k$ ，即 $E_k=\left\{x\big|\exists f\in G,f\left(k\right)=x\right\}$ .

---

#### Main

一般情况下，相关问题均可转化为这样一个问题：  
给定一些 $n$ 元状态的全体集合 $S$ 和 $S$ 上的一个置换群 $\left(G,\cdot\right)$ .  
$S$ 中状态的每个元均有 $m$ 种状态，求 $G$ 诱导的 $S$ 的等价类数目 $l$ .

##### *`Burnside Lemma`*

对 $\forall f\in G$ ，记

$$
cnt\left(f\right)=\sum_{x\in S}\left[f\left(x\right)=x\right]
$$

则

$$
l=\frac{1}{\left|G\right|}\sum_{f\in G}cnt\left(f\right)
$$

*`Proof`*

对 $\forall k\in S$ ，设 $\left|E_k\right|=s,E_k=\left\{a_1,a_2,\cdots,a_s\right\}$ ，其中 $a_1=k$ .  
由 $E_k$ 定义，对 $\forall i\in\left[1,s\right]$ 满足 $\exists f_i\in G,f_i\left(k\right)=a_i$ ，记 $f_iZ_k=\left\{f_ig\big|g\in Z_k\right\}$ .   
显然，对 $\forall i,j\in\left[1,s\right]$ 有：

- $\left|f_iZ_k\right|=\left|Z_k\right|$ .
- 若 $i\neq j$ ，则 $f_iZ_k\cap f_jZ_k=\varnothing$ .

而

$$
\bigcup_{i=1}^sf_iZ_k\subseteq G
$$

任取 $f\in G$ ，设 $f\left(k\right)=a_x\left(x\in\left[1,s\right]\right)$ ，则

$$
f_x^{-1}f\left(k\right)=f_x^{-1}\left(f\left(k\right)\right)=f_x^{-1}\left(a_x\right)=k
$$

有 $f_x^{-1}f\in Z_k,f\in f_xZ_k$ .  
则

$$
G\subseteq\bigcup_{i=1}^sf_iZ_k
$$

即

$$
G=\bigcup_{i=1}^sf_iZ_k
$$

故

$$
\left|G\right|=\sum_{i=1}^s\left|f_iZ_k\right|=s\left|Z_k\right|=\left|E_k\right|\left|Z_k\right|
$$

对 $\forall i\in\left[1,l\right]$ ，记 $x_i$ 为第 $i$ 个等价类的代表元素。
则

![](https://cdn.luogu.com.cn/upload/image_hosting/70jr1ywz.png)

故

$$
l=\frac{1}{\left|G\right|}\sum_{f\in G}cnt\left(f\right)
$$

*`QED`*

##### *`Pólya Theorem`*

对 $\forall f\in G$ ，记 $rotate\left(f\right)$ 为 $f$ 表示成不相杂轮换之积时轮换的数目，则

$$
l=\frac{1}{\left|G\right|}\sum_{f\in G}m^{rotate\left(f\right)}
$$

*`Proof`*

对 $\forall f\in G$ ，令 $r=rotate\left(f\right)$ ，设

$$
f=\prod_{i=1}^rh_i
$$

其中 $h_1,h_2,\cdots,h_r$ 为不相杂的 $r$ 个轮换，且

$$
\sum_{i=1}^r\left|h_i\right|=n
$$

对 $\forall i,j\in\left[1,r\right]$ ，若 $i\neq j$ ，则 $h_i$ 和 $h_j$ 对状态的影响是独立且互不干涉的。  
若 $\exists x\in S,f\left(x\right)=x$ ，则对 $\forall i\in\left[1,r\right],h_i\left(x\right)=x$ .  
故 $x$ 受 $h_i$ 影响的元的状态应相同，且有 $m$ 种选择。  
故

$$
cnt\left(f\right)=m^{rotate\left(f\right)}
$$

$$
l=\frac{1}{\left|G\right|}\sum_{f\in G}m^{rotate\left(f\right)}
$$

*`QED`*

可以看出， *`Pólya`* 定理实际上就是给出了 *`Burnside`* 引理中 $cnt\left(f\right)$ 的具体计算方法。

---

#### Exemple Problem

##### Description

给定一个 $n$ 个点， $n$ 条边的环，以及 $n$ 种颜色 $\left(1\leq n\leq10^9\right)$ .  
现给环上的每个点染色，求本质不同的染色方案数，答案对 $10^9+7$ 取模。  
本质不同指的是不能通过旋转变得与其他染色方案相同。  
共 $t$ $\left(1\leq t\leq10^3\right)$ 组测试。

##### Solution

问题可转化为：  
给定一些 $n$ 元状态的全体集合 $S$ 和 $S$ 上的一个置换群 $\left(G,\cdot\right)$ .  
$S$ 中状态的每个元均有 $n$ 种状态， $G$ 中共 $n$ 个置换。  
对 $\forall i\in\left[1,n\right]$ ，记 $f_i\in G$ 为顺时针旋转 $i$ 个单位的置换。  
求 $G$ 诱导的 $S$ 的等价类数目。

直接应用 *`Pólya`* 定理，得

![](https://cdn.luogu.com.cn/upload/image_hosting/nxj2zsw6.png)

考虑如何求 $rotate\left(f_i\right)$ .
将 $f_i$ 表示为不相杂轮换之积，考虑其中一个轮换 $h$ .  
显然 $\left|h\right|=\frac{\operatorname{lcm}\left(n,i\right)}{i}=\frac{n}{\gcd\left(n,i\right)}$ ，则 $rotate\left(f_i\right)=\frac{n}{\left|h\right|}=\gcd\left(n,i\right)$ .  
故

$$
ans=\sum_{i=1}^nn^{\gcd\left(n,i\right)-1}
$$

枚举 $\gcd$ ，得

![](https://cdn.luogu.com.cn/upload/image_hosting/f99e4q9u.png)

设唯一分解后

$$
n=\prod_{i=1}^mp_i^{k_i}
$$

对 $\forall i\in\left[1,m\right]$ ，预处理 $\varphi\left(p_i\right),\varphi\left(p_i^2\right),\cdots,\varphi\left(p_i^{k_i}\right)$ .  
通过枚举 $p_i$ 的指数枚举 $d$ 即可在 $O\left(1\right)$ 的时间内求 $\varphi\left(\frac{n}{d}\right)$ .

时间复杂度： $O\left(t\sqrt n\log n\right)$ .

##### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int p = 1e9 + 7;
const int M = 35;
int t, n;
int ct, pri[N], idx[N];
int px[N][M], phi[N][M];
int sqr, ans;

void solve(void);
void rec(int x = 1, int d = 1, int p1 = 1, int p2 = 1);
int qpow(int a, int b);

int main(void) {
    scanf("%d", &t);
    while(t--) solve();
    return 0;
}

void solve(void) {
    scanf("%d", &n), ct = 0, sqr = sqrt(n);
    int g = n;
    for(int i = 2; i <= sqr; i++) {
        if(g % i) continue;
        pri[++ct] = i, idx[ct] = 0;
        px[ct][0] = phi[ct][0] = 1, phi[ct][1] = i - 1;
        for(int j = 1; !(g % i); j++) {
            idx[ct]++, g /= i, px[ct][j] = i * px[ct][j - 1];
            if(j > 1) phi[ct][j] = i * phi[ct][j - 1];
        }
    }
    if(g > 1) {
        pri[++ct] = g, idx[ct] = 1, px[ct][1] = g;
        px[ct][0] = phi[ct][0] = 1, phi[ct][1] = g - 1;
    }
    ans = 0, rec(), printf("%d\n", ans);
}

void rec(int x, int d, int p1, int p2) {
    if(x > ct) {
        ans = (ans + qpow(n, d - 1) * 1ll * p1 % p) % p;
        if(d * d < n) ans = (ans + qpow(n, n / d - 1) * 1ll * p2 % p) % p;
        return;
    }
    for(int i = 0; i <= idx[x] && d * px[x][i] <= sqr; i++)
        rec(x + 1, d * px[x][i], p1 * phi[x][idx[x] - i], p2 * phi[x][i]);
}

int qpow(int a, int b) {
    int r = 1;
    for(; b; a = a * 1ll * a % p, b >>= 1)
        if(b & 1) r = r * 1ll * a % p;
    return r;
}
```

---

## 作者：ThinkofBlank (赞：6)

提供一个新算法。。。

首先,我们来分析一下题目:

#### 给一个有n个点的环图n种颜色，问本质不同的方案数

那么，很明显的，这是一个polya定理（废话，题目名说明了一切）

我们先来看看这道题的“操作”，很明显的操作就是只有一个——平移（有人说旋转，但我个人更喜欢看成平移。。。）

我们就可以开始枚举置换了

#### 首先，我们枚举每次平移的单位长度，那么很明显的本质不同的平移有n种，分别是平移0-(n-1)个单位

可以发现，每一种平移方案就是一种置换

所以，我们可以枚举平移长度，假设现在单步平移i个单位，那么要使得序列"平移"回来，我们假设最少要k步。那么k一定满足:i*k%n==0，可以解得k=lcm(n,i)/i=n/gcd(n,i)，所以就有n/k=gcd(n,i)个"循环",故而，根据polya定理，当前置换的"不动点"数为n(颜色数)^gcd(n,i),为了简写，我们把这一坨设为s[i]。

#### 最后，由burnside引理，我们可以知道，方案数为$\frac{sum_{i=0}^{n-1}s[i]}{n}$%$mod$

于是我们可以打出代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
inline int ksm(int x,int y,int z){
	int ans=1;
	while(y){
		if(y&1){
			ans=(1LL*ans*x)%z;
		}
		x=(1LL*x*x)%z;
		y>>=1;
	}
	return ans%z;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		int ans=0;
		for(int i=0;i<n;++i){
			ans+=ksm(n,__gcd(n,i),mod);
			ans%=mod; 
		}
		ans=(1LL*ans*ksm(n,mod-2,mod))%mod;//逆元 
		printf("%d\n",ans);
	}
	return 0;
}
```

然后，它就T了。。。qwq

那么，我们该怎么优化这个程序呢？

————————————————以下是正文——————————————————

#### 我们不难注意到，对于使得gcd(n,i)相同的i，对答案的贡献是一样的(先不管除以n)，为n^gcd(n,i)，那么，我们不妨就枚举gcd(n,i)!

因为枚举gcd(n,i)等价与枚举n的约数，所以，我们枚举部分的复杂度就降为了$O(\sqrt{n})$,所以，现在我们需要做的就是尽量快速的计算这个问题:

#### 给出n的一个约数i，求0-(n-1)中有多少个数与n的gcd为i

我们先把i=1和i=n的情况算出来(为了方便)。

i=1时，满足条件的一共有φ(n)个，i=n时一个有一个(gcd(0,n)=n)

所以，这两个的答案和为Ans1=(φ(n)*n+n^n)%mod

那么，我们再来看看剩下的该怎么算

我们发现，求0-(n-1)中有多少个数与n的gcd为i,因为i不等于1和n,所以问题等价于

#### 求1-n中有多少个数与n的gcd为i。

#### 而我们可以发现，满足条件的数一定是i的倍数。所以，问题又等价于:枚举1-n/i中，有多少个数j满足gcd(n,j*i)=i

#### 等价于求1-n/i中有多少个数j满足gcd(n/i,j)=1，很明显，这个问题的答案就是φ(n/i)

（为什么转化了这么多步啊！抓狂ing。。。）

#### 那么，我们就需要较快的求φ(x)了

本来，我们可以通过预处理，用O(n)的时间求出所有的φ，但，问题是n<=1e9，时间上如果优秀的话，估计可能卡过，但空间上就明显不允许了，所以，我们必须找到一个较好的方法。

我们知道，φ是一个积性函数，所以，我们可以根据它的性质，找到它的一个质因数，然后递归求解。。。

#### 参照杜教筛，我们可以先将较小的φ预处理出来(我是预处理到1e7)

#### 然后，我们先用Miller_rabin算法判断x是否是质数，如果是，我们就返回x-1,否则,我们就可以用pollard_rho算法来分解x，递归求解，中间可以套个map来加速。问题得解。

#### 当然，记得特判下n=1的答案(因为一开始我们同时统计了i=1和i=n的答案，于是对于1，就多算了一次)

半伪代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7,N=1e7+1;
map<int,int>f;
int T,fi[N],zhi[N>>1],e;
inline int ksm(int x,int y,int z){
	int ans=1;
	while(y){
		if(y&1){
			ans=(1LL*ans*x)%z;
		}
		x=(1LL*x*x)%z;
		y>>=1;
	}
	return ans;
}
inline void sai(int maxe){
	T=maxe;fi[1]=1;
	for(int i=2;i<=maxe;++i){
		if(!fi[i]){
			fi[i]=i-1;zhi[++e]=i;
		}
		for(int j=1;j<=e;++j){
			if(i*zhi[j]>maxe){
				break;
			}
			if(i%zhi[j]==0){
				fi[i*zhi[j]]=fi[i]*zhi[j];
				break;
			}
			fi[i*zhi[j]]=fi[i]*fi[zhi[j]];
		}
	}
}
inline bool Miller_rabin(int x){
	//偷懒省略 
}
inline int pollard_rho(int x){
	//偷懒省略 
}
inline int calc(int x){
	if(x<=T){
		return fi[x];
	}
	if(f.find(x)!=f.end()){
		return f[x];
	}
	int ret=pollard_rho(x);
	if(ret==x){
		return x-1;
	}
	return f[x]=((x/ret)%ret==0?ret*calc(x/ret):(ret-1)*calc(x/ret));
}
int main(){
	srand(1);
	sai(1e7);//预处理 
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);	
        if(n==1){
            puts("1");
            continue;
        }
		int ans=(ksm(n,n,mod)+(1LL*n*calc(n))%mod)%mod;
		for(int i=sqrt(n);i>=2;--i){//一次平移的距离
			if(n%i==0){
				ans+=(1LL*ksm(n,i,mod)*calc(n/i))%mod;
				ans%=mod;
				if(n/i!=i){
					ans+=(1LL*ksm(n,n/i,mod)*calc(i))%mod;
					ans%=mod;
				}
			}
		}
		ans=(1LL*ans*ksm(n,mod-2,mod))%mod;//逆元 
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：Jμdge (赞：6)

这道题可能没那么难？ 【雾，假的


反正就是只要知道 polya 定理然后会点反演套路的话，这道题就不难做
（学完莫比的我是这么觉得的）

简单点说， 假设要用 k 种颜色去染 n 个点，给出 m 个置换，求染色方案书

 polya 就是考虑对于置换群 G 中的一个置换 $g_i$ ，用 $c(g_i)$ 表示 $g_i$ 的循环节个数，那么染色方案数就是：
 
 $$ANS={1\over |G|}\sum_{i=1}^{m} k^{c(g_i)}$$


什么是循环节？比如有这样一个循环： 
$$(1,2,3)(4,5)(6)(7)(8,9,10,11,12)$$

那么循环个数就是 5 （其实就是括号的个数）

那么对于循环长度均为 x 的置换，循环节个数就是 $n\over x$ ，本题中的置换都是满足这个性质的（所以会稍微可做一些）

然后我们考虑答案是什么，答案其实就是：

 $$ANS={1\over n}\sum_{i=1}^{n} n^{(n,i)}$$

化式子：

 $$ANS={1\over n}\sum_{i=1}^{n} n^{(n,i)} \sum_{i|j}^{n} [(j,n)=i]$$

 $$ANS={1\over n}\sum_{i|n} n^{(n,i)} \sum_{j=1}^{n\over i} [(j,{n\over i})=1]$$



 $$ANS={1\over n}\sum_{i|n} n^{(n,i)} φ({n\over i})$$


那么单个 求 $φ$ 复杂度 $\sqrt n$ ，乍一看好像不对经，因为枚举因数也是 $\sqrt n$ 的，那么我们发现我们算的是约数的 $φ$ ，信仰一下就能过了（据说复杂度单次询问复杂度 $n^{3\over 4}$?反正我不会求）




```
//by Judge
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=(a),I=(b)+1;i<I;++i)
using namespace std;
const int mod=1e9+7;
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int mul(int x,int y){return 1ll*x*y%mod;}
inline void ADD(int& a,int b){a+=a+b>=mod?b-mod:b;}
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(int x,char chr='\n'){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]=chr;
} int n,ans;
inline int qpow(int x,int p=mod-2,int s=1){
	for(;p;p>>=1,x=mul(x,x)) if(p&1) s=mul(s,x); return s;
}
inline int getphi(int x){ int s=x;
	for(int i=2;i*i<=x;++i) if(!(x%i)){
		s=s/i*(i-1); while(!(x%i)) x/=i;
	} if(x>1) s=s/x*(x-1); return s;
}
inline int get(int d){
	return 1ll*qpow(n,d)*getphi(n/d)%mod;
}
int main(){int T=read();
	fp(kkk,1,T){ n=read(),ans=0;
		fp(i,1,sqrt(n)) if(!(n%i)){
			ADD(ans,get(i));
			if(i*i<n) ADD(ans,get(n/i));
		} print(mul(ans,qpow(n)));
	} return Ot(),0;
}
```





---

## 作者：Rorschachindark (赞：6)

# 【模板】Polya定理
[题目传送门](https://www.luogu.com.cn/problem/P4980)
## 题目大意
给定$n$,求长度为$n$的环用$n$种颜色染出来不同的个数。
## 思路
看到其他博客都是用的$\text {Polya}$定理做的，不过，$\text {Polya}$定理的题怎么能用$\text {Polya}$做呢？这里提供一种思路简单结果相同的想法，来自于《具体数学》。

我们定义$N(n,m)$为长度为$n$的环用$m$种颜色染的方案数。那么，我们就知道:

$$nN(n,m)=\sum_{k} \sum_{a_{1,2,3,...,n}} [a_{1,2,3,...,n}=a_{k+1,k+2,...,k}]$$

因为两边都是算的重复的个数。

我们举个例子，比如$n=12,k=8$，就可以得到:

$$a_1a_2a_3a_4a_5a_6a_7a_8a_9a_{10}a_{11}a_{12}=a_9a_{10}a_{11}a_{12}a_1a_2a_3a_4a_5a_6a_7a_8$$

就可以得到:

$$a_1=a_9=a_5$$

$$a_2=a_{10}=a_6$$

$$a_3=a_{11}=a_7$$

$$a_4=a_{12}=a_8$$

于是，就有$m^4$中方法使得$n=12,k=8$时满足$a_{1,2,3,...,n}=a_{k+1,k+2,...,k}$。

我们考虑拓展。我们发现$kl$的膜$n$的剩余系就是:

$$\{0,d,2d,3d,...,n-d\}$$

其中$d=gcd(n,k)$。这个显然易证。

所以，我们就可以得到:

$$nN(n,m)=\sum_{k} m^{gcd (n,k)}$$

但是这个式子并不简单，我们可以考虑进一步简化:

$$nN(n,m)=\sum_{k} m^{gcd (n,k)}$$

$$=\sum_ {k} \sum_{d} m^d [d=gcd(n,k)]$$

$$=\sum_{d} m^d \sum_{d|k} 1$$

$$=\sum_{d} m^d \sum_{k=1}^{\frac{n}{d}} [gcd(d,k)=1]$$

$$=\sum_{d} m^d \varphi (\frac{n}{d})$$

$$\therefore N(n,m)=\frac{1}{n} \sum_{d} m^d \varphi (\frac{n}{d})$$

这道题的答案实际上就是$N(n,n)$，直接预处理一下$\varphi$就好了，每次$\Theta(\sqrt n)$解决。

代码很简单，这里就不给出了。

---

## 作者：littlez_meow (赞：5)

群论初学者的题解！

[题目指路](https://www.luogu.com.cn/problem/P4980)

## 逃课做法
如果你想正常学习 Pólya 定理，可以跳过本节。

考虑把这个环的分成 $d$ 段，每段染色方案相同，那么设此时有 $f(d)$ 种方案（不是不同），我们就有以下两式：

1. $f(d)$ 每种方案被算了 $d$ 次，因此答案为 $\sum_{d|n}\frac{f(d)}d$。

2. 所有 $f(d)$ 之和等于染色总方案，根据乘法原理，等于 $n^n$,即 $\sum_{d|n} f(d)=n^n$。

而第二个式好巧不巧就是莫比乌斯变换的式子。记 $g(x)=n^x$，对 $g(x)$ 进行莫比乌斯反演，得到 $f(n)$ 的表达式：

$f(n)=\sum_{d|n} g(d)\mu(\frac n d)=\sum_{d|n}n^d\mu(\frac n d)$

带入原式开始计算。

答案 $=\sum\limits_{d|n}\dfrac{f(d)}d$

$=\sum\limits_{d|n}\dfrac 1 d\sum\limits_{k|d} n^k\mu(\dfrac d k)$

由于 $d$ 与 $\frac n d$ 相互对应，替换 $d$ 为 $\frac n d$。

$=\sum\limits_{d|n}\dfrac 1{\ \frac n d\ }\sum\limits_{k|\frac n d} n^k\mu(\dfrac{\ \frac n d\ }k)$

$=\sum\limits_{d|n}\dfrac d n\sum\limits_{k|\frac n d} n^k\mu(\dfrac n{dk})$

$=\sum\limits_{d|n} d\sum\limits_{k|\frac n d} n^{k-1}\mu(\dfrac n{dk})$

交换求和号

$=\sum\limits_{k|n} n^{k-1}\sum\limits_{d|\frac n k} d\mu(\dfrac n{dk})$

右边这一堆正好是 $id*\mu=\varphi$

$=\sum\limits_{k|n} n^{k-1}\varphi(\dfrac n k)$

## Pólya 定理做法

啊，你不想用逃课方法？好吧，那就和我一起学群论吧！

作为一名群论初学者，各位 dalao 可以选择性跳过。

### 群的基础知识

**【定义 1】（群）**
若存在集合 $G\neq\varnothing$和二元运算 $\sigma:G\times G\mapsto G$ 使得代数结构 $(G,\sigma)$ 满足以下四个性质：

1. 封闭性：$\forall a,b\in G,a\sigma b\in G$

2. 结合律：$\forall a,b,c\in G,(a\sigma b)\sigma c=a\times(b\times c)$

3. 单位元：$\exists e\in G,\forall a\in G,e\sigma a=a\sigma e=a$，此时称 $e$ 为该群的单位元（幺元），单位元是唯一的

4. 逆元：$\forall a\in G,\exists b\in G,a\sigma b=b\sigma a=e$，此时称 $b$ 为 $a$ 的逆元，记 $b=a^{-1}$，逆元是唯一的

则称代数结构 $(G,\sigma)$ 为一个群，有时也称 $G$ 是一个群。

为了方便，将二元运算 $\sigma$ 记为 $\times$ 或 $\cdot$，注意与数之间的乘法相区分。

举几个栗子：整数集和整数集上的加法 $(\mathbb{Z},+)$ 是一个群，它的单位元是 $0$，$a$ 的逆元是它的相反数；整数集和整数集上的乘法 $(\mathbb{Z},\times)$ 不是一个群，它虽然有单位元 $1$，除了 $1$ 和 $-1$ 外所有数都没有逆元；模质数 $p$ 意义下正整数集和模 $p$ 意义下正整数集上乘法$(\mathbb{Z}[p],\times)$ 是一个群，它的单位元是 $1$，$a$ 的逆元是 $a^{p-2}$；等等。

**【定义 2】（子群）**
若存在群 $(G,\times)$ 和 $(H,\times)$，且 $H\subseteq G$，则称 $(H,\times)$ 为 $(G,\times)$ 的子群。

例如整数加法群 $(\mathbb{Z},+)$ 是有理数加法群 $(\mathbb{Q},+)$ 的子群。

**【定义 3】（阶）**
群 $G$ 的阶为其中的元素个数，记为 $|G|$。特别地，无限群的阶定义为 $0$。

### 陪集

**【定义 4】（陪集）**
若群 $(H,\times)$ 为 $(G,\times)$ 的子群，那么对于 $g\in G$，称集合 $\{g\times h|h\in H\}$ 为 $H$ 的左陪集，记为 $gH$；集合 $\{h\times g|h\in H\}$ 为 $H$ 的右陪集，记为 $Hg$。

下文若未特别说明，则陪集默认为左陪集。由于对称性，以下性质证明仅证左陪集，右陪集证明同理，可以自己试一下。

**【性质 1】**
$\forall g\in G,g\in gH$

证明：

$\because e\in H$

$\therefore g=g\cdot e\in gH$

证毕

**【性质 2】**
$\forall g\in G,|H|=|gH|$

证明：

$\forall h\in H$，$gH$ 总有元素 $g\cdot h$ 与之对应。

又由逆元唯一，$\forall h\in H$，$g\cdot h$ 两两不同。

$\therefore \forall g\in G,|H|=|gH|$

证毕

**【性质 3】**
$\forall a,b\in G,a\cdot b^{-1}\in H\Rightarrow aH=bH$

证明：

由封闭性，$(a\cdot b^{-1})H=H$

$\therefore (a\cdot b^{-1}\cdot b)H=bH$

即 $aH=bH$

证毕

**【性质 4】**
$\forall a,b\in G,aH\cap bH\neq\varnothing\Rightarrow aH=bH$

证明：

当 $aH\neq bH$ 时，假设 $h\in aH\cap bH$

$\therefore\exists r,s\in H,a\cdot r=h,b\cdot s=h$

$\therefore a\cdot b^{-1}=s\cdot r^{-1}$

由封闭性 $s\cdot r^{-1}\in H$

$\therefore a\cdot b^{-1}\in H$

由性质 3，有 $aH=bH$，与假设矛盾。

$\forall a,b\in G,aH\cap bH\neq\varnothing\Rightarrow aH=bH$

证毕

**【性质 5】**
$\bigcup_{g\in G}gH=G$

证明：

由性质 1，$g\in gH$；由封闭性，$gH\subseteq G$

$\therefore \bigcup_{g\in G}gH=\{g|g\in G\}=G$

证毕

### 拉格朗日定理

**【定义 5】（指数）**
若 $H$ 是 $G$ 的子群，称 $H$ 在 $G$ 中本质不同陪集个数为 $H$ 对 $G$ 的指数，记为 $[G:H]$。

**【定理 1】（拉格朗日定理）**
若有限群 $H$ 是有限群 $G$ 的子群，则有

$$|H|[G:H]=|G|$$

证明：根据性质 4，本质不同陪集互不相交，并集大小为各陪集大小之和。

根据性质 5，这些陪集之并的大小为 $|G|$。

根据性质 2，每个陪集的大小均为 $|H|$

因此，$|H|[G:H]=|G|$。

证毕

### 置换

**【定义 6】（置换）**
若 $f$ 是有限集合 $S=\{a_1,a_2,\dots,a_n\}$ 到自身的双射，则称 $f$ 为 $S$ 的一个置换，记为

$$f=\begin{pmatrix}
 a_1 & a_2 & \dots & a_n \\
 a_{p_1} & a_{p_2} & \dots & a_{p_n}
\end{pmatrix}$$

表示 $S$ 中元素 $a_i$ 被映射为元素 $a_{p_i}$。其中 $a_{p_i}$ 各不相同。当 $a_i=i$ 时，可简记为 $f=(a_{p_1},a_{p_2},\dots,a_{p_n})$。

然后你会发现，把 $f$ 中每一列打乱，这个置换和 $f$ 等效。

**【定义 7】（置换乘法）**
先后进行两个置换后得到的结果，可以视为一个置换。把两个置换合成一个置换的运算，称为置换的乘法，记为 $f\circ g$。

记集合 $S$ 上的所有置换的集合记为 $F$，那么 $(F,\circ)$ 是不是一个群呢？

首先，封闭性和结合律肯定是满足的。第二，将每个元素映射成自身的置换是恒等置换，是单位元。第三，将其中一个元素上下两行交换，就可以得到该元素的逆元。

因此 $(F,\circ)$ 是一个群。

**【定义 8】（置换群）**
将集合 $S$ 上的所有置换的集合记为 $F$，则群 $(F,\circ)$ 的任意一个子群称为置换群。

**【定义 9】（循环置换）**
若置换 $f$ 形如

$$f=\begin{pmatrix}
 a_1 & a_2 & \dots & a_{n-1} & a_n \\
 a_2 & a_3 & \dots & a_n & a_1
\end{pmatrix}$$

则称 $f$ 为循环置换，记为 $f=(a_1,a_2,\dots,a_n)$。如果两个置换不含相同元素，则称这两个循环置换不相交。

**【定理 2】**
任意一个置换都可以分解为若干不相交的循环置换的乘积。

证明：以元素为节点，置换中的映射关系连有向边，因为置换是双射，该图每个点的入度出度均为 $1$，无重边、自环。

因此，该图由若干环组成。

图中的每个环都可以用一个循环置换表示。故任意一个置换都可以分解为若干不相交的循环置换的乘积。

### 轨道稳定子定理

**【定义 10】（群作用）**
在群 $G$ 和集合 $X$ 上，若存在二元函数 $f:G\times X\mapsto X$，对于所有 $x\in X$ 和 $g,h\in G$ 满足以下两点：

1. $f(e,x)=x$

2. $f(g,f(h,x))=f(g\cdot h,x)$

则称 $G$ 作用于 $X$。

若是右群作用，则 $f:X\times G\mapsto X$。

为了方便，以下将 $f(g,x)$ 简记为 $g(x)$。

**【定义 11】（轨道和稳定子）**
若群 $G$ 作用于集合 $X$，对于 $x\in X$，称集合 $\{g(x)|g\in G\}$ 为元素 $x$ 的轨道，记为 $G(x)$；称集合 $\{g|g(x)=x,g\in G\}$ 为元素 $x$ 的稳定子，记为 $G^x$。

**【定理 3】（轨道稳定子定理）**
$\forall x\in X,|G|=|G^x||G(x)|$

证明：根据定义，$G^x$ 中有单位元 $e$ 且满足结合律。 

$\forall f,g\in G^x,f(x)=x,g(x)=x$

$\therefore (f\cdot g)(x)=f(g(x))=f(x)=x$

$\therefore f\cdot g\in G^x$，满足封闭性。

$\forall f\in G^x,(f^{-1}\cdot f)(x)=f^{-1}(f(x))=f^{-1}(x)=e(x)=x$

$\therefore f^{-1}\in G^x$，满足逆元。

因此，$G^x$ 是一个群。

根据定义，有 $G^x\subseteq G$，

故 $G^x$ 是 $G$ 的子群。

由拉格朗日定理，$|G|=[G:G^x]|G^x|$，仅需证明 $[G:G^x]=|G(x)|$。

考虑构造一一对应。

若 $g(x)=f(x)$，则 $(f^{-1}\cdot g)(x)=e(x)=x$，所以 $f^{-1}\cdot g\in G^x$，由陪集的性质 3 可得 $gG^x=fG^x$。 

同理，若 $gG^x=fG^x$，则有 $g(x)=f(x)$。 

这表明对于 $g\in G(x)$，有且仅有一个左陪集与其对应。反之亦然，每个左陪集有且仅有一个 $g\in G(x)$ 与之对应。

故 $[G:G^x]=|G(x)|$

证毕

### Burnside 引理

终于要进入正题了！

**【定义 12】（等价类）**
若 $G$ 为作用于 $X$ 的置换群，如果对于 $x,y\in X$ 满足 $\exists f\in G,f(x)=y$ 则称 $x,y$ 属于一个等价类。记等价类的集合为 $X/G$。记集合 $X^g=\{x|x\in X,g(x)=x\}$。

**【定理 4】（Burnside 引理）**
$|X/G|=\dfrac 1{|G|}\sum\limits_{g\in G}|X^g|$

证明：等式右边比较麻烦，让我们从右边开始。

等式右边 $=\dfrac 1{|G|}\sum\limits_{g\in G}|X^g|$

我们发现 $X^g$ 和 $G^x$ 很像，不如把集合展开。

$=\dfrac 1{|G|}\sum\limits_{g\in G}\sum\limits_{x\in X}[g(x)=x]$

交换求和号。

$=\dfrac 1{|G|}\sum\limits_{x\in X}\sum\limits_{g\in G}[g(x)=x]$

右边这玩意正好是 $G^x$ 的大小！

$=\dfrac 1{|G|}\sum\limits_{x\in X}|G^x|$

使用轨道稳定子定理，得到 $|G^x|=\frac{|G|}{|G(x)|}$。

$=\dfrac 1{|G|}\sum\limits_{x\in X}\dfrac{|G|}{|G(x)|}$

$=\sum\limits_{x\in X}\dfrac 1{|G(x)|}$

是时候引入等价类了！

$=\sum\limits_{T\in X/G}\sum\limits_{x\in T}\dfrac 1{|G(x)|}$

既然这些元素都在同一个等价类里，对于所有 $t\in T$ 肯定存在 $g\in G$ 使 $g(x)=t$。换句话说，$G(x)=T$。

$=\sum\limits_{T\in X/G}\sum\limits_{x\in T}\dfrac 1{|T|}$

$=\sum\limits_{T\in X/G}\dfrac 1{|T|}\sum\limits_{x\in T}1$

$=\sum\limits_{T\in X/G}\dfrac 1{|T|}|T|$

$=\sum\limits_{T\in X/G}1$

$=|X/G|=$ 等式左边

证毕

然后你会发现等价类的数量不就是本质不同方案数量吗？

到这一步我们已经可以做出本题了。其中 $G=\{\text{旋转}1\text{位},\text{旋转}2\text{位},\dots,\text{旋转}n\text{位}\}$，$X$ 为该环所有可能的排列。

对于操作“旋转 $k$ 位”，考虑其中不动点。如果一个环在旋转 $k$ 位后不变，它一定有一个周期为 $t$ 的循环节，其中 $t|k$。既然这玩意都是循环节了，$t$ 一定满足 $t|n$。所以 $t|(n,k)$。如果 $t\neq (n,k)$，我们可以构造一个 $k'<k$ 使得 $t=(n,k')$。为了保证枚举不重复，不如就令 $t=(n,k)$。这 $(n,k)$ 个位置上，随意排布，根据乘法原理，共有 $n^{(n,k)}$ 种方式，即 $|X^g|=n^{(n,k)}$。因此，答案为

$$\dfrac 1 n\sum\limits_{k=1}^n n^{(n,k)}$$

### Pólya 定理

在进行莫比乌斯反演前，不如让我们再进一步，研究一下上面是怎么求 $|X^g|$ 的。在上面的求法中，我们用到了循环节。这就能联想到循环置换。再看看 $(n,k)$ ，这不正是把置换 $g$ 能拆分成的不相交的循环置换的数量吗？

我们不如记颜色的集合为 $D$，把置换 $g$ 能拆分成的不相交的循环置换的数量记为 $c(g)$。这样，我们就有下式：

**【定理 5】（Pólya 定理）**
$|X/G|=\dfrac 1{|G|}\sum\limits_{g\in G}|D|^{c(g)}$

证明：考虑在定理 2 的证明中我们建图的方法。如果这种变换是不动点，它一定满足每个环颜色相同，因为一旦由一个环中哪怕一个颜色不同，环内至少有两个元素颜色不同，这种变换就不是不动点。一共有 $c(g)$ 个环，每个环有 $|D|$ 种染色方式，根据乘法原理，有 $|D|^{c(g)}$ 个。故 $|X^g|=|D|^{c(g)}$。根据 Burnside 引理，该式成立。

证毕

最后，把最大公约数用莫比乌斯反演经典套路化掉后，和逃课做法的式子是一样的，在这里就不写啦 OvO~

## 附上代码

```cpp
#include<bits/stdc++.h>
#define ri register int
#define ll long long 
#define F(i,a,b) for(ri i(a);i<=b;++i)
#define R(i,a,b) for(ri i(a);i>=b;--i)
#define _ 0
using namespace std;
const int MOD=1e9+7;
int n;
inline int input(){
	ri x;register char ch;
	for(ch=getchar();!isdigit(ch);ch=getchar());
	for(x=0;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x;
}
inline ll qpow(ll base,int expo){
	register ll res(1);
	while(expo){
		if(expo&1) res=res*base%MOD;
		base=base*base%MOD;
		expo=expo>>1;
	}
	return res;
}
inline int phi(int x){
	ri res(x),h(x);
	for(ri i(2);(ll)i*i<=h;++i){
		if(h%i) continue;
		res=res/i*(i-1);
		while(!(h%i)) h/=i;
	}
	if(h^1) res=res/h*(h-1);
	return res;
}
int main(){
	R(t,input(),1){
		register ll ans(0);
		n=input();
		for(ri d(1);(ll)d*d<=n;++d){
			if(n%d) continue;
			ri h=n/d;
			ans=(ans+qpow(n,d-1)*phi(h)%MOD)%MOD;
			if(h^d) ans=(ans+qpow(n,h-1)*phi(d)%MOD)%MOD;
		}
		printf("%d",ans),putchar('\n');
	}
	return ~~(0^_^0);//每日卖萌（1/1）
}

完结撒花awa~

---

## 作者：SAOKA_ (赞：4)

[欢迎来我的blog交流学习！](https://www.luogu.org/blog/saoka/)

### 解题思路
>首先我们要了解一个东西，叫做**polya定理**，具体的形式如下:
**$N=\frac{\sum_{g\in G}k^{m(g)}}{|G|}$**
其中，通俗来讲，$|G|$代表的是置换群，$m(g)$表示的是对于不同的转换方式，**置换群**内的循环个数，**k**代表染色（颜料）数。

>但是这样讲可能 ~~有些~~ **很抽象**，我们先来举个栗子：


|i=  |1  |2  |3  | 4 | 5 | 6 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| | | | | | | |



>给定这样一个含有6个格子的表格，我们现在有m种颜色，规定可以进行**反转**，若反转后与未反转之前的某一种方案**重合**，则我们视之为同一种方案数。

>好！我们现在知道了如何进行变换——反转，则此时我们可以得到
$|G|=2$

>且当$g=1$时，即不进行任何操作时对应的置换群是：$(1 ,2,3,4,5,6) $，此时$m(g)=1$

>当$g=2$时，即进行反转时，对应得置换群是：$(1,6),(2,5),(3,4)$，此时$m(g)=3$

>由此，我们带入已知得数据——颜色数$m$，根据公式可得：
$N=\frac{1}{2} {\times}(m^{1}+m^{3})$

>同理我们可以类推到旋转问题，就可以得到这道题得思路啦！！具体得推导过程楼下大佬已经解释得很清楚了，我就提一点

> -$φ(N)$是表示的小于等于$N$且与$N$互质的数的个数


### $C^{++} code$:与楼下大佬代码一致

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long 
#define f(a,b) for(ull i=a;i<=b;++i)
using namespace std;
ull t,n;
const ull MOD=1e9+7;
inline ull get_phi(ull k)	//φ函数，φ(n)表示在小于等于n的数中，与n互质的数的个数
{							//在这里我们可以逆向考虑，即考虑n的约数个数设为p，则φ(n)=n-p
	ull res=1;
	for(ull i=2;i*i<=k;i++)
		if(k%i==0)
		{
			k/=i;
			res*=(i-1);
			while(k%i==0)
				k/=i,res*=i;
		}
	if(k>1) res*=(k-1);
	return res;
}

inline ull quick_pow(ull x,ull y){ 
    ull res = 1;
    while(y){
        if(y&1) res = res*x%MOD;
        x = x*x%MOD;
        y >>= 1;
    }
    return res;
}

inline ull polya(ull m,ull n)
{
	ull tot=0;
	for(ull i=1;i*i<=n;i++)
	{
		if(n%i)
			continue;
		tot=(tot%MOD)+get_phi(i)*quick_pow(m,n/i-1)%MOD;		//找到一个约数进行计算
		if(i*i!=n)
			tot=(tot%MOD)+get_phi(n/i)*quick_pow(m,i-1)%MOD;		//除开n的算数平方根，一个约数必定有另一个不相等的约数使之乘积为n
	}
	return tot%MOD;
}

inline ull read()
{
	ull f_=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f_=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*=f_;
}

int main()
{
	//t=read();
	cin>>t;
	f(1,t)
	{
		//n=read();
		cin>>n;
		//printf("%lld\n",polya(n,n));
		cout<<polya(n,n)<<endl;
	}
	return 0;
}

```




---

## 作者：BFLSTiger (赞：3)

由于本题只限制不能通过旋转重合，可以通过莫比乌斯反演推导得出结论。

### 说在前面

本题解推导方法为逃课方法，绕开了各种群论定义和理论，利用莫比乌斯反演得到结果。虽然最终得出结果相同，但是如果想利用题解学习群论各种知识的同学请去阅读其他题解。

### 准备工作

在进行推导之前，首先先需要掌握初步的莫比乌斯反演的知识，并知道以下两个式子：

$$1 * \mu = \epsilon$$

$$1 * \phi = id$$

我们定义以下函数：

$f(i)$ 表示长度为 $i$ 的环在不考虑翻转变换的情况下有多少种染色方法。

$g(i)$ 表示长度为 $i$ 且最小循环节为 $i$ 的环在不考虑翻转变换的情况下有多少种染色方法。

### 推导过程

由定义，我们可以得出以下关系：

$$ans = \sum_{i|n} \frac{g(i)}{i} = \frac{1}{n} \sum_{i|n} g_i \cdot \frac{n}{i} = \frac{1}{n} (g*id)(n)$$

$$f(i)= \sum_{j|i} g(j) \Rightarrow f=g*1 \Rightarrow g=f*\mu$$

将第二个式子代入第一个式子后可得：

$$ans = \frac{1}{n} (f * \mu * id)(n) = \frac{1}{n} (f * \phi)(n) =  \frac{1}{n} \sum_{i|n} f(i) \cdot \phi(\frac{n}{i})$$

在本题中 $f(i)=n^i$，代入可得：

$$ans = \frac{1}{n} \sum_{i|n} n^i \cdot \phi(\frac{n}{i})$$

其中 $\phi$ 在本题中可以暴力求解。

完整代码如下：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
namespace Dango
{
	const int MOD=1000000007;
	int T,n;
	long long ans;
	int read()
	{
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
		while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
		return f?-x:x;
	}
	long long pow_(long long a,long long b)
	{
		long long res=1;
		while(b)
		{
			if(b&1)res=res*a%MOD;
			a=a*a%MOD;
			b>>=1;
		}
		return res;
	}
	long long phi(long long x)
	{
		long long res=x;
		int s=sqrt(x);
		for(int i=2;i<=s;i++)
		{
			if(x%i)continue;
			res=res-res/i;
			while(!(x%i))x/=i;
		}
		if(x>1)res=res-res/x;
		return res;
	}
	int work()
	{
		T=read();
		for(int i=1;i<=T;i++)
		{
			n=read();
			int s=sqrt(n);
			ans=0;
			for(int j=1;j<=s;j++)
			{
				if(n%j||j*j==n)continue;
				ans=(ans+pow_(n,j)*phi(n/j)%MOD)%MOD;
				ans=(ans+pow_(n,n/j)*phi(j)%MOD)%MOD;
			}
			if(s*s==n)ans=(ans+pow_(n,s)*phi(s)%MOD)%MOD;
			printf("%lld\n",ans*pow_(n,MOD-2)%MOD);
		}
		return 0;
	}
}
int main()
{
	return Dango::work();
}
```

---

## 作者：Tenshi (赞：3)

# Burnside 引理 & Pólya 定理

> **Burnside 引理 & Pólya 定理**能够用来解**求本质不同的方案数**这类问题。

考虑到定理的证明依赖于**群论**，而萌新可能对群论比较陌生，因此从群论相关知识讲起。

群论知识参考了许多资料（见本文**引用资料**），把本人认为简洁易于理解的讲解保留了下来，而对于一些理论。证明使用了自己的讲述方法/证法，如果发现不严谨或者笔误指出请指出 `orz`。

~~写这份博客的时候电脑曾经停电丢失了数据，写到一半的进度没了，我厄厄。~~



## 群论相关知识

### 半群

- 集合 $S$ 和 $S$ 上满足**结合律**的二元运算 $\cdot$ 所形成的代数结构叫做**半群**，记为 $(S, \cdot)$ 或者简记为 $S$，运算 $x \cdot y$ 常记为 $xy$。对于 $x, y\in S$，有 $xy \in S$（即运算 $\cdot$ 在 $S$ 上满足**封闭性**）

    > 运算同时满足交换律的半群称为**交换半群**。

- 若 $\forall x\in S$ 均有 $ex = xe = x$，称 $e$ 为 $x$ 的幺元。

    幺元是**唯一**的：若 $e'$ 也是幺元，有 $e' = e'e = e$。

    具有幺元的半群称为**含幺半群**。

- 对于含幺半群 $S$，元素 $y\in S$ 叫做元素 $x \in S$ 的**逆元**，是指 $xy = yx = 1$。

    逆元是**唯一**的：若 $y'$ 也是逆元，有 $y' = y' \cdot 1 =  y'xy = 1\cdot y = y$。把这个唯一的逆元记作 $x ^ {-1}$。



### 群

对于每个元素均有**逆元**的**含幺半群** $G$ 称为**群**。

> 若运算又满足交换律，称 $G$ 为交换群或阿贝尔（Abel）群。

群 $G$ 的元素数 $|G|$ 称为群的**阶**。

> 个人认为，把群看成是具有一定约束并且支持运算 $\cdot$ 的**集合**会比较容易理解相关内容。

#### 群的性质总结

由上文所述，群满足性质：

- 封闭性。
- （运算满足）结合律。
- 存在幺元。
- 每个元素均有逆元。

当然，如果 $G$ 在 $\cdot$ 下满足上述四个性质，那么称 $(G, \cdot)$ 为一个群。



#### 例子

上面给了半群与群的定义，现举个例子：

对于自然数集 $N$，$(N, +)$ 为含幺交换半群，幺元为 $0$，不是的群的原因是 $N$ 中非 $0$ 的数均不存在逆元。

而整数集 $Z$ 对于加法是交换群，因为对于 $x\in Z$，$-x$ 为对应的逆元，事实上，它被称为**整数加法群**。



###  子群

若 $H \subseteq G$ 且在 $(H, \cdot)$ 为群，称 $H$ 为 $G$ 的**子群**，记为 $H \leq G$。

验证子集 $H$ 为 $G$ 的子群只需验证以下三点：

- $1_G \in H$
- $h \in H$，$h^{-1} \in H$
- $a, b \in H \Rightarrow a \cdot b \in H$



### 陪集

陪集是由任意固定的 $g\in G$ 与 $G$ 子群 $H$ 生成的集合，

其中**左陪集**为：$gH = \{gh | h\in H\}$

**右陪集**为：$Hg = \{hg | h\in H\}$

陪集的性质：

- 陪集元素个数**等于**子群的阶，因为：（以左陪集为例：$gh \ne gh' \Leftrightarrow h \ne h'$）
- 若 $g\in H$，由**封闭性**易知，陪集为 $H$ 本身。



#### 陪集定理

对于 $H$ 两个左（右）陪集，要么相等，要么交集为 $\varnothing$。

> 证明：
>
> 如果陪集 $gH, g'H$ 存在交集，假设交集的一个元素为 $gh = g'h'$（$h, h'\in H$），
>
> 显然有 $gh H = g'h' H$，因为 $hH = h'H = H$，因此 $gH = g'H$。

利用陪集定理，我们有分拆：$G = \cup g_iH$，叫做 $G$ 对子群 $H$ 的**左陪集分解**。

其中左陪集的个数记为 $[G:H]$，称为子群 $H$ 对于 $G$ 的**指数**。

进而，我们显然有：设 $G$ 为有限群，$H\leq G$，则 $|G| = |H|[G:H]$。（**拉格朗日（J.Lagrange） 定理**）



### 置换

集合 $\Sigma$ 到自身每个一一对应 $\sigma$ 叫做 $\Sigma$ 上的一个置换。若 $\Sigma$ 为有限集，此置换可表示为：
$$
\sigma = 

\begin{pmatrix}
a_1 & a_2 & \dots & a_n \\
\sigma(a_1) & \sigma(a_2) & \dots & \sigma(a_n) \\
\end{pmatrix}
$$
$\sigma$ 的逆可以表示为：
$$
\sigma ^ {-1} = 

\begin{pmatrix}
\sigma(a_1) & \sigma(a_2) & \dots & \sigma(a_n) \\
a_1 & a_2 & \dots & a_n \\
\end{pmatrix}
$$
两个置换 $\sigma, \tau$ 的乘积定义为 $\Sigma \to \Sigma$ 映射的合成：$(\sigma \tau) (a_i) = \sigma(\tau(a_i))$，其中 $i \in [1, n]$。

 例如，
 $$
 \begin{pmatrix}
 1 & 2 & 3 & 4 \\
 2 & 4 & 3 & 1 \\
 \end{pmatrix}
 
 \begin{pmatrix}
 1 & 2 & 3 & 4 \\
 3 & 1 & 4 & 2 \\
 \end{pmatrix}
 
 =
 
 \begin{pmatrix}
 1 & 2 & 3 & 4 \\
 1 & 2 & 4 & 3 \\
 \end{pmatrix}
 $$

轮换（循环置换）是一类特殊的置换，表示为 
$$
\begin{pmatrix}
a_1 & a_2 & \dots & a_{n-1} & a_n \\
a_2 & a_3 & \dots & a_n & a_1 \\
\end{pmatrix}
$$


每个置换均可写成一些**轮换**的乘积（轮换的次序可随意写），使不同轮换中没有公共元素，长为 $1$ 的置换往往**略去不写**，如：

 $$
 \begin{pmatrix}
 1 & 2 & 3 & 4 & 5 & 6 \\
 3 & 1 & 2 & 5 & 4 & 6 \\
 \end{pmatrix}
 
 =
 
 (1, 3, 2)(4, 5)
 
 =
 
 (4, 5)(1, 3, 2)
 $$

#### 置换群

上面已说明置换的乘积仍为**置换**，且存在逆元。而对于置换的幺元显然是**恒等置换**（简单来说就是 $a_i \to a_i$）。

因此我们可以定义一个 $S(\Sigma)$ 表示 $\Sigma$ 上全体置换构成的**集合**，这是一个 $n!$ 元群，叫做集合 $\Sigma$ 上的对称群。

而它的每个子群都叫集合 $\Sigma$ 上的**置换群**。



### Burnside 引理 & Pólya 定理

给定集合 $X$ 和**置换群** $G$。

> 如果感觉到十分抽象的话，不妨代入下面的情境（意义）对下文的内容进行理解：
>
> $A$ 表示待染色物品**集合**。
>
> $B$ 表示支持染的颜色的**集合**。
>
> $X$ 表示染色方案**集合**。
>
> $G$ 表示支持的变换。
>
> $X/G$ 表示**本质不同**的染色方案**集合**。
>
> $X^g$ 表示经过一个变换 $g$ 后保持不变的**染色方案**对应的**集合**。
>
> 比如说：给你一串共 $n$ 个珠子，支持旋转变换 $G$（可以看作是置换的一种）（这意味着如果两种染色方案在旋转后一样视为**本质相同**），每个珠子可以被染成 $m$ 种颜色（也就是说方案集 $X$ 的大小为 $m ^ n$），求本质不同的染色方案数（也就是 $|X/G|$）





#### 轨道-稳定子定理

##### 轨道

$\forall x\in X$, 称 $G(x) = \{g(x) | g\in G\}$ 为 $x$ 的**轨道**。

##### 稳定子

$\forall x\in X$，称 $G ^ x = \{g | g(x) = x, g\in G \}$ 为 $x$ 的**稳定子**。
$$
|G| = |G ^ x||G(x)|
$$
先证明 $G^x$ 是 $G$ 的**子群**：

- 封闭性：对于 $G^x$ 的元素 $g, g'$，有 $(gg')(x) = x$，故 $gg'\in G^x$
- 结合律：由置换乘法易知成立。
- 存在幺元：也就是恒等置换 $I$，显然在 $G^x$ 中。
- 每个元素均有逆元：$g ^ {-1}(g(x)) = I(x) = x$，同时 $g^{-1}(g(x)) = g^{-1}(x)$，故 $g ^ {-1} \in G ^ x$。

由**拉格朗日**定理，$|G| = |G ^ x| [G: G^x]$

故下面只需证 $[G: G^x] = |G(x)|$，也就是左陪集的个数等于 $x$ 轨道的个数。

> 证明：
>
> 考虑证明存在 $G(x)$ 到 $G^x$ 左陪集的**一一映射**：
>
> 注意到对于每个 $gG^x$，有 $gG^x(x)$ 的元素均相同，这意味着每个左陪集 $gG^x$ 能够对应一个 $G(x)$ 的元素 $g(x)$；而对于不同的左陪集 $gG^x, g'G^x$，因为 $g\ne g'$，因此必然满足相应的 $g'(x) \ne g(x)$。
>
> 因此有 $G(x)$ 到 $G^x$ 左陪集的一一映射关系。



#### Burnside 引理

$$
\begin{aligned}
\sum_{g\in G}|X^g| &= |\{(g,x) | (g,x)\in G\times X, g(x) = x\}| \\
&= \sum_{x\in X}|G^x| \\
&= \sum_{x\in X}\frac{|G|}{|G(x)|} 

\end{aligned}
$$

下面结合实际意义进行推导：

对于**本质相同**的一组（染色方案）$x$，它们的轨道数都是 $G(x)$，因此有：
$$
\begin{aligned}
\sum_{x\in X}\frac{1}{|G(x)|} &=  |X/G|
\end{aligned}
$$
故我们有 **Burnside 引理**：
$$
|X/G| = \frac{1}{|G|}\sum_{g\in G}|X^g|
$$

这意味着，对于实际的计数问题，在给出变换的种类数 $|G|$ 后，我们只需要求出染色方案在各种变换下保持不动的数量的和（即 $\sum_{g\in G}|X^g|$），那么我们就可以求出本质不同的染色方案数了。



#### Pólya 定理

考虑到 Burnside 引理需要求的 $\sum_{g\in G}|X^g|$ 在实际统计中时间复杂度较高，而很多问题都是求解 **$A\to B$ 所有可能的映射**（也就是比较特殊的 $X$）所对应的染色方案（共 $|B| ^ {|A|}$ 种）中**本质不同**的数量。

那么，在这样的问题中，可以使用 **Pólya 定理**：
$$
|X/G| = \frac{1}{|G|}\sum_{g\in G}|B|^{c(g)}
$$

> $c(g)$ 表示置换 $g$ 能拆分出的循环置换数。

证明：

注意到对于置换 $g$，对于其拆分出的每个循环置换中的颜色必须相同，根据乘法原理，可知共有 $|B | ^ {c(g)}$ 种

这意味着满足在 $g$ 作用下保持不变的方案 $x$ 数量 $|X^g|$ 等于 $|B| ^ {c(g)}$。

也就是 $|B| ^ {c(g)} = |X ^ g|$，证毕。



## 例题

[https://www.luogu.com.cn/problem/P4980](https://www.luogu.com.cn/problem/P4980)



### 解答

考虑使用 **Pólya 定理**：

只需统计对于每个置换 $g$ 的 $c(g)$ 值即可。

而对于本题，置换的形式就是 $k \in [0, n-1]$ 的**循环移位**，例如 $n=4, k=2$：
$$
g

=

\begin{pmatrix}
1 & 2 & 3 & 4 \\
3 & 4 & 1 & 2 \\
\end{pmatrix}
$$
那么上例的 $c(g)$ 值就是 $2$。



现在的问题就是：给定 $n, k$，求相应的 $c(g)$ 值。

其实就是求给定大小为 $n$ 的环，能拆分成多少个步长为 $k$ 的环，比如上面的例子就是能拆成两个环：$(1, 3), (2, 4)$。

所以考虑求每个环的大小 $size$（容易发现每个环大小相等），那么 $c(g) = \frac{n}{size}$。

而 $size$ 是满足 $n | tk$ 的最小的 $t$，所以 $size = \frac{n}{\gcd(n, k)}$。



现在，由上述推理以及 Pólya 定理，题目所求的答案 $Ans$ 就是：
$$
Ans = \frac{1}{|n|}\sum_{k=0}^{n-1} |n|^{\gcd(n, k)}
$$
当然因为直接枚举的复杂度为 $O(TN)$，会超时。

考虑根据 $\gcd$ 的值对上述和式进行分块，可以从枚举 $n$ 的因子 $d$ 入手：
$$
Ans = \frac{1}{|n|}\sum_{d|n} |n|^{d} \varphi(\frac{n}{d})
$$
复杂度为 $O(T \cdot \sqrt N \cdot \rm{log}N)$，可以通过。



### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int mod=1e9+7;

int fpow(int x, int p){
	int res=1;
	for(; p; p>>=1, x=x*x%mod) if(p&1) res=res*x%mod;
	return res;
}

int gcd(int a, int b){
	return b? gcd(b, a%b): a;
}

int inv(int x){
	return fpow(x, mod-2);
}

int phi(int x){
    int res=x;
    for(int i=2;i<=x/i;i++)
        if(x%i==0){
            res=res/i*(i-1);
            while(x%i==0) x/=i;
        }
    if(x>1) res=res/x*(x-1);

    return res;
}

signed main(){
	int T; cin>>T;
	while(T--){
		int n; cin>>n;
		int res=0;
		for(int i=1; i<=n/i; i++){
			if(n%i==0){
				res=(res+fpow(n, i)*phi(n/i)%mod)%mod;
				if(n/i!=i) res=(res+fpow(n, n/i)*phi(i)%mod)%mod;
			}
		}
		cout<<res*inv(n)%mod<<endl;
	}	
	return 0;
}
```







## 引用资料

[https://cp-algorithms.com/combinatorics/burnside.html](https://cp-algorithms.com/combinatorics/burnside.html)

[https://zhuanlan.zhihu.com/p/294221308](https://zhuanlan.zhihu.com/p/294221308)

[https://oiwiki.com/math/permutation-group/](https://oiwiki.com/math/permutation-group/)

冯克勤,李尚志,章璞.近世代数引论[M].合肥:中国科学技术大学出版社,2018

---

## 作者：歌吟入梦 (赞：3)

看到楼下一大堆神仙写的又臭又长的对Polya定理的证明，蒟蒻表示没时间看 ~~（好吧其实是看不懂）~~

这里说一下本人对Polya定理的理解，不太严谨，但是易于理解（就是1分钟就能理解的那种）

Polya定理用于解决如下问题：若将一个A经过B变换或C变换或D变换或……后得到的与Z一样，则称A与Z本质相同，求本质不同的个数

计算有多少个A经过B变换后不变(不仅是本质相同，还要真的一模一样)，有多少个A经过C变换后不变，有多少个A经过D变换后不变，……然后把它们取平均数

感性理解一下，若有x种变换，每种情况都要被重复算x次。（如果要严禁证明看神仙们的题解，本题解仅供快速学习Polya定理）

对于这道题，剩下的处理其它题解已经讲得很清楚了，我就不说了

巨丑的代码：
```cpp
#include<cstdio>
using namespace std;
template<class T>inline void read(T&a){
	char c=getchar();int f=1;a=0;
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c<='9'&&c>='0') a=(a<<1)+(a<<3)+c-48,c=getchar();
	a*=f;
}
template<class T>void write(T a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) write(a/10);
	putchar(a%10+48);
}
const int MOD=1e9+7;
#define int long long
int t,n;
int qp(int b,int f){
	if(!f) return 1ll;
	int rcd=qp(b,f>>1);
	return rcd*rcd%MOD*(f&1?b:1ll)%MOD;
}
int getphi(int n){
	int res=n;
	for(int i=2;i*i<=n;++i) if(n%i==0){res=res*(i-1)/i;while(n%i==0) n/=i;}
	if(n^1) res=res*(n-1)/n;
	return res;
}
inline int polya(int n){
	int res=0;
	for(int i=1;i*i<=n;++i) if(n%i==0){
		res=(res+getphi(i)*qp(n,n/i-1))%MOD;
		if((i*i)^n) res=(res+getphi(n/i)*qp(n,i-1))%MOD;
	}
	return res;
}
signed main(){
	read(t);while(t--) read(n),write(polya(n)),putchar('\n');
	return 0;
}
```

---

## 作者：hfjh (赞：2)

# Burnside 定理
## [可能更好的阅读体验](https://www.cnblogs.com/hfjh/p/17594566.html)
## 问题：

给定一个 $n$ 个点，$n$ 条边的环，有 $m$ 种颜色，给每个顶点染色，问有多少种**本质不同**的染色方案，答案对 $10^9+7$ 取模。

注意本题的本质不同，定义为：**只需要不能通过旋转与别的染色方案相同**。

## 题目初步解读

我们考虑如果不要求**本质不同**只需要 $n^n$。

但因为无标号的环就会重复。

例如这是一个 4 个点， 2 种颜色的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/llz915lr.png)

在这里面如果不要求**本质不同**就有 16 种方案，若要求，则只有 6 种。

> 同一行的都是一种方案。

## Burnside 引入

~~我们先来一些定义~~

### 置换群

令集合 $N=\{1,2,\cdots,n\}$。

令集合 $M$ 为 $N$ 若干个排列构成的集合。

令群 $G = (M,\times)$ 其中符号 $\times$ 解释如下：

$\sigma$ 是一个排列，也就是 $M$ 周一个元素。

写为 $\sigma \times a$ 不过更习惯被表示为 $\sigma(a)$。

其运算规则为：$\sigma(a)= (a_{\sigma_1},a_{\sigma_2}...a_{\sigma_n})$。

> 在前面样例中，置换群是：
> 
> $ (\{$旋转$0°$,$旋转$90°,$旋转$180°,$旋转$270°$\},\times) $
> 
> 若写成排列则是：
> 
> $(\{\{1,2,3,4\},\{2,3,4,1\},\{3,4,1,2\},\{4,1,2,3\}\},\times)$

### 轨道

考虑一个作用在 $X$ 上的置换群 $G$ ， $X$ 中一个元素 $x$ 的轨道则是 $x$ 通过 $G$ 中元素可以转移到的元素的集合。记作 $G(x)$。

> 样例中每一行就是一个轨道。例如下面就是一个轨道。
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/tutjgvbo.png)

### 稳定子

稳定子定义为：$G^x = \{g|g\in G,g \times x = x\}$。

使用语言描述，便是群 $G$ 中满足 $g(x)=x$ 的所有元素 $g$ 所构成的集合。

> 样例中：
> 
>  ![](https://cdn.luogu.com.cn/upload/image_hosting/iw8uez2r.png) 的稳定子为 $\{$旋转$0°\}$，
> 
>  ![](https://cdn.luogu.com.cn/upload/image_hosting/cwbqd87u.png) 的稳定子为 $\{$旋转$0°,$旋转$180°\}$，
> 
>  ![](https://cdn.luogu.com.cn/upload/image_hosting/za4g14ha.png) 的稳定子为 $\{$旋转$0°,$旋转$90°,$旋转$180°,$旋转$270°\}$。

### 轨道-稳定子定理：

我们可以发现：

1.在同一轨道的元素稳定子**个数**一定相等。

2.稳定子大小乘轨道大小等于群 $G$ 大小。

$$
|G^x|\times |G(x)|=|G|
$$

没错，他是个定理，考虑感性证明：

一个元素 $x$ 按照 $G$ 的操作一定可以得到轨道内所有元素，也就是集合 $G(x)$。

但在操作过程中会有重复的，重复的次数也就是稳定子集合大小。

详细证明可以看[这里](https://www.luogu.com.cn/blog/Soulist/solution-p4980)。

### 不动点

若 $g(x) = x$ 则称 $x$ 是在 $g$ 下的不动点。

定义集合 $X^g = \{x|g(x) = x,x\in X\}$。

稳定子和不动点有类似反演的关系。

若 x 的稳定子集合里有 $g$，那么 g 下不动点集合中也有 x。

所以对于**每一个 $x$ 稳定子的个数**之和等于**对于每一个 $g$ 不动点个数之和**。

形式化

$$
\sum_{x\in X} {|G(x)|} = \sum_{g\in G} |X^g|
$$

> 注意稳定子是对于 g 来说的，而不动点是对于 x 来说的。
> 
> 例如 ''旋转180°'' 不动点是
> ![](https://cdn.luogu.com.cn/upload/image_hosting/892l2k11.png)
> ![](https://cdn.luogu.com.cn/upload/image_hosting/6ffkhh21.png)
> ![](https://cdn.luogu.com.cn/upload/image_hosting/za4g14ha.png)

## Burnside 定理

### 公式：

我们要求的答案一般来说也就是轨道数量。

$$
ans = \dfrac{1}{|G|}\sum_{g\in G} X^g
$$

### 证明：

等价类数量也就是轨道数量。

$|G(x)|$ 代表 $x$ 所在轨道大小。

$$
ans = \sum_{x\in X} \frac 1 {|G(x)|}
$$

根据轨道-稳定子定理得：

$$
ans = \sum_{x\in X} \frac {|G^x|}{|G|}=\frac 1 {|G|} \sum_{x\in X} {|G^x|}
$$

用稳定子和不动点关系得：

$$
ans = \dfrac{1}{|G|}\sum_{g\in G} |X^g|
$$

## 回到题目

扩展到 $n$，现在的 $G$ 就是$\{$ 旋转 $0$ 次，旋转 $1$ 个，$\cdots$，旋转$n-1$个 $\}$。

考虑旋转 $k$ 次的不动点个数是 $n^{\gcd(k,n)}$。

当 $\gcd(k,n) = k$:

我们按照 $k$ 将环切成 $\frac n k$ 份，然后标上号。

![](https://cdn.luogu.com.cn/upload/image_hosting/yfakpwuq.png)

将他旋转。

![](https://cdn.luogu.com.cn/upload/image_hosting/6tc1u6oa.png)

我们发现每一份必须一样他才是个不动点。

答案就是 $n^k = n^{\gcd(n,k)}$。

当 $\gcd(k,n) \ne k$:

令 $g = \gcd(k,n)$ 那么我们将他旋转 $g \times \frac k g$ ，等价于将长度为 $g$ 的旋转 $\frac k g$ 次。

答案就是 $n^{gcd(n,k)}$。

> 如果还不懂，建议手模一下 $k = 4,n = 6$ 这个样例。

应用**Burnside**则有：

$$
Ans = \dfrac{1}{n}\sum_{k=1}^{n} n^{\gcd(k,n)}
$$

发现有 $\gcd$ ，可以莫反。

莫反基操，不多说。

$$
\frac{1}{n}\sum_{d|n}n^d \varphi(\frac{n}{d})
$$

直接暴力可过。

# Pólya 定理

就是染色问题中 **Burnside** 的运用。

对于一个排列 $g$ ，我们将每一个 $i$ 向 $a_i$ 连一条边，会得到若干环，每个环内元素颜色应该相同。定义 $c(g)$ 代表环数量，那么 **Pólya** 就是
$$
\dfrac{1}{|G|}\sum_{g\in G}m^{c(g)}
$$

---

## 作者：I_am_Accepted (赞：2)

[**本优化喜提最优解 50 ms。**](https://www.luogu.com.cn/record/77674348)

**很抱歉，本题解不讲任何数学部分内容**，只讲求得
$$
\text{Ans}=\frac{1}{n}\sum_{d|n}\varphi(d)n^{n/d}
$$
后如何优化程序。

首先，$\frac{1}{n}$ 可以通过快速幂快速求得，所以只考虑后面的求和即可。

## 朴素做法

首先，我们得枚举 $n$ 的因数 $d$，然后对于每一个 $d$，我们要 $O(\log n/d)$ 求快速幂和 $O(\sqrt{d})$ 求单点的 $\varphi$。

这样总体时间大概为 $O(\text{d}(n)\sqrt{n})$（好像被证明可以更快？不管了），$\text{d}(n)$ 表示 $n$ 的正因数个数。

## DFS 做法

发现「单点求 $\varphi$」太慢啦。尝试将 $n$ 因数的 $\varphi$ 统一做。

$\pi(x)$ 表示 $\le x$ 的数中素数的个数，即
$$
\pi(x)=\sum_{i=1}^{x}[i\in prime]
$$
我们还是 $O(\pi(\sqrt{n}))$ 得出
$$
n=a_1^{b_1}a_2^{b_2}\dots a_t^{b_t}\quad(a_i\in prime)
$$
（唯一分解定理）

可以得到 $t\le 9$（前 $10$ 个素数乘积 $>10^9$）。

$n$ 的因数可以表示为
$$
a_1^{c_1}a_2^{c_2}\dots a_t^{c_t}\quad(0\le c_i\le b_i)
$$
所以我们按 $a_1\to a_n$ DFS 这些指数 $\{c\}$。

当一个素数 $a_i$ 第一次加入时，乘 $(a_i-1)$，否则乘 $a_i$，这样我们就 $O(\text{d}(n))$ 得到了所有因数的 $\varphi$。

再用快速幂搞定 $n^{n/d}$ 即可。

总时间 $O(\sqrt{n}+2\pi(\sqrt{n})+\displaystyle\frac{1}{2}\text{d}(n)\log n)$。

（其实常系数没用，但是还是象征性地写上了，第一项为线性筛素数的时间）

Upd：感谢 @[pzq_loves_qwq](https://www.luogu.com.cn/user/384214) 提供的化简思路，我写写看。
$$\begin{aligned}
\sum_{d|n}\log d&=\frac{1}{2}\sum_{d|n}\log d+\log\frac{n}{d}
\\&=\frac{1}{2}\sum_{d|n}2\log \sqrt{n}
\\&=\frac{1}{2}\sum_{d|n}\log n
\\&=\frac{1}{2}\text{d}(n)\log n
\end{aligned}$$
## Code

~~如果有人比我跑得快请踹我。~~

```cpp
#include<stdio.h>
using namespace std;
#define ll long long
const ll mod=1e9+7;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define N 31628
int n,m,p[N],len=0,a[10],b[10],tot;
bool vis[N];
void init(){
	for(int i=2;i<N;i++){
		if(!vis[i]) p[++len]=i;
		for(int x=1,j;x<=len && (j=p[x])*i<N;x++){
			vis[i*j]=1;
			if(i%j==0) break;
		}
	}
}
ll ans;
void dfs(int id,int val,int lst){
	if(id==tot+1){
		(ans+=pw(n,n/lst)*val)%=mod;
		return ;
	}
	dfs(id+1,val,lst);
	int x=a[id];
	val*=(x-1);
	for(int i=1,j=b[id];i<=j;i++){
		lst*=x;
		dfs(id+1,val,lst);
		val*=x;
	}
}
void work(){
	scanf("%d",&n);
	m=n;
	ans=tot=0;
	for(int x=1,i;(i=p[x])*i<=m;x++) if(m%i==0){
		a[++tot]=i;
		b[tot]=1;
		m/=i;
		while(m%i==0) b[tot]++,m/=i;
	}
	if(m!=1) a[++tot]=m,b[tot]=1;
	dfs(1,1,1);
	(ans*=pw(n,mod-2))%=mod;
	printf("%lld\n",ans);
}
int main(){
	init();
	int T;scanf("%d",&T);
	while(T--)work();
return 0;}
```

---

## 作者：Light_snow (赞：2)

本文同步于[Pólya 定理学习笔记](https://www.cnblogs.com/dixiao/p/14778360.html)


在介绍 Polya 定理前，先来介绍一下群论（大概了解一下就好）：
群是满足下列要求的集合：
1. 封闭性：即有一个操作使对于这个集合中每个元素操作完都使这个集合中的元素。
2. 结合律：即对于上面那个操作有结合律。
3. 单位元：对于 $a * e = a$ 则称$e$是集合 $A$ 对于操作 $*$ （并不一定是相乘）的逆元。
4. 逆元：即有 $a * b = b * a = e$ 对于元素 $a$ 有逆元。


置换群：

考虑这样的一个全置换集合，可以验证该集合为群。（置换不懂的话建议右转百度，这里不细说）。

接下来介绍 Burnside 定理：

对于一类染色问题，并统计在一些操作下的本质不同方案数有这样一个公式:

我们把所有的操作（类似于顺时针旋转，对称等等）写成一个置换群
则有答案为:

$ans = \frac{1}{cnt}\sum_{f \in G}p(f)$

其中 $p(f)$ 指的是在该置换下不变的染色方案数。

举例有： 
一个大小 5 的环，顺时针旋转了 144 度的置换为:

$
\begin{pmatrix} 
1&2&3&4&5\\
4&5&1&2&3
\end{pmatrix}
$

以两种颜色染色则有:

$
\begin{pmatrix} 
1&1&1&1&1
\end{pmatrix}
$

$
\begin{pmatrix} 
0&0&0&0&0
\end{pmatrix}
$

两种方案满足对该置换不动。
 
接下来介绍 Polya 定理：

考虑把置换写成循环的形式。

$
\begin{pmatrix} 
1&2&3&4\\
1&2&3&4
\end{pmatrix}
$
写作:$(1)(2)(3)(4)$。

$
\begin{pmatrix} 
1&2&3&4\\
3&4&1&2
\end{pmatrix}
$
写作:$(1\ 3)(2\ 4)$。

则有 Polya 定理：
$ans = \frac{1}{cnt}\sum_{f \in G}k^{m(f)}$。

 $k$ 为染色数, $m(f)$ 为该置换拆解成的循环数。

[【模板】Pólya 定理](https://www.luogu.com.cn/problem/P4980)。

考虑写出置换后，易证得顺时针旋转$k$次的置换的循环为 $\gcd(n,k)$。

则有 $ans = \frac{1}{n}\sum_i^n n^{\gcd(n,i)}$ 。

这样复杂度不在承受范围内，考虑枚举 $\gcd(n,i)$ 。

$ans = \frac{1}{n}\sum_{L|n} n^{L} * \varphi(\frac{n}{L})$ 。

这样就能在根号里做出答案了。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
#define mod 1000000007

ll T,n;

inline ll pow(ll a,ll b){
	ll ans = 1;
	while(b){
		if(b & 1) ans = 1ll * ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans % mod;
}

inline ll phi(int now){
	int ans = now;
	for(int i = 2;i * i <= now;++i){
		if(now % i)continue;
		ans = ans - ans / i;
		while(now % i == 0)
		now /= i;
	}
	if(now != 1)
	ans = ans - ans / now;
	return ans % mod;
}

inline ll get(int now){ll ans = phi(n / now) * pow(n,now) % mod;}

int main(){
	scanf("%lld",&T);
	while(T -- ){
		scanf("%lld",&n);
		ll ans = 0;
		for(int i = 1;i * i <= n;++i){
			if(n % i == 0){
				ans = (ans + get(i)) % mod;
				if(n / i != i)
				ans = (ans + get(n / i)) % mod;
			}
		}
		std::cout<<ans * pow(n,mod - 2) % mod<<std::endl;
	}
}

```

---

## 作者：aaaaaaaawsl (赞：1)

去掉繁琐的证明过程，尽量使用通俗易懂的语言，直接理解这个东西在 OI 中可以用到哪，应该怎么用。

~~绝对不是因为我不会~~

--------------

稍微的前置知识：

### 群的概念

群表示一个拥有满足**封闭性、满足结合律、有单位元、有逆元**的代数结构。

结构里包括一个集合和一个作用在集合内的元素的二元运算（二元运算是指由两个元素形成第三个元素的一种规则），二元运算可以自己定义。

具体的那四条性质为了本文的针对性就不谈了，网上一搜全是，请自行查找。

### 置换群

置换群是**集合内元素为置换**，**二元运算为置换的复合**的群。

就比如

$$

\begin{pmatrix}
a_1, a_2, a_3,……,a_{m - 1}, a_{m}\\
b_1, b_2, b_3,……,b_{m - 1}, b_{m}
\end{pmatrix}

$$

元素为 $a_1 \to b_1$，$a_2 \to b_2 ……$

二元运算为对于两个置换，先执行一个再执行下一个。

### 循环置换

是一类特殊的置换群，可表示为

$$

\begin{pmatrix}
a_1, a_2, a_3,……,a_{m - 1}, a_{m}\\
a_2, a_3,……,a_{m - 1}, a_{m}, a_1
\end{pmatrix}

$$

也可以表示为

$$

(a_1, a_2, a_3,……,a_{m - 1}, a_{m})

$$

性质：任意一个置换都可以分解为若干不相交的循环置换的乘积，例如

$$

\begin{pmatrix}
a_1, a_2, a_3, a_4, a_5\\
a_3, a_1, a_2, a_5, a_4
\end{pmatrix}

=

(a_1, a_3, a_2) \times (a_4, a_5)

$$

**注意**

这里  
 $(a_1, a_3, a_2) = 
\begin{pmatrix}
a_1, a_3, a_2\\
a_3, a_2, a_1
\end{pmatrix}
$ 中

$a_1$ 表示一个 $a_1$ 这个小元素（区分群内的元素），而不是第一个小元素的意思。$ \times $ 代表置换的复合。如果是第一次接触，上面那个例子也等于

$$

\begin{pmatrix}
a_1, a_3, a_2, a_4, a_5\\
a_3, a_2, a_1, a_5, a_4
\end{pmatrix}

$$

该定理的证明也非常简单。如果把小元素视为图的节点，映射关系视为有向边，则每个节点的入度和出度都为 $ 1 $，因此形成的图形必定是若干个环的集合，而一个环即可用一个循环置换表示。

-----------------

### Brunside 引理

Burnside 引理给我们一个求解本质不同的方案数的方法。

一般来说，可以用到 Burnside 引理的题会有一种或几种变换，在变换下相同的两个构造被看作等效的，比如本题的旋转。而为了之后的计算，这个变换是比较简单的，能处理的，如本质不同的字符串这样的就不好用他做。

把构造与进行一次变换之后得到的构造加上变换（看作置换）作为元素，**所有可能的元素**加上**置换的复合作为运算**构成一个置换群。

把他分解成循环群，Burnside 引理告诉我们，**本质不同的方案数为每个置换的不动点的数的平均数**。

**这里的不动点指的是对于一个群里的元素，元素里的小元素经过元素里的置换得到的还是这个小元素。**

比如对于本题来说

![](https://cdn.luogu.com.cn/upload/image_hosting/yi8k5sk8.png)

该方案旋转两位后是和原来相同的，那么该方案加上旋转两位这个置换作为元素就是在旋转两位这个置换内的一个不动点。

### Pólya 定理

Pólya 给了我们一个计算上述不动点的公式。

把置换拆解成循环置换，设拆解出的循环置换的个数为 $d$，对于一个**小元素**（本题中为一个方案）里的基本单位（本题中为点）有 $n$ 个种类（本题中为颜色），那么方案数为 
 $\frac{1}   {N}\displaystyle\sum_{i = 1}^{N}n^{d_i}$，$d_i$ 为置换群里的某个置换拆解出的循环置换的个数。

感性理解，由于要求不动点，那么小元素在置换后应该不变，拆成的循环置换之间独立，就是每个循环置换内不变，那么只能每个循环置换内涉及到的点的颜色都一样。一共有 $n$ 种颜色， 有 $d$ 个独立的循环置换，那么对于这一个置换而言，他的贡献就是  $\frac{1}{N}n^{d}$（每个循环置换都可以染 $n$ 种颜色中任意一种）。把 $N$ 个置换的价值加起来就是上式。

----------

### 本题做法

解决三个量，$N, n, d$。

$N$: 有 $n$ 个点，所以这个环可以转 $0, 1, 2, 3 ……, n-1$ 位，他们分别为不同的置换，所以 $N = n$。

$n$：每个点有 $n$ 个颜色，所以 $n = n$。

$d$：设 $k$ 为目前的置换是转 $k$ 位，对于第 $x$ 个点，转 $t$ 次回到本身，那么有 $x + kt \equiv x \pmod n$

即 $kt \equiv 0 \pmod n$

即 $kt = rn$

$t = \frac{rn}{k}$

要求 $t$ 最小（循环置换内不能重复），也就是 $rn$ 刚好整除 $k$，设 $\gcd(n, k) = x, n = ax, k = bx$

即 $t = \frac{rn}{bx}$

由于 $r$ 可以任意取，使 $r = b$  后原式 $ = \frac{n}{x}$，$n$ 是确定的，为使 $x$ 可以表示 $k$，$x$ 能整除 $n$ 且得数最小，$x$  刚好应该取 $\gcd(n, k)$。

此时 $t = \frac{n}{\gcd(n, k)}$，$t$ 为转 $t$ 次回到本身，那么一个循环置换里就包含了 $t$ 个点，则一共有 $\frac{n}{t} =\frac{n}{\frac{n}{\gcd(n, k)}}=\gcd(n,k)$ 个循环置换，则  $d = n$。

下面就是简单的推式子：

$$
\begin{aligned}

&\frac{1}{n} \sum^{n}_{i = 1}n^{\gcd(n, i)} 

\\

=& \frac{1}{n} \sum_{d|n}n^{d}\sum_{i = 1}^{n}[\gcd(n, i) = d]

\\

=& \frac{1}{n} \sum_{d|n}n^{d}\sum_{i = 1}^{\frac{n}{d}}[\gcd(\frac{n}{d}, i) = 1]

\\

=& \frac{1}{n} \sum_{d|n}n^{d}\varphi(\frac{n}{d})

\end{aligned}
$$

$\sqrt{n} $ 枚举 $d$ 和求 $\varphi$，$\log$ 求幂，最后乘上   $n$ 的逆元输出即可。时间复杂度     $O(n^{\frac{3}{4}})$。

--------

### 代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

const int Mod = 1e9 + 7;

inline int read(){
	register int x = 0, f = 1; register char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x * f;
}

int T, n;
long long ans;
int len, tot;

long long Quick_Power(long long a, int b, int m){
    long long ans = 1;
    while(b){
        if(b & 1) ans = ans * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return ans;
}

int factor[10005];
void findFac(int n){
	int o = sqrt(n);
	for(int i = 1; i <= o; ++ i)
		if(n % i == 0){
			factor[++ tot] = i;
			if(i * i != n) factor[++ tot] = n / i;
		}
}

int euler(int c){
	int res = c;
	for(int i = 2; i <= c / i; ++ i){
		if(c % i == 0){
			while(c % i == 0) c /= i;
			res = res / i * (i - 1); // res = res - res / i;
		}
	}
	if(c > 1) res = res / c * (c - 1);
	return res;
}

signed main(){
	T = read();
	while(T --){
		memset(factor, 0, sizeof factor);
		tot = 0; ans = 0;
		n = read();
		findFac(n);
		sort(factor + 1, factor + tot + 1);
		for(int i = 1; i <= tot; ++ i)
			ans = (ans + Quick_Power(n, factor[i], Mod) * euler(n / factor[i]) % Mod ) % Mod;
		
		printf("%lld\n", ans * Quick_Power(n, Mod - 2, Mod) % Mod);
	}
}
```


---

## 作者：m256i (赞：1)

参考书籍：

* 《具体数学》4.9
* 《组合数学》14 章
* <https://blog.csdn.net/whereisherofrom/article/details/79631703>

做这道题你不需要会什么群论或者 Pólya（读 /ˈpoʊljə/，虽然匈牙利语里应该读 /ˈpoːjɒ/）定理（实际上这题应该是 Burnside 引理的板子），会一点数论（欧拉函数以及一些基础的莫反技巧）就行。

设长度为 $n$，$k$ 种颜色的答案为 $F(n,k)$。

先举个例子：按照 $1,2,3,4$ 为顺序的环可以变成多少种序列？

显然是四种：

* $1,2,3,4$
* $2,3,4,1$
* $3,4,1,2$
* $4,1,2,3$

对 $1,2,1,2$ 也做一遍：

* $1,2,1,2$
* $2,1,2,1$
* $\color{red}1,2,1,2$
* $\color{red}2,1,2,1$

其中出现了重复，每个不同的序列恰好出现两次，因为序列有一个长为 $2$ 的循环节。

$1,1,1,1$ 则是这样：

* $1,1,1,1$
* $\color{red}1,1,1,1$
* $\color{red}1,1,1,1$
* $\color{red}1,1,1,1$

序列出现了四次。

那么显然一个序列在 $nF(n,k)$ 种序列出现的次数就是旋转后不变的方案数。

现在给定一个 $m$，假设有 $G(m)$ 个序列旋转 $m$ 个点后不变，则：

$$
\begin{aligned}
nF(n,k)&=\sum_{\mathrm{SEQ}}\sum_{i=1}^{n}[\operatorname{Rotate}_i(\mathrm{SEQ})=\mathrm{SEQ}]\\
&=\sum_{i=1}^{n}\sum_{\mathrm{SEQ}}[\operatorname{Rotate}_i(\mathrm{SEQ})=\mathrm{SEQ}]\\
&=\sum_{i=1}^{n}G(i)
\end{aligned}
$$

这就是 Burnside 引理。

不难发现旋转 $m$ 个点不变意味着 $\gcd(n,m)$ 是它的循环节，因此 $G(m)=k^{\gcd(n,m)}$，代入进去：

$$
\begin{aligned}
F(n,k)&=\dfrac{1}{n}\sum_{i=1}^{n}k^{\gcd(i,n)}\\
&=\dfrac{1}{n}\sum_{i=1}^{n}\sum_{d \mid n}[\gcd(i,n)=d]k^d\\
&=\dfrac{1}{n}\sum_{d \mid n}k^d\sum_{i=1}^{n}[\gcd(i,n)=d]\\
&=\dfrac{1}{n}\sum_{d \mid n}k^d\sum_{i=1}^{\frac{n}{d}}[\gcd(id,n)=d]\\
&=\dfrac{1}{n}\sum_{d \mid n}k^d\sum_{i=1}^{\frac{n}{d}}\left[\gcd\left(i,\dfrac{n}{d}\right)=1\right]\\
&=\dfrac{1}{n}\sum_{d \mid n}k^d\varphi\left(\dfrac{n}{d}\right)\\
&=\dfrac{1}{n}\sum_{d \mid n}k^{\frac{n}{d}}\varphi(d)\\
\end{aligned}
$$

做的时候可以先质因数分解，然后在 dfs 过程中计算欧拉函数。

代码：

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#include <bitset>
#include <algorithm>
typedef long long ll;
typedef unsigned long long ull;

template <typename T>
void read(T &x){
    static char ch;
    x = 0;
    while (!isdigit(ch=getchar()));
    do x = (x<<3)+(x<<1)+(ch^'0');
    while (isdigit(ch=getchar()));
}

template <typename T>
void write(T x, char c = ' '){
    static char st[100], *p;
    if (x < 0) putchar('-'), x = -x;
    if (x == 0) putchar('0');
    for (p = st; x; x /= 10) *++p = x%10;
    for (; p != st; --p) putchar(*p|'0');
    putchar(c);
}

template <typename T>
inline void writeln(T x){write(x, '\n');}

ll P = 1e9+7;

template <typename T>
inline T pow(T x, T y){
    T ans = 1;
    while (y){
        if (y&1) ans = (ans*x)%P;
        x = (x*x)%P;
        y >>= 1;
    }
    return ans;
}

ll a[50];
size_t v[50];
ll n, ans;
size_t cnt;

void dfs(size_t dep, ll phi, ll d){
    if (dep == cnt){
        ans = (ans+phi*pow(n, n/d))%P;
        return;
    }
    dfs(dep+1, phi, d); // p^0
    ll p = phi*(a[dep]-1); d *= a[dep]; dfs(dep+1, p, d); // p^1
    for (size_t i = 2; i <= v[dep]; ++i) p *= a[dep], d *= a[dep], dfs(dep+1, p, d);    
}

int main(){
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
    int t; read(t);
    for (; t; --t){
        read(n); ll x = n;
		cnt = 0;
		for (int i = 2; i*i <= x; ++i){
			if (!(x%i)){
				a[cnt] = i, v[cnt] = 0;
				while (!(x%i)) ++v[cnt], x /= i;
				++cnt;
			}
		}
		if (x > 1) a[cnt] = x, v[cnt++] = 1;
        ans = 0; dfs(0, 1, 1);
        writeln(ans*pow(n, P-2)%P);
    }
    
    
    return 0;
}
```

---

## 作者：WeLikeStudying (赞：1)

- 作者并不只希望理解群论的基本内容，还希望就此理解抽象代数的一些知识。
- 作者虽然退役了，但是信息学的光芒将会照亮这个时代。
- 作者的内心也应该平和一点，作者存在着诸多不足，这些不足是应该，也是必须去弥补的，作者的目标不应该首先是在信息学中取得成就，而应该首先拥有完整的人格。

**借鉴**
- [这篇](https://www.luogu.com.cn/blog/command-block/qun-lun-xiao-ji)，[这篇](https://oi-wiki.org/math/group-theory/)，以及组合数学引论。
- ~~没用的东西~~专业的群论知识我尽量不写，因为~~作者很懒~~便于理解。
- 以下的内容极其不专业。

**群**
- 定义集合 $S$ 与二元运算 $\times$ 满足：
$$\forall a,b\in S,a\times b\in S$$
$$\forall a,b,c\in S,(a\times b)\times c=a\times( b\times c)$$
$$\exists e\in S,\forall a\in S,a\times e=a$$
$$\forall a\in S,\exists b\in S,a\times b=e$$
- 即封闭性，结合律，单位元，逆元（其中 $a$ 的逆元为 $a^{-1}$），称 $S$ 在 $\times$ 运算下是个群。

**简单定理**
- 单位元唯一：$e_1,e_2$ 是单位元则 $e_1\times e_2=e_1=e_2$。
- $a\times c=b\times c\to a=b$：同乘逆元。
- 逆元唯一：$ab=e=ac\to b=c$。
- 对于任意有限群，设 $a^b$ 是 $b$ 个 $a$ 相乘的结果，则对于每个 $a$ 都存在 $\text{ord}(a)$ 满足 $a^{\text{ord}(a)}=e$，且 $a^{-1}=a^{\text{ord}(a)-1}$。
- 直接构造 $a^0,\cdots,a^n$，根据鸽巢原理肯定有两个相等，设 $a^x=a^y$ 则 $a^{y-x}=e$，非常合理对吧。

**置换群**
- 置换是一个排列，置换的乘法就是把 $i$ 换成 $p_i$。
- 置换不满足交换律，但满足结合率，单位元是 $i=p_i$，逆元也很好求，所以 $n$ 元置换组成的结合与乘法直接成群。
- 我们用环表示置换，即把 $i\to p_i$ 的边表示出来形成的多个环写出来。
- 我们也喜欢用几个基本置换，把大小为 $1$ 的置换隐去，表示所有置换。
- 置换还可以和整数运算，具体细节十分简单就不重点提及，我们通过把集合标号成整数的方式来实现它。

**前置知识**
- 我们研究的问题是在一个集合 $|S|$ 内的元素，通过置换群 $|G|$ 的置换，形成的等价类个数的问题，请务必注意这点。
- 不动点：设 $k\times p=k$ 则元素 $k$ 是置换 $p$ 下的不动点，$p$ 形成的集合组成的置换群为 $Z_k$ 为 $k$ 不动置换类，经过 $p$ 的不动点组成集合 $C_p$。
- 等价类：设 $E_k$ 为元素 $k$ 经过置换群 $G$ 中的元素能到达的集合，由于群的特性，等价类中任何一个元素的等价类都是该等价类，而且每个元素至少是完全图的连边，都可以一步到达。
- 注意不动置换类是置换群，等价类是元素集合。
- 等价类和不动点定理：$|Z_k|\times |E_k|=|G|$，即使得 $k$ 不动的置换个数，乘上 $k$ 的等价类个数，恰好是置换总个数。
- 我们设 $E_k=\{a_1,\cdots a_m\}$，再对每个 $a_i$ 瞎弄一个置换 $p_i$，使得 $k\times p_i=a_i$，然后让 $G_i=Z_k\times p_i$（也就是让每个置换和该置换搞下形成新的置换群），你发现对于 $i\ne j$，$G_i\cap G_j=\varnothing$，且 $|G_i|=|Z_k|$，剩下的唯一问题在于证明 $G_i$ 不交。
- 由于显然 $G_1\cup\cdots\cup G_m\subseteq G$，而对于任意 $p\in G$，一定存在 $k\times p=a_i$，所以 $G\subseteq G_1\cup\cdots\cup G_m$，所以 $|Z_k|\times |E_k|=|G|$。

**Burnside 引理**
- 对于 $|S|$ 内元素形成的等价类个数 $l$：
$$l=\frac 1{|G|}\sum_{p\in G}|C_p|$$
- 也就是等价类个数为在各个置换下不动的元素个数的平均数。
- 设 $f(i,j)$ 表示元素 $i$ 在置换 $j$ 的作用下是否不动，返回 $0/1$。
$$\sum_{i\in S}f(i,j)=|C_j|$$
$$\sum_{j\in G}f(i,j)=|Z_i|$$
- 因此：
$$\sum_{i\in S}|Z_i|=\sum_{j\in G}|C_j|$$
- 设 $l$ 个等价类分别为 $E_1,\cdots,E_l$。
- 原式直接变成：
$$\sum_{p\in G}|C_p|=\sum_{i\in S}|Z_i|=\sum_{i=1}^l|Z_i||E_i|=l|G|$$
- 证明完毕，对于染色问题（很非形式化的表达）我们还有个小定理。

**Pólya 定理**
- 给 $S$ 中的元素染个色！假设有 $n$ 种元素，每种元素有 $m$ 种染色方法，设 $G$ 是这 $n$ 种元素的置换群，则染色形成的等价类个数：
$$\frac1{|G|}\sum_{p\in G}T(p)$$
- $T(p)$ 表示在 $p$ 置换下的不动点染色方案数。
- 这个怎么理解？咱们当然用上面那个定理，搞一个有 $m^n$ 个元素的集合 $S'$，然后把映射也挪到上面，变成群 $G'$。
- 此时答案是：
$$l=\frac 1{|G'|}\sum_{p\in G}|C_p|$$
- 你发现 $|C_p|$ 很熟悉，就是 $T(p)$，然后你发现 $G'$ 只是元素变成了更长的排列，其它根本就没变，然后就证完了。
- 等等，如何求 $T(p)$ 呢？还记得循环拆解吗？你发现每个循环必须颜色相同并且只有这个条件，设 $d(p)$ 为 $p$ 置换的循环个数，完整的定理叫做：
$$\frac1{|G|}\sum_{p\in G}m^{d(p)}$$

**[习题 1](https://www.luogu.com.cn/problem/P4980)**
- 纯纯模板题，你掐指一算，发现循环移位 $k$ 能够拆成 $\gcd(k,n)$ 个循环，所以答案是：
$$\frac1n\sum_{i=1}^nm^{\gcd(i,n)}$$
- 强行枚举指数（它一定是 $n$ 的约数）我们得到：
$$\frac1n\sum_{d|n}m^d\varphi(n/d)$$
- 连莫比乌斯反演都不用，真的惊呆了，可以强行使用二次筛法做到亚指数复杂度，[代码](https://www.luogu.com.cn/paste/2c9e4iwm)。

**[习题 2](https://www.luogu.com.cn/problem/P4727)**
- 图同构判定都是 Open 的你直接跳到计数？还给出了 $n\le 60$ 的奇葩范围，我也是醉了，果断打表，[表](http://oeis.org/A000088/b000088.txt)，这个表足足给到了 $n\le 87$，如果你有能耐打它对某个数取模的结果，那也是可以的，[代码](https://www.luogu.com.cn/paste/lyxl7tn0)，当然，这种做法太不讲武德了。
- 这个提示也告诉你只要你掌握了理论上能跑出来的做法就不需要担心常数了（虽然[这题](https://www.luogu.com.cn/problem/P4128)加大了难度，还更改了模数，为我们提供了一个先进示范）。
- 容易发现这个问题可以转化成边染色问题，而置换可以理解成对点进行重排，但是这个置换群的大小是 $n!$，甚至无法逐个枚举。
- 考虑每个点置换形成的一堆环，显然，环的大小分别相同的时候的时候，贡献（这个置换的不动点个数）肯定相同，而环的大小各不相同的情况有多少呢？[这个](https://oeis.org/A000041)数列（还有[这题](https://www.luogu.com.cn/problem/P6189)）告诉我们，大概有 $\frac1{4n\sqrt3} e^{\pi\sqrt{2n/3}}$，是奇妙的亚指数复杂度，在 $n=60$ 时只有 $966467$ 个状态。
- 问题在对于一堆数如何求它形成的置换个数，由于个数固定，我们可以先组合划分，再求原排列，但是还要考虑相同个数的问题，如果有多个相同的话还要乘回来，这个排列又是固定的，容易算的。
- 问题还在于求这类置换的不动点个数，我们可以暴力并查集染色，也可以利用圆圈，对圈内与圈外分别讨论：对于圈内的边所连两点的最短距离相同的一定在同一个等价类，对于圈外的容易发现它和公约数有关，[代码](https://www.luogu.com.cn/paste/e97lz7je)，[有色图代码](https://www.luogu.com.cn/paste/15679dze)。

---

