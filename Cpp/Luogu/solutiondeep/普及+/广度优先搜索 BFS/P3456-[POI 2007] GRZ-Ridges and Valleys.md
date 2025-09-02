# 题目信息

# [POI 2007] GRZ-Ridges and Valleys

## 题目描述

**译自 POI 2007 Stage 2. Day 0「[Ridges and Valleys](https://szkopul.edu.pl/problemset/problem/rd6H05Dm8ME79sO3U9_f_ga_/site/?key=statement)」**

给定一个 $n \times n$ 的网格状地图，每个方格 $(i,j)$ 有一个高度 $w_{ij}$。如果两个方格有公共顶点，则它们是相邻的。

定义山峰和山谷如下：
* 均由地图上的一个连通块组成；
* 所有方格高度都相同；
* 周围的方格（即不属于山峰或山谷但与山峰或山谷相邻的格子）高度均大于山谷的高度，或小于山峰的高度。

求地图内山峰和山谷的数量。特别地，如果整个地图方格的高度均相同，则整个地图既是一个山谷，也是一个山峰。

## 样例 #1

### 输入

```
5
8 8 8 7 7
7 7 8 8 7
7 7 7 7 7
7 8 8 7 8
7 8 8 8 8```

### 输出

```
2 1```

## 样例 #2

### 输入

```
5
5 7 8 3 1
5 5 7 6 6
6 6 6 2 8
5 7 2 5 8
7 1 0 1 7```

### 输出

```
3 3```

# AI分析结果

### 综合分析与结论

这些题解主要围绕BFS和DFS两种搜索算法展开，核心思路是通过遍历网格中的每个连通块，判断其是否为山峰或山谷。难点在于如何高效地判断一个连通块是否满足山峰或山谷的条件，以及如何处理边界情况和特殊情况（如整个地图高度相同）。

大多数题解都采用了BFS或DFS来遍历连通块，并在搜索过程中记录周围方格的高度信息，从而判断当前连通块是否为山峰或山谷。部分题解还提到了优化技巧，如提前终止搜索、标记已访问的方格等。

### 所选高星题解

#### 1. 作者：李尧 (5星)
- **关键亮点**：代码结构清晰，BFS实现简洁，通过`flag`变量高效判断连通块是否为山峰或山谷。特别处理了全地图高度相同的情况。
- **个人心得**：作者提到多次WA的经历，强调了注意八个方向的搜索和0值的处理，提醒读者注意细节。

```cpp
void bfs(int sx,int sy){
    int col=a[sx][sy];
    q.push(Node(sx,sy));
    for(int j=0;j<8;j++){
        int xx=sx+dx[j];
        int yy=sy+dy[j];
        if(xx>=1&&xx<=n&&yy>=1&&yy<=n&&a[xx][yy]!=col){
            if(p==-1) p=a[xx][yy];
            else if((p-col>0&&a[xx][yy]-col<0)||(p-col<0&&a[xx][yy]-col>0)) {
                flag=true;
                break;
            }
        }
    }
    while(!q.empty()){
        Node cur=q.front();
        for(int i=0;i<8;i++){
            int nx=cur.x+dx[i];
            int ny=cur.y+dy[i];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=n&&!v[nx][ny]&&a[nx][ny]==col){
                v[nx][ny]=true;
                q.push(Node(nx,ny));
                if(!flag)
                    for(int j=0;j<8;j++){
                        int xx=nx+dx[j];
                        int yy=ny+dy[j];
                        if(xx>=1&&xx<=n&&yy>=1&&yy<=n&&a[xx][yy]!=col){
                            if(p==-1) p=a[xx][yy];
                            else if((p-col>0&&a[xx][yy]-col<0)||(p-col<0&&a[xx][yy]-col>0)) {
                                flag=true;
                                break;
                            }
                        }
                    }
            }           
        }
        q.pop();    
    }
    if(flag) return;
    if(p<col) sf++;
    else sg++;
}
```

#### 2. 作者：FCBM71 (4星)
- **关键亮点**：通过`ifhigh`和`iflow`两个布尔变量简洁地判断连通块是否为山峰或山谷，代码逻辑清晰，易于理解。
- **个人心得**：作者强调了BFS的核心思路，并提供了简洁的实现方式。

```cpp
void bfs(int p,int q){
    vis[p][q]=1;
    queue<int>x,y;
    x.push(p);y.push(q);
    bool ifhigh=1,iflow=1;
    while(!x.empty()){
        rg int xs=x.front();
        rg int ys=y.front();
        for(rg int i=0;i<=7;++i){
            rg int xf=xs+dx[i];
            rg int yf=ys+dy[i];
            if(xf>0&&xf<=n&&yf>0&&yf<=n){
                if(a[xf][yf]==a[xs][ys]){
                    if(!vis[xf][yf]){
                        x.push(xf);y.push(yf);
                        vis[xf][yf]=1;
                    }
                }
                if(a[xf][yf]<a[xs][ys])iflow=0;
                if(a[xf][yf]>a[xs][ys])ifhigh=0;
            }
        }
        x.pop();y.pop();
    }
    if(ifhigh)++ans1;
    if(iflow)++ans2;
}
```

#### 3. 作者：sounds_666 (4星)
- **关键亮点**：通过两个独立的BFS函数分别判断山峰和山谷，代码结构清晰，且通过`rule`函数处理越界情况，增强了代码的可读性。
- **个人心得**：作者强调了在BFS中不要直接返回，而是让搜索完成，以确保找到完整的连通块。

```cpp
bool bfs(int pp,int qq){
    bool flag=1;
    q.push(mk(pp,qq));
    vis[pp][qq]=1;
    while(!q.empty()){
        int x=q.front().first,y=q.front().second;
        q.pop();
        for(int i=0;i<8;i++){
            int nx=x+dx[i],ny=y+dy[i];
            if(rule(nx,ny))continue;
            if(mapp[nx][ny]>mapp[x][y])flag=0;
            else if(!vis[nx][ny]&&mapp[x][y]==mapp[nx][ny]){
                vis[nx][ny]=1;
                q.push(mk(nx,ny));
            }
        }
    }
    if(flag)return 1;
    else return 0;
}
```

### 最优关键思路与技巧

1. **BFS/DFS遍历连通块**：通过BFS或DFS遍历每个连通块，确保所有相同高度的方格都被访问到。
2. **高效判断山峰/山谷**：在搜索过程中，记录周围方格的高度信息，通过布尔变量（如`ifhigh`和`iflow`）判断连通块是否为山峰或山谷。
3. **处理特殊情况**：特别处理全地图高度相同的情况，确保程序能够正确处理这种边界情况。
4. **优化搜索**：通过标记已访问的方格，避免重复搜索，提高算法效率。

### 拓展思路与类似题目

- **类似题目**：
  1. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
  2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
  3. [P1131 八数码难题](https://www.luogu.com.cn/problem/P1131)

- **拓展思路**：在处理网格类问题时，BFS和DFS是常用的搜索算法，可以通过类似的思路解决其他连通块问题，如迷宫问题、岛屿问题等。

---
处理用时：46.38秒