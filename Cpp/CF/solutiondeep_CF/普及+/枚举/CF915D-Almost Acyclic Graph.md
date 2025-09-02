# 题目信息

# Almost Acyclic Graph

## 题目描述

You are given a [directed graph](https://en.wikipedia.org/wiki/Directed_graph) consisting of $ n $ vertices and $ m $ edges (each edge is directed, so it can be traversed in only one direction). You are allowed to remove at most one edge from it.

Can you make this graph [acyclic](https://en.wikipedia.org/wiki/Directed_acyclic_graph) by removing at most one edge from it? A directed graph is called acyclic iff it doesn't contain any cycle (a non-empty path that starts and ends in the same vertex).

## 说明/提示

In the first example you can remove edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), and the graph becomes acyclic.

In the second example you have to remove at least two edges (for example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/7480c546ca7ee72615c3ded7d769355b1c864f93.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png)) in order to make the graph acyclic.

## 样例 #1

### 输入

```
3 4
1 2
2 3
3 2
3 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 6
1 2
2 3
3 2
3 1
2 1
4 5
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 近乎无环图

## 题目描述
给定一个由 $n$ 个顶点和 $m$ 条边组成的有向图（每条边都是有向的，因此只能沿一个方向遍历）。你最多可以从图中移除一条边。
通过最多移除一条边，能否使该图变为无环图？如果一个有向图不包含任何环（即从某个顶点出发并回到该顶点的非空路径），则称该有向图为无环图。

## 说明/提示
在第一个示例中，你可以移除边 $(3, 2)$，图就变为无环图。
在第二个示例中，你至少需要移除两条边（例如，$(3, 2)$ 和 $(2, 1)$）才能使图变为无环图。

## 样例 #1
### 输入
```
3 4
1 2
2 3
3 2
3 1
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
5 6
1 2
2 3
3 2
3 1
2 1
4 5
```
### 输出
```
NO
```

### 综合分析与结论
这些题解的核心思路都是围绕拓扑排序来判断图是否有环，并且都意识到暴力枚举删边（时间复杂度 $O(m(n + m))$）会超时，需要进行优化。优化的关键在于发现删除指向同一个点的不同边，对拓扑排序的影响是相同的，即都是使该点入度减一。所以改为枚举点，让每个入度不为0的点入度减一，再进行拓扑排序判断是否无环，将时间复杂度降低到 $O(n(n + m))$。

各题解的不同主要体现在代码实现细节，如变量命名、数据结构使用、拓扑排序具体实现方式等。

### 所选的题解
- **作者：青烟绕指柔 (5星)**
    - **关键亮点**：思路清晰简洁，代码实现精炼，使用 `vector` 存储图结构，整体逻辑流畅。
    - **重点代码**：
```cpp
inline int top_sort(){
    int cnt=0;	queue<int> q;
    for(int i=1;i<=n;i++)	if(!dag[i])	q.push(i);
    while(q.size()){
        int u=q.front();	q.pop();	cnt++;
        for(auto to:g[u])	if(--dag[to]==0)	q.push(to);
    }
    return cnt==n;
}
signed main(){
    cin>>n>>m;
    for(int i=1,a,b;i<=m;i++)	scanf("%d %d",&a,&b),g[a].push_back(b),dag[b]++;
    for(int i=1;i<=n;i++)	t[i]=dag[i];
    for(int i=1;i<=n;i++)	if(dag[i]){
        dag[i]--;	if(top_sort())	return puts("YES"),0;
        for(int i=1;i<=n;i++)	dag[i]=t[i];
    }
    puts("NO");
    return 0;
}
```
    - **核心实现思想**：`top_sort` 函数实现拓扑排序，通过队列将入度为0的点依次处理，更新其他点入度并判断最终处理的点数是否等于总点数来确定是否有环。主函数先读入图，备份入度数组，然后枚举每个入度不为0的点，将其入度减一进行拓扑排序，若成功则说明可通过删边使图无环。
- **作者：CharlesZiy (4星)**
    - **关键亮点**：对思路阐述详细，特别是对拓扑排序模板的分析以及优化思路的推导很清晰，代码注释详细，考虑到了很多细节。
    - **重点代码**：
```cpp
bool topsort()
{
    queue<int> q;
    int cnt = 0;
    
    for (int i = 1; i <= n; i++) in[i] = IN[i];
    
    for (int i = 1; i <= n; i++)
    {
        if (in[i] == 0) q.push(i);
    }
    
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        cnt++;
        for (int i = 0; i < e[u].size(); i++)
        {
            int cur = e[u][i];
            in[cur]--;
            if (in[cur] == 0)
            {
                q.push(cur);
            }
        }
    }
    
    return (cnt == n);
}

int main()
{
    std::ios::sync_with_stdio(false);
    
    cin >> n >> m;
    
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        IN[v]++;
    }
    
    for (int i = 1; i <= n; i++)
    {
        bool flag = 0;
        if (IN[i]!= 0)
        {
            IN[i]--;
            flag = true;
        }
        
        if (topsort())
        {
            cout << "YES" << endl;
            return 0;
        }
        
        if (flag == true) IN[i]++;
    }
    
    cout << "NO" << endl;
}
```
    - **核心实现思想**：`topsort` 函数进行拓扑排序，先复制原始入度数组，将入度为0的点入队处理，更新入度并判断是否所有点都能处理完来确定有无环。主函数读入图并记录入度，枚举每个点，若该点入度不为0则减一，进行拓扑排序，若成功则输出 `YES`，最后恢复入度。
- **作者：wangyibo201026 (4星)**
    - **关键亮点**：对优化思路的分析详细，通过对暴力枚举删边的时间复杂度分析，引出优化的必要性，并清晰阐述了优化的原理。代码结构清晰，有明确的函数划分。
    - **重点代码**：
```cpp
bool topo(){
  for(int i = 1; i <= n; i++){
    IN[i] = in[i];
  }
  queue<int> q;
  for(int i = 1; i <= n; i++){
    if(!IN[i]){
      q.push(i);
    }
  }
  int cnt = 0;
  while(!q.empty()){
    int x = q.front();
    q.pop();
    cnt++;
    for(int i = 1; i <= n; i++){
      if(!e[x][i]){
        continue;
      }
      IN[i]--;
      if(!IN[i]){
        q.push(i);
      }
    }
  }
  return cnt == n;
}

void Solve(){
  cin >> n >> m;
  for(int i = 1; i <= m; i++){
    cin >> u[i] >> v[i];
    in[v[i]]++;
    e[u[i]][v[i]] = true;
  }
  if(topo()){
    cout << "YES\n";
    return ;
  }
  for(int i = 1; i <= n; i++){
    if(in[i]){
      in[i]--;
      if(topo()){
        cout << "YES\n";
        return ;
      }
      in[i]++;
    }
  }
  cout << "NO\n";
}
```
    - **核心实现思想**：`topo` 函数实现拓扑排序，先复制入度数组，将入度为0的点入队，处理过程中更新入度并统计处理点数判断是否有环。`Solve` 函数读入图并记录入度，先进行一次拓扑排序看原图是否无环，若有环则枚举每个入度不为0的点，减一入度后再拓扑排序，若成功则输出 `YES`。

### 最优关键思路或技巧
通过深入分析拓扑排序和删边对入度的影响，将暴力枚举删边优化为枚举点，减少重复计算，降低时间复杂度。在代码实现上，注意备份原始入度数组，以便每次拓扑排序前恢复初始状态。

### 可拓展之处
同类型题可考虑增加对边或点的限制条件，或改变图的性质（如变为有权图等）。类似算法套路可应用于其他与图的环相关问题，如判断是否存在特定长度的环，或在有环图中寻找关键边/点等。

### 相似知识点洛谷题目
- **P1983 车站分级**：通过拓扑排序确定车站等级关系，涉及到对图中节点关系的梳理和拓扑排序应用。
- **P3387 【模板】缩点**：在有向图中通过缩点操作转化为DAG，再进行后续处理，与本题对有向图的处理思路相关，涉及到图的结构分析和拓扑排序基础。
- **P2831 [NOIP2016 提高组] 愤怒的小鸟**：虽然不是直接的拓扑排序题，但在处理图状关系和优化枚举过程中，与本题优化枚举思路类似，都需要对问题进行深入分析以减少不必要计算。 

---
处理用时：36.49秒