# 题目信息

# Buying Jewels

## 题目描述

[Nightwish feat. Jonsu - Erämaan Viimeinen](https://youtu.be/QYlFn5q_UQk)

ඞ



Alice has $ n $ coins and wants to shop at Bob's jewelry store. Today, although Bob has not set up the store yet, Bob wants to make sure Alice will buy exactly $ k $ jewels. To set up the store, Bob can erect at most $ 60 $ stalls (each containing an unlimited amount of jewels) and set the price per jewel for each stall to be an integer number of coins between $ 1 $ and $ 10^{18} $ .

Fortunately, Bob knows that Alice buys greedily: and she will go to stall $ 1 $ , buy as many jewels as possible, then go to stall $ 2 $ , buy as many jewels as possible, and so on until the last stall. Knowing this, Bob can choose the number of stalls to set up, as well as set the price for each stall so that Alice buys exactly $ k $ jewels. Help Bob fulfill the task, or determine if it is impossible to do so.

Note that Alice does not need to spend all her coins.

## 说明/提示

In the first test case, at the first stall, Alice buys $ 3 $ jewels and is left with $ 1 $ coin. This is not enough to buy any jewels for any of the remaining stalls, so Alice buys exactly $ 3 $ jewels at the end.

In the third test case,

- At the first stall, Alice buys $ 1 $ jewel and is left with $ 127 $ coins.
- At the second stall, Alice buys $ 1 $ jewel and is left with $ 63 $ coins.
- At the third stall, Alice buys $ 1 $ jewel and is left with $ 31 $ coins.
- At the fourth stall, Alice buys $ 1 $ jewel and is left with $ 15 $ coins.
- At the fifth stall, Alice buys $ 1 $ jewel and is left with $ 7 $ coins.
- At the sixth stall, Alice buys $ 1 $ jewel and is left with $ 3 $ coins.
- At the seventh stall, Alice buys $ 1 $ jewel and is left with $ 1 $ coin.
- At the eighth stall, Alice buys $ 1 $ jewel and is left with $ 0 $ coins.

 Therefore, Alice buys exactly $ 8 $ jewels in total.

## 样例 #1

### 输入

```
3
7 3
6 4
255 8```

### 输出

```
YES
10
2 3 4 5 6 7 8 9 10 11
NO
YES
8
128 64 32 16 8 4 2 1```

# AI分析结果

### 题目内容重写

#### 购买珠宝

**题目描述**

Alice 有 $n$ 个硬币，想在 Bob 的珠宝店购物。今天，虽然 Bob 还没有开店，但 Bob 希望确保 Alice 会购买恰好 $k$ 件珠宝。为了开店，Bob 最多可以设置 $60$ 个摊位（每个摊位包含无限数量的珠宝），并将每个摊位的每件珠宝的价格设置为 $1$ 到 $10^{18}$ 之间的整数。

幸运的是，Bob 知道 Alice 的购买方式是贪心的：她会先去第一个摊位，购买尽可能多的珠宝，然后去第二个摊位，购买尽可能多的珠宝，依此类推，直到最后一个摊位。Bob 可以根据这一点选择摊位的数量以及每个摊位的价格，使得 Alice 购买恰好 $k$ 件珠宝。帮助 Bob 完成任务，或确定是否无法做到。

注意：Alice 不需要花光所有的硬币。

**说明/提示**

在第一个测试用例中，Alice 在第一个摊位购买了 $3$ 件珠宝，剩下 $1$ 个硬币。这不足以购买任何其他摊位的珠宝，因此 Alice 最终购买了恰好 $3$ 件珠宝。

在第三个测试用例中，Alice 在第一个摊位购买了 $1$ 件珠宝，剩下 $127$ 个硬币；在第二个摊位购买了 $1$ 件珠宝，剩下 $63$ 个硬币；依此类推，直到最后一个摊位购买了 $1$ 件珠宝，剩下 $0$ 个硬币。因此，Alice 总共购买了恰好 $8$ 件珠宝。

**样例 #1**

**输入**
```
3
7 3
6 4
255 8
```

**输出**
```
YES
10
2 3 4 5 6 7 8 9 10 11
NO
YES
8
128 64 32 16 8 4 2 1
```

### 算法分类
构造、贪心

### 综合分析与结论

这道题的核心是通过构造摊位的价格，使得 Alice 在贪心购买的情况下恰好购买 $k$ 件珠宝。题解主要集中在如何通过设置摊位的价格来满足这一条件，特别是通过分析 $n$ 和 $k$ 的关系来判断是否有解，并给出具体的构造方法。

大多数题解都采用了类似的思路：首先判断 $k$ 是否大于 $n$，如果是则无解；如果 $k$ 等于 $n$，则只需设置一个价格为 $1$ 的摊位；如果 $k$ 小于 $n$，则通过设置两个摊位，第一个摊位的价格为 $n - k + 1$，第二个摊位的价格为 $1$，来确保 Alice 购买恰好 $k$ 件珠宝。此外，题解还讨论了当 $k$ 大于 $\frac{n}{2}$ 时的特殊情况，并证明了在这种情况下除了 $n = 2k - 1$ 外均无解。

### 所选题解

#### 题解作者：HHH6666666666 (赞：4)
**星级：★★★★★**
**关键亮点：**
- 通过分类讨论 $k$ 与 $n$ 的关系，清晰地给出了构造方法。
- 提供了详细的证明，解释了为什么在某些情况下无解。
- 代码简洁明了，直接实现了分类讨论的结果。

**个人心得：**
“像这种构造没思路时赶紧小数据打表。把所有方案都看一遍就大概会了。”

**核心代码：**
```cpp
void solve() {
    ll n, k; cin >> n >> k;
    if (n == k) {
        cout << "YES" << endl << 1 << endl << 1 << endl;
    }
    else if (k * 2 <= n) {
        cout << "YES" << endl << 2 << endl << n - k + 1 << ' ' << 1 << endl;
    }
    else if ((n & 1) && 2 * k - 1 == n) {
        cout << "YES" << endl << 2 << endl << 2 << ' ' << 1 << endl;
    }
    else cout << "NO" << endl;
    return;
}
```

#### 题解作者：Day_Tao (赞：2)
**星级：★★★★**
**关键亮点：**
- 详细解释了构造思路，特别是通过设置第一个摊位的价格来控制 Alice 的购买行为。
- 提供了对 $k$ 与 $n$ 关系的深入分析，并给出了具体的构造方案。

**核心代码：**
```cpp
signed main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &n, &k);
        if (n == k) printf ("YES\n1\n1\n");
        else if (k * 2 - 2 < n || n < k) printf ("YES\n2\n%lld 1\n", n - k + 1);
        else printf ("NO\n");
    }
    return 0;
}
```

#### 题解作者：fujiayu (赞：0)
**星级：★★★★**
**关键亮点：**
- 通过贪心策略，详细解释了如何通过设置摊位的价格来确保 Alice 购买恰好 $k$ 件珠宝。
- 提供了对 $k$ 与 $n$ 关系的证明，并给出了具体的构造方案。

**核心代码：**
```cpp
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T; cin >> T;
    while(T --) {
        cin >> n >> k;
        if(n == k)
            cout << "YES\n1\n1\n";
        else if((n + 1) / 2 < k)
            cout << "NO\n";
        else
            cout << "YES\n2\n", 
            cout << n - k + 1 << " 1\n";
    }
    return 0;
}
```

### 最优关键思路或技巧
1. **分类讨论**：通过分析 $k$ 与 $n$ 的关系，判断是否有解，并给出具体的构造方法。
2. **贪心策略**：通过设置摊位的价格，确保 Alice 在贪心购买的情况下恰好购买 $k$ 件珠宝。
3. **构造方法**：在 $k$ 小于 $n$ 的情况下，通过设置两个摊位，第一个摊位的价格为 $n - k + 1$，第二个摊位的价格为 $1$，来确保 Alice 购买恰好 $k$ 件珠宝。

### 可拓展之处
这类题目可以通过类似的贪心策略和构造方法来解决，特别是在需要控制某种行为或结果的情况下。类似的题目可以考察如何通过设置参数或条件来达到特定的目标。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)

---
处理用时：53.34秒