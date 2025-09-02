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



### 唯一算法分类  
**字符串处理（KMP算法 + 哈希递推优化）**

---

### 综合分析与结论  
**题目核心**：求字符串的最长前缀和后缀，使其循环同构且不重叠。  
**关键难点**：如何高效计算中间部分的最长不重叠 border。  
**解决方案**：  
1. **KMP预处理**原串的 border，快速判断前缀是否与后缀相同。  
2. **递推优化**：从大到小枚举前缀长度，维护中间部分的最长 border 长度。利用 `f[i] ≤ f[i+1] + 2` 的递推性质，逐步调整边界。  
3. **哈希快速比较**：通过双哈希或模数哈希判断字符串相等，避免自然溢出被卡。  

**可视化设计思路**：  
- **动画流程**：  
  - 展示字符串切割为前缀 `A`、中间部分 `B`、后缀 `A` 的过程。  
  - 高亮当前枚举的 `i` 和 `f[i]`，动态调整 `f[i]` 的长度（绿色表示有效，红色表示不匹配需缩短）。  
- **复古像素风格**：  
  - 字符串以 8-bit 像素块表示，移动时带有音效。  
  - 每次调整 `f[i]` 时播放“滴答”音效，找到最大值时触发通关音效。  
- **交互控制**：支持单步执行观察递推过程，速度可调。

---

### 题解清单 (≥4星)  
1. **Alex_Wei（5星）**  
   - **亮点**：结合 KMP 预处理与哈希递推，代码结构清晰，注释详细。  
   - **关键代码**：递推 `f[i]` 时从 `i+1` 继承并调整。  
   - **心得**：通过势能分析证明复杂度为线性。  

2. **maruize（4星）**  
   - **亮点**：图示递推关系，简化问题为中间部分 border 的递推。  
   - **关键代码**：`f[i] = min(f[i+1]+2, ...)` 的边界处理。  

3. **Leasier（4星）**  
   - **亮点**：双哈希避免冲突，代码简洁高效。  
   - **关键代码**：`get_hash` 函数实现快速比较。  

---

### 最优思路与代码实现  
**核心逻辑**：  
1. **KMP预处理**原串的 border，用于快速判断前后缀相同。  
2. **倒序递推**：从 `n/2` 开始枚举 `i`，维护 `f[i]` 为中间部分的最长 border。  
3. **哈希验证**：检查 `A` 和 `B` 的循环同构关系。  

```cpp
// 核心代码片段（Alex_Wei 题解）
for (int i = n / 2; i; i--) {
    f[i] = f[i + 1] + 2; // 递推初始化
    while (f[i]) {
        if ((i + f[i]) * 2 > n) f[i]--; // 边界检查
        else if (hash_check_failed) f[i]--; // 哈希验证
        else break;
    }
    if (is_border(i)) ans = max(ans, i + f[i]);
}
```

**完整代码**（简化版）：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
int n, ans, f[N], nxt[N], hsh[N], pw[N];
char s[N];

int calc(int l, int r) { 
    return (hsh[r] - 1ll * hsh[l-1] * pw[r-l+1] % mod + mod) % mod; 
}

int main() {
    scanf("%d%s", &n, s + 1);
    // KMP预处理
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[j+1] != s[i]) j = nxt[j];
        nxt[i] = j += (s[j+1] == s[i]);
    }
    // 哈希预处理
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = 1ll * pw[i-1] * 131 % mod;
        hsh[i] = (1ll * hsh[i-1] * 131 + s[i]) % mod;
    }
    // 递推 f[i]
    for (int i = n/2; i; i--) {
        f[i] = f[i+1] + 2;
        while (f[i] && (i + f[i]) * 2 > n) f[i]--;
        while (f[i] && calc(i+1, i+f[i]) != calc(n-i-f[i]+1, n-i)) f[i]--;
        if (calc(1, i) == calc(n-i+1, n)) ans = max(ans, i + f[i]);
    }
    cout << ans << "\n";
}
```

---

### 相似题目推荐  
1. **P4555 [国家集训队]最长双回文串**  
   - 类似的双回文结构，需结合 Manacher 算法。  
2. **CF961F k-substrings**  
   - 利用递推优化计算每个位置的最长 border。  
3. **P3435 [POI2006] OKR-Periods of Words**  
   - 基于 KMP 的周期分析，递推思想相似。  

---

### 可视化与复古游戏化设计  
**Canvas 动画方案**：  
1. **字符串切割展示**：  
   - 前缀 `A`（蓝色）、中间 `B`（黄色）、后缀 `A`（蓝色）分块显示。  
2. **递推过程**：  
   - 高亮当前 `i`（红色边框），动态调整 `f[i]` 长度（绿色扩展，红色收缩）。  
3. **音效设计**：  
   - 调整 `f[i]` 时播放“点击”音效，找到答案时播放 8-bit 胜利音乐。  

**复古风格实现**：  
- **颜色方案**：16色调色板，像素字体。  
- **交互**：方向键控制递推速度，空格暂停/继续。  

---

**总结**：通过递推优化和哈希快速比较，将看似复杂的循环同构问题转化为线性复杂度的高效解法。结合 KMP 预处理和递推性质，是处理此类字符串问题的经典思路。

---
处理用时：83.32秒