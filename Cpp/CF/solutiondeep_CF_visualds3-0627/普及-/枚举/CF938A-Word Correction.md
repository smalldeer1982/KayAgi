# 题目信息

# Word Correction

## 题目背景

给一个长为n的字符串，当有两个元音字母相邻时，删除后一个元音，输出修改后的字符串。（注：a,e,i,o,u,y为元音字母）

## 题目描述

Victor tries to write his own text editor, with word correction included. However, the rules of word correction are really strange.

Victor thinks that if a word contains two consecutive vowels, then it's kinda weird and it needs to be replaced. So the word corrector works in such a way: as long as there are two consecutive vowels in the word, it deletes the first vowel in a word such that there is another vowel right before it. If there are no two consecutive vowels in the word, it is considered to be correct.

You are given a word $ s $ . Can you predict what will it become after correction?

In this problem letters a, e, i, o, u and y are considered to be vowels.

## 说明/提示

Explanations of the examples:

1. There is only one replace: weird ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png) werd;
2. No replace needed since there are no two consecutive vowels;
3. aaeaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aeaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png) a.

## 样例 #1

### 输入

```
5
weird
```

### 输出

```
werd
```

## 样例 #2

### 输入

```
4
word
```

### 输出

```
word
```

## 样例 #3

### 输入

```
5
aaeaa
```

### 输出

```
a
```

# AI分析结果



---

**唯一算法分类**：字符串处理/贪心算法

---

### **题解思路与难点分析**
- **核心逻辑**：遍历字符串，保留每个连续元音块的第一个元音，跳过后续元音。
- **关键步骤**：
  1. 使用一个标记变量记录前一个保留的字符是否为元音。
  2. 遍历字符串时，若当前字符是元音且标记为已保留元音，则跳过；否则保留并更新标记。
- **解决难点**：确保一次遍历即可处理所有连续元音，避免多次扫描。
- **数据结构**：无需复杂结构，仅用变量或标记数组。

---

### **题解评分（≥4星）**
1. **珅肐的解法（5星）**
   - **亮点**：在线处理，变量标记前一个是否元音，代码简洁高效。
   - 代码片段：
     ```cpp
     if (当前是元音且前一个标记为元音) -> 跳过
     else -> 输出并更新标记
     ```
2. **Eason_AC的解法（5星）**
   - **亮点**：通过 `vowel` 变量记录状态，仅需一次遍历。
   - 代码片段：
     ```cpp
     if (当前是元音 && vowel) continue;
     else 输出并更新 vowel 状态。
     ```
3. **Chthology的解法（5星）**
   - **亮点**：类似珅肐的思路，使用 `tag` 变量控制输出。
   - 代码片段：
     ```cpp
     if (当前是辅音) -> 输出并重置标记
     else if (标记未设置) -> 输出并设置标记
     ```

---

### **最优思路与技巧**
- **贪心策略**：保留连续元音的第一个，跳过后续元音。
- **关键变量**：使用 `vowel` 或 `tag` 标记前一个字符是否为元音。
- **时间复杂度**：$O(n)$，仅需一次遍历。

---

### **同类型题目与算法套路**
- **类似问题**：删除相邻重复项（如 LeetCode 1047）。
- **通用解法**：通过遍历+状态标记处理连续元素，避免多次扫描。

---

### **推荐题目**
1. **洛谷 P1308**：统计单词数（字符串匹配）。
2. **洛谷 P1553**：数字反转（字符串处理）。
3. **洛谷 P1071**：潜伏者（字符替换与映射）。

---

### **个人心得摘录**
- **调试教训**：需注意 `y` 是否为元音（易遗漏）。
- **边界处理**：如字符串末尾的越界检查（Zirnc的解法因未处理导致错误）。

---

### **可视化算法设计**
1. **动画方案**：
   - **像素风格**：用绿色高亮保留的元音，红色标记跳过的元音。
   - **步进执行**：显示当前字符是否被保留，并更新标记变量。
   - **控制面板**：支持暂停/继续、调整速度。
2. **演示示例**（输入 `aaeaa`）：
   - 初始字符串：`a a e a a`。
   - 第1步：保留第一个 `a`，标记为元音。
   - 后续步骤：跳过所有后续元音，最终输出 `a`。
3. **音效设计**：
   - 保留字符时播放清脆音效，跳过时播放低沉音效。

---

### **代码实现（珅肐的解法）**
```cpp
#include<iostream>
using namespace std;
int main() {
    int n, m = 0; // m标记前一个是否为元音
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'y') {
            cout << c;  // 辅音直接输出
            m = 0;      // 重置标记
        } else if (m) { // 前一个是元音，跳过当前
            continue;
        } else {        // 保留当前元音
            cout << c;
            m = 1;      // 设置标记
        }
    }
    return 0;
}
```

---

**总结**：最优解法通过一次遍历和状态标记，高效处理连续元音，时间复杂度 $O(n)$，代码简洁且鲁棒性强。

---
处理用时：260.08秒