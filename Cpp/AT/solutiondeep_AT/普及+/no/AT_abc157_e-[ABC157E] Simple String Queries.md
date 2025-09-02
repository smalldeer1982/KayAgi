# 题目信息

# [ABC157E] Simple String Queries

## 题目描述

给定长度为n的原字符串与q次操作或询问。其格式如下:

①1 i c: 将第i位字符改为c(c也是字符)。

②2 l r: 询问区间[l,r]内不同字符的个数。



感谢ducati小蒟蒻的翻译

## 样例 #1

### 输入

```
7

abcdbbd

6

2 3 6

1 5 z

2 1 1

1 4 a

1 7 d

2 1 7```

### 输出

```
3

1

5```

# AI分析结果

### 题目内容重写
给定长度为n的原字符串与q次操作或询问。其格式如下:

①1 i c: 将第i位字符改为c(c也是字符)。

②2 l r: 询问区间[l,r]内不同字符的个数。

### 算法分类
树状数组、线段树、分块

### 题解分析与结论
本题的核心在于如何高效地处理字符串的单点修改和区间查询不同字符的个数。以下是各题解的思路对比：

1. **线段树 + bitset**：使用线段树维护每个区间内字符的出现情况，通过bitset来存储26个字母的存在情况。单点修改时更新叶子节点，区间查询时通过位运算合并子区间的bitset。该方法的优点是查询和修改的时间复杂度均为O(log n)，且代码简洁。

2. **树状数组**：为每个字母单独维护一个树状数组，记录该字母在字符串中的出现情况。单点修改时更新对应字母的树状数组，区间查询时遍历26个字母，统计每个字母在区间内的出现次数。该方法的优点是实现简单，但空间复杂度较高。

3. **分块**：将字符串分成若干块，每块维护一个桶记录字符的出现情况。单点修改时更新对应块的桶，区间查询时遍历所有相关块，统计字符的出现情况。该方法的优点是实现简单，但时间复杂度较高。

### 所选高星题解
1. **Grisses (线段树 + bitset)**
   - **星级**：5星
   - **关键亮点**：使用bitset优化了字符存在情况的存储和查询，代码简洁高效。
   - **核心代码**：
     ```cpp
     struct Node {
         int l, r;
         bitset<26> m;
     };
     void Add(int q, int x, char s) {
         if (c[q].l == c[q].r) {
             c[q].m.reset();
             c[q].m[s - 'a'] = 1;
             return;
         }
         int mid = c[q].l + c[q].r >> 1;
         if (x <= mid) Add(q << 1, x, s);
         else Add(q << 1 | 1, x, s);
         c[q].m = c[q << 1].m | c[q << 1 | 1].m;
     }
     ```

2. **徐晨轩✅ (树状数组)**
   - **星级**：4星
   - **关键亮点**：为每个字母单独维护一个树状数组，实现简单直观。
   - **核心代码**：
     ```cpp
     void update(int x, int y, int p) {
         for (; x <= n; x += lowbit(x)) c[x][p] += y;
     }
     int ask(int x, int p) {
         int sum = 0;
         for (; x; x -= lowbit(x)) sum += c[x][p];
         return sum;
     }
     ```

3. **CaiXY06 (线段树)**
   - **星级**：4星
   - **关键亮点**：使用线段树维护字符的存在情况，代码结构清晰。
   - **核心代码**：
     ```cpp
     inline void push_up(int p) {
         tr[p].c = tr[p << 1].c | tr[p << 1 | 1].c;
     }
     inline SGT query(int p, int l, int r, int L, int R) {
         if (l >= L && r <= R) return tr[p];
         int mid = (l + r) >> 1;
         SGT res; res.c.reset();
         if (L <= mid) res.c |= query(p << 1, l, mid, L, R).c;
         if (R > mid) res.c |= query(p << 1 | 1, mid + 1, r, L, R).c;
         return res;
     }
     ```

### 最优关键思路
使用线段树结合bitset来维护字符的存在情况，能够高效地处理单点修改和区间查询，且代码简洁易读。

### 可拓展之处
类似的问题可以扩展到更大范围的字符集，或者处理更复杂的字符串操作，如区间反转、区间替换等。

### 推荐题目
1. [P1972 HH的项链](https://www.luogu.com.cn/problem/P1972)
2. [P1903 数颜色](https://www.luogu.com.cn/problem/P1903)
3. [P3834 可持久化线段树](https://www.luogu.com.cn/problem/P3834)

---
处理用时：29.37秒