# 题目信息

# Another Permutation Problem

## 题目描述

Andrey is just starting to come up with problems, and it's difficult for him. That's why he came up with a strange problem about permutations $ ^{\dagger} $ and asks you to solve it. Can you do it?

Let's call the cost of a permutation $ p $ of length $ n $ the value of the expression:

  $ (\sum_{i = 1}^{n} p_i \cdot i) - (\max_{j = 1}^{n} p_j \cdot j) $ . Find the maximum cost among all permutations of length $ n $ .

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the permutation with the maximum cost is $ [2, 1] $ . The cost is equal to $ 2 \cdot 1 + 1 \cdot 2 - \max (2 \cdot 1, 1 \cdot 2)= 2 + 2 - 2 = 2 $ .

In the second test case, the permutation with the maximum cost is $ [1, 2, 4, 3] $ . The cost is equal to $ 1 \cdot 1 + 2 \cdot 2 + 4 \cdot 3 + 3 \cdot 4 - 4 \cdot 3 = 17 $ .

## 样例 #1

### 输入

```
5
2
4
3
10
20```

### 输出

```
2
17
7
303
2529```

# AI分析结果

### 题目内容重写

#### 另一个排列问题

## 题目描述

Andrey 刚开始出题，对他来说这很困难。因此，他想出了一个关于排列 $ ^{\dagger} $ 的奇怪问题，并请你来解决它。你能做到吗？

我们定义一个长度为 $ n $ 的排列 $ p $ 的代价为以下表达式的值：

  $ (\sum_{i = 1}^{n} p_i \cdot i) - (\max_{j = 1}^{n} p_j \cdot j) $ 。请找出所有长度为 $ n $ 的排列中的最大代价。

 $ ^{\dagger} $ 一个长度为 $ n $ 的排列是一个由 $ n $ 个不同的整数组成的数组，这些整数从 $ 1 $ 到 $ n $ 任意排列。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是排列（$ 2 $ 在数组中出现了两次），$ [1,3,4] $ 也不是排列（$ n=3 $ 但数组中有 $ 4 $）。

## 说明/提示

在第一个测试用例中，具有最大代价的排列是 $ [2, 1] $ 。其代价为 $ 2 \cdot 1 + 1 \cdot 2 - \max (2 \cdot 1, 1 \cdot 2)= 2 + 2 - 2 = 2 $ 。

在第二个测试用例中，具有最大代价的排列是 $ [1, 2, 4, 3] $ 。其代价为 $ 1 \cdot 1 + 2 \cdot 2 + 4 \cdot 3 + 3 \cdot 4 - 4 \cdot 3 = 17 $ 。

## 样例 #1

### 输入

```
5
2
4
3
10
20```

### 输出

```
2
17
7
303
2529```

### 算法分类
构造

### 题解分析与结论

本题的核心是通过构造排列来最大化代价。大部分题解通过观察规律，发现最优排列通常是将某个后缀翻转得到的。具体来说，最优排列形如 $1, 2, \dots, k, n, n-1, \dots, k+1$，其中 $k$ 是需要枚举的翻转点。

### 精选题解

#### 1. 作者：vanishingloser (赞：6)
**星级：4.5**
**关键亮点：** 通过观察规律，发现最优排列是将某个后缀翻转得到的，并提供了暴力枚举翻转点的实现。
**个人心得：** 作者通过手玩数据发现规律，并验证了翻转后缀的有效性。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=255;
int t,n,m,x,a[N];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		int ans=0,maxn=0;
		for(int i=1;i<=n;++i)a[i]=i;
		for(int i=1;i<=n;++i)
		{
			int sum=0;
			reverse(a+i,a+n+1);
			for(int j=1;j<=n;++j)
			{
				sum+=j*a[j];
				maxn=max(maxn,j*a[j]);
			}
			ans=max(ans,sum-maxn);
			reverse(a+i,a+n+1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

#### 2. 作者：tZEROちゃん (赞：4)
**星级：4**
**关键亮点：** 通过枚举全排列打表，验证了翻转后缀的规律，并提供了简洁的实现。
**个人心得：** 作者通过打表发现规律，并验证了翻转后缀的有效性。
```cpp
void solve() {
  int n; cin >> n;
  rep (i, 1, n) {
    a[i] = i;
  }
  int ans = 0;
  auto calc = [&]() {
    int cnt = 0, mx = 0;
    rep (i, 1, n) cnt += a[i] * i;
    rep (i, 1, n) mx = max(a[i] * i, mx);
    return cnt - mx;
  };
  rep (i, 1, n) {
    reverse(a + i, a + n + 1);
    ans = max(calc(), ans);
    reverse(a + i, a + n + 1);
  }
  cout << ans << '\n';
}
```

#### 3. 作者：masonpop (赞：2)
**星级：4**
**关键亮点：** 通过爆搜找规律，发现最优排列形如 $1, 2, \dots, k, n, n-1, \dots, k+1$，并提供了 $O(n^2)$ 的实现。
**个人心得：** 作者通过爆搜发现规律，并验证了翻转后缀的有效性。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=510;
const int inf=1e15;
int t,n,a[maxn],ans;
int p[maxn];
inline int calc()
{
	int maxx=0,res=0;
	for(int i=1;i<=n;i++)res=(res+a[i]*i),maxx=max(maxx,a[i]*i);
	return res-maxx;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)a[i]=i;
	int ans=0;
	do{
		int val=calc();
		if(val>ans)
		{
			ans=val;
			for(int i=1;i<=n;i++)p[i]=a[i];
		}
	}while(next_permutation(a+1,a+n+1));
	for(int i=1;i<=n;i++)printf("%lld ",p[i]);
	puts("");
	return 0;
}
```

### 最优关键思路与技巧
通过观察和打表发现，最优排列通常是将某个后缀翻转得到的。具体来说，最优排列形如 $1, 2, \dots, k, n, n-1, \dots, k+1$，其中 $k$ 是需要枚举的翻转点。这种构造方法可以有效地最大化代价。

### 可拓展之处
类似的问题可以通过构造排列或翻转子序列来优化目标函数。这种思路可以应用于其他需要最大化或最小化某种代价的排列问题。

### 推荐题目
1. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)
2. [P1088 火星人](https://www.luogu.com.cn/problem/P1088)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

---
处理用时：44.28秒