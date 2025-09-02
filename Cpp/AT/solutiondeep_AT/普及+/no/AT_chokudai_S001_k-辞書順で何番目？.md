# 题目信息

# 辞書順で何番目？

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_k

長さ $ N $ の順列のうち、$ a $ は辞書順で何番目になるかを求めなさい。

ただし、答えは非常に大きくなるため、$ 1,000,000,007 $ で割った余りを出力しなさい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100,000 $

## 样例 #1

### 输入

```
5

3 1 5 4 2```

### 输出

```
54```

## 样例 #2

### 输入

```
6

1 2 3 4 5 6```

### 输出

```
1```

## 样例 #3

### 输入

```
7

7 6 5 4 3 2 1```

### 输出

```
5040```

## 样例 #4

### 输入

```
20

19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12```

### 输出

```
542869439```

# AI分析结果

### 题目内容重写

**题目描述**

给定一个长度为 $N$ 的排列 $a$，求该排列在字典序中的排名。由于答案可能非常大，输出时需要对 $1,000,000,007$ 取模。

**说明/提示**

**约束条件**

- $1 \leq N \leq 100,000$

**样例 #1**

**输入**

```
5
3 1 5 4 2
```

**输出**

```
54
```

**样例 #2**

**输入**

```
6
1 2 3 4 5 6
```

**输出**

```
1
```

**样例 #3**

**输入**

```
7
7 6 5 4 3 2 1
```

**输出**

```
5040
```

**样例 #4**

**输入**

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12
```

**输出**

```
542869439
```

### 算法分类

**树状数组**

### 题解分析与结论

本题的核心是计算给定排列在字典序中的排名，使用康托展开公式进行计算。康托展开的基本思想是通过计算每个位置上的数在当前未使用数中的排名，乘以相应的阶乘，累加得到比当前排列小的排列数，最后加一得到当前排列的排名。

各题解的主要思路都是基于康托展开，但实现方式有所不同。大部分题解使用了树状数组来优化查询未使用数的排名，时间复杂度为 $O(n \log n)$。

### 精选题解

#### 题解1：作者：_Kenma_ (赞：2)

**星级：4星**

**关键亮点：**
- 使用树状数组优化查询未使用数的排名。
- 代码简洁，逻辑清晰。
- 详细解释了康托展开的思路和实现。

**核心代码：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,ans,a[1000005],fac[1000005];
#define lowbit(i) (i&(-i))
int c[1000005];
void modify(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=k;
	}
}
int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	ans=1;
	for(int i=n;i>=1;i--){
		ans=(ans+fac[n-i]*query(a[i])%mod)%mod;
		modify(a[i],1);
	}
	cout<<ans;
	return 0;
}
```

**核心实现思想：**
- 使用树状数组维护未使用数的排名。
- 从后向前遍历排列，计算每个位置上的数在当前未使用数中的排名，乘以阶乘后累加。

#### 题解2：作者：happybob (赞：1)

**星级：4星**

**关键亮点：**
- 使用线段树维护未使用数的排名。
- 详细解释了康托展开的公式和实现。
- 代码结构清晰，易于理解。

**核心代码：**

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

#define int long long

const int N = 1e5 + 5;
int a[N], n, mul[N], ans = 0;

constexpr int MOD()
{
	return 1000000007ll;
}

struct Node
{
	int l, r, sum;
};

Node tree[N << 2];

inline void push_up(int u)
{
	tree[u].sum = tree[u << 1ll].sum + tree[u << 1ll | 1ll].sum;
}

inline void build(int u, int l, int r)
{
	tree[u] = { l, r };
	if (l == r) tree[u].sum = 1;
	else
	{
		int mid = (l + r) >> 1;
		build(u << 1ll, l, mid);
		build(u << 1ll | 1ll, mid + 1, r);
		push_up(u);
	}
}

inline void modify(int u, int x, int v)
{
	if (tree[u].l == x && tree[u].r == x) tree[u].sum = v;
	else
	{
		int mid = (tree[u].l + tree[u].r) >> 1;
		if (x <= mid) modify(u << 1ll, x, v);
		else modify(u << 1ll | 1ll, x, v);
		push_up(u);
	}
}

inline int query(int u, int l, int r)
{
	if (tree[u].l >= l && tree[u].r <= r) return tree[u].sum;
	int mid = (tree[u].l + tree[u].r) >> 1, s = 0;
	if (l <= mid) s += query(u << 1ll, l, r);
	if (r > mid) s += query(u << 1ll | 1ll, l, r);
	return s;
}

signed main()
{
	scanf("%lld", &n);
	mul[0] = 1;
	for (int i = 1; i <= n; i++) mul[i] = mul[i - 1] * i % MOD();
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	build(1, 1, n);
	for (int i = 1; i <= n; i++)
	{
		ans += ((query(1, 1, a[i]) - 1) * mul[n - i] % MOD()) % MOD();
		ans %= MOD();
		modify(1, a[i], 0);
	}
	printf("%lld\n", (ans + 1) % MOD());
	return 0;
}
```

**核心实现思想：**
- 使用线段树维护未使用数的排名。
- 从前向后遍历排列，计算每个位置上的数在当前未使用数中的排名，乘以阶乘后累加。

### 最优关键思路与技巧

1. **康托展开**：通过计算每个位置上的数在当前未使用数中的排名，乘以相应的阶乘，累加得到比当前排列小的排列数，最后加一得到当前排列的排名。
2. **树状数组/线段树**：用于高效查询未使用数的排名，优化时间复杂度。
3. **从后向前遍历**：可以简化未使用数的排名计算，减少代码复杂度。

### 可拓展之处

- **逆康托展开**：给定排名，求出对应的排列。
- **其他排列问题**：如全排列生成、排列的逆序数计算等。

### 推荐题目

1. [P5367 康托展开](https://www.luogu.com.cn/problem/P5367)
2. [P1155 逆康托展开](https://www.luogu.com.cn/problem/P1155)
3. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)

### 个人心得摘录

- **_Kenma_**：提高 OI 水平还是应该以提高思维能力为主，学习新算法为辅。
- **happybob**：康托展开式还是十分有用的，尤其是在处理排列问题时。

---
处理用时：50.81秒