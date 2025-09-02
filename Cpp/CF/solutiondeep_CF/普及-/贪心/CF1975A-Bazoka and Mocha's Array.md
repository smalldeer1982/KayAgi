# 题目信息

# Bazoka and Mocha's Array

## 题目描述

Mocha likes arrays, so before her departure, Bazoka gave her an array $ a $ consisting of $ n $ positive integers as a gift.

Now Mocha wants to know whether array $ a $ could become sorted in non-decreasing order after performing the following operation some (possibly, zero) times:

- Split the array into two parts — a prefix and a suffix, then swap these two parts. In other words, let $ a=x+y $ . Then, we can set $ a:= y+x $ . Here $ + $ denotes the array concatenation operation.

For example, if $ a=[3,1,4,1,5] $ , we can choose $ x=[3,1] $ and $ y=[4,1,5] $ , satisfying $ a=x+y $ . Then, we can set $ a:= y + x = [4,1,5,3,1] $ . We can also choose $ x=[3,1,4,1,5] $ and $ y=[\,] $ , satisfying $ a=x+y $ . Then, we can set $ a := y+x = [3,1,4,1,5] $ . Note that we are not allowed to choose $ x=[3,1,1] $ and $ y=[4,5] $ , neither are we allowed to choose $ x=[1,3] $ and $ y=[5,1,4] $ , as both these choices do not satisfy $ a=x+y $ .

## 说明/提示

In the first test case, it can be proven that $ a $ cannot become non-decreasing after performing the operation any number of times.

In the second test case, we can perform the following operations to make $ a $ sorted in non-decreasing order:

- Split the array into two parts: $ x=[7] $ and $ y=[9,2,2,3] $ , then swap these two parts. The array will become $ y+x = [9,2,2,3,7] $ .
- Split the array into two parts: $ x=[9] $ and $ y=[2,2,3,7] $ , then swap these two parts. The array will become $ y+x=[2,2,3,7,9] $ , which is non-decreasing.

## 样例 #1

### 输入

```
3
6
1 1 4 5 1 4
5
7 9 2 2 3
3
1 2 3```

### 输出

```
No
Yes
Yes```

# AI分析结果



# Bazoka and Mocha's Array

## 题目描述

Mocha 喜欢数组，Bazoka 在离别前送给她一个由 $n$ 个正整数组成的数组 $a$ 作为礼物。

现在 Mocha 想知道，是否可以通过执行以下操作若干次（可能为零次），使得数组 $a$ 变为非递减排序：

- 将数组分割为一个前缀和一个后缀，然后交换这两个部分。具体来说，将数组 $a$ 表示为 $x+y$，然后将其变为 $y+x$，其中 $+$ 表示数组连接操作。

例如，若 $a=[3,1,4,1,5]$，选择 $x=[3,1]$ 和 $y=[4,1,5]$，则交换后得到 $y+x=[4,1,5,3,1]$。也可以选择 $x$ 为整个数组，$y$ 为空数组，此时数组保持不变。

## 说明/提示

第一个样例中，无法通过任何操作使数组非递减。

第二个样例中，通过两次操作可得到非递减数组：
1. 分割为 $x=[7]$ 和 $y=[9,2,2,3]$，交换后得到 $[9,2,2,3,7]$。
2. 再次分割 $x=[9]$ 和 $y=[2,2,3,7]$，交换后得到 $[2,2,3,7,9]$。

## 样例 #1

### 输入

```
3
6
1 1 4 5 1 4
5
7 9 2 2 3
3
1 2 3
```

### 输出

```
No
Yes
Yes
```

---

### 综合分析与结论

本题的关键在于判断数组是否存在一个循环移位后的形式是非递减的。通过分析下降点的数量和位置，可以高效解决问题：

#### 核心思路
1. **下降点统计**：遍历数组统计相邻元素中的下降点（`a[i] > a[i+1]`）。
2. **直接判断**：
   - 若下降点数为 0，数组已非递减，返回 "Yes"。
   - 若下降点数超过 1，无法通过循环移位得到非递减数组，返回 "No"。
   - 若下降点数为 1，构造循环移位后的数组（将下降点后的部分移到前面），检查其是否非递减。

#### 解决难点
- **高效构造循环移位**：无需实际生成所有可能的移位数组，只需根据唯一的下降点构造一次即可。
- **复杂度优化**：通过 O(n) 的线性扫描和一次构造验证，避免了 O(n²) 的暴力检查。

### 最优题解

#### 题解关键代码
```python
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    cnt = 0
    pos = -1
    for i in range(n-1):
        if a[i] > a[i+1]:
            cnt += 1
            pos = i
    if cnt == 0:
        print("Yes")
    elif cnt == 1:
        new_arr = a[pos+1:] + a[:pos+1]
        ok = True
        for i in range(len(new_arr)-1):
            if new_arr[i] > new_arr[i+1]:
                ok = False
                break
        print("Yes" if ok else "No")
    else:
        print("No")
```

#### 评分与亮点
- **★★★★★**  
  **亮点**：  
  - 通过下降点数量快速缩小判断范围。
  - 线性时间复杂度，高效处理大规模数据。
  - 代码简洁，逻辑清晰。

### 关键技巧
- **下降点分析**：通过统计下降点数量快速判断可能存在的循环移位情况。
- **构造验证法**：仅需构造并验证唯一可能的循环移位形式，避免无效计算。

### 扩展与相似题目
1. **循环数组排序**：类似思路可解决循环移位后的极值问题（如 [CF 976B](https://codeforces.com/problemset/problem/976/B)）。
2. **旋转数组查找**：如 LeetCode 33 题（搜索旋转排序数组）。
3. **非递减数组修复**：如 LeetCode 665 题（最多修改一个元素使数组非递减）。

### 推荐题目
1. [洛谷 P1908 逆序对](https://www.luogu.com.cn/problem/P1908)  
   **考察点**：统计逆序对，与下降点分析类似。
2. [洛谷 P1969 积木大赛](https://www.luogu.com.cn/problem/P1969)  
   **考察点**：分段递增结构的处理。
3. [洛谷 P5662 纪念品](https://www.luogu.com.cn/problem/P5662)  
   **考察点**：动态规划与循环结构结合的问题。

---
处理用时：353.62秒