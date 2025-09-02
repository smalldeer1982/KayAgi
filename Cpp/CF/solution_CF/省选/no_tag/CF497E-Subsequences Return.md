# Subsequences Return

## 题目描述

Assume that $ s_{k}(n) $ equals the sum of digits of number $ n $ in the $ k $ -based notation. For example, $ s_{2}(5)=s_{2}(101_{2})=1+0+1=2 $ , $ s_{3}(14)=s_{3}(112_{3})=1+1+2=4 $ .

The sequence of integers $ a_{0},...,a_{n-1} $ is defined as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF497E/6cf1a2e064eafad1586b721275139d1721b088bf.png). Your task is to calculate the number of distinct subsequences of sequence $ a_{0},...,a_{n-1} $ . Calculate the answer modulo $ 10^{9}+7 $ .

Sequence $ a_{1},...,a_{k} $ is called to be a subsequence of sequence $ b_{1},...,b_{l} $ , if there is a sequence of indices $ 1<=i_{1}&lt;...&lt;i_{k}<=l $ , such that $ a_{1}=b_{i1} $ , ..., $ a_{k}=b_{ik} $ . In particular, an empty sequence (i.e. the sequence consisting of zero elements) is a subsequence of any sequence.

## 说明/提示

In the first sample the sequence $ a_{i} $ looks as follows: $ (0,1,1,0) $ . All the possible subsequences are:

 $ (),(0),(0,0),(0,1),(0,1,0),(0,1,1),(0,1,1,0),(1),(1,0),(1,1),(1,1,0). $ In the second sample the sequence $ a_{i} $ looks as follows: $ (0,1,2,3,4,5,6) $ . The subsequences of this sequence are exactly all increasing sequences formed from numbers from 0 to 6. It is easy to see that there are $ 2^{7}=128 $ such sequences.

## 样例 #1

### 输入

```
4 2
```

### 输出

```
11
```

## 样例 #2

### 输入

```
7 7
```

### 输出

```
128
```

# 题解

## 作者：zombie462 (赞：9)

## 题解

$\text{update}$：一点 $\text{markdown}$ 挂了，修个锅。

$\text{update}$：又有一点 $\text{markdown}$ 挂了，修个锅。

看了一下 $\texttt{Codeforces}$ 的那篇官方题解，理解了一下写了下面的这篇东西，大体的思路基本按那篇官方题解展开，但也不是纯粹的翻译。

对于一个字符串而言，如何计算它不同子序列的个数：

当我们把某一个字符附加到一个字符串上面去，并且每次都计算以前未曾出现的子序列的数量。

比如，在字符串 $s$ 后面附加一个字符 $c$，以 $c$ 结尾的子序列和 $s$ 中的子序列一样多。

我们把这些新构成的子序列加到 $s$ 的子序列数目中去，作为 $s+c$ 的子序列个数。现在每个 $s+c$ 的子序列仅计数一次，除了那些以 $c$ 结尾但是已曾在 $s$ 中出现的子序列。这些子序列将被计算 $2$ 次。

因此，新字符串 $s+c$ 中的子序列总数 $=$ 旧字符串 $s$ 中的子序列总数 $\times 2$ $-$ 以 $c$ 结尾的旧字符串 $s$ 中的子序列总数。

这样就有了以下方案：

对于每个字符 $c$，储存以 $c$ 结尾的子序列数量，表示为 $f_c$，现在 $f_c=(\sum f_c)+1$，并且其它的 $f_{x,x\neq c}$ 不改变。

举个例子：

```
empty	--	(0,0)
0		--	(0+0+1=1,0)
01		--	(1,1+0+1=2)
011		--	(1,1+2+1=4)
0110	--	(1+4+1=6,4)
...		--	...
```

如果我们把 $f_c$ 都放在一个向量中，并总是附加一个等于 $1$ 的值。显然地，在字符串中附加一个字符会改变这个向量，相当于把它和某个矩阵相乘。这样的话，我们就可以把每个字符变成一个矩阵，把每个字符串也变成一个矩阵。这样一个字符串和一个字符相连等价于求两个矩阵的乘积。

现在，考虑一个序列 $a_i$，和它长度为 $k^m$ 的前缀，把这个前缀分成长度为 $k$ 个长度 $k^{m-1}$ 的部分。为了求出这些部分中的第 $x$ 项（从 $0$ 开始计数），我们可以通过将 $x$ 对 $k$ 取模并将其加到第 $0$ 部分中的所有元素上。我们通过这样的方式来计算出这样长度为 $k^m$ 的前缀矩阵，并且计算出通过向所有前缀元素中加入 $x$ 而获得的所有字符串。记这样的矩阵为 $A_{m,x}$。

考虑 $A_{m,x}$ 的性质，当 $m>0$ 时，$A_{m,x}=A_{m-1,x}A_{m-1,(x+1)\text{ mod }k}\cdots A_{m-1,(x+k-1)\text{ mod }k}$。

通过这种方式，我们可以在 $O(\log_kn\times k\times k\times k^3)$ 的时间复杂度内求出所有的 $A_{m,x}(m\leq \log_kn,0\leq x\leq k-1)$。这个复杂度是 $O(\dfrac{\log n\times k^5}{\log k})$ 的。既然求出了所有的 $A_{m,x}$，我们可以对其中的某些矩阵按照特定顺序进行一些乘法运算，从而得到对于 $a_i$ 的长度为 $n$ 的前缀，而通过这个我们可以轻而易举地求出答案。

但是，这个复杂度是卡不过去的。考虑如何加速 $A_{m,x}=A_{m-1,x}A_{m-1,(x+1)\text{ mod }k}\cdots A_{m-1,(x+k-1)\text{ mod }k}$ 这个式子。这个式子的右边可以分成这样的形式：$A_{m-1,x}\cdots A_{m-1,k-1}\times A_{m-1,0}\cdots A_{m-1,x-1}$（如果 $x=0$，则忽略第二部分）。

计算 $A_{m,x}$ 所有的前缀 $P_{m,x}$ 和后缀 $S_{m,x}$。其中 $P_{m,x}=A_{m,0}\cdots A_{m,x-1}$，$S_{m,x}=A_{m,x}\cdots A_{m,k-1}$。则 $A_{m,x}=S_{m-1,x}P_{m-1,x}$。因此，我们只要在 $O(k)$ 次的矩乘中算出所有的 $P_{m-1,x}$ 和 $S_{m-1},x$，并通过一次矩阵乘法，就能求出 $A_{m,x}$ 了。

这样，我们就可以把时间复杂度缩减到 $O(\dfrac{\log n\times k^4}{\log k})$ 了。

 ```cpp
#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define N 33
#define int long long
int bin[N*2],n,m;
struct matrix{ //矩阵乘法模板
    int mat[N][N];
    inline matrix operator * (const matrix &a) const {
        matrix res;
        memset(res.mat,0,sizeof(res.mat));
        for (int i=0;i<=m;++i){
            for (int j=0;j<=m;++j){
                for (int k=0;k<=m;++k){
                    res.mat[i][j]=(res.mat[i][j]+mat[i][k]*a.mat[k][j])%mod;
                }
            }
        }
        return res;
    }
}ans,P[N*2][N],S[N*2][N],A[N*2][N];
//ans是寄存答案的矩阵，P是前缀矩阵，S是后缀矩阵，A就是题解中的A矩阵
int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0' || ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9'){
        x=x*10+ch-'0';ch=getchar();
    }
    return x*f;
}
signed main(){
    n=read(),m=read();
    int n2=n,len=-1;
    while (n2){ //求出n的二进制表示
        len++;bin[len]=n2%m;n2=n2/m;
    }
    len++;
    for (int i=0;i<=m;++i) ans.mat[0][i]=1; //给答案矩阵赋一个初始值
    for (int i=0;i<len;++i){
        for (int j=0;j<=m;++j) A[i][0].mat[j][j]=1; //给A[i][0]赋一个初始值
        if (!i){ //i==0的情况与众不同，类似于初始值，只不过这个初始值稍微麻烦一些
            for (int j=0;j<m;++j){
                A[i][j].mat[m][m]=1;
                for (int k=0;k<m;++k){
                    if (k!=j){
                        A[i][j].mat[k][k]=1;
                        continue;
                    }
                    for (int l=0;l<=m;++l) A[i][j].mat[k][l]=1;
                }
            }
        }else{
            for (int j=0;j<m;++j){
                if (!j) A[i][j]=S[i-1][0]; //这个很显然吧qwq
                else A[i][j]=S[i-1][j]*P[i-1][j-1]; //根据前缀矩阵和后缀矩阵的实际意义，乘起来就得到了A
            }
        }
        //求出前缀和后缀矩阵数组P和S，根据题解的方法求出即可
        P[i][0]=A[i][0];
        for (int j=1;j<m;++j) P[i][j]=P[i][j-1]*A[i][j];
        S[i][m-1]=A[i][m-1];
        for (int j=m-2;j>=0;--j) S[i][j]=A[i][j]*S[i][j+1];
    }
    int j=0;
    for (int i=len-1;i>=0;--i){ //既然已经得到了所有的A矩阵，就可以把它们用乘法组装起来获得结果了
        while (bin[i] --> 0){
            ans=ans*A[i][j];j++;if (j==m) j=0;
        }
    }
    cout<<ans.mat[0][m]<<endl;
}
 ```



---

## 作者：tzc_wk (赞：3)

[Codeforces 题目传送门](https://codeforces.com/contest/497/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF497E)

一道还算不错的矩乘 tea 罢，不过做过类似的题应该就比较套路了……

首先考虑对于一个固定的序列 $\{a\}$ 怎样求其本质不同的序列个数，考虑用一个“动态添加元素”的思想，每次往序列最后添加一个元素 $x$ 并计算加入这个元素后会新增多少个不同的子序列，显然对于所有原来的子序列，在其后面添上 $x$ 后得到序列依旧是该序列的子序列，但是我们不能仅仅简简单单地用原来的子序列个数 $\times 2$ 得到新的序列的子序列个数，因为会出现重复计算的情况。不难发现一个子序列被重复计算当且仅当它的末尾一位是 $x$，并且它在原来的序列中出现过了。还可以发现所有在原来的序列中出现过，并且末尾一位为 $x$ 的子序列，去掉末尾一位后仍是原序列的子序列，只有一个例外，那就是单独的 $x$，因此如果我们记 $f_{i,x}$ 表示序列 $\{a_1,a_2,\cdots,a_i\}$ 中有多少个序列以 $x$ 结尾，那么有 $f_{i,x}=\sum f_{i-1,y}+1$。（qwq 其实在[这道题](https://www.cnblogs.com/ET2006/p/Codeforces-1383E.html)我自己的解法中就已经用到这个思想了）

接下来考虑原题，看到数据范围 $10^{18}$，值域却只有 $30$，一脸矩乘，并且刚刚 $dp$ 转移方程式又恰好可以写成矩乘的形式，即假设 $a_i=x$，那么 $\begin{bmatrix}f_{i,0}\\f_{i,1}\\f_{i,2}\\\cdots\\f_{i,k-1}\\1\end{bmatrix}=\begin{bmatrix}1&0&0&\cdots&0\\0&1&0&\cdots&0\\\vdots&\vdots&\ddots&\cdots&\vdots\\1&1&1&\cdots&1\\\vdots&\vdots&\vdots&\vdots&\vdots\\0&0&0&\cdots&1\end{bmatrix}\times \begin{bmatrix}f_{i-1,0}\\f_{i-1,1}\\f_{i-1,2}\\\cdots\\f_{i-1,k-1}\\1\end{bmatrix}$，其中转移矩阵满足第 $x$ 行及对角线上所有元素都是 $0$，其余元素都是 $1$。

可是问题又来了，此题序列长度高达 $10^{18}$，不可能对每个元素都做一遍矩乘，不然复杂度肯定爆炸，有什么优化的办法呢？注意到此题的一个性质，那就是对于所有**各位数字和模 $k$ 相同的整数 $x,y$ 和非负整数 $z$**，必然有子序列 $a[x...x+k^z-1]$ 与子序列 $a[y...y+k^z-1]$ 完全相同，因此我们可以将所有形如 $a[x...x+k^z]$ 的子序列划分成 $k$ 个等价类，第 $i$ 类表示 $x$ 各位数字和 $\bmod k=i$ 的那一类，再预处理出 $A_{x,z}$ 表示 $a[x...x+k^z]$ 转移矩阵的乘积，那么有 $A_{x,z}=A_{x,z-1}\times A_{x+1,z-1}\times\cdots\times A_{k-1,z-1}\times A_{0,z-1}\times\cdots\times A_{x-1,z-1}$，暴力计算是 $k^4$ 的，不过用爪子想想也可以用前后缀积优化到 $k^3$。

最后求出 $n$ 在 $k$ 进制下的表达式，记作 $(a_ma_{m-1}\cdots a_1a_0)_k$，那么所有转移矩阵连乘的结果就是 $\prod\limits_{i=m}^0\prod\limits_{j=0}^{a_i}A_{j,i}$（左边的 $\prod\limits_{i=m}^0$ 表示倒序枚举，写的可能不是特别规范，不过大概意思懂就行了罢），这个随便算算即可，复杂度 $\log_knk^3$，可以通过此题。

```cpp
const int LOG=60;
const int MAXM=30;
const int MOD=1e9+7;
ll n;int m,d[LOG+2],dc=-1;
struct mat{
	int a[MAXM+2][MAXM+2];
	mat(){memset(a,0,sizeof(a));}
	mat operator *(const mat &rhs){
		mat ret;
		for(int i=0;i<=m;i++) for(int j=0;j<=m;j++) for(int k=0;k<=m;k++)
			ret.a[i][j]=(ret.a[i][j]+1ll*a[i][k]*rhs.a[k][j])%MOD;
		return ret;
	}
} ans,mul,a[LOG+2][MAXM+2],suf[LOG+2][MAXM+2],pre[LOG+2][MAXM+2];
int main(){
	scanf("%lld%d",&n,&m);
	while(n){d[++dc]=n%m;n/=m;}
	for(int i=0;i<=dc;i++){
		if(!i){
			for(int j=0;j<m;j++){
				a[i][j].a[m][m]=1;
				for(int k=0;k<m;k++) if(k^j) a[i][j].a[k][k]=1;
				for(int k=0;k<=m;k++) a[i][j].a[j][k]=1;
//				printf("A %d %d:\n",i,j);
//				for(int k=0;k<=m;k++) for(int l=0;l<=m;l++)
//					printf("%d%c",a[i][j].a[k][l],(l==m)?'\n':' ');
			}
		} else {
			for(int j=0;j<m;j++){
				if(!j) a[i][j]=suf[i-1][0];
				else a[i][j]=suf[i-1][j]*pre[i-1][j-1];
//				printf("A %d %d:\n",i,j);
//				for(int k=0;k<=m;k++) for(int l=0;l<=m;l++)
//					printf("%d%c",a[i][j].a[k][l],(l==m)?'\n':' ');
			}
		}
		pre[i][0]=a[i][0];
		for(int j=1;j<m;j++) pre[i][j]=pre[i][j-1]*a[i][j];
		suf[i][m-1]=a[i][m-1];
		for(int j=m-2;~j;j--) suf[i][j]=a[i][j]*suf[i][j+1];
	} int sum=0;ans.a[m][0]=1;
	for(int i=0;i<=m;i++) mul.a[i][i]=1;
	for(int i=dc;~i;i--){
		while(d[i]){
			d[i]--;mul=mul*a[i][sum];
			sum++;if(sum==m) sum=0;
		}
	} ans=mul*ans;int ret=0;
	for(int i=0;i<=m;i++) ret=(ret+ans.a[i][0])%MOD;
	printf("%d\n",ret%MOD);
	return 0;
}
```



---

## 作者：Felix72 (赞：1)

此题需要求解本质不同子序列个数，因此先思考一般的求法。有 DP 状态 $f_{i, c}$ 表示前 $i$ 个字符组成的以 $c$ 结尾的本质不同子序列数量，转移是容易的，复杂度 $O(nk)$。

这个 DP 的好处是可以矩阵加速。此题的矩阵呈每 $k, k^2, k^3, \dots$ 一循环的树状结构，因此对于每个深度的每种子树预处理出矩阵乘积，这样就可以以 $O(\log_k nk^4)$ 的复杂度通过了。

```cpp
 /* NE_Cat 4.1 */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int K = 35, mod = 1e9 + 7;
long long n, m, pw[65], res; int k;
struct Matrix
{
	int h, w; long long s[K][K];
	inline void init(int n, int m)
	{
		h = n, w = m;
		for(int i = 0; i < h; ++i)
			for(int j = 0; j < w; ++j)
				s[i][j] = 0;
	}
	inline void unit(int n)
	{
		init(n, n);
		for(int i = 0; i < n; ++i) s[i][i] = 1;
	}
}; Matrix base[65][K], dp;
Matrix operator * (Matrix u, Matrix v)
{
	Matrix res; res.init(u.h, v.w);
	for(int i = 0; i < u.h; ++i)
		for(int j = 0; j < u.w; ++j)
			for(int k = 0; k < v.w; ++k)
				res.s[i][k] = (res.s[i][k] + u.s[i][j] * v.s[j][k]) % mod;
	return res;
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for(int i = 0; i < k; ++i)
	{
		base[0][i].init(k + 1, k + 1);
		base[0][i].s[k][k] = 1, base[0][i].s[k][i] = 1;
		for(int j = 0; j <= k; ++j) if(j != i) base[0][i].s[j][j] = 1;
		for(int j = 0; j <= k; ++j) base[0][i].s[j][i] = 1;
	}
	pw[0] = 1;
	while((__int128)pw[m] * k <= n) ++m, pw[m] = pw[m - 1] * k;
	for(int w = 1; w <= m; ++w)
	{
		for(int i = 0; i < k; ++i)
		{
			base[w][i].unit(k + 1);
			for(int j = i; j < i + k; ++j)
				base[w][i] = base[w][i] * base[w - 1][j % k];
		}
	}
	dp.init(1, k + 1); dp.s[0][k] = 1;
	for(int i = m, ex = 0; i >= 0; --i)
	{
		while(n >= pw[i])
		{
			dp = dp * base[i][ex % k];
			++ex; n -= pw[i];
		}
	}
	for(int i = 0; i < k; ++i) res = (res + dp.s[0][i]) % mod;
	cout << (res + 1) % mod << '\n';
	return 0;
}
/*

*/
```

---

