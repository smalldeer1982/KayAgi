# 题目信息

# Mahmoud and Ehab and another array construction task

## 题目描述

Mahmoud has an array $ a $ consisting of $ n $ integers. He asked Ehab to find another array $ b $ of the same length such that:

- $ b $ is lexicographically greater than or equal to $ a $ .
- $ b_{i}>=2 $ .
- $ b $ is pairwise coprime: for every $ 1<=i<j<=n $ , $ b_{i} $ and $ b_{j} $ are coprime, i. e. $ GCD(b_{i},b_{j})=1 $ , where $ GCD(w,z) $ is the greatest common divisor of $ w $ and $ z $ .

Ehab wants to choose a special array so he wants the lexicographically minimal array between all the variants. Can you find it?

An array $ x $ is lexicographically greater than an array $ y $ if there exists an index $ i $ such than $ x_{i}>y_{i} $ and $ x_{j}=y_{j} $ for all $ 1<=j<i $ . An array $ x $ is equal to an array $ y $ if $ x_{i}=y_{i} $ for all $ 1<=i<=n $ .

## 说明/提示

Note that in the second sample, the array is already pairwise coprime so we printed it.

## 样例 #1

### 输入

```
5
2 3 5 4 13
```

### 输出

```
2 3 5 7 11 ```

## 样例 #2

### 输入

```
3
10 3 7
```

### 输出

```
10 3 7 ```

# AI分析结果



---

**唯一算法分类**：数学（质数处理与贪心构造）

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
- **贪心构造**：优先保留原数组 `a` 的前缀，直到第一个无法满足互质条件的位置。
- **质数预处理**：用线性筛法生成足够多的质数，便于后续快速选择。
- **质因数标记**：维护已使用的质因数集合，确保后续元素互质。
- **分阶段处理**：  
  - **阶段1**：尽可能与原数组相同，检查质因数是否冲突。  
  - **阶段2**：一旦发生冲突，找到最小的合法数，后续填充未使用的最小质数。

#### **解决难点**
1. **质因数快速分解**：通过预处理每个数的最小质因数，加速分解过程。
2. **冲突检测**：检查当前数的所有质因数是否已被标记。
3. **最小合法数选择**：在阶段2中，找到第一个大于等于 `a[i]` 且质因数未冲突的数。
4. **高效维护可用质数**：使用标记数组或集合快速筛选可用质数。

---

### **题解评分 (≥4星)**

1. **wangbinfeng（★★★★☆）**  
   - **亮点**：清晰的阶段划分，预处理质数加速选择，代码逻辑简洁。  
   - **不足**：未处理质数范围不足的潜在问题。  
   - **代码片段**：  
     ```cpp
     // 线性筛预处理质数
     for (int i = 2; i <= N; i++) {
         if (!vis[i]) pri[++size] = i;
         for (int j = 1; j <= size; j++) {
             int k = pri[j] * i;
             if (k > N) break;
             vis[k] = true;
             last[k] = pri[j]; // 记录最小质因数
             if (i % pri[j] == 0) break;
         }
     }
     ```

2. **mulberror（★★★★☆）**  
   - **亮点**：利用 `set` 动态维护可用数，删除质因数倍数模拟埃筛。  
   - **不足**：`set` 操作可能带来较高常数复杂度。  
   - **代码片段**：  
     ```cpp
     set<int> s;
     for (int i = 2; i < N; i++) s.insert(i);
     void del(int x) {
         for (int i = 2; i * i <= x; i++) {
             if (x % i == 0) {
                 for (int j = i; j < N; j += i) s.erase(j);
                 while (x % i == 0) x /= i;
             }
         }
         if (x > 1) for (int j = x; j < N; j += x) s.erase(j);
     }
     ```

3. **zhaotiensn（★★★★★）**  
   - **亮点**：分情况处理，暴力枚举合法数，标记质因数高效。  
   - **代码片段**：  
     ```cpp
     bool check(int x) {
         int tx = x;
         vector<int> factors;
         while (tx > 1) {
             int p = last[tx]; // 最小质因数
             if (use[p]) return false;
             factors.push_back(p);
             while (tx % p == 0) tx /= p;
         }
         if (tx > 1 && use[tx]) return false;
         return true;
     }
     ```

---

### **最优思路或技巧提炼**

1. **质数预处理与标记**  
   - 线性筛法预处理质数，并记录每个数的最小质因数，加速质因数分解。
   - 维护标记数组 `use`，记录已使用的质因数，确保后续元素互质。

2. **分阶段贪心构造**  
   - **阶段1**：遍历原数组，检查每个数的质因数是否冲突。若无冲突，保留原数并标记质因数。
   - **阶段2**：找到第一个冲突位置后，暴力枚举后续最小的合法数，后续直接选择未使用的质数。

3. **暴力枚举优化**  
   - 在阶段2中，从 `a[i]+1` 开始枚举，直到找到第一个合法数。利用预处理的最小质因数快速分解。

---

### **同类型题或类似算法套路**

- **构造型贪心**：如 [CF1144F. Graph Without Long Directed Paths](https://codeforces.com/problemset/problem/1144/F)，需分阶段决策。
- **质因数标记与冲突检测**：如 [LeetCode 952. Largest Component Size by Common Factor](https://leetcode.com/problems/largest-component-size-by-common-factor/)，利用质因数建图。

---

### **推荐题目**

1. **CF1144F**：构造无向图的有向边，满足路径长度限制。
2. **LeetCode 952**：基于质因数分组的并查集应用。
3. **洛谷 P1072**：[Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)，数论与因数分解。

---

### **个人心得摘录**

- **质数范围需足够大**：如预处理质数到 `2e6` 避免越界（zhaotiensn 的代码因筛到 `2e6` 通过）。
- **分解质因数优化**：预处理最小质因数可将分解复杂度降至 `O(log x)`（wangbinfeng 的 `last` 数组）。

---

### **可视化与算法演示**

#### **动画方案设计**
1. **分阶段高亮**：  
   - **阶段1**：绿色高亮保留的原数组元素，红色标记冲突位置。  
   - **阶段2**：蓝色显示暴力枚举过程，黄色填充后续质数。

2. **质因数标记动态显示**：  
   - 每次选择元素后，显示其质因数被标记为红色，后续元素检测时高亮冲突质因数。

3. **像素风格界面**：  
   - 使用 8-bit 像素字体，质因数以不同颜色方块表示，操作步骤配以电子音效。

#### **交互设计**
- **步进控制**：允许单步执行，观察质因数分解和标记过程。
- **音效提示**：冲突时播放低音，选择质数时播放高音。

---

**代码示例（核心冲突检测）**  
```cpp
// 质因数分解与冲突检测
bool check(int x) {
    int tmp = x;
    while (tmp > 1) {
        int p = min_prime[tmp]; // 预处理的最小质因数
        if (used[p]) return false;
        while (tmp % p == 0) tmp /= p;
    }
    return true;
}
```

**完整代码参考（zhaotiensn）**  
```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1e5 + 5, MAXP = 2e6;
int a[MAXN], b[MAXN], min_prime[MAXP], primes[MAXP], cnt;
bool used[MAXP], vis[MAXP];

void sieve() {
    for (int i = 2; i < MAXP; i++) {
        if (!vis[i]) primes[++cnt] = i, min_prime[i] = i;
        for (int j = 1; j <= cnt && i * primes[j] < MAXP; j++) {
            vis[i * primes[j]] = true;
            min_prime[i * primes[j]] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

bool check(int x) {
    int tmp = x;
    while (tmp > 1) {
        int p = min_prime[tmp];
        if (used[p]) return false;
        tmp /= p;
    }
    return true;
}

void mark(int x) {
    while (x > 1) {
        int p = min_prime[x];
        used[p] = true;
        x /= p;
    }
}

int main() {
    sieve();
    int n, ptr = 1;
    bool flag = false;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (flag) {
            while (used[primes[ptr]]) ptr++;
            b[i] = primes[ptr];
            used[primes[ptr++]] = true;
        } else {
            int x = a[i];
            while (!check(x)) x++;
            if (x > a[i]) flag = true;
            b[i] = x;
            mark(x);
        }
    }
    for (int i = 1; i <= n; i++) cout << b[i] << " ";
    return 0;
}
```

---
处理用时：107.48秒