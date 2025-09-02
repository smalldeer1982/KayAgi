# 题目信息

# Search in Parallel

## 题目描述

Suppose you have $ n $ boxes. The $ i $ -th box contains infinitely many balls of color $ i $ . Sometimes you need to get a ball with some specific color; but you're too lazy to do it yourself.

You have bought two robots to retrieve the balls for you. Now you have to program them. In order to program the robots, you have to construct two lists $ [a_1, a_2, \dots, a_k] $ and $ [b_1, b_2, \dots, b_{n-k}] $ , where the list $ a $ represents the boxes assigned to the first robot, and the list $ b $ represents the boxes assigned to the second robot. Every integer from $ 1 $ to $ n $ must be present in exactly one of these lists.

When you request a ball with color $ x $ , the robots work as follows. Each robot looks through the boxes that were assigned to that robot, in the order they appear in the list. The first robot spends $ s_1 $ seconds analyzing the contents of a box; the second robot spends $ s_2 $ . As soon as one of the robots finds the box with balls of color $ x $ (and analyzes its contents), the search ends. The search time is the number of seconds from the beginning of the search until one of the robots finishes analyzing the contents of the $ x $ -th box. If a robot analyzes the contents of all boxes assigned to it, it stops searching.

For example, suppose $ s_1 = 2 $ , $ s_2 = 3 $ , $ a = [4, 1, 5, 3, 7] $ , $ b = [2, 6] $ . If you request a ball with color $ 3 $ , the following happens:

- initially, the first robot starts analyzing the box $ 4 $ , and the second robot starts analyzing the box $ 2 $ ;
- at the end of the $ 2 $ -nd second, the first robot finishes analyzing the box $ 4 $ . It is not the box you need, so the robot continues with the box $ 1 $ ;
- at the end of the $ 3 $ -rd second, the second robot finishes analyzing the box $ 2 $ . It is not the box you need, so the robot continues with the box $ 6 $ ;
- at the end of the $ 4 $ -th second, the first robot finishes analyzing the box $ 1 $ . It is not the box you need, so the robot continues with the box $ 5 $ ;
- at the end of the $ 6 $ -th second, the first robot finishes analyzing the box $ 5 $ . It is not the box you need, so the robot continues with the box $ 3 $ . At the same time, the second robot finishes analyzing the box $ 6 $ . It is not the box you need, and the second robot has analyzed all the boxes in its list, so that robot stops searching;
- at the end of the $ 8 $ -th second, the first robot finishes analyzing the box $ 3 $ . It is the box you need, so the search ends;
- so, the search time is $ 8 $ seconds.

You know that you are going to request a ball of color $ 1 $ $ r_1 $ times, a ball of color $ 2 $ $ r_2 $ times, and so on. You want to construct the lists $ a $ and $ b $ for the robots in such a way that the total search time over all requests is the minimum possible.

## 样例 #1

### 输入

```
3
7 3 1
8 6 4 4 4 1 7
5 1 10
1 1 1 1 1
8 1 1
4 5 6 8 1 7 3 2```

### 输出

```
2 5 6
5 1 7 2 4 3
5 4 3 5 2 1
0
4 4 2 7 5
4 6 3 1 8```

# AI分析结果

### 中文题目重写

# 并行搜索

## 题目描述

假设你有 $ n $ 个盒子。第 $ i $ 个盒子里有无限多个颜色为 $ i $ 的球。有时你需要获取某个特定颜色的球；但你太懒了，不想自己动手。

你买了两个机器人来帮你取球。现在你需要为它们编程。为了编程，你需要构造两个列表 $ [a_1, a_2, \dots, a_k] $ 和 $ [b_1, b_2, \dots, b_{n-k}] $，其中列表 $ a $ 表示分配给第一个机器人的盒子，列表 $ b $ 表示分配给第二个机器人的盒子。每个从 $ 1 $ 到 $ n $ 的整数必须恰好出现在其中一个列表中。

当你请求一个颜色为 $ x $ 的球时，机器人会按照以下方式工作。每个机器人会按照列表中出现的顺序检查分配给它的盒子。第一个机器人花费 $ s_1 $ 秒分析一个盒子的内容；第二个机器人花费 $ s_2 $ 秒。一旦其中一个机器人找到颜色为 $ x $ 的盒子（并分析其内容），搜索结束。搜索时间是从搜索开始到其中一个机器人完成分析 $ x $ 号盒子内容所花费的秒数。如果一个机器人分析完所有分配给它的盒子，它会停止搜索。

例如，假设 $ s_1 = 2 $，$ s_2 = 3 $，$ a = [4, 1, 5, 3, 7] $，$ b = [2, 6] $。如果你请求一个颜色为 $ 3 $ 的球，会发生以下情况：

- 初始时，第一个机器人开始分析盒子 $ 4 $，第二个机器人开始分析盒子 $ 2 $；
- 在第 $ 2 $ 秒结束时，第一个机器人完成分析盒子 $ 4 $。这不是你需要的盒子，所以机器人继续分析盒子 $ 1 $；
- 在第 $ 3 $ 秒结束时，第二个机器人完成分析盒子 $ 2 $。这不是你需要的盒子，所以机器人继续分析盒子 $ 6 $；
- 在第 $ 4 $ 秒结束时，第一个机器人完成分析盒子 $ 1 $。这不是你需要的盒子，所以机器人继续分析盒子 $ 5 $；
- 在第 $ 6 $ 秒结束时，第一个机器人完成分析盒子 $ 5 $。这不是你需要的盒子，所以机器人继续分析盒子 $ 3 $。同时，第二个机器人完成分析盒子 $ 6 $。这不是你需要的盒子，且第二个机器人已经分析完所有分配给它的盒子，所以它停止搜索；
- 在第 $ 8 $ 秒结束时，第一个机器人完成分析盒子 $ 3 $。这是你需要的盒子，所以搜索结束；
- 因此，搜索时间为 $ 8 $ 秒。

你知道你会请求颜色为 $ 1 $ 的球 $ r_1 $ 次，颜色为 $ 2 $ 的球 $ r_2 $ 次，依此类推。你希望构造列表 $ a $ 和 $ b $，使得所有请求的总搜索时间最小。

### 算法分类
贪心

### 题解分析与结论

所有题解的核心思路都是基于贪心算法，将请求次数较多的盒子优先分配给搜索时间较短的机器人。具体来说，题解们首先将盒子按照请求次数从大到小排序，然后根据当前两个机器人的搜索时间决定将盒子分配给哪个机器人。

#### 题解对比
1. **plank_black**：思路清晰，代码简洁，直接计算当前两个机器人的搜索时间并选择较小的一个。代码可读性较好，但未处理多测清空的问题。
2. **zeekliu**：思路与plank_black类似，但代码实现更为抽象，使用了数组记录搜索时间，边算边放。代码可读性稍差，但逻辑正确。
3. **Sun_pirf**：思路与上述题解一致，代码实现较为规范，使用了结构体存储盒子的信息，并进行了多测清空处理。代码可读性较好，逻辑清晰。
4. **Special_Tony**：思路与上述题解一致，代码实现简洁，使用了pair存储盒子的信息，逻辑清晰，代码可读性较好。

### 评分较高的题解

1. **plank_black**（4星）
   - 关键亮点：思路清晰，代码简洁，直接计算当前两个机器人的搜索时间并选择较小的一个。
   - 代码核心：
     ```cpp
     for(int i = 1; i <= n; i++) {
         if(cnt1 * s1 > cnt2 * s2) {
             vec2.push_back(A[i]);
             cnt2++;
         } else {
             vec1.push_back(A[i]);
             cnt1++;
         }
     }
     ```

2. **Sun_pirf**（4星）
   - 关键亮点：代码实现规范，使用了结构体存储盒子的信息，并进行了多测清空处理。
   - 代码核心：
     ```cpp
     for (int i=1;i<=n;i++){
         if (cnt1*s1<cnt2*s2){
             ans1[cnt1]=ball[i].id;
             cnt1++;
         }
         else{
             ans2[cnt2]=ball[i].id;
             cnt2++;
         }
     }
     ```

3. **Special_Tony**（4星）
   - 关键亮点：代码实现简洁，使用了pair存储盒子的信息，逻辑清晰。
   - 代码核心：
     ```cpp
     for (int i = 1; i <= n; ++ i)
         if (m1 * s1 < m2 * s2)
             ans1[m1] = a[i].second, ++ m1;
         else
             ans2[m2] = a[i].second, ++ m2;
     ```

### 最优关键思路
将盒子按照请求次数从大到小排序，然后根据当前两个机器人的搜索时间决定将盒子分配给哪个机器人，以最小化总搜索时间。

### 可拓展之处
类似的问题可以扩展到多个机器人的情况，或者扩展到不同的搜索时间模型。此外，可以考虑动态调整机器人的搜索顺序以进一步优化总搜索时间。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：41.89秒