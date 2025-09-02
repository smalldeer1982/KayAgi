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



## 唯一算法分类
**字典树（Trie）**

---

## 综合分析与结论

### 核心算法流程
1. **数据分组**：按整数部分分组，仅处理同组数据（整数部分不同时贡献为0）。
2. **字典树构建**：将小数部分视为字符串构建字典树，每个节点记录：
   - `num`：经过该节点的字符串总数
   - `end`：以该节点结尾的字符串数
   - `dep`：当前位数（小数部分的精度）
3. **贡献计算**：遍历字典树时，统计分叉节点贡献和前缀覆盖贡献：
   - **分叉贡献**：当路径分叉时，未走的分支数量 × 当前位数。
   - **前缀贡献**：遍历结束后，剩余以当前路径为前缀的字符串数量 × 总位数。

### 可视化设计
- **颜色高亮**：遍历路径用红色标记，分叉节点用黄色高亮，贡献计算区域用绿色框展示。
- **动画步骤**：
  1. 输入字符串分解为整数和小数部分。
  2. 展示字典树插入过程（逐个字符生成节点）。
  3. 查询时逐步遍历字典树，动态显示分叉贡献计算。
  4. 最终结果区域展示总和计算过程。
- **像素风格**：用 8-bit 网格绘制字典树，节点用方块表示，分叉时播放经典 FC 音效。

---

## 题解评分（≥4星）

### 1. wloving（5星）
- **亮点**：完整字典树实现，插入与查询逻辑清晰，通过 `num/end/dep` 精准统计贡献。
- **关键代码**：
  ```cpp
  int findStr(string s) {
    int sum = 0, re = trie[0].num;
    int u = 0;
    for (int i = 0; i < len; i++) {
      int ch = toNum[s[i]];
      u = trie[u].son[ch];
      int num = re - trie[u].num + trie[u].end;
      sum += num * trie[u].dep;
      re -= num;
    }
    sum += (trie[u].num - trie[u].end) * trie[u].dep;
    return sum;
  }
  ```

### 2. irris（4星）
- **亮点**：按整数部分分组处理，减少无效计算，代码紧凑。
- **关键逻辑**：
  ```cpp
  for (int l = 0, r = 0; l < N; l = ++r) {
    while (r < N-1 && floor[r+1].first == floor[l].first) ++r;
    for (int i = l; i <= r; ++i) Insert(Q[floor[i].second]);
    for (int i = l; i <= r; ++i) ans[floor[i].second] = calc(...);
  }
  ```

---

## 最优思路提炼
1. **字典树处理前缀**：将小数部分转为字符串，利用字典树高效统计最长公共前缀。
2. **分组优化**：按整数部分分组，避免跨组无效计算。
3. **贡献分阶段计算**：分叉贡献和前缀贡献分开统计，确保复杂度线性。

---

## 相似题目推荐
1. **P2580 于是他错误的点名开始了**（字典树基础应用）
2. **P8306 【模板】字典树**（高效字符串匹配）
3. **P2922 [USACO08DEC] Secret Message G**（前缀覆盖统计）

---

## 核心代码实现

```cpp
// 字典树节点定义
struct Node {
    int son[11] = {0};
    int num = 0, end = 0, dep = 0;
} trie[M];

// 插入逻辑
void insert(string s) {
    int u = 0, dot_pos = -1;
    trie[u].num++;
    for (int i = 0; i < s.size(); i++) {
        int ch = (s[i] == '.' ? 10 : s[i] - '0');
        if (!trie[u].son[ch]) trie[u].son[ch] = ++tot;
        u = trie[u].son[ch];
        trie[u].num++;
        if (ch == 10) dot_pos = i;
        trie[u].dep = (dot_pos != -1) ? i - dot_pos : 0;
    }
    trie[u].end++;
}

// 查询逻辑
int query(string s) {
    int sum = 0, remain = trie[0].num;
    int u = 0;
    for (char c : s) {
        int ch = (c == '.' ? 10 : c - '0');
        u = trie[u].son[ch];
        int branch = remain - trie[u].num + trie[u].end;
        sum += branch * trie[u].dep;
        remain -= branch;
    }
    sum += (trie[u].num - trie[u].end) * trie[u].dep;
    return sum;
}
```

---

## 可视化设计

### 动画流程
1. **输入解析**：显示输入字符串分解为整数和小数部分。
2. **字典树插入**：逐字符生成节点，展示 `num/end/dep` 更新。
3. **贡献计算**：遍历时分步显示分叉节点贡献（黄色高亮）和前缀贡献（绿色框）。
4. **像素风格**：Canvas 绘制 8-bit 风格字典树，节点用 16x16 像素方块，分叉时播放 FC 音效。

### 交互功能
- **速度控制**：滑动条调节动画速度（0.5x~2x）。
- **单步执行**：按钮控制逐字符执行插入/查询。
- **音效触发**：分叉时播放 `jump.wav`，计算完成播放 `success.wav`。

---
处理用时：86.19秒