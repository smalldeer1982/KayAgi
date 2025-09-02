# 题目信息

# L-shapes

## 题目描述

An L-shape is a figure on gridded paper that looks like the first four pictures below. An L-shape contains exactly three shaded cells (denoted by \*), which can be rotated in any way.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722F/c4bb8e8c5c94521e87ed2d5ba5ef373384bb7be7.png)You are given a rectangular grid. Determine if it contains L-shapes only, where L-shapes can't touch an edge or corner. More formally:

- Each shaded cell in the grid is part of exactly one L-shape, and
- no two L-shapes are adjacent by edge or corner.

For example, the last two grids in the picture above do not satisfy the condition because the two L-shapes touch by corner and edge, respectively.

## 样例 #1

### 输入

```
10
6 10
........**
.**......*
..*..*....
.....**...
...*.....*
..**....**
6 10
....*...**
.**......*
..*..*....
.....**...
...*.....*
..**....**
3 3
...
***
...
4 4
.*..
**..
..**
..*.
5 4
.*..
**..
....
..**
..*.
3 2
.*
**
*.
2 3
*..
.**
3 2
..
**
*.
3 3
.**
*.*
**.
3 3
..*
.**
..*```

### 输出

```
YES
NO
NO
NO
YES
NO
NO
YES
NO
NO```

# AI分析结果

### 题目内容重写

#### L型图案

**题目描述**

L型图案是指在网格纸上看起来像下面前四张图片的图形。一个L型图案恰好包含三个阴影单元格（用`*`表示），并且可以以任何方式旋转。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722F/c4bb8e8c5c94521e87ed2d5ba5ef373384bb7be7.png)

给定一个矩形网格，判断它是否仅包含L型图案，且这些L型图案不能通过边或角接触。更正式地说：

- 网格中的每个阴影单元格必须恰好属于一个L型图案。
- 任何两个L型图案不能通过边或角相邻。

例如，上图中的最后两个网格不满足条件，因为两个L型图案分别通过角和边接触。

**样例 #1**

**输入**

```
10
6 10
........**
.**......*
..*..*....
.....**...
...*.....*
..**....**
6 10
....*...**
.**......*
..*..*....
.....**...
...*.....*
..**....**
3 3
...
***
...
4 4
.*..
**..
..**
..*.
5 4
.*..
**..
....
..**
..*.
3 2
.*
**
*.
2 3
*..
.**
3 2
..
**
*.
3 3
.**
*.*
**.
3 3
..*
.**
..*
```

**输出**

```
YES
NO
NO
NO
YES
NO
NO
YES
NO
NO
```

### 题解分析与结论

#### 综合分析

本题的核心在于判断网格中是否仅包含L型图案，并且这些L型图案不能通过边或角接触。题解中主要有以下几种思路：

1. **直接枚举L型图案的四种可能形态**：通过枚举L型图案的四种旋转形态，检查每个`*`是否属于一个L型图案，并确保L型图案之间不相邻。
2. **并查集维护连通块**：使用并查集维护`*`的连通块，检查每个连通块的大小是否为3，并且不满足直线或对角线上的条件。
3. **搜索与标记**：通过搜索每个`*`的连通块，检查其大小是否为3，并确保L型图案之间不相邻。

#### 最优关键思路

最优的思路是**直接枚举L型图案的四种可能形态**，通过遍历网格中的每个`*`，检查其是否属于一个L型图案，并确保L型图案之间不相邻。这种方法思路清晰，代码实现简单，且时间复杂度较低。

#### 可拓展之处

类似的问题可以扩展到其他形状的图案判断，如T型、十字型等。可以通过枚举这些形状的旋转形态，并检查其是否满足条件。

#### 推荐题目

1. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

### 精选题解

#### 题解1：Binary_Lee (★★★★★)

**关键亮点**：
- 直接枚举L型图案的四种可能形态，思路清晰。
- 通过标记已处理的`*`，确保每个`*`只属于一个L型图案。
- 代码简洁，时间复杂度较低。

**核心代码**：
```cpp
void search(int i,int j){
	if(a[i+1][j]&&a[i+1][j+1]&&!a[i-1][j-1]&&!a[i-1][j]&&!a[i-1][j+1]&&
	   !a[i][j-1]&&!a[i][j+1]&&!a[i][j+2]&&!a[i+1][j-1]&&!a[i+1][j+2]&&
	   !a[i+2][j-1]&&!a[i+2][j]&&!a[i+2][j+1]&&!a[i+2][j+2]){
		a[i][j]=a[i+1][j]=a[i+1][j+1]=0;
		return ;
	}
	// 其他三种形态的检查类似
}
```

#### 题解2：lihanwen12 (★★★★)

**关键亮点**：
- 通过扫描每个`*`，检查其是否属于一个L型图案。
- 使用标记数组记录已处理的`*`，确保每个`*`只属于一个L型图案。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
if(leixing==1){
	f[i][j]=1;
	f[i-1][j]=1;
	f[i][j+1]=1;
}
// 其他三种形态的标记类似
```

#### 题解3：CodingShark (★★★★)

**关键亮点**：
- 使用BFS搜索每个`*`的连通块，检查其大小是否为3。
- 通过枚举直线和对角线的情况，确保L型图案之间不相邻。
- 代码实现较为复杂，但思路清晰。

**核心代码**：
```cpp
int bfs(int sx, int sy){
    int res = 0;
    queue<pair<int, int>> q;
    q.push({sx, sy}), vis[sx][sy] = true;
    while (q.size()){
        auto cur = q.front();
        q.pop(), res++;
        for (int i = 0; i < 8; i++){
            int tx = cur.first + dir[i][0], ty = cur.second + dir[i][1];
            if (1 <= tx && tx <= n && 1 <= ty && ty <= m && !vis[tx][ty])
                vis[tx][ty] = true, q.push({tx, ty});
        }
    }
    return res;
}
```

### 总结

本题的难点在于如何高效地判断L型图案的存在及其相邻关系。通过枚举L型图案的四种形态，并结合标记数组，可以有效地解决这一问题。推荐的题解思路清晰，代码简洁，适合学习和参考。

---
处理用时：55.03秒