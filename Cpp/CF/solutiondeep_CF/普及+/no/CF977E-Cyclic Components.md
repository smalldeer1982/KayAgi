# 题目信息

# Cyclic Components

## 题目描述

给定一张 $n$ 个点，$m$ 条边的无向图。保证无重边、无自环。在该图的所有连通块中，你需要找出环的个数。



无向图的环的定义如下：



原无向图中的一个子图被定义为环，当且仅当它的点集重新排序后可以满足如下条件：



- 第一个点与第二个点通过一条边相连接；

- 第二个点与第三个点通过一条边相连接；

- ……

- 最后一个点与第一个点通过一条边相连接。

- 所有的边都应当是不同的。

- 其边集不应当包含除了以上所述的边以外的任何边。



这样，我们就称这个子图（点 + 边）为环。



根据定义，一个环至少需要包含三个点，且边数与点数应当是相同的。



![](https://cdn.luogu.org/upload/vjudge_pic/CF977E/4eb49ec2d535d241bf8aedac2221e1f54d715822.png)



例如对于上图，共有 $6$ 个联通块，但只有 $[7,10,16]$ 和 $[5,11,9,15]$ 这两个联通块是环。

## 说明/提示

在第一个样例中，只有 $[3, 4, 5]$ 这个联通块是一个环。



第二个样例就对应着题目解释中的图片。

## 样例 #1

### 输入

```
5 4
1 2
3 4
5 4
3 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
17 15
1 8
1 12
5 11
11 9
9 15
15 5
4 13
3 13
4 3
10 16
7 10
16 7
14 3
14 4
17 6
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# 循环组件

## 题目描述
给定一张 $n$ 个点，$m$ 条边的无向图。保证无重边、无自环。在该图的所有连通块中，你需要找出环的个数。

无向图的环的定义如下：

原无向图中的一个子图被定义为环，当且仅当它的点集重新排序后可以满足如下条件：
- 第一个点与第二个点通过一条边相连接；
- 第二个点与第三个点通过一条边相连接；
- ……
- 最后一个点与第一个点通过一条边相连接。
- 所有的边都应当是不同的。
- 其边集不应当包含除了以上所述的边以外的任何边。

这样，我们就称这个子图（点 + 边）为环。

根据定义，一个环至少需要包含三个点，且边数与点数应当是相同的。

![](https://cdn.luogu.org/upload/vjudge_pic/CF977E/4eb49ec2d535d241bf8aedac2221e1f54d715822.png)

例如对于上图，共有 $6$ 个联通块，但只有 $[7,10,16]$ 和 $[5,11,9,15]$ 这两个联通块是环。

## 说明/提示
在第一个样例中，只有 $[3, 4, 5]$ 这个联通块是一个环。

第二个样例就对应着题目解释中的图片。

## 样例 #1
### 输入
```
5 4
1 2
3 4
5 4
3 5
```
### 输出
```
1
```

## 样例 #2
### 输入
```
17 15
1 8
1 12
5 11
11 9
9 15
15 5
4 13
3 13
4 3
10 16
7 10
16 7
14 3
14 4
17 6
```
### 输出
```
2
```

### 算法分类
图论

### 综合分析与结论
这些题解主要围绕判断无向图中连通块是否为环展开。核心思路是利用环的性质，即环内所有点度数为2 。在实现上，部分题解使用并查集维护连通块（如Otue、first_fan、FiraCode的题解），部分使用深度优先搜索（如StudyingFather、FanYongchen、ModestCoder_ 、RainbOwO的题解），还有使用广度优先搜索（如ZZQF5677的题解）或结合多种搜索方式（如Priori_Incantatem的题解）。各题解的主要区别在于数据结构的选择和搜索方式的运用，难点在于准确判断每个连通块是否符合环的定义，特别是处理图的连通性和度数判断的结合。

### 所选的题解
- **Otue（5星）**
  - **关键亮点**：思路清晰简洁，代码短小精悍。利用并查集高效维护连通块，通过一次遍历统计度数，再通过两次遍历判断连通块是否为环，时间复杂度低。
  - **个人心得**：无
  ```c++
  int find(int x) {
      if (p[x]!= x) p[x] = find(p[x]);
      return p[x];
  }

  int main() {
      cin >> n >> m;
      for (int i = 1; i <= n; i++) p[i] = i;
      for (int i = 1; i <= m; i++) {
          int a, b;
          cin >> a >> b;
          p[find(a)] = find(b);
          d[a]++, d[b]++;
      }
      for (int i = 1; i <= n; i++) {
          if (d[i]!= 2) st[find(i)] = 1;  
      }
      for (int i = 1; i <= n; i++) {
          if (find(i) == i && st[find(i)] == 0) res++;
      }
      cout << res << endl;
  }
  ```
- **StudyingFather（4星）**
  - **关键亮点**：利用DFS求出所有连通分量，代码结构清晰，逻辑直接。在DFS过程中记录路径，然后通过判断路径上点的度数来确定是否为环。
  - **个人心得**：无
  ```c++
  void dfs(int u) {
      vis[u]=1;
      path.push_back(u);
      for(int i=head[u];i;i=e[i].next)
          if(!vis[e[i].v])dfs(e[i].v);
      return;
  }

  int main() {
      int n,m,ans=0;
      scanf("%d%d",&n,&m);
      for(int i=1;i<=m;i++) {
          int u,v;
          scanf("%d%d",&u,&v);
          t[u]++,t[v]++;
          addedge(u,v);
          addedge(v,u);
      }
      for(int i=1;i<=n;i++)
          if(!vis[i]) {
              path.clear();
              dfs(i);
              int maxn=path.size(),flag=1;
              for(int i=0;i<maxn;i++)
                  if(t[path[i]]!=2) {
                      flag=0;
                      break;
                  }
              ans+=flag;
          }
      printf("%d\n",ans);
      return 0;
  }
  ```
- **Priori_Incantatem（4星）**
  - **关键亮点**：综合运用DFS和BFS。DFS用于判环，BFS用于计算点数和边数并判等，同时结合度数判断，思路较为全面。
  - **个人心得**：通过多次调试，逐步完善代码，先是DFS判环不过样例，增加BFS计算点数边数，又在第三个点挂掉，最终加上度数判断才AC。
  ```c++
  bool dfs(int x,int fa,int top) {
      vis[x]=1;
      for(int i=0;i<e[x].size();++i) {
          int y=e[x][i];
          if(y==fa)continue;
          if(vis[y] && y!=top)return 0;
          if(y==top)return 1;
          bool flag=dfs(y,x,top);
          if(flag)return 1;
      }
      return 0;
  }
  bool bfs(int s) {
      queue <int> q;
      int cnt=0,tot=0;
      vist[s]=1,q.push(s);
      while(q.size()) {
          int x=q.front();
          q.pop();
          ++cnt;
          if(d[x]!=2)return 0;
          for(int i=0;i<e[x].size();++i) {
              int y=e[x][i];
              ++tot;
              if(vist[y])continue;
              vist[y]=1,q.push(y);
          }
      }
      tot>>=1;
      return cnt==tot;
  }

  int main() {
      n=read(),m=read();
      for(int i=1;i<=m;++i) {
          int x=read(),y=read();
          e[x].push_back(y);
          e[y].push_back(x);
          d[x]++,d[y]++;
      }
      for(int i=1;i<=n;++i) {
          if(vis[i])continue;
          bool flag=dfs(i,0,i) && bfs(i);
          if(flag)++ans;
      }
      printf("%d\n",ans);
      return 0;
  }
  ```

### 最优关键思路或技巧
利用环内点度数为2这一性质，结合并查集或搜索算法（DFS、BFS）来判断连通块是否为环。并查集能高效维护连通性，搜索算法能遍历连通块内的点。

### 可拓展之处
同类型题可考察不同图结构中环的判断，或结合其他图论问题，如在有向图中判断环、求环的长度等。类似算法套路是先明确目标子图的性质，再选择合适的数据结构和搜索算法去实现判断。

### 洛谷相似题目推荐
- [P1196 银河英雄传说](https://www.luogu.com.cn/problem/P1196)：并查集应用，与本题使用并查集维护连通性有相似之处。
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：涉及图的连通块判断，可使用DFS或BFS解决，和本题判断连通块性质类似。
- [P1603 斯诺登的密码](https://www.luogu.com.cn/problem/P1603)：同样是图论问题，通过搜索判断图中满足特定条件的子图，与本题思路有共通点。 

---
处理用时：53.67秒