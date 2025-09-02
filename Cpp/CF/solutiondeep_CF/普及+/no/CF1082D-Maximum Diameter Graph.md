# 题目信息

# Maximum Diameter Graph

## 题目描述

Graph constructive problems are back! This time the graph you are asked to build should match the following properties.

The graph is connected if and only if there exists a path between every pair of vertices.

The diameter (aka "longest shortest path") of a connected undirected graph is the maximum number of edges in the shortest path between any pair of its vertices.

The degree of a vertex is the number of edges incident to it.

Given a sequence of $ n $ integers $ a_1, a_2, \dots, a_n $ construct a connected undirected graph of $ n $ vertices such that:

- the graph contains no self-loops and no multiple edges;
- the degree $ d_i $ of the $ i $ -th vertex doesn't exceed $ a_i $ (i.e. $ d_i \le a_i $ );
- the diameter of the graph is maximum possible.

Output the resulting graph or report that no solution exists.

## 说明/提示

Here are the graphs for the first two example cases. Both have diameter of $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1082D/1b7fb105b3cde080c9710b0afa613b7d3cfaed06.png) $ d_1 = 1 \le a_1 = 2 $  $ d_2 = 2 \le a_2 = 2 $

 $ d_3 = 1 \le a_3 = 2 $

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1082D/a291014788668d36fcaf7a8e87cdf44a6c2682df.png) $ d_1 = 1 \le a_1 = 1 $  $ d_2 = 4 \le a_2 = 4 $

 $ d_3 = 1 \le a_3 = 1 $

 $ d_4 = 1 \le a_4 = 1 $

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
YES 2
2
1 2
2 3
```

## 样例 #2

### 输入

```
5
1 4 1 1 1
```

### 输出

```
YES 2
4
1 2
3 2
4 2
5 2
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 最大直径图

## 题目描述
图的构造问题又来啦！这次要求你构建的图需满足以下性质。
当且仅当每对顶点之间都存在一条路径时，该图是连通的。
连通无向图的直径（即“最长最短路径”）是其任意一对顶点之间最短路径中的最大边数。
顶点的度是与之关联的边的数量。
给定一个由 $n$ 个整数组成的序列 $a_1, a_2, \dots, a_n$，构造一个具有 $n$ 个顶点的连通无向图，使得：
- 该图不包含自环和重边；
- 第 $i$ 个顶点的度 $d_i$ 不超过 $a_i$（即 $d_i \le a_i$）；
- 该图的直径尽可能大。
输出最终的图，若不存在解则报告无解。

## 说明/提示
以下是前两个示例情况的图。它们的直径均为 $2$。
![第一个示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1082D/1b7fb105b3cde080c9710b0afa613b7d3cfaed06.png) 
$d_1 = 1 \le a_1 = 2$  ，$d_2 = 2 \le a_2 = 2$  ，$d_3 = 1 \le a_3 = 2$ 

![第二个示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1082D/a291014788668d36fcaf7a8e87cdf44a6c2682df.png) 
$d_1 = 1 \le a_1 = 1$  ，$d_2 = 4 \le a_2 = 4$  ，$d_3 = 1 \le a_3 = 1$  ，$d_4 = 1 \le a_4 = 1$ 

## 样例 #1
### 输入
```
3
2 2 2
```
### 输出
```
YES 2
2
1 2
2 3
```

## 样例 #2
### 输入
```
5
1 4 1 1 1
```
### 输出
```
YES 2
4
1 2
3 2
4 2
5 2
```

## 样例 #3
### 输入
```
3
1 1 1
```
### 输出
```
NO
```

### 算法分类
构造

### 题解综合分析与结论
- **思路**：几篇题解都基于贪心思想，认为要使图的直径最大，应尽量构造链状结构。先处理度数大于等于2的点形成链，再将度数为1的点连接到链上。
- **算法要点**：统计度数为1和度数大于等于2的点，将度数大于等于2的点连成链，同时记录每个点剩余可连接的度数。然后依次将度数为1的点连接到链上合适的点，过程中要判断是否能成功连接所有点。
- **解决难点**：难点在于如何合理地将度数为1的点连接到链上以保证直径最大且满足度数限制，同时要准确判断无解的情况，如所有点度数都为1或无法连接所有点。

### 所选的题解
- **作者：米奇奇米 (5星)**
    - **关键亮点**：思路清晰，代码实现详细，通过贪心构造链，先将度数大于等于2的点连成链，再将度数为1的点粘到链上，还特别提到将两个度为1的点粘到链两端使直径最长，对不合法情况判断准确。
    - **核心代码片段**：
```cpp
int main() {
    n=read();
    For(i,1,n) {
        int s=read();
        du[i]=s;
        if(s==1) one[++s]=i;
    }
    if(one[1]) tmp[1]=one[1];
    For(i,1,n) if(du[i]!=1) tmp[++tot]=i;
    if(one[2]) tmp[++tot]=one[2];
    if(!tot) return printf("NO\n"),0;
    For(i,1,tot-1) {
        e[++m][0]=tmp[i];
        e[m][1]=tmp[i+1];
        Du[tmp[i]]+=1;
        Du[tmp[i+1]]+=1;
        G[tmp[i]][tmp[i+1]]=G[tmp[i+1]][tmp[i]]=1;
    }
    For(i,1,tot) if(du[tmp[i]]>=2) {
        if(Du[tmp[i]]>=du[tmp[i]]) continue;
        For(j,1,n) 
            if(du[j]==1&&j!=tmp[i]&&!G[j][tmp[i]]) {
                if(Du[j]>=du[j]) continue;
                if(Du[tmp[i]]>=du[tmp[i]]) continue;
                e[++m][0]=tmp[i];
                e[m][1]=j;
                Du[tmp[i]]+=1;
                Du[j]+=1;
            }
    }
    For(i,1,n) if(!Du[i]) return printf("NO\n"),0;
    printf("YES ");
    For(i,1,m) jia(e[i][0],e[i][1]),jia(e[i][1],e[i][0]);
    dfs(1,0,0);
    md=0;
    dfs(rt,0,0);
    wln(md);
    wln(m);
    For(i,1,m) wrn(e[i][0]),wln(e[i][1]);
    return 0;
}
```
    - **核心实现思想**：先读入各点度数，将度数为1和不为1的点分别存储。将不为1的点连成链，再尝试将度数为1的点连接到链上度数未达上限的点。最后通过两次DFS求树的直径并输出图的信息。
- **作者：Dilute (4星)**
    - **关键亮点**：同样思路清晰，代码简洁，先将度数大于等于2的点连成链，再按特定顺序将度数为1的点连接到链上，通过DFS求直径。
    - **核心代码片段**：
```cpp
int main(){
    memset(head, -1, sizeof(head));
    int n = inp();
    for(int i = 1; i <= n; i++){
        d[i] = inp();
        if(d[i] == 0){
            printf("NO");
            return 0;
        }
    }
    int c = 0;
    for(int i = 1; i <= n; i++){
        if(d[i] >= 2)
            s[++c] = (Node){i, d[i] - 2};
    }
    if(c == 0){
        printf("NO");
        return 0;
    }
    int cur = 1;
    s[1].res++;
    s[c].res++;
    bool flg = false;
    for(int i = 1; i <= n; i++){
        if(d[i] < 2){
            if(!flg){
                link(i, s[c].x);
                link(s[c].x, i);
                s[c].res--;
                flg = true;
                continue;
            }
            while(s[cur].res <= 0 && cur <= c)
                cur++;
            if(cur > c){
                printf("NO");
                return 0;
            }
            s[cur].res--;
            link(i, s[cur].x);
            link(s[cur].x, i);
        }
    }
    for(int i = 1; i < c; i++){
        link(s[i].x, s[i + 1].x);
        link(s[i + 1].x, s[i].x);
    }
    dfs(1, -1);
    int max = 0;
    int maxk;
    for(int i = 1; i <= n; i++)
        if(dis[i] > max){
            max = dis[i];
            maxk = i;
        }
    dis[maxk] = 0;
    dfs(maxk, -1);
    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(dis[i] > ans)
            ans = dis[i];
    }
    printf("YES %d\n", ans);
    printf("%d\n", n - 1);
    for(int i = 1; i <= n; i++)
        for(int x = head[i]; x!= -1; x = nxt[x])
            if(end[x] > i)
                printf("%d %d\n", i, end[x]);
}
```
    - **核心实现思想**：初始化后，将度数大于等于2的点存起来并连成链，同时调整两端点剩余度数。然后按顺序将度数小于2的点连接到链上合适的点，最后通过两次DFS求直径并输出图的信息。
- **作者：lzyqwq (4星)**
    - **关键亮点**：对不同情况分类讨论清晰，先考虑特殊情况，如所有点度数都为1或度数为1的点较少时的构造，再处理一般情况，用队列维护链上可挂叶子的点，思路明确。
    - **核心代码片段**：
```cpp
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        if(a[i]==1){
            ++cnt;
        }
    }
    if(cnt<=2){
        cout<<"YES "<<n-1<<'\n'<<n-1<<'\n';
        if(!cnt){
            for(int i=1;i<n;++i){
                cout<<i<<' '<<i+1<<'\n';
            }
        }else if(cnt==1){
            for(int i=1,la=0;i<=n;++i){
                if(a[i]==1)du1[1]=i;
                else{
                    if(ed)g.emplace_back(ed,i);
                    else st=i;
                    ed=i;
                }
            }
            g.emplace_back(du1[1],st);
            for(pii i:g){
                cout<<i.fi<<' '<<i.se<<'\n';
            }
        }else{
            int tot=0;
            for(int i=1;i<=n;++i){
                if(a[i]==1)du1[++tot]=i;
                else{
                    if(ed)g.emplace_back(ed,i);
                    else st=i;
                    ed=i;
                }
            }
            g.emplace_back(du1[1],st),g.emplace_back(du1[2],ed);
            for(pii i:g){
                cout<<i.fi<<' '<<i.se<<'\n';
            }
        }
        return 0;
    }
    cnt=0;
    for(int i=1;i<=n;++i){
        if(a[i]==1&&cnt<2){
            a[i]=0;
            vis[i]=1;
            ++cnt;
            du1[cnt]=i;
            ++ans;
        }else if(a[i]!=1){
            a[i]-=2;
            if(!ed){
                st=i;
            }else{
                g.emplace_back(ed,i);
            }
            ed=i;
            if(a[i]){
                q.emplace_back(a[i],i);
            }
            vis[i]=1;
            ++ans;
        }
    }
    g.emplace_back(du1[1],st);
    g.emplace_back(ed,du1[2]);
    for(int i=1;i<=n;++i){
        if(!vis[i]&&a[i]==1){
            if(!q.size()){
                cout<<"NO";
                return 0;
            }
            pii u=q.front();
            q.pop_front();
            --u.fi;
            g.emplace_back(i,u.se);
            if(u.fi){
                q.emplace_front(u);
            }
        }
    }
    cout<<"YES "<<ans-1<<'\n'<<g.size()<<'\n';
    for(pii i:g){
        cout<<i.fi<<' '<<i.se<<'\n';
    }
    return 0;
}
```
    - **核心实现思想**：先统计度数为1的点的数量，分情况处理。当度数为1的点较少时直接构造。当较多时，先将度数为1的点中两个放到链两端，其余点尝试挂到链上用队列维护的可挂点上，最后输出图的信息。

### 最优关键思路或技巧
- **贪心构造链**：优先将度数大于等于2的点构造为链，能使直径在满足度数限制下尽量大。
- **合理连接度数为1的点**：将度数为1的点连接到链两端或链上合适位置，如先连接到链尾，再从链头开始连接剩余度数为1的点，保证直径最大。
- **准确判断无解情况**：判断所有点度数都为1或无法连接所有点的情况，确保程序正确性。

### 可拓展之处
- **同类型题**：此类图的构造题目常围绕图的各种性质和限制条件，如给定度数序列构造特定图，或构造满足某种连通性、直径、边权等条件的图。
- **类似算法套路**：遇到此类构造图的问题，通常先分析目标性质（如本题直径最大）对应的图结构（链状），再根据限制条件（度数限制）逐步构造，过程中注意判断无解情况。

### 推荐洛谷题目
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：涉及图的构造与染色问题，通过合理构造图的连接关系满足题目要求。
- [P2827 [NOIP2016 提高组] 蚯蚓](https://www.luogu.com.cn/problem/P2827)：虽然不是图的构造，但同样运用贪心思想解决问题，与本题贪心构造图的思路类似。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：贪心算法的经典应用，通过对线段的合理选择构造满足条件的方案，与本题贪心选择点构造图有相似之处。

### 个人心得摘录与总结
无

---
处理用时：119.93秒