# 题目信息

# Vasily the Bear and Sequence

## 题目描述

Vasily the bear has got a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Vasily the Bear wants to write out several numbers on a piece of paper so that the beauty of the numbers he wrote out was maximum.

The beauty of the written out numbers $ b_{1},b_{2},...,b_{k} $ is such maximum non-negative integer $ v $ , that number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by number $ 2^{v} $ without a remainder. If such number $ v $ doesn't exist (that is, for any non-negative integer $ v $ , number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by $ 2^{v} $ without a remainder), the beauty of the written out numbers equals -1.

Tell the bear which numbers he should write out so that the beauty of the written out numbers is maximum. If there are multiple ways to write out the numbers, you need to choose the one where the bear writes out as many numbers as possible.

Here expression $ x $ $ and $ $ y $ means applying the bitwise AND operation to numbers $ x $ and $ y $ . In programming languages C++ and Java this operation is represented by "&", in Pascal — by "and".

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
2
4 5
```

## 样例 #2

### 输入

```
3
1 2 4
```

### 输出

```
1
4
```

# AI分析结果



---

### **综合分析与结论**

**题目核心**：给定正整数序列，选出若干数，使其按位与的结果能被最大的 $2^v$ 整除，且选数尽可能多。若结果为0（能被任意 $2^v$ 整除），返回 $v=-1$。

**贪心策略**：  
1. **高位优先枚举**：从最高位（如30位）开始倒序枚举可能的 $v$，优先保证高位条件成立。  
2. **筛选候选数**：对当前 $v$，筛选所有在该二进制位为1的数。  
3. **验证条件**：检查这些数的按位与结果是否在低 $v$ 位全为0（即能被 $2^v$ 整除）。  
4. **选择最多数**：满足条件时，选择尽可能多的数（即所有在 $v$ 位为1的数），确保解的最大性。

**难点解决**：  
- **高效验证**：通过按位与的低 $v$ 位掩码（$2^v-1$）快速判断结果是否满足条件。  
- **位运算优化**：直接操作二进制位，避免复杂数学计算，时间复杂度 $O(30n)$，适用于大 $n$。

---

### **题解清单（≥4星）**

#### **题解1：Graphcity（4星）**
- **亮点**：  
  - 显式计算按位与结果，逻辑清晰。  
  - 代码结构完整，用 `vector` 动态维护候选数。  
- **代码片段**：  
  ```cpp
  for (int v = 30; v >= 0; v--) {
      vector<int> candidates;
      int res = -1;
      for (int num : a) {
          if (num & (1 << v)) {
              candidates.push_back(num);
              res &= num;  // 初始为第一个数的值
          }
      }
      if (res % (1 << v) == 0 && !candidates.empty()) {
          // 输出结果
      }
  }
  ```

#### **题解2：Rye_Catcher（4星）**
- **亮点**：  
  - 利用掩码 $2^v-1$ 快速验证低 $v$ 位是否为0，避免完整按位与计算。  
  - 代码更简洁，条件判断高效。  
- **代码片段**：  
  ```cpp
  for (int v = 30; v >= 0; v--) {
      int mask = (1 << v) - 1;
      int and_result = mask;
      vector<int> candidates;
      for (int num : a) {
          if (num & (1 << v)) {
              and_result &= num;
              candidates.push_back(num);
          }
      }
      if (and_result == 0 && !candidates.empty()) {
          // 输出结果
      }
  }
  ```

---

### **最优思路提炼**

1. **高位优先贪心**：从最高位开始枚举，确保最大 $v$。  
2. **候选数筛选**：仅保留当前位为1的数，保证结果的该位为1。  
3. **掩码验证**：用 $2^v-1$ 快速判断结果的低 $v$ 位是否全0。  
4. **多选原则**：在相同 $v$ 下选择最多的数，确保解的完整性。

---

### **同类型题目与算法套路**

- **位运算贪心**：优先处理高位，独立考虑每一位的最优解（如最大异或值、按位与最大）。  
- **掩码技巧**：通过位掩码快速验证条件。  
- **扩展场景**：区间调度、二进制拆分优化、子集选择问题。

**推荐题目**：  
1. [P2114 起床困难综合症](https://www.luogu.com.cn/problem/P2114)  
2. [P4310 绝世好题](https://www.luogu.com.cn/problem/P4310)  
3. [P2420 自然数拆分](https://www.luogu.com.cn/problem/P2420)

---

### **可视化与算法演示**

**核心贪心过程动画设计**：  
1. **像素化显示**：将每个数的二进制位以像素块表示，高位在左，低位在右。  
2. **高亮当前位**：枚举 $v$ 时，高亮所有数的第 $v$ 位，绿色表示1，红色表示0。  
3. **候选数筛选**：筛选出绿色块（当前位为1）的数，放入候选队列。  
4. **按位与计算**：动态显示候选数的按位与结果，低 $v$ 位用黄色闪烁表示是否全0。  
5. **音效反馈**：验证成功时播放胜利音效，失败时播放错误音效。

**复古游戏化设计**：  
- **8位风格**：数字以像素方块呈现，背景音乐为芯片音乐循环。  
- **自动演示**：AI自动逐步枚举 $v$，用户可暂停/调速观察每一步决策。  
- **积分系统**：正确选择 $v$ 后获得积分，连击加分，增强沉浸感。

---

### **代码实现（核心逻辑）**

**题解2的关键代码**：  
```cpp
int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int& num : a) cin >> num;

    for (int v = 30; v >= 0; v--) {
        int mask = (1 << v);
        vector<int> candidates;
        int low_mask = mask - 1;  // 低v位的掩码
        int res = low_mask;        // 初始为全1，逐步按位与

        for (int num : a) {
            if (num & mask) {
                candidates.push_back(num);
                res &= num;
            }
        }

        // 检查低v位是否全0
        if ((res & low_mask) == 0 && !candidates.empty()) {
            cout << candidates.size() << endl;
            for (int num : candidates) cout << num << " ";
            return 0;
        }
    }

    cout << -1;
    return 0;
}
```

--- 

**总结**：通过高位贪心和掩码验证，高效解决最大按位与问题，代码简洁且时间复杂度最优。

---
处理用时：321.47秒