# 题目信息

# The Fair Nut and Elevator

## 题目描述

The Fair Nut lives in $ n $ story house. $ a_i $ people live on the $ i $ -th floor of the house. Every person uses elevator twice a day: to get from the floor where he/she lives to the ground (first) floor and to get from the first floor to the floor where he/she lives, when he/she comes back home in the evening.

It was decided that elevator, when it is not used, will stay on the $ x $ -th floor, but $ x $ hasn't been chosen yet. When a person needs to get from floor $ a $ to floor $ b $ , elevator follows the simple algorithm:

- Moves from the $ x $ -th floor (initially it stays on the $ x $ -th floor) to the $ a $ -th and takes the passenger.
- Moves from the $ a $ -th floor to the $ b $ -th floor and lets out the passenger (if $ a $ equals $ b $ , elevator just opens and closes the doors, but still comes to the floor from the $ x $ -th floor).
- Moves from the $ b $ -th floor back to the $ x $ -th.

 The elevator never transposes more than one person and always goes back to the floor $ x $ before transposing a next passenger. The elevator spends one unit of electricity to move between neighboring floors. So moving from the $ a $ -th floor to the $ b $ -th floor requires $ |a - b| $ units of electricity.Your task is to help Nut to find the minimum number of electricity units, that it would be enough for one day, by choosing an optimal the $ x $ -th floor. Don't forget than elevator initially stays on the $ x $ -th floor.

## 说明/提示

In the first example, the answer can be achieved by choosing the second floor as the $ x $ -th floor. Each person from the second floor (there are two of them) would spend $ 4 $ units of electricity per day ( $ 2 $ to get down and $ 2 $ to get up), and one person from the third would spend $ 8 $ units of electricity per day ( $ 4 $ to get down and $ 4 $ to get up). $ 4 \cdot 2 + 8 \cdot 1 = 16 $ .

In the second example, the answer can be achieved by choosing the first floor as the $ x $ -th floor.

## 样例 #1

### 输入

```
3
0 2 1
```

### 输出

```
16```

## 样例 #2

### 输入

```
2
1 1
```

### 输出

```
4```

# AI分析结果



# 中文题目翻译

## 题目描述

Fair Nut 住在有 $n$ 层的房子里，第 $i$ 层住着 $a_i$ 个人。每个人每天使用电梯两次：早上从所在楼层到一楼，晚上从一楼回家。电梯在空闲时停在第 $x$ 层（$x$ 待定）。电梯的移动规则如下：

1. 从 $x$ 层移动到乘客所在楼层 $a$。
2. 从 $a$ 层移动到目标楼层 $b$（此处 $b=1$ 或 $a$）。
3. 返回 $x$ 层。

电梯每次运送一人后必须返回 $x$ 层。求选择最优的 $x$ 层，使得总耗电量最小（耗电量按楼层差的绝对值计算）。

## 说明/提示

- 样例 1 中，选择 $x=2$ 层时总耗电为 16。
- 样例 2 中，选择 $x=1$ 层时总耗电为 4。

## 输入输出样例

### 样例 1
**输入**
```
3
0 2 1
```
**输出**
```
16
```

### 样例 2
**输入**
```
2
1 1
```
**输出**
```
4
```

---

**算法分类**：数学（贪心）

---

## 题解分析与结论

### 题解对比与评分
1. **RealityCreator（五星）**
   - **关键思路**：推导出电梯应放在第 1 层，总耗电为 $4 \cdot \sum (i-1)a_i$。
   - **亮点**：数学推导简洁，时间复杂度 $O(n)$。
   - **代码**：
     ```cpp
     for (int i=1; i<=n; i++) ans += a[i]*(i-1)*4;
     ```

2. **翼德天尊（五星）**
   - **关键思路**：通过分类讨论证明 $x=1$ 时总耗电最小，推导严谨。
   - **亮点**：数学证明清晰，代码简洁。
   - **代码**：
     ```cpp
     ans += 4 * i * a; // i 为楼层号（从 0 开始）
     ```

3. **xyf007（四星）**
   - **关键思路**：暴力枚举所有可能的 $x$，计算总耗电取最小值。
   - **亮点**：通用性强，正确性不依赖特定条件。
   - **代码**：
     ```cpp
     sum += 2*a[j]*(abs(j-i)+j+i-2);
     ```

---

### 最优思路总结
电梯应放在第 1 层。对于每个楼层 $i$ 上的 $a_i$ 人，总耗电为 $4 \cdot (i-1) \cdot a_i$。该结论的推导基于以下观察：
- 当电梯在 $x$ 层时，单次移动耗电为 $2 \cdot (|x-i| + i + x - 2)$。
- 若 $x=1$，则公式简化为 $4 \cdot (i-1)$，此时总耗电最小。

---

### 拓展与同类题目
- **类似套路**：贪心选择固定点（如中位数、边界点）以优化总和。
- **推荐题目**：
  1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)（贪心排序）
  2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（双指针贪心）
  3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995)（贪心选择最大/最小值交替）

---

### 个人心得摘录
- **RealityCreator**：通过分析电梯路径得出 $x=1$ 最优，避免暴力枚举。
- **xyf007**：暴力枚举所有可能 $x$，强调全面覆盖可能情况的重要性。

---
处理用时：215.00秒