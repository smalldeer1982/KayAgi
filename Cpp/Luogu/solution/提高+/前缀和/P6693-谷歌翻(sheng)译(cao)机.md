# 谷歌翻(sheng)译(cao)机

## 题目背景

小 L 最近沉迷用谷歌生草机生草一些奇奇怪怪的东西。

小 L 在生草出了各式各样的作品后便开始考虑这样一个问题。

## 题目描述

**注：为了方便描述，下文所有字符串起始位置都为 $1$，即都从 $1$ 开始标号。**

小 L 将每次生草前的原文和生草后的结果看作两个**仅由小写字母组成**的两个字符串 $A$ 和 $B$。

我们按如下方式定义「分割数列」和「分割串」：

- 对于一个长度为 $n$ 的字符串，定义它的一条「分割数列」为：存在长度为 $k+2$ 的数列 $p$，使得 $0=p_0<p_1<p_2<...<p_k<p_{k+1}=n+1$。对于一条「分割数列」，定义其「分割串」为 $p_i+1$ 到 $p_{i+1}-1$ 之间字符构成的子串（$i \in[0,k]$，可以为空串）。显然，对于一条长度为 $k+2$ 的分割数列，一共有 $k+1$ 个分割串。

- 对于同一个字符串，两条分割数列（$p$ 和 $q$）不同**当且仅当两条数列长度不同（$k_1\neq k_2$）**，或**存在 $i$ 使得 $p_i\neq q_i$**。

不同人对于同样的原文和结果，他们的理解方式都是不同的。我们按如下方式定义一种理解方式：

- 对于字符串 $A$ 和 $B$，我们为这两个字符串各找一条分割数列（$p$ 和 $q$），这两个分割数列满足以下要求：
1. 两个分割数列长度相等（$k_1=k_2$）。
1. 对于任意 $i$，有 $A[p_i]=B[q_i]$，即 **$A$ 第 $p_i$ 个位置的字符与 $B$ 第 $q_i$ 个位置的字符相同**。

- 定义这种理解方式的「生草程度」为**此时两个字符串的所有分割串长度的平方和**，即 $\sum\limits_{i=0}^{k_1}(p_{i+1}-p_i-1)^2+\sum\limits_{i=0}^{k_2}(q_{i+1}-q_i-1)^2$。

- 两种理解方式不同**当且仅当**两种理解方式的 $p$ 不同，或两种理解方式的 $q$ 不同。

小 L 想要知道所有理解方式的生草程度之和的结果。由于他不喜欢 $10^9+7$ 这个数，他不希望你告诉他的结果会是这个数，所以你要将结果对 $10^9+7$ 取模。

## 说明/提示

对于样例一，一共有以下理解方式：
+ $p=\{0,4\},q=\{0,5\}$，生草程度为 $25$。
+ $p=\{0,1,4\},q=\{0,2,5\}$，生草程度为 $9$。
+ $p=\{0,2,4\},q=\{0,1,5\}$，生草程度为 $11$。
+ $p=\{0,2,4\},q=\{0,4,5\}$，生草程度为 $11$。
+ $p=\{0,3,4\},q=\{0,3,5\}$，生草程度为 $9$。
+ $p=\{0,1,2,4\},q=\{0,2,4,5\}$，生草程度为 $3$。
+ $p=\{0,1,3,4\},q=\{0,2,3,5\}$，生草程度为 $3$。
+ $p=\{0,2,3,4\},q=\{0,1,3,5\}$，生草程度为 $3$。

总生草程度为 $74$。

### 数据范围

**本题采用捆绑测试。**

- Subtask 1( $20\%$ )：$n,m\leq 50$。
- Subtask 2( $30\%$ )：$n,m\leq 200$。
- Subtask 3( $50\%$ )：无特殊限制。

对于 $100\%$ 的数据，$n,m\leq 3000$，$A$ 和 $B$ **仅包含小写字母**。

## 样例 #1

### 输入

```
3 4
abc
bacb
```

### 输出

```
74```

## 样例 #2

### 输入

```
7 9
adcbbde
bdaegbcba
```

### 输出

```
2128```

# 题解

## 作者：Alex_Wei (赞：15)

Upd on 2020.11.18：补充说明

> [题面传送门](https://www.luogu.com.cn/problem/P6693)。

> 题意简述：给定两个字符串 $A,B$，长度分别为 $n,m$。构造长度为 $k$ 的两个数列 $p,q$ 满足 $p_1=q_1=0,p_k=n,q_k=m,p_i<p_{i+1},q_i<q_{i+1}$ 且 $A_{p_i}=B_{q_i}$（字符串下标从 $1$ 开始），则其权值为 $\sum (p_i-p_{i-1}-1)^2+(q_i-q_{i-1}-1)^2$。求所有这样的数列 $p,q$ 的权值之和。

---

显然有一个 $n^4$ 的 DP：

设 $f_{i,j}$ 表示数列 $p$ 以 $i$ 结尾，数列 $q$ 以 $j$ 结尾的所有数列 $p,q$ 的权值之和。  
设 $num_{i,j}$ 表示数列 $p$ 以 $i$ 结尾，数列 $q$ 以 $j$ 结尾的方案数。

那么有转移方程

$$f_{i,j}=\begin{cases}\sum_{k<i,\ l<j} f_{k,l}+num_{k,l}\times[(i-k-1)^2+(j-l-1)^2]\quad&(A_i=B_j)\\0&(A_i\neq B_j)\end{cases}$$

$$num_{i,j}=\begin{cases}\sum_{k<i,\ l<j}num_{k,l}\quad&(A_i=B_j)\\0&(A_i\neq B_j)\end{cases}$$

不难发现这样转移是 $O(n^2)$ 的，因为有 $O(n^2)$ 个状态，所以时间复杂度为 $O(n^4)$，无法接受。

不难看出 $num$ 的转移就是一个二维前缀和形式，用二维前缀和优化 DP 可以将 $num_{i,j}$ 的转移降为 $O(1)$。但是 $f$ 似乎不能这么优化？

当然可以。显然 $\sum f_{k,l}$ 是可以前缀和优化的，我们将后面一部分单独拎出来看：

$$\sum num_{k,l}\times[(i-k-1)^2+(j-l-1)^2]$$

记 $num_{k,l}=S$，平方部分拆开来就能得到

$$\begin{aligned}&\sum S\times(i^2-2i+1-2ki+2k+k^2+j^2-2j+1-2lj+2l+l^2)\\=&\sum S\times[(i^2+j^2-2i-2j+2)+(k^2+l^2+2k+2l)-2ki-2lj]\\=&\sum \color{red}S\color{black}\times(i^2+j^2-2i-2j+2)+\color{blue}S\times(k^2+l^2+2k+2l)\color{black}-\color{orange}2Sk\color{black}i-\color{green}2Sl\color{black}j\end{aligned}$$

将上式与 $i,j$ 无关的二维前缀和预处理出来（即红色的 $\sum num_{k,l}$，蓝色的 $\sum num_{k,l}\times(k^2+l^2+2k+2l)$，橙色的 $2\sum num_{k,l}\times k$ 和绿色的 $2\sum num_{k,l}\times l$）即可 $O(1)$ 转移 $f$。

答案即为 $\sum f_{i,j}+num_{i,j}\times[(n-i)^2+(m-j)^2]$。

- 需要注意的是只有当 $A_i=B_j$ 的时候柿子才能算入贡献。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N=3e3+5;
const int mod=1e9+7;

ll pw[N],f[N][N],num[N][N],sumf[N][N],sumn[N][N],cons[N][N],delk[N][N],dell[N][N],ans;
string s,t;
int n,m;

void add(ll &x,ll y){
	x+=y%mod;
	if(x>=mod)x-=mod; if(x<0)x+=mod;
}

int main() {
	for(int i=1;i<N;i++)pw[i]=i*i;
	cin>>n>>m>>s>>t;
	for(int i=0;i<=max(n,m);i++)sumn[i][0]=sumn[0][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(s[i-1]==t[j-1]){
				f[i][j]=sumf[i-1][j-1],num[i][j]=sumn[i-1][j-1];
				add(f[i][j],(pw[i]+pw[j]-2*i-2*j+2)%mod*sumn[i-1][j-1]+cons[i-1][j-1]);
				add(f[i][j],-delk[i-1][j-1]*i-dell[i-1][j-1]*j);
				add(ans,f[i][j]+num[i][j]*(pw[n-i]+pw[m-j]));
			}
			sumf[i][j]=(sumf[i-1][j]+sumf[i][j-1]-sumf[i-1][j-1]+f[i][j]+mod)%mod;
			sumn[i][j]=(sumn[i-1][j]+sumn[i][j-1]-sumn[i-1][j-1]+num[i][j]+mod)%mod;
			cons[i][j]=(cons[i-1][j]+cons[i][j-1]-cons[i-1][j-1]+num[i][j]*(pw[i]+pw[j]+2*i+2*j)+mod)%mod;
			delk[i][j]=(delk[i-1][j]+delk[i][j-1]-delk[i-1][j-1]+num[i][j]*2*i%mod+mod*2)%mod;
			dell[i][j]=(dell[i-1][j]+dell[i][j-1]-dell[i-1][j-1]+num[i][j]*2*j%mod+mod*2)%mod;
		}
	cout<<(ans+pw[n]+pw[m])%mod<<endl;
	return 0;
}
```

求赞 qwq。

---

## 作者：littleKtian (赞：4)

upd on 2021.7.12：重调了题解排版~~并顺带修复了链接~~

------------

[顺便宣传一下出题人的谷歌生草作品qwq。](https://www.luogu.com.cn/blog/Ktian/ji-guai-di-fan-yi-zeng-jia-liao)

------------

以下复杂度分析均令 $n,m$ 同阶。

------------
### Subtask 1

我们在原来的字符串最前面和最后面都加一个特殊的字符（比如在 $A$ 和 $B$ 最前面都加一个字符 `A`，最后面都加一个字符 `B`）。

设 $f_{i,j}$ 表示两个字符串的分割点分别为 $i,j$ 时所有理解方案到当前位置时的生草程度之和，$g_{i,j}$ 表示总方案数。

容易得到下面两条转移方程：

$f_{i,j}=\begin{cases}\sum\limits_{k=0}^{i-1}\sum\limits_{l=0}^{j-1}\left\{f_{k,l}+g_{k,l}\times\left[(i-k-1)^2+(j-l-1)^2\right]\right\}&A_i=B_j\\0&A_i\neq B_j]\end{cases}$

$g_{i,j}=\begin{cases}\sum\limits_{k=0}^{i-1}\sum\limits_{l=0}^{j-1}g_{k,l}&A_i=B_j\\0&A_i\neq B_j\end{cases}$

最终答案即为 $f_{n+2,m+2}$（因为我们在字符串里加了两个字符）。

暴力计算即可，复杂度 $O(n^4)$。

------------
### Subtask 2

~~出题人并不知道为什么要放这档分数。~~

不过验题人写了个 $O(n^3)$ 做法，~~可以去找他~~[做法在加强版题解里](https://www.luogu.com.cn/blog/Ktian/string-hard-ti-xie)。

------------
### Subtask 3

显然上面计算 $g_{i,j}$ 可以利用前缀和优化。

考虑是否可以利用同样的方式来计算 $f_{i,j}$。

$\begin{aligned}& \sum\limits_{k=0}^{i-1}\sum\limits_{l=0}^{j-1}\left\{f_{k,l}+g_{k,l}\times\left[(i-k-1)^2+(j-l-1)^2\right]\right\}\\&=\sum\limits_{k=0}^{i-1}\sum\limits_{l=0}^{j-1}f_{k,l}+\sum\limits_{k=0}^{i-1}\sum\limits_{l=0}^{j-1}g_{k,l}\times\left[(i-k-1)^2+(j-l-1)^2\right]\end{aligned}$

显然前一部分可以用前缀和来计算。

设 $h_{i,j}=\sum\limits_{k=0}^{i-1}\sum\limits_{l=0}^{j-1}g_{k,l}\times\left[(i-k-1)^2+(j-l-1)^2\right]$。

$\begin{aligned}h_{i,j}=&\sum\limits_{k=0}^{i-1}\sum\limits_{l=0}^{j-1}g_{k,l}\times\left[(i-k-1)^2+(j-l-1)^2\right]\\=&{\color{red}\sum\limits_{k=0}^{i-1}\sum\limits_{l=0}^{j-2}g_{k,l}\times\left[(i-k-1)^2+(j-l-2)^2\right]}\\&+{\color{blue}\sum\limits_{k=0}^{i-2}\sum\limits_{l=0}^{j-1}g_{k,l}\times\left[(i-k-2)^2+(j-l-1)^2\right]}\\&-{\color{green}\sum\limits_{k=0}^{i-2}\sum\limits_{l=0}^{j-2}g_{k,l}\times\left[(i-k-2)^2+(j-l-2)^2\right]}\\&{\color{orange}+(2i-1)\sum\limits_{k=0}^{i-1}g_{k,j}+(2j-1)\sum\limits_{l=0}^{j-1}g_{i,l}}\\&{\color{purple}-2\sum\limits_{k=0}^{i-1}k\times g_{k,j}-2\sum\limits_{l=0}^{j-1}l\times g_{i,l}}\\=&{\color{red}h_{i-1,j}}+{\color{blue}h_{i,j-1}}-{\color{green}h_{i-1,j-1}}\\&{\color{orange}+(2i-1)\sum\limits_{k=0}^{i-1}g_{k,j}+(2j-1)\sum\limits_{l=0}^{j-1}g_{i,l}}\\&{\color{purple}-2\sum\limits_{k=0}^{i-1}k\times g_{k,j}-2\sum\limits_{l=0}^{j-1}l\times g_{i,l}}\end{aligned}$

（上面相同颜色对应的部分内容相同）

容易发现 $(2i-1)\sum\limits_{k=0}^{i-1}g_{k,j},(2j-1)\sum\limits_{l=0}^{j-1}g_{i,l},2\sum\limits_{k=0}^{i-1}k\times g_{k,j},2\sum\limits_{l=0}^{j-1}l\times g_{i,l}$ 都可以利用类似前缀和优化的方法在 $O(n^2)$ 内推出。

总复杂度 $O(n^2)$。

---

## 作者：MutU (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/P6693)

非常好的一道推式子 dp 题。

## Case1

容易想到一种 $O(n^4)$ 的做法。

令 $f_{i,j}$ 表示串 $A$ 匹配到第 $i$ 位，串 $B$ 匹配到第 $j$ 位的价值和。

$n^2$ 地枚举当前状态，$n^2$ 地枚举前置状态。注意到需要用到方案数，于是令 $k_{i,j}$ 表示串 $A$ 匹配到第 $i$ 位，串 $B$ 匹配到第 $j$ 位的方案数。

式子如下：

$k_{i,j} = \sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y}$

$f_{i,j} = \sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times [(i-x-1)^2+(j-y-1)^2]+f_{x,y}$

当然若 $A_i \ne B_j$ 时 $k_{i,j}$ 和 $f_{i,j}$ 都为 $0$。

可以拿到 $50$ pts。

## Case2

显然 $k$ 的转移可以用二维前缀和来优化，但是 $f$ 转移的优化似乎不容易。

先将 $f$ 的式子拆成两部分：

$f_{i,j} = \sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times [(i-x-1)^2+(j-y-1)^2]+f_{x,y}$

$= (\sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times [(i-x-1)^2+(j-y-1)^2])
+
(\sum_{x=1}^{i-1}\sum_{y=1}^{j-1}f_{x,y})$

注意到后面一半可以用前缀和维护。再拆前面：

$\sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times [(i-x-1)^2+(j-y-1)^2]$

$=\sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times (i^2+j^2+x^2+y^2-2ix-2jy-2i-2j+2x+2y+2)$

我们把括号里的东西分类处理：

$=\sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times (i^2+j^2+2-2i-2ix-2j-2jy+x^2+y^2+2x+2y)$

$=\sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times [(i^2+j^2+2)-2i(x+1)-2j(y+1)+(x^2+y^2+2x+2y)]$

$=[\sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times (i^2+j^2+2)]-
[\sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times (x+1)] \times 2i-
[\sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times (y+1)] \times 2j+
[\sum_{x=1}^{i-1}\sum_{y=1}^{j-1}k_{x,y} \times (2x+2y+x^2+y^2)]$

我这里是开了五个二维前缀数组来分别维护以上四项中后三项以及 $k$ 数组和 $f$ 数组的前缀和。

注意当 $A_i \ne B_j$ 时当前这项直接是 $0$，但也要转移前缀和。

## Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3010;
const int mod = 1e9 + 7;
int n,m,sumf[N][N],sumk[N][N],sumx[N][N],sumy[N][N],sumt[N][N];
int f[N][N],k[N][N];
char a[N],b[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	cin>>a+1>>b+1;
	a[n+1]=b[m+1]='?';
	k[0][0]=1;
	for(int i=0;i<=n+1;i++) sumk[i][0]=sumx[i][0]=sumy[i][0]=1;
	for(int i=0;i<=m+1;i++) sumk[0][i]=sumx[0][i]=sumy[0][i]=1;
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<=m+1;j++){
			if(a[i]==b[j]){
				k[i][j] = sumk[i-1][j-1];
				f[i][j] = (sumf[i-1][j-1] + sumk[i-1][j-1]*(i*i+j*j+2)%mod - sumx[i-1][j-1]*2*i - sumy[i-1][j-1]*2*j + sumt[i-1][j-1])%mod;
				f[i][j] = (f[i][j]+mod)%mod;
			}
			sumf[i][j] = (sumf[i-1][j]+sumf[i][j-1]-sumf[i-1][j-1]+f[i][j])%mod;
			sumk[i][j] = (sumk[i-1][j]+sumk[i][j-1]-sumk[i-1][j-1]+k[i][j])%mod;
			sumx[i][j] = (sumx[i-1][j]+sumx[i][j-1]-sumx[i-1][j-1]+k[i][j]*(i+1))%mod;
			sumy[i][j] = (sumy[i-1][j]+sumy[i][j-1]-sumy[i-1][j-1]+k[i][j]*(j+1))%mod;
			sumt[i][j] = ((sumt[i-1][j]+sumt[i][j-1]-sumt[i-1][j-1]+k[i][j]*(2*i+2*j+i*i+j*j)%mod)%mod+mod)%mod;
		}
	}
	cout<<f[n+1][m+1];
	return 0;
}
```

还要注意取模后减法出负数问题，见 [真实经历](https://www.luogu.com.cn/discuss/1006915)

---

