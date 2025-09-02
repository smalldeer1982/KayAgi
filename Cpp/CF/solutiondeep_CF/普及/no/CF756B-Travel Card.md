# 题目信息

# Travel Card

## 题目描述

A new innovative ticketing systems for public transport is introduced in Bytesburg. Now there is a single travel card for all transport. To make a trip a passenger scan his card and then he is charged according to the fare.

The fare is constructed in the following manner. There are three types of tickets:

1. a ticket for one trip costs $ 20 $ byteland rubles,
2. a ticket for $ 90 $ minutes costs $ 50 $ byteland rubles,
3. a ticket for one day ( $ 1440 $ minutes) costs $ 120 $ byteland rubles.

Note that a ticket for $ x $ minutes activated at time $ t $ can be used for trips started in time range from $ t $ to $ t+x-1 $ , inclusive. Assume that all trips take exactly one minute.

To simplify the choice for the passenger, the system automatically chooses the optimal tickets. After each trip starts, the system analyses all the previous trips and the current trip and chooses a set of tickets for these trips with a minimum total cost. Let the minimum total cost of tickets to cover all trips from the first to the current is $ a $ , and the total sum charged before is $ b $ . Then the system charges the passenger the sum $ a-b $ .

You have to write a program that, for given trips made by a passenger, calculates the sum the passenger is charged after each trip.

## 说明/提示

In the first example, the system works as follows: for the first and second trips it is cheaper to pay for two one-trip tickets, so each time $ 20 $ rubles is charged, after the third trip the system understands that it would be cheaper to buy a ticket for $ 90 $ minutes. This ticket costs $ 50 $ rubles, and the passenger had already paid $ 40 $ rubles, so it is necessary to charge $ 10 $ rubles only.

## 样例 #1

### 输入

```
3
10
20
30
```

### 输出

```
20
20
10
```

## 样例 #2

### 输入

```
10
13
45
46
60
103
115
126
150
256
516
```

### 输出

```
20
20
10
0
20
0
0
20
20
10
```

# AI分析结果



# Travel Card 中文翻译

## 题目描述

字节堡市推出了创新的公共交通票务系统。乘客每次乘车时刷卡，系统会根据最优票价策略自动扣费。票价规则如下：

- 单次票：20 卢布（覆盖 1 分钟）
- 90 分钟票：50 卢布（覆盖连续 90 分钟内的所有行程）
- 1440 分钟票：120 卢布（覆盖连续 24 小时内的所有行程）

每次乘车后，系统会重新计算包含当前行程的所有行程的最小总费用，并扣除本次新增费用。要求输出每次乘车后的增量费用。

**样例解释**  
例如前三次乘车时间分别为 10、20、30 分钟时：  
- 第三次乘车后，前三次可被 90 分钟票覆盖（总费用 50），扣除 50 - 20*2 = 10 卢布

**算法分类**  
动态规划

---

## 题解分析与结论

### 核心思路对比
| 方法         | 时间复杂度 | 核心技巧                     | 优势                          |
|--------------|------------|------------------------------|-------------------------------|
| 二分+动态规划 | O(n log n) | 使用 lower_bound 查找时间边界 | 代码简洁，逻辑清晰            |
| 双指针+动态规划 | O(n)      | 维护滑动窗口的左右指针        | 理论更优，但实现细节较多      |
| 队列模拟     | O(n)       | 实时维护两个时间窗口的费用    | 思路新颖，但正确性需要验证    |

### 最优题解推荐

1. **封禁用户（★★★★☆）**  
   **亮点**：  
   - 使用标准二分查找确定时间边界  
   - 状态转移方程简洁直观  
   ```cpp
   int x=lower_bound(a+1,a+i+1,a[i]-89)-a-1;
   f[i]=min(f[i],f[x]+50);
   int y=lower_bound(a+1,a+i+1,a[i]-1439)-a-1;
   f[i]=min(f[i],f[y]+120);
   ```

2. **ChenZQ（★★★★☆）**  
   **亮点**：  
   - 双指针维护滑动窗口  
   - 兼容未排序输入的预处理  
   ```cpp
   while(abs(a[i]-a[l1])>=90) l1++;
   while(abs(a[i]-a[l2])>1439) l2++;
   ```

3. **Sol1（★★★☆☆）**  
   **亮点**：  
   - 显式处理边界值（-INF）  
   - 验证有效行程数阈值  

---

## 关键实现技巧

**动态规划 + 二分查找**：  
1. 预处理行程时间排序  
2. 定义 `dp[i]` 表示前 `i` 次行程的最小费用  
3. 状态转移：  
   ```cpp
   dp[i] = min({
       dp[i-1] + 20,  // 单次票
       dp[lower_bound(90分钟边界)] + 50, 
       dp[lower_bound(1440分钟边界)] + 120
   });
   ```

---

## 同类题目推荐
1. [P2585 三色二叉树](https://www.luogu.com.cn/problem/P2585) - 树形DP  
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044) - 递推型DP  
3. [P3572 PTA-Little Bird](https://www.luogu.com.cn/problem/P3572) - 单调队列优化DP

---
处理用时：53.47秒