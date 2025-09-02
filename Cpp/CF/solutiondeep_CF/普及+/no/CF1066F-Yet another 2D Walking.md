# 题目信息

# Yet another 2D Walking

## 题目描述

Maksim walks on a Cartesian plane. Initially, he stands at the point $ (0, 0) $ and in one move he can go to any of four adjacent points (left, right, up, down). For example, if Maksim is currently at the point $ (0, 0) $ , he can go to any of the following points in one move:

- $ (1, 0) $ ;
- $ (0, 1) $ ;
- $ (-1, 0) $ ;
- $ (0, -1) $ .

There are also $ n $ distinct key points at this plane. The $ i $ -th point is $ p_i = (x_i, y_i) $ . It is guaranteed that $ 0 \le x_i $ and $ 0 \le y_i $ and there is no key point $ (0, 0) $ .

Let the first level points be such points that $ max(x_i, y_i) = 1 $ , the second level points be such points that $ max(x_i, y_i) = 2 $ and so on. Maksim wants to visit all the key points. But he shouldn't visit points of level $ i + 1 $ if he does not visit all the points of level $ i $ . He starts visiting the points from the minimum level of point from the given set.

The distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ where $ |v| $ is the absolute value of $ v $ .

Maksim wants to visit all the key points in such a way that the total distance he walks will be minimum possible. Your task is to find this distance.

If you are Python programmer, consider using PyPy instead of Python when you submit your code.

## 说明/提示

The picture corresponding to the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1066F/896df4e9ea79d5fd52a150516ea0bd817a9ff17d.png)

There is one of the possible answers of length $ 15 $ .

The picture corresponding to the second example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1066F/df4d50be023876f6bcdf0e6166cef5c64a3a8a11.png)

There is one of the possible answers of length $ 9 $ .

## 样例 #1

### 输入

```
8
2 2
1 4
2 3
3 1
3 4
1 1
4 3
1 2
```

### 输出

```
15
```

## 样例 #2

### 输入

```
5
2 1
1 0
2 0
3 2
0 3
```

### 输出

```
9
```

# AI分析结果

### 题目内容
# 又一个二维行走问题

## 题目描述
马克西姆在笛卡尔平面上行走。最初，他站在点$(0, 0)$，并且在一次移动中，他可以前往四个相邻点中的任意一个（左、右、上、下）。例如，如果马克西姆当前位于点$(0, 0)$，他可以在一次移动中前往以下任意一个点：
- $(1, 0)$；
- $(0, 1)$；
- $(-1, 0)$；
- $(0, -1)$。

在这个平面上还有$n$个不同的关键点。第$i$个点是$p_i = (x_i, y_i)$。保证$0 \leq x_i$且$0 \leq y_i$，并且不存在关键点$(0, 0)$。

设第一层的点满足$\max(x_i, y_i) = 1$，第二层的点满足$\max(x_i, y_i) = 2$，以此类推。马克西姆想要访问所有的关键点。但是，如果他没有访问完第$i$层的所有点，就不应该访问第$i + 1$层的点。他从给定集合中最低层的点开始访问。

两点$(x_1, y_1)$和$(x_2, y_2)$之间的距离是$|x_1 - x_2| + |y_1 - y_2|$，其中$|v|$是$v$的绝对值。

马克西姆希望以总行走距离尽可能小的方式访问所有关键点。你的任务是找出这个距离。

如果你是Python程序员，提交代码时考虑使用PyPy而不是Python。

## 说明/提示
第一个示例对应的图片：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1066F/896df4e9ea79d5fd52a150516ea0bd817a9ff17d.png)

存在一种长度为15的可能答案。

第二个示例对应的图片：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1066F/df4d50be023876f6bcdf0e6166cef5c64a3a8a11.png)

存在一种长度为9的可能答案。

## 样例 #1
### 输入
```
8
2 2
1 4
2 3
3 1
3 4
1 1
4 3
1 2
```
### 输出
```
15
```
## 样例 #2
### 输入
```
5
2 1
1 0
2 0
3 2
0 3
```
### 输出
```
9
```

### 算法分类
动态规划

### 题解综合分析与结论
这些题解的核心思路都是基于动态规划，利用同一层关键点的特殊分布和转移规律来解题。
 - **思路**：各题解都意识到要按级别分层处理关键点，且在同一级别内，从最左上点到最右下点（或反之）的路径是最优的，不同级别间从一个级别的端点转移到下一级别的端点。
 - **算法要点**：定义状态$dp[i][0/1]$表示处理完第$i$等级，且停留在该等级最左上/最右下点的最短路，通过状态转移方程计算最小路径。
 - **解决难点**：证明并确定同一级别内及级别间的最优转移方式，从而准确写出状态转移方程。

### 所选的题解
- **作者：p_b_p_b（5星）**
  - **关键亮点**：思路清晰，代码实现完整且包含自定义快速输入等优化。对状态和转移方程的定义明确，详细注释辅助理解。
  - **个人心得**：激动抢到第一篇题解，提及可使用滚动数组优化但因不卡空间未实现。
  ```cpp
  // 状态转移核心代码
  for (x = 0; x < 2; x++)
      for (y = 0; y < 2; y++)
          dp[z][x]=min(dp[z][x],dp[z - 1][y]+dis(p[z - 1][y],p[z][!x])+dis(p[z][!x],p[z][x]));
  ```
- **作者：ncwzdlsd（4星）**
  - **关键亮点**：简洁明了地阐述思路，状态转移方程表达清晰，代码简洁。
  ```cpp
  // 状态转移核心代码
  for(int i = 1;i <= cnt;i++)
      f[i][0]=min(f[i - 1][0]+dis(l[i - 1],r[i]),f[i - 1][1]+dis(r[i - 1],r[i]))+dis(l[i],r[i]),
      f[i][1]=min(f[i - 1][0]+dis(l[i - 1],l[i]),f[i - 1][1]+dis(r[i - 1],l[i]))+dis(l[i],r[i]);
  ```
- **作者：littlewyy（4星）**
  - **关键亮点**：对题意和思路有详细分析，包括对最优解的证明。代码结构清晰，有读入优化和离散化处理。
  ```cpp
  // 状态转移核心代码
  if(last == 0) {
      f[i][0] = dis + A[Rig[i]].x + A[Rig[i]].y;
      f[i][1] = dis + A[Lef[i]].x + A[Lef[i]].y;
  }
  else {
      f[i][0] = dis + min(f[last][0] + getDis(Lef[last],Rig[i]),f[last][1] + getDis(Rig[last],Rig[i]));
      f[i][1] = dis + min(f[last][0] + getDis(Lef[last],Lef[i]),f[last][1] + getDis(Rig[last],Lef[i]));
  }
  ```

### 最优关键思路或技巧
通过观察关键点分布规律，利用动态规划，将问题按级别分层处理，定义合适状态和状态转移方程。关键在于确定同一级别内及级别间的最优转移路径，以减少路径重复，从而降低总距离。

### 可拓展之处
此类题目属于平面点集路径规划问题，类似套路可应用于其他有特定访问顺序和距离计算规则的路径规划题。例如，改变点集分布或移动规则，依然可尝试通过动态规划分层处理。

### 洛谷相似题目推荐
 - [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)：涉及二维空间的路径规划与动态规划。
 - [P1280尼克的任务](https://www.luogu.com.cn/problem/P1280)：时间序列上的任务安排，同样需要合理定义状态和转移方程。
 - [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)：区间动态规划，与本题类似的是通过划分阶段来解决问题。 

---
处理用时：57.16秒