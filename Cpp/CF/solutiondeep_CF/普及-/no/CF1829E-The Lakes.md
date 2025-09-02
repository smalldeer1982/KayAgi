# 题目信息

# The Lakes

## 题目描述

You are given an $ n \times m $ grid $ a $ of non-negative integers. The value $ a_{i,j} $ represents the depth of water at the $ i $ -th row and $ j $ -th column.

A lake is a set of cells such that:

- each cell in the set has $ a_{i,j} > 0 $ , and
- there exists a path between any pair of cells in the lake by going up, down, left, or right a number of times and without stepping on a cell with $ a_{i,j} = 0 $ .

The volume of a lake is the sum of depths of all the cells in the lake.

Find the largest volume of a lake in the grid.

## 样例 #1

### 输入

```
5
3 3
1 2 0
3 4 0
0 0 5
1 1
0
3 3
0 1 1
1 0 1
1 1 1
5 5
1 1 1 1 1
1 0 0 0 1
1 0 5 0 1
1 0 0 0 1
1 1 1 1 1
5 5
1 1 1 1 1
1 0 0 0 1
1 1 4 0 1
1 0 0 0 1
1 1 1 1 1```

### 输出

```
10
0
7
16
21```

# AI分析结果

### 题目翻译
你得到了一个由非负整数组成的 $n \times m$ 网格 $a$。值 $a_{i,j}$ 表示第 $i$ 行第 $j$ 列的水深。

湖是一组单元格，满足以下条件：
- 该集合中的每个单元格都有 $a_{i,j} > 0$。
- 通过上下左右移动若干次，且不经过 $a_{i,j} = 0$ 的单元格，集合中任意两个单元格之间都存在一条路径。

湖的体积是湖中所有单元格深度的总和。

找出网格中最大的湖的体积。

### 算法分类
搜索

### 综合分析与结论
这些题解主要围绕搜索算法来解决连通块问题，以找到最大湖的体积。大部分题解采用了广度优先搜索（BFS）或深度优先搜索（DFS）的方法，通过遍历网格中的每个非零且未访问过的单元格，标记已访问的单元格，统计连通块的体积，并更新最大体积。少部分题解使用了并查集的方法，将相邻的非零单元格合并，最后找出最大的连通块体积。

### 所选的题解
- **作者：zhlzt (赞：7)，4星**
    - **关键亮点**：思路清晰，代码结构简洁，详细注释了 BFS 函数的功能，易于理解。
    - **代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int x,y;
};
int p[1010][1010],vis[1010][1010];
int a[]={0,1,0,-1},b[]={1,0,-1,0};
int bfs(int x,int y,int n,int m){//返回这个连通块中所有点的值之和
    queue<node>q;node fa,sn;
    fa.x=x,fa.y=y;int ans=0;
    q.push(fa),vis[x][y]=1;
    while(!q.empty()){
        fa=q.front();q.pop();
        ans+=p[fa.x][fa.y];
        for(int i=0;i<4;i++){
            sn.x=fa.x+a[i],sn.y=fa.y+b[i];
            if(sn.x<1||sn.x>n||sn.y<1||sn.y>m) continue;
            if(p[sn.x][sn.y]==0||vis[sn.x][sn.y]==1) continue;
            q.push(sn);vis[sn.x][sn.y]=1;
        }
    }
    return ans;
}
int main(){
    int t;scanf("%d",&t);
    while(t--){
        int n,m;scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++) 
                scanf("%d",&p[i][j]),vis[i][j]=0;
        int ans=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(vis[i][j]==0&&p[i][j]>0) 
                    ans=max(ans,bfs(i,j,n,m));
        printf("%d\n",ans);
    }
    return 0;
}
```
    - **核心实现思想**：定义了一个 BFS 函数，使用队列存储待访问的节点，通过方向数组遍历相邻节点，将符合条件的节点加入队列并标记为已访问，同时累加节点的值，最后返回连通块的体积。

- **作者：cjh20090318 (赞：4)，4星**
    - **关键亮点**：明确指出本题有多组数据，需要清空访问数组，避免错误，代码规范，注释清晰。
    - **代码实现**：
```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#include<queue>
#include<utility>
#define mp std::make_pair
typedef std::pair<int,int> PII;
int n,m;
int a[1001][1001];//水深。
bool b[1001][1001];//访问数组。
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};//方向数组。
void solve(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&a[i][j]),b[i][j]=0;//记得清空访问数组！
    std::queue<PII> Q;
    int ans=0;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
        int w=0;
        if(!a[i][j]||b[i][j]) continue;//保证当前位置非 0 且未访问。
        Q.push(mp(i,j));
        for(int x,y;!Q.empty();){
            x=Q.front().first,y=Q.front().second;Q.pop();
            if(b[x][y]) continue;//访问过则退出。
            b[x][y]=1;//标记访问数组。
            w+=a[x][y];//统计权值。
            for(int k=0,nx,ny;k<4;k++){
                nx=x+dx[k],ny=y+dy[k];
                if(nx>0&&nx<=n&&ny>0&&ny<=m&&a[nx][ny]) Q.push(mp(nx,ny));//符合范围则继续广搜。
            }
        }
        ans=std::max(ans,w);//更新答案。
    }
    printf("%d\n",ans);
}
int main(){
    int T;scanf("%d",&T);
    while(T--) solve();
    return 0;
}
```
    - **核心实现思想**：定义了一个 solve 函数，使用队列存储待访问的节点对，通过方向数组遍历相邻节点，将符合条件的节点对加入队列并标记为已访问，同时累加节点的值，最后更新最大体积。

- **作者：Jorisy (赞：1)，4星**
    - **关键亮点**：使用 DFS 算法，代码简洁，逻辑清晰，通过递归调用实现深度优先搜索。
    - **代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int X[]={1,0,-1,0};
const int Y[]={0,1,0,-1};
int n,m,a[1005][1005],f[1005][1005],s,maxs;

void dfs(int x,int y)
{
    s+=a[x][y];//累加
    for(int i=0;i<4;i++)
    {
        int x_=x+X[i],y_=y+Y[i];
        if(x_<1||y_<1||x_>n||y_>m||!a[x_][y_]||f[x_][y_]) continue;
        f[x_][y_]=1;//标记
        dfs(x_,y_);
    }
}

void sol()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
            f[i][j]=0;
        }
    }
    maxs=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(f[i][j]||!a[i][j]) continue;
            s=0;//清零
            f[i][j]=1;//标记
            dfs(i,j);
            maxs=max(maxs,s);//计算当前最大的总权值
        }
    }
    cout<<maxs<<endl;
}

int main()
{
    int t;
    cin>>t;
    while(t--) sol(); 
    return 0;
}
```
    - **核心实现思想**：定义了一个 DFS 函数，通过递归调用遍历相邻节点，将符合条件的节点标记为已访问，同时累加节点的值，最后更新最大体积。

### 最优关键思路或技巧
- 使用方向数组（如 `int a[]={0,1,0,-1},b[]={1,0,-1,0}`）来简化上下左右移动的判断。
- 对于多组数据，每次处理前要清空访问数组，避免影响后续结果。
- 可以使用 BFS 或 DFS 来遍历连通块，根据个人习惯选择。

### 拓展思路
同类型题通常涉及连通块问题，如岛屿数量、最大岛屿面积等。类似算法套路包括使用搜索算法（BFS 或 DFS）遍历图或网格，标记已访问的节点，统计相关信息。

### 推荐题目
- [P1596 湖计数](https://www.luogu.com.cn/problem/P1596)
- [P2002 消息扩散](https://www.luogu.com.cn/problem/P2002)
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)

### 个人心得摘录与总结
- **作者：zajasi**：在构造简单数据时发现了一个 hack 数据，意识到刚开始扫的时候没有判 $0$ 不能进深搜，导致从 $(1,1)$ 开始搜，调整后解决问题。总结：在搜索时要注意判断起始点是否为 $0$，避免错误。

---
处理用时：58.36秒