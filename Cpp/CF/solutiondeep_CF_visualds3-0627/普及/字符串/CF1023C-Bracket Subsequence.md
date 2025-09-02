# 题目信息

# Bracket Subsequence

## 题目描述

A bracket sequence is a string containing only characters "(" and ")". A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)"), and ")(", "(" and ")" are not.

Subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

You are given a regular bracket sequence $ s $ and an integer number $ k $ . Your task is to find a regular bracket sequence of length exactly $ k $ such that it is also a subsequence of $ s $ .

It is guaranteed that such sequence always exists.

## 样例 #1

### 输入

```
6 4
()(())
```

### 输出

```
()()
```

## 样例 #2

### 输入

```
8 8
(()(()))
```

### 输出

```
(()(()))
```

# AI分析结果



### 【唯一算法分类】  
**贪心算法**

---

### 【题解思路、算法要点与解决难点】  
**核心思路**：  
1. **目标结构**：所求子序列必须有 `k/2` 个左括号和右括号，且在任何前缀中右括号数量不超过左括号。  
2. **贪心策略**：遍历原字符串，优先收集足够的左括号（直到达到 `k/2`），随后收集右括号（需满足当前右括号数 < 左括号数）。  

**解决难点**：  
- **合法性保证**：右括号必须严格在左括号之后匹配，避免出现 `)(` 等非法情况。  
- **高效性要求**：数据规模为 `2e5`，需线性时间复杂度。  

**关键变量**：  
- `l`：已选取的左括号数量（目标为 `k/2`）。  
- `r`：已选取的右括号数量（目标为 `k/2`，且 `r < l`）。  

---

### 【题解评分 (≥4星)】  
1. **__CrossBow_EXE__（5星）**  
   - **亮点**：代码简洁，直接遍历输出，实时判断条件并终止循环。  
   - **代码可读性**：变量命名清晰，逻辑紧凑。  

2. **StudyingFather（4星）**  
   - **亮点**：明确说明合法性的数学保证，代码中分情况处理左右括号。  
   - **优化点**：预先计算 `k/2`，减少重复运算。  

3. **Sai_t（4星）**  
   - **亮点**：代码简洁，通过字符串拼接动态构建结果。  
   - **实践性**：直接使用字符串操作，无需额外数组。  

---

### 【最优思路或技巧提炼】  
1. **贪心选择顺序**：优先收集左括号至 `k/2`，再按序匹配右括号。  
2. **合法性验证**：在选取右括号时，强制要求 `r < l`，确保前缀合法。  
3. **提前终止**：当总长度达到 `k` 时立即退出循环，节省时间。  

---

### 【同类型题或类似算法套路】  
- **括号匹配问题**：如判断合法括号序列、最长合法子串等。  
- **子序列构造问题**：需满足特定结构约束的子序列提取。  

---

### 【推荐相似题目】  
1. **LeetCode 32. 最长有效括号**（贪心/动态规划）  
2. **LeetCode 678. 有效的括号字符串**（双指针贪心）  
3. **洛谷 P1944 最长前缀**（子序列匹配）  

---

### 【个人心得摘录】  
- **FutureThx**：尝试用栈删除多余括号，但需注意栈操作的边界条件。  
- **MorsLin**：未初始化数组导致错误，强调代码细节的重要性。  

---

### 【可视化与算法演示】  
**动画设计**：  
1. **遍历过程可视化**：  
   - 原字符串以网格显示，当前字符高亮为黄色。  
   - 左括号选中时变为绿色，右括号选中时变为蓝色。  
2. **状态面板**：  
   - 显示 `l` 和 `r` 的当前值，目标值为 `k/2`。  
   - 结果字符串动态构建，显示在底部。  
3. **交互功能**：  
   - **步进控制**：允许单步执行或自动播放（速度可调）。  
   - **音效反馈**：选中括号时播放“嘀”声，完成时播放胜利音效。  

**复古像素风格**：  
- **颜色方案**：8位色调色板（绿、蓝、黄、黑）。  
- **Canvas 绘制**：字符以 16x16 像素块呈现，背景为黑色网格。  
- **音效设计**：  
  - 选中括号：8位“哔”声（Web Audio API）。  
  - 完成匹配：经典 FC 过关音效。  

---

### 【核心代码实现】  
```cpp
// 代码来自 __CrossBow_EXE__ 的题解（5星）
#include<iostream>
using namespace std;
char a[200005];
int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == '(' && l < k / 2) {
            l++;
            cout << '(';
        } else if (a[i] == ')' && r < l) {
            r++;
            cout << ')';
        }
        if (l + r == k) break;
    }
    return 0;
}
```

**代码核心逻辑**：  
- 遍历原字符串，优先收集左括号至 `k/2`。  
- 收集右括号时，确保 `r < l` 以保证合法性。  
- 当总长度达到 `k` 时立即终止。  

---

**可视化代码片段（JavaScript）**：  
```javascript
// Canvas 绘制核心逻辑（伪代码）
function drawStep(char, index, isSelected) {
    ctx.fillStyle = isSelected ? '#00FF00' : '#FFFFFF'; // 高亮选中字符
    ctx.fillRect(index * 16, 0, 16, 16); // 在 Canvas 上绘制字符块
    if (char === '(') playSound('beep'); // 触发音效
}
```

---
处理用时：64.94秒