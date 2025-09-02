# 题目信息

# Romaji

## 题目描述

Vitya has just started learning Berlanese language. It is known that Berlanese uses the Latin alphabet. Vowel letters are "a", "o", "u", "i", and "e". Other letters are consonant.

In Berlanese, there has to be a vowel after every consonant, but there can be any letter after any vowel. The only exception is a consonant "n"; after this letter, there can be any letter (not only a vowel) or there can be no letter at all. For example, the words "harakiri", "yupie", "man", and "nbo" are Berlanese while the words "horse", "king", "my", and "nz" are not.

Help Vitya find out if a word $ s $ is Berlanese.

## 说明/提示

In the first and second samples, a vowel goes after each consonant except "n", so the word is Berlanese.

In the third sample, the consonant "c" goes after the consonant "r", and the consonant "s" stands on the end, so the word is not Berlanese.

## 样例 #1

### 输入

```
sumimasen
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
ninja
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
codeforces
```

### 输出

```
NO
```

# AI分析结果



---

**算法分类**：字符串处理（模拟）

---

### **题解思路与核心难点**

**题目核心**：验证字符串是否满足辅音后必须接元音（除'n'外）的规则，需处理以下情况：
1. 辅音（非'n'）必须后接元音。
2. 'n'后可接任意字符或无字符。
3. 字符串末尾的辅音（非'n'）直接判否。

**关键分析步骤**：
1. **遍历字符**：逐个检查每个字符是否为辅音且非'n'。
2. **边界处理**：若当前字符是辅音（非'n'）且为最后一个字符，直接返回`NO`。
3. **后继检查**：若非末尾辅音（非'n'），则检查下一个字符是否为元音。

**题解对比**：
- **错误处理**：前两篇题解未正确处理数组越界问题，可能导致未定义行为。
- **正确实现**：第三篇题解通过`i != Str.size() - 1`显式避免越界，逻辑严密。

---

### **题解评分 (≥4星)**

1. **小闸蟹（5星）**
   - **亮点**：逻辑严谨，显式处理末尾字符，代码可读性强。
   - **代码片段**：
     ```cpp
     if (OK(Str[i])) continue; // 元音跳过
     else if (Str[i] == 'n') continue; // 'n'跳过
     else if (i != Str.size() - 1 && OK(Str[i + 1])) continue; // 非末尾且后接元音
     else return cout << "NO", 0; // 其他情况判否
     ```

---

### **最优思路提炼**

**核心逻辑**：
```cpp
for (遍历每个字符) {
    if (当前是元音) continue;
    if (当前是'n') continue;
    if (是最后一个字符) return NO;
    if (下一个字符不是元音) return NO;
}
return YES;
```

**实现技巧**：
- **边界检查**：通过`i != Str.size() - 1`避免越界。
- **函数封装**：用`OK()`函数判断元音，提高可读性。

---

### **类似题目推荐**

1. **P1308 统计单词数**：字符串匹配与条件判断。
2. **P1598 垂直柱状图**：字符频率统计与格式化输出。
3. **P1179 数字统计**：特定字符的条件遍历。

---

### **可视化算法演示**

**动画设计**：
1. **遍历高亮**：当前字符高亮为黄色，检查是否为辅音（非'n'）。
2. **边界标记**：若为末尾字符且是辅音（非'n'），标记为红色并终止。
3. **后继检查**：若非末尾，检查下一字符是否为元音（绿色成功，红色失败）。

**复古像素风格**：
- **Canvas 网格**：每个字符显示为8x8像素块，辅音为蓝色，元音为绿色，'n'为紫色。
- **音效**：正确步骤播放8-bit音效，错误时播放低沉音效。

**交互控制**：
- **步进按钮**：手动控制遍历速度。
- **自动播放**：按预设速度演示算法流程。

---

### **正确代码实现**

```cpp
#include <iostream>
#include <string>

bool is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
    std::string s;
    std::cin >> s;
    for (size_t i = 0; i < s.size(); ++i) {
        if (is_vowel(s[i])) continue;
        if (s[i] == 'n') continue;
        if (i == s.size() - 1 || !is_vowel(s[i+1])) {
            std::cout << "NO" << std::endl;
            return 0;
        }
    }
    std::cout << "YES" << std::endl;
    return 0;
}
```

---
处理用时：169.18秒