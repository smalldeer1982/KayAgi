# 题目信息

# Verse Pattern

## 题目描述

You are given a text consisting of $ n $ lines. Each line contains some space-separated words, consisting of lowercase English letters.

We define a syllable as a string that contains exactly one vowel and any arbitrary number (possibly none) of consonants. In English alphabet following letters are considered to be vowels: 'a', 'e', 'i', 'o', 'u' and 'y'.

Each word of the text that contains at least one vowel can be divided into syllables. Each character should be a part of exactly one syllable. For example, the word "mamma" can be divided into syllables as "ma" and "mma", "mam" and "ma", and "mamm" and "a". Words that consist of only consonants should be ignored.

The verse patterns for the given text is a sequence of $ n $ integers $ p_{1},p_{2},...,p_{n} $ . Text matches the given verse pattern if for each $ i $ from $ 1 $ to $ n $ one can divide words of the $ i $ -th line in syllables in such a way that the total number of syllables is equal to $ p_{i} $ .

You are given the text and the verse pattern. Check, if the given text matches the given verse pattern.

## 说明/提示

In the first sample, one can split words into syllables in the following way:

`in-tel<br></br>co-de<br></br>ch al-len-ge<br></br>`Since the word "ch" in the third line doesn't contain vowels, we can ignore it. As the result we get $ 2 $ syllabels in first two lines and $ 3 $ syllables in the third one.

## 样例 #1

### 输入

```
3
2 2 3
intel
code
ch allenge
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
1 2 3 1
a
bcdefghi
jklmnopqrstu
vwxyz
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
13 11 15 15
to be or not to be that is the question
whether tis nobler in the mind to suffer
the slings and arrows of outrageous fortune
or to take arms against a sea of troubles
```

### 输出

```
YES
```

# AI分析结果



**唯一算法分类**：字符串处理

---

### **综合分析与结论**

**题目核心**：判断每行文本的元音总数是否等于给定模式。由于每个音节恰好一个元音，总音节数等于元音总数，直接统计元音即可。

**解决难点**：
1. **输入处理**：每行可能包含空格，需用 `getline` 读取整行。
2. **换行符处理**：输入 `n` 后的换行符需用 `getchar()` 或额外 `getline` 吸收。
3. **元音判断**：包含 `y` 易被遗漏。

**可视化设计**：
- **动画流程**：逐字符扫描，高亮元音并累加计数器，与目标值实时比对。
- **复古像素风格**：字符以像素块显示，元音高亮为绿色，非元音灰色。音效触发于元音检测和最终结果。
- **步进控制**：支持暂停/继续，速度调节，错误时播放失败音效，成功时播放胜利音效。

---

### **题解清单 (≥4星)**

1. **zhang_kevin（5星）**  
   - **亮点**：代码简洁，明确处理换行符，逐字符判断元音。
   - **代码片段**：
     ```cpp
     getchar(); // 吸收换行
     getline(cin, s);
     for (int j = 0; j < s.length(); j++) {
         if (s[j]是元音) ans++;
     }
     ```

2. **liangbowen（5星）**  
   - **亮点**：详细解释 `getline` 的用法，强调输入流处理。
   - **代码片段**：
     ```cpp
     getline(cin, s); // 吸收换行
     for (char c : s) cnt += (c是元音);
     ```

3. **OoXiao_QioO（4星）**  
   - **亮点**：使用 `getchar()` 逐字符读取，避免处理整行字符串。
   - **代码片段**：
     ```cpp
     while ((c = getchar()) != '\n') {
         if (是元音) cnt++;
     }
     ```

---

### **最优思路提炼**

**关键步骤**：
1. **输入处理**：使用 `getline` 读取整行，吸收前导换行符。
2. **元音统计**：遍历每个字符，检查是否为 `a, e, i, o, u, y`。
3. **即时判断**：一旦某行元音数与目标不符，立即终止并输出 `NO`。

**代码实现**：
```cpp
#include <iostream>
using namespace std;

int main() {
    int n, p[105];
    cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i];
    cin.ignore(); // 吸收换行符
    
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        int cnt = 0;
        for (char c : s) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') {
                cnt++;
            }
        }
        if (cnt != p[i]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}
```

---

### **同类型题推荐**

1. **P1308 [统计单词数]**：处理含空格的字符串，统计单词出现次数。
2. **P1598 [垂直柱状图]**：统计字母频率并绘制柱状图。
3. **P1765 [手机]**：模拟手机键盘输入，计算按键次数。

---

### **个人心得摘录**

- **OoXiao_QioO**：因漏掉 `y` 导致 WA，强调仔细审题。
- **MLCabc**：`getline` 必须在 `cin` 后吸收换行，否则读空数据。

---

### **可视化与算法演示**

**动画设计**：
1. **输入展示**：以像素网格显示每行输入，元音高亮为绿色。
2. **统计过程**：逐个字符扫描，元音触发音效（如8位“哔”声）。
3. **结果对比**：每行末尾显示目标值与实际值，不匹配时屏幕闪烁红色。

**交互功能**：
- **速度控制**：滑动条调节扫描速度（慢速学习/快速浏览）。
- **AI模式**：自动播放，模拟“正确”和“错误”路径，对比结果。

---
处理用时：94.83秒