# 题目信息

# [USACO06FEB] Cellphones G

## 题目描述

The cows have started using cellphones to cowmunicate with each other, but have found that the button layout doesn't suit their hooves very well. They are designing a special cellphone with fewer but larger buttons.


One feature they liked on the standard cellphones was predictive text. Each button has a few letters associated with it, and one types a word by pushing the associated buttons. Because there is more than one letter for each button, this can be ambiguous for some words.  However, most of the time the ambiguity can be resolved by using a dictionary to determine what word the user wanted.


Since the cows are designing a custom cellphone, they are also going to replace the English alphabet with the Cow alphabet. By an amazing coincidence, the cow alphabet is simply the first L (1 <= L <= 26) letters of the English alphabet, in the same order. They want to find out how to assign the letters of the Cow alphabet to the B buttons (1 <= B <= L) in such a way that the maximum number of words in their dictionary are unambiguous when entered with predictive text. Like normal cellphones, they want the letters on each button to be a contiguous section (one or more consecutive letters) of the alphabet.

奶牛的名字都是由英文字母表的前1(1 < K 26)个字母构成的.现在想设计一种手机， 有个按键.请你把这L个字母按顺序分配给B个按键，使能够通过按这些键而唯一确 定的奶牛数尽量多.


## 说明/提示

Explanation of the sample:




Button 1 contains AB, button two contains C-K, and button 3 contains LM. The words CELL, DILL, FILL and FILM are all entered as 2233, while the remaining 7 words are all entered uniquely.


## 样例 #1

### 输入

```
3 13
11
ALL
BALL
BELL
CALK
CALL
CELL
DILL
FILL
FILM
ILL
MILK```

### 输出

```
7
AB
CDEFGHIJK
LM```

# AI分析结果



### 综合分析与结论

**题目核心**：将字母连续划分为B个按键，最大化字典中唯一对应按键序列的单词数。  
**关键难点**：在指数级分割方案中高效寻找最优解，同时处理字典序约束。  
**题解策略**：DFS剪枝枚举所有合法分割方案，计算每个方案的唯一性得分，保留最优解。  
**可视化设计**：  
- **动画演示**：以字母序列为横轴，DFS递归时高亮当前处理位置，分叉显示两种选择（继续当前按键/新建按键）。  
- **像素风格**：按键用不同色块表示，字母分配时动态填充颜色，剪枝处显示红色警示。  
- **音效反馈**：找到更优解时播放胜利音效，递归回溯时播放点击音效。  
- **自动模式**：模拟DFS的选择过程，动态展示哈希计算与统计步骤。

---

### 题解清单（4星）

1. **DFS剪枝枚举法**（作者：HPXXZYY）  
   **亮点**：  
   - 通过DFS生成所有合法分割，利用`color +剩余字母≥B`剪枝，大幅减少搜索空间。  
   - 哈希编码设计巧妙（B+1进制），快速统计唯一单词数。  
   - 更新答案时自动处理字典序，无需额外比较。  

---

### 核心代码实现

**DFS剪枝逻辑**：
```cpp
void dfs(int sub, int color) {
    if (sub > L) {
        if (color >= B) updata_answer(); // 有效分割
        return;
    }
    // 尝试新建按键（需满足剩余字母足够）
    if (sub > 1 && color < B) { 
        ch[sub] = color + 1;
        dfs(sub + 1, color + 1);
    }
    // 延续当前按键（需保证后续可分完）
    if (color + (L - sub) >= B) { 
        ch[sub] = color;
        dfs(sub + 1, color);
    }
}
```

**哈希计算与统计**：
```cpp
void updata_answer() {
    for (int i = 1; i <= n; i++) {
        num[i] = 0;
        for (char c : str[i]) 
            num[i] = num[i] * (B + 1) + ch[c - 'A' + 1]; // B+1进制编码
    }
    sort(num + 1, num + n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++) 
        if (num[i] != num[i-1] && num[i] != num[i+1]) cnt++;
    if (cnt >= ans) { // 更新最优解及字典序
        ans = cnt;
        memcpy(CH, ch, sizeof(ch));
    }
}
```

---

### 最优思路提炼

1. **剪枝策略**：确保剩余字母足够分配给未分配的按键，避免无效递归。  
2. **哈希编码**：用`B+1`进制保证不同按键序列的编码唯一性，快速统计冲突。  
3. **字典序处理**：DFS优先延长当前按键，自然保证同解时左侧按键字母更多。

---

### 同类题目推荐

1. **P1090 [NOIP2004 提高组] 合并果子**（贪心选择最小代价）  
2. **P1106 删数问题**（贪心保留最优数字序列）  
3. **P2285 [HNOI2004] 打鼹鼠**（时间序列最优决策）

---

### 可视化实现要点

**Canvas绘制**：  
```javascript
// 初始化字母序列
drawLetters() {
    for (let i = 0; i < L; i++) {
        ctx.fillStyle = buttonColors[currentPartition[i]];
        ctx.fillRect(i * 30, 0, 28, 28); // 像素风格色块
    }
}
// DFS动画步骤
function dfsStep(sub) {
    highlightCurrentLetter(sub); // 高亮当前处理字母
    setTimeout(() => {
        if (canSplit()) { // 显示分叉动画
            playSound('split'); 
            drawSplit(sub);
        }
    }, 500);
}
```

**音效触发**：  
- **split.wav**：尝试分割时播放。  
- **success.wav**：找到更优解时播放。  
- **backtrack.wav**：递归回溯时播放。  

---

### 个人心得

- **剪枝条件调试**：初始未考虑剩余字母数必须≥剩余按键数，导致大量无效递归。  
- **哈希进制选择**：使用`B+1`而非`B`进制，避免不同长度字符串误判冲突。  
- **字典序陷阱**：更新答案时需用`≥`而非`>`，才能保留同分下的字典序最优解。

---
处理用时：88.42秒