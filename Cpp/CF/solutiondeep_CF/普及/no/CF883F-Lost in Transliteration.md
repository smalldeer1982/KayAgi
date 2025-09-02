# 题目信息

# Lost in Transliteration

## 题目描述

There are some ambiguities when one writes Berland names with the letters of the Latin alphabet.

For example, the Berland sound u can be written in the Latin alphabet as "u", and can be written as "oo". For this reason, two words "ulyana" and "oolyana" denote the same name.

The second ambiguity is about the Berland sound h: one can use both "h" and "kh" to write it. For example, the words "mihail" and "mikhail" denote the same name.

There are $ n $ users registered on the Polycarp's website. Each of them indicated a name represented by the Latin letters. How many distinct names are there among them, if two ambiguities described above are taken into account?

Formally, we assume that two words denote the same name, if using the replacements "u" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/77b2db707b29a82aec640f23cbd1fafe4293bbb0.png) "oo" and "h" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/77b2db707b29a82aec640f23cbd1fafe4293bbb0.png) "kh", you can make the words equal. One can make replacements in both directions, in any of the two words an arbitrary number of times. A letter that resulted from the previous replacement can participate in the next replacements.

For example, the following pairs of words denote the same name:

- "koouper" and "kuooper". Making the replacements described above, you can make both words to be equal: "koouper" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "kuuper" and "kuooper" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "kuuper".
- "khun" and "kkkhoon". With the replacements described above you can make both words to be equal: "khun" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "khoon" and "kkkhoon" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "kkhoon" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "khoon".

For a given list of words, find the minimal number of groups where the words in each group denote the same name.

## 说明/提示

There are four groups of words in the first example. Words in each group denote same name:

1. "mihail", "mikhail"
2. "oolyana", "ulyana"
3. "kooooper", "koouper"
4. "hoon", "khun", "kkkhoon"

There are five groups of words in the second example. Words in each group denote same name:

1. "hariton", "kkkhariton", "khariton"
2. "hkariton"
3. "buoi", "boooi", "boui"
4. "bui"
5. "boi"

In the third example the words are equal, so they denote the same name.

## 样例 #1

### 输入

```
10
mihail
oolyana
kooooper
hoon
ulyana
koouper
mikhail
khun
kuooper
kkkhoon
```

### 输出

```
4
```

## 样例 #2

### 输入

```
9
hariton
hkariton
buoi
kkkhariton
boooi
bui
khariton
boui
boi
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2
alex
alex
```

### 输出

```
1
```

# AI分析结果



# Lost in Transliteration

## 题目描述

用拉丁字母书写 Berland 名称时存在一些歧义。

1. Berland 发音 u 可以用 "u" 或 "oo" 表示。例如 "ulyana" 和 "oolyana" 是同一个名字。
2. Berland 发音 h 可以用 "h" 或 "kh" 表示。例如 "mihail" 和 "mikhail" 是同一个名字。

给定 $n$ 个用户注册的名字，求考虑上述歧义规则后，实际有多少个不同的名字。

## 说明/提示

两个字符串被视为相同，当且仅当通过任意次数的 "u" ↔ "oo" 和 "h" ↔ "kh" 替换可以使其相等。例如：
- "koouper" 和 "kuooper" 可以统一为 "kuuper"
- "khun" 和 "kkkhoon" 可以统一为 "khoon"

## 样例 #1

### 输入
```
10
mihail
oolyana
kooooper
hoon
ulyana
koouper
mikhail
khun
kuooper
kkkhoon
```

### 输出
```
4
```

## 样例 #2

### 输入
```
9
hariton
hkariton
buoi
kkkhariton
boooi
bui
khariton
boui
boi
```

### 输出
```
5
```

---

**算法分类**：字符串处理、哈希表

---

### 精选题解分析

#### 题解作者：LKY928261（★★★★★）
**关键亮点**：
1. **高效处理连续k**：从后往前扫描，遇到'h'时将前面所有连续的'k'标记为空格，避免频繁的字符串修改操作。
2. **统一替换规则**：将'u'替换为"oo"，确保标准形式唯一。
3. **空间换时间**：用空格标记待删除字符，最后统一处理，时间复杂度优化至$O(n)$。

**核心代码**：
```cpp
for(j = s.size()-1; j > 0; j--) {
    if(s[j] == 'h') { // 从后往前找h
        for(j--; j >=0 && s[j] == 'k'; j--) s[j] = ' '; // 标记k为空格
        j++; // 调整位置
    }
}
// 构造最终字符串，跳过空格，u转oo
for(j = 0; j < s.size(); j++) {
    if(s[j] != ' ') {
        if(s[j] == 'u') a[i] += "oo";
        else a[i] += s[j];
    }
}
```

#### 题解作者：PigJokerYellow（★★★★☆）
**关键亮点**：
1. **分步处理逻辑**：先处理所有'k'后接'h'的情况，再处理'u'的替换。
2. **字符串替换函数**：通过自定义函数逐步处理替换逻辑，代码结构清晰。

**核心代码**：
```cpp
string solve(string s) {
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'h') { // 处理h前的k
            int j = i-1;
            while(j >= 0 && s[j] == 'k') j--;
            s.erase(j+1, i-j-1);
            i = j+1;
        } else if(s[i] == 'u') { // u转oo
            s.replace(i, 1, "oo");
        }
    }
    return s;
}
```

---

### 最优思路总结
1. **标准化处理**：
   - 将连续的'k'后接'h'替换为单个'h'（如"kkh" → "h"）。
   - 将所有的'u'替换为"oo"。
2. **高效实现技巧**：
   - 从后往前扫描处理'h'，避免字符串频繁修改。
   - 使用哈希表（map/set）统计唯一标准化后的字符串数量。

---

### 拓展与相似题目
1. **字符串标准化处理**：
   - [CF1121C. System Testing](https://www.luogu.com.cn/problem/CF1121C)
   - [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
   - [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)

---

### 心得体会
- **处理顺序关键**：先处理'h'再处理'u'，避免替换后的新字符干扰原有规则。
- **避免频繁修改字符串**：用标记代替实际删除，显著提升性能。
- **测试用例验证**：通过样例中的复杂替换案例（如"kkkhoon" → "khoon"）验证算法正确性。

---
处理用时：188.19秒