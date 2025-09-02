# 题目信息

# Even Positions

## 题目描述

Monocarp had a regular bracket sequence $ s $ of length $ n $ ( $ n $ is even). He even came up with his own way to calculate its cost.

He knows that in a regular bracket sequence (RBS), each opening bracket is paired up with the corresponding closing bracket. So he decided to calculate the cost of RBS as the sum of distances between pairs of corresponding bracket pairs.

For example, let's look at RBS (())(). It has three pairs of brackets:

- (\_\_)\_\_: the distance between brackets at position $ 1 $ and at $ 4 $ is $ 4 - 1 = 3 $ ;
- \_()\_\_\_: the distance is $ 3 - 2 = 1 $ ;
- \_\_\_\_(): the distance is $ 6 - 5 = 1 $ .

 So the cost of (())() is $ 3 + 1 + 1 = 5 $ .Unfortunately, due to data corruption, Monocarp lost all characters on odd positions $ s_1, s_3, \dots, s_{n-1} $ . Only characters on even positions ( $ s_2, s_4, \dots, s_{n} $ ) remain. For example, (())() turned to \_(\_)\_).

Monocarp wants to restore his RBS by placing brackets on the odd positions. But since the restored RBS may not be unique, he wants to choose one with minimum cost. It's too hard to do for Monocarp alone, so can you help him?

Reminder: A regular bracket sequence is a string consisting of only brackets, such that this sequence, when inserted 1-s and +-s, gives a valid mathematical expression. For example, (), (()) or (()())() are RBS, while ), ()( or ())(() are not.

## 说明/提示

In the first test case, it's optimal to make $ s $ equal to (())(). The cost of $ s $ will be equal to $ 3 + 1 + 1 = 5 $ .

In the second test case, the only option is to make $ s $ equal to () with cost $ 1 $ .

In the third test case, the only possible RBS is ()()()() with cost $ 1 + 1 + 1 + 1 = 4 $ .

In the fourth test case, it's optimal to make $ s $ equal to (())(()) with cost $ 3 + 1 + 3 + 1 = 8 $ .

## 样例 #1

### 输入

```
4
6
_(_)_)
2
_)
8
_)_)_)_)
8
_(_)_(_)```

### 输出

```
5
1
4
8```

# AI分析结果



**唯一算法分类**  
贪心算法

---

### **题解思路、算法要点与解决难点**

**核心思路**  
题目要求通过填充奇数位置的括号，使得合法括号序列的总距离和最小。所有正确解法均采用**贪心策略**，核心思想是：在填充空缺时优先闭合最近的左括号，从而最小化每对括号的距离。关键在于维护栈结构，实时跟踪未闭合的左括号位置，贪心选择右括号填充以尽早闭合。

**解决难点**  
1. **贪心策略的正确性**：优先闭合最近的左括号，确保每个括号对的局部最优（距离最小），进而达到全局最优。  
2. **栈的维护**：处理输入中的固定字符（偶数位置）时，需正确压入或弹出栈顶元素；处理空缺时，根据栈的状态选择填充左/右括号。  
3. **总距离计算**：在填充过程中实时累加每对括号的距离，或在最终构造的序列中统计左右括号的位置差之和。

**各题解对比**  
- **Alexander**：直接使用栈模拟填充过程，实时计算总距离，代码简洁高效。  
- **CashCollectFactory**：先填充空缺生成完整序列，再统计总距离，逻辑清晰但需额外遍历。  
- **cfkk**：通过数学公式直接计算总距离（`n/2 + 2*cnt`），但需验证公式的正确性。  
- **Heldivis**：与Alexander类似，但代码更简洁，直接维护栈和距离总和。  

---

### **题解评分 (≥4星)**  
1. **Alexander（⭐⭐⭐⭐⭐）**  
   - 思路清晰，代码简洁，实时计算距离，无需二次遍历。  
   - 栈维护直观，处理固定字符和空缺逻辑明确。  
2. **CashCollectFactory（⭐⭐⭐⭐）**  
   - 分步填充和统计，代码可读性高。  
   - 需额外遍历字符串计算总距离，略低效。  
3. **Heldivis（⭐⭐⭐⭐）**  
   - 代码简洁，直接维护栈和总距离。  
   - 逻辑与Alexander一致，但变量命名更规范。  

---

### **最优思路或技巧提炼**  
1. **贪心闭合策略**：空缺位置优先填充右括号，闭合最近的左括号（栈顶）。  
2. **栈的动态维护**：遇到固定左括号入栈，右括号出栈并累加距离；空缺时根据栈状态填充。  
3. **实时计算距离**：在出栈时直接计算当前右括号位置与栈顶左括号的距离，避免后续遍历。

---

### **代码实现（核心逻辑）**  
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        string s; cin >> s;
        stack<int> st;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (c == '_') { // 奇数位置需填充
                if (!st.empty()) {
                    ans += (i + 1) - st.top(); // 距离计算（i从0开始）
                    st.pop();
                } else {
                    st.push(i + 1); // 填充左括号
                }
            } else if (c == '(') {
                st.push(i + 1); // 偶数位置左括号入栈
            } else {
                ans += (i + 1) - st.top();
                st.pop();
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

### **可视化与算法演示**  
**动画设计**  
1. **数据结构展示**：栈的实时状态（左括号位置）、当前字符位置及类型、总距离值。  
2. **操作高亮**：  
   - **红色方块**：当前处理字符，若为`_`则闪烁提示填充决策。  
   - **绿色连线**：闭合括号对的连线，显示距离数值。  
3. **交互控制**：步进执行、暂停、重置，速度调节支持观察栈的动态变化。  

**复古像素风格**  
- **8位像素UI**：栈用像素方块表示，位置编号为8位字体。  
- **音效设计**：  
  - 闭合成功：上扬音效（8-bit音效）。  
  - 压栈/弹栈：短促“哔”声。  
- **自动演示**：AI自动填充空缺并匹配括号，展示贪心策略的决策过程。  

---

### **同类型题推荐**  
1. **LeetCode 921. Minimum Add to Make Parentheses Valid**  
2. **Codeforces 5C. Longest Regular Bracket Sequence**  
3. **洛谷 P1944 最长括号匹配**  

**核心技巧**：栈维护括号匹配，贪心策略优化操作。  

--- 

**总结**：通过栈动态维护未闭合左括号，贪心选择右括号填充，确保每对括号距离最小，是解决此类问题的通用模式。

---
处理用时：260.00秒