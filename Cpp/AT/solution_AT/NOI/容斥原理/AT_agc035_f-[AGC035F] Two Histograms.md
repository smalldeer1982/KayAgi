# [AGC035F] Two Histograms

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc035/tasks/agc035_f

$ N $ 行 $ M $ 列のマス目があります。高橋君は、以下のようにして各マスに整数を書き込みます。

- まず、すべてのマスに $ 0 $ を書き込む
- $ i=1,2,...,N $ に対し、整数 $ k_i\ (0\leq\ k_i\leq\ M) $ を選び、上から $ i $ 行目の左から $ k_i $ 個のマスに書かれた整数すべてに $ 1 $ を足す
- $ j=1,2,...,M $ に対し、整数 $ l_j\ (0\leq\ l_j\leq\ N) $ を選び、左から $ j $ 列目の上から $ l_j $ 個のマスに書かれた整数すべてに $ 1 $ を足す

こうして、各マスに $ 0,1,2 $ のいずれかの整数の書かれたマス目が出来上がります。最終的にできる可能性のある相異なるマス目の個数を $ 998244353 $ で割った余りを求めてください。 ただし、$ 2 $ つのマス目が異なるとは、あるマスが存在してそのマスに書かれた整数が異なることを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ N,M\ \leq\ 5\times\ 10^5 $
- $ N,M $ は整数である

### Sample Explanation 1

左のマスに $ a $ が、右のマスに $ b $ が書き込まれたマス目を $ (a,b) $ と表すことにすると、$ (0,0),(0,1),(1,0),(1,1),(1,2),(2,0),(2,1),(2,2) $ の $ 8 $ 通りのマス目ができる可能性があります。

## 样例 #1

### 输入

```
1 2```

### 输出

```
8```

## 样例 #2

### 输入

```
2 3```

### 输出

```
234```

## 样例 #3

### 输入

```
10 7```

### 输出

```
995651918```

## 样例 #4

### 输入

```
314159 265358```

### 输出

```
70273732```

# 题解

## 作者：xmy3 (赞：18)

PS：这个题解只是翻译一下官方题解给出的结论的证明，关于容斥的部分略去。

如果存在 $k_i=j-1,l_j=i$ ，那么把它换成 $k_i=j,l_j=i-1$ 显然方格里的数不变。

我们记不存在 $k_i=j-1,l_j=i$ 的方案为 $\text{regular~expression}$，可以证明两种不同的 $\text{regular~expression}$ 对应的网格不同构，证明如下：

假设两个 $\text{regular~expression}$ 分别为 $k_1,k_2,...,k_N,l_1,l_2,...,l_M$ 和 $k'_1,k'_2,...,k'_N,l'_1,l'_2,...,l'_M$，它们对应的网格同构，尝试推出矛盾：
- 找到最小的 $j$，使得 $l_j\neq l_j'$，不妨令 $l_j<l'_j$，并记 $r=l'_j$
- 因为两个网格同构，必然有 $k_r\ge j,~k'_r<j$，这样这个位置才能同时为 1
- 如果 $j=1$，那么 $k'_r=0$，这与它是 $\text{regular~expression}$ 矛盾。
- 如果 $j>1$，那么 $k'_r<j-1$，而 $k_r\ge j,l_{j-1}=l'_{j-1}$，推出两个网格$(r,j-1)$的位置不相等，矛盾。

所以就只需要统计不存在 $k_i=j-1,l_j=i$ 的方案了。

---

## 作者：yijan (赞：12)

建议在 luogu 博客或者 [这里](https://www.yijan.co/agc035f-two-histograms/) 查看

首先，所有不同的操作方式是很好求的。但是不同操作序列并不正好对应一种不同的网格。

考虑什么情况下两个操作序列不同但是求出了不同的网格。如果出现了这种情况：

```
0 0 1 0
0 0 1 0
1 1 1 0
0 0 0 0
```

那么明显，要么第三行 +3 ，第三列 +2 或者 第三行 +2 第三列 +3 ，会出现两种不同的状况。

除开这种情况，不会有出现两种不同操作序列对应同一个网格图了。~~神仙[137_345_2814](https://www.luogu.com.cn/user/27329)已经教了我一个绝妙的证明，可惜我懒得写下来了（逃~~

我们将一个导致操作序列出现不同的位置称为一个拐角，那么很明显，同一列或同一行不会出现超过一个拐角。因为在 $(i,j)$ 出现拐角，也就是这里导致了 $i$ 行，$j$ 列有两种不同的操作方式，那么 $(i+1,j)$ 和 $(i,j+1)$ 必然都是 $0$ （否则并不能对应两个不同的操作方式）。

设 $f_i$ 为**钦定**了 $i$ 个拐角的网格图的数量。 $f_i$ 是很好求的，选择 $i$ 行 $i$ 列后进行排列一下即可
$$
f_i = \binom n i \binom  m i i! (n+1)^{m-i} (m+1)^{n-i}
$$
设 $f'_i$ 为**钦定**了 $i$ 个拐角的操作序列的数量，于是我们知道
$$
f_i' = 2^i f_i
$$
然后设 $g_i$ 是**正好** $i$ 个拐角的操作序列的数量。可以二项式反演一下有 
$$
f_i' = \sum_{j\ge i} \binom j i g_j \Leftrightarrow g_i = \sum_{j \ge i} \binom j i (-1)^{j-i} f_j'
$$
我们要求的是
$$
\sum_{i\ge 0} \frac{g_i}{2^i}
$$
推式子：
$$
\begin{aligned}&=\sum_{i\ge 0} \frac{g_i}{2^i}\\&=\sum_{i\ge 0} \frac{1}{2^i} \sum_{j\ge i} \binom j i (-1)^{j-i} f_j'\\&=\sum_{i\ge 0} \frac{1}{2^i} \sum_{j\ge i} \binom j i (-1)^{j-i} f_j2^j\\&=\sum_{j \ge 0} f_j \sum_{i\le j} \binom j i (-1)^{j-i}2^{j-i}\\&=\sum_{j \ge 0} f_j (-1)^j\end{aligned}
$$
最后是一个二项式定理。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
#define MAXN 500006
#define P 998244353
int n , m;

int Pow( int x , int a ) {
    int ret = 1;
    while( a ) {
        if( a & 1 ) ret = 1ll * ret * x % P;
        x = 1ll * x * x % P , a >>= 1;
    }
    return ret;
}

int J[MAXN] , iJ[MAXN];

int C( int a , int b ) {
    return J[a] * 1ll * iJ[b] % P * iJ[a - b] % P;
}

int main() {
    J[0] = iJ[0] = 1;
    for( int i = 1 ; i < MAXN ; ++ i ) J[i] = J[i - 1] * 1ll * i % P , iJ[i] = Pow( J[i] , P - 2 );
    cin >> n >> m;
    int lim = min( n , m );
    int c = 0 , res = 0;
    for( int i = 0 , zjk ; i <= lim ; ++ i ) {
        zjk = C( n , i ) * 1ll * C( m , i ) % P * J[i] % P * Pow( n + 1 , m - i ) % P * Pow( m + 1 , n - i ) % P;
        if( c ) zjk = P - zjk;
        c ^= 1;
        res = ( res + zjk ) % P;
    }
    cout << res << endl;
}
```



---

## 作者：玄燕本燕 (赞：8)

提供一个与所见题解不同的思路。可能较为复杂，但本人感觉更为自然。最后的式子是一样的。

考虑如何判定一个给定的网格是否能通过操作得到。我们从下往上依次确定操作。观察网格的最后一行，能发现可能合法的网格具有如下性质：（这些性质和下文提到的性质都较为显然，因此不额外进行原因的说明）
1. 所有 $2$ 应在所有 $0$ 的左边。
2. 这一行的 $+1$ 操作一定延伸到了最右的 $2$ 的右侧，但在最左的 $0$ 的左侧。这二者之间一定全是 $1$。
3. 一个 $2$ 会迫使其所在的列的 $+1$ 操作从网格最上面延伸至当前这一行。我们称这样的列“被限制”。同时，若一个 $1$ 的左边有 $0$，那么它也会迫使其所在列的 $+1$ 操作有如上性质。

一个例子如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/umvhhb0l.png)
图中红色部分即代表“被限制”的列。这一行的 $+1$ 操作至少应延伸到蓝色实线部分，至多延伸到蓝色虚线部分。可以发现，这二者之间的某个 $1$ 若未被该行 $+1$ 操作覆盖，则也会使其所在列“被限制”。因此我们强制让该 $+1$ 操作延伸到虚线部分，就不会出现这种情况，是对其他尚未确定的操作限制最少的。

那么现在最后一行的操作已经确定了，而它对于其他操作的确定的影响，仅仅是这些“被限制”的列。

看向下一个行。如果给当前行确定操作时，已经有了一些“被限制”的列，是什么情况呢？上面的性质都会继续存在，但是会多出一条：在当前行内，已经“被限制”的列只能是 $1$ 或 $2$，且这些 $2$ 一定在这些 $1$ 的前面。

接下来我们定义这一行的**分段点**：关注上述的 $2$ 和 $1$ 中，最右的 $2$ 和最左的 $1$ 之间的部分。如果它们之间没有 $0$，称这个“最左的 $1$”为**分段点**；否则，称这些 $0$ 中**最左**的为**分段点**。

（若最右的 $2$ 不存在，视其在整行的左边；最左的 $1$ 不存在视为在整行右边）

那么，处在**分段点**及其右侧的格子，只能是 $0$ 或 $1$；其左的格子，只能是 $1$ 或 $2$。并且，如果右侧格子是 $1$，会造成所在列“被限制”；左侧格子为 $2$ 同理。

此时进行一个重要观察：在当前行，如果一个列确定了“被限制”的时间（之前、在当前行新增、尚未），又确定了在分段点的哪一侧（左、右），就可以唯一确定这一列应该是哪个数了。也即，当前行的数字，和当前行的分段点位置+每一列的“被限制”情况，构成一个双射。

于是可以尝试设计一个这样的dp：记 $dp_{i,j}$ 表示在第 $i$ 行之后填数的方案数，使其确定第 $i$ 行之后的操作会让 $j$ 个列“被限制”。

考虑刷表转移。枚举新增“被限制”列数 $k$，并分类讨论。
1. 分段点所在列是一个之前已经“被限制”的列。
$$dp_{i-1,j+k}\ \leftarrow_+\ dp_{i,j}\times j\times \binom{m-j}{k}$$
2. 是一个未“被限制”的列。给它填上0。
$$dp_{i-1,j+k}\ \leftarrow_+\ dp_{i,j}\times (m-j)\times \binom{m-j-1}{k}$$

~~我们终于获得了一个多项式时间的算法~~。考虑上述dp过程的组合意义，就是在每一行选了一个分段点，又给每一列确定了在哪一行首次“被限制”，以此唯一对应一个合法填数方案。（~~想一想，为什么~~）但是有一个限制：如果第 $j$ 列被第 $i$ 行选为了分段点，则其不能恰好在第 $i$ 行时首次“被限制”。

用生成函数描述，则一个行的生成函数为：
$$\sum_{i=0}(m-i+1)\dfrac{x^i}{i!}=(m+1-x)e^x$$
组合意义是说，枚举这一行造成的“首次被限制”的列数 $i$，则这些列不能被这一行选为分段点，于是选分段点的方案数是 $m+1-i$。（$+1$ 的原因是分段点可以在整行的右边，可以看分段点定义处）。而指数型生成函数就将列的标号分配给了行。

所以答案就是：
$$\left[\dfrac{x^m}{m!}\right][(m+1-x)e^x]^n\times e^x$$
最后卷一个 $e^x$，是因为可能有的列最后也没有“被限制”，将它们放进 $e^x$ 中。

化简得
$$m!\sum_{i=0}\binom n i(-1)^i(m+1)^{n-i}\dfrac{(n+1)^{m-i}}{(m-i)!}$$
可以 $O(n)$ 计算。

---

## 作者：Vocalise (赞：6)

### 2020.5.8.Upd: 参见评论区。

---

一道有趣的计数题。

首先我们考虑一下如果就这样随便放的话，哪些方案会重复。

我们认为操作是有序的。所以现在就是要给操作去重。

发现只有重叠才会引起重复计数；更进一步地，发现只有如下情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/pscuww1m.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/c4lfoay5.png)

这样会有两个方案重复。

现在我们的目标是计算没有重复的方案数，即方案与目标矩阵一一对应。

考虑容斥。

则根据一个反演（当然大可不必这一步），设**至少有 $i$ 个上述局面的答案数为 $f(i)$,而正好有 $i$ 个的答案数为 $g(i)$**。

上述局面就是指图片中出现的局面，两个长条恰好交于一点。

则显然有多少上述局面就有多少重复，则

$$f(s)=\sum_{i = s}^{\min(n,m)}{g(i)}$$

为什么上界取到 $\min(n,m)$ 呢？是因为一对横纵的长条对应着一个局面，毕竟不要忘记**它们是不能出头的**。

反演得

$$g(s)=\sum_{i = s}^{\min(n,m)}{(-1)^{i - s}f(i)}$$

左边 $s$ 取 $0$ 得到

$$g(0)=\sum_{i = 0}^{\min(n,m)}{(-1)^if(i)}$$

当然也可以不推式子~~其实是背式子~~，用容斥解释。总方案中恰好有 $0$ 个重复的取法中有至少 $0$ 个的减去至少 $1$ 个的再加上至少 $2$ 个的...就是恰好 $0$ 个的了。

现在考虑计算出 $f(i)$。

因为这是“至少”，所以我们先取 $i$ 个重复的，然后剩下随便取。

先给式子，再解释。

$$f(i)=\binom n i \binom m i i! (m + 1)^{n - i}(n + 1)^{m - i}$$

首先我们枚举取哪些行列延伸并相交。这就是 $\binom n i\binom m i$

然后它们如何配对呢？为何不是 $(i!)^2$? 因为对于**行或列中的一方固定**后另一方就是一个全排列了。这就是 $i!$。

剩下的行中，可以选择不延伸，或延伸 $1-m$ 格，共 $n - i$ 行，就是 $(m + 1)^{n - i}$。

列也类似，合起来就是 $(m + 1)^{n - i}(n + 1)^{m - i}$。

于是可以 $O(n)$ 预处理阶乘，逆元， $(m + 1)$ 和 $(n + 1)$ 的幂，然后就用上面的式子算即可。

总的就是 $O(n)$。

要注意上界，是 $\min(n,m)$,$\max(n,m)$ 还是 $n,m$，各个地方不同。


```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
	return x * f;
}

typedef long long ll;
const int MAXN = 500001;
const int mod = 998244353;

int n,m;
ll fac[MAXN],ifac[MAXN];
ll pown[MAXN],powm[MAXN];

ll C(int n,int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main() {
	n = read(), m = read();
	fac[0] = 1;
	for(int i = 1;i <= n || i <= m;i++) fac[i] = (fac[i - 1] * i) % mod;
	ifac[0] = ifac[1] = 1;
	for(int i = 2;i <= n || i <= m;i++) ifac[i] = ((mod - mod / i) * ifac[mod % i]) % mod;
	for(int i = 2;i <= n || i <= m;i++) ifac[i] = (ifac[i - 1] * ifac[i]) % mod;
	pown[0] = powm[0] = 1;
	for(int i = 1;i <= m;i++) pown[i] = (pown[i - 1] * (n + 1)) % mod;
	for(int i = 1;i <= n;i++) powm[i] = (powm[i - 1] * (m + 1)) % mod;
	ll ans = 0;
	for(int i = 0;i <= n && i <= m;i++) {
		ll res = (C(n,i) * C(m,i)) % mod;
		res = res * fac[i] % mod;
		res = res * pown[m - i] % mod;
		res = res * powm[n - i] % mod;
		if(i & 1) ans = (ans + mod - res) % mod;
		else ans = (ans + res) % mod;
	}
	std::printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：justin_cao (赞：6)

考虑什么样的约束条件能与合法的方案一一对应。

可以发现，对于第$x$行和第$y$列，$k_x=y,l_y=x-1$的情况和$k_x=y-1,l_y=x$的情况是一样的。

于是可以将所要求的转化为所有不存在行和列满足$k_x=y,l_y=x-1$的方案数。可以证明，这与合法的方案是一一对应的。

那么考虑容斥解决，枚举有多少行和列满足上面的限制，那就是：
$$
\sum_{i=0}^{min(n,m)}(-1)^iC_n^iC_m^ii!(m+1)^{n-i}(n+1)^{m-i}
$$
预处理之后直接求即可，复杂度$O(n)$。

code：
```cpp
#include<bits/stdc++.h>
#define maxn 500010
#define mod 998244353
using namespace std;
typedef long long ll;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,mx,mn;
int ci_n[maxn],ci_m[maxn];
int fac[maxn],inv[maxn];
int quick_pow(int x,int p)
{
    int an=1,po=x;
    while(p)
    {
        if(p&1)  an=1ll*an*po%mod;
        po=1ll*po*po%mod;
        p>>=1;
    }
    return an;
}
int ans;
void add(int &x,int y)
{
    x=(x+y>=mod)?x+y-mod:x+y;
}
int C(int x,int y)
{
    return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int main()
{
    n=read();m=read();mx=max(n,m);mn=min(n,m);
    fac[0]=1;
    for(int i=1;i<=mx;i++)  fac[i]=1ll*fac[i-1]*i%mod;
    inv[mx]=quick_pow(fac[mx],mod-2);
    for(int i=mx-1;i>=0;i--)  inv[i]=1ll*inv[i+1]*(i+1)%mod;
    ci_m[0]=ci_n[0]=1;
    for(int i=1;i<=n;i++)  ci_m[i]=1ll*ci_m[i-1]*(m+1)%mod;
    for(int i=1;i<=m;i++)  ci_n[i]=1ll*ci_n[i-1]*(n+1)%mod;
    for(int i=0;i<=mn;i++)
    {
        int tmp=1ll*C(n,i)*C(m,i)%mod*fac[i]%mod*ci_m[n-i]%mod*ci_n[m-i]%mod;
        add(ans,(i&1)?mod-tmp:tmp);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Felix72 (赞：2)

**无式子、无结论、无人类智慧的纯粹组合意义优化 DP 做法。**

把两次染色分开看待。先从左往右扫描线，对形如下图的结构分析：

![](https://cdn.luogu.com.cn/upload/image_hosting/x528hbbn.png)

若 $i < j$，第 $j$ 列的红色格子数量不大于第 $i$ 列的。

然后一排一排地插入从上到下的染色，形如这样（公共部分为紫色）：

![](https://cdn.luogu.com.cn/upload/image_hosting/83npw35e.png)

既然我们是边扫描线边统计方案，那么我们以一列为例思考不同颜色格子的存在条件：

- 紫色：这一行的红色一直延申到了当前位置，并且还被这一列的蓝色覆盖；
- 红色或蓝色：要么是之前的红色延申了过来且没有被蓝色覆盖，要么被蓝色覆盖且之前的红色没有延申过来；
- 黑色：其余情况该格子为黑色。

紫色和黑色的情况都很唯一，可能出现重复情况的当属红/蓝格子了。如果存在一个蓝色格子，它左边的红色能延伸过来，能达到一种它本身变为红色，其他所有格子都保持原色的情况，那么恭喜你算重了。

不过这种情况仅仅发生在该列的蓝色在这个格子结束的时候。于是人为地添加一个限制：不能存在一个格子，使得该行的红色在它前一个位置结束，该列的蓝色格子在它这里结束。

写出 DP，令 $f_{i, j}$ 表示到了第 $i$ 列，有 $j$ 个红色行还在延伸的方案数。转移：

$$
f_{i, k} = f_{i - 1, j} \times {j \choose k} \times (n + 1 - (j - k))
$$

意思就是可以选择若干红色行不在延伸。当然，该列蓝色不能在这些位置停止。复杂度 $O(n^3)$。

这个 DP 的组合意义是：

> 有 $n$ 个**不同**元素，选出**若干个**分成 $m$ 个**不同**的组，每个组可以在 $n$ 个元素中选一个代表元素，也可以不选，但是只要选了，必定不能是该组的元素。求方案数。

容斥，写出 DP 式子，设 $f_{i, j}$ 表示考虑到第 $i$ 个元素，有 $j$ 个组已经被钦定选了组内的元素做代表元的方案数。转移式子：

$$
f_{i, j} = f_{i - 1, j} + f_{i - 1, j} \times m + f_{i - 1, j - 1} \times (m - (j - 1))
$$

三项分别表示不分组、随便分到某个组、分到某个组并且选为代表元。复杂度 $O(n^2)$。

答案:$\sum f_i \times (-1)^i \times (n + 1)^{m - i}$。

这个 DP 又有组合意义。把 $j$ 和 $i$ 这两维调换一下就看出来了：

> 有一条数轴，数轴上每个点 $i$ 有得分 $g_i$。一开始有一个棋子在位置 $0$，有 $n$ 秒，每秒可以选择把它向右移动一步，也可以原地不动。最后棋子所在的位置的 $g_i$ 就是得分。求所有操作方式的分数和。

这个就可以直接组合数计算了，复杂度 $O(n)$。

可能有人会说发现了这个题的重复条件也可以直接容斥推出这个式子，但我想说的是写出 DP 式子然后根据其特征一步一步做优化的思维方式同样是难能可贵的。

---

## 作者：Minche1992 (赞：2)

# **[AGC035F] Two Histograms**

根据乘法原理，可以得到总可能操作数为$(n+1)^m(m+1)^n$，而结果应该是有重复的，然后我们发现只有一种情况是会出现重复的，（即操作不同，但是结果相同）也就是存在 $\ k_{i+1}=j$，$l_j=i\ $ 的情况，至于证明嘛，官方的证明很详细了，这里着重讨论容斥原理的部分。

## 前置知识

容斥原理 https://codeforces.com/blog/entry/64625

### 基本形式

设我们有集合 $S$，$A_i\subset S$， 记 $\bar{A_i}$ 为 $A_i$ 在 $S$ 中的补集，那么我们有：

练习：思考如何证明这个式子。

$$
\left|\bigcap_{i=1}^n \bar{A_i}\right| = \left|S - \bigcup_{i=1}^n A_i \right| =|S| - \sum_{i=1}^n |A_i| + \sum_{1 \leqslant i < j \leqslant n} |A_i\cap A_j| - \cdots + (-1)^n |A_1\cap\cdots\cap A_n|.
$$



证明：假设 $x \in \bigcup_{i=1}^n A_i$，我们设 $x$ 恰好在这 $n$ 个集合中的 $a$ 个集合中出现过。考虑等式左侧，由于存在一个 $A_i$ 包含 $x$,则此$A_i$的补集中无 $x$, 故交集中无 $x$。 

则 $-\sum_{i=1}^n |A_i|$ 中 $x$ 贡献了 $-a$，$\sum_{1 \leqslant i < j \leqslant n} |A_i\cap A_j|$ 中 $x$ 贡献了 $C_a^2$ 个。那么我们可以得到，$x$ 在右边贡献了

$$
ans = 1-C_a^1+C_a^2+\cdots+ (-1)^{a}C_a^a
$$

根据二项式定理，我们有$(1+x)^a = 1+C_a^1x+C_a^2 x^2+\cdots + C_a^a x^a$，代入 $x=-1$ 即可，$x$ 贡献了 $0$ 次。

下面考虑第二种情况

等式左边易得 $x$ 被计算了一次

考虑等式右边首先 $|S|$ 中 $x$ 被计算一次，后面的式子中 $x$ 均未出现

故等式两边一致

综上所述，我们证明了这个式子的正确性。

### 进阶形式

假设我们有一个全集 $X$，并且有一个关于 $X$ 中元素性质的集合 $E=\{e_1,\cdots, e_k \}$。对于 $E$ 中的每个性质 $e_i$, $X$ 中可能有元素满足，可能有元素不满足。我们可以定义我们想要的性质，例如 $e_i$ 可以是“$>0$”，也可以是“是个整数”。我们可以定义 $A_i$ 为 $X$ 中满足 $e_i$ 的元素所构成的集合（这里集合中的元素可能也满足其他的性质 $e_j$, 也可能不满足，不重要）。那么 $|X \backslash \cup_{i=1}^n A_i|$ 就是 $X$ 中不满足所有 $e_i$ 性质的个数.

我们记

$$
N_{\supset T} = \#\{x\in X, x满足T 中的所有条件（可以满足E中的其他条件）\}\\ N_{= T} = \#\{x\in X, x只满足T中的所有条件（不满足E中的其他条件）\}
$$

容斥原理（Inclusion-Exclusion Principle）

$$
N_{=\empty} = \sum_{T\subset E}(-1)^{|T|} N_{\supset T} = \sum_{k = 0}^n(-1)^k \sum_{T:|T|=k}N_{\supset T}
$$

练习：利用最初的公式推导上面这个版本的结论。

证明：中间推导右边是显然的。

练习：利用**上面的公式**推导下面的结论。

证明：设 $e_{i,j}$ 为 $存在i， j满足\  k_{i+1}=j, l_j=i$

那么 定义$T_k = \sum_{i_1,i_2,\cdots i_k, j_1,j_2,\cdots, j_k} |\cap_{1\le t \le k}S_{i_t,j_t}| =  C_m^kC_n^k\times k!\times(n+1)^{m-k}(m+1)^{n-k}$

$设S = |\cup e_{i,j}|$， 易得：

$$
|S|\ =\sum_{k = 1}^{\min(m,n)} (-1)^{k+1} T_k 
$$


## 思路

设 $P$ 是一种操作

$S = \{P |P 中存在有\  k_{i+1}=j, l_j=i \}$ ，令 $S_{i,j} = \{P |P满足\  k_{i+1}=j, l_j=i \}$

$$
S = \cup_{i,j} S_{i,j}\\
$$

性质 1：

$$
S_{i, j_1}\cap S_{i,j_2}=\varnothing, S_{i_1, j}\cap S_{i_2,j}=\varnothing
$$

性质2，如果 $i_1\neq i_2, j_1\neq j_2$，（提示：除了 $i_1,j_1, i_2,j_2$ 固定了，其他地方随便动）

$$
|S_{i_1,j_1}\cap S_{i_2, j_2}|\ =(n+1)^{m-2}(m+1)^{n-2}
$$

所以

$$
T_2 = \sum_{i_1,j_1,i_2,j_2} |S_{i_1,j_1}\cap S_{i_2, j_2}| = C_n^2C_m^2\times2!\times (n+1)^{m-2}(m+1)^{n-2}
$$

定义 $T_k = \sum_{i_1,i_2,\cdots i_k, j_1,j_2,\cdots, j_k} |\cap_{1\le t \le k}S_{i_t,j_t}| =  C_m^kC_n^k\times k!\times(n+1)^{m-k}(m+1)^{n-k}$ 

下面求 $|S|$，

$$
|S|\ =\sum_{k = 1}^{\min(m,n)} (-1)^{k+1} T_k 
$$

最后的答案是
$$
ans = (n+1)^m(m+1)^n-|S|\\ = \sum_{k=0}^{\min(m,n)}(-1)^k C_m^kC_n^k\times k!\times(n+1)^{m-k}(m+1)^{n-k}
$$



代码：

```cpp
#include <iostream>
#include <vector> 
typedef long long ll;
const ll mod = 998244353;
using namespace std;
ll n, m;
vector<ll> fct;
vector<ll> ifct;
inline ll power(ll a, ll b){
    ll ret = 1;
    for (; b; b = b>>1) {
        if (b&1) ret = ret*a%mod;
        a = a*a%mod;
    }
    return ret;
} //快速幂 
inline ll Com(ll a, ll b) {
    return fct[a]*ifct[b]%mod*ifct[a-b]%mod;
} //组合数 
int main() {
	cin >> n >> m;
    if (n > m) swap(n, m);
	ll ans = 0;
    fct.assign(m+1, 0);
    ifct.assign(m+1, 0);
    fct[0] = fct[1] = 1;
    ifct[0] = ifct[1] = 1;
    for(ll i=2; i<=m; i++) 
        ifct[i] = ((mod-mod/i)*ifct[mod%i]) % mod;
	for(ll i=2; i<=m; i++) 
        ifct[i] = (ifct[i-1]*ifct[i]) % mod;
    for (ll i=2; i<=m; i++) {
        fct[i] = (i*fct[i-1]) % mod;
    } //阶乘 
    ll i=1;
    for (ll k=0; k<=n; k++) {
    	ans += i*(Com(m, k)*Com(n, k)%mod*fct[k] % mod *power(n+1, m-k)% mod*power(m+1, n-k)%mod);
        ans %= mod; 
        i *= -1ll;
    }
	cout << (ans+mod)%mod;
	return 0;	
}
```

---

## 作者：Mortidesperatslav (赞：2)

参考了一下其他题解，但是应该讲的更细节一点。主要增补了一些推导过程。

感觉这题难度不止 $3720$。

求操作方式是非常简单的，但是容易发现操作序列和操作结果不构成映射关系（不等式秒了），这是因为不同操作序列可以产生相同结果。

但是我们会发现一个性质：当且仅当存在一个格子为 $1$ 且正左边和正上方所有格子都不为 $0$，对于这个格子所在的行和列存在不同操作序列相同操作结果。

证明：假设格子坐标为 $(i,j)$，$k_i=x$，$l_j=y$。

+ 若当前格为 $0$，则 $x < j$ 且 $y < i$，与当前格无关。

+ 若当前格为 $2$，则 $x \ge j$ 且 $y \ge i$，与当前格无关。

+ 若当前格为 $1$ 但左边或上面有格子为 $0$，则 $x < j$ 或 $y<i$，依然与当前格无关。

+ 否则 $x$ 为 $j$，$y$ 为 $i-1$，或 $x$ 为 $j-1$，$y$ 为 $i$。这个时候会出现冲突。

我们不妨把这样的冲突格子称作 JunXion 格子。用 $f_i$ 表示至少有 $i$ 个 JunXion 个格子的网格图的数量。

方案数怎么算呢？我们会发现实际上从 $n$ 行中选出 $i$ 行，从 $m$ 行中选出 $i$ 列，保持 $i$ 行的顺序不变，$i$ 列进行全排列，然后剩下的随便赋值。

也就是说，$f_i=i!C_{m}^{i}C_{n}^{i}(n+1)^{m-i}(m+1)^{n-i}$。

这两个幂次的 $+1$ 是因为可以不选格子。

设 $g_i$ 为至少 $i$ 个 JunXion 格子的操作序列数量。根据前文 JunXion 格子的性质可知，$g_i=f_i \times 2^i$。

接下来我们再定义一个 $h_i$ 表示恰有 $i$ 个 JunXion 格子的操作序列数量。

注意到 $\displaystyle{\sum_{j=i}^{\min\{n,m\}}C_j^ih_j}=g_i$。

那么我们如何用 $g_i$ 表示 $f_i$ 呢？有一个东西叫[二项式反演](https://oi-wiki.org/math/combinatorics/combination/#%E4%BA%8C%E9%A1%B9%E5%BC%8F%E5%8F%8D%E6%BC%94)。

$h_i=\displaystyle{\sum_{j=i}^{\min\{n,m\}}C_j^i(-1)^{j-i}g_j}$。

我们需要算的就是操作序列数除以 $2$ 的 JunXion 格子个数次方（因为每一个 JunXion 格子会导致两种序列一个结果）。

也就是要算 $\displaystyle{\sum_{i=0}^{\min\{n,m\}}\dfrac{h_i}{2^i}}$。

把 $h_i$ 用 $f_i$ 代进去：

$$\displaystyle{\sum_{i=0}^{\min\{n,m\}}\dfrac{h_i}{2^i}=\sum_{i=0}^{\min\{n,m\}}\dfrac{1}{2^i}\displaystyle{\sum_{j=i}^{\min\{n,m\}}C_j^i(-1)^{j-i}f_i2^i}}$$

交换两层：

$$=\displaystyle{\sum_{j=0}^{\min\{n,m\}}f_j\displaystyle{\sum_{i=0}^{j}C_j^i(-1)^{j-i}2^{j-i}}}$$

拆开 $-1$ 的次数：

$$=\displaystyle{\sum_{j=0}^{\min\{n,m\}}f_j\displaystyle{\sum_{i=0}^{j}C_j^i[(-1)^j(-1)^{-i}2^{j-i}]}}$$

利用 $-1$ 的性质：

$$=\displaystyle{\sum_{j=0}^{\min\{n,m\}}f_j\displaystyle{\sum_{i=0}^{j}C_j^i[(-1)^j(-1)^{i}2^{j-i}]}}$$

提出一个 $(-1)^j$：

$$=\displaystyle{\sum_{j=0}^{\min\{n,m\}}f_j(-1)^j\displaystyle{\sum_{i=0}^{j}C_j^i[(-1)^{i}2^{j-i}]}}$$

二项式定理：

$$=\displaystyle{\sum_{j=0}^{\min\{n,m\}}f_j(-1)^j(2-1)^j}=\displaystyle{\sum_{j=0}^{\min\{n,m\}}f_j(-1)^j}$$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, fac[500005], ans;
const int mod = 998244353;
int qpow(int x, int k){
	int ans = 1;
	while (k){
		if (k & 1)
			ans = ans * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ans;
}
int inv(int x){
	return qpow(x, mod - 2);
}
int fmod(int x, int y){
	return x * inv(y) % mod;
}
int C(int n, int m){
	return fac[n] * inv(fac[m]) % mod * inv(fac[n - m]) % mod;
}
int nm(int x){
	return (x % mod + mod) % mod;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	fac[0] = 1;
	for (int i = 1; i <= max(n, m); i++)
		fac[i] = fac[i - 1] * i % mod;
	for (int i = 0; i <= min(n, m); i++){
		int gx = C(n, i) * C(m, i) % mod * fac[i] % mod;
		gx = gx * qpow(n + 1, m - i) % mod * qpow(m + 1, n - i) % mod;
		if (i & 1)
			ans = nm(ans - gx);
		else
			ans = nm(ans + gx);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：xht (赞：2)

## [Two Histograms](https://atcoder.jp/contests/agc035/tasks/agc035_f)

### 题意

- 对于一个 $n \times m$ 的矩阵，一开始每个位置上都是 $0$。
- 对于每一行，选择最左边的 $0 \sim m$ 个位置 $+1$；对于每一列，选择最上边的 $0 \sim n$ 个位置 $+1$。
- 求最后能形成的矩阵方案数。
- $n,m \le 5 \times 10^5$，答案对 $998244353$ 取模。

### 题解

注意到只有 $k_x = y$，$l_y = x - 1$ 和 $k_x = y - 1$，$l_y = x$ 才会形成一样的矩阵，那么枚举满足条件的 $(x,y)$ 对数容斥：
$$
ans = \sum_{i=0}^{\min(n,m)} (-1)^i \binom ni \binom mi i!(m+1)^{n-i}(n+1)^{m-i}
$$
时间复杂度 $\mathcal O(n)$。

### 代码

```cpp
int main() {
	int n, m;
	rd(n, m), init(max(n, m) + 1);
	modint a = (modint)(m + 1) ^ n, b = (modint)(n + 1) ^ m, w = 1, ans;
	for (int i = 0; i <= min(n, m); i++, a *= v[m+1], b *= v[n+1], w = -w)
		ans += w * binom(n, i) * binom(m, i) * p[i] * a * b; 
	print(ans);
	return 0;
}
```

---

## 作者：Schi2oid (赞：1)

### 题意简述

现在你有一个 $n\times m$ 的网格，你会按顺序进行做如下操作：

+ 把所有格子中的数都赋为 $0$。
+ 对每一行选一个 $k_i$ $(0\leq k_i\leq m)$，并把这一行最左边的 $k_i$ 个格子 $+1$。
+ 对每一列选一个 $l_i$ $(0\leq l_i\leq n)$, 并把这一列最上面的 $l_i$ 个格子 $+1$。

经过这些操作后，你可以得到一个只包含 $0$，$1$，$2$ 的网格。请你求出，在所有可能的操作下，可以得到多少本质不同的网格。

两个网格被称为本质不同的，当且仅当存在至少一个位置，两个网格对应位置上的数不同。

输出答案对 $998244353$ 取模的结果。

### 思路分析

考虑什么情况下会出现两个网格虽然本质相同，但是填入的 $k,l$ 不同。以下图为例：

```
0 0 1 1
0 0 1 1
1 1 1 1
1 1 1 1
```

显然，存在很多组 $l$ 和 $k$ 可以构成上图。但是，我们认为 $k_3=4,k_4=4,l_3=2,l_4=2$ 是这个图案对应的填法。定义一个**合法的填法**中不存在 $k_i=j-1,l_j=i$ 的情况。一个简单的将填法变为合法的方式是，依次考察每一个 $k_i$，若不合法，就执行 $l_{k_i}\leftarrow l_{k_i}-1,k_i\leftarrow k_i+1$。直到合法为止。显然这样的调整只会经历有限步，这是因为每次调整后 $k_i$ 都会变大 $1$。那么，所有的填法都被我们唯一转化成了一个**合法的填法**，且转化前后其所构成的最终图案是一样的。本质思想是利用代表元去重。

现在，我们要说明对于两个不同的**合法的填法**，它们最终形成的图案不同。同时，对于两个形成相同图案的填法，它们形成的**合法的填法**相同。换句话来说，图案和**合法的填法**一一对应。注意到这两个命题互为逆否命题，故只证明第一个。

由于填法不同，故一定存在一对 $l_i$ 或 $k_i$ 填入的数不同。不妨设存在 $l_i$ 填入的数不同。那么我们找到最小的 $x$ 使得两种方案填入的 $l_x$ 不同，称第一种方案填入的数为 $l_x$，第二种方案填入的数为 $l'_x$，不妨设 $l_x<l'_x$。那么，此时两个图案如图所示：

```
? ? ? 1 ?		? ? ? 1 ?
? ? ? 1 ?		? ? ? 1 ?
? ? ? ? ?		? ? ? 1 ?
? ? ? * ?		? ? ? 1 ?
? ? ? ? ?		? ? ? ? ?
 case 1   		 case 2
```

考察 $(l'_x,x)$，上图中的 ```*```。在第一种填法中，这一个格子最终的值 $\le 1$；在第二种填法中，这一个格子最终的值 $\ge 1$。由于两种方案的最终图案应该相同，所以，这个格子最终的值只能是 $1$，即 $k_{l'_x}\ge x,k'_{l'_x}\le x-1$。又由于这两种填法都必须是**合法的填法**，那么 $k'_{l'_x}\not =x-1$，即 $k'_{l'_x}< x-1$。此时两个图案如图所示：

```
? ? ? 1 ?		? ? ? 1 ?
? ? ? 1 ?		? ? ? 1 ?
? ? ? ? ?		? ? ? 1 ?
1 1 1 1 1		1 1 * 1 ?
? ? ? ? ?		? ? ? ? ?
 case 1   		 case 2
```

此时再考察 $(l'_x,x-1)$，即第二种填法中在第 $l'_x$ 这一行的缝隙中最靠右的位置，上图中的 ```*```。由于 $x$ 是第一个使得 $l$ 不同的位置，所以 $l_{x-1}=l'_{x-1}$。两种填法原本填入的值不同，再加上一个相同的值 $0/1$，因此，两种填法在这一格子内的值一定不同，推出矛盾，证毕。

至此，问题转化为对**合法的填法**进行计数。

我们可以换一个角度，统计恰好有 $i$ 个位置不合法的方案数，再进行累加。容易发现不合法位置之间的行坐标与列坐标都不相同。这一过程可以借助容斥转化为求钦定有 $i$ 个位置不合法的方案数（不合法位置即为 $k_i=j-1,l_j=i$ 中的 $(i,j)$）。具体来说：
$$
Ans=\sum_{i=0}^{\min\{n,m\}}(-1)^i\binom{n}{i}\binom{m}{i}i!(m+1)^{n-i}(n+1)^{m-i}
$$
上式意为先挑出不合法位置的行坐标和列坐标，再进行组合，其余位置随便填。总复杂度 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int LIM=1e6;
const int mod=998244353;
int jc[1000005],jcny[1000005];
int qkp(int x,int k){
	int ret=1;
	while(k){
		if(k&1) ret=ret*x%mod;
		k>>=1;
		x=x*x%mod;
	}
	return ret;
}
int C(int x,int y){return jc[x]*jcny[y]%mod*jcny[x-y]%mod;}
signed main(){
	int n,m;
	cin>>n>>m;
	jc[0]=1;
	for(int i=1;i<=LIM;i++) jc[i]=jc[i-1]*i%mod;
	jcny[LIM]=qkp(jc[LIM],mod-2);
	for(int i=LIM-1;i>=0;i--) jcny[i]=jcny[i+1]*(i+1)%mod;
	int ans=0;
	for(int i=0;i<=min(n,m);i++) ans=(ans+((i&1)?(-1):1)*C(n,i)%mod*C(m,i)%mod*jc[i]%mod*qkp(m+1,n-i)%mod*qkp(n+1,m-i)%mod+mod)%mod;
	cout<<ans;
	return 0;
}
```





---

## 作者：Ephemeroptera (赞：1)


**简要题意：**  
 有一个 $n \times m\space (1 \le n,m \le 5 \times 10^5)$ 的棋盘，对于每一行和每一列选择当前行和列的一个格子，并将从这个行或列的起始点到这个格子全部             	  $+1$，得到的棋盘本质不同的有多少种。

**Solution**:  
随便操作一下，容易发现很容易就将染出重复颜色棋盘来。重复的原因在于一行一列交在了一起并且不再向下延申，而此时这种染色    	  情况对应了两种染色的方案，所以我们规定当且仅当行染到这里才是合法的，明显地，这样规定之后不会对答案产生干扰。这样对重复的东西规   	  定之后，不难想到使用容斥（二项式反演）来统计方案，我们设 $f(i)$ 表示规定 $i$ 个位置不合法，其余随便填。那么 $f(i)$ 方便表示出来。
$$
f(i) = i! {n \choose i} {m \choose i} (m + 1)^{n - i}(n + 1)^{m - i}
$$
 具体意义是，我们先随便选将要产生不合法的行和列，然后利用 $i!$ 对行和列进行配对，这样对于选取的行和列而言，其结果已经固定，再对剩下 	  的行和列进行选取。有了这一个那么 $g(i)$ 就会是恰好 $i$ 个位置不合法，答案将会是 $g(0)$ 。其满足 $f(i) = \sum_{j = i}^n {j \choose i}g(j)$ ，所以 $g(0)$ 可由反演得	  出 $g(0) = \sum_{i = 0}^n (-1)^i{n \choose 0} f(i)$。

**Summary**: 个人认为此题中规定**合法**方案很有价值，这是对于重复方案的一个很经典的处理。

---

## 作者：chenhouyuan (赞：0)

首先不考虑本质不同的条件，那么总的操作方案是 $(n+1)^m(m+1)^n$。接下来考虑如何去重。注意到如果操作方案中存在形如 $k_i=j$ 且 $l_j=i-1$ 的部分那么其可以被替换为 $k_i=j-1$ 和 $l_j=i$ 导致重复。如果没有呢？结论是有且仅有唯一的操作方案。下面给出证明：考虑 $k_n=i$，则由假设得 $l_i<n-1$ 且 $n$ 行 $i$ 列之后的 $1$ 只能由 $l_j=n$ 得到。然后递归考虑每一行即可得到唯一操作方案。

现在问题转化成求上述情况不发生的方案数，考虑容斥。记 $f_i$ 表示至少发生 $i$ 次上述情况的方案数，则 $f_i=\binom{n}{i}\binom{m}{i}i!(n+1)^{m-i}(m+1)^{n-i}$。容斥得最终答案为 $\sum_{i=0}(-1)^if_i$。
##### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=5e5+5,mod=998244353;
ll n,m,ans,jc[N],ny[N];
ll c(ll x,ll y){
	return jc[x]*ny[x-y]%mod*ny[y]%mod;
}
ll ksm(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1){
			res*=x;
			res%=mod;
		}
		x*=x;
		x%=mod;
		y>>=1;
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	jc[0]=1;
	ny[0]=1;
	for(ll i=1;i<N;i++){
		jc[i]=i*jc[i-1]%mod;
		ny[i]=ksm(jc[i],mod-2);
	}
	cin>>n>>m;
	for(ll i=0;i<=min(n,m);i++){
		ll f=c(n,i)*c(m,i)%mod*jc[i]%mod*ksm(n+1,m-i)%mod*ksm(m+1,n-i)%mod;
		if(i&1)f=mod-f;
		ans=(ans+f)%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Aurie (赞：0)

如果不考虑算重问题，答案显然是 $(n+1)^m(m+1)^n$。

考虑什么时候可能会算重，会算重当且仅当结果网格出现以下子布局：

```
? 1 ?
1 1 0
? 0 ?
```

此时，最中间的 $1$ 可能是由横向的 $k_i$ 贡献，也可能是由纵向的 $l_j$ 贡献。这个条件的充分性是显然的。如何证明必要性？考虑以最中间的 $1$ 为主体证明，若最中间的 $1$ 是 $2$，则说明 $k_i$ 和 $l_j$ 均要包含住该点，此时只有这一种情况——都包含该点，不会算重。若中心的 $1$ 下面或右面有一个不为 $0$，则证明不为零的那个对应的 $k_i$ 或 $l_j$ 要延伸下去，另一个到此处停止，情况唯一不会算重。考虑如何避免算重，可以钦定出现这种情况时，中间的 $1$ 由横向的包含，即对于任意 $i,j$ 不存在（删掉） $k_i=j-1$ 且 $l_j=i$ 的情况。考虑使用总情况数减去要删掉的情况数。一种 $k,l$ 数组的情况要被删掉当且仅当存在一组 $i,j$ 使得 $k_i=j-1,l_j=i$，存在性命题是一种并集，考虑使用容斥解决。设 $f_k$ 为：钦定 $k$ 组 $i,j$ 使得 $k_i=j-1,l_j=i$，其余不管的方案数。则 $f_i=C_n^iC_m^ii!(n+1)^{m-i}(m+1)^{n-i}$，套用最朴素的容斥式子，最终要删掉的情况数为：

$$\sum_{i=1}^{\min\{n,m\}}{(-1)^{i-1}f_i}$$

最后的最后：

$$ans=(n+1)^m(m+1)^n-\sum_{i=1}^{\min\{n,m\}}{(-1)^{i-1}f_i}
\\=(n+1)^m(m+1)^n+\sum_{i=1}^{\min\{n,m\}}{(-1)^if_i}
\\=(n+1)^m(m+1)^n+\sum_{i=1}^{\min\{n,m\}}{(-1)^iC_n^iC_m^ii!(n+1)^{m-i}(m+1)^{n-i}}$$

## 代码
```cpp
#include <bits/stdc++.h>
typedef long long ll;
const int mod = 998244353;
using namespace std;
const int N = 1e6;
int fp(int x, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = (ll) res * x % mod;
        x = (ll) x * x % mod;
        n >>= 1;
    }
    return res;
}
int pre[N];

int C(int n, int m) {
    if (m > n) return 0;
    return (ll) pre[n] * fp((ll) pre[m] * pre[n - m] % mod, mod - 2) % mod;
}
int n, m;
int main() {
    cin >> n >> m;
    pre[0] = 1;
    for (int i = 1; i <= max(n, m) + 3; i++) pre[i] = (ll) pre[i - 1] * i % mod;
    int ans = (ll) fp(n + 1, m) * fp(m + 1, n) % mod;
    for (int i = 1; i <= min(n, m); i++) {
        ans += (i & 1 ? -1ll : 1ll ) * C(n, i) % mod * C(m, i) % mod * pre[i] % mod * fp(n + 1, m - i) % mod * fp(m + 1, n - i) % mod;
        ans %= mod;
    }
    cout << (ans + mod) % mod << endl;
    return 0;
}
```

---

## 作者：yllcm (赞：0)

首先考虑怎么判断一个序列是合法的。

假如我们只保留行的操作，那么会得到一个只有 ${0,1}$ 的网格，$1$ 的形状形似“山峰”；只保留列的情况同理。那么可以得到一个判断合法的思路：在网格中删去列所对应的“山峰”，判断剩下的是否是一个合法的山峰图形。

分析格子，可以发现一些点是必须被删去的：

* 重复格子：$a_{i,j}=2$ 的格子。
* 悬浮格子：$a_{i,j}=1$ 且 $a_{i,j-1}=0$ 的格子。

可以得到一个判定合法的方式：从 $1\sim m$ 枚举每一列，找到必须被删去的最远的格子，假设为 $a_{x,i}$，那么令 $l_i=x$，并删去这些格子。注意删去这些格子可能形成新的悬浮格子。如果不能删除，则不合法。（容易发现，只需要删到最远的必删格子，删多了是不优的）

注意到我们的判断过程是唯一的，这说明：每个合法的方案可以和上述判断方式构成双射。所以不妨计数有多少种局面的判断过程是某个确定的过程，我们用序列 $l_i$ 表示这个过程。

注意到，如果我们依次考虑某一行 $x$，找到 $l_i=x$ 的所有 $i$，那么 $a_{x,i}$ 为重复格子的 $i$ 必定是一个前缀。这是因为这一行的行山峰会覆盖这些格子，而除开行山峰覆盖的格子，剩下格子的摆放方式是唯一的，可以根据悬浮格子的位置来还原。所以所有局面和每行行山峰的格子数量构成双射，只需要考虑行山峰的长度是否合法。这是简单的，行山峰的长度合法当且仅当它后面的一个格子不是悬浮格子，所以假如 $l_i=x$ 的 $i$ 有 $s$ 个，那么行山峰长度的方案数就是 $m+1-s$。

所以，问题被我们转化成了如下形式：对于序列 $b_{0\sim n}$，$b_x$ 表示 $l_i=x$ 的数量，保证 $b$ 的元素和为 $m$，序列的权值为 $\binom{m}{b_0,b_1,\cdots,b_n}\prod_{i=1}^n (m+1-b_i)$，你需要求所有序列的权值和。写成生成函数的形式就是：

$$
[\frac{x^n}{n!}]e^x((m+1-x)e^x)^n
$$

可以多项式快速幂，实际上把幂次里面的 $e^x$ 提出来就可以线性算单项系数了。~~然而我脑抽了还是写了个多项式~~

[Submission #48492347 - AtCoder Grand Contest 035](https://atcoder.jp/contests/agc035/submissions/48492347)



---

