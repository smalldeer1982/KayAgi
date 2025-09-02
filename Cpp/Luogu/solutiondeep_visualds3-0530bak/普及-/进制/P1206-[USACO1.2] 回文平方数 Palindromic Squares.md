# 题目信息

# [USACO1.2] 回文平方数 Palindromic Squares

## 题目描述

回文数是指从左向右念和从右向左念都一样的数。如 $12321$ 就是一个典型的回文数。

给定一个用十进制表示的正整数 $B$，输出所有 $[1,300]$ 中，它的平方用 $B$ 进制表示时是回文数的数。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$2 \le B \le 20$

题目翻译来自NOCOW。

USACO Training Section 1.2


## 样例 #1

### 输入

```
10
```

### 输出

```
1 1
2 4
3 9
11 121
22 484
26 676
101 10201
111 12321
121 14641
202 40804
212 44944
264 69696
```

# AI分析结果



# 算法分析：回文平方数 Palindromic Squares

## 算法分类
**进制转换与回文判断**

---

## 题解思路与解决难点

### 核心逻辑
1. **枚举范围**：遍历 1~300 的所有数 i，计算其平方值。
2. **进制转换**：将 i 和 i² 转换为 B 进制字符串。
3. **回文判断**：检查转换后的字符串是否为回文。
4. **输出结果**：若满足条件，按 B 进制输出 i 和 i²。

### 解决难点
- **进制转换的正确性**：正确处理余数 >9 的情况（如 10→A，11→B）。
- **回文判断的效率**：通过双指针法（头尾同时向中间移动）实现 O(n/2) 的时间复杂度。
- **代码可读性**：模块化设计（拆分进制转换、回文判断为独立函数）。

---

## 题解评分（≥4星）

### 1. 作者：buickboy（⭐⭐⭐⭐⭐）
- **亮点**：代码简洁，使用字符串处理，递归转换进制，双指针回文判断。
- **关键代码**：
  ```cpp
  string ten2b(int n, int b) {
      string x, dic = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      while (n) x = dic[n % b] + x, n /= b;
      return x;
  }
  bool hw(string s) {
      for (int i = 0; i < s.size() / 2; ++i)
          if (s[i] != s[s.size() - 1 - i]) return false;
      return true;
  }
  ```

### 2. 作者：hsfzLZH1（⭐⭐⭐⭐）
- **亮点**：面向对象设计，结构体封装转换逻辑，构造函数处理进制转换。
- **关键代码**：
  ```cpp
  struct node {
      int l, a[20];
      node(int x) { for (l = 0; x; l++) a[l] = x % b, x /= b; }
      bool tf() { 
          for (int i = 0; i < l; i++)
              if (a[i] != a[l - i - 1]) return false;
          return true;
      }
  };
  ```

### 3. 作者：Violette（⭐⭐⭐⭐）
- **亮点**：数组存储余数，分离转换、判断、输出逻辑，代码模块化。
- **关键代码**：
  ```cpp
  void jz(int a, int b) {
      int r = 0;
      while (a) s[++r] = a % b, a /= b;
      s[0] = r; // s[0] 存储长度
  }
  bool change() {
      for (int i = 1; i <= s[0]; i++)
          if (s[i] != s[s[0] + 1 - i]) return false;
      return true;
  }
  ```

---

## 最优思路提炼
- **进制转换**：通过短除法取余，逆序拼接字符串，用预定义字符表（如 `0123456789ABCDEFGHIJ`）快速映射。
- **回文判断**：双指针法比较首尾对称位置，提前终止不匹配情况。
- **输出优化**：转换后的字符串直接输出，避免额外存储。

---

## 类似题目推荐
1. **P1017 进制转换**（负数进制转换）
2. **P1217 回文质数**（双重条件判断）
3. **P1022 计算器的改良**（表达式解析与进制处理）

---

## 可视化算法演示

### 动画设计
1. **进制转换过程**：
   - **网格展示**：将十进制数逐步分解为 B 进制余数，动态显示除法过程。
   - **颜色标记**：当前操作的余数用黄色高亮，已计算部分用蓝色填充。
   
2. **回文判断**：
   - **指针移动**：红色和绿色箭头从两端向中间移动，匹配时显示绿色，否则红色闪烁。
   - **音效反馈**：匹配成功播放清脆音效，失败播放低沉音效。

### 复古像素风格
- **8位画风**：数字用 8x8 像素块显示，背景为经典 FC 游戏风格。
- **自动演示**：AI 自动遍历 1~300，速度可调，支持暂停/单步。

---

## 核心代码实现
```cpp
#include <iostream>
#include <string>
using namespace std;

string toBase(int num, int base) {
    const string digits = "0123456789ABCDEFGHIJ";
    string res;
    while (num) {
        res = digits[num % base] + res;
        num /= base;
    }
    return res.empty() ? "0" : res;
}

bool isPalindrome(const string &s) {
    for (int i = 0; i < s.size() / 2; ++i)
        if (s[i] != s[s.size() - 1 - i]) return false;
    return true;
}

int main() {
    int B;
    cin >> B;
    for (int i = 1; i <= 300; ++i) {
        string square = toBase(i * i, B);
        if (isPalindrome(square))
            cout << toBase(i, B) << " " << square << endl;
    }
    return 0;
}
```

---

## 总结
通过模块化设计和高效算法，将复杂问题分解为可管理的子任务。回文判断与进制转换的组合是此类问题的通用解法，适用于多种变体题目。

---
处理用时：90.51秒