# [ARC162F] Montage

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc162/tasks/arc162_f

正整数 $ N,\ M $ が与えられます。各要素が $ 0 $ または $ 1 $ である $ N $ 行 $ M $ 列の行列 $ A $ は全部で $ 2^{NM} $ 個存在しますが、そのうち以下の条件を満たすものの個数を $ 998244353 $ で割ったあまりを求めてください。

- $ 1\ \leq\ a\ <\ c\ \leq\ N $ かつ $ 1\ \leq\ b\ <\ d\ \leq\ M $ を満たす全ての整数の組 $ (a,\ b,\ c,\ d) $ について、$ A_{a,\ b}\ \times\ A_{c,\ d}\ \leq\ A_{a,\ d}\ \times\ A_{c,\ b} $ が成り立つ。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 400 $
- 入力される数値は全て整数
 
### Sample Explanation 1

条件は $ A_{1,1}\ \times\ A_{2,2}\ \leq\ A_{1,2}\ \times\ A_{2,1} $ です。$ \begin{pmatrix}\ 1\ &amp;\ 0\ \\ 0\ &amp;\ 1\ \end{pmatrix},\ \begin{pmatrix}\ 1\ &amp;\ 1\ \\ 0\ &amp;\ 1\ \end{pmatrix},\ \begin{pmatrix}\ 1\ &amp;\ 0\ \\ 1\ &amp;\ 1\ \end{pmatrix} $ 以外の $ 13 $ 個が条件を満たします。

### Sample Explanation 2

$ 2^{NM} $ 個すべての行列が条件を満たすので、$ 2^{30} $ を $ 998244353 $ で割ったあまりである $ 75497471 $ を出力します。

## 样例 #1

### 输入

```
2 2```

### 输出

```
13```

## 样例 #2

### 输入

```
1 30```

### 输出

```
75497471```

## 样例 #3

### 输入

```
400 400```

### 输出

```
412670892```

# 题解

## 作者：EuphoricStar (赞：11)

题目限制可以被改写成，如果 $A_{a, b} = A_{c, d} = 1$，那么 $A_{a, d} = A_{c, b} = 1$。

考虑删去空白的行和列，那么对于每个 $A_{a, b} = A_{c, d} = 1$，矩形 $(a, b), (c, d)$ 中一定都是 $1$。

发现每一行只可能存在一个极长 $1$ 区间。并且对于第 $i$ 行的这个区间 $[l_i, r_i]$，有 $l_i \le l_{i - 1} \le r_i + 1, r_i \le r_{i - 1}$。也就是说最终的 $A$ 长这样：

![](https://img.atcoder.jp/arc162/F-fig12-NlQnCfwe.png)

这是一个很强的性质。已经可以 dp 了，设 $f_{i, j, k}$ 为考虑到第 $i$ 行，$l_i = j, r_i = k$ 的方案数。转移容易二维前缀和优化。

统计答案时，注意我们是在删掉空行和空列的基础上讨论的，因此 $f_{i, j, k}$ 对答案的贡献系数是在 $n \times m$ 的矩阵中选 $i$ 行，$m - j + 1$ 列的方案数即 $\binom{n}{i} \times \binom {m}{m - j + 1}$。

[code](https://atcoder.jp/contests/arc162/submissions/42788202)

---

## 作者：0x3F (赞：4)

讲一个不一样的 dp 思路。

首先，去掉所有空白行列以后，每行的 $1$ 构成一个区间，从上往下，区间的左右端点依次（非严格）递减，且相邻两行之间满足八连通。原因在其他题解里已经讲的很详细了。

我们看图：

![](https://img.atcoder.jp/arc162/F-fig12-NlQnCfwe.png)

我们发现所有 $1$ 构成的区域被红色，棕色两条从左下到右上的路径围成。

进一步的，我们发现红色在上方，棕色在下方，互不穿过，也没有公共边（可以有公共点）。

据此，令左下的格点为坐标原点，我们记 $dp_{i,j,k}$ 表示红色，棕色两条线被直线 $x+y=i$ 所截的两点分别为 $(j,i-j)$ 和 $(k,i-k)$ 对应的方案数。

可以进行如下转移：

1. 当 $j=k$ 时，$dp_{i,j,k}$ 转移到 $dp_{i+1,j,k+1}$。这是因为两条线已经处于公共点，只能向反方向移动，否则会交叉或有公共边。

2. 当 $j\ne k$ 时，$dp_{i,j,k}$ 转移到 $dp_{i+1,j,k}$，$dp_{i+1,j,k+1}$，$dp_{i+1,j+1,k}$，$dp_{i+1,j+1,k+1}$。这是因为两条线各有两种选择。

答案即为 $f(n,m)=dp_{n+m,m,m}$。

原问题的答案为 $\sum_{i=0}^{n}\sum_{j=0}^{m}\binom{n}{i}\binom{m}{j}f(i,j)$。

时间复杂度为 $O(n^3)$。空间复杂度经滚动数组可优化为 $O(n^2)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int p = 998244353;
const int _ = 810;
int n, m, c[_][_], dp[_][_], tmp[_][_], ans;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    c[0][0] = 1;
    for (int i = 0; i <= 800; i++) {
        for (int j = 0; j <= i; j++) {
            c[i+1][j] = (c[i+1][j] + c[i][j]) % p;
            c[i+1][j+1] = (c[i+1][j+1] + c[i][j]) % p;
        }
    }
    dp[0][0] = 1;
    for (int s = 0; s <= 800; s++) {
        for (int i = 0; i <= s; i++) {
            if (i <= n && s - i <= m) {
                ans = (ans + (long long) dp[i][i] * c[n][i] % p * c[m][s-i]) % p;
            }
        }
        for (int i = 0; i <= s; i++) {
            for (int j = i; j <= s; j++) {
                tmp[i][j] = dp[i][j];
                dp[i][j] = 0;
            }
        }
        for (int i = 0; i <= s; i++) {
            for (int j = i; j <= s; j++) {
                dp[i][j+1] = (dp[i][j+1] + tmp[i][j]) % p;
                if (i != j) {
                    dp[i][j] = (dp[i][j] + tmp[i][j]) % p;
                    dp[i+1][j+1] = (dp[i+1][j+1] + tmp[i][j]) % p;
                    dp[i+1][j] = (dp[i+1][j] + tmp[i][j]) % p;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：hjc452666 (赞：2)

# 一道看似可以 oeis 实则不能的 DP 题的 solution

## 题意

略。

第一眼看到是计数，发现限制条件相当齐整，并且 $n,m$ 是对称的，就想到打表找规律，但是即使借助了 ~~oeis 也不能找到~~ 在机房大佬的启发下开始想 DP。

### 朴素的 DP

考虑每次加入一行，那么一定是从前面所有行转移，如果一个位置为 $1$，那么它左上角所有的 $1$ 都会使得这一行对应列以及这一列对应行的位置上为 $1$。我们枚举一行中一的左端点、右端点，从前面每一行转移。可以想象将前面某一行直接投影下来，而中间的行则全为 $1$。发现右端点不能向右转移，而左端点可以向左转移：

```
0 1 1 0
1 1 0 0
```
是合法的，而：

```
0 1 1 0
0 1 1 1
```
显然是不合法的。

**设** $f_{i,l,r}$ 表示第 $i$ 行，左端点为 $l$，右端点为 $r$ 的方案数。

可以考虑每次先将之前行的 $l$、$r$ 的答案转移到该行的 $l$，$r$ 内，因为：

```
0 1 0 1 0 1 
0 1 1 1 0 1

```
以及：

```
0 1 0 1 0 1
0 1 0 0 0 1

```
显然是不行的，所以 $l$－$r$ 的方案在转移时是一一对应的，可以直接转移。

接着从已有方案出发，向左拓展。

但是显然右端点能够向左，但我们并不知道具体的方案。

然后发现右端点无所谓，反正所有方案都是对应的，我们不如记录 $1$ 的个数，也能够直接投影至对应左端点。

向左拓展，可以从右往左跑一遍 DP，选或不选，~~避免了组合数的转移~~。

钦定先进行**右**边个数的减少，再加入新的**左**端点，可以保证正确性。

枚举行、左端点、$1$ 的个数、之前行，再进行一轮枚举列、$1$ 的个数的 DP，总复杂度为 $\Theta(n^4)$。

### 优化

发现之前行的方案数投影到同一状态的可以简单前缀和，记 $sum_{j,s}$ 表示左端点为 $j$ 时有 $s$ 个 $1$ 的方案数，则优化到 $\Theta(n^3)$。

具体细节参考代码。

### 代码：

码风一般，不喜勿喷。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=405;
int n,m,mod=998244353,f[N][N],C[N][N],g[N],sum[N][N],ans;
int main()
{
    cin>>n>>m;
    sum[m][1]=1;//初值，全为0时可变为1
    for(int i=1;i<=n;++i)
    {
        memset(f,0,sizeof(f));//清空
        for(int s=0;s<=m;++s)g[s]=0;
        for(int mi=m;mi>=1;--mi)
        {
            for(int s=m-mi+1;s>=0;--s)
            {
                f[mi][s]=(f[mi][s+1]+sum[mi][s])%mod;//加入前缀和
            }
            for(int s=m-mi+1;s>=1;--s)
            {
                (sum[mi][s]+=f[mi][s]=(f[mi][s]+g[s-1])%mod)%=mod;
                (g[s]+=f[mi][s])%=mod;
            }
            (g[0]+=f[mi][0])%=mod;//0是没有选，要特殊处理
        }
    }
    for(int mi=m;mi>=1;--mi)
    {
        for(int s=m-mi+1;s>=0;--s)
        {
            (ans+=f[mi][s])%=mod;
        }
    }
    cout<<ans;
    return 0;
}
``````

---

## 作者：Arghariza (赞：1)

脑子被吃掉了。

手玩一下，容易转化题意为：

> 按行从上到下填 $0/1$ 矩阵，设第 $i$ 个**非空**行上是 $1$ 的位置的集合为 $S_i$，满足：
- 对于任意 $i>1$，令 $D=S_i\cup S_{i-1}$。
- 若 $D=\varnothing$，则 $S_i$ 中所有元素均比 $S_{i-1}$ 中任意元素小，即 $\max\limits_{i\in S_i}i<\min\limits_{i\in S_{i-1}}i$。
- 若 $D\neq\varnothing$，则 $S_i,S_{i-1},D$ 从小到大排序后，$D$ 为 $S_i$ 的后缀，为 $S_{i-1}$ 的前缀，即 $\max\limits_{i\in S_i\setminus D}i<\min\limits_{i\in D}i\le \max\limits_{i\in D}i<\min\limits_{i\in S_{i-1}\setminus D}i$。

现在这个限制是从右上角走到左下角，那不如先把行翻转一下，就变成了从左上角到右下角：

- $D=\varnothing$，$\min\limits_{i\in S_i}i>\max\limits_{i\in S_{i-1}}i$。
- $D\neq\varnothing$，$\min\limits_{i\in S_i\setminus D}i>\max\limits_{i\in D}i\ge \min\limits_{i\in D}i>\max\limits_{i\in S_{i-1}\setminus D}i$。

那我们直接把空行删掉，令 $f_{i,j,k}$ 表示考虑到第 $i$ 行，第 $i$ 行一共有 $j$ 个 $1$，最右边的 $1$ 的位置为 $k$ 的方案数。转移枚举新的最右边的 $1$ 的位置 $p$，$D$ 的大小 $s$，$S_{i+1}\setminus D$ 的大小 $l$，转移系数就是个组合数：

$$f_{i,j,k}\dbinom{p-k-1}{s-1}\to f_{i+1,l+s,p}$$

枚举非空的行数，答案就是：

$$\text{ans}=1+\sum\limits_{i=1}^{n}\dbinom{n}{i}\sum\limits_{j=1}^m\sum\limits_{k=1}^{m-j+1}f_{i,j,k}$$

直接做是 $O(n^6)$ 的。利用不同的 $l$ 转移相同可用前缀和优化至 $O(n^5)$。

然后我们发现把矩阵转置一下，将 $n,m$ 交换不影响答案，也就是说我们可以把空的列也拿出来。于是每个 $S_i$ 就是一段区间了，且 $S_i,S_{i+1}$ 要么相交不包含要么相邻，$S_{i+1}$ 在 $S_i$ 的右边。

将 $f_{i,j,k}$ 重新定义为 $S_1=[1,r_1],S_i=[j-k+1,j]$，满足以上限制的方案数。其实就是把前面的 $j,k$ 两维交换了一下。

那么答案变为：

$$\text{ans}=1+\sum\limits_{i=1}^n\sum\limits_{j=1}^m\dbinom{n}{i}\dbinom{m}{j}\sum\limits_{k=1}^jf_{i,j,k}$$

转移还是枚举 $S_{i+1}$ 的两个端点 $p,q$，满足 $j-k+1\le p\le j+1,\max(p,j)\le q\le m$:

$$f_{i,j,k}\to f_{i+1,q,q-p+1}$$

然而这还是 $O(n^5)$ 的。由于对于不同的 $p$ 贡献相同，设 $f'_{i,j,k}$ 为第三维差分后的 $f$ 数组，可用前缀和优化至 $O(n^4)$：

$$f_{i,j,k}\to f'_{i+1,q,q-\min(j+1,q)+1},-f_{i,j,k}\to f'_{i+1,q,q-j+k+1}$$

单独将 $q=j$ 的转移拎出来，这部分 $O(n^3)$：

$$f_{i,j,k}\to f'_{i+1,j,1},-f_{i,j,k}\to f'_{i+1,j,k+1}$$

剩下的是 $q\ge j+1$ 的转移：

$$f_{i,j,k}\to f'_{i+1,q,q-j},-f_{i,j,k}\to f'_{i+1,q,q-j+k+1}$$

这还是 $O(n^4)$ 的，但是我们观察到第二维和第三维的差为定值且与 $q$ 无关，所以令 $g_{i,j,k+1}=f'_{i,j,j-k}$：

$$f_{i,j,k}\to g_{i+1,q,j+1},-f_{i,j,k}\to g_{i+1,q,j-k}$$

注意到 $q\in [j+1,m]$，再对 $g$ 的第二维进行差分记作 $g'$，前缀和优化即可做到 $O(n^3)$：

$$f_{i,j,k}\to g'_{i+1,j+1,j+1},-f_{i,j,k}\to g'_{i+1,j+1,j-k}$$

最终时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$：

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define pb pop_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;


const int N = 405;
const int P = 998244353;

int n, m, ans, f[2][N][N], g[2][N][N], C[N][N];

int qpow(int p, int q) {
	int res = 1;
	for (; q; q >>= 1, p = 1ll * p * p % P)
		if (q & 1) res = 1ll * res * p % P;
	return res;
}

void init(int lim) {
	C[0][0] = 1;
	for (int i = 1; i <= lim; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= lim; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
	}
}

void solve() {
	cin >> n >> m, init(400);
	for (int i = 1; i <= m; i++) 
			f[1][i][i] = 1;
	for (int i = 1, t = 1; i <= n; i++, t ^= 1) {
		memset(f[t ^ 1], 0, sizeof(f[t ^ 1]));
		memset(g[t ^ 1], 0, sizeof(g[t ^ 1]));
		for (int j = 1; j <= m; j++) {
			for (int k = 1; k <= j; k++)
				(g[t][j][k] += g[t][j - 1][k]) %= P;
			for (int k = 1; k <= j; k++)
				(f[t][j][k] += g[t][j][j - k + 1]) %= P;
			for (int k = 1; k <= j; k++)
				(f[t][j][k] += f[t][j][k - 1]) %= P;
			for (int k = 1; k <= j; k++) {
				(f[t ^ 1][j][1] += f[t][j][k]) %= P;
				(f[t ^ 1][j][k + 1] += P - f[t][j][k]) %= P;
				(g[t ^ 1][j + 1][j + 1] += f[t][j][k]) %= P;
				(g[t ^ 1][j + 1][j - k] += P - f[t][j][k]) %= P;
			}
			int res = 0;
			for (int k = 1; k <= j; k++) 
				(res += f[t][j][k]) %= P;
			(ans += 1ll * C[n][i] * C[m][j] % P * res % P) %= P;
		}
	}
	cout << (ans + 1) % P << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：gdf_yhm (赞：1)

[arc162f](https://www.luogu.com.cn/problem/AT_arc162_f)

### 思路

$a_{x1,y2}\times a_{x2,y2}\leq a_{x1,y2}\times a_{x2,y1}$ 改为所有 $a_{x1,y1}=a_{x2,y2}=1$，都有 $a_{x1,y2}=a_{x2,y1}=1$。

观察发现，第 $i$ 行 $a_{i,j_1}=\ldots =a_{i,j_{num}}=1,(j_1<\ldots <j_{num})$，第 $ii,(ii>i)$ 行能取 $1$ 的位置是 $[1,j_1-1]$ 和 $j$ 的一个前缀。形如：

```
000010110
000010100
010110100
000000000
100000000
```



但可以空一些行和列，不方便，考虑将所有有 $1$ 的行和列压起来。设 $dp_{i,j,k}$ 表示前 $i$ 行，有 $j$ 个列有过 $1$，上一行有 $k$ 个 $1$，强制连续选。首先可以取一个前缀，$dp'_{i,j,k}=\sum_{l=k}^j dp_{i-1,j,l}$，后缀和维护。其次可以向前在  $[1,j_1-1]$  任意取，但强制连续选，枚举选 $l$ 个，$dp_{i,j,k}=\sum_{l=0}^k dp'_{i,j-l,k-l}$，维护一个斜线的前缀和。

计算答案，对于每个 $dp_{i,j,k}$，$n$ 行选 $i$ 行，$m$ 列选 $j$ 列，其他放 $0$，$ans=\sum \binom{n}{i}\times \binom{m}{j}\times dp_{i,j,k}$。再加上全取 $0$ 的情况。

注意取模优化和枚举时 $\frac{1}{2}$ 的常数。

### code

```cpp

	for(int i=1;i<=m;i++)dp[i][i]=1,ans=add(ans,C(m,i)*C(n,1)%mod);
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=j;~k;k--)f[j][k]=add(f[j][k+1],dp[j][k]);
		}
		for(int j=1;j<=m;j++){
			for(int k=1;k<=j;k++)f[j][k]=add(f[j][k],f[j-1][k-1]);
		}
		for(int j=1;j<=m;j++){
			for(int k=1;k<=j;k++){
				dp[j][k]=f[j][k];
			}
		}
		for(int j=1;j<=m;j++){
			for(int k=1;k<=j;k++){
				ans=add(ans,C(m,j)*C(n,i)%mod*dp[j][k]%mod);
			}
		}
	}
	printf("%lld\n",ans+1);
```


---

## 作者：Vidoliga (赞：1)

模拟赛题。

3100* 感觉虚高，这题应该很好想，至少除去我往后面想其他题的时间，这题也就想了大概 1h。（？）

首先题目条件可以看成不存在：

$$\begin{matrix}x&1\\1&y\end{matrix}$$

其中 $x \&y=0$。

考虑从下往上填一行。

考虑若填出形如：

$$1\dots0\dots$$

不难发现这个 $0$ 对应的行应当全部填 $0$ 否则不满足限制。

那么就简单了，考虑找到最左侧填的 $1$，将这个 $1$ 右侧 $0$ 删除后，剩下的一定形如：

$$00000\dots11111\dots$$

那么考虑一个暴力 dp，$f_{i,j,x}$ 表示填到 $x$ 行，剩下 $i$ 个 $0$，$j$ 个 $1$。

枚举删的 $0/1$ 最左的 $1$ 位置，暴力转移复杂度 $O(n^6)$。

考虑一下这个可以怎么转化：

首先将对于整个矩阵一列/行全是 $0$的直接枚举除去，考虑删去这些行列剩下的举证。

剩下的行列一定至少存在 $1$ 个 $1$，观察转移，发现若之前的行 $1$ 的位置为区间 $[l,r]$，考虑其可以转移到的区间为 $[x, \geq r],x\in[l,r+1]$。

设计状态 $f_{i,j,k}$ 表示考虑到 $i$ 行 $j$ 列，最后一列有 $k$ 个区间包含。

转移：

$$f_{i,j,k} \leftarrow f_{i-1,j,k-1}$$

$$f_{i,j,k} \leftarrow f_{i-1,j-1,\geq k}$$

$$f_{i,j,1} \leftarrow f_{i-1,j-1,k}$$

设 $F_{i,j}=\sum\limits_{k\geq 1}f_{i,j,k}$

最终答案就是 $\sum\limits_{i=0}^{m}\sum\limits_{j=0}^{n-1}\binom{m}{i}\binom{n}{j}F_{n-j,m-i}$。

复杂度 $O(n^3)$。

```cpp
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("Ofast","unroll-loops","inline")
#include<bits/stdc++.h>
#define ll long long
//#define int ll
using namespace std;
const int N=1e3+20,M=1e6+20;
const int mod=998244353;
int fac[N],ifac[N],inv[N];
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=1ll*res*a%mod;
		a=1ll*a*a%mod;b>>=1;
	}return res;
}
inline int C(int n,int m){
	if(n<0||m<0||n<m) return 0;
	return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod; 
}
int f[2][N][N],g[2][N][N],F[N][N],nw,n,m;
inline void Add(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void calcg(int j,int k){
	g[nw][j][k]=(g[nw][j][k+1]+f[nw][j][k])%mod;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	fac[0]=inv[0]=ifac[0]=ifac[1]=1;for(int i=1;i<N;i++) fac[i]=1ll*i*fac[i-1]%mod;
	ifac[N-1]=qpow(fac[N-1],mod-2);for(int i=N-1;i;i--) ifac[i-1]=1ll*i*ifac[i]%mod;
	for(int i=N-1;i;i--) inv[i]=1ll*ifac[i]*fac[i-1]%mod;
	for(int j=1;j<=m;j++) f[nw][j][1]=1,g[nw][j][1]=1,F[1][j]=1;
	nw^=1;
	for(int i=2;i<=n;i++,nw^=1){
		memset(f[nw],0,sizeof(f[nw]));
		for(int j=1;j<=m;j++){
			for(int k=i;k;k--){
				Add(f[nw][j][k],f[nw^1][j][k-1]);
				Add(f[nw][j][k],g[nw][j-1][k]);
				if(k==1) Add(f[nw][j][k],g[nw^1][j-1][1]);
				calcg(j,k);
			}
			F[i][j]=g[nw][j][1];
		}
	}
	int ans=0;nw^=1;
	for(int x=0;x<=m;x++,nw^=1){
		int t=m-x;
		int res=0;
		for(int i=0;i<n;i++) Add(res,1ll*C(n,i)*F[n-i][t]%mod);
		if(x==m) res++; 
		Add(ans,1ll*C(m,x)*res%mod);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Cindy_Li (赞：0)

看起来很神秘，实则是找规律 + dp。

提供一个跟主流做法略有不同的 dp 思路。

容易发现，条件等价于：
> 若左上右下都是 `1`，则右上左下也是 `1`。

从下到上考虑 `1` 的分布，形如若干个从左下到右上排布的上阶梯。

```
0 0 0 0 0 0 1
0 0 0 1 0 1 1
0 0 1 1 0 1 0
1 0 1 0 0 0 0
```

于是设 $f(i,j,k)$ 表示第 $i$ 行，最右边的 `1` 是在第 $j$ 列，一共有 $k$ 个 `1` 的方案数。

转移时，先考虑下面第一行有 `1` 的，枚举这个阶梯内的 `1` 的数量；然后再考虑在右边增加 `1`，形成新的阶梯。

$$f(i,j,k) \leftarrow f(a,j,c),\forall i<a,k\le c$$

$$f(i,j,k) \leftarrow f(i,b,k-1),\forall b<j$$

有一些边界的细节，需要前缀和优化。

三维空间开不下，需要滚动数组优化。

```c++
namespace zj{
    int f[N][N];
    int sm1[N][N],sm2[N],sm3[N][N];
    inline void solve(){
        getC();
        // 初值
        f[0][0]=sm1[0][0]=1;
        rep(j,1,m) {
            rep(k,1,j) f[j][k]=C[j-1][k-1],sm1[j][k]=f[j][k];
            per(k,j,0) sm1[j][k]=pls(sm1[j][k],sm1[j][k+1]);
        }
        per(i,n-1,1){
            // 从下面的阶梯转移
            memset(f,0,sizeof(f));
            rep(j,1,m) rep(k,0,j) {
                f[j][k]=pls(f[j][k],sm1[j][max(k,1)]);
            }
            // 向右拓展
            memset(sm2,0,sizeof(sm2));
            rep(j,1,m) {
                rep(k,1,j) {
                    f[j][k]=pls(f[j][k],sm2[k-1]);
                }
                rep(k,0,j) sm2[k]=pls(sm2[k],f[j][k]);
            }
            // 下面都是 0，从第 i 行开始
            f[0][0]=1;
            rep(j,1,m) rep(k,1,j) f[j][k]=pls(f[j][k],C[j-1][k-1]);
            memset(sm3,0,sizeof(sm3));
            rep(j,1,m) {
                rep(k,0,j) sm3[j][k]=pls(sm3[j][k],f[j][k]);
                per(k,j,0) sm3[j][k]=pls(sm3[j][k],sm3[j][k+1]);
            }
            rep(j,1,m) rep(k,0,j) sm1[j][k]=pls(sm1[j][k],sm3[j][k]);
        }
        int ans=1;
        rep(j,1,m) rep(k,0,j) ans=pls(ans,f[j][k]);
        printf("%d\n",ans);
    }
}
```

---

## 作者：xxxxxzy (赞：0)

题目的限制可以改写成，如果 $A_{a,b} = A_{c,d} = 1$，那么 $A_{a,d}=A_{b,c}=1$。

删去空白的行和列，那么一定会成为一个矩形，且每行只有一段连续的 $1$，并且上一段的左端点和下一段的右端点至少有公共交点，并且上一段的右端点小于这一段的右端点。

（借一下图）

![](https://img.atcoder.jp/arc162/F-fig12-NlQnCfwe.png)

设 $f_{i,l,r}$ 为从下往上 dp，dp 到第 $i$ 行，这一行的 $[l,r]$ 被染成 $1$。

这个 dp 是简单的，注意 dp 完后，需要把删除的行再插入进去。

另外，这个 dp 会漏掉全是 $0$ 的情况，所以请给答案 $+1$。

Tips：$2^{31}$ 次方为 $998244353$ 的 $2$ 倍多，请开 ll。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<ll, ll>
#define mp make_pair
#define pb push_back
#define ld lower_bound
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define drep(i, a, b) for (int i = (a); i >= (b); i--)
#define ud upper_bound
#define mem(s, k) memset(s, k, sizeof(s))
#define fi first
#define se second
#define ull unsigned long long
#define vec vector <int>
#define fv inline void
#define fn inline static
using u16 = unsigned short; using u32 = unsigned; using u64 = unsigned ll; using u128 = __uint128_t;
using i16 = short; using i32 = ll; using i64 = ll; using i128 = __int128_t;
using namespace std;
const i32 N = 405, mod = 998244353;
i32 fac[N], ifac[N]; 
fn i32 qkpow(i32 a, i32 b) {
  i32 ans = 1;
  for (; b; b >>= 1) {
    if (b & 1) ans = 1ll * ans * a % mod;
    a = 1ll * a * a % mod;
  }
  return ans;
}
fv init() {
  rep (i, fac[0] = ifac[0] = 1, N - 5) ifac[i] = qkpow(fac[i] = 1ll * fac[i - 1] * i % mod, mod - 2);
}
fn i32 C(i32 n, i32 m) {
  return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
i32 n, m, ans, f[N][N][N], s[N][N][N];
fn i32 qry(i32 i, i32 a, i32 c, i32 b, i32 d) {
  return ((s[i][c][d] - s[i][c][b - 1] - s[i][a - 1][d] + s[i][a - 1][b - 1]) % mod + mod) % mod;
}
int main() {
  cin >> n >> m;
  init();
  rep (i, 1, m) f[1][1][i] = 1;
  rep (i, 2, n) {
    rep (j, 1, m) rep (k, 1, m) s[i][j][k] = ((s[i][j - 1][k] + s[i][j][k - 1] - s[i][j - 1][k - 1] + f[i - 1][j][k]) % mod + mod) % mod;
    rep (j, 1, m) rep (k, j, m) f[i][j][k] = qry(i, 1, j, j - 1, k) % mod;
  }
  rep (i, 1, n) {
    rep (j, 1, m) {
      rep (k, j, m) {
//        cout << i << " " << j << " " << k << " " << f[i][j][k] << "\n"; 
        ans = (ans + 1ll * f[i][j][k] * C(n, i) % mod * C(m, k) % mod) % mod;
      }
    }
  }
  cout << (ans + 1) % mod;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc162_f)

**题目大意**

> 对于一个 $n\times m$ 的 $01$ 矩阵 $A$，其合法当且仅当：
>
> - $\forall 1\le i<j\le n,1\le x<y\le m$ 有 $A_{i,x}\times A_{j,y}\le A_{i,y}\times A_{j,x}$。
>
> 求有多少合法矩阵。
>
> 数据范围：$n,m\le 400$。

**思路分析**

显然全 $1$ 矩阵合法，考虑把某个位置 $(i,j)$ 变成 $0$。

那么对于所有 $x\ge i,y\le j$，$A_{x,j}\times A_{i,y}=0$，那么 $A_{i+1,j}\sim A_{n,j}$ 和 $A_{i,1}\sim A_{i,j-1}$，至少有一个部分全是 $0$（即左侧射线和下方射线）。

同理 $(i,j)$ 的上方射线和右侧射线至少有一个全是 $0$。

如果把 $(i,j)$ 的上方射线和下方射线全部变成 $0$，直接变成了 $n\times m-1$ 的子问题，这种操作是平凡的。

那么我们只要考虑所有 $i\times j$ 的非平凡合法矩阵，乘以 $\binom ni\times\binom mj$ 作为系数即可。

对于一个非平凡的矩阵，不妨假设清零的是上方射线和左侧射线。

由定义，对于 $(i,j)$ 上方的每个点，其下方至少有一个 $1$，那么他们的左侧射线必须全是 $0$，那么 $x\le i,y\le j$ 的所有 $A_{x,y}=0$。

因此每个 $0$ 会导致其左上方或右下方全部被清 $0$。

所以每行的 $1$ 必须连续，设第 $i$ 行区间为 $[l_i,r_i]$，显然 $l_i\le l_{i-1},r_i\le r_{i-1}$。

由于不能有全零的行或列，那么 $r_1=m,l_n=1$，且 $r_i\ge l_{i-1}-1$。

设 $f_{i,l,r}$ 为第 $i$ 行区间为 $[l,r]$ 的方案数，显然转移是对一个矩形区域 $+f_{i,l,r}$，二维前缀和优化即可。

时间复杂度 $\mathcal O(nm^2)$。

**代码呈现**

代码里是倒着考虑每个区间的（$l_{i-1}\le l_{i},r_{i-1}\le r_i$）。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=405,MOD=998244353;
ll C[MAXN][MAXN],f[MAXN][MAXN],g[MAXN][MAXN],ans=1;
signed main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<MAXN;++i) for(int j=C[i][0]=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
	for(int i=1;i<=n;++i) f[1][i]=1,ans=(ans+m*C[n][i])%MOD;
	for(int k=2;k<=m;++k) {
		memset(g,0,sizeof(g));
		for(int i=1;i<=n;++i) for(int j=i;j<=n;++j) if(f[i][j]) {
			g[i][j]=(g[i][j]+f[i][j])%MOD;
			if(j+2<=n) g[j+2][j]=(g[j+2][j]+MOD-f[i][j])%MOD;
		}
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) {
			g[i][j]=(g[i][j]+g[i-1][j]+g[i][j-1]+MOD-g[i-1][j-1])%MOD;
			if(j>=i) f[i][j]=g[i][j],ans=(ans+C[m][k]*C[n][j]%MOD*f[i][j])%MOD;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Inui_Sana (赞：0)

%赛场切了！

矩阵是不太好处理的，所以考虑从一行去推下一行。

设上一行选择了 $p_1,p_2,\cdots,p_k$ 这几个横坐标的位置为 $1$，分情况讨论一下这一行选择的 $x$ 位置。

（下列结合自己画图理解）

- $x\ge p_1$。

首先发现如果选择一个 $x\not\in p$，则一定不满足条件。

然后也可以发现，设这一行的选择的 $x\ge p_1$ 的部分为 $q$，则 $q$ 是 $p$ 的一个前缀。

但是又发现，如果有一行完全不选，则这一行状态可以视为继承上一行的。这个要特判一下。

- $x<p_1$。

结合前面，发现可以任选。

于是我们可以开始 dp 了。

设 $dp_{i,j,k}$ 表示枚举到第 $i$ 行，这一行选了 $j$ 个 $1$，最左侧的 $1$ 左边还有 $k$ 个 $0$ 的方案数。

首先转移 $x\ge p_1$ 的情况。枚举转移到长度为 $l$ 的前缀，直接转移即可。

**然后在上一步的基础上转移 $x<p_1$ 的**。枚举选 $a$ 个，最左边一个左边有 $l$ 个 $0$，另用一个数组转移。最后全部加到一起。

于是能写出如下 $O(n^5)$ 的代码，$n,m$ 同阶：

```cpp
fac[0]=1;
rep(i,1,m)fac[i]=1ll*fac[i-1]*i%mod;
ifac[m]=qpow(fac[m],mod-2);
drep(i,m-1,0)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
rep(i,1,m)rep(j,0,m)dp[1][i][j]=binom(m-j-1,i-1);
dp[1][0][m]=1;
rep(i,2,n){
	mems(f,0);
	rep(j,0,m){
		rep(k,0,m){
			rep(l,0,j)dp[i][l][k]=Mod(dp[i][l][k],dp[i-1][j][k]);
			if(j)f[j][k]=Mod(f[j][k],dp[i-1][j][k]),f[0][k]=Mod(f[0][k],mod-dp[i-1][j][k]);
		}
	}
	rep(j,0,m){
		rep(k,0,m){
			rep(l,1,k)rep(p,0,k-l)f[j+p+1][l-1]=Mod(f[j+p+1][l-1],1ll*dp[i][j][k]*binom(k-l,p)%mod);
		}
	}
	rep(j,0,m)rep(k,0,m)dp[i][j][k]=Mod(dp[i][j][k],f[j][k]);
}
int ans=0;
rep(i,0,m)rep(j,0,m)ans=Mod(ans,dp[n][i][j]);
printf("%d\n",ans);
```

然后开始优化！

发现我们的状态已经足够优秀了。从转移入手。

瓶颈在 $x<p_1$ 的部分。然后发现这一部分其实没必要枚举两个值，可以再用一次 dp 去转移，每次枚举左边下一个点选什么，以此转移。变成 $O(n^4)$。

```cpp
rep(i,2,n){
	mems(f,0),mems(g,0);
	rep(j,0,m){
		rep(k,0,m){
			rep(l,0,j)f[l][k]=Mod(f[l][k],dp[i-1][j][k]);
			if(j)dp[i][j][k]=Mod(dp[i][j][k],dp[i-1][j][k]),dp[i][0][k]=Mod(dp[i][0][k],mod-dp[i-1][j][k]);
		}
	}
	rep(j,0,m){
		drep(k,m,0){
			rep(l,1,k)f[j+1][l-1]=Mod(f[j+1][l-1],f[j][k]);
		}
	}
	rep(j,0,m)rep(k,0,m)dp[i][j][k]=Mod(dp[i][j][k],f[j][k]);
}
```

然后继续优化！

发现上面的 $f_{l,k}$ 的转移是从 $dp_{i,[l,m],k}$ 来的，于是可以变一下枚举顺序然后前缀和，复杂度少一个 $n$。然后下面也可以一样处理。

于是变成了 $O(n^3)$：

```cpp
rep(i,2,n){
	mems(f,0);
	rep(k,0,m){
		s[0]=dp[i-1][0][k];
		rep(j,1,m)s[j]=Mod(s[j-1],dp[i-1][j][k]);
		rep(l,0,m)f[l][k]=Mod(f[l][k],Mod(s[m],mod-s[l-1]));
	}
	rep(j,0,m){
		rep(k,0,m){
			if(j)dp[i][j][k]=Mod(dp[i][j][k],dp[i-1][j][k]),dp[i][0][k]=Mod(dp[i][0][k],mod-dp[i-1][j][k]);
		}
	}
	rep(j,0,m){
		s[0]=0;
		rep(k,1,m)s[k]=Mod(s[k-1],f[j][k]);
		drep(l,m,1){
			f[j+1][l-1]=Mod(f[j+1][l-1],Mod(s[m],mod-s[l-1]));
		}
	}
	rep(j,0,m)rep(k,0,m)dp[i][j][k]=Mod(dp[i][j][k],f[j][k]);
}
```

然后可能被卡空间，使滚动，空间 $O(n^2)$。可以通过。

code：

```cpp
int n,m,dp[2][N][N],f[N][N],s[N];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
void solve3(){
	dp[0][0][m]=1;
	rep(i,1,n){
		int p=i&1;
		mems(f,0),mems(dp[p],0);
		rep(k,0,m){
			s[0]=dp[p^1][0][k];
			rep(j,1,m)s[j]=Mod(s[j-1],dp[p^1][j][k]);
			rep(l,0,m)f[l][k]=Mod(f[l][k],Mod(s[m],mod-s[l-1]));
		}
		rep(j,0,m){
			rep(k,0,m){
				if(j)dp[p][j][k]=Mod(dp[p][j][k],dp[p^1][j][k]),dp[p][0][k]=Mod(dp[p][0][k],mod-dp[p^1][j][k]);
			}
		}
		rep(j,0,m){
			s[0]=0;
			rep(k,1,m)s[k]=Mod(s[k-1],f[j][k]);
			drep(l,m,1)f[j+1][l-1]=Mod(f[j+1][l-1],Mod(s[m],mod-s[l-1]));
		}
		rep(j,0,m)rep(k,0,m)dp[p][j][k]=Mod(dp[p][j][k],f[j][k]);
	}
	int ans=0;
	rep(i,0,m)rep(j,0,m)ans=Mod(ans,dp[n&1][i][j]);
	printf("%d\n",ans);
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	solve3();
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

横向对比，发现这个方法不需要组合数，所以事实上是可以做任意模数的！:)

---

