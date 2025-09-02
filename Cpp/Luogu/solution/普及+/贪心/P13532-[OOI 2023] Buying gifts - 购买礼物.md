# [OOI 2023] Buying gifts / 购买礼物

## 题目背景

CF1801B

## 题目描述

小萨沙有两位好朋友，他想在三八妇女节时为她们各自挑选礼物。为此，他来到了城市里最大的购物中心。

购物中心里有 $n$ 个部门，每个部门里恰好有两家商店。我们用 $1$ 到 $n$ 给这些部门编号。已知第 $i$ 个部门的第一家商店的礼物价格为 $a_i$ 卢布，第二家商店的礼物价格为 $b_i$ 卢布。

进入购物中心后，萨沙会依次经过所有 $n$ 个部门，并且在每个部门里只会进入一家商店。因此，在第 $i$ 个部门，他会做如下两种选择之一：

1. 为第一位朋友购买礼物，花费 $a_i$ 卢布。
2. 为第二位朋友购买礼物，花费 $b_i$ 卢布。

对于每位朋友，萨沙都要至少买一个礼物。此外，他还希望选择礼物的方式，使得两位朋友收到的最贵礼物的价格之差尽可能小，这样谁都不会觉得不公平。

更具体地说，设 $m_1$ 为第一位朋友收到的礼物中最贵的价格，$m_2$ 为第二位朋友收到的礼物中最贵的价格。萨沙想要最小化 $| m_1 - m_2 |$。


## 说明/提示

### 样例解释

在第一个样例中，萨沙有两种选择：在第一个部门为第一位朋友买礼物，在第二个部门为第二位朋友买礼物，或者反过来。在这两种情况下，$m_1 = m_2 = 1$ 或 $m_1 = m_2 = 2$，结果都是 $0$。

在第二个样例中，可以在第 $2$、$4$、$5$ 个部门为第一位朋友买礼物，在第 $1$、$3$ 个部门为第二位朋友买礼物。此时 $m_1 = \max(2, 4, 2) = 4$，$m_2 = \max(5, 3) = 5$，答案为 $|4 - 5| = 1$。

### 评分说明

本题测试点分为 5 组。只有通过某一组的所有测试点，且通过部分之前组的所有测试点，才能获得该组分数。

| 组别 | 分值 | $n$ | $a_i$ 和 $b_i$ | 必须通过的组 | 备注 |
|:----:|:----:|:---:|:--------------:|:------------:|:----:|
| 0    | 0    | --  | --             | --           | 样例测试点 |
| 1    | 16   | $n \le 20$ | --        | 0            | --   |
| 2    | 17   | $n \le 500$ | --       | 0, 1         | --   |
| 3    | 22   | $n \le 5000$ | --      | 0, 1, 2      | --   |
| 4    | 12   | --  | $a_i = b_i$    | --           | --   |
| 5    | 33   | --  | --             | 0--4         | --   |

## 样例 #1

### 输入

```
2
1 2
2 1```

### 输出

```
0```

## 样例 #2

### 输入

```
5
1 5
2 7
3 3
4 10
2 5```

### 输出

```
1```

# 题解

## 作者：ycy1124 (赞：2)

### 题意
在每个二元组 $(a_i,b_i)$ 中选择一个，使得选出的最大的 $b_i$ 与选出的最大的 $a_i$ 的差值的绝对值最小。
### 思路
我们首先给这些二元组按 $a_i$ 从小到大排个序。然后我们从前往后去枚举 $a_i$，我们假定我们枚举到的 $a_i$ 就是最大的那个 $a_i$，我们发现，由于我们排序后后面的 $a$ 都比这个 $a_i$ 大，所以一定会在后面取 $b$。这里的贡献我们直接后缀 $\max$ 处理。考虑前面的数，取 $a$ 肯定不会有影响，我们考虑取哪些 $b$。贪心不难发现我们一定会选第一个大于和第一个小于这个 $a_i$ 的 $b$。至于这个怎么找呢。我们可以用对顶堆和平衡树。
### 代码
这里用 set 实现。
```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;
int n, ma[N], ans = 1e9;
struct Node
{
	int a, b;
}w[N];
inline bool cmp(Node x, Node y)
{
	return x.a < y.a;
}
set<int>s;
int main()
{
	ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> w[i].a >> w[i].b;
	}
	sort(w + 1, w + n + 1, cmp);
	for(int i = n; i >= 1; i--)
	{
		ma[i] = max(ma[i + 1], w[i].b);
	}
	s.insert(-2e9), s.insert(2e9);
	for(int i = 1; i <= n; i++)
	{
		int x, y;
		auto it = s.lower_bound(w[i].a);//这里是找到set中第一个大于等于 a[i] 的值。建议不会set的学习一下。
		y = *it;
		it--;
		x = *it;
		if(x > ma[i + 1])
		{
			ans = min(abs(w[i].a - x), ans);
		}
		if(y > ma[i + 1])
		{
			ans = min(abs(w[i].a - y), ans);
		}
		ans = min(ans, abs(w[i].a - ma[i + 1]));
		s.insert(w[i].b);
	}
	cout << ans;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/228321785)。

---

## 作者：StarRoam (赞：1)

**[P13532 [OOI 2023] Buying gifts / 购买礼物](https://www.luogu.com.cn/problem/P13532)**

观察数据范围，可以推测时间复杂度大致为：$O(n \log n)$。

大致思路：枚举第一位朋友购买的礼物价格的最大值，再从数组 $B$ 中求出最优答案的选择。

我们首先按照 $A$ 从大到小排序。如果我们保证了当前 $a_i$ 是最大的，则前 $i-1$ 个数我们选的一定是 $B$ 数组，所以我们将前 $i-1$ 个 $B$ 数组中的最大数定义为 $mx$，则其中的一种选法的答案必为 $|mx-a_i|$。

但是如果满足 $mx < a_i$，最优的选择也可能位于还没有选择的数中，即从第 $i+1$ 到 $n$ 的 $B$ 数组。而最优选择尽可能使剩余数中第一个大于等于 $a_i$ 或者最后一个小于 $a_i$ 的 $b_j$ 、 $b_k$。此贡献为 $|\max(b_j,mx)-a_i|$ 与  $|\max(mx,b_k)-a_i|$。

考虑用 multiset 维护。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e5+5;
int n;
struct Data{int x,y;}a[N];
bool cmp(Data px,Data py){
	return px.x>py.x;
}
multiset<int> q;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;
	sort(a+1,a+n+1,cmp);
	int ans=1e9+5,mx=0;
	for(int i=1;i<=n;i++) q.insert(a[i].y);
	for(int i=1;i<=n;i++)
	{
		ans=min(ans,abs(mx-a[i].x));
		q.erase(a[i].y);
		if(q.size()==0) break;
		auto now=q.lower_bound(a[i].x);
		int k1=*now;
		if(now!=q.end()) ans=min(ans,abs(max(mx,k1)-a[i].x));
		if(now!=q.begin())
		{
			now--;
			k1=*now;
			ans=min(ans,abs(max(k1,mx)-a[i].x));
		}
		mx=max(mx,a[i].y);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：reinforest (赞：0)

### 简要题意

给定两个长度为 $n$ 的序列 $a$ 和 $b$，以及初始为空的可重集 $S$ 和 $T$。对于 $1 \le i \le n$ 的每一个 $i$，你可以把 $a_i$ 放在可重集 $S$ 中，或者把 $b_i$ 放在可重集 $T$ 中。最终要求 $S$ 和 $T$ 不是空集。记 $m_1$ 为 $S$ 中元素的最大值，$m_2$ 为 $T$ 中元素的最大值，要求你最小化 $|m_1-m_2|$，并输出。

$n \leq 5 \times 10^5$。

### 题解

这里会用一些“简要题意”内的表述。

一个比较好的想法是枚举序列 $a$ 中的每一个数，然后钦定这个数是 $S$ 中的最大值。记这个数为 $a_t$，最终的答案就是对于所有的 $t$ 的最小值。

首先对于所有的 $a_k > a_t$ 的下标 $k$，都要求 $b_k$ 在 $T$ 中，记这些 $b$ 组成的可重集为 $T'$。

我们实际上就是在所有的 $a_p \leq a_t$ 的下标 $p$ （不包括 $t$）中，选择一些 $b_p$，记选择的数组成的集合为 $T''$，我们只需要 $T=T' \cup T''$ 中的最大值与 $a_t$ 的差的绝对值最小。

比如说，我们在 $(1,5),(2,2),(4,6),(5,4),(6,7)$ 中，假如我们枚举到 $a_t=4$，此时 $T'=\{4,7\}$，我们可选的 $b$ 有 $\{5,2\}$，可以使 $T''=\{5\}$，使得 $T=\{5,4,7\}$，$S=\{2,4\}$ 此时的答案就是 $1$。

相信你可以发现实际上如果我们钦定了 $a_t$ 为 $S$ 中最大值，按照以上的方法无论怎么选择对于下标按照 $a_k > a_t$ 和 $a_p \leq a_t$ 分组是不会对 $S$ 中最大值产生影响的。

按照下标分组我们不难想到按照 $a$ 从大到小排序。然后从前往后遍历 $i$。

然后考虑怎么优化选择，对于所有的 $p$，称所有 $b_p$ 组成的集合为 “候选集合”，我们可以首先在候选集合中选择一个数 $c$，使得 $|c-a_i|$ 最小，然后我们就可以令 $T=\{c\} \cup T'$，计算这个集合的最大值就是这个的答案。

“候选集合”可以使用 multiset 维护，遍历到 $i$ 即在 multiset 中将 $b_i$ 删除即可；在候选集合中选择一个数 $c$，使得 $|c-a_i|$ 最小也是好查询的，在候选集合中选取 `*lower_bound(a[i])` 以及它的前驱更新答案；$T'$ 的元素最大值也是好维护的。

所以这道题就做完了。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr ll maxn=5e5+5,inf=1e18;
multiset<ll> st;
struct item{
	ll a,b;
}arr[maxn];
ll n,maxb=-inf,ans=inf;
bool cmp(item a,item b){
	if(a.a==b.a)return a.b>b.b;
	else return a.a>b.a; 
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i].a>>arr[i].b;
		st.insert(arr[i].b);
	}
	sort(arr+1,arr+n+1,cmp);
	for(int i=1;i<=n;i++){
		st.erase(st.find(arr[i].b));
		auto it=st.lower_bound(arr[i].a); 
		if(it!=st.end())ans=min(ans,abs(max(*it,maxb)-arr[i].a));
		if(it!=st.begin())ans=min(ans,abs(max(*(--it),maxb)-arr[i].a));
		maxb=max(maxb,arr[i].b);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：_cbw (赞：0)

[LOJ 1st](https://loj.ac/s/2381273)！

---

## Solution

直接做不方便，如果能先确定 $m_1$ 或 $m_2$ 中的一个，再最小化 $|m_1 - m_2|$ 就会方便很多。

我们先确定 $m_1$。为此，将 $a$ 排序。设从大到小排序后的 $a$ 的第 $i$ 个位置在原数组对应的位置是 $p_i$。

这样，枚举 $i$ 从 $1 \sim n$，则 $m_1 = a_i$ 就确定下来了，而不受 $j \in (i, n]$ 是选择 $a_j$ 还是 $b_{pos_j}$ 影响。现在的问题变成了，求 $\min_{m_2} |m_1 - m_2|$。

由于在 $m_1$ 在 $i$ 的位置取得了，因此所有的在 $i$ 之前的位置 $j$ 都必须选择 $b_{pos_j}$。
于是，$m_2$ 至少要为 $\max_{j = 1}^{i - 1} b_{pos_j}$，这个值在枚举 $i$ 的时候直接维护即可。

那么在 $i$ 后面的位置呢？由于 $m_1$ 已经确定，因此对 $j \in (i, n]$ 我们可以不受限制地进行最优化。由绝对值性质容易知道选择 $\le m_1$ 的最大的数和 $\ge m_1$ 的最小的数可以使 $|m_1 - m_2|$ 取得尽可能小的值。这个可以使用 `multiset` 进行维护，在枚举 $i$ 时不断删除其中的数即可。

时间复杂度 $\Theta(n \log n)$，空间复杂度 $\Theta(n)$。

## Code

```cpp
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iterator>
#include <set>
#define MAXN 500003
using namespace std;

namespace IO
{
#define SIZ (1 << 18)
    char ibuf[SIZ], *p1 = nullptr, *p2 = nullptr;
#define gc() (p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, SIZ, stdin), p1 == p2) ? EOF : *p1++)
    void rd(int &x)
    {
        x = 0;
        char c = gc();
        while (!isdigit(c))
            c = gc();
        while (isdigit(c))
            x = x * 10 + (c ^ 48), c = gc();
    }
#undef gc
#undef SIZ
}
using IO::rd;

struct Node
{
    int id, w;
    bool operator<(const Node &other) const
    {
        return w > other.w;
    }
} a[MAXN];
int b[MAXN];
multiset<int> st;

int main()
{
    int n, mx = 0, ans = 0x3f3f3f3f;
    rd(n);
    for (int i = 1; i <= n; ++i)
        a[i].id = i, rd(a[i].w), rd(b[i]), st.insert(b[i]);
    sort(a + 1, a + n + 1);
    multiset<int>::iterator it;
    for (int i = 1; i <= n; ++i)
    {
        st.erase(st.find(b[a[i].id]));
        ans = min(ans, abs(mx - a[i].w));
        it = st.lower_bound(a[i].w);
        if (it != st.end())
            ans = min(ans, abs(max(mx, *it) - a[i].w));
        if (it != st.begin())
            ans = min(ans, abs(max(mx, *prev(it)) - a[i].w));
        mx = max(mx, b[a[i].id]);
    }
    printf("%d", ans);
    return 0;
}
```

---

