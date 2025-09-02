# [HBCPC2024] Points on the Number Axis A

## 题目描述

Alice 正在数轴上玩一个单人游戏。

数轴上有 $n$ 个点。每次，玩家选择两个点。这两个点将被移除，并添加它们的中点。当数轴上只剩下一个点时，游戏结束。形式上，如果选择的两个点是 $x_i$ 和 $x_j$，那么在操作后将添加 $\dfrac{x_i+x_j}{2}$。

为了愉快地进行这个游戏，Alice 总是随机选择两个点。

现在 Alice 有一个问题：最后一个点的期望位置在哪里。

可以证明，答案可以表示成 $\dfrac{p}{q}$ 的形式，你只需要输出 $p\cdot q^{-1} \bmod 998\,244\,353$ 的值。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3
1 2 4```

### 输出

```
332748120
```

# 题解

## 作者：lzyqwq (赞：60)

小 L 是一个机器人，负责协助老 L 的研究工作。

老 L 在生命的最后时刻在研究一种奇怪的生物 L。这种生物的遗传遵循融合遗传规律。老 L 在一定的空间里让它们自由交配。

> 已知一共有 $n$ 个 L 个体，第 $i$ 个 L 个体有一个能力值 $a_i$。这些 L 个体会进行 $n-1$ 轮交配。每次交配会 **等概率随机** 选出当前存在的两个 L 个体 $x,y$，然后它们会繁衍出一个子代，能力值为 $\dfrac{a_x+a_y}{2}$，最后 $x,y$ 两个个体会死亡。子代可以继续参与后续的交配。显然最后只会剩下一个 L 个体，求它的 **期望** 能力值 $E(a)$。

老 L 已经进行了多次交配实验，但是仍然无法得到理想的结果。他需要小 L 进行更精密地计算。

小 L 选取了 $3$ 个 L 个体，能力值分别为 $a=(1,2,4)$，然后开始了演算。

如果第 $1$ 轮交配选取 $1,2$ 两个 L 个体，则会得到能力值为 $\dfrac{3}{2}$ 的子代；第 $2$ 轮由剩余的两个个体交配，会得到能力值为 $\dfrac{11}{4}$ 的子代。得到这种结果的概率为 $\dfrac{1}{3}$。

同理，剩余两种选取方式得到的最终 L 个体能力值分别为 $\dfrac{9}{4}$ 和 $2$，得到它们的概率均为 $\dfrac{1}{3}$。

最后的 L 个体期望能力值为 $E=\dfrac{9}{4}\times \dfrac{1}{3}+\dfrac{11}{4}\times \dfrac{1}{3}+2\times \dfrac{1}{3}=\dfrac{7}{3}$。

小 L 猛然发现 $E(a)$ 恰好为 $1,2,4$ 的平均数，它不敢相信这个绝望的结果。

小 L 用数学归纳法进行了更严谨的证明。

> $\bf{Blending\space\space Inheritance\space\space Theory}$
>
> 若 $n$ 个 L 个体的能力值分别为 $(a_1,\dots,a_n)$，则 $E(a)=\dfrac{\sum_{i=1}^n a_i}{n}$。
> 
> $\bf{Proof}$
> 
> - 当 $n=2$ 时，显然成立。
> - 若当 $n=m$ 时成立，则当 $n=m+1$ 时，考虑第一轮交配选取了 $i,j\,(i<j)$ 两个 L 个体，记 $b(i,j)$ 表示 $a$ 序列删除 $a_i,a_j$ 两个元素并插入 $\dfrac{a_i+a_j}{2}$ 这个元素后得到的新序列，即选取 $i,j$ 作为第一轮交配的个体交配后得到的序列。有：
>
>   $$\begin{aligned}E(a)&=\sum\limits_{i=1}^{m}\sum\limits_{j=i+1}^{m+1}\dfrac{2E(b(i,j))}{m(m+1)}\\&=\dfrac{2}{m(m+1)}\sum\limits_{i=1}^m\sum\limits_{j=i+1}^{m+1}\dfrac{\sum_{k=1}^mb(i,j)_k}{m}\\&=\dfrac{2}{m(m+1)}\sum\limits_{i=1}^m\sum\limits_{j=i+1}^{m+1}\dfrac{\left(\sum_{k=1}^{m+1}a_k\right)-\frac{a_i+a_j}{2}}{m}\\&=\dfrac{2}{m^2(m+1)}\sum\limits_{i=1}^m\sum\limits_{j=i+1}^{m+1}\sum\limits_{k=1}^{m+1}a_k-\dfrac{1}{m^2(m+1)}\sum\limits_{i=1}^m\sum\limits_{j=i+1}^{m+1}(a_i+a_j)\\&=\dfrac{2}{m^2(m+1)}\times \dfrac{m(m+1)}{2}\sum\limits_{i=1}^{m+1}a_i-\dfrac{1}{m^2(m+1)}\times m\sum\limits_{i=1}^{m+1}a_i\\&=\dfrac{\sum_{i=1}^{m+1}a_i}{m}-\dfrac{\sum_{i=1}^{m+1}a_i}{m(m+1)}\\&=\dfrac{\sum_{i=1}^{m+1}a_i}{m+1}\end{aligned}$$
>
> - $\mathcal{Q.E.D.}$

小 L 不可置信地看着看着这个无比正确的结论。难道繁衍的意义就是平均。平均。平均。然后死亡。死亡。死亡。然后一无所有。

老 L 看到这个结果，不知道脸上是欢喜还是悲伤，但是他完成了研究 L 生物的任务。然后，他不留遗憾地死了。

真的没留下遗憾吗？老 L 在临死前将自己的记忆芯片植入了小 L 的处理器。小 L 处理器中的数据流向它展示了老 L 的一生。

老 L 在小学的时候成绩还算不错。小升初的暑假他开始学习信息学竞赛。然而学着学着，老 L 的 OI 成绩却平庸。平庸。平庸。whk 成绩也平庸。平庸。平庸。在【】面前也平庸。平庸。平庸。

接着，老 L 的 OI 失败。失败。失败。whk 失败。失败。失败。和【】的距离拉远。拉远。拉远。

……

最后，老 L 除了小 L 和生物 L 之外，一无所有。

小 L 奔溃地大吼，它不敢相信毫无意义的平均。平均。平均。就是世界的意义。小 L 甚至开始嚎啕大哭。

但是小 L 是机器人，它不会哭。它理解不了哭的意义。

但是它会哭。因为哭毫无意义。

---

## 作者：hhoppitree (赞：5)

提供一个较为简洁的证明：对称性，证毕。

说详细点就是由于每个点没有区别，所以对答案 $\sum a_ic_i$ 的贡献系数 $c_i$ 相等，又因为 $\sum c_i=1$，所以 $c_i=\dfrac{1}{n}$。

或者你把合并看成一棵二叉树嘛，然后考虑每种不同构的二叉树，它的每个 $\sum c_i$ 不是都是 $1$ 吗？所以 $n!$ 种填法的贡献总和为 $\dfrac{1}{n}$，那取个平均是不是还是 $\dfrac{1}{n}$ 喵？

哎呀反正你就感受那股劲喵。

---

## 作者：Hyvial (赞：5)

[**题目传送门**](https://www.luogu.com.cn/problem/P10867)
- - - 


# 题目翻译
[翻译](https://www.luogu.com.cn/article/zjtl3hd0)

# 样例分析
样例给出了一个共有 $3$ 项的数组 $\{1,2,4\}$，我们对这个样例进行模拟：

第一次，我们有 $3$ 种选择，分别是将 $1$ 和 $2$，$1$ 和 $4$，$2$ 和 $4$ 进行和并。

第一种合并之后产生 $1$ 个值为 $\frac{3}{2}$ 的数，接着将这个数和剩下的 $4$ 合并，产生 $\frac{11}{4}$ 的数，概率是 $\frac{1}{3}$。

第二、三种同理，产生的结果分别是 $\frac{9}{4}$、$2$，概率都是 $\frac{1}{3}$。

最后我们进行整理就可以得出 $E(a) = \frac{11}{4} \times \frac{1}{3} + \frac{9}{4} \times \frac{1}{3} + 2 \times \frac{1}{3} = \frac{7}{3}$。

$\frac{7}{3}$ 是什么呢？是所有数之和的平均数啊，于是，我提出了一个假设：
$$E(a)=\frac{\sum_{i=1}^{n}a_i}{n}$$

# 证明过程
~~接着就开始了最坐牢的阶段~~。我们就使用数学归纳大法进行证明，当 $n = 2$ 时显然是对的。

若 $n=m$ 时成立，则当 $n=m+1$ 时，由于第一轮将 $i$ 和 $j$ （$i<j$） 合并，记 $c(i,j)$ 表示将当前 $a$ 序列中的第 $i$ 项 和 第 $j$ 项 （$i<j$） 删除，添加一个为 $\frac{a_i+a_j}{2}$ 的数的操作。于是就有：

$$\begin{aligned}
E(a)&=\frac{2}{m(m+1)}\sum_{i=1}^{m}\sum_{j=i+1}^{m+1}E(c(i,j))
\end{aligned}$$

由于 $E(c(i,j))$ 是符合假设的，而 $a$ 中数的和在进行一次c操作后会少 $a_i+a_j$，多 $\frac{a_i+a_j}{2}$，综合起来就是少 $\frac{a_i+a_j}{2}$，故：

$$\begin{aligned}
E(c(i,j))&=\frac{\sum_{k=1}^{m+1}a_k-\frac{a_i+a_j}{2}}{m}
\end{aligned}$$

所以：

$$\begin{aligned}
E(a)&=\frac{2}{m(m+1)}\sum_{i=1}^{m}\sum_{j=i+1}^{m+1}\frac{\sum_{k=1}^{m}a_k-\frac{a_i+a_j}{2}}{m}\\
&=\frac{2}{m^2(m+1)}\sum_{i=1}^{m}\sum_{j=i+1}^{m+1}\sum_{k=1}^{m+1}(a_k-\frac{a_i+a_j}{2})\\
&=\frac{2}{m^2(m+1)}\sum_{i=1}^{m}\sum_{j=i+1}^{m+1}\sum_{k=1}^{m+1}a_k-\frac{1}{m^2(m+1)}\sum_{i=1}^{m}\sum_{j=i+1}^{m+1}(a_i+a_j)
\end{aligned}$$

因为：

$\sum_{i=1}^{m}\sum_{j=i+1}^{m+1}1=\frac{m(m+1)}{2}$，与 $\frac{2}{m^2(m+1)}$ 抵消成 $\frac{1}{m}$。

而 $\sum_{i=1}^{m}\sum_{j=i+1}^{m+1}(a_i+a_j)=m \times \sum_{i=1}^{m+1}a_i$。


所以：

$$\begin{aligned}
E(a)&=\frac{1}{m}\sum_{k=1}^{m+1}a_k-\frac{1}{m^2(m+1)}*m*\sum_{i=1}^{m+1}a_i\\
&=\frac{1}{m}\sum_{k=1}^{m+1}a_k-\frac{1}{m(m+1)}\sum_{i=1}^{m+1}a_i\\
&=\frac{m+1}{m(m+1)}\sum_{i=1}^{m+1}a_i-\frac{1}{m(m+1)}\sum_{i=1}^{m+1}a_i\\
&=\frac{m}{m(m+1)}\sum_{i=1}^{m+1}a_i\\
&=\frac{\sum_{i=1}^{m+1}a_i}{m+1}
\end{aligned}$$

证毕！

# 代码实现
```
#include <bits/stdc++.h>
#define PII pair <int, int>
#define int long long
#define DB double

using namespace std;

const int N = 1e6 + 10, MOD = 998244353;
int n, x, sum;

int kuaisu(int x, int y)
{
	// 快速幂求逆元
	int ret = 1;
	while(y)
	{
		if(y & 1)
			ret = ret * x % MOD;
		x = x * x % MOD;
		y >>= 1;
	}
	return ret;
}

signed main()
{
	scanf("%lld", &n);
	
	for(int i = 1; i <= n; i ++ )
	{
		scanf("%lld", &x);
		sum = (x + sum) % MOD;
		// 输入并求和
	}
	
	printf("%lld\n", sum * kuaisu(n, MOD - 2) % MOD);
	// n的p-2次方（p为质数）在模p的意义下等同于n的-1次方，也就是n的逆元
	
	return 0;
}
```

---

## 作者：Cyx20110930 (赞：3)

# 简要题意

有一个序列 $a_1,a_2,...,a_n$，问若每次等概率选择 $2$ 个数 $a_i,a_j$，删去这 $2$ 个数，并插入 $\frac{a_i+a_j}2$，操作 $n-1$ 后剩下的那个数期望是？

# Sol

猜一手结论：平均数。

~~感性地理解一下~~说讲的很模糊？来理论地证一下！（证明在下面）

有理数的取模：$\frac pq \bmod 998244353$ 就是 $p$ 乘上 $q$ 对 $998244353$ 的逆元。

逆元：因为除法不满足 $(a\div b) \bmod p=(a \bmod p) \div (b \bmod p)$，所以要将除法转换为乘法。根据费马小定理有 $a^{p-1} \equiv 1  \bmod p$，所以 $a$ 在模 $p$ 意义下的逆元为 $a^{p-2}$。

# Proof

由 lzyqwq 大佬的思路启发，只是解释的啰嗦一点：

不妨设答案记作 $Sum(a,n)$。

若 $a$ 数组只有 $2$ 项，即 $n=2$，显然成立。

若 $a$ 数组有 $3$ 项 $a_1,a_2,a_3$，期望为 

$$
\begin{aligned}
Sum(a,3)
&=\frac 13 \times(\frac{\frac {a_1+a_2}2+a_3}2+ \frac{\frac {a_1+a_3}2+a_2}2+ \frac{\frac {a_2+a_3}2+a_1}2)\\
&=\frac 13 \times (a_1+a_2+a_3)
\end{aligned}
$$

就是平均数。

若 $a$ 数组有 $4$ 项 $a_1,a_2,a_3,a_4$，期望为 

$$
\begin{aligned}
Sum(a,4)
&=\frac 16\times (Sum(\Set {\frac {a_1+a_2}2,a_3,a_4},3)+Sum(\Set {\frac {a_1+a_3}2,a_2,a_4},3)+Sum(\Set {\frac {a_1+a_4}2,a_2,a_3},3)+Sum(\Set {\frac {a_2+a_3}2,a_1,a_4},3)+Sum(\Set {\frac {a_2+a_4}2,a_1,a_3},3)+Sum(\Set {\frac {a_3+a_4}2,a_1,a_2},3))\\
&=\frac {1}{18} \times (\frac 92 \times (a_1+a_2+a_3+a_4))\\
&=\frac 14 \times (a_1+a_2+a_3+a_4)
\end{aligned}
$$

也是平均数。

那么若 $a$ 数组有 $n$ 项，期望为 

$$
\begin{aligned}
Sum(a,n)
&=\frac 1{\frac {n\times (n-1)}2}\times (Sum(\Set {\frac {a_1+a_2}2,a_3,...},n-1)+Sum(\Set {\frac {a_1+a_3}2,a_2,...},n-1)+Sum(\Set {\frac {a_1+a_4}2,a_2,...},n-1)+...+Sum(\Set {\frac {a_{n-1}+a_n}2,a_1,...},n-1))\\
&=\frac {1}{\frac {n\times (n-1)^2}2} \times ((n-1 \times \frac12+(\frac {n\times (n-1)}2-(n-1)) \times 1 ) \times (a_1+a_2+a_3+a_4+...+a_n))\\
&=\frac {1}{\frac {n\times (n-1)^2}2} \times (\frac {(n-1)^2}2) \times (a_1+a_2+a_3+a_4+...+a_n))\\
&=\frac 1n \times (a_1+a_2+a_3+a_4+...+a_n)
\end{aligned}
$$

还是平均数。证毕！

# Code

因为跟 seanli1008 组队的，用他的账号交的代码，这个 Code 是我写的，没有作弊，特此声明。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
int qmi(int a,int b,int p){
	int res=1;
	while(b){
		if(b&1) res=res*a%p;
		b>>=1;
		a=a*a%p;
	}
	return res;
}
signed main(){
    int n;
    cin>>n;
    int x,ans=0;
    for(int i=1;i<=n;i++){
    	cin>>x;
    	ans+=x;
    }
    ans=ans%mod;
	ans=ans*qmi(n,mod-2,mod)%mod;
	cout<<ans;
}
```

---

## 作者：Vct14 (赞：3)

膜拜大佬 @[lzyqwq](https://www.luogu.com.cn/user/539211)。

[题面](https://www.luogu.com.cn/problem/P10867)。

题意：给定一个长度为 $n$ 的数列 $x$，每次操作随机删除两个整数 $x_i,x_j$，并添加一个整数 $\dfrac{x_i+x_j}{2}$。进行 $n-1$ 次操作，求最后一个数的期望值对 $998244353$ 取模的值。

---

先举几个例子。

- 如果只有一个数，那么期望值就是这个数。
- 如果有两个数，期望值是这两个数的平均数。
- 如果有三个数，以样例 `1 2 4` 为例，最后一个数有 $\dfrac{1}{3}$ 的概率为 $\dfrac{1+\frac{2+4}{2}}{2}=2$，$\dfrac{1}{3}$ 的概率为 $\dfrac{2+\frac{1+4}{2}}{2}=\dfrac{9}{4}$，$\dfrac{1}{3}$ 的概率为 $\dfrac{4+\frac{1+2}{2}}{2}=\dfrac{11}{4}$，期望值为 $2\times\dfrac{1}{3}+\dfrac{9}{4}\times\dfrac{1}{3}+\dfrac{11}{4}\times\dfrac{1}{3}=\dfrac{7}{3}$。

可以猜测期望值为这 $n$ 个数的平均数。

---



第一数学归纳法证明如下：

记 $E(x)$ 表示 $x$ 数列经操作后最后一个数的期望值，$f_x(i,j)$ 表示删除 $x_i,x_j$ 并添加 $\dfrac{x_i+x_j}{2}$ 后的数列。

$n=1$ 时，易证。（其实上面例子已经证了 $n=1,2,3$ 成立。）

如果 $n=m$（$m\geqslant1$）成立，即对于任意长度为 $m$ 的数列 $x$，$E(x)=\dfrac{\sum\limits_{i=1}^m x_i}{m}$，则 $n=m+1$ 时，即 $x$ 的长度为 $m+1$ 时：

因为一共有 $\dfrac{(m+1)^2-(m+1)}{2}=\dfrac{m(m+1)}{2}$ 种不同的无序对 $(i,j)$，所以每种情况的概率为 $\dfrac{1}{\frac{m(m+1)}{2}}=\dfrac{2}{m(m+1)}$。

可以得到式子

$$E(x)=\sum\limits_{i=1}^m \sum\limits_{j=i+1}^{m+1}\dfrac{2}{m(m+1)}\times E(f_x(i,j))$$

由乘法分配律可得

$$E(x)=\dfrac{2}{m(m+1)}\sum\limits_{i=1}^m \sum\limits_{j=i+1}^{m+1}E(f_x(i,j))$$

易知 $f_x(i,j)$ 的长度为 $m$，所以 $E(f_x(i,j))=\dfrac{\sum\limits_{k=1}^{m+1} x_k-x_i-x_j+\frac{x_i+x_j}{2}}{m}=\dfrac{\sum\limits_{k=1}^{m+1} x_k-\frac{x_i+x_j}{2}}{m}$。这里很好理解，$f_x(i,j)$ 的每一项之和相当于 $x$ 中每一项之和减去 $x_i,x_j$ 再加上 $\dfrac{x_i+x_j}{2}$ 的结果。

带进去可得

$$E(x)=\dfrac{2}{m(m+1)}\sum\limits_{i=1}^m \sum\limits_{j=i+1}^{m+1}\dfrac{\sum\limits_{k=1}^{m+1} x_k-\frac{x_i+x_j}{2}}{m}$$

把 $m$ 提出来得到

$$E(x)=\dfrac{2}{m^2(m+1)}\sum\limits_{i=1}^m \sum\limits_{j=i+1}^{m+1}(\sum\limits_{k=1}^{m+1} x_k-\frac{x_i+x_j}{2})$$

括号拆开，得（这里顺便把后面的 $\dfrac{1}{2}$ 提出来了。）

$$E(x)=\dfrac{2}{m^2(m+1)}\sum\limits_{i=1}^m \sum\limits_{j=i+1}^{m+1}\sum\limits_{k=1}^{m+1} x_k-\dfrac{1}{m^2(m+1)}\sum\limits_{i=1}^m \sum\limits_{j=i+1}^{m+1}(x_i+x_j)$$

上文提到，共有 $\dfrac{m(m+1)}{2}$ 种不同的 $(i,j)$。所以 $\sum\limits_{i=1}^m \sum\limits_{j=i+1}^{m+1}\sum\limits_{k=1}^{m+1} x_k$ 相当于加 $\dfrac{m(m+1)}{2}$ 次 $\sum\limits_{k=1}^{m+1} x_k$；$\sum\limits_{i=1}^m \sum\limits_{j=i+1}^{m+1}(x_i+x_j)$ 相当于累加每一组里的 $x_i$ 和 $x_j$，我们不妨换一个角度，每一个 $x_i$ 都存在于 $m$ 组中，即和其他所有 $x_j$（$i\neq j$）组合，因此 $\sum\limits_{i=1}^m \sum\limits_{j=i+1}^{m+1}(x_i+x_j)=m\sum\limits_{i=1}^{m+1}x_i$。

因此可以带入得到

$$E(x)=\dfrac{2}{m^2(m+1)}\times\dfrac{m(m+1)}{2}\sum\limits_{k=1}^{m+1} x_k-\frac{1}{m^2(m+1)}\times m\sum\limits_{i=1}^{m+1}x_i$$

也就是

$$E(x)=\dfrac{\sum\limits_{k=1}^{m+1} x_k}{m}-\dfrac{\sum\limits_{i=1}^{m+1}x_i}{m(m+1)}$$

换个形式，再通分一下可得

$$E(x)=\dfrac{(m+1)\sum\limits_{i=1}^{m+1} x_i-\sum\limits_{i=1}^{m+1}x_i}{m(m+1)}=\dfrac{m\sum\limits_{i=1}^{m+1} x_i}{m(m+1)}=\dfrac{\sum\limits_{i=1}^{m+1} x_i}{m+1}$$

即证。

由以上可得对于所有正整数 $n$，命题：最后一个数的期望值为所有 $x_i$ 的平均数成立。

---

记 $998244353=m$。由费马小定理，$q^{m-1}\equiv 1\pmod m$。那么 $q^{m-2}\equiv q^{-1}\pmod m$（这也被称为 $q$ 在模 $m$ 意义下的[逆](https://www.luogu.com.cn/problem/P3811)）。因此只需求 $p\times q^{m-2}$ 模 $998244353$ 的值。用快速幂可以解决。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int mod=998244353;

int qmul(int a,int b){
	int ans=0,base=a;
	while(b){
		if(b&1) ans=(ans+base)%mod;
		base=(base+base)%mod;
		b>>=1;
	}
	return ans;
}

int qpow(int a,int b){
	int ans=1%mod,base=a;
	while(b){
		if(b&1) ans=qmul(ans,base);
		base=qmul(base,base);
		b>>=1; 
	}
	return ans;
}

signed main(){
	int n;cin>>n;
	int sum=0,a;
	for(int i=1; i<=n; i++){
		cin>>a;
		sum=(sum+a)%mod;
	}
	cout<<sum*qpow(n,mod-2)%mod;
	return 0;
}
```

---

## 作者：lzdll (赞：2)

如果只有三个点按照 $x_1$，$x_2$，$x_3$ 的顺序两两取中点，最终的贡献就是 $\frac{{\frac{x_1+x_2}{2}}+x_3}{2}$，把它化简一下，就是 $\frac{x_1}{4}+\frac{x_2}{4}+\frac{x_3}{2}$。然后我们考虑 $x_i$ 的贡献，只需要所有情况的系数加起来再除以 $n$ 就行了。

也就是 $\frac{1}{2^{i-1}}+\sum_{i=1}^{n-1}\frac{1}{2^i}$，化简一下得到 $x_i$。

所以答案就是 $\frac{\sum_{i=1}^{n}x_i}{n}$。

使用快速幂求 $n$ 的逆元。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n;
int x[1000005];
int Pow(int a,int b){
	int as=1,bs=a;
	while(b){
		if(b&1)as=as*bs%mod;
		bs=bs*bs%mod;
		b>>=1;
	}
	return as;
}
int ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>x[i];ans+=x[i];
	}
	ans%=mod;
	cout<<ans*Pow(n,mod-2)%mod;
	return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

有一个长度为 $n$ 的序列 $a$，你每次随机选择两个数 $a_i,a_j$，将其删掉后在序列末尾插入 $\frac{a_i+a_j}{2}$，然后你重复此流程直到只剩下一个数。求剩下的这个数的期望值，对 $998244353$ 取模。

$1\leq n\leq 10^6$

## 思路

容易猜到答案为 $\frac{1}{n}\sum_{k=1}^{n}a_k$，不过小松鼠想要需要证明这一点。

小松鼠先发现对于 $n=2$，这个结论是显然成立的。

然后小松鼠想到自己吃松果的过程，要吃到第 $n$ 个松果，必须吃到第 $n-1$ 个松果，证明一个命题也可以先假设 $n=k-1$ 成立，再证明 $n=k$ 的情况成立。小松鼠了解到这个方法叫做数学归纳法。

小松鼠为了偷懒，令此时序列的总和为 $S$。然后它写出了下面的式子，这就是期望：

$$
\frac{1}{\sum_{i=1}^{k}\sum_{j=i+1}^k 1}\sum_{i=1}^{k}\sum_{j=i+1}^k\frac{S-i-j+\frac{i+j}{2}}{k-1}
$$

小松鼠决定先计算最左边分式下面的部分：

$$
\begin{aligned}
&\sum_{i=1}^{k}\sum_{j=i+1}^k 1\\
&=\sum_{i=1}^{k}k-i\\
&=\sum_{i=0}^{k-1}i\\
&=\frac{1}{2}k(k-1)
\end{aligned}
$$

于是它将其代入了原式：

$$
\begin{aligned}
&\frac{1}{\sum_{i=1}^{k}\sum_{j=i+1}^k 1}\sum_{i=1}^{k}\sum_{j=i+1}^k\frac{S-a_i-a_j+\frac{a_i+a_j}{2}}{k-1}\\
&=\frac{2}{k(k-1)}\sum_{i=1}^{k}\sum_{j=i+1}^k\frac{S-a_i-a_j+\frac{a_i+a_j}{2}}{k-1}\\
&=\frac{2}{(k-1)^2k}\left(\frac{1}{2}k(k-1)S-\sum_{i=1}^{k}\sum_{j=i+1}^{k} \frac{a_i+a_j}{2}\right)\\
&=\frac{2}{(k-1)^2k}\left(\frac{1}{2}k(k-1)S-\frac{1}{2}\sum_{i=1}^{k}\sum_{j=i+1}^{k} a_i+a_j\right)\\
&=\frac{2}{(k-1)^2k}\left(\frac{1}{2}k(k-1)S-\frac{1}{4}\left(-2\sum_{i=1}^{k}a_i+\sum_{i=1}^{k}\sum_{j=1}^{k} a_i+a_j\right)\right)\\
&=\frac{2}{(k-1)^2k}\left(\frac{1}{2}k(k-1)S-\frac{1}{4}(-2S+\sum_{i=1}^{k}(ka_i+S))\right)\\
&=\frac{2}{(k-1)^2k}\left(\frac{1}{2}k(k-1)S-\frac{1}{4}(-2S+2kS)\right)\\
&=\frac{2}{(k-1)^2k}\left(\frac{1}{2}k(k-1)S-\frac{1}{2}(k-1)S\right)\\
&=\frac{S}{(k-1)^2k}\left(k(k-1)-(k-1)\right)\\
&=\frac{S}{(k-1)^2k}(k-1)^2\\
&=\frac{S}{k}
\end{aligned}
$$

证明完成，小松鼠高兴地去写代码去了，写完代码后提交，就通过了本题。

额外的思考：无论选择过程如何，无论当初怎样的自信的选择，最后只要一进行期望，都会归于平均，平均，平庸的无意义的平均才是世界的终极意义吗？

## 代码

啥，你看懂了上面的内容还需要代码？小松鼠才不肯放代码呢！

---

## 作者：yinpeichu2021 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P10867)

由样例容易发现答案为 $x$ 序列的平均数，所以直接乘法逆元即可。但是这也带给我们思考：为何有许多的操作可能，答案仍如此简洁呢？

证明：

首先，可以将最终得到点的坐标表示成 $X=\sum\limits_{i=1}^n c_ia_i$，其中 $a$ 为 $x$ 重排后得到的序列，从前往后依次对应操作时每次新选择的点，$c$ 为具体操作的系数。

容易通过数学归纳法证明系数之和 $\sum\limits_{i=1}^n c_i=1$。$n=1$ 时显然，$n>1$ 时，考虑将 $a$ 序列从中间某一断点断开，划分成大小分别为 $p,q$ 的连续非空的两部分 $y,z$，其系数序列分别为 $a_i,b_i$，假设之前的均成立，即 $\sum\limits_{i=1}^p a_i=1,\sum\limits_{i=1}^q b_i=1$，则 $\sum\limits_{i=1}^n c_i=\sum\limits_{i=1}^p\dfrac{a_i}2+\sum\limits_{i=1}^q\dfrac{b_i}2=\dfrac12+\dfrac12=1$，得证。

所以，对于某一种可能的系数序列 $c$，$X$ 值的期望为：

$$
\begin{split}
E(c)&=\dfrac1{n!}\sum\limits_{i=1}^n\sum\limits_{j=1}^n c_ix_j(n-1)!\\
&=\dfrac1{n!}(n-1)!\sum\limits_{j=1}^n\Big(x_j\sum\limits_{i=1}^n c_i\Big)\\
&=\dfrac1n\sum\limits_{i=1}^n x_i
\end{split}
$$

对于 $(n-1)!$ 的解释：某一个位置 $i$ 上 $a_i=x_j$，其他位置上可以任意重排，故满足 $a_i=x_j$ 的序列 $a$ 数量为 $(n-1)!$。

由于一种操作方式均可唯一对应某一个 $a$ 序列+某一个 $c$ 序列，一个 $a$ 序列+一个 $c$ 序列均可唯一对应某一种操作方式，所以我们可以将题中描述的“若干次随机选择两点删去并加入中点”的操作转化为“随机选取一个 $c$ 序列以及随机选取一个重排后的 $x$ 序列”。

由于每一种系数序列 $c$ 对应的重排后的序列 $a$ 的个数均为 $n!$，故而随机选取到某一个系数序列 $c$ 的概率均相等。令可能的系数序列 $c$ 的数量为 $S$，且 $s=\sum\limits_{i=1}^n x_i$，则期望为 $E=S\times\Big(\dfrac 1 S\times\dfrac s n\Big)=\dfrac s n=\dfrac1n\sum\limits_{i=1}^n x_i$。

~~终于证明完了！！！~~

代码就不给了，自行 bdfs 乘法逆元。

---

## 作者：linjunye (赞：1)

给一种不需要推太多式子的方法。

首先我们知道，期望值其实就是等于一个条件的值乘上它出现的概率的总和。比如我们设这个条件的权值为 $x$，出现概率为 $\frac{p}{q}$，则这个条件的期望为 $\frac{px}{q}$，总期望就是所有条件的期望和。

然后我们回归这道题。我们根据样例，列出一个条件的权值：$\frac{\frac{a_1+a_2}{2}+a_3}{2}$，其中 $a$ 数组就是选择的序列。

然后我们发现，$a$ 数组是 $x$ 重排后的序列！

这样的 $a$ 有多少种呢？答案为 $n!$ 个。

那么，一个条件发生的概率，就是从所有可能的 $a$ 种选一种，为 $\frac{1}{n!}$。

那么，就可以分析了。

首先，我们发现每一个条件发生概率相同，所以直接可以将所有期望相加。

这里的相加和之前不同，因为我们知道概率一样，那么根据乘法分配律，总期望就等于概率乘上权值和（不用算出每一个概率乘上权值再相加）。

接着只需算权值和即可。

我们先思考一个 $a_i$ 的总和（在这一层上）。

当 $a_i=x_i$ 时，固定 $x_i$，那么剩下可能的排列，就是剩下 $n-1$ 个数进行重排，总数为 $(n-1)!$，即当 $a_i=x_i$ 时，总和为 $(n-1)!x_i$。

那么 $a_i$ 的总和就为 $(n-1)!x_1+(n-1)!x_2+\cdots+(n-1)!x_n=(n-1)!\sum_{i=1}^{n}x_i$。

设 $\sum_{i=1}^{n}x_i=s$。

那么：

- 第一层总和为 $2(n-1)!s$。

- 往下，乘上 $\frac{1}{2}$，再加上第二层总和：$\frac{2(n-1)!s}{2}+(n-1)!s=(n-1)!s+(n-1)!s=2(n-1)!s$。

- 往下，乘上 $\frac{1}{2}$，再加上第三层总和：$\frac{2(n-1)!s}{2}+(n-1)!s=2(n-1)!s$。

- 一直往下，发现每次乘上 $\frac{1}{2}$ 后均为 $(n-1)!s$，再加上第 $i$ 层的总和 $(n-1)!s$，加上后又为 $2(n-1)!s$。

- 到达最后一层，权值为 $2(n-1)!s$。

- 别忘了最后还要乘上 $\frac{1}{2}$，最终权值为 $(n-1)!s$。

概率刚才也说明了，是 $\frac{1}{n!}$。刚才的式子：总期望就等于概率乘上权值和，也就是等于 $\frac{(n-1)!s}{n!}=\frac{1\times2\times\cdots\times (n-1)\times s}{1\times2\times\cdots\times (n-1)\times n}=\frac{s}{n}$，发现其实就是 $x$ 数组的平均数。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000010;
const int mod=998244353;
int n,a[N];
int ans;
int ksm(int a,int b){
	int z=1;
	while(b){
		if(b&1)z=z*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return z;
}
int inv(int x){
	return ksm(x,mod-2);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)ans+=a[i];
	ans=ans%mod*inv(n%mod)%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：__harry_potter__ (赞：0)

结果：**平均数**，即 $\frac{\sum_{i=1}^{n} a_i}{n}$ 。\
证明如下。\
利用第一数学归纳法。令长度为 $n$ 且此数组为 $a$ 时，结果为$F(n,a)$ \
 $n=1$ 时， $F(n,a)=\frac{\sum_{i=1}^{n} a_i}{n}$ 。

否则，若 $F(n-1,a)=\frac{\sum_{i=1}^{n-1} a_i}{n-1}$ ，则

令 $p=\sum_{i=1}^n a_i，$ 则   $F(n,a)=\sum_{i=1}^{n} \frac{F(n-1,a-a_i)+a_i}{2}$ \
$\sum_{i=1}^{n} \frac{\frac{p-a_i}{n-1}+a_i}{2}\div n$\
$\sum_{i=1}^{n} \frac{p+a_i\times(n-2)}{2\times n-2}\div n$\
$=\frac{(2\times n-2)\times p}{(2\times n-2)\times n}\div n$\
$=\frac{p}{n}$\
$=\frac{\sum_{i=1}^{n} a_i}{n}$

---

