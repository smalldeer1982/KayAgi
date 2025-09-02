# 题目信息

# camel_case

## 题目描述

在编程中，我们常用到两种字符串格式：「驼峰命名法」和「下划线分隔」。它们的定义如下：

- **单词**：一个以小写字母开头的字符串，由小写字母和数字构成。
- **驼峰命名法字符串**：由一个或多个单词连接而成，除了第一个单词外，其他单词首字母需大写。
- **下划线分隔字符串**：由一个或多个单词通过下划线连接形成。

这些字符串可能会在头尾被加上多余的下划线。

给定一个字符串，若它符合驼峰命名法或下划线分隔格式，要求将其互相转换，否则直接输出原字符串。同时，若某个字符串既符合驼峰命名法又符合下划线分隔，保证无论哪种解释方式，转换结果都是一致的。

输入格式如下：
> $ c_1c_2…c_N $

- 输入为一行字符串。
- 字符串长度 $ N $ 满足 $ 1 \leq N \leq 50 $。
- 字符 $ c_i $ 可以是大写字母（`A` 到 `Z`）、小写字母（`a` 到 `z`）、数字（`0` 到 `9`）或下划线（`_`）。

请将输入的字符串进行转换，结果以一行形式输出，并保证以换行符结尾。

## 说明/提示

字符串长度 $ N $ 满足 $ 1 \leq N \leq 50 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
lower_camel_case```

### 输出

```
lowerCamelCase```

## 样例 #2

### 输入

```
_snakeCase_```

### 输出

```
_snake_case_```

## 样例 #3

### 输入

```
KLab```

### 输出

```
KLab```

## 样例 #4

### 输入

```
_```

### 输出

```
_```

## 样例 #5

### 输入

```
a_bc_9a_b```

### 输出

```
a_bc_9a_b```

# AI分析结果



### 题目内容
# camel_case

## 题目描述

在编程中，我们常用到两种字符串格式：「驼峰命名法」和「下划线分隔」。它们的定义如下：

- **单词**：一个以小写字母开头的字符串，由小写字母和数字构成。
- **驼峰命名法字符串**：由一个或多个单词连接而成，除了第一个单词外，其他单词首字母需大写。
- **下划线分隔字符串**：由一个或多个单词通过下划线连接形成。

这些字符串可能会在头尾被加上多余的下划线。

给定一个字符串，若它符合驼峰命名法或下划线分隔格式，要求将其互相转换，否则直接输出原字符串。同时，若某个字符串既符合驼峰命名法又符合下划线分隔，保证无论哪种解释方式，转换结果都是一致的。

输入格式如下：
> $ c_1c_2…c_N $

- 输入为一行字符串。
- 字符串长度 $ N $ 满足 $ 1 \leq N \leq 50 $。
- 字符 $ c_i $ 可以是大写字母（`A` 到 `Z`）、小写字母（`a` 到 `z`）、数字（`0` 到 `9`）或下划线（`_`）。

请将输入的字符串进行转换，结果以一行形式输出，并保证以换行符结尾。

---

### 算法分类
**字符串**

---

### 题解分析与结论
题目要求判断输入字符串是否符合驼峰式或下划线式格式，并进行转换。关键点在于如何正确识别格式并处理头尾下划线。

#### 解题思路
1. **预处理头尾下划线**：提取中间有效部分。
2. **正则表达式验证格式**：
   - 驼峰式：中间部分首字符小写，无下划线，后续大写字母作为单词分割点。
   - 下划线式：中间部分由有效单词通过下划线连接，无连续下划线。
3. **格式转换**：
   - 驼峰式转下划线式：在大写字母前插入下划线并转小写。
   - 下划线式转驼峰式：下划线后单词首字母转大写，去除下划线。

#### 代码核心实现
```cpp
#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    
    int head = 0, tail = 0;
    while (head < s.size() && s[head] == '_') head++;
    while (tail < s.size() && s[s.size() - 1 - tail] == '_') tail++;
    string mid = (s.size() - head - tail > 0) ? s.substr(head, s.size() - head - tail) : "";
    
    bool isCamel = false, isSnake = false;
    if (!mid.empty()) {
        regex camelRegex("^[a-z][a-z0-9]*([A-Z][a-z0-9]*)*$");
        isCamel = regex_match(mid, camelRegex);
        
        regex snakeRegex("^([a-z][a-z0-9]*)(_[a-z][a-z0-9]*)*$");
        isSnake = regex_match(mid, snakeRegex);
    }
    
    string res;
    if (isCamel || isSnake) {
        string converted;
        if (isCamel) {
            for (int i = 0; i < mid.size(); ++i) {
                if (i > 0 && isupper(mid[i])) {
                    converted += '_';
                    converted += tolower(mid[i]);
                } else {
                    converted += mid[i];
                }
            }
        } else {
            size_t pos = 0;
            bool first = true;
            while (pos < mid.size()) {
                size_t next = mid.find('_', pos);
                if (next == string::npos) {
                    string word = mid.substr(pos);
                    if (!word.empty()) {
                        if (first) converted += word;
                        else converted += (char)toupper(word[0]) + word.substr(1);
                    }
                    break;
                } else {
                    string word = mid.substr(pos, next - pos);
                    if (!word.empty()) {
                        if (first) converted += word;
                        else converted += (char)toupper(word[0]) + word.substr(1);
                        first = false;
                    }
                    pos = next + 1;
                }
            }
        }
        res = string(head, '_') + converted + string(tail, '_');
    } else {
        res = s;
    }
    
    cout << res << endl;
    return 0;
}
```

---

### 关键思路与技巧
1. **正则表达式匹配**：快速验证字符串格式。
2. **头尾下划线处理**：通过截取中间有效部分简化判断。
3. **分情况转换**：根据格式类型选择不同的转换逻辑，确保边界条件正确处理。

---

### 相似题目推荐
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308) - 字符串处理与模式匹配。
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598) - 字符串分析与格式化输出。
3. [P1765 手机](https://www.luogu.com.cn/problem/P1765) - 字符串转换与按键映射。

---
处理用时：383.06秒