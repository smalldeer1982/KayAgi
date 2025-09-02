# [ARC126D] Pure Straight

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc126/tasks/arc126_d

$ N $ 項からなる正整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ が与えられます。各 $ A_i $ は $ 1,\ 2,\ \ldots,\ K $ のいずれかです。

あなたはこの数列に対して、次の操作を何度でも行うことができます：

- 隣接する $ 2 $ 項を入れ替える。つまり、$ |i-j|=1 $ となる $ i,\ j $ を選び、$ A_i $ と $ A_j $ を入れ替える。

数列 $ A $ が以下の条件を満たすようにするために必要な操作回数の最小値を求めてください。

- 数列 $ A $ は、連続部分列として $ (1,\ 2,\ \ldots,\ K) $ を含む。 つまり、$ A_n\ =\ 1 $, $ A_{n+1}\ =\ 2 $, $ \ldots $, $ A_{n+K-1}\ =\ K $ が成り立つような $ N-K+1 $ 以下の正整数 $ n $ が存在する。

## 说明/提示

### 制約

- $ 2\leq\ K\leq\ 16 $
- $ K\ \leq\ N\leq\ 200 $
- $ A_i $ は $ 1,\ 2,\ \ldots,\ K $ のいずれかに等しい
- 数列 $ A $ は、$ 1,\ 2,\ \ldots,\ K $ のそれぞれを少なくともひとつ含む

### Sample Explanation 1

例えば次のように操作を行うのが最適です。 - $ A_1 $ と $ A_2 $ を入れ替える。$ A $ は $ (1,3,2,1) $ へ変化する。 - $ A_2 $ と $ A_3 $ を入れ替える。$ A $ は $ (1,2,3,1) $ へ変化する。 - $ A_1\ =\ 1 $, $ A_2\ =\ 2 $, $ A_3\ =\ 3 $ が成り立ち、条件を満たす。

## 样例 #1

### 输入

```
4 3
3 1 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5 5
4 1 5 2 3```

### 输出

```
5```

## 样例 #3

### 输入

```
8 4
4 2 3 2 4 2 1 4```

### 输出

```
5```

# 题解

## 作者：syta (赞：10)

首先考虑 $dp$ 数组的含义，$dp_{S,i}$ 表示 $S$ 中的元素是有序的，且均已经跨过了第 $i$ 位所得到的最小代价。

对于 $i$ 号元素，枚举每一个合法的 $dp_{S,i-1}$ 进行转移，有两种情况：

- $i$ 号元素和集合 $S$ 并在一起，当且仅当 $S$ 中不含 $a_i$ 时可以进行，这样是不需要跨过的，就相当于它们都来找第 $i$ 位，然后第 $i$ 位要冒泡排序一下插进去，也即加上逆序对个数。

	具体来说，$dp_{S \bigcup a_i,i}=\min dp_{S,i-1}+calc(S,a_i)$，$calc(S,a_i)$ 表示计算 $S$ 中比 $a_i$ 大的元素个数。
   
- $i$ 号元素不和集合 $S$ 并在一起，这个没有进行条件，所以 $S$ 中的所有元素都要跟着跨过 $i$ 号元素，$dp_{S,i}=dp_{S,i-1}+\min(\operatorname{popcount}(S),k-\operatorname{popcount}(S))$ 。

	那这里为什么是取 $\min$ 呢，相当于有一个隔板，两边都有数，要把一边的数移到另一边，那肯定是移动小的一边，所以更改一下 $dp$ 数组的含义，为 $S$ 中的元素是有序的，且 $S$ 已经跨过了第 $i$ 位**或** $\overline{S}$ 已经从 $i$ 后面跨到了前面所得到的最小代价。
    
至此本题就结束了，容易发现和背包一样，倒着循环可以省掉 $i$ 这一维。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
int dp[1<<16];
int calc(int s,int x){
	s&=(~((1<<x)-1));
	return __builtin_popcount(s);
}
int main(){
	scanf("%d%d",&n,&k);
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		x--;
		for(int S=(1<<k)-1;~S;S--){
			if(!((S>>x)&1)) dp[S|(1<<x)]=min(dp[S|(1<<x)],dp[S]+calc(S,x));
			dp[S]+=min(__builtin_popcount(S),k-__builtin_popcount(S));
		}
	}
	printf("%d",dp[(1<<k)-1]);
	return 0;
}
```

---

## 作者：do_while_true (赞：7)

状压 dp + 费用提前计算。

考虑假如已经确定好了选出那些数（称作标记点），计算一下代价。

毛估估贪心就是先让它们尽量靠中间聚在一起，然后内部再算算逆序对。

尝试把这个东西均摊到每一个位置上，首先是让它们聚在标记点的中位数附近，那么每一个非标记点的代价就是左右两侧标记点个数的 $\min$（有这么多标记点要跨过它）。

对于标记点内部的交换，那就是算下逆序对。

这里要将代价均摊到每一个位置上是为了方便 dp 的过程中每加入一个点来计算代价，比较类似费用提前计算的思想。

从前往后枚举 $i$，设 $f_S$ 为考虑标记点集合是 $S$ 的代价，转移的时候枚举当前这个是否是标记点：

- 标记点：代价为以它为结尾的逆序对个数；
- 非标记点：$\min(\operatorname{popcount}(S),k-\operatorname{popcount}(S))$，左右两侧标记点个数的 $\min$．


[Code](https://atcoder.jp/contests/arc126/submissions/26044778)

---

## 作者：5k_sync_closer (赞：2)

设最后连续的 $1\dots k$ 为关键点。

可以发现，一定有一种最优解是，先把关键点交换到一起，再把关键点排序。

第一步把关键点交换到一起，对于每个非关键点，都有把其左的关键点移到其右，把其右的关键点移到其左两种方案，则其贡献为其两边关键点数之 $\min$。

第二步把关键点排序，每个关键点的贡献即为其形成的逆序对数，钦定其为值较小的一个。

设 $f_{i,S}$ 为在 $a_{[1,i]}$ 中选定值 $\in S$ 的关键点，$a_{[1,i]}$ 的贡献和最小值。

考虑从 $f_{i-1}$ 转移到 $f_i$，分类讨论 $a_i$ 是否关键点：

- $a_i$ 为关键点，则 $\forall S|a_i\notin S,f_{i,S\cup\{i\}}\gets\min\{f_{i,S\cup\{i\}},f_{i-1,S}+|S\cap(a_i,\infty)|\}$。
- $a_i$ 为非关键点，则 $\forall S,f_{i,S}\gets\min\{f_{i,S},f_{i-1,S}+\min(|S|,k-|S|)\}$。

答案即为 $f_{n,\{x\in\mathbf{N}_+|1\le x\le k\}}$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, k, f[1 << 16];
int main()
{
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    scanf("%d%d", &n, &k);
    for (int i = 0, x; i < n; ++i)
    {
        scanf("%d", &x);
        --x;
        for (int S = (1 << k) - 1; ~S; --S)
            if (f[S] != 0x3f3f3f3f)
            {
                if (!(S & 1 << x))
                    f[S | 1 << x] = min(f[S | 1 << x], f[S] + __builtin_popcount(S & ~((1 << x) - 1)));
                f[S] += min(__builtin_popcount(S), k - __builtin_popcount(S));
            }
    }
    printf("%d", f[(1 << k) - 1]);
    return 0;
}
```


---

## 作者：Trump_ (赞：2)

我们这道题要用逆天的 dp 做（考场没想到），考试后也是请教了巨佬才明白。

题意有很多题解都讲的很好，就不在这里过多赘述了。

看到 $k \leq 16$ 的时候，我们可以想到用 $2^k$ 的时间复杂度来做，因此就会自然的想到状态压缩 dp。

我们设 $dp_{i,S}$ 表示转移到第 $i$ 个元素时，我们选取元素所构成的集合为 $S$，这时我们移动的次数为 $dp_{i,S}$。

我们会有两种情况转移过来：选或者不选。

- 选现在的 $a_i$，那么此时加入集合的花费即为比 $a_i$ 大的数的个数。但是可能 $a_i$ 转移到的状态有其他状态转移过来的更优解，所以要取 $ \min $。

- 若不选，我们要么将现在处理好的集合 $S$ 移到现在选的元素 $i$ 的后面，要么将未来可能会移过来的数的花费先加上，也就是先加上 $S$ 的补集的数的个数。这个的大概意思就是说将两边已经排好序的集合不断的向中间靠拢，这样才能保证花费最小。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

int n, k, a[1000000], dp[1000000];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", &a[i]);
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i <= n; ++ i) {
		int mask = (1 << (a[i] - 1)) - 1, bit = (1 << (a[i] - 1));
		for (int j = (1 << k) - 1; j >= 0; -- j) {
			if ((j & bit) == 0) {
				dp[j | bit] = min(dp[j | bit], dp[j] + __builtin_popcount(j & (~mask)));
			}
			//若能选，就比较一下 
			dp[j] = dp[j] + min(__builtin_popcount(j), k - __builtin_popcount(j));
			//将不选的情况更新 至于为什么不是else 因为我们选了比较的情况下，我们也可以重新选择不选 
		}
	}
	cout << dp[(1 << k) - 1] << endl;
	return 0;
} 
```

---

## 作者：Rolling_star (赞：1)

首先可以考虑对于最后组成连续 $k$ 个数的 $k$ 项，一定是先聚集在一个地方然后冒泡排序，所以这个交换次数可以拆成聚集在一起需要的次数和冒泡排序的次数（也就是逆序对个数）。

设状态 $f_{i,S}$ 表示考虑到第 $i$ 项，最终的 $k$ 个数情况为 $S$，则我们对于每个数有两种转移方式：

1. $i$ 作为最后的 $k$ 个数出现，其贡献为 $i$ 作为末尾的逆序对数目。
2. $i$ 不作为最后的 $k$ 个数出现，那么因为最后 $k$ 个数要聚集在一起，所以要不就是 $i$ 左边的最终项全到 $i$ 右边，要么就是反过来，所以这个贡献为 $\min(\operatorname{popcount}(S),k-\operatorname{popcount}(S))$。

然后发现倒序枚举 $S$ 可以滚掉一位，时间复杂度为 $O(2^kn)$。

```cpp
#include<bits/stdc++.h>
#define N 205
#define bitcnt __builtin_popcount
#define inf 0x3f3f3f3f
using namespace std;

int n,k,a[N],f[1<<16],ans=inf,range;
vector<int> vec[N];

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) scanf("%d",a+i),a[i]--;
    memset(f,0x3f,sizeof(f));
    f[0]=0;range=(1<<k)-1;
    for(int i=1;i<=n;i++){
        for(int j=range;j>=0;j--){
            int cnt=bitcnt(j);
            if(!(j&(1<<a[i]))) f[j|(1<<a[i])]=min(f[j|(1<<a[i])],f[j]+bitcnt(j&(~((1<<a[i])-1))));
            f[j]+=min(cnt,k-cnt);
        }
    }
    cout<<f[range];
}
```

---

## 作者：User_Unauthorized (赞：1)

## 题意
给定一个有 $N$ 个正整数的序列 $A=(A_1,A_2,\cdots,A_N)$，且 $A_i \in \left[1,K\right]$。

你可以对这个序列做如下操作若干次。
> 交换两个相邻的元素，也就是选出 $i$ 和 $j$ 满足 $\lvert i - j\rvert = 1$ 并交换 $A_i$ 和 $A_j$。

找到最小的操作数使 $A$ 满足如下条件。
> $A$ 包含 $(1,2,\cdots,K)$ 作为一个相接的子序列，也就是对于任意正整数 $n \le N−K+1$ 满足 $A_n=1,A_{n+1}=2,\cdots,A_{N−K+1}=K$。

$2 \le K \le 16, K \le N \le 200$。

## 题解

设 $f_{i,S}$ 表示在前 $i$ 个元素中选取的数字构成集合 $S$ 并将其按序排列并将其末尾元素移动到 $i$ 的最小操作次数。

转移的话考虑两种情况：
- 将数 $A_i$ 加入集合 $S$，那么贡献为当前集合中比 $A_i$ 大的数的个数，即逆序对个数；
- 不将数 $A_i$ 加入集合 $S$，那么贡献可以考虑将在 $S$ 中的数全部右移或将未在 $S$ 中的数全部左移，两种操作方案取 $\min$ 即可。

复杂度为 $\mathcal{O}(n2^k)$，可以通过本题。

## Code
```cpp
//D
#include <bits/stdc++.h>

typedef int bitType;
typedef int valueType;
typedef std::vector<valueType> ValueVector;

typedef std::function<valueType(bitType)> BitCountFunction;

constexpr valueType MAX = INT_MAX >> 1;

int main() {
    valueType N, K;

    std::cin >> N >> K;

    bitType const S = (1 << K) - 1;

    ValueVector source(N);

    for (auto &iter: source)
        std::cin >> iter;

    BitCountFunction count = [](bitType n) -> valueType {
        return __builtin_popcount(n);
    };

    ValueVector dp(S + 1, MAX);

    dp[0] = 0;

    for (valueType i = 0; i < N; ++i) {
        bitType const mask = (1 << (source[i] - 1)) - 1, bit = 1 << (source[i] - 1);

        for (bitType j = S; j >= 0; --j) {
            if ((j & bit) == 0)
                dp[j | bit] = std::min(dp[j | bit], dp[j] + count(j & (~mask)));

            dp[j] = dp[j] + std::min(count(j), K - count(j));
        }
    }

    std::cout << dp[S] << std::endl;

    return 0;
}
```

---

## 作者：_luanyi_ (赞：0)

虽然这道题做法已经被说烂了，但是作为一道卡了我半个小时的 ARC 的 D，我想分享一下我的做题思路。

首先，这道题如果保证了 $A$ 是排列就是一个简单题了。发现 $K$ 很小，可能可以往状压方向去想。

一开始我试图使用 $dp_{i,S}$ 表示以 $i$ 位置开头接下来有一个 $[1,K]$ 的子集 $S$ 所需要的最小代价。但是这样难以操作，因为没有保留数与数之间的位置关系，以及这是一个看似有后效性的 dp，看起来没什么前途。

尝试手模样例以获得一些思路。发现对于样例 $3$，为了达到 $5$ 次操作需要将唯一的一个 $1$ 一直向左移动，两次移动后 $1$ 到了位置 $5$，发现出现了排列 $a_{[3,6]}=[3,2,1,4]$。接下来的三次操作就是对于这个排列冒泡排序，发现操作次数恰好就是逆序对数量。

于是我们有了一些简单的观察后，可以有以下想法：

首先，最优的答案大概是两边的一些数集中到中间某个位置形成一个排列，然后再在排列内进行冒泡排序。

其次，如果要集中到位置 $i$，以数字 $2$ 为例，左边有两个 $2$（比如，$i=5,a_{[1,5]}=[1,2,3,2,1]$），不一定是只选择靠近 $i$ 的那个 $2$ 是最优的，因为可能使得逆序对增加，反而不优。

所以，如果使用 dp，我们要试图把移动的距离和逆序对数量这两个会印象到操作数量的信息一起刻画进去。

发现先集中再排序和边集中边排序是等价的，原因就是排序的操作数量就是逆序对数量，逆序对数量不变操作数量不变。

因此，状态就呼之欲出了。

---

令 $f_{i,S}$ 表示只考虑了前 $i$ 位，$a_{[i-|S|+1,i]}$ 的数恰好是集合 $S$ 中的所有数的升序排列，所需要的最小操作次数。

考虑怎么求这个东西。

对于第 $i$ 位，如果不选这个数，那么 $f_{i,S}=f_{i-1,S}+|S|$，其中 $|S|$ 的贡献就是 $a_{[i-|S|+1,i]}$ 中的每一个数都要往后移动一位。

如果选第 $i$ 位，那么首先需要有 $a_i\in S$，那么 $f_{i,S}=f_{i-1,S\backslash\{i\}}+\sum\limits_{j\in S}[j>i]$，其中 $\sum\limits_{j\in S}[j>i]$ 的贡献就是把 $a_i$ 加进去时为了使 $S$ 中的数升序排列所需要花费的操作次数，也即，逆序对数量。

那么这样我们就可以在 $O(n2^k)$ 的复杂度内求出 $f$ 了。

类似地我们也可以定义 $g_{i,S}$ 表示只考虑了后 $i$ 位，$a_{[i,i+|S|-1]}$ 的数恰好是集合 $S$ 中的所有数的升序排列，所需要的最小操作次数。转移是类似的。

考虑如何计算答案。发现有了 $f,g$ 之后我们可以很轻松的计算出排列集中在位置 $i$ 的答案。

枚举左边的集合以及右边的集合，答案就是 $\min\limits_{S_r=U\backslash S_l}\left(f_{i,S_l}+g_{i+1,S_r}+\sum\limits_{l\in S_l}\sum\limits_{r\in S_r}[l>r]\right)$，其中 $U=[1,K]$。后面那部分算的是合并序列时逆序对的贡献。



计算单个 $i$ 的答案复杂度是 $O(2^KK^2)$ 的，瓶颈在于逆序对计数，容易被优化至 $O(2^KK)$。

那么只需要对于每一个 $i$ 都枚举一遍就好了，复杂度 $O(n2^KK)$，恰好可过。听说可以使用高妙的位运算把 $K$ 去掉，但没必要。其实是我不会。

```cpp
#define fq(i,a,b) for (int i = (a); i <= (b); i++)
#define fnq(i,a,b) for (int i = (a); i < (b); i++)
#define nfq(i,a,b) for (int i = (a); i >= (b); i--)

#define int ll
typedef long long ll;

const int maxn = 210;
int n, k;
int a[maxn];
int bitcnt(int x) {return __builtin_popcount (x);}
int f[maxn][1 << 16], g[maxn][1 << 16];
signed main () {
	cin >> n >> k;
	fq (i, 1, n) cin >> a[i];
	fq (i, 1, n) --a[i];
	memset (f, 0x3f, sizeof f);
	f[0][0] = 0;
	fq (i, 1, n) {
		fnq (st, 0, 1 << k) {
			f[i][st] = min (f[i][st], f[i-1][st] + bitcnt(st));
			if ((st >> a[i])&1) {
				int sst = st ^ (1 << a[i]);
				int x = f[i-1][sst];
				fnq (j, a[i]+1, k) if ((sst >> j) & 1) ++x;
				f[i][st] = min (f[i][st], x);
			}
		}
	}
	memset (g, 0x3f, sizeof g);
	g[n+1][0] = 0;
	nfq (i, n, 1) {
		fnq (st, 0, 1 << k) {
			g[i][st] = min (g[i][st], g[i+1][st] + bitcnt(st));
			if ((st >> a[i])&1) {
				int sst = st ^ (1 << a[i]);
				int x = g[i+1][sst];
				fnq (j, 0, a[i]) if ((sst >> j) & 1) ++x;
				g[i][st] = min (g[i][st], x);
			}
		}
	}
	int ans = 1e18;
	fnq (i, 1, n) {
		fnq (stl, 0, 1 << k) {
			int str = (1 << k) - 1 - stl;
			int cnt = 0, cc = 0;
			fnq (j, 0, k) if ((str >> j) & 1) ++cc;
			else cnt += cc;
			ans = min (ans, f[i][stl] + g[i+1][str] + cnt);
		}
	} cout << ans << endl;
	return 0;
}
```

略显繁琐，在众多精简的题解中显得幽默。

---

## 作者：Glacial_Shine (赞：0)

# 思路

首先我们看看假设选中 $m$ 个数后的答案。

我们首先现将 $m$ 个数移动到一起，在将他们重新排序。

我们知道，$m$ 个数移在一起时，当位于中间的那个数不动时交换次数最少，于是可以列出式子（$c_i$ 是点 $i$ 的位置）：

$$
\sum_{i = 1}^m |c_{mid} + mid - c_i + i|
$$

我们可以将上面的式子改成如下形式：

$$
-\dfrac{2}{m}\cdot mid + (m \bmod 2) \cdot c_{mid} + \sum_{i = 1}^m c_i^{-1^{i \leq mid}}
$$

此时我们就可以用状压 DP 来做了。

我们首先枚举每个数，在枚举选上这个数后的情况，在 DP 的过程中计算出下面的式子的求和公式里面的值，前面的为常数，并且在加上逆序对个数就可以了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, mid, a[205], f[205][1 << 18], INF = 1e9;
int solve(int state, int i) {
    int sum = 0, t = 0, t1 = 0;
    //t是目前选了多少个数，t1选了的树中比这个数要小的数。
    for (int j = 0; j < m; j++) {
        if (state & (1 << j))
            t++;
        if (a[i] - 1 == j)
            t1 = t;
    }
    return i * (t <= mid ? -1 : 1) + i * (m & 1) * (mid == t) + (t - t1);
    //此时的i就是c值，于是我们把他带进去式子就可以了。
}
int main() {
    scanf("%d%d", &n, &m), mid = (m + 1) / 2;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    memset(f, 36, sizeof(f));
    for (int i = 0; i <= n; i++) f[i][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 1 << m; j++)
            f[i][j] = min(j & (1 << (a[i] - 1)) ? f[i - 1][j ^ (1 << (a[i] - 1))] + solve(j, i) : INF, f[i - 1][j]);
    printf("%d", f[n][(1 << m) - 1] - m / 2 * mid);
    return 0;
}
```


---

## 作者：ZillionX (赞：0)

# Description

给定一个长度为 $n$ 的序列 $a$，其中 $a_i \in [1,k]$，每次可以交换相邻数，求最小的操作次数使得序列存在子区间 $[1, \cdots ,k]$。

$n \le 200, k \le 16$，时限 2s。

# Solution

我们考虑假如已经钦定了区间范围和要选的数的下标序列（单增）。则答案由两部分组成，首先是移到对应位置的距离，其次是逆序对的贡献。

现在我们设 $f_{i,S}$ 表示已经考虑到了第 $i$ 个数，目前已经钦定了集合 $S$ 中的数的最小操作次数。

转移的话同样分两部分：

- 加入 $a_i$，则我们需要加上比 $a_i$ 大的数的逆序对贡献。

- 不加入 $a_i$，则我们可以将 $S$ 中的数整体右移或未在 $S$ 中的数整体左移，取 $\min$ 即可。

时间复杂度 $\mathcal O(n 2^k)$。

# Code

```cpp
const int S=(1<<16)+5,inf=1e9;
int n,m,f[S];
int main() {
	mes(f,0x3f);
	scanf("%d%d",&n,&m);
	f[0]=0;
	for (int i=0;i<n;i++) {
		int x;
		scanf("%d",&x);
		x--;
		for (int j=(1<<m)-1;j>=0;j--) {
			if (f[j]>=inf) continue;
			if (!(j>>x&1)) cmn(f[j|(1<<x)],f[j]+btc(j&(~((1<<x)-1))));
			f[j]+=min(btc(j),btc(j^((1<<m)-1)));
		}
	}
	printf("%d",f[(1<<m)-1]);
	return 0;
}
```

---

## 作者：hello_world_djh (赞：0)

又来给 [do_while_true](https://www.luogu.com.cn/user/223298) 大佬交作业了，所以本篇题解仅仅是对 [该篇题解](https://www.luogu.com.cn/blog/dowhiletrue/solution-at-arc126-d) 进行补充说明的。

本篇题解适用于像我这样的小萌新，那篇题解适合大佬食用。

Part 1：

为什么我们要用状压 dp？

~~因为题解里面写了要用。~~

因为我们要进行对答案集合内的情况取最小值的操作，可以使用 dp。并且 $K \le 16$ 但 $N \le 200$。所以肯定是使用状压 dp 或者倍增优化 dp。又发现是对一个集合里面的数进行的操作，且 $2^K$ 的数组能开下，所以应该是状压 dp。

Part 2：

状态的设计和转移。

~~跟着题解设计就行。~~

我们设 $f_S$ 表示已经将 $S$ 这个集合里的数字将题目要求的顺序排好的代价。我们插入一个新的数，她既可能去前面作为前面的排列中的一个数，也有可能去后面作为后面的排列中的这个数。对于集合整体，既可以将在这个集合里的数汇总起来，也可以将不在这个集合的数交换出去。

综上所述，我们可以得到这样的式子：

$f(S \operatorname{or} 2^x) = \min\{f(S \operatorname{or} 2^x),f(S) + \operatorname{popcount}(s \operatorname{and} (\operatorname{not}(2^x - 1)))\}$

$f(S) = f(S) + \min\{\operatorname{popcount}(S),k - \operatorname{popcount}(S)\}$

Part 3：

上代码！！！！

```cpp
#include <bits/stdc++.h>

namespace hello_world_djh {
    template <typename T>
    T read() {
        T x = 0, f = 1;
        char ch = getchar();
        for (; ch < '0' || ch > '9'; ch = getchar())
            if (ch == '-')
                f = ~f + 1;
        for (; ch >= '0' && ch <= '9'; ch = getchar())
            x = (x << 3) + (x << 1) + (ch ^ '0');
        return x * f;
    }

    const int N = 210, K = 16, INF = 0x3f3f3f3f;
    int n = read<int>(), k = read<int>();
    int f[(1 << K) + 10];
    #define sum __builtin_popcount

    int main() {
        for (int i = 1; i <= (1 << k) - 1; i++)
            f[i] = INF;
        for (int i = 1; i <= n; i++) {
            int x = read<int>() - 1;
            for (int j = (1 << k) - 1; ~j; j--)
                if (f[j] != INF) {
                    if (!(j & (1 << x)))
                        f[j | (1 << x)] = std::min(f[j | (1 << x)], f[j] + sum(j & (~((1 << x) - 1))));
                    f[j] += std::min(sum(j), k - sum(j));
                }
        }
        printf("%d\n", f[(1 << k) - 1]);
        return 0;
    }
};

int main() {
    hello_world_djh::main();
    return 0;
}
```

---

