# 题目信息

# Sereja and Swaps

## 题目描述

As usual, Sereja has array $ a $ , its elements are integers: $ a[1],a[2],...,a[n] $ . Let's introduce notation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF425A/32568eeb8040eb1aa136af55c788f7e656cb44a9.png)A swap operation is the following sequence of actions:

- choose two indexes $ i,j $ $ (i≠j) $ ;
- perform assignments $ tmp=a[i],a[i]=a[j],a[j]=tmp $ .

What maximum value of function $ m(a) $ can Sereja get if he is allowed to perform at most $ k $ swap operations?

## 样例 #1

### 输入

```
10 2
10 -1 2 2 2 2 2 2 -1 10
```

### 输出

```
32
```

## 样例 #2

### 输入

```
5 10
-1 -1 -1 -1 -1
```

### 输出

```
-1
```

# AI分析结果

### 题目中文重写
# Sereja和交换操作

## 题目描述
和往常一样，Sereja有一个数组 $ a $，它的元素都是整数：$ a[1],a[2],...,a[n] $。引入如下符号：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF425A/32568eeb8040eb1aa136af55c788f7e656cb44a9.png)交换操作是按以下步骤进行的：
- 选择两个索引 $ i,j $（$ i≠j $）；
- 执行赋值操作 $ tmp=a[i],a[i]=a[j],a[j]=tmp $。

如果Sereja最多可以进行 $ k $ 次交换操作，那么函数 $ m(a) $ 能达到的最大值是多少？

## 样例 #1
### 输入
```
10 2
10 -1 2 2 2 2 2 2 -1 10
```
### 输出
```
32
```

## 样例 #2
### 输入
```
5 10
-1 -1 -1 -1 -1
```
### 输出
```
-1
```

### 综合分析与结论
这些题解主要围绕枚举区间并结合贪心策略来解决问题，部分题解使用数据结构优化复杂度。
- **思路对比**：大部分题解通过枚举区间 $[l, r]$，然后将区间内最小值与区间外最大值交换以优化区间和；柳易辰的解法二则通过STL优化了区间递推过程；0000pnc使用动态规划求解。
- **算法要点**：多数题解采用暴力枚举区间 + 贪心交换的策略，复杂度多为 $O(n^3k)$ 或 $O(n^3\log n)$；柳易辰的解法二复杂度为 $O(n^2(\log k+\log n + k)+n)$；0000pnc的动态规划复杂度为 $O(nk^{2})$。
- **解决难点**：主要难点在于如何高效地找出区间内最小值和区间外最大值，部分题解使用优先队列、multiset等数据结构来解决。

### 所选题解
- **柳易辰（5星）**
    - **关键亮点**：使用STL对排序进行优化，通过递推减少重复计算，降低复杂度。
    - **个人心得**：提到用平衡树实现较复杂，选择用STL水掉，考虑了不同数据结构的优缺点。
```cpp
#include <set>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, k, a[210], b[210], c(-2e5); // b 记录 a 的前缀和，c 记录答案
#define ins insert
#define lb lower_bound
#define out_ins(i) out.ins(lb(out.begin(), out.end(), a[i], greater<int>()), a[i]); \
			if (out.size() > k) out.pop_back() // 在 out 中插入 a[i]
int main()
{
	scanf("%d%d", &n, &k); 
	for (int i(1); i <= n; ++i) { scanf("%d", &a[i]); b[i] = a[i] + b[i - 1]; }
	for (int l(1); l <= n; ++l)
	{
		multiset<int> in; vector<int> out;
		for (int i(l); i <= n; ++i) in.ins(a[i]);
		for (int i(1); i < l; ++i) { out_ins(i); }
		for (int r(n); r >= l; --r)
		{
			int p(0), d(b[r] - b[l - 1]); // p 代表 out 中的指针，d 记录 [l, r] 的答案
			for (int i : in)
			{
				if (p == out.size()) break;
				if (out[p] <= i) break; // 调换 in[p] 与 out[p] 不会优化答案，跳出循环
				d += out[p++] - i;
			}
			if (d > c) c = d;
			in.erase(in.lb(a[r]));
			out_ins(r);
		}
	}
	printf("%d\n", c);
	return 0;
} 
```
核心实现思想：循环枚举左端点 $l$，预处理区间 $[l, n]$ 内元素到 `in` 数组，区间 $[1, l)$ 元素到 `out` 数组；逆序枚举右端点 $r$，统计答案并更新 `in` 和 `out` 数组。

- **0000pnc（4星）**
    - **关键亮点**：使用动态规划解决问题，复杂度相对较低。
```cpp
// 伪代码，展示转移方程
f(i,j,in,out)=\begin{cases} 0 &,i \gt n,j\neq 0,in=out \\ -\infty &,i\gt n(\mathrm{otherwise}) \\ \mathrm{max}(f(i+1,0,in+1,out)+ a_{i},\kern{3pt}f(i+1,0,in,out),\kern{3pt}f(i+1,1,in,out+1),\kern{3pt}f(i+1,1,in,out)+a_{i}) &,j=0 \\ \mathrm{max}(f(in+1,1,in,out)+a_{i},\kern{3pt} f(in+1,1,in,out+1),\kern{3pt}f(i+1,2,in,out)) &,j=1 \\ \mathrm{max}(f(i+1,2,in+1,out)+a_{i},\kern{3pt}f(i+1,2,in,out) &,j=2\end{cases}
```
核心实现思想：设 $dp_{i,j,in,out}$ 表示目前 dp 到 $i$，$j$ 表示当前状态，假想的区间已经有 $in$ 个数被换进去，$out$ 个数被换出去，通过分类讨论 $j$ 的值得到转移方程。

### 最优关键思路或技巧
- 使用STL数据结构（如multiset、vector）优化排序和查找操作，减少代码复杂度。
- 利用区间递推，避免重复计算，降低时间复杂度。
- 动态规划的状态设计和转移方程推导，可用于解决类似的区间优化问题。

### 可拓展之处
同类型题可考虑增加数据规模，或改变操作规则，如交换操作变为替换操作等。类似算法套路可用于解决其他区间最值优化问题，如区间合并、区间修改等。

### 推荐洛谷题目
- P1115 最大子段和
- P2672 推销员
- P2422 良好的感觉

### 个人心得摘录与总结
- 柳易辰：意识到使用平衡树实现复杂度较高，选择用STL简化代码，体现了在实际编程中根据需求选择合适数据结构的重要性。
- 伟大的王夫子：提到刚开始会往复杂算法（如DP）思考，后来发现直接枚举和贪心更简单，提醒我们在解题时不要被固有思维局限，要从简单方法入手。 

---
处理用时：43.21秒