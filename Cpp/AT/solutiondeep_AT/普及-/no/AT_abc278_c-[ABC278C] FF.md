# 题目信息

# [ABC278C] FF

## 题目描述

【题目翻译】

洛谷是一个大平台，从前，这里有 $n$ 个用户。刚开始，他们没有任何关系。

有 $q$ 次操作，每组操作包含 $op_i$，$a_i$，$b_i$：

+ $op_i = 1$，表示 $a_i$ 关注了 $b_i$。
+ $op_i = 2$，表示 $a_i$ 取关了 $b_i$。
+ $op_i = 3$，表示查询 $a_i$ 与 $b_i$ 是否互关。

对于每个 $op_i = 3$，输出结果。

translated by @[liangbowen](https://www.luogu.com.cn/user/367488).

## 说明/提示

$1 \le n \le 10^9$

$1 \le q \le 2 \times 10^5$

保证 $1 \le a_i, b_i \le n$，且 $a_i \ne b_i$。

保证 $op_i \in \{1, 2, 3\}$。

## 样例 #1

### 输入

```
3 9

1 1 2

3 1 2

1 2 1

3 1 2

1 2 3

1 3 2

3 1 3

2 1 2

3 1 2```

### 输出

```
No

Yes

No

No```

## 样例 #2

### 输入

```
2 8

1 1 2

1 2 1

3 1 2

1 1 2

1 1 2

1 1 2

2 1 2

3 1 2```

### 输出

```
Yes

No```

## 样例 #3

### 输入

```
10 30

3 1 6

3 5 4

1 6 1

3 1 7

3 8 4

1 1 6

2 4 3

1 6 5

1 5 6

1 1 8

1 8 1

2 3 10

1 7 6

3 5 6

1 6 7

3 6 7

1 9 5

3 8 6

3 3 8

2 6 9

1 7 1

3 10 8

2 9 2

1 10 9

2 6 10

2 6 8

3 1 6

3 1 8

2 8 5

1 9 10```

### 输出

```
No

No

No

No

Yes

Yes

No

No

No

Yes

Yes```

# AI分析结果

### 题目内容重写

【题目描述】

洛谷是一个大平台，从前，这里有 $n$ 个用户。刚开始，他们没有任何关系。

有 $q$ 次操作，每组操作包含 $op_i$，$a_i$，$b_i$：

+ $op_i = 1$，表示 $a_i$ 关注了 $b_i$。
+ $op_i = 2$，表示 $a_i$ 取关了 $b_i$。
+ $op_i = 3$，表示查询 $a_i$ 与 $b_i$ 是否互关。

对于每个 $op_i = 3$，输出结果。

### 算法分类

模拟

### 题解分析与结论

题目要求处理大量用户之间的关注关系，且用户数量可能非常大（$n \le 10^9$），但操作次数相对较少（$q \le 2 \times 10^5$）。因此，直接使用数组存储关注关系会导致内存不足。题解中普遍采用了 `map` 或 `unordered_map` 来存储关注关系，避免了内存问题。

### 所选高星题解

#### 题解1：作者 youyew2007 (4星)

**关键亮点**：
- 使用 `map<pair<int, int>, int>` 存储关注关系，避免了内存问题。
- 代码结构清晰，使用了快读快写模板，提高了输入输出效率。

**核心代码**：
```cpp
map<pii,int> mp;
while(q--) {
    int t = read(), a = read(), b = read();
    if(t == 1) mp[mpp(a,b)] = 1;
    if(t == 2) mp[mpp(a,b)] = 0;
    if(t == 3) {
        if(mp[mpp(a,b)] == 1 && mp[mpp(b,a)] == 1) printf("Yes\n");
        else printf("No\n");
    }
}
```

#### 题解2：作者 RainSpark (4星)

**关键亮点**：
- 使用 `map<pair<int, int>, bool>` 存储关注关系，代码简洁明了。
- 使用了 `switch` 语句，增强了代码的可读性。

**核心代码**：
```cpp
map<PII,bool> g;
while(q--) {
    int opt, x, y;
    scanf("%d %d %d", &opt, &x, &y);
    switch(opt) {
        case 1: g[make_pair(x,y)] = 1; break;
        case 2: g[make_pair(x,y)] = 0; break;
        case 3: puts(g[make_pair(x,y)] && g[make_pair(y,x)] ? "Yes" : "No"); break;
    }
}
```

#### 题解3：作者 Strelitzia_ (4星)

**关键亮点**：
- 使用 `map<pair<int, int>, bool>` 存储关注关系，代码简洁。
- 使用了 `make_pair` 函数，增强了代码的可读性。

**核心代码**：
```cpp
map<pair<int, int>, bool> mp;
while(q--) {
    int type = read(), a = read(), b = read();
    if(type == 1) mp[make_pair(a, b)] = 1;
    else if(type == 2) mp[make_pair(a, b)] = 0;
    else puts(mp[make_pair(a, b)] && mp[make_pair(b, a)] ? "Yes" : "No");
}
```

### 最优关键思路或技巧

- 使用 `map` 或 `unordered_map` 存储关注关系，避免了内存问题。
- 使用 `pair<int, int>` 作为键值，方便存储和查询关注关系。

### 可拓展之处

- 类似的问题可以扩展到其他社交网络关系处理，如好友关系、点赞关系等。
- 可以使用更高效的数据结构如 `unordered_map` 来进一步优化查询速度。

### 推荐相似题目

1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3384 【模板】线段树 1](https://www.luogu.com.cn/problem/P3384)

---
处理用时：27.46秒