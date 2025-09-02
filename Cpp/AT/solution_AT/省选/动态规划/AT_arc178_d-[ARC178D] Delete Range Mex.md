# [ARC178D] Delete Range Mex

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc178/tasks/arc178_d

正整数 $ N $ と長さ $ M $ の非負整数列 $ A=(A_{1},A_{2},\dots,\ A_{M}) $ が与えられます。

ここで、 $ A $ の全ての要素は $ 0 $ 以上 $ N $ 未満の整数で、相異なります。

$ (0,\ 1,\ \dots\ ,\ N\ -\ 1) $ の順列 $ P $ のうち、以下の条件を満たすものの個数を $ 998244353 $ で割ったあまりを求めてください。

- 数列 $ B\ =\ (B_{1},\ B_{2},\ \dots\ ,\ B_{N}) $ を $ P $ で初期化した後、以下の操作を好きな回数繰り返すことで $ B\ =\ A $ にすることができる。
  - $ 1\leq\ l\leq\ r\leq\ |B| $ を満たす $ l,r $ を選び、 $ \mathrm{mex}(\{B_{l},B_{l+1},\dots\ ,B_{r}\}) $ が $ B $ に含まれているなら、それを $ B $ から削除する。
 
   $ \mathrm{mex}(X) $ とは？ 非負整数からなる有限集合 $ X $ に対し，$ x\notin\ X $ を満たす最小の非負整数 $ x $ を $ \mathrm{mex}(X) $ と定義します．

## 说明/提示

### 制約

- $ 1\leq\ M\leq\ N\leq\ 500 $
- $ 0\leq\ A_{i}\ <\ N $
- $ A $ の要素は互いに相異なる
- 入力は全て整数
 
### Sample Explanation 1

$ B\ =\ (2,\ 1,\ 0,\ 3) $ で初期化したのち、以下の手順で $ B=A $ とすることが可能です。 - $ (l,r)\ =\ (2,\ 4) $ を選び、$ B $ から $ \mathrm{mex}(\{1,0,3\})\ =\ 2 $ を削除し、$ B=(1,0,3) $ とする。 - $ (l,r)\ =\ (3,\ 3) $ を選び、$ B $ から $ \mathrm{mex}(\{3\})\ =\ 0 $ を削除し、$ B=(1,\ 3) $ とする。 よって、$ P=(2,\ 1,\ 0,\ 3) $ は条件を満たします。 条件を満たす $ P $ はこれを含めて $ 8 $ 通りあるので、$ 8 $ を出力してください。

### Sample Explanation 2

$ P\ =\ (0,\ 3,\ 2,\ 1) $ のときのみ条件を満たします。

### Sample Explanation 4

$ 998244353 $ で割ったあまりを求めてください。

## 样例 #1

### 输入

```
4 2
1 3```

### 输出

```
8```

## 样例 #2

### 输入

```
4 4
0 3 2 1```

### 输出

```
1```

## 样例 #3

### 输入

```
16 7
9 2 4 0 1 6 7```

### 输出

```
3520```

## 样例 #4

### 输入

```
92 4
1 67 16 7```

### 输出

```
726870122```

# 题解

## 作者：xyz105 (赞：14)

$$\begin{Bmatrix}\color{red}\LARGE\bold{Solution}\\\normalsize\texttt{No.007 }\bold{AT\_arc178\_d}\end{Bmatrix}\times\footnotesize\texttt{ By Xyz105}$$

### 题目描述

给定 $N, M$ 和长度为 $M$ 且值域为 $[0,N-1]$ 的整数序列 $A$，求出关于 $(0,1,\ldots,N-1)$ 的合法排列 $P$ 的数量。一个排列 $P$ 合法，当且仅当经过若干次以下操作后它能变成序列 $A$：
- 选择 $P$ 的某个子区间 $[l,r]$，若 $\text{mex}(\{P_l,P_{l+1},\ldots,P_r\})$ 在 $P$ 中出现，则将它从 $P$ 中删除。


### 解题思路

**区间 DP**。

先挖一下本题的性质。$x$ 能被删掉的情况，就是选择的子区间 $[l,r]$ 包含 $0\sim x-1$ 这些数并且不包含 $x$ 本身，因为只有这样这个子区间的 $\text{mex}$ 值才能为 $x$。

所以 $x$ 不能在 $[l,r]$ 这个子区间里面，也就是说 $x$ 如果在删除序列中，那么比 $x$ 小的数要么都在 $x$ 左侧，要么都在 $x$ 右侧。

不难看出 一个数被删掉 要先以 比它小的数字都存在（没被删掉）作为前提，所以删除的数字按顺序来看必须是从大到小的。

考虑倒着来，从小到大插入数字。序列 $A$ 的长度为 $M$，所以它有 $M+1$ 个空隙可供插入，同一个空隙可能会插入多个数字。不妨设 $f_{l,r,k}$ 表示当前已确定插入 $0\sim k$，并且保证后续填数的位置（空隙编号）$\le l$ 或 $\ge r$（可以理解为，第 $l+1\sim r-1$ 个空隙不能再插入比 $k$ 大且在删除序列中的任何数字）的方案数。

从小到大枚举插入的数字 $x$。如果 $x$ 已经在 $A$ 序列出现过，设它出现的位置在第 $pos_x\sim pos_x+1$ 个空隙之间，则有 $\forall l,r$，$f_{\min\{pos_x,l\},\max\{pos_x+1,r\},x}\gets f_{l,r,x-1}$。

如果 $x$ 不在 $A$ 序列中，说明 $x$ 在删除序列里。因此如果 $x$ 插在比它小的数的左侧，那么有 $f_{l,r,x}\gets\sum_{i=l}^rf_{i,r,x-1}$。枚举时 $i$ 这一维可被前缀和优化掉。

同理，如果 $x$ 插在比它小的数的右侧，那么有 $f_{l,r,x}\gets\sum_{i=l}^rf_{l,i,x-1}$。

考虑 DP 初值，发现 $0$ 是个特殊的存在。如果序列 $A$ 中已经出现过 $0$ 了，那么就令 $f_{pos_0,pos_0+1,0}=1$。

如果序列 $A$ 中没有 $0$，那么 $0$ 是要被删掉的。根据 $\text{mex}$ 特性，随便挑一个正整数都能将 $0$ 删掉，所以 $0$ 可以插在任何位置，故令 $i\isin [1,m+1],f_{i,i,0}=1$。

DP 终值：$f_{1,m+1,n-1}$。总时间复杂度 $O(m^2n)$。


### 参考代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;

int n, m, a[510], pos[510];

ll f[510][510][510];

inline void add(ll &a, ll b) {a = (a + b) % MOD;}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) pos[a[i]] = i;
	
	if (!pos[0])
		for (int i = 1; i <= m + 1; i++) f[i][i][0] = 1;
	else f[pos[0]][pos[0] + 1][0] = 1;
	
	for (int i = 1; i < n; i++)
		if (!pos[i])
		{
			for (int r = 1; r <= m + 1; r++)
			{
				ll i1 = 0;
				for (int l = r; l; l--)
					add(i1, f[l][r][i - 1]), add(f[l][r][i], i1);
			}
			for (int l = 1; l <= m + 1; l++)
			{
				ll i1 = 0;
				for (int r = l; r <= m + 1; r++)
					add(i1, f[l][r][i - 1]), add(f[l][r][i], i1);
			}
		}
		else
		{
			for (int l = 1; l <= m + 1; l++)
				for (int r = l; r <= m + 1; r++)
					add(f[min(pos[i], l)][max(pos[i] + 1, r)][i], f[l][r][i - 1]);
		}
	cout << f[1][m + 1][n - 1];
	
	return 0;
}
```

---

## 作者：Eraine (赞：7)

编号：AT_arc178_d

tag：区间 dp

难度：*2498

没场切，因为没打。

观察此题，容易得到以下性质：

性质 $1$：删除的数必然递减，这是由于大的 $\text{mex}$ 需要小的数还存在于序列中。

性质 $2$：若 $i$ 位于删除序列中，那么 $[0,i-1]$ 只能全部出现在 $i$ 的左侧或 $i$ 的右侧。否则选出来的任意区间不可能使得 $\text{mex}$ 恰为 $i$。感兴趣的读者可以证明一下，这里由于证明较为简单且不太重要，笔者就不放了。

性质 $3$：假设区间 $[l,r]$ 是在一个排列 $P$ 中包含所有 $[0,i]$ 的最小区间。显然这样的区间唯一存在。若 $i$ 是待删除元素，则 $P_l=i$ 或 $P_r=i$。由于这是最小区间，所以 $P_l,P_r\in[0,i]$。若 $P_l$ 和 $P_r$ 均不为 $i$，则 $i$ 出现在 $[l+1,r-1]$ 内，此时值为 $[0,i-1]$ 的元素出现在值为 $i$ 的元素的两侧，不满足性质 $2$，故假设不成立，结论成立。

很容易发现我们需要得到的序列转移和区间有关，故能想到区间 dp。状态表示包含所有 $[0,i]$ 的最小区间方案数，状态数 $\Theta(n^3)$。滚动数组优化一下就是 $\Theta(n^2)$。枚举 $i$，当 $i$ 不在删除序列时不足即可，$i$ 在删除序列显然区间要不只往左拓展，要不只往右拓展。这个前缀和简单维护，可以实现均摊 $\Theta(1)$ 转移。

$\Theta(n^3)$。

[submission](https://atcoder.jp/contests/arc178/submissions/53687177)

如有错误和疑问请指出，虚心接受您的意见。

---

## 作者：XichenOC (赞：1)

## [[ARC178D] Delete Range Mex](https://www.luogu.com.cn/problem/AT_arc178_d)
# 题目翻译：
给定一个长度为 $M$ 且值域为 $[1,N-1]$ 的整数序列  $A$，及目标序列。我们要对为 $(0,1,2,…,N-1)$ 所组成的序列 $P$ 的不同排序进行统计，统计有多少种排序使其在任意次数的操作下变为 $A$。
>**操作:** 每次选择任意一个区间 $l \sim  r,(1 \le l \le r \le |P|)$ 并且如果 $\operatorname{mex}({ P_l ,P_{l+1},P_{l+2},…,P_r })$ 存在与 $A$ 中，就删除它。  
>* 其中 $\operatorname{mex}$ 是指，对于一个由非负整数构成的集合 $S$，$\operatorname{mex}(S)$ 表示不在集合 $S$ 的最小非负整数。
# 思路：
**一，分析题目：** 可以发现该题有以下性质：
>1.若我想要删掉一个数 $num$，那我一定要保证所给的 $l \sim r$ 之间有 $0 \sim num-1$ 这些数，并且不包含 $num$。只有这样才能保证该区间的 $\operatorname{mex}$ 为 $num$。因此我们的删除顺序一定是从大到小的。
>
>---
>2.也就是说所有比 $num$ 小的数都在它的左侧，或者都在它的右侧。这样保证该数被删掉前，比他小的都没有删掉。

**二，分析解法：** 
>1. 我们的最终目标是要删掉一些数后变成 $A$ 而前面又知道删除的顺序一定是从大到小的。那我们反过来，考虑加数，那加数的顺序也就是从小到大的。
>
>---
>2. 因为 $A$ 的大小为 $M$ 那我们就有 $M+1$ 个地方可以插入，中间空隙和左右两边。而且同一个空隙可以同时插入多个数。
>
>---
>3. 我们假设 $f[l][r][k]$ 表示在区间 $[l,r]$ 已经插入了数字 $0 \sim k$ 的方案数,并且保证该区间内不会在填出现比 $k$ 大的数，也就是后续不能再填数到这个区间。理由是为了保证该状态的答案确定性，因为若多添加一个数，那改变的是 $f[l][r][k+1]$。
>
>---
>4. 那我们从小到大枚举所有要加的点，若一个点已经出现在 $A$ 间，那这个数原本就存在，也就不需要在有这个数的区间内加入这个数，那它的方案数也就没变。那我们令该数出现 $pos_x$ 与 $pos_{x+1}$ 之间的空隙间。那任意有该数的区间的答案都等于该区间不加这个数的答案，转移方程为：
>$$ \forall l,r \in[1,M+1],f[\min(pos_x,l)][\max(pos_x+1,r)][x]=f[l][r][x-1]$$
>
>---
>5.若一点不存在与 $A$ 中那就这个数就被删除了，也就要加入：
>>* 若这个数要加到比他小的数的左侧，也就需要从之前右侧的状态转移过来。那转移方程为：
>>$$f[l][r][x]+= \sum_{i=l}^rf[i][r][x-1]$$
>>* 同理，若这个数要加到比他小的数的右侧，也就需要从之前左侧的状态转移过来。那转移方程为：
>>$$f[l][r][x]+= \sum_{i=l}^rf[l][i][x-1]$$
>
>---
>6.**考虑特殊：** 情况可以发现 $0$ 比较特殊。继续分类讨论:
>>* 如果 $0$ 已经出现，那很明显:
>>$$f[pos_0][pos_0+1][0]=1$$
>>* 如果 $0$ 还没出现，由于 $0$ 是最小的非负整数，那任意正整数都可以将他删除。也就是说它可以插到到任意空隙，对答案没有影响：
>>$$\forall i \in [1,M+1],f[i][i][0]=1$$
>最后只需要最开始给其初始化即可
>
>---
>7. **考虑优化：** 第 $5$ 点的转移可以由前缀和优化，维护。

最终答案也就是 $f[1][M-1][N-1]$，总体的时间复杂度为 $O(m^2n)$，考点**区间 dp**。
# 完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=510;
const int P=998244353;

int a[N],pos[N],f[N][N][N];
void add(int &a,int b){
    a=(a+b)%P;
}
signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        pos[a[i]]=i;
    }
    if(!pos[0]){
        for(int i=1;i<=m+1;i++){
            f[i][i][0]=1;
        }
    }
    else{
        f[pos[0]][pos[0]+1][0]=1;
    }
    for(int i=1;i<n;i++){
        if(!pos[i]){
            for(int r=1;r<=m+1;r++){
                int il=0;
                for(int l=r;l;l--){
                    add(il,f[l][r][i-1]);
                    add(f[l][r][i],il);
                }
            }
            for(int l=1;l<=m+1;l++){
                int il=0;
                for(int r=l;r<=m+1;r++){
                    add(il,f[l][r][i-1]);
                    add(f[l][r][i],il);
                }
            }
        }
        else{
            for(int l=1;l<=m+1;l++){
                for(int r=l;r<=m+1;r++){
                    add(f[min(pos[i],l)][max(pos[i]+1,r)][i],f[l][r][i-1]);
                }
            }
        }
    }
    cout<<f[1][m+1][n-1]<<endl;
}
```
~~由于做题时，借鉴了第一篇题解，所以思路和代码可能比较相似。~~

---

## 作者：Assembly_line (赞：1)

来一个不一样的做法。

$O(n^4)$。

首先进行一些观察，发现对于不在 $A$ 中的数（要删的数），一定要从大到小删。因为如果先删掉了一个较小的数 $x$，以后的 $\text{mex}$ 都会小于等于 $x$，于是较大的数就删不掉了。

接着考虑一个数 $x$ 能被删掉还要满足什么条件。选出的数的 $\text{mex}$ 是 $x$ 当且仅当 $0\sim x-1$ 都被选且 $x$ 不被选，于是发现 $0\sim x-1$ 只能在 $x$ 的一侧。（否则要选满 $0\sim x-1$ 就会跨越 $x$）

同时还要满足 $A$ 是 $P$ 的一个子序列。（$A$ 的相对顺序不能变）

考虑 dp，从小到大插入 $0\sim n-1$，由于上面的性质 2，现在插入一个要被删去的数，它一定会被放在当前序列的最左侧/最右侧（这样比它小的数都在一侧）。于是设 $f_{i,j,k}$ 为插入了 $0\sim i$，当前序列左侧有 $j$ 个要被删去的数，右侧有 $k$ 个要被删去的数。转移有两种：

- 当前插入的数 $i+1$ 在 $A$ 没有出现。那么可以将其放在左/右侧。$f_{i,j,k}\rightarrow f_{i+1,j+1,k},f_{i+1,j,k+1}$。

- 否则，$i+1$ 在 $A$ 中出现过，要满足 $A$ 的相对顺序不变就很麻烦，于是考虑提前计算贡献的 trick：

  假如 $A=(4,7,8,1)$，现在要插入 $4$，当前序列状态为 $(0,0,1,0)$。（这些 $0$ 代表要被删去的数，也就是不影响 $A$ 的相对顺序）显然 $4$ 要插在 $1$ 左侧，枚举插在第 $t$ 个 $0$ 和第 $t+1$ 个 $0$ 之间，比如 $(0,4,0,1,0)$，那我们在这里直接计算以后插入 $7,8$ 的贡献，此时 $(4,(),0,(),1)$ 中括号的位置可以任意插入数，要把 $7,8$ 插进去显然有 $3$ 种选择。（这可以用插板法解决）

  类似地可以计算 $i+1$ 插在右边的情况。这样就满足了 $A$ 相对顺序不变的条件，注意到上面要枚举 $t$，所以这里的复杂度是 $O(n^4)$。

但是常数很小，预处理组合数即可通过本题。（1300ms）

[code](https://atcoder.jp/contests/arc178/submissions/61450767)。

---

## 作者：Lyrella (赞：1)

# [[ARC178D]Delete Range Mex](https://atcoder.jp/contests/arc178/tasks/arc178_d) 2024.11.20

## 简要题意

对于一个排列 $A$，每次可以选择一个区间 $[l,r]$ 删去当前排列中的 $\operatorname{mex}(A_l,A_{l+1}\dots A_r)$ 这个数，可以操作任意次。现在给定一个序列 $B$，求长度为 $n$ 的排列 $A$ 能够通过若干次操作变成 $B$ 的 $A$ 的数量对 $998244353$ 取模。

**数据范围**：$1\le m\le n\le500,0\le B_i<n$。

## 题解

对于这道题目我们先去寻找它有什么性质。考虑我们如何删掉一个数 $x$？我们需要选择一段区间，满足 $x$ 不在里面但是小于 $x$ 的数全在。那么这有什么特殊的呢？我们这样考虑。

加入我们现在要把 $0$ 到 $n-1$ 从小到大插入序列，如果我们后面要删除 $x$，我们在插入 $x$ 时就需要把它放在当前序列的最左边或者最右边某个位置（如下图），也就是说当前 $x$ 可以插入的位置范围是 $[1,lpos)\cup(rpos,n]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/odx8md44.png)

回到此题。现在给出了最后剩下的 $m$ 个数，而我们需要把删去的数填入这 $m+1$ 个空中。于是就有 $f_{l,r,x}$ 表示插入到了 $x$，且区间 $[l,r]$ 内不能再填其他数的方案数。

枚举 $x$，对于 $x$，若 $x$ 没有被删除，说明它的位置已经确定，我们可以先将其记录下来。转移时就只能转移到旁边的区间：$f_{\min\{pos_x,l\},\max\{pos_x+1,r\},x}\leftarrow f_{l,r,x-1}$。因为 $pos_x$ 不能动。

若 $x$ 要被删掉，就大概枚举一下 $x$ 的位置，是一个标准的区间 $DP$。当计算到区间 $[l,r]$ 时，$f_{l,r,x}$ 的转移需要从子区间来，转移式子就是：
$$
f_{l,r,x}=\sum_{l\le pos\le r}f_{l,pos,x-1}+\sum_{l\le pos\le r}f_{pos,r,x-1}
$$
解释一下转移。对于一个区间 $[l,r]$ 不能填数，说明最后填 $x$ 时肯定填在了一个端点。如果填在 $r$，子区间就只能在 $[l,pos]$ 中选择，如果填在 $l$ 同理。然后可以前缀和优化一下，最后时间复杂度 $O(nm^2)$。

## 代码

```cpp
const int N = 505, p = 998244353;

int n, m, a[N], pos[N], f[N][N][N];

int add(int x, int y){return x - p + y >= 0 ? x - p + y : x + y;}

int main(){
 	freopen("c.in", "r", stdin);
 	freopen("c.out", "w", stdout);
	n = rd(), m = rd();
	for(int i = 1; i <= m; ++i)a[i] = rd(), pos[a[i]] = i;
	if(pos[0])f[pos[0]][pos[0] + 1][0] = 1;
	else for(int i = 1; i <= m + 1; ++i)f[i][i][0] = 1;
	for(int x = 1; x < n; ++x)if(pos[x])
		for(int i = 1; i <= m + 1; ++i)for(int j = i; j <= m + 1; ++j)
			f[min(pos[x], i)][max(pos[x] + 1, j)][x] = add(f[min(pos[x], i)][max(pos[x] + 1, j)][x], f[i][j][x - 1]);
	else{
		for(int i = 1, tmp = 0; i <= m + 1; ++i, tmp = 0)for(int j = i; j <= m + 1; ++j)
			tmp = add(tmp, f[i][j][x - 1]), f[i][j][x] = add(f[i][j][x], tmp);
		for(int j = 1, tmp = 0; j <= m + 1; ++j, tmp = 0)for(int i = j; i; --i)
			tmp = add(tmp, f[i][j][x - 1]), f[i][j][x] = add(f[i][j][x], tmp);
	}
	wt(f[1][m + 1][n - 1]);
	return 0;
}
```

---

## 作者：Polarisx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc178_d)。

考场上没切出来，赛后发现自己是小丑🤣。

## 思路

容易发现的是数一定是从大到小删的。

对于一个排列，删数 $x$ 时，假设 $[l,r]$ 是包含 $0\sim x-1$ 所有数的**最小**区间（这种区间有且仅有一个），要让这个排列合法当且仅当数 $x$ 没有出现在区间 $[l,r]$ 中，可以发现，随着 $x$ 的增长，这个区间是逐步增大的，相对的，$x$ 能取到的位置在逐渐减少。

这样我们可以设计一个 DP，令 $f_{i,l,r}$ 表示已经处理了 $0\sim i$ 的数（即这些数都合法），包含 $0\sim i$ 每个数的最小区间为 $[l,r]$ 的合法排列数，对于 $f_{i-1,l,r}$，我们可以在此基础上将 $i$ 填到 $l$ 左边或 $r$ 右边。

但是随之我们发现了一个问题，就是我们并不确定剩下的数在原排列的位置，考虑插入法，将每个数插入已经确定好的数的空隙中（我们称 $B_i$ 到 $B_{i+1}$ 的空隙为 $i$ 号空隙）。

那么这就好办了，令 $f_{i,l,r}$ 表示已经处理了 $0\sim i$ 的数，包含 $0\sim i$ 每个数的最小区间为**空隙** $l$ 到**空隙** $r$ 的合法排列数，有转移：

- 若数 $i$ 没有出现在序列 $B$ 中，$f_{i,l,r}\leftarrow \sum_{j=l}^r f_{i-1,l,j}+f_{i-1,j,r}$，即一种方案为填到 $l$ 空隙左边，一种为填到 $r$ 空隙右边。

- 若数 $i$ 存在于序列 $B$ 中，假定其在序列 $B$ 的位置为 $pos_i$，也就是在空隙 $pos_{i}-1,pos_i$ 之间，有 $f_{i,\min(pos_i-1,l),\max(pos_i,r)}\leftarrow f_{i-1,l,r}$。

最终答案就是 $f_{n-1,0,m}$，前缀和优化即可做到 $\mathcal O (nm^2)$。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Mod=998244353;
const int Maxn=510;
int n,m;
int f[Maxn][Maxn][Maxn];
int a[Maxn],pos[Maxn];

inline void chadd(int &x,int y){
    x+=y;
    if(x>=Mod) x-=Mod;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]),pos[a[i]]=i;

    if(!pos[0]) for(int i=0;i<=m;i++) f[0][i][i]=1;
    else f[0][pos[0]-1][pos[0]]=1;

    for(int i=1;i<n;i++){
        if(!pos[i]){
            for(int l=0;l<=m;l++){
                int sm=0;
                for(int r=l;r<=m;r++)
                    chadd(sm,f[i-1][l][r]),chadd(f[i][l][r],sm);
            }
            for(int r=0;r<=m;r++){
                int sm=0;
                for(int l=r;~l;l--)
                    chadd(sm,f[i-1][l][r]),chadd(f[i][l][r],sm);
            }
                
        }
        else{
            for(int l=0;l<=m;l++)
                for(int r=l;r<=m;r++)
                    chadd(f[i][min(l,pos[i]-1)][max(r,pos[i])],f[i-1][l][r]);
        }
    }
    printf("%d",f[n-1][0][m]);

    system("pause");
    return 0;
}
```

---

## 作者：songhongyi (赞：1)

题意：求有多少个 $N$ 阶排列（值域为 $0$ 到 $N-1$），使得每次选一个区间，在序列中删去这个区间的 $\operatorname{mex}$，可以得到给定的长为 $M$ 的序列 $A$。

考虑删除的过程。显然，我们需要删除掉所有不在 $A$ 中的数，并按照倒序删除。原因是序列中删掉一个数后，任意区间的 $\operatorname{mex}$ 都不可能超过这个数。

继而考虑原排列需要满足的性质。加入我们现在想要删掉 $x$，那么我们就需要找一个区间，使得 $0$ 到 $x-1$ 出现过，$x$ 没有出现。这也意味着，我们必须把 $x$ 放到 $0$ 到 $x-1$ 这些数的同侧。既然如此，不如考虑正序放数。当然考虑到 $A$ 需要是原排列的子序列，所以考虑把不在 $A$ 中的数插到 $A$ 中。

考虑 DP，设 $f_{i,j,k}$ 表示考虑到第 $i$ 个数，其中目前所有数前面还有 $j$ 个空位，所有数后面还有 $k$ 个空位。

接下来每次加一个数 $x$。讨论。若 $x$ 在 $A$ 中出现，不妨设为第 $l$ 个。那么对于一组 $(j,k)$，显然一定会变为 $(\min(j,l-1),\max(k,M-l))$。这个过程可以单轮 $O(M^2)$ 转移。

若不然，则枚举其放置位置。可以得到：
$$
f_{i,j,k}=\sum_{l=j}^M f_{i-1,l,k}+\sum_{l=k}^M f_{i-1,j,l}
$$
显然用前缀和优化，可以做到单论 $O(M^2)$ 转移。

那么总时间复杂度为 $O(NM^2)$，空间复杂度利用滚动数组可以优化为 $O(M^2)$。

---

## 作者：Genius_Star (赞：0)

模拟赛题。

### 思路：

容易发现，若想要删掉数 $x$，则必须要先满足 $[0, x - 1]$ 内的数都存在，故必须从大到小删除。

再观察一个性质，若想要使得 $[l, r]$ 的 $\operatorname{mex} = x$，那么 $[l, r]$ 肯定不能包含 $x$；则小于 $x$ 的数都必须同时在 $x$ 左边或右边。

通过上述性质，我们考虑从小到大插入数，有 $m + 1$ 个空；令 $dp_{k, l, r}$ 表示已经插入了 $[0, k]$ 的数后 $[0, k]$ 中最远插到了第 $r$ 个空，最近插入到了 $l$ 这个空。

故后面插入的数必须在 $l$ 左边（即 $\le l$）或 $r$ 右边（即 $\ge r$）的空。

当 $x$ 本身存在时，令 $a_x$ 表示 $x$ 所在的位置，则：

$$dp_{nxt, \min(l, a_x), \max(r, a_x + 1)} \gets dp_{nxt, \min(l, a_x), \max(r, a_x + 1)} + dp_{now, l, r}$$

否则，枚举将 $x$ 插入到第 $k$ 个空：

$$dp_{nxt, k, r} \gets dp_{nxt, k, r} + dp_{now, l,r}(k \le l)$$

$$dp_{nxt, l, k} \gets dp_{nxt, l, k} + dp_{now, l, r} (k \ge r)$$

朴素转移是 $O(nm^2(n-m))$ 的，但是由于模拟赛数据过弱，可以直接过掉（且比三次方的跑的快）。

在本题需要使用差分优化。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 505, mod = 998244353;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, x;
int a[N];
int f[2][N][N], s[N][N], t[N][N];
int main(){
//	open("c.in", "c.out");
	n = read(), m = read();
	for(int i = 1; i <= m; ++i){
		x = read();
		a[x] = i;
	}
	if(a[0])
	  f[0][a[0]][a[0] + 1] = 1;
	else{
		for(int i = 1; i <= m + 1; ++i)
		  f[0][i][i] = 1; 
	}
	for(int i = 1; i < n; ++i){
		int nxt = i & 1, now = nxt ^ 1;
		memset(f[nxt], 0, sizeof(f[nxt]));
		memset(s, 0, sizeof(s));
		memset(t, 0, sizeof(t));
		for(int l = 1; l <= m + 1; ++l){
			for(int r = l; r <= m + 1; ++r){
				if(!f[now][l][r])
				  continue;
				if(a[i]){
					f[nxt][min(l, a[i])][max(r, a[i] + 1)] = (f[nxt][min(l, a[i])][max(r, a[i] + 1)] + f[now][l][r]) % mod;
					continue;
				}
				s[r][1] = (s[r][1] + f[now][l][r]) % mod;
				s[r][l + 1] = (s[r][l + 1] - f[now][l][r] + mod) % mod;
				t[l][r] = (t[l][r] + f[now][l][r]) % mod;
			}
		}
		for(int r = 1; r <= m + 1; ++r){
			int sum = 0;
			for(int l = 1; l <= r; ++l){
				sum = (sum + s[r][l]) % mod;
				f[nxt][l][r] = (f[nxt][l][r] + sum) % mod;
			}
		}
		for(int l = 1; l <= m + 1; ++l){
			int sum = 0;
			for(int r = l; r <= m + 1; ++r){
				sum = (sum + t[l][r]) % mod;
				f[nxt][l][r] = (f[nxt][l][r] + sum) % mod;
			}
		}
	}
	write(f[(n - 1) & 1][1][m + 1]);
	return 0;
}
```

---

## 作者：SFlyer (赞：0)

第一次（？）独立做出 arc 评分 $\sim 2500$ 的题，记之。

MEX 我们肯定是从大的往小的删，因为小的先删了肯定不能再删更大的了。然后如果我们要删掉 $i$，那么 $0\sim i-1$ 必定是在 $i$ 的左边或者右边（不能两边都有否则包含 $i$）。

一个立马想到的思路就是从大往小确定枚举是在左边还是右边，但是发现 $a$ 要是子序列这个很难搞。所以不如确定下来 $a$ 再插空填不在 $a$ 中的，设为 $b$ 数组。一共有 $m+1$ 个空隙。

我们可以维护要填一个数 $b_i$ 的时候我们可以填的空隙。这个不可以填的空隙一定是一个连续的区间。这个是因为不能填的地方就是 $<b_i$ 的区间，我们必须要在左边或者右边。

设 $dp_{x,l,r}$ 为确定了 $b_0\sim b_x$，目前 $b_{x+1}$ 可以填的区间是 $l\sim r$ 空隙。那么我们填 $b_{i+1}$ 的时候，先把 $a$ 中 $b_i+1\sim b_{i+1}-1$ 的数至少要用到的区间和 $l\sim r$ 合并，设为 $[L,R]$。则 $dp_{x+1,1\sim L,R}$ 和 $dp_{x+1,L,R\sim m+1}$ 都要加上 $dp_{x,l,r}$。这个可以查分一下再前缀和。

注意 $b_0=0$ 和 $b_0\neq 0$ 不同考虑。复杂度 $\mathcal{O}(m^3)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 5e2+2;
const ll mod = 998244353;

ll m,n,a[N],lb[N],rb[N],vis[N],dp[N][N][N],f[2][N][N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>m;
	for (int i=1; i<=m; i++){
		cin>>a[i];
		vis[a[i]]=1;
	}
	for (int i=0; i<n; i++){
		int mn=n+1,mx=0;
		for (int j=1; j<=m; j++){
			if (a[j]<=i){
				mn=min(mn,j);
				mx=max(mx,j);
			}
		}
		mx++;
		lb[i]=mn,rb[i]=mx;
	}
	vector<int> v;
	for (int i=0; i<n; i++){
		if (!vis[i]){
			v.push_back(i);
		}
	}
	if (n==m){
		return cout<<"1\n",0;
	}
	if (v[0]==0){
		for (int i=1; i<=m+1; i++){
			dp[1][i][i]=1;
		}
	}
	else{
		dp[0][lb[v[0]-1]][rb[v[0]-1]]=1;
	}
	for (int i=(v[0]==0?2:1); i<=v.size(); i++){
		int it=v[i-1];
		for (int l=1; l<=m+1; l++){
			for (int r=l; r<=m+1; r++){
				f[0][l][r]=f[1][l][r]=0;
			}
		}
		for (int l=1; l<=m+1; l++){
			for (int r=l; r<=m+1; r++){
				ll L=l,R=r;
				if (it){
					L=min(L,lb[it-1]);
					R=max(R,rb[it-1]);
				}
				f[0][1][R]=(f[0][1][R]+dp[i-1][l][r])%mod;
				f[0][L+1][R]=(f[0][L+1][R]-dp[i-1][l][r]+mod)%mod;
				f[1][L][R]=(f[1][L][R]+dp[i-1][l][r])%mod;
			}
		}
		for (int l=1; l<=m+1; l++){
			ll cur=0;
			for (int r=l; r<=m+1; r++){
				cur=(cur+f[1][l][r])%mod;
				dp[i][l][r]=(dp[i][l][r]+cur)%mod;
			}
		}
		for (int r=1; r<=m+1; r++){
			ll cur=0;
			for (int l=1; l<=r; l++){
				cur=(cur+f[0][l][r])%mod;
				dp[i][l][r]=(dp[i][l][r]+cur)%mod;
			}
		}
	}
	ll ans=0;
	for (int l=1; l<=m+1; l++){
		for (int r=l; r<=m+1; r++){
			ans=(ans+dp[v.size()][l][r])%mod;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：gan1234 (赞：0)

### 分析

令 $pre_i$ 表示 $\min^i_{k=1}{a_k}$，$suf_i$ 表示 $\min^n_{k=i}a_k$。

两个性质：

- 删数是从大到小依次删除的。如果一个小的数在大的数之前被删掉，那么较大的数将无法被删掉

- 令某次被删除的 $b_i=k$，那么显然 $b$ 中存在区间 $b_{l...r}$ 包含 $[1,k-1]$ 且不包含 $k$。

考虑从小到大往 $a$ 里面插数。

根据性质二，我们发现存在一个区间我们无法插入任何数，而其余位置随便插。考虑设计 DP 状态表示这个性质。

令 $f_{l,r,k}$ 表示已经插入前 $k$ 个数，区间 $a_{l...r}$ 内已经不能再插数。

为了不重不漏的把所有情况考虑到，DP 的初值怎么赋是一个难点。

分两种情况：

- $a$ 中有 $0$。

令 $a$ 的 $mex$ 为 $k$，此时 $k$ 左右侧不能同时存在小于 $k$ 的数。因此找到一个最小的区间 $[l,r]$ 使得 $pre_{l-1}>k,suf_{r+1}>k$，令 $f_{l,r,0}=1$，这便是最开始就不能插入的区间。

- $a$ 中没有 $0$。

此时 $a$ 的 $mex$ 就是 $0$，因此它可以插入到任何地方。考虑 $0$ 插入到任何地方都不会使得存在一个区间变得不能插入，为了体现这种空区间的特殊情况，我们令 $f_{i,i-1,0}$ 表示。因此我们只需将所有 $1\le i \le n+1$ 的 $f_{i,i-1,0}=1$ 即可。

转移：

当 $pre_{l-1}>k$ 时，可以从区间左侧插入：

$$ f_{l,r,k}\longleftarrow \sum^{r+1}_{i=l}f_{i,r,k-1}$$

当 $suf_{r+1}>k$ 时，可以从区间右侧插入：

$$f_{l,r,k}\longleftarrow \sum^{r}_{i=l-1}f_{l,i,k-1}$$

这个东西可以前缀和优化。

状态数 $O(n^3)$，转移 $O(1)$，复杂度 $O(n^3)$。

注意，转移时不要忘了 $r$ 可以等于 $l-1$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,m,ans;
int a[505];
int f[505][505][505];
int pre[505],suf[505];
int b[505];
vector<int>v;
signed main(){
	ios::sync_with_stdio(0);
	cin>>m>>n;
	for(int i=1;n>=i;i++)cin>>a[i],b[a[i]]=i;
	v.push_back(0);
	for(int i=1;m>i;i++)
		if(!b[i])v.push_back(i);
	pre[0]=1e9;suf[n+1]=1e9;
	for(int i=1;n>=i;i++)pre[i]=min(pre[i-1],a[i]);
	for(int i=n;i;i--)suf[i]=min(suf[i+1],a[i]);
	if(!b[0]){
		for(int i=1;n+1>=i;i++)f[i][i-1][0]=1;
	}else{
		for(int i=1;m>=i;i++){
			if(!b[i]){
				int l=1,r=n;
				while(pre[l]>i)l++;
				while(suf[r]>i)r--;
				f[l][r][0]=1;
				break;
			}
		}
	}
	for(int k=1;v.size()>k;k++){
		for(int l=1;n+1>=l;l++){	
			int sum=0;
			for(int r=l-1;n>=r;r++){
				(sum+=f[l][r][k-1])%=mod;
				if(suf[r+1]>v[k])(f[l][r][k]+=sum)%=mod;
			}
		}
		for(int r=0;n>=r;r++){
			int sum=0;
			for(int l=r+1;l;l--){
				(sum+=f[l][r][k-1])%=mod;
				if(pre[l-1]>v[k])(f[l][r][k]+=sum)%=mod;
			}
		}
	}
	for(int l=1;n+1>=l;l++)
		for(int r=l-1;n>=r;r++)
			(ans+=f[l][r][v.size()-1])%=mod;
	cout<<ans<<endl;
}
```

---

