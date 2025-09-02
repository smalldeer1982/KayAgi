# [ABC288G] 3^N Minesweeper

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc288/tasks/abc288_g

位置 $ 0,\ 1,\ 2,\ \ldots,\ 3^N-1 $ にそれぞれ $ 0 $ 個あるいは $ 1 $ 個の爆弾があります。  
 また、位置 $ x $ と位置 $ y $ は $ i=0,1,\ \ldots,\ N-1 $ すべてに対し以下の条件を満たすとき、またそのときに限り**近い位置**であるとします。

- $ x,\ y $ を $ 3 $ 進表記したときの $ 3^i $ の位の数字をそれぞれ $ x',\ y' $ として、$ |x'\ -\ y'|\ \leq\ 1 $ が成立する。
 
位置 $ i $ と近い位置にある爆弾の個数が $ A_i $ 個であるとわかっているとき、爆弾の配置としてありえるものを $ 1 $ つ出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 12 $
- $ A_0,\ A_1,\ \ldots,\ A_{3^N-1} $ に対応する爆弾の配置が存在する
- 入力はすべて整数
 
### Sample Explanation 1

$ 0 $ と近い位置は $ 0 $ と $ 1 $ で、位置 $ 0 $ と位置 $ 1 $ に爆弾は合計で $ 0 $ 個あります。 $ 1 $ と近い位置は $ 0 $ と $ 1 $ と $ 2 $ で、位置 $ 0 $ と位置 $ 1 $ と位置 $ 2 $ に爆弾は合計で $ 1 $ 個あります。 $ 2 $ と近い位置は $ 1 $ と $ 2 $ で、位置 $ 1 $ と位置 $ 2 $ に爆弾は合計で $ 1 $ 個あります。 $ 2 $ にのみ爆弾があるような配置は上の条件を全て満たすため、正答となります。

## 样例 #1

### 输入

```
1
0 1 1```

### 输出

```
0 0 1```

## 样例 #2

### 输入

```
2
2 3 2 4 5 3 3 4 2```

### 输出

```
0 1 0 1 0 1 1 1 0```

## 样例 #3

### 输入

```
2
0 0 0 0 0 0 0 0 0```

### 输出

```
0 0 0 0 0 0 0 0 0```

# 题解

## 作者：do_while_true (赞：9)

会推 fwt 就能直接秒/jy

先考虑 B 进行个什么线性变换才能得到 A．fwt 要做的是：枚举每一维，然后固定其它维的值看作常数，然后将这一维上的值单独拎出来乘上一个矩阵。那么只需要构造 $n=3$ 的矩阵，然后每次做这样一个过程就能完成 $n=3^k$．

构造就挺简单的了：

$$
\begin{bmatrix}
 1 & 1 & 0\\
 1 & 1 & 1\\
 0 & 1 & 1
\end{bmatrix}
\begin{bmatrix}
 b_0\\
 b_1\\
b_2
\end{bmatrix}
=
\begin{bmatrix}
 b_0+b_1\\
 b_0+b_1+b_2\\
b_1+b_2
\end{bmatrix}
$$

这是 B 到 A 要做的事情。而 A 转成 B 每次就乘上它的逆矩阵就行了。

$$
\begin{bmatrix}
 0 & 1 & -1\\
 1 & -1 & 1\\
 -1 & 1 & 0
\end{bmatrix}
$$

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=600010;
int n,fpow[14];
int f[N],a[3][3],b[3],c[3];
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	a[0][0]=0;a[0][1]=1;a[0][2]=-1;
	a[1][0]=1;a[1][1]=-1;a[1][2]=1;
	a[2][0]=-1;a[2][1]=1;a[2][2]=0;
	read(n);
	fpow[0]=1;for(int i=1;i<=n;i++)fpow[i]=fpow[i-1]*3;
	for(int i=0;i<fpow[n];i++)read(f[i]);
	for(int i=0;i<n;i++){
		for(int j=0;j<fpow[n];j++){
			if((j/fpow[i])%3==0){
				c[0]=c[1]=c[2]=0;
				b[0]=f[j];b[1]=f[j+fpow[i]];b[2]=f[j+fpow[i]*2];
				for(int p=0;p<3;p++)
					for(int q=0;q<3;q++)
						c[p]+=a[p][q]*b[q];
				f[j]=c[0];f[j+fpow[i]]=c[1];f[j+fpow[i]*2]=c[2];
			}
		}
	}
	for(int i=0;i<fpow[n];i++)cout << f[i] << ' ';
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：3)

## 张量积
考虑 $\mathbb F$ 上的两个线性空间 $A,B,C$, 考虑双线性映射 $f : A \times B \to C$, 则有性质
* $f(\lambda a,b)=\lambda f(a,b)=f(a,\lambda b).$

则 $\langle k_1a_1+k_2a_2,b\rangle$ 这个有序对根据双线性映射的性质, 得 $k_1 \otimes \langle a_1,b\rangle \oplus k_2 \otimes \langle a_2,b\rangle$, 其中 $f(a \oplus b) = f(a)+f(b)$, $f(k \otimes a) = kf(a)$. 但显然没有合理的 $V \times W$ 上的 $\oplus,\otimes$ 的定义. 

考虑用形式 $\otimes,\oplus$ 定义一个线性空间
$$
\begin{aligned}
A \odot B = \{f \mid f : A \times B \to \mathbb F\},
\end{aligned}
$$
其中 $f(\cdot)$ 表示
$$
\bigoplus_{p \in A \times B} f(p) \otimes p,
$$
但显然这个集合太大了, 于是我们可以用刚才的性质定义等价类 $\sim$:
- $\langle k_1a_1+k_2a_2,b\rangle \sim k_1 \otimes \langle a_1,b\rangle \oplus k_2 \otimes \langle a_2,b\rangle$;
- $\langle a, k_1b_1+k_2b_2\rangle \sim k_1 \otimes \langle a,b_1\rangle \oplus k_2 \otimes \langle a,b_2\rangle$.

于是我们得到张量积 $A \otimes B = (A \odot B)/\sim$, 满足 $\dim(A \otimes B) = \dim A \times \dim B$. 
考虑线性映射 $\phi : A \to B,\psi : C \to D$, 则定义其张量积:
$$
\begin{aligned}
\phi \otimes \psi&: A \otimes C \to B \otimes D \\
& ~a \oplus b \mapsto \phi(a) \oplus \psi(c) \\
& ~ \lambda \otimes x \mapsto \lambda \otimes \phi(x) \\
\end{aligned}
$$
, 容易验证如下性质: 
* 若 $A,B$ 是线性同构, 则 $(A \otimes B)$ 是线性同构. 
* 张量积的表示矩阵是表示矩阵的 Kronecker 积. 
* 若 $A,B$ 是线性同构, $(A \otimes B)^{-1} = A^{-1} \otimes B^{-1}$. 

## 张量幂
考虑线性空间 $V \otimes^n$（$\dim U,V \ne \infty$）, 以及线性映射
$$
\begin{aligned}
\phi : V \to V \\
\phi \otimes^n : V \otimes^n \to V \otimes^n,
\end{aligned}
$$
不妨得 $\phi$ 的表示矩阵 $M \in \mathbb F^{a \times a}$, $\phi \otimes^{n}$ 的表示矩阵 $\mathscr M$, 则
$$
\mathscr M_{i,j} = \prod_{k=0}^{n-1} M_{(i)_a[k],(j)_a[k]},
$$
其中 $(x)_a[y]$ 为 $x$ 在 $a$ 进制下的从右往左第 $y$ 位, 形式化地定义为: 
$$
\left\lfloor \dfrac{x}{a^y} \right\rfloor \bmod a.
$$
有: 
$$
\begin{aligned}
(\mathscr Mv)_i &= \sum_{j=0}^{a^n-1} \mathscr M_{ij} v_j \\
&= \sum_{j=0}^{a^n-1} v_j \prod_{k=0}^{n-1} M_{(i)_a[k],(j)_a[k]} \\
&= \sum_{x=0}^{a-1} \sum_{y=0}^{a^{n-1}-1} v_{na^{n-1}+m} M_{(i)_{a}[n-1],x} \prod_{k=0}^{n-2} M_{(i)_a[k],(j)_a[k]} \\
&= \sum_{x=0}^{a-1} M_{(i)_a[n-1],x} \sum_{y=0}^{a^{n-1}-1} v_{na^{n-1}+m} \prod_{k=0}^{n-2} M_{(i)_a[k],(j)_a[k]} \\
&= \sum_{x=0}^{a-1} M_{(i)_a[n-1],x} ((M\otimes^{n-1}) w)_{i-a^{n-1}},
\end{aligned}
$$
其中 $w_i = v_{na^{n-1}+i}$. 这样, 我们发现递归地计算, 一个规模为 $n$ 的问题可以分裂为 $a$ 个规模为 $n-1$ 的问题: 
$$
T(n) = aT(n-1);T(0)= a^2 \implies O(T(n)) = O(na^na^2).
$$

## 题解
考虑 线性空间 $\mathbb Q^3 \otimes^n$, 则 “扫雷运算” 相当于
$$
\phi(\vec a) = \begin{bmatrix}
1&1&0\\1&1&1\\0&1&1
\end{bmatrix}\otimes^{n} \vec a.
$$
然而我们要求的是扫雷逆运算. 矩阵求逆, 得
$$
\phi^{-1}(\vec a) = \begin{bmatrix}
0&1&-1\\
1&-1&1\\
-1&1&0
\end{bmatrix}\otimes^n\vec a.
$$
所以, 用上述提到的算法即可计算, 因为 $a$ 是常数, 所以时间复杂度可以被计算为 $O(n3^n)$. 

---

## 作者：win114514 (赞：2)

非常有教育意义的题目。

### 思路

我们需要深入理解 fwt 的本质。

本质上，我们不断对每一维进行线性变换。

例如在做 $a_i=\sum_{i | j = i}b_j$ 时。

我们的 fwt 过程中的变换是：

$$
\begin{cases}
  a_0=b_0\\
  a_1=b_0+b_1\\
\end{cases}
$$

这一点很容易理解，我们是将值为 $0$ 的累加到值为 $1$ 的上面。

对于这道题来说，尽管每一维变成了三个数，但它同样也是一个线性变换。

我们首先考虑如何从答案推导输入：

$$
\begin{cases}
a_0=b_0+b_1\\
a_1=b_0+b_1+b_2\\
a_2=b_1+b_2
\end{cases}
$$

现在我们需要通过输入得到答案，这实际上是对上述变换的逆变换。

只需将 $b$ 解出来即可。

$$
\begin{cases}
b_0=a_1-a_2\\
b_1=a_0+a_2-a_1\\
b_2=a_1-a_0
\end{cases}
$$

然后直接套 fwt 过程即可。

时间复杂度：$O(n3^n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int m;
int a[1000010];

int main() {
  cin >> n, m = 1;
  for (int i = 0; i < n; i++) m = m * 3;
  for (int i = 0; i < m; i++) cin >> a[i];
  for (int i = 1; i < m; i = i * 3) {
    for (int j = 0; j < m; j = j + i * 3) {
      for (int k = j; k < j + i; k++) {
        int x = a[k];
        int y = a[k + i];
        int z = a[k + i + i];
        a[k] = y - z;
        a[k + i] = x + z - y;
        a[k + i + i] = y - x;
      }
    }
  }
  for (int i = 0; i < m; i++) cout << a[i] << " \n"[i == m - 1];
}
```

---

## 作者：daniEl_lElE (赞：2)

考虑一维如何计算。我们有式子：

$\begin{cases}a_0=b_0+b_1\\a_1=b_0+b_1+b_2\\a_2=b_1+b_2\end{cases}$

容易推得：

$\begin{cases}b_0=a_1-a_2\\b_1=a_0+a_2-a_1\\b_2=a_1-a_0\end{cases}$

对于每一维分别做以上变换，容易发现直接扩展 FWT 即可。

其实长度为 $4,5,\dots$ 的超正方体应该也可做。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int pw[15],a[2000005];
signed main(){
	pw[0]=1; for(int i=1;i<=14;i++) pw[i]=pw[i-1]*3;
	int n; cin>>n;
	for(int i=0;i<pw[n];i++) cin>>a[i];
	for(int i=1;i<=n;i++) for(int j=0;j<pw[n];j++) if((j/pw[i-1])%3==0){
		int p1=a[j],p2=a[j+pw[i-1]],p3=a[j+pw[i-1]*2];
		a[j]=p2-p3,a[j+pw[i-1]]=p1+p3-p2,a[j+pw[i-1]*2]=p2-p1;
	}
	for(int i=0;i<pw[n];i++) cout<<a[i]<<" ";
	return 0;
}

```

---

## 作者：ZillionX (赞：2)

> 给定长度为 $3^n$ 的数组 $A$。若两数 $x,y$ 满足它们从低到高对应的每一位 $x',y'$ 都有 $|x'-y'| \le 1$，则建边 $(x,y)$。  
现在某些点上有一些炸弹，$a_i$ 则为与 $i$ 相邻的点（包括 $i$ 本身）上的炸弹总数。试求出每个点上的炸弹个数。  
$n \le 12$。

相关文献：[位运算卷积(FWT) & 集合幂级数 by @command_block](https://www.luogu.com.cn/blog/command-block/wei-yun-suan-juan-ji-yu-ji-kuo-zhan)。

设每个点上的炸弹数为数组 $B$，我们考虑怎么从 $B$ 得到 $A$。

很显然，贡献系数可以写成一个矩阵 $c$ 的形式，那么我们将 $A$ 乘上 $c^{-1}$ 就可以得到 $B$。暴力做是 $\mathcal O(3^{2n})$ 的，现在我们要干的就是优化这一过程。

容易发现这十分类似于 $3$ 进制上的 IDWT，但是贡献矩阵显然是不同的。注意到本题和位运算卷积问题一样，仍然满足可以分位做的性质。

那么我们就可以先求出 $c([0,1,2],[0,1,2],[0,1,2])$ 的真值表，然后仿照 FWT 分治的方法做卷积。

根据题目要求容易构造出

$$c=\begin{bmatrix}1 & 1 &0\\1 &1 &1\\0 &1 &1\end{bmatrix}$$

进一步，待定系数法容易求出

$$c^{-1}=\begin{bmatrix}0 & 1 &-1\\1 &-1 &1\\-1 &1 &0\end{bmatrix}$$

和 FWT 一样，分类讨论 $x$ 的最高位 $x_t=\{0,1,2\}$，分别处理幂级数最高位为 $\{0,1,2\}$ 的部分 $A_0,A_1,A_2$ 的贡献，就可以做到 $\mathcal O(n3^n)$。

```cpp
const int N=1e6+5,c[3][3]={{0,1,-1},{1,-1,1},{-1,1,0}};
int n,a[N],pw3[15];
signed main(){
	pw3[0]=1;
	for(int i=1;i<15;i++)pw3[i]=pw3[i-1]*3;
	cin>>n,n=pw3[n];
	for(int i=0;i<n;i++)cin>>a[i];
	for(int len=1;len<n;len*=3)for(int p=0;p<n;p+=len*3)
	for(int i=p;i<p+len;i++){
		int f0=a[i],f1=a[i+len],f2=a[i+len*2];
		a[i]=c[0][0]*f0+c[0][1]*f1+c[0][2]*f2;
		a[i+len]=c[1][0]*f0+c[1][1]*f1+c[1][2]*f2;
		a[i+len*2]=c[2][0]*f0+c[2][1]*f1+c[2][2]*f2;
	}
	for(int i=0;i<n;i++)printf("%lld ",a[i]);
	return 0;
}
```


---

## 作者：Fzrcy (赞：1)

定义 $A(X_{n-1},X_{n-2},\dots,X_{0}) = a[X_{n-1}3^{n-1}+X_{n-2}3^{n-2}+\dots+X_{0}3^{0}]$，答案为 $B(X_{n-1},X_{n-2},\dots,X_{0})$。

定义 

$$F(X_{n-1},X_{n-2},\dots,X_{0},total) = \sum_{i\in[total+1,n-1],\lvert X_i-Y_i\rvert \le 1}^{n}B(Y_{n-1},Y_{n-2},\dots,Y_{total+1},X_{total},\dots,X_{0})$$

有

$$A(X_{n-1},X_{n-2},\dots,X_{0}) = \sum_{i\in[0,n-1],\lvert X_i-Y_i\rvert \le 1}^{n}B(Y_{n-1},Y_{n-2},\dots,Y_{0})$$

先考虑 $n = 1$ 的情况：

$$B(0) = A(1) - A(2)$$

$$B(1) = A(0) + A(2) - A(1)$$

$$B(2) = A(1) - A(0)$$

对其推广：

$$
\begin{aligned}
F(X_{n-1},X_{n-2},\dots,0,X_{i-1},\dots,X_0,i) = &F(X_{n-1},X_{n-2},\dots,X_{i},1,\dots,X_0,i-1) \\
&- F(X_{n-1},X_{n-2},\dots,X_{i},2,\dots,X_0,i-1)\\
\\
F(X_{n-1},X_{n-2},\dots,1,X_{i-1},\dots,X_0,i) = &F(X_{n-1},X_{n-2},\dots,X_{i},0,\dots,X_0,i-1) \\&+ F(X_{n-1},X_{n-2},\dots,X_{i},2,\dots,X_0,i-1) \\&- F(X_{n-1},X_{n-2},\dots,X_{i},1,\dots,X_0,i-1)\\
\\
F(X_{n-1},X_{n-2},\dots,2,X_{i-1},\dots,X_0,i) = &F(X_{n-1},X_{n-2},\dots,X_{i},1,\dots,X_0,i-1) \\&- F(X_{n-1},X_{n-2},\dots,X_{i},0,\dots,X_0,i-1)
\end{aligned}
$$

举个栗子：

$$A(0,0) = 2,A(0,1)=3,A(0,2)=2$$

$$A(1,0) = 4,A(1,1)=5,A(1,2)=3$$

$$A(2,0) = 3,A(2,1)=4,A(2,2)=2$$

有：

$$F(0,0,-1)= 2,F(0,1,-1)=3,F(0,2,-1)=2$$

$$F(1,0,-1) = 4,F(1,1,-1)=5,F(1,2,-1)=3$$

$$F(2,0,-1) = 3,F(2,1,-1)=4,F(2,2,-1)=2$$

以 $F(0,1,0)$ 的计算为例：

$$F(0,1,0) = F(0,0,-1)+F(0,2,-1)-F(0,1,-1) = 1$$

有：

$$F(0,0,0) = 1,F(0,1,0)=1,F(0,2,0)=1$$

$$F(1,0,0) = 2,F(1,1,0)=2,F(1,2,0)=1$$

$$F(2,0,0) = 2,F(2,1,0)=1,F(2,2,0)=1$$

以 $F(1,1,1)$ 的计算为例：

$$F(1,1,1) = F(0,1,0)+F(2,1,0)-F(1,1,0) = 0$$

有：

$$F(0,0,1) = B(0,0) = 0,F(0,1,1)=B(0,1)=1,F(0,2,1)=B(0,2)=0$$

$$F(1,0,1) = B(1,0) = 1,F(1,1,1)=B(1,1)=0,F(1,2,1)=B(1,2)=1$$

$$F(2,0,1) = B(2,0) = 1,F(2,1,1)=B(2,1)=1,F(2,2,1)=B(2,2)=0$$

也就是说我们可以通过 $F(X_{n-1},X_{n-2},\dots,X_{0},i-1)$ 得到 $F(X_{n-1},X_{n-2},\dots,X_{0},i)$ 的解，你可以认为求解的过程时使模糊变**精确**的过程。

~~如果没有听懂我在说什么，可以去看官方文档，或学习 Zeta 变换~~。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[531441+11]; // a[3^12 + 11]
int pow3[15];
int main(){
    scanf("%d", &n), pow3[0] = 1;
    for(int i = 1; i <= n; i ++) pow3[i] = pow3[i-1] * 3;
    for(int i = 0; i < pow3[n]; i++) scanf("%d", &a[i]);
    for(int wei = 0; wei < n; wei++){
        int chu = pow3[wei];
        for(int i = 0; i < pow3[n]; i++){
            if((i/chu)%3)continue;
            int val0 = a[i], val1 = a[i+chu], val2 = a[i+chu*2];
            a[i] = val1 - val2, a[i+chu] = val0 + val2 - val1, a[i+chu*2] = val1 - val0;
        }
    }
    for(int i = 0; i < pow3[n]-1; i ++){
        printf("%d ", a[i]);
    }
  	printf("%d", a[pow3[n]-1]);
    return 0;
}
```

---

