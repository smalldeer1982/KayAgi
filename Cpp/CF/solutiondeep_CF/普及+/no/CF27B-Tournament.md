# 题目信息

# Tournament

## 题目描述

The tournament «Sleepyhead-2010» in the rapid falling asleep has just finished in Berland. $ n $ best participants from the country have participated in it. The tournament consists of games, each of them is a match between two participants. $ n·(n-1)/2 $ games were played during the tournament, and each participant had a match with each other participant.

The rules of the game are quite simple — the participant who falls asleep first wins. The secretary made a record of each game in the form « $ x_{i} $ $ y_{i} $ », where $ x_{i} $ and $ y_{i} $ are the numbers of participants. The first number in each pair is a winner (i.e. $ x_{i} $ is a winner and $ y_{i} $ is a loser). There is no draws.

Recently researches form the «Institute Of Sleep» have found that every person is characterized by a value $ p_{j} $ — the speed of falling asleep. The person who has lower speed wins. Every person has its own value $ p_{j} $ , constant during the life.

It is known that all participants of the tournament have distinct speeds of falling asleep. Also it was found that the secretary made records about all the games except one. You are to find the result of the missing game.

## 样例 #1

### 输入

```
4
4 2
4 1
2 3
2 1
3 1
```

### 输出

```
4 3
```

# AI分析结果

### 题目内容
# Tournament

## 题目描述
“Sleepyhead - 2010”嗜睡锦标赛刚刚在Berland落下帷幕。该国最优秀的$n$名参与者参加了此次比赛。锦标赛由多场比赛组成，每场比赛都是两名参与者之间的对决。锦标赛期间共进行了$n·(n - 1)/2$场比赛，每位参与者都与其他每位参与者进行了一场比赛。

比赛规则相当简单——先睡着的参与者获胜。秘书以“$x_{i}$ $y_{i}$”的形式记录每场比赛，其中$x_{i}$和$y_{i}$是参与者的编号。每对中的第一个数字是获胜者（即$x_{i}$是获胜者，$y_{i}$是失败者）。比赛不存在平局。

最近，“睡眠研究所”的研究人员发现，每个人都有一个特征值$p_{j}$——入睡速度。入睡速度较慢的人获胜。每个人都有自己独特的$p_{j}$值，且一生保持不变。

已知锦标赛的所有参与者入睡速度各不相同。此外还发现，秘书记录了除一场比赛之外的所有比赛结果。你需要找出这场缺失比赛的结果。

## 样例 #1
### 输入
```
4
4 2
4 1
2 3
2 1
3 1
```
### 输出
```
4 3
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路大多围绕确定未比赛的两人以及判断他们的胜负关系展开。多数题解通过统计比赛场次找到未比赛的两人，再依据胜场次数或选手间的实力传递关系判断胜负。

思路方面，部分题解利用完全图边数特性，通过邻接矩阵或数组记录比赛情况，找到未比赛的两人；另一部分题解从入度、出度角度出发，找出比赛场次非$n - 1$的两人。判断胜负时，有的通过比较两人胜场次数，有的通过检查选手间实力传递关系。

算法要点在于图的构建与遍历，以及对比赛数据的统计分析。解决难点在于如何准确判断未比赛两人的胜负关系，不同题解采用了不同方法。

### 所选的题解
- **作者：Rainbow_qwq (赞：4)  星级：4星**
    - **关键亮点**：思路清晰，利用邻接矩阵记录比赛，通过比较两人的胜场次数确定胜负关系，代码简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
#define TP long long
inline TP read(){//快读
    char c=getchar();TP x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int n,e[55][55],deg[55];
int main()
{
    n=read();
    int m=n*(n-1)/2-1;//边数
    For(i,1,m){//边数
        int u=read(),v=read();
        e[max(u,v)][min(u,v)]++;//编号大的点在前面
        deg[u]++;//u赢了比赛，出度+1
    }
    For(i,1,n)
        For(j,1,i-1)
            if(!e[i][j]){
                if(deg[i]>deg[j])printf("%d %d\n",i,j);//比赛赢的人输出在前面
                else printf("%d %d\n",j,i);
            }
    return 0;
}
```
    - **核心实现思想**：用邻接矩阵`e`记录比赛情况，`deg`数组统计每个选手的胜场次数。遍历所有可能的比赛对，若某对选手未比赛（`e[i][j]==0`），则比较他们的胜场次数`deg[i]`和`deg[j]`，输出胜场多的选手在前。
- **作者：Moon_Lighter (赞：3)  星级：4星**
    - **关键亮点**：从比赛场次和选手实力关系出发，通过记录每个选手的强手来判断未比赛两人的胜负关系，逻辑清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define inf 10000000
#define pi acos(-1.0)
#define eps 1e-8
#define seed 131
#define min(a,b) a<b?a:b
#define max(a,b) a<b?b:a
using namespace std;
typedef pair<int,int> pa;
typedef unsigned long long ULL;
typedef long long LL;
const int maxn=100005;
int d[55];
vector<int>vec[55];
int main()
{
    int n;
    scanf("%d",&n);
    int num=n*(n-1)/2-1;
    memset(d,0,sizeof(d));
    int a,b;
    for(int i=1;i<=num;i++)
    {
        scanf("%d%d",&a,&b);
        vec[b].push_back(a);
        d[a]++;
        d[b]++;
    }
    int u[2];
    int e=0;
    for(int i=1;i<=n;i++)
    {
        if(d[i]!=n-1)
            u[e++]=i;
    }
    bool flag=true;
    for(int i=0;i<vec[u[0]].size();i++)
    {
        if(vec[u[0]][i]==u[1]||find(vec[vec[u[0]][i]].begin(),vec[vec[u[0]][i]].end(),u[1])!=vec[vec[u[0]][i]].end())
        {
            flag=false;
            break;
        }
    }
    if(flag)
        printf("%d %d\n",u[0],u[1]);
    else
        printf("%d %d\n",u[1],u[0]);
    return 0;
}
```
    - **核心实现思想**：`vec`数组记录每个选手的强手（即打败该选手的人），`d`数组统计每个选手的比赛场次。先找出比赛场次非$n - 1$的两人`u[0]`和`u[1]`，然后检查`u[0]`的强手中是否有`u[1]`或者`u[0]`强手的强手中是否有`u[1]`，以此判断两人的胜负关系。
- **作者：Fool_Fish (赞：0)  星级：4星**
    - **关键亮点**：通过证明得出在缺一条边的完全竞赛图中，出度大的点实力更强，以此来确定未比赛两人的胜负关系，思路独特。
    - **重点代码**：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int MAXN=55;
bool g[MAXN][MAXN];
int out[MAXN];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1,u,v;i<=(n*(n-1)/2-1);i++){
        scanf("%d %d",&u,&v);
        g[u][v]=g[v][u]=true;
        out[u]++;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(g[i][j]==0 && i!=j){
                if(out[i]<out[j]){
                    printf("%d %d",j,i);
                }
                else{
                    printf("%d %d",i,j);
                }
                return 0;
            }
        }
    }
    return 0;
}
```
    - **核心实现思想**：`g`数组标记选手之间是否比赛过，`out`数组统计每个选手的出度。遍历所有选手对，找到未比赛的两人（`g[i][j]==0 && i!=j`），比较他们的出度`out[i]`和`out[j]`，输出出度大的选手在前。

### 最优关键思路或技巧
利用图论中完全图的性质，通过统计比赛场次（入度、出度）或构建邻接矩阵来处理数据，在判断胜负关系时，部分题解通过证明得出的出度与实力关系，简化了判断过程，是较为巧妙的思路。

### 可拓展之处
此类题目属于竞赛图相关问题，类似套路可用于解决一些需要根据比赛结果或选手关系进行排序、判断的问题。例如一些体育比赛赛程安排、选手排名等场景。

### 推荐洛谷题目
- [P1129 开车旅行](https://www.luogu.com.cn/problem/P1129)
- [P2746 [USACO5.3]校园网Network of Schools](https://www.luogu.com.cn/problem/P2746)
- [P3387 缩点](https://www.luogu.com.cn/problem/P3387) 

---
处理用时：76.48秒