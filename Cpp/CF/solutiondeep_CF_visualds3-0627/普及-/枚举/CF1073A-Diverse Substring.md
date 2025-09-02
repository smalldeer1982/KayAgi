# 题目信息

# Diverse Substring

## 题目描述

You are given a string $ s $ , consisting of $ n $ lowercase Latin letters.

A substring of string $ s $ is a continuous segment of letters from $ s $ . For example, "defor" is a substring of "codeforces" and "fors" is not.

The length of the substring is the number of letters in it.

Let's call some string of length $ n $ diverse if and only if there is no letter to appear strictly more than $ \frac n 2 $ times. For example, strings "abc" and "iltlml" are diverse and strings "aab" and "zz" are not.

Your task is to find any diverse substring of string $ s $ or report that there is none. Note that it is not required to maximize or minimize the length of the resulting substring.

## 说明/提示

The first example has lots of correct answers.

Please, restrain yourself from asking if some specific answer is correct for some specific test or not, these questions always lead to "No comments" answer.

## 样例 #1

### 输入

```
10
codeforces
```

### 输出

```
YES
code
```

## 样例 #2

### 输入

```
5
aaaaa
```

### 输出

```
NO
```

# AI分析结果



---

**算法分类**：字符串遍历/贪心策略

---

### **题解思路与难点分析**
**核心思路**：  
题目要求找出任意长度的子串，使得其中所有字符出现次数不超过子串长度的一半。通过观察发现，若存在相邻两个不同字符（如`ab`），则长度为2的子串满足条件（每个字符出现次数为1，不超过1）。若整个字符串所有相邻字符均相同，则无解。

**解决难点**：  
1. **关键观察**：最短的满足条件的子串长度为2，此时只需两个不同字符即可。
2. **优化思路**：无需遍历所有可能的子串，只需检查相邻字符是否不同，时间复杂度从暴力法的O(n²)降为O(n)。
3. **边界处理**：当n=1时直接输出NO；当字符串全为相同字符时输出NO。

---

### **题解评分 (≥4星)**
1. **Annihilation_y (5星)**  
   - 亮点：代码简洁高效，直接遍历相邻字符判断，无冗余操作。
2. **liuyz11 (4星)**  
   - 亮点：明确解释数学条件（各字符出现次数不超过总和），代码逻辑清晰。
3. **decoqwq (4星)**  
   - 亮点：代码简短，直接通过下标遍历相邻字符，适合快速实现。

---

### **最优思路与技巧提炼**
**关键技巧**：  
- **贪心策略**：优先检查最短可能的子串（长度为2），降低时间复杂度。
- **边界剪枝**：若字符串长度为1直接判定无解。
- **遍历优化**：只需线性遍历一次字符串，比较相邻字符即可。

**代码片段**：
```cpp
for (int i = 1; i < n; i++) {
    if (s[i] != s[i-1]) { // 核心判断
        cout << "YES\n" << s[i-1] << s[i];
        return 0;
    }
}
cout << "NO";
```

---

### **同类型题与算法套路**
**通用解法**：  
- **字符串模式匹配**：寻找特定字符组合（如相邻不同字符）。
- **贪心策略**：优先检查局部最优解（最短满足条件的子串）。

**推荐题目**：  
1. CF977B - 找出出现次数最多的长度为2的子串。
2. LeetCode 3 - 最长无重复字符子串。
3. 洛谷P1739 - 表达式括号匹配（类似线性遍历判断）。

---

### **个人心得摘录**
- **Annihilation_y**：直接结束程序（`return 0`）避免使用标志变量，简化代码。
- **OoXiao_QioO**：调试时发现必须从`i=1`开始遍历，避免数组越界。
- **zsc2003**：暴力法虽正确但效率低，适合教学演示而非实际竞赛。

---

### **算法可视化与复古动画设计**
**动画方案**：  
1. **像素风格遍历**：  
   - **Canvas网格**：将字符串字符显示为像素方块，背景色为深蓝，字符颜色为黄色。
   - **高亮当前字符对**：用红色边框标记当前比较的`i`和`i-1`位置字符。
   - **步进效果**：按空格键单步执行，自动模式时每步间隔500ms。
2. **音效设计**：  
   - **发现解**：播放8-bit胜利音效（上升音阶）。
   - **无解**：播放低沉失败音效。
   - **单步移动**：轻微“滴”声提示遍历进度。
3. **自动演示**：  
   - AI自动从左到右遍历，红色光标逐步移动，找到解时弹出结果窗口。

**代码片段（JS伪代码）**：
```javascript
function animateCheck() {
  let i = 1;
  const interval = setInterval(() => {
    highlight(i-1, i); // 高亮当前字符对
    if (s[i] !== s[i-1]) {
      playSuccessSound();
      showResult(s.substring(i-1, i+1));
      clearInterval(interval);
    } else if (i === s.length-1) {
      playFailSound();
      showResult("NO");
      clearInterval(interval);
    }
    i++;
  }, 500);
}
```

---

### **总结**
本题通过观察最短子串性质，将问题简化为线性遍历，体现了贪心策略在字符串处理中的高效应用。可视化设计通过复古像素风格和音效增强理解，适合教学演示。

---
处理用时：73.19秒