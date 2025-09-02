# [ARC144C] K Derangement

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc144/tasks/arc144_c

正整数 $ N,\ K $ が与えられます． $ 1 $ から $ N $ までの整数からなる順列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ であって次の条件を満たすもののうち， 辞書順最小のものを求めてください．

- 任意の $ i $ ($ 1\leq\ i\leq\ N $) に対して $ \lvert\ A_i\ -\ i\rvert\ \geq\ K $ が成り立つ．

そのような順列が存在しない場合には，`-1` を出力してください．

 数列の辞書順とは？ 相異なる数列 $ S $ と数列 $ T $ の大小を判定するアルゴリズムを以下に説明します．

以下では $ S $ の $ i $ 番目の要素を $ S_i $ のように表します．また， $ S $ が $ T $ より辞書順で小さい場合は $ S\ \lt\ T $ ，大きい場合は $ S\ \gt\ T $ と表します．

1. $ S $ と $ T $ のうち長さが短い方の文字列の長さを $ L $ とします．$ i=1,2,\dots,L $ に対して $ S_i $ と $ T_i $ が一致するか調べます．
2. $ S_i\ \neq\ T_i $ である $ i $ が存在する場合，そのような $ i $ のうち最小のものを $ j $ とします．そして，$ S_j $ と $ T_j $ を比較して， $ S_j $ が $ T_j $ より（数として）小さい場合は $ S\ \lt\ T $ ，大きい場合は $ S\ \gt\ T $ と決定して，アルゴリズムを終了します．
3. $ S_i\ \neq\ T_i $ である $ i $ が存在しない場合， $ S $ と $ T $ の長さを比較して，$ S $ が $ T $ より短い場合は $ S\ \lt\ T $ ，長い場合は $ S\ \gt\ T $ と決定して，アルゴリズムを終了します．

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 3\times\ 10^5 $
- $ 1\leq\ K\leq\ N\ -\ 1 $

### Sample Explanation 1

条件を満たす順列は，$ (2,\ 3,\ 1) $ と $ (3,\ 1,\ 2) $ の $ 2 $ つです．例えば $ (2,\ 3,\ 1) $ は - $ \lvert\ A_1\ -\ 1\rvert\ =\ 1\ \geq\ K $ - $ \lvert\ A_2\ -\ 2\rvert\ =\ 1\ \geq\ K $ - $ \lvert\ A_3\ -\ 3\rvert\ =\ 2\ \geq\ K $ であるため条件を満たしています．

## 样例 #1

### 输入

```
3 1```

### 输出

```
2 3 1```

## 样例 #2

### 输入

```
8 3```

### 输出

```
4 5 6 7 8 1 2 3```

## 样例 #3

### 输入

```
8 6```

### 输出

```
-1```

# 题解

## 作者：ZepX_D (赞：3)

## 思路
我们首先打表找规律，可以打出以下表
```
n k
5 3  ：无解
6 3  : 4 5 6 1 2 3
7 3  : 4 5 6 7 1 2 3
8 3  : 4 5 6 7 8 1 2 3
9 3  : 4 5 6 7 8 9 1 2 3
10 3 : 4 5 6 1 8 9 10 2 3 7
11 3 : 4 5 6 1 2 9 10 11 3 7 8
12 3 : 4 5 6 1 2 3 10 11 12 7 8 9
13 3 : 4 5 6 1 2 3 10 11 12 13 7 8 9
14 3 : 4 5 6 1 2 3 10 11 12 13 14 7 8 9
15 3 : 4 5 6 1 2 3 10 11 12 13 14 15 7 8 9
16 3 : 4 5 6 1 2 3 10 11 12 7 14 15 16 8 9 13
17 3 : 4 5 6 1 2 3 10 11 12 7 8 15 16 17 9 13 14
18 3 : 4 5 6 1 2 3 10 11 12 7 8 9 16 17 18 13 14 15
19 3 ：4 5 6 1 2 3 10 11 12 7 8 9 16 17 18 19 13 14 15 
```
可以看出 $ n = 6 $ 到 $ n = 9 $ 是插入操作，$ n = 10 $ 到 $ n = 12 $ 是插入加交换，而且在 $ n = 12 $ 及以后前六个数就固定为 $ 4\ 5\ 6\ 1\ 2\ 3 $ 了，我们就可以得出当 $ n = 2 \times k $ 时正好有解，往后 $ k $ 个是插入，再往后 $ k $ 个为插入加交换，每 $ 2 \times k $ 个为一个循环，且每循环一次前面就会多 $ 2 \times k $ 个数固定住。

那我们就可以当 $ n \ge 4 \times k $ 时选前 $ 2 \times k $ 个数放到前面固定住，直到 $ n < 4 \times k $ 时再分两种情况，$ 2 \times k \le n \le 3 \times k $ 时直接插入， $ 3 \times k < n < 4 \times k $ 时先处理出来 $ n = 3\times k $ 的排列再往后加上交换操作

交换操作的话比较简单，每次是倒数第 $ 2 \times k $ 个数变为倒数第 $ k $ 个数，再记录一下倒数第 $ k $ 个数，再把倒数第 $ k $ 个数变为要插入的数，最后把记录的数添加到排列末尾就行了，说的有点绕，还是看代码吧

## code
```cpp
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

int n,k,a[600010];
void print(int l,int r)
{
	for (int i = l+k;i <= r;i++) printf("%d ",i);
	for (int i = l;i < l+k;i++) printf("%d ",i);
}

int main()
{
	cin >> n >> k;
	if (n < 2*k) printf("-1");
	else
	{
		int l = 0;
		while(n-l >= 4*k)//大于等于4k，选前2k个数打印出来
			print(l+1,l+2*k),l += 2*k;
		if (n-l <= 3*k)//直接插入
		{
			for (int i = l+k+1;i <= n;i++) printf("%d ",i);
			for (int i = l+1;i <= l+k;i++) printf("%d ",i);
		}
		else
		{
			int cnt = 0;
			for (int i = l+k+1;i <= l+3*k;i++) a[++cnt] = i;
			for (int i = l+1;i <= l+k;i++) a[++cnt] = i;//先把n = 3k处理出来
			for (int i = l+3*k+1;i <= n;i++)//插入+交换
			{
				swap(a[cnt-k+1],a[cnt-2*k+1]);
				cnt++;a[cnt] = a[cnt-k];a[cnt-k] = i;
			}
			for (int i = 1;i <= cnt;i++) printf("%d ",a[i]);
		}
	}
	return 0;
}
```


---

## 作者：Eous (赞：2)

我是打表仙人。显而易见的有当 $2k > n$ 时非法。让我们打个暴力代码出来。（此处省略一份 $O(n!)$ 暴力代码）让我们试试 `6 3` 的输出结果：`4 5 6 1 2 3`。再让我们试试 `12 3` 的输出结果：`4 5 6 1 2 3 10 11 12 7 8 9`。是不是有点初见端倪？再来一组：`8 2` 的输出：`3 4 1 2 7 8 5 6`。现在你可以看出规律了。把 $n$ 分成几段长度为 $2k$ 的段，每段结构为：

$$
2k \times x + k + 1,2k \times x + k + 2,2k \times x + k + 3,...,2k \times x + k + k, \\
2k \times x + 1,2k \times x + 2,2k \times x + 3,...,2k \times x + k
$$

其中 $x$ 表示这是第几段，从 $0$ 开始计数。但是这是 $2k \mid n$ 的情况。

那么 $2k \nmid n$ 呢？试试 `8 3`。输出为 `4 5 6 7 8 1 2`。再来 `10 3`。输出为 `4 5 6 1 8 9 10 2 3 7`。多打几组，你会发现，前面 $[1,n - 2k]$ 平安无事，依然是上面的规律。直到 $n - 2k + 1$ 这个位置。我们发现它输出了 $[n - 2k + 1,n - k]$ 的 $k$ 个数，究其原因是，如果都到这了还按照原来的规律输出，最后几个一定是 $p_i = i$ 不合法的。所以我们需要提早把它输出以避免非法情况。至于最后的 $k$ 个数，把没输出的按照大小输出即可。可以证明一定合法。

code:

```cpp
#include<bits/extc++.h>
#define int long long
using namespace std;
const int maxn = 3e5 + 5;
int n,k;
int p[maxn];
bool b[maxn];
vector<int>ans;
signed main()
{
    scanf("%lld%lld",&n,&k);
    if ((k << 1) > n)
        return printf("-1"),0;
    fill(b + 1,b + n + 1,1);
    for (int s = 1; s + (k << 1) - 1 <= n && ans.size() < n - (k << 1); s += (k << 1))
    {
        int t = s + (k << 1);
        for (int i = s + k; i < t && ans.size() < n - (k << 1); i++)
        {
            b[i] = 0;
            ans.push_back(i);
        }
        for (int i = s; i < s + k && ans.size() < n - (k << 1); i++)
        {
            b[i] = 0;
            ans.push_back(i);
        }
    }
    for (int i = n - k + 1; i <= n; i++)
    {
        b[i] = 0;
        ans.push_back(i);
    }
    for (int i = 1; i <= n; i++)
        if (b[i])
            ans.push_back(i);
    for (auto i : ans)
        printf("%lld ",i);
    return 0;
} 
```

---

## 作者：SunsetGlow95 (赞：2)

# 题解 - ARC144C K Derangement

背景：本人是打表也瞪不出规律，看题解区都是找规律大神，发一篇比较有确定性的解法。

## 题意简述

找到字典序最小的长度为 $n$ 的排列 $a$，满足 $\forall 1\le i\le n$，$|a_i-i|\ge k$。$n$、$k$ 给定，$2\le n\le 3\times 10^5$，$1\le k\le n$。无解输出 `-1`。

## 解析

无解是容易判的：$2k>n$。考虑构造一组字典序不一定最小的可行解：$\{k+1,k+2,\ldots,n,1,2,\ldots,k\}$。那么无解也就显然：第 $n-k$ 位的 $n$ 和第 $n-k+1$ 位的 $1$ 相邻的情景不存在，也就是 $n-k+1-1<k$，即 $2k>n$。

来，减小这个排列的字典序：$\{k+1,k+2,\ldots,n,1,2,\ldots,k\}$。

我希望把 $1$ 提前。我们第一次在点 $k+1$ 处可以选 $1$，这以后的每一处都可以选 $1$。但是 $k+1$ 以后还能不能选 $2k+1$？

意思就是，在前面一大段的 $i$ 我们都选择 $a_i=k+i$。能不能把最后 $\{1,2,\ldots,k\}$ 的头 $1$ 先在前面输出，而在最后放上点 $2k+1$？

如果可以，我们就放，否则，就不放。

这点启发我们想到在逐位考虑 $a_i$ 时维护一个最小的值 $v$，它在 $j<i$ 的 $a_j$ 中没有出现过。如果它可以在 $a_i$ 处出现并且 $i+k$ 可以延迟出现，也就是 $v\le i-k\land i+k\le n-k$，我们输出 $v$，延迟出现 $i+k$。否则我们继续延迟 $v$，输出 $i+k$。

最后把剩余未出现的数升序输出即可。

时间复杂度：$1\sim n$ 逐位考虑 $a_i$，$v$ 移动 $n$ 次，时间为 $O(n)$。

## 代码

```cpp
int main() {
  int N(0), K(0);
  cin >> N >> K;
  if (2 * K - 1 >= N) {
    cout << -1 << endl;
    return 0;
  }
  vector<bool> vis(N);
  int id(0);
  for (int i(0); i != N - K; ++i) {
    if (i + K <= N - 1 - K && id != N && id <= i - K) {
      cout << id + 1 << ' ';
      vis[id] = true;
      while (id != N && vis[id]) ++id;
    } else {
      cout << i + K + 1 << ' ';
      vis[i + K] = true;
    }
  }
  while (id != N) {
      cout << id + 1 << ' ';
      vis[id] = true;
      while (id != N && vis[id]) ++id;
  }
  cout << endl;
  return 0;
}
```

---

## 作者：lowbit (赞：2)

首先 $2k>n$ 无解，因为此时 $a_k$ 无法填入满足的数。

由于求字典序最小，我们可以从前往后贪心地填。

有一个直接的想法，把每 $k$ 个数分为一组，每次选能填的数中最小的。

按照这种方法，构造出的序列是这样的：

$$a_i = \begin{cases} i-k & 2\nmid c_i \\ i+k & 2\mid c_i \end{cases}$$

其中 $c_i$ 表示 $i$ 所处组的编号。

$\!$

显然，这个构造是不合法的，我们需要调整，且希望改动尽量少的元素。考虑无解的条件，只需修改最后 $2k$ 个即可。

观察发现，对于 $i\in [n-2k+1,n-k]$ 这段 $a_i$ 只能填 $i+k$，否则会与前面冲突或导致后面 $a_{i+k}$ 处无数可填。

最后 $k$ 个就把剩余的数从小到大填进去，易证必然合法且最优。

提供一个简便的写法，用 set 维护最后剩下的 $k$ 个数。
```cpp
set <int> s;
rep(i, 1, n) s.insert(i);
rep(i, 1, n-k-k) {
	int x = (i-1)/k&1 ? i-k : i+k;
	printf("%d ", x);
	s.erase(x);
}
rep(i, n-k-k+1, n-k) printf("%d ", i+k), s.erase(i+k);
while(k--) {
	printf("%d ", *s.begin());
	s.erase(s.begin());
}
```

---

