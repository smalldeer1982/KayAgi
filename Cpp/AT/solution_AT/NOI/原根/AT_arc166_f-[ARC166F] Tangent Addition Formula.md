# [ARC166F] Tangent Addition Formula

## 题目描述

给定素数 $p$ 以及非负整数 $a,\ b$。

请判断是否存在一个长度为无穷的非负整数序列 $t = (t(0),\ t(1),\ t(2),\ \ldots)$，使其满足以下所有条件：

- 对任意非负整数 $x$，都有 $0 \leq t(x) < p$。
- 对任意非负整数 $x,\ y$，都有 $t(x+y)\bigl(1-t(x)t(y)\bigr)\equiv t(x)+t(y)\pmod{p}$。
- $t(a) = b$。

给定 $T$ 组测试数据，请分别回答每组数据是否存在满足条件的非负整数序列 $t$。

## 说明/提示

### 限制

- $1 \leq T \leq 2 \times 10^5$
- $p$ 是满足 $1 \leq p \leq 10^9$ 的素数。
- $0 \leq a \leq 10^{9}$
- $0 \leq b < p$

### 样例解释 1

- 当 $p=11,\ a=1,\ b=0$ 时：常数序列 $t = (0,0,0,0,\ldots)$ 满足条件。
- 当 $p=11,\ a=1,\ b=5$ 时：周期为 $3$ 的数列 $t = (0,5,6,0,5,6,\ldots)$ 满足条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
11 1 0
11 1 1
11 1 3
11 1 5```

### 输出

```
Yes
No
No
Yes```

## 样例 #2

### 输入

```
5
5 0 0
5 1 1
5 2 2
5 3 3
5 4 4```

### 输出

```
Yes
No
Yes
Yes
No```

## 样例 #3

### 输入

```
7
2 3 1
2 5 0
5 0 1
5 0 2
7 1 4
11 12345 5
13 12345 5```

### 输出

```
Yes
Yes
No
Yes
No
No
Yes```

# 题解

## 作者：littlez_meow (赞：3)

很漂亮的数论加抽代题，太神了。

[题目指路](https://www.luogu.com.cn/problem/AT_arc166_f)。

# step 1：转化

拿到这道题，一开始可能是懵掉的。$t$ 的性质二 $\forall x,y\in \mathbb{N},t(x+y)(1-t(x)t(y))\equiv t(x)+t(y)\pmod p$ 看起来完全没法下手。但这个式子在三条性质中最复杂，肯定有用，下记为式 $(\star)$。

可能会先用抽象函数题的套路来求一些特值什么的。带入 $x=0,y=0$，得到 $t(0)(1-t(0)^2)\equiv 2t(0)\pmod p$，解得 $t(0)=0$ 或 $t(0)^2\equiv -1\pmod p$。设 $I^2\equiv-1\pmod p$，即模 $p$ 意义下虚数单位，则 $t(0)\in\{I,-I,0\}$。

看上去还是没什么用。

有什么特殊的数列？$t=(0,0,0,\cdots)$ 满足 $(\star)$，但这只说明 $b=0$ 时 $t$ 存在。

扫一眼标题，Tangent Addition Formula，正切和角公式？有什么关系呢？

写出和角公式 $\tan(x+y)=\dfrac{\tan(x)+\tan(y)}{1-\tan(x)\tan(y)}$，对比 $(\star)$，发现正好就是移了项少了取模。因此，数列 $t$ 肯定和正切函数脱不了关系。更进一步，$t(x)$ 就是某种模意义下的正切函数。（说某种是因为要求 $t(a)=b$。

怎么办？泰勒展开肯定不现实，$\tan x$ 的系数和伯努利数有关，还要取模，很麻烦。三角函数还有什么？欧拉公式！

首先展开 $\tan(x)=\dfrac{\sin(x)}{\cos(x)}$。

根据欧拉公式 $e^{ix}=\cos(x)+i\sin(x)$，得到 $\sin(x)=\dfrac{e^{ix}-e^{-ix}}{2i},\cos(x)=\dfrac{e^{ix}+e^{-ix}}{2}$。

相除得到下式：

$$\tan(x)=\dfrac{1-(e^{2i})^{x}}{1+(e^{2i})^{x}}\times i$$

形式上 $\tan(x)$ 形如 $\dfrac{1-r^{x}}{1+r^{x}}\cdot i$

那就猜 $t(x)$ 也长这样，把 $i$ 换成上文中的 $I$。

因此有：

**【结论 1】** $t(x)$ 形如 $\dfrac{1-r^{x}}{1+r^{x}}\cdot I$，其中 $I^2\equiv -1\pmod p$。

证明：将该式带入 $(\star)$，得到：

$$t(x+y)(1-t(x)t(y)) = \dfrac{1-r^{x+y}}{1+r^{x+y}}\cdot I\cdot(1-\dfrac{1-r^{x}}{1+r^{x}}\cdot I\cdot\dfrac{1-r^{y}}{1+r^{y}}\cdot I)$$

利用 $I^2\equiv -1\pmod p$，得到：

$$\equiv\dfrac{1-r^{x+y}}{1+r^{x+y}}\cdot I\cdot(1+\dfrac{(1-r^x)(1-r^y)}{(1+r^x)(1+r^y)})\pmod p$$

将分子分母去括号并通分，得到：

$$\equiv\dfrac{1-r^{x+y}}{1+r^{x+y}}\cdot I\cdot\dfrac{2(1+r^{x+y})}{1+r^x+r^y+r^{x+y}}\pmod p$$

约分，分解因式，得：

$$\equiv I\cdot\dfrac{(1+r^x)(1-r^y)+(1-r^x)(1+r^y)}{(1+r^x)(1+r^y)}\pmod p$$

拆开分子，得：

$$\equiv \dfrac{1-r^y}{1+r^y}\cdot I+\dfrac{1-r^x}{1+r^x}\cdot I\pmod p$$

再代回去：

$$\equiv t(x)+t(y)\pmod p$$

左边同余于右边，$(\star)$ 成立。原命题得证。

上面除了 $I^2\equiv -1\pmod p$ 都是恒等变换，因此原问题变成了和 $I$ 相关的问题。而这个式子，就是二次剩余。

为了叙述方便，下面记模 $p$ 意义下的整数域为 $\mathbb{Z}_p$。

# step 2：分类

由于二次剩余的 $-1$ 很奇特，我们选择分情况讨论。

## part 1：$p=2$

在讨论二次剩余时往往只考虑奇质数，因此这里我们也把 $p=2$ 单拎出来。

若 $b=0$，则可以有 $t=(0,0,0,\cdots)$ 满足 $(\star)$。

若 $b=1$，则可以有 $t=(1,1,1,\cdots)$ 满足 $(\star)$。

由于这两种数列的取值和项数无关，对于所有 $a$ 都能这样取。

因此，此时 $t$ 存在。

## part 2：$p\equiv 1\pmod 4$

为什么要分这一类？因为有如下结论：

**【结论 2】** $p\equiv 1\pmod 4\Leftrightarrow \exists I\in\mathbb{Z}_p,I^2\equiv-1\pmod p$，其中 $p$ 为奇质数。

证明：

设 $p$ 的最小正原根为 $g$。由原根存在性定理，$g$ 存在。

由 $g^{p-1}\equiv 1\pmod p$，$g$ 可视为 $\mathbb{Z}_p$ 下 $p-1$ 次单位根。由 $I^4\equiv 1\pmod p$，$I$ 可视为 $\mathbb{Z}_p$ 下 $4$ 次单位根。

因此有 $I=g^{\frac {p-1} 4}$。若 $I$ 存在，则 $\dfrac {p-1} 4\in\mathbb{Z}$，即 $4|p-1$

故若 $I$ 存在，则 $p\equiv 1\pmod 4$，必要性得证。

对于充分性，取 $I\equiv g^{\frac {p-1} 4}\pmod p$，满足题意。

原命题得证。

既然如此，再结合上 $t(0)\in\{I,-I,0\}$，我们继续分类。

请注意，为了叙述简介，下面所有结论都有前提条件 $p\equiv 1\pmod 4$。

### part 2.1：$t(1)\in\{I,-I\}$

我们有下面的结论：

**【结论 3】** 若 $t(1)\in\{I,-I\}$，则 $\forall x\in\mathbb{N^+},t(x)=t(1)$。

证明：考虑数学归纳法，当 $x=1$ 时显然相等。

现在假设当 $x=n\in\mathbb{N^+}$ 时成立，即 $t(n)=t(1)$，下证当 $x=n+1$ 时成立。

$$t(n+1)(1-t(n)t(1))\equiv t(n)+t(1)\pmod p$$

代入 $t(n)=t(1)$，得：

$$t(n+1)(1-t(1)^2)\equiv 2t(1)\pmod p$$

代入 $t(1)^2\equiv -1\pmod p$，两边同时除以 $2$，得到 $t(n+1)=t(1)$。

原命题得证。

由此可得，本类的合法 $t$ 有且仅有六种情况：

1. $t=(I,I,I,I,\cdots)$

2. $t=(I,-I,-I,-I,\cdots)$

3. $t=(0,I,I,I,\cdots)$

4. $t=(0,-I,-I,-I,\cdots)$

5. $t=(-I,I,I,I,\cdots)$

6. $t=(-I,-I,-I,-I,\cdots)$

### part 2.2：$t(1)\notin\{I,-I\}$

这玩意和 $t(0)$ 看上去是有关系的，我们考虑这种情况下 $t(0)$ 的值，有下面结论：

**【结论 4】** 若 $t(1)\notin\{I,-I\}$，则 $t(0)=0$。

证明：考虑证明其逆否命题，即若 $t(0)\neq 0$，则 $t(1)\in\{I,-I\}$。

将 $x=0,y=1$ 代入 $(\star)$，得到 $t(1)(1-t(1)t(0))\equiv t(1)+t(0)\pmod p$。

化简得到 $(t(1)^2+1)t(0)\equiv 0\pmod p$。

因为 $t(0)\neq 0$，两边同时除以 $t(0)$，移项得 $t(1)^2\equiv -1\pmod p$。

解得 $t(1)\in\{I,-I\}$。

原命题得证。

将特值代入 $(\star)$ 也起不了效果了，只能求助结论 1 了。

由于分母不能为 $0$，所以要求 $\forall x\in\mathbb{N},r^x\not \equiv-1\pmod p$。如果存在 $r\in\mathbb{Z}_p$，则 $t$ 存在，否则 $t$ 不存在。

真的是这样吗？

不要忘记了性质三：$t(a)=b$。我们可以列方程 $b\equiv \dfrac{1-r^a}{1+r^a}\cdot I\pmod p$。

化简得到 $r^a\equiv \dfrac{I-b}{I+b}\pmod p$，是个模为质数的高次剩余方程，原根加 BSGS 就能解。

也就是说，在本分类下，$t$ 存在当且仅当存在 $r\in\{r|r^a\equiv \dfrac{I-b}{I+b}\pmod p\}$ 使得 $\forall x\in\mathbb{N},r^x\not\equiv -1\pmod p$。

## part 3：$p\equiv 3\pmod 4$

这下没有模意义下虚数单位了，$t$ 还有可能存在吗？有可能。

例如样例中 $p=11,a=1,b=5$，则 $t=(0,5,6,0,5,6,\cdots)$ 满足 $(\star)$。

束手无策了？

不。我们还有一条路：扩域。

既然在普通的模意义下整数域上没有，那就请出高斯整环 $\mathbb{Z}(i)$。

不妨记模 $p$ 意义下高斯整环为 $\mathbb{Z}(i)_p=\{a+bi|a,b\in\mathbb{Z}_p\}$，不难得出这玩意是个有限域。

根据 part 2.2 的讨论，我们有这里 $t(0)=0$，在下面不讨论。

在强行添加上虚数单位后，我们来继续研究 $t$ 的存在条件。

由于对于所有 $x\in\mathbb{Z}_p$ 可以看作 $x+0\cdot i\in\mathbb{Z}(i)_p$，因此 $\mathbb{Z}_p\subseteq\mathbb{Z}(i)_p$。

依题有 $t(x)=\dfrac{1-r^x}{1+r^x}\cdot i\in\mathbb{Z}_p$，因此 $r\in\mathbb{Z}(i)_p$ 应该满足 $\forall x\in\mathbb{N},\dfrac{1-r^x}{1+r^x}\cdot i\in\mathbb{Z}_p$ 且 $r^x\not\equiv -1\pmod p$。

判断属不属于集合还是太麻烦了。能不能转化一下？当然可以。我们有如下结论：

**【结论 5】** $\forall x\in\mathbb{N},\dfrac{1-r^x}{1+r^x}\cdot i\in\mathbb{Z}_p\Leftrightarrow r^{p+1}\equiv1\pmod p$

证明：根据二项式定理有 $(x+y)^p\equiv x^p+y^p\pmod p$。（仅有 $\dbinom{p}{0}$ 和 $\dbinom{p}{p}$ 不能被 $p$ 整除，其余均含因数 $p$。）

设 $z=x+yi\in\mathbb{Z}_p$，则 $z^p\equiv x^p+(yi)^p\pmod p$。

由于 $p\equiv 3\pmod 4$，有 $i^p=-i$，因此 $z^p\equiv x^p-y^pi\pmod p$

根据费马小定理，$x^p\equiv x\pmod p$，所以 $z^p\equiv x-yi\pmod p$。

当且仅当 $y=0$，即 $z\in\mathbb{Z}_p$ 时，$z=x-yi$。

故 $z\in\mathbb{Z}_p\Leftrightarrow z^p\equiv z\pmod p$。

代入 $z=\dfrac{1-r^x}{1+r^x}\cdot i$，原命题可转化为：

$$(\dfrac{1-r^x}{1+r^x}\cdot i)^p\equiv\dfrac{1-r^x}{1+r^x}\cdot i\pmod p\Leftrightarrow r^{p+1}\equiv1\pmod p$$

移项有：

$$(\dfrac{1-r^x}{1+r^x}\cdot i)^p-\dfrac{1-r^x}{1+r^x}\cdot i\equiv 0\pmod p$$

拆括号，得到：

$$-\dfrac{(1-r^x)^p}{(1+r^x)^p}\cdot i-\dfrac{1-r^x}{1+r^x}\cdot i\equiv 0\pmod p$$

两边同乘 $-\dfrac 1 i$，得：

$$\dfrac{(1-r^x)^p}{(1+r^x)^p}+\dfrac{1-r^x}{1+r^x}\equiv 0\pmod p$$

用上面二项式定理的推论展开幂次，得：

$$\dfrac{1-r^{xp}}{1+r^{x^p}}+\dfrac{1-r^x}{1+r^x}\equiv 0\pmod p$$

通分，得：

$$\dfrac{1-(r^{p+1})^x}{1+r^x+r^{px}+r^{(p+1)x}}\equiv 0\pmod p$$

去分母，移项，得：

$$(r^{p+1})^x\equiv 1\pmod p$$

由于该式对于所有 $x$ 均成立，可以去掉指数，得：

$$r^{p+1}\equiv 1\pmod p$$

充分性得证。以上各式均为恒等变换，反过来可证明必要性。

原命题得证。

和上面同样解方程 $b\equiv \dfrac{1-r^a}{1+r^a}\cdot i\pmod p$，解得 $r^a\equiv \dfrac{i-b}{i+b}\pmod p$。

问题来了。我们不知道这玩意有没有原根，没办法 BSGS，怎么办？

真的是这样吗？

还记得我们说 $\mathbb{Z}(i)_p$ 是个有限域吗？

这个域共有 $p^2$ 个元素，根据有限域的存在性和唯一性，其为有限域 $\mathbb{F}_{p^2}$。

打开你的抽代课本，我们有以下结论：

**【结论 6】（有限域原根存在性）** 有限域 $\mathbb{F}$ 存在元素 $g$ 使得 $g^n=1,\mathbb{F}=\{g^t|0\le t<n\}$。

大致证明思路：有限域的非零元素乘法群 $(\mathbb{F}/\{0\},\times)$ 是循环群，取该循环群生成元即为原根。

# step 3：存在性判定

综合上述讨论，我们最终得到 $t$ 的存在性判定方式。

当 $p=2$ 或 $b=0$ 或 $b^2\equiv -1\pmod p$ 时，$t$ 存在。

否则，若 $t$ 存在，则存在 $r$ 满足以下三个条件：

1. $r^a\equiv u\pmod p$

2. $r^v\equiv 1\pmod p$

3. $\forall x\in\mathbb{N},r^x\not\equiv-1\pmod p$

其中 $u=\dfrac{i-b}{i+b},i^2\equiv-1\pmod p,v=\left\{\begin{matrix}
 0 & (p\equiv 1\pmod 4)\\
 p+1 & (p\equiv 3\pmod 4)
\end{matrix}\right.$。

如何快速判定？这时就要上原根了。

下记循环群大小 $n=\left\{\begin{matrix}
 p-1 & (p\equiv 1\pmod 4)\\
 p^2-1 & (p\equiv 3\pmod 4)
\end{matrix}\right.$。

设 $r\equiv g^t\pmod p$，则 $r^v\equiv g^{tv}\equiv 1\pmod p$。

由 $g^n\equiv 1\pmod p$，得到 $n|tv$，因此有 $\dfrac n {\gcd(n,v)}|t$。

同理，由 $r^x\not\equiv-1\pmod p$ 得 $g^{2tx}\not\equiv1\pmod p$

因此 $tx\not\equiv\dfrac n 2\pmod n$。这玩意可以继续除下去直到 $n$ 中的 $2$ 因数被除干净。

设 $2^m|n,2^{m+1}\nmid n$，则可以推出 $2^m|t$。

所以 $t$ 的一个取值是 $\operatorname{lcm}(\dfrac n {\gcd(n,v)},2^m)$。

不妨就令 $t$ 为该值。则再设 $r\equiv g^{tk}$。

还差条件一，代入 $r$ 得 $g^{atk}\equiv u$。

再和上面一样的做法，得出 $u^{\frac{n}{\operatorname{gcd}(at, n)}}=1$。

就此判断完毕！

# step 4：时间复杂度与细节

我们发现并不需要指数和原根的具体值，只需要快速幂和最大公约数，时间复杂度 $O(T\log p)$。

记得不要忘记判前面分类 part 1 和 part 2.1 的特殊情况。

# step 5：附上代码
```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define ll long long
using namespace std;
int T,p,a,b;
int imod;
mt19937 gen(time(0)^*new int);
inline ll qpow(ll base,int expo){
	base=(base+p)%p;
	ll res(1);
	while(expo){
		(expo&1)&&(res=res*base%p);
		base=base*base%p;
		expo>>=1;
	}
	return res;
}
inline bool euler(int x){
	return qpow(x,(p-1)>>1)==1;
}
struct Complex{
	ll re,im;
	inline bool operator==(Complex x){
		return re==x.re&&im==x.im;
	}
	inline Complex operator*(Complex x){
		Complex res;
		res=(Complex){re*x.re%p+imod*x.im%p*im%p,im*x.re%p+re*x.im%p};
		res.re>=p&&(res.re-=p);
		res.im>=p&&(res.im-=p);
		return res;
	}
	inline Complex operator^(ll expo){
		Complex res({1,0}),base(*this);
		while(expo){
			(expo&1)&&(res=res*base,1);
			base=base*base;
			expo>>=1;
		}
		return res;
	}
};
inline void cipolla(int n,int&x){
	int qwq;
	do{
		qwq=gen()%p,imod=1ll*qwq*qwq%p-n;
		imod<0&&(imod+=p);
	}while(!qwq||euler(imod));
	x=((Complex){qwq,1}^((p+1)>>1)).re;
	p-x<x&&(x=p-x);
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	for(cin>>T;T;--T){
		cin>>p>>a>>b;
		if(p==2||b==0||1ll*b*b%p+1==p){
			cout<<"Yes\n";
			continue;
		}
		ll n;
		if((p&3)==1){
			n=p-1;
			int I;
			cipolla(p-1,I);
			ll t=n/(n&(-n));
			t/=__gcd(1ll*a,t);
			int u=(I-b)*1ll*qpow(I+b,p-2)%p;
			u<0&&(u+=p);
			if(qpow(u,t)==1) cout<<"Yes\n";
			else cout<<"No\n";
		}else{
			n=1ll*p*p-1;
			imod=p-1;
			ll t=n/((n&(-n))/__gcd((n&(-n)),p-1ll)*(p-1));
			t/=__gcd(1ll*a,t);
			int inv=qpow(b*1ll*b%p+1,p-2);
			Complex u={(1-b*1ll*b%p+p)*inv%p,1ll*(b<<1)%p*inv%p};//(i-b)/(i+b)=(1-b^2+2bi)/(b^2+1)
			if((u^t)==(Complex){1,0}) cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
	return 0;
} 
```
完结撒花 0v0~

---

## 作者：Leasier (赞：3)

~~第一步就十分抽象了。~~

考虑一般的 $\tan$ 函数的表达式：$\tan(x) = \dfrac{\sin(x)}{\cos(x)} = \dfrac{e^{ix} - e^{-ix}}{i(e^{ix} + e^{-ix})}$。令 $s = e^{2i}$，则 $\tan(x) = i \cdot \dfrac{1 - s^x}{1 + s^x}$。

我们可以把这一点扩展到这里的 $t(x) = i \cdot \dfrac{1 - s^x}{1 + s^x}$，其中 $s \in \mathbb{C}$。

------------

显然 $t(x)$ 是存在**循环**的。

考虑 $t(0)$，解方程可得 $t(0) = 0, \pm i$。下面分类讨论。

- $t(0) = \pm i$

解方程可得此时 $t$ 只有以下四种情况：

- $[i, i, \cdots]$。
- $[i, -i, -i, \cdots]$。
- $[-i, -i, \cdots]$。
- $[-i, i, i, \cdots]$。

于是 $(b^2 + 1) \bmod p = 0$ 时一定有解。

- $t(0) = 0$

$b = 0$ 显然有解，因为全 $0$ 满足条件。

否则，分 $p \bmod 4$ 的值讨论。

1. $p = 2$：此时显然有解。

2. $p \bmod 4 = 1$

此时 $-1$ 在 $\bmod \ p$ 意义下存在二次剩余——设其为 $I$。

则我们可以得出 $s^a = \dfrac{I - b}{I + b}$。

接下来考虑一下我们对 $s$ 的限制：$\forall x \geq 0, s^x \not\equiv -1 \pmod p$。

由于质数存在原根，该条件等价于 $e = v_p(\frac{p - 1}{2}), 2^e \mid \operatorname{ord}_p(s)$。

再结合上面 $s^a$ 的值，我们可以得出一个判断条件：

- $\gcd(a 2^e, p - 1) \mid \operatorname{ord}_p(s^a)$。

于是我们判断 $(s^a)^{\frac{p - 1}{\gcd(a 2^e, p - 1)}} \bmod p$ 是否为 $1$ 即可。

3. $p \bmod 4 = 3$

可惜此时 $-1$ 在 $\bmod \ p$ 意义下不存在二次剩余 /ng

我们尝试给出此情况下的数集 $G_p = \{a + bi \mid a, b \in F_p, a + b > 0\}$（也就是 $\bmod \ p$ 意义下的高斯整数）的“原根”状物。

注意到此时 $p$ 是**高斯质数**（其范数 $N(p) = p^2$ 根据费马平方和定理无法进行平方和拆分），则感性理解可得这样的数确实存在。

接下来的步骤与 2. 中基本相同，略去。

综上，写一个 Cipolla 求二次剩余和扩域快速幂即可。时间复杂度为 $O(T \log p)$。

代码：
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long ll;
typedef __int128 lll;

typedef struct Complex_tag {
	ll re;
	ll im;
	Complex_tag(ll re_, ll im_){
		re = re_;
		im = im_;
	}
} Complex;

bool operator ==(const Complex a, const Complex b){
	return a.re == b.re && a.im == b.im;
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline ll legendre(ll n, int mod){
	if (n == 0) return 0;
	return quick_pow(n, (mod - 1) / 2, mod);
}

inline int rand32(){
#if RAND_MAX == 0x7fff
	return rand() * rand();
#else
	return rand();
#endif
}

inline Complex mul(Complex a, Complex b, ll w, ll mod){
	return Complex(((a.re * b.re % mod + w * a.im % mod * b.im % mod) % mod + mod) % mod, (a.re * b.im % mod + a.im * b.re % mod) % mod);
}

inline Complex quick_pow(Complex x, ll p, ll w, ll mod){
	Complex ans(1, 0);
	while (p){
		if (p & 1) ans = mul(ans, x, w, mod);
		x = mul(x, x, w, mod);
		p >>= 1;
	}
	return ans;
}

inline ll cipolla(int n, int mod){
	n %= mod;
	if (n == 0) return 0;
	if (mod == 2) return 1;
	if (legendre(n, mod) == mod - 1) return -1;
	while (true){
		int a = rand32() % mod;
		ll w = (((ll)a * a % mod - n) % mod + mod) % mod;
		if (legendre(w, mod) == mod - 1) return quick_pow(Complex(a, 1), (mod + 1) / 2, w, mod).re;
	}
}

lll gcd(lll a, lll b){
	return b == 0 ? a : gcd(b, a % b);
}

int main(){
	int t;
	scanf("%d", &t);
	srand(time(NULL));
	for (register int i = 1; i <= t; i++){
		int p, a, b;
		scanf("%d %d %d", &p, &a, &b);
		if (p == 2 || b == 0 || (ll)b * b % p == p - 1){
			printf("Yes\n");
		} else if (p % 4 == 1){
			ll u = cipolla(p - 1, p), v = ((u - b) * quick_pow(u + b, p - 2, p) % p + p) % p;
			if (quick_pow(v, (p - 1) / gcd((ll)a << __builtin_ctz(p - 1), p - 1), p) == 1){
				printf("Yes\n");
			} else {
				printf("No\n");
			}
		} else {
			ll q = (ll)p * p - 1, inv = quick_pow(p - (ll)b * b % p - 1, p - 2, p);
			if (quick_pow(Complex(((ll)b * b % p - 1) * inv % p, (p - b * 2 % p) * inv % p), q / gcd((lll)a << __builtin_ctzll(q), q), p - 1, p) == Complex(1, 0)){
				printf("Yes\n");
			} else {
				printf("No\n");
			}
		}
	}
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：2)

## 0 在实数上讨论
求性质充分好的函数 $T : \mathbb R \to \mathbb R$，使得
$$
T(x+y) = \dfrac{T(x) + T(y)}{1 - T(x)T(y)}.
$$

*解:* 带入 $x = y = 0$，得 $T(0)$ 是方程 $X = \dfrac{2X}{1-X^2}$(即 $X^3+X=0$)的解，只考虑实数，得到 $T(0) = 0$；

下述过程中，会利用无穷小量简化语言，并不是完全严谨的（求救非标准分析大神）：
$$
\begin{aligned}
T(x + \varepsilon) &= \dfrac{T(x) + T(\varepsilon)}{1 - T(x) T(\varepsilon)} \\
T(x + \varepsilon) - T(x) &= \dfrac{\cancel{T(x)} + T(\varepsilon) - \cancel{T(x)} + T(x)^2 T(\varepsilon)}{1 - T(x) T(\varepsilon)} \\
&= \dfrac{\varepsilon T'(0)(1+T(x)^2)}{1-\varepsilon T(x) T'(0)} \\
\dfrac{T(x + \varepsilon) - T(x)}{\varepsilon} &= \dfrac{T'(0)(1+T(x)^2)}{1-\varepsilon T(x) T'(0)} \\
&\to T'(0) (1 + T(x)^2).
\end{aligned}
$$
设 $c = T'(0)$，这样所需只是解微分方程 $y' = c (1 + y^2)$：分离变量法。
$$
\begin{aligned}
\dfrac{\mathrm dy}{\mathrm dx} &= c(1 + y^2) \\
\dfrac{\mathrm dy}{1 + y^2} &= c \mathrm dx \\
\int \dfrac{\mathrm{d}y}{1+y^2} &= \int c \mathrm dx \\
\arctan y + C &= cx.
\end{aligned}
$$
结合上 $x = 0$ 时 $y = 0$ 显然 $C = 0$。这样，我们证明了 $T(x) = \tan(cx)$。

好，现在实数上满足条件的比较好的函数只有正切函数变换一个振幅(移项前还有平凡解 $T(x) = 1$)。似乎在 $\mathbb F_p$ 上，也如此……

## 1 正切的推广
发挥想象力：$\tan x$ 在数学分析上的定义是怎样的？
$$
\begin{aligned}
\tan x &= \dfrac{\sin x}{\cos x} \\
&= \dfrac{(\mathrm e^{\mathrm ix} - \mathrm e^{-\mathrm ix})/2 \mathrm i}{(\mathrm e^{\mathrm ix} + \mathrm e^{-\mathrm ix}) / 2} \\
&= \mathrm i \cdot \dfrac{1 - (\mathrm e^{2 \mathrm i})^x}{1 + (\mathrm e^{2 \mathrm i})^x}.
\end{aligned}
$$
我们需要 $\tan(cx)$，所以上式的 $\mathrm e^{2 \mathrm i}$ 可以变为 $\mathrm e^{2 c \mathrm i}$。这样，当 $c = \dfrac \pi k$ 时，$\mathrm e^{2 c \mathrm i}$ 可以视为 $\mathbb F_p$ 中的一个本原 $k$ 次单位根，使得 $\bmod\;p$ 意义下进行运算。因此，对于任意的 $R$ 都有对应的 $c$，所以，我们可以把 $\tan(cx)$ 写成 $\mathrm i \cdot \dfrac{1 - R^x}{1 + R^x}$。

现在分析这个函数在有限域 $\mathbb F_p$ 的性质：首先，考虑到 $R$ 的幂是一个周期函数。这样，$\tan(cx)$ 表现出一定的周期性。另外，由于 $R^x$ 在 $x \in \mathbb Z$ 时不能为 $-1$，所以 $R$ 的阶必须是奇数。

可意外发生了。我们在推导 $T$ 形如 $\tan(cx)$ 的时候，用到了 $T(0) = 0$，因为它符合多项式方程 $X^3 + X = 0$。然而，$\mathbb F_p$ 上，它可以有非 $0$ 的解。怎么办？我们要把问题归结到 $\mathrm i$ 的存在性了……

## 2 整数的三种素理想
**定理（Fermat）：** 素数 $p$ 能写成 $x^2 + y^2~(x, y \in \mathbb Z)$ 的形式，当且仅当 $p = 2$，或 $p \equiv 1 \pmod 4$；且解 $(x, y)$ 在重排、变号的意义下唯一。

*证明.* $\mathbb Z[\mathrm i]$ 是唯一分解整环。设 $\mathring a$ 表示集合 $\{a, -a, \mathrm ia, -\mathrm ia\} = a \bmod \mathbb Z[\mathrm i]^\times$。这样，根据唯一分解性，有
$$
\mathring a = \prod_{\mathring {\mathfrak p}} \mathfrak p^{n_\mathfrak p}, a^2 = N(\mathring a) = \prod_{\mathring{\mathfrak p}} N(\mathfrak p)^{n_{\mathfrak p}},
$$
其中 $N$ 是范数映射 $x + y \mathrm i \mapsto x^2 + y^2$。由于 $N(\mathfrak p)$ 均为整数，$\sum n_{\mathfrak p} \le \omega(a)$，其中 $\omega(x)$ 表示 $x$ 的素因子个数(计重数)。

取 $a = p$ 为素数，则 $\sum n_{\mathfrak p} \le 2$，因此，对其分成三类：

* **分歧** $n_\mathfrak p = 2$；
* **分裂** $n_\mathfrak p = n_\mathfrak q = 1$；
* **惯性** $n_\mathfrak p = 1$。

不难证明：分歧素数使得 $p = 2$。令 $\mathfrak{p} = x + \sqrt{-1}y \in \Z[\sqrt{-1}]$， 那么 $N(\mathfrak{p}) = x^2 + y^2$。 综上， 平方和问题 $p = x^2 + y^2$ 有解当且仅当 $p = N(\mathfrak{p})$， 此式成立时 $\mathfrak{p}$ 不可约， 正好对应到 $p$ 分裂或分歧的情形。 此时从唯一分解性 (精确到 $\pm 1, \pm\sqrt{-1}$ 和 $\mathfrak{p} \leftrightarrow \bar{\mathfrak{p}}$) 直接推出解 $(x,y)$ 的唯一性 (精确到符号和重排)。 欲证的断言归结到以下性质：素数 $p$
$$ \text{分歧} \iff p=2, \quad \text{分裂} \iff p \equiv 1 \pmod{4}, \quad \text{惯性} \iff p \equiv 3 \pmod{4}. $$
分歧情形 $p=2$ 已经处理。此外容易验证 $x^2 + y^2 \equiv 0, 1, 2 \pmod{4}$，因此 $p \equiv 3 \pmod{4}$ 导致 $p$ 是惯性素数。以下设 $p \equiv 1 \pmod{4}$。初等数论告诉我们 $(\Z/p\Z)^\times$ 是 $p-1$ 阶循环群；事实上任何有限域的乘法群皆循环。 任取 $(\Z/p\Z)^\times$ 的生成元 $g \bmod p$， 数论中称 $g$ 为 $\bmod\; p$ 的原根，那么 $g^{\frac{p-1}{2}} \equiv -1 \pmod p$，故整数 $t = g^{\frac{p-1}{4}}$ 满足同余式 $t^2 + 1 \equiv 0 \pmod p$。因而在 $\Z[\sqrt{-1}]$ 中 $p  \mid  (t + \sqrt{-1})(t - \sqrt{-1})$。显然 $p \nmid (t \pm \sqrt{-1})$，于是 $p$ 在 $\Z[\sqrt{-1}]$ 中可约， 从 $p \neq 2$ 遂知 $p$ 分裂。

> 上述证明完全选自李文威的《代数学方法》 $\S 5.7$。似乎可以只留最后一段，但是我更希望让 OIer 接触这三个术语。

对于一般的环，上述讨论变得更为复杂。请参考任何一本《代数数论》。

## 3 分歧
> $2$ 一到自然数集，所有的自然数便都看着他笑，有的叫道，「$2$，你又成为反例了！」他不回答，对零元说，「温 $2$ 碗酒，要 $2$ 碟茴香豆。」便排出 $2^2$ 文大钱。他们又故意的高声嚷道，「你一定又偷了人家的东西了！」$2$ 睁大眼睛说，「你怎么这样凭空污人清白……」「什么清白？我前天亲眼见你偷了 $\sqrt 2$ 的两本书，吊着打。」$2$ 便涨红了脸，额上的青筋条条绽出，争辩道，「取模不能算偷……取模！……素域的事，能算偷么？」接连便是难懂的话，什么「特征为 $0$」，什么「代数」之类，引得众人都哄笑起来：数集内外充满了快活的空气。
>
> 上述文字来自 cyb 酱的《孔 $22$》，这里，$2$ 确实也成为了反例。

讨论 $T(0)$ 的值：当 $T(0) = 1$ 时，向
$$
T(x+y)(1-T(x)T(y)) = T(x)+T(y)
$$
中带入 $x = 0$ 得 $T(y)$ 是方程 $X(1-X) = 1+X$ 的解，在 $\mathbb F_2$ 中它只能是 $1$；当 $T(0) = 0$ 时，考虑 $S = \{m \mid T(m) = 0\}$，可知 $S$ 对加法封闭（直接对 $T(m+n)$ 带入 $x=m, y=n$）、当减出来的值非负时还对减法封闭（类似地带入），因此 $S = n \mathbb N$。这样，
$$
T(x) = \begin{cases} 0 & x \in n \mathbb N, \\ 1 & x \notin n \mathbb N. \end{cases}
$$

## 4 分裂
此时，仍然有我们所说的不满足 $\tan(cx)$ 的「反例」。仍然是那个套路：讨论 $T(0)$ 的值：当 $T(0) = \pm \mathrm i$ 时，向
$$
T(x+y)(1-T(x)T(y)) = T(x)+T(y)
$$
中带入 $x = 0$，得 $T(x)$ 满足 $X(1-\mathrm iX) = \mathrm i + X$（即 $\mathrm iX^2 = -\mathrm i$），即 $X = \pm \mathrm i$。直接计算，可得 $S = \{m \mid T(m) = \mathrm i\}$ 和 $T = \{m \mid T(m) = -\mathrm i\}$ 均为对加法封闭的集合。注意到其中必然有一个集合包含 $0$，一个集合包含 $1$，因此：

* $0 \in S, 1 \in S$：$S = \mathbb N, T = \varnothing$。
* $0 \in T, 1 \in S$：$S = \mathbb N_{> 0}, T = \{0\}$。
* $0 \in S, 1 \in T$：$S = \{0\}, T = \mathbb N_{> 0}$。
* $0 \in T, 1 \in T$：$S = \varnothing, T = \mathbb N$。

当 $T(0) = 0$ 时，观察到当且仅当 $T(1) = \pm \mathrm i$ 时有 $T(n) = T(1)$ 的强周期性质，所以我们尝试对其讨论，当 $T(1) = \pm \mathrm i$ 时，可以验证 $T(k) = \begin{cases} 0 & k = 0, \\ T(1) & k > 0 \end{cases}$ 满足正切和角公式，当 $T(1) \ne \pm \mathrm i$ 时，取 $R = \dfrac{1 + \mathrm i T(1)}{1 - \mathrm i T(1)}$，则 $T(1) = \mathrm i \cdot \dfrac{1-R}{1+R}$。这样，我们有
$$
\begin{aligned}
T(2) &= \dfrac{2\mathrm i(1-R)/(1+R)}{1 - (\mathrm i^2) (1-R)^2/(1+R)^2} \\
&= \dfrac{2 \mathrm i (1 - R) (1 + R)}{(2 + 2R^2) / (1 + R^2)} \\
&= \mathrm i \cdot \dfrac{1-R^2}{1+R^2},
\end{aligned}
$$
类似地，$T(n) = \mathrm i \cdot \dfrac{1 - R^n}{1 + R^n}$。当然，由于 $R$ 是唯一确定的，不走运地 $R^n = -1$ 了也只能宣告不存在 $T(n)$。

## 5 惯性
考虑有限域 $\mathbb F_{p^2} = \mathbb F_p[X]/(X^2-1) = \mathbb F_p[\mathrm i]$。重复对「分裂」部分最后一步的论证可知一定是满足 $T(n) = \mathrm i \cdot \dfrac{1 - R^n}{1 + R^n}$（$R \in \mathbb F_p[\mathrm i]$）。现在尝试说明在什么时候 $\mathrm i \cdot \dfrac{1 - R^n}{1 + R^n} \in \mathbb F_p$。

由于 $T(n+1) = \dfrac{T(1) + T(n)}{1 - T(1) T(n)}$，所以 $T(n) \in \mathbb F_p \implies T(n + 1) \in \mathbb F_p\ (n > 0)$。这样，我们只需要确保 $T(1) \in \mathbb F_p$ 即可。于是我们有一个神奇的结论
$$
\mathrm i \cdot \dfrac{1-R}{1+R} \in \mathbb F_p \iff R^{p + 1} = 1.
$$
（不得不说，这个结论是 unmotivated 的，不是为了这个结论我不会看题解）

*证明.*
$$
\begin{aligned}
R^{p + 1} &= \left(\dfrac{1 + \mathrm i x}{1 - \mathrm ix}\right)^{p + 1} & (x = T(1)) \\
&= \left(\dfrac{1 + \mathrm i x}{1 - \mathrm ix}\right) \cdot \left(\dfrac{1 + (\mathrm i x)^p}{1 - (\mathrm ix)^p}\right) \\
&= \left(\dfrac{1 + \mathrm ix}{1 - \mathrm ix}\right) \left(\dfrac{1 - \mathrm ix^p}{1 + \mathrm ix^p}\right),
\end{aligned}
$$
它是 $1$ 当且仅当 $x^p = x \iff x \in \mathbb F_p$。得证。

## 5 算法
对于分歧 $p = 2$ 情形，答案必然为 $\mathtt{Yes}$。

对于分裂 $p \equiv 1 \pmod 4$ 情形，首先特判掉目标在 $\{\pm \mathrm i\}$ 内的 $\mathrm O(1)$ 个情形，然后剩余的情形是 $T(n) = \mathrm i \cdot \dfrac{1 - R^n}{1 + R^n}$ 的情形，这样我们所要的限制就是：

> $R$ 的阶是奇数、整除某个数 $N$（要求 $N \mid |F^\times|$）、$R^m = k$。

前两条显然可以被 $R$ 的阶整除 $N' = \dfrac{N}{2^{\nu_2(N)}}$ 取代。观察 $\langle k \rangle$ 可知其大小为 $\dfrac{|R|}{(m, |R|)}$。观察到对于 $a, m, r, 0 \le r \le a$，一定有 $a + \min(m, r) - r + \min(m, a)$（直接分类讨论），有 $\dfrac{N'/(m, N')}{|R|/(m, |R|)}$ 是整数。兹有

**判据：** 存在满足条件的 $R$ 当且仅当 $k^{N'/(m, N')} = 1$。

*证明.* 

* （$\implies$ 方向） 由上知 $k^{|R|/(m, |R|)} = 1$，推出 $k^{N'/(m, N')} = 1$。
* （$\impliedby$ 方向） 考虑 $F^\times$ 中惟一一个 $N'$ 阶循环群，其生成元记作 $\lambda$，则 $k = \lambda^x$，$\lambda^{xN'/(m,N')} = 1$，$N' \mid (x N' / (m, N'))$，即 $(m, N') \mid x$，即 $ym \equiv x \pmod {N'}$ 有解，$R = \lambda^y$ 即为所求。

分裂情形有 $N = p - 1$，惯性情形有 $N = p + 1$。因此，我们完成了本题。

## 6 代码

由于 $T(n) = \mathrm i \cdot \dfrac{1 - R^n}{1 + R^n}$ 中 $T(k) = 0 \iff N \mid k$，所以我们维护 $(T(a), T(b)) \mapsto T(a+b)$ 这个「乘法」运算的快速幂是更容易的实现。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

template <typename T>
T qpow(T a, int b, function<T(T, T)> op, T initial = 1) {
    T res = initial;
    while (b) {
        if (b & 1) res = op(res, a);
        a = op(a, a), b >>= 1;
    }
    return res;
}

optional<int> inv(int a, int p) {
    if (a == 0) return nullopt;
    return qpow<int>(a, p - 2, [&](int a, int b) { return a * b % p; });
}

optional<int> tan_mult(optional<int> a, optional<int> b, int p) {
    if (!a || !b) return nullopt;
    optional<int> u = inv((1 - a.value() * b.value() % p + p) % p, p);
    if (!u) return nullopt;
    return (a.value() + b.value()) * u.value() % p;
}

void solve() {
    int p, N, a, b;
    cin >> p >> a >> b;
    if (p == 2) return cout << "Yes" << endl, void();
    if (b == 0 || b * b % p == p - 1) return cout << "Yes" << endl, void();
    N = p % 4 == 1 ? p - 1 : p + 1;
    while (N % 2 == 0) N /= 2;
    N /= gcd(N, a);
    cout << (qpow<optional<int>>(
                 b, N,
                 [&](optional<int> a, optional<int> b) {
                     return tan_mult(a, b, p);
                 },
                 0) == 0
                 ? "Yes"
                 : "No")
         << endl;
}

signed main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：Eznibuil (赞：1)

神奇数论题，毒瘤大分讨。

注意到题目中的第二个条件去除取模后就是正切和角公式，这解释了题目名字的来源。

可惜了，总归不能把正切给取个模吧。把 $\tan x$ 在 $x=0$ 处展开倒是可以得到一个叫做正切数的序列，不过也不能对这个无限长的序列来个取模吧。

不妨运用一下欧拉公式 $\exp(ix)=\cos x+i\sin x$，可以得到 $\sin x=\frac1{2i}(\exp(ix)-\exp(-ix)),\cos x=\frac12(\exp(ix)+\exp(-ix))$。简单做一个除法：
$$\tan x=i\cdot\frac{1-\exp(2ix)}{1+\exp(2ix)}$$

现在猜想题目中的 $t(x)$ 对于两个数（可能是虚数）$I,r$ 同样满足：（其中 $I^2\equiv-1\pmod p$）
$$t(x)\equiv I\cdot\frac{1-r^x}{1+r^x}\pmod p$$

尝试证明一下以上公式，带入题目的条件：
$$
\begin{aligned}
t(x+y)(1-t(x)t(y))&\equiv I\cdot\frac{1-r^{x+y}}{1+r^{x+y}}\cdot\left(1-\left(I\cdot\frac{1-r^x}{1+r^x}\right)\left(I\cdot\frac{1-r^y}{1+r^y}\right)\right)\\
&\equiv I\cdot\frac{1-r^{x+y}}{1+r^{x+y}}\cdot\left(1+\frac{1-r^x}{1+r^x}\cdot\frac{1-r^y}{1+r^y}\right)\\
&\equiv I\cdot\frac{1-r^{x+y}}{1+r^{x+y}}\cdot\left(1+\frac{1-r^x-r^y+r^{x+y}}{1+r^x+r^y+r^{x+y}}\right)\\
&\equiv I\cdot\frac{1-r^{x+y}}{1+r^{x+y}}\cdot\frac{2+2r^{x+y}}{1+r^x+r^y+r^{x+y}}\\
&\equiv I\cdot\frac{2-2r^{x+y}}{1+r^x+r^y+r^{x+y}}\\
&\equiv I\cdot\frac{(1-r^x)(1+r^y)+(1+r^x)(1-r^y)}{(1+r^x)(1+r^y)}\\
&\equiv I\cdot\frac{1-r^x}{1+r^x}+I\cdot\frac{1-r^y}{1+r^y}\\
&\equiv t(x)+t(y)\pmod p
\end{aligned}
$$

注意上面推导利用了一次 $I^2\equiv-1\pmod p$ 才得到猜想成立，这使得很容易确定 $I$ 的值：如果 $-1$ 是 $p$ 的二次剩余那 $I$ 存在，否则 $I$ 是不存在。

若 $b=0$ 显然为 `Yes`（只需要 $t$ 全 $0$）。现在假设 $b\ne0$。

$p=2$ 的情况很特别，二次剩余和二次非剩余并不对称，单独考虑。容易发现要么 $t$ 是全 $0$，要么全 $1$，所以答案一定是 `Yes`。

将 $x=y=0$ 带入条件二，有 $t(0)(1-t^2(0))=2t(0)$，所以一定有 $t(0)\in\{0,I,-I\}$。

现在是 $p\bmod4=1$ 的情况，这种情况 $I$ 存在。分类讨论：
1. $t(1)\in\{I,-I\}$：容易发现 $\forall i\ge1:t(i)=t(1)$。
1. $t(1)\notin\{I,-I\}$：容易发现 $t(0)=0$，满足条件的 $t$ 必定可以表示为 $t(x)=I\cdot\frac{1-r^x}{1+r^x}$ 且分母永远不是 $0$，胡乱开根即可。

然后是 $p\bmod4=3$ 的情况，这种情况 $I$ 不存在，利用高斯整环的思想给它一个扩域，令 $I$ 为虚数单位且 $I^2\equiv-1\pmod p$。这时候必然有 $t(0)=0$，$r$ 为虚数。

可以发现扩域以后就可以照搬 $p\bmod4=1$ 的第二种情况（因为第一种不可能）。现在需要找到满足条件的 $r$ 使得所有 $t(x)=I\cdot\frac{1-r^x}{1+r^x}$ 都是实数且分母永远不是 $0$。

根据 $(a+b)^p\equiv a^p+b^p\pmod p$ 可以得到 $z$ 是实数的条件相当于 $z^p\equiv z\pmod p$，于是尝试带入 $t(x)$：（注意，$I^p\equiv-I\pmod p$）
$$
\begin{aligned}
I\cdot\frac{1-r^x}{1+r^x}&\equiv\left(I\cdot\frac{1-r^x}{1+r^x}\right)^p\pmod p\\
\frac{1-r^x}{1+r^x}+\left(\frac{1-r^x}{1+r^x}\right)^p&\equiv0\pmod p\\
\frac{1-r^x}{1+r^x}+\frac{1-r^{px}}{1+r^{px}}&\equiv0\pmod p\\
\frac{1-r^{(p+1)x}}{1+r^x+r^{px}+r^{(p+1)x}}&\equiv0\pmod p\\
1-r^{(p+1)x}&\equiv0\pmod p\\
r^{p+1}&\equiv1\pmod p
\end{aligned}
$$

问题转化为求满足条件的虚数 $r$ 有 $r^{p+1}\equiv1\pmod p$ 且 $I\cdot\frac{1-r^a}{1+r^a}\equiv b\pmod p$ 且 $r$ 任意幂次不能同余于 $-1$。

由于 $1$ 的模 $p$ 意义下根号只有 $1$ 和 $p-1$，因此必然也有 $r^\frac{p+1}2\equiv1\pmod p$，依此类推，可以将 $p+1$ 中的 $2$ 全部去除得到 $q$，有 $r^q\equiv1\pmod p$。

到了这一步容易卡死，所以官方题解给了一个妙妙结论：扩域后仍然有原根，其所有幂能得到除了 $0$ 外的所有元素。然后就能胡乱开根了。（惭愧了，居然不知道这个结论。）

现在需要证明上述结论为真。这很简单，把质数原根存在的证明搬过来即可。

注意到高斯整环上抛开单位元 $i$ 的影响是有唯一分解的，而 $\bmod4=3$ 形的质数 $p$ 在高斯整环上仍然是不可分解的，所以所有的在整数的操作搬过来基本上都成立。

现在可以得到高次剩余的结论：$x^k\equiv1\pmod p$ 至多有 $k$ 个解。

考虑任意 $d\mid(p^2-1)$，如果存在 $x$ 满足其阶为 $d$，根据刚刚的结论，阶为 $d$ 不会是 $x^0,\dots,x^{d-1}$ 之外的数，因此阶为 $d$ 的数要么没有要么有 $\varphi(d)$ 个。

显然把所有的阶的加起来总和应该是 $p^2-1$，所以必然每个都有 $\varphi(d)$ 个，因此必然有原根，且有 $\varphi(p^2-1)$ 个。证毕。

真是神仙题。

---

