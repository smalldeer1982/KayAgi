# 题目信息

# [ARC185E] Adjacent GCD

## 题目描述

定义一个整数序列 $B=(B_1,B_2,\dots,B_k)$ 的分数为 $\sum_{i=1}^{k-1}\gcd(B_i,B_{i+1})$。

给出一个整数序列 $A=(A_1,A_2,\dots,A_N)$，求出以下问题在 $m=1,2,\dots,N$ 时的答案：

- 序列 $A=(A_1,A_2,\dots,A_m)$ 有 $2^m-1$ 个非空子序列。求出这些子序列的分数之和对 $998244353$ 取模后的值。如果两个子序列在原序列中的位置不同，即使它们的元素全部相同，我们也认为它们是不同的。

## 说明/提示

- $1\le N\le 5\times 10^5$
- $1\le A_i\le 10^5$
- 输入的值全部为整数

## 样例 #1

### 输入

```
3

9 6 4```

### 输出

```
0

3

11```

## 样例 #2

### 输入

```
5

3 8 12 6 9```

### 输出

```
0

1

13

57

155```

## 样例 #3

### 输入

```
10

47718 21994 74148 76721 98917 73766 29598 59035 69293 29127```

### 输出

```
0

2

14

35

97

372

866

1859

4273

43287```

# AI分析结果



**唯一算法分类**：数论

---

### **题解思路与核心难点**

1. **递推框架**  
   每个前缀的答案可通过递推得到：`ans_i = 2 * ans_{i-1} + 新增贡献`。  
   - **新增贡献**：所有包含新增元素 `a_i` 的子序列中，相邻元素的 `gcd(a_j, a_i)` 之和。  
   - **核心难点**：快速计算 `∑_{j=1}^{i-1} gcd(a_j, a_i) * 2^{j-1}`。

2. **数学优化（欧拉反演）**  
   将 `gcd(a_j, a_i)` 转化为数论函数的和：  
   ```math
   \gcd(a_j, a_i) = \sum_{d \mid \gcd(a_j, a_i)} \varphi(d)
   ```  
   从而将问题转化为对每个因数 `d` 的统计：  
   ```math
   \sum_{d \mid a_i} \varphi(d) \cdot \text{sum\_power}[d]
   ```  
   其中 `sum_power[d]` 表示前面满足 `d \mid a_j` 的 `2^{j-1}` 之和。

3. **动态维护因数贡献**  
   - **预处理**：每个数的因数列表及欧拉函数。  
   - **维护数组 `sum_power`**：每次处理 `a_i` 时，遍历其因数 `d`，将当前 `2^{i-1}` 累加到 `sum_power[d]`。

---

### **最优思路提炼**

- **关键公式**：利用欧拉函数分解 `gcd` 的贡献，将复杂度降至线性。  
- **优化点**：动态维护每个因数的贡献，避免重复计算。  
- **实现步骤**：  
  1. 预处理每个数的因数和欧拉函数。  
  2. 遍历数组，递推计算答案并更新 `sum_power`。

---

### **题解评分（≥4星）**

1. **xwh_Marvelous（5星）**  
   - 思路清晰，直接应用欧拉反演和因数统计。  
   - 代码简洁，维护 `g[d]` 数组高效计算贡献。

2. **cancan123456（4星）**  
   - 使用线性筛预处理因数，代码结构清晰。  
   - 动态维护 `sum_power`，时间复杂度优秀。

3. **jr_zch（4星）**  
   - 预处理欧拉函数，逻辑简洁。  
   - 直接枚举因数，代码易于理解。

---

### **核心代码实现**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353, MAX = 1e5 + 5;
vector<int> divisors[MAX];
int phi[MAX], sum_power[MAX], pow2[MAX];

void preprocess() {
    // 预处理因数和欧拉函数
    for (int i = 1; i < MAX; i++) 
        for (int j = i; j < MAX; j += i) 
            divisors[j].push_back(i);
    
    phi[1] = 1;
    vector<bool> is_prime(MAX, true);
    for (int i = 2; i < MAX; i++) {
        if (is_prime[i]) {
            phi[i] = i - 1;
            for (int j = 2 * i; j < MAX; j += i) {
                is_prime[j] = false;
                if (j / i % i == 0) phi[j] = phi[j / i] * i;
                else phi[j] = phi[j / i] * (i - 1);
            }
        }
    }
    // 预处理2的幂次
    pow2[0] = 1;
    for (int i = 1; i < MAX; i++) 
        pow2[i] = pow2[i - 1] * 2 % MOD;
}

int main() {
    preprocess();
    int n, a;
    scanf("%d", &n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        int add = 0;
        for (int d : divisors[a]) 
            add = (add + 1LL * phi[d] * sum_power[d]) % MOD;
        ans = (2LL * ans + add) % MOD;
        printf("%d\n", ans);
        // 更新sum_power
        int current_pow = pow2[i - 1];
        for (int d : divisors[a]) 
            sum_power[d] = (sum_power[d] + current_pow) % MOD;
    }
    return 0;
}
```

---

### **可视化算法演示**

1. **动画流程**  
   - **步骤1**：高亮当前处理的元素 `a_i`，显示其因数列表。  
   - **步骤2**：遍历每个因数 `d`，计算 `phi[d] * sum_power[d]`，累加到新增贡献。  
   - **步骤3**：更新 `sum_power[d]`，显示数值变化。  
   - **步骤4**：递推计算 `ans_i`，显示最终结果。

2. **复古像素风格**  
   - **颜色方案**：因数用绿色高亮，贡献计算用红色闪烁。  
   - **音效**：完成一步计算时播放 8-bit 音效，更新数组时触发“点击”声。

---

### **相似题目推荐**

1. [P1891 疯狂 LCM](https://www.luogu.com.cn/problem/P1891)  
   - 应用欧拉函数与因数统计。

2. [P2303 Longge的问题](https://www.luogu.com.cn/problem/P2303)  
   - 使用数论技巧分解 `gcd` 贡献。

3. [P1390 公约数的和](https://www.luogu.com.cn/problem/P1390)  
   - 枚举因数并动态维护统计值。

---
处理用时：77.13秒