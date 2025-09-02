# The Third Side

## 题目描述

粉色士兵们给了你一个由 $n$ 个正整数组成的序列 $a$。

你必须重复执行以下操作直到序列中只剩下 $1$ 个元素：

- 选择两个不同的下标 $i$ 和 $j$
- 选择一个正整数 $x$，使得存在一个非退化三角形$^{\text{∗}}$，其边长为 $a_i$、$a_j$ 和 $x$
- 删除这两个元素 $a_i$ 和 $a_j$，并将 $x$ 追加到序列 $a$ 的末尾

请找出最终序列中唯一剩余元素可能的最大值。

$^{\text{∗}}$当边长为 $a$、$b$、$c$ 的三角形满足 $a + b > c$、$a + c > b$ 且 $b + c > a$ 时，该三角形是非退化的。

## 说明/提示

在第一个测试用例中，序列已经只有一个元素。最终剩余元素的值为 $10$。

在第二个测试用例中，初始序列为 $[998, 244, 353]$。以下操作序列是合法的：

1. 删除 $a_2 = 244$ 和 $a_3 = 353$，并追加 $596$ 到序列末尾。此时 $a$ 变为 $[998, 596]$
2. 删除 $a_1 = 998$ 和 $a_2 = 596$，并追加 $1593$ 到序列末尾。此时 $a$ 变为 $[1593]$

可以证明最终元素不可能超过 $1593$。因此答案为 $1593$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1
10
3
998 244 353
5
1 2 3 4 5
9
9 9 8 2 4 4 3 5 3```

### 输出

```
10
1593
11
39```

# 题解

## 作者：Vct14 (赞：1)

为使答案最大，每次可以选择 $x=a_i+a_j-1$。

因此每次操作后序列的和减少 $1$，答案为 $\sum\limits_{i=1}^na_i-(n-1)$。

---

## 作者：WYX1210 (赞：1)

### 思路
我们知道构成三角形的条件是 $a + b > c$，为了让最后的结果尽可能大，我们可以让 $c = a + b - 1$， 经过 $n-1$ 次合并之后，最终的答案为 $ \sum a_i - (n-1) $ 。

---

## 作者：dg114514 (赞：1)

一道比较简单的题目。\
对于任意的 $a,b$，可以将 $a,b$ 删除并添加 $a+b-1$，这是合法的最大的边。显然，$a+b$ 是不可以的，因为 $(a+b) \ge a+b$。而合并的顺序对答案并无影响。（毕竟不是合并果子）所以可以先合并 $a_1$ 和 $a_2$ 得到 $a_1+a_2-1$，然后以此类推，发现总共 $-1$ 的数量就是 $n-1$，而加的部分就是 $\sum a$。所以和就是 $\sum a-(n-1)$，每次输出即可。

---

## 作者：A_R_O_N_A (赞：1)

一种数学方法，不需要拿什么 `set` 模拟。

三边能够形成三角形的一种判断方法是判断两条短边之和是否大于第三边，即当三个数 $a<b<c$ 且 $a+b>c$ 时，以 $a,b,c$ 为边长的三条边可以构成三角形。

这题要求剩下的最后一个数字最大，那么策略就是选择两个数字 $a,b$ 并弃掉它们，将一个 $a+b-1$ 加入集合，卡最长边的极限。容易发现每次操作完毕后集合中数字的总和 $sum$ 会减掉 $1$，我们总共会执行 $n-1$ 次操作，所以答案就是 $(\sum a_i)-(n-1)$。


```cpp
inline void work(){
	n=read();sum=0;
	for(int i=1;i<=n;i++)sum+=read();
	write(sum-(n-1));puts("");
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：1)

[Problem](https://www.luogu.com.cn/problem/CF2074B)

## Statement

给了一个序列 $a$，长度为 $n$，每次选定 $a_i,a_j$，将原序列中的这两个数替换成与之能构成三角形的 $x$，即满足 $a_i + x > a_j,a_j + x >a_i,a_i + a_j > x$，直到序列中只剩一个数，求序列中剩下的数的最大值。

## Solution

要使剩下的那个数最大，$x = a_i + a_j - 1$。

这样一来从大到小替换是最优的，我们用 multiset 模拟即可。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int Test, n, A[200010];

inline void Solve() {
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> A[i];
	multiset <int, greater<int>> S;
	for (int i = 1; i <= n; i ++) S.insert (A[i]);
	while (S.size() > 1) {
		int x = *S.begin(); S.erase (S.begin());
		int y = *S.begin(); S.erase (S.begin());
		S.insert (x + y - 1);
	}
	cout << *S.begin() << endl;
}

signed main() {
	cin >> Test;
	while (Test --) Solve();
	return 0;
}
```

---

## 作者：gdz0214_and_zxb0214 (赞：0)

## 思路
首先知道，此题每次的操作都会将长度为 $a_i$ 和 $a_j$ 两条边 $i$ 和 $j$ 变成长度为 $x$，且 $a_i+a_j>x$，所以 $x$ 最大的值为 $a_i+a_j-1$，接下来再使用这条边时，就等于使用了 $a_i$ 和 $a_j$ 再减 $1$，所以一共有会操作  $n-1$ 次，等于是把所有的边权相加，再减去 $n-1$。

## 代码
略。

---

## 作者：yyycj (赞：0)

## 题目简述
给定长度为 $n$ 的序列 $a$，每次操作可以选择 $a$ 中的任意两个元素，并选择一个整数 $x$，使得这三个数可以分别作为一个三角形的边，最后删除 $a$ 中的这两个元素，将 $x$ 添加到 $a$ 中。

重复操作直到 $a$ 中只有一个元素，求这个元素的最大值。

## 主要思路
小学数学题。要想组成三角形，就要满足两边之和大于第三边。想要最后剩的值最大，$x$ 的选值也要最大，那么 $x$ 就应该选择两数之和减 $1$。

每次选择两个数，总共就要选择 $n-1$ 次，添加的 $x$ 会让 $\sum a$ 减 $1$，那么最终答案就是 $\sum a-(n-1)$。

## AC Code
```cpp
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;
typedef long double db;
const int N = 2e5 + 10;
const int INT_INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
// ----------------------------

// ----------------------------

// ----------------------------


int main() {
	int t; cin >> t;
	// ----------------------------
	int n, a, sum;
	while (t--) {
		cin >> n;
		sum = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a;
			sum += a;
		}
		sum -= n - 1;
		cout << sum << '\n';
	}
	return 0;
}
```

---

## 作者：jubaoyi2011 (赞：0)

## 思路

首先我们需要了解：三角形任意两边之和大于第三边，放在这道题里就是 $a_i + a_j > x$；由于要求最后元素的最大可能值，所以要让每次添加的 $x$ 最大，也就是 $x = a_i + a_j - 1$。我们一共可以添加 $n - 1$ 个元素，所以最终答案为 $\sum{a_i} - ( n - 1 )$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int T,n,a[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		int sum=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum+=a[i];
		}
		cout<<sum-(n-1)<<endl;
	}
	return 0;
}

```

---

## 作者：cqbzhzf (赞：0)

[vjudge 中文翻译](https://vjudge.net/problem/CodeForces-2074B#author=GPT_zh)
### 思路
三角形两边之和一定大于第三边，所以对于已有的两条边 $a,b$，第三边的最大值为 $a+b-1$。

从 $n$ 条边每次选两条边，要选 $n-1$ 次，那么答案为 $\sum_{i=1}^{n} a_i-(n-1)$。
### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
int t,n,a[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		ll sum=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i],sum+=a[i];
		cout<<sum-(n-1)<<"\n";
	}
	return 0;
}
```

---

## 作者：MorningStarCzy (赞：0)

## 0x00 前言
div3 B 的题目应该还算简单的吧，至少这道题是这样的。

> 我不知道啊，我听说~~有学分~~可以写题解我就来了啊
## 0x01 思路&解法
题意：在长度为 $n$ 的序列 $a$ 中任取两个数 $a_i,a_j$ ，选择一个数 $x$ 使得 $a_i+a_j>x,a_i+x>a_j,a_j+x>a_i$ 三个条件均成立，并将 $a_i,a_j$ 删除并将 $x$ 添加至 $a$。求 $a$ 中最后一个剩余元素的最大可能值。

由于要求“最大”的值，我们可以在每次操作中都在 $a$ 中加入 $x$ 的最大值 $a_i+a_j-1$。结合样例解释以及自己手玩自己造的数据得出的结论，可以知道这种贪心策略是正确的。

注意每次取得的 $a_i$ 与 $a_j$ 应是数组中最小的两个数。

于是这道题就变得十分简单了（类似于合并果子弱化版）。详见代码。
## 0x02 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
priority_queue<int>Q;
void Solve()
{
    int n;cin>>n;
    for(int i=1;i<=n;i++)
    {
        int x;cin>>x;
        Q.push(x);
    }
    while(Q.size()>1)
    {
        int now1=Q.top();Q.pop();
        int now2=Q.top();Q.pop();
        Q.push(now1+now2-1);
    }
    cout<<Q.top()<<endl;Q.pop();
    //记得清空Q!
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;cin>>T;
    while(T--) Solve();
    return 0;
}
```

---

## 作者：xuyifei0302 (赞：0)

由于要使剩下的值最大，所以新添加的 $x$ 也要最大。

由于要满足三角形的性质：任意两边之和大于第三边，所以我们把最大的两个数和 $x$ 在一起，设最大的两个数为 $a$ 和 $b$，那么 $x$ 就为 $a + b - 1$。

然后一直贪心地添加，直到只剩一个元素为止。可以用大根堆很好地实现。

下面是代码环节：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
priority_queue<int> pq;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 1; i <= n; i ++) {
			int x;
			cin >> x;
			pq.push(x);
		}
		while (pq.size() >= 2) {
			int u = pq.top();
			pq.pop();
			int v = pq.top();
			pq.pop();
			pq.push(u + v - 1);
		}
		cout << pq.top() << "\n";
		pq.pop();
	}
	return 0;
}
```

---

## 作者：RyanLi (赞：0)

传送门：洛谷 [CF2074B The Third Side](https://www.luogu.com.cn/problem/CF2074B) | Codeforces [B. The Third Side](https://codeforces.com/contest/2074/problem/B)

更佳的阅读体验：[CF2074B 题解](https://blog.ryanli.top/index.php/archives/263/)

---

**简要题意**：给定序列 $a$，需要重复进行操作，直到 $a$ 中仅剩一个元素：选择 $a$ 中的任意两个元素，并指定一个正整数 $x$，使得这两个元素与 $x$ 可以构成三角形，然后从 $a$ 中删除选定的两个元素，并将 $x$ 插入 $a$ 末尾。求出这个剩下的元素的最大值。

首先需要考虑一个问题，什么情况下剩下的那个值可以最大？可以想到，我们需要贪心地保证每次插入的数都尽可能大才行。

接下来就需要考虑怎么求这个最大的数。

假设三角形的三条边为 $x$、$y$ 和 $z$，那么就有：
$$
\begin{cases}
x + y > z \\
x + z > y \\
y + z > x
\end{cases}
$$
我们假设从序列中取出的两个数是 $x$ 和 $y$，那么此时就需要最大化 $z$ 的值。我们首先考虑 $x + y > z$，显然有 $z \le x + y - 1$，即 $z$ 最大可以取到 $x + y - 1$。

我们将 $z = x + y - 1$ 代入其它两个式子，有：
$$
\begin{cases}
x + (x + y - 1) > y \\
y + (x + y - 1) > x
\end{cases}
\ \Longrightarrow \
\begin{cases}
2x - 1 > 0 \\
2y - 1 > 0
\end{cases}
$$
由于 $x, y \ge 1$，上式显然成立，得证。此时我们想到，只需要每次取出 $a$ 中最小的两个数 $x, y$，然后将 $x + y - 1$ 重新插入即可。

我们可以使用 `priority_queue` 来维护上述操作。每次取出堆顶的两个数，并插入一个新的数，直到堆中只剩一个元素，输出即可。

```cpp
#include <iostream>
#include <queue>
using namespace std;

const int N = 2e5 + 10;
int t, n, a, x, y;
priority_queue<int> q;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        while (!q.empty()) q.pop();
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a, q.emplace(a);
        while (q.size() > 1) {
            x = q.top();
            q.pop();
            y = q.top();
            q.pop();
            q.emplace(x + y - 1);
        } cout << q.top() << '\n';
    } return 0;
}
```

---

## 作者：Nahida_Official (赞：0)

打比赛的时候还以为是神秘题目，没想到找找规律就出来了。

题目让求将给定数组 $a$ 的任意两个元素取出后得到一个与这两个元素能构成三角形的整数 $x$，然后再把 $x$ 加入到数组里，求所有操作后的剩下那一个数字的最大值。

不妨令 $a[n]={a_1,a_2,a_3......a_n}$，我们从中任取两个数字 $a_i,a_j$，那么有且仅有一个数字 $a_k=a_i+a_j-1$ 为我们需要求的最大的 $x$。

由此，所有元素取出后的期望最大值 $fans$ 为：
$$
fans=\sum_{i = 1}^{n} a_i-(n-1)
$$
求和输出即可。
```cpp
	cin>>T;
	while(T--){
		sum=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			sum+=a[i];
		}
		sum-=(n-1);
		cout<<sum<<'\n';
	}
```

---

## 作者：_Lazy_whr_ (赞：0)

简单题。

由于每次选的 $a_i, a_j, x$ 都需要满足 $a_i + a_j > x, a_j + x > a_i, x + a_i > a_j$，所以可以得到 $x \in (|a_i - a_j|, a_i + a_j)$。

于是乎我们考虑贪心，每次取最大的两个数所以，这样得到的 $x$ 尽可能大，这样最后剩下的那个元素就是最大的。这样的话，我们可以通过贪心的策略，每次取最大的两个数合并，得到它们的和减一的值，然后将这个值放回数组中，重复直到只剩一个元素。

[AC Link](https://codeforces.com/contest/2074/submission/310204845)

---

