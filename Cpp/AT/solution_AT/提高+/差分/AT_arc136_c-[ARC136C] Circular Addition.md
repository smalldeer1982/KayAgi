# [ARC136C] Circular Addition

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc136/tasks/arc136_c

長さ $ N $ の整数列 $ x=(x_0,x_1,\cdots,x_{N-1}) $ があります（添字が $ 0 $ から始まることに注意）． 最初，$ x $ の要素はすべて $ 0 $ です．

あなたは，以下の操作を好きな回数繰り返すことができます．

- 整数 $ i,k $ ($ 0\ \leq\ i\ \leq\ N-1 $, $ 1\ \leq\ k\ \leq\ N $) を選ぶ． その後，$ i\ \leq\ j\ \leq\ i+k-1 $ を満たすすべての $ j $ について，$ x_{j\bmod\ N} $ の値を $ 1 $ 増やす．

長さ $ N $ の整数列 $ A=(A_0,A_1,\cdots,A_{N-1}) $ が与えられます． $ x $ を $ A $ に一致させるために必要な最小の操作回数を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力される値はすべて整数

### Sample Explanation 1

以下のように操作すればよいです． - 最初，$ x=(0,0,0,0) $ である． - $ i=1,k=3 $ で操作を行う．$ x=(0,1,1,1) $ となる． - $ i=3,k=3 $ で操作を行う．$ x=(1,2,1,2) $ となる．

## 样例 #1

### 输入

```
4
1 2 1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
5
3 1 4 1 5```

### 输出

```
7```

## 样例 #3

### 输入

```
1
1000000000```

### 输出

```
1000000000```

# 题解

## 作者：白简 (赞：8)

#### 题目大意

给定一个长度为 $N$ 的序列 $A$，这个序列组成一个环。每次可以选择环上的一段都减去 $1$，求最少操作次数使得序列每个位置值均为 $0$。

#### 思路
首先考虑一次操作会产生什么影响。

发现，会使得序列的最大值最多减 $1$，环的差分序列最多减 $2$。

那么我们设 $M = \max \left\{A_i \right\},D=\dfrac{1}{2}\sum\limits_{1 \leq i \leq N - 1} \left\lvert A_i-A_{i + 1 \bmod{N}} \right\rvert$。

那么显然答案的下限为 $\max(M,D)$，我们需要证明一定能使得答案为 $\max(M,D)$。

考虑把情况转化为 $D=M$ 的情况。

##### 当 $M > D$ 时

由于 $D$ 一定大于等于序列的极差，如果存在 $A_i=0(1 \leq i \leq N)$，那么一定有 $D \geq M$，所以当 $M > D$ 时序列中不存在 $0$。

那么此时对整个序列的值都减去 $1$，一定会使得 $M$ 减少 $1$，$D$ 的值一定不变，可以直接重复操作至 $D=M$。

##### 当 $D > M$ 时

可以选择全是最大值的连续区间减去 $1$，这样可以使得 $M$ 至多减 $1$，$D$ 一定减 $1$，可以重复操作至 $D = M$。

##### 当 $D=M$ 时

如果只有一个连续最大值段，直接使这段减 $1$，可以使得 $D,M$ 的值均减 $1$；

如果有不止一个连续最大值段，此时序列中不存在 $0$。因为序列中存在 $0$ 时一定只存在一个只包含 $M$ 的连续段。

那么我们可以找到一个最小的包含所有 $M$ 的区间，对这个区间操作，可以使得 $D,M$ 的值均减 $1$，重复操作至 $D,M$ 的值均为 $0$。

因此，答案一定为 $\max(M,D)$。

#### Code
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2000600;

int n,a[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int D = 0,M = 0;

    cin >> n;
    for(int i = 1;i <= n; i++) {
        cin >> a[i];
        M = max(M,a[i]);
    }

    for(int i = 1;i <= n; i++) {
        if(i != 1)
            D += abs(a[i] - a[i - 1]);        
        else
            D += abs(a[1] - a[n]);
    }
    
    D /= 2;
    
    int ans = max(D,M);

    cout << ans << endl;
    return 0;
}
```

---

## 作者：TillTheEnd (赞：6)

看到没有题解，仅仅为官方题解写个翻译，因为我也不知道如何从题面出发推出结论。

题意：圆周上有 $n$ 数，每次把圆周上的一段区间整体减一，问最少几次操作可以归零。区间自己不重叠。

以 $1$ 为起始点做一遍差分，则一次操作是将差分数组单点加一再单点减一。容易得到答案的下限是差分数组绝对值和的一半。

一个下限是不够的；可以尝试找到另一个下限并证明这两个下限能放出答案。

注意到一次操作相当于把差分数组单点加并单点减，同时把最大值增加最大 $1$（后面那个“注意到”我真的难以理解）。于是下限的另一估计是 $\max\{a_i\}$。

下面证明 $\max\{\frac{1}{2}\sum_{i=1}^n{|a_i - a_{i+1}|},\max\{a_i\}\}$ 为答案。

若后者大于前者，做全局减一即可，可证没有数字等于 $0$。

若前者大于后者，选取全为最大值的连续区间减一，前者减一。

若前者等于后者，找一段包含全部最大值但不是整个环减一，可证没有数字为 $0$。

很离谱。我不知道赛场上遇到这道题会怎样。可能是顺着差分的思路渐行渐远？感觉这个答案下限估计并证明可取真的离谱。

代码很好写，不给了。

---

## 作者：WeLikeStudying (赞：5)

- [往期回顾](https://www.luogu.com.cn/blog/luo1gu1zui1bang1/zhen-jing-jing-dian-jian-dan-tan-xin-jing-ran-you-ren-fou-kuai-ji-zho)。
- ~~震惊！经典简单贪心竟然有小编不会其中原理！究竟是人性的缺失还是道德的沦丧？是怎样一回事呢？贪心相信大家都很熟悉，但是经典简单贪心竟然有小编不会其中原理是怎样一回事呢？下面就让小编带大家来了解一下吧！~~
- 有一个非负数列，一次操作可以将一个连续段减一，问将数列中所有数减到 $0$ 的最小操作次数。
- 我们不难想到一个贪心，那就是随便选择一个点，然后将它能够减 $1$ 的最长子段减 $1$，令人震惊的是它居然是正确的，其实就是[这题](https://www.luogu.com.cn/problem/P1969)，小编也非常惊讶，而且利用这个式子，甚至可以归纳出这个简单的式子：
$$a_0+\sum_{i=0}^{n-1}\max(0,a_{i+1}-a_i)$$
- 让我们考虑补上一个证明，其实只需要证明存在一种最优方案让区间不包含就相离就好了，这是容易的，因为如果有相交的情况我们可以改成等量的两个互相包含区间。
- 另外一个更简洁的证明同样可以证明这是下界，每次操作至多使得这个式子减小 $2$：
$$a_0+\sum_{i=0}^{n-1}|a_i-a_{i+1}|+a_{n-1}$$
- 所以答案同样可以表示成一个更简洁的式子：
$$\frac12(a_0+\sum_{i=0}^{n-1}|a_i-a_{i+1}|+a_{n-1})$$
- [代码](https://www.luogu.com.cn/paste/zondgfdc)，小编也非常惊讶。
- 然后小编不禁灵机一动：这题可不可以出到环上呢？[其实就是这题](https://atcoder.jp/contests/arc136/tasks/arc136_c)。
- 有人可能觉得一开始的贪心仍然适用，但是小编给你看一个例子：$1,2,1,2$，最优解是两次操作，第一次数列变成 $1,1,0,1$，第二次清空。
- 猜一波结论是：
$$\frac12\sum_{i=0}^{n-1}|a_i-a_{(i+1)\bmod n}|$$
- 结果发现可以被一个数的情况 hack，于是加上对最大值取 $\max$ 就……过了？[代码](https://www.luogu.com.cn/paste/7g475su9)，小编也很惊讶。
- 让我们尝试证明一下答案是：
$$\max(\frac12\sum_{i=0}^{n-1}|a_i-a_{(i+1)\bmod n}|,\max_{i=0}^{n-1}a_i)$$
- 设左边是 $A$ 右边是 $B$。
- 若 $A<B$，$a_i$ 最小值必不为 $0$，整体减即可。
- 若 $A=B$，要么全 $0$，要么存在一个数小于最大值，找到极长的一段，单独不减它。
- 若 $A>B$，随便找一段包含所有最大值即可。
- 对于一般图的情况，可以证明这个问题是 $\text{NPC}$，对于有向无环图的情况，我们有高效的网络流解法。
- ~~以上就是震惊！经典简单贪心竟然有小编不会其中原理！究竟是人性的缺失还是道德的沦丧？的全部内容了，大家有什么想法呢，欢迎在评论区告诉小编一起讨论哦！~~

---

## 作者：Demeanor_Roy (赞：3)

怎么都是神秘结论。来个正常贪心。

我们考虑倒过来，将原序列变为全 $0$。

先对原序列 $A$ 进行一遍差分得到差分序列 $A'$。注意到环上一次区间减 $1$ 操作对应到差分序列 $A'$ 上可能为以下两种：

- $A'_{i} \gets A'_{i}-1,A'_j \gets A'_j+1(1 \leq i <j \leq n+1）$。

- $A'_1 \gets A'_1-1,A'_{i} \gets A'_{i}+1,A'_j \gets A'_j-1,A'_{n+1} \gets A'_{n+1}+1(1 < i <j < n+1）$。

对于 $A'_{n+1}$ 的操作我们忽略。同时注意到，我们把一个负数减少或者把一个正数增加一定是不优的。且操作二可以调整三个数的值，而操作一只能调整两个，故我们的策略一定为：

- 在保证剩下的数能被操作一消完的前提下尽量多进行操作二。

我们每次取出差分序列的最后一个正数 $A'_x$ 和最后一个负数 $A'_y$，分情况讨论：

- $x<y$，跳过这个负数考虑它的前一个。

- 否则在保证 $A'_1$ 非负，操作后正数和不小于负数（为了满足之后剩余数能被操作一消完）的前提下用二操作消除 $(1,y,x)$ 即可。

用两个队列模拟，复杂度线性。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n,a[N];
queue<int> q1,q2;
long long ans,sum,rest;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=n;i>=2;i--) 
	{
		a[i]-=a[i-1];
		if(a[i]>0) q1.push(i),rest+=a[i];
		else if(a[i]<0) q2.push(i),sum-=a[i];
	}
	rest+=a[1];
	while(a[1]&&q1.size()&&q2.size()&&rest>sum)
		if(q2.front()>q1.front()) q2.pop();
		else
		{
			if(min(rest-sum,1ll*min(a[1],-a[q2.front()]))>=a[q1.front()]) 
			{
				ans+=a[q1.front()];
				sum-=a[q1.front()];
				rest-=2ll*a[q1.front()];
				a[1]-=a[q1.front()];a[q2.front()]+=a[q1.front()];
				q1.pop();
			}
			else 
			{
				int x=min(rest-sum,1ll*min(a[1],-a[q2.front()]));
				ans+=x;sum-=x;a[1]-=x;a[q2.front()]+=x;a[q1.front()]-=x;rest-=2ll*x;
				if(!a[q2.front()]) q2.pop();
			}
		}
	if(a[1]) ans+=a[1];
	while(!q1.empty()) ans+=a[q1.front()],q1.pop();
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：User_Authorized (赞：3)

## 题意

给定一个长度为 $N$ 的环，每次选取环上一段并使其中每个元素值均加 $1$。给定一个长度为 $N$ 的序列 $A$，环上元素初始值为 $0$，求将环变为序列 $A$ 的最少操作次数。

（$1 \le N \le 2 \times 10^5, 1 \le A_i \le 10^9$）。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-ARC136C.html)

### 结论

设 $M = \max\left\{A_i\right\}, D = \dfrac{1}{2}\sum\limits_{i = 0}^{N - 1}\left\lvert A_i - A_{i + 1 \bmod N}\right\rvert$，那么答案为 $\max(M, D)$。

### 证明

考虑将区间加操作视为对序列 $A$ 执行区间减，直至全部减为 $0$。

发现每次操作最多使 $D, M$ 的值减 $1$，由此可以证明必要性。

接下来按 $D, M$ 的大小关系分类讨论来证明充分性。

#### 若 $D = M$

可以发现此时若序列中存在 $0$，那么序列中一定只存在一个只包含 $M$ 的极长连续段。

若序列中包含多个只包含 $M$ 的极长连续段，即序列的最大值不相邻，那么序列中一定不含有 $0$。

那么一定存在极小的，包含所有序列最大值的区间，对该区间进行操作，一定可以使 $M$ 和 $D$ 的值均减少 $1$。重复操作至 $D = M = 0$ 即可。

#### 若 $M > D$

因为 $D \ge \max\left\{A_i\right\} - \min\left\{A_i\right\}$，所以有 $\min\left\{A_i\right\} > 0$，那么我们对整个 $A$ 序列执行操作，一定有 $M$ 的值减少 $1$，$D$ 的值不改变。重复操作至 $D = M$ 即可。

#### 若 $D > M$

此时我们选取任意一个只包含 $M$ 的极长连续段即可，可以发现 $D$ 的值一定减少 $1$，$M$ 的值至多减少 $1$，重复操作至 $D = M$ 即可。

至此可以得到结论，只需要 $\max(D, M)$ 次操作便一定可以完成要求。

总复杂度 $\mathcal{O}(N)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    ValueVector A(N);

    for (auto &iter: A)
        std::cin >> iter;

    valueType D = 0;

    for (valueType i = 1; i < N; ++i)
        D += std::abs(A[i] - A[i - 1]);

    D += std::abs(A.front() - A.back());

    D /= 2;

    valueType const M = *std::max_element(A.begin(), A.end());

    std::cout << std::max(D, M) << std::endl;

    return 0;
}
```

---

## 作者：braveTester (赞：3)

## 题意

给一个有 $1 \le n \le 2\times 10^5$ 个元素的环，初始为全 $0$。每次可以在环上选取一个长度在 $[1, n]$ 的区间，使得每个元素都加一。

问达到目标状态 $A$ 所需要的最小操作步数。

## 题解

这里给出和官方题解不一样的一种思路。

### 断环成链

直觉上，如果这个问题可以断环成链，那么就会和 [[NOIP2013 提高组] 积木大赛](https://www.luogu.com.cn/problem/P1969) 类似，因此首先尝试是否可以寻找到一些特殊点并从此处断开。

对于涉及某一个特定元素的操作，可以将其上的操作分成以下几类：

1. 环；
2. 仅从此元素开始；
3. 仅在此元素终止；
4. 既在此元素开始又在此元素终止（仅选该元素进行操作）；
5. 既不在此元素开始又不在此元素终止（穿过该元素）；

**注**：如果一个操作是环，会归类到环上；其他操作才会归类到剩余的类别中。

容易观察到，如果对于位置 $i$ 和 $i + 1$，有操作 $O_1$ 在 $i + 1$ 上开始（1，4），有操作 $O_2$ 在 $i$ 上终止（3，4），那么可以将操作 $O_1$ 和 $O_2$ 拼接在一起，如果长度溢出的话就再拆出另一个操作，这样做不会使得操作数增加。

由此可以得到以下两个推论：

1. 如果 $i + 1$ 处有操作的起始，那么 $i$ 不会有操作的终止；
2. 如果 $i$ 处有操作的终止，那么 $i + 1$ 处不会有操作的起始。

利用以上两个推论，可以发现一定存在一个最优解，其在最小值处只会有两种操作：环（1），或者穿过（5）。

- 为了证明这个发现，需要一些细节上的讨论。由于这些细节易于理解，但是在此说明过于冗长，因此略去。

### 环与穿过的区分

断环成链以后（令最小值为第一个元素，即 $A[0]$），按照 [[NOIP2013 提高组] 积木大赛](https://www.luogu.com.cn/problem/P1969) 的思路，有以下贪心策略：对于位置 $i + 1$，其会尽量白嫖 $i$ 上的操作，实在不行再新开。初始时默认已有 $A[0]$ 个操作，不需要付出代价。

但是这样会有一个问题：对于 $0$ 上的穿过操作，会正确的计算代价，但是对于环操作，却会漏掉代价，最后需要加上。但是我们无法区分 $0$ 上有多少穿过和环。

注意到，虽然我们无法区分穿过和环，但是对于上述的贪心策略是没有任何影响的，因此我们只需要在此基础上最小化环的数量即可。

第一个尝试是直接最小化环的数量，即一旦有操作消失，先让从 $0$ 开始的操作消失，尝试构造穿过操作，这样环的数量最小。然而这种方式会有反例，例如对于 `1 2`，会发现实际构造的操作只有一个长度为 $3$ 的操作，违反了长度限制。

分析发现，原因在于虽然试图让操作尽早结束以构造穿过操作，但是只关注了穿过的结束，实际上并没有那么多合法的穿过起始位置。

为了解决这个问题，将一个元素上的操作分成三个集合：

1. 从 $0$ 起始的操作；
2. 有潜力构成穿过的操作；
3. 其他操作。

根据贪心策略，

- 如果 $A[i] < A[i + 1]$，那么会有 $A[i + 1] - A[i]$ 个操作出现。这些操作都可以尝试构成穿过的起始位置，但是和已有的有潜力构成穿过的操作数量之和不可以超过已经消失的从 $0$ 起始的操作。其余都是其他操作；
- 如果 $A[i] > A[i + 1]$，那么会有 $A[i] - A[i + 1]$ 个操作消失。根据我们的目标，我们希望优先让从 $0$ 起始的操作消失，这样可以让后面出现更多有潜力的操作；同时让有潜力的操作最后消失，这样可以使环最少。

最终贪心的代价加上 $A[0]$ 再减去在 $A[n - 1]$ 有潜力构成穿过的操作数目即可。

- 实际应该是消失的从 $0$ 起始的操作数目和有潜力构成穿过的操作数目取 $\min$，不过由于上述计算过程，有潜力的穿过数目一定小于等于消失的从 $0$ 起始的操作数目，因此化简为上式。

## 代码

```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 2 * 210000;
const int INF = ~0u>>2;

int N;
int A[NMAX];
long long ans = 0;

void try_subtract(int &x, int &delta)
{
    int tmp = min(x, delta);
    x -= tmp;
    delta -= tmp;
}

void try_add(int &x, int &delta, int limit)
{
    int tmp = min(limit - x, delta);
    x += tmp;
    delta -= tmp;
}

int main()
{
    scanf("%d", &N);
    int min_val = INF;
    int m_pos = 0;
    for(int i = 0;i < N;i += 1)
    {
        scanf("%d", &A[i]);
        A[i + N] = A[i];
        if(min_val > A[i])
        {
            min_val = A[i];
            m_pos = i;
        }
    }
    ans = 0;
    int left = A[m_pos];
    int x = A[m_pos], y = 0, z = 0;
    // x: 从 0 起始的操作
    // y: 其他操作
    // z: 有潜力构成穿过的操作
    for(int i = 0;i < N;i += 1)
    {
        int idx = m_pos + i;
        ans += max(A[idx] - left, 0);
        if(A[idx] < left) {
            int delta = left - A[idx];
            try_subtract(x, delta);
            try_subtract(y, delta);
            try_subtract(z, delta);
        } else {
            int delta = A[idx] - left;
            try_add(z, delta, A[m_pos] - x);
            try_add(y, delta, INF);
        }
        left = A[idx];
    }
    // A[m_pos + N - 1] 到 A[m_pos] 的转移不必做，不影响 z
    ans += A[m_pos] - z;
    printf("%lld\n", ans);
    exit(0);
}
```


---

## 作者：under_the_time (赞：1)

## 题意

> 给定一个 $n$ 个点的环，环上每个点有点权 $a_i$；每次操作选择环上连续的一段 $a_l,\cdots,a_n,a_1,\cdots a_r$（$l>r$）或 $a_l,a_{l+1},\cdots,a_r$（$l<r$），使得段上的点 $i$，$x_i\gets x_i-1$。求最少的操作次数使得 $\forall i\in [1,n],a_i=0$​。
>
> $n\le 2\times 10^5$，$1\le a_i\le 10^9$。

## 解法

观察一次操作带来的影响。显然答案至少是 $\max\{a_i\}$，我们记这个值为 $m$，但是在操作中点权被减到 $0$ 的元素会将环断成若干段，答案不一定能取到 $m$。区间减法启发我们考虑差分，令 $d_i=|a_i-a_{i+1}|$（$d_n=|a_n-a_1|$），发现一次操作最多使 $\sum d_i$ 减二。于是答案至少是 $\cfrac{\sum d_i}{2}$，我们记这个值为 $k$，但是若选择整个环进行操作，那么答案不一定能取到 $k$。结论就是，答案等于 $\max(m,k)$。

1. 首先，若 $k=0$，那么 $a$ 一定全部相等，做若干次全局减一即可，答案为 $m$。
2. 否则，若 $k<m$，那么 $m>0$，不断做全局减一使得 $m\gets m-1$ 而 $k$ 显然不变，直到 $m=k$，该情况留到后面讨论。
3. 若 $k>m$，观察到 $a$ 的初始值 $>0$，我们考虑不断选择仅包含 $m$ 的区间 $-1$，这样 $m$ 的变化量不大于 $k$ 的变化量且可以保证全 $0$ 段的数量 $\le 1$​，也是一直做直到 $m=k$。
4. 若 $k=m$，进行分类讨论：
   - 若当前只存在一个极长的仅包含 $m$ 的连续段，那么我们将这个连续段直接 $-1$ 使 $m,k$ 均减一。
   - 否则 $a$ 中一定没有 $0$，我们找到最短的包含了所有值为 $m$ 的元素的区间 $-1$，效果同上。

## 代码

```cpp
// Problem: [ARC136C] Circular Addition
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc136_c
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// Good luck to the code >w<
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define open(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define abs(x) (((x) > (0)) ? (x) : (-(x)))
#define print(x) printf("%d %d\n", x.first, x.second)
const int maxn = 2e5 + 5;
int a[maxn], mx; ll d;
int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &a[i]), mx = max(mx, a[i]), d += abs(a[i] - a[i - 1]);
	d = (d + abs(a[n] - a[1]) - a[1]) >> 1, printf("%lld\n", max(1ll * mx, d));
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

序列上为经典问题，考虑两个相邻数之间间隔作为左右括号数量的下界，容易证明这个下界易于达到。

对于环上的问题，由于左右两端接在一起，只考虑下界有可能使得最后剩余的元素 $>0$，通过观察发现答案为：
$$\max(\frac{1}{2}\sum\limits_i ^ {n - 1} |a_i - a_{(i + 1) \bmod n}|, \max_i ^ {n - 1} a_i)$$

证明：记前者为 $S$，后者为 $M$，根据 $S, M$ 的大小关系讨论（需要将问题拓展到 $a_i \ge 0$ 的情况）。

若 $S<M$，则 $a$ 中一定不存在 $0$，将全体减 $1$，最大值减 $1$。

若 $S = M$，考虑环被极长的最大值段分割成了几段，则一定至多一个段存在 $0$，单独不操作这个段，$S, M$ 同时减 $1$。
若 $S>M$，任选一段极长的最大值连续段减 $1$，$S$ 减 $1$。

复杂度 $\mathcal{O}(n)$。

---

