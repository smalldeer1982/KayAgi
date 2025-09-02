# 题目信息

# Strange Addition

## 题目描述

Unfortunately, Vasya can only sum pairs of integers ( $ a $ , $ b $ ), such that for any decimal place at least one number has digit $ 0 $ in this place. For example, Vasya can sum numbers $ 505 $ and $ 50 $ , but he cannot sum $ 1 $ and $ 4 $ .

Vasya has a set of $ k $ distinct non-negative integers $ d_{1},d_{2},...,d_{k} $ .

Vasya wants to choose some integers from this set so that he could sum any two chosen numbers. What maximal number of integers can he choose in the required manner?

## 样例 #1

### 输入

```
4
100 10 1 0
```

### 输出

```
4
0 1 10 100 ```

## 样例 #2

### 输入

```
3
2 70 3
```

### 输出

```
2
2 70 ```

# AI分析结果



# Strange Addition

## 题目描述

Vasya 只能对满足以下条件的整数对 $(a, b)$ 进行求和运算：对于任意十进制数位，至少有一个数在该位上的数字为 $0$。例如，Vasya 可以计算 $505$ 和 $50$ 的和，但不能计算 $1$ 和 $4$ 的和。

给定 $k$ 个互不相同的非负整数 $d_1, d_2, \dots, d_k$，要求选出尽可能多的数，使得这些数中任意两个数都满足上述求和条件。求最大可选数目及对应的集合。

---

**算法分类**：构造

---

### 题解对比与分析

#### 核心思路总结
1. **分类讨论**：将数字按数位特征分类（如 0、100、个位为 0 的两位数等），通过类间兼容性构造最大集合。
2. **互斥规则**：除 0 和 100 外，其他类（如个位非零的两位数、一位数）至多选一个。
3. **贪心选择**：优先包含 0 和 100，再在兼容的类中选择代表元素。

#### 最优题解推荐

1. **题解作者：Larryyu（4 星）**  
   **关键亮点**：  
   - 将数分为五类（0、100、个位为 0 的两位数、一位数、其他），通过规则组合最大化选数。  
   - 代码简洁，直接统计各类首个出现的数。  
   **核心代码**：
   ```cpp
   if (a[i] == 100) cnt1 = i;         // 第一类：100
   else if (a[i]是10的倍数) cnt2 = i;    // 第二类：个位为0的两位数
   else if (a[i] < 10) cnt3 = i;      // 第三类：一位数
   else if (a[i] == 0) cnt4++;        // 第四类：0
   else cnt5 = i;                     // 第五类：其他数
   ans = cnt1存在 ? 1 : 0;
   ans += max(第二/三类组合, 第五类存在);
   ```

2. **题解作者：ztxtjz（4 星）**  
   **关键亮点**：  
   - 更细化的分类规则（如个位/十位是否为 0），通过标记避免冲突。  
   - 处理特殊数（如 100）和普通数的逻辑清晰。  
   **核心代码**：
   ```cpp
   if (x == 0 || x == 100) 直接加入集合;
   else if (x是1~9且未被选过) 加入并标记;
   else if (x是两位数且个位为0且未被选过) 加入并标记;
   else if (x是两位数且个位非0) 暂存为候选;
   最后检查候选数是否能加入集合。
   ```

3. **题解作者：王熙文（3 星）**  
   **思路亮点**：  
   - 枚举每一位的可能代表数，强制保证每位最多一个非零数。  
   **不足**：复杂度较高（$O(n^4)$），仅适用于小数据。  
   **个人心得**：  
   > “思路复杂但覆盖全面，通过添加虚拟数简化判断。”

---

### 关键技巧总结
1. **数位补零分析**：将数字统一补至三位（如 7 → 007），便于逐位检查。
2. **类间兼容性**：利用 0 和 100 的特殊性（所有位含 0）作为兼容基础。
3. **极值构造**：通过互斥规则（如每类至多选一个）保证局部最优，组合成全局最优。

---

### 拓展练习
1. [CF1157B](https://codeforces.com/problemset/problem/1157/B) - 构造最优替换序列  
2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094) - 贪心分组  
3. [P1209 修理牛棚](https://www.luogu.com.cn/problem/P1209) - 贪心选择间隔

---
处理用时：149.97秒