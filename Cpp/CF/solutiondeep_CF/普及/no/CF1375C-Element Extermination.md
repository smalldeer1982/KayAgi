# 题目信息

# Element Extermination

## 题目描述

You are given an array $ a $ of length $ n $ , which initially is a permutation of numbers from $ 1 $ to $ n $ . In one operation, you can choose an index $ i $ ( $ 1 \leq i < n $ ) such that $ a_i < a_{i +       1} $ , and remove either $ a_i $ or $ a_{i + 1} $ from the array (after the removal, the remaining parts are concatenated).

For example, if you have the array $ [1, 3, 2] $ , you can choose $ i = 1 $ (since $ a_1 = 1 < a_2 = 3 $ ), then either remove $ a_1 $ which gives the new array $ [3, 2] $ , or remove $ a_2 $ which gives the new array $ [1, 2] $ .

Is it possible to make the length of this array equal to $ 1 $ with these operations?

## 说明/提示

For the first two test cases and the fourth test case, we can operate as follow (the bolded elements are the pair chosen for that operation):

 $ [\text{1}, \textbf{2}, \textbf{3}] \rightarrow [\textbf{1},       \textbf{2}] \rightarrow [\text{1}] $

 $ [\text{3}, \textbf{1}, \textbf{2}, \text{4}] \rightarrow       [\text{3}, \textbf{1}, \textbf{4}] \rightarrow [\textbf{3},       \textbf{4}] \rightarrow [\text{4}] $

 $ [\textbf{2}, \textbf{4}, \text{6}, \text{1}, \text{3},       \text{5}] \rightarrow [\textbf{4}, \textbf{6}, \text{1}, \text{3},       \text{5}] \rightarrow [\text{4}, \text{1}, \textbf{3}, \textbf{5}]       \rightarrow [\text{4}, \textbf{1}, \textbf{5}] \rightarrow       [\textbf{4}, \textbf{5}] \rightarrow [\text{4}] $

## 样例 #1

### 输入

```
4
3
1 2 3
4
3 1 2 4
3
2 3 1
6
2 4 6 1 3 5```

### 输出

```
YES
YES
NO
YES```

# AI分析结果

### 题目内容重写

**元素消除**

#### 题目描述

给定一个长度为 $n$ 的数组 $a$，初始时它是从 $1$ 到 $n$ 的一个排列。在一次操作中，你可以选择一个索引 $i$（$1 \leq i < n$），使得 $a_i < a_{i+1}$，然后删除 $a_i$ 或 $a_{i+1}$ 中的一个（删除后，剩余部分会拼接在一起）。

例如，如果你有数组 $[1, 3, 2]$，你可以选择 $i = 1$（因为 $a_1 = 1 < a_2 = 3$），然后删除 $a_1$，得到新数组 $[3, 2]$，或者删除 $a_2$，得到新数组 $[1, 2]$。

问：是否可以通过这些操作将数组的长度减少到 $1$？

#### 说明/提示

对于前两个测试用例和第四个测试用例，我们可以如下操作（加粗的元素是每次操作选择的元素对）：

$[\text{1}, \textbf{2}, \textbf{3}] \rightarrow [\textbf{1}, \textbf{2}] \rightarrow [\text{1}]$

$[\text{3}, \textbf{1}, \textbf{2}, \text{4}] \rightarrow [\text{3}, \textbf{1}, \textbf{4}] \rightarrow [\textbf{3}, \textbf{4}] \rightarrow [\text{4}]$

$[\textbf{2}, \textbf{4}, \text{6}, \text{1}, \text{3}, \text{5}] \rightarrow [\textbf{4}, \textbf{6}, \text{1}, \text{3}, \text{5}] \rightarrow [\text{4}, \text{1}, \textbf{3}, \textbf{5}] \rightarrow [\text{4}, \textbf{1}, \textbf{5}] \rightarrow [\textbf{4}, \textbf{5}] \rightarrow [\text{4}]$

#### 样例 #1

##### 输入

```
4
3
1 2 3
4
3 1 2 4
3
2 3 1
6
2 4 6 1 3 5
```

##### 输出

```
YES
YES
NO
YES
```

### 算法分类

**贪心**

### 题解分析与结论

本题的核心思路是通过贪心策略判断是否可以将数组缩减到长度为1。大多数题解都基于一个关键结论：如果数组的第一个元素 $a_1$ 小于最后一个元素 $a_n$，则可以通过一系列操作将数组缩减到1，否则无法做到。

#### 关键思路

1. **贪心策略**：通过保留数组的第一个和最后一个元素，确保在操作过程中能够逐步缩减数组。
2. **边界条件**：如果 $a_1 < a_n$，则可以通过删除中间的元素，最终保留 $a_1$ 或 $a_n$。
3. **反证法**：如果 $a_1 > a_n$，则无论如何操作，最终无法将数组缩减到1。

#### 最优题解

**题解作者：三点水一个各 (赞：23)**

- **星级**：5星
- **关键亮点**：详细证明了为什么 $a_1 < a_n$ 是能够缩减数组到1的充分必要条件，并通过递推的方式解释了如何通过贪心策略逐步缩减数组。
- **代码实现**：简洁明了，直接判断 $a_1$ 和 $a_n$ 的大小关系。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,x,a,b,n;
int main()
{
   scanf("%lld",&t);
   for(ll kk=1;kk<=t;++kk)
   {
       scanf("%lld",&n);
       for(int i=1;i<=n;++i)
       {
           scanf("%lld",&x);
           if(i==1) a=x; if(i==n) b=x;
       }
       if(a<b) printf("YES\n");
       else printf("NO\n");
   }
   return 0;
}
```

**题解作者：5k_sync_closer (赞：4)**

- **星级**：4星
- **关键亮点**：通过观察操作过程中数组两端的变化，证明了 $a_1 < a_n$ 的必要性，并给出了具体的操作策略。
- **代码实现**：同样简洁，直接判断 $a_1$ 和 $a_n$ 的大小关系。

```cpp
#include <cstdio>
int T, n, a[300050];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        puts(a[1] < a[n] ? "YES" : "NO");
    }
    return 0;
}
```

**题解作者：Andrewzdm (赞：3)**

- **星级**：4星
- **关键亮点**：从对立面思考，证明了 $a_1 > a_n$ 时无法缩减数组到1，并给出了具体的操作策略。
- **代码实现**：简洁明了，直接判断 $a_1$ 和 $a_n$ 的大小关系。

```cpp
#include<cstdio>
const int maxn = 3e5 + 10;
int a[maxn];

void solve()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", a + i);
	puts(a[n] > a[1] ? "YES" : "NO");
	return;
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
```

### 最优关键思路

通过贪心策略，保留数组的第一个和最后一个元素，确保在操作过程中能够逐步缩减数组。最终结论是：如果 $a_1 < a_n$，则可以通过一系列操作将数组缩减到1，否则无法做到。

### 可拓展之处

类似的问题可以通过贪心策略解决，尤其是在涉及数组缩减或合并操作时。可以通过保留关键元素（如数组的两端）来简化问题。

### 推荐题目

1. [CF1375C Element Extermination](https://www.luogu.com.cn/problem/CF1375C)
2. [CF1370D Odd-Even Subsequence](https://www.luogu.com.cn/problem/CF1370D)
3. [CF1367D Task On The Board](https://www.luogu.com.cn/problem/CF1367D)

### 个人心得

大多数题解都基于一个关键结论：如果数组的第一个元素 $a_1$ 小于最后一个元素 $a_n$，则可以通过一系列操作将数组缩减到1，否则无法做到。这个结论的证明过程展示了贪心策略在解决数组缩减问题中的有效性。

---
处理用时：47.25秒