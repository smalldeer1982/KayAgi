# 题目信息

# Andrey and Escape from Capygrad

## 题目描述

An incident occurred in Capygrad, the capital of Tyagoland, where all the capybaras in the city went crazy and started throwing mandarins. Andrey was forced to escape from the city as far as possible, using portals.

Tyagoland is represented by a number line, and the city of Capygrad is located at point $ 0 $ . There are $ n $ portals all over Tyagoland, each of which is characterised by four integers $ l_i $ , $ r_i $ , $ a_i $ and $ b_i $ ( $ 1 \le l_i \le a_i \le b_i \le r_i \le 10^9 $ ). Note that the segment $ [a_i, b_i] $ is contained in the segment $ [l_i, r_i] $ .

If Andrey is on the segment $ [l_i, r_i] $ , then the portal can teleport him to any point on the segment $ [a_i, b_i] $ . Andrey has a pass that allows him to use the portals an unlimited number of times.

Andrey thinks that the point $ x $ is on the segment $ [l, r] $ if the inequality $ l \le x \le r $ is satisfied.

Andrey has $ q $ options for where to start his escape, each option is characterized by a single integer $ x_i $ — the starting position of the escape. He wants to escape from Capygrad as far as possible (to the point with the maximum possible coordinate). Help Andrey determine how far he could escape from Capygrad, starting at each of the $ q $ positions.

## 说明/提示

In the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1859D/e16f53a0bb292ac32fb706ca20fa668cca5f7c21.png)Optimal actions when starting from each position:

1. Use portal $ 1 $ and teleport to point $ b_1 = 14 $ .
2. Use portal $ 2 $ first and teleport to point $ 6 $ , which is on the segment $ [l_1, r_1] = [6, 17] $ , then use portal $ 1 $ and teleport to point $ b_1 = 14 $ .
3. Stay at point $ x_3=23 $ without using any portals.
4. Stay at point $ x_4=15 $ without using any portals.
5. Point $ x_5=28 $ is not on any segment, so Andrey won't be able to teleport anywhere.
6. Point $ x_6=18 $ is only on the segment $ [l_3, r_3] = [16, 24] $ , use portal $ 3 $ and teleport to point $ b_3 = 22 $ .

In the fifth test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1859D/039563dbba6cbb0aa164e573669410ec3fd16328.png)Optimal actions when starting from each position:

1. Use portal $ 1 $ first and teleport to point $ 15 $ on the segment $ [a_1, b_1] = [14, 20] $ , then use portal $ 2 $ and teleport to point $ 21 $ , which is on the segment $ [l_4, r_4] = [21, 33] $ and on the segment $ [a_2, b_2] = [13, 24] $ , then teleport to point $ b_4 = 32 $ .
2. Use portal $ 6 $ first and teleport to point $ 20 $ on the segment $ [a_6, b_6] = [20, 21] $ , then use portal $ 2 $ and teleport to point $ 22 $ , which is simultaneously on the segment $ [l_4, r_4] = [21, 33] $ and on the segment $ [a_2, b_2] = [13, 24] $ , then teleport to point $ b_4 = 32 $ .
3. Perform the same actions as from the first position.
4. Stay at point $ x_4=5 $ without using any portals.
5. Point $ 8 $ is not on any segment, so Andrey won't be able to teleport anywhere.
6. Stay at point $ x_6=33 $ without using any portals.
7. Use portal $ 5 $ and teleport to point $ b_5 = 4 $ .
8. Perform the same actions as from the first position.

## 样例 #1

### 输入

```
5
3
6 17 7 14
1 12 3 8
16 24 20 22
6
10 2 23 15 28 18
3
3 14 7 10
16 24 20 22
1 16 3 14
9
2 4 6 8 18 23 11 13 15
2
1 4 2 3
3 9 6 7
3
4 8 1
5
18 24 18 24
1 8 2 4
11 16 14 14
26 32 28 30
5 10 6 8
9
15 14 13 27 22 17 31 1 7
6
9 22 14 20
11 26 13 24
21 33 22 23
21 33 25 32
1 6 3 4
18 29 20 21
8
11 23 16 5 8 33 2 21```

### 输出

```
14 14 23 15 28 22 
14 14 14 14 22 23 14 14 15 
7 8 7 
15 14 14 30 24 17 31 4 8 
32 32 32 5 8 33 4 32```

# AI分析结果

### 题目翻译

#### Andrey 和逃离 Capygrad

**题目描述**

在 Tyagoland 的首都 Capygrad 发生了一起事件，城市中的所有水豚都疯了，开始扔橘子。Andrey 被迫尽可能远离这座城市，使用传送门逃离。

Tyagoland 用一条数轴表示，Capygrad 位于点 $0$。Tyagoland 上有 $n$ 个传送门，每个传送门由四个整数 $l_i$、$r_i$、$a_i$ 和 $b_i$ 描述（$1 \le l_i \le a_i \le b_i \le r_i \le 10^9$）。注意，区间 $[a_i, b_i]$ 包含在区间 $[l_i, r_i]$ 内。

如果 Andrey 位于区间 $[l_i, r_i]$ 内，那么传送门可以将他传送到区间 $[a_i, b_i]$ 内的任意一点。Andrey 有一张通行证，允许他无限次使用传送门。

Andrey 认为点 $x$ 位于区间 $[l, r]$ 内，如果满足不等式 $l \le x \le r$。

Andrey 有 $q$ 个逃离的起点选项，每个选项由一个整数 $x_i$ 表示——逃离的起始位置。他希望尽可能远离 Capygrad（到达坐标最大的点）。请帮助 Andrey 确定从每个 $q$ 个起始位置出发，他能够逃离的最远距离。

**说明/提示**

在第一个测试用例中：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1859D/e16f53a0bb292ac32fb706ca20fa668cca5f7c21.png)

从每个位置出发的最优操作：

1. 使用传送门 $1$，传送到点 $b_1 = 14$。
2. 首先使用传送门 $2$，传送到点 $6$，该点位于区间 $[l_1, r_1] = [6, 17]$ 内，然后使用传送门 $1$，传送到点 $b_1 = 14$。
3. 停留在点 $x_3=23$，不使用任何传送门。
4. 停留在点 $x_4=15$，不使用任何传送门。
5. 点 $x_5=28$ 不在任何区间内，因此 Andrey 无法传送到任何地方。
6. 点 $x_6=18$ 仅位于区间 $[l_3, r_3] = [16, 24]$ 内，使用传送门 $3$，传送到点 $b_3 = 22$。

在第五个测试用例中：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1859D/039563dbba6cbb0aa164e573669410ec3fd16328.png)

从每个位置出发的最优操作：

1. 首先使用传送门 $1$，传送到点 $15$，该点位于区间 $[a_1, b_1] = [14, 20]$ 内，然后使用传送门 $2$，传送到点 $21$，该点同时位于区间 $[l_4, r_4] = [21, 33]$ 和区间 $[a_2, b_2] = [13, 24]$ 内，然后传送到点 $b_4 = 32$。
2. 首先使用传送门 $6$，传送到点 $20$，该点位于区间 $[a_6, b_6] = [20, 21]$ 内，然后使用传送门 $2$，传送到点 $22$，该点同时位于区间 $[l_4, r_4] = [21, 33]$ 和区间 $[a_2, b_2] = [13, 24]$ 内，然后传送到点 $b_4 = 32$。
3. 执行与第一个位置相同的操作。
4. 停留在点 $x_4=5$，不使用任何传送门。
5. 点 $8$ 不在任何区间内，因此 Andrey 无法传送到任何地方。
6. 停留在点 $x_6=33$，不使用任何传送门。
7. 使用传送门 $5$，传送到点 $b_5 = 4$。
8. 执行与第一个位置相同的操作。

**样例 #1**

**输入**

```
5
3
6 17 7 14
1 12 3 8
16 24 20 22
6
10 2 23 15 28 18
3
3 14 7 10
16 24 20 22
1 16 3 14
9
2 4 6 8 18 23 11 13 15
2
1 4 2 3
3 9 6 7
3
4 8 1
5
18 24 18 24
1 8 2 4
11 16 14 14
26 32 28 30
5 10 6 8
9
15 14 13 27 22 17 31 1 7
6
9 22 14 20
11 26 13 24
21 33 22 23
21 33 25 32
1 6 3 4
18 29 20 21
8
11 23 16 5 8 33 2 21
```

**输出**

```
14 14 23 15 28 22 
14 14 14 14 22 23 14 14 15 
7 8 7 
15 14 14 30 24 17 31 4 8 
32 32 32 5 8 33 4 32
```

### 算法分类
贪心、离散化

### 题解分析与总结

#### 题解对比与总结
1. **核心思路**：所有题解都基于贪心策略，认为从某个点出发后，最优的传送目标是传送门的右端点 $b_i$。通过合并重叠的区间，将问题转化为在离散化后的区间中查找每个查询点的最远可达位置。
2. **难点**：
   - **区间合并**：如何高效地合并重叠的区间，确保每个查询点能够快速找到其最远可达位置。
   - **离散化处理**：由于坐标范围较大，需要对坐标进行离散化处理，以减少计算复杂度。
3. **优化**：部分题解通过使用并查集、线段树等数据结构来优化区间合并和查询操作，进一步提高了算法的效率。

#### 评分较高的题解
1. **作者：shinzanmono (赞：11)**
   - **星级**：4.5
   - **关键亮点**：通过合并区间并利用 `set` 数据结构进行查询，代码简洁且高效。
   - **核心代码**：
     ```cpp
     std::set<segment> cur;
     cur.insert(segment{0,0});
     for(int i=1;i<=n;i++){
         int l=line[i].l,r=line[i].r;
         while(i<n&&line[i+1].l>=l&&line[i+1].l<=r)i++,r=std::max(r,line[i].r);
         cur.insert(segment{l,r});
     }
     ```
   - **个人心得**：通过合并区间，减少了查询的复杂度，使得算法更加高效。

2. **作者：xujunlang2011 (赞：8)**
   - **星级**：4
   - **关键亮点**：通过二分查找快速定位查询点所在的区间，代码实现清晰。
   - **核心代码**：
     ```cpp
     int l = 1, r = cnt;
     while (l < r) {
         int mid = (l + r + 1) / 2;
         if (a[mid].l > x) r = mid - 1;
         else l = mid;
     }
     ```
   - **个人心得**：通过二分查找优化了查询效率，使得算法在大数据量下依然高效。

3. **作者：Jie_Xu_Sheng (赞：4)**
   - **星级**：4
   - **关键亮点**：使用线段树维护区间信息，进一步优化了区间合并和查询操作。
   - **核心代码**：
     ```cpp
     void modify(int p,int l,int r,int x,int y){
         if(l>x||r<x) return ;
         if(l==r&&r==x){
             mx[p]=y;
             return ;
         }
         int mid=(l+r)/2;
         modify(p*2,l,mid,x,y);
         modify(p*2+1,mid+1,r,x,y);
         pushup(p);
     }
     ```
   - **个人心得**：通过线段树维护区间信息，使得区间合并和查询操作更加高效。

### 最优关键思路
1. **贪心策略**：从某个点出发后，最优的传送目标是传送门的右端点 $b_i$。
2. **区间合并**：通过合并重叠的区间，减少查询的复杂度。
3. **离散化处理**：对坐标进行离散化处理，以减少计算复杂度。

### 拓展思路
1. **类似题目**：可以扩展到其他需要区间合并和离散化处理的题目，如区间覆盖、区间查询等。
2. **数据结构优化**：可以进一步使用更高效的数据结构（如并查集、线段树）来优化区间合并和查询操作。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

---
处理用时：87.12秒