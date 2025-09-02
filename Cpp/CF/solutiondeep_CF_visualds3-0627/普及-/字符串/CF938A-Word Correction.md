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



**唯一算法分类**  
字符串处理

---

**综合分析与结论**  
题目要求删除相邻元音中的后者，需确保处理后无相邻元音。核心难点在于正确处理多次连续删除后的新相邻情况。各题解思路对比：  

1. **多次扫描法**（happybob）：通过循环遍历字符串直至无相邻元音，每次删除后一个元音。正确但时间复杂度较高（O(n²)），适用于小规模数据。  
2. **单次遍历法**（monstersqwq、Zirnc）：利用前驱状态判断，仅输出非连续元音，在单次遍历中隐式处理所有可能情况。时间复杂度O(n)，高效且简洁。  
3. **栈法**（monstersqwq）：维护栈顶元音状态，仅压入非连续元音。逻辑清晰，时间复杂度O(n)。  

**可视化设计思路**  
- **动画方案**：以字符数组展示，高亮当前处理位置，若发现相邻元音对，标记后一个为删除（红色）。单次遍历法中，绿色表示已输出字符，灰色表示跳过字符。  
- **复古像素风**：字符显示为8位方块，删除操作用爆炸动画和音效。自动播放时，逐步移动指针并触发对应操作。  
- **步进控制**：支持暂停/继续，调整速度观察标记和删除过程。  

---

**题解清单 (≥4星)**  
1. **monstersqwq的第一种解法（5星）**  
   - 亮点：单次遍历，判断当前与前一个是否均为元音，仅输出非连续元音。  
   - 代码简洁高效，直接解决问题。  

2. **Zirnc的解法（4星）**  
   - 亮点：输出当前元音后跳过后续连续元音，逻辑直接。  
   - 代码简短，但需注意边界条件。  

3. **happybob的解法（4星）**  
   - 亮点：多次扫描确保完全处理，鲁棒性强。  
   - 代码稍复杂，但符合直觉，适合教学。  

---

**最优思路提炼**  
**单次遍历状态标记法**：遍历时记录前一个字符是否为元音，若当前和前一个均为元音则跳过当前字符。此方法无需额外空间，时间复杂度O(n)，适用于线性处理。  

**关键代码片段**  
```cpp
// monstersqwq解法核心逻辑
for (int i = 0; i < n; i++) {
    if (i == 0) {
        cout << s[i];
        continue;
    }
    if (is_vowel(s[i]) && is_vowel(s[i-1])) 
        continue;
    else 
        cout << s[i];
}
```

---

**同类型题拓展**  
- **相邻元素处理**：如删除重复项（LeetCode 26）、压缩字符串（LeetCode 443）。  
- **状态机应用**：如解析特定模式的字符串（括号匹配、正则表达式）。  

**推荐题目**  
1. 洛谷 P1308 [统计单词数]（字符串遍历）  
2. 洛谷 P1055 [ISBN号码]（字符处理与校验）  
3. 洛谷 P1598 [垂直柱状图]（字符频率统计）  

---

**个人心得摘录**  
- **judgejudge**提到转换01序列后需处理多次相邻情况，强调需考虑处理后新产生的相邻对。  
- **Chthology**采用逐字符在线处理，避免数组操作，但需注意初始状态设置。  

---

**可视化算法演示**  
```javascript
// 伪代码：复古像素风动画核心逻辑
let s = "aaeaa";
let pixels = [];
for (let i = 0; i < s.length; i++) {
    // 绘制字符块（8位风格）
    let block = createPixelBlock(s[i], x, y);
    pixels.push(block);
    // 判断与前一个是否均为元音
    if (i > 0 && isVowel(s[i]) && isVowel(s[i-1])) {
        block.setColor('red'); // 标记删除
        playSound('delete');   // 8-bit音效
    } else {
        block.setColor('green'); // 保留
    }
}
```

---
处理用时：322.95秒