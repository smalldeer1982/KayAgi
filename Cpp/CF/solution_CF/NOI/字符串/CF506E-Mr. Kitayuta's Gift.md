# Mr. Kitayuta's Gift

## 题目描述

Mr. Kitayuta has kindly given you a string $ s $ consisting of lowercase English letters. You are asked to insert exactly $ n $ lowercase English letters into $ s $ to make it a palindrome. (A palindrome is a string that reads the same forward and backward. For example, "noon", "testset" and "a" are all palindromes, while "test" and "kitayuta" are not.) You can choose any $ n $ lowercase English letters, and insert each of them to any position of $ s $ , possibly to the beginning or the end of $ s $ . You have to insert exactly $ n $ letters even if it is possible to turn $ s $ into a palindrome by inserting less than $ n $ letters.

Find the number of the palindromes that can be obtained in this way, modulo $ 10007 $ .

## 说明/提示

For the first sample, you can obtain the palindrome "reviver" by inserting 'r' to the end of "revive".

For the second sample, the following 28 palindromes can be obtained: "adada", "adbda", ..., "adzda", "dadad" and "ddadd".

## 样例 #1

### 输入

```
revive
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
add
2
```

### 输出

```
28
```

# 题解

## 作者：xht (赞：47)

> [CF506E Mr. Kitayuta's Gift](https://codeforces.com/contest/506/problem/E)

## 题意

- 给定一个小写字符串 $s$ 和一个正整数 $n$。
- 要求在 $s$ 中插入恰好 $n$ 个小写字符使其回文的方案数。
- $|s| \le 200$，$n \le 10^9$，答案对 $10^4 + 7$ 取模。

## 题解

首先考虑 $n+|s|$ 为偶数的情况。

考虑 dp。设 $f_{i,l,r}$ 表示只考虑最终回文串的前 $i$ 和后 $i$ 个字符，它们与 $s$ **尽可能**匹配后 $s$ 还剩下 $[l,r]$ 这段区间时的方案数。再设 $g_i$ 表示只考虑最终回文串的前 $i$ 和后 $i$ 个字符，它们与 $s$ 已经能够完全匹配时的方案数。

那么转移有：

1. $s_l = s_r$，$r - l \le 1$。

$$g_{i+1} \leftarrow f_{i,l,r}$$

$$f_{i+1,l,r} \leftarrow 25 \cdot f_{i,l,r}$$

2. $s_l = s_r$，$r - l \ge 2$。

$$f_{i+1,l+1,r-1} \leftarrow f_{i,l,r}$$

$$f_{i+1,l,r} \leftarrow 25 \cdot f_{i,l,r}$$

3. $s_l \ne s_r$。

$$f_{i+1,l+1,r} \leftarrow f_{i,l,r}$$

$$f_{i+1,l,r-1} \leftarrow f_{i,l,r}$$

$$f_{i+1,l,r} \leftarrow 24 \cdot f_{i,l,r}$$

4. $g$。

$$
g_{i+1} \leftarrow g_i
$$

此时我们可以得到一个状态数 $\mathcal O(|s|^2)$ 递推 $\mathcal O(n + |s|)$ 次的 dp，这个 dp 可以强行矩阵加速，复杂度为 $\mathcal O(|s|^6 \log (n + |s|))$，一脸的过不去。

仔细观察这个 dp，可以发现这实际上是在一个**有限状态自动机**上匹配的过程。

比如对于 $s = \texttt{abaac}$ 转移的过程如下：

![](http://www.xht37.com/wp-content/uploads/2020/02/61e9c25b977bad7af00165b92070a9acabf16704.png)

如果真的理解了上面的 dp，会发现这张图中不同颜色的点和不同形态的边与上面的状态和转移一一对应。

这个自动机的节点数依旧是 $\mathcal O(|s|^2)$ 的。考虑压缩这个自动机，可以发现，对于每一条从起点到终点的链，如果其上面有 $k$ 个红点，那么就意味着它有 $\lceil \frac{|s|-k}2 \rceil$ 个绿点，同时最终连接终点的点一定是绿点。

而对于两条红点数量相同的链，它们对答案的贡献与红点的具体位置无关，因此本质上是一样的，这意味着本质不同的链只有 $\mathcal O(|s|)$ 条。

但我们还要求出有 $k$ 个红点的链的数量。设 $h_{i,l,r}$ 表示从起点走到 $(l,r)$ 对应的节点的路径中，有多少条经过了 $i$ 个红点。那么我们可以采用**记忆化搜索**的方法 $\mathcal O(|s|^3)$ 求出答案。

现在我们有 $\mathcal O(|s|)$ 条本质不同的链，同时还知道了每条链的数量。至此我们可以对每条链做一次矩阵加速，时间复杂度降为 $\mathcal O(|s|^4 \log (n + |s|))$。

但还不够，我们要想办法建出一个节点数只有 $\mathcal O(|s|)$ 的自动机。构建方法如下（方法来自 [CQzhangyu](https://www.cnblogs.com/CQzhangyu/p/8685601.html)）：

![](http://www.xht37.com/wp-content/uploads/2020/02/1077980-20180401083928510-472522990.png)

同样的，如果真的理解了上面的转化，肯定能自己根据这样图脑补出来压缩后的自动机具体长成什么样。

压缩后的自动机点数只有 $\mathcal O(|s|)$ 个了，这时候再使用矩阵加速，就可以 $\mathcal O(|s|^3 \log (n+|s|))$。

然而这玩意儿稍微有点卡常，但如果我们把状态转移设计成只能从编号小的往编号大的点转移，那么矩阵乘法时常数可以除以 $6$。

最后还有一个问题，$n+|s|$ 如果为奇数，咋办？

唯一的区别在于，在最后一步的时候，包含两个字符的绿点无法再转移到终点。

那么，我们只保留这样的链，同时去掉终点的自环，这样得到的结果就是要去掉的方案数。


## 代码

```cpp
const int N = 207, M = 307;
int n, m, k;
char s[N];
bool v[N][N][N];
modint h[N][N][N], f[M], g[M][M], F[M], G[M][M];

inline modint H(int i, int l, int r) {
	if (i < 0) return 0;
	if (v[i][l][r]) return h[i][l][r];
	v[i][l][r] = 1;
	if (l == 1 && r == m) return h[i][l][r] = !i;
	if (l != 1 && s[l-1] != s[r]) h[i][l][r] += H(i - 1, l - 1, r);
	if (r != m && s[l] != s[r+1]) h[i][l][r] += H(i - 1, l, r + 1);
	if (l != 1 && r != m && s[l-1] == s[r+1]) h[i][l][r] += H(i, l - 1, r + 1);
	return h[i][l][r];
}

inline int ceil(int x) {
	return (x >> 1) + (x & 1);
}

inline void mul(modint f[M], modint g[M][M]) {
	modint a[M];
	for (int j = 1; j <= k; j++)
		for (int i = 1; i <= k; i++)
			a[i] += f[j] * g[j][i];
	for (int i = 1; i <= k; i++) f[i] = a[i];
}

inline void mul(modint g[M][M]) {
	modint a[M][M];
	for (int i = 1; i <= k; i++)
		for (int o = i; o <= k; o++)
			for (int j = o; j <= k; j++)
				a[i][j] += g[i][o] * g[o][j];
	for (int i = 1; i <= k; i++)
		for (int j = 1; j <= k; j++)
			g[i][j] = a[i][j];
}

inline void ksm(int o) {
	while (o) {
		if (o & 1) mul(f, g);
		mul(g), o >>= 1;
	}
}

int main() {
	rds(s, m), rd(n), k = m + ceil(m);
	for (int i = 0; i < m; i++) {
		modint c;
		for (int j = 1; j <= m; j++) {
			c += H(i, j, j);
			if (j != m && s[j] == s[j+1]) c += H(i, j, j + 1);
		}
		if (i) {
			g[i][k-ceil(m-i)] = c, g[i][i] = 24;
			if (i != 1) g[i-1][i] = 1;
			else f[i] = 1;
		} else {
			f[m] = c, g[k][k] = 26;
			for (int j = m; j < k; j++) g[j][j+1] = 1, g[j][j] = 25;
		}
	}
	if ((n + m) & 1) {
		for (int i = 1; i <= k; i++) F[i] = f[i];
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= k; j++)
				G[i][j] = g[i][j];
	}
	ksm(ceil(n + m));
	if (!((n + m) & 1)) return print(f[k]), 0;
	modint ans = f[k];
	for (int i = 1; i <= k; i++) f[i] = F[i];
	for (int i = 1; i <= k; i++)
		for (int j = 1; j <= k; j++)
			g[i][j] = G[i][j];
	for (int i = 0; i < m; i++) {
		modint c;
		for (int j = 1; j <= m; j++)
			if (j != m && s[j] == s[j+1]) c += H(i, j, j + 1);
		if (i) g[i][k-ceil(m-i)] = c;
		else f[m] = c, g[k][k] = 0;
	}
	ksm(ceil(n + m));
	print(ans - f[k]);
	return 0;
}
```

---

## 作者：shadowice1984 (赞：28)

神仙矩阵乘法……

~~我矩乘今天就是要玩死你~~

~~其实这种回文串计数的题还是相当套路的~~
_________________

先简述一下题意

给定一个字符串$S$,输入一个$m$问你有多少个长度为$|S|+m$的回文串含有S这个子序列

$|S| \leq 200,m\leq 10^{9}$

### 前置芝士:矩阵快速幂

~~蛤？淦cfE题不会矩乘？出门左转你站膜板区,包教包会~~

# 本题题解

**为了减少不必要的分情况讨论,我们以下的解法仅仅针对$|S|+m$是偶数的情况**


首先这是一道可爱~~(并不)~~的数数题，那么既然是计数我们常用的一个套路就是dp了

这道题显然最要命的限制就是回文串了,由于我们现在仅仅考虑偶回文串的情况,所以情况还比较简单。

我们仿照一般的对字符串进行dp的套路,我们不停的一位一位的放字符来进行决策,换句话讲我们的转移就是枚举下一位放什么,这样dp有一个相当棒的好处就是我们永远不会重复数同一个串

由于我们的限制是回文串因此我们的决策是同时在字符串的头和尾放一个字符进行转移,(我们这样做一定可以dp出所有的偶回文串)

那么我们就会有一个比较naive的dp设计,我们设$dp(i,j,k)$表示现在字符串的前$k$位和后$k$位已经被决策完毕,当前字符串的$(i,j)$这段区间**还没有被匹配完毕**时的方案数,另设一个状态$target(k)$表示该字符串的前$k$位和后$k$位同时被确定,并且已经包含$S$这个子序列的字符串数目

那么我们状态中的"还没有匹配的区间"是什么意思呢？

我们发现一个回文串会可能会有很多个等于字符串$S$的子序列,所以我们的dp状态的限制维度设计的不好的话我们就会很容易将同一个串多次计数

所以我们采取这样一种策略匹配子序列**从头尾两端同时添加字符,一旦可以和|S|匹配子序列就进行匹配**,可以证明的是如果这个字符串含有子序列$S$
就肯定能被这个算法识别出一个子序列来，并且我们还可以证明的是对于同一个字符串被识别出的子序列有且仅有一种,因此我们会发现这样设计状态的话每个字符串就只会被统计一次了,所以我们的"还没有匹配的区间"指的就是这样贪心的匹配完前后$k$位之后

那么我们的dp转移就十分的简易了

假设我们已知$dp(i,j,k)$的值我们现在想要更新其他状态的值

那么我们根据$S(i)==S(j)$这个命题的真假来进行分类讨论进行转移

### Case1:$S(i)==S(j)\&\&j-i\leq1$

此时我们发现这种情况下我们只需要填对$S(i)$这个字符我们就可以成功的完成对于$S$的匹配了,另外的$25$种填字符方案都会仅仅使步数$+1$

所以我们的转移方程就是

$$target(k+1)+=dp(i,j,k)$$

$$dp(i,j,k+1)+=dp(i,j,k)×25$$

### Case2:$S(i)==S(j)\&\&j-i > 1$

这种情况下我们发现必须填对$S(i),S(j)$所代表的字符才能进行转移,其他情况下仅仅只是令步数$+1$

$$dp(i+1,j-1,k+1)+=dp(i,j,k)$$

$$dp(i,j,k+1)+=dp(i,j,k)×25$$

### Case3:$S(i)!=S(j)$

这种情况下我们会发现只要填对$S(i)$或者$S(j)$所代表的字符才能进行转移,其余的$24$种情况才会令步数$+1$

$$dp(i+1,j,k+1)+=dp(i,j,k)$$

$$dp(i,j-1,k+1)+=dp(i,j,k)$$

$$dp(i,j,k+1)+=dp(i,j,k)×24$$

### Case4:$target$

显然$target$状态的话可以随便转移，因此26种字符都可以填

$$target(k+1)+=target(k)×26$$

___________________________

那么对于一个偶回文串来讲我们需要做的就是提取$target((|S|+m)/2)$的值就可以得到总的方案数了，上面的dp显然是可以大力矩乘的,不过由于状态的总量是$O(|S|^2)$的这样写我们会得到一个$O(|S|^{6}log(|S|+m))$的严格过不去算法

那么我们想想有什么的办法可以优化这个暴力呢?我们真的利用了全部的信息吗？有没有信息可以压缩呢？

答案是显然的,上述的算法存在着严重的信息浪费我们明明刷出了一个信息量是$O(|S|^{4})$级别的矩阵但是我们却仅仅提取的其中一项(也就是$target$)的值,很明显中间的变量全部被浪费了

所以我们要想办法利用起这些中间变量来

怎么办呢？

我们观察一下我们刚才的dp转移方程,如果状态A和状态B之间存在着这样一种转移方程的话

$$dp(B)+=dp(A)×C$$

我们就在$A->B$之间连$C$条$A$指向$B$的有向边

 _(注意如果两个状态仅仅是k值不同的话我们视为相同的状态,比如$dp(i,j,k)$和$dp(i,j,k+1)$视为相同状态)_ 
 
那么我们发现这样建出来的图如果去掉自环的话就是一张$DAG$了,而我们$target((|S|+m)/2)$的值就是从$(1,n)$这个点出发,走$(|S|+m)/2$条边之后到达$target$点的方案数

很好所以我们就这样把一个dp问题转化为了图上的路径计数问题

那这个问题怎么做呢？

我们首先值得观察的一点就是图上点的自环数目总共就只有三种:$24,25,26$

那么这又有什么用呢？

我们观察这个图上的每一条路径,这条路径经过的边可能很多，不过经过的点的种类却很少,最多经过$|S|$个点(因为走过的边绝大部分都是在走自环)

那么如果我们将经过点的点集相同的路径成为"一类路径"的话我们会发现两类路径的所包含的路径条数相等当且仅当这两条路径上自环数目为$24,25,26$的点的个数分别相等(经过点集相同之后两个路径不同的唯一可能就是走自环方式不同了)

其中$26$相等的限制明显是个废话,因为整张图就一个点有$26$的自环它就是终点，我们统计的就是从$(1,n)$到终点的路径，所以终点显然会出现在每一条路径中

另一个相当有趣的性质就是如果我们已知一条路径上有$a$个自环数目为$24$的点,那么自环数目为$25$的点就是$\lceil \frac{n-a}{2} \rceil$，这个性质可以由dp的转移特性推出，因为我们每次走过一个自环为$24$的点仅仅消耗一个字符，不过走过自环为$25$却经常消耗两个字符,唯一的特例出现在$i==j$的时候,此时我们的自环数为$25$不过却消耗了一个字符,这就是我们的公式里面加上了上取整的原因

那这个性质告诉我们什么呢？图中本质不同的路径类仅仅只有$O(|S|)$种,换句话说两个路径类包含的路径条数不同当且仅当他们包含的自环数为$24$的点不同

那么我们可以设一个$cnt(i,j)$表示从$j$出发到达终点走了$i$个自环数为$24$的点的方案数，这个状态可以通过记忆化搜索的方式以$O(|S|^3)$的方式求出

有了这个状态我们就可以枚举走了几个24自环点,用矩阵快速幂求出这类路径的总方案数，然后读一下$cnt$数组找到这类路径一共有几条二者乘一下就可以了

这样我们就得到了一个$O(|S|^4log(|S|+m))$的过不去算法

怎么办呢？

我们发现刚才的算法之所以慢是因为你做了$O(|S|)$次矩阵乘法,问题来了你为什么要做矩乘呢？肯定是为了算从起点到终点的路径条数对不对啊,那么问题来了你刷出了一个$O(|S|^2)$的矩阵你却就提取这个矩阵的一位，剩下的中间变量又双叒叕被你扔了……算法当然会慢了

那么我们接下来该怎么办呢？

我们要抛弃传统矩乘的思路,传统矩阵乘法在统计路径条数的时候显然是只有一个起点和一个汇点的,但是我们考虑一下矩阵乘法的意义立即就会发现一个事实，假如我们最后刷出来的矩阵是$C$的话,$C(i,j)$表示的就是从$i$走到$j$的方案数

换句话说我们的矩阵乘法其实兹瓷多个源点和汇点的,只是我们一般不用而已

那么对于这道题来讲多源点和汇点的矩乘就显得十分有用了

我们这样建一张图,前$|S|-1$个点连成一条有向的链并且每个点有一个$24$的自环指向自己,之后$(|S|+1)/2$个点连成一条有向链并且和前面的链接起来,这些点每个点有一个$25$的自环,最后每个有25自环的点连出去一条边和一个有$26$个自环的点相连(注意我们需要开$(|S|+1)/2)$个有26自环的点)

你这样建一个图你就会发现首先图上任意两点的路径都是唯一的(不考虑自环),第二就是任意一个走了$n$个24自环点$m$个25自环点1个26自环的路径都可以在图上被表示出来,换句话说,这张图蕴含了所有的路径类

那么我们就可以对这个图做一遍矩乘就可以计算出所有路径类的路径条数了(这对应了图上某两个点之间的方案数)

至此我们得到了一个$O(|S|^{3}log(|S|+m)$的做法我们已经可以解决偶回文串的问题了

问题来了似乎还有奇回文串的问题啊？

~~笑容逐渐凝固~~

____________________________

## 关于奇回文串的解决方案

奇回文串和偶回文串的唯一不同在于奇回文串有一个回文中心它不需要和其他的字符一样，而偶回文串没有

那其实我们的做法异常简单粗暴，我们枚举回文中心是什么字符

首先我们对于所有的字符来讲$target((|S|+m)/2)$一定是一个合法的状态

然后假设我们枚举的回文中心的字符是$char$的话那么$dp(i,i,(|S|+m)/2)$(其中$S(i)==char$)也会是一个合法的状态

而$target((|S|+m)/2)$的值当然可以直接按照偶回文串的解决方案求出

现在就是我们多了一些dp值需要求出

怎么办呢？

我们把dp的转移图中的边全部反向,计算一个$cnt(i,j)$数组表示从j点出发到$(1,n)$经过了i个24自环点的方案数,然后我们枚举考虑每个$dp(i,i)$状态到$(1,n)$的24自环点数目然后读取一下矩阵上的信息就可以计算了

_______________________


## 关于卡常数

嗯~ o(\*￣▽￣\*)然后我们信心满满的交了这个算法

~~“Time limit exceeded on test 14”~~

~~就算你有6000ms时限,就算你是cf评测姬,我说你T,你还是得T~~

~~卡常数了不起啊？~~

~~sorry，卡常数真的是可以为所欲为的~~

~~以后天天卡他常数！~~

~~“Time limit exceeded,Time limit exceeded”~~

然后你发现你的矩阵似乎是一个上三角矩阵

这意味着我们一般的矩阵乘法

```C
for(int i=1;i<=n;i++)
	for(int k=1;k<=n;k++)
    	for(int j=1;j<=n;j++)(a[i][j]+=b[i][k]*c[k][j])%=mod;
```

可以换成

```C
for(int i=1;i<=n;i++)
	for(int k=i;k<=n;k++)
    	for(int j=k;j<=n;j++)(a[i][j]+=b[i][k]*c[k][j])%=mod;

```

常数减少至原来的$1/6$就可以通过这题了

上代码~

```C
#include<cstdio>
#include<algorithm>
using namespace std;const int N=2*1e2+10;const int mod=10007;
int tr[N][N];int tp[N*N];int n;char mde[N];int m;int ctt;int trp[N<<1][N<<1];int S;int ans;
struct Grph
{
	int v[2*N*N];int x[2*N*N];int ct;int al[N*N];int dp[N][N*N];bool book[N][N*N];
	inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
	inline int dfs(int cnt,int u)
	{
		if(cnt<0)return 0;if(book[cnt][u])return dp[cnt][u];book[cnt][u]=true;
		for(int i=al[u];i;i=x[i])(dp[cnt][u]+=dfs(cnt-tp[u],v[i]))%=mod;
		return dp[cnt][u];
	}
}g2;//转移的dag 
struct mar//矩阵类 
{
	int mp[N<<1][N<<1];
	inline int* operator [](const int x){return mp[x];}
	void operator *=(const mar& b)
	{
		for(int i=1;i<=S;i++)for(int j=1;j<=S;j++)trp[i][j]=0;
		for(int i=1;i<=S;i++)
			for(int k=i;k<=S;k++)
				for(int j=k;j<=S;j++)(trp[i][j]+=mp[i][k]*b.mp[k][j])%=mod;
		for(int i=1;i<=S;i++)for(int j=1;j<=S;j++)mp[i][j]=trp[i][j];
	}
}trs,res;int f[N];int g[N];
int main()
{
	scanf("%s",mde+1);scanf("%d",&m);for(n=1;mde[n+1]!='\0';n++);
	for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)tr[i][j]=++ctt;++ctt;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			if(mde[i]==mde[j])//建图 
			{if(j-i<=1)g2.add(ctt,tr[i][j]);else g2.add(tr[i+1][j-1],tr[i][j]);}
			else {tp[tr[i][j]]=1;g2.add(tr[i+1][j],tr[i][j]),g2.add(tr[i][j-1],tr[i][j]);}
	for(int i=0;i<n;i++)g2.book[i][tr[1][n]]=true;g2.dp[tp[tr[1][n]]][tr[1][n]]=1;
	for(int i=0;i<n;i++)g2.dfs(i,ctt);//记忆化搜索 
	for(int i=1;i<n;i++)trs[i][i]=24;int t=(n+1)/2;//构建矩阵 
	for(int i=0;i<t;i++)trs[n+i][n+i]=25;
	for(int i=0;i<t;i++)trs[n+t+i][n+t+i]=26;
	for(int i=1;i<n+t-1;i++)trs[i][i+1]++;
	for(int i=0;i<t;i++)trs[n+i][n+t+i]++;S=n+(t<<1)-1;
	for(int i=1;i<=S;i++)res[i][i]=1;
	for(int p=(n+m)>>1;p;p>>=1,trs*=trs)if(p&1)res*=trs;
	for(int i=0,v;i<n;i++)v=(n-i+1)/2,f[i]=res[n-i][n+t+v-1],g[i]=res[n-i][n+v-1];
	if((n+m)&1)
	{
		for(int i=0;i<n;i++)(ans+=f[i]*g2.dp[i][ctt])%=mod;(ans*=26)%=mod;
		for(int i=1;i<=26;i++)
			for(int j=1;j<=n;j++)
				if(mde[j]=='a'+i-1)for(int k=0;k<n;k++)(ans+=g[k]*g2.dp[k][tr[j][j]])%=mod;
	}
	else{for(int i=0;i<n;i++)(ans+=f[i]*g2.dp[i][ctt])%=mod;}printf("%d",ans);return 0;//拜拜程序~ 
}

```



































---

## 作者：team0001 (赞：20)

给出一个不需要思考的 $O(s^3)$ 做法。

首先，我们发现这题容易写出 $n \times s^2$ 的暴力，就是考虑 $f_{i,l,r}$表示考虑到最终回文串前一半的第 $i$ 个数，在原串中最少剩下$[l,r]$的方案数，转移只需考虑左右端点是否相等以及是否彻底匹配完。

记$a_i$表示加入 $i$ 个数是（奇/偶）回文的方案数（其中奇偶取决于最终串的奇偶，注意讨论）。

我们尝试推出它的递推式，于是用 $Berlekamp - Massey$ 算法尝试打个表，发现递推式不超过 $4 \times s$ 。

我们很高兴啊，直接暴力线性递推就做完了（就是把多项式乘法和取模暴力做）。

复杂度 $O(s^3)$（暴力），$O(s^2)$（$BM$算法）， $O(s^2logn)$（暴力线性递推）。~~所以复杂度瓶颈在暴力~~

具体的长度证明可以见其他题解，容易发现线性递推的长度不会超过矩阵大小的两倍。本题解只是提供一个做题想不出来时的思路。

code:
```
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
const int N=1005;
const int mod=10007;
int a[N],n;
int _b[N],_c[N],_res[N];
int _inv[mod+1];
void BM(int *a,int n){//bm算法 
	_inv[0]=_inv[1]=1;
	rep(i,2,mod-1)_inv[i]=(mod-mod/i)*_inv[mod%i]%mod;
	int las=0,lp=0;
	rep(i,1,n){
		if(a[i]&&!_b[0])_b[0]=i,lp=i,las=a[i];
		else {
			int delta=a[i];
			rep(j,1,_b[0]){
				delta=(delta-1ll*a[i-j]*_b[j])%mod;
			}
			delta=(delta+mod)%mod;
			if(delta!=0){
				rep(i,0,_b[0])_res[i]=_b[i];
				int mul=1ll*delta*_inv[las]%mod;
				_b[i-lp]=(_b[i-lp]+mul)%mod;
				rep(j,1,_c[0])_b[i-lp+j]=((_b[i-lp+j]-1ll*_c[j]*mul)%mod+mod)%mod;
				_b[0]=max(_b[0],i-lp+_c[0]);
				rep(i,0,_res[0])_c[i]=_res[i];
				las=delta;lp=i;
			}
		}
	}
}
int f[N][205][205];
void add(int &x,long long y){
	x=(x+y)%mod;
}
char s[N];
//暴力线性递推
int ans[N],tmp[N];
int len;
int _[N];
void times(int *a,int *b){
	rep(i,0,len*2)_[i]=0;
	rep(i,0,len)rep(j,0,len)add(_[i+j],a[i]*b[j]);
	for(int i=len*2;i>=len;i--)if(_[i]){
		rep(j,i-len,i-1)add(_[j],_[i]*_b[i-j]);
		_[i]=0;
	}
	rep(i,0,len)a[i]=_[i];
}
void ksm(int y){
	tmp[1]=1;ans[0]=1;
	for(;y;y>>=1,times(tmp,tmp))
	if(y&1)times(ans,tmp);
} 
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	f[0][1][n]=1;
	int c;
	cin>>c;
	int flag=(c+n&1);
	rep(i,1,1000){
		add(a[i],a[i-1]*26ll);
		rep(j,1,n+1){
			rep(k,j,n)if(f[i-1][j][k]){
				if(j<=k){
					if(j-k==0)add(a[i],f[i-1][j][k]),add(f[i][j][k],f[i-1][j][k]*25);
					else if(k-j==1&&s[j]==s[k]){
						if(flag)add(a[i+1],f[i-1][j][k]*26);
						else add(a[i],f[i-1][j][k]);
						add(f[i][j][k],f[i-1][j][k]*25);
					}
					else if(s[j]==s[k])add(f[i][j+1][k-1],f[i-1][j][k]),add(f[i][j][k],f[i-1][j][k]*25);
					else add(f[i][j+1][k],f[i-1][j][k]),add(f[i][j][k-1],f[i-1][j][k]),add(f[i][j][k],f[i-1][j][k]*24);
				}
			}
		}
	}
	BM(a,1000);
	len=_b[0];
	c=(n+c+1>>1);
	ksm(c);
	int as=0;
	rep(i,1,len)add(as,ans[i]*a[i]);
	printf("%d\n",as);
}
```

---

## 作者：Alex_Wei (赞：19)

> B. [CF506E Mr. Kitayuta's Gift](https://www.luogu.com.cn/problem/CF506E) *3000

这题真的只有 ***3000** 吗？

注意到最终串 $t$ 长度固定，因此为了不重不漏地计数，我们尝试从两端向回文中心依次枚举对应两个（或一个，当且仅当枚举到回文中心）位置上的字符。

不妨设串长为偶数，此时我们填入恰好 $k = \dfrac {|s| + n} 2$ 层字符。

据题意，$s$ 能生成 $t$ 当且仅当 $s$ 是 $t$ 的子序列。模仿子序列自动机，我们尝试枚举 $t$，并 **从两端向中心** 匹配 $s$（因为 $t$ 是回文串，所以每一层的两个字符相等）。设 $f_{i, l, r}$ 表示填好 $i$ 层字符时，在 **两端尽量匹配 $s$** 的前提下还剩 $s_l \sim s_r$ 没有匹配。

- 当 $s_l = s_r$ 时，$f_{i, l, r}$ 以 $25$ 的系数转移到 $f_{i + 1, l, r}$，以 $1$ 的系数转移到 $f_{i, l + 1, r - 1}$。
- 当 $s_l \neq s_r$ 时，$f_{i, l, r}$ 以 $24$ 的系数转移到 $f_{i + 1, l, r}$，以 $1$ 的系数转移到 $f_{i, l + 1, r}$ 或 $f_{i, l, r - 1}$。
- 任何 $l > r$ 的状态均可视作等价的终点 $g_i$，以 $26$ 的系数转移到 $g_{i + 1}$。因为已经匹配 $s$，剩下字符可以任意填。 

$g_k$ 即为所求。

$n$ 非常大。使用矩阵快速幂优化，我们有了一个 $|s| ^ 6\log n$ 的算法。

接下来需要使用一些魔法。

我们将转移图 $G$ 给建出来（这是一个自动机）。上面有若干 $24$ 和 $25$ 的自环，以及终点处 $26$ 的自环。具体地，若 $s_{l, r}$ 满足 $s_l = s_r$，则对应节点有 $25$ 条自环，称为 $25$ 点；否则有 $24$ 条自环，称为 $24$ 点。

所有能转移到 $l > r$ 的 $s_{l, r}$ 均连向终点，$1$ 的系数对应图上的一条边。这里借用 CF 官方题解的图片。

![](https://codeforces.com/predownloaded/61/e9/61e9c25b977bad7af00165b92070a9acabf16704.png)

从起点 $s_{1, |s|}$ 到终点的长度为 $k$ 的路径条数即为答案。

---

若想优化复杂度，必须要寻找路径之间的等价性。

注意到整个自动机的规模是很小的，大部分时间我们都在走自环。将目光放在自环上。

我们去掉所有自环得到新图 $G_{\mathrm{acyc}}$。对于 $G_{\mathrm{acyc}}$ 上的任意一条从起点 $s_{1, |s|}$ 到终点的路径 $P_{\mathrm{acyc}}$，在其中插入若干自环使其长度为 $k$，即可 **唯一对应** $G$ 上的一条需要计入答案的合法路径 $P$。

不妨设 $P_{\mathrm{acyc}}$ 上有 $a$ 个 $24$ 点和 $b$ 个 $25$ 点，本题最关键的性质是 **插入自环的方案数仅与 $a$ 和 $b$ 有关**。这是因为在插入自环时，影响方案数的并非一个点具体是什么，而是一个点的自环个数。

换句话说，对于任意两条均具有 $a$ 个 $24$ 点和 $b$ 个 $25$ 点的路径 $P_{\mathrm{acyc}}$ 和 $Q_{\mathrm{acyc}}$，任何一种在 $P_{\mathrm{acyc}}$ 中插入自环的方案可唯一对应一种在 $Q_{\mathrm{acyc}}$ 中插入自环的方案（只需将 $P$ 和 $Q$ 的 $24$ 点和 $25$ 点一一对应即可）。

因此，设 $F(a, b)$ 表示往 $a$ 个 $24$ 点和 $b$ 个 $25$ 点当中插入 $k - a - b$ 条自环的方案数，则答案可表示为 $\sum \#(a, b) F(a, b)$，其中 $\#(a, b)$ 表示 $G_{\mathrm{acyc}}$ 上从起点到终点经过 $a$ 个 $24$ 点和 $b$ 个 $25$ 点的路径条数。

---

考虑求解 $F(a, b)$。

朴素的想法是直接把自动机建出来跑。具体地，建出这样一个自动机 $A_{a, b}$，其形如 $a$ 个 $24$ 点连成一条链，接上 $b$ 个 $25$ 点连成一条链，再接上一个终点，并添上每个节点对应的自环数量。那么从起点走 $k$ 步到终点的方案数即为 $F(a, b)$。

这样做的时间复杂度是 $|s| ^ 5\log n$，很劣。考虑优化。

我们发现大部分时间都浪费在矩阵快速幂上，但最终我们只取出了从起点到终点的路径条数。效率低下的主要原因是没有利用 **矩阵快速幂能求出图上任意两点间长度为 $k$ 的路径条数** 这一性质。

考虑将若干自动机合并在一起。

具体地，建出一张大自动机 $A$，其形如 $|s| - 1$ 个 $24$ 点连成一条链（任何路径的 $24$ 点个数最多为 $|s| - 1$：走向终点的最后一步一定是 $25$ 点），接上 $\left\lceil \dfrac{|s|} 2\right\rceil$ 个 $25$ 点连成一条链。在每个 $25$ 点后均接上一个终点。

这样，任意一条 $a$ 个 $24$ 点和 $b$ 个 $25$ 点的路径均被自动机 $A$ 表示出。只需求一遍 $A ^ k$，然后合适地选取起点和终点即可 $\mathcal{O}(1)$ 获得信息 $F(a, b)$。

整个过程如下，图源 CF 官方题解。

![](https://codeforces.com/predownloaded/5e/54/5e54f2c067227e74f7a2c1338e076f3b2a0874aa.png)

由于 $|A| = 2|s|$ 所以求 $A ^ k$ 会比较卡常。模数很小，所以用 `long long` 存矩阵就可以只在最后取模。

此外，根据 $A$ 是上三角矩阵的特点，容易优化 $6$ 倍常数。

---

考虑求解 $\#(a, b)$。由于 $\#(a, b)$ 是在 $G_{\mathrm{acyc}}$ 上的，所以直接 DAG DP 即可做到 $|s| ^ 4$：设 $g_{l, r, a, b}$ 表示从 $s_{l, r}$ 走到终点经过 $a$ 个 $24$ 点和 $b$ 个 $25$ 点的方案数，转移很显然。

过不去，考虑优化。

我们发现，一个点的自环数和经过该点后串长减小的长度息息相关。更具体地，如果我们确定了一条路径经过了 $a$ 个 $24$ 个有自环的点，那么因为剩下来的点全都是 $25$ 个有自环的点，而一个 $24$ 点使未被匹配的 $s$ 长度减小 $1$，一个 $25$ 点使为被匹配的 $s$ 的长度减小 $2$，故确定 $25$ 点的个数为 $\left\lceil\dfrac {|s| - a} 2\right\rceil$。

这说明 $b$ 是 $a$ 的函数，即 $b$ 可以根据 $a$ 直接推出来，所以不需要记录 $b$。这样复杂度就成了 $|s| ^ 3$，结合 $F(a, b)$ 的 $|s| ^ 3\log n$（上述性质对自动机部分没有什么优化），可以通过本题的 $|s| + n$ 为偶数的情况。

---

对于 $|s| + n$ 为奇数的情况，最后一步只能消去一个字符。因此，最后一步形如从 $s_{l, l + 1}$ 且 $s_l = s_{l + 1}$ 的状态走到终点的路径是不合法的。

令 $k = \left\lceil\dfrac {|s| + n} 2\right\rceil$，只需先做一遍偶数的情况，再令 $G$ 上所有 $s_{l, l + 1}$ 且 $s_l = s_{l + 1}$ 的状态成为终点，减掉从起点走 $k - 1$ 步到终点的方案数即可（$\#(a, b)$ 和 $F(a, b)$ 都类似求）。注意后者的 $F(a, b)$ 从 $A ^ {k - 1}$ 中得到，所以先减去后者再加上前者可以优化掉一半常数（不用做两次矩阵快速幂）。

时间复杂度 $\mathcal{O}(|s| ^ 3\log n)$。

我的评价是，这道题目太好太神了，做完很受启发。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200 + 5;
const int mod = 1e4 + 7;
int n, m, sz, red, green, ans;
char s[N];
struct mat {
	int a[N << 1][N << 1]; // 数组开小 =.=
	void init() {memset(a, 0, sizeof(a));}
	friend mat operator * (mat &x, mat &y) {
		mat z;
		z.init();
		for(int i = 1; i <= sz; i++)
			for(int k = i; k <= sz; k++) {
				for(int j = k; j <= sz; j++) z.a[i][j] += x.a[i][k] * y.a[k][j];
				if(k % 20 == 0 || k == sz) for(int j = 1; j <= sz; j++) z.a[i][j] %= mod;
			}
		return z;
	}
} tr, PATH;
mat matrix_quickpow(mat a, int b) {
	assert(b--);
	mat s = a;
	while(b) {
		if(b & 1) s = s * a;
		a = a * a, b >>= 1;
	}
	return s;
}

int k, f[N][N][N], tmp[N];
bool vis[N][N][N];
int calc_path(int l, int r, int num) {
	if(num < 0) return 0;
	if(l > r) return num ? 0 : 1;
	if(vis[l][r][num]) return f[l][r][num];
	vis[l][r][num] = 1;
	if(s[l] ^ s[r]) f[l][r][num] = calc_path(l, r - 1, num - 1) + calc_path(l + 1, r, num - 1);
	else f[l][r][num] = calc_path(l + 1, r - 1, num);
	return f[l][r][num] % mod;
}
int calc_path2(int l, int r, int num) {
	if(l >= r || num < 0) return 0;
	if(l + 1 == r && s[l] == s[r]) return num ? 0 : 1;
	if(vis[l][r][num]) return f[l][r][num];
	vis[l][r][num] = 1;
	if(s[l] ^ s[r]) f[l][r][num] = calc_path2(l, r - 1, num - 1) + calc_path2(l + 1, r, num - 1);
	else f[l][r][num] = calc_path2(l + 1, r - 1, num);
	return f[l][r][num] % mod;
}

int main() {
	// freopen("1.in", "r", stdin);
	cin >> s + 1 >> n, m = strlen(s + 1), k = m + n >> 1;
	for(int i = 0; i < m; i++) tmp[i] = calc_path(1, m, i);
	// for(int i = 0; i < m; i++) cerr << i << " " << calc_path(1, m, i) << endl;
	red = m - 1, green = m + 1 >> 1, sz = red + green * 2;
	for(int i = 1; i < red + green; i++) tr.a[i][i + 1] = 1;
	for(int i = red + 1; i <= red + green; i++) tr.a[i][i + green] = 1;
	for(int i = 1; i <= red; i++) tr.a[i][i] = 24;
	for(int i = red + 1; i <= red + green; i++) tr.a[i][i] = 25;
	for(int i = red + green + 1; i <= sz; i++) tr.a[i][i] = 26;
	PATH = matrix_quickpow(tr, k);
	if(n + m & 1) {
		memset(vis, 0, sizeof(vis));
		memset(f, 0, sizeof(f));
		for(int i = 0; i <= m - 2; i++) {
			int coef = calc_path2(1, m, i);
			// cerr << i << " " << coef << endl;
			if(m - i & 1) {assert(!coef); continue;}
			ans = (ans - coef * PATH.a[red + 1 - i][red + (m - i >> 1)]) % mod;
		}
		ans += mod, PATH = PATH * tr;
	}
	// cerr << ans - mod << endl;
	for(int i = 0; i < m; i++) {
		int gnum = m - i + 1 >> 1;
		// cerr << i << " " << red + green + gnum << " " << PATH.a[red + 1 - i][red + green + gnum] << endl;
		ans = (ans + tmp[i] * PATH.a[red + 1 - i][red + green + gnum]) % mod;
	}
	cout << ans << endl;
	return 0;
}

/*
2022/4/28
start thinking at 7:55

设 f_{i, l, r} 表示添加 i 个字符后, s_l ~ s_r 部分不是回文的方案数.
i 太大了.
i 越来越大, 我该怎么办?
矩阵快速幂也不行.
尝试组合意义.

看了眼标签发现就是矩阵快速幂.
可是状态有 |s| ^ 2 个啊.
能不能简化状态啊?
不管具体是什么, 只要知道长度就行了!
因为每个字符是等价的!
设 f_{i, j} 表示添加 i 个字符后没有匹配的串长度为 j 的方案数.
不行, 尽管每个字符等价, 但每个长为 j 的字符串不等价.

看了题解, 感觉好牛逼.
太牛逼了.
先找到路径之间的等价性, 然后再对每种路径的方案数计数.
路径方案又可以合起来算.
太猛了.

对于奇数的处理也很妙.

start coding at 9:48
finish debugging at 11:11
*/
```

---

## 作者：tzc_wk (赞：7)

[Codeforces 题目传送门](https://codeforces.com/contest/506/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF506E)

神仙题 %%%%%%%%%%%%%

u1s1 感觉这道题风格很省选（

下记 $m=|s|$，首先探讨 $n+m$ 为偶数的情形。

首先考虑一个暴力的 DP，我们设 $dp_{i,l,r}$ 表示当前考虑了回文串的前 $i$ 个字符和后 $i$ 个字符，前 $i$ 个字符恰好匹配了 $s$ 的 $[1,l-1]$ 区间中的字符，后 $i$ 个字符恰好匹配了 $s$ 的 $[r+1,m]$ 区间中的字符的方案数，再记 $g_i$ 为当前考虑了回文串的前 $i$ 个字符和后 $i$ 个字符。

考虑转移，分四种情况：

1. $r-l\le 1$ 且 $s_l=s_r$，那么如果我们在 $i+1$ 位置填上 $s_l$ 那么就匹配结束了，即 $g_{i+1}\leftarrow dp_{i,l,r}$，否则还是只能完全匹配 $[1,l-1]$ 和 $[r+1,n]$ 中的字符，即 $dp_{i+1,l,r}\leftarrow 25·dp_{i,l,r}$。
2. $r-l\ge 2$ 且 $s_l=s_r$，那么如果我们在从左往右数和从右往左数第 $i+1$ 的位置填上 $s_l$ 就可以匹配到 $[1,l]$ 和 $[r,m]$，即 $dp_{i+1,l+1,r-1}\leftarrow dp_{i,l,r}$，否则还是有 $dp_{i+1,l,r}\leftarrow 25·dp_{i,l,r}$
3. $s_l\ne s_r$，那么如果我们在从左往右数和从右往左数第 $i+1$ 的位置填 $s_l$，左端点就可以多匹配一位，即 $dp_{i+1,l+1,r}\leftarrow dp_{i,l,r}$，同理如果我们填 $s_r$，右端点就可以多匹配一位，即 $dp_{i+1,l,r-1}\leftarrow dp_{i,l,r}$，否则还是只能完全匹配 $[1,l-1]$ 和 $[r+1,n]$ 中的字符，即 $dp_{i+1,l,r}\leftarrow 24·dp_{i,l,r}$。
4. $g$ 的转移：显然由于我们已经匹配结束了，剩下的位置填什么都行，即 $g_{i+1}\leftarrow g_i$。

最终答案即为 $g_{(n+m)/2}$

这样暴力是 $nm^2$ 的，如果强行把 $(l,r)$ 看作一个二元组套矩乘，那可以实现 $m^6\log n$ 的优秀复杂度，一脸过不去。

我们考虑优化，敏感一些的同学应该可以注意到这个 DP 转移方程有点像 DAG 上的 DP，事实上，如果我们把所有二元组 $(l,r)$ 以及 $g_i$（下记为目标点）分别看作一个点，对于形如 $dp_{i+1,x}\leftarrow z·dp_{i,y}$ 的状态转移方程式，我们就从 $y$ 到 $x$ 连 $z$ 条边，那么答案就是 $(1,m)$ 表示的点到目标点的经过 $\dfrac{n+m}{2}$ 条边的路径条数。

我们考虑探究一下这张图长啥样，比方说 $s=\text{abaac}$，那么建出图来就长这样（这里借用了 xht37 大佬题解里的图）：

![](http://www.xht37.com/wp-content/uploads/2020/02/61e9c25b977bad7af00165b92070a9acabf16704.png)

不难发现，该图是由若干个自环即若干条有向边组成了，对于每个状态 $(l,r)$ 都有一个自环连向自己，如果去掉这些自环，那形成的图显然是一个 DAG（$(l,r)$ 能到达 $(l',r')$ 当且仅当 $[l',r']\subseteq[l,r]$，这显然构成了一个偏序关系），也就是说从源点 $(1,m)$ 到目标点，经过的非自环边的个数最多只有 $m$（每次经过一条边，区间长度缩小 $1$ 或 $2$，因此至少缩小 $m$ 次就能到达目标点）

并且还可以发现除了目标点上有个 $26$ 的自环之外，自环的类型只有 $2$ 种，那就是权值为 $25$ 的环和权值为 $24$ 的环，我们不妨称存在权值为 $25$ 的自环连向自己的点为“$25$ 点”，其余的点称为“$24$ 点”。考虑观察这个路径个数有什么性质，我们不妨称去掉自环边后路径相同的路径为等价类，考虑对每个等价类计算一遍方案数，容易发现等价类具体先经过权值为多少的自环，后经过权值为多少的自环并不重要，我们只关心它经过了多少权值为 $24,25,26$ 的自环，即两个等价类的路径的个数相同当且仅当这两个等价类的路径上 $24,25,26$ 的自环的个数相同。

显然权值为 $26$ 的自环就是废话，因为从起始点到目标点总共只会经过一个 $26$ 的自环。而经过的 $25$ 的自环和 $24$ 的自环个数有一个性质，那就是如果我们记经过的 $25$ 的自环个数为 $c_{25}$，经过的 $24$ 的自环个数为 $c_{24}$，则 $c_{25}=\lceil\dfrac{s-c_{24}}{2}\rceil$，道理很简单，对于一个 $25$ 点 $[l,r]$，每当我们从该点走向一个别的点时，区间长度会缩短 $2$（当然 $l=r$ 时只会缩短 $1$），而对于一个 $24$ 点 $[l,r]$ 则会缩短 $1$，因此 $c_{25}=\lceil\dfrac{s-c_{24}}{2}\rceil$，故我们只需对于每个 $i$ 求出经过 $i$ 个 $24$ 点的等价类个数，然后对每个 $i$ 跑一遍矩阵快速幂即可。

这个东西怎么求呢？考虑记忆化搜索，记 $f_{x,l,r}$ 为以状态 $[l,r]$ 为结尾的经过 $x+[(l,r)\text{是否为}24\text{点}]$ 个 $24$ 点的路径个数，转移很容易，如果 $s_{l-1}\ne s_r$ 那 $(l-1,r)$ 为 $24$ 点并且存在 $(l-1,r)\to (l,r)$ 的边，$f_{x,l,r}\leftarrow f_{x,l,r}$，$(l,r+1)$ 也同理，如果 $s_{l-1}=s_{r+1}$，那 $(l-1,r+1)$ 为 $25$ 点并且存在 $(l-1,r+1)\to(l+r)$ 的边，$f_{x,l,r}\leftarrow f_{x,l-1,r+1}$，记忆化搜索即可，边界条件 $f_{0,1,m}=1$。

这样复杂度是 $m^4\log n$ 的，还是无法通过，继续优化。

这题复杂度瓶颈在于对于每个 $x$ 都跑一遍矩阵优化，考虑对状态进行压缩，我们在上面建一排 $m$ 个 $24$ 点，在下面建一排 $\lceil\dfrac{m}{2}\rceil$ 个 $25$ 点，对于上面一排的第 $i$ 个点，连一条指向第二排第 $\lceil\dfrac{m}{2}\rceil-\lceil\dfrac{m-i}{2}\rceil$ 个节点，权值为经过 $i$ 个路径的等价类个数，然后在相邻的 $24$ 点之间连权值为 $1$ 的边，在相邻的 $25$ 点之间连权值为 $1$ 的边，然后每个 $24$ 点上都套个权值为 $24$ 的自环，每个 $25$ 点上套个权值为 $25$ 的自环，最后连一条从最右边的 $25$ 点向目标点，权值为 $1$ 的边，再在目标点上套个 $26$ 的自环即可。这里还是借一张 xht37 神仙题解里的图：

![](http://www.xht37.com/wp-content/uploads/2020/02/1077980-20180401083928510-472522990.png)

这样状态数降低到了 $\mathcal O(m)$，跑一遍矩乘即可，复杂度 $m^3\log n$。

这仅仅只是 $n+m$ 为偶数的情况，最后考虑 $n+m$ 为奇数的情况有什么不同。记 $p=\dfrac{n+m-1}{2}$，唯一的不同就是最后一步，$dp_{p,i,i+1}$（$s_i=s_{i+1}$），无法转移到 $g_{p+1}$。正难则反，我们考虑拿总方案数减去这部分方案数，我们只需保留最后一步从 $(i,i+1)$ 转移的链，并去掉目标点上 $26$ 的自环即可。

最后，此题还存在卡常数的问题。这里有一个小技巧，那就是由于我们只在 $(i,j)(i<j)$ 的状态之间连边，得到的矩阵是一个下三角矩阵（我代码里使用的是先矩阵、后向量的乘法，因此对于存在边的 $(i,j)$ 我是令 $j$ 为行号 $i$ 为列号，因此得到的是上三角矩阵，不过差不多辣），因此我们在矩阵乘法时候只需枚举 $1\le i\le k\le j$ 的 $(i,j,k)$，这样常数可以减小到原来的 $\dfrac{1}{6}$

~~u1s1 这题题解码死我了~~

话说这场的 D1C D E 我是不是都做过了啊，u1s1 这场的 C 我[都不会](https://www.cnblogs.com/ET2006/p/Codeforces-505E.html)。

```cpp
const int MAXN=200;
const int MAXM=300;
const int MOD=1e4+7;
int n,m,k;char s[MAXN+5];
struct mat{
	ll a[MAXM+5][MAXM+5];
	mat(){memset(a,0,sizeof(a));}
	mat operator *(const mat &rhs){
		mat res;
		for(int i=1;i<=k;i++) for(int l=1;l<=i;l++) for(int j=1;j<=l;j++)
			res.a[i][j]+=a[i][l]*rhs.a[l][j];
		for(int i=1;i<=k;i++) for(int j=1;j<=k;j++) res.a[i][j]%=MOD;
		return res;
	}
};
int dp[MAXN+5][MAXN+5][MAXN+5];
int dfs(int x,int l,int r){
	if(x<0) return 0;
	if(~dp[x][l][r]) return dp[x][l][r];
	if(l==1&&r==m) return dp[x][l][r]=(!x);
	dp[x][l][r]=0;
	if(l!=1&&s[l-1]!=s[r]) dp[x][l][r]=(dp[x][l][r]+dfs(x-1,l-1,r))%MOD;
	if(r!=m&&s[l]!=s[r+1]) dp[x][l][r]=(dp[x][l][r]+dfs(x-1,l,r+1))%MOD;
	if(l!=1&&r!=m&&s[l-1]==s[r+1]) dp[x][l][r]=(dp[x][l][r]+dfs(x,l-1,r+1))%MOD;
	return dp[x][l][r];
}
int main(){
	scanf("%s%d",s+1,&n);m=strlen(s+1);k=m+((m+1)>>1);
	memset(dp,-1,sizeof(dp));mat st,trs,res;
	for(int i=0;i<m;i++){
		int cnt=0;
		for(int j=1;j<=m;j++){
			cnt=(cnt+dfs(i,j,j))%MOD;
			if((j^m)&&!(s[j]^s[j+1])) cnt=(cnt+dfs(i,j,j+1))%MOD;
		}
//		printf("%d %d\n",i,cnt);
		if(i) trs.a[k-((m-i+1)>>1)][i]=cnt;
		else st.a[m][1]=cnt;
	}
	for(int i=2;i<m;i++) trs.a[i][i-1]=1;
	if(m>1) st.a[1][1]=1;
	for(int i=m;i<k;i++) trs.a[i+1][i]=1;
	for(int i=1;i<m;i++) trs.a[i][i]=24;
	for(int i=m;i<k;i++) trs.a[i][i]=25;
	trs.a[k][k]=26;
	for(int i=1;i<=k;i++) res.a[i][i]=1;
//	for(int i=1;i<=k;i++) for(int j=1;j<=k;j++) printf("%d%c",trs.a[i][j],(j==k)?'\n':' ');
	int stp=(n+m+1)>>1;
	for(;stp;stp>>=1,trs=trs*trs) if(stp&1) res=res*trs;
//	for(int i=1;i<=k;i++) for(int j=1;j<=k;j++) printf("%d%c",res.a[i][j],(j==k)?'\n':' ');
	int sum=0;for(int i=1;i<=k;i++) sum=(sum+st.a[i][1]*res.a[k][i])%MOD;
	if(!((n+m)&1)) return printf("%d\n",sum),0;
	int ans=sum;
	memset(res.a,0,sizeof(res.a));memset(trs.a,0,sizeof(trs.a));
	memset(st.a,0,sizeof(st.a));
	for(int i=0;i<m;i++){
		int cnt=0;
		for(int j=1;j<=m;j++){
			if((j^m)&&!(s[j]^s[j+1])) cnt=(cnt+dfs(i,j,j+1))%MOD;
		}
		if(i) trs.a[k-((m-i+1)>>1)][i]=cnt;
		else st.a[m][1]=cnt;
	}
	for(int i=2;i<m;i++) trs.a[i][i-1]=1;
	if(m>1) st.a[1][1]=1;
	for(int i=m;i<k;i++) trs.a[i+1][i]=1;
	for(int i=1;i<m;i++) trs.a[i][i]=24;
	for(int i=m;i<k;i++) trs.a[i][i]=25;
	for(int i=1;i<=k;i++) res.a[i][i]=1;
	stp=(n+m+1)>>1;
	for(;stp;stp>>=1,trs=trs*trs) if(stp&1) res=res*trs;
	sum=0;for(int i=1;i<=k;i++) sum=(sum+st.a[i][1]*res.a[k][i])%MOD;
	printf("%d\n",(ans-sum+MOD)%MOD);
	return 0;
}
```



---

## 作者：_sys (赞：5)

题目要求的是不同的字符串个数，而不是操作数。所以我们考虑直接考虑这个回文串的形态。如果有一个回文串 $T$，我们判断其是否能作为答案的算法如下：

最初令 $l=0, r = |s| - 1$。从 $0$ 到 $\frac {|T| - 1}2$ 枚举 $T_i$，如果 $T_i = s_l = s_r$，那么 $l \leftarrow l+1, r \leftarrow r - 1$，否则如果 $T_i = s_l$，$l \leftarrow l + 1$，否则如果 $T_i = s_r$，$r \leftarrow r - 1$。最终我们检查是否有 $l > r$，如果是，则 $T$ 属于答案。

我们可以由此得到一个递推算法。设 $f_{i, l, r}$ 表示此算法进行到这个状态的 $T$ 的个数。终态 $\text{goal}_i$ 表示算法已经执行完毕的 $T$ 的个数。

如果 $s_l = s_r$，则有

$$\begin{cases}
    f_{i+1, l+1, r-1} \leftarrow f_{i, l, r} \\
    f_{i+1, l, r} \leftarrow 25f_{i, l, r} \\
\end{cases}$$

否则有

$$\begin{cases}
    f_{i+1, l+1, r} \leftarrow f_{i, l, r} \\
    f_{i+1, l, r - 1} \leftarrow f_{i, l, r} \\
    f_{i+1, l, r} \leftarrow 24f_{i, l, r}
\end{cases}$$

最后我们回收

$$\begin{cases}
    \text{goal}_{i} \leftarrow f_{i, l, l - 1} + f_{i, l, l - 2} \\
    \text{goal}_{i+1} \leftarrow \text{goal}_{i}
\end{cases}$$

这样每轮的状态数是 $O(|s|^2)$ 的，需要做 $O(n)$ 轮。

我们知道，每一个递推过程都对应着一个有限状态自动机。

**定义** 有限状态自动机是一个五元组 $M = (Q, \Sigma, \delta, q_0, F)$，其中 $Q$ 表示状态的集合，$\Sigma$ 表示字符集，$\delta:Q \times \Sigma \to Q$（输入是一个二元组 $(q, \sigma)$，输出一个 $Q$ 中的元素）表示转移函数，$q_0$ 表示 $M$ 的（唯一）起始状态，$F \subseteq Q$ 表示终止状态集合。

有限状态自动机从起始状态开始，一个字符接一个字符地读入一个字符串，并根据给定的转移函数一步一步地转移至下一个状态。在读完该字符串后，如果该自动机停在一个属于 $M$ 的接受状态，那么它就接受该字符串，反之则拒绝该字符串。

我们可以把 $Q$ 看作点集，$\delta$ 看作边集，$q_0$ 看作起点，$F$ 看作终点，那么 $M$ 便可以被看作一张有向图。一个被接受的字符串对应着图上一条从起点到某个终点的路径。

在自动机的视角下，递推过程的状态便是其状态，状态间的转移便是其转移，字符集便是这个过程的一种“操作”。比如在此题里，一个 $(l, r)$ 就对应着一个状态。填入一个 $T_i$ 就对应着一个操作，在每个状态那里可以得到一个转移。一个合法的 $T$ 就对应着自动机上一条从 $(0, |s| - 1)$ 到 $\text{goal}$ 的路径。于是我们将问题转化为了一个图上的路径问题。

现在考虑用组合的视角来看这个图。每条路径形如在每个点上走许多次自环，之后向前走。如果有 $a$ 个权值为 $24$ 的自环，那么便会有 $b = \lceil \frac{|s| - a}2 \rceil$ 个长度为 $25$ 的自环，其走过非自环边的次数为两者之和。而我们发现，其路径权值和与这些自环权值的顺序是无关的，所以我们可以将 $a$ 相同的全部归为一类。这样我们对每一种 $a$ 使用矩阵加速，复杂度为 $O(|s|^4 \log n)$。

一个观察是 $a$ 不同的图可以合并起来，我们在左侧从起点开始向下连出一个足够长的链，每个点有一个权值为 $24$ 的自环，再在右侧以终点为链尾向上反着连出一个足够长的链，每个点有一个权值为 $25$ 的自环。这样 $(a, b)$ 就可以对应为左侧的正数第 $a$ 个点往右侧倒数第 $b$ 个点连了一条边。这样所有的 $a$ 可以在一次加速中全部算出，复杂度为 $O(|s|^3 \log n)$。

当然，我们可以直接把其组合式列出来并使用组合计数的方法来优化。

![](https://cdn.luogu.com.cn/upload/image_hosting/90pgcr3u.png)



---

## 作者：KAMIYA_KINA (赞：4)

## Tag

动态规划，字符串。

## Description

给定一个字符串 $S$，往 $S$ 里面随便塞 $n$ 个字符，求最后的字符串为回文串的方案数。

$\texttt{data range:} n\leq 10^9, |S| \leq 200$.

## Solution

神题。

假设此时 $|S| + n$ 为偶数，方便我们进一步分析。

对于一个回文串而言，我们可以先对称构造出来，然后观察源字符串 $S$ 是不是这个字符串的一个子串。

我们设 $f_{i,l,r}$ 表示放第 $i$ 个字符，$S[l, r]$ 最多能匹配多少个，十分容易转移。

这样可以做到 $O(n|S|^2)$，显然是过不去的，然而我们可以用矩阵优化到 $O(|S|^6\lg(n+|S|))$，在这里引入了矩阵。

不过时间复杂度还是错误的，因为我们有 $O(|S|^2)$ 个状态。对于一般动态规划问题，这个时候我们就需要找到一个压缩状态的方法了。

我们发现实际上其转移非常少，因为一个状态到另一个状态的转移只有可能有 $O(1)$ 种。

但是对此我们还是没有很好的方法进行压缩转移，因为这实在是太困难了，还是要优化我们的状态。

这个时候引入一个非常玄学的概念，那就是状态中有两种点，一种是左右两边相同的点，一种是左右两边不同的点，特殊的，我们 $[i,i]$ 这样的点也是两个相同的点，我们定义前者为**绿点**，后者为**红点**，这里可以参考[ CQzhangyu 大佬的博客](https://www.cnblogs.com/CQzhangyu/p/8685601.html)中给到的图进行理解。

如果一条链上有 $k$ 个红点，那么这条链上一定有 $\left\lceil\dfrac{|S|-k}{2}\right\rceil$ 个绿点。

证明：一个红点的时候我们一定只能消掉一个点，使其长度减一，那么剩下的长度一定是绿点消掉的，而且绿点一次消俩，不过要考虑 $[i,i]$ 的特殊情况，所以是向上取整。

我们容易分析，如果一条链上有 $k$ 个红点，那么这两条链的转移状态是完全一致的，可以压缩起来。

分析到了这里，我们可以重新设计状态了，设 $f_{i,l,r}$ 为从 $[1,|S|]$ 走到 $[l,r]$ 需要走过 $i$ 个红点，这个过程可以用区间 dp 或者记忆化搜索完成，不多细说。

此时我们的复杂度来到一个比刚刚低很多的级别 $O(|S|^4\lg(n + |S|))$，~~有没有卡常大师可以试一下这个玩意过不过的去啊~~。

所以还是不够的，我们需要将这个状态压缩到 $O(|S|)$ 级别。红点和绿点有分歧，那么可以将红点分别构造，绿点分别构造，然后连红点到绿点的边就可以了，不难想到红点最多只有 $O(|S|)$ 个，绿点最多只有 $O(|S|)$ 个，我们整体的状态数就来到了 $O(|S|)$ 这个级别，实际上这个状态数大概是 $\dfrac 32 |S|$ 个，所以可以过掉本题，时间复杂度 $O(|S|^3\lg (|S|+n))$。

$|S|+n$ 为奇数的情况可以限定红点只能转移到形如 $[i,i]$ 的绿点上，然后用一开始的答案减去这部分就可以了。

本题考察了矩阵快速幂优化 dp 和状态压缩的种种技巧，虽然是出现在 CF 比赛中，但是非常有 OI 比赛的风格，希望这种题目多来点。

## Code

```cpp
const int N = 2e2 + 10;
const int M = 3e2 + 10;

int n, m, lim;
modint f[N][N][N], g[N];
char s[N];

struct Matrix {
    modint a[M][M];
    inline void init() { FOR(i, 0, M - 1) FOR(j, 0, M - 1) a[i][j] = 0; }
    modint *operator [] (const int x) {return a[x];}
    Matrix operator * (Matrix &tem) {
        Matrix ret;
        FOR(i, 0, lim) FOR(j, i, lim) FOR(k, i, j)
            ret[i][j] += a[i][k] * tem[k][j];
        return ret;
    }
    friend ostream &operator << (ostream &ou, const Matrix x) {
        FOR(i, 0, lim) FOR(j, 0, lim) ou << x.a[i][j] << " \n"[j == jj];
        return ou;
    }
    
} S, T;

void KSM(int y) {
    for(; y; y >>= 1, T = T * T)
        if(y & 1) S = S * T;
}

inline void solve() {
    cin >> (s + 1) >> m;
    n = strlen(s + 1);
    f[1][n][0] = 1;
    FOR(i, 1, n) ROF(j, n, i) {
        if(s[i] == s[j]) {
            FOR(k, 0, i + n - j - 1) {
                if(i + 1 < j) f[i + 1][j - 1][k] += f[i][j][k];
                else g[k] += f[i][j][k];
            }
        } else {
            FOR(k, 0, i + n - j - 1) {
                f[i + 1][j][k + 1] += f[i][j][k];
                f[i][j - 1][k + 1] += f[i][j][k];
            }
        }
    }
    lim = n + (n + 1) / 2 + 1;
    S.init(), T.init();
    S[0][1] = 1, S[0][lim - (n + 1) / 2] = g[0], T[lim][lim] = 26;
    FOR(i, 1, n) {
        T[i][i] = 24, T[i][lim - (n - i + 1) / 2] = g[i];
        if(i != n) T[i][i + 1] = 1;
    }
    FOR(i, n + 1, lim - 1) T[i][i + 1] = 1, T[i][i] = 25;
    KSM((n + m + 1) >> 1);
    modint ans = S[0][lim];
    if((n + m) & 1) {
        S.init(), T.init();
        FOR(i, 0, n) g[i] = 0;
        FOR(i, 0, n - 1) if(s[i] == s[i + 1]) FOR(k, 0, n)
            g[k] += f[i][i + 1][k];
        S[0][1] = 1, S[0][lim - (n + 1) / 2] = g[0];
        FOR(i, 1, n) {
            T[i][i] = 24, T[i][lim - (n - i + 1) / 2] = g[i];
            if(i != n) T[i][i + 1] = 1;
        }
        FOR(i, n + 1, lim - 1) T[i][i + 1] = 1, T[i][i] = 25;
        KSM((n + m + 1) >> 1);
        cout << ans - S[0][lim] << '\n';
    } else cout << ans << '\n';
    return ;
}
```

## Final

卡常技巧：由于我们的转移矩阵是一个上三角矩阵，所以可以只枚举上半部分就可以了。

---

## 作者：Fan_sheng (赞：3)

决定搞定这道看起来很吓人的题。

# Part 1

回文串分奇偶两种，先考虑**偶回文串**的情况。

可以把题目转化一下，相当于是说构造一个长度恰好为 $|s|+n$ 的回文串 $t$，使得 $s$ 是 $t$ 的子串（可能不连续），求不同的 $t$ 有多少个。

考虑一个朴素 dp。$dp[i][l][r]$ 表示已经构造好了 $t$ 的前 $i$ 位和末 $i$ 位，它与 $s$ 尽可能匹配后，$s$ 还剩下 $[l,r]$ 未匹配的方案数。换句话说，$s_{1\cdots l-1}$ 和 $s_{r+1\cdots |s|}$ 都已经按顺序出现在了当前的 $t$ 中。再设 $ans[i]$ 表示已经构造好了 $t$ 的前 $i$ 位和后 $i$ 位，并且已经能够完全匹配 $s$ 的方案数。

然后就可以在 $t$ 的第 $i+1$ 位和倒数 $i+1$ 位添上一个相同的字符，实现转移：

Case 1：$s_l=s_r\land r-l\le1$，
$$
ans[i+1]+=dp[i][l][r]
$$
$$
dp[i+1][l][r]+=25\times dp[i][l][r]
$$

前者表示添上的字符刚好是 $s_l$，已经可以构成完整的 $s$，后者表示添其他字符无法使匹配更进一步。其他的转移类似，就不再赘述。

Case 2：$s_l=s_r\land r-l>1$，
$$
dp[i+1][l+1][r-1]+=dp[i][l][r]
$$
$$
dp[i+1][l][r]+=25\times dp[i][l][r]
$$

Case 3：$s_l\neq s_r$，
$$
dp[i+1][l+1][r]+=dp[i][l][r]
$$
$$
dp[i+1][l][r-1]+=dp[i][l][r]
$$
$$
dp[i+1][l][r]+=24\times dp[i][l][r]
$$

对于 $ans$，都有：
$$
ans[i+1]+=26\times ans[i]
$$

于是答案就是 $ans[\lceil\frac{|s|+n}{2}\rceil]$。

递推形式，使用矩阵优化。然后有 $l,r$ 两维状态，时间复杂度 $\mathbb O(|s|^6\log n)$，就炸了。

# Part 2
我们发现这个 dp 的实质是在一个 **有限状态自动机**上的转移，也就是一个图上路径计数问题。

依然使用官图

![](https://cdn.luogu.com.cn/upload/image_hosting/mujgxlia.png)

解释一下这张图：

我们忽略掉 $dp$ 中 $i$ 这一维，只考虑 $l,r$ 之间的转移。每个节点就表示 $s$ 还未匹配的区间是 $[l,r]$。用有向边表示转移，就形成了 DAG+大量自环。绿红蓝分别表示自环数 $24,25,26$ 的三种点，其中只有终态（完全匹配）是蓝色。

这样答案就变成了从初态（$[1,|s|]$）到终态，走 $\lceil\frac{|s|+n}{2}\rceil$ 步的不同走法数。

状态数仍为 $|s|^2$ 级别。

# Part 3

接下来考虑压缩状态量。

**首先声明，以下的“路径”均指一条链，不论走了多少自环，只要经过的点相同就称为同一条路径**。

发现这样的性质：

**对于一条从初态到终态的路径，如果它经过了 $k$ 个红点，则它经过了 $\lceil \frac{|s|-k}{2}\rceil$ 个绿点**。

这是因为初态区间是 $[1,|s|]$，每出现一个红点，区间减小 $1$；每出现一个绿点，如果它代表的区间 $l=r$，区间减小 $1$，否则减小 $2$。

于是红点数量可以确定绿点数量了。由于同颜色点的自环数相同，可以知道**红点数量相同的路径对答案的贡献也相同**，即只要两条路径的红点数量一样，它们从初态到终态的不同走法数量就是一样多的。

把红点数量相同的路径称为一类路径，有 $\mathbb O(|s|)$ 类路径。

$cnt[i][l][r]$ 表示从点 $(l,r)$ 到终态有多少条路径经过了 $i$ 个红色点，这可以根据最开始推的 dp 方程 $O(|s|^3)$ 记忆化搜索出来。

再把不同类路径分离开来

![](https://cdn.luogu.com.cn/upload/image_hosting/do2z3eo6.png)

对于每类路径，上面的自环数是确定的，可以矩乘算出单条路径的走法数，再乘上相应的 $cnt[i][1][|s|]$，最后求和即可。

复杂度变为 $\mathbb O(|s|^4\log n)$，优化了很多，但还是歇菜了。

# Part 4

最后再考虑压缩一波状态。

![](https://cdn.luogu.com.cn/upload/image_hosting/mmbapg7v.png)

由于随着红点的增加，绿点的变化量有规律，所以可以很容易地把点数降到 $\mathbb O(|s|)$，上图的方法是可行的一种。

考虑一个常见的 trick：

> 设一个图的邻接矩阵为 $A$（$A_{i,j}=t$ 表示 $i$ 向 $j$ 连 $t$ 条边），$A^k$ 的第 $(i,j)$ 项就表示点 $i$ 走了 $k$ 步后到达点 $j$ 的方案数。

于是把图建出来，只需跑一遍矩乘就能求出所有类路径的答案，再乘上 $cnt$ 并求和。复杂度 $\mathbb O(|s|^3\log n)$。

**这是个 DAG，只有编号小的点能到达编号较大的点，矩乘内部可以剪枝减小常数**。

# Part 5

于是乎你会悲哀地发现我们忽略了奇回文串的情况。

然而前面的论述已经很完备了，奇回文较之偶回文唯一的不同在于：**代表区间 $[l,l+1]$ 的绿点无法连向终态，只有代表区间 $[l,l]$ 的绿点才行**。

考虑用之前的答案减去不合法的路径数。不合法的路径数就是走 $\lceil\frac{|s|+n}{2}\rceil-1$ 步，恰好走到代表区间长度为 $2$ 的绿点（最后留了一步走到终态蓝点）。

你可能会疑惑为什么恰好留一步走到蓝点，不能跑蓝点上的自环吗？**回看 dp 方程，如果跑自环，相当于在 $[l,l+1]$ 之间插了一堆其他字符组成了一个奇回文串，实际上是符合要求的。**

这个东西可以再记搜和矩乘一次算出来。此题就做完了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e4+7;
int n,m,R,G,B,tot,cnt[203][203][203],ans;
char s[203];
inline int add(int n){return n>=mod?n-mod:n;}
struct star{
	int a[403][403];
	friend star operator*(const star &a,const star &b){
		star c;
		memset(c.a,0,sizeof(c.a));
		for(int i=1;i<=tot;i++)
		for(int k=i;k<=tot;k++)
		for(int j=k;j<=tot;j++)c.a[i][j]=add(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j]%mod);
		return c;
	}
}base,mat;
inline star quickpow(star a,int b){
	star ans;
	for(int i=1;i<=tot;i++)
	for(int j=1;j<=tot;j++)ans.a[i][j]=(i==j);
	while(b){
		if(b&1)ans=ans*a;
		a=a*a,b>>=1;
	}return ans;
}
int dfs(int k,int l,int r){
	if(k<0)return 0;
	if(l>r)return (!k);
	if(cnt[k][l][r]>=0)return cnt[k][l][r];
	if(s[l]==s[r])cnt[k][l][r]=dfs(k,l+1,r-1);
	else cnt[k][l][r]=add(dfs(k-1,l+1,r)+dfs(k-1,l,r-1));
	return cnt[k][l][r];
}
int redfs(int k,int l,int r){
	if(k<0||l==r)return 0;
	if(l>r)return (!k);
	if(cnt[k][l][r]>=0)return cnt[k][l][r];
	if(s[l]==s[r])cnt[k][l][r]=redfs(k,l+1,r-1);
	else cnt[k][l][r]=add(redfs(k-1,l+1,r)+redfs(k-1,l,r-1));
	return cnt[k][l][r];
}
int main(){
	scanf("%s%d",s+1,&n),m=strlen(s+1);
	R=m-1,G=B=((m+1)>>1),tot=R+G+B;
	for(int i=1;i<=R;i++)base.a[i][i]=24;
	for(int i=R+1;i<=R+G;i++)base.a[i][i]=25;
	for(int i=R+G+1;i<=tot;i++)base.a[i][i]=26;
	for(int i=1;i<R+G;i++)base.a[i][i+1]=1;
	for(int i=R+1;i<=R+G;i++)base.a[i][i+G]=1;
	mat=quickpow(base,(n+m)>>1);
	if((n+m)&1){
		memset(cnt,-1,sizeof(cnt));
		for(int i=0;i<=R;i++)if(!((m-i)&1))
		ans=add(ans-1ll*mat.a[R-i+1][R+((m-i+1)>>1)]*redfs(i,1,m)%mod+mod);
		mat=mat*base;
	}
	memset(cnt,-1,sizeof(cnt));
	for(int i=0;i<=R;i++)
	ans=add(ans+1ll*mat.a[R-i+1][R+G+((m-i+1)>>1)]*dfs(i,1,m)%mod);
	printf("%d",ans);return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：2)

## 题目简述

> - 给定长度为 $m$ 的字符串 $s$，你可以插入 $n$ 个**小写字母**，问最后可能得到多少个**本质不同**的回文串？
> - $m\leq 200,n\leq 10^9$。时限 $\text{6s}$，答案对 $10^4+7$ 取模。

## 约定

- 定义 $s$ 的生成串为在其中插入若干小写字母形成的字符串。 
- 对于一条不一定简单的路径，去掉其中的自环组成新路径称之为「简化路径」。

## 解题思路

为了方便书写，我们下文中的 $n$ 指生成串长度，即「题目描述」当中的 $n+m$。

我们先考虑 $n$ 为偶数的情况。

首先 $s$ 的生成串 $t$ 的充要条件是 $s$ 是 $t$ 的一个子串（不一定连续）。由于我们需要生成串是回文串，我们可以考虑以子序列自动机一样贪心地去匹配。不难想到 dp：$f_{i,l,r}$ 表示当前已经考虑生成串的前后 $i$ 位，而且当前 $s$ 未匹配段为 $[l,r]$。考虑转移：

- 如果 $l>r$ 我们称之为「目标点」，同样按照下面转移。
- 如果 $l\leq r$ 且 $s_l=s_r$ 那么有 $25$ 的权值会传到自己，$1$ 的权值传给 $f_{i+1,l+1,r-1}$。
- 如果 $l\leq r$ 且 $s_l\not = s_r$，那么有 $24$ 的权值给自己，$1$ 的权值传给 $f_{i+1,l+1,r}$ 和 $f_{i+1,l,r-1}$。

由于 $n$ 很大，不难想到矩阵优化。由于点数是 $\mathcal O(m^2)$ 的，所以时间复杂度 $\mathcal O(m^6\log n)$。爆炸。

我们继续观察上面的 dp 转移，不难发现它本质上是在走 DAG。如例子 $s=\texttt{abbac}$，它对应的转移如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/5rlgl9wv.png)

其中点旁边的数字表示自环数，$\texttt ?$ 表示已经匹配的点。

我们需要从 $[1,m]$ 走到 $\text{goal}$。不难发现当 $n$ 较大的时候我们大部分时间都在走自环。但是不难发现「简化路径」的长度是 $\mathcal O(m)$ 的，我们考虑从简化路径入手。

一个简化路径加上自环所产生的权值应当只与其中 $24-$度点的个数 $u$ 和 $25-$度点的个数 $v$ 有关。不难发现 $v=\left\lceil\dfrac{n-u}{2}\right\rceil$，这是因为每次经过一个 $24-$度点未匹配的长度就会减少 $1$，经过一个 $25-$度点未匹配的长度会减少 $2$，最终会达到 $0$ 或 $-1$ 的长度。

以此，我们只需要求出到达目标点 $\text{goal}$ 的路径且经过 $u$ 个 $24-$度点的个数 $g_{\text{goal},i}$，再乘上经过 $u$ 个 $24-$度点和 $v=\left\lceil\dfrac{n-u}{2}\right\rceil$ 个 $25-$度点组成路径的权值 $val_{u,v}$ 即可。后面讨论 $g,val$ 的求法。

首先 $g$ 的求法比较简单，只要一次记忆化搜索即可。定义 $g_{l,r,k}$ 表示在状态 $[l,r]$ 经过 $k$ 个 $24-$度点的方案数即可。

然后 $val$ 的求法比较奇妙。首先直观的想法是推组合数，不过这个玩意不好推，我们考虑另一种方法也就是再把它变成图，变回矩阵乘法。

![](https://cdn.luogu.com.cn/upload/image_hosting/q99kecpp.png)

上图是一个 $u=2,v=4$ 的例子。

这样子复杂度是 $\mathcal O(m^4\log n)$ 的，依然不可接受。

但是利用矩阵乘法求出的是两两点之间长度一定的路径数量，不难可以把所有的路径合成一个更大的图，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/2i4csfcz.png)

实际上把所有边反过来更符合上面的图，不过代码使用的是这张图的建模。

当我们需要查询 $2$ 个红点，$4$ 个蓝点之间的答案时，只需要调用红点上面的「目标点」和对应蓝点之间矩阵的数值即可。

这下可以做到 $\mathcal O(m^3\log n)$ 求出 $val$。

最终时间复杂度为 $\mathcal O(m^3\log n)$，轻微卡常。

----

别忘了我们上面假设了 $n$ 为偶数，当 $n$ 为奇数的时候只要减去 $n-1$ 步时还有一步到终点的方案即可。

### 代码实现

不严谨的来说，直接暴力建是 $\mathcal O((3m)^3\log n)$ 的，显然过不去。但是注意到 $v$ 的值域比较小，这样我们只用建一半左右，矩阵变到 $2m$。然后这个矩阵还是三角矩阵，容易优化一个 $\dfrac16$ 的常数，得以通过。

还要注意的是 $n$ 为偶数时需要求出 $n-1$ 步的矩阵，这里不用两次矩阵快速幂。只要求出 $A^{n-1}$ 再乘上 $A$ 就可以得到 $A^n$ 了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
#define int youzi_xinzuo_jijiji
const int MAXN=205;
const int MOD=10007;
void add(int &x,int y){x+=y;if(x>=MOD)x-=MOD;} 
int n,m,sz;
string s;
int rep_24[MAXN],rep_25[MAXN],rep_goal[MAXN];
int f[MAXN][MAXN][MAXN];// f[l,r,k] 从 [l,r] 到 goal 经过 k 个 24- 节点的方案数 
struct matrix{
int a[MAXN<<1][MAXN<<1];
matrix(){memset(a,0,sizeof(a));}
friend matrix operator *(matrix x,matrix y){
	matrix z;
	for(int i=1;i<=sz;i++)
		for(int k=i;k<=sz;k++) if(x.a[i][k])
			for(int j=k;j<=sz;j++)
				add(z.a[i][j],x.a[i][k]*y.a[k][j]%MOD);
	return z;
} 
}A,B;
matrix ksm(matrix a,int b){matrix res;for(int i=1;i<=sz;i++)res.a[i][i]=1;while(b){if(b&1)res=res*a;a=a*a,b>>=1;}return res;} 
void build(){
	for(int i=(n+1)/2;i>=1;i--){
		rep_goal[i]=++sz;rep_25[i]=++sz;
		if(i<(n+1)/2) A.a[rep_25[i+1]][rep_25[i]]=1;
		A.a[rep_25[i]][rep_25[i]]=25;
		A.a[rep_goal[i]][rep_25[i]]=1;
	} 
	A.a[rep_25[1]][rep_goal[0]=++sz]=1;
	for(int i=1;i<=n;i++){
		rep_24[i]=++sz,
		A.a[rep_24[i]][rep_24[i]]=24;
		if(i>1) A.a[rep_24[i-1]][rep_24[i]]=1;
	} 
	A.a[rep_25[1]][rep_24[1]]=1;
	for(int i=0;i<=n;i++) A.a[rep_goal[i]][rep_goal[i]]=26;
	B=ksm(A,(m+1)/2-1),A=B*A;
	return;
}
int query(int x,int y){return A.a[rep_goal[x]][(y?rep_24[y]:rep_25[1])];}// x 25, y 24  
int query1(int x,int y){return B.a[rep_25[x]][(y?rep_24[y]:rep_25[1])];}// x 25, y 24  
int dfs(int l,int r,int k){
	if(k<0) return 0;
	if(f[l][r][k]>=0) return f[l][r][k];
	if(l>r) return (k==0);
	int ans=0;
	if(s[l]==s[r]) ans=dfs(l+1,r-1,k);
	else ans=(dfs(l+1,r,k-1)+dfs(l,r-1,k-1))%MOD;
	return (f[l][r][k]=ans);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>s>>m;n=s.length(),m+=n;
	s=" "+s;
	build();
	memset(f,-1,sizeof(f));
	ll ans=0;
	for(int i=0;i<=n;i++){
		ans+=dfs(1,n,i)*query((n-i+1)/2,i)%MOD;
		if((m&1)&&(n-i)%2==0) ans-=dfs(1,n,i)*query1((n-i+1)/2,i)%MOD;
	}
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```



---

## 作者：WeLikeStudying (赞：2)

- 你以为它需要字符串算法吗？
- 不，它需要的是你的脑子(╯▔皿▔)╯。
- 感谢 [$\text{ZillionX}$](https://www.luogu.com.cn/user/283913) 大佬送出的思维好题，愿其信息学道路光芒璀璨。
- 但是洛谷将我已经打好的文章给吃了 qwq，所以我只好重新打一份。
- 本文所有的字符串符号来源于[此文](https://www.luogu.com.cn/blog/luo1gu1zui1bang1/post-zi-fu-chuan-lun)。

**题意**
- [题目](https://www.luogu.com.cn/problem/CF506E)。
- 给定字符串 $s$ 和数字 $n$，计算在该字符串中加入 $n$ 个字符后生成的回文串的个数。
- $|s|\le 200,n\le 10^9$。

**分析**
- 首先看到这个数据范围你会想到什么算法，一个数超级大，另一个数却超级小，矩阵乘法满足这个要求。
- 还有一个特殊的要求，那就是不同的操作但最后字符串相同的算作一种方案，做过[这道](https://www.luogu.com.cn/problem/AT3878)的应该都知道如何应对，应该从结果而非过程入手。
- 所以这道题目就被转化为了这种形式：计算以 $s$ 为子序列的长度为 $|s|+n$ 的回文串的个数。
- 但转化到这里并没有很好地解释这题与矩阵乘法的关系，我们先对这题进行一个简化，即计算以 $s$ 为子序列，长度为 $|s|+n$ 的字符串个数，然后找到它与矩阵乘法的关系。
- 做过[这道](https://www.luogu.com.cn/problem/AT3878)应该都知道这题一种常见的思路是标准化。
- 如何标准化？遵循贪心匹配的原则，从左到右匹配上，最后能够匹配上的一定是可以的，我们可以列出状态转移，并将其表示成矩阵的形式，这增强了我们的信心。
- 对于回文串的情况，我们希望找到一种类似的方法进行标准化。
- 没错，容易将其标准化为如下形式：相同的字符可以分别匹配掉 $s$ 的第一个位置和最后一个位置，当然，对于奇回文串，情况比较特殊，不过我们只需要特别加上只剩下一个字符的情况即可。
- 接下来我们来表示成一个形式化的式子，设矩阵 $A(i,j)$ 为当前 $s(i,j)$ 还没有完成匹配的方案数，初始时 $A(i,j)=[i=1][j=|s|]$。
- 我们考虑多一对字符串的贡献。
- 对于所有 $A(i,j)$：如果 $i\le j$，如果 $s(i)= s(j)$ 那么转移 $25$ 的贡献到 $A(i,j)$，转移 $1$ 的贡献到 $A(i+1,j-1)$，如果 $s(i)\ne s(j)$ 那么转移 $24$ 的贡献到 $A(i,j)$，转移 $1$ 的贡献到 $A(i+1,j)$，转移 $1$ 的贡献到 $A(i,j-1)$，然后我们就有了 $O(|s|^2n)$ 的算法，[代码实现](https://www.luogu.com.cn/paste/k36vmya6)。
- 问题来了，这鬼东西也能够矩乘优化吗？如果表示为 $|s|^2\times |s|^2$ 的矩阵，我们会获得 $O(|s|^6\log n)$ 的~~优秀~~时间复杂度，这显然不可接受。
- 不过我们有对于这是正解的自信，所以理理思维。

**思维**
- 我们有的工具是什么？
- 使用矩阵乘法，给出一个点数为 $m$ 的图，用每条边表示它的重数，我们可以利用矩阵乘法在 $O(m^3\log n)$ 的时间复杂度内求出该图上所有不同的长度为 $n$ 的（不一定简单的）路径。
![](https://cdn.luogu.com.cn/upload/image_hosting/pewjs3fn.png)
- 我们一开始的思路就是将整个关系图建成图直接暴力上矩阵乘法，然后得到 $O(|s|^6\log n)$ 的不可过复杂度。
- 我们唯一的方法就是尝试发现性质，简化问题的规模。
- 性质有什么？
- 我们只需要考虑起点到终点的情况，这个图也很有特点，除去所有的自环，它是一个无权（边权都为 $1$）的有向无环图，而且除了结尾有一个权为 $26$ 的自环，中间的自环权不是 $24$ 就是 $25$。
- 考虑从起点到终点的任意一条路径（长度为 $\lceil|s|/2\rceil$ 到 $s$），容易发现，$24,25$ 权重的自环是顺序是无关紧要的，重要的是它们的个数。（可以尝试建立双射证明这点）
- 所以如果我们 $O(|s|^3)$ 计算所有可能的本质不同的路径（容易发现它们的条数是 $O(|s|)$ 的），计算它们分别有几条，再分别对它们进行矩阵乘法，复杂度是 $O(|s|^4\log n)$ 的。
- 当然，这似乎显得很浪费，状态之间有着相当多的相似性，我们将所有可能的状态分为自环 $24$ 和自环 $25$ 两层，上下的连边之权重恰好为起点到终点这条路径（我们算出来的）条数，对这条类似于路径的东西进行矩阵乘法，复杂度就是 $O(|s|^3\log n)$，为可过复杂度。
![](https://cdn.luogu.com.cn/upload/image_hosting/yfh2vfya.png)

**细节问题**
- 如何特判奇回文串的情况？
- 感觉把 $A(i,i)$ 强行设为终止状态跑就可以了（其实感觉有许多方法）。
- 另外：通过自环为 $24$ 的个数 $c$ 其实也可以推出自环为 $25$ 的个数为 $\lceil \frac{n-c}2\rceil$。
- [代码实现](https://www.luogu.com.cn/paste/qn3mu0do)，轻微卡常，可以尝试利用有向无环图的性质使得矩阵乘法常数变为原来 $1/6$。
- 感觉教训就是要充分利用性质，我直接研究一般化的问题发现不可做，结果和[大佬](https://www.luogu.com.cn/user/52881)讨论他弄出了一大堆基于性质的优化（我直接尴尬。

---

## 作者：shao0320 (赞：2)

#### CF506E Mr. Kitayuta's Gift

首先考虑一下最终字符串字符数为偶数，即$2|(n+|s|)$的情况。

我们考虑从两边往中间不断添加字符，那么一个合法的解就是这个最终字符串中的某个子序列为$s$。

那我们从两边不断加字符的过程中，考虑这个新字符串和原字符串的匹配，一定也是不断地从左右两边新匹配一些字符的。

那么考虑这样一个$dp$,$f(i,l,r)$表示已经从左右两边各加了$i$个字符，左边匹配到了$s[l]$,右边匹配到了$s[r]$，使新字符串回文的方案数。转移只需要讨论$s[l]$和$s[r]$是否相等即可。

但这样做复杂度是依赖于$n$的，不幸的是本题$n$非常大，会歇逼。

考虑这个匹配的过程实际上是在一个$DAG$上走路，问$(n+|s|)/2$步走到重点的方案数（~~skr~~）。如果范围小一点的话这实际上是个矩阵乘法的经典问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/j8ml2yly.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图所示，红点有两种可能是因为两边的字符种类不一样，可以添加左边或右边将其改成回文并多匹配一位，而绿点只有一种选择使其多匹配一位，而自环是因为可以加入别的字符。

但这个图的节点数有$|s|^2$个，直接大力矩乘的话就变成$O(|s|^6)$级别的了，更别提还要快速幂，肯定爆炸。

考虑优化，我们如果单拿出一条链出来的话，那么是很好算的，但是链的条数依旧很多，但我们考虑两条不一样的链，他们的绿点和红点数相同，只是排列方式（先后顺序）不同，那么他们的答案实际上是一样的，也就是说我们可以把这些看起来不同的链一起处理。我们可以强制让他先走一堆红点之后再走一堆绿点。

但是如果暴力找链还是会挂掉的，考虑$dp$，设$g(i,j,k)$表示匹配到$(i,j)$，走了$k$个红点的方案数，讨论一下$s[l]$和$s[r]$是否相等即可。

处理出了每种链的条数后，这里有一个性质，就是因为走一个红点实际上少一个字符，走一个绿点少两个字符，那么如果一条链上有$x$个红点$y$个绿点，那么一定满足$x+2y=n$或$x+2y=n-1$，也就是走$x$个红点就会走$\lceil \frac{|s|-x}{2}\rceil$个绿点，根据这个性质，我们可以构造一张这样的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/bxvpphq3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在下边这张图中跑矩阵快速幂即可。

还有最后一个问题就是如果最终字符串长度为奇数怎么办。

观察最上边的图，答案为奇数就意味着最后剩两个字符的绿点无法转移到终点，那么我们先让他多走一步使得这些可以走到终点，最后再减去他们的贡献即可，方法就是只考虑这种的转移，强制让这样的绿点作为终点并且取消终点的自环

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 205
#define mod 10007 
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
char ch[N];
int n,m,f[N][N][N],g[N],MAXN;
struct Martix
{
	int a[N<<1][N<<1];
}A,B;
Martix operator*(Martix a,Martix b)
{
	Martix c;
	memset(c.a,0,sizeof(c));
	for(int i=0;i<=MAXN;i++)
	{
		for(int j=i;j<=MAXN;j++)
		{
			for(int k=i;k<=j;k++)
			{
				c.a[i][j]+=a.a[i][k]*b.a[k][j];
				c.a[i][j]%=mod;
			}
		}
	}
	return c;
}
void ksm(int b)
{
	while(b)
	{
		if(b&1)A=A*B;
		B=B*B;b>>=1;
	}
}
int main()
{
	scanf("%s",ch);m=read();n=strlen(ch);
	f[0][n-1][0]=1;
	for(int i=0;i<n;i++)
	{
		for(int j=n-1;j>=i;j--)
		{
			if(ch[i]==ch[j])
			{
				for(int k=0;k<i+n-j;k++)
				{
					if(i+1<j)f[i+1][j-1][k]+=f[i][j][k],f[i+1][j-1][k]%=mod;
					else g[k]+=f[i][j][k],g[k]%=mod; 
				}
			}
			else
			{
				for(int k=0;k<i+n-j;k++)
				{
					f[i+1][j][k+1]+=f[i][j][k],f[i+1][j][k+1]%=mod;
					f[i][j-1][k+1]+=f[i][j][k],f[i][j-1][k+1]%=mod;
				}
			}
		}
	}
	MAXN=n+(n+1)/2+1;
	A.a[0][1]=1;A.a[0][n+1]=g[0];B.a[MAXN][MAXN]=26;
	for(int i=1;i<=n;i++)B.a[i][i]=24,B.a[i][i+1]=1,B.a[i][MAXN-(n-i+1)/2]=g[i];
	B.a[n][n+1]=0;for(int i=n+1;i<MAXN;i++)B.a[i][i+1]=1,B.a[i][i]=25;
	if((n+m)%2==1)
	{
		ksm((n+m+1)/2);
		int ans=A.a[0][MAXN];
		memset(A.a,0,sizeof(A.a));
		memset(B.a,0,sizeof(B.a));
		memset(g,0,sizeof(g));
		for(int i=0;i<n-1;i++)
		{
			if(ch[i]==ch[i+1])
			{
				for(int j=0;j<=n;j++)
				{
					g[j]+=f[i][i+1][j];
					g[j]%=mod;
				}
			}
		}
		A.a[0][1]=1;A.a[0][n+1]=g[0];
		for(int i=1;i<=n;i++)B.a[i][i]=24,B.a[i][i+1]=1,B.a[i][MAXN-(n-i+1)/2]=g[i];
		B.a[n][n+1]=0;for(int i=n+1;i<MAXN;i++)B.a[i][i+1]=1,B.a[i][i]=25;
		ksm((n+m+1)/2);
		printf("%d\n",(ans-A.a[0][MAXN]+mod)%mod);
	}
	else
	{
		ksm((n+m)/2);
		printf("%d\n",A.a[0][MAXN]);
	}
	return 0;
}
```

##### 

---

