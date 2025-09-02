# 题目信息

# Robot Rapping Results Report

## 题目描述

#### 题目简述
$n$ 个机器人，每个机器人有一个不同的级别，级别介于 $1\sim n$，高级别的可以打败低级别的，现在给出 $n$ 个机器人的 $m$ 场比赛胜负情况，问最少需要前几场比赛就可以确定每个机器人的级别。

## 说明/提示

$2\leq n\leq 10^5$，$1\leq m\leq \min(\frac{n\times (n-1)}{2},10^5)$。

## 样例 #1

### 输入

```
4 5
2 1
1 3
2 3
4 2
4 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 2
1 2
3 2
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 机器人说唱比赛结果报告

## 题目描述

#### 题目简述
有\(n\)个机器人，每个机器人都有不同的级别，级别范围在\(1\)到\(n\)之间，高级别的机器人可以打败低级别的机器人。现在给出\(n\)个机器人之间的\(m\)场比赛胜负情况，问最少需要前几场比赛就能确定每个机器人的级别。

## 说明/提示
\(2\leq n\leq 10^5\)，\(1\leq m\leq \min(\frac{n\times (n - 1)}{2},10^5)\)。

## 样例 #1
### 输入
```
4 5
2 1
1 3
2 3
4 2
4 3
```
### 输出
```
4
```

## 样例 #2
### 输入
```
3 2
1 2
3 2
```
### 输出
```
-1
```

### 算法分类
二分 + 图论（拓扑排序）

### 题解综合分析与结论
这些题解主要围绕二分答案与拓扑排序展开。核心思路是利用二分查找确定最少比赛场数，通过拓扑排序判断该场数下能否确定机器人级别。若在拓扑排序过程中，入度为\(0\)的点多于一个，说明机器人等级顺序不唯一，无法确定级别。

各题解的不同之处主要在于实现细节，如存图方式（vector存图、链式前向星存图等），以及对拓扑排序结果判断和记录的方式。部分题解还对代码进行了一些优化，如减少不必要的初始化操作等。

### 所选的题解
- **作者：EnochWenzhou（5星）**
  - **关键亮点**：提出了时间复杂度为\(O(n)\)的优秀做法。在拓扑排序时记录确定每个点拓扑序的最少边数，通过巧妙的更新策略，避免了二分查找，直接得到结果，大大优化了时间复杂度。
  - **个人心得**：无
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define rint register int
#define M 100010
using namespace std;
int n,m,a1,b1,cnt,in[M],nt[M],to[M],ft[M],id[M],dfn[M],ID[M],mk[M],ans,F;
queue<int>q;
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a1,&b1);
        cnt++,id[cnt]=i,to[cnt]=b1,nt[cnt]=ft[a1],ft[a1]=cnt;in[b1]++;
    }
    for(int i=1;i<=n;i++)
        if(!in[i]){
            if(F){cout<<-1;return 0;}
            q.push(i),F=1;
        }
    while(q.size()){
        int x=q.front();q.pop();
        for(int i=ft[x];i;i=nt[i]){
            int y=to[i];
            if(dfn[y]==dfn[x]+1)ID[y]=min(ID[y],id[i]);
            if(dfn[y]<dfn[x]+1)dfn[y]=dfn[x]+1,ID[y]=id[i];
            if(!(--in[y]))q.push(y);
        }
    }
    for(int i=1;i<=n;i++){if(mk[dfn[i]]){cout<<-1;return 0;}mk[dfn[i]]=1;}
    for(int i=1;i<=n;i++)ans=max(ans,ID[i]);
    cout<<ans;
    return 0;
}
```
  - **核心实现思想**：在拓扑排序过程中，使用`dfn`数组记录拓扑序，`ID`数组记录确定该点拓扑序的最少边数。遍历每条边时，根据当前点和目标点的拓扑序关系，更新目标点的拓扑序和最少边数。最后通过检查拓扑序是否唯一以及取所有点最少边数的最大值得到答案。
- **作者：Allanljx（4星）**
  - **关键亮点**：思路清晰，代码简洁明了。采用二分答案结合拓扑排序的常规思路，代码实现过程中，函数模块化，将初始化、拓扑排序、检查等操作分别封装成函数，提高了代码的可读性。
  - **个人心得**：无
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
queue<int> q;
int n,m,ans;
vector<int> t[100005];
int in[100005];
int vis[100005];
int u[100005],v[100005];
void init()//初始化 
{
    memset(in,0,sizeof(in));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) t[i].clear();
    while(q.size()) q.pop();
}
bool topo()//拓扑排序 
{
    for(int i=1;i<=n;i++) if(!in[i]) q.push(i),vis[i]=1;
    while(q.size())
    {
        if(q.size()>1) return 0;//入度为0的点不止一个 
        int f=q.front();
        q.pop();
        for(int i=0;i<t[f].size();i++)
        {
            in[t[f][i]]--;
            if(!in[t[f][i]]&&!vis[t[f][i]]) q.push(t[f][i]),vis[t[f][i]]=1;
        }
    }
    return 1;
}
bool check(int x)
{
    for(int i=1;i<=x;i++)//建图，统计入度 
    {
        t[u[i]].push_back(v[i]);
        in[v[i]]++;
    }
    return topo();
}
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i];
    int l=1,r=m;
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
        init();
    }
    if(!ans) puts("-1");//没找到（无法确定） 
    else cout<<ans<<endl;
    return 0;
}
```
  - **核心实现思想**：通过二分法确定比赛场数`mid`，在`check`函数中构建前`mid`条边的图并统计入度，调用`topo`函数进行拓扑排序。在拓扑排序中，若队列中同时存在多个入度为\(0\)的点，则返回\(0\)表示无法确定级别，否则返回\(1\)。根据`check`函数的结果调整二分区间，最终得到最少比赛场数。
- **作者：Diode123（4星）**
  - **关键亮点**：详细解释了参考自EnochWenzhou大佬的\(O(n)\)做法，对其中的变量含义和更新策略使用Latex进行了清晰的说明，方便读者理解。代码注释详细，对链式前向星存图和拓扑排序过程中的关键步骤都进行了注释。
  - **个人心得**：参考EnochWenzhou大佬题解，因原解未用Latex且变量命名易混淆，故重写题解使其更易懂。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define N 100005 
using namespace std;
struct Edge{
    int next, to;
}edge[N<<2]; //链式前向星
int head[N], cnt, n, m, ind[N], k, tp[N], ged[N]; //同正文
bool flag=1; //用于指示是否有多个拓扑序
void AddEdge(int from, int to){ 
    edge[++cnt].next = head[from];
    edge[cnt].to = to;
    head[from] = cnt; //如果你的样例1输出3，可以检查你的边的编号是否从1开始
}
void toposort(){ //BFS 跑拓扑序
    queue<int> q;
    for(int i=1; i<=n; i++){
        if(ind[i]==0){ q.push(i);}
    } 
    while(!q.empty()){
        if(q.size()>1){ flag=0; return ; }  
        int nx= q.front(); q.pop(); tp[nx]=++k;
        for(int i=head[nx]; ~i; i=edge[i].next){
            int to = edge[i].to;
            if(tp[to]==tp[nx]+1) ged[to]=min(ged[to],i);
            if(tp[to]<tp[nx]+1) tp[to]=tp[nx]+1,ged[to]=i; //同正文
            ind[to]--;
            if(!ind[to]){ q.push(to); }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    memset(head, -1, sizeof head);
    cin >> n >> m;
    for(int i=1,u,v; i<=m; i++){
        cin >> u >> v;
        AddEdge(u,v);
        ind[v]++;
    }
    toposort();
    int ans=0;
    if(flag){
        for	(int i=1; i<=n; i++) ans = max(ans,ged[i]);
        cout<<ans;
    } 
    else cout<< -1;
    return 0;
}
```
  - **核心实现思想**：与EnochWenzhou的\(O(n)\)做法类似，使用链式前向星存图，在拓扑排序过程中，根据当前点和目标点的拓扑序关系，更新目标点的拓扑序`tp`和确定该点拓扑序的编号最小边`ged`。最后根据是否存在多个拓扑序以及取`ged`数组的最大值得到答案。

### 最优关键思路或技巧
EnochWenzhou提出的在拓扑排序时直接记录确定每个点拓扑序的最少边数的方法是最优技巧。这种方法避免了常规的二分查找过程，将时间复杂度从\(O(n \log n)\)优化到\(O(n)\)，大大提高了算法效率。其关键在于设计合理的更新策略，根据当前点和目标点的拓扑序关系，准确更新目标点的拓扑序和最少边数。

### 可拓展思路
此类题目属于图论中拓扑排序结合二分查找的类型。相似套路是当问题具有单调性，且可以通过某种方式判断某个值是否满足条件时，可考虑二分答案。在图论场景下，常结合拓扑排序判断图的连通性、节点顺序的唯一性等。例如，在一些任务调度问题中，任务之间存在先后顺序关系，可转化为有向图，通过拓扑排序判断任务能否顺利执行，并可利用二分查找优化寻找满足条件的最小资源或时间等。

### 洛谷相似题目推荐
- [P1983 车站分级](https://www.luogu.com.cn/problem/P1983)：同样涉及拓扑排序，通过火车停靠站点信息确定车站级别，需要判断不同车站之间的等级关系，与本题判断机器人级别有相似之处。
- [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)：该题涉及有向图的缩点操作，缩点后进行拓扑排序，对于理解图论中复杂结构的处理和拓扑排序的应用有帮助，与本题在图论处理思路上有一定关联。
- [P2831 [NOIP2016 提高组] 愤怒的小鸟](https://www.luogu.com.cn/problem/P2831)：虽然不完全是图论问题，但需要通过枚举和状态压缩动态规划解决，其中枚举部分与二分查找类似，都是在一定范围内寻找满足条件的解，有助于拓展相关算法的应用能力。 

---
处理用时：97.06秒