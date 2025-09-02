# 题目信息

# Number With The Given Amount Of Divisors

## 题目描述

Given the number $ n $ , find the smallest positive integer which has exactly $ n $ divisors. It is guaranteed that for the given $ n $ the answer will not exceed $ 10^{18} $ .

## 样例 #1

### 输入

```
4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6
```

### 输出

```
12
```

# AI分析结果



# 算法分类
**搜索与剪枝**

---

## 题解思路与核心难点

### 核心算法逻辑
1. **质数分配策略**：将指数分配给尽可能小的连续质数（如2,3,5,...），且指数序列保持非递增排列，以保证数值最小。
2. **DFS搜索框架**：
   - 当前数值 `now`、当前质数下标 `k`、剩余可用指数 `last`、已累计因子数 `cnt`
   - 遍历指数分配（从大到小），递归搜索下一质数
3. **剪枝优化**：
   - 数值溢出判断（now ≤ 0 或 >1e18）
   - 当前结果已劣于已找到的最优解
   - 质数数量限制（最多前16个质数）

### 解决难点
- **最优性保证**：通过指数非递增的遍历顺序，确保优先将高指数分配给小质数
- **溢出处理**：利用数值越界特征（now ≤ 0）快速剪枝
- **复杂度控制**：限制质数个数与指数范围（16质数×64指数）

---

## 题解评分（≥4星）

### 1. Plozia（★★★★★）
- **亮点**：严谨的数学证明，清晰的搜索剪枝逻辑
- **代码亮点**：预处理质数表，指数遍历顺序优化

### 2. 一扶苏一（★★★★☆）
- **亮点**：详细的定理推导，质数数量优化（15个）
- **不足**：代码可读性稍逊

### 3. 一只书虫仔（★★★★☆）
- **亮点**：简洁的指数剪枝（i <= k），直观的变量命名
- **个人心得**："k 的质因数分解"注释帮助理解递归参数

---

## 最优思路提炼

### 关键技巧
1. **指数非递增遍历**：确保大指数优先分配给小质数
2. **连续质数选择**：强制使用2,3,5,...序列避免漏解
3. **乘法溢出剪枝**：利用溢出后数值变为负数快速终止无效分支

### 代码片段
```cpp
void dfs(LL now, int k, int last, int cnt) {
    if (now <= 0 || cnt > n || now > ans) return;
    if (cnt == n) { ans = min(ans, now); return; }
    for (int i = 1; i <= last; ++i) {
        dfs(now * prime[k], k + 1, i, cnt * (i + 1));
    }
}
```

---

## 同类型题推荐
1. **反质数问题**（如 [Luogu P1463】](https://www.luogu.com.cn/problem/P1463))
2. **因数个数约束的最值问题**
3. **质因数分解相关的构造问题**

---

## 可视化设计

### 动画方案
1. **树状结构展示**：
   - 根节点为1，每层选择质数（2,3,5...）
   - 分支显示当前指数选择（如3²→3³）
   - 高亮当前最优路径（红色边框）

2. **状态面板**：
   ```plaintext
   当前数值: 12
   质数序列: 2^2 * 3^1
   剩余因子数: 6 → 6/6 ✔
   已用质数: [2,3]
   ```

3. **像素风格元素**：
   - 质数球：不同颜色代表不同质数（2=蓝，3=绿）
   - 指数方块：高度表示指数值，下落动画展示分配过程

### 复古效果
- **音效设计**：
  - 正确分支：8-bit 上升音阶
  - 剪枝触发：短促 "哔" 声
  - 找到解：经典马里奥过关音效
- **自动演示模式**：
  - AI模拟最优路径选择
  - 每步延迟可调（100ms-2s）

---

## 核心代码（完整版）
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int PRIMES[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
LL ans = 1e18;
int n;

void dfs(LL val, int prime_idx, int max_exp, int div_count) {
    if (div_count == n) { ans = min(ans, val); return; }
    if (prime_idx >= 16 || div_count > n) return;
    
    for (int e = 1; e <= max_exp; ++e) {
        if (val > LLONG_MAX / PRIMES[prime_idx]) break;
        val *= PRIMES[prime_idx];
        dfs(val, prime_idx + 1, e, div_count * (e + 1));
    }
}

int main() {
    cin >> n;
    dfs(1, 0, 64, 1);
    cout << ans << endl;
    return 0;
}
```

---
处理用时：63.31秒