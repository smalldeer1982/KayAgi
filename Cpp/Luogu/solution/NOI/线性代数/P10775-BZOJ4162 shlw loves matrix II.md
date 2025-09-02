# BZOJ4162 shlw loves matrix II

## 题目背景

**请注意：本题不是矩阵快速幂模板题。**

## 题目描述

给定矩阵 $M$，计算 $M^n$，并将其中每一个元素对 $10^9+7$ 取模输出。

## 说明/提示

对于 $100\%$ 的数据，$1\leq n\leq 2^{10^4}$，$1\leq k\leq 50$，$0\leq M_{i,j}<10^9+7$。

## 样例 #1

### 输入

```
010 3
5 9 5
5 4 0
8 8 8```

### 输出

```
110 121 65
45 61 25
144 168 104```

# 题解

## 作者：Galois_Field_1048576 (赞：7)

本文不铺陈线性代数基础以及后续做法，只讨论作为本题的最重要一步——Cayley-Hamilton 定理的证明。所有证明都并非我的原创。

**定理 (Cayley-Hamilton).** 设 $R$ 是交换环，$\varphi$ 是有限生成自由 $R$-模上的自同态，其特征多项式为 $p(\lambda) = \det(\lambda \mathrm{id} - \varphi) \in R[X]$，则 $p(\varphi) = 0$（由于 $\mathrm{End}(M)$ 是 $R$-代数）。

不少证明并不能涵摄 $R$ 是全部交换环的情形。

## (0) 错误的证明
$$
p(\lambda) = \det(\lambda \mathrm{id} - \varphi) \implies p(\varphi) = \det(\varphi \mathrm{id} - \varphi) = \det(0) = 0.
$$

这个证明的错误在于：$p(\varphi)$ 本应属于 $\mathrm{End}(M)$，但在这个证明中最后一项是行列式的结果，属于 $R$。

## (1) 直接、简洁的证明
考虑 $\varphi_\lambda$ 为 $\lambda \mathrm{id} - \varphi$，它是 $M[\lambda] = R[\lambda] \underset{R}\otimes M$ 的自同态。这样，根据初等线性代数，
$$
\varphi_\lambda^{\rm adj} \varphi_\lambda = p \mathrm{id}.
$$
这样，
$$
\begin{aligned}
p(\varphi) v &= \left.p(x)v\right\rvert_{x = \varphi} \\
&= \left.\varphi_\lambda^{\rm adj} (xv - \varphi v)\right\rvert_{x = \varphi} \\
&= 0.
\end{aligned}
$$

这个证明曾风靡一时，但实际上观看它的实质就会发现我们只是变了个戏法然后把 $\varphi$ 带了进去。这是如何成立的？解释它可能要花一些时间。我们做的事实质上是把 $p$ 在环 $\mathrm{End}(M)[\lambda]$ 上进行了一个因式分解：分解为 $\varphi_\lambda^{\rm adj} \varphi_\lambda$。这里它在 $\mathrm{End}(M[\lambda])$ 上是复合的关系，而到了 $\mathrm{End}(M)[\lambda]$ 就成了乘积。

然后我们实际上在非交换环 $\mathrm{End}(M)$ 上操作要格外小心，因为实际上 $f_L(x)g_L(x) = (fg)_L(x)$ 并不成立，其中 $L$ 代表带入多项式时每一项形如 $a_kx^k$，而 $R$ 代表带入多项式时每一项形如 $x^ka_k$。但是，我们还是有单侧因式定理：
$$
f_L(x) = 0 \implies (fg)_L(x) = 0, g_R(x) = 0 \implies (fg)_R(x) = 0.
$$
我们用到的就是后一条。$\varphi_\lambda$ 从右面带入 $\varphi$ 是 $0$，因此 $\varphi_\lambda^{\rm adj} \varphi_\lambda$ 从右面带入 $\varphi$ 也是 $0$。

我们还要说明它和前面的伪证到底有什么区别。区别在于：
$$
\mathrm{ev}_\varphi \circ \det(\varphi_\lambda)
$$
是复合的关系。第一个证明将它与
$$
\det \circ\ \mathrm{ev}_\varphi(\varphi_\lambda)
$$
混淆。而第二个证明通过将 $\mathrm{ev}_\varphi \circ \det$ 整体转化得到了乘积的形式，才完成了证明。

现在的线性代数课本很少涉及这个证明，就是因为它带来的此种误会。

## (2) 大力出奇迹
通过计算矩阵元直接证明结果。[证明在这个论文集的 32-36 页。](https://ssmr.ro/gazeta/gma/2014/gma3-4-2014-continut.pdf)

## (3) 对维度归纳
设 $M \simeq R^n$ 并 $R$ 是域。注意到，当 $\operatorname{span}\{\varphi^k v : 0 \le k < n\} = M$ 时，$v, \varphi v, \dots, \varphi^n v$ 线性相关，导出存在 $n$ 次多项式 $f$ 使得 $f(\varphi) = 0$。在 $\varphi^k v$ 这组基下，$\varphi$ 的表示矩阵是 $f$ 的友阵。也就是说，$p = f$，$p(\varphi) = 0$。

现在对 $n$ 归纳。设任取 $v \in M \setminus \{0\}$，并定义 $m = \dim W, W = \{\varphi^k v : 0 \le k < n\}$。如果 $m = n$，则归结到上一段的内容，否则将 $\varphi^k v~(0 \le k < m)$ 扩充为一组基 $\mathfrak B$。在这组基下，$\varphi$ 是分块上三角的
$$
M = \begin{pmatrix} A & B \\ 0 & C \end{pmatrix},
$$
（这是因为 $\varphi(\varphi^k v) \in W$。）根据归纳假设，$p_A(A) = 0, p_C(C) = 0$。这样我们有
$$
p_{M}(M) = p_A(M) p_C(M) = \begin{pmatrix} 0 & * \\ 0 & * \end{pmatrix} \begin{pmatrix} 0 & 0 \\ * & * \end{pmatrix} = 0.
$$

利用不变子空间可以将其进行改写。并无本质不同，略去。

## (4) 扩充到多项式环去
设 $R$ 是域，$R' = \mathrm{Sym}(\mathrm{End}(M)^*)$，其中 $V^*$ 是 $V$ 的对偶空间，$\mathbb F = \mathrm{Frac}(R'), \mathbb K = \overline {\mathbb F}$，$M' = M \underset R \otimes R'$。这样，我们有自然的 $M'$ 的自同态：$\varphi(v \otimes f) = f(v)$。具体而言，若 $n = \dim M$，$R'$ 是 $R$ 上有 $n^2$ 个变元 $X_{ij}$ 的多项式环，而 $\varphi$ 是在说 $\varphi_{ij} = X_{ij}$，作为 $R'$ 上的 $n \times n$ 矩阵。直觉上，$\varphi$ 给出了“一般”的算子，安插 $X_{ij}$ 的值可以得到特殊的算子。

现在我们证明，$\varphi$ 在 $\mathbb K$ 上有 $n$ 个不同的特征值：否则，考虑 $\varphi$ 的特征多项式 $p$，我们有判别式 $\Delta(p) = 0$。这样，设 $\psi \in \mathrm{End}(M)$，其特征多项式为 $q$，定义代数同态 $c : R' \to R$ 为 $F \mapsto F(\psi)$，它满足 $c(\varphi) = \psi$。那么 $\Delta(q) = \Delta\circ\mathrm{charpoly}\circ c(\varphi) = c \circ \Delta(p) = 0$，于是所有的算子都不可能有 $n$ 个不同的特征值，这是显然不对的。所以断言成立，于是 $\varphi$ 的 Cayley-Hamilton 定理成立。

仍然取 $\psi \in \mathrm{End}(M)$，其特征多项式为 $q$，以及上述构造的映射 $c$，则
$$
q(\psi) = c(p(\varphi)) = 0.
$$

这是我最喜欢的证明。

## (5) 一个常见的《高等代数》书的证明
假设 $R$ 是域，把 $M$ 当成 $M \underset R \otimes \overline R$（例如，$R = \mathbb C$，这是《高等代数》书中常考虑的）。通过归纳法可以证明 $\varphi$ 在适当的基下是一个上三角阵 $A$。我们曾经计算过
$$
p_{M}(M) = p_A(M) p_C(M) = \begin{pmatrix} 0 & * \\ 0 & * \end{pmatrix} \begin{pmatrix} 0 & 0 \\ * & * \end{pmatrix} = 0, M = \begin{pmatrix} A & * \\ O & C \end{pmatrix}.
$$
所以 Cayley-Hamilton 定理对所有的上三角阵成立，进而对所有复矩阵成立。

## (6) 拓扑学证明
假设 $R$ 是整环，$\mathbb F = \mathrm{Frac}(R), \mathbb K = \overline {\mathbb F}, R' = \mathbb K[X_{ij} : 0 \le i, j < n]$，在 $\mathbb K^{n^2}$ 作为环上装配 Zariski 拓扑，则任意的 $\mathbb K^{n^2} \to \mathbb K$ 的多项式函数 $f \in R'$ 是连续的。考虑特征多项式，作为矩阵元的多项式，有 $\mathrm{charpoly} \in R'[X]$，这样考虑 $P = \Delta(\mathrm{charpoly}) \in R'$（$\Delta$ 表示判别式）。考虑 $U = P^{-1}(0)^\complement$，它是稠密的开集。

好，我们考虑一下 $P(X_{ij}) = 0$ 的意义：它表示矩阵 $X$ 的特征多项式有重根，因此 $P(X_{ij}) \ne 0$ 代表 $X$ 的特征多项式无重根，因此可以推出 $X$ 是可对角化的，符合 Cayley-Hamilton 定理。这样，根据稠密性，所有的矩阵符合 Cayley-Hamilton 定理。

## (7) 复分析证明
自然要假设 $R = \mathbb C$。设 $C$ 是包含 $0$ 的简单闭曲线，则
$$
\begin{aligned}
p &= \sum_{k=0}^n \dfrac{x^k}{\tau \mathrm i} \oint_C \dfrac{p(\zeta)}{\zeta^{k+1}} \mathrm d\zeta \\
p(\varphi) &= \sum_{k=0}^n \dfrac{\varphi^k}{\tau \mathrm i} \oint_C \dfrac{p(\zeta)}{\zeta^{k+1}} \mathrm d\zeta \\
&= \dfrac 1{\tau \mathrm i} \oint_C \dfrac{p(\zeta)}{\zeta} \sum_{k=0}^{n} (\zeta^{-1} \varphi)^k \mathrm d\zeta \\
&= \dfrac 1{\tau \mathrm i} \oint_C p(\zeta) (\zeta \mathrm{id} - \varphi)^{-1} (\mathrm {id} - \zeta^{-n-1} \varphi^{n+1}) \mathrm d\zeta \\
&= \dfrac 1{\tau \mathrm i} \oint_C (\zeta \mathrm{id} - \varphi)^{\rm adj} (\mathrm {id} - \zeta^{-n-1} \varphi^{n+1}) \mathrm d\zeta \\
&= \dfrac 1{\tau \mathrm i} \oint_C (\zeta \mathrm{id} - \varphi)^{\rm adj} \mathrm d\zeta + \dfrac 1{\tau \mathrm i} \oint_C (\zeta \mathrm{id} - \varphi)^{\rm adj} \zeta^{-n-1} \varphi^{n+1} \mathrm d\zeta.
\end{aligned}
$$
第一项的每个矩阵元为 $\le n-1$ 次多项式，根据 Cauchy 积分公式为 $0$ 矩阵，第二项的每个矩阵元均为 $\le -2$ 次分式，积分为 $0$ 矩阵。

复分析还有其它的证明。不再赘述。

---

## 作者：gxy001 (赞：5)

~~这不就是矩阵快速幂模板题吗~~

求特征多项式的方法可以看[模板题](https://www.luogu.com.cn/problem/P7776)，当然这题其实不需要 $O(k^3)$ 的求解方法，我们可以用 $O(k^4)$ 的笨办法，代入 $k+1$ 个 $\lambda$，求出行列式然后插值。

我们知道，由 Cayley-Hamilton 定理，矩阵的特征多项式是矩阵的零化多项式。设矩阵的特征多项式为 $f(\lambda)$，我们有 $f(M)=O$。

于是，我们设 $g(x)=x^n\bmod f(x)$，那么 $M^n=g(M)$，而 $g$ 是一个 $k-1$ 次多项式，这也意味着，我们只要求出 $M^0,M^1,\cdots,M^{k-1}$ 就可以求出 $g(M)$ 了，这部分时间复杂度 $O(k^4)$。

关于 $g$ 怎么求，我们使用快速幂求 $x^n$，过程中对 $f(x)$ 取模即可，多项式取模用暴力 $O(k^2)$ 就好，这部分时间复杂度为 $O(k^2\log n)$。

总复杂度为 $O(k^4+k^2\log n)$。

```cpp
#include<iostream>
#include<ranges>
#include<string>
using std::cin,std::cout;
int const mod=1e9+7;
int pow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return res;
}
int n,a[60][60],f[60][60],m[60],p[60],q[60];
void mul(int *x,int *y){
	static int p[110];
	int lim=2*n-1;
	for(int i=0;i<lim;i++) p[i]=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			p[i+j]=(p[i+j]+1ll*x[i]*y[j])%mod;
	for(int i=lim-1;i>=n;i--){
		int u=(mod-p[i])%mod;
		for(int j=0;j<=n;j++)
			p[i-j]=(p[i-j]+1ll*u*m[n-j])%mod;
	}
	for(int i=0;i<n;i++) x[i]=p[i];
}
struct mat{
	int a[60][60];
	mat():a(){}
	int* operator [](int x){return a[x];}
	const int* operator [](int x)const{return a[x];}
	mat operator *(int x)const{
		mat res;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) res[i][j]=1ll*a[i][j]*x%mod;
		return res;
	}
	friend mat operator +(mat const &a,mat const &b){
		mat res;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) res[i][j]=(a[i][j]+b[i][j])%mod;
		return res;
	}
	friend mat operator *(mat const &a,mat const &b){
		mat res;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++)
					res[i][k]=(res[i][k]+1ll*a[i][j]*b[j][k])%mod;
		return res;
	}
}ans,c,w;
int main(){
	std::string s;
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>s>>n;
	for(int i=1;i<=n;i++)	
		for(int j=1;j<=n;j++)
			cin>>a[i][j],c[i][j]=a[i][j];
	for(int i=1;i<n;i++){
		int k=0;
		for(int j=i+1;j<=n;j++)if(a[j][i]){k=j;break;}
		if(k){
			if(k!=i+1){
				std::swap(a[i+1],a[k]);
				for(int j=1;j<=n;j++) std::swap(a[j][i+1],a[j][k]);
			}
			int r=a[i+1][i];
			for(int j=1;j<=n;j++) a[j][i+1]=1ll*a[j][i+1]*r%mod;
			r=pow(r,mod-2);
			for(int j=i;j<=n;j++) a[i+1][j]=1ll*a[i+1][j]*r%mod;
			for(int j=i+2;j<=n;j++) if(a[j][i]){
				int u=a[j][i];
				for(int k=1;k<=n;k++) a[k][i+1]=(a[k][i+1]+1ll*u*a[k][j])%mod;
				u=(mod-u)%mod;
				for(int k=i;k<=n;k++) a[j][k]=(a[j][k]+1ll*u*a[i+1][k])%mod;
			}
		}
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++) f[i][j]=(mod-1ll*a[i][i]*f[i-1][j]%mod)%mod;
		for(int j=0;j<i;j++) f[i][j+1]=(f[i][j+1]+f[i-1][j])%mod;
		int p=1;
		for(int j=i-1;j;j--){
			p=(mod-1ll)*p%mod*(mod-a[j+1][j])%mod;
			int w=1ll*p*(mod-a[j][i])%mod;
			for(int k=0;k<j;k++) f[i][k]=(f[i][k]+1ll*w*f[j-1][k])%mod;
		}
	}
	for(int i=0;i<=n;i++) m[i]=f[n][i];
	p[0]=1;
	if(n==1) q[0]=(mod-m[0])%mod;else q[1]=1;
	for(auto u:s|std::views::reverse){
		if(u=='1') mul(p,q);
		mul(q,q);
	}
	for(int i=1;i<=n;i++)w[i][i]=1;
	for(int i=0;i<n;i++){
		ans=ans+w*p[i];
		w=w*c;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cout<<ans[i][j]<<" \n"[j==n];
	return 0;
}
```

---

## 作者：TernaryTree (赞：4)

妈妈，我也想入门线性代数。

当你点开这题，给你扔了个 $n$ 阶矩阵 $A$，又扔了个数 $k$，让你算 $A^k$，一眼矩阵快速幂板子题，然后我们就喜闻乐见地看到 $k\le 2^{10^4}$，这咋办，做不了啊？？然后你开了题解，发现第一句话特征多项式把你迅速劝退。事实上并没有这么难，我写点入门东西，也方便自己看看。

假设我们现在有一个矩阵 $A$。定义它的特征多项式是：

$$p_A(x)=\det(I_nx-A)$$

其中 $I_n$ 即单位矩阵。注意到 $n$ 阶矩阵的特征多项式是 $n$ 次的，这可以参考行列式的定义。

考虑得到了这个 $p_A(x)$，对计算有什么好处。

引出一个定理：Cayley-Hamilton 定理，简称 CH 定理。它告诉我们一个矩阵的特征多项式同时是它的零化多项式，用人话说，就是 $p_A(A)$ 是全 $0$ 矩阵。

你会发现这样一件事情：把 $f(x)=x^k$ 化成 $p_A(x)q(x)+r(x)$ 的形式，即做了多项式带余除法，那么将 $A$ 代进去，只会得到 $r(x)$，因为 $p_A(A)=0$！！！而 $r(x)$ 是不超过 $n-1$ 次的，我们只要选择一种你喜欢的方式暴力计算，这部分就能做到 $\Theta(n^4)$ 了！那么我们还有两个问题需要解决：

- 如何求出 $p_A(x)$：
  
  暴力在矩阵上维护多项式显然行不通。~~翻看洛谷模板题库发现有一道题叫做“特征多项式”然后苦学半天三方算法，最后没看懂，睡着了。~~ 由于结果是 $n$ 次多项式，我们代入 $n+1$ 个点值计算行列式，再[拉插插出系数](https://www.luogu.com.cn/article/qdz3thhq)即可，这部分 $\Theta(n^4)$。

- 如何求出 $r(x)$：

  对 $x$ 快速幂，快速幂的过程中暴力对 $p_A(x)$ 取模即可。这部分 $\Theta(n^2\log n)$。

于是这题就做完了，并不需要任何 $\ge$ 紫的算法。[Code](https://www.luogu.com.cn/paste/opn5goho)。

---

