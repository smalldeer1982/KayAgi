# 题目信息

# Long Multiplication

## 题目描述

You are given two integers $ x $ and $ y $ of the same length, consisting of digits from $ 1 $ to $ 9 $ .

You can perform the following operation any number of times (possibly zero): swap the $ i $ -th digit in $ x $ and the $ i $ -th digit in $ y $ .

For example, if $ x=73 $ and $ y=31 $ , you can swap the $ 2 $ -nd digits and get $ x=71 $ and $ y=33 $ .

Your task is to maximize the product of $ x $ and $ y $ using the aforementioned operation any number of times. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
73
31
2
5
3516
3982```

### 输出

```
71
33
5
2
3912
3586```

# AI分析结果



# Long Multiplication

## 题目描述

给定两个长度相同的整数 $x$ 和 $y$，均由 $1$ 到 $9$ 的数字组成。你可以进行任意次数的操作：交换 $x$ 的第 $i$ 位与 $y$ 的第 $i$ 位。目标是通过这些操作使得 $x \times y$ 的乘积最大化。若有多个解，输出任意一种。

## 样例 #1

### 输入
```
3
73
31
2
5
3516
3982
```

### 输出
```
71
33
5
2
3912
3586
```

---

### 题解综合分析

#### 核心思路
所有题解均基于数学结论：**当两数和固定时，差越小，乘积越大**。通过贪心策略，从高位到低位处理：
1. **确定大小关系**：找到首个不同的数位，确定两数大小关系
2. **调整后续数位**：后续数位将较大的数字分配给较小的数，较小的数字分配给较大的数

#### 关键优化
- 字符串处理代替数值计算（解决大数问题）
- 单次遍历确定交换策略（时间复杂度 O(n)）

---

### 精选题解（评分≥4星）

#### 1. xdogg（⭐⭐⭐⭐⭐）
**亮点**：通过状态变量 `t` 标记大小关系，代码简洁直观
```cpp
int t = 0;
for (int i = 0; i < len; i++) {
    if (a[i] > b[i]) {
        if (t == 0) t = 1;  // 确定x > y
        else if (t == 1) swap(a[i], b[i]); // 后续调整
    } else if (a[i] < b[i]) {
        if (t == 0) t = 2;  // 确定y > x
        else if (t == 2) swap(a[i], b[i]);
    }
}
```

#### 2. FlipWind（⭐⭐⭐⭐）
**亮点**：通过位差标记优化比较逻辑
```cpp
for (pos = 0; pos < sz; pos++) {
    if (a[pos] != b[pos]) break;  // 寻找首个不同位
}
bool flag = (a[pos] > b[pos]);  // 确定大小关系
for (; pos < sz; pos++) {  // 后续调整
    if (flag ? (a[pos] > b[pos]) : (b[pos] > a[pos]))
        swap(a[pos], b[pos]);
}
```

#### 3. Expert_Dream（⭐⭐⭐⭐）
**亮点**：动态维护字符串比较状态
```cpp
bool flag = false;
for (int i = 0; i < n; ++i) {
    if (!flag) {
        if (s[i] < t[i]) swap(s[i], t[i]);
        if (s[i] != t[i]) flag = true;  // 确定大小关系
    } else if (s[i] > t[i]) {  // 后续调整
        swap(s[i], t[i]);
    }
}
```

---

### 关键技巧总结
1. **数学建模**：将乘积最大化转化为差值最小化问题
2. **贪心策略**：高位优先确定大小关系，低位反向调整
3. **字符串处理**：直接操作字符数组避免数值溢出
4. **状态标记**：使用布尔变量记录首个差异位后的调整方向

---

### 相似题目推荐
1. [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098) - 字符串操作与条件判断
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012) - 贪心排序策略
3. [CF1328C Ternary XOR](https://codeforces.com/problemset/problem/1328/C) - 数位分配问题

---

### 题解心得知乎
- **调试经验**：多位题解指出需注意首位差异位的处理（如案例 `3982` vs `3516`，第三位交换后仍需保持整体大小关系）
- **优化启示**：直接操作字符数组比构造新字符串更高效（如 `resize` vs 动态拼接）
- **思维误区**：有题解最初尝试构造两个新字符串，后发现直接修改原字符串更简洁

---
处理用时：47.09秒