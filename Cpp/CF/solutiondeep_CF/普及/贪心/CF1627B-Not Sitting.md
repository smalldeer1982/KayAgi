# 题目信息

# Not Sitting

## 题目描述

Rahul and Tina are looking forward to starting their new year at college. As they enter their new classroom, they observe the seats of students are arranged in a $ n \times m $ grid. The seat in row $ r $ and column $ c $ is denoted by $ (r, c) $ , and the distance between two seats $ (a,b) $ and $ (c,d) $ is $ |a-c| + |b-d| $ .

As the class president, Tina has access to exactly $ k $ buckets of pink paint. The following process occurs.

- First, Tina chooses exactly $ k $ seats in the classroom to paint with pink paint. One bucket of paint can paint exactly one seat.
- After Tina has painted $ k $ seats in the previous step, Rahul chooses where he sits. He will not choose a seat that has been painted pink due to his hatred of the colour pink.
- After Rahul has chosen his seat, Tina chooses a seat for herself. She can choose any of the seats, painted or not, other than the one chosen by Rahul.

Rahul wants to choose a seat such that he sits as close to Tina as possible. However, Tina wants to sit as far away from Rahul as possible due to some complicated relationship history that we couldn't fit into the statement!

Now, Rahul wonders for $ k = 0, 1, \dots, n \cdot m - 1 $ , if Tina has $ k $ buckets of paint, how close can Rahul sit to Tina, if both Rahul and Tina are aware of each other's intentions and they both act as strategically as possible? Please help satisfy Rahul's curiosity!

## 说明/提示

One possible sequence of choices for the first testcase where Tina has $ k=3 $ buckets of paints is as follows.

Tina paints the seats at positions $ (1, 2) $ , $ (2, 2) $ , $ (3, 2) $ with pink paint. Rahul chooses the seat at $ (3, 1) $ after which Tina chooses to sit at $ (1, 3) $ .

Therefore, the distance between Tina and Rahul is $ |3-1| + |1-3| = 4 $ , and we can prove that this is indeed the minimum possible distance under the given constraints. There may be other choices of seats which lead to the same answer as well.

For $ k=0 $ in the first test case, Rahul can decide to sit at $ (2, 2) $ and Tina can decide to sit at $ (4, 3) $ so the distance between them would be $ |2 - 4| + |2 - 3| = 3 $ .

Below are pictorial representations of the $ k=3 $ and $ k=0 $ cases for the first test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627B/135a6759a6ba23b198694ead1674597ee527f081.png) A possible seating arrangement for $ k=3 $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627B/f8d6f4f57279fb43f8c4bcfe0a1490483d3f4037.png) A possible seating arrangement for $ k=0 $ .

## 样例 #1

### 输入

```
2
4 3
1 2```

### 输出

```
3 3 4 4 4 4 4 4 5 5 5 5 
1 1```

# AI分析结果

### 题目翻译

Rahul 和 Tina 期待着在大学开始他们的新学年。当他们进入新教室时，他们发现学生的座位排列在一个 $n \times m$ 的网格中。第 $r$ 行第 $c$ 列的座位记为 $(r, c)$，两个座位 $(a,b)$ 和 $(c,d)$ 之间的距离定义为 $|a-c| + |b-d|$。

作为班长，Tina 有恰好 $k$ 桶粉色油漆。以下是过程：

1. 首先，Tina 选择教室中的恰好 $k$ 个座位，并用粉色油漆涂色。一桶油漆只能涂一个座位。
2. 在 Tina 涂完 $k$ 个座位后，Rahul 选择他的座位。他不会选择被涂成粉色的座位，因为他讨厌粉色。
3. 在 Rahul 选择座位后，Tina 为自己选择一个座位。她可以选择任何座位，无论是否被涂色，除了 Rahul 选择的座位。

Rahul 希望选择一个座位，使他尽可能靠近 Tina。然而，由于一些复杂的关系历史，Tina 希望尽可能远离 Rahul！

现在，Rahul 想知道，对于 $k = 0, 1, \dots, n \cdot m - 1$，如果 Tina 有 $k$ 桶油漆，Rahul 能坐得离 Tina 多近，假设 Rahul 和 Tina 都了解彼此的意图，并且他们都尽可能采取最优策略？请帮助满足 Rahul 的好奇心！

### 样例 #1

#### 输入

```
2
4 3
1 2
```

#### 输出

```
3 3 4 4 4 4 4 4 5 5 5 5 
1 1
```

### 题解分析与结论

#### 综合分析

1. **核心思路**：无论 Rahul 坐在哪里，Tina 都会选择四个角落中离 Rahul 最远的位置。因此，问题的关键在于计算每个座位到四个角落的最大距离，并按照这些距离从小到大排序输出。
2. **算法要点**：
   - 计算每个座位到四个角落的距离，取最大值。
   - 将所有座位的最大距离排序，依次输出。
3. **难点**：如何高效地计算每个座位到四个角落的最大距离，并处理多组数据。
4. **优化**：使用桶排序或优先队列来优化排序过程，避免使用复杂的排序算法。

#### 最优关键思路

- **距离计算**：对于每个座位 $(i,j)$，计算其到四个角落 $(1,1)$、$(1,m)$、$(n,1)$、$(n,m)$ 的距离，取最大值。
- **排序输出**：将所有座位的最大距离排序，依次输出。

#### 可拓展之处

- 类似的问题可以扩展到其他距离度量方式，如欧几里得距离。
- 可以进一步优化空间复杂度，避免存储所有座位的距离。

### 推荐题目

1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 [NOIP2006 提高组] 开心的金明](https://www.luogu.com.cn/problem/P1060)

### 精选题解

#### 题解1：Daidly (5星)

**关键亮点**：
- 使用桶排序优化了排序过程，时间复杂度为 $O(nm)$，优于其他题解的 $O(nm \log nm)$。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
        p[max(i-1,n-i)+max(j-1,m-j)]++;
    }
}
for(int i=n-(n+1)/2+m-(m+1)/2;i<=n-1+m-1;++i){
    while(p[i]--)print(i),printf(" ");
    p[i]++;
}
```

#### 题解2：xkcdjerry (4星)

**关键亮点**：
- 使用 BFS 预处理每个点到四个角的距离，确保时间复杂度为 $O(nm)$。
- 通过桶排序优化了输出过程，避免了复杂的排序算法。

**核心代码**：
```cpp
for(int j=0;j<4;j++){
    head=tail=0;
    clear(vis,n*m); clear(g[j],n*m); add(s[j]);
    while(head!=tail){
        t=q[tail++];
        x=t/m,y=t%m;
        if(tail==N) tail=0;
        int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0};
        for(int i=0;i<4;i++){
            pk=(nx=x+dx[i])*m+(ny=y+dy[i]);
            if(nx>=0&&nx<n&&ny>=0&&ny<m&&!vis[pk]){
                g[j][pk]=g[j][t]+1;
                add(pk);
            }
        }
    }
}
```

#### 题解3：Shunpower (4星)

**关键亮点**：
- 通过预处理每个座位到四个角落的最大距离，简化了问题。
- 使用排序算法输出结果，代码简洁明了。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        tot++;
        a[tot]=max(abs(i-1)+abs(j-1),max(abs(i-1)+abs(m-j),max(abs(n-i)+abs(j-1),abs(n-i)+abs(m-j))));
    }
}
sort(a+1,a+tot+1);
for(int i=1;i<=n*m;i++){
    cout<<a[i]<<" ";
}
```

### 个人心得

- **调试经历**：在处理多组数据时，务必清空数组和变量，避免数据污染。
- **顿悟感想**：通过预处理和排序，可以大大简化问题的复杂度，尤其是在处理大规模数据时。

---
处理用时：53.32秒