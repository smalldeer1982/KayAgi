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



### 算法分类
**字符串处理（哈希 + KMP递推）**

---

### 题解思路与核心难点
#### **核心思路**
1. **循环等价性质**：两个字符串循环等价可表示为 `AB` 和 `BA`。题目要求寻找最长的前缀 `A` 和后缀 `B`，使得 `A` 和 `B` 循环等价。
2. **递推优化**：对于每个可能的 `i`（前缀长度），计算中间部分的最长不重叠 border `f_i`，最终取 `max(i + f_i)`。利用 `f[i] ≤ f[i+1] + 2` 的递推性质，逆序高效计算 `f` 数组。

#### **解决难点**
- **快速比较子串**：通过双哈希预处理，避免自然溢出哈希的碰撞风险。
- **避免重复计算**：利用 `f[i]` 的单调性，每次调整最多减少 `2` 次，总时间复杂度 `O(n)`。

---

### 题解评分（≥4星）
1. **Alex_Wei（★★★★★）**  
   - 思路清晰，完整推导递推关系；双哈希实现严谨，代码可读性高。  
   - 关键代码片段：逆序维护 `f[i]`，结合 KMP 预处理原串 border。
2. **Leasier（★★★★）**  
   - 与 Alex_Wei 思路一致，代码简洁，但未显式处理 KMP。  
   - 亮点：直接利用哈希逆推 `f[i]`，适合快速实现。
3. **kczno1（★★★★）**  
   - 双哈希实现，避免哈希碰撞；代码简短高效，包含边界条件处理。  
   - 调试心得：强调取模需 `+ mod % mod` 防止负数。

---

### 最优思路提炼
#### **关键步骤**
1. **预处理哈希**：计算全串哈希值，支持快速子串比较。
2. **逆序递推 `f[i]`**：  
   ```cpp
   for (int i = n / 2; i >= 1; i--) {
       f[i] = f[i + 1] + 2;
       while (f[i] 不合法) f[i]--;
   }
   ```
3. **验证前缀后缀**：对每个 `i`，检查 `s[1..i]` 是否等于 `s[n-i+1..n]`。

#### **技巧总结**
- **双哈希防碰撞**：使用两个不同基数和模数的哈希函数。
- **递推剪枝**：`f[i]` 的调整范围不超过 `2n`，确保线性复杂度。

---

### 同类型题与算法套路
1. **双回文串问题**（如 [P4555](https://www.luogu.com.cn/problem/P4555)）：利用中心扩展递推性质。
2. **KMP 扩展应用**：如 [CF961F](https://www.luogu.com.cn/problem/CF961F) 的 Border 性质分析。
3. **字符串分割优化**：通过递推和哈希快速验证子串。

---

### 推荐相似题目
1. [P4555 最长双回文串](https://www.luogu.com.cn/problem/P4555)  
2. [CF961F k-substrings](https://www.luogu.com.cn/problem/CF961F)  
3. [P3375 KMP模板](https://www.luogu.com.cn/problem/P3375)

---

### 个人心得摘录
- **哈希安全**：自然溢出易被卡，双哈希或大质数模更可靠（见 kczno1 题解）。
- **边界处理**：检查 `i + f[i] ≤ n/2` 时需严格验证子串不重叠（Alex_Wei 的 `while` 循环）。

---

### 可视化算法演示
#### **动画设计**
1. **核心变量高亮**：  
   - 当前 `i` 和 `f[i]` 用红色标记，调整过程用黄色闪烁。  
   - 比较的子串区间用绿色/蓝色框标出。
2. **递推过程分步**：  
   - 初始状态：显示 `f[n/2] = 0`。  
   - 逆序迭代：`i` 从 `n/2` 递减，每次 `f[i]` 初始为 `f[i+1] + 2`，逐步减少至合法值。
3. **哈希比较演示**：  
   - 对比 `s[i+1..i+f]` 和 `s[n-i-f+1..n-i]` 时，显示哈希值计算过程。

#### **复古像素风格**
- **8位像素界面**：  
  - 字符串以网格显示，每个字符为 16x16 像素块。  
  - 递推过程用“贪吃蛇”式移动指针，音效伴随每次 `f[i]` 调整。  
- **音效触发**：  
  - 成功匹配：8-bit 上升音阶。  
  - 哈希碰撞失败：短促“哔”声。  
  - 背景音乐：低循环芯片音乐。

---

### 关键代码实现
#### **双哈希预处理与验证**
```cpp
const int base1 = 131, mod1 = 1e9+7;
const int base2 = 233, mod2 = 1e8+7;
ll h1[N], h2[N], p1[N], p2[N];

void init_hash() {
    p1[0] = p2[0] = 1;
    for (int i = 1; i <= n; i++) {
        p1[i] = p1[i-1] * base1 % mod1;
        p2[i] = p2[i-1] * base2 % mod2;
        h1[i] = (h1[i-1] * base1 + s[i]) % mod1;
        h2[i] = (h2[i-1] * base2 + s[i]) % mod2;
    }
}

bool check(int l1, int r1, int l2, int r2) {
    ll a1 = (h1[r1] - h1[l1-1] * p1[r1-l1+1] % mod1 + mod1) % mod1;
    ll b1 = (h1[r2] - h1[l2-1] * p1[r2-l2+1] % mod1 + mod1) % mod1;
    ll a2 = (h2[r1] - h2[l1-1] * p2[r1-l1+1] % mod2 + mod2) % mod2;
    ll b2 = (h2[r2] - h2[l2-1] * p2[r2-l2+1] % mod2 + mod2) % mod2;
    return a1 == b1 && a2 == b2;
}
```

#### **递推求解 f[i]**
```cpp
for (int i = n/2; i >= 1; i--) {
    f[i] = f[i+1] + 2;
    while (f[i] > 0) {
        if (i + f[i] > n/2) f[i]--;
        else if (!check(i+1, i+f[i], n-i-f[i]+1, n-i)) f[i]--;
        else break;
    }
}
```

---

### 总结
通过结合哈希快速比较和递推优化，算法在 `O(n)` 时间内高效求解最长循环等价前后缀。核心在于逆序利用 `f[i]` 的单调性，避免暴力枚举。

---
处理用时：93.28秒