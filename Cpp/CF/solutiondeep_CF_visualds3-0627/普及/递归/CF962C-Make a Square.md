# 题目信息

# Make a Square

## 题目描述

You are given a positive integer $ n $ , written without leading zeroes (for example, the number 04 is incorrect).

In one operation you can delete any digit of the given integer so that the result remains a positive integer without leading zeros.

Determine the minimum number of operations that you need to consistently apply to the given integer $ n $ to make from it the square of some positive integer or report that it is impossible.

An integer $ x $ is the square of some positive integer if and only if $ x=y^2 $ for some positive integer $ y $ .

## 说明/提示

In the first example we should delete from $ 8314 $ the digits $ 3 $ and $ 4 $ . After that $ 8314 $ become equals to $ 81 $ , which is the square of the integer $ 9 $ .

In the second example the given $ 625 $ is the square of the integer $ 25 $ , so you should not delete anything.

In the third example it is impossible to make the square from $ 333 $ , so the answer is -1.

## 样例 #1

### 输入

```
8314
```

### 输出

```
2
```

## 样例 #2

### 输入

```
625
```

### 输出

```
0
```

## 样例 #3

### 输入

```
333
```

### 输出

```
-1
```

# AI分析结果



## 算法分类
回溯/DFS

## 题解思路与难点
### 核心思路
题目要求通过删除若干位使原数成为平方数，且删除次数最少。核心思路是生成所有可能的子序列，并检查是否为平方数。关键在于正确处理前导零和高效剪枝。

### 算法要点
1. **子序列生成**：通过DFS遍历每一位，选择保留或删除该位，生成所有可能的子序列。
2. **前导零处理**：若生成的子序列以0开头，则直接跳过。
3. **平方数判定**：对生成的子序列转换为整数，判断其平方根是否为整数。
4. **剪枝优化**：从长到短搜索，找到第一个可行解即为最优解。

### 解决难点
- **顺序保留**：子序列需保持原数字的位顺序。
- **高效检查**：对每个子序列快速验证是否为平方数。
- **前导零处理**：避免生成无效数字。

## 题解评分（≥4星）
1. **QianianXY（5星）**  
   - 使用DFS生成子序列，处理前导零清晰。
   - 从长到短剪枝，效率高。
   - 代码简洁，可读性强。
2. **Andy_Li（4星）**  
   - DFS回溯生成子序列，检查平方数。
   - 处理前导零，但代码结构稍复杂。
3. **RNTBW（4星）**  
   - DFS生成子序列，正确处理前导零。
   - 代码简洁，但变量命名可优化。

## 最优思路与技巧
1. **DFS生成子序列**：按原顺序保留或删除每位，确保子序列顺序正确。
2. **剪枝优化**：优先保留更多位数，找到即返回。
3. **前导零处理**：生成时若当前字符串以0开头，跳过后续分支。
4. **平方数快速验证**：使用整数转换后判断平方根是否为整数。

## 同类型题与套路
- **子序列验证**：如寻找最长递增子序列、特定数值条件等。
- **暴力搜索剪枝**：适用于位数较少的场景，如数位DP类问题。

## 推荐题目
1. [CF914B - Consecutive Subsequence](https://codeforces.com/problemset/problem/914/B)
2. [LeetCode 279 - Perfect Squares](https://leetcode.com/problems/perfect-squares/)
3. [洛谷P1102 - A-B数对](https://www.luogu.com.cn/problem/P1102)

## 个人心得摘录
- **调试教训**：处理前导零需在生成子序列时立即判断，而非最后转换。
- **顿悟点**：从长到短搜索可避免记录所有可能，直接找到最优解。

## 可视化设计
### 动画方案
- **Canvas绘制**：原数字以像素块排列，绿色表示保留，红色删除。
- **步进执行**：展示DFS每一步选择保留或删除，当前生成的子序列实时显示。
- **颜色标记**：
  - 当前操作位高亮黄色。
  - 有效子序列显示为绿色，无效为红色。
- **控制面板**：暂停/继续、步进、调节速度。

### 复古像素风格
- **8位调色板**：使用经典FC配色（绿、红、黄）。
- **音效**：
  - 保留位：短促“哔”声。
  - 找到解：胜利音效。
  - 无解：低沉提示音。

---

## 核心代码实现（QianianXY）
```cpp
#include <bits/stdc++.h>
using namespace std;

char c[10], str[10];
int len, ans = 1e9;

void dfs(int k, int tot) {
    if (k > len) {
        if (tot && str[0] != '0') {
            long long num = stoll(str);
            long long sq = sqrt(num);
            if (sq * sq == num) 
                ans = min(ans, len - tot);
        }
        return;
    }
    // 不保留当前位
    dfs(k + 1, tot);
    // 保留当前位（避免前导零）
    if (tot == 0 && c[k] == '0') return;
    str[tot] = c[k];
    dfs(k + 1, tot + 1);
}

int main() {
    scanf("%s", c + 1);
    len = strlen(c + 1);
    dfs(1, 0);
    printf("%d", ans == 1e9 ? -1 : ans);
    return 0;
}
```

---
处理用时：503.61秒