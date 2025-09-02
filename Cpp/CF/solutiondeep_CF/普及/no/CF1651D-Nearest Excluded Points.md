# 题目信息

# Nearest Excluded Points

## 题目描述

You are given $ n $ distinct points on a plane. The coordinates of the $ i $ -th point are $ (x_i, y_i) $ .

For each point $ i $ , find the nearest (in terms of Manhattan distance) point with integer coordinates that is not among the given $ n $ points. If there are multiple such points — you can choose any of them.

The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ .

## 样例 #1

### 输入

```
6
2 2
1 2
2 1
3 2
2 3
5 5```

### 输出

```
1 1
1 1
2 0
3 1
2 4
5 4```

## 样例 #2

### 输入

```
8
4 4
2 4
2 2
2 3
1 4
4 2
1 3
3 3```

### 输出

```
4 3
2 5
2 1
2 5
1 5
4 1
1 2
3 2```

# AI分析结果

### 题目内容重写

#### 题目描述

给定平面上 $n$ 个不同的点，第 $i$ 个点的坐标为 $(x_i, y_i)$。

对于每个点 $i$，找到与其曼哈顿距离最近的、且不在给定 $n$ 个点中的整数坐标点。如果有多个这样的点，可以选择其中任意一个。

曼哈顿距离的定义为：两个点 $(x_1, y_1)$ 和 $(x_2, y_2)$ 之间的曼哈顿距离为 $|x_1 - x_2| + |y_1 - y_2|$。

#### 样例 #1

##### 输入

```
6
2 2
1 2
2 1
3 2
2 3
5 5
```

##### 输出

```
1 1
1 1
2 0
3 1
2 4
5 4
```

#### 样例 #2

##### 输入

```
8
4 4
2 4
2 2
2 3
1 4
4 2
1 3
3 3
```

##### 输出

```
4 3
2 5
2 1
2 5
1 5
4 1
1 2
3 2
```

### 算法分类
广度优先搜索 BFS

### 综合分析与结论

本题的核心思路是利用 BFS 来找到每个点的最近非给定点。所有题解都采用了 BFS 的思想，但实现细节有所不同。主要的难点在于如何高效地存储和处理点的信息，以及如何通过 BFS 来扩展搜索范围。

### 所选高星题解

#### 题解1：XL4453 (赞：7)
**星级：5星**
**关键亮点：**
- 使用 `map` 存储点的信息，避免了空间不足的问题。
- 通过 BFS 从已知点的周围点开始搜索，逐步扩展，确保找到最近的合法点。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    for(int l=0;l<=3;l++)
    if(f[make_pair(x[i]+dx[l],y[i]+dy[l])]!=-1)
    q.push(make_pair(x[i]+dx[l],y[i]+dy[l])),
    ans[make_pair(x[i]+dx[l],y[i]+dy[l])]=make_pair(x[i]+dx[l],y[i]+dy[l]);
}
while(!q.empty()){
    nx=q.front().first;
    ny=q.front().second;
    for(int i=0;i<=3;i++){
        if(f[make_pair(nx+dx[i],ny+dy[i])]==-1){
            f[make_pair(nx+dx[i],ny+dy[i])]=1;
            ans[make_pair(nx+dx[i],ny+dy[i])]=ans[make_pair(nx,ny)];
            q.push(make_pair(nx+dx[i],ny+dy[i]));
        }
    }
    q.pop();
}
```

#### 题解2：Otomachi_Una_ (赞：4)
**星级：4星**
**关键亮点：**
- 使用 `map` 套 `map` 来存储点的信息，处理复杂但有效。
- 通过 BFS 从边缘点开始搜索，逐步扩展，确保找到最近的合法点。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
for(int i=1;i<=n;i++)
    for(int j=0;j<4;j++)
        if(!M[x[i]+dx[j]][y[i]+dy[j]]){
            sx[i]=x[i]+dx[j];
            sy[i]=y[i]+dy[j];
            vis[i]=true;
            q.push(i);
        }
while(!q.empty()){
    int p=q.front();
    q.pop();
    for(int i=0;i<4;i++)
        if(M[x[p]+dx[i]][y[p]+dy[i]]){
            int k=M[x[p]+dx[i]][y[p]+dy[i]];
            if(!vis[k]){
                sx[k]=sx[p];
                sy[k]=sy[p];
                vis[k]=true;
                q.push(k);
            }
        }
}
```

#### 题解3：songge888 (赞：2)
**星级：4星**
**关键亮点：**
- 使用 `map` 存储点的信息，避免了空间不足的问题。
- 通过 BFS 从已知点的周围点开始搜索，逐步扩展，确保找到最近的合法点。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    for(int j=0;j<4;j++){
        int xx=a[i].x+dx[j],yy=a[i].y+dy[j];
        if(!mp[{xx,yy}]){
            ans[i]={xx,yy};
            vis[i]++;
            q.push(i);
            break;
        }
    } 
}
bfs();
```

### 最优关键思路或技巧
- 使用 `map` 或 `map` 套 `map` 来存储点的信息，避免空间不足的问题。
- 通过 BFS 从已知点的周围点开始搜索，逐步扩展，确保找到最近的合法点。
- 代码结构清晰，易于理解。

### 可拓展之处
- 类似的问题可以使用相同的 BFS 思路来解决，例如在网格图中寻找最短路径或最近的点。
- 可以扩展到三维空间，使用类似的方法来寻找最近的点。

### 推荐题目
1. P1141 01迷宫
2. P1443 马的遍历
3. P1162 填涂颜色

---
处理用时：37.72秒