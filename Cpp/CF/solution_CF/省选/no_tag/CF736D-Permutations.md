# Permutations

## 题目描述

奥斯塔普·本德 (Ostap Bender) 开始忧心忡忡，因为人们已经开始逐渐忘记他是伟大的组合学带师。现在，他想秀一下自己高超的组合技术。

现在，他正研究着长度为 $n$ 的排列。另外。他还有 $m$ 个限制，第 $i$ 个限制可以表示成数对 $(a_i, b_i)$，代表排列中的第 $a_i$ 个位置可以是 $b_i$。

现在他已经知道，满足所有限制的排列数量有奇数个。而他想知道的是，对于每一个限制，在去掉（且仅去掉）它之后，满足所有限制的排列数量是否仍然是奇数个。

## 样例 #1

### 输入

```
2 3
1 1
1 2
2 2
```

### 输出

```
NO
YES
NO
```

## 样例 #2

### 输入

```
3 3
1 1
2 2
3 3
```

### 输出

```
NO
NO
NO
```

## 样例 #3

### 输入

```
3 7
3 3
3 1
1 3
1 1
2 2
1 2
2 1
```

### 输出

```
YES
NO
NO
NO
YES
NO
NO
```

# 题解

## 作者：iotang (赞：7)

## 题目翻译

现在，你有一个二分图，点数为 $2n$。

已知这个二分图的完备匹配的个数是奇数。

现在你要知道，删除每条边后，完备匹配个数是奇数还是偶数。

$1 \leq n \leq 2000$。

## 如何解决它？

先把邻接矩阵搞出来，把它叫做 $G$，对于每个限制 $(a_i, b_i)$，让 $G_{a_i, b_i} = 1$。

可以看出，如果有一个合法的排列 $p_1, \dots , p_n$，那么 $G_{i, p_i}$ 都是 $1$。

有想到什么吗？

还记得行列式的式子吗？

你问我行列式前面 $(-1)^{???}$ 的系数怎么办？我们只关心奇偶性（对 $2$ 取模），$1$ 和 $-1$ 对我们来说是一样的，所以我们就可以不管它了。（其实这个东西叫做积和式）

所以，当邻接矩阵 $G$ 的行列式是奇数的时候，合法的排列数量也是奇数。

问题到现在，可以变成：把每个位置变成 $0$ 后，行列式是奇数还是偶数。

减去一个位置，行列式的变化怎么算？

大家应该都知道，有一个东西叫做代数余子式。$(-1)^{???}$ 的系数扔掉之后，只要看它的奇偶性就可以了。

$n$ 有 2000 诶，怎么把它们快速算出来？

大家应该都知道，有一个东西叫做伴随矩阵。求出伴随矩阵，就相当于求出所有位置的代数余子式。

因为 $G^{*} = G^{-1} |G|$，$|G|$ 是奇数（题面里面已经说了），那么只要求 $G^{-1}$ 就完事了！!1

$n$ 有 2000 诶，怎么把它快速算出来？

单走一个~~搞死乔丹算法~~高斯约当算法求个矩阵逆，就可以用神必技巧做到 $O(n^3 / 64)$（用 bitset 优化一下）甚至 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef long double louble;

template<typename T1, typename T2> inline T1 max(T1 a, T2 b)
{
	return a < b ? b : a;
}
template<typename T1, typename T2> inline T1 min(T1 a, T2 b)
{
	return a < b ? a : b;
}

const char lf = '\n';

namespace ae86
{
	const int bufl = 1 << 15;

	char buf[bufl], *s = buf, *t = buf;

	inline int fetch()
	{
		if (s == t)
		{
			t = (s = buf) + fread(buf, 1, bufl, stdin);
			if (s == t)return EOF;
		}
		return *s++;
	}

	inline int ty()
	{
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c))a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::ty;

const int _ = 2007, __ = _ + _, _e = 500007;

int n, m, ea[_e], eb[_e];
bitset<__> f[_];

int main()
{
	ios::sync_with_stdio(0), cout.tie(nullptr);

	n = ty(), m = ty();
	for (int i = 1; i <= m; i++)ea[i] = ty(), eb[i] = ty(), f[ea[i]][eb[i]] = 1;
	for (int i = 1; i <= n; i++)f[i][n + i] = 1;
	for (int i = 1; i <= n; i++)
	{
		int a = i;
		while (a < n && !f[a][i])a++;
		if (!f[a][i])throw "c**a b***t";
		swap(f[i], f[a]);
		for (int j = 1; j <= n; j++)if (j != i && f[j][i])f[j] ^= f[i];
	}
	for (int i = 1; i <= m; i++)
		cout << (f[eb[i]][ea[i] + n] ? "NO" : "YES") << lf;

	return 0;
}
```

代码里和谐了一些不好的词语。

---

## 作者：moongazer (赞：4)

[$\mathfrak{View\space it\space on\space my\space Blog}$](https://blog.seniorious.cc/2020/CF-736D/)

## 题意

左右各 $n$ 个点，$m$ 条边的二分图，满足完美匹配数为奇数个，问分别去掉每一条边后，完美匹配数是否仍为奇数个

$n\le2000$，$m\le5\times10^5$

## 分析

首先发现完美匹配数为 $\sum\limits_{\sigma\in S_n}\prod\limits_{i=1}^n\left[M_{i,\sigma(i)}=1\right]$，其中 $M$ 为邻接矩阵，$S_n$ 为所有 $1\sim n$ 的置换构成的集合

由于是 $\bmod2$ 意义下的，且 $-1\equiv1\pmod2$ 故有 $Ans\equiv\sum\limits_{\sigma\in S_n}\operatorname{sgn}(\sigma)\prod\limits_{i=1}^n\left[M_{i,\sigma(i)}=1\right]=\det(M)\pmod2$

考虑容斥，去掉一条边的完美匹配数为奇数等价于包含一条边的完美匹配数为偶数，必须包含一条边即为删掉一行一列，于是等价于它的余子式为偶数，同样的，由于 $(-1)^{i+j}$ 不影响答案直接求代数余子式即可，又有矩阵 $M$ 在 $i$ 行 $j$ 列的代数余子式等于伴随矩阵 $M^{*}$ 的 $j$ 行 $i$ 列，于是可以求伴随矩阵 $M^{*}=\det(M)M^{-1}$ 直接高斯消元就好了，$\det(M)$ 一定为奇数

注意到运算在 $\bmod2$ 意义下进行，加减和异或运算等价，直接使用 bitset 进行优化即可，复杂度 $\operatorname{O}(\frac{n^3}{\omega})$

## 代码
```cpp
constexpr int N = 2001;
constexpr int S = 4001;
constexpr int M = 500001;

void Gauss(int n);

std::bitset<S> a[N];
int u[M], v[M];
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    read(u[i]), read(v[i]);
    a[u[i]][v[i]] = true;
  }
  for (int i = 1; i <= n; ++i) {
    a[i][i + n] = true;
  }
  Gauss(n);
  for (int i = 1; i <= m; ++i) {
    if (a[v[i]][u[i] + n]) {
      puts("NO");
    } else {
      puts("YES");
    }
  }
  return 0;
}

void Gauss(int n) {
  for (int i = 1; i <= n; ++i) {
    int now = 0;
    for (int j = i; j <= n; ++j) {
      if (a[j][i]) {
        now = j;
      }
    }
    if (now != i) {
      std::swap(a[i], a[now]);
    }
    for (int j = 1; j <= n; ++j) {
      if (i != j && a[j][i]) {
        a[j] ^= a[i];
      }
    }
  }
}
```


---

## 作者：lingying (赞：3)

# 题意

长度为 $n$ 的排列 $p$ 有 $m$ 个限制，每个限制两个整数 $a,b$ 表示 $p_a$ 可以等于 $b$。保证满足上述限制的方案数为奇数，现在你需要对于每一个限制求出去掉这个限制方案数是否还为奇数。

$n\le 2000,m\le \min(n^2,5\times 10^5)$。

# 题解

**本题涉及知识点有点多，建议对矩阵相关操作不熟悉的配合百度搜索食用。**

判断方案数的奇偶，我们可以看作对 $2$ 取模，假设一开始的方案数为 $x$，去掉过后的方案数为 $y$，则需要 $x\equiv y \pmod 2$。

我们设 $A_{x,y}$ 表示 $p_x$ 能否等于 $y$，能为 $1$，否则为 $0$。我们尝试把 $x$ 用一个式子表达出来，可以得到 $\sum\limits_{p}\prod\limits_{i=1}^n A_{i,p_i}$。发现跟行列式极其相似。


> **行列式**

>定义一个 $n\times m$ 的矩阵 $A$，其行列式为 $\sum\limits_{p}(-1)^k \prod\limits_{i=1}^n A_{i,p_i}$，$k$ 为排列 $p$ 的逆序对数量。

虽然有一个 $(-1)^k$，但是在模 $2$ 下没有任何影响，所以我们接下来可以看作方案数就是行列式的结果（模 $2$ 的情况下，平常不能这么用）。

现在我们考虑删掉一个限制求剩下的方案数，假设第 $i$ 个限制为 $p_a$ 可以等于 $b$，考虑容斥即为总的方案数减去固定 $p_a=b$ 的方案数，对应到我们的矩阵上就是删去第 $i$ 行第 $j$ 列，剩下这个 $(n-1)\times (m-1)$ 这个矩阵的行列式。

定睛一看发现这个东西就是伴随矩阵。

> **伴随矩阵**

> 定义一个 $n\times m$ 的矩阵 $A$，其伴随矩阵，记为 $T$，大小为 $m\times n$，$T_{i,j}=(-1)^{i+j}M_{j,i}$，其中 $M_{i,j}$ 为代数余子式。

额，代数余子式。

> **代数余子式**

> 定义一个 $n\times m$ 的矩阵 $A$，其代数余子式记为 $M_{i,j}$ 表示将原矩阵第 $i$ 行第 $j$ 列删去过后所得的行列式。

我们发现把伴随矩阵处理出来就可以 $O(1)$ 回答每个询问。

这里有一个性质：

$$
 T=\dfrac{A^{-1}}{\det(A)}
$$

证明可以百度，由于是个很入门的伴随矩阵定理这里不单独证明。

由于对 $2$ 取模，题目又说了初始方案数为奇数，所以 $\det(A)$ 可以视作没有，所以我们现在转换为求 $A$ 的逆矩阵，套个板子就可以了，由于 $n\le 2000$，需要使用 bitset 优化一下。

时间复杂度为 $O(\dfrac{n^3}{w})$。

# 代码

```
#include<bits/stdc++.h>
using namespace std;

const int N=4005,M=5e5+5;

int n,m;
int qry[M][2];
bitset<N> f[N];

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>qry[i][0]>>qry[i][1];qry[i][0]--,qry[i][1]--;
		f[qry[i][0]][qry[i][1]]=1;
	}
	for(int i=0;i<n;i++)f[i][n+i]=1;
	for(int i=0;i<n;i++)
	{
		int p=0;
		for(int j=i;j<n;j++)
			if(f[j][i])
				p=j;
		if(i!=p)swap(f[i],f[p]);
		for(int j=0;j<n;j++)
			if(i!=j&&f[j][i])
				f[j]^=f[i];
	}
	for(int i=1;i<=m;i++)puts(f[qry[i][1]][qry[i][0]+n]?"NO":"YES");
	return 0;
}
```





---

## 作者：45dino (赞：2)

同步于我的博客，地址略。

---
首先对于一个排列，如何检查是否合法？可以把给定的 $m$ 个限制写成一个 $n\times n$ 的矩阵 $A$，$A_{i,l}=1$ 表示第 $i$ 个数可以是 $l$。那么一个合法的排列 $p$ 必须满足 $A_{1,p_1}=A_{2,p_2}=A_{3,p_3}=\dots=A_{n,p_n}=1$。考虑如何快速算出合法排列的个数模 $2$ 的结果。

---

## 积和式

一个 $n\times n$ 的矩阵的积和式定义为：
$$
\operatorname {prem}(A)=\sum_{\sigma \in S_n} \prod_{i=1}^n A_{i,\sigma_i}
$$
其中 $\sigma$ 表示一个排列，$S_n$ 表示长度为 $n$ 的所有排列。

根据定义，$\operatorname {prem}(A)$ 就是合法排列的个数，因为当且仅当 $\sigma$ 是一个合法排列时，$\prod_{i=1}^n A_{i,\sigma_i}$ 才会对答案造成 $1$ 的贡献。

但是积和式的计算被证明是一个 $\#P$ 完全问题，计算难度还在 $NP$ 问题之上，因此需要考虑用别的思路进行优化。**之所以会存在更优的做法，是因为只需要求原式模 $2$ 的值。** 因此我们可以考虑求一些其他东西。

## 行列式

这应该是大家更熟悉的东西。一个 $n\times n$ 的矩阵的行列式式定义为：
$$
\operatorname {det}(A)=\sum_{\sigma \in S_n} \operatorname {sgn}(\sigma)\prod_{i=1}^n A_{i,\sigma_i}
$$
其中 $\operatorname{sgn}(\sigma)$ 表示 $\sigma$ 的符号差，如果 $\sigma$ 有奇数个逆序对为 $-1$，否则为 $1$。

行列式和积和式的形式非常相似，容易发现，$\operatorname {prem}(A)\equiv\operatorname {det}(A)(\bmod 2)$。而行列式显然是可以用多项式复杂度求得的。

（我认为检查 hack 数据的 validator 大概就是这样实现的，因为原矩阵 $A$ 有奇数个合法排列等价于行列式模 $2$ 余 $1$）

因此问题变成了，给定一个 $n\times n$ 的矩阵，对于每个 $1$，求把 $1$ 变成 $0$ 后，行列式是否能被 $2$ 整除。

枚举 $m$ 次是不行的。

## 代数余子式和伴随矩阵

如何一次性求出所有的行列式？

对于一个 $n\times m$ 的矩阵 $A$，定义矩阵 $A$ 的 $(i,j)$ 代数余子式为 $(-1)^{i+j}M_{i,j}$，其中 $M_{i,j}$ 表示原矩阵去掉第 $i$ 行和第 $j$ 列后，剩下一个 $(n-1)\times(m-1)$ 的矩阵的行列式。将矩阵每一个位置的代数余子式组合成一个新的 $m\times n$ 的矩阵 $A^*$，称为伴随矩阵，即 $A^*_{i,j}=C_{j,i}$。

假如 $A_{i,j}=1$，那么根据定义，$C_{i,j}$ 模 $2$ 的值就是钦定排列的第 $i$ 个数是 $j$，合法排列的个数模 $2$ 的值。换句话说，就是如果把 $A_{i,j}$  变成 $0$，合法排列的个数会减少奇数个还是减少偶数个。由于知道初始有奇数个合法的排列，可以借此判断把 $A_{i,j}$ 变成 $0$ 后，剩下的合法排列的奇偶性。**因此如果能求出 $A^*$，就能知道每一个满足 $A_{i,j}=1$ 的位置的代数余子式 $M_{i,j}$，进而一次性求出所有答案。**

伴随矩阵和矩阵逆有密不可分的联系，具体来说，如果原矩阵 $A$ 有逆，那么：
$$
A^{-1}={A^*\over |A|}
$$
其中 $A^{-1}$ 为矩阵 $A$ 的逆，$A^*$ 表示矩阵 $A$ 的伴随矩阵，$|A|$ 表示矩阵 $A$ 的行列式。

现在要求的是 $A^*$ ，所以有 $A^*=A^{-1}|A|$，而 $|A|$ 模 $2$ 余 $1$，因此 $A^*\equiv A^{-1}(\bmod 2)$。

现在问题变成了求 $A^{-1}$。

## 矩阵求逆

吐了，写不动了。

详见 [P4783 题解](https://www.luogu.com.cn/blog/_post/306195)，会一点线代的应该都能看懂，看不懂的也能感性理解，就不搬证明了。

具体做法就是先把 $A$ 和 $I_n$ 置于同一矩阵中，然后通过消元把左半边 $A$ 变成 $I_n$，那么右半边就会自动变成 $A^{-1}$，时间复杂度为 $\Theta(n^3)$。无法通过 $n\le2000$ 的限制，但是已经无法在复杂度上变得更优了，因此考虑一些常数（？）优化。

由于所有操作都在模 $2$ 意义下进行，因此只会涉及到两行的加（不会乘参数），又因为异或可以看作模 $2$ 意义下的加法，因此可以用 bitset 存储每个矩阵进行消元。

时间复杂度：$\Theta(\frac {n^3} \omega)$

参考代码：

```c++
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define int long long
#define elif else if
#define ALL(x) x.begin(),x.end()
#define lowbit(x) (x&(-x))
using namespace std;
void fileio(const string &s)
{
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}
const int INF=4e18;
inline int read()
{
	int x=0;
	bool flag=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
int n,m;
bitset<4000> f[2000];
array<int,2> a[500000];
signed main()
{
	n=read();
	m=read();
	for(int i=0;i<m;i++)
	{
		int x=read()-1,y=read()-1;
		a[i]={x,y};
		f[x][y]=1;
	}
	for(int i=0;i<n;i++)
		f[i][n+i]=1;
	for(int i=0;i<n;i++)
	{
		int now=0;
		for(int l=i;l<n;l++)
			if(f[l][i])
				now=l;
		if(i!=now)
			swap(f[i],f[now]);
		for(int l=0;l<n;l++)
			if(i!=l&&f[l][i])
				f[l]^=f[i];
	}
	for(int i=0;i<m;i++)
		if(f[a[i][1]][a[i][0]+n])
			puts("NO");
		else
			puts("YES");
	return 0;
}
```
## 参考资料

- [积和式 - 维基百科，自由的百科全书](https://zh.wikipedia.org/zh-hans/%E7%A7%AF%E5%92%8C%E5%BC%8F)
- [行列式 - 维基百科，自由的百科全书](https://zh.wikipedia.org/zh/%E8%A1%8C%E5%88%97%E5%BC%8F)
- [子式和余子式 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E5%AD%90%E5%BC%8F%E5%92%8C%E4%BD%99%E5%AD%90%E5%BC%8F)

- [题解 P4783 【模板】矩阵求逆](https://www.luogu.com.cn/blog/_post/306195)



---

## 作者：Jayun (赞：1)

## 题目大意

给定一个二分图，已知这个二分图的完备匹配个数是奇数，询问删除每条边后完备匹配个数的奇偶。

$n\leq2000,m\leq5\times10^5$。

## 题解

线性代数苦手者。

令二分图的邻接矩阵为 $A$，二分图的完备匹配个数可以列式 $\sum_p\prod_{i=1}^nA_{i,p_i}$。由于题目只考虑奇偶，所以可以看作是在模 2 的背景下，此时邻接矩阵的行列式 $|A|=\sum_p(-1)^k\prod_{i=1}^nA_{i,p_i}=\sum_p\prod_{i=1}^nA_{i,p_i}$。我们便知道了 $|A|$ 就是二分图的完备匹配个数，为奇数。

考虑删除每条边的情况，只需要知道钦定该边存在的排列数奇偶性即可。它正好与余子式的意义相同——删去该行该列后矩阵的行列式。对于求解余子式有伴随矩阵的定义式

$$A^*_{i,j}=(-1)^{i+j}M_{j,i}$$

在模 2 意义下等价于

$$A^*_{i,j}=M_{j,i}$$

而求伴随矩阵又有性质

$$A^*=|A|A^{-1}$$

已知 $|A|$ 为奇数且在模 2 意义下所以等价于

$$A^*=A^{-1}$$

用 bitset 优化矩阵求逆即可，时间复杂度 $\mathcal{O}\left(\frac{n^3}{\omega}\right)$。

## 代码

```cpp
const int N = 2010, M = 5e5 + 5;

inline ll Read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

namespace Main {
	int n, m;
	int u[M], v[M];
   	bitset<N << 1> a[N];
	int main () {
		n = Read(), m = Read();
		for (int i = 1; i <= m; i++) {
			u[i] = Read(), v[i] = Read();
			a[u[i]][v[i]] = 1;
		}
		for (int i = 1; i <= n; i++) a[i][i + n] = 1;
		for (int i = 1; i <= n; i++) {
			int mxi = i;
			for (int j = i + 1; j <= n; j++)
				if (a[j][i]) mxi = j;
			swap(a[i], a[mxi]);
			for (int j = 1; j <= n; j++)
				if (a[j][i] && j != i) a[j] ^= a[i];
		}
		for (int i = 1; i <= m; i++) puts(a[v[i]][n + u[i]]? "NO": "YES");
		return 0;
	}
}

int main () {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	Main::main();
	return 0;
}
```

---

