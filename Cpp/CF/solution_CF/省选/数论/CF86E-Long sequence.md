# Long sequence

## 题目描述

一个序列 $a_0, a_1, \ldots$ 被称为循环二进制序列，当且仅当每项 $a_i$（$i = 0, 1, \ldots$）都是 0 或 1，并且存在系数 $c_1, c_2, \ldots, c_k$，使得对所有的 $n \ge k$，都有

$$ a_n = c_1 \times a_{n-1} + c_2 \times a_{n-2} + \cdots + c_k \times a_{n-k} \ (\text{mod}\ 2) $$

成立。假设这些系数 $c_i$ 中至少有一个不为零。这样的序列可以通过任意一个 $k$ 元组 $\{a_s, a_{s+1}, \ldots, a_{s+k-1}\}$ 唯一决定，因此它是有周期性的。此外，如果一个 $k$ 元组全是零，则整个序列也全为零，这种情形没有任何研究价值。否则，序列的最小周期不超过 $2^k - 1$，因为每个 $k$ 元组决定下一个元素，而非零 $k$ 元组的个数为 $2^k - 1$。我们将一个周期恰好为 $2^k - 1$ 的序列称为长周期序列。你的任务是，给定 $k$ 后，找出一个长周期序列（如果存在）。

## 说明/提示

1. 在第一个示例中：$c_1 = 1$，$c_2 = 1$，所以 $a_n = a_{n-1} + a_{n-2} \ (\text{mod}\ 2)$。因此序列为：

   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF86E/912635ecee4595ec8a08c4fc9af41871119bb40b.png)

   其周期为 $3 = 2^2 - 1$。

2. 在第二个示例中：$c_1 = 0$，$c_2 = 1$，$c_3 = 1$，所以 $a_n = a_{n-2} + a_{n-3} \ (\text{mod}\ 2)$。因此序列为：

   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF86E/2fea09c3d1bbe470004e6ccd52eac13ebf7eeb8e.png)

   其周期为 $7 = 2^3 - 1$。

示例中的周期部分已用颜色标出。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
```

### 输出

```
1 1
1 0
```

## 样例 #2

### 输入

```
3
```

### 输出

```
0 1 1
1 1 1
```

# 题解

## 作者：MatrixGroup (赞：1)

## 题意

给定一个正整数 $n$，请求出序列 $c_1,\cdots,c_n$ 和 $a_1,\cdots,a_n$，使得 $v_i=\begin{cases}a_i&i\le n\\\left(\sum\limits_{j=1}^nc_jv_{i-j}\right)\bmod 2&\text{otherwise}\end{cases}$ 的最小正周期为 $2^n-1$。

$n\le 50$。

## 题解

显然与 $a$ 无关，因为最终长度为 $n$ 的子序列都会出现。考虑随机生成 $c$，检验 $v$。

怎么检验 $v$ 的最小正周期为 $2^n-1$？判断 $2^n-1$ 是周期且 $\forall p|(2^n-1)$ 且 $p$ 是素数 $\dfrac{2^n-1}{p}$ 不是正周期即可。

怎么检验 $m$ 是否是周期？写出转移矩阵 $B$ 使得 $\forall a,B\begin{pmatrix}
a_1\\
a_2\\
\vdots \\
a_n
\end{pmatrix}\equiv \begin{pmatrix}
a_2\\
a_3\\
\vdots \\
a_{n+1}
\end{pmatrix}\pmod{2}$，则 $\forall a,B^m a\equiv a\pmod 2$（即 $B^m\equiv I_n\pmod 2$） 当且仅当  $m$ 是周期（这是显然的）。因此随机化检验即可。

还可以做得更好吗？令 $P(x)=x^n+\sum\limits_{i=0}^{n-1}c_{n-i}x^i$（因为 $\bmod 2$ 所以符号无关），则 $a_m=\sum_{i=0}^{n-1}a_{i+1}[x^i](x^{m-1}\bmod{P(x)})$。读者自证不难。

因此，判断变成了判断 $x^m\bmod{P(x)}\equiv1\pmod 2$，可以用位运算实现。

如何证明复杂度？显然，我们要找的就是 $GF(2)$ 上度数为 $n$ 的 [本原多项式](https://mathworld.wolfram.com/PrimitivePolynomial.html)，有 $\dfrac{\varphi(2^n-1)}{n}$ 个，$n\le 50$ 时概率最小值在 $n=48$ 时取到，为 $\dfrac{8505}{2^{20}}$，期望随机 $\dfrac{2^{20}}{8505}\approx123.3$ 次就可以随机到，判断的复杂度是 $O(2^\frac{n}{2}+\dfrac{n^42^n\omega(2^n-1)}{\varphi(2^n-1)w})$，其中 $\omega(N)$ 表示 $N$ 的不同素因子个数，$w=64$ 为字长。如果你的常数很大过不去可以考虑打表。

P.S 你可以这样生成 $GF(2^n)$（甚至可能生成 $GF(p^q)$），这样大概（我没试）就可以做 [P3923 大学数学题](https://www.luogu.com.cn/problem/P3923) 了。

## 代码

主要部分：

```cpp
mt19937_64 myrand(time_related_rand());
int n;
ll max_per;
vector<ll> prdv;
void get_pr(ll val)
{
	prdv.clear();
	for(int i=2;i<=val/i;++i)
	{
		if(val%i==0) prdv.pb(max_per/i);
		while(val%i==0)val/=i;
	}
	if(val>1) prdv.pb(max_per/val);
}
ll mul(__int128 u,__int128 v,__int128 mod)
{
	__int128 r=0;
	rep(i,n) if((v>>i)&1) r^=u<<i;
	per(i,n) if((r>>(i+n))&1) r^=mod<<i;
	return r;
}
ll qkpw(ll u,ll k,ll mod)
{
	ll r=1;
	while(k)
	{
		if(k&1)r=mul(r,u,mod);
		u=mul(u,u,mod);
		k>>=1;
	}
	return r;
}
bool isvalid(ll x)
{
	if(qkpw(2,max_per,x)!=1) return 0;
	rep(i,prdv.size())
	{
		ll cur=prdv[i];
		if(qkpw(2,cur,x)==1) return 0;
	}
	return 1;
}
void find_prime()
{
	max_per=(1ll<<n)-1;
	get_pr(max_per);
	ll v=((myrand())&((1ll<<n)-1))|(1ll<<n)|1;
	while(!isvalid(v))
	{
		v=((myrand())&((1ll<<n)-1))|(1ll<<n)|1;
	}
	per(i,n) cout<<((v>>i)&1)<<" ";cout<<endl;
	per(i,n) cout<<"1 ";
}
```

---

