# 题目信息

# Connected Component on a Chessboard

## 题目描述

You are given two integers $ b $ and $ w $ . You have a chessboard of size $ 10^9 \times 10^9 $ with the top left cell at $ (1; 1) $ , the cell $ (1; 1) $ is painted white.

Your task is to find a connected component on this chessboard that contains exactly $ b $ black cells and exactly $ w $ white cells. Two cells are called connected if they share a side (i.e. for the cell $ (x, y) $ there are at most four connected cells: $ (x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1) $ ). A set of cells is called a connected component if for every pair of cells $ C_1 $ and $ C_2 $ from this set, there exists a sequence of cells $ c_1 $ , $ c_2 $ , ..., $ c_k $ such that $ c_1 = C_1 $ , $ c_k = C_2 $ , all $ c_i $ from $ 1 $ to $ k $ are belong to this set of cells and for every $ i \in [1, k - 1] $ , cells $ c_i $ and $ c_{i + 1} $ are connected.

Obviously, it can be impossible to find such component. In this case print "NO". Otherwise, print "YES" and any suitable connected component.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
3
1 1
1 4
2 5
```

### 输出

```
YES
2 2
1 2
YES
2 3
1 3
3 3
2 2
2 4
YES
2 3
2 4
2 5
1 3
1 5
3 3
3 5
```

# AI分析结果

### 题目翻译
# 棋盘上的连通分量

## 题目描述
给定两个整数 $b$ 和 $w$。你有一个大小为 $10^9 \times 10^9$ 的棋盘，左上角的单元格坐标为 $(1; 1)$，单元格 $(1; 1)$ 被涂成白色。

你的任务是在这个棋盘上找到一个连通分量，该连通分量恰好包含 $b$ 个黑色单元格和 $w$ 个白色单元格。如果两个单元格共享一条边，则称它们是连通的（即对于单元格 $(x, y)$，最多有四个连通单元格：$(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)$）。如果对于该集合中的每一对单元格 $C_1$ 和 $C_2$，都存在一个单元格序列 $c_1, c_2, \cdots, c_k$，使得 $c_1 = C_1$，$c_k = C_2$，所有从 $1$ 到 $k$ 的 $c_i$ 都属于这个单元格集合，并且对于每一个 $i \in [1, k - 1]$，单元格 $c_i$ 和 $c_{i + 1}$ 是连通的，那么这个单元格集合就被称为一个连通分量。

显然，可能无法找到这样的分量。在这种情况下，输出 "NO"。否则，输出 "YES" 并输出任何合适的连通分量。

你需要回答 $q$ 个独立的查询。

## 样例 #1
### 输入
```
3
1 1
1 4
2 5
```
### 输出
```
YES
2 2
1 2
YES
2 3
1 3
3 3
2 2
2 4
YES
2 3
2 4
2 5
1 3
1 5
3 3
3 5
```

### 算法分类
构造

### 综合分析与结论
- **思路对比**：
    - Bring 的题解从贪心角度出发，认为将方块拉成直线能使相差数量巨大的 $b$ 和 $w$ 更易成功放置。先处理 $b = w$ 的简单情况，对于 $b \neq w$ 假设 $b > w$，先画包含所有白块且两端为黑块的直线消耗 $w + 1$ 个黑块，再判断剩余黑块数量是否满足条件。
    - FiraCode 的题解利用选中一个颜色后选另一个颜色最多能解锁 3 个当前颜色的性质，考虑横着构造，若不够则在两边再选。
- **算法要点对比**：
    - Bring 主要是通过直线构造连通分量，根据黑块和白块数量关系判断是否可行并输出结果。
    - FiraCode 是根据黑块和白块数量关系判断可行性，然后分情况构造连通分量。
- **解决难点对比**：
    - Bring 主要解决的难点是如何合理安排黑块和白块的位置，使它们构成连通分量且满足数量要求，通过直线构造和剩余黑块的分配来解决。
    - FiraCode 主要解决的难点同样是构造满足条件的连通分量，利用颜色解锁数量的性质和横着构造的方法来解决。

### 题解评分
- Bring：3 星。思路较清晰，有图解辅助理解，但代码中使用了较多自定义宏，影响代码可读性。
- FiraCode：2 星。思路有一定阐述，但不够详细，代码中使用固定的坐标值，缺乏灵活性。

### 通用建议与扩展思路
- 对于此类构造问题，可以先分析问题的性质和特点，找到一些关键的规律和限制条件，然后根据这些条件进行构造。
- 可以通过画图等方式辅助理解问题，帮助找到构造的方法。
- 同类型题或类似算法套路：在其他棋盘类构造问题中，也可以考虑利用棋盘的特性（如颜色分布、连通性等）进行构造，或者根据给定的数量关系进行合理的分配和布局。

### 推荐洛谷题目
- P1162 填涂颜色：考察对连通区域的判断和处理。
- P1605 迷宫：涉及路径的构造和连通性问题。
- P2002 消息扩散：与图的连通性和构造相关。

### 重点代码
#### Bring 的题解核心代码
```cpp
while(q--){
    Rd(b),Rd(w);
    if(b==w){
        puts("YES");
        Frn1(i,1,b<<1)Pc('1'),Ps,wr(i),Pe;
    }else{
        b<w?(swap(b,w),s=2):s=1;
        if((b-=w+1)>w<<1){puts("NO");continue;};
        puts("YES");
        Frn1(i,0,w<<1)Pc('2'),Ps,wr(s+i),Pe;
        if(b<=w)Frn0(i,0,b)Pc('1'),Ps,wr(s+(i<<1|1)),Pe;
        else{
            Frn0(i,0,w)Pc('1'),Ps,wr(s+(i<<1|1)),Pe;
            b-=w;
            Frn0(i,0,b)Pc('3'),Ps,wr(s+(i<<1|1)),Pe;
        }
    }
}
```
核心实现思想：先处理 $b = w$ 的情况，直接输出一条直线的坐标。对于 $b \neq w$ 的情况，先交换使 $b > w$，判断剩余黑块数量是否满足条件，若满足则先输出直线的坐标，再根据剩余黑块数量分情况输出其他坐标。

#### FiraCode 的题解核心代码
```cpp
while (T--) {
    scanf("%d%d", &x, &y);
    if (3 * x + 1 < y || 3 * y + 1 < x) puts("NO");
    else {
        puts("YES");
        if (x == y) {
            int X1 = 100000, Y1 = 100000;
            for (int i = 1; i <= y; ++i) {
                printf("%d %d\n", X1, Y1);
                printf("%d %d\n", X1, Y1 + 1);
                Y1 += 2;
            }
        } else if (x > y) {
            printf("%d %d\n", 100000, 100001);
            int X1 = 100000, Y1 = 100002;
            int tmp = max(0, x - y - 1);
            for (int i = 1; i <= y; ++i) {
                printf("%d %d\n", X1, Y1);
                printf("%d %d\n", X1, Y1 + 1);
                if (tmp) {
                    printf("%d %d\n", X1 + 1, Y1);
                    --tmp;
                }
                if (tmp) {
                    printf("%d %d\n", X1 - 1, Y1);
                    --tmp;
                }
                Y1 += 2;
            }
        } else {
            printf("%d %d\n", 100000, 100000);
            int X1 = 100000, Y1 = 100001;
            int tmp = max(0, y - x - 1);
            for (int i = 1; i <= x; ++i) {
                printf("%d %d\n", X1, Y1);
                printf("%d %d\n", X1, Y1 + 1);
                if (tmp) {
                    printf("%d %d\n", X1 - 1, Y1);
                    --tmp;
                }
                if (tmp) {
                    printf("%d %d\n", X1 + 1, Y1);
                    --tmp;
                }
                Y1 += 2;
            }
        }
    }
}
```
核心实现思想：先判断是否满足条件，若不满足输出 "NO"。对于 $x = y$ 的情况，输出特定的坐标序列。对于 $x \neq y$ 的情况，根据数量关系输出起始坐标，然后在循环中输出其他坐标，并根据剩余数量在两边添加坐标。

---
处理用时：48.36秒