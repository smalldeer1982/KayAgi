# 题目信息

# Greg and Graph

## 题目描述

Greg 有一个有边权的有向图，包含 $n$ 个点。这个图的每两个点之间都有两个方向的边。Greg 喜欢用他的图玩游戏，现在他发明了一种新游戏：

- 游戏包含 $n$ 步。
- 第 $i$ 步 Greg 从图中删掉编号为 $x_i$ 的点。当删除一个点时，这个点的出边和入边都会被删除。
- 在执行每一步之前，Greg 想知道所有点对间最短路长度的和。最短路可以经过任何没删掉的点。换句话说，如果我们假设 $d(i, v, u)$ 是在删掉 $x_i$ 前 $v$ 和 $u$ 间的最短路长度，那么Greg想知道下面这个求和的值：$\sum_{v, u, v \neq u} d(i, v, u)$ 。

帮帮 Greg，输出每一步之前要求的值。

## 样例 #1

### 输入

```
1
0
1
```

### 输出

```
0 ```

## 样例 #2

### 输入

```
2
0 5
4 0
1 2
```

### 输出

```
9 0 ```

## 样例 #3

### 输入

```
4
0 3 1 1
6 0 400 1
2 4 0 1
1 1 1 0
4 1 2 3
```

### 输出

```
17 23 404 0 ```

# AI分析结果

### 题目内容
# Greg和图

## 题目描述
Greg有一个带边权的有向图，包含$n$个点。该图中每两个点之间都有两个方向的边。Greg喜欢用他的图玩游戏，现在他发明了一种新游戏：
- 游戏包含$n$步。
- 第$i$步Greg从图中删掉编号为$x_i$的点。当删除一个点时，这个点的出边和入边都会被删除。
- 在执行每一步之前，Greg想知道所有点对间最短路长度的和。最短路可以经过任何未删掉的点。换句话说，如果我们假设$d(i, v, u)$是在删掉$x_i$前$v$和$u$间的最短路长度，那么Greg想知道下面这个求和的值：$\sum_{v, u, v \neq u} d(i, v, u)$ 。

帮帮Greg，输出每一步之前要求的值。

## 样例 #1
### 输入
```
1
0
1
```
### 输出
```
0 ```
## 样例 #2
### 输入
```
2
0 5
4 0
1 2
```
### 输出
```
9 0 ```
## 样例 #3
### 输入
```
4
0 3 1 1
6 0 400 1
2 4 0 1
1 1 1 0
4 1 2 3
```
### 输出
```
17 23 404 0 ```

### 综合分析与结论
所有题解思路均为采用逆向思维，将每次删点转化为加点操作，利用Floyd算法解决问题。因为正向按题意每次删除点后用Floyd计算最短路和，时间复杂度为$O(n^4)$会超时，而逆向思维下每次加点并更新最短路，时间复杂度降为$O(n^3)$。各题解在思路和算法要点上基本一致，区别主要在于代码实现的细节、注释详细程度以及代码风格。

### 所选的题解
- **作者：Dream_weavers (5星)**
    - **关键亮点**：思路阐述清晰，先点明正向思路的问题，再详细说明逆向思维的解法，核心代码简洁明了，注释恰到好处。
    - **核心代码**：
```cpp
//输入n
//输入有向带权图
//输入数组x
for(int l=n;l>=1;l--){//循环每一个点
    int k=x[l];vis[k]=1;//标记并记录添加的点
        
    for(int i=1;i<=n;i++)//进行一次Floyd	
        for(int j=1;j<=n;j++)
            d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
   
    sum=0;
    for(int i=1;i<=n;i++)//统计最短路的和
        for(int j=1;j<=n;j++)
            if(vis[i]&&vis[j])
                sum+=d[i][j];
    ans[l]=sum;//记录答案
}
//倒序输出答案
```
    - **核心实现思想**：从后往前遍历要删除的点，将其作为新加入的点，利用Floyd算法更新所有点对间的最短路径，统计当前存在点的最短路之和并记录，最后倒序输出答案。

- **作者：RainAir (4星)**
    - **关键亮点**：代码结构完整，包含快读模板，对变量的定义和用途有清晰注释，解题报告简洁明了。
    - **核心代码**：
```cpp
// Luogu 交不上去只能去 Vjudge
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

namespace fastIO{
    // 快读模板部分省略
};
using namespace fastIO;

const int MAXN = 500 + 5;
int f[MAXN][MAXN],N;
int del[MAXN];
bool tag[MAXN];
LL ans[MAXN];

int main(){
    read(N);
    FOR(i,1,N)
        FOR(j,1,N)
        read(f[i][j]);
    FOR(i,1,N) read(del[i]);
    RFOR(p,N,1){
        int k = del[p];
        tag[k] = true;
        FOR(i,1,N){
            FOR(j,1,N){
                f[i][j] = std::min(f[i][j],f[i][k] + f[k][j]);
                if(tag[i] && tag[j]) ans[p] += f[i][j];
            }
        }
    }
    FOR(i,1,N) printf("%I64d ",ans[i]);
    return 0;
}
```
    - **核心实现思想**：与其他题解类似，倒序枚举删除点，将其作为新加入点更新最短路，统计当前图中所有点对最短路之和并存入数组，最后顺序输出结果。

- **作者：Gerald_Chen (4星)**
    - **关键亮点**：对题意和分析部分阐述详细，代码简洁易懂，变量命名有一定表意性。
    - **核心代码**：
```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=501;
int del[N]/*要删除的点*/,dist[N][N],n;
long long ans[N];
bool avi[N]/*(available)当前该点是否在图中*/;
inline int read()
{
    int sum=0;
    char ch=getchar();
    while(!(ch>='0' && ch<='9'))
        ch=getchar();
    while(ch>='0' && ch<='9')
        sum=sum*10+ch-'0',ch=getchar();
    return sum;
}
int main()
{
    n=read();
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j)
            dist[i][j]=read();
    for(int i=1; i<=n; ++i)
        del[i]=read();
    for(int cur=n; cur; --cur) {
        int k=del[cur];
        avi[k]=true;//将当前点加入图
        //Floyd
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                if(i!=j) {
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                    if(avi[i] && avi[j])//只有i与j都在图中最短路才有意义
                        ans[cur]+=dist[i][j];//当前删除过程所求的答案
                }
    }
    for(int i=1; i<=n; ++i)
        printf("%I64d ",ans[i]);//按照要求输出
    return 0;
}
```
    - **核心实现思想**：从后往前处理要删除的点，将其加入图中，利用Floyd算法更新最短路，统计当前图中有效点对的最短路之和，最后按顺序输出答案。

### 最优关键思路或技巧
采用逆向思维，将删点操作转化为加点操作，利用Floyd算法每次以新加入的点作为中转点更新所有点对间的最短路径，从而避免了正向删点带来的复杂处理和高时间复杂度问题。

### 可拓展之处
同类型题或类似算法套路：此类问题常涉及图论中动态变化的结构（点或边的增减）与最短路求解。常见套路是通过逆向思维将复杂的动态操作转化为易于处理的形式，结合经典图论算法（如Floyd、Dijkstra等）解决。例如在一些动态更新边权并求最短路的问题中，也可尝试逆向考虑边权变化顺序，简化计算过程。

### 洛谷相似题目推荐
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：同样涉及动态图的最短路问题，随着时间推移某些点会恢复可用，需计算不同时间点的最短路。
- [P3386 【模板】二分图匹配](https://www.luogu.com.cn/problem/P3386)：虽然是二分图匹配问题，但在处理一些动态二分图（如点或边动态增减）时，逆向思维和类似动态更新的思想可能会有帮助。
- [P2761 软件补丁问题](https://www.luogu.com.cn/problem/P2761)：该题将软件漏洞和补丁抽象为图的节点和边，通过一定的操作序列达到目标状态，可类比本题逆向思考操作顺序以优化求解过程。

### 个人心得摘录与总结
- **作者：tzl_Dedicatus545**：强调了本题要开`long long` ，否则会炸`int` 。同时指出在Floyd内更新最短路时不能在更新前对节点可用性进行判断，否则会遗漏经过新加入点的情况，应先更新再在后续统计答案时进行特判。总结为在处理图论算法结合动态节点操作时，要注意更新顺序和条件判断的位置，避免因错误的判断导致结果遗漏或错误。 

---
处理用时：42.28秒