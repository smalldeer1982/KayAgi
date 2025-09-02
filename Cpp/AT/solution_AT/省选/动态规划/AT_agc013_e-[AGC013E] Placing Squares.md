# [AGC013E] Placing Squares

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc013/tasks/agc013_e

joisinoお姉ちゃんは、長さ $ N $ の棒を持っています。 この棒には $ M $ 個の印がついています。 $ i $ 個目の印は、棒の左端から距離 $ X_i $ の位置についています。

joisinoお姉ちゃんは、この棒の上にいくつかの正方形を置くことにしました。 正方形を置くにあたって、以下のような条件があります。

- 辺の長さが整数の正方形しか置いてはならない。
- 全ての正方形は、底辺が棒と接するように置かなくてはならない。
- 正方形は、棒の上に敷き詰められている必要がある。 つまり、正方形が棒からはみ出したり、上に正方形が乗っていないような棒の部分が存在したりしてはならない。
- 棒の印がついている部分の真上は、$ 2 $ つの正方形の境目であってはならない。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc013_e/60c8a1a1423174de467baae2e3cd9946ad507a48.png)条件を満たす配置とそうでない配置の例

 

ある正方形の配置の美しさとは、置かれている正方形の面積をすべて**掛け合わせた**値です。 joisinoお姉ちゃんは、上の条件を満たすような正方形の配置全てについて、その美しさを求め、その総和を知りたくなりました。 あなたの仕事は、joisinoお姉ちゃんの代わりにこれを求めるプログラムを作ることです。 なお、答えは非常に大きくなることがあるので、$ 10^9+7 $ で割った余りを出力してください。

## 说明/提示

### 制約

- 入力は全て整数である
- $ 1\ \leq\ N\ \leq\ 10^9 $
- $ 0\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ X_1\ <\ X_2\ <\ ...\ <\ X_{M-1}\ <\ X_M\ \leq\ N-1 $

### Sample Explanation 1

可能な配置は、 - 一辺の長さ $ 1 $ の正方形を左に、一辺の長さ $ 2 $ の正方形を右に置く - 一辺の長さ $ 3 $ の正方形を置く の $ 2 $ 通りで、その美しさの合計は、$ (1\ \times\ 1\ \times\ 2\ \times\ 2)\ +\ (3\ \times\ 3)\ =\ 13 $ となります。

## 样例 #1

### 输入

```
3 1
2```

### 输出

```
13```

## 样例 #2

### 输入

```
5 2
2 3```

### 输出

```
66```

## 样例 #3

### 输入

```
10 9
1 2 3 4 5 6 7 8 9```

### 输出

```
100```

## 样例 #4

### 输入

```
1000000000 0```

### 输出

```
693316425```

# 题解

## 作者：tzc_wk (赞：34)

upd on 2021.12.22：修了个 typo。

[Atcoder 题面传送门](https://atcoder.jp/contests/agc013/tasks/arc013_e) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT2371)

~~这是一道难度 Cu 的 AGC E，碰到这种思维题我只能说：not for me，thx~~

~~然鹅似乎 ycx 把题看错了？~~

首先这个平方与乘法比较喜闻乐见，很容易与**组合**联系在一起，于是我们不妨把题目条件翻译成组合的语言：

- 有一排 $n$ 个格子，你要在其中插入若干个隔板将其隔成若干段
- 有 $m$ 个特殊格子 $a_1,a_2,\dots,a_m$，$\forall i\in [1,m]$ 你禁止在 $a_i$ 与 $a_{i}+1$ 之间放隔板
- 在相邻隔板之间的格子中需恰好放上一个黑球和一个白球（可以重合）

不难发现，上述题面中的”隔板“对应原题中的正方形边界，对于一段长度为 $l$ 的段，在上面放一个黑球和一个白球的方案数为 $l^2$，也就对应了原题面中的”平方“，而原题中的乘法在上述题面中被翻译成了乘法原理。因此我们就将这题与组合意义联系在了一起。

考虑设 $dp_{i,j}$ 表示现在考虑了前 $i$ 个位置，在当前位置到上一个隔板的区间中放上了 $j$ 个球的方案数，其中 $j\in [0,2]$。

显然对于非特殊格子 $i$ 我们有状态转移方程：

- $dp_{i+1,0}=dp_{i,0}+dp_{i,2}$（在 $i$ 与 $i+1$ 之间放隔板或不放隔板）
- $dp_{i+1,1}=2dp_{i,0}+dp_{i,1}+2dp_{i,2}$（如果放隔板，那么只能从 $dp_{i,2}$ 转移过来，由于有黑白两种颜色的求所以乘个 $2$；如果不放隔板，那么可以从 $dp_{i,0},dp_{i,1}$ 转移过来，同理 $dp_{i,0}$ 前的系数也需乘个 $2$）
- $dp_{i+1,2}=dp_{i,0}+dp_{i,1}+2dp_{i,2}$（如果放隔板，那么只能从 $dp_{i,2}$ 转移过来；如果不放隔板，那么可以从 $dp_{i,0},dp_{i,1},dp_{i,2}$ 转移过来，以上四种情况均只有一种放法，而 $dp_{i,2}$ 前系数的 $2$ 是因为 $dp_{i,2}$ 出现了两次）

对于特殊格子 $i$ 我们同样可以得到类似的状态转移方程：

- $dp_{i+1,0}=dp_{i,0}$
- $dp_{i+1,1}=2dp_{i,0}+dp_{i,1}$
- $dp_{i+1,2}=dp_{i,0}+dp_{i,1}+dp_{i,2}$

那么这样转化有什么好处呢？在原题中我们直接 $dp$ 不是太容易，或者说我们只能想出 1D1D 的 $dp$ 状态。而在转化后的题面中则可以将转移写成常系数齐次递推的形式了。

由于上述状态转移方程以常系数齐次递推的形式出现，故我们可以把它写成矩阵的形式，即对于非特殊格子 $i$，$\begin{bmatrix}dp_{i+1,0}\\dp_{i+1,1}\\dp_{i+1,2}\end{bmatrix}=\begin{bmatrix}1&0&1\\2&1&2\\1&1&2\end{bmatrix}\begin{bmatrix}dp_{i,0}\\dp_{i,1}\\dp_{i,2}\end{bmatrix}$，对于特殊格子 $i$，$\begin{bmatrix}dp_{i+1,0}\\dp_{i+1,1}\\dp_{i+1,2}\end{bmatrix}=\begin{bmatrix}1&0&0\\2&1&0\\1&1&1\end{bmatrix}\begin{bmatrix}dp_{i,0}\\dp_{i,1}\\dp_{i,2}\end{bmatrix}$。因此最后的 $dp_n$ 可以写成一排 $\begin{bmatrix}1&0&1\\2&1&2\\1&1&2\end{bmatrix}$ 和 $\begin{bmatrix}1&0&0\\2&1&0\\1&1&1\end{bmatrix}$ 连乘的形式，其中 $\begin{bmatrix}1&0&0\\2&1&0\\1&1&1\end{bmatrix}$ 的个数为 $m$，显然矩乘算一下就好了，复杂度 $m\log n\omega^3$，其中 $\omega=3$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MOD=1e9+7;
int n,m;
struct mat{
	ll a[3][3];
	mat(){memset(a,0,sizeof(a));}
	mat operator *(const mat &rhs){
		mat res;
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) for(int k=0;k<3;k++)
			res.a[i][j]+=a[i][k]*rhs.a[k][j];
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) res.a[i][j]%=MOD;
		return res;
	}
};
int main(){
	mat x,y,ret;ret.a[0][0]=1;
	x.a[0][0]=1;x.a[0][1]=0;x.a[0][2]=1;
	x.a[1][0]=2;x.a[1][1]=1;x.a[1][2]=2;
	x.a[2][0]=1;x.a[2][1]=1;x.a[2][2]=2;
	y.a[0][0]=1;y.a[0][1]=0;y.a[0][2]=0;
	y.a[1][0]=2;y.a[1][1]=1;y.a[1][2]=0;
	y.a[2][0]=1;y.a[2][1]=1;y.a[2][2]=1;
	scanf("%d%d",&n,&m);int pre=-1;
	for(int i=1,v;i<=m;i++){
		scanf("%d",&v);int stp=v-pre-1;
		mat z=x;for(;stp;stp>>=1,z=z*z) if(stp&1) ret=z*ret;
		ret=y*ret;pre=v;
	} int stp=n-pre-1;
	mat z=x;for(;stp;stp>>=1,z=z*z) if(stp&1) ret=z*ret;
	printf("%d\n",ret.a[2][0]);
	return 0;
}
```

upd on 2021.3.9：

事实上还有一种基于朴素 $dp$ 的代数优化方法。

首先我们不考虑组合意义，就直接设 $dp_i$ 表示考虑前 $i$ 个格子并在 $i$ 与 $i+1$ 放上隔板的答案。显然对于非特殊点 $dp_i=\sum\limits_{j=0}^{i-1}dp_j(i-j)^2$，否则 $dp_i=0$。

考虑直接着手优化这个式子，我们考虑 $dp_{i+1}$ 的递推式，（这里假设 $i+1$ 不是标记点，即 $dp_{i+1}\ne 0$）显然 $dp_{i+1}=\sum\limits_{j=0}^idp_j(i+1-j)^2$，考虑把最后一项单独提出来，即 $dp_{i+1}=\sum\limits_{j=0}^{i-1}dp_j(i+1-j)^2+dp_i$，把括号打开即有 $dp_{i+1}=\sum\limits_{j=0}^{i-1}dp_j(i-j)^2+2\sum\limits_{j=0}^{i-1}dp_j(i-j)+\sum\limits_{j=0}^{i-1}dp_j+dp_i$

我们记 $a_i=\sum\limits_{j=0}^{i-1}dp_j,b_i=\sum\limits_{j=0}^{i-1}dp_j(i-j),c_i=\sum\limits_{j=0}^{i-1}dp_j(i-j)^2$，那么显然 $dp_i=c_i$，还是考虑上面 $dp_{i+1}$ 的展开式，那么有 $dp_{i+1}=a_i+2b_i+c_i+dp_i$，假设我们知道了 $a_{i},b_{i},c_{i}$，考虑怎样求出 $a_{i+1},b_{i+1},c_{i+1}$，分 $i$ 我特殊点和 $i$ 不是特殊点讨论：

- 若 $i$ 不是特殊点，那么
  - $a_{i+1}=\sum\limits_{j=0}^{i-1}dp_j+dp_{i}=a_i+c_i$
  - $b_{i+1}=\sum\limits_{j=0}^{i-1}dp_j(i+1-j)+dp_{i}=\sum\limits_{j=0}^{i-1}dp_j(i-j)+\sum\limits_{j=0}^{i-1}dp_j+dp_i=b_i+a_i+c_i$
  - $c_{i+1}=dp_{i+1}=a_i+2b_i+c_i+dp_i=a_i+2b_i+2c_i$
- 若 $i$ 是特殊点，那么
  - $a_{i+1}=\sum\limits_{j=0}^{i-1}dp_j=a_i$
  - $b_{i+1}=\sum\limits_{j=0}^{i-1}dp_j(i+1-j)=\sum\limits_{j=0}^{i-1}dp_j(i-j)+\sum\limits_{j=0}^{i-1}dp_j=b_i+a_i$
  - $c_{i+1}=dp_{i+1}=a_i+2b_i+c_i$

上述式子也可写成矩阵的形式，即对于关键点 $i$，$\begin{bmatrix}a_{i+1}\\b_{i+1}\\c_{i+1}\end{bmatrix}=\begin{bmatrix}1&0&1\\1&1&1\\1&2&2\end{bmatrix}\times\begin{bmatrix}a_{i}\\b_{i}\\c_{i}\end{bmatrix}$，否则 $\begin{bmatrix}a_{i+1}\\b_{i+1}\\c_{i+1}\end{bmatrix}=\begin{bmatrix}1&0&0\\1&1&0\\1&2&1\end{bmatrix}\times\begin{bmatrix}a_{i}\\b_{i}\\c_{i}\end{bmatrix}$，这个同样可以矩阵 ksm 计算。时间复杂度同上。

代码与前一种解法大同小异：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MOD=1e9+7;
int n,m;
struct mat{
	ll a[3][3];
	mat(){memset(a,0,sizeof(a));}
	mat operator *(const mat &rhs){
		mat res;
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) for(int k=0;k<3;k++)
			res.a[i][j]+=a[i][k]*rhs.a[k][j];
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) res.a[i][j]%=MOD;
		return res;
	}
};
int main(){
	mat x,y,ret;ret.a[0][0]=ret.a[1][0]=ret.a[2][0]=1;
	x.a[0][0]=1;x.a[0][1]=0;x.a[0][2]=1;
	x.a[1][0]=1;x.a[1][1]=1;x.a[1][2]=1;
	x.a[2][0]=1;x.a[2][1]=2;x.a[2][2]=2;
	y.a[0][0]=1;y.a[0][1]=0;y.a[0][2]=0;
	y.a[1][0]=1;y.a[1][1]=1;y.a[1][2]=0;
	y.a[2][0]=1;y.a[2][1]=2;y.a[2][2]=1;
	scanf("%d%d",&n,&m);int pre=0;
	for(int i=1,v;i<=m;i++){
		scanf("%d",&v);int stp=v-pre-1;
		mat z=x;for(;stp;stp>>=1,z=z*z) if(stp&1) ret=z*ret;
		ret=y*ret;pre=v;
	} int stp=n-pre-1;
	mat z=x;for(;stp;stp>>=1,z=z*z) if(stp&1) ret=z*ret;
	printf("%d\n",ret.a[2][0]);
	return 0;
}
```



---

## 作者：小粉兔 (赞：14)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC013.html](https://www.cnblogs.com/PinkRabbit/p/AGC013.html)。

寻求组合意义：

- 在 $N + 1$ 个间隔（包含位置为 $0$ 和 $N$ 的间隔）中放置若干个隔板。

- 其中位置 $0$ 和 $N$ 必须放置隔板，且有 $M$ 个位置禁止放置隔板。

- 对于 $N$ 个格子，每个格子中可以放球，蓝球或者红球。

- 特别地需要满足：在相邻两个隔板间的每个格子中，蓝球的数量恰好为 $1$，红球的数量也恰好为 $1$。

不难验证，对于一种放置隔板的方案，放球的方案数恰好为 $\displaystyle \prod_{i = 1}^{k} {(a_i)}^2$，其中 $k$ 为正方形个数，$a_i$ 为第 $i$ 个正方形的边长。

此时我们即是要统计上述放置隔板和球的方案数。

我们可以令 $\mathrm{f}[i][j]$ 表示仅考虑了前 $i$ 个格子和前 $i + 1$ 个间隔（也就是考虑到第 $i$ 个格子右侧的间隔）时，且当最后一个隔板的右边的球数恰好为 $j$ 时的放置方案数。

显然 $j$ 的取值为 $[0, 2]$。我们容易写出 $\mathrm{f}[i][\ast]$ 从 $\mathrm{f}[i - 1][\ast]$ 转移的式子，有两种转移，取决于第 $i$ 个格子右侧是否禁止了放置隔板。

注意到这两种转移关于 $\mathrm{f}[i]$ 看作向量后，都是线性变换，可以被表示为矩阵的形式。

那么也就是有 $N$ 个 $\boldsymbol{A}$ 矩阵连乘，然而实际上其中有 $\mathcal O (M)$ 个被替换成了 $\boldsymbol{B}$ 矩阵，求一向量乘矩阵的结果。

显然使用矩阵快速幂可以做到 $\mathcal O (M \log N)$ 的时间复杂度。

```cpp
#include <cstdio>

typedef long long LL;
const int Mod = 1000000007;

#define F(i) for (int i = 0; i < 3; ++i)
struct Mat {
	int a[3][3];
	Mat() {}
	Mat(int v) {
		F(i) F(j) a[i][j] = (i == j) * v;
	}
	int * operator [] (int i) {
		return a[i];
	}
	friend Mat operator * (Mat a, Mat b) {
		Mat c(0);
		F(i) F(k) F(j) c[i][j] = (c[i][j] + (LL)a[i][k] * b[k][j]) % Mod;
		return c;
	}
};

int N, M;
Mat A, B, Ans(1);

int main() {
	A[0][0] = 2, A[0][1] = 1, A[0][2] = 1;
	A[1][0] = 2, A[1][1] = 1, A[1][2] = 0;
	A[2][0] = 1, A[2][1] = 1, A[2][2] = 1;
	B[0][0] = 1, B[0][1] = 0, B[0][2] = 0;
	B[1][0] = 2, B[1][1] = 1, B[1][2] = 0;
	B[2][0] = 1, B[2][1] = 1, B[2][2] = 1;
	scanf("%d%d", &N, &M);
	int lst = 0;
	for (int i = 1, x; i <= M; ++i) {
		scanf("%d", &x);
		int e = x - lst - 1;
		Mat C = A;
		for (; e; e >>= 1, C = C * C)
			if (e & 1) Ans = C * Ans;
		Ans = B * Ans;
		lst = x;
	}
	int e = N - lst - 1;
	Mat C = A;
	for (; e; e >>= 1, C = C * C)
		if (e & 1) Ans = C * Ans;
	Ans = B * Ans;
	printf("%d\n", Ans[2][0]);
	return 0;
}
```

---

## 作者：i207M (赞：10)

？？？这道题做法有那么复杂吗？我来一个简单做法！

首先考虑没有限制怎么做？

这显然可以矩乘对吧，式子其他题解都写了。

有限制怎么做？

不知道大家有没有做过“在网格上向上向右走，不能经过黑点，从左下到右上的方案数”，这道题，回忆我们的转移方程：

$$dp[i]=f[pos[i]]-\sum_j  dp[j]\times f[pos[i]-pos[j]]$$

现在我们的f数组变成了矩阵，**而且这个矩阵有逆矩阵！！！**

那么就变成了

$$dp[i]=M^{pos[i]}(1-\sum_j dp[j]M^{-pos[j]})$$

多维护一个变量，从前往后DP即可！

```cpp
#define N 100005
// void test(int n)
// {
// 	static int w[N],f[N],g[N],h[N];
// 	w[0]=1;
// 	for(ri i=1; i<=n; ++i)
// 	{
// 		for(ri j=1; j<=i; ++j)
// 			inc(w[i],mul(w[i-j],j,j));
// 	}
// 	h[0]=1;
// 	for(ri i=1; i<=n; ++i)
// 	{
// 		f[i]=add(f[i-1],f[i-1],g[i-1],g[i-1],h[i-1]);
// 		g[i]=add(f[i-1],g[i-1],h[i-1]);
// 		h[i]=add(f[i-1],h[i-1]);
// 	}
// 	for(ri i=1; i<=n; ++i) out(i,w[i]);
// }
struct Mat
{
	int m[3][3];
	il int *operator[](const int x) {return m[x];}
	il const int *operator[](const int x) const {return m[x];}
	friend Mat operator*(const Mat &a,const Mat &b)
	{
		Mat c; mem(c.m,0);
		for(ri i=0; i<3; ++i)
			for(ri k=0; k<3; ++k)
				for(ri j=0; j<3; ++j)
					inc(c[i][j],mul(a[i][k],b[k][j]));
		return c;
	}
	friend Mat operator*(Mat a,const int v)
	{
		for(ri i=0; i<3; ++i)
			for(ri j=0; j<3; ++j)
				a[i][j]=mul(a[i][j],v);
		return a;
	}
	il void operator+=(const Mat &v)
	{
		for(ri i=0; i<3; ++i)
			for(ri j=0; j<3; ++j)
				inc(m[i][j],v[i][j]);
	}
	il void operator-=(const Mat &v)
	{
		for(ri i=0; i<3; ++i)
			for(ri j=0; j<3; ++j)
				dec(m[i][j],v[i][j]);
	}
	il void print()
	{
		for(ri i=0; i<3; ++i) prt(m[i],3);
	}
};
Mat qpow(Mat a,int b)
{
	Mat res; mem(res.m,0);
	for(ri i=0; i<3; ++i) res[i][i]=1;
	for(; b; b>>=1,a=a*a) if(b&1) res=res*a;
	return res;
}
Mat zy,ni,sum;
il int func(int x)
{
	return qpow(zy,x)[2][0];
}
int n,m;
int pos[N];
// int dp[N];
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("ot.out","w",stdout);
#endif
	// test(20);
	zy[0][0]=zy[1][0]=2,zy[0][1]=zy[0][2]=zy[1][1]=zy[2][0]=zy[2][1]=zy[2][2]=1;
	ni[0][0]=ni[2][0]=ni[1][1]=1,ni[0][2]=ni[2][1]=md-1,ni[1][0]=md-2,ni[1][2]=2;
	in(n,m);
	for(ri i=1; i<=m; ++i) in(pos[i]);
	pos[m+1]=n;
	for(ri i=1; i<=m+1; ++i)
	{
		Mat t=qpow(zy,pos[i]);
		t-=t*sum;
		// out(i,pos[i]);
		// t.print();
		if(i<=m) sum+=qpow(ni,pos[i])*t[2][0];
		else sum=t;
		// sum.print();
		// dp[i]=func(pos[i]);
		// for(ri j=1; j<i; ++j) dec(dp[i],mul(dp[j],func(pos[i]-pos[j])));
	}
	int ans=sum[2][0];
	out(ans);
	return 0;
}
```

---

## 作者：myee (赞：9)

### 前言

憨憨题。为啥有铜牌。

这是一个非常简洁的做法，效率也比较高。

### 思路

忽略掉现实背景，考虑直接以间隔点为状态 dp。

$$f_0=1,f_p=[p\notin S]\sum_{k<p}(p-k)^2f_k$$

这个是经典题：遇到幂次就展开！

假设 $A_p=\sum_{k<p}f_k,B_p=\sum_{k<p}(k-p)f_k,C_p=\sum_{k<p}(k-p)^2f_k$，则也即

$$C_{p+1}=(1+[p\notin S])C_p+2B_p+A_p$$

$$B_{p+1}=[p\notin S]C_p+B_p+A_p$$

$$A_{p+1}=[p\notin S]C_p+A_p$$

作为没脑子选手，当然对每个 $p\notin S$ 区间进行矩阵快速幂啦！

$$\begin{bmatrix}C_{p+1}\\B_{p+1}\\A_{p+1}\end{bmatrix}=\begin{bmatrix}2&2&1\\1&1&1\\1&&1\end{bmatrix}\begin{bmatrix}C_p\\B_p\\A_p\end{bmatrix}$$

特别地，对 $p\in S$ 时，即为

$$\begin{bmatrix}C_{p+1}\\B_{p+1}\\A_{p+1}\end{bmatrix}=\begin{bmatrix}1&2&1\\&1&1\\&&1\end{bmatrix}\begin{bmatrix}C_p\\B_p\\A_p\end{bmatrix}$$

倍增预处理前者快速幂即可。

如果想进一步优化，可以考虑使用 $k$ 进制快速幂、矩阵对角化等来平衡复杂度。

### Code

以下是核心代码。

```cpp
const ullt Mod=1e9+7;
typedef ConstMod::mod_ullt<Mod>modint;
typedef std::vector<modint>modvec;
modint A[31][3][3],B[3][3],Ans[3],User[3];
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    // freopen("QAQ.out","w",stdout);
#endif
    A[0][0][0]=A[0][0][1]=B[0][1]=2;
    A[0][0][2]=A[0][1][0]=A[0][1][1]=A[0][1][2]=A[0][2][0]=A[0][2][2]=1;
    B[0][0]=B[0][2]=B[1][1]=B[1][2]=B[2][2]=1;
    Ans[2]=1;
    for(uint i=1;i<=30;i++)
        A[i][0][0]=A[i-1][0][0]*A[i-1][0][0]+A[i-1][0][1]*A[i-1][1][0]+A[i-1][0][2]*A[i-1][2][0],
        A[i][0][1]=A[i-1][0][0]*A[i-1][0][1]+A[i-1][0][1]*A[i-1][1][1]+A[i-1][0][2]*A[i-1][2][1],
        A[i][0][2]=A[i-1][0][0]*A[i-1][0][2]+A[i-1][0][1]*A[i-1][1][2]+A[i-1][0][2]*A[i-1][2][2],
        A[i][1][0]=A[i-1][1][0]*A[i-1][0][0]+A[i-1][1][1]*A[i-1][1][0]+A[i-1][1][2]*A[i-1][2][0],
        A[i][1][1]=A[i-1][1][0]*A[i-1][0][1]+A[i-1][1][1]*A[i-1][1][1]+A[i-1][1][2]*A[i-1][2][1],
        A[i][1][2]=A[i-1][1][0]*A[i-1][0][2]+A[i-1][1][1]*A[i-1][1][2]+A[i-1][1][2]*A[i-1][2][2],
        A[i][2][0]=A[i-1][2][0]*A[i-1][0][0]+A[i-1][2][1]*A[i-1][1][0]+A[i-1][2][2]*A[i-1][2][0],
        A[i][2][1]=A[i-1][2][0]*A[i-1][0][1]+A[i-1][2][1]*A[i-1][1][1]+A[i-1][2][2]*A[i-1][2][1],
        A[i][2][2]=A[i-1][2][0]*A[i-1][0][2]+A[i-1][2][1]*A[i-1][1][2]+A[i-1][2][2]*A[i-1][2][2];
    uint n,m,wil=-1,p;
    scanf("%u%u",&n,&m);
    while(m--){
        scanf("%u",&p),wil=p-wil-1;
        for(uint j=0;j<=30;j++)if(wil>>j&1)
        {
            User[0]=A[j][0][0]*Ans[0]+A[j][0][1]*Ans[1]+A[j][0][2]*Ans[2];
            User[1]=A[j][1][0]*Ans[0]+A[j][1][1]*Ans[1]+A[j][1][2]*Ans[2];
            User[2]=A[j][2][0]*Ans[0]+A[j][2][1]*Ans[1]+A[j][2][2]*Ans[2];
            Ans[0]=User[0],Ans[1]=User[1],Ans[2]=User[2];
        }
        wil=p;
        User[0]=B[0][0]*Ans[0]+B[0][1]*Ans[1]+B[0][2]*Ans[2];
        User[1]=B[1][0]*Ans[0]+B[1][1]*Ans[1]+B[1][2]*Ans[2];
        User[2]=B[2][0]*Ans[0]+B[2][1]*Ans[1]+B[2][2]*Ans[2];
        Ans[0]=User[0],Ans[1]=User[1],Ans[2]=User[2];
    }
    wil=n-wil-1;
    for(uint j=0;j<=30;j++)if(wil>>j&1)
    {
        User[0]=A[j][0][0]*Ans[0]+A[j][0][1]*Ans[1]+A[j][0][2]*Ans[2];
        User[1]=A[j][1][0]*Ans[0]+A[j][1][1]*Ans[1]+A[j][1][2]*Ans[2];
        User[2]=A[j][2][0]*Ans[0]+A[j][2][1]*Ans[1]+A[j][2][2]*Ans[2];
        Ans[0]=User[0],Ans[1]=User[1],Ans[2]=User[2];
    }
    Ans[0].println();
    return 0;
}
```


---

## 作者：苹果蓝17 (赞：5)

写一个不需要任何组合意义的暴力代数做法。

先考虑没有限制的情况。

先写出 $F(x)=\sum_{i=0} i^2 x^i$ 的封闭形式。由 $k^2=2\dbinom{k+2}{2}-3\dbinom{k+1}{1}+\dbinom{k}{0}$，可以得到：

$$F(x)=\dfrac{2}{(1-x)^3}-\dfrac{3}{(1-x)^2}+\dfrac{1}{1-x}$$

于是答案的生成函数为：

$$G(x)=\dfrac{1}{1-F(x)}=\dfrac{(1-x)^3}{-x^3+2x^2-4x+1}$$

化为线性递推形式即：

$$g_0=0,g_1=1,g_2=5,g_k=4g_{k-1}-2g_{k-2}+g_{k-3}$$

记矩阵 $M$ 的第三行第一列值为 $v(M)$。

对于限制，容斥钦定一个点集 $S$ 必须经过。考虑设 $f_i$ 表示考虑前 $i$ 个点，钦定经过第 $i$ 个点的方案数，有：

$$f_i=v\big( -\sum\limits_{j=0}^{i-1} f_j A^{x_i-x_j} P \big)=v\big( A^{x_i} (\sum\limits_{j=0}^{i-1} f_j A^{-x_j}) P \big)$$

$A$ 是有逆矩阵的，前缀和优化即可。时间复杂度 $O(m \log n)$。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,mod=1e9+7;
int n,m;
int a[N];

struct mat{
	int M[3][3];
	mat(int x=0){
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				M[i][j]=(i==j)*x;
	}
};
mat operator +(mat X,mat Y){
	mat T;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			T.M[i][j]=(X.M[i][j]+Y.M[i][j])%mod;
	return T;
}
mat mult(mat X,int x){
	mat T;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			T.M[i][j]=1ll*X.M[i][j]*x%mod;
	return T;
}
mat operator *(mat X,mat Y){
	mat T;
	for(int k=0;k<3;k++)
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				T.M[i][j]=(T.M[i][j]+1ll*X.M[i][k]*Y.M[k][j]%mod)%mod;
	return T;
}

mat ksm(mat A,int x){
	mat T(1);
	while(x){
		if(x & 1) T=T*A;
		A=A*A;
		x>>=1;
	}
	return T;
}

int f[N];
mat G[N];

int main(){
	cin>>n>>m;
	mat P;
	P.M[0][0]=5,P.M[1][0]=1,P.M[2][0]=0;
	mat A;
	A.M[0][0]=4,A.M[0][1]=mod-2,A.M[0][2]=1,A.M[1][0]=1,A.M[2][1]=1;
	mat iA;
	iA.M[2][0]=1,iA.M[2][1]=mod-4,iA.M[2][2]=2,iA.M[1][2]=1,iA.M[0][1]=1;
	
	for(int i=1;i<=m;i++) cin>>a[i];
	a[++m]=n;
	
	f[0]=mod-1;
	G[0]=(mat){1};
	for(int i=1;i<=m;i++){
		f[i]=(ksm(A,a[i])*G[i-1]*P).M[2][0];
		G[i]=G[i-1]+mult(ksm(iA,a[i]),mod-f[i]);
	}
	cout<<f[m];
}
```

---

## 作者：hwk0518 (赞：5)

令$f[i]$表示以只考虑$[0,i]$的木板的答案。

容易写出：

$f[i]=\sum_{j=0}^{i-1} f[j]*(i-j)^2$

发现不能作为木板交界处的点很少，所以很多点的转移是类似的。可以使用矩阵快速幂。

令$(i-j)=x[j]$，则

$f[i]=\sum_{j=0}^{i-1} f[j]*x[j]^2$

如果$f[i]$是一个标记点，则

$f[i+1]=\sum_{j=0}^{i-1} f[j]*(x[j]+1)^2$

$=\sum_{j=0}^{i-1} f[j]*x[j]^2+2*f[j]*x[j]+f[j]$

如果不是，则

$f[i+1]=\sum_{j=0}^{i-1} f[j]*(x[j]+1)^2+f[i]$

$=2*f[j]*x[j]^2+2*f[j]*x[j]+f[j]$

于是令：

$s[i]=\sum_{j=0}^{i-1} f[j]*x[j]^2$

$t[i]=\sum_{j=0}^{i-1} 2*f[j]*x[j]$

$u[i]=\sum_{j=0}^{i-1} f[j]$

则转移矩阵如下：

标记点：

$\left[\begin{matrix}s_i & t_i & u_i \end{matrix}\right]$

$=\left[\begin{matrix}1 & 0 & 0 \\1 & 1 & 0 \\1 & 2 & 1\\ \end{matrix}\right]*\left[\begin{matrix}s_{i-1} & t_{i-1} & u_{i-1} \end{matrix}\right]$

非标记点的$u_i$要加上$f_i$，即：

$\left[\begin{matrix}s_i & t_i & u_i \end{matrix}\right]$

$=\left[\begin{matrix}1 & 0 & 1 \\1 & 1 & 1 \\1 & 2 & 2\\ \end{matrix}\right]*\left[\begin{matrix}s_{i-1} & t_{i-1} & u_{i-1} \end{matrix}\right]$

初始矩阵为：

$\left[\begin{matrix}0 & 0 & 1 \end{matrix}\right]$

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int M=3;
const int N=1e5+5;
const int mod=1e9+7;
struct mat
{
	int a[M][M];
};
mat hv,uhv,sig;
int len,n,s[N],t[N];

namespace MATHEMATICS
{
	int add(int x,int y)
	{
		int ret=x+y;
		if(ret>=mod) ret-=mod;
		return ret;
	}
	int mi(int x,int y)
	{
		int ret=x-y;
		if(ret<0) ret+=mod;
		return ret;
	}
	
	void inc(int &x,int y)
	{
		x+=y;
		if(x>=mod) x-=mod;
	}
	void dec(int &x,int y)
	{
		x-=y;
		if(x<0) x+=mod;
	}
	
	int mul(int x,int y)
	{
		return 1LL*x*y%mod;
	}
	int F_p(int x,int y)
	{
		int ret=1,bas=x;
		while(y)
		{
			if(y&1) ret=mul(ret,bas);
			bas=mul(bas,bas);
			y>>=1;
		}
		return ret;
	}
}
using namespace MATHEMATICS;

namespace MAT
{
	void clear(mat &A)
	{
		int i,j;
		for(i=0;i<3;++i)
			for(j=0;j<3;++j)
				A.a[i][j]=0;
	}
	void reset(mat &A)
	{
		int i,j;
		clear(A);
		for(i=0;i<3;++i) A.a[i][i]=1;
	}
	
	mat operator * (mat x,mat y)
	{
		mat ret;clear(ret);
		int i,j,k;
		for(i=0;i<3;++i)
			for(j=0;j<3;++j)
				for(k=0;k<3;++k)
					inc(ret.a[i][j],mul(x.a[i][k],y.a[k][j]));
		return ret;
	}
	
	mat F_p(mat x,int y)
	{
		mat ret,bas;
		reset(ret),bas=x;
		while(y)
		{
			if(y&1) ret=ret*bas;
			bas=bas*bas;
			y>>=1;
		}
		return ret;
	}
}
using namespace MAT;

void init()
{
	int i;
	scanf("%d%d",&len,&n);
	for(i=1;i<=n;++i) scanf("%d",&t[i]);
	for(i=1;i<=n;++i) s[i]=t[i]-t[i-1]-1;
	s[++n]=len-t[n-1];
}

void prework()
{
	uhv.a[0][0]=1,uhv.a[0][1]=0,uhv.a[0][2]=0;
	uhv.a[1][0]=1,uhv.a[1][1]=1,uhv.a[1][2]=0;
	uhv.a[2][0]=1,uhv.a[2][1]=2,uhv.a[2][2]=1;
	
	int i,j;
	for(i=0;i<3;++i)
		hv.a[i][0]=hv.a[i][1]=0,hv.a[i][2]=1;
	
	for(i=0;i<3;++i)
		for(j=0;j<3;++j)
			hv.a[i][j]+=uhv.a[i][j];
}

void work()
{
	int i,j,k;
	mat pr;reset(pr);
	for(i=1;i<=n;++i)
	{
		pr=pr*F_p(hv,s[i]);
		if(i<n) pr=pr*uhv;
	}
	printf("%d\n",pr.a[2][0]);
}

int main()
{
	init();prework();work();
	return 0;
}

```

---

## 作者：asuldb (赞：4)

[题目](https://www.luogu.com.cn/problem/AT2371)

模型转化；要是转化不出来就啥都不会了。

这个$\prod_{i=1}^ka_i^2$看起来并不好直接处理，我们考虑$a_i^2$的组合意义，就是**把两个可区分的球放到$a_i$个可区分的盒子，允许一个盒子放多个的方案数**；于是我们可以搞一个dp状物，设$f_{i,j}$表示处理了前$i$个位置，当前这一段共放了$j$个球，转移的话就枚举一下这个位置放哪几个球，以及是否要另起一段，由于第二维只有$0/1/2$，所以复杂度是$O(n)$的。

再来考虑一下关键点的限制，发现这个关键点的限制本质上就是使得这次转移不能另起一段，于是也很好处理。

不难发现这两种转移都可以矩乘优化，由于两种转移的矩阵不一样，关键点个数只有$10^5$级别，所以我们用矩阵快速幂处理没有关键点的转移，就能做到$O(w^3m\log n)$的复杂度，$w$是矩阵大小；但是不难发现我们并不需要最后的矩阵，我们要的只是一个向量乘矩阵的结果，于是我们可以预处理所有矩阵的$2$次幂，拿一个向量直接乘过去就好了，由于向量乘矩阵的是$O(w^2)$的，所以复杂度是$O(w^3\log n+w^2m\log n)$。看起来好像没快多少，但少一个$w$就跑到了最优解。

代码

```cpp
#include<bits/stdc++.h>
#define re register
inline int read() {
	char c=getchar();int x=0;while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
const int mod=1e9+7;const int maxn=1e5+5;
int n,m,b[maxn];
struct Vector{int v[3];}D,ans;
struct Matrix{int a[3][3];}C,pw[32],G;
inline int qm(int x) {return x>=mod?x-mod:x;}
inline Matrix operator*(const Matrix &A,const Matrix &B) {
	for(re int i=0;i<3;i++)
		for(re int j=0;j<3;j++)C.a[i][j]=0;
	for(re int k=0;k<3;k++)
		for(re int i=0;i<3;i++)
			for(re int j=0;j<3;j++)C.a[i][j]=qm(C.a[i][j]+1ll*A.a[i][k]*B.a[k][j]%mod);
	return C;
}
inline Vector operator^(const Vector &A,const Matrix &B) {
	for(re int i=0;i<3;i++)D.v[i]=0;
	for(re int i=0;i<3;i++) 
		for(re int j=0;j<3;j++)D.v[i]=qm(D.v[i]+1ll*A.v[j]*B.a[i][j]%mod);
	return D;
}
inline void mul(int x) {
	for(re int i=0;(1<<i)<=x;i++) 
		if(x>>i&1) ans=ans^pw[i];
}
int main() {
	n=read(),m=read();ans.v[0]=1;
	for(re int i=1;i<=m;i++)b[i]=read();
	std::sort(b+1,b+m+1);
	for(re int i=0;i<3;i++)
		for(re int j=0;j<3;j++) pw[0].a[i][j]=1;
	pw[0].a[0][0]=pw[0].a[1][0]=2,pw[0].a[1][2]=0;
	for(re int i=1;(1<<i)<=n;++i) pw[i]=pw[i-1]*pw[i-1];
	G.a[1][0]=2;G.a[0][0]=G.a[1][1]=G.a[2][2]=G.a[2][0]=G.a[2][1]=1;
	for(re int i=1;i<=m;i++) mul(b[i]-b[i-1]-1),ans=ans^G;
	mul(n-b[m]);printf("%d\n",ans.v[2]); 
	return 0;
}
```

---

## 作者：lsj2009 (赞：2)

### Solution

很巧妙的转换！

看到 $a_i^2$，我们考虑进行一个非常厉害的转换：

> 给定一个长为 $n$ 的序列，你需要将其分成若干段，其中每段需要恰好放两个互不相同的小球，位置可以重叠，求方案总数。

对于连续的长为 $a_i$ 一段，放两个互不相同的小球的方案总数恰为 $a_i^2$，而对于一共 $k$ 段，由于每段互相独立，根据乘法原理，恰有 $\prod\limits_{i=1}^k a_i^2$ 种方案，与题目所求相符。

至于为什么要进行这样一个转换，是因为可以方便我们进行更简单的 dp：考虑设 $f_{i,j}$ 为考虑前 $i$ 个位置，并且当前这一段已经放了 $j\in[0,2]$ 个小球的方案总数，我们不妨先去掉有一些点不能断开的限制，设计 dp 方程：

1. $f_{i,0}\gets f_{i-1,0}+f_{i-1,2}$，分别表示的是否断 $(i-1,i)$ 这条边。
2. $f_{i,1}\gets 2\times f_{i-1,0}+f_{i-1,1}+2\times f_{i-1,2}$，其中 $2\times f_{i-1,0}$ 表示不断边且在 $i$ 处放小球，$f_{i-1,1}$ 表示不断边且不在 $i$ 处放小球，$2\times f_{i-1,2}$ 断边且在 $i$ 处放小球，其中 $\times 2$ 是因为可以放两个球的任意一个。
3. $f_{i,2}\gets f_{i-1,0}+f_{i-1,1}+f_{i-1,2}+f_{i-1,2}$，其中 $f_{i-1,0}$ 表示不断边且在 $i$ 处放两个小球，$f_{i-1,1}$ 表示不断边且在 $i$ 处放还没有放的那个小球，后面两个 $f_{i-1,2}$ 分别表示不断边且不放小球和断边且放两个小球。

容易把 $f_{i-1}\to f_i$ 这种形式的转移列成矩阵乘法的形式：

$$\begin{bmatrix}
 1 & 0 & 1\\
 2 & 1 & 2\\
 1 & 1 & 2
\end{bmatrix}
\begin{bmatrix}
 f_{i-1,0}\\
 f_{i-1,1}\\
 f_{i-1,2}
\end{bmatrix}
\to
\begin{bmatrix}
 f_{i,0}\\
 f_{i,1}\\
 f_{i,2}
\end{bmatrix}$$

而对于那些规定了某些边不能断掉的约束，我们只需要去掉断边的转移即可，同样容易得到转移矩阵：

$$\begin{bmatrix}
 1 & 0 & 0\\
 2 & 1 & 0\\
 1 & 1 & 1
\end{bmatrix}
\begin{bmatrix}
 f_{i-1,0}\\
 f_{i-1,1}\\
 f_{i-1,2}
\end{bmatrix}
\to
\begin{bmatrix}
 f_{i,0}\\
 f_{i,1}\\
 f_{i,2}
\end{bmatrix}$$

然后就做完了，矩阵快速幂加速可以做到复杂度 $\Theta(3^3m\log{n})$。

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int MOD=1e9+7;
void add(int &a,int b) {
	a+=b;
	if(a>=MOD)
		a-=MOD;
}
struct matrix {
	static const int n=3;
	int c[n+1][n+1];
	matrix() {
		cl(c,0);
	}
	void init() {
		rep(i,1,n)
			c[i][i]=1;
	}
	matrix operator * (const matrix &tmp) const {
		matrix res;
		rep(i,1,n) {
			rep(j,1,n) {
				rep(k,1,n)
					add(res.c[i][j],1ll*c[i][k]*tmp.c[k][j]%MOD);
			}
		}
		return res;
	}
}; matrix g1,g2,res;
void init() {
	g1.c[1][1]=1; g1.c[1][2]=0; g1.c[1][3]=1;
	g1.c[2][1]=2; g1.c[2][2]=1; g1.c[2][3]=2;
	g1.c[3][1]=1; g1.c[3][2]=1; g1.c[3][3]=2;
	g2.c[1][1]=1; g2.c[1][2]=0; g2.c[1][3]=0;
	g2.c[2][1]=2; g2.c[2][2]=1; g2.c[2][3]=0;
	g2.c[3][1]=1; g2.c[3][2]=1; g2.c[3][3]=1;
	res.c[1][1]=1;
}
matrix qpow(matrix a,int b) {
	matrix res,base=a; res.init();
	while(b) {
		if(b&1)
			res=res*base;
		base=base*base; b>>=1;
	}
	return res;
}
void solve() {
	init();
	int n,m;
	scanf("%d%d",&n,&m);
	int last=0;
	while(m--) {
		int x;
		scanf("%d",&x);
		res=g2*(qpow(g1,x-last)*res);
		last=x+1;
	}
	res=qpow(g1,n-last)*res;
	printf("%d\n",res.c[3][1]);
}
signed main() {
    int testcase=1;
    while(testcase--)
        solve();
    return 0;
}
```

---

## 作者：Resurgammm (赞：2)

> 给定一个长度为 $n$ 的木板，在若干整数位置断开将它分为若干段，要求其中 $m$ 个位置不能成为断点（称为标记点），定义一种划分方案的贡献为最终所有线段长度乘积的平方，求所有方案贡献之和。

~~组合意义天地灭，代数推导保平安。~~

设 $f_i$ 为考虑前 $i$ 个格子并在 $i$ 和 $i+1$ 放隔板的方案数，显然有：

$$f_i=\begin{cases}\sum\limits_{j=0}^{i-1}f_j\times(i-j)^2 & \text{i is a markpoint} \\ 0 & \text{i is not a markpoint}\end{cases}$$

考虑优化，假设 $i+1$ 不是标记点，那么有：

$$\begin{aligned}f_{i+1}&=\sum\limits_{j=0}^{i}f_j\times(i+1-j)^2 \\ &=\sum\limits_{j=0}^{i-1}f_j\times(i+1-j)^2+f_i \\ &=\sum\limits_{j=0}^{i-1}f_j\times(i-j)^2+2\sum\limits_{j=0}^{i-1}f_j\times(i-j)+\sum\limits_{j=0}^{i-1}f_j+f_i\end{aligned}$$

设 $a_i=\sum\limits_{j=0}^{i-1}f_j,b_i=\sum\limits_{j=0}^{i-1}f_j\times(i-j),c_i=\sum\limits_{j=0}^{i-1}f_j\times(i-j)^2$，有：

$$\begin{cases}f_i=c_i \\ f_{i+1}=a_i+2b_i+c_i\end{cases}$$

假设已经知道了 $a_i,b_i,c_i$，只需能求出 $a_{i+1},b_{i+1},c_{i+1}$ 就能实现方程的转移，分类讨论一下：

* $\text{i is a markpoint}$

	$$\begin{cases}a_{i+1}=\sum\limits_{j=0}^{i-1}f_j=a_i \\ b_{i+1}=\sum\limits_{j=0}^{i-1}f_j\times(i+1-j)=a_i+b_i \\ c_{i+1}=f_{i}=a_i+2b_i+c_i\end{cases}$$

* $\text{i is not a markpoint}$

	$$\begin{cases}a_{i+1}=\sum\limits_{j=0}^{i-1}f_j+f_i=a_i+c_i \\ b_{i+1}=\sum\limits_{j=0}^{i-1}f_j\times(i+1-j)+f_i=a_i+b_i+c_i \\ c_{i+1}=f_{i+1}=a_i+2b_i+2c_i\end{cases}$$

显然可以矩阵快速幂优化，那么是不是关键点的转移矩阵分别为 $\begin{bmatrix}1 & 0 & 0 \\ 1 & 1 & 0 \\ 1 & 2 & 1\end{bmatrix}$ 和 $\begin{bmatrix}1 & 0 & 1 \\ 1 & 1 & 1 \\ 1 & 2 & 1\end{bmatrix}$。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define fir first
#define sec second
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout)
	#define fill(a,b,c,d) memset(a,b,sizeof(c)*(d+1))
	#define fillall(x,y) memset(x,y,sizeof(x))
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<1)+(w<<3)+(ch^48); ch=getchar();}
		return w*f;
	}
}
using namespace IO;
namespace CL{

	const int mod=1e9+7;

	int n,m;
	namespace Matrix{
		struct matrix{
			ll p[4][4];
			matrix(){fillall(p,0);}
			inline void build(){for(int i=1;i<=3;i++) p[i][i]=1;}
			inline matrix operator *(const matrix &x)const{
				matrix res;
				for(int i=1;i<=3;i++)
					for(int k=1;k<=3;k++) if(p[i][k])
						for(int j=1;j<=3;j++)
							res.p[i][j]=(res.p[i][j]+p[i][k]*x.p[k][j])%mod;
				return res;
			}
		}t1,t2,f,tmp;
		inline matrix qpow(matrix x,int y){
			matrix res; res.build();
			for(;y;y>>=1,x=x*x) if(y&1) res=res*x;
			return res;
		}
	}using namespace Matrix;

	inline int main(){
		n=read(),m=read();
		t1.p[1][1]=t1.p[1][3]=t1.p[2][1]=t1.p[2][2]=t1.p[2][3]=t1.p[3][1]=1,t1.p[3][2]=t1.p[3][3]=2;
		t2.p[1][1]=t2.p[2][1]=t2.p[2][2]=t2.p[3][1]=t2.p[3][3]=1,t2.p[3][2]=2;
		f.p[1][1]=f.p[2][1]=f.p[3][1]=1;
		int lst=1;
		for(int i=1;i<=m;i++){
			int x=read();
			tmp=qpow(t1,x-lst),f=tmp*f,f=t2*f;
			lst=x+1;
		}
		tmp=qpow(t1,n-lst),f=tmp*f;
		printf("%lld\n",f.p[3][1]);
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：5k_sync_closer (赞：1)

把 $\prod a_i^2$ 转化成组合意义，即在每个正方形的底边中放不同的两个球的方案数。

设 $f_{i,j}$ 表示考虑到第 $i$ 个点，最后一条底边放了 $j$ 个球，

若第 $i$ 个点被标记，则：

$$
\begin{aligned}
&f_{i+1,0}=f_{i,0}\\
&f_{i+1,1}=2f_{i,0}+f_{i,1}\\
&f_{i+1,2}=f_{i,0}+f_{i,1}+f_{i,2}
\end{aligned}
$$

若第 $i$ 个点没有被标记，则：

$$
\begin{aligned}
&f_{i+1,0}=f_{i,0}+f_{i,2}\\
&f_{i+1,1}=2f_{i,0}+f_{i,1}+2f_{i,2}\\
&f_{i+1,2}=f_{i,0}+f_{i,1}+2f_{i,2}
\end{aligned}
$$

矩阵加速即可。

```cpp
#include <cstdio>
#include <cstring>
#define M 1000000007
#define int long long
int n, m, a[100050];
struct S
{
    int a[3][3];
    S() { memset(a, 0, sizeof a); }
    S operator*(S b)
    {
        S c;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                for (int k = 0; k < 3; ++k)
                    c.a[i][j] += a[i][k] * b.a[k][j];
                c.a[i][j] %= M;
            }
        return c;
    }
} z, x, y;
S P(S x, int y)
{
    S q;
    for (int i = 0; i < 3; ++i)
        q.a[i][i] = 1;
    for (; y; y >>= 1, x = x * x)
        if (y & 1)
            q = q * x;
    return q;
}
signed main()
{
    for (int i = 0; i < 3; ++i)
        z.a[i][i] = 1;
    x.a[0][0] = x.a[0][2] = x.a[1][1] = x.a[1][2] = x.a[2][0] = y.a[0][0] = y.a[0][2] = y.a[1][1] = y.a[1][2] = y.a[2][2] = 1;
    x.a[0][1] = x.a[2][1] = x.a[2][2] = y.a[0][1] = 2;
    scanf("%lld%lld", &n, &m);
    if (!m)
        return !printf("%lld", P(x, n).a[0][2]);
    a[0] = -1;
    for (int i = 1; i <= m; ++i)
        scanf("%d", a + i), z = z * P(x, a[i] - a[i - 1] - 1) * y;
    z = z * P(x, n - a[m] - 1);
    printf("%lld", z.a[0][2]);
    return 0;
}
```


---

## 作者：xuantianhao (赞：0)

# [Placing Squares](https://www.luogu.com.cn/problem/AT_agc013_e)

关键是将问题从抽象的“正方形面积”转为具象的形式：一段长度为 $d$ 的区间，有两个不同的小球要放进去，则总放置方案就是 $d^2$，且不同的区间间方案是通过乘法原理结合的，刚好是题目中 $\prod d^2$ 的形式。

于是我们可以设计 DP：设 $f_{i,j}$ 表示前 $i$ 个格子中，最后一段中有 $j$ 个球。明显 $j\in[0,2]$。

常规的位置可以直接矩阵快速幂解决；然而对于题目中给出的特殊位置，需要用特殊的矩阵处理。

因此复杂度 $O(3^3m\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100100];
const int mod=1e9+7;
struct Matrix{
    int g[3][3];
    int*operator[](int x){return g[x];}
    Matrix(){memset(g,0,sizeof(g));}
    friend Matrix operator*(Matrix x,Matrix y){
        Matrix z;
        for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				for(int k=0;k<3;k++){
					(z[i][j]+=1ll*x[i][k]*y[k][j]%mod)%=mod; 
				}
			}
		}
        return z;
    }
}A,B,R;
Matrix ksm(Matrix x,int y){
    Matrix z;
    z[0][0]=z[1][1]=z[2][2]=1;
    for(;y;y>>=1,x=x*x) if(y&1) z=z*x;
    return z; 
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
	a[m+1]=n;
    A[0][1]=2,A[0][2]=A[1][2]=1;
    A[2][0]=1,A[2][1]=A[2][2]=2;
    A[0][0]=A[1][1]=1;
    B[0][1]=2,B[0][2]=B[1][2]=1;
    B[0][0]=B[1][1]=B[2][2]=1;
    R=ksm(A,a[1]);
    for(int i=1;i<=m;i++){
		R=R*B;
		R=R*ksm(A,a[i+1]-a[i]-1);
	}
    printf("%d",R[0][2]);
    return 0;
} 
```

---

## 作者：jucason_xu (赞：0)

我们考虑转化题意，一个合法的将 $1$ 到 $N$ 划分成长度依次为 $a_1,a_2,\cdots a_k$ 的小区间，对答案的贡献为 $a_1^2a_2^2\cdots a_k^2$。

化贡献为方案数，我们在每个长度为 $a_i$ 的小区间内放置两个独立的标记，每个合法的划分方案对放置标记方案种数的贡献恰好是其对最终答案的贡献权值。并且每个划分方案的标记方案互不重合。

然后我们就可以 $dp$，设 $dp_{i,mask}$ 表示目前处理到第 $i$ 个小格子，目前区间已经安放标记的状态为 $mask$ 的方案数量。其中 $mask$ 是一个长度为 $2$ 的二进制串，表示第一个和第二个标记分别有没有被放下。

然后考虑从 $dp_i$ 到 $dp_{i+1}$ 的转移，其实就是讨论：

+ 在 $i$ 和 $i+1$ 之间是否放置划分点

+ 在 $i+1$ 这个位置怎么放标记

首先是不放置划分点，那么每个 $mask$ 就只能转移到 $newmask\wedge mask=mask$ 的状态，也就是 $\{0\rightarrow 0,1,2,3\}\{1\rightarrow 1,3\}\{2\rightarrow 2,3\}\{3\rightarrow 3\}$。

然后是放置划分点，首先上一个要已经放完标记，所以只能从 $3$ 转移过去，而下面变成 $0$，$i+1$ 随便放，也就是 $\{3\rightarrow 0,1,2,3\}$。

我们发现，这样就可以矩阵快速幂了，在 $i\in X$ 的时候，转移就是矩阵

$$D_1=\begin{pmatrix}
 1 & 1 & 1 & 1\\
 0 & 1 & 0 & 1\\
 0 & 0 & 1 & 1\\
 0 & 0 & 0 & 1
\end{pmatrix}$$

在 $i\notin X$ 的时候，就加上放置划分点的转移变成

$$D_2=\begin{pmatrix}
 1 & 1 & 1 & 1\\
 0 & 1 & 0 & 1\\
 0 & 0 & 1 & 1\\
 1 & 1 & 1 & 2
\end{pmatrix}$$

注意两种 $3$ 到 $3$ 的转移是分开的，所以权值是 $2$。

然后用 $X$ 中的数分段，段内部 $D_2$ 矩阵快速幂，段和段之间用 $D_1$ 乘上即可。

复杂度 $O(4^3m\log n)$（事实上可以做到 $3\times 3$ 的矩阵，但是转移不如 $4\times 4$ 来得直观）~~（但是跑得实在是很慢啊）~~

```cpp

const int P=1000000007;
struct matrix{
	vt<vt<int> >a;
	matrix(){};
	matrix(int n,int m){
		vt<vt<int> >vv(n,vt<int>(m,0));
		a=vv;
	}
	matrix operator *(const matrix b)const{
		matrix res;
		vt<vt<int> >vv(a.size(),vt<int>(b.a[0].size(),0));
		rd(i,(int)a.size())rd(j,(int)b.a[0].size())rd(k,(int)b.a.size()){
			vv[i][j]=(vv[i][j]+1ll*a[i][k]*b.a[k][j]%P)%P;
		}
		res.a=vv;
		return res;
	}
};
matrix fpow(matrix a,ll k){
	if(k==1)return a;
	matrix res=fpow(a,k>>1);
	if(k&1)return res*res*a;
	return res*res;
}
int n,m,x[100005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	rp(i,m)cin>>x[i];x[m+1]=n;x[0]=-1;
	matrix dp(1,4);
	dp.a[0][0]=1;
	matrix tf(4,4),ty(4,4);
	rd(i,4)rd(j,4)if((i&j)==i)tf.a[i][j]=1;
	ty=tf;
	rd(i,4)ty.a[3][i]=1;
	ty.a[3][3]=2;
	matrix bb=fpow(ty,2);
	rep(i,1,m+1){
		int len=x[i]-x[i-1]-1;
		if(len>0)dp=dp*fpow(ty,len);
		if(i!=m+1)dp=dp*tf;
	}cout<<dp.a[0][3]<<endl;
	return 0;
}
//Crayan_r
```


---

