# 题目信息

# Three Activities

## 题目描述

Winter holidays are coming up. They are going to last for $ n $ days.

During the holidays, Monocarp wants to try all of these activities exactly once with his friends:

- go skiing;
- watch a movie in a cinema;
- play board games.

Monocarp knows that, on the $ i $ -th day, exactly $ a_i $ friends will join him for skiing, $ b_i $ friends will join him for a movie and $ c_i $ friends will join him for board games.

Monocarp also knows that he can't try more than one activity in a single day.

Thus, he asks you to help him choose three distinct days $ x, y, z $ in such a way that the total number of friends to join him for the activities ( $ a_x + b_y + c_z $ ) is maximized.

## 说明/提示

In the first testcase, Monocarp can choose day $ 2 $ for skiing, day $ 1 $ for a movie and day $ 3 $ for board games. This way, $ a_2 = 10 $ friends will join him for skiing, $ b_1 = 10 $ friends will join him for a movie and $ c_3 = 10 $ friends will join him for board games. The total number of friends is $ 30 $ .

In the second testcase, Monocarp can choose day $ 1 $ for skiing, day $ 4 $ for a movie and day $ 2 $ for board games. $ 30 + 20 + 25 = 75 $ friends in total. Note that Monocarp can't choose day $ 1 $ for all activities, because he can't try more than one activity in a single day.

In the third testcase, Monocarp can choose day $ 2 $ for skiing, day $ 3 $ for a movie and day $ 7 $ for board games. $ 19 + 19 + 17 = 55 $ friends in total.

In the fourth testcase, Monocarp can choose day $ 1 $ for skiing, day $ 4 $ for a movie and day $ 9 $ for board games. $ 17 + 19 + 20 = 56 $ friends in total.

## 样例 #1

### 输入

```
4
3
1 10 1
10 1 1
1 1 10
4
30 20 10 1
30 5 15 20
30 25 10 10
10
5 19 12 3 18 18 6 17 10 13
15 17 19 11 16 3 11 17 17 17
1 17 18 10 15 8 17 3 13 12
10
17 5 4 18 12 4 11 2 16 16
8 4 14 19 3 12 6 7 5 16
3 4 8 11 10 8 10 2 20 3```

### 输出

```
30
75
55
56```

# AI分析结果

### 题目中文重写
# 三项活动

## 题目描述
寒假即将来临，假期将持续 $n$ 天。

在假期期间，Monocarp 想和他的朋友们一起尝试以下所有活动各一次：
- 去滑雪；
- 在电影院看电影；
- 玩棋盘游戏。

Monocarp 知道，在第 $i$ 天，分别会有 $a_i$ 个朋友和他一起去滑雪，$b_i$ 个朋友和他一起看电影，$c_i$ 个朋友和他一起玩棋盘游戏。

Monocarp 还知道他不能在同一天尝试多项活动。

因此，他请你帮他选择三个不同的日子 $x$、$y$、$z$，使得参与这些活动的朋友总数（$a_x + b_y + c_z$）最大化。

## 说明/提示
在第一个测试用例中，Monocarp 可以选择第 2 天去滑雪，第 1 天去看电影，第 3 天玩棋盘游戏。这样，会有 $a_2 = 10$ 个朋友和他一起去滑雪，$b_1 = 10$ 个朋友和他一起看电影，$c_3 = 10$ 个朋友和他一起玩棋盘游戏。朋友总数为 30。

在第二个测试用例中，Monocarp 可以选择第 1 天去滑雪，第 4 天去看电影，第 2 天玩棋盘游戏。总共会有 $30 + 20 + 25 = 75$ 个朋友参与。请注意，Monocarp 不能选择第 1 天进行所有活动，因为他不能在同一天尝试多项活动。

在第三个测试用例中，Monocarp 可以选择第 2 天去滑雪，第 3 天去看电影，第 7 天玩棋盘游戏。总共会有 $19 + 19 + 17 = 55$ 个朋友参与。

在第四个测试用例中，Monocarp 可以选择第 1 天去滑雪，第 4 天去看电影，第 9 天玩棋盘游戏。总共会有 $17 + 19 + 20 = 56$ 个朋友参与。

## 样例 #1

### 输入
```
4
3
1 10 1
10 1 1
1 1 10
4
30 20 10 1
30 5 15 20
30 25 10 10
10
5 19 12 3 18 18 6 17 10 13
15 17 19 11 16 3 11 17 17 17
1 17 18 10 15 8 17 3 13 12
10
17 5 4 18 12 4 11 2 16 16
8 4 14 19 3 12 6 7 5 16
3 4 8 11 10 8 10 2 20 3
```

### 输出
```
30
75
55
56
```

### 综合分析与结论
- **思路对比**：三位作者思路相近，均先对三个数组排序，再通过枚举找出满足日期不同且朋友总数最大的组合。hjqhs 和 InversionShadow 枚举较大的几个数，infinite2021 则直接枚举每个数组的前三大数。
- **算法要点**：均使用排序和三重循环枚举，通过比较不同组合的和更新最大值。
- **解决难点**：核心难点是保证所选的三个日期不同，三位作者都通过条件判断解决该问题。

### 题解选择
- **hjqhs（5星）**
    - **关键亮点**：思路清晰，代码规范，注释详细，复杂度分析准确。
    - **核心代码**：
```cpp
sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n), sort(c + 1, c + 1 + n);
per(i, n, max(n - 2, 0) ) per(j, n, max(n - 2, 0) ) per(k, n, max(n - 2, 0) ) {
    if(a[i].second!= b[j].second && a[i].second!= c[k].second && b[j].second!= c[k].second) 
        ans = max(ans, a[i].first + b[j].first + c[k].first);
}
```
    - **核心思想**：对三个数组排序后，从大到小枚举每个数组中最大的三个数，检查日期是否不同，更新最大朋友总数。

### 最优关键思路或技巧
先对三个数组排序，减少不必要的枚举，通过枚举较大的数找到满足条件的最大和。

### 可拓展之处
此问题可拓展到 $k$ 项活动，可使用类似思路，先排序再枚举较大的数，复杂度为 $O(kn \log n + k^3)$。

### 洛谷相似题目推荐
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及路径规划和状态枚举。
2. [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：动态规划枚举路径。
3. [P1434 [SHOI2002] 滑雪](https://www.luogu.com.cn/problem/P1434)：枚举不同路径求最优解。

### 个人心得
题解中未包含个人心得。 

---
处理用时：28.51秒