# 题目信息

# 「TAOI-1」Apollo

## 题目背景

Execution.

这题原来叫 `std::cout << std::fixed << std::setprecision(1) << 6.5 << '\n';`。

[被当事人删掉的图片.jpg]

**【Upd 2023/04/15 21:42】添加了一组 Hack 数据位于 Subtask 2，#13。现在所有赛时的 $\bm{50}$ 分提交理论上均只能获得 $\bm{30}$ 分。**

## 题目描述

给出 $n$ 个十进制小数 $a_1 \dots a_n$。

对于一个 **数** $a$，定义其精度 $f(a)$ 表示最小的非负整数 $k$ 使得 $10^k\times a$ 为整数；对于整数 $a$，定义 $f(a) = 0$。对于两个十进制小数 $a, b$，定义 $g(a, b)$ 为对于所有 **数** $c \in [\min(a,b), \max(a,b)]$ 的 $f(c)$ 的最小值。

对于所有 $1 \leq i \leq n$，你需要求出 $\sum\limits_{j=1}^ng(a_i, a_j)$ 的值并输出。

定义十进制小数是一个含有整数部分和小数部分的数，其小数部分不为 $0$。之所以描述得这么愚蠢是因为保证输入的每个数都有小数点，但是好像无论什么写法都会有人提出不满，真是抱歉了。~~所以还是得看看被当事人删掉的图片。所以我在这里写闲话有人看得到吗。~~

## 说明/提示

### 数据范围

**本题采用捆绑测试。**

令 $\sum\limits_{i=1}^n f(a_i) = t$。

- Subtask 1（15 points）：$a_i \leq 10$，$n \leq 5$，$t \leq 10$。
- Subtask 2（15 points）：$a_i \leq 10$，$n \leq 100$，$t \leq 1000$。
- Subtask 3（20 points）：$n \leq 1722$。
- Subtask 4（15 points）：$a_i \leq 1$。
- Subtask 5（35 points）：无特殊限制。

对于所有数据，$0 \lt a_i \lt 10^9$，$1 \leq n \leq 10^5$，$1 \leq t \leq 3 \times 10^6$，**保证 $\bm{a_i}$ 没有后导 [$\color{black}\bm 0$](https://cdn.luogu.com.cn/upload/image_hosting/pg66fm1z.png)，不保证 $\bm{a_i}$ 互不相同**。

### 样例解释

以 $i = 1$ 为例：

+ $j = 1$：取 $c = 11.4514$，$f(c) = 4$；
+ $j = 2$：取 $c = 11.46$，$f(c) = 2$；
+ $j = 3$：取 $c = 11.2$，$f(c) = 1$；
+ $j = 4$：取 $c = 11.3$，$f(c) = 1$；
+ $j = 5$：取 $c = 11.47$，$f(c) = 2$。

故 $\sum\limits_{j=1}^n g(a_1, a_j) = 4 + 2 + 1 + 1 + 2 = 10$。对于同一个 $j$，上文给出的所有 $c$，都可能有其它的不同的 $c$ 满足 $f(c)$ 同样最小。

## 样例 #1

### 输入

```
5
11.4514
11.4778
11.1338
11.1236
11.4789```

### 输出

```
10
11
9
9
11```

## 样例 #2

### 输入

```
8
1.1145
1.114
1.1145
1.514
1.19198
1.1154
1.114
1.1145```

### 输出

```
24
21
24
10
18
22
21
24```

# AI分析结果



### 综合分析与结论
该题核心在于快速计算两个数的小数部分最长公共前缀长度，并处理整数部分不同的情况。最优解法为字典树实现，通过预处理所有数的小数部分公共前缀关系，实现O(t)时间复杂度的统计。

---

### 精选题解分析

#### 题解1：wloving（★★★★★）
**关键亮点**：
1. 以小数点位置为分界点建立字典树，将小数部分视为字符串处理
2. 通过维护每个节点的访问次数、结束标记、深度信息实现快速统计
3. 创新性地提出"前缀贡献"概念，将问题转化为字典树节点遍历过程
**核心实现**：
```cpp
void insert(string s) {
    int u = 0;
    for (char ch : s) {
        int idx = toNum[ch];
        if (!trie[u].son[idx]) trie[u].son[idx] = ++tot;
        u = trie[u].son[idx];
        trie[u].num++;
        if (ch == '.') dot_pos = current_pos;
        trie[u].dep = current_pos - dot_pos; // 记录小数位数
    }
    trie[u].end++;
}

int findStr(string s) {
    int sum = 0, remain = trie[0].num;
    for (int i = 0; i < s.length(); ++i) {
        int idx = toNum[s[i]];
        u = trie[u].son[idx];
        sum += (remain - trie[u].num) * trie[u].dep;
        remain = trie[u].num;
    }
    sum += (trie[u].num - trie[u].end) * trie[u].dep;
    return sum;
}
```

#### 题解2：gyyyyx（★★★★☆）
**关键亮点**：
1. 分治处理相同整数部分的数，减少字典树规模
2. 动态插入/删除字典树优化内存使用
3. 利用排序预处理实现整数部分分组
**核心技巧**：
```cpp
void Solve(int l, int r) {
    for (int i = l; i <= r; ++i) Insert(y[id[i]], 1);
    for (int i = l; i <= r; ++i) ans[id[i]] += Query(y[id[i]]);
    for (int i = l; i <= r; ++i) Insert(y[id[i]], -1); // 动态释放
}
```

#### 题解3：irris（★★★★☆）
**创新点**：
1. 提出单调栈优化区间最小值计算
2. 将问题转化为LCA深度统计问题
3. 使用压缩字典树结构节省内存
**实现亮点**：
```cpp
struct Trie {
    int node[10], sz, ed; // 压缩存储
    int getNxt(int val) { return node[val] ?: node[val]=++st; }
} f[MAXV];
```

---

### 关键思路总结
1. **字典树构建**：将小数部分视为字符串构建字典树，记录每个节点的访问次数、结束标记、当前小数位数
2. **贡献统计**：遍历时累计分支节点的贡献，公式：sum += (前节点总数 - 当前分支数) * 当前深度
3. **动态分组**：按整数部分分组处理，结合排序优化时间复杂度
4. **后缀处理**：对以当前节点为前缀的更长数字单独处理

---

### 拓展训练推荐
1. [P2580 统计难题](https://www.luogu.com.cn/problem/P2580) - 基础字典树应用
2. [P3879 阅读理解](https://www.luogu.com.cn/problem/P3879) - 字典树+位运算优化
3. [P3294 背单词](https://www.luogu.com.cn/problem/P3294) - 字典树与树形DP结合

---

### 实践心得摘录
1. **边界处理**："注意小数点为10的特殊处理，避免与数字0-9冲突"（N0_1题解）
2. **优化经验**："动态插入删除字典树节点，避免内存超限"（gyyyyx题解）
3. **调试技巧**："通过绘制字典树结构图验证贡献计算公式"（wloving题解附图）
4. **思维误区**："最初认为需要单独处理整数部分，后发现字典树自动处理了整数前缀"（konyakest题解）

---
处理用时：49.24秒