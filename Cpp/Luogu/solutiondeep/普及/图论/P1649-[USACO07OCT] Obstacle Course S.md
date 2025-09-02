# 题目信息

# [USACO07OCT] Obstacle Course S

## 题目描述

Consider an N x N (1 <= N <= 100) square field composed of 1

by 1 tiles. Some of these tiles are impassible by cows and are marked with an 'x' in this 5 by 5 field that is challenging to navigate:

```cpp
. . B x . 
. x x A . 
. . . x . 
. x . . . 
. . x . . 
```
Bessie finds herself in one such field at location A and wants to move to location B in order to lick the salt block there.  Slow, lumbering creatures like cows do not like to turn and, of course, may only move parallel to the edges of the square field. For a given field, determine the minimum number of ninety degree turns in any path from A to B. The path may begin and end with Bessie facing in any direction. Bessie knows she can get to the salt lick.



## 说明/提示

只可以上下左右四个方向行走，并且不能走出这些格子之外。开始和结束时的方向可以任意。

### 数据范围及约定

对于全部数据，保证 $2\le N\le 100$。


## 样例 #1

### 输入

```
3
. x A
. . .
B x .```

### 输出

```
2```

# AI分析结果

### 综合分析与结论
这些题解主要围绕寻找从点A到点B的最少转弯次数展开，运用了DFS、BFS、最短路（Dijkstra、SPFA）等多种算法。各算法要点和解决难点如下：
- **DFS**：通过递归搜索所有可能路径，记录转弯次数。为避免超时，采用剪枝（如当前转弯次数大于已知最小转弯次数则返回）和记忆化搜索（记录到达某点的最小转弯次数）。
- **BFS**：逐层扩展节点，每次扩展四个方向，记录转弯次数。为保证结果最优，一个点可能多次入队，更新最小转弯次数。部分题解采用“洪水填充”优化，一次扩展一个方向上的所有可达点。
- **最短路算法**：将每个点拆成四个点表示四个方向，根据转弯情况构建带权图，使用Dijkstra或SPFA求解。

### 所选题解
- **作者：Lidy（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对DFS的剪枝操作有明确说明，便于理解。
    - **个人心得**：作者尝试用暴搜解题，意外AC，但指出方向数组顺序可能影响结果，体现了搜索算法的不确定性。
    - **核心代码**
```cpp
void dfs(int x,int y,int t,int k)
{
    if(k>=ans)return ;
    if(x==xn&&y==yn){ans=min(ans,k);bj=1;return ;}
    for(int i=0;i<4;i++)
    {
        int nx=dx[i]+x;int ny=dy[i]+y;
        if(nx<=0||nx>n||ny<=0||ny>n)continue;
        if(!a[nx][ny])
        {
            a[nx][ny]=-1;
            int f=0;
            if(i!=t)f=1;if(t==-1)f=0;
            dfs(nx,ny,i,k+f);
            a[nx][ny]=0;
        }
    }
}
```
核心思想：递归搜索四个方向，若方向改变则转弯次数加1，使用剪枝避免无效搜索。

- **作者：「QQ红包」（4星）**
    - **关键亮点**：采用BFS算法，对每个点可能多次入队更新最优解的处理方式解释清晰，代码结构合理。
    - **核心代码**
```cpp
while (!q.empty())
{
    node u;
    u=q.front();
    q.pop();
    if (u.d>ans) continue;
    for (int i=0;i<=3;i++)
    {
        node v;
        v.x=u.x+fx[i][0];
        v.y=u.y+fx[i][1];
        v.f=i;
        if (u.f==-1||u.f==v.f) v.d=u.d; else v.d=u.d+1;
        if (v.x<1||v.y<0||v.x>n||v.y>n) continue;
        if ((a[v.x][v.y]!=1&&v.d>d[v.x][v.y])||a[v.x][v.y]==0) continue;
        a[v.x][v.y]=233;
        d[v.x][v.y]=v.d;
        if (v.x==tx&&v.y==ty)
        {
            ans=min(ans,v.d);
            continue;
        }
        q.push(v);
    }
}
```
核心思想：BFS逐层扩展节点，根据方向判断转弯次数，更新每个点的最小转弯次数。

- **作者：GNAQ（4星）**
    - **关键亮点**：提出特殊的BFS扩展策略，通过“层”扩展节点，证明了新点转弯次数的计算方法，思路独特。
    - **核心代码**
```cpp
while (quex.size()>0)
{
    memset(teller,true,sizeof(teller));
    cachex=quex.front(); cachey=quey.front();
    if (cachex==ex && cachey==ey)
    {
        cout<<timex[ex][ey]<<endl;
        return 0;
    }
    for (int j=0;j<=3;j++)
    {
        for (int i=1;i<=n;i++) if (teller[j]==true) 
        {
            if (cachex+wayx[j]*i>=0 && cachex+wayx[j]*i<n && cachey+wayy[j]*i>=0 && cachey+wayy[j]*i<n)
            {
                if (mapx[cachex+wayx[j]*i][cachey+wayy[j]*i]=='.' && timex[cachex+wayx[j]*i][cachey+wayy[j]*i]==-1) 
                {
                    timex[cachex+wayx[j]*i][cachey+wayy[j]*i]=timex[cachex][cachey]+1;
                    quex.push(cachex+wayx[j]*i); quey.push(cachey+wayy[j]*i);
                }
                else if (mapx[cachex+wayx[j]*i][cachey+wayy[j]*i]=='x') teller[j]=false;
            }
            else teller[j]=false;
        }
    }
    quex.pop(); quey.pop();
}
```
核心思想：BFS扩展时，按“层”扩展四个方向，遇到障碍或越界停止，更新新点的转弯次数。

### 最优关键思路或技巧
- **记忆化搜索**：在DFS中使用记忆化数组记录到达某点的最小转弯次数，避免重复搜索，提高效率。
- **洪水填充**：在BFS中，一次扩展一个方向上的所有可达点，减少搜索次数，优化时间复杂度。
- **拆点建图**：将每个点拆成四个点表示四个方向，构建带权图，将问题转化为最短路问题求解。

### 可拓展之处
同类型题或类似算法套路：
- 迷宫问题变种，如求最大转弯次数、特定转弯规则下的路径等。
- 分层图最短路问题，可应用拆点建图的思想。

### 推荐题目
- P1144 最短路计数
- P1629 邮递员送信
- P3371 单源最短路径（弱化版）

### 个人心得总结
- **Lidy**：尝试用暴搜解题，发现方向数组顺序可能影响结果，提醒在使用搜索算法时要注意边界情况和算法的稳定性。
- **yjxyjx**：用DFS只有30分，改用BFS解决问题，认识到BFS在保证每个点只入队一次时时间复杂度更优，不同算法适用于不同场景。
- **s_ShotღMaki**：认为本题与普通BFS不同，需要全扩展掉，花费较多时间解决问题，强调对特殊情况的处理能力。 

---
处理用时：45.40秒