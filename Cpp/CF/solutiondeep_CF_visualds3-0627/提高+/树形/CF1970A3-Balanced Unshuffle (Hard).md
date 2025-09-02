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

**唯一算法分类**：构造、栈的应用

---

### 综合分析与结论

**核心思路**：  
题目要求逆向平衡洗牌操作，还原原序列。核心在于理解洗牌排序规则（按前缀平衡值升序，同值按原位置降序），将输入字符串分段处理，逆序还原出原序列。

**算法流程关键点**：  
1. **分段策略**：根据前缀平衡值将输入字符串划分为多个段，每个段对应原序列中的一层嵌套结构。  
2. **逆序处理**：同一段内字符按原位置逆序排列（因排序规则中的位置降序）。  
3. **栈管理**：为每个前缀平衡值维护一个栈，保存该层字符，最后按层级顺序弹出字符构造原序列。  

**难点与解决**：  
- **正确分段**：需动态统计左括号数量，确定每段右括号的抵消条件。  
- **逆序还原**：利用栈的先进后出特性，模拟排序后的逆序弹出过程。  

---

### 题解清单（≥4星）

1. **cjh20090318（⭐⭐⭐⭐⭐）**  
   **亮点**：  
   - 简洁的栈数组实现，时间复杂度 O(n)。  
   - 分段统计左括号与抵消右括号，逻辑清晰。  
   **核心代码**：  
   ```cpp
   stack<char,vector<char> > t[MAXN]; // 栈数组存储各层字符
   for(int i=0,j;i<n;i=j){
       for(j=i; j<n && s[j]=='('; j++) t[x].push(s[j]); // 左括号入栈
       x++;
       for(r=l; j<n && r; j++) t[x].push(s[j]), r -= (s[j]==')'); // 右括号抵消
   }
   ```

2. **SFlyer（⭐⭐⭐⭐）**  
   **亮点**：  
   - 树结构构建，直观展示括号嵌套层次。  
   - 通过 DFS 遍历生成序列，逻辑类似括号树遍历。  

3. **EXODUS（⭐⭐⭐⭐）**  
   **亮点**：  
   - 动态维护父子节点关系，模拟嵌套结构。  
   - 通过后序遍历生成序列，符合括号闭合顺序。  

---

### 最优思路提炼

**关键技巧**：  
- **栈数组分层存储**：每个前缀平衡值对应一个栈，逆序保存字符。  
- **动态抵消计数**：处理右括号时统计抵消数量，确定段边界。  
- **层级跳跃**：构造原序列时根据括号类型调整当前层级（左括号进入子层，右括号返回父层）。  

**代码实现**：  
```cpp
// 构造原序列核心逻辑
for(char c; !t[x].empty();) {
    putchar(c = t[x].top());
    t[x].pop();
    x += (c == '(') ? 1 : -1; // 左括号进入下层，右括号返回上层
}
```

---

### 同类型题与算法套路

**通用解法**：  
- 括号序列问题常涉及栈、树结构或层级计数。  
- 逆序处理技巧适用于需要还原操作步骤的场景（如撤销操作）。  

**类似题目**：  
1. **CF1970A1/A2**（同系列简单/中等版）  
2. **洛谷 P7913 [CSP-S 2021] 括号序列**（构造合法括号序列）  
3. **LeetCode 856. Score of Parentheses**（括号嵌套计算）  

---

### 个人心得摘录

- **cjh20090318**：使用 `vector` 特化的 `stack` 避免内存问题，警示 STL 容器选择的重要性。  
- **SFlyer**：通过示例分析发现分段规律，强调观察具体案例推导通解。  

---

### 可视化与算法演示

**动画方案**：  
1. **分层栈可视化**：  
   - 用垂直排列的栈表示不同层级，新字符压入对应层级栈顶。  
   - 高亮当前处理的字符和活跃栈（如右括号抵消时红色闪烁）。  
   ![栈分层示意图](https://cdn.luogu.com.cn/upload/image_hosting/3m7xr3o0.png)  

2. **构造过程演示**：  
   - 初始状态：所有栈为空，指针在输入字符串起始位置。  
   - 左括号压栈：字符进入当前层级栈，层级值显示在栈右侧。  
   - 右括号处理：字符进入当前层级栈，动态减少抵消计数器。  
   - 生成原序列：从层级 0 开始，弹出字符并动态调整层级。  

**复古像素风格设计**：  
- **颜色方案**：左括号绿色（#00FF00），右括号红色（#FF0000），栈边框灰色（#808080）。  
- **音效设计**：  
  - 压栈：8-bit 短促“滴”声。  
  - 弹栈：低沉“嘟”声。  
  - 层级切换：上升音阶。  

**交互功能**：  
- **步进控制**：空格暂停/继续，左右键单步前进/后退。  
- **层级高亮**：鼠标悬停显示当前栈的层级值和字符数量。  

---

**示例代码（关键动画逻辑）**：  
```javascript
// 伪代码：栈压入过程动画
function animatePush(stackIdx, char) {
    const stack = document.getElementById(`stack-${stackIdx}`);
    const pixel = createPixel(char); // 创建像素块元素
    stack.appendChild(pixel);
    playSound('push_sound.wav');
    animate(pixel, 'bounce');
}
```

---
处理用时：79.03秒