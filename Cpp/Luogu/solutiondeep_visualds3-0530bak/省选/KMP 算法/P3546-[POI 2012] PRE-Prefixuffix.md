# 题目信息

# [POI 2012] PRE-Prefixuffix

## 题目描述

We consider strings consisting of lowercase letters of the English alphabet in this problem.

An initial fragment of a given string is called its prefix.

A final (terminal) fragment of a given string is called its suffix.

In particular, the empty string is both a prefix and a suffix of any string.

Two strings are cyclically equivalent if one of them can be obtained from another by    moving its certain suffix from the end of the string to its beginning.

For example, the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.1.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.2.png) are cyclically equivalent, whereas the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.3.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.4.png) are not.

In particular, every string is cyclically equivalent to itself.

A string ![](http://main.edu.pl/images/OI19/pre-en-tex.5.png) consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.6.png) letters is given.

We are looking for its prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.7.png) and suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.8.png) of equal length such that:

![](http://main.edu.pl/images/OI19/pre-en-tex.9.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.10.png) are cyclically equivalent,                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.11.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.12.png) does not exceed ![](http://main.edu.pl/images/OI19/pre-en-tex.13.png)        (i.e., the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.14.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.15.png) do not overlap in ![](http://main.edu.pl/images/OI19/pre-en-tex.16.png)), and                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.17.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.18.png) is maximized.

对于两个串 $S_1, S_2$，如果能够将 $S_1$ 的一个后缀移动到开头后变成 $S_2$，就称 $S_1$ 和 $S_2$ 循环相同。例如串 ababba 和串 abbaab 是循环相同的。

给出一个长度为 $n$ 的串 $S$，求满足下面条件的最大的 $L(L\leq \frac n 2)$：$S$ 的 $L$ 前缀和 $S$ 的 $L$ 后缀是循环相同的。

## 说明/提示

数据范围：

- 对于 $30\%$ 的数据，保证 $n\le 500$；
- 对于 $50\%$ 的数据，保证 $n\le 5000$；
- 对于 $100\%$ 数据，保证 $1\le n\le 10^6$。

## 样例 #1

### 输入

```
15
ababbabababbaab```

### 输出

```
6```

# AI分析结果



**唯一算法分类**：字符串哈希 + 贪心递推

---

### **题解思路与难点分析**

#### **核心思路**
题目要求找到最长的前缀和后缀，使得它们循环等价且不重叠。循环等价的条件是两串可拆分为 `AB` 和 `BA` 形式。关键在于快速判断子串是否相等，并递推中间部分的最长不重叠 Border。

1. **Border 性质**：若前缀 `A` 和后缀 `A` 相等，中间部分 `S[i+1..n-i]` 的最长 Border `B` 决定了答案 `L = |A| + |B|`。
2. **递推优化**：从大到小枚举 `i`，维护中间部分的最长 Border 长度 `f[i]`。根据 `f[i+1]` 推导 `f[i]`，最多调整 2 次，保证总时间复杂度为 `O(n)`。
3. **双哈希判断**：使用双哈希避免自然溢出冲突，快速比较子串是否相等。

#### **解决难点**
- **快速求 Border**：中间部分的 Border 长度递推依赖 `f[i+1] + 2`，需逐步调整确保合法。
- **不重叠条件**：每次调整 `f[i]` 时需满足 `2*f[i] ≤ len(S[i+1..n-i])`。
- **哈希实现**：预处理前缀哈希，支持 `O(1)` 比较子串。

---

### **题解评分（≥4星）**
1. **Alex_Wei（5星）**  
   - 思路清晰，递推关系明确，双哈希避免冲突。
   - 代码结构简洁，预处理 KMP 和哈希，高效处理边界。
2. **kczno1（4星）**  
   - 类似递推思路，代码简短，但未预处理 KMP，直接枚举所有可能的 `i`。
3. **MikukuOvO（4星）**  
   - 明确递推关系，代码可读性高，但哈希仅用单模数，存在风险。

---

### **最优思路提炼**
- **递推维护 Border**：逆序枚举 `i`，利用 `f[i] ≤ f[i+1] + 2` 快速调整。
- **双哈希防冲突**：采用双模数哈希确保字符串比较的准确性。
- **KMP 预处理原串 Border**：快速筛选可能的 `i` 值，减少无效计算。

---

### **同类型题与算法套路**
- **循环等价问题**：通常转化为 `AB` 和 `BA` 拆分，结合哈希/KMP 快速判断。
- **Border 递推**：利用相邻状态的关系优化时间复杂度。
- **相关题目**：  
  1. [CF961F](https://codeforces.com/problemset/problem/961/F)（Border 递推）  
  2. [P4555 最长双回文串](https://www.luogu.com.cn/problem/P4555)（回文扩展）  
  3. [P5829 失配树](https://www.luogu.com.cn/problem/P5829)（KMP Border 树）

---

### **个人心得摘录**
- **调试教训**：自然溢出哈希容易被卡，需用双模数；边界条件如 `i + f[i] ≤ n/2` 需仔细处理。
- **顿悟点**：递推优化时，`f[i]` 的调整总和为 `O(n)`，类似摊还分析。

---

### **可视化与算法演示**
**动画设计**：
1. **像素风格界面**：  
   - 使用 8 位像素字体显示字符串 `S`，前缀 `A` 和后缀 `A` 用绿色高亮，中间部分用蓝色。
   - 当前枚举的 `i` 用红色箭头标记，递推 `f[i]` 时动态显示调整过程。
2. **关键步骤高亮**：  
   - 比较子串时，前后 `B` 部分闪烁黄色，哈希值显示在侧边栏。
   - 调整 `f[i]` 时，显示 `p` 值递减并实时验证。
3. **音效与交互**：  
   - 哈希匹配成功播放“叮”声，失败则“哔”声。
   - 用户可拖拽进度条观察不同 `i` 的递推过程。

**核心代码片段**：
```cpp
// 预处理双哈希
h1.init(29, 1e9+7); h2.init(37, 1e9+9);
for (int i = n/2; i >= 1; i--) {
    f[i] = min(f[i+1] + 2, (n - 2*i)/2);
    while (f[i] && !check(i+1, i+f[i], n-i-f[i]+1, n-i)) f[i]--;
}
int ans = 0;
for (int i = 1; i <= n/2; i++) {
    if (check(1, i, n-i+1, n)) ans = max(ans, i + f[i]);
}
```

---

### **复古游戏化实现**
- **Canvas 绘制**：字符串以 8x8 像素块显示，不同部分用颜色区分。
- **自动演示模式**：AI 按 `i` 从大到小递推，实时显示 `f[i]` 调整，背景音乐为芯片风格循环。
- **积分与关卡**：每正确找到一个 `f[i]` 得 10 分，连续正确触发连击倍率。

---
处理用时：95.73秒