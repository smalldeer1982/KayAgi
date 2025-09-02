# 【模板】Pfaffian

## 题目背景

称一个长度为 $2n$ 的排列 $\pi$ 是完美匹配，当且仅当其满足
- $\forall 1\le i\le n,\pi_{2i-1}<\pi_{2i}$
- $\forall 1\le i< n,\pi_{2i-1}<\pi_{2i+1}$

记 $\textup{inv }\pi$ 表示 $\pi$ 的逆序对数，$\textup{sgn }\pi=(-1)^{\textup{inv }\pi}$，$\mathfrak{M}_{2n}$ 表示全体长度为 $2n$ 的完美匹配构成的集合。
	
令 $\mathbf{A}=(a_{i,j})_{1\le i<j\le 2n}$ 是一个反对称矩阵，定义 $\mathbf{A}$ 的 $\text{Pfaffian}$ 为
$$\textup{Pf}(\mathbf{A})=\sum\limits_{\pi\in\mathfrak{M}_{2n}}(\textup{sgn }\pi)\prod\limits_{i=1}^{n}a_{\pi(2i-1),\pi(2i)}$$

## 题目描述

给定偶数 $n$ 与反对称矩阵 $\mathbf{A}=(a_{i,j})_{1\le i<j\le n}$，求 $\textup{Pf}(\mathbf{A})$ 对 $10^9+7$ 取模的结果。

## 说明/提示

对于 $30\%$ 的数据，$n\le 10$。

对于 $100\%$ 的数据，$2\leq n\le 500$，$0\le a_{i,j}<10^9+7$。

## 样例 #1

### 输入

```
4
1 2 3
4 5
6```

### 输出

```
8```

# 题解

## 作者：IdnadRev (赞：16)

由于 Pfaffian 值满足性质 $\operatorname{Pf}(A)=\det(Q)\operatorname{Pf}(Q^TAQ)$，对于初等行列变换矩阵 $Q$（除了乘常数），我们有 $\operatorname{Pf}(A)=\operatorname{Pf}(Q^TAQ)$。类似行列式求值，这为我们提供了一个使用合同变换对 $A$ 消元以求出 Pfaffian 值的算法——

从 $1$ 到 $n-1$ 枚举每个奇数 $i$，若 $A_{i,i+1}$ 处为零，我们可以找到某个非零位置 $A_{p,i+1}$，并同时交换第 $p$ 列与第 $i+1$ 列，第 $p$ 行与第 $i+1$ 行（因为变换形如 $A\rightarrow Q^TAQ$）。

接下来我们用第 $i+1$ 列来消去所有 $A_{i,p},p>i+1$ 的值，只需以 $-\frac{A_{i,p}}{A_{i,i+1}}$ 的系数，将第 $i+1$ 列加到第 $p$ 列，将第 $i+1$ 行加到第 $p$ 行。

对于最终的反对称矩阵 $A$，每个奇数 $i$ 都满足，$A$ 第 $i$ 行的第 $i+2$ 列到第 $n$ 列均为零（由反对称性，对第 $i$ 列亦然），此时 $\operatorname{Pf}(A)=\prod A_{2k-1,2k}$。

具体实现中，我们可以只维护矩阵主对角线上方的元素，但是需谨慎处理对称产生的正负号。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=505,mod=1000000007;
int n,ans,flg;
int a[maxn][maxn];
int ksm(int a,int b) {
	int res=1;
	while(b) {
		if(b&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		for(int j=i+1; j<=n; j++)
			scanf("%d",&a[i][j]);
	for(int i=1; i<=n; i+=2) {
		int p=i+1;
		for(int j=i+2; j<=n; j++)
			if(a[i][j]) {
				p=j;
				break;
			}
		if(p!=i+1) {
			flg^=1;
			for(int j=1; j<=i; j++)
				swap(a[j][i+1],a[j][p]);
			for(int j=i+2; j<p; j++)
				swap(a[i+1][j],a[j][p]),a[i+1][j]=mod-a[i+1][j],a[j][p]=mod-a[j][p];
			a[i+1][p]=mod-a[i+1][p];
			for(int j=p+1; j<=n; j++)
				swap(a[i+1][j],a[p][j]);
		}
		int iv=ksm(a[i][i+1],mod-2);
		for(int j=i+2; j<=n; j++)
			if(a[i][j]) {
				int coef=1ll*(mod-a[i][j])*iv%mod;
				for(int k=1; k<=i; k++)
					a[k][j]=(a[k][j]+1ll*coef*a[k][i+1])%mod;
				for(int k=i+2; k<j; k++)
					a[k][j]=(a[k][j]+1ll*(mod-coef)*a[i+1][k])%mod;
				for(int k=j+1; k<=n; k++)
					a[j][k]=(a[j][k]+1ll*coef*a[i+1][k])%mod;
			}
	}
	ans=1;
	for(int i=1; i<=n; i+=2)
		ans=1ll*ans*a[i][i+1]%mod;
	printf("%d\n",flg==0? ans%mod:(mod-ans)%mod);
	return 0;
}
```

---

## 作者：qianyuzhe (赞：11)

>称一个长度为 $2n$ 的排列 $\pi$ 是完美匹配，当且仅当其满足
>- $\forall 1\le i\le n,\pi_{2i-1}<\pi_{2i}$
>- $\forall 1\le i<n,\pi_{2i-1}<\pi_{2i+1}$
>
>或者一种更加简单的记法：**所有完美排列表示将 $1\sim 2n$ 分成 $n$ 对的所有情况。**
>
>记 $\textup{inv }\pi$ 表示 $\pi$ 的逆序对数，$\textup{sgn }\pi=(-1)^{\textup{inv }\pi}$，$M_{2n}$ 表示全体长度为 $2n$ 的完美匹配构成的集合。
>	
>令 $\mathbf{A}=(a_{i,j})_{1\le i<j\le 2n}$ 是一个反对称矩阵，定义 $\mathbf{A}$ 的 $\text{Pfaffian}$ 为

$$\textup{Pf}(\mathbf{A})=\sum\limits_{\pi\in M_{2n}}(\textup{sgn }\pi)\prod\limits_{i=1}^{n}a_{\pi(2i-1),\pi(2i)}$$

举个例子，二阶反对称矩阵

$$\mathbf{A}=\begin{bmatrix}0&a\\-a&0\end{bmatrix}$$

它的 $\text{Pfaffian}$ 值 $\textup{Pf}(\mathbf{A})=a$。

四阶反对称矩阵

$$\mathbf{B}=\begin{bmatrix}0&a&b&c\\-a&0&d&e\\-b&-d&0&f\\-c&-e&-f&0\end{bmatrix}$$

它的 $\text{Pfaffian}$ 值 $\textup{Pf}(\mathbf{B})=af-be+cd$。

至此还没有什么发现，我们把它们平方一下试试：

$$\textup{Pf}(\mathbf{A})^2=a^2=\det(\mathbf{A})$$

$$\textup{Pf}(\mathbf{B})^2=(af-be+cd)^2=\det(\mathbf{B})$$

是否对于一切偶数阶反对称矩阵都有如上结论呢？

Proof 1. $\textup{Pf}(\mathbf{A})^2=\det(\mathbf{A})$

证明：

首先易得

$$\begin{aligned}\textup{Pf}(\mathbf{A})^2&=[\sum\limits_{\pi\in M_{2n}}(\textup{sgn }\pi)\prod\limits_{i=1}^{n}a_{\pi(2i-1),\pi(2i)}]^2\\&=\sum\limits_{\pi,\sigma\in M_{2n}}(\textup{sgn }\pi)(\textup{sgn }\sigma)\prod\limits_{i=1}^{n}a_{\pi(2i-1),\pi(2i)}a_{\sigma(2i-1),\sigma(2i)}\\&=\sum\limits_{\pi\in M_{2n}}(\textup{sgn }\pi)(\textup{sgn }\pi^{-1})\prod\limits_{i=1}^{n}a_{\pi(2i-1),\pi(2i)}a_{\pi^{-1}(2i-1),\pi^{-1}(2i)}\end{aligned}$$

再考虑行列式的组合定义：

$$\det(\mathbf{A})=\sum\limits_{\pi\in S_{2n}}(\textup{sgn }\pi)\prod\limits_{i=1}^{2n}a_{i,\pi_i}$$

对于每个排列 $\pi$，我们对其作轮换分解：

$$\pi=\prod\limits\sigma_i$$

由 $\mathbf{A}$ 的反对称性，

- 若 $\exist|\sigma_x|=1$，设 $\sigma_x=(y)$，则 $\prod\limits_{i=1}^{n}a_{i,\pi_i}$ 中有因数 $a_{y,y}=0$，消去。

- 若 $\exist|\sigma_x|>1$，设 $\pi^{-1}=\prod\limits\sigma_i^{-1}$，则 $\sigma_x\not=\sigma_x^{-1}$，于是 $\pi\not=\pi^{-1}$，进而 $(\textup{sgn }\pi)\prod\limits_{i=1}^{n}a_{i,\pi_i}+(\textup{sgn }\pi^{-1})\prod\limits_{i=1}^{n}a_{i,\pi^{-1}_i}=0$，消去。

于是**只有可分解为对换之积的排列（即完美匹配）不会被消去**，故

$$\begin{aligned}\det(\mathbf{A})&=\sum\limits_{\pi\in M_{2n}}(\textup{sgn }\pi)\prod\limits_{i=1}^{2n}a_{i,\pi_i}\\&=\sum\limits_{\pi\in M_{2n}}(\textup{sgn }\pi)\prod\limits_{i=1}^{n}a_{2i-1,\pi(2i-1)}a_{2i,\pi(2i)}\\&=\sum\limits_{\pi\in M_{2n}}(\textup{sgn }\pi)\prod\limits_{i=1}^{n}a_{\pi^{-1}(\pi(2i-1)),\pi(2i-1)}a_{\pi^{-1}(\pi(2i)),\pi(2i)}\\&=\sum\limits_{\pi\in M_{2n}}(\textup{sgn }\pi)(\textup{sgn }\pi^{-1})\prod\limits_{i=1}^{n}a_{\pi(2i-1),\pi(2i)}a_{\pi^{-1}(2i-1),\pi^{-1}(2i)}\\&=\textup{Pf}(\mathbf{A})^2\end{aligned}$$

定理得证。

（对于奇数阶反对称矩阵，其行列式值为 $0$，$\text{Pfaffian}$ 也为 $0$，证明可类比偶数阶反对称矩阵的证明。）

考虑一个更强的定理：

Proof 2. $\text{Pf}(\mathbf{A})\det(\mathbf{Q})=\text{Pf}(\mathbf{Q^T}\mathbf{A}\mathbf{Q})$

证明：

先证 $[\text{Pf}(\mathbf{A})\det(\mathbf{Q})]^2=[\text{Pf}(\mathbf{Q^T}\mathbf{A}\mathbf{Q})]^2$。

$$\begin{aligned}[\text{Pf}(\mathbf{A})\det(\mathbf{Q})]^2&=\text{Pf}(\mathbf{A})^2\det(\mathbf{Q})^2\\&=\det(\mathbf{A})\det(\mathbf{Q})^2\\&=\det(\mathbf{Q^T})\det(\mathbf{A})\det(\mathbf{Q})\\&=\det(\mathbf{Q^T}\mathbf{A}\mathbf{Q})\\&=[\text{Pf}(\mathbf{Q^T}\mathbf{A}\mathbf{Q})]^2\end{aligned}$$

再证 $\text{Pf}(\mathbf{A})\det(\mathbf{Q})=\text{Pf}(\mathbf{Q^T}\mathbf{A}\mathbf{Q})$。

显然当 $\mathbf{Q}=\mathbf{E}$ 时成立，又因为 $\det(\mathbf{Q})$ 和 $\text{Pf}(\mathbf{Q^T}\mathbf{A}\mathbf{Q})$ 均为关于 $\mathbf{Q}$ 的多项式函数，且在 $\mathbf{Q}$ 可逆时连续，因此符号必须恒为正（否则会导致不连续性），于是 $\text{Pf}(\mathbf{A})\det(\mathbf{Q})=\text{Pf}(\mathbf{Q^T}\mathbf{A}\mathbf{Q})$。

定理得证。

（关于上述定理，还有一种使用外代数的更简便的证明方法，等中考完再补吧。）

这启示我们运用合同变换将原矩阵化为特殊矩阵求解。我们知道，对称矩阵可以通过合同变换化为对角矩阵，对于偶数阶反对称矩阵，由于对其施加任意次合同变换后其依然为反对称矩阵，因此我们不能将其化为对角矩阵，但是我们可以将其化为如下分块对角矩阵：

$$\mathbf{B}=\begin{bmatrix}\mathbf{B_1}&&0\\&\ddots&\\0&&\mathbf{B_n}\end{bmatrix}$$

其中 $\mathbf{B_1},\dots,\mathbf{B_n}$ 均为二阶反对称矩阵。

也就是说，我们可以构造一个矩阵 $\mathbf{Q}=\begin{bmatrix}\mathbf{E}&\mathbf{P}\\\mathbf{O}&\mathbf{E}\end{bmatrix}$ 来将 $A$ 化为 $\mathbf{Q^T}$。

考虑如下矩阵 $\mathbf{A}$。

$$\begin{bmatrix}
0&1&2&3&6&5\\
-1&0&3&5&4&1\\
-2&-3&0&1&-1&-1\\
-3&-5&-1&0&9&8\\
-6&-4&1&-9&0&-7\\
-5&-1&1&-8&7&0\end{bmatrix}$$

假设现在我们要求出它的 $\text{Pfaffian}$ 值。

我们先从 $a_{1,3}$ 消起：

$$\begin{bmatrix}
0&1&\color{Red}2&3&6&5\\
-1&0&3&5&4&1\\
-2&-3&0&1&-1&-1\\
-3&-5&-1&0&9&8\\
-6&-4&1&-9&0&-7\\
-5&-1&1&-8&7&0\end{bmatrix}$$

要使 $a_{1,3}$ 变为 $0$，有两种选择：

1. $r_1-\dfrac{2}{3}r_2$
2. $c_3-2c_2$

为了与后面保持一致，这里我们采用第 $2$ 种方法消去。注意由于是合同变换，我们还要把 $r_3-2r_2$。

$$\begin{bmatrix}
0&1&0&3&6&5\\
-1&0&3&5&4&1\\
0&-3&0&-9&-9&-3\\
-3&-5&9&0&9&8\\
-6&-4&9&-9&0&-7\\
-5&-1&3&-8&7&0\end{bmatrix}$$

再看 $a_{1,4}$，我们仍然用 $c_2$ 来消，用 $c_4-3c_2,r_4-3r_2$。

$$\begin{bmatrix}
0&1&0&0&6&5\\
-1&0&3&5&4&1\\
0&-3&0&0&-9&-3\\
0&-5&0&0&-3&5\\
-6&-4&9&3&0&-7\\
-5&-1&3&-5&7&0\end{bmatrix}$$

类似地，我们用 $c_5-6c_2,r_5-6r_2$。

$$\begin{bmatrix}
0&1&0&0&0&5\\
-1&0&3&5&4&1\\
0&-3&0&0&9&-3\\
0&-5&0&0&27&5\\
0&-4&-9&-27&0&-13\\
-5&-1&3&-5&13&0\end{bmatrix}$$

用 $c_6-5c_2,r_6-5r_2$。

$$\begin{bmatrix}
0&1&0&0&0&0\\
-1&0&3&5&4&1\\
0&-3&0&0&9&12\\
0&-5&0&0&27&30\\
0&-4&-9&-27&0&7\\
0&-1&-12&-30&-7&0\end{bmatrix}$$

我们忽略 $r_2$，直接看 $r_3$，由于 $a_{3,4}=0$，我们让 $c_4\leftrightarrow c_5,r_4\leftrightarrow r_5$，得：

$$\begin{bmatrix}
0&1&0&0&0&0\\
-1&0&3&4&5&1\\
0&-3&0&9&0&12\\
0&-4&-9&0&-27&7\\
0&-5&0&27&0&30\\
0&-1&-12&-7&-30&0\end{bmatrix}$$

注意此处我们对换了矩阵的两行列，相当于在 $Q$ 上实行一次对换，故结果需要变号。不要误因为在原矩阵上实行了两次对换而忘记变号。

$a_{3,5}=0$，无需消去，考虑 $a_{3,6}$。

$$\begin{bmatrix}
0&1&0&0&0&0\\
-1&0&3&4&5&1\\
0&-3&0&9&0&\color{Red}12\\
0&-4&-9&0&-27&7\\
0&-5&0&27&0&30\\
0&-1&-12&-7&-30&0\end{bmatrix}$$

类比刚才的方法，我们用 $c_6-\tfrac{4}{3}c_4,r_6-\tfrac{4}{3}r_4$（注意不是减 $c_2$ 和 $r_2$）。

$$\begin{bmatrix}
0&1&0&0&0&0\\
-1&0&3&4&5&\tfrac{14}{3}\\
0&-3&0&9&0&0\\
0&-4&-9&0&-27&7\\
0&-5&0&27&0&-6\\
0&-\tfrac{14}{3}&0&-7&6&0\end{bmatrix}$$

对于剩下的元素：

$$\begin{bmatrix}
0&1&0&0&0&0\\
-1&0&\color{Red}3&\color{Red}4&\color{Red}5&\color{Red}\tfrac{14}{3}\\
0&\color{Red}-3&0&9&0&0\\
0&\color{Red}-4&-9&0&\color{Red}-27&\color{Red}7\\
0&\color{Red}-5&0&\color{Red}27&0&-6\\
0&\color{Red}-\tfrac{14}{3}&0&\color{Red}-7&6&0\end{bmatrix}$$

我们依次实行：

1. $c_3+3c_1,r_3+3r_1$
2. $c_4+4c_1,r_4+4r_1$
3. $c_5+5c_1,r_5+5r_1$
4. $c_6+\tfrac{14}{3}c_1,r_6+\tfrac{14}{3}r_1$

$$\begin{bmatrix}
0&1&0&0&0&0\\
-1&0&0&0&0&0\\
0&0&0&9&0&0\\
0&0&-9&0&\color{Red}-27&\color{Red}7\\
0&0&0&\color{Red}27&0&-6\\
0&0&0&\color{Red}-7&6&0\end{bmatrix}$$

5. $c_5-3c_3,r_5-3r_3$
6. $c_6+\tfrac{7}{9}c_3,r_6+\tfrac{7}{9}r_3$

$$\begin{bmatrix}
0&1&0&0&0&0\\
-1&0&0&0&0&0\\
0&0&0&9&0&0\\
0&0&-9&0&0&0\\
0&0&0&0&0&-6\\
0&0&0&0&6&0\end{bmatrix}$$

可以看到，对于我们希望知道的位置的元素，其数值是不变的。

对于这个矩阵，其行列式为 $(-1)^1\times[1\times(-1)\times9\times(-9)\times6\times(-6)]=(1\times9\times6)^2$，所以 $\textup{Pf}(A)=1\times9\times6=54$。

我们总结一下算法步骤：初始计数器 $cnt=0$，对于每一个奇数行 $r_{2i-1}$，若该行元素全部为 $0$，直接输出 $0$ 并终止程序。否则，找到一个 $j$ 使 $a_{2i-1,j}\not=0$ 并对换 $c_{i}$ 和 $c_j$，对换 $r_{i}$ 和 $r_j$，若 $j\not=2i$ 则令 $cnt\leftarrow cnt+1$。然后对于 $j\in[2i+1,2n]$ 将 $c_j-\tfrac{a_{2i-1,j}}{a_{2i-1,2i}}c_{2i}$。最后输出 $(-1)^{cnt}\prod\limits_{i=1}^n a_{2i-1,2i}$。

时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$。

下面是你们最喜欢的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,w,r,t,q,i,j,k,p=1e9+7,a[505][505];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++){
			cin>>a[i][j];
			a[j][i]=-a[i][j];//补全反对称矩阵 
		}
	for(r=i=1;i<n;i+=2){
		for(j=i+1;j<=n&&!a[i][j];j++);//找到非0位置
		if(j>n)return cout<<0,0;//遇到全0行直接输出0
		swap(a[i+1],a[j]);//r[i+1] <-> r[j]
		for(k=1;k<=n;k++)swap(a[k][i+1],a[k][j]);//c[i+1] <-> c[j]
		if(j>i+1)r=-r;//结果取反
		for(j=i+2;j<=n;j++){
			t=a[i][i+1];
			q=a[i][j];
			for(k=p-2;k;k>>=1){//计算乘法逆元 
				if(k&1)q=q*t%p;
				t=t*t%p;
			}
			for(k=1;k<=n;k++){
				(a[j][k]-=a[i+1][k]*q)%=p;//c[j] - (a[i][j]/a[i][i+1])*c[i+1]
				(a[k][j]-=a[k][i+1]*q)%=p;//r[j] - (a[i][j]/a[i][i+1])*r[i+1]
			}
		}
		r=r*a[i][i+1]%p;//ans <- ans*a[i][i+1]
	}
	cout<<(r+p)%p;//为避免负数再加模取模 
}
```

---

## 作者：lalaouye (赞：2)

$\text{Pfaffian}$ 与图的匹配问题密切相关，是一个暂时比较冷门的线代~~科技~~工具。

我们定义一个长度为 $2n$ 的排列 $\pi$ 是一个完美匹配，当且仅当：

1.   $\forall 1\le i\le n,\pi_{2i-1}<\pi_{2i}$

2. $\forall 1\le i<n,\pi_{2i-1}<\pi_{2i+1}$

其实就是用排列中的 $n$ 对 $(\pi_{2i-1},\pi_{2i})$ 刻画了一组完美匹配。记 $\mathcal{M}_{2n}$ 为长度为 $2n$ 的完美匹配构成集合。

对于 $2n\times 2n$ 的反对称矩阵 $A$，定义 $A$ 的 $\text{Pfaffian}$ 为

$$\text{Pf}(A)=\sum_{\pi\in\mathcal{M}_{2n}} \text{sgn}(\pi)\prod_{i=1}^nA_{\pi_{2i-1},\pi_{2i}}$$

其中 $\text{sgn}(\pi)$ 就是 $(-1)^{\text{inv}(\pi)}$，$\text{inv}(\pi)$ 则表示逆序对个数。

我们不难证明对于完美匹配排列，其逆序对个数的奇偶性，就是把 $(\pi_{2i-1},\pi_{2i})$ 视为一个区间，相交但不包含的区间对数的奇偶性，证明可以考虑一个区间两个数的贡献，这就不细说了。

关于该函数是存在一些性质的，下面我们一个一个讨论。

在讨论性质之前，我们来证一个比较厉害的东西：

$$\text{Pf}(A)=\frac{1}{2^{n}n!}\sum_{\pi}\text{sgn}(\pi)\prod_{i=1}^n A_{\pi_{2i-1},\pi_{2i}}$$

证明我们可以考虑，我们对于一个排列还是令 $(\pi_{2i-1},\pi_{2i})$ 表示一组匹配，那么对于本质相同的匹配，我们考虑如果我们要交换一组匹配在排列中的位置，那么 $\text{sgn}$ 不变，因为我们不难发现不管相对位置如何，相交但不包含稳定产生一次奇偶性改变，否则不变。

而如果我们要交换一组匹配的前后位置，那么 $\text{sgn}$ 就要取相反数，但是 $A$ 是反对称矩阵，所以这边也要取相反数，于是贡献就抵消了。

关于该函数主要有以下两个性质：

1. $\text{Pf}(BAB^T)=\det(B)\text{Pf}(A)$

2. $\det(A)=\text{Pf}^2(A)$

第二个性质貌似题解区的证法是有问题的，而且网上的证明跟看英文一样，对于本蒟蒻来说太复杂了，我这边可以提供一个比较简单的证明。

我们先来证第一个，其中 $i_1,j_1,\cdots,i_n,j_n$ 构成一个长为 $2n$ 的排列，$(i_t,j_t)$ 表示一组匹配：

$$\begin{aligned}\text{Pf}(BAB^T)&=\frac 1 {2^nn!}\sum_{i,j}\text{sgn}(i,j)\prod_{t=1}^n\sum_{k=1}^{2n}B_{i_t,k}\sum_{l=1}^{2n}A_{k,l}B_{j_t,l}\\&=\frac 1 {2^nn!}\sum_{i,j,k,l}\text{sgn}(i,j)\prod_{t=1}^n B_{i_t,k_t}A_{k_t,l_t}B_{j_t,l_t} \end{aligned}$$

然后我们接下来证明只需要计算 $k\cup l$ 是排列的情况。如果存在 $t_1,t_2$ 使得 $k_{t_1}=k_{t_2}$，我们交换 $i_{t_1},i_{t_2}$ 发现贡献变成相反数，答案抵消。对于 $l$ 类似。而如果存在 $t_1,t_2$ 使得 $k_{t_1}=l_{t_2}$，那么我们交换 $i_{t_1}$ 和 $j_{t_2}$ 答案也能够抵消。

所以我们可以钦定 $k\cup l$ 构成排列。之后我们定义 $i\cup j=p,k\cup l=q$，于是

$$\begin{aligned} \text{Pf}(BAB^T)&=\frac 1 {2^nn!}\sum_{p,q}\text{sgn}(p)\prod_{i=1}^{2n} B_{p_i,q_i} \prod_{i=1}^n A_{q_{2i-1},q_{2i}}\\&=\frac 1 {2^nn!}\sum_q \text{sgn}(q)(\sum_p\text{sgn}(p)\prod_{i=1}^{2n} B_{i,p_i})\prod_{i=1}^n A_{q_{2i-1},q_{2i}}\\&=\det(B)\text{Pf}(A) \end{aligned}$$

至于说为啥第二行乘了个 $\text{sgn}(q)$？因为 $p$ 的含义已经改变了，它变成了两个排列的复合，所以需要多乘个 $\text{sgn}(q)$。

在证明第二个性质之前，我们可以先讲讲怎么快速计算 $\text{Pf}$ 函数，我们可以利用第一条性质，对 $A$ 进行初等变换，我们知道初等变换中除了乘一行的初等变换矩阵，其它的行列式绝对值都为 $1$，交换两行需要取 $-1$。

我们考虑把矩阵变成最容易计算答案的矩阵。我们从第一行开始，只关心奇数行，若当前考虑到第 $i$ 行，我们找到 $p$ 使得 $A_{i,p}$ 不为 $0$，交换第 $i+1$ 列与第 $p$ 列，同时注意也要交换第 $i+1$ 行和第 $p$ 行。然后我们要把第 $i$ 行，$i+1$ 列后面的数全部消成 $0$，也就是对于 $i+1<j\le 2n$，我们要将第 $j$ 列减去第 $i+1$ 列乘以 $\frac{A_{i,j}}{A_{i,i+1}}$，同时将第 $j$ 行减去第 $i+1$ 行乘以 $\frac {A_{i,j}}{A_{i,i+1}}$。我们发现后面的操作不影响前面，不难发现这样变换后最后的答案一定是 $\prod_{i=1}^n A_{2i-1,2i}$。

会了这个就可以快乐的通过模板题了。但是别忘了我们还有一个历史遗留问题，也就是如何证明第二条性质。

我们考虑令 $A=PDP^T$，其中 $D$ 就是我们刚刚过程变换完最后的矩阵。对于这个矩阵，我们是容易证明 $\text{Pf}^2(D)=\det(D)$ 的。我们可以考虑归纳法，第一行只有 $D_{1,2}$ 有值，那么 $p_1=2$，然后第二列只有 $D_{2,1}$ 有值，那么 $p_2=1$，那么相当于我们的行列式需要乘以 $D_{1,2}^2$，以此类推我们发现

$$\det(D)=\prod_{i=1}^n D_{2i-1,2i}^2=\text{Pf}^2(D)$$

然后 $\text{Pf}^2(A)=\det(P)^2\det(D)$，又因为 $\det(A)=\det(P)\det(D)\det(P^T)=\det(P)^2\det(D)$，于是可以得知他们是相等的。

洛谷模板题的代码：


```cpp
int n, a[N][N];
int32_t main () {
  n = rd ();
  rep (i, 1, n) {
    rep (j, i + 1, n) {
      a[i][j] = rd (); a[j][i] = -a[i][j];
    }
  }
  int ans (1);
  for (int i (1); i <= n; i += 2) {
    int j (i + 1);
    for (; j <= n && ! a[i][j]; ++ j) ++ j;
    if (j == n + 1) return puts ("0") * 0;
    if (j != i + 1) ans = -ans;
    swap (a[j], a[i + 1]);
    rep (k, 1, n) swap (a[k][j], a[k][i + 1]);
    rep (k, i + 2, n) {
      if (a[i][k]) {
        int v = a[i][k] * qpow (a[i][i + 1], P - 2) % P;
        rep (l, 1, n) {
          (a[l][k] -= v * a[l][i + 1]) %= P;
          (a[k][l] -= v * a[i + 1][l]) %= P;
        }
      }
    }
    ans = ans * a[i][i + 1] % P;
  }
  cout << (ans + P) % P;
}
```

第二个性质有什么用呢？我们发现这个式子非常纯，左边只有 $\det$，右边只有 $\text{Pf}$，而行列式的性质可多得去了！这样在偶数阶反对称矩阵中，$\text{Pf}$ 函数拥有很多优良的性质。如果没有模数的话，我们可以直接算 $\det$ 求 $\text{Pf}$ 哦！

---

