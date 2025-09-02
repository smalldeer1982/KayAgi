# 题目信息

# [ABC164C] gacha

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc164/tasks/abc164_c

くじ引きを $ N $ 回行い、$ i $ 回目には種類が文字列 $ S_i $ で表される景品を手に入れました。

何種類の景品を手に入れましたか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ S_i $ は英小文字のみからなり、長さは $ 1 $ 以上 $ 10 $ 以下

### Sample Explanation 1

`apple` と `orange` の $ 2 $ 種類の景品を手に入れました。

## 样例 #1

### 输入

```
3

apple

orange

apple```

### 输出

```
2```

## 样例 #2

### 输入

```
5

grape

grape

grape

grape

grape```

### 输出

```
1```

## 样例 #3

### 输入

```
4

aaaa

a

aaa

aa```

### 输出

```
4```

# AI分析结果

【题目内容】
# [ABC164C] gacha

## 题目描述

进行 $N$ 次抽奖，第 $i$ 次抽奖得到的奖品类型由字符串 $S_i$ 表示。

请问一共得到了多少种不同的奖品？

## 说明/提示

### 制約

- $1 \leq N \leq 2 \times 10^5$
- $S_i$ 仅由小写字母组成，长度在 $1$ 到 $10$ 之间

### 样例解释 1

得到了 `apple` 和 `orange` 两种不同的奖品。

## 样例 #1

### 输入

```
3

apple

orange

apple
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5

grape

grape

grape

grape

grape
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4

aaaa

a

aaa

aa
```

### 输出

```
4
```

【算法分类】
字符串

【题解分析与结论】
本题的核心是统计一组字符串中不同字符串的数量。各题解主要采用了以下几种方法：
1. 使用 `set` 自动去重，直接统计 `set` 的大小。
2. 先排序，再使用 `unique` 函数去重，统计去重后的元素个数。
3. 使用 `map` 记录每个字符串是否出现过，最后统计 `map` 的大小。

这些方法的核心思想都是利用数据结构（如 `set`、`map`）或算法（如排序+去重）来高效地统计不同字符串的数量。其中，`set` 的方法最为简洁和高效，适合本题的规模。

【所选高星题解】
1. **Diamiko（5星）**
   - **关键亮点**：使用 `set` 自动去重，代码简洁高效。
   - **代码核心**：
     ```python
     n = int(input())
     s = set()
     for i in range(n):
         s.add(input())
     print(len(s))
     ```
   - **个人心得**：无。

2. **ADay（4星）**
   - **关键亮点**：使用 `vector` 和 `unique` 函数，结合排序实现去重。
   - **代码核心**：
     ```cpp
     vector<string> a;
     int n;
     string x;
     cin >> n;
     while (n--) cin >> x, a.push_back(x);
     sort(a.begin(), a.end());
     cout << unique(a.begin(), a.end()) - a.begin();
     ```
   - **个人心得**：无。

3. **Scrutiny（4星）**
   - **关键亮点**：使用 `set` 自动去重，并强调了 `set` 的类型和定义指针的注意事项。
   - **代码核心**：
     ```cpp
     set<string> ss;
     int n;
     string s;
     cin >> n;
     for (int i = 1; i <= n; ++i) {
         getline(cin, s);
         ss.insert(s);
     }
     cout << ss.size();
     ```
   - **个人心得**：无。

【最优关键思路】
使用 `set` 自动去重是最简洁和高效的方法，适合本题的规模。`set` 的插入和查询操作时间复杂度均为 $O(\log n)$，整体复杂度为 $O(n \log n)$，能够很好地处理 $2 \times 10^5$ 的数据规模。

【拓展思路】
类似的问题可以通过 `unordered_set` 进一步提高效率，`unordered_set` 的平均时间复杂度为 $O(1)$，但最坏情况下可能退化为 $O(n)$。此外，`map` 和 `unordered_map` 也可以用于统计不同元素的数量，适用于需要记录更多信息的场景。

【推荐题目】
1. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
3. [P1918 保龄球](https://www.luogu.com.cn/problem/P1918)

---
处理用时：26.69秒