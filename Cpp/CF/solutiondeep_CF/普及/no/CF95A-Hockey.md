# 题目信息

# Hockey

## 题目描述

Petya loves hockey very much. One day, as he was watching a hockey match, he fell asleep. Petya dreamt of being appointed to change a hockey team's name. Thus, Petya was given the original team name $ w $ and the collection of forbidden substrings $ s_{1},s_{2},...,s_{n} $ . All those strings consist of uppercase and lowercase Latin letters. String $ w $ has the length of $ |w| $ , its characters are numbered from $ 1 $ to $ |w| $ .

First Petya should find all the occurrences of forbidden substrings in the $ w $ string. During the search of substrings the case of letter shouldn't be taken into consideration. That is, strings "aBC" and "ABc" are considered equal.

After that Petya should perform the replacement of all letters covered by the occurrences. More formally: a letter in the position $ i $ should be replaced by any other one if for position $ i $ in string $ w $ there exist pair of indices $ l,r $ ( $ 1<=l<=i<=r<=|w| $ ) such that substring $ w[l ... r] $ is contained in the collection $ s_{1},s_{2},...,s_{n} $ , when using case insensitive comparison. During the replacement the letter's case should remain the same. Petya is not allowed to replace the letters that aren't covered by any forbidden substring.

Letter $ letter $ (uppercase or lowercase) is considered lucky for the hockey players. That's why Petya should perform the changes so that the $ letter $ occurred in the resulting string as many times as possible. Help Petya to find such resulting string. If there are several such strings, find the one that comes first lexicographically.

Note that the process of replacements is not repeated, it occurs only once. That is, if after Petya's replacements the string started to contain new occurrences of bad substrings, Petya pays no attention to them.

## 样例 #1

### 输入

```
3
bers
ucky
elu
PetrLoveLuckyNumbers
t
```

### 输出

```
PetrLovtTttttNumtttt
```

## 样例 #2

### 输入

```
4
hello
party
abefglghjdhfgj
IVan
petrsmatchwin
a
```

### 输出

```
petrsmatchwin
```

## 样例 #3

### 输入

```
2
aCa
cba
abAcaba
c
```

### 输出

```
abCacba
```

# AI分析结果



### 题目中文重写

#### 题目名称：冰球

**题目描述**  
Petya 非常热爱冰球。某天观看比赛时睡着了，梦见自己被任命修改冰球队名称。他得到原始队名 $w$ 和一组禁止的子串 $s_1,s_2,...,s_n$（均由大小写字母组成）。要求：

1. **不区分大小写**找出所有禁止子串的匹配位置。
2. 将这些位置的字符替换为其他字符，同时保持原字母的大小写。
3. 替换后字符串中指定幸运字母 $letter$ 的出现次数要尽可能多，次数相同时字典序最小。

**输入格式**  
- 第一行：整数 $n$  
- 接下来 $n$ 行：禁止子串  
- 随后两行：原始队名 $w$ 和幸运字母 $letter$

**输出格式**  
替换后的队名字符串。

---

### 算法分类  
字符串、模拟

---

### 题解对比与总结

#### 核心思路
1. **预处理**：将所有字符串转为小写以统一比较。
2. **标记替换位置**：暴力枚举每个子串可能出现的所有位置。
3. **贪心替换**：优先替换为幸运字母，若原字符已是幸运字母则选择字典序最小的替代字母。
4. **保留大小写**：最终结果需与原字符串的大小写模式一致。

#### 关键难点
- **子串匹配**：需处理不区分大小写的多模式匹配。
- **替换策略**：既要最大化幸运字母数量，又要保证字典序最小。
- **大小写保留**：替换后的字符需与原字符的大小写一致。

#### 最优思路提炼
1. 预处理所有字符串为小写便于比较。
2. 使用布尔数组标记所有需要替换的位置。
3. 遍历每个字符，若被标记则替换：
   - 原字符与幸运字母相同 → 替换为 `a`（若幸运字母为 `a` 则换 `b`）。
   - 否则直接替换为幸运字母。
4. 输出时恢复原字符串的大小写格式。

---

### 精选题解

#### 题解1（柳易辰，★★★★★）
**亮点**  
- 逻辑清晰，步骤分解明确。
- 代码简洁，直接使用 `substr` 暴力匹配。
- 正确处理了幸运字母与原字符冲突时的字典序问题。

**核心代码**  
```cpp
// 标记需要替换的位置
vector<bool> mark(w.length());
for (auto& forbidden : forbidden_list) {
    int len = forbidden.length();
    for (int i = 0; i <= w.length() - len; ++i) {
        if (lower(w).substr(i, len) == forbidden) {
            fill(mark.begin() + i, mark.begin() + i + len, true);
        }
    }
}

// 替换逻辑
string result;
for (int i = 0; i < w.length(); ++i) {
    if (mark[i]) {
        char original = tolower(w[i]);
        if (original == lucky_char) {
            result += (lucky_char == 'a') ? 'b' : 'a';
        } else {
            result += lucky_char;
        }
        // 恢复大小写
        if (isupper(w[i])) result.back() = toupper(result.back());
    } else {
        result += w[i];
    }
}
```

#### 题解2（alan1118，★★★★☆）
**亮点**  
- 独立处理大小写转换函数。
- 使用二维循环标记覆盖区间，逻辑严谨。

**代码片段**  
```cpp
void tolow(string& c) {
    for (char& ch : c) ch = tolower(ch);
}

// 标记覆盖区间
vector<bool> covered(w.size(), false);
for (auto& s : forbidden) {
    for (int pos = 0; pos + s.size() <= w.size(); ++pos) {
        if (tolower(w.substr(pos, s.size())) == s) {
            fill(covered.begin() + pos, covered.begin() + pos + s.size(), true);
        }
    }
}
```

---

### 拓展与心得
**同类问题**  
- 多模式匹配优化（如 KMP、AC 自动机）。
- 字典序最优策略在贪心算法中的通用应用。

**推荐题目**  
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)（字符串匹配）
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)（字符统计与格式化输出）
3. [CF1120A Diana and Liana](https://codeforces.com/problemset/problem/1120/A)（复杂替换逻辑）

**心得总结**  
- 调试时要特别注意大小写转换和还原的边界情况。
- 当原字符与幸运字母相同时，必须选择次小字母以同时满足次数最多和字典序最小的双重要求。

---
处理用时：63.55秒