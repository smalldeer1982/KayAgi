# 题目信息

# Extract Numbers

## 题目描述

You are given string $ s $ . Let's call word any largest sequence of consecutive symbols without symbols ',' (comma) and ';' (semicolon). For example, there are four words in string "aba,123;1a;0": "aba", "123", "1a", "0". A word can be empty: for example, the string $ s $ =";;" contains three empty words separated by ';'.

You should find all words in the given string that are nonnegative INTEGER numbers without leading zeroes and build by them new string $ a $ . String $ a $ should contain all words that are numbers separating them by ',' (the order of numbers should remain the same as in the string $ s $ ). By all other words you should build string $ b $ in the same way (the order of numbers should remain the same as in the string $ s $ ).

Here strings "101", "0" are INTEGER numbers, but "01" and "1.0" are not.

For example, for the string aba,123;1a;0 the string $ a $ would be equal to "123,0" and string $ b $ would be equal to "aba,1a".

## 说明/提示

In the second example the string $ s $ contains five words: "1", "", "01", "a0", "".

## 样例 #1

### 输入

```
aba,123;1a;0
```

### 输出

```
"123,0"
"aba,1a"
```

## 样例 #2

### 输入

```
1;;01,a0,
```

### 输出

```
"1"
",01,a0,"
```

## 样例 #3

### 输入

```
1
```

### 输出

```
"1"
-
```

## 样例 #4

### 输入

```
a
```

### 输出

```
-
"a"
```

# AI分析结果



# 提取数字

## 题目描述
给定字符串 $s$，我们将由 ',' 或 ';' 分隔的最大连续符号序列称为"单词"。例如字符串"aba,123;1a;0"包含四个单词："aba"、"123"、"1a"、"0"。空字符串也被视为单词（如字符串";;"包含三个空单词）。

需要将所有符合非负整数格式（无前导零，允许单个0）的单词收集到字符串 $a$ 中，其余单词收集到字符串 $b$ 中，保持原有顺序并用逗号分隔。

## 分类标签
模拟

## 题目分析与题解对比
本题核心在于正确分割字符串并验证数字格式。各题解普遍采用以下步骤：
1. 追加分隔符简化边界处理
2. 遍历字符分割单词
3. 验证数字规则（全数字字符、无前导零）
4. 分类存储并处理输出格式

关键差异点：
1. 数据结构选择：数组存储（liuchishahuang）vs 字符串拼接（Jerrywang09）
2. 空字符处理：部分题解在连续分隔符场景下可能产生多余逗号
3. 输出优化：提前拼接逗号后删除末尾符号（Jerrywang09）vs 条件判断插入符号（liuchishahuang）

## 精选题解（评分≥4星）

### 题解一（Jerrywang09）⭐⭐⭐⭐
**亮点**：
- 使用双字符串实时拼接结果，减少存储空间
- 通过末尾删除优化输出格式
- 函数封装数字验证逻辑

**核心代码**：
```cpp
bool isNumber(string s) {
    if(s == "0") return true;
    if(s[0] == '0') return false;
    for(char c : s)
        if(!isdigit(c)) return false;
    return true;
}

int main() {
    string s, ans1, ans2, t;
    s += ';'; // 追加分隔符处理末尾
    for(char c : s) {
        if(c == ',' || c == ';') {
            if(t.empty()) ans2 += ',';
            else if(isNumber(t)) ans1 += t + ',';
            else ans2 += t + ',';
            t.clear();
        } else t += c;
    }
    // 处理输出...
}
```

### 题解二（JerryMao）⭐⭐⭐⭐
**亮点**：
- 使用vector存储单词，逻辑清晰
- 独立函数验证数字格式
- 严格按题目要求处理空字符串

**核心代码**：
```cpp
vector<string> splitWords(string s) {
    vector<string> res;
    s += ';';
    string tmp;
    for(char c : s) {
        if(c == ',' || c == ';') {
            res.push_back(tmp);
            tmp.clear();
        } else tmp += c;
    }
    return res;
}

void output(vector<string> vec) {
    if(vec.empty()) cout << "-";
    else cout << "\"" << join(vec, ",") << "\"";
}
```

## 关键思路总结
1. **边界处理技巧**：在原字符串末尾追加分隔符，统一处理最后一个单词
2. **数字验证逻辑**：
   - 空字符串直接判为非数字
   - 单零字符直接通过验证
   - 首字符零且长度>1直接淘汰
   - 全数字字符检查
3. **输出优化**：使用逗号拼接所有元素后删除末尾逗号，避免条件判断

## 同类题目推荐
1. P1308 [统计单词数] - 字符串分割与模式匹配
2. P1598 [垂直柱状图] - 字符统计与格式化输出
3. P3741 [honoka的键盘] - 特殊字符处理与字符串操作

## 调试经验摘录
1. **空字符陷阱**：多个题解作者提到空字符串需要单独处理，特别是在连续分隔符场景下
2. **前导零判断**：需注意"0"是合法数字，而"01"不合法
3. **输出引号转义**：部分题解使用(char)34直接输出引号，提高可读性

---
处理用时：433.11秒