# 题目信息

# Equal XOR Segments

## 题目描述

Let us call an array $ x_1,\dots,x_m $ interesting if it is possible to divide the array into $ k>1 $ parts so that [bitwise XOR](http://tiny.cc/xor_wiki_eng) of values from each part are equal.

More formally, you must split array $ x $ into $ k $ consecutive segments, each element of $ x $ must belong to exactly $ 1 $ segment. Let $ y_1,\dots,y_k $ be the XOR of elements from each part respectively. Then $ y_1=y_2=\dots=y_k $ must be fulfilled.

For example, if $ x = [1, 1, 2, 3, 0] $ , you can split it as follows: $ [\color{blue}1], [\color{green}1], [\color{red}2, \color{red}3, \color{red}0] $ . Indeed $ \color{blue}1=\color{green}1=\color{red}2 \oplus \color{red}3\oplus \color{red}0 $ .

You are given an array $ a_1,\dots,a_n $ . Your task is to answer $ q $ queries:

- For fixed $ l $ , $ r $ , determine whether the subarray $ a_l,a_{l+1},\dots,a_r $ is interesting.

## 说明/提示

Explanation for the first test case:

The first query is described in the statement.

In the second query, we should divide $ [1,2,3] $ . A possible division is $ [1,2],[3] $ , since $ 1\oplus 2=3 $ .

It can be shown that for queries $ 3,4,5 $ , the subarrays are not interesting.

## 样例 #1

### 输入

```
4
5 5
1 1 2 3 0
1 5
2 4
3 5
1 3
3 4
5 5
1 2 3 4 5
1 5
2 4
3 5
1 3
2 3
7 4
12 9 10 9 10 11 9
1 5
1 7
2 6
2 7
11 4
0 0 1 0 0 1 0 1 1 0 1
1 2
2 5
6 9
7 11```

### 输出

```
YES
YES
NO
NO
NO

YES
NO
NO
YES
NO

NO
NO
NO
NO

YES
NO
YES
YES```

# AI分析结果

### 题目内容
# 相等的异或段

## 题目描述
如果可以将数组 $x_1,\dots,x_m$ 分成 $k>1$ 个部分，使得每个部分的值的按位异或（[按位异或](http://tiny.cc/xor_wiki_eng)）相等，我们就称这个数组是有趣的。

更正式地说，你必须将数组 $x$ 分成 $k$ 个连续的段，$x$ 的每个元素必须恰好属于一个段。设 $y_1,\dots,y_k$ 分别是每个部分元素的异或值。那么必须满足 $y_1=y_2=\dots=y_k$。

例如，如果 $x = [1, 1, 2, 3, 0]$ ，你可以按如下方式拆分：$[\color{blue}1], [\color{green}1], [\color{red}2, \color{red}3, \color{red}0]$ 。实际上，$\color{blue}1=\color{green}1=\color{red}2 \oplus \color{red}3\oplus \color{red}0$ 。

给定一个数组 $a_1,\dots,a_n$ 。你的任务是回答 $q$ 个查询：
- 对于给定的 $l$ ，$r$ ，判断子数组 $a_l,a_{l + 1},\dots,a_r$ 是否有趣。

## 说明/提示
第一个测试用例的解释：
第一个查询在题目描述中已有说明。
在第二个查询中，我们应该划分 $[1,2,3]$ 。一种可能的划分是 $[1,2],[3]$ ，因为 $1\oplus 2=3$ 。
可以证明，对于查询 $3$、$4$、$5$ ，子数组不是有趣的。

## 样例 #1
### 输入
```
4
5 5
1 1 2 3 0
1 5
2 4
3 5
1 3
3 4
5 5
1 2 3 4 5
1 5
2 4
3 5
1 3
2 3
7 4
12 9 10 9 10 11 9
1 5
1 7
2 6
2 7
11 4
0 0 1 0 0 1 0 1 1 0 1
1 2
2 5
6 9
7 11
```
### 输出
```
YES
YES
NO
NO
NO

YES
NO
NO
YES
NO

NO
NO
NO
NO

YES
NO
YES
YES
```

### 题解综合分析与结论
所有题解的核心思路都是先利用前缀异或和简化区间异或和的计算，再根据 $k$ 的取值情况进行分类讨论。主要难点在于证明 $k$ 只需考虑 2 和 3 两种情况，以及在 $k = 3$ 时如何高效地找到满足条件的划分点。
1. **思路方面**：都基于异或的性质，如自反性（$x \oplus x = 0$）、交换律（$a \oplus b = b \oplus a$）等。当区间异或和为 0 时，可直接判断能分成两个异或和相同的区间；当区间异或和不为 0 时，需考虑分成三个异或和相同的区间。
2. **算法要点**：构建前缀异或和数组，对于每个查询的区间 $[l, r]$，通过前缀异或和快速计算区间异或和。利用数据结构（如 vector 结合 map 或离散化处理）存储前缀异或和相同的位置，便于二分查找满足条件的划分点。
3. **解决难点**：证明 $k > 3$ 时可转化为 $k = 2$ 或 $k = 3$ 的情况。在 $k = 3$ 时，通过贪心策略，在满足条件的位置集合中二分查找最左和最右的位置，判断是否存在满足 $l \leq i < j < r$ 且 $s_j = s_{l - 1}, s_i = s_r$ 的 $i$ 和 $j$。

### 所选的题解
- **作者：LEE114514 (赞：8)  星级：5星**
    - **关键亮点**：思路清晰简洁，直接证明 $k$ 只需考虑 2 和 3 两种取值情况。代码利用 map 存储前缀异或和及其位置，通过二分查找判断是否存在满足条件的划分，写法简洁高效。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int T, n, m, x, y;
int a[maxn], b[maxn], c[maxn], len;
map<int, vector<int> > mp;
vector<int>::iterator posx, posy;
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        mp.clear();
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), a[i] ^= a[i - 1], mp[a[i]].emplace_back(i);
        while (m--) {
            scanf("%d%d", &x, &y);
            if (a[y] == a[x - 1]) {
                puts("YES");
                continue;
            }
            posy = lower_bound(mp[a[x - 1]].begin(), mp[a[x - 1]].end(), y);
            posx = lower_bound(mp[a[y]].begin(), mp[a[y]].end(), x);
            if (posy == mp[a[x - 1]].begin() || posx == mp[a[y]].end()) puts("NO");
            else --posy, puts(*posx < *posy && *posx >= x && *posy <= y? "YES" : "NO");
        }
        putchar('\n');
    }
}
```
核心实现思想：先对输入数组求前缀异或和并存入 `a` 数组，同时用 `mp` 记录每个前缀异或和出现的位置。对于每个查询 $[x, y]$，若 $a[y] == a[x - 1]$ 直接输出 `YES`；否则在 `mp[a[x - 1]]` 中二分查找大于等于 `y` 的位置 `posy`，在 `mp[a[y]]` 中二分查找大于等于 `x` 的位置 `posx`，通过判断 `posx` 和 `posy` 的关系输出结果。
- **作者：Special_Tony (赞：8)  星级：5星**
    - **关键亮点**：详细阐述异或性质，并基于性质推出若区间异或和不为 0 则一定是奇数组且可转化为 3 组的结论。代码结构清晰，利用 vector 和 map 实现离散化和二分查找，逻辑明确。
    - **核心代码**：
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, q, l, r, x, tmp, a[200005], tot;
map <int, int> mp;
vector <int> v[200005];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> q;
        tot = 0, mp.clear();
        for (int i = 1; i <= n; ++i) {
            v[i].clear();
            cin >> a[i], a[i] ^= a[i - 1];
            if (!mp[a[i]])
                mp[a[i]] = ++tot;
            v[mp[a[i]]].emplace_back(i);
        }
        while (q--) {
            cin >> l >> r;
            if (!(a[r] ^ a[l - 1])) {
                cout << "YES\n";
                continue;
            }
            tmp = mp[a[r]];
            x = lower_bound(v[tmp].begin(), v[tmp].end(), l) - v[tmp].begin();
            if (x >= v[tmp].size() || v[tmp][x] >= r) {
                cout << "NO\n";
                continue;
            }
            tmp = mp[a[l - 1]];
            x = lower_bound(v[tmp].begin(), v[tmp].end(), v[mp[a[r]]][x]) - v[tmp].begin();
            if (x >= v[tmp].size() || v[tmp][x] >= r) {
                cout << "NO\n";
                continue;
            }
            cout << "YES\n";
        }
        cout << '\n';
    }
    return 0;
}
```
核心实现思想：先对输入数组求前缀异或和并存入 `a` 数组，用 `mp` 对前缀异或和离散化并记录每个离散值对应的位置存入 `v` 数组。对于每个查询 $[l, r]$，若 $a[r] ^ a[l - 1] == 0$ 直接输出 `YES`；否则在 `v[mp[a[r]]]` 中二分查找大于等于 `l` 的位置 `x`，再在 `v[mp[a[l - 1]]]` 中二分查找大于 `v[mp[a[r]]][x]` 的位置，根据查找结果输出。
- **作者：Muse_Dash (赞：2)  星级：4星**
    - **关键亮点**：简洁明了地阐述基于前缀异或和的解题思路，对 $pre_r = pre_{l - 1}$ 和 $pre_r \neq pre_{l - 1}$ 两种情况分别说明判断方法，易于理解。
    - **核心代码**：无完整代码，但思路实现核心步骤可描述为：先求前缀异或和 `pre`，对于查询区间 $[l, r]$，若 `pre[r] == pre[l - 1]` 直接输出 `YES`；否则利用 `map` 映射前缀异或和数值到其位置的 `vector`，在对应 `vector` 中二分查找满足条件的位置判断是否存在满足条件的划分。

### 最优关键思路或技巧
1. **性质利用**：充分利用异或运算的性质，如自反性、交换律等，简化问题分析。通过分析得出 $k$ 只需考虑 2 和 3 两种情况，大大减少讨论复杂度。
2. **前缀异或和**：构建前缀异或和数组，将区间异或和的计算转化为前缀异或和的简单异或运算，提高计算效率。
3. **数据结构运用**：利用 map 结合 vector 实现对前缀异或和及其位置的存储与快速查找，通过二分查找满足条件的划分点，优化查找过程。

### 可拓展之处
同类型题通常围绕位运算（特别是异或运算）与数组区间操作展开。类似算法套路是先利用位运算性质简化问题，再通过前缀和（这里是前缀异或和）优化区间操作的计算，最后借助合适的数据结构实现高效查找。

### 相似知识点洛谷题目
1. [P1514 引水入城](https://www.luogu.com.cn/problem/P1514)：涉及图论与搜索，同时可能需要利用位运算优化某些判断。
2. [P3128 [USACO15DEC]Max Flow P](https://www.luogu.com.cn/problem/P3128)：结合图论与位运算，通过合理运用位运算性质解决流量相关问题。
3. [P4151 [WC2011]最大XOR和路径](https://www.luogu.com.cn/problem/P4151)：重点考察异或运算与图的路径问题，与本题在异或运算运用上有相似之处。

### 个人心得摘录与总结
1. **作者Special_Tony**：在比赛倒数第一分钟提交成功并借此比赛上青，该经历强调了在竞赛中把握时间和对思路正确性的果断判断的重要性。 

---
处理用时：56.88秒