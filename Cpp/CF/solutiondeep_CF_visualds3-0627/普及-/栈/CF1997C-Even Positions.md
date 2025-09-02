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



### 唯一算法分类
贪心

### 综合分析与结论
**核心思路**：通过栈维护未闭合的左括号位置，遇到空缺时优先闭合最近的左括号以保证最小距离。总成本为所有右括号位置减去对应左括号位置的累加。

**算法流程**：
1. **栈维护**：遍历所有位置，确定字符直接处理，空缺字符优先闭合栈顶左括号。
2. **贪心策略**：空缺位置优先填右括号（若栈非空），否则填左括号。
3. **成本计算**：实时累加每对括号的距离差。

**可视化设计**：
- **动画方案**：用像素网格展示每个位置的状态（左/右括号或空缺），栈以动态方块表示。
- **颜色标记**：当前处理位置高亮为黄色，栈顶元素为红色，闭合对连线为绿色。
- **音效与交互**：闭合时播放清脆音效，压栈时低沉音效，支持步进/暂停观察栈变化。

### 题解清单 (≥4星)
1. **Alexander（5星）**  
   - 亮点：代码简洁，直接通过栈操作实时计算成本，逻辑清晰。
2. **CashCollectFactory（4星）**  
   - 亮点：分两步补全字符串再统计，思路直观，便于调试。
3. **Heldivis（4星）**  
   - 亮点：代码极简，使用动态数组模拟栈，效率高。

### 最优思路或技巧提炼
- **贪心闭合**：空缺位置优先填右括号，使得已存在的左括号尽早闭合。
- **栈跟踪法**：用栈保存左括号位置，实时维护未闭合括号集合。
- **实时累加**：在闭合操作时直接计算距离差，避免二次遍历。

### 同类型题与算法套路
- **括号匹配**：如LeetCode 921（最少添加使有效）、32（最长有效括号）。
- **贪心+栈**：适用于需动态维护最近可匹配元素的场景，如表达式求值。

### 推荐洛谷题目
1. P1944（最长括号匹配）
2. P1739（表达式括号匹配）
3. P7914（括号序列）

### 代码片段（Alexander的核心逻辑）
```cpp
stack<int> st;
for (int i = 1; i <= n; i++) {
    c = getchar();
    if (c == '_') {            // 空缺位置
        if (!st.empty()) {     // 优先闭合
            res += i - st.top();
            st.pop();
        } else {               // 必须填左括号
            st.push(i);
        }
    } else if (c == '(') {     // 确定左括号
        st.push(i);
    } else {                   // 确定右括号
        res += i - st.top();
        st.pop();
    }
}
```

### 可视化与游戏化设计
- **8位像素风**：用16色调色板，栈显示为蓝色方块队列，闭合线为绿色。
- **自动演示**：逐帧推进算法流程，按空格键暂停/继续。
- **音效设计**：闭合时播放“哔”声，压栈时“咚”声，背景为8位循环音乐。

---

**总结**：贪心策略结合栈操作是该题的最优解，通过实时维护未闭合左括号位置，确保每次闭合距离最小。可视化设计通过动态元素和音效增强理解，适用于类似括号匹配问题。

---
处理用时：174.61秒