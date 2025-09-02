# 题目信息

# Boris and His Amazing Haircut

## 题目描述

Boris thinks that chess is a tedious game. So he left his tournament early and went to a barber shop as his hair was a bit messy.

His current hair can be described by an array $ a_1,a_2,\ldots, a_n $ , where $ a_i $ is the height of the hair standing at position $ i $ . His desired haircut can be described by an array $ b_1,b_2,\ldots, b_n $ in a similar fashion.

The barber has $ m $ razors. Each has its own size and can be used at most once. In one operation, he chooses a razor and cuts a segment of Boris's hair. More formally, an operation is:

- Choose any razor which hasn't been used before, let its size be $ x $ ;
- Choose a segment $ [l,r] $ ( $ 1\leq l \leq r \leq n $ );
- Set $ a_i := \min (a_i,x) $ for each $ l\leq i \leq r $ ;

Notice that some razors might have equal sizes — the barber can choose some size $ x $ only as many times as the number of razors with size $ x $ .

He may perform as many operations as he wants, as long as any razor is used at most once and $ a_i = b_i $ for each $ 1 \leq i \leq n $ at the end. He does not have to use all razors.

Can you determine whether the barber can give Boris his desired haircut?

## 说明/提示

In the first test case, Boris's hair is initially $ [3,3,3] $ . Let us describe a sequence of $ 2 $ operations the barber can perform:

- The barber uses the razor with size $ 1 $ on the segment $ [2,2] $ ; hence Boris's hair becomes $ [3,1,3] $ .
- The barber uses the razor with size $ 2 $ on the segment $ [1,3] $ ; hence Boris's hair becomes $ [2,1,2] $ which is the desired haircut.

In the third test case, no operation has to be done since Boris's hair is already as desired.

In the fourth test case, no cuts will be able to increase the third element in $ [1,1,1] $ in a way that the array becomes $ [1,1,2] $ .

## 样例 #1

### 输入

```
7
3
3 3 3
2 1 2
2
1 2
6
3 4 4 6 3 4
3 1 2 3 2 3
3
3 2 3
10
1 2 3 4 5 6 7 8 9 10
1 2 3 4 5 6 7 8 9 10
10
1 2 3 4 5 6 7 8 9 10
3
1 1 1
1 1 2
12
4 2 4 3 1 5 6 3 5 6 2 1
13
7 9 4 5 3 3 3 6 8 10 3 2 5
5 3 1 5 3 2 2 5 8 5 1 1 5
8
1 5 3 5 4 2 3 1
13
7 9 4 5 3 3 3 6 8 10 3 2 5
5 3 1 5 3 2 2 5 8 5 1 1 5
7
1 5 3 4 2 3 1
3
19747843 2736467 938578397
2039844 2039844 2039844
1
2039844```

### 输出

```
YES
NO
YES
NO
YES
NO
YES```

# AI分析结果

### 题目内容重写
# Boris 和他的神奇理发

## 题目描述

Boris 认为国际象棋是一个乏味的游戏。因此，他提前离开了比赛，去了理发店，因为他的头发有点乱。

他当前的头发可以用一个数组 $a_1,a_2,\ldots, a_n$ 来描述，其中 $a_i$ 表示位置 $i$ 的头发高度。他理想的发型可以用类似的数组 $b_1,b_2,\ldots, b_n$ 来描述。

理发师有 $m$ 把剃刀。每把剃刀都有自己的尺寸，且每把剃刀最多只能使用一次。在一次操作中，理发师选择一把剃刀并剪掉 Boris 头发的一个区间。更正式地说，一次操作是：

- 选择任何一把之前未使用过的剃刀，设其尺寸为 $x$；
- 选择一个区间 $[l,r]$（$1\leq l \leq r \leq n$）；
- 对于每个 $l\leq i \leq r$，将 $a_i$ 设置为 $\min(a_i,x)$；

注意，有些剃刀可能有相同的尺寸——理发师可以选择尺寸 $x$ 的次数等于尺寸为 $x$ 的剃刀数量。

理发师可以进行任意次数的操作，只要每把剃刀最多使用一次，并且最终每个 $1 \leq i \leq n$ 都有 $a_i = b_i$。他不一定要使用所有的剃刀。

你能确定理发师是否能给 Boris 他理想的发型吗？

## 说明/提示

在第一个测试用例中，Boris 的头发最初是 $[3,3,3]$。以下是理发师可以执行的两次操作：

- 理发师使用尺寸为 $1$ 的剃刀在区间 $[2,2]$ 上操作；因此，Boris 的头发变为 $[3,1,3]$。
- 理发师使用尺寸为 $2$ 的剃刀在区间 $[1,3]$ 上操作；因此，Boris 的头发变为 $[2,1,2]$，这是理想的发型。

在第三个测试用例中，不需要进行任何操作，因为 Boris 的头发已经是他想要的发型。

在第四个测试用例中，任何剪发操作都无法将 $[1,1,1]$ 中的第三个元素增加到 $[1,1,2]$。

### 算法分类
贪心

### 题解分析与结论
本题的核心在于如何合理地使用剃刀来将头发数组 $a$ 转换为目标数组 $b$。题解的主要思路是通过贪心策略，尽可能减少剃刀的使用次数，同时确保每个位置的头发高度能够达到目标值。

### 精选题解
#### 题解1：作者：xiaruize (赞：8)
**星级：5星**
**关键亮点：**
- 使用 ST 表快速计算区间最大值，优化了时间复杂度。
- 通过贪心策略，计算每个高度 $h$ 所需的最少剃刀数量，并检查是否足够。
- 代码结构清晰，逻辑严谨。

**核心代码：**
```cpp
void rmq_init() {
    for (int i = 1; i <= n; i++) f[i][0] = b[i];
    int k = 20;
    for (int j = 1; j <= k; j++)
        for (int i = n; i >= 1; i--) {
            if (i + (1 << (j - 1)) <= n)
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
}

int rmq(int i, int j) {
    int k = log2(j - i + 1);
    return max(f[i][k], f[j - (1 << k) + 1][k]);
}
```

#### 题解2：作者：forgotmyhandle (赞：6)
**星级：4星**
**关键亮点：**
- 使用 set 来管理未使用和正在使用的剃刀，简化了剃刀的选择过程。
- 通过实时移除不符合条件的剃刀，确保剃刀的使用符合要求。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
while (!oks.empty() && *oks.begin() < b[i]) {
    oks.erase(oks.begin());
}
if (oks.count(b[i]) == 0 && st.count(b[i]) >= 1) {
    st.erase(st.find(b[i]));
    oks.insert(b[i]);
} else if (oks.count(b[i]) == 0 && st.count(b[i]) == 0) {
    flag = false;
    break;
}
```

#### 题解3：作者：BFSDFS123 (赞：1)
**星级：4星**
**关键亮点：**
- 使用线段树来查找区间最大值，优化了查询效率。
- 通过枚举每个值 $x$，计算需要的最小剃刀数量，并检查是否足够。
- 代码结构合理，逻辑清晰。

**核心代码：**
```cpp
int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return t[node].maxx;
    int mid = (l + r) >> 1;
    int ans = 0;
    if (ql <= mid) ans = max(ans, query(ls, l, mid, ql, qr));
    if (qr > mid) ans = max(ans, query(rs, mid + 1, r, ql, qr));
    return ans;
}
```

### 最优关键思路或技巧
1. **区间最大值查询**：使用 ST 表或线段树快速查询区间最大值，优化了时间复杂度。
2. **贪心策略**：通过计算每个高度所需的最少剃刀数量，确保剃刀的使用次数最小化。
3. **数据结构优化**：使用 set 或 map 来管理剃刀，简化了剃刀的选择和管理过程。

### 可拓展之处
类似的问题可以扩展到其他区间操作，如区间最小值、区间和等。可以使用类似的数据结构和贪心策略来解决这些问题。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

### 个人心得
在调试过程中，发现区间最大值的查询效率对整体性能影响较大，使用 ST 表或线段树可以显著优化查询速度。此外，贪心策略的正确性需要通过严格的逻辑验证，确保每个步骤都能达到预期效果。

---
处理用时：56.07秒