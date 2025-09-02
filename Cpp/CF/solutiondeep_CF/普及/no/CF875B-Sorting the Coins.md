# 题目信息

# Sorting the Coins

## 题目描述

Recently, Dima met with Sasha in a philatelic store, and since then they are collecting coins together. Their favorite occupation is to sort collections of coins. Sasha likes having things in order, that is why he wants his coins to be arranged in a row in such a way that firstly come coins out of circulation, and then come coins still in circulation.

For arranging coins Dima uses the following algorithm. One step of his algorithm looks like the following:

1. He looks through all the coins from left to right;
2. If he sees that the $ i $ -th coin is still in circulation, and $ (i+1) $ -th coin is already out of circulation, he exchanges these two coins and continues watching coins from $ (i+1) $ -th.

Dima repeats the procedure above until it happens that no two coins were exchanged during this procedure. Dima calls hardness of ordering the number of steps required for him according to the algorithm above to sort the sequence, e.g. the number of times he looks through the coins from the very beginning. For example, for the ordered sequence hardness of ordering equals one.

Today Sasha invited Dima and proposed him a game. First he puts $ n $ coins in a row, all of them are out of circulation. Then Sasha chooses one of the coins out of circulation and replaces it with a coin in circulation for $ n $ times. During this process Sasha constantly asks Dima what is the hardness of ordering of the sequence.

The task is more complicated because Dima should not touch the coins and he should determine hardness of ordering in his mind. Help Dima with this task.

## 说明/提示

Let's denote as O coin out of circulation, and as X — coin is circulation.

At the first sample, initially in row there are coins that are not in circulation, so Dima will look through them from left to right and won't make any exchanges.

After replacement of the first coin with a coin in circulation, Dima will exchange this coin with next three times and after that he will finally look through the coins and finish the process.

XOOO $ → $ OOOX

After replacement of the third coin, Dima's actions look this way:

XOXO $ → $ OXOX $ → $ OOXX

After replacement of the fourth coin, Dima's actions look this way:

XOXX $ → $ OXXX

Finally, after replacement of the second coin, row becomes consisting of coins that are in circulation and Dima will look through coins from left to right without any exchanges.

## 样例 #1

### 输入

```
4
1 3 4 2
```

### 输出

```
1 2 3 2 1
```

## 样例 #2

### 输入

```
8
6 8 3 4 7 2 1 5
```

### 输出

```
1 2 2 3 4 3 4 5 1
```

# AI分析结果



### 题目内容
# 排序硬币的难度

## 题目描述

Dima 和 Sasha 收集硬币，并希望将硬币排列成“流通中”（X）在后、“停止流通”（O）在前的顺序。Dima 的排序算法每次从左到右遍历硬币，若发现某硬币是 X 且右侧是 O，则交换它们，并继续检查下一个位置。重复此过程直到某次遍历中没有交换发生。排序的“难度”即所需的完整遍历次数。

初始时所有硬币均为 O。Sasha 进行 n 次操作，每次将某个硬币翻转为 X。每次操作后需立即计算当前硬币序列的排序难度。

## 输入输出样例

### 样例 #1

输入：
```
4
1 3 4 2
```
输出：
```
1 2 3 2 1
```

### 样例 #2

输入：
```
8
6 8 3 4 7 2 1 5
```
输出：
```
1 2 2 3 4 3 4 5 1
```

---

### 算法分类
模拟、贪心

---

### 题解综合分析与结论

**核心思路**：每次操作后，计算当前 X 的总数（i）减去末尾连续的 X 的数量（j），再加 1。即 **难度 = i - j + 1**。  
**难点**：快速维护末尾连续 X 的数量。通过逆序存储硬币位置并维护指针 r（指向当前最右侧的非 X 位置），可以高效更新 j。

---

### 精选题解

#### 作者：Withershine（★★★★☆）
**关键亮点**：  
1. 逆序存储硬币，简化末尾连续 X 的判断。  
2. 维护指针 r，每次操作后从右向左更新，确保 O(1) 均摊时间复杂度。  
**个人心得**：通过逆序存储硬币位置，将问题转换为从右向左的连续判断，极大简化代码逻辑。

**核心代码**：
```cpp
ll n, ex, coin[300005];
ll ans, r;

int main() {
    r = n = read();
    printf("1 ");
    n--;
    while (n >= 1) {
        ans++;
        ex = read();
        coin[ex] = 1;
        while (coin[r] == 1) {
            r--;
            ans--;
        }
        printf("%lld ", ans + 1);
        n--;
    }
    printf("1");
}
```
**代码思想**：  
- `coin` 数组逆序存储硬币状态，`r` 初始为 n。  
- 每次操作更新对应位置为 X，然后从 `r` 向左寻找第一个非 X 的位置，更新连续 X 的数量。  
- 难度计算为当前 X 总数（`ans` 初始递增）减去连续 X 数（循环中递减），再加 1。

---

### 最优思路总结
1. **逆序存储**：将硬币位置逆序处理，便于从右向左维护连续 X 的边界。  
2. **贪心维护指针**：使用指针 r 记录最右侧的非 X 位置，每次操作后只需线性扫描减少 r。  
3. **公式计算**：通过 `i - j + 1` 直接计算难度，其中 i 是操作次数，j 是末尾连续 X 数。

---

### 拓展与相似题目
1. **CF1157B**（模拟与贪心维护边界）  
2. **P1106 删数问题**（贪心维护最优序列）  
3. **P1563 玩具谜题**（逆序与指针操作）

---
处理用时：391.91秒