# 题目信息

# [USACO08DEC] Secret Message G

## 题目描述

Bessie is leading the cows in an attempt to escape! To do this, the cows are sending secret binary messages to each other.

Ever the clever counterspy, Farmer John has intercepted the first $b_i$ ($1 \le b_i \le 10,000$) bits of each of $M$ ($1 \le M \le 50,000$) of these secret binary messages.

He has compiled a list of $N$ ($1 \le N \le 50,000$) partial codewords that he thinks the cows are using. Sadly, he only knows the first $c_j$ ($1 \le c_j \le 10,000$) bits of codeword $j$.

For each codeword $j$, he wants to know how many of the intercepted messages match that codeword (i.e., for codeword $j$, how many times does a message and the codeword have the same initial bits). Your job is to compute this number.

The total number of bits in the input (i.e., the sum of the $b_i$ and the $c_j$) will not exceed  $500,000$.

贝茜正在领导奶牛们逃跑．为了联络，奶牛们互相发送秘密信息．

信息是二进制的，共有 $M$（$1 \le M \le 50000$）条，反间谍能力很强的约翰已经部分拦截了这些信息，知道了第  $i$ 条二进制信息的前 $b_i$（$1 \le b_i \le 10000$）位，他同时知道，奶牛使用 $N$（$1 \le N \le 50000$）条暗号．但是，他仅仅知道第 $j$ 条暗号的前 $c_j$（$1 \le c_j \le 10000$）位。

对于每条暗号 $j$，他想知道有多少截得的信息能够和它匹配。也就是说，有多少信息和这条暗号有着相同的前缀。当然，这个前缀长度必须等于暗号和那条信息长度的较小者。

在输入文件中，位的总数（即 $\sum b_i + \sum c_i$）不会超过 $500000$。

## 说明/提示

Four messages; five codewords. 

The intercepted messages start with 010, 1, 100, and 110.

The possible codewords start with 0, 1, 01, 01001, and 11.


0 matches only 010: 1 match

1 matches 1, 100, and 110: 3 matches

01 matches only 010: 1 match

01001 matches 010: 1 match

11 matches 1 and 110: 2 matches


## 样例 #1

### 输入

```
4 5 
3 0 1 0 
1 1 
3 1 0 0 
3 1 1 0 
1 0 
1 1 
2 0 1 
5 0 1 0 0 1 
2 1 1 
```

### 输出

```
1 
3 
1 
1 
2 
```

# AI分析结果

### 综合分析与结论

这些题解大多基于**Trie树**（字典树）来解决该问题，核心思路是通过构建Trie树来存储信息，并在查询时统计匹配的前缀数量。题解之间的差异主要体现在对Trie树的实现细节、统计方式以及代码的优化程度上。部分题解通过引入额外的统计变量（如`sum`、`end`等）来优化查询效率，避免重复计算。

总体来看，题解的质量参差不齐，部分题解思路清晰、代码简洁，而另一些则存在冗余或不够优化的实现。以下是对部分高质量题解的总结与推荐。

---

### 精选题解

#### 1. **题解作者：户山香澄**
- **星级**：★★★★★
- **关键亮点**：
  - 思路清晰，详细解释了Trie树的构建与查询过程。
  - 通过`sum`和`end`两个变量分别统计经过节点的信息数量和以节点结尾的信息数量，优化了查询效率。
  - 代码简洁，逻辑清晰，易于理解。
- **个人心得**：
  - 作者提到“如果待查询信息无法终结，说明没有比该信息长且前缀是该信息的信息”，这一观察帮助优化了查询逻辑。

**核心代码**：
```cpp
void insert() {
    int p = 1;
    for (int i = 1; i <= len; i++) {
        int c = a[i];
        if (!trie[p][c]) trie[p][c] = ++tot;
        p = trie[p][c];
        sum[p]++;
    }
    end[p]++;
}

int query() {
    int p = 1, ans = 0;
    for (int i = 1; i <= len; i++) {
        int c = a[i];
        if (!trie[p][c]) return ans;
        p = trie[p][c];
        ans += end[p];
    }
    return ans + sum[p] - end[p];
}
```

#### 2. **题解作者：yue__z**
- **星级**：★★★★☆
- **关键亮点**：
  - 通过`bo`和`sum`数组分别记录以节点结尾的信息数量和经过节点的信息数量，优化了查询逻辑。
  - 代码结构清晰，注释详细，便于理解。
- **个人心得**：
  - 作者提到“如果当前u处有单词结尾，那么多加了一次，减去”，这一细节处理避免了重复计算。

**核心代码**：
```cpp
void add(bool p[]) {
    int u = 1;
    for (int i = 1; i <= k; i++) {
        int c = p[i];
        if (ch[u][c] == -1) ch[u][c] = ++tot;
        u = ch[u][c];
        sum[u]++;
    }
    bo[u]++;
}

int find(bool p[]) {
    int u = 1, res = 0;
    for (int i = 1; i <= k; i++) {
        int c = p[i];
        if (ch[u][c] == -1) return res;
        u = ch[u][c];
        res += bo[u];
    }
    return res - bo[u] + sum[u];
}
```

#### 3. **题解作者：LB_tq**
- **星级**：★★★★☆
- **关键亮点**：
  - 通过`d`和`b`数组分别记录经过节点的信息数量和以节点结尾的信息数量，优化了查询逻辑。
  - 代码简洁，逻辑清晰，易于理解。
- **个人心得**：
  - 作者提到“有可能存在相同的信息，所以b数组要++而不是=1”，这一细节处理避免了重复计算。

**核心代码**：
```cpp
void tire(int x, int a[]) {
    int u = 1;
    for (int i = 1; i <= x; i++) {
        if (c[u][a[i]] == 0) c[u][a[i]] = ++t;
        u = c[u][a[i]];
        d[u]++;
    }
    b[u]++;
}

int tai(int x, int a[]) {
    int u = 1, ans = 0, f = 0;
    for (int i = 1; i <= x; i++) {
        if (c[u][a[i]] != 0) u = c[u][a[i]];
        else { f = 1; break; }
        if (b[u] != 0) ans += b[u];
    }
    if (f == 0) ans += d[u] - b[u];
    return ans;
}
```

---

### 最优关键思路与技巧

1. **Trie树的构建与查询**：通过Trie树存储信息，查询时统计匹配的前缀数量。
2. **统计变量优化**：引入`sum`和`end`等变量，分别统计经过节点的信息数量和以节点结尾的信息数量，避免重复计算。
3. **细节处理**：在查询时，若信息无法终结，直接返回当前统计值，避免无效计算。

---

### 可拓展之处

1. **类似算法套路**：Trie树常用于处理字符串前缀匹配问题，如AC自动机、后缀树等。
2. **同类型题目**：
   - **P3879 [TJOI2010]阅读理解**：考察Trie树的基本应用。
   - **P5149 [USACO18OPEN]会议座位**：考察Trie树与字符串排序的结合。
   - **P2580 [ZJOI2007]报表统计**：考察Trie树与统计的结合。

---

### 推荐题目

1. **P3879 [TJOI2010]阅读理解**：考察Trie树的基本应用。
2. **P5149 [USACO18OPEN]会议座位**：考察Trie树与字符串排序的结合。
3. **P2580 [ZJOI2007]报表统计**：考察Trie树与统计的结合。

---

### 个人心得总结

- **调试经历**：部分作者提到在处理重复信息时，通过`++`而非`=`来避免重复计算，这一细节处理提升了代码的鲁棒性。
- **顿悟感想**：通过引入额外的统计变量（如`sum`、`end`等），可以优化查询效率，避免重复计算，这一思路值得借鉴。

---
处理用时：49.29秒