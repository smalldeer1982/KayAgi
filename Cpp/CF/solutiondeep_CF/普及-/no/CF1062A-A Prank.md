# 题目信息

# A Prank

## 题目描述

JATC and his friend Giraffe are currently in their room, solving some problems. Giraffe has written on the board an array $ a_1 $ , $ a_2 $ , ..., $ a_n $ of integers, such that $ 1 \le a_1 < a_2 < \ldots < a_n \le 10^3 $ , and then went to the bathroom.

JATC decided to prank his friend by erasing some consecutive elements in the array. Since he doesn't want for the prank to go too far, he will only erase in a way, such that Giraffe can still restore the array using the information from the remaining elements. Because Giraffe has created the array, he's also aware that it's an increasing array and all the elements are integers in the range $ [1, 10^3] $ .

JATC wonders what is the greatest number of elements he can erase?

## 说明/提示

In the first example, JATC can erase the third and fourth elements, leaving the array $ [1, 3, \_, \_, 6, 9] $ . As you can see, there is only one way to fill in the blanks.

In the second example, JATC can erase the second and the third elements. The array will become $ [998, \_, \_] $ . Because all the elements are less than or equal to $ 1000 $ , the array is still can be restored. Note, that he can't erase the first $ 2 $ elements.

In the third example, JATC can erase the first $ 4 $ elements. Since all the elements are greater than or equal to $ 1 $ , Giraffe can still restore the array. Note, that he can't erase the last $ 4 $ elements.

## 样例 #1

### 输入

```
6
1 3 4 5 6 9
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
998 999 1000
```

### 输出

```
2```

## 样例 #3

### 输入

```
5
1 2 3 4 5
```

### 输出

```
4```

# AI分析结果



# A Prank

## 题目描述

JATC 和他的朋友长颈鹿正在房间里解决问题。长颈鹿在黑板上写了一个严格递增的整数数组 $ a_1, a_2, ..., a_n $（$ 1 \le a_1 < a_2 < ... < a_n \le 10^3 $），然后去了洗手间。JATC 决定擦除数组中的一些连续元素，但要确保剩余元素能唯一还原原数组。求最多可擦除的元素数量。

## 算法分类
模拟

---

## 题解分析与结论

### 核心思路
关键点在于：**可删除的连续元素必须被左右边界唯一确定**。通过在数组首尾添加虚拟边界（0 和 1001），寻找最长连续递增 1 的区间。该区间的长度减一即为可删除的最大元素数。

### 最优思路提炼
1. **虚拟边界**：在数组前补 0，后补 1001，统一处理边界情况。
2. **连续段统计**：遍历数组，统计连续递增 1 的最长区间长度。
3. **结果计算**：最长连续段长度减一即为答案。

---

## 精选题解

### 题解1（作者：FJ·不觉·莫笑） ⭐⭐⭐⭐⭐
**关键亮点**：  
- 动态处理输入，避免数组越界。
- 时间复杂度 O(n)，空间复杂度 O(1)。

**核心代码**：
```cpp
int main() {
    int n, x = 0, y, ans = 0, len = 0;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        y = (i == n) ? 1001 : (cin >> y, y);
        if (y == x + 1) len++;
        else {
            ans = max(ans, len - 1);
            len = 0;
        }
        x = y;
    }
    cout << max(ans, len - 1);
}
```

### 题解2（作者：joy2010WonderMaker） ⭐⭐⭐⭐⭐
**关键亮点**：  
- 首尾双虚拟边界处理，逻辑清晰。
- 边读取边处理，无需存储完整数组。

**核心代码**：
```cpp
int main() {
    int a = 0, b, ans = 0, temp = 0;
    int n; scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        b = (i == n) ? 1001 : (scanf("%d", &b), b);
        if (b == a + 1) temp++;
        else {
            ans = max(ans, temp - 1);
            temp = 0;
        }
        a = b;
    }
    printf("%d", max(ans, temp - 1));
}
```

---

## 拓展与技巧
- **边界处理技巧**：通过添加虚拟元素简化边界判断，常见于数组首尾操作问题。
- **同类题目推荐**：  
  1. [P1567 统计天数](https://www.luogu.com.cn/problem/P1567)（最长连续递增序列）  
  2. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)（连续子段处理）  
  3. [P1281 最长连续子序列](https://www.luogu.com.cn/problem/P1281)（类似边界条件处理）

---

## 心得体会
- **虚拟边界**：通过添加 0 和 1001 巧妙处理数组首尾的特殊情况，避免了复杂的条件分支。
- **连续段统计**：将问题转化为最长连续递增 1 的序列，极大简化了逻辑判断。
- **踩坑警示**：数组越界问题需特别注意，动态处理输入比静态数组更安全。

---
处理用时：173.15秒