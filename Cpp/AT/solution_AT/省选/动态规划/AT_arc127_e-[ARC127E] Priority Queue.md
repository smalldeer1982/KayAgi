# [ARC127E] Priority Queue

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc127/tasks/arc127_e

長さ $ A+B $ の整数列 $ (X_1,X_2,\cdots,X_{A+B}) $ が与えられます． $ X $ はちょうど $ A $ 個の $ 1 $ とちょうど $ B $ 個の $ 2 $ を含みます．

すぬけくんは集合 $ s $ を持っており，最初 $ s $ は空です． 彼は今から，$ A+B $ 回の操作を行います． $ i $ 回目の操作は以下のような行動です．

- $ X_i=1 $ の時: $ 1\ \leq\ v\ \leq\ A $ を満たす整数 $ v $ を選び，$ s $ に追加する． ただし，今までの操作で選んだことのある整数は $ v $ として選べない．
- $ X_i=2 $ の時: $ s $ の中で最大値となる要素を削除する． なお，この操作の直前に $ s $ が空でないことは入力から保証される．

最終的な $ s $ としてありうる集合は何通りあるでしょうか？ 答えを $ 998244353 $ で割った余りを求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ A\ \leq\ 5000 $
- $ 0\ \leq\ B\ \leq\ A-1 $
- $ 1\ \leq\ X_i\ \leq\ 2 $
- $ X_i=1 $ を満たす $ i $ がちょうど $ A $ 個存在する．
- $ X_i=2 $ を満たす $ i $ がちょうど $ B $ 個存在する．
- $ X_i=2 $ の操作を行う直前で $ s $ は空ではない．
- 入力される値はすべて整数である．

### Sample Explanation 1

最終的な $ s $ としてありうる状態は，$ s=\{1,2\},\{1,3\} $ の $ 2 $ 通りです． 例えば，以下のように操作すると，最終的に $ s=\{1,3\} $ となります． - $ i=1 $: $ s $ に $ 2 $ を追加する． - $ i=2 $: $ s $ に $ 1 $ を追加する． - $ i=3 $: $ s $ から $ 2 $ を削除する． - $ i=4 $: $ s $ に $ 3 $ を追加する．

## 样例 #1

### 输入

```
3 1
1 1 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
20 6
1 1 1 1 1 2 1 1 1 2 1 2 1 2 1 2 1 1 1 1 2 1 1 1 1 1```

### 输出

```
5507```

# 题解

## 作者：Gold14526 (赞：8)

这篇题解将会以思维过程讲述，较为自然地得出结论。

$\rm Problem:$[Priority Queue](https://www.luogu.com.cn/problem/AT_arc127_e)

$\rm Difficulty:2678$

### 题意

有一个初始为空的大根堆，给出一个长度为 $n+m(0\le n<m\le5000)$ 的操作序列，其中有 $n$ 个 $1$，$m$ 个 $2$，从前往后遍历该序列，对一个 $1\sim n$ 的排列 $p$，按照操作序列进行以下操作：

- 若操作序列该位为 $1$，将 $p$ 的下一个数加入大根堆。
- 若操作序列该位为 $2$，删除堆顶。

求对于所有的 $p$，操作完之后，堆中的元素集合有多少种可能，对 $998244353$ 取模。

### 做法

首先进行一个不难的转化：考虑求被删除的集合有多少种可能。

于是我们每次删除，相当于把原先被保留下来的集合中最大的数，放入被删除的集合中。

考虑对于 $2$ 操作，直接删除操作序列中的 $1$，具体的，删除其左边离它最近的未被删除的 $1$。

于是考虑在新的序列中操作变为了以下两种：

- 若操作序列该位为 $1$，将一个数加入保留集合。
- 若操作序列该位为 $2$，将一个比保留集合里所有数都大的数放入删除集合。

现在也就是给排列 $p$ 打上标记，$p$ 中每个标记 $2$ 的位置比它前面所有标记 $1$ 的位置都大，假设其前面有 $cnt$ 个 $1$，那么这个数的取值范围就是 $[cnt+1,n]$。

避免算重，钦定标记为 $2$ 的数字单调递增。

这样，对于每一个标记为 $2$ 的位置，它比前面所有数都大，如果它的下标为 $x$，则它的取值范围为 $[x,n]$。

现在，这题就变成了一个经典题，有一个递增序列，每个数在 $[x_i,n]$ 间，求这个序列有几种可能。

考虑设 $dp_{i,j}$ 表示填到第 $i$ 个数，第 $i$ 个数为 $j$ 的方案数，显然有：

$$dp_{i,j}=\sum\limits_{j+1\le k\le n}dp_{i+1,k}$$

可以前缀和优化，计算出 $dp_{1,i}$ 的和即为答案，时间复杂度 $O(nm)$。

### 证明

发现我们上面的说法很不严谨，毕竟这只是思维过程，很多结论都是先感性理解后面再去证的，这篇题解的过程也是如此。

#### 证明：对于每一个 $2$，删除其左边最靠近它的未被删除的 $1$ 一定最优。

如果被选择的 $1$ 与这个 $2$ 中间隔了 $k$ 个 $2$，那么被选择的数最多也只能是前缀的第 $k+1$ 大值，相比之下，两者中间隔的 $2$ 越少，约束越小，方案更多，其左边最靠近它的未被删除的 $1$ 满足间隔的 $2$ 最少的要求。

#### 证明：只计算递增序列不会漏算。

假设序列不递增，有两个数 $i,j$ 满足 $i$ 在前，$j$ 在后，且 $i>j$，对应的 $x$ 分别为 $x_i,x_j$，于是，有 $i>j,x_i\le i,x_j\le j$，因为 $x$ 递增，所以还有 $x_i<x_j$。

于是有 $x_i<j,x_j<i$，交换 $i,j$ 仍然合法，经过若干次交换则一定能把序列排序，所以一定会被算到。

### 代码

```cpp
#include<bits/stdc++.h>
#define cint const int
#define iint inline int
#define ll long long
#define cll const long long
#define ill inline long long
using namespace std;
iint read()
{
	int num=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+(ch-'0');
		ch=getchar();
	}
	return num;
}
cint mod=998244353;
int n,m,t;
int a[10001],l[5001],dp[5001][5002];
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	m=read();
	for(int i=1;i<=n+m;++i)
	{
		a[i]=read();
	}
	for(int i=n+m;i;--i)
	{
		t+=a[i]-1;
		if(t&&a[i]==1)
		{
			a[i]=0;
			--t;
		}
	}
	n+=m;
	m=0;
	for(int i=1;i<=n;++i)
	{
		t+=!!a[i];
		if(a[i]==2)l[++m]=t;
	}
	n-=m;
	for(int i=1;i<=n+1;++i)
	{
		dp[m+1][i]=1;
	}
	for(int i=m;i>=1;--i)
	{
		for(int j=l[i];j<=n;++j)
		{
			dp[i][j]=dp[i+1][j+1];
		}
		for(int j=n;j>=1;--j)
		{
			dp[i][j]=(dp[i][j]+dp[i][j+1])%mod;
		}
	}
	printf("%d",dp[1][1]);
	return 0;
}
```

---

## 作者：Phartial (赞：4)

首先我们每次加入的数必定是一个 $1\sim a$ 的排列，但从排列角度考虑的话非常复杂，因为 $s$ 是一个集合。所以我们考虑最后能剩下哪些数。

考虑最后剩下的集合为 $\{a_i\}$，其中 $a_i<a_{i+1}$，显然这个集合里面的元素个数为 $A-B$。

那么我们会发现一件事情：我们按上升序依次留下这些数是最优的。

考虑相邻两个数 $a_i,a_{i+1}$，若以 $a_{i+1},a_i$ 的顺序可以留下这些数，那么：

- 由于 $a_{i+1}>a_i$，将 $a_i$ 调到 $a_{i+1}$ 的位置必定更容易被留下。
- 由于 $a_{i+1}$ 出现在 $a_i$ 前面，因此若 $a_{i+1}$ 在前面可以被留下，那么放到 $a_i$ 的位置也必定可以留下。

于是我们最后留下的数必定是有序的，所以我们如果已经确定了前 $i$ 个数，第 $i+1$ 个数的下界就对应的被确定了（$a_i<a_{i+1}$）。因为在一个位置填上小一点的数必定比大一点的数更容易留下，所以 $a_{i+1}$ 的值域是一段连续的区间，我们只需要知道上界即可。

考虑贪心，我们为了让每一位上的数尽可能的大，肯定要让大的数尽量留在后面，所以按从小到大的顺序依次加数即可。

最后就是一个简单 dp 了。

```cpp
#include <atcoder/all>
#include <iostream>

using namespace std;
using LL = atcoder::modint998244353;

const int kN = 5001;

int a, b, r[kN], t;
LL f[kN][kN], s[kN][kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> a >> b;
  for (int i = 1, v, j = 0; i <= a + b; ++i) {
    cin >> v;
    if (v == 1) {
      r[++t] = ++j;
    } else {
      --t;
    }
  }
  f[0][0] = 1;
  for (int i = 0; i <= a; ++i) {
    s[0][i] = 1;
  }
  for (int i = 1; i <= a - b; ++i) {
    for (int j = 1; j <= r[i]; ++j) {
      f[i][j] = s[i - 1][j - 1];
      s[i][j] = s[i][j - 1] + f[i][j];
    }
    for (int j = r[i] + 1; j <= a; ++j) {
      s[i][j] = s[i][r[i]];
    }
  }
  cout << s[a - b][r[a - b]].val();
  return 0;
}
```


---

## 作者：wanggk (赞：3)

[cnblogs](https://www.cnblogs.com/wanggk/p/-/ARC127E)

## 题解

每个**权值**的**最终状态**只有删与不删，我们只需要统计有多少最终状态是合法的。

将操作序列从左往右排开为 $A$ 个点 $B$ 条竖线的序列：

![](https://cdn.luogu.com.cn/upload/image_hosting/qjqfr60u.png)

点被竖线分成了若干段，同一段内交换顺序不影响**最终状态**，于是不妨把红点放在每一段的最后一个。这样上面每个**位置**的颜色都是确定的。

![](https://cdn.luogu.com.cn/upload/image_hosting/sqcc79vt.png)

- 一个**球的序列**合法当且仅当，对于每个红球，它比前面的黄球都大。
- 一种**对 $1 \sim n$ 球的染色方案**合法，当且仅当任意安排同色球的顺序，**存在**一个**球的序列**合法。

所以我们要 Check 一种染色方案，只需要它的最优的球的序列合法就行了，最优的显然是排序后的。

- 贪心地，将两种颜色的球分别排序：$Y_1 \leq Y_2 \leq \cdots Y_{A-B}$，$R_1 \leq R_2 \leq \cdots \leq R_{B}$（限制一）。
- 对于每个红球，它比前面的黄球都大（限制二）。
- 权值 $1 \sim A$ 恰好出现一次（限制三）。

每种合法的染色方案和满足上述限制的序列一一对应，所以最终转化为统计以上序列的数量。

DP 非常好做，设 $f_{i,j}$ 表示考虑了 $i \sim n$ 的权值，已经染了 $R_j \sim R_B$ 的红球。

考虑 $i-1$ 删不删（省略了转移条件）：

- 权值 $i-1$ 染红，成为红球 $R_{j-1}$：$f_{i-1,j-1} \leftarrow f_{i,j}$。
- 权值 $i-1$ 染黄：$f_{i-1,j} \leftarrow f_{i,j}$。

最终答案为 $f_{1,1}$。

## 代码

[Atcoder 提交记录](https://atcoder.jp/contests/arc127/submissions/64642831)

```cpp
#include<bits/stdc++.h>
#define For(i,il,ir) for(int i=(il);i<=(ir);++i)
#define Rof(i,ir,il) for(int i=(ir);i>=(il);--i)
using namespace std;
typedef long long ll;
void qadd(ll &x,ll y){ x=(x+y>=998244353)?(x+y-998244353):(x+y); }
const int N=5005;

ll f[N][N];
int m,A,B;
int q[N],pos[N],t,n,x;
signed main()
{
	scanf("%d%d",&A,&B);
	For(i,1,A+B){
		scanf("%d",&x);
		if(x==1) q[++t]=++n;
		else pos[++m]=q[t--];
	}
	sort(pos+1,pos+1+m);
	f[A+1][m+1]=1ll;
	Rof(i,A+1,2)
		Rof(j,m+1,1){
			if(j>1) qadd(f[i-1][j-1],f[i][j]);
			if(i-1>pos[j-1]) qadd(f[i-1][j],f[i][j]);
		}
	printf("%lld\n",f[1][1]);
	return 0;
}
```

---

## 作者：APJifengc (赞：3)

题目要求最后有多少种不同的情况，而这个东西正着考虑不好考虑，我们尝试以每种最终局面倒过来考虑是否合法。

那么第一个操作就从加任意一个数变成了删任意一个数，第二个操作从删最大值变成了加入一个最大值。这个最大值必须是最终局面中没有的数。

那么我们可以把没有选择的数看作一个空位。这个局面合不合法，就取决于每次第二个操作是否有一个空位大于当前的所有数。

那么我们肯定删数时贪心的删最大的数，而放数的时候一定尽可能放最小的。我们注意到，如果我们放了若干个数，那么我们删数时就必须先放的数然后才能接着删最终局面中的数。

那么我们就可以设计出一种贪心的方式：

先把 $x_i$ 翻转，我们令当前剩余的空位有 $x$ 个，第 $k$ 个数后面的空位有 $a_k$ 个，当前最大的没被删除的最终局面中的数为第 $k$ 个，当前没有被删除的放入的数有 $c$ 个。那么我们有以下流程：

1. 如果 $x_i=1$，那么：
	- 若 $c=0$，则令 $x \gets a_k - a_{k - 1}, k \gets k - 1$；
	- 否则，令 $c \gets c - 1$；
2. 如果 $x_i=2$，那么：
	- 若 $x \ge 1$，那么令 $x \gets x - 1, c \gets c + 1$；
	- 否则，该局面不合法。

我们发现，每一步时 $c$ 的值是不受最终局面中的数的影响的，那么也就是说每一步时 $x$ 的具体值是可以用最后局面中的数表示出来的。那么我们模拟以上过程，就能确定出每一个数后面的空位的最小值是多少。然后，我们就可以直接 DP 出有多少种空位的方案了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005, P = 998244353;
int f[MAXN][MAXN];
int a, b, x[2 * MAXN];
int g[MAXN];
int main() {
    scanf("%d%d", &a, &b);
    for (int i = 1; i <= a + b; i++) {
        scanf("%d", &x[i]);
    }
    reverse(x + 1, x + 1 + a + b);
    int c = 0, d = 1, k = a - b;
    for (int i = 1; i <= a + b; i++) {
        if (x[i] == 1) {
            if (c) {
                c--;
            } else {
                k--;
            }
        } else {
            g[k] = max(g[k], d);
            d++, c++;
        }
    }
    for (int i = 0; i <= b; i++) 
        f[a - b + 1][i] = 1;
    for (int i = a - b; i >= 1; i--) {
        for (int j = g[i]; j <= b; j++) {
            if (j) f[i][j] = f[i][j - 1];
            f[i][j] = (f[i][j] + f[i + 1][j]) % P;
        }
    }
    printf("%d\n", f[1][b]);
    return 0;
}
```

---

## 作者：Rosabel (赞：2)

不难吧。

若将 $[1,a]$ 的元素降序依次填进序列里，那其实问题就变成将元素投到未删除的 $1$ 上，并消掉这个 $1$，如果右边有 $2$，那就同步消掉最右边的 $2$，同时为这个元素标记为 $1$，问标记的形式能有多少种。

发现对于每一个元素实际就两种操作：未标记和标记。未标记，说明落在了目前最靠右的 $2$ 的右边；标记，说明落在了目前最靠右的 $2$ 的左边。发现对于标记一侧的操作只要满足之前标记过的数 $\lt b$ 即可，也就是只需要记录标记过的数的个数，具体位置无所谓。而对于未标记的数，我们希望它的可操作范围尽可能越大越好（能覆盖到所有的合法位置），一种贪心策略就是标记操作恰好能消掉最靠右的 $2$。所以这时上限只需要取到 $g_i$ 即可（即删掉后面 $i$ 个 $2$ 的最多 $1$ 可放置位置。易得 $g_i$ 转移式：
$$
g_i=\max(g_{i-1}+1,sum_{i+1})
$$
其中 $sum_{i}$ 表示从右往左数第 $i$ 个 $2$ 左边 $1$ 的个数。特别地，令 $g_{b+1}=a$。注意上述式子要对 $g_{i-1}+1$ 取 $\max$ 是因为有可能出现连续若干个 $2$ 连起来的情况，可能需要消掉相对位置很远的一个 $1$。

然后就是暴力 dp。状态 $\Theta(n^2)$，转移 $\Theta(1)$。总复杂度 $\Theta(n^2)$。

[code](https://atcoder.jp/contests/arc127/submissions/59094707)

---

## 作者：CmsMartin (赞：1)

[更好的阅读体验](http://www.cmsblog.top/archives/arc127epriorityqueue)

## 题目描述

[题目传送门](https://atcoder.jp/contests/arc127/tasks/arc127_e)

## 思路

正着做比较困难，反着来。假设 $\{a\}$ 是我们最后剩下来的集合。

可以发现一个结论：**$a$ 是一个单调上升序列肯定不劣。**

这样我们可以从头开始加入数字。每一此 `2` 操作实际上可以与其之前的 `1` 操作抵消。所以我们无需考虑二操作。

由于我们可以证明 $a$ 单调升。可以设 $f_{i,j}$ 表示 $\{a\}$ 第 $i$ 位填 $1\sim j$ 的时候的答案。

显然有：

$$
f_{i,j} = f_{i-1,j-1} + f_{i,j-1}
$$

时间复杂度：$\mathcal{O}(ab)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 5010;
const ll mod = 998244353;

int n;
int c[MAXN], tot, cnt, a, b;
ll sum[MAXN][MAXN];

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> a >> b;
	for (int i = 1; i <= a + b; i++) {
		cin >> c[++tot];
		if (c[tot] == 1) {
			c[tot] = ++cnt;
		} else {
			tot--;
			tot--;
		}
	}
	for (int i = 0; i <= a; i++) sum[0][i] = 1;
	for (int i = 1; i <= a - b; i++) {
		for (int j = 1; j <= c[i]; j++) {
			sum[i][j] = (sum[i][j - 1] + sum[i - 1][j - 1]) % mod;
		}
		for (int j = c[i] + 1; j <= a; j++)
			sum[i][j] = sum[i][c[i]];
	}
	cout << sum[a - b][c[a - b]] << endl;
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

首先两种方案本质不同等价于其最后保留的数不同，**等价于其删除的数不同**。于是可以将问题转化为对删除集合计数。

显然当执行到一个 $2$ 操作的时候，删除前面的哪个下标的 $1$ 操作都可以。于是我们可以钦定 $2$ 删除离其最近的一个没有删除的 $1$。

我们将这个操作序列改造一下：**让每一个 $2$ “吸收”掉其应该删除的那个 $1$**。这样操作就可以改成：当遇见一个 $1$ 时，将一个数加入保留集合。遇见 $2$ 时，把比当前保留集合还大的一个数加入删除集合。这本质上是延后计算所加的数，使前面在考虑决策的时候不会被后面的操作所干扰，没有后效性。

当保留集合与删数集合确定的时候，怎么安排才能使得限制更松？显然保留集合应该从小往大排序：当交换一对 $i<j,a_i>a_j$ 时，$<i$ 的删除数与 $>j$ 的删除数约束不会有变化，而中间的 $\ge a_i$ 的限制会变成 $\ge a_j$，更松了。

同理，删数集合也应该从小到大排序：交换 $i<j,b_i>b_j$ 时，$i$ 前 $j$ 后不变，而中间的 $a$ 限制从 $< b_j$ 变成了 $<b_i$，更松了。

考虑对删数集合进行 DP。令 $dp_{i,j}$ 为第 $i$ 个删数位置选择 $j$ 的方案数。显然两个“从小到大排序” 加上所有删数位置的数比所有之前的保留数大这两个限制就能够等价于所有的删数位置，它比所有前面的数大。其推论就是对于一个删数位置 $i$，如果其在原序列的位置为 $p_i$，则比其值小的数至少有 $p_i-1$ 个，并且其数 $b_{p_i} > b_{p_{i-1}}$。

于是可以列出转移方程：

$$dp_{i,j} = [j \ge p_i]\sum \limits_{k=1}^{j-1}dp_{i-1,k}$$

边界条件为 $dp_{1,i} = [i \ge p_1]$。前缀和优化即可做到 $O(n^2)$。

---

## 作者：Purslane (赞：0)

# Solution

比较简单的题目。

首先考虑告诉你要删掉一些数，你会怎么排。

显然，要删的数和不删的数都是升序排列的，不然调整会更优。

而如果一个要删的数第 $t$ 个被加入，这个数的大小一定要大于等于 $t$——因为它要大于所有在他之前的数。

而我们可以不妨设每次 $2$ 删掉的都是最后的、没有被删除的一个 $1$——显然如果存在一组合法的构造，一定可以通过调整实现每个 $2$ 删掉的是最后的 $1$。

所以我们得到了一组 $t$。问题转化为：对递增序列 $x$ 计数，满足 $x_i \ge t_i$。随便 DP 就是 $O(n^2)$ 的了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5000+10,MOD=998244353;
int n,m,lim[MAXN],dp[MAXN][MAXN],ok[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	int tot=0,rnk=0;
	stack<int> st;
	ffor(i,1,n+m) {
		int id;
		cin>>id;
		if(id==1) ++tot,st.push(tot);
		else ok[st.top()]=1,st.pop();
	}
	tot=0;
	ffor(i,1,n) if(ok[i]) ++tot,lim[tot]=i;
	else ++rnk;
	ffor(i,lim[m],n) dp[m][i]=1;
	roff(i,m-1,1) {
		roff(j,n,1) dp[i+1][j]=(dp[i+1][j]+dp[i+1][j+1])%MOD;
		ffor(j,lim[i],n) dp[i][j]=dp[i+1][j+1];
	}
	int ans=0;
	if(m) ffor(i,1,n) ans=(ans+dp[1][i])%MOD;
	else ans=1;
	cout<<ans;
	return 0;
}
```

---

## 作者：rizynvu (赞：0)

[我的博客](https://www.cnblogs.com/rizynvu/p/18298459)。

考虑转化一下，每个最后留下来的集合都相对的对应着一个被删除的集合。  
于是考虑去对被删除的数去计数。

然后贪心的，去让每一次 $2$ 操作删除的数都是前面加入中还剩下的最后加入的数（因为有的可能被前面的 $2$ 操作删了）。  
对于证明，考虑到如果不是剩下的最后加入的，那么中间可能会有 $2$ 操作截胡了，且把其调整到最后加入肯定不劣。

于是可以先把这些已经确定要被删去的 $1$ 操作删掉，被这个操作一起考虑到 $2$ 操作上。  
那么此时 $2$ 操作的定义就是把一个大于当前已有的数的集合的没选过的数加入到删除的集合里。

于是可以知道对于一个 $2$ 操作，其选的数一定会大于前面每个 $1$ 操作选的数。  
但是此时 $2$ 操作之间的大小关系还没确定，还是不是很好做。

但是，凭直觉去想一想，可以知道同样可以贪心的，让后面的 $2$ 选的数大于前面的 $2$ 选的数。  
证明考虑记第 $i$ 次 $2$ 操作选到的数为 $s_i$，那么如果有 $i < j, s_i > s_j$，那么肯定 $j$ 之前选的 $1$ 都没有 $s_j$ 大，因为 $i < j$ 于是让 $i$ 位置选 $s_j$ 肯定满足，因为又有 $s_i > s_j$ 所以 $j$ 位置选 $s_i$ 肯定也满足。

于是可以知道 $2$ 操作选的数需要大于所有前面操作选的数。  
记第 $i$ 次 $2$ 操作在操作序列中是第 $l_i$ 个，所以可以知道这次操作选的数的区间就是 $[l_i, a]$。

同时又有 $2$ 操作选的数是递增的，于是考虑 DP。  
设 $f_{i, j}$ 为第 $i$ 此 $2$ 操作选的数为 $j$ 的方案数，那么有转移 $f_{i, j} = \begin{cases} 0 & j < l_i\\ \sum\limits_{k = 0}^{j - 1} f_{i - 1, k} & j \ge l_i\end{cases}$。  
然后用个前缀和优化就可以了。

时间复杂度 $\mathcal{O}(ab)$。

```cpp
#include<bits/stdc++.h>
constexpr int mod = 998244353;
const int maxn = 1e4 + 10;
int x[maxn], l[maxn];
int f[maxn];
int main() {
   int a, b;
   scanf("%d%d", &a, &b);
   for (int i = 1; i <= a + b; i++)
      scanf("%d", &x[i]);
   for (int i = a + b, tot = 0; i; i--) {
      if (x[i] == 2) tot++;
      else if (tot) x[i] = 0, tot--;
   }
   for (int i = 1, tot = 0, n = 0; i <= a + b; i++) {
      tot += x[i] > 0;
      if (x[i] == 2) l[++n] = tot;
   }
   for (int i = 0; i <= a; i++)
      f[i] = 1;
   for (int i = 1; i <= b; i++) {
      for (int j = a; j >= l[i]; j--)
         f[j] = f[j - 1];
      for (int j = l[i] - 1; ~ j; j--)
         f[j] = 0;
      for (int j = 1; j <= a; j++)
         (f[j] += f[j - 1]) %= mod;
   }
   printf("%d\n", f[a]);
   return 0;
}
```

---

## 作者：binbin_200811 (赞：0)

# [ARC127E Priority Queue](https://www.luogu.com.cn/problem/AT_arc127_e)

分析性质+dp。

### 思路

由于每次加入的数肯定是一个 $a$ 的排列，但这个角度不好考虑。

设 $\{a\}$ 为最终状态的集合，其中 $a_i<a_{i+1}$，显然集合内元素个数为 $A-B$。

然后可以发现，按照元素值升序的加入顺序形成最终状态一定是最保险的一种方案。

设 $a_{i+1},a_i$ 加入的顺序可以形成该最终状态，试交换顺序为 $a_i,a_{i+1}$。

* 因为 $a_i<a_{i+1}$ 所以 $a_i$ 可以留下。

* 因为 $a_{i+1},a_i$ 的顺序可以形成最终状态，所以 $a_i,a_{i+1}$ 也可以形成最终状态。

所以如果乱序加入的状态可以留下 $a_i,a_{i+1}$，那么升序加入一定可以留下。

那么我们可以发现，最后留下的顺序是升序的，就可以考虑 $dp$。

设 $dp[i][j]$ 为目前已经放了 $i-1$ 个数，第 $i$ 个数放 $j$ 的状态数。

有转移：
$$
dp[i][j]=\sum_{k=1}^{j-1} dp[i-1][k]
$$
可以用前缀和优化转移，时间复杂度 $O(n^2)$。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 998244353

const int maxn=5005;

int n,a,b,t,m;
int r[maxn];

ll dp[maxn][maxn],s[maxn][maxn];

int main()
{
    scanf("%d%d",&a,&b);
    for(int i=1;i<=a+b;i++)
    {
        int x;
        scanf("%d",&x);
        if(x==1) r[++t]=++m;
        else t--;
    }
    dp[0][0]=1;
    for(int i=0;i<=a;i++) s[0][i]=1;
    for(int i=1;i<=a-b;i++)
    {
        for(int j=1;j<=r[i];j++)
            dp[i][j]=s[i-1][j-1],s[i][j]=(dp[i][j]+s[i][j-1])%mod;
        for(int j=r[i]+1;j<=a;j++) s[i][j]=s[i][r[i]];
    }
    printf("%lld",s[a-b][r[a-b]]);
}
```



---

## 作者：daduoli (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/v9fm8g07.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

秒了，感觉没有道理的，感觉比前面的题简单，过的人少可能是因为位置放的太后了，~~不会做 $D$，不会套路题是这样的。~~

首先问我们最后序列的可能情况，我们一般考虑结果序列可行的充要条件。

容易发现倘若结果序列中删除了 $2\ 4$ 这两个数字，那么我想把删除变成 $4\ 5$ 是显然可以成立的，自己思考一下不难发现。

也就是说倘若删了一个数 $i$，那么实际上可以把删除的数替换成任意大于等于 $i$ 没有删掉过的数。

所以我们只需要找到所有删除都最靠前的情况即可，然后计算方案数只需要考虑把删除往后放就可以了。

考虑从小到大填 $1$ 就可以，然后遇到 $2$ 就删数。

考虑从后往前删数，记 $f_{i,j}$ 表示考虑了 $i\sim n$ 的删除标记，最靠近 $i$ 的删除标记在 $j$。然后计算这个动态规划是简单的。

时间复杂度 $O(nm)$。


```
#include<bits/stdc++.h>
typedef long long LL;

using namespace std;
const int N=5010,MAXN=1e4+10,P=998244353;
int n,m;
int a[MAXN],l[MAXN],tot,cnt;
int f[N],g[N],s[N];
bool sf[MAXN];
LL fad(LL x,LL y) {
	return (x+y>=P?x+y-P:x+y);
}
signed main () {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+m;++i) {
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n+m;++i) {
		if(a[i]==1) l[++tot]=++cnt;
		else sf[l[tot--]]=1;
	}
	f[n+1]=1;
	for(int i=n;i>=1;--i) {
		if(!sf[i]) continue;
		for(int j=n+1;j>=i;--j) {
			s[j]=fad(s[j+1],f[j]);
		}
		for(int j=i;j<=n;++j) {
			g[j]=s[j+1];
		}
		for(int j=i;j<=n+1;++j) {
			f[j]=g[j];
		}
	}
	LL ans=0;
	for(int i=1;i<=n+1;++i) {
		ans=fad(ans,f[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

