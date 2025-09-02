# 题目信息

# Integers Shop

## 题目描述

The integers shop sells $ n $ segments. The $ i $ -th of them contains all integers from $ l_i $ to $ r_i $ and costs $ c_i $ coins.

Tomorrow Vasya will go to this shop and will buy some segments there. He will get all integers that appear in at least one of bought segments. The total cost of the purchase is the sum of costs of all segments in it.

After shopping, Vasya will get some more integers as a gift. He will get integer $ x $ as a gift if and only if all of the following conditions are satisfied:

- Vasya hasn't bought $ x $ .
- Vasya has bought integer $ l $ that is less than $ x $ .
- Vasya has bought integer $ r $ that is greater than $ x $ .

Vasya can get integer $ x $ as a gift only once so he won't have the same integers after receiving a gift.

For example, if Vasya buys segment $ [2, 4] $ for $ 20 $ coins and segment $ [7, 8] $ for $ 22 $ coins, he spends $ 42 $ coins and receives integers $ 2, 3, 4, 7, 8 $ from these segments. He also gets integers $ 5 $ and $ 6 $ as a gift.

Due to the technical issues only the first $ s $ segments (that is, segments $ [l_1, r_1], [l_2, r_2], \ldots, [l_s, r_s] $ ) will be available tomorrow in the shop.

Vasya wants to get (to buy or to get as a gift) as many integers as possible. If he can do this in differents ways, he selects the cheapest of them.

For each $ s $ from $ 1 $ to $ n $ , find how many coins will Vasya spend if only the first $ s $ segments will be available.

## 说明/提示

In the first test case if $ s = 1 $ then Vasya can buy only the segment $ [2, 4] $ for $ 20 $ coins and get $ 3 $ integers.

The way to get $ 7 $ integers for $ 42 $ coins in case $ s = 2 $ is described in the statement.

In the second test case note, that there can be the same segments in the shop.

## 样例 #1

### 输入

```
3
2
2 4 20
7 8 22
2
5 11 42
5 11 42
6
1 4 4
5 8 9
7 8 7
2 10 252
1 11 271
1 10 1```

### 输出

```
20
42
42
42
4
13
11
256
271
271```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

整数商店出售 $n$ 个区间。第 $i$ 个区间包含从 $l_i$ 到 $r_i$ 的所有整数，并且花费 $c_i$ 个硬币。

明天 Vasya 将去这家商店购买一些区间。他将获得所有出现在至少一个购买区间中的整数。购买的总成本是所有购买区间的成本之和。

购物后，Vasya 还会获得一些额外的整数作为礼物。他将获得整数 $x$ 作为礼物，当且仅当满足以下所有条件：

- Vasya 没有购买 $x$。
- Vasya 购买了一个小于 $x$ 的整数 $l$。
- Vasya 购买了一个大于 $x$ 的整数 $r$。

Vasya 只能获得一次整数 $x$ 作为礼物，因此他不会在收到礼物后拥有相同的整数。

例如，如果 Vasya 购买了区间 $[2, 4]$ 花费 $20$ 个硬币，以及区间 $[7, 8]$ 花费 $22$ 个硬币，他总共花费了 $42$ 个硬币，并从这些区间中获得了整数 $2, 3, 4, 7, 8$。他还获得了整数 $5$ 和 $6$ 作为礼物。

由于技术问题，明天商店中只有前 $s$ 个区间（即区间 $[l_1, r_1], [l_2, r_2], \ldots, [l_s, r_s]$）可用。

Vasya 希望获得（购买或作为礼物）尽可能多的整数。如果他能以不同的方式实现这一点，他会选择其中最便宜的方式。

对于每个 $s$ 从 $1$ 到 $n$，找出如果只有前 $s$ 个区间可用时，Vasya 将花费多少硬币。

#### 说明/提示

在第一个测试用例中，如果 $s = 1$，那么 Vasya 只能购买区间 $[2, 4]$ 花费 $20$ 个硬币，并获得 $3$ 个整数。

在 $s = 2$ 的情况下，获得 $7$ 个整数花费 $42$ 个硬币的方式在题目描述中已经说明。

在第二个测试用例中，注意商店中可能存在相同的区间。

#### 样例 #1

##### 输入

```
3
2
2 4 20
7 8 22
2
5 11 42
5 11 42
6
1 4 4
5 8 9
7 8 7
2 10 252
1 11 271
1 10 1
```

##### 输出

```
20
42
42
42
4
13
11
256
271
271
```

### 算法分类
贪心

### 题解分析与结论

所有题解都采用了贪心算法的思路，核心思想是维护当前最左端和最右端的区间，并记录它们的最小成本。同时，如果存在一个区间能够覆盖整个范围，则直接使用该区间的成本。最终答案是在购买两个端点区间和购买一个覆盖整个区间的区间之间取最小值。

### 所选高分题解

#### 题解1：作者 qfpjm (5星)
**关键亮点**：
- 思路清晰，代码简洁。
- 通过维护最左端和最右端的区间成本，以及覆盖整个区间的成本，实现了高效的贪心策略。
- 代码可读性强，逻辑清晰。

**核心代码**：
```cpp
int l = INT_MAX, r = 0;
int lans = INT_MAX, rans = INT_MAX, ans = INT_MAX;
for (int i = 1 ; i <= n ; i ++) {
    int li, ri, ci;
    cin >> li >> ri >> ci;
    if (l > li) {
        l = li;
        lans = ci;
        ans = INT_MAX;
    }
    if (l == li) {
        lans = min(lans, ci);
    }
    if (r < ri) {
        r = ri;
        rans = ci;
        ans = INT_MAX;
    }
    if (r == ri) {
        rans = min(rans, ci);
    }
    if (li == l && ri == r) {
        ans = min(ans, ci);
    }
    cout << min(ans, lans + rans) << endl;
}
```

#### 题解2：作者 XL4453 (4星)
**关键亮点**：
- 解题思路与题解1类似，但代码实现略有不同。
- 通过维护最左端和最右端的区间成本，以及覆盖整个区间的成本，实现了贪心策略。
- 代码逻辑清晰，但变量命名稍显复杂。

**核心代码**：
```cpp
int ll = 2147483647, rr = 0;
int lans, rans, aans = 2147483647;
for (int i = 1; i <= n; i++) {
    if (ll > l[i]) {
        ll = l[i];
        lans = c[i];
        aans = 2147483647;
    }
    if (ll == l[i]) {
        lans = min(lans, c[i]);
    }
    if (rr < r[i]) {
        rr = r[i];
        rans = c[i];
        aans = 2147483647;
    }
    if (rr == r[i]) {
        rans = min(rans, c[i]);
    }
    if (ll == l[i] && rr == r[i]) {
        aans = min(aans, c[i]);
    }
    printf("%d\n", min(lans + rans, aans));
}
```

### 最优关键思路或技巧
- **贪心策略**：通过维护最左端和最右端的区间成本，以及覆盖整个区间的成本，实现了高效的贪心策略。
- **代码优化**：通过不断更新最小成本，避免重复计算，提高了代码效率。

### 可拓展之处
- 类似的问题可以扩展到多维空间，例如在二维平面上选择矩形区域来覆盖最大范围。
- 可以进一步优化算法，考虑区间的重叠情况，减少不必要的计算。

### 推荐相似题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录
- **qfpjm**：通过维护最左端和最右端的区间成本，以及覆盖整个区间的成本，实现了高效的贪心策略。代码简洁，逻辑清晰。
- **XL4453**：解题思路与题解1类似，但代码实现略有不同。通过维护最左端和最右端的区间成本，以及覆盖整个区间的成本，实现了贪心策略。

---
处理用时：46.55秒