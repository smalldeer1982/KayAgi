# 题目信息

# New Theatre Square

## 题目描述

You might have remembered Theatre square from the [problem 1A](https://codeforces.com/problemset/problem/1/A). Now it's finally getting repaved.

The square still has a rectangular shape of $ n \times m $ meters. However, the picture is about to get more complicated now. Let $ a_{i,j} $ be the $ j $ -th square in the $ i $ -th row of the pavement.

You are given the picture of the squares:

- if $ a_{i,j} =  $ "\*", then the $ j $ -th square in the $ i $ -th row should be black;
- if $ a_{i,j} =  $ ".", then the $ j $ -th square in the $ i $ -th row should be white.

The black squares are paved already. You have to pave the white squares. There are two options for pavement tiles:

- $ 1 \times 1 $ tiles — each tile costs $ x $ burles and covers exactly $ 1 $ square;
- $ 1 \times 2 $ tiles — each tile costs $ y $ burles and covers exactly $ 2 $ adjacent squares of the same row. Note that you are not allowed to rotate these tiles or cut them into $ 1 \times 1 $ tiles.

You should cover all the white squares, no two tiles should overlap and no black squares should be covered by tiles.

What is the smallest total price of the tiles needed to cover all the white squares?

## 说明/提示

In the first testcase you are required to use a single $ 1 \times 1 $ tile, even though $ 1 \times 2 $ tile is cheaper. So the total price is $ 10 $ burles.

In the second testcase you can either use two $ 1 \times 1 $ tiles and spend $ 20 $ burles or use a single $ 1 \times 2 $ tile and spend $ 1 $ burle. The second option is cheaper, thus the answer is $ 1 $ .

The third testcase shows that you can't rotate $ 1 \times 2 $ tiles. You still have to use two $ 1 \times 1 $ tiles for the total price of $ 20 $ .

In the fourth testcase the cheapest way is to use $ 1 \times 1 $ tiles everywhere. The total cost is $ 6 \cdot 3 = 18 $ .

## 样例 #1

### 输入

```
4
1 1 10 1
.
1 2 10 1
..
2 1 10 1
.
.
3 3 3 7
..*
*..
.*.```

### 输出

```
10
1
20
18```

# AI分析结果

### 题目内容
# 新剧院广场

## 题目描述
你可能还记得[问题1A](https://codeforces.com/problemset/problem/1/A)中的剧院广场。现在它终于要重新铺设了。

广场仍然是一个\(n×m\)米的矩形形状。然而，现在情况变得更复杂了。设\(a_{i,j}\)为路面第\(i\)行第\(j\)个方块。

你会得到方块的布局：
 - 如果\(a_{i,j} = \)“\(*\)”，那么第\(i\)行第\(j\)个方块应该是黑色的；
 - 如果\(a_{i,j} = \)“\(.\)”，那么第\(i\)行第\(j\)个方块应该是白色的。

黑色方块已经铺设好了。你需要铺设白色方块。有两种铺设瓷砖可供选择：
 - \(1×1\)的瓷砖 - 每块瓷砖花费\(x\)卢布，恰好覆盖\(1\)个方块；
 - \(1×2\)的瓷砖 - 每块瓷砖花费\(y\)卢布，恰好覆盖同一行中相邻的\(2\)个方块。注意，你不允许旋转这些瓷砖或将它们切割成\(1×1\)的瓷砖。

你应该覆盖所有白色方块，任何两块瓷砖都不应重叠，并且黑色方块不应被瓷砖覆盖。

覆盖所有白色方块所需瓷砖的最小总价格是多少？

## 说明/提示
在第一个测试用例中，即使\(1×2\)的瓷砖更便宜，你也需要使用单个\(1×1\)的瓷砖。所以总价格是\(10\)卢布。

在第二个测试用例中，你可以使用两块\(1×1\)的瓷砖，花费\(20\)卢布，或者使用单个\(1×2\)的瓷砖，花费\(1\)卢布。第二种选择更便宜，因此答案是\(1\)。

第三个测试用例表明你不能旋转\(1×2\)的瓷砖。你仍然需要使用两块\(1×1\)的瓷砖，总价格为\(20\)。

在第四个测试用例中，最便宜的方法是到处都使用\(1×1\)的瓷砖。总成本是\(6×3 = 18\)。

## 样例 #1
### 输入
```
4
1 1 10 1
.
1 2 10 1
..
2 1 10 1
.
.
3 3 3 7
..*
*..
.*.
```
### 输出
```
10
1
20
18
```
### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕两种思路展开。一种是贪心策略，根据\(2x\)与\(y\)的大小关系进行判断。若\(2x \leq y\)，则全部使用\(1×1\)的瓷砖；若\(2x > y\)，则对于每行，尽量使用\(1×2\)的瓷砖，剩余单个白色方块用\(1×1\)瓷砖。另一种是动态规划思路，通过定义状态\(f_i\)（或\(f_{i,j}\)）表示当前行前\(i\)列（或第\(i\)行前\(j\)列）所需最小花费，根据当前方块颜色及前一方块颜色进行状态转移。解决难点在于如何合理利用两种瓷砖的价格关系以及每行方块的连续性来找到最小花费。

### 通用建议与扩展思路
对于此类问题，关键在于理解不同瓷砖组合的性价比，并根据题目条件找到合适的策略。可以拓展到不同形状瓷砖、不同放置规则、不同价格关系的类似铺设问题。在解决这类问题时，要善于分析不同情况，选择合适的算法。如果问题规模较小且情况复杂，模拟可能是个好方法；若问题具有明显的子问题结构，动态规划可能更合适；若能根据某些条件直接确定最优选择，贪心算法则更为高效。

### 洛谷相似题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
 - [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937) 

---
处理用时：29.75秒