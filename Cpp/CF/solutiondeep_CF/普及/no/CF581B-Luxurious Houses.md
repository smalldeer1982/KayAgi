# 题目信息

# Luxurious Houses

## 题目描述

The capital of Berland has $ n $ multifloor buildings. The architect who built up the capital was very creative, so all the houses were built in one row.

Let's enumerate all the houses from left to right, starting with one. A house is considered to be luxurious if the number of floors in it is strictly greater than in all the houses with larger numbers. In other words, a house is luxurious if the number of floors in it is strictly greater than in all the houses, which are located to the right from it. In this task it is assumed that the heights of floors in the houses are the same.

The new architect is interested in $ n $ questions, $ i $ -th of them is about the following: "how many floors should be added to the $ i $ -th house to make it luxurious?" (for all $ i $ from $ 1 $ to $ n $ , inclusive). You need to help him cope with this task.

Note that all these questions are independent from each other — the answer to the question for house $ i $ does not affect other answers (i.e., the floors to the houses are not actually added).

## 样例 #1

### 输入

```
5
1 2 3 1 2
```

### 输出

```
3 2 0 2 0 ```

## 样例 #2

### 输入

```
4
3 2 1 4
```

### 输出

```
2 3 4 0 ```

# AI分析结果



# Luxurious Houses 题解分析

## 题目重述
给定一行排列的 $n$个房屋，每个房屋的楼层数已知。一个房屋被称为豪华的，当且仅当其楼层数严格大于其右侧所有房屋的楼层数。对于每个房屋，求至少需要增加多少层才能成为豪华的（所有计算独立，不影响其他房屋）。

## 算法分类
贪心

## 题解对比与结论

### 最优思路总结
**核心思路**：  
从右向左遍历，维护当前遇到的最大楼层数。每个房屋的答案取决于右侧的最大楼层数：
1. 若当前房屋楼层数 > 右侧最大楼层数 → 无需添加（输出0）
2. 否则 → 需添加 `右侧最大楼层数 - 当前楼层数 + 1` 层

**关键技巧**：  
- **逆序遍历**：通过从右向左的单次遍历，高效维护右侧最大值。
- **变量维护最大值**：使用变量而非数组存储右侧最大值，节省空间。
- **边界处理**：最后一个房屋（最右侧）无需处理，答案固定为0。

---

### 高分题解推荐

#### 题解作者：wanggk (★★★★☆)
**关键亮点**：  
- 代码简洁，变量维护最大值。
- 逆序遍历一次完成计算，时间复杂度 $O(n)$。
- 输出时强制修正最后一个元素为0，巧妙处理边界。

**核心代码**：
```cpp
int main() {
    scanf("%d", &n);
    for (int i =1; i <=n; i++) scanf("%d", &a[i]);
    int mx = 0;
    for (int i =n; i >=1; i--) {
        if (a[i] > mx) ans[i] =0;
        else ans[i] = mx +1 -a[i];
        mx = max(mx, a[i]);
    }
    // 输出时最后一个元素强制设为0
    for (int i =1; i <n; i++) printf("%d ", ans[i]);
    printf("0\n");
    return 0;
}
```

#### 题解作者：WKAHPM (★★★★☆)
**关键亮点**：  
- 预处理最大值数组 `maxn`，清晰展示右侧最大值计算过程。
- 显式处理最后一个房屋的答案，逻辑直观。

**核心代码**：
```cpp
for (int i =n; i >=2; i--)
    maxn[i] = max(h[i], maxn[i+1]);
for (int i =1; i <=n-1; i++)
    cout << max(maxn[i+1] -h[i] +1, 0) << " ";
cout <<0; // 最后一个固定输出0
```

#### 题解作者：Mysterious_bird (★★★★☆)
**关键亮点**：  
- 预处理最大值数组 `maxn`，并详细注释逻辑。
- 输出时统一取 `max(计算值, 0)`，避免负值。

**核心代码**：
```cpp
for (int i =n; i >=1; i--)
    maxn[i] = max(a[i], maxn[i+1]);
for (int i =1; i <=n; i++)
    printf("%d ", max(maxn[i+1] -a[i] +1, 0));
```

---

## 类似题目推荐
1. **P2947 [USACO09MAR] Look Up S**  
   - 逆序维护单调栈，找右侧第一个更大元素。
2. **P1901 发射站**  
   - 双向维护单调栈，处理左右相邻的极值问题。
3. **P5788 【模板】单调栈**  
   - 基础单调栈应用，找右侧第一个更大元素的位置。

---
处理用时：252.72秒