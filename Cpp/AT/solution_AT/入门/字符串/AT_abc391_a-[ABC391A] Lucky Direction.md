# [ABC391A] Lucky Direction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc391/tasks/abc391_a

给定一个表示 $8$ 种方位（北、东、西、南、东北、西北、东南、西南）之一的字符串 $D$。方位与其对应的字符串关系如下：

- 北：`N`
- 东：`E`
- 西：`W`
- 南：`S`
- 东北：`NE`
- 西北：`NW`
- 东南：`SE`
- 西南：`SW`

请输出与 $D$ 所表示方位相反的方向对应的字符串。

## 说明/提示

### 约束条件

- $D$ 是 `N`, `E`, `W`, `S`, `NE`, `NW`, `SE`, `SW` 中的任意一个

### 样例解释 1

请输出表示北方反方向（南方）的字符串 `S`。

### 样例解释 2

请输出表示东南方反方向（西北方）的字符串 `NW`。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
N```

### 输出

```
S```

## 样例 #2

### 输入

```
SE```

### 输出

```
NW```

# 题解

## 作者：FlowerAccepted (赞：3)

## 前言

其实这种题作为签到题还是蛮讨厌的，$\text{QwQ}$。

## 解题思路

注意到，对于位置字符串中的每一个字符，取相反的字符替换原字符即可。

常识告诉我们，南北向对，东西相对。

可以使用 `map` 完成此题。

具体的，声明字典 $M$，令 $a$ 为 `N`、`S`、`E`、`W` 中的任意一个，设 $b$ 与 $a$ 相对，则 `M[a] = b` 即可。

## 代码呈现

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map> // 不用万能头
using namespace std;

map<char, char> m;

int main() {
    m['N'] = 'S';
    m['S'] = 'N';
    m['E'] = 'W';
    m['W'] = 'E'; // 添加
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i ++) {
        s[i] = m[s[i]];
    } // 遍历字符串
    cout << s;
    return 0;
}

```

至此，本题 Accepted。

---

