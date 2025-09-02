# Xor-Grid Problem

## 题目描述

Given a matrix $ a $ of size $ n \times m $ , each cell of which contains a non-negative integer. The integer lying at the intersection of the $ i $ -th row and the $ j $ -th column of the matrix is called $ a_{i,j} $ .

Let's define $ f(i) $ and $ g(j) $ as the [XOR](https://en.wikipedia.org/wiki/Exclusive_or) of all integers in the $ i $ -th row and the $ j $ -th column, respectively. In one operation, you can either:

- Select any row $ i $ , then assign $ a_{i,j} := g(j) $ for each $ 1 \le j \le m $ ; or
- Select any column $ j $ , then assign $ a_{i,j} := f(i) $ for each $ 1 \le i \le n $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993E/ab8c49518f9b338686e1980130aba0ac0a188a1e.png) An example of applying an operation on column $ 2 $ of the matrix.In this example, as we apply an operation on column $ 2 $ , all elements in this column are changed:

- $ a_{1,2} := f(1) = a_{1,1} \oplus a_{1,2} \oplus a_{1,3} \oplus a_{1,4} = 1 \oplus 1 \oplus 1 \oplus 1 = 0 $
- $ a_{2,2} := f(2) = a_{2,1} \oplus a_{2,2} \oplus a_{2,3} \oplus a_{2,4} = 2 \oplus 3 \oplus 5 \oplus 7 = 3 $
- $ a_{3,2} := f(3) = a_{3,1} \oplus a_{3,2} \oplus a_{3,3} \oplus a_{3,4} = 2 \oplus 0 \oplus 3 \oplus 0 = 1 $
- $ a_{4,2} := f(4) = a_{4,1} \oplus a_{4,2} \oplus a_{4,3} \oplus a_{4,4} = 10 \oplus 11 \oplus 12 \oplus 16 = 29 $

You can apply the operations any number of times. Then, we calculate the $ \textit{beauty} $ of the final matrix by summing the absolute differences between all pairs of its adjacent cells.

More formally, $ \textit{beauty}(a) = \sum|a_{x,y} - a_{r,c}| $ for all cells $ (x, y) $ and $ (r, c) $ if they are adjacent. Two cells are considered adjacent if they share a side.

Find the minimum $ \textit{beauty} $ among all obtainable matrices.

## 说明/提示

Let's denote $ r(i) $ as the first type operation applied on the $ i $ -th row, and $ c(j) $ as the second type operation applied on the $ j $ -th column.

In the first test case, you can apply an operation $ c(1) $ , which assigns $ a_{1,1} := 1 \oplus 3 = 2 $ . Then, we'll receive this matrix:

 23In the second test case, you can apply an operation $ r(1) $ , which assigns:

- $ a_{1,1} := g(1) = 0 \oplus 5 = 5 $
- $ a_{1,2} := g(2) = 1 \oplus 4 = 5 $
- $ a_{1,3} := g(3) = 0 \oplus 4 = 4 $

The resulting matrix after performing the operation is:

 554544In the third test case, the best way to achieve minimum $ \textit{beauty} $ is applying three operations: $ c(3) $ , $ r(2) $ , and $ c(2) $ . The resulting matrix is:

 046456

## 样例 #1

### 输入

```
4
1 2
1 3
2 3
0 1 0
5 4 4
2 3
0 2 4
4 5 1
3 3
1 2 3
4 5 6
7 8 9```

### 输出

```
1
3
13
24```

# 题解

## 作者：Alex_Wei (赞：13)

### [CF1993E Xor-Grid Problem](https://www.luogu.com.cn/problem/CF1993E)

首先只考虑列操作。根据异或的性质，第 $i$ 次操作会让被操作的列变为第 $i - 1$ 次操作时被替换的列，于是可以这样想：我们手里拿着一列数，初始为每一行的所有数的异或和。每次用手里的列和某一列交换。对于行同理。

因此，对 $1\leq i\leq n$，设 $a_{i, m + 1}$ 等于 $a_{i, j} \ (1\leq j\leq m)$ 的异或和。对 $1\leq j\leq m + 1$，设 $a_{n + 1, j}$ 等于 $a_{i, j}\ (1\leq i\leq n)$ 的异或和，则每次操作相当于交换某一列和第 $m + 1$ 列，或交换某一行和第 $n + 1$ 行。

枚举删掉哪一行哪一列，剩下的行和列可以任意排列且行列贡献独立，预处理每两行之间和每两列之间的贡献，问题转化为最短哈密顿路径。使用 $\mathcal{O}(2 ^ nn ^ 2)$ 的 DP 求解，总时间复杂度 $\mathcal{O}(2 ^ n n ^ 4)$，不能通过。

注意到在计算列之间的贡献时不需要枚举删掉哪一列，因为将第 $m + 1$ 列加入 DP 后，删去一列可以直接在状态里进行操作。对于行同理。时间复杂度降为 $\mathcal{O}(2 ^ nn ^ 3)$。[代码](https://codeforces.com/contest/1993/submission/275030437)。

---

## 作者：TernaryTree (赞：6)

比 D 简单好多。我们对一行进行手玩。我们用数字表示下标，用连着的数字表示几个下标上数的异或。

$$
\begin{aligned}
&1,2,3,4 \\
\rightarrow &1,1234,3,4 \\
\rightarrow &1,1234,3,2 \\
\rightarrow &1,4,3,2 \\
\end{aligned}
$$

一个简单的发现是，我们可以任意交换两个数。然而里面时不时还会出现 $1234$，我们猜测任意情况只有原来的数和原来所有数的异或出现，并且恰好是从这 $n+1$ 个数中去掉了一个数。

证明：考虑归纳，假设进行 $i-1$ 次操作是满足原命题的。

- 若存在原来所有数的异或，我们下一步会得到不在上一轮的那个数。
- 否则，我们下一步会得到原来所有数的异或。

由此，我们不妨在每一行末尾放上每一行所有数的异或，在每一列最下面放上每一列所有数的异或，最右下角放上矩阵里所有数的异或，得到一个 $(n+1)\times (m+1)$ 的矩阵。我们现在需要：

- 选出 $n$ 行 $m$ 列，等价于删掉一行一列。
- 任意 swap 行或列，使答案最小。

我们把答案进行一个贡献的拆，拆成行与行之间与列与列之间的贡献。然后进行 dp：$f_{S,i,k}$ 表示，我们选了 $S$ 里面的行，最后一行是 $i$，我们不选的那一列是 $k$。$g_{S,i,k}$ 即转置矩阵后的 $f_{S,i,k}$。转移：

$$f_{S,i,k}=\min_{j\in S, j\neq i}f_{S/\{i\}, j, k} + s_{i,j}-|a_{i,k}-a_{j,k}|$$

其中 $s_{i,j}=\sum_{k} |a_{i,k}-a_{j,k}|$，$g$ 的转移同理。

对于统计答案，枚举删掉的行 $i$ 删掉的列 $j$，此时最优答案是容易通过我们的 dp 值算出的。这样做法就是 $\Theta(2^n n^2 m+2^m m^2 n)$ 的。注意到 $\sum n^2+m^2\le 500$，这等价于最大的 $n=m=15$ 只有一组，开了 $5s$，随便跑。

---

## 作者：AzusidNya (赞：5)

### CF1993E Xor-Grid Problem

场上看到这题的第一反应是想到了 [AGC016D XOR Replace](https://www.luogu.com.cn/problem/AT_agc016_d)。

先考虑将一个数替换为整行的异或和的情况。

设这一行的异或和为 $x$，将 $a_i$ 替换为 $x$，然后考虑再次求整行的异或和。

然后我们发现此时整行的异或和变成了刚刚替换的 $a_i$。

然后我们再将 $a_j$ 替换为整行的异或和，那么 $j$ 这个位置上的数会变成 $a_i$，然后整行的异或和会变成 $a_j$。 

所以考虑在这一行后面多加上一个格子，一开始里面放着这一行所有数的异或和。那么对于这一行，将一个数替换为一行的异或和的操作等价于它与新加的格子里的数交换。

回到这题，这题可以对一列全部替换为它们对应行的异或和。在这个矩阵后面增加第 $m + 1$ 列代表一行的异或和，然后这次操作就变成了选择矩阵的一列，并和 $m + 1$ 列交换。

行是同理的，考虑增加第 $n + 1$ 行代表每列的异或和，行操作就变成了将选择的行和 $n + 1$ 列交换。

那么还有一个问题是，当我们操作了一行后操作一列，那么交点位置会怎么样。手玩发现交点位置会变成初始整个矩阵的异或和。那么按照上面的交换操作，这个交点位置上的值会被换成 $(n + 1, m + 1)$ 这个位置上的值，所以我们只需要在 $(n + 1, m + 1)$ 这个位置上填上整个矩阵的异或和即可。

现在问题变成了，给一个 $(n + 1)$ 行 $(m + 1)$ 列的矩阵，行之间可以任意交换，列之间可以任意交换，求在它左上角 $n$ 行 $m$ 列这个范围内的美丽值的最大值。

美丽值是可以拆开成行和列算的，最终美丽值等于上下相邻的格子之间的差的绝对值之和加上左右相邻的格子之间的差的绝对值之和。先考虑左右相邻的格子之间的差的绝对值之和的最小值怎么算。

然后就成了很经典的状压了。先预处理出 $s_{i, j}$ 表示将第 $i$ 列拼到第 $j$ 列后面产生多少贡献。枚举最后把哪一行换到第 $(n + 1)$ 行，设它为 $df$。

设 $f_{S, j}$ 表示已经填了 $S$ 集合中的列，当前填在最后一列的是 $j$ 产生的最小美丽值贡献。枚举一列 $k$ 拼在 $j$ 后面，产生的贡献就是 $s_{j, k} + |a_{df, k} - a_{df, j}|$。直接转移即可。

设 $ans_{i, j}$ 表示将第 $i$ 行放到 $(n + 1)$ 行，第 $j$ 列放到 $(m + 1)$ 列的最小美丽值，那么左右相邻格子的贡献在这次状压已经算出来了，累加到贡献里就行。

上下相邻格子的贡献同理，对行状压即可，然后贡献到 $ans_{i, j}$。

最后 $ans$ 数组的最小值就是答案。认为 $n, m$ 同阶，则时间复杂度 $O(n ^ 32^n)$

[code.](https://codeforces.com/contest/1993/submission/274543550)

Fun fact：赛时很快想到了 $O(n ^3 2 ^n)$ 的做法，但是没看时限，一直认为这个复杂度过不去硬想优化想了 40min 无果，第二天看到官方题解就是自己的做法后彻底破防。

---

## 作者：WeWantToRun (赞：2)

我竟然独立想出了 *2700，虽然死磕 $O(n^42^n)$ 磕了一个小时。

考虑在原矩阵右边加一列表示每一行的异或和，下面加一行表示每一行的异或和，那么不难发现一次操作就相当于是把当前行/列和最后一行/列交换的过程。那么就相当于可以将原矩阵的行和列任意重排。

这时候有一个简单的 $O(n^42^n)$ 做法，就是枚举最终没有贡献的行号和列号，然后行和列分别独立状压 DP 求解。我这个复杂度的代码跑了七秒，很遗憾过不去。于是考虑优化这个东西。因为行和列是互相独立的，可以只枚举删除了哪一行，然后 DP 算出这个情况下，删除某一列时每两列之差的最小值。同理可以枚举删除了哪一列时，删除某一行的每两行之差的最小值。最后再枚举删除的行号和列号，就可以直接把前面两个值相加。由于行和列互相独立，所以这个做法是正确的。总时间复杂度为 $O(n^32^n)$。

[Code](https://www.luogu.com.cn/paste/scszphan)

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF1993E)

**题目大意**

> 给定 $n\times m$ 矩阵，每次操作选择一行或一列，把该行的所有值替换为所在列的异或和，或把该列的所有值替换为所在行的异或和，最小化所有相邻元素的差的绝对值之和。
>
> 数据范围：$n,m\le 15$。

**思路分析**

把某个元素替换为整行异或和，等价于交换整行异或和和当前元素。

那么添加一个虚拟行和虚拟列，虚拟列的元素就是所在行的异或和，虚拟行的元素就是所在列的异或和。

那么操作就是交换虚拟行和某一行，或交换虚拟列和某一列。

看成删去一行一列后任意重排行列，重排时行列贡献独立，分别状压 dp 求出最小权哈密顿路。

注意到考虑行之间的贡献只需要枚举删除了哪一列，删除每一行的贡献都能直接计算。

设 $n,m$ 同阶，时间复杂度 $\mathcal O(n^32^n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,m,a[16][16],w[16][16],dp[1<<16][16],res[16][16];
inline void chkmin(int &x,const int &y) { x=y<x?y:x; }
void DP(int q) {
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<q;++i) dp[1<<i][i]=0;
	for(int s=0;s<(1<<q);++s) {
		for(int i=0;i<q;++i) if(s>>i&1) {
			for(int j=0;j<q;++j) if(!(s>>j&1)) {
				chkmin(dp[s|(1<<j)][j],dp[s][i]+w[i][j]);
			}
		}
	}
}
void solve() {
	cin>>n>>m;
	memset(a,0,sizeof(a));
	memset(res,0,sizeof(res));
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) {
		cin>>a[i][j],a[0][j]^=a[i][j],a[i][0]^=a[i][j],a[0][0]^=a[i][j];
	}
	for(int i=0;i<=n;++i) {
		memset(w,0,sizeof(w));
		for(int u=0;u<=m;++u) for(int v=u+1;v<=m;++v) {
			for(int j=0;j<=n;++j) if(i!=j) w[u][v]+=abs(a[j][u]-a[j][v]);
			w[v][u]=w[u][v];
		}
		DP(m+1);
		int U=(1<<(m+1))-1;
		for(int j=0;j<=m;++j) {
			int mn=inf;
			for(int k=0;k<=m;++k) if(k!=j) chkmin(mn,dp[U-(1<<j)][k]);
			res[i][j]+=mn;
		}
	}
	for(int i=0;i<=m;++i) {
		memset(w,0,sizeof(w));
		for(int u=0;u<=n;++u) for(int v=u+1;v<=n;++v) {
			for(int j=0;j<=m;++j) if(i!=j) w[u][v]+=abs(a[u][j]-a[v][j]);
			w[v][u]=w[u][v];
		}
		DP(n+1);
		int U=(1<<(n+1))-1;
		for(int j=0;j<=n;++j) {
			int mn=inf;
			for(int k=0;k<=n;++k) if(k!=j) chkmin(mn,dp[U-(1<<j)][k]);
			res[j][i]+=mn;
		}
	}
	int ans=inf;
	for(int i=0;i<=n;++i) for(int j=0;j<=m;++j) chkmin(ans,res[i][j]);
	cout<<ans<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：superl61 (赞：0)

[题目传送门](https://codeforces.com/contest/1993/problem/E) 

## 题意

给定一个 $n \times m$ 的矩阵 $a$，有两种操作：

- 选择一**行**，把每个数变成所在**列**所有数的异或之和。
- 选择一**列**，把每个数变成所在**行**所有数的异或之和。

求进行任意次操作后整个矩阵最小的美丽值。

## 思路

第一个发现：**同一数异或两次相当于没有异或**，基于这个性质，我们首先可以发现连续两次对同一行（列）操作相当于没有操作。

第二个发现：能替换的值其实是很有限的，因为它是由一行或一列所有值的异或一起决定的，我们会忍不住把所有可供替换的值规规整整地写在对应行（列）前面，以样例中的第 $4$ 组数据为例，我们把异或值写在第 $0$ 行和第 $0$ 列，可以得到：
$$
\begin{matrix}
1 & 2 & 15 & 12 \\
0 & 1 & 2  & 3 \\
7 & 4 & 5 & 6 \\
6 & 7 & 8 & 9 \\
\end{matrix}
$$
你仔细观察这个矩阵或者手动操作几次，可以发现对某行（列）操作相当于和第 $0$ 行（列）整体交换。

所以题目就转化成了：给定一个 $(n + 1) \times (m + 1)$ 的矩阵 $a$，你可以不断地交换某一行和第 $0$ 行，或者某一列和第 $0$ 列，求最终矩阵（不包含第 $0$ 行和第 $0$ 列）最小的美丽值。

## 实现

交换次数是无限的，但矩阵的状态是有限的。

朴素想法是枚举所有的状态，全部求一遍美丽值。

肯定要枚举哪行哪列不选，还要枚举每行每列的排列方式，最后对整个矩阵求答案。所以直接做的话应该是 $O(nm \times 2^{n + m} \times nm)$，即 $O((nm)^22^{n + m})$。

首先可以发现其实行和列的贡献是分别独立的。以行为例，如果行的排列方式确定了，那竖着的贡献就是固定的。这是由操作方式决定的，题目给出的两种操作能保证**初始同行（列）的元素到最后仍然同行（列），变的只是行之间和列之间的顺序**。复杂度变为 $O((nm)^2(2^nm + 2^mn)$。

继续优化答案统计。每次都重新求一遍整个矩形的贡献实在是太不划算了。又想到对于一个选行（列）的集合 $S$，可以预先把最优的排列方式求出来，最后直接查。考虑状压 dp。

记 $f_{S, i, j}$ 表示选的**行**集合为 $S$，最后一**行**是 $i$，不选第 $j$ **列**，最小美丽值。

记 $g_{S, i, j}$ 表示选的**列**集合为 $S$，最后一**列**是 $i$，不选第 $j$ **行**，最小美丽值。

有转移
$$
f_{S, i, j} = \min_{k \in S,k \ne i} f_{T, k, j} + sum_{i, k} - \left| a_{i, j} - a_{k, j}\right|
$$
其中 $sum_{i, k}$ 是某两行之间的总贡献，$T$ 是 $S$ 去掉 $i$。

$g_{S, i, j}$ 转移同理。统计答案就还是枚举删除的行和列，答案容易通过 dp 值求出。

时间复杂度 $O(2^nn^2m + 2^mm^2n)$。

注意 dp 三层循环的顺序。

```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(int i(l);i<=(r);++i)
#define G(i,r,l) for(int i(r);i>=(l);--i)
using namespace std;
using ll = long long;
const int inf = 0x3f3f3f3f;
int f[66000][18][18], g[66000][18][18];
int s[18][18], ss[18][18], a[18][18];
int T, n, m;
void init(){
	cin >> n >> m;
	F(s, 0, (1 << (n + 1)) - 1) F(i, 0, n) F(j, 0, m) f[s][i][j] = inf;
	F(s, 0, (1 << (m + 1)) - 1) F(i, 0, m) F(j, 0, n) g[s][i][j] = inf;
	F(i, 0, n) F(j, 0, n) s[i][j] = 0;
	F(i, 0, m) F(j, 0, m) ss[i][j] = 0; 
	
	
	F(i, 1, n) F(j, 1, m) cin >> a[i][j];
	F(j, 1, m){
		a[0][j] = 0;
		F(i, 1, n) a[0][j] ^= a[i][j];
	}
	F(i, 0, n){
		a[i][0] = 0;
		F(j, 1, m) a[i][0] ^= a[i][j];
	} // ok
	F(i, 0, n) F(k, i + 1, n) {
		s[i][k] = 0;
		F(j, 0, m) s[i][k] += abs(a[i][j] - a[k][j]);	
		s[k][i] = s[i][k];
	}
	
	F(i, 0, m) F(k, i + 1, m) {
		ss[i][k] = 0;
		F(j, 0, n) ss[i][k] += abs(a[j][i] - a[j][k]);
		ss[k][i] = ss[i][k];
	}
	
}
int solve(){
	F(i, 0, n) F(j, 0, m) f[1 << i][i][j] = 0; // 只考虑行 
	F(j, 0, m) F(i, 0, n) g[1 << j][j][i] = 0; // 只考虑列 
	F(j, 0, m){
		F(S, 1, (1 << (n + 1)) - 1){
			F(i, 0, n){
				if(!((S >> i) & 1) || f[S][i][j] == inf) continue;
				F(k, 0, n){
					if(i == k || ((S >> k) & 1)) continue;
					f[S + (1 << k)][k][j] = min(f[S + (1 << k)][k][j], f[S][i][j] + s[i][k] - abs(a[i][j] - a[k][j]));
				}
			}
		}
	}
	
	F(j, 0, n){
		F(S, 1, (1 << (m + 1)) - 1){
			F(i, 0, m){
				if(!((S >> i) & 1) || g[S][i][j] == inf) continue;
				F(k, 0, m){
					if(i == k || ((S >> k) & 1)) continue;
					g[S + (1 << k)][k][j] = min(g[S + (1 << k)][k][j], g[S][i][j] + ss[i][k] - abs(a[j][i] - a[j][k]));
				}
			}
		}
	}
	int ans = inf, U1 = (1 << (n + 1)) - 1, U2 = (1 << (m + 1)) - 1;
	F(i, 0, n){
		F(j, 0, m){
			int ret1 = inf;
			F(k, 0, n) if(k != i) {
				ret1 = min(ret1, f[U1 - (1 << i)][k][j]);
			}
			int ret2 = inf;
			F(k, 0, m) if(k != j) {
				ret2 = min(ret2, g[U2 - (1 << j)][k][i]);	
			}
			ans = min(ans, ret1 + ret2);
		}
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> T;
	while(T --){
		init();
		cout << solve() << '\n';
	}
	return fflush(0), 0; 
}
```

---

## 作者：GGapa (赞：0)

##### [CF1993E Xor-Grid Problem](https://codeforces.com/contest/1993/problem/E)

由这道题可以联想到一个 AGC 的题，有一个 trick：

给定你长度为 $n + 1$ 的序列 $a$，初始时 $a_{n + 1} = a_1 \oplus a_2 \oplus \cdots \oplus a_n$，你每次可以交换 $a_i(i \in [1, n])$ 和 $a_{n + 1}$，若不限制操作次数，则你可以实现对序列 $a$ 任意重排。

对于为什么是交换 $a_i$ 和 $a_{n + 1}$ 的推导：记 $a_5 = a_1 \oplus a_2 \oplus a_3 \oplus a_4$，若此时 $a_5 \gets w$，那么新序列的 $a_5 = a_1 \oplus a_1 \oplus a_2 \oplus a_3 \oplus a_4 \oplus a_3 \oplus a_4 = a_2$，因为 $a_1$、$a_2$、$a_3$ 相互抵消了。此时相当于 $a_5$ 和 $a_2$ 互相替换了。

此时问题转化成从 $(n + 1) \times(m + 1)$ 的矩阵中删除一行和一列，使得美丽值最小。

由于 $n$ 非常小，而且将行和列分开处理是不会影响答案的，考虑进行两次状态压缩。

定义 $F(s, i)$ 为当前已经放好了的行或列的集合为 $s$，最后一个放入行或列的是 $i$，接着便可以运用类似的旅行商问题来解决，由于是二维问题，故每次对行或列进行动态规划时还要枚举列或行哪些不能用。因为要执行两次，每次 DP 完成之后用 $ans(i, j)$ 代表不选第 $i$ 行和第 $j$ 列得到的最小的美丽值。

为了转移方便，我们可能需要两个数组 $dn(i, j)$ 和 $dm(i, j)$ 分别用来记录 $j$ 接在 $i$ 行或列后面所产生的代价。

最终的答案即为 $ans$ 数组中的最小值。时间复杂度为 $O(n^32^n)$。

代码比较简单，$40$ 行左右即可搞定，~~我不喜欢太过松散的代码，所以我压了一下行qwq。~~

```cpp
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
using VI = vector<int>;
const int INF = 1e9;

void solve() {
    int n, m; cin >> n >> m;
    vector<VI> A(n + 1, VI(m + 1)) ;
    rep(i, 0, n - 1) rep(j, 0, m - 1) cin >> A[i][j], A[i][m] ^= A[i][j], A[n][j] ^= A[i][j], A[n][m] ^= A[i][j];
    vector<VI> dn(n + 1, VI(n + 1)), dm(m + 1, VI(m + 1));
    rep(i, 0, n) rep(j, 0, n) if(i != j) 
        rep(k, 0, m) dn[i][j] += abs(A[i][k] - A[j][k]);
    rep(i, 0, m) rep(j, 0, m) if(i != j) 
        rep(k, 0, n) dm[i][j] += abs(A[k][i] - A[k][j]);
    int tn = (1 << n + 1) - 1, tm = (1 << m + 1) - 1;
    vector<VI> ans(n + 1, VI(m + 1, INF));
    vector<VI> F(tn + 1, VI(n + 1, INF));
    rep(ban, 0, m) {
        fill(F.begin(), F.end(), VI(n + 1, INF));
        rep(i, 0, n) F[1 << i][i] = 0;
        rep(s, 0, tn) rep(i, 0, n) if(s >> i & 1 && F[s][i] < INF)  
            rep(j, 0, n) if(!(s >> j & 1))
                F[s | 1 << j][j] = min(F[s | 1 << j][j], F[s][i] + dn[i][j] - abs(A[i][ban] - A[j][ban]));
        rep(i, 0, n) rep(j, 0, n) if(i != j) 
            ans[i][ban] = min(ans[i][ban], F[tn ^ 1 << i][j]);
    }
    F.assign(tm + 1, VI(m + 1, INF)) ;
    rep(ban, 0, n) {
        fill(F.begin(), F.end(), VI(m + 1, INF));
        rep(i, 0, m) F[1 << i][i] = 0;
        rep(s, 0, tm) rep(i, 0, m) if(s >> i & 1 && F[s][i] < INF)
            rep(j, 0, m) if(!(s >> j & 1)) 
                F[s | 1 << j][j] = min(F[s | 1 << j][j], F[s][i] + dm[i][j] - abs(A[ban][i] - A[ban][j]));
        rep(i, 0, m) {
            int x = INF;
            rep(j, 0, m) if(i != j) 
                x = min(x, F[tm ^ (1 << i)][j]);
            ans[ban][i] += x;
        }
    }
    int ret = INF;
    rep(i, 0, n) ret = min(ret, *min_element(ans[i].begin(), ans[i].end()));
    cout << ret << '\n';
}

```

---

## 作者：gyyyyx (赞：0)

我们手动模拟一下，会发现对于不同的两行或列做三次操作相当于交换这两行或列，用异或的性质也很好证明。

我们将最终矩阵的美丽值分成行美丽值和列美丽值之和，容易发现行列的操作是独立的，也就是行交换不影响列美丽值，列交换同理。

因此我们就是要将行列重新排序，然后让行美丽值最大，列美丽值最大。

由于 $n,m\leq 15$，可以用状压 dp $O(n^22^n+m^22^m)$ 解决。

但我们发现，我们可以在行列交换完后单独对某一行或列进行操作，这样这一行或列的值都会变成新的数。

但因为这样的操作只可能在交换操作完后出现，且只对某一行或列操作，可以直接 $O(nm)$ 枚举单独操作的行和列。

设 $n,m$ 同阶，总时间复杂度 $(n^42^n)$，但跑不满。

我的代码常数比较大，但时限很宽，所以过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector <int> bl[1<<15];
int _,n,m,a[20][20],b[20],c[20],X[20],Y[20];
int d[20][20],f[1<<15][20];
inline int DP(int len){
	memset(f,0x3f3f3f3f,sizeof(f));
	for(int i(0);i<len;++i) f[1<<i][i]=0;
	for(int S(1);S<(1<<len);++S){
		if(bl[S].size()==1) continue;
		for(int i(0);i<bl[S].size();++i){
			int p(bl[S][i]),_S(S^(1<<p));
			for(int j(0);j<bl[_S].size();++j){
				int q(bl[_S][j]);
				f[S][p]=min(f[S][p],f[_S][q]+d[p][q]);
			}
		}
	}
	int S((1<<len)-1),ret(0x3f3f3f3f);
	for(int i(0);i<len;++i) ret=min(ret,f[S][i]);
	return ret;
}
inline int Solve(){
	int ret(0);
	memset(d,0,sizeof(d));
	for(int i(0);i<n;++i)
		for(int j(0);j<n;++j)
			for(int k(0);k<m;++k)
				d[i][j]+=abs(a[i][k]-a[j][k]);
	ret+=DP(n);
	memset(d,0,sizeof(d));
	for(int i(0);i<m;++i)
		for(int j(0);j<m;++j)
			for(int k(0);k<n;++k)
				d[i][j]+=abs(a[k][i]-a[k][j]);
	ret+=DP(m);
	return ret;
}
int main(){
	for(int S(1);S<(1<<15);++S)
		for(int i(0);i<15;++i)
			if(S>>i&1) bl[S].push_back(i);
	scanf("%d",&_);
	while(_--){
		scanf("%d%d",&n,&m);
		int al(0);
		for(int i(0);i<n;++i)
			for(int j(0);j<m;++j)
				scanf("%d",&a[i][j]),al^=a[i][j];
		for(int i(0);i<n;++i){
			X[i]=0;
			for(int j(0);j<m;++j) X[i]^=a[i][j];
		}
		for(int j(0);j<m;++j){
			Y[j]=0;
			for(int i(0);i<n;++i) Y[j]^=a[i][j];
		}
		int ans(Solve());
		for(int i(0);i<n;++i){
			for(int j(0);j<m;++j) b[j]=a[i][j];
			for(int j(0);j<m;++j) a[i][j]=Y[j];
			ans=min(ans,Solve());
			for(int j(0);j<m;++j) a[i][j]=b[j];
		}
		for(int j(0);j<m;++j){
			for(int i(0);i<n;++i) c[i]=a[i][j];
			for(int i(0);i<n;++i) a[i][j]=X[i];
			ans=min(ans,Solve());
			for(int i(0);i<n;++i) a[i][j]=c[i];
		}
		for(int i(0);i<n;++i)
			for(int j(0);j<m;++j){
				for(int _j(0);_j<m;++_j) b[_j]=a[i][_j];
				for(int _i(0);_i<n;++_i) c[_i]=a[_i][j];
				for(int _j(0);_j<m;++_j) a[i][_j]=Y[_j];
				for(int _i(0);_i<n;++_i) a[_i][j]=X[_i];
				a[i][j]=al;ans=min(ans,Solve());
				for(int _j(0);_j<m;++_j) a[i][_j]=b[_j];
				for(int _i(0);_i<n;++_i) a[_i][j]=c[_i];
			}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：tobie (赞：0)

幽默题。

考虑对于每行求出改行所有数字的异或和，放在这行的末尾（称为第 $m+1$ 列），那么对于第 $i$ 列的操作等价于交换第 $i$ 列和第 $m+1$ 列。

接下来对于列进行相似的转化，那么问题就转化为：任意交换行列后，忽略最后一行和最后一列后，最小化矩阵的美丽值。

我们发现行和列的操作相对独立。所以枚举删掉哪行和哪列后，可以用一个状压dp在 $O(n^2 2^n)$ 的时间内得到答案。总时间复杂度是高贵的 $O(n^4 2^n)$。

事实上，如果知道了删掉的行编号，那么可以用一次状压dp求出对于所有列编号的删除情况的答案，对于列同理。这样子可以将复杂度压到 $O(n^32^n)$，可以通过。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
//#define int long long
const int N=17,M=70009,inf=1e9+5;
int n,m,a[N][N];
int f[N][N][M],g[N][N][M],ma[N][N];
inline void chkmin(int &x,int y){if(y<x) x=y;}
#define abs Abs
inline int Abs(int x){return x>0?x:-x;}
void work()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		a[i][m]=0;
		for(int j=0;j<m;j++)
		scanf("%d",&a[i][j]),a[i][m]^=a[i][j];
	}
	for(int j=0;j<=m;j++)
	{
		a[n][j]=0;
		for(int i=0;i<n;i++) a[n][j]^=a[i][j];
	}
	n++;m++;
	for(int t=0;t<n;t++)
	{
		for(int i=0;i<m;i++)
		for(int j=0;j<(1<<m);j++)
		f[t][i][j]=inf;
		for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
		{
			ma[i][j]=0;
			for(int k=0;k<n;k++)
			if(k!=t) ma[i][j]+=abs(a[k][i]-a[k][j]);
		}
		for(int i=0;i<m;i++)
		f[t][i][1<<i]=0;
		for(int j=0;j<(1<<m);j++)
		for(int i=0;i<m;i++)
		if((j>>i)&1)
		for(int k=0;k<m;k++)
		if(!((j>>k)&1))
		chkmin(f[t][k][j|(1<<k)],f[t][i][j]+ma[i][k]);
	}
	for(int t=0;t<m;t++)
	{
		for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)
		g[t][i][j]=inf;
		for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			ma[i][j]=0;
			for(int k=0;k<m;k++)
			if(k!=t) ma[i][j]+=abs(a[i][k]-a[j][k]);
		}
		for(int i=0;i<n;i++)
		g[t][i][1<<i]=0;
		for(int j=0;j<(1<<n);j++)
		for(int i=0;i<n;i++)
		if((j>>i)&1)
		for(int k=0;k<n;k++)
		if(!((j>>k)&1))
		chkmin(g[t][k][j|(1<<k)],g[t][i][j]+ma[i][k]);
	}
	int ans=inf;
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	for(int x=0;x<m;x++)
	for(int y=0;y<n;y++)
	chkmin(ans,f[i][x][(1<<m)-1-(1<<j)]+g[j][y][(1<<n)-1-(1<<i)]);
	printf("%d\n",ans);
}
signed main()
{
	int T;
	scanf("%d",&T);
	while(T--) work();
}
```

---

