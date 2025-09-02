# 题目信息

# Vika and the Bridge

## 题目描述

In the summer, Vika likes to visit her country house. There is everything for relaxation: comfortable swings, bicycles, and a river.

There is a wooden bridge over the river, consisting of $ n $ planks. It is quite old and unattractive, so Vika decided to paint it. And in the shed, they just found cans of paint of $ k $ colors.

After painting each plank in one of $ k $ colors, Vika was about to go swinging to take a break from work. However, she realized that the house was on the other side of the river, and the paint had not yet completely dried, so she could not walk on the bridge yet.

In order not to spoil the appearance of the bridge, Vika decided that she would still walk on it, but only stepping on planks of the same color. Otherwise, a small layer of paint on her sole will spoil the plank of another color. Vika also has a little paint left, but it will only be enough to repaint one plank of the bridge.

Now Vika is standing on the ground in front of the first plank. To walk across the bridge, she will choose some planks of the same color (after repainting), which have numbers $ 1 \le i_1 < i_2 < \ldots < i_m \le n $ (planks are numbered from $ 1 $ from left to right). Then Vika will have to cross $ i_1 - 1, i_2 - i_1 - 1, i_3 - i_2 - 1, \ldots, i_m - i_{m-1} - 1, n - i_m $ planks as a result of each of $ m + 1 $ steps.

Since Vika is afraid of falling, she does not want to take too long steps. Help her and tell her the minimum possible maximum number of planks she will have to cross in one step, if she can repaint one (or zero) plank a different color while crossing the bridge.

## 说明/提示

In the first test case, Vika can repaint the plank in the middle in color $ 1 $ and walk across the bridge without stepping over any planks.

In the second test case, Vika can repaint the plank in the middle in color $ 2 $ and walk across the bridge, stepping over only one plank each time.

In the third test case, Vika can repaint the penultimate plank in color $ 2 $ and walk across the bridge, stepping only on planks with numbers $ 2 $ and $ 5 $ . Then Vika will have to step over $ 1 $ , $ 2 $ and $ 1 $ plank each time she steps, so the answer is $ 2 $ .

In the fourth test case, Vika can simply walk across the bridge without repainting it, stepping over two planks each time, walking on planks of color $ 3 $ .

In the fifth test case, Vika can simply walk across the bridge without repainting it, without stepping over any planks.

## 样例 #1

### 输入

```
5
5 2
1 1 2 1 1
7 3
1 2 3 3 3 2 1
6 6
1 2 3 4 5 6
8 4
1 2 3 4 2 3 1 4
3 1
1 1 1```

### 输出

```
0
1
2
2
0```

# AI分析结果

### 题目内容重写

在夏天，Vika喜欢去她的乡间别墅度假。那里有舒适的秋千、自行车和一条河流。

河上有一座由 $n$ 块木板组成的木桥。这座桥相当老旧且不美观，因此Vika决定给它刷漆。在棚子里，他们正好找到了 $k$ 种颜色的油漆。

在将每块木板刷成 $k$ 种颜色之一后，Vika准备去荡秋千休息一下。然而，她意识到房子在河的另一边，而油漆还没有完全干透，所以她暂时还不能走过桥。

为了不破坏桥的外观，Vika决定她仍然会走过桥，但只能踩在同一种颜色的木板上。否则，她鞋底上的一小层油漆会弄脏另一种颜色的木板。Vika还剩下一点油漆，但只够重新刷一块桥上的木板。

现在，Vika站在第一块木板前的地面上。为了走过桥，她会选择一些同一种颜色的木板（在重新刷漆后），这些木板的编号为 $1 \le i_1 < i_2 < \ldots < i_m \le n$（木板从左到右编号为 $1$）。然后，Vika将不得不跨过 $i_1 - 1, i_2 - i_1 - 1, i_3 - i_2 - 1, \ldots, i_m - i_{m-1} - 1, n - i_m$ 块木板，作为每一步的结果。

由于Vika害怕摔倒，她不想跨过太多的木板。请帮助她，告诉她在一跨中必须跨过的木板的最大数量的最小值，如果她可以在过桥时重新刷一块（或零块）木板为另一种颜色。

### 算法分类
贪心

### 题解分析与结论

这道题的核心在于通过贪心策略，找到一种颜色，使得在同种颜色的木板之间，跨过的木板数量的最大值最小化。由于Vika可以重新刷一块木板，因此我们需要考虑如何通过改变一块木板的颜色来减少最大跨步。

大多数题解都采用了类似的思路：对于每种颜色，计算其木板之间的最大跨步和次大跨步，然后通过改变最大跨步中间的一块木板颜色，将最大跨步减半，最终取所有颜色的最小跨步。

### 评分较高的题解

#### 题解1：作者：wangjingtian1234 (赞：7)
**星级：4.5**
**关键亮点：**
- 清晰地解释了贪心策略，特别是如何处理最大跨步和次大跨步。
- 代码结构清晰，逻辑严密，处理了多组数据的情况。
- 特别强调了如何处理第 $n+1$ 块木板的跨步问题。

**核心代码：**
```cpp
for (int i = 1; i <= n; i++) {
    if (i - las[a[i]] - 1 > Max[a[i]]) {
        ciMax[a[i]] = Max[a[i]];
        Max[a[i]] = i - las[a[i]] - 1;
    }
    else if (i - las[a[i]] - 1 > ciMax[a[i]]) ciMax[a[i]] = i - las[a[i]] - 1;
    las[a[i]] = i;
}
```

#### 题解2：作者：RAINBOW_ddd (赞：5)
**星级：4**
**关键亮点：**
- 代码简洁，逻辑清晰，直接计算每种颜色的最大跨步和次大跨步。
- 特别强调了如何处理最后一块木板的跨步问题。

**核心代码：**
```cpp
for (int i = 1; i <= N; i++) {
    if (i - pre[num[i]] - 1 > Max[num[i]]) SecMax[num[i]] = Max[num[i]], Max[num[i]] = i - pre[num[i]] - 1;
    else if (i - pre[num[i]] - 1 > SecMax[num[i]]) SecMax[num[i]] = i - pre[num[i]] - 1;
    pre[num[i]] = i;
}
```

#### 题解3：作者：HNOIRPplusplus (赞：4)
**星级：4**
**关键亮点：**
- 详细解释了贪心策略，特别是如何通过改变最大跨步中间的木板的颜色来减少跨步。
- 代码结构清晰，逻辑严密，处理了多组数据的情况。

**核心代码：**
```cpp
for (int i = 1; i <= n; i++) {
    int dis = i - last[a[i]] - 1;
    if (dis > maxxx[a[i]]) {
        maxx[a[i]] = maxxx[a[i]];
        maxxx[a[i]] = dis;
    } else if (dis > maxx[a[i]]) {
        maxx[a[i]] = dis;
    }
    last[a[i]] = i;
}
```

### 最优关键思路或技巧
1. **贪心策略**：通过改变最大跨步中间的一块木板颜色，将最大跨步减半，从而减少最大跨步。
2. **处理边界**：特别处理第 $n+1$ 块木板的跨步问题，确保所有颜色的跨步都被正确计算。
3. **多组数据处理**：在代码中清空数组，确保每组数据独立处理。

### 可拓展之处
这种贪心策略可以应用于类似的问题，例如在路径规划中，通过改变某些节点的属性来优化路径的最大跨步。类似的问题还可以扩展到多步改变的情况，或者在不同约束条件下的优化问题。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：34.91秒