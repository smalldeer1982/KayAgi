# 题目信息

# Christmas Trees

## 题目描述

There are $ n $ Christmas trees on an infinite number line. The $ i $ -th tree grows at the position $ x_i $ . All $ x_i $ are guaranteed to be distinct.

Each integer point can be either occupied by the Christmas tree, by the human or not occupied at all. Non-integer points cannot be occupied by anything.

There are $ m $ people who want to celebrate Christmas. Let $ y_1, y_2, \dots, y_m $ be the positions of people (note that all values $ x_1, x_2, \dots, x_n, y_1, y_2, \dots, y_m $ should be distinct and all $ y_j $ should be integer). You want to find such an arrangement of people that the value $ \sum\limits_{j=1}^{m}\min\limits_{i=1}^{n}|x_i - y_j| $ is the minimum possible (in other words, the sum of distances to the nearest Christmas tree for all people should be minimized).

In other words, let $ d_j $ be the distance from the $ j $ -th human to the nearest Christmas tree ( $ d_j = \min\limits_{i=1}^{n} |y_j - x_i| $ ). Then you need to choose such positions $ y_1, y_2, \dots, y_m $ that $ \sum\limits_{j=1}^{m} d_j $ is the minimum possible.

## 样例 #1

### 输入

```
2 6
1 5
```

### 输出

```
8
-1 2 6 4 0 3 
```

## 样例 #2

### 输入

```
3 5
0 3 1
```

### 输出

```
7
5 -2 4 -1 2 
```

# AI分析结果

### 中文题目重写
# 圣诞树

## 题目描述

在一个无限长的数轴上有 $n$ 棵圣诞树。第 $i$ 棵树位于位置 $x_i$。所有 $x_i$ 保证互不相同。

每个整数点可以被圣诞树、人占据，或者空着。非整数点不能被任何东西占据。

有 $m$ 个人想要庆祝圣诞节。设 $y_1, y_2, \dots, y_m$ 为这些人的位置（注意所有 $x_1, x_2, \dots, x_n, y_1, y_2, \dots, y_m$ 必须互不相同，且所有 $y_j$ 必须是整数）。你需要找到一种安排人的位置的方式，使得 $\sum\limits_{j=1}^{m}\min\limits_{i=1}^{n}|x_i - y_j|$ 的值最小（换句话说，所有人到最近的圣诞树的距离之和最小）。

换句话说，设 $d_j$ 为第 $j$ 个人到最近的圣诞树的距离（$d_j = \min\limits_{i=1}^{n} |y_j - x_i|$）。你需要选择位置 $y_1, y_2, \dots, y_m$，使得 $\sum\limits_{j=1}^{m} d_j$ 最小。

## 样例 #1

### 输入

```
2 6
1 5
```

### 输出

```
8
-1 2 6 4 0 3 
```

## 样例 #2

### 输入

```
3 5
0 3 1
```

### 输出

```
7
5 -2 4 -1 2 
```

### 算法分类
广度优先搜索 BFS

### 题解分析与结论
本题的核心是通过广度优先搜索（BFS）来找到离圣诞树最近的位置，并依次扩展，直到找到足够的位置来放置所有人。BFS的优势在于它能够按距离递增的顺序遍历所有可能的位置，确保每次选择的位置都是当前最优的。

### 所选高星题解
#### 题解1：作者：dd_d (赞：5)
- **星级**：5星
- **关键亮点**：使用BFS从圣诞树的位置开始扩展，按距离递增的顺序选择位置，确保每次选择的位置都是当前最优的。代码简洁，思路清晰。
- **核心代码**：
```cpp
void bfs()
{
    while (ans.size()<m)
    {
        int u=q.front(); q.pop();
        sum+=dis[u];
        if (dis[u]) ans.push_back(u);
        for (int i=0;i<2;i++)
        {
            int xx=u+dx[i];
            if (dis.count(xx)) continue;
            dis[xx]=dis[u]+1; q.push(xx);
        }
    }
}
```
- **实现思想**：从圣诞树的位置开始，使用BFS按距离递增的顺序扩展位置，直到找到足够的位置来放置所有人。

#### 题解2：作者：_JellyFish_ (赞：0)
- **星级**：4星
- **关键亮点**：使用BFS从圣诞树的位置开始扩展，按距离递增的顺序选择位置，确保每次选择的位置都是当前最优的。代码简洁，思路清晰。
- **核心代码**：
```cpp
while(num!=M){
    pair<int,int>t=q.front();
    q.pop();
    int fi=t.first,se=t.second;
    if(fi!=0){
        cnt+=fi;
        ans[++num]=se;
    }	
    if(!m[se+1])q.push(make_pair(fi+1,se+1)),m[se+1]=1;
    if(!m[se-1])q.push(make_pair(fi+1,se-1)),m[se-1]=1;
}
```
- **实现思想**：从圣诞树的位置开始，使用BFS按距离递增的顺序扩展位置，直到找到足够的位置来放置所有人。

### 最优关键思路或技巧
- **BFS扩展**：从圣诞树的位置开始，按距离递增的顺序扩展位置，确保每次选择的位置都是当前最优的。
- **数据结构**：使用队列和哈希表来存储和扩展位置，确保每个位置只被扩展一次。

### 可拓展之处
- **类似问题**：可以使用类似的BFS思路解决其他需要按距离递增顺序扩展的问题，如最短路径问题、覆盖问题等。

### 推荐题目
1. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
3. [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)

---
处理用时：33.52秒