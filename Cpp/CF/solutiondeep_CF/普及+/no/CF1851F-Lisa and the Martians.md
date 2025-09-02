# 题目信息

# Lisa and the Martians

## 题目描述

Lisa was kidnapped by martians! It okay, because she has watched a lot of TV shows about aliens, so she knows what awaits her. Let's call integer martian if it is a non-negative integer and strictly less than $ 2^k $ , for example, when $ k = 12 $ , the numbers $ 51 $ , $ 1960 $ , $ 0 $ are martian, and the numbers $ \pi $ , $ -1 $ , $ \frac{21}{8} $ , $ 4096 $ are not.

The aliens will give Lisa $ n $ martian numbers $ a_1, a_2, \ldots, a_n $ . Then they will ask her to name any martian number $ x $ . After that, Lisa will select a pair of numbers $ a_i, a_j $ ( $ i \neq j $ ) in the given sequence and count $ (a_i \oplus x) \& (a_j \oplus x) $ . The operation $ \oplus $ means [Bitwise exclusive OR](http://tiny.cc/xor_wiki), the operation $ \& $ means [Bitwise And](<http://tiny.cc/and_wiki >). For example, $ (5 \oplus 17) \& (23 \oplus 17) = (00101_2 \oplus 10001_2) \& (10111_2 \oplus 10001_2) = 10100_2 \& 00110_2 = 00100_2 = 4 $ .

Lisa is sure that the higher the calculated value, the higher her chances of returning home. Help the girl choose such $ i, j, x $ that maximize the calculated value.

## 说明/提示

First testcase: $ (3 \oplus 14) \& (1 \oplus 14) = (0011_2 \oplus 1110_2) \& (0001_2 \oplus 1110_2) = 1101_2 = 1101_2 \& 1111_2 = 1101_2 = 13 $ .

Second testcase: $ (1 \oplus 0) \& (1 \oplus 0) = 1 $ .

Third testcase: $ (9 \oplus 4082) \& (13 \oplus 4082) = 4091 $ .

Fourth testcase: $ (3 \oplus 7) \& (0 \oplus 7) = 4 $ .

## 样例 #1

### 输入

```
10
5 4
3 9 1 4 13
3 1
1 0 1
6 12
144 1580 1024 100 9 13
4 3
7 3 0 4
3 2
0 0 1
2 4
12 2
9 4
6 14 9 4 4 4 5 10 2
2 1
1 0
2 4
11 4
9 4
2 11 10 1 6 9 11 0 5```

### 输出

```
1 3 14
1 3 0
5 6 4082
2 3 7
1 2 3
1 2 15
4 5 11
1 2 0
1 2 0
2 7 4```

# AI分析结果

### 题目内容重写

#### 题目描述

Lisa被火星人绑架了！不过没关系，因为她看过很多关于外星人的电视节目，所以她知道会发生什么。我们称一个整数为“火星数”，如果它是一个非负整数且严格小于 $2^k$。例如，当 $k = 12$ 时，数字 $51$、$1960$、$0$ 是火星数，而数字 $\pi$、$-1$、$\frac{21}{8}$、$4096$ 不是。

火星人会给Lisa $n$ 个火星数 $a_1, a_2, \ldots, a_n$。然后他们会让她选择一个火星数 $x$。之后，Lisa会从给定的序列中选择一对数 $a_i, a_j$（$i \neq j$），并计算 $(a_i \oplus x) \& (a_j \oplus x)$。操作 $\oplus$ 表示[按位异或](http://tiny.cc/xor_wiki)，操作 $\&$ 表示[按位与](<http://tiny.cc/and_wiki >)。例如，$(5 \oplus 17) \& (23 \oplus 17) = (00101_2 \oplus 10001_2) \& (10111_2 \oplus 10001_2) = 10100_2 \& 00110_2 = 00100_2 = 4$。

Lisa相信，计算出的值越高，她回家的机会就越大。帮助女孩选择这样的 $i, j, x$，使得计算出的值最大化。

### 算法分类

位运算

### 题解分析与结论

本题的核心是通过位运算最大化 $(a_i \oplus x) \& (a_j \oplus x)$ 的值。大多数题解都基于以下关键观察：

1. **位运算性质**：当 $a_i$ 和 $a_j$ 在某一位上相同时，可以通过选择 $x$ 的该位为相反值，使得该位的结果为1。反之，若 $a_i$ 和 $a_j$ 在某一位上不同，则无论 $x$ 如何选择，该位的结果都为0。
2. **贪心策略**：为了使结果最大化，应尽量选择 $a_i$ 和 $a_j$ 在高位上相同的数对，因为高位对结果的影响更大。
3. **排序与相邻数对**：将数组排序后，相邻的数对在高位上相同的概率更大，因此可以通过遍历相邻数对来寻找最优解。

### 精选题解

#### 题解1：_sunkuangzheng_ (赞：6)

**星级**：★★★★★  
**关键亮点**：  
- 使用01-trie树来高效查找与当前数 $a_i$ 在高位上相同的数 $a_j$。
- 通过遍历每个数 $a_i$，在trie树中查找最优的 $a_j$，并计算相应的 $x$。
- 代码清晰，逻辑严谨，时间复杂度为 $\Theta(nk)$。

**核心代码**：
```cpp
void insert(int x, int id) {
    int s = 0;
    for (int i = kk; i >= 0; i--) {
        int k = (x >> i) & 1;
        if (vis[s][k] != times) ch[s][k] = ++tot;
        else p[ch[s][k]] = times;
        vis[s][k] = times, s = ch[s][k];
    }
    ed[s].push_back(id);
}

int query(int x, int id) {
    int s = 0, flag = 0;
    for (int i = kk; i >= 0; i--) {
        int k = (x >> i) & 1;
        if (vis[s][k] == times && (flag || (p[ch[s][k]] == times))) s = ch[s][k];
        else s = ch[s][!k], flag = 1;
    }
    if (ed[s][0] == id) return ed[s][1];
    return ed[s][0];
}
```

#### 题解2：Keroshi (赞：0)

**星级**：★★★★  
**关键亮点**：  
- 通过排序数组，遍历相邻数对来寻找最优解。
- 直接计算每个相邻数对的 $x$，并更新最大值。
- 代码简洁，时间复杂度为 $O(nk)$。

**核心代码**：
```cpp
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), f(n);
    REP(i, n) cin >> a[i];
    iota(ALL(f), 0);
    sort(ALL(f), [&] (int x, int y) {
        return a[x] < a[y];
    });
    int ans = 0, p1 = 0, p2 = 1, p3 = 0;
    REP(i, n - 1) {
        int x = 0, res = 0;
        ROF(j, k - 1, 0) {
            int u = (a[f[i]] >> j) & 1;
            int v = (a[f[i + 1]] >> j) & 1;
            if (u == v) {
                res ^= (1 << j);
                if (!u) x ^= (1 << j);
            }
        }
        if (res > ans) {
            ans = res;
            p1 = f[i];
            p2 = f[i + 1];
            p3 = x;
        }
    }
    if (p1 > p2) swap(p1, p2);
    cout << p1 + 1 << " " << p2 + 1 << " " << p3 << endl;
}
```

#### 题解3：xzyg (赞：0)

**星级**：★★★★  
**关键亮点**：  
- 使用01-trie树来查找与当前数 $a_i$ 在高位上相同的数 $a_j$。
- 通过贪心策略，优先选择与当前位相同的路径。
- 代码实现清晰，时间复杂度为 $O(nk)$。

**核心代码**：
```cpp
void query(ll x, ll num, ll bit, ll cnt, ll cntt, ll pos) {
    if (bit == -1) {
        if (ans < cnt) {
            ans = cnt;
            ansx = cntt;
            anspos1 = pos;
            anspos2 = tree[x].pos;
        }
        return;
    }
    bool p = num & (1 << bit);
    if (tree[x].son[p]) {
        cnt ^= (1 << bit);
        if (p == 0) {
            cntt ^= (1 << bit);
        }
        query(tree[x].son[p], num, bit - 1, cnt, cntt, pos);
    } else {
        query(tree[x].son[p ^ 1], num, bit - 1, cnt, cntt, pos);
    }
}
```

### 最优关键思路

1. **位运算性质**：利用 $a_i$ 和 $a_j$ 在某一位上相同时，可以通过选择 $x$ 的该位为相反值，使得该位的结果为1。
2. **贪心策略**：优先选择在高位上相同的数对，因为高位对结果的影响更大。
3. **数据结构优化**：使用01-trie树来高效查找与当前数在高位上相同的数。

### 拓展思路

- **类似题目**：可以考虑其他位运算相关的题目，如最大异或对、最小异或对等。
- **数据结构**：01-trie树在处理位运算相关问题时非常高效，可以应用于其他类似问题。

### 推荐题目

1. [P4735 最大异或和](https://www.luogu.com.cn/problem/P4735)
2. [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)
3. [P4592 最小异或对](https://www.luogu.com.cn/problem/P4592)

---
处理用时：63.28秒