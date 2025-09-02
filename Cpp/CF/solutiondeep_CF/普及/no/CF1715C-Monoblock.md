# 题目信息

# Monoblock

## 题目描述

Stanley has decided to buy a new desktop PC made by the company "Monoblock", and to solve captcha on their website, he needs to solve the following task.

The awesomeness of an array is the minimum number of blocks of consecutive identical numbers in which the array could be split. For example, the awesomeness of an array

- $ [1, 1, 1] $ is $ 1 $ ;
- $ [5, 7] $ is $ 2 $ , as it could be split into blocks $ [5] $ and $ [7] $ ;
- $ [1, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9] $ is 3, as it could be split into blocks $ [1] $ , $ [7, 7, 7, 7, 7, 7, 7] $ , and $ [9, 9, 9, 9, 9, 9, 9, 9, 9] $ .

You are given an array $ a $ of length $ n $ . There are $ m $ queries of two integers $ i $ , $ x $ . A query $ i $ , $ x $ means that from now on the $ i $ -th element of the array $ a $ is equal to $ x $ .

After each query print the sum of awesomeness values among all subsegments of array $ a $ . In other words, after each query you need to calculate $ $$$\sum\limits_{l = 1}^n \sum\limits_{r = l}^n g(l, r), $ $  where  $ g(l, r) $  is the awesomeness of the array  $ b = \[a\_l, a\_{l + 1}, \\ldots, a\_r\]$$$.

## 说明/提示

After the first query $ a $ is equal to $ [1, 2, 2, 4, 5] $ , and the answer is $ 29 $ because we can split each of the subsegments the following way:

1. $ [1; 1] $ : $ [1] $ , 1 block;
2. $ [1; 2] $ : $ [1] + [2] $ , 2 blocks;
3. $ [1; 3] $ : $ [1] + [2, 2] $ , 2 blocks;
4. $ [1; 4] $ : $ [1] + [2, 2] + [4] $ , 3 blocks;
5. $ [1; 5] $ : $ [1] + [2, 2] + [4] + [5] $ , 4 blocks;
6. $ [2; 2] $ : $ [2] $ , 1 block;
7. $ [2; 3] $ : $ [2, 2] $ , 1 block;
8. $ [2; 4] $ : $ [2, 2] + [4] $ , 2 blocks;
9. $ [2; 5] $ : $ [2, 2] + [4] + [5] $ , 3 blocks;
10. $ [3; 3] $ : $ [2] $ , 1 block;
11. $ [3; 4] $ : $ [2] + [4] $ , 2 blocks;
12. $ [3; 5] $ : $ [2] + [4] + [5] $ , 3 blocks;
13. $ [4; 4] $ : $ [4] $ , 1 block;
14. $ [4; 5] $ : $ [4] + [5] $ , 2 blocks;
15. $ [5; 5] $ : $ [5] $ , 1 block;

 which is $ 1 + 2 + 2 + 3 + 4 + 1 + 1 + 2 + 3 + 1 + 2 + 3 + 1 + 2 + 1 = 29 $ in total.

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
3 2
4 2
3 1
2 1
2 2```

### 输出

```
29
23
35
25
35```

# AI分析结果

### 题目内容重写

**题目描述**

Stanley决定购买由公司“Monoblock”生产的新台式电脑，为了在网站上解决验证码，他需要完成以下任务。

一个数组的“awesome值”是指将该数组分割成连续相同数字块的最小数量。例如，数组的awesome值：

- $ [1, 1, 1] $ 是 $ 1 $；
- $ [5, 7] $ 是 $ 2 $，因为它可以分割成块 $ [5] $ 和 $ [7] $；
- $ [1, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9] $ 是 3，因为它可以分割成块 $ [1] $，$ [7, 7, 7, 7, 7, 7, 7] $，和 $ [9, 9, 9, 9, 9, 9, 9, 9, 9] $。

给定一个长度为 $ n $ 的数组 $ a $，有 $ m $ 个查询，每个查询包含两个整数 $ i $ 和 $ x $。查询 $ i $，$ x $ 表示从现在开始，数组 $ a $ 的第 $ i $ 个元素等于 $ x $。

在每个查询之后，输出数组 $ a $ 的所有子段的awesome值之和。换句话说，在每个查询之后，你需要计算：

$$ \sum\limits_{l = 1}^n \sum\limits_{r = l}^n g(l, r), $$

其中 $ g(l, r) $ 是数组 $ b = [a_l, a_{l + 1}, \ldots, a_r] $ 的awesome值。

### 算法分类
数学、递推

### 题解分析与结论

本题的核心在于如何高效计算每次修改后所有子段的awesome值之和。题解中主要思路是通过分析每个位置的变化对整体答案的影响，利用数学公式和递推关系来快速更新答案。

### 所选高星题解

#### 题解1：作者：liangbowen (赞：17)
**星级：5星**
**关键亮点：**
- 通过分析每个位置的贡献，利用数学公式快速计算每个查询后的答案。
- 代码简洁，逻辑清晰，易于理解。
- 通过减去和重新加上贡献的方式，避免了重复计算。

**核心代码：**
```cpp
LL calc(int i) {
	LL k = n - i + 1;
	if (a[i-1] == a[i]) return k;
	return 1ll * (i - 1) * (n - i + 1) + k;
}
```
**实现思想：**
通过计算每个位置与前一个位置的贡献，快速更新答案。每次修改时，先减去旧贡献，再重新计算新贡献。

#### 题解2：作者：Zigh_Wang (赞：11)
**星级：4星**
**关键亮点：**
- 通过预处理和分类讨论，详细分析了每种修改情况对答案的影响。
- 提供了详细的分类讨论，确保每种情况都被正确处理。

**核心代码：**
```cpp
if(a[id] == a[id - 1] && x != a[id - 1])
	ans += 1ll * (id - 1) * (n - id + 1);
if(a[id] != a[id - 1] && x == a[id - 1])
	ans -= 1ll * (id - 1) * (n - id + 1);
```
**实现思想：**
通过分类讨论，详细分析了每种修改情况对答案的影响，确保每次修改后答案的正确性。

#### 题解3：作者：luo_shen (赞：6)
**星级：4星**
**关键亮点：**
- 通过维护每个位置的贡献，快速更新答案。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
ans-=(a[x]!=a[x-1])*(n-x+1)*(x-1);
ans-=(a[x+1]!=a[x])*(n-x)*x;
a[x]=y;
ans+=(a[x]!=a[x-1])*(n-x+1)*(x-1);
ans+=(a[x+1]!=a[x])*(n-x)*x;
```
**实现思想：**
通过维护每个位置的贡献，快速更新答案，确保每次修改后答案的正确性。

### 最优关键思路或技巧
- **贡献分析**：通过分析每个位置的变化对整体答案的贡献，利用数学公式快速更新答案。
- **分类讨论**：详细分析每种修改情况对答案的影响，确保每次修改后答案的正确性。
- **递推关系**：利用递推关系快速计算每个查询后的答案，避免重复计算。

### 可拓展之处
- 类似的问题可以通过贡献分析和分类讨论来解决，例如区间修改和查询问题。
- 可以通过维护前缀和或其他数据结构来进一步优化计算。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)

### 个人心得摘录
- **调试经历**：在处理边界情况时，需要特别注意，确保每种情况都被正确处理。
- **顿悟感想**：通过贡献分析和分类讨论，可以大大简化问题的复杂度，提高代码的可读性和效率。

---
处理用时：36.98秒