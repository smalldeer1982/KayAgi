# 题目信息

# Balanced Subsequences

## 题目描述

A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters '+' and '1'. For example, sequences '(())()', '()', and '(()(()))' are balanced, while ')(', '(()', and '(()))(' are not.

A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements.

You are given three integers $ n $ , $ m $ and $ k $ . Find the number of sequences consisting of $ n $ '(' and $ m $ ')', such that the longest balanced subsequence is of length $ 2 \cdot k $ . Since the answer can be large calculate it modulo $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 说明/提示

For the first test case "()()", "(())" are the $ 2 $ sequences

For the second test case no sequence is possible.

For the third test case ")((()", ")(()(", ")()((", "())((" are the $ 4 $ sequences.

## 样例 #1

### 输入

```
3
2 2 2
3 2 3
3 2 1```

### 输出

```
2
0
4```

# AI分析结果



---

### **数学分类**
**组合数学**

---

### **题解思路与核心难点**
**核心思路**：将括号序列转化为折线路径，利用反射原理计算满足最低点条件的路径数目。  
**关键公式**：答案为组合数之差，即 $\dbinom{n+m}{k} - \dbinom{n+m}{k-1}$。  
**解决难点**：  
1. 最长平衡子序列长度对应折线的最低点纵坐标为 $k - m$。  
2. 通过反射原理将路径计数转化为组合数问题，用容斥思想（总路径数减去不满足条件的路径数）。  

---

### **题解评分（≥4星）**
1. **UnyieldingTrilobite（5星）**  
   - 思路清晰，直接应用反射原理推导公式。  
   - 代码简洁，仅需预处理组合数即可高效计算。  
2. **OrezTsim（4星）**  
   - 模型转化直观，详细解释赌徒模型与路径对称性。  
   - 代码完整，组合数预处理逻辑清晰。  
3. **zifanwang（4星）**  
   - 推导简洁，代码高效，结合贪心算法验证模型正确性。  

---

### **最优思路与技巧提炼**
**关键技巧**：  
1. **反射原理**：将路径最低点限制转化为对称路径计数问题。  
2. **组合数容斥**：通过 $\dbinom{n+m}{k} - \dbinom{n+m}{k-1}$ 精确计算符合条件的路径数目。  
**公式推导**：  
- 若折线最低点纵坐标为 $k - m$，则总路径数为 $\dbinom{n+m}{k}$。  
- 需排除最低点更小的路径（即 $\dbinom{n+m}{k-1}$）。  

---

### **同类型题与算法套路**
**通用套路**：  
1. **路径计数问题**：用组合数或动态规划解决网格路径限制问题。  
2. **卡特兰数变形**：涉及括号匹配、栈操作等问题时，常需调整反射原理参数。  
**类似题目**：  
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)（卡特兰数基础）  
2. [P1641 生成字符串](https://www.luogu.com.cn/problem/P1641)（组合数路径限制）  
3. [P2532 树屋阶梯](https://www.luogu.com.cn/problem/P2532)（卡特兰数分治）  

---

### **可视化与算法演示**
**动画设计**：  
1. **折线路径绘制**：  
   - 初始点 $(0,0)$，左括号向右上移动，右括号向右下移动。  
   - 动态绘制路径，标记最低点 $y = k - m$。  
2. **反射变换演示**：  
   - 将路径最后一次触碰 $y = k - m$ 后的部分对称翻转，展示路径终点变换。  
3. **像素风格交互**：  
   - **颜色标记**：当前操作字符（左/右括号）高亮，路径最低点用红色标记。  
   - **音效触发**：完成关键步骤（如触碰最低点）时播放音效。  

**代码片段（JS Canvas）**：  
```javascript
// 绘制折线路径（示例）
function drawPath(ctx, path) {
    ctx.beginPath();
    ctx.moveTo(0, 0);
    let x = 0, y = 0;
    for (const c of path) {
        x += 10;
        y += (c === '(') ? 10 : -10;
        ctx.lineTo(x, y);
        ctx.strokeStyle = (y === k - m) ? '#FF0000' : '#000000';
        ctx.stroke();
    }
}
```

---

### **个人心得摘录**
- **UnyieldingTrilobite**：“场上直接想到反射原理，模型转化是解题关键。”  
- **EthanOI**：“将括号序列想象为赌徒输赢，顿悟路径对称性的重要性。”  

---

### **核心代码实现**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7, N = 4005;
int C[N][N];

void init() {
    C[0][0] = 1;
    for (int i = 1; i < N; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
    }
}

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        int n, m, k; cin >> n >> m >> k;
        if (k > min(n, m)) cout << "0\n";
        else cout << (C[n+m][k] - C[n+m][k-1] + MOD) % MOD << '\n';
    }
    return 0;
}
```

---
处理用时：61.24秒