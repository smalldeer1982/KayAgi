# 题目信息

# Restore Graph

## 题目描述

Valera had an undirected connected graph without self-loops and multiple edges consisting of $ n $ vertices. The graph had an interesting property: there were at most $ k $ edges adjacent to each of its vertices. For convenience, we will assume that the graph vertices were indexed by integers from 1 to $ n $ .

One day Valera counted the shortest distances from one of the graph vertices to all other ones and wrote them out in array $ d $ . Thus, element $ d[i] $ of the array shows the shortest distance from the vertex Valera chose to vertex number $ i $ .

Then something irreparable terrible happened. Valera lost the initial graph. However, he still has the array $ d $ . Help him restore the lost graph.

## 样例 #1

### 输入

```
3 2
0 1 1
```

### 输出

```
3
1 2
1 3
3 2
```

## 样例 #2

### 输入

```
4 2
2 0 1 3
```

### 输出

```
3
1 3
1 4
2 3
```

## 样例 #3

### 输入

```
3 1
0 0 0
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 恢复图

## 题目描述
瓦莱拉有一个无向连通图，该图没有自环和重边，由 $n$ 个顶点组成。这个图有一个有趣的性质：每个顶点最多与 $k$ 条边相连。为了方便起见，我们假设图的顶点用从1到 $n$ 的整数进行索引。

有一天，瓦莱拉计算了从图中一个顶点到其他所有顶点的最短距离，并将它们写在数组 $d$ 中。因此，数组中的元素 $d[i]$ 表示从瓦莱拉选择的顶点到编号为 $i$ 的顶点的最短距离。

然后，发生了一些无法挽回的可怕事情。瓦莱拉丢失了初始图。然而，他仍然有数组 $d$ 。帮助他恢复丢失的图。

## 样例 #1
### 输入
```
3 2
0 1 1
```
### 输出
```
3
1 2
1 3
3 2
```
## 样例 #2
### 输入
```
4 2
2 0 1 3
```
### 输出
```
3
1 3
1 4
2 3
```
## 样例 #3
### 输入
```
3 1
0 0 0
```
### 输出
```
-1
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过分析最短路数组 $d$ 来构造满足条件的图，同时判断是否存在满足条件的图。主要依据是在边权为1的情况下，到某点距离为 $a_i$ 的点通常由距离为 $a_i - 1$ 的点连接而来，且每个点度数有限制。各题解在实现细节上有所不同，例如存储方式、判断无解条件的顺序以及连边的具体操作等。

### 所选的题解
- **作者：DinnerHunt (5星)**
  - **关键亮点**：思路清晰简洁，利用队列存储同距离的点，代码实现紧凑高效。通过从距离为0的点依次递增连边，并根据度数限制条件判断无解情况，逻辑严谨。
  - **重点代码**：
```cpp
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxd = 1e5+10;
int n,k,s,arr[maxd],flag,mx;
queue<int> que[maxd];
int main()
{
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&s);
        arr[s]++;
        que[s].push(i);
        mx = max(s,mx);
    }
    if(arr[0]!=1) flag=1;
    if(k < arr[1]) flag=1;
    for(int i=2;i<=mx;i++)
        if((long long)arr[i-1]*(k-1)<arr[i]) flag=1;
    if(flag)printf("-1");
    else
    {
        printf("%d\n",n-1);
        for(int i=0;i<mx;i++)
        {
            while(arr[i+1])
            {
                int x = que[i].front();que[i].pop();
                for(int j=1;arr[i+1]&&j<=k-1+(i==0);j++)
                {
                    int y = que[i+1].front();que[i+1].pop();
                    que[i+1].push(y); arr[i+1]--;
                    printf("%d %d\n",x,y);
                }
            }
        }
    }
    return 0;
}
```
  - **核心实现思想**：先统计每个距离值出现的次数并存储对应顶点到队列。通过判断距离为0的点是否唯一、距离为1的点个数与 $k$ 的关系以及各距离层点个数与度数限制的关系来确定是否有解。有解时，从距离0开始依次连边，利用队列操作实现。

- **作者：Umbrella_Leaf (4星)**
  - **关键亮点**：通过将问题转化为构造最短路树来简化问题，思路直观。利用 `vector` 存储深度相同的节点，代码简洁明了。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v[100005];
int d[100005],fa[100005];
int n,k;
int root,num;
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&d[i]);
        if(d[i]==0){
            root=i;
            num++;
        }
        v[d[i]].push_back(i);
    }
    if(num!=1){
        puts("-1");
        return 0;
    }
    if(n==1){
        puts("0");
        return 0;
    }
    if(v[1].size()>k){
        puts("-1");
        return 0;
    }
    for(int i=0;i<v[1].size();i++)fa[v[1][i]]=root;
    for(int i=2;i<n;i++){
        if(v[i].size()>(long long)(k-1)*(v[i-1].size())){
            puts("-1");
            return 0;
        }
        for(int j=0;j<v[i].size();j++)fa[v[i][j]]=v[i-1][j/(k-1)];
    }
    printf("%d\n",n-1);
    for(int i=1;i<=n;i++)if(i!=root)printf("%d %d\n",i,fa[i]);
    return 0;
}
```
  - **核心实现思想**：先记录根节点，判断根节点是否唯一及深度为1的点个数是否符合度数限制。然后通过遍历各深度层，根据度数限制条件判断无解情况，同时用 `fa` 数组记录节点的父亲节点，最后输出边。

- **作者：TheSky233 (4星)**
  - **关键亮点**：巧妙利用树的性质将图的问题简化，清晰地列举出所有无解情况，代码结构清晰。
  - **重点代码**：
```cpp
#include<cstdio>
#include<vector>
#include<cstdlib>
using namespace std;

const int N=1e5+5;

int n,k,MaxDep;
int dis[N];
vector<int> v[N];
vector<pair<int,int> > ans;

void Exit(int num){
    printf("%d\n",num);
    exit(0);
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&dis[i]);
        v[dis[i]].push_back(i);
        MaxDep=max(dis[i],MaxDep);
    }
    if(v[0].size()!=1 || v[0].size()*k<v[1].size()) Exit(-1);
    if(n==1) Exit(0);
    for(int i=0;i<v[1].size();i++) ans.push_back(make_pair(v[0][0],v[1][i]));
    for(int i=2;i<=MaxDep;i++){
        if(v[i].size()==0) Exit(-1);
        if((v[i-1].size()*(long long)(k-1)<v[i].size() && i!=1)) Exit(-1);
        for(int j=0;j<v[i].size();j++)
            ans.push_back(make_pair(v[i-1][j/(k-1)],v[i][j]));
    }
    printf("%d\n",ans.size());
    for(int i=0;i<ans.size();i++)
        printf("%d %d\n",ans[i].first,ans[i].second);
    return 0;
}
```
  - **核心实现思想**：先将各距离的点存储到 `vector` 中，判断无解情况，包括根节点数量、根节点孩子数量及各层节点数量与度数限制的关系。有解时，从根节点开始依次连接各层节点，将边存入 `ans` 中最后输出。

### 最优关键思路或技巧
将图的构造问题转化为树的构造问题，利用树中路径唯一简化问题。通过分析节点度数限制和距离关系来判断无解情况，在连边时按照距离递增的顺序，利用数据结构（如队列、`vector`）存储同距离节点，使操作更有序高效。

### 可拓展之处
此类题目属于图的构造类型，通常给定一些图的性质和限制条件，要求构造出满足条件的图或判断是否存在这样的图。类似的题目可能会改变边权、度数限制条件或最短路的计算方式等。解题时关键是抓住给定条件，将复杂的图问题转化为更易处理的结构（如树），并合理利用数据结构辅助实现。

### 洛谷相似题目
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)
- [P1993 小K的农场](https://www.luogu.com.cn/problem/P1993)
- [P2761 软件补丁问题](https://www.luogu.com.cn/problem/P2761)

### 个人心得
无

---
处理用时：83.95秒