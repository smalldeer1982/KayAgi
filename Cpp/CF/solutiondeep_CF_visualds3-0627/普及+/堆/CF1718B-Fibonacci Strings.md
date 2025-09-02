# 题目信息

# Fibonacci Strings

## 题目描述

In all schools in Buryatia, in the $ 1 $ class, everyone is told the theory of Fibonacci strings.

"A block is a subsegment of a string where all the letters are the same and are bounded on the left and right by the ends of the string or by letters other than the letters in the block. A string is called a Fibonacci string if, when it is divided into blocks, their lengths in the order they appear in the string form the Fibonacci sequence ( $ f_0 = f_1 = 1 $ , $ f_i = f_{i-2} + f_{i-1} $ ), starting from the zeroth member of this sequence. A string is called semi-Fibonacci if it possible to reorder its letters to get a Fibonacci string."

Burenka decided to enter the Buryat State University, but at the entrance exam she was given a difficult task. She was given a string consisting of the letters of the Buryat alphabet (which contains exactly $ k $ letters), and was asked if the given string is semi-Fibonacci. The string can be very long, so instead of the string, she was given the number of appearances of each letter ( $ c_i $ for the $ i $ -th letter) in that string. Unfortunately, Burenka no longer remembers the theory of Fibonacci strings, so without your help she will not pass the exam.

## 说明/提示

In the first test case, a one-character string is semi-Fibonacci, being itself a Fibonacci string.

In the second test case, a string of two different characters is Fibonacci.

In the third test case, the string "abb" (let the first of the alphabet letter be a, the second letter b) is not a semi-Fibonacci string, since no permutation of its letters ("abb", "bab", and "bba") is a Fibonacci string.

In the fourth test case, two permutations of the letters of the string "abaccac" (the first letter is a, the second letter is b, the third letter is c) are Fibonacci strings — "abaaccc" and "cbccaaa".

## 样例 #1

### 输入

```
6
1
1
2
1 1
2
1 2
3
3 1 3
2
7 5
6
26 8 3 4 13 34```

### 输出

```
YES
YES
NO
YES
NO
YES```

# AI分析结果



## 算法分类  
**贪心算法**

---

## 综合分析与结论  
### 核心思路  
1. **总字符数验证**：总字符数必须等于斐波那契前缀和，否则直接无解。  
2. **贪心策略**：从最大的斐波那契数开始，依次选择当前剩余最多的字符填充块，且避免连续使用同一字符。  

### 难点与解决方案  
- **正确性证明**：斐波那契数列的不可分割性决定了必须用最大可用字符处理当前最大的块，否则剩余字符无法满足后续块的要求。  
- **避免重复选择**：通过记录上一次选择的字符，确保不连续使用同一字符。  

### 可视化设计  
1. **动画流程**：  
   - **颜色标记**：当前处理的斐波那契数（红色）、当前选中的字符（绿色）、上一次选择的字符（灰色）。  
   - **步进控制**：可调节速度或单步执行，观察每一步的字符数量变化。  
   - **音效提示**：成功选择时播放上升音调，失败时播放下降音调。  

2. **复古风格**：  
   - **像素方块**：用不同颜色的方块表示各字符的剩余数量，每次选中时方块缩小对应斐波那契数的长度。  
   - **音效**：使用 8-bit 音效模拟经典游戏操作。  

---

## 题解清单 (≥4星)  
1. **happy_dengziyue (5星)**  
   - **亮点**：使用优先队列高效维护最大字符，代码简洁且时间复杂度低。  
   - **关键代码**：  
     ```cpp  
     priority_queue<long long> q;  
     for (处理每个字符) q.push(a[i]);  
     while (!q.empty()) {  
         long long u = q.top(); q.pop();  
         if (u < f[pos]) 无解;  
         u -= f[pos];  
         if (u > 0) q.push(u);  
         pos--;  
     }  
     ```  

2. **Alex_Wei (4星)**  
   - **亮点**：数学归纳法证明贪心正确性，优化处理逻辑。  
   - **关键代码**：  
     ```cpp  
     sort(c + 1, c + n + 1);  
     for (int i = k; i >= 1; i--) {  
         c[n] -= f[i];  
         if (c[n] < 0 || c[n] > c[n-1]) 无解;  
         sort(c + 1, c + n + 1);  
     }  
     ```  

3. **Micnation_AFO (4星)**  
   - **亮点**：结合堆与标记机制避免重复选择，代码可读性强。  
   - **关键代码**：  
     ```cpp  
     priority_queue<pair<ll, int>> q;  
     q.push({a[i], i});  
     if (当前字符 == 上一次选择的字符) 选择次大字符;  
     ```  

---

## 最优思路提炼  
1. **斐波那契前缀和验证**：总和必须匹配斐波那契前缀和。  
2. **逆向贪心选择**：从最大斐波那契数开始，每次选最大可用字符。  
3. **避免重复标记**：记录上一次选择的字符，确保不连续使用。  

---

## 类似题目  
1. **P1896 斐波那契数列拆分**：判断数能否拆分为不连续的斐波那契数之和。  
2. **CF1538D 字符重组**：类似贪心策略判断字符重组可能性。  
3. **洛谷 P1216 数字三角形**：贪心选择最大值的思想。  

---

## 可视化代码片段 (JS)  
```javascript  
// 初始化 Canvas  
const canvas = document.getElementById('canvas');  
const ctx = canvas.getContext('2d');  
const blockSize = 20; // 像素方块大小  

function drawBlocks(blocks, selectedIdx, lastIdx) {  
    ctx.clearRect(0, 0, canvas.width, canvas.height);  
    blocks.forEach((count, idx) => {  
        ctx.fillStyle = idx === selectedIdx ? '#00FF00' : (idx === lastIdx ? '#888888' : '#FF0000');  
        ctx.fillRect(idx * blockSize, 0, blockSize - 2, count * blockSize);  
    });  
}  

// 示例动画流程  
let fibs = [5, 3, 2, 1, 1];  
let chars = [7, 5];  
let lastSelected = -1;  
fibs.forEach((fib, step) => {  
    const maxIdx = chars.reduce((maxIdx, val, idx) =>  
        (val > chars[maxIdx] && idx !== lastSelected) ? idx : maxIdx, 0);  
    chars[maxIdx] -= fib;  
    drawBlocks(chars, maxIdx, lastSelected);  
    lastSelected = maxIdx;  
    // 播放音效  
    new Audio('success.wav').play();  
});  
```  

---

## 个人心得摘录  
- **happy_dengziyue**：调试中发现必须严格避免同一字符连续选择，否则贪心策略会失败。  
- **Alex_Wei**：通过数学归纳法证明贪心正确性，避免陷入复杂分支判断。  

---

## 复古游戏化动画设计  
1. **颜色方案**：红（当前块）、绿（选中字符）、灰（禁用字符）。  
2. **音效触发**：  
   - **成功选择**：上升音调（8-bit 风格）。  
   - **失败**：短促爆炸音。  
3. **自动演示**：AI 自动运行贪心算法，用户可随时暂停观察。  
4. **积分系统**：每正确选择一次得 10 分，连续正确触发连击奖励。  

---

**通过上述分析，题目核心在于贪心策略与斐波那契数列性质的结合，可视化设计可有效辅助理解算法流程。**

---
处理用时：97.39秒