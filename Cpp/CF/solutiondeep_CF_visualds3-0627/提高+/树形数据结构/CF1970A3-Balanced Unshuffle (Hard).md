# 题目信息

# Balanced Unshuffle (Hard)

## 题目描述

The only difference with the medium version is the maximum length of the input.

A parentheses sequence is a string consisting of characters "(" and ")", for example "(()((".

A balanced parentheses sequence is a parentheses sequence which can become a valid mathematical expression after inserting numbers and operations into it, for example "(()(()))".

The balance of a parentheses sequence is defined as the number of opening parentheses "(" minus the number of closing parentheses ")". For example, the balance of the sequence "(()((" is 3.

A balanced parentheses sequence can also be defined as a parentheses sequence with balance 0 such that each of its prefixes has a non-negative balance.

We define the balanced shuffle operation that takes a parentheses sequence and returns a parentheses sequence as follows: first, for every character of the input sequence, we compute the balance of the prefix of the sequence before that character and write those down in a table together with the positions of the characters in the input sequence, for example:

Prefix balance01212321Position12345678Character(()(()))Then, we sort the columns of this table in increasing order of prefix balance, breaking ties in decreasing order of position. In the above example, we get:

Prefix balance01112223Position18427536Character()(()())The last row of this table forms another parentheses sequence, in this case "()(()())". This sequence is called the result of applying the balanced shuffle operation to the input sequence, or in short just the balanced shuffle of the input sequence.

Surprisingly, it turns out that the balanced shuffle of any balanced parentheses sequence is always another balanced parentheses sequence (we will omit the proof for brevity). Even more surprisingly, the balanced shuffles of two different balanced parentheses sequences are always different, therefore the balanced shuffle operation is a bijection on the set of balanced parentheses sequences of any given length (we will omit this proof, too).

You are given a balanced parentheses sequence. Find its preimage: the balanced parentheses sequence the balanced shuffle of which is equal to the given sequence.

## 样例 #1

### 输入

```
()(()())```

### 输出

```
(()(()))```

# AI分析结果



---

**唯一算法分类**：栈的应用与分层处理

---

### **题解思路与核心难点**

**核心问题**：通过逆向操作恢复原平衡括号序列。核心难点在于如何根据排序规则（前缀平衡升序，位置降序）反向推导字符的原始位置。

**算法要点**：
1. **分层处理**：将结果字符串按前缀平衡值分层，每层对应一组字符。
2. **逆序存储**：利用栈结构保存每层的字符，保证取出顺序符合原位置降序规则。
3. **动态调整层级**：根据右括号数量动态调整当前层级，确保平衡条件。

**题解对比**：
- **cjh20090318**：通过栈数组直接模拟逆过程，时间复杂度 O(n)，代码简洁高效。
- **SFlyer**：构建括号树结构并 DFS 输出，思路直观但实现复杂。
- **EXODUS**：类似 SFlyer 的思路，但代码更复杂。

---

### **题解评分 (≥4星)**

1. **cjh20090318（⭐⭐⭐⭐⭐）**  
   - **亮点**：代码简洁，利用栈分层处理，直接模拟逆过程。
   - **代码片段**：
     ```cpp
     stack<char,vector<char>> t[MAXN];  // 使用 vector 特化的栈减少内存占用
     for (int i=0,j; i<n; i=j) {
         // 处理左括号段
         for (j=i; j<n && s[j]=='('; j++) t[x].push(s[j]);
         // 处理右括号段，动态调整层级
         for (r=l, l=0; j<n && r; j++) t[x].push(s[j]), ... ;
     }
     ```
   - **心得**：避免使用基于 `deque` 的容器防止内存爆炸。

---

### **最优思路提炼**

**关键技巧**：
1. **栈逆序存储**：每层字符按逆序压入栈，弹出时自然满足原位置降序规则。
2. **动态层级调整**：通过右括号数量确定当前层结束，进入下一层。
3. **线性时间复杂度**：仅需一次遍历输入，一次遍历栈输出。

---

### **同类型题推荐**

1. **CF1023D**（括号序列与栈操作）
2. **LeetCode 1190**（反转每层括号）
3. **洛谷 P5658**（括号树结构）

---

### **可视化算法演示**

**动画设计**：
1. **颜色标记**：
   - 红色：当前处理的字符。
   - 蓝色：栈层级变化时的分割线。
2. **步进流程**：
   - **分段阶段**：从左到右扫描输入，将字符分配到不同层级的栈中，动态显示栈增长。
   - **输出阶段**：按层级弹出栈顶字符，显示原序列逐步构建。
3. **复古像素风格**：
   - 使用 8 位音效：压栈时播放“哔”声，弹栈时播放“咚”声。
   - Canvas 网格显示栈结构，层级用不同颜色方块表示。

**交互控制**：
- **暂停/继续**：观察分段与层级调整。
- **速度调节**：慢速观察右括号抵消过程。

---

### **代码实现（核心逻辑）**

```cpp
// 分段处理输入，动态调整层级
int x = 0, l = 0, r;
for (int i = 0, j; i < n; i = j) {
    // 处理左括号段
    for (j = i; j < n && s[j] == '('; j++) {
        t[x].push(s[j]);
        l++;
    }
    x++; // 进入下一层
    // 处理右括号段，抵消左括号数
    r = l, l = 0;
    for (; j < n && r; j++) {
        t[x].push(s[j]);
        if (s[j] == '(') l++;
        else r--;
    }
}

// 输出阶段，按层级弹栈
for (char c; !t[x].empty();) {
    c = t[x].top();
    putchar(c);
    t[x].pop();
    x += (c == '(') ? 1 : -1; // 动态调整层级
}
```

---

### **总结**

通过逆向分层和栈结构，将字符按规则分配到各层并逆序存储，最终线性时间内还原原序列。该思路简洁高效，是处理此类括号问题的经典方法。

---
处理用时：99.71秒