# [AGC039E] Pairing Points

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc039/tasks/agc039_e

円周上の一般の位置に相異なる $ 2N $ 個の点が並んでおり、反時計回りに順に $ 1,\dots,2N $ の番号が付けられています。 ただし、ここでいう一般の位置とは、どの相異なる $ 6 $ 点 $ U,\ V,\ W,\ X,\ Y,\ Z $ についても、線分 $ UV,\ WX,\ YZ $ が一点で交わらないことをいいます。 また、 $ 2N\ \times\ 2N $ の行列 $ A $ が与えられます。

円周上の $ 2N $ 個の点を $ N $ 個のペアに分ける方法であって、以下の条件をみたすようなものの個数を求めてください。

- すべてのペアに対してそのペアの $ 2 $ つの点を結ぶ赤い線分をひいたとき、赤い部分が "木" になっている。
- すべてのペアについて、その端点を点 $ P,\ Q $ としたとき、 $ A_{P,Q}\ =\ A_{Q,P}\ =\ 1 $ である。

より厳密には、赤い部分が "木" になっているとは、赤い部分全体が連結かつ無閉路になっていることを指します。

例えば、下図において、

- 左上の例は条件を満たします。
- 右上の例は、赤い部分に閉路が存在し、条件を満たしません。
- 左下の例は、赤い部分が非連結であり、条件を満たしません。
- 右下の例は、ペアに属さない頂点やペアに複数回含まれる頂点が存在し、条件を満たしません。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc039_e/c0b743c8aac73d041d43810449124e729c319bc8.png)図: 条件を満たす例 (左上) とそうでない例 (それ以外)

## 说明/提示

### ノート

答えは、$ 2N $ 個の点が一般の位置にある限り、その具体的な位置関係には依存しないことが証明できます。

### 制約

- $ 1\ \leq\ N\ \leq\ 20 $
- $ A_{i,j} $ は `0` または `1` である
- $ A_{i,i} $ は `0` である
- $ A_{i,j}=A_{j,i} $
- $ N $ は整数である

### Sample Explanation 1

$ ((1,4),(2,6),(3,5)) $, $ ((1,3),(2,5),(4,6)) $, $ ((1,5),(2,4),(3,6)) $ の $ 3 $ つの分け方が条件を満たします。

## 样例 #1

### 输入

```
3
011111
101111
110111
111011
111101
111110```

### 输出

```
3```

## 样例 #2

### 输入

```
4
01111100
10011111
10011100
11101111
11110111
11111011
01011101
01011110```

### 输出

```
6```

## 样例 #3

### 输入

```
8
0111101111111111
1011101111111111
1101101111011101
1110111111111111
1111011111110111
0001101111111111
1111110111011111
1111111011111111
1111111101111111
1111111110111111
1101110111011111
1111111111101111
1111011111110111
1111111111111011
1101111111111101
1111111111111110```

### 输出

```
4762```

# 题解

## 作者：小粉兔 (赞：17)

令 $n = 2 N$，枚举第 $n$ 个点和哪个点连了，假设为 $k$，即：

![](https://cdn.luogu.com.cn/upload/image_hosting/f6yslrpq.png)

就分成了 $1 \sim (k - 1)$ 和 $(k + 1) \sim (n - 1)$ 两段。

直接考虑如果是区间 $[i, j]$，且这区间中的一点 $k$ 与区间外的一点连线了，即：

![](https://cdn.luogu.com.cn/upload/image_hosting/dems968y.png)

如果 $i < j$，那么被 $k$ 分割的左右两边必然要通过至少一条线与 $(? \leftrightarrow k)$ 连接起来

但是又不能交叉，如果交叉就形成环了，所以取最上方的一条线 $(x \leftrightarrow y)$。

所谓最上方，形式化地说就是 $x$ 最靠近 $i$，$y$ 最靠近 $j$。

那么，$x, y$ 在两边必然就会有各自的“管辖范围”。  
（你可以理解成，从 $(? \leftrightarrow k)$ 和 $(x \leftrightarrow y)$ 的交点出发向 $x$ 或 $y$ 方向走，能遍历到的区域，它和其它区域不相交）

假设这个范围分别为 $[i, p]$ 和 $[q, j]$。

那么如果我们枚举 $i, j, k, x, y, p, q$（满足 $i \le x \le p < k < q \le y \le j$）：

就可以转化成三个子问题 $[i, p](x)$ 和 $[p + 1, q - 1](k)$ 和 $[q, j](y)$。

可以在 $\mathcal O (n^7)$ 的复杂度内解决此问题，因为常数大约是 $1 / 7! = 1 / 5040$，所以其实是可以过的。

---

不过可以继续优化，可以发现 $[i, p]$ 和 $[q, j]$ 是和 $k$ 独立的，也就是如果 $[i, j]$ 固定，$k$ 的位置不影响 $p, q$ 的选择。

那么我们考虑先枚举 $p, q$，得到 $[i, p] \circ [q, j]$ 这个子问题，再在子问题里枚举 $x, y$。

则处理所有 $[i, q] \circ [q, j]$ 就可以做到 $\mathcal O (n^6)$ 的复杂度（枚举 $6$ 个变量）。

外层的 $[i, j](k)$ 就可以只枚举 $p, q$ 进行转移，这部分复杂度为 $\mathcal O (n^5)$。

总时间复杂度为 $\mathcal O (n^6)$，同样带了一个 $1 / 6! = 1 / 720$ 的常数。

---

不过可以继续优化，现在复杂度瓶颈是在 $[i, p] \circ [q, j]$ 这里，需要枚举 $x, y$ 才能转移。

如果只枚举一个 $y$ 呢？

那就需要求 $[i, p]$ 区间中的，从 $y > p$ 连进来一条边的方案数，用记号 $[i, p]\{y\}$ 表示。

当然还有本来就要求的 $[q, j](y)$，这个是旧的东西了。

那么考虑计算 $[i, p]\{y\}$，这时就可以枚举具体是和哪个 $i \le x \le p$ 连边，然后直接加上 $[i, p](x)$ 即可。

所以处理所有 $[i, p]\{y\}$ 的复杂度为 $\mathcal O (n^4)$，而处理所有 $[i, p] \circ [q, j]$ 的复杂度降为 $\mathcal O (n^5)$。

总时间复杂度为 $\mathcal O (n^5)$，带了一个 $1 / 5! = 1 / 120$ 的常数，[评测链接](https://atcoder.jp/contests/agc039/submissions/10388182)。

---

## 作者：关怀他人 (赞：15)

#### Solution
下面令$n=2N$，首先把环从$n$那里断开变成一条链，然后假设与$1$配对的点是$i$。

那么我们接下来就要对$[2,i)\cup (i,n]$之间的点继续配对，由于要构成一颗树，这就相当于在$[2,i)$中选一些点$p_1<p_2<\cdots <p_x$，在$(i,n]$中选一些点$q_1>q_2>\cdots >q_x$，令$p_i$和$q_i$连线，对于剩下那些没被选到的点，在它们之间连线，求合法方案数。

考虑dp，设$f_{l,i,r}$表示**考虑到$[l,r]$这段区间中的点，$i$和向区间外部连线，其余点的连线要和$i$的连线连通的方案数**。最后求的即为$\sum f_{2,i,n}$。

考虑如何转移，枚举$p_1$和$q_1$，记为$j$和$k$，然后先考虑$(j,i)$之间的点，它们连出的边要么和$j$连出的这条边相连，要么和$i$连出的这条边相连，且一定存在一个分界点$p$，满足$p$和之前的都与$j$连出的边相连，$p+1$和之后的都与$i$连出的边相连，那么可以递归为一个$[l,j)\cup (j,p]$的子问题

同理定义(i,k)的分界点q，那么这也可以递归为一个$[q,k)∪(k,r]$的子问题。而中间那部分就是一个$[p+1,i)∪(i,q−1]$的子问题

所以易得转移方程$f_{l,i,r}\leftarrow \sum f_{p+1,i,q-1}f_{l,j,p}f_{q,k,r}[a_{j,k}=1]$

时间复杂度$\mathcal O(n^7)$，由于常数极小所以能通过。

下面考虑优化，先枚举$p,q$，然后枚举$i$，那么$f_{l,i,r}+=f_{p+1,i,q-1}\sum f_{l,j,p}f_{q,k,r}[a_{j,k}=1]$，不难发现后面和$i$无关，设后面的部分为$s$，考虑如何快速计算$s$。

令$g_{l,k,p}=\sum f_{l,j,p}[a_{j,k}=1]$，那么$s=\sum g_{l,k,p}f_{q,k,r}$，转移$f$的时候顺便转移一下$g$即可，时间复杂度为$\mathcal O(n^5)$
#### Code
```cpp
int n;
ll f[MAXN][MAXN][MAXN],g[MAXN][MAXN][MAXN];
char s[MAXN][MAXN];

int main(){
    scanf("%d",&n); n <<= 1;
    for(int i = 1;i <= n;i++) scanf("%s",s[i] + 1);
    for(int i = 2;i <= n;i++){
        f[i][i][i] = 1;
        for(int j = i + 1;j <= n;j++) g[i][j][i] = (s[i][j] == '1');
    }
    for(int len = 3;len < n;len += 2){
        for(int l = 2;l + len - 1 <= n;l++){
            int r = l + len - 1;
            for(int p = l;p <= r;p += 2){
                for(int q = r;q > p;q -= 2){
                    ll sum = 0;
                    for(int k = q;k <= r;k++) sum += g[l][k][p] * f[q][k][r];
                    for(int i = p + 1;i <= q;i++) f[l][i][r] += sum * f[p + 1][i][q - 1];
                }
            }
            for(int i = l;i <= r;i++){
                for(int j = i + 1;j <= n;j++){
                    if(s[i][j] == '1')
                        g[l][j][r] += f[l][i][r];
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 2;i <= n;i++){
        if(s[1][i] == '1')
            ans += f[2][i][n];
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：wrpwrp (赞：6)

考虑$1$号点向外连出一条边之后， 整个圆被分成两个部分， 每个部分肯定是内部连边然后一个点连一条边出来跨越一号点连出的那一条线。考虑对这种形状的部分进行$dp$。

设$f(i, j, k)$表示$[i, j]$这个区间内部匹配， $k$点向外连接的方案数， 

$g(i,j,k)$表示外面一点$k$连接到区间$[i, j]$内， 区间内其他点两两匹配的方案数目。

考虑转移， 可以枚举左边和右边的小块， 然后连接， 再枚举中间的每一个点作为连出去的点转移， 因为只有左右两边连起来， 中间连出去才会是一棵树， 所以连出去的点除了一个点的情况， 其他时候都不该在区间边上。

比如枚举了当前要处理的块的左右端点$j, k$。

设$s = \sum g(j, l, t) * f(r, k, t)$,表示两边的连通块连起来的总方案数目。

$l, r$是枚举的中间的那个区间的左右端点。

然后枚举中间区间的每一个点作为连出的点， 有：

$f(j, k, t) = \sum f(l + 1, r - 1, t)$

最后更新一下$g$, 枚举在外面的点和在里面的点更新即可。

```cpp
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

#define R register
#define LL long long
const int N = 50;

inline int read() {
	int x = 0, f = 1; char a = getchar();
	for(; a > '9' || a < '0'; a = getchar()) if(a == '-') f = -1;
	for(; a >= '0' && a <= '9'; a = getchar()) x = x * 10 + a - '0';
	return x * f;
}
char s[N][N];
LL f[N][N][N], g[N][N][N];

int main() {
	#ifdef IN
	freopen("a.in", "r", stdin);
	//freopen(".out", "w", stdout);
	#endif
	int n = read(); n <<= 1;
	for(R int i = 1; i <= n; i ++) 
		scanf("%s", s[i] + 1);
	for(R int i = 1; i < n; i ++) {
		f[i][i][i] = 1;
		for(R int j = i + 1; j <= n; j ++)
			if(s[i][j] == '1') 
				g[i][i][j] = 1;
	}
	for(R int len = 3; len < n; len += 2) {
		for(R int j = 1; j + len <= n; j ++) {
			int k = len + j - 1;
			for(R int l = j; l <= k; l += 2)
				for(R int r = k; r >  l; r -= 2) {
					LL s = 0;
					for(R int t = r; t <= k; t ++)
						s += g[j][l][t] * f[r][k][t];
					for(R int t = l + 1 ; t < r; t ++)
						f[j][k][t] += f[l + 1][r - 1][t] * s;
				}
			for(R int t1 = j + 1; t1 < k; t1 ++)
				for(R int t2 = k + 1; t2 < n; t2 ++)
					if(s[t1][t2] == '1')
						g[j][k][t2] += f[j][k][t1];
		}
	}
	LL ans = 0;
	for(R int i = 1; i < n; i ++)
		if(s[i][n] == '1') ans += f[1][n - 1][i];
	printf("%lld\n", ans);
	return 0;
}
```





---

## 作者：OtoriEmu (赞：4)

感觉还是能做的题吧！只要能想到定义就好了。可是我没有做出来。

首先的想法一般是考虑忽略掉容斥之类的想法，不只是因为没有模数，而且因为在排除不合法的方案中有一些非常痛苦的相同方案的进一步容斥，再怎么想都是麻烦且不可做的。

那么考虑一些其他的事情。试试找一下这个题 DP 定义的动机。

合法条件可以描述成三个限制（注意到题目其实告诉我们了，点在哪里并不重要，所以自动忽略三点不共线的条件）：

1. 连出的边不能成环；   
2. 连通；   
3. 每个点恰好连一条线。

其实第三个条件是最弱的，尝试从这个条件入手。

「每个点恰好连一条线」也可以描述成「共有 $n$ 对匹配的点」。在转移的过程中，需要用「配对」来描述转移。

猜猜复杂度，也许是个高复杂度多项式算法，暂且当作一个区间 DP。同时注意到题目要求连通，不妨定义 $f_{l,r,\cdots}$ 为 $[l,r]$ 里的所有结点连通的合法方案数，$\cdots$ 是根据题目可能需要维护的不同的东西。

遗憾的是我们现在直接套上区间 DP 的板子，合并两个相邻的区间是不行的，因为我们找不到「配对」操作的影子。那就不妨重新定义 $f_{l,r,u}$ 表示，$[l,r]$ 里的所有点除了 $u$ 已经合法匹配成功，并且 $u$ 与其他点配对之后不会产生环（容易发现如果连出去有一种方案会产生环那就一定会产生环，所以贡献一定为 $0$）的方案数。

然而如果还是合并相邻的区间的话还是不行，因为这样就缺少了下一层状态中 $u$ 的存在了。这样干脆直接合并三个区间 $[l,p],[p+1,q-1],[q,r]$ 就好了。分析这样做的合法性。记三个区间留下来的三个点分别为 $x,u,y$，将三个区间合并为 $[l,r]$，删除掉除了 $u$ 之外 $[l,r]$ 内的所有点并不影响，后续匹配与 $[l,r]$ 无关了；同时因为 $x,y$ 相连不会成环（根据 DP 定义），$u$ 在删去了 $[l,p],[q,r]$ 内的点之后向外连边不会成环，并且加上了这些点只会和 $(x,y)$ 相交，也不会新成环。这样做是合理的。转移比较简单，式子就不写啦。

这样就有一个 $O(n^7)$ 的做法了。卡卡常实际能过。

好像忘记说为什么不会算重了，但是如果这样想的话其实不会算重的原因也好像比较明显的说。

优化到 $O(n^5)$ 的话比较容易，可以看一下其他的题解。下面给以下我的实现，[酸っぱい顔　＞＿＜](https://www.luogu.com.cn/paste/rhkzj7my)。

---

## 作者：xht (赞：3)

## [Pairing Points](https://atcoder.jp/contests/agc039/tasks/agc039_e)

### 题意

- 圆上有 $2n$ 个点，对于任意六个点 $a,b,c,d,e,f$ 满足 $ab,cd,ef$ 三线不共点。
- 给定一个 $2n \times 2n$ 的 $0/1$ 矩阵 $a$，你需要计算将 $2n$ 个点分成 $n$ 个点对的方案数，满足：
  - 对于所有点对 $(p,q)$，$a_{p,q} = a_{q,p} = 1$。
  - 将所有点对用线段连接起来，恰好形成一棵树。
- $n \le 20$。

### 题解

考虑先将 $n$ 设为原本的 $2n$。

考虑用 $f(l,m,r)$ 表示**在 $[l,m-1] \cup [m+1,r]$ 中连一些点对，使得至少有一组点对跨过 $m$，且所有跨过 $m$ 的点对两两不交**的方案数。

枚举 $1$ 号点的对应点 $i$，于是问题求 $f(2,i,n)$ 的答案。

考虑如何求 $f(l,m,r)$，枚举跨过 $m$ 的所有点对中最靠近 $l,r$ 的点对 $(p,q)$。

可以发现，此时 $[p+1,m-1]$ 中，有靠近 $p$ 的一部分会和 $p$ **连通**，剩下的部分与 $m$ 连通，分界点为 $x$。

同理，此时 $[m+1,q-1]$ 中，有靠近 $q$ 的一部分会和 $q$ 连通，剩下的部分与 $m$ 连通，分界点为 $y$。

而 $[l,p-1]$ 一定和 $p$ 连通，$[q+1,r]$ 一定和 $q$ 连通。

因此问题被分为了 $f(l,p,x),f(y,q,r),f(x+1,m,y-1)$ 三个子问题。

记忆化搜索即可，状态数为 $\mathcal O(n^3)$，转移为 $\mathcal O(n^4)$，总时间复杂度为 $\mathcal O(n^7)$，常数非常小，可以通过本题。

这个 DP 可以优化到 $\mathcal O(n^5)$，不过没必要。

### 代码

```cpp
const int N = 47;
int n, a[N][N];
char s[N][N];
ll f[N][N][N], ans;
bool v[N][N][N];

ll DP(int l, int m, int r) {
	if ((l ^ r) & 1) return 0;
	if (l == m && m == r) return 1;
	if (l == m || m == r) return 0;
	if (v[l][m][r]) return f[l][m][r];
	v[l][m][r] = 1;
	for (int p = l; p < m; p++)
		for (int q = r; q > m; q--)
			if (a[p][q])
				for (int x = p; x < m; x++)
					for (int y = q; y > m; y--)
						f[l][m][r] += DP(l, p, x) * DP(y, q, r) * DP(x + 1, m, y - 1);
	return f[l][m][r];
}

int main() {
	rd(n), n <<= 1;
	for (int i = 1; i <= n; i++) rds(s[i], n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = s[i][j] & 1;
	for (int i = 2; i <= n; i++)
		if (a[1][i]) ans += DP(2, i, n);
	print(ans);
	return 0;
}
```

---

## 作者：zzzYheng (赞：2)

#### 题意：

一个圆上有 $2N$ 个点，点对之间有连边，你要选出一组匹配，使得所有弦的相交关系形成一棵树。

数据范围：$N\le 20$。

#### 思路：

很好的一道题。

首先这道题说明了一句话：$N\le 80$ 不一定是多项式复杂度，$N\le 20$ 不一定不是多项式复杂度。大家不要像我一样想当然了。

首先考虑如何刻画形态是树这件事，无根树仅仅只是一个没有环的无向图，但有根树就具有一个非常好的递归结构，非常利于我们 $\text{dp}$ 计数。

那么我们直接拉出来 $1$ 的出边作为树的根，如下图所示。

![](https://pic.imgdb.cn/item/675ab442d0e0a243d4e2eefe.png)

然后考虑其的所有儿子，一定都是跨越两边的弦，并且互不相交，如下图所示：

![](https://pic.imgdb.cn/item/675ab4f7d0e0a243d4e2f02c.png)

然后再考虑儿子的儿子，其只能位于根的一侧，并且只能和一个儿子相交，如下图中的红弦和蓝弦：

![](https://pic.imgdb.cn/item/675ab600d0e0a243d4e2f188.png)

然后可以继续在根的儿子的儿子上继续接儿子，不断递归下去。

同时可以注意到一条非根的弦会被其父亲分成两个部分，这两个部分上接的若干子树是互相独立的两个部分，并且每个部分在圆上都是一个区间。（比如一条根的儿子弦上接的红弦的子树和蓝弦的子树就是相互独立的两个部分，并且每个部分都恰好是一个区间）

所以如果我们把每条非根弦都分成两条弦分别递归子树，那么这个树就始终会保持一个区间递归的结构了。

具体来说，递归的子树可以用 $(l,r,i)$ 描述：子树是 $[l,r]$ 这段区间，子树的根是 $i$ 的出边（注意这条弦已经被我们分成两个部分了）。枚举根的儿子即可完成递归。如下图所示：

![](https://pic.imgdb.cn/item/675abbbfd0e0a243d4e2f71f.png)

那么我们就可以直接对这个结构进行区间 $\text{dp}$，令 $f(l,r,i)$ 表示 $(l,r,i)$ 这个子树共有多少种方案。

考虑转移，显然我们不能直接枚举根的所有儿子，那么考虑更改一下阶段，枚举第一个根的儿子（最高的儿子），如下图中的红弦和蓝弦（假设为 $(a,b)$）：

![](https://pic.imgdb.cn/item/675abb4bd0e0a243d4e2f707.png)

那么现在可以看作 $a,b,i$ 三个点上的弦分别往下接弦形成三个子树，因此只需枚举三个子树区间的分界点即可完成转移。如下图所示：

![](https://pic.imgdb.cn/item/675abd9ad0e0a243d4e2f809.png)

容易算出时间复杂度为 $\Theta(n^7)$，但是由于区间 $\text{dp}$ 的状态和转移中都包含很多的偏序关系，所以实际常数非常非常小，可以在 30ms 内通过。

#### 总结：

这道题目的核心就是要找到递归的子结构来进行 $\text{dp}$，而树天然具有这个结构，利用一些性质就可以进行区间 $\text{dp}$ 了。

---

## 作者：acb437 (赞：1)

# 题解：[AGC039E Pairing Points](https://www.luogu.com.cn/problem/AT_agc039_e)
## 题目大意
本题题意乍看之下就很抽象。根据我个人的理解，题目中的要求的“构成一颗树”的意思是：树上的每一条边就是圆中的连线，而圆上的点和连线的交点就是树上的节点。那么题目的要求实际上可以转化为下面几个条件：

1. 一条连线不能同时和原本已经相交的若干条连线相交，否则会形成环，也即原题示意图右上角的情况。
2. 每一条连线都必须至少与其它一条连线相交，否则会出现不连通的情况，也即原题示意图左下角的情况。这时候就有人问了，$N=1$ 的时候怎么判呢？如果按照我所理解的情况，只有一条连线，没有交点的话，这仅有的 $2$ 个点显然无法构成树结构，故答案为 $0$。
3. 题目要求每一个点必须恰好连一条线，这一点并无什么特别的说法，可以给后面的做法提供思路。同时也可以发现它等价于圆上的点必须是树结构的叶子节点，当然这一点并无实际用处。

有了上述条件，就可以开始考虑如何解题了。
## 思路简述
共有 $2N$ 个点，设 $n=2N$ 便于表述。由于点分布在圆上，不利于考虑问题。在处理时可以直接断环成链，可以令 $1$ 号点为链首，$n$ 号节点为链尾。接着考虑 DP 来解决问题。观察加入一条边时的情况：

![加入一条边的示意图](https://cdn.luogu.com.cn/upload/image_hosting/qd719atm.png)

$m$ 点就是新加入的边，$l$、$r$ 分别表示在 $[l,m)$ 和 $(m,r]$ 范围内的点是在 $m$ 连出的这条边（红边）上某个点的子树上的。直观地说，也就是指它们要么与 $m$ 连出的边（图中的 $p$、$q$，与红边相交）相交，要么与上面这一种边相交（图中的 $x$、$y$，与绿边相交），要么继续嵌套下去（与蓝边相交）。也可以描述为，图中的蓝色点、$p$、$q$ 两点都是在红边与绿边交点的子树上。可以结合下面这张图理解：

![以树的结构表示](https://cdn.luogu.com.cn/upload/image_hosting/wiiegktw.png)

考虑当前的这一种状态，为了防止出现意外的交点（形成环），蓝色点和除 $p$、$q$ 外的其它绿点之间必定有一个分界线，在这里，这条分界线就是 $x$、$y$，在 $[l,x]$ 和 $[y,r]$ 之间的点的边要么与 $p$ 连出的绿边相交，要么与蓝边相交。而剩下的，在 $x$、$y$ 下方的点，则继续与红边相交。如此，我们便设计出了一种状态：设 $dp_{l,m,r}$ 表示当前区间 $[l,r]$ 中的一点 $m$ 向区间外连出一条边的方案数。转移时枚举 $p$、$q$、$x$、$y$，其中与绿边相交的部分可以视为 $[l,x]/[y,r]$ 区间中的点 $p/q$ 向区间外连出一条边，而剩下的部分则是 $(x,y)$ 中的点 $m$ 向区间外连出一条边。我们便得到了第一个版本，可以在 $O(n^7)$（按一些大佬的说法，带有 $\frac{1}{7!}$ 的常数）的时间内解决本题的转移方程：

$$dp_{l,m,r}=\sum_{p\in [l,m)}\sum_{q\in (m,r]}[A_{p,q}]\sum_{x\in [p,m)}\sum_{y\in (m,q]}dp_{l,p,x}\times dp_{y,q,r} \times dp_{x+1,m,y-1}$$

### 基础的代码
```cpp
#include <cstdio>
#include <iostream>
#define N 45
using namespace std;
typedef long long ll;
int n;char s[N];int a[N][N];ll ans;
bool vis[N][N][N];ll dp[N][N][N];

ll DFS(int l, int m, int r)
{
    if((l ^ r) & 1)return 0;
    if(l == m && m == r)return 1;
    if(l == m || m == r)return 0;
    if(vis[l][m][r])return dp[l][m][r];vis[l][m][r] = true;
    for(int p = l;p < m;p++)
        for(int q = r;q > m;q--)
            if(a[p][q])
                for(int x = p;x < m;x++)
                    for(int y = q;y > m;y--)
                        dp[l][m][r] += DFS(l, p, x) * DFS(y, q, r) * DFS(x + 1, m, y - 1);
    return dp[l][m][r];
}

int main()
{
    scanf("%d", &n), n <<= 1;
    for(int i = 1;i <= n;i++)
    {
        scanf("%s", s + 1);
        for(int j = 1;j <= n;j++)
            a[i][j] = (s[j] ^ 48) & 1;
    }
    for(int i = 2;i <= n;i++)
        if(a[1][i])
            ans += DFS(2, i, n);
    printf("%lld\n", ans);
    return 0;
}
```

尽管上述做法已经足以通过本题，但可能无法满足某些毒瘤出题人的要求，考虑继续优化。接着我们可以发现，枚举过程中的 $dp_{l,p,x}$ 和 $dp_{y,q,r}$ 都是与 $m$ 无关的，于是可以提出来，交换一下枚举顺序（因为确定了 $p$、$q$ 的话，中间枚举 $x$、$y$ 时还是需要一个 $m$ 限制，但确定了 $x$、$y$ 的话，$p$、$q$ 的范围是确定的），单独计算一个 $f_{l,r,x,y}$，表示原本的 $\sum_{p\in[l,x]}\sum_{q\in[y,r]}dp_{l,p,x}\times dp_{y,q,r}$，转移时在相应位置做调整即可。用记忆化搜索的话需要两个函数相互调用，如此，我们得到了可以在 $O(n^6)$（按一些大佬的说法，带有 $\frac{1}{6!}$ 的常数）的时间内通过本题的算法。

### 优化一次后的代码
```cpp
#include <cstdio>
#include <iostream>
#define N 85
#define P 998244353
using namespace std;
typedef long long ll;
int n;char s[N];int a[N][N];ll ans;
bool visf[N][N][N][N], visdp[N][N][N];ll dp[N][N][N], f[N][N][N][N];

ll DFS(int l, int m, int r);
ll calF(int l, int r, int x, int y)
{
    if(visf[l][r][x][y])return f[l][r][x][y];visf[l][r][x][y] = true;
    for(int p = l;p <= x;p++)
        for(int q = r;q >= y;q--)
            if(a[p][q])
                f[l][r][x][y] = (f[l][r][x][y] + DFS(l, p, x) * DFS(y, q, r));
    return f[l][r][x][y];
}
ll DFS(int l, int m, int r)
{
    if((l ^ r) & 1)return 0;
    if(l == m && m == r)return 1;
    if(l == m || m == r)return 0;
    if(visdp[l][m][r])return dp[l][m][r];visdp[l][m][r] = true;
    for(int x = l;x < m;x++)
        for(int y = r;y > m;y--)
            dp[l][m][r] = (dp[l][m][r] + DFS(x + 1, m, y - 1) * calF(l, r, x, y));
    return dp[l][m][r];
}

int main()
{
    scanf("%d", &n), n <<= 1;
    for(int i = 1;i <= n;i++)
    {
        scanf("%s", s + 1);
        for(int j = 1;j <= n;j++)
            a[i][j] = (s[j] ^ 48) & 1;
    }
    for(int i = 2;i <= n;i++)
        if(a[1][i])
            ans = (ans + DFS(2, i, n));
    printf("%lld\n", ans);
    return 0;
}
```

但这并不是极限。观察计算过程，可以发现 $f$ 数组的转移过程中，$dp_{y,q,r}$ 在很大程度上与 $p$ 无关，于是交换枚举顺序，提出 $[l,x]$，设 $g_{l,x,q}$ 表示区间 $[l,x]$ 中有一个点与 $q$ 相连的方案数，在计算 $g$ 的过程中枚举 $x$，同样地，在 $f$ 转移的相应位置修改即可。于是，最终版本的，复杂度为 $O(n^5)$（按一些大佬的说法，带有 $\frac{1}{5!}$ 的常数）的算法终于出炉。
## 最终代码
```cpp
#include <cstdio>
#include <iostream>
#define N 85
#define P 998244353
using namespace std;
typedef long long ll;
int n;char s[N];int a[N][N];ll ans;
bool visg[N][N][N], visf[N][N][N][N], visdp[N][N][N];ll g[N][N][N], dp[N][N][N], f[N][N][N][N];

ll DFS(int l, int m, int r);
ll calG(int l, int x, int q)
{
    if(visg[l][x][q])return g[l][x][q];visg[l][x][q] = true;
    for(int p = l;p <= x;p++)
        if(a[p][q])
            g[l][x][q] = (g[l][x][q] + DFS(l, p, x));
    return g[l][x][q];
}
ll calF(int l, int r, int x, int y)
{
    if(visf[l][r][x][y])return f[l][r][x][y];visf[l][r][x][y] = true;
    for(int q = r;q >= y;q--)f[l][r][x][y] = (f[l][r][x][y] + calG(l, x, q) * DFS(y, q, r));
    return f[l][r][x][y];
}
ll DFS(int l, int m, int r)
{
    if((l ^ r) & 1)return 0;
    if(l == m && m == r)return 1;
    if(l == m || m == r)return 0;
    if(visdp[l][m][r])return dp[l][m][r];visdp[l][m][r] = true;
    for(int x = l;x < m;x++)
        for(int y = r;y > m;y--)
            dp[l][m][r] = (dp[l][m][r] + DFS(x + 1, m, y - 1) * calF(l, r, x, y));
    return dp[l][m][r];
}

int main()
{
    scanf("%d", &n), n <<= 1;
    for(int i = 1;i <= n;i++)
    {
        scanf("%s", s + 1);
        for(int j = 1;j <= n;j++)
            a[i][j] = (s[j] ^ 48) & 1;
    }
    for(int i = 2;i <= n;i++)
        if(a[1][i])
            ans = (ans + DFS(2, i, n));
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：KazamaRuri (赞：1)

## 解析

前情提要：这是一篇以优化为中心的题解，其他题解把常规做法讲的很清楚了，我看其他题解的优化方法与我有所不同，故有了这篇文章。

先增强一下数据范围，让 $ n \le 40 $。

这个时候常规的 $O(n^7)$ 的暴力已经无法在 1s 内得出答案了，贴一下这部分代码：


```cpp
#include <iostream>
using namespace std;
using ll =long long;
const int N=85,mod=998244353;
int n,a[N][N]; char s[N][N];
ll f[N][N][N],ans; bool vis[N][N][N];
ll F(int l,int m,int r){
	if((l+r)&1) return 0;
	if(l==m||r==m) return l==m&&r==m;
	if(vis[l][m][r]) return f[l][m][r];
	vis[l][m][r]=1;
	for(int u=l;u<m;u++)
		for(int v=m+1;v<=r;v++)
			if(a[u][v])
				for(int i=u;i<m;i++)
					for(int j=m+1;j<=v;j++)
						f[l][m][r]+=F(l,u,i)*F(j,v,r)*F(i+1,m,j-1);
	return f[l][m][r];
}
int main(){
	scanf("%d",&n),n<<=1;
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=s[i][j]^48;
	for(int i=2;i<=n;i++)
		if(a[1][i]) ans+=F(2,i,n);
	return !printf("%lld",ans);
}
```

状态数三维加上枚举转移四维，时间复杂度就飙到了七次方的级别。


考虑从枚举优化，观察下面的代码。
```cpp
f[l][m][r]+=F(l,u,i)*F(j,v,r)*F(i+1,m,j-1)
```
换个角度考虑问题，我们原本是枚举 $u,v$ 这对匹配点，然后枚举联通段的 $i,j$，由于最后的 $f_{i+1,m,j-1}$ 与 $u,v$ 无关，不妨先枚举 $i,j$，然后再在 $[l,i]$ 和 $[j,r]$ 中枚举 $u,v$，发现这是一个子问题，记 $ g_{l,x,y,r} = \sum f_{l,i,x} \cdot f_{y,j,r} $，则 $ f_{l,m,r} = \sum g_{l,i,j,r} \cdot f_{i+1,m,j-1} $，以此可以把变量枚举数的时间替换成子问题答案的空间，我们在枚举 $f$ 时，就不用算每个子问题的答案了，时间复杂度 $O(n^6)$，实测这次优化直接让效率足足翻了五倍。

这部分优化的代码如下：

```cpp
inline ll F(int l,int m,int r);
inline ll G(int l,int x,int y,int r);
inline ll F(int l,int m,int r){
	if((l+r)&1) return 0;
	if(l==m||r==m) return l==m&&r==m;
	if(vis[l][m][r]) return f[l][m][r];
	vis[l][m][r]=1;
	for(int i=l;i<m;i++)
		for(int j=m+1;j<=r;j++)
			f[l][m][r]+=G(l,i,j,r)*F(i+1,m,j-1);
	return f[l][m][r];
}
inline ll G(int l,int x,int y,int r){
	if(cal[l][x][y][r]) return g[l][x][y][r];
	cal[l][x][y][r]=1;
	for(int i=l;i<=x;i++)
		for(int j=y;j<=r;j++)
			if(a[i][j]) g[l][x][y][r]+=F(l,i,x)*F(y,j,r);
	return g[l][x][y][r];
}
```
最后一步优化，还是从枚举的角度出发，用上文的方法优化，观察新的这段代码：

```cpp
for(int i=l;i<m;i++)
		for(int j=m+1;j<=r;j++)
			f[l][m][r]+=G(l,i,j,r)*F(i+1,m,j-1);
```
 似乎当我们枚举 $i$ 时，$j$ 的枚举范围总是不变，与 $i$ 无关，也就是说还有一个子问题的模型，记录一个新的状态 $h_{l,i,m,r} = \sum g_{l,i,j,r} \cdot f_{i+1,m,j-1} $，则 $ f_{l,m,r} = \sum h_{l,i,m,r} $，时间复杂度降到 $O(n^5)$，足以通过加强的数据（虽然这份代码在小数据没有上一份优秀，但只有这份能过大数据）。

放下代码：
 
```cpp
inline ll F(int l,int m,int r);
inline ll G(int l,int x,int y,int r);
inline ll H(int l,int i,int m,int r);
inline ll F(int l,int m,int r){
	if((l+r)&1) return 0;
	if(l==m||r==m) return l==m&&r==m;
	if(vis1[l][m][r]) return f[l][m][r];
	vis1[l][m][r]=1;
	for(int i=l;i<m;i++) f[l][m][r]+=H(l,i,m,r);
	return f[l][m][r];
}
inline ll G(int l,int x,int y,int r){
	if(vis2[l][x][y][r]) return g[l][x][y][r];
	vis2[l][x][y][r]=1;
	for(int i=l;i<=x;i++)
		for(int j=y;j<=r;j++)
			if(a[i][j]) g[l][x][y][r]+=F(l,i,x)*F(y,j,r);
	return g[l][x][y][r];
}
inline ll H(int l,int i,int m,int r){
	if(vis3[l][i][m][r]) return h[l][i][m][r];
	vis3[l][i][m][r]=1;
	for(int j=m+1;j<=r;j++)
		h[l][i][m][r]+=G(l,i,j,r)*F(i+1,m,j-1);
	return h[l][i][m][r];
}
```
总结一下，这种优化方式的步骤：

1.剖离不相关量，找到独立的部分。

2.抽象出不相关量的子问题。

3.空间换时间，记录子问题答案。

这种空间换时间的优化看上去并没有减少枚举量，实际上的减少可以想象成有一个每个状态为根的森林，然后我们把他们共有的子树合并到了一起，组成了一个点数更少的 DAG。只凭代码看，优化不直观的原因可能是因为我的递归写法，其他题解的迭代写法的优化更加直观，但是不像递归容易理解。

---

## 作者：Phartial (赞：1)

很妙的状态设计啊！

考虑枚举 $1$ 号点连向的 $x$ 号点，那么在 $[2,2n]$ 这段区间内就会有一条主干边 $(1,x)$ 分割了左右两边。

不难发现 $[2,2n]$ 内跨过了主干边的边之间不能有交（否则就会产生一个三元环），所以这些边形成了一个包含关系。

考虑枚举最外层的边 $(i,j)$，那么从 $(1,x)$ 和 $(i,j)$ 的交点开始往 $i$ 走必然可以走到一个区间 $[2,a]$ 内的所有圆周点，往 $x$ 走也可以走到一个区间 $(a,b]$ 内的所有圆周点，往 $j$ 走同样可以走出一个区间 $(b,2n]$ 内的所有圆周点。

枚举 $a,b$，那么原问题就划分成了三个形如“在 $[l,r]$ 这段区间内的 $x$ 有一条连出去的主干边，求这段区间内部的合法连边方案数”的子问题，直接 dp 即可。时间复杂度 $\mathcal{O}(n^7)$，因为常数很小所以能过。

可以优化到 $\mathcal{O}(n^5)$，不过没啥必要。

代码相当幽默。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 41;

int n;
bool a[kN][kN], v[kN][kN][kN];
LL f[kN][kN][kN], ans;

LL F(int l, int r, int x) {
  if (r - l & 1) {
    return 0;
  }
  if (l == r) {
    return 1;
  }
  if (v[l][r][x]) {
    return f[l][r][x];
  }
  v[l][r][x] = 1;
  for (int i = l; i < x; ++i) {
    for (int j = x + 1; j <= r; ++j) {
      if (a[i][j]) {
        for (int p = i; p < x; ++p) {
          for (int q = x; q < j; ++q) {
            f[l][r][x] += F(l, p, i) * F(p + 1, q, x) * F(q + 1, r, j);
          }
        }
      }
    }
  }
  return f[l][r][x];
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n, n *= 2;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      char c;
      cin >> c;
      a[i][j] = c - '0';
    }
  }
  for (int x = 2; x <= n; ++x) {
    if (a[1][x]) {
      ans += F(2, n, x);
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：OoXiao_QioO (赞：0)

注意到这么一个事实: 如果场上已经有了一个叉，那么接下来的边不能再穿过这个叉了。

首先需要破环为链，考虑从 $1$ 号点这里断开，枚举 $1$ 号点连接哪个点，然后就可以让 $[2,2n]$ 这些点断开了。我们令 $f_{i,j,k}$ 或 $[i,j](k)$ 表示区间 $[i,j]$ 中的 $k$ 向外连了一条边. 答案是枚举 $1$ 号点连了哪个点，也就是 $\sum_{i=3}^{2n-1} f_{2,2n,i}$。

于是我们现在的问题在于如何求 $f_{i,j,k}$。 由于边要联通，所以与 $k$ 相连的这条边必然被 $[i,j]$ 中的某两个点所连接的边穿过。我们考虑枚举最靠外的那条边，假设为 $x\to y$. 这样整个区间被分为了两个部分:$[i,k](x)，[k,j](y)$。但是问题并没有得到解决，因为 $[i,x]$ 和 $[y,j]$ 之间的
确不可能出现连边了，但 $[x,k]$ 和 $[k,y]$ 之间仍然可能出现连边。

但我们发现: 在 $[i,k]$ 中一定存在一个分界线，使得分界线两侧是连到不同的两边的。

我们不妨再枚举一下这两个分界线，分别设为 $p,q$。现在整个区间被分为了三个部分：$[i,p](x)$、$[p,q](k)$、$[q,j](y)$，三个部分之间并没有连边,于是成功将区间拆分。

所以这个题告诉我们：拆分区间的很重要的条件是，将一个区间拆分为若干相互无联系的区间，而我们的重点就是找到一种方式使得区间间相互无联系的。大家今后一定要注意。

明白了这些，代码呼之欲出。

---

## 作者：strcmp (赞：0)

题意比较抽象的题。

首先令 $n \leftarrow 2N$。

首先直接当成环考虑显然不好做，于是你不妨枚举 $1$ 和某个点 $k$ 连接。这样它就相当于变成了两个序列。

那么就分成了 $[2,\,k - 1]$ 和 $[k + 1,\,n]$ 两个部分，我们肯定是先让它们内部形成树，然后两个部分各自选出一只点出来连接。

因此我们设一个 $f_{l,\,r,\,x}$ 代表区间 $[l,\,r]$ 选出 $x$ 出来连边的方案数。我们相当于要求 $\sum\limits_{i=2}^n f_{2,\,n,\,i}$。

这是一个区间 dp 的形式，但如果我们使用朴素的枚举 $[l,\,k]$ 和 $[k + 1,\,r]$ 的 dp 得到 $f_{l,\,r,\,x}$，会找不到能转移到哪个 $x$。

因此可以想到我们要枚举两个分界点 $p,\,q$ 以及其选出来的点 $i,\,j$。钦定只有 $i,\,j$ 跨过了 $x$，那么剩下的就是 $f_{l,\,p,\,i},\,f_{p + 1,\,q - 1,\,x},\,f_{q + 1,\,r,\,j}$ 自己建树。

划分好状态直接转移即可，时间复杂度 $\Theta(n^7)$。

仔细分析代码你会发现它远远跑不满，事实上考虑 $40 \times 40$ 的全 $1$ 矩阵，内层循环只运行了 $30908098$ 次，因此是可以通过的。

有较简单方法将算法时间复杂度优化到 $\Theta(n^5)$，这里放 $\Theta(n^7)$ 的。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define per(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
typedef long long int ll;
using pli = pair<ll, int>;
using ppi = pair<pli, int>;
using vec = vector<int>;
const ll inf = 1LL << 30;
constexpr int maxn = 1e5 + 10, mod = 998244353;
int n; char s[45][45]; ll f[45][45][45];
ll dp(int l, int r, int x) {
    if (l == r) return 1; ll& u = f[l][r][x];
    if (u != -1) return u; u = 0;
    rep(i, l, x - 1) {
        rep(j, x + 1, r) {
            if (s[i][j] == '1') {
                rep(p, i, x - 1) rep(q, x + 1, j) u += dp(l, p, i) * dp(p + 1, q - 1, x) * dp(q, r, j);
            }
        }
    }
    return u;
}
int main() {
    memset(f, -1, sizeof(f));
    scanf("%d", &n); n <<= 1; ll ans = 0;
    rep(i, 1, n) scanf("%s", s[i] + 1);
    rep(i, 2, n) if (s[1][i] == '1') ans += dp(2, n, i);
    printf("%lld\n", ans);
    return 0;
}
```

---

