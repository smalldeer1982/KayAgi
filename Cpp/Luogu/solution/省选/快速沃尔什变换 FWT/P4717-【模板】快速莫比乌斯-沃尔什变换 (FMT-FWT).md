# 【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)

## 题目描述

给定长度为 $2^n$ 两个序列 $A,B$，设 

$$C_i=\sum_{j\oplus k = i}A_j \times B_k$$

分别当 $\oplus$ 是 or, and, xor 时求出 $C$。

## 说明/提示

$1 \le n \le 17$。

## 样例 #1

### 输入

```
2
2 4 6 8
1 3 5 7
```

### 输出

```
2 22 46 250
88 64 112 56
100 92 68 60
```

# 题解

## 作者：xht (赞：278)

# 请在博客中查看

## 核心思想

记对序列 $a$ 进行快速沃尔什变换后的序列为 $fwt[a]$。

已知序列 $a,b$，求一个新序列 $c = a \cdot b$，直接计算是 $\mathcal O(n^2)$ 的。

若 $a \to fwt[a]$ 和 $b \to fwt[b]$ 是 $\mathcal O(n \log n)$ 的，而 $fwt[c] = fwt[a] \cdot fwt[b]$ 是 $\mathcal O(n)$ 的，同时 $fwt[c] \to c$ 也是 $\mathcal O(n \log n)$ 的。

那么我们可以利用上述过程 $\mathcal O(n \log n)$ 求出 $c$。

## OI 中的运用

在 OI 中，FWT 是用于解决对下标进行位运算卷积问题的方法。
$$
c_{i}=\sum_{i=j \oplus k} a_{j} b_{k}
$$
其中 $\oplus$ 是二元位运算中的一种。

### 或

要求

$$
c_{i}=\sum_{i=j | k} a_{j} b_{k}
$$

显然有 $j|i = i, k|i=i \to (j|k)|i = i$。

构造 $fwt[a]_i = \sum_{j|i=i} a_j$。

则有

$$
\begin{aligned}
fwt[a] \times fwt[b] &= \left(\sum_{j|i=i} a_j\right)\left(\sum_{k|i=i} b_k\right) \\\\
&= \sum_{j|i=i} \sum_{k|i=i} a_jb_k \\\\
&= \sum_{(j|k)|i = i} a_jb_k \\\\
&= fwt[c]
\end{aligned}
$$

#### $a \to fwt[a]$

要求
$$
fwt[a]_i = \sum_{j|i=i} a_j
$$
令 $a_0$ 表示 $a$ 中下标最高位为 $0$ 的那部分序列，$a_1$ 表示 $a$ 中下标最高位为 $1$ 的那部分序列。

则有
$$
fwt[a] = \text{merge}(fwt[a_0], fwt[a_0] + fwt[a_1])
$$
其中 $\text{merge}$ 表示「拼接」，$+$ 表示对应位置相加。

于是可以分治。

```cpp
inline void OR(modint *f) {
	for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
		for (int i = 0; i < n; i += o)
			for (int j = 0; j < k; j++)
				f[i+j+k] += f[i+j];
}
```

#### $fwt[a] \to a$

由
$$
fwt[a] = \text{merge}(fwt[a_0], fwt[a_0] + fwt[a_1])
$$
可得
$$
a = \text{merge}(a_0, a_1 - a_0)
$$

```cpp
inline void IOR(modint *f) {
	for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
		for (int i = 0; i < n; i += o)
			for (int j = 0; j < k; j++)
				f[i+j+k] -= f[i+j];
}
```

显然两份代码可以合并。

```cpp
inline void OR(modint *f, modint x = 1) {
	for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
		for (int i = 0; i < n; i += o)
			for (int j = 0; j < k; j++)
				f[i+j+k] += f[i+j] * x;
}
```

### 与

同理或。

```cpp
inline void AND(modint *f, modint x = 1) {
	for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
		for (int i = 0; i < n; i += o)
			for (int j = 0; j < k; j++)
				f[i+j] += f[i+j+k] * x;
}
```

### 异或


定义 $x\otimes y=\text{popcount}(x \& y) \bmod 2$，其中 $\text{popcount}$ 表示「二进制下 $1$ 的个数」。

满足 $(i \otimes j) \operatorname{xor} (i \otimes k) = i \otimes (j \operatorname{xor} k)$。

构造 $fwt[a]_i = \sum_{i\otimes j = 0} a_j - \sum_{i\otimes j = 1} a_j$。

则有

$$
\begin{aligned}
fwt[a] \times fwt[b] &= \left(\sum_{i\otimes j = 0} a_j - \sum_{i\otimes j = 1} a_j\right)\left(\sum_{i\otimes k = 0} b_k - \sum_{i\otimes k = 1} b_k\right) \\
&=\left(\sum_{i\otimes j=0}a_j\right)\left(\sum_{i\otimes k=0}b_k\right)-\left(\sum_{i\otimes j=0}a_j\right)\left(\sum_{i\otimes k=1}b_k\right)-\left(\sum_{i\otimes j=1}a_j\right)\left(\sum_{i\otimes k=0}b_k\right)+\left(\sum_{i\otimes j=1}a_j\right)\left(\sum_{i\otimes k=1}b_k\right) \\
&=\sum_{i\otimes(j \operatorname{xor} k)=0}a_jb_k-\sum_{i\otimes(j\operatorname{xor} k)=1}a_jb_k \\
&= fwt[c]
\end{aligned}
$$

因此

$$
\begin{aligned}
fwt[a] &= \text{merge}(fwt[a_0] + fwt[a_1], fwt[a_0] - fwt[a_1]) \\\\
a &= \text{merge}(\frac{a_0 + a_1}2, \frac{a_0 - a_1}2)
\end{aligned}
$$

```cpp
inline void XOR(modint *f, modint x = 1) {
	for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
		for (int i = 0; i < n; i += o)
			for (int j = 0; j < k; j++)
				f[i+j] += f[i+j+k],
				f[i+j+k] = f[i+j] - f[i+j+k] - f[i+j+k],
				f[i+j] *= x, f[i+j+k] *= x;
}
```

### 【模板】[P4717 【模板】快速沃尔什变换](https://www.luogu.com.cn/problem/P4717)

```cpp
const int N = 1 << 17 | 1;
int n, m;
modint A[N], B[N], a[N], b[N];

inline void in() {
	for (int i = 0; i < n; i++) a[i] = A[i], b[i] = B[i];
}

inline void get() {
	for (int i = 0; i < n; i++) a[i] *= b[i];
}

inline void out() {
	for (int i = 0; i < n; i++) print(a[i], " \n"[i==n-1]);
}

inline void OR(modint *f, modint x = 1) {
	for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
		for (int i = 0; i < n; i += o)
			for (int j = 0; j < k; j++)
				f[i+j+k] += f[i+j] * x;
}

inline void AND(modint *f, modint x = 1) {
	for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
		for (int i = 0; i < n; i += o)
			for (int j = 0; j < k; j++)
				f[i+j] += f[i+j+k] * x;
}

inline void XOR(modint *f, modint x = 1) {
	for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
		for (int i = 0; i < n; i += o)
			for (int j = 0; j < k; j++)
				f[i+j] += f[i+j+k],
				f[i+j+k] = f[i+j] - f[i+j+k] - f[i+j+k],
				f[i+j] *= x, f[i+j+k] *= x;
}

int main() {
	rd(m), n = 1 << m;
	for (int i = 0; i < n; i++) rd(A[i]);
	for (int i = 0; i < n; i++) rd(B[i]);
	in(), OR(a), OR(b), get(), OR(a, P - 1), out();
	in(), AND(a), AND(b), get(), AND(a, P - 1), out();
	in(), XOR(a), XOR(b), get(), XOR(a, (modint)1 / 2), out();
	return 0;
}
```

---

## 作者：warzone (赞：94)

Upd 2025/06/08：修复部分 Markdown 并调整题解中部分符号。

以下是一个偏向于初学者的题解。
## 卷积的定义
对于一个序列，将其中元素一一映射到一个多项式函数的系数上，  
这个多项式函数便叫做该序列的 **生成函数**。  
形式化地讲，对于序列 $f_0,f_1,\cdots,f_n$，$f(x)=\displaystyle\sum_{k=0}^nf_kx^k$ 为其生成函数。  
**卷积** 即为生成函数的乘积在对应序列的变换上的的抽象，  
“卷”即为其作用效果，“积”即为其本质。  
对于序列 $f,g$，其卷积序列 $f\times g$ 满足 

$$(f\times g)_k=\displaystyle\sum_{i=0}^kf_i g_{k-i}=\sum_{i+j=k}f_i g_j$$  

FFT 计算的是循环卷积，也即 $(f\times g)_k=\displaystyle\sum_{i+j\equiv k\pmod n}f_i g_j$，$n$ 为序列长度。
## 卷积的基本性质
- $f\times g=g\times f$  
  显而易见的交换律，用定义 $(f\times g)_k=\displaystyle\sum_{i+j=k}f_i g_j$，  
  乘法交换律 $a b=b a$ 即可证明。
- $(f\times g)\times h=f\times(g \times h)$（结合律）  
  证明： $(f\times(g\times h))_n=\displaystyle\sum_{a+b=n}f_a(g\times h)_b$  
  $$=\sum_{a+b=n}f_a\sum_{i+j=b}g_ih_j=\sum_{a+(i+j)=n}f_ag_ih_j=\sum_{(a+i)+j=n}f_ag_ih_j$$
  反向推导即可得证。
- $(f+ g)\times h=(f\times h)+(g\times h)$（分配律）  
  其中 $(f+ g)_k=f_k+g_k$ 表示向量加法。  
  证明：$((f+ g)\times h)_k=\displaystyle\sum_{i=0}^k(f+ g)_ih_{k-i}=\sum_{i=0}^k (f_i+g_i)h_{k-i}$  
  $$=\sum_{i=0}^k(f_ih_{k-i}+g_ih_{k-i})=\sum_{i=0}^kf_ih_{k-i}+\sum_{i=0}^kg_ih_{k-i}\\   
  =(f\times h)_k+(g\times h)_k=((f\times h)+(g\times h))_k$$  
- $(\lambda f)\times g=f\times (\lambda g)=\lambda(f\times g)$（与数乘的相容性）  
  其中 $(\lambda f)_k=\lambda f_k$ 表示数乘。  
  证明：$((\lambda f)\times g)_k=\displaystyle\sum_{i=0}^k(\lambda f)_ig_{k-i}=\sum_{i=0}^k\lambda f_ig_{k-i}=\lambda\sum_{i=0}^kf_ig_{k-i}=\lambda(f\times g)_k$  
  $f\times (\lambda g)=\lambda(f\times g)$ 同理。

## 位运算卷积定义及其性质
一般的卷积满足 $i+j=k$，又称为加法卷积。

类似的，对于序列 $f=\{f_0,f_1,\cdots,f_{2^n-1}\},g=\{g_0,g_1,\cdots,g_{2^n-1}\}$，  
可以定义位运算卷积 $\displaystyle(f\times_\odot g)_k=\sum_{i\odot j=k}f_i g_j$，其中 $\odot=\text{and},\text{or},\text{xor}$。  
还有 $\max$ 卷积，这里不再拓展，  读者自行查找相关资料，现在着重讨论 $\times_\text{xor}$
- $\displaystyle f\times_\text{xor} g=g\times_\text{xor} f$（交换律）  
  由于 $a\operatorname{xor}b=b\operatorname{xor}a$，根据定义显然成立。  
  $\operatorname{and},\operatorname{or}$ 同样满足此性质，原因同上。
- $(f\times_\text{xor} g)\times_\text{xor} h=f\times_\text{xor}(g \times_\text{xor} h)$（结合律）  
  证明： $(f\times_\text{xor}(g\times_\text{xor} h))_k=\displaystyle\sum_{a\operatorname{xor}b=k}f_a(g\times_\text{xor} h)_b$  
  $$=\sum_{a\operatorname{xor}b=k}f_a\sum_{i\operatorname{xor}j=b}g_ih_j=\sum_{a\operatorname{xor}(i\operatorname{xor}j)=k}f_ag_ih_j=\sum_{(a\operatorname{xor}i)\operatorname{xor}j=k}f_ag_ih_j$$ 
  反向推导即可得证。$\operatorname{and},\operatorname{or}$ 同理。
- $(f+ g)\times_\text{xor} h=(f\times_\text{xor} h)+(g\times_\text{xor} h)$（分配律）  
  证明同加法卷积，$\operatorname{and},\operatorname{or}$ 同理。
- $(\lambda f)\times_\text{xor} g=f\times_\text{xor} (\lambda g)=\lambda(f\times_\text{xor} g)$（与数乘的相容性）  
  证明同加法卷积，$\operatorname{and},\operatorname{or}$ 同理。

## FFT 的性质
在 FFT 的实现过程中，我们得到了两个很重要的处理方法：
奇偶分段和蝴蝶变换。  
现在让我们仔细审视一下 FFT 的变换过程。  
分治证明式：  
$$f(w^k_n)=f_0(w^k_\frac{n}{2})+w^k_n f_1(w^k_\frac{n}{2})$$  
$$f(w^{k+\frac{n}{2}}_n)=f_0(w^k_\frac{n}{2})-w^k_n f_1(w^k_\frac{n}{2})$$
实际变换过程：  
$$
\begin{matrix}
f_0(w^k_\frac{n}{2}) & f_1(w^k_\frac{n}{2}) \\
\Downarrow & \Downarrow \\
f_0(w^k_\frac{n}{2})+w^k_n f_1(w^k_\frac{n}{2}) & f_0(w^k_\frac{n}{2})-w^k_n f_1(w^k_\frac{n}{2})
\end{matrix}
$$
注意到单次卷积 DFT $\rightarrow$ 点乘 $\rightarrow$ IDFT 实际上是一个单次递归过程。  
（ DFT 时向下递归，点乘时到达底部，IDFT 时向上回溯）   
那么 IDFT 就是：
$$
\begin{matrix}
f_0(w^{-k}_\frac{n}{2}) & f_1(w^{-k}_\frac{n}{2}) \\
\Downarrow & \Downarrow \\
f_0(w^{-k}_\frac{n}{2})+w^{-k}_n f_1(w^{-k}_\frac{n}{2}) & f_0(w^{-k}_\frac{n}{2})-w^{-k}_n f_1(w^{-k}_\frac{n}{2})
\end{matrix}
$$
设 $\mathcal{F}(f)$ 表示对序列 $f$ 作 DFT 以后的序列，
$\mathcal{F}^{-1}(f)$ 表示对序列 $f$ 作 IDFT 以后的序列。  
我们已经知道了以下性质：
$$\mathcal{F}^{-1}(\mathcal{F}(f))=\mathcal{F}(\mathcal{F}^{-1}(f))=f$$
$$\mathcal{F}(f\times g)_k=\mathcal{F}(f)_k \mathcal{F}(g)_k$$
$$\mathcal{F}(f+ g)=\mathcal{F}(f)+ \mathcal{F}(g),\mathcal{F}(\lambda f)=\lambda \mathcal{F}(f)$$

## FWT的推导过程
我们希望通过与 FFT 类似的方法实现位运算卷积。  
设 $\mathcal{F}_\text{xor}(f)$ 表示 FWT 的异或形式，则其至少满足：  
$$f\times_\text{xor}g=\mathcal{F}^{-1}_\text{xor}(\mathcal{F}_\text{xor}(f)\cdot \mathcal{F}_\text{xor}(g))$$ 
其中 $\cdot$ 表示对应位置相乘。  

已知 $c=a\times_\text{xor}b$，设三个序列奇偶分段后分别为 $c_0,c_1,a_0,a_1,b_0,b_1$，则显然有  
$$c_0=(a_0\times_\text{xor}b_0)+(a_1\times_\text{xor}b_1)$$
$$c_1=(a_1\times_\text{xor}b_0)+(a_0\times_\text{xor}b_1)$$

考虑蝴蝶变换，发现
$$(a_0+a_1)\times_\text{xor}(b_0+b_1)=(a_0\times_\text{xor}b_0)+(a_1\times_\text{xor}b_1)+(a_0\times_\text{xor}b_1)+(a_1\times_\text{xor}b_0)$$
$$(a_0-a_1)\times_\text{xor}(b_0-b_1)=(a_0\times_\text{xor}b_0)+(a_1\times_\text{xor}b_1)-(a_0\times_\text{xor}b_1)-(a_1\times_\text{xor}b_0)$$
其中 $-$ 为向量减法，即 $a-b=a+(-1)b$。

显然，逆变换时只要对如上两式加减消元即可。  
于是可得 $\mathcal{F}_\text{xor}$ 为：

$$
\begin{matrix}
a_0 & a_1 & b_0 & b_1\\
\Downarrow & \Downarrow &
\Downarrow & \Downarrow \\
a_0+ a_1 & a_0-a_1 & 
b_0+ b_1 & b_0-b_1
\end{matrix}
$$

向下递归，计算出卷积 
$$d_0=(a_0+a_1)\times_\text{xor}(b_0+b_1)$$
$$d_1=(a_0-a_1)\times_\text{xor}(b_0-b_1)$$
回溯时，逆变换为
$$
\begin{matrix}
\dfrac{1}{2}(d_0+d_1) & \dfrac{1}{2}(d_0-d_1) \\
\Uparrow & \Uparrow \\
d_0 & d_1
\end{matrix}
$$
注意到系数 $\dfrac{1}{2}$ 可以提出来，到最后再除，因此可得到： $\mathcal{F}^{-1}_\text{xor}(f)_k=2^{-n}\mathcal{F}_\text{xor}(f)_k$  
类似的，可以得到 $\operatorname{and},\operatorname{or}$ 的位运算卷积，这里读者自行推导，只给出结果：
$$

\begin{matrix}
 & a_0 & a_1 &  & a_0-a_1 & a_1\\
\mathcal{F}_\text{and}: & \Downarrow & \Downarrow & \mathcal{F}^{-1}_\text{and}: & \Uparrow & \Uparrow \\
 & a_0+ a_1 & a_1 & & a_0 & a_1
\end{matrix}
$$
$$
\begin{matrix}
 & a_0 & a_1 & & a_0 & a_1-a_0\\
\mathcal{F}_\text{or}: & \Downarrow & \Downarrow & \mathcal{F}^{-1}_\text{or}: & \Uparrow & \Uparrow \\
 & a_0 & a_1+ a_0 & & a_0 & a_1
\end{matrix}
$$
自此，我们已经可以 $\Theta(n\log n)$ 实现单次位运算卷积，即：
$$f\times_\text{xor}g=\mathcal{F}^{-1}_\text{xor}(\mathcal{F}_\text{xor}(f)\cdot \mathcal{F}_\text{xor}(g))$$  

## FWT 的性质
为了方便使用，我们希望 FWT 满足与 FFT 类似的性质。
- $\mathcal{F}_\text{xor}^{-1}(\mathcal{F}_\text{xor}(f))=f$  
	证明：在序列长度为 $2^0=1$ 时，$\mathcal{F}_\text{xor}(f)=\mathcal{F}^{-1}_\text{xor}(f)=f$，性质显然成立  
    序列长度 $>1$ 时，考虑不做卷积，只有蝴蝶变换，得到
  $$
  \begin{matrix}
  & f_0 & f_1 \\
  \mathcal{F}_\text{xor}: & \Downarrow & \Downarrow \\
  & f_0+f_1 & f_0-f_1 \\
  \texttt{递归:} & \Downarrow & \Downarrow \\
  	& g_0=\mathcal{F}^{-1}_\text{xor}(\mathcal{F}_\text{xor}(f_0+f_1)) &  g_1=\mathcal{F}^{-1}_\text{xor}(\mathcal{F}_\text{xor}(f_0-f_1)) \\
  \mathcal{F}^{-1}_\text{xor}: & \Downarrow & \Downarrow \\
  & \dfrac{1}{2}(g_0+g_1) & \dfrac{1}{2}(g_0-g_1)
  \end{matrix}
  $$
  显然
  $$\dfrac{1}{2}((f_0+f_1)+(f_0-f_1))=\frac{1}{2}(2f_0)=f_0$$
  $$\dfrac{1}{2}((f_0+f_1)-(f_0-f_1))=\frac{1}{2}(2f_1)=f_1$$
  便可递归证明。  
  $\operatorname{and},\operatorname{or}$ 证明类似：
  $$
  \begin{matrix}
  \mathcal{F}_\text{and}: & (a_0+a_1)-a_1=a_0 & a_1=a_1 \\
  \mathcal{F}_\text{or}: & a_0=a_0 & (a_1+a_0)-a_0=a_1
  \end{matrix}
  $$
- $\mathcal{F}_\text{xor}(\mathcal{F}^{-1}_\text{xor}(f))=f,\mathcal{F}_\text{xor}(f+ g)=\mathcal{F}_\text{xor}(f)+ \mathcal{F}_\text{xor}(g),\mathcal{F}_{\text{xor}}(\lambda f)=\lambda \mathcal{F}_{\text{xor}}(f)$  
	同上，此处不再赘述。
- $\mathcal{F}_\text{xor}(f\times_\text{xor} g)_k=\mathcal{F}_\text{xor}(f)_k \mathcal{F}_\text{xor}(g)_k$  
	证明：已知 $f\times_\text{xor}g=\mathcal{F}^{-1}_\text{xor}(\mathcal{F}_\text{xor}(f)\cdot \mathcal{F}_\text{xor}(g))$，则  
$$\mathcal{F}_\text{xor}(f\times_\text{xor}g)=\mathcal{F}_\text{xor}(\mathcal{F}^{-1}_\text{xor}(\mathcal{F}_\text{xor}(f)\cdot \mathcal{F}_\text{xor}(g)))=\mathcal{F}_\text{xor}(f)\cdot \mathcal{F}_\text{xor}(g)$$

## 总结与代码
经过严谨的推导，我们得出了 FWT 的实现，  
并发现其具有与 FFT 类似的性质，这为我们解题带来了极大的方便。
```cpp
#include<stdio.h>
#include<string.h>
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int word;
struct READ{
	char c;
	inline READ(){c=getchar();}
	template<typename type>
	inline READ& operator>>(register type& num){
		while('0'>c||c>'9') c=getchar();
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
};//快读快写 
#define mx 17
#define mx_ 16
word root[1<<mx],inv[1<<mx],realid[1<<mx];
const word mod=998244353;
inline ull pow(register ull a,register word b){
	register ull ans=1;
	for(;b;b>>=1){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
	}
	return ans;
}//快速幂 
#define loading()			\
	register ull num1=pow(3,(mod-1)>>mx);	\
	register ull num2=pow(num1,mod-2);	\
	register word head,i;	\
	register byte floor;	\
	register ull ni2=pow(2,mod-2);	\
	root[0]=inv[0]=1;	\
	for(i=1;head=i,i<(1<<mx);++i){	\
		root[i]=num1*root[i-1]%mod;	\
		inv[i]=num2*inv[i-1]%mod;	\
		for(floor=0;floor<mx;++floor,head>>=1)	\
			realid[i]=realid[i]<<1|(head&1);	\
	}
//单位根及下标翻转初始化 
#define load()	\
	register ull num1,num2;\
	register word head,i;	\
	register byte floor
//floor 变换区间大小
//head 变换区间头指针 
//i 变换位置 
#define nttfor(size)	\
	for(floor=0;floor<(size);++floor)	\
		for(head=0;head<(1u<<(size));head+=1u<<(floor+1))	\
			for(i=0;i<(1u<<(floor));++i)
//FFT/FWT循环 
#define ntt(num,root)(	\
	num1=(num)[head+i],	\
	num2=(num)[head+i+(1<<floor)],	\
	(num)[head+i]=(num1+((num2*=root[i<<(mx_-floor)])%=mod))%mod,	\
	(num)[head+i+(1u<<floor)]=(num1+mod-num2)%mod)
//FFT蝴蝶变换 
#define _and(num)(	\
	num1=(num)[head+i],	\
	(num)[head+i]=(num1+(num)[head+i+(1u<<floor)])%mod)
//FWT and 蝴蝶变换 
#define and_(num)(	\
	num1=(num)[head+i],	\
	(num)[head+i]=(num1+mod-(num)[head+i+(1u<<floor)])%mod)
//逆FWT and 蝴蝶变换 
#define _or(num)(	\
	num2=(num)[head+i+(1<<floor)],	\
	(num)[head+i+(1u<<floor)]=(num2+(num)[head+i])%mod)
//FWT or 蝴蝶变换 
#define or_(num)(	\
	num2=(num)[head+i+(1<<floor)],	\
	(num)[head+i+(1u<<floor)]=(num2+mod-(num)[head+i])%mod)
//逆FWT and 蝴蝶变换 
#define _xor(num)(	\
		num1=(num)[head+i],	\
		num2=(num)[head+i+(1<<floor)],	\
		(num)[head+i]=(num1+mod-num2)%mod,	\
		(num)[head+i+(1<<floor)]=(num1+num2)%mod)
//FWT xor 蝴蝶变换 
#define id(size,i) (realid[i]>>(mx-(size)))
//下标二进制翻转的编号 
#define FOR(size) for(i=0;i<1u<<(size);i++)
word eax[1<<mx],ebx[1<<mx],ecx[1<<mx],edx[1<<mx],eex[1<<mx],efx[1<<mx];
int main(){
	byte size;
	register READ cin;
	cin>>size;
	loading();
	FOR(size) cin>>eax[id(size,i)];
	FOR(size) cin>>ebx[id(size,i)];
	memcpy(ecx,eax,4u<<size);
	memcpy(edx,ebx,4u<<size);
	memcpy(eex,eax,4u<<size);
	memcpy(efx,ebx,4u<<size);
	nttfor(size){
		_or(eax),_or(ebx);
		_and(ecx),_and(edx);
	}
	FOR(size){
		head=id(size,i);
		root[head]=(ull)(eax[i])*ebx[i]%mod;
		inv[head]=(ull)(ecx[i])*edx[i]%mod;
	}
	nttfor(size) or_(root),and_(inv);
	FOR(size) printf("%u ",root[i]);
	putchar('\n');
	FOR(size) printf("%u ",inv[i]);
	putchar('\n');
	nttfor(size) _xor(eex),_xor(efx);
	FOR(size) root[id(size,i)]=(ull)(eex[i])*efx[i]%mod;
	nttfor(size) _xor(root);
    num1=pow(ni2,size);
	FOR(size) printf("%u ",num1*root[i]%mod);
	// $\mathcal{F}_\text{xor}^{-1}(f)_k=2^{-n}\mathcal{F}_\text{xor}(F)_k$
	return 0;
}
```

---

## 作者：LawrenceSivan (赞：46)

# 快速莫比乌斯&沃尔什变换(FMT&FWT)学习笔记


## 位运算卷积

之前提到了 FFT（快速傅里叶变换）、NTT（快速数论变换），他们都是对于加法卷积(多项式乘法)的快速变换。

回忆一下卷积的一般形式是：

$$\sum\limits_{i\oplus j=k}{A[i]B[j]}$$

根据上式我们可以给出位运算卷积的定义：

将第 $i$ 项与第 $j$ 项的乘积贡献到第 $i\oplus j$ 项，其中 $\oplus$ 是一种位运算。

## 思路

大致思路与 FFT 一致，首先进行正变换，之后逐位相乘，最后经过逆变换得出答案。

## 或卷积（FWT_or）

要求：

$$C[i]=\sum\limits_{j|k=i}{A[j]B[k]}$$

### 正变换 （FWT）

有个显然的性质是 $j|i=i,k|i=i \rightarrow(j|k)|i=i$。

于是可以构造：

$$FWT[A]_i=\sum\limits_{j|i=i}A[j]$$

意义是下标的子集对应位置之和。

$j|i=i$ 表示 $j$ 是 $i$ 的子集。

于是有：

$$FWT[A]_i\times FWT[B]_i=\left(\sum\limits_{j|i=i}{A[j]}\right)\left(\sum\limits_{k|i=i}{B[k]}\right)$$

$$=\sum\limits_{j|i=i}\sum\limits_{k|i=i}{A[j]B[k]}$$

$$=\sum\limits_{(j|k)|i=i}{A[j]B[k]}$$

$$=\sum\limits_{x|i=i}\sum\limits_{j|k=x}{A[j]B[k]}$$

$$=\sum\limits_{x|i=i}C[x]$$

$$=FWT[C]_i$$

依照这个思路，我们就完成了正变换。

直接做显然是 $\mathcal{O(n^2)}$ 的。

考虑如何快速实现这个过程：

回忆 FFT 的实现过程，我们通过分治降低了复杂度。

于是将整个区间分成两部分，进行分治。

对于一个长度为 $2^n$ 的多项式，我们使用 $A_0$ 表示前 $2^{n-1}$ 项，$A_1$ 表示后 $2^{n-1}$ 项。

可以发现，对于 $A_0$ ，他的下标最高位一定是 $0$，于是他的子集只能是自己的子集。

对于 $A_1$ 由于最高位是 $1$，所以它的子集除了包括自己的部分，还要包括 $A_0$ 的部分。

于是可以写出以下式子：

$$FWT[A]= \begin{cases}{\text{merge}(FWT[A_0],FWT[A_0]+FWT[A_1]),(n>0)}\\{A,(n=0)} \end{cases} $$

其中， $\text{merge}$ 表示拼接，$+$ 表示对应位置相加。

这就是分治手段。

事实上是高维前缀和。

### 逆变换 (IFWT)

满足 $A=IFWT(FWT(A))$。

#### 感性理解&做法

嗯，写这个主要是为了方便 ~~（逃~~

把正变换的符号换一下就行了。

由 

$${\text{merge}(FWT[A_0],FWT[A_0]+FWT[A_1]),(n>0)}$$ 

得：

$$IFWT(FWT(A))=merge(IFWT(FWT(A_0)),IFWT(FWT(A_1))-IFWT(FWT(A_0)))$$

简单一点就是：

$$A=merge(A_0,A_1-A_0)$$

感性理解就是前缀和与差分的关系。

实际上是高维前缀差分。

#### 理性理解&证明

证明：

现在我们已知 $FWT[A]_0,FWT[A]_1$ ，要求出 $A_0,A_1$。

根据上面提到的 $A_0$ 的子集只包括自己的那一部分，得到：

$$FWT[A]_0=FWT[A_0]$$

所以:

$$A_0=IFWT(FWT(A_0))=IFWT(FWT(A)_0)$$

依据上面提到的 $A_1$ 还要包括 $A_0$ 的那一部分，得到：

$$FWT[A]_1=FWT[A_0]+FWT[A_1]$$

$$FWT[A_1]=FWT[A]_1-FWT[A_0]=FWT[A]_1-FWT[A]_0$$

所以：

$$A_1=IFWT(FWT(A_1))=IFWT(FWT[A]_1-FWT[A]_0)$$

之后合并：

$$A=merge(IFWT(FWT(A)_0),IFWT(FWT[A]_1-FWT[A]_0))$$

~~似乎感性理解已经完全够用了~~

### CODE:

```cpp
inline void FWT_or(int *a,int op){
    for(re int i=1;i<n;i<<=1){
        for(re int p=i<<1,j=0;j<n;j+=p){
            for(re int k=0;k<i;k++){
                (a[i+j+k]+=a[j+k]*op+mod)%=mod;
            }
        }
    }
}
```

## 与卷积（FWT_and）

要求：

$$C[i]=\sum\limits_{j \& k=i}{A[j]B[k]}$$

### 正变换 （FWT）

有了前面的构造经验，我们可以类似地得出以下构造方式：

$$FWT[A]_i=\sum\limits_{i|j=j}A[j]$$

意义依旧是是下标的子集对应位置之和。

$i|j=j$ 表示 $i$ 是 $j$ 的子集。

证明：

$$FWT[A]_i\times FWT[B]_i=\left(\sum\limits_{i|j=j}{A[j]}\right)\left(\sum\limits_{i|k=k}{B[k]}\right)$$

$$=\sum\limits_{i|j=j}\sum\limits_{i|k=k}A[j]B[k]$$

$$=\sum\limits_{i|(j\&k)=(j\&k)}A[j]B[k]$$

$$=\sum\limits_{i|x=x}\sum\limits_{j\&k=x}{A[j]B[k]}$$

$$=\sum\limits_{i|x=x}C[x]$$

$$=FWT[C]_i$$

可以发现与卷积和或卷积十分相似，前者是后面对前面有贡献，后者是前面对后面有贡献。

类比或卷积即可得到递归公式：

$$FWT[A]= \begin{cases}{\text{merge}(FWT[A_0]+FWT[A_1]，FWT[A_1]),(n>0)}\\{A,(n=0)} \end{cases} $$

证明：

依旧考虑分治：

对于一个长度为 $2^n$ 的多项式，我们使用 $A_0$ 表示前 $2^{n-1}$ 项，$A_1$ 表示后 $2^{n-1}$ 项。

可以发现，由于按位与的性质是集合只会变小不会变大，所以分成左右两个部分之后 $A_1$ 与 $A_0$ 按位与得到的结果只能是首位为 $0$ ，这么说来后面会变成前面的子集，而前面只会包含自己，所以后面的贡献要加到前面去。

实际上是高维后缀和。

### 逆变换 (IFWT)

满足 $A=IFWT(FWT(A))$。

#### 感性理解&做法

依旧是把正变换的符号换一下就行了。

由 

$${\text{merge}(FWT[A_0]+FWT[A_1]+FWT[A_1]),(n>0)}$$ 

得：

$$IFWT(FWT(A))=merge(IFWT(FWT(A_0))-IFWT(FWT(A_1)),IFWT(FWT(A_1))$$

简单一点就是：

$$A=merge(A_0-A_1,A_1)$$

实际上是高维后缀差分。

#### 理性理解&证明

是真的不太清楚这玩意有啥用，咕了。

### CODE:

```cpp
inline void FWT_and(int *a,int op){
	for(re int i=1;i<n;i<<=1){
		for(re int p=i<<1,j=0;j<n;j+=p){
			for(re int k=0;k<i;k++){
				(a[j+k]+=a[i+j+k]*op+mod)%=mod;
			}
		}
	}
}
```

## 异或卷积（FWT_xor）

要求：

$$C[i]=\sum\limits_{j \oplus k=i}{A[j]B[k]}$$

### 正变换 （FWT）

参照上面的构造经验，我们需要构造出变换满足：

$$FWT(C)_x=FWT(A)_xFWT(B)_x$$

考虑到 FWT 是线性变换，所以可以做出以下构造：

$$FWT(F)_x=\sum\limits_{i=0}^{n}g(x,i)F_i$$

其中 $g$ 是一个系数。

于是需要做到：

$$\sum\limits_{i=0}^{n}g(x,i)C_i=\left(\sum\limits_{j=0}^{n}g(x,j)A_j\right)\left(\sum\limits_{k=0}^{n}g(x,k)B_k\right)$$

代入 $C_i$ 得到：

$$\left(\sum\limits_{i=0}^{n}g(x,i)\right)\left(\sum\limits_{j \oplus k=i}{A[j]B[k]}\right)=\left(\sum\limits_{j=0}^{n}g(x,j)A_j\right)\left(\sum\limits_{k=0}^{n}g(x,k)B_k\right)$$

化简整理可得：

$$\sum\limits_{j=0}^{n}\sum\limits_{k=0}^{n}g(x,j \oplus k)A[j]B[k]=\sum\limits_{j=0}^{n}\sum\limits_{k=0}^{n}g(x,j)g(x,k)A[j]B[k]$$

于是只需要令：

$$g(x,j \oplus k)=g(x,j)g(x,k)$$

即可。

接下来的手法就有些奇妙了。

考虑异或操作之后 $i,j$ 的什么属性会把他们和 $i \oplus j$ 联系起来。

有个结论是在异或前后 $1$ 的个数的奇偶性不会发生变化。

具体就是异或前 $i,j$ 的 $1$ 的个数的和与 $i \oplus j$ 的奇偶性相同。

证明过程是按位考虑的。

分两种情况：

1. 两个数对应位相同，如果都是 $1$ ，那么 $1$ 的个数减少 $2$ ，奇偶性不变；如果都是 $0$ ，那么 $1$ 的个数不变化。
2. 两个数不同，只能是一个 $1$ 一个 $0$ ，所以 $1$ 的数量不变。

证毕；

形式化的说法是:

>  $ \rm{popcount(a)+popcount(b)\equiv popcount(a\ xor\ b)\pmod 2}$

于是我们可以构造：

$$g(x,i)=(-1)^{|i \cap x|}$$

每一项是二进制表示的集合

$i \cap x$ 实际就是取出了 $i$ 中 $x$ 是 $1$ 的位。

如此构造满足了：

$$g(x,j \oplus k)=g(x,j)g(x,k)$$

证明：

由：

$$g(x,i)=(-1)^{|i \cap x|}$$

得：

$$g(x,j \oplus k)=g(x,j)g(x,k)$$

$$=(-1)^{|(j \oplus k) \cap x|}=(-1)^{|j \cap x|}(-1)^{|k \cap x|}$$

$$=(-1)^{|(j \oplus k) \cap x|}=(-1)^{|j \cap x|+|k \cap x|}$$

其中 $i \cap x$ 表示取出了 $i$ 中 $x$ 是 $1$ 的位。

其中 $|i \cap x|$ 表示取出了 $i$ 中 $x$ 是 $1$ 的位的个数。

根据上面的结论，$|(j \oplus k) \cap x|\equiv|j \cap x|+|k \cap x|\pmod 2$

所以两式确实相等。

证毕。

于是我们得到了 FWT_xor 的变换方式：

$$FWT(F)_x=\sum\limits_{i=0}^{n}(-1)^{|i \cap x|}F_i$$

或许你看着这样的比较顺眼：

$$FWT(F)_x=\sum\limits_{i=0}^{n}(-1)^{|i \& x|}F_i$$

也可以写成：

$$FWT(F)_x=\sum\limits_{\text{c}(x\&i)\pmod 2=0}F[i]-\sum\limits_{\text{c}(x\&k)\pmod 2=1}F[k]$$

其中 $c$ 代表 $\text{popcount}$. 

这里似乎有一个关于底数问题的讨论？

~~但是我觉得似乎比较显然，就放个链接略过吧~~

[关于底数问题的讨论](https://moyujiang.blog.luogu.org/solution-p4717)

每一个位置对于 $FWT(F)_x$ 都有贡献，贡献的正负由集合大小的奇偶性决定。

递归式是这样的：

$$FWT[A]= \begin{cases}{\text{merge}(FWT[A_0]+FWT[A_1]，FWT[A_0]-FWT[A_1]),(n>0)}\\{A,(n=0)} \end{cases} $$

快速变换还是基于分治增量：

对于新加入的一位，分两种情况考虑，把当前集合也分成选或不选，取放右边，不取放左边。

1. 取，如果与取的状态合并，集合大小不变；若和不取的状态合并，那么集合大小-1，所以贡献取反。
2. 不取，与取或不取状态取并，集合大小都不会变。

于是取会累加到取，累减到不取。

不取同时累加到取或者不取。

### 逆变换 (IFWT)

满足 $A=IFWT(FWT(A))$。

#### 感性理解&做法

如果方便记忆的话，那么直接 $\times inv2$ 即可。

感性一些的做法是直接移项两式和差什么的就好了。

$$IFWT(FWT(A))=merge\left(\dfrac{IFWT(FWT(A_0))+IFWT(FWT(A_1))}{2},\dfrac{IFWT(FWT(A_0)-IFWT(FWT(A_1)}{2}\right)$$

即：

$$A=\text{merge}\left(\dfrac{A_0+A_1}{2},\dfrac{A_0-A_1}{2}\right)$$

### CODE:

```cpp
inline void FWT_xor(int *a,int op){
	for(re int i=1;i<n;i<<=1){
		for(re int p=i<<1,j=0;j<n;j+=p){
			for(re int k=0;k<i;k++){
				int X=a[j+k],Y=a[i+j+k];
				a[j+k]=(X+Y)%mod;
				a[i+j+k]=(X+mod-Y)%mod;
				(a[j+k]*=op)%=mod,(a[i+j+k]*=op)%=mod;
			}
		}
	}
}
```

似乎代码还挺~~好背~~简单的？

## 全部代码：

```cpp
//#define LawrenceSivan

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define INF 0x3f3f3f3f
#define re register
#define int ll

namespace IO{
	template<typename T>
	inline void read(T &x){
		x=0;T f=1;char ch=getchar();
		while (!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
		while (isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
		x*=f;
	}

	template <typename T, typename... Args>
	inline void read(T& t, Args&... args){
		read(t); read(args...);
	}

	template<typename T>
	void write(T x){
		if(x<0)putchar('-'),x=-x;
		if(x>9)write(x/10);
		putchar(x%10+'0');
	}

	template<typename T,typename... Args>
	void write(T t,Args... args){
		write(t);putchar(' ');write(args...);
	}
}

using namespace IO;

const int maxn=1<<17|1;
const int mod=998244353;

int n,inv2=(mod+1)>>1;

int A[maxn],B[maxn],a[maxn],b[maxn];

inline void copy(){
	memcpy(a,A,sizeof(A));
	memcpy(b,B,sizeof(B));
}

inline void mul(){
	for(re int i=0;i<n;i++){
		a[i]=(a[i]*b[i])%mod;
	}
}

inline void print(){
	for(re int i=0;i<n;i++){
		write(a[i]),putchar(' ');
	}
	puts("");
}

inline void FWT_or(int *a,int op){
	for(re int i=1;i<n;i<<=1){
		for(re int p=i<<1,j=0;j<n;j+=p){
			for(re int k=0;k<i;k++){
				(a[i+j+k]+=a[j+k]*op+mod)%=mod;
			}
		}
	}
}

inline void FWT_and(int *a,int op){
	for(re int i=1;i<n;i<<=1){
		for(re int p=i<<1,j=0;j<n;j+=p){
			for(re int k=0;k<i;k++){
				(a[j+k]+=a[i+j+k]*op+mod)%=mod;
			}
		}
	}
}

inline void FWT_xor(int *a,int op){
	for(re int i=1;i<n;i<<=1){
		for(re int p=i<<1,j=0;j<n;j+=p){
			for(re int k=0;k<i;k++){
				int X=a[j+k],Y=a[i+j+k];
				a[j+k]=(X+Y)%mod;
				a[i+j+k]=(X+mod-Y)%mod;
				(a[j+k]*=op)%=mod,(a[i+j+k]*=op)%=mod;
			}
		}
	}
}

signed main(){
#ifdef LawrenceSivan
	freopen("aa.in","r", stdin);
	freopen("aa.out","w", stdout);
#endif
	read(n);n=1<<n;
	for(re int i=0;i<n;i++)read(A[i]);
	for(re int i=0;i<n;i++)read(B[i]);
	copy();FWT_or(a,1),FWT_or(b,1),mul(),FWT_or(a,-1),print();
	copy();FWT_and(a,1),FWT_and(b,1),mul(),FWT_and(a,-1),print();
	copy();FWT_xor(a,1),FWT_xor(b,1),mul(),FWT_xor(a,inv2),print();


	return 0;
}
```

---

## 作者：a___ (赞：36)

所谓 $\lceil\mathsf{FWT}\rfloor$ 主要就是构造一种 **可逆** 的 **快速** 的 **变换** $F$ 使 $F(C)=F(A)\cdot F(B)$，以 **快速解决** 某些 **下标位运算卷积** 的问题。   
（$C=A\cdot B$ 指 $\forall i\ \ \ C_i=A_i\times B_i$）   


- $\lceil\mathsf{FWT - or}\rfloor$     

求
$$\forall i\ \ \ C_i=\sum_{j|k=i}A_jB_k$$

设 $T'=F(T)$ 使 $\forall i\ \ \ T'_ i=\sum\limits_{j|i=i}T_j$。（即其 **下标的所有子集处** 的值的和）

由于 $j|i=i,k|i=i\Rightarrow (j|k)|i=i$（$j$ 是 $i$ 的子集，$k$ 是 $i$ 的子集，那么 $j\cup k$ 也是 $i$ 的子集），  
则有 $\forall i,$    
$$\large\begin{aligned}&F(A)_ i\times F(B)_ i\\=&\left(\sum_{j|i=i}A_j\right)\left(\sum_{k|i=i}B_k\right)\\=&\sum_{j|i=i}\sum_{k|i=i}A_jB_k\\=&\sum_{(j|k)|i=i}A_jB_k\\=&F(C)_ i\end{aligned}$$   

得证 $F(C)=F(A)\cdot F(B)$。    

快速进行变换 $F$：    
性质 1：二进制下每 $2^i$ 个数前 $i$ 位（第 $0 \sim i-1$ 位）对应相同。    
证明：$x\equiv x+2^i \pmod {2^i}$。  
性质 2：二进制下相差 $2^i$ 的两数第 $i$ 位相异。   
证明：$\left\lfloor\dfrac {x+2^i}{2^i}\right\rfloor\equiv\left\lfloor\dfrac {x\oplus2^i}{2^i}\right\rfloor \pmod 2$。   

设 $F_0(A)$ 表示二进制最高位（第 $i$ 位）为 $0$ 的数（前 $2^{i-1}$ 个数）仅考虑前 $i-1$ 位的答案，$F_1(A)$ 表示最高位为 $1$ 的数（后 $2^{i-1}$ 个数）仅考虑前 $i-1$ 位的答案，则   
$$F(A)=F_0(A),F_0(A)+F_1(A)$$  
（其中 $+$ 表示对应位相加）  
证明：对于前 $2^{i-1}$ 个数，其最高位为 $0$，其子集不会有最高位为 $1$ 的数，所以答案与后面无关；   
对于后 $2^{i-1}$ 个数（$\forall x$），其最高位为 $1$，是 $x-2^i$ 子集的也一定是 $x$ 的子集，所以要加上 $x-2^i$ 位的答案。    

同理，逆变换就是把加的反着减掉就好。   

具体实现就是枚举 $i$，枚举每一段数，在前一半和后一半之间做贡献。

代码：   
```cpp
void FWTor(int a[],int type)
{
    int i,j,k;
    for(i=1;i<=n;i++)
    for(j=0;j<(1<<n);j+=1<<i)
    for(k=0;k<(1<<i-1);k++)
    (a[j|(1<<i-1)|k]+=(a[j|k]*type+p)%p)%=p;
}
```

- $\lceil\mathsf{FWT - and}\rfloor$     

求
$$\forall i\ \ \ C_i=\sum_{j\&k=i}A_jB_k$$

类似或，与就是把子集变成超集再推一遍就好，这里省略不谈。  

设 $T'=F(T)$ 使 $\forall i\ \ \ T'_ i=\sum\limits_{j\&i=i}T_j$。

$$F(A)=F_0(A)+F_1(A),F_1(A)$$    

```cpp
void FWTand(int a[],int type)
{
    int i,j,k;
    for(i=1;i<=n;i++)
    for(j=0;j<(1<<n);j+=1<<i)
    for(k=0;k<(1<<i-1);k++)
    (a[j|k]+=(a[j|(1<<i-1)|k]*type+p)%p)%=p;
}
```

- $\lceil\mathsf{FWT - xor}\rfloor$     

求
$$\forall i\ \ \ C_i=\sum_{j\oplus k=i}A_jB_k$$
（$\oplus$ 表示异或）

异或比较麻烦，因为其不能像与和或那样简单地用子集关系表示。    

设 $i\circ j=\operatorname{popcount}(i\&j)\bmod 2$，则有    
$$(i\circ j) \oplus(i \circ k)=i\circ(j\oplus k)$$   
证明：  
$$\Leftrightarrow\operatorname{popcount}(i\&j)\oplus\operatorname{popcount}(i\&k)\equiv\operatorname{popcount}(i\&(j\oplus k)) \pmod 2$$   
$$\Leftrightarrow\operatorname{popcount}(i\&j)+\operatorname{popcount}(i\&k)\equiv\operatorname{popcount}(i\&(j\oplus k)) \pmod 2$$   
设 $x=i\&j,y=i\&k,z=i\&(j\oplus k)$   
$\forall p$ ，   
$x$ 的第 $p$ 位为 $1$，$y$ 的第 $p$ 位为 $1$，则 $z$ 的第 $p$ 位为 $0$（$j,k$ 都有异或无），$1+1\equiv0\pmod2$ ；   
$x$ 的第 $p$ 位为 $0$，$y$ 的第 $p$ 位为 $1$，则 $z$ 的第 $p$ 位为 $1$（$j,k$ 相异异或有），$0+1\equiv1\pmod2$ ；   
$x$ 的第 $p$ 位为 $1$，$y$ 的第 $p$ 位为 $0$，则 $z$ 的第 $p$ 位为 $1$（$j,k$ 相异异或有），$1+0\equiv1\pmod2$ ；   
$x$ 的第 $p$ 位为 $0$，$y$ 的第 $p$ 位为 $0$，则 $z$ 的第 $p$ 位为 $0$（$j,k$ 都无异或无），$0+0\equiv0\pmod2$ 。     
于是得证。    

设 $T'=F(T)$ 使 $\forall i\ \ \ T'_ i=\sum\limits_{j\circ i=0}T_j-\sum\limits_{j\circ i=1}T_j$

那么有 $\forall i,$    
$$\large\begin{aligned}&F(A)_ i\times F(B)_ i\\=&\left(\sum_{j\circ i=0}A_j-\sum_{j\circ i=1}A_j\right)\left(\sum_{k\circ i=0}B_k-\sum_{k\circ i=1}B_k\right)\\=&\left(\sum_{j\circ i=0}\sum_{k\circ i=0}A_jB_k+\sum_{j\circ i=1}\sum_{k\circ i=1}A_jB_k\right)-\left(\sum_{j\circ i=0}\sum_{k\circ i=1}A_jB_k+\sum_{j\circ i=1}\sum_{k\circ i=0}A_jB_k\right)\\=&\left(\sum_{(j\oplus k)\circ i=0\oplus0}A_jB_k+\sum_{(j\oplus k)\circ i=1\oplus1}A_jB_k\right)-\left(\sum_{(j\oplus k)\circ i=0\oplus1}A_jB_k+\sum_{(j\oplus k)\circ i=1\oplus0}A_jB_k\right)\\=&\sum_{(j\oplus k)\circ i=0}A_jB_k-\sum_{(j\oplus k)\circ i=1}A_jB_k\\=&F(C)_ i\end{aligned}$$    

得证 $F(C)=F(A)\cdot F(B)$。

快速进行变换 $F$：     
同样设 $F_0(A)$ 表示二进制最高位（第 $i$ 位）为 $0$ 的数（前 $2^{i-1}$ 个数）仅考虑前 $i-1$ 位的答案，$F_1(A)$ 表示最高位为 $1$ 的数（后 $2^{i-1}$ 个数）仅考虑前 $i-1$ 位的答案，则   
$$F(A)=F_0(A)+F_1(A),F_0(A)-F_1(A)$$    
证明：由于最高位原先默认为 $0$（或者说不考虑），   
对于前 $2^{i-1}$ 个数这一位 $0\&0=0,0\&1=0$，不变；   
对于后 $2^{i-1}$ 个数这一位 $1\&0=0,1\&1=1$，由于 $1$ 与 $0$ 不同，于是 $\circ$ 运算结果改变，差值与原先相反，所以是 $-F_1(A)$。   

同理逆变换就是反过来    
$$F'(A')=\frac{F'_ 0(A')+F'_ 1(A')}2,\frac{F'_ 0(A')-F'_ 1(A')}2$$    

```cpp
void FWTxor(int a[],long long type)
{
    int i,j,k,x,y;
    for(i=1;i<=n;i++)
    for(j=0;j<(1<<n);j+=1<<i)
    for(k=0;k<(1<<i-1);k++)
    x=(a[j|k]+a[j|(1<<i-1)|k])*type%p,
    y=(a[j|k]-a[j|(1<<i-1)|k]+p)*type%p,
    a[j|k]=x,a[j|(1<<i-1)|k]=y;
}
```   


________

附本题代码完全版：  
```cpp
#include<cstdio>
#include<cstring>
const int N=(1<<17)+10,p=998244353;
int n,a[N],b[N],ta[N],tb[N];
void FWTor(int a[],int type)
{
    int i,j,k;
    for(i=1;i<=n;i++)
    for(j=0;j<(1<<n);j+=1<<i)
    for(k=0;k<(1<<i-1);k++)
    (a[j|(1<<i-1)|k]+=(a[j|k]*type+p)%p)%=p;
}
void FWTand(int a[],int type)
{
    int i,j,k;
    for(i=1;i<=n;i++)
    for(j=0;j<(1<<n);j+=1<<i)
    for(k=0;k<(1<<i-1);k++)
    (a[j|k]+=(a[j|(1<<i-1)|k]*type+p)%p)%=p;
}
void FWTxor(int a[],long long type)
{
    int i,j,k,x,y;
    for(i=1;i<=n;i++)
    for(j=0;j<(1<<n);j+=1<<i)
    for(k=0;k<(1<<i-1);k++)
    x=(a[j|k]+a[j|(1<<i-1)|k])*type%p,
    y=(a[j|k]-a[j|(1<<i-1)|k]+p)*type%p,
    a[j|k]=x,a[j|(1<<i-1)|k]=y;
}
int main()
{
    int i;scanf("%d",&n);
    for(i=0;i<(1<<n);i++)scanf("%d",&a[i]),a[i]%=p;
    for(i=0;i<(1<<n);i++)scanf("%d",&b[i]),b[i]%=p;
    //or
    memcpy(ta,a,sizeof a);memcpy(tb,b,sizeof b);
    FWTor(ta,1);FWTor(tb,1);
    for(i=0;i<(1<<n);i++)ta[i]=(long long)ta[i]*tb[i]%p;
    FWTor(ta,-1);
    for(i=0;i<(1<<n);i++)printf("%d ",ta[i]);putchar('\n');
    //and
    memcpy(ta,a,sizeof a);memcpy(tb,b,sizeof b);
    FWTand(ta,1);FWTand(tb,1);
    for(i=0;i<(1<<n);i++)ta[i]=(long long)ta[i]*tb[i]%p;
    FWTand(ta,-1);
    for(i=0;i<(1<<n);i++)printf("%d ",ta[i]);putchar('\n');
    //xor
    memcpy(ta,a,sizeof a);memcpy(tb,b,sizeof b);
    FWTxor(ta,1);FWTxor(tb,1);
    for(i=0;i<(1<<n);i++)ta[i]=(long long)ta[i]*tb[i]%p;
    FWTxor(ta,(p+1)>>1);
    for(i=0;i<(1<<n);i++)printf("%d ",ta[i]);putchar('\n');
    return 0;
}
```

---

## 作者：摸鱼酱 (赞：32)

更新了 FWT-xor 地方关于底数选取的讨论。

[更好的阅读体验](https://www.moyujiang.com/964.html)

$$
c_x=\sum_{i\oplus j=x}a_ib_j
$$
当 $\oplus$ 为 $+$ 时，这个就是多项式乘法。

FMT/FWT 则是处理 $\oplus$ 为 $\rm{or,and,xor}$ 时的问题。

快速莫比乌斯变换和莫比乌斯函数/反演并无关系。

FMT 处理 $\rm{or/and}$ 时的问题，可以看作是集合的 交/并 来看。

FWT 处理 $\rm{xor}$ 时的问题。但是有时把 FMT 和 FWT 统称为 FWT。

下面的讲解可能都会带一点集合的味道，但是我不擅长这玩意，有描述不对的地方麻烦指出。

如果我的描述让你感到了疑惑，可以访问 [这篇博文](http://blog.leanote.com/post/rockdu/TX200) ，也许他的讲解会让你更理解一些。

计算

### 1.$\rm or$(并)

$$
c_x=\sum_{i∪j=x}a_ib_j
$$

考虑对一个序列 $\text F$ 进行莫比乌斯变换，得到 $\rm{FMT(F)}$  ,$\rm F$ 序列的第 $\rm x$ 项记为 $\rm{F_x}$。

如果我们有 $\rm{FMT(c)_n=FMT(a)_n*FMT(b)_n}$ ，并且可以 $\rm{FMT(F)→F}$ ，那就可以解决这个问题了。

我们考虑让 $\rm{FMT(F)_n=\sum_{i\subseteq n}F_i}$。
$$
\begin{aligned}
&\rm{FMT(a)_n*FMT(b)_n}\\
&\rm{=\sum_{i\subseteq n}a_i\sum_{j\subseteq n}b_j}\\
&\rm{=\sum_{k\subseteq n}\sum_{i∪j=k}a_ib_j}\\
&\rm{=FMT(c)_n}
\end{aligned}
$$
交换枚举的那个意义是先枚举 $\rm{k=i∪j}$，然后再枚举合法的 $\rm{i,j}$ ，这样和之前的枚举是等价的。

问题就转化为了如何快速变换了，也就是如何快速求子集和。

那我们考虑一种增量构造的方法。

令 $\rm{T_n}$ 表示 $\rm{FMT(F)_n}$ 。

新加入第 $i$ 个点。

如果不选，那么集合是 不选 $i$  的，答案不会变。

如果选了，那么集合是 选择 $i$  了的， 不选 $i$ 时的集合 会成为新的集合的子集，那答案也要对应加上去。

也就是用 选 $i$  的答案加上 不选 $i$  的答案，合并即可。

![](https://cdn.jsdelivr.net/gh/moyujiang/piccdn@0deea81e54dbcda77de29942de118c634dfc4639/2021/03/25/134266399e1bf062675ea6453f20bb96.png)

如图，这个过程可以分成 $\log$ 层来做，箭头就是累加，时间复杂度 $\mathcal O(n\log n)$ 。

考虑反过来的过程，我们就是要通过子集和反推原来的数列，那就把加进来的减回去就好了。

```cpp
void FMT_or(int *f,int n,int op){//op=1 FMT op=-1 IFMT
	for(int i=1;i<n;i<<=1)
		for(int o=i<<1,j=0;j<n;j+=o)
			for(int k=0;k<i;k++)
				(f[i+j+k]+=f[j+k]*op+p)%=p;
}
```

----------

### 2.$\rm{and}$(交)

$$
c_x=\sum_{i∩j=x}a_ib_j
$$

和 $\rm{or}$ 相似地，我们考虑 $\rm{FMT(F)_n}=\sum_{n\subseteq i}F_i$。
$$
\begin{aligned}
&\rm{FMT(a)_n*FMT(b)_n}\\
&\rm{=\sum_{n\subseteq i}\sum_{n\subseteq j}a_ib_j}\\
&\rm{=\sum_{n\subseteq x}\sum_{i∩j=x}a_ib_j}\\
&\rm{=FMT(c)_n}
\end{aligned}
$$
最后的改变枚举对象和上面也是类似的，可以不重不漏的枚举到所有的情况，只是换了个形式和 FMT(c) 重合。

也是相似地，我们考虑增量构造的方法求 $\rm{\sum_{n\subseteq i}F_i}$。

新加入一个元素 $i$ 。

如果 选 $i$ ，对应的集合和答案都不会变。

如果 不选 $i$  ，集合在 $i$ 这一位就对应 0 ，也就是缩小了，会成为 选 $i$  对应集合的子集。

由于求和方式的不同，和上面相反，这里需要的是用 不选 $i$  的答案加上 选 $i$  的答案。代码类似。

反过来的话是类似的，逐步减去即可。

```cpp
void FMT_and(int *f,int n,int op){//op=1 FMT op=-1 IFMT
	for(int i=1;i<n;i<<=1)
		for(int o=i<<1,j=0;j<n;j+=o)
			for(int k=0;k<i;k++)
				(f[j+k]+=f[i+j+k]*op+p)%=p;
}
```

--------------

### 3.$\rm{xor}$

$$
c_x=\sum_{i\ xor\ j=x}a_ib_j
$$

这里的 $\rm{FWT(F)}$ 不太好构造，稍微推导一下这个是怎么来的。

设 $\rm{FWT(F)_n=\sum_{i=0}^n}g(n,i)F_i$ ，这么设的原因是因为 $\rm{FWT(F)_n}$ 的第 $i$ 项的系数肯定只和 $n,i$ 线性相关，因为我们没有乘除操作。

然后带入 $\rm{FWT(c)_n=FWT(a)_n*FWT(b)_n}$ 中。
$$
\begin{aligned}
&\rm{\sum_{i=0}^ng(n,i)c_i=\sum_{j=0}^ng(n,j)a_j\sum_{k=0}^ng(n,k)b_k}\\
&\rm{\sum_{i=0}^ng(n,i)\sum_{j\ xor\ k=i}a_jb_k=\sum_{j=0}^ng(n,j)a_j\sum_{k=0}^ng(n,k)b_k}\\
&\rm{\sum_{j=0}^n\sum_{k=0}^ng(n,j\ xor \ k)a_jb_k=\sum_{j=0}^n\sum_{k=0}^ng(n,j)g(n,k)a_jb_k}\\
\end{aligned}
$$
不难发现， $\rm{g(n,j\ xor\ k)=g(n,j)*g(n,k)}$，那接下来要思考的就是啥样的东西会把 $\rm{j,k}$ 和 $\rm{j\ xor\ k}$ 联系起来。

虽然确实难想到，但是 $\rm{popcount(a)+popcount(b)\equiv popcount(a\ xor\ b)\pmod 2}$ 。

所以就有 $\rm{g(n,i)=(-1)^{|i∩n|}}$ 。这里把 $i,n$ 看做集合，实际就是取出了 $i$ 中 $n$ 是 1 的位数。

那么就可以 $\rm{FWT(F)_x=\sum_{i=0}^n(-1)^{|i∩x|}F_i}$。

按道理，这里的 -1 是可以换成任意数的，但是稍微把 0,1 这种数带进去就知道有问题。问题出在哪呢？

我们定义 g 的时候就说了，它和 n,i 线性相关，但是当底数是 0,1 的时候，它似乎和 n,i 不太相关。0 只有它的 0 次幂可以定义为 1，但计算起来就会出问题。1 的任何整数次幂都是 1，所以完全和指数没有关系。

那如果放 2 进去当底数呢，它不满足 $\rm{2^i}= 2^{i\ mod\ 2}$ ，所以不太行。

综合下来，只有 -1 作为底数，便于计算，也便于进行逆运算。

容易证明 $\rm{g(n,i)*g(n,j)=(-1)^{|i∩n|+|j∩n|}=(-1)^{|(i\ xor\ j)∩n|}=g(n,i\ xor\ j)}$ 。

依然仿造 $\rm{FMT}$ 考虑增量构造方法。

新加入一位 $i$ ，分选或者不选考虑。

选。和选的集合取并，大小不变。和不选的集合取并，大小 -1 。

不选。和选的集合取并，大小不变。和不选的集合取并，大小也不变。

所以 $i$ 这一位如果 选 ，那会累加到原来的 选 上，累减到原来的 不选 上。

如果 不选，那会累加到原来的选和不选上。

也就是 `int x=f[j+k],y=f[i+j+k];f[i+j+k]=x-y,f[j+k]=x+y `，就有 $\rm{FFT}$ 那种感觉了。

逆变换的话是反过来，移一下项，`f[i+j+k]=(x-y)/2,f[j+k]=(x+y)/2`。

于是就做完了。

```cpp
void FWT_xor(int *f,int n,int op){//op=1 FWT op=-1 IFWT
	for(int i=1;i<n;i<<=1)
		for(int o=i<<1,j=0;j<n;j+=o)
			for(int k=0;k<i;k++){
				int x=f[j+k],y=f[i+j+k];
				f[j+k]=(x+y)%p,f[i+j+k]=(x-y+p)%p;
				if(op==-1)(f[j+k]*=inv2)%=p,(f[i+j+k]*=inv2)%=p;
			}
}
```

--------

感谢阅读。

---

## 作者：ZnPdCo (赞：13)

我们先速通一下前面的部分：

### 按位或

$$
A=\text{merge}(A_0, A_0+A_1)
$$

$$
a=\text{merge}(a_0, a_1-a_0)
$$

### 按位与


$$
A=\text{merge}(A_0+A_1, A_1)
$$

$$
a=\text{merge}(a_0 - a_1, a_1)
$$

### 按位异或

$$
A=\text{merge}(A_0+A_1, A_0-A_1)
$$

$$
a=\text{merge}(\frac{a_0+a_1}{2}, \frac{a_0-a_1}{2})
$$

---

我们设 $c(i,j)$ 是 $a_j$ 对 $A_i$ 的贡献系数。我们可以重新描述 FWT 变换的过程：

$$
A_i = \sum_{j=0}^{n-1} c(i,j) a_j
$$

因为有：

$$
A_iB_i=C_i
$$

所以我们可以通过简单的证明得到：$c(i,j)c(i,k)=c(i,j\odot k)$。其中 $\odot$ 是任意一种位运算。

同时，$c$ 函数还有一个重要的性质，它可以按位处理。

举个例子，我们变换的时候：

$$
A_i = \sum_{j=0}^{n-1} c(i,j) a_j
$$

这么做是比较劣的，我们将其拆分：

$$
A_i = \sum_{j=0}^{(n-1)/2} c(i,j) a_j+\sum_{j=(n-1)/2+1}^{n-1} c(i,j) a_j
$$

考虑前面的式子和后面的式子 $i,j$ 的区别，发现只有最高位不同。

所以我们将 $i,j$ 去除最高位的值为 $i',j'$，并记 $i_0$ 为 $i$ 的最高位。有：

$$
A_i = c(i_0,0)\sum_{j=0}^{(n-1)/2} c(i',j') a_j+c(i_0,1)\sum_{j=(n-1)/2+1}^{n-1} c(i',j') a_j
$$

如果 $i_0=0$，则有：

$$
A_i = c(0,0)\sum_{j=0}^{(n-1)/2} c(i',j') a_j+c(0,1)\sum_{j=(n-1)/2+1}^{n-1} c(i',j') a_j
$$

$i_0=1$ 则有：

$$
A_i = c(1,0)\sum_{j=0}^{(n-1)/2} c(i',j') a_j+c(1,1)\sum_{j=(n-1)/2+1}^{n-1} c(i',j') a_j
$$

也就是说，我们只需要：

$$
\begin{bmatrix}
c(0,0) & c(0,1) \\
c(1,0) & c(1,1)
\end{bmatrix}
$$

四个数就可以完成变换了。我们称这个矩阵为位矩阵。

---

如果我们要进行逆变换，则需要上面的位矩阵的逆矩阵。

若逆矩阵为 $c^{-1}$，可以通过类似操作得到原数：

$$
a_i = \sum_{j=0}^n c^{-1}(i,j) A_j
$$

逆矩阵不一定存在，比如如果有一排 $0$ 或者一列 $0$ 那么这个矩阵就没有逆，我们在构造时需要格外小心。

### 按位或

我们可以构造：

$$
\begin{bmatrix}
1 & 0 \\
1 & 1
\end{bmatrix}
$$

这样满足 $c(i,j)c(i,k)=c(i,j\cup k)$。我们发现，这和我们前面推出的 $A=\text{merge}(A_0, A_0+A_1)$ 一模一样！同理，下面也是一个满足这个条件的矩阵，但我们一般使用上面这个：

$$
\begin{bmatrix}
1 & 1 \\
1 & 0
\end{bmatrix}
$$

虽然下面这个矩阵也满足 $c(i,j)c(i,k)=c(i,j\cup k)$，但这个矩阵存在一排 $0$，不存在逆，所以不合法：

$$
\begin{bmatrix}
0 & 0 \\
1 & 1
\end{bmatrix}
$$

如果我们要进行逆变换，则需要对矩阵求逆，以**最上面**这个矩阵为例，得：

$$
\begin{bmatrix}
1 & 0 \\
-1 & 1
\end{bmatrix}
$$

然后按照顺变换的方法，把逆变换矩阵代入即可。

### 按位与

我们可以构造：

$$
\begin{bmatrix}
1 & 1 \\
0 & 1
\end{bmatrix}
$$

这样满足 $c(i,j)c(i,k)=c(i,j\cap k)$。

逆矩阵：

$$
\begin{bmatrix}
1 & -1 \\
0 & 1
\end{bmatrix}
$$

### 按位异或

我们可以构造：

$$
\begin{bmatrix}
1 & 1 \\
1 & -1
\end{bmatrix}
$$

这样满足 $c(i,j)c(i,k)=c(i,j\oplus k)$。

逆矩阵：

$$
\begin{bmatrix}
0.5 & 0.5 \\
0.5 & -0.5
\end{bmatrix}
$$

## K 维 FWT

其实位运算的本质是对一个 $n$ 维 $\{0,1\}$ 向量的运算。或运算就是每一维取 $\max$。且运算就是每一维取 $\min$。异或运算则是每一维对应相加再 $\bmod 2$。

位运算有个特点：向量的每一位都是独立的。

我们把 $\{0,1\}$ 扩展到 $[0,K)\cap Z$ 也就是扩展到 $K$ 进制，看看会得到什么？

### max 运算

我们将 $\cup$ 运算拓展到 $K$ 进制，定义 $i\cup j$ 表示按位取 $\max$，有：

$$
c(i,j)c(i,k)=c(i,j\cup k)
$$

若 $j=k$，那么上式又是：

$$
c(i,j)c(i,j)=c(i,j)
$$

也就是说，每一行的 $1$ 必定只能在 $0$ 的前面，如果在后面则不合法了。手玩一下可以发现一组合法构造：

$$
\begin{bmatrix}
1 & 0 & 0 & 0 \\
1 & 1 & 0 & 0 \\
1 & 1 & 1 & 0 \\
1 & 1 & 1 & 1
\end{bmatrix}
$$

求逆可得：

$$
\begin{bmatrix}
1 & 0 & 0 & 0 \\
-1 & 1 & 0 & 0 \\
0 & -1 & 1 & 0 \\
0 & 0 & -1 & 1
\end{bmatrix}
$$

### min 运算

我们将 $\cap$ 运算拓展到 $K$ 进制，定义 $i\cap j$ 表示按位取 $\min$，有：

$$
c(i,j)c(i,k)=c(i,j\cap k)
$$

若 $j=k$，那么上式又是：

$$
c(i,j)c(i,j)=c(i,j)
$$

也就是说，每一行的 $1$ 必定只能在 $0$ 的后面，如果在前面则不合法了。手玩一下可以发现一组合法构造：

$$
\begin{bmatrix}
1 & 1 & 1 & 1 \\
0 & 1 & 1 & 1 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

求逆可得：

$$
\begin{bmatrix}
1 & -1 & 0 & 0 \\
0 & 1 & -1 & 0 \\
0 & 0 & 1 & -1 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

前两者用得比较少，用得比较多的是：

### 不进位加法

我们将 $\oplus$ 运算拓展到 $K$ 进制，定义 $i\oplus j$ 表示按位相加再 $\bmod K$，有：

$$
c(i,j)c(i,k)=c(i,j\oplus k)
$$

我们构造 $c(i,j)=\omega_{K}^j$，就可以满足要求了：

$$
\omega_{K}^j\omega_{k}^k=\omega_{K}^{(j+k)\bmod K}
$$

但是每一行都一样矩阵也没有逆，所以我们可以构造 $c(i,j)=\omega_{K}^{(i-1)j}$ 即可。

有下面这个矩阵：

$$
\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & \omega_{K}^1 & \omega_{K}^2 & \cdots & \omega_{K}^{k-1} \\
1 & \omega_{K}^2 & \omega_{K}^4 & \cdots & \omega_{K}^{2(k-1)} \\
1 & \omega_{K}^3 & \omega_{K}^6 & \cdots & \omega_{K}^{3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_{K}^{k-1} & \omega_{K}^{2(k-1)} & \cdots & \omega_{K}^{(k-1)(k-1)}
\end{bmatrix}
$$

此即为 [范德蒙德矩阵](https://en.wikipedia.org/wiki/Vandermonde_matrix)，求逆可得：

$$
\frac{1}{K}\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & \omega_{K}^{-1} & \omega_{K}^{-2} & \cdots & \omega_{K}^{-(k-1)} \\
1 & \omega_{K}^{-2} & \omega_{K}^{-4} & \cdots & \omega_{K}^{-2(k-1)} \\
1 & \omega_{K}^{-3} & \omega_{K}^{-6} & \cdots & \omega_{K}^{-3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_{K}^{-(k-1)} & \omega_{K}^{-2(k-1)} & \cdots & \omega_{K}^{-(k-1)(k-1)}
\end{bmatrix}
$$

如果我们题目给出的模数是存在单位根的，我们就可以简单实现。

---

但是**单位根在模意义下可能不存在**，所以我们考虑扩域，就是人为地定义一个 $x$，满足 $x^K=1$，然后直接把 $x$ 代入计算，这样每个数都是一个关于 $x$ 的 $k-1$ 次多项式。我们只需要在 $\pmod {x^K-1}$ 下计算即可。那么矩阵可以这么表示：

$$
\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & x^1 & x^2 & \cdots & x^{k-1} \\
1 & x^2 & x^4 & \cdots & x^{2(k-1)} \\
1 & x^3 & x^6 & \cdots & x^{3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & x^{k-1} & x^{2(k-1)} & \cdots & x^{(k-1)(k-1)}
\end{bmatrix}
$$

但是这么做可能会存在零因子，也就是**一个数有多种表示方法**，我们无法确定一个数的真实值。

我们考虑不 $\pmod {x^K-1}$ 了，我们 $\bmod$ 分圆多项式 $\Phi_{K}(x)$，他满足 $x$ 的阶为 $k$，且在 $Q$ 上不可约。所以我们定义上面的计算是在 $\pmod {\Phi_{K}(x)}$ 下进行即可。

另一方面，如何求分圆多项式，这一点可以在[因式分解](https://www.luogu.com.cn/problem/P1520)这道题的题解区里了解。这里给出分圆多项式的表：

![](https://znpdco.github.io/blogimage/2024-05-07-FWT/cyclotomic.png)

还有一个问题是，$\bmod \Phi_{K}(x)$ 常数大（因为 $\Phi$ 本身就是一个多项式）。但是因为 $\Phi_{K}(x)\mid x^k-1$，我们只需要在计算时 $\bmod x^k -1$，最后再 $\bmod \Phi_{K}(x)$ 即可。

---

## 作者：Doqe (赞：3)

该篇不会显式出现该题的代码，但可以得到该题的大众做法和一种另类做法，且从一个可能更不跳跃的方向解题。

首先尝试使用分治解决问题。

记 $W(a,b)=c,c_k=\sum_{i\mathop{\mathrm{op}} j=k}a_ib_j$。其中 $\mathop{\mathrm{op}}$ 是位运算。容易发现其具有分配律：$W(ka+b,c)=kW(a,c)+W(b,c)$，$W(a,kb+c)=kW(a,b)+W(a,c)$。

使用分治的一个契机是，可以将长度 $2^n$ 的 $W(a,b)$ 求解化为若干个长度 $2^{n-1}$ 的 $W(a',b')$ 求解。最后长度为 $2^0$ 是容易的。最后使用 $T(n)=rT(n-1)+O(2^n)$ 分析复杂度。

我们最终要求 $W(a,b)$。设 $a^0$ 表示下标最高位为 $0$ 的所有 $a_i$ 按顺序排列（下标从 $0$ 开始）。

比如如果 $a=(1,2,3,4)$，那么 $a^0=(1,2),a^1=(3,4)$。$a^1,b^0,b^1,c^0,c^1$ 以此类推。

我们最后要求 $c^0,c^1$，枚举 $i,j$ 的最高位 $x,y$，需要满足 $x\mathop{\mathrm{op}}y=0$ 的贡献到 $c^0$，$=1$ 贡献到 $c^1$。

于是 $c^t=\sum_{x\mathop{\mathrm{op}}y=t}W(a^x,b^y)$。

注意我们递归调用的是乘法，也就是 $W$，我们需要尽可能减少 $W$ 操作的使用。

比如对于或操作，我们有：

$$c^0=W(a^0,b^0),c^1=W(a^1,b^0)+W(a^1,b^1)+W(a^0,b^1)$$

直接做是 $4$ 次乘法，所以复杂度约为 $O(r^n)=O(4^n)$，和暴力无异。

但我们有 $c^0+c^1=W(a^0,b^0)+W(a^1,b^0)+W(a^0,b^1)+W(a^1b^1)=W(a^0+a^1,b^0+b^1)$。

计算 $c^0$ 使用一个 $W$，计算 $c^1$ 使用总的 $W$ 减去 $c^0$，则做到了 $r=2$。于是有 $O(2^nn)$ 的复杂度，根据主定理分析可得。

对于与操作，我们有：

$$c^1=W(a^1,b^1),c^0=W(a^1,b^0)+W(a^0,b^0)+W(a^0,b^1)$$

其和或运算是类似的。

对于异或操作，我们有：

$$c^0=W(a^1,b^1)+W(a^0,b^0),c^1=W(a^1,b^0)+W(a^0,b^1)$$

全局仍然是可以算的。但是如果强行单独计算 $c^0$ 或者 $c^1$ 顶多做到 $O(3^n)$。

考虑一下 $c^1-c^0=W(a^0-a^1,b^0-b^1)$，于是我们也可以解出来 $c^0,c^1$，复杂度 $O(2^nn)$。

---

但我们知道这题的做法不只有分治求解。例如一种计算 OR 运算的方法是：FMT（高维前缀和），按位乘法，IFMT（高维差分）。

这里首先给出上述分治乘法的形式化的算法流程：

设 $W_n(a,b)$ 表示解决 $2^n$ 范围的计算，允许调用 $W_{n-1}$。

我们记 $a^0,a^1$，$b^0,b^1$。然后记 $d_i=W_{n-1}(\sum_j A_{i,j}a^i,\sum j B_{i,j}b^i)$。

最后记 $c^i=\sum C_{i,j}d_j$。我们在上述分治乘法构造中获得了对应的 $A,B,C$。

注意到这里 $d_j$ 的下标范围是 $[0,r)$。

我们不加证明地考虑如下算法（当 $r$ 和进制数 $2$ 相同），不加证明的原因是因为：上面或运算的构造其实就是前缀和状物。而我们可以使用高维前缀和（FMT）解决，进而依据此推出通式。

```cpp
const int R=2;
void trans(int a[],int A[2][2])
{
    static int x[2],y[2];
    for(int i=0;i<n;++i)
        for(int j=0;j<(1<<n);++j)
            if(!(j>>i&1))
            {
                x[0]=a[j],x[1]=a[j|(1<<i)];
                y[0]=y[1]=0;
                for(int k=0;k<R;++k)
                    for(int t=0;t<2;++t)
                        y[k]+=A[k][t]*x[t];
                a[j]=y[0],a[j|(1<<i)]=y[1];
            }
}
int main()
{
    //read a,b
    trans(a,A);
    trans(b,B);
    for(int i=0;i<(1<<n);++i)c[i]=a[i]*b[i];
    trans(c,C);
    //output c
}
```

可以证明上述方式（枚举每一维，按住这一维，枚举其他维度）是和分治乘法正确性相同的。只需证明二维情况即可，因为这样就可以不断压缩维度（通过若干一维的操作合并出二维的操作，随后合并到整体的操作）。

如果不是很关注正确性和上述两种做法的关联，非常不建议去证明。但是可以尝试口胡。

---

最后探讨一下 $A,B,C$ 满足构造的条件。

不妨考虑一维情况，记 $A^i=[i=x]$，$B^j=[j=y]$。考虑 $C^z$。

$$C^z=[x\mathop{\mathrm{op}}y=z]=\sum C_{z,i}A_{i,x}B_{i,y}$$

就是如此。我们还可以使用高斯消元的思想。隐去 $C$。

那么如果矩阵 $M^i$ 满足 $M^i_{x,y}=A_{i,x}B_{i,y}$，最后可以线性组合出来 $O^i$ 满足 $[O^i]_{x,y}=[x\mathop{\mathrm{op}}y=i]$。

其几乎是充要的（不考虑在特殊的有限域下运算的话），对于任意情形可以通过 $W$ 的线性性拆成多个上述例子解决。

---

## 作者：__O_v_O__ (赞：0)

## 算法介绍

我们知道 FFT 可以在 $O(n\log n)$ 的时间内求解 $C_k=\sum\limits_{i+j=k}A_i\times B_j$。而类似的，我们将求和符号中的加号换成其余的位运算符号，即得到了 FWT。

FWT 可以在 $O(n\log n)$ 时间内求出：

- $C_k=\sum\limits_{i|j=k}A_i\times B_j$

- $C_k=\sum\limits_{i\&j=k}A_i\times B_j$

- $C_k=\sum\limits_{i\oplus j=k}A_i\times B_j$

与 FFT 相似：先对 $A,B$ 做正变换，然后两个数组按位置做点积，最后对得到的数列做逆变换。

于是我们需要关注的点就是**正变换**、**逆变换**怎么做。

以下记序列 $A$ 经 $\operatorname{FWT}$ 变换后的序列为 $A^{'}$ 或 $\operatorname{FWT}(A)$。

### 或运算

#### 正变换

我们让 $A^{'}_i$ 等于所有是 $i$ 的子集的下标 $j$ 的系数和 $\sum\limits_{j\subseteq i}A_j$。

考虑乘积的下标 $k$ 有：

$\begin{aligned}A^{'}_k\cdot B^{'}_k&=(\sum\limits_{i\subseteq k}a_i)(\sum\limits_{j\subseteq k}b_j)\\&=\sum\limits_{i\subseteq k}\sum\limits_{j\subseteq k}a_ib_j\\&=\sum\limits_{(i\cup j)\subseteq k}a_ib_j=C^{'}_k\end{aligned}$

那么 $\operatorname{FWT}(C)=\operatorname{FWT}(A)\cdot\operatorname{FWT}(B)$。

如何求出序列 $A^{'}$ 呢？如果使用暴力，复杂度 $O(n^2)$，需要优化。

- 对于多项式计算的一个常规套路，就是考虑分治。具体来说，当 $2$ 个区间长度为 $\frac{n}{2}$ 的都求解出来之后，合并得到一个区间长度为 $n$ 的答案。

我们引入多项式 $A_0,A_1$，分别表示 $A$ 的前一半和后一半，即下标二进制最高位分别为 $0$ 和 $1$ 的。

假设已经求解出了 $\operatorname{FWT}(A_0),\operatorname{FWT}(A_1)$，那么如何合并求解 $\operatorname{FWT}(A)$ 呢？

在递归过程中，我们眼中 $A_0$ 和 $A_1$ 的下标都只是 $0\sim \dfrac{n}{2}-1$，但是将两个序列合并后，一些下标就发生变化，下面分别考虑 $A_0$ 与 $A_1$：

- $\operatorname{FWT}(A_0)$ 对应的下标没有任何变化，所以变成 $\operatorname{FWT}(A)$，这部分对应的值也没有任何变化。即 $\operatorname{FWT}(A)[0:\dfrac{n}{2}]=\operatorname{FWT}(A_0)$。

- $\operatorname{FWT}(A_1)$ 中，对于一个二进制为 `1___` 的下标 $k$，它在递归时已经统计了形如 `1___` 的子集，合并后它多出了形如 `0___` 的子集需要再统计。而这个信息，在 $\operatorname{FWT}(A_0)_{k-\frac{n}{2}}$ 位置已经计算，也就是说，在位置偏移 $\frac{n}{2}$ 的下标，恰好就有我们要的信息，直接多项式加法即可。所以 $\operatorname{FWT}(A)[\dfrac{n}{2}:n]=\operatorname{FWT}(A_0)+\operatorname{FWT}(A_1)$。

最后拼接起来有：

$$\operatorname{FWT}(A)=[\operatorname{FWT}(A_0),\operatorname{FWT}(A_0)+\operatorname{FWT}(A_1)]$$

#### 逆变换

与正变换类似，依旧考虑分治。

现在，逆变换的含义是扣除某一个位置的子集。

分 $A_0$ 与 $A_1$ 考虑：

- $\operatorname{UFWT}(A_0)$ 的下标，显然已经完全扣除。

- $\operatorname{UFWT}(A_1)$ 中，对于一个二进制为 `1___` 的下标 $k$，它已经扣除了形如 `1___` 的子集，还剩 `0___` 的子集需要扣除。这些信息在 $\operatorname{UFWT}(A_0)_{k-\frac{n}{2}}$ 中已经计算，做多项式减法即可。

于是最终有：

$$\operatorname{UFWT}(A)=[\operatorname{UFWT}(A_0),\operatorname{UFWT}(A_1)-\operatorname{UFWT}(A_0)]$$

我们使用 $O(n\log n)$ 的复杂度解决了问题。

### 与运算

我们让 $A^{'}_i$ 等于所有是 $i$ 的超集的下标 $j$ 的系数和 $\sum\limits_{i\subseteq j}A_j$。

同或运算考虑方法，得到正变换与逆变换法则：

$$\operatorname{FWT}(A)=[\operatorname{FWT}(A_0)+\operatorname{FWT}(A_1),\operatorname{FWT}(A_1)]$$

$$\operatorname{UFWT}(A)=[\operatorname{UFWT}(A_0)-\operatorname{UFWT}(A_1),\operatorname{UFWT}(A_1)]$$

### 异或运算

异或比前面两个运算稍复杂。

定义 $x\circ y=\operatorname{popcnt}(x\&y)\bmod 2$。

可以发现，$(x\circ y)\oplus(x\circ z)=x\circ(y\oplus z)$，这个性质是 $\operatorname{FWT}$ 构造的关键。

构造 $A^{'}_i=\sum\limits_{i\circ j=0}A_j-\sum\limits_{i\circ j=1}A_j$。

考虑乘积的下标 $k$：

$\begin{aligned}A^{'}_k\cdot B^{'}_k&=(\sum\limits_{k\circ i=0}A_i-\sum\limits_{k\circ i=1}A_i)(\sum\limits_{k\circ j=0}B_j-\sum\limits_{k\circ j=1}B_j)\\&=(\sum\limits_{k\circ i=0}\sum\limits_{k\circ j=0}A_iB_j+\sum\limits_{k\circ i=1}\sum\limits_{k\circ j=1}A_iB_j)-(\sum\limits_{k\circ i=0}\sum\limits_{k\circ j=1}A_iB_j+\sum\limits_{k\circ i=1}\sum\limits_{k\circ j=0}A_iB_j)\\&=\sum\limits_{k\circ(i\oplus j)=0}A_iB_j-\sum\limits_{k\circ(i\oplus j)=1}A_iB_j=C^{'}_k\end{aligned}$

那么它仍然满足 $\operatorname{FWT}(C)=\operatorname{FWT}(A)\cdot\operatorname{FWT}(B)$。

考虑正变换：

- $\operatorname{FWT}(A_0)$ 中，对于一个下标 $k$：原本的下标，最高位新增了 $0$，因为 $0\cap 0=0$ 所以并不会改变 $\operatorname{popcnt}$ 的奇偶性，这部分保留。还得计算 $[n/2,n)$ 这些下标和它的关系，因为 $0\cap 1=0$，所以也不会改变原先的奇偶性，只需要再累加上 $\operatorname{FWT}(A_1)_{k+\frac{n}{2}}$ 即可。于是 $\operatorname{FWT}(A)[0,n/2]=\operatorname{FWT}(A_0)+\operatorname{FWT}(A_1)$。

- $\operatorname{FWT}(A_1)$ 同理。因为 $1\cap 0=0,1\cap 1=1$，所以前半段奇偶性不变，改变后半段奇偶性。于是 $\operatorname{FWT}(A)[n/2,n]=\operatorname{FWT}(A_0)-\operatorname{FWT}(A_1)$。

最后拼接起来有：

$$\operatorname{FWT}(A)=[\operatorname{FWT}(A_0)+\operatorname{FWT}(A_1),\operatorname{FWT}(A_0)-\operatorname{FWT}(A_1)]$$

类似模仿在“或运算”那一节中的考虑方法，容易推导出 $\operatorname{UFWT}$：

$$\operatorname{UFWT}(A)=[\dfrac{\operatorname{UFWT}(A_0)+\operatorname{UFWT}(A_1)}{2},\dfrac{\operatorname{UFWT}(A_0)-\operatorname{UFWT}(A_1)}{2}]$$

至此，异或运算已经解决。

## 代码实现

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=998244353,ny=499122177;
int n,A[500001],B[500001],c[500001];
int a[500001],b[500001];
void or_(int *f,int T=1){
	for(int i=2;i<=n;i<<=1){
		int o=i>>1;
		for(int j=0;j<n;j+=i)
			for(int k=0;k<o;k++)
				f[j+k+o]=(f[j+k+o]+f[j+k]*T%mo)%mo;
	}
}
void an_(int *f,int T=1){
	for(int i=2;i<=n;i<<=1){
		int o=i>>1;
		for(int j=0;j<n;j+=i)
			for(int k=0;k<o;k++)
				f[j+k]=(f[j+k]+f[j+k+o]*T%mo)%mo;
	}
}
void xo_(int *f,int T=1){
	for(int i=2;i<=n;i<<=1){
		int o=i>>1;
		for(int j=0;j<n;j+=i)
			for(int k=0;k<o;k++){
				f[j+k]=(f[j+k]+f[j+k+o])%mo;
				f[j+k+o]=((f[j+k]-2*f[j+k+o])%mo+mo)%mo;
				f[j+k]=f[j+k]*T%mo;
				f[j+k+o]=f[j+k+o]*T%mo;
			}
	}
}
void in(){
	for(int i=0;i<n;i++)
		a[i]=A[i],b[i]=B[i];
}
void ca(){
	for(int i=0;i<n;i++)
		c[i]=a[i]*b[i]%mo;
}
void ou(){
	for(int i=0;i<n;i++)
		cout<<c[i]<<' ';
	cout<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n,n=(1<<n);
	for(int i=0;i<n;i++)cin>>A[i];
	for(int i=0;i<n;i++)cin>>B[i];
	in(),or_(a),or_(b),ca(),or_(c,mo-1),ou();
	in(),an_(a),an_(b),ca(),an_(c,mo-1),ou();
	in(),xo_(a),xo_(b),ca(),xo_(c,ny),ou();
	return 0;
}
```

---

