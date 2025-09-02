# 题目信息

# Check the string

## 题目描述

A has a string consisting of some number of lowercase English letters 'a'. He gives it to his friend B who appends some number of letters 'b' to the end of this string. Since both A and B like the characters 'a' and 'b', they have made sure that at this point, at least one 'a' and one 'b' exist in the string.

B now gives this string to C and he appends some number of letters 'c' to the end of the string. However, since C is a good friend of A and B, the number of letters 'c' he appends is equal to the number of 'a' or to the number of 'b' in the string. It is also possible that the number of letters 'c' equals both to the number of letters 'a' and to the number of letters 'b' at the same time.

You have a string in your hands, and you want to check if it is possible to obtain the string in this way or not. If it is possible to obtain the string, print "YES", otherwise print "NO" (without the quotes).

## 说明/提示

Consider first example: the number of 'c' is equal to the number of 'a'.

Consider second example: although the number of 'c' is equal to the number of the 'b', the order is not correct.

Consider third example: the number of 'c' is equal to the number of 'b'.

## 样例 #1

### 输入

```
aaabccc
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
bbacc
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
aabc
```

### 输出

```
YES
```

# AI分析结果

### 题目翻译

**题目描述**

A有一个由若干小写英文字母'a'组成的字符串。他把它给了他的朋友B，B在字符串的末尾添加了一些字母'b'。由于A和B都喜欢字母'a'和'b'，他们确保此时字符串中至少有一个'a'和一个'b'。

B现在把这个字符串给了C，C在字符串的末尾添加了一些字母'c'。然而，由于C是A和B的好朋友，他添加的字母'c'的数量等于字符串中'a'的数量或'b'的数量。也有可能字母'c'的数量同时等于字母'a'和'b'的数量。

你手中有一个字符串，你想检查这个字符串是否符合上述要求。如果符合，输出"YES"，否则输出"NO"（不带引号）。

**说明/提示**

考虑第一个例子：'c'的数量等于'a'的数量。

考虑第二个例子：尽管'c'的数量等于'b'的数量，但顺序不正确。

考虑第三个例子：'c'的数量等于'b'的数量。

**样例 #1**

### 输入

```
aaabccc
```

### 输出

```
YES
```

**样例 #2**

### 输入

```
bbacc
```

### 输出

```
NO
```

**样例 #3**

### 输入

```
aabc
```

### 输出

```
YES
```

### 算法分类
字符串、模拟

### 题解分析与结论

#### 题解1：_tommysun_
**星级：4**
**关键亮点：**
- 通过排序判断字符串顺序是否正确，简洁高效。
- 使用计数器统计字符数量，逻辑清晰。
- 代码结构简洁，易于理解。

**核心代码：**
```cpp
string t = s;
sort(t.begin(), t.end());
if (t != s) {
    cout << "NO";
    return 0;
}
for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'a') cnta++;
    else if (s[i] == 'b') cntb++;
    else if (s[i] == 'c') cntc++;
}
if (cnta == 0 || cntb == 0) {
    cout << "NO";
    return 0;
}
if (cntc != cnta && cntc != cntb) {
    cout << "NO";
    return 0;
}
cout << "YES";
```

#### 题解2：时律
**星级：4**
**关键亮点：**
- 使用`find`和`rfind`函数判断字符顺序，避免多余循环。
- 通过宏定义简化代码，提高可读性。
- 逻辑严谨，考虑了多种边界情况。

**核心代码：**
```cpp
if (A > B || A > C || B > C || A == -1 || B == -1 || C == -1) {
    cout << "NO";
    return 0;
}
if (s.rfind('a') + 1 != B || s.rfind('b') + 1 != C) {
    cout << "NO";
    return 0;
}
for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'a') a++;
    else if (s[i] == 'b') b++;
    else c++;
}
if (a == c || b == c) {
    cout << "YES";
} else {
    cout << "NO";
}
```

#### 题解3：Suuon_Kanderu
**星级：3**
**关键亮点：**
- 使用栈结构判断字符顺序，思路新颖。
- 通过栈的`empty`和`top`方法避免多余循环。
- 代码结构稍显复杂，但逻辑清晰。

**核心代码：**
```cpp
if (s == 'a') {
    if (!a.empty() && a.top() != 'a') {
        cout << "NO";
        return 0;
    }
    a.push(s), a_cnt++;
}
if (s == 'b') {
    if (a.empty() || a.top() == 'c') {
        cout << "NO";
        return 0;
    }
    a.push(s), b_cnt++;
}
if (s == 'c') {
    if (a.empty() || a.top() == 'a') {
        cout << "NO";
        return 0;
    }
    a.push(s), c_cnt++;
}
if (c_cnt != a_cnt && c_cnt != b_cnt || a == 0 || b == 0) {
    cout << "NO";
    return 0;
}
cout << "YES";
```

### 最优关键思路
1. **排序法**：通过排序字符串并与原字符串比较，快速判断字符顺序是否正确。
2. **计数器法**：使用计数器统计字符数量，判断是否符合题目要求。
3. **栈结构**：利用栈的先进后出特性，判断字符顺序是否正确。

### 可拓展之处
- 类似题目可以扩展到更多字符或更复杂的顺序要求。
- 可以使用其他数据结构如队列或双端队列来处理类似问题。

### 推荐题目
1. [P1042 字符统计](https://www.luogu.com.cn/problem/P1042)
2. [P1055 字符串排序](https://www.luogu.com.cn/problem/P1055)
3. [P1061 字符串匹配](https://www.luogu.com.cn/problem/P1061)

---
处理用时：32.07秒