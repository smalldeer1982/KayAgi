# [AGC057E] RowCol/ColRow Sort

## 题目描述

给定一个 $H\times W$ 的矩阵 $A = (A_{i,j})$（$1\leq i\leq H,\ 1\leq j\leq W$），定义如下两种操作：

- **行排序**：对每一行进行升序排序。即对于所有 $i$，将 $A_{i,1},\ldots,A_{i,W}$ 升序排列。
- **列排序**：对每一列进行升序排序。即对于所有 $j$，将 $A_{1,j},\ldots,A_{H,j}$ 升序排列。

给定一个 $H\times W$ 的矩阵 $B = (B_{i,j})$，请计算满足以下两个条件的 $H\times W$ 矩阵 $A$ 的总数，并对 $998244353$ 取模：

- 对 $A$ 先进行行排序再进行列排序，结果等于 $B$。
- 对 $A$ 先进行列排序再进行行排序，结果等于 $B$。

## 说明/提示

### 限制条件

- $1\leq H,\ W\leq 1500$
- $0\leq B_{i,j}\leq 9$
- 对任意 $1\leq i\leq H$ 及 $1\leq j\leq W-1$，有 $B_{i,j}\leq B_{i,j+1}$
- 对任意 $1\leq j\leq W$ 及 $1\leq i\leq H-1$，有 $B_{i,j}\leq B_{i+1,j}$
- 输入的所有值均为整数

### 样例解释 1

满足条件的矩阵有如下 $4$ 个：$\begin{pmatrix}0&0\\1&2\end{pmatrix}$，$\begin{pmatrix}0&0\\2&1\end{pmatrix}$，$\begin{pmatrix}1&2\\0&0\end{pmatrix}$，$\begin{pmatrix}2&1\\0&0\end{pmatrix}$。例如，$\begin{pmatrix}2&1\\0&0\end{pmatrix}$ 满足条件的验证如下：
- 先行排序再列排序：$\begin{pmatrix}2&1\\0&0\end{pmatrix}\to\begin{pmatrix}1&2\\0&0\end{pmatrix}\to\begin{pmatrix}0&0\\1&2\end{pmatrix}$。
- 先列排序再行排序：$\begin{pmatrix}2&1\\0&0\end{pmatrix}\to\begin{pmatrix}0&0\\2&1\end{pmatrix}\to\begin{pmatrix}0&0\\1&2\end{pmatrix}$。

### 样例解释 2

例如 $\begin{pmatrix}5&7&6\\3&0&1\\4&8&2\end{pmatrix}$ 满足条件，验证如下：
- 先行排序再列排序：$\begin{pmatrix}5&7&6\\3&0&1\\4&8&2\end{pmatrix}\to\begin{pmatrix}5&6&7\\0&1&3\\2&4&8\end{pmatrix}\to\begin{pmatrix}0&1&3\\2&4&7\\5&6&8\end{pmatrix}$。
- 先列排序再行排序：$\begin{pmatrix}5&7&6\\3&0&1\\4&8&2\end{pmatrix}\to\begin{pmatrix}3&0&1\\4&7&2\\5&8&6\end{pmatrix}\to\begin{pmatrix}0&1&3\\2&4&7\\5&6&8\end{pmatrix}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 2
0 0
1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3
0 1 3
2 4 7
5 6 8```

### 输出

```
576```

## 样例 #3

### 输入

```
3 5
0 0 0 1 1
0 0 1 1 2
0 1 1 2 2```

### 输出

```
10440```

## 样例 #4

### 输入

```
1 7
2 3 3 6 8 8 9```

### 输出

```
1260```

# 题解

## 作者：Linshey (赞：8)

首先考虑只有 `01` 怎么做，实际上就行和列分别进行一个可重排列即可。对应的方案是唯一的（由于**杨图的性质**），比如说：

```
   3  2  1  1
2  x  x  x  x
1  x  x
4  x
```

以行为例，选择最大的行，此时一定有恰好它这么多列非零：

```
    1  2  3  1
 2  
 1 
 4  x  x  x  x
```

然后再选择最大的行：

```
    0  1  2  0
 2     x  x  
 1 
 4  x  x  x  x
```

我们考虑依次在 $0$ 里面选出一些 $1$，$1$ 里面选出一些 $2$，……方案数相乘即可。

比如 $1$ 长这样，我们要从中选出一些 $2$：

```
  1  1  1  1
  1  1
  1
```

假如每列有 $a_i$ 个 $2$，每行有 $b_i$ 个 $2$，那么我们就是要找到 $a,b$ 的一个置换，使得：根据杨图的构造方式，不会有 $0$ 被改成 $2$。比如上述情况的第四列，若 $a_4=1$，结果 $b_3=3$，那么 $(3,4)$ 就会被弄成 $2$，这是不可接受的。

设 $p_j$ 为 第 $j$ 多的列，那么最后它等于 $0$ 的行的 $b_i<j$。我们从右向左填 $a$，设 $f_{i,j}$ 表示从右向左到了第 $i$ 列，最小值为 $j$ 的方案数，计算 $b$ 的填法的方案数就是“排列 $p_i$ 的数量使得 $p_i<Hold_i$ 这样的问题”，$\prod(a_i-i+1)$ 即可。而这个 $\prod$ 可以很轻松地分阶段，就可以 dp 了。

---

## 作者：EuphoricStar (赞：5)

搞了一上午的人生中第一道金牌题。

首先考虑一个经典的套路：转 $01$。具体而言，我们考虑若值域是 $[0, 1]$ 怎么做。

发现可以很容易地判定一个 $A$ 是否合法。设矩阵第 $i$ 行的和为 $r_i$，第 $j$ 列的和为 $c_j$，那么合法当且仅当 $A$ 的 $\{r_i\}$ 和 $\{c_j\}$（可重集）分别与 $B$ 的 $\{r_i\}$ 和 $\{c_j\}$ 相同。并且 $r_i, c_j$ 的每一种不同的排列方案都恰好对应一个可以被操作成 $B$ 的 $A$。

那么值域为 $[0, 1]$ 时答案就是 $\{r_i\}$ 和 $\{c_j\}$ 的可重集排列数相乘。

考虑值域为 $[0, 9]$ 的情况，考虑枚举 $k \in [0, 8]$，把 $\le k$ 的值赋成 $0$，$> k$ 赋成 $1$。那么 $A$ 合法等价于，对于每个 $k \in [0, 8]$，都存在两个排列 $p_k(i), q_k(j)$，使得 $A_{i, j} \le k \Longleftrightarrow B_{p_k(i), q_k(j)} \le k$。那么一堆排列 $(p_0, q_0, p_1, q_1, \ldots, p_8, q_8)$ 可以唯一确定一个 $A$，但是因为 $\{r_i\}, \{c_j\}$ 是可重集，所以一个 $A$ 实际上会对应 $\prod\limits_{k = 0}^m (\sum\limits_{i = 1}^n [r_i = k])! \times \prod\limits_{k = 0}^n (\sum\limits_{i = 1}^m [c_i = k])!$ 堆排列。最后除一下即可。

于是考虑对这堆排列 $(p_0, q_0, p_1, q_1, \ldots, p_8, q_8)$ 计数。条件 $A_{i, j} \le k \Longleftrightarrow B_{p_k(i), q_k(j)} \le k$ 里面有 $A$，不妨把 $A$ 扔掉，根据 $A_{i, j} \le k \Longrightarrow A_{i, j} \le k + 1$ 有 $B_{p_k(i), q_k(j)} \le k \Longrightarrow B_{p_{k + 1}(i), q_{k + 1}(j)} \le k + 1$。

发现我们实际上只关心 $p_{k + 1} \circ p_k^{-1}$ 和 $q_{k + 1} \circ q_k^{-1}$。于是条件可以被改写成 $B_{i, j} \le k \Longrightarrow B_{p_k(i), q_k(j)} \le k + 1$。

考察 $[B_{i, j} \le k]$ 的杨表结构。设 $a_i = \sum\limits_{j = 1}^m [B_{i, j} \le k], b_j = \sum\limits_{i = 1}^n [B_{i, j} \le k + 1]$，可以发现 $a, b$ 单调不升。若把 $B$ 旋转 $180 \degree$，那么条件可以转化为 $j \le a_i \Longrightarrow p_k(i) \le b_{q_k(j)}$。更进一步地，因为 $b$ 单调不升，所以 $p_k(i) \le b_{\max\limits_{j = 1}^{a_i} q_k(j)}$。

然后可以 dp 计数了。设 $f_{i, j}$ 为 $\max\limits_{o = 1}^i q_k(o) = j$ 的方案数。我们 $p_k, q_k$ 的方案数分别统计。$f_{i - 1} \to f_i$ 时，计算 $q_k(i)$ 的方案数，有 $f_{i, j} \gets (j - i + 1) f_{i - 1, j} + \sum\limits_{k = 1}^{j - 1} f_{i - 1, k}$，分别表示 $q_k(i)$ 是或不是最大值。然后我们再维护一个指针 $t$ 从后往前扫，当 $a_t = i$ 时，计算 $p_k(t)$ 的方案，相当于 $p_k(t)$ 有一个 $b_j$ 的上界，于是有 $f_{i, j} \gets f_{i, j} \times (b_j - t + 1)$，因为 $p_k(t)$ 的上界随 $t$ 减小而减小。

每次的 $f_{m, m}$ 相乘，然后再除一下上面的 $\prod\limits_{k = 0}^m (\sum\limits_{i = 1}^n [r_i = k])! \times \prod\limits_{k = 0}^n (\sum\limits_{i = 1}^m [c_i = k])!$ 就是最终答案。

时间复杂度 $O(Vnm)$。

[code](https://atcoder.jp/contests/agc057/submissions/46270560)

---

## 作者：FZzzz (赞：4)

考虑对于一个 $k$，把不大于 $k$ 的格子标成黑色，其余的标成白色。那么行列排序就是把每一行的黑色格子数从大到小排序，列行排序就是每一列。$A$ 的条件就是对于每个 $k$，这两个东西排序以后都与 $B$ 相同。换句话说，要存在一个长度为 $n$ 的排列 $p$ 和一个长度为 $m$ 的排列 $q$，使得 $A_{i,j}\le k\Leftrightarrow B_{p_i,q_j}\le k$。

如果我们已经知道了对于 $k-1$ 的这俩排列 $p'$ 和 $q'$，相当于我知道了 $A$ 中哪些位置是不大于 $k-1$ 的，然后我再确定对于 $k$ 的排列 $p$ 和 $q$，我就知道了哪些位置是 $k$。

发现对于任何 $(p',q')$，$(p,q)$ 的数量都是相等的。并且，一个 $A$ 对应了 $\left(\prod\limits_{i=0}^mc_i!\right)\left(\prod\limits_{i=0}^nd_i!\right)$ 个 $(p,q)$，其中 $c_i$ 为有 $i$ 个格子小于等于 $k$ 的数量，$d_i$ 同理。所以我们只需要对每个 $k$ 求在 $p'_i=i$，$q'_i=i$ 时的 $(p,q)$ 数量，然后乘起来即可。

$(p,q)$ 的限制是 $B_{i,j}\le k-1\Rightarrow B_{p_i,q_j}\le k$。只需要知道 $B$ 中每行或每列的黑格子数量就可以确定 $B$。为了用简单的不等式表述限制，考虑分别用每行和每列的黑格子数描述 $B$ 中不大于 $k-1$ 和 $k$ 的格子。

设 $B$ 的第 $i$ 行有 $a_i$ 个小于等于 $k-1$ 的，第 $i$ 列有 $b_i$ 个小于等于 $k$ 的，$a_0=m$，$b_0=n$。我们的限制是：若 $j\le a_i\Rightarrow p_i\le b_{q_j}$。根据 $a$ 和 $b$ 的单调性，改写为
$$p_i\le b_{\max\limits_{j=1}^{a_i}q_j}$$
若 $a_i=0$ 则下面那个 max 是 $0$。

现在如果我们确定了 $x_i=\max\limits_{j=1}^{a_i}q_j$，那么限制改为 $p_i\le b_{x_i}$，这样 $p$ 和 $q$ 就独立了。考虑这样一组 $x$ 对应多少 $(p,q)$。首先 $p$ 是很简单的给每个位置一个限制，而且限制是递增的，那么 $i$ 这个位置的贡献就是 $b_{x_i}-i+1$。

对 $q$ 的贡献分两种情况。若 $x_i=x_{i-1}$（认为 $x_0=m$），说明 $q_{a_i+1}$ 到 $q_{a_{i-1}}$ 全都小于 $x_i$，贡献是
$$\prod_{j=a_i+1}^{a_{i-1}}x_i-1-(j-2)$$
可以写成阶乘的形式。后面 $-2$ 是因为下面肯定有一个确定为 $x_i$ 的，其他位置都是小于 $x_i$。若 $x_i\ne x_{i-1}$，则说明中间有一个 $x_{i-1}$，其他都小于 $x_{i-1}$。贡献是
$$\prod_{j=a_i+1}^{a_{i-1}}\left(\prod_{k=a_i+1}^{j-1}x_i-1-(j-1)\right)\left(\prod_{j+1}^{a_{i-1}}x_i-1-(j-2)\right)$$
然后发现后面两个 prod 的积跟 $j$ 根本没关系，所以是这玩意的 $a_{i-1}-a_i$ 倍。

所以总的贡献是一堆东西的积，只跟 $x$ 的每一项和每相邻两项有关。那就可以 dp 了，前缀和优化做到 $O(n^2)$。如果值域记为 $k$，$n$ 和 $m$ 同阶，总时间复杂度为 $O(n^2k)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=1.5e3+5;
int n,m,c[maxn][maxn],a[10][maxn],b[10][maxn];
const ll mod=998244353;
ll ksm(ll a,ll b){
	ll ans=1;
	while(b){
		if(b%2==1) ans=ans*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return ans;
}
ll fac[maxn],ifac[maxn],f[maxn];
ll solve(int* a,int* b){
	a[0]=m;
	b[0]=n;
	memset(f,0,sizeof(f));
	f[m]=1;
	for(int i=1;i<=n;i++){
		ll s=0;
		for(int j=m;j>=0;j--){
			ll res=f[j];
			f[j]=j>=a[i-1]?f[j]*fac[j-a[i]]%mod*ifac[j-a[i-1]]%mod:0;
			f[j]=b[j]>=i?(f[j]+s)%mod*(b[j]-i+1)%mod:0;
			if(a[i-1]>a[i]&&j>=a[i-1])
				s=(s+res*fac[j-a[i]-1]%mod*ifac[j-a[i-1]]%mod*(a[i-1]-a[i])%mod)%mod;
		}
	}
	ll ans=a[n]?0:f[0];
	if(a[n]) for(int i=a[n];i<=m;i++)
		ans=(ans+f[i]*fac[i-1]%mod*ifac[i-a[n]]%mod*a[n]%mod)%mod;
	return ans;
}
int cnt[maxn];
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	m=read();
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) c[i][j]=read();
	for(int i=0;i<=9;i++)
		for(int j=1;j<=n;j++) for(int k=1;k<=m;k++) if(c[j][k]<=i){
			a[i][j]++;
			b[i][k]++;
		}
	int len=max(n,m);
	fac[0]=1;
	for(int i=1;i<=len;i++) fac[i]=fac[i-1]*i%mod;
	ifac[len]=ksm(fac[len],mod-2);
	for(int i=len-1;i>=0;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
	ll ans=fac[n]*fac[m]%mod;
	for(int i=0;i<9;i++) ans=ans*solve(a[i],b[i+1])%mod;
	for(int i=0;i<=9;i++){
		memset(cnt,0,sizeof(cnt));
		for(int j=1;j<=n;j++) cnt[a[i][j]]++;
		for(int j=0;j<=m;j++) ans=ans*ifac[cnt[j]]%mod;
		memset(cnt,0,sizeof(cnt));
		for(int j=1;j<=m;j++) cnt[b[i][j]]++;
		for(int j=0;j<=n;j++) ans=ans*ifac[cnt[j]]%mod;
	}
	printf("%lld\n",ans);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：_edge_ (赞：2)

模拟赛出了这题，怎么回事捏。

先思考只有 $0,1$ 的情况怎么做。

手玩一下大概操作就是把所有行的 0 个数求出来，然后按照这个个数对所有行进行排序，另一个操作也一样。

具体的，比方说，我们求出第 $i$ 行的 0 个数为 $r_i$，那么对于一次对第 $i$ 行进行排序相当于是把 0 都提到前 $r_i$ 个，然后对列的排序，相当于是在把 0 都向上拿，也就相当于对 $r$ 进行排序。

我们令 $r_i$ 表示第 $i$ 行的 0 的个数，$c_i$ 表示第 $i$ 列的 0 的个数，可以明确的是只要这个表格内的 $r$ 和 $c$ 与 目标表格的 $r$ 和 $c$ 排序之后分别相同，那么就是 ok 的。

上面的条件是充分并且必要的，原因是，如果满足他们的 A 一定都能够排成 B，如果有一行不满足就不合法了，一列也是一样的。

那么对于 $0,1$ 的情况，我们求出目标表格 r 序列和 c 序列，尝试随意重排他们就可以了，但是对于 r 和 c 的一种重排为啥就一定对应一种方案捏（[这个证明](https://www.luogu.com.cn/article/8r5dvz3m)很抽象，我没怎么看懂）。

这个问题如果忽略题目中的条件是不可做的，并且大部分情况都不是唯一的，比方说是下面这种情况。

```
* 1 1 
1 0 1
1 1 0

* 1 1 
1 1 0
1 0 1
```

`*` 是没有意义的，就是上面一行表示每一列的 0 的个数，左边一列表示每一行 0 的个数。

简单的证明就是，存在是必然的，因为你可以交换 B 矩阵的行或者列，唯一也是必然的，因为你可以把它交换为 B，B 唯一的话交换回去得到的也是唯一的！

因此，我们的答案就是，每一行 0 的个数求出来重排一下，每一列 0 的个数求出来重排一下！注意到 0 的个数有可能相同，所以要稍微处理一下。

那么考虑值域为 $[0,9]$ 的情况，我们认为，对于 $\le k$ 的点我们标记为 0，对于 $> k$ 的点我们标记为 1，只要对于所有的 $k$ 都满足就可以了。

我们尝试换一种描述方式，如果说能够重排的话就是存在两个排列 $p,q$，满足 $A_{i,j}=B_{p_i,q_j}$。

唯一可能出问题的地方在于，我们如果钦定某个点 $\le k$，那么在之后的 $k+1,k+2, \cdots , 9$ 就也得满足小于等于他们，如果随意排列的话就可能会出问题。

我们把条件写出来，大概是 $B_{p^k_i,q^k_j} \le k$ 能够得到 $B_{p^{k+1}_i,q^{k+1}_j} \le k+1$，我们可以做这样的操作，$p^k \times inv(p^{k-1})$， 也就是相当于乘个逆排列，最终的目的是让每一个 $k$ 变得互相独立，即 $B_{i,j} \le k$ 得到 $B_{p^k_i,q^k_j} \le k+1$。

这样就很不错，我们可以枚举每一个 $k$ 来计数。

模拟赛里有一档分是 $n \le 8$，就可以直接暴力枚举 $p$ 排列来处理掉，处理 $q$ 排列是非常简单的。

考虑先枚举一个排列 $p$，然后我们可以得到 $q$ 每个位置的范围。

我们令 $A1_j$ 表示第 $j$ 列，最大的满足 $B_{A1_j,j} \le k-1$。令 $A2_i$ 表示第 $i$ 行，最大的满足 $B_{i,A2_i} \le k$。容易观察到 A1 和 A2 都是单调不升的。

令，$f_{i,j}$ 表示前 i 项，最大值为 j 的贡献总和，分别计算 p 和 q 的贡献就 ok 了，相信这一步 dp 不是特别困难。

---

## 作者：Fire_Raku (赞：0)

[[AGC057E] RowCol/ColRow Sort](https://www.luogu.com.cn/problem/AT_agc057_e)

问题的操作是对序列排序，关注的是数之间的大小关系，这时候我们可以考虑将题目的范围缩小，思考值域在 $[0,1]$ 怎么做？

手玩后发现，在这样的条件下，第一种操作即按照每行 $0$ 的数量将行从上到下降序排序，列同理，为按照每列 $0$ 的数量将行从上到下降序排序。

思考如何刻画 $A$ 矩阵满足两种操作的条件。以行为例，设 $r_i$ 表示第 $i$ 行 $0$ 的数量，那么 $A$ 矩阵所有行的 $r$ 构成可重集合与 $B$ 矩阵的 $r$ 构成的可重集合相等是必要的，同时根据 $B$ 矩阵的性质，可以得出这也是充分的。

那么刻画就是行列的可重集合与 $B$ 相同。根据 $B$ 矩阵的特殊性质，满足条件的 $A$ 矩阵一定对应两个可重集合排列后唯一一种方案（每个排列并不对应唯一一种矩阵），那么 $[0,1]$ 的答案就是两个可重排列数相乘。

回到原问题，只需要将前面的方法拓展，枚举 $k\in[0,9)$，令 $A_{i,j}\leftarrow[A_{i,j}\le k]$，$B_{i,j}\leftarrow[A_{i,j}\le k]$，那么一个合法的 $A$ 矩阵一定在所有 $k$ 上都满足上面的条件。但是方案显然不是简单的排列数相乘了，那么问题就聚焦在排列满足的条件上。                            

注意到操作的特殊性，枚举每个 $k$，我们其实可以这样刻画一个矩阵 $A$：存在两个排列 $p^{k}(1\cdots n)$ 和 $q^{k}(1\cdots m)$，使得 $A_{i,j}=B_{p^k_i,q^k_j}$。一个合法的 $A$ 对应唯一一个集合 $\{{(p^0,q^0)\cdots (p^k, q^k)\}}$。但是对于每一个 $k+1$ 时，$p^{k}$ 对 $p^{k+1}$ 有制约，具体的说，$B_{p^k_i,q^k_j}\le k\Rightarrow B_{p^{k+1}_i,q^{k+1}_j}\le k+1$。这里有四个排列非常难受，但实际上我们只关心两对排列的相对关系，并且不关心其他排列，所以考虑逆置换，设 $p^{k}_i=i$，那么条件就变成：$B_{i,j}\le k\Rightarrow B_{p^{k}_i,q^{k}_j}\le k+1$ (这里可以当作是枚举 $k$ 或 $k+1$ 时满足的条件，看你怎么理解)。这样转化后单次计算 $k$ 情况下的方案数就独立了。

继续改写条件。设 $r_i=\sum_{j=1}^m[B_{i,j}\le k]$，$c_{j}=\sum_{i=1}^n[A_{i,j}\le k+1]$，那么就有 $j\le r_i\Rightarrow p^k_i\le c_{q^k_{j}}$，即为 $p^k_i\le \min_{j\le r_i}c_{q^k_{j}}$，再根据 $c$ 的单调性，即 $p^k_i\le c_{\max_{j\le r_i} q^k_{j}}$。

至此我们将原问题变为：给定两个单调不升的序列 $r$ 和 $c$，求满足上述的排列 $p$ 和 $q$ 的方案数。考虑用 dp 求解。设 $f_{i,j}$ 表示 $\max(q_1\cdots q_{i})=j$ 的方案数。可以发现 $p$ 和 $q$ 并不是相互制约，所以在求解过程中可以只考虑一个排列的方案数。先考虑 $q$，转移只需要枚举当前位 $q_i$ 是否为最大值。

怎么考虑 $p$，可以在 dp 过程中用一个指针 $t$ 从右往左扫描 $r_i$，如果 $r_t=i$，那么考虑 $p_t$ 这一位的填法即可。 

每一次 $k$ 算出来的方案数都要除以 $\prod_{k=1}^m(\sum_{i=1}^n[r_{i}=k])!\cdot\prod_{k=1}^m(\sum_{i=1}^n[r_{i}=k])!$，这是可重排列重复算的部分。

时间复杂度 $O(km^2)$。

```cpp
#include <bits/stdc++.h>
#define pii std::pair<int, int>
#define fi first
#define se second
#define pb push_back
#define mk std::make_pair

using u32 = unsigned int;
using u64 = unsigned long long;
using i64 = long long;
const i64 iinf = 0x3f3f3f3f, linf = 0x3f3f3f3f3f3f3f;
const int N = 1.5e3 + 10, mod = 998244353;
int n, m;
int B[N][N];
i64 inv[N], fac[N], r[15][N], c[15][N], cnt[N];
i64 f[N][N], ans = 1;
i64 qpow(i64 a, i64 b) {
	i64 ret = 1;
	while(b) {
		if(b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	} 
	return ret;
}
int main () {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	
	std::cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			std::cin >> B[i][j];
			r[B[i][j]][i]++;
			c[B[i][j]][j]++;
		}
	}
	int M = std::max(n, m);
	fac[0] = 1;
	for(i64 i = 1; i <= M; i++) fac[i] = fac[i - 1] * i % mod;
	inv[M] = qpow(fac[M], mod - 2);
	for(i64 i = M - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
	 
	for(int k = 0; k < 9; k++) {
		for(int j = 1; j <= n; j++) r[k + 1][j] += r[k][j];
		for(int j = 1; j <= m; j++) c[k + 1][j] += c[k][j];
		int t = n;
		for(; t && !r[k][t]; t--);
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for(i64 i = 1; i <= m; i++) {
			i64 s = f[i - 1][0];
			for(i64 j = 1; j <= m; j++) {
				f[i][j] = ((j - i + 1) * f[i - 1][j] + s) % mod;
				s = (s + f[i - 1][j]) % mod;
			}
			for(; t && r[k][t] == i; t--) {
				for(int j = 1; j <= m; j++) f[i][j] = f[i][j] * std::max(0LL, c[k + 1][j] - t + 1) % mod;
			} 
		}
		ans = ans * f[m][m] % mod;
		memset(cnt, 0, sizeof(cnt));
		for(int i = 1; i <= n; i++) cnt[r[k][i]]++;
		for(int i = 1; i <= m; i++) ans = ans * inv[cnt[i]] % mod;
		memset(cnt, 0, sizeof(cnt));
		for(int i = 1; i <= m; i++) cnt[c[k][i]]++;
		for(int i = 0; i <= n; i++) ans = ans * inv[cnt[i]] % mod;
	}
	
	std::cout << ans << "\n";
	
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc057_e)

**题目大意**

> 给定一个 $n\times m$ 矩阵 $B$，求有多少个矩阵 $A$ 同时满足：
>
> - 依次对 $A$ 每一行、每一列排序最终得到 $B$。
> - 依次对 $A$ 每一列、每一行排序最终得到 $B$。
>
> 数据范围：$n,m\le 1500,B_{i,j}\le 9$。

**思路分析**

考虑 $B_{i,j}\in\{0,1\}$ 如何做。

那么对 $A$ 每行每列排序，相当于把 $A$ 的每一列按 $0$ 的个数升序排列，每列每行同理。

因此 $A$ 合法当且仅当 $A$ 每行每列 $0$ 的个数构成的可重集和 $B$ 相同。

进一步一定存在排列 $p_n,q_m$ 使得 $B_{p_i,q_i}=A_{i,j}$（把 $B$ 的每行每列根据 $0$ 的个数一一对应到 $A$ 的行列上）。

回到原问题，可以证明 $B$ 合法当且仅当对于每个 $k$，把 $\le k$ 的看成 $0$，剩余看成 $1$ 后合法。

设我们每次取出的排列为 $p^k_n,q^k_m$，那么我们要求 $B(p^k_i,q^k_j)\le k\implies B(p^{k+1}_i,q_{j}^{k+1})\le k+1$。

然后对所有 $p,q$ 计数，但是对于每个 $k$，行和相同的列是本质相同的，要除以对应的排列数。

我们计数 $p^k$ 可以转成计数 $p^k\times \mathrm{inv}(p^{k-1})$，因此要求变成 $B(i,j)\le k\implies B(p^k_i,q^k_j)\le k+1$，这样每层的方案都是独立的。

由于 $B$ 一定是杨表，因此设 $r^k_{i},c^k_j$ 表示此时第 $i$ 行、第 $j$ 列的 $0$ 的个数，那么 $B(i,j)\le k\iff j\le r^k_i\iff i\le r^k_j$。

那么对于 $j\in[1,r_i^k]$ 都有 $p_i^{k}\le c(q_j^k)$，由于 $c$ 单调递减，因此等价于 $p_{i}^k\le c(\max_{j=1}^{r_i^k}q_j^k)$。

因此可以 dp，设 $f_{i,j}$ 表示 $\max q^k_1\sim q^k_i=j$ 的方案数，转移时考虑 $q_i$ 是否是最大值，并且把 $r_x^k=i$ 的 $p_x^k$ 确定取值，由于每个 $p$ 的取值范围单调减小，因此当前 $p_x^k$ 方案数就是 $\max(0,j-x+1)$，

时间复杂度 $\mathcal O(nmB)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1505,MOD=998244353;
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
int n,m,r[10][MAXN],c[10][MAXN],a[MAXN][MAXN],cnt[MAXN];
ll f[MAXN][MAXN],fac[MAXN],ifac[MAXN];
signed main() {
	for(int i=fac[0]=ifac[0]=1;i<MAXN;++i) ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) {
		scanf("%d",&a[i][j]);
		for(int k=a[i][j];k<10;++k) ++r[k][i],++c[k][j];
	}
	ll ans=1;
	for(int k=0;k<9;++k) {
		memset(f,0,sizeof(f)),f[0][0]=1;
		int p=n;
		for(;p&&!r[k][p];--p);
		for(int i=1;i<=m;++i) {
			ll s=f[i-1][0];
			for(int j=1;j<=m;++j) {
				f[i][j]=(f[i-1][j]*(j-i+1)+s)%MOD;
				s=(s+f[i-1][j])%MOD;
			}
			for(;p&&r[k][p]==i;--p) {
				for(int j=1;j<=m;++j) f[i][j]=f[i][j]*max(0,c[k+1][j]-p+1)%MOD;
			}
		}
		ans=ans*f[m][m]%MOD;
		for(int i=1;i<=n;++i) if(r[k][i]) ++cnt[r[k][i]];
		for(int i=1;i<=m;++i) ans=ans*ifac[cnt[i]]%MOD,cnt[i]=0;
		for(int i=1;i<=m;++i) ++cnt[c[k][i]];
		for(int i=0;i<=n;++i) ans=ans*ifac[cnt[i]]%MOD,cnt[i]=0;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：JWRuixi (赞：0)

## [AGC057E] RowCol/ColRow Sort

### 题意

给定 $n \times m$ 的矩阵 $A$（$0 \le A_{i, j} \le 9$），求有多少个不同的 $B$ 满足：

- 对每一行中的元素排序，再对每一列中的元素排序后 $A = B'$；
- 对每一列中的元素排序，再对每一行中的元素排序后 $A = B'$；

$n, m \le 1500$。

### 分析

先分析合法的 $B$ 的特征。

不妨将值域弱化到 $[0, 1]$，那么对于这个 01 矩阵，对一行排序相当于将 $0$ 全部前置，那么此时列排序的效果相当于是将行按 $0$ 的数量排序；换而言之，记 $a_i = \sum\limits_{j \le m} [A_{i, j} = 0], b_i = \sum\limits_{j \le m} [B_{i, j} = 0]$，要求 $a$ 的可重集和 $b$ 的可重集相同，列同理。那么对于值域广泛的情况，我们相当于对于 $k = 0 \dots, V - 1$，按 $\le k$ 和 $> k$ 染色，都要通过 01 测试。

我们尝试改写一下这个判定条件，相当于序列 $a, b$，存在一个置换 $\{p_n\}$ 使得 $a_i = b_{p_i}$。我们发在前面叙述的排序方式中，我们将行排序之后的列排序视为直接对 $n$ 个行这 $n$ 个整体排序，所以行列是独立的。那么假设列对应的映射是 $\{q_m\}$，则条件等价于 $A_{i, j} = 0 \iff B_{p_i, q_j} = 0$。推广到值域广泛的情况就是对于 $(p^0, q^0), \dots, (p^{V - 1}, q^{V - 1})$，要求 $\forall k, A_{i, j} \le k \iff B_{p^k_i, q^k_j} \le k$。

这个条件直接包含了最开始前面可重集相同的要求，即 $(p^0, q^0), \dots, (p^{V - 1}, q^{V - 1})$ 可以唯一对应一个合法的 $B$（方案数应除掉可重集造成的重复）。但是这样难以利用到一些我们已知的条件，比如：$B$ 在对 $k$ 染色后行列 $0$ 个数的可重集。我们在已知这些信息的情况下可以对条件进行弱化。

考虑为什么不能直接认为这 $V$ 个排列独立？这是由于 $A_{i, j} \le k$ 隐含了 $A_{i, j} \le k + 1$。所以我们只需要让排列间满足：若 $B_{p^k_i, q^k_j} \le k$，则 $B_{p^{k + 1}_i, q^{k + 1}_j} \le k + 1$ 即可。

我们发现我们只需要考虑 ${p^k}^{-1} \circ p^{k + 1}$，所以条件再次改写为：若 $B^k_{i, j} \le k$，则 $B^{k + 1}_{p^{k + 1}_i, q^{k + 1}_j} \le k + 1$。

注意到 $B_{i, j}$ 在对 $k$ 染色的意义下是有序的，考虑记 $R_i = \sum\limits_{j \le m} [A_{i, j} \le k], C_j = \sum\limits_{i \le n} [A_{i, j} \le k + 1]$。则 $B^k_{i, j} \le k$ 即 $j \le R_i$，所以 $B^{k + 1}_{p^{k + 1}_i, q^{k + 1}_j} \le k + 1$ 即 $p^{k + 1}_i \le C_{q^{k + 1}_j}$。于是 $p^{k + 1}_i \le \min\limits_{j \le R_i} C_{q^{k + 1}_j}$。注意到 $C$ 单调不增，于是有 $p^{k + 1}_i \le C_{\max\limits_{j \le R_i}q^{k + 1}_j}$。

在此基础上 DP，记 $f_{i, j}$ 为 $\max\limits_{k \le i} q_k = j$ 的方案数。转移分层与层，和层内部：

- 若 $q_i$ 是最大值：$\forall t < j, f_{i - 1, t} \to f_{i, j}$；若 $q_i$ 不是最大值：$f_{i - 1, j} \times (j - (i - 1)) \to f_{i, j}$；
- 枚举所有的 $R_t = i$，考虑随 $t$ 的减小，$p_t$ 的上限不增，于是方案数就是 $b_j - t + 1$。

最后去掉可重集带来的重复即可。

总复杂度 $\mathcal O(Vnm)$。

### Code

提交记录：<https://atcoder.jp/contests/agc057/submissions/57248082>。

---

