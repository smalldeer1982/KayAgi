# 题目信息

# 1D Sokoban

## 题目描述

You are playing a game similar to Sokoban on an infinite number line. The game is discrete, so you only consider integer positions on the line.

You start on a position $ 0 $ . There are $ n $ boxes, the $ i $ -th box is on a position $ a_i $ . All positions of the boxes are distinct. There are also $ m $ special positions, the $ j $ -th position is $ b_j $ . All the special positions are also distinct.

In one move you can go one position to the left or to the right. If there is a box in the direction of your move, then you push the box to the next position in that direction. If the next position is taken by another box, then that box is also pushed to the next position, and so on. You can't go through the boxes. You can't pull the boxes towards you.

You are allowed to perform any number of moves (possibly, zero). Your goal is to place as many boxes on special positions as possible. Note that some boxes can be initially placed on special positions.

## 说明/提示

In the first testcase you can go $ 5 $ to the right: the box on position $ 1 $ gets pushed to position $ 6 $ and the box on position $ 5 $ gets pushed to position $ 7 $ . Then you can go $ 6 $ to the left to end up on position $ -1 $ and push a box to $ -2 $ . At the end, the boxes are on positions $ [-2, 6, 7, 11, 15] $ , respectively. Among them positions $ [-2, 6, 7, 15] $ are special, thus, the answer is $ 4 $ .

In the second testcase you can push the box from $ -1 $ to $ -10^9 $ , then the box from $ 1 $ to $ 10^9 $ and obtain the answer $ 2 $ .

The third testcase showcases that you are not allowed to pull the boxes, thus, you can't bring them closer to special positions.

In the fourth testcase all the boxes are already on special positions, so you can do nothing and still obtain the answer $ 3 $ .

In the fifth testcase there are fewer special positions than boxes. You can move either $ 8 $ or $ 9 $ to the right to have some box on position $ 10 $ .

## 样例 #1

### 输入

```
5
5 6
-1 1 5 11 15
-4 -3 -2 6 7 15
2 2
-1 1
-1000000000 1000000000
2 2
-1000000000 1000000000
-1 1
3 5
-1 1 2
-2 -1 1 2 5
2 1
1 2
10```

### 输出

```
4
2
0
3
1```

# AI分析结果

### 题目内容重写
# 1D Sokoban

## 题目描述

你在一个无限数轴上进行一个类似于推箱子的游戏。游戏是离散的，因此你只考虑数轴上的整数位置。

你从位置 $0$ 开始。有 $n$ 个箱子，第 $i$ 个箱子位于位置 $a_i$。所有箱子的位置都是唯一的。还有 $m$ 个特殊位置，第 $j$ 个特殊位置是 $b_j$。所有特殊位置也是唯一的。

每次移动，你可以向左或向右移动一个位置。如果你移动的方向上有箱子，那么你会将该箱子推向下一个位置。如果下一个位置被另一个箱子占据，那么该箱子也会被推向下一个位置，依此类推。你不能穿过箱子，也不能将箱子拉向你。

你可以进行任意次数的移动（包括零次）。你的目标是将尽可能多的箱子放置在特殊位置上。注意，有些箱子可能一开始就已经在特殊位置上了。

## 说明/提示

在第一个测试用例中，你可以向右移动 $5$ 步：将位置 $1$ 的箱子推到位置 $6$，将位置 $5$ 的箱子推到位置 $7$。然后你可以向左移动 $6$ 步，最终停在位置 $-1$，并将一个箱子推到 $-2$。最终，箱子的位置分别为 $[-2, 6, 7, 11, 15]$，其中 $[-2, 6, 7, 15]$ 是特殊位置，因此答案是 $4$。

在第二个测试用例中，你可以将位置 $-1$ 的箱子推到 $-10^9$，然后将位置 $1$ 的箱子推到 $10^9$，得到答案 $2$。

第三个测试用例展示了你不能将箱子拉向特殊位置，因此无法将它们移动到更接近特殊位置的地方。

第四个测试用例中，所有箱子已经位于特殊位置，因此你不需要做任何操作，答案就是 $3$。

第五个测试用例中，特殊位置的数量少于箱子的数量。你可以向右移动 $8$ 或 $9$ 步，使某个箱子位于位置 $10$。

## 样例 #1

### 输入

```
5
5 6
-1 1 5 11 15
-4 -3 -2 6 7 15
2 2
-1 1
-1000000000 1000000000
2 2
-1000000000 1000000000
-1 1
3 5
-1 1 2
-2 -1 1 2 5
2 1
1 2
10```

### 输出

```
4
2
0
3
1```

### 算法分类
贪心

### 题解分析与结论
题目要求将尽可能多的箱子推到特殊位置上，且每次移动只能推动连续的箱子。题解的核心思路是将正数和负数的箱子分开处理，利用前缀和和二分查找来优化计算。

### 所选高分题解
#### 1. 作者：CodyTheWolf (赞：1)
- **星级**：4
- **关键亮点**：利用前缀和和双指针优化计算，正负数分开处理，代码清晰且高效。
- **核心代码**：
```cpp
int ta = lower_bound(a, a + n, 0) - a - 1;
int tb = lower_bound(b, b + m, 0) - b - 1;
while (tb >= 0) {
    while (ta >= 0 && a[ta] >= b[tb]) sum[tb]++, ta--;
    tb--;
}
```
- **实现思想**：通过双指针计算每个特殊位置可以推动的箱子数量，利用前缀和优化计算。

#### 2. 作者：Rui_R (赞：0)
- **星级**：4
- **关键亮点**：使用二分查找优化计算，正负数分开处理，代码结构清晰。
- **核心代码**：
```cpp
int id = std::upper_bound(alpha.begin(),alpha.end(),beta[j]) - alpha.begin();
if(id == 0) continue ;id -- ;
int num = id + 1;int st = beta[j] - num + 1;
int Id = std::lower_bound(beta.begin(),beta.end(),st) - beta.begin();
Id -- ;
answer = max(answer , j - Id + v.back()-v[j]);
```
- **实现思想**：通过二分查找确定每个特殊位置可以推动的箱子数量，利用后缀和优化计算。

### 最优关键思路或技巧
1. **正负数分开处理**：将正数和负数的箱子分开处理，简化问题。
2. **前缀和与二分查找**：利用前缀和和二分查找优化计算，减少时间复杂度。
3. **双指针优化**：使用双指针维护当前可以推动的箱子数量，提高效率。

### 可拓展之处
类似的问题可以扩展到二维推箱子游戏，或者在有障碍物的情况下进行推箱子操作。还可以考虑箱子的重量或推动的代价，增加问题的复杂度。

### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)

### 个人心得摘录
- **CodyTheWolf**：在处理正负数时，注意边界条件，避免数组越界。
- **Rui_R**：二分查找的使用大大减少了计算量，但需要确保序列有序。

---
处理用时：36.95秒