# 题目信息

# [入门赛 #14] 扶苏和串 (Hard Version)

## 题目背景

众所周知，每个月入门赛的字符串题都是扶苏来枚举 idea 出出来的。

## 题目描述

给定一个 01 字符串 $s$，你可以任选 $s$ 的一个非空子串，把这个子串在 $s$ 中**翻转**一次。

问你能得到字典序最小的字符串是什么？

形式化的，你可以选择一个区间 $[l, r]$ 满足 $1 \leq l \leq r \leq |s|$，构造一个串 $t$ 满足：

$$t_i = \begin{cases}s_i, &i < l \text{ 或 } i > r \\ s_{r - (i - l)}, & l \leq i \leq r\end{cases}$$

最小化字符串 $t$ 的字典序。

## 说明/提示

### 样例 1 解释

$s = \texttt{\underline{10}1}$，翻转下划线标出的子串，得到 $t = \texttt{011}$

### 样例 2 解释

$s = \texttt{00\underline{10100}}$，翻转下划线标出的子串，得到 $\texttt{0000101}$。

### 数据规模与约定

下面用 $|s|$ 表示输入字符串的长度。

- 对 $100\%$ 的数据，$1 \leq |s| \leq 3000$。$s$ 只含字符 $\texttt{0,1}$。

## 样例 #1

### 输入

```
101```

### 输出

```
011```

## 样例 #2

### 输入

```
0010100```

### 输出

```
0000101```

# AI分析结果



**算法分类：贪心**

---

### 题解综合分析

所有题解均基于同一核心思路：**翻转左端点固定为第一个 '1' 的位置，枚举右端点求最优解**。通过贪心策略将时间复杂度从暴力法的 O(n³) 优化至 O(n²)，并通过数学证明该策略的正确性。

---

### 精选题解 (评分≥4⭐)

#### 1. 作者：I_am_AKed_by_NOI (5⭐)
**关键亮点**：
- 详细数学证明左端点必须为第一个 '1' 的位置，解决其他题解未论证的痛点。
- 代码注释清晰，处理全 '0' 的特殊情况。
- **个人心得**：明确强调结论证明的必要性，避免读者盲目套用。

**核心代码**：
```cpp
int main() {
    cin >> s;
    // 寻找第一个 '1' 的位置
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '1') { l = i; break; }
    }
    // 枚举右端点并翻转比较
    for (int r = l + 1; r < s.length(); r++) {
        string tmp = s;
        reverse(tmp.begin() + l, tmp.begin() + r);
        ans = min(ans, tmp);
    }
    cout << ans;
}
```

#### 2. 作者：一扶苏一 (4⭐)
**关键亮点**：
- 使用反证法证明左端点固定的必要性，逻辑严谨。
- 代码简洁，直接复用 `std::reverse` 和字符串截取。

**核心代码**：
```cpp
int main() {
    std::string s;
    int pos = 0;
    while (s[pos] == '0') ++pos;
    std::string ans = s;
    for (int r = pos + 1; r <= s.size(); ++r) {
        auto mid = s.substr(pos, r - pos);
        std::reverse(mid.begin(), mid.end());
        ans = std::min(ans, s.substr(0, pos) + mid + s.substr(r));
    }
    std::cout << ans;
}
```

---

### 最优关键思路
1. **固定左端点**：左端点必须为第一个 '1' 的位置，确保翻转后尽可能多地将后续的 '0' 带到前缀。
2. **枚举右端点**：遍历所有可能的右端点，翻转区间并比较字典序。
3. **直接比较字符串**：利用 `std::string` 的 `<` 运算符高效比较字典序。

---

### 拓展与同类题
- **同类题套路**：贪心策略结合枚举，常用于字符串最小化问题（如字典序最小、翻转操作最优解）。
- **推荐题目**：
  1. [P2870 [USACO07DEC] Best Cow Line G](https://www.luogu.com.cn/problem/P2870)（贪心+双指针）
  2. [P3404 字符串的修改](https://www.luogu.com.cn/problem/P3404)（动态规划优化翻转）
  3. [P7985 [USACO21DEC] Lazy Letters G](https://www.luogu.com.cn/problem/P7985)（贪心+优先队列）

---
处理用时：51.36秒