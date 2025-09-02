# 题目信息

# Divide and Summarize

## 题目描述

Mike received an array $ a $ of length $ n $ as a birthday present and decided to test how pretty it is.

An array would pass the $ i $ -th prettiness test if there is a way to get an array with a sum of elements totaling $ s_i $ , using some number (possibly zero) of slicing operations.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461D/bacc5f6e8a5007e7b78d11e0dd09c5d277e67ed2.png)An array slicing operation is conducted in the following way:

- assume $ mid = \lfloor\frac{max(array) + min(array)}{2}\rfloor $ , where $ max $ and $ min $ — are functions that find the maximum and the minimum array elements. In other words, $ mid $ is the sum of the maximum and the minimum element of $ array $ divided by $ 2 $ rounded down.
- Then the array is split into two parts $ \mathit{left} $ and $ right $ . The $ \mathit{left} $ array contains all elements which are less than or equal $ mid $ , and the $ right $ array contains all elements which are greater than $ mid $ . Elements in $ \mathit{left} $ and $ right $ keep their relative order from $ array $ .
- During the third step we choose which of the $ \mathit{left} $ and $ right $ arrays we want to keep. The chosen array replaces the current one and the other is permanently discarded.

You need to help Mike find out the results of $ q $ prettiness tests.

Note that you test the prettiness of the array $ a $ , so you start each prettiness test with the primordial (initial) array $ a $ . Thus, the first slice (if required) is always performed on the array $ a $ .

## 说明/提示

Explanation of the first test case:

1. We can get an array with the sum $ s_1 = 1 $ in the following way: 1.1 $ a = [1, 2, 3, 4, 5] $ , $ mid = \frac{1+5}{2} = 3 $ , $ \mathit{left} = [1, 2, 3] $ , $ right = [4, 5] $ . We choose to keep the $ \mathit{left} $ array.
  
   1.2 $ a = [1, 2, 3] $ , $ mid = \frac{1+3}{2} = 2 $ , $ \mathit{left} = [1, 2] $ , $ right = [3] $ . We choose to keep the $ \mathit{left} $ array.
  
   1.3 $ a = [1, 2] $ , $ mid = \frac{1+2}{2} = 1 $ , $ \mathit{left} = [1] $ , $ right = [2] $ . We choose to keep the $ \mathit{left} $ array with the sum equalling $ 1 $ .
2. It can be demonstrated that an array with the sum $ s_2 = 8 $ is impossible to generate.
3. An array with the sum $ s_3 = 9 $ can be generated in the following way: 3.1 $ a = [1, 2, 3, 4, 5] $ , $ mid = \frac{1+5}{2} = 3 $ , $ \mathit{left} = [1, 2, 3] $ , $ right = [4, 5] $ . We choose to keep the $ right $ array with the sum equalling $ 9 $ .
4. It can be demonstrated that an array with the sum $ s_4 = 12 $ is impossible to generate.
5. We can get an array with the sum $ s_5 = 6 $ in the following way: 5.1 $ a = [1, 2, 3, 4, 5] $ , $ mid = \frac{1+5}{2} = 3 $ , $ \mathit{left} = [1, 2, 3] $ , $ right = [4, 5] $ . We choose to keep the $ \mathit{left} $ with the sum equalling $ 6 $ .

Explanation of the second test case:

1. It can be demonstrated that an array with the sum $ s_1 = 1 $ is imposssible to generate.
2. We can get an array with the sum $ s_2 = 2 $ in the following way: 2.1 $ a = [3, 1, 3, 1, 3] $ , $ mid = \frac{1+3}{2} = 2 $ , $ \mathit{left} = [1, 1] $ , $ right = [3, 3, 3] $ . We choose to keep the $ \mathit{left} $ array with the sum equalling $ 2 $ .
3. It can be demonstrated that an array with the sum $ s_3 = 3 $ is imposssible to generate.
4. We can get an array with the sum $ s_4 = 9 $ in the following way: 4.1 $ a = [3, 1, 3, 1, 3] $ , $ mid = \frac{1+3}{2} = 2 $ , $ \mathit{left} = [1, 1] $ , $ right = [3, 3, 3] $ . We choose to keep the $ right $ array with the sum equalling $ 9 $ .
5. We can get an array with the sum $ s_5 = 11 $ with zero slicing operations, because array sum is equal to $ 11 $ .

## 样例 #1

### 输入

```
2
5 5
1 2 3 4 5
1
8
9
12
6
5 5
3 1 3 1 3
1
2
3
9
11```

### 输出

```
Yes
No
Yes
No
Yes
No
Yes
No
Yes
Yes```

# AI分析结果

### 题目翻译
# 划分与求和

## 题目描述
迈克收到了一个长度为 $n$ 的数组 $a$ 作为生日礼物，他决定测试一下这个数组有多“漂亮”。

一个数组如果能通过第 $i$ 次“漂亮度测试”，那么就意味着存在一种方式，通过若干次（可能为零次）切片操作，得到一个元素总和为 $s_i$ 的数组。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461D/bacc5f6e8a5007e7b78d11e0dd09c5d277e67ed2.png)数组切片操作按以下步骤进行：
- 假设 $mid = \lfloor\frac{max(array) + min(array)}{2}\rfloor$，其中 $max$ 和 $min$ 分别是找出数组中最大元素和最小元素的函数。换句话说，$mid$ 是数组中最大元素和最小元素之和除以 2 并向下取整的结果。
- 然后将数组分成两部分 $\mathit{left}$ 和 $\mathit{right}$。$\mathit{left}$ 数组包含所有小于或等于 $mid$ 的元素，$\mathit{right}$ 数组包含所有大于 $mid$ 的元素。$\mathit{left}$ 和 $\mathit{right}$ 数组中的元素保持它们在原数组中的相对顺序。
- 在第三步中，我们选择要保留 $\mathit{left}$ 和 $\mathit{right}$ 数组中的哪一个。被选中的数组将替换当前数组，另一个数组则被永久丢弃。

你需要帮助迈克找出 $q$ 次漂亮度测试的结果。

请注意，你测试的是数组 $a$ 的漂亮度，因此每次漂亮度测试都要从原始数组 $a$ 开始。因此，第一次切片（如果需要）总是在数组 $a$ 上进行。

## 说明/提示
第一个测试用例的解释：
1. 我们可以通过以下方式得到一个元素和为 $s_1 = 1$ 的数组：
   1.1 $a = [1, 2, 3, 4, 5]$，$mid = \frac{1 + 5}{2} = 3$，$\mathit{left} = [1, 2, 3]$，$\mathit{right} = [4, 5]$。我们选择保留 $\mathit{left}$ 数组。
   1.2 $a = [1, 2, 3]$，$mid = \frac{1 + 3}{2} = 2$，$\mathit{left} = [1, 2]$，$\mathit{right} = [3]$。我们选择保留 $\mathit{left}$ 数组。
   1.3 $a = [1, 2]$，$mid = \frac{1 + 2}{2} = 1$，$\mathit{left} = [1]$，$\mathit{right} = [2]$。我们选择保留 $\mathit{left}$ 数组，其元素和为 1。
2. 可以证明，无法生成元素和为 $s_2 = 8$ 的数组。
3. 可以通过以下方式生成元素和为 $s_3 = 9$ 的数组：
   3.1 $a = [1, 2, 3, 4, 5]$，$mid = \frac{1 + 5}{2} = 3$，$\mathit{left} = [1, 2, 3]$，$\mathit{right} = [4, 5]$。我们选择保留 $\mathit{right}$ 数组，其元素和为 9。
4. 可以证明，无法生成元素和为 $s_4 = 12$ 的数组。
5. 我们可以通过以下方式得到一个元素和为 $s_5 = 6$ 的数组：
   5.1 $a = [1, 2, 3, 4, 5]$，$mid = \frac{1 + 5}{2} = 3$，$\mathit{left} = [1, 2, 3]$，$\mathit{right} = [4, 5]$。我们选择保留 $\mathit{left}$ 数组，其元素和为 6。

第二个测试用例的解释：
1. 可以证明，无法生成元素和为 $s_1 = 1$ 的数组。
2. 我们可以通过以下方式得到一个元素和为 $s_2 = 2$ 的数组：
   2.1 $a = [3, 1, 3, 1, 3]$，$mid = \frac{1 + 3}{2} = 2$，$\mathit{left} = [1, 1]$，$\mathit{right} = [3, 3, 3]$。我们选择保留 $\mathit{left}$ 数组，其元素和为 2。
3. 可以证明，无法生成元素和为 $s_3 = 3$ 的数组。
4. 我们可以通过以下方式得到一个元素和为 $s_4 = 9$ 的数组：
   4.1 $a = [3, 1, 3, 1, 3]$，$mid = \frac{1 + 3}{2} = 2$，$\mathit{left} = [1, 1]$，$\mathit{right} = [3, 3, 3]$。我们选择保留 $\mathit{right}$ 数组，其元素和为 9。
5. 我们可以不进行切片操作就得到一个元素和为 $s_5 = 11$ 的数组，因为原数组的元素和就等于 11。

## 样例 #1
### 输入
```
2
5 5
1 2 3 4 5
1
8
9
12
6
5 5
3 1 3 1 3
1
2
3
9
11
```
### 输出
```
Yes
No
Yes
No
Yes
No
Yes
No
Yes
Yes
```

### 算法分类
深度优先搜索 DFS

### 综合分析与结论
这些题解的核心思路都是通过深度优先搜索（DFS）来模拟数组的切片操作，找出所有可能的数组和，再判断给定的查询值是否在这些和中。

- **思路**：先对数组进行排序，方便后续二分查找中间位置；利用前缀和来快速计算区间和；使用 DFS 递归地对数组进行切片操作，记录所有可能的和；最后对于每个查询，判断其是否在记录的和中。
- **算法要点**：排序、前缀和、DFS、二分查找。
- **解决难点**：
    - 如何高效地模拟切片操作，通过排序和二分查找来确定中间位置，减少时间复杂度。
    - 如何存储所有可能的和，使用 `map`、`set` 或数组来存储，方便后续查找。

### 高星题解
- **作者：Lynkcat (4星)**
    - **关键亮点**：思路清晰，对暴力做法的复杂度进行了分析，代码简洁。
    - **个人心得**：指出这是一道暴力题，并分析了暴力复杂度可行的原因，即 $a_i$ 的值域较小，最后跑出来的区间数有限。
- **作者：2021sunzishan (4星)**
    - **关键亮点**：思路简单直接，使用 `set` 存储所有可能的和，代码注释详细。
    - **个人心得**：提到用数论做了半天没做出来，最后发现是暴力解法，体现了对题目的思考过程。
- **作者：511_Juruo_wyk (4星)**
    - **关键亮点**：对时间复杂度进行了分析，强调这是正解而非暴力，使用 `set` 进行查询，代码规范。
    - **个人心得**：感谢他人指出错误，体现了积极的学习态度。

### 重点代码
以作者为 2021sunzishan 的题解为例，核心 DFS 函数代码如下：
```cpp
void dfs(int l,int r) {
    q.insert(s[r]-s[l-1]);//把和放进set里
    if(l==r)return;//终止条件
    int mid=upper_bound(a+l,a+1+r,(a[l]+a[r])/2)-a-1;//求出中间数的下标
    if(mid>=r)return;//注意判断边界
    dfs(l,mid);
    dfs(mid+1,r);
}
```
**核心实现思想**：该函数通过递归的方式模拟数组的切片操作。首先将当前区间的和插入到 `set` 中，若区间只有一个元素则返回；然后使用 `upper_bound` 二分查找中间位置，若中间位置不合法则返回；最后递归处理左右两个子区间。

### 可拓展之处
同类型题或类似算法套路：
- 涉及数组分割和状态搜索的问题，如将数组按一定规则分割成多个子数组，求满足特定条件的子数组组合。
- 利用 DFS 或递归模拟操作过程，结合排序、前缀和等技巧优化时间复杂度的问题。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及组合和递归搜索。
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：使用 BFS 或 DFS 搜索状态。
- [P1434 [SHOI2002] 滑雪](https://www.luogu.com.cn/problem/P1434)：结合 DFS 和记忆化搜索。

---
处理用时：61.95秒