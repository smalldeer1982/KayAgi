# Camel Train

## 题目描述

[problemUrl]: https://atcoder.jp/contests/aising2020/tasks/aising2020_e

$ 1,2,\ldots,N $ の番号がついた $ N $ 頭のラクダがいます。 すぬけ君はラクダたちを一列に並べることにしました。

ラクダ $ i $ が先頭から $ K_i $ 番目以内にいるときのうれしさは $ L_i $ です。 そうでない場合のうれしさは $ R_i $ です。

すぬけ君はラクダたちのうれしさの総和を最大化したいです。 ラクダたちのうれしさの総和としてありうる値のうち最大値を求めてください。

テストケースは $ T $ 個与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ T\ \leq\ 10^5 $
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ K_i\ \leq\ N $
- $ 1\ \leq\ L_i,\ R_i\ \leq\ 10^9 $
- $ 1 $ つの入力ファイルにおいて、$ N $ の総和は $ 2\ \times\ 10^5 $ を超えない。

### Sample Explanation 1

\- $ 1 $ 番目のテストケースにおいて、ラクダ $ 2,1 $ の順で並べるのが最適です。 - ラクダ $ 1 $ は先頭から $ 1 $ 番目以内にいないのでうれしさは $ 10 $ です。 - ラクダ $ 2 $ は先頭から $ 2 $ 番目以内にいるのでうれしさは $ 15 $ です。 - $ 2 $ 番目のテストケースにおいて、ラクダ $ 2,1,3 $ の順で並べるのが最適です。 - ラクダ $ 1 $ は先頭から $ 2 $ 番目以内にいるのでうれしさは $ 93 $ です。 - ラクダ $ 2 $ は先頭から $ 1 $ 番目以内にいるのでうれしさは $ 71 $ です。 - ラクダ $ 3 $ は先頭から $ 3 $ 番目以内にいるのでうれしさは $ 57 $ です。

## 样例 #1

### 输入

```
3
2
1 5 10
2 15 5
3
2 93 78
1 71 59
3 57 96
19
19 23 16
5 90 13
12 85 70
19 67 78
12 16 60
18 48 28
5 4 24
12 97 97
4 57 87
19 91 74
18 100 76
7 86 46
9 100 57
3 76 73
6 84 93
1 6 84
11 75 94
19 15 3
12 11 34```

### 输出

```
25
221
1354```

# 题解

## 作者：liangbowen (赞：2)

[blog](https://www.cnblogs.com/liangbowen/p/18344885)。没题解就来写一篇捏。

---

显然 $L_i>R_i$ 的人都想去左边（记为 LFT 人），$L_i<R_i$ 的人都想去右边（记为 RHT 人），$L_i=R_i$ 的人可以摆烂。

（LFT 人与 RHT 人互相干扰，很难刻画。于是找性质。）

**存在最优方案，使得所有 LFT 人都在 RHT 人的左边**。证明：如果有 RHT 人在 LFT 人的左边，交换两人不会使答案更劣。

即：假设有 $x$ 个 LFT 人，那么 $1\sim x$ 的位置全是 LFT 人，$x+1\sim N$ 的位置全是 RHT 人。

于是可以分开考虑 LFT 人与 RHT 人了！下文将只考虑 LFT 人。

---

先令初始答案为 $\sum R_i$，然后再看有多少个 LFT 人能从 $R_i$ 调整成 $L_i$。记 $v_i=L_i-R_i$，只需解决如下问题：

> 如果第 $i$ 个元素在前 $K_i$ 个元素中，那么会获得 $v_i$ 的价值。求出最大价值。

这个就是入门贪心了，按 $v_i$ 排序后贪心放置即可，可以用 set / priority_queue 模拟。当然也可以反悔贪心（

[code](https://atcoder.jp/contests/aising2020/submissions/56399359)，时间复杂度 $O(n\log n)$。

---

## 作者：CQ_Bab (赞：1)

# 思路
看到这种题就应该往反悔贪心上想吧，我们考虑一个最基础的贪心假设每一根香蕉都不考虑是否与其他香蕉冲突那么对于没一根香蕉一定会放取 $\max(l_i,r_i)$ 然后我们去考虑反悔。

- 如果 $l_i>r_i$  那么会优先放在前 $k_i$ 个，就在数组中存入一个 $k_i,r_i-l_i$ 因为如果改了会加上 $r_i-l_i$ 的贡献，并将答案加上 $l_i$。
- 如果 $r_i>l_i$ 那么会优先放在后 $n-k_i$ 个，就在另一个数组中存入 $n-k_i,l_i-r_i$，这与上面同理，并将答案加上 $r_i$。
- 如果 $l_i=r_i$ 那么无论如何房都没有区别不用考虑。

然后我们去进行反悔，我们先对于第一个数组按第一维排序，然后用一个大根堆维护当前能替换的中换之后最优的，如果当前大根堆中的数的个数大于了当前能支持的就一直踢出堆头知道合法，并将答案加上变化值。

处理另一个数组也与上述方法一样。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define int long long
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T=1;
int n;
const int N=2e5+10;
vector<pair<int,int>>le,ri;
int res;
void sum(vector<pair<int,int>>a) {
	sort(a.begin(),a.end());
	priority_queue<int>q;
	for(auto x:a) {
		q.push(x.second);
		while(q.size()>x.first) {
			res+=q.top();
			q.pop();
		}
	}
}
void solve() {
	in(n);
	res=0;
	le.clear(),ri.clear();
	rep(i,1,n) {
		int k,l,r;
		in(k),in(l),in(r);
		if(l>r) le.push_back({k,r-l}),res+=l;
		else if(l<r) ri.push_back({n-k,l-r}),res+=r;
		else res+=l; 
	}	
	sum(le),sum(ri);
	printf("%lld\n",res);
}
fire main() {
	in(T);
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：Heldivis (赞：0)

## Camel Train

前置知识：[反悔贪心](https://www.luogu.com.cn/problem/P2949)

一句话来说，就是：按时间升序，如果之前时间内最小价值小于当前元素的价值，则替换。

```cpp
inline ll Calc(vector<pair<int, int> > vec) {
  ll sum = 0;
  sort(vec.begin(), vec.end());
  priority_queue<int, vector<int>, greater<int>> q;
  for (const auto &[k, v] : vec) {
    q.push(v), sum += v;
    if (q.size() > k) sum -= q.top(), q.pop();
  }
  return sum;
}
```

然后回到本题，第一反应是先默认没有满足前 $k$ 个这一条件，有一个基础的 $\sum r_i$ 的价值，然后对 $X_i = (k_i, l_i - r_i)$ 计算上述方案。

然后第一组样例 $X = \{(1, -5), (2, 10)\}$ 就错了。显然第二个元素放在第一个位置更优。

原因是这个贪心要求的的是每个价值非负。于是考虑如何让价值非负。

把这个序列分为 $l>r$、$l=r$ 和 $l<r$ 三部分，假设分别有 $a,b,c$ 个，显然最后序列一定是前 $a$ 个 $l>r$、后 $c$ 个 $l<r$ ，否则可以交换。

于是把这 $a$ 个和这 $c$ 个分开贪心，因为两部分在最后序列的位置，没有交集。所以一定是合法的。

```cpp
inline void Main() {
  int n = read();
  ll sum = 0;
  vector<pair<int, int>> a, b;
  for (int i = 1, k, l, r; i <= n; ++i) {
    k = read(), l = read(), r = read();
    if (l > r) sum += r, a.push_back({k, l - r});
    if (l == r) sum += l;
    if (l < r) sum += l, b.push_back({n - k, r - l});
  }
  printf("%lld\n", sum + Calc(a) + Calc(b));
}
```

多测记得清空。

---

